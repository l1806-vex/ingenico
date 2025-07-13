
/*! @addtogroup KSFAM_DEPRECATED
	* @{
 */

#ifndef OEM_PUBLIC_DEPRECATED_H
#define OEM_PUBLIC_DEPRECATED_H


#ifdef _DEPRECATED_TRAP_SDK091000_

#define SWP_FIOCTL_CONFIG_SWIPE		0x9000			/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_TRAP_SDK091000_ in your application. 
																		  @brief fioctl for ISO2 and ISO31 : select which swipe is activated 
                                                               parameter int : SWP_INTERNAL / SWP_PINPAD / SWP_BOTH */

#define SWP_FIOCTL_GET_USED_SWIPE	0x9001			/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_TRAP_SDK091000_ in your application. 
																		  @brief fioctl for ISO2 and ISO31 : gets which swipe is activated  
                                                               parameter int : SWP_INTERNAL / SWP_PINPAD */

#define SWP_INTERNAL	   0		/*!< fioctl SWP_FIOCTL_CONFIG_SWIPE : Internal Swipe used */
#define SWP_PINPAD		1		/*!< fioctl SWP_FIOCTL_CONFIG_SWIPE : PinPad swipe used */
#define SWP_BOTH			2		/*!< fioctl SWP_FIOCTL_CONFIG_SWIPE : Use internal and pinpad swipe */

#define SWP_FIOCTL_GET_USED_HEAD 0x9002			/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_TRAP_SDK091000_ in your application. 
																	  @brief fioctl for ISO2 and ISO31 : Get type of magnetic head
                                                            parameter typre int : SWP_NORMAL / SWP_MAGTEK */
                                                            
#define SWP_NORMAL   0		/*!< fioctl SWP_FIOCTL_GET_USED_HEAD : Normal head */
#define SWP_MAGTEK   1		/*!< fioctl SWP_FIOCTL_GET_USED_HEAD : MAGTEK head */

#endif // _DEPRECATED_TRAP_SDK091000_

/*
======================================================================
					Configuration couche rtc sur Osg/Nuc
======================================================================
*/

#define	OS_rtc_k_NbTask            150		/*!< Max number of tasks @deprecated */
#define	OS_rtc_k_NbMailBox   			 150		/*!< Max number of mailboxes @deprecated */
#define	OS_rtc_k_NbSema       		 150  	/*!< Max number of semaphores @deprecated */
#define	OS_rtc_k_NbDelay     				30		/*!< Max number of  delays @deprecated */
#define	OS_rtc_k_NbEnveloppe     		60		/*!< Max number of "enveloppes" @deprecated */


#ifndef _DEPRECATED_TRAP_SDK96_

/*! @deprecated OS_rtc_EnterRegion is obsolete. You have to remove the call of it in your code, this function is without effect in Telium range of product */
#define OS_rtc_EnterRegion() ERROR_Deprecation_For_Function_OS_rtc_EnterRegion_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK96_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated OS_rtc_EnterRegion is obsolete. You have to remove the call of it in your code, this function is without effect in Telium range of product */
void OS_rtc_EnterRegion(void) MACRO_DEPRECATED;

#endif


#ifndef _DEPRECATED_TRAP_SDK96_

/*! @deprecated OS_rtc_LeaveRegion is obsolete. You have to remove the call of it in your code, this function is without effect in Telium range of product */
#define OS_rtc_LeaveRegion() ERROR_Deprecation_For_Function_OS_rtc_LeaveRegion_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK96_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated OS_rtc_LeaveRegion is obsolete. You have to remove the call of it in your code, this function is without effect in Telium range of product */
void OS_rtc_LeaveRegion(void) MACRO_DEPRECATED;

#endif


#ifndef _DEPRECATED_ENCRIT_SDK90_
#define encrit ERROR_Deprecation_For_Function_encrit_For_encrit_SeeDocumentationFor_encrit_In_CHM_File;
/* This error is generated to warn you about the deprecation for encrit.
You have to remove the call of it in your code, this function is without effect in Telium range of product.
*/
#else
/*! @deprecated This function is obsolete. You have to remove the call of it in your code, this function is without effect in Telium range of product.
 */
extern void encrit(void) MACRO_DEPRECATED;
#endif



#ifndef _DEPRECATED_ENCRIT_SDK90_
#define excrit ERROR_Deprecation_For_Function_excrit_For_excrit_SeeDocumentationFor_excrit_In_CHM_File;
/* This error is generated to warn you about the deprecation for encrit.
You have to remove the call of it in your code, this function is without effect in Telium range of product.
*/
#else
/*! @deprecated This function is obsolete. You have to remove the call of it in your code, this function is without effect in Telium range of product.
 */
extern int excrit(void) MACRO_DEPRECATED;
#endif


#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated auto_repeat is obsolete. You have to use Goal function */
#define auto_repeat(a) ERROR_Deprecation_For_Function_auto_repeat_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated auto_repeat is obsolete. You have to use Goal function */
int auto_repeat(int key) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated CAMSPED_Mount is obsolete. You have to SPED library */
#define CAMSPED_Mount() ERROR_Deprecation_For_Function_CAMSPED_Mount_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated CAMSPED_Mount is obsolete. You have to SPED library */
int CAMSPED_Mount(void) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated delay_user is obsolete. You have to remove the call of it in your code */
#define delay_user(a) ERROR_Deprecation_For_Function_delay_user_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated delay_user is obsolete. You have to remove the call of it in your code */
Word	delay_user(int index) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated dllmalloc is obsolete. You have to use OS Layer API */
#define dllmalloc(a) ERROR_Deprecation_For_Function_dllmalloc_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated dllmalloc is obsolete. You have to use OS Layer API */
void *dllmalloc(unsigned long size) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated dllrealloc is obsolete. You have to use OS Layer API */
#define dllrealloc(a,b) ERROR_Deprecation_For_Function_dllrealloc_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated dllrealloc is obsolete. You have to use OS Layer API */
void *dllrealloc(void *old_p, unsigned int new_size) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated dllfree is obsolete. You have to use OS Layer API */
#define dllfree(a) ERROR_Deprecation_For_Function_dllfree_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated dllfree is obsolete. You have to use OS Layer API */
void dllfree(void* ptr) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated dspdef_reset is obsolete. You have to use Goal function */
#define dspdef_reset() ERROR_Deprecation_For_Function_dspdef_reset_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated dspdef_reset is obsolete. You have to use Goal function */
void dspdef_reset (void) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated gotoxy is obsolete. You have to use Goal function */
#define gotoxy(a,b) ERROR_Deprecation_For_Function_gotoxy_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated gotoxy is obsolete. You have to use Goal function */
int  gotoxy (int line, int column) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated gotoxydsp is obsolete. You have to use Goal function */
#define gotoxydsp(a,b,c) ERROR_Deprecation_For_Function_gotoxydsp_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated gotoxydsp is obsolete. You have to use Goal function */
int  gotoxydsp(FILE *stream, int line ,int row) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated key_c_alpha is obsolete. You have to remove the call of it in your code */
#define key_c_alpha(a,b,c) ERROR_Deprecation_For_Function_key_c_alpha_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated key_c_alpha is obsolete. You have to remove the call of it in your code */
int key_c_alpha( int x , int y, const char *table) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated mailbox_user is obsolete. You have to remove the call of it in your code */
#define mailbox_user(a) ERROR_Deprecation_For_Function_mailbox_user_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated mailbox_user is obsolete. You have to remove the call of it in your code */
Word	mailbox_user(int index) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated PPR_Mount is obsolete. You have to pinpad library */
#define PPR_Mount() ERROR_Deprecation_For_Function_PPR_Mount_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated PPR_Mount is obsolete. You have to pinpad library */
int PPR_Mount (void) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated sem_user is obsolete. You have to remove the call of it in your code */
#define sem_user(a) ERROR_Deprecation_For_Function_sem_user_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated sem_user is obsolete. You have to remove the call of it in your code */
Word	sem_user(int index) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated StartRetroEclairage is obsolete. You have to use HWCNF library */
#define StartRetroEclairage(a,b,c) ERROR_Deprecation_For_Function_StartRetroEclairage_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated StartRetroEclairage is obsolete. You have to use HWCNF library */
int StartRetroEclairage (unsigned char diviseur,  unsigned short int duree_high , unsigned short int duree_totale ) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated startupcv20 is obsolete. You have to use Goal function */
#define startupcv20(a,b) ERROR_Deprecation_For_Function_startupcv20_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated startupcv20 is obsolete. You have to use Goal function */
void startupcv20 (char pdoth,char pdotv) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated startupcv20dsp is obsolete. You have to use Goal function */
#define startupcv20dsp(a,b,c) ERROR_Deprecation_For_Function_startupcv20dsp_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated startupcv20dsp is obsolete. You have to use Goal function */
void startupcv20dsp (FILE *Fp, char pdoth,char pdotv) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated StopRetroEclairage is obsolete. You have to use HWCNF library */
#define StopRetroEclairage() ERROR_Deprecation_For_Function_StopRetroEclairage_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated StopRetroEclairage is obsolete. You have to use HWCNF library */
int StopRetroEclairage (void) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated task_user is obsolete. You have to remove the call of it in your code */
#define task_user(a) ERROR_Deprecation_For_Function_task_user_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated task_user is obsolete. You have to remove the call of it in your code */
Word	task_user(int index) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated WatchdogRefresh is obsolete. You have to remove the call of it in your code */
#define WatchdogRefresh() ERROR_Deprecation_For_Function_WatchdogRefresh_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated WatchdogRefresh is obsolete. You have to remove the call of it in your code */
void WatchdogRefresh(void) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated wherex is obsolete. You have to use Goal function */
#define wherex() ERROR_Deprecation_For_Function_wherex_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated wherex is obsolete. You have to use Goal function */
int  wherex (void) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated wherexdsp is obsolete. You have to use Goal function */
#define wherexdsp(a) ERROR_Deprecation_For_Function_wherexdsp_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated wherexdsp is obsolete. You have to use Goal function */
int  wherexdsp(FILE *stream) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated wherey is obsolete. You have to use Goal function */
#define wherey() ERROR_Deprecation_For_Function_wherey_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated wherey is obsolete. You have to use Goal function */
int  wherey (void) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated whereydsp is obsolete. You have to use Goal function */
#define whereydsp(a) ERROR_Deprecation_For_Function_whereydsp_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated whereydsp is obsolete. You have to use Goal function */
int  whereydsp(FILE *stream) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated exit is obsolete. You have to replace exit by OEM_exit in your code */
#define exit(a) ERROR_Deprecation_For_Function_exit_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please replace exit by OEM_exit in your code.*/

#else

#define exit OEM_exit

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated blink is obsolete. You have to use Goal function */
#define blink(a) ERROR_Deprecation_For_Function_exit_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated blink is obsolete. You have to use Goal function */
int  blink  (int flag) MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_TRAP_SDK091000_

/*! @deprecated cursor is obsolete. You have to use Goal function */
#define cursor(a) ERROR_Deprecation_For_Function_exit_For_Module_OS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for Trap. 
You can remove this error by adding _DEPRECATED_TRAP_SDK091000_. 
Please do the necessary to clean your code.*/

#else

/*! @deprecated cursor is obsolete. You have to use Goal function */
int  cursor  (int flag) MACRO_DEPRECATED;

#endif


#endif  // OEM_PUBLIC_DEPRECATED_H

 /* @}  */
