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

#define GL_ID_HSCROLLBAR 1
#define GL_ID_PROGRESSBAR 2
#define GL_ID_VSCROLLBAR 3

// Callback for processing a scroll message
static bool OnScroll(T_GL_HMESSAGE message)
{
	T_GL_HWIDGET widget;
	widget = GL_Message_GetWidgetById(message, GL_ID_HSCROLLBAR);
	GL_Widget_SetMin(widget, GL_Message_GetRange(message).min);
	GL_Widget_SetMax(widget, GL_Message_GetRange(message).max);
	GL_Widget_SetPage(widget, GL_Message_GetRange(message).value);

	widget = GL_Message_GetWidgetById(message, GL_ID_VSCROLLBAR);
	GL_Widget_SetMin(widget, GL_Message_GetRange(message).min);
	GL_Widget_SetMax(widget, GL_Message_GetRange(message).max);
	GL_Widget_SetPage(widget, GL_Message_GetRange(message).value);

	widget = GL_Message_GetWidgetById(message, GL_ID_PROGRESSBAR);
	GL_Widget_SetMin(widget, GL_Message_GetRange(message).min);
	GL_Widget_SetMax(widget, GL_Message_GetRange(message).max);
	GL_Widget_SetPage(widget, GL_Message_GetRange(message).value);
	
	return true;
}


// Sample of all widgets
void GL_SampleAllWidgets(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET scrollview;
	T_GL_HWIDGET layout;
	T_GL_HWIDGET widget;
	T_GL_DIM row = 0;

	// Creating a blank window
	window = GL_Window_Create(graphicLib);

		// Creating scrollview
		scrollview = GL_ScrollView_Create(window);
	
			// Creating the main layout
			layout = GL_Layout_Create(scrollview);

				// Creating button
				widget = GL_Button_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "quit");

					// Registering a callback. This callback will be called every click on the button
					GL_Widget_RegisterCallback(widget, GL_EVENT_STYLUS_CLICK, OnClick);


				// Creating label
				widget = GL_Label_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "label");


				// Creating button
				widget = GL_Button_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "button");


				// Creating radio button
				widget = GL_RadioButton_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "radio button");


				// Creating check button
				widget = GL_CheckButton_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "check button");


				// Creating icon button
				widget = GL_IconButton_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "icon button");

					// Set the image
					GL_Widget_SetSource(widget, "file://flash/HOST/TU.TAR/icones/1.png");


				// Creating icon
				widget = GL_Icon_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "icon");

					// Set the image
					GL_Widget_SetSource(widget, "file://flash/HOST/TU.TAR/icones/1.png");


				// Creating virtual keyboard
				widget = GL_VirtualKeyboard_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "Virtual keyboard");


				// Creating edit
				widget = GL_Edit_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "Edit");

					// Set expand
					GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);


				// Creating palette
				widget = GL_Palette_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);


				// Creating scroll bar
				widget = GL_VScrollBar_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Register the id of the widget
					GL_Widget_SetId(widget, GL_ID_VSCROLLBAR);

					GL_Widget_SetGrow(widget, GL_DIRECTION_WIDTH);
					GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);
					GL_Widget_SetMinSize(widget, 100, 50, GL_UNIT_PERCENT);


				// Creating scroll bar
				widget = GL_HScrollBar_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Register the id of the widget
					GL_Widget_SetId(widget, GL_ID_HSCROLLBAR);


				// Creating progress bass
				widget = GL_ProgressBar_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "Progress bar [%%d%%]");

					// Register the id of the widget
					GL_Widget_SetId(widget, GL_ID_PROGRESSBAR);


				// Creating slider
				widget = GL_HSlider_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Configure slider
					GL_Widget_SetMin  (widget, 0);
					GL_Widget_SetMax  (widget, 100);
					GL_Widget_SetValue(widget, 0);
					GL_Widget_SetStep (widget, 10);

					// Registering a callback. This callback will be called every click on the button
					GL_Widget_RegisterCallback(widget, GL_EVENT_HORIZONTAL_SCROLL, OnScroll);


				// Creating button
				widget = GL_Button_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "Media");


				// Creating video
				widget = GL_Media_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the video file
					GL_Widget_SetSource(widget,"file://flash/HOST/CLESS.MP4");

					GL_Media_SetLoop(widget,1);
		
				// Creating button
				widget = GL_Button_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "Picture");


				// Creating a picture
				widget = GL_Picture_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the image source
					GL_Widget_SetSource(widget, "file://flash/HOST/TU.TAR/gifsuite/earth.gif");
			

				// Creating button
				widget = GL_Button_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "Drawing");


				// Create a widget surface
				widget = GL_Drawing_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the background color of the widget
					GL_Widget_SetBackColor(widget, GL_COLOR_GRAY);

					// A action to draw an ellipse
					GL_Drawing_SetPen(widget, GL_COLOR_BLUE, 1,GL_UNIT_PERCENT);
					GL_Drawing_SetBrush(widget, GL_COLOR_YELLOW);
					GL_Drawing_DrawEllipse(widget, 25, 25, 25, 25, GL_UNIT_PERCENT);

					// A action to draw a rectangle
					GL_Drawing_SetPen(widget, GL_COLOR_RED, 1,GL_UNIT_PERCENT);
					GL_Drawing_SetBrush(widget, GL_COLOR_ORANGE);
					GL_Drawing_DrawRect(widget, 50, 50, 50, 50, GL_UNIT_PERCENT);

					// A action to draw line
					GL_Drawing_SetPen(widget, GL_COLOR_BLACK, 1,GL_UNIT_PERCENT);
					GL_Drawing_DrawLine(widget, 25,25,75,75,GL_UNIT_PERCENT);

					// A action to draw a text "Hello world"
					GL_Drawing_SetPen(widget, GL_COLOR_BLUE, 1,GL_UNIT_PERCENT);
					GL_Drawing_SetFont(widget, "arial", GL_FONT_STYLE_NORMAL, 30, 30, GL_UNIT_PERCENT);
					GL_Drawing_DrawText(widget, 0,300,GL_UNIT_PERTHOUSAND, "Hello world");


				// Creating button
				widget = GL_Button_Create(layout);

					// Set the position in the layout
					GL_Widget_SetItem(widget, 0, row++);

					// Set the text
					GL_Widget_SetText(widget, "quit");

					// Registering a callback. This callback will be called every click on the button
					GL_Widget_RegisterCallback(widget, GL_EVENT_STYLUS_CLICK, OnClick);


	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
