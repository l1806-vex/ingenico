//! \file
// \copyright  Ingenico 2013
// \brief This module implements Mifare SAM commands and the Mifare Key functions.

/** \addtogroup MifareSAM
   * @{
   *    \details This module implements commands to manage MIFARE SAM in AV1 mode or in AV2 mode.
   *
   *    \defgroup SAMErrors SAM Errors
   *
   *    \defgroup SAMContextManagement SAM context management functions
   *    @{
   *       \details Functions used to create or free a SAM context. These functions usually don't need
   *       to be used because \ref desfire_NewContextWithSAM, \ref ClessMFP_NewContextWithSAM or
   *       \ref ClessMFU_NewContextWithSAM create a SAM context and \ref desfire_FreeContext,
   *       \ref ClessMFP_FreeContext or \ref ClessMFU_FreeContext also free the SAM context.
   *    @}
   *    \defgroup SAMCommands SAM commands
   *    @{
   *       \details Commands for SAM management.
   *    @}
   *    \defgroup SAMCommandsDeprecated Deprecated SAM commands
   *    @{
   *       \details Deprecated Commands for the SAM.
   *    @}
   * @}
   * \addtogroup MifareKeyManagement
   * @{
   *    Functions to create or free keys to be used for cryptographic operations.
   * @}
 *
*/


#ifndef __MIFARESAM_H__
#define __MIFARESAM_H__

// Mifare SAM defines
#define MIFARE_SAM_CAPDU_HEADER_SIZE      5     //!< SAM command APDU header size [CLA][INS][P1][P2][Lc]
#define MIFARE_SAM_CAPDU_PAYLOAD_SIZE     255   //!< Maximum SAM command APDU payload size
#define MIFARE_SAM_MAX_CAPDU_SIZE         (MIFARE_SAM_CAPDU_HEADER_SIZE + MIFARE_SAM_CAPDU_PAYLOAD_SIZE) //!< Maximum SAM command APDU size [CLA][INS][P1][P2][Lc][0..255][Le]
#define MIFARE_SAM_RAPDU_TAIL_SIZE        2     //!< Maximum SAM response APDU tail size [SW1][SW2]
#define MIFARE_SAM_RAPDU_PAYLOAD_SIZE     256   //!< Maximum SAM response APDU payload size
#define MIFARE_SAM_MAX_RAPDU_SIZE         (MIFARE_SAM_RAPDU_PAYLOAD_SIZE + MIFARE_SAM_RAPDU_TAIL_SIZE) //!< Maximum SAM response APDU size [0..256][SW1][SW2]

//! \addtogroup SAMErrors
//! @{

#define MF_SAM_OK                           0    //!< Successful operation
#define MF_SAM_PARAMETER_ERROR              0x01 //!< Invalid value of the parameter(s)
#define MF_SAM_STATE_ERROR                  0x0C //!< The current state doesn't allow the command execution (ex: wrong SAM mode, authentication required...)
#define MF_SAM_RESPONSE_ERROR               0x0D //!< The response has an error (bad format, bad length...)
#define MF_SAM_DLL_NOT_LOADED             0x0100 //!< The MIFARE DLL is not loaded

//! @}

//! \addtogroup SAMContextManagement
//! @{

//! \brief Type allowing to identify SAM configuration mode
typedef enum
{
   MF_SAM_AV1, //!< SAM mode AV1
   MF_SAM_AV2  //!< SAM mode AV2
} T_MIFARE_SAM_MODE;

//! Context needed for SAM operations
struct S_MIFARE_SAM_CONTEXT;

//! Type associated to S_MIFARE_SAM_CONTEXT
typedef struct S_MIFARE_SAM_CONTEXT T_MIFARE_SAM_CONTEXT;

//! @}

//! \addtogroup SAMCommands
//! @{

//! Key Entry for MIFARE SAM key management in AV1 mode
typedef struct S_MIFARE_KEY_ENTRY
{
   unsigned char tKeyA[16];   //!< Key A value
   unsigned char tKeyB[16];   //!< Key B value
   unsigned char tKeyC[16];   //!< Key C value
   unsigned char dfAid[3];    //!< Corresponding Desfire AID
   unsigned char dfKeyNr;     //!< Corresponding Desfire key number (of Desfire AID)
   unsigned char CEK_No;      //!< Key number of Change Entry Key
   unsigned char CEK_V;       //!< Key version of Change Entry Key
   unsigned char KUC;         //!< Key number of Key Usage Counter
   unsigned char SET[2];      //!< Key settings
   unsigned char VerA;        //!< Key A version
   unsigned char VerB;        //!< Key B version
   unsigned char VerC;        //!< Key C version
} T_MIFARE_KEY_ENTRY;


//! Key Entry for MIFARE SAM key management in AV2 mode
typedef struct S_MIFARE_KEY_ENTRY_AV2
{
   unsigned char tKeyA[16];   //!< Key A value
   unsigned char tKeyB[16];   //!< Key B value
   unsigned char tKeyC[16];   //!< Key C value
   unsigned char dfAid[3];    //!< Corresponding Desfire AID
   unsigned char dfKeyNr;     //!< Corresponding Desfire key number (of Desfire AID)
   unsigned char CEK_No;      //!< Key number of Change Entry Key
   unsigned char CEK_V;       //!< Key version of Change Entry Key
   unsigned char KUC;         //!< Reference number of Key Usage Counter
   unsigned char SET[2];      //!< Key settings
   unsigned char VerA;        //!< Key A version
   unsigned char VerB;        //!< Key B version
   unsigned char VerC;        //!< Key C version
   unsigned char ExtSET;      //!< Extended Key Settings
} T_MIFARE_KEY_ENTRY_AV2;

//! @}


//! \addtogroup MifareKeyManagement
//! @{

//! \brief Structure containing various information related to the key, needed for cryptographic operations.
//! \details For example : key type; key value, des, aes or cmac contexts; generated subkeys etc.
struct S_MIFARE_KEY;

//! \brief Type associated to private structure S_MIFARE_KEY.
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion,
//! \ref desfire_NewContext, \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
typedef struct S_MIFARE_KEY T_MIFARE_KEY;

//! Encrypt/Decrypt block chaining mode
typedef enum
{
   MF_CHAINING_ECB, //!< ECB chaining mode.
   MF_CHAINING_CBC, //!< CBC chaining mode.
   MF_CHAINING_DESFIRE_NATIVE //!< MIFARE DESFire Native chaining mode
} T_MIFARE_CHAINING_MODE;

//! @}

// Mifare SAM functions

//! \addtogroup SAMContextManagement
//! @{

//! \brief Detect SAM presence and power it on.
//! \details This function detect and return the descriptor to the first SAM
//! detected. If several SAM are present, the first one will be used and others
//! will be ignored. If a specific SAM has to be used, it will be necessary to
//! power it on without the mifareSAM_AutoDetectSAM function.
//! \remarks Think about powering off the SAM when it is not used anymore.
//! \return
//! - Pointer to descriptor of powered SAM
//! - NULL if SAM not found or if power on failed
#ifdef __FRAMEWORK_TELIUM_PLUS__ 
extern Telium_File_t* mifareSAM_AutoDetectSAM(void);
#else
extern FILE* mifareSAM_AutoDetectSAM(void);
#endif

//! \brief Create a SAM context
//! \param[in] hSAM File descriptor of the SAM to use
//! \param[in] samMode SAM mode (see \ref T_MIFARE_SAM_MODE)
//! - \ref MF_SAM_AV1
//! - \ref MF_SAM_AV2
//! \return Pointer to the new SAM context. NULL if an error occurred.
//! \sa \ref mifareSAM_FreeContext
#ifdef __FRAMEWORK_TELIUM_PLUS__ 
extern T_MIFARE_SAM_CONTEXT* mifareSAM_NewContext(Telium_File_t* hSAM, T_MIFARE_SAM_MODE samMode);
#else
extern T_MIFARE_SAM_CONTEXT* mifareSAM_NewContext(FILE* hSAM, T_MIFARE_SAM_MODE samMode);
#endif

//! \brief Clear a SAM context
//! \param[in,out] pSAMCtx Pointer to the SAM context to be cleared
//! \sa \ref mifareSAM_NewContext
extern void mifareSAM_FreeContext(T_MIFARE_SAM_CONTEXT* pSAMCtx);

//! @}



//! \addtogroup SAMCommands
//! @{

/**
 * Put the SAM in sleep mode to lower power consumption.
 * @param[in,out] pSAMCtx Pointer to the SAM context.
 * @return
 *    - \ref MF_SAM_OK for success,
 *    - MF_SAM_XXX_ERROR or SAM SW1-SW2 if failed.
 */
extern int mifareSAM_Sleep(T_MIFARE_SAM_CONTEXT* pSAMCtx);

/**
 * Return SAM manufacturing data.
 * @param[in,out] pSAMCtx Pointer to the SAM context.
 * @param[in,out] pulLength Pointer to manage the length of \a pData :
 *    - input : max size of \a pData,
 *    - output : number of bytes written in \a pData.
 * @param[out] pData Pointer to a buffer which will receive the manufacturing data.
 * @return
 *    - \ref MF_SAM_OK for success,
 *    - MF_SAM_XXX_ERROR or SAM SW1-SW2 if failed.
 */
extern int mifareSAM_GetVersion(T_MIFARE_SAM_CONTEXT* pSAMCtx, unsigned long* pulLength, void* pData);

/**
 * Read the content of a key entry.
 * @param[in,out] pSAMCtx Pointer to the SAM context.
 * @param[in] ucKeyNo key entry number to read.
 * @param[in,out] pulLength Pointer to manage the length of \a pData :
 *    - input : max size of \a pData,
 *    - output : number of bytes written in \a pData.
 * @param[out] pData pointer to a buffer which will receive the key entry data.
 * See NXP SAM datasheet for description of the returned data.
 * @return
 *    - \ref MF_SAM_OK for success,
 *    - MF_SAM_XXX_ERROR or SAM SW1-SW2 if failed.
 */
int mifareSAM_GetKeyEntry(T_MIFARE_SAM_CONTEXT* pSAMCtx, unsigned char ucKeyNo, unsigned long* pulLength, void *pData);

/**
 * Make a mutual authentication between the Host and the SAM.
 * @param[in,out] pSAMCtx Pointer to the SAM context.
 * @param[in] pKey Pointer to the Host \ref T_MIFARE_KEY key.
 * @param[in] ucMode
 *   - in AV1 mode, defines the AV1 Authentication Mode.
 *      <table><tr><th>Bits Value</th><th>Description</th></tr>
 *      <tr><td>Bit 7 - 5</td><td>0 : RFU</td></tr>
 *      <tr><td>Bit 4</td><td>
 *      - 0 : use AV1 compatibility mode key diversification methods
 *      - 1 : use AV2 compatibility mode key diversification methods (make bit 3 ignored)</td></tr>
 *      <tr><td>Bit 3</td><td>DES or 2K3DES key
 *      - 0 : diversify using 2 encryption rounds
 *      - 1 : diversify using 1 encryption rounds
 *
 *      3K3DES and AES key
 *      - 0 : RFU </td></tr>
 *      <tr><td>Bit 2</td><td>
 *      - 0 : generate session key
 *      - 1 : use secret key for crypto </td></tr>
 *      <tr><td>Bit 1</td><td> 0 : Not used (internally set to 0)</td></tr>
 *      <tr><td>Bit 0</td><td> 0 : Not used (internally set according to diversififcation input)</td></tr>
 *      </table>
 *   - in AV2 mode, defines the secure messaging protection mode to use for Host-SAM communication
 *      <table><tr><th>Value</th><th>Description</th></tr>
 *      <tr><td>0</td><td>Plain</td></tr>
 *      <tr><td>1</td><td>MAC protection</td></tr>
 *      <tr><td>2</td><td>Full protection (MAC + Cipher)</td></tr>
 *      </table>
 * @param[in] ucSAMKeyNo SAM key number to authenticate with.
 * @param[in] ucSAMKeyVersion SAM key version.
 * @param[in] pDivInp In AV1 mode, pointer to diversification input data, or NULL if no diversifcation. Not used in AV2 mode.
 * @param[in] iDivInpLen In AV1 mode, length in bytes of the diversification data, or 0 if no diversification. Not used in AV2 mode.
 * @return \ref MF_SAM_OK when authentication is successful, other values when it fails.
 */
extern int mifareSAM_AuthenticateHost(T_MIFARE_SAM_CONTEXT* pSAMCtx,
      T_MIFARE_KEY* pKey, unsigned char ucMode, unsigned char ucSAMKeyNo,
      unsigned char ucSAMKeyVersion, const void* pDivInp, int iDivInpLen);


/**
 * Update a SAM key entry for a SAM in AV1 mode or in AV2 mode.
 * @note In AV2mode, changing a key entry using an Off-line change key is not supported.
 * @param[in,out] pSAMCtx Pointer to the SAM context.
 * @param[in] ucKeyNo key Entry number to change.
 * @param[in] ucProgMask Programming mask options:
 *      <table><tr><th>Bits</th><th>Option (1: enabled / 0: disabled) </th></tr>
 *      <tr><td>Bit 7 </td><td> Update key A value</td></tr>
 *      <tr><td>Bit 6 </td><td> Update key B value</td></tr>
 *      <tr><td>Bit 5 </td><td> Update key C value</td></tr>
 *      <tr><td>Bit 4 </td><td> Update DF AID and DF Key Number</td></tr>
 *      <tr><td>Bit 3 </td><td> Update CEK number and version</td></tr>
 *      <tr><td>Bit 2 </td><td> Update KUC Number</td></tr>
 *      <tr><td>Bit 1 </td><td> Update SET</td></tr>
 *      <tr><td>Bit 0 </td><td> For TDEA keys, keys versions are defined by the bytes VerA, VerB and VerC </td></tr>
 *      </table>
 * @param[in] ulSize Size of the structure given in \a pKeyEntry.
 * @param[in] pKeyEntry Pointer to \ref T_MIFARE_KEY_ENTRY for AV1 mode or to \ref T_MIFARE_KEY_ENTRY_AV2 for AV2 mode.
 * @return
 *    - \ref MF_SAM_OK for success,
 *    - MF_SAM_XXX_ERROR or SAM SW1-SW2 if failed.
 */
extern int mifareSAM_ChangeKeyEntryEx(T_MIFARE_SAM_CONTEXT* pSAMCtx, unsigned char ucKeyNo,
           unsigned char ucProgMask, unsigned long ulSize,  const void* pKeyEntry);

//! @}

//Key management fonctions

//! \addtogroup MifareKeyManagement
//! @{

//! \brief Generate a DES key either for DESFire Native authentication or standard
//! authentication.
//! \details The key version is set to 0 (see \ref mifare_KeySetVersion).
//! \param[in] tucValue Value of the key (array of 8 bytes).
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Return a pointer to the new key.
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion,
//! \ref desfire_NewContext, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_NewDesKey(unsigned char tucValue[8],
      T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Generate a DES key either for DESFire Native authentication or standard
//! authentication.
//! \details The parity bits (used to set a key version) are kept unchanged.
//! \param[in] tucValue Value of the key (array of 8 bytes).
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Return a pointer to the new key.
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion,
//! \ref desfire_NewContext, \ref mifare_NewDesKey, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_NewDesKeyWithVersion(unsigned char tucValue[8],
      T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Generate a 2K3DES key either for DESFire Native authentication or standard
//! authentication.
//! \details The key version is set to 0 (see \ref mifare_KeySetVersion).
//! \param[in] tucValue Value of the key (array of 16 bytes).
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Return a pointer to the new key.
//! \sa \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey, \ref mifare_New3k3desKeyWithVersion,
//! \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion, \ref desfire_NewContext,
//! \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_New3desKey(unsigned char tucValue[16],
      T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Generate a 2K3DES key either for DESFire Native authentication or standard
//! authentication.
//! \details The parity bits (used to set a key version) are kept unchanged.
//! \param[in] tucValue Value of the key (array of 16 bytes).
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Return a pointer to the new key.
//! \sa \ref mifare_New3desKey, \ref mifare_New3k3desKey, \ref mifare_New3k3desKeyWithVersion,
//! \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion, \ref desfire_NewContext,
//! \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_New3desKeyWithVersion(unsigned char tucValue[16],
      T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Generate a 3K3DES key for DESFire standard authentication
//! (see \ref desfire_Authenticate, or \ref desfire_AuthenticateIso).
//! \details The key version is set to 0 (see \ref mifare_KeySetVersion).<br>
//! <b>This key is not compliant with DESFire EV0</b>.
//! \param[in] tucValue Value of the key (array of 24 bytes).
//! or desfire_AuthenticateIso).
//! \return Return a pointer to the new key.
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKeyWithVersion,
//! \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion, \ref desfire_NewContext,
//! \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_New3k3desKey(unsigned char tucValue[24]);

//! \brief Generate a 3K3DES key for DESFire standard authentication
//! (see \ref desfire_Authenticate, or \ref desfire_AuthenticateIso).
//! \details The parity bits (used to set a key version) are kept unchanged.<br>
//! <b>This key is not compliant with DESFire EV0</b>.
//! \param[in] tucValue Value of the key (array of 24 bytes).
//! or desfire_AuthenticateIso).
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion, \ref desfire_NewContext,
//! \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_New3k3desKeyWithVersion(unsigned char tucValue[24]);

//! \brief Generate a AES 128 bits key for DESFire standard authentication
//! (see \ref desfire_Authenticate, or \ref desfire_AuthenticateAes).
//! \details The key version is set to 0 (see \ref mifare_KeySetVersion).<br>
//! <b>This key is not compliant with DESFire EV0</b>.
//! \param[in] tucValue Value of the key (array of 16 bytes).
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKeyWithVersion, \ref desfire_NewContext,
//! \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_NewAesKey(unsigned char tucValue[16]);

//! \brief Generate a AES 128 bits key for DESFire standard authentication
//! (see \ref desfire_Authenticate, or \ref desfire_AuthenticateAes).
//! \details <b>This key is not compliant with DESFire EV0</b>.
//! \param[in] tucValue Value of the key (array of 16 bytes).
//! \param[in] ucVersion Version of the key to create (1 byte).
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey, \ref desfire_NewContext,
//! \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_NewAesKeyWithVersion(const unsigned char tucValue[16],
      unsigned char ucVersion);

//! \brief Free a key.
//! \details The key and all data it contains will be deleted.
//! \param[in] pKey Pointer to the key to delete.
//! \remarks If the value of pointer is NULL, no operations will be performed.
//! \remarks After having deleted a key, it can be advised to set the pointer
//! value to NULL.
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion,
//! \ref desfire_NewContext, \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion
extern void mifare_FreeKey(T_MIFARE_KEY *pKey);

//! \brief Create a diversified DES key. Compliant with MIFARE SAM AV1
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] tucDivInp Diversification input
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
extern T_MIFARE_KEY * mifare_DiversifyKeyDES(unsigned char tucKeyValue[8],
      unsigned char tucDivInp[8], T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Create a diversified 2k3DES key. Compliant with MIFARE SAM AV1
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] tucDivInp Diversification input
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
//! \sa \ref mifare_DiversifyKey2K3DES_AV2
extern T_MIFARE_KEY * mifare_DiversifyKey2K3DES(unsigned char tucKeyValue[16],
      unsigned char tucDivInp[8], T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Create a diversified 2k3DES key. Compliant with MIFARE SAM AV2
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] tucDivInp Diversification input (1 to 15 bytes)
//! \param[in] iDivInpLen Diversification input length
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
//! \sa \ref mifare_DiversifyKey2K3DES
extern T_MIFARE_KEY * mifare_DiversifyKey2K3DES_AV2(
      unsigned char tucKeyValue[16], unsigned char tucDivInp[15],
      int iDivInpLen, T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Create a diversified 3k3DES key. Compliant with MIFARE SAM AV1
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] tucDivInp Diversification input
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
//! \sa \ref mifare_DiversifyKey3K3DES_AV2
extern T_MIFARE_KEY * mifare_DiversifyKey3K3DES(unsigned char tucKeyValue[24],
      unsigned char tucDivInp[8]);

//! \brief Create a diversified 3k3DES key. Compliant with MIFARE SAM AV2
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] tucDivInp Diversification input (1 to 15 bytes)
//! \param[in] iDivInpLen Diversification input length
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
//! \sa \ref mifare_DiversifyKey3K3DES
extern T_MIFARE_KEY * mifare_DiversifyKey3K3DES_AV2(
      unsigned char tucKeyValue[24], unsigned char tucDivInp[15],
      int iDivInpLen);

//! \brief Create a diversified AES key. Compliant with MIFARE SAM AV1
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] ucVersion Version of the key to diversify.
//! \param[in] tucDivInp Diversification input
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
//! \sa \ref mifare_DiversifyKeyAES128
extern T_MIFARE_KEY * mifare_DiversifyKeyAES128(unsigned char tucKeyValue[16],
      unsigned char ucVersion, unsigned char tucDivInp[16]);

//! \brief Create a diversified AES key. Compliant with MIFARE SAM AV2
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] ucVersion Version of the key to diversify.
//! \param[in] tucDivInp Diversification input (1 to 31 bytes)
//! \param[in] iDivInpLen Diversification input length
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
//! \sa \ref mifare_DiversifyKeyAES128_AV2
extern T_MIFARE_KEY * mifare_DiversifyKeyAES128_AV2(
      unsigned char tucKeyValue[16], unsigned char ucVersion,
      unsigned char tucDivInp[31], int iDivInpLen);

//! \brief Retrieve the version of a key.
//! \details  No command is sent to the PICC.<br>
//! For DES keys, the version is computed from the parity bits of the first 8 bytes of the key.
//! \param[in] pKey Pointer to a key.
//! \return Version of the key.
//! \sa \ref mifare_KeySetVersion, desfire_GetKeyVersion
extern unsigned char mifare_KeyGetVersion(T_MIFARE_KEY *pKey);

//! \brief Update the version of a key.
//! \details Only the version of the key passed in parameter is changed.
//! <b> No changes are done on the PICC</b>.
//! <br>For DES keys, the version is stored in the parity bits of the first 8 bytes of the key, the other bytes are not changed.
//! \param[in] pKey Pointer to a key.
//! \param[in] ucVersion Version to add.
//! \sa \ref mifare_KeyGetVersion, desfire_GetKeyVersion
extern void mifare_KeySetVersion(T_MIFARE_KEY *pKey, unsigned char ucVersion);
//! @}


#endif // __MIFARE_H__
