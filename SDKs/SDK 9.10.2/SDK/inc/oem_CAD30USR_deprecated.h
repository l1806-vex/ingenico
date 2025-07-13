/*
 * OEM C  CAD30USR interfaces 
 */ 
 
#ifndef _OEM_CAD30USR_DEPRECATED_H
#define _OEM_CAD30USR_DEPRECATED_H
 
#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated CAD30USR_Mount is obsolete. You have to use CAD30USR library */
#define CAD30USR_Mount(a) ERROR_Deprecation_For_Function_CAD30USR_Mount_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated CAD30USR_Mount is obsolete. You have to use CAD30USR library */
int CAD30USR_Mount(char* lien) MACRO_DEPRECATED;

#endif


#endif

