/*! @addtogroup KSFAM_DEPRECATED
	* @{
 */

#ifndef _LOADERAPI_DEPRECATED_H_
#define _LOADERAPI_DEPRECATED_H_

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated DllGetId is obsolete. You have to use OS Layer API */
#define DllGetId(a,b) ERROR_Deprecation_For_Function_DllGetId_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated DllGetId is obsolete. You have to use OS Layer API */
int DllGetId(char *name,int *id) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated DllLink is obsolete. You have to use OS Layer API */
#define DllLink(a) ERROR_Deprecation_For_Function_DllLink_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated DllLink is obsolete. You have to use OS Layer API */
void *DllLink(char *name) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated DllLinkByType is obsolete. You have to use OS Layer API */
#define DllLinkByType(a) ERROR_Deprecation_For_Function_DllLinkByType_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated DllLinkByType is obsolete. You have to use OS Layer API */
void *DllLinkByType(unsigned short application_type) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated DllUnlink is obsolete. You have to use OS Layer API */
#define DllUnlink(a) ERROR_Deprecation_For_Function_DllUnlink_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated DllUnlink is obsolete. You have to use OS Layer API */
int DllUnlink(char *name) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated DllUnlinkByType is obsolete. You have to use OS Layer API */
#define DllUnlinkByType(a) ERROR_Deprecation_For_Function_DllUnlinkByType_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated DllUnlinkByType is obsolete. You have to use OS Layer API */
int DllUnlinkByType(unsigned short application_type) MACRO_DEPRECATED;

#endif


#endif

/*! @}  */ 
