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

// Sample of media
void GL_SampleMedia(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET media;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Creating a media widget
	media = GL_Media_Create(window);

	// Sets video filename
	GL_Widget_SetSource(media,"file://flash/HOST/CLESS.MP4");

	// Sets the volume
	GL_Media_SetVolume(media, 100);

	// Start the video
	GL_Media_Start(media);

	// Registering a callback. This callback will be called every click on the media
	GL_Widget_RegisterCallback(media, GL_EVENT_STYLUS_CLICK, OnClick);

	// Register shortcut to quit
	GL_Widget_SetShortcut(media, GL_KEY_VALID);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);
	
	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
