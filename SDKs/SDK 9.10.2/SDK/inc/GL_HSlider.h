// $Id: GL_HSlider.h,v 1.1.2.17 2012/08/24 12:42:52 rbertholet Exp $
// Widget slider
#ifndef GL_HSlider_h_INCLUDED
#define GL_HSlider_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_HSlider
@{
@addtogroup GL_HSliderDoc  Horizontal slider
@{

The slider is the classic widget for controlling a bounded value. 
It lets the user move a slider handle along groove and translates the handle's position into an integer value within the legal range
	
Below is a list of specific functions to this class :
	- @ref GL_HSlider_Create : Creating an horizontal slider

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_FocusProperties
	- @ref GL_Widget_CallbackProperties
	- @ref GL_Widget_RangeProperties
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
	- @ref GL_Widget_SetMin
	- @ref GL_Widget_GetMin
	- @ref GL_Widget_SetMax
	- @ref GL_Widget_GetMax
	- @ref GL_Widget_SetValue
	- @ref GL_Widget_GetValue
	- @ref GL_Widget_SetStep
	- @ref GL_Widget_GetStep
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

	Below is an example of creating a window with an horizontal slider. 

	@image html hsliderTest.png
	@include GL_SampleHSlider.c
@}
*/

/*<ALL>
	Extension("HSLIDER",           "WIDGET",     "The slider is the classic widget for controlling a bounded value. It lets the user move a slider handle along groove and translates the handle's position into an integer value within the legal range",
		RefOne("children",         "CHILDREN",   "Children items attached to this widget"),
		RefOne("range",            "RANGE",      "Range"),
		),
</ALL>*/

/** Creating a horizontal slider
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_HSlider_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_HSlider_h_INCLUDED
