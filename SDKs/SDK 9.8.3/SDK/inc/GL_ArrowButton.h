// $Id: GL_ArrowButton.h,v 1.1.2.2 2012/08/24 12:42:52 rbertholet Exp $
// Graphic Object arrow button
#ifndef GL_ArrowButton_h_INCLUDED
#define GL_ArrowButton_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_ArrowButton
@{
@addtogroup GL_ArrowButtonDoc Arrow button
@{

The button to command the terminal to perform some action, or to answer a question. 
This has an arrow displayed above. It is mainly used to indicate a sub menu in a list.
Typical buttons are OK, Cancel, Yes and No.
A button emits the message clicked when it is activated by the stylus, stylus or valid key.

Below is a list of specific functions to this class :
	- @ref GL_ArrowButton_Create : Creating a button
	- @ref GL_ArrowButton_SetArrowDirection : Sets the arrow direction on button 
	- @ref GL_ArrowButton_GetArrowDirection : Gets the arrow direction on button 

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

	Below is an example of creating a blank window with an arrow button. We leave this window by pressing a button.

	@image html arrowButtonTest.png
	@include GL_SampleArrowButton.c

@}
*/


/*<ALL>
	Enum("ARROWDIRECTION",                               "Arrow direction",
		Define("none",            "0",          "No arrow on the button"),
		Define("left",            "1",          "The arrow is displayed at left"),
		Define("right",           "2",          "The arrow is displayed at right"),
		Define("left,right",      "3",          "The arrow is displayed left and right"),
		),
</ALL>*/


/*<ALL>
	Extension("ARROWBUTTON",            "WIDGET",     "The arrow button is used to display a button with an arrow",
		RefOne("children",         "CHILDREN",   "Children items attached to this widget"),
		String("text",                           "Text displayed on the widget"),
		RefOne("font",             "FONT",       "Font used in display of text"),
		RefOne("arrowdirection",             "ARROWDIRECTION",       "Arrow direction"),
		),
</ALL>*/

/** Creating a button
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_ArrowButton_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/** Arrow direction */
typedef enum T_GL_ARROW_DIRECTION
{
	GL_ARROW_DIRECTION_NONE,          ///< No arrow on the button
	GL_ARROW_DIRECTION_LEFT,          ///< The arrow is displayed at left
	GL_ARROW_DIRECTION_RIGHT,         ///< The arrow is displayed at right
	GL_ARROW_DIRECTION_LEFT_AND_RIGHT ///< The arrow is displayed left and right
} T_GL_ARROW_DIRECTION;


/** Sets the arrow direction on button 
@param widget widget handle 
@param direction arrow direction to set */
void GL_ArrowButton_SetArrowDirection(T_GL_HWIDGET widget, T_GL_ARROW_DIRECTION direction) GL_EXCEPTION;

/** Gets the arrow direction on button 
@param widget widget handle 
@return direction arrow direction to set */
T_GL_ARROW_DIRECTION GL_ArrowButton_GetArrowDirection(T_GL_HWIDGET widget) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_ArrowButton_h_INCLUDED
