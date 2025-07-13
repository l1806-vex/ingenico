// $Id: OSL_SharedMem.h,v 1.1.2.6 2013/03/19 13:49:42 nthibert Exp $
// This module allows the management of shared memory
#ifndef OSL_SharedMem_h_INCLUDED
#define OSL_SharedMem_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

// ****************************************************************************
/// @addtogroup OSLayer
/// @{
/// @addtogroup SharedMemory SharedMemory
/// @{

// ****************************************************************************

/** @addtogroup sharedMemDoc Documentation
	@{
	
	This module lets you create shared memory. Shared memory is a chunk of memory that can
	be shared between several processes using a common name.
	
	@}
	*/

/** Shared memory Handle */
typedef struct T_OSL_SHARED_MEM * T_OSL_HSHARED_MEM;

/** Create or open a new shared memory object
@param name of the shared memory, optional
@param size of the object to create, discarded in open mode (can be 0 in this case)
@param mode openning mode of the shared memory
@param sec security attributes, optional
@return handle of a shared memory or NULL if error */
T_OSL_HSHARED_MEM OSL_SharedMem_Create(const char *name, unsigned long size, T_OSL_OPEN_MODE mode, T_OSL_HSECURITY sec);

/** Release reference on the shared memory object. When all references on a shared memory are released memory is desroyed
If the creator of the named shared memory destroy it, the name will no more be accessible with open (but if other reference
are still opened on the shared memory they are not lost)
@param sharedMemory handle to release */
void OSL_SharedMem_Destroy(T_OSL_HSHARED_MEM sharedMemory);

/** Return a pointer to the shared memory
@param sharedMemory handle
@return address of the shared memory */
void* OSL_SharedMem_GetPointer(T_OSL_HSHARED_MEM sharedMemory);

/** Return the size of the shared memory block
@param sharedMemory handle
@return size of the shared memory block */
unsigned long OSL_SharedMem_GetSize(T_OSL_HSHARED_MEM sharedMemory);


/// @}
/// @}
#ifdef __cplusplus
}
#endif
#endif // OSL_SharedMem_h_INCLUDED
