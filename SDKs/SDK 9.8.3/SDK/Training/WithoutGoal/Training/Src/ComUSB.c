//****************************************************************************
//       INGENICO                                INGEDEV 7                  
//============================================================================
//       FILE  COMSERIAL.C                        (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  USB communication management:
//             Transmission by USB communication
//             Test done with Hyper-terminal
//  !!! Link Layer application must be loaded 34290302.SGN inside the terminal
//      AVL.lib + LinkLayerExeInterface.lib must be implemented to link properly   
//                                                                            
//  List of routines in file :  
//      GetHandle : Handle of the configuration.
//      OpenUSB : Create the USB port.
//      InitUSB : Configure the USB port.
//      ConnectUSB : Connect the USB port.
//      SendUSB : Send data through the USB port.
//      ReceiveUSB : Receive data through the USB port.
//      DisconnectUSB : Disconnect the USB port.                                           
//      CloseUSB : Delete the USB port.
//      ComUSB : USB communication demo.
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
#include "LinkLayer.h"
#include "TlvTree.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern FILE *pxKbd;      // Peripheral file Keyboard

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define MAX_SND  512
#define MAX_RSP  512

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

//****************************************************************************
//                    LL_HANDLE* OpenUSB (void)
//  This function creates the handle of the USB port.      
//  This function has no parameter.
//  This function has return value
//    !NULL : Pointer to the handle of the USB port created
//    NULL : Processing failed                                        
//****************************************************************************

static LL_HANDLE* OpenUSB(void)
{
    return tvSession;
}

//****************************************************************************
//                          int SetUSB (void)                            
//  This function configures the USB port.     
//       LL_Configure() : Create Link Layer configuration
//  This function has no parameters.  
//  This function has return value
//    >=0 : Configuration done
//     <0 : Configuration failed                                        
//****************************************************************************

static int SetUSB(void) 
{
	// Local variables 
    // ***************
    int iRet;

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
     
    // Port USB
	// --------
	TlvTree_AddChildInteger(piPhysicalConfig, 
		                    LL_PHYSICAL_T_LINK,                       // TAG
		                    LL_PHYSICAL_V_USB,                        // VALUE
							LL_PHYSICAL_L_LINK);                      // LENGTH 1 byte
	
	// Link Layer configuration
	// ************************
    iRet = LL_Configure(tvSession, piConfig);

	// Release the LinkLayer configuration parameters tree
	// ***************************************************
	TlvTree_Release(piConfig);

	return iRet;
}

//****************************************************************************
//                          int ConnectUSB (void)                            
//  This function connects the USB port.     
//       LL_Connect() : Connect Link Layer
//  This function has no parameters.  
//  This function has return value
//    >=0 : Connect done
//     <0 : Connect failed                                        
//****************************************************************************

static int ConnectUSB(void)
{
	// Local variables 
    // ***************
    int iRet;
    
    // Link Layer connection
	// *********************
    iRet = LL_Connect(tvSession[0]);

    return iRet;
}

//****************************************************************************
//              int SendUSB (const char *pcMsg, word usLen)
//  This function sends data through the USB port.      
//       LL_Send() : Send data
//       LL_GetLastError() : Retrieve the last error
//  This function has parameters.  
//    pcMsg (I-) : Data to send
//    usLen (I-) : Number of byte to send
//  This function has return value
//    >=0 : Number of bytes sent
//     <0 : Transmission failed                                       
//****************************************************************************

static int SendUSB(const char *pcMsg, word usLen)
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
//        int ReceiveUSB (char *pcMsg, word usLen, byte ucDly)
//  This function receives data through the USB port.      
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

static int ReceiveUSB(char *pcMsg, word usLen, byte ucDly)
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
//                     int DisconnectUSB (void)                            
//  This function disconnects the USB port.      
//       LL_Disconnect() : Disconnect Link Layer
//  This function has no parameters.  
//  This function has return value
//    >=0 : Disconnect done
//     <0 : Disconnect failed                                       
//****************************************************************************

static int DisconnectUSB(void) 
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
//                     int CloseUSB (void)                            
//  This function deletes the handle of the USB port.   
//       LL_Configure() : Delete Link Layer configuration   
//  This function has no parameters.  
//  This function has return value
//    >=0 : Configuration deleted
//     <0 : Processing failed                                        
//****************************************************************************

static int CloseUSB(void)
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
//                      void ComUSB(void)                            
//  This function communicates through USB port.   
//  This function has parameters.
//  This function has no return value
//****************************************************************************

void ComUSB(void) 
{
	// Local variables 
    // ***************
    LL_HANDLE *pvCom=NULL;
    char tcSnd[MAX_SND+1];
    char tcRsp[MAX_RSP+1];
	int iRet=0, iStatus=0;

	// Transmission through USB port in progress
	// *****************************************
    memset(tcSnd, 0, sizeof(tcSnd));
	memset(tcRsp, 0, sizeof(tcRsp));
	_clrscr();                                                     // Clear screen

    // Open USB port 
	// =============
	DisplayMedium(0, 0, "1-comOpen..     ");                       // Display start message
    pvCom = OpenUSB(); CHECK(pvCom!=NULL, lblKO);                  // ** Open **
    DisplayMedium(1, 0, "1-comOpen OK    ");                       // Display open OK

	// Configure USB port
	// ==================
	DisplayMedium(2, 0, "2-comSet...     ");                       // Display set message
    iRet = SetUSB(); CHECK(iRet>=0, lblComKO);                     // ** Set **
    DisplayMedium(3, 0, "2-comSet OK     ");                       // Display set OK

	// Connect USB port
	// ================
	_clrscr();                                                     // Clear screen
	DisplayMedium(0, 0, "3-comConnect... ");                       // Display connect message
    iRet = ConnectUSB(); CHECK(iRet>=0, lblComKO);                 // ** Connect **
    DisplayMedium(1, 0, "3-comConnect OK ");                       // Display connect OK

	// Clear sending/receiving buffers
	// ===============================
	iRet = LL_ClearSendBuffer(*pvCom);                             // Clear sending buffer
    CHECK(iRet==LL_ERROR_OK, lblComKO);
    iRet = LL_ClearReceiveBuffer(*pvCom);                          // Clear receiving buffer
    CHECK(iRet==LL_ERROR_OK, lblComKO);

    // Send data through USB port
	// ==========================
	DisplayMedium(2, 0, "4-comSend...    ");                       // Display send message
    strcpy(tcSnd, "Hello, do you hear me?\r\n"                     // Data to send
		          "Hello, do you hear me?\r\n"
			   	  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n");
    iRet = SendUSB(tcSnd, (word) strlen(tcSnd));                   // ** Send data **
	CHECK(iRet>=0, lblComKO);
	DisplayMedium(3, 0, "4-comSend OK    ");                       // Display send OK

	// Receive data through USB port
	// =============================
	_clrscr();                                                     // Clear screen
	DisplayMedium(0, 0, "5-comRec...     ");                       // Display receive message
    iRet = ReceiveUSB(tcRsp, sizeof(tcRsp), 30);                   // ** Receive data **
	CHECK(iRet>=0, lblComKO);
    if (iRet > MAX_RSP) strcpy (tcRsp, "Buffer overflow Max=512"); // Data overflow
	DisplayMedium(1, 0, "5-comRec OK     ");                       // Display receive OK

	// Disconnection
	// =============
	iRet = DisconnectUSB();                                        // ** Disconnect **
	CHECK(iRet>=0, lblComKO);
	DisplayMedium(2, 0, "6-comDisconn OK");                        // Display disconnect OK
	iRet = CloseUSB();                                             // ** Close **
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
	iRet = pprintf("\x1b""E""          USB Demo\n\n"               // Print demo in progress
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
	if (iRet == LL_Network_GetStatus(LL_PHYSICAL_V_USB, &iStatus))
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
lblEnd:
    if (pvCom) {
		DisconnectUSB();                                           // ** Disconnect **
		CloseUSB();                                                // ** Close **
	}
}
