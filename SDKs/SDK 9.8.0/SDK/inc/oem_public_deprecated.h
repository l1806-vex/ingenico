
/*! @addtogroup KSFAM_DEPRECATED
	* @{
 */

#ifndef OEM_PUBLIC_DEPRECATED_H
#define OEM_PUBLIC_DEPRECATED_H

#ifndef _DEPRECATED_TRAP_SDK96_

/*! @deprecated OS_rtc_EnterRegion is obsolete. You have to remove the call of it in your code, this function is without effect in Telium range of product */
#define OS_rtc_EnterRegion() ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK96_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated OS_rtc_EnterRegion is obsolete. You have to remove the call of it in your code, this function is without effect in Telium range of product */
void OS_rtc_EnterRegion(void) MACRO_DEPRECATED;

#endif


#ifndef _DEPRECATED_TRAP_SDK96_

/*! @deprecated OS_rtc_LeaveRegion is obsolete. You have to remove the call of it in your code, this function is without effect in Telium range of product */
#define OS_rtc_LeaveRegion() ERROR_Deprecation_For_Module_Trap_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK96_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated OS_rtc_LeaveRegion is obsolete. You have to remove the call of it in your code, this function is without effect in Telium range of product */
void OS_rtc_LeaveRegion(void) MACRO_DEPRECATED;

#endif

#endif

 /* @}  */
