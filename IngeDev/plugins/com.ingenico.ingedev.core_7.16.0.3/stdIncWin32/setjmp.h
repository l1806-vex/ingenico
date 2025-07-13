/*****************************************************************************
 *+
 *  PROJECT        :    MILLENNIUM SOFTWARE
 *  MODULE         :    Incarm
 *  FILEMANE       :    setjmp.h
 *  PURPOSE        :
 *
 *  HISTORY
 *
 *  date         author     modifications
 *  2004-07-07   SGU0141    Merged GNU header into ARM with options recognized by compilers.
 *  2004-07-27   SGU0146    CBN simplified the code compliant ARM and GNU and
 *                           removed some useless symbols and comments.
 *  2006-04-03   CBN0014    Add the WIN32 support for U32 simulation. 
 *
 * --------------------------------------------------------------------------
 *  DESCRIPTION    :    -
-*/

#ifndef __SETJMP_H
#define __SETJMP_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
typedef int jmp_buf[16];

int __cdecl _setjmp (jmp_buf);

#define	setjmp(x)	_setjmp(x)

void __cdecl longjmp (jmp_buf, int) __attribute__ ((__noreturn__));

#else /* !WIN32 */
typedef int   jmp_buf[23];

extern int    setjmp(jmp_buf);
extern void   longjmp(jmp_buf, int);
#endif /* WIN32 */

#ifdef __cplusplus
}
#endif

#endif /*__SETJMP_H */

/* end of setjmp.h */
