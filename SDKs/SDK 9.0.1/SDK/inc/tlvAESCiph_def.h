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
 * @Title:        tlvAESCiph_def.H
 * @Description:  Interface with tlvAESCiph scheme
 * @Reference:    
 * @Comment:      
 *
 * @author        JLM
 * @version       
 * @Comment:      
 * @date:         2007/09/11 
 *
 */ 
 
#ifndef _TLV_AESCIPH_DEF_H
#define _TLV_AESCIPH_DEF_H


/*
 TLV Id
 */

#define  NAM_TLV_AESCIPH               ("TlvAESCiph")
#define  ID_TLV_AESCIPH                0x40020604

#define  TAG_TLV_AESCIPH      ID_TLV_AESCIPH

/* Values for 1rst parameter : Mode */
#define  TAES_CBC_CIPHER		0
#define  TAES_CBC_DECIPHER		1
#define  TAES_ECB_CIPHER		2
#define  TAES_ECB_DECIPHER		3

/* SPECIFIC RETURN ERROR CODE IN T_HEADER_RESULT */
/*************************************************/
#define  TAES_BAD_KEY			(-1401)

#endif
