#include "SDK30.H"
#include "GL_GraphicLib.h"
#include "SampDetailsDef.h"
#include "SampDetailsDiag.h"
#include "widgetMappings.h"


/*+************* DATA DECLARATIONS ***************************************---*/
extern T_GL_HGRAPHIC_LIB global_graphicLib;


/*+************* FUNCTION PROTOTYPES ***************************************+*/
bool USRDetails_resOKBUTTON_pressed(T_GL_HMESSAGE message);
bool USRDetails_resCANCELBUTTON_pressed(T_GL_HMESSAGE message);
bool USRprintDetailsRes(T_GL_HMESSAGE message);

/*+************* FUNCTION DEFINTIONS ***************************************+*/

/**
 * This function displays a sample screen using GOAL resource file (.gml).
 *
 * \note The user can input a date, which is validated via GOAL CallBack functions.
 *       If the date is not valid, an error dialog is displayed, and the date has to be re-entered.
 *       Otherwise, the date is displayed in a dialog.
 *       The user can abort selecting "Cancel" button.
 */
void USRinputDetailsRes(void)
{

   T_GL_HWIDGET window;
   //dal name of the GOAL resource screen to display
   char ResourceName[100];
   // message displayed in the dialog box
   char message[100];

   strcpy(ResourceName,"dal://inputDetailsScreen");

   // Instantiates the goal resource screen using the resource file
   // the dal name must the same as in the gml file  (example inputDateScreen).
   window = GL_GraphicLib_ReadResource(global_graphicLib,ResourceName);

   if (window == NULL)
   {
      // GOAL fails loading the resource file (wrong name, no GOAL resource file in the terminal...)
      sprintf(message, "Cannot find\nscreen resource\n%s", ResourceName);

      // Displays the error in a dialog
      GL_Dialog_Message(global_graphicLib, "Error", message,GL_ICON_NONE, GL_BUTTON_VALID, 3000);
      return;
   }

   // Creates a CallBack to be called when the "OK" button is pressed
   GL_Widget_RegisterCallback(GL_Widget_SearchId(window,ID_BUTTON_OK), GL_EVENT_STYLUS_CLICK,USRDetails_resOKBUTTON_pressed);

   // Creates a CallBack to be called when the "Cancel" button is pressed
   GL_Widget_RegisterCallback(GL_Widget_SearchId(window,ID_BUTTON_CANCEL), GL_EVENT_STYLUS_CLICK,USRDetails_resCANCELBUTTON_pressed);
   // This function hangs until an execution result is positioned. See "GL_Message_SetResult"
   // and "GL_Window_GetResult" APIs
   GL_Window_MainLoop(window);

   // Test the result set by the CallBack functions
   if (GL_Window_GetResult(window) == GOAL_CANCEL_STATUS)
   {
      GL_Dialog_Message(global_graphicLib, "Info", "Cancelled",GL_ICON_NONE, GL_BUTTON_VALID, 3000);
   }
   else //OK button pressed
   {
      // A dialog box is displayed with the input date
//      GL_Dialog_Message(global_graphicLib, "Info", message,GL_ICON_INFORMATION, GL_BUTTON_VALID, 3000);
   }

   // The screen is destroyed to release memory
   GL_Widget_Destroy(window);
}

bool USRDetails_resCANCELBUTTON_pressed(T_GL_HMESSAGE message)
{
	GL_Message_SetResult(message, 0);
	return false;
}
bool USRDetails_resOKBUTTON_pressed(T_GL_HMESSAGE message)
{
	bool bPrint;

	bPrint=USRprintDetailsRes(message);
	GL_Message_SetResult(message, 0);
	return true;
}

bool USRprintDetailsRes(T_GL_HMESSAGE message)
{
	bool result;

	result = GL_Dialog_Message  (global_graphicLib, "Error Print", "Print using Resource\nis not yet\nimplemented", GL_ICON_NONE, GL_BUTTON_VALID, 3*GL_TIME_SECOND);


	return true;
}
