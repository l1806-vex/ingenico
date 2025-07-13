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

#include "sendrec.h"
#include "code.h"

static   t_topstack     *gsTaskHdl2;

/*
------------------------------------------------------------
*
*       PURPOSE: This routine send and receive host data
*
*       PARAMETER: 
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
Word sSENDREC_Task(void)
{
unsigned short usMsg;
int iRet;
unsigned char ucMyText[ 100 ] ;
unsigned char ucVersion[ 20 ];
unsigned char ucMsgData[ UCMHOST_USER_SIZEMAX ];
int iMsgSending;

	/* Les com doivent être lancee dans la tache pour qu'elle soit proprietaire */
	iRet = iSENDREC_InitCom( ) ;
	iMsgSending = 0;
	
	if( iRet == FCT_OK )
	{
		while ( 1 )
		{
		   /* FIRST OF ALL CHECK IF THERE IS SOME MESSAGE UCMC->HOST IN FIFO */
			if( iSENDREC_Is_Open( 0xFF ) == FCT_OK )
			{
				/* Pas d'emisson si message en creation */
				if( iSENDREC_FIFO_HOST_Msg_Is_Creation() == 0 )
				{
					if( ( iSENDREC_FIFO_HOST_Is_Msg_To_Send_Waiting() != 0 ) && (iMsgSending == 0) )
					{
						iMsgSending = 1;
						iRet = iSENDREC_FIFO_HOST_Task_Send_Msg();
				
						iSENDREC_FIFO_HOST_Set_Msg_Sent();
						
						iMsgSending = 0;
					}
				}
		
   		   /* CHECK IF THERE IS SOME MESSAGE HOST->UCMC */
				usMsg = usSENDREC_Task_Is_Msg_From_HOST( ucMsgData ) ;
				sprintf((char*)ucMyText, "%04X", usMsg ) ;


				switch( usMsg )
				{
					case 0:
						break;

					case UCMHOSTLIB_MSG_DEM_SOLVED:
						iSENDREC_Msg_Creation( SEND_MSG_ACK, ucMyText, 4 ) ;
					break;

					case UCMHOSTLIB_MSG_DEM_ENREG:
						iSENDREC_Msg_Creation( SEND_MSG_ACK, ucMyText, 4 ) ;
					break;

					case UCMHOSTLIB_MSG_DEM_STATUS:
						iSENDREC_UCMC_Give_Status( NULL ) ;
					break;
					
					case UCMHOSTLIB_MSG_DEM_MTNC:
						iSENDREC_Msg_Creation( SEND_MSG_ACK, ucMyText, 4 ) ;
					break;

					case UCMHOSTLIB_MSG_REP_CONSO:
						iSENDREC_Msg_Creation( SEND_MSG_ACK, ucMyText, 4 ) ;
					break;

					case UCMHOSTLIB_MSG_DEM_RESTART:
						iSENDREC_Msg_Creation( SEND_MSG_ACK, ucMyText, 4 ) ;
					break;

					case UCMHOSTLIB_MSG_DEM_CANCEL:
						iSENDREC_Msg_Creation( SEND_MSG_ACK, ucMyText, 4 ) ;
					break;

					case UCMHOSTLIB_MSG_DEM_VERSION:
						UcmHostDll_GetVersion(&ucVersion[0]);
						sprintf((char *)ucMyText, "DLL Version DLL=%s", ucVersion ) ;
						iSENDREC_Msg_Creation( UCMHOSTLIB_MSG_DATA, ucMyText, strlen( (char*)ucMyText) ) ;
					break;

					case UCMHOSTLIB_MSG_DEM_CHGT_DATE:
						iSENDREC_Msg_Creation( SEND_MSG_ACK, ucMyText, 4 ) ;
					break;

					case UCMHOSTLIB_MSG_DEM_FCTAPP:
						iSENDREC_Msg_Creation( SEND_MSG_ACK, ucMyText, 4 ) ;
					break;

					case UCMHOSTLIB_MSG_DISPLAY:
						iSENDREC_Msg_Creation( SEND_MSG_ACK, ucMyText, 4 ) ;
					break;

               case UCMHOSTLIB_MSG_ASK_CHANGE_IDLE_MSG:
						iSENDREC_Msg_Creation( SEND_MSG_ACK, ucMyText, 4 ) ;
					break;

					case UCMHOSTLIB_MSG_DEM_ISO2:
						iSENDREC_Msg_Creation( SEND_MSG_ACK, ucMyText, 4 ) ;
					break;

					case 0xFFFF:
						iSENDREC_Msg_Creation( SEND_MSG_ACK, NULL, 0 ) ;
					break;
					
					default:
						iSENDREC_Msg_Creation( SEND_MSG_ACK, NULL, 0 ) ;
					break;
				}

			}
		
			ttestall( 0, 1 );
		} 

		iSENDREC_CloseCom( ) ;

	}
	else
	{

	}
	
	return ( iRet );
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine create task
*
*       PARAMETER: 
*       RETURN: 0  if bad
*               task number
*              
------------------------------------------------------------
*/
int iSENDREC_Redef_task(void)
{
   int num_task_ext;

	gsTaskHdl2 = fork(sSENDREC_Task, NULL, -1);

	num_task_ext = GiveNoTask (gsTaskHdl2);

	return num_task_ext;
}

