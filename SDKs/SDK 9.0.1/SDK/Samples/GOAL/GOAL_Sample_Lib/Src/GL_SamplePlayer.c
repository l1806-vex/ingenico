#include "GL_GraphicLib.h"
#include "GL_Samples.h"

#define GL_MEDIA_ID 0
#define GL_TIME_ID  1
#define GL_STOP_ID  2
#define GL_PLAY_ID  3
#define GL_PAUSE_ID 4
#define GL_PROGRESS_ID 5
#define GL_SELECT_ID 6
#define GL_TIMER_ID 7

// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnVideoClick(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}

// Callback for processing a volume.
static bool OnVolumeChanged(T_GL_HMESSAGE message)
{
	GL_Media_SetVolume(GL_Message_GetWidgetById(message, GL_MEDIA_ID),(byte) GL_Message_GetRange(message).value);
	return true;
}

// Callback for processing a volume.
static bool OnTimeChanged(T_GL_HMESSAGE message)
{
	T_GL_HWIDGET media = GL_Message_GetWidgetById(message, GL_MEDIA_ID);
	GL_Media_SetTime(media, ((ulong)GL_Message_GetRange(message).value)*1000);
	return true;
}

// Callback for refresh time bar
static bool OnRefresh(T_GL_HMESSAGE message)
{
	T_GL_HWIDGET media    = GL_Message_GetWidgetById(message, GL_MEDIA_ID);
	T_GL_HWIDGET time     =  GL_Message_GetWidgetById(message, GL_TIME_ID);

	GL_Widget_SetMax  (time, (T_GL_COORD)(GL_Media_GetDuration(media)/1000));
	GL_Widget_SetValue(time, (T_GL_COORD)(GL_Media_GetTime(media)/1000));

#ifdef _DEBUG
	{
		T_GL_HWIDGET progress = GL_Message_GetWidgetById(message, GL_PROGRESS_ID);
		const char * progressStr;
		progressStr = GL_Widget_GetText(progress);
		if      (strcmp(progressStr, "|") == 0) GL_Widget_SetText(progress,"/");
		else if (strcmp(progressStr, "/") == 0) GL_Widget_SetText(progress,"-");
		else if (strcmp(progressStr, "-") == 0) GL_Widget_SetText(progress,"\\");
		else                                    GL_Widget_SetText(progress,"|");
	}
#endif
	return true;
}

// Callback for processing a ratio click
static bool OnRatioClick(T_GL_HMESSAGE message)
{
	GL_Widget_ToggleCheck(GL_Message_GetWidget(message));
	return true;
}

// Callback for processing a ratio.
static bool OnRatioCheck(T_GL_HMESSAGE message)
{
	GL_Media_KeepRatio(GL_Message_GetWidgetById(message, GL_MEDIA_ID), true);
	return true;
}

// Callback for processing a ratio.
static bool OnRatioUncheck(T_GL_HMESSAGE message)
{
	GL_Media_KeepRatio(GL_Message_GetWidgetById(message, GL_MEDIA_ID), false);
	return true;
}

// Callback for processing a loop click
static bool OnLoopClick(T_GL_HMESSAGE message)
{
	GL_Widget_ToggleCheck(GL_Message_GetWidget(message));
	return true;
}

// Callback for processing a loop.
static bool OnLoopCheck(T_GL_HMESSAGE message)
{
	GL_Media_SetLoop(GL_Message_GetWidgetById(message, GL_MEDIA_ID), true);
	return true;
}

// Callback for processing a loop.
static bool OnLoopUncheck(T_GL_HMESSAGE message)
{
	GL_Media_SetLoop(GL_Message_GetWidgetById(message, GL_MEDIA_ID), false);
	return true;
}

// Callback for processing a visible.
static bool OnVisibleClick(T_GL_HMESSAGE message)
{
	GL_Widget_ToggleCheck(GL_Message_GetWidget(message));
	return true;
}

// Callback for processing a visible.
static bool OnVisibleCheck(T_GL_HMESSAGE message)
{
	GL_Widget_SetVisible(GL_Message_GetWidgetById(message, GL_MEDIA_ID), true);
	return true;
}

// Callback for processing a visible.
static bool OnVisibleUncheck(T_GL_HMESSAGE message)
{
	GL_Widget_SetVisible(GL_Message_GetWidgetById(message, GL_MEDIA_ID), false);
	return true;
}

// Callback for processing a play click.
static bool OnPlay(T_GL_HMESSAGE message)
{
	GL_Widget_SetVisible(GL_Message_GetWidgetById(message, GL_STOP_ID), true);
	GL_Widget_SetVisible(GL_Message_GetWidgetById(message, GL_PAUSE_ID), true);
	GL_Widget_SetVisible(GL_Message_GetWidgetById(message, GL_PLAY_ID), false);
	GL_Media_Start(GL_Message_GetWidgetById(message, GL_MEDIA_ID));
	GL_Timer_Start(GL_Message_GetWidgetById(message, GL_TIMER_ID));
	return true;
}

// Callback for processing a stop click.
static bool OnStop(T_GL_HMESSAGE message)
{
	GL_Widget_SetVisible(GL_Message_GetWidgetById(message, GL_STOP_ID), false);
	GL_Widget_SetVisible(GL_Message_GetWidgetById(message, GL_PAUSE_ID), false);
	GL_Widget_SetVisible(GL_Message_GetWidgetById(message, GL_PLAY_ID), true);
	GL_Media_Stop(GL_Message_GetWidgetById(message, GL_MEDIA_ID));
	GL_Timer_Stop(GL_Message_GetWidgetById(message, GL_TIMER_ID));
	return true;
}

// Callback for processing a pause click.
static bool OnPause(T_GL_HMESSAGE message)
{
	GL_Widget_SetVisible(GL_Message_GetWidgetById(message, GL_STOP_ID), true);
	GL_Widget_SetVisible(GL_Message_GetWidgetById(message, GL_PAUSE_ID), false);
	GL_Widget_SetVisible(GL_Message_GetWidgetById(message, GL_PLAY_ID), true);
	GL_Media_Pause(GL_Message_GetWidgetById(message, GL_MEDIA_ID));
	GL_Timer_Stop(GL_Message_GetWidgetById(message, GL_TIMER_ID));
	return true;
}


// Filter on file to select
static bool GL_SampleMediaFilter(const char * path, bool isFile)
{
	bool result = true;
	if (isFile)
	{
		if (GL_File_MatchPath(path, "*.ogg") || 
			GL_File_MatchPath(path, "*.wav") || 
			GL_File_MatchPath(path, "*.mp4"))
		{
			result = true;
		}
		else
		{
			result = false;
		}
	}
	return result;
}


// Select file
static bool OnSelect(T_GL_HMESSAGE message)
{
	char filename[256];
	OnStop(message);
	
	if (GL_Dialog_File(GL_Message_GetGraphicLib(message), "Select media", "dir://flash/HOST", "*.*", filename, sizeof(filename), GL_SampleMediaFilter, GL_TIME_INFINITE) == GL_KEY_VALID)
	{
		// Sets video filename
		GL_Widget_SetSource(GL_Message_GetWidgetById(message, GL_MEDIA_ID),filename);
	}

	OnPlay(message);
	return true;
}

// Callback on media ended
static bool OnMediaEnded(T_GL_HMESSAGE message)
{
	GL_Message_SetResult(message, 0);
	return true;
}

// Sample of player
void GL_SamplePlayer(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	T_GL_HWIDGET media;
	T_GL_HWIDGET mainLayout;
	T_GL_HWIDGET buttonLayout;
	T_GL_HWIDGET volumeLayout;
	T_GL_HWIDGET widget;


	// Creating a blank window
	window = GL_Window_Create(graphicLib);

		// Creating the main layout
		mainLayout = GL_Layout_Create(window);

		// Creating text label
		widget = GL_Label_Create(mainLayout);

			// Select the cells in the main layout
			GL_Widget_SetItem(widget, 0, 0);

			// Set text
			GL_Widget_SetText(widget, "Video hidden");


		// Creating the refresh timer
		widget = GL_Timer_Create(window);

			// Sets the timer interval
			GL_Timer_SetInterval(widget, 500);

			// Start the timer
			GL_Timer_Start(widget);

			// Registering a callback on time change
			GL_Widget_RegisterCallback(widget, GL_EVENT_TIMER_OUT, OnRefresh);

			// Set the id of the media
			GL_Widget_SetId(widget, GL_TIMER_ID);


		// Creating a media widget
		media = GL_Media_Create(mainLayout);

			// Select the cells in the main layout
			GL_Widget_SetItem(media, 0, 0);

			// Set the id of the media
			GL_Widget_SetId(media, GL_MEDIA_ID);

			// Sets video filename
			GL_Widget_SetSource(media,"file://flash/HOST/INGENICO.MP4");

			// Registering a callback. This callback will be called every click on the media
			GL_Widget_RegisterCallback(media, GL_EVENT_STYLUS_CLICK, OnVideoClick);

			// Registering a callback. This callback will be called when the video ended
			GL_Widget_RegisterCallback(media, GL_EVENT_MEDIA_ENDED, OnMediaEnded);

			// Register shortcut to quit
			GL_Widget_SetShortcut(media, GL_KEY_VALID);

			// Force the video to shrink its size according to space available
			GL_Widget_SetShrink(media, GL_DIRECTION_ALL);

			// Force the video to expand
			GL_Widget_SetExpand(media, GL_DIRECTION_ALL);


		// Creating the time scrollbar
		widget = GL_HSlider_Create(mainLayout);

			// Select the cells in the main layout
			GL_Widget_SetItem(widget, 0, 1);

			// Set the id of the time
			GL_Widget_SetId(widget, GL_TIME_ID);

			// Registering a callback on time change
			GL_Widget_RegisterCallback(widget, GL_EVENT_HORIZONTAL_SCROLL, OnTimeChanged);

		
		// Creating the volume layout
		volumeLayout = GL_Layout_Create(mainLayout);

			// Select the cells in the main layout
			GL_Widget_SetItem(volumeLayout, 0, 2);

			// Allows the expansion in width only to group the buttons in the bottom of the window
			GL_Widget_SetGrow(volumeLayout, GL_DIRECTION_WIDTH);

			// Creating the volume label
			widget = GL_Label_Create(volumeLayout);

				// Select the cells in the volume layout
				GL_Widget_SetItem(widget, 0, 0);

				// Sets the label text
				GL_Widget_SetText(widget, "Vol");
				
				// Set small font
				GL_Widget_SetFontScale(widget, GL_SCALE_XXSMALL);

				// Inhibit grow
				GL_Widget_SetGrow(widget, GL_DIRECTION_NONE);

				// Not enlarge text
				GL_Widget_SetExpand(widget, GL_DIRECTION_NONE);


			// Create the slider volume
			widget = GL_HSlider_Create(volumeLayout);

				// Select the cells in the volume layout
				GL_Widget_SetItem(widget, 1, 0);

				// Configure the slider
				GL_Widget_SetMin(widget, 0);
				GL_Widget_SetMax(widget, 255);
				GL_Widget_SetValue(widget, 50);

				// Sets the volume
				GL_Media_SetVolume(media, (byte)GL_Widget_GetValue(widget));

				// Registering a callback on slider change
				GL_Widget_RegisterCallback(widget, GL_EVENT_HORIZONTAL_SCROLL, OnVolumeChanged);

				// Allows the expansion in width only to group the buttons in the bottom of the window
				GL_Widget_SetGrow(widget, GL_DIRECTION_WIDTH);


		// Create the button layout into the main layout
		buttonLayout = GL_Layout_Create(mainLayout);

			// Select the cells in the main layout
			GL_Widget_SetItem(buttonLayout, 0, 3);

			// Allows the expansion in width only to group the buttons in the bottom of the window
			GL_Widget_SetGrow(buttonLayout, GL_DIRECTION_WIDTH);


			// Create the ratio check box
			widget = GL_CheckButton_Create(buttonLayout);

				// Select the cells in the button layout
				GL_Widget_SetItem(widget, 0, 0);

				// Set the text ratio
				GL_Widget_SetText(widget, "%%");

				// Set small font
				GL_Widget_SetFontScale(widget, GL_SCALE_XXSMALL);

				// Set the default value
				GL_Widget_SetCheck(widget, true);

				// Sets the ratio
				GL_Media_KeepRatio(media, GL_Widget_GetCheck(widget));
				
				// Registering a callback on click
				GL_Widget_RegisterCallback(widget, GL_EVENT_STYLUS_CLICK, OnRatioClick);

				// Registering a callback on check
				GL_Widget_RegisterCallback(widget, GL_EVENT_CHECKED, OnRatioCheck);

				// Registering a callback on uncheck
				GL_Widget_RegisterCallback(widget, GL_EVENT_UNCHECKED, OnRatioUncheck);

				// Allows the expansion in width only to group the buttons in the bottom of the window
				GL_Widget_SetGrow(widget, GL_DIRECTION_WIDTH);

				// Enlarges the widget in width
				GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);


			// Create the loop check box
			widget = GL_CheckButton_Create(buttonLayout);

				// Select the cells in the button layout
				GL_Widget_SetItem(widget, 1, 0);

				// Set the text ratio
				GL_Widget_SetText(widget, "loop");

				// Set small font
				GL_Widget_SetFontScale(widget, GL_SCALE_XXSMALL);

				// Set the default value
				GL_Widget_SetCheck(widget, true);

				// Sets the loop
				GL_Media_SetLoop(media, GL_Widget_GetCheck(widget));

				// Registering a callback on click
				GL_Widget_RegisterCallback(widget, GL_EVENT_STYLUS_CLICK, OnLoopClick);

				// Registering a callback on check
				GL_Widget_RegisterCallback(widget, GL_EVENT_CHECKED, OnLoopCheck);

				// Registering a callback on uncheck
				GL_Widget_RegisterCallback(widget, GL_EVENT_UNCHECKED, OnLoopUncheck);

				// Allows the expansion in width only to group the buttons in the bottom of the window
				GL_Widget_SetGrow(widget, GL_DIRECTION_WIDTH);

				// Enlarges the widget in width
				GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);


			// Create the visible check box
			widget = GL_CheckButton_Create(buttonLayout);

				// Select the cells in the button layout
				GL_Widget_SetItem(widget, 2, 0);

				// Set the text ratio
				GL_Widget_SetText(widget, "show");

				// Set small font
				GL_Widget_SetFontScale(widget, GL_SCALE_XXSMALL);

				// Set the default value
				GL_Widget_SetCheck(widget, true);

				// Sets the loop
				GL_Widget_SetVisible(widget, GL_Widget_GetCheck(widget));

				// Registering a callback on click
				GL_Widget_RegisterCallback(widget, GL_EVENT_STYLUS_CLICK, OnVisibleClick);

				// Registering a callback on check
				GL_Widget_RegisterCallback(widget, GL_EVENT_CHECKED, OnVisibleCheck);

				// Registering a callback on uncheck
				GL_Widget_RegisterCallback(widget, GL_EVENT_UNCHECKED, OnVisibleUncheck);

				// Allows the expansion in width only to group the buttons in the bottom of the window
				GL_Widget_SetGrow(widget, GL_DIRECTION_WIDTH);

				// Enlarges the widget in width
				GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);


			// Create the play button
			widget = GL_Button_Create(buttonLayout);

				// Select the cells in the button layout
				GL_Widget_SetItem(widget, 0, 1);

				// Set the text button
				GL_Widget_SetText(widget, "play");

				// Set small font
				GL_Widget_SetFontScale(widget, GL_SCALE_XXSMALL);

				// Registering a callback
				GL_Widget_RegisterCallback(widget, GL_EVENT_STYLUS_CLICK, OnPlay);

				// Allows the expansion in width only to group the buttons in the bottom of the window
				GL_Widget_SetGrow(widget, GL_DIRECTION_WIDTH);

				// Enlarges the widget in width
				GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);

				// Set the id of the button
				GL_Widget_SetId(widget, GL_PLAY_ID);

				// Hide the button
				GL_Widget_SetVisible(widget, false);


			// Create the pause button
			widget = GL_Button_Create(buttonLayout);

				// Select the cells in the button layout
				GL_Widget_SetItem(widget, 0, 1);

				// Set the text button
				GL_Widget_SetText(widget, "pause");

				// Set small font
				GL_Widget_SetFontScale(widget, GL_SCALE_XXSMALL);

				// Registering a callback
				GL_Widget_RegisterCallback(widget, GL_EVENT_STYLUS_CLICK, OnPause);

				// Allows the expansion in width only to group the buttons in the bottom of the window
				GL_Widget_SetGrow(widget, GL_DIRECTION_WIDTH);

				// Enlarges the widget in width
				GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);

				// Set the id of the button
				GL_Widget_SetId(widget, GL_PAUSE_ID);


			// Create the stop button
			widget = GL_Button_Create(buttonLayout);

				// Select the cells in the button layout
				GL_Widget_SetItem(widget, 1, 1);

				// Set the text button
				GL_Widget_SetText(widget, "stop");

				// Set small font
				GL_Widget_SetFontScale(widget, GL_SCALE_XXSMALL);

				// Registering a callback
				GL_Widget_RegisterCallback(widget, GL_EVENT_STYLUS_CLICK, OnStop);

				// Allows the expansion in width only to group the buttons in the bottom of the window
				GL_Widget_SetGrow(widget, GL_DIRECTION_WIDTH);

				// Enlarges the widget in width
				GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);

				// Set the id of the button
				GL_Widget_SetId(widget, GL_STOP_ID);


			// Create the select button
			widget = GL_Button_Create(buttonLayout);

				// Select the cells in the button layout
				GL_Widget_SetItem(widget, 2, 1);

				// Set the text 
				GL_Widget_SetText(widget, "sel");

				// Set small font
				GL_Widget_SetFontScale(widget, GL_SCALE_XXSMALL);

				// Registering a callback
				GL_Widget_RegisterCallback(widget, GL_EVENT_STYLUS_CLICK, OnSelect);

				// Allows the expansion in width only to group the buttons in the bottom of the window
				GL_Widget_SetGrow(widget, GL_DIRECTION_WIDTH);

				// Enlarges the widget in width
				GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);

				// Set the id of the button
				GL_Widget_SetId(widget, GL_SELECT_ID);

#ifdef _DEBUG
			// Create the progress label
			widget = GL_Label_Create(buttonLayout);

				// Select the cells in the button layout
				GL_Widget_SetItem(widget, 2, 1);

				// Set small font
				GL_Widget_SetFontScale(widget, GL_SCALE_XXSMALL);

				// Set the id of the widget
				GL_Widget_SetId(widget, GL_PROGRESS_ID);

				// Allows the expansion in width only to group the buttons in the bottom of the window
				GL_Widget_SetGrow(widget, GL_DIRECTION_WIDTH);

				// Enlarges the widget in width
				GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);

				// Progress animation
				GL_Widget_SetText(widget,"|");
#endif

	// Here we loop indefinitely until a video click
	GL_Window_MainLoop(window);
	
	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
