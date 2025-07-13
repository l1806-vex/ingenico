/** 
Description
-----------

CGUI_Retrieve is a sample application which manages a simple page
which send datas to the application.
See sdk chm section CGUI Guidelines for more informations
*/

#include "sdk30.h"
#include "WGUI.h"
#include "CGUI_Retrieve.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** Display a form page on the screen and then the result*/
void CGUI_Retrieve(void)
{
	WGUI_CANVAS_HANDLE canvas;
	unsigned int width = 0, height = 0;

	// Initialize WGUI library
	WGUI_DLL_Init();

	// Get screen size info
	WGUI_Display_GetInfo(&width, &height, 0);

	// Create canvas
	canvas = WGUI_Canvas_Create(WGUI_CANVAS_SCREEN, 0, 0, width, height);

	// If canvas created
	if (canvas)
	{
		WGUI_BROWSER_HANDLE browser;

		// Display mouse cursor
		WGUI_Canvas_SetCursor(canvas, WGUI_CURSOR_CROSS);

		// Create browser
		browser = WGUI_Browser_Create(canvas);

		// If browser created
		if (browser)
		{
			char name[256];
			WGUI_HTML_EVENT_HANDLE evt = 0;
			WGUI_HTML_EVENT_TYPE type = 0;
			int i = 0;

			//Don't display loading bar
			WGUI_Browser_SetOption(browser,WGUI_BROWSER_LOADING_BAR_DELAY,WGUI_INFINITE);
			//Allow template replacment
			WGUI_Browser_SetOption(browser, WGUI_BROWSER_TEMPLATE_MODE, WGUI_TEMPLATE_ACTIVATE);

			//Load page
			WGUI_Browser_LoadUrl(browser, "tar:///param/"_ING_APPLI_DATA_FILE_BINARY_NAME".tar/Retrieve.html", 1);

			//loop until an event occurs
			while(evt == 0)
			{
				WGUI_Canvas_DispatchEvent (canvas);
				WGUI_Browser_GetHtmlEvent (browser, &evt);
				//Wait only get event type
				if(evt)
				{
					WGUI_HtmlEvent_GetType(evt, &type);
					if(type != WGUI_HTML_EVENT_GET)
						evt = 0;
				}
			}

			//prepare result template tag
			WGUI_Template_AddTagAscii(browser,"RECEIVED", "Nothing received",1);

			if(WGUI_HtmlEvent_GetVariableAscii(evt, "name", name, sizeof(name)) == WGUI_OK)
			{
				//name variable contain the value of the form field
				WGUI_Template_AddTagAscii(browser,"RECEIVED", name,1);
			}else
			{
				if(WGUI_HtmlEvent_GetVariableAscii(evt, "Return", name, sizeof(name)) == WGUI_OK)
				{
					//In this sample variable name must contain "Cancel"
					WGUI_Template_AddTagAscii(browser,"RECEIVED", "User canceled data submission",1);
				}
			}

			//Load result page
			WGUI_Browser_LoadUrl(browser, "@tar:///param/"_ING_APPLI_DATA_FILE_BINARY_NAME".tar/Result.html", 1);

			//Display result page for a certain amount of time
			for(i=0;i<200;i++)
				WGUI_Canvas_DispatchEvent (canvas);


			//Flush all tags stored in the browser
			WGUI_Template_FlushTags(browser);



			// Destroy browser
			WGUI_Browser_Destroy(browser);
		}

		// Destroy canvas
		WGUI_Canvas_Destroy(canvas);
	}

	// Terminate WGUI library
	WGUI_DLL_Terminate();
}

#ifdef __cplusplus
}
#endif
