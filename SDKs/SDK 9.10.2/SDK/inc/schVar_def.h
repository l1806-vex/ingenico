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
 * @Title:        SCHVAR_DEF.H
 * @Description:  Definitions for schemes package
 * @Reference:
 * @Comment:
 *
 * @author
 * @version
 * @Comment:
 * @date:         2003/09/05
 *
 * @author
 * @version
 * @Comment:      Adding T_HEADER_RESULT
 * @date:         2006/08/17
 *
 * @author
 * @version
 * @Comment:      Adding ID_SCH_RANDOM, NAM_SCH_RANDOM
 * @date:         2006/09/04
 *
 * @author
 * @version
 * @Comment:      Adding Specific MAC_ICV Scheme, TLV Mac Key in DUKPT secret area
 * @date:         2006/12/04
 */

#ifndef _SCH_VAR_DEF_H
#define _SCH_VAR_DEF_H

/*
 Global definitions
 */
#define  DES_KEY_SIZE                    8				/*!< DES key 8 bytes */
#define  TDES_KEY_SIZE                   16				/*!< TDES key 16 bytes */
#define  TRANSACTION_FIELD_SIZE          5				/*!< size in bytes */
#define  PIN_BLOC_SIZE                   8				/*!< size in bytes */
#define  PAN_BLOC_SIZE                   8				/*!< size in bytes */
#define  TDES_16_KEY_SIZE                TDES_KEY_SIZE
#define  TDES_24_KEY_SIZE                24

#define  TAG_SIZE                        4				/*!< 4 bytes TAG */
#define  LEN_SIZE                        4				/*!< 4 bytes for length field */
#define  ANSWER_HEADER_SIZE              (TAG_SIZE + LEN_SIZE)		/*!< Header size in bytes */
#define  RETURN_CODE_SIZE                4							/*!< size in bytes */
#define  BUFFER_SIZE                     32							/*!< size in bytes */

#define  MIN_PIN_CODE_SIZE               4			/*!< Min numeric keys for PIN input */
#define  MAX_PIN_CODE_SIZE               12			/*!< Max numeric keys for PIN input */
#define  MAX_PIN_AREA_SIZE               20			/*!< PIN area size in bytes */
#define  MAX_DATA_SIZE                   1024		/*!< size in bytes */

#define  SEND_COMPLETED                  COM_FIN_EMI		/*!< send completed */

#define  MAX_SCH_REC_TIMEOUT             10  /*!< 10 sec. timeout for scheme receive */

/*
 Definitions for ISO9564
 */
#define  ISO9564_F0_DES                  1		/*!< DES ciphering ISO9564 format 0 */
#define  ISO9564_F0_TDES                 2		/*!< TDES ciphering ISO9564 format 0 */
#define  ISO9564_F1_DES                  3		/*!< DES ciphering ISO9564 format 1 */
#define  ISO9564_F1_TDES                 4		/*!< TDES ciphering ISO9564 format 1 */
#define  ISO9564_F3_DES                  5		/*!< DES ciphering ISO9564 format 3 */
#define  ISO9564_F3_TDES                 6		/*!< TDES ciphering ISO9564 format 3 */
#define  ISO9564_F2_DES                  7		/*!< DES ciphering ISO9564 format 2 */
#define  ISO9564_F2_TDES                 8		/*!< TDES ciphering ISO9564 format 2 */
#define  ISO9564_F2_OTHER                9		/*!< Other ISO9564 format 2 */
#define  ISO9564_F0_F8_DES               10		/*!< DES ciphering ISO9564 format 0-8 */
#define  ISO9564_F0_F8_TDES              11		/*!< TDES ciphering ISO9564 format 0-8 */
#define  ISO9564_F3_F8_DES               12		/*!< DES ciphering ISO9564 format 3-8 */
#define  ISO9564_F3_F8_TDES              13		/*!< TDES ciphering ISO9564 format 3-8 */
#define  ISO9564_F0_TDES_24              14		/*!< TDES_24 ciphering ISO9564 format 0 */
#define  ISO9564_F1_TDES_24              15		/*!< TDES_24 ciphering ISO9564 format 1 */
#define  ISO9564_F2_TDES_24              16		/*!< TDES_24 ciphering ISO9564 format 2 */
#define  ISO9564_F3_TDES_24              17		/*!< TDES_24 ciphering ISO9564 format 3 */

#define  AA                              (0x10101010)	/*!< AA hexa constant */
#define  CONTROL_FIELD_3                 0x30			/*!< Control field value 3 */

#define  ID_SCH_ISO9564                  0x40020000		/*!< Scheme Id */

#define  TAG_ISO9564_0                   0x40020000		/*!< Header Tag Id */
#define  TAG_ISO9564_1                   0x40020001		/*!< Header Tag Id */
#define  TAG_ISO9564_2                   0x40020002		/*!< Header Tag Id */
#define  TAG_ISO9564_3                   0x40020003		/*!< Header Tag Id */

/*
 Definitions for DUKPT
 */
#define  ID_SCH_DUKPT_DES				0x40020100		/*!< Scheme Id */
#define  TAG_DUKPT                      0x40020100     	/*!< Header Tag Id DUKPT (ANSI X9.24-1998) */
#define  TAG_DUKPT_INITIALISATION      	0x40020101		/*!< Header Tag Id */
#define  TAG_DUKPT_LOAD                	0x40020102		/*!< Header Tag Id */
#define  TAG_DUKPT_TRANSACTION         	0x40020103		/*!< Header Tag Id */
#define  TAG_DUKPT_CANCEL              	0x40020104		/*!< Header Tag Id */

#define  DUKPT_INITIAL_KEY_CREATION           1			/*!< DUKPT Command */
#define  DUKPT_LOAD_KEY                       2			/*!< DUKPT Command */
#define  DUKPT_LOAD_KSN                       3			/*!< DUKPT Command */
#define  DUKPT_LOAD_KSN_CREATE                3+0x10000	/*!< DUKPT Command */
#define  DUKPT_ENCRYPT_PIN                    4			/*!< DUKPT Command */
#define  DUKPT_ENCRYPT_PIN_F3                 5			/*!< DUKPT Command */
#define  DUKPT_CANCEL_KEYS                    6			/*!< DUKPT Command */
#define  DUKPT_GET_CURRENT_STATE              7         /*!< DUKPT Command */
#define  DUKPT_LOAD_RIGHT_PART_DERIVATION_KEY 8			/*!< DUKPT Command */
#define  DUKPT_LOAD_LEFT_PART_DERIVATION_KEY  9			/*!< DUKPT Command */
#define  DUKPT_LOAD_RIGHT_PART_KEY            10		/*!< DUKPT Command */
#define  DUKPT_LOAD_LEFT_PART_KEY             11		/*!< DUKPT Command */
#define  DUKPT_LOAD_CIPHERED_DERIVATION_KEY   12		/*!< DUKPT Command */
#define  DUKPT_LOAD_CIPHERED_INITIAL_KEY      13		/*!< DUKPT Command */
#define  DUKPT_CREATE_KEYS                    14		/*!< DUKPT Command */
#define  DUKPT_GET_CURRENT_SMID               15		/*!< DUKPT Command */
#define  DUKPT_KCV_INITIALKEY                 16		/*!< DUKPT Command */
#define  DUKPT_KCV_DERIVKEY                   17		/*!< DUKPT Command */
#define  DUKPT_MAC_VERIFY                     18		/*!< DUKPT Command */
#define  DUKPT_MAC_COMPUTE                    19		/*!< DUKPT Command */
#define  DUKPT_ENCRYPT_DATABLOCK              20		/*!< DUKPT Command */
#define  DUKPT_ENCRYPT_DATABLOCK_F3           21		/*!< DUKPT Command */
#define  DUKPT_ENCRYPT_DATA_ECB               22		/*!< DUKPT Command */
#define  DUKPT_ENCRYPT_DATA_CBC               23		/*!< DUKPT Command */
#define  DUKPT_ENCRYPT_DATA_EXT_ECB           24		/*!< DUKPT Command */
#define  DUKPT_DECRYPT_DATA_EXT_ECB           25		/*!< DUKPT Command */
#define  DUKPT_ENCRYPT_DATA_EXT_CBC           26		/*!< DUKPT Command */
#define  DUKPT_DECRYPT_DATA_EXT_CBC           27		/*!< DUKPT Command */

#define  NB_DUKPT_KEYS                 		  21		/*!< Number of DUKPT keys */
#define  DUKPT_SMID_SIZE               		  10		/*!< size in bytes */
#define  DUKPT_DATA_SIZE               		  512		/*!< size in bytes */

#define  DUKPT_IN_FUNCTION             		  0			/*!< DUKPT status OK */
#define  DUKPT_NOT_IN_FUNCTION         		  1			/*!< DUKPT status NOK */
#define  DUKPT_KSN_NOT_REC	  				  2			/*!< DUKPT status KSN not received */
#define  DUKPT_INIT_KEY_NOT_REC				  3			/*!< DUKPT status initial key not received */
#define  DUKPT_END_OF_LIFE             		  (-110)	/*!< DUKPT status EOL */

#define  ID_SCH_DUKPT_TDES             0x40020200		/*!< Scheme Id */
#define  TAG_DUKPT_TDES                0x40020200		/*!< Header Tag Id */
#define  TAG_TDUKPT                    0x40020200		/*!< Header Tag Id */
#define  TAG_TDUKPT_INITIALISATION     0x40020201		/*!< Header Tag Id */
#define  TAG_TDUKPT_LOAD               0x40020202		/*!< Header Tag Id */
#define  TAG_TDUKPT_TRANSACTION        0x40020203		/*!< Header Tag Id */
#define  TAG_TDUKPT_CANCEL             0x40020204		/*!< Header Tag Id */

#define  INC_AUTO_MODE                 0                /*!< Auto Key advance */
#define  INC_FORCED_MODE               1                /*!< Forced Key advance */

/*
 Temporary definitions (do not use)
 */
#define  ID_SCH_INIT_PIN_CODE          0x40020300		/*!< Scheme Id */
#define  ID_SCH_INIT_KEYS_ISO9564      0x40020400		/*!< Scheme Id */
#define  ID_SCH_INIT_KEY_DUKPT         0x40020500		/*!< Scheme Id */
#define  ID_SCH_INIT_KEY_TDUKPT        0x40020600		/*!< Scheme Id */

#define  ID_SCR_KEY_DES_ISO9564        0x40022000		/*!< Scheme Id */
#define  ID_SCR_KEY_TDES_ISO9564       0x40022100		/*!< Scheme Id */
#define  ID_SCR_KEY_OTHER_ISO9564      0x40022200		/*!< Scheme Id */
#define  ID_SCR_KEY_DES_DUKPT          0x40022300		/*!< Scheme Id */
#define  ID_SCR_KEY_TDES_DUKPT         0x40022400		/*!< Scheme Id */
#define  ID_SCR_KEY                    0x40022400		/*!< Scheme Id */


/*
 Definitions for LOAD DATA
 */
#define  NAM_SCH_LOAD_DATA             ("SchLoadData")	/*!< Scheme Name */
#define  ID_SCH_LOAD_DATA              0x40020400		/*!< Scheme Id */
#define  TAG_LOAD_DATA                 0x40020400		/*!< Header Tag Id */

#define  DATA_NO_CIPHER                0x00000000		        /*!< Scheme Command */
#define  CLEAR_DATA_MODE               0x00000000		        /*!< Scheme Command */
#define  DATA_DES_CIPHER               0x01000000		        /*!< Scheme Command */
#define  DES_CIPHERED_MODE             0x01000000		        /*!< Scheme Command */
#define  DATA_TDES_CIPHER              0x02000000		        /*!< Scheme Command */
#define  TDES_CIPHERED_MODE            DATA_TDES_CIPHER		  /*!< Scheme Command */
#define  CREATE_AREA                   0x03000000		        /*!< Scheme Command */
#define  CREATE_AREA_FULLBL1           0x04000000		        /*!< Scheme Command */

#define  DATA_TDES_16_CIPHER           DATA_TDES_CIPHER		  /*!< Scheme Command */
#define  TDES_16_CIPHERED_MODE         DATA_TDES_CIPHER		  /*!< Scheme Command */
#define  DATA_TDES_24_CIPHER           0x05000000		        /*!< Scheme Command */
#define  TDES_24_CIPHERED_MODE         DATA_TDES_24_CIPHER	/*!< Scheme Command */

#define  OFFCET_MASTER_KEY             0x000003FF		/*!< Offset in the secret area */
#define  OFFSET_MASTER_KEY             0x000003FF		/*!< Offset in the secret area */

#define  NAM_SCH_LOAD_KEYTLV           ("SloadKeyTlv")	/*!< Scheme Name */
#define  ID_SCH_LOAD_KEYTLV            0x40020403		/*!< Scheme Id */

/*
 Definitions for PIN CODE entry
 */
#define  NAM_SCH_GET_PIN               ("SchGetPin")	/*!< Scheme Name */
#define  ID_SCH_GET_PIN                0x40020500		/*!< Scheme Id */


#define  HID_KEY_PIN_CODE              '*'				/*!< Hidden key value */
#define  C_GET_PIN_AUTO_VAL_MODE       0x01             // Automatic T_VAL mode
#define  C_GET_PIN_NO_FCT_KEY          0x80
#define  C_GET_PIN_T_ANN_MODE          0x40				/* Landi Modification, T_ANN_MODE */
/*
 Definitions for CIPHER or DECIPHER DATA
 */
#define  NAM_SCH_CIPHER_DATA           ("SchCipherDa")	/*!< Scheme Name */
#define  ID_SCH_CIPHER_DATA            0x40020600		/*!< Scheme Id */
#define  TAG_CIPHER_DATA               0x40020600		/*!< Header Tag Id */

#define  DATA_DES_DECIPHER             0x04000000		/*!< Scheme Command */
#define  DATA_TDES_DECIPHER            0x08000000		/*!< Scheme Command */
#define  DATA_TDES_24_CIPHER_BIS       0x60000000		/*!< Scheme Command */
#define  DATA_TDES_24_DECIPHER         0x09000000		/*!< Scheme Command */
#define  DATA_DES_CIPHER_ICV           0x10000000		/*!< Scheme Command */
#define  DATA_TDES_CIPHER_ICV          0x20000000		/*!< Scheme Command */
#define  DATA_TDES_24_CIPHER_ICV       0x30000000		/*!< Scheme Command */
#define  DATA_DES_DECIPHER_ICV         0x40000000		/*!< Scheme Command */
#define  DATA_TDES_DECIPHER_ICV        0x80000000		/*!< Scheme Command */
#define  DATA_TDES_24_DECIPHER_ICV     0x50000000		/*!< Scheme Command */
#define  DATA_DES_CIPHER_OFB           0x05000000		/*!< Scheme Command */
#define  DATA_TDES_CIPHER_OFB          0x06000000		/*!< Scheme Command */
#define  DATA_TDES_24_CIPHER_OFB       0x07000000		/*!< Scheme Command */
#define  DATA_MAC_ICV                  0x90000000		/*!< Scheme Command */

/*
 Definitions for other PIN entry scheme
 */
#define  SCH_PIN_ENTRY_NAME            ("SchPinEntry")	/*!< Scheme Name */
#define  ID_SCH_PIN_ENTRY              0x40020700		/*!< Scheme Id */

// Sound level
#define  LOW                           1		/*!< sound level value */
#define  MIDDLE_LOW                    2		/*!< sound level value */
#define  MIDDLE                        3		/*!< sound level value */
#define  MIDDLE_HIGH                   4		/*!< sound level value */
#define  HIGH                          5		/*!< sound level value */

// Note definitions
#define  C                             0		/*!< bip note */
#define  C_SHARP                       1		/*!< bip note */
#define  D                             2		/*!< bip note */
#define  D_SHARP                       3		/*!< bip note */
#define  E                             4		/*!< bip note */
#define  F                             5		/*!< bip note */
#define  F_SHARP                       6		/*!< bip note */
#define  G                             7		/*!< bip note */
#define  G_SHARP                       8		/*!< bip note */
#define  A                             9		/*!< bip note */
#define  A_SHARP                       10		/*!< bip note */
#define  B                             11		/*!< bip note */

/*
 Definitions for FREE SECRET AREA
 */
#define  NAM_SCH_FREE_SECRET           ("SchFree")	/*!< Scheme Name */
#define  ID_SCH_FREE_SECRET            0x40020800	/*!< Scheme Id */

/*
 Definitions for SchXOR
 */
#define  NAM_SCH_XOR					("SchXOR")	/*!< Scheme Name */
#define  ID_SCH_XOR					   0x40030200	/*!< Scheme Id */
#define  TAG_XOR					   ID_SCH_XOR	/*!< Header Tag Id */

/*
 Definitions for Sch_Random
 */
#define  NAM_SCH_RANDOM					("Sch_Random")	/*!< Scheme Name */
#define  ID_SCH_RANDOM					   0x40030100	/*!< Scheme Id */

/*
 Definitions for MAC_ICVDU Scheme
 */
#define  NAM_SCH_MAC_ICVDU           ("SchMacIcvDu")	/*!< Scheme Name */
#define  ID_SCH_MAC_ICVDU            0x40020A00			/*!< Scheme Id */
#define  TAG_MAC_ICVDU               ID_SCH_MAC_ICVDU	/*!< Header Tag Id */

/* Value for parameter 1 : 16 bits high */
#define  OP_MAC_ICV_DES                 0x90000000		/*!< 16 bits high Scheme Command */
#define  OP_MAC_ICV_TDES                0xA0000000		/*!< 16 bits high Scheme Command */

/* Value for parameter 1 : 16 bits low */
#define  MAC_VERIFY		                0x0001			/*!< 16 bits low Scheme Command */
#define  MAC_COMPUTE	                0x0002			/*!< 16 bits low Scheme Command */


/*
 Definitions for ENmEntryGEN Scheme
 */
#define  NAM_SCH_ENMENTRY				("ENmEntryGEN")		/*!< Scheme Name */
#define  ID_SCH_ENMENTRY				0x40030850			/*!< Scheme Id */
#define TAG_ENMENTRYGEN					ID_SCH_ENMENTRY		/*!< Header Tag Id */

/* Parameters to call the Scheme */

/* 1rst parameter */
#define  C_DECAL_FIRSTTIMEOUT     16 
#define  C_MSK_FIRSTTIMEOUT       0xFFFF

#define  C_DECAL_INTERTIMEOUT      0
#define  C_MSK_INTERTIMEOUT       0xFFFF

/* 2nd parameter */
#define  C_MSK_NUM     (1 << 0) 
#define  C_MSK_VAL     (1 << 1) 
#define  C_MSK_CORR    (1 << 2)
#define  C_MSK_ANN     (1 << 3) 
#define  C_MSK_F       (1 << 4)
#define  C_MSK_POINT   (1 << 5)
#define  C_MSK_STAR    (1 << 6) 
#define  C_MSK_UP      (1 << 7) 
#define  C_MSK_SK2     (1 << 8) 
#define  C_MSK_SK3     (1 << 9) 
#define  C_MSK_DOWN    (1 << 10) 
#define  C_MSK_SK1     (1 << 11) 
#define  C_MSK_SK4     (1 << 12) 

/* 3rd parameter */
#define  C_DECAL_MESSHEAD		24 
#define  C_MSK_MESSHEAD			0xFF

#define  C_DECAL_LINEHEAD		16 
#define  C_MSK_LINEHEAD			0xFF

#define  C_DECAL_COLHEAD		8 
#define  C_MSK_COLHEAD			0xFF

#define  C_DECAL_MODE			0
#define  C_MSK_MODE				0xFF


#define  C_NUMGEN_MODE_TEXT			0 
#define  C_NUMGEN_MODE_GRAPH		1 


/* 4th parameter */
#define  C_DECAL_MESSFOOT		24 
#define  C_MSK_MESSFOOT			0xFF

#define  C_DECAL_LINEFOOT		16 
#define  C_MSK_LINEFOOT			0xFF

#define  C_DECAL_COLFOOT		8 
#define  C_MSK_COLFOOT			0xFF

#define  C_DECAL_EXTRA			0
#define  C_MSK_EXTRA			0xFF

/* Extra parameters Input IAPP */
#define  C_EXTRA_LENGTH_PARAM  25 /* parameters exchanged via IAPP (without the signed buffeur)*/

/* Maximum size of file messages*/
#define  C_MESSAGE_BUFFER_MAX_SIZE     	14000 

/* Message Length in bytes of the variable numeric message */
/* to display and to send via IAPP */
#define  C_NUM_MESS_LENGTH      60 

/*! @addtogroup ERR_Schemes
	* @{
	**/
/*
 Error codes (for all schemes)
 */
#define  ERR_ID_NOT_FOUND              (-1024)		/*!< Scheme Error code */
#define  ERR_PIN_CODE_NOT_FOUND        (-1025)		/*!< Scheme Error code */
#define  ERR_BAD_PIN_CODE_LEN          (-1026)		/*!< Scheme Error code */
#define  ERR_BAD_IAPP_OPERATION        (-1027)		/*!< Scheme Error code */
#define  ERR_UNKNOW_FORMAT             (-1028)		/*!< Scheme Error code */
#define  ERR_DUKPT_END_OF_LIFE         (-1029)		/*!< Scheme Error code */
#define  ERR_BAD_ACTION_TYPE           (-1030)		/*!< Scheme Error code */

#define  ERR_ENTRY_CANCELED            (-1031)		/*!< Scheme Error code */
#define  ERR_TIMEOUT                   (-1032)		/*!< Scheme Error code */
#define  ERR_BAD_IHM_OPERATION         (-1033)		/*!< Scheme Error code */

#define  ERR_SYSTEME_ERROR             (-1034)		/*!< Scheme Error code */
#define  ERR_SYSTEM                    (-1034)		/*!< Scheme Error code */

#define  ERR_BAD_PARAM				   (-1035)		/*!< Scheme Error code */

#define  ERR_MAC_VERIFY				   (-1036)		/*!< Scheme Error code */
#define  ERR_MAC_KEY				   (-1037)		/*!< Scheme Error code */

#define  ERR_DUKPT_NOT_IN_FUNCTION     (-1038)		/*!< Scheme Error code */
#define  ERR_DIFFERENCE				   (-1039)		/*!< Scheme Error code */

#define C_ERR_BAD_MESS_NO				(-2901)		/*!< Scheme #NAM_SCH_ENMENTRY Error code */
#define C_ERR_BAD_MESS_IAPP    			(-2902)		/*!< Scheme #NAM_SCH_ENMENTRY Error code */
#define C_ERR_BAD_SIGN_CARD    			(-2903)		/*!< Scheme #NAM_SCH_ENMENTRY Error code */
#define C_ERR_BAD_SIGN         			(-2904)		/*!< Scheme #NAM_SCH_ENMENTRY Error code */
#define C_ERR_BAD_BUFFER_FORMAT 		(-2905)		/*!< Scheme #NAM_SCH_ENMENTRY Error code */
#define C_ERR_BAD_MODE         			(-2906)		/*!< Scheme #NAM_SCH_ENMENTRY Error code */
#define C_ERR_BUFFER_SIZE      			(-2907)		/*!< Scheme #NAM_SCH_ENMENTRY Error code */
#define C_ERR_ECHO_CHAR 	    		(-2908)		/*!< Scheme #NAM_SCH_ENMENTRY Error code */
#define C_ERR_CURRENCY_CODE				(-2909)		/*!< Scheme #NAM_SCH_ENMENTRY Error code */
#define C_ERR_FILE_NAME_PREFIX			(-2910)		/*!< Scheme #NAM_SCH_ENMENTRY Error code */

/*! @} **/

typedef struct{
 unsigned int	tag;
 unsigned int   id;
 unsigned int   len;
 unsigned int	usage;
 unsigned char  key[DES_KEY_SIZE];
}T_MAC_KDES;

typedef struct{
 unsigned int	tag;
 unsigned int   id;
 unsigned int   len;
 unsigned int	usage;
 unsigned char  key[TDES_KEY_SIZE];
}T_MAC_KTDES;

/*
 New types (for all schemes)
 */
typedef struct {
  unsigned char PinCode[MAX_PIN_CODE_SIZE];
  int           PinLen;
  unsigned char Rfu[4];
} T_PIN_CODE_AREA;

typedef struct {
   int           CardNumber1;
   int           CardNumber2;
   unsigned char Key[TDES_KEY_SIZE];
} T_TDES_KEY_AREA;

typedef struct {
   int           CardNumber1;
   int           CardNumber2;
   unsigned char Key[DES_KEY_SIZE];
} T_DES_KEY_AREA;

typedef struct {
   int           CardNumber1;
   int           CardNumber2;
   unsigned char Key[TDES_KEY_SIZE];
   unsigned char Rfu[104];
} T_ISO9564_TDES_KEY_AREA;

typedef struct {
   int           CardNumber1;
   int           CardNumber2;
   unsigned char Key[DES_KEY_SIZE];
   unsigned char Rfu[112];
} T_ISO9564_DES_KEY_AREA;

typedef struct {
   int           CardNumber1;
   int           CardNumber2;
   unsigned char PinBloc[PIN_BLOC_SIZE];
   unsigned char Rfu[1000];
} T_ISO9564_2_OTHER_AREA;

typedef struct {
   int           Tag;
   int           Len;
   int           ReturnCode;
   unsigned char Answer[BUFFER_SIZE];
} T_ISO9564_RESULT;

#ifndef __OEM_S_H
#ifndef __CRYPTO_DEF_H
#ifndef __CRYPTO_DEF_H_INCLUDED__
typedef struct {
   unsigned char  Key[DES_KEY_SIZE];
   unsigned short Check;
} T_DUKPT_KEY;

typedef struct{
   unsigned char  Key[TDES_KEY_SIZE];
   unsigned short Check;
} T_DUKPT_TDES_KEY;

#endif
#endif
#endif

typedef struct {
   int           CardNumber1;
   int           CardNumber2;
   int           CurrentState;
   T_DUKPT_KEY   keys[NB_DUKPT_KEYS];
   unsigned char Smid[DUKPT_SMID_SIZE];
   unsigned char DerivationKey[TDES_KEY_SIZE];
   unsigned char InitialKey[DES_KEY_SIZE];
   T_MAC_KDES    MacKey;
   unsigned char Rfu[760-sizeof(T_MAC_KDES)];
} T_DUKPT_DES_SECRET_AREA;

typedef struct {
   int           Tag;
   int           Len;
   int           ReturnCode;
   unsigned char TransactionSmid[DUKPT_SMID_SIZE];
   unsigned char TransactionPinBloc[PIN_BLOC_SIZE];
} T_DUKPT_RESULT;

typedef struct {
   int           Tag;
   int           Len;
   int           ReturnCode;
   unsigned char TransactionSmid[DUKPT_SMID_SIZE];
   unsigned char CipheredData[DUKPT_DATA_SIZE];
} T_DUKPT_DATA_RESULT;

typedef struct {
   int              CardNumber1;
   int              CardNumber2;
   int              CurrentState;
   T_DUKPT_TDES_KEY keys[NB_DUKPT_KEYS];
   unsigned char    Smid[DUKPT_SMID_SIZE];
   unsigned char    DerivationKey[TDES_KEY_SIZE];
   unsigned char    InitialKey[TDES_KEY_SIZE];
   T_MAC_KTDES   	MacKey;
   unsigned char    Rfu[572-sizeof(T_MAC_KTDES)];
} T_DUKPT_TDES_SECRET_AREA;

typedef struct {
	int           CardNumber1;
	int           CardNumber2;
	unsigned char Keys[1008];
} T_SECRET_AREA;

typedef struct {
   int           Tag;
   int           Len;
   int           ReturnCode;
} T_LOAD_DATA_RESULT;

typedef struct {
   int           Tag;
   int           Len;
   int           ReturnCode;
   unsigned char BufferOut[MAX_DATA_SIZE];
} T_CIPHER_DATA_RESULT;




typedef struct {
  unsigned char  Echo;
  unsigned char  EchoChar;
  unsigned char  Line;
  unsigned char  Column;
} T_ECHO_INFO;

typedef union {
  int         i;
  T_ECHO_INFO c;
} U_ECHO_INFO;


typedef struct {
  unsigned char  Rfu;
  unsigned char  BipOn;
  unsigned char  MinDigit;
  unsigned char  MaxDigit;
} T_KEY_INFO;

typedef union {
  int         i;
  T_KEY_INFO  c;
} U_KEY_INFO;


typedef struct {
  unsigned short InterTimeout;
  unsigned short GlobalTimeout;
} T_TIMEOUT_INFO;

typedef union {
  int            i;
  T_TIMEOUT_INFO s;
} U_TIMEOUT_INFO;


typedef struct {
  unsigned char  ErrorNote;
  unsigned char  ErrorLevel;
  unsigned char  NormalNote;
  unsigned char  NormalLevel;
} T_BIP_INFO;

typedef union {
  int         i;
  T_BIP_INFO  c;
} U_BIP_INFO;


typedef struct {
   int           Tag;
   int           Len;
   int           ReturnCode;
} T_PIN_ENTRY_RESULT;

typedef struct {
   int           Tag;
   int           Len;
   int			 ReturnCode;
} T_XOR_RESULT;

typedef struct {
   int           Tag;
   int           Len;
   int			 ReturnCode;
} T_HEADER_RESULT;

#endif
