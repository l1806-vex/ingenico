#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnClick(T_GL_HMESSAGE message)
{
	// Return the identifier of the icon clicked
	GL_Message_SetResult(message, GL_Widget_GetId(GL_Message_GetWidget(message)));
	return true;
}


// Adds to the list an icon completely redefined by the user 
// @param list : List in which to add the icon
// @param text : text of icon
// @param image : image on the icon
// @param id : identifier of the icon
static void GL_Sample_AddUserIcon(T_GL_HWIDGET list, const char * text, const char * image, T_GL_ID id)
{
	T_GL_HWIDGET icon;
	T_GL_HWIDGET picture;
	T_GL_HWIDGET label;

	// Creating a new icon
	icon  = GL_Icon_Create(list);

	// Assigns the identifier of the icon
	GL_Widget_SetId(icon, id);

	// Defines a margin around the icon
	GL_Widget_SetMargins(icon, 5, 5, 5, 10, GL_UNIT_PIXEL);

	// Registering a callback. This callback will be called every click on the button
	GL_Widget_RegisterCallback(icon, GL_EVENT_STYLUS_CLICK, OnClick);

	// At this point we will completely redefine the icon. 
	// So by adding a picture into the icon widget, the default skin is removed from the icon widget, 
	// and then you can completely redefine the icon.

		// Image creation focus
		picture = GL_Picture_Create(icon);
			// Forces the size of the image to 50 pixels square
			GL_Widget_SetSize  (picture, 52, 52, GL_UNIT_PIXEL);

			// Forces the image to keep its width height ratio : The image will be adapted to the size given previously
			GL_Widget_SetTransformation(picture, GL_TRANSFORMATION_FIT_ALL);

			// Load the image of the focus
			GL_Widget_SetSource(picture, "file://flash/HOST/TU.TAR/icones/focus.png");

			// Indicates that the image will be displayed only if the widget has focus
			GL_Widget_SetStateMask(picture, GL_STATE_FOCUSED, GL_STATE_EMPTY);

		// Image creation
		picture = GL_Picture_Create(icon);
			// Forces the size of the image to 50 pixels square
			GL_Widget_SetSize(picture, 52, 52, GL_UNIT_PIXEL);

			// Forces the image to keep its width height ratio : The image will be adapted to the size given previously
			GL_Widget_SetTransformation(picture, GL_TRANSFORMATION_FIT_ALL);

			// Load the image of the icon
			GL_Widget_SetSource(picture, image);

			// Set the id used by the skin, so if you use a @ref GL_Widget_SetSource this picture will change
			GL_Widget_SetId(picture, GL_ID_SKIN_ICON);

		// Label creation
		label = GL_Label_Create(icon);
			// Place the text below the image
			GL_Widget_SetItem(label, 0, 1);

			// Aligns text to the left
			GL_Widget_SetTextAlign(label, GL_ALIGN_LEFT);

			// To truncate the text if it exceeds the width of the icon
			GL_Widget_SetShrink(label, GL_DIRECTION_WIDTH);

			// Put the value of the text in the label
			GL_Widget_SetText(label, text);

			// Set the id used by the skin, so if you use a @ref GL_Widget_SetText this text will change
			GL_Widget_SetId(label, GL_ID_SKIN_LABEL);
}


// Sample list icons completely user-defined
void GL_SampleUserList(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET list;
	T_GL_ID id = 0;
	ulong result;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

	// Creating a list
	list = GL_List_Create(window);

		// Creating and attaches all icon to the list
		GL_Sample_AddUserIcon(list,  "0", "file://flash/HOST/TU.TAR/icones/0.png" , id++);
		GL_Sample_AddUserIcon(list,  "1", "file://flash/HOST/TU.TAR/icones/1.png" , id++);
		GL_Sample_AddUserIcon(list,  "2", "file://flash/HOST/TU.TAR/icones/2.png" , id++);
		GL_Sample_AddUserIcon(list,  "3", "file://flash/HOST/TU.TAR/icones/3.png" , id++);
		GL_Sample_AddUserIcon(list,  "4", "file://flash/HOST/TU.TAR/icones/4.png" , id++);
		GL_Sample_AddUserIcon(list,  "5", "file://flash/HOST/TU.TAR/icones/5.png" , id++);
		GL_Sample_AddUserIcon(list,  "6", "file://flash/HOST/TU.TAR/icones/6.png" , id++);
		GL_Sample_AddUserIcon(list,  "7", "file://flash/HOST/TU.TAR/icones/7.png" , id++);
		GL_Sample_AddUserIcon(list,  "8", "file://flash/HOST/TU.TAR/icones/8.png" , id++);
		GL_Sample_AddUserIcon(list,  "9", "file://flash/HOST/TU.TAR/icones/9.png" , id++);
		GL_Sample_AddUserIcon(list, "10", "file://flash/HOST/TU.TAR/icones/10.png", id++);
		GL_Sample_AddUserIcon(list, "11", "file://flash/HOST/TU.TAR/icones/11.png", id++);
		GL_Sample_AddUserIcon(list, "12", "file://flash/HOST/TU.TAR/icones/12.png", id++);
		GL_Sample_AddUserIcon(list, "13", "file://flash/HOST/TU.TAR/icones/13.png", id++);

	// Hides the display of the vertical scrollbar of the list
	GL_Widget_SetVisible(GL_Widget_SearchId(list, GL_ID_SKIN_VSCROLLBAR), false);

	// Here we loop indefinitely. The result returned is the icon clicked
	result = GL_Window_MainLoop(window);
	(void)result; // <- Avoid a compilation warning

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
