// $Id: GL_File.h,v 1.1.2.5 2012/03/06 16:34:52 rbertholet Exp $
// File file management
#ifndef GL_File_h_INCLUDED
#define GL_File_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_File 
@{
@addtogroup GL_FileDoc File
@{
   File API provide an uniform mean to acces file in the terminal or external peripheral of the terminal using a unique filename like an url.
   
   See @ref GL_Widget_Url for the url coding.

Sample to write : 


 * @include GL_File_Sample_01.c

Sample to read :


 * @include GL_File_Sample_02.c

You can read the contents of a tar file, this requires that the file extension is the "TAR".
It is not possible to write in a TAR file.


 * @include GL_File_Sample_03.c

@}
*/

/** File file handle */
typedef struct T_TL_FILE * T_GL_HFILE;

/** Creates or opens a file and return its handle
@param name : complete filename of the file to open (See @ref GL_Widget_Url for the url coding)
@param mode : opening mode of the file
@param access : opening access mode of the file
@return the File handle or NULL if an error occurs */
T_GL_HFILE GL_File_Open(const char* name, T_GL_FILE_OPEN_MODE mode, T_GL_FILE_ACCESS access) GL_EXCEPTION;

/** Close sa file previously opened with GL_File_Open
@param file pointer on a previously opened file to close
@return error code*/
T_GL_ERROR_CODE GL_File_Close(T_GL_HFILE file) GL_EXCEPTION;

/** Reads data from the specified file
@param file previously opened file to read
@param buffer point to the buffer to fill in
@param count number of bytes to read
@return the number of bytes read */
unsigned long GL_File_Read(T_GL_HFILE file, void * buffer, unsigned long count) GL_EXCEPTION;

/** Writes data in the specified file
@param file previously opened file to read
@param buffer point to the buffer to read from
@param count number of bytes to write
@return the number of bytes written */
unsigned long GL_File_Write(T_GL_HFILE file, const void * buffer, unsigned long count) GL_EXCEPTION;

/** Move pointer in file to the desired position
@param file previously opened file to seek in
@param offset offset to move pointer in bytes
@param origin  origin
@return GL_SUCCESS or error code */
T_GL_ERROR_CODE GL_File_Seek(T_GL_HFILE file, long offset, T_GL_FILE_POS origin) GL_EXCEPTION;

/** Returns the current position in the file in bytes from the beginning
@param file previously opened file to retrieve position
@return the position in the file of (-1) if error */
long GL_File_Tell(T_GL_HFILE file);

/** Delete a file specified by its complete filename
@param name : complete filename of the file to delete (See @ref GL_Widget_Url for the url coding)
@return error code*/
T_GL_ERROR_CODE GL_File_Delete(const char* name) GL_EXCEPTION;

/** Returns the size of a file
@param name complete filename of the file to retrieve its size (See @ref GL_Widget_Url for the url coding)
@return the size of the file of (-1) if error */
long GL_File_GetSizeFilename(const char* name) GL_EXCEPTION;

/** Returns the size of a file (with its descriptor)
@param file file descriptor to retrieve its size
@return the size of the file of (-1) if error */
long GL_File_GetSize(T_GL_HFILE file) GL_EXCEPTION;

/** Returns the time of a file (creation / last modified / last access)
@param name complete filename of the file to retrieve its time (See @ref GL_Widget_Url for the url coding)
@param time pointer on a valid time structure to fill in the time
@return error code 

Nota : for FFMS only creation time exists, other times will be filled with the creation time */
T_GL_ERROR_CODE GL_File_GetTimeFilename(const char* name, T_GL_FILE_TIME* time) GL_EXCEPTION;

/** Returns the time of a file (creation / last modified / last access) (with its descriptor)
@param file file descriptor to retrieve its time
@param time pointer on a valid time structure to fill in the time
@return error code

Nota : for FFMS only creation time exists, other times will be filled with the creation time */
T_GL_ERROR_CODE GL_File_GetTime(T_GL_HFILE file, T_GL_FILE_TIME* time) GL_EXCEPTION;

/** Test whether the filename string matches the pattern string (support for MSDOS shell-style wildcards)
The special characters used in shell-style wildcards are:
	- * matches everything 
	- ? matches any single character 
@param path path or filename string to compare
@param pattern pattern to compare using wildcards ('?' & '*'). 
@return true if path is equal to pattern else returns false */
bool GL_File_MatchPath (const char * path, const char * pattern);

/** Forces a write of all user-space buffered data
@param file previously opened file 
@return GL_SUCCESS or error code */
T_GL_ERROR_CODE GL_File_Flush(T_GL_HFILE file) GL_EXCEPTION;

/** Checks if the file is existing
@param name complete filename of the file (See @ref GL_Widget_Url for the url coding)
@return GL_SUCCESS or error code */
T_GL_ERROR_CODE GL_File_Exists(const char* name) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_File_h_INCLUDED
