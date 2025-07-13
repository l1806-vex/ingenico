/**
 * \file GTL_StdTimer.h
 * \brief This file describes all the standard timer measurement features (precision is 10ms).
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

#ifndef __GTL_STDTIMER_H__INCLUDED__
#define __GTL_STDTIMER_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

//! \addtogroup StdTimersDefines
//! @{

#define TIMER_STD_INFINITE			0x7fffffff		/*!< Infinite timeout value. */

//! @}


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup StdTimersFunctions
//! @{

//! \brief Get the tick value.
//! \return The tick value.

unsigned long GTL_StdTimer_GetCurrent (void);



//! \brief Get the elapsed time.
//! \param[in] ulStartTime The tick value for the starting time.
//! \return The elapsed number of ticks.

unsigned long GTL_StdTimer_GetElapsed (const unsigned long ulStartTime);



//! \brief Get the remaining time of a timeout.
//! \param[in] ulStartTime The tick value for the starting time.
//! \param[in] nTimeout The timeout value. Use \ref TIMER_STD_INFINITE for an infinite timeout.
//! \return The remaining number of ticks. 0 if the timeout has expired.

unsigned long GTL_StdTimer_GetRemaining (const unsigned long ulStartTime, const unsigned int nTimeout);

//! @}


#endif // __GTL_STDTIMER_H__INCLUDED__
