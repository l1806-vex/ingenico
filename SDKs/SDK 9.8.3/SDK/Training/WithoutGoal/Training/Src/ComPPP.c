//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  COMPPP.C                           (Copyright INGENICO 2009)   
//============================================================================
//  Created :       19-April-2009     Kassovic                                 
//  Last modified : 19-April-2009     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Ethernet communication management:
//             Transmission by point to point protocol PPP
//             Test done with Hyper-terminal Tcp/Ip Winsock
//  !!! Link Layer application must be loaded 3628xxxx.SGN inside the terminal
//      Supports PPP, TCP/IP and SSL protocols. Submitted under licence.
//  !!! Link Layer provided under SDK package 3429xxxx.SGN does not support
//      TCP/IP excepted under Wifi and Gprs (So this demo will not work).
//      AVL.lib + LinkLayerExeInterface.lib must be implemented to link properly   
//                                                                            
//  List of routines in file :  
//      GetHandle : Handle of the configuration.
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
//  190409-BK : File created 
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
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

#define DIAL_TIMEOUT 30*100
#define TCPIP_TIMEOUT 30*100

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
static LL_HANDLE tvSession[1] = {NULL};

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
	char tcPabx[lenPppPabx+1];
	char tcPrefix[lenPppPrefix+1];
	char tcCountry[lenPppCountry+1];
	char tcPhone[lenPppPhone+1];
    char tcUser[lenPppUser+1];
    char tcPass[lenPppPass+1];
	char tcIpAddress[lenPppIpLocal+1];
	char tcPort[lenPppPort+1];
    int iRet;
     
    // Enter pabx
    // **********
    do
    {
    	iRet = appGet(appPppPabx, tcPabx, lenPppPabx+1); CHECK(iRet>=0, lblDbaErr);
    	iRet = ShowEntry("ENTER  PABX", "", tcPabx, 0, lenPppPabx, 0);
		if (iRet<0)
		{
			DisplaySmall(5, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                           // Cancel, Timeout
	if (iRet==2)                                                      // Save pabx
	{
		iRet = appPut(appPppPabx, tcPabx, lenPppPabx); CHECK(iRet>=0, lblDbaErr);
	}
		
	// Enter prefix
	// ************
	do
	{
		iRet = appGet(appPppPrefix, tcPrefix, lenPppPrefix+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  PREFIX", "", tcPrefix, 0, lenPppPrefix, 0);
		if (iRet<0)
		{
			DisplaySmall(5, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                           // Cancel, Timeout
	if (iRet==2)                                                      // Save prefix
	{
		iRet = appPut(appPppPrefix, tcPrefix, lenPppPrefix); CHECK(iRet>=0, lblDbaErr);
	}
		
	// Enter country code
	// ******************
	do
	{
		iRet = appGet(appPppCountry, tcCountry, lenPppCountry+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  COUNTRY  CODE", "", tcCountry, 0, lenPppCountry, 0);
		if (iRet<0)
		{
			DisplaySmall(5, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                           // Cancel, Timeout
	if (iRet==2)                                                      // Save country code
	{
		iRet = appPut(appPppCountry, tcCountry, lenPppCountry); CHECK(iRet>=0, lblDbaErr);
	}
		
	// Enter phone number
	// ******************
	do
	{
		iRet = appGet(appPppPhone, tcPhone, lenPppPhone+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  PHONE  NUMBER", "", tcPhone, 0, lenPppPhone, 0);
		if (iRet<0)
		{
			DisplaySmall(5, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                           // Cancel, Timeout
	if (iRet==2)                                                      // Save phone number
	{
		iRet = appPut(appPppPhone, tcPhone, lenPppPhone); CHECK(iRet>=0, lblDbaErr);
	}
		
	// Enter User Name 
	// ***************
	do
	{
		iRet = appGet(appPppUser, tcUser, lenPppUser+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  USERNAME", "", tcUser, 0, lenPppUser, 0);
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
		iRet = appPut(appPppUser, tcUser, lenPppUser); CHECK(iRet>=0, lblDbaErr);
	}

	// Enter Password 
	// **************
	do
	{
		iRet = appGet(appPppPass, tcPass, lenPppPass+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  PASSWORD", "", tcPass, 0, lenPppPass, 0);
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
		iRet = appPut(appPppPass, tcPass, lenPppPass); CHECK(iRet>=0, lblDbaErr);
	}
		
	// Enter Local IP address
	// **********************
	do
	{
		iRet = appGet(appPppIpLocal, tcIpAddress, lenPppIpLocal+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER LOCAL IP", "", tcIpAddress, 0, lenPppIpLocal, 4);
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
		iRet = appPut(appPppIpLocal, tcIpAddress, lenPppIpLocal); CHECK(iRet>=0, lblDbaErr);
	}

	// Enter Port number 
	// *****************
	do
	{
		iRet = appGet(appPppPort, tcPort, lenPppPort+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  PORT  NUMBER", "", tcPort, 0, lenPppPort, 0);
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
		iRet = appPut(appPppPort, tcPort, lenPppPort); CHECK(iRet>=0, lblDbaErr);
	}
		
	goto lblEnd;

	// Errors treatment 
	// ****************
lblDbaErr:
	_clrscr();                                                        // Clear screen
	DisplayMedium(0, 0, FMG_ErrorMsg(iRet));                          // FMG error
	DisplayMedium(1, 0, "Reset Needed");                              // Rebuild data base
	ttestall(0, 5*100);                                               // Delay 5s
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
    LL_HANDLE *pvCom=NULL;
	char *pcStr, tcStr[128+1];
	char tcIpAddress[lenPppIpLocal+1];
	char tcPort[lenPppPort+1];
    char tcSnd[MAX_SND+1];
    char tcRsp[MAX_RSP+1];
	int iRet=0, iStatus=0;

	// Transmission throught PPP layer in progress
	// ********************************************
    memset(tcSnd, 0, sizeof(tcSnd));
	memset(tcRsp, 0, sizeof(tcRsp));
	_clrscr();                                                     // Clear screen

    // Open PPP layer 
	// ==============
	DisplayMedium(0, 0, "1-comOpen...");                           // Display open message
    pvCom = OpenPPP(); CHECK(pvCom!=NULL, lblKO);                  // ** Open **
    DisplayMedium(1, 0, "1-comOpen OK");                           // Display open OK
    
	// Configure PPP layer
	// ===================
	DisplayMedium(2, 0, "2-comSet...");                            // Display set message
	pcStr = tcStr;                                                 // Build param string
	iRet = appGet(appPppPabx, pcStr, lenPppPabx+1);                // Retrieve pabx
	CHECK(iRet>=0, lblDbaErr);
	if (strlen(pcStr) != 0)
	{
		pcStr+=strlen(pcStr);
		*pcStr='-'; pcStr++;
	}
	iRet = appGet(appPppPrefix, pcStr, lenPppPrefix+1);            // Retrieve prefix
	CHECK(iRet>=0, lblDbaErr);
	if (strlen(pcStr) != 0)
	{
		pcStr+=strlen(pcStr);
		*pcStr='-'; pcStr++;
	}
	iRet = appGet(appPppCountry, pcStr, lenPppCountry+1);          // Retrieve country number
	CHECK(iRet>=0, lblDbaErr);
	if (strlen(pcStr) != 0)
	{
		pcStr+=strlen(pcStr);
		*pcStr='-'; pcStr++;
	}
	iRet = appGet(appPppPhone, pcStr, lenPppPhone+1);              // Retrieve phone number
	CHECK(iRet>=0, lblDbaErr);
	pcStr += strlen(pcStr);
	*pcStr = '|'; pcStr++;
	iRet = appGet(appPppUser, pcStr, lenPppUser+1);                // Retrieve username
	CHECK(iRet>=0, lblDbaErr);
	pcStr += strlen(pcStr);
    *pcStr = '|'; pcStr++;
	iRet = appGet(appPppPass, pcStr, lenPppPass+1);                // Retrieve password
	CHECK(iRet>=0, lblDbaErr);
	pcStr += strlen(pcStr);
	*pcStr = '|';
	DisplayMedium(3, 0, tcStr);                                    // Display param string
    iRet = SetPPP(tcStr); CHECK(iRet>=0, lblComKO);                // ** Set **
	_clrscr();                                                     // Clear screen
    DisplayMedium(0, 0, "2-comSet OK");                            // Display set OK

	// Connect PPP layer
    // =================
	DisplayMedium(1, 0, "3-comConnect...");                        // Display connect message
	iRet = appGet(appPppIpLocal, tcIpAddress, lenPppIpLocal+1);    // Retrieve local IP
	CHECK(iRet>=0, lblDbaErr);
    DisplayMedium(2, 0, tcIpAddress);                              // Display IP Address (entry manually)
	iRet = appGet(appPppPort, tcPort, lenPppPort+1);               // Retrieve port number
	CHECK(iRet>=0, lblDbaErr);
    DisplayMedium(3, 0, tcPort);                                   // Display port number
    sprintf (tcStr, "%s|%s", tcIpAddress, tcPort);	
	iRet = ConnectPPP(tcStr); CHECK(iRet>=0, lblComKO);            // ** Connect **
	_clrscr();                                                     // Clear screen
    DisplayMedium(0, 0, "3-comConnect OK");                        // Display connect OK

	// Clear sending/receiving buffers
	// ===============================
	iRet = LL_ClearSendBuffer(*pvCom);                             // Clear sending buffer
    CHECK(iRet==LL_ERROR_OK, lblComKO);
    iRet = LL_ClearReceiveBuffer(*pvCom);                          // Clear receiving buffer
    CHECK(iRet==LL_ERROR_OK, lblComKO);

    // Send data through PPP layer
	// ===========================
	DisplayMedium(1, 0, "4-comSend...");                           // Display send message
    strcpy(tcSnd, "Hello, do you hear me?\r\n"                     // Data to send
		          "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n");
    iRet = SendPPP(tcSnd, (word) strlen(tcSnd));                   // ** Send data **
	CHECK(iRet>=0, lblComKO);
	DisplayMedium(2, 0, "4-comSend OK");                           // Display send OK

	// Receive data through PPP layer
	// ==============================
	DisplayMedium(3, 0, "5-comRec...");                            // Display receive message
    iRet = ReceivePPP(tcRsp, sizeof(tcRsp), 30);                   // ** Receive data **
	CHECK(iRet>=0, lblComKO);
    if (iRet > MAX_RSP) strcpy (tcRsp, "Buffer overflow Max=512"); // Data overflow
	_clrscr();                                                     // Clear screen
	DisplayMedium(0, 0, "5-comRec OK");                            // Display receive OK

	// Disconnection
	// =============
	iRet = DisconnectPPP();                                        // ** Disconnect **
	CHECK(iRet>=0, lblComKO);
	DisplayMedium(1, 0, "6-comDisconn OK");                        // Display disconnect OK
	iRet = ClosePPP();                                             // ** Close **
	CHECK(iRet>=0, lblComKO);
	pvCom=NULL;

	// Display transmission data
	// =========================
	_clrscr();                                                     // Clear screen
	DisplaySmall(0, 0, "RECEIVING:");                              // Display data to receive
	iRet = Display25(1, tcRsp, strlen(tcRsp)); CHECK(iRet>=0, lblKO);
    DisplaySmall(7, 6, "Press a key");

	// Print transmission data
	// =======================
	iRet = pprintf("\x1b""E""           PPP Demo\n\n"              // Print demo in progress
		           "\x1b""F"); CHECK(iRet>=0, lblKO);      
    iRet = pprintf("Sending:\n"); CHECK(iRet>=0, lblKO);           // Print data to send
	iRet = Print24(tcSnd, sizeof(tcSnd)); CHECK(iRet>=0, lblKO);
    iRet = pprintf("\nReceiving:\n"); CHECK(iRet>=0, lblKO);       // Print data to receive
	iRet = pprintf(tcRsp, sizeof(tcRsp)); CHECK(iRet>=0, lblKO);
    iRet = pprintf("\n\n\n\n\n\n"); CHECK(iRet>=0, lblKO);

	reset_buf(pxKbd, _receive_id);                                 // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                    // Wait until key pressed or timeout
	reset_buf(pxKbd, _receive_id);                                 // Reset keyboard FIFO to clear key pressed

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                             // None-classified low level error
    _clrscr();                                                     // Clear screen
    DisplayMedium(0, 0, "Processing Error");                       // Oops! error
    ttestall(0,5*100);                                             // Delay 5s 
    goto lblEnd;
lblComKO:                                                          // Communication error
    _clrscr();                                                     // Clear screen
    DisplayMedium(0, 0, LL_ErrorMsg(iRet));                        // Link Layer error
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
		DisplayMedium(1, 0, LL_ErrorMsg(iStatus));                 // Link Layer status
	}
	ttestall(0,5*100);                                             // Delay 5s
    goto lblEnd;
lblDbaErr:                                                         // Data base error
	_clrscr();                                                     // Clear screen
	DisplayMedium(0, 0, FMG_ErrorMsg(iRet));                       // FMG error
	DisplayMedium(1, 0, "Reset Needed");                           // Rebuild data base
	ttestall(0, 5*100);                                            // Delay 5s
lblEnd:
    if (pvCom) {
		DisconnectPPP();                                           // ** Disconnect **
		ClosePPP();                                                // ** Close **
	}
}


