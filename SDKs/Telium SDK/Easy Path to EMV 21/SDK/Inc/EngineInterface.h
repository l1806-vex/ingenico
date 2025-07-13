/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//! \addtogroup EngineErrors
//! \{

#define ERR_ENG_OK										(0)		//!< The operation is successful.
#define ERR_ENG_UNKNOWN									(1)		//!< An unexpected error occurred.
#define ERR_ENG_INVALID_PARAMETERS						(2)		//!< An invalid parameter is given.
#define ERR_ENG_OUTPUT_BUFFER_TOO_SMALL					(3)		//!< The output buffer is too small.
#define ERR_ENG_EMVDC_ERROR								(4)		//!< Error while communicating with EMV DC.
#define ERR_ENG_CANCEL									(5)		//!< A cancel event occurred.
#define ERR_ENG_TIMEOUT									(6)		//!< A timeout occurred.
#define ERR_ENG_NOT_ENOUGH_MEMORY						(7)		//!< There is not enough memory.
#define ERR_ENG_NOT_ALLOWED								(8)		//!< The operation is not allowed.
#define ERR_ENG_TRY_ANOTHER_AID							(9)		//!< The application should try another AID.
#define ERR_ENG_UNKNOWN_SERVICE							(10)	//!< The service is unknown.
#define ERR_ENG_ENGINE_ERROR							(11)	//!< Error while communicating with EMV ENGINE.
#define ERR_ENG_SUSPEND									(12)	//!< The application has suspended the transaction.

//! \}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//! \addtogroup EngineCommStatus
//! \{

#define ENG_COMM_STATUS_NOK								(0)		//!< The communication with the host has failed. See \ref TAG_CUST_IS_COMMUNICATION_OK.
#define ENG_COMM_STATUS_OK								(1)		//!< The communication with the host was successful. See \ref TAG_CUST_IS_COMMUNICATION_OK.
#define ENG_COMM_STATUS_CANCEL							(2)		//!< The communication with the host has been cancelled. See \ref TAG_CUST_IS_COMMUNICATION_OK.

//! \}

//! \addtogroup EngineAuthorisationResult
//! \{

#define TAG_AUTHORISATION_RESULT_DECLINED				(0)		//!< The host declines the transaction. See \ref TAG_AUTHORISATION_RESULT.
#define TAG_AUTHORISATION_RESULT_APPROVED				(1)		//!< The host approves the transaction. See \ref TAG_AUTHORISATION_RESULT.
#define TAG_AUTHORISATION_RESULT_REFERRAL				(2)		//!< The host requests a referral. See \ref TAG_AUTHORISATION_RESULT.
#define TAG_AUTHORISATION_RESULT_ERROR					(3)		//!< The host has sent an invalid authorisation result. See \ref TAG_AUTHORISATION_RESULT.

//! \}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

//! \addtogroup EngineTags
//! \{

#define TAG_ENG_WAIT_CARD_TIMEOUT						0x9f8730	//!< \details Maximum card waiting time in tenth of milliseconds (ex: 100 means 1 second). This tag has no effect if \ref TAG_ENG_APPLI_SEL_ALREADY_DONE is non-zero.<br>- Format : b (little endian)<br>- Length : 4 bytes<br>- Source : Terminal
#define TAG_ENG_WAIT_CARD_CANCEL_EVENTS					0x9f8731	//!< \details Events that can interrupt the card detection (user event, keyboard event, ...). This tag has no effect if \ref TAG_ENG_APPLI_SEL_ALREADY_DONE is non-zero.<br>- Format : b (little endian).<br>- Length : 4 bytes.<br>- Source : Terminal.
#define TAG_ENG_REMOVE_CARD_TIMEOUT						0x9f8732	//!< \details Maximum card removal time in tenth of milliseconds (ex: 100 means 1 second). This tag has no effect if \ref TAG_ENG_APPLI_SEL_ALREADY_DONE is non-zero.<br>- Format : b (little endian)<br>- Length : 4 bytes<br>- Source : Terminal
#define TAG_ENG_REMOVE_CARD_CANCEL_EVENTS				0x9f8733	//!< \details Events that can interrupt the card removal detection (user event, keyboard event, ...). This tag has no effect if \ref TAG_ENG_APPLI_SEL_ALREADY_DONE is non-zero.<br>- Format : b (little endian).<br>- Length : 4 bytes.<br>- Source : Terminal.
#define TAG_ENG_CUSTOM_APPLI_TYPE						0x9f8734	//!< \details Application Type of the CUSTOM application. If the tag is not given by the application, the historical application type 0x0051 is used.<br>- Format : b (big endian).<br>- Length : 2 bytes.<br>- Source : Terminal.
#define TAG_ENG_APPLI_SEL_ALREADY_DONE					0x9f8735	//!< \details Non-zero if the application selection has already been performed by the Telium Manager, zero if not.<br>- Format : b<br>- Length : 1 byte<br>- Source : Terminal
#define TAG_ENG_WAIT_CHIP_READERS						0x9f8736	//!< \details It is a bitfield with the possible values CAM0 and CAM2. For example, it can be used to allow or not the terminal reader when a pinpad is connected. This tag has no effect if \ref TAG_ENG_APPLI_SEL_ALREADY_DONE is non-zero.<br>- Format : b (little endian)<br>- Length : 4 bytes<br>- Source : Terminal
#define TAG_ENG_REMOVE_CHIP_READERS						0x9f8737	//!< \details It is a bitfield with the possible values CAM0 and CAM2. For example, it can be used to force removal of all the cards (CAM0 | CAM2) even if only CAM0 is allowed to perform a transaction. This tag has no effect if \ref TAG_ENG_APPLI_SEL_ALREADY_DONE is non-zero.<br>- Format : b (little endian)<br>- Length : 4 bytes<br>- Source : Terminal

//! \}

//// Types //////////////////////////////////////////////////////

//// Static function definitions ////////////////////////////////

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////
