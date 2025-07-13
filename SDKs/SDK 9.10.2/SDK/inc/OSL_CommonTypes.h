// $Id: OSL_CommonTypes.h,v 1.1.2.4 2013/03/19 13:41:08 nthibert Exp $
// This module defines general types
#ifndef OS_CommonTypes_h_INCLUDED
#define OS_CommonTypes_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif

#define OSL_TIMEOUT_INFINITE (unsigned long)(-1)

typedef enum {
	OSL_OPEN_CREATE,
	OSL_OPEN_EXISTING
}T_OSL_OPEN_MODE;


#ifdef __cplusplus
}
#endif
#endif // OS_CommonTypes_h_INCLUDED
