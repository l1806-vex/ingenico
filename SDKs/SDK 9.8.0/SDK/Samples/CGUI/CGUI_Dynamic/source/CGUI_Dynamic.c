/** 
Description
-----------

CGUI_Dynamic is a sample application which manages dynamic pages.
See sdk chm section CGUI Guidelines for more informations

*/
#include "sdk30.h"
#include "WGUI.h"
#include "CGUI_Dynamic.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** Create a response filled with categories */
WGUI_JSON_NODE DisplayCategories(void)
{
	/** Hardcoded for the sample */
	char* Cat[] = {"Fruits","Vegetables","Other"};
	WGUI_JSON_NODE node = 0, Array;
	int i=0, result = 0;

	do
	{
		//Create JSON node
		if((node = WGUI_JSON_CreateObject()) == NULL)
			break;
		//Add type in JSON object
		if(WGUI_JSON_AddItemStringAscii(node,"Type","Cat") != WGUI_OK)
			break;
		//Add an Array in JSON object
		if((Array = WGUI_JSON_AddItemArray(node,"List")) == NULL)
			break;

		//Add all categories in the List array
		for(i = 0; i < sizeof(Cat)/sizeof(Cat[0]); i++)
		{
			if(WGUI_JSON_AddStringAscii(Array,Cat[i]) != WGUI_OK)
				break;
		}

		//No error during insertion
		if(i == sizeof(Cat)/sizeof(Cat[0]))
			result = 1;
	}while(0);

	//Return node if all is done
	if(result)
		return(node);

	//An error occurred : destroy node return NULL
	if(node)
		WGUI_JSON_DestroyObject(node);
	return(NULL);
}

/** Create a response filled with product corresponding to Cat*/
WGUI_JSON_NODE DisplayProducts(const char* Category)
{
	/** Hardcoded for the sample */
	char* FProd[] = {"Apple","Lemon","Pear"};
	char* VProd[] = {"Carrot","Mushroom","Onion","Potato"};
	char* OProd[] = {"Milk","Sugar"};
	char** Arr;
	int ArrLength;
	WGUI_JSON_NODE node = 0, Array;
	int i=0, result = 0;

	//Initializing array to fill and its length
	if(strcmp(Category,"Fruits") == 0)
	{
		Arr = FProd;
		ArrLength = sizeof(FProd)/sizeof(FProd[0]);
	}else if(strcmp(Category,"Vegetables") == 0)
	{
		Arr = VProd;
		ArrLength = sizeof(VProd)/sizeof(VProd[0]);
	}else
	{
		Arr = OProd;
		ArrLength = sizeof(OProd)/sizeof(OProd[0]);
	}

	do
	{
		//Create JSON node
		if((node = WGUI_JSON_CreateObject()) == NULL)
			break;
		//Add type in JSON object
		if(WGUI_JSON_AddItemStringAscii(node,"Type","Prod") != WGUI_OK)
			break;
		//Add an Array in JSON object
		if((Array = WGUI_JSON_AddItemArray(node,"List")) == NULL)
			break;

		//Add all categories in the List array
		for(i = 0; i < ArrLength; i++)
		{
			if(WGUI_JSON_AddStringAscii(Array,Arr[i]) != WGUI_OK)
				break;
		}

		//No error during insertion
		if(i == ArrLength)
			result = 1;
	}while(0);

	//Return node if all is done
	if(result)
		return(node);

	//An error occurred : destroy node return NULL
	if(node)
		WGUI_JSON_DestroyObject(node);
	return(NULL);
}


/** Send message text on the screen*/
void CGUI_Dynamic(void)
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
			WGUI_HTML_EVENT_HANDLE evt;

			//Don't display loading bar
			WGUI_Browser_SetOption(browser,WGUI_BROWSER_LOADING_BAR_DELAY,WGUI_INFINITE);

			//Load page
			WGUI_Browser_LoadUrl(browser, "tar:///param/"_ING_APPLI_DATA_FILE_BINARY_NAME".tar/Dynamic.html", 1);

			do
			{
				// Dispatch mouse, keyboard, timer events to the browser
				WGUI_Canvas_DispatchEvent(canvas);
				// Get the html event (link clicked, form validated, xhr sent)
				WGUI_Browser_PeekHtmlEvent(browser, &evt);

				if(evt)
				{
					WGUI_HTML_EVENT_TYPE type = 0;

					//Get type of the event
					WGUI_HtmlEvent_GetType(evt, &type);

					//If from XHR (event we can answer to)
					if(type == WGUI_HTML_EVENT_XHR_GET)
					{
						//you can reply when you want until the page change
						//just continue the dispatch event loop
						WGUI_JSON_NODE response = 0;
						char value[32];

						//Verify values asked by the page
						if(WGUI_HtmlEvent_GetVariableAscii(evt, "Type", value, sizeof(value)) == WGUI_OK)
						{
							if(strcmp(value,"Cat")==0)
							{
								//Category list requested
								response = DisplayCategories();

							}else if(strcmp(value,"Prod") == 0)
							{
								//Product list requested
								//Verify Category of the product list asked by the page
								if(WGUI_HtmlEvent_GetVariableAscii(evt, "Value", value, sizeof(value)) == WGUI_OK)
								{
									response = DisplayProducts(value);
								}

							}


						}

						if(response)
						{
							//Send response to the browser
							WGUI_JSON_SendResponse(browser,response,evt);

							//Destroy response object
							WGUI_JSON_DestroyObject(response);
						}else
						{
							//Release HTML Event (event is garbaged)
							WGUI_Browser_ReleaseHtmlEvent(browser,evt);
						}
						evt = NULL;
					}
					//if it's a browsing event (link or page change)
					else
					{
						//Release HTML Event (event is garbaged)
						WGUI_Browser_ReleaseHtmlEvent(browser,evt);
					}
				}
			}while(!evt);	//Loop until an event other than xhr comes
							//case when we select a product we send a get event

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
