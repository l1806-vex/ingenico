// $Id: GL_List.h,v 1.1.2.30 2012/05/11 13:55:38 rbertholet Exp $
// Graphic Object list
#ifndef GL_List_h_INCLUDED
#define GL_List_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_List
@{
@addtogroup GL_ListDoc List
@{

The list allows the display of all elements of widgets, it automatically handles the formatting. 
If the list contains only icons, the display is then as matrix. 
A scroll bar is present for the allow to see all the widgets.

Below is a list of specific functions to this class :
	- @ref GL_List_Create : Creating a list

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_FocusProperties
	- @ref GL_Widget_CallbackProperties

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

For messages sent by this widget see @ref GL_Widget_CommonMessage

<h2>Sample</h2>

	Below is an example of creating a window with a list of widgets.

	@image html listTest1.png 

	@include GL_SampleList.c

	Below is an example of creating a window with a list of icons.

	@image html listTest3.png 

	@include GL_SampleListIcon.c

	Below is an example of creating a window with a dynamic list.

	@example GL_SampleListDynamic.c

@}
*/


/*<ALL>
	List("ITEMS",                                    "List of widgets",
		Item("button",            "BUTTON",          "The button to command the terminal to perform some action, or to answer a question"),
		Item("checkbutton",       "CHECKBUTTON",     "A check button is an option button that can be switched on (checked) or off (unchecked)"),
		Item("edit",              "EDIT",            "The edit widget provides a widget that is used to edit a single line of text."),
		Item("hslider",           "HSLIDER",         "The slider is the classic widget for controlling a bounded value. It lets the user move a slider handle along groove and translates the handle's position into an integer value within the legal range"),
		Item("icon",              "ICON",            "The class icon is equivalent to a button, it allows the display of an image more"),
		Item("iconbutton",        "ICONBUTTON",      "This class is an icon followed by a button"),
		Item("label",             "LABEL",           "This class is used to display text on a line or a multi-line text"),
		Item("layout",            "LAYOUT",          "The layout can be viewed as a table with multiple rows and columns to place widgets"),
		Item("palette",           "PALETTE",         "A palette is a widget that can display a color palette"),
		Item("picture",           "PICTURE",         "A picture is a widget that can display a fixed image or animated image"),
		Item("progressbar",       "PROGRESSBAR",     "A progress bar is used to give the user an indication of the progress of an operation "),
		Item("radiobutton",       "RADIOBUTTON",     "A radio button is an option button that can be switched on (checked) or off (unchecked)"),
		Item("virtualkeyboard",   "VIRTUALKEYBOARD", "The virtual keyboard allows easy entry of special characters"),
		Item("barcode",           "BARCODE",         "This widget can display a barcode"),
	),
	ExtensionMany("LIST",              "WIDGET",     "The list allows the display of all elements of widgets",
		RefMany("items",               "ITEMS",      "List of items. IMPORTANT: All elements of the list widget should be placed in this tag."),
		),
</ALL>*/

/** Creating a list
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_List_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/** Gets the number of items in the list
@param list list handle
@return the number of items in the list */
ulong GL_List_GetCount(T_GL_HWIDGET list) GL_EXCEPTION;

/** Gets an element to a given index
@param list list handle 
@param index index in the list (The index should be equal or greater than 0 and less than the value returned by @ref GL_List_GetCount)
@return the widget handle or null if it failed */
T_GL_HWIDGET GL_List_GetElement(T_GL_HWIDGET list, ulong index) GL_EXCEPTION;

/** Removes all elements in the list
@param list list handle */
void GL_List_Clear(T_GL_HWIDGET list) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_List_h_INCLUDED
