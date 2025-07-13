// $Id: OSL_Mutex.h,v 1.1.2.5 2013/03/19 13:49:42 nthibert Exp $
// This module allows the management of mutex
#ifndef OSL_Mutex__h_INCLUDED
#define OSL_Mutex__h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

// ****************************************************************************
/// @addtogroup OSLayer
/// @{
/// @addtogroup Mutex Mutex
/// @{

// ****************************************************************************

/** @addtogroup MutexDoc Documentation
	@{

	This module lets you create mutex. Mutex can be entered multiple times by the same thread with no deadlock and is 
	really released	when the owner thread leaves the mutex the same number of time it enters it. After that, another 
	thread can enter a mutex.

	@}
*/

/** Mutex Handle */
typedef struct T_OSL_MUTEX * T_OSL_HMUTEX;

/** Create a mutex object
@param owned if 0 indicates that mutex is not owned by creator other that it's taken
@param sec security attributes, optional
@return handle of a mutex or NULL if error */
T_OSL_HMUTEX OSL_Mutex_Create(short owned, T_OSL_HSECURITY sec);

/** Destroy mutex object
@param mutex handle to destroy */
void OSL_Mutex_Destroy(T_OSL_HMUTEX mutex);

/** Take the mutex if possible or wait timeout
@param mutex handle to access
@param timeout to wait in ms (OSL_ERROR_TIMEOUT_INFINITE to wait indefinitely)
@return T_OSL_ERROR error */
T_OSL_ERROR OSL_Mutex_Lock(T_OSL_HMUTEX mutex, unsigned long timeout);

/** Release the mutex to let access to other process
@param mutex handle to access */
void OSL_Mutex_Unlock(T_OSL_HMUTEX mutex);



/// @}
/// @}
#ifdef __cplusplus
}
#endif
#endif // OSL_Mutex__h_INCLUDED
