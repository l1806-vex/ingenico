#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Open the scheme
static unsigned long GL_SampleDialog_OpenScheme (T_GL_HSCHEME_INTERFACE interfac)
{
	// Insert code here to open pin scheme
	(void)(interfac);
	return GL_RESULT_SUCCESS;
}

// Close the scheme
static void GL_SampleDialog_CloseScheme (T_GL_HSCHEME_INTERFACE interfac)
{
	// Insert code here to close pin scheme
	(void)(interfac);
}

// Refresh display
static unsigned long GL_SampleDialog_RefreshScheme(T_GL_HSCHEME_INTERFACE interfac, T_GL_HWIDGET label)
{
	// All lines of this function must be replaced by the request input on the scheme
	unsigned long result = GL_RESULT_SUCCESS; 
	
	switch(*(int*)interfac->privateData)
	{
	case 0: GL_Widget_SetText(label, "----");    break;
	case 1: GL_Widget_SetText(label, "*");     break;
	case 2: GL_Widget_SetText(label, "***");   break;
	case 3: GL_Widget_SetText(label, "****");  break;
	case 4: GL_Widget_SetText(label, "***");   break;
	case 5: GL_Widget_SetText(label, "**");    break;
	case 6: result = GL_KEY_VALID;             break; // return GL_KEY_VALID to exit the dialog 
	}

	(*((int*)interfac->privateData)) ++;
	return result;
}


// Sample of dialog scheme
void GL_SampleDialogScheme(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;
	T_GL_SCHEME_INTERFACE schemeInterface;
	int state = 0;

	// Initializes interface scheme management
	schemeInterface.open        = GL_SampleDialog_OpenScheme;
	schemeInterface.close       = GL_SampleDialog_CloseScheme;
	schemeInterface.refresh     = GL_SampleDialog_RefreshScheme;
	
	// Put here the pointer on your data private
	schemeInterface.privateData = &state;

	// Example of entering a pin code
	result = GL_Dialog_Scheme (graphicLib, "Password", "Enter your pin", "Enter your code\nfrom prying eyes", &schemeInterface);
}
