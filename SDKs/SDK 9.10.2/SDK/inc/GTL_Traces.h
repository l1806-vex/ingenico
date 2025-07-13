/**
 * \file GTL_Traces.h
 * \brief Functions used to manage traces features (debug purpose).
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

#ifndef __GTL_TRACES_H__INCLUDED__
#define __GTL_TRACES_H__INCLUDED__


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \addtogroup TracesFunctions
//! @{

//! \brief Generate a diagnostic.
//! \param[in] nDiag Diagnostic value.
//! \param[in] bCritical TRUE for a critical diagnostic, FALSE otherwise.

void GTL_Traces_Diagnostic (const int nDiag, const int bCritical);



//! \brief Generate a text diagnostic.
//! \param[in] pString Diagnostic text in the \a printf format.

void GTL_Traces_DiagnosticText (const char* pString, ...)
#if (defined(__GNUC__) && !defined(_SIMULPC_))
	__attribute__((format(__printf__, 1, 2)));
#else
	;
#endif



//! \brief Output a debug string.
//! \param[in] pString A string in the \a printf format.

void GTL_Traces_TraceDebug (const char* pString, ...)
#if (defined(__GNUC__) && !defined(_SIMULPC_))
	__attribute__((format(__printf__, 1, 2)));
#else
	;
#endif



//! \brief Output a debug buffer.
//! \param[in] nSize The size of the buffer to trace.
//! \param[in] pBuffer The buffer to trace.
//! \param[in] pString A string in the \a printf format.

void GTL_Traces_TraceDebugBuffer (const int nSize, const void* pBuffer, const char* pString, ...)
#if (defined(__GNUC__) && !defined(_SIMULPC_))
	__attribute__((format(__printf__, 3, 4)));
#else
	;
#endif

//! @}


#endif // __GTL_TRACES_H__INCLUDED__
