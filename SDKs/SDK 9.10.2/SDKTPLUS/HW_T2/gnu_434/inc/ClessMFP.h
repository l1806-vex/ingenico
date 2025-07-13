//! \file
// \copyright  Ingenico 2012
// \brief This module implements MIFARE Plus commands.

/** \addtogroup ClessMFP
   * @{
     *   \details This module implements MIFARE Plus commands to manage MIFARE Plus cards from
     *   Security Level 0 to Security Level 3.
     *   The cryptographic operations can be done either on the Thunder, either on a MIFARE SAM in AV2 mode.
     *
     *   \par How to use this library :
     *   -# <b>The PICC has to be detected and activated.</b>
     *   -# <b>The SAM has to be detected and powered if it needs to be used (\ref mifareSAM_AutoDetectSAM).</b>
     *   -# Create a new MIFARE Plus context (\ref ClessMFP_NewContext, \ref ClessMFP_NewContextWithSAM).
     *   <b>This is at this step that the cryptographic mode (use a SAM or not) is determined.</b>
     *   -# Use MIFARE Pus commands to interact with the PICC using commands provided by
     *   this library. For example : authentication, read/write a block (See \ref ClessMFPCommands).
     *   -# Free the MIFARE Plus context (\ref ClessMFP_FreeContext).
     *   -# Power off the SAM if it has been powered.
     *   -# Power off the Cless field.
     *
     *   \defgroup ClessMFPErrors MIFARE Plus Errors
     *   \defgroup ClessMFPCommands MIFARE Plus Commands
     *   @{
     *      The MIFARE Plus cryptographic operations can be done by Telium
     *      or by a SAM. That's why for context creation and card authentication
     *      two versions of the function exist.
     *
     *      A Mifare Plus card can be detected/activated with the MIFARE Classic protocol or the ISO 14443-4 (EMV) protocol.
     *      According to the used protocol, some MIFARE Plus commands are available or not.
     *
     *      To use the MIFARE Classic protocol, the application should:
     *        - use the ClessMifare driver by calling ClessMifare_OpenDriver(),
     *        - detect the card with the \a ClessMifare_DetectCardxxx() functions,
     *        - activate the card with \a ClessMifare_ActiveCard().
     *
     *      To use the ISO 14443-4 protocol, the application should:
     *        - use the ClessEmv driver by calling \a ClessEmv_OpenDriver(),
     *        - detect the card with the \a ClessEmv_DetectCardxxx() functions,
     *        - activate the card with \a ClessEmv_ActiveCard().
     *
     *      The following table indicates which protocol is supported for each function :
     *          <table><tr><th>Function              </th><th>MIFARE Classic protocol</th><th>ISO 14443-4 protocol</th></tr>
     *          <tr><td>\ref ClessMFP_SL0WritePerso                  </td><td>  No        </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL0CommitPerso                 </td><td>  No        </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL1AuthenticateAES             </td><td>  Yes       </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL1AuthenticateAESWithSAM      </td><td>  Yes       </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL2AuthenticateAES             </td><td>  Yes       </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL2AuthenticateAESWithSAM      </td><td>  Yes       </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL12AuthenticateClassic        </td><td>  Yes       </td><td> No  </td></tr>
     *          <tr><td>\ref ClessMFP_SL12AuthenticateClassicWithSAM </td><td>  Yes       </td><td> No  </td></tr>
     *          <tr><td>\ref ClessMFP_SL12ReadBlock                  </td><td>  Yes       </td><td> No  </td></tr>
     *          <tr><td>\ref ClessMFP_SL12WriteBlock                 </td><td>  Yes       </td><td> No  </td></tr>
     *          <tr><td>\ref ClessMFP_SL12ValueOperation             </td><td>  Yes       </td><td> No  </td></tr>
     *          <tr><td>\ref ClessMFP_SL2ReadMultiBlock              </td><td>  Yes       </td><td> No  </td></tr>
     *          <tr><td>\ref ClessMFP_SL2WriteMultiBlock             </td><td>  Yes       </td><td> No  </td></tr>
     *          <tr><td>\ref ClessMFP_SL3Authenticate                </td><td>  No        </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL3AuthenticateWithSAM         </td><td>  No        </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL3ResetAuthentication         </td><td>  No        </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL3Read                        </td><td>  No        </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL3Write                       </td><td>  No        </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL3ValueOperation              </td><td>  No        </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL3ProximityCheck              </td><td>  No        </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL3ProximityCheckWithSAM       </td><td>  No        </td><td> Yes </td></tr>
     *          <tr><td>\ref ClessMFP_SL3ChangeKeyWithSAM            </td><td>  No        </td><td> Yes </td></tr>
     *          </table>
     *
     *   @}
   * @}
 * \example MFPSample.c
*/

#include "MifareSAM.h"

#ifndef CLESSMFP_H
#define CLESSMFP_H

//! \addtogroup ClessMFPErrors
//! @{
// MFP Errors
#define MFP_OK                           0    //!< Successful operation
// API Error
#define MFP_PARAMETER_ERROR              0x01 //!< Value of the parameter(s) invalid
#define MFP_MAC_VERIFICATION_ERROR       0x02 //!< Verification of the PICC MAC failed
#define MFP_AUTHENTICATION_ERROR         0x03 //!< The authentication failed
#define MFP_COMMUNICATION_ERROR          0x04 //!< Communication error with PICC
#define MFP_COMMUNICATION_TIMEOUT_ERROR  0x05 //!< Communication error with PICC
#define MFP_INVALID_VALUE                0x06 //!< The value block has an error
#define MFP_VALUE_ADD_WARNING            0x07 //!< The address byte of value block doesn't match the current block number
#define MFP_INTERNAL_ERROR               0x08 //!< The library has a processing error
#define MFP_CRYPTO_ERROR                 0x09 //!< The library has a crypto processing error
#define MFP_SAM_ERROR                    0x0A //!< SAM has an error
#define MFP_PC_TIME_ERROR                0x0B //!< The Proximity Check time verification failed
#define MFP_STATE_ERROR                  0x0C //!< The current state doesn't allow the command execution (ex: MIFARE Classic command in ISO 14443-4, wrong Security Level...)
#define MFP_RESPONSE_ERROR               0x0D //!< The response has an error (bad format, bad length...)
#define MFP_DLL_NOT_LOADED               0xFF //!< The MIFARE DLL is not loaded

// PICC Error
#define MFP_SC_ERROR                     0x100 //!< PICC error codes
#define MFP_SC_AUTHENTICATION_ERROR      (MFP_SC_ERROR + 0x06) //!< PICC error : access conditions not fulfilled
#define MFP_SC_COMMAND_OVERFLOW          (MFP_SC_ERROR + 0x07) //!< PICC error : too many read or write commands
#define MFP_SC_INVALID_MAC               (MFP_SC_ERROR + 0x08) //!< PICC error : invalid MAC in command or response
#define MFP_SC_INVALID_BLOCK_NB          (MFP_SC_ERROR + 0x09) //!< PICC error : block number is not valid
#define MFP_SC_NOT_EXISTING_BLOCK_NB     (MFP_SC_ERROR + 0x0A) //!< PICC error : invalid block number, not existing block number
#define MFP_SC_BAD_CONDITIONS            (MFP_SC_ERROR + 0x0B) //!< PICC error : command not available at the current card state
#define MFP_SC_LENGTH_ERROR              (MFP_SC_ERROR + 0x0C) //!< PICC error : length error
#define MFP_SC_GENERAL_ERROR             (MFP_SC_ERROR + 0x0F) //!< PICC error : failure in the operation

#define MFP_NAK                           0x200 //!< The PICC NAK the command (MIFARE Classic compatibility mode)

//! @}

//! \addtogroup ClessMFPCommands
//! @{
// MIFARE Plus Command Code

#define MFP_READ	                          0x30 //!< Reading encrypted, no MAC on response, MAC on command
#define MFP_READ_MAC                        0x31 //!< Reading encrypted, MAC on response, MAC on command
#define MFP_READ_PLAIN                      0x32 //!< Reading in plain, no MAC on response, MAC on command
#define MFP_READ_PLAIN_MAC                  0x33 //!< Reading in plain, MAC on response, MAC on command
#define MFP_READ_UNMAC                      0x34 //!< Reading encrypted, no MAC on response, no MAC on command
#define MFP_READ_UNMAC_MAC_RESPONSE         0x35 //!< Reading encrypted, MAC on response, no MAC on command
#define MFP_READ_PLAIN_UNMAC                0x36 //!< Reading in plain, no MAC on response, no MAC on command
#define MFP_READ_PLAIN_UNMAC_MAC_RESPONSE   0x37 //!< Reading in plain, MAC on response, no MAC on command

#define MFP_WRITE                           0xA0 //!< Writing encrypted, no MAC on response, MAC on command
#define MFP_WRITE_MAC                       0xA1 //!< Writing encrypted, MAC on response, MAC on command
#define MFP_WRITE_PLAIN                     0xA2 //!< Writing in plain, no MAC on response, MAC on command
#define MFP_WRITE_PLAIN_MAC                 0xA3 //!< Writing in plain, MAC on response, MAC on command

#define MFP_INCREMENT                       0xB0 //!< Incrementing a value encrypted, no MAC on response, MAC on command
#define MFP_INCREMENT_MAC                   0xB1 //!< Incrementing a value encrypted, MAC on response, MAC on command
#define MFP_DECREMENT                       0xB2 //!< Decrementing a value encrypted, no MAC on response, MAC on command
#define MFP_DECREMENT_MAC                   0xB3 //!< Decrementing a value encrypted, MAC on response, MAC on command
#define MFP_TRANSFER                        0xB4 //!< Transferring a value, no MAC on response, MAC on command
#define MFP_TRANSFER_MAC                    0xB5 //!< Transferring a value, MAC on response, MAC on command
#define MFP_INC_TRANSFER                    0xB6 //!< Incrementing and transferring a value encrypted, no MAC on response, MAC on command
#define MFP_INC_TRANSFER_MAC                0xB7 //!< Incrementing and transferring a value encrypted, MAC on response, MAC on command
#define MFP_DEC_TRANSFER                    0xB8 //!< Decrementing and transferring a value encrypted, no MAC on response, MAC on command
#define MFP_DEC_TRANSFER_MAC                0xB9 //!< Decrementing and transferring a value encrypted, MAC on response, MAC on command
#define MFP_RESTORE                         0xC2 //!< Restoring a value, no MAC on response, MAC on command
#define MFP_RESTORE_MAC                     0xC3 //!< Restoring a value, MAC on response, MAC on command

#define MFP_AUTH_F                          0x00 //!< First Authentication mode
#define MFP_AUTH_N                          0x01 //!< Following Authentication mode


// MIFARE Classic define (compatibility mode when in SL1 or SL2)
#define MFP_KEY_A                            0x0A //!< MIFARE Classic key type A
#define MFP_KEY_B                            0x0B //!< MIFARE Classic key type B

#define MFP_SL12_READ                        0x30 //!< MIAFRE Classic Read Command (only in Security Level 1 or 2)
#define MFP_SL12_WRITE                       0xA0 //!< MIAFRE Classic Write Command (only in Security Level 1 or 2)
#define MFP_SL12_INCREMENT                   0xC1 //!< MIAFRE Classic Increment Command (only in Security Level 1 or 2)
#define MFP_SL12_DECREMENT                   0xC0 //!< MIAFRE Classic Decrement Command (only in Security Level 1 or 2)
#define MFP_SL12_RESTORE                     0xC2 //!< MIAFRE Classic Restore Command (only in Security Level 1 or 2)
#define MFP_SL12_TRANSFER                    0xB0 //!< MIAFRE Classic Transfer Command (only in Security Level 1 or 2)

//! \struct S_MFP_CONTEXT
//! \brief Context needed for MIFARE Plus commands processing.
struct S_MFP_CONTEXT;

//! \brief Type associated to the MIFARE Plus context.
typedef struct S_MFP_CONTEXT T_MFP_CONTEXT;


/**
 * Create a MIFARE Plus context.
 * A contactless driver (EMV or Mifare) should be opened before calling this function.
 * @return Pointer to the new MFP context. NULL if an error occurred.
 */
T_MFP_CONTEXT* ClessMFP_NewContext(void);

/**
 * Create a MIFARE Plus context using a SAM AV2 for cryptographic operations.
 * A contactless driver (EMV or Mifare) should be opened before calling this function.
 * @param[in] hSAM File descriptor of the SAM AV2.
 * @return Return a pointer to the new MFP context. NULL if an error occurred.
 */
#ifdef __FRAMEWORK_TELIUM_PLUS__
T_MFP_CONTEXT* ClessMFP_NewContextWithSAM(Telium_File_t* hSAM);
#else
T_MFP_CONTEXT* ClessMFP_NewContextWithSAM(FILE* hSAM);
#endif

/**
 * Free a MIFARE Plus context.
 * The context and all data it contains will be deleted.
 * @param[in,out] pContext Pointer to the MFP context to delete. If NULL, nothing is done.
 * @remarks After having deleted a context, it can be advised to set the pointer value to NULL.
 * @sa @ref ClessMFP_NewContext.
 */
void ClessMFP_FreeContext(T_MFP_CONTEXT* pContext);

/**
 * Get the SAM context of a MIFARE Plus context.
 * @param[in] pContext Pointer to the T_MFP_CONTEXT (see \ref ClessMFP_NewContextWithSAM).
 * @return Return a pointer to \ref T_MIFARE_SAM_CONTEXT context. NULL if an error occurred.
 */
T_MIFARE_SAM_CONTEXT* ClessMFP_GetSAMContext(T_MFP_CONTEXT* pContext);

/**
 * Write data or keys in plain. Only available in Security Level 0 (personalization).
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] usBNr Block number or key address where to write \a pData.
 * @param[in] pData 16 bytes of plain data to write.
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL0WritePerso(T_MFP_CONTEXT* pContext,  unsigned short usBNr, const void* pData);

/**
 * Finalize the personalization and switch the card to Security Level 1 for "L1 card"
 * or to Security Level 3 for "L3 card". Only available in Security Level 0.
 * @param[in,out] pContext Pointer to the MFP context.
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL0CommitPerso(T_MFP_CONTEXT* pContext);

/**
 * Make a MIFARE Plus AES Authentication between PCD and PICC when in SL1.
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] usKeyNb Key number of the AES key used for the authentication.
 * @param[in] ucMode @ref MFP_AUTH_F or @ref MFP_AUTH_N.
 * @param[in] pKey Value of the key (16 bytes).
 * @return @ref ClessMFPErrors.
 * @note When using SL1 Card Authentication Key, \a ucMode shall be MFP_AUTH_N
 */
int ClessMFP_SL1AuthenticateAES(T_MFP_CONTEXT* pContext, unsigned short usKeyNb, unsigned char ucMode, const void* pKey);

/**
 * Make a MIFARE Plus AES Authentication between PCD and PICC using the SAM when in SL1.
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] usKeyNb Key number of the PICC key used for the authentication.
 * @param[in] ucMode \ref MFP_AUTH_F or \ref MFP_AUTH_N
 * @param[in] ucSAMKeyNb Key number of the SAM key used for the authentication.
 * @param[in] ucSAMKeyVersion Key version of the SAM key used.
 * @param[in] iDivInpLen Length in bytes of the \a pDivInp data. 0 if no diversification.
 * @param[in] pDivInp Pointer to diversification data for PICC key. NULL if no diversification.
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL1AuthenticateAESWithSAM(T_MFP_CONTEXT* pContext, unsigned short usKeyNb, unsigned char ucMode,
               unsigned char ucSAMKeyNb, unsigned char ucSAMKeyVersion, int iDivInpLen, const void* pDivInp);


/**
 * Make a MIFARE Plus AES Authentication between PCD and PICC when in SL2.
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] usKeyNb Key number of the AES key used for the authentication.
 * @param[in] ucMode @ref MFP_AUTH_F or @ref MFP_AUTH_N.
 * @param[in] pKey Value of the key (16 bytes).
 * @return @ref ClessMFPErrors.
 */int ClessMFP_SL2AuthenticateAES(T_MFP_CONTEXT* pContext, unsigned short usKeyNb,  unsigned char ucMode, const void* pKey);

 /**
  * Make a MIFARE Plus AES Authentication between PCD and PICC using the SAM when in SL2.
  * @param[in,out] pContext Pointer to the MFP context.
  * @param[in] usKeyNb Key number of the PICC key used for the authentication.
  * @param[in] ucMode \ref MFP_AUTH_F or \ref MFP_AUTH_N
  * @param[in] ucSAMKeyNb Key number of the SAM key used for the authentication (should be a AES PICC key).
  * @param[in] ucSAMKeyVersion Key version of the SAM key used.
  * @param[in] iDivInpLen Length in bytes of the \a pDivInp data. 0 if no diversification.
  * @param[in] pDivInp Pointer to diversification data for PICC key. NULL if no diversification.
  * @return @ref ClessMFPErrors.
  */
 int ClessMFP_SL2AuthenticateAESWithSAM(T_MFP_CONTEXT* pContext, unsigned short usKeyNb, unsigned char ucMode,
                unsigned char ucSAMKeyNb, unsigned char ucSAMKeyVersion, int iDivInpLen, const void* pDivInp);

/**
 * Make a MIFARE Classic authentication between PCD and PICC.
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] ucKeyType The type of the key: \ref MFP_KEY_A or \ref MFP_KEY_B.
 * @param[in] ucSector The sector number to authenticate.
 * @param[in] pKey Value of the MIFARE key (6 bytes).
 * @return @ref ClessMFPErrors.
 */
 int ClessMFP_SL12AuthenticateClassic(T_MFP_CONTEXT* pContext, unsigned char ucKeyType, unsigned char ucSector,
                const void* pKey);

 /**
  * Make a MIFARE Classic authentication between PCD and PICC using the SAM.
  * @param[in,out] pContext Pointer to the MFP context.
  * @param[in] ucKeyType The type of the key: \ref MFP_KEY_A or \ref MFP_KEY_B
  * @param[in] ucSector The sector number to authenticate.
  * @param[in] ucSAMKeyNb Key number of the SAM key used for the authentication (should be a MIFARE PICC key)..
  * @param[in] ucSAMKeyVersion Key version of the SAM key used.
  * @param[in] pDiv Pointer to the diversification block number (1 byte) or NULL if no diversification.
  * @return @ref ClessMFPErrors.
  */
 int ClessMFP_SL12AuthenticateClassicWithSAM(T_MFP_CONTEXT* pContext, unsigned char ucKeyType, unsigned char ucSector,
                unsigned char ucSAMKeyNb, unsigned char ucSAMKeyVersion, const void* pDiv);



 /**
 * Read a block of a MIFARE contactless card.
 * To be used in MIFARE Classic compatibility mode (SL1 or SL2).
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] ucBNr The block number to read.
 * @param[out] pBuffer The buffer that will receive the read data (16 bytes).
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL12ReadBlock(T_MFP_CONTEXT* pContext, unsigned char ucBNr, void* pBuffer);

 /**
 * Write a block of a sector of a MIFARE contactless card.
 * To be used in MIFARE Classic compatibility mode (SL1 or SL2).
 * @param[in, out] pContext Pointer to the MFP context.
 * @param[in] ucBNr The block number to write.
 * @param[in] pBuffer The buffer of the data to write (16 bytes).
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL12WriteBlock(T_MFP_CONTEXT* pContext, unsigned char ucBNr, const void* pBuffer);

/**
 * Make a value operation on a block.
 * To be used in MIFARE Classic compatibility mode (SL1 or SL2).
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] ucCC Value command code: cf. MFP_SL12_xxx
 * @param[in] ucBNr The sector number to use.
 * @param[in,out] pData Pointer to the 4 bytes value, can be NULL if value is not needed by the operation.
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL12ValueOperation(T_MFP_CONTEXT* pContext,  unsigned char ucCC, unsigned char ucBNr, void* pData);

/**
 * Read up to three consecutive blocks.
 * Only available in Security Level 2.
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] ucBNr The first block number to read.
 * @param[in] ucNbBlock number of blocks to read (from 1 to 3).
 * @param[out] pBuffer The buffer that receives the read data (16 bytes).
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL2ReadMultiBlock(T_MFP_CONTEXT* pContext, unsigned char ucBNr, unsigned char ucNbBlock, void* pBuffer);

/**
 * Write up to three consecutive blocks.
 * Only available in Security Level 2.
 * @param[in, out] pContext Pointer to the MFP context.
 * @param[in] ucBNr The first block number to write.
 * @param[in] ucNbBlock number of blocks to write (from 1 to 3).
 * @param[in] pBuffer The buffer of the data to write (16 bytes).
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL2WriteMultiBlock(T_MFP_CONTEXT* pContext, unsigned char ucBNr, unsigned char ucNbBlock, const void* pBuffer);

/**
 * Make a MIFARE Plus First or Following Authentication between PCD and PICC.
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] usKeyNb Key number of the key used for the authentication.
 * @param[in] ucMode \ref MFP_AUTH_F or \ref MFP_AUTH_N.
 * @param[in] pKey Value of the key (16 bytes).
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL3Authenticate(T_MFP_CONTEXT* pContext, unsigned short usKeyNb,  unsigned char ucMode, const void* pKey);

/**
 * Make a MIFARE Plus First or Following Authentication between PCD and PICC using the SAM.
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] usKeyNb Key number of the PICC key used for the authentication.
 * @param[in] ucMode \ref MFP_AUTH_F or \ref MFP_AUTH_N
 * @param[in] ucSAMKeyNb Key number of the SAM key used for the authentication.
 * @param[in] ucSAMKeyVersion Key version of the SAM key used.
 * @param[in] iDivInpLen Length in bytes of the \a pDivInp data. 0 if no diversification.
 * @param[in] pDivInp Pointer to diversification data for PICC key. NULL if no diversification.
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL3AuthenticateWithSAM(T_MFP_CONTEXT* pContext, unsigned short usKeyNb, unsigned char ucMode,
               unsigned char ucSAMKeyNb, unsigned char ucSAMKeyVersion, int iDivInpLen, const void* pDivInp);

/**
 * Reset the MIFARE Plus PCD-PICC authentication.
 * @note If authentication was made with SAM, the SAM-PICC state is also reset (internal call to \ref ClessMFP_SAMResetAuthentication).
 * @param[in,out] pContext Pointer to the MFP context.
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL3ResetAuthentication(T_MFP_CONTEXT* pContext);

/**
 * Read data from one or multiple blocks when in security level 3.
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] ucCC Read command code: cf. MFP_READ_XXX.
 * @param[in] usBNr Block number of the first block to read.
 * @param[in] ucNbBlock Number of blocks to read (from 1 to 14)
 * @param[out] pData Pointer to the buffer which will receive the data read.
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL3Read(T_MFP_CONTEXT* pContext, unsigned char ucCC, unsigned short usBNr, unsigned char ucNbBlock, void* pData);

/**
 * Write data to one or multiple blocks when in security level 3.
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] ucCC Write command code: cf. MFP_WRITE_XXX.
 * @param[in] usBNr Block number of the first block to write.
 * @param[in] ucNbBlock Number of blocks to write (max 3).
 * @param[in] pData Pointer to the data to write.
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL3Write(T_MFP_CONTEXT* pContext, unsigned char ucCC, unsigned short usBNr, unsigned char ucNbBlock, const void* pData);

/**
 * Make a value operation on a block.
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] ucCC Value command code: cf. MFP_READ_xxx, MFP_WRITE_xxx & MFP_VAL_xxx.
 * @param[in] usBNr1 Main block number used by the command \a ucCC.
 * @param[in] usBNr2 Additional block number used by the commands Increment-Transfer or Decrement-Transfer. For the other commands, put 0.
 * @param[in,out] pData Pointer to the 4 bytes value, can be NULL if value is not needed by the operation.
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL3ValueOperation(T_MFP_CONTEXT* pContext, unsigned char ucCC, unsigned short usBNr1,
                              unsigned short usBNr2, void* pData);

/**
 * Perform the Proximity Check sequence.
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] pKey Value of the Proximity Check key or NULL to use the sessions keys.
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL3ProximityCheck(T_MFP_CONTEXT* pContext, const void* pKey);

/**
 * Perform the Proximity Check sequence using the SAM.
 * @param[in,out] pContext
 * @param[in] ucSAMKeyNo SAM Key number of the Proximity Check key or 0xFF to use current session keys.
 * @param[in] ucSAMKeyVersion SAM Key version or 0xFF to use current session keys.
 * @param[in] iDivInpLen Length in bytes of the \a pDivInp data. 0 if no diversification.
 * @param[in] pDivInp Pointer to diversification data for Proximity Check key. NULL if no diversification.
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL3ProximityCheckWithSAM(T_MFP_CONTEXT* pContext, unsigned char ucSAMKeyNo,
      unsigned char ucSAMKeyVersion, int iDivInpLen, const void* pDivInp);

/**
 * Replace a MIFARE Plus key with a key stored in the SAM.
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] usKeyNb Key number of the PICC key to replace.
 * @param[in] ucSAMKeyNb Key number of the SAM key to use.
 * @param[in] ucSAMKeyVersion Key version of the SAM key.
 * @param[in] iDivInpLen Length in bytes of the \a pDivInp data. 0 if no diversification.
 * @param[in] pDivInp Pointer to diversification data for PICC key. NULL if no diversification.
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SL3ChangeKeyWithSAM(T_MFP_CONTEXT* pContext, unsigned short usKeyNb,
      unsigned char ucSAMKeyNb, unsigned char ucSAMKeyVersion, int iDivInpLen, const void* pDivInp);


/**
 * Authentication between PCD and SAM AV2.
 * @param[in,out] pContext Pointer to the MFP context.
 * @param[in] pKey Value of key (16 bytes).
 * @param[in] ucSAMKeyNo SAM key number to authenticate with.
 * @param[in] ucSAMKeyVersion SAM key version.
 * @param[in] ucSMMode Secure messaging protection mode to use for Host-SAM communication ( 0 : plain, 1 : MAC, 2 : Full (MAC + Cipher) ).
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SAMAuthenticate(T_MFP_CONTEXT* pContext, const void* pKey,
      unsigned char ucSAMKeyNo, unsigned char ucSAMKeyVersion, unsigned char ucSMMode);

/**
 * Reset SAM authentication state.
 * @param[in,out] pContext pContext Pointer to the MFP context.
 * @param[in] iMode   0 : reset all SAM authentication state (PCD, PICC), 1 : reset SAM authentication state with PICC
 * @return @ref ClessMFPErrors.
 */
int ClessMFP_SAMResetAuthentication(T_MFP_CONTEXT* pContext, int iMode);



//! @}

#endif /* CLESSMFP_H */
