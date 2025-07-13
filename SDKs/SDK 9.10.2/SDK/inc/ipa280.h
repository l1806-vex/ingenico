/******************************************************************************/
/*                                                                            */
/*            Copyright (C) 2009.  Ingenico France.                           */
/*      All rights reserved.  No part of this program or listing may          */
/*      be reproduced transmitted, transcribed, stored in a retrieval         */
/*      system, or translated into any language, in any form or by any        */
/*      means, electronic, mechanical, magnetic, optical, chemical,           */
/*      manual, or otherwise, without the prior written permission of         */
/*                                                                            */
/*      Ingenico France                                                       */
/*                                                                            */
/*============================================================================*/
/*                                                                            */
/* Module Name: lib_ipa280.h                                                  */
/*                                                                            */
/* Function:    API functions provided by ipa280                              */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/*============================================================================*/
/* usr | yy-mm-dd |                                        |                  */
/* ewc | 09-06-15 | New for IPA280                         |                  */
/******************************************************************************/

#ifndef _LIB_IPA280_H
#define _LIB_IPA280_H

#include <sdk30.h>
#include "ipa280_def.h"
#include "ipa280_type.h"
#include "TlvTree.h"

//PDA_start_transaction defines


//! \addtogroup KSFAM_SPMCI_GlobalDefines
//! \{

typedef void* SPMCI_HANDLE;	//!< SPCM generic handle.

#define __SPMCI_MAGIC						0x0100BAB3			//!< SPMCI Magic number.
#define __SPMCI_MAX_EXTENDED_DATA_SIZE		(16*1024)			//!< Maximum size for the extended data.


//! \brief Service to implement the transaction without requesting an implicit selection to the Telium Manager.

//! The Telium application implementing this service is explicitely selected by the SMPCI application without requesting 
//! the Telium Manager's service 100.
//!
//! The parameters of this service call are encoded using the structure \ref T_SERVICE_CALL_PARAM_PDA_START_TRANSACTION 
//! (when extended data must be exchanged) or using the Telium Manager's structure StructDebitEmv
//! (when there is no extended data).

//! The function implementing this service must test the size of the input parameter structure to determine which type of
//! structure is used.
//! \code
//!int PdaTransaction (unsigned int nDataSize, void* pData)
//!{
//!	StructDebitEmv *psDebit = NULL;

//!	if( nDataSize == sizeof( StructDebitEmv ))
//!	{
//!
//!		// Input parameter without extended data.
//!
//!		psDebit = ( StructDebitEmv * ) pData;
//!	}
//!	else
//!	{
//!		// Input parameter with extended data.
//!		T_SERVICE_CALL_PARAM_PDA_START_TRANSACTION *pParams = ( T_SERVICE_CALL_PARAM_PDA_START_TRANSACTION *) pData;
//!
//!		char szTemp[100];
//!
//!		if( pParams->m_nMagic == __SPMCI_MAGIC )
//!		{
//!			// The parameter handle is valid.
//!			psDebit = &pParams->m_sDebitEmv;
//!
//!			// Send extended data in response.
//!			pParams->m_nResponseSize = sprintf(	szTemp, "Payment Application=%x, 
//!												res=%d", ApplicationGetCurrent(), (int) psDebit->param_out.rc_payment );
//!			strcpy( pParams->m_pucResponse, szTemp );
//!
//!		}
//!	}
//!
//!	return 0;
//!}

//! \endcode

//!\note If serveral applications implements the \ref PDA_START_TRANSACTION service, only the first one loaded in the terminal
//! is selected.
#define		PDA_START_TRANSACTION	0x1E05

//! \brief Structure used to exchange the parameters for the service call \ref PDA_START_TRANSACTION.
typedef struct
{
	StructDebitEmv	m_sDebitEmv;	//!< Parameter structure for the ServiceCall 100 (please refer the documentation of the TELIUM Manager).

	//
	unsigned int m_nMagic;		//!< Must be set to \ref __SPMCI_MAGIC.
	unsigned int m_nRuf;		//!< Reserved for future use (must be set to 0).

	//
	int m_nTransactionType;		//!< Transaction type character.

	//
	unsigned int m_nResponseSize;	//!< Size of the extended data in response.
	unsigned char m_pucResponse[__SPMCI_MAX_EXTENDED_DATA_SIZE];	//!< Buffer containing the extended data in response.

	// Extended Data.
	unsigned int m_nSize;		//!< Size of the extended data contained in the request.
	unsigned char m_ucData;		//!< Field to retrieve the address of the buffer containing the extended data of the request.

} T_SERVICE_CALL_PARAM_PDA_START_TRANSACTION;

// Prototypes.

/** SPMCI SERVER PRIVATE FUNCTION
SPM_set_time called to set the SPM date. This API is used in SPMCI server, and called when receiving a
 Set SPM Time request from PDA.
\param date : pointer to structure DATE, contain date information.
\return
- On success, 0x00 is returned.
- On error,   0x02 is returned if time modification is refused, 0x01 is returned othrewise. */
int  SPM_set_time( DATE * date);

/** SPMCI SERVER PRIVATE FUNCTION
SPM_get_status called to get the SPM satus. This API is used in SPMCI server, and called when receiving a
 Get SPM Status request from PDA.
\return
- On Idle, 0x01 is returned.
- On Buzy, 0x02 is returned.*/
int  SPM_get_status( void );

/** SPMCI SERVER PRIVATE FUNCTION
SPM_get_information called to get SPM serial number and product range. This API is used in SPMCI server, 
 and called when receiving a Get Information request from PDA.
\param SPMInformation : pointer to structure T_SPMInformation, contain SPM information.
\return
- On success, 0x00 is returned.
- On error,   0x01 is returned. */
int  SPM_get_information( T_SPMInformation * SPMInformation);

/** SPMCI SERVER PRIVATE FUNCTION
SPM_do_update called to perform an SPM update. This API is used in SPMCI server, and called when receiving a
 do update request from PDA.
\return Download report. */
int  SPM_do_update( void );

/** SPMCI SERVER PRIVATE FUNCTION
SPM_receive_message called when receiving message from PDA. This API is used in SPMCI server.
\param parent_node : pointer to structure TLV_TREE_NODE, contain message node in TLV format.
\return
- On success, 0x00 is returned.
- On error,   0x01 is returned.*/
int  SPM_receive_message( TLV_TREE_NODE parent_node);

//! \addtogroup PCL_API Common functions
//! @{

/** PDA_get_information called to get PDA serial number. This API is used by applications.
@param pSerialNumber : [out] pointer to buffer where to store serial number (managed by applications)
@param pSize : [in/out] pointer to the size of the buffer
@return
- On success,         0x00 is returned, the length of the serial number is set in pSize.
- otherwise,  		  0x01 is returned, the needed size is returned in pSize*/
int PDA_get_serial_number( char * pSerialNumber, int *pSize);

/** PDA_set_comm_periph_state called to set PDA peripheral to preffered satus. This API is used by applications.
@param pda_periph : 0x00 - PDA_GPRS
                    0x01 - PDA_WLAN
                    0x02 - PDA_BLUETOOTH
                    0x03 - PDA_LAN
@return
- On connected,         0x00 is returned.
- On cannot turned on,  0x01 is returned.
- On cannot connect,    0x02 is returned. */
int  PDA_set_comm_periph_state( uchar pda_periph);

/** PDA_get_comm_periph_state called to get PDA peripheral status. This API is used by applications.
@param PDAPeripheralState : pointer to structure T_PDAPeripheralState, contain PDA peripheral state information.
@return
- On success, 0x00 is returned.
- On timeout, 0x01 is returned. */
int  PDA_get_comm_periph_state( T_PDAPeripheralState * PDAPeripheralState);

/** PDA_set_spm_update_time called to set update time : when the SPM must be waked up. This API is used by applications.s
@param date : pointer to structure DATE, contain date information.
@return
- On success, 0x00 is returned.
- On error,   0x01 is returned.*/
int  PDA_set_spm_update_time( DATE * date);

/** PDA_send_message called to send message to PDA. This API is used by application.
@param buffer : pointer to the buffer to send.
@param bufSize : size of the buffer to send
@return
- On success, 0x00 is returned.
- On error,   0x01 is returned. */
int  PDA_send_message(void * buffer, unsigned int bufSize);

/** Open printer channel 
@param jobId pointer to job id allocated
@return returns 0 if success, returns 1 if failed */
int IPA_printer_open(IPA_JOB_ID * jobId);

/** Close printer channel 
@param jobId printer job id 
@return returns 0 if success, returns 1 if failed */
int IPA_printer_close(IPA_JOB_ID jobId);

/** Print text line 
@param jobId printer job id 
@param text text to print 
@return returns 0 if success, returns 1 if failed */
int IPA_printer_printText (IPA_JOB_ID jobId, const char * text);

/** This function will print out the image with specified width and height. (for more details see apiPrintOutImage in M81B SDK documentation) 
@param jobId printer job id 
@param width number of pixels in horizontal direction
@param height number of pixels in vertical direction
@param image the pointer to the raw image data
@return returns 0 if success, returns 1 if failed */
int IPA_printer_printImage(IPA_JOB_ID jobId, unsigned long width, unsigned long height, const void *image);

/** This function will get the jobId status. (for more details see apiGetPrinterStatus in M81B or M82 SDK documentation)
@param jobId printer job id 
@param pStatus pointer to variable bitmask status which has the following meaning:
for IPA:
 - Bit 0 Head temperature : Off=OK, On=Too high or too low
 - Bit 1 Head-up : Off=Don't care, On=Don't care
 - Bit 2 Paper out :  Off=No, On=Yes
 - Bit 3 Power supply : Off=OK, On=Too high or too low
 - Bit 4 Printer in use : Off=Ready, On=Action in progress
 - Bit 5 On/Off line : Off, On
 - Bit 6 Hole/Mark detection Error : Off=Don't care On=Don't care
 - Bit 7 Cutter failure : Off=Yes On=No
for IWP:
 - Bit 0 Paper out :  Off=No, On=Yes
 - Bit 1 Lever Position Error : Off=No Error, On=Error on lever position
 - Bit 2 Paper near end : Off=Don't care, On=Don't care
 - Bit 3 Head temperature : Off=OK, On=Too high or too low
 - Bit 4 Autocutter error : Off=No Error, On=Error on auto-cutter
 - Bit 5 voltage error : Off=No Error On=Error on voltage
@return returns 0 if success, returns 1 if failed */
int IPA_printer_getStatus (IPA_JOB_ID jobId, unsigned short *pStatus);

/** This function will select the font for printing. (for more details see apiPrinterSelectInternalFont in M81B or M82 SDK documentation)
@param jobId printer job id
@param font The font value to be set. Not all characters are the same for all font.
for IPA:
 - 0: 8x16 Font is selected. (default)
 - 1: 12x20 Font is selected.
 - 2: 7x16 Font is selected.
for IWP:
 - 0: 24 dot size is selected. (default)
 - 1: 16 dot size is selected.
@return returns 0 if success, returns 1 if failed */
int IPA_printer_setFont (IPA_JOB_ID jobId, unsigned char font);

//! @}
//! \addtogroup IPA280_Only Specific functions only available on the SPM
//! @{

/** PDA_do_signature_capture called to get signature capture from PDA. This API is used applications. This API is deprecated, use \ref PDA_getSignature() instead.
@param Signature    : pointer to structure T_Signature, contain signature capture.
@return
- On success, 0x00 is returned.
- On error,   0x01 is returned. */
int  PDA_do_signature_capture( T_Signature * Signature);

/** PDA_getSignature called to get signature capture from PDA. This API is used by applications.
@param[in]  pSettings:    configuration of the signature capture (size and position).
@param[out] pucBmpBuffer: buffer to store the signature BMP data.
@param[in]  nBufferSize:  size of the previous buffer.
@param[out] pBmpSize:     pointer filled with the size of the signature BMP data.
@return
- On success, 0x00 is returned.
- On error,   0x01 is returned. */
int PDA_getSignature( const T_CAPTURE_SETTINGS* pSettings, unsigned char* pucBmpBuffer, unsigned int nBufferSize, unsigned int* pBmpSize );

/** This function will feed specified number of dot lines of paper. (for more details see apiPrinterFeedPaper in M81B SDK documentation)
@param jobId printer job id
@param ndotlines The specified number of dot lines to be fed, 0 < ndotlines < 256. ndotlines > 0: Paper is fed for (ndotlines times 0.125 mm) forward. The print position is at the beginning of the next line.
@return returns 0 if success, returns 1 if failed */
int IPA_printer_feedPaper(IPA_JOB_ID jobId, int ndotlines);

/** This function will set the print intensity. (for more details see apiSetPrintIntensity in M81B SDK documentation) 
@param jobId printer job id 
@param intensity The intensity value to be set. Valid intensity: from 0 to FFh (255). :
 - intensity = 80h (128): Default normal print intensity
 - intensity < 80h (128): Printout becomes lighter.
 - intensity > 80h (128): Printout becomes darker.
@return returns 0 if success, returns 1 if failed */
int IPA_printer_setIntensity (IPA_JOB_ID jobId, unsigned char intensity);

/** This function will select the international character set for printing. (for more details see apiPrinterSelectCharSet in M81B SDK documentation) 
@param jobId printer job id 
@param charSet The international character set to be selected
 - 0: USA, default
 - 1: France
 - 2: Germany
 - 3: UK
 - 4: Denmark1
 - 5: Sweden
 - 6: Italy
 - 7: Spain1
 - 8: Japan
 - 9: Norway
 - 10: Denmark2
 - 11: Spain2
 - 12: Latin America.
@return returns 0 if success, returns 1 if failed */
int IPA_printer_setCharSet (IPA_JOB_ID jobId, unsigned char charSet);

/** This function will set the printout text justification.  (for more details see apiPrinterSetTextJust in M81B SDK documentation) 
@param jobId printer job id 
@param justification The text justification to be set.
 - 0: text will be centered.
 - 1: text will be right justified.
 - 2: text will be left justified (default).
@return returns 0 if success, returns 1 if failed */
int IPA_printer_setTextJust (IPA_JOB_ID jobId, unsigned char justification);

/** This function will set the print mode. (for more details see apiSetPrintMode in M81B SDK documentation) 
@param jobId printer job id 
@param mode The value of mode (default 0) selects the print mode.
 - bit 1 Quadruple Height : Off=Cancelled, On=Set
 - bit 2 Quadruple Width : Off=Cancelled, On=Set
 - bit 4 Double Height : Off=Cancelled, On=Set
 - bit 5 Double Width : Off=Cancelled, On=Set
 - bit 7 Underlined : Off=Cancelled, On=Set
@return returns 0 if success, returns 1 if failed */
int IPA_printer_setPrintMode (IPA_JOB_ID jobId, unsigned char mode);

/** This function will connect the IPA to the specified number over GSM Data
@param phContext pointer to a HANDLE variable to store GSM Context
@param SimSlot SimSlot to activate
@param Pin PinCode of the SIM Card (send void string if SIM isn't Pin Protected)
@param DialNumber Phone number to dial
@param Modulation Modulation to use for the call
- PDAGSM_MODULATION_V21
- PDAGSM_MODULATION_V22
- PDAGSM_MODULATION_V22BIS
- PDAGSM_MODULATION_V23
- PDAGSM_MODULATION_V26TER
- PDAGSM_MODULATION_V32
- PDAGSM_MODULATION_V34
- PDAGSM_MODULATION_V110
- PDAGSM_MODULATION_V120
- PDAGSM_MODULATION_TRANSP
@param Service modem service to use for the call
- PDAGSM_SERVICE_UNKNOWN
- PDAGSM_SERVICE_MODEM_ASYNC
- PDAGSM_SERVICE_MODEM_SYNC
- PDAGSM_SERVICE_PADACCESS_ASYNC
- PDAGSM_SERVICE_PACKETACCESS_SYNC
@param Speed baudrate to use for the call
- PDAGSM_SPEED_AUTO
- PDAGSM_SPEED_300
- PDAGSM_SPEED_1200
- PDAGSM_SPEED_1200_75
- PDAGSM_SPEED_2400
- PDAGSM_SPEED_4800
- PDAGSM_SPEED_9600
- PDAGSM_SPEED_14400
- PDAGSM_SPEED_19200
- PDAGSM_SPEED_28800
- PDAGSM_SPEED_38400
- PDAGSM_SPEED_48000
- PDAGSM_SPEED_56000
- PDAGSM_SPEED_64000
@param ConnectionElement Connection type of the call
- PDAGSM_CONNELEM_UNKNOWN
- PDAGSM_CONNELEM_TRANSPARENT
- PDAGSM_CONNELEM_NONTRANSPARENT
- PDAGSM_CONNELEM_BOTH_TRANSPARENT
- PDAGSM_CONNELEM_BOTH_NONTRANSPARENT
@param timeout timeout in ms before exiting in case of error
@return returns 0 if success, otherwise see error in ePdaModemError enum*/
int IPA_GSMConnect(HANDLE *phContext, unsigned char SimSlot, unsigned char *Pin, unsigned char *DialNumber, unsigned long Modulation, unsigned long Service, unsigned long Speed, unsigned long ConnectionElement, unsigned long timeout);

/** Disconnect from GSM Data
@param hContext GSM Context returned by IPA_GSMConnect
@return returns 0 if success, otherwise see error in ePdaModemError enum*/
int IPA_GSMDisconnect(HANDLE hContext);

/** Get GSM Data Status
@param hContext GSM Context returned by IPA_GSMConnect
@param Status pointer to store GSM Status
@return returns 0 if success, otherwise see error in ePdaModemError enum*/
int IPA_GSMStatus(HANDLE hContext, unsigned long *Status);

/** Get GSM Data Status
@param hContext GSM Context returned by IPA_GSMConnect
@param Size size of the buffer to send
@param pData pointer to data to send
@return returns 0 if success, otherwise see error in ePdaModemError enum*/
int IPA_GSMSend(HANDLE hContext, unsigned int Size, unsigned char *pData);

/** Get GSM Data Status
@param hContext GSM Context returned by IPA_GSMConnect
@param Size pointer to variable which store the maximum size of the buffer and returned the actual received data size
@param pData pointer to buffer where to store received data
@param ulTimeout timeout of the function
@return returns 0 if success, otherwise see error in ePdaModemError enum*/
int IPA_GSMReceive(HANDLE hContext, unsigned int *Size, unsigned char *pData, unsigned long ulTimeout);

/** Clear GSM Data Tx Buffer
@param hContext GSM Context returned by IPA_GSMConnect
@return returns 0 if success, otherwise see error in ePdaModemError enum*/
int IPA_GSMClearSendBuffer(HANDLE hContext);

/** Clear GSM Data Rx Buffer
@param hContext GSM Context returned by IPA_GSMConnect
@return returns 0 if success, otherwise see error in ePdaModemError enum*/
int IPA_GSMClearReceiveBuffer(HANDLE hContext);

//! @}
//! \addtogroup PCL_API Common functions
//! @{

/** Get_PCL_State called to get PCL state. This API is used by applications.
 * @return returns PCL_STATE_NOT_STARTED, PCL_STATE_STARTED_NOT_INITIALIZED or PCL_STATE_STARTED_INITIALIZED.
 * */
int PCL_get_state(void);

/** Get Modem Info
@param hGSMContext GSM Context returned by IPA_GSMConnect
@param hGPRSContext GPRS Context returned by PDA_GPRSConnect
@param SimSlot SimSlot currently used
@param SimID Sim identification number
@param inet_addr IP address of the GPRS connection (if connected otherwise 0.0.0.0)
@param operator_name operator associated with SIM
@param IMEI modem IMEI number
@param RSSI signal quality level
@return returns 0 if success, otherwise see error in ePdaModemError enum*/
int PDA_ModemInfo(HANDLE hGSMContext,HANDLE hGPRSContext,unsigned char *SimSlot,unsigned char *SimID,unsigned long *inet_addr,unsigned char *operator_name,unsigned char *IMEI,unsigned long *RSSI);

/** Connect to GPRS
@param phContext pointer to a HANDLE variable to store GPRS Context
@param SimSlot SimSlot to activate
@param Pin PinCode of the SIM Card (send void string if SIM isn't Pin Protected)
@param APN name of the GPRS Access Point
@param username Username used to connect to APN (void string if no username required)
@param password Password used to connect to APN (void string if no password required)
@param timeout timeout in ms before exiting in case of error
@return returns 0 if success, otherwise see error in ePdaModemError enum*/
int PDA_GPRSConnect(HANDLE *phContext, unsigned char SimSlot, unsigned char *Pin, unsigned char *APN, unsigned char *username,unsigned char *password, unsigned long timeout);

/** Disconnect from GPRS
@param hContext GPRS Context returned by PDA_GPRSConnect
@return returns 0 if success, otherwise see error in ePdaModemError enum*/
int PDA_GPRSDisconnect(HANDLE hContext);

/** Get GPRS Status
@param hContext GPRS Context returned by PDA_GPRSConnect
@param Status pointer to store GPRS Status
@return returns 0 if success, otherwise see error in ePdaModemError enum*/
int PDA_GPRSStatus(HANDLE hContext, unsigned long *Status);

/** SPM_suspend called when receiving suspend request from PDA. This API is used in SPMCI server.
@return returns 0 if success*/
int SPM_suspend( void );

/** SPM_set_settings called when receiving set settings request from PDA. This API is used in SPMCI server.
@param stTimeoutSettings Timeout settings to apply
@return returns 0 if success*/
int SPM_set_settings( Timeout_Settings *stTimeoutSettings);

/** SPM_get_settings called when receiving get settings request from PDA. This API is used in SPMCI server.
@param stTimeoutSettings Structure where to store timeout settings
@return returns 0 if success, */
int SPM_get_settings( Timeout_Settings *stTimeoutSettings);

/** Check if PDA has an external IP link
@return return TRUE if PDA has an external IP connection (GPRS, WLAN, Bluetooth or Ethernet), FALSE instead */
int Is_IP_Available ( void );

/** SPM_get_PDA_power_information called to request power informations from PDA. This API is used in SPMCI client.
@param stPowerInfo Structure where to store PDA power informations
@return returns 0 if success, */
int SPM_get_PDA_power_information( PDA_Power_informations * stPowerInfo);

/** Check if PDA is powered
@return return TRUE if PDA is powered, FALSE otherwise */
int Is_PDA_Powered( void );

/** SPM_set_idle_message called to set SPMCI idle message. This API is used by applications.
 * @param nSize size of the message (set to 0 to disable idle message)
 * @param pucMessage pointer to the new idle message
 * @return returns 0 if success
 *  */
int SPM_set_idle_message(unsigned int nSize, unsigned char *pucMessage);

/** SPM_start_service called when starting SPMCI service. This API is used by applications.
* @return returns 0 if success
*  */
int SPM_start_service(void);

/** SPM_stop_service called when stoping SPMCI service. This API is used by applications.
* @return returns 0 if success
*  */
int SPM_stop_service(void);

//! @}
//! \addtogroup IWP_Only Specific functions only available on the ML30/IPP3xx
//! @{

/** This function will cut the paper of the printer only available on iWP
@param jobId printer job id
@return returns 0 if success, returns 1 if failed */
int PCL_printer_cutPaper (IPA_JOB_ID jobId);

//! @}
//! \addtogroup IMP3xx_Only Specific functions only available on the IMP3xx
//! @{

/** SPM_request_charging called when requesting charging of the attached Apple product. This API is now deprecated. This API is used by applications and is only available on iSMP.
 * @param ucCharging state of the charging request (0=Off (stop the charging), 1=On (start the charging))
 * @return returns 0 if success
 * */
int SPM_request_charging(unsigned char ucCharging);

/** IMP_get_server_state called to get state of Apple Server connection. This API is used by applications and is only available on iSMP.
 * @return returns 0 if product is disconnected, 1 if it's connected
 * */
int IMP_get_server_state( void );

/** Get_ISMP_Connection_State called to get Apple Product connection state. This API is used by applications and is only available on iSMP.
 * @return returns 0 if Apple product is disconnected, 1 if it's present, 2 if it's authenticated and 3 if it's connected to a server
 * */
int Get_ISMP_Connection_State();

//! @}

//! @}

#endif
