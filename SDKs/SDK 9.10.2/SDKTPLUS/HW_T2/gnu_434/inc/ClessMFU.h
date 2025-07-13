//! \file
// \copyright  Ingenico 2013
// \brief This module implements MIFARE Ultralight and Ultralight C commands.

/** \addtogroup ClessMFU
   * @{
     *   \details This module manages MIFARE Ultralight and MIFARE Ultralight C cards.
     *   The cryptographic operations can be done either on the Thunder, either on a MIFARE SAM in AV1 mode or in AV2 mode.
     *
     *   \par How to use this library :
     *   -# <b>The PICC has to be detected and activated</b>.
     *   -# <b>The SAM has to be detected and powered if it will be used (\ref mifareSAM_AutoDetectSAM).</b>
     *   -# Create a new MIFARE Ultralight context (\ref ClessMFU_NewContext, \ref ClessMFU_NewContextWithSAM).
     *   <b>This is at this step that the cryptographic mode (use a SAM or not) is determined.</b>
     *   -# Use MIFARE Ultralight commands to interact with the PICC using commands provided by
     *   this library. For example : authentication, read/write a page (See \ref ClessMFUCommands).
     *   -# Free the MIFARE Ultralight context (\ref ClessMFU_FreeContext).
     *   -# Power off the SAM if it has been powered.
     *   -# Power off the Cless field.
     *
     *   \note A contactless communication is more sensitive to disturbances, therefore the previous sequence may failed
     *   with a communication error. In such a case, it is advised that the application implements an
     *   automatic retry/restart feature before ending up with an error. The retry feature should manage the
     *   detection/activation step but, if possible, it can also manage the commands step.
     *
     *   \defgroup ClessMFUErrors MIFARE Ultralight Errors
     *   \defgroup ClessMFUCommands MIFARE Ultralight Commands
     *   @{
     *      The MIFARE Ultralight cryptographic operations can be done by Telium
     *      or by a SAM. That's why for context creation and card authentication
     *      two versions of the function exist.
     *
     *      A Mifare Ultralight card is detected/activated with the MIFARE Classic protocol.
     *      To set up the MIFARE Classic protocol, the application should:
     *        - use the ClessMifare driver by calling ClessMifare_OpenDriver(),
     *        - detect the card with the \a ClessMifare_DetectCardxxx() functions,
     *        - activate the card with \a ClessMifare_ActiveCard().
     *
     *   @}
   * @}
 * \example MFUSample.c
*/

#include "MifareSAM.h"

#ifndef CLESSMFU_H
#define CLESSMFU_H

//! \addtogroup ClessMFUErrors
//! @{
// MFU Errors
#define MFU_OK                           0    //!< Successful operation
// API Error
#define MFU_PARAMETER_ERROR              0x01 //!< Invalid value of the parameter(s)
#define MFU_AUTHENTICATION_ERROR         0x03 //!< The authentication failed
#define MFU_COMMUNICATION_ERROR          0x04 //!< Communication error with PICC
#define MFU_COMMUNICATION_TIMEOUT_ERROR  0x05 //!< Communication timeout with PICC
#define MFU_INTERNAL_ERROR               0x08 //!< The library has a processing error
#define MFU_CRYPTO_ERROR                 0x09 //!< The library has a crypto processing error
#define MFU_RESPONSE_ERROR               0x0D //!< The response has an error (bad format, bad length...)
#define MFU_DLL_NOT_LOADED             0x0100 //!< The MIFARE DLL is not loaded
#define MFU_NAK                        0x0200 //!< The PICC NAK the command
#define MFU_SAM_ERROR                0x020000 //!< Error with SAM (the two lsb bytes are the SW1-SW2 retuned by the SAM)

//! @}

//! \addtogroup ClessMFUCommands
//! @{

//! \struct S_MFU_CONTEXT
//! \brief Context needed for MIFARE Ultralight commands processing.
struct S_MFU_CONTEXT;

//! \brief Type associated to the MIFARE Ultralight context.
typedef struct S_MFU_CONTEXT T_MFU_CONTEXT;


/**
 * Create a MIFARE Ultralight context.
 * The Mifare contactless driver should be opened before calling this function.
 * @return Pointer to the new MFU context. NULL if an error occurred.
 */
T_MFU_CONTEXT* ClessMFU_NewContext(void);

/**
 * Create a MIFARE Ultralight context using a SAM for cryptographic operations.
 * The Mifare contactless driver should be opened before calling this function.
 * @param[in] hSAM File descriptor of the SAM.
 * @param[in] samMode Use the SAM in AV1 or AV2 mode (see @ref T_MIFARE_SAM_MODE).
 * @return Return a pointer to the new MFU context. NULL if an error occurred.
 */
#ifdef __FRAMEWORK_TELIUM_PLUS__ 
T_MFU_CONTEXT* ClessMFU_NewContextWithSAM(Telium_File_t* hSAM, T_MIFARE_SAM_MODE samMode);
#else
T_MFU_CONTEXT* ClessMFU_NewContextWithSAM(FILE* hSAM, T_MIFARE_SAM_MODE samMode);
#endif

/**
 * Free a MIFARE Ultralight context.
 * The context and all data it contains will be deleted.
 * @param[in,out] pContext Pointer to the MFU context to delete. If NULL, nothing is done.
 * @remarks After having deleted a context, it can be advised to set the pointer value to NULL.
 * @sa @ref ClessMFU_NewContext.
 */
void ClessMFU_FreeContext(T_MFU_CONTEXT* pContext);

/**
 * Get the SAM context of a MIFARE Ultralight context.
 * @param[in] pContext Pointer to the T_MFU_CONTEXT (see \ref ClessMFU_NewContextWithSAM)
 * @return Return a pointer to \ref T_MIFARE_SAM_CONTEXT context. NULL if an error occurred.
 */
T_MIFARE_SAM_CONTEXT* ClessMFU_GetSAMContext(T_MFU_CONTEXT* pContext);

/**
 * Make a MIFARE Ultralight C Authentication between PCD and PICC.
 * @param[in,out] pContext Pointer to the MFU context.
 * @param[in] pKeyValue Value of the key (16 bytes).
 * @return @ref ClessMFUErrors.
 */
int ClessMFU_Authenticate(T_MFU_CONTEXT* pContext, const void* pKeyValue);

/**
 * Make a MIFARE Ultralight C Authentication between PCD and PICC using the SAM.
 * @note Ultralight C authentication is a 2 key 3DES authentication, thus SAM key should be a 2K3DES key.
 * @param[in,out] pContext Pointer to the MFU context.
 * @param[in] ucSAMKeyNb Key number of the SAM key used for the authentication.
 * @param[in] ucSAMKeyVersion Key version of the SAM key used.
 * @param[in] ucMode set options for SAM authentication
 *    <table><tr><th>Bits Value</th><th>Description</th></tr>
 *       <tr><td>Bit 7 - 5</td><td> 0 : RFU</td></tr>
 *       <tr><td>Bit 4</td><td>
 *          - 0 : use AV1 compatibility mode key diversification methods
 *          - 1 : use AV2 compatibility mode key diversification methods (make bit 3 ignored)</td></tr>
 *       <tr><td>Bit 3</td><td>
 *          - 0 : diversify using 2 encryption rounds
 *          - 1 : diversify using 1 encryption rounds
 *       <tr><td>Bit 2- 0</td><td> 0 : RFU </td></tr>
 *    </table>
 * @param[in] iDivLen Length in bytes of the \a pDiv data. 0 if no diversification.
 * @param[in] pDiv Pointer to diversification data for PICC key. NULL if no diversification.
 * @return @ref ClessMFUErrors.
 */
int ClessMFU_AuthenticateWithSAM(T_MFU_CONTEXT* pContext, unsigned char ucSAMKeyNb,
						unsigned char ucSAMKeyVersion, unsigned char ucMode, int iDivLen, const void* pDiv);

 /**
 * Read 4 successive pages of a MIFARE Ultralight contactless card.
 * @param[in,out] pContext Pointer to the MFU context.
 * @param[in] ucAdd The address of the first page.
 * @param[out] pBuffer The buffer that will receive the read data (16 bytes).
 * @return @ref ClessMFUErrors.
 */
int ClessMFU_Read(T_MFU_CONTEXT* pContext, unsigned char ucAdd, void* pBuffer);

 /**
 * Write 1 page of a MIFARE Ultralight contactless card.
 * @param[in, out] pContext Pointer to the MFU context.
 * @param[in] ucAdd The address of the page to write.
 * @param[in] pBuffer The buffer of the data to write (4 bytes).
 * @return @ref ClessMFUErrors.
 */
int ClessMFU_Write(T_MFU_CONTEXT* pContext, unsigned char ucAdd, const void* pBuffer);

//! @}


#endif /* CLESSMFU_H */
