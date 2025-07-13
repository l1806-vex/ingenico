//****************************************************************************
//       INGENICO                                INGEDEV 7                  
//============================================================================
//       FILE  COMSERIAL.C                        (Copyright INGENICO 2012)
//============================================================================
//  Created :       11-July-2012     Kassovic
//  Last modified : 11-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                 *** USB communication management ***
//  How to use the linklayer to create an USB configuration to communicate.
//                 Transmission by USB communication
//                   Test done with Hyper-terminal
//  !!! Link Layer application must be loaded 3628xxxx.SGN inside the terminal
//      AVL.lib + LinkLayerExeInterface.lib must be implemented to link properly   
//                                                                            
//  List of routines in file :  
//      OpenUSB : Create the USB port.
//      SetUSB : Configure the USB port.
//      ConnectUSB : Connect the USB port.
//      SendUSB : Send data through the USB port.
//      ReceiveUSB : Receive data through the USB port.
//      DisconnectUSB : Disconnect the USB port.                                           
//      CloseUSB : Delete the USB port.
//      ComUSB : USB communication demo.
//                            
//  File history :
//  071112-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "LinkLayer.h"
#include "TlvTree.h"
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

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the USB screen (Goal)
// ===================================
static const ST_DSP_LINE txUSB[] =
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
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xLine;
    LL_HANDLE *pvCom=NULL;
    char tcSnd[MAX_SND+1];
    char tcRsp[MAX_RSP+1];
    char tcDisplay[50+1];
    byte p; // Printer line index
	int iRet=0, iStatus=0;

	// Transmission through USB port in progress
	// *****************************************
    memset(tcSnd, 0, sizeof(tcSnd));
	memset(tcRsp, 0, sizeof(tcRsp));

	xScreen = GoalCreateScreen(xGoal, txUSB, NUMBER_OF_LINES(txUSB), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);                                            // Create screen and clear it

    // Open USB port 
	// =============
	iRet = GoalDspLine(xScreen, 0, "1-comOpen...", &txUSB[0], 0, true);
	CHECK(iRet>=0, lblKO);
    pvCom = OpenUSB();                                                // ** Open **
    CHECK(pvCom!=NULL, lblKO);
    iRet = GoalDspLine(xScreen, 1, "1-comOpen OK", &txUSB[1], 0, true);
	CHECK(iRet>=0, lblKO);

	// Configure USB port
	// ==================
    iRet = GoalDspLine(xScreen, 2, "2-comSet...", &txUSB[2], 0, true);
	CHECK(iRet>=0, lblKO);
    iRet = SetUSB();                                                  // ** Set **
    CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 3, "2-comSet OK", &txUSB[3], 0, true);
	CHECK(iRet>=0, lblKO);

	// Connect USB port
	// ================
    iRet = GoalDspLine(xScreen, 4, "3-comConnect...", &txUSB[4], 0, true);
	CHECK(iRet>=0, lblKO);
    iRet = ConnectUSB();                                              // ** Connect **
    CHECK(iRet>=0, lblComKO);
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false); // Clear screen
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 0, "3-comConnect OK", &txUSB[0], 0, true);
	CHECK(iRet>=0, lblKO);

	// Clear sending/receiving buffers
	// ===============================
	iRet = LL_ClearSendBuffer(*pvCom);
    CHECK(iRet==LL_ERROR_OK, lblComKO);
    iRet = LL_ClearReceiveBuffer(*pvCom);
    CHECK(iRet==LL_ERROR_OK, lblComKO);

    // Send data through USB port
	// ==========================
    iRet = GoalDspLine(xScreen, 1, "4-comSend...", &txUSB[1], 0, true);
	CHECK(iRet>=0, lblKO);
    strcpy(tcSnd, "Hello, do you hear me?\r\n"                        // Data to send
		          "Hello, do you hear me?\r\n"
			   	  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n");
    iRet = SendUSB(tcSnd, (word) strlen(tcSnd));                      // ** Send data **
	CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 2, "4-comSend OK", &txUSB[2], 0, true);
	CHECK(iRet>=0, lblKO);

	// Receive data through USB port
	// =============================
    iRet = GoalDspLine(xScreen, 3, "5-comRec...", &txUSB[3], 0, true);
	CHECK(iRet>=0, lblKO);
    iRet = ReceiveUSB(tcRsp, sizeof(tcRsp), 30);                      // ** Receive data **
	CHECK(iRet>=0, lblComKO);
    if (iRet > MAX_RSP) strcpy (tcRsp, "Buffer overflow Max=512");    // Data overflow
    iRet = GoalDspLine(xScreen, 4, "5-comRec OK", &txUSB[4], 0, true);
	CHECK(iRet>=0, lblKO);

	// Disconnection
	// =============
	iRet = DisconnectUSB();                                           // ** Disconnect **
	CHECK(iRet>=0, lblComKO);
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false); // Clear screen
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 0, "6-comDisconn OK", &txUSB[0], 0, true);
	CHECK(iRet>=0, lblKO);
	iRet = CloseUSB();                                                // ** Close **
	CHECK(iRet>=0, lblComKO);
	pvCom=NULL;

	// Display transmission data
	// =========================
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);  // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspMultiLine(xScreen, 0, tcRsp, strlen(tcRsp), txUSB, NUMBER_OF_LINES(txUSB), 0, true);
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
	iRet = GoalPrnLine(xDocument, p++, "USB Demo", &xLine);
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
		strcat(tcDisplay, "\n");
		strcat(tcDisplay, LL_ErrorMsg(iStatus)); // Link Layer status
	}
	if (iRet != LL_ERROR_TIMEOUT)                // Cancel or timeout ?
		GL_Dialog_Message(xGoal, NULL, tcDisplay, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
    if (pvCom) {
		DisconnectUSB();                         // ** Disconnect **
		CloseUSB();                              // ** Close **
	}
	if (xScreen)
		GoalDestroyScreen(&xScreen);             // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);         // Destroy document
}
