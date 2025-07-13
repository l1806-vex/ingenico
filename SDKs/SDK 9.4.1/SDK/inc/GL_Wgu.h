// $Id: GL_Wgu.h,v 1.1.2.2 2012/01/06 10:27:30 rbertholet Exp $

#ifndef GL_Wgu_h_INCLUDED
#define GL_Wgu_h_INCLUDED

/** 
@defgroup GL_WguImage WGU Image format
@{
*/

#define GL_WGU_TYPE 0x00554757 ///< Wgu image type is equal to string "WGU\0" (see @ref T_GL_WGU_HEADER)

#define GL_WGU_FORMAT_8_BPP  1 ///< Image format : binary = AARRGGBB => 1 byte per pixel (A=alpha, R=red, G=green, B=blue) (see @ref T_GL_WGU_HEADER)
#define GL_WGU_FORMAT_16_BPP 2 ///< Image format : binary = AAAARRRR GGGGBBBB => 2 bytes per pixel (little endian) (A=alpha, R=red, G=green, B=blue) (see @ref T_GL_WGU_HEADER)
#define GL_WGU_FORMAT_24_BPP 3 ///< Image format : binary = RRRRRRAA GGGGGGAA BBBBBBAA => 3 bytes per pixel (little endian) (A=alpha, R=red, G=green, B=blue) (see @ref T_GL_WGU_HEADER)
#define GL_WGU_FORMAT_32_BPP 4 ///< Image format : binary = AAAAAAAA RRRRRRRR GGGGGGGG BBBBBBBB => 4 bytes per pixel (little endian) (A=alpha, R=red, G=green, B=blue) (see @ref T_GL_WGU_HEADER)

#define GL_WGU_COMBINE    0x0000004 ///< undraw flag : leaves the image displayed before displaying the next image (see @ref T_GL_WGU_HEADER)
#define GL_WGU_REPLACE    0x0000008 ///< undraw flag : replaces the image displayed by the background before displaying the next image (see @ref T_GL_WGU_HEADER)
#define GL_WGU_PREVIOUS   (GL_WGU_REPLACE | GL_WGU_COMBINE) ///< undraw flag : replaces the previously displayed image before displaying the next image  (see @ref T_GL_WGU_HEADER)

/** Header of the WGU image file, the bitmap length is computed according to (width * height * format),
the bitmap datas follow the header and are codding according to the specified format.
An animated images is a concatenation of WGU images in a single file.
To create a WGU image with an image coded in anoter format, you can use the tools :
 - PictureOptimizer.exe : graphical tools
 - ImageOptimizer.exe : console tools ("ImageOptimizer.exe --help" to get the online help) */
typedef struct T_GL_WGU_HEADER
{
	/** Type format "WGU\0" (see @ref GL_WGU_TYPE) */
	unsigned long type;

	/** Image format (see @ref GL_WGU_FORMAT_8_BPP, @ref GL_WGU_FORMAT_16_BPP, @ref GL_WGU_FORMAT_24_BPP, @ref GL_WGU_FORMAT_32_BPP) */
	unsigned long format;
	
	/** Image width in pixels */
	unsigned long width;
	
	/** Image height in pixels */
	unsigned long height;
	
	/** X position in pixels (this value is used only with animated image)*/
	unsigned long x;
	
	/** Y position in pixels (this value is used only with animated image)*/
	unsigned long y; 
	
	/** Display duration in milliseconds (this value is used only with animated image) */
	unsigned long delay;
	
	/** Flags (this value is used only with animated image) (see @ref GL_WGU_COMBINE, @ref GL_WGU_REPLACE, @ref GL_WGU_PREVIOUS) */
	unsigned long flags;

	/** Loop (this value is used only with animated image) */
	unsigned long loop;
	
	/** Total image width in pixels */
	unsigned long totalWidth;
	
	/** Total image height in pixels */
	unsigned long totalHeight;
	
	/** Reserved word */
	unsigned long reserved[5];
} T_GL_WGU_HEADER;


/** 
@}
*/

#endif // GL_Wgu_h_INCLUDED
