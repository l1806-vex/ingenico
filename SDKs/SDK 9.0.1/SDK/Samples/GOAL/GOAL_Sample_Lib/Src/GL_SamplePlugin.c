#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnClick(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}

// Sample of generic plugin
void GL_SamplePlugin(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET plugin;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Creating a plugin widget
	plugin = GL_Plugin_Create(window);

	// Sets the mime type of the plugin DLL
	GL_Plugin_SetMimeType(plugin, "ingenico/mmplayer");

	// This dispatch the event is very IMPORTANT here because as long as the plugin is not displayed the configuration of it is not possible
	GL_Window_Dispatch(window, 0);

	// Configuration of the plugin
	GL_Plugin_SetParam(plugin, "SetSource", "file://flash/HOST/CLESS.MP4", strlen("file://flash/HOST/CLESS.MP4") + 1);
	GL_Plugin_SetParam(plugin, "Start", 0, 0);

	// Registering a callback. This callback will be called every click on the plugin
	GL_Widget_RegisterCallback(plugin, GL_EVENT_STYLUS_CLICK, OnClick);

	// Register shortcut to quit
	GL_Widget_SetShortcut(plugin, GL_KEY_VALID);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
