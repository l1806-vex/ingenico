// $Id: OSL_Dll.h,v 1.1.2.10 2013/03/22 14:43:41 nthibert Exp $
// This module allows the management of dll
#ifndef OSL_Dll__h_INCLUDED
#define OSL_Dll__h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

// ****************************************************************************
/// @addtogroup OSLayer
/// @{
/// @addtogroup Dll Dll
/// @{

// ****************************************************************************

/** @addtogroup DllDoc Documentation
	@{

	This module allows the use of Dll. You can open a Dll with @ref OSL_Dll_Open then get a function address
	either by name with @ref OSL_Dll_GetSymbolByName or by id with @ref OSL_Dll_GetSymbolById.
	Id method is provided in the new Dll to reduce size of stubs and dll to not keep function names.
	When dll is no more needed you can unload it with @ref OSL_Dll_Close

	This module deals with legacy T2 dlls and new T+ dll.
	New Dll (called as T+ dll) don't share local data like in legacy Dll. Local Dll data are initialized per process.
	You have to use another IPC mechanism (like @ref SharedMemory) to pass datas from one process/application to another.

	New T+ Dlls :
	As mentioned above these Dll don't share local datas accross process. Local datas are initialised automatically when the
	Dll will be used, no more need to call InitVar
	If you need to add a function called on the load or the unload of the dll by a process use the following syntax for GCC :

	This one is called on the first load of the dll :
	@code
		void onLoad (void) __attribute__((constructor));
	@endcode
	This one is called when a process unload the dll :
	@code
		void onUnload (void) __attribute__((destructor));
	@endcode


	In order to retrieve function from Dll you must implement the following function :

	This one shall return a function pointer passing the function name (this function is provided for compatibility and can return always NULL)
	@code
		extern void* GetProcAddress(const char* name);
	@endcode

	You can also declare the function (optional), which shall return the function pointer according to the function id :
	@code
		extern void* GetProcAddressById(unsigned long id);
	@endcode


	@}
*/

/** Dll Handle */
typedef struct T_OSL_DLL * T_OSL_HDLL;

/** Open a dll
@param dllName : family name of the dll
@return handle of a dll or NULL if error */
T_OSL_HDLL OSL_Dll_Open(const char *dllName);

/** Open a dll by its application type
@param appliType : appli type of the dll
@return handle of a dll or NULL if error */
T_OSL_HDLL OSL_Dll_OpenByAppliType(unsigned long appliType);

/** Check the presence of a dll
@param dllName : family name of the dll
@return presence of the dll (0 is for missing other for present)*/
short OSL_Dll_IsPresent(const char *dllName);

/** Returns the address of a symbol in a dll
@param dll : dll handle to get symbol from
@param symId : Id of the symbol to look for
@return pointer to the function*/
const void *OSL_Dll_GetSymbolById(T_OSL_HDLL dll, unsigned long symId);

/** Returns the address of a symbol in a dll
@param dll : dll handle to get symbol from
@param symName : Name of the symbol to look for
@return pointer to the function*/
const void *OSL_Dll_GetSymbolByName(T_OSL_HDLL dll, const char *symName);

/** Close a dll
@param dll : name of the dll to close
@return */
void OSL_Dll_Close(T_OSL_HDLL dll);

#if defined(WIN32)/** @cond OSL_Dll_Ignore */

typedef void * (*T_OSL_DLL_GETPROCADDRESS)(unsigned int );

#define OSL_DLL_MAX 100 //< Maximal quantity of dll used (reserved only for WIN32)
/** Register the getProcAddress callback (reserved only for WIN32)
@param dllName : name of the dll
@param getProcAddress : call back address */
void OSL_Dll_Register(const char * dllName, T_OSL_DLL_GETPROCADDRESS getProcAddress);

/** Unregister the getProcAddress callback (reserved only for WIN32)
@param dllName : name of the dll */
void OSL_Dll_Unregister(const char * dllName);

#endif /** @endcond */

/// @}
/// @}
#ifdef __cplusplus
}
#endif
#endif // OSL_Dll__h_INCLUDED
