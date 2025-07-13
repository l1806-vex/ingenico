/**
 * Utils.h
 *
 * Header for the utilities source file.
 *
 */
#ifndef __UTILS_H
#define __UTILS_H

/*+************* #DEFINES **************************************************+*/

/*+************* CONSTANTS *************************************************+*/

/*+************* STRUCTURES ************************************************+*/
/**
 * Structure used to store the date entered by the user
 */
typedef struct
{
  int year;
  int month;
  int day;
} date_t;

/*+************* VARIABLES *************************************************+*/

/*+************* FUNCTION PROTOTYPES ***************************************+*/
extern int utilsCheckDate(date_t *inputDate);

#endif //__UTILS_H
