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
 
#ifndef _TLV_MACKEYGEN_DEF_H
#define _TLV_MACKEYGEN_DEF_H


/*
 TLV Id values for parameter type in NAM_TLV_FREE_SECRET scheme
 */
#define TLV_TYPE_MAC	8
#define TLV_TYPE_AES	9

#define  NAM_TLV_MACKEYGEN               ("TlvMAKeyGen")
#define  ID_TLV_MACKEYGEN                0x40030704

#define  TAG_TLV_MACKEYGEN      ID_TLV_MACKEYGEN

/* Max length of key to generate */
#define PK_MAX_KEY_SIZE				128

#define C_MSK_DEF_KEYID		0xFFFF
#define C_VAL_DEF_KEYID		0x0800

/* SPECIFIC RETURN ERROR CODE IN T_HEADER_RESULT */
/*************************************************/
#define  TMA_BAD_KEY_TYPE	    (-1601)
#define  TMA_BAD_KEY_SIZE		(-1602)
#define  TMA_USED_KEY_USAGE		(-1603)
#define  TMA_USED_KEY_LENGTH	(-1604)
#define  TMA_PROCESSING_ERROR	(-1605)
#define  TMA_BAD_LENGTH			(-1606)

#endif
