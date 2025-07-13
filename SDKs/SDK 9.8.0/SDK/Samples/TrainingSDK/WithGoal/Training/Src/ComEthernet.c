//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  COMETHERNET.C                      (Copyright INGENICO 2012)
//============================================================================
//  Created :       11-July-2012     Kassovic
//  Last modified : 11-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                   *** Ethernet communication management ***
//             Transmission by Ethernet interface ETH
//  How to use the linklayer to create an Ethernet configuration to communicate.
//             Test done with Hyper-terminal Tcp/Ip Winsock
//  !!! Link Layer application must be loaded 3628xxxx.SGN inside the terminal
//      Supports PPP, TCP/IP and SSL protocols.
//      AVL.lib + LinkLayerExeInterface.lib must be implemented to link properly   
//                                                                            
//  List of routines in file :  
//      OpenEthernet : Create the Ethernet configuration.
//      SetEthernet : Configure the Ethernet layer.
//      ConnectEthernet : Connect the Ethernet layer.
//      SendEthernet : Send data through the Ethernet layer.
//      ReceiveEthernet : Receive data through the Ethernet layer.
//      DisconnectEthernet : Disconnect the Ethernet layer.
//      CloseEthernet : Delete the Ethernet configuration.
//      PromptEthernet : Prompt for Ethernet's parameters.
//      ComEthernet : Ethernet communication demo.
//                            
//  File history :
//  071112-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "TlvTree.h"
#include "LinkLayer.h"
#include "VGE_FMG.H"
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

#define TCPIP_TIMEOUT 30*100

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
   // Empty

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the Ethernet screen (Goal)
// ========================================
static const ST_DSP_LINE txEthernet[] =
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

static LL_HANDLE tvSession[1] = {NULL}; // Session handle

// Tlv tree nodes
// ==============
static TLV_TREE_NODE piConfig=NULL;
static TLV_TREE_NODE piPhysicalConfig=NULL;
static TLV_TREE_NODE piTransportConfig=NULL;

//****************************************************************************
//                   LL_HANDLE* OpenEthernet(void)
//  This function creates the handle of the Ethernet layer.
//  This function has no parameter.
//  This function has return value
//    !NULL : Pointer to the handle configuration.
//    NULL : Processing failed                                        
//****************************************************************************

static LL_HANDLE* OpenEthernet(void)
{
    return tvSession;
}

//****************************************************************************
//                   int SetEthernet (const char *pcInit)                            
//  This function configures the Ethernet layer.
//   - LL_Configure() : Create Link Layer configuration
//  This function has parameters.  
//    pcInit (I-) : if *pcInit!= 0 => use static IP address
//           LocalAddress = xxx.xxx.xxx.xxx
//           NetMask      = xxx.xxx.xxx.xxx
//           Gateway      = xxx.xxx.xxx.xxx
//           The '|' is the separator
//           Ex: "192.168.1.2|255.255.255.0|192.168.1.1     
//  This function has return value
//    >=0 : Configuration done
//     <0 : Configuration failed                                        
//****************************************************************************

static int SetEthernet(const char *pcInit) 
{
	// Local variables 
    // ***************
    char tcLocalAddr[15+1];    // Ip address xxx.xxx.xxx.xxx
    char tcNetmask[15+1];      // Mask address xxx.xxx.xxx.xxx
    char tcGateway[15+1];      // Gateway address xxx.xxx.xxx.xxx
//    doubleword uiLocalAddr=0;
//    doubleword uiNetmask=0;
//    doubleword uiGateway=0;
    int iRet;
        
    // Configure Static Address if present
    // ***********************************
    if (*pcInit)
    {
    	memset(tcLocalAddr, 0, sizeof(tcLocalAddr));  // Ip address
    	pcInit = parseStr('|', tcLocalAddr, pcInit, sizeof(tcLocalAddr));
        CHECK(pcInit!=NULL, lblKOConfigure);
    
        memset(tcNetmask, 0, sizeof(tcNetmask));      // Netmask address
        pcInit = parseStr('|', tcNetmask, pcInit, sizeof(tcNetmask));
        CHECK(pcInit!=NULL, lblKOConfigure);

        memset(tcGateway, 0, sizeof(tcGateway));      // Gateway address
        pcInit = parseStr('|', tcGateway, pcInit, sizeof(tcGateway));
        CHECK(pcInit!=NULL, lblKOConfigure);
    }

/*  Extra functions from TCP/IP
    if (tcLocalAddr[0]) {
        uiLocalAddr = __inet_addr(tcLocalAddr);       // Force local address
        EthernetSetOption(ETH_IFO_ADDR, &uiLocalAddr);
    }

    if (tcNetmask[0]) {
        uiNetmask = __inet_addr(tcNetmask);           // Force mask
        EthernetSetOption(ETH_IFO_NETMASK, &uiNetmask);
    }
    if(tcGateway[0]) {
        uiGateway = __inet_addr(tcGateway);           // Force gateway
        EthernetSetOption(ETH_IFO_GATEWAY, &uiGateway);
    }
*/  
    
	// Create the LinkLayer configuration parameters tree 
	// **************************************************

    // Create parameters tree
    // ======================
    piConfig = TlvTree_New(LL_TAG_LINK_LAYER_CONFIG);                 // LinkLayer parameters Root tag of the configuration tree
    
    // Physical layer parameters
	// =========================
	piPhysicalConfig = TlvTree_AddChild(piConfig,                        
		                                LL_TAG_PHYSICAL_LAYER_CONFIG, // TAG Physical layer parameters
									    NULL,                         // VALUE (Null)
									    0);                           // LENGTH 0

	// Ethernet
	// --------
    TlvTree_AddChildInteger(piPhysicalConfig, 
		                    LL_PHYSICAL_T_LINK,                       // TAG
							LL_PHYSICAL_V_ETHERNET,                   // VALUE
							LL_PHYSICAL_L_LINK);                      // LENGTH 1
        
    iRet=LL_ERROR_OK;
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKOConfigure:
    iRet=LL_ERROR_INVALID_PARAMETER;
lblEnd:
	return iRet;
}

//****************************************************************************
//              int ConnectEthernet (const char *pcServer)                            
//  This function connects the Ethernet layer.
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

static int ConnectEthernet(const char *pcServer) 
{
	// Local variables 
    // ***************
    char tcAddr[lenEthIpLocal+1];
    char tcPort[lenEthPort+1];
	doubleword uiTimeout, uiRemotePort;
    int iRet=LL_ERROR_INVALID_PARAMETER;
        
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
        CHECK(pcServer!=NULL, lblKOConfigure);                          // End string
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
//            int SendEthernet (const char *pcMsg, word usLen)
//  This function sends data through the Ethernet layer.
//   - LL_Send() : Send data
//   - LL_GetLastError() : Retrieve the last error
//  This function has parameters.  
//    pcMsg (I-) : Data to send
//    usLen (I-) : Number of byte to send
//  This function has return value
//    >=0 : Number of bytes sent
//     <0 : Transmission failed                                       
//****************************************************************************

static int SendEthernet(const char *pcMsg, word usLen)
{
	// Local variables 
    // ***************
    int iRet;
    
	// Send data
	// *********
    iRet = LL_Send(tvSession[0], usLen, pcMsg, LL_INFINITE);
    if(iRet != usLen)
		iRet = LL_GetLastError(tvSession[0]);

    return iRet;
}

//****************************************************************************
//        int ReceiveEthernet (char *pcMsg, word usLen, byte ucDly)
//  This function receives data through the Ethernet layer.
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

static int ReceiveEthernet(char *pcMsg, word usLen, byte ucDly)
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
		// Receiving next block until timeout (Inter block 500ms)
		// ======================================================
		while(1)
		{
			iNbrBytes = LL_Receive(tvSession[0], usLen-iLength, pcMsg+iLength, 50);
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
//                   int DisconnectEthernet (void)                            
//  This function disconnects the Ethernet layer.
//   - LL_Disconnect() : Disconnect Link Layer
//  This function has no parameters.  
//  This function has return value
//    >=0 : Disconnect done
//     <0 : Disconnect failed                                       
//****************************************************************************

static int DisconnectEthernet(void) 
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
//                     int CloseEthernet (void)                            
//  This function deletes the handle of the Ethernet layer.
//   - LL_Configure() : Delete Link Layer configuration
//  This function has no parameters.  
//  This function has return value
//    >=0 : Configuration deleted
//     <0 : Processing failed                                        
//****************************************************************************

static int CloseEthernet(void)
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
//                    void PromptEthernet (void)                            
//  This function asks for the Ethernet's parameters.   
//  This function has no parameters.  
//  This function has no return value
//****************************************************************************

void PromptEthernet(void)
{
	// Local variables 
    // ***************
	char tcMask[256];
	char tcIpAddressN[lenEthIpLocal+1], tcIpAddressP[lenEthIpLocal+1];
	char tcPortN[lenEthPort+1], tcPortP[lenEthPort+1];
	doubleword uiIp;
	char tcDisplay[50+1];
    int i, iRet;

    // Enter Local IP address
    // **********************
	iRet = appGet(appEthIpLocal, tcIpAddressP, lenEthIpLocal+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcIpAddressN, tcIpAddressP);
	uiIp = IpToUint(tcIpAddressN);                                        // Convert Ip address to unsigned int
	CHECK(uiIp>=0, lblKO);
	iRet = GL_Dialog_Ip(xGoal, "Local Ip Address", "Enter Ip Address :", (T_GL_HIP)&uiIp, GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	strcpy(tcIpAddressN, UintToIp(uiIp));                                 // Convert unsigned int to Ip address
	if (strcmp(tcIpAddressN, tcIpAddressP) != 0)
	{
		iRet = appPut(appEthIpLocal, tcIpAddressN, lenEthIpLocal);        // Save new Ip address
		CHECK(iRet>=0, lblDbaErr);
	}
	
	// Enter Port number 
	// *****************
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenEthPort; i++)
		strcat(tcMask, "/d");                                             // Accept only decimal character
	iRet = appGet(appEthPort, tcPortP, lenEthPort+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcPortN, tcPortP);
	iRet = GL_Dialog_Text(xGoal, "Port Number", "Enter Port# :", tcMask, tcPortN, sizeof(tcPortN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (strcmp(tcPortN, tcPortP) != 0)
	{
		iRet = appPut(appEthPort, tcPortN, lenEthPort);                   // Save new Port number
		CHECK(iRet>=0, lblDbaErr);
	}

	goto lblEnd;

	// Errors treatment 
	// ****************
lblKO:                                                                    // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblDbaErr:                                                                // Data base error
	sprintf(tcDisplay, "%s\n%s", FMG_ErrorMsg(iRet), "Software Reset Needed");
	GL_Dialog_Message(xGoal, NULL, tcDisplay, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
    return;
}

//****************************************************************************
//                      void ComEthernet (void)                            
//  This function communicates through the Ethernet layer.
//  This function has no parameters.
//  This function has no return value
//****************************************************************************

void ComEthernet(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xLine;
    LL_HANDLE *pvCom=NULL;
	char *pcStr, tcStr[128+1];
	char tcIpAddress[lenEthIpLocal+1];
	char tcPort[lenEthPort+1];
    char tcSnd[MAX_SND+1];
    char tcRsp[MAX_RSP+1];
    char tcDisplay[50+1];
    byte p; // Printer line index
	int iRet=0, iStatus=0;

	// Transmission through Ethernet layer in progress
	// ************************************************
    memset(tcSnd, 0, sizeof(tcSnd));
	memset(tcRsp, 0, sizeof(tcRsp));

	xScreen = GoalCreateScreen(xGoal, txEthernet, NUMBER_OF_LINES(txEthernet), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                                          // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);

    // Open Ethernet layer
	// ===================
    iRet = GoalDspLine(xScreen, 0, "1-comOpen...", &txEthernet[0], 0, true);
    CHECK(iRet>=0, lblKO);
    pvCom = OpenEthernet();                                               // ** Open **
    CHECK(pvCom!=NULL, lblKO);
    iRet = GoalDspLine(xScreen, 1, "1-comOpen OK", &txEthernet[1], 0, true);
    CHECK(iRet>=0, lblKO);
    
	// Configure Ethernet layer
	// ========================
    iRet = GoalDspLine(xScreen, 2, "2-comSet...", &txEthernet[2], 0, true);
    CHECK(iRet>=0, lblKO);
	pcStr = "DHCP";                                                       // No static address => use DHCP
    iRet = GoalDspLine(xScreen, 3, pcStr, &txEthernet[3], 0, true);
    CHECK(iRet>=0, lblKO);
    iRet = SetEthernet(pcStr);                                            // ** Set **
    CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 4, "2-comSet OK", &txEthernet[4], 0, true);
    CHECK(iRet>=0, lblKO);

	// Connect Ethernet layer
    // ======================
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);     // Clear screen
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 0, "3-comConnect...", &txEthernet[0], 0, true);
    CHECK(iRet>=0, lblKO);
	iRet = appGet(appEthIpLocal, tcIpAddress, lenEthIpLocal+1);           // Retrieve local IP
	CHECK(iRet>=0, lblDbaErr);
    iRet = GoalDspLine(xScreen, 1, tcIpAddress, &txEthernet[1], 0, true); // Show local IP
    CHECK(iRet>=0, lblKO);
	iRet = appGet(appEthPort, tcPort, lenEthPort+1);                      // Retrieve port number
	CHECK(iRet>=0, lblDbaErr);
    iRet = GoalDspLine(xScreen, 2, tcPort, &txEthernet[2], 0, true);      // Show port number
    CHECK(iRet>=0, lblKO);
    sprintf (tcStr, "%s|%s", tcIpAddress, tcPort);                        // ** Connect **
	iRet = ConnectEthernet(tcStr);
	CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 3, "3-comConnect OK", &txEthernet[3], 0, true);
    CHECK(iRet>=0, lblKO);

	// Clear sending/receiving buffers
	// ===============================
	iRet = LL_ClearSendBuffer(*pvCom);
    CHECK(iRet==LL_ERROR_OK, lblEnd);
    iRet = LL_ClearReceiveBuffer(*pvCom);
    CHECK(iRet==LL_ERROR_OK, lblEnd);

    // Send data through Ethernet layer
	// ================================
    iRet = GoalDspLine(xScreen, 4, "4-comSend...", &txEthernet[4], 0, true);
	CHECK(iRet>=0, lblKO);
    strcpy(tcSnd, "Hello, do you hear me?\n"                            // Data to send
		          "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n");
    iRet = SendEthernet(tcSnd, (word) strlen(tcSnd));                     // ** Send data **
	CHECK(iRet>=0, lblComKO);
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);     // Clear screen
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 0, "4-comSend OK", &txEthernet[0], 0, true);
	CHECK(iRet>=0, lblKO);

	// Receive data through Ethernet layer
	// ===================================
    iRet = GoalDspLine(xScreen, 1, "5-comRec...", &txEthernet[1], 0, true);
	CHECK(iRet>=0, lblKO);
    iRet = ReceiveEthernet(tcRsp, sizeof(tcRsp), 30);                     // ** Receive data **
	CHECK(iRet>=0, lblComKO);
    if (iRet > MAX_RSP) strcpy (tcRsp, "Buffer overflow Max=512");        // Data overflow
    iRet = GoalDspLine(xScreen, 2, "5-comRec OK", &txEthernet[2], 0, true);
	CHECK(iRet>=0, lblKO);

	// Disconnection
	// =============
	iRet = DisconnectEthernet();                                          // ** Disconnect **
	CHECK(iRet>=0, lblComKO);
	iRet = GoalDspLine(xScreen, 3, "6-comDisconn OK", &txEthernet[3], 0, true);
	CHECK(iRet>=0, lblKO);
	iRet = CloseEthernet();                                               // ** Close **
	CHECK(iRet>=0, lblComKO);
	pvCom=NULL;

	// Display transmission data
	// =========================
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspMultiLine(xScreen, 0, tcRsp, strlen(tcRsp), txEthernet, NUMBER_OF_LINES(txEthernet), 0, true);
	CHECK(iRet>=0, lblKO);                                                // Show data to receive

	// Print transmission data
	// =======================
	p=0;                                                                  // Create document
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);
	CHECK(xDocument!=NULL, lblKO);

	xLine = xPrinter;                                                     // Build document (Demo, Tx/Rx data)
	xLine.eTextAlign = GL_ALIGN_CENTER;
	xLine.bReverse = TRUE;
	xLine.xMargin.usBottom = PIXEL_BOTTOM;
	xLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "Ethernet Demo", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine = xPrinter;
	iRet = GoalPrnLine(xDocument, p++, "Sending:", &xLine);               // Data to send
	CHECK(iRet>=0, lblKO);
    iRet = GoalPrnLine(xDocument, p++, tcSnd, &xLine);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "\nReceiving:", &xLine);           // Data to receive
	CHECK(iRet>=0, lblKO);
    iRet = GoalPrnLine(xDocument, p++, tcRsp, &xLine);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "\n\n\n\n", &xLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                                    // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);                      // Wait for key pressed/touched (shortcut)

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                           // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
	goto lblEnd;
lblComKO:                                        // Communication error
	strcpy(tcDisplay, LL_ErrorMsg(iRet));        // Link Layer error
	if (iRet == LL_Network_GetStatus(LL_PHYSICAL_V_ETHERNET, &iStatus))
	{
		switch(iStatus)
		{
		// Ethernet status
		case LL_STATUS_ETHERNET_NO_DEFAULT_ROUTE:   iStatus=LL_STATUS_ETH_NO_DEFAULT_ROUTE;        break;
		case LL_STATUS_ETHERNET_NOT_PLUGGED:        iStatus=LL_STATUS_ETH_NOT_PLUGGED;             break;
		case LL_STATUS_ETHERNET_BASE_NOT_READY:     iStatus=LL_STATUS_ETH_BASE_NOT_READY;          break;
		case LL_STATUS_ETHERNET_OUT_OF_BASE:        iStatus=LL_STATUS_ETH_OUT_OF_BASE;             break;
		// Bluetooth status
		case LL_BT_STATUS_NO_BASE_ASSOCIATED:       iStatus=LL_STATUS_BT_NO_BASE_ASSOCIATED;       break;
		case LL_BT_STATUS_PERIPHERAL_NOT_AVAILABLE: iStatus=LL_STATUS_BT_PERIPHERAL_NOT_AVAILABLE; break;
		case LL_BT_STATUS_PERIPHERAL_BUSY:          iStatus=LL_STATUS_BT_PERIPHERAL_BUSY;          break;
		case LL_BT_STATUS_BASE_NOT_AVAILABLE:       iStatus=LL_STATUS_BT_BASE_NOT_AVAILABLE;       break;
		default:                                    iStatus=-1;                                    break;
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
		DisconnectEthernet();                    // ** Disconnect **
		CloseEthernet();                         // ** Close **
	}
	if (xScreen)
		GoalDestroyScreen(&xScreen);             // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);         // Destroy document
}


