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
//                   *** Serial communication management ***
//  How to use the linklayer to create a serial configuration to communicate.
//             Transmission by serial communication COM0
//             Test done with Hyper-terminal (8-N-1-115200)
//  !!! Link Layer application must be loaded 3628xxxx.SGN inside the terminal
//      AVL.lib + LinkLayerExeInterface.lib must be implemented to link properly   
//                                                                            
//  List of routines in file :  
//      GetHandle : Handle of the configuration.
//      OpenSerial : Create the serial port.
//      SetSerial : Configure the serial port.
//      ConnectSerial : Connect the serial port.
//      SendSerial : Send data through the serial port.
//      ReceiveSerial : Receive data through the serial port.
//      DisconnectSerial : Disconnect the serial port.                                           
//      CloseSerial : Delete the serial port.
//      PromptSerial : Prompt for serial's parameters.
//      ComSerial : COM0 communication demo.
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
enum eChn {          // Com channels
    chnBeg,          // Start sentinel
    chnCom0,         // Com0 Rs232
    chnCom1,         // Com1 Rs232
    chnCom2,         // Com2 Rs232
    chnComExt,       // ComExt Usb->Rs232
    chnEnd           // End sentinel
};

typedef struct sComChn 
{
	byte chn;                   // communication channel used
} tComChn;

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the Serial screen (Goal)
// ======================================
static const ST_DSP_LINE txSerial[] =
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

// List of dialog choice
// =====================
static const char *tzComSerial[] =
{
	"RS232(COM0)",
	"RS232(COM1)",
	"RS232(COM2)",
	"USB->RS232(COM_EXT)",
	NULL
};

static const char *tzDataBits[] =
{
	"Seven",
	"Eight",
	NULL
};

static const char *tzParity[] =
{
	"None",
	"Even",
	"Odd",
	NULL
};

static const char *tzStopBits[] =
{
	"One",
	"Two",
	NULL
};

static const char *tzBaudRate[] =
{
	"300",
	"1200",
	"2400",
	"4800",
	"9600",
	"19200",
	"38400",
	"57600",
	"115200",
	NULL
};

static LL_HANDLE tvSession[4] = {NULL,NULL,NULL,NULL}; // Session handles

static tComChn xCom; // Communication channel

// Tlv tree nodes
// ==============
static TLV_TREE_NODE piConfig=NULL;
static TLV_TREE_NODE piPhysicalConfig=NULL;

// *****************************************************
// Functions to retrieve the handle of the configuration
// *****************************************************
static int GetHandleIndex(enum eChn eCommType)
{
    int i=-1;

    switch(eCommType)
    {
	case chnCom0:   i=0; break;
	case chnCom1:   i=1; break;
	case chnCom2:   i=2; break;
	case chnComExt: i=3; break;
	default:           break;
    }

    return i;
}

static LL_HANDLE* GetHandle(enum eChn eCommType)
{
	int i;

	i=GetHandleIndex(eCommType);
	CHECK(i>=0, lblKOHandleIndex);
	return(&tvSession[i]);

lblKOHandleIndex:
    return(NULL);
}

//****************************************************************************
//                 LL_HANDLE* OpenSerial (byte ucChn)                            
//  This function creates the handle of the serial port selected.      
//  This function has parameters.  
//    ucChn (I-) :  chnCom0, chnCom1, chnCom2, chnComExt
//  This function has return value
//    !NULL : Pointer to the handle of the serial port created
//    NULL : Processing failed                                        
//****************************************************************************

static LL_HANDLE* OpenSerial(byte ucChn)
{
	xCom.chn = ucChn;
    switch (xCom.chn)
	{
	case chnCom0:
	case chnCom1:
	case chnCom2:
	case chnComExt:
		return GetHandle((enum eChn) xCom.chn);
	default:
		break;
    }
    return NULL;
}

//****************************************************************************
//                   int SetSerial (const char *pcInit)                            
//  This function configures the serial port.     
//   - LL_Configure() : Create Link Layer configuration
//  This function has parameters.  
//    pcInit (I-) :  DPSB com channel(s) (ex: "8N12400")
//           D = Number of data bits (7,8)
//           P = Parity (None, Even, Odd)
//           S = Stop bits (1,2)
//           B = Baud Rate (300,1200,2400,4800,9600,19200,38400,57600,115200)
//  This function has return value
//    >=0 : Configuration done
//     <0 : Configuration failed                                        
//****************************************************************************

static int SetSerial(const char *pcInit) 
{
	// Local variables 
    // ***************
    byte ucDatasize;   
    byte ucParity;    
    byte ucStopbits;    
    doubleword uiBps;
	byte ucComNbr;
	LL_HANDLE *pvSession;
    int iRet;

	// Create the LinkLayer configuration parameters tree 
	// **************************************************
    pvSession = GetHandle((enum eChn) xCom.chn);                      // Handle of the configuration
	CHECK (*pvSession==NULL, lblKOConfigure);                         // Create a new config               
        
	ucDatasize = LL_PHYSICAL_V_8_BITS;                                // *** Number of data bits ***  
    switch (*pcInit++)    
    {
	case '7': ucDatasize = LL_PHYSICAL_V_7_BITS; break;               // 7 data bits 
	case '8': ucDatasize = LL_PHYSICAL_V_8_BITS; break;               // 8 data bits
	default: goto lblKOConfigure;                                     // Configuration error  
    }
    
	ucParity = LL_PHYSICAL_V_NO_PARITY;                               // *** Parity ***
    switch (*pcInit++)           
    {          
	case 'N': ucParity = LL_PHYSICAL_V_NO_PARITY;   break;            // No parity
	case 'E': ucParity = LL_PHYSICAL_V_EVEN_PARITY; break;            // Even parity
	case 'O': ucParity = LL_PHYSICAL_V_ODD_PARITY; break;             // Odd parity
	default: goto lblKOConfigure;                                     // Configuration error
    }

    ucStopbits = LL_PHYSICAL_V_1_STOP;                                // *** Number of stop bits ***
    switch (*pcInit++)          
    {         
    case '1': ucStopbits = LL_PHYSICAL_V_1_STOP; break;               // 1 stop bit
    case '2': ucStopbits = LL_PHYSICAL_V_2_STOP; break;               // 2 stop bits
    default: goto lblKOConfigure;                                     // Configuration error
    }

    if(*pcInit == 0) {                                                // *** Baud rate ***
        uiBps = LL_PHYSICAL_V_BAUDRATE_1200; pcInit++;                // 1200 bauds
	} else if(memcmp(pcInit, "300", 3) == 0) {   
		uiBps = LL_PHYSICAL_V_BAUDRATE_300; pcInit+=3;                // 300 bauds  
	} else if(memcmp(pcInit, "1200", 4) == 0) {   
		uiBps = LL_PHYSICAL_V_BAUDRATE_1200; pcInit+=4;               // 1200 bauds
	} else if(memcmp(pcInit, "2400",4) == 0) {   
		uiBps = LL_PHYSICAL_V_BAUDRATE_2400; pcInit+=4;               // 2400 bauds  
	} else if(memcmp(pcInit, "4800", 4) == 0) {   
		uiBps = LL_PHYSICAL_V_BAUDRATE_4800; pcInit+=4;               // 4800 bauds 
	} else if(memcmp(pcInit, "9600", 4) == 0) {   
		uiBps = LL_PHYSICAL_V_BAUDRATE_9600; pcInit+=4;               // 9600 bauds 
	} else if(memcmp(pcInit, "19200", 5) == 0) {   
		uiBps = LL_PHYSICAL_V_BAUDRATE_19200; pcInit+=5;              // 19200 bauds
	} else if(memcmp(pcInit, "38400", 5) == 0) {   
		uiBps = LL_PHYSICAL_V_BAUDRATE_38400; pcInit+=5;              // 38400 bauds
	} else if(memcmp(pcInit, "57600", 5) == 0) {   
		uiBps = LL_PHYSICAL_V_BAUDRATE_57600;  pcInit+=5;             // 57600 bauds
	} else if(memcmp(pcInit, "115200", 6) == 0) {   
		uiBps = LL_PHYSICAL_V_BAUDRATE_115200; pcInit+=6;             // 115200 bauds
	} else
		goto lblKOConfigure;                                          // Configuration error

    // Create parameters tree
    // ======================
	piConfig = TlvTree_New(LL_TAG_LINK_LAYER_CONFIG);                 // LinkLayer parameters Root tag of the configuration tree

	// Physical layer parameters  
	// =========================
	piPhysicalConfig = TlvTree_AddChild(piConfig,                        
		                                LL_TAG_PHYSICAL_LAYER_CONFIG, // TAG Physical layer parameters 
									    NULL,                         // VALUE (Null)
									    0);                           // LENGTH 0
    
 
    // Port Com(s)
	// -----------
    ucComNbr = (byte)(xCom.chn==chnCom0 ? LL_PHYSICAL_V_COM0 :    
	                  xCom.chn==chnCom1 ? LL_PHYSICAL_V_COM1 : 
					  xCom.chn==chnCom2 ? LL_PHYSICAL_V_COM2 :
	                  LL_PHYSICAL_V_CONVERTER_USB_RS232);
	TlvTree_AddChildInteger(piPhysicalConfig, 
		                    LL_PHYSICAL_T_LINK,                       // TAG
							ucComNbr,                                 // VALUE
							LL_PHYSICAL_L_LINK);                      // LENGTH 1 byte

	// Baud Rate
	// ---------
	TlvTree_AddChildInteger(piPhysicalConfig,
		                    LL_PHYSICAL_T_BAUDRATE,                   // TAG
	                        uiBps,                                    // VALUE (Integer)
                            LL_PHYSICAL_L_BAUDRATE);                  // LENGTH 4 bytes                                               

    // Data bits
	// ---------
	TlvTree_AddChildInteger(piPhysicalConfig, 
		                    LL_PHYSICAL_T_BITS_PER_BYTE,              // TAG
							ucDatasize,                               // VALUE
							LL_PHYSICAL_L_BITS_PER_BYTE);             // LENGTH 1 byte

    // Stop bits
	// ---------
	TlvTree_AddChildInteger(piPhysicalConfig, 
		                    LL_PHYSICAL_T_STOP_BITS,                  // TAG
							ucStopbits,                               // VALUE
							LL_PHYSICAL_L_STOP_BITS);                 // LENGTH 1 byte
    
    // Parity
	// ------
	TlvTree_AddChildInteger(piPhysicalConfig, 
		                    LL_PHYSICAL_T_PARITY,                     // TAG
							ucParity,                                 // VALUE
							LL_PHYSICAL_L_PARITY);                    // LENGTH 1 byte
	
	// Link Layer configuration
	// ************************
    iRet = LL_Configure(pvSession, piConfig);

	// Release the LinkLayer configuration parameters tree
	// ***************************************************
	TlvTree_Release(piConfig);
        
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKOConfigure:
    iRet=LL_ERROR_INVALID_PARAMETER;
lblEnd:
	return iRet;
}

//****************************************************************************
//                          int ConnectSerial (void)                            
//  This function connects the serial port.     
//   - LL_Connect() : Connect Link Layer
//  This function has no parameters.  
//  This function has return value
//    >=0 : Connect done
//     <0 : Connect failed                                        
//****************************************************************************

static int ConnectSerial(void)
{
	// Local variables 
    // ***************
    LL_HANDLE *pvSession = GetHandle((enum eChn) xCom.chn);
    int iRet;
       
    // Link Layer connection
	// *********************
    iRet = LL_Connect(*pvSession);
 
    return iRet;
}

//****************************************************************************
//             int SendSerial (const char *pcMsg, word usLen)
//  This function sends data through the serial port.      
//   - LL_Send() : Send data
//   - LL_GetLastError() : Retrieve the last error
//  This function has parameters.  
//    pcMsg (I-) : Data to send
//    usLen (I-) : Number of byte to send
//  This function has return value
//    >=0 : Number of bytes sent
//     <0 : Transmission failed                                       
//****************************************************************************

static int SendSerial(const char *pcMsg, word usLen)
{
	// Local variables 
    // ***************
    LL_HANDLE *pvSession = GetHandle((enum eChn) xCom.chn);
    int iRet;
    
	// Send data
	// *********
    iRet = LL_Send(*pvSession, usLen, pcMsg, LL_INFINITE);
    if(iRet != usLen)
		iRet = LL_GetLastError(*pvSession);

    return iRet;
}

//****************************************************************************
//        int ReceiveSerial (char *pcMsg, word usLen, byte ucDly)
//  This function receives data through the serial port.      
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

static int ReceiveSerial(char *pcMsg, word usLen, byte ucDly)
{
	// Local variables 
    // ***************
    LL_HANDLE *pvSession = GetHandle((enum eChn) xCom.chn);
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
	ResetPeripherals(KEYBOARD | TSCREEN);                                // Reset peripherals FIFO
    iRet = TimerStart(0, iSec);                                          // Timer0 starts
    CHECK(iRet>=0, lblTimeOut);
	do
    {
    	iNbrBytes = LL_Receive(*pvSession, usLen, pcMsg+iLength, 1*100); // Check reception
    	if (iNbrBytes != 0)
    		break;                                                       // Bytes received
		iKey = GoalGetKey(xScreen, xGoal, true, 0, false);               // Get key pressed/touched (shortcut)
		CHECK(iKey!=GL_KEY_CANCEL, lblTimeOut);                          // Exit on cancel key
		if (iSec != LL_INFINITE)
			iTimeOut = TimerGet(0);                                      // Retrieve timer value
    } while (iTimeOut>0);

    CHECK(iTimeOut!=0, lblTimeOut);                                      // Exit on timeout

	iLength += iNbrBytes;
	iRet = LL_GetLastError(*pvSession);
	CHECK (iRet==LL_ERROR_OK, lblEnd);
	if (iNbrBytes != 0)
	{
		// Receiving next block until timeout (Inter block 500ms)
		// ======================================================
		while(1)
		{
			iNbrBytes = LL_Receive(*pvSession, usLen-iLength, pcMsg+iLength, 50);
			iLength += iNbrBytes;
			iRet = LL_GetLastError(*pvSession);
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
//                     int DisconnectSerial (void)                            
//  This function disconnects the serial port.      
//   - LL_Disconnect() : Disconnect Link Layer
//  This function has no parameters.  
//  This function has return value
//    >=0 : Disconnect done
//     <0 : Disconnect failed                                       
//****************************************************************************

static int DisconnectSerial(void) 
{	
	// Local variables 
    // ***************
	LL_HANDLE *pvSession = GetHandle((enum eChn) xCom.chn);
	int iRet;

	// Link Layer disconnection
	// ************************
	iRet = LL_Disconnect(*pvSession);

	return iRet;
}

//****************************************************************************
//                     int CloseSerial (void)                            
//  This function deletes the handle of the serial port.   
//   - LL_Configure() : Delete Link Layer configuration
//  This function has no parameters.  
//  This function has return value
//    >=0 : Configuration deleted
//     <0 : Processing failed                                        
//****************************************************************************

static int CloseSerial(void)
{
	// Local variables 
    // ***************
    LL_HANDLE *pvSession = GetHandle((enum eChn) xCom.chn);
    int iRet;

	// Delete the configuration
	// ************************
    iRet = LL_Configure(pvSession, NULL);

    return iRet;
}

//****************************************************************************
//                      void PromptSerial (void)                            
//  This function asks for the Serial's parameters.   
//  This function has no parameters.  
//  This function has no return value
//****************************************************************************

void PromptSerial(void)
{
	// Local variables 
    // ***************
	char tcSerialItem[lenSerialItem];
	char tcSerialInit[lenSerialInit+1];
	char tcDisplay[50+1];
    int iDefItemP, iDefItemN, iRet;

    // Retrieve serial parameters
    // **************************
	iRet = appGet(appSerialItem, tcSerialItem, lenSerialItem);
	CHECK(iRet>=0, lblDbaErr);
	iRet = appGet(appSerialInit, tcSerialInit, lenSerialInit+1);
	CHECK(iRet>=0, lblDbaErr);

	// Select com serial
	// *****************
	iDefItemP = tcSerialItem[0];                                                    // Retrieve previous item selected
	iDefItemN = GL_Dialog_Choice(xGoal, "Com Port", tzComSerial, iDefItemP, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE);
	CHECK((iDefItemN!=GL_KEY_CANCEL) && (iDefItemN!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
    if (iDefItemN != iDefItemP)
    {
    	tcSerialItem[0] = iDefItemN;                                                // Save new item selected
    	iRet = appPut(appSerialItem, tcSerialItem, lenSerialItem);                  // Save serial parameters
    	CHECK(iRet>=0, lblDbaErr);
    }

    // Select data bits
    // ****************
	iDefItemP = tcSerialItem[1];                                                    // Retrieve previous item selected
	iDefItemN = GL_Dialog_Choice(xGoal, "Data Bits", tzDataBits, iDefItemP, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE);
	CHECK((iDefItemN!=GL_KEY_CANCEL) && (iDefItemN!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (iDefItemN != iDefItemP)
	{
		tcSerialInit[0] = *tzDataBits[iDefItemN];                                   // Save data bits
		tcSerialItem[1] = iDefItemN;                                                // Save new item selected
		iRet = appPut(appSerialItem, tcSerialItem, lenSerialItem);                  // Save serial parameters
		CHECK(iRet>=0, lblDbaErr);
		iRet = appPut(appSerialInit, tcSerialInit, lenSerialInit);
		CHECK(iRet>=0, lblDbaErr);
	}

    // Select parity
    // *************
	iDefItemP = tcSerialItem[2];                                                    // Retrieve previous item selected
	iDefItemN = GL_Dialog_Choice(xGoal, "Parity", tzParity, iDefItemP, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE);
	CHECK((iDefItemN!=GL_KEY_CANCEL) && (iDefItemN!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
    if (iDefItemN != iDefItemP)
    {
    	tcSerialInit[1] = *tzParity[iDefItemN];                                     // Save parity
    	tcSerialItem[2] = iDefItemN;                                                // Save new item selected
    	iRet = appPut(appSerialItem, tcSerialItem, lenSerialItem);                  // Save serial parameters
    	CHECK(iRet>=0, lblDbaErr);
    	iRet = appPut(appSerialInit, tcSerialInit, lenSerialInit);
    	CHECK(iRet>=0, lblDbaErr);
    }

    // Select stop bits
    // ****************
	iDefItemP = tcSerialItem[3];                                                    // Retrieve previous item selected
	iDefItemN = GL_Dialog_Choice(xGoal, "Stop Bits", tzStopBits, iDefItemP, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE);
	CHECK((iDefItemN!=GL_KEY_CANCEL) && (iDefItemN!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (iDefItemN != iDefItemP)
	{
		tcSerialInit[2] = *tzStopBits[iDefItemN];                                   // Save stop bits
		tcSerialItem[3] = iDefItemN;                                                // Save new item selected
		iRet = appPut(appSerialItem, tcSerialItem, lenSerialItem);                  // Save serial parameters
		CHECK(iRet>=0, lblDbaErr);
		iRet = appPut(appSerialInit, tcSerialInit, lenSerialInit);
		CHECK(iRet>=0, lblDbaErr);
	}

    // Select baud rate
    // ****************
	iDefItemP = tcSerialItem[4];                                                    // Retrieve previous item selected
	iDefItemN = GL_Dialog_Choice(xGoal, "Baud Rate", tzBaudRate, iDefItemP, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE);
	CHECK((iDefItemN!=GL_KEY_CANCEL) && (iDefItemN!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (iDefItemN != iDefItemP)
	{
		strcpy (&tcSerialInit[3], tzBaudRate[iDefItemN]);                           // Save baud rate
		tcSerialItem[4] = iDefItemN;                                                // Save new item selected
		iRet = appPut(appSerialItem, tcSerialItem, lenSerialItem);                  // Save serial parameters
		CHECK(iRet>=0, lblDbaErr);
		iRet = appPut(appSerialInit, tcSerialInit, lenSerialInit);
		CHECK(iRet>=0, lblDbaErr);
	}

	goto lblEnd;

	// Errors treatment 
	// ****************
lblDbaErr:                                                                          // Data base error
	sprintf(tcDisplay, "%s\n%s", FMG_ErrorMsg(iRet), "Software Reset Needed");
	GL_Dialog_Message(xGoal, NULL, tcDisplay, GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	return;
}

//****************************************************************************
//                        void ComSerial(void)                            
//  This function communicates through COM0 port at 8-N-1-115200(default).
//  This function has no parameters.
//  This function has no return value
//****************************************************************************

void ComSerial(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xLine;
    LL_HANDLE *pvCom=NULL;
    byte ucChannel;
    int iPhysical=0;
	char tcSerialItem[lenSerialItem];
	char tcSerialInit[lenSerialInit+1];
    char tcSnd[MAX_SND+1];
    char tcRsp[MAX_RSP+1];
    char tcDisplay[50+1];
    byte p; // Printer line index
	int iRet=0, iStatus=0;;

	// Transmission through serial port in progress
	// ********************************************
    memset(tcSnd, 0, sizeof(tcSnd));
	memset(tcRsp, 0, sizeof(tcRsp));

	xScreen = GoalCreateScreen(xGoal, txSerial, NUMBER_OF_LINES(txSerial), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                               // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);

    // Open COM port 
	// =============
	iRet = GoalDspLine(xScreen, 0, "1-comOpen...", &txSerial[0], 0, true);
	CHECK(iRet>=0, lblKO);
	iRet = appGet(appSerialItem, tcSerialItem, lenSerialItem); // Retrieve com serial parameters
	CHECK(iRet>=0, lblDbaErr);
	switch (tcSerialItem[0])
	{
	case 0:
		ucChannel=chnCom0;                                     // Rs232 Com0
		iPhysical=LL_PHYSICAL_V_COM0;
		break;
	case 1:
		ucChannel=chnCom1;                                     // Rs232 Com1
		iPhysical=LL_PHYSICAL_V_COM1;
		break;
	case 2:
		ucChannel=chnCom2;                                     // Rs232 Com2
		iPhysical=LL_PHYSICAL_V_COM2;
		break;
	case 3:
		ucChannel=chnComExt;                                   // Usb->Rs232 ComExt
		iPhysical=LL_PHYSICAL_V_CONVERTER_USB_RS232;
		break;
	default:
		ucChannel=0xFF;
		break;
	}
    pvCom = OpenSerial(ucChannel);                                       // ** Open **
    CHECK(pvCom!=NULL, lblKO);
    iRet = GoalDspLine(xScreen, 1, "1-comOpen OK", &txSerial[1], 0, true);
	CHECK(iRet>=0, lblKO);

	// Configure COM port
	// ==================
    iRet = GoalDspLine(xScreen, 2, "2-comSet...", &txSerial[2], 0, true);
	CHECK(iRet>=0, lblKO);
	iRet = appGet(appSerialInit, tcSerialInit, lenSerialInit+1);         // Retrieve init string
	CHECK(iRet>=0, lblDbaErr);
    iRet = GoalDspLine(xScreen, 3, tcSerialInit, &txSerial[3], 0, true); // Show init string
	CHECK(iRet>=0, lblKO);
    iRet = SetSerial(tcSerialInit);                                      // ** Set **
    CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 4, "2-comSet OK", &txSerial[4], 0, true);
	CHECK(iRet>=0, lblKO);

	// Connect COM port
	// ================
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);    // Clear screen
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 0, "3-comConnect...", &txSerial[0], 0, true);
	CHECK(iRet>=0, lblKO);
    iRet = ConnectSerial();                                              // ** Connect **
    CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 1, "3-comConnect OK", &txSerial[1], 0, true);
	CHECK(iRet>=0, lblKO);

	// Clear sending/receiving buffers
	// ===============================
	iRet = LL_ClearSendBuffer(*pvCom);
    CHECK(iRet==LL_ERROR_OK, lblComKO);
    iRet = LL_ClearReceiveBuffer(*pvCom);
    CHECK(iRet==LL_ERROR_OK, lblComKO);

    // Send data through COM port
	// ==========================
    iRet = GoalDspLine(xScreen, 2, "4-comSend...", &txSerial[2], 0, true);
	CHECK(iRet>=0, lblKO);
    strcpy(tcSnd, "Hello, do you hear me?\r\n"                           // Data to send
		          "Hello, do you hear me?\r\n"
			   	  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n"
				  "Hello, do you hear me?\r\n");
    iRet = SendSerial(tcSnd, (word) strlen(tcSnd));                      // ** Send data **
	CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 3, "4-comSend OK", &txSerial[3], 0, true);
	CHECK(iRet>=0, lblKO);

	// Receive data through COM port
	// =============================
    iRet = GoalDspLine(xScreen, 4, "5-comRec...", &txSerial[4], 0, true);
	CHECK(iRet>=0, lblKO);
    iRet = ReceiveSerial(tcRsp, sizeof(tcRsp), 30);                      // ** Receive data **
	CHECK(iRet>=0, lblComKO);
    if (iRet > MAX_RSP) strcpy (tcRsp, "Buffer overflow Max=512");       // Data overflow
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);    // Clear screen
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 0, "5-comRec OK", &txSerial[0], 0, true);
	CHECK(iRet>=0, lblKO);

	// Disconnection
	// =============
	iRet = DisconnectSerial();                                           // ** Disconnect **
	CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 1, "6-comDisconn OK", &txSerial[1], 0, true);
	CHECK(iRet>=0, lblKO);
	iRet = CloseSerial();                                                // ** Close **
	CHECK(iRet>=0, lblComKO);
	pvCom=NULL;

	// Display transmission data
	// =========================
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspMultiLine(xScreen, 0, tcRsp, strlen(tcRsp), txSerial, NUMBER_OF_LINES(txSerial), 0, true);
	CHECK(iRet>=0, lblKO);                                               // Show data to receive

	// Print transmission data
	// =======================
	p=0;
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);             // Create document
	CHECK(xDocument!=NULL, lblKO);

	xLine = xPrinter;                                                    // Build document (Demo, Tx/Rx data)
	xLine.eTextAlign = GL_ALIGN_CENTER;
	xLine.bReverse = TRUE;
	xLine.xMargin.usBottom = PIXEL_BOTTOM;
	xLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "RS232 Demo", &xLine);
	CHECK(iRet>=0, lblKO);

	xLine = xPrinter;
	iRet = GoalPrnLine(xDocument, p++, "Sending:", &xLine);              // Data to send
	CHECK(iRet>=0, lblKO);
    iRet = GoalPrnLine(xDocument, p++, tcSnd, &xLine);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "\nReceiving:", &xLine);          // Data to receive
	CHECK(iRet>=0, lblKO);
    iRet = GoalPrnLine(xDocument, p++, tcRsp, &xLine);
	CHECK(iRet>=0, lblKO);
	iRet = GoalPrnLine(xDocument, p++, "\n\n\n\n", &xLine);
	CHECK(iRet>=0, lblKO);

	iRet = GoalPrnDocument(xDocument);                                   // Print document
	CHECK(iRet>=0, lblKO);

	GoalGetKey(xScreen, xGoal, true, 30*1000, true);                     // Wait for key pressed/touched (shortcut)

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                           // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
    goto lblEnd;
lblComKO:                                        // Communication error
	strcpy(tcDisplay, LL_ErrorMsg(iRet));        // Link Layer error
	if (iRet == LL_Network_GetStatus(iPhysical, &iStatus))
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
		DisconnectSerial();                      // ** Disconnect **
		CloseSerial();                           // ** Close **
	}
	if (xScreen)
		GoalDestroyScreen(&xScreen);             // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);         // Destroy document
}
