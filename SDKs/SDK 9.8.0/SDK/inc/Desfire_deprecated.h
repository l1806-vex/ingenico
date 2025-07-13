//! \file Desfire_deprecated.h
//! \brief This module implements the deprecated DESFire commands



#ifndef __DESFIRE_DEPRECATED_H__
#define __DESFIRE_DEPRECATED_H__


#ifndef _DEPRECATED_MIFARE_SDK090800_

#define mifareSAM_SelectApplication()				ERROR_Deprecation_For_MifareDLL_SeeDocumentation_In_CHM_File;
#define mifareSAM_VerifyMAC()						ERROR_Deprecation_For_MifareDLL_SeeDocumentation_In_CHM_File;
#define mifareSAM_GenerateMAC()						ERROR_Deprecation_For_MifareDLL_SeeDocumentation_In_CHM_File;
#define mifareSAM_DecipherData()					ERROR_Deprecation_For_MifareDLL_SeeDocumentation_In_CHM_File;
#define mifareSAM_EncipherData()					ERROR_Deprecation_For_MifareDLL_SeeDocumentation_In_CHM_File;
#define mifareSAM_AuthenticatePICCFirstPart()		ERROR_Deprecation_For_MifareDLL_SeeDocumentation_In_CHM_File;
#define mifareSAM_AuthenticatePICCSecondPart()		ERROR_Deprecation_For_MifareDLL_SeeDocumentation_In_CHM_File;
#define mifareSAM_ChangeKeyPICC()					ERROR_Deprecation_For_MifareDLL_SeeDocumentation_In_CHM_File;
// This error is generated to warn you about the deprecation of some Mifare DLL functions for Telium+. You can remove this error by adding the define _DEPRECATED_MIFARE_SDK090800_ to your project options.

#else // _DEPRECATED_MIFARE_SDK090800_
//! \addtogroup SAMCommandsDeprecated
//! @{

// SAM Security and configuration commands

//! \deprecated The application should not call this function.
//! \brief Select a list of available keys matching to a DESFire application
//! \details This command has to be sent when a SelectApplication command
//! has been sent on a DESFire card so that the key number specified on further
//! operations on the DESFire PICC match to the corresponding key of the SAM.
//! \param[in] pSAMCtx Pointer to the SAM context
//! \param[in] tucAid Application ID to be selected
//! \return
//! - 0 if OK
//! - EMV_apdu error return code in case of EMV_apdu error
//! - Byte SW2 or the SAM response APDU if SW1 SW2 is not equal to 0x90 0x00
//! \sa \ref desfire_SelectApplication
extern int mifareSAM_SelectApplication(T_MIFARE_SAM_CONTEXT* pSAMCtx,
      unsigned char tucAid[3]) MACRO_DEPRECATED;

// Data Processing commands

//! \deprecated The application should not call this function.
//! \brief Ask the SAM to verify the MAC appended to an amount of data.
//! \param[in] pSAMCtx Pointer to the SAM context
//! \param[in] iDataLen Length of the amount of data, including the MAC.
//! \param[in] pData Buffer containing the data and the MAC to verify
//! \param[in] iMacLen Number of byte to verify in the MAC. If set to 0, the whole
//! MAC will be checked.
//! \return
//! - 0 if OK
//! - EMV_apdu error return code in case of EMV_apdu error
//! - Byte SW2 or the SAM response APDU if SW1 SW2 is not equal to 0x90 0x00
//! \sa \ref mifareSAM_GenerateMAC
extern int mifareSAM_VerifyMAC(T_MIFARE_SAM_CONTEXT* pSAMCtx, int iDataLen,
     unsigned char *pData, int iMacLen) MACRO_DEPRECATED;

//! \deprecated The application should not call this function.
//! \brief Ask the SAM to generate a MAC from an amount of data/
//! \details The generation of a MAC will make the SAM update its IV with the
//! generated MAC.
//! \param[in] pSAMCtx Pointer to the SAM context
//! \param[in] iDataLen Length of the amount of data.
//! \param[in] pData Data used to generate the MAC
//! \param[out] puiMacLen Size of the generated MAC returned by the SAM
//! \param[out] pMac MAC returned by the SAM
//! \return
//! - 0 if OK
//! - EMV_apdu error return code in case of EMV_apdu error
//! - Byte SW2 or the SAM response APDU if SW1 SW2 is not equal to 0x90 0x00
//! \sa \ref mifareSAM_VerifyMAC
extern int mifareSAM_GenerateMAC(T_MIFARE_SAM_CONTEXT* pSAMCtx, int iDataLen,
      unsigned char *pData, unsigned int *puiMacLen, unsigned char *pMac);

//! \deprecated The application should not call this function.
//! \brief Use the SAM to decipher an amount of data.
//! \param[in] pSAMCtx Pointer to the SAM context
//! \param[in] iDataLen Length of the amount of data.
//! \param[in] pData Data to decipher
//! \param[out] piDecipheredDataLen Size of deciphered data.
//! \param[out] pDecipheredData Deciphered data.
//! \return
//! - 0 if OK
//! - EMV_apdu error return code in case of EMV_apdu error
//! - Byte SW2 or the SAM response APDU if SW1 SW2 is not equal to 0x90 0x00
//! \sa \ref mifareSAM_EncipherData
extern int mifareSAM_DecipherData(T_MIFARE_SAM_CONTEXT* pSAMCtx, int iDataLen,
      unsigned char *pData, int *piDecipheredDataLen,
      unsigned char *pDecipheredData) MACRO_DEPRECATED;

//! \deprecated The application should not call this function.
//! \brief Use the SAM to encipher an amount of data.
//! \param[in] pSAMCtx Pointer to the SAM context
//! \param[in] ucOffset Offset specifying the first byte in the data field to be encrypted
//! \param[in] iDataLen Length of the amount of data.
//! \param[in] pData Data to encipher
//! \param[out] piCipheredDataLen Size of enciphered data.
//! \param[out] pCipheredData enciphered data.
//! \return
//! - 0 if OK
//! - EMV_apdu error return code in case of EMV_apdu error
//! - Byte SW2 or the SAM response APDU if SW1 SW2 is not equal to 0x90 0x00
//! \sa \ref mifareSAM_DecipherData
extern int mifareSAM_EncipherData(T_MIFARE_SAM_CONTEXT* pSAMCtx,
      unsigned char ucOffset, int iDataLen, unsigned char *pData,
      int *piCipheredDataLen, unsigned char *pCipheredData) MACRO_DEPRECATED;

// Mifare DESFire and ULC in non-X-mode commands

//! \deprecated The application should not call this function.
//! \brief Send the first response of a PICC during authentication to the SAM.
//! \details Send the ciphered random number (rndB) received from the PICC to
//! the SAM. The SAM will then decipher it, roll it, generate a other random
//! number (rndA) and return rndA+rndB' ciphered. This result has to be sent to
//! the PICC to continue authentication.
//! \param[in] pSAMCtx Pointer to the SAM context
//! \param[in] ucKeyNo Key number :
//! - DESFire Key number (0x00 to 0x0D) if \ref mifareSAM_SelectApplication has
//! been sent before.
//! - SAM Key reference number (0x00 to 0x7F) if \ref mifareSAM_SelectApplication
//! <b>has not been sent</b> before
//! \param[in] ucKeyVersion Key version
//! \param[in] ucAuthMode Authentication mode :
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 5</td><td>RFU</td></tr>
//! <tr><td>Bit 4</td><td>
//! - 0 : use AV1 compatibility mode key diversification methods
//! - 1 : use MIFARE SAM AV2 mode key diversification methods</td></tr>
//! <tr><td>Bit 3</td><td> DES or 2K3DES keys :
//! - 0 : diversify using 2 encryption rounds
//! - 1 : diversify using 1 encryption rounds
//! .
//! 3K3DES or AES keys :
//! - RFU : has to be set to 0.
//! .
//! If bit 4 is set to 1 : RFU </td></tr>
//! <tr><td>Bit 2</td><td>RFU </td></tr>
//! <tr><td>Bit 1</td><td>
//! - 0 : key selection by SAM entry number
//! - 1 : key selection by DESFire key number</td></tr>
//! <tr><td>Bit 0</td><td>
//! - 0 : no key diversification
//! - 1 : key diversified with 8 or 16 bytes diversification input</td></tr>
//! </table>
//! \param[in] iDataLen Size of RndB enciphered
//! \param[in] pData RndB enciphered returned by the first authentication command
//! sent to the PICC.
//! \param[in] iDivInpLen Diversification input length
//! \param[in] pDivInp Diversification input.
//! \param[out] piResLen SAM response length
//! \param[out] pucRes SAM response to the first part authentication command,
//! RndA + RndB' ciphered
//! \return
//! - 0 if OK
//! - EMV_apdu error return code in case of EMV_apdu error
//! - Byte SW2 or the SAM response APDU if SW1 SW2 is not equal to 0x90 0x00
//! \sa \ref mifareSAM_AuthenticatePICCSecondPart
extern int mifareSAM_AuthenticatePICCFirstPart(T_MIFARE_SAM_CONTEXT* pSAMCtx,
      unsigned char ucKeyNo, unsigned char ucKeyVersion,
      unsigned char ucAuthMode, int iDataLen, unsigned char *pData,
      int iDivInpLen, unsigned char *pDivInp, int *piResLen,
      unsigned char *pucRes) MACRO_DEPRECATED;

//! \deprecated The application should not call this function.
//! \brief Send the second response of a PICC during authentication to the SAM
//! \details Send the ciphered second random number rolled (RndA') received
//! from the PICC to the SAM. The SAM will then decipher it to retrieve RndA' and
//! compare it the RndA it has generated and sent to the PICC during first part of
//! authentication. If it does not match, then the authentication is aborted.
//! \param[in] pSAMCtx Pointer to the SAM context
//! \param[in] iDataLen Size of RndA' enciphered
//! \param[in] pData RndA' enciphered returned by the second authentication command
//! sent to the PICC.
//! \return
//! - 0 if OK
//! - EMV_apdu error return code in case of EMV_apdu error
//! - Byte SW2 or the SAM response APDU if SW1 SW2 is not equal to 0x90 0x00
//! \sa \ref mifareSAM_AuthenticatePICCFirstPart
extern int mifareSAM_AuthenticatePICCSecondPart(T_MIFARE_SAM_CONTEXT* pSAMCtx,
      int iDataLen, unsigned char *pData) MACRO_DEPRECATED;

//! \deprecated The application should not call this function.
//! \brief Ask the SAM to generate the payload cryptogram to send to the PICC via
//! the ChangeKey command (\ref desfire_ChangeKey)
//! \param[in] pSAMCtx Pointer to the SAM context
//! \param[in] ucKeyCompMeth Key compilation method (defines the method of key generation)
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 6</td><td>RFU</td></tr>
//! <tr><td>Bit 5</td><td>choice between AV1 and AV2 key diversification methods.
//! - 0 : diversify using AV1 compatibility mode key diversification methods.
//! - 1 : diversify using MIFARE SAM AV2 mode key diversification methods.</td></tr>
//! <tr><td>Bit 4</td><td>key diversification method for current key.
//! RFU if key entry is of type 3K3DES or AES or bit 5 is set to 1.
//! - 0 : diversify using 2 encryption method rounds.
//! - 1 : diversify using 1 encryption method rounds.</td></tr>
//! <tr><td>Bit 3</td><td>key diversification method for new key.
//! RFU if key entry is of type 3K3DES or AES or bit 5 is set to 1.
//! - 0 : diversify using 2 encryption method rounds.
//! - 1 : diversify using 1 encryption method rounds.</td></tr>
//! <tr><td>Bit 2</td><td>use of key diversification for current key.
//! - 0 : current key is not diversified.
//! - 1 : current key is already diversified.</td></tr>
//! <tr><td>Bit 1</td><td>use of key diversification for new key.
//! - 0 : current key is should not be diversified.
//! - 1 : current key is should be diversified.</td></tr>
//! <tr><td>Bit 0</td><td>role or involvement of ChangeKey key.
//! - 0 : If the ChangeKey key of the targeted application is 0x00 to 0x0D.
//! In this case both the old and the new key are involved in the calculation
//! of the deciphered key data.
//! - 1 : if the ChangeKey key of the targeted application is 0x0E or the master
//! (key 0x00) itself changed. In this case only the new key is involved ins the
//! calculation of the deciphered key data. The parameter ucOldSAMKeyNo is ignored
//! in this case.</td></tr>
//! </table>
//! \param[in] ucConfig Configuration
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 5</td><td>RFU</td></tr>
//! <tr><td>Bit 4</td><td>
//! - 0 : Any other key but not the DESFire card master key shall be changed</td></tr>
//! - 1 : the DESFire card master key shall be changed (the key type information
//! has to be included in the cryptogram)</td></tr>
//! <tr><td>Bit 3 - 0</td><td> number of the DESFire key to be changed</td></tr>
//! </table>
//! \param[in] ucOldKeyNo 1 byte unsigned SAM key entry holding the current key
//! (0x00 to 0x7F).
//! \param[in] ucOldKeyVersion 1 byte unsigned key version of the current key
//! (0x00 to 0xFF)
//! \param[in] ucNewKeyNo 1 byte unsigned SAM key entry holding the new key
//! (0x00 to 0x7F).
//! \param[in] ucNewKeyVersion 1 byte unsigned key version of the new key
//! (0x00 to 0xFF)
//! \param[in] iDivInpLen Length of the diversification input parameter
//! \param[in] pDivInp Diversification input
//! \param[out] piDataLen Length of the cryptogram computed by the SAM
//! \param[out] pData Cryptogram computed by the SAM
//! \return
//! - 0 if OK
//! - EMV_apdu error return code in case of EMV_apdu error
//! - Byte SW2 or the SAM response APDU if SW1 SW2 is not equal to 0x90 0x00
extern int mifareSAM_ChangeKeyPICC(T_MIFARE_SAM_CONTEXT* pSAMCtx,
      unsigned char ucKeyCompMeth, unsigned char ucConfig,
      unsigned char ucOldKeyNo, unsigned char ucOldKeyVersion,
      unsigned char ucNewKeyNo, unsigned char ucNewKeyVersion, int iDivInpLen,
      unsigned char *pDivInp, int *piDataLen, unsigned char *pData) MACRO_DEPRECATED;

//! @}
#endif // _DEPRECATED_MIFARE_SDK090800_

#endif /* !__DESFIRE_DEPRECATED_H__ */
