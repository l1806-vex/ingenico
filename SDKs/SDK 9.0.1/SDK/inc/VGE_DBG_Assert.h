/**
 * \file VGE_DBG_Assert.h
 * \brief Functions to manage assertion.
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

#ifndef __VGE_DBG_ASSERT_H__INCLUDED__
#define __VGE_DBG_ASSERT_H__INCLUDED__


#ifdef __cplusplus
extern "C" {
#endif


//! \addtogroup VGE_DBG
//! @{


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define ASSERT_FAILED_DIAG		0xffff		/*!< \brief Diagnostic generated when an assertion fails. */


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////


#ifdef _SIMULPC_

#ifdef __GNUC__

/* DebugBreak() : Stop the execution of the software as a breakpoint do. */

//! \hideinitializer
#define DebugBreak()		__asm__ ( "int $3" )

#elif (defined _MSC_VER)

//! \hideinitializer
#define DebugBreak()		__asm { int 3 }

#else

//! \hideinitializer
#define DebugBreak()		ttestall(0, 0)

#endif

#else // _SIMULPC_

#ifdef __GNUC__

//! \hideinitializer
#define DebugBreak()		__asm__ ( ".byte 0x00\n.byte 0xdf" )

#else

//! \hideinitializer
#define DebugBreak()		exit(ASSERT_FAILED_DIAG)

#endif

#endif // _SIMULPC_

//! \def VGE_DBG_ASSERT(test)
//! \brief If \a __USE_ASSERT__ is defined, it checks that the condition \a test is \a TRUE. If the condition is \a FALSE, <b>the execution is stopped</b>.<br>
//! If \a __USE_ASSERT__ is not defined, <b>no code and no data are generated</b>.\n
//! When assertion is false, this function proposes to developpers to continue, to do a breakpoint, to reset the terminal or to print the assertion.
//! In case of brakpoint chosen, on Ingedev it is not possible to continue to run the code.

//! \def VGE_DBG_VERIFY(test)
//! \brief If \a __USE_ASSERT__ is defined, it checks that the condition \a test is \a TRUE. If the condition is \a FALSE, <b>the execution is stopped</b>.<br>
//! If \a __USE_ASSERT__ is not defined, the condition <b>\a test is compiled</b> but <b>the result is not tested</b>.\n
//! When assertion is false, this function proposes to developpers to continue, to do a breakpoint, to reset the terminal or to print the assertion.
//! In case of brakpoint chosen, on Ingedev it is not possible to continue to run the code.

//! \def VGE_DBG_VERIFY_OK(test)
//! \brief If \a __USE_ASSERT__ is defined, it checks that the condition \a test is \a OK (=0). If the condition is not \a OK, <b>the execution is stopped</b>.<br>
//! If \a __USE_ASSERT__ is not defined, the condition <b>\a test is compiled</b> but <b>the result is not tested</b>.\n
//! When assertion is false, this function proposes to developpers to continue, to do a breakpoint, to reset the terminal or to print the assertion.
//! In case of brakpoint chosen, on Ingedev it is not possible to continue to run the code.

//! \cond NOT_IN_DOCUMENTATION

//! \endcond

#ifdef __USE_ASSERT__

	int __VGE_DBG_Assert_Test (const int bTest, const char * szCondition, const char * szFile, const int nLine);

	/*! \hideinitializer */
	#define VGE_DBG_ASSERT(test)							{ if (__VGE_DBG_Assert_Test((int)(test), #test, __FILE__, __LINE__)) \
															DebugBreak(); }

	/*! \hideinitializer */
	#define VGE_DBG_VERIFY(test)							VGE_DBG_ASSERT(test)

	/*! \hideinitializer */
	#define VGE_DBG_VERIFY_OK(test)							VGE_DBG_ASSERT((test) == OK)

#else // __USE_ASSERT__

	/*! \hideinitializer */
	#define VGE_DBG_ASSERT(test)							((void)0)

	/*! \hideinitializer */
	#define VGE_DBG_VERIFY(test)							(test)

	/*! \hideinitializer */
	#define VGE_DBG_VERIFY_OK(test)							(test)

#endif // __USE_ASSERT__

//! @}

#ifdef __cplusplus
}
#endif

#endif // __VGE_DBG_ASSERT_H__INCLUDED__
