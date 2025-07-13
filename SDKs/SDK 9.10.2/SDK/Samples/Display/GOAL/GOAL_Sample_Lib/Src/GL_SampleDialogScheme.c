#include "GL_GraphicLib.h"
#include "GL_Samples.h"
#if defined(__TELIUM2__)
	#include "SEC_interface.h"
	#include "schvar_def.h"
#endif


typedef struct T_GL_SCHEME_CONTEXT
{
	int state;
	int firstDisplay;
} T_GL_SCHEME_CONTEXT;


// Open the scheme
static unsigned long GL_SampleDialog_OpenScheme (T_GL_HSCHEME_INTERFACE interfac)
{
#if defined(__TELIUM2__)
	T_SEC_ENTRYCONF entryConfig;

	(void) (interfac);
	entryConfig.ucEchoChar = 0x2A;

	//char to echo
	entryConfig.ucMinDigits = 4; // min digit
	entryConfig.ucMaxDigits = 6; // max digit
	entryConfig.iFirstCharTimeOut = 60 * 1000;
	entryConfig.iInterCharTimeOut = 10 * 1000;

	if (SEC_PinEntryInit(&entryConfig, C_SEC_PINCODE) == OK)
	{
		return GL_RESULT_SUCCESS;
	}
	else
	{
		return GL_RESULT_FAILED;
	}
#else
	// Insert code here to open pin scheme
	(void)(interfac);
	return GL_RESULT_SUCCESS;
#endif
}


// Close the scheme
static void GL_SampleDialog_CloseScheme (T_GL_HSCHEME_INTERFACE interfac)
{
	// Insert code here to close pin scheme
	(void)(interfac);
}


#if defined(__TELIUM2__)
#define STAR_KEY 0x2A
// Gets a key from the pin
static int GL_SampleDialog_GetKey(unsigned int *key)
{
	int result;
	unsigned char outData;
	unsigned int eventToWait;
	unsigned int toContinue;

	result      = TRUE;
	toContinue  = TRUE;
	eventToWait = 0;

	switch(SEC_PinEntry(&eventToWait, &outData, &toContinue))
	{
	case OK:
		if (outData == STAR_KEY)
		{
			// This is a numeric key
			*key = T_NUM0;
		} 
		else
		{
			switch (outData)
			{
			case 0x00:
				result = FALSE;
				break;
			case 0x01:
				result = FALSE;
				break;
			default:
				*key = outData; /* T_VAL, T_ANN, T_CORR */
				break;
			}
		}
		break;

	case ERR_TIMEOUT:
		{
			result = FALSE;
		}
		break;

	default:
		{
			result = FALSE;
		}
		break;
	}

	return (result);
}
#endif


// Refresh the display
static unsigned long GL_SampleDialog_RefreshScheme(T_GL_HSCHEME_INTERFACE interfac, T_GL_HWIDGET label)
{
#if defined(__TELIUM2__)
	unsigned long result = GL_RESULT_SUCCESS;
	int cr;
	unsigned int key;
	T_GL_SCHEME_CONTEXT * schemeContext = (T_GL_SCHEME_CONTEXT*)interfac->privateData;

	if (schemeContext->firstDisplay == 0)
	{
		schemeContext->firstDisplay = 1;
		GL_Widget_SetText(label, "----");
	}
	else
	{
		cr = GL_SampleDialog_GetKey(&key);
		if (cr == FALSE)
		{
			result = GL_RESULT_INACTIVITY;
		}
		else
		{
			switch (key)
			{
			case T_VAL:
				// end of the enter pin
				result = GL_RESULT_SHORTCUT; //any return value different than OK will stop
				break;

			case T_ANN:
				// cancel the enter pin
				result = CANCEL_INPUT;
				break;

			case T_CORR:
				// correction
				if (schemeContext->state != 0)
				{
					schemeContext->state--;
				}
				break;

			default:
				schemeContext->state++;
				break;
			}
		}

		if (result == GL_RESULT_SUCCESS)
		{
			// Manage the display
			switch (schemeContext->state)
			{
			case 0:
				GL_Widget_SetText(label, "----");
				break;
			case 1:
				GL_Widget_SetText(label, "*");
				break;
			case 2:
				GL_Widget_SetText(label, "**");
				break;
			case 3:
				GL_Widget_SetText(label, "***");
				break;
			case 4:
				GL_Widget_SetText(label, "****");
				break;
			case 5:
				GL_Widget_SetText(label, "*****");
				break;
			case 6:
				GL_Widget_SetText(label, "******");
				break; // return GL_KEY_VALID to exit the dialog
			}
		}
	}

	return result;
#else
	// All lines of this function must be replaced by the request input on the scheme
	unsigned long result = GL_RESULT_SUCCESS;
	T_GL_SCHEME_CONTEXT * schemeContext = (T_GL_SCHEME_CONTEXT*)interfac->privateData;

	switch(schemeContext->state)
	{
	case 0: GL_Widget_SetText(label, "----");    break;
	case 1: GL_Widget_SetText(label, "*");     break;
	case 2: GL_Widget_SetText(label, "***");   break;
	case 3: GL_Widget_SetText(label, "****");  break;
	case 4: GL_Widget_SetText(label, "***");   break;
	case 5: GL_Widget_SetText(label, "**");    break;
	case 6: result = GL_KEY_VALID;             break; // return GL_KEY_VALID to exit the dialog
	}

	schemeContext->state ++;
	return result;
#endif
}


// Sample of dialog scheme
void GL_SampleDialogScheme(T_GL_HGRAPHIC_LIB graphicLib)
{
	ulong result;
	T_GL_SCHEME_INTERFACE schemeInterface;
	T_GL_SCHEME_CONTEXT   schemeContext;
	
	// Initializes the scheme private context
	schemeContext.state = 0;
	schemeContext.firstDisplay = 0;

	// Initializes interface scheme management
	schemeInterface.open        = GL_SampleDialog_OpenScheme;
	schemeInterface.close       = GL_SampleDialog_CloseScheme;
	schemeInterface.refresh     = GL_SampleDialog_RefreshScheme;
	
	// Put here the pointer on your data private
	schemeInterface.privateData = &schemeContext;

	// Example of entering a pin code
	result = GL_Dialog_Scheme (graphicLib, "Password", "Enter your pin", "Enter your code\nfrom prying eyes", &schemeInterface);
	(void)result; // <- Avoid a compilation warning
}
