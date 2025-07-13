/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#ifndef __DEL_H_INCLUDED__
#define __DEL_H_INCLUDED__

#include "del_types.h"

/////////////////////////////////////////////////////////////////

// Return errors
#define DEL_OK								(0)
#define DEL_ERROR							(-1)

//// Types //////////////////////////////////////////////////////

//// Functions Mappings /////////////////////////////////////////

// For compatibility with _emvdc_.h
#undef CopyEntree
#undef CopySortie
#undef DEL_CleanTags
#undef DEL_FlushTags


#ifdef _SECDEL_

#define DelPtr_Init							DelPtrSec_Init
#define DelPtr_GetCount						DelPtrSec_GetCount

#define DelPtr_AddDataElement				DelPtrSec_AddDataElement

#define DelPtr_GetDataElement				DelPtrSec_GetDataElement
#define DelPtr_GetFirstDataElement			DelPtrSec_GetFirstDataElement
#define DelPtr_GetNextDataElement			DelPtrSec_GetNextDataElement

#define DelPtr_Remove						DelPtrSec_Remove
#define DelPtr_RemoveDataElement			DelPtrSec_RemoveDataElement
#define DelPtr_RemoveEmptyDataElements		DelPtrSec_RemoveEmptyDataElements

#define DelPtr_CopyDelValue					DelPtrSec_CopyDelValue
#define DelPtr_AddDelValue					DelPtrSec_AddDelValue

#define DelPtr_CopyDelPtrStd				DelPtrSec_CopyDelPtrStd
#define DelPtr_AddDelPtrStd					DelPtrSec_AddDelPtrStd

#define DelPtr_CopyDelPtrSec				DelPtrSec_CopyDelPtrSec
#define DelPtr_AddDelPtrSec					DelPtrSec_AddDelPtrSec

#define DelPtr_CopyDelPtr					DelPtrSec_CopyDelPtrSec
#define DelPtr_AddDelPtr					DelPtrSec_AddDelPtrSec

#define DelValue_CopyDelPtr					DelValue_CopyDelPtrSec
#define DelValue_AddDelPtr					DelValue_AddDelPtrSec

#else // _SECDEL_

#define DelPtr_Init							DelPtrStd_Init
#define DelPtr_GetCount						DelPtrStd_GetCount

#define DelPtr_AddDataElement				DelPtrStd_AddDataElement

#define DelPtr_GetDataElement				DelPtrStd_GetDataElement
#define DelPtr_GetFirstDataElement			DelPtrStd_GetFirstDataElement
#define DelPtr_GetNextDataElement			DelPtrStd_GetNextDataElement

#define DelPtr_Remove						DelPtrStd_Remove
#define DelPtr_RemoveDataElement			DelPtrStd_RemoveDataElement
#define DelPtr_RemoveEmptyDataElements		DelPtrStd_RemoveEmptyDataElements

#define DelPtr_CopyDelValue					DelPtrStd_CopyDelValue
#define DelPtr_AddDelValue					DelPtrStd_AddDelValue

#define DelPtr_CopyDelPtrStd				DelPtrStd_CopyDelPtrStd
#define DelPtr_AddDelPtrStd					DelPtrStd_AddDelPtrStd

#define DelPtr_CopyDelPtrSec				DelPtrStd_CopyDelPtrSec
#define DelPtr_AddDelPtrSec					DelPtrStd_AddDelPtrSec

#define DelPtr_CopyDelPtr					DelPtrStd_CopyDelPtrStd
#define DelPtr_AddDelPtr					DelPtrStd_AddDelPtrStd

#define DelValue_CopyDelPtr					DelValue_CopyDelPtrStd
#define DelValue_AddDelPtr					DelValue_AddDelPtrStd

#endif // _SECDEL_

/////////////////////////////////////////////////////////////////

#ifndef _NO_DEL_VALUE_MAPPINGS_

#define _DEL_Init							DelValue_Init
#define _DEL_GetCount						DelValue_GetCount
#define _DEL_AddDataElement					DelValue_AddDataElement
#define _DEL_GetDataElement					DelValue_GetDataElement
#define _DEL_GetFirstDataElement			DelValue_GetFirstDataElement
#define _DEL_GetNextDataElement				DelValue_GetNextDataElement
#define _DEL_Remove							DelValue_Remove
#define _DEL_RemoveDataElement				DelValue_RemoveDataElement
#define _DEL_RemoveEmptyDataElements		DelValue_RemoveEmptyDataElements

#define _DEL_CopyDelValue					DelValue_CopyDelValue
#define _DEL_AddDelValue					DelValue_AddDelValue
#define _DEL_CopyDelPtrStd					DelValue_CopyDelPtrStd
#define _DEL_AddDelPtrStd					DelValue_AddDelPtrStd
#define _DEL_CopyDelPtrSec					DelValue_CopyDelPtrSec
#define _DEL_AddDelPtrSec					DelValue_AddDelPtrSec
#define _DEL_CopyDelPtr						DelValue_CopyDelPtr
#define _DEL_AddDelPtr						DelValue_AddDelPtr

// For compatibility
#define _DEL_init							DelValue_Init
#define _DEL_CleanTags						DelValue_RemoveEmptyDataElements
#define _DEL_FlushTags(pDel)				DelValue_RemoveDataElement(pDel, 0xffff)

#define DEL_AddToVal(pSource, pDest)		DelValue_CopyDelPtr(pSource, pDest)
#define CopyFromExternal(pSource, pDest)	DelValue_CopyDelPtr(pSource, pDest)
#define CopyEntree(pSource, pDest)			DelValue_CopyDelPtr(pSource, pDest)

#endif // _NO_DEL_VALUE_MAPPINGS_

/////////////////////////////////////////////////////////////////

#ifndef _NO_DEL_PTR_MAPPINGS_

#define DEL_Init							DelPtr_Init
#define DEL_GetCount						DelPtr_GetCount
#define DEL_AddDataElement					DelPtr_AddDataElement
#define DEL_GetDataElement					DelPtr_GetDataElement
#define DEL_GetFirstDataElement				DelPtr_GetFirstDataElement
#define DEL_GetNextDataElement				DelPtr_GetNextDataElement
#define DEL_Remove							DelPtr_Remove
#define DEL_RemoveDataElement				DelPtr_RemoveDataElement
#define DEL_RemoveEmptyDataElements			DelPtr_RemoveEmptyDataElements

#define DEL_CopyDelValue					DelPtr_CopyDelValue
#define DEL_AddDelValue						DelPtr_AddDelValue
#define DEL_CopyDelPtrStd					DelPtr_CopyDelPtrStd
#define DEL_AddDelPtrStd					DelPtr_AddDelPtrStd
#define DEL_CopyDelPtrSec					DelPtr_CopyDelPtrSec
#define DEL_AddDelPtrSec					DelPtr_AddDelPtrSec
#define DEL_CopyDelPtr						DelPtr_CopyDelPtr
#define DEL_AddDelPtr						DelPtr_AddDelPtr

#define DEL_CopyDEL							DEL_CopyDelPtr

// For compatibility
#define DEL_init							DelPtr_Init
#define DEL_CleanTags						DelPtr_RemoveEmptyDataElements
#define DEL_FlushTags(pDel)					DelPtr_RemoveDataElement(pDel, 0xffff)

#define DEL_ValToAdd						DelPtr_CopyDelValue
#define DEL_ConcatDEL						DelPtr_AddDelPtr
#define CopyToExternal						DelPtr_CopyDelValue
#define CopySortie							DelPtr_CopyDelValue

#endif // _NO_DEL_PTR_MAPPINGS_

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

int DelValue_Init(T_DEL_VALUE* pDel);
int DelValue_GetCount(const T_DEL_VALUE* pDel);

int DelValue_AddDataElement(T_DEL_VALUE* pDel, const T_DATA_ELEMENT_PTR* pElement);

T_DATA_ELEMENT_VALUE* DelValue_GetDataElement(T_DEL_VALUE* pDel, int nIndex);
T_DATA_ELEMENT_VALUE* DelValue_GetFirstDataElement(T_DEL_VALUE* pDel);
T_DATA_ELEMENT_VALUE* DelValue_GetNextDataElement(T_DEL_VALUE* pDel);

int DelValue_Remove(T_DEL_VALUE* pDel, int nIndex);
int DelValue_RemoveDataElement(T_DEL_VALUE* pDel, unsigned long ulTag);
int DelValue_RemoveEmptyDataElements(T_DEL_VALUE* pDel);

int DelValue_CopyDelValue(const T_DEL_VALUE* pSource, T_DEL_VALUE* pDestination);
int DelValue_AddDelValue(const T_DEL_VALUE* pSource, T_DEL_VALUE* pDestination);

int DelValue_CopyDelPtrStd(const T_DEL_PTR_STD* pSource, T_DEL_VALUE* pDestination);
int DelValue_AddDelPtrStd(const T_DEL_PTR_STD* pSource, T_DEL_VALUE* pDestination);

int DelValue_CopyDelPtrSec(const T_DEL_PTR_SEC* pSource, T_DEL_VALUE* pDestination);
int DelValue_AddDelPtrSec(const T_DEL_PTR_SEC* pSource, T_DEL_VALUE* pDestination);

/////////////////////////////////////////////////////////////////

int DelPtrStd_Init(T_DEL_PTR_STD* pDel);
int DelPtrStd_GetCount(const T_DEL_PTR_STD* pDel);

int DelPtrStd_AddDataElement(T_DEL_PTR_STD* pDel, const T_DATA_ELEMENT_PTR* pElement);

T_DATA_ELEMENT_PTR* DelPtrStd_GetDataElement(T_DEL_PTR_STD* pDel, int nIndex);
T_DATA_ELEMENT_PTR* DelPtrStd_GetFirstDataElement(T_DEL_PTR_STD* pDel);
T_DATA_ELEMENT_PTR* DelPtrStd_GetNextDataElement(T_DEL_PTR_STD* pDel);

int DelPtrStd_Remove(T_DEL_PTR_STD* pDel, int nIndex);
int DelPtrStd_RemoveDataElement(T_DEL_PTR_STD* pDel, unsigned long ulTag);
int DelPtrStd_RemoveEmptyDataElements(T_DEL_PTR_STD* pDel);

int DelPtrStd_CopyDelPtrStd(const T_DEL_PTR_STD* pSource, T_DEL_PTR_STD* pDestination);
int DelPtrStd_AddDelPtrStd(const T_DEL_PTR_STD* pSource, T_DEL_PTR_STD* pDestination);

int DelPtrStd_CopyDelValue(const T_DEL_VALUE* pSource, T_DEL_PTR_STD* pDestination);
int DelPtrStd_AddDelValue(const T_DEL_VALUE* pSource, T_DEL_PTR_STD* pDestination);

int DelPtrStd_CopyDelPtrSec(const T_DEL_PTR_SEC* pSource, T_DEL_PTR_STD* pDestination);
int DelPtrStd_AddDelPtrSec(const T_DEL_PTR_SEC* pSource, T_DEL_PTR_STD* pDestination);

/////////////////////////////////////////////////////////////////

int DelPtrSec_Init(T_DEL_PTR_SEC* pDel);
int DelPtrSec_GetCount(const T_DEL_PTR_SEC* pDel);

int DelPtrSec_AddDataElement(T_DEL_PTR_SEC* pDel, const T_DATA_ELEMENT_PTR* pElement);

T_DATA_ELEMENT_PTR* DelPtrSec_GetDataElement(T_DEL_PTR_SEC* pDel, int nIndex);
T_DATA_ELEMENT_PTR* DelPtrSec_GetFirstDataElement(T_DEL_PTR_SEC* pDel);
T_DATA_ELEMENT_PTR* DelPtrSec_GetNextDataElement(T_DEL_PTR_SEC* pDel);

int DelPtrSec_Remove(T_DEL_PTR_SEC* pDel, int nIndex);
int DelPtrSec_RemoveDataElement(T_DEL_PTR_SEC* pDel, unsigned long ulTag);
int DelPtrSec_RemoveEmptyDataElements(T_DEL_PTR_SEC* pDel);

int DelPtrSec_CopyDelPtrSec(const T_DEL_PTR_SEC* pSource, T_DEL_PTR_SEC* pDestination);
int DelPtrSec_AddDelPtrSec(const T_DEL_PTR_SEC* pSource, T_DEL_PTR_SEC* pDestination);

int DelPtrSec_CopyDelValue(const T_DEL_VALUE* pSource, T_DEL_PTR_SEC* pDestination);
int DelPtrSec_AddDelValue(const T_DEL_VALUE* pSource, T_DEL_PTR_SEC* pDestination);

int DelPtrSec_CopyDelPtrStd(const T_DEL_PTR_STD* pSource, T_DEL_PTR_SEC* pDestination);
int DelPtrSec_AddDelPtrStd(const T_DEL_PTR_STD* pSource, T_DEL_PTR_SEC* pDestination);

/////////////////////////////////////////////////////////////////

#endif // __DEL_H_INCLUDED__
