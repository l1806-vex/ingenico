/**
 * \file GTL_AccurateTimer.h
 * \brief Functions used to manage accurate system ticks and timeouts.
 *
 *
 * \author Ingenico
 * \author Copyright (c) 2009 Ingenico, 1 rue claude Chappe,\n
 *		   07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 **/

#ifndef __GTL_ACCURATE_TIMER_H__INCLUDED__
#define __GTL_ACCURATE_TIMER_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Init the plateform (which timer base depends on).

void GTL_AccurateTimer_Init (void);



//! \brief Get the tick value (accurate value).
//! \return The tick value.

unsigned long GTL_AccurateTimer_GetCurrent (void);



//! \brief Get the elapsed time (accurate value).
//! \param[in] ulStartTime The tick value for the starting time.
//! \return The elapsed number of ticks.

unsigned long GTL_AccurateTimer_GetElapsed (const unsigned long ulStartTime);



//! \brief Converts tick to time according to the running plateform.
//! \param[in] ulTicks Number of ticks to be converted.
//! \param[in] ulBase Requested time base (1=>sedconds, 1000=>milliseconds, 1000000=>µseconds).
//! \return Time in the requested base.

unsigned long GTL_AccurateTimer_ConvertTicksToTime (const unsigned long ulTicks, const unsigned long ulBase);



#endif // __GTL_ACCURATE_TIMER_H__INCLUDED__
