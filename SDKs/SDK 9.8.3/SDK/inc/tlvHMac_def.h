/***
 * Copyright (c) 2007 Sagem Monetel SA, rue claude Chappe,
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
 * @Title:        tlvMACKeyGen_def.H
 * @Description:  Interface with tlvMACKeyGen scheme
 * @Reference:    
 * @Comment:      
 *
 * @author        JLM
 * @version       
 * @Comment:      
 * @date:         2007/09/11 
 *
 */ 
 
#ifndef _TLV_HMAC_DEF_H
#define _TLV_HMAC_DEF_H


/*
 TLV Id
 */

#define  NAM_TLV_HMAC               ("TlvHMac")
#define  ID_TLV_HMAC                0x40020A04

#define  TAG_TLV_HMAC      ID_TLV_HMAC

/* Values for 2nd parameter : HMAC part */
#define  THM_FIRST_HMAC			0x00000000
#define  THM_SECOND_HMAC		0x01000000
#define  THM_ALL_HMAC			0x02000000

/* SPECIFIC RETURN ERROR CODE IN T_HEADER_RESULT */
/*************************************************/
#define  THM_BAD_KEY			(-1701)

#endif
