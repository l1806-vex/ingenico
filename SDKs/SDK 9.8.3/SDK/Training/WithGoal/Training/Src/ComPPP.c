//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  COMPPP.C                           (Copyright INGENICO 2012)
//============================================================================
//  Created :       12-July-2012     Kassovic
//  Last modified : 12-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//              *** PPP communication management ***
//  How to use the linklayer to create a PPP configuration to communicate.
//  This demo is based on PPP over modem.
//             Transmission by point to point protocol PPP
//             Test done with Hyper-terminal Tcp/Ip Winsock
//  !!! Link Layer application must be loaded 3628xxxx.SGN inside the terminal
//      Supports PPP, TCP/IP and SSL protocols.
//      AVL.lib + LinkLayerExeInterface.lib must be implemented to link properly   
//                                                                            
//  List of routines in file :  
//      OpenPPP : Create the PPP configuration.
//      SetPPP : Configure the modem and PPP layer.
//      ConnectPPP : Connect the modem and PPP layer.
//      SendPPP : Send data through the PPP layer.
//      ReceivePPP : Receive data through the PPP layer.
//      DisconnectPPP : Disconnect the PPP layer.                                           
//      ClosePPP : Delete the PPP configuration.
//      PromptPPP : Prompt for PPP's parameters.
//      ComPPP : PPP communication demo.
//                            
//  File history :
//  071212-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
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

#define DIAL_TIMEOUT 30*100
#define TCPIP_TIMEOUT 30*100

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the PPP screen (Goal)
// ===================================
static const ST_DSP_LINE txPPP[] =
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
static TLV_TREE_NODE piDataLinkConfig=NULL;
static TLV_TREE_NODE piTransportConfig=NULL;

//****************************************************************************
//                   LL_HANDLE* OpenPPP (void)
//  This function creates the handle of the PPP layer.      
//  This function has parameters.  
//    ucChn (I-) : chnPPP 
//  This function has return value
//    !NULL : Pointer to the handle configuration.
//    NULL : Processing failed                                        
//****************************************************************************

static LL_HANDLE* OpenPPP(void)
{
    return tvSession;
}

//****************************************************************************
//                    int SetPPP (const char *pcInit)                            
//  This function configures the modem port and the PPP layer.  
//       LL_Configure() : Create Link Layer configuration
//  This function has parameters.  
//    pcInit (I-) : 
//           Phone = Max 64 bytes
//                  Pabx          0
//                  Prefix        00   
//                  Country code  33  
//                  Phone Number  169012345
//                  The '-' is the separator
//           Username = a string (max 30 bytes)
//           Password = a string (max 30 bytes)
//           The '|' is the separator
//           Ex: "0-00-33-169012345|admin|admin"
//  This function has return value
//    >=0 : Configuration done
//     <0 : Configuration failed                                        
//****************************************************************************

static int SetPPP(const char *pcInit) 
{
	// Local variables 
    // ***************
    char *pcPabx, *pcPrefix, *pcCountry, *pcPhone;
    char tcTmp[64+1];
    char tcBuf[64+1];
    char tcUsername[lenPppUser+1];
    char tcPassword[lenPppPass+1];
	int iLen, iRet;
    
    // PPP parameters
    // **************
    if(*pcInit)               
    {
    	memset(tcTmp, 0, sizeof(tcTmp));
		pcInit = parseStr('|', tcTmp, pcInit, sizeof(tcTmp));           // Extract phone
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

	// Parsing Phone
	// *************
    iRet=0;
    iLen=0;
    pcPabx = "";
    pcPrefix = "";
    pcCountry = "";
    pcPhone = tcTmp;
    
	// Extract pabx if found
	// =====================
    while(tcTmp[iLen]) {
        if(tcTmp[iLen] != '-') {
            iLen++;
            continue;
        }
        pcPabx = &tcTmp[iRet];
        tcTmp[iLen++] = 0;
        iRet = iLen;
        pcPhone = &tcTmp[iLen];
        break;
    }

	// Extract prefix if found
	// =======================
    while(tcTmp[iLen]) {
        if(tcTmp[iLen] != '-') {
            iLen++;
            continue;
        }
        pcPrefix = &tcTmp[iRet];
        tcTmp[iLen++] = 0;
        iRet = iLen;
        pcPhone = &tcTmp[iLen];
        break;
    }

	// Extract country code if found
    // =============================
    while(tcTmp[iLen]) {
        if(tcTmp[iLen] != '-') {
            iLen++;
            continue;
        }
        pcCountry = &tcTmp[iRet];
        tcTmp[iLen++] = 0;
        iRet = iLen;
        pcPhone = &tcTmp[iLen];
        break;
    }

    memset(tcBuf, 0, sizeof(tcBuf));
    strcpy(tcBuf, pcPabx);
    strcat(tcBuf, pcPrefix);
    if(*pcCountry) {
        strcat(tcBuf, ",");
        strcat(tcBuf, pcCountry);
        strcat(tcBuf, ",");
    }
    strcat(tcBuf, pcPhone);

	// Create the LinkLayer configuration parameters tree 
	// **************************************************
 
    // Create parameters tree
    // ======================
	piConfig = TlvTree_New(LL_TAG_LINK_LAYER_CONFIG);                                      // LinkLayer parameters Root tag of the configuration tree
    
    // Physical layer parameters  
	// =========================
	piPhysicalConfig = TlvTree_AddChild(piConfig, LL_TAG_PHYSICAL_LAYER_CONFIG, NULL, 0);  // *** Physical layer parameters ***
	TlvTree_AddChildInteger(piPhysicalConfig, LL_PHYSICAL_T_LINK,                          // Modem layer
			                LL_PHYSICAL_V_MODEM, LL_PHYSICAL_L_LINK);                      
	TlvTree_AddChildInteger(piPhysicalConfig, LL_PHYSICAL_T_BAUDRATE,                      // Baud rate 19200
			                LL_PHYSICAL_V_BAUDRATE_19200, LL_PHYSICAL_L_BAUDRATE);                                                                 
	TlvTree_AddChildInteger(piPhysicalConfig, LL_PHYSICAL_T_BITS_PER_BYTE,                 // Data bits 8
			                LL_PHYSICAL_V_8_BITS, LL_PHYSICAL_L_BITS_PER_BYTE);
	TlvTree_AddChildInteger(piPhysicalConfig, LL_PHYSICAL_T_STOP_BITS,                     // Stop bits 1
			                LL_PHYSICAL_V_1_STOP, LL_PHYSICAL_L_STOP_BITS);
   	TlvTree_AddChildInteger(piPhysicalConfig, LL_PHYSICAL_T_PARITY,                        // Parity None
   			                LL_PHYSICAL_V_NO_PARITY, LL_PHYSICAL_L_PARITY);
	TlvTree_AddChildInteger(piPhysicalConfig, LL_MODEM_T_TYPE,                             // Standard Modem
			                LL_MODEM_V_TYPE_STANDARD, LL_MODEM_L_TYPE);
	TlvTree_AddChildInteger(piPhysicalConfig, LL_MODEM_T_DIAL_TIMEOUT,                     // Dial timeout 30s
			                DIAL_TIMEOUT, LL_MODEM_L_DIAL_TIMEOUT);
    TlvTree_AddChildInteger(piPhysicalConfig, LL_MODEM_T_CMD_TERMINATOR,                   // Command line terminator CR 
    		                LL_MODEM_V_CMD_TERMINATOR_CR, LL_MODEM_L_CMD_TERMINATOR);
    TlvTree_AddChildString(piPhysicalConfig,  LL_MODEM_T_INIT_STRING, "ATZE0");            // Modem string ATZE0
    TlvTree_AddChildString(piPhysicalConfig,  LL_MODEM_T_PHONE_NUMBER, tcBuf);             // Phone number
	
    // Data link layer parameters
    // ==========================
    piDataLinkConfig = TlvTree_AddChild(piConfig, LL_TAG_DATA_LINK_LAYER_CONFIG, NULL, 0); // *** Data link layer parameters ***
    TlvTree_AddChildInteger(piDataLinkConfig, LL_DATA_LINK_T_PROTOCOL,                     // PPP protocol
    		                LL_DATA_LINK_V_PPP, LL_DATA_LINK_L_PROTOCOL);
    TlvTree_AddChildString(piDataLinkConfig, LL_PPP_T_LOGIN, tcUsername);                  // Username
    TlvTree_AddChildString(piDataLinkConfig, LL_PPP_T_PASSWORD, tcPassword);               // Password
                        
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
//              int ConnectPPP (const char *pcServer)                            
//  This function connects the modem and the PPP layer.      
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

static int ConnectPPP(const char *pcServer) 
{
	// Local variables 
    // ***************
    char tcAddr[lenPppIpLocal+1];
    char tcPort[lenPppPort+1];
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
//            int SendPPP (const char *pcMsg, word usLen)
//  This function sends data through the PPP layer.      
//       LL_Send() : Send data
//       LL_GetLastError() : Retrieve the last error
//  This function has parameters.  
//    pcMsg (I-) : Data to send
//    usLen (I-) : Number of byte to send
//  This function has return value
//    >=0 : Number of bytes sent
//     <0 : Transmission failed                                       
//****************************************************************************

static int SendPPP(const char *pcMsg, word usLen)
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
//        int ReceivePPP (char *pcMsg, word usLen, byte ucDly)
//  This function receives data through the PPP layer.      
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

static int ReceivePPP(char *pcMsg, word usLen, byte ucDly)
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
//                   int DisconnectPPP (void)                            
//  This function disconnects the PPP layer and the modem.      
//       LL_Disconnect() : Disconnect Link Layer
//  This function has no parameters.  
//  This function has return value
//    >=0 : Disconnect done
//     <0 : Disconnect failed                                       
//****************************************************************************

static int DisconnectPPP(void) 
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
//                     int ClosePPP (void)                            
//  This function deletes the handle of the PPP layer.   
//       LL_Configure() : Delete Link Layer configuration   
//  This function has no parameters.  
//  This function has return value
//    >=0 : Configuration deleted
//     <0 : Processing failed                                        
//****************************************************************************

static int ClosePPP(void)
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
//                      void PromptPPP (void)                            
//  This function asks for the PPP's parameters.   
//  This function has no parameters.  
//  This function has no return value
//****************************************************************************

void PromptPPP(void)
{
	// Local variables 
    // ***************
	char tcMask[256];
	char tcPabxN[lenPppPabx+1], tcPabxP[lenPppPabx+1];
	char tcPrefixN[lenPppPrefix+1], tcPrefixP[lenPppPrefix+1];
	char tcCountryN[lenPppCountry+1], tcCountryP[lenPppCountry+1];
	char tcPhoneN[lenPppPhone+1], tcPhoneP[lenPppPhone+1];
    char tcUserN[lenPppUser+1], tcUserP[lenPppUser+1];
    char tcPassN[lenPppPass+1], tcPassP[lenPppPass+1];
	char tcIpAddressN[lenPppIpLocal+1], tcIpAddressP[lenPppIpLocal+1];
	char tcPortN[lenPppPort+1], tcPortP[lenPppPort+1];
	doubleword uiIp;
	char tcDisplay[50+1];
    int i, iRet;
     
    // Enter pabx
    // **********
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenPppPabx; i++)
		strcat(tcMask, "/d");                                             // Accept only decimal character
	iRet = appGet(appPppPabx, tcPabxP, lenPppPabx+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcPabxN, tcPabxP);
	iRet = GL_Dialog_Text(xGoal, "Pabx", "Enter Pabx :", tcMask, tcPabxN, sizeof(tcPabxN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (strcmp(tcPabxN, tcPabxP) != 0)
	{
		iRet = appPut(appPppPabx, tcPabxN, lenPppPabx); // Save new pabx
		CHECK(iRet>=0, lblDbaErr);
	}

	// Enter prefix
	// ************
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenPppPrefix; i++)
		strcat(tcMask, "/d");                                             // Accept only decimal character
	iRet = appGet(appPppPrefix, tcPrefixP, lenPppPrefix+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcPrefixN, tcPrefixP);
	iRet = GL_Dialog_Text(xGoal, "Prefix", "Enter Prefix :", tcMask, tcPrefixN, sizeof(tcPrefixN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (strcmp(tcPrefixN, tcPrefixP) != 0)
	{
		iRet = appPut(appPppPrefix, tcPrefixN, lenPppPrefix);             // Save new prefix
		CHECK(iRet>=0, lblDbaErr);
	}

	// Enter country code
	// ******************
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenPppCountry; i++)
		strcat(tcMask, "/d");                                             // Accept only decimal character
	iRet = appGet(appPppCountry, tcCountryP, lenPppCountry+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcCountryN, tcCountryP);
	iRet = GL_Dialog_Text(xGoal, "Country Code", "Enter Country Code :", tcMask, tcCountryN, sizeof(tcCountryN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (strcmp(tcCountryN, tcCountryP) != 0)
	{
		iRet = appPut(appPppCountry, tcCountryN, lenPppCountry);          // Save new country code
		CHECK(iRet>=0, lblDbaErr);
	}

	// Enter phone number
	// ******************
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenPppPhone; i++)
		strcat(tcMask, "/d");                                             // Accept only decimal character
	iRet = appGet(appPppPhone, tcPhoneP, lenPppPhone+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcPhoneN, tcPhoneP);
	iRet = GL_Dialog_Text(xGoal, "Phone Number", "Enter Phone# :", tcMask, tcPhoneN, sizeof(tcPhoneN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (strcmp(tcPhoneN, tcPhoneP) != 0)
	{
		iRet = appPut(appPppPhone, tcPhoneN, lenPppPhone);                // Save new phone number
		CHECK(iRet>=0, lblDbaErr);
	}

	// Enter User Name 
	// ***************
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenPppUser; i++)
		strcat(tcMask, "/c");                                             // Accept any character
	iRet = appGet(appPppUser, tcUserP, lenPppUser+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcUserN, tcUserP);
	iRet = GL_Dialog_Text(xGoal, "User Name", "Enter User Name :", tcMask, tcUserN, sizeof(tcUserN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (strcmp(tcUserN, tcUserP) != 0)
	{
		iRet = appPut(appPppUser, tcUserN, lenPppUser);                   // Save new user name
		CHECK(iRet>=0, lblDbaErr);
	}

	// Enter Password 
	// **************
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenPppPass; i++)
		strcat(tcMask, "/c");                                             // Accept any character
	iRet = appGet(appPppPass, tcPassP, lenPppPass+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcPassN, tcPassP);
	iRet = GL_Dialog_Password(xGoal, "Password", "Enter Password :", tcMask, tcPassN, sizeof(tcPassN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (strcmp(tcPassN, tcPassP) != 0)
	{
		iRet = appPut(appPppPass, tcPassN, lenPppPass);                   // Save new password
		CHECK(iRet>=0, lblDbaErr);
	}

    // Enter Local IP address
    // **********************
	iRet = appGet(appPppIpLocal, tcIpAddressP, lenPppIpLocal+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcIpAddressN, tcIpAddressP);
	uiIp = IpToUint(tcIpAddressN);                                        // Convert Ip address to unsigned int
	CHECK(uiIp>=0, lblKO);
	iRet = GL_Dialog_Ip(xGoal, "Local Ip Address", "Enter Ip Address :", (T_GL_HIP)&uiIp, GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	strcpy(tcIpAddressN, UintToIp(uiIp));                                 // Convert unsigned int to Ip address
	if (strcmp(tcIpAddressN, tcIpAddressP) != 0)
	{
		iRet = appPut(appPppIpLocal, tcIpAddressN, lenPppIpLocal);        // Save new Ip address
		CHECK(iRet>=0, lblDbaErr);
	}

	// Enter Port number 
	// *****************
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenPppPort; i++)
		strcat(tcMask, "/d");                                             // Accept only decimal character
	iRet = appGet(appPppPort, tcPortP, lenPppPort+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcPortN, tcPortP);
	iRet = GL_Dialog_Text(xGoal, "Port Number", "Enter Port# :", tcMask, tcPortN, sizeof(tcPortN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (strcmp(tcPortN, tcPortP) != 0)
	{
		iRet = appPut(appPppPort, tcPortN, lenPppPort);                   // Save new Port number
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
//                      void ComPPP (void)                            
//  This function communicates through the PPP layer.   
//  This function has no parameters.
//  This function has no return value
//****************************************************************************

void ComPPP(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xLine;
    LL_HANDLE *pvCom=NULL;
	char *pcStr, tcStr[128+1];
	char tcIpAddress[lenPppIpLocal+1];
	char tcPort[lenPppPort+1];
    char tcSnd[MAX_SND+1];
    char tcRsp[MAX_RSP+1];
    char tcDisplay[50+1];
    byte p; // Printer line index
	int iRet=0, iStatus=0;

	// Transmission through PPP layer in progress
	// ******************************************
    memset(tcSnd, 0, sizeof(tcSnd));
	memset(tcRsp, 0, sizeof(tcRsp));

	xScreen = GoalCreateScreen(xGoal, txPPP, NUMBER_OF_LINES(txPPP), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                                      // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);

    // Open PPP layer 
	// ==============
	iRet = GoalDspLine(xScreen, 0, "1-comOpen...", &txPPP[0], 0, true);
	CHECK(iRet>=0, lblKO);
    pvCom = OpenPPP();                                                // ** Open **
    CHECK(pvCom!=NULL, lblKO);
    iRet = GoalDspLine(xScreen, 1, "1-comOpen OK", &txPPP[1], 0, true);
	CHECK(iRet>=0, lblKO);
    
	// Configure PPP layer
	// ===================
    iRet = GoalDspLine(xScreen, 2, "2-comSet...", &txPPP[2], 0, true);
	CHECK(iRet>=0, lblKO);
	pcStr = tcStr;                                                    // Build param string
	iRet = appGet(appPppPabx, pcStr, lenPppPabx+1);                   // Retrieve pabx
	CHECK(iRet>=0, lblDbaErr);
	if (strlen(pcStr) != 0)
	{
		pcStr+=strlen(pcStr);
		*pcStr='-'; pcStr++;
	}
	iRet = appGet(appPppPrefix, pcStr, lenPppPrefix+1);               // Retrieve prefix
	CHECK(iRet>=0, lblDbaErr);
	if (strlen(pcStr) != 0)
	{
		pcStr+=strlen(pcStr);
		*pcStr='-'; pcStr++;
	}
	iRet = appGet(appPppCountry, pcStr, lenPppCountry+1);             // Retrieve country number
	CHECK(iRet>=0, lblDbaErr);
	if (strlen(pcStr) != 0)
	{
		pcStr+=strlen(pcStr);
		*pcStr='-'; pcStr++;
	}
	iRet = appGet(appPppPhone, pcStr, lenPppPhone+1);                 // Retrieve phone number
	CHECK(iRet>=0, lblDbaErr);
	pcStr += strlen(pcStr);
	*pcStr = '|'; pcStr++;
	iRet = appGet(appPppUser, pcStr, lenPppUser+1);                   // Retrieve username
	CHECK(iRet>=0, lblDbaErr);
	pcStr += strlen(pcStr);
    *pcStr = '|'; pcStr++;
	iRet = appGet(appPppPass, pcStr, lenPppPass+1);                   // Retrieve password
	CHECK(iRet>=0, lblDbaErr);
	pcStr += strlen(pcStr);
	*pcStr = '|';
    iRet = GoalDspLine(xScreen, 3, tcStr, &txPPP[3], 0, true);        // Show param string
	CHECK(iRet>=0, lblKO);
    iRet = SetPPP(tcStr);                                             // ** Set **
    CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 4, "2-comSet OK", &txPPP[4], 0, true);
	CHECK(iRet>=0, lblKO);

	// Connect PPP layer
    // =================
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false); // Clear screen
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 0, "3-comConnect...", &txPPP[0], 0, true);
	CHECK(iRet>=0, lblKO);
	iRet = appGet(appPppIpLocal, tcIpAddress, lenPppIpLocal+1);       // Retrieve local IP
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 1, tcIpAddress, &txPPP[1], 0, true);
	CHECK(iRet>=0, lblKO);                                            // Show IP Address
	iRet = appGet(appPppPort, tcPort, lenPppPort+1);                  // Retrieve port number
	CHECK(iRet>=0, lblDbaErr);
	iRet = GoalDspLine(xScreen, 2, tcPort, &txPPP[2], 0, true);       // Show port number
	CHECK(iRet>=0, lblKO);
    sprintf (tcStr, "%s|%s", tcIpAddress, tcPort);	
	iRet = ConnectPPP(tcStr);                                         // ** Connect **
	CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 3, "3-comConnect OK", &txPPP[3], 0, true);
	CHECK(iRet>=0, lblKO);

	// Clear sending/receiving buffers
	// ===============================
	iRet = LL_ClearSendBuffer(*pvCom);
    CHECK(iRet==LL_ERROR_OK, lblComKO);
    iRet = LL_ClearReceiveBuffer(*pvCom);
    CHECK(iRet==LL_ERROR_OK, lblComKO);

    // Send data through PPP layer
	// ===========================
    iRet = GoalDspLine(xScreen, 4, "4-comSend...", &txPPP[4], 0, true);
	CHECK(iRet>=0, lblKO);
    strcpy(tcSnd, "Hello, do you hear me?\r\n"                        // Data to send
		          "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n");
    iRet = SendPPP(tcSnd, (word) strlen(tcSnd));                      // ** Send data **
	CHECK(iRet>=0, lblComKO);
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspLine(xScreen, 0, "4-comSend OK", &txPPP[0], 0, true);
	CHECK(iRet>=0, lblKO);

	// Receive data through PPP layer
	// ==============================
    iRet = GoalDspLine(xScreen, 1, "5-comRec...", &txPPP[1], 0, true);
	CHECK(iRet>=0, lblKO);
    iRet = ReceivePPP(tcRsp, sizeof(tcRsp), 30);                      // ** Receive data **
	CHECK(iRet>=0, lblComKO);
    if (iRet > MAX_RSP) strcpy (tcRsp, "Buffer overflow Max=512");    // Data overflow
    iRet = GoalDspLine(xScreen, 2, "5-comRec OK", &txPPP[2], 0, true);
	CHECK(iRet>=0, lblKO);

	// Disconnection
	// =============
	iRet = DisconnectPPP();                                           // ** Disconnect **
	CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 3, "6-comDisconn OK", &txPPP[3], 0, true);
	CHECK(iRet>=0, lblKO);
	iRet = ClosePPP();                                                // ** Close **
	CHECK(iRet>=0, lblComKO);
	pvCom=NULL;

	// Display transmission data
	// =========================
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspMultiLine(xScreen, 0, tcRsp, strlen(tcRsp), txPPP, NUMBER_OF_LINES(txPPP), 0, true);
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
	iRet = GoalPrnLine(xDocument, p++, "PPP Demo", &xLine);
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
	if (iRet == LL_Network_GetStatus(LL_PHYSICAL_V_MODEM, &iStatus))
	{
		switch(iStatus)
		{
		// General physical status
		case LL_STATUS_PERIPHERAL_BUSY:             iStatus=LL_STATUS_PHY_PERIPHERAL_BUSY;         break;
		case LL_STATUS_PERIPHERAL_OUT_OF_BASE:      iStatus=LL_STATUS_PHY_PERIPHERAL_OUT_OF_BASE;  break;
		case LL_STATUS_CONVERTER_NOT_PLUGGED:       iStatus=LL_STATUS_PHY_CONVERTER_NOT_PLUGGED;   break;
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
		DisconnectPPP();                         // ** Disconnect **
		ClosePPP();                              // ** Close **
	}
	if (xScreen)
		GoalDestroyScreen(&xScreen);             // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);         // Destroy document
}


