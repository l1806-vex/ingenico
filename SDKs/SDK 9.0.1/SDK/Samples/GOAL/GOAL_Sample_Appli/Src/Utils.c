/**
 * Utils.c
 *
 * This file manage utilities.
 *
 */

#include "Utils.h"

/*+************* #DEFINES **************************************************+*/

/*+************* CONSTANTS *************************************************+*/

/*+************* STRUCTURES ************************************************+*/

/*+************* VARIABLES *************************************************+*/

/*+************* FUNCTION PROTOTYPES ***************************************+*/

/**
 * This function checks if the date entered by the user is valid.
 *
 *
 * \param inputDate The input date structure
 *
 * \return 1 if the input date is valid, 0 otherwise
 */
int utilsCheckDate(date_t *inputDate)
{
  int isDateCorrect = 1;

  if (inputDate->year == 0)
  {
    isDateCorrect = 0;
  }

  // month must be between 1 and 12
  if ((inputDate->month < 1) || (inputDate->month > 12))
  {
    isDateCorrect = 0;
  }

  // day must be between 1 and 31
  if ((inputDate->day < 1) || (inputDate->day > 31))
  {
    isDateCorrect = 0;
  }
  else
  {
    // Check month with 28, 29, 30 and 31 days
    switch (inputDate->month)
    {
    case 2: //special treatment for February
      if (inputDate->day > 29)
      {
        isDateCorrect = 0;
      }
      else
      {
        // We simplify leap year treatment in considering multiple of 4 as leap year
        if ((inputDate->year % 4) == 0)
        {
          if (inputDate->day > 29)
          {
            isDateCorrect = 0;
          }
        }
        else
        {
          if (inputDate->day > 28)
          {
            isDateCorrect = 0;
          }
        }
      }
      break;

    case 4:
    case 6:
    case 9:
    case 11:
      //months with 30 days
      if (inputDate->day > 30)
      {
        isDateCorrect = 0;
      }
      break;
    }
  }

  return isDateCorrect;
}
