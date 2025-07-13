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
 * @Description:  Err functions
 * @Reference:    
 * @Comment:      
 *
 * @author        
 * @version       
 * @Comment:      
 * @date:         
 */

#include "sdk30.h"
#include "ucmtelium.h"
#include "UCMHOSTDLL.h"
#include "sendrec.h"


/*
------------------------------------------------------------
*
*       PURPOSE: This routine connect 
*						Called by API
*       PARAMETER: hote struct
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iModem_UCMC_Cnx( T_UCMHOST *pMsg_p )
{
int iRet ;

	iRet = iSENDREC_Msg_Modem_Creation( UCMHOSTLIB_MSG_DEM_CONNECT /*pMsg_p->usType*/ 
		, pMsg_p->u.pucData, pMsg_p->uiSize) ;

	return( iRet ); 
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine deconnect 
*						Called by API
*       PARAMETER: hote struct
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iModem_UCMC_Dcnx( T_UCMHOST *pMsg_p )
{
int iRet ;

	iRet = iSENDREC_Msg_Modem_Creation( UCMHOSTLIB_MSG_DEM_DISCONNECT
		/*pMsg_p->usType*/ , pMsg_p->u.pucData, pMsg_p->uiSize ) ;

	return( iRet ); 
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine write to modem
*						Called by API
*       PARAMETER: hote struct
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iModem_UCMC_Write( T_UCMHOST *pMsg_p )
{
int iRet ;

	iRet = iSENDREC_Msg_Modem_Creation( UCMHOSTLIB_MSG_NETWORK_WRITE
		/*pMsg_p->usType*/ , pMsg_p->u.pucData, pMsg_p->uiSize ) ;

	return( iRet ); 
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine read from modem
*						Called by API
*       PARAMETER: hote struct
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iModem_UCMC_Read( T_UCMHOST *pMsg_p )
{
int iRet ;

	iRet = iSENDREC_Msg_Modem_Creation( UCMHOSTLIB_MSG_NETWORK_READ
		/*pMsg_p->usType*/ , pMsg_p->u.pucData, pMsg_p->uiSize ) ;

	return( iRet ); 
}

/*
------------------------------------------------------------
*
*       PURPOSE: This routine request modem status
*						Called by API
*       PARAMETER: hote struct
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iModem_UCMC_Status( T_UCMHOST *pMsg_p )
{
int iRet ;

	iRet = iSENDREC_Msg_Modem_Creation( UCMHOSTLIB_MSG_NETWORK_STATUS
		/*pMsg_p->usType*/ , pMsg_p->u.pucData, pMsg_p->uiSize ) ;

	return( iRet ); 
}

