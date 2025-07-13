/**
 * DateScreen.c
 *
 * This file manage the screen actions.
 *
 */
#include "SDK30.H"

#include "Utils.h"
#include "Menu.h"
#include "widgetMappings.h"

/*+************* #DEFINES **************************************************+*/

/*+************* CONSTANTS *************************************************+*/
const ulong DATESCREEN_OK_STATUS = 0;
const ulong DATESCREEN_CANCEL_STATUS = 1;

/*+************* STRUCTURES ************************************************+*/

/*+************* VARIABLES *************************************************+*/

/*+************* FUNCTION PROTOTYPES ***************************************+*/
static bool dateScreenSOnOkPressed(T_GL_HMESSAGE message);
static bool genericSOnCancelPressed(T_GL_HMESSAGE message);
static bool dateScreenSGetInputDate(T_GL_HWIDGET window, date_t *inputDate);

/**
 * This function displays a sample screen using GOAL resource file (.gml).
 *
 * \note The user can input a date, which is validated via GOAL CallBack functions.
 *       If the date is not valid, an error dialog is displayed, and the date has to be re-entered.
 *       Otherwise, the date is displayed in a dialog.
 *       The user can abort selecting "Cancel" button.
 */
void dateScreenUseGoalResource(void)
{

  const char* RESOURCE_NAME = "dal://dateScreen";

  T_GL_HWIDGET window, button_ok, button_cancel;
  // message displayed in the dialog box
  char message[200];

  // Instantiates the goal resource screen using the resource file
  // the dal name must the same as in the gml file  (example inputDateScreen).
  window = GL_GraphicLib_ReadResource(goalGraphicLibInstance, RESOURCE_NAME);

  if (window == NULL)
  {
    // GOAL fails loading the resource file (wrong name, no GOAL resource file in the terminal...)
    sprintf(message, "Cannot find\n%s", RESOURCE_NAME);

    // Displays the error in a dialog
    GL_Dialog_Message(goalGraphicLibInstance, "Error", message, GL_ICON_ERROR,
        GL_BUTTON_VALID, 3000);
    return;
  }

  // Creates a CallBack to be called when the "OK" button is pressed
  button_ok = GL_Widget_SearchId(window, DATE_SCREEN_BUTTON_OK);
  GL_Widget_RegisterCallback(button_ok,
      GL_EVENT_STYLUS_CLICK, dateScreenSOnOkPressed);


  // Creates a CallBack to be called when the "Cancel" button is pressed
  button_cancel = GL_Widget_SearchId(window, GENERIC_BUTTON_CANCEL);
  GL_Widget_RegisterCallback(button_cancel,
      GL_EVENT_STYLUS_CLICK, genericSOnCancelPressed);

  // This function hangs until an execution result is positioned. See "GL_Message_SetResult"
  // and "GL_Window_GetResult" APIs
  GL_Window_MainLoop(window);

  // Test the result set by the CallBack functions
  if (GL_Window_GetResult(window) == DATESCREEN_CANCEL_STATUS)
  {
    GL_Dialog_Message(goalGraphicLibInstance, "Warning", "Canceled",
        GL_ICON_WARNING, GL_BUTTON_VALID, 3000);
  }
  else //OK button pressed
  {
    date_t inputDate;

    // Gets the input date, which is valid because the CallBack
    // "screenOnOkPressed" is in charge of this validation.
    if (dateScreenSGetInputDate(window, &inputDate))
    {
      sprintf(message, "The date is:\n%04d/%02d/%02d", inputDate.year,
          inputDate.month, inputDate.day);

      // A dialog box is displayed with the input date
      GL_Dialog_Message(goalGraphicLibInstance, "Info", message,
          GL_ICON_INFORMATION, GL_BUTTON_VALID, 3000);
    }
  }

  // The screen is destroyed to release memory
  GL_Widget_Destroy(window);
}

/**
 * This function is a GOAL CallBack called when OK button is pressed in the resource sample date screen.
 * The input date format is checked.
 *
 * \param message the CallBack message
 *
 * \note Each Goal CallBack requires this function signature (bool as return value and T_GL_HMESSAGE as parameter)
 *
 * \return true if the CallBack has been treated
 *
 */
static bool dateScreenSOnOkPressed(T_GL_HMESSAGE message)
{
  char res;
  T_GL_HWIDGET window = GL_Message_GetWindow(message);
  date_t inputDate;

  // Gets and validates the input date
  res = dateScreenSGetInputDate(window, &inputDate);

  if (res == true) // date is valid
  {
    // Calling "GL_Message_SetResult"  forces end of "GL_Window_MainLoop(window);" with result set to OK_STATUS for no error
    GL_Message_SetResult(message, DATESCREEN_OK_STATUS);
  }
  else //date is not valid
  {
    // GL_Message_SetResult is not called to stay in "GL_Window_MainLoop(window);"
    GL_Dialog_Message(goalGraphicLibInstance, "Error",
        "Please enter\na valid date", GL_ICON_ERROR, GL_BUTTON_VALID, 3000);

    // Clears the edit widget (which was filled with the wrong date).
    GL_Widget_SetText(GL_Widget_SearchId(window, DATE_SCREEN_EDIT_DATE), "___/__/__");

    // The focus is managed according to the order the widgets are declared in the resource file.
    // The "edit" widget is declared just before the "OK" button,
    // then the GL_Window_PreviousFocus will set the focus on the "edit" widget.
    GL_Window_PreviousFocus(window);
  }
  return true;

}

/**
 * This function is a GOAL CallBack called when "Cancel" button is pressed.
 *
 *
 * \param message the CallBack message
 *
 * \note Each Goal CallBack requires this function signature (bool as return value and T_GL_HMESSAGE as parameter)
 *
 * \return true if the CallBack has been treated
 */
static bool genericSOnCancelPressed(T_GL_HMESSAGE message)
{
  // force end of "GL_Window_MainLoop(window);" with result set to CANCEL_STATUS
  GL_Message_SetResult(message, DATESCREEN_CANCEL_STATUS);
  return true;
}

/**
 * This function returns the date entered by the user in the resource sample date screen.
 *
 *
 * \param window the current GOAL window
 * \param inputDate the date to be filled by the function
 *
 * \return true if the input date is valid, false otherwise
 */
static bool dateScreenSGetInputDate(T_GL_HWIDGET window, date_t *inputDate)
{
  char date[10 + 1];
  char year[4 + 1];
  char month[2 + 1];
  char day[2 + 1];
  char * posUnderscore;

  strncpy(date, GL_Widget_GetText(GL_Widget_SearchId(window, DATE_SCREEN_EDIT_DATE)),
      sizeof(date));

  // In the resource file, the edit is filled with '_' characters by default.
  // They must be have been replaced by the input date.
  // If there is still some '_', the date is incorrect.
  posUnderscore = strstr(date, "_");

  if (posUnderscore != NULL)
    return false;

  memset(year, 0, sizeof(year));
  memset(month, 0, sizeof(month));
  memset(day, 0, sizeof(day));

  strncpy(year, &date[0], 4);
  strncpy(month, &date[5], 2); //ignore '/'
  strncpy(day, &date[8], 2); //ignore '/'

  inputDate->year = atoi(year);
  inputDate->month = atoi(month);
  inputDate->day = atoi(day);

  if (!utilsCheckDate(inputDate))
    return false;

  return true;
}
