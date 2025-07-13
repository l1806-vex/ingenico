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
*       PURPOSE: This routine print
*						Called by API
*       PARAMETER: hote struct
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iPrint_UCMC_Msg( T_UCMHOST *pMsg_p )
{
int iRet ;
int iLg ;

	iLg = pMsg_p->uiSize;
	if( iLg >= 2 )
	{
		if( pMsg_p->u.pucData[ iLg - 1 ] == '\n' )
			iLg --;
			
	}
	
	iRet = FCT_OK;
	
	if( iLg > 0 )
	{
		iRet = iSENDREC_Msg_Printer_Creation( pMsg_p->usType, pMsg_p->u.pucData, iLg ) ;
	}

	return( iRet ); 
}
