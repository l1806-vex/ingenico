// $Id: GL_Dialog.h,v 1.1.2.42 2012/03/05 11:10:03 rbertholet Exp $
// Graphic Object dialog
#ifndef GL_Dialog_h_INCLUDED
#define GL_Dialog_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_Dialog
@{
@addtogroup GL_DialogDoc Dialog boxes
@{

These functions allow the opening of a dialog box, wait and control input, and returns the value entered.

Below is a list dialogs boxes displaying lists :
	- @ref GL_Dialog_Menu : Displays a list of items and awaits the user selection
	- @ref GL_Dialog_IconMenu : Displays a list of icons and awaits the user selection
	- @ref GL_Dialog_IconButtonMenu : Displays a list of icons buttons and awaits the user selection
	- @ref GL_Dialog_Choice : Choose from a list item
	- @ref GL_Dialog_MultiChoice : Dialog box for selecting multiple items

Below is a list of dialogs boxes for selecting files
	- @ref GL_Dialog_File : Selects a file in a file system
	- @ref GL_Dialog_MultiFile : Selects multiple files in a file system

Below is a list of dialogs boxes to display message : 
	- @ref GL_Dialog_Message : Creating a message box to display an informations, a question, or an error
	- @ref GL_Dialog_Picture : Display a picture
	- @ref GL_Dialog_Progress : Display a dialog with a progress bar.
	- @ref GL_Dialog_Media : Display a video or play audio

Below is a list of dialogs boxes for data entry :
	- @ref GL_Dialog_Text : Inputs a value string 
	- @ref GL_Dialog_Date : Gets a date or hour
	- @ref GL_Dialog_Ip : Inputs an ip address
	- @ref GL_Dialog_Amount : Inputs an amount
	- @ref GL_Dialog_Color : Selects a color in palette
	- @ref GL_Dialog_Slider : Selects a value with the slider
	- @ref GL_Dialog_VirtualKeyboard : Inputs a value string with the virtual keyboard
	- @ref GL_Dialog_Password  : Inputs a password string 
	- @ref GL_Dialog_Scheme : Inputs a pin data with a scheme
	- @ref GL_Dialog_Signature : Dialog box to capture a signature

@} */

/** Defines the icons supported by the message box */
typedef enum T_GL_DIALOG_ICON
{
	GL_ICON_NONE,         ///< The message box does not have any icon. 
	GL_ICON_QUESTION,     ///< An icon indicating that the message is asking a question. 
	GL_ICON_INFORMATION,  ///< An icon indicating that the message is nothing out of the ordinary. 
	GL_ICON_WARNING,      ///< An icon indicating that the message is a warning, but can be dealt with. 
	GL_ICON_ERROR      ///< An icon indicating that the message represents a critical problem. 
} T_GL_DIALOG_ICON;


/** Defines the buttons managed in the dialogs */
typedef enum T_GL_BUTTONS
{
	GL_BUTTON_NONE                = 0x0000, ///< No button managed
	GL_BUTTON_VALID               = 0x0001, ///< Green button validation managed
	GL_BUTTON_CANCEL              = 0x0002, ///< Red button cancellation managed
	GL_BUTTON_CORRECTION          = 0x0004, ///< Yellow button correction managed
	GL_BUTTON_SHORTCUT            = 0x0008, ///< Shortcut present (reserved for the manager application)

	GL_BUTTON_VALID_CANCEL        = (GL_BUTTON_VALID|GL_BUTTON_CANCEL),
	GL_BUTTON_CORRECTION_CANCEL   = (GL_BUTTON_CORRECTION|GL_BUTTON_CANCEL),
	GL_BUTTON_VALID_CORRECTION    = (GL_BUTTON_VALID|GL_BUTTON_CORRECTION),
	GL_BUTTON_ALL                 = (GL_BUTTON_VALID|GL_BUTTON_CANCEL|GL_BUTTON_CORRECTION),
	GL_BUTTON_DEFAULT             = 0xFFFF ///< To use the default shortcuts
} T_GL_BUTTONS;


/* **************************************************************************************************************************************** */
/* **************************************************************************************************************************************** */
/** 
@addtogroup GL_DialogList List dialog
@{

@addtogroup GL_DialogListDoc List dialog
@{
Below is an example of creating a menu (@ref GL_Dialog_Menu)

	@image html dialogTest6.png
	@include GL_SampleDialogMenu.c

Below is an example of creating an icon menu (@ref GL_Dialog_IconMenu)

	@image html dialogTest1.png
	@include GL_SampleDialogIconMenu.c

Below is an example of creating an icon button menu (@ref GL_Dialog_IconButtonMenu)

	@image html dialogTest25.png
	@include GL_SampleDialogIconButtonMenu.c

Below is an example of creating a choice (@ref GL_Dialog_Choice)

	@image html dialogTest13.png
	@include GL_SampleDialogChoice.c

Below is an example for selecting multiple items(@ref GL_Dialog_MultiChoice)

	@image html dialogTest21.png
	@include GL_SampleDialogMultiChoice.c
@}


*/
/* **************************************************************************************************************************************** */
/* **************************************************************************************************************************************** */

/** Displays a list of items and awaits the user selection
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param menu menu items (array of strings, WARNING : THE LAST IN THE LIST MUST ALWAYS BE A NULL POINTER)
@param selectedItem number of the item that has focus
@param shortcut Keyboard shortcut value for the first list item or GL_KEY_NONE for no keyboard shortcut, only the values ??ranging from GL_KEY_O to GL_KEY_9 are supported
@param buttons button to make visible and manage
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return the number of the menu item clicked (numbering starts at zero) else returns GL_KEY_CANCEL @see GL_TypesKeys*/
ulong GL_Dialog_Menu (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * const * menu, int selectedItem, T_GL_BUTTONS buttons, T_GL_WCHAR shortcut, T_GL_DURATION duration) GL_EXCEPTION;

/** Displays a list of icons and awaits the user selection
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param menu menu items (array of two strings : text and icon filename @see GL_Widget_Url) (WARNING : THE LAST IN THE LIST MUST ALWAYS BE A NULL POINTER)
@param selectedItem number of the item that has focus
@param buttons button to make visible and manage
@param shortcut Keyboard shortcut value for the first list item or GL_KEY_NONE for no keyboard shortcut, only the values ??ranging from GL_KEY_O to GL_KEY_9 are supported
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return the number of the menu item clicked (numbering starts at zero) else returns GL_KEY_CANCEL @see GL_TypesKeys*/
ulong GL_Dialog_IconMenu (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * const * menu, int selectedItem, T_GL_BUTTONS buttons, T_GL_WCHAR shortcut, T_GL_DURATION duration) GL_EXCEPTION;

/** Displays a list of icons button and awaits the user selection
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param menu menu items (array of two strings : text and icon filename @see GL_Widget_Url) (WARNING : THE LAST IN THE LIST MUST ALWAYS BE A NULL POINTER)
@param selectedItem number of the item that has focus
@param buttons button to make visible and manage
@param shortcut Keyboard shortcut value for the first list item or GL_KEY_NONE for no keyboard shortcut, only the values ??ranging from GL_KEY_O to GL_KEY_9 are supported
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return the number of the menu item clicked (numbering starts at zero) else returns GL_KEY_CANCEL @see GL_TypesKeys*/
ulong GL_Dialog_IconButtonMenu (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * const * menu, int selectedItem, T_GL_BUTTONS buttons, T_GL_WCHAR shortcut, T_GL_DURATION duration) GL_EXCEPTION;

/** Choose from a list item
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param menu items menu (array of strings) (WARNING : THE LAST IN THE LIST MUST ALWAYS BE A NULL POINTER)
@param selectedItem number of the item that has focus
@param buttons button to make visible and manage
@param shortcut Keyboard shortcut value for the first list item or GL_KEY_NONE for no keyboard shortcut, only the values ??ranging from GL_KEY_O to GL_KEY_9 are supported
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return the number of the menu item clicked (numbering starts at zero) else returns GL_KEY_CANCEL @see GL_TypesKeys*/
ulong GL_Dialog_Choice (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * const * menu, int selectedItem, T_GL_BUTTONS buttons, T_GL_WCHAR shortcut, T_GL_DURATION duration) GL_EXCEPTION;

/** Dialog box for selecting multiple items
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param items items (array of strings) (WARNING : THE LAST IN THE LIST MUST ALWAYS BE A NULL POINTER)
@param selectedItem item number receives focus at first display
@param checkedItems array containing the status of all the checkboxes, this table is modified by the function according to the boxes checked
@param buttons button to make visible and manage
@param shortcut Keyboard shortcut value for the first list item or GL_KEY_NONE for no keyboard shortcut, only the values ??ranging from GL_KEY_O to GL_KEY_9 are supported
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return the number of the menu item clicked (numbering starts at zero) else returns GL_KEY_CANCEL @see GL_TypesKeys*/
ulong GL_Dialog_MultiChoice (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * const * items, int selectedItem, bool * checkedItems, T_GL_BUTTONS buttons, T_GL_WCHAR shortcut, T_GL_DURATION duration) GL_EXCEPTION;



/* **************************************************************************************************************************************** */
/* **************************************************************************************************************************************** */
/** 
@}
@addtogroup GL_DialogFile File dialog
@{ 

@addtogroup GL_DialogFileDoc File dialog
@{
Below is an example of dialog file (@ref GL_Dialog_File)

	@image html dialogTest18.png
	@include GL_SampleDialogFile.c

Below is an example dialog box for selecting multiple files (@ref GL_Dialog_MultiFile)
	
	@image html dialogTest24.png
	@include GL_SampleDialogMultiFile.c
@}
*/
/* **************************************************************************************************************************************** */
/* **************************************************************************************************************************************** */

/** Callback for filtering the display of files or directories
@param path Path full file name (with the filesystem)
@param isFile true indicates a file, false indicates a directory
@return must return true if the file is displayed, otherwise returns false */
typedef bool (*T_GL_DIALOG_FILE_FILTER)(const char * path, bool isFile);

/** Select a file into the filesystem
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param root root directory name to open (dir://flash/HOST for the HOST, dir://infd0A/directory for the vfs directory)
@param filter the filter used in the file dialog to the given filter (can contains the wildcard * or ?)
@param fileSelected return the file selected
@param fileSelectedSize maximal size of the buffer fileSelected
@param filterCallback filter callback function
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return Returns the identity of the standard button*/
ulong GL_Dialog_File (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * root, const char * filter, char * fileSelected, unsigned long fileSelectedSize, T_GL_DIALOG_FILE_FILTER filterCallback, T_GL_DURATION duration) GL_EXCEPTION;

/** Allows you to select multiple files
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param root root directory name to open (dir://flash/HOST for the HOST, dir://infd0A/directory for the vfs directory)
@param filter the filter used in the file dialog to the given filter (can contains the wildcard * or ?)
@param files list of files selected
@param filterCallback filter callback function or null
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return Returns the identity of the standard button*/
ulong GL_Dialog_MultiFile (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * root, const char * filter, T_GL_HSTRINGLIST files, T_GL_DIALOG_FILE_FILTER filterCallback, T_GL_DURATION duration) GL_EXCEPTION;


/* **************************************************************************************************************************************** */
/* **************************************************************************************************************************************** */
/** 
@}
@addtogroup GL_DialogMessage Message dialog
@{ 

@addtogroup GL_DialogMessageDoc Message dialog
@{
Below is an example of creating a message box (@ref GL_Dialog_Message)

	@image html dialogTest2.png
	@image html dialogTest3.png
	@image html dialogTest4.png
	@image html dialogTest5.png
	@include GL_SampleDialogMessage.c

Below is an example of picture (@ref GL_Dialog_Picture)

	@image html dialogTest15.png
	@include GL_SampleDialogPicture.c

Below is an example of dialog progress (@ref GL_Dialog_Progress)

	@image html dialogTest17.png
	@include GL_SampleDialogProgress.c

Below is an example of video (@ref GL_Dialog_Media)

	@image html dialogTest14.png
	@include GL_SampleDialogMedia.c
@}
*/
/* **************************************************************************************************************************************** */
/* **************************************************************************************************************************************** */

/** Creating a message box to display an informations, a question, or an error
@param graphicLib handle on the graphical client
@param title value to be displayed in the title (null hide title)
@param text text displayed (null hide text)
@param icon icon displayed
@param buttons button to make visible and manage
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return returns the key or button pressed @see GL_TypesKeys*/
ulong GL_Dialog_Message(T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, T_GL_DIALOG_ICON icon, T_GL_BUTTONS buttons, T_GL_DURATION duration) GL_EXCEPTION;

/** Display a picture
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param text text displayed (null hide text)
@param source media filename (See @ref GL_Widget_Url for the url coding)
@param buttons button to make visible and manage
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return returns the key or button pressed @see GL_TypesKeys*/
ulong GL_Dialog_Picture (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, const char * source, T_GL_BUTTONS buttons, T_GL_DURATION duration) GL_EXCEPTION;

/** Callback function called periodically to update the progress bar */
typedef T_GL_COORD (*T_GL_DIALOG_PROGRESS_UPDATE)(T_GL_COORD value);

/** Display a dialog with a progress bar. The dialog box exit automatically when the max is reached.
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param text text displayed (null hide text)
@param source picture filename (See @ref GL_Widget_Url for the url coding)
@param value pointer on the value (When the value pointer is null the update callback is called)
@param min minimal value
@param max maximal value
@param update null or callback function called periodically to update the progress bar (if this pointer is null value is only taken into account)
@param buttons button to make visible and manage
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return returns the key or button pressed @see GL_TypesKeys*/
ulong GL_Dialog_Progress(T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, const char * source, T_GL_COORD * value, T_GL_COORD min, T_GL_COORD max, T_GL_DIALOG_PROGRESS_UPDATE update, T_GL_BUTTONS buttons, T_GL_DURATION duration) GL_EXCEPTION;

/** Display a video or play audio
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param text text displayed (null hide text)
@param source media filename (See @ref GL_Widget_Url for the url coding)
@param volume volume level (0..255)
@param buttons button to make visible and manage
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return returns the key or button pressed @see GL_TypesKeys*/
ulong GL_Dialog_Media (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, const char * source, byte volume, T_GL_BUTTONS buttons, T_GL_DURATION duration) GL_EXCEPTION;

/* **************************************************************************************************************************************** */
/* **************************************************************************************************************************************** */
/** 
@}
@addtogroup GL_DialogInput Input dialog
@{ 
@addtogroup GL_DialogInputDoc Input dialog
@{
Below is an example of entering a text (@ref GL_Dialog_Text)

	@image html dialogTest11.png
	@include GL_SampleDialogText.c

Below is an example of entering a date and time (@ref GL_Dialog_Date)

	@image html dialogTest7.png
	@image html dialogTest8.png
	@include GL_SampleDialogDate.c

Below is an example of entering an IP address (@ref GL_Dialog_Ip)

	@image html dialogTest10.png
	@include GL_SampleDialogIp.c

Below is an example of entering an amount (@ref GL_Dialog_Amount)

	@image html dialogTest9.png
	@include GL_SampleDialogAmount.c

Below is an example of color selection (@ref GL_Dialog_Color)

	@image html dialogTest12.png
	@include GL_SampleDialogColor.c

Below is an example of dialog slider (@ref GL_Dialog_Slider)

	@image html dialogTest16.png
	@include GL_SampleDialogSlider.c

Below is an example of entering a text with a virtual keyboard(@ref GL_Dialog_VirtualKeyboard)

	@image html dialogTest19.png
	@include GL_SampleDialogVirtualKeyboard.c

Below is an example of entering a password(@ref GL_Dialog_Password)

	@image html dialogTest20.png
	@include GL_SampleDialogPassword.c

Below is an example for input data with a scheme (@ref GL_Dialog_Scheme)

	@image html dialogTest22.png
	@include GL_SampleDialogScheme.c

Below is an example of the signature capture (@ref GL_Dialog_Signature)

	@image html dialogTest23.png
	@include GL_SampleDialogSignature.c

@}
*/
/* **************************************************************************************************************************************** */
/* **************************************************************************************************************************************** */

/** Inputs a value string 
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param text text displayed (null hide text) (This value is the raw text without the mask characters)
@param mask mask string (or null if no mask defined) @ref GL_Widget_MaskProperties 
@param value value displayed and value entered (This value is the raw text without the mask characters)
@param valueSize maximum size of value buffer
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return returns the key or button pressed @see GL_TypesKeys*/
ulong GL_Dialog_Text (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, const char * mask, char * value, ulong valueSize, T_GL_DURATION duration) GL_EXCEPTION;

/** Gets a date
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param text text displayed (null hide text)
@param date date to get
@param format date format string is composed of 
	- y : Year with century as a decimal number[0000-9999].
	- m : Month as a decimal number [01,12].
	- d : Day of the month as a decimal number [01,31].
	- H : Hour (24-hour clock) as a decimal number [00,23].
	- M : Minute as a decimal number [00,59].
	- S : Second as a decimal number [00,59].
	other characters are treated as separators.
	If the string format is empty or null default value is "y/m/d"
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return returns the key or button pressed @see GL_TypesKeys*/
ulong GL_Dialog_Date (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, T_GL_HDATE date, const char * format, T_GL_DURATION duration) GL_EXCEPTION;

/** Inputs an ip addresse
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param text text displayed (null hide text)
@param ipAddr ip address displayed and returned
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return returns the key or button pressed @see GL_TypesKeys*/
ulong GL_Dialog_Ip (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, T_GL_HIP ipAddr, T_GL_DURATION duration) GL_EXCEPTION;

/** Inputs an amount
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param text text displayed (null hide text) (This value is the raw text without the mask characters)
@param mask mask string (or null if no mask defined) @ref GL_Widget_MaskProperties 
@param amount amount displayed and amount entered (all characters not significant from the mask must be absent in the amount: for example a mask "/d/d/d,/d/d/D./D/D" you must put the amount without dot "123456" and you will see on the screen "1,234.56").
The position of the decimal separator is not returned and must be deducted from the mask passed in parameter.
@param amountBufferSize size of amount buffer (The size of buffer must take into account the null character)
@param unit unit displayed (used for the currency)
@param unitAlign unit alignement (only GL_ALIGN_LEFT and  GL_ALIGN_RIGHT supported)
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return returns the key or button pressed @see GL_TypesKeys*/
ulong GL_Dialog_Amount (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, const char * mask, char * amount, ulong amountBufferSize , const char * unit, T_GL_ALIGN unitAlign, T_GL_DURATION duration) GL_EXCEPTION;

/** Selects a color in palette
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param text text displayed (null hide text)
@param color default color and color selected
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return returns the key or button pressed @see GL_TypesKeys*/
ulong GL_Dialog_Color (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, T_GL_HCOLOR color, T_GL_DURATION duration) GL_EXCEPTION;

/** Callback function called when the slider change */
typedef void (*T_GL_DIALOG_SLIDER_UPDATE)(T_GL_RANGE range) GL_EXCEPTION;

/** Select value with the slider
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param text text displayed (null hide text)
@param source picture filename (See @ref GL_Widget_Url for the url coding)
@param value value slider and value returned 
@param min minimal value
@param max maximal value
@param step step increment
@param update null or callback function called when the slider change
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return returns the key or button pressed @see GL_TypesKeys*/
ulong GL_Dialog_Slider(T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, const char * source, T_GL_COORD * value, T_GL_COORD min, T_GL_COORD max, T_GL_DIM step, T_GL_DIALOG_SLIDER_UPDATE update, T_GL_DURATION duration) GL_EXCEPTION;

/** Inputs a value string with the virtual keyboard
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param text text displayed (null hide text) (This value is the raw text without the mask characters)
@param mask mask string (or null if no mask defined) @ref GL_Widget_MaskProperties 
@param value value displayed and value entered 
@param valueSize maximum size of value buffer
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return Returns the identity of the standard button*/
ulong GL_Dialog_VirtualKeyboard (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, const char * mask, char * value, ulong valueSize, T_GL_DURATION duration) GL_EXCEPTION;

/** Inputs a password string 
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param text text displayed (null hide text)
@param mask mask string (or null if no mask defined) @ref GL_Widget_MaskProperties 
@param value value displayed and value entered 
@param valueSize maximum size of value buffer
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return Returns the identity of the standard button*/
ulong GL_Dialog_Password (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, const char * mask, char * value, ulong valueSize, T_GL_DURATION duration) GL_EXCEPTION;

/** Scheme interface */
struct T_GL_SCHEME_INTERFACE;

/** Scheme interface */
typedef struct T_GL_SCHEME_INTERFACE
{
	/** Open the scheme 
	@param interfac point on the current interface schema 
	@return 
		- GL_RESULT_SUCCESS : no error 
		- GL_ERROR_FAILED   : if the scheme cannot be opened */
	unsigned long (*open) (struct T_GL_SCHEME_INTERFACE *  interfac);

	/** Close the scheme 
	@param interfac point on the current interface schema  */
	void (*close)(struct T_GL_SCHEME_INTERFACE * interfac);

	/** Refresh the scheme content
	@param interfac point on the current interface schema 
	@param label label handle to refresh
	@return To exit the dialog box you must return a value other than GL_RESULT_SUCCESS.
		The value you put in return is equivalent to the value returned by the function @ref GL_Dialog_Scheme.
		Below are some examples of reporting that you can use :
		- GL_KEY_VALID         : key valid pressed
		- GL_KEY_CANCEL        : key cancel pressed
		- GL_RESULT_INACTIVITY : the scheme ends with a timeout
		- GL_RESULT_SUCCESS    : Stay in the execution of the function @ref GL_Dialog_Scheme */
	unsigned long (*refresh)(struct T_GL_SCHEME_INTERFACE * interfac, T_GL_HWIDGET label);

	/** Private data pointer */
	void * privateData;
} T_GL_SCHEME_INTERFACE;

/** Scheme interface handle */
typedef T_GL_SCHEME_INTERFACE * T_GL_HSCHEME_INTERFACE;


/** Inputs a pin data with a scheme
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param text text displayed (null hide text)
@param help help displayed (null hide text)
@param interfac scheme interface (must not null)
@return Returns the identity of the standard button pressed or error code */
ulong GL_Dialog_Scheme (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, const char * help, T_GL_HSCHEME_INTERFACE interfac) GL_EXCEPTION;

/** Capture a signature
@param graphicLib handle on the graphical client
@param title title of the message box (or null if no title)
@param text text displayed (null hide text)
@param filename name of the signature file generated (See @ref GL_Widget_Url for the url coding)
@param duration inactivity duration in milliseconds (@ref GL_RESULT_INACTIVITY)
@return returns the key or button pressed @see GL_TypesKeys*/
ulong GL_Dialog_Signature (T_GL_HGRAPHIC_LIB graphicLib, const char * title, const char * text, const char * filename, T_GL_DURATION duration);


/**@}*/


/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Dialog_h_INCLUDED
