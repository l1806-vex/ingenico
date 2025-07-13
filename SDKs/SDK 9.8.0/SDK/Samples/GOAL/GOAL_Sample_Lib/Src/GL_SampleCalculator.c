// Example of creating a user control for a simple arithmetic operation
#include "GL_GraphicLib.h"
#include "GL_Samples.h"
#include "widgetMappings.h"
#include "resources\Calculator.h"

// Gets the operand
static long GL_Sample_GetOperand(T_GL_HWIDGET userControl, T_GL_ID operandId)
{
	long result = 0;

	// Gets the operand string value
	const char * operand = GL_Widget_GetInput(GL_Widget_SearchId(userControl, operandId));

	// Converts string into integer
	while (*operand)
	{
		result *= 10;
		result += (*operand - '0');
		operand++;
	}
	return result;
}


// Gets the operator
static char GL_Sample_GetOperator(T_GL_HWIDGET userControl)
{
	return GL_Widget_GetText(GL_Widget_SearchId(userControl, GL_ID_OPERATOR))[0];
}


// Sets the operator
static void GL_Sample_SetOperator(T_GL_HWIDGET userControl, const char * operat)
{
	GL_Widget_SetTextById(userControl, GL_ID_OPERATOR, operat);
}


// Update the result of operation
static void GL_Sample_UpdateResult(T_GL_HWIDGET userControl)
{
	char result [32];

	// Gets the operand 1 value
	long operand1 = GL_Sample_GetOperand(userControl, GL_ID_OPERAND_1);

	// Gets the operand 2 value
	long operand2 = GL_Sample_GetOperand(userControl, GL_ID_OPERAND_2);

	// Computes the result of operation
	switch(GL_Sample_GetOperator(userControl))
	{
	case '+': sprintf(result, "%d", (int)(operand1 + operand2)); break;
	case '*': sprintf(result, "%d", (int)(operand1 * operand2)); break;
	case '-': sprintf(result, "%d", (int)(operand1 - operand2)); break;
	case '/': 
		// If division possible
		if (operand2)
		{
			sprintf(result, "%d", (int)(operand1 / operand2));
		}
		else
		{
			sprintf(result, "INFINIT");
		}
		break;
	}

	// Sets the result in label
	GL_Widget_SetTextById(userControl, GL_ID_RESULT, result);
}


// Callback for processing a text change message.
// The "message" contains details of the message received by the widget
static bool GL_Sample_OnOperandChange(T_GL_HMESSAGE message)
{
	// Gets the user control associated to this message 
	T_GL_HWIDGET userControl = GL_Message_GetUserControl(message);
	GL_Sample_UpdateResult(userControl);
	return true;
}


// Changes the current operator
static bool GL_Sample_OnOperatorChange(T_GL_HMESSAGE message)
{
	// Gets the user control associated to this message 
	T_GL_HWIDGET userControl = GL_Message_GetUserControl(message);

	// According to the current operator, change it
	switch(GL_Sample_GetOperator(userControl))
	{
	// Changes the operator
	case '+': GL_Sample_SetOperator(userControl, "*"); break;
	case '*': GL_Sample_SetOperator(userControl, "-"); break;
	case '-': GL_Sample_SetOperator(userControl, "/"); break;
	case '/': GL_Sample_SetOperator(userControl, "+"); break;
	}

	// Update the result of operation
	GL_Sample_UpdateResult(userControl);
	return true;
}


// Initialization function of the user control, this function will register all the callback processing calculator 
void GL_SampleCalculatorInit(T_GL_HWIDGET userControl)
{
	// Initialize the first operator
	GL_Widget_SetTextById(userControl, GL_ID_OPERATOR, "+");

	// Register callback to update the results when the operands change 
	GL_Widget_RegisterCallbackById(userControl, GL_ID_OPERAND_1, GL_EVENT_TEXT_CHANGED, GL_Sample_OnOperandChange);
	GL_Widget_RegisterCallbackById(userControl, GL_ID_OPERAND_2, GL_EVENT_TEXT_CHANGED, GL_Sample_OnOperandChange);

	// Register callback to change the operator
	GL_Widget_RegisterCallbackById(userControl, GL_ID_OPERATOR, GL_EVENT_STYLUS_CLICK, GL_Sample_OnOperatorChange);

	// Update the result of operation : in this it is used to update the result with initial operands
	GL_Sample_UpdateResult(userControl);
}


