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


#define  NAM_SCH_UTILTLV               ("SchutilTlv")	/*!<  Scheme Name (11 characters max) */
#define  ID_SCH_UTILTLV					0x40020404		/*!<  Scheme Id */

#define  NAM_SCH_COMPL_UTILTLV         ("ScCplutlTlv")	/*!<  Scheme Name (11 characters max) */
#define  ID_SCH_COMPL_UTILTLV				0x40020407		/*!<  Scheme Id */

/* Values for 1rst parameter : Command value */
#define C_UTLV_CMD_TYPE			0		/*!<  To return the secret area type */
#define C_UTLV_CMD_OFFSET		1		/*!<  To compute the offset of a  key/data in a TLV_BL1 secret area */
#define C_UTLV_CMD_MEMORY 		2		/*!<  To return the secret area memory storage */


/* Returned value */
#define C_UTLV_TYPE_TLV				0    /*!< TLV type format (only for command C_UTLV_CMD_TYPE) */
#define C_UTLV_TYPE_TLV_BL1			1	 /*!< TLV_BL1 type format (only for command C_UTLV_CMD_TYPE) */
#define C_UTLV_TYPE_FULL_TLV_BL1	2	 /*!< FULL_TLV_BL1 type format (only for command C_UTLV_CMD_TYPE) */
#define C_UTLV_TYPE_NOT_TLV			-1	 /*!< Non-TLV type format */
#define C_UTLV_TYPE_NO_SECRET		-2	 /*!< No secret area */


#endif
