// $Id: GL_Edit.h,v 1.1.2.31 2012/01/16 08:12:56 rbertholet Exp $
// Widget edit box
#ifndef GL_Edit_h_INCLUDED
#define GL_Edit_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_Edit
@{
@addtogroup GL_EditDoc  Documentation
@{

The edit widget provides a widget that is used to edit a single line of text. 

Below is a list of specific functions to this class :
	- @ref GL_Edit_Create : Creating an edit
	- @ref GL_Widget_SetMask : Specifies a mask that controls the input characters
	- @ref GL_Widget_SetFillChar1 : Sets the default fill character (This character appears only in fields with an input mask defined)
	- @ref GL_Widget_GetFillChar1 : Gets the default fill character (This character appears only in fields with an input mask defined)
	- @ref GL_Widget_SetFillChar2 : Sets the default fill character (This character appears only in fields with an input mask defined)
	- @ref GL_Widget_GetFillChar2 : Gets the default fill character (This character appears only in fields with an input mask defined)
	- @ref GL_Widget_SetPasswordChar : Sets the default password character 
	- @ref GL_Widget_GetPasswordChar : Gets the default password character 
	- @ref GL_Widget_SetMode : Sets the input mode
	- @ref GL_Widget_GetMode : Gets the input mode
	- @ref GL_Widget_SetInput : Sets the input text of the edit (The input text is the raw text entered by the user without the mask characters)
	- @ref GL_Widget_GetInput : Gets the input text of the edit  (The input text is the raw text entered by the user without the mask characters)
	- @ref GL_Widget_SelectAll : Selects all characters in the edit, the first entry of a character deletes the entire contents of the field

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_FocusProperties
	- @ref GL_Widget_TextProperties
	- @ref GL_Widget_InputProperties
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
	- @ref GL_Widget_SetFontName
	- @ref GL_Widget_GetFontName
	- @ref GL_Widget_SetFontSize
	- @ref GL_Widget_GetFontSize
	- @ref GL_Widget_SetFontStyle
	- @ref GL_Widget_GetFontStyle
	- @ref GL_Widget_SetShortcut
	- @ref GL_Widget_GetShortcut
	- @ref GL_Widget_SetMask
	- @ref GL_Widget_SetFillChar1
	- @ref GL_Widget_GetFillChar1
	- @ref GL_Widget_SetFillChar2
	- @ref GL_Widget_GetFillChar2
	- @ref GL_Widget_SetPasswordChar
	- @ref GL_Widget_GetPasswordChar
	- @ref GL_Widget_SetMode
	- @ref GL_Widget_GetMode
	- @ref GL_Widget_SetInput
	- @ref GL_Widget_GetInput
	- @ref GL_Widget_SelectAll
	- @ref GL_Widget_SetUserData
	- @ref GL_Widget_GetUserData

For messages sent by this widget see @ref GL_Widget_CommonMessage

<h2>Sample</h2>

	Below is an example of creating a window with an edit with an input field for entering a date.

	@image html editTest.png
	@include GL_SampleEdit.c

	Below is an example of creating a window with many edit field with mask.

	@image html editTest2.png

	@include GL_SampleEditMask.c

	Below is an example of creating a window with many edit mode.

	@image html editTest3.png

	@include GL_SampleEditMode.c
	
@}
*/

/*<ALL>
	Extension("EDIT",              "WIDGET",     "The edit widget provides a widget that is used to edit a single line of text.",
		String("text",                           "Text displayed on the widget"),
		RefOne("font",             "FONT",       "Font used in display of text"),
		String("fillchar1",                      "Sets the default fill character 1 (This character appears only in fields with an input mask defined)"),
		String("fillchar2",                      "Sets the default fill character 2 (This character appears only in fields with an input mask defined)"),
		String("passwordchar",                   "Sets the default password character (This character appears only in fields with an input mask defined)"),
		String("mask",                           "mask string handle, see 'Mask properties' in the documentation"),
		RefOne("mode",             "INPUTMODE",  "Configure the input mode"),
		String("userchar",                       "String that contains the set of characters accepted by the user character mask (/u or /U)"),
		),
</ALL>*/

/** Creating a edit
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_Edit_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Edit_h_INCLUDED
