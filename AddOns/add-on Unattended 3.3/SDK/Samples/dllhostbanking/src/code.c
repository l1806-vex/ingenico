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
* @Title: CODE.C
* @Description: exchanges between UCMC and DLL Protocole for banking
* @Reference: 
* @Comment: 
* 
* @author	
* @version	1.0
* @Comment: 
* @date:	2008/02/01
*/
#include "SDK30.h"
#include "UCMTELIUM.h"
#include "UCMHOSTDLL.h"

#include "etat.h"
#include "sendrec.h"
#include "modem.h"
#include "print.h"
#include "display.h"

/* MAX characteres = 5 + NULL end string */
#define _VERSION_ "01.01"

/************************************************************/
/* API : Version for compatibility :            				*/
/************************************************************/
void UcmHostDll_GetVersion(unsigned char *version)
{
	strcpy((char *)version,_VERSION_);
}

/************************************************************/
/* API: UCMC sends severals commandes and messages 			*/
/************************************************************/
void UcmHostDll_Cmd(int *piRet_p, unsigned short usCmd_p, int iLg1_p, void* vpPar1_p, 
		int iLg2_p, void* vpPar2_p )
{
	*piRet_p = usCmd_p ; /* Renvoie le numéro de la commande demandee */

	switch( usCmd_p )
	{
		case UCMHOST_CLEAR:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;
		break;

		case UCMHOST_CLOSE:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;		
			break;
		case UCMHOST_INIT:
			*piRet_p = iSENDREC_Init( (T_UCM_DEVICE *)vpPar1_p );
		break;
		
		case UCMHOST_MASK:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;
		break;
		
		case UCMHOST_WAIT_MSG:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;
		break;

		case UCMHOST_SEND:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;			
		break;

		case UCMHOST_SEND_MSG:
			*piRet_p = iSENDREC_UCMC_Send_Msg( ( T_UCMHOST *) vpPar1_p ) ;
		break;

		case UCMHOST_READ_MSG:
			*piRet_p = iSENDREC_UCMC_Read_Msg( ( T_UCMHOST *) vpPar1_p ) ;
		break;

		case UCMHOST_READ:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;
		break;

		case UCMHOST_START:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;
		break;

		case UCMHOST_DLL_STATUS:
			*piRet_p = iSENDREC_UCMC_Get_DLL_Status( (T_UCMHOST_MPA_STATUS *) vpPar1_p ) ;
		break;

		case UCMHOST_STOP:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;
		break;

		case UCMHOST_SUSPEND:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;
		break;

		case UCMHOST_TEST:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;
		break;

      case UCMHOST_STOP_REC:
         *piRet_p = FCT_OK;
      break;

      case UCMHOST_START_REC:
         *piRet_p = FCT_OK;
      break;

		/*********************************************/
		/*           UCMC status                     */
		/*********************************************/
		case UCMHOST_UCM_STATUS:
			*piRet_p = iSENDREC_UCMC_Give_Status( ( T_UCMHOST_STATUS_UCM *) vpPar1_p ) ;
		break;

		/*********************************************/
		/*           DISPLAY on HOST                 */
		/*********************************************/
		case UCMHOST_DISPLAY_MSG:
			*piRet_p = iDisplay_UCMC_Msg( ( T_UCMHOST *) vpPar1_p ) ;
		break;

		/*********************************************/
		/*           PRINTER on HOST                */
		/*********************************************/
		case UCMHOST_PRINT_MSG:
			*piRet_p = iPrint_UCMC_Msg( ( T_UCMHOST *) vpPar1_p ) ;
		break;
		
		/*********************************************/
		/*           CAM on HOST                     */
		/*********************************************/
		case UCMHOST_ICC_MSG:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;
		break;

		/*********************************************/
		/*           PINPAD on HOST                 */
		/*********************************************/
		case UCMHOST_PINPAD_MSG:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;
		break;

		/*********************************************/
		/*           BUZZER on HOST                 */
		/*********************************************/
		case UCMHOST_BUZZER_MSG:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;
		break;

		/*********************************************/
		/*           LED on HOST                     */
		/*********************************************/
		case UCMHOST_LED_MSG:
			*piRet_p = UCMHOSTLIB_ERR_CMD_NOT_AUTHORIZED;
		break;

		/*********************************************/
		/*           MODEM on HOST                 */
		/*********************************************/
		case UCMHOST_MODEM_CONNECT:
			*piRet_p = iModem_UCMC_Cnx( ( T_UCMHOST *) vpPar1_p ) ;
		break;

		case UCMHOST_MODEM_DISCONNECT:
			*piRet_p = iModem_UCMC_Dcnx( ( T_UCMHOST *) vpPar1_p ) ;			
		break;

		case UCMHOST_MODEM_WRITE	:
			*piRet_p = iModem_UCMC_Write( ( T_UCMHOST *) vpPar1_p ) ;			
		break;

		case UCMHOST_MODEM_READ:
			*piRet_p = iModem_UCMC_Read( ( T_UCMHOST *) vpPar1_p ) ;			
		break;

		case UCMHOST_MODEM_STATUS:
			*piRet_p = iModem_UCMC_Status( ( T_UCMHOST *) vpPar1_p ) ;			
		break;

		default:
			*piRet_p = UCMHOSTLIB_ERR_CMD_UNKNOWN;
			break;
	}

}


