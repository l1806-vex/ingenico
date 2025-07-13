#ifdef __cplusplus
extern "C" {
#endif

#ifndef __RTCTIME_H_INCLUDED__
#define __RTCTIME_H_INCLUDED__

#include "rtctime_def.h"
#ifdef __FRAMEWORK_TELIUM_2__
#include "rtctime_deprecated.h"
#endif

/*! @addtogroup KSFAM_CAL
	* @{
 */ 

/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function is used to check the date by verifying the coherency of the param eterized date.
 * @param date : pointer to structure DATE.
 * @return
 * - 0 if function has been correctly executed
 * - 1 if date is incoherent.
 *
 * @link KSFAM_CAL Back to top @endlink
 */ 
int ctrl_date (DATE * date);



/*! @brief This function is used to read the date in the terminal's calendar.
 * @param pt_date : pointer to structure DATE. 
 * @return 
 * - 0 if function has been correctly executed.
 * - -1 if date is incoherent.
 *
 * @link KSFAM_CAL Back to top @endlink
 */ 
int  read_date (DATE *pt_date );

/*! @}  */ 


#endif   // __RTCTIME_H_INCLUDED__

#ifdef __cplusplus
}
#endif
