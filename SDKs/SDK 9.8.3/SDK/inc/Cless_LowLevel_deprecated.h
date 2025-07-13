/**
 * \file
 * \brief Define the deprecated low level interface of the contactless DLL.
 *
 *
 * \author	Ingenico France
 * \author	Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico France has intellectual property rights relating to the technology embodied\n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico France.
 **/

#ifndef __CLESS_LOWLEVEL_DEPRECATED_H__INCLUDED__
#define __CLESS_LOWLEVEL_DEPRECATED_H__INCLUDED__

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup TPassApiErrors
//! @{

#ifndef _DEPRECATED_TPASS_SDK090800_
#define ERR_TPASS_DISCONNECT
// This error is generated to warn you about the deprecation of TPass DLL declarations for Telium+. You can remove this error by adding the define _DEPRECATED_TPASS_SDK090800_ to your project options.
#else
#define ERR_TPASS_DISCONNECT				ERR_TPASS_DISCONNECTED	//!< DEPRECATED: use \ref ERR_TPASS_DISCONNECTED instead.
#endif

//! @}

//! \addtogroup TPassApiGeneral
//! @{

// For compatibility
#ifndef _DEPRECATED_TPASS_SDK090800_
#define TPASS_CLESS_TYPE_CAD30VT
#define TPASS_CLESS_TYPE_P30
// This error is generated to warn you about the deprecation of TPass DLL declarations for Telium+. You can remove this error by adding the define _DEPRECATED_TPASS_SDK090800_ to your project options.
#else
#define TPASS_CLESS_TYPE_CAD30VT			TPASS_CLESS_TYPE_VENDING_PASS	//!< DEPRECATED: use \ref TPASS_CLESS_TYPE_VENDING_PASS instead.
#define TPASS_CLESS_TYPE_P30     			TPASS_CLESS_TYPE_P30C			//!< DEPRECATED: use \ref TPASS_CLESS_TYPE_P30C instead.
#endif

//! @}

//// Types //////////////////////////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

#ifndef _DEPRECATED_TPASS_SDK090800_
#define CLESS_OpenDriver()			ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define CLESS_CloseDriver()			ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define CLESS_IsDriverOpened()		ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define CLESS_DetectCardsStart(a, b)	ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define CLESS_DetectCards(a, b, c, d)			ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define CLESS_DetectCardsStop(a)		ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define CLESS_ActiveCard(a, b, c)			ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define CLESS_DeselectCard(a, b, c, d)		ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define CLESS_DeselectCardStart(a, b, c, d)	ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define CLESS_Apdu(a, b, c, d, e, f)				ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
// This error is generated to warn you about the deprecation of CLESS_xxx function for Telium+. You can remove this error by adding the define _DEPRECATED_TPASS_SDK090800_ to your project options.
#else

//! \addtogroup TPassContactLessStdObsolete
//! @{

//! \brief Open the ISO14443-4 driver.
//! \return Zero if an error occurs. Non zero if the driver is opened.
//! \warning This function will be deprecated in Telium+. Use \ref ClessEmv_OpenDriver instead.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_OpenDriver:0x31:0x08                                       */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_OpenDriver (void) MACRO_DEPRECATED;

//! \brief Close the ISO14443-4 driver.
//! \return Zero if an error occurs. Non zero if the driver is closed.
//! \warning This function will be deprecated in Telium+. Use \ref ClessEmv_CloseDriver instead.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_CloseDriver:0x31:0x09                                      */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_CloseDriver (void) MACRO_DEPRECATED;

//! \brief Indicate if the ISO14443-4 driver is opened or not.
//! \return Zero if the driver is closed. Non zero if the driver is opened.
//! \warning This function will be deprecated in Telium+. Use \ref ClessEmv_IsDriverOpened instead.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_IsDriverOpened:0x31:0x0A                                   */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_IsDriverOpened (void) MACRO_DEPRECATED;

/*! \brief Start the detection of an ISO14443-4 contactless card.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nTypeOfCard Type of card that is allowed:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_TYPE_A</td><td>Type A cards will be detected.</td></tr>
<tr><td>\a CL_TYPE_B</td><td>Type B cards will be detected.</td></tr>
<tr><td>\a CL_TYPE_AB</td><td>Type A and type B cards will be detected.</td></tr>
</table>
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The detection has started.</td></tr>
<tr><td>\a CL_KO</td><td>An error occurred.</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessEmv_DetectCardsStart instead.
\remarks
When a card is detected by the contactless driver the <b>CLESS</b> event is generated. Use <i>ttestall(CLESS, timeout)</i> to wait for it.<br>
When the event occurs, the application shall call \ref CLESS_DetectCards to retrieve the result and the number of detected cards.<br>
To cancel the detection, call \ref CLESS_DetectCardsStop or \ref CLESS_CloseDriver.<br>
When a card is detected, the application shall call \ref CLESS_ActiveCard before to send commands.
<br>Example:

//! \include Cless_LowLevel_Sample_21.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_DetectCardsStart:0x31:0x01                                 */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_DetectCardsStart(FILE* hDriver, unsigned char nTypeOfCard) MACRO_DEPRECATED;

/*! \brief Wait until an ISO14443-4 contactless card is detected.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nTypeOfCard Type of card that is allowed:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_TYPE_A</td><td>Type A cards will be detected.</td></tr>
<tr><td>\a CL_TYPE_B</td><td>Type B cards will be detected.</td></tr>
<tr><td>\a CL_TYPE_AB</td><td>Type A and type B cards will be detected.</td></tr>
</table>
\param[out] pNumOfCards The number of detected cards.
\param[in] nTimeout Detection timeout in <b>seconds</b>. If 0 is given the function tries to detect a card during a very small timeout.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>One or several cards are detected.</td></tr>
<tr><td>\a CL_KO</td><td>An error occurred.</td></tr>
<tr><td>\a CL_NOCARD</td><td>There is no card (timeout).</td></tr>
<tr><td>\a CL_TOOMANYCARDS</td><td>Too many cards are presented.</td></tr>
<tr><td>\a CL_INVALIDCARD</td><td>The detected card is not valid.</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessEmv_DetectCards instead.
\remarks
This function blocks the caller until a card is detected or the timeout is reached.
If the caller does not want to be blocked, it must call first the \ref CLESS_DetectCardsStart function.
In such a case, the \ref CLESS_DetectCards functions will not block the caller. So, a small timeout may be given.<br>
When a card is detected, the application shall call \ref CLESS_ActiveCard before to send commands.
<br>Example:

//! \include Cless_LowLevel_Sample_22.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_DetectCards:0x31:0x02                                      */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:3:ONE_POINTER                                                    */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_DetectCards(FILE* hDriver, unsigned char nTypeOfCard, unsigned int* pNumOfCards, unsigned int nTimeout) MACRO_DEPRECATED;

/*! \brief Stop the detection of a contactless card started with \ref CLESS_DetectCardsStart.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The detection is stopped.</td></tr>
<tr><td>\a CL_KO</td><td>An error occurred.</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessEmv_DetectCardsStop instead.
\remarks
See \ref CLESS_DetectCardsStart for more details.
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_DetectCardsStop:0x31:0x03                                  */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_DetectCardsStop(FILE* hDriver) MACRO_DEPRECATED;

/*! \brief Activate an ISO14443-4 contactless card to communicate with it.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref CLESS_DetectCards function.
\param[in] nKindOfCard Is the kind of card that is waited. It must be \a CL_ISO14443_4.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The card is activated.</td></tr>
<tr><td>\a CL_KO</td><td>An error occurred.</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessEmv_ActiveCard instead.
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_ActiveCard:0x31:0x04                                       */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_ActiveCard(FILE* hDriver, unsigned char nCardIndex, unsigned char nKindOfCard) MACRO_DEPRECATED;

/*! \brief Deselect an ISO14443-4 contactless card.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref CLESS_DetectCards function.
\param[in] bSendDeselect Indicate if the deselect command shall be sent to the card or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Send the deselect command to the card. Use it in the nominal case (no error).</td></tr>
<tr><td>\a FALSE</td><td>Do not send the deselect command to the card. Use it only when the last contactless function call returned an error.</td></tr>
</table>
\param[in] bWaitRemove Indicate if the function shall wait for the card to be removed or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Wait for the card to be removed from the field.</td></tr>
<tr><td>\a FALSE</td><td>Returns immediately.</td></tr>
</table>
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The card is deselected.</td></tr>
<tr><td>\a CL_KO</td><td>An error occurred.</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessEmv_DeselectCard instead.
\remarks <b>With Level 1 1.X drivers :</b>
\remarks This function wait a physical card remove from Cless field only if bWaitRemove parameter is set to TRUE.
\remarks <b>With Level 1 2.X drivers (2.0 and upper):</b>
\remarks This function don't use bSendDeselect and bWaitRemove parameters. Theses parameters are kept for compatibility.
\remarks In any case, this function send a deselect sequence and wait a physical card remove from Cless field.
\remarks If the card remove action doesn't be wait, don't call this function (DESELECT 2.0) but use the PICC Reset action with ClessEmv_FormatCommand(RESETPICC,0,0,0,0).
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_DeselectCard:0x31:0x05                                     */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_DeselectCard(FILE* hDriver, unsigned char nCardIndex, unsigned int bSendDeselect, unsigned int bWaitRemove) MACRO_DEPRECATED;

/*! \brief Start the deselection of an ISO14443-4 contactless card.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref ClessEmv_DetectCards function.
\param[in] bSendDeselect Indicate if the deselect command shall be sent to the card or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Send the deselect command to the card. Use it in the nominal case (no error).</td></tr>
<tr><td>\a FALSE</td><td>Do not send the deselect command to the card. Use it only when the last contactless function call returned an error.</td></tr>
</table>
\param[in] bWaitRemove Indicate if the function shall wait for the card to be removed or not:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a TRUE</td><td>Wait for the card to be removed from the field.</td></tr>
<tr><td>\a FALSE</td><td>Returns immediately.</td></tr>
</table>
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The card is being deselected.</td></tr>
<tr><td>\a CL_KO</td><td>An error occurred.</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessEmv_DeselectCardStart instead.
\remarks
When the operation is finished the <b>CLESS</b> event is generated. Use <i>ttestall(CLESS, timeout)</i> to wait for it.<br>
To cancel the deselection, call \ref CLESS_CloseDriver.<br>
\remarks <b>With Level 1 1.X drivers :</b>
\remarks If bWaitRemove parameter is set to TRUE, this function wait a physical card remove from Cless field.
\remarks <b>With Level 1 2.X drivers (2.0 and upper):</b>
\remarks This function don't use bSendDeselect and bWaitRemove parameters. Theses parameters are kept for compatibility.
\remarks In any case, this function send a deselect sequence and wait a physical card remove from Cless field.
\remarks If the card remove action doesn't be wait, don't call this function (DESELECT 2.0) but use the PICC Reset action with ClessEmv_FormatCommand(RESETPICC,0,0,0,0).
*/
unsigned int CLESS_DeselectCardStart(FILE* hDriver, unsigned char nCardIndex, unsigned int bSendDeselect, unsigned int bWaitRemove) MACRO_DEPRECATED;

/*! \brief Send a command to an ISO14443-4 contactless card.
\param[in] hDriver If \ref CLESS_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref CLESS_DetectCards function.
\param[in] pCommand Is the command to send to the card.
\param[in] nCommandLength Is the length of the command to be sent to the card.
\param[out] pResponse Will contain the card response. The maximum response length is 288 bytes.
\param[out] pResponseLength Is the length of the card response.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_OK</td><td>The command is sent.</td></tr>
<tr><td>\a CL_KO</td><td>An error occurred.</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessEmv_Apdu instead.
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:CLESS_Apdu:0x31:0x07                                             */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:3:DATA_SIZE(nCommandLength)                                      */
/* @GSIM_A:3:IN_ONLY                                                        */
/* @GSIM_A:5:DATA_CODE(*pResponseLength)                                    */
/* @GSIM_A:5:OUT_ONLY                                                       */
/* @GSIM_A:6:ONE_POINTER                                                    */
/* ------------------------------------------------------------------------ */
unsigned int CLESS_Apdu(FILE* hDriver, unsigned char nCardIndex, const void* pCommand, unsigned int nCommandLength, void* pResponse, unsigned int* pResponseLength) MACRO_DEPRECATED;

//! @}

#endif

#ifndef _DEPRECATED_TPASS_SDK090800_
#define MF_OpenDriver()			ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define MF_CloseDriver()		ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define MF_IsDriverOpened()		ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define MF_DetectCards(a, b, c)		ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define MF_DetectCardsEx(a, b, c, d)		ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define MF_GetUid(a, b, c, d, e)				ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define MF_ActiveCard(a, b)			ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define MF_Authentication(a, b, c, d)		ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define MF_ReadBlock(a, b, c, d, e)			ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define MF_WriteBlock(a, b, c, d, e)			ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
#define MF_ValueOperation(a, b, c, d, e, f)		ERROR_Deprecation_For_TPassDLL_SeeDocumentation_In_CHM_File;
// This error is generated to warn you about the deprecation of MF_xxx functions for Telium+. You can remove this error by adding the define _DEPRECATED_TPASS_SDK090800_ to your project options.
#else

//! \addtogroup TPassContactLessMifareObsolete
//! @{

//! \brief Open the MIFARE driver.
//! \return Zero if an error occurs. Non zero if the driver is opened.
//! \warning This function will be deprecated in Telium+. Use \ref ClessMifare_OpenDriver instead.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_OpenDriver:0x2D:0x25                                          */
/* ------------------------------------------------------------------------ */
unsigned int MF_OpenDriver (void) MACRO_DEPRECATED;

//! \brief Close the MIFARE driver.
//! \return Zero if an error occurs. Non zero if the driver is closed.
//! \warning This function will be deprecated in Telium+. Use \ref ClessMifare_CloseDriver instead.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_CloseDriver:0x2D:0x26                                         */
/* ------------------------------------------------------------------------ */
unsigned int MF_CloseDriver (void) MACRO_DEPRECATED;

//! \brief Indicate if the MIFARE driver is opened or not.
//! \return Zero if the driver is closed. Non zero if the driver is opened.
//! \warning This function will be deprecated in Telium+. Use \ref ClessMifare_IsDriverOpened instead.
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_IsDriverOpened:0x2D:0x27                                      */
/* ------------------------------------------------------------------------ */
unsigned int MF_IsDriverOpened (void) MACRO_DEPRECATED;

/*! \brief Wait until a MIFARE contactless card is detected.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in,out] pNumOfCards As input, specify the the maximum number of cards that can be presented.
As output, it is the number of detected cards.
\param[in] nTimeout Detection timeout in <b>seconds</b>. If 0 is given the function tries to detect a card during a very small timeout.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>One or several cards are detected.</td></tr>
<tr><td>\a MF_KO</td><td>An error occurred.</td></tr>
<tr><td>\a MF_NOCARD</td><td>There is no card (timeout).</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessMifare_DetectCards instead.
\remarks
This function blocks the caller until a card is detected or the timeout is reached.
When a card is detected, the application shall call \ref MF_ActiveCard before to send commands.
<br>Example:

//! \include Cless_LowLevel_Sample_25.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_DetectCards:0x2D:0x15                                         */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:2:ONE_POINTER                                                    */
/* ------------------------------------------------------------------------ */
unsigned int MF_DetectCards(FILE* hDriver, unsigned int *pNumOfCards, unsigned int nTimeout) MACRO_DEPRECATED;

/*! \brief Wait until a MIFARE contactless card is detected.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nKindOfCard Type of the MIFARE. Can a mix of the following values:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_MF_CLASSIC</td><td>Support for MIFARE Classic cards.</td></tr>
<tr><td>\a CL_MF_ULTRALIGHT</td><td>Support for MIFARE Ultra Light cards.</td></tr>
</table>
\param[in,out] pNumOfCards As input, specify the the maximum number of cards that can be presented.
As output, it is the number of detected cards.
\param[in] nTimeout Detection timeout in <b>seconds</b>. If 0 is given the function tries to detect a card during a very small timeout.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>One or several cards are detected.</td></tr>
<tr><td>\a MF_KO</td><td>An error occurred.</td></tr>
<tr><td>\a MF_NOCARD</td><td>There is no card (timeout).</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessMifare_DetectCardsEx instead.
\remarks
This function blocks the caller until a card is detected or the timeout is reached.
When a card is detected, the application shall call \ref MF_ActiveCard before to send commands.
<br>Example:

//! \include Cless_LowLevel_Sample_26.c
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_DetectCardsEx:0x2D:0x2A                                       */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:3:ONE_POINTER                                                    */
/* ------------------------------------------------------------------------ */
unsigned int MF_DetectCardsEx(FILE* hDriver, unsigned char nKindOfCard, unsigned int *pNumOfCards, unsigned int nTimeout) MACRO_DEPRECATED;

/*! \brief Retrieve the type of the MIFARE card and its UID.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref MF_DetectCards function.
\param[out] pKindOfCard The type of the MIFARE card.
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a CL_MF_CLASSIC</td><td>MIFARE Classic.</td></tr>
<tr><td>\a CL_MF_ULTRALIGHT</td><td>MIFARE Ultra Light.</td></tr>
</table>
\param[out] pUidLength Length of the UID.
\param[out] pUid UID of the card.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>One or several cards are detected.</td></tr>
<tr><td>\a MF_KO</td><td>An error occurred.</td></tr>
<tr><td>\a CLESS_NOT_IMPLEMENTED</td><td>The function is not implemented (the driver is too old).</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessMifare_GetUid instead.
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_GetUid:0x2D:0x2B                                              */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:2:IN_ONLY                                                       */
/* @GSIM_A:3:ONE_POINTER                                                    */
/* @GSIM_A:3:OUT_ONLY                                                       */
/* @GSIM_A:4:ONE_POINTER                                                    */
/* @GSIM_A:4:OUT_ONLY                                                       */
/* @GSIM_A:5:DATA_SIZE(10)                                                  */
/* @GSIM_A:5:OUT_ONLY                                                       */
/* ------------------------------------------------------------------------ */
unsigned int MF_GetUid(FILE* hDriver, unsigned char nCardIndex, unsigned char *pKindOfCard, unsigned char *pUidLength, unsigned char *pUid) MACRO_DEPRECATED;

/*! \brief Activate a MIFARE contactless card to communicate with it.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nCardIndex Is the index of the card. It must be between 0 and the number of cards given by is the \ref MF_DetectCards function.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The card is activated.</td></tr>
<tr><td>\a MF_KO</td><td>An error occurred.</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessMifare_ActiveCard instead.
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_ActiveCard:0x2D:0x16                                          */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* ------------------------------------------------------------------------ */
unsigned int MF_ActiveCard(FILE* hDriver, unsigned char nCardIndex) MACRO_DEPRECATED;

/*! \brief Authenticate a sector of a MIFARE contactless card.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nKeyType The type of the key:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a KEY_A</td><td>It is a type A key.</td></tr>
<tr><td>\a KEY_B</td><td>It is a type B key.</td></tr>
</table>
\param[in] pUncodedKey Is the key to use. The length of a MIFARE key is \ref TPASS_MIFARE_KEY_LENGTH (6 bytes).
\param[in] nSector The sector to authenticate.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The sector is authenticated.</td></tr>
<tr><td>\a MF_KO</td><td>An error occurred.</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessMifare_Authentication instead.
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_Authentication:0x2D:0x17                                      */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:3:DATA_SIZE(6)                                                   */
/* @GSIM_A:3:IN_ONLY                                                        */
/* ------------------------------------------------------------------------ */
unsigned int MF_Authentication(FILE* hDriver, unsigned char nKeyType, const unsigned char* pUncodedKey, unsigned char nSector) MACRO_DEPRECATED;

/*! \brief Read a block of a sector of a MIFARE contactless card.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nDataType Is the type of the data:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a VALUE</td><td>To access to a 4 bytes value.</td></tr>
<tr><td>\a DATA</td><td>To access to a 16 bytes buffer.</td></tr>
</table>
\param[in] nSector The sector number to read.
\param[in] nBlock The block number where the sector is located.
\param[out] pBuffer The buffer that will receive the read data.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The block is read.</td></tr>
<tr><td>\a MF_KO</td><td>An error occurred.</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessMifare_ReadBlock instead.
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_ReadBlock:0x2D:0x18                                           */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:5:DATA_CODE(((nDataType == 1) ? 4:16))                           */
/* @GSIM_A:5:OUT_ONLY                                                       */
/* ------------------------------------------------------------------------ */
unsigned int MF_ReadBlock(FILE* hDriver, unsigned char nDataType, unsigned char nSector, unsigned char nBlock, void* pBuffer) MACRO_DEPRECATED;

/*! \brief Write a block of a sector of a MIFARE contactless card.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nDataType Is the type of the data:
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a VALUE</td><td>To access to a 4 bytes value.</td></tr>
<tr><td>\a DATA</td><td>To access to a 16 bytes buffer.</td></tr>
</table>
\param[in] nSector The sector number to read.
\param[in] nBlock The block number where the sector is located.
\param[in] pBuffer The buffer that contains the data to write.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The block is written.</td></tr>
<tr><td>\a MF_KO</td><td>An error occurred.</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessMifare_WriteBlock instead.
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_WriteBlock:0x2D:0x19                                          */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:5:DATA_CODE(((nDataType == 1) ? 4:16))                           */
/* @GSIM_A:5:IN_ONLY                                                        */
/* ------------------------------------------------------------------------ */
unsigned int MF_WriteBlock(FILE* hDriver, unsigned char nDataType, unsigned char nSector, unsigned char nBlock, const void* pBuffer) MACRO_DEPRECATED;

/*! \brief Perform an operation on the value of a block of a MIFARE contactless card.
\param[in] hDriver If \ref MF_OpenDriver function is used, this parameter shall be \a NULL, otherwise give the file handle of the contactless driver returned by \a fopen.
\param[in] nOperationType Is the operation to perform.
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_INCREMENT</td><td>To increment the value.</td></tr>
<tr><td>\a MF_DECREMENT</td><td>To decrement the value.</td></tr>
<tr><td>\a MF_RESTORE</td><td>To restore the value.</td></tr>
</table>
\param[in] nSector The sector number on which the operation is performed.
\param[in] nSourceBlock The source block where the sector is located.
\param[in] nDestBlock The destination block where the sector is located.
\param[in] pValue The value used of the operation.
\return
<table><tr><th>Value</th><th>Description</th></tr>
<tr><td>\a MF_OK</td><td>The operation on the block is successful.</td></tr>
<tr><td>\a MF_KO</td><td>An error occurred.</td></tr>
</table>
\warning This function will be deprecated in Telium+. Use \ref ClessMifare_ValueOperation instead.
*/
/* ------------------------------------------------------------------------ */
/* @GSIM_F:MF_ValueOperation:0x2D:0x1A                                      */
/* @GSIM_A:1:ONE_ADDRESS                                                    */
/* @GSIM_A:6:DATA_SIZE(4)                                                   */
/* @GSIM_A:6:IN_ONLY                                                        */
/* ------------------------------------------------------------------------ */
unsigned int MF_ValueOperation(FILE* hDriver, unsigned char nOperationType, unsigned char nSector, unsigned char nSourceBlock, unsigned char nDestBlock, void* pValue) MACRO_DEPRECATED;

//! @}

#endif

#endif // __CLESS_LOWLEVEL_DEPRECATED_H__INCLUDED__
