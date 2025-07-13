/**
 * \file SDI_Download.h
 * \brief Defines the interface of the download services.
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

#ifndef __SDI_DOWNLOAD_H__INCLUDED__
#define __SDI_DOWNLOAD_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup SDI_Download_InterfaceFunctions
//! @{

//! \brief Download session handle.
typedef struct T_SDI_DOWNLOAD_CONTEXT* SDI_DOWNLOAD_HANDLE;

//! \brief Download link.
typedef enum
{
	SDI_LINK_NOT_SET,  /*!< No download link set. */
	SDI_LINK_ETHERNET, /*!< IP download on Ethernet. */
	SDI_LINK_GPRS,     /*!< IP download on GPRS. */
	SDI_LINK_WIFI,     /*!< IP download on Wifi. */
	SDI_LINK_PSTN,     /*!< PSTN download. */
	SDI_LINK_PSTN_X25  /*!< PSTN/X25 download. */
}T_SDI_DOWNLOAD_LINK;

//! \brief Download options.
typedef enum
{
	// Common configuration.
	SDI_DOWNLOAD_LINK,   /*!< Physical link used for the download (\ref T_SDI_DOWNLOAD_LINK). Mandatory. */
	SDI_RPC_CHANNEL,     /*!< RPC channel to use ("COM0" or "USB", like in \ref SDI_System_Connect()). If not set, it uses the value set in the last successful call to \ref SDI_System_Connect(). */

	// TMS common parameters.
	SDI_CONTRACT_NUMBER, /*!< TMS contract number (zero terminated ASCII string). Mandatory. */
	SDI_SOFTWARE_NUMBER, /*!< TMS software number (zero terminated ASCII string). Optionnal. */
	
	// IP parameters.
	SDI_IP_ADDRESS,      /*!< TCP/IP server address (zero terminated ASCII string). Mandatory for IP download. */
	SDI_IP_PORT,         /*!< TCP/IP server port (unsigned short). Mandatory for IP download. */
	SDI_IP_SSL_PROFILE,  /*!< SSL profile (zero terminated ASCII string). Optionnal. */

	// PSTN and X25 parameters.
	SDI_PHONE_NUMBER,    /*!< PSTN phone number (zero terminated ASCII string). Mandatory for both PSTN and X25 download. */
	SDI_X25_ADDRESS      /*!< X25 address (zero terminated ASCII string). Mandatory for X25 download. */
}T_SDI_DOWNLOAD_OPTION;

//! \brief Instantiate a download session.
//! \param[out] pSession Download session handle.
//! \return
//! - \ref SDI_STATUS_OK : if the download session was successfully created.
//! - \ref SDI_STATUS_NOT_ENOUGH_MEMORY : if there is not enough memory to allocate the session.

int SDI_Download_Create( SDI_DOWNLOAD_HANDLE* pSession );

//! \brief Destroy a download session.
//! \param[in] hSession Download session handle.
//! \return
//! - \ref SDI_STATUS_OK : if the download session was successfully destroyed.
//! - \ref SDI_STATUS_INVALID_PARAMETER : if the handle given is not correct.

int SDI_Download_Destroy( SDI_DOWNLOAD_HANDLE hSession );

//! \brief Set an option on a download session.
//! \param[in] hSession Download session handle.
//! \param[in] eOption  Download option.
//! \param[in] pOption  Option's value.
//! \return
//! - \ref SDI_STATUS_OK : if the option was successfully set.
//! - \ref SDI_STATUS_INVALID_PARAMETER : if the handle or the option given is not correct.

int SDI_Download_SetOption( SDI_DOWNLOAD_HANDLE hSession, T_SDI_DOWNLOAD_OPTION eOption, const void* pOption );

//! \brief Start a download session.
//! This function must be called after having switched to maintenance mode (\ref SDI_Maintenance_Start()) and disconnected the SDI facility (\ref SDI_System_Disconnect()).
//! \param[in]  hSession Download session handle.
//! \param[out] pStatus  Will contain the download status.
//! \return
//! - \ref SDI_STATUS_OK : if the download was successfully performed.
//! - \ref SDI_STATUS_KO : if the download failed.
//! - \ref SDI_STATUS_INVALID_PARAMETER : if the handle given or the session's parameters is/are not correct.
//! - \ref SDI_STATUS_DISCONNECTED : if the intelligent reader is not connected, or has not answered correctly.

int SDI_Download_Start( SDI_DOWNLOAD_HANDLE hSession, int* pStatus );

//! @}

#endif // __SDI_DOWNLOAD_H__INCLUDED__
