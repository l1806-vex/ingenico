/*! @addtogroup KSFAM_OS_KERNEL
	* @{
 */ 

#ifndef _NOY_RTC_PUBLIC_H
#define _NOY_RTC_PUBLIC_H


/*
======================================================================
					Configuration couche rtc sur Osg/Nuc
======================================================================
*/

#define	OS_rtc_k_NbTask            150		/*!< Max number of tasks @deprecated replaced by \ref SYS_FIOCTL_GET_OEMC_MAX_TASK_NUMBER
                                          */
#define	OS_rtc_k_NbMailBox   			 150		/*!< Max number of mailboxes @deprecated replaced by \ref SYS_FIOCTL_GET_OEMC_MAX_MAILBOX_NUMBER
                                          */
#define	OS_rtc_k_NbSema       		 150  	/*!< Max number of semaphores @deprecated replaced by \ref SYS_FIOCTL_GET_OEMC_MAX_SEMAPHORE_NUMBER
                                          */
#define	OS_rtc_k_NbDelay     				30		/*!< Max number of  delays @deprecated replaced by \ref SYS_FIOCTL_GET_OEMC_MAX_DELAY_NUMBER
                                          */
#define	OS_rtc_k_NbEnveloppe     		60		/*!< Max number of "enveloppes" @deprecated  */


#endif

/*! @}  */ 


