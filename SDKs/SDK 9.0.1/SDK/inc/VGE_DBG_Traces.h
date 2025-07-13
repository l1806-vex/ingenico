

#ifndef __VGE_DBG_TRACES_H__INCLUDED__
#define __VGE_DBG_TRACES_H__INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif
//! \addtogroup VGE_DBG
//! @{
//! \brief Debug functionnalities :
//!	- traces and diagnostic features
//!	- assert 


 /////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Generate a diagnostic.
//! \param[in] nDiag Diagnostic value.
//! \param[in] bCritical TRUE for a critical diagnostic, FALSE otherwise.
//! \note If the the diagnostic is critical, the terminal resets with diagnostic value as returned error.\n
//! If not critical the diagnostic is recorded in APPTEXT.DIA

void VGE_DBG_Traces_Diagnostic (const int nDiag, const int bCritical);



//! \brief Generate a text diagnostic.
//! \param[in] pString Diagnostic text in the \a printf format.

void VGE_DBG_Traces_DiagnosticText (const char* pString, ...)
#if (defined(__GNUC__) && !defined(_SIMULPC_))
	__attribute__((format(printf, 1, 2)));
#else
	;
#endif



//! \brief Output a debug string.
//! \param[in] pString A string in the \a printf format to trace.

void VGE_DBG_Traces_TraceDebug (const char* pString, ...)
#if (defined(__GNUC__) && !defined(_SIMULPC_))
	__attribute__((format(printf, 1, 2)));
#else
	;
#endif



//! \brief Output a debug buffer.
//! \param[in] nSize The size of the buffer to trace.
//! \param[in] pBuffer The buffer to trace.
//! \param[in] pString A string in the \a printf format to trace.

void VGE_DBG_Traces_TraceDebugBuffer (const int nSize, const void* pBuffer, const char* pString, ...)
#if (defined(__GNUC__) && !defined(_SIMULPC_))
	__attribute__((format(printf, 3, 4)));
#else
	;
#endif


//! @} 

#ifdef __cplusplus
}
#endif
#endif // __VGE_DBG_TRACES_H__INCLUDED__
