// $Id: OSL_Error.h,v 1.1.2.3 2013/01/21 10:38:08 nthibert Exp $
// This module describe the OS layer errors
#ifndef OSL_Error_h_INCLUDED
#define OSL_Error_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

// ****************************************************************************
/// @addtogroup OSLayer
/// @{
/// @addtogroup Error Error
/// @{
// ****************************************************************************

/** System error enumeration */
typedef enum T_OSL_ERROR
{
	OSL_SUCCESS = 0,		///< No error
	OSL_ERROR_TIMEOUT,		///< Timeout
	OSL_ERROR_BUSY,			///< Resource is busy
	OSL_ERROR_INVARG,		///< Invalid argument
	OSL_ERROR_FAILED,		///< Failed to perform operation
	OSL_ERROR_SEMAPHORE,	///< Error on semaphore
	OSL_ERROR_MUTEX,			///< Error on mutex
	OSL_ERROR_UNDEF			///< Undefined error
}T_OSL_ERROR;
	
/// @}
/// @}
#ifdef __cplusplus
}
#endif
#endif // OSL_Error_h_INCLUDED
