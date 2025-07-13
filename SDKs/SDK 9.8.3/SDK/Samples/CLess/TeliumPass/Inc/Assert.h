/**
 *! \file        Assert.h
 * \brief Assertions management for debug purposes.
 *
 *
 * \author SAGEM MONETEL
 * \author Copyright (c) 2006 Sagem Monetel SA, rue claude Chappe,\n
 *		   07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Sagem Monetel SA has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Sagem Monetel.
 **/

/////////////////////////////////////////////////////////////////

#ifndef __ASSERT_H__INCLUDED__
#define __ASSERT_H__INCLUDED__

// Always execute ASSERTs in debug mode
#if (defined(_DEBUG) || defined(__DOXYGEN__))
	#ifndef __USE_ASSERT__
		#define __USE_ASSERT__		//!< Enable or not the ASSERT functions.
	#endif // __USE_ASSERT__
#endif // _DEBUG || __DOXYGEN__


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


/*! \def DebugBreak() */
/*! \brief Stop the execution of the software as a break point do. */

#ifdef _SIMULPC_
	/*! \hideinitializer */
	#define DebugBreak()			{ _asm int 3 }
#else // _SIMULPC_
	/*! \hideinitializer */
	#define DebugBreak()			while(1) { }
#endif // _SIMULPC_


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////


/*! \def ASSERT(test)
 *	@hideinitializer
 *	@brief Assert that the specified value is true.
 *	@param[in] test Test to perform. If the result is FALSE, the execution of the software is stopped.
 *	@remarks This function is compiled only if \a __USE_ASSERT__ or \a _DEBUG are defined.
 **/

/*! \def VERIFY(test)
 *	@hideinitializer
 *	@brief Verify that test to perform is true.
 *	@param[in] test Test to perform. If the result is FALSE, the execution of the software is stopped.
 *	@remarks The test instructions are always executed. The verification procedure is compiled only if \a __USE_ASSERT__ or \a _DEBUG are defined.
 **/

/*! \def VERIFY_OK(test)
 *	@hideinitializer
 *	@brief Verify that test to perform is equal to OK.
 *	@param[in] test Test to perform. If the result is not \a OK, the execution of the software is stopped.
 *	@remarks The test instructions are always executed. The verification procedure is compiled only if \a __USE_ASSERT__ or \a _DEBUG are defined.
 **/

#ifdef __USE_ASSERT__

	#define ASSERT_FAILED_DIAG		0xffff		/*!< Diagnostic generated when an assertion fails. */

	/*! \brief Manage an assertion.
	 *	@param[in] bTest TRUE or FALSE.
	 *	@param[in] szFile Source file name.
	 *	@param[in] nLine Line in the source file name.
	 *	@return TRUE if the process must be stopped, FALSE to continue.
	 *	@remarks You must not call directly this function. Use only \ref ASSERT, \ref VERIFY and \ref VERIFY_OK.
	 **/
	extern int __assert(int bTest, const char* szFile, int nLine);

	/*! \hideinitializer */
	#define ASSERT(test)							{ if (__assert((unsigned char)(test), __FILE__, __LINE__)) \
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

#endif // __ASSERT_H__INCLUDED__
