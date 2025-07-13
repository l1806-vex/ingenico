/*
 * OEM C  C30 interfaces 
 */ 
 
#ifndef _OEM_C30_DEPRECATED_H
#define _OEM_C30_DEPRECATED_H

#include "oem_buzzerC30.h"
#include "oem_ledsC30.h"
#include "oem_retroeclairageC30.h"
#include "oem_cless.h"


#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated C30_Mount is obsolete. You have to TPass library */
#define C30_Mount(a) ERROR_Deprecation_For_Function_C30_Mount_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated C30_Mount is obsolete. You have to TPass library */
int C30_Mount(char* lien) MACRO_DEPRECATED;

#endif


#endif

