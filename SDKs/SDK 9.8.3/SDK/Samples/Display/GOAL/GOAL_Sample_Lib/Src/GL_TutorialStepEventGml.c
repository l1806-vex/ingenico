#include "GL_GraphicLib.h"
#include "widgetMappings.h"

// On click ok button event
static bool GL_Tutorial_OnOkClick(T_GL_HMESSAGE message)
{
	GL_Message_SetResult(message, GL_KEY_VALID);
	return true;
}

// On click cancel button event
static bool GL_Tutorial_OnCancelClick(T_GL_HMESSAGE message)
{
	GL_Message_SetResult(message, GL_KEY_CANCEL);
	return true;
}


void GL_TutorialStepEventGml(void)
{
	// Creates the graphic lib instance. The creation of the graphics library takes an important time, it is recommended to do creation once at application startup and use it for all windows created after.
	T_GL_HGRAPHIC_LIB gl = GL_GraphicLib_Create();

	// Load window ressource file
	T_GL_HWIDGET window = GL_GraphicLib_ReadResource(gl, "dal://StepEvent");

	// Register event callback
	GL_Widget_RegisterCallbackById(window, GL_ID_OK,     GL_EVENT_STYLUS_CLICK, GL_Tutorial_OnOkClick);
	GL_Widget_RegisterCallbackById(window, GL_ID_CANCEL, GL_EVENT_STYLUS_CLICK, GL_Tutorial_OnCancelClick);

	if (GL_Window_MainLoop(window) == GL_KEY_VALID)
	{
		// Futur treatment
	}

	// Destroy the window
	GL_Widget_Destroy(window);

	// Destroy the graphic lib instance
	GL_GraphicLib_Destroy(gl);
}
