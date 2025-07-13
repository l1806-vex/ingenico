/*! @addtogroup KSFAM_OS_KERNEL
	* @{
 */ 

#ifndef _XECARM_DEPRECATED_H
#define _XECARM_DEPRECATED_H

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated OS_rtc_StartTask is obsolete. You have to remove the call of it in your code */
#define OS_rtc_StartTask(a) ERROR_Deprecation_For_Function_OS_rtc_StartTask_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated OS_rtc_StartTask is obsolete. You have to remove the call of it in your code */
tStatus OS_rtc_StartTask(Word TaskNumber) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated OS_rtc_StopTask is obsolete. You have to remove the call of it in your code */
#define OS_rtc_StopTask(a) ERROR_Deprecation_For_Function_OS_rtc_StopTask_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated OS_rtc_StopTask is obsolete. You have to remove the call of it in your code */
tStatus OS_rtc_StopTask(Word TaskNumber) MACRO_DEPRECATED;

#endif


#endif

/*! @}  */ 
