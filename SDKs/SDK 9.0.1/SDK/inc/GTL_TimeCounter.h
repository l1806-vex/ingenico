/**
 * \file GTL_TimeCounter.h
 * \brief This file describes all the timer measurement features.
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

#ifndef __GTL_TIME_COUNTER_H__INCLUDED__
#define __GTL_TIME_COUNTER_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////

/*! \brief Structure for time counter */
typedef struct
{
	unsigned char m_bStarted;	/*!< Is the time counter is started or not */
	unsigned long m_ulStart;	/*!< Value of started time. */
	unsigned long m_ulTime;		/*!< Time counter value */
} T_TIME_COUNTER;


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Initialize a time counter.
//! \param[in,out] pCounter Time counter to initialize.

void GTL_TimeCounter_Init (T_TIME_COUNTER * pCounter);



//! \brief Start a time counter.
//! \param[in,out] pCounter Time counter to start.

void GTL_TimeCounter_StdStart (T_TIME_COUNTER * pCounter);



//! \brief Stop a time counter.
//! \param[in,out] pCounter Time counter to stop.

void GTL_TimeCounter_StdStop (T_TIME_COUNTER * pCounter);



//! \brief Start a time counter (with accurate time).
//! \param[in,out] pCounter Time counter to start.

void GTL_TimeCounter_AccurateStart (T_TIME_COUNTER * pCounter);



//! \brief Stop a time counter (with accurate time).
//! \param[in,out] pCounter Time counter to stop.

void GTL_TimeCounter_AccurateStop (T_TIME_COUNTER * pCounter);



#endif // __GTL_TIME_COUNTER_H__INCLUDED__
