// $Id: GL_Icon.h,v 1.1.2.25 2012/01/16 08:12:56 rbertholet Exp $
// Graphic Object icon
#ifndef GL_Icon_h_INCLUDED
#define GL_Icon_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_Icon
@{
@addtogroup GL_IconDoc  Documentation
@{
the class icon is equivalent to a button, it allows the display of an image more

Below is a list of specific functions to this class :
	- @ref GL_Icon_Create : Creating an icon

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_FocusProperties
	- @ref GL_Widget_TextProperties
	- @ref GL_Widget_ImagesProperties
	- @ref GL_Widget_CallbackProperties
	- @ref GL_Widget_ShortcutProperties

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

For messages sent by this widget see @ref GL_Widget_CommonMessage

<h2>Sample</h2>

	Below is an example of creating a window with an icon.

	@image html iconTest.png
	@include GL_SampleIcon.c
@}
*/

/*<ALL>
	Extension("ICON",              "WIDGET",     "The class icon is equivalent to a button, it allows the display of an image more",
		RefOne("source",           "SOURCEFILE","Image source (file name can contain alphanumeric, underscore, minus, spaces characters)"),
		String("text",                           "Text displayed on the widget"),
		RefOne("font",             "FONT",       "Font used in display of text"),
		RefOne("transformation",   "TRANSFORMATION", "Image transformation"),
		),
</ALL>*/

/** Creating a icon
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_Icon_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Icon_h_INCLUDED
