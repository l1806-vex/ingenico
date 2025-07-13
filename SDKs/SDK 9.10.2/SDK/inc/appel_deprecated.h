
#ifdef __cplusplus
extern "C" {
#endif

#ifndef APPEL_DEPRECATED_H
#define APPEL_DEPRECATED_H
/*! @addtogroup KSFAM_M2OS
	* @{
**/


// appel.h

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should call directly the system object API: use field "name" returned by function ObjectGetInfo
 *
 * @brief This function returns the name of the application
 * @param no_appli : rank of the application
 * @return The last eight characters of the application family of the application. 
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 99) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
#ifndef _DEPRECATED_MANAGER_SDK980_
#define Get_AppliName ERROR_Deprecation_For_Function_Get_AppliName_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern char          *Get_AppliName(NO_SEGMENT no_appli) MACRO_DEPRECATED;
#endif


/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should call directly the system object API: use field "object_type" returned by function ObjectGetInfo
 *
 * @brief This function returns the name of the application.
 * - OBJECT_TYPE_APPLI	 = 1,
 * - OBJECT_TYPE_DLL	   = 2,
 * - OBJECT_TYPE_DRIVER = 3,
 * - OBJECT_TYPE_PARAM  = 4,
 * - OBJECT_TYPE_KEY    = 5
 * @param no_appli : rank of the application during the loading.
 * @return object type.
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
#ifndef _DEPRECATED_MANAGER_SDK980_
#define Get_ObjectType ERROR_Deprecation_For_Function_Get_ObjectType_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int 			  Get_ObjectType(NO_SEGMENT no_appli) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should call directly the system object API: use field "application_type" returned by function ObjectGetInfo
 *
 * @brief This function returns the type of the application, defined in the ADF file.
 * @param no_appli : rank of the application during the loading.
 * @return application type.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 4) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
#ifndef _DEPRECATED_MANAGER_SDK980_
#define Get_TypeCode ERROR_Deprecation_For_Function_Get_TypeCode_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int            Get_TypeCode(NO_SEGMENT no_appli) MACRO_DEPRECATED;
#endif


/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should call directly the system object API: use field "file_name" returned by function ObjectGetInfo
 *
 * @brief This function returns the name and the version of the application
 * @param no_appli : rank of the application
 * @return The last eight characters of the primary file name of the  application. 
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 111) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
#ifndef _DEPRECATED_MANAGER_SDK980_
#define Get_FileName ERROR_Deprecation_For_Function_Get_FileName_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern char          *Get_FileName(NO_SEGMENT no_appli) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should call directly the system object API: use field "crc" returned by function ObjectGetInfo
 *
 * @brief This function returns the crc of an application
 * @param no_appli : rank of an application
 * @return Crc of the application.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 100) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
#ifndef _DEPRECATED_MANAGER_SDK980_
#define Get_AppliCrc ERROR_Deprecation_For_Function_Get_AppliCrc_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern unsigned short Get_AppliCrc(NO_SEGMENT no_appli) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should call directly the system object API: use field "application_type" returned by function ObjectGetInfo
 *
 * @brief This function retrieves application number providing application type.
 * @param type : application type ( range to be defined ).
 * @return
 * - application number as an integer
 * - -1 if application not present.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 5) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
#ifndef _DEPRECATED_MANAGER_SDK980_
#define Get_Appli_Number ERROR_Deprecation_For_Function_Get_Appli_Number_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int            Get_Appli_Number(int type) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The function always returns 0x200000.
 *
 * @brief This function returns the address of the beginning of an application's data.
 * @param no_appli : rank of the application during the loading
 * @return Address of the beginning of the data.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 101) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
#ifndef _DEPRECATED_MANAGER_SDK980_
#define Get_AppliData ERROR_Deprecation_For_Function_Get_AppliData_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern char          *Get_AppliData(NO_SEGMENT no_appli) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The function always returns 0.
 *
 * @brief This function returns the adress of the beginning of the application's code given as input parameter.
 * @param no_appli : rank of the application during the loading.
 * @return Address of the beginning of the application's code.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 108) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
#ifndef _DEPRECATED_MANAGER_SDK980_
#define Get_AppliCode ERROR_Deprecation_For_Function_Get_AppliCode_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int            Get_AppliCode(NO_SEGMENT no_appli) MACRO_DEPRECATED;
#endif

/*!
 * @deprecated To continue to use this function, define _DEPRECATED_MANAGER_SDK980_ in your application.
 *  The application should call directly the system object API: use function ObjectGetNumber(OBJECT_TYPE_APPLI)
 *
 * @brief This function returns the number of applications loaded in the terminal
 * @return Number of applications.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 73) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
#ifndef _DEPRECATED_MANAGER_SDK980_
#define Get_Nb_Segment ERROR_Deprecation_For_Function_Get_Nb_Segment_For_Module_Manager_SeeDocumentation_In_CHM_File;
#else
extern int            Get_Nb_Segment(void) MACRO_DEPRECATED;
#endif

/*! @} **/

#endif /* APPEL_DEPRECATED_H */

#ifdef __cplusplus
}
#endif
