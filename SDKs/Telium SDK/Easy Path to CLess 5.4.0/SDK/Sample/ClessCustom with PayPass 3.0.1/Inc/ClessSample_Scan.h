/**
 * \file	ClessSample_Scan.h
 * \brief	Contains several common functions.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2008 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 */

#ifndef __CLESS_SAMPLE_SCAN_H__INCLUDED__
#define __CLESS_SAMPLE_SCAN_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define E_USER_EVENT_CANCEL_UNATTENDED_UCMC		27											//!< User event bit for cancel with COM0 (unattended with UCMC).
#define USER_EVENT_CANCEL_UNATTENDED_UCMC		(1 << E_USER_EVENT_CANCEL_UNATTENDED_UCMC)	//!< Cancel event.

#define E_USER_EVENT_CANCEL						28								//!< User event bit for cancel.
#define USER_EVENT_CANCEL						(1 << E_USER_EVENT_CANCEL)		//!< Cancel event.

#define E_USER_EVENT_PIN						29								//!< User event offset.
#define USER_EVENT_PIN     						1 << E_USER_EVENT_PIN  			//!< User event.

#define E_USER_EVENT							30								//!< User event offset.
#define USER_EVENT								1 << E_USER_EVENT				//!< User event.

#define E_USER_EVENT_START						31								//!< User event offset.
#define USER_EVENT_START						1 << E_USER_EVENT_START			//!< User event.


#define SCAN_CANCEL_KEYBOARD					(0x01)							//!< Indicates to use keyboard to cancel the transaction.
#define SCAN_CANCEL_CAM0						(0x02)							//!< Indicates to use CAM0 to cancel the transaction.
#define SCAN_CANCEL_SWIPE						(0x04)							//!< Indicates to use SWIPE to cancel the transaction.
#define SCAN_CANCEL_ALL_INTERFACES				(0xFF)							//!< Indicates to use all the interfaces for cancel (SWIPE, CAM0 and KEYBOARD).


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

extern word g_ScanningTask;						// To store the different tasks ID.
extern t_topstack * g_tsScanning_task_handle;	// Handle of the scanning task.
extern int g_ListOfEvent;						// Global variable used by the scanning task to provide the event.


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Start an EMV contact transaction.
//! \param[in] ulAmount Transaction amount.
//! \param[in] nCurrencyCode Transaction currency code.
//! \return
//!	- \a TRUE if EMV contact component correctly called.
//!	- \a FALSE if EMV contact component cannot be called.

int ClessSample_Scan_TransacCam0 (unsigned long ulAmount, int nCurrencyCode);



//! \brief Start an SWIPE transaction.
//! \param[in] ulAmount Transaction amount.
//! \param[in] nCurrencyCode Transaction currency code.
//! \return
//!	- \a TRUE if SWIPE component correctly called.
//!	- \a FALSE if SWIPE component cannot be called.

int ClessSample_Scan_TransacSwipe2 (unsigned long ulAmount, int nCurrencyCode);



//! \brief Launch the scanning task.
//! \param[in] nScannedInterfaces Indicates the interfaces to be used for scanning.
//! \return
//!	- \a TRUE if task correctly launch
//!	- \a FALSE else.

int ClessSample_Scan_LaunchScanningTask (const int nScannedInterfaces);



//! \brief Kill the scanning task.

void ClessSample_Scan_KillScanningTask (void);



//! \brief Open the CAM0 and SWIPE if not already opened.

void ClessSample_Scan_TransacOpenDrivers(void);



//! \brief Close the CAM0 driver.

void ClessSample_Scan_TransacCloseDriversExceptSwipe(void);



//! \brief Close the drivers opened by the application.

void ClessSample_Scan_TransacCloseDrivers(void);



#endif // __CLESS_SAMPLE_SCAN_H__INCLUDED__
