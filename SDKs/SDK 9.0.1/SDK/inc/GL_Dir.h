// $Id: GL_Dir.h,v 1.1.2.3 2011/12/13 14:07:53 pplasse Exp $
/* This module provide a uniform access to dirs in terminal */
#ifndef GL_DIR_h_INCLUDED
#define GL_DIR_h_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/** 
@addtogroup GL_Dir
@{
@addtogroup GL_DirDoc Documentation
@{
   File API provide an uniform mean to access directory in the terminal or external peripheral of the terminal using a unique directory like an url.
   
   See @ref GL_Widget_Url for the url coding.

Sample to scan directory : 


 * @include GL_Dir_Sample_01.c

Sample to scan TAR file : 


 * @include GL_Dir_Sample_02.c


@}
*/


/** Define a dir handle used in dir module function,
	a value of 0 / NULL indicates a bad handle */
typedef struct T_TL_DIR * T_GL_HDIR;

/** Creates or opens a dir and return its handle.
To open a folder you must prefix it with "dir://", to open a tar archive you must prefix it with" file://"
(See @ref GL_Widget_Url for the url coding)
@param directory complete dirname of the dir to open
@return the directory handle or NULL if an error occurs */
T_GL_HDIR GL_Dir_Open(const char* directory) GL_EXCEPTION;

/** Closes a directory previously opened with @ref GL_Dir_Open
@param dir directory handle
@return GL_SUCCESS or error in @ref T_GL_ERROR_CODE */
T_GL_ERROR_CODE GL_Dir_Close(T_GL_HDIR dir) GL_EXCEPTION;

/** Selects the next item in the directory opened
@param dir directory handle
@return the number of bytes read */
T_GL_ERROR_CODE GL_Dir_Next(T_GL_HDIR dir) GL_EXCEPTION;

/** Gets the current selected item name
@param dir directory handle
@return name of current item */
const char * GL_Dir_GetName(T_GL_HDIR dir) GL_EXCEPTION;

/** Gets the current selected item path name
@param dir directory handle
@return name of current item */
const char * GL_Dir_GetPath(T_GL_HDIR dir) GL_EXCEPTION;

/** Indicates if the current selected item is a directory
@param dir directory handle
@return true if it is a directory else returns false */
bool GL_Dir_IsDirectory(T_GL_HDIR dir) GL_EXCEPTION;

/** Indicates if the current selected item is a file
@param dir directory handle
@return true if it is a file else returns false */
bool GL_Dir_IsFile(T_GL_HDIR dir) GL_EXCEPTION;

/// @}

#ifdef __cplusplus
}
#endif

#endif /*GL_DIR_h_INCLUDED*/
