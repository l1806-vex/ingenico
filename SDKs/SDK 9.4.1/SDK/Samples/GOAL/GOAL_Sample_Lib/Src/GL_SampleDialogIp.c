#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Sample of dialog ip
void GL_SampleDialogIp(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_IP ip = 0xC0A80101;
	ulong result;

	// Example of entering a date
	result = GL_Dialog_Ip (graphicLib, "Ip", "ENTER SERVER IP :", &ip, GL_TIME_INFINITE);
}
