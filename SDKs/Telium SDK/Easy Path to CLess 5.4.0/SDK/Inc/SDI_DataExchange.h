/**
 * \file SDI_DataExchange.h
 * \brief Defines the interface of Data Exchange services.
 *
 *
 * \author	Ingenico France
 * \author	Copyright (c) 2010 Ingenico France, 1 rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico France has intellectual property rights relating to the technology embodied\n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico France.
 **/

#ifndef __SDI_DATA_EXCHANGE_H__INCLUDED__
#define __SDI_DATA_EXCHANGE_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


//! \addtogroup SDI_DataExchange_InterfaceFunctions
//! @{

//! \brief Request an application to indicate the caller when a DEK signal has been received. 
//! DEK data are returned as function output (DEK output can be retrieved with \ref SDI_DataExchange_GetDEKResult() function). 
//! Note this command can be interrupted using the SDI_DataExchange_GetDEKStop() function.
//! This function is asynchronous, non-blocking. A notification is sent to the caller to indicate the Get DEK processing is completed.
//! \param[in] nAppliId Identifies the application to which the call is for. 
//! \param[in] hTlvTreeIn Empty if it is the first call, else contains the data that are necessary to perform the last DET signal (\ref TAG_SDSA_DEKDET_DATA).In some cases, it would be necessary for the application to send several DET for a single DEK.
//! For example if three DET signals correspond to the received DEK signal, the first two DET signals will be sent with \ref SDI_DataExchange_SendDET() function and the third will be sent using the \ref SDI_DataExchange_GetDEK() (DET data will be included in the input data of the next call).
//! Then the intelligent reader will continue to wait for DEK signals from the kernel.
//! If no matching DEK Signal is found, the reader must send a CANCEL to the kernel. In this case, the \ref TAG_SDSA_SEND_CANCEL tag is added in the Input data.
//! \param[in] nEvent Event identifier, necessary to be notified the response has been received. See \ref SDI_Overview for more details about asynchronous functions.
//! \return
//! - \ref SDI_STATUS_OK : Get DEK processing has been correctly launched.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a Get DEK is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_DataExchange_GetDEK (const int nAppliId, const TLV_TREE_NODE hTlvTreeIn, const int nEvent);



//! \brief This function is called after the notification related to the \ref SDI_DataExchange_GetDEK() function has been received.
//! It allows retrieving the Get DEK result (DEK signal).
//! Note this function is synchronous, blocking.
//! \param[out] pTlvTreeOut Contains the DEK data received from the kernel (\ref TAG_SDSA_DEKDET_DATA tag).
//! \return
//! - \ref SDI_STATUS_OK : if DEK signal has been correctly retrieved.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_NOT_ALLOWED : if no Get DEK processing has been started.
//! - \ref SDI_STATUS_CANCELLED : if the Get DEK processing has been cancelled.
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier (given in SDI_DataExchange_GetDEK parameters) is not valid or if the application in the intelligent reader does not implement the related service.
//! - \ref SDI_STATUS_ANSWER_NOT_YET_RECEIVED : if the Get DEK processing result is not yet received.

int SDI_DataExchange_GetDEKResult (TLV_TREE_NODE * pTlvTreeOut);



//! \brief Cancel the Get DEK process in progress into the intelligent reader (started using the \ref SDI_DataExchange_GetDEK() functions).
//! Note if the cancellation is taken into account by the application in the intelligent reader, the caller will be notified that the Get DEK process is completed (ie: \ref SDI_STATUS_CANCELLED will be returned by \ref SDI_DataExchange_GetDEKResult() function).
//! This function is synchronous, blocking.
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \return
//! - \ref SDI_STATUS_OK : if cancel command has been correctly sent.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a Cancel is already in progress).
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_NO_OPERATION_IN_PROGRESS : if there is no Get DEK in progress.
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier is not valid or if the application in the intelligent reader does not implement the related service.

int SDI_DataExchange_GetDEKStop (const int nAppliId);



//! \brief Request an application to send a DET signal to the kernel. This feature is necessary if there are several DET signals to be sent.
//! For example if three DET signals correspond to the received DEK signal, the first two DET signals will be sent with \ref SDI_DataExchange_SendDET() function and the third will be sent using the SDI_DataExchange_GetDEK() (DET data will be included in the input data of the next call).
//! Note this function is synchronous, blocking.
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \param[in] hTlvTreeIn Contains the data for the DET signal (\ref TAG_SDSA_DEKDET_DATA tag).
//! \param[out] pTlvTreeOut Empty.
//! \return
//! - \ref SDI_STATUS_OK : if the DET signal has been correctly sent.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a Get DEK is in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier is not valid or if the application in the intelligent reader does not implement the related service.

int SDI_DataExchange_SendDET (const int nAppliId, const TLV_TREE_NODE hTlvTreeIn, TLV_TREE_NODE * pTlvTreeOut);



//! \brief Request an application to indicate the caller when the kernel requests to stop the Data Exchange processing.
//! Note this function is asynchronous, non-blocking. A notification is sent to the caller to indicate the processing is completed (Data Exchange processing must be cancelled).
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \param[in] hTlvTreeIn Empty.
//! \param[in] nEvent Event identifier, necessary to be notified the response has been received. See \ref SDI_Overview for more details about asynchronous functions.
//! \return
//! - \ref SDI_STATUS_OK : if Is Cancel checking correctly started.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (for example a Is Cancel processing is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_DataExchange_IsCancel (const int nAppliId, const TLV_TREE_NODE hTlvTreeIn, const int nEvent);



//! \brief Stop the asynchronous call started with the \ref SDI_DataExchange_IsCancel() function.
//! Note this function is synchronous, blocking.
//! \param[in] nAppliId Identifies the application to which the call is for.
//! \return
//! - \ref SDI_STATUS_OK : if the asynchronous function correctly stopped.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a Is Cancel Stop is already in progress).
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_BUSY : if a Is Cancel is already launched with another application, so cancellation is not possible.
//! - \ref SDI_STATUS_NO_OPERATION_IN_PROGRESS : if there is no status checking in progress.
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier is not valid or if the application in the intelligent reader does not implement the related service.

int SDI_DataExchange_IsCancelStop (const int nAppliId);



//! \brief This function is called when a notification has been received following the call of \ref SDI_DataExchange_IsCancel() function.
//! Note this function is synchronous, blocking.
//! \param[out] pTlvTreeOut Empty.
//! \return
//! - \ref SDI_STATUS_OK : if the Is Cancel processing is correctly performed and the Data Exchange processing must be stopped.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_NOT_ALLOWED : if there is no Is Cancel checking in progress.
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_CANCELLED : if the process has been cancelled using the \ref SDI_DataExchange_IsCancelStop() function.
//! - \ref SDI_STATUS_ANSWER_NOT_YET_RECEIVED : if the Is Cancel result is not yet received.
//! - \ref SDI_STATUS_UNKNOWN_SERVICE : if application identifier (given in SDI_DataExchange_IsCancel parameters) is not valid or if the application in the intelligent reader does not implement the related service.

int SDI_DataExchange_GetIsCancelResult (TLV_TREE_NODE * pTlvTreeOut);


//! @}

#endif // __SDI_DATA_EXCHANGE_H__INCLUDED__
