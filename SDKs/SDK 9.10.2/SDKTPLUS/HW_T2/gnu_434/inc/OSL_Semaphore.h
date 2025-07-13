// $Id: OSL_Semaphore.h,v 1.1.2.7 2013/03/19 13:49:42 nthibert Exp $
// This module allows the management of semaphore
#ifndef OSL_Semaphore__h_INCLUDED
#define OSL_Semaphore__h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

// ****************************************************************************
/// @addtogroup OSLayer
/// @{
/// @addtogroup Semaphore Semaphore
/// @{

// ****************************************************************************

/** @addtogroup semaphoreDoc Documentation
	@{

	This module lets you create semaphore.

	@}
	*/

/** semaphore Handle */
typedef struct T_OSL_SEMAPHORE * T_OSL_HSEMAPHORE;

/** Create or open a new semaphore object
@param name of the semaphore, optional
@param value of the object >=0
@param mode openning mode of the semaphore
@param sec security attributes, optional
@return handle of a semaphore or NULL if error */
T_OSL_HSEMAPHORE OSL_Semaphore_Create(const char *name, unsigned long value, T_OSL_OPEN_MODE mode, T_OSL_HSECURITY sec);

/** Release reference on the semaphore object. When all references on a semaphore are released sempahore is desroyed
If the creator of the named semaphore destroy it, the name will no more be accessible with open (but if other reference
are still opened on the semaphore they are not lost)
@param semaphore handle to release */
void OSL_Semaphore_Destroy(T_OSL_HSEMAPHORE semaphore);

/** Take a semaphore unit if possible or wait timeout  to get access
@param semaphore handle to get a unit
@param timeout to wait in ms (OSL_TIMEOUT_INFINITE to wait indefinitely)
@return T_OSL_ERROR error */
T_OSL_ERROR OSL_Semaphore_Acquire(T_OSL_HSEMAPHORE semaphore, unsigned long timeout);

/** Release a semaphore unit
@param semaphore handle to release a unit */
void OSL_Semaphore_Release(T_OSL_HSEMAPHORE semaphore);



/// @}
/// @}
#ifdef __cplusplus
}
#endif
#endif // OSL_Semaphore__h_INCLUDED
