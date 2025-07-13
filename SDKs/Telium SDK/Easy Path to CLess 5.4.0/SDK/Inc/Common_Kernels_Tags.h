/**
 * \file     Common_Kernels_Tags.h
 * \brief    This describes all the tags used by all Contacless kernels.
 *
 *
 * \author    Ingenico
 * \author    Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *            07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author    Ingenico has intellectual property rights relating to the technology embodied \n
 *            in this software. In particular, and without limitation, these intellectual property rights may\n
 *            include one or more patents.\n
 *            This software is distributed under licenses restricting its use, copying, distribution, and\n
 *            and decompilation. No part of this software may be reproduced in any form by any means\n
 *            without prior written authorization of Ingenico.
 **/

/////////////////////////////////////////////////////////////////////////////
// WARNING : HERE MUST BE DECLARED COMMON TAGS FOR ALL CONTACTLESS KERNELS //
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup Generic_Tags
//! @{

#define TAG_KERNEL_PAYMENT_FLOW_STOP	                        0x9F918400          /*!< Indicates the steps on which the kernel shall stop the processing and give hand back to the custom application. If the transaction is stopped, it can be resumed using the correct kernel API function (if available).<br>	- Format : b.<br>	- Length : 32 bytes.<br>	- Source : Terminal. */
#define KERNEL_PAYMENT_FLOW_STOP_LENGTH    	                    0x20				/*!< Length of \ref TAG_KERNEL_PAYMENT_FLOW_STOP. */

#define TAG_KERNEL_PAYMENT_FLOW_CUSTOM	                        0x9F918401          /*!< Indicates the steps on which the kernel shall call the curstom application for step customisation (value is a \ref T_KERNEL_TRANSACTION_FLOW_CUSTOM structure).<br>	- Format : b.<br>	- Length : 36 bytes.<br>	- Source : Terminal. */
#define KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH  	                    0x20				/*!< Length of the bit field within \ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM. */

#define TAG_KERNEL_DEBUG_ACTIVATION                             0x9F918402          /*!< Indicates the kernel debug mode (tag sent on the kernel debug API function, if available). The value is a bit field using the bit defined in \ref Generic_Debug_Mask.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define KERNEL_DEBUG_ACTIVATION_LENGTH    	                    0x01				/*!< Length of \ref TAG_KERNEL_DEBUG_ACTIVATION. */

#define TAG_KERNEL_DEBUG_TIME                                   0x9F918403          /*!< Indicates the time measures in debug mode only, depending on the kernel (active measures of steps, cards access, ...). This is a concatenation of \ref T_KERNEL_TIME_MEASURE structures.<br>	- Format : b.<br>	- Length : up to 256 bytes.<br>	- Source : Terminal. */
#define KERNEL_DEBUG_TIME_LENGTH    	                        0x100				/*!< Maximum length of \ref TAG_KERNEL_DEBUG_TIME. */

#define TAG_KERNEL_AUTOMAT_STATE                                0x9F918404          /*!< Indicates an automat transaction step.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define KERNEL_AUTOMAT_STATE_LENGTH                             0x01				/*!< Length of \ref TAG_KERNEL_AUTOMAT_STATE. */

#define TAG_KERNEL_PROPRIETARY_TAGS                             0x9F918405          /*!< Contains the proprietary tags definition. This is a concatenation of \a T_TI_TAG_INFO structure (refer to \a GTL documentation for more information about this structure). Each of them describes a proprietary tag.<br>Note the tag list shall be arranged using ascending order.<br>When sent to the kernel (if supported), a proprietary database is created accordingly to the tag value.<br>	- Format : b.<br>	- Length : up to 768 bytes.<br>	- Source : Terminal. */
#define KERNEL_PROPRIETARY_TAGS_LENGTH                          0x300				/*!< Maximum length of \ref TAG_KERNEL_PROPRIETARY_TAGS. */

#define TAG_KERNEL_TRACE_ERROR                                  0x9F918406          /*!< Indicates the different errors that occured during the transaction. This is a concatenation of error code. The error code on lower adress is the first error occured. Each error code (on 8 bytes) is coding as following :<br>	- Error code identifier as described in each kernel (4 bytes).<br>	- tag concerned by the error (4 bytes) (if applicable) or 0xFFFFFFFF if no applicable tag.<br>	- Format : b.<br>	- Maximum buffer length : up to 128 bytes.<br>	- Source : Terminal. */
#define KERNEL_TRACE_ERROR_LENGTH                               0x80				/*!< Maximum length of \ref TAG_KERNEL_TRACE_ERROR (i.e. mawimum of 16 error codes). */

#define TAG_KERNEL_STATUS_CODE                                  0x9F918407          /*!< Indicates the kernel status code. Please refer to \ref Generic_Status for possible status codes.<br>Note there would exist specific kernel status codes. Refer to kernel documentation for more information.<br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Terminal. */
#define KERNEL_STATUS_CODE_LENGTH                               0x02				/*!< Length of \ref TAG_KERNEL_STATUS_CODE. */

#define TAG_KERNEL_CUSTOM_STEP                                  0x9F918408          /*!< Indicates the customisation step on which the ustom application has requested to be called (using \ref TAG_KERNEL_PAYMENT_FLOW_CUSTOM tag).<br>Customisation step corresponds to a kernel transaction step after which the customisation has been requested.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define KERNEL_CUSTOM_STEP_LENGTH                               0x01				/*!< Length of \ref TAG_KERNEL_CUSTOM_STEP. */

#define TAG_KERNEL_APPLICATION_NAME                             0x9F918409          /*!< Indicates the kernel name (when calling the GetInfos kernel API function, if available).<br>	- Format : anp.<br>	- Length : up to 32 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_APPLICATION_IDENT                            0x9F91840A          /*!< Indicates the kernel identifier (when calling the GetInfos kernel API function, if available).<br>	- Format : n.<br>	- Length : 2-5 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_APPLICATION_CRC                              0x9F91840B          /*!< Indicates the kernel CRC (when calling the GetInfos kernel API function, if available).<br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Terminal. */

#define TAG_KERNEL_IPK_RECOVERED_DATA							0x9F91840C			/*!< Data Recovered from the Issuer Public Key Certificate, as defined in EMV Specification 4.2, Book 2, Table 6.<br>	- Format : b.<br>	- Length : up to 248 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_SDA_RECOVERED_DATA							0x9F91840D			/*!< Data Recovered from the SDA, as defined in EMV Specifcation 4.2, Book 2, Table 7.<br>	- Format : b.<br>	- Length : up to 248 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_ICC_RECOVERED_DATA							0x9F91840E			/*!< Data Recovered from the ICC Public Key Certificate, as defined in EMV Specification 4.2, Book 2, Table 14.<br>	- Format : b.<br>	- Length : up to 248 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_DDA_RECOVERED_DATA							0x9F91840F			/*!< Data Recovered from the DDA, as defined in EMV specification, Book 2, Table 17.<br>	- Format : b.<br>	- Length : up to 248 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_IS_CA_REVOKED								0x9F918410			/*!< Indicates if the Certificate Authority public key is revoked or not (\a 1 if CA is revoked, \a 0 or \a not \a present if not revoked).<br>Note this tag can be managed or not depending on the kernel.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_KERNEL_LAST_APDU_AND_SW								0x9F918411			/*!< Indicates the last command sent to the card (CLA/INS/P1/P2) and the status word (SW) provided by the card to this command.<br>	- Format : b.<br>	- Length : 6 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_CUMULATED_AMOUNT								0x9F918412			/*!< Indicates the cumulated amount for the card during the transaction. */
#define TAG_KERNEL_SIGNATURE_REQUESTED							0x9F918413			/*!< Indicates whether a signature is required or not (\a 1 if signature is required, \a 0 or \a not \a present if not required).<br>Note this tag can be managed or not depending on the kernel.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_KERNEL_IS_PINPAD_FUNCTIONING						0x9F918414			/*!< Indicates if the PinPad is functioning or not (\a 1 or \a not \a present if pinpad is functionning, \a 0 if not functioning).<br>Note this tag can be managed or not depending on the kernel.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_KERNEL_PAN_IN_BLACK_LIST							0x9F918415			/*!< Indicates if the Card PAN is in the black list or not (\a 1 if in exception file, \a 0 or \a not \a present if not in exception file). This tag can be provided to th ekernel to indicate if the PAN is present or not in the exception file.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_KERNEL_CARD_TYPE									0x9F918416			/*!< Indicates the card type (value depends on the kernel defines).<br>	- Format : b.<br>	- Length : 2 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_ONLINE_PIN_REQUESTED							0x9F918417			/*!< Indicates if online PIN is requested by the kernel or not (\a 1 if Online PIN is requested, \a 0 or \a not \a present if not).<br>Note this tag can be managed or not depending on the kernel.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define TAG_KERNEL_CONSTRUCTED_TDOL_VALUE 						0x9F918418			/*!< Value of the constructed TDOL (using terminal data).<br>Note this tag can be managed or not depending on the kernel.<br>	- Format : b.<br>	- Length : up to 256 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_CONSTRUCTED_PDOL_VALUE 						0x9F918419			/*!< Value of the constructed PDOL (using terminal data).<br>Note this tag can be managed or not depending on the kernel.<br>	- Format : b.<br>	- Length : up to 256 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_CONSTRUCTED_CDOL1_VALUE						0x9F91841A			/*!< Value of the constructed CDOL1 (using terminal data).<br>Note this tag can be managed or not depending on the kernel.<br>	- Format : b.<br>	- Length : up to 256 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_CONSTRUCTED_CDOL2_VALUE						0x9F91841B			/*!< Value of the constructed CDOL2 (using terminal data).<br>Note this tag can be managed or not depending on the kernel.<br>	- Format : b.<br>	- Length : up to 256 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_CONSTRUCTED_DDOL_VALUE 						0x9F91841C			/*!< Value of the constructed DDOL (using terminal data).<br>Note this tag can be managed or not depending on the kernel.<br>	- Format : b.<br>	- Length : up to 256 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_TERMINAL_SUPPORTED_LANGUAGES					0x9F91841D			/*!< List of languages supported by the terminal (concatenation of languages identifiers : for example "enfrde"). From this tag would be determined the common prefered language (if kernel supports multi-language), stored in the \ref TAG_KERNEL_SELECTED_PREFERED_LANGUAGE tag.<br>	- Format : a.<br>	- Length : up to 64 bytes (maximum of 32 supported languages).<br>	- Source : Terminal. */
#define TAG_KERNEL_SELECTED_PREFERED_LANGUAGE					0x9F91841E			/*!< Language identifier matching between the card and the terminal (as determined by the language selection).<br>	- Format : a.<br>	- Length : 2 bytes.<br>	- Source : Terminal. */
#define TAG_KERNEL_REVOKED_CERTIFICATE_LIST						0x9F91841F			/*!< List of revoked certificates. Each revoked certificate is a concatenation of RID (on 5 bytes), Exponent (on 1 byte) and the serial number (on 3 bytes).<br>	- Format : b.<br>	- Length : up to 288 bytes (maximum of 32 revoked certificates).<br>	- Source : Terminal. */
#define TAG_KERNEL_LAST_EXECUTED_STEP_INTERRUPTION				0x9F918420			/*!< Indicates the last executed step  when interruption or cancellation occurs.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
#define KERNEL_LAST_EXECUTED_STEP_INTERRUPTION_LENGTH			0x01				/*!< Length of \ref TAG_KERNEL_LAST_EXECUTED_STEP_INTERRUPTION. */

#define TAG_KERNEL_TERMINAL_ENTRY_CAPABILITY    				0x9F918421			/*!< Indicates if the contact chip is available.<br>	- Format : b.<br>	- Length : 1 byte.<br>	- Source : Terminal. */
//! @}


/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Glodal Data ////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////
