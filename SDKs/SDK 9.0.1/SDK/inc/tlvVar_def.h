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
 * @Title:        TLVVAR_DEF.H
 * @Description:  Additional definitions for TLV schemes package
 * @Reference:    
 * @Comment:      
 *
 * @author        JCP
 * @version       
 * @Comment:      
 * @date:         2006/08/30 
 *
 */ 
 
#ifndef _TLV_VAR_DEF_H
#define _TLV_VAR_DEF_H


/*
 TLV Id
 */
#define TLV_TYPE_KDES           1
#define TLV_TYPE_KTDES          2
#define TLV_TYPE_DATA           3
#define TLV_TYPE_PINBLOC        4
#define TLV_TYPE_DESDUKPT       5
#define TLV_TYPE_TDESDUKPT      6
#define TLV_TYPE_TIMLIMIT       7
#define TLV_TYPE_KHMAC          8
#define TLV_TYPE_KAES           9
#define TLV_TYPE_PINPRIV        12
#define TLV_TYPE_TDESDUKPTLIGHT 13
#define TLV_TYPE_DESDUKPTLIGHT  14
#define TLV_TYPE_DATA_NONSECRET 17
#define TLV_TYPE_KSUKPT         18
#define TLV_TYPE_RSA_PK         19
#define TLV_TYPE_KTDES_16       TLV_TYPE_KTDES
#define TLV_TYPE_KTDES_24       20
#define TLV_TYPE_TDESDUKPT_E2EE 21
#define TLV_TYPE_RSA_PRIV	22
#define TLV_TYPE_PINPAD_RSA	23
#define TLV_TYPE_CUSTOM_RSA	24
#define TLV_TYPE_TDESDUKPTSERV  25

#define  ID_KEY_DES(bk,no)                (bk | 0x00000100 | no)
#define  ID_KEY_TDES(bk,no)               (bk | 0x00000200 | no)
#define  ID_KEY_TDES_24(bk,no)         	  (bk | 0x00001400 | no)
#define  ID_DATA(bk,no)                   (bk | 0x00000300 | no)
#define  ID_PINBLOC(bk,no)                (bk | 0x00000400 | no)
#define  ID_KEY_DUKPT(bk,no)              (bk | 0x00000500 | no)
#define  ID_KEY_TDUKPT(bk,no)             (bk | 0x00000600 | no)
#define  ID_PIN_TIMLIMIT                      (0x00000700)
#define  ID_PINPRIV(bk,no)                (bk | 0x00000C00 | no)
#define  ID_TDESDUKPTLIGHT(bk,no)         (bk | 0x00000D00 | no)
#define  ID_DESDUKPTLIGHT(bk,no)          (bk | 0x00000E00 | no)
#define  ID_TDESDUKPT_E2EE(bk,no)         (bk | 0x00001500 | no)

#define  BK_SAGEM                        0x80000000
#define  BK_INGENICO                     BK_SAGEM



/*
 Definitions for ISO 9564
 */
#define  NAM_TLV_ISO9564               ("TlvIso9564")
#define  ID_TLV_ISO9564                0x40020001

/*
 Definitions for DUKPT DES
 */
#define  NAM_TLV_DUKPT_DES             ("TlvDukpt")
#define  ID_TLV_DUKPT_DES              0x40020101

/*
 Definitions for DUKPT TDES
 */
#define  NAM_TLV_DUKPT_TDES            ("TlvDukpTDes")
#define  ID_TLV_DUKPT_TDES             0x40020201

/*
 Definitions for LOAD DATA
 */
#define  NAM_TLV_LOAD_DATA             ("TlvLoadData")
#define  ID_TLV_LOAD_DATA              0x40020401

/*
 Definitions for LOAD KEY
 */
#define  NAM_TLV_LOAD_KEY             ("TlvLoadKey")
#define  ID_TLV_LOAD_KEY              0x40020402

#define  CIPHERING_DATA		           0
#define  CIPHERING_KEY		           1
#define  CIPHERING_PIN		           2
#define  TR31_KBPK_KEY				   3
#define  DERIVATION_KEY_CIPHERING_DATA 4
#define  DERIVATION_KEY_CIPHERING_KEY  5
#define  DERIVATION_KEY_CIPHERING_PIN  6
#define  E2EE_KEY					   7

/*
 Definitions for LOAD KEY (TR31 format)
 */
#define  NAM_TLV_LOAD_KEY_TR31        ("TlvLoadTR31")
#define  ID_TLV_LOAD_KEY_TR31         0x40020403

/*
 Definitions for GET PIN
 */
#define  NAM_TLV_GET_PIN               ("TlvGetPin")
#define  ID_TLV_GET_PIN                0x40020501

/*
 Definitions for CIPHER DATA
 */
#define  NAM_TLV_CIPHER_DATA           ("TlvCipherDa")
#define  ID_TLV_CIPHER_DATA            0x40020601

#define  NAM_STLV_CIPHER_DATA          ("STLCipherDa")
#define  ID_STLV_CIPHER_DATA           0x40020605

/*
 Definitions for FREE SECRET AREA
 */
#define  NAM_TLV_FREE_SECRET           ("TlvFree")
#define  ID_TLV_FREE_SECRET            0x40020801 

/*
 Definitions for XOR
 */
#define  NAM_TLV_XOR                  ("TlvXOR")
#define  ID_TLV_XOR                   0x40030201

/*
 Definitions for RSA
 */
#define  NAM_TLV_RSA                  ("TlvRsa")
#define  ID_TLV_RSA                   0x40020701

#define RSA_KEY_GENERATION            1
#define RSA_PUBLIC_KEY_CIPHERING      2
#define RSA_PRIVATE_KEY_CIPHERING     3

/*
 Definitions for KCV
 */
#define  NAM_TLV_KEYVERIF			   ("TlvKeyVerif")
#define  ID_TLV_KEYVERIF			   0x40020602


/*
 Definitions for DUKPT LIGHT TDES
 */
#define  NAM_TLV_DUKPT_LIGHT_TDES      ("SDukptLTDes")
#define  ID_TLV_DUKPT_LIGHT_TDES       0x40020202

/*
 Definitions for DUKPT LIGHT DATA TDES
 */
#define  NAM_TLV_DUKPT_LIGHT_DATA_TDES      ("SDukptLTDt")
#define  ID_TLV_DUKPT_LIGHT_DATA_TDES       0x40020203

/*
 Definitions for DUKPT LIGHT DES
 */
#define  NAM_TLV_DUKPT_LIGHT_DES      ("SDukptLDes")
#define  ID_TLV_DUKPT_LIGHT_DES       0x40020102

/*
 Definitions for DUKPT LIGHT DATA DES
 */
#define  NAM_TLV_DUKPT_LIGHT_DATA_DES      ("SDukptLDDt")
#define  ID_TLV_DUKPT_LIGHT_DATA_DES       0x40020103




#endif
