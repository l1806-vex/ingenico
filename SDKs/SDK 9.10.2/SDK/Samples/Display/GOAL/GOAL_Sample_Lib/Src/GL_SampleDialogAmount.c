#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog amount
void GL_SampleDialogAmount(T_GL_HGRAPHIC_LIB graphicLib)
{
	char amount[100] = "12345678";
	ulong result;

	// Example of entering an amount
	result = GL_Dialog_Amount (graphicLib, "Amount", "ENTER AMOUNT :", "/d/d/d,/d/d/d,/d/d/D./D/D", amount, sizeof(amount), "Eur", GL_ALIGN_LEFT, GL_TIME_INFINITE);

	(void)result; // <- Avoid a compilation warning
}
