/*****************************************************************************
 *+
 *  PROJECT        :    MILLENNIUM SOFTWARE
 *  MODULE         :    Incarm
 *  FILEMANE       :    stdarg.h
 *  PURPOSE        :
 *
 *  HISTORY
 *
 *  date         author     modifications
 *  2004-07-07   SGU0141    Merged GNU header into ARM with options recognized by compilers.
 *  2004-07-27   SGU0146    CBN simplified the code compliant ARM and GNU and
 *                           removed some useless symbols and comments.
 *  2006-04-03   CBN0014    Add the WIN32 macros definition for U32 simulation. 
 *                          Add missing parenthesis in "__alignuptotype" macro 
 *                           to avoid warnings.
 *
 * --------------------------------------------------------------------------
 *  DESCRIPTION    :    -
-*/

#ifndef __STDARG_H
#define __STDARG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32

#ifndef _ANSI_STDARG_H_
#ifndef RC_INVOKED
#ifndef __need___va_list
#define _STDARG_H
#define _ANSI_STDARG_H_
#endif /* not __need___va_list */
#undef __need___va_list

/* Define __gnuc_va_list.  */

#ifndef __GNUC_VA_LIST
#define __GNUC_VA_LIST
typedef __builtin_va_list __gnuc_va_list;
#endif

/* Define the standard macros for the user,
   if this invocation was from the user program.  */
#ifdef _STDARG_H

#define va_start(v,l)	__builtin_va_start(v,l)
#define va_end(v)	__builtin_va_end(v)
#define va_arg(v,l)	__builtin_va_arg(v,l)
#if !defined(__STRICT_ANSI__) || __STDC_VERSION__ + 0 >= 199900L
#define va_copy(d,s)	__builtin_va_copy(d,s)
#endif
#define __va_copy(d,s)	__builtin_va_copy(d,s)

/* Define va_list, if desired, from __gnuc_va_list. */
/* We deliberately do not define va_list when called from
   stdio.h, because ANSI C says that stdio.h is not supposed to define
   va_list.  stdio.h needs to have access to that data type, 
   but must not use that name.  It should use the name __gnuc_va_list,
   which is safe because it is reserved for the implementation.  */

#ifdef _HIDDEN_VA_LIST  /* On OSF1, this means varargs.h is "half-loaded".  */
#undef _VA_LIST
#endif

#ifdef _BSD_VA_LIST
#undef _BSD_VA_LIST
#endif

#if defined(__svr4__) || (defined(_SCO_DS) && !defined(__VA_LIST))
/* SVR4.2 uses _VA_LIST for an internal alias for va_list,
   so we must avoid testing it and setting it here.
   SVR4 uses _VA_LIST as a flag in stdarg.h, but we should
   have no conflict with that.  */
#ifndef _VA_LIST_
#define _VA_LIST_
#ifdef __i860__
#ifndef _VA_LIST
#define _VA_LIST va_list
#endif
#endif /* __i860__ */
typedef __gnuc_va_list va_list;
#ifdef _SCO_DS
#define __VA_LIST
#endif
#endif /* _VA_LIST_ */
#else /* not __svr4__ || _SCO_DS */

/* The macro _VA_LIST_ is the same thing used by this file in Ultrix.
   But on BSD NET2 we must not test or define or undef it.
   (Note that the comments in NET 2's ansi.h
   are incorrect for _VA_LIST_--see stdio.h!)  */
#if !defined (_VA_LIST_) || defined (__BSD_NET2__) || defined (____386BSD____) || defined (__bsdi__) || defined (__sequent__) || defined (__FreeBSD__) || defined(WINNT)
/* The macro _VA_LIST_DEFINED is used in Windows NT 3.5  */
#ifndef _VA_LIST_DEFINED
/* The macro _VA_LIST is used in SCO Unix 3.2.  */
#ifndef _VA_LIST
/* The macro _VA_LIST_T_H is used in the Bull dpx2  */
#ifndef _VA_LIST_T_H
/* The macro __va_list__ is used by BeOS.  */
#ifndef __va_list__
typedef __gnuc_va_list va_list;
#endif /* not __va_list__ */
#endif /* not _VA_LIST_T_H */
#endif /* not _VA_LIST */
#endif /* not _VA_LIST_DEFINED */
#if !(defined (__BSD_NET2__) || defined (____386BSD____) || defined (__bsdi__) || defined (__sequent__) || defined (__FreeBSD__))
#define _VA_LIST_
#endif
#ifndef _VA_LIST
#define _VA_LIST
#endif
#ifndef _VA_LIST_DEFINED
#define _VA_LIST_DEFINED
#endif
#ifndef _VA_LIST_T_H
#define _VA_LIST_T_H
#endif
#ifndef __va_list__
#define __va_list__
#endif

#endif /* not _VA_LIST_, except on certain systems */

#endif /* not __svr4__ */

#endif /* _STDARG_H */

#endif /* not RC_INVOKED */
#endif /* not _ANSI_STDARG_H_ */

#else /* !WIN32 */

typedef char  *va_list[1];

#ifdef __GNUC__
#define ___type
#endif /* __GNUC__ */

#define       __alignof(type) \
              ((char *)&(((struct{char __member1; \
              ___type type __member2;}*) 0)->__member2) - \
              (char *)0)
    
#define       __alignuptotype(ptr,type) \
              ((char *)(((int)(ptr) + (__alignof(type)-1)) & ~(__alignof(type)-1)))

#ifdef __arm
#define       va_start(ap,parmN) \
              (___assert((___typeof(parmN) & 0x481) == 0, \
              "Illegal type of 2nd argument to va_start"), \
              (void)(*(ap) = (char *)&(parmN) + sizeof(parmN)))

#define       va_arg(ap,type) \
              (___assert((___typeof(___type type) & 0x481) == 0, \
              "Illegal type used with va_arg"), \
              *(___type type *)((*(ap)=__alignuptotype(*(ap),type)+sizeof(___type type))-\
              sizeof(___type type)))
#endif /* __arm */

#ifdef __GNUC__
#define       va_start(ap,parmN) \
              ((void)(*(ap) = (char *)&(parmN) + sizeof(parmN)))

#define       va_arg(ap,type) \
              (*(___type type *)((*(ap)=__alignuptotype(*(ap),type)+sizeof(___type type))-\
              sizeof(___type type)))
#endif /* __GNUC__ */

#define       va_end(ap) ((void)(*(ap) = (char *)-256))

#endif /* WIN32 */

#ifdef __cplusplus
}
#endif

#endif /*__STDARG_H */

/* end of stdarg.h */
