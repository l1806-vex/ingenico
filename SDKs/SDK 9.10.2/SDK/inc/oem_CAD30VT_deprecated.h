/*
 * OEM C  CAD30VT interfaces 
 */ 
 
#ifndef _OEM_CAD30VT_DEPRECATED_H
#define _OEM_CAD30VT_DEPRECATED_H
 
#include "oem_buzzerC30.h"
#include "oem_ledsC30.h"
#include "oem_retroeclairageC30.h"
#include "oem_cless.h"


#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated CAD30VT_Mount is obsolete. You have to use TPass library */
#define CAD30VT_Mount(a) ERROR_Deprecation_For_Function_CAD30VT_Mount_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated CAD30VT_Mount is obsolete. You have to use TPass library */
int CAD30VT_Mount(char* lien) MACRO_DEPRECATED;

#endif


#endif

