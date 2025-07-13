/*! @addtogroup KSFAM_MSGLIB
	* @{
	**/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MSGLIB_DEPRECATED_H
#define MSGLIB_DEPRECATED_H

/*! @addtogroup KSFAM_MSGLIB_MISCELLANOUS
 * @{
 */

/*!@deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use system object api instead: object_type field returned by function ObjectGetInfo for the current application
 *
 *! @brief Get the file type of the application
 * @return  : The file type of the application (1:appli,2:DLL,3:driver)
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 148) if function does not exist
 *
 * @link KSFAM_MSGLIB_MISCELLANOUS Back to top @endlink
 */
#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetFileType ERROR_Deprecation_For_Function_GetFileType_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int 	GetFileType(void) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should not call this function. Use system object api instead: application_type field returned by function ObjectGetInfo for the current application
 *
 * @brief Get the application type of the application
 * @return  : The application type of the application
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 149) if function does not exist
 *
 * @link KSFAM_MSGLIB_MISCELLANOUS Back to top @endlink
*/
#ifndef _DEPRECATED_MANAGER_SDK980_
#define GetAppliType ERROR_Deprecation_For_Function_GetAppliType_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int 	GetAppliType(void) MACRO_DEPRECATED;
#endif



/*! @} **/
#endif

/*! @} **/

#ifdef __cplusplus
}
#endif
