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
 * Title:        E2EE_interface.h
 * Description:  E2EE DLL interface header file
 * @Reference:    
 * @Comment:      
 *
 * @author       A.ROCHE
 * @version: $Revision: 1.1.2.13 $
 * @Comment:      
 * @date:        2011/05
 *
 */

/*! @addtogroup DLL_E2EE_GENERAL
	* @{
	**/	

#ifndef __E2EE_INTERF_H__
#define __E2EE_INTERF_H__

/*****************************************************************************************************/
/************************************** GENERAL SERVICES INTERFACE ***********************************/
/*****************************************************************************************************/

//////////// Defines

///// Input Parameters

//// Error Codes
/*! @defgroup DLL_E2EE_ERROR_CODES     E2EE Error codes
	* @{
	**/	
#define E2EE_OK                  0
#define E2EE_ERR_INPUT_PARAM     (-12)		/*!< Error code : Missing any input parameter, see trace for more details*/

#define E2EE_ERR_TRACK1_PARSING  (-13)		/*!< Error code : Error parsing track1, no field separator*/
#define E2EE_ERR_TRACK2_PARSING  (-14)		/*!< Error code : Error parsing track2, no field separator*/
// PAN + ED + CVV
#define E2EE_ERR_PAN             (-15)		/*!< Error code : Error in PAN lenght*/
#define E2EE_ERR_PAN_ED          (-16)		/*!< Error code : Error in expiry date length*/
#define E2EE_ERR_PAN_CVV         (-17)		/*!< Error code : Error in CVV length*/

#define E2EE_ERR_MEMORY          (-18)		/*!< Error code : Error allocating memory*/
#define E2EE_KO                  (-19)		/*!< Error code : Internal Error*/
/*! @} **/

////// Warnings
/*! @defgroup DLL_E2EE_WARNING    E2EE Warning codes
	* @{
	**/	
#define E2EE_MASK_PAN_DIF			0x00000001		/*!< Warning: if pan in track1, track2 and PAN (when provided) is not the same.*/
#define E2EE_MASK_SC_ED_DIF			0x00000002		/*!< Warning: if track1 and track2 are both provided, their Service Codes and their Expiry Dates must be the same.*/
#define E2EE_MASK_ED_DIF			0x00000004		/*!< Warning: iIf ED and one of, or both, track1 and track2 are provided,
													the expiry date of track1 and / or track2 must be the same as the first 4 characters of ED*/
#define E2EE_MASK_NOT_CIPHERED		0x00000008		/*!< Warning: Not all Data returned ciphered*/
#define E2EE_MASK_BTF_PAN_NOT_FOUND	0x00000020		/*!< Warning: Pan requested is not in the file*/
#define E2EE_MASK_BTF_NOT_FOUND		0x00000040		/*!< Warning: BinTable file is not in the terminal*/
#define E2EE_MASK_BTF_BAD_FORMAT	0x00000080		/*!< Warning: Whether the pan furnished or the bin table has an error*/
#define E2EE_MASK_BTF_BAD_SIGNATURE	0x00000100		/*!< Warning: Bin table file is not correctly signed*/
/*! @} **/


//////////// Structs
/*! @brief This structure is used to input the E2EE Function.*/
typedef struct {
	char *track1;				/*!< Track1 in the clear, string null terminate*/
	char *track2;				/*!< Track2 in the clear, string null terminate*/
	char *pan;					/*!< PAN in the clear, string null terminate*/
	char *expDate;				/*!< Expiry Date - string, lenght 4 - Null terminate
									- or lenght 6 when PAN + ED + CVV*/
	char *cvv;					/*!< CVV in the clear, string, lenght 3 - null terminate
									- or lenght 4 when PAN + ED + CVV*/
	int nBin;					/*!< Number of digits in the clear in the BIN*/
	char extensiveFlag;			/*!< TRUE or FALSE */
	int iSecretArea;			/*!< Secret Area Id conform with "policy for secret Id": hexa form XXYY2T3Z
									- XXYY is the card signature VAR_ID
									- T is in the set [1.. F] hexa form
									- Z is in the set [0.. F] hexa form */
	unsigned short usNumber;	/*!< Key/Data number multiple of 4 from 0 through 1023 (see the previous note) */
	unsigned int uiBankId;		/*!< Bank Id : 2 MSB from 8000 hexa through FFFF hexa, 2 LSB to 0000 (see the previous note) */
	char encPANEnd;				/*!< Enable/Disable Encipher PAN End (MSNS)
									TRUE or FALSE */
}e2eeInput_t;

/*! @brief This structure is used to output the E2EE Function.*/
typedef struct {
	char *track1;			/*!< Track1 encrypted, string null*/
	char *track2;			/*!< Track2 encrypted, string null*/
	char *pan;				/*!< Pan encrypted, string null*/
	char *expDate;			/*!< Expiry Date encrypted, string terminate*/
	char *cvv;				/*!< Cvv encrypted,  string null terminate, null terminate*/
	char *ksn;				/*!< KSN, string null terminate, null terminate*/
} e2eeOutput_t;



/* Definitions of secure parts */
/*! @brief This type identifies a secure part, relatively to its functionnalities.	*/
typedef enum {
	C_E2EE_PINCODE 	= 1,			/*!< secure part relative to the pincode entries; */
	C_E2EE_CARD 			= 2,		 	/*!< secure part relative to the card reader functions; */ 
	C_E2EE_CIPHERING = 3,			/*!< secure part relative to ciphering/deciphering data functions; 
	                            it is the default secure part used by high level functions */
	C_E2EE_KEYBOARD 	= 4,			/*!< secure part relative to keyboard entries other than pincode (FUTURE) */
	C_E2EE_DISPLAY 	= 5				/*!< secure part relative to displaying functions (FUTURE) */
} T_E2EE_PARTTYPE;


/* Values for cBoosterType in T_E2EE_CONFIG structure */
#define C_SEC_BL1	0					/*!< BL1 Booster : Value for cBoosterType in T_E2EE_CONFIG structure */
#define C_SEC_BL2	1					/*!< BL2 and more Booster : Value for cBoosterType in T_E2EE_CONFIG structure */

/* Values for ptszBoosterPeripheral, ptszIAPPName */
#define IAPP_DEF_NAME		"IAPP"								/*!< Internal Booster : Value for ptszBoosterPeripheral in T_SEC_CONFIG */
#define IAPP_USB_NAME		"IAPP_PPR"						/*!< External Booster USB link : Value for ptszBoosterPeripheral in T_SEC_CONFIG */
#define IAPP_USB_USR_NAME	"IAPP_CAD30USR"			/*!< External Booster CAD30USR : Value for ptszBoosterPeripheral in T_SEC_CONFIG */



/*! @brief This structure is used to modify the configuration of the Secure parts according to secure functionalities and available peripherals.	*/
typedef struct {                       
	T_E2EE_PARTTYPE	SecureType; 					/*!< Secure part to configure */
	char			cBoosterType; 							/*!< Booster Type : C_SEC_BL1 or C_SEC_BL2; Recommended value is C_SEC_BL2. */
	char * ptszBoosterPeripheral; 				/*!< Value is a pointer to IAPP_DEF_NAME ("IAPP") or IAPP_USB_NAME ("IAPP_PPR") or null pointer.
																					It is the peripheral Booster to use:
																					-	IAPP_DEF_NAME is the internal Booster
																					-	IAPP_USB_NAME is the external Booster on the USB link
 																																																	*/
	char   cbGestResid; 								  /*!< TRUE if the mainPeripheral has to manage resident schemes; Recommended value is TRUE. */
} T_E2EE_CONFIG;


/*
======================================================================
			                 Functions Definition
======================================================================
*/

/*! @brief This function calls the version of the API lib interface with E2EE DLL.
 *	@return The version.
 *   BCD format (4 bytes) : VVVVmmpp where
 *	 - VVVV : Major number
 *	 - mm : minor number
 *	 - pp : patch number
 *
 *	@link DLL_E2EE_GENERAL Back to top @endlink
 **/ 
int E2EE_libversion(void);

/*! @brief This function calls the version of the DLL services.
 *	@return Version as integer
 *   BCD format (4 bytes) : VVVVmmpp where
 *	 - VVVV : Major number
 *	 - mm : minor number
 *	 - pp : patch number
 *
 *  @return Error code (@link ERR_Schemes @endlink)

 *	@link DLL_E2EE_GENERAL Back to top @endlink
 **/
int E2EE_GetVersion (void);


/*! @brief This function is used to run a the encryption of a payment application integrated in an E2EE solution
 *
 *  Scheme to sign with your application: IngeCrypt
 *
 *  @param[in] 		inputData	: pointer to e2eeInput_t struct 
 *	@param[out]		outputData 	: pointer to e2eeOutput_t struct
 *  @param[out]		warnings : bit indicate warning (@link DLL_E2EE_WARNING @endlink)
 *
 *  @return Error code (@link DLL_E2EE_ERROR_CODES @endlink or @link ERR_Schemes @endlink)
 *
 *  @par Example:
 *  @include E2EE_Sample_01.c
 *
 *	@link DLL_E2EE_GENERAL Back to top @endlink
 **/
int E2EE_Format_And_Cipher(e2eeInput_t *inputData, e2eeOutput_t *outputData, int *warnings);


/*! @brief This function is used to return the version of PCI
 *	@param[out]	ptucVersionPCI	: Version of PCI
 *
 *  @return Error code (@link ERR_Schemes @endlink)
 *
 *	@link DLL_E2EE_GENERAL Back to top @endlink
 **/
int E2EE_GetPCIV3Module4VersionNumber(unsigned char * ptucVersionPCI);

/*! @brief This function is used to configure the secure parts according to the available peripherals and secure functionalities. 
 *
 *  The default configuration is made by the main component of the product (according to the MANAGER user interface for pinpad or UCMC application).
 *  In a multi-application context, every application can specify its own secure configuration.
 *  Use #E2EE_GetConfig to get the current configuration.
 *
 *  @param[in] iNbparts	 : Number of secure parts to configure
 *  @param[in] ptSecparts : Secure parts configuration
 *  @return OK if success otherwise error
 *  @note The application retrieves its default configuration if the parameter iNbparts is set to 0
 *
 *	@link DLL_E2EE_GENERAL Back to top @endlink
 **/
int E2EE_SetConfig (int iNbparts, T_E2EE_CONFIG ptSecparts[]);

/*! @brief This function is used to get the configuration of the secure parts for the current application; 
 *
 *  The returned configuration includes the default configuration for every secure part.

 *	@param[out] pt_iNbparts		: Number of configured secure parts
 *	@param[out] ptSecparts			: Secure parts configuration
 * 	@return OK if success otherwise error
 *
 *	@link DLL_E2EE_GENERAL Back to top @endlink
 **/
int E2EE_GetConfig (int * pt_iNbparts, T_E2EE_CONFIG ptSecparts[]);

#endif /* __E2EE_INTERF_H__ */

/*! @} **/
