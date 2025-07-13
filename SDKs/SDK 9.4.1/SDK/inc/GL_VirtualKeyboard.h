// $Id: GL_VirtualKeyboard.h,v 1.1.2.32 2012/05/23 07:03:48 rbertholet Exp $
// Graphic Object virtual keyboard
#ifndef GL_VirtualKeyboard_h_INCLUDED
#define GL_VirtualKeyboard_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_VirtualKeyboard
@{
@addtogroup GL_VirtualKeyboardDoc Virtual keyboard
@{

The virtual keyboard allows easy entry of special characters. It also allows direct input with the stylus.

Below is a list of specific functions to this class :
	- @ref GL_VirtualKeyboard_Create : Creating a virtual keyboard
	- @ref GL_VirtualKeyboard_AddPage : Adds a new page in virtual keyboard
	- @ref GL_VirtualKeyboard_ClearPages : Removes all pages in the virtual keyboard

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_FocusProperties
	- @ref GL_Widget_TextProperties
	- @ref GL_Widget_InputProperties
	- @ref GL_Widget_CallbackProperties

Methods inherited from class widget :
	- @ref GL_Widget_GetSize
	- @ref GL_Widget_SetSize
	- @ref GL_Widget_GetMinSize
	- @ref GL_Widget_SetMinSize
	- @ref GL_Widget_GetMaxSize
	- @ref GL_Widget_SetMaxSize
	- @ref GL_Widget_GetPosition
	- @ref GL_Widget_SetPosition
	- @ref GL_Widget_GetVisible
	- @ref GL_Widget_SetVisible
	- @ref GL_Widget_GetItem
	- @ref GL_Widget_SetItem
	- @ref GL_Widget_GetBackAlign
	- @ref GL_Widget_SetBackAlign
	- @ref GL_Widget_GetForeAlign
	- @ref GL_Widget_SetForeAlign
	- @ref GL_Widget_Destroy
	- @ref GL_Widget_GetWindow
	- @ref GL_Widget_SetMargins
	- @ref GL_Widget_GetMargins
	- @ref GL_Widget_GetId
	- @ref GL_Widget_SetId
	- @ref GL_Widget_SearchId
	- @ref GL_Widget_GetBackColor
	- @ref GL_Widget_SetBackColor
	- @ref GL_Widget_GetForeColor
	- @ref GL_Widget_SetForeColor
	- @ref GL_Widget_SetShrink
	- @ref GL_Widget_GetShrink
	- @ref GL_Widget_SetGrow
	- @ref GL_Widget_GetGrow
	- @ref GL_Widget_SetExpand
	- @ref GL_Widget_GetExpand
	- @ref GL_Widget_SetText
	- @ref GL_Widget_GetText
	- @ref GL_Widget_SetTextAlign
	- @ref GL_Widget_GetTextAlign
	- @ref GL_Widget_SetFontName
	- @ref GL_Widget_GetFontName
	- @ref GL_Widget_SetFontSize
	- @ref GL_Widget_GetFontSize
	- @ref GL_Widget_SetFontStyle
	- @ref GL_Widget_GetFontStyle
	- @ref GL_Widget_SetMask
	- @ref GL_Widget_SetFillChar1
	- @ref GL_Widget_GetFillChar1
	- @ref GL_Widget_SetFillChar2
	- @ref GL_Widget_GetFillChar2
	- @ref GL_Widget_SetPasswordChar
	- @ref GL_Widget_GetPasswordChar
	- @ref GL_Widget_SetMode
	- @ref GL_Widget_GetMode
	- @ref GL_Widget_SetInput
	- @ref GL_Widget_GetInput
	- @ref GL_Widget_SelectAll
	- @ref GL_Widget_SetUserData
	- @ref GL_Widget_GetUserData
	- @ref GL_Widget_SetClickable
	- @ref GL_Widget_GetClickable
	- @ref GL_Widget_SetClickSensitive
	- @ref GL_Widget_GetClickSensitive
	- @ref GL_Widget_ReadResource
	- @ref GL_Widget_InstanciateResource
	- @ref GL_Widget_SetFontScale
	- @ref GL_Widget_SetUserChar
	- @ref GL_Widget_GetUserChar

For messages sent by this widget see @ref GL_Widget_CommonMessage

<h2>Sample</h2>

	Below is an example of creating a virtual keyboard with a button. You leave this window by pressing a button valid.

	@image html virtualKeyboardTest.png

	@include GL_SampleVirtualKeyboard.c


	Below is an example if you want to create your own custom keyboard

	@image html virtualKeyboardTest2.png

	@include GL_SampleCustomVirtualKeyboard.c

	Below is an example if you want to create your keyboard by defining a mask user

	@image html virtualKeyboardTest3.png

	@include GL_SampleUserMaskVirtualKeyboard.c

@}
*/

/*<ALL>
	Struct("MAPPAGE",                               "Page of characters displayed on the virtual keyboard",
		String("name",                           "Page name displayed in the button page selection"),
		String("mapping",                        "List of characters in the page content, use \\\\n to change the line, use \\\\uXXXX to enter an unicode value"),
		),

	List("PAGES",                               "List of drawing actions",
		Item("mappage",                "MAPPAGE",    "Mapping definition of the binary virtual keyboard"),
	),

	Extension("VIRTUALKEYBOARD",   "WIDGET",     "The virtual keyboard allows easy entry of special characters",
		RefOne("font",             "FONT",       "Font used in display of text"),
		RefOne("fillchar1",        "CHARACTER",  "Sets the default fill character 1 (This character appears only in fields with an input mask defined)"),
		RefOne("fillchar2",        "CHARACTER",  "Sets the default fill character 2 (This character appears only in fields with an input mask defined)"),
		String("mask",                           "mask string handle, see 'Mask properties' in the documentation"),
		RefOne("mode",             "INPUTMODE",  "Configure the input mode"),
		RefOne("passwordchar",     "CHARACTER",  "Sets the default password character (This character appears only in fields with an input mask defined)"),
		String("text",                           "Text displayed on the widget"),
		RefOne("binary",              "PAGES",    "Mapping definition of the binary virtual keyboard"),
		RefOne("octal",               "PAGES",    "Mapping definition of the octal virtual keyboard"),
		RefOne("decimal",             "PAGES",    "Mapping definition of the decimal virtual keyboard"),
		RefOne("hexadecimal",         "PAGES",    "Mapping definition of the hexadecimal virtual keyboard"),
		RefOne("alphanumeric",        "PAGES",    "Mapping definition of the alphanumerical virtual keyboard"),
		RefOne("anychar",             "PAGES",    "Mapping definition of the any character virtual keyboard"),
		RefOne("userchar",         "CHARACTER",  "String that contains the set of characters accepted by the user character mask (/u or /U)"),
		RefOne("usermapping",         "PAGES",    "Mapping definition of the any user character virtual keyboard"),
		),

</ALL>*/

/** Creating a Virtual Keyboard
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_VirtualKeyboard_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/** Adds a new page in virtual keyboard
@param virtualKeyboard virtual keyboard handle
@param pageName String containing the name of the page that is displayed on the page change buttons
@param mapping string containing the mapping of the keyboard, the first character will be placed in the upper left corner, 
the next will be placed on his right and so on. The number of characters in the strings must be equal to or greater than 40, 
otherwise the keyboard will not function correctly. (the default charset is UTF8, to change the charset use the function @ref GL_GraphicLib_SetCharset), 

WARNING: If the default charset is UTF8 and if you pass a non-UTF8 string all non-utf8 characters are replaced by '?'

Some characters have a particular effect on the virtual keyboard, this is : 
 - Cancel : Displays a cancel key with a red icon. Pressing this key sends a message @ref GL_EVENT_CANCEL.
 - Valid  : Displays a valid key with a green icon. Pressing this key sends a message @ref GL_EVENT_VALID.
 - Correction : Displays a correction key with a yellow icon. Pressing this button deletes the character just before prompt.
 - Page up : Pressing this key displays the previous characters page.
 - Page down : Pressing this key displays the next characters page.

To set these keys in the string mapping, you must use @ref GL_TypesKeysUtf8 if the encoding charset is utf8, or @ref GL_TypesKeysIso if the
encoding charset is iso8859.*/
void GL_VirtualKeyboard_AddPage(T_GL_HWIDGET virtualKeyboard, const char * pageName, const char * mapping) GL_EXCEPTION;

/** Removes all pages in the virtual keyboard
@param virtualKeyboard virtual keyboard handle */
void GL_VirtualKeyboard_ClearPages(T_GL_HWIDGET virtualKeyboard) GL_EXCEPTION;


/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_VirtualKeyboard_h_INCLUDED
