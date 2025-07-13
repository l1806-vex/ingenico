//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  GOAL.C                              (Copyright INGENICO 2012)
//============================================================================
//  Created :       17-July-2012     Kassovic
//  Last modified : 17-July-2012     Kassovic
//  Module : GOAL
//                                                                          
//  Purpose :                                                               
//  Existing TELIUM Graphic User Interface:
//  - System function level (OEM-C: historical text interface => printf, etc...)
//    Native method (obsolete)
//    Does not support font
//    No access to color function, only monochrome mode
//  - Graphic library level (LIBGR: legacy GRaphical Monochrome LIBrary => DrawString, etc...)
//    Graphic functionalities
//    Support fonts
//    No access to color functions, only colorized mode
//  - Color library level (legacy COLOR library => DrawText, etc...)
//    Full color functionalities
//    Support fonts
//    Only for color terminals
//
//  Since the beginning of 2012, Graphic Object Advanced Library (GOAL) is available:
//  GOAL provides 3 usage modes:
//  - Predefined dialog box mode (provides a set of high level UI functions)
//    MESSAGE to display a message. The user can optionally react on it.
//    INPUT to enter information of different types (like date, hour, amount, formatted field, etc...)
//    CHOICE to provide different ways of selecting  elements through a text or icons list.
//    MULTIMEDIA to render a multimedia file.
//  - Modular customization mode (How to build your own screen with file resource)
//    Group of simple widgets objects (Text, Graphical, Bar & Slider, etc...)
//    Group of complex widgets objects (Containers, Plug-in, Miscellaneous, etc...)
//    Available soon a WYSIWYG, otherwise use DAL (Data Abstraction Layer)
//  - Monolithic customization mode (How to build your own screen in 'C' using predefined API(s))
//    GOAL generic API(s) (GraphicLib_, Widget_, Message_, etc...)
//    GOAL specific API(s) (Button_, CheckButton_, Icon_, Label_, Layout_, List_, ScrollView_, etc...)
//
//  This file will provides a set of API(s) developed in Monolithic customization mode to handle
//  text, drawing, picture on screen and printing.
//
//  List of routines in file :
//      CallBackPressKey : Call back for processing a key pressed.
//      CallBackValidKey : Call back for processing a valid key pressed or touched.
//      CallBackCancelKey : Call back for processing a cancel key pressed or touched.
//      CallBackDownKey : Call back for processing a down key pressed or touched.
//      CallBackUpKey : Call back for processing a up key pressed or touched.
//      CallBackTimeout : Call back for processing a timeout message.
//                                *** SCREEN ***
//      GoalCreateScreen : Create a screen context.
//      GoalClrScreen : Clear all widgets on screen context.
//      GoalRefreshScreen : Refresh all widgets on screen.
//      GoalDspLine : Display a line on screen.
//      GoalDspMultiLine : Display multi-lines on screen.
//      GoalGetKey : Wait for shortcut key pressed or touched.
//      GoalDestroyScreen : Destroy a screen context.
//                                *** DRAWING ***
//      GoalCreateDrawing : Create  a drawing context.
//      GoalClrDrawing : Clear all widgets on drawing context.
//      GoalDrawLine : Draw a line on screen.
//      GoalDrawRect : Draw a rectangle on screen.
//      GoalDrawEllipse : Draw an ellipse on screen.
//      GoalDrawText : Draw a text on screen.
//      GoalDestroyDrawing : Destroy a drawing context.
//                                *** PICTURE ***
//      GoalCreatePicture : Create a picture context.
//      GoalClrPicture : Clear all widgets on picture context.
//      GoalDspPicture : Display a picture on screen.
//      GoalDestroyPicture : Destroy a picture context.
//                                *** DOCUMENT ***
//      GoalCreateDocument : Create a document context.
//      GoalPrnLine : Build a line on document.
//      GoalMultiLine : Build multi-lines on document.
//      GoalPrnPicture : Build a picture on document.
//      GoalPrnDocument : Print the document built.
//      GoalDestroyDocument : Destroy a document context.
//                            
//  File history :
//  071712-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES
//****************************************************************************
#include "Goal.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
int IsColorDisplay(void);
int IsPrinter(void);

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
#define CHECK(CND,LBL) {if(!(CND)){goto LBL;}}

// Maximum line supported by the layout (Screen)
// =============================================
#define MAX_LINE    9

// Widget Id(s)
// ============
#define TIMER_ID       0x0000
#define LABEL_0_ID     0x0100
#define BUTTON_VAL_ID  0x0200
#define BUTTON_CAN_ID  0x0300
#define BUTTON_DOWN_ID 0x0400
#define BUTTON_UP_ID   0x0500
#define LAYOUT2_ID     0x0600
#define DRAWING_ID     0x0700
#define PICTURE_ID     0x0800
#define LAYOUT3_ID     0x0900

// Result returns from the call back function
// ==========================================
#define RES_VALID_STATUS  0  // Valid key pressed or touched (Green key)
#define RES_CANCEL_STATUS 1  // Red key pressed or touched (Red key)
#define RES_DOWN_STATUS   2  // Down key pressed or touched
#define RES_UP_STATUS     3  // Up key pressed or touched
#define RES_TIMER_STATUS  4  // Timeout expiration
#define RES_PRESS_STATUS  5  // Key pressed

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
	/* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
	/* */

//****************************************************************************
//              bool CallBackPressKey(T_GL_HMESSAGE xMessage)
// This function handles the call back for processing a key pressed and returns
// its value to GL_Window_MainLoop.
// This function has parameters.
//   xMessage (I-) : Message handle (Stylus button, key, timer, ...)
// This function has return value.
//  true : When leaving the loop GL_Window_MainLoop
//  false : When leaving the loop GL_Window_MainLoop
//****************************************************************************

static bool CallBackPressKey(T_GL_HMESSAGE xMessage)
{
	T_GL_WCHAR ulKey;

	// Retrieve key pressed
	ulKey = GL_Message_GetKey(xMessage);

    // Sets the data user attached to the window
    GL_Message_SetUserData(xMessage, &ulKey, sizeof(ulKey));

	// Will exit the application from the loop on GL_Window_MainLoop by returning
	// the result RES_PRESS_STATUS
	GL_Message_SetResult(xMessage, RES_PRESS_STATUS);

	// Force the value to true to release the application from the loop on GL_Window_MainLoop
	return true;
}

//****************************************************************************
//              bool CallBackValidKey(T_GL_HMESSAGE xMessage)
// This function handles the call back for processing a valid key pressed or
//  touched.
// This function has parameters.
//   xMessage (I-) : Message handle (Stylus button, key, timer, ...)
// This function has return value.
//  true : When leaving the loop GL_Window_MainLoop
//  false : When leaving the loop GL_Window_MainLoop
//****************************************************************************

static bool CallBackValidKey(T_GL_HMESSAGE xMessage)
{
	// Will exit the application from the loop on GL_Window_MainLoop by returning
	// the result RES_VALID_STATUS
	GL_Message_SetResult(xMessage, RES_VALID_STATUS);

	// Force the value to true when releasing the application from the main loop
	return true;
}

//****************************************************************************
//              bool CallBackCancelKey(T_GL_HMESSAGE xMessage)
// This function handles the call back for processing a cancel key pressed or
//  touched.
// This function has parameters.
//   xMessage (I-) : Message handle (Stylus button, key, timer, ...)
// This function has return value.
//  true : When leaving the loop GL_Window_MainLoop.
//  false : When leaving the loop GL_Window_MainLoop.
//****************************************************************************

static bool CallBackCancelKey(T_GL_HMESSAGE xMessage)
{
	// Will exit the application from the loop on GL_Window_MainLoop by returning
	// the result RES_CANCEL_STATUS
	GL_Message_SetResult(xMessage, RES_CANCEL_STATUS);

	// Force the value to true when releasing the application from the main loop
	return true;
}

//****************************************************************************
//              bool CallBackDownKey(T_GL_HMESSAGE xMessage)
// This function handles the call back for processing a down key pressed or
//  touched.
// This function has parameters.
//   xMessage (I-) : Message handle (Stylus button, key, timer, ...)
// This function has return value.
//  true : When leaving the loop GL_Windpw_MainLoop.
//  false : When leaving the loop GL_Window_MainLoop.
//****************************************************************************

static bool CallBackDownKey(T_GL_HMESSAGE xMessage)
{
	// Will exit the application from the loop on GL_Window_MainLoop by returning
	// the result RES_DOWN_STATUS
	GL_Message_SetResult(xMessage, RES_DOWN_STATUS);

	// Force the value to true when releasing the application from the main loop
	return true;
}

//****************************************************************************
//              bool CallBackUpKey(T_GL_HMESSAGE xMessage)
// This function handles the call back for processing a up key pressed or
//  touched.
// This function has parameters.
//   xMessage (I-) : Message handle (Stylus button, key, timer, ...)
// This function has return value.
//  true : When leaving the loop GL_Window_MainLoop.
//  false : When leaving the loop GL_Window_MainLoop.
//****************************************************************************

static bool CallBackUpKey(T_GL_HMESSAGE xMessage)
{
	// Will exit the application from the loop on GL_Window_MainLoop by returning
	// the result RES_UP_STATUS
	GL_Message_SetResult(xMessage, RES_UP_STATUS);

	// Force the value to true when releasing the application from the main loop
	return true;
}

//****************************************************************************
//              bool CallBackTimeout(T_GL_HMESSAGE xMessage)
// This function handles the call back for processing a timeout message.
// This function has parameters.
//   xMessage (I-) : Message handle (Stylus button, key, timer, ...)
// This function has return value.
//  true : When leaving the loop GL_Window_MainLoop.
//  false : When leaving the loop GL_Window_MainLoop.
//****************************************************************************

static bool CallBackTimeout(T_GL_HMESSAGE xMessage)
{
	// Will exit the application from the loop on GL_Window_MainLoop by returning
	// the result RES_TIMER_STATUS
	GL_Message_SetResult(xMessage, RES_TIMER_STATUS);

	// Stop the timer
	GL_Timer_Stop(GL_Message_GetWidget(xMessage));

	// Force the value to true when releasing the application from the main loop
	return true;
}

//##############################################################################
//                                   SCREEN
//##############################################################################

//****************************************************************************
//      T_GL_HWIDGET GoalCreateScreen (T_GL_HGRAPHIC_LIB xGraphicLib,
//                                     const ST_LINE txLine[],
//                                     ushort usMaxLine,
//                                     T_GL_ENCODING_CHARSET eCharSet)
// This function creates a screen context which is composed of:
//  - A timer to exit from this screen.
//  - A number of line which composed this screen.
//  - Shortcut keys on 4 buttons to react on this screen:
//      Cancel Key, Down Key, Up Key and Valid Key
//  !!! All other keys detection will be done with standard Telium functions.
//  - Encoding charsets:
//      GL_ENCODING_UTF8 => Unicode utf8
//      GL_ENCODING_ISO_8859_X => ISO 8859
// This function has parameters.
//   xGraphicalLib (I-) : Graphic library context handle.
//   txLine[] (I-) : Screen properties.
//   usMaxLine (I-) : Number of line which composed the screen.
//   eCharSet (I-) : Encoding charsets.
// This function has return value.
//   !NULL : Pointer to the handle of the screen.
//   NULL : Screen failed
//****************************************************************************

T_GL_HWIDGET GoalCreateScreen (T_GL_HGRAPHIC_LIB xGraphicLib, const ST_DSP_LINE txLine[], ushort usMaxLine, T_GL_ENCODING_CHARSET eCharSet)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xWindow, xTimer, xLayout, xLabel, xLayout2, xButtonVal, xButtonCan, xButtonDown, xButtonUp;
	bool bTouch=FALSE;
	ushort usLine;

	// Build screen context with MAX labels and 4 buttons (Cancel, Valid, Down and Up)
	// *******************************************************************************
	xWindow = GL_Window_Create(xGraphicLib);                                          // Create a window in the user area
	CHECK(xWindow!=NULL, lblEnd);

	GL_GraphicLib_SetCharset(xGraphicLib, eCharSet);                                  // Change the encoding charset of the graphic library

	bTouch = GL_GraphicLib_IsTouchPresent(xGraphicLib);                               // Is it a touch screen?

	xTimer = GL_Timer_Create(xWindow);                                                // Create a timer on this window
	CHECK(xTimer!=NULL, lblKO);
	GL_Widget_SetId(xTimer, TIMER_ID);                                                // Timer Identifier TIMER_ID
	GL_Widget_RegisterCallback(xTimer, GL_EVENT_TIMER_OUT, CallBackTimeout);          // Call back when the timer expired

	xLayout = GL_Layout_Create(xWindow);                                              // Create a layout on this window
	CHECK(xLayout!=NULL, lblKO);

	for (usLine=0; usLine<usMaxLine; usLine++)                                        // Build labels on this layout
	{
		xLabel = GL_Label_Create(xLayout);                                            // Create a label on this layout
		CHECK(xLabel!=NULL, lblKO);
		GL_Widget_SetItem(xLabel, 0, usLine);                                         // Label location on this layout
		GL_Widget_SetText(xLabel, NULL);                                              // Clear text on this label
		GL_Widget_SetShrink(xLabel, GL_DIRECTION_WIDTH);                              // Shrink beyond its size (No width scrolling cell if label goes over screen)
		if (IsColorDisplay())                                                         // Color display?
			GL_Widget_SetFontScale(xLabel, txLine[usLine].xColor.xFont.eScale);       // Yes, font scale color
		else
			GL_Widget_SetFontScale(xLabel, txLine[usLine].xBW.xFont.eScale);          // No, font scale B&W
		GL_Widget_SetId(xLabel, LABEL_0_ID+usLine);                                   // Label identifier LABEL0_ID + (0..8)
	}

	xLayout2 = GL_Layout_Create(xLayout);                                             // Create a second layout on this layout
	CHECK(xLayout2!=NULL, lblKO);
	GL_Widget_SetId(xLayout2, LAYOUT2_ID);                                            // Second layout identifier
	GL_Widget_SetItem(xLayout2, 0, usLine);                                           // Second layout location on this layout
	GL_Widget_SetGrow(xLayout2, GL_DIRECTION_WIDTH);                                  // Grow beyond its size (Background width around layout will fill the complete cell)

	xButtonCan = GL_Button_Create(xLayout2);                                          // Create a cancel button on this second layout
	CHECK(xButtonCan!=NULL, lblKO);
	GL_Widget_SetSource(xButtonCan, "skin://images/cancel.wgu");                      // Set the cancel skinned image
	GL_Widget_SetItem(xButtonCan, 0, 0);                                              // Button location on this layout
	GL_Widget_SetExpand(xButtonCan, GL_DIRECTION_WIDTH);                              // Expand button width
	GL_Widget_SetShortcut(xButtonCan, GL_KEY_CANCEL);                                 // Shortcut on this button
	GL_Widget_SetId(xButtonCan, BUTTON_CAN_ID);                                       // Cancel button Identifier
	GL_Widget_SetGrow(xButtonCan, GL_DIRECTION_WIDTH);                                // Grow beyond its size (Background width around cancel button will fill the complete cell)
	GL_Widget_RegisterCallback(xButtonCan, GL_EVENT_STYLUS_CLICK, CallBackCancelKey); // Call back when key pressed

	xButtonDown = GL_Button_Create(xLayout2);                                         // Create a down button on this layout
	CHECK(xButtonDown!=NULL, lblKO);
	GL_Widget_SetSource(xButtonDown, "skin://images/downArrow.wgu");                  // Set the down arrow skinned image
	GL_Widget_SetItem(xButtonDown, 1, 0);                                             // Button location on this layout
	//GL_Widget_SetText(xButtonDown, "Down");                                           // Text on this button
	GL_Widget_SetExpand(xButtonDown, GL_DIRECTION_WIDTH);                             // Expand button width
	GL_Widget_SetForeColor(xButtonDown, GL_COLOR_WHITE);                              // Foreground color
	if (bTouch)
		GL_Widget_SetShortcut(xButtonDown, GL_KEY_DOT);                               // Shortcut on this button
	else
		GL_Widget_SetShortcut(xButtonDown, GL_KEY_DOWN);                              // Shortcut on this button
	GL_Widget_SetId(xButtonDown, BUTTON_DOWN_ID);                                     // Down button Identifier
	GL_Widget_SetGrow(xButtonDown, GL_DIRECTION_WIDTH);                               // Grow beyond its size (Background width around down button will fill the complete cell)
	GL_Widget_RegisterCallback(xButtonDown, GL_EVENT_STYLUS_CLICK, CallBackDownKey);  // Call back when key pressed

	xButtonUp = GL_Button_Create(xLayout2);                                           // Create a up button on this layout
	CHECK(xButtonUp!=NULL, lblKO);
	GL_Widget_SetSource(xButtonUp, "skin://images/upArrow.wgu");                      // Set the up arrow skinned image
	GL_Widget_SetItem(xButtonUp, 2, 0);                                               // Button location on this layout
	//GL_Widget_SetText(xButtonUp, "Up");                                               // Text on this button
	GL_Widget_SetExpand(xButtonUp, GL_DIRECTION_WIDTH);                               // Expand button width
	GL_Widget_SetForeColor(xButtonUp, GL_COLOR_WHITE);                                // Foreground color
	if (bTouch)                                                                       // Touch screen?
		GL_Widget_SetShortcut(xButtonUp, GL_KEY_F);                                   // Yes, Shortcut (Key F) on this button
	else
		GL_Widget_SetShortcut(xButtonUp, GL_KEY_UP);                                  // No, Shortcut (Key Up) on this button
	GL_Widget_SetId(xButtonUp, BUTTON_UP_ID);                                         // Up button Identifier
	GL_Widget_SetGrow(xButtonUp, GL_DIRECTION_WIDTH);                                 // Grow beyond its size (Background width around up button will fill the complete cell)
	GL_Widget_RegisterCallback(xButtonUp, GL_EVENT_STYLUS_CLICK, CallBackUpKey);      // Call back when key pressed

	xButtonVal = GL_Button_Create(xLayout2);                                          // Create a valid button on this second layout
	CHECK(xButtonVal!=NULL, lblKO);
	GL_Widget_SetSource(xButtonVal, "skin://images/validation.wgu");                  // Set the valid skinned image
	GL_Widget_SetItem(xButtonVal, 3, 0);                                              // Button location on this layout
	GL_Widget_SetExpand(xButtonVal, GL_DIRECTION_WIDTH);                              // Expand button width
	GL_Widget_SetShortcut(xButtonVal, GL_KEY_VALID);                                  // Shortcut on this button
	GL_Widget_SetId(xButtonVal, BUTTON_VAL_ID);                                       // Valid button Identifier
	GL_Widget_SetGrow(xButtonVal, GL_DIRECTION_WIDTH);                                // Grow beyond its size (Background width around valid button will fill the complete cell)
	GL_Widget_RegisterCallback(xButtonVal, GL_EVENT_STYLUS_CLICK, CallBackValidKey);  // Call back when key pressed

	if(!bTouch)                                                                       // Touch screen?
		GL_Widget_SetSize(xLayout2, 100, 0, GL_UNIT_PERCENT);                         // No, do not show second layout (keep shortcut access on key pressed)

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                                                // Window creation failed
	if (xWindow)
	{
		GL_Widget_Destroy(xWindow);                                                   // Destroy window and all widgets
		xWindow=NULL;
	}
lblEnd:
	return xWindow;
}

//****************************************************************************
//       int GoalClrScreen(T_GL_HWIDGET xWindow, T_GL_COLOR ulBackColor,
//                         unsigned int uiKeys, bool bRefresh)
// This function clears the screen context, can change the background color
//  and sets the shortcut keys needed (Cancel, Down, Up and Valid).
//  Background color is forced to white for B&W terminal.
// This function has parameters.
//   xWindow (I-) : Window context handle.
//   ulBackColor (I-) : Screen background color.
//   uiKeys (I-) : Shortcut keys (exp: KEY_CANCEL | KEY_VALID)
//                   Cancel Key (KEY_CANCEL)
//                   Down Key (KEY_DOWN)
//                   Up Key (KEY_UP)
//                   Valid Key (KEY_VALID)
//   bRefresh (I-) : Refresh or not the screen.
// This function has return value.
//   >=0 : Clear screen done.
//   <0 : Clear screen failed.
//****************************************************************************

int GoalClrScreen(T_GL_HWIDGET xWindow, T_GL_COLOR ulBackColor, unsigned int uiKeys, bool bRefresh)
{
	// Local variables
    // ***************
	ushort usIdx;
	T_GL_HWIDGET xLabel, xLayout2, xButtonVal, xButtonCan, xButtonDown, xButtonUp;
	int iRet;

	// Disable the complete second layout
	// **********************************
	xLayout2 = GL_Widget_SearchId(xWindow, LAYOUT2_ID);           // Retrieve the second layout
	CHECK(xLayout2!=NULL, lblKO);
	xButtonCan = GL_Widget_SearchId(xWindow, BUTTON_CAN_ID);      // Retrieve the cancel button on this second layout
	CHECK(xButtonCan!=NULL, lblKO);
	xButtonDown = GL_Widget_SearchId(xWindow, BUTTON_DOWN_ID);    // Retrieve the down button on this second layout
	CHECK(xButtonDown!=NULL, lblKO);
	xButtonUp = GL_Widget_SearchId(xWindow, BUTTON_UP_ID);        // Retrieve the up button on this second layout
	CHECK(xButtonUp!=NULL, lblKO);
	xButtonVal = GL_Widget_SearchId(xWindow, BUTTON_VAL_ID);      // Retrieve the valid button on this second layout
	CHECK(xButtonVal!=NULL, lblKO);

	GL_Widget_SetVisible(xLayout2, false);                        // Blind all widgets on this second layout
	GL_Widget_SetVisible(xButtonCan, false);                      // Blind the cancel button
	GL_Widget_SetFocusable(xButtonCan, false);                    // No focus on cancel button
	GL_Widget_UnregisterCallback(xButtonCan, GL_EVENT_STYLUS_CLICK, CallBackCancelKey); // Unregister call back on cancel button
	GL_Widget_SetVisible(xButtonDown, false);                     // Blind the down button
	GL_Widget_SetFocusable(xButtonDown, false);                   // No focus on down button
	GL_Widget_UnregisterCallback(xButtonDown, GL_EVENT_STYLUS_CLICK, CallBackDownKey); // Unregister call back on down button
	GL_Widget_SetVisible(xButtonUp, false);                       // Blind the up button
	GL_Widget_SetFocusable(xButtonUp, false);                     // No focus on up button
	GL_Widget_UnregisterCallback(xButtonUp, GL_EVENT_STYLUS_CLICK, CallBackUpKey); // Unregister call back on up button
	GL_Widget_SetVisible(xButtonVal, false);                      // Blind the valid button
	GL_Widget_SetFocusable(xButtonVal, false);                    // No focus on valid button
	GL_Widget_UnregisterCallback(xButtonVal, GL_EVENT_STYLUS_CLICK, CallBackValidKey); // Unregister call back on valid button

	// Set the second layout with the right properties
	// ***********************************************
	if (uiKeys != 0)                                              // Shortcut keys?
		GL_Widget_SetVisible(xLayout2, true);                     // Yes, enable the second layout

	if ((uiKeys & KEY_CANCEL) == KEY_CANCEL)                      // Cancel key?
	{
		GL_Widget_SetVisible(xButtonCan, true);                   // Yes, show the cancel key on this second layout
		GL_Widget_RegisterCallback(xButtonCan, GL_EVENT_STYLUS_CLICK, CallBackCancelKey); // Register call back when cancel key pressed or touched
	}

	if ((uiKeys & KEY_DOWN) == KEY_DOWN)                          // Down key?
	{
		GL_Widget_SetVisible(xButtonDown, true);                  // Yes, show the down key on this second layout
		GL_Widget_RegisterCallback(xButtonDown, GL_EVENT_STYLUS_CLICK, CallBackDownKey); // Register call back when down key pressed or touched
	}

	if ((uiKeys & KEY_UP) == KEY_UP)                              // Up key?
	{
		GL_Widget_SetVisible(xButtonUp, true);                    // Yes, show the up key on this second layout
		GL_Widget_RegisterCallback(xButtonUp, GL_EVENT_STYLUS_CLICK, CallBackUpKey); // Register call back when up key pressed or touched
	}

	if ((uiKeys & KEY_VALID) == KEY_VALID)                        // Valid key?
	{
		GL_Widget_SetVisible(xButtonVal, true);                   // Yes, show the valid key on this second layout
		GL_Widget_RegisterCallback(xButtonVal, GL_EVENT_STYLUS_CLICK, CallBackValidKey); // Register call back when key pressed or touched
	}

	if (IsColorDisplay())                                         // Color display?
		GL_Widget_SetBackColor(xWindow, ulBackColor);             // Yes, set window back color
	else
	{
		ulBackColor = GL_COLOR_WHITE;                             // No, force window back color to white
		GL_Widget_SetBackColor(xWindow, ulBackColor);
	}

	// Clear screen
	// ************
	usIdx=0;
	while(1)
	{
		xLabel = GL_Widget_SearchId(xWindow, LABEL_0_ID+usIdx++); // Get label from its id
		if(xLabel == NULL)
			break;

		GL_Widget_SetText(xLabel, NULL);                          // Remove label text
		GL_Widget_SetBorders(xLabel, 0, 0, 0, 0, GL_UNIT_PIXEL, ulBackColor); // Remove border with window back color
		GL_Widget_SetBackColor(xLabel, ulBackColor);              // Paint label back color with window back color
	}

	if (bRefresh)                                                 // Refresh window?
		GL_Window_Dispatch(xWindow, 0);                           // Yes, refresh it

	iRet=1;
	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                            // Clear screen failed
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//                void GoalRefreshScreen (T_GL_HWIDGET xWindow)
// This function refreshes the screen context.
// This function has parameters.
//   xWindow (I-) : Window context handle.
// This function has return value.
//****************************************************************************

void GoalRefreshScreen(T_GL_HWIDGET xWindow)
{
	// Local variables
    // ***************
		// Empty

	// Refresh screen
	// **************
	GL_Window_Dispatch(xWindow, 0);  // Refresh the window and dispatch all messages received
}

//****************************************************************************
//    int GoalDspLine(T_GL_HWIDGET xWindow, ushort usLine, char *pcText,
//                    const ST_DSP_LINE* pxLine, ulong ulTimeOut, bool bRefresh)
// This function displays a string on screen for B&W terminal or color terminal.
//  The line has the following properties:
//   - Text Align, Background Align, Pen/Brush Color, Reverse mode,
//   - Background size (width), Background grow size (width),
//   - Text padding, Border, Margin, Font
//  A Time-out to exit from the screen.
//  Refresh or not the screen.
// This function has parameters.
//   xWindow (I-) : Window context handle.
//   usLine (I-) : Line number.
//   pcText (I-) : Text to display.
//   pxLine (I-) : Line properties.
//   ulTimeOut (I-) : Timeout in milliseconds.
//   bRefresh (I-) : Refresh or not the screen.
// This function has return value.
//   >=0 : Display line done (Exit screen: 0=timeout,GL_KEY_CANCEL,GL_KEY_VALID).
//   <0 : Display line failed.
//****************************************************************************

int GoalDspLine(T_GL_HWIDGET xWindow, ushort usLine, char *pcText, const ST_DSP_LINE* pxLine, ulong ulTimeOut, bool bRefresh)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xLabel, xTimer;
	int iRet=0; // iRet must be initialized to 0

	// Display line
	// ************
	xLabel = GL_Widget_SearchId(xWindow, LABEL_0_ID+usLine); // Get label from its id
	CHECK(xLabel!=NULL, lblKO);

	GL_Widget_SetVisible(xLabel, false);                     // Blind text if null
	CHECK(pcText!=NULL, lblEnd);

	GL_Widget_SetVisible(xLabel, true);
	GL_Widget_SetText(xLabel, "%s", pcText);                 // Show text (Add %s to allow '%' to be displayed)

	if (IsColorDisplay())                                    // Color display?
	{
		// Color properties
		// ================
		if (pxLine)                                          // Yes
		{
			GL_Widget_SetTextAlign(xLabel, pxLine->xColor.eTextAlign);      // Text alignment
			GL_Widget_SetBackAlign(xLabel, pxLine->xColor.eBackAlign);      // Background alignment
			GL_Widget_SetForeColor(xLabel, pxLine->xColor.ulPen);           // Pen color
			GL_Widget_SetBackColor(xLabel, pxLine->xColor.ulBrush);         // Brush color
			if (pxLine->xColor.usSizeWidth < 99)                            // Background width size
				GL_Widget_SetMinSize(xLabel, pxLine->xColor.usSizeWidth, 0, GL_UNIT_PERCENT); // The size
			else
				GL_Widget_SetExpand(xLabel, GL_DIRECTION_WIDTH);                              // Full size
			if (pxLine->xColor.bGrowWidth)                                  // Grow beyond its size
				GL_Widget_SetGrow(xLabel, GL_DIRECTION_WIDTH);              // Background width around the label will fill the complete cell
			                                                                // Paddings, Borders and Margins
			GL_Widget_SetTextPaddings(xLabel, pxLine->xColor.xPadding.usLeft, pxLine->xColor.xPadding.usTop, pxLine->xColor.xPadding.usRight, pxLine->xColor.xPadding.usBottom, GL_UNIT_PERCENT);
			GL_Widget_SetBorders(xLabel, pxLine->xColor.xBorder.usLeft, pxLine->xColor.xBorder.usTop, pxLine->xColor.xBorder.usRight, pxLine->xColor.xBorder.usBottom, GL_UNIT_PIXEL, pxLine->xColor.xBorder.ulColor);
			GL_Widget_SetMargins(xLabel, pxLine->xColor.xMargin.usLeft, pxLine->xColor.xMargin.usTop, pxLine->xColor.xMargin.usRight, pxLine->xColor.xMargin.usBottom, GL_UNIT_PIXEL);
			if (pxLine->xColor.xFont.pcName != NULL)
				GL_Widget_SetFontName(xLabel, pxLine->xColor.xFont.pcName); // Font name
			GL_Widget_SetFontScale(xLabel, pxLine->xColor.xFont.eScale);    // Font scale
			GL_Widget_SetFontStyle(xLabel, pxLine->xColor.xFont.eStyle);    // Font style
		}
	}
	else                                                     // No
	{
		// Black & White properties
		// ========================
		if (pxLine)
		{
			GL_Widget_SetTextAlign(xLabel, pxLine->xBW.eTextAlign); // Text alignment
			GL_Widget_SetBackAlign(xLabel, pxLine->xBW.eBackAlign); // Background alignment
			if (!pxLine->xBW.bReverse)                              // B&W reverse?
			{                                                       // Yes
				GL_Widget_SetForeColor(xLabel, GL_COLOR_BLACK);     // Force pen color to black and brush color to white
				GL_Widget_SetBackColor(xLabel, GL_COLOR_WHITE);
			}
			else                                                    // No
			{
				GL_Widget_SetForeColor(xLabel, GL_COLOR_WHITE);     // Force pen color to white and brush color to black
				GL_Widget_SetBackColor(xLabel, GL_COLOR_BLACK);
			}
			if (pxLine->xBW.usSizeWidth < 99)                       // Background width size
				GL_Widget_SetMinSize(xLabel, pxLine->xBW.usSizeWidth, 0, GL_UNIT_PERCENT); // The size
			else
				GL_Widget_SetExpand(xLabel, GL_DIRECTION_WIDTH);                           // Full size
			if (pxLine->xBW.bGrowWidth)                             // Grow beyond its size
				GL_Widget_SetGrow(xLabel, GL_DIRECTION_WIDTH);      // Background width around the label will fill the complete cell
			                                                        // Paddings, Borders and Margins
			GL_Widget_SetTextPaddings(xLabel, pxLine->xBW.xPadding.usLeft, pxLine->xBW.xPadding.usTop, pxLine->xBW.xPadding.usRight, pxLine->xBW.xPadding.usBottom, GL_UNIT_PERCENT);
			if ((pxLine->xBW.xBorder.ulColor & 0x00FFFFFF) != 0x00FFFFFF) // Force border to black or white
				GL_Widget_SetBorders(xLabel, pxLine->xBW.xBorder.usLeft, pxLine->xBW.xBorder.usTop, pxLine->xBW.xBorder.usRight, pxLine->xBW.xBorder.usBottom, GL_UNIT_PIXEL, pxLine->xBW.xBorder.ulColor & 0xFF000000);
			else
				GL_Widget_SetBorders(xLabel, pxLine->xBW.xBorder.usLeft, pxLine->xBW.xBorder.usTop, pxLine->xBW.xBorder.usRight, pxLine->xBW.xBorder.usBottom, GL_UNIT_PIXEL, pxLine->xBW.xBorder.ulColor | 0x00FFFFFF);
			GL_Widget_SetMargins(xLabel, pxLine->xBW.xMargin.usLeft, pxLine->xBW.xMargin.usTop, pxLine->xBW.xMargin.usRight, pxLine->xBW.xMargin.usBottom, GL_UNIT_PIXEL);
			if (pxLine->xBW.xFont.pcName != NULL)
				GL_Widget_SetFontName(xLabel, pxLine->xBW.xFont.pcName); // Font name
			GL_Widget_SetFontScale(xLabel, pxLine->xBW.xFont.eScale);    // Font scale
			GL_Widget_SetFontStyle(xLabel, pxLine->xBW.xFont.eStyle);    // Font style
		}
	}

	CHECK(bRefresh, lblEnd);                           // Refresh window? No, skip timer and keyboard

	// Restart timer
	// *************
	xTimer = GL_Widget_SearchId(xWindow, TIMER_ID);    // Get timer from its id
	CHECK(xTimer!=NULL, lblKO);
	GL_Timer_SetInterval(xTimer, ulTimeOut);           // Set timeout value

	// Loop indefinitely until the result is set from the call back functions
	// **********************************************************************
	GL_Window_MainLoop(xWindow);                       // Wait until a result is set

	// Test the result set by the call back functions
	// **********************************************
	switch(GL_Window_GetResult(xWindow))               // Get the result
	{
	case RES_VALID_STATUS:                             // Key valid result
		GL_Timer_Stop(xTimer);
		iRet=GL_KEY_VALID;
		break;
	case RES_CANCEL_STATUS:                            // Key cancel result
		GL_Timer_Stop(xTimer);
		iRet=GL_KEY_CANCEL;
		break;
	case RES_TIMER_STATUS:                             // Timer result
		iRet=0;
		break;
	default:                                           // Unknown result
		iRet=-1;
		break;
	}

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                 // Display line failed
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//    int GoalDspMultiLine(T_GL_HWIDGET xWindow, ushort usLine, char *pcData,
//                         int iLen, const ST_LINE txLine[], ulong ulTimeOut,
//                         bool bRefresh)
//  This function sends a data buffer to the display.
//   The buffer is divided on lines of 100 bytes max except the last line.
//   Each line is automatically displayed on screen. The '\n' automatically
//   switches to the next line.
//   The function can display up to max line defined on screen creation.
//  This function has parameters:
//    xWindow (I-) : Window context handle.
//    usLine (I-) : Line number.
//    pcData (I-) : Data to display.
//    iLen (I-) : Length of data.
//    ulTimeOut (I-) : Timeout in milliseconds.
//    bRefresh (I-) : Refresh or not the screen.
//  This function has return value.
//    >=0 : Display buffer done (Exit screen : 0=timeout,GL_KEY_CANCEL,GL_KEY_VALID).
//    <0 : Display buffer failed.
//****************************************************************************

int GoalDspMultiLine(T_GL_HWIDGET xWindow, ushort usLine, char *pcData , int iLen, const ST_DSP_LINE txLine[], ushort usMaxLine, ulong ulTimeOut, bool bRefresh)
{
	// Local variables
    // ***************
	ST_DSP_LINE xLine;
	int iCount=0;
	char tcBuffer[100+1];
	int iRet=-1, iLength;

	// Printing in progress
	// ********************
	CHECK ((pcData!=NULL) && (iLen!=0), lblKO)
	iLength = iLen;

	memset(tcBuffer, 0, sizeof(tcBuffer));
	while(usLine < usMaxLine)
	{
		if (iLen > 0)               // Check if it is the end of data
		{                           // No, it's a line with '\n' detected
			if (*pcData != '\n')    // Save character into buffer
			{
				if (iCount < 100)
				{
					tcBuffer[iCount++] = *pcData++;
					tcBuffer[iCount]=0;
				}
				iLen--;
			}
			else                    // '\n' detected
			{
				xLine = txLine[usLine];
				if (usLine == usMaxLine-1)
				{                   // Last line to display
					iRet = GoalDspLine(xWindow, usLine++, tcBuffer, &xLine, ulTimeOut, bRefresh);
					CHECK(iRet>=0, lblKO);
				}
				else
				{                   // Next line to display
					iRet = GoalDspLine(xWindow, usLine++, tcBuffer, &xLine, 0, false);
					CHECK(iRet>=0, lblKO);
				}
				iCount=0;
				tcBuffer[iCount]=0;
				pcData++;
				iLen--;
			}
		}
		else
		{                           // Yes, it's the end of data
			xLine = txLine[usLine]; // Display line
			iRet = GoalDspLine(xWindow, usLine++, tcBuffer, &xLine, ulTimeOut, bRefresh);
			CHECK(iRet>=0, lblKO);
			break;                  // Exit from the loop
		}
	}

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                              // Display buffer failed.
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//     int GoalGetKey(T_GL_HWIDGET xWindow, T_GL_HGRAPHIC_LIB xGraphicLib,
//                    ulong ulTimeOut, bool bClear)
// This function waits for shortcut key pressed or touched.
// This function has parameters.
//   xWindow (I-) : Window context handle.
//   xGraphicalLib (I-) : Graphic library context handle.
//   bShortcut (I-) : true => Return only shortcut keys pressed
//                    false => Return all keys pressed
//   ulTimeOut (I-) : Timeout in milliseconds.
//   bClear (I-) : true => FIFO touch and keyboard reseted before waiting
//                         into GL_Window_MainLoop.
// This function has return value.
//   >0 : Key value.
//   =0 : Timeout.
//****************************************************************************

int GoalGetKey(T_GL_HWIDGET xWindow, T_GL_HGRAPHIC_LIB xGraphicLib, bool bShortcut, ulong ulTimeOut, bool bClear)
{
	// Local variables
    // ***************
	FILE *pxKbd=NULL;  // Peripheral file Keyboard
	FILE *pxTsc=NULL;  // Peripheral file Touch
	bool bTouch;
	int iRet;

	T_GL_WCHAR ulKey;

	// Loop indefinitely until the result is set from the call back functions
	// **********************************************************************
	bTouch = GL_GraphicLib_IsTouchPresent(xGraphicLib);       // Touch screen?
	if (bTouch)
	{                                                         // Yes,
		GL_GraphicLib_UnbindKey(xGraphicLib, GL_KEY_F);       // Bind "F" key to Telium Key
		GL_GraphicLib_UnbindKey(xGraphicLib, GL_KEY_DOT);     // Bind "Dot" key to Telium Key
	}
	else
	{                                                         // No,
		GL_GraphicLib_UnbindKey(xGraphicLib, GL_KEY_UP);      // Bind "Up" key to Telium Key
		GL_GraphicLib_UnbindKey(xGraphicLib, GL_KEY_DOWN);    // Bind "Down" key to Telium Key
		GL_GraphicLib_UnbindKey(xGraphicLib, GL_KEY_F1);      // Bind "F1" key to Telium Key
		GL_GraphicLib_UnbindKey(xGraphicLib, GL_KEY_F4);      // Bind "F4" key to Telium Key
	}

	// Restart timer
	// *************
	if (ulTimeOut == GL_TIME_INFINITE)                        // Set timeout value
		GL_Timer_SetInterval(GL_Widget_SearchId(xWindow, TIMER_ID), 0x7FFFFFFF);             // Bug 0xFFFFFFFF not supported
	else
		GL_Timer_SetInterval(GL_Widget_SearchId(xWindow, TIMER_ID), ulTimeOut);

	// Detect key pressed
	// ******************
	if (!bShortcut)                                           // All keys pressed
	{
		GL_Widget_RegisterCallback(xWindow, GL_EVENT_KEY_DOWN, CallBackPressKey);       // Call back when key pressed
		GL_Widget_SetShortcut(GL_Widget_SearchId(xWindow, BUTTON_CAN_ID), GL_KEY_NONE); // Remove shortcut from cancel button
		GL_Widget_SetShortcut(GL_Widget_SearchId(xWindow, BUTTON_VAL_ID), GL_KEY_NONE); // Remove shortcut from valid button
	}

	// Reset FIFO keyboard and touch
	// *****************************
	if (bClear)
	{
		pxKbd = stdperif("KEYBOARD", NULL);                   // Check "keyboard" peripheral opened?
		if(pxKbd)
			reset_buf(pxKbd, _receive_id);                    // Yes, reset "keyboard" FIFO

		pxTsc = stdperif("TSCREEN", NULL);                    // Check "touch" peripheral opened?
		if(pxTsc)
			reset_buf(pxTsc, _receive_id);                    // Yes, reset "touch" FIFO
	}

	GL_Window_MainLoop(xWindow);                              // Wait until a result is set

	// Test the result set by the call back functions
	// **********************************************
	switch(GL_Window_GetResult(xWindow))                      // Get the result
	{
	case RES_PRESS_STATUS:                                    // Key press result
		GL_Timer_Stop(GL_Widget_SearchId(xWindow, TIMER_ID));
		GL_Widget_GetUserData(xWindow, &ulKey, sizeof(ulKey));
		iRet=ulKey;
		break;
	case RES_VALID_STATUS:                                    // Key valid result
		GL_Timer_Stop(GL_Widget_SearchId(xWindow, TIMER_ID));
		iRet=GL_KEY_VALID;
		break;
	case RES_CANCEL_STATUS:                                   // Key cancel result
		GL_Timer_Stop(GL_Widget_SearchId(xWindow, TIMER_ID));
		iRet=GL_KEY_CANCEL;
		break;
	case RES_DOWN_STATUS:                                     // Key down result
		GL_Timer_Stop(GL_Widget_SearchId(xWindow, TIMER_ID));
		iRet=GL_KEY_DOWN;
		break;
	case RES_UP_STATUS:                                       // Key up result
		GL_Timer_Stop(GL_Widget_SearchId(xWindow, TIMER_ID));
		iRet=GL_KEY_UP;
		break;
	case RES_TIMER_STATUS:                                    // Timer result
		iRet=0;
		break;
	default:                                                  // Unknown result
		iRet=0;
		break;
	}

	if (!bShortcut)                                                                       // All keys pressed
	{
		GL_Widget_UnregisterCallback(xWindow, GL_EVENT_KEY_DOWN, CallBackPressKey);       // Unregister call back on key pressed
		GL_Widget_SetShortcut(GL_Widget_SearchId(xWindow, BUTTON_CAN_ID), GL_KEY_CANCEL); // Set shortcut on cancel button
		GL_Widget_SetShortcut(GL_Widget_SearchId(xWindow, BUTTON_VAL_ID), GL_KEY_VALID);  // Set shortcut on valid button
	}

	if (bTouch)                                               // Touch screen?
	{                                                                                 // Yes
		GL_GraphicLib_BindSingleKey(xGraphicLib, GL_KEY_F, GL_VIRTUAL_KEY_PREVIOUS);  // Bind "F" key to virtual Key
		GL_GraphicLib_BindSingleKey(xGraphicLib, GL_KEY_DOT, GL_VIRTUAL_KEY_NEXT);    // Bind "Dot" key to virtual Key
	}
	else
	{                                                                                 // No
		GL_GraphicLib_BindSingleKey(xGraphicLib, GL_KEY_UP, GL_VIRTUAL_KEY_PREVIOUS); // Bind "Up" key to virtual Key
		GL_GraphicLib_BindSingleKey(xGraphicLib, GL_KEY_DOWN, GL_VIRTUAL_KEY_NEXT);   // Bind "Down" key to virtual Key
		GL_GraphicLib_BindSingleKey(xGraphicLib, GL_KEY_F1, GL_VIRTUAL_KEY_LEFT);     // Bind "F1" key to virtual Key
		GL_GraphicLib_BindSingleKey(xGraphicLib, GL_KEY_F4, GL_VIRTUAL_KEY_RIGHT);    // Bind "F4" key to virtual Key
	}

	return iRet;
}

//****************************************************************************
//            void GoalDestroyScreen(T_GL_HWIDGET *pxWindow)
// This function destroys the screen context by releasing all allocated memory
//  and all widgets attached.
//  This call is crucial, if it is forgotten you get a memory leak.
// This function has parameters.
//   pxWindow (I-) : Pointer on window context handle.
// This function has no return value.
//****************************************************************************

void GoalDestroyScreen(T_GL_HWIDGET *pxWindow)
{
	// Local variables
    // ***************
		// Empty

	// Destroy screen
	// **************
	GL_Widget_Destroy(*pxWindow); // Destroy window with all widgets attached
	*pxWindow=NULL;
}

//##############################################################################
//                                   DRAWING
//##############################################################################

//****************************************************************************
//      T_GL_HWIDGET GoalCreateDrawing (T_GL_HGRAPHIC_LIB xGraphicLib,
//                                      T_GL_ENCODING_CHARSET eCHarSet)
// This function creates a drawing context which is composed of:
//  - A timer to exit from this screen.
//  - A drawing window.
//  - Shortcut keys on 2 buttons to react on this screen:
//      Cancel Key and Valid Key
//  !!! All other keys detection will be done with standard Telium functions.
//  - Encoding charsets:
//      GL_ENCODING_UTF8 => Unicode utf8
//      GL_ENCODING_ISO_8859_X => ISO 8859
// This function has parameters.
//   xGraphicalLib (I-) : Graphic library context handle.
//   eCharSet (I-) : Encoding charsets.
// This function has return value.
//   !NULL : Pointer to the handle of the drawing.
//   NULL : Drawing failed
//****************************************************************************

T_GL_HWIDGET GoalCreateDrawing (T_GL_HGRAPHIC_LIB xGraphicLib, T_GL_ENCODING_CHARSET eCharSet)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xWindow, xTimer, xLayout, xDrawing, xLayout2, xButtonVal, xButtonCan;
	bool bTouch=FALSE;

	// Build drawing context with 2 buttons (Cancel and Valid)
	// *******************************************************
	xWindow = GL_Window_Create(xGraphicLib);                          // Create a window in a user area
	CHECK(xWindow!=NULL, lblEnd);

    GL_GraphicLib_SetCharset(xGraphicLib, eCharSet);                  // Change the encoding charset of the graphic library

	bTouch = GL_GraphicLib_IsTouchPresent(xGraphicLib);               // Touch screen?

	xTimer = GL_Timer_Create(xWindow);                                // Create a timer on this window
	CHECK(xTimer!=NULL, lblKO);
	GL_Widget_SetId(xTimer, TIMER_ID);                                // Timer Identifier TIMER_ID
	GL_Widget_RegisterCallback(xTimer, GL_EVENT_TIMER_OUT, CallBackTimeout); // Call back when the timer expired

	xLayout = GL_Layout_Create(xWindow);                              // Create a layout on this window
	CHECK(xLayout!=NULL, lblKO);

	xDrawing = GL_Drawing_Create(xLayout);                            // Create a drawing on this layout
	CHECK(xDrawing!=NULL, lblKO);
	GL_Widget_SetId(xDrawing, DRAWING_ID);                            // Drawing Identifier DRAWING_ID
	GL_Widget_SetItem(xDrawing, 0, 0);                                // Drawing location on this layout

	xLayout2 = GL_Layout_Create(xLayout);                             // Create a second layout on this layout
	CHECK(xLayout2!=NULL, lblKO);
	GL_Widget_SetId(xLayout2, LAYOUT2_ID);                            // Second layout identifier
	GL_Widget_SetItem(xLayout2, 0, 1);                                // Second layout location on this layout
	GL_Widget_SetGrow(xLayout2, GL_DIRECTION_WIDTH);                  // Grow beyond its size (Background width around layout will fill the complete cell)

	xButtonCan = GL_Button_Create(xLayout2);                          // Create a cancel button on this second layout
	CHECK(xButtonCan!=NULL, lblKO);
	GL_Widget_SetSource(xButtonCan, "skin://images/cancel.wgu");      // Set the cancel skinned image
	GL_Widget_SetItem(xButtonCan, 0, 0);                              // Button location on this layout
	GL_Widget_SetExpand(xButtonCan, GL_DIRECTION_WIDTH);              // Expand button width
	GL_Widget_SetShortcut(xButtonCan, GL_KEY_CANCEL);                 // Shortcut on this button
	GL_Widget_SetId(xButtonCan, BUTTON_CAN_ID);                       // Cancel button Identifier
	GL_Widget_SetGrow(xButtonCan, GL_DIRECTION_WIDTH);                // Grow beyond its size (Background width around cancel button will fill the complete cell)
	GL_Widget_RegisterCallback(xButtonCan, GL_EVENT_STYLUS_CLICK, CallBackCancelKey); // Call back when key pressed

	xButtonVal = GL_Button_Create(xLayout2);                          // Create a valid button on this second layout
	CHECK(xButtonVal!=NULL, lblKO);
	GL_Widget_SetSource(xButtonVal, "skin://images/validation.wgu");  // Set the valid skinned image
	GL_Widget_SetItem(xButtonVal, 1, 0);                              // Button location on this layout
	GL_Widget_SetExpand(xButtonVal, GL_DIRECTION_WIDTH);              // Expand button width
	GL_Widget_SetShortcut(xButtonVal, GL_KEY_VALID);                  // Shortcut on this button
	GL_Widget_SetId(xButtonVal, BUTTON_VAL_ID);                       // Valid button Identifier
	GL_Widget_SetGrow(xButtonVal, GL_DIRECTION_WIDTH);                // Grow beyond its size (Background width around valid button will fill the complete cell)
	GL_Widget_RegisterCallback(xButtonVal, GL_EVENT_STYLUS_CLICK, CallBackValidKey); // Call back when key pressed

	if(!bTouch)                                                       // Touch screen?
		GL_Widget_SetSize(xLayout2, 100, 0, GL_UNIT_PERCENT);         // No, do not show second layout (keep shortcut on key pressed)

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                                // Window creation failed
	if (xWindow)
	{
		GL_Widget_Destroy(xWindow);                                   // Destroy window and all widgets
		xWindow=NULL;
	}
lblEnd:
	return xWindow;
}

//****************************************************************************
//        int GoalClrDrawing(T_GL_HWIDGET xWindow, T_GL_COLOR ulBackColor,
//                           unsigned int uiKeys, bool bRefresh)
// This function clears the drawing context, can change the background color
//  and sets the shortcut keys needed (Cancel and Valid).
//  Background color is forced to white for B&W terminal.
// This function has parameters.
//   xWindow (I-) : Window context handle.
//   ulBackColor (I-) : Drawing background color.
//   uiKeys (I-) : Shortcut keys (exp: KEY_CANCEL | KEY_VALID)
//                   Cancel Key (KEY_CANCEL)
//                   Valid Key (KEY_VALID)
//   bRefresh (I-) : Refresh or not the screen.
// This function has return value.
//   >=0 : Clear drawing done.
//   <0 : Clear drawing failed.
//****************************************************************************

int GoalClrDrawing(T_GL_HWIDGET xWindow, T_GL_COLOR ulBackColor, unsigned int uiKeys, bool bRefresh)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xDrawing, xLayout2, xButtonVal, xButtonCan;
	int iRet;

	// Disable the complete second layout
	// **********************************
	xLayout2 = GL_Widget_SearchId(xWindow, LAYOUT2_ID);          // Retrieve the second layout
	CHECK(xLayout2!=NULL, lblKO);
	xButtonCan = GL_Widget_SearchId(xWindow, BUTTON_CAN_ID);     // Retrieve the cancel button on this second layout
	CHECK(xButtonCan!=NULL, lblKO);
	xButtonVal = GL_Widget_SearchId(xWindow, BUTTON_VAL_ID);     // Retrieve the valid button on this second layout
	CHECK(xButtonVal!=NULL, lblKO);

	GL_Widget_SetVisible(xLayout2, false);                       // Blind all widgets on this second layout
	GL_Widget_SetVisible(xButtonCan, false);                     // Blind the cancel button
	GL_Widget_SetFocusable(xButtonCan, false);                   // No focus on cancel button
	GL_Widget_UnregisterCallback(xButtonCan, GL_EVENT_STYLUS_CLICK, CallBackCancelKey); // Unregister call back on cancel button
	GL_Widget_SetVisible(xButtonVal, false);                     // Blind the valid button
	GL_Widget_SetFocusable(xButtonVal, false);                   // No focus on valid button
	GL_Widget_UnregisterCallback(xButtonVal, GL_EVENT_STYLUS_CLICK, CallBackValidKey); // Unregister call back on valid button

	// Set the second layout with the right properties
	// ***********************************************
	if (uiKeys != 0)                                             // Shortcut keys?
		GL_Widget_SetVisible(xLayout2, true);                    // Yes, enable the second layout

	if ((uiKeys & KEY_CANCEL) == KEY_CANCEL)                     // Cancel key?
	{
		GL_Widget_SetVisible(xButtonCan, true);                  // Yes, show the cancel key on this second layout
		GL_Widget_RegisterCallback(xButtonCan, GL_EVENT_STYLUS_CLICK, CallBackCancelKey); // Register call back when cancel key pressed or touched
	}

	if ((uiKeys & KEY_VALID) == KEY_VALID)                       // Valid key?
	{
		GL_Widget_SetVisible(xButtonVal, true);                  // Yes, show the valid key on this second layout
		GL_Widget_RegisterCallback(xButtonVal, GL_EVENT_STYLUS_CLICK, CallBackValidKey); // Register call back when valid key pressed or touched
	}

	if (IsColorDisplay())                                        // Color display?
		GL_Widget_SetBackColor(xWindow, ulBackColor);            // Yes, set window back color
	else
	{
		ulBackColor = GL_COLOR_WHITE;                            // No, force window back color to white
		GL_Widget_SetBackColor(xWindow, ulBackColor);
	}

	// Clear drawing
	// *************
	xDrawing = GL_Widget_SearchId(xWindow, DRAWING_ID);          // Get drawing from its id
	CHECK(xDrawing!=NULL, lblKO);
	GL_Drawing_Clear(xDrawing);                                  // Clear drawing

	if (bRefresh)                                                // Refresh window?
		GL_Window_Dispatch(xWindow, 0);                          // Yes, refresh it

	iRet=1;
	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                           // Clear drawing failed
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//    int GoalDrawLine(T_GL_HWIDGET xWindow, T_GL_COLOR ulPen,
//                     T_GL_COORD sX1, T_GL_COORD sY1,
//                     T_GL_COORD sX2, T_GL_COORD sY2,
//                     ulong ulTimeOut, bool bRefresh)
// This function draws a line on screen for B&W terminal or color terminal.
//  The drawing line has the following properties:
//   - Pen color, Coordinates (X1,Y1,X2,Y2)
//  A Time-out to exit from the screen.
//  Refresh or not the screen.
//  Pen color is forced to black for B&W terminal.
// This function has parameters.
//   xWindow (I-) : Window context handle.
//   ulPen (I-) : Pen color.
//   sX1 (I-), sY1(I-) : Coordinates of the first point.
//   sX2 (I-), sY2 (I-) : Coordinates of the second point.
//   ulTimeOut (I-) : Timeout in milliseconds.
//   bRefresh (I-) : Refresh or not the screen.
// This function has return value.
//   >=0 : Drawing line done (Exit screen : 0=timeout,GL_KEY_CANCEL,GL_KEY_VALID).
//   <0 : Drawing line failed.
//****************************************************************************

int GoalDrawLine(T_GL_HWIDGET xWindow, T_GL_COLOR ulPen, T_GL_COORD sX1, T_GL_COORD sY1, T_GL_COORD sX2, T_GL_COORD sY2, ulong ulTimeOut, bool bRefresh)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xTimer, xDrawing;
	int iRet=0;  // iRet must be initialized to 0

	// Drawing line
	// ************
	xDrawing = GL_Widget_SearchId(xWindow, DRAWING_ID);    // Get drawing from its id
	CHECK(xDrawing!=NULL, lblKO);
	GL_Drawing_SetPen(xDrawing, ulPen, 1, GL_UNIT_PIXEL);  // Set pen color and stroke (only 1 pixel supported)
	GL_Drawing_DrawLine(xDrawing, sX1, sY1, sX2, sY2, GL_UNIT_PERCENT); // Draw line with pen

	CHECK(bRefresh, lblEnd);                               // Refresh window? No, skip timer and keyboard

	// Restart timer
	// *************
	xTimer = GL_Widget_SearchId(xWindow, TIMER_ID);        // Get timer from its id
	CHECK(xTimer!=NULL, lblKO);
	GL_Timer_SetInterval(xTimer, ulTimeOut);               // Set timeout value

	// Loop indefinitely until the result is set from the call back functions
	// **********************************************************************
	GL_Window_MainLoop(xWindow);                           // Wait until a result is set

	// Test the result set by the call back functions
	// **********************************************
	switch(GL_Window_GetResult(xWindow))                   // Get the result
	{
	case RES_VALID_STATUS:                                 // Key valid result
		GL_Timer_Stop(xTimer);
		iRet=GL_KEY_VALID;
		break;
	case RES_CANCEL_STATUS:                                // Key cancel result
		GL_Timer_Stop(xTimer);
		iRet=GL_KEY_CANCEL;
		break;
	case RES_TIMER_STATUS:                                 // Timer result
		iRet=0;
		break;
	default:                                               // Unknown result
		iRet=-1;
		break;
	}

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                     // Drawing line failed
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//  int GoalDrawRect(T_GL_HWIDGET xWindow, T_GL_COLOR ulPen, T_GL_COLOR ulBrush,
//                   T_GL_COORD sX, T_GL_COORD sY,
//                   T_GL_COORD sWidth, T_GL_COORD sHeight,
//                   ulong ulTimeOut, bool bRefresh)
// This function draws a rectangle on screen for B&W terminal or color terminal.
//  The drawing rectangle has the following properties:
//   - Pen/Brush color, Coordinates (X,Y,Width, Height)
//  A Time-out to exit from the screen.
//  Refresh or not the screen.
//  Pen=black and Brush=white for B&W terminal.
// This function has parameters.
//   xWindow (I-) : Window context handle.
//   ulPen (I-), ulBrush (I-) : Pen and brush color.
//   sX (I-), sY(I-) : Coordinates of the first point (X,Y).
//   sWidth (I-), sHeight (I-) : Coordinates of the second point (Width, Height).
//   ulTimeOut (I-) : Timeout in milliseconds.
//   bRefresh (I-) : Refresh or not the screen.
// This function has return value.
//   >=0 : Drawing rectangle done (Exit screen : 0=timeout,GL_KEY_CANCEL,GL_KEY_VALID).
//   <0 : Drawing rectangle failed.
//****************************************************************************

int GoalDrawRect(T_GL_HWIDGET xWindow, T_GL_COLOR ulPen, T_GL_COLOR ulBrush, T_GL_COORD sX, T_GL_COORD sY, T_GL_COORD sWidth, T_GL_COORD sHeight, ulong ulTimeOut, bool bRefresh)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xTimer, xDrawing;
	int iRet=0; // iRet must be initialized to 0

	// Drawing rectangle
	// *****************
	xDrawing = GL_Widget_SearchId(xWindow, DRAWING_ID);   // Get drawing from its id
	CHECK(xDrawing!=NULL, lblKO);
	GL_Drawing_SetPen(xDrawing, ulPen, 1, GL_UNIT_PIXEL); // Set pen color and stroke (only 1 pixel supported)
	GL_Drawing_SetBrush(xDrawing, ulBrush);               // Set brush color
	GL_Drawing_DrawRect(xDrawing, sX, sY, sWidth, sHeight, GL_UNIT_PERCENT); // Draw rectangle with pen and brush

	CHECK(bRefresh, lblEnd);                              // Refresh window? No, skip timer and keyboard

	// Restart timer
	// *************
	xTimer = GL_Widget_SearchId(xWindow, TIMER_ID);       // Get timer from its id
	CHECK(xTimer!=NULL, lblKO);
	GL_Timer_SetInterval(xTimer, ulTimeOut);              // Set timeout value

	// Loop indefinitely until the result is set from the call back functions
	// **********************************************************************
	GL_Window_MainLoop(xWindow);                          // Wait until a result is set

	// Test the result set by the call back functions
	// **********************************************
	switch(GL_Window_GetResult(xWindow))                  // Get the result
	{
	case RES_VALID_STATUS:                                // Key valid result
		GL_Timer_Stop(xTimer);
		iRet=GL_KEY_VALID;
		break;
	case RES_CANCEL_STATUS:                               // Key cancel result
		GL_Timer_Stop(xTimer);
		iRet=GL_KEY_CANCEL;
		break;
	case RES_TIMER_STATUS:                                // Timer result
		iRet=0;
		break;
	default:                                              // Unknown result
		iRet=-1;
		break;
	}

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                    // Drawing rectangle failed
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//  int GoalDrawEllipse(T_GL_HWIDGET xWindow, T_GL_COLOR ulPen, T_GL_COLOR ulBrush,
//                      T_GL_COORD sX, T_GL_COORD sY,
//                      T_GL_DIM usRadiusX, T_GL_DIM usRadiusY,
//                      ulong ulTimeOut, bool bRefresh)
// This function draws an ellipse on screen for B&W terminal or color terminal.
//  The drawing elipse has the following properties:
//   - Pen/Brush color, Coordinates (X,Y,RadiusX,RadiusY)
//  A Time-out to exit from the screen.
//  Refresh or not the screen.
//  Pen=black and Brush=white for B&W terminal.
// This function has parameters.
//   xWindow (I-) : Window context handle.
//   ulPen (I-), ulBrush (I-) : Pen and brush color.
//   sX (I-), sY(I-) : Coordinates of the first point (X,Y).
//   usRadiusX (I-), usRadiusY (I-) : Coordinates of the second point (RadiusX, RadiusY).
//   ulTimeOut (I-) : Timeout in milliseconds.
//   bRefresh (I-) : Refresh or not the screen.
// This function has return value.
//   >=0 : Drawing ellipse done (Exit screen : 0=timeout,GEL_KEY_CANCEL,GL_KEY_VALID).
//   <0 : Drawing ellipse failed.
//****************************************************************************

int GoalDrawEllipse(T_GL_HWIDGET xWindow, T_GL_COLOR ulPen, T_GL_COLOR ulBrush, T_GL_COORD sX, T_GL_COORD sY, T_GL_DIM usRadiusX, T_GL_DIM usRadiusY, ulong ulTimeOut, bool bRefresh)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xTimer, xDrawing;
	int iRet=0; // iRet must be initialized to 0

	// Drawing ellipse
	// ***************
	xDrawing = GL_Widget_SearchId(xWindow, DRAWING_ID);   // Get drawing from its id
	CHECK(xDrawing!=NULL, lblKO);
	GL_Drawing_SetPen(xDrawing, ulPen, 1, GL_UNIT_PIXEL); // Set pen color and stroke (only 1 pixel supported)
	GL_Drawing_SetBrush(xDrawing, ulBrush);               // Set brush color
	GL_Drawing_DrawEllipse(xDrawing, sX, sY, usRadiusX, usRadiusY, GL_UNIT_PERCENT); // Draw ellipse with pen and brush

	CHECK(bRefresh, lblEnd);                              // Refresh window? No, skip timer and keyboard

	// Restart timer
	// *************
	xTimer = GL_Widget_SearchId(xWindow, TIMER_ID);       // Get timer from its id
	CHECK(xTimer!=NULL, lblKO);
	GL_Timer_SetInterval(xTimer, ulTimeOut);              // Set timeout value

	// Loop indefinitely until the result is set from the call back functions
	// **********************************************************************
	GL_Window_MainLoop(xWindow);                          // Wait until a result is set

	// Test the result set by the call back functions
	// **********************************************
	switch(GL_Window_GetResult(xWindow))                  // Get the result
	{
	case RES_VALID_STATUS:                                // Key valid result
		GL_Timer_Stop(xTimer);
		iRet=GL_KEY_VALID;
		break;
	case RES_CANCEL_STATUS:                               // Key cancel result
		GL_Timer_Stop(xTimer);
		iRet=GL_KEY_CANCEL;
		break;
	case RES_TIMER_STATUS:                                // Timer result
		iRet=0;
		break;
	default:                                              // Unknown result
		iRet=-1;
		break;
	}

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                    // Drawing ellipse failed
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//  int GoalDrawText(T_GL_HWIDGET xWindow, const char* pcText,
//                   const ST_DRAW_FONT* pxFont, T_GL_COLOR ulPen,
//                   T_GL_COORD sX, T_GL_COORD sY,
//                   ulong ulTimeOut, bool bRefresh)
// This function draws text on screen for B&W terminal or color terminal.
//  The drawing text has the following properties:
//   - Pen color, Coordinates (X,Y) and font
//  A Time-out to exit from the screen.
//  Refresh or not the screen.
//  Pen color is forced to black for B&W terminal.
// This function has parameters.
//   xWindow (I-) : Window context handle.
//   pcText (I-) : String to draw.
//   pxFont (I-) : Font properties.
//   ulPen (I-) : Pen color.
//   sX (I-), sY(I-) : Coordinates of the text position.
//   ulTimeOut (I-) : Timeout in milliseconds.
//   bRefresh (I-) : Refresh or not the screen.
// This function has return value.
//   >=0 : Drawing text done (Exit screen : 0=timeout,GL_KEY_CANCEL,GL_KEY_VALID).
//   <0 : Drawing text failed.
//****************************************************************************

int GoalDrawText(T_GL_HWIDGET xWindow, const char* pcText, const ST_DRAW_FONT* pxFont, T_GL_COLOR ulPen, T_GL_COORD sX, T_GL_COORD sY, ulong ulTimeOut, bool bRefresh)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xTimer, xDrawing;
	int iRet=0; // iRet must be initialized to 0

	// Drawing text
	// ************
	xDrawing = GL_Widget_SearchId(xWindow, DRAWING_ID);             // Get drawing from its id
	CHECK(xDrawing!=NULL, lblKO);
	GL_Drawing_SetPen(xDrawing, ulPen, 1, GL_UNIT_PIXEL);           // Set pen color and stroke (only 1 pixel supported)
	if (pxFont->pcName!=NULL)                                       // Customer font?
		GL_Drawing_SetFont(xDrawing, pxFont->pcName, pxFont->eStyle, pxFont->usWidth, pxFont->usHeight, GL_UNIT_PERCENT); // Yes, Set customer font
	else
		GL_Drawing_SetFont(xDrawing, "GOAL", pxFont->eStyle, pxFont->usWidth, pxFont->usHeight, GL_UNIT_PERCENT); // No, Set default GOAL font
	GL_Drawing_DrawText(xDrawing, sX, sY, GL_UNIT_PERCENT, pcText); // Draw text with pen

	CHECK(bRefresh, lblEnd);                                        // Refresh window? No, skip timer and keyboard

	// Restart timer
	// *************
	xTimer = GL_Widget_SearchId(xWindow, TIMER_ID);                 // Get timer from its id
	CHECK(xTimer!=NULL, lblKO);
	GL_Timer_SetInterval(xTimer, ulTimeOut);                        // Set timeout value

	// Loop indefinitely until the result is set from the call back functions
	// **********************************************************************
	GL_Window_MainLoop(xWindow);                                    // Wait until a result is set

	// Test the result set by the call back functions
	// **********************************************
	switch(GL_Window_GetResult(xWindow))                            // Get the result
	{
	case RES_VALID_STATUS:                                          // Key valid result
		GL_Timer_Stop(xTimer);
		iRet=GL_KEY_VALID;
		break;
	case RES_CANCEL_STATUS:                                         // Key cancel result
		GL_Timer_Stop(xTimer);
		iRet=GL_KEY_CANCEL;
		break;
	case RES_TIMER_STATUS:                                          // Timer result
		iRet=0;
		break;
	default:                                                        // Unknown result
		iRet=-1;
		break;
	}

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                              // Drawing text failed
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//          void GoalDestroyDrawing(T_GL_HWIDGET *pxWindow)
// This function destroys the drawing context by releasing all allocated memory,
//  all widgets attached.
//  This call is crucial, if it is forgotten you get a memory leak.
// This function has parameters.
//   pxWindow (I-) : Pointer on window context handle.
// This function has no return value.
//****************************************************************************

void GoalDestroyDrawing(T_GL_HWIDGET *pxWindow)
{
	// Local variables
    // ***************
		// Empty

	// Destroy screen
	// **************
	GL_Widget_Destroy(*pxWindow); // Destroy window with all widgets attached
	*pxWindow=NULL;
}

//##############################################################################
//                                   PICTURE
//##############################################################################

//****************************************************************************
//      T_GL_HWIDGET GoalCreatePicture (T_GL_HGRAPHIC_LIB xGraphicLib)
// This function creates a picture context which is composed of:
//  - A timer to exit from this screen.
//  - A title line.
//  - A picture window.
//  - Shortcut keys on 2 buttons to react on this screen:
//      Cancel Key and Valid Key
//  !!! All other keys detection will be done with standard Telium functions.
// This function has parameters.
//   xGraphicalLib (I-) : Graphic library context handle.
// This function has return value.
//   !NULL : Pointer to the handle of the picture.
//   NULL : Picture failed
//****************************************************************************

T_GL_HWIDGET GoalCreatePicture (T_GL_HGRAPHIC_LIB xGraphicLib)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xWindow, xTimer, xLayout, xLabel, xPicture, xLayout2, xButtonVal, xButtonCan;
	bool bTouch=FALSE;

	// Build picture context with 2 buttons (Cancel and Valid)
	// *******************************************************
	xWindow = GL_Window_Create(xGraphicLib);                          // Create a window in a user area
	CHECK(xWindow!=NULL, lblEnd);

	bTouch = GL_GraphicLib_IsTouchPresent(xGraphicLib);               // Is a touch screen?

	xTimer = GL_Timer_Create(xWindow);                                // Create a timer on this window
	CHECK(xTimer!=NULL, lblKO);
	GL_Widget_SetId(xTimer, TIMER_ID);                                // Timer Identifier TIMER_ID
	GL_Widget_RegisterCallback(xTimer, GL_EVENT_TIMER_OUT, CallBackTimeout); // Call back when the timer expired

	xLayout = GL_Layout_Create(xWindow);                              // Create a layout on this window
	CHECK(xLayout!=NULL, lblKO);

	xLabel = GL_Label_Create(xLayout);                                // Create a label on this layout
	CHECK(xLabel!=NULL, lblKO);
	GL_Widget_SetItem(xLabel, 0, 0);                                  // Label location on this layout
	GL_Widget_SetText(xLabel, NULL);                                  // Clear text on this label
	GL_Widget_SetShrink(xLabel, GL_DIRECTION_WIDTH);                  // Shrink beyond its size (No width scrolling cell if label goes over screen)
	GL_Widget_SetId(xLabel, LABEL_0_ID);                              // Label identifier LABEL0_ID

	xPicture = GL_Picture_Create(xLayout);                            // Create a picture on this layout
	CHECK(xPicture!=NULL, lblKO);
	GL_Widget_SetId(xPicture, PICTURE_ID);                            // Picture Identifier PICTURE_ID
	GL_Widget_SetItem(xPicture, 0, 1);                                // Picture location on this layout

	xLayout2 = GL_Layout_Create(xLayout);                             // Create a second layout on this layout
	CHECK(xLayout2!=NULL, lblKO);
	GL_Widget_SetId(xLayout2, LAYOUT2_ID);                            // Second layout identifier
	GL_Widget_SetItem(xLayout2, 0, 2);                                // Second layout location on this layout
	GL_Widget_SetGrow(xLayout2, GL_DIRECTION_WIDTH);                  // Grow beyond its size (Background width around layout will fill the complete cell)

	xButtonCan = GL_Button_Create(xLayout2);                          // Create a cancel button on this second layout
	CHECK(xButtonCan!=NULL, lblKO);
	GL_Widget_SetSource(xButtonCan, "skin://images/cancel.wgu");      // Set the cancel skinned image
	GL_Widget_SetItem(xButtonCan, 0, 0);                              // Button location on this layout
	GL_Widget_SetExpand(xButtonCan, GL_DIRECTION_WIDTH);              // Expand button width
	GL_Widget_SetShortcut(xButtonCan, GL_KEY_CANCEL);                 // Shortcut on this button
	GL_Widget_SetId(xButtonCan, BUTTON_CAN_ID);                       // Cancel button Identifier
	GL_Widget_SetGrow(xButtonCan, GL_DIRECTION_WIDTH);                // Grow beyond its size (Background width around cancel button will fill the complete cell)
	GL_Widget_RegisterCallback(xButtonCan, GL_EVENT_STYLUS_CLICK, CallBackCancelKey); // Call back when key pressed

	xButtonVal = GL_Button_Create(xLayout2);                          // Create a valid button on this second layout
	CHECK(xButtonVal!=NULL, lblKO);
	GL_Widget_SetSource(xButtonVal, "skin://images/validation.wgu");  // Set the valid skinned image
	GL_Widget_SetItem(xButtonVal, 1, 0);                              // Button location on this layout
	GL_Widget_SetExpand(xButtonVal, GL_DIRECTION_WIDTH);              // Expand button width
	GL_Widget_SetShortcut(xButtonVal, GL_KEY_VALID);                  // Shortcut on this button
	GL_Widget_SetId(xButtonVal, BUTTON_VAL_ID);                       // Valid button Identifier
	GL_Widget_SetGrow(xButtonVal, GL_DIRECTION_WIDTH);                // Grow beyond its size (Background width around valid button will fill the complete cell)
	GL_Widget_RegisterCallback(xButtonVal, GL_EVENT_STYLUS_CLICK, CallBackValidKey); // Call back when key pressed

	if(!bTouch)                                                       // Touch screen?
		GL_Widget_SetSize(xLayout2, 100, 0, GL_UNIT_PERCENT);         // No, do not show second layout (keep shortcut access on key pressed)

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                                // Window creation failed
	if (xWindow)
	{
		GL_Widget_Destroy(xWindow);                                   // Destroy window and all widgets
		xWindow=NULL;
	}
lblEnd:
	return xWindow;
}

//****************************************************************************
//        int GoalClrPicture (T_GL_HWIDGET xWindow, T_GL_COLOR ulBackColor,
//                            unsigned int uiKeys, bool bRefresh)
// This function clears the picture context, can change the background color
//  and sets the shortcut keys needed (Cancel and Valid).
//  Background color is forced to white for B&W terminal.
// This function has parameters.
//   xWindow (I-) : Window context handle.
//   ulBackColor (I-) : Drawing background color.
//   uiKeys (I-) : Shortcut keys (exp: KEY_CANCEL | KEY_VALID)
//                   Cancel Key (KEY_CANCEL)
//                   Valid Key (KEY_VALID)
//   bRefresh (I-) : Refresh or not the screen.
// This function has return value.
//   >=0 : Clear picture done.
//   <0 : Clear picture failed.
//****************************************************************************

int GoalClrPicture(T_GL_HWIDGET xWindow, T_GL_COLOR ulBackColor, unsigned int uiKeys, bool bRefresh)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xLabel, xPicture, xLayout2, xButtonVal, xButtonCan;
	int iRet;

	// Disable the complete second layout
	// **********************************
	xLayout2 = GL_Widget_SearchId(xWindow, LAYOUT2_ID);          // Retrieve the second layout
	CHECK(xLayout2!=NULL, lblKO);
	xButtonCan = GL_Widget_SearchId(xWindow, BUTTON_CAN_ID);     // Retrieve the cancel button on this second layout
	CHECK(xButtonCan!=NULL, lblKO);
	xButtonVal = GL_Widget_SearchId(xWindow, BUTTON_VAL_ID);     // Retrieve the valid button on this second layout
	CHECK(xButtonVal!=NULL, lblKO);

	GL_Widget_SetVisible(xLayout2, false);                       // Blind all widgets on this second layout
	GL_Widget_SetVisible(xButtonCan, false);                     // Blind the cancel button
	GL_Widget_SetFocusable(xButtonCan, false);                   // No focus on cancel button
	GL_Widget_UnregisterCallback(xButtonCan, GL_EVENT_STYLUS_CLICK, CallBackCancelKey); // Unregister call back on cancel button
	GL_Widget_SetVisible(xButtonVal, false);                     // Blind the valid button
	GL_Widget_SetFocusable(xButtonVal, false);                   // No focus on valid button
	GL_Widget_UnregisterCallback(xButtonVal, GL_EVENT_STYLUS_CLICK, CallBackValidKey); // Unregister call back on valid button

	// Set the second layout with the right properties
	// ***********************************************
	if (uiKeys != 0)                                             // Shortcut keys?
		GL_Widget_SetVisible(xLayout2, true);                    // Yes, enable the second layout

	if ((uiKeys & KEY_CANCEL) == KEY_CANCEL)                     // Cancel key?
	{
		GL_Widget_SetVisible(xButtonCan, true);                  // Yes, show the cancel key on this second layout
		GL_Widget_RegisterCallback(xButtonCan, GL_EVENT_STYLUS_CLICK, CallBackCancelKey); // Register call back when cancel key pressed or touched
	}

	if ((uiKeys & KEY_VALID) == KEY_VALID)                       // Valid key?
	{
		GL_Widget_SetVisible(xButtonVal, true);                  // Yes, show the valid key on this second layout
		GL_Widget_RegisterCallback(xButtonVal, GL_EVENT_STYLUS_CLICK, CallBackValidKey); // Register call back when valid key pressed or touched
	}

	if (IsColorDisplay())                                        // Color display?
		GL_Widget_SetBackColor(xWindow, ulBackColor);            // Yes, set window back color
	else
	{
		ulBackColor = GL_COLOR_WHITE;                            // No, force window back color to white
		GL_Widget_SetBackColor(xWindow, ulBackColor);
	}

	// Clear Title
	// ***********
	xLabel = GL_Widget_SearchId(xWindow, LABEL_0_ID);            // Get label from its id
	GL_Widget_SetText(xLabel, NULL);                             // Remove label text

	// Clear picture
	// *************
	xPicture = GL_Widget_SearchId(xWindow, PICTURE_ID);          // Get picture from its id
	GL_Widget_SetSource(xPicture, "");                           // Clear picture
	GL_Widget_SetBorders(xPicture, 0, 0, 0, 0, GL_UNIT_PIXEL, ulBackColor); // Remove border with window back color

	if (bRefresh)                                                // Refresh window?
		GL_Window_Dispatch(xWindow, 0);                          // Yes, refresh it

	iRet=1;
	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                           // Clear picture failed
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//    int GoalDspPicture (T_GL_HWIDGET xWindow, char *pcTitle,
//                        const char* pcPicture, const ST_IMAGE* pxImage,
//                        ulong ulTimeOut, bool bRefresh)
// This function displays a picture on screen for B&W terminal or color terminal.
//  The picture has the following properties:
//   - Pen Color,Font for title
//   - Expand, Border, Margin for picture
//  A Time-out to exit from the screen.
//  Refresh or not the screen.
// This function has parameters.
//   xWindow (I-) : Window context handle.
//   pcTitle (I-) : To show a title on top of the picture.
//   pcPicture (I-) : The picture to display (.BMP, .GIF etc...)
//   pxImage (I-) : Picture properties.
//   ulTimeOut (I-) : Timeout in milliseconds.
//   bRefresh (I-) : Refresh or not the screen.
// This function has return value.
//   >=0 : Display picture done (Exit screen : 0=timeout,GL_KEY_CANCEL,GL_KEY_VALID).
//   <0 : Display picture failed.
//****************************************************************************

int GoalDspPicture(T_GL_HWIDGET xWindow, char *pcTitle, const char* pcPicture, const ST_IMAGE* pxImage, ulong ulTimeOut, bool bRefresh)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xTimer, xLabel, xPicture;
	int iRet=0; // iRet must be initialized to 0

	// Display label
	// *************
	xLabel = GL_Widget_SearchId(xWindow, LABEL_0_ID); // Get label from its id
	CHECK(xLabel!=NULL, lblKO);

	GL_Widget_SetVisible(xLabel, false);              // Blind title if null
	if (pcTitle!=NULL)
	{
		GL_Widget_SetVisible(xLabel, true);
		GL_Widget_SetText(xLabel, "%s", pcTitle);     // Show title (Add %s to allow '%' to be displayed)

		if (IsColorDisplay())                         // Color display?
		{                                             // Yes
			// Color properties
			// ================
			if (pxImage)
			{
				GL_Widget_SetForeColor(xLabel, pxImage->xColor.ulPen);           // Pen color
				if (pxImage->xColor.bGrowWidth)                                  // Grow beyond its size
					GL_Widget_SetGrow(xLabel, GL_DIRECTION_WIDTH);               // Background width around the label will fill the complete cell
				if (pxImage->xColor.xFont.pcName != NULL)
					GL_Widget_SetFontName(xLabel, pxImage->xColor.xFont.pcName); // Font name
				GL_Widget_SetFontScale(xLabel, pxImage->xColor.xFont.eScale);    // Font scale
				GL_Widget_SetFontStyle(xLabel, pxImage->xColor.xFont.eStyle);    // Font style
			}
		}
		else                                           // No
		{
			// Black & White properties
			// ========================
			if (pxImage)
			{
				if (pxImage->xBW.bGrowWidth)                                     // Grow beyond its size
					GL_Widget_SetGrow(xLabel, GL_DIRECTION_WIDTH);               // Background width around the label will fill the complete cell
				if (pxImage->xBW.xFont.pcName != NULL)
					GL_Widget_SetFontName(xLabel, pxImage->xBW.xFont.pcName);    // Font name
				GL_Widget_SetFontScale(xLabel, pxImage->xBW.xFont.eScale);       // Font scale
				GL_Widget_SetFontStyle(xLabel, pxImage->xBW.xFont.eStyle);       // Font style
			}
		}
	}

	// Display picture
	// ***************
	xPicture = GL_Widget_SearchId(xWindow, PICTURE_ID); // Get picture from its id
	GL_Widget_SetSource(xPicture, pcPicture);
	GL_Widget_SetTransformation(xPicture, GL_TRANSFORMATION_STRETCH_ALL); // Stretched along all directions
	GL_Widget_SetShrink(xPicture, GL_DIRECTION_ALL);    // Shrink beyond its size (Picture shrink automatically if picture goes over screen)

	if (IsColorDisplay())                               // Color display?
	{                                                   // Yes, set expand, border and margin
		GL_Widget_SetExpand(xPicture, pxImage->xColor.eExpand);
		GL_Widget_SetBorders(xPicture, pxImage->xColor.xBorder.usLeft, pxImage->xColor.xBorder.usTop, pxImage->xColor.xBorder.usRight, pxImage->xColor.xBorder.usBottom, GL_UNIT_PIXEL, pxImage->xColor.xBorder.ulColor);
		GL_Widget_SetMargins(xPicture, pxImage->xColor.xMargin.usLeft, pxImage->xColor.xMargin.usTop, pxImage->xColor.xMargin.usRight, pxImage->xColor.xMargin.usBottom, GL_UNIT_PIXEL);
	}
	else
	{                                                   // No, set expand, border and margin
		GL_Widget_SetExpand(xPicture, pxImage->xBW.eExpand);
		GL_Widget_SetBorders(xPicture, pxImage->xBW.xBorder.usLeft, pxImage->xBW.xBorder.usTop, pxImage->xBW.xBorder.usRight, pxImage->xBW.xBorder.usBottom, GL_UNIT_PIXEL, pxImage->xBW.xBorder.ulColor);
		GL_Widget_SetMargins(xPicture, pxImage->xBW.xMargin.usLeft, pxImage->xBW.xMargin.usTop, pxImage->xBW.xMargin.usRight, pxImage->xBW.xMargin.usBottom, GL_UNIT_PIXEL);
	}

	CHECK(bRefresh, lblEnd);                            // Refresh window? No, skip timer and keyboard

	// Restart timer
	// *************
	xTimer = GL_Widget_SearchId(xWindow, TIMER_ID);     // Get timer from its id
	CHECK(xTimer!=NULL, lblKO);
	GL_Timer_SetInterval(xTimer, ulTimeOut);            // Set timeout value

	// Loop indefinitely until the result is set from the call back functions
	// **********************************************************************
	GL_Window_MainLoop(xWindow);                        // Wait until a result is set

	// Test the result set by the call back functions
	// **********************************************
	switch(GL_Window_GetResult(xWindow))                // Get the result
	{
	case RES_VALID_STATUS:                              // Key valid result
		GL_Timer_Stop(xTimer);
		iRet=GL_KEY_VALID;
		break;
	case RES_CANCEL_STATUS:                             // Key cancel result
		GL_Timer_Stop(xTimer);
		iRet=GL_KEY_CANCEL;
		break;
	case RES_TIMER_STATUS:                              // Timer result
		iRet=0;
		break;
	default:                                            // Unknown result
		iRet=-1;
		break;
	}

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                  // Display picture failed
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//          void GoalDestroyPicture (T_GL_HWIDGET *pxWindow)
// This function destroys the picture context by releasing all allocated memory,
//  and all widgets attached.
//  This call is crucial, if it is forgotten you get a memory leak.
// This function has parameters.
//   pxWindow (I-) : Pointer on window context handle.
// This function has no return value.
//****************************************************************************

void GoalDestroyPicture(T_GL_HWIDGET *pxWindow)
{
	// Local variables
    // ***************
		// Empty

	// Destroy screen
	// **************
	GL_Widget_Destroy(*pxWindow); // Destroy window with all widgets attached
	*pxWindow=NULL;
}

//##############################################################################
//                                   PRINTING
//##############################################################################

//****************************************************************************
//      T_GL_HWIDGET GoalCreateDocument (T_GL_HGRAPHIC_LIB xGraphicLib,
//                                       T_GL_ENCODING_CHARSET eCHarSet)
// This function creates a document context which is composed of:
//  - A document to print.
//  - Encoding charsets:
//      GL_ENCODING_UTF8 => Unicode utf8
//      GL_ENCODING_ISO_8859_X => ISO 8859
// This function has parameters.
//   xGraphicalLib (I-) : Graphic library context handle.
//   eCharSet (I-) : Encoding charsets.
// This function has return value.
//   !NULL : Pointer to the handle of the document.
//   NULL : Document failed
//****************************************************************************

T_GL_HWIDGET GoalCreateDocument (T_GL_HGRAPHIC_LIB xGraphicLib, T_GL_ENCODING_CHARSET eCharSet)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xDocument, xLayout;

	// Build document context
	// **********************
	xDocument = GL_Document_Create(xGraphicLib);      // Create a document to print
	CHECK(xDocument!=NULL, lblEnd);

	GL_GraphicLib_SetCharset(xGraphicLib, eCharSet);  // Changes the encoding charset of the graphic library

	xLayout = GL_Layout_Create(xDocument);            // Create a layout on this document
	CHECK(xLayout!=NULL, lblKO);
	GL_Widget_SetId(xLayout, LAYOUT3_ID);             // Layout Identifier LAYOUT3_ID

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                // Document creation failed
	if (xDocument)
	{
		GL_Widget_Destroy(xDocument);                 // Destroy document and all widgets
		xDocument=NULL;
	}
lblEnd:
	return xDocument;
}

//****************************************************************************
//    int GoalPrnLine(T_GL_HWIDGET xDocument, ushort usLine, char *pcText,
//                    const ST_PRN_LINE* pxLine)
// This function build a string on document for printing.
//  The line has the following properties:
//   - Text Align, Background Align, Reverse mode,
//   - Background size (width),
//   - Text padding, Border, Margin, Font
// This function has parameters.
//   xDocument (I-) : Document context handle.
//   usLine (I-) : Line number.
//   pcText (I-) : Text to print.
//   pxLine (I-) : Line properties.
// This function has return value.
//   >=0 : Build line done.
//   <0 : Build line failed.
//****************************************************************************

int GoalPrnLine(T_GL_HWIDGET xDocument, ushort usLine, char *pcText, const ST_PRN_LINE* pxLine)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xLayout, xPrint;
	int iRet;

	// Build line on document
	// **********************
	xLayout = GL_Widget_SearchId(xDocument, LAYOUT3_ID);      // Get layout from its id
	CHECK(xLayout!=NULL, lblKO);

	xPrint = GL_Print_Create(xLayout);                        // Create a print label designed to be printed on this layout
	CHECK(xPrint!=NULL, lblKO);
	GL_Widget_SetItem(xPrint, 0, usLine);                     // Print label location on this layout
	GL_Widget_SetText(xPrint, "%s", pcText);                  // Print text (Add %s to allow '%' to be printed)
	GL_Widget_SetWrap(xPrint, true);                          // Set the wrap of text (Allows text to automatically return to the next line if it does not fit in width)
	GL_Widget_SetShrink(xPrint, GL_DIRECTION_WIDTH);          // Shrink beyond its size (No width scrolling cell if text goes over printer size)

	GL_Widget_SetTextAlign(xPrint, pxLine->eTextAlign);       // Text alignment
	GL_Widget_SetBackAlign(xPrint, pxLine->eBackAlign);       // Background alignment
	if (pxLine->usSizeWidth < 99)                             // Background size
		GL_Widget_SetMinSize(xPrint, pxLine->usSizeWidth, 0, GL_UNIT_PERCENT); // The size
	else
		GL_Widget_SetExpand(xPrint, GL_DIRECTION_WIDTH);                       // Full size
	if (!pxLine->bReverse)                                    // Reverse mode?
	{                                                         // No
		GL_Widget_SetForeColor(xPrint, GL_COLOR_BLACK);       // Force pen color to black and brush color to white
		GL_Widget_SetBackColor(xPrint, GL_COLOR_WHITE);
	}
	else
	{                                                         // Yes
		GL_Widget_SetForeColor(xPrint, GL_COLOR_WHITE);       // Force pen color to white and brush color to black
		GL_Widget_SetBackColor(xPrint, GL_COLOR_BLACK);
	}
	                                                          // Padding, Border and Margin
	GL_Widget_SetTextPaddings(xPrint, pxLine->xPadding.usLeft, pxLine->xPadding.usTop, pxLine->xPadding.usRight, pxLine->xPadding.usBottom, GL_UNIT_PERCENT);
	if ((pxLine->xBorder.ulColor & 0x00FFFFFF) != 0x00FFFFFF) // Force border to black or white
		GL_Widget_SetBorders(xPrint, pxLine->xBorder.usLeft, pxLine->xBorder.usTop, pxLine->xBorder.usRight, pxLine->xBorder.usBottom, GL_UNIT_PIXEL, pxLine->xBorder.ulColor & 0xFF000000);
	else
		GL_Widget_SetBorders(xPrint, pxLine->xBorder.usLeft, pxLine->xBorder.usTop, pxLine->xBorder.usRight, pxLine->xBorder.usBottom, GL_UNIT_PIXEL, pxLine->xBorder.ulColor | 0x00FFFFFF);
	GL_Widget_SetMargins(xPrint, pxLine->xMargin.usLeft, pxLine->xMargin.usTop, pxLine->xMargin.usRight, pxLine->xMargin.usBottom, GL_UNIT_PIXEL);
	if (pxLine->xFont.pcName != NULL)
		GL_Widget_SetFontName(xPrint, pxLine->xFont.pcName);  // Font name
	GL_Widget_SetFontScale(xPrint, pxLine->xFont.eScale);     // Font scale
	GL_Widget_SetFontStyle(xPrint, pxLine->xFont.eStyle);     // Font style

	iRet=1;
	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                        // Build line on document failed
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//   int GoalPrnMultiLine(T_GL_HWIDGET xDocument, ushort usLine, ushort usSize,
//                        char *pcData, ushort usLen, const ST_PRN_LINE* pxLine)
//  This function sends a data buffer to the document.
//   The buffer is divided on lines of size bytes max except the last line.
//   Each line is automatically sent to the document. The '\n' automatically
//   switches to the next line.
//  This function has parameters:
//    xDocument (I-) : Window context handle.
//    usLine (I-) : Line number.
//    usSize (I-) : Line size max.
//    pcData (I-) : Data to send to the document.
//    usLen (I-) : Length of data.
//    pxLine (I-) : Line properties.
//  This function has return value.
//    >=0 : Build buffer done.
//    <0 : Build buffer failed.
//****************************************************************************

int GoalPrnMultiLine(T_GL_HWIDGET xDocument, ushort usLine, ushort usSize, char *pcData , ushort usLen, const ST_PRN_LINE* pxLine)
{
	// Local variables
    // ***************
	ushort usIdx=0;
	ushort usCount=0;
	char tcBuffer[1024+1];
	int iRet=-1;

	// Build document in progress
	// **************************
	CHECK ((pcData!=NULL) && (usLen!=0), lblKO)

	memset(tcBuffer, 0, sizeof(tcBuffer));
	while(1)
	{
		if (usLen > 0)                 // Check if it is the end of data
		{                              // No, it's a line with '\n' detected
			if (usCount < usSize)      // Save character into buffer
			{
				if (*pcData == '\n')
					usCount=0;
				else
					usCount++;
				tcBuffer[usIdx++] = *pcData++;
				usLen--;
			}
			else                       // Bloc detected
			{
				tcBuffer[usIdx++] = '\n';
				usCount=0;
			}
		}
		else
		{                              // Yes, it's the end of data
			tcBuffer[usIdx++] = '\n';
			break;                     // Exit from the loop
		}
	}
                                       // Send line to the document
	iRet = GoalPrnLine(xDocument, usLine, tcBuffer, pxLine);

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                 // Build buffer failed.
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//    int GoalPrnPicture (T_GL_HWIDGET xDocument, ushort usLine,
//                        char *pcPicture, const ST_BORDER* pxBorder)
// This function build a picture on document for printing.
//  The picture has the following properties:
//   - Picture shrinks beyond its size
//   - Border around the picture
// This function has parameters.
//   xDocument (I-) : Document context handle.
//   usLine (I-) : Line number.
//   pcPicture (I-) : Picture to print.
//   pxBorder (I-) : Border properties.
// This function has return value.
//   >=0 : Build picture done.
//   <0 : Build picture failed.
//****************************************************************************

int GoalPrnPicture(T_GL_HWIDGET xDocument, ushort usLine, const char* pcPicture, const ST_BORDER* pxBorder)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xLayout, xPrint;
	int iRet;

	// Build picture on document
	// *************************
	xLayout = GL_Widget_SearchId(xDocument, LAYOUT3_ID);    // Get layout from its id
	CHECK(xLayout!=NULL, lblKO);

	xPrint = GL_Picture_Create(xLayout);                    // Create a picture designed to be printed on this layout
	CHECK(xPrint!=NULL, lblKO);
	GL_Widget_SetItem(xPrint, 0, usLine);                   // Picture location on this layout
	GL_Widget_SetSource(xPrint, pcPicture);                 // The picture to print

	GL_Widget_SetShrink(xPrint, GL_DIRECTION_WIDTH);        // Shrink beyond its size (Picture shrinks automatically if picture goes over printer size)
	                                                        // Border around the picture
	GL_Widget_SetBorders(xPrint, pxBorder->usLeft, pxBorder->usTop, pxBorder->usRight, pxBorder->usBottom, GL_UNIT_PIXEL, pxBorder->ulColor);

	iRet=1;
	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                      // Build picture failed.
	iRet=-1;
lblEnd:
	return iRet;
}

//****************************************************************************
//          int GoalPrnDocument (T_GL_HWIDGET xDocument)
// This function prints the document built.
// This function has parameters.
//   xDocument (I-) : Document context handle.
// This function has return value.
//   >=0 : Print document done.
//   <0 : Print document failed.
//****************************************************************************

int GoalPrnDocument(T_GL_HWIDGET xDocument)
{
	// Local variables
    // ***************
	T_GL_ERROR_CODE eRet;
	int iRet=-1;

	// Printing in progress
	// ********************
	eRet = GL_Document_Print(xDocument, 0);
	if ((eRet == GL_SUCCESS) || !IsPrinter())
		iRet=1;

	return iRet;
}

//****************************************************************************
//          void GoalDestroyDocument (T_GL_HWIDGET *pxDocument)
// This function destroys the document context by releasing all allocated memory,
//  and all widgets attached.
//  This call is crucial, if it is forgotten you get a memory leak.
// This function has parameters.
//   pxDocument (I-) : Pointer on document context handle.
// This function has no return value.
//****************************************************************************

void GoalDestroyDocument(T_GL_HWIDGET *pxDocument)
{
	// Local variables
    // ***************
		// Empty

	// Destroy document
	// ****************
	GL_Widget_Destroy(*pxDocument); // Destroy document with all widgets attached
	*pxDocument=NULL;
}








