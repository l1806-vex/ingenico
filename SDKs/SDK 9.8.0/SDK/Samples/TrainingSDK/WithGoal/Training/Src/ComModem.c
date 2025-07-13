//****************************************************************************
//       INGENICO                                INGEDEV 7                    
//============================================================================
//       FILE  COMMODEM.C                         (Copyright INGENICO 2012)
//============================================================================
//  Created :       11-July-2008     Kassovic
//  Last modified : 11-July-2008     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                   *** Modem communication management ***
//  How to use the linklayer to create a modem configuration to communicate.
//                   Transmission by Asynchronous Modem
//               Test done with Hyper-terminal (8-N-1-19200)
//  !!! Link Layer application must be loaded 3628xxxx.SGN inside the terminal
//      AVL.lib + LinkLayerExeInterface.lib must be implemented to link properly   
//                                                                            
//  List of routines in file :  
//      GetHandle : Handle of the configuration.
//      OpenModem : Create the modem port.
//      SetModem : Configure the modem port.
//      ConnectModem : Connect the modem port.
//      SendModem : Send data through the modem port.
//      ReceiveModem : Receive data through the modem port.
//      DisconnectModem : Disconnect the modem port.    
//      CloseModem : Delete the modem port.
//      PromptModem : Prompt for modem's parameters.
//      ComModem : Modem communication demo.
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

#define DIAL_TIMEOUT 30*100
#define HDLC_TIMEOUT 30*100

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
enum eChn {        // Com channels
    chnBeg,        // Start sentinel
    chnMdm,        // Internal Modem
    chnHdlc,       // Hdlc
    chnEnd         // End sentinel
};

enum comDialMode_t
{
   COM_DIAL_DEFAULT, // Mode dialing
   COM_DIAL_PULSE,   // Decimal
   COM_DIAL_TONE     // DTMF
};

typedef struct sComChn 
{
	byte chn;                   // communication channel used
	byte bits;                  // data bits
	byte parity;                // parity 
} tComChn;

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the Modem screen (Goal)
// =====================================
static const ST_DSP_LINE txModem[] =
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

static LL_HANDLE tvSession[2] = {NULL,NULL}; // Session handles

static tComChn xCom; // Communication channel

// Tlv tree nodes
// ==============
static TLV_TREE_NODE piConfig=NULL;
static TLV_TREE_NODE piPhysicalConfig=NULL;
static TLV_TREE_NODE piDataLinkConfig=NULL;

// *****************************************************
// Functions to retrieve the handle of the configuration
// *****************************************************
static int GetHandleIndex(enum eChn eCommType)
{   
    int i = -1;

    switch(eCommType)
    {   
	case chnMdm:  i=0; break;
	case chnHdlc: i=1; break;
	default:           break;
    }

    return i;
}

static LL_HANDLE* GetHandle(enum eChn eCommType)
{   
	int i; 
		
	i = GetHandleIndex(eCommType);
	CHECK(i>=0, lblKOHandleIndex);
	return(&tvSession[i]);

lblKOHandleIndex:
    return(NULL);
}

//****************************************************************************
//                   LL_HANDLE* OpenModem (byte ucChn)                            
//  This function creates the handle of the modem port.      
//  This function has parameters.  
//    ucChn (I-) :  chnMdm, chnHdlc 
//  This function has return value
//    !NULL : Pointer to the handle configuration
//    NULL : Processing failed                                        
//****************************************************************************

static LL_HANDLE* OpenModem(byte ucChn)
{
	xCom.chn = ucChn;
    switch (xCom.chn) 
	{
	case chnMdm:
	case chnHdlc:
		return GetHandle((enum eChn) xCom.chn);
	default:
		break;
    }
    return NULL;
}

//****************************************************************************
//                    int SetModem (const char *pcInit)                            
//  This function configures the modem port.  
//  For Synchronous pcInit is forced to "8N11200". 
//   - LL_Configure() : Create Link Layer configuration
//  This function has parameters.  
//    pcInit (I-) :  .?#MDPSB   (ex: ".?#T8N12400") => O=Optional M=Mandatory
//    O      . = Data compression
//    O      ? = Error correction
//    O      # = DTR management
//    O      M = T/P (Tone/Pulse fast connect)  t/p (tone/pulse NO fast connect)
//    M      D = Number of data bits (7,8)
//    M      P = Parity (None, Even, Odd)
//    M      S = Stop bits (1, 2=>is not supported)
//    M      B = Baud Rate (300,1200,2400,9600,19200)   
//  This function has return value
//    >=0 : Configuration done
//     <0 : Configuration failed                                        
//****************************************************************************

static int SetModem(const char *pcInit) 
{
	// Local variables 
    // ***************
    byte ucDatasize;                      // Implemented 
    byte ucParity;                        // Implemented 
    byte ucStopbits;                      // Implemented  
    enum comDialMode_t eDialmode;         // Implemented  
    int iBlindDial;                       // Implemented  
    byte ucFast;                          // Implemented  
    byte ucCompression;                   // Implemented                                  
    byte ucCorrection;                    // Implemented  
    byte ucHangUpDtr;                     // NOT IMPLEMENTED 
    doubleword uiBps, uiTimeout;
	char tcInitString[50];
	LL_HANDLE *pvSession;
    int iRet;

	// Create the LinkLayer configuration parameters tree 
	// **************************************************
    pvSession = GetHandle((enum eChn) xCom.chn);                      // Handle of the configuration
	CHECK (*pvSession==NULL, lblKOConfigure);                         // Create a new config               

    if(xCom.chn == chnHdlc)                                           // *** Hdlc parameters ***
        pcInit = "8N11200";                                           // 8Bits ParityNone 1Stop 1200 

    if(*pcInit == '.') {                                              // *** Compression field (optional) ***
		ucCompression=1; pcInit++;                                    // Compression 
    } else
        ucCompression=0;                                              // No compression

    if(*pcInit == '?') {                                              // *** Correction field (optional) ***
        ucCorrection=1; pcInit++;                                     // Correction
    } else
        ucCorrection=0;                                               // No correction
                  
    if(*pcInit == '#') {                                              // *** HangUp DTR (optional) ***
        ucHangUpDtr=1; pcInit++;                                      // DTR
    } else
        ucHangUpDtr=0;                                                // No DTR

    switch (*pcInit)                                                  // *** Fast dialing ***
	{
    case 'P': case 'T': ucFast=0; break;                              // Upper case means baud rate negotiation
	case 'p': case 't': ucFast=1; break;                              // Lower case means baud rate without negotiation
    default:            ucFast=0; break;
    }

    switch (*pcInit)                                                  // *** Dial mode (unused in Telium) ***                   
	{
	case 'T': case 't': eDialmode=COM_DIAL_TONE; pcInit++;  break;     // Dtmf
    case 'P': case 'p': eDialmode=COM_DIAL_PULSE; pcInit++; break;     // Decimal
    default:            eDialmode=COM_DIAL_DEFAULT;         break;     // Default
    }
            // !!! Data format is 8 bits no parity 1 stop (Other framing/parity must be handled at application level)
    ucDatasize=LL_PHYSICAL_V_8_BITS;                                  // *** Number of data bits ***
    switch (*pcInit++) 
	{     
    case '7': xCom.bits='7'; break;                                   // 7 data bits (Must be handled at application level)
    case '8': xCom.bits='8'; break;                                   // 8 data bits
    default:  goto lblKOConfigure;                                    // Configuration error
    }
    
    ucParity=LL_PHYSICAL_V_NO_PARITY;                                 // *** Parity ***
    switch (*pcInit++)              
	{        
    case 'N': xCom.parity=0;   break;                                 // No parity
    case 'E': xCom.parity='E'; break;                                 // Even parity (Must be handled at application level)
    case 'O': xCom.parity='O'; break;                                 // Odd parity (Must be handled at application level)
	default:  goto lblKOConfigure;                                    // Configuration error
    }
    
    ucStopbits=LL_PHYSICAL_V_1_STOP;                                  // *** Number of stop bits ***
    switch (*pcInit++) 
	{          
    case '1': ucStopbits=LL_PHYSICAL_V_1_STOP; break;                 // 1 stop bit
    case '2':                                                         // 2 stop bits (Not supported by Telium modem)
    default:  goto lblKOConfigure;                                    // Configuration error
    }
    
    uiBps=LL_PHYSICAL_V_BAUDRATE_1200;                                // *** Baud rate ***
    if(memcmp(pcInit, "300", 3) == 0) {                               // 300 bauds
		uiBps = (ucFast ? LL_PHYSICAL_V_BAUDRATE_1200 : LL_PHYSICAL_V_BAUDRATE_300); pcInit += 3; 
	} else if(memcmp(pcInit, "1200", 4) == 0) {                       // 1200 bauds  
		uiBps = (ucFast ? LL_PHYSICAL_V_BAUDRATE_1200 : LL_PHYSICAL_V_BAUDRATE_1200); pcInit += 4;
    } else if(memcmp(pcInit, "2400", 4) == 0) {                       // 2400 bauds  
        uiBps =  (ucFast ? LL_PHYSICAL_V_BAUDRATE_1200 : LL_PHYSICAL_V_BAUDRATE_2400); pcInit += 4;
    } else if(memcmp(pcInit, "4800", 4) == 0) {                       // 2400 bauds  
        uiBps =  (ucFast ? LL_PHYSICAL_V_BAUDRATE_1200 : LL_PHYSICAL_V_BAUDRATE_4800); pcInit += 4;  
    } else if(memcmp(pcInit, "9600", 4) == 0) {                       // 9600 bauds 
        uiBps = (ucFast ? LL_PHYSICAL_V_BAUDRATE_1200 : LL_PHYSICAL_V_BAUDRATE_9600); pcInit += 4;
    } else if(memcmp(pcInit, "19200", 5) == 0) {                      // 19200 bauds
        uiBps = (ucFast ? LL_PHYSICAL_V_BAUDRATE_1200 : LL_PHYSICAL_V_BAUDRATE_19200); pcInit += 5;
    } else if(memcmp(pcInit, "38400", 5) == 0) {                      // 38400 bauds
        uiBps = (ucFast ? LL_PHYSICAL_V_BAUDRATE_1200 : LL_PHYSICAL_V_BAUDRATE_38400); pcInit += 5;
    } else if(memcmp(pcInit, "57600", 5) == 0) {                      // 57600 bauds
        uiBps = (ucFast ? LL_PHYSICAL_V_BAUDRATE_1200 : LL_PHYSICAL_V_BAUDRATE_57600); pcInit += 5;
    } else if(memcmp(pcInit, "115200", 6) == 0) {                     // 115200 bauds
        uiBps = (ucFast ? LL_PHYSICAL_V_BAUDRATE_1200 : LL_PHYSICAL_V_BAUDRATE_115200); pcInit += 6;
    } else
		goto lblKOConfigure;                                          // Configuration error

    iBlindDial = (*pcInit == 'D' ? 0: 1);                             // *** Blind dialing ***
         
    uiTimeout = DIAL_TIMEOUT;                                         // *** Dial timeout ***
 
    // Create parameters tree
    // ======================
	piConfig = TlvTree_New(LL_TAG_LINK_LAYER_CONFIG);                 // LinkLayer parameters Root tag of the configuration tree
    
    // Physical layer parameters  
	// =========================
	piPhysicalConfig = TlvTree_AddChild(piConfig,                        
		                                LL_TAG_PHYSICAL_LAYER_CONFIG, // TAG Physical layer parameters 
									    NULL,                         // VALUE (Null)
									    0);                           // LENGTH 0

    // Modem
	// -----
	TlvTree_AddChildInteger(piPhysicalConfig, 
		                    LL_PHYSICAL_T_LINK,                       // TAG
							LL_PHYSICAL_V_MODEM,                      // VALUE
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

    // Modem type
    // ----------
	TlvTree_AddChildInteger(piPhysicalConfig, 
		                    LL_MODEM_T_TYPE,                          // TAG
							LL_MODEM_V_TYPE_STANDARD,                 // VALUE
							LL_MODEM_L_TYPE);                         // LENGTH 1 byte
	
    // Dial Timeout
	// ------------
	TlvTree_AddChildInteger(piPhysicalConfig,
		                    LL_MODEM_T_DIAL_TIMEOUT,                  // TAG
	                        uiTimeout,                                // VALUE (Integer)
                            LL_MODEM_L_DIAL_TIMEOUT);                 // LENGTH 4 bytes                                               

    // Command Line Terminator
	// -----------------------
    if (xCom.chn == chnMdm) {    	
	    TlvTree_AddChildInteger(piPhysicalConfig, 
		                    LL_MODEM_T_CMD_TERMINATOR,                // TAG
							LL_MODEM_V_CMD_TERMINATOR_CR,             // VALUE
							LL_MODEM_L_CMD_TERMINATOR);               // LENGTH 1 byte
    }

    // Modem initialisation string
	// ---------------------------
    if(xCom.chn == chnHdlc) {                                         // Hdlc string
		sprintf(tcInitString, "ATE0%sS6=1$M249$M251F4S144=16", iBlindDial ? "X1":"X4");
    } else                                                            // Modem string 
        sprintf(tcInitString, "ATZE0\\N%c%%C%c%s", ucCorrection ? '3':'0', ucCompression ? '1':'0', iBlindDial ? "X1":"X4");
    TlvTree_AddChildString(piPhysicalConfig,
		                   LL_MODEM_T_INIT_STRING,                    // TAG
						   tcInitString);                             // VALUE
	                                                                  // LENGTH (strlen initString)
                         
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
//                   int ConnectModem (const char *pcPhone)                            
//  This function dials a phone number through the modem port.    
//   - LL_Configure() : Finish Link Layer configuration
//   - LL_Connect() : Connect Link Layer
//  This function has parameters.  
//    pcPhone (I-)    ex: "0-00-33-169012345"
//           Pabx                  0
//           Prefix                00   
//           Country code          33  
//           Phone Number          169012345
//  This function has return value
//    >=0 : Connect done
//     <0 : Connect failed                                        
//****************************************************************************

static int ConnectModem(const char *pcPhone) 
{
	// Local variables 
    // ***************
    char *pcPabx, *pcPrefix, *pcCountry;
    char tcTmp[64+1];
    char tcBuf[64+1];
	doubleword uiTimeout=0;
    LL_HANDLE *pvSession = GetHandle((enum eChn) xCom.chn);
    int iRet, iLen;

	// Parsing Phone
	// *************
    iRet=0;
    iLen=0;
    strcpy(tcTmp, pcPhone);
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

    // LinkLayer configuration parameters tree
	// ***************************************

    // Physical layer parameters
	// =========================
    memset(tcBuf, 0, sizeof(tcBuf));
    strcpy(tcBuf, pcPabx);
    strcat(tcBuf, pcPrefix);
    if(*pcCountry) {
        strcat(tcBuf, ",");
        strcat(tcBuf, pcCountry);
        strcat(tcBuf, ",");
    }
    strcat(tcBuf, pcPhone);

	// Phone number
	// ------------
    TlvTree_AddChildString(piPhysicalConfig,
		                   LL_MODEM_T_PHONE_NUMBER,                        // TAG
						   tcBuf);                                         // VALUE
	                                                                       // LENGTH (strlen buf)
    
    if(xCom.chn == chnHdlc) {   

		// Data link layer parameters
		// ==========================
		piDataLinkConfig = TlvTree_AddChild(piConfig,                        
		                                    LL_TAG_DATA_LINK_LAYER_CONFIG, // TAG Data link layer parameters 
									        NULL,                          // VALUE (Null)
									        0);                            // LENGTH 0
        

		// HDLC
		// ----
	    TlvTree_AddChildInteger(piDataLinkConfig, 
		                        LL_DATA_LINK_T_PROTOCOL,                   // TAG
			    				LL_DATA_LINK_V_HDLC,                       // VALUE
				    			LL_DATA_LINK_L_PROTOCOL);                  // LENGTH 1 byte


		// Connection timeout
		// ------------------
		uiTimeout = HDLC_TIMEOUT;
        TlvTree_AddChildInteger(piDataLinkConfig,         
                                LL_HDLC_T_CONNECT_TIMEOUT,                 // TAG
	                            uiTimeout,                                 // Value (Integer)
                                LL_HDLC_L_CONNECT_TIMEOUT);                // LENGTH 4 bytes
		
   
        // Minimum tries for sending
		// -------------------------
	    TlvTree_AddChildInteger(piDataLinkConfig, 
		                        LL_HDLC_T_MIN_RESEND_REQUESTS,             // TAG
			    				2,                                         // VALUE
				    			LL_HDLC_L_MIN_RESEND_REQUESTS);            // LENGTH 1 byte

        // V80 mode
		// --------
	    TlvTree_AddChildInteger(piDataLinkConfig, 
		                        LL_HDLC_T_V80_MODE,                        // TAG
			    				1,                                         // VALUE (Enable)
				    			LL_HDLC_L_V80_MODE);                       // LENGTH 1 byte
    }
    
	// Link Layer configuration
	// ************************
    iRet = LL_Configure(pvSession, piConfig);
	CHECK (iRet==LL_ERROR_OK, lblKOConfigure); 

	// Release the LinkLayer configuration parameters tree
	// ***************************************************
	TlvTree_Release(piConfig);

	// Link Layer connection
	// *********************
    iRet = LL_Connect(*pvSession);
	CHECK (iRet==LL_ERROR_OK, lblEnd);
    
	ttestall(0, 8*100);                                                    // Wait 8s to show that HyperTerminal is really connected
                                                                           // This line must be removed if you don't use HyperTerminal
    goto lblEnd;

	// Errors treatment 
    // ****************
lblKOConfigure:
	TlvTree_Release(piConfig);
lblEnd:
	return(iRet);
}

//****************************************************************************
//              int SendModem (char *pcMsg, word usLen)
//  This function sends data through the modem port.      
//   - LL_Send() : Send data
//   - LL_GetLastError() : Retrieve the last error
//  This function has parameters.  
//    pcMsg (I-) : Data to send 
//    usLen (I-) : Number of byte to send
//  This function has return value
//    >=0 : Number of bytes sent
//     <0 : Transmission failed                                       
//****************************************************************************

static int SendModem(char *pcMsg, word usLen)
{
	// Local variables 
    // ***************
    LL_HANDLE *pvSession = GetHandle((enum eChn) xCom.chn);
    word usIdx;
    int iRet;

    // Set parity (7bits Even/Odd only)
    // ********************************
    if (xCom.parity) 
    	SetParity(pcMsg, usLen, 1, xCom.parity);

	// Send data
	// *********
    iRet = LL_Send(*pvSession, usLen, pcMsg, LL_INFINITE);
    if (xCom.parity) 
    	for (usIdx=0; usIdx<usLen; usIdx++)
    		*(pcMsg+usIdx) = *(pcMsg+usIdx) & 0x7F;
    if(iRet != usLen)
		iRet = LL_GetLastError(*pvSession);
	    
    return iRet;
}

//****************************************************************************
//           int ReceiveModem (char *pcMsg, word usLen, byte ucDly)
//  This function receives data through the modem port.      
//   - LL_ClearReceiveBuffer() : Clear receiving buffer
//   - LL_Receive() : Wait and receive data
//   - LL_GetLastError() : Retrieve the last error
//  This function has parameters.  
//    pcMsg (-O) : Data to receive 
//    usLen (I-) : Maximum number of bytes to receive
//    ucDly (I-) : Timeout reception (in second, 0xFF infinite)
//  This function has return value
//    >=0 : Number of bytes received
//     <0 : Reception failed                                       
//****************************************************************************

static int ReceiveModem(char *pcMsg, word usLen, byte ucDly)
{
	// Local variables 
    // ***************
    LL_HANDLE *pvSession = GetHandle((enum eChn) xCom.chn);
    int iKey;
    int iRet, iLength=0, iTimeOut=LL_INFINITE, iSec, iNbrBytes, iIdx;

	// Timeout setting
	// ***************
    if(ucDly != 0xFF)  
        iSec = ucDly * 100;
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
		iKey = GoalGetKey(xScreen, xGoal, true, 0, false);               // Get key pressed/touched
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

	// Check parity (7bits Even/Odd only)
	// **********************************
	if (xCom.parity)
    {
    	for (iIdx=0; iIdx<iLength; iIdx++)
    	{
    		iRet = (int) CheckParity(pcMsg+iIdx, 1, 1, xCom.parity);
    		CHECK(iRet==1, lblParityKO);
    		*(pcMsg+iIdx) = *(pcMsg+iIdx) & 0x7F;
    	}
    }

	iRet = iLength;
    goto lblEnd;

	// Errors treatment 
    // ****************	
lblParityKO:
    iRet=LL_ERROR_PHYSICAL_PARITY;
    goto lblEnd;
lblTimeOut:
	iRet=LL_ERROR_TIMEOUT;
lblEnd:
	TimerStop(0);
	return iRet;
}

//****************************************************************************
//                      int DisconnectModem (void)                            
//  This function disconnects the modem port.      
//   - LL_Disconnect() : Disconnect Link Layer
//  This function has no parameters.  
//  This function has return value
//    >=0 : Disconnect done
//     <0 : Disconnect failed                                       
//****************************************************************************

static int DisconnectModem(void)
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
//                       int CloseModem (void)                            
//  This function deletes the handle of the modem port.   
//   - LL_Configure() : Delete Link Layer configuration
//  This function has no parameters.  
//  This function has return value
//    >=0 : Configuration deleted
//     <0 : Processing failed                                        
//****************************************************************************

int CloseModem(void)
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
//                      void PromptModem (void)                            
//  This function asks for the modem's parameters.   
//  This function has no parameters.  
//  This function has no return value
//****************************************************************************

void PromptModem(void)
{
	// Local variables 
    // ***************
	char tcMask[256];
	char tcModemItem[lenModemItem];
	char tcModemInit[lenModemInit+1];
	char tcPabxN[lenModemPabx+1], tcPabxP[lenModemPabx+1];
	char tcPrefixN[lenModemPrefix+1], tcPrefixP[lenModemPrefix+1];
	char tcCountryN[lenModemCountry+1], tcCountryP[lenModemCountry+1];
	char tcPhoneN[lenModemPhone+1], tcPhoneP[lenModemPhone+1];
	char tcDisplay[50+1];
    int i, iDefItemP, iDefItemN, iRet;
    
    // Retrieve modem parameters
    // *************************
	iRet = appGet(appModemItem, tcModemItem, lenModemItem);
	CHECK(iRet>=0, lblDbaErr);
	iRet = appGet(appModemInit, tcModemInit, lenModemInit+1);
	CHECK(iRet>=0, lblDbaErr);

    // Select dial mode (Tone by default)
    // **********************************
    tcModemInit[0]='T'; 
    
    // Select stop bits (1 only supported)
    // ***********************************
    tcModemInit[3]='1';    
        
    // Select data bits
    // ****************
	iDefItemP = tcModemItem[0];                                                     // Retrieve previous item selected
	iDefItemN = GL_Dialog_Choice(xGoal, "Data Bits", tzDataBits, iDefItemP, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE);
	CHECK((iDefItemN!=GL_KEY_CANCEL) && (iDefItemN!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (iDefItemN != iDefItemP)
	{
		tcModemInit[1] = *tzDataBits[iDefItemN];                                    // Save data bits
		tcModemItem[0] = iDefItemN;                                                 // Save new item selected
		iRet = appPut(appModemItem, tcModemItem, lenModemItem);                     // Save modem parameters
		CHECK(iRet>=0, lblDbaErr);
		iRet = appPut(appModemInit, tcModemInit, lenModemInit);
		CHECK(iRet>=0, lblDbaErr);
	}

    // Select parity
    // *************
	iDefItemP = tcModemItem[1];                                                     // Retrieve previous item selected
	iDefItemN = GL_Dialog_Choice(xGoal, "Parity", tzParity, iDefItemP, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE);
	CHECK((iDefItemN!=GL_KEY_CANCEL) && (iDefItemN!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (iDefItemN != iDefItemP)
	{
		tcModemInit[2] = *tzParity[iDefItemN];                                      // Save parity
		tcModemItem[1] = iDefItemN;                                                 // Save new item selected
		iRet = appPut(appModemItem, tcModemItem, lenModemItem);                     // Save modem parameters
		CHECK(iRet>=0, lblDbaErr);
		iRet = appPut(appModemInit, tcModemInit, lenModemInit);
		CHECK(iRet>=0, lblDbaErr);
	}

    // Select baud rate
    // ****************
	iDefItemP = tcModemItem[2];                                                     // Retrieve previous item selected
	iDefItemN = GL_Dialog_Choice(xGoal, "Baud Rate", tzBaudRate, iDefItemP, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_MINUTE);
	CHECK((iDefItemN!=GL_KEY_CANCEL) && (iDefItemN!=GL_RESULT_INACTIVITY), lblEnd); // Exit on cancel/timeout
	if (iDefItemN != iDefItemP)
	{
		strcpy (&tcModemInit[4], tzBaudRate[iDefItemN]);                            // Save baud rate
		tcModemItem[2] = iDefItemN;                                                 // Save new item selected
		iRet = appPut(appModemItem, tcModemItem, lenModemItem);                     // Save modem parameters
		CHECK(iRet>=0, lblDbaErr);
		iRet = appPut(appModemItem, tcModemInit, lenModemInit);
		CHECK(iRet>=0, lblDbaErr);
	}

    // Enter pabx
    // **********
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenModemPabx; i++)
		strcat(tcMask, "/d");                                                       // Accept only decimal character
	iRet = appGet(appModemPabx, tcPabxP, lenModemPabx+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcPabxN, tcPabxP);
	iRet = GL_Dialog_Text(xGoal, "Pabx", "Enter Pabx :", tcMask, tcPabxN, sizeof(tcPabxN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd);           // Exit on cancel/timeout
	if (strcmp(tcPabxN, tcPabxP) != 0)
	{
		iRet = appPut(appModemPabx, tcPabxN, lenModemPabx);                         // Save new pabx
		CHECK(iRet>=0, lblDbaErr);
	}

	// Enter prefix
	// ************
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenModemPrefix; i++)
		strcat(tcMask, "/d");                                                       // Accept only decimal character
	iRet = appGet(appModemPrefix, tcPrefixP, lenModemPrefix+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcPrefixN, tcPrefixP);
	iRet = GL_Dialog_Text(xGoal, "Prefix", "Enter Prefix :", tcMask, tcPrefixN, sizeof(tcPrefixN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd);           // Exit on cancel/timeout
	if (strcmp(tcPrefixN, tcPrefixP) != 0)
	{
		iRet = appPut(appModemPrefix, tcPrefixN, lenModemPrefix);                   // Save new prefix
		CHECK(iRet>=0, lblDbaErr);
	}
		
	// Enter country code
	// ******************
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenModemCountry; i++)
		strcat(tcMask, "/d");                                                       // Accept only decimal character
	iRet = appGet(appModemCountry, tcCountryP, lenModemCountry+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcCountryN, tcCountryP);
	iRet = GL_Dialog_Text(xGoal, "Country Code", "Enter Country Code :", tcMask, tcCountryN, sizeof(tcCountryN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd);           // Exit on cancel/timeout
	if (strcmp(tcCountryN, tcCountryP) != 0)
	{
		iRet = appPut(appModemCountry, tcCountryN, lenModemCountry);                // Save new country code
		CHECK(iRet>=0, lblDbaErr);
	}
		
	// Enter phone number
	// ******************
	memset(tcMask, 0, sizeof(tcMask));
	for (i=0; i<lenModemPhone; i++)
		strcat(tcMask, "/d");                                                       // Accept only decimal character
	iRet = appGet(appModemPhone, tcPhoneP, lenModemPhone+1);
	CHECK(iRet>=0, lblDbaErr);
	strcpy(tcPhoneN, tcPhoneP);
	iRet = GL_Dialog_Text(xGoal, "Phone Number", "Enter Phone# :", tcMask, tcPhoneN, sizeof(tcPhoneN), GL_TIME_MINUTE);
	CHECK((iRet!=GL_KEY_CANCEL) && (iRet!=GL_RESULT_INACTIVITY), lblEnd);           // Exit on cancel/timeout
	if (strcmp(tcPhoneN, tcPhoneP) != 0)
	{
		iRet = appPut(appModemPhone, tcPhoneN, lenModemPhone);                      // Save new phone number
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
//                       void ComModem (void)                            
//  This function communicates through the modem (Async) at 8-N-1-19200.   
//             Test done with Hyper-terminal.   
//  This function has no parameters.  
//  This function has no return value
//****************************************************************************

void ComModem(void) 
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xDocument=NULL;
	ST_PRN_LINE xLine;
    LL_HANDLE *pvCom=NULL;
	char tcModemInit[lenModemInit+1];
	char *pcStr, tcStr[128+1];
    char tcSnd[MAX_SND+1];
    char tcRsp[MAX_RSP+1];
    char tcDisplay[50+1];
    byte p; // Printer line index
	int iRet=0, iStatus=0;

	// Transmission through internal Modem in progress
	// ***********************************************
    memset(tcSnd, 0, sizeof(tcSnd));
	memset(tcRsp, 0, sizeof(tcRsp));

	xScreen = GoalCreateScreen(xGoal, txModem, NUMBER_OF_LINES(txModem), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                                          // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);
	CHECK(iRet>=0, lblKO);

	// Open modem 
	// ==========
	iRet = GoalDspLine(xScreen, 0, "1-comOpen...", &txModem[0], 0, true);
	CHECK(iRet>=0, lblKO);
    pvCom = OpenModem(chnMdm);                                            // ** Open **
    CHECK(pvCom!=NULL, lblKO);
    iRet = GoalDspLine(xScreen, 1, "1-comOpen OK", &txModem[1], 0, true);
	CHECK(iRet>=0, lblKO);

	// Configure modem
	// ===============
    iRet = GoalDspLine(xScreen, 2, "2-comSet...", &txModem[2], 0, true);
	CHECK(iRet>=0, lblKO);
	iRet = appGet(appModemInit, tcModemInit, lenModemInit+1);             // Retrieve init string
	CHECK(iRet>=0, lblDbaErr);
    iRet = GoalDspLine(xScreen, 3, tcModemInit, &txModem[3], 0, true);    // Show init string
	CHECK(iRet>=0, lblKO);
    iRet = SetModem(tcModemInit);                                         // ** Set **
    CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 4, "2-comSet OK", &txModem[4], 0, true);
	CHECK(iRet>=0, lblKO);

    // Dialing
	// =======
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);     // Clear screen
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 0, "3-comDial...", &txModem[0], 0, true);
	CHECK(iRet>=0, lblKO);
	pcStr = tcStr;                                                        // Build dial string
	iRet = appGet(appModemPabx, pcStr, lenModemPabx+1);                   // Retrieve pabx
	CHECK(iRet>=0, lblDbaErr);
	if (strlen(pcStr) != 0)
	{
		pcStr+=strlen(pcStr);
		*pcStr='-'; pcStr++;
	}
	iRet = appGet(appModemPrefix, pcStr, lenModemPrefix+1);               // Retrieve prefix
	CHECK(iRet>=0, lblDbaErr);
	if (strlen(pcStr) != 0)
	{
		pcStr+=strlen(pcStr);
		*pcStr='-'; pcStr++;
	}
	iRet = appGet(appModemCountry, pcStr, lenModemCountry+1);             // Retrieve country number
	CHECK(iRet>=0, lblDbaErr);
	if (strlen(pcStr) != 0)
	{
		pcStr+=strlen(pcStr);
		*pcStr='-'; pcStr++;
	}
	iRet = appGet(appModemPhone, pcStr, lenModemPhone+1);                 // Retrieve phone number
	CHECK(iRet>=0, lblDbaErr);
    iRet = GoalDspLine(xScreen, 1, tcStr, &txModem[1], 0, true);          // Show dial string
 	CHECK(iRet>=0, lblKO);
    iRet = ConnectModem(tcStr);                                           // ** Connect **
    CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 2, "3-comDial OK", &txModem[2], 0, true);
 	CHECK(iRet>=0, lblKO);

	// Clear sending/receiving buffers
	// ===============================
	iRet = LL_ClearSendBuffer(*pvCom);
    CHECK(iRet==LL_ERROR_OK, lblComKO);
    iRet = LL_ClearReceiveBuffer(*pvCom);
    CHECK(iRet==LL_ERROR_OK, lblComKO);

    // Send data through modem
	// =======================
    iRet = GoalDspLine(xScreen, 3, "4-comSend...", &txModem[3], 0, true);
	CHECK(iRet>=0, lblKO);
    strcpy(tcSnd, "Hello, do you hear me?\n"                              // Data to send
		          "Hello, do you hear me?\n"
		    	  "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n");
	iRet = SendModem(tcSnd, (word) strlen(tcSnd));                        // ** Send data **
	CHECK(iRet>=0, lblComKO);
	iRet = GoalDspLine(xScreen, 4, "4-comSend OK", &txModem[4], 0, true);
	CHECK(iRet>=0, lblKO);
    
	// Receive data through modem
	// ==========================
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL, false);     // Clear screen
	CHECK(iRet>=0, lblKO);
    iRet = GoalDspLine(xScreen, 0, "5-comRec...", &txModem[0], 0, true);
	CHECK(iRet>=0, lblKO);
    iRet = ReceiveModem(tcRsp, sizeof(tcRsp), 30);                        // ** Receive data **
	CHECK(iRet>=0, lblComKO);
    if (iRet > MAX_RSP) strcpy (tcRsp, "Buffer overflow Max=512");        // Data overflow
    iRet = GoalDspLine(xScreen, 1, "5-comRec OK", &txModem[1], 0, true);
	CHECK(iRet>=0, lblKO);

	// Disconnection
	// =============
    iRet = DisconnectModem();                                             // ** Disconnect **
	CHECK(iRet>=0, lblComKO);
    iRet = GoalDspLine(xScreen, 2, "6-comDisconn OK", &txModem[2], 0, true);
	CHECK(iRet>=0, lblKO);
    iRet = CloseModem();                                                  // ** Close **
	CHECK(iRet>=0, lblComKO);
	pvCom=NULL;

	// Display transmission data
	// =========================
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false); // Clear screen
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspMultiLine(xScreen, 0, tcRsp, strlen(tcRsp), txModem, NUMBER_OF_LINES(txModem), 0, true);
	CHECK(iRet>=0, lblKO);                                                // Show data to receive

	// Print transmission data
	// =======================
	p=0;
	xDocument = GoalCreateDocument(xGoal, GL_ENCODING_UTF8);              // Create document
	CHECK(xDocument!=NULL, lblKO);

	xLine = xPrinter;                                                     // Build document (Demo, Tx/Rx data)
	xLine.eTextAlign = GL_ALIGN_CENTER;
	xLine.bReverse = TRUE;
	xLine.xMargin.usBottom = PIXEL_BOTTOM;
	xLine.xFont.eScale = GL_SCALE_XXLARGE;
	iRet = GoalPrnLine(xDocument, p++, "Modem Demo", &xLine);
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
    	DisconnectModem();                       // ** Disconnect **
    	CloseModem();                            // ** Close **
	}
	if (xScreen)
		GoalDestroyScreen(&xScreen);             // Destroy screen
    if (xDocument)
    	GoalDestroyDocument(&xDocument);         // Destroy document
}
