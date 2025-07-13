// $Id: GL_HScrollBar.h,v 1.1.2.17 2012/01/16 08:12:56 rbertholet Exp $
// Widget scrollbar box
#ifndef GL_HScrollBar_h_INCLUDED
#define GL_HScrollBar_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_HScrollBar
@{
@addtogroup GL_HScrollBarDoc  Documentation
@{

A scroll bar is a control that enables the user to access parts of a document that is larger than the widget used to display it. 
It provides a visual indication of the user's current position within the document and the amount of the document that is visible.

Below is a list of specific functions to this class :
	- @ref GL_HScrollBar_Create : Creating an horizontal scroll bar

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_FocusProperties
	- @ref GL_Widget_CallbackProperties
	- @ref GL_Widget_RangeProperties

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
	- @ref GL_Widget_SetUserData
	- @ref GL_Widget_GetUserData

<h2>Sample</h2>

	Below is an example of creating a window with an horizontal scroll bar. 

	@image html hscrollbarTest.png
	@include GL_SampleHScrollBar.c
@}
*/

/*<ALL>
	Extension("HSCROLLBAR",        "WIDGET",     "A scroll bar is a control that enables the user to access parts of a document that is larger than the widget used to display it",
		RefOne("range",            "RANGE",      "Range"),
		),
</ALL>*/

/** Creating a horizontal scrollbar
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_HScrollBar_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_HScrollBar_h_INCLUDED
