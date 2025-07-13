#include "GL_GraphicLib.h"
#include "string.h"
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


void GL_TutorialStepDataGml(void)
{
	// Creates the graphic lib instance. The creation of the graphics library takes an important time, it is recommended to do creation once at application startup and use it for all windows created after.
	T_GL_HGRAPHIC_LIB gl = GL_GraphicLib_Create();
	char firstName[256];
	char lastName[256];
	char birthDay[256];
	int mister, married;

	// Load window ressource file
	T_GL_HWIDGET window = GL_GraphicLib_ReadResource(gl, "dal://StepData");

	// Register event callback	
	GL_Widget_RegisterCallbackById(window, GL_ID_OK,     GL_EVENT_STYLUS_CLICK, GL_Tutorial_OnOkClick);
	GL_Widget_RegisterCallbackById(window, GL_ID_CANCEL, GL_EVENT_STYLUS_CLICK, GL_Tutorial_OnCancelClick);

	// Sets the default data
	GL_Widget_SetTextById(window, GL_ID_FIRST_NAME, "Set first name");
	GL_Widget_SetTextById(window, GL_ID_LAST_NAME,  "Set last name");
	GL_Widget_SetTextById(window, GL_ID_BIRTH_DAY,  "Set birth day");
	GL_Widget_SetCheckById(window, GL_ID_MARRIED, 0);

	// Wait the validation by the user
	if (GL_Window_MainLoop(window) == GL_KEY_VALID)
	{
		// Gets the data entered
		strncpy(firstName, GL_Widget_GetTextById(window, GL_ID_FIRST_NAME), sizeof(firstName));
		strncpy(lastName,  GL_Widget_GetTextById(window, GL_ID_LAST_NAME),  sizeof(lastName));
		strncpy(birthDay,  GL_Widget_GetTextById(window, GL_ID_BIRTH_DAY),  sizeof(birthDay));

		if (GL_Widget_GetCheckById(window, GL_ID_MR))
		{
			mister= 1;
		}
		else
		{
			mister = 0;
		}

		if (GL_Widget_GetCheckById(window, GL_ID_MARRIED))
		{
			married = 1;
		}
		else
		{
			married = 0;
		}
	}
	(void)married; // <- Avoid a compilation warning
	(void)mister; // <- Avoid a compilation warning
	
	// Destroy the window
	GL_Widget_Destroy(window);

	// Destroy the graphic lib instance
	GL_GraphicLib_Destroy(gl);
}
