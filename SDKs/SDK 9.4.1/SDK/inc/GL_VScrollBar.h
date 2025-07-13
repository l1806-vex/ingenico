// $Id: GL_VScrollBar.h,v 1.1.2.22 2012/05/23 07:03:48 rbertholet Exp $
// Widget scrollbar box
#ifndef GL_VScrollBar_h_INCLUDED
#define GL_VScrollBar_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_VScrollBar
@{
@addtogroup GL_VScrollBarDoc Vertical scrollbar
@{

A scroll bar is a control that enables the user to access parts of a document that is larger than the widget used to display it. 
It provides a visual indication of the user's current position within the document and the amount of the document that is visible.

Below is a list of specific functions to this class :
	- @ref GL_VScrollBar_Create : Creating a vertical scroll bar

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
	- @ref GL_Widget_SetClickable
	- @ref GL_Widget_GetClickable
	- @ref GL_Widget_SetClickSensitive
	- @ref GL_Widget_GetClickSensitive
	- @ref GL_Widget_ReadResource
	- @ref GL_Widget_InstanciateResource

For messages sent by this widget see @ref GL_Widget_CommonMessage

<h2>Sample</h2>

	Below is an example of creating a window with a vertical scroll bar. 

	@image html vscrollbarTest.png

	@include GL_SampleVScrollBar.c
@}
*/

/*<ALL>
	Extension("VSCROLLBAR",        "WIDGET",     "A scroll bar is a control that enables the user to access parts of a document that is larger than the widget used to display it",
		RefOne("range",            "RANGE",      "Range"),
		),
</ALL>*/

/** Creating a vertical scrollbar
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_VScrollBar_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_VScrollBar_h_INCLUDED
