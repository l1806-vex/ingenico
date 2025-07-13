//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  COMETHERNET.C                       (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Ethernet communication management:
//             Transmission by ethernet interface ETH
//             Test done with Hyper-terminal Tcp/Ip Winsock
//  !!! Link Layer application must be loaded 3628xxxx.SGN inside the terminal
//      Supports PPP, TCP/IP and SSL protocols. Submitted under licence.
//  !!! Link Layer provided under SDK package 3429xxxx.SGN does not support
//      TCP/IP excepted under Wifi and Gprs (So this demo will not work).
//      AVL.lib + LinkLayerExeInterface.lib must be implemented to link properly   
//                                                                            
//  List of routines in file :  
//      GetHandle : Handle of the configuration.
//      OpenEthernet : Create the ethernet configuration.
//      SetEthernet : Configure the ethernet layer.
//      ConnectEthernet : Connect the ethernet layer.
//      SendEthernet : Send data through the ethernet layer.
//      ReceiveEthernet : Receive data through the ethernet layer.
//      DisconnectEthernet : Disconnect the ethernet layer.                                           
//      CloseEthernet : Delete the ethernet configuration.
//      PromptEthernet : Prompt for ethernet's paramaters.
//      ComEthernet : Ethernet communication demo.
//                            
//  File history :
//  120508-BK : File created 
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
//       LL_Configure() : Create Link Layer configuration
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
		memset(tcLocalAddr, 0, sizeof(tcLocalAddr));
    	pcInit = parseStr('|', tcLocalAddr, pcInit, sizeof(tcLocalAddr));
        CHECK(pcInit!=NULL, lblKOConfigure);
    
        memset(tcNetmask, 0, sizeof(tcNetmask));
        pcInit = parseStr('|', tcNetmask, pcInit, sizeof(tcNetmask));
        CHECK(pcInit!=NULL, lblKOConfigure);

        memset(tcGateway, 0, sizeof(tcGateway));
        pcInit = parseStr('|', tcGateway, pcInit, sizeof(tcGateway));
        CHECK(pcInit!=NULL, lblKOConfigure);
    }

/*  Extra functions from add-on TCP/IP submit under fees    
    if (tcLocalAddr[0]) {
        uiLocalAddr = __inet_addr(tcLocalAddr);                         // Force local address
        EthernetSetOption(ETH_IFO_ADDR, &uiLocalAddr);
    }

    if (tcNetmask[0]) {
        uiNetmask = __inet_addr(tcNetmask);                             // Force mask
        EthernetSetOption(ETH_IFO_NETMASK, &uiNetmask);
    }
    if(tcGateway[0]) {
        uiGateway = __inet_addr(tcGateway);                             // Force gateway
        EthernetSetOption(ETH_IFO_GATEWAY, &uiGateway);
    }
*/  
    
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

	// Ethernet
	// --------
    TlvTree_AddChildInteger(piPhysicalConfig, 
		                    LL_PHYSICAL_T_LINK,                         // TAG
							LL_PHYSICAL_V_ETHERNET,                     // VALUE
							LL_PHYSICAL_L_LINK);                        // LENGTH 1
        
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
//       LL_Send() : Send data
//       LL_GetLastError() : Retrieve the last error
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

static int ReceiveEthernet(char *pcMsg, word usLen, byte ucDly)
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
//       LL_Disconnect() : Disconnect Link Layer
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
//       LL_Configure() : Delete Link Layer configuration   
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
	char tcIpAddress[lenEthIpLocal+1];
	char tcPort[lenEthPort+1];
    int iRet;

    // Enter Local IP address
    // **********************
	do
	{
		iRet = appGet(appEthIpLocal, tcIpAddress, lenEthIpLocal+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER LOCAL IP", "", tcIpAddress, 0, lenEthIpLocal, 4);
		if (iRet<0)
		{
			DisplaySmall(6, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                     // Cancel, Timeout
	if (iRet==2)                                                // Save Ip address
	{
		iRet = appPut(appEthIpLocal, tcIpAddress, lenEthIpLocal); CHECK(iRet>=0, lblDbaErr);
	}

	// Enter Port number 
	// *****************
	do
	{
		iRet = appGet(appEthPort, tcPort, lenEthPort+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  PORT  NUMBER", "", tcPort, 0, lenEthPort, 0); //CHECK(iRet>=0, lblKO);
		if (iRet<0)
		{
			DisplaySmall(5, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                    // Cancel, Timeout
	if (iRet==2)                                               // Save port number
	{
		iRet = appPut(appEthPort, tcPort, lenEthPort); CHECK(iRet>=0, lblDbaErr);
	}
		
	goto lblEnd;

	// Errors treatment 
	// ****************
lblDbaErr:
	_clrscr();                                                 // Clear screen
	DisplayMedium(0, 0, FMG_ErrorMsg(iRet));                   // FMG error
	DisplayMedium(1, 0, "Reset Needed");                       // Rebuild data base
	ttestall(0, 5*100);                                        // Delay 5s
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
    LL_HANDLE *pvCom=NULL;
	char *pcStr, tcStr[128+1];
	char tcIpAddress[lenEthIpLocal+1];
	char tcPort[lenEthPort+1];
    char tcSnd[MAX_SND+1];
    char tcRsp[MAX_RSP+1];
	int iRet=0, iStatus=0;

	// Transmission through Ethernet layer in progress
	// ************************************************
    memset(tcSnd, 0, sizeof(tcSnd));
	memset(tcRsp, 0, sizeof(tcRsp));
	_clrscr();                                                     // Clear screen

    // Open Ethernet layer
	// ===================
	DisplayMedium(0, 0, "1-comOpen...");                           // Display open message
    pvCom = OpenEthernet(); CHECK(pvCom!=NULL, lblKO);             // ** Open **
    DisplayMedium(1, 0, "1-comOpen OK");                           // Display open OK
    
	// Configure Ethernet layer
	// ========================
	DisplayMedium(2, 0, "2-comSet...");                            // Display set message
	pcStr = "";                                                    // No static addess => use DHCP
    DisplayMedium(3, 0, pcStr);                                    // Display config
    iRet = SetEthernet(pcStr); CHECK(iRet>=0, lblComKO);           // ** Set **
	_clrscr();                                                     // Clear screen
    DisplayMedium(0, 0, "2-comSet OK");                            // Display set OK

	// Connect Ethernet layer
    // ======================
	DisplayMedium(1, 0, "3-comConnect...");                        // Display connect message
	iRet = appGet(appEthIpLocal, tcIpAddress, lenEthIpLocal+1);    // Retrieve local IP
	CHECK(iRet>=0, lblDbaErr);
    DisplayMedium(2, 0, tcIpAddress);                              // Display IP Address
	iRet = appGet(appEthPort, tcPort, lenEthPort+1);               // Retrieve port number
	CHECK(iRet>=0, lblDbaErr);
    DisplayMedium(3, 0, tcPort);                                   // Display port number
    sprintf (tcStr, "%s|%s", tcIpAddress, tcPort);
	iRet = ConnectEthernet(tcStr); CHECK(iRet>=0, lblComKO);       // ** Connect **
	_clrscr();                                                     // Clear screen
    DisplayMedium(0, 0, "3-comConnect OK");                        // Display connect OK

	// Clear sending/receiving buffers
	// ===============================
	iRet = LL_ClearSendBuffer(*pvCom);                             // Clear sending buffer
    CHECK(iRet==LL_ERROR_OK, lblEnd);
    iRet = LL_ClearReceiveBuffer(*pvCom);                          // Clear receiving buffer
    CHECK(iRet==LL_ERROR_OK, lblEnd);

    // Send data through Ethernet layer
	// ================================
	DisplayMedium(1, 0, "4-comSend...");                           // Display send message
    strcpy(tcSnd, "Hello, do you hear me?\r\n"                     // Data to send
		          "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n");
    iRet = SendEthernet(tcSnd, (word) strlen(tcSnd));              // ** Send data **
	CHECK(iRet>=0, lblComKO);
	DisplayMedium(2, 0, "4-comSend OK");                           // Display send OK

	// Receive data through Ethernet layer
	// ===================================
	DisplayMedium(3, 0, "5-comRec...");                            // Display receive message
    iRet = ReceiveEthernet(tcRsp, sizeof(tcRsp), 30);              // ** Receive data **
	CHECK(iRet>=0, lblComKO);
    if (iRet > MAX_RSP) strcpy (tcRsp, "Buffer overflow Max=512"); // Data overflow
	_clrscr();                                                     // Clear screen
	DisplayMedium(0, 0, "5-comRec OK");                            // Display receive OK

	// Disconnection
	// =============
	iRet = DisconnectEthernet();                                   // ** Disconnect **
	CHECK(iRet>=0, lblComKO);
	DisplayMedium(1, 0, "6-comDisconn OK");                        // Display disconnect OK
	iRet = CloseEthernet();                                        // ** Close **
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
	iRet = pprintf("\x1b""E""      ETHERNET Demo\n\n"              // Print demo in progress
		           "\x1b""F"); CHECK(iRet>=0, lblKO);      
    iRet = pprintf("Sending:\n"); CHECK(iRet>=0, lblKO);           // Print data to send
	iRet = Print24(tcSnd, strlen(tcSnd)); CHECK(iRet>=0, lblKO);
    iRet = pprintf("\nReceiving:\n"); CHECK(iRet>=0, lblKO);       // Print data to receive
	iRet = Print24(tcRsp, strlen(tcRsp)); CHECK(iRet>=0, lblKO);
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
		DisplayMedium(1, 0, LL_ErrorMsg(iStatus));                 // Link Layer status
	}
	ttestall(0, 5*100);                                            // Delay 5s
	goto lblEnd;
lblDbaErr:                                                         // Data base error      
    _clrscr();                                                     // Clear screen
    DisplayMedium(0, 0, FMG_ErrorMsg(iRet));                       // FMG error
    DisplayMedium(1, 0, "Reset Needed");                           // Rebuild data base
    ttestall(0, 5*100);                                            // Delay 5s
lblEnd:
    if (pvCom) {
		DisconnectEthernet();                                      // ** Disconnect **
		CloseEthernet();                                           // ** Close **
	}
}


