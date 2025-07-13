/**
 * \file	CST_UserInterfaceHelpers.h
 * \brief 	Module that manages the user interface.
 *
 * \author	Ingenico
 * \author	Copyright (c) 2009 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

#define ERASE						TRUE
#define NO_ERASE					FALSE

#define WAIT						TRUE
#define NOWAIT						FALSE

#define WITHBEEP					TRUE
#define WITHOUTBEEP					FALSE

// Output display alignment
#define HELPERS_ALIGN_LEFT					(1)
#define HELPERS_ALIGN_CENTER				(2)
#define HELPERS_ALIGN_RIGHT					(3)

// Customer display lines
#define HELPERS_CUSTOMER_LINE_1				(0)
#define HELPERS_CUSTOMER_LINE_2				(1)
#define HELPERS_CUSTOMER_LINE_3				(2)
#define HELPERS_CUSTOMER_LINE_4				(3)
#define HELPERS_CUSTOMER_LINE_5				(4)
#define HELPERS_CUSTOMER_LINE_6				(5)

#define HELPERS_MERCHANT_LINE_1				(0)
#define HELPERS_MERCHANT_LINE_2				(1)
#define HELPERS_MERCHANT_LINE_3				(2)
#define HELPERS_MERCHANT_LINE_4				(3)
#define HELPERS_MERCHANT_LINE_5				(4)
#define HELPERS_MERCHANT_LINE_6				(5)

// Indicates if it is a payWave or a VisaWave transaction
#define HELPERS_PAYWAVE						1
#define HELPERS_VISAWAVE					2

// Indicates if it is an offline or an online transaction
#define OFFLINE								1
#define ONLINE								2

// Indicates if Available Offline Spending Amount is displayed/printed or not
#define WITH_AOSA							1
#define WITHOUT_AOSA						0

#define WITH_SIGNATURE						1
#define WITHOUT_SIGNATURE					0

#define APPROVED_TICKED 					1
#define DECLINED_TICKED 					0


//// Global variables ///////////////////////////////////////////

typedef struct
{
	int nMessageId;
	const char * sIconName;
} T_CST_HELPER_MENU_ITEM;


//// Functions //////////////////////////////////////////////////

//! \brief Create a menu according options.
//! \param[in] nTitle : message number of the Menu
//! \param[in] nDefaultChoice : default choice
//! \param[in] nItems : number of items in the menu
//! \param[in] Items : arrays containing all the menu items
//! \param[in] bUseCguiIconList Indicates if the CGUI icon list shall be used (if available) or not. If not, CGUI list is used instead.
//! \return 0 if ok, error code else.

int HelperDisplayMenu(const int nTitle, int nDefaultChoice, int nItems, const T_CST_HELPER_MENU_ITEM Items[], int bUseCguiIconList);



//! \brief This function displays a text on the customer pinpad (if connected).
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] ucLongLine LONGLINE for long line to display.

void _Helper_DisplayTextCustomer(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, int nAlignment, unsigned char ucLongLine);



//! \brief This function displays a text on the customer pinpad (if connected).
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,

#define Helper_DisplayTextCustomer(nEraseDisplay,nLineNumber,ptrMSG,nAlignment) \
   _Helper_DisplayTextCustomer(nEraseDisplay,nLineNumber,ptrMSG,nAlignment,SHORTLINE)



//! \brief This function displays a text on the customer pinpad (if connected).
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
#define Helper_DisplayTextCustomerLong(nEraseDisplay,nLineNumber,ptrMSG,nAlignment) \
    _Helper_DisplayTextCustomer(nEraseDisplay,nLineNumber,ptrMSG,nAlignment,LONGLINE)



//! \brief This function displays a text on the PinPad or terminal used to input Pin.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bLongLine LONG if long line must be displayed.

void _Helper_DisplayPinText(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, int nAlignment, unsigned char bLongLine);



//! \brief This function displays a text on the PinPad or terminal used to input Pin.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,

#define Helper_DisplayPinText(nEraseDisplay,nLineNumber,ptrMSG,nAlignment) \
    _Helper_DisplayPinText(nEraseDisplay,nLineNumber,ptrMSG,nAlignment,SHORTLINE)



//! \brief This function displays a text on the PinPad or terminal used to input Pin.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,

#define Helper_DisplayPinTextLong(nEraseDisplay,nLineNumber,ptrMSG,nAlignment) \
    _Helper_DisplayPinText(nEraseDisplay,nLineNumber,ptrMSG,nAlignment,LONGLINE)



//! \brief Display transaction result on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] bLongLine LONG if long line must be displayed.

void _Helper_DisplayTextMerchant (int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, unsigned char bLongLine);



//! \brief Display message on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \return nothing.

#define Helper_DisplayTextMerchant(nEraseDisplay,nLineNumber,ptrMSG) \
    _Helper_DisplayTextMerchant(nEraseDisplay,nLineNumber,ptrMSG,SHORTLINE)



//! \brief Display message on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.

#define Helper_DisplayTextMerchantLong(nEraseDisplay,nLineNumber,ptrMSG) \
    _Helper_DisplayTextMerchant(nEraseDisplay,nLineNumber,ptrMSG,LONGLINE)



//! \brief This function displays a text on the terminal screen.
//! \param[in] nNum = message number.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,

void Helper_DisplayMessage(int nNum, int nEraseDisplay, int nLineNumber);



//! \brief Wait allowing user to see screen message.

void Helper_WaitUserDisplay(void);



//! \brief This function ask a question to the user.
//! \param[in] pMsg User question informations ("Signature OK ?" for example).
//! \param[in] nTimeout Tiemout (in seconds) for user answer (if no answer, default return if \a FALSE).
//! \return
//!		- \a TRUE if user selected "YES".
//!		- \a FALSE if not.

int HelperQuestionYesNo (MSGinfos * pMsg, int nTimeout);



//! \brief This function refresh the screen (for WGUI only) and waits for message reading if required.
//! \param[in] bWait \a TRUE if need to wait to read message, \a FALSE if not.

void Helper_RefreshScreen (const unsigned int bWait);



///////////////////////
// Specific Visa IHM //
///////////////////////

//! \brief Perform the signature CVM IHM.

void Helper_Visa_SignatureCVMIHM(void);



//! \brief Perform the IHM for an approved transaction (either offline or online).
//! \param[in] nOfflineOnline : OFFLINE or ONLINE transaction

void Helper_Visa_ApprovedIHM(const int nOfflineOnline);



//! \brief Perform the IHM when the Signature CVM is OK.

void Helper_Visa_SignatureOKIHM(void);



//! \brief Perform the IHM when the Signature CVM is KO.

void Helper_Visa_SignatureKOIHM(void);



//! \brief Perform the IHM when the PIN Entry CVM is KO.

void Helper_Visa_PinEntryKOIHM(const int bPINCanceled);



//! \brief Perform the IHM for a declined transaction (either offline or online).
//! \param[in] nOfflineOnline : OFFLINE or ONLINE transaction

void Helper_Visa_DeclinedIHM(const int nOfflineOnline);



//! \brief Perform the IHM for Online Processing.

void Helper_Visa_OnlineProcessingIHM(void);



//! \brief Perform the IHM for transaction that was terminated.

void Helper_Visa_ErrorIHM(void);
