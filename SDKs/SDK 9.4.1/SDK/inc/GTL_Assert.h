/**
 * \file GTL_Assert.h
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

#ifndef __GTL_ASSERT_H__INCLUDED__
#define __GTL_ASSERT_H__INCLUDED__

//! \addtogroup AssertDebugTool
//! @{

/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#define ASSERT_FAILED_DIAG		0xffff		/*!< \brief Diagnostic generated when an assertion fails. */


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

/*! \def DebugBreak() */
/*! \brief Stop the execution of the software as a breakpoint do. */

#ifdef _SIMULPC_

#ifdef __GNUC__

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

//! \def ASSERT(test)
//! \brief If \a __USE_ASSERT__ is defined, it checks that the condition \a test is \a TRUE. If the condition is \a FALSE, <b>the execution is stopped</b>.<br>
//! It \a __USE_ASSERT__ is not defined, <b>no code and no data are generated</b>.

//! \def VERIFY(test)
//! \brief If \a __USE_ASSERT__ is defined, it checks that the condition \a test is \a TRUE. If the condition is \a FALSE, <b>the execution is stopped</b>.<br>
//! It \a __USE_ASSERT__ is not defined, the condition <b>\a test is compiled</b> but <b>the result is not tested</b>.

//! \def VERIFY_OK(test)
//! \brief If \a __USE_ASSERT__ is defined, it checks that the condition \a test is \a OK (=0). If the condition is not \a OK, <b>the execution is stopped</b>.<br>
//! It \a __USE_ASSERT__ is not defined, the condition <b>\a test is compiled</b> but <b>the result is not tested</b>.

//! \cond NOT_IN_DOCUMENTATION

//! \brief Manage an assertion. You must not call directly this function. Use only \ref ASSERT, \ref VERIFY and \ref VERIFY_OK.
//! \param[in] bTest TRUE or FALSE.
//! \param[in] szExpression Tested expression.
//! \param[in] szFile Source file name.
//! \param[in] nLine Line in the source file name.
//! \return TRUE if the process must be stopped.
//! \return FALSE to continue.

int __GTL_Assert_Test (const int bTest, const char * szExpression, const char * szFile, const int nLine);

//! \endcond

#ifdef __USE_ASSERT__

	/*! \hideinitializer */
	#define ASSERT(test)							{ if (__GTL_Assert_Test((int)(test), #test, __FILE__, __LINE__)) \
															DebugBreak(); }

	/*! \hideinitializer */
	#define VERIFY(test)							ASSERT(test)

	/*! \hideinitializer */
	#define VERIFY_OK(test)							ASSERT((test) == OK)

#else // __USE_ASSERT__

	/*! \hideinitializer */
	#define ASSERT(test)							((void)0)

	/*! \hideinitializer */
	#define VERIFY(test)							(test)

	/*! \hideinitializer */
	#define VERIFY_OK(test)							(test)

#endif // __USE_ASSERT__

//! @}

#endif // __GTL_ASSERT_H__INCLUDED__
