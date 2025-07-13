#ifndef _BARCODE_H
#define _BARCODE_H


#ifdef __cplusplus
extern "C" {
#endif

#include "QR_Decoder.h"
/*! @addtogroup DOC_BARCODE
* @{ **/
 
// 1D barcode

/*! @name 1D Barcodes
 * @brief BarCode library provides functions to print a string of characters in Code 128 
 * norm,  Code 39 norm and Code 2 interleaved 5 norm. It allows the configuration of the vertical 
 * and horizontal size, the choice of the justification and the direction. It also allows to print the 
 * content of the Barcode. 

* @{ **/
	
// Code128

#ifndef _DEPRECATED_AVL_BARCODE_SDK090800_
#define PrintBarCode128(a,b,c,d,e,f) ERROR_Deprecation_For_ModuleAVLBarcode_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module AVL Barcode. You can remove this error by adding _DEPRECATED_AVL_BARCODE_SDK090800_. Please do the necessary to clean your code.*/
#else
/*! @brief AVL Barcode will not be supported in Telium+ framework. Please use GOAL instead.*/
/*! @brief To continue to use this function add _DEPRECATED_AVL_BARCODE_SDK090800_ in you compilation defines.*/
/*! @brief This function prints a string of characters in the \b Code128 norm.

* @param Message Message to print <i>(Ascii characters)</i>
* @param Xsize Width of 1 unit in pixels <i>(width of 1 black bar or white bar)</i>
* @param Ysize Height of 1 unit in pixels <i>(height of 1 black bar or white bar)</i>
* @param Direction Direction of the barcode <i>(@c 0: horizontal, @c 1: vertical)</i>
* @param alignment Justification of the barcode <i>(@c 0: left, @c 1: center, @c 2: right)</i>
* @param PrintValue Prints the value of the barcode <i>(@c 0: no, @c 1: yes)</i>

* @return 
*  - @c 0: Message correctly printed; or
*  - @c -1: Message too long; or
*  - @c -2: String contains unknown characters; or
*  - @c -3: Wrong parameters
* @par Example:
*  The following will print a centered barcode that contains the message \a Test 

 * @include BarCode_Sample_01.c
* 
* @link DOC_BARCODE Back to top @endlink
**/

extern int  PrintBarCode128(unsigned char *Message,int Xsize,int Ysize,int Direction,int alignment, int PrintValue)MACRO_DEPRECATED;
#endif

#ifndef _DEPRECATED_AVL_BARCODE_SDK090800_
#define PrintBarCode25(a,b,c,d,e,f,g) ERROR_Deprecation_For_ModuleAVLBarcode_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module AVL Barcode. You can remove this error by adding _DEPRECATED_AVL_BARCODE_SDK090800_. Please do the necessary to clean your code.*/
#else
/*! @brief AVL Barcode will not be supported in Telium+ framework. Please use GOAL instead.*/
/*! @brief To continue to use this function add _DEPRECATED_AVL_BARCODE_SDK090800_ in you compilation defines.*/
// Code 2 interleaved 5
/*! @brief This function prints a string of characters in the \b Code25 norm.

* @param Message Message to print <i>(digit characters 0 to 9)</i>
* @param Xsize Width of 1 unit in pixels <i>(width of 1 black bar or white bar)</i>
* @param Ysize Height of 1 unit in pixels <i>(height of 1 black bar or white bar)</i>
* @param Direction Direction of the barcode <i>(@c 0: horizontal, @c 1: vertical)</i>
* @param alignment Justification of the barcode <i>(@c 0: left, @c 1: center, @c 2: right)</i>
* @param PrintValue Prints the value of the barcode <i>(@c 0: no, @c 1: yes)</i>
* @param checksum Adds a checksum at the end of the barcode <i>(@c 0 : no, @c 1: yes)</i>

* @return 
* - @c 0: Message correctly printed; or
* - @c -1: Message too long; or
* - @c -2: String contains unknown characters; or
* - @c -3: Wrong parameters

* @par Example:
* The following will print a centered barcode that contains the message \a 01234567

 * @include BarCode_Sample_02.c
* 
* @link DOC_BARCODE Back to top @endlink
**/

extern int  PrintBarCode25(unsigned char *Message,int Xsize,int Ysize,int Direction,int alignment, int PrintValue, int checksum)MACRO_DEPRECATED;
#endif

#ifndef _DEPRECATED_AVL_BARCODE_SDK090800_
#define PrintBarCode39(a,b,c,d,e,f) ERROR_Deprecation_For_ModuleAVLBarcode_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module AVL Barcode. You can remove this error by adding _DEPRECATED_AVL_BARCODE_SDK090800_. Please do the necessary to clean your code.*/
#else
/*! @brief AVL Barcode will not be supported in Telium+ framework. Please use GOAL instead.*/
/*! @brief To continue to use this function add _DEPRECATED_AVL_BARCODE_SDK090800_ in you compilation defines.*/

// Code39
/*! @brief This function prints a string of characters in the \b Code39 norm.

* @param Message Message to print <i>(uppercase letters (A through Z), numeric digits (0 through 9) and a special characters (-, ., $, /, +, %, and space))</i>
* @param Xsize Width of 1 unit in pixels <i>(width of 1 black bar or white bar)</i>
* @param Ysize Height of 1 unit in pixels <i>(height of 1 black bar or white bar)</i>
* @param Direction Direction of the barcode <i>(@c 0: horizontal, @c 1: vertical)</i>
* @param alignment Justification of the barcode <i>(@c 0: left, @c 1: center, @c 2: right)</i>
* @param PrintValue Prints the value of the barcode <i>(@c 0: no, @c 1: yes)</i>

* @return 
* - @c 0: Message correctly printed; or
* - @c -1: Message too long; or
* - @c -2: String embeds unknown characters; or
* - @c -3: Incoherent parameters
* @par Example:
* The following will print a centered barcode that contains the message \a TEST

 * @include BarCode_Sample_03.c
* 
* @link DOC_BARCODE Back to top @endlink
**/

extern int  PrintBarCode39(unsigned char *Message,int Xsize,int Ysize,int Direction,int alignment, int PrintValue)MACRO_DEPRECATED;


#endif

#ifndef _DEPRECATED_AVL_BARCODE_SDK090800_
#define PrintBarCodeEAN8(a,b,c,d,e,f) ERROR_Deprecation_For_ModuleAVLBarcode_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module AVL Barcode. You can remove this error by adding _DEPRECATED_AVL_BARCODE_SDK090800_. Please do the necessary to clean your code.*/
#else
/*! @brief AVL Barcode will not be supported in Telium+ framework. Please use GOAL instead.*/
/*! @brief To continue to use this function add _DEPRECATED_AVL_BARCODE_SDK090800_ in you compilation defines.*/
// 1D barcode EAN

/*! @brief This function prints a string of characters in the \b EAN8 norm.

* @param Message Message to print <i>(7 digits)</i>
* @param Xsize Width of 1 unit in pixels <i>(width of 1 black bar or white bar)</i>
* @param Ysize Height of 1 unit in pixels <i>(height of 1 black bar or white bar)</i>
* @param Direction Direction of the barcode <i>(@c 0: horizontal, @c 1: vertical)</i>
* @param alignment Justification of the barcode <i>(@c 0: left, @c 1: center, @c 2: right)</i>
* @param PrintValue Prints the value of the barcode <i>(@c 0: no, @c 1: yes)</i>

* @return 
* - @c 0: Message correctly printed; or
* - @c -1: Message too long; or
* - @c -2: String embeds unknown characters; or
* - @c -3: Incoherent parameters
* @par Example:
* The following will print a centered barcode that contains the message \a Test

 * @include BarCode_Sample_04.c
* 
* @link DOC_BARCODE Back to top @endlink
**/
extern int PrintBarCodeEAN8(unsigned char *Message,int Xsize,int Ysize,int Direction,int alignment, int PrintValue)MACRO_DEPRECATED;

#endif

#ifndef _DEPRECATED_AVL_BARCODE_SDK090800_
#define PrintBarCodeEAN13(a,b,c,d,e,f) ERROR_Deprecation_For_ModuleAVLBarcode_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module AVL Barcode. You can remove this error by adding _DEPRECATED_AVL_BARCODE_SDK090800_. Please do the necessary to clean your code.*/
#else
/*! @brief AVL Barcode will not be supported in Telium+ framework. Please use GOAL instead.*/
/*! @brief To continue to use this function add _DEPRECATED_AVL_BARCODE_SDK090800_ in you compilation defines.*/
/*! @brief This function prints a string of characters in the \b EAN13 norm.

* @param Message Message to print <i>(12 digits)</i>
* @param Xsize Width of 1 unit in pixels <i>(width of 1 black bar or white bar)</i>
* @param Ysize Height of 1 unit in pixels <i>(height of 1 black bar or white bar)</i>
* @param Direction Direction of the barcode <i>(@c 0: horizontal, @c 1: vertical)</i>
* @param alignment Justification of the barcode <i>(@c 0: left, @c 1: center, @c 2: right)</i>
* @param PrintValue Prints the value of the barcode <i>(@c 0: no, @c 1: yes)</i>

* @return 
* - @c 0: Message correctly printed; or
* - @c -1: Message too long; or
* - @c -2: String embeds unknown characters; or
* - @c -3: Incoherent parameters
* @par Example:
* The following will print a centered barcode that contains the message \a Test

 * @include BarCode_Sample_05.c
* 
* @link DOC_BARCODE Back to top @endlink
**/
extern int PrintBarCodeEAN13(unsigned char *Message,int Xsize,int Ysize,int Direction,int alignment, int PrintValue	)MACRO_DEPRECATED;
#endif

#ifndef _DEPRECATED_AVL_BARCODE_SDK090800_
#define PrintBarCodePDF417(a,b,c,d,e) ERROR_Deprecation_For_ModuleAVLBarcode_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module AVL Barcode. You can remove this error by adding _DEPRECATED_AVL_BARCODE_SDK090800_. Please do the necessary to clean your code.*/
#else
/*! @brief AVL Barcode will not be supported in Telium+ framework. Please use GOAL instead.*/
/*! @brief To continue to use this function add _DEPRECATED_AVL_BARCODE_SDK090800_ in you compilation defines.*/


/*! @}
* @name 2D Barcode
 * @brief BarCode library provides a function to print a PDF417 2D barcodes
*  @{ **/
	
// 2D barcode PDF417

/*! @brief The barcode library allows printing \b PDF417 barcodes on the EFT.
 	* @section PrintBarCodePDF417  

* @param BarCodeText Text to be converted into 2D barcode
* @param nrows, ncols The optional \a rows and \a cols arguments allow the user to specify number of rows <tt>(<=90 for 0 and 180 degrees, <=48 for 90 and 270 degrees)</tt> and number of columns <tt>(<=9)</tt> in the output barcode. 
* - If the rows are supplied <i>(not @c 0)</i>, then the columns must be also supplied. 
* - If these arguments are set to @c 0, the default is @c 24 rows and @c 9 columns. 
* - If rows are set to @c 999, the library will use as many rows as needed to generate the barcode.
* @param ecLevel Specifies the level of error correction to use. It is optionally supplied only if rows and columns are also supplied <i>(default: @c 5)</i>.
* @param rotate specifies the rotate (0, 90, 180, 270)
* 
* @return 
* - @c 0: OK; or
* - @c -1: Columns must be between @c 1 and @c 30, inclusive; or
* - @c -2: Rows must be between @c 3 and @c 90, inclusive; or
* - @c -3: Error Correction level should be from @c 1 to @c 8; or
* - @c -4: Size of barcode too large; or
* - @c -5: Data will not fit in @c 90 rows. Must reduce input data or use more columns; or
* - @c -6: Must have more than two columns; or
* - @c -7: Message length plus Error Code Length too big. Use larger row or column size. Or set \a rows = @c 999 for unlimited row size
* - @c -8 : Incorrect rotate
* - @c -9 : Size of barcode too large
* - @c -10 : Size of barcode too large

*  @par Example:
*  The following will print a 2D barcode that contains the message \a Test

 * @include BarCode_Sample_06.c
* 
* @link DOC_BARCODE Back to top @endlink
**/
extern int  PrintBarCodePDF417(unsigned char *BarCodeText,int nrows,int ncols,int ecLevel,int rotate)MACRO_DEPRECATED;
#endif

#ifndef _DEPRECATED_AVL_BARCODE_SDK090800_
#define Print_PDF417_BarCode(a,b,c,d) ERROR_Deprecation_For_ModuleAVLBarcode_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module AVL Barcode. You can remove this error by adding _DEPRECATED_AVL_BARCODE_SDK090800_. Please do the necessary to clean your code.*/
#else
/*! @brief AVL Barcode will not be supported in Telium+ framework. Please use GOAL instead.*/
/*! @brief To continue to use this function add _DEPRECATED_AVL_BARCODE_SDK090800_ in you compilation defines.*/

/*! @brief This function is the old format for PDF417 barcodes. Please see @ref PrintBarCodePDF417 for more information
* 
* @link DOC_BARCODE Back to top  @endlink
**/
extern int Print_PDF417_BarCode(unsigned char *BarCodeText,int nrows,int ncols,int ecLevel)MACRO_DEPRECATED;
#endif

#ifndef _DEPRECATED_AVL_BARCODE_SDK090800_
#define Print_QR_BarCode(a,b,c,d,e) ERROR_Deprecation_For_ModuleAVLBarcode_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for module AVL Barcode. You can remove this error by adding _DEPRECATED_AVL_BARCODE_SDK090800_. Please do the necessary to clean your code.*/
#else
/*! @brief AVL Barcode will not be supported in Telium+ framework. Please use GOAL instead.*/
/*! @brief To continue to use this function add _DEPRECATED_AVL_BARCODE_SDK090800_ in you compilation defines.*/

// 2D barcode QR

/*! @brief This function prints a QR barcode. 
 	* @section Print_QR_BarCode

 * @param BarCodeText Content of the barcode to print (null-terminated string)
 * @param BarCodeTextSize Size of the input buffer (with the \0 character included)
 * @param nsize Optional size arguments to specify
 * @param mode Encoding mode (0:Numeric mode, 1:Alphabet-numeric mode, 2:8-bit data mode, 3:Kanji (shift-jis) mode. If nsize is set to 0, default values are used depending from BarCodeText
 * @param ecLevel Level of error correction to use. It is optionnaly supplied only if rows and columns are also supplied.
* @return 
* - @c 0  : OK
* - @c -1 : size must be between 63 and 384, inclusive
* - @c -2 : Failed to encode BarCodeText
* - @c -3 : Error Correction level should be from 0 to 4
* - @c -4 : Encode mode should be from 0 to 4
* - @c -5 : Data will not fit in 90 rows. Must reduce input data or use more columns
* - @c -6 : Must have more than two columns
* - @c -7 : Message length plus Error Code Length too big:
 * - Use larger row or column size
 * - Or set rows = 999 for unlimited row size
* - @c -8 : Incorrect rotate
* - @c -9 : Size of barcode too large
* - @c -10 : Failed to encode BarCodeText
* - @c -11 : QRDecoder DLL not present

* @note @b The DLL 844096xxx must be loaded in the terminal./@b This DLL is provided in the SDK in the directory component\\AVL\\Barcode\\QR.

*  @par Example:
*  The following will print a 2D barcode that contains the message \a Test

 * @include BarCode_Sample_07.c
*
* @link DOC_BARCODE Back to top @endlink
**/
extern int Print_QR_BarCode(unsigned char *BarCodeText, unsigned int BarCodeTextSize,int nsize,QRencodeMode mode,QRecLevel ecLevel)MACRO_DEPRECATED;
#endif

/*! @}
*  @} **/

#ifdef __cplusplus
}
#endif

#endif
