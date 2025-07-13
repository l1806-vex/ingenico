#include "GL_GraphicLib.h"
#include "GL_Samples.h"
#include "widgetMappings.h"
#include "resources\Calculator.h"


#ifdef WIN32
#define APPLI_TYPE_TEST "?appli_type=7AFE"
#else
#define APPLI_TYPE_TEST 
#endif

// Callback for processing a click message.
// The "message" contains details of the message received by the window
static bool OnClick(T_GL_HMESSAGE message)
{
	// Here we force the value to 0 to release the application of the loop on @ref GL_Window_Dispatch,
	// this assignment is an example and may be replaced by a more complete treatment 
	GL_Message_SetResult(message, 0);
	return true;
}

// Example of creating a user control for a simple arithmetic operation
void GL_SampleUserControl(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET window;
	char message[256];

	// Initialization function of the user control, this function will register all the callback processing calculator 
	// YOU MUST ALWAYS REGISTER USER CONTROL INIT CALLBACK BEFORE READ THE RESSOURCE
	GL_UserControl_Register(graphicLib, "dal://calculator" APPLI_TYPE_TEST, GL_SampleCalculatorInit);

	// Load window ressource file
	window = GL_GraphicLib_ReadResource(graphicLib, "dal://usecalculator" APPLI_TYPE_TEST);

	// Registering a callback. This callback will be called every click on the button
	GL_Widget_RegisterCallbackById(window, GL_ID_OK, GL_EVENT_STYLUS_CLICK, OnClick);

	// Place the focus on OK button
	GL_Widget_SetFocus(GL_Widget_SearchId(window,GL_ID_OK));

	// Sets the initial value of the first operation
	GL_Widget_SetText(GL_UserControl_SearchId(window, GL_ID_OPERATION_1, GL_ID_OPERAND_1), "123");
	GL_Widget_SetText(GL_UserControl_SearchId(window, GL_ID_OPERATION_1, GL_ID_OPERAND_2), "321");

	// Sets the initial value of the second operation
	GL_Widget_SetText(GL_UserControl_SearchId(window, GL_ID_OPERATION_2, GL_ID_OPERAND_1), "456");
	GL_Widget_SetText(GL_UserControl_SearchId(window, GL_ID_OPERATION_2, GL_ID_OPERAND_2), "654");

	// Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult), 
	// which was made earlier in the call back OnClick
	GL_Window_MainLoop(window);

	// Extracts the result of two operation
	sprintf(message,"%s %s %s = %s\n%s %s %s = %s", 
		GL_Widget_GetText(GL_UserControl_SearchId(window, GL_ID_OPERATION_1, GL_ID_OPERAND_1)),
		GL_Widget_GetText(GL_UserControl_SearchId(window, GL_ID_OPERATION_1, GL_ID_OPERATOR)),
		GL_Widget_GetText(GL_UserControl_SearchId(window, GL_ID_OPERATION_1, GL_ID_OPERAND_2)),
		GL_Widget_GetText(GL_UserControl_SearchId(window, GL_ID_OPERATION_1, GL_ID_RESULT)),

		GL_Widget_GetText(GL_UserControl_SearchId(window, GL_ID_OPERATION_2, GL_ID_OPERAND_1)),
		GL_Widget_GetText(GL_UserControl_SearchId(window, GL_ID_OPERATION_2, GL_ID_OPERATOR)),
		GL_Widget_GetText(GL_UserControl_SearchId(window, GL_ID_OPERATION_2, GL_ID_OPERAND_2)),
		GL_Widget_GetText(GL_UserControl_SearchId(window, GL_ID_OPERATION_2, GL_ID_RESULT)));

	// Display result
	GL_Dialog_Message(graphicLib, "Result of operations", message, GL_ICON_NONE, GL_BUTTON_NONE, 1000);

	// Destruction of the window. Destruction frees all allocated memory, 
	// all the widgets attached to the window and suppress the window on the screen.
	// This call is crucial, if it forgotten you get a memory leak.
	GL_Widget_Destroy(window);
}
