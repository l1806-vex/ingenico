// $Id: GL_Button.h,v 1.1.2.44 2012/08/24 12:42:52 rbertholet Exp $
// Graphic Object button
#ifndef GL_Button_h_INCLUDED
#define GL_Button_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_Button
@{
@addtogroup GL_ButtonDoc Button
@{

The button to command the terminal to perform some action, or to answer a question. 
Typical buttons are OK, Cancel, Yes and No.
A button emits the message clicked when it is activated by the stylus, stylus or valid key.

Below is a list of specific functions to this class :
	- @ref GL_Button_Create : Creating a button

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_ImagesProperties
	- @ref GL_Widget_FocusProperties
	- @ref GL_Widget_CheckProperties
	- @ref GL_Widget_TextProperties
	- @ref GL_Widget_CallbackProperties
	- @ref GL_Widget_ShortcutProperties
	- @ref GL_Widget_UserDataProperties

For messages sent by this widget see :
	- @ref GL_Widget_CommonMessage

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
	- @ref GL_Widget_SetBorders
	- @ref GL_Widget_GetBorders
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
	- @ref GL_Widget_SetTextPaddings
	- @ref GL_Widget_GetTextPaddings
	- @ref GL_Widget_SetFontName
	- @ref GL_Widget_GetFontName
	- @ref GL_Widget_SetFontSize
	- @ref GL_Widget_GetFontSize
	- @ref GL_Widget_SetFontStyle
	- @ref GL_Widget_GetFontStyle
	- @ref GL_Widget_SetSource
	- @ref GL_Widget_GetSource
	- @ref GL_Widget_SetShortcut
	- @ref GL_Widget_GetShortcut
	- @ref GL_Widget_SetUserData
	- @ref GL_Widget_GetUserData
	- @ref GL_Widget_SetClickable
	- @ref GL_Widget_GetClickable
	- @ref GL_Widget_SetClickSensitive
	- @ref GL_Widget_GetClickSensitive
	- @ref GL_Widget_ReadResource
	- @ref GL_Widget_InstanciateResource
	- @ref GL_Widget_SetFontScale

For messages sent by this widget see @ref GL_Widget_CommonMessage

<h2>Sample</h2>

	Below is an example of creating a blank window with a button. We leave this window by pressing a button.

	@image html buttonTest.png
	@include GL_SampleButton.c

	Below is an example of stretching button

	@image html buttonTest2.png
	@include GL_SampleButtonStretch.c

	Below is an example of button with skined icon

	@image html buttonTest3.png
	@include GL_SampleButtonWithSkinedIcon.c
@}
*/


/*<ALL>
	Extension("BUTTON",            "WIDGET",     "The button to command the terminal to perform some action, or to answer a question",
		RefOne("children",         "CHILDREN",   "Children items attached to this widget"),
		String("text",                           "Text displayed on the widget"),
		RefOne("font",             "FONT",       "Font used in display of text"),
		),
</ALL>*/

/** Creating a button
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_Button_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Button_h_INCLUDED
