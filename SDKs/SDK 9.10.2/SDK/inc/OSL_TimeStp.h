// $Id: OSL_TimeStp.h,v 1.1.2.2 2013/03/19 13:41:08 nthibert Exp $
// This module allows the management of mutex
#ifndef OSL_TimeStp_h_INCLUDED
#define OSL_TimeStp_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

// ****************************************************************************
/// @addtogroup OSLayer
/// @{
/// @addtogroup TimeStp TimeStamp
/// @{

// ****************************************************************************

/** @addtogroup TimeStpDoc Documentation
	@{

  	This module lets you deal with high precision counter to make time measurment

	@}
	*/

/** TimeStp Value in nano second */
typedef long long T_OSL_TIMESTP;

/** Get the current time stamp (time since the system start)
@return current time stamp in ns */
T_OSL_TIMESTP OSL_TimeStp_Now(void);

/** Get elapsed time between 2 time stamp (end-begin) and return the difference
@param begin beginning time stamp
@param end ending time stamp
@return time stamp containing difference between beginning and end (in ns) */
T_OSL_TIMESTP OSL_TimeStp_Elapsed(T_OSL_TIMESTP begin, T_OSL_TIMESTP end);

/** Get elapsed time between 2 time stamp (end-begin), return the
difference in ms in a long
@param begin beginning time stamp
@param end ending time stamp
@return the elapsed time between begin and end in ms */
long OSL_TimeStp_ElapsedMs(T_OSL_TIMESTP begin, T_OSL_TIMESTP end);


/// @}
/// @}
#ifdef __cplusplus
}
#endif
#endif // OSL_TimeStp_h_INCLUDED
