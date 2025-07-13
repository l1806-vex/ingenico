//****************************************************************************
//       INGENICO                                INGEDEV 7                    
//============================================================================
//       FILE  COMMODEM.C                        (Copyright INGENICO 2008)   
//============================================================================
//  Created :       12-May-2008     Kassovic                                 
//  Last modified : 12-May-2008     Kassovic                                
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Modem communication management:
//             Transmission by Asynchronous Modem
//             Test done with Hyper-terminal (8-N-1-19200)
//  !!! Link Layer application must be loaded 34290302.SGN inside the terminal
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

#define DIAL_TIMEOUT 30*100
#define HDLC_TIMEOUT 30*100

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
enum eChn {                     ///<Com channels
    chnBeg,                     ///<start sentinel
    chnMdm,                     ///<Internal Modem
    chnHdlc,                    ///<Hdlc
    chnEnd                      ///<end sentinel
};

enum comDialMode_t
{
   COM_DIAL_DEFAULT,            ///<Mode dialing
   COM_DIAL_PULSE,              ///<Decimal
   COM_DIAL_TONE                ///<DTMF
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
static const char *tzDataBits[] = { "7", "8" };
static const char *tzParity[] = { "NONE", "EVEN", "ODD" };
static const char *tzBaudRate[] = { "300", "1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200" };

static LL_HANDLE tvSession[2] = {NULL,NULL};

static tComChn xCom;

static TLV_TREE_NODE piConfig=NULL;
static TLV_TREE_NODE piPhysicalConfig=NULL;
static TLV_TREE_NODE piDataLinkConfig=NULL;

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
		
	i = GetHandleIndex(eCommType); CHECK(i>=0, lblKOHandleIndex);
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
//       LL_Configure() : Create Link Layer configuration
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
//       LL_Configure() : Finish Link Layer configuration
//       LL_Connect() : Connect Link Layer
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
    
	ttestall(0, 4*100);                                                    // Wait 8s to show that HyperTerminal is really connected
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
//       LL_Send() : Send data
//       LL_GetLastError() : Retrieve the last error
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
//       LL_ClearReceiveBuffer() : Clear receiving buffer
//       LL_Receive() : Wait and receive data
//       LL_GetLastError() : Retrieve the last error
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
	char cKey;
    int iRet, iLength=0, iTimeOut=LL_INFINITE, iSec, iNbrBytes, iIdx;

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
    	iNbrBytes = LL_Receive(*pvSession, usLen, pcMsg+iLength, 1*100);  // Check reception
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
    return iRet;
}

//****************************************************************************
//                      int DisconnectModem (void)                            
//  This function disconnects the modem port.      
//       LL_Disconnect() : Disconnect Link Layer
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
//       LL_Configure() : Delete Link Layer configuration   
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
	char tcModemItem[lenModemItem];
	char tcModemInit[lenModemInit+1];
	char tcPabx[lenModemPabx+1];
	char tcPrefix[lenModemPrefix+1];
	char tcCountry[lenModemCountry+1];
	char tcPhone[lenModemPhone+1];
    int iDefItemP, iDefItemN, iRet;
    
    // Retrieve modem parameters
    // *************************
	iRet = appGet(appModemItem, tcModemItem, lenModemItem); CHECK(iRet>=0, lblDbaErr);
	iRet = appGet(appModemInit, tcModemInit, lenModemInit+1); CHECK(iRet>=0, lblDbaErr);

    // Select dial mode (Tone by default)
    // **********************************
    tcModemInit[0]='T'; 
    
    // Select stop bits (1 only supported)
    // ***********************************
    tcModemInit[3]='1';    
        
    // Select data bits
    // ****************
	iDefItemP = tcModemItem[0];                                                          // Retrieve previous item selected
	iDefItemN = ShowMenu("DATA  BITS", 2, iDefItemP, NUMBER_OF_ITEMS(tzDataBits), tzDataBits);
	CHECK(iDefItemN>=0, lblEnd);                                                         // Cancel, Timeout
	if (iDefItemN != iDefItemP)
	{
		tcModemInit[1] = *tzDataBits[iDefItemN];                                         // Save data bits
		tcModemItem[0] = iDefItemN;                                                      // Save new item selected
		iRet = appPut(appModemItem, tcModemItem, lenModemItem); CHECK(iRet>=0, lblDbaErr); // Save modem parameters
		iRet = appPut(appModemInit, tcModemInit, lenModemInit); CHECK(iRet>=0, lblDbaErr);
	}

    // Select parity
    // *************
	iDefItemP = tcModemItem[1];                                                          // Retrieve previous item selected
	iDefItemN = ShowMenu("PARITY", 2, iDefItemP, NUMBER_OF_ITEMS(tzParity), tzParity);
	CHECK(iDefItemN>=0, lblEnd);                                                         // Cancel, Timeout
	if (iDefItemN != iDefItemP)
	{
		tcModemInit[2] = *tzParity[iDefItemN];                                           // Save parity
		tcModemItem[1] = iDefItemN;                                                      // Save new item selected
		iRet = appPut(appModemItem, tcModemItem, lenModemItem); CHECK(iRet>=0, lblDbaErr); // Save modem parameters
		iRet = appPut(appModemInit, tcModemInit, lenModemInit); CHECK(iRet>=0, lblDbaErr);
	}

    // Select baud rate
    // ****************
	iDefItemP = tcModemItem[2];                                                          // Retrieve previous item selected
	iDefItemN = ShowMenu("BAUD  RATE", 2, iDefItemP, NUMBER_OF_ITEMS(tzBaudRate), tzBaudRate);
	CHECK(iDefItemN>=0, lblEnd);                                                         // Cancel, Timeout
	if (iDefItemN != iDefItemP)
	{
		strcpy (&tcModemInit[4], tzBaudRate[iDefItemN]);                                 // Save baud rate
		tcModemItem[2] = iDefItemN;                                                      // Save new item selected
		iRet = appPut(appModemItem, tcModemItem, lenModemItem); CHECK(iRet>=0, lblDbaErr); // Save modem parameters
		iRet = appPut(appModemInit, tcModemInit, lenModemInit); CHECK(iRet>=0, lblDbaErr);
	}

    // Enter pabx
    // **********
	do
	{
		iRet = appGet(appModemPabx, tcPabx, lenModemPabx+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  PABX", "", tcPabx, 0, lenModemPabx, 0);
		if (iRet<0)
		{
			DisplaySmall(5, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                                              // Cancel, Timeout
	if (iRet==2)                                                                         // Save pabx
	{
		iRet = appPut(appModemPabx, tcPabx, lenModemPabx); CHECK(iRet>=0, lblDbaErr);
	}
		
	// Enter prefix
	// ************
	do
	{
		iRet = appGet(appModemPrefix, tcPrefix, lenModemPrefix+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  PREFIX", "", tcPrefix, 0, lenModemPrefix, 0);
		if (iRet<0)
		{
			DisplaySmall(5, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                                              // Cancel, Timeout
	if (iRet==2)                                                                         // Save prefix
	{
		iRet = appPut(appModemPrefix, tcPrefix, lenModemPrefix); CHECK(iRet>=0, lblDbaErr);
	}
		
	// Enter country code
	// ******************
	do
	{
		iRet = appGet(appModemCountry, tcCountry, lenModemCountry+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  COUNTRY  CODE", "", tcCountry, 0, lenModemCountry, 0);
		if (iRet<0)
		{
			DisplaySmall(5, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                                              // Cancel, Timeout
	if (iRet==2)                                                                         // Save country code
	{
		iRet = appPut(appModemCountry, tcCountry, lenModemCountry); CHECK(iRet>=0, lblDbaErr);
	}
		
	// Enter phone number
	// ******************
	do
	{
		iRet = appGet(appModemPhone, tcPhone, lenModemPhone+1); CHECK(iRet>=0, lblDbaErr);
		iRet = ShowEntry("ENTER  PHONE  NUMBER", "", tcPhone, 0, lenModemPhone, 0);
		if (iRet<0)
		{
			DisplaySmall(5, 4, "Entry exceeded !!!");
			buzzer(10);
			ttestall(0, 2*100);
		}
	} while (iRet<0);
	CHECK(iRet!=0, lblEnd);                                                              // Cancel, Timeout
	if (iRet==2)                                                                         // Save phone number
	{
		iRet = appPut(appModemPhone, tcPhone, lenModemPhone); CHECK(iRet>=0, lblDbaErr);
	}
		
	goto lblEnd;

	// Errors treatment 
	// ****************
lblDbaErr:
	_clrscr();                                                                           // Clear screen
	DisplayMedium(0, 0, FMG_ErrorMsg(iRet));                                             // FMG error
	DisplayMedium(1, 0, "Reset Needed");                                                 // Rebuild data base
	ttestall(0, 5*100);                                                                  // Delay 5s
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
    LL_HANDLE *pvCom=NULL;
	char tcModemInit[lenModemInit+1];
	char *pcStr, tcStr[128+1];
    char tcSnd[MAX_SND+1];
    char tcRsp[MAX_RSP+1];
	int iRet=0, iStatus=0;

	// Transmission through internal Modem in progress
	// ***********************************************
    memset(tcSnd, 0, sizeof(tcSnd));
	memset(tcRsp, 0, sizeof(tcRsp));
	_clrscr();                                                      // Clear screen

	// Open modem 
	// ==========
	DisplayMedium(0, 0, "1-comOpen...");                            // Display start message
    pvCom = OpenModem(chnMdm); CHECK(pvCom!=NULL, lblKO);           // ** Open **
    DisplayMedium(1, 0, "1-comOpen OK");                            // Display open OK

	// Configure modem
	// ===============
	DisplayMedium(2, 0, "2-comSet...");                             // Display set message
	iRet = appGet(appModemInit, tcModemInit, lenModemInit+1);       // Retrieve init string
	CHECK(iRet>=0, lblDbaErr);
    DisplayMedium(3, 0, tcModemInit);                               // Display init string
    iRet = SetModem(tcModemInit); CHECK(iRet>=0, lblComKO);         // ** Set **
	_clrscr();                                                      // Clear screen
    DisplayMedium(0, 0, "2-comSet OK");                             // Display set OK

    // Dialing
	// =======
	DisplayMedium(1, 0, "3-comDial...");                            // Display dial message
	pcStr = tcStr;                                                  // Build dial string
	iRet = appGet(appModemPabx, pcStr, lenModemPabx+1);             // Retrieve pabx
	CHECK(iRet>=0, lblDbaErr);
	if (strlen(pcStr) != 0)
	{
		pcStr+=strlen(pcStr);
		*pcStr='-'; pcStr++;
	}
	iRet = appGet(appModemPrefix, pcStr, lenModemPrefix+1);         // Retrieve prefix
	CHECK(iRet>=0, lblDbaErr);
	if (strlen(pcStr) != 0)
	{
		pcStr+=strlen(pcStr);
		*pcStr='-'; pcStr++;
	}
	iRet = appGet(appModemCountry, pcStr, lenModemCountry+1);       // Retrieve country number
	CHECK(iRet>=0, lblDbaErr);
	if (strlen(pcStr) != 0)
	{
		pcStr+=strlen(pcStr);
		*pcStr='-'; pcStr++;
	}
	iRet = appGet(appModemPhone, pcStr, lenModemPhone+1);           // Retrieve phone number
	CHECK(iRet>=0, lblDbaErr);
    DisplayMedium(2, 0, tcStr);                                     // Display dial string
    iRet = ConnectModem(tcStr); CHECK(iRet>=0, lblComKO);           // ** Connect **
	DisplayMedium(3, 0, "3-comDial OK");                            // Display set OK

	// Clear sending/receiving buffers
	// ===============================
	iRet = LL_ClearSendBuffer(*pvCom);                              // Clear sending buffer
    CHECK(iRet==LL_ERROR_OK, lblComKO);
    iRet = LL_ClearReceiveBuffer(*pvCom);                           // Clear receiving buffer
    CHECK(iRet==LL_ERROR_OK, lblComKO);

    // Send data through modem
	// =======================
	_clrscr();                                                      // Clear screen
	DisplayMedium(0, 0, "4-comSend...");                            // Display send message
    strcpy(tcSnd, "Hello, do you hear me?\n"                        // Data to send
		          "Hello, do you hear me?\n"
		    	  "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n"
				  "Hello, do you hear me?\n");
	iRet = SendModem(tcSnd, (word) strlen(tcSnd));                  // ** Send data **
	CHECK(iRet>=0, lblComKO);
	DisplayMedium(1, 0, "4-comSend OK");                            // Display send OK
    
	// Receive data through modem
	// ==========================
	DisplayMedium(2, 0, "5-comRec...");                             // Display receive message
    iRet = ReceiveModem(tcRsp, sizeof(tcRsp), 30);                  // ** Receive data **
	CHECK(iRet>=0, lblComKO);
    if (iRet > MAX_RSP) strcpy (tcRsp, "Buffer overflow Max=512");  // Data overflow
	DisplayMedium(3, 0, "5-comRec OK");                             // Display receive OK

	// Disconnection
	// =============
    iRet = DisconnectModem();                                       // ** Disconnect **
	CHECK(iRet>=0, lblComKO);
	_clrscr();                                                      // Clear screen
	DisplayMedium(0, 0, "6-comDisconn OK");                         // Display disconnect OK
    iRet = CloseModem();                                            // ** Close **
	CHECK(iRet>=0, lblComKO);
	pvCom=NULL;

	// Display transmission data
	// =========================
	_clrscr();                                                      // Clear screen
	DisplaySmall(0, 0, "RECEIVING:");                               // Display data to receive
	iRet = Display25(1, tcRsp, strlen(tcRsp)); CHECK(iRet>=0, lblKO);
    DisplaySmall(7, 6, "Press a key");

	// Print transmission data
	// =======================
	iRet = pprintf("\x1b""E""         Modem Demo\n\n"               // Print demo in progress
		           "\x1b""F"); CHECK(iRet>=0, lblKO);      
    iRet = pprintf("Sending:\n"); CHECK(iRet>=0, lblKO);            // Print data to send
	iRet = Print24(tcSnd, strlen(tcSnd)); CHECK(iRet>=0, lblKO);
    iRet = pprintf("\nReceiving:\n"); CHECK(iRet>=0, lblKO);        // Print data to receive
	iRet = Print24(tcRsp, strlen(tcRsp)); CHECK(iRet>=0, lblKO);
    iRet = pprintf("\n\n\n\n\n\n"); CHECK(iRet>=0, lblKO);

	reset_buf(pxKbd, _receive_id);                                  // Reset keyboard FIFO
	ttestall(KEYBOARD, 30*100);                                     // Wait until key pressed or timeout
	reset_buf(pxKbd, _receive_id);                                  // Reset keyboard FIFO to clear key pressed

    goto lblEnd;

	// Errors treatment 
    // ****************
lblKO:                                                              // None-classified low level error
    _clrscr();                                                      // Clear screen
    DisplayMedium(0, 0, "Processing Error");                        // Oops! error
    ttestall(0,5*100);                                              // Delay 5s 
    goto lblEnd;
lblComKO:                                                           // Communication error
    _clrscr();                                                      // Clear screen
    DisplayMedium(0, 0, LL_ErrorMsg(iRet));                         // Link Layer error
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
		DisplayMedium(1, 0, LL_ErrorMsg(iStatus));                  // Link Layer status
	}
	ttestall(0,5*100);                                              // Delay 5s
    goto lblEnd;
lblDbaErr:                                                          // Data base error
	_clrscr();                                                      // Clear screen
	DisplayMedium(0, 0, FMG_ErrorMsg(iRet));                        // FMG error
	DisplayMedium(1, 0, "Reset Needed");                            // Rebuild data base
	ttestall(0, 5*100);                                             // Delay 5s
lblEnd:
    if (pvCom) {
    	DisconnectModem();                                          // ** Disconnect **
    	CloseModem();                                               // ** Close **
	}
}
