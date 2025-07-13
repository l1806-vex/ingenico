/*! @addtogroup KSFAM_CAL
	* @{
 */ 

#ifndef _RTCTIMER_DEPRECATED_H
#define _RTCTIMER_DEPRECATED_H

/*
======================================================================
			Data Structures Definition
======================================================================
*/



/*! @deprecated This function (in oem.h) is deprecated since SDK 9.6.0, please use write_date from oem.h
 * When using this function, an error is generated, you can remove this error by adding _DEPRECATED_RTCTIME_SDK96_ 
 * This function is used to program the terminal calendar. 
 * @param pt_date : pointer to structure DATE.
 * @return 
 * - 0 if function has been correctly executed.
 * - -1 if date is incoherent.
 *
 * @link KSFAM_CAL Back to top @endlink
 */ 
// \if SIMULATION
// write_date:KSFAM_CAL:0x03
// 1: ONE_POINTER
// \endif
#ifndef _DEPRECATED_RTCTIME_SDK96_
#define  write_date(a) ERROR_Deprecation_For_This_write_date__Use_write_date_from_oem_h;
/* This error is generated to warn you about the deprecation for writedate (rtctime).
You can remove this error by adding _DEPRECATED_RTCTIME_SDK96_. Please do the necessary to clean your
code.*/
#else
int  write_date ( DATE *pt_date) MACRO_DEPRECATED;
#endif

#endif
/*! @}  */ 


