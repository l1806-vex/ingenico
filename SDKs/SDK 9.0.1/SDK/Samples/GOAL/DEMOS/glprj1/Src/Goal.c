#include "SDK30.H"
#include "GL_GraphicLib.h"
#include "Goal.h"

/*+************* CONSTANTS *************************************************+*/
static const int GOAL_CANCEL_STATUS = -1;
static const int GOAL_OK_STATUS = 0;

/*+************* GLOBAL VARIABLES ****************************************---*/
static FILE *gKeyboard;
static FILE *gTouch;
static FILE *gMouse;
static FILE *gDisplay;

/*+************* FUNCTION DEFINTIONS ***************************************+*/

/**
 * Initialize the display context to maximize the canvas on user area
 */
void goalSInitContext(CGUI_CONTEXT_STRUCT *ManagerContext, bool bFullScreenn)
{
   // Configure manager display
   memset(ManagerContext, 0, sizeof(CGUI_CONTEXT_STRUCT));
   ManagerContext->CGUIStatus = CGUI_NOT_NEEDED;
   if (bFullScreenn==true){
	   ManagerContext->HeaderStatus = _PERIPH_OFF; // Disable header
	   ManagerContext->FooterStatus = _PERIPH_OFF; // Disable footer
   }
   else{
	   ManagerContext->HeaderStatus = _PERIPH_ON; // Disable header
	   ManagerContext->FooterStatus = _PERIPH_ON; // Disable footer
   }

   ManagerContext->LedsStatus = _PERIPH_OFF; // Disable led
   ManagerContext->CanvasStatus = CANVAS_NOT_USED; // Maximize canvas on User Area

   // Save display context
   PushCGUIContext(ManagerContext);

   // Open display
   gDisplay = fopen("DISPLAY", "w*");
   // Open keyboard
   gKeyboard = fopen("KEYBOARD", "r*");
   // Open mouse
   gMouse = fopen("MOUSE", "r*");
   // Open touch
   gTouch = fopen("TSCREEN", "r*");

   return;
}

/**
 * Restore display context
 */
void goalSReleaseContext(void)
{
	// close touch
	if (gTouch){fclose(gTouch);gTouch = NULL; }
	// close mouse
	if (gMouse){fclose(gMouse);gMouse = NULL;}
	// close keyboard
	if (gKeyboard){fclose(gKeyboard);gKeyboard = NULL;}
	// close display
	if (gDisplay){fclose(gDisplay);gDisplay = NULL;}

   // Restore display context
   PopCGUIContext();
   return;
}

