//! \file
//! Module that mprovides functions to help developer to make easily user interfaces.

#ifndef __UIHELPERS_H__INCLUDED__
#define __UIHELPERS_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

// Allows to trace some or all output informations 
#define C_INFORMATION_RESULT		1
#define C_INFORMATION_ALL			2

#define ERASE						TRUE
#define NO_ERASE					FALSE

#define WAIT						TRUE
#define NOWAIT						FALSE

#define LEDSOFF						TRUE
#define NOLEDSOFF					FALSE

#define WITHBEEP					TRUE
#define WITHOUTBEEP					FALSE

#define HELPERS_MERCHANT_SCREEN		TRUE
#define HELPERS_CUSTOMER_SCREEN		FALSE
// Output display alignment
#define CLESSSAMPLE_ALIGN_LEFT				(1)
#define CLESSSAMPLE_ALIGN_CENTER			(2)
#define CLESSSAMPLE_ALIGN_RIGHT				(3)

#define HELPERS_FONT_SIZE_DEFAULT	0
#define HELPERS_FONT_SIZE_LARGE		1
#define HELPERS_FONT_SIZE_MEDIUM	2
#define HELPERS_FONT_SIZE_SMALL		3

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

// Time on and time off for blinking leds
#define VISA_ASIA_LED_BLINK_ON					(17)			/*!< 340 ms. */
#define VISA_ASIA_LED_BLINK_OFF					(17)			/*!< 340 ms. */

// Indicates if it is a payWave or a VisaWave transaction
#define HELPERS_PAYWAVE						1
#define HELPERS_VISAWAVE					2

// Indicates if it is an offline or an online transaction
#define OFFLINE								1
#define ONLINE								2

#define WITH_AOSA							1
#define WITHOUT_AOSA						0

#define WITH_SIGNATURE						1
#define WITHOUT_SIGNATURE					0

#define APPROVED_TICKED 					1
#define DECLINED_TICKED 					0

#define C_DEFAULT_BEEP_VOLUME			    (255)
#define C_DEFAULT_BEEP_DELAY			    (50)

#define C_DEFAULT_BEEP_OK_FREQUENCY		    (1500)
#define C_DEFAULT_BEEP_ERROR_FREQUENCY	    (750)
#define C_DEFAULT_BEEP_OK_DELAY			    (50)
#define C_DEFAULT_BEEP_ERROR_DELAY		    (20)

#define C_TIME_1S						    100
#define C_TIME_100MS            10


//// Types //////////////////////////////////////////////////////

#define MAX_ICON_NAME_LEN			(32)		/*!< Maximum length of the icon name. */

typedef struct
{
	int nMessageId;
	const char * sIconName;
} T_CLESS_SAMPLE_HELPER_MENU_ITEM;
//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

//! \brief This function displays a text on the cless reader
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned.
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
//! \param[in] ucLongLine LONGLINE for long line to display.
//! \param[in] nFontSize Possibility to indicate the font size to use.
void _Helper_DisplayTextCustomer(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, int nAlignment, unsigned char bLedsOff, unsigned char ucLongLine, int nFontSize);

//! \brief This function displays a text on the cless reader
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bUseP30 = indicates if a P30 is used or not.
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
#define Helper_DisplayTextCustomer(nEraseDisplay,nLineNumber,ptrMSG,nAlignment, bLedsOff) \
	_Helper_DisplayTextCustomer(nEraseDisplay,nLineNumber,ptrMSG,nAlignment,bLedsOff,SHORTLINE,HELPERS_FONT_SIZE_DEFAULT)

//! \brief This function displays a text on the cless reader
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bUseP30 = indicates if a P30 is used or not.
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
#define Helper_DisplayTextCustomerLong(nEraseDisplay,nLineNumber,ptrMSG,nAlignment,bLedsOff) \
    _Helper_DisplayTextCustomer(nEraseDisplay,nLineNumber,ptrMSG,nAlignment,bLedsOff,LONGLINE,HELPERS_FONT_SIZE_DEFAULT)

//! \brief This function displays a text on the PinPad or terminal used to input Pin.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bUseP30 = indicates if a P30 is used or not.
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
//! \param[in] bLongLine LONG if long line must be displayed.
void _Helper_DisplayPinText(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, int nAlignment, unsigned char bLedsOff, unsigned char bLongLine);

//! \brief This function displays a text on the PinPad or terminal used to input Pin.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bUseP30 = indicates if a P30 is used or not.
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
#define Helper_DisplayPinText(nEraseDisplay,nLineNumber,ptrMSG,nAlignment,bLedsOff) \
    _Helper_DisplayPinText(nEraseDisplay,nLineNumber,ptrMSG,nAlignment,bLedsOff,SHORTLINE)

//! \brief This function displays a text on the PinPad or terminal used to input Pin.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] nAlignment = centered, left or right aligned,
//! \param[in] bUseP30 = indicates if a P30 is used or not.
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
#define Helper_DisplayPinTextLong(nEraseDisplay,nLineNumber,ptrMSG,nAlignment,bLedsOff) \
    _Helper_DisplayPinText(nEraseDisplay,nLineNumber,ptrMSG,nAlignment,bLedsOff,LONGLINE)

//! \brief Display a message on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] bLongLine LONG if long line must be displayed.
//! \param[in] nFontSize Possibility to indicate the desired font size.
//! \return nothing.
void _HelperDisplayMessageOnTerminal(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, unsigned char bLongLine, int nFontSize);

//! \brief Display a message on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \return nothing.
#define HelperDisplayMessageOnTerminal(nEraseDisplay,nLineNumber,ptrMSG) \
	_HelperDisplayMessageOnTerminal(nEraseDisplay,nLineNumber,ptrMSG,SHORTLINE,HELPERS_FONT_SIZE_DEFAULT)

//! \brief Display a message on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \return nothing.
#define HelperDisplayMessageOnTerminalLong(nEraseDisplay,nLineNumber,ptrMSG) \
    _HelperDisplayMessageOnTerminal(nEraseDisplay,nLineNumber,ptrMSG,LONGLINE,HELPERS_FONT_SIZE_DEFAULT)

//! \brief Display transaction result on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
//! \param[in] bLongLine LONG if long line must be displayed.
//! \param[in] nFontSize Possibility to indicate the font size.
//! \return nothing.
void _Helper_DisplayTextMerchant (int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, unsigned char bLedsOff, unsigned char bLongLine, int nFontSize);

//! \brief Display message on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
//! \return nothing.
#define Helper_DisplayTextMerchant(nEraseDisplay,nLineNumber,ptrMSG,bLedsOff) \
    _Helper_DisplayTextMerchant(nEraseDisplay,nLineNumber,ptrMSG,bLedsOff,SHORTLINE,HELPERS_FONT_SIZE_DEFAULT)
	
//! \brief Display message on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
//! \return nothing.
#define Helper_DisplayTextMerchantLong(nEraseDisplay,nLineNumber,ptrMSG,bLedsOff) \
    _Helper_DisplayTextMerchant(nEraseDisplay,nLineNumber,ptrMSG,bLedsOff,LONGLINE,HELPERS_FONT_SIZE_DEFAULT)
	
//! \brief This function specify if a specific Display is available for the customer.
//! \return TRUE if a specific display is available for customer.
//!        	FALSE else.
int Helper_IsClessCustomerDisplayAvailable(void);

//! \brief Create a menu.
//! \param[in] szTitle .
//! \param[in] nDefaultChoice .
//! \param[in] nItems .
//! \param[in] Items .
//! \return 0 if input ok, error code else.
int HelperDisplayMenu(const char* szTitle, int nDefaultChoice, int nItems, const T_CLESS_SAMPLE_HELPER_MENU_ITEM Items[]);

//! \brief Create a choice menu (with radio buttons).
//! \param[in] szTitle .
//! \param[in] nDefaultChoice .
//! \param[in] nItems .
//! \param[in] Items .
//! \return 0 if input ok, error code else.
int HelperDisplayChoices(const char* szTitle, int nDefaultChoice, int nItems, const T_CLESS_SAMPLE_HELPER_MENU_ITEM Items[]);

//! \brief Graphical interface allowing to input a numerical entry.
//! \param[in] szTitle .
//! \param[in] szLabel .
//! \param[in] nMinLength .
//! \param[in] nMaxLength .
//! \param[in] szDefault.
//! \param[in] szInput.
//! \return 0 if input ok, error code else.
int HelperNumericInput(const char* szTitle, const char* szLabel, int nMinLength, int nMaxLength, const char* szDefault, char* szInput);

//! \brief Graphical interface allowing to input a alpha_numerical entry.
//! \param[in] szTitle .
//! \param[in] szLabel .
//! \param[in] nMinLength .
//! \param[in] nMaxLength .
//! \param[in] szDefault.
//! \param[in] szAllowedChars.
//! \param[in] szInput.
//! \return 0 if input ok, error code else.
int HelperAlphanumericInput(const char* szTitle, const char* szLabel, int nMinLength, int nMaxLength, const char* szDefault, const char* szAllowedChars, char* szInput);

//! \brief Trace tags from a Share Buffer.
//! \param[in] share buffer with tags to trace.
//! \param[in] information type as C_INFORMATION_RESULT=>only results are traces, C_INFORMATION_ALL=> all tags are traced.
//! \return STATUS_SHARED_EXCHANGE_END if no problem, other else.
int HelperDisplayOutputTags(T_SHARED_DATA_STRUCT * pStruct, int nInformationType);

//! \brief Process the deactivation sequence (buzzer 1500Hz, Leds in order) and displays the correct message.
//! \param[in] pSharedData Data structure containing the customisation data (step ID, and prefered selected language if present).
//! \return nothing.
void HelperRemoveCardSequence (T_SHARED_DATA_STRUCT * pSharedData);

//! \brief Process the deactivation sequence (buzzer 1500Hz, Leds in order) and displays the correct message.
//! \param[in] pSharedData Data structure containing the customisation data (step ID, and prefered selected language if present).
//! \return nothing.
void HelperRemoveCardSequenceTwoLines (T_SHARED_DATA_STRUCT * pSharedData);

//! \brief Process the represent card sequence.
//! \param[in] pSharedData Data structure containing the customisation data (prefered selected language if present).
//! \return nothing.
void HelperRepresentCardSequence (T_SHARED_DATA_STRUCT * pSharedData);

//! \brief Process the deactivation sequence (buzzer 1500Hz, Leds in order).
//! \param[in] nWithBeep = TRUE if Beep and delay must be made,
//! \return nothing.
void HelperErrorSequence(int nWithBeep);

//! \brief Display transaction result on the terminal display.
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display,
//! \param[in] ptrMSG : informations on text to display.
//! \param[in] bWait Wait 2 seconds before giving back hand.
//! \param[in] bLedsOff Indicates if LEDs have to be turned off or not.
//! \return nothing.
void Helper_DisplayTransactionResult(int nEraseDisplay, int nLineNumber, MSGinfos * ptrMSG, unsigned char bWait, unsigned char bLedsOff);

//! \brief Wait allowing user to see srceen message.
//! \return nothing.
void Helper_WaitUserDisplay(void);

//! \brief Wait just 600ms allowing user to see screen message.
//! \return nothing.
void Helper_QuickWaitUserDisplay(void);

//! \brief This function wait 750ms to see LEDS.
//! \return nothing.
void HelperWaitLedsTime(void);

//! \brief Wait 750ms and set LEDS off.
//! \return nothing.
void HelperLedsOff(void);

//! \brief This function set the LEDs into the idle state (first LED blinking 250ms every 5 seconds).
//! \return nothing.
void HelperLedsIdleState(void);

//! \brief This function set the LEDs into the idle state (first LED blinking 250ms every 5 seconds).
//! \param[in] pMsg User question informations ("Signature OK ?" for example).
//! \param[in] nTimeout Tiemout (in seconds) for user answer (if no answer, default return if \a FALSE).
//! \param[in] nMerchantLanguage Indicates the merchant language to be used.
//! \return
//!		- \a TRUE if user selected "YES".
//!		- \a FALSE if not.

int HelperQuestionYesNo (MSGinfos * pMsg, int nTimeout, int nMerchantLanguage);

//! \brief This function refresh the screen (for WGUI only) and waits for message reading if required.
//! \param[in] bWait \a TRUE if need to wait to read message, \a FALSE if not.
//! \param[in] bMerchantDisplay Indicates if this is the merchant display that should be refreshed or not. If \a TRUE, it means it is always refresh, if \a FALSE, the screen is refreshed using CGUI only if the customer screen is the internal terminal screen.

void Helper_RefreshScreen (const unsigned int bWait, const int bMerchantDisplay);


//! \brief This function displays a text on the cless reader
//! \param[in] nEraseDisplay = TRUE if screen must be erased,
//! \param[in] nLineNumber = display line to display.
//! \return Nothing.

void Helper_DisplayBlankLineCustomer(int nEraseDisplay, int nLineNumber);


//! \brief This function set the LEDs into the idle state (first LED blinking 250ms every 5 seconds).
//! \param[in] pMsg User question informations ("Signature OK ?" for example).
//! \param[in] nTimeout Tiemout (in seconds) for user answer (if no answer, default return if \a FALSE).
//! \param[in] nMerchantLanguage Indicates the merchant language to be used.
//! \return
//!		- \a TRUE if user selected "YES".
//!		- \a FALSE if not.

int HelperSignatureCapture (MSGinfos * pMsg, int nMerchantLanguage);


//! \brief Third light is on and beep beep sound.

void Helper_PerformOKSequence (void);


//! \brief Fourth light blinking and beep beep sound.

void Helper_PerformKOSequence (void);


//! \brief Third light blinking and beep sound.

void Helper_PerformOfflineSequence (void);


//! \brief Third light blinking.

void Helper_PerformOnlineSequence (void);


//! \brief Third light blinking and beep sound.

void Helper_PerformCVMSequence (void);


//! \brief Perform the signature CVM IHM.

void Helper_Visa_SignatureCVMIHM(const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang);


//! \brief Perform the IHM for an approved transaction (either offline or online).
//! \param[in] nVisa : Indicates if it is a payWave or a VisaWave transaction.
//! \param[in] nOfflineOnline : OFFLINE or ONLINE transaction
//! \param[in] nAOSA : with Available Offline Spending Amount : WITH_AOSA or WITHOUT_AOSA
void Helper_Visa_ApprovedIHM(const int nVisa, const int nOfflineOnline, T_SHARED_DATA_STRUCT * pDataStruct, const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang, const int nAOSA);


//! \brief Perform the IHM when the Signature CVM is OK.
//! \param[in] nVisa : Indicates if it is a payWave or a VisaWave transaction.

void Helper_Visa_SignatureOKIHM(const int nVisa, T_SHARED_DATA_STRUCT * pDataStruct, const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang);


//! \brief Perform the IHM when the Signature CVM is KO.
//! \param[in] nVisa : Indicates if it is a payWave or a VisaWave transaction.

void Helper_Visa_SignatureKOIHM(const int nVisa, T_SHARED_DATA_STRUCT * pDataStruct, const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang);


//! \brief Perform the IHM when the PIN Entry CVM is KO.

void Helper_Visa_PinEntryKOIHM(const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang);


//! \brief Perform the IHM for a declined transaction (either offline or online).
//! \param[in] nVisa : Indicates if it is a payWave or a VisaWave transaction.
//! \param[in] nOfflineOnline : OFFLINE or ONLINE transaction

void Helper_Visa_DeclinedIHM(const int nVisa, const int nOfflineOnline, T_SHARED_DATA_STRUCT * pDataStruct, const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang);


//! \brief Perform the IHM for Online Processing.
//! \param[in] nVisa : Indicates if it is a payWave or a VisaWave transaction.

void Helper_Visa_OnlineProcessingIHM(int nVisa, T_SHARED_DATA_STRUCT * pDataStruct, const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang);


//! \brief Perform the IHM for Transaction that was Terminated.

void Helper_Visa_ErrorIHM(const unsigned char ucCustomerDisplayAvailable, const int nMerchantLang, const int nCardHolderLang);


//! \brief Display Available amount (if available) on customer display if available or on Merchant display else.
//! \param[in] nVisa Indicates if it is a payWave or a VisaWave transaction.
//! \param[in] pDataStruct share buffer with tags informations.
//! \param[in] nCardHolderLang lang to use for the customer. 

void Helper_Visa_DisplayAvailableAmount(int nVisa, T_SHARED_DATA_STRUCT * pDataStruct, int nCardHolderLang);

void HelperCardWait(void);

//! \brief Clear the screen.
void UIH_ClearScreen(void);


//! \brief Launch the task that manages the remove card sequence (PayPass specific needs).
//! \return OK if task correctly launched, KO else.
int UIH_RemoveCardTask_Launch (void);


//! \brief Indicates if the remove card task is running or not.
//! \return
//!	- \a TRUE if the task is running.
//!	- \a FALSE if not.
int UIH_IsRemoveCardTaskRunning (void);


//! \brief Wait the end of the Remove Card task.
void UIH_RemoveCardTask_WaitEnd (void);


#endif //__UIHELPERS_H__INCLUDED__
