/*** 
* Copyright (c) 2006 Sagem Monetel SA, rue claude Chappe, 
* 07503 Guilherand-Granges, France, All Rights Reserved. 
* 
* Sagem Monetel SA has intellectual property rights relating 
* to the technology embodied in this software. In particular, 
* and without limitation, these intellectual property rights 
* may include one or more patents. 
* 
* This software is distributed under licenses restricting 
* its use, copying, distribution, and decompilation. 
* No part of this software may be reproduced in any form 
* by any means without prior written authorization of 
* Sagem Monetel. 
* 
* @Title: UCMHOSTDLL.H
* @Description: exchanges between UCMC and DLLHOSTs
* @Reference: 
* @Comment: 
* 
* @author	
* @version	1.0
* @Comment: 
* @date:	2006/02/01
*/
#ifndef _INC_UCMHOSTDLL 
#define _INC_UCMHOSTDLL

/************************************************************/
/* API dans la LIB 														*/
/************************************************************/
extern int iUcmHostLib_GetInfo( object_info_t *pinfos_p ) ;
extern int iUcmHostLib_Open(char *);
extern void UcmHostLib_Close(void);
extern int iUcmHostLib_Cmd(unsigned short, int, void*, int, void* ) ;

extern int iUcmHost2Lib_GetInfo( object_info_t *pinfos_p ) ;
extern int iUcmHost2Lib_Open(char *);
extern void UcmHost2Lib_Close(void);
extern int iUcmHost2Lib_Cmd(unsigned short, int, void*, int, void* ) ;

/************************************************************/
/*  Structs exchanged in service iUcmHostLib_Cmd			*/
/************************************************************/

// max size of userdata buffer
#define UCMHOST_USER_SIZEMAX (2048) /* max size of buffer userdata */

/************************************************************/
/* Description des commandes API dans la LIB						*/
/************************************************************/
#define UCMHOST_TO_HOST   		0x0000
#define UCMHOST_TO_DISPLAY		0x1000
#define UCMHOST_TO_PRINTER		0x2000
#define UCMHOST_TO_NETWORK	   0x4000
#define UCMHOST_TO_ICC			0x8000
#define UCMHOST_TO_PINPAD	   0x1100
#define UCMHOST_TO_BUZZER	   0x1200
#define UCMHOST_TO_LED        0x1400
#define UCMHOST_TO_ALL_LED    0x1401
#define UCMHOST_TO_BACKLIGHT  0x1501
#define UCMHOST_TO_DA  			0x9000
#define UCMHOST_TO_HOST2		0xA000

#define UCMHOST_CLEAR			0x0001
#define UCMHOST_CLOSE			0x0002
#define UCMHOST_INIT          0x0003
#define UCMHOST_MASK 			0x0004
#define UCMHOST_WAIT_MSG      0x0005
#define UCMHOST_SEND 			0x0006
#define UCMHOST_SEND_MSG      0x0007
#define UCMHOST_READ 			0x0008
#define UCMHOST_READ_MSG      0x0009
#define UCMHOST_START         0x000A
#define UCMHOST_DLL_STATUS    0x000B
#define UCMHOST_UCM_STATUS    0x000C
#define UCMHOST_STOP          0x000D
#define UCMHOST_SUSPEND       0x000E
#define UCMHOST_TEST          0x000F
#define UCMHOST_STOP_REC      0x0010
#define UCMHOST_START_REC     0x0011
#define UCMHOST_PAY_CMD       0x0012
#define UCMHOST_READ_CMD      0x0013
#define UCMHOST_MORE_FCT      0x0014

/* Efface les buffers emission et reception */
#define iUcmHostDll_Clear( void ) (iUcmHostLib_Cmd( UCMHOST_CLEAR, 0, NULL, 0, NULL ) )
/* Fermeture de la DLL */
#define UcmHostDll_Close( void ) (iUcmHostLib_Cmd( UCMHOST_CLOSE, 0, NULL, 0, NULL ) )
/* Initialisation de la DLL x=pointeur sur T_UCM_DEVICE Pas appele par Appli mais par UCMC */
#define iUcmHostDll_Init( x ) (iUcmHostLib_Cmd( UCMHOST_INIT, sizeof(T_UCM_DEVICE), x, 0, NULL ) )
/* Masque les messages attendus x=pointeur sur unsigned short y=pointeur sur unsigned short */
#define iUcmHostDll_Mask( x, y ) (iUcmHostLib_Cmd( UCMHOST_MASK, 2, x, 2, y ) )
/* Lecture des donnees brutes x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Read( x ) (iUcmHostLib_Cmd( UCMHOST_READ, sizeof(T_UCMHOST), x, 0, NULL ) )
/* Lecture des donnees brutes x=pointeur sur T_UCMHOST y= cmde */
#define iUcmHostDll_Read_Cmd( x, y ) (iUcmHostLib_Cmd( UCMHOST_READ_CMD, 2, x, sizeof(T_UCMC_IAC_HOST2), y ) )
/* Lecture du message x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Read_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_READ_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )
/* Attente d'un message : bloquant x=pointeur sur unsigned short y=pointeur sur unsigned short */
#define iUcmHostDll_Wait_Msg( x, y ) (iUcmHostLib_Cmd( UCMHOST_WAIT_MSG, 2, x, 2, y ))
/* Emission brute x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Send( x, y ) (iUcmHostLib_Cmd( UCMHOST_SEND , y , x, 0, NULL ) )
/* emission d'un message x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Send_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_SEND_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )
/* demarrage de la tache hote x=pointeur sur unsigned short */
#define iUcmHostDll_Start( x ) (iUcmHostLib_Cmd( UCMHOST_START, 2, x, 0, NULL ) )
/* Etat x=pointeur sur unsigned short, x=pointeur sur unsigned short*/
#define iUcmHostDll_Status( x ) (iUcmHostLib_Cmd( UCMHOST_DLL_STATUS, UCM_MAX_SIZE_DATA_DEVICE, x, 0, NULL ) )
/* Arret definitif de la tache hote avec port x=pointeur sur unsigned short */
#define iUcmHostDll_Stop( x ) (iUcmHostLib_Cmd( UCMHOST_STOP, 2, x, 0, NULL ) )
/* Arret definitif de la tache hote avec port x=pointeur sur unsigned short */
#define iUcmHostDll_Stop_Rec(void) (iUcmHostLib_Cmd( UCMHOST_STOP_REC, 0, NULL, 0, NULL ) )
#define iUcmHostDll_Start_Rec(void) (iUcmHostLib_Cmd( UCMHOST_START_REC, 0, NULL, 0, NULL ) )

/* Arret momentanee de la tache hote avec port x=pointeur sur unsigned short*/
#define iUcmHostDll_Suspend( x ) (iUcmHostLib_Cmd( UCMHOST_SUSPEND, 2, x, 0, NULL ) )
/* test de la DLL hote x=pointeur sur unsigned short */
#define iUcmHostDll_Test( x ) (iUcmHostLib_Cmd( UCMHOST_TEST, 2, x, 0, NULL ) )

/* More function de la DLL hote x=pointeur sur unsigned char = type d'imprimante */
#define iUcmHostDll_MoreFct( x ) (iUcmHostLib_Cmd( UCMHOST_MORE_FCT, 1, x, 0, NULL ) )

#define iUcmHostDll_SetUcmStatus( x ) (iUcmHostLib_Cmd( UCMHOST_UCM_STATUS, sizeof(T_UCMHOST_STATUS_UCM), x, 0, NULL ) )

/* Request cmd for payment x=normal command  y=pointer of T_UCMHOST_STATUS_UCM structure */
#define iUcmHostDll_GetPayCmd( x, y ) (iUcmHostLib_Cmd( UCMHOST_PAY_CMD, 1, x, sizeof(T_UCMHOST_STATUS_UCM), y ) )

/******* HOST DISPLAY ******/
#define UCMHOST_DISPLAY_MSG 		( UCMHOST_TO_DISPLAY | 0x0031 )

/* emission d'un message pour l'afficheur du hote x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Display_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_DISPLAY_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )

/******* HOST PRINTER ******/
#define UCMHOST_PRINT_MSG 			( UCMHOST_TO_PRINTER | 0x0041 )

/* emission d'un message pour l'imprimante du hote  hote x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Print_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_PRINT_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )

/******* HOST ICC ******/
#define UCMHOST_ICC_MSG 			( UCMHOST_TO_ICC | 0x0051 )

/* emission d'un message pour l'imprimante du hote  hote x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Icc_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_ICC_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )

/******* HOST PINPAD ******/
#define UCMHOST_PINPAD_MSG 			( UCMHOST_TO_PINPAD | 0x0061 )

/* emission d'un message pour le buzzer  hote x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Pinpad_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_PINPAD_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )

/******* HOST BUZZER ******/
#define UCMHOST_BUZZER_MSG 			( UCMHOST_TO_BUZZER | 0x0071 )

/* emission d'un message pour l'imprimante du hote  hote x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Buzzer_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_BUZZER_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )

/******* HOST LED ******/
#define UCMHOST_LED_MSG 			( UCMHOST_TO_LED | 0x0081 )

/* emission d'un message pour les leds du hote  hote x=pointeur sur T_UCMHOST */
#define iUcmHostDll_LED_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_LED_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )

/******* HOST MODEM ******/
#define UCMHOST_MODEM_CONNECT		( UCMHOST_TO_NETWORK | 0x0020 )
#define UCMHOST_MODEM_DISCONNECT	( UCMHOST_TO_NETWORK | 0x0021 )
#define UCMHOST_MODEM_WRITE		( UCMHOST_TO_NETWORK | 0x0022 )
#define UCMHOST_MODEM_READ			( UCMHOST_TO_NETWORK | 0x0023 )
#define UCMHOST_MODEM_STATUS		( UCMHOST_TO_NETWORK | 0x0024 )

/* Connexion modem hote x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Modem_Cnx( x ) (iUcmHostLib_Cmd( UCMHOST_MODEM_CONNECT, sizeof(T_UCMHOST_D_CONNECT), x, 0, NULL ) )
/* Deconnexion modem hote x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Modem_Dnx( x ) (iUcmHostLib_Cmd( UCMHOST_MODEM_DISCONNECT, 1, x, 0, NULL ) )
/* Ecriture data modem hote x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Modem_Write( x ) (iUcmHostLib_Cmd( UCMHOST_MODEM_WRITE, sizeof(T_UCMHOST), x,0, NULL ) )
/* Lecture data modem hote x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Modem_Read( x, y ) (iUcmHostLib_Cmd( UCMHOST_MODEM_READ, sizeof(T_UCMHOST), x, y, NULL ) )
/* Demande de status modem hote x=pointeur sur T_UCMHOST */
#define iUcmHostDll_Modem_Status( x, y ) (iUcmHostLib_Cmd( UCMHOST_MODEM_STATUS, sizeof(T_UCMHOST), x, 0, NULL ) )


/*********************************************************/
/* HOST2 */
/*********************************************************/
#define UCMHOST2_CLOSE			0x0002
#define UCMHOST2_INIT        0x0003
#define UCMHOST2_MASK 			0x0004
#define UCMHOST2_WAIT_MSG  0x0005
#define UCMHOST2_SEND 			0x0006
#define UCMHOST2_SEND_MSG      0x0007
#define UCMHOST2_READ 			0x0008
#define UCMHOST2_READ_MSG      0x0009
#define UCMHOST2_START         0x000A
#define UCMHOST2_DLL_STATUS    0x000B
#define UCMHOST2_UCM_STATUS    0x000C
#define UCMHOST2_STOP          0x000D
#define UCMHOST2_SUSPEND       0x000E
#define UCMHOST2_TEST          0x000F
#define UCMHOST2_STOP_REC      0x0010
#define UCMHOST2_START_REC     0x0011
#define UCMHOST2_PAY_CMD       0x0012
#define UCMHOST2_READ_CMD      0x0013
#define UCMHOST2_MORE_FCT      0x0014


/* Efface les buffers emission et reception */
#define iUcmHost2Dll_Clear( void ) (iUcmHost2Lib_Cmd( UCMHOST_CLEAR, 0, NULL, 0, NULL ) )
/* Fermeture de la DLL */
#define UcmHost2Dll_Close( void ) (iUcmHost2Lib_Cmd( UCMHOST_CLOSE, 0, NULL, 0, NULL ) )
/* Initialisation de la DLL x=pointeur sur T_UCM_DEVICE Pas appele par Appli mais par UCMC */
#define iUcmHost2Dll_Init( x ) (iUcmHost2Lib_Cmd( UCMHOST_INIT, sizeof(T_UCM_DEVICE), x, 0, NULL ) )
/* Masque les messages attendus x=pointeur sur unsigned short y=pointeur sur unsigned short */
#define iUcmHost2Dll_Mask( x, y ) (iUcmHost2Lib_Cmd( UCMHOST_MASK, 2, x, 2, y ) )
/* Lecture des donnees brutes x=pointeur sur T_UCMHOST */
#define iUcmHost2Dll_Read( x ) (iUcmHost2Lib_Cmd( UCMHOST_READ, sizeof(T_UCMHOST), x, 0, NULL ) )
/* Lecture des donnees brutes x=pointeur sur T_UCMHOST y= cmde */
#define iUcmHost2Dll_Read_Cmd( x, y ) (iUcmHost2Lib_Cmd( UCMHOST_READ_CMD, 2, x, sizeof(T_UCMC_IAC_HOST2), y ) )
/* Lecture du message x=pointeur sur T_UCMHOST */
#define iUcmHost2Dll_Read_Msg( x ) (iUcmHost2Lib_Cmd( UCMHOST_READ_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )
/* Attente d'un message : bloquant x=pointeur sur unsigned short y=pointeur sur unsigned short */
#define iUcmHost2Dll_Wait_Msg( x, y ) (iUcmHost2Lib_Cmd( UCMHOST_WAIT_MSG, 2, x, 2, y ))
/* Emission brute x=pointeur sur T_UCMHOST */
#define iUcmHost2Dll_Send( x, y ) (iUcmHost2Lib_Cmd( UCMHOST_SEND , y , x, 0, NULL ) )
/* emission d'un message x=pointeur sur T_UCMHOST */
#define iUcmHost2Dll_Send_Msg( x ) (iUcmHost2Lib_Cmd( UCMHOST_SEND_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )
/* demarrage de la tache hote x=pointeur sur unsigned short */
#define iUcmHost2Dll_Start( x ) (iUcmHost2Lib_Cmd( UCMHOST_START, 2, x, 0, NULL ) )
/* Etat x=pointeur sur unsigned short, x=pointeur sur unsigned short*/
#define iUcmHost2Dll_Status( x ) (iUcmHost2Lib_Cmd( UCMHOST_DLL_STATUS, UCM_MAX_SIZE_DATA_DEVICE, x, 0, NULL ) )
/* Arret definitif de la tache hote avec port x=pointeur sur unsigned short */
#define iUcmHost2Dll_Stop( x ) (iUcmHost2Lib_Cmd( UCMHOST_STOP, 2, x, 0, NULL ) )
/* Arret definitif de la tache hote avec port x=pointeur sur unsigned short */
#define iUcmHost2Dll_Stop_Rec(void) (iUcmHost2Lib_Cmd( UCMHOST_STOP_REC, 0, NULL, 0, NULL ) )
#define iUcmHost2Dll_Start_Rec(void) (iUcmHost2Lib_Cmd( UCMHOST_START_REC, 0, NULL, 0, NULL ) )

/* Arret momentanee de la tache hote avec port x=pointeur sur unsigned short*/
#define iUcmHost2Dll_Suspend( x ) (iUcmHostLib_Cmd( UCMHOST_SUSPEND, 2, x, 0, NULL ) )
/* test de la DLL hote x=pointeur sur unsigned short */
#define iUcmHost2Dll_Test( x ) (iUcmHostLib_Cmd( UCMHOST_TEST, 2, x, 0, NULL ) )

/* More function de la DLL hote x=pointeur sur unsigned char = type d'imprimante */
#define iUcmHost2Dll_MoreFct( x ) (iUcmHostLib_Cmd( UCMHOST_MORE_FCT, 1, x, 0, NULL ) )

#define iUcmHost2Dll_SetUcmStatus( x ) (iUcmHostLib_Cmd( UCMHOST_UCM_STATUS, sizeof(T_UCMHOST_STATUS_UCM), x, 0, NULL ) )

/* Request cmd for payment x=normal command  y=pointer of T_UCMHOST_STATUS_UCM structure */
#define iUcmHost2Dll_GetPayCmd( x, y ) (iUcmHostLib_Cmd( UCMHOST_PAY_CMD, 1, x, sizeof(T_UCMHOST_STATUS_UCM), y ) )

/* emission d'un message pour l'afficheur du hote x=pointeur sur T_UCMHOST */
#define iUcmHost2Dll_Display_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_DISPLAY_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )

/* emission d'un message pour l'imprimante du hote  hote x=pointeur sur T_UCMHOST */
#define iUcmHost2Dll_Print_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_PRINT_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )

/* emission d'un message pour l'imprimante du hote  hote x=pointeur sur T_UCMHOST */
#define iUcmHost2Dll_Icc_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_ICC_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )

/* emission d'un message pour le buzzer  hote x=pointeur sur T_UCMHOST */
#define iUcmHost2Dll_Pinpad_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_PINPAD_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )

/* emission d'un message pour l'imprimante du hote  hote x=pointeur sur T_UCMHOST */
#define iUcmHost2Dll_Buzzer_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_BUZZER_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )

/* emission d'un message pour les leds du hote  hote x=pointeur sur T_UCMHOST */
#define iUcmHost2Dll_LED_Msg( x ) (iUcmHostLib_Cmd( UCMHOST_LED_MSG, sizeof(T_UCMHOST), x, 0, NULL ) )



/************************************************************/
/* Msg		HOST 											*/
/************************************************************/
#define UCMHOSTLIB_MSG_DATA					0x0000

#define UCMHOSTLIB_MSG_DEM_STATUS			0x0001 
#define UCMHOSTLIB_MSG_REP_STATUS 			0x0002

#define UCMHOSTLIB_MSG_DEM_VERSION			0x0003
#define UCMHOSTLIB_MSG_REP_VERSION			0x0004

#define UCMHOSTLIB_MSG_DEM_SYS	 			0x0005
#define UCMHOSTLIB_MSG_REP_SYS	 			0x0006

#define UCMHOSTLIB_MSG_DEM_FCTAPP 			0x0007
#define UCMHOSTLIB_MSG_REP_FCTAPP 			0x0008

#define UCMHOSTLIB_MSG_DEM_ISO2 			   0x0009
#define UCMHOSTLIB_MSG_REP_ISO2 			   0x000a

#define UCMHOSTLIB_MSG_DEM_SOLVED 			0x000b
#define UCMHOSTLIB_MSG_REP_SOLVED 			0x000c

#define UCMHOSTLIB_MSG_DEM_ENREG 			0x000d
#define UCMHOSTLIB_MSG_REP_ENREG 			0x000e

#define UCMHOSTLIB_MSG_DEM_CANCEL 			0x0011
#define UCMHOSTLIB_MSG_REP_CANCEL 			0x0012

#define UCMHOSTLIB_MSG_DEM_RESTART 			0x0013
#define UCMHOSTLIB_MSG_REP_RESTART 			0x0014

#define UCMHOSTLIB_MSG_DEM_CONSO			   0x0015
#define UCMHOSTLIB_MSG_REP_CONSO			   0x0016

#define UCMHOSTLIB_MSG_DEM_MTNC 			   0x0017
#define UCMHOSTLIB_MSG_REP_MTNC 			   0x0018

#define UCMHOSTLIB_MSG_DEM_CHGT_DATE		0x0019
#define UCMHOSTLIB_MSG_REP_CHGT_DATE		0x001A

#define UCMHOSTLIB_MSG_DEM_SOLVED_LOC		0x0020
#define UCMHOSTLIB_MSG_REP_SOLVED_LOC		0x0021

#define UCMHOSTLIB_MSG_DEM_ENREG_LOC 		0x0022
#define UCMHOSTLIB_MSG_REP_ENREG_LOC		0x0023

#define UCMHOSTLIB_MSG_DEM_CARD_INFO 		0x0024
#define UCMHOSTLIB_MSG_REP_CARD_INFO		0x0025

#define UCMHOSTLIB_MSG_DEM_PAY      		0x0026

#define UCMHOSTLIB_MSG_DEM_CONF_DEVICE   0x0028
#define UCMHOSTLIB_MSG_REP_CONF_DEVICE 0x0029

#define UCMHOSTLIB_MSG_DEM_PARAM_CONF  0x002A
#define UCMHOSTLIB_MSG_REP_PARAM_CONF 0x002B

#define UCMHOSTLIB_MSG_DEM_DEVICE_INIT  0x002C
#define UCMHOSTLIB_MSG_REP_DEVICE_INIT 0x002D

#define  UCMHOSTLIB_MSG_DEM_DEVICE_CMD   0x002E
#define  UCMHOSTLIB_MSG_REP_DEVICE_CMD   0x002F


#define UCMHOSTLIB_MSG_DEM_CONNECT			( UCMHOST_TO_NETWORK |0x0020 )
#define UCMHOSTLIB_MSG_REP_CONNECT			( UCMHOST_TO_NETWORK |0x0021 )

#define UCMHOSTLIB_MSG_DEM_DISCONNECT		( UCMHOST_TO_NETWORK |0x0022 )

#define UCMHOSTLIB_MSG_NETWORK_WRITE			( UCMHOST_TO_NETWORK |0x0023 )
#define UCMHOSTLIB_MSG_NETWORK_READ				( UCMHOST_TO_NETWORK |0x0024 )
#define UCMHOSTLIB_MSG_NETWORK_STATUS		( UCMHOST_TO_NETWORK |0x0025 )

#define UCMHOSTLIB_MSG_DISPLAY 				( UCMHOST_TO_DISPLAY |0x0010 )
#define UCMHOSTLIB_MSG_DEM_DISPLAY_ASK_MSG 	( UCMHOST_TO_DISPLAY |0x0011 )
#define UCMHOSTLIB_MSG_REP_DISPLAY_ASK_MSG 	( UCMHOST_TO_DISPLAY |0x0012 )

#define UCMHOSTLIB_MSG_PRINTER 				( UCMHOST_TO_PRINTER |0x0010 )

#define UCMHOSTLIB_MSG_ICC 				   ( UCMHOST_TO_ICC |0x0010 )

#define UCMHOSTLIB_MSG_PPAD 				   ( UCMHOST_TO_PINPAD |0x0010 )

#define UCMHOSTLIB_MSG_BUZZER				   ( UCMHOST_TO_BUZZER |0x0010 )

#define UCMHOSTLIB_MSG_LED 				   ( UCMHOST_TO_LED |0x0010 )
#define UCMHOSTLIB_MSG_LEDCH 				   ( UCMHOST_TO_LED |0x0020 )

#define UCMHOSTLIB_MSG_ALL_LEDS	         ( UCMHOST_TO_ALL_LED |0x0010 )
#define UCMHOSTLIB_MSG_ALL_LEDSCH	      ( UCMHOST_TO_ALL_LED |0x0020 )

#define UCMHOSTLIB_MSG_BACKLIGHT                  (UCMHOST_TO_BACKLIGHT|0x0010)

//UCM
#define	UCMHOSTLIB_MSG_PARAM_DA				(UCMHOST_TO_DA|1)
#define	UCMHOSTLIB_MSG_EPURSE_BALANCE		(UCMHOST_TO_DA|2)
#define	UCMHOSTLIB_MSG_ANSW_DEBIT			(UCMHOST_TO_DA|3)
#define	UCMHOSTLIB_MSG_ANSW_REVALUE		(UCMHOST_TO_DA|4)
#define	UCMHOSTLIB_MSG_END					(UCMHOST_TO_DA|5)
#define	UCMHOSTLIB_MSG_PARAM_DA_MSG		(UCMHOST_TO_DA|6)
#define	UCMHOSTLIB_MSG_APP_END_REVALUE   (UCMHOST_TO_DA|7)
#define	UCMHOSTLIB_MSG_PARAM_DA_GET		    (UCMHOST_TO_DA|8)
#define	UCMHOSTLIB_MSG_PARAM_DA_MSG_GET	(UCMHOST_TO_DA|9)

#define	UCMHOSTLIB_MSG_ASK_CHANGE_IDLE_MSG	(UCMHOST_TO_DA|0x0A)
#define  UCMHOSTLIB_MSG_ASK_DEBIT 			   (UCMHOST_TO_DA|0x0B)
#define	UCMHOSTLIB_MSG_ASK_REMOVE_CARD		(UCMHOST_TO_DA|0x0C)
#define	UCMHOSTLIB_MSG_NOT_AVAILABLE		   (UCMHOST_TO_DA|0x0D)
#define	UCMHOSTLIB_MSG_CR_DISTRIBUTION		(UCMHOST_TO_DA|0x0E)
#define	UCMHOSTLIB_MSG_ASK_REVALUE			   (UCMHOST_TO_DA|0x0F)
#define	UCMHOSTLIB_MSG_REC_REVALUE			   (UCMHOST_TO_DA|0x10)
#define	UCMHOSTLIB_MSG_ASK_DISP_MSG_APPLI	(UCMHOST_TO_DA|0x11)
#define	UCMHOSTLIB_MSG_CASH_SALE            (UCMHOST_TO_DA|0x12)
#define	UCMHOSTLIB_MSG_ASK_CHANGE_IDLE_MSG_CH (UCMHOST_TO_DA|0x13)
/*#define	UCMHOSTLIB_CMD_ANSW_EPURSE_REVALUE	(01)*/
#define	UCMHOSTLIB_MSG_PARAM_DA_VM_GET	(UCMHOST_TO_DA|0x14) 
#define  UCMHOSTLIB_MSG_NO			 		       0xFFFF

/************ Command T_UCMC_IAC_HOST for vending ************/
#define  UCMHOSTLIB_CMD_EPURSE_BALANCE          ( UCMHOST_TO_DA | 0x20 )
#define  UCMHOSTLIB_CMD_ANS_EPURSE_REVALUE      ( UCMHOST_TO_DA | 0x21 )
#define  UCMHOSTLIB_CMD_ANS_REC_EPURSE_REVALUE  ( UCMHOST_TO_DA | 0x22 )
#define  UCMHOSTLIB_CMD_PARAM_DA                ( UCMHOST_TO_DA | 0x23 )
#define  UCMHOSTLIB_CMD_END_DEBIT               ( UCMHOST_TO_DA | 0x24 )
#define  UCMHOSTLIB_CMD_PARAM_DA_MSG            ( UCMHOST_TO_DA | 0x25 )
#define  UCMHOSTLIB_CMD_PARAM_DA_GET            ( UCMHOST_TO_DA | 0x26 )
#define  UCMHOSTLIB_CMD_PARAM_DA_MSG_GET        ( UCMHOST_TO_DA | 0x27 )
#define  UCMHOSTLIB_CMD_PARAM_DA_VM_GET        ( UCMHOST_TO_DA | 0x28 )

/************ Command T_UCMC_IAC_HOST for vending master MDB ************/
#define  UCMHOSTLIB_CMD_MDBM_PERIPH_STATUS       ( UCMHOST_TO_HOST2 | 0x20 )
#define  UCMHOSTLIB_CMD_MDBM_CR_PERIPH_STATUS    ( UCMHOST_TO_HOST2 | 0x21 )
#define  UCMHOSTLIB_CMD_MDBM_PERIPH_ACTIVATION   ( UCMHOST_TO_HOST2 | 0x22 )
#define  UCMHOSTLIB_CMD_MDBM_PERIPH_CR_ACTIVATION ( UCMHOST_TO_HOST2 | 0x23 )
#define  UCMHOSTLIB_CMD_MDBM_BALANCE              ( UCMHOST_TO_HOST2 | 0x24 )
#define  UCMHOSTLIB_CMD_MDBM_CR_DEBIT             ( UCMHOST_TO_HOST2 | 0x25 )
#define  UCMHOSTLIB_CMD_MDBM_END                  ( UCMHOST_TO_HOST2 | 0x26 )
#define  UCMHOSTLIB_CMD_MDBM_ASK_DEBIT            ( UCMHOST_TO_HOST2 | 0x27 )
#define  UCMHOSTLIB_CMD_MDBM_CR_DISTRIBUTION     ( UCMHOST_TO_HOST2 | 0x28 )
#define  UCMHOSTLIB_CMD_MDBM_GIVE_BACK            ( UCMHOST_TO_HOST2 | 0x29 )
#define  UCMHOSTLIB_CMD_MDBM_CR_GIVE_BACK        ( UCMHOST_TO_HOST2 | 0x2A )
#define  UCMHOSTLIB_CMD_MDBM_ASK_REVALUE          ( UCMHOST_TO_HOST2 | 0x2B )
#define  UCMHOSTLIB_CMD_MDBM_CR_REVALUE           ( UCMHOST_TO_HOST2 | 0x2C )

/************************************************************/

/************************************************************/
/* Erreur																	*/
/************************************************************/
#define UCMHOSTLIB_ERR_LINK					( -50 )
#define UCMHOSTLIB_ERR_OBJECTLOAD			( -51 )
#define UCMHOSTLIB_ERR_CMD_UNKNOWN			( -52 )
#define UCMHOSTLIB_ERR_DLL_NAME				( -53 )
#define UCMHOSTLIB_ERR_DLL_WRITE_BUF		( -54 )
#define UCMHOSTLIB_ERR_DLL_WRITE_BUF2		( -55 )
#define UCMHOSTLIB_ERR_DLL_WRITE_BUF3		( -56 )
#define UCMHOSTLIB_ERR_DLL_READ_BUF			( -57 )
#define UCMHOSTLIB_ERR_DLL_COM		 		( -58 )
#define UCMHOSTLIB_ERR_DLL_BAD_PILOTE		( -59 )
#define UCMHOSTLIB_ERR_DLL_NO_MSG  			( -60 )
#define UCMHOSTLIB_ERR_DLL_COM_HANDLE		( -61 )
#define UCMHOSTLIB_ERR_DLL_COM_NUMBER		( -62 )
#define UCMHOSTLIB_ERR_DLL_COM_CLOSED		( -63 )
#define UCMHOSTLIB_ERR_DLL_DATA_LG			( -64 )
#define UCMHOSTLIB_ERR_DLL_DATA_LG_0		( -65 )
#define UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED	( -66 )
#define UCMHOSTLIB_ERR_DLL_MSG_UNKNOWN		( -67 )
#define UCMHOSTLIB_ERR_DLL_MSG_DISPLAY_UNKNOWN ( -68 )
#define UCMHOSTLIB_ERR_DLL_MSG_PRINTER_UNKNOWN ( -69 )
#define UCMHOSTLIB_ERR_DLL_MSG_MODEM_UNKNOWN ( -70 )
#define UCMHOSTLIB_ERR_DLL_MSG_OVERRUN		( -71 )
#define UCMHOSTLIB_ERR_DLL_MSG_CREAT		( -72 )
#define UCMHOSTLIB_ERR_DLL_MSG_ICC_UNKNOWN ( -73 )
#define UCMHOSTLIB_ERR_DLL_MSG_PINPAD_UNKNOWN ( -74 )
#define UCMHOSTLIB_ERR_DLL_MSG_BUZZER_UNKNOWN ( -75 )
#define UCMHOSTLIB_ERR_DLL_MSG_LED_UNKNOWN ( -76 )

#define UCMHOST2LIB_ERR_LINK					( -150 )
#define UCMHOST2LIB_ERR_OBJECTLOAD			( -151 )
#define UCMHOST2LIB_ERR_CMD_UNKNOWN		( -152 )
#define UCMHOST2LIB_ERR_DLL_NAME				( -153 )
#define UCMHOST2LIB_ERR_DLL_WRITE_BUF		( -154 )
#define UCMHOST2LIB_ERR_DLL_WRITE_BUF2		( -155 )
#define UCMHOST2LIB_ERR_DLL_WRITE_BUF3		( -156 )
#define UCMHOST2LIB_ERR_DLL_READ_BUF			( -157 )
#define UCMHOST2LIB_ERR_DLL_COM		 		( -158 )
#define UCMHOST2LIB_ERR_DLL_BAD_PILOTE		( -159 )
#define UCMHOST2LIB_ERR_DLL_NO_MSG  			( -160 )
#define UCMHOST2LIB_ERR_DLL_COM_HANDLE		( -161 )
#define UCMHOST2LIB_ERR_DLL_COM_NUMBER		( -162 )
#define UCMHOST2LIB_ERR_DLL_COM_CLOSED		( -163 )
#define UCMHOST2LIB_ERR_DLL_DATA_LG			( -164 )
#define UCMHOST2LIB_ERR_DLL_DATA_LG_0		( -165 )
#define UCMHOST2LIB_ERR_CMD_NOT_AUTHORIZED	( -166 )
#define UCMHOST2LIB_ERR_DLL_MSG_UNKNOWN		( -167 )
#define UCMHOST2LIB_ERR_DLL_MSG_DISPLAY_UNKNOWN ( -168 )
#define UCMHOST2LIB_ERR_DLL_MSG_PRINTER_UNKNOWN ( -169 )
#define UCMHOST2LIB_ERR_DLL_MSG_MODEM_UNKNOWN ( -170 )
#define UCMHOST2LIB_ERR_DLL_MSG_OVERRUN		( -171 )
#define UCMHOST2LIB_ERR_DLL_MSG_CREAT		( -172 )
#define UCMHOST2LIB_ERR_DLL_MSG_ICC_UNKNOWN ( -173 )
#define UCMHOST2LIB_ERR_DLL_MSG_PINPAD_UNKNOWN ( -174 )
#define UCMHOST2LIB_ERR_DLL_MSG_BUZZER_UNKNOWN ( -175 )
#define UCMHOST2LIB_ERR_DLL_MSG_LED_UNKNOWN ( -176 )

/* Structures Echanges UCM <-> DLLHote */
/************************************/
/*************** DEBIT **************/
/************************************/
/********** VENDING *****************/
/* DLL -> APP */
typedef struct
{
	unsigned char ucCmd;
	unsigned char ucSelectionNumber;
   unsigned char ucVendType;
   unsigned char ucSelectionNotDefined ; /* modif v91.11 */
	unsigned int  uiSelectionPrice;
	unsigned char tucCurrencyCode [ 3 ] ;
}T_UCMHOST_DA_ASK_DEBIT ;           /*T_UCMC_DA_ASK_DEBIT;*/

typedef struct
{
	unsigned char ucCmd;
	unsigned char ucCrDistribution;    /*UCMHOST_CR_OK*/
	unsigned char ucSelectionNumber;
}T_UCMHOST_DA_CR_DISTRIBUTION ;   /*T_UCMC_DA_CR_DISTRIBUTION;*/


typedef struct
{
	unsigned char ucCmd;
   unsigned char tucCurrencyCode [ 3 ] ;
	unsigned int  uiRevalueAmount;
}T_UCMHOST_DA_ASK_REVALUE ;      /*T_UCMC_DA_ASK_REVALUE;*/

typedef struct
{
   unsigned char      ucCmd ;             /* UCMC_RECORD_REVALUE_EPURSE */
	unsigned char      ucType ;
   unsigned char      tucRuf ;
	unsigned char      ucCrRevalue ;
} T_UCMHOST_DA_REC_EPURSE_REVALUE ;  /*T_UCMC_DA_REC_EPURSE_REVALUE ;*/

typedef struct
{
	unsigned char   ucRecord[ 12 ] ;   /* dossier ASCII */ 
	unsigned char   ucCardOlder ;      /* 0=absent   1=present */

	union
	{
		unsigned char ucRuf[ 20 - 13 ];     /* Reserve */	
	} u;
	
} T_UCMHOST_SOLV_COMP_LOC ;

typedef struct
{
	unsigned char   ucRecord[ 12 ] ;   /* For location only ASCII else space 0x20 */ 
	unsigned char   ucCardOlder ;     /* For location only 0=absent   1=present */

   unsigned char  ucLg;
   unsigned short  usType;

   unsigned char   ucTLVData[ 40 - 3 - 13 ] ; /* ASCII */
} T_UCMHOST_SOLV_TLV ;


typedef struct
{
	unsigned long  ulAmount ;
	S_MONEY      tCurrency;   /* T_COD_MONEY  only mandatory for 1042 */

	unsigned char  ucTrsType;    /* For UCM: Type of transaction equal transin.payment TRANSACTION_TYPE */
	unsigned char  ucTrsEntry;    /* For UCM:equal param_in.entry  ENTRY_TYPE */
	unsigned char  ucTrsMode;    /* For UCM:equal param_in.payment  PAYMENT_MODE */
	unsigned char  ucTrsSupport;  /* For UCM: equal  SUPPORT_TYPE */
	
	unsigned char  ucFunction; /* UCMHOST_FCT_SOLV or UCMHOST_FCT_ENREG */	
	unsigned char  ucMode;		/* Real or Test */
	unsigned char  ucClasse;	/* '2'=2.1 */

	unsigned char  ucPrint;		/* Ticket to be print */
	unsigned char  ucDisplay;	/* RUF: Display operation */

	unsigned short  usToWaitingCard; /* timeout waiting card if not inside before trs 1=Yes 0=no 0xFF=default */
	unsigned short  usToRemovedCard; /* Time out to retrieved card after trs 1=Yes 0=No 0xFF= default */

	unsigned char  ucAppliNum; /* Application number if specific */

	unsigned char  ucPowerOn; /* 1= Power on for solv */

	union
	{
		unsigned char                    ucRuf[ 40 ]; /* Reserve */	
		T_UCMHOST_DA_ASK_DEBIT      		tDaAskForDebit ;
		T_UCMHOST_DA_CR_DISTRIBUTION 		tDaCrDistribution ;
		T_UCMHOST_DA_ASK_REVALUE			tDaAskForRevalue ;
		T_UCMHOST_DA_REC_EPURSE_REVALUE	tDaRecRevalue ;
		T_UCMHOST_SOLV_COMP_LOC          tSolvLoc ;
		T_UCMHOST_SOLV_TLV               tSolvTlv ;
	} u;
	
} T_UCMHOST_DEBIT ;

/***  APPLI -> DLL ****/
//T_UCMHOST_DA_TABLE_PRIX
typedef struct
{
   unsigned int  uiPrixEspece;
   unsigned int  uiPrixCarte ;
	unsigned char ucNumSelection ;
	unsigned char ucValiditePrixEspece ;
   unsigned char ucValiditePrixCarte ;
   unsigned char ucRuf;
}T_UCMHOST_DA_TABLE_PRIXV3 ;    /*compatible to T_UCMHOST_TABLE_PRIX;*/

// T_UCMHOST_DA_PARAM
//ucVendingMode
#define UCMHOST_VENDING_MODE_BALANCE_FIRST   0	//balance -> selection (default mode)
#define UCMHOST_VENDING_MODE_SELECTION_FIRST	1	//selection-> vend
#define UCMHOST_VENDING_MODE_PUSHBUTTON      2	//button -> vend
#define UCMHOST_VENDING_MODE_SELECTION_FIRST_NO_MIXED 3	//selection-> vend for 2EXE If money is the coin in the payment with card is not possible

//ucDisplayPrice
#define UCMHOST_DISPLAY_PRICE_NONE				0
#define UCMHOST_DISPLAY_PRICE_CASH				1
#define UCMHOST_DISPLAY_PRICE_CARD				2

typedef struct
{
	unsigned char ucParamDisplayOn; /* 0: pas d'affichage 1:affichage */
   unsigned char ucMaxLine;
   unsigned char ucMaxCololon;
   unsigned char ucPad;  /* 1 paddage avec des blancs et pas de saut de ligne */
   unsigned short usOption;
   unsigned short usRuf;
} T_UCMHOST_PARAM_DA_DISPLAY;

typedef struct 
{
   unsigned char                 ucValidity;
   unsigned char                 tucTerminalNumber [ 10 + 1 ] ;
   unsigned char                 ucVmcType [ 2 ] ;

   unsigned short                usiTimeOutIfNoSelection ;     /* second */
   unsigned short                usiTimeOutBuzzer ;            /* second */
   unsigned short                usiBuzzerDuration ;           /* second */
   unsigned char                 ucDigitNumber ;               /* dot position */

   unsigned char                 tucCurrencyLabel [ 3 + 1 ] ;
   unsigned char                 tucCurrencyCode [ 3 + 1 ] ;
   unsigned char                 ucMultivendPossible;
   unsigned char                 ucPriceHolding;
   unsigned char                 ucRuf;                     /* v0200 */

   unsigned int                   uiScaleFactor ;            /* v0220 old name usiScaleFactor */
   unsigned char                 ucNbSelection;
   unsigned char                 ucEVA ;                   /* Old ucRuf2: 0=LED EVA default parameters, 0xFF=no EVA, 0x01=Default backlight Display,
                                                                           0x02=Second backlight Display, 0x03=All Displays, 0x10=IUR250, 0x77=All Blacklight */
   unsigned short int            usiTimeOutVM ;               /*  v0208  */  

   T_UCMHOST_DA_TABLE_PRIXV3  tPriceTable [ 100 ] ;      /* v0205 */

   unsigned short                usTimeOutIfSelected ;    	/* second */
   unsigned char                 ucVendingMode ;
   unsigned char                 ucDisplayPrice;				/* supported if ucPriceHolding==1 and ucVendingMode!=UCMHOST_VENDING_MODE_SELECTION_FIRST */

   unsigned int                  uiDllParameters ;         /* v0208 b0 = ACTIVE GATEWAY. b1 = ACTIVE SIELAFF MODE.
                                                                              b2 = MDB ANSWER MODE =>  1=direct, 0=wait poll cmd to answer */
   unsigned short int             usiCashLessAdress ;       /* v0208 */

   unsigned char                 ucDisplayDa;     /* v0208 : use Vending Machine display */
   unsigned char                 ucAppMaxRspTime ;  /* MDB:Application non response Time max 255 seconds old ucRuf3*/

}T_UCMHOST_DA_PARAMV5 ;		

typedef struct 				
{
   unsigned char                 tucIdleMsg [ 65 + 1 ] ;		
   unsigned char                 tucMsgDaNonInit [ 65 + 1 ];
   unsigned char                 tucMsgCommunicationVmcKo [ 65 + 1 ] ;
   unsigned char                 tucMsgProductSelected [ 65 + 1 ] ;	// used in first selection mode		
   unsigned char                 tucMsgProductPriceNotDefined [ 65 + 1 ] ;			
}T_UCMHOST_DA_PARAM_MSGV3 ; 

typedef struct 				
{
   T_UCMHOST_PARAM_DA_DISPLAY tParamDisplay;
}T_UCMHOST_DA_PARAM_VMV1 ; 

typedef struct
{
	unsigned long                  ulEpurseBalance ;
	unsigned char                  ucCr ;           /*UCMHOST_CR_OK*/
	unsigned char                  tucCurrencyCode [ 3 ] ;
	unsigned char                  tucLanguageCode [ 3 ] ;
	unsigned char                  ucAllowRevalue ;
   unsigned char                  ucAllowRefund ;
   unsigned char                  ucAllowDisplayBalance ;
   unsigned char                  ucAllowMultiVend ;
   unsigned char                  ucRuf ;             /* v0200 */
												// if ucAllowRevalue=TRUE else set to 0
   unsigned long	                ulRevalueLimitBalance ;	// max value of Epurse Balance
   unsigned long	                ulRevalueLimitAmount ;	// max value of coins used for revalue (coins upper limit)
}T_UCMHOST_DA_EPURSE_BALANCEV3 ;      /* compatible to T_UCMHOST_EPURSE_BALANCEV2;*/

typedef struct
{
	unsigned char ucCrRevalue ;         /*UCMHOST_CR_OK*/
   unsigned char tucRuf [ 3 ] ;        /* v0200 size = 3 instead of 2 */
   unsigned long ulRevalueAmount ;
   unsigned long ulEpurseBalance ;
}T_UCMHOST_DA_CR_EPURSE_REVALUEV3 ;   /*compatible to T_UCMC_DA_CR_REVALUE;*/

typedef struct
{
	unsigned char ucCrRecRevalue ;         /*UCMHOST_CR_OK*/
   unsigned char tucRuf [ 2 ] ;
}T_UCMHOST_DA_CR_REC_EPURSE_REVALUE ;  
/********** FIN VENDING *************/

/************************************/
/*********RESULT DEBIT **************/
/************************************/
//ucMode
#define UCMHOST_MODE_REEL	0
#define UCMHOST_MODE_TEST	1
//ucClasse
#define UCMHOST_CLASSE_1	    1
#define UCMHOST_CLASSE_2_1	 2
#define UCMHOST_CLASSE_2_2	 3

//ucFunction
#define UCMHOST_FCT_SOLV 	'D' /* au lieu de 0 */
#define UCMHOST_FCT_ENREG 1
#define UCMHOST_FCT_REVALUE   2	
#define UCMHOST_FCT_CARD_INFO      3

//ucCR
#define UCMHOST_CR_OK					0				
#define UCMHOST_CR_BUSY			      1
#define UCMHOST_CR_MTNC				   2	// Mode maintenance
#define UCMHOST_CR_PBINIT				3	// Appli non init
#define UCMHOST_CR_PBFILE			   4	// Pb fichier applicatifs
#define UCMHOST_CR_AMOUNT_CURRENCY	5	// Montant ou devise incorrecte
#define UCMHOST_CR_CARDINVALIDE		6	// Carte Invalide
#define UCMHOST_CR_CARDINCIDENT		7	// Incident Carte
#define UCMHOST_CR_CANCEL				8	// Abandon Operateur
#define UCMHOST_CR_NETWORK				9	// Acces centre
#define UCMHOST_CR_CARDFORBIDEN		10	// carte interdite
#define UCMHOST_CR_REFUSED				11	// Tr refusee
#define UCMHOST_CR_PB_SAM				12	// Pb SAM
#define UCMHOST_CR_PB_EPURSE			13	// Pb EPURSE MONEO for exemple
#define UCMHOST_CR_PB_SOFT_TOLL		14	// Pb Serveur
#define UCMHOST_CR_NO_FCT				14	// demande echouee pas d'appli
#define UCMHOST_CR_PB_RECORD_EXIST	15	// Pb Record exist
#define UCMHOST_CR_PB_AMOUNT_EXACT	16	// Pb Amount not exact

#define UCMHOST_CR_NOSOLV			    4	// Enreg : Pas de solvabilite anterieure
#define UCMHOST_CR_AMOUNTSUP			 5	// Enreg : Montant > montant autorise
#define UCMHOST_CR_SOLV_CANCEL		 6	// Enreg : Solv annulée
#define UCMHOST_CR_CANCEL_REFUSED    7	// Enreg : Annulation impossible
#define UCMHOST_CR_RETRY				 8	// Enreg : Reprise de la transaction
#define UCMHOST_CR_RECORD_UNKNOWN	 9	// Enreg : dossier inconnu

#define UCMHOST_CR_APPLI_ASK_SOLV_AGAIN			98	// Demande recommencer la solvabilité
#define UCMHOST_CR_APPLI_ASK_NEW_SELECTION		99	// Demande new selection other AID

//ucTest
#define UCMHOST_CARD_REAL	0
#define UCMHOST_CARD_TEST	1
#define UCMHOST_CARD_TYPE_MONEO	2

//ucTypeCardStruct
#define	UCMHOST_CARD_UNKNOWN 0
#define	UCMHOST_CARD_EMV      	1
#define	UCMHOST_CARD_B0      	 2
#define	UCMHOST_CARD_MONEO    3
#define	UCMHOST_CARD_GEN       4
#define   UCMHOST_CARD_EMV_INFO_TLV 5

#define UCMHOST_MAX_SIZE_CARD_INFO 250
/* Max size struct less than UCMHOST_MAX_SIZE_CARD_INFO */
typedef struct
{
	unsigned char ucCodeMotFixe;
	unsigned char ucAdMotFixe[4];
	unsigned char ucCertificat[16];
}T_UCMHOST_CARD_B0;

/* Max size struct less than UCMHOST_MAX_SIZE_CARD_INFO */
typedef struct
{
	unsigned char	 ucCrypto [16];
	S_AID			    AID;
	T_LABEL			 LabelAID;
}T_UCMHOST_CARD_EMV;

/* Max size struct less than UCMHOST_MAX_SIZE_CARD_INFO */
typedef struct
{
	int					iStatus;
#ifdef _EXPORT_	
	TRACK1_BUFFER		track1;  	// track 1 contents
	TRACK2_BUFFER		track2;  	// track 2 contents
	TRACK3_BUFFER		track3;  	// track 3 contents
#else
	BUFFER_PISTE1		track1;  	// track 1 contents
	BUFFER_PISTE2		track2;  	// track 2 contents
	BUFFER_PISTE3		track3;  	// track 3 contents
#endif

} T_UCMHOST_READ_TRACK;

//iStatus
#define UCMHOST_TRACK_OK		    0
#define UCMHOST_TRACK_BUSY	   	 1	// non OK
#define UCMHOST_TRACK_MTNC		   2	// EN mode MTNC
#define UCMHOST_TRACK_NO_CARD		3	 // time out-> no track
#define UCMHOST_TRACK_LUHN	     4	 // wrong key luhn	
#define UCMHOST_TRACK_KO		     5 // pb with parity, digits ...
#define UCMHOST_TRACK_NULL		     6// the track is empty
#define UCMHOST_TRACK_DENIED	   7	// reading denied: the track is known by an application
#define UCMHOST_TRACK_ICC		     8 // ICC reading only
#define UCMHOST_TRACK_CANCEL	   9	// the operation is cancelled

#define UCMHOST_TRACK_SEP 			10 // sperateur
#define UCMHOST_TRACK_NUM 			11	// numerique
#define UCMHOST_TRACK_LRC			12 // LRC
#define UCMHOST_TRACK_PAR			13 // Parite

#define UCMHOST_TRACK_NO_READER		14

#define UCMHOST_MAX_SIZE_CARD_ACCEPT_INFO 300
/* Max size struct less than UCMHOST_MAX_SIZE_ACCEPT_INFO */
typedef struct
{
	unsigned char ucNoContrat[7];
	unsigned char ucNoSA[3];
	unsigned char ucNoSiret[14];
	unsigned char ucTypeActivite[4];
	unsigned char ucTypePaiement[2];
	unsigned char ucTypeSite[8];
	unsigned char ucEnseigne[60+1];
	unsigned char ucEnteteTicket[50+1];
	unsigned char ucPiedTicket[50+1];
	unsigned char ucCrVerifAcc[2];
} T_UCMHOST_CARD_ACCEPT;

#define UCMHOST_MAX_SIZE_CARD_APPLI_INFO 100
/* Max size struct less than UCMHOST_MAX_SIZE_CARD_APPLI_INFO */
typedef struct
{
	//transaction
	DATE			   sLocalDate;

	unsigned char	ucTypeTrs[2];
	
	NO_PORTEUR		OwnerNumber;		
	unsigned char	ucEndVal[4];		//// End validity MMAA if JJMMAA blank use ucEndVal2
	unsigned char	ucServiceCode[3];
	
	int				iTrsNumber;
	int				iRemisNumber;

	// contre valeur
	MONTANT			ulAmountCV;		// montant contre Valeur, 0 si non rensigné
	S_MONEY			sCurrencyCV;		// devise contre Valeur

	// montant estimé
	MONTANT			ulAmountEstimat;	// only for enreg */

	// autorisation
	unsigned char	ucAutoNumber[ 6 ];		// 0x00 si non renseigné
	unsigned char	ucForcingCode;          // ASCII

	unsigned char   ucEndVal2[ 6 ] ;    // End validity JJMMAA
	unsigned char   ucRuf1[ 4 ] ;
	
	// card
	unsigned char	ucReaderMode;           /* ascii value */

	//appli
	unsigned short usTASA;
	
} T_UCMHOST_CARD_APPLI2;

typedef struct
{
	union
	{
		T_UCMHOST_CARD_APPLI2 sApp;
		unsigned char ucBuf[ UCMHOST_MAX_SIZE_CARD_APPLI_INFO ] ;	/* Max bytes for all struct */
	} uAppli;
	
	union
	{
		T_UCMHOST_CARD_EMV	sEMV;
		T_UCMHOST_CARD_B0	   sB0;
		T_UCMHOST_READ_TRACK sTrack;
			
		unsigned char ucBuf[ UCMHOST_MAX_SIZE_CARD_INFO ] ;	/* Max bytes for all struct */
	} uCard ;

	//accepteur
	union
	{
		T_UCMHOST_CARD_ACCEPT sAcpt;

		unsigned char ucBuf[ UCMHOST_MAX_SIZE_CARD_ACCEPT_INFO ] ;	/* Max bytes for all struct */
	} uAccept;

}T_UCMHOST_CARD;

typedef struct
{
   unsigned char  ucTypeASCIICardStruct;    /* ASCII value */ 

   unsigned char  ucDataASCIIStruct;   /* structure used for ucDataASCII : ASCII value */
   unsigned short  usDataASCIILg;      /* Length ucDataASCII */

   unsigned char  ucRuf[ 12 ];         /* must initailized with RUFRUFRUF */

	union
	{
		unsigned char ucDataASCII[ UCMHOST_MAX_SIZE_CARD_APPLI_INFO 
                           + UCMHOST_MAX_SIZE_CARD_INFO 
                           + UCMHOST_MAX_SIZE_CARD_ACCEPT_INFO - 16] ;	/* ASCII Only 600 Bytes is authorized for SES1042 */
                           
	} u;

}T_UCMHOST_CARD_GEN;

typedef struct
{
   T_AFFNOM      tAppliName;    /* 12 + 1 */
   unsigned char ucTypeRevalue;  /* '0'=Pas de rechargement '1'=Rechargement express off line '2'='1'=Rechargement express on line */
	DATE			  sLocalDate;
   unsigned char ucLogicalID[ 8 ];
   unsigned char ucMerchant[ 20 ];   
   unsigned char ucH_OR_T_SEQ[ 8 ];
   unsigned char ucCustomer[ 20 ];
   unsigned char ucR_SEQ[ 8 ];
   unsigned char ucL_OR_B_SEQ[ 8 ];
   unsigned char ucR_AND_L_SEQ[ 8 ];

	MONTANT	     ulAmount;             /* trs amount or revalue */
	MONTANT	     ulNewAmount;          /* ou bon de remboursement */
	S_MONEY	     tCurrency;
   unsigned char ucMessage2[ 31 ];

   unsigned char ucCertificat[ 16 ];

   unsigned char ucMessage1[ 20 ]; /* use only 18 byte for result debit */

   unsigned char ucCustomerCB[ 20 ]; /* use only rechargement non express sur carte */
	union
	{
   	unsigned char ucBuf[ UCMHOST_MAX_SIZE_CARD_APPLI_INFO ] ;	/* Max bytes for all struct */
   } uBuf;

} T_UCMHOST_CARD_MONEO;


typedef struct
{
	MONTANT ulEpurseBalance;
}T_UCMHOST_R_DEBIT_DA;

typedef struct
{
	unsigned char ucCr;				/* hexa */
	unsigned char ucDiag;			/* hexa: see chapter 5 of 1042 */
	unsigned char ucUCMDiag;      /* from UCM: 0= OK 1=Service not called 2=Called service returned Error 3=No appli */
	
	unsigned char ucPrinter;	   /* 0=Ok or no paper or out of order */
	unsigned char ucDisplay;        /* 0=Ok or pb */

	unsigned char ucCardInside;     /* 1= Card inside during transaction */

	unsigned char ucMode;			 /* UCMHOST_CARD_TEST or  UCMHOST_CARD_REAL or UCMHOST_CARD_TYPE_MONEO*/
	
	unsigned char ucFunction;	    /* UCMHOST_FCT_SOLV or UCMHOST_FCT_ENREG */

	unsigned char ucTypeCardStruct;	    /* UCMHOST_CARD_UNKNOWN ... */

	unsigned char ucSupport;	    /* SUPPORT_TYPE */
		
	unsigned short usAppName;	    /* NO SEGMENT */
	T_AFFNOM     tAppLibelle;	    /* See 1042: CB, CBEMV, MONEO ... */

	MONTANT	     ulAmount;
	S_MONEY	     tCurrency;

   unsigned char  ucCardHolderLanguage; /* 0xFF not used */
   
	union
	{
		unsigned char ucBuf[ 20 ];
      T_UCMHOST_SOLV_COMP_LOC sLoc;
	} uRuf;
	
	//info
	union
	{
		T_UCMHOST_CARD_GEN   sCardGen; /* v0206 */
		T_UCMHOST_CARD        sCard;
		T_UCMHOST_CARD_MONEO sCardMoneo;
		
		T_UCMHOST_R_DEBIT_DA	 sRDebitDa;
		unsigned char            ucBuf[ UCMHOST_MAX_SIZE_CARD_APPLI_INFO +
										UCMHOST_MAX_SIZE_CARD_INFO +
										UCMHOST_MAX_SIZE_CARD_ACCEPT_INFO];
	}u;
} T_UCMHOST_R_DEBIT;

#define UCMHOST_MAX_SIZE_TLV_DATAV2 608

typedef struct
{
	unsigned char ucCr;				/* hexa */
	unsigned char ucDiag;			/* hexa: see chapter 5 of 1042 */
	unsigned char ucUCMDiag;      /* from UCM: 0= OK 1=Service not called 2=Called service returned Error 3=No appli */
	
	unsigned char ucPrinter;	   /* 0=Ok or no paper or out of order */
	unsigned char ucDisplay;        /* 0=Ok or pb */

	unsigned char ucCardInside;     /* 1= Card inside during transaction */

	unsigned char ucMode;			 /* UCMHOST_CARD_TEST or  UCMHOST_CARD_REAL or UCMHOST_CARD_TYPE_MONEO */
	
	unsigned char ucFunction;	    /* UCMHOST_FCT_SOLV or UCMHOST_FCT_ENREG */

	unsigned char ucTypeCardStruct;	    /* UCMHOST_CARD_UNKNOWN ... */

	unsigned char ucSupport;	    /* SUPPORT_TYPE */
		
	unsigned short usAppName;	    /* NO SEGMENT */
	T_AFFNOM     tAppLibelle;	    /* See 1042: CB, CBEMV, MONEO ... */

	MONTANT	     ulAmount;
	S_MONEY	     tCurrency;

   unsigned char  ucCardHolderLanguage; /* 0xFF not used */
   
	union
	{
		unsigned char ucBuf[ 20 ];
      T_UCMHOST_SOLV_COMP_LOC sLoc;
	} uRuf;
	
	//info
	union
	{
		T_UCMHOST_CARD_GEN   sCardGen; /* v0206 */
		T_UCMHOST_CARD        sCard;
		T_UCMHOST_CARD_MONEO sCardMoneo;
		
		T_UCMHOST_R_DEBIT_DA	 sRDebitDa;
		unsigned char            ucBuf[ UCMHOST_MAX_SIZE_CARD_APPLI_INFO +
										UCMHOST_MAX_SIZE_CARD_INFO +
										UCMHOST_MAX_SIZE_CARD_ACCEPT_INFO]; /* 643 */
	}u;

   /* TLV v0230 */
   unsigned short usTLVLg;
   unsigned short usTLVType; 

	union
	{
		unsigned char  ucTLVData[ UCMHOST_MAX_SIZE_TLV_DATAV2 ]; /* ASCII */
	}uTlvPay;

} T_UCMHOST_R_DEBITV3;

// ucCr
#define R_DEBIT_KO            1        /* not used for vending  */

/************************************/
/**************** STATUS ************/
/************************************/
typedef struct
{
	unsigned char ucUCM;       /* exemple UCMHOST_STATE_MAINTENANCE */
	unsigned char ucM2OS;      /* Gest state */
	unsigned char ucICC;			/* Card present = UCMHOST_ICC_IN | UCMHOST_ICC_HS*/
	unsigned char ucNetwork;	/*  */
	unsigned char ucPrinter;	/* HS or no paper */
	unsigned char ucPinpad;	   /* OK = 0 HS=1 */
	unsigned char ucDisplay;	/* OK = 0 */
	unsigned char ucDevice;	   /* Other device 0=Ok else pb */
   unsigned char ucPayState;  /* v0123 */
   unsigned char ucRuf;       /* v0123 */
} T_UCMHOST_STATUS_UCM;

//ucICC
#define UCMHOST_ICC_OUT			0
#define UCMHOST_ICC_IN			1
#define UCMHOST_ICC_HS			2
		
/* ucUCM  */
#define UCMHOST_STATE_IDLE		0
#define UCMHOST_STATE_START		1
#define UCMHOST_STATE_BUSY		2
#define UCMHOST_STATE_MAINTENANCE 3
#define UCMHOST_STATE_TLC		4
#define UCMHOST_STATE_TLP		5
#define UCMHOST_STATE_DOWNLOAD	6
#define UCMHOST_STATE_HS	 7

/* Network */
#define UCMHOST_NETWORK_OK		0
#define UCMHOST_NETWORK_KO		1
#define UCMHOST_NETWORK_START	2
#define UCMHOST_NETWORK_ONLINE	3

/* device */
#define UCMHOST_DEVICE_OK		0

/* Printer */
#define UCMHOST_PAPER_OK		0
#define UCMHOST_PAPER_KO		1
#define UCMHOST_PRINTER_KO		2

/******************************************/
/************* OTHER  ********************/
/******************************************/
/*  values of UCM status (set by UCMC and not others applications)*/
/* #define UCMHOST_CR_OK				0	DEFINED */
#define UCMHOST_CR_KO				1	// UCM KO
#define UCMHOST_CR_MAINTENANCE		2	// UCM is on maintenance
#define UCMHOST_CR_PB_SOFTWARE		3	// UCM software isn't functional (DLL missing...)
#define UCMHOST_CR_OVERRUN			4	// UCM isn't able to manage the request
#define UCMHOST_CR_MSG_UNKNOWN		5	// UCM recieves message unknown from host

/* ucUCM  */
#define UCMHOST_CANCEL_OK		    0
#define UCMHOST_CANCEL_IMPOSSIBLE 1
#define UCMHOST_CANCEL_KO_MTNC    2
#define UCMHOST_CANCEL_KO_REFUSED 3


/******************************************/
/************* SPEED NEGOCIATION *********/
/******************************************/
typedef struct
{
	unsigned long ulSpeed;		/* exemple 19200 for 19200 bauds */
} T_UCMHOST_SPEED_DIAL;

typedef struct
{
	unsigned char ucStatus;
} T_UCMHOST_R_SPEED_DIAL;

/*  values of UCM status */
#define UCMHOST_CR_SPEED_OK		0	   /* OK */
#define UCMHOST_CR_SPEED_KO		1	   /* NOT OK */
#define UCMHOST_CR_SPEED_NOT_READY	2	/* NOT READY and maintenance */
#define UCMHOST_CR_SPEED_IMPOSSIBLE 3	/* Request impossible */


/************************************/
/******** CONSOLIDATION       ******/
/************************************/
typedef struct
{
	unsigned char ucCr;					/* non renseigné lors de la demande */
	unsigned char ucRuf;					/* non renseigné */

	unsigned short usAppName ;	    /* NO SEGMENT */
	T_AFFNOM     tAppLibelle;	

	unsigned long   ulAmount ;
	T_COD_MONEY  tCodeMoney;
	NO_PORTEUR		OwnerNumber;	
} T_UCMHOST_CONSO;

// ucCr
#define	UCMHOST_CONSO_OK			0
#define	UCMHOST_CONSO_KO			1
#define	UCMHOST_CONSO_KO_CANCEL			2

/************************************/
/******** CANCEL              ******/
/************************************/
typedef struct
{
	unsigned char ucCr;
	unsigned char ucRuf;
} T_UCMHOST_R_CANCEL;	

/************************************/
/******** NEW DATE            ******/
/************************************/
typedef struct
{
	DATE sDate;
} T_UCMHOST_NEW_DATE;	

typedef struct
{
	unsigned char ucCr;
} T_UCMHOST_R_NEW_DATE;	

/* ucCr */
#define UCMHOST_DATE_OK			     0
#define UCMHOST_DATE_KO			     1 /* Not dispo */
#define UCMHOST_DATE_KO_MTNC			2 /* Ko because of maintenance */
#define UCMHOST_DATE_KO_REFUSED	3 /* Ko refuse because transaction files not empty */
#define UCMHOST_DATE_KO_DATA	   4 /* pb size or format */
#define UCMHOST_DATE_KO_WRITE	 5  /* write date ko */

/************************************/
/****** FTC APP TELECOLLECTE *******/
/************************************/
#define UCMHOST_MAX_SIZE_FCTAPP_ACCEPT_INFO 250
/* Max size struct less than UCMHOST_MAX_SIZE_MTNC_ACCEPT_INFO */
typedef struct
{
	unsigned char ucEnteteTicket[50+1];
	DATE        sDate;
	unsigned char ucNoContrat[7];
	unsigned char ucNoSiret[14];
	unsigned char ucTypeActivite[4];
	unsigned char ucTypePaiement[2];
	unsigned char ucTypeSite[8];	
	unsigned char ucNoSA[3];
	unsigned char ucReponse[32+1];
	unsigned char ucPiedTicket[50+1];
} T_UCMHOST_FCTAPP_ACCEPT;

#define UCMHOST_MAX_SIZE_FCTAPP_TRS_INFO 50
/* Max size struct less than UCMHOST_MAX_SIZE_MTNC_ACCEPT_INFO */
typedef struct
{
		int	   iNoSequenceAcq;
		int	   iNoRemise;
		int       iNoTransac;
		int       iNoTNA;
		S_MONEY tCurrency;
		MONTANT	ulAmount;
} T_UCMHOST_REMISE_CB;

typedef struct
{
	S_MONEY	     tCurrency;
   unsigned char ucRuf;
	MONTANT	     ulAmountTotal;

	unsigned long ulTrs;
	unsigned long ulRevalueOffline;

   unsigned char ucRuf2[20 ];
} T_UCMHOST_FCTAPP_TRS_MONEO;

typedef struct
{
   T_AFFNOM      tAppliName;    /* 12 + 1 */
   unsigned char ucRuf;

	DATE			  sLocalDate;
   unsigned char ucLogicalID[ 8 ];
   unsigned char ucMerchant[ 20 ];   

   unsigned char ucHSEQ[ 8 ];
   unsigned char ucSSEQ[ 8 ];

   unsigned char ucMessage[ 48 ];
} T_UCMHOST_FCTAPP_ACCEPT_MONEO;

#define UCMHOST_MAX_FCTAPP_MAX_TRS_INFO 10

typedef struct
{
	object_info_t   sInfo ;   /* size = 56 */
	unsigned char   ucState ;
	unsigned char   ucTypeCardStruct ;
	
	union
	{
      T_UCMHOST_FCTAPP_ACCEPT_MONEO sAcceptMoneo;
		T_UCMHOST_FCTAPP_ACCEPT sAccept;
		unsigned char ucBuf[ UCMHOST_MAX_SIZE_FCTAPP_ACCEPT_INFO];
	}u;

	unsigned char ucNbTrs;   /* Transaction or "remise" number  less than UCMHOST_MAX_SIZE_FCTAPP_MAX_TRS_INFO */

	unsigned char ucRuf2;
	
	union
	{
		T_UCMHOST_REMISE_CB sCB[UCMHOST_MAX_FCTAPP_MAX_TRS_INFO];
		T_UCMHOST_FCTAPP_TRS_MONEO sMoneo;
		unsigned char ucBuf[ UCMHOST_MAX_SIZE_FCTAPP_TRS_INFO*UCMHOST_MAX_FCTAPP_MAX_TRS_INFO];
	}uTrs ;
	
} T_UCMHOST_APP_TLC_STATE;

/* ucState */
#define UCMHOST_TLC_STATE_OK	             0 /* Last collect OK */
#define UCMHOST_TLC_STATE_NOT_COMPLET	    1 /* Last collect not complete or refused by center */
#define UCMHOST_TLC_STATE_CALL_ERROR	    2 /* or not efficient */
#define UCMHOST_TLC_STATE_NO_CALL	       3 /*  */
#define UCMHOST_TLC_STATE_REFUSED	       4 /* collect refused by center */

typedef struct
{
	object_info_t	sInfo ;
	unsigned char   ucState ;
	unsigned char   ucRuf ;
} T_UCMHOST_APP_TLC_START;

/************************************/
/******   FTC APP TELEPARAM  *******/
/************************************/
#define UCMHOST_MAX_SIZE_FCTAPP_TABLE_INFO 50
/* Max size struct less than UCMHOST_MAX_SIZE_FCTAPP_TABLE_INFO */
typedef struct
{
	unsigned int	uiNo;
	unsigned int	uiVersion;
} T_UCMHOST_TLP_TABLE;

#define UCMHOST_MAX_FCTAPP_MAX_TABLE_INFO 255

typedef struct
{
	object_info_t   sInfo ;
	unsigned char   ucState ;
	unsigned char   ucRuf;
	
	union
	{
		T_UCMHOST_FCTAPP_ACCEPT sAccept;
		unsigned char ucBuf[ UCMHOST_MAX_SIZE_FCTAPP_ACCEPT_INFO];
	}u;

	unsigned char ucAppInit;						/* Not initialized = 0  Initialized = 1 */
	unsigned char ucAppActive;						/* Not active = 0     Active = 1 */
	
	unsigned char ucTLCError[ 4 ];				/* Telecollecte */
	unsigned char ucTLCErrorTable[ 2 ];			/* Table */
	unsigned char ucTLCErrorCnct[ 2 ];			/* Connection */
	
	unsigned char ucNbTable;   /* Transaction or "remise" number  less than UCMHOST_MAX_FCTAPP_MAX_TABLE_INFO */

	unsigned char ucRuf2;   /* */
	unsigned char ucRuf3;   /* */
	
	union
	{
		T_UCMHOST_TLP_TABLE stab[UCMHOST_MAX_FCTAPP_MAX_TABLE_INFO];
		
		unsigned char ucBuf[ UCMHOST_MAX_SIZE_FCTAPP_TABLE_INFO*UCMHOST_MAX_FCTAPP_MAX_TABLE_INFO];
	}uTable ;
	
} T_UCMHOST_APP_TLP_STATE;

/************************************/
/***** FTC APP CONSULTATION *******/
/************************************/
typedef struct
{
	object_info_t   sInfo ;

	unsigned char   ucAppStatus ; 
	unsigned char   ucFileStatus ;
	
	unsigned char   ucRuf[ 20 ] ;
	
} 	T_UCMHOST_APP_CONSULT ; 

/*	ucAppStatus */
#define UCMHOST_APP_STATUS_INIT_ACTIVE			      0
#define UCMHOST_APP_STATUS_INIT_NOT_ACTIVE			   1
#define UCMHOST_APP_STATUS_NOT_INIT_ACTIVE			   2
#define UCMHOST_APP_STATUS_NOT_INIT_NOT_ACTIVE		3
#define UCMHOST_APP_STATUS_NOT_SIGNED				      99

/* ucFileStatus */
#define UCMHOST_APP_FILE_EMPTY			 0
#define UCMHOST_APP_FILE_NOT_EMPTY		 1
#define UCMHOST_APP_FILE_FULL				 2
#define UCMHOST_APP_FILE_NOT_SIGNED     99

#define UCMHOST_NB_MAX_APPLI	10
#define UCMHOST_NB_MAX_APPLI_RECORD	2

typedef struct
{
	object_info_t	sInfo ;
	unsigned char   ucState ;
	unsigned short  usNbRecord ;
	unsigned char   ucRuf ;
} T_UCMHOST_APP_NB_RECORD_LOC;

#define UCMHOST_RECORD_STATE_OK        0 /* OK */
#define UCMHOST_RECORD_STATE_NO_APP	   1 /* no application */
#define UCMHOST_RECORD_STATE_UNKNOWN   2 /*  */

#define UCMHOST_RECORD_MAX_LOC 500

typedef struct
{
	object_info_t	sInfo ;
	unsigned char   ucState ;
	unsigned short  usNbRecords ;
	unsigned char   ucRecords[UCMHOST_RECORD_MAX_LOC][12] ;
} T_UCMHOST_APP_LIST_RECORD_LOC;

typedef struct
{
	object_info_t	sInfo ;
	unsigned char   ucState ;    /*  UCMHOST_RECORD_STATE_OK */
	unsigned char   ucCrCsf ;    /* UCMHOST_RECORD_CRCSF_OK for example  */
	unsigned char   ucRecord[12] ; /* ASCII */
	unsigned char   ucRuf ;
   T_UCMHOST_R_DEBIT sDebit;
} T_UCMHOST_APP_INFO_RECORD_LOC;

typedef struct
{
	object_info_t	sInfo ;
	unsigned char   ucState ;    /*  UCMHOST_RECORD_STATE_OK */
	unsigned char   ucCrCsf ;    /* UCMHOST_RECORD_CRCSF_OK for example  */
	unsigned char   ucRecord[12] ; /* ASCII */
	unsigned char   ucRuf ;
   T_UCMHOST_R_DEBITV3 sDebit;
} T_UCMHOST_APP_INFO_RECORD_LOCV3;

#define UCMHOST_RECORD_CRCSF_OK     1 /* Found */
#define UCMHOST_RECORD_CRCSF_KO	   0 /* not found*/

typedef struct
{
   unsigned short usType;
   unsigned short usLg;

   unsigned char tucData[100];  /* value variable */
} T_UCMHOST_FCTAPP_TLV;

/* 	unsigned char   ucState  */
#define UCMHOST_APP_DATA_STATE_OK        0 /* OK */
#define UCMHOST_APP_DATA_STATE_NO_APP	  1 /* no application */
#define UCMHOST_APP_DATA_STATE_UNKNOWN   2 /* state unknown */
#define UCMHOST_APP_DATA_TYPE_ERROR      4 /*  */

#define UCMHOST_MAX_SIZE_FCTAPP_DATA 2048
typedef struct
{
	unsigned short usNbTLV ;
	unsigned short usLgTLV ;
	unsigned char ucRuf2[4] ;
	union
	{
      T_UCMHOST_FCTAPP_TLV sTLV;
		unsigned char ucBuf[ UCMHOST_MAX_SIZE_FCTAPP_DATA];
	}u;
	
} T_UCMHOST_TOTAL_TLV;

typedef struct
{
	object_info_t   sInfo ;   /* size = 56 */
	unsigned char   ucState ;
	unsigned char   ucRuf1 ;

   T_UCMHOST_TOTAL_TLV sTotalTLV ;
	
} T_UCMHOST_APP_DATA;

typedef struct
{
	unsigned char  ucFunction ;
	unsigned char  ucLibelle[ 21 ] ; /* without zero */
	unsigned short usAppliNumber ;
	unsigned short usRuf1 ;

   T_UCMHOST_TOTAL_TLV sTotalTLV;
	
} T_UCMHOST_HOST_DATA;

/************************************/
/***** FTC APP ........................ *******/
/************************************/
typedef struct
{
	unsigned char ucFunction ;
	unsigned short usAppliNumber ; /* UCMHOST_APP_ALL for all or application_type given by object_info_t */
   
   union 
	{
      unsigned char ucData[ 20 ];
      unsigned char ucRecord[ 12 ];
   } u;

} T_UCMHOST_DEM_FCTAPP;

#define UCMHOST_APP_ALL 0xFFFF

typedef struct
{
	unsigned char ucCr ;
	unsigned char ucRuf ;
	unsigned char ucFunction ;
	unsigned char ucNbAppli ;

	NO_SERIE 	 tSerial ; /* 20+1 */
	
	union 
	{
		T_UCMHOST_APP_TLC_STATE sTLC [ UCMHOST_NB_MAX_APPLI ] ;
		T_UCMHOST_APP_TLC_START sTLCs [ UCMHOST_NB_MAX_APPLI ] ;
		T_UCMHOST_APP_TLP_STATE sTLP [ UCMHOST_NB_MAX_APPLI ] ;
		T_UCMHOST_APP_CONSULT   sAppCo [ UCMHOST_NB_MAX_APPLI ] ;

		T_UCMHOST_APP_NB_RECORD_LOC   sNbRecordLoc [ UCMHOST_NB_MAX_APPLI_RECORD ] ;
		T_UCMHOST_APP_LIST_RECORD_LOC sListRecordLoc [ UCMHOST_NB_MAX_APPLI_RECORD ] ;
		T_UCMHOST_APP_INFO_RECORD_LOC sInfoRecordLoc ;

		T_UCMHOST_APP_DATA   sAppData [ UCMHOST_NB_MAX_APPLI ] ;
	} u;

} T_UCMHOST_FCTAPP;	

/* ucCr */
#define UCMHOST_FCTAPP_CR_OK	        0
#define UCMHOST_FCTAPP_CR_KO	        1	/* Not dispo */
#define UCMHOST_FCTAPP_CR_KO_MTNC	  2	/* Not dispo maintenance */

#define UCMHOST_FCTAPP_CR_KO_NO_SERVICE	  3
#define UCMHOST_FCTAPP_CR_KO_SERVICE_KO	  4
#define UCMHOST_FCTAPP_CR_KO_GETINFO_KO	  5

/* ucFunction */
#define UCMHOST_FCTAPP_TLC_STATUS    1	/* Telecollecte status */
#define UCMHOST_FCTAPP_TLC_R_STATUS  2	/* Telecollecte status CR */
#define UCMHOST_FCTAPP_TLC_START      3	 /* Telecollecte start */
#define UCMHOST_FCTAPP_TLC_R_START   4	/* Telecollecte start CR */

#define UCMHOST_FCTAPP_TLP_STATUS    5	/* Teleparametrage state */
#define UCMHOST_FCTAPP_TLP_R_STATUS  6	/* Teleparametrage state */
#define UCMHOST_FCTAPP_TLP_START      7	/* Teleparametrage start */
#define UCMHOST_FCTAPP_TLP_R_START   8	/* Teleparametrage start CR */

#define UCMHOST_FCTAPP_CONSULT  		 9	 /* Consultation status */
#define UCMHOST_FCTAPP_CONSULT_R    10	/* Consultation status CR */

#define UCMHOST_FCTAPP_NB_RECORD_LOC	11
#define UCMHOST_FCTAPP_NB_RECORD_LOC_R	12

#define UCMHOST_FCTAPP_INFO_RECORD_LOC	13
#define UCMHOST_FCTAPP_INFO_RECORD_LOC_R 14

#define UCMHOST_FCTAPP_LIST_RECORD_LOC	15
#define UCMHOST_FCTAPP_LIST_RECORD_LOC_R	16

#define UCMHOST_FCTAPP_DATA	17
#define UCMHOST_FCTAPP_DATA_R	18

#define UCMHOST_FCTAPP_EVENT	19

#define UCMHOST_FCTAPP_IDLE_EVENT	20


#define UCMHOST_PROTOCOL_INIT 100
#define UCMHOST_PROTOCOL_SEND 101
#define UCMHOST_PROTOCOL_READ 102


/******** APP <->HOST      *****/
typedef struct
{
	unsigned short usAppliNumber ; /* UCMHOST_APP_ALL for all or application_type given by object_info_t */
   int            iSize;
   union 
	{
      unsigned char ucData[ 2048 ];
   } u;

} T_UCMHOST_APP_MSG;

/************************************/
/******** MAINTENANCE MODE    *****/
/************************************/
typedef struct
{
	unsigned char ucCr ;
	unsigned char ucUCM ;
} T_UCMHOST_R_MTNC;

/************************************/
/************* RESTART **************/
/************************************/
typedef struct
{
	int iStatus;
} T_UCMHOST_R_RESTART;	

/************************************/
/*********** CONNEXION **************/
/************************************/

// DEMANDE DE CONNEXION avant version 0113 */
/*typedef struct
{
	unsigned char ucHostType;
	unsigned char ucX25Type;
	unsigned char ucPhone[20+1];
	unsigned char ucAddress[40+1];
	unsigned char ucComplData[50+1];
} T_UCMHOST_X25; */

#define UCMHOST_LG_ADR_COMPLX25 40
#define UCMHOST_LG_ADR_RACCORD  20
#define UCMHOST_LG_ADR_APPEL    40

// DEMANDE DE CONNEXION apres version 0113 */
typedef struct
{
   unsigned char         ucTypeProt;   /* equivalent STR_ETABL_CONNEX type_protocole;  CBCOM V5 / V42A */
   unsigned char         ucTypePad;    /* equivalent STR_ETABL_CONNEX type_PAD EBA / EMA */

	unsigned char         ucTypeCentre; /* Correspond à la raison d'appel Utiliser par exemple UCMHOST_HOST_CAB */ 

   unsigned char         ucLgComplX25; /* equivalent STR_ETABL_CONNEX unsigned char   lgr_data_compl;	longueur de la chaine */
   unsigned char         uctComplX25[ UCMHOST_LG_ADR_COMPLX25 ]; 	/* equivalent STR_ETABL_CONNEX  STR_COMP_X25    data_compl_X25 buffer ipdu_identif_out */

	unsigned char         uctRaccord[ UCMHOST_LG_ADR_RACCORD ];   /* equivalent STR_ETABL_CONNEX  adr_raccord; 	numero_PAD */
	unsigned char         ucLgRaccord;  /* equivalent STR_ETABL_CONNEX lgr_adr_raccord */

	unsigned char         ucLgAppel;    /* equivalent STR_ETABL_CONNEX lgr_adr_appel */
	unsigned char         uctAppel[ UCMHOST_LG_ADR_APPEL ];     /* equivalent STR_ETABL_CONNEX adr_appel; numero_X25 */

   unsigned char         ucTimer;      /* equivalent STR_ETABL_CONNEX timer_TNR valeur de l'init timer 		*/

   unsigned char         ucRuf[ 40 ] ;
}T_UCMHOST_X25 ;

/* ucTypeProt See ccext.h from sdk
#define CC_PROT_V42A   0x01
#define CC_PROT_CB2A   0x02
#define CC_PROT_CBCOM  0x03
#define CC_PROT_CBSA   0x04
#define CC_PROT_CBPR   0x10
#define CC_PROT_CAPR   0x11
#define CC_PROT_SVPR   0x12
#define CC_PROT_SFPR   0x13
#define CC_PROT_CHPR   0x14
#define CC_PROT_MULTI  0x15
*/

/* ucTypeCentre See cb2a_cmp.h from sdk
#define PAS_DE_SERVICE              0
#define SERVICE_TELECOLLECTE        1
#define SERVICE_TELECHARGEMENT      2
#define SERVICE_TELEPARAMETRAGE     3
#define SERVICE_AUTORISATION        4
*/

/* ucTypePad See ccext.h from sdk
#define CC_PAD_IP  3
#define CC_PAD_EBA 2
#define CC_PAD_EMA 1
#define CC_NUM_PAD 20 */


typedef struct
{
	unsigned char ucNetwork;
	union
	{
		T_UCMHOST_X25	hostX25;
		//T_UCMHOST_IP;
		unsigned char ucData[ 200 ] ;
	}u;

} T_UCMHOST_D_CONNECT;

/* ucNetwork */
#define	UCMHOST_NET_X25	 0 //T_UCMHOST_X25
#define	UCMHOST_NET_IP	 1 //T_UCMHOST_IP

// REPONSE A LA DEMANDE DE CONNEXION
typedef struct
{
	unsigned char ucStatusCn;
	unsigned char ucStatusHost;	/* RUF */

	union
	{
		unsigned char ucData[ 50 ] ;	/* RUF */
	}u;
	
} T_UCMHOST_R_CONNECT;

//ucStatusCn
#define UCMHOST_CN_OK			0
#define UCMHOST_CN_KO			1 // pb unknown
#define UCMHOST_CN_PBX25		2
#define UCMHOST_CN_CANCEL		3		
#define UCMHOST_CN_NODIALTONE	4
#define UCMHOST_CN_NOCARRIER	5
#define UCMHOST_CN_HANGUP		6
#define UCMHOST_CN_BUSY			7
#define UCMHOST_CN_BLIND		8
#define UCMHOST_CN_NOANSWER	9

// ucStatusHost
#define UCMHOST_MTNC_OK					    0
#define UCMHOST_MTNC_KO_MTNC			    1 /* yet in mtnc */
#define UCMHOST_MTNC_KO_NOT_SUPPORTED	 2 /*  */
#define UCMHOST_MTNC_KO_BUSY	          3 /*  */
#define UCMHOST_MTNC_KO_OUT_OF_ORDER    4 /*  */

#define UCMHOST_MODEM_READ_BUFFER_SIZE (UCMHOST_USER_SIZEMAX - (sizeof(unsigned long) + 2*sizeof(unsigned short)))
typedef struct
{
   unsigned short        usTimeOut ;
   unsigned long         ulLength ;
   unsigned short        usRuf ;

   unsigned char         ucBuf[ UCMHOST_MODEM_READ_BUFFER_SIZE ] ;
} T_UCMHOST_CNX_READ ;

/************************************/
/******** DISPLAY               *****/
/************************************/
#define UCMDISPLAY_MAX_LG 200
typedef struct
{
	unsigned char ucChannel;	/* 0xF0=Default channel= UCMC_DISPLAY*/
	unsigned char ucRuf;
   unsigned short usOption;   /* ex: UCMDISPLAY_CLEAR */
   unsigned short usFunction;  /* 0 = normal, 1=no wait or 2 cycling 3=idle message */
   unsigned short usTimeout1; /* time out for first message second */
   unsigned short usTimeout2; /* time out for second message second */
   unsigned short usRuf; 
   unsigned char  ucLgMessage1;
   unsigned char  ucLgMessage2;
	char cMessage1[ UCMDISPLAY_MAX_LG + 1 ] ;
	char cMessage2[ UCMDISPLAY_MAX_LG + 1 ] ;
} T_UCMHOST_MSG_DISPLAY;

// usOption ex: UCMDISPLAY_CLEAR or UCMDISPLAY_APPEND

// usFunction Bit 0=No Wait 1=2 Msg 9=Cycl 17=Idle
#define UCMDISPLAY_FCT_SAMPLE        0x0000   /* waiting */
#define UCMDISPLAY_FCT_NO_WAIT       0x0001
#define UCMDISPLAY_FCT_NO_WAIT2      0x0003   
#define UCMDISPLAY_FCT_NO_WAIT2_CYC  0x0013
#define UCMDISPLAY_FCT_IDLE_MSG      0x0101   /* Change idle message */
#define UCMDISPLAY_FCT_IDLE_MSG_CYC  0x0113   

typedef struct
{
   int            iCr;                 /* FCT_OK if order correct */ 
	unsigned char ucChannel;	         /* 0xF0=Default channel= UCMC_DISPLAY */
	unsigned char ucLangage;            /* UCMDISPLAY_MSG_LANGAGE_MANAGER= default langage of manager */
   unsigned short usMsgNumber;         /* see UCMDISPLAY_ASK_MSG_IDLE .... */
   unsigned short usCmd;               /* 0=Read MSG or 2=Display 2=Change Msg */
   unsigned short usOption;             /* UCMDISPLAY_NO_OPTION or  UCMDISPLAY_CENTER */
   unsigned short usRuf;                 /* */
   unsigned char  ucLgMessage;         /* set par DLL if usCmd = 2 or 0; Set bu UCMC : Max = 64 byte end of string inside */
	char cMessage[ UCMDISPLAY_MAX_LG + 1 ] ;  /* Set 0 by DLL or field if usCmd=change, field by UCMCC */
} T_UCMHOST_ASK_MSG_DISPLAY;

/* usMsgNumber */
#define UCMDISPLAY_ASK_MSG_IDLE             0
#define UCMDISPLAY_ASK_MSG_PROCESSING       1
#define UCMDISPLAY_ASK_MSG_WAIT_CARD        2
#define UCMDISPLAY_ASK_MSG_WAIT_TRACK       3
#define UCMDISPLAY_ASK_MSG_CARD_REJECT      4
#define UCMDISPLAY_ASK_MSG_CARD_INVALID     5
#define UCMDISPLAY_ASK_MSG_CARD_MUTE        6
#define UCMDISPLAY_ASK_MSG_RETREIVE_CARD    7
#define UCMDISPLAY_ASK_MSG_ESCAPE           8
#define UCMDISPLAY_ASK_MSG_CURRENCY_REFUSED 9
#define UCMDISPLAY_ASK_MSG_NO_APPLI         10
#define UCMDISPLAY_ASK_MSG_APPLI_NO_INIT    11
#define UCMDISPLAY_ASK_MSG_APPLI_NO_ACTIVE  12
#define UCMDISPLAY_ASK_MSG_INSERT_CARD      13
#define UCMDISPLAY_ASK_MSG_YOUR_CHOICE      18
#define UCMDISPLAY_ASK_MSG_RUF              19

/* ucLangage */
#define UCMDISPLAY_MSG_LANGAGE_MANAGER  0xFF
#define UCMDISPLAY_MSG_LANGAGE_ENGLISH  0x00
#define UCMDISPLAY_MSG_LANGAGE_FRENCH   0x01
#define UCMDISPLAY_MSG_LANGAGE_SPANISH  0x02

/* usCmd */
#define UCMDISPLAY_MSG_CMD_READ         0x00
#define UCMDISPLAY_MSG_CMD_DISPLAY      0x01
#define UCMDISPLAY_MSG_CMD_CHANGE       0x02

/************************************/
/****** COMMUNICATION STATUS ********/
/************************************/
//#define UCMHOST_DLL_OK			0

/* Used for T_UCMHOST_VM_STATUS */
// MPA 
#define UCMHOST_MPA_COM			1
#define UCMHOST_MPA_NOCOM		2
#define UCMHOST_MPA_NOCOM_NOW	3   /* com has been established but is ko now */

//  **  ucVM **
#define UCMHOST_VM_OK			0x00

#define UCMHOST_VM_PAY_READER	0x01	//	payment by ICC in progress
#define UCMHOST_VM_PAY_COIN   0x02	//	payment by coins in progress
#define UCMHOST_VM_PAY_NEG		0x03	//  negative vend
#define UCMHOST_VM_REVALUE		0x04	//	revalue in progress (ICC+coins)		

//errors
#define UCMHOST_VM_NOINIT		0x81		// display com impossible
#define UCMHOST_VM_MUTE			0x82		// display com impossible
#define UCMHOST_VM_INHIBITED	0x83		// display com impossible
#define UCMHOST_VM_FREE			0x84		// display com impossible
#define UCMHOST_VM_KO			0xFF		// display com impossible

//  **  ucDLL **
#define UCMHOST_DLL_IDLE		0x00	//idle
#define UCMHOST_DLL_SESSION	0x01	// vend session
	//errors
#define UCMHOST_DLL_NOINIT    0x81 	//	no init		--> display not initialized
#define UCMHOST_DLL_INHIBITED 0x82	// init received but ucValidity=0...
#define UCMHOST_DLL_INITKO    0x83	// wrong parameters	--> display not initialized   
#define UCMHOST_DLL_KO        0xFF	//		internal error

//  **  ucCoiner **
#define UCMHOST_COINER_OK		  0	// 
#define UCMHOST_COINER_UNKNOWN  1	// in MDB mode for ex.
#define UCMHOST_COINER_NOCHANGE 2	// OK but no change in coiner
	//errors
#define UCMHOST_COINER_MUTE     0x81	// not present
#define UCMHOST_COINER_INIBITED 0x84	//  
#define UCMHOST_COINER_KO       0xFF	// 

typedef struct
{
	unsigned char ucType;           /* VENDING CBS */
	unsigned char ucMode;           /*  */
	unsigned char ucICC0_Type;	     /* 0=None */
	unsigned char ucICC0_Mode;	     /*  */
	unsigned char ucICC0_Mixte;     /*  */
	unsigned char ucICC0_State;     /* 0=OK else HS */
	unsigned char ucICC1_Type;	     /* 0=None */
	unsigned char ucICC1_Mode;	     /*  */
	unsigned char ucICC1_Mixte;     /*  */
	unsigned char ucICC1_State;     /* 0=OK else HS */
	unsigned char ucSAM0_Type;	     /* 0=None */
	unsigned char ucSAM0_Mode;	     /*  */
	unsigned char ucSAM0_State;     /* 0=OK else HS */
	unsigned char ucSAM1_Type;	     /* 0=None */
	unsigned char ucSAM1_Mode;	     /*  */
	unsigned char ucSAM1_State;     /* 0=OK else HS */
	unsigned char ucSAM2_Type;	     /* 0=None */
	unsigned char ucSAM2_Mode;	     /*  */
	unsigned char ucSAM2_State;     /* 0=OK else HS */
	unsigned char ucDisplay0_Type;  /* 0=None */
	unsigned char ucDisplay0_Mode;  /*  */
	unsigned char ucDisplay0_State; /* 0=OK else HS */
	unsigned char ucDisplay1_Type;  /* 0=None */
	unsigned char ucDisplay1_Mode;  /*  */
	unsigned char ucDisplay1_State; /* 0=OK else HS */
	unsigned char ucPinpad0_Type;  /* 0=None */
	unsigned char ucPinpad0_Mode;  /*  */
	unsigned char ucPinpad0_State; /* 0=OK else HS */
	unsigned char ucPinpad1_Type;  /* 0=None */
	unsigned char ucPinpad1_Mode;  /*  */
	unsigned char ucPinpad1_State; /* 0=OK else HS */
	unsigned char ucPrinter0_Type;  /* 0=None */
	unsigned char ucPrinter0_Mode;  /*  */
	unsigned char ucPrinter0_State; /* 0=OK else HS */
	unsigned char ucPrinter1_Type;  /* 0=None */
	unsigned char ucPrinter1_Mode;  /*  */
	unsigned char ucPrinter1_State; /* 0=OK else HS */
	unsigned char ucModem_Type;  /* 0=None */
	unsigned char ucModem_Mode;  /*  */
	unsigned char ucModem_State; /* 0=OK else HS */
	unsigned char ucLed0_Type;  /* 0=None */
	unsigned char ucLed0_Mode;  /*  */
	unsigned char ucLed0_State; /* 0=OK else HS */
	unsigned char ucLed1_Type;  /* 0=None */
	unsigned char ucLed1_Mode;  /*  */
	unsigned char ucLed1_State; /* 0=OK else HS */
	unsigned char ucBuzzer0_Type;  /* 0=None */
	unsigned char ucBuzzer0_Mode;  /*  */
	unsigned char ucBuzzer0_State; /* 0=OK else HS */
	unsigned char ucBuzzer1_Type;  /* 0=None */
	unsigned char ucBuzzer1_Mode;  /*  */
	unsigned char ucBuzzer1_State; /* 0=OK else HS */
	unsigned char ucMMC_Type;  /* 0=None */
	unsigned char ucMMC_Mode;  /*  */
	unsigned char ucRuf[40];	/*  */
} T_UCMHOST_DEVICE_CONF;

typedef struct
{
   unsigned char  ucDevice;    /* TE_UCM_DEVICE */
   unsigned char  ucRuf;
   unsigned short usRuf;
   T_UCM_DEVICE tDevice;
} T_UCMHOST_DEVICE_INIT;

#define UCMHOST_MAX_SIZE_MDBM_DEVICE 255
#define UCMHOST_MAX_MDBM_DEVICE 5

#define UCMHOST_MAX_MDBM_CHANGER    0x01   /* indice 0 des tableaux UCMHOST_MAX_MDBM_DEVICE */
#define UCMHOST_MAX_MDBM_BILL         0x02
#define UCMHOST_MAX_MDBM_CASHLESS1  0x04
#define UCMHOST_MAX_MDBM_CASHLESS2  0x08
#define UCMHOST_MAX_MDBM_RUF         0x10
#define UCMHOST_MAX_MDBM_ALL         0x1F

typedef struct {
   unsigned char  ucWho; /* ex UCMHOST_MAX_MDBM_CHANGER | UCMHOST_MAX_MDBM_BILL */
   unsigned char  ucRuf;
   unsigned short  usEnable[UCMHOST_MAX_MDBM_DEVICE];
   unsigned short  usOption[UCMHOST_MAX_MDBM_DEVICE];
} T_UCMHOST_MDBM_ACTIVATION ;

typedef struct {
   unsigned char  ucCr;
   unsigned char  ucRuf[3];
   unsigned long ulTubeCoinValue[ 16 ];
   unsigned char ucTubeCoinNumber[ 16 ];
   /* a faie evoluer avec lecteur de billet */
} T_UCMHOST_MDBM_CR_ACTIVATION ;

typedef struct {
      unsigned long ulBalance;
      unsigned short usType;
      unsigned short usRuf;
} T_UCMHOST_MDBM_BALANCE ;

typedef struct {
   unsigned char  ucType;
   unsigned char  ucStatus;
   unsigned char  ucRuf[2];
   int            iError;        /* From device */
   unsigned char  ucLgData;  /* max UCMHOST_MAX_SIZE_MDBM_DEVICE */
   unsigned char  ucDataASCII[ UCMHOST_MAX_SIZE_MDBM_DEVICE ] ; /* Place pour recuperer d'autres infos ex:numero serie, marque */
} T_UCMHOST_MDBM_DEVICE ;

typedef struct {
   unsigned char  ucNBDevice; /* 1 to UCMHOST_MAX_MDBM_DEVICE */
   unsigned char  ucRuf[3];

   T_UCMHOST_MDBM_DEVICE tDevice[ UCMHOST_MAX_MDBM_DEVICE ];
} T_UCMHOST_MDBM_STATUS_DEVICE ;
typedef struct {
    T_UCMHOST_DA_ASK_REVALUE sRev;	
} T_UCMHOST_MDBM_ASK_REVALUE;

typedef struct {
    T_UCMHOST_DA_REC_EPURSE_REVALUE sRev;	
} T_UCMHOST_MDBM_CR_REVALUE;

typedef struct {
   unsigned char  ucForceVend;
   unsigned char  ucRuf[3];

   T_UCMHOST_DA_ASK_DEBIT sDebit;
} T_UCMHOST_MDBM_ASK_DEBIT ;

typedef struct
{
   unsigned char  ucCr;
   unsigned char  ucGiveBack;
   unsigned char  ucRuf[2];

	MONTANT ulEpurseBalance;
}T_UCMHOST_MDBM_R_DEBIT;

typedef struct
{
   T_UCMHOST_DA_CR_DISTRIBUTION sDistri;
}T_UCMHOST_MDBM_CR_DISTRIBUTION ;   /*T_UCMC_DA_CR_DISTRIBUTION;*/

typedef struct
{
	MONTANT ulAmountToGive;
	MONTANT ulAmountGiven;
}T_UCMHOST_MDBM_CR_GIVE_BACK;

#define UCMHOST_DEVICE_CMD_NB_MAX_APPLI 30
typedef struct
{
   unsigned short usNb;
   unsigned short usNbMax;
	object_info_t   sInfo[ UCMHOST_DEVICE_CMD_NB_MAX_APPLI ]  ;
} 	T_UCMHOST_DEVICE_CMD_LISTE_APP ; 

#define UCMHOST_DEVICE_CMD_LIST                 0x0001
#define UCMHOST_DEVICE_CMD_MDBM_STATUS       0x0010
#define UCMHOST_DEVICE_CMD_MDBM_CR_STATUS    0x0011
#define UCMHOST_DEVICE_CMD_MDBM_ACTIVATION   0x0012
#define UCMHOST_DEVICE_CMD_MDBM_GIVE_BACK    0x0013
#define UCMHOST_DEVICE_CMD_MDBM_BALANCE      0x0013

#define UCMHOST_IAC_SIZEMAX 2032  /*idem UCMC_IAC_HOST2_BUFFER_SIZE */
#define UCMHOST_DEVICE_CMD_BUFFER_SIZE (UCMHOST_IAC_SIZEMAX - ( 8*sizeof(unsigned short) + 4*sizeof(unsigned char) ) )
typedef struct
{
   unsigned short  usToDevice;      /* TE_UCM_DEVICE ex: UCM_DEVICE_HOST */
   unsigned short  usFromDevice;   /* TE_UCM_DEVICE   0xFF from application*/
   unsigned short  usToApp;        /* 0x000 if not for app */
   unsigned short  usFromApp;     /* 0x000 if not from app */
   unsigned short  usCpt;           /* 0 used for big data */
   unsigned char  ucRuf[4];
   unsigned short usRuf;
   unsigned short usCmd;          /* ex: UCMHOSTLIB_CMD_MDBM_PERIPH_STATUS ou UCMHOSTLIB_CMD_PARAM_DA_GET */
   unsigned short usLgData;

   union
	{
		unsigned char ucData[ UCMHOST_DEVICE_CMD_BUFFER_SIZE ] ;	/* RUF */
                                                      /* UCMHOSTLIB_CMD_MDBM_PERIPH_STATUS */
      T_UCMHOST_MDBM_STATUS_DEVICE sMDMStatus;   /* UCMHOSTLIB_CMD_MDBM_CR_PERIPH_STATUS */
      T_UCMHOST_MDBM_ACTIVATION sActivation;       /* UCMHOSTLIB_CMD_MDBM_PERIPH_ACTIVATION */
      T_UCMHOST_MDBM_CR_ACTIVATION sRActivation;  /* UCMHOSTLIB_CMD_MDBM_PERIPH_CR_ACTIVATION */
      T_UCMHOST_MDBM_BALANCE sBalance;            /* UCMHOSTLIB_CMD_MDBM_BALANCE */
      T_UCMHOST_MDBM_R_DEBIT sRDebit;          /* UCMHOSTLIB_CMD_MDBM_CR_DEBIT */
                                                    /* UCMHOSTLIB_CMD_MDBM_END */
      T_UCMHOST_MDBM_ASK_DEBIT sAskDebit;        /* UCMHOSTLIB_CMD_MDBM_ASK_DEBIT */
      T_UCMHOST_MDBM_CR_DISTRIBUTION sDis;         /* UCMHOSTLIB_CMD_MDBM_CR_DISTRIBUTION */
      T_UCMHOST_MDBM_CR_GIVE_BACK sRGB;         /* UCMHOSTLIB_CMD_MDBM_CR_GIVE_BACK */
      T_UCMHOST_MDBM_ASK_REVALUE sAskRevalue;	/* UCMHOSTLIB_CMD_MDBM_ASK_REVALUE */
	  T_UCMHOST_MDBM_CR_REVALUE sRRevalue;		/* UCMHOSTLIB_CMD_MDBM_CR_REVALUE */
	  
      T_UCMHOST_DEVICE_CMD_LISTE_APP sListApp;
	}u;

} T_UCMHOST_DEVICE_CMD ;   /* UCMHOSTLIB_MSG_DEM_DEVICE_CMD */



/************************************/
/************ GENERAL **************/
/************************************/

typedef struct
{
	unsigned short	usWho;
	unsigned short	usType;
	int				iStatus;	
	unsigned int	uiNbApp;
	unsigned int     uiSize;

	union
	{
		unsigned char             *pucData;
		void                      *pvData;
		void                      **ppvData;
		T_UCMHOST_DEBIT           *psDebit;
		T_UCMHOST_R_DEBIT         *psDebit_R;
		T_UCMHOST_R_DEBITV3       *psDebit_RV3;
		T_UCMHOST_STATUS_UCM      *pUCMStatus;
    	T_UCMHOST_DEM_FCTAPP      *pDFctApp;
		T_UCMHOST_FCTAPP          *pFctApp;
		T_UCMHOST_D_CONNECT       *pDConnect;
		T_UCMHOST_R_CONNECT       *pConnect_R;
      T_UCMHOST_CNX_READ        *pCnxRead;
		T_UCMHOST_SPEED_DIAL      *pSpeed;
	 	T_UCMHOST_R_SPEED_DIAL    *pSpeed_R;
	 	T_UCMHOST_R_CANCEL        *pCancel;
    	T_UCMHOST_CONSO           *pConsol;
    	T_UCMHOST_NEW_DATE        *pDate;
    	T_UCMHOST_R_NEW_DATE      *pDate_R;
		T_UCMHOST_R_MTNC          *pRMtnc;
		T_UCMHOST_MSG_DISPLAY     *pDisplay;
      T_UCMHOST_ASK_MSG_DISPLAY *pDisplayAsk;
      T_UCM_PARAM                *pUcmParam;
      T_UCMHOST_DEVICE_CONF      *pConfDevice;
      T_UCMHOST_DEVICE_INIT      *pDeviceInit;
      T_UCMHOST_DEVICE_CMD      *pDeviceCmd;

      /* vending */
      T_UCMHOST_DA_PARAMV5                *pParamDa ;
      T_UCMHOST_DA_PARAM_MSGV3            *pParamDaMsg ;
      T_UCMHOST_DA_PARAM_VMV1              *pParamDaVM ;
      T_UCMHOST_DA_EPURSE_BALANCEV3       *pEPurseBal ;
      T_UCMHOST_DA_CR_EPURSE_REVALUEV3    *pCrRevalue ;
      T_UCMHOST_DA_CR_REC_EPURSE_REVALUE  *pCrRecRevalue ;
      unsigned int                        *puiReason ;
      int                                 *piCr ;
      T_UCMHOST_APP_MSG                   *pAppMgs ;
      T_UCMHOST_HOST_DATA                 *pHostData ;
      T_UCMHOST_PARAM_DA_DISPLAY         *pHostParamDaDdisplay ;
	}u;
}T_UCMHOST;

#endif
/* end of file*/

