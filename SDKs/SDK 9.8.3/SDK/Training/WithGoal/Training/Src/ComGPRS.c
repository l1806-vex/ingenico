//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  COMGPRS.C                          (Copyright INGENICO 2012)
//============================================================================
//  Created :       11-July-2012     Kassovic
//  Last modified : 11-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                   *** GPRS communication management ***
//  How to use the linklayer to create a GPRS configuration to communicate.
//                   Transmission by GPRS
//               Test done with Hyper-terminal Tcp/Ip Winsock
//  !!! Link Layer application must be loaded 3628xxxx.SGN inside the terminal
//      Supports PPP, TCP/IP and SSL protocols.
//      AVL.lib + LinkLayerExeInterface.lib must be implemented to link properly   
//                                                                            
//  List of routines in file :  
//      GprsReport : Provide the state of the GPRS driver.
//      StartGPRS : Attach to the GPRS network.
//      OpenGPRS : Create the GPRS layer.
//      SetGPRS : Configure the GPRS layer.
//      ConnectGPRS : Connect the GPRS layer.
//      SendGPRS : Send data through the GPRS layer.
//      ReceiveGPRS : Receive data through the GPRS layer.
//      DisconnectGPRS : Disconnect the GPRS layer.                                           
//      CloseGPRS : Delete the GPRS layer.
//      StopGPRS : Break the attachment to the GPRS network.
//      PromptGPRS : Prompt for GPRS's parameters.
//      ComGPRS : GPRS communication demo.
//                            
//  File history :
//  071112-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
// !!! Warning : Functions ONLY supported for Telium 1&2 and will be replaced
// or removed for next products generation Telium 3 coming later
#define _DEPRECATED_DGPRS_SDK96_
// DGPRS_FIOCTL_SET_PIN_MODE_FREE => Enable or disable the automatic PIN
//                                   presentation by the driver
// DGPRS_FIOCTL_SET_PUK_CODE => Present the SIM PUK code.
#include "SDK30.H"
#include "TlvTree.h"
#include "LinkLayer.h"
#include "Training.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern T_GL_HGRAPHIC_LIB xGoal; // New instance of the graphics object library

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define MAX_SND  512
#define MAX_RSP  512

#define GPRS_TIMEOUT  60*100
#define TCPIP_TIMEOUT 30*100

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
   // Empty

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the GPRS screen (Goal)
// ====================================
static const ST_DSP_LINE txGPRS[] =
{
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line0
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line1
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line2
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line3
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT, GL_ALIGN_CENTER, GL_COLOR_WHITE, GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line4
	  {GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} }
};

static T_GL_HWIDGET xScreen=NULL; // Screen handle

// Properties of the default printer (Goal)
// ========================================
static const ST_PRN_LINE xPrinter =
{
	GL_ALIGN_LEFT, GL_ALIGN_CENTER, FALSE, 100, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {1, 0, 1, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_LARGE}
};

// Dialog choice
// =============
static const char *tzRequirePin[] =
{
	"Yes",
	"No",
	NULL
};

static LL_HANDLE tvSession[1] = {NULL}; // Session handle

// Tlv tree nodes
// ==============
static TLV_TREE_NODE piConfig=NULL;
static TLV_TREE_NODE piPhysicalConfig=NULL;
static TLV_TREE_NODE piTransportConfig=NULL;

//****************************************************************************
//                   int GprsReport (char *pcApn, char *pcUserName)
//  This function provides the state of the GPRS driver.
//  The state of the GPRS driver includes the "start report" and the
//  "sim status", these informations are displayed on screen to show the
//  progress.
//  A low level "fioctl" function should be used (DGPRS_FIOCTL_GET_INFORMATION)
//  to get the information on a structure.
//  A second low level "fioctl" function is also used (DGPRS_FIOCTL_SET_PIN_MODE_FREE)
//  to ask for the pin entry each time the terminal has been switched off.
//   - LL_GPRS_Start() : Start GPRS modem and enable facility
//  This function has parameters.
//    pcApn (I-) : Gprs Apn string (max 30 bytes)
//    pcUsername (I-) : Gprs Username string (max 30 bytes)
//  This function has return value
//    >=0 : Report done
//     <0 : Report failed
//****************************************************************************

static int GprsReport(char *pcApn, char *pcUsername)
{
	// Local variables
    // ***************
    FILE *pxGprs = NULL;
    char tcMask[256];
    int iRequirePin;
	char tcRequirePin[lenGprsRequirePin+1]; // Pin required ?
	char tcPin[lenGprsPin+1];
	char tcPin1[lenGprsPin+1];
	char tcPuk[lenGprsPuk+1];
	char tcCmd[lenGprsPin+lenGprsPuk+1+1];  // (+1 for comma, +1 for end string)
    char tcReport[25+1], tcStatus[25+1];
    T_DGPRS_GET_INFORMATION xInfo;
    int i, iRet;

	// Get state of GPRS driver
	// ************************
    pxGprs = stdperif((char*)"DGPRS", NULL);
	CHECK(pxGprs!=NULL, lblKO);

	iRet = appGet(appGprsRequirePin, tcRequirePin, lenGprsRequirePin+1);
	CHECK(iRet>=0, lblKO);

	iRequirePin=atoi(tcRequirePin); // False => 0 (pin required), True => 1 (pin saved)
	iRet = fioctl(DGPRS_FIOCTL_SET_PIN_MODE_FREE, &iRequirePin, pxGprs);
	CHECK(iRet==0, lblKO);

	iRet = fioctl(DGPRS_FIOCTL_GET_INFORMATION, &xInfo, pxGprs);
	CHECK(iRet==0, lblKO);

	// GPRS start report
	// =================
	switch (xInfo.start_report)
	{
	case DGPRS_REPORT_NOT_RECEIVED_YET: strcpy(tcReport, "Rpt: NOT_RECEIVED_YET"); break;
	case DGPRS_REPORT_READY:            strcpy(tcReport, "Rpt: READY");            break;
	case DGPRS_REPORT_WAITING_CODE:     strcpy(tcReport, "Rpt: WAITING_CODE");     break;
	case DGPRS_REPORT_SIM_NOT_PRESENT:  strcpy(tcReport, "Rpt: SIM_NOT_PRESENT");  break;
	case DGPRS_REPORT_SIMLOCK_STATE:    strcpy(tcReport, "Rpt: SIMLOCK_STATE");    break;
	case DGPRS_REPORT_FATAL_ERROR:      strcpy(tcReport, "Rpt: FATAL_ERROR");      break;
	default:                            strcpy(tcReport, "Rpt: UNKNOWN_ERROR");    break;
	}

	// GPRS sim status
	// ===============
	switch (xInfo.sim_status)
	{
	case DGPRS_SIM_NOT_RECEIVED_YET:
		strcpy(tcStatus, "Sta: NOT_RECEIVED_YET");

		// *** Start GSM session ***
		iRet = LL_GSM_Start(NULL);
		CHECK(iRet==LL_ERROR_OK, lblKO);

		break;
	case DGPRS_SIM_OK:                                         // Sim ready, pin already checked
		strcpy(tcStatus, "Sta: SIM_OK");

		// *** Start GPRS session ***
		iRet = LL_GPRS_Start(NULL, pcApn);
	    CHECK(iRet==LL_ERROR_OK, lblKO);

		iRet = GoalDspLine(xScreen, 4, "CONNECT. IN PROGRESS", &txGPRS[4], 0, true);
		CHECK(iRet>=0, lblKO);
		break;
	case DGPRS_SIM_KO:                  strcpy(tcStatus, "Sta: SIM_KO"); break;
	case DGPRS_SIM_PIN_REQUIRED:                              // Pin required, enter it
		strcpy(tcStatus, "Sta: PIN_REQUIRED");

		// *** Enter Pin code ***
		memset(tcMask, 0, sizeof(tcMask));
		for (i=0; i<lenGprsPin; i++)
			strcat(tcMask, "/d");                             // Accept only decimal character
		memset (tcPin, 0, sizeof(tcPin));
		iRet = GL_Dialog_Password(xGoal, "Pin Code", "Enter Pin :", tcMask, tcPin, sizeof(tcPin), GL_TIME_MINUTE);
		if ((iRet==GL_KEY_CANCEL) || (iRet==GL_RESULT_INACTIVITY))
			iRet=0;                                           // Exit on cancel/timeout
		CHECK(iRet!=0, lblEnd);

		// *** Start GSM session ***
		iRet = LL_GSM_Start(tcPin[0] ? tcPin : NULL);
		CHECK(iRet==LL_ERROR_OK, lblKO);

		// *** Start GPRS session ***
		iRet = LL_GPRS_Start(tcPin[0] ? tcPin : NULL, pcApn);
	    CHECK(iRet==LL_ERROR_OK, lblKO);

		iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false); // Clear screen
		CHECK(iRet>=0, lblKO);
		iRet = GoalDspLine(xScreen, 0, "1-comStart...", &txGPRS[0], 0, false);
		CHECK(iRet>=0, lblKO);
		iRet = GoalDspLine(xScreen, 1, pcUsername, &txGPRS[1], 0, false); // Show user name
		CHECK(iRet>=0, lblKO);
		iRet = GoalDspLine(xScreen, 4, "CONNECT. IN PROGRESS", &txGPRS[4], 0, true);
		CHECK(iRet>=0, lblKO);
	    break;
	case DGPRS_SIM_PIN2_REQUIRED:       strcpy(tcStatus, "Sta: PIN2 REQUIRED"); break;
	case DGPRS_SIM_PIN_ERRONEOUS:                             // Wrong Pin, enter it
		strcpy(tcStatus, "Sta: PIN ERRONEOUS   ");

		// *** Enter Pin code ***
		memset(tcMask, 0, sizeof(tcMask));
		for (i=0; i<lenGprsPin; i++)
			strcat(tcMask, "/d");                             // Accept only decimal character
		memset (tcPin, 0, sizeof(tcPin));
		iRet = GL_Dialog_Password(xGoal, "Pin Code", "Enter Pin :", tcMask, tcPin, sizeof(tcPin), GL_TIME_MINUTE);
		if ((iRet==GL_KEY_CANCEL) || (iRet==GL_RESULT_INACTIVITY))
			iRet=0;                                           // Exit on cancel/timeout
		CHECK(iRet!=0, lblEnd);

		// *** Start GSM session ***
		LL_GSM_Start(tcPin[0] ? tcPin : NULL);

		// *** Start GPRS session ***
		iRet = LL_GPRS_Start(tcPin[0] ? tcPin : NULL, pcApn);
	    CHECK(iRet==LL_ERROR_OK, lblKO);

		iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false); // Clear screen
		CHECK(iRet>=0, lblKO);
		iRet = GoalDspLine(xScreen, 0, "1-comStart...", &txGPRS[0], 0, false);
		CHECK(iRet>=0, lblKO);
		iRet = GoalDspLine(xScreen, 1, pcUsername, &txGPRS[1], 0, false); // Show user name
		CHECK(iRet>=0, lblKO);
		iRet = GoalDspLine(xScreen, 4, "CONNECT. IN PROGRESS", &txGPRS[4], 0, true);
		CHECK(iRet>=0, lblKO);
		break;
	case DGPRS_SIM_NOT_INSERTED:        strcpy(tcStatus, "Sta: SIM_NOT_INSERTED"); break;
	case DGPRS_SIM_PUK_REQUIRED:                               // Puk required, enter it
		strcpy(tcStatus, "Sta: PUK_REQUIRED    ");

		// *** Enter Puk code ***
		memset(tcMask, 0, sizeof(tcMask));
		for (i=0; i<lenGprsPuk; i++)
			strcat(tcMask, "/d");                              // Accept only decimal character
		memset (tcPuk, 0, sizeof(tcPuk));
		iRet = GL_Dialog_Password(xGoal, "Puk Code", "Enter Puk :", tcMask, tcPuk, sizeof(tcPuk), GL_TIME_MINUTE);
		if ((iRet==GL_KEY_CANCEL) || (iRet==GL_RESULT_INACTIVITY))
			iRet=0;                                            // Exit on cancel/timeout
		CHECK(iRet!=0, lblEnd);

		// *** Enter new Pin code and confirm ***
		do
		{
			// *** Enter new Pin code ***
			memset(tcMask, 0, sizeof(tcMask));
			for (i=0; i<lenGprsPin; i++)
				strcat(tcMask, "/d");                          // Accept only decimal character
			memset (tcPin1, 0, sizeof(tcPin1));                // Enter new Pin
			iRet = GL_Dialog_Password(xGoal, "New Pin Code", "Enter New Pin :", tcMask, tcPin1, sizeof(tcPin1), GL_TIME_MINUTE);
			if ((iRet==GL_KEY_CANCEL) || (iRet==GL_RESULT_INACTIVITY))
				iRet=0;                                        // Exit on cancel/timeout
			CHECK(iRet!=0, lblEnd);
			// *** Confirm new Pin code ***
			memset (tcPin, 0, sizeof(tcPin));                  // Confirm new Pin
			iRet = GL_Dialog_Password(xGoal, "New Pin Code", "Confirm New Pin :", tcMask, tcPin, sizeof(tcPin), GL_TIME_MINUTE);
			if ((iRet==GL_KEY_CANCEL) || (iRet==GL_RESULT_INACTIVITY))
				iRet=0;                                        // Exit on cancel/timeout
			CHECK(iRet!=0, lblEnd);
		} while (memcmp(tcPin1, tcPin, lenGprsPin) != 0);

		sprintf(tcCmd, "%s,%s", tcPuk, tcPin);
		iRet = fioctl(DGPRS_FIOCTL_SET_PUK_CODE, tcCmd, pxGprs);
		if (iRet == 0)                                         // Puk code OK
		{
			ttestall(0, 1*100);                                // Wait a little bit before restarting a session

			// *** Start GSM session ***
			LL_GSM_Start(tcPin[0] ? tcPin : NULL);

			// *** Start GPRS session ***
			iRet = LL_GPRS_Start(tcPin[0] ? tcPin : NULL, pcApn);
			CHECK(iRet==LL_ERROR_OK, lblKO);
		}

		iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false); // Clear screen
		CHECK(iRet>=0, lblKO);
		iRet = GoalDspLine(xScreen, 0, "1-comStart...", &txGPRS[0], 0, false);
		CHECK(iRet>=0, lblKO);
		iRet = GoalDspLine(xScreen, 1, pcUsername, &txGPRS[1], 0, false); // Show user name
		CHECK(iRet>=0, lblKO);
		iRet = GoalDspLine(xScreen, 4, "CONNECT. IN PROGRESS", &txGPRS[4], 0, true);
		CHECK(iRet>=0, lblKO);
		break;
	case DGPRS_SIM_PUK2_REQUIRED: 		strcpy(tcStatus, "Sta: PUK2_REQUIRED"); break;
	case DGPRS_SIM_PIN_PRESENTED:       strcpy(tcStatus, "Sta: PIN_PRESENTED"); break;
	default:                            strcpy(tcStatus, "Sta: UNKNOWN_ERROR"); break;
	}

	iRet = GoalDspLine(xScreen, 2, tcReport, &txGPRS[2], 0, true); // Show start report
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 3, tcStatus, &txGPRS[3], 0, true); // Show sim status
	CHECK(iRet>=0, lblKO);

	iRet=1;
    goto lblEnd;

	// Errors treatment
    // ****************
lblKO:
    iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//                   int StartGPRS (const char *pcInit)                            
//  This function handles the attachment to the GPRS network.
//   - LL_GPRS_Connect() : Connect the GPRS network
//   - LL_Network_GetStatus() : Return current status of the network
//  This function has parameters.  
//    pcInit (I-) : 
//           Apn          = a string (max 30 bytes)
//           Username     = a string (max 30 bytes)
//           Password     = a string (max 30 bytes)
//           The '|' is the separator
//           Ex: "1234|internet-entreprise|orange|orange     
//  This function has return value
//    >=0 : Attachment done
//     <0 : Attachment failed
//****************************************************************************

static int StartGPRS(const char *pcInit) 
{
	// Local variables 
    // ***************
    char tcApn[lenGprsApn+1];       // Apn
    char tcUsername[lenGprsUser+1]; // Login
    char tcPassword[lenGprsPass+1]; // Password
    int iKey;
    word usTimeOut=0;
    bool bExit=TRUE;
    int iStatus, iRet;

    // Network GPRS parameters
    // ************************
    if (*pcInit)
    {
    	memset(tcApn, 0, sizeof(tcApn));                                
    	pcInit = parseStr('|', tcApn, pcInit, sizeof(tcApn));           // Extract apn
        CHECK(pcInit!=NULL, lblKOConfigure);
    
        memset(tcUsername, 0, sizeof(tcUsername));
        pcInit = parseStr('|', tcUsername, pcInit, sizeof(tcUsername)); // Extract username
        CHECK(pcInit!=NULL, lblKOConfigure);

        memset(tcPassword, 0, sizeof(tcPassword));
        pcInit = parseStr('|', tcPassword, pcInit, sizeof(tcPassword)); // Extract password
        CHECK(pcInit!=NULL, lblKOConfigure);
    }
    else
		goto lblKOConfigure;                                            // Configuration error

    // Connect the GPRS network
    // ************************
    ResetPeripherals(KEYBOARD | TSCREEN);           // Reset peripherals FIFO
    do
    {
    	iRet = GprsReport(tcApn, tcUsername);
    	CHECK(iRet>=0, lblKOConfigure);
    	CHECK(iRet!=0, lblEnd);                     // Exit on cancel/timeout

    	iRet = LL_GPRS_Connect(tcApn, tcUsername, tcPassword, 10*100);
    	switch (iRet)
    	{
    	//case LL_ERROR_NETWORK_NOT_READY:
    	//	bExit = FALSE;
    	//	break;
    	case LL_ERROR_ALREADY_CONNECTED:
    	case LL_ERROR_OK:
    		iRet = GoalDspLine(xScreen, 4, "GPRS CONNECTED!!!", &txGPRS[4], 0, true);
    		CHECK(iRet>=0, lblKOConfigure);        // Show Gprs connected
        	buzzer(10);
    		iRet = 1;
    		bExit=TRUE;
    		break;
    	case LL_ERROR_NETWORK_NOT_SUPPORTED:
    	case LL_ERROR_SERVICE_CALL_FAILURE:
            bExit = TRUE;
    		break;
    	default:                                   // LL_ERROR_NETWORK_NOT_READY or LL_ERROR_NETWORK_ERROR
        	iRet = LL_Network_GetStatus(LL_PHYSICAL_V_GPRS, &iStatus);
    		switch (iStatus)                       // Check network status
    		{
    		case LL_STATUS_GPRS_ERROR_SIM_LOCK:    // Pin locked => Wait Puk
    		case LL_STATUS_GPRS_ERROR_BAD_PIN:     // Wrong Pin => Wait Pin
    		case LL_STATUS_GPRS_ERROR_NO_PIN:      // Pin required => Wait Pin
    		case LL_STATUS_GPRS_CONNECTING:        // Connection to GPRS Network in progress
    		case LL_STATUS_GPRS_AVAILABLE:         // GPRS Network is available
    		case LL_STATUS_GPRS_CONNECTING_PPP:    // PPP connection is in progress with the GPRS provider
    		case LL_STATUS_GPRS_DISCONNECTED:      // Disconnection to GPRS Network, let's retry a connection
    		case 0x2000600:                        // Wait until network ready
    			bExit = FALSE;
    			break;
    		case LL_STATUS_GPRS_CONNECTED:
        		iRet = GoalDspLine(xScreen, 4, "GPRS CONNECTED!!!", &txGPRS[4], 0, true);
        		CHECK(iRet>=0, lblKOConfigure);    // Show Gprs connected
            	buzzer(10);
        		iRet = 1;
        		bExit=TRUE;
    			break;
    		case LL_STATUS_GPRS_ERROR_NO_SIM:      // No SIM card is inserted into the terminal
    		case LL_STATUS_GPRS_ERROR_PPP:         // Error occurred during the PPP link establishment.
    		case LL_STATUS_GPRS_ERROR_UNKNOWN:     // Error status unknown
    		default:
				bExit = TRUE;
    			break;          
    		}

    		if (!bExit)                            // Keyboard and timeout management
    		{
    			iKey = GoalGetKey(xScreen, xGoal, true, 1*1000, false); // Get key pressed/touched (shortcut)

    			usTimeOut += 1*100;                // Increment timeout
    		}
    	}
    } while (!bExit && (usTimeOut < GPRS_TIMEOUT) && (iKey!=GL_KEY_CANCEL));

    if ((usTimeOut==GPRS_TIMEOUT) || (iKey==GL_KEY_CANCEL))             // Exit on timeout/cancel
    	iRet=0;

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKOConfigure:
    iRet=LL_ERROR_INVALID_PARAMETER;
lblEnd:
	return iRet;
}

//****************************************************************************
//                   LL_HANDLE* OpenGPRS (void)
//  This function creates the handle of the GPRS layer.      
//  This function has no parameter.
//  This function has return value
//    !NULL : Pointer to the handle configuration.
//    NULL : Processing failed                                        
//****************************************************************************

static LL_HANDLE* OpenGPRS(void)
{
    return tvSession;
}

//****************************************************************************
//                        void SetGPRS (void)
//  This function configures the GPRS layer.      
//  This function has no parameter.
//  This function has no return value
//****************************************************************************

static void SetGPRS(void)
{
	// Local variables 
    // ***************
       // Empty
    
	// Create the LinkLayer configuration parameters tree 
	// **************************************************

    // Create parameters tree
    // ======================
    piConfig = TlvTree_New(LL_TAG_LINK_LAYER_CONFIG);                  // LinkLayer parameters Root tag of the configuration tree
    
    // Physical layer parameters
	// =========================
	piPhysicalConfig = TlvTree_AddChild(piConfig,                        
		                                LL_TAG_PHYSICAL_LAYER_CONFIG,  // TAG Physical layer parameters
									    NULL,                          // VALUE (Null)
									    0);                            // LENGTH 0

	// GPRS
	// ----
    TlvTree_AddChildInteger(piPhysicalConfig, 
		                    LL_PHYSICAL_T_LINK,                        // TAG
							LL_PHYSICAL_V_GPRS,                        // VALUE
							LL_PHYSICAL_L_LINK);                       // LENGTH 1
}

//****************************************************************************
//              int ConnectGPRS (const char *pcServer)                            
//  This function connects the GPRS layer.      
//   - LL_Configure() : Create Link Layer configuration
//   - LL_Connect() : Connect Link Layer
//  This function has parameters.  
//    pcServer (I-) : Tcp/Ip address and port number
//           IpAddress = xxx.xxx.xxx.xxx or url
//           PortNumber = a string (max 5 bytes)
//           The '|' is the separator
//           Ex: "192.168.1.3|2000     
//  This function has return value
//    >=0 : Connect done
//     <0 : Connect failed                                        
//****************************************************************************

static int ConnectGPRS(const char *pcServer) 
{
	// Local variables 
    // ***************
    char tcAddr[lenGprsIpRemote+1];
    char tcPort[lenGprsPort+1];
	doubleword uiTimeout, uiRemotePort;
    int iRet=0;

	// LinkLayer configuration parameters tree 
	// ***************************************
        
	// Transport and network layer parameters
	// ======================================
	piTransportConfig = TlvTree_AddChild(piConfig, 
		                                 LL_TAG_TRANSPORT_LAYER_CONFIG, // TAG Transport layer parameters
										 NULL,                          // VALUE (Null)
										 0);                            // LENGTH 0
    if(*pcServer)               
    {
    	memset(tcAddr, 0, sizeof(tcAddr));
		pcServer = parseStr('|', tcAddr, pcServer, sizeof(tcAddr));     // Parse Tcp/Ip address
        CHECK(pcServer!=NULL, lblKOConfigure);

        memset(tcPort, 0, sizeof(tcPort));
        pcServer = parseStr('|', tcPort, pcServer, sizeof(tcPort));     // Parse Tcp/Ip port
        CHECK(pcServer!=NULL, lblKOConfigure);
    } 
	else
		goto lblKOConfigure;                                            // Configuration error

	// TCP/IP
	// ------
	TlvTree_AddChildInteger(piTransportConfig, 
		                    LL_TRANSPORT_T_PROTOCOL,                    // TAG
							LL_TRANSPORT_V_TCPIP,                       // VALUE
							LL_TRANSPORT_L_PROTOCOL);                   // LENGTH 1 byte

	// Host Name
	// ---------
	TlvTree_AddChildString(piTransportConfig,
		                   LL_TCPIP_T_HOST_NAME,                        // TAG         
                           tcAddr);                                     // VALUE
                                                                        // LENGTH (strlen addr)
	
	// Port
	// ----
	uiRemotePort = atoi (tcPort);
	TlvTree_AddChildInteger(piTransportConfig, 
		                    LL_TCPIP_T_PORT,                            // TAG
							uiRemotePort,                               // VALUE (Integer)
							LL_TCPIP_L_PORT);                           // LENGTH 4 bytes



	// Connection timeout
	// ------------------
	uiTimeout = TCPIP_TIMEOUT;                                        
    TlvTree_AddChildInteger(piTransportConfig,         
                            LL_TCPIP_T_CONNECT_TIMEOUT,                 // TAG
	                        uiTimeout,                                  // Value (Integer)
                            LL_TCPIP_L_CONNECT_TIMEOUT);                // LENGTH 4 bytes

	// Link Layer configuration
	// ************************
    iRet = LL_Configure(tvSession, piConfig);
	CHECK (iRet==LL_ERROR_OK, lblKOConfigure); 

	// Release the LinkLayer configuration parameters tree
	// ***************************************************
	TlvTree_Release(piConfig);

    // Link Layer connection
	// *********************
    iRet = LL_Connect(tvSession[0]);

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKOConfigure:
	TlvTree_Release(piConfig);
lblEnd:
	return iRet;
}

//****************************************************************************
//              int SendGPRS (const char *pcMsg, word usLen)
//  This function sends data through the GPRS layer.      
//   - LL_Send() : Send data
//   - LL_GetLastError() : Retrieve the last error
//  This function has parameters.  
//    pcMsg (I-) : Data to send
//    usLen (I-) : Number of byte to send
//  This function has return value
//    >=0 : Number of bytes sent
//     <0 : Transmission failed                                       
//****************************************************************************

static int SendGPRS(const char *pcMsg, word usLen)
{
	// Local variables 
    // ***************
    int iRet;
    
	// Send data
	// *********
    iRet = LL_Send(tvSession[0], usLen, (byte*)pcMsg, LL_INFINITE);
    if(iRet != usLen)
		iRet = LL_GetLastError(tvSession[0]);

    return iRet;
}

//****************************************************************************
//          int ReceiveGPRS (char *pcMsg, word usLen, byte ucDly)
//  This function receives data through the GPRS layer.      
//   - LL_ClearReceiveBuffer() : Clear receiving buffer
//   - LL_Receive() : Wait and receive data
//   - LL_GetLastError() : Retrieve the last error
//  This function has parameters.  
//     pcMsg (-O) : Data to receive
//     usLen (I-) : Maximum number of bytes to receive
//     ucDly (I-) : Timeout reception (in second, 0xFF infinite)
//  This function has return value
//    >=0 : Number of bytes received
//     <0 : Reception failed                                       
//****************************************************************************

static int ReceiveGPRS(char *pcMsg, word usLen, byte ucDly)
{
	// Local variables 
    // ***************
	int iKey;
    int iRet, iLength=0, iTimeOut=LL_INFINITE, iSec, iNbrBytes;

	// Timeout setting
	// ***************
    if(ucDly != 0xFF)  
        iSec = ucDly*100;
	else
		iSec = LL_INFINITE;

	// Receiving first block
	// *********************
	ResetPeripherals(KEYBOARD | TSCREEN);                                  // Reset peripherals FIFO
    iRet = TimerStart(0, iSec);                                            // Timer0 starts
    CHECK(iRet>=0, lblTimeOut);
	do
    {
    	iNbrBytes = LL_Receive(tvSession[0], usLen, pcMsg+iLength, 1*100); // Check reception
    	if (iNbrBytes != 0)
    		break;                                                         // Bytes received
		iKey = GoalGetKey(xScreen, xGoal, true, 0, false);                 // Get key pressed/touched (shortcut)
		CHECK(iKey!=GL_KEY_CANCEL, lblTimeOut);                            // Exit on cancel key
		if (iSec != LL_INFINITE)
			iTimeOut = TimerGet(0);                                        // Retrieve timer value
    } while (iTimeOut>0);

    CHECK(iTimeOut!=0, lblTimeOut);                                        // Exit on timeout

	iLength += iNbrBytes;
	iRet = LL_GetLastError(tvSession[0]);
	CHECK (iRet==LL_ERROR_OK, lblEnd);
	if (iNbrBytes != 0)
	{
		// Receiving next block until timeout (Inter block 2s)
		// ===================================================
		while(1)
		{
			iNbrBytes = LL_Receive(tvSession[0], usLen-iLength, pcMsg+iLength, 2*100);
			iLength += iNbrBytes;
			iRet = LL_GetLastError(tvSession[0]);
			CHECK ((iRet==LL_ERROR_OK) || (iRet==LL_ERROR_TIMEOUT), lblEnd);
			if ((iRet==LL_ERROR_TIMEOUT) || (iNbrBytes==0))
				break;
		}
	}

	iRet = iLength;
    goto lblEnd;

	// Errors treatment 
    // ****************	
lblTimeOut:
	iRet = LL_ERROR_TIMEOUT;
lblEnd:
	TimerStop(0);
    return iRet;
}

//****************************************************************************
//                   int DisconnectGPRS (void)                            
//  This function disconnects the GPRS layer.      
//   - LL_Disconnect() : Disconnect Link Layer
//  This function has no parameters.  
//  This function has return value
//    >=0 : Disconnect done
//     <0 : Disconnect failed                                       
//****************************************************************************

static int DisconnectGPRS(void) 
{	
	// Local variables 
    // ***************
	int iRet;

	// Link Layer disconnection
	// ************************
	iRet = LL_Disconnect(tvSession[0]);
	
	return iRet;
}

//****************************************************************************
//                        int CloseGPRS (void)                            
//  This function deletes the handle of the GPRS layer.   
//   - LL_Configure() : Delete Link Layer configuration
//  This function has no parameters.  
//  This function has return value
//    >=0 : Configuration deleted
//     <0 : Processing failed                                        
//****************************************************************************

static int CloseGPRS(void)
{
	// Local variables 
    // ***************
    int iRet;

	// Delete the configuration
	// ************************
    iRet = LL_Configure(tvSession, NULL);

    return iRet;
}

//****************************************************************************
//                        int StopGPRS (void)                            
//  This function breaks the attachment to the GPRS network.
//   - LL_GPRS_Stop() : Disconnect the GPRS network
//  This function has no parameters.  
//  This function has return value
//    >=0 : Break attachment done
//     <0 : Break attachment failed
//****************************************************************************

static int StopGPRS(void)
{
	// Local variables 
    // ***************
    int iRet;
	
	// GPRS disconnection
	// ******************
	iRet = LL_GPRS_Stop();
	
	return iRet;
}

//****************************************************************************
//                      void PromptGPRS (void)                            
//  This function asks for the GPRS's parameters.   
//  This function has no parameters.  
//  This function has no return value
//****************************************************************************

void PromptGPRS(void)
{
	// Local variables 
    // ***************
	char tcMask[256];
    char tcRequirePin[lenGprsRequirePin+1];
    char tcApnN[lenGprsApn+1], tcApnP[lenGprsApn+1];
    char tcUserN[lenGprsUser+1], tcUserP[lenGprsUser+1];
    char tcPassN[lenGprsPass+1], tcPassP[lenGprsPass+1];
	char tcIpAddressN[lenGprsIpRemote+1], tcIpAddressP[lenGprsIpRemote+1];
	char tcPortN[lenGprsPort+1], tcPortP[lenGprsPort+1];
	doubleword uiIp;
	char tcDisplay[50+1];
	int iHeader, iFooter;
	int i, iDefItemP, iDefItemN, iRet;

    // Pin Required ?
    // **************
	iRet = appGet(appGprsRequirePin, tcRequirePin, lenGprsRequirePin+1);
	CHECK(iRet>=0, lblDbaErr);
	iDefItemP = atoi(tcRequirePin);
	iDefItemN = GL_Dialog_Choice(xGoal, "Pin Required?", tzRequirePin, iDefItemP, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE);
	CHECK((iDefItemN!=GL_KEY_CANCEL) && (iDefItemN!=GL_RESULT_INACTIVITY), lblEnd); // Exit cancel/timeout
	if (iDefItemN != iDefItemP)
	{
		tcRequirePin[0] = iDefItemN + 0x30;
		iRet = appPut(appGprsRequirePin, tcRequirePin, lenGprsRequirePin); // Save pin required
		CHECK(iRet>=0, lblDbaErr);
	}

	// Enter APN 
	// *********
	iHeader = IsHeader();                                                  // Save header state
	iFooter = IsFooter();                                                  // Save footer state

	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenGprsApn; i++)
		strcat(tcMask, "/c");                                              // Accept any character
	iRet = appGet(appGprsApn, tcApnP, lenGprsApn+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcApnN, tcApnP);

	DisplayLeds(_OFF_);                                                    // Disable Leds
	DisplayHeader(_OFF_);                                                  // Disable Header
	DisplayFooter(_OFF_);                                                  // Disable Footer

	iRet = GL_Dialog_VirtualKeyboard(xGoal, NULL, "Enter Apn :", tcMask, tcApnN, sizeof(tcApnN), GL_TIME_MINUTE);

	if (IsColorDisplay())                                                  // Color terminal?
	{                                                                      // Yes
		DisplayLeds(_ON_);                                                 // Enable Leds
		DisplayHeader(iHeader);                                            // Enable Header
		if(!GL_GraphicLib_IsTouchPresent(xGoal))                           // Check if it is a touch screen
			DisplayFooter(iFooter);                                        // No, restore Footer
	}

	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd);  // Exit on cancel/timeout
	if (strcmp(tcApnN, tcApnP) != 0)
	{
		iRet = appPut(appGprsApn, tcApnN, lenGprsApn);                     // Save new apn
		CHECK(iRet>=0, lblDbaErr);
	}
		
	// Enter User Name 
	// ***************
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenGprsUser; i++)
		strcat(tcMask, "/c");                                              // Accept any character
	iRet = appGet(appGprsUser, tcUserP, lenGprsUser+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcUserN, tcUserP);
	iRet = GL_Dialog_Text(xGoal, "User Name", "Enter User Name :", tcMask, tcUserN, sizeof(tcUserN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd);  // Exit on cancel/timeout
	if (strcmp(tcUserN, tcUserP) != 0)
	{
		iRet = appPut(appGprsUser, tcUserN, lenGprsUser);                  // Save new user name
		CHECK(iRet>=0, lblDbaErr);
	}

	// Enter Password 
	// **************
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenGprsPass; i++)
		strcat(tcMask, "/c");                                              // Accept any character
	iRet = appGet(appGprsPass, tcPassP, lenGprsPass+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcPassN, tcPassP);
	iRet = GL_Dialog_Password(xGoal, "Password", "Enter Password :", tcMask, tcPassN, sizeof(tcPassN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd);  // Exit on cancel/timeout
	if (strcmp(tcPassN, tcPassP) != 0)
	{
		iRet = appPut(appGprsPass, tcPassN, lenGprsPass);                  // Save new password
		CHECK(iRet>=0, lblDbaErr);
	}
			
    // Enter Remote IP address
    // ***********************
	iRet = appGet(appGprsIpRemote, tcIpAddressP, lenGprsIpRemote+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcIpAddressN, tcIpAddressP);
	uiIp = IpToUint(tcIpAddressN);                                         // Convert Ip address to unsigned int
	CHECK(uiIp>=0, lblKO);
	iRet = GL_Dialog_Ip(xGoal, "Remote Ip Address", "Enter Ip Address :", (T_GL_HIP)&uiIp, GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd);  // Exit on cancel/timeout
	strcpy(tcIpAddressN, UintToIp(uiIp));                                  // Convert unsigned int to Ip address
	if (strcmp(tcIpAddressN, tcIpAddressP) != 0)
	{
		iRet = appPut(appGprsIpRemote, tcIpAddressN, lenGprsIpRemote);     // Save new Ip address
		CHECK(iRet>=0, lblDbaErr);
	}
	
	// Enter Port number 
	// *****************
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenGprsPort; i++)
		strcat(tcMask, "/d");                                              // Accept only decimal character
	iRet = appGet(appGprsPort, tcPortP, lenGprsPort+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcPortN, tcPortP);
	iRet = GL_Dialog_Text(xGoal, "Port Number", "Enter Port# :", tcMask, tcPortN, sizeof(tcPortN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd);  // Exit on cancel/timeout
	if (strcmp(tcPortN, tcPortP) != 0)
	{
		iRet = appPut(appGprsPort, tcPortN, lenGprsPort);                  // Save new Port number
		CHECK(iRet>=0, lblDbaErr);
	}

	goto lblEnd;

	// Errors treatment 
	// ****************
lblKO:                                                                     // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblDbaErr:                                                                 // Data base error
	sprintf(tcDisplay, "%s\n%s", FMG_ErrorMsg(iRet), "Software Reset Needed");
	GL_Dialog_Message(xGoal, NULL, tcDisplay, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
    return;
}

//****************************************************************************
//                      void ComGPRS (void)                            
//  This function communicates through the GPRS layer.   
//  This function has no parameters.
//  This function has no return value
//****************************************************************************

void ComGPRS(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xLine;
    LL_HANDLE *pvCom=NULL;
	char *pcStr, tcStr[128+1];
	char tcUser[lenGprsUser+1];
	char tcIpAddress[lenGprsIpRemote+1];
	char tcPort[lenGprsPort+1];
    char tcSnd[MAX_SND+1];
    char tcRsp[MAX_RSP+1];
    char tcDisplay[50+1];
    byte p;
	int iRet=0, iStatus=0;

	xScreen = GoalCreateScreen(xGoal, txGPRS, NUMBER_OF_LINES(txGPRS), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                                    // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);

	// Attachment to the GPRS network in progress
	// ******************************************
	iRet = GoalDspLine(xScreen, 0, "1-comStart...", &txGPRS[0], 0, true);
	CHECK(iRet>=0, lblKO);
	pcStr = tcStr;                                                  // Build param string
	iRet = appGet(appGprsApn, pcStr, lenGprsApn+1);                 // Retrieve apn
	CHECK(iRet>=0, lblDbaErr);
	pcStr += strlen(pcStr);
	*pcStr = '|'; pcStr++;
	iRet = appGet(appGprsUser, pcStr, lenGprsUser+1);               // Retrieve username
	CHECK(iRet>=0, lblDbaErr);
	pcStr += strlen(pcStr);
    *pcStr = '|'; pcStr++;
	iRet = appGet(appGprsPass, pcStr, lenGprsPass+1);               // Retrieve password
	CHECK(iRet>=0, lblDbaErr);
	pcStr += strlen(pcStr);
	*pcStr = '|';
	iRet = appGet(appGprsUser, tcUser, lenGprsUser+1);              // Retrieve username to show
	CHECK(iRet>=0, lblDbaErr);
	iRet = GoalDspLine(xScreen, 1, tcUser, &txGPRS[1], 0, true);    // Show username
    iRet = StartGPRS(tcStr);                                        // ** Start **
    CHECK(iRet>=0, lblComKO);
	CHECK(iRet!=0, lblEnd);                                         // Exit on cancel/timeout
	iRet = GoalDspLine(xScreen, 2, "1-comStart OK", &txGPRS[2], 0, true);
	CHECK(iRet>=0, lblKO);
		
	// Transmission through GPRS layer in progress
	// *******************************************
    memset(tcSnd, 0, sizeof(tcSnd));
	memset(tcRsp, 0, sizeof(tcRsp));

    // Open GPRS layer 
	// ===============
	iRet = GoalDspLine(xScreen, 3, "2-comOpen...", &txGPRS[3], 0, true);
	CHECK(iRet>=0, lblKO);
    pvCom = OpenGPRS();                                               // ** Open **
    CHECK(pvCom!=NULL, lblKO);
    iRet = GoalDspLine(xScreen, 4, "2-comOpen OK", &txGPRS[4], 0, true);
	CHECK(iRet>=0, lblKO);

	// Configure GPRS layer
	// ====================
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 0, "3-comSet...", &txGPRS[0], 0, true);
	CHECK(iRet>=0, lblKO);
    SetGPRS();                                                        // ** Set **
    iRet = GoalDspLine(xScreen, 1, "3-comSet OK", &txGPRS[1], 0, true);
	CHECK(iRet>=0, lblKO);

	// Connect GPRS layer
    // ==================
	iRet = GoalDspLine(xScreen, 2, "4-comConnect...", &txGPRS[2], 0, true);
	CHECK(iRet>=0, lblKO);
	iRet = appGet(appGprsIpRemote, tcIpAddress, lenGprsIpRemote+1);   // Retrieve remote IP
	CHECK(iRet>=0, lblDbaErr);
	iRet = GoalDspLine(xScreen, 3, tcIpAddress, &txGPRS[3], 0, true); // Show IP Address
	CHECK(iRet>=0, lblKO);
	iRet = appGet(appGprsPort, tcPort, lenGprsPort+1);                // Retrieve port number
	CHECK(iRet>=0, lblDbaErr);
	iRet = GoalDspLine(xScreen, 4, tcPort, &txGPRS[4], 0, true);      // Show port number
	CHECK(iRet>=0, lblKO);
    sprintf (tcStr, "%s|%s", tcIpAddress, tcPort);
	iRet = ConnectGPRS(tcStr);                                        // ** Connect **
	CHECK(iRet>=0, lblComKO);
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 0, "4-comConnect OK", &txGPRS[0], 0, true);
	CHECK(iRet>=0, lblKO);

	// Clear sending/receiving buffers
	// ===============================
	iRet = LL_ClearSendBuffer(*pvCom);
    CHECK(iRet==LL_ERROR_OK, lblComKO);
    iRet = LL_ClearReceiveBuffer(*pvCom);
    CHECK(iRet==LL_ERROR_OK, lblComKO);

    // Send data through GPRS layer
	// ============================
	iRet = GoalDspLine(xScreen, 1, "5-comSend...", &txGPRS[1], 0, true);
	CHECK(iRet>=0, lblKO);
    strcpy(tcSnd, "Hello, do you hear me?\n"                        // Data to send
		          "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n");
    iRet = SendGPRS(tcSnd, (word) strlen(tcSnd));                     // ** Send data **
	CHECK(iRet>=0, lblComKO);
	iRet = GoalDspLine(xScreen, 2, "5-comSend OK", &txGPRS[2], 0, true);
	CHECK(iRet>=0, lblKO);

	// Receive data through GPRS layer
	// ===============================
	iRet = GoalDspLine(xScreen, 3, "6-comRec...", &txGPRS[3], 0, true);
	CHECK(iRet>=0, lblKO);
    iRet = ReceiveGPRS(tcRsp, sizeof(tcRsp), 30);                     // ** Receive data **
	CHECK(iRet>=0, lblComKO);
    if (iRet > MAX_RSP) strcpy (tcRsp, "Buffer overflow Max=512");    // Data overflow
    iRet = GoalDspLine(xScreen, 4, "6-comRec OK", &txGPRS[4], 0, true);
	CHECK(iRet>=0, lblKO);

	// Disconnection
	// =============
	iRet = DisconnectGPRS();                                          // ** Disconnect **
	CHECK(iRet>=0, lblComKO);
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 0, "7-comDisconn OK", &txGPRS[0], 0, true);
	CHECK(iRet>=0, lblKO);
	iRet = CloseGPRS();                                               // ** Close **
	CHECK(iRet>=0, lblComKO);
	pvCom=NULL;

	// Display transmission data
	// =========================
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspMultiLine(xScreen, 0, tcRsp, strlen(tcRsp), txGPRS, NUMBER_OF_LINES(txGPRS), 0, true);
	CHECK(iRet>=0, lblKO);                                            // Show data to receive

	// Print transmission data
	// =======================
	p=0;
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);          // Create document
	CHECK(xDocument!=NULL, lblKO);

	xLine = xPrinter;                                                 // Build document (Demo, Tx/Rx data)
	xLine.eTextAlign = GL_ALIGN_CENTER;
	xLine.bReverse = TRUE;
	xLine.xMargin.usBottom = PIXEL_BOTTOM;
	xLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "GPRS Demo", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine = xPrinter;
	iRet = GoalPrnLine(xDocument, p++, "Sending:", &xLine);           // Data to send
	CHECK(iRet>=0, lblKO);
    iRet = GoalPrnLine(xDocument, p++, tcSnd, &xLine);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "\nReceiving:", &xLine);       // Data to receive
	CHECK(iRet>=0, lblKO);
    iRet = GoalPrnLine(xDocument, p++, tcRsp, &xLine);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "\n\n\n\n", &xLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);                  // Wait for key pressed/touched (shortcut)

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                           // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblComKO:                                        // Communication error
	strcpy(tcDisplay, LL_ErrorMsg(iRet));        // Link Layer error
	if (iRet == LL_Network_GetStatus(LL_PHYSICAL_V_GPRS, &iStatus))
	{
		switch(iStatus)
		{
		case LL_STATUS_GPRS_ERROR_NO_SIM:   iStatus=LL_STATUS_GPRS_NO_SIM;      break;
        case LL_STATUS_GPRS_ERROR_PPP:      iStatus=LL_STATUS_GPRS_ERR_PPP;     break;
		case LL_STATUS_GPRS_ERROR_UNKNOWN:  iStatus=LL_STATUS_GPRS_ERR_UNKNOWN; break;
		default:                            iStatus=-1;                         break;
		}
		strcat(tcDisplay, "\n");
		strcat(tcDisplay, LL_ErrorMsg(iStatus)); // Link Layer status
	}
	if (iRet != LL_ERROR_TIMEOUT)                // Cancel or timeout ?
		GL_Dialog_Message(xGoal, NULL, tcDisplay, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblDbaErr:                                       // Data base error
	sprintf(tcDisplay, "%s\n%s", FMG_ErrorMsg(iRet), "Software Reset Needed");
	GL_Dialog_Message(xGoal, NULL, tcDisplay, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
    if (pvCom) {
		DisconnectGPRS();                        // ** Disconnect **
		CloseGPRS();                             // ** Close **
	}
    StopGPRS();                                  // ** Stop **
	if (xScreen)
		GoalDestroyScreen(&xScreen);             // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);         // Destroy document
}


