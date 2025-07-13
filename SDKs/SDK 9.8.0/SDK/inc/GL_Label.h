// $Id: GL_Label.h,v 1.1.2.44 2012/12/04 15:03:44 rbertholet Exp $
// Label management
#ifndef GL_Label_h_INCLUDED
#define GL_Label_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_Label
@{
@addtogroup GL_LabelDoc Label
@{

This class is used to display text on a line or a multi-line text.

Below is a list of specific functions to this class :
	- @ref GL_Label_Create : Creating a label

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_TextProperties
	- @ref GL_Widget_CallbackProperties
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

	Below is an example of creating a window with a text label.

	@image html labelTest.png
	@include GL_SampleLabel.c

	Below is an example of creating a window with different font size.

	@image html labelTest2.png
	@include GL_SampleFont.c

	Below is an example of creating a window with a text label in utf8.

	@image html labelTest3.png
	@include GL_SampleLabelUtf8.c

	Below is an example of creating a window with a wrapped text. 

	@image html scrollText.png
	@include GL_SampleScrollText.c

	Below is an example of creating a window with different font style.

	@image html labelTest4.png
	@include GL_SampleFontStyle.c

	Below is an example of creating a window with escape sequences.

	@image html labelTest5.png
	@include GL_SampleLabelEscapeSequence.c

@}
*/


/*<ALL>
	Extension("LABEL",             "WIDGET",     'This class is used to display text on a line or a multi-line text.',
		String("text",                           'Text displayed on the widget\n'
		'Escapes sequences supported :\n'
		' - "\\x1B*" : Toggle in bold\n'
		' - "\\x1B/" : Toggle in italic\n'
		' - "\\x1B-" : Toggle in underline\n'
		' - "\\x1B0" : Text in xxsmall size\n'
		' - "\\x1B1" : Text in xsmall size\n'
		' - "\\x1B2" : Text in small size\n'
		' - "\\x1B3" : Text in medium size\n'
		' - "\\x1B4" : Text in large size\n'
		' - "\\x1B5" : Text in xlarge size\n'
		' - "\\x1B6" : Text in xxlarge size\n'
		' - "\\x1B#" : Reverse the color of text\n'
		' - "\\x1B." : Restore the default format\n'
		' - "\\x1B\\x??" : Set the forecolor or backcolor, see in documentations the colors value'),
		RefOne("font",             "FONT",       "Font used in display of text"),
		Bool("wrap",                             "The wrap allows text to automatically return to the line if it does not fit in width in the space allocated to it."),
		),
</ALL>*/

/** Creating a label
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_Label_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Label_h_INCLUDED
