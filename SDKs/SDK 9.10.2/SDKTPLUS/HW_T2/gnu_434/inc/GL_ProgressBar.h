// $Id: GL_ProgressBar.h,v 1.1.2.26 2012/08/24 12:42:52 rbertholet Exp $
// Widget progressbar box
#ifndef GL_ProgressBar_h_INCLUDED
#define GL_ProgressBar_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_ProgressBar
@{
@addtogroup GL_ProgressBarDoc Progress bar
@{
A progress bar is used to give the user an indication of the progress of an operation and to reassure them that the application is still running.

To change the text that appears in the progress bar, use GL_Widget_SetText.
The text should contain a "%d" to display the percentage. 
<b>WARNING</b> GL_Widget_SetText function interprets the character '%', so you have to double. 

Example, if you want to display "Progress [25%]" you must complete "Progress [%%d%%]".

Below is a list of specific functions to this class :
	- @ref GL_ProgressBar_Create : Creating a progress bar

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_FocusProperties
	- @ref GL_Widget_TextProperties
	- @ref GL_Widget_RangeProperties
	- @ref GL_Widget_UserDataProperties

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
	- @ref GL_Widget_SetMin
	- @ref GL_Widget_GetMin
	- @ref GL_Widget_SetMax
	- @ref GL_Widget_GetMax
	- @ref GL_Widget_SetPage
	- @ref GL_Widget_GetPage
	- @ref GL_Widget_SetValue
	- @ref GL_Widget_GetValue
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

	Below is an example of creating a window with a progress bar. 

	@image html progressbarTest.png

	@include GL_SampleProgressBar.c
@}
*/

/*<ALL>
	Extension("PROGRESSBAR",       "WIDGET",     "A progress bar is used to give the user an indication of the progress of an operation ",
		RefOne("children",         "CHILDREN",   "Children items attached to this widget"),
		RefOne("font",             "FONT",       "Font used in display of text"),
		RefOne("range",            "RANGE",      "Range"),
		String("text",                           "Text displayed on the widget"),
		),
</ALL>*/

/** Creating a horizontal progressbar
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_ProgressBar_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_ProgressBar_h_INCLUDED
