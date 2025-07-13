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


// Resource of a button in JSON
// Here we placed the json resource into a constant C, 
// this is to demonstrate the use of @ref GL_Widget_InstanciateResource, 
// this is not necessarily a good idea, it is preferable rather to put the content in a signed data file
// as you can change the look without modifying the source code in C.
static const char GL_JsonButtonResource[] = 
	"{\n"
	"	\"type\"           :\"button\",\n"
	"	\"grow\"           :\"all\",\n"
	"	\"shrink\"         :\"none\",\n"
	"	\"clickable\"      :true,\n"
	"	\"clicksensitive\" :true,\n"
	"	\"focusable\"      :true,\n"
	"	\"children\"       :\n"
	"	[\n"
	"		// Focus pictures \n"
	"		{\n"
	"			\"type\"           :\"picture\",\n"
	"			\"item\"           :{\"column\":0, \"row\":0},\n"
	"			\"statemask\"      :\"focused\",\n"
	"			\"source\"         :\"file://flash/HOST/TU.TAR/wgusuite/ButFocus(Left).wgu\",\n"
	"			\"size\"           :{\"width\":7},\n"
	"			\"margins\"        :{\"left\":3, \"top\":2, \"right\":0, \"bottom\":2},\n"
	"			\"forealign\"      :\"left\",\n"
	"			\"transformation\" :\"stretchy\",\n"
	"			\"expand\"         :\"height\",\n"
	"			\"shrink\"         :\"height\",\n"
	"		},\n"
	"		{\n"
	"			\"type\"           :\"picture\",\n"
	"			\"item\"           :{\"column\":1, \"row\":0},\n"
	"			\"statemask\"      :\"focused\",\n"
	"			\"source\"         :\"file://flash/HOST/TU.TAR/wgusuite/ButFocus(center).wgu\",\n"
	"			\"margins\"        :{\"left\":0, \"top\":2, \"right\":0, \"bottom\":2},\n"
	"			\"transformation\" :\"repeatxstretchy\",\n"
	"			\"expand\"         :\"all\",\n"
	"			\"shrink\"         :\"all\",\n"
	"		},\n"
	"		{\n"
	"			\"type\"           :\"picture\",\n"
	"			\"item\"           :{\"column\":2, \"row\":0},\n"
	"			\"statemask\"      :\"focused\",\n"
	"			\"source\"         :\"file://flash/HOST/TU.TAR/wgusuite/ButFocus(right).wgu\",\n"
	"			\"size\"           :{\"width\":7},\n"
	"			\"margins\"        :{\"left\":0, \"top\":2, \"right\":3, \"bottom\":2},\n"
	"			\"forealign\"      :\"right\",\n"
	"			\"transformation\" :\"stretchy\",\n"
	"			\"expand\"         :\"height\",\n"
	"			\"shrink\"         :\"height\",\n"
	"		},\n"
	"		// Button pictures \n"
	"		{\n"
	"			\"type\"           :\"picture\",\n"
	"			\"item\"           :{\"column\":0, \"row\":0},\n"
	"			\"statemask\"      :\"unfocused\",\n"
	"			\"source\"         :\"file://flash/HOST/TU.TAR/wgusuite/Button(left).wgu\", \n"
	"			\"size\"           :{\"width\":7},\n"
	"			\"margins\"        :{\"left\":3, \"top\":2, \"right\":0, \"bottom\":2},\n"
	"			\"forealign\"      :\"left\",\n"
	"			\"transformation\" :\"stretchy\",\n"
	"			\"expand\"         :\"height\",\n"
	"			\"shrink\"         :\"height\",\n"
	"		},\n"
	"		{\n"
	"			\"type\"           :\"picture\",\n"
	"			\"item\"           :{\"column\":1, \"row\":0},\n"
	"			\"statemask\"      :\"unfocused\",\n"
	"			\"source\"         :\"file://flash/HOST/TU.TAR/wgusuite/Button(center).wgu\",\n"
	"			\"margins\"        :{\"left\":0, \"top\":2, \"right\":0, \"bottom\":2},\n"
	"			\"transformation\" :\"repeatxstretchy\",\n"
	"			\"expand\"         :\"all\",\n"
	"			\"shrink\"         :\"all\",\n"
	"		},\n"
	"		{\n"
	"			\"type\"           :\"picture\",\n"
	"			\"item\"           :{\"column\":2, \"row\":0},\n"
	"			\"statemask\"      :\"unfocused\",\n"
	"			\"source\"         :\"file://flash/HOST/TU.TAR/wgusuite/Button(right).wgu\",\n"
	"			\"size\"           :{\"width\":7},\n"
	"			\"margins\"        :{\"left\":0, \"top\":2, \"right\":3, \"bottom\":2},\n"
	"			\"forealign\"      :\"right\",\n"
	"			\"transformation\" :\"stretchy\",\n"
	"			\"expand\"         :\"height\",\n"
	"			\"shrink\"         :\"height\",\n"
	"		},\n"
	"		// Icon image \n"
	"		{\n"
	"			\"type\"           :\"picture\",\n"
	"			\"item\"           :{\"column\":1, \"row\":0},\n"
	"			\"id\"             :0xFF000006, // GL_ID_SKIN_ICON\n"
	"			\"source\"         :\"\",\n"
	"			\"shrink\"         :\"none\",\n"
	"		},\n"
	"		// Label \n"
	"		{\n"
	"			\"type\"           :\"label\",\n"
	"			\"item\"           :{\"column\":1, \"row\":0},\n"
	"			\"id\"             :0xFF000001, // GL_ID_SKIN_LABEL\n"
	"			\"font\"           :{\"size\":{\"height\":0x3FF3}},\n"
	"			\"forecolor\"      :0x0000000D, // GL_COLOR_BUTTON_TEXT\n"
	"			\"margins\"        :{\"top\":2, \"bottom\":2},\n"
	"		},\n"
	"	]\n"
	"}\n";


// Sample of instanciation of a resource
void GL_SampleInstanciateResource(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET button;
	T_GL_HWIDGET layout;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Reduces the size of window
	GL_Widget_SetSize(window, 50, 50, GL_UNIT_PERCENT);

	// Creating a layout with 3 rows and one column
	layout = GL_Layout_Create(window);

	// Creating first button with JSON resource file
	button = GL_Widget_InstanciateResource(layout, GL_JsonButtonResource, strlen(GL_JsonButtonResource));

	// Change the text of button
	GL_Widget_SetText(button,"One");

	// Set the button in the first cell of the layout
	GL_Widget_SetItem(button, 0, 0);

	// Creating second button with JSON resource file
	button = GL_Widget_InstanciateResource(layout, GL_JsonButtonResource, strlen(GL_JsonButtonResource));

	// Change the text of button
	GL_Widget_SetText(button,"Two");

	// Set the button in the second cell of the layout
	GL_Widget_SetItem(button, 0, 1);

	// Set the check by default on the second button
	GL_Widget_SetCheck(button, true);

	// Creating third button with JSON resource file
	button = GL_Widget_InstanciateResource(layout, GL_JsonButtonResource, strlen(GL_JsonButtonResource));

	// Change the text of button
	GL_Widget_SetText(button,"Three");

	// Set the button in the third cell of the layout
	GL_Widget_SetItem(button, 0, 2);

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
