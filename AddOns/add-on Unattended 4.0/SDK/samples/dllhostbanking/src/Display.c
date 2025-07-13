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
#include "sdk30.h"
#include "ucmtelium.h"
#include "ucmhostDLL.h"
#include "sendrec.h"

/*
------------------------------------------------------------
*
*       PURPOSE: This routine display
*       PARAMETER: T_UCMHOST struct  
*             Message are compatible 2 lines of 16 characters each
*       RETURN: 0  if successfull
*               -1 if array is empty before init. phase
*              
------------------------------------------------------------
*/
int iDisplay_UCMC_Msg( T_UCMHOST *pMsg_p )
{
int iRet ;

   /* Message are compatible 2 lines of 16 characters each */
   /* Reception in same block */
	iRet = iSENDREC_Msg_Display_Creation( pMsg_p->usType , 
		pMsg_p->u.pucData, pMsg_p->uiSize ) ;

	return( iRet ); 
}
