// $Id: GL_StringList.h,v 1.1.2.4 2011/12/13 14:07:53 pplasse Exp $
// StringList file management
#ifndef GL_StringList_h_INCLUDED
#define GL_StringList_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_StringList
@{
@addtogroup GL_StringListDoc Documentation
@{
	This allows the management of list of strings.

	Sample to manage a list of strings :


 * @include GL_StringList_Sample_01.c

@}
*/

/** StringList file handle */
typedef struct T_GL_STRINGLIST * T_GL_HSTRINGLIST;

/** Creates string list
@param charset encoding charset of strings
@return the strings list handle or null */
T_GL_HSTRINGLIST GL_StringList_Create(T_GL_ENCODING_CHARSET charset) GL_EXCEPTION;

/** Destroys all the content of the list 
@param list strings list handle */
void GL_StringList_Destroy(T_GL_HSTRINGLIST list) GL_EXCEPTION;

/** Clears all the content of the list 
@param list strings list handle */
void GL_StringList_Clear(T_GL_HSTRINGLIST list) GL_EXCEPTION;

/** Gets the number of elements in the list
@param list strings list handle 
@return the number of elements */
unsigned long GL_StringList_GetCount(T_GL_HSTRINGLIST list) GL_EXCEPTION;

/** Indicates the charset of the strings list 
@param list strings list handle 
@return charset */
T_GL_ENCODING_CHARSET GL_StringList_GetCharset(T_GL_HSTRINGLIST list) GL_EXCEPTION;

/** Gets a string located at a given index. 
WARNING : a pointer to the string is returned, if you want to keeps its value you must copy the contents
@param list strings list handle
@param index index of element in the list
@return string pointer or null if the index is out of bound of list */
const char * GL_StringList_GetString(T_GL_HSTRINGLIST list, unsigned long index) GL_EXCEPTION;

/** Sets a string located at a given index
@param list strings list handle
@param index index of element in the list
@param value string to set (WARNING: if the string is not correctly encoded with the charset of list, it will be ignored)*/
void GL_StringList_SetString(T_GL_HSTRINGLIST list, unsigned long index, const char * value) GL_EXCEPTION;

/** Deletes a string located at a given index
@param list strings list handle
@param index index of element in the list */
void GL_StringList_RemoveString(T_GL_HSTRINGLIST list, unsigned long index) GL_EXCEPTION;

/** Adds a string at the end of list 
@param list strings list handle
@param value string to add */
void GL_StringList_AddString(T_GL_HSTRINGLIST list, const char * value) GL_EXCEPTION;

/** Searchs a string in the list 
@param list strings list handle
@param value string to search
@return the index of string or GL_TIME_INFINITE if it is not found */
unsigned long GL_StringList_Search(T_GL_HSTRINGLIST list, const char * value) GL_EXCEPTION;

/** Clone the list and clone the content
@param list strings list handle
@return the strings list handle or null */
T_GL_HSTRINGLIST GL_StringList_Clone(T_GL_HSTRINGLIST list);

/** Copy the source list into the target list
@param source source strings list handle
@param target target strings list handle */
void GL_StringList_Copy(T_GL_HSTRINGLIST source, T_GL_HSTRINGLIST target);

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_StringList_h_INCLUDED
