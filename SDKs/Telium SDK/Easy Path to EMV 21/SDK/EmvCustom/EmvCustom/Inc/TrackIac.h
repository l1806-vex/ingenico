/**
* \file TrackIac.h
* \brief This module contains the functions needed to perform service 
* call to Emv Tool application.
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/

#ifndef INCLUDED_TRACK_IAC_H
#define INCLUDED_TRACK_IAC_H

//! \defgroup Group_TrackIac Functions needed to use EMV tool application.
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ========================================================================	*/
/* Static function definitions                                              */
/* ========================================================================	*/

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

#ifdef _TRACK_IAC_

//===========================================================================
//! \brief This function performs a service call to Emv tool, with empty data
//! to reset the trace file.
//===========================================================================
void TrackIAC_Init(void);

//===========================================================================
//! \brief This function performs a service call to Emv tool, to trace the
//! input DEL.
//! \param[in] pProcessStep : structure containing the input DEL.
//===========================================================================
void TrackIAC_TraceInput(StructProcessStep* pProcessStep);

//===========================================================================
//! \brief This function performs a service call to Emv tool, to trace the
//! output DEL.
//! \param[in] pProcessStep : structure containing the output DEL.
//===========================================================================
void TrackIAC_TraceOutput(StructProcessStep* pProcessStep);

#else

#define TrackIAC_Init()
#define TrackIAC_TraceInput(pProcessStep)		(void)pProcessStep
#define TrackIAC_TraceOutput(pProcessStep)		(void)pProcessStep

#endif

//! @}

#endif  // INCLUDED_TRACK_IAC_H

