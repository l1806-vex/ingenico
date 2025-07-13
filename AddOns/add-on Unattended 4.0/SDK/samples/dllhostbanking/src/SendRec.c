/***
 * Copyright (c) 2004 Sagem Monetel SA, rue claude Chappe,
 * 07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * Sagem Monetel SA has intellectual property rights relating
 * to the technology embodied in this software.  In particular, 
 * and without limitation, these intellectual property rights 
 * may include one or more patents.
 *
 * This software is distributed under licenses restricting 
 * its use, copying, distribution, and decompilation.  
 * No part of this software may be reproduced in any form 
 * by any means without prior written authorization of 
 * Sagem Monetel.
 *
 * @Title:        
 * @Description:
 * @Reference:    
 * @Comment:      
 *
 * @author        
 * @version       
 * @Comment:      
 * @date:         
 */

#include "SDK30.h"
#include "UCMTELIUM.h"
#include "UCMHOSTDLL.h"
#include "UCMCLIB.h"
#include "etat.h"
#include "sendrec.h"
#include "code.h"
#include "task.h"

FILE          			*ghandleCom;

unsigned long gulEvenCom ;
unsigned char gucNoCom ;

T_UCMHOST_STATUS_UCM sStatusUCM;
T_UCMHOST_MPA_STATUS gHostStatus;

unsigned char gucRecBuf [ UCMHOST_USER_SIZEMAX ] ;


#define MAX_BUFFER_SEND (UCMHOST_USER_SIZEMAX * 2 )
int giIndexBufSend ;
unsigned char gucBufSend [ MAX_BUFFER_SEND + 100 ] ;
int giIndexBufToSend ;
int giMsgInCreation ;
int giNumberCreatMsg ;
int giNbMsgToSend ;

unsigned char gucRecBufSave[ UCMHOST_USER_SIZEMAX ] ;
T_UCMHOST gsRecHoteSave;

#undef read_date
unsigned char ucMonBuf[ 500 ] ;

/************************************************************/
/* Example of FIFO: extract a message sent by host 			*/
/* 4 byte = size of message1                                */
/* Date of message1                                         */
/* 4 byte = size of message2                                */
/* Date of message2                                         */
/* 4 byte = size of message3                                */
/* Date of message3                                         */
/* ......                                                   */
/************************************************************/
void SENDREC_FIFO_HOST_Msg_AddBuffer( int iLg_p, unsigned char *pucBuf_p )
{
   union
   {
	   unsigned char ucBuf [ 4 ] ;
	   int			 iLg ;
   } uByteLength ;

	/* Controle si le message tient jusqu'a la fin du buffer */
	if( ( giIndexBufSend + iLg_p + 4 ) > MAX_BUFFER_SEND )
	{
		memset( &gucBufSend[ giIndexBufSend ], 0, 4 ) ; 
			
		giIndexBufSend = 0 ;
	}

	/* Longueur */
	uByteLength.iLg = iLg_p ;
	memcpy( &gucBufSend[ giIndexBufSend ], uByteLength.ucBuf , 4 ) ;
	giIndexBufSend += 4;

	/* Donnee */
	memcpy( &gucBufSend[ giIndexBufSend ], pucBuf_p, iLg_p ) ;
	giIndexBufSend += iLg_p ;

	/* Prochaine longueur a zero */
	uByteLength.iLg = 0;
	memcpy( &gucBufSend[ giIndexBufSend ], uByteLength.ucBuf, 4 ) ;

}

/************************************************************/
/* Example of FIFO: extract a message sent by host 			*/
/* 4 byte = size of message1                                */
/* Date of message1                                         */
/* 4 byte = size of message2                                */
/* Date of message2                                         */
/* 4 byte = size of message3                                */
/* Date of message3                                         */
/* ......                                                   */
/* When message is taken size is set to 0                   */
/************************************************************/
void SENDREC_FIFO_HOST_Msg_ExtractBuffer( int *piLg_p, unsigned char *pucBuf_p, int iMaxLg_p )
{
int iLg;
union /* for length of message */
{
	unsigned char ucBuf [ 4 ] ;
	int			 iLg ;
} uByteLength ;

	/* Length of message */
	memcpy( uByteLength.ucBuf, &gucBufSend[ giIndexBufToSend ],  4 ) ;
	iLg = uByteLength.iLg ;
	if( iLg == 0 )
	{
		/* End */
		giIndexBufToSend = 0;

		memcpy( uByteLength.ucBuf, &gucBufSend[ giIndexBufToSend ],  4 ) ;
		iLg = uByteLength.iLg ;
	}
		
	*piLg_p = iLg ;
	
	/* Reset length of message treated */
	memset( &gucBufSend[ giIndexBufToSend ], 0, 4 ) ;

	/* Check size of buffer to copy */
	if( iLg > iMaxLg_p )
	{
		/* Cut to max size */
		*piLg_p = iMaxLg_p ;
	}

	/* Copy */
	memcpy( pucBuf_p, &gucBufSend[ giIndexBufToSend + 4],  *piLg_p ) ;

	/* New index */
	/* 4 byte are lenth of message */
	if( ( giIndexBufToSend + iLg + 4 ) > MAX_BUFFER_SEND )
	{
		giIndexBufToSend = 0 ;
	}
	else
		giIndexBufToSend = giIndexBufToSend + iLg + 4	;

	
}

int iSENDREC_FIFO_HOST_Msg_Is_Creation( void )
{
	return( giMsgInCreation );
}

void SENDREC_FIFO_HOST_Msg_Creation_Start( void )
{
	giMsgInCreation = 1 ;
}

void SENDREC_FIFO_HOST_Msg_Creation_Finish( void )
{
	giNbMsgToSend ++;

	giMsgInCreation = 0 ;

	giNumberCreatMsg++;

}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine give number messsage wait to be send
*
*       PARAMETER: 	
*					
*       RETURN: number of message waiting
*              
------------------------------------------------------------
*/
int iSENDREC_FIFO_HOST_Is_Msg_To_Send_Waiting( void )
{
	return( giNbMsgToSend ) ;
}

int iSENDREC_UCMC_Get_DLL_Status( T_UCMHOST_MPA_STATUS *psPar1_p )
{
   memcpy( psPar1_p, &gHostStatus, sizeof( T_UCMHOST_MPA_STATUS ) );

   return( FCT_OK);
}


/*
------------------------------------------------------------
*
*       PURPOSE: This routine give number messsage wait to be send
*
*       PARAMETER: 	
*					
*       RETURN: number of message waiting
*              
------------------------------------------------------------
*/
int iSENDREC_FIFO_HOST_Set_Msg_Sent( void )
{
	/* Un message de moins */
	if( giNbMsgToSend > 0 )
		giNbMsgToSend --;

	return( FCT_OK );
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine send data
*
*       PARAMETER: file handle, event, buffer, length
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iSENDREC_Send_buf(FILE *fd_p, unsigned long lEvent_p,
		unsigned char *pucBuf_p, unsigned int iNb_p)
{
int iRet;
unsigned long ulCr_ttestall;

	mask_event( fd_p, COM_FIN_EMI ) ;

	iRet = UCMHOSTLIB_ERR_DLL_WRITE_BUF ;

	if( fwrite((char *)pucBuf_p, 1, iNb_p, fd_p ) == iNb_p)
	{
		ulCr_ttestall = ttestall( lEvent_p, 0 ) ;

		if (ulCr_ttestall & lEvent_p)
      {
			iRet = FCT_OK;
         gHostStatus.iNbMsgSent ++;
      }
		else
			iRet = UCMHOSTLIB_ERR_DLL_WRITE_BUF2 ;			
	}
	else
		iRet = UCMHOSTLIB_ERR_DLL_WRITE_BUF3 ;

   if( iRet != FCT_OK)
   {
      gHostStatus.ucCom = (gHostStatus.ucCom | UCMHOST_MPA_NOCOM );
      gHostStatus.iNbErrSend++;
      gHostStatus.iNbMsgNotSent++;
   }

  return( iRet ) ;
}


/*
------------------------------------------------------------
*
*       PURPOSE: This routine receive data
*
*       PARAMETER: file handle, event, buffer, length
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iSENDREC_Rec_buf(FILE *fd_p, unsigned long lEvent_p,
		unsigned char *pucBuf_p, unsigned int *piNb_p, unsigned int time_out_global)
{
  int iCr;

	iCr = UCMHOSTLIB_ERR_DLL_READ_BUF ;
	
	mask_event ( fd_p, COM_REC_NOT_EMPTY );
  
	*piNb_p = 0;

	do
	{
		/* lecture du caractere */
		*piNb_p += fread ( pucBuf_p + *piNb_p, 1 , UCMHOST_USER_SIZEMAX - *piNb_p, fd_p ) ;
	}
	while( ttestall ( lEvent_p, time_out_global ) == lEvent_p );

	if( *piNb_p != 0 )
   {
		iCr = FCT_OK;
	   gHostStatus.ucCom = UCMHOST_MPA_COM;
      gHostStatus.iNbMsgRece++;
   }
	
	return( iCr );
}


/*
------------------------------------------------------------
*
*       PURPOSE: This routine send data from task
*
*       PARAMETER: void
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iSENDREC_FIFO_HOST_Task_Send_Msg( void )
{
int iRet, iLg ;
unsigned char ucMonBuf[ 500 + 4];

	SENDREC_FIFO_HOST_Msg_ExtractBuffer( &iLg, ucMonBuf , 500 ) ;

	if( iLg != 0 )
		iRet = iSENDREC_Send_buf( ghandleCom, gulEvenCom,
						ucMonBuf, iLg ) ;
	else
	{
		iRet = -1;
		sprintf( (char *)ucMonBuf, "\nError SENDREC_FIFO_HOST_Msg_ExtractBuffer()" ) ;
		iLg = strlen( (char*)ucMonBuf );
		iSENDREC_Send_buf( ghandleCom, gulEvenCom,
						ucMonBuf, iLg ) ;
	}
	return( iRet );
}

#define CMD_SOLV1 "Solvability request 0,01 EUR"
#define CMD_SOLV2 "Solvability request 5,06 EUR"
#define CMD_RECORD1 "Record request 0,01 EUR"
#define CMD_RECORD2 "Record request 4,98 EUR"
#define CMD_DLL_VERSION "DLL Version request"
#define CMD_READ_ISO2 "ISO2 Track read request"
#define CMD_CHGT_DATE "Change Date request"
#define CMD_CONSOLIDATION "Consolidation response"
#define CMD_STATUS "Status request"
#define CMD_RESTART "Restart"
#define CMD_CANCEL "Cancel request" 
#define CMD_MODE_MTNC "Maintenance mode" 
#define CMD_APP_CONSULATION "Consultation application request"
#define CMD_APP_DOWNLOADING_TRS "Downloading transaction status"
#define CMD_APP_DOWNLOADING_TRS_START "Downloading transaction status" 
#define CMD_APP_DOWNLOADING_PAR "Downloading parameters status" 
#define CMD_APP_DOWNLOADING_PAR_START "Downloading parameters start"



void SENDREC_Help_Command( void)
{
	iSENDREC_Msg_Creation_Key_Txt( 's', CMD_SOLV1 );
	iSENDREC_Msg_Creation_Key_Txt( 'S', CMD_SOLV2 );
	iSENDREC_Msg_Creation_Key_Txt( 'e', CMD_RECORD1 );
	iSENDREC_Msg_Creation_Key_Txt( 'E', CMD_RECORD2 );
				
	iSENDREC_Msg_Creation_Key_Txt( 'v', CMD_DLL_VERSION );
				
	iSENDREC_Msg_Creation_Key_Txt( 'i', CMD_READ_ISO2 );
	iSENDREC_Msg_Creation_Key_Txt( 'd', CMD_CHGT_DATE );
	iSENDREC_Msg_Creation_Key_Txt( 'c', CMD_CONSOLIDATION );
	iSENDREC_Msg_Creation_Key_Txt( 't', CMD_STATUS );
	iSENDREC_Msg_Creation_Key_Txt( 'r', CMD_RESTART );
	iSENDREC_Msg_Creation_Key_Txt( 'a', CMD_CANCEL );
	iSENDREC_Msg_Creation_Key_Txt( 'm', CMD_MODE_MTNC );

	iSENDREC_Msg_Creation_Key_Txt( 'C', CMD_APP_CONSULATION );
	iSENDREC_Msg_Creation_Key_Txt( 'H', CMD_APP_DOWNLOADING_TRS );
	iSENDREC_Msg_Creation_Key_Txt( 'I', CMD_APP_DOWNLOADING_TRS_START );
	iSENDREC_Msg_Creation_Key_Txt( 'J', CMD_APP_DOWNLOADING_PAR );
	iSENDREC_Msg_Creation_Key_Txt( 'K', CMD_APP_DOWNLOADING_PAR_START );			
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine say if msg is received from HOST
*
*       PARAMETER: void
*       RETURN: 0  if non msg
*               else msg number
*              
------------------------------------------------------------
*/
unsigned short usSENDREC_Task_Is_Msg_From_HOST( unsigned char *pucData_p )
{
int iRet ;
unsigned int uiNb;
unsigned short usRet;
union
{
	T_UCMHOST_DEBIT sDebit;
	T_UCMHOST_CONSO sConso;
	T_UCMHOST_DEM_FCTAPP sFApp;
	T_UCMHOST_MSG_DISPLAY sDisplay;
	DATE  sDate;
	T_UCMC_IAC_BUZ sBuz;
} u;
int i;

	iRet = iSENDREC_Rec_buf( ghandleCom, gulEvenCom, 
						&gucRecBuf[ 0 ], &uiNb, 10 ) ;
	usRet = 0;
	
	if( uiNb!= 0 )
	{
		memcpy( pucData_p, gucRecBuf, uiNb );
	
		/* Message decorticaged */
		switch( gucRecBuf[ 0 ] )
		{
			case 's':
				usRet = UCMHOSTLIB_MSG_DEM_SOLVED;
		
				u.sDebit.ulAmount = 1;	// 0,01 EUR because posde=2
				u.sDebit.tCurrency.code[0] = '9';
				u.sDebit.tCurrency.code[1] = '7';
				u.sDebit.tCurrency.code[2] = '8';

				u.sDebit.tCurrency.nom[0] = 'E';
				u.sDebit.tCurrency.nom[1] = 'U';
				u.sDebit.tCurrency.nom[2] = 'R';

				u.sDebit.tCurrency.posdec = 2;   /* position of decimal */


				u.sDebit.ucTrsType = DEBIT_TR;
				u.sDebit.ucTrsEntry = NO_ENTRY;
				u.sDebit.ucTrsMode = CARD_PAYMENT ;
				u.sDebit.ucTrsSupport = CHIP_SUPPORT;
				
				u.sDebit.ucFunction = UCMHOST_FCT_SOLV;
				u.sDebit.ucMode = UCMHOST_MODE_TEST;
				u.sDebit.ucClasse = UCMHOST_CLASSE_2_1;

				u.sDebit.ucPrint = 1;		/* Application print receipt*/
				u.sDebit.ucDisplay = 0;       /* RUF */
				u.sDebit.usToWaitingCard = 10;  /* Time out in second if waiting card */
				u.sDebit.usToRemovedCard = 5;  /* Time out in second if waiting retry card */
			 
				u.sDebit.ucAppliNum = 0;

				u.sDebit.ucPowerOn = 1;

				memcpy( &gucRecBufSave[ 0 ], &u.sDebit, sizeof( T_UCMHOST_DEBIT ) ) ;
				
				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_SOLVED;
				gsRecHoteSave.uiSize = sizeof( T_UCMHOST_DEBIT );
				gsRecHoteSave.u.pucData = gucRecBufSave ;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_SOLV1 );
			break;
			case 'S':
				usRet = UCMHOSTLIB_MSG_DEM_SOLVED;
		
				u.sDebit.ulAmount = 506;	
				u.sDebit.tCurrency.code[0] = '9';
				u.sDebit.tCurrency.code[1] = '7';
				u.sDebit.tCurrency.code[2] = '8';

				u.sDebit.tCurrency.nom[0] = 'E';
				u.sDebit.tCurrency.nom[1] = 'U';
				u.sDebit.tCurrency.nom[2] = 'R';

				u.sDebit.tCurrency.posdec = 2;

				u.sDebit.ucTrsType = DEBIT_TR;
				u.sDebit.ucTrsEntry = NO_ENTRY;
				u.sDebit.ucTrsMode = CARD_PAYMENT ;
				u.sDebit.ucTrsSupport = CHIP_SUPPORT;
				
				u.sDebit.ucFunction = UCMHOST_FCT_SOLV;
				u.sDebit.ucMode = UCMHOST_MODE_TEST;
				u.sDebit.ucClasse = UCMHOST_CLASSE_2_1;

				u.sDebit.ucPrint = 1;
				u.sDebit.ucDisplay = 0;
				u.sDebit.usToWaitingCard = 0;   /* Time out in second if waiting card */
				u.sDebit.usToRemovedCard = 0;   /* Time out in second if waiting retry card */
			 
				u.sDebit.ucAppliNum = 0;

				u.sDebit.ucPowerOn = 1;

				memcpy( &gucRecBufSave[ 0 ], &u.sDebit, sizeof( T_UCMHOST_DEBIT ) ) ;
				
				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_SOLVED;
				gsRecHoteSave.uiSize = sizeof( T_UCMHOST_DEBIT );
				gsRecHoteSave.u.pucData = gucRecBufSave;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_SOLV2 );
				
			break;			
			case 'e':
				usRet = UCMHOSTLIB_MSG_DEM_ENREG;
	
				u.sDebit.ulAmount = 1;
				u.sDebit.tCurrency.code[0] = '9';
				u.sDebit.tCurrency.code[1] = '7';
				u.sDebit.tCurrency.code[2] = '8';

				u.sDebit.tCurrency.nom[0] = 'E';
				u.sDebit.tCurrency.nom[1] = 'U';
				u.sDebit.tCurrency.nom[2] = 'R';

				u.sDebit.tCurrency.posdec = 2;

				u.sDebit.ucTrsType = DEBIT_TR;
				u.sDebit.ucTrsEntry = NO_ENTRY;
				u.sDebit.ucTrsMode = CARD_PAYMENT ;
				u.sDebit.ucTrsSupport = CHIP_SUPPORT;
				
				u.sDebit.ucFunction = UCMHOST_FCT_ENREG;
				u.sDebit.ucMode = UCMHOST_MODE_TEST;
				u.sDebit.ucClasse = UCMHOST_CLASSE_2_1;

				u.sDebit.ucPrint = 1;
				u.sDebit.ucDisplay = 0;
				u.sDebit.usToWaitingCard = 0;
				u.sDebit.usToRemovedCard = 0;
			 
				u.sDebit.ucAppliNum = 0;

				u.sDebit.ucPowerOn = 0;

				memcpy( &gucRecBufSave[ 0 ], &u.sDebit, sizeof( T_UCMHOST_DEBIT ) ) ;				
					
				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_ENREG;
				gsRecHoteSave.uiSize = sizeof( T_UCMHOST_DEBIT );
				gsRecHoteSave.u.pucData = gucRecBufSave;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_RECORD1 );
				
			break;

			case 'E':
				usRet = UCMHOSTLIB_MSG_DEM_ENREG;
	
				u.sDebit.ulAmount = 498;
				u.sDebit.tCurrency.code[0] = '9';
				u.sDebit.tCurrency.code[1] = '7';
				u.sDebit.tCurrency.code[2] = '8';

				u.sDebit.tCurrency.nom[0] = 'E';
				u.sDebit.tCurrency.nom[1] = 'U';
				u.sDebit.tCurrency.nom[2] = 'R';

				u.sDebit.tCurrency.posdec = 2;

				u.sDebit.ucTrsType = DEBIT_TR;
				u.sDebit.ucTrsEntry = NO_ENTRY;
				u.sDebit.ucTrsMode = CARD_PAYMENT ;
				u.sDebit.ucTrsSupport = UNKNOWN_SUPPORT;
				
				u.sDebit.ucFunction = UCMHOST_FCT_ENREG;
				u.sDebit.ucMode = UCMHOST_MODE_TEST;
				u.sDebit.ucClasse = UCMHOST_CLASSE_2_1;

				u.sDebit.ucPrint = 1;
				u.sDebit.ucDisplay = 0;
				u.sDebit.usToWaitingCard = 0;
				u.sDebit.usToRemovedCard = 0;
			 
				u.sDebit.ucAppliNum = 0;

				u.sDebit.ucPowerOn = 0;

				memcpy( &gucRecBufSave[ 0 ], &u.sDebit, sizeof( T_UCMHOST_DEBIT ) ) ;				
					
				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_ENREG;
				gsRecHoteSave.uiSize = sizeof( T_UCMHOST_DEBIT );
				gsRecHoteSave.u.pucData = gucRecBufSave;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_RECORD2 );
				
			break;
			
			case 'v':
				usRet = UCMHOSTLIB_MSG_DEM_VERSION;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_DLL_VERSION );
			break;

			case 'i':
				usRet = UCMHOSTLIB_MSG_DEM_ISO2;

				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_ISO2;
				gsRecHoteSave.uiSize = 0;
				gsRecHoteSave.u.pucData = gucRecBufSave;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_READ_ISO2 );

			break;

			case 'd':
				usRet = UCMHOSTLIB_MSG_DEM_CHGT_DATE;

				i = read_date( &u.sDate );

				/* example: Same date but set second to 0 */
				u.sDate.second[0] = '0';
				u.sDate.second[1] = '0';

				u.sDate.minute[0] = '0';
				u.sDate.minute[1] = '0';

				memcpy( &gucRecBufSave[ 0 ], &u.sDate, sizeof( DATE ) ) ;
				
				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_CHGT_DATE;
				gsRecHoteSave.uiSize = sizeof( T_UCMHOST_NEW_DATE );
				gsRecHoteSave.u.pucData = gucRecBufSave ;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_CHGT_DATE );

			break;
			
			case 'c':
				usRet = UCMHOSTLIB_MSG_REP_CONSO;
	
				u.sConso.ucCr = 0;
				u.sConso.ucRuf = 0 ;
				u.sConso.usAppName = 12;				
				memset( u.sConso.tAppLibelle, 'A', sizeof( T_AFFNOM ) );
				u.sConso.ulAmount = 53;
				memset( u.sConso.tCodeMoney, 'B', sizeof( T_COD_MONEY ) );
				memset( u.sConso.OwnerNumber, 'C', sizeof( NO_PORTEUR ) ) ;
				memcpy( &gucRecBufSave[ 0 ], &u.sConso, sizeof( T_UCMHOST_CONSO ) ) ;				

				gsRecHoteSave.usType = UCMHOSTLIB_MSG_REP_CONSO;
				gsRecHoteSave.uiSize = sizeof( T_UCMHOST_CONSO );
				gsRecHoteSave.u.pucData = gucRecBufSave;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_CONSOLIDATION );

			break;
			
			case 't':
				usRet = UCMHOSTLIB_MSG_DEM_STATUS;

				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_STATUS;
				gsRecHoteSave.uiSize = sizeof( T_UCMHOST_STATUS_UCM );
				gsRecHoteSave.u.pucData = gucRecBufSave ;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_STATUS );
			break;
			
			case 'r':	/* Restart */
				usRet = UCMHOSTLIB_MSG_DEM_RESTART;

				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_RESTART;
				gsRecHoteSave.uiSize = 0;
				gsRecHoteSave.u.pucData = gucRecBufSave;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_RESTART );

			break;

			case 'a':	/* annulation */
				usRet = UCMHOSTLIB_MSG_DEM_CANCEL;

				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_CANCEL;
				gsRecHoteSave.uiSize = 0;
				gsRecHoteSave.u.pucData = gucRecBufSave;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_CANCEL );

			break;

			case 'm':
				usRet = UCMHOSTLIB_MSG_DEM_MTNC;
		
				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_MTNC;
				gsRecHoteSave.uiSize = 0;
				gsRecHoteSave.u.pucData = gucRecBufSave;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_MODE_MTNC );

			break;

			case 'C':
				usRet = UCMHOSTLIB_MSG_DEM_FCTAPP;

				u.sFApp.ucFunction = UCMHOST_FCTAPP_CONSULT;
				u.sFApp.usAppliNumber = UCMHOST_APP_ALL; /* All application */

				memcpy( &gucRecBufSave[ 0 ], &u.sFApp, sizeof( T_UCMHOST_DEM_FCTAPP ) ) ;
				
				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_FCTAPP;
				gsRecHoteSave.uiSize = sizeof( T_UCMHOST_DEM_FCTAPP );
				gsRecHoteSave.u.pucData = gucRecBufSave ;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_APP_CONSULATION );
	
			break;

			case 'H':
				usRet = UCMHOSTLIB_MSG_DEM_FCTAPP;

				u.sFApp.ucFunction = UCMHOST_FCTAPP_TLC_STATUS;
				u.sFApp.usAppliNumber = UCMHOST_APP_ALL; /* All application */

				memcpy( &gucRecBufSave[ 0 ], &u.sFApp, sizeof( T_UCMHOST_DEM_FCTAPP ) ) ;
				
				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_FCTAPP;
				gsRecHoteSave.uiSize = sizeof( T_UCMHOST_DEM_FCTAPP );
				gsRecHoteSave.u.pucData = gucRecBufSave;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_APP_DOWNLOADING_TRS );
				
			break;

			case 'I':
				usRet = UCMHOSTLIB_MSG_DEM_FCTAPP;

				u.sFApp.ucFunction = UCMHOST_FCTAPP_TLC_START;
				u.sFApp.usAppliNumber = UCMHOST_APP_ALL; /* All application */

				memcpy( &gucRecBufSave[ 0 ], &u.sFApp, sizeof( T_UCMHOST_DEM_FCTAPP ) ) ;
				
				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_FCTAPP;
				gsRecHoteSave.uiSize = sizeof( T_UCMHOST_DEM_FCTAPP );
				gsRecHoteSave.u.pucData = gucRecBufSave;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_APP_DOWNLOADING_TRS_START );
				
			break;

			case 'J':
				usRet = UCMHOSTLIB_MSG_DEM_FCTAPP;

				u.sFApp.ucFunction = UCMHOST_FCTAPP_TLP_STATUS;
				u.sFApp.usAppliNumber = UCMHOST_APP_ALL; /* All application */

				memcpy( &gucRecBufSave[ 0 ], &u.sFApp, sizeof( T_UCMHOST_DEM_FCTAPP ) ) ;
				
				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_FCTAPP;
				gsRecHoteSave.uiSize = sizeof( T_UCMHOST_DEM_FCTAPP );
				gsRecHoteSave.u.pucData = gucRecBufSave;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_APP_DOWNLOADING_PAR );
			break;

			case 'K':
				usRet = UCMHOSTLIB_MSG_DEM_FCTAPP;

				u.sFApp.ucFunction = UCMHOST_FCTAPP_TLP_START;
				u.sFApp.usAppliNumber = UCMHOST_APP_ALL; /* All application */

				memcpy( &gucRecBufSave[ 0 ], &u.sFApp, sizeof( T_UCMHOST_DEM_FCTAPP ) ) ;
				
				gsRecHoteSave.usType = UCMHOSTLIB_MSG_DEM_FCTAPP;
				gsRecHoteSave.uiSize = sizeof( T_UCMHOST_DEM_FCTAPP );
				gsRecHoteSave.u.pucData = gucRecBufSave;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], CMD_APP_DOWNLOADING_PAR_START );			
			break;
			
			case '?':
				SENDREC_Help_Command( );
			break;
			
			default:
            gHostStatus.iNbErrRece++;

				iSENDREC_Msg_Creation_Key_Txt( gucRecBuf[ 0 ], "Unknown request ?" );
				usRet = 0;
			break;
		}
	}
	
	return( usRet );
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine send msg 
*						Called by API
*       PARAMETER: hote struct
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iSENDREC_UCMC_Send_Msg( T_UCMHOST *pMsg_p )
{
int iRet ;

	iRet = iSENDREC_Msg_Creation( pMsg_p->usType , pMsg_p->u.pucData, pMsg_p->uiSize ) ;

	return( iRet ); 
}


/* TESTER POUR QUI ET REGARDER LE MASK */
/* CHERCHER LE MESSAGE RECU */
/* SI pas dans le mak mettre le type a jour met faire un compte rendu */
/* pas de message recu */
int iSENDREC_UCMC_Read_Msg( T_UCMHOST *pMsg_p )
{
int iRet ;

	if( gsRecHoteSave.usType != UCMHOSTLIB_MSG_NO )
	{
		iRet = FCT_OK ;
		pMsg_p->usType = gsRecHoteSave.usType ;
		pMsg_p->uiSize = gsRecHoteSave.uiSize ;

		pMsg_p->u.pucData = gsRecHoteSave.u.pucData;

		gsRecHoteSave.usType = UCMHOSTLIB_MSG_NO;
	}
	else
	{
		iRet = UCMHOSTLIB_ERR_DLL_NO_MSG ;
		pMsg_p->usType = UCMHOSTLIB_MSG_NO ;
		pMsg_p->uiSize = 0 ;
		pMsg_p->u.pucData = NULL ;
	}
   
   iRet = iSENDREC_Is_Open( 0xFF ) ;

	return( iRet ); 
}


int iSENDREC_UCMC_Give_Status( T_UCMHOST_STATUS_UCM *pNewStatus_p )
{
char ucTemp[ 100 ];
int iRet;

	if( iSENDREC_FIFO_HOST_Msg_Is_Creation() == 0 )
	{
		if( pNewStatus_p != NULL )
			memcpy( &sStatusUCM, pNewStatus_p, sizeof( T_UCMHOST_STATUS_UCM ) );
	
		sprintf( ucTemp, "UCM=%d M2OS=%02d ICC=%d Ppad=%d Disp=%d Prn=%d device=%d",
			sStatusUCM.ucUCM, sStatusUCM.ucM2OS, 
			sStatusUCM.ucICC, sStatusUCM.ucPinpad, sStatusUCM.ucDisplay, 
         sStatusUCM.ucPrinter, sStatusUCM.ucDevice ) ;

		iRet = iSENDREC_Msg_Creation( SEND_MSG_STATUS , ucTemp, strlen( ucTemp) ) ;
	}
	else
	{
		iRet = UCMHOSTLIB_ERR_DLL_MSG_CREAT;
	}
	
	return( iRet );
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine create msg header
*
*       PARAMETER: wich Device
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iSENDREC_Header( char cDevice_p, unsigned short usType_p, 
	int iLgData_p, unsigned char *pucBufHeader_p )
{
int iRet, i ;
DATE  sDate;
char cBuf[ 60 ];

	iRet = 0 ;
	
	pucBufHeader_p[ 0 ] = 0x0D;
	pucBufHeader_p[ 1 ] = 0x0A;
	pucBufHeader_p[ 2 ] = cDevice_p;
	pucBufHeader_p[ 3 ] =':';

	i = read_date( &sDate );
		
	sprintf( (char*)&pucBufHeader_p[ 4 ], "%04X LG=%04X %04d %.2s:%.2s:%.2s=",
		usType_p, iLgData_p, giNumberCreatMsg, 
		sDate.hour, sDate.minute, sDate.second );

	iRet = 4 + strlen( (char*)&pucBufHeader_p[ 4 ] ) ;

	/* Test de la date */
	if( ( sDate.hour[ 1 ] == '?' ) || ( sDate.hour[ 0 ] == '?' ) )
	{
		sprintf( cBuf, "HOTETEST iSENDREC_Header %d=date%.2s:%.2s:%.2s/n", i,
			sDate.hour, sDate.minute, sDate.second) ;
		
		upload_diagnostic_txt( (unsigned char*)cBuf ) ;

	}
	
	return ( iRet );
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine send msg for hote
*
*       PARAMETER: file handle, event, buffer, length
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iSENDREC_Msg_Creation( unsigned short usType_p , void *pvData_p, int iLgData_p )
{
int iRet, i,j ;
int iHeader ;
T_UCMHOST_R_DEBIT *pDebit;
T_UCMHOST_FCTAPP *pFctApp;
T_UCMHOST_R_MTNC *pMtnc;
T_UCMHOST_STATUS_UCM *pStatus;
T_UCMHOST_CONSO *pConso;
unsigned char *pChar;
T_UCMHOST_READ_TRACK *pTrack;

	iRet = FCT_OK ;
	i = 0;
	
	SENDREC_FIFO_HOST_Msg_Creation_Start( ) ;
	
	iHeader = iSENDREC_Header( 'H', usType_p, iLgData_p, &ucMonBuf[ 0 ] );
	
	switch( usType_p )
	{
		case UCMHOSTLIB_MSG_DATA:
		case SEND_MSG_STATUS:
			if( iLgData_p <= (400 -iHeader) )
			{
				i = iLgData_p;
			}
			else
			{
			   i = (400 - iHeader - 1 );
				iRet = UCMHOSTLIB_ERR_DLL_DATA_LG;
			}

			if( i != 0 )
			{
				memcpy( &ucMonBuf[ iHeader ], pvData_p, i );
			}
			else	
				iRet = UCMHOSTLIB_ERR_DLL_DATA_LG_0;

			ucMonBuf[ iHeader + i ] = 0 ;
			
			break;
				
		case SEND_MSG_ACK:
			sprintf( (char*)&ucMonBuf[ iHeader ], "ACK" );
			break;
			
		case SEND_MSG_NACK:
			sprintf( (char*)&ucMonBuf[ iHeader ], "NACK" );
			break;
			
		case UCMHOSTLIB_MSG_REP_SOLVED:
			pDebit = (T_UCMHOST_R_DEBIT*)pvData_p;
			
			sprintf( (char*)&ucMonBuf[ iHeader ], "R Solv Amount=%lu %s Cr=%d Diag=%d DiagUCM=%d",
				pDebit->ulAmount, pDebit->tAppLibelle, pDebit->ucCr, pDebit->ucDiag, pDebit->ucUCMDiag );
			
			break;

		case UCMHOSTLIB_MSG_REP_STATUS:
			pStatus = (T_UCMHOST_STATUS_UCM*)pvData_p;

			iSENDREC_UCMC_Give_Status( pvData_p ) ;
			
			break;

		case UCMHOSTLIB_MSG_REP_ENREG:
			pDebit = (T_UCMHOST_R_DEBIT*)pvData_p;

			sprintf( (char*)&ucMonBuf[ iHeader ], "R Record Amount=%lu %s Cr=%d Diag=%d DiagUCM=%d",
				pDebit->ulAmount, pDebit->tAppLibelle, pDebit->ucCr, pDebit->ucDiag, pDebit->ucUCMDiag );
			
			break;

		case UCMHOSTLIB_MSG_DEM_CONSO:
			pConso = (T_UCMHOST_CONSO*)pvData_p;

			sprintf( (char*)&ucMonBuf[ iHeader ], "D CONSO Amount=%lu %s",
				pConso->ulAmount, pConso->tAppLibelle );
			
			break;

		case UCMHOSTLIB_MSG_REP_RESTART:
			sprintf( (char*)&ucMonBuf[ iHeader ], "Restart");
			break;

		case UCMHOSTLIB_MSG_REP_CANCEL:
			pChar = pvData_p;
			sprintf( (char*)&ucMonBuf[ iHeader ], "R CANCEL %d",
				*pChar );

			break;

		case UCMHOSTLIB_MSG_REP_CHGT_DATE:
			pStatus = (T_UCMHOST_STATUS_UCM*)pvData_p;
			
			sprintf( (char*)&ucMonBuf[ iHeader ], "R Chgt Date=%d",
				pStatus->ucUCM );
			
			break;

		case UCMHOSTLIB_MSG_REP_ISO2:
			pTrack = (T_UCMHOST_READ_TRACK*)pvData_p;

			if( pTrack->iStatus == 0 )
				sprintf( (char*)&ucMonBuf[ iHeader ], "R Iso2 Status=%d %c%c%c%c%c%c %s",
					pTrack->iStatus, 
               pTrack->track2[0], pTrack->track2[1], pTrack->track2[2],
               pTrack->track2[3], pTrack->track2[4], pTrack->track2[5], pTrack->track2 );
			else
				sprintf( (char*)&ucMonBuf[ iHeader ], "R Iso2 KO Status=%d %s",
					pTrack->iStatus, &pTrack->track2[0]);
			
			
			break;

		case UCMHOSTLIB_MSG_REP_MTNC:
			pMtnc = (T_UCMHOST_R_MTNC*)pvData_p;

			sprintf( (char*)&ucMonBuf[ iHeader ], "R Mtnc %d %d",
				pMtnc->ucCr, pMtnc->ucUCM);
	
			break;

		case UCMHOSTLIB_MSG_REP_FCTAPP:
			pFctApp = (T_UCMHOST_FCTAPP*)pvData_p;
			
			sprintf( (char*)&ucMonBuf[ iHeader ], "R Ftc%d NbApp=%d Cr=%d Serial=%12s",
				pFctApp->ucFunction, pFctApp->ucNbAppli,  
				pFctApp->ucCr, pFctApp->tSerial );
			
			for( i = 0; i <pFctApp->ucNbAppli; i++ )
			{
				j = strlen( (char*)&ucMonBuf[ iHeader ] ) ;
            ucMonBuf[ iHeader + j ] = 0x0D ;
            ucMonBuf[ iHeader + j + 1 ] = 0x0A ;
            j+= 2;

				switch( pFctApp->ucFunction )
					{
						case UCMHOST_FCTAPP_CONSULT_R:
							sprintf( (char*)&ucMonBuf[ iHeader+ j ], "Name=%.20s crc=%X File=%.20s app=%d file=%d",
								&pFctApp->u.sAppCo[i].sInfo.name[0], 
								pFctApp->u.sAppCo[i].sInfo.crc, 
								&pFctApp->u.sAppCo[i].sInfo.file_name[0],
								pFctApp->u.sAppCo[i].ucAppStatus,
								pFctApp->u.sAppCo[i].ucFileStatus);

						break;
						case UCMHOST_FCTAPP_TLC_R_STATUS:
							sprintf( (char*)&ucMonBuf[ iHeader+ j ], "\nLib=%.10s Ver=%.10s state=%d nbtrs=%d Date%.12s",
								&pFctApp->u.sTLC[i].sInfo.name[0], 
								&pFctApp->u.sTLC[i].sInfo.file_name[0],
								pFctApp->u.sTLC[i].ucState,
								pFctApp->u.sTLC[i].ucNbTrs,
								(char*)&pFctApp->u.sTLC[i].u.sAccept.sDate );

	
						break;
						
						case UCMHOST_FCTAPP_TLC_R_START:
							sprintf( (char*)&ucMonBuf[ iHeader+ j ], "\nLib=%.20s Ver=%.20s state=%d nbtrs=%d",
								&pFctApp->u.sTLC[i].sInfo.name[0], 
								&pFctApp->u.sTLC[i].sInfo.file_name[0],
								pFctApp->u.sTLC[i].ucState,
								pFctApp->u.sTLC[i].ucNbTrs);
							
						break;	
						
						case UCMHOST_FCTAPP_TLP_R_STATUS:
							sprintf( (char*)&ucMonBuf[ iHeader+ j ], "\nLib=%.20s Ver=%.20s state=%d nbtable=%d Date=%.12s",
								&pFctApp->u.sTLP[i].sInfo.name[0], 
								&pFctApp->u.sTLP[i].sInfo.file_name[0],
								pFctApp->u.sTLP[i].ucState,
								pFctApp->u.sTLP[i].ucNbTable,
								(char*)&pFctApp->u.sTLP[i].u.sAccept.sDate
								);

						break;		
						
						case UCMHOST_FCTAPP_TLP_R_START:
						break;	
						
						default:
							sprintf( (char*)&ucMonBuf[ iHeader+ j ], "\nDefault Lib=%.20s Ver=%.20s",
								&pFctApp->u.sAppCo[i].sInfo.name[0], 
								&pFctApp->u.sAppCo[i].sInfo.file_name[0] );
							
						break;
						
					}
			}

			break;
		default:
			sprintf( (char*)&ucMonBuf[ iHeader ], "Message UCMC %04X unknown\n", usType_p);
			iRet = UCMHOSTLIB_ERR_DLL_MSG_UNKNOWN;
			break;

	}

	i = strlen( (char*)&ucMonBuf[ iHeader ] ) ;
	
	SENDREC_FIFO_HOST_Msg_AddBuffer( i + iHeader , &ucMonBuf[ 0 ] ) ;
	
	SENDREC_FIFO_HOST_Msg_Creation_Finish();
	
	return( iRet );
}

int iSENDREC_Msg_Creation_Key_Txt( char cKey, void *pvData_p )
{
int iRet, i ;
int iHeader ;
unsigned char ucBufLoc[ 200 ];

	iRet = FCT_OK ;
	i = 0;
	
	SENDREC_FIFO_HOST_Msg_Creation_Start( ) ;
	
	iHeader = 4;
	ucBufLoc[ 0 ] = 0x0D;
	ucBufLoc[ 1 ] = 0x0A;
	ucBufLoc[ 2 ] = cKey;
	ucBufLoc[ 3 ] =':';
	
	sprintf( (char*)&ucBufLoc[ iHeader ], "%s", (unsigned char*)pvData_p );
	
	i = strlen( (char*)&ucBufLoc[ iHeader ] ) ;
	
	SENDREC_FIFO_HOST_Msg_AddBuffer( i + iHeader , &ucBufLoc[ 0 ] ) ;
	
	SENDREC_FIFO_HOST_Msg_Creation_Finish();
	
	return( iRet );
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine send msg for display
*
*       PARAMETER: file handle, event, buffer, length
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iSENDREC_Msg_Display_Creation( unsigned short usType_p , unsigned char *pvData_p, int iLgData_p )
{
int iRet, i ;
int iHeader;
unsigned char ucMonBuf[ 400 ] ;

	iRet = FCT_OK ;
	i = 0;
	
	SENDREC_FIFO_HOST_Msg_Creation_Start( ) ;
	
	iHeader = iSENDREC_Header( 'D', usType_p, iLgData_p, &ucMonBuf[ 0 ] );
	
	switch( usType_p )
	{
		case UCMHOST_PRINT_MSG:
				
			if( iLgData_p <= (400 -iHeader) )
			{
				i = iLgData_p;
			}
			else
			{
			   i = (400 - iHeader - 1 );
				iRet = UCMHOSTLIB_ERR_DLL_DATA_LG;
			}

			if( i != 0 )
			{
				memcpy( &ucMonBuf[ iHeader ], pvData_p, i );
			}
			else	
				iRet = UCMHOSTLIB_ERR_DLL_DATA_LG_0;

			ucMonBuf[ iHeader + i ] = 0 ;
			
			break;
		default:
			sprintf( (char*)&ucMonBuf[ iHeader ], "Message Display %04X unknown\n", usType_p);
			iRet = UCMHOSTLIB_ERR_DLL_MSG_DISPLAY_UNKNOWN;
			break;

	}

	i = strlen( (char*)&ucMonBuf[ iHeader ] ) ;
	
   /* Add message in FIFO with HOST */
	SENDREC_FIFO_HOST_Msg_AddBuffer( i + iHeader , &ucMonBuf[ 0 ] ) ;
	
	SENDREC_FIFO_HOST_Msg_Creation_Finish();
	
	
	return( iRet );
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine send msg for printer
*
*       PARAMETER: file handle, event, buffer, length
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iSENDREC_Msg_Printer_Creation( unsigned short usType_p , unsigned char *pvData_p, int iLgData_p )
{
int iRet, i ;
int iHeader;
unsigned char ucMonBuf[ 400 ] ;

	iRet = FCT_OK ;
	i = 0;
	
	SENDREC_FIFO_HOST_Msg_Creation_Start( ) ;
	
	iHeader = iSENDREC_Header( 'P', usType_p, iLgData_p, &ucMonBuf[ 0 ] );
	
	switch( usType_p )
	{
/* UCMCPRINT_MESSAGE */
		case UCMHOST_PRINT_MSG:

			if( iLgData_p <= (400 -iHeader) )
			{
				i = iLgData_p;
			}
			else
			{
			   i = (400 - iHeader - 1 );
				iRet = UCMHOSTLIB_ERR_DLL_DATA_LG;
			}

			if( i != 0 )
			{
				memcpy( &ucMonBuf[ iHeader ], pvData_p, i );
			}
			else	
				iRet = UCMHOSTLIB_ERR_DLL_DATA_LG_0;

			ucMonBuf[ iHeader + i ] = 0 ;
			
			break;
		default:
			sprintf( (char*)&ucMonBuf[ iHeader], "Message Printer %04X unknown\n", usType_p);
			iRet = UCMHOSTLIB_ERR_DLL_MSG_PRINTER_UNKNOWN;
			break;

	}

	i = strlen( (char*)&ucMonBuf[ iHeader ] ) ;
	
	SENDREC_FIFO_HOST_Msg_AddBuffer( i + iHeader , &ucMonBuf[ 0 ] ) ;
	
	SENDREC_FIFO_HOST_Msg_Creation_Finish();
	
	
	return( iRet );
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine send msg for Modem
*
*       PARAMETER: file handle, event, buffer, length
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iSENDREC_Msg_Modem_Creation( unsigned short usType_p , unsigned char *pvData_p, int iLgData_p )
{
T_UCMC_IAC_MODEM_CNX *pCnx;
int iRet, i ;
int iHeader;
unsigned char ucMonBuf[ 400 ] ;

	iRet = FCT_OK ;
	i = 0;
	
	SENDREC_FIFO_HOST_Msg_Creation_Start( ) ;
	
	iHeader = iSENDREC_Header( 'M', usType_p, iLgData_p, &ucMonBuf[ 0 ] );
	
	switch( usType_p )
	{
		case UCMHOSTLIB_MSG_DEM_CONNECT:
			pCnx = (T_UCMC_IAC_MODEM_CNX *)pvData_p;

			if( iLgData_p != 0 )
			{
				sprintf( (char*)&ucMonBuf[iHeader], "Appel=%s Raccord=%s Centre=%d PAD=%d",
					 pCnx->uctAppel, pCnx->uctRaccord, pCnx->ucTypeCentre, pCnx->ucTypePad );
			}
			else
			{
				iRet = UCMHOSTLIB_ERR_DLL_DATA_LG_0;
			}
			
			break;
		case UCMHOSTLIB_MSG_DEM_DISCONNECT:
			
			if( iLgData_p != 0 )
			{
				/* on ne prend pas en compte les data de dcnx */
				sprintf( (char*)&ucMonBuf[iHeader], "DCNX Option %d", *pvData_p );
			}
			else
			{
				iRet = UCMHOSTLIB_ERR_DLL_DATA_LG_0;
			}
			
			break;

		case UCMHOSTLIB_MSG_NETWORK_WRITE:
				
			if( iLgData_p <= (400 -iHeader) )
			{
				i = iLgData_p;
			}
			else
			{
			   i = (400 - iHeader - 1 );
				iRet = UCMHOSTLIB_ERR_DLL_DATA_LG;
			}

			if( i != 0 )
			{
				memcpy( &ucMonBuf[ iHeader ], pvData_p, i );
			}
			else	
				iRet = UCMHOSTLIB_ERR_DLL_DATA_LG_0;

			ucMonBuf[ iHeader + i ] = 0 ;			
			break;
			
		case UCMHOSTLIB_MSG_NETWORK_READ:
				
			if( iLgData_p <= (400 -iHeader) )
			{
				i = iLgData_p;
			}
			else
			{
			   i = (400 - iHeader - 1 );
				iRet = UCMHOSTLIB_ERR_DLL_DATA_LG;
			}

			if( i != 0 )
			{
				memcpy( &ucMonBuf[ iHeader ], pvData_p, i );
			}
			else	
				iRet = UCMHOSTLIB_ERR_DLL_DATA_LG_0;

			ucMonBuf[ iHeader + i ] = 0 ;			
			break;

		default:
			sprintf( (char*)&ucMonBuf[iHeader], "Message Modem %04X unknown\n", usType_p);

			iRet = UCMHOSTLIB_ERR_DLL_MSG_MODEM_UNKNOWN;
			break;

	}

	i = strlen( (char*)&ucMonBuf[ iHeader ] ) ;
	
	SENDREC_FIFO_HOST_Msg_AddBuffer( i + iHeader , &ucMonBuf[ 0 ] ) ;
	
	SENDREC_FIFO_HOST_Msg_Creation_Finish();
	

	return( iRet );
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine Init Com
*
*       PARAMETER: com number
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iSENDREC_CloseCom( void )
{
	int iRet;
	
	iRet = FCT_OK;

	if( ghandleCom != NULL )
		iRet = UCMHOSTLIB_ERR_DLL_COM_HANDLE ;
	
	fclose( ghandleCom ) ;
	
	ghandleCom = NULL;
	
	return( iRet );
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine Init Com
*
*       PARAMETER: com number
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iSENDREC_InitCom( void )
{
	int iRet;
	
	iRet = FCT_OK;
	
	/* Init COM */
	switch( gucNoCom )
	{
		case 0:
			gulEvenCom = COM0 ;
	   	format("COM0", CBR_19200, 8, 1, PARITY, EVEN, 0);
	   	ghandleCom = fopen("COM0","rw") ;

	   	break;
		case 1:
			gulEvenCom = COM1 ;
	   	format("COM1", CBR_19200, 8, 1, PARITY, EVEN, 0);
	   	ghandleCom = fopen("COM1","rw") ;

	   	break;
		case 2:
			gulEvenCom = COM2 ;
	   	format("COM2", CBR_19200, 8, 1, PARITY, EVEN, 0);
	   	ghandleCom = fopen("COM2","rw") ;

	   	break;
		case 5:	/* USB */
			gulEvenCom = COM5 ;
	   	format("COM5", CBR_19200, 8, 1, PARITY, EVEN, 0);
	   	ghandleCom = fopen("COM5","rw") ;

	   	break;
	   default:
	   	iRet = UCMHOSTLIB_ERR_DLL_COM ;
	   	break;
   	
	}

   if( ghandleCom == NULL )
      iRet = UCMHOSTLIB_ERR_DLL_COM_HANDLE ;

	return( iRet );
}



/*
------------------------------------------------------------
*
*       PURPOSE: This routine init payement
*
*       PARAMETER: 	mode
*					
*       RETURN: 0  if closed
*              
------------------------------------------------------------
*/
int iSENDREC_Init( T_UCM_DEVICE *psDevice_p )
{
	int iRet;
	
	iRet = FCT_OK ;

	memset( gucBufSend, 0, 4 ) ;
			
	giIndexBufSend = 0 ;
	giNbMsgToSend = 0 ;

	giIndexBufToSend = 0 ;
	
	ghandleCom = NULL ;
	gulEvenCom = 0 ;

	giNumberCreatMsg	= 0;
	
	giMsgInCreation = 0 ;

   memset( &gHostStatus,0,sizeof( T_UCMHOST_MPA_STATUS ) ) ;
	memset( &sStatusUCM, 0, sizeof( T_UCMHOST_STATUS_UCM ) );
	
	gsRecHoteSave.usType = UCMHOSTLIB_MSG_NO;
	gHostStatus.ucDLL = UCMHOST_DLL_NOINIT;
   gHostStatus.ucCom = UCMHOST_MPA_NOCOM;
	
	if( psDevice_p != NULL )
	{
      gucNoCom = psDevice_p->ucCom ;

		if( psDevice_p->ucType != PARAM_TYPE_NOT_USED )
		{
			/* Start task */
			iSENDREC_Redef_task();

         gHostStatus.ucDLL = UCMHOST_DLL_IDLE;
		}
		else
			iRet = UCMHOSTLIB_ERR_DLL_BAD_PILOTE;
	}

   if( iRet != FCT_OK )
   {
      gHostStatus.ucDLL = UCMHOST_DLL_INITKO;
   }
	
	return( iRet );
}




/*
------------------------------------------------------------
*
*       PURPOSE: This routine test if com is open
*
*       PARAMETER: 	com number or 0xFF for com in use
*					
*       RETURN: 0  if open
*              
------------------------------------------------------------
*/
int iSENDREC_Is_Open( unsigned char ucCom_p )
{
int iRet = 0;

	iRet = FCT_OK;
	
	/* Treatement */
	if( ghandleCom == NULL )
	{
		iRet = UCMHOSTLIB_ERR_DLL_COM_CLOSED ;
	}
	else
	{	
		/* Not com in use and com to test different */
		if( (ucCom_p != 0xFF) && ( ucCom_p != gucNoCom ) )
		{
			/* Com is open but bad number */
			iRet = UCMHOSTLIB_ERR_DLL_COM_NUMBER;
		}
	}

	return( iRet ) ;
}




