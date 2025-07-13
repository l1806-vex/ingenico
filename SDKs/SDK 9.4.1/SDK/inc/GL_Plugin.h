// $Id: GL_Plugin.h,v 1.1.2.13 2012/03/05 11:10:03 rbertholet Exp $
// Plugin management
#ifndef GL_Plugin_h_INCLUDED
#define GL_Plugin_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_Plugin
@{
@addtogroup GL_PluginDoc Generic plugin
@{

This widget is intended to pilot a plugin other than those provided as standard.

Below is a list of specific functions to this class :
	- @ref GL_Plugin_SetParam : Sets plugin parameter 
	- @ref GL_Plugin_GetParam : Gets plugin parameter 
	- @ref GL_Plugin_SetMimeType : Sets the mime type
	- @ref GL_Plugin_GetMimeType : Gets the mime type

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
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
	- @ref GL_Widget_SetShortcut
	- @ref GL_Widget_GetShortcut
	- @ref GL_Widget_SetUserData
	- @ref GL_Widget_GetUserData
	- @ref GL_Widget_SetClickable
	- @ref GL_Widget_GetClickable
	- @ref GL_Widget_SetClickSensitive
	- @ref GL_Widget_GetClickSensitive

For messages sent by this widget see @ref GL_Widget_CommonMessage

<h2>Sample</h2>

	Below is an example of how to use the generic widget plugin to interact with the native plugin video.
	This is just one example, to view a video you must use the media widget.

	@image html pluginTest.png

	@include GL_SamplePlugin.c
@}
*/

/*<ALL>
	Extension("PLUGIN",             "WIDGET",     "This class is used to play movie or sound",
		String("mimetype",                         "Mime type used to find the DLL plugin"),
		),
</ALL>*/


/** Creating a plugin
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_Plugin_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/** Sets plugin parameter.
WARNING : To use this function you must have to load the plugin before. The loading is done automatically when calling the function GL_Window_Dispatch.
@param plugin plugin handle
@param name string parameter name 
@param value pointer to the value to set
@param valueLength size of value to set
@return returns -1 if failed else returns value length set */
long GL_Plugin_SetParam(T_GL_HWIDGET plugin, const char * name, const void * value, ulong valueLength) GL_EXCEPTION;

/** Gets plugin parameter.
WARNING : To use this function you must have to load the plugin before. The loading is done automatically when calling the function GL_Window_Dispatch.
@param plugin plugin handle
@param name string parameter name 
@param value pointer to the value to get
@param valueLength size of value to get
@return returns -1 if failed else returns value length get */
long GL_Plugin_GetParam(T_GL_HWIDGET plugin, const char * name, void * value, ulong valueLength) GL_EXCEPTION;

/** Sets the mime type, WARNING : the mime type of the plugin must imperatively be informed before the first call of GL_Window_Dispatch.
@param plugin plugin handle
@param mimeType mime type string */
void GL_Plugin_SetMimeType(T_GL_HWIDGET plugin, const char * mimeType) GL_EXCEPTION;

/** Gets the mime type
@param plugin plugin handle
@return mimeType mime type string */
const char *GL_Plugin_GetMimeType(T_GL_HWIDGET plugin) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Plugin_h_INCLUDED
