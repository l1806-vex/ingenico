/**
 * Menu.c
 *
 * This file manage the menu.
 *
 */

#include "SDK30.H"

#include "DateScreen.h"
#include "Menu.h"
#include "GL_Samples.h"

/*+************* #DEFINES **************************************************+*/

/*+************* CONSTANTS *************************************************+*/

/*+************* STRUCTURES ************************************************+*/

/*+************* VARIABLES *************************************************+*/
T_GL_HGRAPHIC_LIB goalGraphicLibInstance = NULL;

/*+************* FUNCTION PROTOTYPES ***************************************+*/
/**
 * Main menu
 *
 * - choice 0: to display a GOAL dialog box
 * - choice 1: to display a screen using GOAL resource file (.gml)
 * - choice 2: to exit
 *
 */
void menuDisplay(void)
{
  char choice = 0;
  char choiceSample = 0;
  FILE *keyboard = NULL, *mouse = NULL, *touch = NULL, *display = NULL;

  const char *MenuUser[] =
  { "Sample Dialog", "Goal Resource Sample","CHM Samples" , "Exit", 0 };

  // Disables header, footer, led in order to Maximize canvas size
  int savedStatusHeader, savedStatusLeds, savedStatusFooter;

  savedStatusHeader=DisplayHeader(_OFF_);
  savedStatusLeds=DisplayLeds(_OFF_);
  savedStatusFooter=DisplayFooter(_OFF_);

  // Open display
  display = fopen("DISPLAY", "w*");
  // Open keyboard
  keyboard = fopen("KEYBOARD", "r*");
  // Open mouse
  mouse = fopen("MOUSE", "r*");
  // Open touch
  touch = fopen("TSCREEN", "r*");

  // Creates an instance of the graphics library.
  // This creation takes some time. To be quicker it can also be instantiated only once in application's life
  goalGraphicLibInstance = GL_GraphicLib_Create();

  do
  {
    //Display the menu using GOAL
    choice = GL_Dialog_Menu(goalGraphicLibInstance, "Select", MenuUser, choice,
        GL_BUTTON_DEFAULT , GL_KEY_0, GL_TIME_INFINITE);

    switch (choice)
    {
    case 0:
      // Displays a GOAL sample dialog
      GL_Dialog_Message(goalGraphicLibInstance, "Sample Dialog",
          "This is the\ndialog message", GL_ICON_INFORMATION, GL_BUTTON_VALID,
          3000);
      break;
    case 1:
      // Loads a GOAL resource file
      dateScreenUseGoalResource();
      break;
    case 2:
      // Run samples of the CHM
      choiceSample = GL_Samples_Menu(goalGraphicLibInstance);
      break;
    default:
      //exit
      break;
    }
  } while (choice != 2);

  // Release resources from the graphics library.
  // This call is crucial to the end of life of the application, this call frees resources and release memory allocated
  GL_GraphicLib_Destroy(goalGraphicLibInstance);
  goalGraphicLibInstance = NULL;

  // close touch
  if (touch)
  {
    fclose(touch);
    touch = NULL;
  }
  // close mouse
  if (mouse)
  {
    fclose(mouse);
    mouse = NULL;
  }
  // close keyboard
  if (keyboard)
  {
    fclose(keyboard);
    keyboard = NULL;
  }
  // close display
  if (display)
  {
    fclose(display);
    display = NULL;
  }
  // Restore display context
  DisplayHeader(savedStatusHeader);
  DisplayLeds(savedStatusLeds);
  DisplayFooter(savedStatusFooter);

  return;
}
