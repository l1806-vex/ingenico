/*! @addtogroup DLLsecu_GENERAL
	* @{
	**/	

#ifndef __SEC_INTERF_H__
#define __SEC_INTERF_H__

/* include definition for SEC_SubmitPIN */
#include "crypto_def.h"

#ifndef SCHMGMT_H			/* SDK TPlus : No schmgmt.h */
typedef long SEG_ID; /*!< Secret Area Identifier Type / Scheme Identifier Type */
#endif


#ifndef _LIBIAPP_H_			/* SDK TPlus : No lib_iapp.h */
typedef enum {
   SYNC_VALID  =  0x01,								//!< 0x01 : OK 
   SYNC_CANCEL =  0x02,								//!< 0x02 : cancel
   SYNC_OTHER  =  0x03,								//!< 0x03 : other kind of synchro information 
   SYNC_ERROR  =  0x04								//!< 0x04 : default 
} T_IAPPSync;
#endif


#define EXIT_DLL_SEC       0x1900							/*!< Exit base value to call functions of DLL SECURITY */
#define EXIT_BASE_VALUE		EXIT_DLL_SEC				/*!< Exit base value to call functions of DLL SECURITY */

/*****************************************************************************************************/
/************************************** GENERAL SERVICES INTERFACE ***********************************/
/*****************************************************************************************************/

/* Definitions of secure parts */
/*! @brief This type identifies a secure part, relatively to its functionnalities.	*/
typedef enum {
	C_SEC_PINCODE 	= 1,			/*!< secure part relative to the pincode entries; 
															it is the default secure part used by high level functions as #SEC_PinEntryInit, #SEC_PinEntry. */						
	C_SEC_CARD 			= 2,		 	/*!< secure part relative to the card reader functions; 
	                            it is the default secure part used by high level functions as #SEC_SubmitPIN. */								
	C_SEC_CIPHERING = 3,			/*!< secure part relative to ciphering/deciphering data functions; 
	                            it is the default secure part used by high level functions */
	C_SEC_KEYBOARD 	= 4,			/*!< secure part relative to keyboard entries other than pincode (FUTURE) */
	C_SEC_DISPLAY 	= 5				/*!< secure part relative to displaying functions (FUTURE) */
} T_SEC_PARTTYPE;


/* Values for cBoosterType in T_SEC_CONFIG structure */
#define C_SEC_BL1	0					/*!< BL1 Booster : Value for cBoosterType in T_SEC_CONFIG structure */
#define C_SEC_BL2	1					/*!< BL2 and more Booster : Value for cBoosterType in T_SEC_CONFIG structure */

/* Values for ptszBoosterPeripheral, ptszIAPPName */
#define IAPP_DEF_NAME		"IAPP"								/*!< Internal Booster : Value for ptszBoosterPeripheral in T_SEC_CONFIG */
#define IAPP_USB_NAME		"IAPP_PPR"						/*!< External Booster USB link : Value for ptszBoosterPeripheral in T_SEC_CONFIG */
#define IAPP_USB_USR_NAME	"IAPP_CAD30USR"			/*!< External Booster CAD30USR : Value for ptszBoosterPeripheral in T_SEC_CONFIG */


/*! @brief This structure is used to modify the configuration of the Secure parts according to secure functionalities and available peripherals.	*/
typedef struct {                       
	T_SEC_PARTTYPE	SecureType; 					/*!< Secure part to configure */
	char			cBoosterType; 							/*!< Booster Type : C_SEC_BL1 or C_SEC_BL2; Recommended value is C_SEC_BL2. */
	char * ptszBoosterPeripheral; 				/*!< Value is a pointer to IAPP_DEF_NAME ("IAPP") or IAPP_USB_NAME ("IAPP_PPR") or null pointer.
																					It is the peripheral Booster to use:
																					-	IAPP_DEF_NAME is the internal Booster
																					-	IAPP_USB_NAME is the external Booster on the USB link
 																																																	*/
	char   cbGestResid; 								  /*!< TRUE if the mainPeripheral has to manage resident schemes; Recommended value is TRUE. */
} T_SEC_CONFIG;

/*! @brief This structure is used to get information about secret area.	*/
typedef struct {                       
	int iInternFormat; 					/*!< Internal Format Type (values are defined in SchutilTlv_def.h) */
	int iFreeMem; 						/*!< Free storage (in bytes)  */
	int iTotAvailMem; 					/*!< Total available storage (in bytes) */
} T_SEC_AREA_MEMORY;

/*
======================================================================
			                 Functions Definition
======================================================================
*/

/*! @brief This function calls the version of the API lib interface with SECURITY DLL.
 *	@return The version.
 *   BCD format (4 bytes) : VVVVmmpp where
 *	 - VVVV : Major number
 *	 - mm : minor number
 *	 - pp : patch number
 *
 *	@link DLLsecu_GENERAL Back to top @endlink
 **/ 
int SEClib_Version(void);


/*! @brief To open and initialise the security component
 *
 *  This call is @b mandatory before using the services of the security component.
 *	@return The return value of the ObjectLoad function. 0 is successful.
 *
 *	@link DLLsecu_GENERAL Back to top @endlink
 **/  
int SEClib_Open(void);

/*! @brief This function unloads the Security DLL.
 *
 *	@link DLLsecu_GENERAL Back to top @endlink
 **/
void SEClib_Close(void);

/*! @brief This function calls the version of the Security services.
 *	@return Version as integer (BCD format 4 bytes : VVVVmmpp)
 *
 *	@link DLLsecu_GENERAL Back to top @endlink
 **/  
int SEC_Version (void);


/*! @brief This function should be called once at the first loading of the DLL : automatic call by SEClib_open.
 *
 *	@link DLLsecu_GENERAL Back to top @endlink
 **/
void SEC_InitVar (void);

/*! @brief This function should be called by every user of the DLL : automatic call by SEClib_open
 *
 *	@link DLLsecu_GENERAL Back to top @endlink
 **/
void SEC_InitInstance (void);

/*! @brief This function is used to configure the secure parts according to the available peripherals and secure functionalities. 
 *
 *  The default configuration is made by the main component of the product (according to the MANAGER user interface for pinpad or UCMC application).
 *  In a multi-application context, every application can specify its own secure configuration.
 *  Use #SEC_GetConfig to get the current configuration.
 *
 *  @param[in] iNbparts	 : Number of secure parts to configure
 *  @param[in] ptSecparts : Secure parts configuration
 *  @return OK if success otherwise error
 *  @note The application retrieves its default configuration if the parameter iNbparts is set to 0
 *
 *	@link DLLsecu_GENERAL Back to top @endlink
 **/
int SEC_SetConfig (int iNbparts, T_SEC_CONFIG ptSecparts[]);

/*! @brief This function is used to get the configuration of the secure parts for the current application; 
 *
 *  The returned configuration includes the default configuration for every secure part.

 *	@param[out] pt_iNbparts		: Number of configured secure parts
 *	@param[out] ptSecparts			: Secure parts configuration
 * 	@return OK if success otherwise error
 *
 *	@link DLLsecu_GENERAL Back to top @endlink
 **/
int SEC_GetConfig (int * pt_iNbparts, T_SEC_CONFIG ptSecparts[]);


/*! @} **/



/*! @addtogroup DLLsecu_HIGH
	* @{
	**/	

/********************************************************************************************************/
/************************************** HIGH LEVEL SERVICES INTERFACE ***********************************/
/********************************************************************************************************/

#define C_SEC_ERR_PINENTRY_CURRENT		-50   /*!< Error code from #SEC_PinEntryInit, #SEC_PinEntry */

/*! @brief This structure is used to identify a data or a key in a secret area.	
 *  @note 1- For compatiblity  with "TLV standard secure schemes", a KeyId is computed in hexa form BBBBTTNN
 *  with BBBB : 2 MSB of uiBankId, TT : cAlgoType, NN : usNumber / 4
 *  @note 2- For compatiblity  with "standard secure schemes", offset is usNumber
 */
typedef struct {
	int				iSecretArea; 					/*!< Secret Area Id conform with "policy for secret Id": hexa form XXYY2T3Z
																- XXYY is the card signature VAR_ID
																- T is in the set [1.. F] hexa form
																- Z is in the set [0.. F] hexa form
	*/
	char			cAlgoType;   					/*!< Algorithm Type : values are defined in tlvVar_def.h 
																- TLV_TYPE_KDES      : DES algorithm
																- TLV_TYPE_KTDES     : double-length TDES algorithm (16 bytes)
																- TLV_TYPE_KTDES_24  : triple-length TDES algorithm (24 bytes)
																- TLV_TYPE_DESDUKPT  : DES Dukpt
																- TLV_TYPE_TDESDUKPT : TDES Dukpt
	@cond NOT_DOCUMENTED
																- TLV_TYPE_DESDUKPTLIGHT : DES Dukpt light memory algorithm
																- TLV_TYPE_TDESDUKPTLIGHT : TDES Dukpt light memory algorithm
	@endcond
																(see the previous note)
	*/
	unsigned short	usNumber;  		  /*!< Key/Data number multiple of 4 from 0 through 1023 (see the previous note) */
	unsigned int	uiBankId;    			/*!< Bank Id : 2 MSB from 8000 hexa through FFFF hexa, 2 LSB to 0000 (see the previous note) */
} T_SEC_DATAKEY_ID;


/*! @brief This structure is used to configure the pin entry	*/
typedef struct {
	unsigned char	ucEchoChar;			  /*!< Value of Echo character at every numeric entry */
	unsigned char	ucFontWidth;		  /*!< Font width (in pixels) (RFU) */
	unsigned char	ucFontHeight;		  /*!< Font height (in pixels) (RFU) */
	unsigned char	ucEchoLine;			  /*!< Line number to display echo characters (Reserved For Specific Schemes) */
	unsigned char	ucEchoColumn;		  /*!< Column number to display echo characters (RFU) */
	unsigned char	ucMinDigits;		  /*!< Min number of PIN digits to entry */
	unsigned char	ucMaxDigits;		  /*!< Max number of PIN digits to entry */
	int				iFirstCharTimeOut;    /*!< Timeout (msec) before the 1st key entry (For PCI PED Agreement, automatic limit to 60 sec) */
	int				iInterCharTimeOut;    /*!< Timeout (msec) between keys entries (For PCI PED Agreement, automatic limit to 60 sec) */
} T_SEC_ENTRYCONF;

/* Definitions of operation for SEC_ECBCipher and SEC_CBCCipher */
typedef enum {
	C_SEC_CIPHER_FUNC = 1,
	C_SEC_DECIPHER_FUNC = 2
} T_SEC_OPER_FUNCT;

/* Definitions for SEC_SubmitPIN */
typedef enum {
	C_SEC_SUBMIT_EMV_PLAINTEXT = 1,
	C_SEC_SUBMIT_EMV_RSA	   = 2
} T_SEC_FORMAT_PIN;

/*! @brief This structure is used for  SEC_listTLVKey	*/
typedef struct {
	T_SEC_DATAKEY_ID stDataKeyId; /*!< Key Id structure */
	int				iTLVKeySize;  /*!< internal TLV Key size (in bytes) */
	unsigned int	uiTLVKeyId;    /*!< internal TLV Key Id */
} T_SEC_LISTTLVKEY;

/*! @brief Definitions for the Extended Numeric entry : SEC_ExtNumEntryInit, SEC_ExtNumEntry */
#define C_SEC_EXTNUMTRY_CONT       	0   // to continue the numeric entry
#define C_SEC_EXTNUMTRY_HALT       	1   // to halt the numeric entry
#define C_SEC_EXTNUMTRY_HALT_END   	2   // to end the numeric entry scheme;

/*! @brief This structure is used to configure the Extended Numeric entry : #SEC_ExtNumEntryInit (See the detailed description in <a href="ICO-OPE-00120_Library_SECExtNumEntry.html">Library Extended Numeric entries </a>)	*/
typedef struct {
    int iFirstCharTimeOut;      			/*!< Timeout (in sec) before the 1rst key to enter */
    int iInterCharTimeOut;      			/*!< Timeout (in sec) between keys to enter */
    int iMaskInput;             			/*!< Input keys mask to use; it defines the keys to treat as input */
    int iHeadMessNo;            			/*!< Header Message number to display before the input.*/
    int iLineHeadMess;          			/*!< Line number position to display the Header Message (0 is the up line). */
    int iColHeadMess;           			/*!< Column number position to display the Header Mes-sage (0 is the left column). */
    int iFootMessNo;            			/*!< Footer Message number to display. */
    int iLineFootMess;          			/*!< Line number position to display the Footer Message (0 is the up line). */
    int iColFootMess;           			/*!< Column number position to display the Footer Message (0 is the left column). */
    int iLineVarMess;           			/*!< Line number position to display the variable Message (0 is the up line). */
    int iColVarMess;	        			/*!< Column number position to display the variable Mes-sage (0 is the left column). */
    int iMovableMessNo;         			/*!< Movable message number witch will be displayed at each call of API SEC_ExtNumEntry. */
    int iCurrencyCode;          			/*!< ISO 4217 currency numeric code. */
    int iLineCurrencyCode;      			/*!< Line number position to display the currency code (0 is the up line). */
    int iColCurrencyCode;       			/*!< Column number position to display the currency code (0 is the left column). */
    unsigned char ucMode;       			/*!< Display mode; values are: #C_NUMGEN_MODE_TEXT, #C_NUMGEN_MODE_GRAPH */
    unsigned char ucFontWidth;				/*!< Value of the 1rst parameter of startupcv20 */
    unsigned char ucFontHeight;				/*!< Value of the 2nd parameter of startupcv20  */
    int iBufferSize;            			/*!< Size of buffer (less than #C_MESSAGE_BUFFER_MAX_SIZE) */
    char *cBuffer;      					/*!< signed Messages buffer pointer */
    char *pt_szMessFileName;   				/*!< Pointer on messages FileName prefix */
    unsigned char ucRfu [30];   			/*!< Reserved for Future usage (to set to 0) */
} T_SEC_EXTNUMENTRYCONF;

/*
======================================================================
			           Functions Definition
======================================================================
*/

/*! @brief This function is used to list Id of secret area and loaded schemes
 *  @param[in] secureType 	      : Secure part to list
 *  @param[in, out] ptiNbId 			: pointer to an int, Number of Id in the list
 *  @param[in, out] tabiListId		: pointer to the array of list Id to output , Id of the list
 *  @return  OK or KO
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_listSecureId (T_SEC_PARTTYPE secureType, int * ptiNbId, int tabiListId []);

/*! @brief This function is used to test if a secret area has been allocated
 *  @param[in] secureType 				: Secure part
 *  @param[in] SecretIdToSearch   : Secret Area Id to search
 *  @return  OK if SecretIdToSearch exists KO if it does not exist
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_isSecretArea (T_SEC_PARTTYPE secureType, SEG_ID SecretIdToSearch);

/*! @brief This function is used to get the format type of a existing Secret area in a secure part
 *  or the default format type for non-existing Secret area.
 *
 *  Scheme to sign with your application: #NAM_SCH_UTILTLV
 *
 *  @param[in]   secureType       : Secure part
 *  @param[in]   SecretAreaId   
 *	@param[out]  ptiSecretType    : Format type (values are defined in SchutilTlv_def.h)
 *  @return     OK or @link ERR_Schemes Error @endlink
 *  @note Use SEC_isSecretArea to test the existence of a secret area.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_GetSecretAreaType (T_SEC_PARTTYPE secureType, SEG_ID SecretAreaId,  
							 int * ptiSecretType);

/*! @brief This function is used to get the offset of a Key/data in TLV_BL1 format in a Secret area in a secure part
 *
 *  Scheme to sign with your application: #NAM_SCH_UTILTLV
 *
 *  @param[in]    secureType 		  : Secure part
 *  @param[in]    SecretAreaId	
 *  @param[in]    TAGToSearch 		: Tag to search
 *  @param[in]    IdToSearch 			: Id to search
 *	@param[out]   ptiOffset				: offset of the val data/key (format TAG, ID, length, val)
 *  @return      OK or @link ERR_Schemes Error @endlink
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_GetOffsetTLVBL1 (T_SEC_PARTTYPE secureType, SEG_ID SecretAreaId, int TAGToSearch, int IdToSearch,
						   int * ptiOffset);


/*! @brief This function is used to create a Secret area in a secure part
 *
 *  Scheme to sign with your application: #NAM_SCH_LOAD_KEYTLV
 *
 *  @param[in] secureType 	: Secure part
 *  @param[in] SecretAreaId
 *  @param[in] iCardId 			: Card Number to protect the Secret Area
 *  @param[in] iVARId       : VAR Id to protect the Secret Area
 *  @return      OK or @link ERR_Schemes Error @endlink
 *  @note This function is only useful for BL1 booster
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_CreateSecretArea (T_SEC_PARTTYPE secureType, SEG_ID SecretAreaId,  
							 int iCardId, int iVARId);
							 
/*! @brief This function is used to free a Secret data/key in a secure part
 *
 *  If the secret area has format C_SEC_TLV, scheme 'TlvFree' is called.
 *
 *  If the secret area has format C_SEC_TLV_BL1, scheme 'STLFree' is called
 *
 *  If the secret area has the format C_SEC_NO_TLV, the scheme to call is 'SchLoadData' to set to 0 the secret key value or 'SchFree' to free the whole secret area.
 *
 *  Schemes to sign with your application: #NAM_SCH_UTILTLV #NAM_TLV_FREE_SECRET #NAM_SCH_FREE_SECRET
 *								#NAM_SCH_LOAD_DATA
 *
 *  @param[in] secureType 	: Secure part
 *  @param[in] ptDataKeyId	: Data/key to free (To free the whole secret area, set cAlgoType to 0)
 *  @return      OK or @link ERR_Schemes Error @endlink
 *  @note For secret area with format C_SEC_NO_TLV, only the whole secret area can be free.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_FreeSecret (T_SEC_PARTTYPE secureType, T_SEC_DATAKEY_ID * ptDataKeyId);

/*! @brief This function is used to load a Secret key in a secure part
 *
 *  The key value is DES or TDES ciphered (ECB mode) with a ciphering key.
 *
 *  A TDES key is 16 bytes length (#TLV_TYPE_KTDES) or 24 bytes length (#TLV_TYPE_KTDES_24).
 *
 *  If the secure part is a BL1 booster and if the secret area does not exist, then an error is returned.
 *
 *  If the secret area has the format C_SEC_NO_TLV, the scheme to call is 'SchLoadData'.
 *
 *  If the secret area has the format C_SEC_TLV_BL1, the scheme to call is 'SloadKeyTlv'.
 *
 *  If the secret area has the format C_SEC_TLV or If (the secure part is a BL2 booster and the secret area does not exist), the scheme to call is 'TlvLoadKey'
 *
 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_SCH_LOAD_KEYTLV,
 *                            #NAM_TLV_LOAD_KEY, #NAM_SCH_LOAD_DATA, NAM_TLV_FIRSTKEY (TlvFirstKey T10-MOCKUP)
 *  @param[in] secureType 		: Secure part
 *  @param[in] ptCipherKeyId  : CipherKey used to cipher the key to load (cAlgoType of the ciphering key is #TLV_TYPE_KDES, #TLV_TYPE_KTDES or #TLV_TYPE_KTDES_24)
 *  @param[in] ptKeyId 				: Key to load (cAlgoType of the key to load is #TLV_TYPE_KDES, #TLV_TYPE_KTDES or #TLV_TYPE_KTDES_24)
 *  @param[in] ptKeyValue 		: DES/TDES Ciphered value (ECB mode) of the Key to load (its length is 8, 16 or 24 bytes) 
 *  @param[in] iUsage 				:Key usage; values are defined in tlvVar_def.h (#CIPHERING_KEY, #CIPHERING_PIN or #CIPHERING_DATA)
 *  @return      OK or @link ERR_Schemes Error @endlink
 *	@note #TLV_TYPE_KTDES_24 only exists for secret area format C_SEC_TLV; The ciphered key value must agree with an odd parity plaintext value if the ciphering key is #TLV_TYPE_KTDES_24.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_LoadKey (T_SEC_PARTTYPE secureType, T_SEC_DATAKEY_ID * ptCipherKeyId, T_SEC_DATAKEY_ID * ptKeyId,
				 unsigned char * ptKeyValue, int iUsage);

/*! @brief This function is used to initialise parameters for the following secure Pincode entry #SEC_PinEntry
 *  @param[in] ptstEntryConfig 		: PinCode Entry configuration
 *  @param[in] secureType 			  : Secure part to transfer the PinCode; If the Pincode is processed by another application, 
 			the value to use is the expected location of the Pin Code by the other application (expected value for PIN offline 
 			processing by old versions of EMV-DC is #C_SEC_CARD).
			We recommend to use #C_SEC_PINCODE for PIN online applications.

 *  @return     OK or @link ERR_Schemes Error @endlink
 *	@note If this function is called, no other application can enter the pincode until the application ends the pincode entry.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_PinEntryInit (T_SEC_ENTRYCONF * ptstEntryConfig, T_SEC_PARTTYPE secureType);

/*! @brief This function is used to manage the secure Pincode entry
 *
 *  This function has to be called after #SEC_PinEntryInit
 *
 *  Signed Schemes with security DLL: #NAM_SCH_GET_PIN, schemes of TransfertToBooster
 *  @param[in, out] pt_uiEventToWait 	: [in] events to wait (0 only TimeOut to manage), [out] received event if the returned value is @link ERR_Schemes#ERR_TIMEOUT ERR_TIMEOUT @endlink
 *  @param[in, out] ptibToContinue		: [in] FALSE to end Pincode entry or TRUE to continue with #SEC_PinEntry, [out] FALSE PinEntry is finished 
 *	@param[out]     pt_ucKey 					: if not 0 it is the last entry key otherwise 0 for TimeOut input
 *  @return   OK or @link ERR_Schemes#ERR_TIMEOUT ERR_TIMEOUT (received event) @endlink or #C_SEC_ERR_PINENTRY_CURRENT or @link ERR_Schemes Error @endlink
 *	@note Management of the display for characters to echo has to be made by the application.
 *        TimeOut Input is not an event : return is OK, *ptibToContinue is FALSE and *pt_ucKey is 0
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_PinEntry (unsigned int * pt_uiEventToWait, unsigned char * pt_ucKey, int * ptibToContinue);

/*! @brief This function is used to encipher the PIN according to ISO9564 (ANSI X9.8)
 *
 *	The PIN code has been entered previously on the secure Pincode part (#C_SEC_PINCODE) and optionally transferred 
     according to the parameter SecureTypePinToTransfer of #SEC_PinEntryInit, and then ISO9564 Pin ciphering is made on the secure part 
     containing the PIN Key (parameter SecureTypeKey). If these secure parts are different, then a TransfertToBooster is called.
 *
 *	If the secret area has the format C_SEC_NO_TLV, the scheme to call is 'SchIso9564'.
 *
 *	If the secret area has the format C_SEC_TLV_BL1, the scheme 'SchutilTlv' is called to retrieve the offset 
 			in the secret area of the key and then the scheme 'SchIso9564o' is called.
 *
 *	If the secret area has the format C_SEC_TLV, the scheme to call is 'TlvIso9564'.

 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_ISO9564, "SchIso9564o"
 *  @param[in] 		secureType 			: Secure part
 *  @param[in] 		ptCipherKeyId 	: Ciphering Key to use (cAlgoType is #TLV_TYPE_KDES, #TLV_TYPE_KTDES or #TLV_TYPE_KTDES_24)
 *  @param[in] 		iFormat 				: ISO9564 Format : format 0 (ISO9564_F0_DES, ISO9564_F0_TDES, ISO9564_F0_TDES_24),
																format 1 (ISO9564_F1_DES, ISO9564_F1_TDES, ISO9564_F1_TDES_24),
																format 2 (ISO9564_F2_DES, ISO9564_F2_TDES, ISO9564_F2_TDES_24, ISO9564_F2_OTHER),
																format 3 (ISO9564_F3_DES, ISO9564_F3_TDES, ISO9564_F3_TDES_24),
																format 8 (ISO9564_F0_F8_DES, ISO9564_F0_F8_TDES, ISO9564_F3_F8_DES, ISO9564_F3_F8_TDES)
 *  @param[in] 		pt_inputPAN_TCounter 	: PAN value (8 bytes) for formats 0, 3 and 8
												or TC value (8 bytes) for format 1
												or NULL pointer for other formats 
 *	@param[out]   pt_OutputData 	: output ciphered data 
 *	@param[out]   pt_uiOutputDataLength 	: length (in bytes) of output ciphered data 
 *  @return      OK or @link ERR_Schemes Error @endlink
 *	@note For BL1 booster, parameter ptCipherKeyId must have the key number equal to 0.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_Iso9564 (T_SEC_PARTTYPE secureType, T_SEC_DATAKEY_ID * ptCipherKeyId, int iFormat,
				 unsigned char * pt_inputPAN_TCounter,
				 unsigned char *pt_OutputData, unsigned int * pt_uiOutputDataLength);

/*! @brief This function is used to load the Key Serial Number (KSN) for DUKPT algorithm
 *
 *	This function uses ActionCode DUKPT_LOAD_KSN.
 *
 *	If the secret area does not exist and if the secure part is a BL1 booster then an error is returned.
 *
 *	If the secret area has the format C_SEC_NO_TLV or C_SEC_TLV_BL1, the scheme to call is 
    'SchDukpt' or 'SchDukpTDes' otherwise 'TlvDukpt' or 'TlvDukpTDes'.

 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_DUKPT_DES, #NAM_TLV_DUKPT_TDES
 *                            "SchDukpt", "SchDukpTDes"
	@cond NOT_DOCUMENTED
							,#NAM_TLV_DUKPT_LIGHT_DES, #NAM_TLV_DUKPT_LIGHT_TDES
	@endcond
 *  @param[in] 		secureTypeKey 		: Secure part
 *  @param[in] 		ptDukptId		 	: DUKPT Identifier to use (cAlgoType determines the Dukpt Algorithm to use
											DES Dukpt (TLV_TYPE_DESDUKPT), TDES Dukpt (TLV_TYPE_TDESDUKPT)
	@cond NOT_DOCUMENTED
											,DES Dukpt light memory (TLV_TYPE_DESDUKPTLIGHT) or TDES Dukpt light memory (TLV_TYPE_TDESDUKPTLIGHT) )
	@endcond
 *  @param[in] 		ptKSNValue 				: KSN value (8 bytes) 
 *  @return      OK or @link ERR_Schemes Error @endlink
 *  @note We call SMID the value of 10 bytes which is composed of: 59 bits for KSN + 21 bits for counter.   
 *  @note SMID (10bytes) = KSN(59bits) + COUNTER(21bits) 
 *  @note The KSN(59bits) are provided by the first 59 bits from the input parameter ptKSNValue.  
 *  @note The COUNTER(21bits) is generated automatically. 
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_DukptLoadKSN (T_SEC_PARTTYPE secureTypeKey, T_SEC_DATAKEY_ID * ptDukptId, 
				 unsigned char * ptKSNValue);

/*! @brief This function is used to load the Derivation Key (16 bytes) to use later to generate the initial key for DUKPT algorithm
 *
 *	The Derivation key is TDES ciphered. This function uses ActionCode DUKPT_LOAD_RIGHT_PART_DERIVATION_KEY and DUKP_LOAD_LEFT_PART_DERIVATION_KEY.
 *
 *	If the secure part is a BL1 booster and if the secret area does not exist then an error is returned.
 *	If the secret area has the format C_SEC_NO_TLV or C_SEC_TLV_BL1, the scheme to call is 
    'SchDukpt' or 'SchDukpTDes' otherwise 'TlvDukpt' or 'TlvDukpTDes'.

 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_DUKPT_DES, #NAM_TLV_DUKPT_TDES
 *                            "SchDukpt", "SchDukpTDes", #NAM_SCH_CIPHER_PR
	@cond NOT_DOCUMENTED
								,#NAM_TLV_DUKPT_LIGHT_DES, #NAM_TLV_DUKPT_LIGHT_TDES
	@endcond
 *  @param[in] 		secureTypeKey			: Secure part
 *  @param[in] 		ptDukptId		 		: DUKPT Identifier to use (cAlgoType determines the Dukpt Algorithm to use
											DES Dukpt (TLV_TYPE_DESDUKPT), TDES Dukpt (TLV_TYPE_TDESDUKPT)
	@cond NOT_DOCUMENTED
											,DES Dukpt light memory (TLV_TYPE_DESDUKPTLIGHT) or TDES Dukpt light memory (TLV_TYPE_TDESDUKPTLIGHT) )
	@endcond
 *  @param[in] 		ptCipherKeyId 			: Identifier of the TDES ciphering key 
 *  @param[in] 		ptDerivationValue : Ciphered Derivation Key value (16 bytes) 
 *  @return   OK or @link ERR_Schemes Error @endlink
 *	@note - We use the scheme #NAM_SCH_CIPHER_PR to TDES decipher the derivation key for the schemes 'SchDukpt' and 'SchDukpTDes'.
 *  @note - This function is disabled with schemes version greater than 820365v0203 and an error is returned.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_DukptLoadDerivationKey (T_SEC_PARTTYPE secureTypeKey, T_SEC_DATAKEY_ID * ptDukptId, 
								T_SEC_DATAKEY_ID * ptCipherKeyId,
								unsigned char * ptDerivationValue);

/*! @brief This function is used to load the Initial Key (8/16 bytes if DES/TDES Dukpt) for DUKPT algorithm
 *         and to initialise the set of 21 keys and counter. This Initial Key is TDES ciphered (ECB mode).
 *
 *	This function uses ActionCode DUKPT_LOAD_LEFT_PART_KEY,  DUKP_LOAD_RIGHT_PART_KEY and DUKPT_LOAD_KEY.
 *	If the secure part is a BL1 booster and if the secret area does not exist then an error is returned.
 *
 *	If the secret area has the format C_SEC_NO_TLV or C_SEC_TLV_BL1, the scheme to call is 'SchDukpt' or 'SchDukpTDes' otherwise 'TlvDukpt' or 'TlvDukpTDes'.

 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_DUKPT_DES, #NAM_TLV_DUKPT_TDES
 *                        "SchDukpt", "SchDukpTDes", #NAM_SCH_CIPHER_PR
	@cond NOT_DOCUMENTED
						,#NAM_TLV_DUKPT_LIGHT_DES, #NAM_TLV_DUKPT_LIGHT_TDES
	@endcond
 *  @param[in] 		secureTypeKey 		: Secure part
 *  @param[in] 		ptDukptId		 	: DUKPT Identifier to use (cAlgoType determines the Dukpt Algorithm to use
											DES Dukpt (TLV_TYPE_DESDUKPT), TDES Dukpt (TLV_TYPE_TDESDUKPT)
	@cond NOT_DOCUMENTED
											,DES Dukpt light memory (TLV_TYPE_DESDUKPTLIGHT) or TDES Dukpt light memory (TLV_TYPE_TDESDUKPTLIGHT) )
	@endcond
 *  @param[in] 		ptCipherKeyId 		: Identifier of the TDES ciphering key (in the same secret area as the DUKPT Id)
 *  @param[in] 		ptInitialKeyValue : Ciphered Initial Key value (8 or 16 bytes) (ECB ciphering mode)
 *  @return      OK or @link ERR_Schemes Error @endlink
 *	@note We use the scheme 'SchCipherPR' to TDES decipher the derivation key for the schemes 'SchDukpt' and 'SchDukpTDes'.
 *	@note The ciphering key ptCipherKeyId and the DUKPT keys ptDukptId must be in the same secret area.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_DukptLoadInitialKey (T_SEC_PARTTYPE secureTypeKey, T_SEC_DATAKEY_ID * ptDukptId, 
								T_SEC_DATAKEY_ID * ptCipherKeyId,
								unsigned char * ptInitialKeyValue);

/*! @brief This function is used to load the Initial Key (8/16 bytes if DES/TDES Dukpt) for DUKPT algorithm,
 *         to verify and compute its Key checksum value
 *         and to initialise the set of 21 keys and counter. This Initial Key is TDES ciphered (ECB mode).
 *         The key checksum value are the 3 most significant bytes result
 *         of TDES ciphering 8 null data bytes with the Initial key value TDES Dukpt.
 *
 *	This function uses ActionCode DUKPT_LOAD_LEFT_PART_KEY,  DUKP_LOAD_RIGHT_PART_KEY and DUKPT_LOAD_KEY.
 *	If the secure part is a BL1 booster and if the secret area does not exist then an error is returned.
 *
 *	If the secret area has the format C_SEC_NO_TLV or C_SEC_TLV_BL1, the scheme to call is 'SchDukpt' or 'SchDukpTDes' otherwise 'TlvDukpt' or 'TlvDukpTDes'.

 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_DUKPT_DES, #NAM_TLV_DUKPT_TDES
 *                        "SchDukpt", "SchDukpTDes", #NAM_SCH_CIPHER_PR
	@cond NOT_DOCUMENTED
						,#NAM_TLV_DUKPT_LIGHT_DES, #NAM_TLV_DUKPT_LIGHT_TDES
	@endcond
 *  @param[in] 		secureTypeKey 		: Secure part
 *  @param[in] 		ptDukptId		 	: DUKPT Identifier to use (cAlgoType determines the Dukpt Algorithm to use
											DES Dukpt (TLV_TYPE_DESDUKPT), TDES Dukpt (TLV_TYPE_TDESDUKPT)
	@cond NOT_DOCUMENTED
											,DES Dukpt light memory (TLV_TYPE_DESDUKPTLIGHT) or TDES Dukpt light memory (TLV_TYPE_TDESDUKPTLIGHT) )
	@endcond
 *  @param[in] 		ptCipherKeyId 		: Identifier of the TDES ciphering key (in the same secret area as the DUKPT Id)
 *  @param[in] 		ptInitialKeyValue : Ciphered Initial Key value (8 or 16 bytes) (ECB ciphering mode)
 *	@param[out]     pt_OutputKeyChecksum : 3 bytes KCV
 *	@param[out]     pt_uiOutputChecksumLength  : KCV length (3 if no computation error)
 *  @return      OK or @link ERR_Schemes Error @endlink
 *	@note We use the scheme 'SchCipherPR' to TDES decipher the derivation key for the schemes 'SchDukpt' and 'SchDukpTDes'.
 *	@note The ciphering key ptCipherKeyId and the DUKPT keys ptDukptId must be in the same secret area.
 *  @note At the end of this function, the Initial Key is erased with schemes version greater than 820365v0108
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_DukptLoadInitialKeyAndVerify (T_SEC_PARTTYPE secureTypeKey, T_SEC_DATAKEY_ID * ptDukptId, 
								T_SEC_DATAKEY_ID * ptCipherKeyId,
								unsigned char * ptInitialKeyValue,
								unsigned char * pt_OutputKeyChecksum, unsigned int * pt_uiOutputChecksumLength);

/*! @brief This function is used to generate the initial Key (8/16 bytes if DES/TDES Dukpt) for DUKPT algorithm
 *               by derivation of the Key Serial Number KSN (8 bytes) with the Derivation Key (16 bytes)
 *               and to initialise the set of 21 keys and counter.
 *
 *	This function uses ActionCode DUKPT_INITIAL_KEY_CREATION and DUKP_LOAD_KEY.
 *
 *	If the secure part is a BL1 booster and if the secret area does not exist then an error is returned.
 *
 *	If the secret area has the format C_SEC_NO_TLV or C_SEC_TLV_BL1, the scheme to call is 'SchDukpt' or 'SchDukpTDes' otherwise 'TlvDukpt' or 'TlvDukpTDes'.

 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_DUKPT_DES, #NAM_TLV_DUKPT_TDES
 *                            "SchDukpt", "SchDukpTDes"
	@cond NOT_DOCUMENTED
							,#NAM_TLV_DUKPT_LIGHT_DES, #NAM_TLV_DUKPT_LIGHT_TDES
	@endcond
 *  @param[in] 		secureTypeKey 	: Secure part
 *  @param[in] 		ptDukptId		 	: DUKPT Identifier to use (cAlgoType determines the Dukpt Algorithm to use
											DES Dukpt (TLV_TYPE_DESDUKPT), TDES Dukpt (TLV_TYPE_TDESDUKPT)
	@cond NOT_DOCUMENTED
											,DES Dukpt light memory (TLV_TYPE_DESDUKPTLIGHT) or TDES Dukpt light memory (TLV_TYPE_TDESDUKPTLIGHT) )
	@endcond
 *  @return      OK or @link ERR_Schemes Error @endlink
 *	@note This function is disabled with schemes version greater than 820365v0203 and an error is returned.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_DukptGenerateInitialKey (T_SEC_PARTTYPE secureTypeKey, T_SEC_DATAKEY_ID * ptDukptId);

/*! @brief This function is used to get the current status of DES/TDES DUKPT algorithm
 * The typical case to activate the DUKPT functions (status DUKPT_IN_FUNCTION) is to call SEC_DukptLoadKSN and then to call SEC_DukptLoadInitialKey.
 *
 *	If the secure part is a BL1 booster and if the secret area does not exist then an error is returned.
 *
 *	If the secret area has the format C_SEC_NO_TLV or C_SEC_TLV_BL1, the scheme to call is 'SchDukpt' or 'SchDukpTDes' otherwise 'TlvDukpt' or 'TlvDukpTDes'.
 *
 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_DUKPT_DES, #NAM_TLV_DUKPT_TDES
 *                            "SchDukpt", "SchDukpTDes"
	@cond NOT_DOCUMENTED
											,#NAM_TLV_DUKPT_LIGHT_DES, #NAM_TLV_DUKPT_LIGHT_TDES
	@endcond
 *  @param[in] 		secureTypeKey 	: Secure part
 *  @param[in] 		ptDukptId		 	: DUKPT Identifier to use (cAlgoType determines the Dukpt Algorithm to use
											DES Dukpt (TLV_TYPE_DESDUKPT), TDES Dukpt (TLV_TYPE_TDESDUKPT)
	@cond NOT_DOCUMENTED
											,DES Dukpt light memory (TLV_TYPE_DESDUKPTLIGHT) or TDES Dukpt light memory (TLV_TYPE_TDESDUKPTLIGHT) )
	@endcond
 *	@param[out]   pt_iStatus 			: @link ERR_Schemes#ERR_ID_NOT_FOUND ERR_ID_NOT_FOUND @endlink or status (DUKPT_IN_FUNCTION or DUKPT_END_OF_LIFE)
 *                                        The status is DUKPT_IN_FUNCTION when SEC_DukptLoadKSN and SEC_DukptLoadInitialKey have been successfull.
 *  @return    OK or @link ERR_Schemes Error @endlink
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_DukptStatus (T_SEC_PARTTYPE secureTypeKey, T_SEC_DATAKEY_ID * ptDukptId, int * pt_iStatus);

/*! @brief This function is used to stop and delete the data of DES/TDES DUKPT algorithm
 *
 *	If the secure part is a BL1 booster and if the secret area does not exist then an error is returned.
 *
 *	If the secret area has the format C_SEC_NO_TLV or C_SEC_TLV_BL1, the scheme to call is 'SchDukpt' or 'SchDukpTDes' otherwise 'TlvDukpt' or 'TlvDukpTDes'.
 *
 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_DUKPT_DES, #NAM_TLV_DUKPT_TDES
 *                            "SchDukpt", "SchDukpTDes"
	@cond NOT_DOCUMENTED
							,#NAM_TLV_DUKPT_LIGHT_DES, #NAM_TLV_DUKPT_LIGHT_TDES
	@endcond
 *  @param[in] 		secureTypeKey 	: Secure part
 *  @param[in] 		ptDukptId		 	: DUKPT Identifier to use (cAlgoType determines the Dukpt Algorithm to use
											DES Dukpt (TLV_TYPE_DESDUKPT), TDES Dukpt (TLV_TYPE_TDESDUKPT)
	@cond NOT_DOCUMENTED
											,DES Dukpt light memory (TLV_TYPE_DESDUKPTLIGHT) or TDES Dukpt light memory (TLV_TYPE_TDESDUKPTLIGHT) )
	@endcond
 *  @return      OK or @link ERR_Schemes Error @endlink
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_DukptStopDelete (T_SEC_PARTTYPE secureTypeKey, T_SEC_DATAKEY_ID * ptDukptId);

/*! @brief This function is used to encrypt the PIN with DES/TDES DUKPT algorithm; The supported PIN block formats are formats 0 and 3.
 *
 *	The PIN code has been entered previously on the secure Pincode part (#C_SEC_PINCODE) and optionally transferred 
     according to the parameter SecureTypePinToTransfer of #SEC_PinEntryInit.
	 If this Pin code location is different from the Dukpt Secure part (parameter secureTypeKey), a TransfertToBooster is called.
 *
 *	If the secure part is a BL1 booster and if the secret area does not exist then an error is returned.
 *
 *	If the secret area has the format C_SEC_NO_TLV or C_SEC_TLV_BL1, the scheme to call is 'SchDukpt' or 'SchDukpTDes' otherwise 'TlvDukpt' or 'TlvDukpTDes'.

 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_DUKPT_DES, #NAM_TLV_DUKPT_TDES
 *                            "SchDukpt", "SchDukpTDes"
	@cond NOT_DOCUMENTED
							,#NAM_TLV_DUKPT_LIGHT_DES, #NAM_TLV_DUKPT_LIGHT_TDES
	@endcond
 *  @param[in] 		secureTypeKey 	: Secure part
 *  @param[in] 		ptDukptId		 	: DUKPT Identifier to use (cAlgoType determines the Dukpt Algorithm to use
											DES Dukpt (TLV_TYPE_DESDUKPT), TDES Dukpt (TLV_TYPE_TDESDUKPT)
	@cond NOT_DOCUMENTED
											,DES Dukpt light memory (TLV_TYPE_DESDUKPTLIGHT) or TDES Dukpt light memory (TLV_TYPE_TDESDUKPTLIGHT) )
	@endcond
 *  @param[in] 		iFormat 				: DUKPT_ENCRYPT_PIN or DUKPT_ENCRYPT_PIN_F3 
 *  @param[in] 		pt_inPANValue 	: PAN value (8 bytes) 
 *	@param[out]   pt_outputPIN 		: output encrypted PIN (8 bytes)
 *	@param[out]   pt_outputSMID 	: output SMID transaction (10 bytes)
 *  @return      OK or @link ERR_Schemes Error @endlink
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_DukptEncryptPin (T_SEC_PARTTYPE secureTypeKey, T_SEC_DATAKEY_ID * ptDukptId, int iFormat,
						 unsigned char * pt_inPANValue, unsigned char * pt_outputPIN,
						 unsigned char * pt_outputSMID);

/*! @brief This function is used to verify and compute the Key checksum value of a TDES Dukpt
 *     key (Initial key or Derivation Key);
 *
 *   The key checksum value are the 3 most significant bytes result
 *        of TDES ciphering 8 null data bytes with the key value.
 *
 *	If the secure part is a BL1 booster and if the secret area does not exist then an error is returned.
 *
 *	If the secret area has the format C_SEC_NO_TLV or C_SEC_TLV_BL1, the scheme to call is 'SchDukpt' or 'SchDukpTDes' otherwise 'TlvDukpt' or 'TlvDukpTDes'.

 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_DUKPT_TDES
	@cond NOT_DOCUMENTED
											,#NAM_TLV_DUKPT_LIGHT_DES, #NAM_TLV_DUKPT_LIGHT_TDES
	@endcond
 *  @param[in] 		secureTypeKey 				: Secure part
 *  @param[in] 		ptDukptId 				: DUKPT Identifier to compute KCV (cAlgoType determines the Dukpt Algorithm to use
											 TDES Dukpt (TLV_TYPE_TDESDUKPT)
	@cond NOT_DOCUMENTED
											,DES Dukpt light memory (TLV_TYPE_DESDUKPTLIGHT) or TDES Dukpt light memory (TLV_TYPE_TDESDUKPTLIGHT)
	@endcond
 *  @param[in] 		ibInitialKey 			: TRUE for KCV InitialKey, FALSE for KCV DerivationKey 
 *	@param[out]   pt_OutputKeyChecksum : 3 bytes KCV
 *	@param[out]   pt_uiOutputChecksumLength  : KCV length (3)
 *  @return   OK or @link ERR_Schemes Error @endlink
 *	@note 1 - The KCV of Derivation Key is disabled with schemes version greater than 820365v0205 and an error is returned.
 *  @note 2 - When the DUKPT algorithm is initiated, the Initial Key is erased with schemes version greater than 820365v0108
 *            and the output KCV is 0x8CA64D.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_DukptKeyVerify (T_SEC_PARTTYPE secureTypeKey, T_SEC_DATAKEY_ID * ptDukptId,
						int ibInitialKey, 
						unsigned char * pt_OutputKeyChecksum, unsigned int * pt_uiOutputChecksumLength);

/*! @brief This function is used to encipher/decipher DES/TDES data in ECB mode
 *
 *	If the secret area has the format C_SEC_NO_TLV, the scheme to call is 'SchCipherPR'.
 *
 *	If the secret area has the format C_SEC_TLV_BL1, the scheme 'SchutilTlv' is called to retrieve the offset in the secret area of the key and then the scheme 'SchCipherPR' is called.
 *
 *	If the secret area has the format C_SEC_TLV, the scheme to call is 'TlvCipherDa'.
 *
 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_CIPHER_DATA, #NAM_SCH_CIPHER_PR
 *  @param[in] 		ptCipherKeyId 		: Ciphering Key to use (cAlgoType determines the Algorithm to use
											DES (#TLV_TYPE_KDES) or TDES (#TLV_TYPE_KTDES/#TLV_TYPE_KTDES_24) )
 *  @param[in] 		iOper 						: Cipher (C_SEC_CIPHER_FUNC) or Decipher (C_SEC_DECIPHER_FUNC) operation 
 *  @param[in] 		pt_inputData 			: Data to cipher/decipher 
 *  @param[in] 		uiInputDataLength : length in bytes of Data to cipher/decipher
 *	@param[out]   pt_OutputData 		: output ciphered/deciphered data 
 *	@param[out]   pt_uiOutputDataLength : length (in bytes) of output ciphered/deciphered data (multiple of 8) 
 *  @return      OK or @link ERR_Schemes Error @endlink
 *	@note 1 - The secure part #C_SEC_CIPHERING is used for the scheme running.
 *
 *	      2 - If the length of input data is not multiple of 8, then padding null bytes are added
 *            and the length of output data is multiple of 8 greater than length of input data.
 *
 *	      3 - For compatibility with old format using the offset, offset is relative to the 8th byte in the secret area.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_ECBCipher (T_SEC_DATAKEY_ID * ptCipherKeyId, T_SEC_OPER_FUNCT iOper,
				 unsigned char * pt_inputData, unsigned int uiInputDataLength,
				 unsigned char *pt_OutputData, unsigned int * pt_uiOutputDataLength);

/*! @brief This function is used to encipher/decipher DES/TDES data in CBC mode
 *
 *	If the secret area has the format C_SEC_NO_TLV, the scheme to call is 'SchCipherPR'.
 *
 *	If the secret area has the format C_SEC_TLV_BL1, the scheme 'SchutilTlv' is called to retrieve the offset in the secret area of the key and then the scheme 'SchCipherPR' is called.
 *
 *	If the secret area has the format C_SEC_TLV, the scheme to call is 'TlvCipherDa'.
 *
 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_CIPHER_DATA, #NAM_SCH_CIPHER_PR
 *  @param[in] 		ptCipherKeyId 		: Ciphering Key to use (cAlgoType determines the Algorithm to use
											DES (#TLV_TYPE_KDES) or TDES (#TLV_TYPE_KTDES/#TLV_TYPE_KTDES_24) )
 *  @param[in] 		iOper 						: Cipher (#C_SEC_CIPHER_FUNC) or Decipher (#C_SEC_DECIPHER_FUNC) operation 
 *  @param[in] 		pt_inputData 			: Data to cipher/decipher 
 *  @param[in] 		uiInputDataLength : length in bytes of Data to cipher/decipher
 *  @param[in] 		pt_IV  						: pointer to 8 bytes ICV value (or NULL pointer if 8 bytes zero value)
 *	@param[out]   pt_OutputData 		: output ciphered/deciphered data 
 *	@param[out]   pt_uiOutputDataLength : length (in bytes) of output ciphered/deciphered data (multiple of 8)
 *  @return      OK or @link ERR_Schemes Error @endlink
 *	@note 1 - The secure part #C_SEC_CIPHERING is used for the scheme running.
 *
 *	      2 - If the length of input data is not multiple of 8, then padding null bytes are added
 *            and the length of output data is multiple of 8 greater than length of input data.
 *
 *	      3 - For compatibility with old format using the offset, offset is relative to the 8th byte in the secret area.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_CBCCipher (T_SEC_DATAKEY_ID * ptCipherKeyId, T_SEC_OPER_FUNCT iOper,
				 unsigned char * pt_inputData, unsigned int uiInputDataLength,
				 unsigned char * pt_IV,
				 unsigned char * pt_OutputData, unsigned int * pt_uiOutputDataLength);

/*! @brief This function is used to compute MAC with DES/TDES ciphering algorithm in CBC mode (see ANNEX "CBC MAC algorithm" in the document "Security DLL Reference guide"). 
 *
 *	This function computes a 8 bytes MAC.
 *
 *	If the secret area has the format C_SEC_NO_TLV, the scheme to call is 'SchCipherPR'.
 *
 *	If the secret area has the format C_SEC_TLV_BL1, the scheme 'SchutilTlv' is called to retrieve the offset in the secret area of the key and then the scheme 'SchCipherPR' is called.
 *
 *	If the secret area has the format C_SEC_TLV, the scheme to call is 'TlvCipherDa' for DES or 'TlvMacTDes' for TDES.
 *
 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_CIPHER_DATA, #NAM_SCH_CIPHER_PR
 *								NAM_TLV_MAC_TDES ("TlvMacTDes")
 *  @param[in] 		ptCipherKeyId 		: Ciphering Key to use (cAlgoType determines the Algorithm to use
											DES (#TLV_TYPE_KDES) or TDES (#TLV_TYPE_KTDES/#TLV_TYPE_KTDES_24) )
 *  @param[in] 		pt_inputData 			: Input Data for MAC calculation 
 *  @param[in] 		uiInputDataLength : length in bytes of Input Data for MAC calculation
 *  @param[in] 		pt_IV  						: pointer to 8 bytes ICV value (or NULL pointer if 8 bytes zero value)
 *	@param[out]   pt_OutputMAC 			: computed MAC buffer (8 bytes)
 *  @return      OK or @link ERR_Schemes Error @endlink
 *	@note 1 - The secure part #C_SEC_CIPHERING is used for the scheme running.
 *
 *	      2 - If the length of input data is not multiple of 8, then padding null bytes are added.
 *
 *	      3 - For compatibility with old format using the offset, offset is relative to the 8th byte in the secret area.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_ComputeMAC (T_SEC_DATAKEY_ID * ptCipherKeyId,
				 unsigned char * pt_inputData, unsigned int uiInputDataLength,
				 unsigned char * pt_IV,
				 unsigned char * pt_OutputMAC);

/*! @brief This function is used to verify MAC according to DES/TDES ciphering algorithm in CBC mode (see ANNEX "CBC MAC algorithm" in the document "Security DLL Reference guide")
 *
 *	This function verifies an 8 bytes MAC.
 *
 *	If the secret area has the format C_SEC_NO_TLV, the scheme to call is 'SchCipherPR'.
 *
 *	If the secret area has the format C_SEC_TLV_BL1, the scheme 'SchutilTlv' is called to retrieve the offset in the secret area of the key and then the scheme 'SchCipherPR' is called.
 *
 *	If the secret area has the format C_SEC_TLV, the scheme to call is 'TlvCipherDa' for DES or 'TlvMacTDes' for TDES.
 *
 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_CIPHER_DATA, #NAM_SCH_CIPHER_PR
 *								NAM_TLV_MAC_TDES ("TlvMacTDes")
 *  @param[in] 		ptCipherKeyId 		: Ciphering Key to use (cAlgoType determines the Algorithm to use
											DES (#TLV_TYPE_KDES) or TDES (#TLV_TYPE_KTDES/#TLV_TYPE_KTDES_24) )
 *  @param[in] 		pt_inputData 			: Input Data for MAC calculation 
 *  @param[in] 		uiInputDataLength : length in bytes of Input Data for MAC calculation
 *  @param[in] 		pt_IV  						: pointer to 8 bytes ICV value (or NULL pointer if 8 bytes zero value)
 *  @param[in] 		pt_MACToVerify 		: MAC buffer to verify (8 bytes)
 *  @return      OK or @link ERR_Schemes Error @endlink
 *	@note 1 - The secure part #C_SEC_CIPHERING is used for the scheme running.
 *
 *	      2 - If the length of input data is not multiple of 8, then padding null bytes are added.
 *
 *	      3 - For compatibility with old format, offset is relative to the 8th byte in the secret area.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_VerifyMAC (T_SEC_DATAKEY_ID * ptCipherKeyId,
				 unsigned char * pt_inputData, unsigned int uiInputDataLength,
				 unsigned char * pt_IV,
				 unsigned char * pt_MACToVerify);

/*! @brief This function is used to submit the PIN to the card reader secure part (#C_SEC_CARD part)
 *
 *	This function can use schemes of TransfertToBooster if the card reader part and the location of the pincode entry are different.


 *
 *  Signed Schemes with the Security DLL: "s_PresenPin" for EMV Pin format
 *
 * <TABLE border="3" cellspacing="0" bordercolor="red">
 * <TR><TD></TD></TR>
 * <TR><TD>  <strong> WARNING: </strong> <b> Format C_SEC_SUBMIT_EMV_RSA : The application must verify the integrity and the authenticity of the RSA public Key by using the signature Telium system verification. </b></TD></TR>
 * <TR><TD></TD></TR>
 * </TABLE>

 *  @param[in] 		iPinFormat 			: Pin format to submit the PIN (C_SEC_SUBMIT_EMV_PLAINTEXT, C_SEC_SUBMIT_EMV_RSA...)
 *  @param[in] 		iPinLength 			: Pincode length (number of digits)
 *  @param[in] 		pt_inputAPDU 		: APDU command to send according to iPinFormat (otherwise NULL)
 *  @param[in] 		pt_stPublicKey 	: RSA public key according to iPinFormat (otherwise NULL) 
 *	@param[out]   pt_outputAPDU 	: APDU response from the card 
 *  @par Detailed parameters description

 *	@verbatim  
          Pin Format Values (iPinFormat)      APDU command (pt_inputAPDU)      Public Key (pt_stPublicKey)
          ------------------------------      ---------------------------      ---------------------------
		  
            C_SEC_SUBMIT_EMV_PLAINTEXT          NULL pointer                     NULL pointer

            C_SEC_SUBMIT_EMV_RSA                ->length is 8                    ->bits is the number of bits of the public key
                                                ->data is the unpredictable      ->modulus MSB first
                                                value (8 bytes)                  ->exponent MSB first
 *	@endverbatim 
 *  @par Detailed APDU response pt_outputAPDU :
 *	@verbatim  
            ->length        :   Card response (in bytes) + 3

            ->data          :   - Card response ( (->length - 3) bytes ) of function EMV_apdu
                            :   - SW1			(1 byte) of the CARD response of function EMV_apdu
                            :   - SW2			(1 byte) of the CARD response of function EMV_apdu
                            :   - CR_CAM		(1 byte) returned from function EMV_apdu if bit CAM_PRESENT is set
                                                         otherwise returned from function status.
 *	@endverbatim 
 *  @return      OK or @link ERR_Schemes Error @endlink
 *	@note  The secure part #C_SEC_CARD is used to run the scheme submitting the APDU command.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_SubmitPIN (T_SEC_FORMAT_PIN iPinFormat, int iPinLength,
					T_APDU * pt_inputAPDU,
					R_RSA_PUBLIC_KEY * pt_stPublicKey,
					T_APDU * pt_outputAPDU);

/*! @brief This function is used to verify and compute the Key checksum value of a DES/TDES key
 *               (whatever its usage is)
 *
 * This key is a DES/TDES key (#TLV_TYPE_KDES, #TLV_TYPE_KTDES, #TLV_TYPE_KTDES_24).
 *
 * A TDES key is 16 bytes length (#TLV_TYPE_KTDES) or 24 bytes length (#TLV_TYPE_KTDES_24).
 *
 * The key checksum value are the 3 most significant bytes result of DES/TDES ciphering 8 null 
          data bytes with the key value for key types #TLV_TYPE_KDES, #TLV_TYPE_KTDES. #TLV_TYPE_KTDES_24
 *
 *	If the secret area has the format C_SEC_TLV, the scheme to call is 'TlvKeyVerif' otherwise the scheme to call is 'schCipherPR'.

 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_SCH_CIPHER_PR,
 *                            #NAM_TLV_KEYVERIF, 
 *  @param[in] 		secureType 		: Secure part
 *  @param[in] 		ptKeyId 			: Key to compute KCV 
										(cAlgoType is DES (#TLV_TYPE_KDES) or TDES (#TLV_TYPE_KTDES or #TLV_TYPE_KTDES_24) )
 *	@param[out]   pt_OutputKeyChecksum : 3 bytes KCV
 *	@param[out]   pt_uiOutputChecksumLength : KCV length (3)
 *  @return    OK or @link ERR_Schemes Error @endlink
 *	@note #TLV_TYPE_KTDES_24 only exists for secret area format C_SEC_TLV.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_KeyVerify (T_SEC_PARTTYPE secureType, T_SEC_DATAKEY_ID * ptKeyId,
				 unsigned char * pt_OutputKeyChecksum, unsigned int * pt_uiOutputChecksumLength);

/*! @brief This function is useful to call some specific schemes having no High Level API.
 *
 *  @param[in] 		secPartOrg 		: Secure part
 *  @param[in] 		secPartDest		: Secure part 
 *  @return    OK or @link ERR_Schemes Error @endlink
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_TransfertToBooster (T_SEC_PARTTYPE secPartOrg, T_SEC_PARTTYPE secPartDest);

/*! @brief This function is useful to call some specific schemes having no High Level API.
 *
 *  @return    OK or @link ERR_Schemes Error @endlink
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_LocatePin (void);

/*! @brief This function is used to compute MAC with TDES ciphering algorithm X9.19-1996 Annex C in CBC mode
 *
 *	For TLV_TYPE_KTDES key: The 1st DES key value is the MSB 8 bytes of the TDES key and the 2nd DES key value is the LSB 8 bytes of the TDES key.
 *
 *	This function computes a 8 bytes MAC.
 *
 *	If the secret area has the format C_SEC_NO_TLV, the scheme to call is 'SchCipherPR'.
 *
 *	If the secret area has the format C_SEC_TLV_BL1, the scheme 'SchutilTlv' is called to retrieve the offset in the secret area of the key and then the scheme 'SchCipherPR' is called.
 *
 *	If the secret area has the format C_SEC_TLV, the scheme to call is 'TlvCipherDa' for DES or 'TlvMacTDes' for TDES.
 *
 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_CIPHER_DATA, #NAM_SCH_CIPHER_PR,
 *								NAM_TLV_MAC_TDES ("TlvMacTDes")
 *  @param[in] 		ptCipherKeyId 		: Ciphering Key to use (cAlgoType must be set to TDES (#TLV_TYPE_KTDES/#TLV_TYPE_KTDES_24) )
 *  @param[in] 		pt_inputData 			: Input Data for MAC calculation 
 *  @param[in] 		uiInputDataLength : length in bytes of Input Data for MAC calculation
 *  @param[in] 		pt_IV  						: pointer to 8 bytes ICV value (or NULL pointer if 8 bytes zero value)
 *	@param[out]   pt_OutputMAC 			: computed MAC buffer (8 bytes)
 *  @return      OK or @link ERR_Schemes Error @endlink
 *	@note 1 - The secure part #C_SEC_CIPHERING is used for the scheme running.
 *
 *	      2 - If the length of input data is not multiple of 8, then padding null bytes are added.
 *
 *	      3 - For compatibility with old format using the offset, offset is relative to the 8th byte in the secret area.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_ComputeMAC_AC (T_SEC_DATAKEY_ID * ptCipherKeyId,
				 unsigned char * pt_inputData, unsigned int uiInputDataLength,
				 unsigned char * pt_IV,
				 unsigned char * pt_OutputMAC);

/*! @brief This function is used to verify MAC according to TDES ciphering algorithm X9.19-1996 Annex C in CBC mode
 *
 *	For TLV_TYPE_KTDES key: The 1st DES key value is the MSB 8 bytes of the TDES key and the 2nd DES key value is the LSB 8 bytes of the TDES key.
 *
 *	This function verifies an 8 bytes MAC.
 *
 *	If the secret area has the format C_SEC_NO_TLV, the scheme to call is 'SchCipherPR'.
 *
 *	If the secret area has the format C_SEC_TLV_BL1, the scheme 'SchutilTlv' is called to retrieve the offset in the secret area of the key and then the scheme 'SchCipherPR' is called.
 *
 *	If the secret area has the format C_SEC_TLV, the scheme to call is 'TlvCipherDa' for DES or 'TlvMacTDes' for TDES.
 *
 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_CIPHER_DATA, #NAM_SCH_CIPHER_PR,
 *								NAM_TLV_MAC_TDES ("TlvMacTDes")
 *  @param[in] 		ptCipherKeyId 		: Ciphering Key to use (cAlgoType must be set to TDES (#TLV_TYPE_KTDES/#TLV_TYPE_KTDES_24) )
 *  @param[in] 		pt_inputData 			: Input Data for MAC calculation 
 *  @param[in] 		uiInputDataLength : length in bytes of Input Data for MAC calculation
 *  @param[in] 		pt_IV  						: pointer to 8 bytes ICV value (or NULL pointer if 8 bytes zero value)
 *  @param[in] 		pt_MACToVerify 		: MAC buffer to verify (8 bytes)
 *  @return    OK or @link ERR_Schemes Error @endlink
 *	@note 1 - The secure part #C_SEC_CIPHERING is used for the scheme running.
 *
 *	      2 - If the length of input data is not multiple of 8, then padding null bytes are added.
 *
 *	      3 - For compatibility with old format using the offset, offset is relative to the 8th byte in the secret area.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_VerifyMAC_AC (T_SEC_DATAKEY_ID * ptCipherKeyId,
				 unsigned char * pt_inputData, unsigned int uiInputDataLength,
				 unsigned char * pt_IV,
				 unsigned char * pt_MACToVerify);

/*! @brief This function is used to get the status and the current transaction SMID of TDES DUKPT algorithm 
 *
 *	If the secret area does not exist or if the secret area has the format C_SEC_NO_TLV then an error is returned.
 *
 *  Schemes to sign with your application: #NAM_SCH_UTILTLV, #NAM_TLV_DUKPT_TDES
	@cond NOT_DOCUMENTED
											,#NAM_TLV_DUKPT_LIGHT_DES, #NAM_TLV_DUKPT_LIGHT_TDES
	@endcond
 *  @param[in] 		secureTypeKey 	: Secure part
 *  @param[in] 		ptDukptId 				: DUKPT Identifier to compute KCV (cAlgoType determines the Dukpt Algorithm to use
											 TDES Dukpt (TLV_TYPE_TDESDUKPT)
	@cond NOT_DOCUMENTED
											,DES Dukpt light memory (TLV_TYPE_DESDUKPTLIGHT) or TDES Dukpt light memory (TLV_TYPE_TDESDUKPTLIGHT)
	@endcond
 *	@param[out]   pt_OutputSMID 	: 10 bytes current SMID
 *  @return      OK or @link ERR_Schemes Error @endlink
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_DukptGetSMID (T_SEC_PARTTYPE secureTypeKey, T_SEC_DATAKEY_ID * ptDukptId,
						  unsigned char * pt_OutputSMID);


/*! @brief This function is used to generate random data bytes 
 *
 *  Signed Schemes with security DLL: #NAM_SCH_RANDOM
 *  @param[in] 		uiRandomLength 		: Length in bytes of random data to generate
 *  @param[in] 		pt_OutRandomData 	: generated random data
 *  @return      OK or @link ERR_Schemes Error @endlink
 *	@note  The secure part #C_SEC_CIPHERING is used for the scheme running.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_RandomData (unsigned int uiRandomLength, unsigned char * pt_OutRandomData);

/*! @brief This function is used to compute a SHA1.
 *         A message digest is computed using SHA-1 algorithm (FIPS 180-1).
 *
 *  Signed Schemes with security DLL: NAM_SCH_SHA_COMPUTE ("Sch_Shacomp")
 *  @param[in] 		secureType 		: Secure part
 *  @param[in] 		pt_InputData 	:Input Data Buffer for calculation
 *  @param[in] 		uiInputDataLength : Length in bytes of the Input Data
 *	@param[out]   pt_OutputData 		: Output Data buffer
 *	@param[out]   pt_uiOutputDataLength  : length (in bytes) of output data (20 for SHA1)
 *  @return      OK or @link ERR_Schemes Error @endlink
 *  @par TEST CASE #1 :
 *	@verbatim  
             Input message : 616263 (hexa form)
             SHA-1         : A9993E364706816A BA3E25717850C26C 9CD0D89D (hexa form)
 *	@endverbatim 
 *  @par TEST CASE #2 :
 *	@verbatim  
             Input message : 1,000,000 repetitions of the character 'a'
             SHA-1         : 34AA973CD4C4DAA4 F61EEB2BDBAD2731 6534016F (hexa form)
 *	@endverbatim 
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_SHA1Compute (T_SEC_PARTTYPE secureType, 
					unsigned char * pt_InputData, unsigned int uiInputDataLength,
					unsigned char * pt_OutputData, unsigned int * pt_uiOutputDataLength);


/*! @brief This function is used to get information about a Secret area in a secure part 
 *
 *  Scheme to sign with your application: #NAM_SCH_COMPL_UTILTLV
 *  @param[in] 		SecPart 	 : Secure part
 *  @param[in] 		SecretAreaId : Secret Area Id
 *  @param[out] 	pt_stMemArea : Information about the secret Area (Internal Format, Free storage, Total available storage)
 *  @return      OK or @link ERR_Schemes Error @endlink
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_GetSecretAreaMemory (T_SEC_PARTTYPE SecPart, SEG_ID SecretAreaId,  
							 T_SEC_AREA_MEMORY * pt_stMemArea);


/*! @brief This function is used to list TLV keys in a Secret area of a secure part 
 *
 *  Scheme to sign with your application: #NAM_TLV_STLLIST_TLV ("STLList_Tlv")
 *  @param[in] 		SecPart 	 : Secure part
 *  @param[in] 		SecretAreaId : Secret Area Id
 *  @param[in]  iMaxtabstKeyList : max size array tabstKeyList
 *  @param[out] *ptiNbtabstKeyList : Number of TLV Keys in the aray tabstKeyList
 *  @param[out] 	tabstKeyList : array of TLV keys
 *  @return      OK or @link ERR_Schemes Error @endlink
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_listTLVKeys (T_SEC_PARTTYPE SecPart, SEG_ID SecretAreaId, int iMaxtabstKeyList,
					int * ptiNbtabstKeyList, T_SEC_LISTTLVKEY tabstKeyList []);

					
/*! @brief This function is used to load a Secret key format TR31 in a Secret area of a secure part.
 *         TR31 format compliance : "Interoperable Secure Key Exchange Key Block Specification for Symmetric Algorithms: TR31 2010 "
 *         Supported values :
 *         - Key Block Version Id : 'A' (0x41), 'B' (0x42), or 'C' (0x43) 
 *         - Key usage : Data Encryption ('D0'), Key Encryption or wrapping ('K0'), or PIN encryption ('P0')
 *         - Algorithm : DEA ('D', 0x44) or TDEA ('T', 0x54)
 *
 *  Scheme to sign with your application: #NAM_TLV_LOAD_KEY_TR31
 *  @param[in] SecPart 	         : Secure part
 *  @param[in] ptKBPCipherKeyId  : KBPCipher Key to use for TR31 format (cAlgoType is #TLV_TYPE_KTDES or #TLV_TYPE_KTDES_24) 
 *                                 previously loaded with usage TR31_KBPK_KEY in the same secret area as the Key to load ptKeyId
 *  @param[in] ptKeyId 		 : Key to load (cAlgoType of the key has no meaning, it is conform with ptKeyTR31Value)
 *  @param[in] uiLengthTR31Value : Length in bytes of the TR31 Key value 
 *  @param[in] ptKeyTR31Value    : TR31 Key value of the Key to load
 *  @return      OK or @link ERR_Schemes Error @endlink
 *	@note The KBPCipher Key ptKBPCipherKeyId and the key to load ptKeyId must be in the same secret area.
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_TR31LoadKey (T_SEC_PARTTYPE SecPart, T_SEC_DATAKEY_ID * ptKBPCipherKeyId, T_SEC_DATAKEY_ID * ptKeyId,
					 unsigned int uiLengthTR31Value, unsigned char * ptKeyTR31Value);


/*! @brief This function is used to initialise the parameters for the extended numeric entry #SEC_ExtNumEntry.
 *  @param[in] ptstExtNumEntryConfig : Extended Numeric entry configuration
 *  @param[in] SecureTypeNumEntry 	 : Secure part to use for the extended numeric entry.

 *  @return     OK or @link ERR_Schemes Error @endlink
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_ExtNumEntryInit (T_SEC_EXTNUMENTRYCONF *ptstExtNumEntryConfig, 
                      T_SEC_PARTTYPE SecureTypeNumEntry);

/*! @brief This function is used to manage the extended numeric entry. Every Key input is returned.
 *         See the detailed description in <a href="ICO-OPE-00120_Library_SECExtNumEntry.html">Library Extended Numeric entries </a>
 *
 *  This function has to be called after #SEC_ExtNumEntryInit
 *
 *  Signed Scheme with security DLL: #NAM_SCH_ENMENTRY
 *  @param[in, out] pt_uiEventToWait 	: [in] events to wait (0 only TimeOut to manage), [out] received event if the returned value is @link ERR_Schemes#ERR_TIMEOUT ERR_TIMEOUT @endlink
 *  @param[in, out] ptibToContinue		: [in] #C_SEC_EXTNUMTRY_HALT to halt the numeric entry, or #C_SEC_EXTNUMTRY_HALT_END to end the numeric entry scheme, or #C_SEC_EXTNUMTRY_CONT to continue with #SEC_ExtNumEntry,
 *                                        [out] #C_SEC_EXTNUMTRY_CONT if the numeric entry is halted and has to be continued (case of received events or key input) with #SEC_ExtNumEntry, or #C_SEC_EXTNUMTRY_HALT if the numeric entry is halted by the application (case [in] #C_SEC_EXTNUMTRY_HALT) and has to be ended with #SEC_ExtNumEntry, or #C_SEC_EXTNUMTRY_HALT_END if the numeric entry scheme is finished.
 *  @param[in]      ucVarMessage        : Movable message position (line/column) and variable message to display (See the detailed description in <a href="ICO-OPE-00120_Library_SECExtNumEntry.html">Library Extended Numeric entries </a>)
 *  @param[in]      uiLengthParam       : Length (in bytes) of the optional parameters (Reserved for future usage 0).
 *  @param[in]      pt_ucParam          : Optional parameters for the extended numeric entry (Reserved for future usage NULL pointer).
 *	@param[out]     pt_ucKey 		    : #SYNC_ERROR if the numeric entry is halted, or 0 if timeout occurs, otherwise it is the last input key
 *  @return   OK or @link ERR_Schemes#ERR_TIMEOUT ERR_TIMEOUT (received event) @endlink or @link ERR_Schemes#ERR_ENTRY_CANCELED ERR_ENTRY_CANCELED if the application ends the scheme @endlink or @link ERR_Schemes Error @endlink
 *	@note This function only runs with BL2 Booster and more.
 *  @note TimeOut Input is not an event : return is OK, *ptibToContinue is #C_SEC_EXTNUMTRY_HALT_END and *pt_ucKey is 0
 *
 *	@link DLLsecu_HIGH Back to top @endlink
 **/
int SEC_ExtNumEntry (unsigned int * pt_uiEventToWait,
				  int *ptibToContinue,
				  unsigned char ucVarMessage[],
				  unsigned int uiLengthParam,
				  unsigned char *pt_ucParam,
				  unsigned char *pt_ucKey);

/*! @} **/


/*! @addtogroup DLLsecu_MEDIUM
	* @{
	**/	

/**********************************************************************************************************/
/************************************** MEDIUM LEVEL SERVICES INTERFACE ***********************************/
/**********************************************************************************************************/


/* IAPP Protocol used for Scheme Communication in SEC_ExecScheme function : cProtocol parameter           */
#define C_PROTOCOL_NO     			0				/*!< NO IAPP communication : Value for the parameter cProtocol in the function #SEC_ExecScheme */
#define C_PROTOCOL_NOSYNC 			1				/*!< NOSYNC protocol : Value for the parameter cProtocol in the function #SEC_ExecScheme */
#define C_PROTOCOL_SYNC   			2				/*!< SYNC protocol : Value for the parameter cProtocol in the function #SEC_ExecScheme */ 
#define C_PROTOCOL_NO_OUTPUT  	3 			/*!< NO_OUTPUT protocol : Value for the parameter cProtocol in the function #SEC_ExecScheme */


/* For SEC_ExecSch Function */
/*! @brief This structure is useful to define a secure scheme to load in a booster.	*/
typedef struct {
	char * ptszSchemeName;		  /*!< Scheme Full Name (Null terminated string !) */
	SEG_ID Id_P; 								/*!< Secret area ID to load the Scheme */
	char cbResident; 						/*!< Values are :
																	-	TRUE  to keep the scheme loaded at the end of its execution
																	-	FALSE to unload the scheme at the end of its execution.
 																																													*/
} T_SEC_EXECSCH;

/* For SEC_ExecSch Function */
/*! @brief This structure is useful to define parameters and data to send to a secure scheme.	*/
typedef struct {
	int ipar0; 										/*!< 1st parameter for the secure scheme  */
	int ipar1; 										/*!< 2nd parameter for the secure scheme  */
	int ipar2; 										/*!< 3rd parameter for the secure scheme  */
	int ipar3; 										/*!< 4th parameter for the secure scheme  */
	unsigned int uilendatain;			/*!< Length in bytes of data to send to the secure scheme  */
	unsigned char * pt_ucdatain;	/*!< Data to send to the secure scheme  */
} T_SEC_PARAM;


/* For SEC_InitStepScheme, SEC_StepScheme Function */
/*! @brief This structure is used to define the protocol to communicate with the secure scheme.	*/
typedef struct {
	char cProtocol; 							/*!< Values are : #C_PROTOCOL_SYNC, #C_PROTOCOL_NOSYNC */
	unsigned int *  pt_iEvents; 	/*!< Input : Pointer to Event to wait with TimeOut, Output : Received Event */
	int i_iTimeOut; 							/*!< TimeOut for event waiting in msec */
} T_SEC_STEPPROT;


/*! @brief This function is used to run a Scheme with parameters (no asynchronous event 
 *               management during the scheme execution).
 *  @param[in] 		secureType 		: Associated secure part 
 *  @param[in] 		pt_Execsch 		: Definition of the secure scheme to use
 *  @param[in] 		pt_param 			: Parameters for the secure scheme
 *	@param[out]   pt_icodeOut 	: Returned code value by the scheme 			
 *	@param[out]   pt_dataout		: Optional data output returned by the secure scheme
 *	@param[out]   pt_lendataout	: Length (in bytes) of optional data output returned by the secure scheme		
 *  @param[in]    cProtocol			: Protocol communication; values are : #C_PROTOCOL_NO, #C_PROTOCOL_SYNC, #C_PROTOCOL_NOSYNC
 *  @return OK, KO, @link ERR_Schemes#ERR_BAD_IAPP_OPERATION ERR_BAD_IAPP_OPERATION @endlink, @link ERR_Schemes#ERR_TIMEOUT ERR_TIMEOUT @endlink 
 *
 *	@link DLLsecu_MEDIUM Back to top @endlink
 **/
int SEC_ExecScheme (T_SEC_PARTTYPE secureType, 
					T_SEC_EXECSCH * pt_Execsch,
				  T_SEC_PARAM * pt_param, int * pt_icodeOut,
				  unsigned char * pt_dataout, unsigned int * pt_lendataout,
					char cProtocol 
					);

/*! @brief This function is used to run a Scheme with parameters (no asynchronous event 
 *               management during the scheme execution) with optional IAPP Synchro waiting.
 *  @param[in] 		ibInfiniteWaiting : TRUE for IAPP Synchro waiting otherwise FALSE 
 *  @param[in] 		secureType 		: Associated secure part 
 *  @param[in] 		pt_Execsch 		: Definition of the secure scheme to use
 *  @param[in] 		pt_param 			: Parameters for the secure scheme
 *	@param[out]   pt_icodeOut 	: Returned code value by the scheme 			
 *	@param[out]   pt_dataout		: Optional data output returned by the secure scheme
 *	@param[out]   pt_lendataout	: Length (in bytes) of optional data output returned by the secure scheme		
 *  @param[in]    cProtocol			: Protocol communication; values are : #C_PROTOCOL_NO, #C_PROTOCOL_SYNC, #C_PROTOCOL_NOSYNC
 *  @return OK, KO, @link ERR_Schemes#ERR_BAD_IAPP_OPERATION ERR_BAD_IAPP_OPERATION @endlink, @link ERR_Schemes#ERR_TIMEOUT ERR_TIMEOUT @endlink 
 *
 *	@link DLLsecu_MEDIUM Back to top @endlink
 **/
int SEC_ExecSchemeWait (int ibInfiniteWaiting, T_SEC_PARTTYPE secureType, 
					T_SEC_EXECSCH * pt_Execsch,
				  T_SEC_PARAM * pt_param, int * pt_icodeOut,
				  unsigned char * pt_dataout, unsigned int * pt_lendataout,
					char cProtocol 
					);


/*! @brief This function is used to run a Scheme with parameters (asynchronous event management)
 *         This is the first step in the kinematics.
 *         Next steps are managed by the function #SEC_StepScheme.
 *         And the end of the communication is managed by the function #SEC_EndStepScheme.
 *  @param[in] 		secureType 	: Associated secure part 
 *  @param[in] 		pt_Execsch 	: Definition of the secure scheme to use	
 *  @param[in] 		pt_param 		: Parameters for the secure scheme
 *	@param[out]   pt_icodeOut : Returned code value by the scheme 		
 *	@param[out]   pt_dataout	: optional data output returned by the secure scheme
 *	@param[out]   pt_lendataout	: length (in bytes) of optional data output returned by the secure scheme
 *  @param[in] 		pt_ststepProt	: Parameters for the protocol communication
 *  @return OK, KO, @link ERR_Schemes#ERR_BAD_IAPP_OPERATION ERR_BAD_IAPP_OPERATION @endlink, @link ERR_Schemes#ERR_TIMEOUT ERR_TIMEOUT @endlink 
 *
 *	@link DLLsecu_MEDIUM Back to top @endlink
 **/
int SEC_InitStepScheme (T_SEC_PARTTYPE secureType,
					T_SEC_EXECSCH * pt_Execsch,
				  T_SEC_PARAM * pt_param, int * pt_icodeOut,
				  unsigned char * pt_dataout, unsigned int * pt_lendataout,
					T_SEC_STEPPROT * pt_ststepProt);

/*! @brief This function is used to run a Scheme with parameters (asynchronous event management)
 *         The first step in the kinematics is managed by the function #SEC_InitStepScheme.
 *         And the end of the communication is managed by the function #SEC_EndStepScheme.
 *  @param[in] 		uilendatain 	: Length (in bytes) of data to send to the secure scheme
 *  @param[in] 		pt_ucdatain 	: Data to send to the secure scheme	
 *	@param[out]   pt_icodeOut 	: Returned code value by the scheme 
 *	@param[out]   pt_dataout		: optional data output returned by the secure scheme
 *	@param[out]   pt_lendataout	: length (in bytes) of optional data output returned by the secure scheme	
 *  @param[in] 		pt_ststepProt	: Parameters for the protocol communication
 *  @return OK, KO, @link ERR_Schemes#ERR_BAD_IAPP_OPERATION ERR_BAD_IAPP_OPERATION @endlink, @link ERR_Schemes#ERR_TIMEOUT ERR_TIMEOUT @endlink 
 *
 *	@link DLLsecu_MEDIUM Back to top @endlink
 **/
int SEC_StepScheme (unsigned int uilendatain,
					unsigned char * pt_ucdatain, int * pt_icodeOut,
				  unsigned char * pt_dataout, unsigned int * pt_lendataout,
					T_SEC_STEPPROT * pt_ststepProt);

/*! @brief This function is used to end the scheme communication with event management, initiated with #SEC_InitStepScheme.
 *  @return OK, KO, error code 
 *
 *	@link DLLsecu_MEDIUM Back to top @endlink
 **/
int SEC_EndStepScheme (void);

/*! @brief This function is used to end the scheme communication with event management, initiated with #SEC_InitStepScheme.
 *  @param[in] 		ibWaitEnd 	: TRUE to wait for the end event from the scheme otherwise FALSE not to wait for the end event from the scheme
 *  @return OK, KO, error code 
 *
 *	@link DLLsecu_MEDIUM Back to top @endlink
 **/
int SEC_EndStepSchemeWait (int ibWaitEnd);

/*! @brief This function is used to free optional resident Scheme
 *  @param[in] 		secureType 	: Associated secure part 
 *  @return      OK or KO
 *
 *	@link DLLsecu_MEDIUM Back to top @endlink
 **/
int SEC_FreeScheme (T_SEC_PARTTYPE secureType);

/*! @} **/


/*! @addtogroup DLLsecu_LOW
	* @{
	**/	

/**********************************************************************************************************/
/************************************** LOW LEVEL SERVICES INTERFACE ***********************************/
/**********************************************************************************************************/

#define C_LEN_SCHEME_NAME 12			/*!< Length of scheme name (including the null terminator) */

#define C_LEN_STR_GETSCHVERS 80  /*!< Length of ASCII string (including the null terminator) used as parameters */

/* Scheme Type : C_DLL_SCH, C_APPLI_SCH, C_NOT_FOUND_SCH for T_SCH_INF structure */
#define C_DLL_SCH 			 0				/*!< Embedded Scheme in DLL SECURITY : Value of cType in T_SCH_INF */
#define C_APPLI_SCH			 1				/*!< Embedded Scheme in the application : Value of cType in T_SCH_INF */
#define C_NOT_FOUND_SCH      2				/*!< Embedded Scheme not found : Value of cType in T_SCH_INF */

/*! @brief This structure is used for compatibility with old version CMP_SECURITY  <= 1.2 */
typedef struct {
	char * ptszMainPeripheral; 			/*!< Pointer to IAPP_DEF_NAME or IAPP_USB_NAME */
	char   cbGestMainResid; 				/*!< TRUE if the mainPeripheral has to manage resident schemes */
	char * ptszSecondPeripheral;		/*!< Pointer to IAPP_DEF_NAME or IAPP_USB_NAME or NULL if no secondary peripheral */
	char   cbGestSecondResid; 			/*!< TRUE if the SecondaryPeripheral has to manage resident schemes */
} T_SCH_OPEN;

/*! @brief This structure is used to define a secure scheme to load in a booster.	*/
typedef struct {
	char * ptszSchemeName; 					/*!< Full name of the secure scheme to load (Null terminated string) */
	char * ptszIAPPName;  					/*!< Value is a pointer to IAPP_DEF_NAME ("IAPP") or IAPP_USB_NAME ("IAPP_PPR") or IAPP_USB_USR_NAME ("IAPP_CAD30USR")
																	It is the peripheral Booster to use:
																	-	IAPP_DEF_NAME is the internal Booster
																	-	IAPP_USB_NAME is the external Booster on the USB link
																	-	IAPP_USRB_USR_NAME is the external Booster on the USB link for CAD30USR.
																																																								 */
	SEG_ID Id_P; 										/*!< Secret area ID to load the Scheme */
	char cbResident; 								/*!< Values are :
																			-	TRUE  to keep the scheme loaded at the end of its execution
																			-	FALSE to unload the scheme at the end of its execution.
 																																																						*/
} T_SCH_INIT;

/*! @brief This structure gives information about a secure scheme to load.	*/
typedef struct {
	char szSchemeName[C_LEN_SCHEME_NAME]; 		/*!< Scheme Full Name (Null terminated string) (NULL value if no found scheme */
	char cType;  															/*!< Secure scheme location : C_DLL_SCH (in the security component) 
	                                          , C_APPLI_SCH (in the application) 
	                                          or C_NOT_FOUND_SCH (no scheme found). */
	unsigned short usVersion; 								/*!< Secure scheme version (the most significant byte is the 
	                                          version number and the other is the minor number) */
} T_SCH_INF;

/* usFctNo : C_SCH_BAD_CERTIF, C_SCH_CALL_SYST, C_SCH_PUTCRC_SYST, C_SCH_COPY_SYST, C_SCH_DALLOC_SYST for T_SCH_SYST_INF structure */
#define C_SCH_BAD_CERTIF 			 1				/*!< BAD CERTIFICAT FORMAT : Value of usFctNo in T_SCH_SYST_INF */
#define C_SCH_CALL_SYST 			 2				/*!< CALL SCHEME SYSTEM : Value of usFctNo in T_SCH_SYST_INF */
#define C_SCH_PUTCRC_SYST 			 3				/*!< PUTCRC SCHEME SYSTEM : Value of usFctNo in T_SCH_SYST_INF */
#define C_SCH_COPY_SYST 			 4				/*!< COPY SCHEME SYSTEM : Value of usFctNo in T_SCH_SYST_INF */
#define C_SCH_DALLOC_SYST 			 5				/*!< DALLOC SCHEME SYSTEM : Value of usFctNo in T_SCH_SYST_INF */
/*! @brief This structure gives information about a secure scheme to load.	*/
typedef struct {
	int iFctNo;					/*!< System Fonction Number with error : 0 No Error */
	int iErrNo;					/*!< Error Number : 0 No error, If iFctNo is #C_SCH_BAD_CERTIF then iErrNo is the expected TeliumType Signature, otherwise Error number */
	int iRfu;					/*!< Reserved for future usage : 0 */
} T_SCH_SYST_INF;

/*! @brief This function is used for compatibility with old version CMP_SECURITY  <= 1.2, to Open/Initialise Security module
 *
 *  It is for compatibility with old version CMP_SECURITY <= 1.2
 *  @param   ptParamBooster : Boosters and schemes configuration
 *  @return None
 *
 *	@link DLLsecu_LOW Back to top @endlink
 **/
void SEC_open (T_SCH_OPEN * ptParamBooster);

/*! @brief This function is used to run schemes without IAPP communication
 *
 *  It loads, executes and wait the end of execution of a scheme.  
 *  @param[in] 		pt_schInit		: Parameters defining the scheme and the loading mode in a booster
 *  @param[out] 	pt_schInfo		: Information about the loaded scheme 
 *  @param[out] 	codeexit			: Returned code value by the scheme 
 *  @param[in] 		p0						: Scheme parameters 
 *  @param[in] 		p1						: Scheme parameters 
 *  @param[in] 		p2						: Scheme parameters 
 *  @param[in] 		p3						: Scheme parameters 
 *  @return OK (0) is successful, otherwise error
 *
 *	@link DLLsecu_LOW Back to top @endlink
 **/

int SEC_sch_init_end_gen (T_SCH_INIT * pt_schInit,
					 T_SCH_INF * pt_schInfo, int*codeexit,
					 int p0,int p1,int p2,int p3);


/*! @brief This function is used to run an asynchronous Scheme using IAPP communication.
 *
 *  It loads, executes a scheme (but does not wait for the end of execution of the scheme).
 *  The scheme will be ended by the function #SEC_sch_end_gen.
 *  @param[in] 		pt_schInit		: Parameters defining the scheme and the loading mode in a booster
 *  @param[out] 	pt_schInfo		: Information about the loaded scheme 
 *  @param[in] 		arg1					: Scheme parameters 
 *  @param[in] 		arg2					: Scheme parameters 
 *  @param[in] 		arg3					: Scheme parameters 
 *  @param[in] 		arg4					: Scheme parameters 
 *  @return OK (0) is successful, otherwise error
 *
 *	@link DLLsecu_LOW Back to top @endlink
 **/
int SEC_sch_init_gen (T_SCH_INIT * pt_schInit,
				  T_SCH_INF * pt_schInfo,
				  int arg1 , int arg2, int arg3 , int arg4);

/*! @brief This function is used to End and return the codexit of an asynchronous running Scheme
 *         (the scheme has been previously loaded by the function #SEC_sch_init_gen).
 *  @return      Exit code returned by the scheme
 *
 *	@link DLLsecu_LOW Back to top @endlink
 **/
int SEC_sch_end_gen (void);

/*! @brief This function is used to End an asynchronous running Scheme without waiting for the END event
 *         (the scheme has been previously loaded by the function #SEC_sch_init_gen).
 *  @return   None
 *
 *	@link DLLsecu_LOW Back to top @endlink
 **/
void SEC_sch_end_gen_NoWait (void);

/*! @brief This function is used to free the last loaded resident scheme.
 *
 *  This function is useful for compatibility with multi-application having no management of resident schemes.
 *  @param[in] 	pt_szBoosterName	: Value is a pointer to #IAPP_DEF_NAME ("IAPP") for the internal Booster or #IAPP_USB_NAME ("IAPP_PPR") for the external Booster.
 *  @return None
 *
 *	@link DLLsecu_LOW Back to top @endlink
 **/
void SEC_sch_free (char * pt_szBoosterName);

/*! @brief This function is used to get the last Error status for the last scheme execution.
 *
 *  @param[out] 	pt_schInfo		: Information about the last scheme to load 
 *  @param[out] 	pt_schSyst		: Information about the last Error if any 
 *                                    If iFctNo is #C_SCH_BAD_CERTIF then iErrNo is the expected TeliumType Signature
 *  @return None
 *
 *	@link DLLsecu_LOW Back to top @endlink
 **/
void SEC_sch_error_status (T_SCH_INF * pt_schInfo,
				  T_SCH_SYST_INF * pt_schSyst);

/*! @brief This function is used to get the version of the security schemes package 820365 .
 *
 *  @param[in] 		usAppliType		: 0 for the current application otherwise another application type value 
 *  @param[out] 	tab_szPackVers	: null terminated ASCII string for the version of the security schemes package 820365
 *  @return OK (0) is successful, otherwise error
 *
 *	@link DLLsecu_LOW Back to top @endlink
 **/
int SEC_sch_GetPackVersion (unsigned short usAppliType, char tab_szPackVers [C_LEN_STR_GETSCHVERS]);

/*! @brief This function is used to get the details of the embedded security schemes for an application .
 *
 *  @param[in] 		usAppliType		: 0 for the current application otherwise another application type value 
 *  @param[in] 		iMaxTabSch		: Max number of schemes to output for tab_szSchemeVers
 *  @param[out] 	ptout_iNbTabSch	: Number of schemes for tab_szSchemeVers 
 *  @param[out] 	tab_szSchemeVers: Array of null terminated ASCII string describing each scheme.
 *                                    The ASCII string format is: "_SCH_ :_Tx_:_VERS_ CRC1:_XXXX_ CRC2:_XXXX_"
 * with _SCH_ Scheme Name,
 *      _Tx_ T1 for Telium1 signature scheme or T2 for Telium2 signature scheme,
 *      _VERS_ Scheme version,
 *      _XXXX_ hexadecimal value for CRC1 (binary scheme CRC) or CRC2 (1rst signature scheme CRC)
 *  @return OK (0) is successful, otherwise error
 *
 *	@link DLLsecu_LOW Back to top @endlink
 **/
int SEC_sch_GetSchemesDetail (unsigned short usAppliType, int iMaxTabSch, int * ptout_iNbTabSch, char tab_szSchemeVers [] [C_LEN_STR_GETSCHVERS]);

#endif /* __SEC_INTERF_H__ */

/*! @} **/
