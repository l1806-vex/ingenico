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
/* Module Name: ipa280_def.h                                                  */
/*                                                                            */
/* Function:    Application definitions used in ipa280                        */
/*                                                                            */
/* Notes:                                                                     */
/*                                                                            */
/*============================================================================*/
/* usr | yy-mm-dd |                                        |                  */
/* ewc | 09-06-12 | New for IPA280                         |                  */
/******************************************************************************/

#ifndef _IPA280_DEF_H_
#define _IPA280_DEF_H_

/*
#define     PDASPMCI_NUMBER         0xB3BA
#define     PDA_SERVICE_BASE        800

// IAC services
#define     SET_SPM_TIME            PDA_SERVICE_BASE + 0
#define     GET_SPM_INFORMATION     PDA_SERVICE_BASE + 1
#define     DO_SPM_UPDATE           PDA_SERVICE_BASE + 2
#define     SET_COMM_PERIPH_STATE   PDA_SERVICE_BASE + 3
#define     GET_COMM_PERIPH_STATE   PDA_SERVICE_BASE + 4
#define     DO_SIGNATURE_CAPTURE    PDA_SERVICE_BASE + 5
#define     SET_SPM_UPDATE_TIME     PDA_SERVICE_BASE + 6
#define     SEND_PDA_MESSAGE        PDA_SERVICE_BASE + 7
#define     RECEIVE_PDA_MESSAGE     PDA_SERVICE_BASE + 8
#define     IPA_PRINTER             PDA_SERVICE_BASE + 9
#define     PDA_MODEM               PDA_SERVICE_BASE + 10
#define     PDA_MODEM_GSM_SEND      PDA_SERVICE_BASE + 11
#define     PDA_MODEM_GSM_RECEIVE   PDA_SERVICE_BASE + 12
#define     START_SERVICE		   	PDA_SERVICE_BASE + 13
#define     STOP_SERVICE			PDA_SERVICE_BASE + 14
#define     SUSPEND_DEVICE			PDA_SERVICE_BASE + 15
#define     SET_SPM_SETTINGS		PDA_SERVICE_BASE + 16
#define     GET_SPM_SETTINGS		PDA_SERVICE_BASE + 17
#define     GET_PDA_POWER_INFO		PDA_SERVICE_BASE + 18
#define     GET_PDA_INFORMATION     PDA_SERVICE_BASE + 19
#define     SET_IDLE_MESSAGE        PDA_SERVICE_BASE + 20
#define     SET_REQUEST_CHARGING    PDA_SERVICE_BASE + 21
#define     GET_SERVER_STATE    	PDA_SERVICE_BASE + 22
#define     GET_SIGNATURE		    PDA_SERVICE_BASE + 23
#define     GET_PCL_STATE		    PDA_SERVICE_BASE + 24

//!! VG
#define     STORE_LOGO		  		PDA_SERVICE_BASE + 30
#define     PRINT_LOGO		  		PDA_SERVICE_BASE + 31
*/


//ret value
#define     RET_OK  0x00
#define     RET_KO  0x01

//SPM STATUS
#define     SPM_IDLE    0x01
#define     SPM_BUZY    0x02

//PDA PERIPH STATE
#define     PDA_PERIPH_CONNECTED        0x00
#define     PDA_PERIPH_NOT_CONNECTED    0x01
#define     PDA_PERIPH_CANNOT_TURNED_ON 0x01
#define     PDA_PERIPH_CANNOT_CONNECT   0x02

//PDA PERIPH
#define     PDA_GPRS        0x00
#define     PDA_WLAN        0x01
#define     PDA_BLUETOOTH   0x02
#define     PDA_LAN         0x03

#define     BMP_IMAGE_SIZE  60062// (800*600/8) bytes + 62 bmp header

// Apple server connection state
#define 	APPLE_SERVER_CONNECTED		1
#define 	APPLE_SERVER_DISCONNECTED	0

// Apple Connection State
#define 	APPLE_DEVICE_DISCONNECTED	0
#define 	APPLE_DEVICE_PRESENT		1
#define 	APPLE_DEVICE_AUTHENTICATED	2
#define 	APPLE_DEVICE_CONNECTED		3

// PCL state
#define		PCL_STATE_NOT_STARTED					0
#define		PCL_STATE_STARTED_NOT_INITIALIZED		1
#define		PCL_STATE_STARTED_INITIALIZED			2

#endif


