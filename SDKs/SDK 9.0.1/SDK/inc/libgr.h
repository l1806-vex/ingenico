/*! @addtogroup KSFAM_VISU
	* @{
**/
#ifndef LIBGR_H
#define LIBGR_H

#include "fontlib.h"

#define _SIZE_       8

#define NB_COLUMN  160
#define NB_LINE    16

#define PERIPH_DISPLAY           0
#define PERIPH_PPR               1
#define PERIPH_C30               2
#define PERIPH_PRINTER           3
#define PERIPH_DISPLAY_EXTENDED  4

#define _BLACK_     0xFF000000
#define _WHITE_     0xFFFFFFFF
#define _GREEN_     0xFF00FF00

#define _ON_         1
#define _OFF_        0

#define _SMALL_       0
#define _MEDIUM_      1
#define _LARGE_       2
#define _XLARGE_      3
#define _POLICE5x5_   10
#define _POLICE4x7_   11
#define _POLICE5x7_   12
#define _POLICE6x8_   13
#define _POLICE7x8_   14
#define _POLICE8x12_  15
#define _POLICE8x14_  16

#define _SIZE_SMALL_       8
#define _SIZE_MEDIUM_      10
#define _SIZE_LARGE_       12
#define _SIZE_XLARGE_      16
#define _SIZE_POLICE5x5_   5
#define _SIZE_POLICE4x7_   7
#define _SIZE_POLICE5x7_   7
#define _SIZE_POLICE6x8_   8
#define _SIZE_POLICE7x8_   8
#define _SIZE_POLICE8x12_  12
#define _SIZE_POLICE8x14_  14
#define _SIZE_POLICE10x16_ 16

#define _PROPORTIONNEL_       0
#define _NORMALE_             1
#define _FIXED_WIDTH_         2
#define _PROP_WIDTH_          3

#define _NOPOPUP_    0
#define _POPUP_      1

#define BMP_OK				 0
#define BMP_BadDriver		-1
#define BMP_TooBig			-2
#define BMP_WrongVideo		-3
#define BMP_Compression		-4
#define BMP_NoVolumeFound   -5
#define BMP_NoFileFound     -6
#define BMP_NotEnoughMem    -7
#define BMP_ReadError       -8
#define BMP_NotAvailable	-9


/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief This structure defines a bitmap file header; All 2 char are intel short , all 4 char are intel long */
typedef struct
{
  unsigned char bfType[2];           //!< "BM"
  unsigned char bfSize[4];           //!< Size of file in bytes
  unsigned char bfReserved1[2];      //!< Set to 0
  unsigned char bfReserved2[2];      //!< Set to 0
  unsigned char bfOffBits[4];        //!< Offset in file where the bits begin
} BITMAPFILEHEADER;


/*! @brief This structure defines a bitmap header information structure; All 2 char are intel short , all 4 char are intel long */
typedef struct
{
  unsigned char biSize[4];           //!< Size of the structure
  unsigned char biWidth[4];          //!< Width in pixels
  unsigned char biHeight[4];         //!< Height in pixels
  unsigned char biPlanes[2];         //!< # of color Planes: Set to 1
  unsigned char biBitCount[2];       //!< Color bits per pixel
  unsigned char biCompression[4];    //!< Compression Scheme
  unsigned char biSizeImage[4];      //!< Number of bitmap bytes
  unsigned char biXPelsPerMeter[4];  //!< Horizontal Resolution
  unsigned char biYPelsPerMeter[4];  //!< Vertical Resolution
  unsigned char biClrUsed[4];        //!< Number of colors used
  unsigned char biClrImportant[4];   //!< Important colors

} BITMAPINFOHEADER;

/*! @brief This structure describes the columns */
typedef struct
{
  unsigned char space_before;			//!< space before the column
  unsigned char nb_column;				//!< number of column
  unsigned char column[NB_COLUMN];		//!< array containing the data of the column
  unsigned char only_line;				//!< only line
  unsigned char space_after;			//!< space after the column
} StructColumn;

/*! @brief This structure defines the structure of the screen (NB_LINE lines of StructColumn).*/
typedef struct
{
  StructColumn line[NB_LINE];			//!< Line
} StructScreen;

/*! @brief This structure defines the structure of an extended screen*/
typedef struct
{
  union
  {
    void           *ColorScreen;
    unsigned short *Color16Screen;
    unsigned int   *Color32Screen;
  } Screen; //!< Internal screen[NB_COLONNE_DISPLAY_COLOR*NB_LIGNE_DISPLAY_COLOR];
} StructScreenExtended;

/*! @brief This structure defines the structure of a menu*/
typedef struct
{
	int            popup;					/*!< save and restore screen : _ON_ or _OFF_ */
	int            first;					/*!< first item of the list*/
	int            left;					/*!< in pixels*/
	int            top;						/*!< in pixels*/
	int            rigth;					/*!< in pixels*/
	int            bottom;				/*!< in pixels*/
	int            thickness;			/*!< window border thickness */
	int            police;				/*!< font, should be 0 */
	int            type;					/*!< font type : _PROPORTIONNEL_ or _NORMALE_ */
	unsigned char *titre;					/*!< title of the menu*/
	unsigned char *tab[10];				/*!< list of the elements of the menu*/
} StructMenu;

#define NB_MAX_PATTERN  128

/*! @brief his structure defines the graphic pattern structure.*/
typedef struct
{
   int            TypePolice;		/*!< font type.*/
   int            Len;					/*!< length.*/
   unsigned char *PtDef;				/*!< Definition of the pattern.*/
   unsigned char  Key;					/*!< character code.*/
} StructGraphicPattern;

#ifdef _SPAIN_
#define _Version_ "02.01" /* n'evolue pas pour l'espagne malgre l'ajout de fontlib !!!*/
#else
#define _Version_ "04.00"
#endif


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function is used to select the peripheral where all pixels are displayed.
 *	See GetGraphicContext and GetGraphicMode. 
 *
 *	Default value is PERIPH_DISPLAY
 *	@param Periph    : Display to use.
 *	- #PERIPH_DISPLAY          : All graphics on DISPLAY 
 *	- #PERIPH_DISPLAY_EXTENDED : All graphics on Color DISPLAY (only possible when terminal has color possibility)
 *	- #PERIPH_PPR              : All graphics on PPC30/PPR30 
 *	- #PERIPH_C30              : All graphics on Telium Pass (C30) 
 *	@return none
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 39) if function does not exist
 *
 *	@note 
 *  - When GraphicContext is set to PERIPH_DISPLAY 
 *		--> GraphicMode is set to PERIPH_DISPLAY for B/W graphic terminal
 *		--> GraphicMode is set to PERIPH_DISPLAY_EXTENDED for color graphic terminal
 *  - When GetGraphicContext is set to PERIPH_DISPLAY_EXTENDED
 *		--> GraphicMode is set to PERIPH_DISPLAY_EXTENDED
 *  - When GetGraphicContext is set to PERIPH_PPR
 *		--> GraphicMode is set to PERIPH_DISPLAY
 *  - When GetGraphicContext is set to PERIPH_C30
 *		--> GraphicMode is set to PERIPH_DISPLAY
 *
 *  - Here are the actual possibility
 *	- +-------------------------+-------------------------+--------------------------------+
 *	- + GetGraphicContext       | GetGraphicMode          | TERMINAL                       +
 *	- +-------------------------+--------------------------+-------------------------------+
 *	- +                         |                         |                                +
 *	- + PERIPH_DISPLAY          | PERIPH_DISPLAY          | B/W graphics                   +
 *	- + PERIPH_DISPLAY          | PERIPH_DISPLAY_EXTENDED | Color graphics (B/W emulation) +
 *	- + PERIPH_DISPLAY_EXTENDED | PERIPH_DISPLAY_EXTENDED | Full color graphics            +
 *	- + PERIPH_PPR              | PERIPH_DISPLAY          | B/W graphic pinpad             +
 *	- + PRIPH_C30               | PERIPH_DISPLAY          | B/W graphic C30                +
 *	- +                         |                         |                                +
 *	- +---------------------------------------------------+--------------------------------+
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:InitContexteGraphique:KSFAM_VISU:
// \endif
extern int InitContexteGraphique(int Periph);

/*! @brief This function is used to set or select a region
 *	@param left,right : horizontal coordonate
 *	@param top,bottom : vertical coordonate
 *	@return none
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 88) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetRegion:KSFAM_VISU:
// \endif
extern int SetRegion(int left,int top,int right,int bottom);


/*! @brief This function gets current region coordinate
 *	@param left,right : horizontal coordonate
 *	@param top,bottom : vertical coordonate
 *	@return none
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 89) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetRegion:KSFAM_VISU:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
// \endif
extern int GetRegion(int *left,int *top,int *right,int *bottom);



/*! @brief This function clears region
 *	@return none
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 90) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:ClearRegion:KSFAM_VISU:
// \endif
extern int ClearRegion(void);

/*! @brief This routine takes the current the graphic context and paints it onto the screen. 
 *
 *	This routine is equivalent to the printf (b) where b is a defdisplaypattern compatible bit map corresponding to the whole screen. 
 *	@return None.
 *	@note
 *	- This routine should be called when the screen is fully ready to be displayed. 
 *	- It is not recommended to call it after each routine manipulating the graphic context for performance purpose. 
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PaintGraphics:KSFAM_VISU:
// \endif
extern void PaintGraphics(void);


/*! @brief This function calculates the pixels number used by a string. 
 *	This is important to know how large a string is and check if it is possible to put it on a line. Use the 
 *	current font and dont type (GetFont) ie _SMALL_, _MEDIUM_, _LARGE_, _XLARGE_. 
 *	@param s : pointer on the formatted string to be checked.
 *	@return The pixels number used by the given string.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 1) if function does not exist
 *	@note String is a formatted text ( see printf ). 
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:StringWidth:KSFAM_VISU:
// \endif
extern int  StringWidth(char *s);


/*! @brief This function is used to change the font height.
 *	@param police :
 *	-  _SMALL _ : characters height is 8 pixels 
 *	-  _MEDIUM_ : characters height is 10 pixels 
 *	-  _LARGE_  : characters height is 12 pixels 
 *	-  _XLARGE_ : characters height is 16 pixels 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 2) if function does not exist
 *	@note
 *	- Could be called prior inserting text.
 *	- There is no link with OEM C routine startupcv20. 
 *	- You also need to initialise the font when creating the graphic context
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetFont:KSFAM_VISU:
// \endif
extern void SetFont(int police);

/*! @brief This function is used to get the currently font height.
 *	@return
 *	Get the font that is currently selected : 
 *	- _SMALL _ : characters height is 8 pixels 
 *	- _MEDIUM_ : characters height is 10 pixels 
 *	- _LARGE_ : characters height is 12 pixels 
 *	- _XLARGE_ : characters height is 16 pixels 
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 3) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetFont:KSFAM_VISU:
// \endif
extern int  GetFont(void);


/*! @brief This function is used to change the font type.
 *	@param type : Font to be selected
 *	- _PROPORTIONNEL _ : Proportional Font 
 *	- _NORMALE_ : Fixed Font 
 *	@return None (void)
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 4) if function does not exist
 *	@note
 *	- You can change the font at any time after creating the graphic context. 
 *	- Default font is proportional. For current font only. 
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetType:KSFAM_VISU:
// \endif
extern void SetType(int type);


/*! @brief This function is used to get the currently font type.
 *	@return 
 *	Font currently selected : 
 *	- _PROPORTIONNEL _ : Proportional Font.
 *	- _NORMALE_ : Fixed Font.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 5) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetType:KSFAM_VISU:
// \endif
extern int  GetType(void);


/*! @brief This function builds and initialises the graphic context with a font height.
 *	@param police : Font to be used :
 *	- _SMALL _ : characters height is 8 pixels 
 *	- _MEDIUM_ : characters height is 10 pixels 
 *	- _LARGE_ : characters height is 10 pixels 
 *	- _XLARGE_ : characters height is 16 pixels 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 6) if function does not exist
 *	@note 
 *	- This is the first routine to be called prior any graphic context access. 
 *	- The font can be small ( 8 pixels height ) or medium ( 10 pixels height ) or large ( 12 pixels height ) or xlarge ( 16 pixels height ). 
 *	- The width cannot be changed because it is proportional. 
 *	- The graphic context is left cleared ( no pixel positioned ) and CreateGraphics forces a clear screen.
 *	- CreateGraphics initialises the font to be proportional. 
 *	- CreateGraphics is automatically called when linking the graphic library DLL as implemented in TELIUM. 
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:CreateGraphics:KSFAM_VISU:
// \endif
extern void CreateGraphics(int police);


/*! @brief This function places a pixel according to its screen position onto the graphic context. 
 *
 *	Pixel state can be set ( _ON_ ) or reset ( _OFF_ ). 
 *	@param x     : in range [0,127]. 
 *	@param y     : in range [0,127]. 
 *	@param state : _ON_ (set pixel) or _OFF_ (reset pixel) 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 7) if function does not exist
 *	@note 
 *	- Such routine allows to create your own drawing routines
 *	- _SetPixel does not refresh the display, SetPixel refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_SetPixel:KSFAM_VISU:
// \endif
extern void _SetPixel(int x,int y,int state);

/*! @brief This function draws a line from point A(x1,y1) to point B (x2,y2) in the graphic context.
 *	@param x1,x2 : in range [0,127]. 
 *	@param y1,y2 : in range [0,63].
 *	@param state : _ON_ or _OFF_ 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 8) if function does not exist
 *	@note 
 *	- The line has a fixed thickness. 
 *	- Different thickness can be obtained by drawing multiple lines with pixels increment. 
 *	- _DrawLine does not refresh the display, DrawLine refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawLine:KSFAM_VISU:
// \endif
extern void _DrawLine(int x1,int y1,int x2,int y2,int state);


/*! @brief This function draws a line from point A(x1,y1) to point B (x2,y2) in the graphic context.
 *	@param x1,x2 : in range [0,127]. 
 *	@param y1,y2 : in range [0,63].
 *	@param state : _ON_ or _OFF_ 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 9) if function does not exist
 *	@note 
 *	- The line has a fixed thickness. 
  *	- Different thickness can be obtained by drawing multiple lines with pixels increment. 
 *	- _DrawLine does not refresh the display, DrawLine refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawLine:KSFAM_VISU:
// \endif
extern void DrawLine(int x1,int y1,int x2,int y2,int state);


/*! @brief This function places a pixel according to its screen position onto the graphic context. 
 *	Pixel state can be set ( _ON_ ) or reset ( _OFF_ ). 
 *	@param x : in range [0,127]. 
 *	@param y : in range [0,127]. 
 *	@param state : _ON_ (set pixel) or _OFF_ (reset pixel) 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 10) if function does not exist
 *	@note 
  *	- Such routine allows to create your own drawing routines
  *	- _SetPixel does not refresh the display, SetPixel refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetPixel:KSFAM_VISU:
// \endif
extern void SetPixel(int x,int y,int state);


/*! @brief This function gets a pixel according to its screen position onto the graphic context. 
 *	@param x : in range [0,127]. 
 *	@param y : in range [0,127]. 
 *	@return  _ON_ or _OFF_ 
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 13) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetPixel:KSFAM_VISU:
// \endif
int GetPixel(int x,int y);


/*! @brief This function inserts a bit map at x and y position with the reverse video option in the graphic context. 
 *	See defdisplaypattern for the bit map definition. 
 *	@param x0 : Parameter x in range [0,127] 
 *	@param y0 : Parameter y in range [0,127] 
 *	@param bitmap : points to a bitmap ( defdisplaypattern compatible ) 
 *	@param reverse : reverse video _ON_ or _OFF_ 
 *	@return None (void).
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 11) if function does not exist
 *	@note 
 *	- This is useful when a logo has to be displayed somewhere on the screen. 
 *	- You should use our tool to convert BMP file to defdisplaypattern compatible bit maps. 
 *	- Bit map height is modulo 8. 
 *	- Defdisplaypattern is no more useful when using this graphic library. 
 *	- _SetBitmap does not refresh the display, SetBitmap refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_SetBitmap:KSFAM_VISU:
//  @GSIM_S:_SetBitmap:E__SetBitmap
//  GSIM_A:3:SUPPLIED(BUF_SER_bmp_pattern;BUF_DES_bmp_pattern)
//  GSIM_A:3:IN_ONLY
// \endif
extern void _SetBitmap(int x0,int y0,unsigned char *bitmap,int reverse);


/*! @brief This function inserts a bit map at x and y position with the reverse video option in the graphic context.
 *	See defdisplaypattern for the bit map definition. 
 *	@param x0 		: Parameter x in range [0,127] 
 *	@param y0 		: Parameter y in range [0,127] 
 *	@param bitmap : points to a bitmap ( defdisplaypattern compatible ) 
 *	@param reverse : reverse video _ON_ or _OFF_ 
 *	@return None (void).
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 12) if function does not exist
 *	@note 
 *	- This is useful when a logo has to be displayed somewhere on the screen. 
 *	- You should use our tool to convert BMP file to defdisplaypattern compatible bit maps.
 *	- Bit map height is modulo 8. 
 *	- Defdisplaypattern is no more useful when using this graphic library. 
 *	- _SetBitmap does not refresh the display, SetBitmap refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetBitmap:KSFAM_VISU:
//  @GSIM_S:SetBitmap:E_SetBitmap
//  GSIM_A:3:SUPPLIED(BUF_SER_bmp_pattern;BUF_DES_bmp_pattern)
//  GSIM_A:3:IN_ONLY
// \endif
extern void SetBitmap(int x0,int y0,unsigned char *bitmap,int reverse);


/*! @brief This function draws a rectangle from point A (left, top) to point B (right, bottom) with or without border in the graphic context.
 *
 *	Border size is programmable and Rectangle can be filled or not. 
 *	@param left 			: in range [0,127].
 *	@param top 				: in range [0,127].
 *	@param right 			: in range [0,127].
 *	@param bottom 		: in range [0,127].
 *	@param thickness 	: pixels number for the border ( 1 minimum if BORDER is _ON_ ).
 *	@param border 		: _ON_0 ( visible ) or _OFF_ ( not visible ) 
 *	@param fill 			: _ON_ ( filled ) or _OFF_ ( not filled ) 
 *	@return None (void).
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 14) if function does not exist
 *	@note 3D rectangle can be obtained by drawing 2 near rectangles
 *	- _DrawRect does not refresh the display, DrawRect refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawRect:KSFAM_VISU:
// \endif
extern void _DrawRect(int left,int top,int right,int bottom,int thickness,int border,int fill);


/*! @brief This function draws a rectangle from point A (left, top) to point B (right, bottom) with or without border in the graphic context. 
 *
 *	Border size is programmable and Rectangle can be filled or not. 
 *	@param left 			: parameter left, in range [0,127].
 *	@param top 				: parameter top, in range [0,127].
 *	@param right 			: parameter right in range [0,127].
 *	@param bottom 		: parameter bottom in range [0,127].
 *	@param thickness	: pixels number for the border ( 1 minimum if BORDER is _ON_ ) .
 *	@param border 		: 
 *	-  _ON_0 (visible)
 *	-  _OFF_ (not visible) 
 *	@param fill 			:
 *	-  _ON_ (filled)
 *	-  _OFF_ (not filled) 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 15) if function does not exist
 *	@note 3D rectangle can be obtained by drawing 2 near rectangles
 *	- _DrawRect does not refresh the display, DrawRect refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawRect:KSFAM_VISU:
// \endif
extern void DrawRect(int left,int top,int right,int bottom,int thickness,int border,int fill);


/*! @brief This function draws a circle with a centre located at (x,y) position and with the given radius in the graphic context.
 *
 *	Circle can be filled or not. 
 *	@param x0 		: in range [0,127]. 
 *	@param y0 		: in range [0,63].
 *	@param r 			: Radius in terms of pixels number 
 *	@param fill 	: _ON_ (filled) or _OFF_ (not filled) 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 16) if function does not exist
 *	@note There is no border option, thickness is 1 single pixel. 
 *	-   x + radius must be less than 127. 
 *	-   y + radius must be less than 64 .
 *	- _DrawCircle does not refresh the display, DrawCircle refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawCircle:KSFAM_VISU:
// \endif
extern void _DrawCircle(int x0,int y0,int r,int fill);


/*! @brief This function draw a circle with a centre located at (x,y) position and with the given radius in the graphic context. 
 *
 *	Circle can be filled or not. 
 *	@param x0 		: in range [0,127]. 
 *	@param y0 		: in range [0,63].
 *	@param r 			: Radius in terms of pixels number 
 *	@param fill 	: _ON_ ( filled ) or _OFF_ ( not filled ) 
 *	@return None (void).
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 17) if function does not exist
 *	@note There is no border option, thickness is 1 single pixel. 
 *	- x + radius must be less than 127. 
 *	- y + radius must be less than 64 .
 *	- _DrawCircle does not refresh the display, DrawCircle refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawCircle:KSFAM_VISU:
// \endif
extern void DrawCircle(int x0,int y0,int r,int fill);


/*! @brief This function draws an ellipse with a centre located at (x,y) position and the 2 given radiuses in the graphic context.
 *
 *	Ellipse can be filled or not. 
 *	@param x0 : in range [0,127] 
 *	@param y0 : in range [0,127]
 *	@param rx : in terms of pixels number : Radius in terms of pixels number .
 *	@param ry : in terms of pixels number : Radius in terms of pixels number .
 *	@param fill : _ON_ ( filled ) or _OFF_ ( not filled ) 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 18) if function does not exist
 *	@note 
 *	- There is no border option, thickness is 1 single pixel. 
 *	-  x + rx must be less than 127, and y + ry must be less than 64 .
 *	- _DrawEllipse does not refresh the display, DrawEllipse refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawEllipse:KSFAM_VISU:
// \endif
extern void _DrawEllipse(int x0,int y0,int rx,int ry,int fill);


/*! @brief This function draws an ellipse with a centre located at (x,y) position and the 2 given radiuses in the graphic context.
 *
 *	Ellipse can be filled or not. 
 *	@param x0 : in range [0,127] 
 *	@param y0 : in range [0,127]
 *	@param rx : in terms of pixels number : Radius in terms of pixels number .
 *	@param ry : in terms of pixels number : Radius in terms of pixels number .
 *	@param fill : _ON_ ( filled ) or _OFF_ ( not filled ) 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 19) if function does not exist
 *	@note
 *	- There is no border option, thickness is 1 single pixel. 
 *	- x + rx must be less than 127, and y + ry must be less than 64 .
 *	- _DrawEllipse does not refresh the display, DrawEllipse refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawEllipse:KSFAM_VISU:
// \endif
extern void DrawEllipse(int x0,int y0,int rx,int ry,int fill);


/*! @brief This function places a text in the graphic context at x and y position with or without reverse video option.
 *
 *	Use the current font and dont type (GetFont) ie _SMALL_, _MEDIUM_, _LARGE_, _XLARGE_. 
 *	- \\n forces x to be resetted (x=0) and y to skip to the next line (y+=fontsize).
 *	- \\r forces x to be resetted (x=0) and y is unchanged.
 *	- Escape character ( \\x1B ) is not handled. 
 *	@param str : pointer on the formatted string to be displayed 
 *	@param x0 : in range [0,127] 
 *	@param y0 : in range [0,127] 
 *	@param reverse : Reverse video (_ON_ or _OFF_ )
 *	@return 
 *	-  0 if OK.
 *	-  <0 if error. 
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 22) if function does not exist
 *	@note String is a formatted text ( see printf ). No blinking possibilities .
 *	- _DrawString does not refresh the display, DrawString refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawString:KSFAM_VISU:
//  @GSIM_A:1:IN_ONLY
// \endif
extern int  _DrawString(char *str,int x0,int y0,int reverse);


/*! @brief This function places a text in the graphic context at x and y position with or without reverse video option.
 *
 *	Use the current font and dont type (GetFont) ie _SMALL_, _MEDIUM_, _LARGE_, _XLARGE_. 
 *	-  \\n forces x to be resetted (x=0) and y to skip to the next line (y+=fontsize).
 *	-  \\rforces x to be resetted (x=0) and y is unchanged. 
 *	-  Escape character (\\x1B) is not handled. 
 *	@param str : pointer on the formatted string to be displayed 
 *	@param x0 : in range [0,127] 
 *	@param y0 : in range [0,127] 
 *	@param reverse : Reverse video (_ON_ or _OFF_ )
 *	@return 0 
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 23) if function does not exist
 *	@note 
 *	-  String is a formatted text ( see printf ). 
 *	-  No blinking possibilities .
 *	- _DrawString does not refresh the display, DrawString refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawString:KSFAM_VISU:
//  @GSIM_A:1:IN_ONLY
// \endif
extern int  DrawString(char *str,int x0,int y0,int reverse);



/*! @brief A window is couple of rectangle: one rectangle for the title and a second rectangle.
 *
 *	It draws the window in the graphic context from point A (left, top) to point B (right, bottom) with a title and a border size using a 8859 font. 
 *	@param left : in range [0,127].
 *	@param top : in range [0,127].
 *	@param rigth : in range [0,127].
 *	@param bottom : in range [0,127].
 *	@param thickness : pixels number for the border ( 1 minimum ) 
 *	@param Titre : string to be displayed at the top of the window. May be NULL (no title) 
 *	@param Police : font data handle for title.
 *	@param Font : font for title.
 *	@return None (void).
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 10) if function does not exist
 *	@note 
 *	-  Border is always visible and rectangles are not filled. The given size includes the 2 rectangles.
 *	-  The first rectangle height is font dependent (2 pixels height + the current font height ) and this cannot be changed.
 *	-  The second rectangle height can be deducted from the total size ( height = given height - font height - 2 ).
 *	-  Title must fit into the window width. The title is automatically centered. 
 *	- _DrawWindow8859 does not refresh the display.
 *
 *	@section TestDrawWindow8859

 * @include libgr_Sample_01.c
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawWindow8859:KSFAM_VISU:
//  @GSIM_A:6:DATA_CODE(strlen(Titre)+1)
//  @GSIM_A:6:IN_ONLY
// \endif
extern void _DrawWindow8859(int left,int top,int rigth,int bottom,int thickness,unsigned char *Titre,char *Police,int Font);


/*! @brief A window is couple of rectangle: one rectangle for the title and a second rectangle.
 *
 *	It draws the window in the graphic context from point A (left, top) to point B (right, bottom) with a title and a border size. 
 *	@param left : in range [0,127].
 *	@param top : in range [0,127].
 *	@param right : in range [0,127].
 *	@param bottom : in range [0,127].
 *	@param thickness : pixels number for the border ( 1 minimum ) 
 *	@param Titre : string to be displayed at the top of the window. May be NULL (no title) 
 *	@return None (void).
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 24) if function does not exist
 *	@note 
 *	-  Border is always visible and rectangles are not filled. The given size includes the 2 rectangles.
 *	-  The first rectangle height is font dependent (2 pixels height + the current font height ) and this cannot be changed.
 *	-  The second rectangle height can be deducted from the total size ( height = given height - font height - 2 ).
 *	-  Title must fit into the window width. The title is automatically centered. 
 *	- _DrawWindow does not refresh the display, DrawWindow refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawWindow:KSFAM_VISU:
//  @GSIM_A:6:DATA_CODE(strlen(Titre)+1)
//  @GSIM_A:6:IN_ONLY
// \endif
extern void _DrawWindow(int left,int top,int right,int bottom,int thickness,unsigned char *Titre);


/*! @brief A window is couple of rectangle: one rectangle for the title and a second rectangle. 
 *
 *	It draws the window in the graphic context from point A (left, top) to point B (right, bottom) with a title and a border size. 
 *	@param left : in range [0,127].
 *	@param top : in range [0,127].
 *	@param right : in range [0,127].
 *	@param bottom : in range [0,127].
 *	@param thickness : pixels number for the border ( 1 minimum ) 
 *	@param Titre : string to be displayed at the top of the window. May be NULL (no title) 
 *	@return None (void)
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 25) if function does not exist
 *	@note 
 *	-  Border is always visible and rectangles are not filled. The given size includes the 2 rectangles. 
 *	-  The first rectangle height is font dependent (2 pixels height + the current font height) and this cannot be changed. 
 *	-  The second rectangle height can be deducted from the total size ( height = given height - font height - 2 ).
 *	-  Title must fit into the window width. The title is automatically centered. 
 *	- _DrawWindow does not refresh the display, DrawWindow refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawWindow:KSFAM_VISU:
//  @GSIM_A:6:DATA_CODE(strlen(Titre)+1)
//  @GSIM_A:6:IN_ONLY
// \endif
extern void DrawWindow(int left,int top,int right,int bottom,int thickness,unsigned char *Titre);


/*! @brief A window is couple of rectangle: one rectangle for the title and a second rectangle.
 *
 *	It draws the window in the graphic context from point A (left, top) to point B (right, bottom) with a title and a border size. 
 *	@param left : in range [0,127].
 *	@param top : in range [0,127].
 *	@param right : in range [0,127].
 *	@param bottom : in range [0,127].
 *	@param thickness : pixels number for the border ( 1 minimum ) 
 *	@param Titre : string to be displayed at the top of the window. May be NULL (no title) 
 *	@param Font  : Font of title (_SMALL_,_MEDIUM_,...)
 *	@return None (void).
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 24) if function does not exist
 *	@note 
 *	-  Border is always visible and rectangles are not filled. The given size includes the 2 rectangles.
 *	-  The first rectangle height is font dependent (2 pixels height + the current font height ) and this cannot be changed.
 *	-  The second rectangle height can be deducted from the total size ( height = given height - font height - 2 ).
 *	-  Title must fit into the window width. The title is automatically centered. 
 *	- _DrawWindowFont does not refresh the display, DrawWindowFont refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawWindow:KSFAM_VISU:
//  @GSIM_A:6:DATA_CODE(strlen(Titre)+1)
//  @GSIM_A:6:IN_ONLY
// \endif
extern void _DrawWindowFont(int left,int top,int right,int bottom,int thickness,unsigned char *Titre,int Font);


/*! @brief A window is couple of rectangle: one rectangle for the title and a second rectangle. 
 *
 *	It draws the window in the graphic context from point A (left, top) to point B (right, bottom) with a title and a border size. 
 *	@param left : in range [0,127].
 *	@param top : in range [0,127].
 *	@param right : in range [0,127].
 *	@param bottom : in range [0,127].
 *	@param thickness : pixels number for the border ( 1 minimum ) 
 *	@param Titre : string to be displayed at the top of the window. May be NULL (no title) 
 *	@param Font  : Font of title (_SMALL_,_MEDIUM_,...)
 *	@return None (void)
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 25) if function does not exist
 *	@note 
 *	-  Border is always visible and rectangles are not filled. The given size includes the 2 rectangles. 
 *	-  The first rectangle height is font dependent (2 pixels height + the current font height) and this cannot be changed. 
 *	-  The second rectangle height can be deducted from the total size ( height = given height - font height - 2 ).
 *	-  Title must fit into the window width. The title is automatically centered. 
 *	- _DrawWindowFont does not refresh the display, DrawWindowFont refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawWindow:KSFAM_VISU:
//  @GSIM_A:6:DATA_CODE(strlen(Titre)+1)
//  @GSIM_A:6:IN_ONLY
// \endif
extern void DrawWindowFont(int left,int top,int right,int bottom,int thickness,unsigned char *Titre,int Font);

/*! @brief This function clears or fill the specified graphic area in the graphic context. 
 *
 *	A graphic area is specified by left, top, right, bottom parameters.
 *	@param left : in range [0,127].
 *	@param top : in range [0,127].
 *	@param right : in range [0,127].
 *	@param bottom : in range [0,127].
 *	@param fill : _ON_ ( fill area ) or _OFF_ ( clear area ) 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 26) if function does not exist
 *	@note 
 *	_SetArea does not refresh the display, SetArea refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_SetArea:KSFAM_VISU:
// \endif
extern void _SetArea(int left,int top,int right,int bottom,int fill);


/*! @brief This function clears or fill the specified graphic area in the graphic context. 
 *
 *	A graphic area is specified by left, top, right; bottom parameters 
 *	@param left : in range [0,127].
 *	@param top : in range [0,127].
 *	@param right : in range [0,127].
 *	@param bottom : in range [0,127].
 *	@param fill : _ON_ ( fill area ) or _OFF_ ( clear area ) 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 27) if function does not exist
 *	@note 
 *	_SetArea does not refresh the display, SetArea refresh it.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetArea:KSFAM_VISU:
// \endif
extern void SetArea(int left,int top,int right,int bottom,int fill);


/*! @brief This function copies the specified graphic area somewhere in the graphic context. 
 *
 *	This area is not displayed. Source graphic area is specified by left,top,right; bottom like a rectangle.
 *
 *	Destination graphic area is specified by dx and dy position. 
 *	@param left 	: in range [0,127].
 *	@param top 		: in range [0,127].
 *	@param right 	: in range [0,127].
 *	@param bottom : in range [0,127].
 *	@param dx 		: in range [0,127].
 *	@param dy 		: in range [0,127].
 *	@param erase 	: Erase if _ON_ or do not erase if _OFF_.
 *	@param fill 	: _ON_ ( fill source) or _OFF_ ( clear source) if erase is _ON_
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 28) if function does not exist
 *	@note 
 *
 * @link KSFAM_VISU Back to top @endlink
*/
//! The source area can be erased or filled if necessary.
// \if SIMULATION
//  @GSIM_F:CopyArea:KSFAM_VISU:
// \endif
extern void CopyArea(int left,int top,int right,int bottom,int dx,int dy,int erase,int fill);

/*! @brief This routine saves the graphic context to be restored later.
 *	@param *screen : pointer on the graphic context.
 *	@return Internal structure.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 29) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SaveScreen:KSFAM_VISU:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern StructScreen *SaveScreen(StructScreen *screen);


/*! @brief This function restores the whole graphic context previously saved in screen.
 *	@param *screen : pointer on the graphic context.
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 30) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:RestoreScreen:KSFAM_VISU:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void RestoreScreen(StructScreen *screen);


/*! @brief This function is used to get library version. 
 *	@return A string that represents the library version (xx.yy).
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 31) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:LibVersion:KSFAM_VISU:
// \endif
extern char *LibVersion(void);


/*! @brief This function gets Height and Width of the screen.
 *	@param *height : Pointers on screen height.
 *	@param *width : Pointers on screen width.
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 32) if function does not exist
 *	@note You need to known the size of the graphic area prior creating the graphic context. 
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetScreenSize:KSFAM_VISU:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
// \endif
extern void GetScreenSize(int *height,int *width);


/*! @brief This function inserts a BMP image at x and y position with the reverse video option in the graphic context .
 *	@param x0 : Parameter x in range [0,127].
 *	@param y0 : Parameter y in range [0,127]. 
 *	@param bitmap : points to a BMP file format ( must be saved with 16 or 256 colors ).
 *	@param reverse : reverse video _ON_ or _OFF_.
 *	@return 
 *	error code : 
 *	-  BMP_OK 0
 *	-  BMP_BadDriver -1
 *	-  BMP_TooBig -2
 *	-  BMP_WrongVideo -3
 *	-  BMP_Compression -4
 *	-  BMP_NoVolumeFound -5
 *	-  BMP_NoFileFound -6
 *	-  BMP_NotEnoughMem -7
 *	-  BMP_ReadError -8
 *	-  BMP_NotAvailable -9
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 33) if function does not exist
 *	@note This is useful when a logo has to be displayed somewhere on the screen.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetBmp:KSFAM_VISU:
//  @GSIM_A:3:SUPPLIED(BUF_SER_bmp;BUF_DES_bmp)
//  @GSIM_A:3:IN_ONLY
// \endif
extern int  SetBmp(int x0,int y0,unsigned char *bitmap,int reverse);


/*! @brief This function print a bitmap at BMP format. 
 *
 *  the bitmap must have a high multiple of eight
 *	BMP characteristics : 
 *	-  1 or 16 color 
 *	-  Maximum size : 384 x 128 
 *	@param x0 			: left margin 0 to 384
 *	@param bitmap 	: bitmap points to a BMP file format.
 *	@param reverse 	: reverse video _ON_ or _OFF_.
 *	@return
 *	error code :  
 *	-  BMP_OK          OK 
 *	-  BMP_TooBig      BMP higher as 384 x 128 
 *	-  BMP_WrongVideo  bad BMP format. 
 *	-  BMP_Compression bad BMP format. 
 *	- _PrintBmp does not print the bitmap, PrintBmp print it.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 77) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_PrintBmp:KSFAM_VISU:
//  @GSIM_A:2:SUPPLIED(BUF_SER_bmp;BUF_DES_bmp)
//  @GSIM_A:2:IN_ONLY
// \endif
extern int _PrintBmp(int x0,unsigned char *bitmap,int reverse);


/*! @brief This function prints a bitmap at BMP format . 
 *
 *  the bitmap must have a high multiple of eight
 *	BMP characteristics : 
 *	-  1 or 16 color 
 *	-  Maximum size : 384 x 128 
 *	@param x0 			: left margin 0 to 384
 *	@param bitmap 	: bitmap points to a BMP file format.
 *	@param reverse 	: reverse video _ON_ or _OFF_.
 *	@return
 *	error code : 
 *	-  BMP_OK          OK 
 *	-  BMP_TooBig      BMP higher as 384 x 128 
 *	-  BMP_WrongVideo  bad BMP format. 
 *	-  BMP_Compression bad BMP format. 
 *	- _PrintBmp does not print the bitmap, PrintBmp print it.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 76) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PrintBmp:KSFAM_VISU:
//  @GSIM_A:2:SUPPLIED(BUF_SER_bmp;BUF_DES_bmp)
//  @GSIM_A:2:IN_ONLY
// \endif
extern int PrintBmp(int x0,unsigned char *bitmap,int reverse);


/*! @brief This function sets the bitmap passed as a parameter to the X, Y position of the final image of the ticket that was previously allocated with the function InitPrinterBitmap.
 *
 *	BMP characteristics : 
 *	-  1 or 16 color 
 *	-  Maximum size : 384 x yyy, yyy defined by the calling to InitPrinterBitmap(yyy)
 *	@param x0 : horizontal position in pixel (in range [0,383])
 *	@param y0 : vertical position in pixel (in range [0,bitmap height])
 *	@param bitmap : bitmap points to a BMP file format.
 *	@param reverse : reverse video _ON_ or _OFF_
 *	@return
 *	error code : 
 *	-  BMP_OK          OK 
 *	-  BMP_TooBig      BMP higher as 384 x yyy 
 *	-  BMP_WrongVideo  bad BMP format. 
 *	-  BMP_Compression bad BMP format. 
 *	- _PrintBmpXY does not print the bitmap.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 80) if function does not exist
 *	@section BMP

 * @include libgr_Sample_02.c
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_PrintBmpXY:KSFAM_VISU:
//  @GSIM_A:3:SUPPLIED(BUF_SER_bmp;BUF_DES_bmp)
//  @GSIM_A:3:IN_ONLY
// \endif
extern int _PrintBmpXY(int x0,int y0,unsigned char *bitmap,int reverse);


/*! @brief This function clears the graphic context.
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 34) if function does not exist
 *	@note The screen will be cleared after PaintGraphics operation.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_clrscr:KSFAM_VISU:
// \endif
extern void _clrscr(void);

/*! @brief This function clears the graphic context and force total refresh of color screen.
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 109) if function does not exist
 *	@note The screen will be cleared after PaintGraphics operation.
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:clrscr:KSFAM_VISU:
// \endif
extern void clrscr(void);


/*! @brief This function calculates the pixels number used by a char. 
 *
 *	This is important to know how large a character is and check if it is possible to put it on a line. Use the 
    current font and dont type (GetFont) ie _SMALL_, _MEDIUM_, _LARGE_, _XLARGE_. 
 *	@param a_char : the character to be checked.
 *	@return The width in terms of pixels number used by the given character.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 35) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_Sizeof:KSFAM_VISU:
// \endif
extern int  _Sizeof(unsigned char a_char);


/*! @brief This function calculates the character height. 
 *
 *	This is important to know how high the font is. Use the current font and dont type (GetFont) ie _SMALL_, _MEDIUM_, _LARGE_, _XLARGE_. 
 *	@return The height in terms of pixels number used by the currently font.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 36) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetPoliceSize:KSFAM_VISU:
// \endif
extern int  GetPoliceSize(void);

// \if SIMULATION
//  @GSIM_F:InitDLLGraphique:KSFAM_VISU:
// \endif
extern void InitDLLGraphique(void);

/*! @brief This function replaces a standard character with a special character. 
 *
 *	Up to 128 characters can be redefined. 
 *	@param key : ASCII value of key parameter 
 *	@param pattern : Definition of character, pattern .
 *	@param police : character font.
 *	@return
 *	-  0 if ok,
 *	-  -1 otherwise.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 38) if function does not exist
// \if SIMULATION
//  @GSIM_F:DefGraphicPattern:KSFAM_VISU:
//  @GSIM_A:2:IN_ONLY
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DefGraphicPattern:KSFAM_VISU:
//  @GSIM_A:2:IN_ONLY
// \endif
extern int  DefGraphicPattern(char key,char *pattern,int police);



/*! @brief This function Inserts a bit map at x and y position with the reverse video option in the graphic context, each lines containing bit pixels .
 *
 *	See defdisplaypattern for the bit map definition. 
 *	@param x0 : in range [0,127] 
 *	@param y0 : in range [0,63] 
 *	@param bitmap : points to a bitmap ( defdisplaypattern compatible )
 *	@param bit : the size in bit of a line 
 *	@param reverse : reverse video _ON_ or _OFF_ 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 41) if function does not exist
 *	@note 
 *	-  This is useful when a logo has to be displayed somewhere on the screen. 
 *	-  You should use our tool to convert BMP file to defdisplaypattern compatible bit maps. 
 *	-  Defdisplaypattern is no more useful when using this graphic library. 
 *	- _DisplayBitmap does not refresh the display, DisplayBitmap refresh it.
// \if SIMULATION
//  @GSIM_F:_DisplayBitmap:KSFAM_VISU:
//  @GSIM_S:_DisplayBitmap:E__DisplayBitmap
//  GSIM_A:3:SUPPLIED(BUF_SER_bmp_pattern;BUF_DES_bmp_pattern)
//  GSIM_A:3:IN_ONLY
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DisplayBitmap:KSFAM_VISU:
//  @GSIM_S:_DisplayBitmap:E__DisplayBitmap
//  GSIM_A:3:SUPPLIED(BUF_SER_bmp_pattern;BUF_DES_bmp_pattern)
//  GSIM_A:3:IN_ONLY
// \endif
extern void _DisplayBitmap(int x0,int y0,unsigned char *bitmap,unsigned char bit,int reverse);


/*! @brief This function Inserts a bit map at x and y position with the reverse video option in the graphic context, each lines containing bit pixels .
 *
 *	See defdisplaypattern for the bit map definition. 
 *	@param x0 : in range [0,127] 
 *	@param y0 : in range [0,63] 
 *	@param bitmap points to a bitmap ( defdisplaypattern compatible )
 *	@param bit : the size in bit of a line 
 *	@param reverse : reverse video _ON_ or _OFF_ 
 *	@return None (void).
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 40) if function does not exist
 *	@note 
 *	-  This is useful when a logo has to be displayed somewhere on the screen. 
 *	-  You should use our tool to convert BMP file to defdisplaypattern compatible bit maps.
 *	-  Defdisplaypattern is no more useful when using this graphic library. 
 *	- _DisplayBitmap does not refresh the display, DisplayBitmap refresh it.
// \if SIMULATION
//  @GSIM_F:DisplayBitmap:KSFAM_VISU:
//  @GSIM_S:DisplayBitmap:E_DisplayBitmap
//  GSIM_A:3:SUPPLIED(BUF_SER_bmp_pattern;BUF_DES_bmp_pattern)
//  GSIM_A:3:IN_ONLY
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DisplayBitmap:KSFAM_VISU:
//  @GSIM_S:DisplayBitmap:E_DisplayBitmap
//  GSIM_A:3:SUPPLIED(BUF_SER_bmp_pattern;BUF_DES_bmp_pattern)
//  GSIM_A:3:IN_ONLY
// \endif
extern void DisplayBitmap(int x0,int y0,unsigned char *bitmap,unsigned char bit,int reverse);



/*! @brief This function is used to change the font height used by M2OS.
 *	@param police Font to be selected : 
 *	-  _SMALL _: characters height is 8 pixels 
 *	-  _MEDIUM_ : characters height is 10 pixels 
 *	-  _LARGE_: characters height is 12 pixels 
 *	-  _XLARGE_ : characters height is 16 pixels 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 47) if function does not exist
 *	@note
 *	-  Could be called prior inserting text.
 *	-  There is no link with OEM C routine startupcv20.
 *	-  You also need to initialise the font when creating the graphic context.
// \if SIMULATION
//  @GSIM_F:SetDefaultFont:KSFAM_VISU:
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetDefaultFont:KSFAM_VISU:
// \endif
extern void SetDefaultFont(int police);


/*! @brief This function is used to get the currently font height.
 *	@return Get the font that is currently selected : 
 *	-  _SMALL _: characters height is 8 pixels 
 *	-  _MEDIUM_ : characters height is 10 pixels 
 *	-  _LARGE_ : characters height is 12 pixels 
 *	-  _XLARGE_ : characters height is 16 pixels 
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 48) if function does not exist
// \if SIMULATION
//  @GSIM_F:GetDefaultFont:KSFAM_VISU:
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetDefaultFont:KSFAM_VISU:
// \endif
extern int  GetDefaultFont(void);


/*! @brief This function Converts a bmp file into internal bitmap file and display it instead of the Sagem monetel idle screen "SAGEM EFT930".
 *
 *	Bitmap is displayed starting on the left top corner. 
 *	@param Name : Complete BMP file name (ex : \\SYSTEM\\SCREEN.BMP).
 *	@param ScreenBitmap : screen to be displayed using defgraphicpattern or printf.
 *	@return 
 *	-  BMP_OK 0 
 *	-  BMP_TooBig -2 bitmap is too big (> 144 pixels)
 *	-  BMP_WrongVideo -3 only 16 or 256-color BMPs can be processed
 *	-  BMP_Compression -4 compression not allowed
 *	-  BMP_NoVolumeFound -5 volume not found
 *	-  BMP_NoFileFound -6 file not found
 *	-  BMP_NotEnoughMem -7 not enough memory
 *	-  BMP_ReadError -8 file can not be read
 *	-  BMP_NotAvailable -9 not supported
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 41) if function does not exist
// \if SIMULATION
//  @GSIM_F:BmpToPattern:KSFAM_VISU:
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:ONE_POINTER
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:BmpToPattern:KSFAM_VISU:
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:ONE_POINTER
// \endif
extern int BmpToPattern(char *Name,StructScreen *ScreenBitmap);


/*! @brief This function Places a text in the graphic context at x and y position with or without reverse video option with the selected font and type. 
 *	-  \\n forces x to be resetted (x=0) and y to skip to the next line (y+=fontsize) 
 *	-  \\r forces x to be resetted (x=0) and y is unchanged 
 *	-  Escape character ( \\x1B ) is not handled. 
 *	@param x0 : in range [0,127]
 *	@param y0 : in range [0,127]
 *	@param chaine : pointer to the formatted string to be displayed 
 *	@param reverse : Reverse video : _ON_ or _OFF_ 
 *	@param police : _POLICE5x5_, _POLICE4x7_,_POLICE5x7_, _POLICE7x8_, _POLICE8x12_, _POLICE8x16_, _SMALL_, _MEDIUM_, _LARGE_, _XLARGE_ 
 *	@param type : _NORMALE_ or _PROPORTIONNEL_ 
 *	@return None (void).
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 49) if function does not exist
 *	@note 
 *	-  String is a formatted text ( see printf ). 
 *	-  No blinking possibilities .
 *	- _DrawExtendedString does not refresh the display, DrawExtendedString refresh it.
// \if SIMULATION
//  @GSIM_F:_DrawExtendedString:KSFAM_VISU:
//  @GSIM_A:3:IN_ONLY
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawExtendedString:KSFAM_VISU:
//  @GSIM_A:3:IN_ONLY
// \endif
extern void _DrawExtendedString(int x0,int y0,char *chaine,int reverse,int police,int type);


/*! @brief This function places a text in the graphic context at x and y position with or without reverse video option with the selected font and type 
 *	-  \\n forces x to be resetted (x=0) and y to skip to the next line (y+=fontsize) 
 *	-  \\r forces x to be resetted (x=0) and y is unchanged 
 *	-  Escape character ( \\x1B ) is not handled. 
 *	@param x0 : in range [0,127]
 *	@param y0 : in range [0,127]
 *	@param chaine : pointer on the formatted string to be displayed 
 *	@param reverse : Reverse video : _ON_ or _OFF_ 
 *	@param police : _POLICE5x5_, _POLICE4x7_,_POLICE5x7_, _POLICE7x8_, _POLICE8x12_, _POLICE8x16_, _SMALL_, _MEDIUM_, _LARGE_, _XLARGE_ 
 *	@param type : _NORMALE_ or _PROPORTIONNEL_ 
 *	@return None.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 50) if function does not exist
 *	@note 
 *	-  String is a formatted text ( see printf ). 
 *	-  No blinking possibilities ..
 *	- _DrawExtendedString does not refresh the display, DrawExtendedString refresh it.
// \if SIMULATION
//  @GSIM_F:DrawExtendedString:KSFAM_VISU:
//  @GSIM_A:3:IN_ONLY
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawExtendedString:KSFAM_VISU:
//  @GSIM_A:3:IN_ONLY
// \endif
extern void DrawExtendedString(int x0,int y0,char *chaine,int reverse,int police,int type);


/*! @brief This function calculates the pixels number used by a string in the selected font and type. 
 *
 *	This is important to know how large a string is and check if it is possible to put it on a line. 
 *	@param chaine : pointer on the formatted string to be checked.
 *	@param police : All.
 *	@param type : _NORMALE_ or _PROPORTIONNEL_ 
 *	@return The pixels number used by the given string.
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 51) if function does not exist
 *	@note 'chaine' is a formatted text ( see printf ).
// \if SIMULATION
//  @GSIM_F:_SizeofExtendedString:KSFAM_VISU:
//  @GSIM_A:1:IN_ONLY
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_SizeofExtendedString:KSFAM_VISU:
//  @GSIM_A:1:IN_ONLY
// \endif
extern int _SizeofExtendedString(char *chaine,int police,int type);


#define _PrintString(p0,p1,p2,p3,p4,p5) _PrintChaine(p0,p1,(char *)p2,p3,p4,p5)
#define  PrintString(p0,p1,p2,p3,p4,p5)  PrintChaine(p0,p1,(char *)p2,p3,p4,p5)
#define _SizeofString(p0,p1,p2)         _SizeofChaine((char *)p0,p1,p2)
#define InitContext(p0) InitContexteGraphique(p0)

/*! @brief This function is used to get the current peripheral display.
 *	@return Display used :
 *	-  #PERIPH_DISPLAY          : All graphics on DISPLAY 
 *	-  #PERIPH_DISPLAY_EXTENDED : All graphics on Color DISPLAY 
 *	-  #PERIPH_PPR              : All graphics on PPC30/PPR30/P30
 *	-  #PERIPH_C30              : All graphics on Telium Pass (C30)
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 52) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetGraphicContext:KSFAM_VISU:
// \endif
extern int  GetGraphicContext(void);


/*! @brief This function is used to get the current peripheral mode (Color or B/W)
 *	@return Display used :
 *	-  #PERIPH_DISPLAY 					: All graphics on a B/W DISPLAY
 *	-  #PERIPH_DISPLAY_EXTENDED         : All graphics on a Color DISPLAY
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 120) if function does not exist
 *
 * @link KSFAM_VISU Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetGraphicMode:KSFAM_VISU:
// \endif
extern int  GetGraphicMode(void);
/*! @} **/

/*--------------------------------------------------------------------------------------------*/
// Functions for color display
/*--------------------------------------------------------------------------------------------*/
/*! @addtogroup KSFAM_COLOR Color functions
	* @{
**/

/*
======================================================================
			Functions Definition for Color Display
======================================================================
*/
/*! @brief This function draw a screen into a region directly to display without updating thunder memory(faster than Paint)
 *	
 *	How to display a BMP in FILM mode
 *	@param begin_x : first horizontal pixel
 *	@param last_x : last horizontal pixel
 *	@param begin_y : first vertical pixel
 *	@param last_y : last vertical pixel
 *	@param biBitCount : resolution (always 24 bits)
 *	@param ptdata : Screen to draw (two bytes per pixel 0x0RGB)
 *	@return none
 *  @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 22) if function does not exist
 *	@section sample1

 * @include libgr_Sample_03.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:PaintFilm:KSFAM_COLOR:
//  @GSIM_A:6:DATA_CODE(((last_x-begin_x+1)*(last_y-begin_y+1)*sizeof(unsigned short int))
// \endif
extern void PaintFilm(unsigned short int  begin_x,
                      unsigned short int  last_x,
                      unsigned short int  begin_y,
                      unsigned short int  last_y,
                      unsigned short      biBitCount,
                      void               *ptdata);


/*! @brief This function initialize color screen saver
 *	
 *	@param bitmap : points to a BMP file format
 *	@return 0 if successfull
 *  @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 59) if function does not exist
 *	@section sample2

 * @include libgr_Sample_04.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:ColorScreenSaver:KSFAM_COLOR:
// \endif
extern int ColorScreenSaver(unsigned char *bitmap);


/*! @brief This function Scale stretch an image
 *	
 *	How to display a BMP stretched to fit on the screen
 *	@param src : source image
 *	@param srcwidth : src width
 *	@param srcheight : src height
 *	@param data : result image
 *	@param datawidth : result width
 *	@param dataheight : result height
 *	@return none
 *  @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 21) if function does not exist
 *	@section sample2

 * @include libgr_Sample_05.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Scale:KSFAM_COLOR:
//  @GSIM_A:1:DATA_CODE(srcwidth*srcheight)
//  @GSIM_A:4:DATA_CODE(datawidth*dataheight)
// \endif
extern void Scale(unsigned short int *src,
                  unsigned int        srcwidth,
                  unsigned int        srcheight,
                  unsigned short int *data,
                  unsigned int        datawidth,
                  unsigned int        dataheight);


/*! @brief This function displays an Windows BMP into screen memory
 *	@param x0 : horizontal position
 *	@param y0 : vertical position
 *	@param *bitmap : windows BMP data
 *	@param mode : display mode : unused
 *	@return 
 *	-  #BMP_OK
 *	-  #BMP_NotAvailable
 *	-  #BMP_TooBig
 *	-  #BMP_WrongVideo
 *	-  #BMP_Compression
 *  @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 15) if function does not exist
 *	@section sample3

 * @include libgr_Sample_06.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawBmp:KSFAM_COLOR:
//  @GSIM_A:3:DATA_SIZE(232448)
//  @GSIM_A:3:IN_ONLY
// \endif
extern int _DrawBmp(int x0,int y0,unsigned char *bitmap,int mode);


/*! @brief This function displays an Windows BMP into screen memory and paint region used by the BMP
 *         supported format : BMP 1,4,8,24 bits.
 *	 
 *	This function mount and unmount volume of BMP file
 *	@param x0 : horizontal position
 *	@param y0 : vertical position
 *	@param *Name : Name of file (exemple "/HOST/HELLO.BMP")
 *	@param mode : display mode :
 *		-  FIOCTL_FULL_COLOR
 *			update manager and thunder memory
 *		-  FIOCTL_BITMAP_COLOR_FILM don't update thunder memory (faster)
 *		  	"FILM" mode is faster because the image is not stored into manager internal memory and into thunder internal memory.
 *			Please note, the call to PaintGraphics restores the screen with the content it had before display in "FILM" mode.
 *			This mode is not operationnal on ISC250, ISC350 and IWL280.
 *	-  #BMP_OK
 *	-  #BMP_NotAvailable
 *	-  #BMP_TooBig
 *	-  #BMP_WrongVideo
 *	-  #BMP_Compression
 *  @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 12) if function does not exist
 *	@section sample4

 * @include libgr_Sample_07.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:BmpToScreen:KSFAM_COLOR:
//  @GSIM_A:3:DATA_CODE(strlen(Name)+1)
//  @GSIM_A:3:IN_ONLY
// \endif
extern int BmpToScreen(int x0,int y0,char *Name,int mode);


/*! @brief This function converts BMP to internal format
 *
 *  You must test the value of data to see if the memory has to be desallocated with dllfree.
 *  supported format : BMP 1,4,8 bits.
 *
 *	@param bitmap : bitmap data
 *	@param data : screen
 *	-  #BMP_OK
 *	-  #BMP_NotAvailable
 *	-  #BMP_TooBig
 *	-  #BMP_WrongVideo
 *	-  #BMP_Compression
 *  @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 52) if function does not exist
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_BmpToScreen:KSFAM_COLOR:
//  @GSIM_A:1:DATA_SIZE(232448)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:ONE_POINTER
// \endif
extern int _BmpToScreen(unsigned char *bitmap,unsigned int **data);


/*! @brief This function puts an Windows BMP into memory.
 *
 *  You must test the value of Src to see if the memory has to be desallocated with dllfree.(see sample1)
 *
 *	@param Name : Name of file 
 *	@param Src : pointer to the data memory pointer.  Where Src[y*SrcWidth+x] is pixel value at (x,y) relative in RBG mode (last three quartets are significant)
 *	@param SrcWidth : Width of BMP
 *	@param SrcHeight : Height of BMP
 *	@return 
 *	-  #BMP_OK
 *	-  #BMP_NotAvailable
 *	-  #BMP_TooBig
 *	-  #BMP_WrongVideo
 *	-  #BMP_Compression
 *  @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 20) if function does not exist
 *	@note \ref sample1
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:BmpToMem:KSFAM_COLOR:
//  @GSIM_A:1:DATA_CODE(strlen(Name)+1)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
// \endif
extern int BmpToMem(char *Name,unsigned short **Src,unsigned long *SrcWidth,unsigned long *SrcHeight);


/*! @brief This function displays an Windows BMP into screen memory and paint region used by the BMP
 *         supported format : BMP 1,4,8,24 bits.
 * 
 *	@param x0 : horizontal position
 *	@param y0 : vertical position
 *	@param *bitmap : windows BMP data
 *	@param mode : display mode : 
 *		-  FIOCTL_FULL_COLOR
 *			update manager and thunder memory
 *		-  FIOCTL_BITMAP_COLOR_FILM don't update thunder memory (faster)
 *		  	"FILM" mode is faster because the image is not stored into manager internal memory and into thunder internal memory.
 *			Please note, the call to PaintGraphics restores the screen with the content it had before display in "FILM" mode.
 *			This mode is not operationnal on ISC250, ISC350 and IWL280.
 *	@return 
 *	-  #BMP_OK
 *	-  #BMP_NotAvailable
 *	-  #BMP_TooBig
 *	-  #BMP_WrongVideo
 *	-  #BMP_Compression
 *  @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 14) if function does not exist
 *	@section sample5

 * @include libgr_Sample_08.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawBmp:KSFAM_COLOR:
//  @GSIM_A:3:DATA_SIZE(232448)
//  @GSIM_A:3:IN_ONLY
// \endif
extern int DrawBmp(int x0,int y0,unsigned char *bitmap,int mode);


/*! @brief This function displays a bitmap into a rectangle (stretch)
 *	@param *bitmap 		: windows BMP data
 *	@param left,right :	horizontal coordonate
 *	@param top,bottom :	vertical coordonate
 *	@return none
 *  @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 13) if function does not exist
 *	@section sample6

 * @include libgr_Sample_09.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:StretchBmp:KSFAM_COLOR:
//  @GSIM_A:1:DATA_SIZE(232448)
//  @GSIM_A:1:IN_ONLY
// \endif
extern int StretchBmp(unsigned char *bitmap,int left,int top,int right,int bottom);


/*! @brief This function displays an ISO 8859 coded string into screen memory and paint region used by the string.
 *
 *	This function use current font of caller
 *	@param x0 : horizontal position
 *	@param y0 : vertical position
 *	@param *message : the ISO 8859 coded string
 *	@param *police : font name
 *	@param type : _FIXED_WIDTH_ or _PROP_WIDTH_
 *	@param pen : color of the text in ARGB mode (0xAARRGGBB)
 *	@param brush : color of the background in ARGB mode (0xAARRGGBB)
 *	@return 
 *	-    0 : OK.
 *	-   -1 : Missing police.
 *	-   -2 : Missing char inside message.
 *  @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 19) if function does not exist
 *	@section sample7

 * @include libgr_Sample_10.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawText8859:KSFAM_COLOR:
//  @GSIM_A:3:DATA_CODE(strlen(message)+1)
//  @GSIM_A:3:IN_ONLY
//  @GSIM_A:4:DATA_CODE(strlen(police)+1)
//  @GSIM_A:4:IN_ONLY
// \endif
int DrawText8859(int x0,int y0,unsigned char *message,char *police,int type,int pen,int brush);


/*! @brief This function displays an ISO 8859 coded string into screen memory.
 *
 *	This function use current font of caller
 *	@param x0 : horizontal position
 *	@param y0 : vertical position
 *	@param *message : the ISO 8859 coded string
 *	@param *police : font name
 *	@param type : _FIXED_WIDTH_ or _PROP_WIDTH_
 *	@param pen : color of the text in ARGB mode (0xAARRGGBB)
 *	@param brush : color of the background in ARGB mode (0xAARRGGBB)
 *	@return 
 *	- 0 : OK.
 *	- -1 : Missing police.
 *	- -2 : Missing char inside message.
 *  @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 18) if function does not exist
 *	@section sample8

 * @include libgr_Sample_11.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawText8859:KSFAM_COLOR:
//  @GSIM_A:3:DATA_CODE(strlen(message)+1)
//  @GSIM_A:3:IN_ONLY
//  @GSIM_A:4:DATA_CODE(strlen(police)+1)
//  @GSIM_A:4:IN_ONLY
// \endif
int _DrawText8859(int x0,int y0,unsigned char *message,char *police,int type,int pen,int brush);


/*! @brief This function displays an ISO 8859 coded string into screen memory with a local font file
 * @param BufferFont : Font data pointer
 * @param x0 : horizontal position
 * @param y0 : vertical position
 * @param *message : the ISO 8859 coded string
 * @param *police : font name
 * @param type : _FIXED_WIDTH_ or _PROP_WIDTH_
 * @param pen : color of the text in ARGB mode (0xAARRGGBB)
 * @param brush : color of the background in ARGB mode (0xAARRGGBB)
 * @return 
 *	-  0 : OK.
 *	-  -1 : Missing police.
 *	-  -2 : Missing char inside message.
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 47) if function does not exist
 * @section sample9

 * @include libgr_Sample_12.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawFont8859:KSFAM_COLOR:
//  @GSIM_A:1:DATA_SIZE(8192)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:4:DATA_CODE(strlen(message)+1)
//  @GSIM_A:4:IN_ONLY
//  @GSIM_A:5:DATA_CODE(strlen(police)+1)
//  @GSIM_A:5:IN_ONLY
// \endif
int _DrawFont8859(unsigned char *BufferFont,int x0,int y0,unsigned char *message,char *police,int type,int pen,int brush);



/*! @brief This function displays an ISO 8859 coded string into screen memory and paints region used by the string with a local font file
 * @param BufferFont : Font data pointer
 * @param x0 : horizontal position
 * @param y0 : vertical position
 * @param *message : the ISO 8859 coded string
 * @param *police : font name
 * @param type : _FIXED_WIDTH_ or _PROP_WIDTH_
 * @param pen : color of the text in ARGB mode (0xAARRGGBB)
 * @param brush : color of the background in ARGB mode (0xAARRGGBB)
 * @return 
 *	- 0 : OK.
 *	- -1 : Missing police.
 *	- -2 : Missing char inside message.
 * @section sample10

 * @include libgr_Sample_13.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawFont8859:KSFAM_COLOR:
//  @GSIM_A:1:DATA_SIZE(8192)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:4:DATA_CODE(strlen(message)+1)
//  @GSIM_A:4:IN_ONLY
//  @GSIM_A:5:DATA_CODE(strlen(police)+1)
//  @GSIM_A:5:IN_ONLY
// \endif
int DrawFont8859(unsigned char *BufferFont,int x0,int y0,unsigned char *message,char *police,int type,int pen,int brush);



/*! @brief This function displays a unicode coded string into screen memory and paint region used by the string.
 * @param x0 : horizontal position
 * @param y0 : vertical position
 * @param *message : the unicode coded string
 * @param *police : font name
 * @param type : _FIXED_WIDTH_ or _PROP_WIDTH_
 * @param pen : color of the text in ARGB mode (0xAARRGGBB)
 * @param brush : color of the background in ARGB mode (0xAARRGGBB)
 * @return 
 *	- 0 : OK.
 *	- -1 : Missing police.
 *	- -2 : Missing char inside message.
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 16) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawTextUnicode:KSFAM_COLOR:
//  @GSIM_A:3:DATA_CODE(2*strlenUNICODE(message)+2)
//  @GSIM_A:3:IN_ONLY
//  @GSIM_A:4:DATA_CODE(strlen(police)+1)
//  @GSIM_A:4:IN_ONLY
// \endif
int DrawTextUnicode(int x0,int y0,unsigned char *message,char *police,int type,int pen,int brush);


/*! @brief This function displays a unicode coded string into screen memory
 * @param x0 				: horizontal position
 * @param y0 				: vertical position
 * @param *message 	: the unicode coded string
 * @param *police 	: font name
 * @param type 			: _FIXED_WIDTH_ or _PROP_WIDTH_
 * @param pen 			: color of the text in ARGB mode (0xAARRGGBB)
 * @param brush 		: color of the background in ARGB mode (0xAARRGGBB)
 * @return 
 *	- 0 : OK.
 *	- -1 : Missing police.
 *	- -2 : Missing char inside message.
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 17) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawTextUnicode:KSFAM_COLOR:
//  @GSIM_A:3:DATA_CODE(2*strlenUNICODE(message)+2)
//  @GSIM_A:3:IN_ONLY
//  @GSIM_A:4:DATA_CODE(strlen(police)+1)
//  @GSIM_A:4:IN_ONLY
// \endif
int _DrawTextUnicode(int x0,int y0,unsigned char *message,char *police,int type,int pen,int brush);


/*! @brief This function displays a UNICODE coded string into screen memory with a local font file
 * @param BufferFont  : Font data pointer
 * @param x0 					: horizontal position
 * @param y0 					: vertical position
 * @param *message 		: the UNICODE coded string
 * @param *police 		: font name
 * @param type 				: _FIXED_WIDTH_ or _PROP_WIDTH_
 * @param pen 				: color of the text in ARGB mode (0xAARRGGBB)
 * @param brush 			: color of the background in ARGB mode (0xAARRGGBB)
 * @return 
 *	- 0 : OK.
 *	- -1 : Missing police.
 *	- -2 : Missing char inside message.
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 57) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_DrawFontUnicode:KSFAM_COLOR:
//  @GSIM_A:1:DATA_SIZE(8192)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:4:DATA_CODE(2*strlenUNICODE(message)+2)
//  @GSIM_A:4:IN_ONLY
//  @GSIM_A:5:DATA_CODE(strlen(police)+1)
//  @GSIM_A:5:IN_ONLY
// \endif
int _DrawFontUnicode(unsigned char *BufferFont,int x0,int y0,unsigned char *message,char *police,int type,int pen,int brush);



/*! @brief This function displays a UNICODE coded string into screen memory and paint region used by the string with a local font file
 * @param BufferFont  : Font data pointer
 * @param x0 					: horizontal position
 * @param y0 					: vertical position
 * @param *message 		: the UNICODE coded string
 * @param *police 		: font name
 * @param type 				: _FIXED_WIDTH_ or _PROP_WIDTH_
 * @param pen 				: color of the text in ARGB mode (0xAARRGGBB)
 * @param brush 			: color of the background in ARGB mode (0xAARRGGBB)
 * @return 
 *	-  0 : OK.
 *	- -1 : Missing police.
 *	- -2 : Missing char inside message.
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 56) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:DrawFontUnicode:KSFAM_COLOR:
//  @GSIM_A:1:DATA_SIZE(8192)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:4:DATA_CODE(2*strlenUNICODE(message)+2)
//  @GSIM_A:4:IN_ONLY
//  @GSIM_A:5:DATA_CODE(strlen(police)+1)
//  @GSIM_A:5:IN_ONLY
// \endif
int DrawFontUnicode(unsigned char *BufferFont,int x0,int y0,unsigned char *message,char *police,int type,int pen,int brush);


/*! @brief This function selects a region for color functions to limit display into this region
 * @param left,right : horizontal coordonate of region
 * @param top,bottom : vertical coordonate of region
 * @return None
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 43) if function does not exist
 * @section sample11

 * @include libgr_Sample_14.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetRegionColor:KSFAM_COLOR:
// \endif
extern int SetRegionColor(int left,int top,int right,int bottom);


/*! @brief This function gets current region coordinate for color functions
 * @param left,right : horizontal coordonate of region
 * @param top,bottom : vertical coordonate of region
 * @return none
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 44) if function does not exist
 * @note \ref sample11
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetRegionColor:KSFAM_COLOR:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
// \endif
extern int GetRegionColor(int *left,int *top,int *right,int *bottom);


/*! @brief This function clears region and restores original region size
 * @return None
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 45) if function does not exist
 * @note \ref sample11
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:ClearRegionColor:KSFAM_COLOR:
// \endif
extern int ClearRegionColor(void);


/*! @brief This function is used to put a small color screen into terminal screen memory
 * @param x0 									: x coordinate
 * @param y0 									: y coordinate
 * @param SrcWidth,SrcHeight  : size of screen
 * @param Screen 							: array of SrcWidth*SrcHeight color
 * @return 
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 39) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_SetScreenToScreen:KSFAM_COLOR:
//  @GSIM_A:3:DATA_SIZE(SrcWidth*SrcHeight)
// \endif
extern int _SetScreenToScreen (int x0,int y0,unsigned short int *Screen,unsigned long SrcWidth,unsigned long SrcHeight);


/*! @brief This function is used to put a small color screen into terminal screen and paint region used by the screen.
 * @param x0 : x coordinate
 * @param y0 : y coordinate
 * @param SrcWidth,SrcHeight : size of screen
 * @param Screen : array of SrcWidth*SrcHeight color
 * @return 
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 40) if function does not exist
 * @note \ref sample11
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetScreenToScreen:KSFAM_COLOR:
//  @GSIM_A:3:DATA_SIZE(SrcWidth*SrcHeight)
// \endif
extern int SetScreenToScreen (int x0,int y0,unsigned short int *Screen,unsigned long SrcWidth,unsigned long SrcHeight);


/*! @brief This function gets pixel from screen memory and return in 32 bits mode
 * @param x,y : pixel coordonates
 * @return color in RBG mode (0xFFR0G0B0)
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 41) if function does not exist
 * @section sample12

 * @include libgr_Sample_15.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetPixelColor:KSFAM_COLOR:
// \endif
extern int GetPixelColor(int x,int y);

/*! @brief This routine saves the graphic color context to be restored later.
 * @param screen : pointer on the graphic color context.
 * @return pointer to internal screen
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 25) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SaveScreenExtended:KSFAM_COLOR:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern StructScreenExtended *SaveScreenExtended(StructScreenExtended *screen);


/*! @brief This function restores the whole graphic color context previously saved in screen.
 * @param screen : pointer on the graphic color context.
 * @return None.
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 26) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:RestoreScreenExtended:KSFAM_COLOR:
//  @GSIM_A:1:ONE_POINTER
// \endif
extern void RestoreScreenExtended(StructScreenExtended *screen);


/*! @brief This function fills screen with a color
 * @param color : color in ARBG mode (0xAARRGGBB)
 * @return None
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 37) if function does not exist
 * @note \ref sample12
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_ClearScreen:KSFAM_COLOR:
// \endif
 extern void _ClearScreen(int color);


/*! @brief This function puts pixel into screen memory
 * @param x,y 	: pixel coordonates
 * @param color : color in ARBG mode (0xAARRGGBB)
 * @return None
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 36) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_Pixel:KSFAM_COLOR:
// \endif
extern void _Pixel(int x,int y,int color);


/*! @brief This function puts pixel into screen memory and paints region used by the pixel
 * @param x,y 	: pixel coordonates
 * @param color : color in ARBG mode (0xAARRGGBB)
 * @return None 
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 33) if function does not exist
 * @note \ref sample12
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Pixel:KSFAM_COLOR:
// \endif
extern void Pixel(int x,int y,int color);


/*! @brief This function fills a region into screen memory
 * @param left,right : horizontal coordonate
 * @param top,bottom : vertical coordonate
 * @param color 		 : color in ARBG mode (0xAARRGGBB)
 * @return None
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 23) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_Area:KSFAM_COLOR:
// \endif
extern void _Area(int left,int top,int right,int bottom,int color);


/*! @brief This function fills a region into screen memory and paints region used by the region
 * @param left,right : horizontal coordonate
 * @param top,bottom : vertical coordonate
 * @param color 		 : color in ARBG mode (0xAARRGGBB)
 * @return None
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 38) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Area:KSFAM_COLOR:
// \endif
extern void Area(int left,int top,int right,int bottom,int color);


/*! @brief This function draws a line into screen memory from (x1,y1) to (x2,y2)
 * @param x1,y1 : first point
 * @param x2,y2 : last point
 * @param color : color in ARBG mode (0xAARRGGBB)
 * @return none
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 35) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_Line:KSFAM_COLOR:
// \endif
extern void _Line(int x1,int y1,int x2,int y2,int color);


/*! @brief This function draws a line into screen memory from (x1,y1) to (x2,y2) and paints region used by the line
 * @param x1,y1 : first point
 * @param x2,y2 : last point
 * @param color : color in ARBG mode (0xAARRGGBB)
 * @return none
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 34) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Line:KSFAM_COLOR:
// \endif
extern void Line(int x1,int y1,int x2,int y2,int color);


/*! @brief This function draws a circle into screen memory
 * @param x0,y0 : origin of the circle
 * @param r 		: radius of the circle
 * @param pen 	: color of the border in ARBG mode (0xAARRGGBB)
 * @param brush : color of the circle in ARBG mode (0xAARRGGBB)
 * @return None
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 31) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_Circle:KSFAM_COLOR:
// \endif
extern void _Circle(int x0,int y0,int r,int pen,int brush);



/*! @brief This function draws a circle into screen memory and paints region used by the circle
 * @param x0,y0 : origin of the circle
 * @param r 		: radius of the circle
 * @param pen 	: color of the border in ARBG mode (0xAARRGGBB)
 * @param brush : color of the circle in ARBG mode (0xAARRGGBB)
 * @return None
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 29) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Circle:KSFAM_COLOR:
// \endif
extern void Circle(int x0,int y0,int r,int pen,int brush);


/*! @brief This function draws an ellipse into screen memory
 * @param x0,y0 : origin of the ellipse
 * @param rx 		: horizontal radius of the ellipse
 * @param ry 		: vertical radius of the ellipse
 * @param pen 	: color of the border in ARBG mode (0xAARRGGBB)
 * @param brush : color of the ellipse in ARBG mode (0xAARRGGBB)
 * @return None
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 28) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_Ellipse:KSFAM_COLOR:
// \endif
extern void _Ellipse(int x0,int y0,int rx,int ry,int pen,int brush);


/*! @brief This function draws an ellipse into screen memory and paints region used by the ellipse
 * @param x0,y0 : origin of the ellipse
 * @param rx 		: horizontal radius of the ellipse
 * @param ry 		: vertical radius of the ellipse
 * @param pen 	: color of the border in ARBG mode (0xAARRGGBB)
 * @param brush : color of the ellipse in ARBG mode (0xAARRGGBB)
 * @return None
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 27) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Ellipse:KSFAM_COLOR:
// \endif
extern void Ellipse(int x0,int y0,int rx,int ry,int pen,int brush);


/*! @brief This function draws a rectangle into screen memory
 * @param left,right : horizontal coordonate
 * @param top,bottom : vertical coordonate
 * @param thickness  : thickness
 * @param pen 			 : color of the border in ARBG mode (0xAARRGGBB)
 * @param brush 		 : color of the rectangle in ARBG mode (0xAARRGGBB)
 * @return None
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 30) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:_Rect:KSFAM_COLOR:
// \endif
extern void _Rect(int left,int top,int right,int bottom,int thickness,int pen,int brush);


/*! @brief this function draws a rectangle into the screen memory and paint region used by the rectangle
 * @param left,right : horizontal coordonate
 * @param top,bottom : vertical coordonate
 * @param thickness  : thickness
 * @param pen 			 : color of the border in ARBG mode (0xAARRGGBB)
 * @param brush 		 : color of the rectangle in ARBG mode (0xAARRGGBB)
 * @return None
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 32) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Rect:KSFAM_COLOR:
// \endif
extern void Rect(int left,int top,int right,int bottom,int thickness,int pen,int brush);


/*! @brief This function sets the background color and the text color
 * @param backgrd : background color RGB format (0x00RRGGBB)
 * @param texte 	: text color RGB format (0x00RRGGBB)
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 132) if function does not exist
 * @section sample13

 * @include libgr_Sample_16.c
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:SetColor:KSFAM_COLOR:
// \endif
extern void SetColor(int  backgrd,int  texte);


/*! @brief This function gets the background color and the text color
 * @param backgrd : return the background color RGB format (0x00RRGGBB)
 * @param texte 	: return text color RGB format (0x00RRGGBB)
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 53) if function does not exist
 * @note \ref sample12
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetColor:KSFAM_COLOR:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
// \endif
extern void GetColor(int *backgrd,int *texte);


/*! @brief This function returns infos about a BMP image
 * @param bitmap		 : source image
 * @param biWidth 	 : Width of image
 * @param biHeight	 : Height of image
 * @param biBitCount : resolution of image (1,4,16,24 bits)
 * @return None
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 122) if function does not exist
 * @note \ref sample2
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetBmpInfos:KSFAM_COLOR:
//  @GSIM_A:1:DATA_SIZE(8192)
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
// \endif
extern int GetBmpInfos(unsigned char   *bitmap,
                       unsigned long   *biWidth,
                       unsigned long   *biHeight,
                       unsigned short  *biBitCount);


/*! @brief This function redraws user area into memory
 * @param begin_x : first horizontal pixel of user area
 * @param last_x : last horizontal pixel of user area
 * @param begin_y : first vertical pixel of user area
 * @param last_y : last vertical pixel of user area
 * @return none
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 106) if function does not exist
 * @note \ref sample13
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:RedrawUserArea:KSFAM_COLOR:
// \endif
extern void RedrawUserArea    (unsigned short int begin_x,unsigned short int last_x,unsigned short int begin_y,unsigned short int last_y);


/*! @brief This function refreshes the user area
 * @param begin_x : first horizontal pixel of user area
 * @param last_x 	: last horizontal pixel of user area
 * @param begin_y : first vertical pixel of user area
 * @param last_y 	: last vertical pixel of user area
 * @return none
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 105) if function does not exist
 * @note \ref sample13
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:RefreshUserArea:KSFAM_COLOR:
// \endif
extern void RefreshUserArea    (unsigned short int begin_x,unsigned short int last_x,unsigned short int begin_y,unsigned short int last_y);


/*! @brief This function paints a region
 * @param begin_x : first horizontal pixel
 * @param last_x	: last horizontal pixel
 * @param begin_y : first vertical pixel
 * @param last_y 	: last vertical pixel
 * @return none
 * @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 104) if function does not exist
 * @note \ref sample3
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Paint:KSFAM_COLOR:
// \endif
extern void Paint    (unsigned short int begin_x,unsigned short int last_x,unsigned short int begin_y,unsigned short int last_y);


/*! @brief This function is used to Get the Height and Width of the color screen.
 * @param height : Pointers on screen height.
 * @param width 	: Pointers on screen width.
 * @return None.
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 53) if function does not exist
 * @note You need to know the size of the graphic area prior creating the graphic context. 
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetColorScreenSize:KSFAM_VISU:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
// \endif
extern void GetColorScreenSize(int *height,int *width);

/*! @brief This function gets current area coordinate for color display
 * @param left,right : horizontal coordonate of region
 * @param top,bottom : vertical coordonate of region
 * @return none
 * @par exit (EXIT_DLL_COLOR_NOT_INITIALIZED + 58) if function does not exist
 *
 * @link KSFAM_COLOR Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:GetColorScreenArea:KSFAM_COLOR:
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
// \endif
extern void GetColorScreenArea(int *left,int *top,int *right,int *bottom);



#endif 
/*! @} **/
