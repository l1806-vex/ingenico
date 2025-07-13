/*! @addtogroup KSFAM_FFMS
	* @{
 */ 

#ifndef _FLASHMANAGER_DEPRECATED_H
#define _FLASHMANAGER_DEPRECATED_H

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated PersistentDataUpdate is obsolete. You have to use file system to save data */
#define PersistentDataUpdate(a) ERROR_Deprecation_For_Function_PersistentDataUpdate_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated PersistentDataUpdate is obsolete. You have to use file system to save data */
void PersistentDataUpdate(void *adr) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated RegisterPowerFailure is obsolete. You have to use file system to save data */
#define RegisterPowerFailure(a,b,c) ERROR_Deprecation_For_Function_RegisterPowerFailure_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated RegisterPowerFailure is obsolete. You have to use file system to save data */
unsigned int RegisterPowerFailure(char * Label,unsigned char * ptr,unsigned short size_p) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated UnregisterPowerFailure is obsolete. You have to use file system to save data */
#define UnregisterPowerFailure(a) ERROR_Deprecation_For_Function_UnregisterPowerFailure_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated UnregisterPowerFailure is obsolete. You have to use file system to save data */
unsigned int UnregisterPowerFailure(char *Label) MACRO_DEPRECATED;

#endif


#endif

/*! @}  */ 


