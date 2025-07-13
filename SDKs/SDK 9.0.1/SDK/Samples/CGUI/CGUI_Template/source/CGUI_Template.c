/** 
Description
-----------

CGUI_Template is a sample application which manages a simple template page.
See sdk chm section CGUI Guidelines for more informations

*/
#include "sdk30.h"
#include "WGUI.h"
#include "CGUI_Template.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** Display a template page on the screen*/
void CGUI_Template(void)
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
			int i = 0;

			//Don't display loading bar
			WGUI_Browser_SetOption(browser,WGUI_BROWSER_LOADING_BAR_DELAY,WGUI_INFINITE);
			//Allow template replacement
			WGUI_Browser_SetOption(browser, WGUI_BROWSER_TEMPLATE_MODE, WGUI_TEMPLATE_ACTIVATE);
			//Add a tag
			WGUI_Template_AddTagAscii(browser, "name", "World", WGUI_TRUE);

			//Load page
			WGUI_Browser_LoadUrl(browser, "@tar:///param/"_ING_APPLI_DATA_FILE_BINARY_NAME".tar/Template.html", 1);

			for (i = 0; i < 100; i++)
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
