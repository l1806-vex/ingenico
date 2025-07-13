// $Id: GL_ScrollView.h,v 1.1.2.31 2012/08/24 12:42:52 rbertholet Exp $
// Graphic Object scrollview
#ifndef GL_ScrollView_h_INCLUDED
#define GL_ScrollView_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_ScrollView
@{
@addtogroup GL_ScrollViewDoc Scrollview
@{

A scroll view is used to display the contents of many children widget within a frame. 
If the widget is greater than the size of the frame, the scroll bars can be attached to the view.

<H1>The scrolled views nested are not supported. <br>
The scrolled view containing a list is also not supported.
The scrolled view must never containing signature capture widget.</H1>

Below is a list of specific functions to this class :
	- @ref GL_ScrollView_Create : Creating a scroll view

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
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

	Below is an example of creating a blank window with a scrolled view. 
	It is composed with two layouts, the "windowLayout" allows for the layout of the scrollbars and the scrolled view,
	the second layout is used for content of the scrolled view.	We leave this window by pressing a button.

	@image html scrollviewTest.png

	@include GL_SampleScrollView.c

	Below is an example of creating a blank window with a scrolled text. 

	@image html scrollText.png

	@include GL_SampleScrollText.c
@}
*/

/*<ALL>
	Extension("SCROLLVIEW",        "WIDGET",     "A scroll view is used to display the contents of many children widget within a frame",
		RefOne("children",         "CHILDREN",   "Children items attached to this widget"),
		),
</ALL>*/

/** Creating a scrollview
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_ScrollView_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/** Attachs scrollbar to the scrollview 
@param scrollview scrollview handle
@param hscrollbar horizontal scrollbar handle (NULL handle is used to detach scrollbar)
@param vscrollbar vertical scrollbar handle  (NULL handle is used to detach scrollbar)*/
void GL_ScrollView_AttachScrollbar(T_GL_HWIDGET scrollview, T_GL_HWIDGET hscrollbar, T_GL_HWIDGET vscrollbar) GL_EXCEPTION;

/** Gets the informations about the scrolled view along the vertical axis
@param scrollview scrollview handle
@return range of the vertical part :
	- min: minimum position in the view
	- max : maximum position in the view
	- value : current position in the view
	- page : size of the visible part */
T_GL_RANGE GL_ScrollView_GetVerticalRange(T_GL_HWIDGET scrollview);

/** Gets the informations about the scrolled view along the horizontal axis
@param scrollview scrollview handle
@return range of the horizontal part :
	- min: minimum position in the view
	- max : maximum position in the view
	- value : current position in the view
	- page : size of the visible part */
T_GL_RANGE GL_ScrollView_GetHorizontalRange(T_GL_HWIDGET scrollview);

/** Moves the contents of the scroll view in the directions x and y
@param scrollview scrollview handle
@param xMove Horizontal movement, the movement must be in the bound min and max returned by @ref GL_ScrollView_GetHorizontalRange
@param yMove Vertical movement, the movement must be in the bound min and max returned by @ref GL_ScrollView_GetVerticalRange*/
void GL_ScrollView_Move(T_GL_HWIDGET scrollview, T_GL_COORD xMove, T_GL_COORD yMove);

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_ScrollView_h_INCLUDED
