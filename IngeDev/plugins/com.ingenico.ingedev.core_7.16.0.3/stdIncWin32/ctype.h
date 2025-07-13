/*****************************************************************************
 *+
 *  PROJECT        :    MILLENNIUM SOFTWARE
 *  MODULE         :    Incarm
 *  FILEMANE       :    ctype.h
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

#ifndef __CTYPE_H
#define __CTYPE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32

int __cdecl isalnum(int);
int __cdecl isalpha(int);
int __cdecl iscntrl(int);
int __cdecl isdigit(int);
int __cdecl isgraph(int);
int __cdecl islower(int);
int __cdecl isprint(int);
int __cdecl ispunct(int);
int __cdecl isspace(int);
int __cdecl isupper(int);
int __cdecl isxdigit(int);
int __cdecl tolower(int);
int __cdecl toupper(int);

#else /* !WIN32 */

extern int (isalnum) (int c);
extern int (isalpha) (int c);
extern int (iscntrl) (int c);
extern int (isdigit) (int c);
extern int (isgraph) (int c);
extern int (islower) (int c);
extern int (isprint) (int c);
extern int (ispunct) (int c);
extern int (isspace) (int c);
extern int (isupper) (int c);
extern int (isxdigit)(int c);
extern int tolower   (int c);
extern int toupper   (int c);

#endif /* WIN32 */

#ifdef __arm

/* __ctype is defined in ARM C library */
extern unsigned char __ctype[];

#define __S 1 
#define __P 2 
#define __B 4 
#define __L 8 
#define __U 16
#define __N 32
#define __C 64
#define __X 128

#define isalnum(c)  (__ctype[c] & (__U+__L+__N))
#define isalpha(c)  (__ctype[c] & (__U+__L))
#define iscntrl(c)  (__ctype[c] & __C)
#define isdigit(c)  (__ctype[c] & __N)
#define isgraph(c)  (__ctype[c] & (__L+__U+__N+__P))
#define islower(c)  (__ctype[c] & __L)
#define isprint(c)  (__ctype[c] & (__L+__U+__N+__P+__B))
#define ispunct(c)  (__ctype[c] & __P)
#define isspace(c)  (__ctype[c] & __S)
#define isupper(c)  (__ctype[c] & __U)
#define isxdigit(c) (__ctype[c] & (__N+__X))

#endif /* __arm */

#ifdef __GNUC__

#ifdef WIN32

extern unsigned short _ctype[];

/*
 * The following flags are used to tell iswctype and _isctype what character
 * types you are looking for.
 */
#define	_UPPER		0x0001
#define	_LOWER		0x0002
#define	_DIGIT		0x0004
#define	_SPACE		0x0008 /* HT  LF  VT  FF  CR  SP */
#define	_PUNCT		0x0010
#define	_CONTROL	0x0020
#define	_BLANK		0x0040 /* this is SP only, not SP and HT as in C99  */
#define	_HEX	  	0x0080
#define	_ALPHA		0x0103

#ifdef __cplusplus
#define __CRT_INLINE inline
#else
#define __CRT_INLINE extern __inline__
#endif

#define __ISCTYPE(c, mask)  (_ctype[c] & mask)
__CRT_INLINE int __cdecl isalnum(int c) {return __ISCTYPE(c, (_ALPHA|_DIGIT));}
__CRT_INLINE int __cdecl isalpha(int c) {return __ISCTYPE(c, _ALPHA);}
__CRT_INLINE int __cdecl iscntrl(int c) {return __ISCTYPE(c, _CONTROL);}
__CRT_INLINE int __cdecl isdigit(int c) {return __ISCTYPE(c, _DIGIT);}
__CRT_INLINE int __cdecl isgraph(int c) {return __ISCTYPE(c, (_PUNCT|_ALPHA|_DIGIT));}
__CRT_INLINE int __cdecl islower(int c) {return __ISCTYPE(c, _LOWER);}
__CRT_INLINE int __cdecl isprint(int c) {return __ISCTYPE(c, (_BLANK|_PUNCT|_ALPHA|_DIGIT));}
__CRT_INLINE int __cdecl ispunct(int c) {return __ISCTYPE(c, _PUNCT);}
__CRT_INLINE int __cdecl isspace(int c) {return __ISCTYPE(c, _SPACE);}
__CRT_INLINE int __cdecl isupper(int c) {return __ISCTYPE(c, _UPPER);}
__CRT_INLINE int __cdecl isxdigit(int c) {return __ISCTYPE(c, _HEX);}

#else /* !WIN32 */

/* _ctype_ is defined in GNU C library */
extern const char _ctype_[];

#define _U  01
#define _L  02
#define _N  04
#define _S  010
#define _P  020
#define _C  040
#define _X  0100
#define _B  0200

/* WARNING: with GCC in case of C++, macros are not used, 
   functions are called instead (these functions use the same defines) 
   !!! DON'T MODIFY THE VALUES OF THESE DEFINES !!!
   ARM compiler calls only macros for C or C++ code */
#ifndef __cplusplus
#define isalpha(c)  ((_ctype_+1)[(unsigned)(c)]&(_U|_L))
#define isupper(c)  ((_ctype_+1)[(unsigned)(c)]&_U)
#define islower(c)  ((_ctype_+1)[(unsigned)(c)]&_L)
#define isdigit(c)  ((_ctype_+1)[(unsigned)(c)]&_N)
#define isxdigit(c) ((_ctype_+1)[(unsigned)(c)]&(_X|_N))
#define isspace(c)  ((_ctype_+1)[(unsigned)(c)]&_S)
#define ispunct(c)  ((_ctype_+1)[(unsigned)(c)]&_P)
#define isalnum(c)  ((_ctype_+1)[(unsigned)(c)]&(_U|_L|_N))
#define isprint(c)  ((_ctype_+1)[(unsigned)(c)]&(_P|_U|_L|_N|_B))
#define isgraph(c)  ((_ctype_+1)[(unsigned)(c)]&(_P|_U|_L|_N))
#define iscntrl(c)  ((_ctype_+1)[(unsigned)(c)]&_C)
#endif /* !__cplusplus */

#endif /* WIN32 */
#endif /* __GNUC__ */

#ifdef __cplusplus
}
#endif

#endif /* __CTYPE_H */

/* end of ctype.h */
