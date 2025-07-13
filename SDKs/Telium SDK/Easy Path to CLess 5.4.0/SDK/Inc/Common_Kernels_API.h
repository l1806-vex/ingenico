/**
 * \file     Common_Kernels_API.h
 * \brief    This describes all the kernel API used by all Contacless kernels.
 *
 *
 * \author    Ingenico
 * \author    Copyright (c) 2008 Ingenico, rue claude Chappe,\n
 *            07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author    Ingenico has intellectual property rights relating to the technology embodied \n
 *            in this software. In particular, and without limitation, these intellectual property rights may\n
 *            include one or more patents.\n
 *            This software is distributed under licenses restricting its use, copying, distribution, and\n
 *            and decompilation. No part of this software may be reproduced in any form by any means\n
 *            without prior written authorization of Ingenico.
 **/

////////////////////////////////////////////////////////////////////////////
// WARNING : HERE MUST BE DECLARED COMMON API FOR ALL CONTACTLESS KERNELS //
////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup Generic_Status
//! @{
#define KERNEL_STATUS_STOPPED_BY_APPLICATION_MASK		0x0080								/*!< Bit to add to the status code to show that treatment has been stopped by application. */

#define KERNEL_STATUS_OK								0x0100								/*!< The function is correctly executed. */
#define KERNEL_STATUS_SERVICE_NOT_AVAILABLE				0x0101								/*!< The kernel to be accessed is not loaded in the terminal. */
#define KERNEL_STATUS_DATABASE_ERROR					0x0102								/*!< A database error occurred. */
#define KERNEL_STATUS_INVALID_INPUT_DATA				0x0103								/*!< One of the provided data is incorrect. */
#define KERNEL_STATUS_NOT_SUPPORTED						0x0104								/*!< The called function is not supported by the kernel. */
#define KERNEL_STATUS_LACK_OF_MEMORY					0x0105								/*!< There is not enough memory to complete the transaction. */
#define KERNEL_STATUS_COMMUNICATION_ERROR				0x0106								/*!< A communication error occurred with the contactless card. */
#define KERNEL_STATUS_MISSING_INPUT_DATA				0x0107								/*!< A mandatory data is missing to perform the transaction. */
#define KERNEL_STATUS_ICC_MISSING_DATA					0x0108								/*!< A mandatory ICC data is missing to perform the transaction. */
#define KERNEL_STATUS_ICC_INVALID_DATA					0x0109								/*!< A data returned by the card is not correctly formatted. */
#define KERNEL_STATUS_ICC_REDUNDANT_DATA				0x010A								/*!< Card returned redundant data. */
#define KERNEL_STATUS_ICC_DATA_FORMAT_ERROR				0x010B								/*!< The card response is not correctly formatted (parsing error, empty response, etc). */
#define KERNEL_STATUS_TERM_MISSING_DATA					0x010C								/*!< A mandatory terminal data is missing to perform the transaction. */
#define KERNEL_STATUS_CARD_BLOCKED						0x010D								/*!< Card is blocked and transaction cannot be performed. */
#define KERNEL_STATUS_APPLICATION_BLOCKED				0x010E								/*!< The application in the card is blocked. */
#define KERNEL_STATUS_REMOVE_AID						0x010F								/*!< The AID shall be removed from the candidate list. */
#define KERNEL_STATUS_UNKNOWN_SW						0x0110								/*!< Unexpected response code from the ICC. */
#define KERNEL_STATUS_COND_OF_USE_NOT_SATISFIED			0x0111								/*!< The ICC returned “Conditions of use not satisfied” in the GPO response. */
#define KERNEL_STATUS_OFFLINE_APPROVED					0x0112								/*!< Transaction succeeded and is offline approved. */
#define KERNEL_STATUS_OFFLINE_DECLINED					0x0113								/*!< Transaction is offline declined. */
#define KERNEL_STATUS_ONLINE_AUTHORISATION				0x0114								/*!< Transaction succeeded and needs and online authorisation to be completed. */
#define KERNEL_STATUS_CANCELLED							0x0115								/*!< Transaction has been cancelled. */
#define KERNEL_STATUS_USE_CONTACT_INTERFACE				0x0116								/*!< The transaction has to be conducted over another interface (chip or swipe for example). */
#define KERNEL_STATUS_NOT_ALLOWED						0x0117								/*!< This function cannot be called as no transaction is in process with this kernel or cancellation is not allowed according to the transaction progress. */
#define KERNEL_STATUS_CONTINUE							0x0118								/*!< The transaction flow must continue. */
#define KERNEL_STATUS_SUSPEND							0x0119								/*!< The transaction flow must be stopped. */
#define KERNEL_STATUS_INTERNAL_ERROR					0x011A								/*!< A kernel internal error occured. */
#define KERNEL_STATUS_LIB_INTERFACE_ERROR				0x011B								/*!< An error occured into the kernel interface (linked to the custom application). */
#define KERNEL_STATUS_EXPIRED_CERTIFICATE				0x011C								/*!< The certificate used for Offline data authentication is expired. */
#define KERNEL_STATUS_REVOKED_CERTIFICATE				0x011D								/*!< The certificate used for Offline data authentication is revoked. */
#define KERNEL_STATUS_CARD_UNKNOWN      				0x011E								/*!< The contacless card accessed isn't the same as at the begining of the transaction. This error occurs for a new card presentation as Issuer Script Processing ... */
#define KERNEL_STATUS_MOBILE      				        0x011F								/*!< A mobil phone GPO response has been detected. This error allows to restart a selection application cycle with new user message (for mobil phone) ... */
#define KERNEL_STATUS_UNKNOWN							0x017F								/*!< The status code is unknown (because not yet set in the database). */
//! @}


//! \addtogroup Generic_Macros
//! @{
#define ADD_STEP_INTERRUPTION(step,buffer)	buffer[sizeof(buffer)-1-step/8]+=1<<(step%8)	/*!< Macro to set information on buffer to stop transaction flow on a specific step */
#define ADD_STEP_CUSTOM(step,buffer) 		buffer[sizeof(buffer)-1-step/8]+=1<<(step%8)	/*!< Macro to set information on buffer to custom transaction flow on a specific step. */
//! @}


//! \addtogroup Generic_Debug_Mask
//! @{
#define KERNEL_DEBUG_MASK_TRACES						0x01								/*!< Mask for \a TAG_KERNEL_DEBUG_ACTIVATION tag indicating traces are activated. */
#define KERNEL_DEBUG_MASK_APDU							0x02								/*!< Mask for \a TAG_KERNEL_DEBUG_ACTIVATION tag indicating APDU exchanged between card and reader are stored or not in the database. */
#define KERNEL_DEBUG_MASK_TIMERS						0x04								/*!< Mask for \a TAG_KERNEL_DEBUG_ACTIVATION tag indicating time measurements are activated. */
#define KERNEL_DEBUG_KERNEL_SPECIFIC_1					0x40								/*!< Mask for \a TAG_KERNEL_DEBUG_ACTIVATION tag used specifically by the kernel for specific debug processing. Please refer to the corresponding kernel to see debug processing linked to this bit. */
#define KERNEL_DEBUG_KERNEL_SPECIFIC_2					0x80								/*!< Mask for \a TAG_KERNEL_DEBUG_ACTIVATION tag used specifically by the kernel for specific debug processing. Please refer to the corresponding kernel to see debug processing linked to this bit. */
//! @}


/////////////////////////////////////////////////////////////////
//// Types definitions //////////////////////////////////////////

//! \addtogroup Generic_Structures
//! @{

//! \brief This structure defines times measured ans stored by kernel. 
typedef struct
{
	unsigned long m_ulCounterId;            							/*!< Time type and counter Id. Note this information depends on the kernel. */
	unsigned long m_ulTime;		            							/*!< Time value. Note this information depends on the kernel. */
} T_KERNEL_TIME_MEASURE;


//! \brief This structure defines parameters used to customise steps of transaction flow. 
typedef struct
{
	unsigned char pucStepCustom[KERNEL_PAYMENT_FLOW_CUSTOM_LENGTH]; 	/*!< Transaction flow bits field. */
	unsigned short usApplicationType;	            					/*!< Application type to call to perform customisation. */
	unsigned short usServiceId; 		            					/*!< Service Id to call to perform customisation. */
} T_KERNEL_TRANSACTION_FLOW_CUSTOM;

//! @}


/////////////////////////////////////////////////////////////////
//// Glodal Data ////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////
