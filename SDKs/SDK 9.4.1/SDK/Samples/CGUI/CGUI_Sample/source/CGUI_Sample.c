/** 
Description
-----------

CGUI_Sample is a sample application which manages screens and events using the CGUI Engine.
It shows how to push screens designed in HTML and Javascript and how to process the user events.

*/
#include "sdk30.h"
#include "WGUI.h"
#include "CGUI_Sample.h"

#define WAIT(X) ttestall(0,X/10);


#ifdef __cplusplus
extern "C"
{
#endif

// Wait Browser Event
static WGUI_HTML_EVENT_HANDLE WGUI_Tool_SleepBrowserEvent(WGUI_BROWSER_HANDLE browser, WGUI_CANVAS_HANDLE canvas)
{
	WGUI_HTML_EVENT_HANDLE evt = 0;

	// Dispatch event while no html event fire
	do
	{
		// Dispatch keyboard, mouse and timer event to all browsers
		WGUI_Canvas_DispatchEvent(canvas);
		
		// Obtain html event
		WGUI_Browser_GetHtmlEvent(browser, &evt);
	}
	while (evt == 0);
	
	return evt;
}


/** Test Sample List */
void CGUI_Sample(void)
{
	WGUI_CANVAS_HANDLE canvas;
	unsigned int width = 0;
	unsigned int height = 0;

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

		// Create browser
		browser = WGUI_Browser_Create(canvas);

		// If browser created
		if (browser)
		{
			WGUI_HTML_EVENT_HANDLE evt;
			char action[128];

			// If Isc350 detected (screen larger than 320px)
			if (width > 320)
			{
				// Assign others navigation key (the arrow keys are not available)
				WGUI_Keymap_BindOneKey(browser, WGUI_TELIUM_KEY_F, WGUI_KEY_FOCUS_PREVIOUS);
				WGUI_Keymap_BindOneKey(browser, WGUI_TELIUM_KEY_DOT, WGUI_KEY_FOCUS_NEXT);
			}

			//Don't display loading bar
			WGUI_Browser_SetOption(browser,WGUI_BROWSER_LOADING_BAR_DELAY,WGUI_INFINITE);
			//Allow template replacement
			WGUI_Browser_SetOption(browser, WGUI_BROWSER_TEMPLATE_MODE, WGUI_TEMPLATE_ACTIVATE);
			WGUI_Template_AddTagAscii(browser,"TERMINAL","Terminal from application",1);
			WGUI_Browser_LoadUrl(browser, "@tar:///param/"_ING_APPLI_DATA_FILE_BINARY_NAME".tar/List.html", 1);

			do
			{
				// Wait for page submission
				evt = WGUI_Tool_SleepBrowserEvent(browser, canvas);

				// Get the "action" variable from html event
				if(WGUI_HtmlEvent_GetVariableAscii(evt,"Action",action,sizeof(action)) == WGUI_OK)
				{
					if(strcmp(action,"IList1") == 0)
					{
						//Load Icon List 1
						WGUI_Browser_LoadUrl(browser, "@tar:///param/"_ING_APPLI_DATA_FILE_BINARY_NAME".tar/IList.html", 1);
					}
					else if(strcmp(action,"IList2") == 0)
					{
						//Load Icon List 2
						WGUI_Browser_LoadUrl(browser, "@tar:///param/"_ING_APPLI_DATA_FILE_BINARY_NAME".tar/IList2.html", 1);
					}
					else if(strcmp(action,"Exit") == 0)
					{
						break;
					}
					else if(strcmp(action,"Back") == 0)
					{
						//Load Primary list
						WGUI_Browser_LoadUrl(browser, "@tar:///param/"_ING_APPLI_DATA_FILE_BINARY_NAME".tar/List.html", 1);
					}
					else if(strcmp(action,"SettForm") == 0)
					{
						//Change USER template for next reload
						if(WGUI_HtmlEvent_GetVariableAscii(evt,"Login",action,sizeof(action)) == WGUI_OK)
						{
							WGUI_Template_AddTagAscii(browser,"USER",action,1);
						}
					}
				}
			}
			while(1);

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
