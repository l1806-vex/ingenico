/*! @addtogroup KSFAM_OS
	* @{
 */ 
 
#ifndef __CALLHOST_DEPRECATED_H
#define __CALLHOST_DEPRECATED_H

//! \addtogroup CALLHOST_SAMPLE
//! @{
//! \include callhost_Sample_01.c
//! @}

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated CallHost is obsolete. You can use "remote_downloading" function if its capabilities fit your use cases. 
A new "CallHost" function will replace at mid term the existing one. It will better fit future download requirements and evolutions.
Its characteristics are currently under definition. */
#define CallHost(a,b,c) ERROR_Deprecation_For_Function_CallHost_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated CallHost is obsolete. You can use "remote_downloading" function if its capabilities fit your use cases. 
A new "CallHost" function will replace at mid term the existing one. It will better fit future download requirements and evolutions.
Its characteristics are currently under definition. */
int CallHost(char CallType, S_PARAM_SYSTEM_CALL *pt_ParamCall,long *PerformedActivity) MACRO_DEPRECATED;

#endif


#endif

/*! @}  */ 
