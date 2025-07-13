/***
 * Copyright (c) 2010 INGENICO , rue claude Chappe,
 * 07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * INGENICO has intellectual property rights relating
 * to the technology embodied in this software.  In particular,
 * and without limitation, these intellectual property rights
 * may include one or more patents.
 *
 * This software is distributed under licenses restricting
 * its use, copying, distribution, and decompilation.
 * No part of this software may be reproduced in any form
 * by any means without prior written authorization of
 * INGENICO.
 *
 * Title:        Digest_interface.h
 * Description:  Digest DLL interface header file
 * @Reference:    
 * @Comment:      
 *
 * @author       A.ROCHE
 * @version: $Revision: 1.1.2.3 $
 * @Comment:      
 * @date:        2011/11
 *
 */

/*! @addtogroup DLL_DIGEST_GENERAL
	* @{
	**/	

#ifndef __DIGEST_INTERF_H__
#define __DIGEST_INTERF_H__

/*****************************************************************************************************/
/************************************** GENERAL SERVICES INTERFACE ***********************************/
/*****************************************************************************************************/



/*
======================================================================
			                 Functions Definition
======================================================================
*/

/*! @brief This function calls the version of the API lib interface with DIGEST DLL.
 *	@return The version.
 *   BCD format (4 bytes) : VVVVmmpp where
 *	 - VVVV : Major number
 *	 - mm : minor number
 *	 - pp : patch number
 *
 *	@link DLL_DIGEST_GENERAL Back to top @endlink
 **/ 
int Digest_libversion(void);

/*! @brief This function calls the version of the DLL services.
 *	@return Version as integer
 *   BCD format (4 bytes) : VVVVmmpp where
 *	 - VVVV : Major number
 *	 - mm : minor number
 *	 - pp : patch number
 *
 *	@link DLL_DIGEST_GENERAL Back to top @endlink
 **/
int Digest_GetVersion (void);


/*! @brief This function is used to run an HMac integrated in an DIGEST solution
 *  @param[in]	ptKMacKeyId : HMAC Key Id (cAlgoType is TLV_TYPE_KMAC)
 *  @param[in]	pt_InputData : Data buffer to HMAC
 *  @param[in]	uiInputDataLength : Length (in bytes) of the input data buffer
 *  @param[out]	pt_OutputHMAC : computed HMAC (length is uiHMACLength)
 *  @param[in,out]	pt_uiHMACLength : Length (in bytes) of the HMAC to compute (28 max for sha224))
 *
 *  @return    OK or @link ERR_Schemes Error @endlink
 *
 *  @par Example:
 *  @include Digest_Sample_01.c
 *
 *	@link DLL_DIGEST_GENERAL Back to top @endlink
 **/

int Digest_ComputeHMACSha224 (T_SEC_DATAKEY_ID * ptKMacKeyId,
                      unsigned char * pt_InputData, unsigned int uiInputDataLength,
                      unsigned char * pt_OutputHMAC, unsigned int * pt_uiHMACLength);

#endif /* __DIGEST_INTERF_H__ */

/*! @} **/
