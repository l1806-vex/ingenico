#ifndef MACRO_DEPRECATED
#if defined(__GNUC__)
#define MACRO_DEPRECATED __attribute__ ((deprecated))
#else
#define MACRO_DEPRECATED
#endif
#endif
