//***************************************************************************
//       INGENICO                                INGEDEV 7
//===========================================================================
//       FILE  ENTRY.C                           (Copyright INGENICO 2012)
//===========================================================================
//  Created :       09-July-2012     Kassovic
//  Last modified : 09-July-2012     Kassovic
//  Module : TRAINING
//                    
//  Purpose :
//  Each time Manager calls an application, it generates only one service
//  call that reaches your application main with the corresponding service
//  number.
// 
//  List of routines in file :
//      give_your_domain : Return application domain.
//      give_your_specific_context : Return specific context to Manager.
//      Task2 : To manage IAM process.
//      Progress : Progress bar counter.
//      after_reset : Application reset processing.
//      is_name : Report application name to Manager.
//      is_state : Return application status (initialize or not).
//      idle_message : Dedicated to display idle message.
//      more_function : Dedicated to navigation menus.
//      keyboard_event : Return key pressed.
//      get_idle_state_parameter : Give manager parameters to customize idle state
//      give_money_extended : Get the currencies supported by the application.
//      state : Print terminal content.
//      consult : Print daily totals.
//      mcall : Print call schedule.
//      is_time_function : Need peripherals at the next call time_function()
//      time_function : Allow automatic execution of periodic functions.
//      is_change_init : Conditions for changing manager parameters?
//      modif_param : Manager reports parameters changing.
//      is_evol_pg : Conditions for application downloading?
//      is_delete : Conditions for application deletion?
//      file_received : Manager reports parameters file received from LLT.
//      message_received : Inter application messaging.
//      is_card_specific : Card needs a specific process?
//      card_inside : Transaction in progress for a specific card.
//      is_for_you_before : Is chip card as an ISO 7816-3?
//      is_for_you_after : Recognize mag, smc or man card in order to be a candidate.
//      debit_non_emv : Process a non EMV chip card or Mag stripe or card manual entry transaction (Debit).
//      select_function : Process a non EMV chip card or Mag stripe or card manual entry transaction (Credit, Cancel, Pre Auth).
//      give_interface : Services registration and priority.
//      entry : Call by OS for recording services and opening DLL(s).
//      OpenPeripherals : Open standard peripherals.
//      ClosePeripherals : CLose standard peripherals.
//      ResetPeripherals : Reset standard peripherals.
//      SoftwareReset : Reset parameters with default values.
// 
//  File history :
//  070912-BK : File created
//
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "SEC_interface.h"
#include "VGE_FMG.h"
#include "Training.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
const char *getAppCmpDat(void); // See Mapapp.c
const char *getAppCmpTim(void);

void DefaultSettings(void); // See Message.c

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define USER2_APPLI_TYPE	   0x162 // User2 application type
#define TRAINING_APPLI_TYPE    0x161 // Training application type

// Services priority
// =================
#define SERVICES_LOW_PRIORITY           30 // For all services except idle_message,
#define SERVICES_HIGH_PRIORITY          10 //      priority => 0x00 highest and 0xFF lowest
#define IDLE_LOW_PRIORITY               10 // For idle_message,
#define IDLE_HIGH_PRIORITY              30 //      priority => 0x00 lowest 0xFF highest
#define SERVICES_DEFAULT_PRIORITY       20

// Application selection
// =====================
#define AMOUNT_ENTRY           TRUE // FALSE => swipe card from Manager
                                     // then enter Amount into application selected
                                     // TRUE => Enter Amount then swipe card from Manager
                                     // before application selection

// Idle Animation
// ==============
#define MAX_IMG   48
#define ANIMATION              FALSE // FALSE => Please Insert Card shows on Idle Display
                                     // TRUE => Card Animation shows on Idle Display

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
typedef struct stParams // See is_change_init() / modif_param() service call
{
	char tcOldDate[24+1];
	char tcOldFmtDate[24+1];
	char tcOldLanguage[24+1];
	char tcOldPabx[24+1];
	char tcOldPPad[24+1];
	char tcOldPPadType[24+1];
	char tcOldISOreader[24+1];
	char tcOldTMSaccess[24+1];
} ST_PARAMS;

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the Idle screen (Goal)
// ====================================
static const ST_DSP_LINE txIdle[] =
{
	{ {GL_ALIGN_CENTER,   GL_ALIGN_CENTER, GL_COLOR_WHITE,  GL_COLOR_BLACK,   0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}},  // Line1
	  {GL_ALIGN_CENTER,   GL_ALIGN_CENTER, FALSE,   0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_CENTER,   GL_ALIGN_CENTER, GL_COLOR_WHITE,  GL_COLOR_RED,     0, FALSE, {8, 2, 8, 2}, {1, 1, 1, 1, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line2
	  {GL_ALIGN_CENTER,   GL_ALIGN_CENTER, TRUE,    0, FALSE, {8, 4, 8, 2}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}} },
	{ {GL_ALIGN_CENTER,   GL_ALIGN_CENTER, GL_COLOR_WHITE,  GL_COLOR_BLACK,   0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_XLARGE}}, // Line3
	  {GL_ALIGN_CENTER,   GL_ALIGN_CENTER, FALSE,   0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} }
};

// Properties of the animated image (Goal)
// =======================================
static const ST_IMAGE xImage =
{
	{GL_COLOR_WHITE, TRUE, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}, GL_DIRECTION_ALL, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0} },
	{TRUE, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}, GL_DIRECTION_ALL, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0} }
};

// Properties of the default screen (Goal)
// =======================================
static const ST_DSP_LINE txScreen[] =
{
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line0
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE,  100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line1
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE,  100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line2
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE,  100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line3
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE,  100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line4
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE,  100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} }
};


// Properties of the default printer (Goal)
// ========================================
static const ST_PRN_LINE xPrinter =
{
	GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {1, 0, 1, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}
};

// Some messages to display
// ========================
static const char zAppName[] = "TRAINING";                      // Application name
static const char zColdReset[] = "Cold Reset TRAINING";         // See after_reset() service call
static const char zWarmReset[] = "Warm Reset TRAINING";
static const char zTimeToCall[] = "Time to Call TRAINING";      // See time_function() service call
static const char zIdleMsg[] = "Insert or Swipe a Card";        // See idle_message() service call
static const char zDate[] = "Date:%.2s/%.2s/%.2s  %.2s:%.2s\n"; // See state() / consult() / mcall() service call
static const char zDate1[] = "%.2s/%.2s/20%.2s   %.2s:%.2s\n";  // See is_change_init() / modif_param() service call
static const char zDate2[] = "20%.2s/%.2s/%.2s   %.2s:%.2s\n";
static const char zDate3[] = "%.2s.%.2s.20%.2s   %.2s:%.2s\n";

// Some handles
// ============
T_GL_HGRAPHIC_LIB xGoal=NULL; // New instance of the graphics object library
FILE *pxDsp=NULL;             // Peripheral file Display
FILE *pxPrn=NULL;             // Peripheral file Printer
FILE *pxKbd=NULL;             // Peripheral file Keyboard
FILE *pxTsc=NULL;             // Peripheral file Touch

// Parameter disk configuration
// ============================
static S_FS_PARAM_CREATE xCfg;
static unsigned long ulSize;

// Animated image sequence
// =======================
const byte tcIdxImg[MAX_IMG] =
{
	 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
	10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
	 9,  8,  7,  6,  5,  4,  3,  2,  1, 0
};
static word usIdxImg=0;       // Index of image
static word usTimeout=10;     // Timeout between two images
static bool bPictureOk=false; // Flag to check if pictures loaded into HOST disk

// Currency table according to ISO 4217
// ====================================
static const S_MONEY_EXTENDED txCurrency[] =
{
	{{{'E','U','R'}, {'9','7','8'}, 2}, {',', '.', CURRENCY_AFTER_AMOUNT}}, // Euro
	{{{'G','B','P'}, {'8','2','6'}, 2}, {'.', ',', CURRENCY_AFTER_AMOUNT}}, // Pound Sterling
	{{{'U','S','D'}, {'8','4','0'}, 2}, {'.', ',', CURRENCY_AFTER_AMOUNT}}, // United State Dollar
	{{{'I','S','K'}, {'3','5','2'}, 0}, {',', '.', CURRENCY_AFTER_AMOUNT}}, // Icelandic Krona
	{{{'T','N','D'}, {'7','8','8'}, 3}, {',', '.', CURRENCY_AFTER_AMOUNT}}  // Tunisian Dinar
};

// Manager parameters
// ==================
static ST_PARAMS xParams; // See is_change_init() / modif_param() service call

// Backup buffer
// =============
char tcPowerFailure[5*1024]; // Buffer saved automatically from RAM to FLASH in case of power failure

// Task2 used for IAM process
// ==========================
static word usMainTaskNbr;
static S_MESSAGE_IAM xMessage;

// Main menu and sub-menu(s)
// =========================
static const char *tzMenuUser[] =
{
	"Display",
	"Printer",
	"Keyboard",
	"Magnetic",
	"Smart",
	"Communication",
	"VFS",
	"Buzzer",
	"Backlight",
	"Power Failure",
	"RealTime",
	"File System",
	"Library",
	"Schemes",
	"Graphic",
	"IAC",
	"IAM",
	"Input",
	"Font",
	"Message",
	"Terminal",
	"Software Reset",
	NULL
};

static const char *tzMenuCom[] =
{
	"ComSerial",
	"ComModem",
	"ComUSB",
	"ComEthernet",
	"ComGPRS",
	"ComPPP",
	NULL
};

static const char *tzMenuParams[] =
{
	"Parameters",
	"Run",
	NULL
};

static const char *tzMenuVFSType[] =
{
	"USB Key",
	"MMC Card",
	NULL
};

static const char *tzMenuVFSProcess[] =
{
	"Write",
	"Read",
	"Delete",
	NULL
};

static const char *tzPowerFailure[]=
{
	"Write Msg1 in RAM",
	"Write Msg2 in RAM",
	"Read Msg from RAM",
	NULL
};

static const char *tzMenuRealTime[]=
{
	"Task",
	"Delay",
	"Timer",
	NULL
};

static const char *tzMenuFileSystem[]=
{
	"FFMS",
	"FMG",
	NULL
};

static const char *tzMenuFFMS[] =
{
	"Disk Create",
	"File Write",
	"File Read",
	"Disk Use",
	"Disk Kill",
	NULL
};

static const char *tzMenuFMG[] =
{
	"Create Batch",
	"AddDel Transactions",
	"Read Transactions",
	"Delete Batch",
	NULL
};

static const char *tzMenuLibrary[]=
{
	"Beep DLL",
	"Beep LIB",
	NULL
};

static const char *tzMenuScheme[] =
{
	"Set Secure Config.",
	"Get Secure Config.",
    "Create Secret Area",
	"Free Secret Area",
	"Load Iso9564 Key",
	"Iso9564 Pin Entry",
	"Load Mac Key",
	"Mac Calculation",
	NULL
};

static const char *tzMenuGraphic[] =
{
	"Draw",
    "Image",
    "Animated",
    NULL
};

static const char *tzMenuIAM[] =
{
	"Training to User2",
	"Training to All",
	"Training to Itself",
	"Training to Task",
	NULL
};

static const char *tzMenuFont[] =
{
	"Encoding ISO-8859",
	"Encoding UTF-8",
	NULL
};

static const char *tzMenuISO8859[] =
{
	"Candara",
	"German",
	"Polish",
	"Turkish",
	"Russian",
	"Arabic",
	"Greek",
	NULL
};

static const char *tzMenuMsg[] =
{
	"Display message",
	"Language selection",
	"Testing",
	NULL
};

static const char *tzMenuTerm[] =
{
	"Configuration",
	"Diagnostic",
	NULL
};

static const char *tzMenuConf[] =
{
	"Flash",
	"Hardware",
	"Software",
	NULL
};

static const char *tzMenuLink[] =
{
	"RS232  (115200)",
	"USB",
	"USB->RS232  (115200)",
	NULL
};

static const char *tzMenuDiag[] =
{
	"Print  (APPTEXT.DIA)",
	"Reset  (APPTEXT.DIA)",
	NULL
};

// ***************************************************************************
//   int give_your_domain(NO_SEGMENT no, void *p1, S_INITPARAMOUT *param_out)
/** Ask application to define its working environment, Manager will select 
 *  common parameters set and adapt its internal processing.
 * \param    param_out (-O) 
 *    - application_type :   
 *      TYP_CARTE (French Bank), TYP_HEALTH(French Health), TYP_EXPORT (Export)
 *    - mask : Key "F" 031 -> Parameters initialization MASK (0:absent, 1:present)
 *                              MSK_NULL / MSK_ALL_PARAM
 *                            On multi-applications environment:
 *                            Mask result = Mask App1 | Mask App2 | Mask AppN 
 *    - response_number : should be incremented
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int give_your_domain(NO_SEGMENT no, void *p1, S_INITPARAMOUT *param_out)
{
	// Local variables *
    // *****************
       // Empty

    // Return application domain to Manager
    // ************************************
	// Setting parameters initialization
    param_out->returned_state[param_out->response_number].mask = MSK_ALL_PARAM; // Accept all

    /* TeliumManager-Initialization-Parameters
    &
    ~MSK_FRMT_DATE &   // Will reject Date format update
    ~MSK_DATE &        // Will reject date and time update
    ~MSK_LANGUE &      // Will reject language update
    ~MSK_NO_TERM &     // Will reject terminal number update
    ~MSK_MONNAIE &     // Will reject currency update
    ~MSK_STANDARD &    // Will reject pabx update
    ~MSK_PINPAD &      // Will reject pinpad update
    ~MSK_SWIPE &       // Will reject swipe update
    ~MSK_NO_SERIE &    // Will reject serial number update
    ~MSK_TYPE_RESEAU & // Will reject network access update
    ~MSK_CAISSE &      // Will reject cash connection update
    ~MSK_MDP;          // Will reject T.M.S update
    */

    // International domain
	param_out->returned_state[param_out->response_number].application_type = TYP_EXPORT;
	param_out->response_number++;
	
	return (FCT_OK);
}

// ***************************************************************************
//   int give_your_specific_context(NO_SEGMENT no, void *p1, S_SPECIFIC_CONTEXT *param_out)
/** Ask application to define its specific context to be used for application
 *  selection using swipe Iso2+Iso1, Iso2+Iso3 or Iso1+Iso2+Iso3.
 *  Return TRACK1_SUPPORT_MASK, TRACK2_SUPPORT_MASK and TRACK3_SUPPORT_MASK to get the
 *  entries point IS_FOR_YOU_BEFORE and IS_FOR_YOU_AFTER called. Otherwise DEBIT_NONE_EMV is
 *  called directly on a polling mode (old way for selection).
 * \param    param_out (-O)
 *    - support :  TRACK1_SUPPORT_MASK | TRACK2_SUPPORT_MASK | TRACK3_SUPPORT_MASK
 *                            On multi-applications environment:
 *                            Mask result = Mask App1 | Mask App2 | Mask AppN
 *    - response_number : should be incremented
 * \return
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c
*/
// ***************************************************************************
int give_your_specific_context(NO_SEGMENT no, void *p1, S_SPECIFIC_CONTEXT *param_out)
{
	// Local variables *
    // *****************
       // Empty

    // Return specific context to Manager
    // **********************************
	// Support field
	param_out->returned_state[param_out->response_number].support = TRACK1_SUPPORT_MASK | TRACK2_SUPPORT_MASK | TRACK3_SUPPORT_MASK;
	param_out->response_number++;

	return (FCT_OK);
}

// ***********************************************************
// Task to manage IAM process (See after_reset() service call)
// ***********************************************************
static word Task2(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	ST_DSP_LINE xDspLine;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xPrnLine;
	FILE *pxDsp=NULL, *pxPrn=NULL;
    char tcSnd[256];
	char tcPrint[256+1];
    byte p;  // Printer line index
    int iRet;
  
    // Assign a mailbox to this task
	// *****************************
    Register_Mailbox_User(TaskIam1);

    // Send a event to Main task 
	// *************************
    SignalEvent(usMainTaskNbr, EVT_SYNCHRO_DIALOG);                    // Signal to main task that task2 is initialized

    // Wait for incoming message
	// *************************
	while(1)
    {
        ttestall(MSG, 0);                                              // Wait until messages received

        while (1)
        {
        	iRet = Read_Message(&xMessage, 0);                         // Read until no more message

        	if (iRet==0)                                               // Exit from the loop and wait for next messages
        		break;

        	switch (xMessage.type)
        	{
        	case 0:                                                    // *** Dialog between task and Training application ***
        		pxDsp = stdperif("DISPLAY", NULL);                     // Check "display" peripheral already opened? (done by Manager)
        		if (pxDsp == NULL)                                     // No, then open it
        			pxDsp = fopen("DISPLAY", "w*");                    // Open "display" peripheral

        		if (pxDsp != NULL)
        		{
        			// Get message received from TRAINING
        			// ==================================
        			xScreen = GoalCreateScreen(xGoal, txScreen, NUMBER_OF_LINES(txScreen), GL_ENCODING_UTF8);
        			GoalClrScreen(xScreen, GL_COLOR_BLACK, 0, false);  // Create and clear screen

        			xDspLine = txScreen[0];                            // Build screen and show it (IAM info, IAM message)
        			xDspLine.xColor.eTextAlign = GL_ALIGN_CENTER;
        			xDspLine.xColor.ulPen = GL_COLOR_YELLOW;
        			xDspLine.xBW.eTextAlign = GL_ALIGN_CENTER;
        			GoalDspLine(xScreen, 0, "TASK2 (Msg from TRAIN)", &xDspLine, 0, false);
        			GoalDspMultiLine(xScreen, 1, (char*)xMessage.value, xMessage.length, txScreen, NUMBER_OF_LINES(txScreen), 0, true);

        			pxPrn = fopen("PRINTER", "w-*");                   // Open "printer" peripheral
        			if (pxPrn != NULL)
        			{
        				p=0;                                           // Create document
        				xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);

        				xPrnLine = xPrinter;                           // Build document (Task2, IAM info, Sender/Receiver, IAM type, IAM message)
        				xPrnLine.eTextAlign = GL_ALIGN_CENTER;
        				xPrnLine.xFont.eScale = GL_SCALE_XXLARGE;
        				GoalPrnLine(xDocument, p++, "TASK2", &xPrnLine);
        				xPrnLine.eTextAlign = GL_ALIGN_LEFT;
        				xPrnLine.xFont.eScale = GL_SCALE_LARGE;
        				GoalPrnLine(xDocument, p++, "Message IAM from Appli:", &xPrnLine);
        				sprintf(tcPrint, "S:%04X R:%04X", xMessage.sender, xMessage.receiver);
        				GoalPrnLine(xDocument, p++, tcPrint, &xPrnLine);
        				sprintf(tcPrint, "IAM Type : %04X\n\n", xMessage.type);
        				GoalPrnLine(xDocument, p++, tcPrint, &xPrnLine);
        				GoalPrnLine(xDocument, p++, "Msg from TRAINING:", &xPrnLine);
        				strncpy(tcPrint, (char*)xMessage.value, xMessage.length);
        				GoalPrnLine(xDocument, p++, tcPrint, &xPrnLine);
        				GoalPrnLine(xDocument, p++, "\n", &xPrnLine);
        				GoalPrnDocument(xDocument);                    // Print document

        				if (xDocument)
        					GoalDestroyDocument(&xDocument);           // Destroy document

        				fclose(pxPrn);                                 // Close "printer" peripheral
        			}

        			ttestall(0, 2*100);                                // Wait to see the message in synchronization with TrainingToTask()
        			// Send back message to TRAINING
        			// =============================
        			memset (tcSnd, 0, sizeof(tcSnd));
        			strcpy(tcSnd, "Hi, how are you doing?\n"           // Data to send
        				          "Hi, how are you doing?\n"
        					      "Hi, how are you doing?\n"
        					      "Hi, how are you doing?");
                                                                       // Send message
        			SendToApplication(TRAINING_APPLI_TYPE, 1, strlen(tcSnd), (byte*)tcSnd);

        			if (xScreen)
        				GoalDestroyScreen(&xScreen);                   // Destroy screen

        			fclose(pxDsp);                                     // Close "display" peripheral
        		}
        		break;
        	default:
        		break;
        	}
        }
    }

	return 0;
}

// *****************************************************
// Progress bar counter (See after_reset() service call)
// *****************************************************
static T_GL_COORD Progress(T_GL_COORD sValue) // This function is called periodically to update the progress bar of the dialog box.
{                                             // The value received as parameter corresponds to the current value of the progress bar.
	ttestall(0, 2);                           // When this value reaches the maximum, the dialog is automatically closed.

	return sValue+1;
}

// ***************************************************************************
//      int after_reset(NO_SEGMENT no, void *p1, S_TRANSOUT *param_out)
/** Initialize data and create disks, eventually ends interrupted transaction
 *  by returning S_TRANS_OUT.
 * \param    param_out (-O) Eventually ends interrupted transaction
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int after_reset(NO_SEGMENT no, void *p1, S_TRANSOUT *param_out)
{
	// Local variables *
    // *****************
	char tcAppDat[lenCmpDat+1], tcAppTim[lenCmpTim+1];
	char tcPath[100];
    byte ucNew, ucType;
    doubleword uiMode;  // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
                        // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
    T_GL_COORD sValue;
    t_topstack *hTsk=NULL;
	byte ucDum1;
	int iDum2=0;
	int i, iRet;

	// Initialization
	// **************
	pxDsp = stdperif("DISPLAY", NULL);    // Check "display" peripheral already opened? (done by Manager)
	if (pxDsp == NULL)                    // No, then open it
	{
		pxDsp = fopen("DISPLAY", "w*");   // Open "display" peripheral
		CHECK(pxDsp!=NULL, lblKO);
	}

	// Check if Cold or Warm reset
	// ===========================
	first_init(no, &ucNew, &ucType);      // NEW SOFTWARE LOADED ?
	if (ucNew == 0xFF)                    // YES, just loaded with first execution
	{
		GL_Dialog_Message(xGoal, NULL, (char*) zColdReset, GL_ICON_INFORMATION, GL_BUTTON_NONE, 2*1000);
        raz_init(no);                     // Reset indicator downloading
	}
	else                                  // NO, already loaded and executed
		GL_Dialog_Message(xGoal, NULL, (char*) zWarmReset, GL_ICON_INFORMATION, GL_BUTTON_NONE, 2*1000);

	// Create backup memory
	// ====================
	memset(tcPowerFailure, 0, sizeof(tcPowerFailure));
	iRet = RegisterPowerFailure("E_TRAINING", (byte*) tcPowerFailure, sizeof(tcPowerFailure));
	if (iRet == FM_SAVE_DATA_PRESENT)
		buzzer(5);                        // Data from FLASH to RAM successfully restored

	// Check if pictures are present in HOST for animation
	// ===================================================
	iRet = FS_mount ("/HOST", &uiMode);   // Disk HOST initialization
	if (iRet == FS_OK)
	{
		for (i=0; i<11; i++)
		{
			if (IsColorDisplay())         // Color terminal?
				sprintf(tcPath, "/HOST/CCARDT%d.JPG", i);  // Yes, check if JPG present
			else
				sprintf(tcPath, "/HOST/BWCARDT%d.BMP", i); // No, check if BMP present
			iRet = FS_exist(tcPath);                       // Picture present?
			if (iRet == FS_OK)
				bPictureOk=true;                           // Yes, set the flag to yes
			else
			{
				bPictureOk=false;                          // No, set the flag to no
				break;                                     // and exit
			}
	    }
		FS_unmount("/HOST");              // Disk HOST deactivation
	}

	// Create Parameter Disk (See Mapapp.c)
	// ====================================
	// ** Parameters Disk used by FMG library ** 
	strcpy(xCfg.Label, PARAM_DISK);       // Disk name
    xCfg.Mode = FS_WRITEONCE;             // Disk on Flash
	xCfg.AccessMode	= FS_WRTMOD;          // r/w access                   
	xCfg.NbFichierMax = 1;                // Max files number
	xCfg.IdentZone	= FS_WO_ZONE_DATA;    // Zone id 
	ulSize = xCfg.NbFichierMax*32768;     // Disk size in bytes
    
	// ** All disks created by FFMS and used by FMG library must be mounted before the call to FMG_init() **
	sprintf(tcPath, "/%s", PARAM_DISK);
	iRet = FS_mount (tcPath, &uiMode);    // Check if disk already activated (!!! second parameter returns (FS_WRITEONCE or FS_WRITEMANY))
    if (iRet != FS_OK)
    {
    	// == Application added ==
    	iRet = FS_dskcreate(&xCfg, &ulSize);  // Create and format the none volatile disk
    	CHECK(iRet==FS_OK, lblKO);
        iRet = FS_mount(tcPath, &uiMode);     // Activate a disk (!!! second parameter returns (FS_WRITEONCE or FS_WRITEMANY))
        CHECK(iRet==FS_OK, lblKO);
        iRet = FMG_Init();                    // Initialize File ManaGement
        CHECK(iRet==FMG_SUCCESS, lblKO);

        iRet = appReset();                    // Reset application parameters (Flash)
        CHECK(iRet>=0, lblKO);

		iRet = appPut(appCmpDat, (char*)getAppCmpDat(), lenCmpDat);  // Store compiler date/time (See Mapapp.c)
		CHECK(iRet>=0, lblKO);
	    iRet = appPut(appCmpTim, (char*)getAppCmpTim(), lenCmpTim);
	    CHECK(iRet>=0, lblKO);

	    GL_Dialog_Progress(xGoal, NULL, "New Software\nReset In Progress",
	    		           NULL, NULL, 0, 100, Progress, GL_BUTTON_NONE, GL_TIME_INFINITE);
	    sValue = 100;
	    GL_Dialog_Progress(xGoal, NULL, "New Software\nReset Done",
	    		           NULL, &sValue, 1, 101, NULL, GL_BUTTON_NONE, 3*1000);
    }
    else
    {
    	iRet = FMG_Init();                                // Initialize File ManaGement
    	CHECK(iRet==FMG_INIT_OK, lblKO);

    	iRet = appGet(appCmpDat, tcAppDat, lenCmpDat+1);  // Retrieve compiler date/time (See Mapapp.c)
    	CHECK(iRet>=0, lblKO);
    	iRet = appGet(appCmpTim, tcAppTim, lenCmpTim+1);
    	CHECK(iRet>=0, lblKO);
                                                          // Check compiler date/time
    	if( (strcmp(tcAppDat, getAppCmpDat()) == 0) && (strcmp(tcAppTim, getAppCmpTim()) == 0))
    	{
    		// == Application already upto date ==
    	}
        else
        {
        	// == Application updated ==
            if ((strcmp(tcAppDat, getAppCmpDat()) != 0) || (strcmp(tcAppTim, getAppCmpTim()) != 0))
            {
            	iRet = appReset();                        // Reset application parameters (Flash)
            	CHECK(iRet>=0, lblKO);
            }

    		iRet = appPut(appCmpDat, (char*)getAppCmpDat(), lenCmpDat); // Store compiler date/time (See Mapapp.c)
    		CHECK(iRet>=0, lblKO);
    	    iRet = appPut(appCmpTim, (char*)getAppCmpTim(), lenCmpTim);
    	    CHECK(iRet>=0, lblKO);

    	    GL_Dialog_Progress(xGoal, NULL, "Update Software\nUpdate In Progress",
    	    		           NULL, NULL, 0, 100, Progress, GL_BUTTON_NONE, GL_TIME_INFINITE);
    	    sValue = 100;
    	    GL_Dialog_Progress(xGoal, NULL, "Update Software\nUpdate Done",
    	    		           NULL, &sValue, 1, 101, NULL, GL_BUTTON_NONE, 3*1000);
        }
    }

	// Fork a task used for IAM 
	// ************************	
    usMainTaskNbr = CurrentTask();        // Retrieve main task number
	hTsk = fork(Task2, &ucDum1, iDum2);   // Fork second task
	ttestall(SYNCHRO_DIALOG, 0);          // Wait until second task started (Synchronization)

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:
	iRet = appReset();                    // Reset one more time
	if (iRet>=0)                          // Memory OK
	{
		appPut(appCmpDat, (char*)getAppCmpDat(), lenCmpDat); // Store compiler date/time (See Mapapp.c)
	    appPut(appCmpTim, (char*)getAppCmpTim(), lenCmpTim);

	    GL_Dialog_Progress(xGoal, NULL, "Initialization\nReset In Progress",
	    		           NULL, NULL, 0, 100, Progress, GL_BUTTON_NONE, GL_TIME_INFINITE);
	    sValue = 100;
	    GL_Dialog_Progress(xGoal, NULL, "Initialization\nReset Done",
	    		           NULL, &sValue, 1, 101, NULL, GL_BUTTON_NONE, 3*1000);
	}
	else                                  // Memory problem => Terminal problem
		GL_Dialog_Message(xGoal, NULL, "Processing Error\nMemory Failed", GL_ICON_ERROR, GL_BUTTON_NONE, 5*1000);
lblEnd:
	if(pxDsp)
	{
		fclose(pxDsp);                    // Close "display" peripheral
		pxDsp=NULL;
	}

	return FCT_OK;
}

// ***************************************************************************
//        int is_name(NO_SEGMENT no, void *p1, S_ETATOUT *param_out)
/** Report application name to Manager.
 * \param    param_out (-O)
 *    - appname : Application name 
 *    - no : Application number
 *    - response_number : should be incremented
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int is_name(NO_SEGMENT no, void *p1, S_ETATOUT *param_out)
{
	// Local variables *
    // *****************
	   // Empty
	
	// Return application name
	// ***********************
	strcpy(param_out->returned_state[param_out->response_number].appname, zAppName);
	param_out->returned_state[param_out->response_number].no_appli = no;
	param_out->response_number++;

	return (FCT_OK);
}

// ***************************************************************************
//      int is_state(NO_SEGMENT no, void *p1, S_ETATOUT *param_out)
/** Report application state initialize or not to Manager.
 * \param    param_out (-O)
 *    - response : 
 *      REP_OK (Initialized), REP_KO (Not initialized)
 *    On multi-applications environment all applications should return REP_KO
 *    to get the message INITIALIZE AN APPLICATION on screen.
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int is_state(NO_SEGMENT no, void *p1, S_ETATOUT *param_out)
{
	// Local variables *
    // *****************
	int iRet; 

	// Return application state
	// ************************
	param_out->returned_state[param_out->response_number].state.response = REP_OK;
	iRet = is_name (no, PT_NULL, param_out);
	
	return iRet;
}

// ***************************************************************************
//          int idle_message(NO_SEGMENT no, void *p1, void *p2)
/** Allows the application to display its idle message when Manager goes back 
 *  to idle (the application should have the higher priority).
 *  In term of conflict, Manager displays its own idle message.
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int idle_message (NO_SEGMENT no, void *p1, void *p2)
{
	// Local variables *
    // *****************
	static T_GL_HWIDGET xScreen=NULL;
	T_GL_HWIDGET xPicture=NULL;
	DATE xDate;
	char tcDisplay[100];
	char tcPath[100];
    char tcDate[10+1];
    char tcTime[5+1];
    word  usCt;

	// Idle message management
	// ***********************	
	pxDsp = stdperif("DISPLAY", NULL);                                       // Check "display" peripheral already opened? (done by Manager)
	if (pxDsp == NULL)                                                       // No, then open it
		pxDsp = fopen("DISPLAY", "w*");                                      // Open "display" peripheral

	if (pxDsp != NULL)
	{
		read_date (&xDate);                                                  // Read terminal Date&Time
		sprintf (tcDate, "%2.2s/%2.2s/20%2.2s",                              // Retrieve date
					     xDate.day, xDate.month, xDate.year);
		sprintf (tcTime, "%2.2s:%2.2s",                                      // Retrieve time
			          	 xDate.hour, xDate.minute);

		if (ANIMATION & bPictureOk)
		{                                                                    // *** Show card animation idle screen ***
			xPicture = GoalCreatePicture(xGoal);                             // Create and clear screen
			GoalClrPicture(xPicture, GL_COLOR_BLACK, 0, false);

			usCt=0;
			do {
				if (usCt==0)                                                 // When counter==0, change image to display
				{
					if (IsColorDisplay())
						sprintf(tcPath, "file://flash/HOST/CCARDT%d.JPG", tcIdxImg[usIdxImg]);
					else
						sprintf(tcPath, "file://flash/HOST/BWCARDT%d.BMP", tcIdxImg[usIdxImg]);
					if (IsHeader()==0)                                       // No header (show Date&Time on user screen)
					{
						sprintf(tcDisplay, "%s        %s", tcDate, tcTime);
						GoalDspPicture(xPicture, tcDisplay, tcPath, &xImage, 0, true);
					}
					else
						GoalDspPicture(xPicture, NULL, tcPath, &xImage, 0, true);

					usIdxImg++; if(usIdxImg==MAX_IMG) usIdxImg=0;            // Last image, move to first image
				}
				usCt++;                                                      // Count until time to change image
				if (ttestall(TIMER, 1) == TIMER)
				{
					if (xPicture)
						GoalDestroyPicture(&xPicture);                       // Destroy screen
					break;                                                   // if TIMER event (All other events), exit from IDLE_MESSAGE to start the service call
				}

				if (usCt==usTimeout) usCt=0;                                 // Time to change image => counter=0
			} while(1);
		}
		else
		{                                                                    // *** Show message idle screen ***
			if (xScreen)
				GoalDestroyScreen(&xScreen);                                 // Destroy previous screen if already exist (to avoid memory leak)
			xScreen = GoalCreateScreen(xGoal, txIdle, NUMBER_OF_LINES(txIdle), GL_ENCODING_UTF8);
			GoalClrScreen(xScreen, GL_COLOR_BLACK, 0, false);                // Create and clear screen

			if (IsHeader()==0)                                               // No header (show Date&Time on user screen)
			{
				sprintf(tcDisplay, "%s        %s", tcDate, tcTime);
				GoalDspLine(xScreen, 0, tcDisplay, &txIdle[0], 0, false);
			}
			else
				GoalDspLine(xScreen, 0, (char*) NULL, &txIdle[0], 0, false);

			GoalDspLine(xScreen, 1, (char*) zAppName, &txIdle[1], 0, false); // Show application name & message,
			GoalDspLine(xScreen, 2, (char*) zIdleMsg, &txIdle[2], 0, true);  // Do not destroy screen here, otherwise Manager will overwrite part of the idle screen
		}

		fclose(pxDsp);                                                       // Close "display" peripheral
        pxDsp=NULL;
	}

	return FCT_OK;
}

// ***************************************************************************
//          int more_function(NO_SEGMENT no, void *p1, void *p2)
/** It's activated when pressing on "F" key to select the right application 
 *  to go on menu.
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int more_function( NO_SEGMENT no, void *p1, void *p2 )
{
	// Local variables *
    // *****************
	bool bContinue=TRUE, bContinue2=TRUE;
	int iHeader, iFooter;
	int iRet;

	// Open peripherals
	// ****************
	iHeader = IsHeader();       // Save header state
	iFooter = IsFooter();       // Save footer state

	if (!IsColorDisplay())      // B&W terminal?
	{                           // Yes
		DisplayLeds(_OFF_);     // Disable Leds
		DisplayHeader(_OFF_);   // Disable Header
		DisplayFooter(_OFF_);   // Disable Footer
	}

	iRet = OpenPeripherals();   // Open standard peripherals
	CHECK(iRet>=0, lblKO);

	iRet = GetPpdDisplay();     // Get pinpad type
	CHECK(iRet>=0, lblKO);
    if (iRet == 1)              // Pinpad with character display
    {
    	PPS_firstline();        // Display pinpad idle message
    	PPS_Display("    WELCOME     ");                                                            
    }

    // Menu management
	// ***************
	do
	{
		switch (GL_Dialog_Menu(xGoal, "Main Menu", tzMenuUser, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
		{
		case 0: Display();   break; // Demo Display
		case 1: Printer();   break; // Demo Printer
		case 2: Keyboard();  break; // Demo keyboard
		case 3: Magnetic();  break; // Demo magnetic
        case 4: Smart();     break; // Demo smart
        case 5:
			do
			{
				switch (iRet=GL_Dialog_Menu(xGoal, tzMenuUser[5], tzMenuCom, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
				{
				case 0:  
					do
					{
						switch (iRet=GL_Dialog_Menu(xGoal, tzMenuCom[0], tzMenuParams, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
						{
						case 0:  PromptSerial();           break; // Serial parameters
						case 1:  ComSerial();              break; // Demo serial COM0/COM1/COM2/COM_EXT
						default: bContinue2=FALSE;         break; // Abort/Timeout
						}						
					} while (bContinue2);
					bContinue2=TRUE;
					CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
					break;
				case 1:  
					do
					{
						switch (iRet=GL_Dialog_Menu(xGoal, tzMenuCom[1], tzMenuParams, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
						{
						case 0:  PromptModem();            break; // Modem parameters
						case 1:  ComModem();               break; // Demo Modem
						default: bContinue2=FALSE;         break; // Abort/Timeout
						}						
					} while (bContinue2);
					bContinue2=TRUE;
					CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
					break;
				case 2:  ComUSB();                         break; // Demo USB
				case 3:  
					do
					{
						switch (iRet=GL_Dialog_Menu(xGoal, tzMenuCom[3], tzMenuParams, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
						{
						case 0:  PromptEthernet();         break; // Ethernet parameters
						case 1:  ComEthernet();            break; // Demo Ethernet
						default: bContinue2=FALSE;         break; // Abort/Timeout
						}
					} while (bContinue2);
					bContinue2=TRUE;
					CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
					break;
				case 4:  
					do
					{
						switch (iRet=GL_Dialog_Menu(xGoal, tzMenuCom[4], tzMenuParams, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
						{
						case 0:  PromptGPRS();             break; // GPRS parameters
						case 1:  ComGPRS();                break; // Demo GPRS
						default: bContinue2=FALSE;         break; // Abort/Timeout
						}
					} while (bContinue2);
					bContinue2=TRUE;
					CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
					break;
				case 5:
					do
					{
						switch (iRet=GL_Dialog_Menu(xGoal, tzMenuCom[5], tzMenuParams, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
						{
						case 0:  PromptPPP();              break; // PPP parameters
						case 1:  ComPPP();                 break; // Demo PPP
						default: bContinue2=FALSE;         break; // Abort/Timeout
						}
					} while (bContinue2);
					bContinue2=TRUE;
					CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
					break;
                default: bContinue2=FALSE;                 break; // Abort/Timeout
				}
			} while (bContinue2);
			bContinue2=TRUE;
			CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
			break;
        case 6: 
        	do
        	{
        		switch (iRet=GL_Dialog_Menu(xGoal, tzMenuUser[6], tzMenuVFSType, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
        		{
        		case 0:
        			do
        			{
        				switch (iRet=GL_Dialog_Menu(xGoal, tzMenuVFSType[0], tzMenuVFSProcess, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
        				{
        				case 0:  VFSWrite(TYPE_USB);       break; // Write file into USB key 
	        		    case 1:  VFSRead(TYPE_USB);        break; // Read file from USB key
	        		    case 2:  VFSDelete(TYPE_USB);      break; // Delete file from USB key
					    default: bContinue2=FALSE;         break; // Abort/Timeout
        		        }
        			} while (bContinue2);
        			bContinue2=TRUE;
        			CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
					break;
				case 1:    
					do
					{
						switch (iRet=GL_Dialog_Menu(xGoal, tzMenuVFSType[1], tzMenuVFSProcess, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
						{
						case 0:  VFSWrite(TYPE_MMC);       break; // Write file into USB key 
	        		    case 1:  VFSRead(TYPE_MMC);        break; // Read file from USB key
	        		    case 2:  VFSDelete(TYPE_MMC);      break; // Delete file from USB key
					    default: bContinue2=FALSE;         break; // Abort/Timeout
        		        }
					} while (bContinue2);
					bContinue2=TRUE;
					CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
					break;
        		default: bContinue2=FALSE;                 break; // Abort/Timeout
        		}
        	} while (bContinue2);
        	bContinue2=TRUE;
        	CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
        	break;
        case 7: Buzzer();    break; // Demo Buzzer
        case 8: Backlight(); break; // Demo Backlight
        case 9:
        	do
        	{
        		switch (iRet=GL_Dialog_Menu(xGoal, tzMenuUser[9], tzPowerFailure, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
        		{
        		case 0:  WriteInRam(1);          break; // Write Msg1 in RAM
        		case 1:  WriteInRam(2);          break; // Write Msg2 in RAM
        		case 2:  ReadFromRam();          break; // Read Msg from RAM
        		default: bContinue2=FALSE;       break; // Abort/Timeout
        		}
        	} while (bContinue2);
        	bContinue2=TRUE;
        	CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
        	break;
        case 10:
        	do
        	{
        		switch (iRet=GL_Dialog_Menu(xGoal, tzMenuUser[10], tzMenuRealTime, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
        		{
        		case 0:  Task();                 break; // Demo Task  
        		case 1:  Delay();                break; // Demo Delay
        		case 2:  Timer();                break; // Demo Timer
        		default: bContinue2=FALSE;       break; // Abort/Timeout
        		}
        	} while (bContinue2);
        	bContinue2=TRUE;
        	CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
        	break;
        case 11:
        	do
        	{
        		switch (iRet=GL_Dialog_Menu(xGoal, tzMenuUser[11], tzMenuFileSystem, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
        		{
        		case 0:
        			do
        			{
        				switch (iRet=GL_Dialog_Menu(xGoal, tzMenuFileSystem[0], tzMenuFFMS, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
        				{
        				case 0:  DiskCreate();             break; // FFMS create disk
        				case 1:  FileWrite();              break; // FFMS write into file
    				    case 2:  FileRead();               break; // FFMS read from file
    				    case 3:  DiskUse();                break; // FFMS use space from disk
    				    case 4:  DiskKill();               break; // FFMS kill disk
    				    default: bContinue2=FALSE;         break; // Abort/Timeout
        				}
    				} while (bContinue2);
        			bContinue2=TRUE;
        			CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
					break;
				case 1:
					do
					{
						switch (iRet=GL_Dialog_Menu(xGoal, tzMenuFileSystem[1], tzMenuFMG, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
						{
						case 0:  FMGCreateBatch();         break; // FMG create Batch
    				    case 1:  FMGAddDelTransactions();  break; // FMG Add or Delete transactions
    				    case 2:  FMGReadTransactions();    break; // FMG Read transactions
						case 3:  FMGDeleteBatch();         break; // FMG delete Batch
    				    default: bContinue2=FALSE;         break; // Abort/Timeout
						}
    				} while (bContinue2);
					bContinue2=TRUE;
					CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
					break;
        		default: bContinue2=FALSE;       break; // Abort/Timeout
        		}
        	} while (bContinue2);
        	bContinue2=TRUE;
        	CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
        	break;
        case 12:
			do
			{
				switch (iRet=GL_Dialog_Menu(xGoal, tzMenuUser[12], tzMenuLibrary, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
				{
				case 0:  BeepDll();              break; // Demo DLL (Dynamic)
				case 1:  BeepLib();              break; // Demo LIB (Static)
				default: bContinue2=FALSE;       break; // Abort/Timeout
				}
			} while (bContinue2);
			bContinue2=TRUE;
			CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
	        break;
        case 13:
			do
			{
				switch (iRet=GL_Dialog_Menu(xGoal, tzMenuUser[13], tzMenuScheme, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
				{
				case 0:  SetConfig();            break; // Set security configuration
				case 1:  GetConfig();            break; // Get security configuration
				case 2:  CreateSecret();         break; // Create a secret area
				case 3:  FreeSecret();           break; // Erase a secret area
				case 4:  LoadIso9564Key();       break; // Load Iso9564 key
				case 5:  Iso9564PinEntry();      break; // Enter pin and pinblock calculation
                case 6:  LoadMacKey();           break; // Load Mac key 
				case 7:  MacCalculation();       break; // Mac calculation
				default: bContinue2=FALSE;       break; // Abort/Timeout
				}
			} while (bContinue2);
			bContinue2=TRUE;
			CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
	        break;
        case 14:
			do
			{
				switch (iRet=GL_Dialog_Menu(xGoal, tzMenuUser[14], tzMenuGraphic, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
				{
				case 0:  Draw();                 break; // Demo drawing
				case 1:  Image();                break; // Demo JPG or BMP
				case 2:  Animated();             break; // Demo animated GIF
				default: bContinue2=FALSE;       break; // Abort/Timeout
				}
			} while (bContinue2);
			bContinue2=TRUE;
			CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
	        break;
		case 15: IacCallUser2();   break; // Demo IAC
		case 16:
			switch (GL_Dialog_Menu(xGoal, tzMenuUser[16], tzMenuIAM, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
			{
			case 0:  TrainingToUser2();          break; // Demo Iam to User2
			case 1:  TrainingToAll();            break; // Demo Iam to All
		    case 2:  TrainingToItself();         break; // Demo Iam to Itself
			case 3:  TrainingToTask();           break; // Demo Iam to Task 
			default:                             break; // Abort/Timeout
			}
			bContinue=FALSE;                            // Return to Manager
			break;
		case 17: DemoEntry();      break; // Demo navigation and data entry
		case 18:
			do
			{
				switch (iRet=GL_Dialog_Menu(xGoal, tzMenuUser[18], tzMenuFont, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
				{
				case 0:                                // Demo ISO8859 font
					do
					{
						switch (iRet=GL_Dialog_Menu(xGoal, tzMenuFont[0], tzMenuISO8859, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
						{
						case 0:  Candara();              break; // Demo Candara font
						case 1:  German();               break; // Demo German font
						case 2:  Polish();               break; // Demo Polish font
						case 3:  Turkish();              break; // Demo Turkish font
						case 4:  Russian();              break; // Demo Russian font
						case 5:  Arabic();               break; // Demo Arabic font
						case 6:  Greek();                break; // Demo Greek font
						default: bContinue2=FALSE;       break; // Abort/Timeout
						}
					} while(bContinue2);
					bContinue2=TRUE;
					CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
					break;
				case 1:  FontUtf8();             break; // Demo UTF-8 font
				default: bContinue2=FALSE;       break; // Abort/Timeout
				}
			} while (bContinue2);
			bContinue2=TRUE;
			CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
			break;
        case 19:
			DefaultSettings();
			do
			{
				switch (iRet=GL_Dialog_Menu(xGoal, tzMenuUser[19], tzMenuMsg, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
				{
				case 0:  GetMsg();               break; // Display and print message 
				case 1:  SelectLang();           break; // Choose language
				case 2:  Testing();              break; // Testing message management
				default: bContinue2=FALSE;       break; // Abort/Timeout
				}
			} while (bContinue2);
			bContinue2=TRUE;
			CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
			break;
        case 20:
        	do
        	{
        		switch (iRet=GL_Dialog_Menu(xGoal, tzMenuUser[20], tzMenuTerm, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
        		{
        		case 0:
                	do
        			{
                		switch (iRet=GL_Dialog_Menu(xGoal, tzMenuTerm[0], tzMenuConf, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
        				{
                        case 0:
                        	switch (GL_Dialog_Menu(xGoal, tzMenuConf[0], tzMenuLink, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
        					{
        					case 0:  ConfFlash(COM0);          break; // Flash configuration RS232
            				case 1:  ConfFlash(COM5);          break; // Flash configuration USB
            				case 2:  ConfFlash(COM_EXT);       break; // Flash configuration USB->RS232
            				default:                           break; // Abort/Timeout
        					}
        					bContinue2=TRUE;
        					break;
        				case 1:
        					switch (GL_Dialog_Menu(xGoal, tzMenuConf[1], tzMenuLink, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
        					{
        					case 0:  ConfHardware(COM0);       break; // Hardware configuration RS232
            				case 1:  ConfHardware(COM5);       break; // Hardware configuration USB
            				case 2:  ConfHardware(COM_EXT);    break; // Hardware configuration USB->RS232
            				default:                           break; // Abort/Timeout
        					}
        					bContinue2=TRUE;
        					break;
        				case 2:
        					switch (GL_Dialog_Menu(xGoal, tzMenuConf[2], tzMenuLink, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
        					{
        					case 0:  ConfSoftware(COM0);       break; // Software configuration RS232
            				case 1:  ConfSoftware(COM5);       break; // Software configuration USB
            				case 2:  ConfSoftware(COM_EXT);    break; // Software configuration USB->RS232
            				default:                           break; // Abort/Timeout
        					}
            				bContinue2=TRUE;
        					break;
        				default: bContinue2=FALSE;             break; // Abort/Timeout
        				}
        			} while (bContinue2);
        			bContinue2=TRUE;
        			CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
					break;
				case 1:
					fclose(pxPrn);
					switch (GL_Dialog_Menu(xGoal, tzMenuTerm[1], tzMenuDiag, 0, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE))
        			{
                    case 0:  print_diagnostic(); break; // Print thunder diagnostic file APPTEXT.DIA
        			case 1:  reset_diagnostic(); break; // Reset thunder diagnostic file APPTEXT.DIA
        			default:                     break; // Abort/Timeout
        			}
                	pxPrn = fopen("PRINTER", "w-*");
                	CHECK(pxPrn!=NULL, lblKO);
        			bContinue2=TRUE;
					break;
        		default: bContinue2=FALSE; break; // Abort/Timeout
        		}
        	} while (bContinue2);
        	bContinue2=TRUE;
        	CHECK(iRet==GL_KEY_CORRECTION, lblEnd);
			break;
        case 21: SoftwareReset(); break;
		default: bContinue=FALSE; break;  // Abort/Timeout
		}
	} while(bContinue);

	goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                       // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	ClosePeripherals();      // Close standard peripherals

	DisplayLeds(_ON_);       // Enable Leds
	DisplayHeader(iHeader);  // Restore Header
	DisplayFooter(iFooter);  // Restore Footer

	return FCT_OK;
}

// ***************************************************************************
//        int keyboard_event(NO_SEGMENT no, S_KEY *key_in, SKEY *key_out)
/** It's activated when key is pressed and terminal is in idle mode. 
 * \param    key_in (I-)
 *    - keycode : Key pressed. 
 * \param    key_out (-O)
 *    - keycode : Key pressed, new key, 0=disable. 
 * ---------------------------------------------------------------------------
 *  case T_F :                   // Filter F key (Menu manager is disabled)
 *      key_out->keycode=0;         // On multi-applications environment, if an application disables
 *      break;                      // the F key, the treatment is done for all applications
 * 	case N0:                     // Key 0 will access the menu manager
 *      key_out->keycode=T_F;       // On multi-applications environment, if an application redirects
 *      break;	                    // the F key, the treatment is done for all applications
 * ---------------------------------------------------------------------------
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int keyboard_event(NO_SEGMENT noappli,S_KEY *key_in,S_KEY *key_out)
{
	// Local variables *
    // *****************
	   // Empty
		
	// Keyboard management
	// *******************
	switch (key_in->keycode)
	{
	case N0: case N1: case N2: case N3: case N4:
	case N5: case N6: case N7: case N8: case N9:
	case T_VAL: case T_POINT:
		key_out->keycode=key_in->keycode;  // Amount entry managed by Manager
		break; 
	case F1: case F2: case F3: case F4:
	case T_CORR: case T_ANN: case NAVI_CLEAR: case NAVI_OK:
	case UP: case DOWN:
		key_out->keycode=key_in->keycode;
		break;
	case T_F:                              // do not filter F key and return the same key !
		key_out->keycode=key_in->keycode;  // Return the same key value for keys above !
		break;
	default:
		key_out->keycode=key_in->keycode;
		break;
	}

	return FCT_OK;
}

// ***************************************************************************
//   int get_idle_state_parameter(NO_SEGMENT no, void *p1, S_STATEOUT *param_out)
/** Ask application to define peripherals accepted by the application in selection
 *  process (CAM0, SWIPE3, SWIPE2, SWIPE31 etc...) and to inhibit some keyboard
 *  functions.
 * \param    param_out (-O)
 *    - mask : CAM0 | SWIPE3 | SWIPE2 | SWIPE31 | etc...
 *    - key : INHIBIT_AMOUNT_ENTRY | INHIBIT_IDLE_MANUAL_ENTRY | INHIBIT_LAST_AMOUNT | etc...
 *            On multi-applications environment, if an application inhibits a treatment,
 *            the treatment is inhibited for all applications.
 *    - response_number : should be incremented

 * \return
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c
*/
// ***************************************************************************
int get_idle_state_parameter(NO_SEGMENT no, void *p1, S_STATEOUT *param_out)
{
	// Local variables *
    // *****************
       // Empty

    // Return idle configuration to Manager
    // ************************************
	// ** Support field to accept application selection **
	param_out->returned_state[param_out->response_number].no_appli = no;
	param_out->returned_state[param_out->response_number].mask = CAM0 | SWIPE3 | SWIPE2 | SWIPE31;
	// ** Inhibit some keyboard functions **
	if (AMOUNT_ENTRY)
		param_out->returned_state[param_out->response_number].key = INHIBIT_IDLE_MANUAL_ENTRY;
	else
		param_out->returned_state[param_out->response_number].key = INHIBIT_AMOUNT_ENTRY;
	param_out->response_number++;

	return (FCT_OK);
}

// ***************************************************************************
//   int give_money_extended(NO_SEGMENT no, void *p1, S_MONEYOUT_EXTENDED *param_out)
/** Get the currencies supported by the application.
 *  It's activated when currency table is updated by the Manager (after_reset,
 *  more_function, time function).
 * \param    param_out (-O)
 *    - money : Table of currency
 *    - nb_money : Number of currency.
 *    - nb_reponse : should be incremented
 * \return
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c
*/
// ***************************************************************************
int give_money_extended (NO_SEGMENT no, void *p1, S_MONEYOUT_EXTENDED *param_out)
{
	// Local variables *
    // *****************

	// Return currency table to Manager
	// ********************************
	strcpy(param_out->etat_retour[param_out->nb_reponse].libelle, zAppName);
	memcpy(param_out->etat_retour[param_out->nb_reponse].money, &txCurrency, sizeof(txCurrency));
	param_out->etat_retour[param_out->nb_reponse].nb_money = 5;
	param_out->nb_reponse++;

	return (FCT_OK);
}

// ***************************************************************************
//             int state(NO_SEGMENT no, void *p1, void *p2)
/** It's activated on "F" key: Consultation->State. 
 *  To print terminal content.  
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int state (NO_SEGMENT no, void *p1, void *p2)
{
	// Local variables *
    // *****************
	DATE xDate;
   	object_info_t xInfos;
	FILE *pxPrn;
	
	// Print application info
	// **********************
	ObjectGetInfo(OBJECT_TYPE_APPLI, no, &xInfos);   // Retrieve application info

	pxPrn = fopen("PRINTER", "w-*");                 // Open "printer" peripheral
	if (pxPrn != NULL) 
	{	
		pprintf("\x1b""E%s\n""\x1b""F", zAppName);   // Print application name
		pprintf("         STATE         \n"
			    "Application used during\n"
			    "SDK training session   \n"
				"Show many samples\n\n");
		read_date(&xDate);                           // Print date and time
		pprintf(zDate, xDate.day, xDate.month, xDate.year, xDate.hour, xDate.minute);
		pprintf("File    : %s\n", xInfos.file_name); // Print application file name
		pprintf("CRC     : %04x\n", xInfos.crc);     // Print application CRC
		ttestall(PRINTER, 1*100);	                 // Wait until the end of printing

		fclose(pxPrn);                               // Close "printer" peripheral
	}
	
	return FCT_OK;
}

// ***************************************************************************
//             int consult(NO_SEGMENT no, void *p1, void *p2)
/** It's activated on "F" key: Consultation->Transactions. 
 *  To print transactions total receipt. 
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int consult (NO_SEGMENT no, void *p1, void *p2)
{
	// Local variables *
    // *****************
	DATE xDate;
	FILE *pxPrn;
	
	// Print daily totals
	// ******************
	pxPrn = fopen("PRINTER", "w-*");               // Open "printer" peripheral
	if (pxPrn != NULL)
	{
		pprintf("\x1b""E%s\n""\x1b""F", zAppName); // Print application name
		pprintf("        CONSULT        \n"
			    "Print daily totals here\n"
			    "Number of Debit/Credit \n"
				"Totals of Debit/Credit \n"
				"Number of Cancel\n\n");
		read_date(&xDate);                         // Print date and time
		pprintf(zDate, xDate.day, xDate.month, xDate.year, xDate.hour, xDate.minute);
	
		ttestall(PRINTER, 1*100);                  // Wait until the end of printing
		fclose(pxPrn);                             // Close "printer" peripheral
	}

	return FCT_OK;
}

// ***************************************************************************
//             int mcall(NO_SEGMENT no, void *p1, void *p2)
/** It's activated on "F" key: Consultation->Call->Planning of Call. 
 *  To print call schedule receipt. 
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int mcall (NO_SEGMENT no, void *p1, void *p2)
{
	// Local variables *
    // *****************
	DATE xDate;
	FILE *pxPrn;
	
	// Print call schedule
	// *******************
	pxPrn = fopen("PRINTER", "w-*");               // Open "printer" peripheral
	if (pxPrn != NULL)
	{ 
		pprintf("\x1b""E%s\n""\x1b""F", zAppName); // Print application name
		pprintf("         MCALL         \n"
	            "Planning of call here  \n"
       			"Time release batch     \n"
				"Time loading parameters\n"
				"Time loading blacklist\n\n");
		read_date(&xDate);                         // Print date and time
		pprintf(zDate, xDate.day, xDate.month, xDate.year, xDate.hour, xDate.minute);
		
		ttestall(PRINTER, 1*100);                  // Wait until the end of printing
		fclose(pxPrn);                             // Close "printer" peripheral
	}

	return FCT_OK;
}

// ***************************************************************************
//     int is_time_function(NO_SEGMENT no, void *p1, S_ETATOUT *param_out)
/** Do you need the peripherals at the next call of time_function()?.
 *  It's call every minute.
 * \param    param_out (-O)
 *    - response : 
 *      REP_OK (Manager closes all peripherals), REP_KO (Manager keeps all peripherals opened)  
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int is_time_function(NO_SEGMENT no, void *p1, S_ETATOUT *param_out)
{
	// Local variables *
    // *****************
	int iRet;

	// Peripherals needed?
	// *******************
	param_out->returned_state[param_out->response_number].state.response=REP_OK;
	iRet = is_name (no, PT_NULL, param_out);

	return iRet;		 
}

// ***************************************************************************
//            int time_function(NO_SEGMENT no, void *p1, void *p2)
/** Allow application to execute its own periodical process. 
 *  It's call every minute. 
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int time_function(NO_SEGMENT no, void *p1, void *p2)
{	
	// Local variables *
    // *****************
	DATE xDate;
    char tcDate[10+1];
    char tcTime[5+1];
    char tcDisplay[100];
	
    // Read date and time
	// ******************
	pxDsp = stdperif("DISPLAY", NULL);          // Check "display" peripheral already opened? (done by Manager)
	if (pxDsp == NULL)                          // No, then open it
		pxDsp = fopen("DISPLAY", "w*");         // Open "display" peripheral

	if (pxDsp != NULL)
	{
		read_date (&xDate);
		sprintf (tcDate, "%2.2s/%2.2s/20%2.2s", // Retrieve date
			          	 xDate.day, xDate.month, xDate.year);
		sprintf (tcTime, "%2.2s:%2.2s",         // Retrieve time
			          	 xDate.hour, xDate.minute);

		// Periodical function in progress
		// *******************************
		sprintf(tcDisplay, "%s\n%s      %s", zTimeToCall, tcDate, tcTime);
		GL_Dialog_Message(xGoal, NULL, tcDisplay, GL_ICON_INFORMATION, GL_BUTTON_NONE, 2*1000);
	
        fclose(pxDsp);                          // Close "display" peripheral
        pxDsp=NULL;
	}

	return FCT_OK;
}

// ***************************************************************************
//     int is_change_init(NO_SEGMENT no, void *p1, S_ETATOUT *param_out)
/** It's activated on "F" key: Initialisation->Parameters->List.
 *  Each time Manager wants to change its own parameters.
 * \param    param_out (-O)
 *    - mask : Key "F" 031 -> Parameters modification (0:accepting, 1:refusing)
 *                                                       MSK_NULL  / MSK_ALL 
 *             Manager prints which applications have refused the modification
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int is_change_init(NO_SEGMENT no, void *p1, S_ETATOUT *param_out)
{
	// Local variables *
    // *****************
	T_STANDARD xPabx;
	bool bIso2=FALSE, bIso1=FALSE, bIso3=FALSE;
	DATE xDate;
   	int iRet;
	
	// Parameters modification allowed?
	// ********************************
	param_out->returned_state[param_out->response_number].state.mask=MSK_NULL;  // Accept all
	iRet = is_name (no, PT_NULL, param_out);

	// Save actual parameters
	// **********************
	memset (&xParams, 0, sizeof(ST_PARAMS));
	read_date(&xDate);                    // Read date and time
	switch (PSQ_Give_Date_Format())       // Retrieve date format
	{
	case 0:
		sprintf (xParams.tcOldDate, zDate1, xDate.day, xDate.month, xDate.year, xDate.hour, xDate.minute);
        strcpy (xParams.tcOldFmtDate, "DD/MM/YYYY\n");
		break;
	case 1:
		sprintf (xParams.tcOldDate, zDate1, xDate.month, xDate.day, xDate.year, xDate.hour, xDate.minute);
        strcpy (xParams.tcOldFmtDate, "MM/DD/YYYY\n");
        break;
	case 2:
		sprintf (xParams.tcOldDate, zDate2, xDate.year, xDate.month, xDate.day, xDate.hour, xDate.minute);
        strcpy (xParams.tcOldFmtDate, "YYYY/MM/DD\n");
		break;
	case 3:
		sprintf (xParams.tcOldDate, zDate3, xDate.day, xDate.month, xDate.year, xDate.hour, xDate.minute);
        strcpy (xParams.tcOldFmtDate, "DD.MM.YYYY\n");
        break;
	default:
		sprintf (xParams.tcOldDate, zDate2, xDate.year, xDate.month, xDate.day, xDate.hour, xDate.minute);
        strcpy (xParams.tcOldFmtDate, "YYYY/MM/DD\n");
		break;
	}
    switch (PSQ_Give_Language())         // Retrieve terminal language
	{
	case 0:
		strcpy (xParams.tcOldLanguage, "English\n");
		break;
	case 1:
		strcpy (xParams.tcOldLanguage, "French\n");
		break;
	case 2:
		strcpy (xParams.tcOldLanguage, "Russian\n");
		break;
	default:
		strcpy (xParams.tcOldLanguage, "Unknown\n");
		break;
	}
	PSQ_No_standard (xPabx);             // Retrieve Pabx prefix
    strcpy (xParams.tcOldPabx, xPabx);
	bIso2=TRUE;                          // Retrieve Swipe
	if (PSQ_Is_ISO1() != 0)
		bIso1=TRUE;
	if (PSQ_Is_ISO3() != 0)
		bIso3=TRUE;
    if (bIso2)
		strcpy (xParams.tcOldISOreader, "Iso2\n");
	if (bIso2 & bIso1)
		strcpy (xParams.tcOldISOreader, "Iso2 + Iso1\n");
	if (bIso2 & bIso3)
		strcpy (xParams.tcOldISOreader, "Iso2 + Iso3\n");
	if (bIso1 & bIso2 & bIso3)
		strcpy (xParams.tcOldISOreader, "Iso1 + Iso2 + Iso3\n");
    strcpy (xParams.tcOldPPad, "No");
	if (PSQ_Is_pinpad())
    {
		strcpy (xParams.tcOldPPad, "Yes");
		switch (PSQ_Pinpad_Value())
		{
		case PP30_PPAD:   strcpy(xParams.tcOldPPadType, "PP30 ");  break; // Pinpad characters no-reader Booster1
		case PP30S_PPAD:  strcpy(xParams.tcOldPPadType, "PP30S");  break; // Pinpad characters no-reader Booster2
		case PPC30_PPAD:  strcpy(xParams.tcOldPPadType, "PPC30");  break; // Pinpad graphic no-reader Booster1
		case PPR30_PPAD:  strcpy(xParams.tcOldPPadType, "PPR30");  break; // Pinpad graphic reader Booster1
		case P30_PPAD:    strcpy(xParams.tcOldPPadType, "P30  ");  break; // Pinpad graphic reader Booster2
		case IPP220_PPAD: strcpy(xParams.tcOldPPadType, "IPP220"); break; // Pinpad characters no-reader Booster3
		case IPP250_PPAD: strcpy(xParams.tcOldPPadType, "IPP250"); break; // Pinpad characters no-reader color Booster3
		case IPP280_PPAD: strcpy(xParams.tcOldPPadType, "IPP280"); break; // Pinpad graphic no-reader color Booster3
		case IPP320_PPAD: strcpy(xParams.tcOldPPadType, "IPP320"); break; // Pinpad graphic reader Booster3
		case IPP350_PPAD: strcpy(xParams.tcOldPPadType, "IPP350"); break; // Pinpad graphic reader color Booster3
		default:                                                   break; // Pinpad unknown
		}
	}

	return FCT_OK;		 
}

// ***************************************************************************
//        int modif_param(NO_SEGMENT no, S_MODIF_P *param_in, void *p2)
/** It's activated on "F" key: Initialization->Parameters->List.
 *  Each time Manager changed its own parameters.
 * \param    param_in (I-)
 *    - mask : Key "F" 031 -> Parameters modification (0:not modified, 1:modified)
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int modif_param(NO_SEGMENT noappli, S_MODIF_P *param_in, void *p2)
{
	// Local variables *
    // *****************
	doubleword uiMask;
	T_STANDARD tcPabx;
	char tcISOreader[24+1];
	bool bIso2=FALSE, bIso1=FALSE, bIso3=FALSE;
	bool bReboot=FALSE;
	DATE xDate;
	FILE *pxPrn;
		
    // Display parameters modified
	// ***************************
	pxPrn = fopen("PRINTER", "w-*");               // Open "printer" peripheral
	read_date(&xDate);                             // Read date and time
	if (pxPrn != NULL)
	{
	    uiMask = param_in->etatout.returned_state[param_in->etatout.response_number].state.mask;
	    switch (uiMask)
		{
        case MSK_DATE:                            // Date and Time (0x20000)
			pprintf("\x1b""E%s\n""\x1b""F", zAppName);      
			pprintf(xParams.tcOldFmtDate);
			pprintf(xParams.tcOldDate);
	        switch (PSQ_Give_Date_Format())       // Retrieve date format
			{
	        case 0:
                pprintf("DD/MM/YYYY\n");
	        	pprintf (zDate1, xDate.day, xDate.month, xDate.year, xDate.hour, xDate.minute);
		        break;
	        case 1:
		        pprintf("MM/DD/YYYY\n");
	        	pprintf (zDate1, xDate.month, xDate.day, xDate.year, xDate.hour, xDate.minute);
                break;
	        case 2:
                pprintf("YYYY/MM/DD\n");
	        	pprintf (zDate2, xDate.year, xDate.month, xDate.day, xDate.hour, xDate.minute);
		        break;
	        case 3:
		        pprintf("DD.MM.YYYY\n");
	        	pprintf (zDate3, xDate.day, xDate.month, xDate.year, xDate.hour, xDate.minute);
                break;
			default:
		        pprintf("YYYY/MM/DD\n");
				pprintf (zDate2, xDate.year, xDate.month, xDate.day, xDate.hour, xDate.minute);
		        break;
			}
            break;
		case MSK_FRMT_DATE:                       // Date format (0x10000 removed => see MSK_DATE)
			break;        
		case MSK_LANGUE:                          // Language (0x08000)
			pprintf("\x1b""E%s\n""\x1b""F", zAppName); 
            pprintf (xParams.tcOldLanguage);
			switch (PSQ_Give_Language())          // Retrieve language
			{
	    	case 0:
				pprintf ("English\n");
				break;
			case 1:
				pprintf ("French\n");
				break;
            case 2:
				pprintf ("Russian\n");
				break;
			default:
				pprintf ("Unknown\n");
				break;
			}
			break;	
		case MSK_STANDARD:                        // Pabx (0x01000)
			pprintf("\x1b""E%s\n""\x1b""F", zAppName); 
			pprintf ("%s\n", xParams.tcOldPabx);
			PSQ_No_standard (tcPabx);             // Retrieve Pabx prefix
			pprintf("%s\n", tcPabx);
			break;         
		case MSK_PINPAD:                          // PinPad (0x00800)
			pprintf("\x1b""E%s\n""\x1b""F", zAppName); 
			pprintf ("%s %s\n", xParams.tcOldPPad, xParams.tcOldPPadType);
			if (PSQ_Is_pinpad())
			{
				switch (PSQ_Pinpad_Value())
				{
				case PP30_PPAD:                   // Pinpad characters no-reader Booster1
					pprintf("Yes PP30\n");
					if (memcmp(xParams.tcOldPPadType, "PP30 ", 5) != 0)
						bReboot=TRUE;
					break;  
				case PP30S_PPAD:                  // Pinpad characters no-reader Booster2
					pprintf("Yes PP30S\n");
					if (memcmp(xParams.tcOldPPadType, "PP30S", 5) != 0)
						bReboot=TRUE;
					break; 
				case PPC30_PPAD:                  // Pinpad graphic no-reader Booster1
					pprintf("Yes PPC30\n");
					if (memcmp(xParams.tcOldPPadType, "PPC30", 5) != 0)
						bReboot=TRUE;					
					break; 
				case PPR30_PPAD:                  // Pinpad graphic reader Booster1
					pprintf ("Yes PPR30\n");
					if (memcmp(xParams.tcOldPPadType, "PPR30", 5) != 0)
						bReboot=TRUE;					
					break; 
				case P30_PPAD:                    // Pinpad graphic reader Booster2
					pprintf ("Yes P30\n");
					if (memcmp(xParams.tcOldPPadType, "P30  ", 5) != 0)
						bReboot=TRUE;					
					break;
				case IPP220_PPAD:                 // Pinpad characters no-reader Booster3
					pprintf ("Yes IPP220\n");
					if (memcmp(xParams.tcOldPPadType, "IPP220", 6) != 0)
						bReboot=TRUE;
					break;
				case IPP250_PPAD:                 // Pinpad characters no-reader color Booster3
					pprintf ("Yes IPP250\n");
					if (memcmp(xParams.tcOldPPadType, "IPP250", 6) != 0)
						bReboot=TRUE;
					break;
				case IPP280_PPAD:                 // Pinpad graphic no-reader color Booster3
					pprintf ("Yes IPP280\n");
					if (memcmp(xParams.tcOldPPadType, "IPP280", 6) != 0)
						bReboot=TRUE;
					break; 
				case IPP320_PPAD:                 // Pinpad graphic reader Booster3
					pprintf ("Yes IPP320\n");
					if (memcmp(xParams.tcOldPPadType, "IPP320", 6) != 0)
						bReboot=TRUE;
					break;
				case IPP350_PPAD:                 // Pinpad graphic reader color Booster3
					pprintf ("Yes IPP350\n");
					if (memcmp(xParams.tcOldPPadType, "IPP350", 6) != 0)
						bReboot=TRUE;
					break;
				default:                          // Pinpad unknown                                             
                    pprintf ("Yes Unknown\n");
					break; 
				}
			}
			else
			{
				pprintf ("No\n");
				if (memcmp(xParams.tcOldPPad, "No", 2) != 0)
					bReboot=TRUE;									
			}
			break;
		case MSK_SWIPE:                           // Swipe (0x00200)
			pprintf("\x1b""E%s\n""\x1b""F", zAppName); 
			pprintf (xParams.tcOldISOreader);
			bIso2=TRUE;
			if (PSQ_Is_ISO1() != 0)
				bIso1=TRUE;
			if (PSQ_Is_ISO3() != 0)
				bIso3=TRUE;
			if (bIso2)
				strcpy (tcISOreader,"Iso2");
			if (bIso2 & bIso1)
				strcpy (tcISOreader, "Iso2 + Iso1");
			if (bIso2 & bIso3)
				strcpy (tcISOreader, "Iso2 + Iso3");
			if (bIso1 & bIso2 & bIso3)
				strcpy (tcISOreader, "Iso1 + Iso2 + Iso3");
			pprintf ("%s\n", tcISOreader);
			break;            
		case MSK_MDP:                             // T.M.S Menu (0x00002)
			break;              
		default:                                  // Others
			break;                   
		}
		
		ttestall(PRINTER, 1*100);                 // Wait until the end of printing
		fclose(pxPrn);                            // Close "printer" peripheral
	}

	if (bReboot)                                  // Reboot if pinpad configuration changed
	{
		pxDsp = stdperif("DISPLAY", NULL);        // Check "display" peripheral already opened? (done by Manager)
		if (pxDsp == NULL)                        // No, then open it
			pxDsp = fopen("DISPLAY", "w*");       // Open "display" peripheral

		if (pxDsp != NULL)
			GL_Dialog_Message(xGoal, NULL, "TERMINAL\nRE-INIT", GL_ICON_INFORMATION, GL_BUTTON_NONE, 1*1000);

		exit(0);                                  
	}
	
	return FCT_OK;
}

// ***************************************************************************
//       int is_evol_pg(NO_SEGMENT no, void *p1, S_ETATOUT *param_out)
/** It's activated each time Manager wants to run a downloading session (local or remote).
 *  "F" key: Evolution->Load->Local or Evolution->Remote Load
 * \param    param_out (-O)
 *    - response : 
 *      REP_OK (App authorizes downloading process), REP_KO (App refuses any downloading process)
 *      Manager prints which applications have refused the downloading session  
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int is_evol_pg(NO_SEGMENT no, void *p1, S_ETATOUT *param_out)
{
	// Local variables *
    // *****************
	int iRet;

    // Downloading process allowed?
    // ****************************
	param_out->returned_state[param_out->response_number].state.response=REP_OK;
	iRet = is_name (no, PT_NULL, param_out);

	return iRet;		 
}

// ***************************************************************************
//       int is_delete(NO_SEGMENT no, void *p1, S_DELETE *param_out)
/** It's activated each time Manager wants to delete an application.
 *  "F" key: Deletion
 * \param    param_out (-O)
 *    - response : 
 *      DEL_YES (App authorizes deletion process), DEL_NO (App refuses any deletion process)
 *      Manager displays a message UNAVAILABLE FUNCTION if deletion refused
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************
int is_delete(NO_SEGMENT no, void *p1, S_DELETE *param_out)
{
	// Local variables *
    // *****************
       // Empty

	// Deletion process allowed?
    // *************************
	param_out->deleting=DEL_YES;

	return FCT_OK;
}

// ***************************************************************************
//        int file_received(NO_SEGMENT no, S_FILE *param_in, void *p2)
/** Manager reports parameters file received from LLT and located on HOST disk.
 *  It's activated upon reception of a parameter file by the manager.
 *  This parameter file must have the extension .PAR, and will be deleted
 *  by manager when leaving the function file_received().
 * \param    param_in (I-)
 *    - volume_name : HOST (File loaded in DFS).
 *    - file_name : Application file name
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************   
int file_received(NO_SEGMENT no, S_FILE *param_in, void *p2)
{
	// Local variables *
    // *****************
	T_GL_HWIDGET xScreen=NULL;
	ST_DSP_LINE xDspLine;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xPrnLine;
	int iHeader, iFooter;
	doubleword uiMode; // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
                       // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	char* pcMsg=NULL;
	int iRet;
	char tcDirFile[25];
	char tcDirLabel[25];
	char tcRsp[256];
	char tcBuffer[128];
	byte p;
	S_FS_FILE *pxFile;

	// Open peripherals
	// ****************
	iHeader = IsHeader();     // Save header state
	iFooter = IsFooter();     // Save footer state
	if (!IsColorDisplay())    // B&W terminal?
	{                         // Yes
		DisplayLeds(_OFF_);   // Disable Leds
		DisplayHeader(_OFF_); // Disable Header
		DisplayFooter(_OFF_); // Disable Footer
	}

	iRet = OpenPeripherals(); // Open standard peripherals
	CHECK(iRet>=0, lblKO);

	// Retrieve parameter file received
	// ********************************
	memset(tcDirFile, 0, sizeof(tcDirFile));
	memset(tcDirLabel, 0, sizeof(tcDirLabel));

	sprintf(tcDirLabel, "/%s", param_in->volume_name);
	iRet = FS_mount (tcDirLabel, &uiMode); // Disk HOST initialization (!!! second parameter returns (FS_WRITEONCE or FS_WRITEMANY))
	CHECK(iRet==FS_OK, lblKODisk);

	sprintf(tcDirFile, "/%s/%s", param_in->volume_name, param_in->file_name);
	pxFile = FS_open (tcDirFile, "r");     // The file can be open at this stage
	CHECK(pxFile!=NULL, lblKO);

	// Eventually read the file and get parameters
	iRet = FS_length(pxFile);              // File length in bytes
	CHECK(iRet!=FS_ERROR, lblKODisk);

	memset(tcRsp, 0, sizeof(tcRsp));
	FS_read(tcRsp, iRet, 1, pxFile);       // Read from file

	iRet = FS_close(pxFile);               // Close the file
	CHECK(iRet==FS_OK, lblKODisk);
	iRet = FS_unmount(tcDirLabel);         // File will be deleted by manager !!!
	CHECK(iRet==FS_OK, lblKODisk);

	// Show parameter file received
	// ****************************
	xScreen = GoalCreateScreen(xGoal, txScreen, NUMBER_OF_LINES(txScreen), GL_ENCODING_UTF8);
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, 0, false); // Create and clear screen
	CHECK(iRet>=0, lblKO);

	xDspLine = txScreen[0];                // Build screen and show it (File.par, msg received)
	xDspLine.xBW.eTextAlign = GL_ALIGN_CENTER;
	xDspLine.xColor.eTextAlign = GL_ALIGN_CENTER; xDspLine.xColor.ulPen = GL_COLOR_YELLOW;
	sprintf(tcBuffer, "TRAIN (from %s)", param_in->file_name);
	iRet = GoalDspLine(xScreen, 0, tcBuffer, &xDspLine, 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspMultiLine(xScreen, 1, tcRsp, strlen(tcRsp), txScreen, NUMBER_OF_LINES(txScreen), 0, true);
	CHECK(iRet>=0, lblKO);

	// Print parameter file received
	// *****************************
	p=0;                                   // Create the document
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);
	CHECK(xDocument!=NULL, lblKO);

	xPrnLine = xPrinter;                   // Build the document (Training, File.par, msg received)
	xPrnLine.eTextAlign = GL_ALIGN_CENTER;
	xPrnLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "TRAINING", &xPrnLine);
	CHECK(iRet>=0, lblKO);
	xPrnLine.eTextAlign = GL_ALIGN_LEFT;
	xPrnLine.xFont.eScale = GL_SCALE_LARGE;
	sprintf(tcBuffer, "File Received: /%s/%s", param_in->volume_name, param_in->file_name);
	iRet = GoalPrnLine(xDocument, p++, tcBuffer, &xPrnLine);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, tcRsp, &xPrnLine);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "\n\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);    // Print document
	CHECK(iRet>=0, lblKO);

	ttestall(0, 1*100);                   // Wait to see the message received

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                    // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblKODisk:                                // Disk error
    switch (iRet)
	{
	case FS_NOACCESS: pcMsg = "No access from Appli";  break;
	case FS_DSKUSED:  pcMsg = "Disk is still mounted"; break;
	case FS_FILEUSED: pcMsg = "Files are still open";  break;
	case FS_KO:
	default:          pcMsg = "Disk not found";        break;
	}
    GL_Dialog_Message(xGoal, NULL, pcMsg, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);      // Destroy screen

	if (xDocument)
		GoalDestroyDocument(&xDocument);  // Destroy document

	ClosePeripherals();                   // Close standard peripherals

	DisplayLeds(_ON_);                    // Enable Leds
	DisplayHeader(iHeader);               // Restore Header
	DisplayFooter(iFooter);               // Restore Footer

	return FCT_OK;
}

// ***************************************************************************
//   int message_received(NO_SEGMENT no, S_MESSAGE_IAM *param_in, void *p2)
/** Inter application messaging.
 *  It's activated each time Manager received a message in its mailbox for this 
 *  application or task.
 * \param    param_in (I-)
 *    - sender : Sender ID.
 *    - receiver : Receiver ID.
 *    - type : IAM type.
 *    - length : Message length.
 *    - value : Message received.
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************   
int message_received(NO_SEGMENT no, S_MESSAGE_IAM *param_in, void *p2)
{
	// Local variables *
    // *****************
	T_GL_HWIDGET xScreen=NULL;
	ST_DSP_LINE xDspLine;
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xPrnLine;
	char tcPrint[256+1];
	byte p; // Printer line index
	int iHeader, iFooter;
	int iRet;

	// Open peripherals
	// ****************
	iHeader = IsHeader();     // Save header state
	iFooter = IsFooter();     // Save footer state
	if (!IsColorDisplay())    // B&W terminal?
	{                         // Yes
		DisplayLeds(_OFF_);   // Disable Leds
		DisplayHeader(_OFF_); // Disable Header
		DisplayFooter(_OFF_); // Disable Footer
	}

	iRet = OpenPeripherals(); // Open standard peripherals
	CHECK(iRet>=0, lblKO);

	// Get message received from TRAINING itself or USER2 or TASK2
	// ***********************************************************
	xScreen = GoalCreateScreen(xGoal, txScreen, NUMBER_OF_LINES(txScreen), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, 0, false); // Create and clear screen
	CHECK(iRet>=0, lblKO);

	xDspLine = txScreen[0];                                  // Build screen and show it (Appli name, msg received)
	xDspLine.xColor.eTextAlign = GL_ALIGN_CENTER; xDspLine.xColor.ulPen = GL_COLOR_YELLOW;
	xDspLine.xBW.eTextAlign = GL_ALIGN_CENTER;

	p=0;                                                     // Create the document
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);
	CHECK(xDocument!=NULL, lblKO);

	xPrnLine = xPrinter;                                     // Build the document (Appli name, IAM info, Sender/Receiver, IAM type, IAM message)
	xPrnLine.eTextAlign = GL_ALIGN_CENTER;
	xPrnLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, (char*)zAppName, &xPrnLine);
	CHECK(iRet>=0, lblKO);
	xPrnLine.eTextAlign = GL_ALIGN_LEFT;
	xPrnLine.xFont.eScale = GL_SCALE_LARGE;

	if (param_in->type == 0)                                 // Message received from Training
	{
		iRet = GoalDspLine(xScreen, 0, "TRAIN (Msg from TRAIN)", &xDspLine, 0, false);
		CHECK(iRet>=0, lblKO);
		iRet = GoalDspMultiLine(xScreen, 1, (char*)param_in->value, param_in->length, txScreen, NUMBER_OF_LINES(txScreen), 0, true);
		CHECK(iRet>=0, lblKO);

		iRet = GoalPrnLine(xDocument, p++, "Message IAM from Appli:", &xPrnLine);
		CHECK(iRet>=0, lblKO);
		sprintf (tcPrint, "S:%04X R:%04X", param_in->sender, param_in->receiver);
		iRet = GoalPrnLine(xDocument, p++, tcPrint, &xPrnLine);
		CHECK(iRet>=0, lblKO);
		sprintf (tcPrint, "IAM Type : %04X\n\n", param_in->type);
		iRet = GoalPrnLine(xDocument, p++, tcPrint, &xPrnLine);
		CHECK(iRet>=0, lblKO);
		iRet = GoalPrnLine(xDocument, p++, "Msg from TRAINING:", &xPrnLine);
		CHECK(iRet>=0, lblKO);
		strncpy(tcPrint, (char*)param_in->value, param_in->length);
		iRet = GoalPrnLine(xDocument, p++, tcPrint, &xPrnLine);
		CHECK(iRet>=0, lblKO);
	}
	else if (param_in->type == 1)                            // Message received from Task2
	{
		iRet = GoalDspLine(xScreen, 0, "TRAIN (Msg from TASK2)", &xDspLine, 0, false);
		CHECK(iRet>=0, lblKO);
		iRet = GoalDspMultiLine(xScreen, 1, (char*)param_in->value, param_in->length, txScreen, NUMBER_OF_LINES(txScreen), 0, true);
		CHECK(iRet>=0, lblKO);

		iRet = GoalPrnLine(xDocument, p++, "Message IAM from Task:", &xPrnLine);
		CHECK(iRet>=0, lblKO);
		sprintf (tcPrint, "S:%04X R:%04X", param_in->sender, param_in->receiver);
		iRet = GoalPrnLine(xDocument, p++, tcPrint, &xPrnLine);
		CHECK(iRet>=0, lblKO);
		sprintf (tcPrint, "IAM Type : %04X\n\n", param_in->type);
		iRet = GoalPrnLine(xDocument, p++, tcPrint, &xPrnLine);
		CHECK(iRet>=0, lblKO);
		iRet = GoalPrnLine(xDocument, p++, "Msg from TASK2:", &xPrnLine);
		CHECK(iRet>=0, lblKO);
		strncpy(tcPrint, (char*)param_in->value, param_in->length);
		iRet = GoalPrnLine(xDocument, p++, tcPrint, &xPrnLine);
		CHECK(iRet>=0, lblKO);
	}
	else                                                     // Message received from User2
	{
		iRet = GoalDspLine(xScreen, 0, "TRAIN (Msg from USER2)", &xDspLine, 0, false);
		CHECK(iRet>=0, lblKO);
		iRet = GoalDspMultiLine(xScreen, 1, (char*)param_in->value, param_in->length, txScreen, NUMBER_OF_LINES(txScreen), 0, true);
		CHECK(iRet>=0, lblKO);

		iRet = GoalPrnLine(xDocument, p++, "Message IAM from Appli:", &xPrnLine);
		CHECK(iRet>=0, lblKO);
		sprintf (tcPrint, "S:%04X R:%04X", param_in->sender, param_in->receiver);
		iRet = GoalPrnLine(xDocument, p++, tcPrint, &xPrnLine);
		CHECK(iRet>=0, lblKO);
		sprintf (tcPrint, "IAM Type : %04X\n\n", param_in->type);
		iRet = GoalPrnLine(xDocument, p++, tcPrint, &xPrnLine);
		CHECK(iRet>=0, lblKO);
		iRet = GoalPrnLine(xDocument, p++, "Msg from USER2:", &xPrnLine);
		CHECK(iRet>=0, lblKO);
		strncpy(tcPrint, (char*)param_in->value, param_in->length);
		iRet = GoalPrnLine(xDocument, p++, tcPrint, &xPrnLine);
		CHECK(iRet>=0, lblKO);
	}

	iRet = GoalPrnLine(xDocument, p++, "----------------------------------------------""\n\n\n\n", &xPrnLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                       // Print document
	CHECK(iRet>=0, lblKO);

	ttestall(0, 2*100);                                      // Wait to see the message received
	
	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                       // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);                         // Destroy screen

	if (xDocument)
		GoalDestroyDocument(&xDocument);                     // Destroy document

	ClosePeripherals();                                      // Close standard peripherals

	DisplayLeds(_ON_);                                       // Enable Leds
	DisplayHeader(iHeader);                                  // Restore Header
	DisplayFooter(iFooter);                                  // Restore Footer

	return FCT_OK;
}

// ***************************************************************************
//   int is_card_specific(NO_SEGMENT no, S_TRANSIN *param_in, S_ETATOUT *param_out)
/** 
 *  It's activated when a card is inserted, swiped or manually entry.
 *  Ask the application if the card needs a specific processing.
 * \param    param_out (-O)
 *    - response : 
 *      REP_OK (card processing), REP_KO (no card processing)  
 *  Only one application wants to process the card, manager calls CARD_INSIDE entry.
 *  More application wants to process the card, manager asks for card removal.
 *  If no application wants to process the card, manager goes on with selection process. 
 * \return                                           
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************   
int is_card_specific(NO_SEGMENT no, S_TRANSIN *param_in, S_ETATOUT *param_out)
{
	// Local variables *
	// *****************
	int iRet; 

	// Card needs a specific processing
	// ********************************
	pxDsp = stdperif("DISPLAY", NULL);  // Check "display" peripheral already opened? (done by Manager)
	if (pxDsp == NULL)                  // No, then open it
		pxDsp = fopen("DISPLAY", "w*"); // Open "display" peripheral

	if (pxDsp != NULL)
	{
		if (AMOUNT_ENTRY && (param_in->amount == 0))
		{                               // Enter amount first before card process
			param_out->returned_state[param_out->response_number].state.response = REP_OK;
			GL_Dialog_Message(xGoal, NULL, "Enter Amount First", GL_ICON_WARNING, GL_BUTTON_NONE, 2*1000);
		}
		else
			param_out->returned_state[param_out->response_number].state.response = REP_KO;

		fclose(pxDsp);                  // Close "display" peripheral
		pxDsp=NULL;
	}

	iRet = is_name (no, PT_NULL, param_out);
	
	return iRet;
}

// ***************************************************************************
//   int card_inside(NO_SEGMENT no, S_TRANSIN *param_in, S_TRANSOUT *param_out)
/** 
 *  It's activated when an application has chosen to treat this card has specific.
 *  The transaction is done here.
 * \param    param_out (-O)
 *    - rc_payment : 
 *      PAY_OK (Transaction done), PAY_KO (Transaction rejected)  
 *  If an application returns STOP, polling is stopped and manager asks for card removal.
 *  The application is in charge to ask for amount and currency if needed.
 * \return   
 *  STOP    Card accepted and transaction process done, polling is stop. 
 *  FCT_OK  Card refused and poll the next application.
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************   
int card_inside(NO_SEGMENT no, S_TRANSIN *param_in, S_TRANSOUT *param_out)
{
	// Local variables *
	// *****************
    bool card_accepted = TRUE;

	if (card_accepted)
	{
	// Return transaction status
	// *************************
		param_out->rc_payment = PAY_OK; // Transaction done, polling is stop
		return STOP;
	}
	else
		return FCT_OK;                  // Card refused, poll the next application
}

// ***************************************************************************
//   int is_for_you_before(NO_SEGMENT no, void *p1, S_ETATOUT *param_out)
/** 
 *  Only for application handling "old" chip cards not supporting software reset. 
 *  Such as synchronous card, the application should power-on the card then
 *  read it to analyze which kind of synchronous card then power off.
 *  Regarding the card, the application should return accepted or rejected.
 * \param    param_out (-O)
 *    - response :
 *      Priority level (>=0 Accepted, 0=Rejected)  
 *    - appname : Application name 
 *    - no : Application number
 *    - response_number : should be incremented
 *  Applications being declared candidate will be placed before EMV applications
 *  in the list.
 * \return   
 *  FCT_OK 
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************   
int is_for_you_before(NO_SEGMENT no, S_TRANSIN *param_in, S_ETATOUT *param_out)
{
	// Local variables *
	// *****************
       // Empty
	
    // Case for a synchronous card which needs a selection process
	// ***********************************************************
	
    // Power on the card
	// =================
       // Implement here the function to power-on the synchronous card.     
	
    // Analyze chip card
	// =================
       // Read the card to analyze which synchronous card it is and return accepted or rejected.
  	   param_out->returned_state[param_out->response_number].state.response = 0;


  	// Power off the card
	// ==================
       // Implement here the function to power-off the synchronous card.

	// Give my application name
	strcpy (param_out->returned_state[param_out->response_number].appname, zAppName);
	// Give my application number
	param_out->returned_state[param_out->response_number].no_appli = no;
	// Increment the response number
	param_out->response_number++;
  
	return FCT_OK;
}

// ***************************************************************************
//   int is_for_you_after(NO_SEGMENT no, S_TRANSIN *param_in, S_CARDOUT *param_out)
/** 
 *  Ask application to recognize the mag, smart or manually card in order to be
 *  a candidate.
 * \param    param_out (-O)
 *    - cardappnumber : 1 = Card accepted, 0 = Card rejected 
 *    - cardapp (Selection priority):
 *      CARD_PROCESSED (low priority) 
 *      CARD_RECOGNIZED (medium priority) 
 *      CARD_PRIORITY (high priority)
 *    - appname : Application name 
 *    - no : Application number
 *    - response_number : should be incremented
 *  If an application returns STOP, polling is stopped and manager asks for card removal.
 *  The application is in charge to ask for amount and currency if needed.
 * \return
 *  STOP    Card accepted and transaction process done, polling is stop.
 *  FCT_OK  Card refused and poll the next application.
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************   
int is_for_you_after(NO_SEGMENT no, S_TRANSIN *param_in, S_CARDOUT *param_out)
{
	// Local variables *
	// *****************
       // Empty
	
	// ####################
	// Case of SMART card #
	// ####################
	if (param_in->support == CHIP_SUPPORT)
	{
		if(param_in->power_on_result == 0) 
		{
			// Accept this card
			param_out->returned_state[param_out->response_number].cardappnumber = 1; 
 		    param_out->returned_state[param_out->response_number].cardapp [0].priority = CARD_PRIORITY;
		}
		else
			// Reject the card
			param_out->returned_state[param_out->response_number].cardappnumber = 0; 
	}

	// ############################################
	// Case of MAGNETIC 2 or 12 or 32 or 123 card #
	// ############################################
	if (    (param_in->support == TRACK2_SUPPORT)
		 || (param_in->support == TRACK12_SUPPORT)
		 || (param_in->support == TRACK32_SUPPORT)
         || (param_in->support == TRACK123_SUPPORT) )
	{
		// Accept this card
		param_out->returned_state[param_out->response_number].cardappnumber = 1;
		param_out->returned_state[param_out->response_number].cardapp [0].priority = CARD_PRIORITY;
	}
	
	// ####################################
	// Case of Card Number MANUALLY entry #
	// ####################################
	if (param_in->support == OPERATOR_SUPPORT)
	{
		// Accept this card
		param_out->returned_state[param_out->response_number].cardappnumber = 1;
		param_out->returned_state[param_out->response_number].cardapp [0].priority = CARD_PRIORITY;
	}

	// Give my application name
	strcpy (param_out->returned_state[param_out->response_number].appname, zAppName) ;
	// Give my application number
	param_out->returned_state[param_out->response_number].no_appli = no;
	// Give my card name
	strcpy (param_out->returned_state[param_out->response_number].cardapp [0].cardappname, "") ;
	// Increment the response number
	param_out->response_number++;

	return FCT_OK;
}

// ***************************************************************************
//   int debit_non_emv(NO_SEGMENT no, S_TRANSIN *param_in, S_CARDOUT *param_out)
/** 
 *  Process a non EMV chip card or a magnetic card or manual entry transaction.
 *  Support only DEBIT transaction.
 * \param    param_out (-O)
 * \param    param_out (-O)
 *    - rc_payment : 
 *      PAY_OK (Transaction done), PAY_KO (Transaction rejected)  
 * \return   
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************   
int debit_non_emv (NO_SEGMENT no, S_TRANSIN * param_in, S_TRANSOUT * param_out)
{
	// Local variables *
	// *****************
	T_GL_HWIDGET xScreen=NULL;
	int iHeader, iFooter;
	char tcDisplay[250+1];
	char *pcSrc, *pcDst;
    char tcTrk1[128], tcTrk2[128], tcTrk3[128];
    char tcPan[19+1];
	int i, iRet;
	
	// Open peripherals
	// ****************
	iHeader = IsHeader();               // Save header state
	iFooter = IsFooter();               // Save footer state
	if (!IsColorDisplay())              // B&W terminal?
	{                                   // Yes
		DisplayLeds(_OFF_);             // Disable Leds
		DisplayHeader(_OFF_);           // Disable Header
		DisplayFooter(_OFF_);           // Disable Footer
	}

	pxDsp = stdperif("DISPLAY", NULL);  // Check "display" peripheral already opened? (done by Manager)
	if (pxDsp == NULL)                  // No, then open it
	{
		pxDsp = fopen("DISPLAY", "w*"); // Open "display" peripheral
		CHECK(pxDsp!=NULL, lblKO);
	}
	pxPrn = fopen("PRINTER", "w-*");    // Open "printer" peripheral
	CHECK(pxPrn!=NULL, lblKO);

	xScreen = GoalCreateScreen(xGoal, txScreen, NUMBER_OF_LINES(txScreen), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, 0, false);                     // Create and clear screen
	CHECK(iRet>=0, lblKO);

	// ####################
	// Case of SMART card #
	// ####################
	if ( param_in->support == CHIP_SUPPORT )
	{
		// Display transaction
		// ===================
		iRet = GoalDspLine(xScreen, 0, (char*)zAppName, &txScreen[0], 0, false); // Show application name
		CHECK(iRet>=0, lblKO);

		if (param_in->historical_bytes.length != 0)      // Show ATR
		{
			strcpy(tcDisplay, "Atr: ");
			for (i=0; i<param_in->historical_bytes.length; i++)
				sprintf(&tcDisplay[5+(2*i)], "%02X", param_in->historical_bytes.historic[i]);
			strcpy(tcTrk2, "B4972026258697417=0911");    // An hard coded track2 for cash register purpose
		}
		else
			strcpy(tcDisplay, "Synchronous or Mute Chip");
		iRet = GoalDspLine(xScreen, 1, tcDisplay, &txScreen[1], 0, true);
		CHECK(iRet>=0, lblKO);

		if (param_in->amount != 0)                       // Show amount
		{
			sprintf(tcDisplay, "Amount: %d", (int) param_in->amount);
			iRet = GoalDspLine(xScreen, 2, tcDisplay, &txScreen[2], 0, true);
			CHECK(iRet>=0, lblKO);
		}
		
		// Print transaction
		// =================
		pprintf("\x1b""E%s\n""\x1b""F", zAppName);       // Print application name
		if (param_in->historical_bytes.length != 0)      // Print ATR
		{
			pprintf("Atr:\n");
			for (i=0; i<param_in->historical_bytes.length; i++)
				pprintf("%02X ", param_in->historical_bytes.historic[i]);
			pprintf("\n");
		}
		else
			pprintf("Synchronous or Mute Chip\n");

		if (param_in->transaction == DEBIT_TR)           // Supported by debit_non_emv
			pprintf("Transaction: DEBIT\n");
		else if (param_in->transaction == CREDIT_TR)     // Supported by select_function
			pprintf("Transaction: CREDIT\n");
		else if (param_in->transaction == CANCEL_TR)     // Supported by select_function
			pprintf("Transaction: CANCEL\n");
		else if (param_in->transaction == EXT_CANCEL_TR) // Supported by select_function
			pprintf("Transaction: EXT CANCEL\n");
		else
			pprintf("Transaction: PRE AUTH\n");          // Supported by select_function

		if (param_in->amount != 0)                       // Print amount and currency
		{
			pprintf("Amount: %d\n", param_in->amount);
			pprintf("Currency: %.3s %.3s %d\n", param_in->currency.nom, param_in->currency.code, param_in->currency.posdec);
		}
		pprintf("\n\n\n\n\n");
	}

	// ############################################
	// Case of MAGNETIC 2 or 12 or 32 or 123 card #
	// ############################################
	if (    (param_in->support == TRACK2_SUPPORT)   
		 || (param_in->support == TRACK12_SUPPORT)
		 || (param_in->support == TRACK32_SUPPORT)
         || (param_in->support == TRACK123_SUPPORT) )
	{
		// Retrieve and analyze track1
		// ===========================
		if (param_in->cr_iso1 == ISO_OK)               // *** Magnetic track1 ***
		{
			pcSrc = (char*)param_in->track1;
			pcDst = tcTrk1;                            // Return track1
			while(*pcSrc) {                            // Find start sentinel
				if(*pcSrc++ == '%')
					break;
			}
			while(*pcSrc) {                            // Copy all data between start and end sentinels
				if(*pcSrc == '?')
					break;
				*pcDst++ = *pcSrc++;
			}
		}
		else
			IsoError (param_in->cr_iso1, tcTrk1);

		// Retrieve and analyze track2
		// ===========================
		if (param_in->cr_iso2 == ISO_OK)               // *** Magnetic track2 ***
		{
			pcSrc = (char*)param_in->track2;
			pcDst = tcTrk2;                            // Return track2
			while(*pcSrc) {                            // Find start sentinel
				if(*pcSrc++ == 'B')
					break;
			}
			while(*pcSrc) {                            // Copy all data between start and end sentinels
				if(*pcSrc == 'F')
					break;
				if(*pcSrc == 'D')
					*pcSrc = '=';
				*pcDst++ = *pcSrc++;
			}
		}
		else
			IsoError (param_in->cr_iso2, tcTrk2);      // Magnetic Card error

		// Retrieve and analyze track3
		// ===========================
		if (param_in->cr_iso3 == ISO_OK)               // *** Magnetic track3 ***
		{
			pcSrc = (char*)param_in->track3;
			pcDst = tcTrk3;                            // Return track3
			while(*pcSrc) {                            // Find start sentinel
				if(*pcSrc++ == 'B')
					break;
			}
			while(*pcSrc) {                            // Copy all data between start and end sentinels
				if(*pcSrc == 'F')
					break;
				if(*pcSrc == 'D')
					*pcSrc = '=';
				*pcDst++ = *pcSrc++;
			}
		}
		else
			IsoError (param_in->cr_iso3, tcTrk3);      // Magnetic Card error

		// Display transaction
		// ===================
		iRet = GoalDspLine(xScreen, 0, (char*)zAppName, &txScreen[0], 0, false); // Show application name
		CHECK(iRet>=0, lblKO);
		sprintf(tcDisplay, "Trk1: %s", tcTrk1);
		iRet = GoalDspLine(xScreen, 1, tcDisplay, &txScreen[1], 0, false);       // Show part of track1
		CHECK(iRet>=0, lblKO);
		sprintf(tcDisplay, "Trk2: %s", tcTrk2);
		iRet = GoalDspLine(xScreen, 2, tcDisplay, &txScreen[2], 0, false);       // Show part of track2
		CHECK(iRet>=0, lblKO);
		sprintf(tcDisplay, "Trk3: %s", tcTrk3);
		iRet = GoalDspLine(xScreen, 3, tcDisplay, &txScreen[3], 0, true);        // Show part of track3
		CHECK(iRet>=0, lblKO);
		if (param_in->amount != 0)                                               // Show amount
		{
			sprintf(tcDisplay, "Amount: %d", (int) param_in->amount);
			iRet = GoalDspLine(xScreen, 4, tcDisplay, &txScreen[4], 0, true);
			CHECK(iRet>=0, lblKO);
		}

		// Print transaction
		// =================
		pprintf("\x1b""E%s\n""\x1b""F", zAppName);       // Print application name
		pprintf("Track1:\n%s\n", tcTrk1);                // Print track1
		pprintf("Track2:\n%s\n", tcTrk2);                // Print track2
		pprintf("Track3:\n%s\n", tcTrk3);                // Print track3

		if (param_in->transaction == DEBIT_TR)           // Supported by debit_non_emv
			pprintf("Transaction: DEBIT\n");
		else if (param_in->transaction == CREDIT_TR)     // Supported by select_function
			pprintf("Transaction: CREDIT\n");
		else if (param_in->transaction == CANCEL_TR)     // Supported by select_function
			pprintf("Transaction: CANCEL\n");
		else if (param_in->transaction == EXT_CANCEL_TR) // Supported by select_function
			pprintf("Transaction: EXT CANCEL\n");
		else
			pprintf("Transaction: PRE AUTH\n");          // Supported by select_function

		if (param_in->amount != 0)                       // Print amount and currency
		{
			pprintf("Amount: %d\n", param_in->amount);
			pprintf("Currency: %.3s %.3s %d\n", param_in->currency.nom, param_in->currency.code, param_in->currency.posdec);
		}
		pprintf("\n\n\n\n\n");
	}
	
	// ####################################
	// Case of Card Number MANUALLY entry #
	// ####################################
	if ( param_in->support == OPERATOR_SUPPORT )
	{
		// Retrieve and analyze entry (track2)
		// ===================================
		pcSrc = (char*)param_in->track2;
		pcDst = tcTrk2;                                // Return track2
		while(*pcSrc) {                                // Find start sentinel
			if(*pcSrc++ == 'B')
				break;
		}
		while(*pcSrc) {                                // Copy all data between start and end sentinels
			if(*pcSrc == 'F')
				break;
			if(*pcSrc == 'D')
				*pcSrc = '=';
			*pcDst++ = *pcSrc++;
		}

		// Display transaction
		// ===================
		iRet = GoalDspLine(xScreen, 0, (char*)zAppName, &txScreen[0], 0, false); // Show application name
		CHECK(iRet>=0, lblKO);
		sprintf(tcDisplay, "Man: %s", tcTrk2);
		iRet = GoalDspLine(xScreen, 1, tcDisplay, &txScreen[1], 0, false);       // Show part of track2
		CHECK(iRet>=0, lblKO);
		if (param_in->amount != 0)                                               // Show amount
		{
			sprintf(tcDisplay, "Amount: %d", (int) param_in->amount);
			iRet = GoalDspLine(xScreen, 2, tcDisplay, &txScreen[2], 0, true);
			CHECK(iRet>=0, lblKO);
		}

		// Print transaction
		// =================
		pprintf("\x1b""E%s\n""\x1b""F", zAppName);       // Print application name
		pprintf("Manual Entry:\n%s\n", tcTrk2);          // Print track2

		if (param_in->transaction == DEBIT_TR)           // Supported by debit_non_emv
			pprintf("Transaction: DEBIT\n");
		else if (param_in->transaction == CREDIT_TR)     // Supported by select_function
			pprintf("Transaction: CREDIT\n");
		else if (param_in->transaction == CANCEL_TR)     // Supported by select_function
			pprintf("Transaction: CANCEL\n");
		else if (param_in->transaction == EXT_CANCEL_TR) // Supported by select_function
			pprintf("Transaction: EXT CANCEL\n");
		else
			pprintf("Transaction: PRE AUTH\n");          // Supported by select_function

		if (param_in->amount != 0)                       // Print amount and currency
		{
			pprintf("Amount: %d\n", param_in->amount);
			pprintf("Currency: %.3s %.3s %d\n", param_in->currency.nom, param_in->currency.code, param_in->currency.posdec);
		}
		pprintf("\n\n\n\n\n");
	}

	GoalGetKey(xScreen, xGoal, true, 2*1000, true);      // Wait for key pressed/touched (shortcut)

	// ****************************************************************
	// Information returned to Cash Register
	// (See ServiceCall100 to communicate with connected Cash Register)
	// ****************************************************************
	param_out->noappli = no;                             // Return application number
	param_out->rc_payment = PAY_OK;                      // Transaction done
	memset(tcPan, 0, sizeof(tcPan));
	parseStr('=', tcPan, tcTrk2, sizeof(tcPan));
	memcpy(param_out->card_holder_nb, tcPan, 19);        // Return card holder number (Pan)

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                               // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_NONE, 5*1000);
	param_out->noappli = no;         // Return application number
	param_out->rc_payment = PAY_KO;  // Transaction failed
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen); // Destroy screen

	if(pxPrn)
    {
		fclose(pxPrn);               // Close "printer" peripheral
		pxPrn=NULL;
    }

	if(pxDsp)
	{
        fclose(pxDsp);               // Close "display" peripheral
        pxDsp=NULL;
	}

	DisplayLeds(_ON_);               // Enable Leds
	DisplayHeader(iHeader);          // Restore Header
	DisplayFooter(iFooter);          // Restore Footer

	return FCT_OK;
}

// ***************************************************************************
//   int select_function(NO_SEGMENT no, S_TRANSIN *param_in, S_CARDOUT *param_out)
/**
 * Process a non EMV chip card or a magnetic card or manual entry transaction.
 * Support CREDIT, CANCEL and PRE AUTHORIZATION Transactions.
 * \param    param_out (-O)
 *    - rc_payment :
 *      PAY_OK (Transaction done), PAY_KO (Transaction rejected)
 * \return
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c
*/
// ***************************************************************************
int select_function (NO_SEGMENT no, S_TRANSIN *param_in, S_TRANSOUT *param_out)
{
	// Local variables *
	// *****************
	int iRet;

	// Same prototype as debit_non_emv transaction
	// *******************************************
	iRet = debit_non_emv (no, param_in, param_out);

	return iRet;
}

// ***************************************************************************
//   int customize_message(int size, InfosMSG_CUST *param)
/**
 *  To customized the Manager messages.
 *  Refer to SDK chm in TELIUM Manager User Guide.
 *  Section 11: Manager customization (see list of messages customizable).
 * \return
 *  FCT_OK
 * \header sdk30.h
 * \source entry.c
*/
// ***************************************************************************
int customize_message (int size, InfosMSG_CUST *param)
{
	// Local variables *
	// *****************
	   // Empty

	// Customizable messages from Manager
	// **********************************
	pxDsp = stdperif("DISPLAY", NULL);  // Check "display" peripheral already opened? (done by Manager)
	if (pxDsp == NULL)                  // No, then open it
		pxDsp = fopen("DISPLAY", "w*"); // Open "display" peripheral

	if (pxDsp != NULL)
	{
		switch (param->num)
		{
		case MESS214: // "    NO MORE\n     PAPER\n"
			GL_Dialog_Message(xGoal, NULL, "   PAPER ROLL   \n    MISSING     ", GL_ICON_NONE, GL_BUTTON_NONE, 0);
			param->cr_treatment = CUSTOMIZED_MESSAGE;    // Accept this new message
			break;
		case MESS262: // "     REMOVE\n  CARD PLEASE"
			GL_Dialog_Message(xGoal, NULL, " PLEASE REMOVE  \n   CHIP CARD    ", GL_ICON_NONE, GL_BUTTON_NONE, 0);
			param->cr_treatment = CUSTOMIZED_MESSAGE;    // Accept this new message
			break;
		default:
			param->cr_treatment = NO_CUSTOMIZED_MESSAGE; // Don't change the default Manager message
			break;
		}

		fclose(pxDsp);                  // Close "display" peripheral
		pxDsp=NULL;
	}

	return FCT_OK;
}

// ***************************************************************************
//       int give_interface(word no, void *p1, void *p2)
/** Services registration and priority.  
 *  For all services except idle_message, priority => 0x00 highest and 0xFF lowest
 *  For idle_message, priority => 0x00 lowest 0xFF highest
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************   
int give_interface(word no, void *p1, void *p2)
{
	// Local variables *
    // *****************
	int i;

	// Recording services in progress
	// ******************************
	static service_desc_t txServices[] =
	{
	    { 0, GIVE_YOUR_DOMAIN,              (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Return application domain to Manager
	    { 0, GIVE_YOUR_SPECIFIC_CONTEXT,    (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Return specific context to Manager
	    { 0, AFTER_RESET,                   (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Application reset processing
	    { 0, IS_NAME,                       (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Report application name to Manager
	    { 0, IS_STATE,                      (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Return application status (Initialized or not)
	    { 0, IDLE_MESSAGE,                  (SAP)Main, IDLE_HIGH_PRIORITY },     // Service Manager => Dedicated to display idle message
	    { 0, MORE_FUNCTION,                 (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Dedicated to navigation menu
	    { 0, KEYBOARD_EVENT,                (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Return the key pressed
	    { 0, GET_IDLE_STATE_PARAMETER,      (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Gives manager parameters to customize idle state
	    { 0, GIVE_MONEY_EXTENDED,           (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Get the currencies supported by the application
	    { 0, STATE,                         (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Print terminal content
	    { 0, CONSULT,                       (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Print daily totals
	    { 0, MCALL,                         (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Print call schedule
	    { 0, IS_TIME_FUNCTION,              (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Do you need the peripherals at the next call of time_function()?
	    { 0, TIME_FUNCTION,                 (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Dedicated to execute automatic periodic functions
	    { 0, IS_CHANGE_INIT,                (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Conditions for changing Manager parameters?
	    { 0, MODIF_PARAM,                   (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Report Manager parameters changing
	    { 0, IS_EVOL_PG,                    (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Conditions for application downloading?
	    { 0, IS_DELETE,                     (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Conditions for application deletion?
	    { 0, FILE_RECEIVED,                 (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Report Manager parameters file received from LLT
	    { 0, MESSAGE_RECEIVED,              (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Message received from another application inside the mailbox
	    { 0, IS_CARD_SPECIFIC,              (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Do you want to process this specific card?
	    { 0, CARD_INSIDE,                   (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Call after IS_CARD_SPECIFIC to start transaction process
	    { 0, IS_FOR_YOU_BEFORE,             (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Ask application to recognize chip card in order to be a candidate
	    { 0, IS_FOR_YOU_AFTER,              (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Ask application to recognize mag, smart, manually card in order to be a candidate
	    { 0, DEBIT_NON_EMV,                 (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Process a non EMV chip card or Mag stripe or card manual entry transaction (DEBIT)
	    { 0, SELECT_FUNCTION,               (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Process a non EMV chip card or Mag stripe or card manual entry transaction (CREDIT/CANCEL/PRE AUTH)
	    { 0, CUSTOMIZE_MESSAGE,(SAP)customize_message, SERVICES_HIGH_PRIORITY }, // Service Manager => Reserved to customize the manager messages

	};

    for(i=0; i<NUMBER_OF_ITEMS(txServices); i++)
        txServices[i].appli_id = no;

    ServiceRegister(NUMBER_OF_ITEMS(txServices), txServices);

    return FCT_OK;
}

// ***************************************************************************
//                       void entry(void)
/** entry() is called by the OS for recording services and opening DLL(s).                   
 *  The RegisteryPowerFailure() can also be moved to entry().
 * \header sdk30.h
 * \source entry.c 
*/
// ***************************************************************************   
void entry(void)
{
	// Local variables *
    // *****************
	object_info_t xInfo;
	
	// Recording services
	// ******************
	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &xInfo);
	give_interface(xInfo.application_type, NULL, NULL);

	// Open all the external libraries
    // *******************************
	xGoal = GL_GraphicLib_Create(); // Create "graphic library" instance
	SEClib_Open();                  // Security Boster1 & 2 & 3
}

//****************************************************************************
// To open standard peripherals
//****************************************************************************
int OpenPeripherals(void)
{
	// Local variables
    // ***************
	int iRet;

	// Open peripherals
	// ****************
	pxDsp = stdperif("DISPLAY", NULL);      // Check "display" peripheral already opened? (done by Manager)
	if (pxDsp == NULL)                      // No, then open it
	{
		pxDsp = fopen("DISPLAY", "w*");     // Open "display" peripheral
		CHECK(pxDsp!=NULL, lblKO);
	}

	pxPrn = fopen("PRINTER", "w-*");        // Open "printer" peripheral
	CHECK(pxPrn!=NULL, lblKO);

	pxKbd = fopen("KEYBOARD", "r*");        // Open "keyboard" peripheral
	CHECK(pxKbd!=NULL, lblKO);

	if(GL_GraphicLib_IsTouchPresent(xGoal)) // Check if it is a touch screen
	{
		DisplayFooter(_OFF_);               // Remove footer otherwise touch does not work
		pxTsc = fopen("TSCREEN", "r*");     // Open "touch" peripheral
		CHECK(pxTsc!=NULL, lblKO);
	}

	iRet=0;
	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                      // Open peripherals failed
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
// To close standard peripherals
//****************************************************************************
void ClosePeripherals(void)
{
	// Local variables
    // ***************
		// Empty

	// Close peripherals
	// *****************
	if(pxTsc)
	{
		fclose(pxTsc); // Close "touch" peripheral
		pxTsc=NULL;
	}

	if(pxKbd)
	{
        fclose(pxKbd); // Close "keyboard" peripheral
		pxKbd=NULL;
	}

	if(pxPrn)
    {
		fclose(pxPrn); // Close "printer" peripheral
		pxPrn=NULL;
    }

	if(pxDsp)
	{
        fclose(pxDsp); // Close "display" peripheral
        pxDsp=NULL;
	}
}

//****************************************************************************
// To reset standard peripherals
//****************************************************************************
void ResetPeripherals(unsigned int uiEvents)
{
	// Local variables
    // ***************
		// Empty

	// Reset FIFO buffers
	// ******************
	if(((uiEvents & KEYBOARD) == KEYBOARD) && pxKbd) // FIFO keyboard
		reset_buf(pxKbd, _receive_id);

	if(((uiEvents & TSCREEN) == TSCREEN) && pxTsc)   // FIFO touch screen
		reset_buf(pxTsc, _receive_id);

	if(((uiEvents & PRINTER) == PRINTER) && pxPrn)   // FIFO printer
		reset_buf(pxPrn, _receive_id);
}

//****************************************************************************
//                       void SoftwareReset(void)
// This function resets the application parameters with the default values.
//  Then stores the compiler date and time into the table.
// This function has no parameters.
// This function has no return value.
//****************************************************************************

void SoftwareReset(void)
{
	// Local variables
    // ***************
	char tcPath[100];
    doubleword uiMode;  // Bug in prototype => 2nd parameter (output) on FS_mount returns Mode (FS_WRITEONCE or FS_WRITEMANY)
                        // and NOT AccessMode (FS_NOFLAGS or FS_RONLYMOD or FS_WRTMOD)
	 T_GL_COORD sValue;
	int iRet;

	// Software reset in progress
	// **************************
	iRet = GL_Dialog_Message(xGoal, "Software Reset", "No=Cancel / Yes=Valid", GL_ICON_QUESTION, GL_BUTTON_VALID_CANCEL, 30*1000);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd);  // Cancel/Timeout

	// Kill the parameter disk in any case
	sprintf(tcPath, "/%s", PARAM_DISK);
	FS_unmount(tcPath);                                         // Release resources on disk
	FS_dskkill(tcPath);                                         // Disk suppression

	// Create a fresh parameter disk
	iRet = FS_dskcreate(&xCfg, &ulSize);                        // Create and format the none volatile disk
	CHECK(iRet==FS_OK, lblKO);
    iRet = FS_mount(tcPath, &uiMode);                           // Activate a disk
    CHECK(iRet==FS_OK, lblKO);

	iRet = appReset();                                          // Reset application parameters (Flash)
	CHECK(iRet>=0, lblKO);

	iRet = appPut(appCmpDat, (char*)getAppCmpDat(), lenCmpDat); // Store compiler date/time Mapapp.c
	CHECK(iRet>=0, lblKO);
    iRet = appPut(appCmpTim, (char*)getAppCmpTim(), lenCmpTim);
    CHECK(iRet>=0, lblKO);

    GL_Dialog_Progress(xGoal, "Software Reset", "Init Software\nReset In Progress",
    		           NULL, NULL, 0, 100, Progress, GL_BUTTON_NONE, GL_TIME_INFINITE);
    sValue = 100;
    GL_Dialog_Progress(xGoal, "Software Reset", "Init Software\nReset Done",
    		           NULL, &sValue, 1, 101, NULL, GL_BUTTON_NONE, 3*1000);

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:
	GL_Dialog_Message(xGoal, NULL, "Processing Error\nReset Failed", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	return;
}

