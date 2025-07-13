#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog signature
void GL_SampleDialogSignature(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;

	// Example of signature capture
	result = GL_Dialog_Signature (graphicLib, "Signature", "Sign please", "file://flash/HOST/signsuite/SIGNATURE.SIG", GL_TIME_INFINITE);
	(void)result; // <- Avoid a compilation warning
}
