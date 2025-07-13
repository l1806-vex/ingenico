// $Id: GL_SignatureFile.h,v 1.1.2.7 2012/12/17 09:51:23 rbertholet Exp $
// Signature file management
#ifndef GL_SignatureFile_h_INCLUDED
#define GL_SignatureFile_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_SignatureFile 
@{
@addtogroup GL_SignatureFileDoc Signature file
@{

This class is used to extract data from a file signature. 
If you specify a size of the destination area to zero, all the data returned by the @ref GL_SignatureFile_GetPoint 
correspond to real data recorded. 
If you specify a size of the destination area, the coordinates are then adapted to optimally occupied the area specified.

To capture a signature see @ref GL_Signature widget or @ref GL_Dialog_Signature.

WARNING : the pressure is not supported on all touch, it depends on the terminal which has acquired.

Sample to read the signature file :


 * @include GL_SignatureFile_Sample_01.c
@}
*/

/** Signature file handle */
typedef struct T_TL_SIGNATURE * T_GL_HSIGNATURE;

/** Opens a file signature
@param filename signature file name (See @ref GL_Widget_Url for the url coding)
@param width width in pixels of the destination area or 0 to obtain the touch coordinates
@param height height in pixels of the destination area or 0 to obtain the touch coordinates
@return the open file handle or null if the file could not be opened */
T_GL_HSIGNATURE GL_SignatureFile_Open(const char * filename, unsigned long width, unsigned long height) GL_EXCEPTION;

/** Closes a file signature
@param signature signature file handle */
void GL_SignatureFile_Close(T_GL_HSIGNATURE signature) GL_EXCEPTION;

/** Gets the content of a point, each call of this function returns a next point.
@param signature signature handle
@param x X touch coordinate of point or coordinate calculated according to the destination area
@param y Y touch coordinate of point or coordinate calculated according to the destination area
@param pressure Stylus pressure, the up of the stylus is represented by a zero pressure
@param pressure Stylus pressure (16 MSB indicates pressure, LSB indicates contact : 1 is no contact with the touch 0 is contact)
@param time Time of point
@return return true until a point has been read */
bool GL_SignatureFile_GetPoint(T_GL_HSIGNATURE signature, unsigned long *x, unsigned long *y, unsigned long *pressure, unsigned long *time) GL_EXCEPTION;

/** Gets the size of the touch
@param signature signature handle
@param width touch resolution width
@param height touch resolution height */
void GL_SignatureFile_GetTouchSize(T_GL_HSIGNATURE signature, unsigned long * width, unsigned long * height) GL_EXCEPTION;

/** Gets the size in pixels of the screen
@param signature signature handle
@param width screen resolution width
@param height screen resolution height */
void GL_SignatureFile_GetScreenSize(T_GL_HSIGNATURE signature, unsigned long * width, unsigned long * height) GL_EXCEPTION;

/** Gets the minimum and maximum boundaries of the signature
@param signature signature handle
@param xMin x minimal touch coordinates
@param yMin y minimal touch coordinates
@param xMax x maximal touch coordinates
@param yMax y maximal touch coordinates */
void GL_SignatureFile_GetBound(T_GL_HSIGNATURE signature, unsigned long *xMin, unsigned long *yMin, unsigned long *xMax, unsigned long *yMax) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_SignatureFile_h_INCLUDED
