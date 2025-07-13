//***************************************************************************
//       INGENICO                                INGEDEV 7
//===========================================================================
//       FILE  ENTRY.C                           (Copyright INGENICO 2008) 
//===========================================================================
//  Created :       12-May-2008     Kassovic
//  Last modified : 12-May-2008     Kassovic
//  Module : CASHREG
//                    
//  Purpose :
//  Each time Manager calls an application, it generates only one service
//  call that reaches your application main with the corresponding service
//  number.
// 
//  List of routines in file :
//      give_your_domain : Return application domain.
//      give_your_specific_context : Return specific context to Manager.
//      after_reset : Application reset processing.
//      is_name : Report application name to Manager.
//      is_state : Return application status (initialize or not).
//      idle_message : Dedicated to display idle message.
//      more_function : Dedicated to navigation menus.
//      keyboard_event : Return key pressed.
//      get_idle_state_parameter : Give manager parameters to customize idle state
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
//      cless_is_specific : Cless card needs a specific process?
//      cless_inside : Transaction in progress for a specific Cless card.
//      cless_give_info : Selection criterion to perform a Cless transaction.
//      cless_is_for_you : Recognize an unknown Cless card in order to be a candidate.
//      cless_debit : Perform the Cless transaction (Debit, Credit, Cancel, Pre Auth).
//      cless_end : To close the Cless transaction.
//      give_interface : Services registration and priority.
//      entry : Call by OS for recording services and opening DLL(s).
// 
//  File history :
//  120508-BK : File created
// 
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "CashReg.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
	/* */

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
// Services priority
// =================
#define SERVICES_LOW_PRIORITY           30   // For all services except idle_message,
#define SERVICES_HIGH_PRIORITY           5   //      priority => 0x00 highest and 0xFF lowest
#define SERVICES_DEFAULT_PRIORITY       20

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
	/* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
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

static const char zAppName[] = "CASHREG";                       // Application name
static const char zColdReset[] = "Cold Reset CASHREG";          // See after_reset() service call
static const char zWarmReset[] = "Warm Reset CASHREG";
static const char zDate[] = "Date:%.2s/%.2s/%.2s  %.2s:%.2s\n"; // See state() service call

T_GL_HGRAPHIC_LIB xGoal=NULL; // New instance of the graphics object library
FILE *pxDsp=NULL;             // Peripheral file Display
FILE *pxPrn=NULL;             // Peripheral file Printer
FILE *pxKbd=NULL;             // Peripheral file Keyboard

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
    param_out->returned_state[param_out->response_number].mask = MSK_ALL_PARAM;  // Accept all

    /* TeliumManager-Initialization-Parameters
    &
    ~MSK_FRMT_DATE &      // Will reject Date format update
    ~MSK_DATE &           // Will reject date and time update
    ~MSK_LANGUE &         // Will reject language update
    ~MSK_NO_TERM &        // Will reject terminal number update
    ~MSK_MONNAIE &        // Will reject currency update
    ~MSK_STANDARD &       // Will reject pabx update
    ~MSK_PINPAD &         // Will reject pinpad update
    ~MSK_SWIPE &          // Will reject swipe update
    ~MSK_NO_SERIE &       // Will reject serial number update
    ~MSK_TYPE_RESEAU &    // Will reject network access update
    ~MSK_CAISSE &         // Will reject cash connection update
    ~MSK_MDP;             // Will reject T.M.S update
    */

    // International domain
	param_out->returned_state[param_out->response_number].application_type = TYP_EXPORT;
	param_out->response_number++;
	
	return FCT_OK;
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
	byte ucChgt, ucType;

    // Initialization
	// **************
	pxDsp = stdperif("DISPLAY", NULL);     // Check "display" peripheral already opened? (done by Manager)
	if (pxDsp == NULL)                     // No, then open it
		pxDsp = fopen("DISPLAY", "w*");    // Open "display" peripheral

	if (pxDsp != NULL)
	{
		// Check if Cold or Warm reset
		// ===========================
		first_init(no, &ucChgt, &ucType);  // New software loaded ?
		if (ucChgt == 0xFF)                // Yes, just loaded with first execution
		{
			GL_Dialog_Message(xGoal, NULL, (char*) zColdReset, GL_ICON_INFORMATION, GL_BUTTON_NONE, 2*1000);
			raz_init(no);                  // Reset indicator downloading
		}
		else                               // No, already loaded and executed
			GL_Dialog_Message(xGoal, NULL, (char*) zWarmReset, GL_ICON_INFORMATION, GL_BUTTON_NONE, 2*1000);

		// Fork a task to listen a cash register
		// =====================================
		ForkListener();

		fclose(pxDsp);                     // Close "display" peripheral
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
 *
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
	int iHeader, iFooter;

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
		pxDsp = fopen("DISPLAY", "w*"); // Open "display" peripheral

	// Display communication settings
	// ******************************
	if (pxDsp != NULL)
	{
		GL_Dialog_Message(xGoal, NULL, "Cash Register\nListener\nCOM5\n115200,N,8,1", GL_ICON_NONE, GL_BUTTON_NONE, 5*1000);
        fclose(pxDsp);                  // Close "display" peripheral
        pxDsp=NULL;
	}

	DisplayLeds(_ON_);                  // Enable Leds
	DisplayHeader(iHeader);             // Restore Header
	DisplayFooter(iFooter);             // Restore Footer

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
	bool bRestart;

    // Return idle configuration to Manager
    // ************************************
	// Support field
	param_out->returned_state[param_out->response_number].no_appli = no;
	param_out->returned_state[param_out->response_number].mask = MSK_NULL;
	param_out->returned_state[param_out->response_number].key = INHIBIT_IDLE_AUTHOR_SELECTION;
	param_out->response_number++;

	// Check if transaction must be restarted due to a IAM message received previously
	// *******************************************************************************
	bRestart = CheckRestartTransaction();

	if (bRestart == TRUE)
		SendToApplication(CASHREG_APPLI_TYPE, 3, 0, NULL); // Send IAM to restart transaction

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
	
	// Print application info
	// **********************
	ObjectGetInfo(OBJECT_TYPE_APPLI, no, &xInfos);      // Retrieve application info

	pxPrn = fopen("PRINTER", "w-*");                    // Open printer driver
	if (pxPrn != NULL) 
	{	
		pprintf("\x1b""E%s\n""\x1b""F", zAppName);      // Print application name
		pprintf("         STATE         \n"
			    "Application used during\n"
			    "SDK training session   \n"
				"Show ServiceCall100\n\n");
		read_date(&xDate);                              // Print date and time
		pprintf(zDate, xDate.day, xDate.month, xDate.year, xDate.hour, xDate.minute);
		pprintf("File    : %s\n", xInfos.file_name);    // Print application file name
		pprintf("CRC     : %04x\n", xInfos.crc);        // Print application CRC
		ttestall(PRINTER, 1*100);	                    // Wait until the end of printing

		fclose(pxPrn);                                  // Close printer driver
		pxPrn=NULL;
	}
	
	return FCT_OK;
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
	byte p;  // Printer line index
	int iHeader, iFooter;
	int iRet;

	// Open peripherals
	// ****************
	iHeader = IsHeader();                // Save header state
	iFooter = IsFooter();                // Save footer state
	if (!IsColorDisplay())               // B&W terminal?
	{                                    // Yes
		DisplayLeds(_OFF_);              // Disable Leds
		DisplayHeader(_OFF_);            // Disable Header
		DisplayFooter(_OFF_);            // Disable Footer
	}

	pxDsp = stdperif("DISPLAY", NULL);   // Check "display" peripheral already opened? (done by Manager)
	if (pxDsp == NULL)                   // No, then open it
	{
		pxDsp = fopen("DISPLAY", "w*");  // Open "display" peripheral
		CHECK(pxDsp!=NULL, lblKO);
	}

	pxPrn = fopen("PRINTER", "w-*");     // Open "printer" peripheral
	CHECK(pxPrn!=NULL, lblKO);

	pxKbd = fopen("KEYBOARD", "r*");     // Open "keyboard" peripheral
	CHECK(pxKbd!=NULL, lblKO);

	// Get message received from TASK
	// ******************************
	if (param_in->type == 1)                                     // *** IAM to start Svc100 received from task ***
	{
		CHECK(param_in->length==16, lblKO);
		iRet =  Svc100Transaction ((char*)param_in->value);
		CHECK(iRet==0, lblKO);
	}

	if (param_in->type == 2)                                     // *** IAM message received from task ***
	{
		xScreen = GoalCreateScreen(xGoal, txScreen, NUMBER_OF_LINES(txScreen), GL_ENCODING_UTF8);
		CHECK(xScreen!=NULL, lblKO);
		iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, 0, false); // Create and clear screen
		CHECK(iRet>=0, lblKO);

		xDspLine = txScreen[0];                                  // Build screen and show it (Appli name, msg received)
		xDspLine.xColor.eTextAlign = GL_ALIGN_CENTER; xDspLine.xColor.ulPen = GL_COLOR_YELLOW;
		xDspLine.xBW.eTextAlign = GL_ALIGN_CENTER;
		iRet = GoalDspLine(xScreen, 0, (char*)zAppName, &xDspLine, 0, false);
		CHECK(iRet>=0, lblKO);
		iRet = GoalDspMultiLine(xScreen, 1, (char*)param_in->value, param_in->length, txScreen, NUMBER_OF_LINES(txScreen), 0, true);
		CHECK(iRet>=0, lblKO);

		p=0;                                                     // Create the document
		xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);
		CHECK(xDocument!=NULL, lblKO);

		xPrnLine = xPrinter;                                     // Build the document (Appli name, IAM message)
		xPrnLine.eTextAlign = GL_ALIGN_CENTER;
		xPrnLine.xFont.eScale = GL_SCALE_XXLARGE;
		iRet = GoalPrnLine(xDocument, p++, (char*)zAppName, &xPrnLine);
		CHECK(iRet>=0, lblKO);
		xPrnLine.eTextAlign = GL_ALIGN_LEFT;
		xPrnLine.xFont.eScale = GL_SCALE_LARGE;
		iRet = GoalPrnLine(xDocument, p++, "Message IAM from Task:", &xPrnLine);
		CHECK(iRet>=0, lblKO);
		strncpy(tcPrint, (char*)param_in->value, param_in->length);
		iRet = GoalPrnLine(xDocument, p++, tcPrint, &xPrnLine);
		CHECK(iRet>=0, lblKO);
		iRet = GoalPrnLine(xDocument, p++, "\n\n\n\n", &xPrnLine);
		CHECK(iRet>=0, lblKO);

		iRet = GoalPrnDocument(xDocument);                       // Print document
		CHECK(iRet>=0, lblKO);

		ttestall(0, 1*100);                                      // Wait to see the message received
	}

	if (param_in->type == 3)                                     // *** IAM to restart Svc100 (See get_idle_state_parameter) ***
	{                                                            // Due to IAM message received during transaction process
		iRet =  Svc100Transaction ((char*)param_in->value);
		CHECK(iRet==0, lblKO);
	}
	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                   // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_NONE, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);     // Destroy screen

	if (xDocument)
		GoalDestroyDocument(&xDocument); // Destroy document

	if(pxKbd)
	{
        fclose(pxKbd);                   // Close "keyboard" peripheral
		pxKbd=NULL;
	}

    if(pxPrn)
    {
		fclose(pxPrn);                   // Close "printer" peripheral
		pxPrn=NULL;
    }

	if(pxDsp)
	{
        fclose(pxDsp);                   // Close "display" peripheral
        pxDsp=NULL;
	}

	DisplayLeds(_ON_);                   // Enable Leds
	DisplayHeader(iHeader);              // Restore Header
	DisplayFooter(iFooter);              // Restore Footer

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
	    { 0, GIVE_YOUR_DOMAIN,           (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Return application domain to Manager
	    { 0, AFTER_RESET,                (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Application reset processing
	    { 0, IS_NAME,                    (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Report application name to Manager
	    { 0, IS_STATE,                   (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Return application status (Initialized or not)
	    { 0, MORE_FUNCTION,              (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Dedicated to navigation menu
	    { 0, GET_IDLE_STATE_PARAMETER,   (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Gives manager parameters to customize idle state
	    { 0, STATE,                      (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Print terminal content
	    { 0, IS_DELETE,                  (SAP)Main, SERVICES_HIGH_PRIORITY }, // Service Manager => Conditions for application deletion?
	    { 0, MESSAGE_RECEIVED,           (SAP)Main, SERVICES_HIGH_PRIORITY }  // Service Manager => Message received from another application inside the mailbox
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
}

