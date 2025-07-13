/*! @addtogroup KSFAM_FONTLIB
	* @{
**/
#ifndef FONTLIB_H
#define FONTLIB_H

#define		_dSMALL_		"_dSMALL_"
#define		_dMEDIUM_		"_dMEDIUM_"
#define		_dLARGE_		"_dLARGE_"
#define		_dXLARGE_		"_dXLARGE_"
#define		_pNORMAL_		"_pNORMAL_"
#define		_pBOLD_			"_pBOLD_"
#define		_pLARGE_		"_pLARGE_"
#define		_pCONDENSED_	"_pCONDENSED_"

#define		_dPOLICE5x5_	"_dPOLICE5x5_"
#define		_dPOLICE4x7_	"_dPOLICE4x7_"
#define		_dPOLICE5x7_	"_dPOLICE5x7_"
#define		_dPOLICE6x8_	"_dPOLICE6x8_"
#define		_dPOLICE7x8_	"_dPOLICE7x8_"
#define		_dPOLICE8x12_	"_dPOLICE8x12_"
#define		_dPOLICE8x14_	"_dPOLICE8x14_"

#define FONT_SIZE_LENGTH 14
#define FONT_NAME_LENGTH 10
/*! @brief Describes FontInfo structure.*/
typedef struct {
	char FontSize[FONT_SIZE_LENGTH];				/*!<  Font type.*/
	short Width;														/*!< character width.*/
	short Height;														/*!<  character height.*/
	short Xspacing;													/*!<  horizontal spacing between 2 characters.*/
	short Yspacing;													/*!<  vertical spacing between 2 characters.*/
	short NbChar;														/*!<  font character number.*/
	long FontOffset;												/*!<  font position in the file.*/
} tm_FontInfo;

/*! @brief Describes FontHeader structure.*/
typedef struct {
	short FileId;														/*!< file identification (0x1BF5).*/
	short FileVersion;											/*!< file version (0x0102).*/
	char FileName[FONT_NAME_LENGTH];				/*!< file name.*/
	short FileFormat;												/*!< file format is Unicode or one of the ISO8859 character sets.*/
	short RTL;															/*!< RTL is the display/print direction: right to left or left to right.*/
	short NbFont;														/*!< number of font contained in the file.*/
} tm_FontHeader;



/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function is used to get the length of an Unicode coded string
 *	@param *string: address of formatted string. string must be coded in Unicode big endian.
 *	@return The string length.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 59) if function does not exist
// \if SIMULATION
//  strlenUNICODE:KSFAM_FONTLIB:0x1D
// \endif
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
extern int	strlenUNICODE(char *string);


/*! @brief This function copies a Unicode coded string to another string
 *	@param *strDestination : destination string.
 *	@param *strSource : null-terminated source string (Unicode coded).
 *	@return The destination string.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 60) if function does not exist
// \if SIMULATION
//  strcpyUNICODE:KSFAM_FONTLIB:0x1C
// \endif
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
extern char *strcpyUNICODE( char *strDestination, char *strSource );


/*! @brief This function appends a Unicode coded string
 *	@param *strDestination : Null-terminated destination string (Unicode coded).
 *	@param *strSource : Null-terminated source string (Unicode coded).
 *	@return The destination string.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 61) if function does not exist
// \if SIMULATION
//  strcatUNICODE:KSFAM_FONTLIB:0x1B
// \endif
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
extern char *strcatUNICODE( char *strDestination, char *strSource );


/*! @brief This function loads a signed font file in memory
 *	@param FileFontName : full name of the font file (ex : '/SYSTEM/ISO5.SGN')
 *	@return A buffer that contains the loaded font file or NULL error code.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 67) if function does not exist
// \if SIMULATION
//  @GSIM_F:LoadFont:KSFAM_FONTLIB:0x01
//  @GSIM_A:0:ONE_ADDRESS
// \endif
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
extern char *LoadFont(char *FileFontName);


/*! @brief This function searches the first font in the terminal
 *	@param FileFontName : full name of the font file (ex : '/SYSTEM/ISO5.SGN')
 *	@return 
 * - != 0 if ok.
 * - 0 if no font loaded.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 114) if function does not exist
// \if SIMULATION
//  @GSIM_F:FontFindFirst:KSFAM_FONTLIB:0x1F
// \endif
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
extern int   FontFindFirst(char *FileFontName);


/*! @brief This function searches the next font in the terminal.
 *	@param FileFontName : full name of the font file (ex : '/SYSTEM/ISO5.SGN')
 *	@return 
 * - != 0 if ok.
 * - 0 if no font loaded.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 115) if function does not exist
// \if SIMULATION
//  @GSIM_F:FontFindNext:KSFAM_FONTLIB:
// \endif
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
extern int   FontFindNext(char *FileFontName);


/*! @brief This function searches the first police in the font.
 *	@param Police : police found.
 *	@param BufferBitMap : bitmap font.
 *	@param CurrentFontInfo : pointer to structure FontInfo
 *	@param CurrentHeader : pointer to structure FontHeader
 *	@return 
 * - != 0 if ok.
 * - 0 if no font loaded.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 116) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PoliceFindFirst:KSFAM_FONTLIB:
//  @GSIM_A:1:DATA_CODE(strlen(Police)+1)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:DATA_SIZE(8192)
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
// \endif
extern int   PoliceFindFirst(char *Police, unsigned char *BufferBitMap, tm_FontInfo *CurrentFontInfo, tm_FontHeader *CurrentHeader);


/*! @brief This function searches the next police in the font.
 *	@param Police : police found.
 *	@param BufferBitMap : bitmap font.
 *	@param CurrentFontInfo : pointer to structure FontInfo
 *	@param CurrentHeader : pointer to structure FontHeader
 *	@return 
 * - != 0 if ok.
 * - 0 if no font loaded.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 117) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PoliceFindNext:KSFAM_FONTLIB:
//  @GSIM_A:1:DATA_CODE(strlen(Police)+1)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:DATA_SIZE(8192)
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
// \endif
extern int   PoliceFindNext(char *Police, unsigned char *BufferBitMap, tm_FontInfo *CurrentFontInfo, tm_FontHeader *CurrentHeader);


/*! @brief This function unloads the font.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 111) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:UnloadFont:KSFAM_FONTLIB:0x23
// \endif
extern int   UnloadFont(char *FileFontPtr);


/*! @brief This function is used to register the font used by the application
 *	@param *MyFont : address of the loaded font used by the application
 *	@return
 * -   0 : OK.
 * -  -1 : MyFont is not a loaded FON file (use LoadFont to load it).
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 53) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DefCurrentFont:KSFAM_FONTLIB:0x02
//  @GSIM_A:1:ONE_ADDRESS
// \endif
extern int	DefCurrentFont(char *MyFont);


/*! @brief This function is used to get the current font.
 *	@return The current font :
 * - '_dSMALL_', '_dMEDIUM_', '_dLARGE_', '_dXLARGE_', '_pNORMAL_', '_pBOLD_', '_pLARGE_', '_pCONDENSED_', OR
 * - '_dPOLICE5x5_', '_dPOLICE4x7_', '_dPOLICE5x7_', '_dPOLICE6x8_', '_dPOLICE7x8_', '_dPOLICE8x12_', '_dPOLICE8x14_'
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 75) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetCurrentFont:KSFAM_FONTLIB:0x14
//  @GSIM_A:0:ONE_ADDRESS
// \endif
extern char *GetCurrentFont(void);


/*! @brief This function places a UNICODE text in the graphic context at x and y position with or without reverse video option with the selected font and type.
 * - ('\\n') 0x00, 0x0A go to next line
 * - ('\\r') 0x00, 0x0D go to beginning of line
 * - Escape character ( \\x1B ) is not handled.
 *
 *	@param x0 : horizontal position in pixel (in range [0,127])
 *	@param y0 : vertical position in pixel (in range [0,63] or [0,127])
 *	@param *message : address of formatted string to be displayed. Message 
//! must be coded in Unicode big endian. 
 *	@param reverse : reverse video mode ( _ON_ or _OFF_ )
 *	@param police :
 *	- _dMEDIUM_, _dLARGE_, _dSMALL_
 *	- _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_
 *
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_
 *	@return 
 *	- Error Code     Description
 *	- 0              OK
 *	- -1             The font is not in the font file : nothing is displayed.
 *	- -2             A character of the message is not in the font. Message is displayed without missing characters.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 66) if function does not exist
 *
 *	@note 
 *	DrawExtendedStringUnicode includes a call to PaintGraphics function.
 *
 *	In order to optimize the time to display a screen, it is recommended to work on the full screen by using _DrawExtendedStringUnicode function and just paint at the end. 
 *
 *	In other words, strings can be inserted at different x and y position to build the full screen and when everything 
    is done, paint routine can then be called.
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawExtendedStringUnicode:KSFAM_FONTLIB:0x03
//  @GSIM_A:3:DATA_CODE(2*strlenUNICODE(message)+2)
//  @GSIM_A:3:IN_ONLY
//  @GSIM_A:5:DATA_CODE(strlen(police)+1)
//  @GSIM_A:5:IN_ONLY
// \endif
extern int	DrawExtendedStringUnicode(int x0,int y0,unsigned char *message,int reverse,char *police,int type);


/*! @brief This function places a UNICODE text in the graphic context at x and y position with or without reverse video option with the selected font and type.
 * - ('\\n') 0x00, 0x0A go to next line
 * - ('\\r') 0x00, 0x0D go to beginning of line
 * - Escape character ( \\x1B ) is not handled.
 *	@param x0 : horizontal position in pixel (in range [0,127])
 *	@param y0 : vertical position in pixel (in range [0,63] or [0,127])
 *	@param *message : address of formatted string to be displayed. Message must be coded in Unicode big endian. 
 *	@param reverse : reverse video mode ( _ON_ or _OFF_ )
 *	@param police :
 * -  _dMEDIUM_, _dLARGE_, _dSMALL_
 * -  _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_.
 *	@return
 * - Error Code     Description
 * - 0              OK
 * - -1             The font is not in the font file : nothing is displayed.
 * - -2             A character of the message is not in the font. Message is displayed without missing characters.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 56) if function does not exist
 *	@note 
 *	DrawExtendedStringUnicode includes a call to PaintGraphics function.
 *
 *	In order to optimize the time to display a screen, it is recommended to work on the full screen by using _DrawExtendedStringUnicode function and just paint at the end. 
 *
 *	In other words, strings can be inserted at different x and y position to build the full screen and when everything is done, paint routine can then be called.
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawExtendedStringUnicode:KSFAM_FONTLIB:0x08
//  @GSIM_A:3:DATA_CODE(2*strlenUNICODE(message)+2)
//  @GSIM_A:3:IN_ONLY
//  @GSIM_A:5:DATA_CODE(strlen(police)+1)
//  @GSIM_A:5:IN_ONLY
// \endif
extern int	_DrawExtendedStringUnicode(int x0,int y0,unsigned char *message,int reverse,char *police,int type);


/*! @brief This function places a ISO 8859 coded text in the graphic context at x and y position with or without reverse video option with the selected font and type.
 * - ('\\n') 0x0A go to next line
 * - ('\\r') 0x0D go to beginning of line
 * - Escape character ( \\x1B ) is not handled.
 *	@param x0 : horizontal position in pixel (in range [0,127])
 *	@param y0 : vertical position in pixel (in range [0,63] or [0,127])
 *	@param *message : address of formatted string to be displayed. Message must be coded in ISO 8859.
 *	@param reverse : reverse video mode ( _ON_ or _OFF_ )
 *	@param police :
 * - _dMEDIUM_, _dLARGE_, _dSMALL_
 * - _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_.
 *	@return
 * -  Error Code     Description
 * -  0              OK
 * -  -1             The font is not in the font file : nothing is displayed.
 * -  -2             A character of the message is not in the font. Message is displayed without missing characters.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 54) if function does not exist
 *	@note 
 *	DrawExtendedString8859 includes a call to PaintGraphics function.
 *
 *	In order to optimize the time to display, it is recommended to work on the full screen by using _DrawExtendedString8859 function and just paint at the end. 
 *
 *	In other words, strings can be inserted at different x and y position to build the full screen and when everything is done, paint routine can then be called.
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawExtendedString8859:KSFAM_FONTLIB:0x05
//  @GSIM_A:3:DATA_CODE(strlen(message)+1)
//  @GSIM_A:3:IN_ONLY
//  @GSIM_A:5:DATA_CODE(strlen(police)+1)
//  @GSIM_A:5:IN_ONLY
// \endif
extern int	DrawExtendedString8859(int x0,int y0,unsigned char *message,int reverse,char *police,int type);


/*! @brief This function places an ISO 8859 coded text in the graphic context at x and y position with or without reverse video option with the selected font and type.
 * - ('\\n') 0x0A go to next line.
 * - ('\\r') 0x0D go to beginning of line.
 * - Escape character ( \\x1B ) is not handled.
 *	@param x0 : horizontal position in pixel (in range [0,127])
 *	@param y0 : vertical position in pixel (in range [0,63] or [0,127])
 *	@param *message : address of formatted string to be displayed. Message must be coded in ISO 8859.
 *	@param reverse : reverse video mode ( _ON_ or _OFF_ )
 *	@param police :
 * - _dMEDIUM_, _dLARGE_, _dSMALL_
 * - _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_.
 *	@return
 * -  Error Code     Description
 * -  0              OK
 * -  -1             The font is not in the font file : nothing is displayed.
 * -  -2             A character of the message is not in the font. Message is displayed without missing characters.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 55) if function does not exist
 *	@note
 *	_DrawExtendedString8859 includes a call to PaintGraphics function.
 *
 *	In order to optimize the time to display, it is recommended to work on the full screen by using _DrawExtendedString8859 function and just paint at the end. 
 *
 *	In other words, strings can be inserted at different x and y position to build the full screen and when everything is done, paint routine can then be called.
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawExtendedString8859:KSFAM_FONTLIB:0x09
//  @GSIM_A:3:DATA_CODE(strlen(message)+1)
//  @GSIM_A:3:IN_ONLY
//  @GSIM_A:5:DATA_CODE(strlen(police)+1)
//  @GSIM_A:5:IN_ONLY
// \endif
extern int	_DrawExtendedString8859(int x0,int y0,unsigned char *message,int reverse,char *police,int type);


/*! @brief This function prints a UNICODE text with or without reverse video option with the selected font and type.
 *	@param *message : address of formatted string to be printed. Message must be coded in Unicode big endian.
 *	@param reverse : reverse video mode ( _ON_ or _OFF_ )
 *	@param *police :  
//! _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_,
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_
 *	@return
 * -  Error Code     Description
 * -  0              OK
 * -  -1             The font is not in the font file : nothing is printed.
 * -  -2             A character of the message is not in the font. Message is printed without missing characters.
 * -  -3             Margins are too big : nothing is printed.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 58) if function does not exist
 *	@note The message is printed when a new-line character ( \\x00\\n or \\x00\\x0A) is reached.
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:pprintfUnicode:KSFAM_FONTLIB:0x04
//  @GSIM_A:1:DATA_CODE(2*strlenUNICODE(message)+2)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:3:DATA_CODE(strlen(police)+1)
//  @GSIM_A:3:IN_ONLY
// \endif
extern int	pprintfUnicode(unsigned char *message,int reverse,char *police,int type);


/*! @brief This function places a Unicodecoded text in the graphic context at current position with or without reverse video option with the selected font and type. 
 *	@param message : pointer on formatted string to be printed. message must be coded in Unicode.
 *	@param reverse : reverse video mode ( _ON_ or _OFF_ )
 *	@param police : _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_...
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_ 
 *	@return 
 * -   Error Code     Description
 * -   0              OK
 * -   -1             The font is not in the font file : nothing is printed.
 * -   -2             A character of the message is not in the font. Message is printed without missing characters.
 * -   -3             Margins are too big : nothing is printed. 
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 84) if function does not exist
 *	@note The message is printed when a new-line character ( \\x00\\n or \\x00\\x0A) is reached.
 *	@note _pprintf8859 and _pprintfUnicode functions are the same functions as pprintf8859 and pprintfUnicode but they are used to print in a graphic context. 
 *	@note At startup current position is (0,0)
 *	@note PaintPrinterGraphics reset current position
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_pprintfUnicode:KSFAM_FONTLIB:0x13
//  @GSIM_A:1:DATA_CODE(2*strlenUNICODE(message)+2)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:3:DATA_CODE(strlen(police)+1)
//  @GSIM_A:3:IN_ONLY
// \endif
extern int	_pprintfUnicode(unsigned char *message,int reverse,char *police,int type);


/*! @brief This function places a Unicodecoded text in the graphic context at x and y position with or without reverse video option with the selected font and type. 
 *	@param Xuser : horizontal position in pixel (in range [0,383])
 *	@param Yuser : vertical position in pixel (in range [0,bitmap height])
 *	@param message : pointer on formatted string to be printed. message must be coded in Unicode.
 *	@param reverse : reverse video mode ( _ON_ or _OFF_ )
 *	@param police : _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_...
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_ 
 *	@return 
 * -   Error Code     Description
 * -   0              OK
 * -   -1             The font is not in the font file : nothing is printed.
 * -   -2             A character of the message is not in the font. Message is printed without missing characters.
 * -   -3             Margins are too big : nothing is printed. 
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 83) if function does not exist
 *	@note
 *	_pprintf8859 and _pprintfUnicode functions are the same functions as pprintf8859 and pprintfUnicode but they are used to print in a graphic context. 
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_pprintfUnicodeXY:KSFAM_FONTLIB:0x12
//  @GSIM_A:3:DATA_CODE(2*strlenUNICODE(message)+2)
//  @GSIM_A:3:IN_ONLY
//  @GSIM_A:5:DATA_CODE(strlen(police)+1)
//  @GSIM_A:5:IN_ONLY
// \endif
extern int	_pprintfUnicodeXY(int Xuser,int Yuser,unsigned char *message,int reverse,char *police,int type);


/*! @brief This function places an ISO 8859 coded text in the graphic context at current position with or without reverse video option with the selected font and type. 
 *	@param message : pointer on formatted string to be printed. message must be coded in ISO 8859. 
 *	@param reverse : reverse video mode ( _ON_ or _OFF_ )
 *	@param police : _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_...
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_ 
 *	@return 
 *	- Error Code     Description
 *	- 0              OK
 *	- -1             The font is not in the font file : nothing is printed.
 *	- -2             A character of the message is not in the font. Message is printed without missing characters.
 *	- -3             Margins are too big : nothing is printed. 
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 20) if function does not exist
 *	@note The message is printed when a new-line character ( \n or \\r) is reached.
 *	@note The function doesn't wait for the end of impression 
 *	@note __pprintf8859 function is the same function as pprintf8859 but the function doesn't wait for the end of impression
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:__pprintf8859:KSFAM_FONTLIB:0x10
//  @GSIM_A:1:DATA_CODE(strlen(message)+1)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:3:DATA_CODE(strlen(police)+1)
//  @GSIM_A:3:IN_ONLY
// \endif
extern int	__pprintf8859(unsigned char *message,int reverse,char *police,int type);


/*! @brief This function prints an ISO 8859 coded text with or without reverse video option with the selected font and type.
 *	@param *message : address of formatted string to be printed. Message must be coded in ISO 8859.
 *	@param reverse : reverse video mode ( _ON_ or _OFF_ )
 *	@param *police : _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_,
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_
 *	@return
//! - Error Code     Description
//! - 0              OK
//! - -1             The font is not in the font file : nothing is printed.
//! - -2             A character of the message is not in the font. Message is printed without missing characters.
//! - -3             Margins are too big : nothing is printed.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 57) if function does not exist
 *	@note This function wait for the end of impression 
 *	@note 
 *	The message is printed when a new-line character ( \\n ) is reached.
 *  The function wait the end of impression by calling ttestall.
 *  The function use 0xF0 to 0xFF characters to redefine bitmaps with defprinterpatternHR
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:pprintf8859:KSFAM_FONTLIB:0x06
//  @GSIM_A:1:DATA_CODE(strlen(message)+1)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:3:DATA_CODE(strlen(police)+1)
//  @GSIM_A:3:IN_ONLY
// \endif
extern int	pprintf8859(unsigned char *message,int reverse,char *police,int type);


/*! @brief This function places an ISO 8859 coded text in the graphic context at current position with or without reverse video option with the selected font and type. 
 *	@param message : pointer on formatted string to be printed. message must be coded in ISO 8859. 
 *	@param reverse : reverse video mode ( _ON_ or _OFF_ )
 *	@param police : _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_...
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_ 
 *	@return 
 *	- Error Code     Description
 *	- 0              OK
 *	- -1             The font is not in the font file : nothing is printed.
 *	- -2             A character of the message is not in the font. Message is printed without missing characters.
 *	- -3             Margins are too big : nothing is printed. 
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 86) if function does not exist
 *	@note The message is printed when a new-line character ( \n or \\r) is reached.
 *	@note _pprintf8859 and _pprintfUnicode functions are the same functions as pprintf8859 and pprintfUnicode 
    but they are used to print in a graphic context. 
 *	@note At startup current position is (0,0)
 *	@note PaintPrinterGraphics reset current position
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_pprintf8859:KSFAM_FONTLIB:0x10
//  @GSIM_A:1:DATA_CODE(strlen(message)+1)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:3:DATA_CODE(strlen(police)+1)
//  @GSIM_A:3:IN_ONLY
// \endif
extern int	_pprintf8859(unsigned char *message,int reverse,char *police,int type);


/*! @brief This function places an ISO 8859 coded text in the graphic context at x and y position with or without reverse video option with the selected font and type. 
 *	@param Xuser : horizontal position in pixel (in range [0,383]).
 *	@param Yuser : vertical position in pixel (in range [0,bitmap height]).
 *	@param message : pointer on formatted string to be printed. message must be coded in ISO 8859. 
 *	@param reverse : reverse video mode ( _ON_ or _OFF_ )
 *	@param police : _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_...
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_ 
 *	@return 
 *	- Error Code     Description
 *	- 0              OK
 *	- -1             The font is not in the font file : nothing is printed.
 *	- -2             A character of the message is not in the font. Message is printed without missing characters.
 *	- -3             Margins are too big : nothing is printed. 
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 85) if function does not exist
 *	@note _pprintf8859 and _pprintfUnicode functions are the same functions as pprintf8859 and pprintfUnicode 
    but they are used to print in a graphic context. 
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_pprintf8859XY:KSFAM_FONTLIB:0x11
//  @GSIM_A:3:DATA_CODE(strlen(message)+1)
//  @GSIM_A:3:IN_ONLY
//  @GSIM_A:5:DATA_CODE(strlen(police)+1)
//  @GSIM_A:5:IN_ONLY
// \endif
extern int	_pprintf8859XY(int Xuser,int Yuser,unsigned char *message,int reverse,char *police,int type);


/*! @brief This functions defines the printer's margins.
 *	@param Left : value of the left margin (in pixel).
 *	@param Right : value of the right margin (in pixel).
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 74) if function does not exist
 *	@note Printer width is 384 pixels. Left + Right margins must be less than 384 pixels.
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DefPrinterMargins:KSFAM_FONTLIB:0x0D
// \endif
extern void DefPrinterMargins(int Left,int Right);


/*! @brief This function prints all the characters of a font contained in a FON file.
 *	@param *Police : _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_.
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_
 *	@return 
 *	- 0 : OK
 *	- -1 : the specified font is not in the FON file
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 62) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PrintPolice:KSFAM_FONTLIB:0x07
//  @GSIM_A:1:DATA_CODE(strlen(Police)+1)
//  @GSIM_A:1:IN_ONLY
// \endif
extern int	PrintPolice(char *Police,int type);


/*! @brief This function is used to get the size in pixels of an Unicode coded message.
 *	@param *message : Unicode coded message
 *	@param *police : font for message displaying/printing
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_.
 *	@return 
 *	- Unicode message size in pixels.
 *	- -1: the specified font is not in the font file used by the application.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 63) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SizeOfUnicodeString:KSFAM_FONTLIB:0x0A
//  @GSIM_A:1:DATA_CODE(2*strlenUNICODE(message)+2)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:DATA_CODE(strlen(police)+1)
//  @GSIM_A:2:IN_ONLY
// \endif
extern int	SizeOfUnicodeString(unsigned char *message,char *police,int type);


/*! @brief This function is used to get the size in pixels of an Unicode coded message.
 *	@param *BufferFont : Font
 *	@param *message : Unicode coded message
 *	@param *police : font for message displaying/printing
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_.
 *	@return 
 *	- Unicode message size in pixels.
 *	- -1: the specified font is not in the font file used by the application.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 118) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SizeOfUnicodeFontString:KSFAM_FONTLIB:
//  @GSIM_A:1:DATA_SIZE(8192)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:DATA_CODE(2*strlenUNICODE(message)+2)
//  @GSIM_A:2:IN_ONLY
//  @GSIM_A:3:DATA_CODE(strlen(police)+1)
//  @GSIM_A:3:IN_ONLY
// \endif
extern int	SizeOfUnicodeFontString(unsigned char *BufferFont,unsigned char *message,char *police,int type);


/*! @brief This function is used to get the size in pixels of an ISO8859 coded message
 *	@param *message : Unicode coded message.
 *	@param *police : font for message displaying/printing.
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_.
 *	@return
 *	- ISO8859 message size in pixels.
 *	- -1: the specified font is not in the font file used by the application.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 64) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SizeOfISO8859String:KSFAM_FONTLIB:0x0B
//  @GSIM_A:1:DATA_CODE(strlen(message)+1)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:DATA_CODE(strlen(police)+1)
//  @GSIM_A:2:IN_ONLY
// \endif
extern int	SizeOfISO8859String(unsigned char *message,char *police,int type);


/*! @brief This function is used to get the size in pixels of an ISO8859 coded message
 *	@param *BufferFont : Font
 *	@param *message : Unicode coded message.
 *	@param *police : font for message displaying/printing.
 *	@param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_.
 *	@return
 *	- ISO8859 message size in pixels.
 *	- -1: the specified font is not in the font file used by the application.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 119) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SizeOfISO8859FontString:KSFAM_FONTLIB:
//  @GSIM_A:1:DATA_SIZE(8192)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:DATA_CODE(strlen(message)+1)
//  @GSIM_A:2:IN_ONLY
//  @GSIM_A:3:DATA_CODE(strlen(police)+1)
//  @GSIM_A:3:IN_ONLY
// \endif
extern int	SizeOfISO8859FontString(unsigned char *BufferFont,unsigned char *message,char *police,int type);


/*! @brief This function is used to get the height in pixels of a font
 *	@param *police : _dMEDIUM_, _dLARGE_, _dSMALL_
 _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_
 *	@return 
 *	- font height in pixels.
 *	- -1 : the specified font is not in the font file.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 65) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetExtendedPoliceSize:KSFAM_FONTLIB:0x0C
//  @GSIM_A:1:DATA_CODE(strlen(police)+1)
//  @GSIM_A:1:IN_ONLY
// \endif
extern int	GetExtendedPoliceSize(char *police);


/*! @brief This function is used to get the height in pixels of a font
 * @param police : _dMEDIUM_, _dLARGE_, _dSMALL_
    _pNORMAL_, _pBOLD_, _pCONDENSED_, _pLARGE_
 * @param BufferBitMap : bitmap font  
 * @return 
 *	- font height in pixels.
 *	- -1 : the specified font is not in the font file.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 112) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetFontPoliceSize:KSFAM_FONTLIB:
//  @GSIM_A:1:DATA_CODE(strlen(police)+1)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:DATA_SIZE(8192)
//  @GSIM_A:2:IN_ONLY
// \endif
extern int GetFontPoliceSize(char *police,unsigned char *BufferBitMap);


/*! @brief This function displays a Unicode string in a graphic area
 * @param x0 : horizontal position in pixel (in range [0,127]) of the beginning and the end of the area.
 * @param y0 : vertical position in pixel (in range [0,63] or [0,127]).
 * @param x1 : horizontal position in pixel (in range [0,127]) of the beginning and the end of the area.
 * @param *chaine : address of formatted string to be displayed. message must be coded in Unicode big endian.
 * @param reverse : reverse video mode ( _ON_ or _OFF_ ).
 * @param police : _dMEDIUM_, _dLARGE_, _dSMALL_ ....
 * @param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_.
 * @param offset : offset in pixels.
 * @return None.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 73) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_ScrollStringUnicode:KSFAM_FONTLIB:0x1A
//  @GSIM_A:4:DATA_CODE(2*strlenUNICODE(chaine)+2)
//  @GSIM_A:4:IN_ONLY
//  @GSIM_A:6:DATA_CODE(strlen(police)+1)
//  @GSIM_A:6:IN_ONLY
// \endif
extern void _ScrollStringUnicode(int x0,int y0,int x1,unsigned char *chaine,int reverse,char *police,int type,int offset);


/*! @brief This functions displays a Unicode string in a graphic area
 * @param x0 : horizontal position in pixel (in range [0,127]) of the beginning and the end of the area.
 * @param y0 : vertical position in pixel (in range [0,63] or [0,127]).
 * @param x1 : horizontal position in pixel (in range [0,127]) of the beginning and the end of the area.
 * @param *chaine : address of formatted string to be displayed. message must be coded in Unicode big endian.
 * @param reverse : reverse video mode ( _ON_ or _OFF_ ).
 * @param police : _dMEDIUM_, _dLARGE_, _dSMALL_ ....
 * @param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_.
 * @param offset : offset in pixels.
 * @return None.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 72) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:ScrollStringUnicode:KSFAM_FONTLIB:0x19
//  @GSIM_A:4:DATA_CODE(2*strlenUNICODE(chaine)+2)
//  @GSIM_A:4:IN_ONLY
//  @GSIM_A:6:DATA_CODE(strlen(police)+1)
//  @GSIM_A:6:IN_ONLY
// \endif
extern void ScrollStringUnicode(int x0,int y0,int x1,unsigned char *chaine,int reverse,char *police,int type,int offset);


/*! @brief This function displays an ISO8859 string in a graphic area
 * @param x0 : horizontal position in pixel (in range [0,127]) of the beginning and the end of the area.
 * @param y0 : vertical position in pixel (in range [0,63] or [0,127])
 * @param x1: horizontal position in pixel (in range [0,127]) of the beginning and the end of the area.
 * @param *chaine : address of formatted string to be displayed. message must be coded in ISO 8859.
 * @param reverse : reverse video mode ( _ON_ or _OFF_ ).
 * @param police : _dMEDIUM_, _dLARGE_, _dSMALL_ ....
 * @param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_.
 * @param offset : offset in pixels.
 * @return None.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 70) if function does not exist
 * @note
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:ScrollString8859:KSFAM_FONTLIB:0x17
//  @GSIM_A:4:DATA_CODE(strlen(chaine)+1)
//  @GSIM_A:4:IN_ONLY
//  @GSIM_A:6:DATA_CODE(strlen(police)+1)
//  @GSIM_A:6:IN_ONLY
// \endif
extern void ScrollString8859(int x0,int y0,int x1,unsigned char *chaine,int reverse,char *police,int type,int offset);


/*! @brief This function displays an ISO8859 string in a graphic area
 * @param x0 : horizontal position in pixel (in range [0,127]) of the beginning and the end of the area.
 * @param y0 : vertical position in pixel (in range [0,63] or [0,127])
 * @param x1: horizontal position in pixel (in range [0,127]) of the beginning and the end of the area.
 * @param *chaine : address of formatted string to be displayed. message must be coded in ISO 8859.
 * @param reverse : reverse video mode ( _ON_ or _OFF_ ).
 * @param police : _dMEDIUM_, _dLARGE_, _dSMALL_ ....
 * @param type : _FIXED_WIDTH_ (all characters have the same width) or _PROP_WIDTH_.
 * @param offset : offset in pixels.
 * @return None.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 71) if function does not exist
 * @note
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_ScrollString8859:KSFAM_FONTLIB:0x18
//  @GSIM_A:4:DATA_CODE(strlen(chaine)+1)
//  @GSIM_A:4:IN_ONLY
//  @GSIM_A:6:DATA_CODE(strlen(police)+1)
//  @GSIM_A:6:IN_ONLY
// \endif
extern void _ScrollString8859(int x0,int y0,int x1,unsigned char *chaine,int reverse,char *police,int type,int offset);



/*! @brief This function is used to get the address of the Manager's default font (embedded in the manager),
 * @return The font address.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 78) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetDefaultFONaddress:KSFAM_FONTLIB:0x16
// \endif
extern char *GetDefaultFONaddress(void);



/*! @brief This function Prints the graphic context on the printer. 
 *
 *	Frees the memory that was allocated in InitPrinterBitmap function. If your bitmap is 1024 pixels high, and you wrote (or draw) only on the first 400 pixels, 
   the printed bitmap will be automatically cut to 400 pixels. 
 * @return None.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 81) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PaintPrinterGraphics:KSFAM_FONTLIB:0x0E
// \endif
extern void PaintPrinterGraphics(void);


/*! @brief This function allocates an empty graphic context for printer.
 * @param Height : the height (in pixels) of the bitmap.
 *	- 0 restore default value (128)
 *	- no upper limit
 * @return None.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 82) if function does not exist
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:InitPrinterBitmap:KSFAM_FONTLIB:0x0F
// \endif
extern void InitPrinterBitmap(int Height);

/*! @brief This function convert an ISO8859 string in an UNICODE string
 * @param i__input_string : horizontal position in pixel (in range [0,127]) of the beginning and the end of the area.
 * @param o__output_string : vertical position in pixel (in range [0,63] or [0,127])
 * @param i__output_string_size: horizontal position in pixel (in range [0,127]) of the beginning and the end of the area.
 * @return None.
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 135) if function does not exist
 * @note
 *
 * @link KSFAM_FONTLIB Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:ISO8859Arabic2Unicode:KSFAM_FONTLIB:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:2:OUT_ONLY
// \endif
extern int ISO8859Arabic2Unicode(char* i__input_string,unsigned short* o__output_string,int i__output_string_size);
#endif
/*! @} **/
