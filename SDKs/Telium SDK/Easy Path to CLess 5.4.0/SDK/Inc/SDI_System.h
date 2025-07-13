/**
 * \file SDI_System.h
 * \brief Defines the interface of the system services.
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

#ifndef __SDI_SYSTEM_H__INCLUDED__
#define __SDI_SYSTEM_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup SDI_System_InterfaceFunctions
//! @{

//! \brief Get the date configured within the intelligent reader.
//! Note for a given transaction, the date and time of either terminal or either reader can be used. But both shall not be used at the same time (intelligent reader date for transaction and Terminal date for clearing message).
//! This function is synchronous, blocking.
//! \param[out] pDate Contains the configured date (on 6 bytes, format is a string, YYMMDD). Regarding the year, “00” to “49” corresponds to [2000;2049]. “50” to “99” corresponds to [1950;1999].
//! \param[out] pTime Contains the configured time (on 6 bytes, format is a string, HHMMSS).
//! \return
//! - \ref SDI_STATUS_OK : if date correctly got.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_INVALID_DATA : if provided data are not correct (pDate or pTime is null).
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a System process is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_System_GetDateAndTime (unsigned char * pDate, unsigned char * pTime);



//! \brief Set the date within the intelligent reader.
//! Note for a given transaction, the date and time of either terminal or either reader can be used. But both shall not be used at the same time (intelligent reader date for transaction and Terminal date for clearing message).
//! This function is synchronous, blocking.
//! \param[in] pDate Contains the date to be set (on 6 bytes, format is a string, YYMMDD). Regarding the year, “00” to “49” corresponds to [2000;2049]. “50” to “99” corresponds to [1950;1999].
//! \param[in] pTime Contains the time to be set (on 6 bytes, format is a string, HHMMSS).
//! \return
//! - \ref SDI_STATUS_OK : if date correctly set.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_INVALID_DATA : if provided data are not correct.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a System process is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_System_SetDateAndTime (const unsigned char * pDate, const unsigned char * pTime);



//! \brief Get the current language selected within the intelligent reader.
//! This is the language defined for all the applications. But it is possible for an application within the intelligent reader to manage its own language(s) (not managed with this function).
//! Note this function is synchronous, blocking.
//! \param[out] pLanguage Contains the language code according to ISO 639-1 (on 2 bytes. For example: “en” for english).
//! \return
//! - \ref SDI_STATUS_OK : if current language correctly got.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_INVALID_DATA : if provided data is not correct (pLanguage is null).
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a System process is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_System_GetCurrentLanguage (unsigned char * pLanguage);



//! \brief Set the current language within the intelligent reader.
//! Note the required language shall be configured and available within the device. This is the language defined for all the applications. But it is possible for an application within the intelligent reader to manage its own language(s) (not managed with this function).
//! This function is synchronous, blocking.
//! \param[in] pLanguage Contains the language code according to ISO 639-1 (on 2 bytes. For example: “en” for english).
//! \return
//! - \ref SDI_STATUS_OK : if current language correctly set.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_BUSY : if a command cannot be executed because the device is busy.
//! - \ref SDI_STATUS_INVALID_DATA : if provided data in the input structure is not correct.
//! - \ref SDI_STATUS_NOT_SUPPORTED : if the provided language to be used is not supported.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a System process is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_System_SetLanguage (const unsigned char * pLanguage);



//! \brief Get the supported languages within the intelligent reader.
//! This is the languages defined for all the applications. But it is possible for an application within the intelligent reader to manage its own language(s) (not managed with this function).
//! Note this function is synchronous, blocking.
//! \param[in] ulBufferSize Size in bytes of pSupportedLanguages.
//! \param[out] pSupportedLanguages Contains the supported languages code according to ISO 639-1 (up to 24 bytes, the device can support 12 different languages at maximum).
//! \param[out] pNumberOfSupportedLanguages Number of supported languages.
//! \return
//! - \ref SDI_STATUS_OK : if supported languages correctly got.
//! - \ref SDI_STATUS_KO : if an error occurred.
//! - \ref SDI_STATUS_INVALID_DATA if provided data are not correct (pSupportedLanguages or pNumberOfSupportedLanguages is null).
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a System process is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_System_GetSupportedLanguages (unsigned char * pSupportedLanguages, const unsigned long ulBufferSize, unsigned long * pNumberOfSupportedLanguages);



//! \brief Get the intelligent reader software configuration.
//! Note this function is synchronous, blocking.
//! \param[in] nComponentTypes bit field indicating which component information has to be retrieved:
//!		- \ref SDI_SOFT_APPLICATIONS : to get applications information.
//!		- \ref SDI_SOFT_DRIVERS : to get drivers information.
//!		- \ref SDI_SOFT_DLL : to get DLLs information.
//!		- \ref SDI_SOFT_MANAGER : to get the Manager information.
//!		- \ref SDI_SOFT_SYSTEM : to get the System information.
//! \param[out] pSoftwareInfoTree Containing the following data:
//!		- One or several <b>Application</b> structures \ref TAG_SDI_CONFIGURATION_APPLICATION_STRUCTURE containing:
//!			- \ref TAG_SDI_COMPONENT_NAME : Name.
//!			- \ref TAG_SDI_COMPONENT_IDENTIFIER : Identifier.
//!			- \ref TAG_SDI_COMPONENT_CRC : CRC.
//!		- One or several <b>Driver</b> structures \ref TAG_SDI_CONFIGURATION_DRIVER_STRUCTURE containing:
//!			- \ref TAG_SDI_COMPONENT_NAME : Name.
//!			- \ref TAG_SDI_COMPONENT_IDENTIFIER : Identifier.
//!			- \ref TAG_SDI_COMPONENT_CRC : CRC.
//!		- One or several <b>DLL</b> structures \ref TAG_SDI_CONFIGURATION_DLL_STRUCTURE containing:
//!			- \ref TAG_SDI_COMPONENT_NAME : Name.
//!			- \ref TAG_SDI_COMPONENT_IDENTIFIER : Identifier.
//!			- \ref TAG_SDI_COMPONENT_CRC : CRC.
//!		- One <b>Manager</b> structure \ref TAG_SDI_CONFIGURATION_MANAGER_STRUCTURE containing:
//!			- \ref TAG_SDI_COMPONENT_IDENTIFIER : Identifier.
//!			- \ref TAG_SDI_COMPONENT_CRC : CRC.
//!		- One <b>System</b> structure \ref TAG_SDI_CONFIGURATION_SYSTEM_STRUCTURE containing:
//!			- \ref TAG_SDI_COMPONENT_IDENTIFIER : Identifier.
//!			- \ref TAG_SDI_COMPONENT_CRC : CRC.
//! \return
//! - \ref SDI_STATUS_OK : software configuration correctly got.
//! - \ref SDI_STATUS_KO : if an error occurred.
//!	- \ref SDI_STATUS_INVALID_DATA if provided data in the input structure is not correct (pSoftwareInfoTree is null).
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a System process is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_System_GetSoftwareConfiguration (const unsigned int nComponentTypes, TLV_TREE_NODE * pSoftwareInfoTree);



//! \brief Get the device serial number.
//! Note this function is synchronous, blocking.
//! \param[out] pSerialNumber Contains the device serial number (ASCII, on 8 bytes).
//! \return
//! - \ref SDI_STATUS_OK : serial number correctly got.
//! - \ref SDI_STATUS_KO : if an error occurred.
//!	- \ref SDI_STATUS_INVALID_DATA : if provided data in the input data is not correct (pSerialNumber is null).
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a System process is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_System_GetDeviceSerialNumber (unsigned char * pSerialNumber);



//! \brief Establishes the connection with the intelligent reader.
//! Note this function is synchronous, blocking.
//! \param[in] szComDriver Communication port name:
//!		- "COM0": if the serial port is used.
//!		- "USB": if the USB port is used.
//! \return
//! - \ref SDI_STATUS_OK : if the connection is correctly established.
//! - \ref SDI_STATUS_KO : if the connection failed.

int SDI_System_Connect (const char *szComDriver);



//! \brief Closes the intelligent reader connection.
//! Note this function is synchronous, blocking.

void SDI_System_Disconnect (void);



//! \brief Check if the intelligent reader is correctly connected.
//! Note this function is synchronous, blocking.
//! \return
//! - \ref SDI_STATUS_OK : if the intelligent reader is correctly connected.
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a System process is already in progress).
//! - \ref SDI_STATUS_IN_PROGRESS : if the connection is in progress (services are not yet available).

int SDI_System_IsConnected (void);



//! \brief Resets the intelligent reader.
//! Note this is the role of the application to establish the connection again with the intelligent reader using the correct functions.
//! This function is synchronous, blocking.
//! \return
//! - \ref SDI_STATUS_OK : if the reset command has been sent.
//! - \ref SDI_STATUS_NOT_ALLOWED : if the command is not allowed according to the reader state (a System process is already in progress).
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.

int SDI_System_Reset (void);

			 
			 
//! \brief Get the intelligent reader current state.
//! Note if card detection has been performed using transparent command and the detection result has been received, the contactless field is opened, but there is no operation in progress. In this case, the reader is considered in idle.
//! This function is synchronous, blocking.
//! \param[out] pState Intelligent reader state:
//!		- \ref SDI_STATE_IDLE : reader is in idle state.
//!		- \ref SDI_STATE_SYSTEM : if system function is currently in progress (SetDate, SetLanguage...) .
//!		- \ref SDI_STATE_APPLICATION_MODE : if application processing is currently in progress.
//! \return
//!	- \ref SDI_STATUS_OK : if the state correctly got.
//!	- \ref SDI_STATUS_KO : if an error occurred.
//!	- \ref SDI_STATUS_INVALID_DATA : if provided data in the input data is not correct (pState is null).
//!	- \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected.
		 
int SDI_System_GetState (unsigned int * pState);

//! @}

#endif // __SDI_SYSTEM_H__INCLUDED__
