//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  COMGPRS.C                           (Copyright INGENICO 2009)   
//============================================================================
//  Created :       13-Avril-2009     Kassovic                                 
//  Last modified : 13-Avril-2009     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  GPRS communication management:
//             Transmission by GPRS
//             Test done with Hyper-terminal Tcp/Ip Winsock
//  !!! Link Layer application must be loaded 3628xxxx.SGN inside the terminal
//      Supports PPP, TCP/IP and SSL protocols. Submitted under licence.
//  !!! Link Layer provided under SDK package 3429xxxx.SGN does not support
//      TCP/IP excepted under Wifi and Gprs (So this demo will not work).
//      AVL.lib + LinkLayerExeInterface.lib must be implemented to link properly
//                                                                            
//  List of routines in file :  
//      GprsReport : Provide the state of the GPRS driver.
//      StartGPRS : Attach to the GPRS network.
//      OpenGPRS : Create the GPRS layer.
//      InitGPRS : Configure the GPRS layer.
//      ConnectGPRS : Connect the GPRS layer.
//      SendBufGPRS : Send data through the GPRS layer.
//      RecBufGPRS : Receive data through the GPRS layer.
//      DisconnectGPRS : Disconnect the GPRS layer.                                           
//      CloseGPRS : Delete the GPRS layer.
//      StopGPRS : Break the attachment to the GPRS network.
//      PromptGPRS : Prompt for GPRS's parameters.
//      ComGPRS : GPRS communication demo.
//                            
//  File history :
//  120508-BK : File created 
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
#include "Training.h"
#include "TlvTree.h"
#include "LinkLayer.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern FILE *pxKbd;      // Peripheral file Keyboard

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
static LL_HANDLE tvSession[1] = {NULL};

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
//       LL_GPRS_Start() : Start GPRS modem and enable facility
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
    int iRequirePin;
	char tcRequirePin[lenGprsRequirePin+1];   // Pin required ?
	char tcPin[lenGprsPin+1];
	char tcPin1[lenGprsPin+1];
	char tcPuk[lenGprsPuk+1];
	char tcCmd[lenGprsPin+lenGprsPuk+1+1];    // (+1 for comma, +1 for end string)
    char tcReport[25+1], tcStatus[25+1];
    T_DGPRS_GET_INFORMATION xInfo;
    int iRet;

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
	case DGPRS_REPORT_READY:            strcpy(tcReport, "Rpt: READY           "); break;
	case DGPRS_REPORT_WAITING_CODE:     strcpy(tcReport, "Rpt: WAITING_CODE    "); break;
	case DGPRS_REPORT_SIM_NOT_PRESENT:  strcpy(tcReport, "Rpt: SIM_NOT_PRESENT "); break;
	case DGPRS_REPORT_SIMLOCK_STATE:    strcpy(tcReport, "Rpt: SIMLOCK_STATE   "); break;
	case DGPRS_REPORT_FATAL_ERROR:      strcpy(tcReport, "Rpt: FATAL_ERROR     "); break;
	default:                            strcpy(tcReport, "Rpt: UNKNOWN_ERROR   "); break;
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
	case DGPRS_SIM_OK:
		strcpy(tcStatus, "Sta: SIM_OK          ");   // Sim ready, pin already checked

		// *** Start GPRS session ***
		iRet = LL_GPRS_Start(NULL, pcApn);
	    CHECK(iRet==LL_ERROR_OK, lblKO);

        DisplaySmall(7, 0, "CONNECT. IN PROGRESS ");
		break;
	case DGPRS_SIM_KO:                  strcpy(tcStatus, "Sta: SIM_KO          "); break;
	case DGPRS_SIM_PIN_REQUIRED:
		strcpy(tcStatus, "Sta: PIN_REQUIRED    ");   // Pin required, enter it

		// *** Enter Pin code ***
		do
		{
			memset (tcPin, 0, sizeof(tcPin));
			iRet = ShowEntry("ENTER  PIN", "PIN  (8 digits max)", tcPin, 4, lenGprsPin, 3);
			if (iRet<0)
			{
				DisplaySmall(6, 4, "Entry exceeded !!!");
				buzzer(10);
				ttestall(0, 2*100);
			}
		} while (iRet<0);
		CHECK(iRet!=0, lblEnd);                      // Cancel, Timeout

		// *** Start GSM session ***
		iRet = LL_GSM_Start(tcPin[0] ? tcPin : NULL);
		CHECK(iRet==LL_ERROR_OK, lblKO);

		// *** Start GPRS session ***
		iRet = LL_GPRS_Start(tcPin[0] ? tcPin : NULL, pcApn);
	    CHECK(iRet==LL_ERROR_OK, lblKO);

        _clrscr();
    	DisplayMedium(0, 0, "1-comStart...");
     	DisplayMedium(1, 0, pcUsername);

    	DisplaySmall(7, 0, "CONNECT. IN PROGRESS ");
	    break;
	case DGPRS_SIM_PIN2_REQUIRED:       strcpy(tcStatus, "Sta: PIN2 REQUIRED   "); break;
	case DGPRS_SIM_PIN_ERRONEOUS:
		strcpy(tcStatus, "Sta: PIN ERRONEOUS   ");   // Wrong Pin, enter it

		// *** Enter Pin code ***
		do
		{
			memset (tcPin, 0, sizeof(tcPin));
			iRet = ShowEntry("ENTER  PIN", "PIN  (8 digits max)", tcPin, 4, lenGprsPin, 3);
			if (iRet<0)
			{
				DisplaySmall(6, 4, "Entry exceeded !!!");
				buzzer(10);
				ttestall(0, 2*100);
			}
		} while (iRet<0);
		CHECK(iRet!=0, lblEnd);                      // Cancel, Timeout

		// *** Start GSM session ***
		LL_GSM_Start(tcPin[0] ? tcPin : NULL);

		// *** Start GPRS session ***
		iRet = LL_GPRS_Start(tcPin[0] ? tcPin : NULL, pcApn);
	    CHECK(iRet==LL_ERROR_OK, lblKO);

        _clrscr();
    	DisplayMedium(0, 0, "1-comStart...");
     	DisplayMedium(1, 0, pcUsername);

    	DisplaySmall(7, 0, "CONNECT. IN PROGRESS ");
		break;
	case DGPRS_SIM_NOT_INSERTED:        strcpy(tcStatus, "Sta: SIM_NOT_INSERTED"); break;
	case DGPRS_SIM_PUK_REQUIRED:
		strcpy(tcStatus, "Sta: PUK_REQUIRED    ");   // Puk required, enter it

		// *** Enter Puk code ***
		do
		{
			memset (tcPuk, 0, sizeof(tcPuk));
			iRet = ShowEntry("ENTER  PUK", "PUK  (8 digits max)", tcPuk, 4, lenGprsPuk, 3);
			if (iRet<0)
			{
				DisplaySmall(6, 4, "Entry exceeded !!!");
				buzzer(10);
				ttestall(0, 2*100);
			}
		} while (iRet<0);
		CHECK(iRet!=0, lblEnd);                      // Cancel, Timeout

		// *** Enter new Pin code and confirm ***
		do
		{
			do
			{
				memset (tcPin1, 0, sizeof(tcPin1));  // Enter new Pin
				iRet = ShowEntry("ENTER  NEW  PIN", "PIN  (8 digits max)", tcPin1, 4, lenGprsPin, 3);
				if (iRet<0)
				{
					DisplaySmall(6, 4, "Entry exceeded !!!");
					buzzer(10);
					ttestall(0, 2*100);
				}
			} while (iRet<0);
			CHECK(iRet!=0, lblEnd);                  // Cancel, Timeout

			do
			{
				memset (tcPin, 0, sizeof(tcPin));    // Confirm new Pin
				iRet = ShowEntry("CONFIRM  NEW  PIN", "PIN  (8 digits max)", tcPin, 4, lenGprsPin, 3);
				if (iRet<0)
				{
					DisplaySmall(6, 4, "Entry exceeded !!!");
					buzzer(10);
					ttestall(0, 2*100);
				}
			} while (iRet<0);
			CHECK(iRet!=0, lblEnd);                  // Cancel, Timeout
		}
		while (memcmp(tcPin1, tcPin, lenGprsPin) != 0);

		sprintf(tcCmd, "%s,%s", tcPuk, tcPin);
		iRet = fioctl(DGPRS_FIOCTL_SET_PUK_CODE, tcCmd, pxGprs);
		if (iRet == 0)                               // Puk code OK
		{
			ttestall(0, 1*100);                      // Wait 1s before restarting a session

			// *** Start GSM session ***
			LL_GSM_Start(tcPin[0] ? tcPin : NULL);

			// *** Start GPRS session ***
			iRet = LL_GPRS_Start(tcPin[0] ? tcPin : NULL, pcApn);
			CHECK(iRet==LL_ERROR_OK, lblKO);
		}

        _clrscr();
    	DisplayMedium(0, 0, "1-comStart...");
     	DisplayMedium(1, 0, pcUsername);

		DisplaySmall(7, 0, "CONNECT. IN PROGRESS ");
		break;
	case DGPRS_SIM_PUK2_REQUIRED: 		strcpy(tcStatus, "Sta: PUK2_REQUIRED   "); break;
	case DGPRS_SIM_PIN_PRESENTED:       strcpy(tcStatus, "Sta: PIN_PRESENTED   "); break;
	default:                            strcpy(tcStatus, "Sta: UNKNOWN_ERROR   "); break;
	}

	DisplaySmall(5, 0, tcReport);                   // Display start report
	DisplaySmall(6, 0, tcStatus);                   // Display sim status

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
//       LL_GPRS_Connect() : Connect the GPRS network 
//       LL_Network_GetStatus() : Return current status of the network
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
    char tcApn[lenGprsApn+1];                 // Apn
    char tcUsername[lenGprsUser+1];           // Login
    char tcPassword[lenGprsPass+1];           // Password
    char cKey;
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
    reset_buf(pxKbd, _receive_id);
    do
    {
    	iRet = GprsReport(tcApn, tcUsername);
    	CHECK(iRet>=0, lblKOConfigure);
    	CHECK(iRet!=0, lblEnd);                                        // Cancel, Timeout

    	iRet = LL_GPRS_Connect(tcApn, tcUsername, tcPassword, 10*100);
    	switch (iRet)
    	{
    	//case LL_ERROR_NETWORK_NOT_READY:
    	//	bExit = FALSE;
    	//	break;
    	case LL_ERROR_ALREADY_CONNECTED:
    	case LL_ERROR_OK:
        	DisplaySmall(7, 0, "GPRS CONNECTED!!!    ");
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
            	DisplaySmall(7, 0, "GPRS CONNECTED!!!    ");
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

    		if (!bExit)                            // Exit on cancel or wait for timeout
    		{
    	    	iRet = ttestall (KEYBOARD, 1*100);
    	    	usTimeOut += 1*100;
    	    	if (iRet & KEYBOARD)
    			{
    				cKey = getchar();
    				if (cKey == T_ANN)
    					usTimeOut = GPRS_TIMEOUT;
    			}
    		}
    	}
    } while (!bExit && (usTimeOut < GPRS_TIMEOUT));

    if (usTimeOut == GPRS_TIMEOUT)                 // Timeout/Cancel
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
    piConfig = TlvTree_New(LL_TAG_LINK_LAYER_CONFIG);                   // LinkLayer parameters Root tag of the configuration tree
    
    // Physical layer parameters
	// =========================
	piPhysicalConfig = TlvTree_AddChild(piConfig,                        
		                                LL_TAG_PHYSICAL_LAYER_CONFIG,   // TAG Physical layer parameters 
									    NULL,                           // VALUE (Null)
									    0);                             // LENGTH 0

	// GPRS
	// ----
    TlvTree_AddChildInteger(piPhysicalConfig, 
		                    LL_PHYSICAL_T_LINK,                         // TAG
							LL_PHYSICAL_V_GPRS,                         // VALUE
							LL_PHYSICAL_L_LINK);                        // LENGTH 1
}

//****************************************************************************
//              int ConnectGPRS (const char *pcServer)                            
//  This function connects the GPRS layer.      
//       LL_Configure() : Create Link Layer configuration
//       LL_Connect() : Connect Link Layer
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
//       LL_Send() : Send data
//       LL_GetLastError() : Retrieve the last error
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
//       LL_ClearReceiveBuffer() : Clear receiving buffer
//       LL_Receive() : Wait and receive data
//       LL_GetLastError() : Retrieve the last error
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
	char cKey;
    int iRet, iLength=0, iTimeOut=LL_INFINITE, iSec, iNbrBytes;

	// Timeout setting
	// ***************
    if(ucDly != 0xFF)  
        iSec = ucDly*100;
	else
		iSec = LL_INFINITE;

	// Receiving first block
	// *********************
    reset_buf(pxKbd, _receive_id);                                          // Reset keyboard FIFO
    iRet = TimerStart(0, iSec);                                             // Timer0 starts
    CHECK(iRet>=0, lblTimeOut);
	do
    {
    	iNbrBytes = LL_Receive(tvSession[0], usLen, pcMsg+iLength, 1*100);  // Check reception
    	if (iNbrBytes != 0)
    		break;                                                          // Bytes received
		iRet = ttestall(KEYBOARD, 1);                                       // Check for a key pressed
		if (iRet & KEYBOARD)                                                // Key detected
		{
			cKey = getchar();                                               // Retrieve key pressed
			CHECK(cKey!=T_ANN, lblTimeOut);                                 // Exit on cancel key
		}
		if (iSec != LL_INFINITE)
			iTimeOut = TimerGet(0);                                         // Retrieve timer value
    } while (iTimeOut>0);

    CHECK(iTimeOut!=0, lblTimeOut);                                         // Exit on timeout

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
//       LL_Disconnect() : Disconnect Link Layer
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
//       LL_Configure() : Delete Link Layer configuration   
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
//       LL_GPRS_Stop() : Disconnect the GPRS network   
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
    char tcRequirePin[lenGprsRequirePin+1];
    char tcAPN[lenGprsApn+1];
    char tcUser[lenGprsUser+1];
    char tcPass[lenGprsPass+1];
	char tcIpAddress[lenGprsIpRemote+1];
	char tcPort[lenGprsPort+1];
    int iRet;

	// Pin Required ?
	// ***************
	do
	{
	    iRet = appGet(appGprsRequirePin, tcRequirePin, lenGprsRequirePin+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("PIN  REQUIRED?", "Yes=0/No=1  (1 digit)", tcRequirePin, 0, lenGprsRequirePin, 2);
		if (iRet<0)
		{
			DisplaySmall(6, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                           // Cancel, Timeout
	if (iRet==2)                                                      // Save pin
	{
		iRet = appPut(appGprsRequirePin, tcRequirePin, lenGprsRequirePin); CHECK(iRet>=0, lblDbaErr);
	}

	// Enter APN 
	// *********
	do
	{
		iRet = appGet(appGprsApn, tcAPN, lenGprsApn+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  APN", "", tcAPN, 0, lenGprsApn, 0);
		if (iRet<0)
		{
			DisplaySmall(5, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                           // Cancel, Timeout
	if (iRet==2)                                                      // Save apn
	{
		iRet = appPut(appGprsApn, tcAPN, lenGprsApn); CHECK(iRet>=0, lblDbaErr);
	}
		
	// Enter User Name 
	// ***************
	do
	{
		iRet = appGet(appGprsUser, tcUser, lenGprsUser+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  USERNAME", "", tcUser, 0, lenGprsUser, 0);
		if (iRet<0)
		{
			DisplaySmall(5, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                           // Cancel, Timeout
	if (iRet==2)                                                      // Save username
	{
		iRet = appPut(appGprsUser, tcUser, lenGprsUser); CHECK(iRet>=0, lblDbaErr);
	}

	// Enter Password 
	// **************
	do
	{
		memset(tcPass, '*', 8);
		iRet = ShowEntry("ENTER  PASSWORD", "", tcPass, 0, lenGprsPass, 0);
		if (iRet<0)
		{
			DisplaySmall(5, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                           // Cancel, Timeout
	if (iRet==2)                                                      // Save password
	{
		iRet = appPut(appGprsPass, tcPass, lenGprsPass); CHECK(iRet>=0, lblDbaErr);
	}
			
    // Enter Remote IP address
    // ***********************
	do
	{
	    iRet = appGet(appGprsIpRemote, tcIpAddress, lenGprsIpRemote+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER REMOTE IP", "", tcIpAddress, 0, lenGprsIpRemote, 4);
		if (iRet<0)
		{
			DisplaySmall(6, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                           // Cancel, Timeout
	if (iRet==2)                                                      // Save Ip address
	{
		iRet = appPut(appGprsIpRemote, tcIpAddress, lenGprsIpRemote); CHECK(iRet>=0, lblDbaErr);
	}

	// Enter Port number 
	// *****************
	do
	{
		iRet = appGet(appGprsPort, tcPort, lenGprsPort+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  PORT  NUMBER", "", tcPort, 0, lenGprsPort, 0);
		if (iRet<0)
		{
			DisplaySmall(5, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                           // Cancel, Timeout
	if (iRet==2)                                                      // Save port
	{
		iRet = appPut(appGprsPort, tcPort, lenGprsPort); CHECK(iRet>=0, lblDbaErr);
	}
		
	goto lblEnd;

	// Errors treatment 
	// ****************
lblDbaErr:
	_clrscr();                                                         // Clear screen
	DisplayMedium(0, 0, FMG_ErrorMsg(iRet));                           // FMG error
	DisplayMedium(1, 0, "Reset Needed");                               // Rebuild data base
	ttestall(0, 5*100);                                            	   // Delay 5s
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
    LL_HANDLE *pvCom=NULL;
	char *pcStr, tcStr[128+1];
	char tcUser[lenGprsUser+1];
	char tcIpAddress[lenGprsIpRemote+1];
	char tcPort[lenGprsPort+1];
    char tcSnd[MAX_SND+1];
    char tcRsp[MAX_RSP+1];
	int iRet=0, iStatus=0;

	// Attachment to the GPRS network in progress
	// ******************************************
    _clrscr();                                                        // Clear screen
	DisplayMedium(0, 0, "1-comStart...");                             // Display start message
	pcStr = tcStr;                                                    // Build param string
	iRet = appGet(appGprsApn, pcStr, lenGprsApn+1);                   // Retrieve apn
	CHECK(iRet>=0, lblDbaErr);
	pcStr += strlen(pcStr);
	*pcStr = '|'; pcStr++;
	iRet = appGet(appGprsUser, pcStr, lenGprsUser+1);                 // Retrieve username
	CHECK(iRet>=0, lblDbaErr);
	pcStr += strlen(pcStr);
    *pcStr = '|'; pcStr++;
	iRet = appGet(appGprsPass, pcStr, lenGprsPass+1);                 // Retrieve password
	CHECK(iRet>=0, lblDbaErr);
	pcStr += strlen(pcStr);
	*pcStr = '|';
	iRet = appGet(appGprsUser, tcUser, lenGprsUser+1);                // Retrieve username to display
	CHECK(iRet>=0, lblDbaErr);
 	DisplayMedium(1, 0, tcUser);                                      // Display username
    iRet = StartGPRS(tcStr); CHECK(iRet>=0, lblComKO);                // ** Start **
	CHECK(iRet!=0, lblEnd);                                           // Cancel, Timeout
    DisplayMedium(2, 0, "1-comStart OK");                             // Display start OK
		
	// Transmission through GPRS layer in progress
	// *******************************************
    memset(tcSnd, 0, sizeof(tcSnd));
	memset(tcRsp, 0, sizeof(tcRsp));

    // Open GPRS layer 
	// ===============
	DisplayMedium(3, 0, "2-comOpen...");                              // Display open message
    pvCom = OpenGPRS(); CHECK(pvCom!=NULL, lblKO);                    // ** Open **
    _clrscr();                                                        // Clear screen
    DisplayMedium(0, 0, "2-comOpen OK");                              // Display open OK

	// Configure GPRS layer
	// ====================
	DisplayMedium(1, 0, "3-comSet...");                               // Display set message
    SetGPRS();                                                        // ** Set **
    DisplayMedium(2, 0, "3-comSet OK");                               // Display set OK

	// Connect GPRS layer
    // ==================
	DisplayMedium(3, 0, "4-comConnect...");                           // Display connect message
    _clrscr();                                                        // Clear screen
	iRet = appGet(appGprsIpRemote, tcIpAddress, lenGprsIpRemote+1);   // Retrieve remote IP
	CHECK(iRet>=0, lblDbaErr);
	DisplayMedium(0, 0, tcIpAddress);                                 // Display IP Address
	iRet = appGet(appGprsPort, tcPort, lenGprsPort+1);                // Retrieve port number
	CHECK(iRet>=0, lblDbaErr);
    DisplayMedium(1, 0, tcPort);                                      // Display port number
    sprintf (tcStr, "%s|%s", tcIpAddress, tcPort);
	iRet = ConnectGPRS(tcStr); CHECK(iRet>=0, lblComKO);              // ** Connect **
    DisplayMedium(2, 0, "4-comConnect OK");                           // Display connect OK

	// Clear sending/receiving buffers
	// ===============================
	iRet = LL_ClearSendBuffer(*pvCom);                                // Clear sending buffer
    CHECK(iRet==LL_ERROR_OK, lblComKO);
    iRet = LL_ClearReceiveBuffer(*pvCom);                             // Clear receiving buffer
    CHECK(iRet==LL_ERROR_OK, lblComKO);

    // Send data through GPRS layer
	// ============================
	DisplayMedium(3, 0, "5-comSend...");                              // Display send message
    strcpy(tcSnd, "Hello, do you hear me?\r\n"                        // Data to send
		          "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n");
    iRet = SendGPRS(tcSnd, (word) strlen(tcSnd));                     // ** Send data **
	CHECK(iRet>=0, lblComKO);
    _clrscr();                                                        // Clear screen
	DisplayMedium(0, 0, "5-comSend OK");                              // Display send OK

	// Receive data through GPRS layer
	// ===============================
	DisplayMedium(1, 0, "6-comRec...");                               // Display receive message
    iRet = ReceiveGPRS(tcRsp, sizeof(tcRsp), 30);                     // ** Receive data **
	CHECK(iRet>=0, lblComKO);
    if (iRet > MAX_RSP) strcpy (tcRsp, "Buffer overflow Max=512");    // Data overflow
	DisplayMedium(2, 0, "6-comRec OK");                               // Display receive OK

	// Disconnection
	// =============
	iRet = DisconnectGPRS();                                          // ** Disconnect **
	CHECK(iRet>=0, lblComKO);
	DisplayMedium(3, 0, "7-comDisconn OK");                           // Display disconnect OK
	iRet = CloseGPRS();                                               // ** Close **
	CHECK(iRet>=0, lblComKO);
	pvCom=NULL;

	// Display transmission data
	// =========================
	_clrscr();                                                        // Clear screen
	DisplaySmall(0, 0, "RECEIVING:");                                 // Display data to receive
	iRet = Display25(1, tcRsp, strlen(tcRsp)); CHECK(iRet>=0, lblKO);
    DisplaySmall(7, 6, "Press a key");

	// Print transmission data
	// =======================
	iRet = pprintf("\x1b""E""        GPRS Demo\n\n"                   // Print demo in progress
		           "\x1b""F"); CHECK(iRet>=0, lblKO);      
    iRet = pprintf("Sending:\n"); CHECK(iRet>=0, lblKO);              // Print data to send
	iRet = Print24(tcSnd, strlen(tcSnd)); CHECK(iRet>=0, lblKO);
    iRet = pprintf("\nReceiving:\n"); CHECK(iRet>=0, lblKO);          // Print data to receive
	iRet = Print24(tcRsp, strlen(tcRsp)); CHECK(iRet>=0, lblKO);
    iRet = pprintf("\n\n\n\n\n\n"); CHECK(iRet>=0, lblKO);

	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                       // Wait until key pressed or timeout
	reset_buf(pxKbd, _receive_id);                                    // Reset keyboard FIFO to clear key pressed

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                                // None-classified low level error
    _clrscr();                                                        // Clear screen
    DisplayMedium(0, 0, "Processing Error");                          // Oops! error
    ttestall(0,5*100);                                                // Delay 5s
    goto lblEnd;
lblComKO:                                                             // Communication error
    _clrscr();                                                        // Clear screen
    DisplayMedium(0, 0, LL_ErrorMsg(iRet));                           // Link Layer error
	if (iRet == LL_Network_GetStatus(LL_PHYSICAL_V_GPRS, &iStatus))
	{
		switch(iStatus)
		{
		case LL_STATUS_GPRS_ERROR_NO_SIM:   iStatus=LL_STATUS_GPRS_NO_SIM;      break;
        case LL_STATUS_GPRS_ERROR_PPP:      iStatus=LL_STATUS_GPRS_ERR_PPP;     break;
		case LL_STATUS_GPRS_ERROR_UNKNOWN:  iStatus=LL_STATUS_GPRS_ERR_UNKNOWN; break;
		default:                            iStatus=-1;                         break;
		}
		DisplayMedium(1, 0, LL_ErrorMsg(iStatus));                    // Link Layer status
	}
    ttestall(0,5*100);                                                // Delay 5s
    goto lblEnd;
lblDbaErr:                                                            // Data base error
	_clrscr();                                                        // Clear screen
	DisplayMedium(0, 0, FMG_ErrorMsg(iRet));                          // FMG error
	DisplayMedium(1, 0, "Reset Needed");                              // Rebuild data base
	ttestall(0, 5*100);                                               // Delay 5s
lblEnd:
    if (pvCom) {
		DisconnectGPRS();                                             // ** Disconnect **
		CloseGPRS();                                                  // ** Close **
	}
    StopGPRS();                                                       // ** Stop **
}


