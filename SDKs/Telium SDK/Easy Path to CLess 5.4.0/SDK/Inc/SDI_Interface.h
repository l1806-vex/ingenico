/**
 * \file SDI_Interface.h
 * \brief Defines the global interface of the SDI DLL.
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

#ifndef __SDI_INTERFACE_H__INCLUDED__
#define __SDI_INTERFACE_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define ERR_SDI_OK						(0)		//!< No error.
#define ERR_SDI_KO						(1)		//!< Unknown error.


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////



//! \addtogroup IntelligentReaderOverview
//! @{
//!
//!
//! <h2>Presentation</h2><br>
//! Ingenico is creating new intelligent contactless readers (i.e. contactless kernels executed in the card reader itself).
//! The goal of this document is to describe the available services provided by these new devices.
//! 
//! In this document, we will use the "intelligent reader" term to refer to a new intelligent contactless reader (iST150 for example).
//! 
//! The new intelligent reader answers the following needs:
//! - Having good performances to perform quick contactless transactions.
//! - Having capability to easily add new payment schemes and new applications within the card reader.
//! - Being able to connect it to Telium or U32 terminals.
//!
//!
//! <br><h2>Available features</h2><br>
//! - Payment services are available to manage all the payment features in explicit mode (\ref SDI_Payment_DoTransaction(), \ref SDI_Payment_LoadParams(), \ref SDI_Payment_CancelTransaction()...).
//!   This implies a custom application dedicated to payment is present within the intelligent reader (the SDSA application).
//! - All the GUI aspects are managed by the card reader itself (no call-back possible to the terminal for GUI customisation because of performances requirements).
//! - Capability to cancel a transaction that is currently in progress (interruption with a contact card or a merchant abort for example).
//!
//!
//!
//! <br><h2>Global architecture</h2><br>
//! <h3>Global overview</h3><br>
//! The intelligent reader is considered as a slave device. It only acts on commands sent by the terminal (or POS). So, the intelligent reader is not capable to send command to the terminal (or POS).
//! @image html GlobalOverview.png
//! 
//!
//! <br><h3>Intelligent reader software architecture</h3><br>
//! Here is an overview of the software architecture within the intelligent reader (example: iST150 device).
//! @image html ReaderArchitecture.png
//!
//! The intelligent reader contains the following components:
//!	- <b>SDM</b> component is the <b>Reader Protocol</b> and is in charge of :
//!		- Managing the applications within the intelligent reader.
//!		- Receiving and sending frames on intelligent reader.
//!		- Managing all the non applicative commands (system functions for example).
//! - TPass DLL.
//! - One or several <b>Reader Applications</b>. One will be provided by default, being capable of performing payment transactions (called <b>SDSA</b>). This application is provided as a sample in software packages for intelligent reader development.
//! - The standard Telium platform, including OS, Manager, drivers, etc.
//!
//! To perform payment, the different sample applications (<b>SDSA</b>) must use predefined services (please refer to \ref PaymentServices).
//!
//! Please note that ISO1 font file must be loaded in the intelligent reader to display messages. If this file is missing "Mess not found" will be displayed.
//!
//! <br><h3>Telium Terminal architecture</h3><br>
//! Here is an overview of the software architecture within a Telium Terminal in the case of the intelligent reader is connected to a Telium Terminal.
//! @image html TerminalArchitecture.png
//!
//! The Telium terminal contains the following components:
//!  - <b>SDI</b> DLL is the <b>Host Protocol</b> and consists of the interface with the intelligent reader. It contains all the functions necessary to access the intelligent reader features.
//!  - A payment application (<b>CST</b>) that interacts with the intelligent reader (in order to make a payment for example). This is linked with the SDI library. It is in charge of:
//!		- Calling the intelligent reader to perform a payment.
//!		- Perform the online authorisation and contact transactions.
//!		- Managing the batch.
//!		- Etc.
//!	 - The standard Telium platform, including OS, Manager, drivers, etc.
//!
//! Please note that ISO1 font file must be loaded in the terminal to display and print messages. If this file is missing "Mess not found" will be displayed/printed.
//!
//! <br><h3>Telium Software package Easy Pass to Cless</h3><br>
//! The software package contains the following components needed to use the intelligent reader:
//!		- <b>CST</b>: payment application on terminal side. Available in the <b>Easy Path to CLess/Component/Sample for Intelligent Reader/DEMO</b> path.
//!		- <b>SDI</b>: protocol on terminal side. Available in the <b>Easy Path to CLess/Component/Intelligent Reader/Host Protocol</b> path.
//!		- <b>SDM</b>: protocol on intelligent reader side. Available in the <b>Easy Path to CLess/Component/Intelligent Reader/Reader Protocol</b> path.
//!		- <b>SDSA</b>: payment application on intelligent reader side. Available in the <b>Easy Path to CLess/Component/Intelligent Reader/Reader Application</b> path.
//!
//!
//! <br><h3>U32 Terminal architecture</h3><br>
//!	Please refer to the specific U32 pack for more documentation.
//!
//! <br><h3>POS architecture</h3><br>
//! Here is an overview of the software architecture within a POS in the case of the intelligent reader is connected to a POS.
//! @image html POSArchitecture.png
//!
//! The POS contains the following components:
//!  - <b>SDI</b> DLL: consists of the interface with the intelligent reader. It contains all the functions necessary to access the intelligent reader features.
//!  - A payment application that interacts with the intelligent reader (in order to make a payment for example). This is linked with the SDI library. It is in charge of:
//!		- Calling the intelligent reader to perform a payment.
//!		- Perform the online authorisation and contact transactions.
//!		- Managing the batch.
//!		- Etc.
//!	 - The standard operating system, drivers, etc.
//!
//!
//!	<br><br>
//! <table cellspacing="5" bgcolor="#FFCCCC" bordercolordark="green" bordercolorlight="yellow">
//! <tr><td>
//! Restriction : <b>Only one application can use the SDI DLL</b> (i.e. several applications cannot access the intelligent reader).
//! </td></tr>
//! </table>
//!
//! @}


//! \addtogroup SDI_Overview
//! @{
//! <h2>Interface usage</h2><br>
//!
//! The SDI DLL provides functions to drive the intelligent reader (\ref SDI_InterfaceFunctions). There are two kinds of functions:
//!  - Synchronous (blocking) functions.
//!  - Asynchronous (non-blocking) functions.
//!
//! Note: It is <b>not allowed to send two asynchronous commands at the same time</b> (for example \ref SDI_Payment_DoTransaction() cannot be sent if a transaction is already in progress (transaction result not yet received)).
//! However, it is possible to send a cancel command (\ref SDI_Payment_CancelTransaction()) when a transaction is in progress.
//! If two Payment commands or two System commands are sent at the same time, the second call will returns \ref SDI_STATUS_NOT_ALLOWED.
//!
//! Here is described the mechanism used for asynchronous functionalities:
//!  - The CST application (the caller) gives an event to be notified when the response has been received.
//!  - \ref SDI_STATUS_ANSWER_NOT_YET_RECEIVED is returned by the SDI DLL when something happened on the link (USB or serial link) but the answer was not yet received. In this case, the CST application continues to wait.
//!
//! @image html Asynchronous.png
//!
//! Here is an example of an asynchronous call (DoTransaction) cancelled by the user (red key is pressed).
//! 
//! View from CST side, the \ref SDI_Payment_DoTransaction() function is an asynchronous function (for example, we can wait for a user interruption (CANCEL) during the execution of the transaction).
//! When SDSA application is called to perform a transaction, it is a synchronous processus that can be stopped by an event (CANCEL).
//! If the CST application aborts the transaction (\ref SDI_Payment_CancelTransaction() function), the SDSA will be called in a second task that will then send an event to the first task to stop the DoTransaction processing.
//! 
//! @image html AsynchronousCancel.png
//! @}


//! \addtogroup DE_mechanism
//! @{
//! <h2>Introduction</h2><br>
//!
//! PayPass 3 kernel specifies a way to exchange data between the kernel and the payment application during the transaction processing. This mechanism is called the Data Exchange.
//! If you need more information about Data Exchange mechanism (i.e. interaction between the payment application and the kernel), please refer to the PayPass 3 kernel documentation.
//! The explanations below just indicates how you can extend the Data Exchange communication from the kernel to your application within the terminal (if necessary), through 
//! the payment application located in the intelligent reader (SDSA). So, we consider that the SDSA application correctly interface the PayPass 3 kernel to manage the Data Exchange mechanism.
//! So, the SDSA sample provided within this package has been updated to be able to extend the communication for Data Exchange with the custom application within the terminal (CST).
//!
//! <h2>Simple case</h2><br>
//!
//! If a DEK is sent, then it means that the kernel will call the application on the DE service call. On the service call return, the application can either send a DET, or no DET (if necessary).
//! So, Note the return of the ServiceCall from the kernel can be a DET if the payment application provides the appropriate data into. If no data, it is just a return.
//! <h3>Classic application</h3><br>
//! @image html PayPassDeServiceCallDek.png
//!
//! <h3>How it works with CST/SDSA applications</h3><br>
//! @image html PayPassDeServiceCallDekCSTSDSA.png
//!
//! If a DEK is sent, then it means that the kernel will call the SDSA application on the DE service call. Then the analyse of the DEK will be done on the CST side.
//! After this analysis, the CST application will call the \ref SDI_DataExchange_GetDEK() function to be notified if another DEK signal is received from the kernel.
//! On the \ref SDI_DataExchange_GetDEK() function call, the CST application can either ask to send a DET (resulting from the received DEK), or no DET.
//! The SDSA will check the presence of the \ref TAG_SDSA_DEKDET_DATA tag in the input data. On the DE service call return, the SDSA can either send a DET, or no DET (if \ref TAG_SDSA_DEKDET_DATA not present).<br>
//! So, note the return of the ServiceCall from the kernel can be a DET if the payment application provides the appropriate data into. If no data, it is just a return.
//!
//! When the CST application initiates a transaction using the \ref SDI_Payment_DoTransaction() function, it must also:
//! 	- Call the \ref SDI_DataExchange_GetDEK() function to be notified when the SDSA application receives a DEK signal from the PayPass kernel.<br>
//!		  -> The SDSA must declare the \ref SERVICE_DATA_EXCHANGE_GET_DEK_START service.
//!		- When the SDSA receives a DEK signal, the DEK data received from the PayPass kernel are copied in the output of the \ref SERVICE_DATA_EXCHANGE_GET_DEK_START service and the SDI will notify the CST application that DEK data can be retrieved throught the \ref SDI_DataExchange_GetDEKResult() function.
//! 	- Call the \ref SDI_DataExchange_GetDEKResult() function when it receives a notification.
//!		- Analyse DEK data contained in \ref TAG_SDSA_DEKDET_DATA tag.
//! 	- Call again the \ref SDI_DataExchange_GetDEK() function to be notified when the SDSA application receives a new DEK signal from the PayPass kernel.<br>
//!		  This second call contains the DET data (if necessary) in the \ref TAG_SDSA_DEKDET_DATA tag.
//!		- Call the \ref SDI_DataExchange_GetDEKStop() function when the transaction is terminated to stop the retrieval of DEK signals on SDSA side.<br>
//!		  -> The SDSA must declare the \ref SERVICE_DATA_EXCHANGE_GET_DEK_STOP service.
//!
//! \note When the SDSA receives a DEK signal, it will be called in the context of the task in the kernel. The application does not need to create an additional task.
//!
//! <h2>Complex case</h2><br>
//!
//! In some cases, it would be necessary for the application to send several DET for a single DEK. In this case, there is an additional kernel service, available for the application, to send these additional DETs.
//! Please refer to PayPass3_DETSignal function for more information.
//! <h3>Classic application</h3><br>
//! @image html PayPassDeServiceCallDekWithDets.png
//!
//! <h3>How it works with CST/SDSA applications</h3><br>
//! @image html PayPassDeServiceCallDekWithDetsCSTSDSA.png
//!
//! If several DET must be sent for a single DET, the CST application must call the \ref SDI_DataExchange_SendDET() function to send the first DETs (\ref TAG_SDSA_DEKDET_DATA tag will contain DET data).<br>
//! -> The SDSA must declare the \ref SERVICE_DATA_EXCHANGE_SEND_DET service.<br>
//! The last DET will then be sent through the next call of the \ref SDI_DataExchange_GetDEK() function.
//!
//! <h2>Synchronisation at the end of the transaction</h2><br>
//!
//! When the kernel has completed its processing and the payment application has not gave hand back yet to the kernel on the DEK ServiceCall, then the kernel will signal the application it shall respond on the ServiceCall.<br>
//!
//! <h3>Classic application</h3><br>
//! @image html PayPassDeSynchronisation.png
//!
//! <h3>How it works with CST/SDSA applications</h3><br>
//! @image html PayPassDeSynchronisationCSTSDSA.png
//!
//! When the CST application initiates a transaction using the \ref SDI_Payment_DoTransaction() function, it must also:
//! 	- Create a task that will call the \ref SDI_DataExchange_IsCancel() function to be notified when the SDSA application receives a request from the PayPass kernel to stop Data Exchange processing.<br>
//!		  -> The SDSA must declare the \ref SERVICE_DATA_EXCHANGE_IS_CANCEL_START service.
//! 	- Call the \ref SDI_DataExchange_GetIsCancelResult() function when it receives a notification.
//!		- Stop Data Exchange processing and give hand back to the kernel: the CST call the \ref SDI_DataExchange_GetDEK() function.
//!		- Call the \ref SDI_DataExchange_IsCancelStop() function when the transaction is terminated to indicate that the SDSA can stop waiting for a cancellation from the PayPass kernel.<br>
//!		  -> The SDSA must declare the \ref SERVICE_DATA_EXCHANGE_IS_CANCEL_STOP service.
//!
//! <h2>Examples</h2><br>
//!
//! The SDSA is asked by the CST to wait for DEK event from the kernel.
//! \code
//! // This task is created when the SDSA is called on SERVICE_DATA_EXCHANGE_GET_DEK_START service.
//! int SDSA_DataExchange_GetDEK (const TLV_TREE_NODE hInputTlvTree, TLV_TREE_NODE hOutputTlvTree)
//! {
//!		// Here we are waiting an event from the Data Exchange task 
//!		ttestall (USER_EVENT_DEK_DET, 0);
//!		// Consider that the pDataStruct (T_SHARED_DATA_STRUCT * pDataStruct) is the structure sent by the PayPass kernel and that contains DEK data.
//!		// The DEK data are copied in the output that will be retrieved using the SDI_DataExchange_GetDEKResult() function.
//!		TlvTree_AddChild (hOutputTlvTree, TAG_SDSA_DEKDET_DATA, pDataStruct->nPtrData, pDataStruct->ulDataLength);
//!		return (SDI_STATUS_OK);
//! }
//! \endcode
//! 
//! On CST side, when the notification of a DEK is received, the \ref SDI_DataExchange_GetDEKResult() function is called and then DEK data are analysed.
//! \code
//! #define nSDSAAppliId	0x0123
//! TLV_TREE_NODE hDEKNode, hTlvTreeInDEKDET;
//! T_SHARED_DATA_STRUCT *pDEKDataStruct;
//! ...
//! // Ask to be notified when a DEK signal is received
//! if(SDI_DataExchange_GetDEK (nSDSAAppliId, hTlvTreeInDEKDET, E_USER_EVENT_DEKDET) == SDI_STATUS_OK)
//! {
//! 	// Wait for notification
//! 	ttestall(USER_EVENT_DEKDET, 0);
//! 	// Get DEK data
//! 	if(SDI_DataExchange_GetDEKResult(&hTlvTreeOutDEKDET) == SDI_STATUS_OK)
//! 	{
//! 		// Allocate memory to copy the DEK data received
//! 		pDEKDataStruct = GTL_SharedExchange_InitLocal(2048);
//! 		if(pDEKDataStruct != NULL)
//! 		{
//! 			// Get the DEK data sent by the SDSA application.
//! 			hDEKNode = TlvTree_Find(hTlvTreeOutDEKDET, TAG_SDSA_DEKDET_DATA, 0);
//! 			if (hDEKNode != NULL)
//! 			{
//! 				// Copy the DEK data received from the SDSA application
//! 				pDEKDataStruct->ulDataLength = TlvTree_GetLength(hDEKNode);
//! 				memcpy(pDEKDataStruct->nPtrData, TlvTree_GetData(hDEKNode), TlvTree_GetLength(hDEKNode));
//! 				...
//! 				// Analyse DEK data and send DET needed
//! 			}
//! 		}
//! 	}
//! }
//! \endcode
//! 
//!
//! See \ref SDI_Overview for more details about asynchronous functions.
//! 
//! @}





//! \addtogroup SDI_GeneralApi
//! @{

//! \brief Load the SDI DLL.
//! \return The return value of the ObjectLoad function. 0 is successull.

int SDIlib_open(void);


//! \brief Unload the SDI DLL.

void SDIlib_close(void);

//! @}

#endif // __SDI_INTERFACE_H__INCLUDED__
