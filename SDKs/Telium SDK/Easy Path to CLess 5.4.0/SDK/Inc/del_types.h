/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

#ifndef __DEL_TYPES_H_INCLUDED__
#define __DEL_TYPES_H_INCLUDED__

#undef _DEL_USE_OLD_DEFINITION_
#ifdef MAX_DATA_ELEMENT
#define _DEL_USE_OLD_DEFINITION_
#endif // MAX_DATA_ELEMENT

/////////////////////////////////////////////////////////////////

#define __DEL_DEFINED__

#define DEL_NUMBER_OF_DATA_ELEMENT			(50)
#define DATA_ELEMENT_MAX_SIZE				(264)

// For compatibility
#undef MAX_DATA_ELEMENT
#undef MAX_ELT_LENGTH
#define MAX_DATA_ELEMENT					(DEL_NUMBER_OF_DATA_ELEMENT)
#define MAX_ELT_LENGTH						(DATA_ELEMENT_MAX_SIZE)

//// Types //////////////////////////////////////////////////////

#ifdef _DEL_USE_OLD_DEFINITION_
typedef _DataElement_ T_DATA_ELEMENT_VALUE;
#else // _DEL_USE_OLD_DEFINITION_
typedef struct
{
	unsigned long tag;
	unsigned int length;
	unsigned char ptValue[DATA_ELEMENT_MAX_SIZE];
} T_DATA_ELEMENT_VALUE;

typedef T_DATA_ELEMENT_VALUE _DataElement_;
#endif // _DEL_USE_OLD_DEFINITION_

/////////////////////////////////////////////////////////////////

#ifdef _DEL_USE_OLD_DEFINITION_
typedef _DEL_ T_DEL_VALUE;
#else // _DEL_USE_OLD_DEFINITION_
typedef struct
{
	int current;
	int count;
	T_DATA_ELEMENT_VALUE list[DEL_NUMBER_OF_DATA_ELEMENT];
} T_DEL_VALUE;

typedef T_DEL_VALUE _DEL_;
#endif // _DEL_USE_OLD_DEFINITION_

/////////////////////////////////////////////////////////////////

#ifdef _DEL_USE_OLD_DEFINITION_
typedef DataElement T_DATA_ELEMENT_PTR;
#else // _DEL_USE_OLD_DEFINITION_
typedef struct
{
	unsigned long tag;
	unsigned int length;
	unsigned char* ptValue;
} T_DATA_ELEMENT_PTR;

typedef T_DATA_ELEMENT_PTR DataElement;
#endif // _DEL_USE_OLD_DEFINITION_

/////////////////////////////////////////////////////////////////

#if ((!defined _DEL_USE_OLD_DEFINITION_) || (defined _SECDEL_))
typedef struct
{
	int current;
	int count;
	T_DATA_ELEMENT_PTR list[DEL_NUMBER_OF_DATA_ELEMENT];
} T_DEL_PTR_STD;
#else // ((!defined _DEL_USE_OLD_DEFINITION_) || (defined _SECDEL_))
typedef DEL T_DEL_PTR_STD;
#endif // ((!defined _DEL_USE_OLD_DEFINITION_) || (defined _SECDEL_))

#if ((!defined _DEL_USE_OLD_DEFINITION_) || (!defined _SECDEL_))
typedef struct
{
	int current;
	int count;
	T_DATA_ELEMENT_PTR list[DEL_NUMBER_OF_DATA_ELEMENT];
	unsigned char ValBuf[DEL_NUMBER_OF_DATA_ELEMENT][DATA_ELEMENT_MAX_SIZE];
} T_DEL_PTR_SEC;
#else // ((!defined _DEL_USE_OLD_DEFINITION_) || (!defined _SECDEL_))
typedef DEL T_DEL_PTR_SEC;
#endif // ((!defined _DEL_USE_OLD_DEFINITION_) || (!defined _SECDEL_))

#ifdef _SECDEL_
typedef T_DEL_PTR_SEC T_DEL_PTR;
#else // _SECDEL_
typedef T_DEL_PTR_STD T_DEL_PTR;
#endif // _SECDEL_

//// Global variables ///////////////////////////////////////////

//// Functions //////////////////////////////////////////////////

#endif // __DEL_TYPES_H_INCLUDED__
