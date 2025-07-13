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
/* Module Name: ipa280_type.h                                                 */
/*                                                                            */
/* Function:    Application definitions of used type in ipa280                */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/*============================================================================*/
/* usr | yy-mm-dd |                                        |                  */
/* ewc | 09-06-12 | New for IPA280                         |                  */
/******************************************************************************/

#ifndef _IPA280_TYPE_H_
#define _IPA280_TYPE_H_

#if !defined(WIN32) && !defined(WINCE)
#include <sdk30.h>
#endif
#include "ipa280_def.h"

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef ushort
#define ushort unsigned short
#endif

#ifndef uint
#define uint unsigned int
#endif

#ifndef ulong
#define ulong unsigned long
#endif

#ifndef HANDLE
typedef void *HANDLE;
#endif

//! \brief Transaction Request structure.
typedef struct {
	ushort us_pos_number; //!< Pos number.
	ulong ul_amount; //!< Amount.
	uchar uc_specific_resp; //!< Presence of a specific field.
	uchar uc_account_type; //!< Account type.
	uchar uc_transaction_type; //!< Transaction type.
	uchar pc_currency[3]; //!< code of the money.
	char pc_private_data[10]; //!< Private data.
	uchar uc_delay; //!< Delay.
	uchar uc_authorization_type; //!< autorization type.
} T_ReqTransaction;

//! \brief Transaction Response structure.
typedef struct {
	ushort us_pos_number; //!< Pos number.
	uchar uc_operation_status; //!< Operation status.
	ulong ul_amount; //!< Real amount used for transaction.
	uchar uc_account_type; //!< Account type used for transaction.
	uchar pc_currency[3]; //!< code of the money.
	char pc_private_data[10]; //!< Private data.
	char pc_pan[19]; //!< Promary Account Number.
	char pc_card_validity[4]; //!< Card validity date.
	char pc_authorization_number[9]; //!< Autorization number.
	char pc_cmc7_track[35]; //!< CMC7 track.
	char pc_iso2_track[38]; //!< ISO2 track.
	char pc_fnci[10]; //!< FNCI.
	char pc_garantisseur[10]; //!< Garantisseur.
	char pc_zone_rep[55]; //!< Response of the cash register connection.
	char pc_zone_priv[10]; //!< Define a private area.
} T_RespTransaction;

//! \brief Transaction structure.
typedef struct {
	T_ReqTransaction t_req; //!< Transaction request structure.
	T_RespTransaction t_resp; //!< Transaction response structure.
} T_Transaction;

//! \brief SPM Information structure.
typedef struct {
	uint ui_serial_number; //!< SPM serial number.
	uint ui_sap_product_number; //!< SAP product number.
} T_SPMInformation;

//! \brief PDA peripheral state structure.
typedef struct {
	uchar uc_gprs_status; //!< PDA GPRS status.
	uchar pc_gprs_mac_address[6]; //!< GPRS MAC Address
	uchar pc_gprs_sim_id[20]; //!< GPRS Sim Id
	uchar uc_wlan_status; //!< PDA WLAN status.
	uchar pc_wlan_mac_address[6]; //!< WLAN MAC Address
	uchar uc_bluetooth_status; //!< PDA BLUETOOTH status.
	uchar pc_bluetooth_mac_address[6];//!< BLUETOOTH MAC Address
	uchar uc_lan_status; //!< PDA LAN status.
	uchar pc_lan_mac_address[6]; //!< LAN MAC Address
} T_PDAPeripheralState;

//#ifndef _WIN32_WCE
//#warning "The structure T_Signature contains an array of 58Ko. Do not allocate it on the stack and use umalloc instead."
//#endif

//! \brief Signature capture structure.
typedef struct {
	ushort us_screen_posx; //!< Screen position x.
	ushort us_screen_posy; //!< Screen position y.
	ushort us_screen_width; //!< Screen width.
	ushort us_screen_height; //!< Screen height.
	ushort us_timeout; //!< Timeout to Signature Capture.
	char pc_bmp_signature[BMP_IMAGE_SIZE];//!< format bmp signature.
	uint ui_bmp_size; //!< bmp signature size
} T_Signature;

//! \brief Signature capture settings.
typedef struct {
	ushort us_screen_posx;   //!< Screen position x.
	ushort us_screen_posy;   //!< Screen position y.
	ushort us_screen_width;  //!< Screen width.
	ushort us_screen_height; //!< Screen height.
	ushort us_timeout;       //!< Timeout for Signature Capture.
}T_CAPTURE_SETTINGS;

/** Job id */
typedef unsigned long IPA_JOB_ID;

//! \brief Telium timeout settings structure.
typedef struct {
	unsigned short usSuspendTimeout; //!< suspend timeout value.
	unsigned short usBacklightTimeout; //!< backlight timeout value.
} Timeout_Settings;

//! \brief WindowsCE power structure.
typedef struct {
	unsigned char ucACLineStatus; //!< Power status.
	unsigned char ucBatteryFlag; //!< Battery charge status.
	unsigned char ucBatteryLifePercent; //!< Battery life percentage.
	unsigned long ulBatteryVoltage; //!< Battery voltage value.
	unsigned long ulBatteryCurrent; //!< Battery current value.
	unsigned long ulBatteryTemperature; //!< Battery temperature value.
} PDA_Power_informations;

#endif

