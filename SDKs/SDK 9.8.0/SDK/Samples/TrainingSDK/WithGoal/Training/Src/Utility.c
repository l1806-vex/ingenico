//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  UTILITY.C                          (Copyright INGENICO 2012)
//============================================================================
//  Created :       17-July-2012     Kassovic
//  Last modified : 17-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//  Utilities regarding some useful functions  
//                                                                            
//  List of routines in file :  
//      FMG_ErrorMsg : Table of error messages regarding File Management.
//      LL_ErrorMsg : Table of error messages regarding Link Layer.
//      SEC_ErrorMsg : Table of error messages regarding Security DLL.
//      OpenConverter : Open the converter Usb->Rs232.
//      BitOn : Set on the bit number.
//      BitOff : Set off the bit number.
//      BitTest : Test the bit number.   
//      SetParity : Set the parity bit.
//      CheckParity : Check the parity bit.
//      parseStr : String parsing.
//      UintToIp : Conversion of an unsigned integer to an IP address.
//      IpToUint : Conversion of an IP address to an unsigned int.
//      ParamExist : Check if parameter file is loaded in SYSTEM disk.
//      SoftwareReset : Reset parameters with default values.
//                            
//  File history :
//  071712-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "LinkLayer.h"
#include "schVar_def.h"
#include "SchutilTlv_def.h"
#include "VGE_FMG.H"
#include "Training.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
	/* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
static const char *tzConverter[] = {"COM_KEYSPAN", "COM_SL", "COM20", "COM21", "COM_MGBX"};
static char tcIp[15+1];

//****************************************************************************
//                     char* FMG_ErrorMsg (int iValue)
//  This function returns an error message regarding the FileManaGement.
//  This function has parameters.
//     iValue (I-) : Error value
//  This function has return value.
//    A message string regarding the error value.
//****************************************************************************

char* FMG_ErrorMsg (int iValue) 
{
	// Local variables 
    // ***************
	char *pcError;
	
	// List error messages 
    // *******************
	switch (iValue)
	{
	case -1:                                   pcError="MEMORY FAILED";    break; // Key unknown from the data base
	                       // ERRORS CODES
    // *** Generic errors ***
	case FMG_FILE_DOES_NOT_EXIST:              pcError="FILE NOT EXIST";   break;
	case FMG_FILE_ALREADY_EXIST:               pcError="FILE YET EXIST";   break;
	case FMG_BAD_RECORD_TYPE:                  pcError="BAD RECORD TYPE";  break;
	case FMG_BAD_CHECKSUM_TYPE:                pcError="BAD CHKSUM TYPE";  break;
	case FMG_BAD_FILE_TYPE:                    pcError="BAD FILE TYPE";    break;
	case FMG_BAD_RECORD_POSITION:              pcError="BAD RECORD INDEX"; break;
	case FMG_BAD_CREATION_PARAM:               pcError="BAD CREATE PARAM"; break;
	case FMG_BAD_PATH:                         pcError="BAD PATH";         break;
	case FMG_OPEN_FILE_PROBLEM:                pcError="OPEN FILE ERROR";  break;
	case FMG_CREATE_FILE_PROBLEM:              pcError="CREATE FILE ERR";  break;
	case FMG_DELETE_FILE_PROBLEM:              pcError="DELETE FILE ERR";  break;
	case FMG_NB_FILE_PROBLEM:                  pcError="FILE INDEX ERROR"; break;
	case FMG_MANAGEMENT_ERROR:                 pcError="FILE ERROR";       break;
	case FMG_ADD_RECORD_ERROR:                 pcError="ADD RECORD ERR";   break;
	case FMG_READ_RECORD_ERROR:                pcError="READ RECORD ERR";  break;
	case FMG_DELETE_RECORD_ERROR:              pcError="DEL RECORD ERR";   break;
	case FMG_CHECKSUM_PROBLEM:                 pcError="CHECKSUM ERROR";   break;
	case FMG_CORRUPTED_FILE:                   pcError="CORRUPTED FILE";   break;
	case FMG_CORRUPTED_RECORD:                 pcError="CORRUPTED RECORD"; break;
	case FMG_INIT_KO:                          pcError="FMG INIT ERROR";   break;
	// *** Other errors
	default:                                   pcError="ERROR UNKNOWN";    break;
	}
	
	return pcError;
}

//****************************************************************************
//                     char* LL_ErrorMsg (int iValue)
//  This function returns an error message regarding the LinkLayer.
//  This function has parameters.
//     iValue (I-) : Error value
//  This function has return value.
//    A message string regarding the error value.
//****************************************************************************

char* LL_ErrorMsg (int iValue) 
{
	// Local variables 
    // ***************
	char *pcError;
	
	// List error messages 
    // *******************
	switch (iValue)
	{
	case -1:                                    pcError="";                 break;  // Timeout/Cancel at GPRS level
	                       // STATUS CODES (re-define in Training.h)
	// *** GPRS status ***
	case LL_STATUS_GPRS_NO_SIM:                 pcError="NO SIM";           break;  // No SIM card is inserted in the terminal
	case LL_STATUS_GPRS_ERR_SIM_LOCK:           pcError="SIM LOCKED";       break;  // The SIM card is locked, enter PUK from Manager menu
	case LL_STATUS_GPRS_ERR_PPP:                pcError="GPRS PPP ERROR";   break;  // Error occurred during the PPP link establishment
	case LL_STATUS_GPRS_ERR_UNKNOWN:            pcError="GPRS UNKNOWN ERR"; break;  // Error GPRS status unknown
	// *** ETHERNET status ***
	case LL_STATUS_ETH_AVAILABLE:               pcError="LINK AVAILABLE";   break;  // The Ethernet link is available and ready to perform a communication
	case LL_STATUS_ETH_NO_DEFAULT_ROUTE:        pcError="NO DEFAULT ROUTE"; break;  // No default route is configured for Ethernet
	case LL_STATUS_ETH_NOT_PLUGGED:             pcError="CABLE NOT PLUG";   break;  // The Ethernet cable is not plugged to the terminal
	case LL_STATUS_ETH_BASE_NOT_READY:          pcError="BASE NOT READY";   break;  // The link between the Ethernet base and the terminal is not ready yet
	case LL_STATUS_ETH_OUT_OF_BASE:             pcError="OUT OF BASE";      break;  // An Ethernet link is available through a base, but the terminal needs to be on its cradle to use it
	// *** PHYSICAL status ***
	case LL_STATUS_PHY_PERIPHERAL_BUSY:         pcError="PERIPH BUSY";      break;  // The specified interface of the base is already used
	case LL_STATUS_PHY_PERIPHERAL_OUT_OF_BASE:  pcError="OUT OF BASE";      break;  // The peripheral can't be used since the terminal is not on its cradle
	case LL_STATUS_PHY_CONVERTER_NOT_PLUGGED:   pcError="CONVERT NOT PLUG"; break;  // The converter is unplugged
	// *** BLUETOOTH status ***
	case LL_STATUS_BT_NO_BASE_ASSOCIATED:       pcError="NO BASE ASSOCIAT"; break;  // No base is associated with the terminal
	case LL_STATUS_BT_PERIPHERAL_NOT_AVAILABLE: pcError="PB BASE ASSOCIAT"; break;  // The associated base does not have the specified communication interface
	case LL_STATUS_BT_PERIPHERAL_BUSY:          pcError="BASE BUSY";        break;  // The specified interface of the base is already used
	case LL_STATUS_BT_BASE_NOT_AVAILABLE:       pcError="BASE UNKNOWN";     break;  // The specified base is not available
	                       // ERRORS CODES
    // *** Generic errors ***
	case LL_ERROR_INTERNAL_RESOURCE:            pcError="RESOURCE ERROR";   break;  // Error in resource allocation (Refer the diagnostic ticket for more information)
	case LL_ERROR_UNKNOWN_CONFIG:               pcError="UNKOWN CONFIG";    break;  // Unknown Link Layer configuration
	case LL_ERROR_INVALID_HANDLE:               pcError="INVALID HANDLE";   break;  // The specified handle is not valid
	case LL_ERROR_SERVICE_NOT_SUPPORTED:        pcError="INVALID SERVICE";  break;  // Service from the Link Layer is not supported
	case LL_ERROR_TIMEOUT:                      pcError="TIMEOUT/CANCEL";   break;  // A timeout has expired
	case LL_ERROR_INVALID_PARAMETER:            pcError="INVALID PARAM";    break;  // The specified parameter is not valid
	case LL_ERROR_NOT_CONNECTED:                pcError="NOT CONNECT";      break;  // The communication has been disconnected (The link has been disconnected by the server)
	case LL_ERROR_ALREADY_CONNECTED:            pcError="ALREADY CONNECT";  break;  // You can not modify or delete a configuration that is in use (Disconnect it first)
	case LL_ERROR_DISCONNECTED:                 pcError="DISCONNECT";       break;  // The communication is disconnected due to a protocol or physical error
	case LL_ERROR_BUSY:                         pcError="BUSY";             break;  // The communication is busy
	case LL_ERROR_SERVICE_FORBIDDEN:            pcError="SERVICE REFUSED";  break;  // Service from the Link Layer is forbidden
	case LL_ERROR_NOT_READY:                    pcError="NOT READY";        break;  // The communication is not ready
	case LL_ERROR_NETWORK_NOT_READY:            pcError="NETWRK NOT READY"; break;  // The physical network (GSM, GPRS...) is not ready to perform the requested
	case LL_ERROR_NETWORK_NOT_SUPPORTED:        pcError="INVALID NETWORK";  break;  // The requested physical network is not supported by the terminal
	case LL_ERROR_NETWORK_ALREADY_CONNECTED:    pcError="NETWORK CONNECT";  break;  // Only returned by LL_GPRS_Connect() (The connection on the GPRS/3G network is already OK)
	case LL_ERROR_NETWORK_ERROR:                pcError="NETWORK ERROR";    break;  // Network error (Such as Ethernet cable not plugged, default route not configured...)
	case LL_ERROR_DLL:                          pcError="SSL DLL MISSING";  break;  // The SSL DLL is not loaded in the terminal
	case LL_ERROR_OUTPUT_BUFFER_TOO_SHORT:      pcError="BUFFER TOO SHORT"; break;  // Internal error (The interface object size is too short)
	case LL_ERROR_SERVICE_CALL_FAILURE:         pcError="NO LINK LAYER";    break;  // Error calling the service (Please check that the LinkLayer component is loaded in the terminal)
	case LL_ERROR_IP_VERSION_REQUIRED:          pcError="WRONG LINK LAYER"; break;  // The configuration requires the TCP/IP version of LinkLayer component
	// *** Session errors ***
	case LL_SESSION_ERROR_TOO_MANY_PROTOCOLS:   pcError="TOO MANY PROTOCL"; break;  // Invalid session stack (It contains too many protocols)
	case LL_SESSION_ERROR_UNKNOWN_PROTOCOL:     pcError="UNKNOWN PROTOCOL"; break;  // Invalid session stack (It contains an unknown protocol)
	// *** Physical layer errors ***
	case LL_ERROR_PHYSICAL_OVERRUN_BUFFER:      pcError="OVERRUN BUFFER";   break;  // Overrun buffer error
	case LL_ERROR_PHYSICAL_OVERRUN:             pcError="OVERRUN";          break;  // Overrun error (the stop bit is missing)
	case LL_ERROR_PHYSICAL_FRAMING:             pcError="FRAMING ERROR";    break;  // Framing error
	case LL_ERROR_PHYSICAL_PARITY:              pcError="PARITY ERROR";     break;  // Parity error
	// *** Modem errors ***
	case LL_MODEM_ERROR_SEND_BUFFER_OVERRUN:    pcError="AT CMD OVERRUN";   break;  // Overrun error of the sending buffer
	case LL_MODEM_ERROR_INIT_MODEM:             pcError="INIT MODEM ERR";   break;  // String AT command initialization failed
	case LL_MODEM_ERROR_RESPONSE_ERROR:         pcError="INVALID AT CMD";   break;  // The modem has returned an error
	case LL_MODEM_ERROR_RESPONSE_BLACKLISTED:   pcError="RESP BLACKLISTED"; break;  // The dialed number is blacklisted
	case LL_MODEM_ERROR_RESPONSE_DELAYED:       pcError="RESP DELAYED";     break;  // The modem has returned the DELAYED error
	case LL_MODEM_ERROR_RESPONSE_NO_DIALTONE:   pcError="NO DIALTONE";      break;  // No dial tone error
	case LL_MODEM_ERROR_RESPONSE_BUSY:          pcError="LINE BUSY";        break;  // The PSTN line is busy
	case LL_MODEM_ERROR_RESPONSE_NO_ANSWER:     pcError="NO ANSWER";        break;  // No answer from the remote part
	case LL_MODEM_ERROR_RESPONSE_NO_CARRIER:    pcError="NO CARRIER";       break;  // The communication has failed upon reception of NO CARRIER
	case LL_MODEM_ERROR_RESPONSE_INVALID:       pcError="INVALID ANSWER";   break;  // The modem has returned an unexpected answer
	// *** SDL errors ***
	case LL_HDLC_ERROR_CONNECT_TIMEOUT:         pcError="SDLC TIMEOUT";     break;  // The timeout of the HDLC connection has expired
	// *** PPP errors ***
	case LL_ERROR_PPP_CONNECT:                  pcError="PPP CONNECT ERR";  break;  // PPP connection error (Connection with the PPP provider failed (problem when negociating PPP options...))
	case LL_ERROR_PPP_AUTHENTICATION:           pcError="PPP AUTH ERROR";   break;  // PPP authentication error (The login and the password are not valid)
	case LL_ERROR_PPP_RAS_MODE:                 pcError="PPP RAS ERROR";    break;  // PPP connection error during the exchange "CLIENT" <-> "CLIENTSERVER"
	// *** TCP/IP errors ***
	case LL_ERROR_UNKNOWN_HOST:                 pcError="UNKNOWN HOST";     break;  // Unable to resolve the DNS name
	case LL_ERROR_CREATE_SOCKET:                pcError="SOCK CREATE ERR";  break;  // Error during the socket creation (Can be observed when too many sockets are used at the same time)
	case LL_ERROR_CANNOT_CONNECT:               pcError="SOCK CONNECT ERR"; break;  // Error during the socket connection (Either the remote server is not responding, or settings problems (configuration parameters, wrong certificate in SSL...))
	case LL_ERROR_CONNECTION_REFUSED:           pcError="CONNECT REFUSED";  break;  // The connection is refused by the remote server (In TCP, the 'errno' value of the socket is __ECONNREFUSED or In SSL, this can be caused by a failure during the SSL handshake)
	case LL_ERROR_HOST_UNREACHABLE:             pcError="HOST UNREACHABLE"; break;  // The host is unreachable (Cannot access the server : The 'errno' value of the socket is __EHOSTUNREACH)
	case LL_ERROR_NETWORK_UNREACHABLE:          pcError="NET UNREACHABLE";  break;  // The network is unreachable (Cannot access the server : The 'errno' value of the socket is __ENETUNREACH)
	// *** X28 errors ***
	case LL_X28_LIB:                            pcError="X28 LIB";          break;  // The network as returned the X28 message "LIB"
	case LL_X28_RESET:                          pcError="X28 RESET";        break;  // The network as returned the X28 message "RESET"
	case LL_X28_CLR:                            pcError="X28 CLR";          break;  // The network as returned the X28 message "CLR"
	// *** SSL errors ***
	case LL_ERROR_SSL_PROFILE:                  pcError="SSL PROFILE ERR";  break;  // The SSL profile cannot be loaded
	case LL_SSL_ERROR_SPECIFIC:                 pcError="SSL SPECIFIC ERR"; break;  // Base error for all SSL Specific error (from -9000 to -12000)
	// *** Other errors
	default:                                    pcError="ERROR UNKNOWN";    break;
	}
	
	return pcError;
}

//****************************************************************************
//                     char* SEC_ErrorMsg (int iValue)
//  This function returns an error message regarding the Security DLL.
//  This function has parameters.
//     iValue (I-): Error value
//  This function has return value.
//    A message string regarding the error value.
//****************************************************************************

char* SEC_ErrorMsg (int iValue)
{
	// Local variables
    // ***************
	char *pcError;

	// List error messages
    // *******************
	switch (iValue)
	{
                            // ERRORS CODES
	// *** Schemes common errors ***
	case 1:                         pcError="SCHEMES MISSING\n"
			                                "OR WRONG PROFILE"; break;
	case ERR_ID_NOT_FOUND:          pcError="ID NOT FOUND";     break;
	case ERR_PIN_CODE_NOT_FOUND:    pcError="PIN NOT FOUND";    break;
	case ERR_BAD_PIN_CODE_LEN:      pcError="PIN BAD LENGTH";   break;
	case ERR_BAD_IAPP_OPERATION:    pcError="IAPP FAILED";      break;
	case ERR_UNKNOW_FORMAT:         pcError="UNKNOWN FORMAT";   break;
	case ERR_DUKPT_END_OF_LIFE:     pcError="DUKPT EXPIRED";    break;
	case ERR_BAD_ACTION_TYPE:       pcError="BAD ACTION TYPE";  break;
	case ERR_ENTRY_CANCELED:        pcError="ENTRY CANCELED";   break;
	case ERR_TIMEOUT:               pcError="TIMEOUT EXPIRED";  break;
	case ERR_BAD_IHM_OPERATION:     pcError="HMI FAILED";       break;
	case ERR_SYSTEM:                pcError="SYSTEM ERROR";     break;
	case ERR_BAD_PARAM:             pcError="BAD PARAMETER";    break;
	case ERR_MAC_VERIFY:            pcError="MAC VERIFY KO";    break;
	case ERR_MAC_KEY:               pcError="MAC KEY FAILED";   break;
	case ERR_DUKPT_NOT_IN_FUNCTION: pcError="DUKPT MISSING";    break;
	case ERR_DIFFERENCE:            pcError="ERROR MISMATCHED"; break;
	case C_UTLV_TYPE_NOT_TLV:		pcError="NO TLV TYPE";      break;
	case C_UTLV_TYPE_NO_SECRET:     pcError="NO SECRET TYPE";   break;
	default:
		switch (iValue)
		{
		// *** Schemes loading errors ***
		case -1:                    pcError="ID FULL";          break;
		case -2:                    pcError="ID ALREADY EXIST"; break;
		case -3:                    pcError="ID UNKNOWN";       break;
		case -4:                    pcError="NO MORE MEMORY";   break;
		case -5:                    pcError="BAD INIT";         break;
		case -6:                    pcError="JUST DOWNLOADED";  break;
		case -7:                    pcError="BAD PARAMETER";    break;
		case -8:                    pcError="GLOBAL ERROR";     break;
		case -9:                    pcError="SCHEMES MISSING";  break;
		case -10:                   pcError="ERROR ADDRESS";    break;
		case -11:                   pcError="WARNING ADDRESS";  break;
		case -12:                   pcError="CERTIFICATE KO";   break;
		default:                    pcError="ERROR UNKNOWN";    break;
		}
	}

	return pcError;
}

//****************************************************************************
//               FILE *OpenConverter (char *pcName, byte ucSize)
//  This function opens the converter Usb->RS232 if exists.
// 	Telium supports the following drivers:
// 	  - "COM_KEYSPAN" (Keyspan USA19HS)
// 	  - "COM_SL" (SiliconLabs CP2102)
// 	  - "COM20" (Prolific 2303)
// 	  - "COM21" (FTDI)
//    - "COM_MGBX" (Generic Magic Box)
//  This function has parameters.
//     pcName (-O) : Buffer driver name.
//     ucSize (I-) : Buffer size.
//  This function has return value.
//     NULL if converter not found or wrong parameter.
//     Driver file if converter found.
//****************************************************************************

FILE *OpenConverter(char *pcName, byte ucSize)
{
	// Local variables
    // ***************
	int i;
	FILE *pxCom;
	byte ucSta;

	// Converter detection in progress
	// *******************************
	for (i=0; i<NUMBER_OF_ITEMS(tzConverter); i++)
	{
		pxCom = fopen(tzConverter[i], "rw*");                // Open converter peripheral
		if(pxCom)
		{
			status (pxCom, &ucSta);                          // Check if converter recognized
			if ( (ucSta & USB_PRESENT) == USB_PRESENT)
			{
				if (ucSize > strlen((char*)tzConverter[i]))
				{
					strcpy (pcName, (char*)tzConverter[i]);	 // Return driver name and driver file
					return pxCom;
				}
			}
			else
				fclose(pxCom);                               // Close converter unrecognized
		}
	}

	return NULL;                                             // Converter not found
}

//****************************************************************************
//                  void BitOn (char *pcBuf, byte ucIdx)
//  This function sets on the bit number Idx in Buf. Bits are numbered from 
//  left to right starting from 1.
//  This function has parameters.
//     pcBuf (I-) : Binary buffer containing a bitmap
//     ucIdx (I-) : Related bit number
//  This function has no return value.
//****************************************************************************

static void BitOn (char *pcBuf, byte ucIdx)
{
    ucIdx--;
    while(ucIdx >= 8) 
    {
        pcBuf++;
        ucIdx -= 8;
    }
    *pcBuf |= (0x01 << (7 - ucIdx));
}

//****************************************************************************
//                  void BitOff (char *pcBuf, byte ucIdx)
//  This function sets off the bit number Idx in Buf. Bits are numbered from 
//  left to right starting from 1.
//  This function has parameters.
//     pcBuf (I-) : Binary buffer containing a bitmap
//     ucIdx (I-) : Related bit number
//  This function has no return value.
//****************************************************************************

static void BitOff (char *pcBuf, byte ucIdx)
{
    ucIdx--;
    while(ucIdx >= 8) 
    {
        pcBuf++;
        ucIdx -= 8;
    }
    *pcBuf &= ~(0x01 << (7 - ucIdx));
}

//****************************************************************************
//               byte BitTest (const char *pcBuf, byte ucIdx)
//  This function tests the bit number Idx in Buf. Bits are numbered left to right 
//  starting from 1.
//  This function has parameters.
//     pcBuf (I-) : Binary buffer containing a bitmap
//     ucIdx (I-) : Related bit number
//  This function has return value.
//    0   : if the related bit is off
//    !=0 : otherwise 
//****************************************************************************

static byte BitTest (const char *pcBuf, byte ucIdx)
{
    ucIdx--;
    while(ucIdx >= 8) 
    {
        pcBuf++;
        ucIdx -= 8;
    }
    return ((*pcBuf) >> (7 - ucIdx)) & 0x01;
}

//****************************************************************************
//      void SetParity (char *pcBuf, word usDim, byte ucPar, byte ucTyp)
//  This function sets the parity bit in Buf (even or odd). Position of the
//  parity bit 1 or 8.
//  This function has parameters.
//     pcBuf (I-) : Binary buffer to be set
//     usDim (I-) : Buffer size
//     usPar (I-) : Position of the parity bit 1 or 8
//     ucTyp (I-) : Even or Odd parity
//  This function has no return value.
//****************************************************************************

void SetParity (char *pcBuf, word usDim, byte ucPar, byte ucTyp)
{
	// Local variables 
    // ***************
    byte ucCnt, ucIdx;

    // Set parity in progress
    // **********************
    while(usDim--) 
    {
        ucCnt=0;
        for (ucIdx=1; ucIdx<=8; ucIdx++) 
        {
            if (ucIdx == ucPar)
                continue;
            if (BitTest(pcBuf, ucIdx))
                ucCnt++;
        }
        switch (ucTyp) 
        {
        case 'E':
        	if (ucCnt % 2)
        		BitOn(pcBuf, ucPar);  // An even parity bit is set to 1 if the number of ones in a given set of bits is odd
        	else
                BitOff(pcBuf, ucPar);
            break;
        case 'O':
            if (ucCnt % 2)
            	BitOff(pcBuf, ucPar);
            else
                BitOn(pcBuf, ucPar);  // An odd parity bit is set to 1 if the number of ones in a given set of bits is even
            break;
        default:
        	break;
        }
        pcBuf++;
    }
}


//****************************************************************************
//    byte CheckParity (const char *pcBuf, word usDim, byte ucPar, byte ucTyp)
//  This function checks the parity bit in Buf (even or odd). Position of the
//  parity bit 1 or 8.
//  This function has parameters.
//     pcBuf (I-) : Binary buffer to be checked
//     usDim (I-) : Buffer size
//     usPar (I-) : Position of the parity bit 1 or 8
//     ucTyp (I-) : Even or Odd parity
//  This function has return value.
//    1 : if parity is OK 
//    0 : if parity NOK
//****************************************************************************

byte CheckParity (const char *pcBuf, word usDim, byte ucPar, byte ucTyp)
{
	// Local variables 
    // ***************
    byte ucCnt, ucIdx;
    byte ucRet;

    // Check parity in progress
    // ************************
    ucRet=1;
    while (usDim--) 
    {
        ucCnt=0;
        for (ucIdx=1; ucIdx<=8; ucIdx++) 
        {
            if (BitTest(pcBuf, ucIdx))
                ucCnt++;
        }
        switch(ucTyp)
        {
        case 'O' :
        	if (!(ucCnt%2)) // Making the total number of ones, including the parity bit, odd
        		ucRet=0;
        	break;
		case 'E':
		    if (ucCnt%2)    // Making the total number of ones, including the parity bit, even
		    	ucRet=0;
        	break;
		default:            // Unknown parity
			ucRet=0;
            break;
        }
        pcBuf++;
    }
    
    return ucRet;
}

//****************************************************************************
//  const char *parseStr(char ucToken, char *pcDst, const char *pcSrc, int iDim)
//  This function parses a string to extract part of it when reaching a token.
//  This function has parameters.
//    ucToken (I-) : Token to reach.
//    pcDst (-O) : Result buffer.
//    pcSrc (I-) : String to parse.
//    iDim (I-) : Result buffer size.
//  This function has return value.
//    NULL : Parsing failed
//    !NULL : Pointer to the end of string extracted.
//****************************************************************************

const char *parseStr(char ucToken, char *pcDst, const char *pcSrc, int iDim)
{
    while(*pcSrc)
    {
    	if (iDim == 0)        // Buffer pcDst overflow
    		return NULL;      // Parsing failed

        if(*pcSrc == ucToken) // Token found
        {
            pcSrc++;          // Skip token
            break;
        }

        *pcDst++ = *pcSrc++;
        iDim--;
    }

    *pcDst=0;
    return pcSrc;
}

//****************************************************************************
//                     char* UintToIp (doubleword uiVal)
//  This function converts an unsigned integer to an IP address.
//  Ex: 0xC0A80202 => 192.168.2.2
//  This function has parameters.
//    uiVal (I-) : The value to convert.
//  This function has return value.
//    A string buffer regarding the IP address.
//****************************************************************************

char* UintToIp(doubleword uiVal)
{
	// Local variables
    // ***************
	byte ucVal1, ucVal2, ucVal3, ucVal4;

	// Conversion unsigned long to Ip address
	// **************************************
	ucVal1 = uiVal%256;
	ucVal2 = (uiVal/256)%256;
	ucVal3 = (uiVal/(256*256))%256;
	ucVal4 = (uiVal/(256*256*256))%256;

	memset(tcIp, 0, sizeof(tcIp));
	sprintf (tcIp, "%d.%d.%d.%d", ucVal4, ucVal3, ucVal2, ucVal1);

	return tcIp;
}

//****************************************************************************
//                 doubleword IpToUint (const char *pcStr)
//  This function converts an IP address to an unsigned int.
//  Ex: 192.168.2.2 => 0xC0A80202
//  This function has parameters.
//    pcStr (I-) : The string to convert.
//  This function has return value.
//    An unsigned long regarding the IP address.
//****************************************************************************

doubleword IpToUint(const char *pcStr)
{
	// Local variables
    // ***************
	char tcStr1[3+1], tcStr2[3+1], tcStr3[3+1], tcStr4[3+1];
	doubleword uiVal=0;
	
	// Conversion Ip address to unsigned int
	// *************************************
	if (*pcStr)
	{
		memset(tcStr4, 0, sizeof(tcStr4));
		pcStr = parseStr('.', tcStr4, pcStr, sizeof(tcStr4));
	    if(pcStr==NULL)
	    	return 0;
	    memset(tcStr3, 0, sizeof(tcStr3));
	    pcStr = parseStr('.', tcStr3, pcStr, sizeof(tcStr3));
	    if(pcStr==NULL)
	    	return 0;
	    memset(tcStr2, 0, sizeof(tcStr2));
	    pcStr = parseStr('.', tcStr2, pcStr, sizeof(tcStr2));
	    if(pcStr==NULL)
	    	return 0;
	    memset(tcStr1, 0, sizeof(tcStr1));
	    pcStr = parseStr('.', tcStr1, pcStr, sizeof(tcStr1));
	    if(pcStr==NULL)
	    	return 0;

	    uiVal = atoi(tcStr4)*256*256*256 + atoi(tcStr3)*256*256 + atoi(tcStr2)*256 + atoi(tcStr1);
	}

	return uiVal;
}

//****************************************************************************
//            int ParamExist (word usFileType, char *pcFileName)
//  This function returns true or false depending if the specified parameter
//  file is loaded or not inside the system disk.
//  This function has parameters:
//     usAppliType (I-) : Application type (unique in terminal)
//     pcFamilyName (I-) : Generic name of the parameter file
//  This function has return value.
//     true : Parameter file present
//     false : Parameter file absent
//****************************************************************************

int ParamExist(word usAppliType, char *pcFamilyName)
{
	// Local variables
    // ***************
	object_descriptor_t xObj;
	int iRet;

	// Search parameter file
	// *********************
	iRet = ObjectGetDescriptor (OBJECT_TYPE_PARAM, usAppliType, &xObj);

	if (iRet == 0)
	{
		if (strcmp ((char*)xObj.appli_family, pcFamilyName) == 0)
			return TRUE;                                   // Parameter file present in SYSTEM disk
	}

	return FALSE;                                          // Parameter file absent from SYSTEM disk
}
