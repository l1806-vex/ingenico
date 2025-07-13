// $Id: GL_Layout.h,v 1.1.2.28 2012/05/23 07:03:48 rbertholet Exp $
// Layout management
#ifndef GL_Layout_h_INCLUDED
#define GL_Layout_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_Layout
@{
@addtogroup GL_LayoutDoc Layout
@{
The layout can be viewed as a table with multiple rows and columns.
The sizes of each table cell automatically adjusts with its content.
The numbering of rows and columns starts at 0 and ends at the max-1.

Example of a layout with 3 rows and 3 columns.

@image html layout.png

Below is a list of specific functions to this class :
	- @ref GL_Layout_Create : Creating a layout

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties

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

	Below is an example of creating a window with a layout with 4 rows and 5 columns.

	@image html layoutTest.png
	@include GL_SampleLayout.c
@}
*/

/*<ALL>
	Extension("LAYOUT",            "WIDGET",     "The layout can be viewed as a table with multiple rows and columns to place widgets",
		),
</ALL>*/

/** Creating a layout
@param parent handle on the parent widget
@return returns the layout handle created or null if creation failed */
T_GL_HWIDGET GL_Layout_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Layout_h_INCLUDED
