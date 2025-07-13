#ifdef __cplusplus
extern "C" {
#endif

#include "AVL_deprecated.h"

/*! @addtogroup VGE_UIM
	* @{
	* @deprecated	UIM is deprecated since SDK 9.2. It was based on Black and White functions. To implement MMI, lease use advanced graphical library GOAL or legacy libgr graphical mode.
**/

#if defined (__GNUC__) || defined(_DEPRECATED_SDK920_AVL_)


/*
======================================================================
					List of Defines
======================================================================
*/
#define UIM_SUCCESS					      35     /*!< The UIM service is successful		*/
#define UIM_INVALID_PARAMETER		  36     /*!< One of the input parameters is NULL	*/
#define UIM_CANCEL_PRESSED			  37     /*!< Red button is pressed by the user	*/
#define UIM_ERROR					        38     /*!< Error */
#define UIM_INVALIDE_IP_ADRESS		39     /*!< The input or the entered IP address is invalid		*/
#define UIM_INVALIDE_SEPARATOR		40     /*!< The input separator is invalid	*/
#define UIM_INVALIDE_FORMAT			  41     /*!< The date/time format are invalid		*/
#define UIM_INVALIDE_TIME			    42     /*!< The input time or the entered time are invalid	*/
#define UIM_INVALIDE_DATE			    43     /*!< The input date or the entered date are invalid		*/
#define UIM_INPUT_PAN_ERROR			  44     /*!< The PAN entry is invalid			*/
#define UIM_INPUT_EXPDATE_ERROR		45     /*!< The Expiration date entry is invalid	*/
#define UIM_INPUT_CVV2_ERROR		  46     /*!< The CVV2 entry is invalid		*/
#define UIM_INPUT_NUM_ERROR			  47     /*!< The numerical entry is invalid			*/
#define UIM_INPUT_ALPHA_NUM_ERROR	48     /*!< The alpha numerical entry is invalid		*/
#define UIM_TIME_OUT				      49     /*!< Timeout																			*/															
#define UIM_CANCEL_INPUT		    	50     /*!< Red button is pressed by the user	*/
#define UIM_CODE_LUHN_ERROR			  51     /*!< The Luhn code is wrong	*/
#define UIM_FONT_FILE_NOT_FOUND		52     /*!< The Iso8859 font file was not found	*/
#define UIM_UNKNOWN_FONT_MODE		  53     /*!< The input font mode is unknown	*/
#define UIM_NORMAL_MODE		        0      /*!< Normal font mode */
#define UIM_UNICODE_MODE	        1      /*!< unicode font mode */
#define UIM_ISO8859_MODE          2      /*!< Iso8859 font mode */

#define UIM_BACK_TO_LAST_MENU		  1      /*!< Action to do after timeout is to go back to last menu */
#define UIM_DISPLAY_MESSAGE			  2      /*!< Action to do after timeout is to display message */
#define UIM_GO_OUT					      3      /*!< Action to do after timeout is to go */

#define UIM_CONTINUE_AFTER_FCT		1      /*!< Action to do after the execution of the function is to continue */
#define UIM_EXIT_AFTER_FCT			  2      /*!< Action to do after the execution of the function is to exit */

#define SECURITY_LOW_LEVEL			  1      /*!< Low level security */
#define SECURITY_MEDIUM_LEVEL		  2      /*!< high level security */

#define NORMAL_MODE					      1      /*!< Non graphic mode */
#define GRAPHIC_MODE			      	2      /*!< Graphic mode */

#define WRITE_MODE				     	"w"      /*!< Write mode */
#define APPEND_MODE				     	"a"      /*!< Append mode */

#define MAX_LENGTH_HEADER			    24 *2  /*!< Multiplied by 2 to enable unicode message  */
#define MAX_LENGTH_FOOTER			    10 *2  /*!< Multiplied by 2 to enable unicode message  */
#define MAX_LENGTH_LINE				    24 *2  /*!< Multiplied by 2 to enable unicode message  */
#define MAX_LENGTH_BMP				    256    /*!< Maximum length of the BMP */

#define ALPHA_NUMERICAL				    0      /*!< Alpha numerical caracter */
#define NUMERICAL					        1      /*!< Numerical caracter */

#define LEFT						          1      /*!< Aligned to the left */
#define RIGHT						          2      /*!< Aligned to the right */
#define CENTER						        3      /*!< Aligned to the center */


 
/*
======================================================================
			Data Structures Definition
======================================================================
*/


/*! @deprecated Navigation menu structure. */
typedef struct
{
	char * pcItemLabel;			/*!< Item label			*/
	char * pcShortCommand;	/*!< Short command	*/
	char cLevel;				    /*!< Level of item	*/
	PFONCNAVI sFunction;		/*!< Function to execute when the user select an item	*/	
} UIM_t_navigate_menu;


/*! @deprecated Navigation option structure. */
typedef struct
{
	int iTimeOut;					/*!< Time to wait when there is no action		*/
	int iOffset;					/*!< Selected item		*/
	int bRadioButtons;	  /*!< Radio buttons or menu
											- 0 --> menu
											- 1 --> radio buttons		*/
	char cActionTodoAfterTimeOut;	/*!< Action to do after timeout
											- UIM_BACK_TO_LAST_MENU
											- UIM_DISPLAY_MESSAGE
											- UIM_GO_OUT		*/

	int iDefaultChoice;				/*!< Default choice		*/
	char *pcMessage;			  	/*!< Message to display after time out			*/
	char cActionAfterFct;			/*!< Action to do after the execution of the function	
											- UIM_CONTINUE_AFTER_FCT
											- UIM_EXIT_AFTER_FCT		*/
} UIM_t_navigate_option;

/*! @deprecated Date format. */
typedef enum
{
	UIMMonthDayYear,	/*!<  MM/DD/YYYY	*/
	UIMDayMonthYear,	/*!<  DD/MM/YYYY	*/
	UIMYearMonthDay,	/*!<  YYYY/MM/DD	*/
	UIMDayYear,			  /*!<  DD/MM/YY		*/
	UIMMonthYear,		  /*!<  MM/YY			*/
	UIMMonthDay	,		  /*!<  MM/DD			*/
	UIMDayMonth			  /*!<  DD/MM			*/
} UIM_e_date_format;

/*! @deprecated Time format. */
typedef enum
{
	UIMHourMinuteSecond, /*!<  HH :MM :SS */
	UIMHourMinute,       /*!<  HH :MM */
	UIMMinuteSecond      /*!<  MM :SS */
} UIM_e_time_format;


/*! @deprecated PAN entry option structure. */
typedef struct
{
	TAB_ENTRY_STRING sPanEntryOption;	/*!< PAN entry option					*/
	char * pcTitle;										/*!< Title of the entry window	*/

	char * pcName;										/*!< The label.											*/
	int iNbTry;						  					/*!< The maximum try number								*/
	char* pcErrMsg;										/*!< The error message to display in case of TimeOut	*/
	int iTimeOutDispErrMsg; 					/*!< The error message timout of display				*/
	int bCheckLuHnCode;								/*!< Do the LuHn code checking :
																		- @c TRUE	-->	Do the check.
																		- @c FALSE	-->	Don't do the check.	*/
} UIM_t_pan_option;


/*! @deprecated Expiration date entry option structure. */
typedef struct
{
	TAB_ENTRY_STRING sExpDateEntryOption;	/*!< Expiration Date entry option	*/
	char * pcTitle;												/*!< Title of the input window							*/
	char * pcName;												/*!< The label											*/
	int iNbTry;								 						/*!< The maximum try number								*/
	char* pcErrMsg;												/*!< The error message to display in case of TimeOut	*/
	int iTimeOutDispErrMsg;								/*!< The error message TimeOut of display				*/
} UIM_t_exp_date_option;


/*! @deprecated CVV2 entry option structure. */
typedef struct
{
	TAB_ENTRY_STRING sCVV2EntryOption;	/*!< CVV2 entry option			*/
	char * pcTitle;											/*!< Title of the entry window			*/
	char * pcName;											/*!< The label											*/
	int iNbTry;							 						/*!< The maximum try number								*/
	char* pcErrMsg;											/*!< The error message to display in case of TimeOut	*/
	int iTimeOutDispErrMsg;							/*!< The error message TimeOut of display				*/
} UIM_t_cvv2_option;


/*! @deprecated Numerical entry option structure. */
typedef struct
{
	TAB_ENTRY_STRING sNumericEntryOption;	/*!< Numerical entry option		*/
	char * pcTitle;												/*!< Title of  the entry window			*/
	
	char * pcName;												/*!< The label											*/
	int iNbTry;								  					/*!< The maximum try number								*/
	char* pcErrMsg;												/*!< The error message to display in case of TimeOut	*/
	int iTimeOutDispErrMsg;								/*!< The error message TimeOut of display				*/
	char cSecurityLevel ;									/*!< Security level
																				- SECURITY_LOW_LEVEL	
																				- SECURITY_MEDIUM_LEVEL	*/
} UIM_t_numeric_option;


/*! @deprecated Alpha numerical entry option structure. */
typedef struct
{
	TAB_ENTRY_STRING sAlphaNumEntryOption;	/*!< Alpha Numeric entry option	*/
	char * pcTitle;													/*!< Title of the entry window			*/
	
	char * pcName;						  						/*!< The label											*/
	int iNbTry;							  							/*!< The maximum try number								*/
	char* pcErrMsg;													/*!< The error message to display in case of TimeOut	*/
	int iTimeOutDispErrMsg;									/*!< The error message TimeOut of display				*/
	char cSecurityLevel ;										/*!< Security level
																					- SECURITY_LOW_LEVEL	
																					- SECURITY_MEDIUM_LEVEL	*/
} UIM_t_alpha_num_option;


/*! @deprecated Graphic mode option structure. */
typedef struct
{
	int iPosX ;				/*!< Vertical position in pixels				*/
	int iPosY ;				/*!< Horizontal position in pixels				*/
	int iReversal ;		/*!< Reversal : _ON_ / _OFF_					*/
	int iPolice ;			/*!< Font type _PROPORTIONNEL_ or _NORMALE_		*/
	int iSize ;				/*!< Font size _SMALL_, _MEDIUM_ or _LARGE_		*/
} UIM_t_graphic_mode;


/*! @deprecated Normal mode option structure. */
typedef struct
{
	int iLine ;				/*!< Line			*/
	int iColumn ;			/*!< Column			*/
} UIM_t_normal_mode ;


/*! @deprecated Message option structure. */
typedef struct
{
	char* pcMessage ;			/*!< Message to display				*/		
	char* pcMode ;				/*!< WRITE_MODE or APPEND_MODE						*/
	int iTimeOut ;				/*!< Time to display the message	*/
	char cDisplay ;				/*!< Display mode
										- NORMAL_MODE	
										- GRAPHIC_MODE				*/
	union
	{
		UIM_t_graphic_mode sGraphicMode;
		UIM_t_normal_mode sNormalMode;
	} UIM_u_info_draw;			/*!< A union between the Graphic mode description
													and the Normal mode description				 */

} UIM_t_message_option;


/*! @deprecated Screen structure. */
typedef struct
{
	char	acHeader[MAX_LENGTH_HEADER];		/*!< Header of screen									*/
	char	acLine1[MAX_LENGTH_LINE];				/*!< Message to display in the line 1 (y==20)			*/
	char	acLine2[MAX_LENGTH_LINE];				/*!< Message to display in the line 2 (y==30)			*/
	char	acLine3[MAX_LENGTH_LINE];				/*!< Message to display in the line 3 (y==40)			*/
	char	acLine4[MAX_LENGTH_LINE];				/*!< Message to display in the line 4 (y==50)			*/
	char	acLine5[MAX_LENGTH_LINE];				/*!< Message to display in the line 5 (y==60)			*/
	char	cDisplayFooter;							    /*!< Footer status 
															- TRUE  --> display the footer.
															- FALSE --> don't display the footer.			*/
	char	acFooterRight[MAX_LENGTH_FOOTER];		/*!< Message to display in the right footer				*/
	char	acFooterLeft[MAX_LENGTH_FOOTER];		/*!< Message to display in the left footer 				*/
	char	acBmp[MAX_LENGTH_BMP];							/*!< Bitmap to display at the right side of the screen	*/
} UIM_t_screen;


/*! @deprecated Input entry option structure. */
typedef struct
{
	int iTimeOut ;			/*!<  Timeout in seconds															*/
	int iLine ;			  	/*!<  Vertical position in pixels													*/
	int iColomne ;			/*!<  Horizontal position in pixels													*/
	char cEcho ;		  	/*!<  Echo type : Normal (@c ECHO_NORMAL), Secret (@c ECHO_SPECIAL) or No echo (@c NO_ECHO)	*/
	int iMaxInput ;			/*!<  Maximum number of keys														*/
	int iMinInput ;			/*!<  Minimum number of keys														*/
	char cInputType ;		/*!<  NUMERICAL or ALPHA_NUMERICAL									*/		
} UIM_t_input;

/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @deprecated	This function is used to create and manage overlapping menus.

 *	@param[in]		i_pxNavigateMenu		Navigation menu items.
 *	@param[in]		i_nNbItmes				Number of items.
 *	@param[in]		i_pxNavigateOption		Navigation option.
 *	@return
 *	- #UIM_SUCCESS			
 *	- #UIM_CANCEL_PRESSED		
 *	- #UIM_TIME_OUT			
 *	- #UIM_INVALID_PARAMETER  
 *
 *	@note
 *
 *	@a bRadioButtons can be set to :
 *	- @c 0 : Menu
 *	- @c 1 : radio buttons
 *
 *	@a cActionTodoAfterTimeOut can be set to :
 *	- #UIM_BACK_TO_LAST_MENU,
 *	- #UIM_DISPLAY_MESSAGE or
 *	- #UIM_GO_OUT.
 *
 *	@a cActionAfterFct can be set to :
 *	- #UIM_CONTINUE_AFTER_FCT or
 *	- #UIM_EXIT_AFTER_FCT
 *
 *
 *	@sa 
 *	- @link UIM_t_navigate_option Navigate option structure@endlink
 *	- @link UIM_t_navigate_menu Navigate menu structure@endlink
 *
 * @link VGE_UIM Back to top @endlink
**/

int UIM_NavigateService
(
	UIM_t_navigate_menu* i_pxNavigateMenu,
	int i_nNbItmes,
	UIM_t_navigate_option* i_pxNavigateOption
);


/*! @deprecated	This function allows the input of an IP address (format: www.xxx.yyy.zzz).
 *	@deprecated It returns to the calling application the entered IP address.
			 The separator between the triplets of IP address can be configurable.
			 The point "." will be the default value .
 *	@param[in]			i_pcTitle					The title of the screen.
  *	@param[in,out]	io_pcIpAddress		The ip address.
 *	@param[in]			i_pcSeparator			The separator.
*	@return
 *	- #UIM_SUCCESS				
 *	- #UIM_CANCEL_INPUT			
 *	- #UIM_INVALIDE_IP_ADRESS	
 *	- #UIM_INVALIDE_SEPARATOR		
 *	- #UIM_INVALID_PARAMETER    
 *	@note This function can be preceded by #UIM_SetFontMode to select the font in which the title will be displayed.
 *
 *
 * @link VGE_UIM Back to top @endlink
**/

int UIM_GetIpAddress
(
	char* i_pcTitle,
	char* io_pcIpAddress,
	char* i_pcSeparator
);

/*! @deprecated This function is used to get a date entered by the user within a configurable graphical interface. Several date formats are taken into account.
 *	@param[in]			i_pcTitle				The screen header. 
 *	@param[in]			i_eDateFormat		The date format, enumerated in #UIM_e_date_format.
 *	@param[out]	io_pcDate				The input / output date. The input date is displayed to the user.								
 * - If the entered date is valid, the output date will be equal to the entered date.
 * - Else, the output date remains identical to the input date.
 *
 * Date format may be an element of the enumeration #UIM_e_date_format
 *
 *	@return
 *	- #UIM_SUCCESS			
 *	- #UIM_INVALIDE_FORMAT	
 *	- #UIM_INVALIDE_DATE		
 *	- #UIM_CANCEL_INPUT		
 *	- #UIM_INVALID_PARAMETER  
 *
 *	@note This function can be preceded by #UIM_SetFontMode to select the font in which the title will be displayed.
 *
 *
 *	@sa 
 *	- @link UIM_e_date_format Date Format Enumeration@endlink
 *
 * @link VGE_UIM Back to top @endlink
**/

int UIM_GetDate
(
	char* i_pcTitle,
	UIM_e_date_format i_eDateFormat,
	char* io_pcDate
);

/*! @deprecated This function is used to get a time entered by the user within a configurable graphical interface. Several time formats are taken into account.
 *	@param[in]		  i_pcTitle				  The screen header.
 *	@param[in]		  i_eTimeFormat			The time format, enumerated in #UIM_e_time_format.
 *	@param[in,out]	io_pcTime				  The input / output time. The input time is displayed to the user.
 * - If the entered time is valid, the output time will be equal to the entered time.
 * - Else, the output time remains identical to the input time.
 *
 *	Time format may be an element of the enumeration #UIM_e_time_format
 *
 *	@return
 *	- #UIM_SUCCESS		
 *	- #UIM_INVALIDE_FORMAT	
 *	- #UIM_INVALIDE_TIME		
 *	- #UIM_CANCEL_INPUT		
 *	- #UIM_INVALID_PARAMETER
 *
 *	@note This function can be preceded by #UIM_SetFontMode to select the font in which the title will be displayed.
 *
 *
 *	@sa 
 *	- @link UIM_e_time_format Time Format Enumeration@endlink
 *
 * @link VGE_UIM Back to top @endlink
**/

int UIM_GetTime
(
	char* i_pcTitle,
	UIM_e_time_format i_eTimeFormat,
	char* io_pcTime
);

/*! @deprecated This function is used to get credit card data within a configurable graphical interface.
 *	@param[in]			i_pxPanOption			The PAN entry option.
 *	@param[in,out]	io_pcPAN					The PAN result.
 *	@param[in]			i_pxExpDateOption	The Expiration Date entry option.
 *	@param[in,out]	io_pcExpDate			The Expiration Date result.
 *	@param[in]			i_bUseCVV2				Use CVV2 (TRUE) or not (FALSE).
 *	@param[in]			i_pxCVV2Option		The CVV2 entry option.
 *	@param[in,out]	io_pcCVV2					The CVV2 result.
 *	@return
 *	- #UIM_SUCCESS				
 *	- #UIM_INPUT_PAN_ERROR		
 *	- #UIM_CODE_LUHN_ERROR		
 *	- #UIM_INPUT_EXPDATE_ERROR	
 *	- #UIM_INPUT_CVV2_ERROR		
 *	- #UIM_INVALID_PARAMETER   
 *
 *	@note
 *
 *	@a bCheckLuHnCode can be set to :
 *	- @c TRUE (LuHn Check active)
 *	- @c FALSE (LuHn Check inactive)
 *	 
 *
 *	@sa 
 *	- @link UIM_t_pan_option PAN option structure@endlink
 *	- @link UIM_t_exp_date_option Expiry Date option structure@endlink
 *	- @link UIM_t_cvv2_option CVV2 option structure@endlink
 *
 * @link VGE_UIM Back to top @endlink
**/

int UIM_GetManualEntry
(
	UIM_t_pan_option* i_pxPanOption,
	char* io_pcPAN,
	UIM_t_exp_date_option* i_pxExpDateOption,
	char* io_pcExpDate,
	char i_bUseCVV2,
	UIM_t_cvv2_option* i_pxCVV2Option,
	char* io_pcCVV2
);


/*! @deprecated This function is used to get a numeric entry within a configurable graphical interface.
 *	@param[in]		i_pxNumericOption		The numeric entry option.
 *	@param[in,out]	o_pcResult				The numeric entry result.
 *	@return
 *	- #UIM_SUCCESS			
 *	- #UIM_INPUT_NUM_ERROR	
 *	- #UIM_CANCEL_INPUT		
 *	- #UIM_TIME_OUT			
 *	- #UIM_INVALID_PARAMETER 
 *
 *	@note
 *
 *	@a cSecurityLevel can be set to :
 *	- #SECURITY_LOW_LEVEL 	 : normal display of entered characters.
 *	- #SECURITY_MEDIUM_LEVEL: display '*' instead of entered characters. 	 
 *
 *	@sa 
 *	- @link UIM_t_numeric_option Numeric option structure@endlink
 *
 * @link VGE_UIM Back to top @endlink
 **/

int UIM_GetNumericEntry
(
	UIM_t_numeric_option * i_pxNumericOption,
	char* o_pcResult
);


/*! @deprecated This function is used to get an alphanumerical entry within a configurable graphical interface.
 *	@param[in]			i_pxAlphaNumOption		The alpha numeric entry option.
 *	@param[in,out]	o_pcResult						The alpha numeric result.
 *	@return
 *	- #UIM_SUCCESS		
 *	- #UIM_INPUT_ALPHA_NUM_ERROR	
 *	- #UIM_CANCEL_INPUT			
 *	- #UIM_TIME_OUT				
 *	- #UIM_INVALID_PARAMETER      
 *
 *	@note
 *	@a cSecurityLevel can be set to :
 *	- #SECURITY_LOW_LEVEL 	 : normal display of entered characters.
 *	- #SECURITY_MEDIUM_LEVEL : displays '*' instead of entered characters. 	
 *
 *	@sa 
 *	- @link UIM_t_alpha_num_option Alphanumeric option structure@endlink
 *
 * @link VGE_UIM Back to top @endlink
**/

int UIM_GetAlphaNumEntry
(
	UIM_t_alpha_num_option * i_pxAlphaNumOption,
	char* o_pcResult
);


/*! @deprecated This function is used to draw a text message within a configurable graphical interface.
 *	@param[in]		i_pxMessageOption	The message description to display on the terminal.
 *	
 *	@return
 *	- #UIM_SUCCESS				
 *	- #UIM_INVALID_PARAMETER   
 * 
 *	@note 
 *	- @a cDisplay can be set to #NORMAL_MODE or #GRAPHIC_MODE
 *	- if @a cDisplay is set to #NORMAL_MODE mode, @a sNormalMode is used.
  *	- if @a cDisplay is set to #GRAPHIC_MODE, @a sGraphicMode is used.
 *	- If @a cDisplay is set to #GRAPHIC_MODE, this function can be preceded by #UIM_SetFontMode to select the font in which the title will be displayed.
 *
 *	@sa 
 *	- @link UIM_t_message_option Message option structure@endlink
 *	- @link UIM_t_normal_mode Normal mode structure@endlink
 *	- @link UIM_t_graphic_mode Graphic mode structure@endlink
 *
 * @link VGE_UIM Back to top @endlink
**/
int UIM_DrawTextMessage
(
	UIM_t_message_option * i_pxMessageOption
);


/*! @deprecated This function is used to draw a configurable screen: 4 lines, footer, bitmap, etc...
 *	@param[in]		i_pxScreen			The screen to display on the terminal.
 *
 *
 *	@return
 *	- #UIM_SUCCESS		
 *	- #UIM_INVALID_PARAMETER
 *      
 *	@note This function can be preceded by #UIM_SetFontMode to select the font in which the title, footer and lines (1..4) will be displayed.
 *
 *	@sa 
 *	- @link UIM_t_screen Screen structure@endlink
 *
 * @link VGE_UIM Back to top @endlink
**/
int UIM_DrawScreen
(
	UIM_t_screen * i_pxScreen
);


/*! @deprecated This function gets a numerical or an alpha numerical entry, several formats are supported.
 *	@param[in]		i_pxInput		The input option.
 *	@param[out]		o_pcResult		The result.
 *	@return
 *	- #UIM_SUCCESS				
 *	- #UIM_INPUT_ALPHA_NUM_ERROR	
 *	- #UIM_INPUT_NUM_ERROR		
 *	- #UIM_CANCEL_INPUT		
 *	- #UIM_TIME_OUT				
 *	- #UIM_INVALID_PARAMETER
 *
 *	@note
 *
 *	@a cEcho can be set to :
 *	- @c ECHO_NORMAL  : echo normal
 *	- @c ECHO_SPECIAL : secret echo '*'
 *	- @c NO_ECHO      : no echo  
 *  
 *	@a cInputType can be set to :
 *	- #NUMERICAL : if the input is numerical
 *	- #ALPHA_NUMERICAL : if the input is alphanumerical.
 *
 *	@sa 
 *	- @link UIM_t_input Input option structure@endlink
 *
 * @link VGE_UIM Back to top @endlink
**/

int UIM_InputValue
(
	UIM_t_input * i_pxInput,
	char* o_pcResult
);


/*! @deprecated This function sets the current font mode  : Normal, ISO8859 or Unicode.
 *	@param[in]		i_nFontMode			The font mode to set : #UIM_NORMAL_MODE, #UIM_UNICODE_MODE or #UIM_ISO8859_MODE.
 *	@param[out]		i_pcFileName		The font file name (@c NULL in case of #UIM_NORMAL_MODE).
 *	@return
 *	- #UIM_SUCCESS				
 *	- #UIM_FONT_FILE_NOT_FOUND	
 *	- #UIM_UNKNOWN_FONT_MODE     
 *	@note The selected Font Mode is applied for the following functions  
 * - #UIM_DrawScreen
 * - #UIM_DrawTextMessage
 * - #UIM_GetTime
 * - #UIM_GetDate
 * - #UIM_GetIpAddress
 * - #UIM_DrawExtendedStringWithFont
 * - #UIM_DrawWindowWithFont.
 * @link VGE_UIM Back to top @endlink
**/
int UIM_SetFontMode(int i_nFontMode, char * i_pcFileName);


/*! @deprecated This function draws an extended string according to the graphical font mode : @c Normal , @c ISO8859 or @c Unicode.
 
 *	@param[in]		message 		Pointer to the formatted string to be displayed.
 *	@param[in]		x0	    		Parameter x in range [0,127]
 *	@param[in]		y0				  Parameter y in range [0,127]
 *	@param[in]		reverse			Reverse video : _ON_ or _OFF_
 *	@param[in]		police  		Police : _SMALL_ , _MEDIUM_ or _LARGE_
 *	@param[in]		type	      Type : _NORMALE_ , _PROPORTIONNEL_ , _FIXED_WIDTH_ or _PROP_WIDTH_

 *	@return None
 *	@note This function can be preceded by #UIM_SetFontMode to select the font in which the string will be displayed.
 * @link VGE_UIM Back to top @endlink 
**/
void   UIM_DrawExtendedStringWithFont(char *message, int x0,int y0,int reverse,int police,int type);



/*! @deprecated This function draws a window according to the graphical font mode : @c Normal , @c ISO8859, @c Unicode.
 
 *	@param[in]		left	   	  In range [0,127]
 *	@param[in]		top	       	In range [0,127]
 *	@param[in]		rigth	   	  In range [0,127]
 *	@param[in]		bottom	   	In range [0,127]
 *	@param[in]		thickness  	Bordersize : pixels number for the border ( 1 minimum )
 *	@param[in]		Titre       Title : string to be displayed at the top of the window. May be @c NULL (no title)

 *	@return None
 *	@note This function can be preceded by #UIM_SetFontMode to select the font in which the title will be displayed.
 *
 * @link VGE_UIM Back to top @endlink
**/
void  UIM_DrawWindowWithFont(int left,int top,int rigth,int bottom,int thickness,unsigned char *Titre);


#endif //#if defined (__GNUC__) || defined(_DEPRECATED_SDK920_AVL_)

/*! @} **/

#ifdef __cplusplus
}
#endif
