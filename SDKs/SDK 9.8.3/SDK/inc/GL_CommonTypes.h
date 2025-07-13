// $Id: GL_CommonTypes.h,v 1.1.2.58 2012/10/25 11:00:22 rbertholet Exp $
// This module defines general types
#ifndef GL_CommonTypes_h_INCLUDED
#define GL_CommonTypes_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_Types Types
@{
@addtogroup GL_TypesKeys Keys
@{
*/

/** No key pressed */
#define GL_KEY_NONE                ((T_GL_WCHAR)0xFFFF)
/** Telium numeric 0 key */
#define GL_KEY_0                   ((T_GL_WCHAR)0x0030)
/** Telium numeric 1 key */
#define GL_KEY_1                   ((T_GL_WCHAR)0x0031)
/** Telium numeric 2 key */
#define GL_KEY_2                   ((T_GL_WCHAR)0x0032)
/** Telium numeric 3 key */
#define GL_KEY_3                   ((T_GL_WCHAR)0x0033)
/** Telium numeric 4 key */
#define GL_KEY_4                   ((T_GL_WCHAR)0x0034)
/** Telium numeric 5 key */
#define GL_KEY_5                   ((T_GL_WCHAR)0x0035)
/** Telium numeric 6 key */
#define GL_KEY_6                   ((T_GL_WCHAR)0x0036)
/** Telium numeric 7 key */
#define GL_KEY_7                   ((T_GL_WCHAR)0x0037)
/** Telium numeric 8 key */
#define GL_KEY_8                   ((T_GL_WCHAR)0x0038)
/** Telium numeric 9 key */
#define GL_KEY_9                   ((T_GL_WCHAR)0x0039)
/** Telium numeric dot key */
#define GL_KEY_DOT                 ((T_GL_WCHAR)0x002E)

/** Begin of range of controls keys */
#define GL_KEY_CONTROL_BEGIN       ((T_GL_WCHAR)0xF800)
/** End of range of controls keys */
#define GL_KEY_CONTROL_END         ((T_GL_WCHAR)0xF87F)
/** Telium green key */
#define GL_KEY_VALID               ((T_GL_WCHAR)0xF850)
/** Telium red key */
#define GL_KEY_CANCEL              ((T_GL_WCHAR)0xF851)
/** Telium yellow key */
#define GL_KEY_CORRECTION          ((T_GL_WCHAR)0xF852)
/** Telium paper feed key */
#define GL_KEY_PAPER               ((T_GL_WCHAR)0xF853)
/** Telium paper feed key */
#define GL_KEY_F                   ((T_GL_WCHAR)0xF854)
/** Telium function 1 key */
#define GL_KEY_F1                  ((T_GL_WCHAR)0xF855)
/** Telium function 2 key */
#define GL_KEY_F2                  ((T_GL_WCHAR)0xF856)
/** Telium function 3 key */
#define GL_KEY_F3                  ((T_GL_WCHAR)0xF857)
/** Telium function 4 key */
#define GL_KEY_F4                  ((T_GL_WCHAR)0xF858)
/** Telium up arrow key */
#define GL_KEY_UP                  ((T_GL_WCHAR)0xF859)
/** Telium down arrow key */
#define GL_KEY_DOWN                ((T_GL_WCHAR)0xF85A)
/** Telium ok key (this key is only present on EFT Smart) */
#define GL_KEY_OK                  ((T_GL_WCHAR)0xF86B)
/** Telium clear key */
#define GL_KEY_CLEAR               ((T_GL_WCHAR)0xF86C)

/* These keystrokes have no physical existence. They are used for navigation in widgets. 
They must be remapped according to existing keys on the terminal keyboard. */

/** Pass the focus to previous widget */
#define GL_VIRTUAL_KEY_PREVIOUS    ((T_GL_WCHAR)0xF81B)
/** Pass the focus to next widget */
#define GL_VIRTUAL_KEY_NEXT        ((T_GL_WCHAR)0xF81C)
/** Moves the cursor to the left in the widget that has focus */
#define GL_VIRTUAL_KEY_LEFT        ((T_GL_WCHAR)0xF800)
/** Moves the cursor to the right in the widget that has focus */
#define GL_VIRTUAL_KEY_RIGHT       ((T_GL_WCHAR)0xF801)
/** Moves the cursor to the up in the widget that has focus */
#define GL_VIRTUAL_KEY_UP          ((T_GL_WCHAR)0xF802)
/** Moves the cursor to the down in the widget that has focus */
#define GL_VIRTUAL_KEY_DOWN        ((T_GL_WCHAR)0xF803)
/** Toggle to insert mode */
#define GL_VIRTUAL_KEY_INSERT      ((T_GL_WCHAR)0xF804)
/** Deletes one character */
#define GL_VIRTUAL_KEY_DELETE      ((T_GL_WCHAR)0xF805)
/** Moves the cursor to the beginning of line */
#define GL_VIRTUAL_KEY_HOME        ((T_GL_WCHAR)0xF806)
/** Moves the cursor to the end of line */
#define GL_VIRTUAL_KEY_END         ((T_GL_WCHAR)0xF807)
/** Selects the previous page */
#define GL_VIRTUAL_KEY_PAGE_UP     ((T_GL_WCHAR)0xF808)
/** Selects the next page */
#define GL_VIRTUAL_KEY_PAGE_DOWN   ((T_GL_WCHAR)0xF809)
/** Print screen, this key is only available in debug version of GOAL, is inoperative in release version for security reasons */
#define GL_VIRTUAL_KEY_PRINT       ((T_GL_WCHAR)0xF80A)



/**
@}
@addtogroup GL_TypesKeysUtf8 Key value encoded in utf8
@{
*/
#ifndef SWIG
/** Selects the previous characters page */
#define GL_KEY_UTF8_PAGE_UP     "\xEF\xA0\x88"
/** Selects the next characters page */
#define GL_KEY_UTF8_PAGE_DOWN   "\xEF\xA0\x89"
/** Telium green key */
#define GL_KEY_UTF8_VALID       "\xEF\xA1\x90"
/** Telium red key */
#define GL_KEY_UTF8_CANCEL      "\xEF\xA1\x91"
/** Telium yellow key */
#define GL_KEY_UTF8_CORRECTION  "\xEF\xA1\x92"
#endif
/**
@}
@addtogroup GL_TypesKeysIso Key value encoded in iso 8859
@{
*/
#ifndef SWIG
/** Escape character */
#define GL_KEY_ESCAPE          0x1B
/** Selects the previous characters page */
#define GL_KEY_ISO_PAGE_UP     "\x1B\xF8\x08"
/** Selects the next characters page */
#define GL_KEY_ISO_PAGE_DOWN   "\x1B\xF8\x09"
/** Telium green key */
#define GL_KEY_ISO_VALID       "\x1B\xF8\x50"
/** Telium red key */
#define GL_KEY_ISO_CANCEL      "\x1B\xF8\x51"
/** Telium yellow key */
#define GL_KEY_ISO_CORRECTION  "\x1B\xF8\x52"
#endif
/**
@}
@addtogroup GL_TypesResults Results
@{
*/

/** No result */
#define GL_RESULT_NONE              GL_KEY_NONE

/** No error */
#define GL_RESULT_SUCCESS           0x0000

/** no user action since the specified time (@ref GL_Window_SetInactivityDuration, @ref GL_EVENT_INACTIVITY) */
#define GL_RESULT_INACTIVITY        0xF880

/** Short cut key pressed */
#define GL_RESULT_SHORTCUT          0xF881

/** The function has failed for any reason */
#define GL_RESULT_FAILED            0xF882

/** Timeout occured */
#define GL_RESULT_TIMEOUT           0xF883

/** Some handles are null */
#define GL_RESULT_HANDLE            0xF884

/** The function is not yet implemented */
#define GL_RESULT_NOT_IMPLEMENTED   0xF885

/** This function is not supported by this object handle */
#define GL_RESULT_NOT_SUPPORTED     0xF886

/** This field has a bad type */
#define GL_RESULT_BAD_TYPE          0xF887

/** A field has not been found */
#define GL_RESULT_NOT_FOUND         0xF888

/** Syntax error detected */
#define GL_RESULT_SYNTAX            0xF889

/** Unable to read or write the content of a file */
#define GL_RESULT_FILE              0xF88A

/** The value of a parameter passed to the function is not acceptable */
#define GL_RESULT_BAD_PARAMETER     0xF88B

/** An internal error is occured handle content corrupted, missing data ... */
#define GL_RESULT_INTERNAL          0xF88C

/** Paper is needed */
#define GL_RESULT_PAPER_OUT         0xF88D

/** Previous printer job not yet terminated */
#define GL_RESULT_PENDING           0xF88E

/** Out of limits */
#define GL_RESULT_OUT_OF_LIMIT      0xF88F

/** Too imbrication of include */
#define GL_RESULT_TOO_MANY_IMBRICATION   0xF890

/** The screen orientation is already locked */
#define GL_RESULT_SCREEN_ALREADY_LOCKED    0xF891

/** The screen is changing its orientation */
#define GL_RESULT_SCREEN_IN_ROTATION    0xF892

/**
@}
@addtogroup GL_TypesEncoding Encoding charsets
@{
*/

/** Charset definition */
typedef enum T_GL_ENCODING_CHARSET
{
	GL_ENCODING_UTF8 = 0,    ///< Unicode utf8
	GL_ENCODING_ISO_8859_1,  ///< Latin-1 Western European
	GL_ENCODING_ISO_8859_2,  ///< Latin-2 Central European
	GL_ENCODING_ISO_8859_3,  ///< Latin-3 South European
	GL_ENCODING_ISO_8859_4,  ///< Latin-4 North European
	GL_ENCODING_ISO_8859_5,  ///< Latin/Cyrillic
	GL_ENCODING_ISO_8859_6,  ///< Latin/Arabic
	GL_ENCODING_ISO_8859_7,  ///< Latin/Greek
	GL_ENCODING_ISO_8859_8,  ///< Latin/Hebrew
	GL_ENCODING_ISO_8859_9,  ///< Latin-5 Turkish
	GL_ENCODING_ISO_8859_10, ///< Latin-6 Nordic
	GL_ENCODING_ISO_8859_11, ///< Latin/Thai 
	GL_ENCODING_ISO_8859_13, ///< Latin-7 Baltic Rim
	GL_ENCODING_ISO_8859_14, ///< Latin-8 Celtic
	GL_ENCODING_ISO_8859_15, ///< Latin-9

	GL_ENCODING_LAST
} T_GL_ENCODING_CHARSET;

/**
@}
@addtogroup GL_TypesError Errors codes
@{
*/

/** Errors codes */
typedef enum T_GL_ERROR_CODE
{
	GL_SUCCESS                     = GL_RESULT_SUCCESS               , ///< No error
	GL_ERROR_FAILED                = GL_RESULT_FAILED                , ///< The function has failed for any reason
	GL_ERROR_TIMEOUT               = GL_RESULT_TIMEOUT               , ///< Timeout occured
	GL_ERROR_HANDLE                = GL_RESULT_HANDLE                , ///< Some handles are null
	GL_ERROR_NOT_IMPLEMENTED       = GL_RESULT_NOT_IMPLEMENTED       , ///< The function is not yet implemented
	GL_ERROR_NOT_SUPPORTED         = GL_RESULT_NOT_SUPPORTED         , ///< This function is not supported by this object handle
	GL_ERROR_BAD_TYPE              = GL_RESULT_BAD_TYPE              , ///< This field has a bad type
	GL_ERROR_NOT_FOUND             = GL_RESULT_NOT_FOUND             , ///< A field has not been found
	GL_ERROR_SYNTAX                = GL_RESULT_SYNTAX                , ///< Syntax error detected
	GL_ERROR_FILE                  = GL_RESULT_FILE                  , ///< Unable to read or write the content of a file
	GL_ERROR_BAD_PARAMETER         = GL_RESULT_BAD_PARAMETER         , ///< The value of a parameter passed to the function is not acceptable
	GL_ERROR_INTERNAL              = GL_RESULT_INTERNAL              , ///< An internal error is occured (handle content corrupted missing data ...)
	GL_ERROR_PAPER_OUT             = GL_RESULT_PAPER_OUT             , ///< Paper is needed 
	GL_ERROR_PENDING               = GL_RESULT_PENDING               , ///< Previous printer job not yet terminated
	GL_ERROR_SCREEN_ALREADY_LOCKED = GL_RESULT_SCREEN_ALREADY_LOCKED , ///< The screen orientation is already locked 
	GL_ERROR_SCREEN_IN_ROTATION	   = GL_RESULT_SCREEN_IN_ROTATION	   ///< The screen is changing its orientation
} T_GL_ERROR_CODE;


/**
@}
@addtogroup GL_TypesOther Other definitions
@{
*/

/*<DEFINE>
	Struct("FONTSIZE",                          "Defines a size",
		RefOne("height",           "FONTSIZES", "Font height"),
		),

	EnumXml("FONTSIZES",                                  "Unit supported by the graphical library.",
		DefineXml("XXSMALL","0x3FF0",                     "Extra extra small font size"),
		DefineXml("XSMALL", "0x3FF1",                     "Extra small font size"),
		DefineXml("SMALL",  "0x3FF2",                     "Small font size"),
		DefineXml("MEDIUM", "0x3FF3",                     "Medium font size"),
		DefineXml("LARGE",  "0x3FF4",                     "Large font size"),
		DefineXml("XLARGE", "0x3FF5",                     "Extra large font size"),
		DefineXml("XXLARGE","0x3FF6",                     "Extra extra large font size"),
		DefineXml("5","5","font size 5"),DefineXml("6","6","font size 6"),DefineXml("7","7","font size 7"),DefineXml("8","8","font size 8"),DefineXml("9","9","font size 9"),
		DefineXml("10","10","font size 10"),DefineXml("11","11","font size 11"),DefineXml("12","12","font size 12"),DefineXml("13","13","font size 13"),
		DefineXml("14","14","font size 14"),DefineXml("15","15","font size 15"),DefineXml("16","16","font size 16"),DefineXml("17","17","font size 17"),
		DefineXml("18","18","font size 18"),DefineXml("19","19","font size 19"),DefineXml("20","20","font size 20"),DefineXml("21","21","font size 21"),
		DefineXml("22","22","font size 22"),DefineXml("23","23","font size 23"),DefineXml("24","24","font size 24"),DefineXml("25","25","font size 25"),
		DefineXml("26","26","font size 26"),DefineXml("27","27","font size 27"),DefineXml("28","28","font size 28"),DefineXml("29","29","font size 29"),
		DefineXml("30","30","font size 30"),DefineXml("31","31","font size 31"),DefineXml("32","32","font size 32"),DefineXml("33","33","font size 33"),
		DefineXml("34","34","font size 34"),DefineXml("35","35","font size 35"),DefineXml("36","36","font size 36"),DefineXml("37","37","font size 37"),
		DefineXml("38","38","font size 38"),DefineXml("39","39","font size 39"),DefineXml("40","40","font size 40"),DefineXml("41","41","font size 41"),
		DefineXml("42","42","font size 42"),DefineXml("43","43","font size 43"),DefineXml("44","44","font size 44"),DefineXml("45","45","font size 45"),
		DefineXml("46","46","font size 46"),DefineXml("47","47","font size 47"),DefineXml("48","48","font size 48"),DefineXml("49","49","font size 49"),
		DefineXml("50","50","font size 50"),DefineXml("51","51","font size 51"),DefineXml("52","52","font size 52"),DefineXml("53","53","font size 53"),
		DefineXml("54","54","font size 54"),DefineXml("55","55","font size 55"),DefineXml("56","56","font size 56"),DefineXml("57","57","font size 57"),
		DefineXml("58","58","font size 58"),DefineXml("59","59","font size 59"),DefineXml("60","60","font size 60"),DefineXml("61","61","font size 61"),
		DefineXml("62","62","font size 62"),DefineXml("63","63","font size 63"),DefineXml("64","64","font size 64"),DefineXml("65","65","font size 65"),
		DefineXml("66","66","font size 66"),DefineXml("67","67","font size 67"),DefineXml("68","68","font size 68"),DefineXml("69","69","font size 69"),
		DefineXml("70","70","font size 70"),DefineXml("71","71","font size 71"),DefineXml("72","72","font size 72"),DefineXml("73","73","font size 73"),
		DefineXml("74","74","font size 74"),DefineXml("75","75","font size 75"),DefineXml("76","76","font size 76"),DefineXml("77","77","font size 77"),
		DefineXml("78","78","font size 78"),DefineXml("79","79","font size 79"),DefineXml("80","80","font size 80"),DefineXml("81","81","font size 81"),
		DefineXml("82","82","font size 82"),DefineXml("83","83","font size 83"),DefineXml("84","84","font size 84"),DefineXml("85","85","font size 85"),
		DefineXml("86","86","font size 86"),DefineXml("87","87","font size 87"),DefineXml("88","88","font size 88"),DefineXml("89","89","font size 89"),
		DefineXml("90","90","font size 90"),DefineXml("91","91","font size 91"),DefineXml("92","92","font size 92"),DefineXml("93","93","font size 93"),
		DefineXml("94","94","font size 94"),DefineXml("95","95","font size 95"),DefineXml("96","96","font size 96"),DefineXml("97","97","font size 97"),
		DefineXml("98","98","font size 98"),DefineXml("99","99","font size 99"),
		),    
</DEFINE>
<ALL>
	Struct("FONT",                               "Font used in display of text",
		String("name",                           "Font name"),
</ALL>
<XSD>
		RefOne("size",             "FONTSIZE",   "Font size"),
</XSD>
<JSON>
		RefOne("size",             "SIZE",   "Font size"),
</JSON>
<ALL>
		RefOne("style",            "FONTSTYLE",  "Font style (bold, italic, normal, ...)"),
		),


	Enum("FONTSTYLE",                            "Possible font style ",
		Define("normal",           "0",          "Normal style"),
		Define("italic",           "1",          "Italic style"),
		Define("bold",             "2",          "Bold style"),
		Define("bold,italic",      "3",          "Bold italic style")
	),       
</ALL>*/
/** Possible font style */
typedef enum T_GL_FONT_STYLE
{
	GL_FONT_STYLE_NORMAL = 0, ///< Normal style
	GL_FONT_STYLE_ITALIC = 1, ///< Italic style
	GL_FONT_STYLE_BOLD   = 2, ///< Bold style
	GL_FONT_STYLE_BOLD_ITALIC = (GL_FONT_STYLE_ITALIC|GL_FONT_STYLE_BOLD) ///< Bold italic style
}T_GL_FONT_STYLE;

/** Possible pixel type */
typedef enum T_GL_PIXEL_TYPE
{
	GL_PIXEL_TYPE_AY11 = 0,		///< pixel type for b&w systems (0baxxxxxxc with bit a = 0 for transparent and bit c = 1 if pixel is white)
	GL_PIXEL_TYPE_ARGB4444 = 1, ///< pixel type for 250/930 color systems (0xARGB) (little endian) 
	GL_PIXEL_TYPE_ARGB8888 = 2	///< pixel type for full color color systems (0xAARRGGBB) (little endian) 
}T_GL_PIXEL_TYPE;


/** Possible screen orientation */
typedef enum T_GL_SCREEN_ORIENTATION
{
	GL_SCREEN_ORIENTATION_UP    = 0, ///< Normal orientation
	GL_SCREEN_ORIENTATION_LEFT  = 1, ///< Screen rotated left (counterclockwise)
	GL_SCREEN_ORIENTATION_RIGHT = 2, ///< Screen rotated right (clockwise)
	GL_SCREEN_ORIENTATION_DOWN  = 4  ///< Screen is top bottom reverted
}T_GL_SCREEN_ORIENTATION;

/** The identifier identifies a widget in a tree, the identifier must be unique.
The identifier are user-defined. 
Some identifiers are reserved to identify certain widgets in the skin, avoid using the identifier.
(See specials value @ref GL_ID_UNDEFINED, reserved value @ref GL_ID_SKIN_START .. @ref GL_ID_SKIN_STOP) */
#ifndef SWIG
typedef unsigned long T_GL_ID;
#endif

/*<ALL>
	Enum("BOOL","boolean",    
		Define("true",             "1",          "True value"),
		Define("false",            "0",          "False value"),
		),  
</ALL>*/
/** @cond GL_Ignore */
#ifdef WIN32
	#ifndef __cplusplus
		typedef unsigned char bool;
	#endif
	typedef unsigned char  byte;
#else
	#include "typ.h"
#endif

#ifndef __cplusplus
	#define true 1
	#define false 0
#endif

#ifndef SWIG

typedef unsigned long  T_GL_WCHAR; ///< Unicode character value
typedef unsigned long  wchar; ///< Unicode character value
typedef unsigned int   uint;
typedef unsigned long  ulong;
typedef unsigned short ushort;
typedef void *         pvoid;
#endif 
#ifndef NULL
	#define NULL (0L)
#endif
#define TL_TIMEOUT_INFINITE (ulong)(-1)
/** @endcond */

/**
@}
@addtogroup GL_TypesEvents Events type
@{
*/

/** Types of event (see documentation @ref GL_Widget_CommonMessage) */
typedef enum T_GL_EVENT_TYPE
{
	GL_EVENT_NONE                 = 0,     ///< Event not defined
	GL_EVENT_STYLUS_MOVE          = 3,     ///< The stylus moved on the screen 
	GL_EVENT_STYLUS_DOWN          = 4,     ///< The stylus pressed on the screen
	GL_EVENT_STYLUS_UP            = 5,     ///< The stylus removed from the screen
	GL_EVENT_KEY_DOWN             = 6,     ///< The key pressed on keyboard
	GL_EVENT_KEY_UP               = 7,     ///< The key released on keyboard
	GL_EVENT_TIMER_OUT            = 8,     ///< The timer is out
	GL_EVENT_PAINT                = 9,     ///< The window must be repaint
	GL_EVENT_EXIT                 = 10,    ///< The button "close" on the main window has been clicked (WIN32 only)
	GL_EVENT_WINDOW_LEAVE         = 12,    ///< The stylus enters the bounding area of a window
	GL_EVENT_WINDOW_ENTER         = 13,    ///< The stylus leaves the bounding area of a window
	GL_EVENT_USERAREA_CHANGED     = 14,    ///< The User Area changed
	GL_EVENT_TOUCH_PHY            = 15,    ///< Physical event on the touchscreen
	GL_EVENT_ORIENTATION_CHANGE   = 16,    ///< The Screen orientation will change

	GL_EVENT_VERTICAL_SCROLL      = 101,   ///< The view or scrollbar moved vertically
	GL_EVENT_HORIZONTAL_SCROLL    = 102,   ///< The view or scrollbar moved horizontally
	GL_EVENT_STYLUS_CLICK         = 103,   ///< The widget clicked
	GL_EVENT_STYLUS_SCROLL        = 104,   ///< The scrolling request was done by the stylus (stylus down, long stylus move, stylus up)
	GL_EVENT_FOCUS_KEY            = 105,   ///< The change in focus is due to key pressed (used to move the scrolled view to the widget focused)
	GL_EVENT_VALID                = 106,   ///< The button valid (green) clicked on virtual keyboard
	GL_EVENT_CANCEL               = 107,   ///< The button cancel (red) clicked on virtual keyboard
	GL_EVENT_FOCUS                = 108,   ///< The widget received focus
	GL_EVENT_UNFOCUS              = 109,   ///< The widget lost focus
	GL_EVENT_INACTIVITY           = 110,   ///< No user action detected for the specified time (@ref GL_Window_SetInactivityDuration, @ref GL_RESULT_INACTIVITY)
	GL_EVENT_STYLUS_LEAVE         = 111,   ///< The stylus enters the bounding area of a widget
	GL_EVENT_STYLUS_ENTER         = 112,   ///< The stylus leaves the bounding area of a widget
	GL_EVENT_BREAK                = 113,   ///< The events are popped before stacking other
	GL_EVENT_CHECKED              = 114,   ///< The widget is checked
	GL_EVENT_UNCHECKED            = 115,   ///< The widget is unchecked
	GL_EVENT_MEDIA_ENDED          = 116,   ///< The video or audio ended
	GL_EVENT_DATA                 = 117,   ///< The message contains data attached
	GL_EVENT_TEXT_CHANGED         = 118,   ///< The text in the input field has changed
	
	GL_EVENT_ALL                  = 0xFFFF ///< This definition is used to catch several events with a single callback
} T_GL_EVENT_TYPE;


/* Stylus button bits*/ // NEVER MODIFY THESE DEFINITIONS
#define GL_STYLUS_BUTTON_LEFT    0x04 ///< Stylus button left
#define GL_STYLUS_BUTTON_MIDDLE  0x02 ///< Stylus button middle
#define GL_STYLUS_BUTTON_RIGHT   0x01 ///< Stylus button right

/**
@}
@addtogroup GL_TypesCursor Cursor
@{
*/

/** Stylus cursor type */
typedef enum T_GL_CURSOR 
{
	GL_CURSOR_NONE,   ///< No cursor displayed
	GL_CURSOR_ARROW,  ///< Stylus arrow cursor displayed
	GL_CURSOR_DOT,    ///< Stylus dot cursor displayed
	GL_CURSOR_CROSS   ///< Stylus cross cursor displayed
} T_GL_CURSOR;

/**
@}
@addtogroup GL_TypesColorsType Color type
@{
*/

#ifndef SWIG
/** Definition of a color. The color-coded and contains 4 bytes: alpha, red, green and blue (0xAARRGGBB) */
typedef unsigned long T_GL_COLOR;

/** Handle on the color */
typedef T_GL_COLOR * T_GL_HCOLOR;
#endif


/**
@}
@addtogroup GL_SkinColors
@{

If you use these color values??, they will be automatically replaced with specified color in the skin.
The link between these colors and colors displayed is described in the file @ref GL_SkinColorsJs.

*/


#define GL_COLOR_LABEL_TEXT                  ((T_GL_COLOR)0x00000001)  //!< Text label color (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_KEY_FOCUS                   ((T_GL_COLOR)0x00000002)  //!< Focus color of a key on the virtual keyboard (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_KEY_TEXT                    ((T_GL_COLOR)0x00000003)  //!< Text color of a key on the virtual keyboard (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_WINDOW_BACKGROUND           ((T_GL_COLOR)0x00000004)  //!< Window background color (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_WINDOW_BORDER               ((T_GL_COLOR)0x00000005)  //!< Window border color (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_WINDOW_TEXT                 ((T_GL_COLOR)0x00000006)  //!< Window text color (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_SIGNATURE_INK               ((T_GL_COLOR)0x00000007)  //!< Ink color of the signature capture (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_SIGNATURE_BORDER            ((T_GL_COLOR)0x00000008)  //!< Border color of the signature capture (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_SIGNATURE_BACKGROUND        ((T_GL_COLOR)0x00000009)  //!< Background color of the signature capture (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_PALETTE_FOCUS               ((T_GL_COLOR)0x0000000A)  //!< Focus color on the palette (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_PALETTE_FOCUS_BORDER        ((T_GL_COLOR)0x0000000B)  //!< Border focus color on the palette (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_EDIT_TEXT                   ((T_GL_COLOR)0x0000000C)  //!< Edit text color (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_BUTTON_TEXT                 ((T_GL_COLOR)0x0000000D)  //!< Button text color (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_DIALOG_TEXT                 ((T_GL_COLOR)0x0000000E)  //!< Dialog text color (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_DIALOG_TEXT_BACKGROUND      ((T_GL_COLOR)0x0000000F)  //!< Dialog text background color (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_PROGRESS_TEXT               ((T_GL_COLOR)0x00000010)  //!< Progress bar text color (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_PROGRESS_TEXT_BACKGROUND    ((T_GL_COLOR)0x00000011)  //!< Progress text background color (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_DIALOG_HELP_TEXT            ((T_GL_COLOR)0x00000012)  //!< Dialog help text color (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_DIALOG_HELP_TEXT_BACKGROUND ((T_GL_COLOR)0x00000013)  //!< Dialog help text background color (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_PRINT_TEXT                  ((T_GL_COLOR)0x00000014)  //!< Printing text color (The exact value of the color is extracted directly from the skin loaded)
#define GL_COLOR_LAST_SKINED                 ((T_GL_COLOR)0x00000100)  //!< Last skined color

/**
@}
@addtogroup GL_TypesColors Colors
@{
*/


#define GL_COLOR_ALICE_BLUE              ((T_GL_COLOR)0xFFF0F8FF)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="AliceBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_ANTIQUE_WHITE           ((T_GL_COLOR)0xFFFAEBD7)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="AntiqueWhite">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_AQUA                    ((T_GL_COLOR)0xFF00FFFF)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Aqua">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_AQUAMARINE              ((T_GL_COLOR)0xFF7FFFD4)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Aquamarine">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_AZURE                   ((T_GL_COLOR)0xFFF0FFFF)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Azure">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_BEIGE                   ((T_GL_COLOR)0xFFF5F5DC)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Beige">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_BISQUE                  ((T_GL_COLOR)0xFFFFE4C4)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Bisque">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_BLACK                   ((T_GL_COLOR)0xFF000000)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Black">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_BLANCHED_ALMOND         ((T_GL_COLOR)0xFFFFEBCD)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="BlanchedAlmond">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_BLUE                    ((T_GL_COLOR)0xFF0000FF)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Blue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_BLUE_VIOLET             ((T_GL_COLOR)0xFF8A2BE2)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="BlueViolet">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_BROWN                   ((T_GL_COLOR)0xFFA52A2A)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Brown">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_BURLY_WOOD              ((T_GL_COLOR)0xFFDEB887)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="BurlyWood">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_CADET_BLUE              ((T_GL_COLOR)0xFF5F9EA0)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="CadetBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_CHARTREUSE              ((T_GL_COLOR)0xFF7FFF00)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Chartreuse">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_CHOCOLATE               ((T_GL_COLOR)0xFFD2691E)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Chocolate">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_CORAL                   ((T_GL_COLOR)0xFFFF7F50)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Coral">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_CORNFLOWER_BLUE         ((T_GL_COLOR)0xFF6495ED)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="CornflowerBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_CORNSILK                ((T_GL_COLOR)0xFFFFF8DC)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Cornsilk">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_CRIMSON                 ((T_GL_COLOR)0xFFDC143C)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Crimson">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_CYAN                    ((T_GL_COLOR)0xFF00FFFF)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Cyan">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_BLUE               ((T_GL_COLOR)0xFF00008B)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_CYAN               ((T_GL_COLOR)0xFF008B8B)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkCyan">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_GOLDEN_ROD         ((T_GL_COLOR)0xFFB8860B)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkGoldenRod">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_GRAY               ((T_GL_COLOR)0xFFA9A9A9)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkGray">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_GREEN              ((T_GL_COLOR)0xFF006400)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_KHAKI              ((T_GL_COLOR)0xFFBDB76B)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkKhaki">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_MAGENTA            ((T_GL_COLOR)0xFF8B008B)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkMagenta">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_OLIVE_GREEN        ((T_GL_COLOR)0xFF556B2F)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkOliveGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_ORANGE             ((T_GL_COLOR)0xFFFF8C00)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Darkorange">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_ORCHID             ((T_GL_COLOR)0xFF9932CC)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkOrchid">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_RED                ((T_GL_COLOR)0xFF8B0000)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkRed">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_SALMON             ((T_GL_COLOR)0xFFE9967A)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkSalmon">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_SEA_GREEN          ((T_GL_COLOR)0xFF8FBC8F)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkSeaGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_SLATE_BLUE         ((T_GL_COLOR)0xFF483D8B)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkSlateBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_SLATE_GRAY         ((T_GL_COLOR)0xFF2F4F4F)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkSlateGray">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_TURQUOISE          ((T_GL_COLOR)0xFF00CED1)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkTurquoise">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DARK_VIOLET             ((T_GL_COLOR)0xFF9400D3)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DarkViolet">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DEEP_PINK               ((T_GL_COLOR)0xFFFF1493)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DeepPink">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DEEP_SKY_BLUE           ((T_GL_COLOR)0xFF00BFFF)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DeepSkyBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DIM_GRAY                ((T_GL_COLOR)0xFF696969)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DimGray">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_DODGER_BLUE             ((T_GL_COLOR)0xFF1E90FF)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="DodgerBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_FELDSPAR                ((T_GL_COLOR)0xFFD19275)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Feldspar">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_FIRE_BRICK              ((T_GL_COLOR)0xFFB22222)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="FireBrick">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_FLORAL_WHITE            ((T_GL_COLOR)0xFFFFFAF0)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="FloralWhite">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_FOREST_GREEN            ((T_GL_COLOR)0xFF228B22)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="ForestGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_FUCHSIA                 ((T_GL_COLOR)0xFFFF00FF)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Fuchsia">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_GAINSBORO               ((T_GL_COLOR)0xFFDCDCDC)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Gainsboro">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_GHOST_WHITE             ((T_GL_COLOR)0xFFF8F8FF)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="GhostWhite">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_GOLD                    ((T_GL_COLOR)0xFFFFD700)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Gold">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_GOLDEN_ROD              ((T_GL_COLOR)0xFFDAA520)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="GoldenRod">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_GRAY                    ((T_GL_COLOR)0xFF808080)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Gray">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_GREEN                   ((T_GL_COLOR)0xFF008000)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Green">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_GREEN_YELLOW            ((T_GL_COLOR)0xFFADFF2F)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="GreenYellow">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_HONEY_DEW               ((T_GL_COLOR)0xFFF0FFF0)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="HoneyDew">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_HOT_PINK                ((T_GL_COLOR)0xFFFF69B4)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="HotPink">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_INDIAN_RED              ((T_GL_COLOR)0xFFCD5C5C)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="IndianRed">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_INDIGO                  ((T_GL_COLOR)0xFF4B0082)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Indigo">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_IVORY                   ((T_GL_COLOR)0xFFFFFFF0)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Ivory">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_KHAKI                   ((T_GL_COLOR)0xFFF0E68C)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Khaki">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LAVENDER                ((T_GL_COLOR)0xFFE6E6FA)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Lavender">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LAVENDER_BLUSH          ((T_GL_COLOR)0xFFFFF0F5)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LavenderBlush">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LAWN_GREEN              ((T_GL_COLOR)0xFF7CFC00)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LawnGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LEMON_CHIFFON           ((T_GL_COLOR)0xFFFFFACD)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LemonChiffon">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_BLUE              ((T_GL_COLOR)0xFFADD8E6)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_CORAL             ((T_GL_COLOR)0xFFF08080)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightCoral">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_CYAN              ((T_GL_COLOR)0xFFE0FFFF)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightCyan">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_GOLDEN_ROD_YELLOW ((T_GL_COLOR)0xFFFAFAD2)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightGoldenRodYellow">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_GRAY              ((T_GL_COLOR)0xFFD3D3D3)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightGrey">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_GREEN             ((T_GL_COLOR)0xFF90EE90)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_PINK              ((T_GL_COLOR)0xFFFFB6C1)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightPink">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_SALMON            ((T_GL_COLOR)0xFFFFA07A)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightSalmon">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_SEA_GREEN         ((T_GL_COLOR)0xFF20B2AA)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightSeaGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_SKY_BLUE          ((T_GL_COLOR)0xFF87CEFA)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightSkyBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_SLATE_BLUE        ((T_GL_COLOR)0xFF8470FF)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightSlateBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_SLATE_GRAY        ((T_GL_COLOR)0xFF778899)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightSlateGray">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_STEEL_BLUE        ((T_GL_COLOR)0xFFB0C4DE)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightSteelBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIGHT_YELLOW            ((T_GL_COLOR)0xFFFFFFE0)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LightYellow">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIME                    ((T_GL_COLOR)0xFF00FF00)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Lime">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LIME_GREEN              ((T_GL_COLOR)0xFF32CD32)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="LimeGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_LINEN                   ((T_GL_COLOR)0xFFFAF0E6)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Linen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MAGENTA                 ((T_GL_COLOR)0xFFFF00FF)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Magenta">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MAROON                  ((T_GL_COLOR)0xFF800000)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Maroon">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MEDIUM_AQUA_MARINE      ((T_GL_COLOR)0xFF66CDAA)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="MediumAquaMarine">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MEDIUM_BLUE             ((T_GL_COLOR)0xFF0000CD)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="MediumBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MEDIUM_ORCHID           ((T_GL_COLOR)0xFFBA55D3)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="MediumOrchid">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MEDIUM_PURPLE           ((T_GL_COLOR)0xFF9370D8)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="MediumPurple">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MEDIUM_SEA_GREEN        ((T_GL_COLOR)0xFF3CB371)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="MediumSeaGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MEDIUM_SLATE_BLUE       ((T_GL_COLOR)0xFF7B68EE)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="MediumSlateBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MEDIUM_SPRING_GREEN     ((T_GL_COLOR)0xFF00FA9A)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="MediumSpringGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MEDIUM_TURQUOISE        ((T_GL_COLOR)0xFF48D1CC)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="MediumTurquoise">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MEDIUM_VIOLET_RED       ((T_GL_COLOR)0xFFC71585)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="MediumVioletRed">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MIDNIGHT_BLUE           ((T_GL_COLOR)0xFF191970)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="MidnightBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MINT_CREAM              ((T_GL_COLOR)0xFFF5FFFA)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="MintCream">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MISTY_ROSE              ((T_GL_COLOR)0xFFFFE4E1)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="MistyRose">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_MOCCASIN                ((T_GL_COLOR)0xFFFFE4B5)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Moccasin">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_NAVAJO_WHITE            ((T_GL_COLOR)0xFFFFDEAD)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="NavajoWhite">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_NAVY                    ((T_GL_COLOR)0xFF000080)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Navy">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_OLD_LACE                ((T_GL_COLOR)0xFFFDF5E6)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="OldLace">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_OLIVE                   ((T_GL_COLOR)0xFF808000)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Olive">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_OLIVE_DRAB              ((T_GL_COLOR)0xFF6B8E23)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="OliveDrab">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_ORANGE                  ((T_GL_COLOR)0xFFFFA500)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Orange">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_ORANGE_RED              ((T_GL_COLOR)0xFFFF4500)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="OrangeRed">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_ORCHID                  ((T_GL_COLOR)0xFFDA70D6)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Orchid">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_PALE_GOLDEN_ROD         ((T_GL_COLOR)0xFFEEE8AA)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="PaleGoldenRod">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_PALE_GREEN              ((T_GL_COLOR)0xFF98FB98)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="PaleGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_PALE_TURQUOISE          ((T_GL_COLOR)0xFFAFEEEE)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="PaleTurquoise">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_PALE_VIOLET_RED         ((T_GL_COLOR)0xFFD87093)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="PaleVioletRed">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_PAPAYA_WHIP             ((T_GL_COLOR)0xFFFFEFD5)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="PapayaWhip">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_PEACH_PUFF              ((T_GL_COLOR)0xFFFFDAB9)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="PeachPuff">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_PERU                    ((T_GL_COLOR)0xFFCD853F)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Peru">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_PINK                    ((T_GL_COLOR)0xFFFFC0CB)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Pink">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_PLUM                    ((T_GL_COLOR)0xFFDDA0DD)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Plum">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_POWDER_BLUE             ((T_GL_COLOR)0xFFB0E0E6)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="PowderBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_PURPLE                  ((T_GL_COLOR)0xFF800080)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Purple">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_RED                     ((T_GL_COLOR)0xFFFF0000)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Red">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_ROSY_BROWN              ((T_GL_COLOR)0xFFBC8F8F)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="RosyBrown">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_ROYAL_BLUE              ((T_GL_COLOR)0xFF4169E1)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="RoyalBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_SADDLE_BROWN            ((T_GL_COLOR)0xFF8B4513)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="SaddleBrown">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_SALMON                  ((T_GL_COLOR)0xFFFA8072)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Salmon">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_SANDY_BROWN             ((T_GL_COLOR)0xFFF4A460)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="SandyBrown">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_SEA_GREEN               ((T_GL_COLOR)0xFF2E8B57)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="SeaGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_SEA_SHELL               ((T_GL_COLOR)0xFFFFF5EE)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="SeaShell">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_SIENNA                  ((T_GL_COLOR)0xFFA0522D)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Sienna">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_SILVER                  ((T_GL_COLOR)0xFFC0C0C0)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Silver">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_SKY_BLUE                ((T_GL_COLOR)0xFF87CEEB)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="SkyBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_SLATE_BLUE              ((T_GL_COLOR)0xFF6A5ACD)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="SlateBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_SLATE_GRAY              ((T_GL_COLOR)0xFF708090)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="SlateGray">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_SNOW                    ((T_GL_COLOR)0xFFFFFAFA)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Snow">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_SPRING_GREEN            ((T_GL_COLOR)0xFF00FF7F)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="SpringGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_STEEL_BLUE              ((T_GL_COLOR)0xFF4682B4)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="SteelBlue">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_TAN                     ((T_GL_COLOR)0xFFD2B48C)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Tan">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_TEAL                    ((T_GL_COLOR)0xFF008080)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Teal">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_THISTLE                 ((T_GL_COLOR)0xFFD8BFD8)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Thistle">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_TOMATO                  ((T_GL_COLOR)0xFFFF6347)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Tomato">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_TURQUOISE               ((T_GL_COLOR)0xFF40E0D0)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Turquoise">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_VIOLET                  ((T_GL_COLOR)0xFFEE82EE)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Violet">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_VIOLET_RED              ((T_GL_COLOR)0xFFD02090)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="VioletRed">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_WHEAT                   ((T_GL_COLOR)0xFFF5DEB3)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Wheat">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_WHITE                   ((T_GL_COLOR)0xFFFFFFFF)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="White">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_WHITE_SMOKE             ((T_GL_COLOR)0xFFF5F5F5)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="WhiteSmoke">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_YELLOW                  ((T_GL_COLOR)0xFFFFFF00)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Yellow">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_YELLOW_GREEN            ((T_GL_COLOR)0xFF9ACD32)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="YellowGreen">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_TRANSPARENT             ((T_GL_COLOR)0x00000000)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Transparent">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>
#define GL_COLOR_OPAQUE                  ((T_GL_COLOR)0xFF000000)  //!< <table border="1" cellspacing="0" cellpadding="0"><tr><td bgcolor="Opaque">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></table>

/**
@}
@addtogroup GL_TypesColorsMacro Colors macro
@{
*/

/** Indicates if the color is visible */
#define GL_COLOR_IS_VISIBLE(color) (GL_COLOR_BLACK & color)

/** Gets the alpha channel of color */
#define GL_COLOR_GET_ALPHA(color) ((unsigned char)(((color) & 0xFF000000) >> 24))

/** Gets the red channel of color */
#define GL_COLOR_GET_RED(color)   ((unsigned char)(((color) & 0x00FF0000) >> 16))

/** Gets the green channel of color */
#define GL_COLOR_GET_GREEN(color) ((unsigned char)(((color) & 0x0000FF00) >>  8))

/** Gets the blue channel of color */
#define GL_COLOR_GET_BLUE(color)  ((unsigned char)(((color) & 0x000000FF)      ))


/** Sets the alpha channel of color */
#define GL_COLOR_SET_ALPHA(color, channel) (((color) & 0x00FFFFFF) | (T_GL_COLOR)((channel) << 24))

/** Sets the red channel of color */
#define GL_COLOR_SET_RED(color, channel)   (((color) & 0xFF00FFFF) | (T_GL_COLOR)((channel) << 16))

/** Sets the green channel of color */
#define GL_COLOR_SET_GREEN(color, channel) (((color) & 0xFFFF00FF) | (T_GL_COLOR)((channel) <<  8))

/** Sets the blue channel of color */
#define GL_COLOR_SET_BLUE(color, channel)  (((color) & 0xFFFFFF00) | (T_GL_COLOR)((channel)      ))


/** Created a color according to its channels */
#define GL_COLOR_CREATE(alpha, red, green, blue) \
	(\
	(((T_GL_COLOR)(alpha)) << 24) | \
	(((T_GL_COLOR)(red))   << 16) | \
	(((T_GL_COLOR)(green)) <<  8) | \
	(((T_GL_COLOR)(blue))       ) \
	)

/**
@}
@addtogroup GL_TypesTime Time definitions
@{
*/
/** Duration in milliseconds */
typedef ulong T_GL_DURATION;

/** Infinite duration in milliseconds */
#define GL_TIME_INFINITE ((T_GL_DURATION)(-1))

/** Second duration in milliseconds */
#define GL_TIME_SECOND ((T_GL_DURATION)1000)

/** Minute duration in milliseconds */
#define GL_TIME_MINUTE ((T_GL_DURATION)(60*GL_TIME_SECOND))

/**
@}
@addtogroup GL_TypesTerminal Terminal definitions
@{
*/

#define GL_TERMINAL_SMART     "EFTSmart"  ///< terminal type EFTSmart
#define GL_TERMINAL_EFT30F    "EFT30"     ///< terminal type EFT30F
#define GL_TERMINAL_EFT30PLUS "EFT30PLUS" ///< terminal type EFT30PLUS
#define GL_TERMINAL_TWIN30    "Twin30"    ///< terminal type Twin30
#define GL_TERMINAL_TWIN31    "Twin31"    ///< terminal type Twin31
#define GL_TERMINAL_TWIN32    "Twin32"    ///< terminal type Twin32
#define GL_TERMINAL_TWIN33    "Twin33"    ///< terminal type Twin33
#define GL_TERMINAL_EFT930G   "EFT930G"   ///< terminal type EFT930G
#define GL_TERMINAL_EFT930B   "EFT930B"   ///< terminal type EFT930B
#define GL_TERMINAL_EFT930S   "EFT930S"   ///< terminal type EFT930S
#define GL_TERMINAL_EFT930W   "EFT930W"   ///< terminal type EFT930W
#define GL_TERMINAL_EFT930P   "EFT930P"   ///< terminal type EFT930P
#define GL_TERMINAL_ML30      "ML30"      ///< terminal type ML30
#define GL_TERMINAL_SPM       "SPM"       ///< terminal type SPM
#define GL_TERMINAL_IPP320    "iPP320"    ///< terminal type iPP320
#define GL_TERMINAL_IPP350    "iPP350"    ///< terminal type iPP350
#define GL_TERMINAL_CAD30     "CAD30UCM"  ///< terminal type CAD30
#define GL_TERMINAL_MR40      "MR40"      ///< terminal type MR40
#define GL_TERMINAL_IWL220    "iWL220"    ///< terminal type iWL220
#define GL_TERMINAL_IWL250    "iWL250"    ///< terminal type iWL250
#define GL_TERMINAL_IWL280    "iWL280"    ///< terminal type iWL280
#define GL_TERMINAL_IWL350    "iWL350"    ///< terminal type iWL350
#define GL_TERMINAL_ICT220    "iCT220"    ///< terminal type iCT220
#define GL_TERMINAL_ICT250    "iCT250"    ///< terminal type iCT250
#define GL_TERMINAL_ISC350    "iSC350"    ///< terminal type iSC350
#define GL_TERMINAL_ISC250    "iSC250"    ///< terminal type iSC250
#define GL_TERMINAL_E560      "E560"      ///< terminal type E560
#define GL_TERMINAL_E532      "E532"      ///< terminal type E532
#define GL_TERMINAL_IMP320    "iMP320"    ///< terminal type iMP320
#define GL_TERMINAL_IMP350    "iMP350"    ///< terminal type iMP350
#define GL_TERMINAL_IPP480    "iPP480"    ///< terminal type iPP480
#define GL_TERMINAL_IST150    "iST150"    ///< terminal type iST150
#define GL_TERMINAL_IUP250    "iUP250"    ///< terminal type iUP250
#define GL_TERMINAL_IUC180    "iUC180"    ///< terminal type iUC180

/**
@}
@addtogroup GL_TypesFile File definitions
@{
*/

/** Time Value */
typedef long long T_GL_TIME;


/** time structure used for GL_File_GetTime*/
typedef struct T_GL_FILE_TIME
{
	T_GL_TIME accessTime;        ///< last access time
	T_GL_TIME modifiedTime;      ///< las modified time
	T_GL_TIME creationTime;      ///< creation time
}T_GL_FILE_TIME;

/** Opening mode used in GL_File_Open */
typedef enum T_GL_FILE_OPEN_MODE
{
	GL_FILE_CREATE_NEW = 1,     ///< Create a new file exit with NULL if error or already exsists
	GL_FILE_CREATE_ALWAYS,      ///< Create a new file or truncate existing file
	GL_FILE_OPEN_EXISTING,      ///< Open an existing file or NULL if not exists
	GL_FILE_OPEN_ALWAYS,        ///< Open an existing file or create a new
	GL_FILE_TRUNCATE_EXISTING   ///< Open an existing file or NULL if not exists and truncate file
}T_GL_FILE_OPEN_MODE;

/** Access mode used in GL_File_Open */
typedef enum T_GL_FILE_ACCESS
{
	GL_FILE_ACCESS_READ  = 1,   ///< Open file for reading
	GL_FILE_ACCESS_WRITE,       ///< Open file for writing
	GL_FILE_ACCESS_READ_WRITE   ///< Open file for reading and writing
}T_GL_FILE_ACCESS;

/** Position mode used in GL_File_Seek */
typedef enum T_GL_FILE_POS
{
	GL_FILE_SEEK_BEGIN = 1,     ///< Seek from the beginning of the file
	GL_FILE_SEEK_CURRENT,       ///< Seek from current position in the file
	GL_FILE_SEEK_END            ///< Seek from end of file
}T_GL_FILE_POS;


/** Indicates the "Byte Order Mark".
The byte order mark (BOM) is a Unicode character used to signal the endianness 
(byte order) of a text file or stream. Its code point is U+FEFF. 
BOM use is optional, and, if used, should appear at the start of the text stream. 
Beyond its specific use as a byte-order indicator, the BOM character may also 
indicate which of the several Unicode representations the text is encoded in. */
typedef enum T_GL_ENCODING_BOM
{
	GL_ENCODING_UNKNOWN_BOM,       ///< The BOM is not identified 
	GL_ENCODING_UTF8_BOM,          ///< The file is encoding in UTF8
	GL_ENCODING_UTF16_BIG_BOM,     ///< The file is encoding in UTF16 big endian
	GL_ENCODING_UTF16_LITTLE_BOM,  ///< The file is encoding in UTF16 little endian
	GL_ENCODING_UTF32_BIG_BOM,     ///< The file is encoding in UTF32 big endian
	GL_ENCODING_UTF32_LITTLE_BOM   ///< The file is encoding in UTF32 little endian
} T_GL_ENCODING_BOM;


#define GL_ROOT_VFS_RAM     "rdd"    ///< prefix to use for file in ram   : VFS/Rdd0a/mypath
#define GL_ROOT_VFS_FLASH   "infd"   ///< prefix to use for file in flash : /Infd0a/mypath
#define GL_ROOT_VFS_MMC     "mmcd"   ///< prefix to use for file in ram   : /Mmcd0a/mypath
#define GL_ROOT_VFS_USB     "umsd"   ///< prefix to use for file in ram   : /Umsd0a/mypath
#define GL_ROOT_PARAM       "param"  ///< prefix to use for file in param : /param/myfile
#define GL_ROOT_FFMS_RAM    "ram/"   ///< prefix to use for file in ram   : /ram/mydisk/myfile
#define GL_ROOT_FFMS_FLASH  "flash/" ///< prefix to use for file in flash : /flash/mydisk/myfile

#define GL_URL_FILE         "file://" ///< the url contains a filename
#define GL_URL_DIR          "dir://"  ///< the url contains a directory
#define GL_URL_DAL          "dal://"  ///< the url contains a dal identifier name
#define GL_URL_SKIN         "skin://" ///< the url is used to access data stored in the skin

/**
@}
@addtogroup GL_TypesMimes Images MIME types
@{
*/

#define GL_MIME_IMAGE_WGU "image/wgu"  ///< MIME type for the wgu image codec
#define GL_MIME_IMAGE_BMP "image/bmp"  ///< MIME type for the bitmap image codec
#define GL_MIME_IMAGE_PNG "image/png"  ///< MIME type for the portable network graphic image codec
#define GL_MIME_IMAGE_JPG "image/jpeg" ///< MIME type for the jpeg image codec
#define GL_MIME_IMAGE_GIF "image/gif"  ///< MIME type for the gif image codec

/**
@}
@addtogroup GL_TypesMimesBarcode Barcode MIME types
@{
*/

#define GL_MIME_BARCODE_QR      "barcode/qr"       ///< MIME type for the barcode QR codec
#define GL_MIME_BARCODE_PDF417  "barcode/pdf417"   ///< MIME type for the barcode pdf417 codec
#define GL_MIME_BARCODE_EAN8    "barcode/ean8"     ///< MIME type for the barcode ean 8 codec
#define GL_MIME_BARCODE_EAN13   "barcode/ean13"    ///< MIME type for the barcode ean 13 codec
#define GL_MIME_BARCODE_CODE25  "barcode/code25"   ///< MIME type for the barcode code 25 codec
#define GL_MIME_BARCODE_CODE39  "barcode/code39"   ///< MIME type for the barcode code 39 codec
#define GL_MIME_BARCODE_CODE128 "barcode/code128"  ///< MIME type for the barcode code 128 codec

/**
@}
@addtogroup GL_ParamBarcodeQr Barcode QR parameters
@{
*/

#define GL_BARCODE_VALUE                "value"           ///< Value of the barcode (Binary buffer)
#define GL_BARCODE_FORECOLOR            "forecolor"       ///< Pixel color of the barcode

#define GL_BARCODE_QR_VERSION           "version"         ///< Version of the symbol. If 0, the library chooses the minimum version for the given input data. (Integer)
#define GL_BARCODE_QR_ERROR_LEVEL       "errorlevel"      ///< Error correction level (@ref T_GL_BARCODE_QR_ERROR_LEVEL) (Integer)
#define GL_BARCODE_QR_ENCODING_MODE     "encoding"        ///< Encoding Mode (@ref T_GL_BARCODE_QR_ENCODING_MODE) (Integer)
#define GL_BARCODE_QR_CASESENSITIVE     "casesensitive"   ///< Case-sensitive(1) or not(0) (Integer)
#define GL_BARCODE_QR_PIXEL_SIZE        "pixelsize"       ///< Minimal size of pixel (Integer)
#define GL_BARCODE_QR_MARGIN            "margin"          ///< Space in pixel of the margin (Integer)

/** QR barcode error correction level */
typedef enum T_GL_BARCODE_QR_ERROR_LEVEL
{
	GL_BARCODE_QR_ERROR_UKNOWN = -1, ///< level not specified
	GL_BARCODE_QR_ERROR_L = 0,       ///< lowest, 7 % of recovery
	GL_BARCODE_QR_ERROR_M = 1,       ///< 15 % of recovery
	GL_BARCODE_QR_ERROR_Q = 2,       ///< 25 % of recovery
	GL_BARCODE_QR_ERROR_H = 3        ///< highest, 30 % of recovery
} T_GL_BARCODE_QR_ERROR_LEVEL;


/** QR barcode encoding mode  (tell the library how non-alphanumerical characters should be encoded. ) */
typedef enum T_GL_BARCODE_QR_ENCODING_MODE
{
	GL_BARCODE_QR_ENCODING_MODE_NUL           = -1, ///< Terminator (NUL character). Internal use only
	GL_BARCODE_QR_ENCODING_MODE_NUMERIC       = 0,  ///< Numeric mode
	GL_BARCODE_QR_ENCODING_MODE_ALPHANUMERIC  = 1,  ///< Alphabet-numeric mode
	GL_BARCODE_QR_ENCODING_MODE_BYTE          = 2,  ///< 8-bit data mode, all of non-alphanumerical characters will be encoded as is. If you want to embed UTF-8 string, choose this.
	GL_BARCODE_QR_ENCODING_MODE_KANJI         = 3,  ///< Kanji (shift-jis) mode, kanji characters will be encoded as Shif-JIS characters. 
	GL_BARCODE_QR_ENCODING_MODE_STRUCTURE     = 4   ///< Internal use only
} T_GL_BARCODE_QR_ENCODING_MODE;

/**
@}
@addtogroup GL_ParamBarcodePdf417 Barcode PDF417 parameters
@{
*/
#define GL_BARCODE_PDF417_COLUMNS       "columns"         ///< Number of columns (Ranged integer from 1 to 30)
#define GL_BARCODE_PDF417_ROWS          "rows"            ///< Number of rows (Ranged integer from 30 to 90)
#define GL_BARCODE_PDF417_CORRECTION    "correctionlevel" ///< error correction level (Ranged integer from 1 to 8)

/**
@}
@addtogroup GL_ParamBarcode1D Barcode one dimension parameters
@{
*/

#define GL_BARCODE_1D_SIDE_MARGIN      "sidemargin"      ///< Space in pixel of the left and right margin for 1D barcodes (Integer)

/**
@}
@addtogroup GL_ParamBarcode25 Barcode code 25 parameters
@{
*/

#define GL_BARCODE_CODE25_CHECKSUM      "checksum"        ///< Activate checksum for code 25 barcodes (Integer)

/**
@}
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_CommonTypes_h_INCLUDED
