/*****************************************************************************
 *+
 *  PROJECT        :    MILLENNIUM SOFTWARE
 *  MODULE         :    Incarm
 *  FILEMANE       :    stdio.h
 *  PURPOSE        :
 *
 *  HISTORY
 *
 *  date         author     modifications
 *  2001-04-19   CAU        Modif keep only the necessary functions FOR ARM.
 *  2004-06-23   CBN/SGU    Added sscanf and vsprintf in ARM ANSI C header FOR ARM.
 *  2004-07-02   SGU0140    Merged into main trunk (ARM).
 *  2004-07-07   SGU0141    Added GNU include.
 *  2004-07-27   SGU0146    CBN simplified the code compliant ARM and GNU and
 *                           removed some useless symbols and comments.
 *  2004-08-03   CBN        Bad 3rd parameter for vsprintf, must be set to
 *                           __va_list.
 *  2006-04-03   CBN0014    va_list is declared in "stdarg.h" header file (don't
 *                           redefine it in this file, just include header file).
 *
 * --------------------------------------------------------------------------
 *  DESCRIPTION    :    -
-*/

#ifndef __STDIO_H
#define __STDIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

extern int    sprintf(char * , const char * , ...);
extern int    sscanf(const char * , const char * , ...);
extern int    vsprintf(char * , const char * , va_list);

#ifdef __cplusplus
}
#endif

#endif /*__STDIO_H */

/* end of stdio.h */
