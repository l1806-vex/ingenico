/*
 * OEM C  CAD30VR interfaces 
 */ 
 
#ifndef _OEM_CAD30USR_DEPRECATED_H
#define _OEM_CAD30USR_DEPRECATED_H
 
#include "oem_buzzer_peri.h"
#include "oem_leds_peri.h"
#include "oem_retroeclairage_peri.h"
#include "oem_cless.h"


#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated CAD30VR_Mount is obsolete. You have to use TCADV library */
#define CAD30VR_Mount(a) ERROR_Deprecation_For_Function_CAD30VR_Mount_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated CAD30VR_Mount is obsolete. You have to use TCADV library */
int CAD30VR_Mount(char* lien) MACRO_DEPRECATED;

#endif


#endif

