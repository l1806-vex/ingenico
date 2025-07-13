// $Id: OSL_Security.h,v 1.1.2.3 2013/03/19 13:41:08 nthibert Exp $
// This module implements a memory pool
#ifndef OSL_Security_h_INCLUDED
#define OSL_Security_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif

// ****************************************************************************
/**
@addtogroup OSLayer
@{
@addtogroup Security Security
@{
	
@addtogroup SecurityDoc Documentation
@{
  To be developped to use the security from application
@}
*/
	
// ****************************************************************************


/** Security object handle */
typedef struct T_OSL_SECURITY * T_OSL_HSECURITY;

/** the created object can be used only in the same process */
#define OSL_SECURITY_LOCAL  ((T_OSL_HSECURITY)0)
/** the created object can be shared between processes */
#define OSL_SECURITY_SHARED ((T_OSL_HSECURITY)4)

/// @}
/// @}

#ifdef __cplusplus
}
#endif

#endif // OSL_Security_h_INCLUDED
