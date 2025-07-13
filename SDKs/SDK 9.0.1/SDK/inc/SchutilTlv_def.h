/***
 * Copyright (c) 2001 Sagem Monetel SA, rue claude Chappe,
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
 * @date:         2007/12/12 
 */ 
 

#ifndef _SCH_UTILTLV_DEF_H
#define _SCH_UTILTLV_DEF_H


#define  NAM_SCH_UTILTLV               ("SchutilTlv")
#define  ID_SCH_UTILTLV					0x40020404


/* Values for 1rst parameter : Command value */
#define C_UTLV_CMD_TYPE			0
#define C_UTLV_CMD_OFFSET		1


/* Returned value */
#define C_UTLV_TYPE_TLV			0    /* only for C_UTLV_CMD_TYPE */
#define C_UTLV_TYPE_TLV_BL1		1	 /* only for C_UTLV_CMD_TYPE */
#define C_UTLV_TYPE_NOT_TLV		-1
#define C_UTLV_TYPE_NO_SECRET	-2


#endif
