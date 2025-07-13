#ifdef __cplusplus
extern "C" {
#endif

#ifndef __XECARM_DEF_H_INCLUDED__
#define __XECARM_DEF_H_INCLUDED__

#include "basearm_def.h"

/*! @addtogroup KSFAM_OS_KERNEL
	* @{
 */ 

/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Define a status. */
typedef Word tStatus;

/*! @brief Define the timeout time :  \li zero : infinite waiting; cTimeOut never occurs. \li other: max waiting time in clock base units (finite waiting) */
typedef DoubleWord tTimeOut;

/*! @brief Define the state of a task :  \li 0=cCurrent, \li 1=cReady, \li 2=cWaiting, \li 3=cNonOperational */
typedef Word   tTaskState;

/*! @brief Define an event. */
typedef Word tEvent;  /* range 0..15 */

/*! @brief Corresponding to the sum of bits, 1 bit per event. */
typedef DoubleWord tEventList;

/*! @}  */ 


#endif   // __XECARM_DEF_H_INCLUDED__

#ifdef __cplusplus
}
#endif
