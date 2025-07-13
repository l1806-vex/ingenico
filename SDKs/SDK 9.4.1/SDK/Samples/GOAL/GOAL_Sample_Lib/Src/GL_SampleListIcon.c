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

// Sample of list icon
void GL_SampleListIcon(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET list;
	T_GL_HWIDGET icon;
	
	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 100, 100, GL_UNIT_PERCENT);

	// Creating a list
	list = GL_List_Create(window);
		// Creating and attaches all icon to the list
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "0");  GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/0.png");
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "1");  GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/1.png");
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "2");  GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/2.png");
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "3");  GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/3.png");
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "4");  GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/4.png");
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "5");  GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/5.png");
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "6");  GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/6.png");
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "7");  GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/7.png");
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "8");  GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/8.png");
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "9");  GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/9.png");
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "10"); GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/10.png");
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "11"); GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/11.png");
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "12"); GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/12.png");
		icon = GL_Icon_Create(list); GL_Widget_SetText(icon, "13"); GL_Widget_SetSource(icon, "file://flash/HOST/TU.TAR/icones/13.png");

	// Registering a callback. This callback will be called every click on the button
	GL_Widget_RegisterCallback(window, GL_EVENT_STYLUS_CLICK, OnClick);

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
