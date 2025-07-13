/*! @addtogroup KSFAM_VISU
	* @{
**/
/*
======================================================================
					List of Defines
======================================================================
*/

#ifndef __POLICE_H_
#define __POLICE_H_

#define CAR_MAX    152
#define POLICE5x5   0
#define POLICE4x7   1
#define POLICE5x7   2
#define POLICE6x8   3
#define POLICE7x8   4
#define POLICE8x12  5
#define POLICE8x14  6
#define POLICE10x16 7


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function displays a string of characters
 *	@param x0 : coordinates.
 *	@param y0 : coordinates.
 *	@param chaine  : string to be printed.
 *	@param reverse : reverse option (on or off).
 *	@param police  : font.
 *	@param type    : type of display (proportional or normal).
 *	@return None
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 45) if function does not exist
// \if SIMULATION
//  @GSIM_F:_PrintChaine:KSFAM_VISU:0x66
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
extern void _PrintChaine(int x0,int y0,char *chaine,int reverse,int police,int type);


/*! @brief This function displays a string of characters
 *	@param x0, y0  : coordinates.
 *	@param chaine  : string to be printed.
 *	@param reverse : reverse option (on or off).
 *	@param police  : font.
 *	@param type    : type of display (proportional or normal).
 *	@return None
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 46) if function does not exist
// \if SIMULATION
//  @GSIM_F:PrintChaine:KSFAM_VISU:0x65
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
extern void PrintChaine(int x0,int y0,char *chaine,int reverse,int police,int type);


/*! @brief This function scrolls a string into a rectangle.
 *	@param x0 : parameter left, in range [0,127].
 *	@param y0 : parameter top in range [0,127].
 *	@param x1 : parameter right, in range [0,127] .
 *	@param chaine  : string to be written in rectangle.
 *	@param reverse : reverse video : _ON_ or _OFF_ 
 *	@param police  : _POLICE5x5_, _POLICE4x7_,_POLICE5x7_, _POLICE7x8_, _POLICE8x12_, _POLICE8x16_, _SMALL_, _MEDIUM_, _LARGE_, _XLARGE_ 
 *	@param type    : _NORMALE_ or _PROPORTIONNEL_ 
 *	@param offset  : offset in pixels.
 *	@return None
 *  @par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 43) if function does not exist
// \if SIMULATION
//  @GSIM_F:_ScrollString:KSFAM_VISU:
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
extern void _ScrollString(int x0,int y0,int x1,char *chaine,int reverse,int police,int type,int offset);


/*! @brief This function scrolls a string into a rectangle.
//! \param x0      : parameter left, in range [0,127].
//! \param y0 		 : parameter top in range [0,127].
//! \param x1 		 : parameter right, in range [0,127] .
//! \param chaine  : string to be written in rectangle.
//! \param reverse : reverse video : _ON_ or _OFF_ 
//! \param police  : _POLICE5x5_, _POLICE4x7_,_POLICE5x7_, _POLICE7x8_, _POLICE8x12_, _POLICE8x16_, _SMALL_, _MEDIUM_, _LARGE_, _XLARGE_ 
//! \param type 	 : _NORMALE_ or _PROPORTIONNEL_ 
//! \param offset  : offset in pixels.
//! \return None.
//! \par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 44) if function does not exist
// \if SIMULATION
//  @GSIM_F:ScrollString:KSFAM_VISU:0x7E
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
extern void ScrollString(int x0,int y0,int x1,char *chaine,int reverse,int police,int type,int offset);


/*! @brief This function calculates the pixels number used by a string in the selected font and type. 
//! This is important to know how large a string is and check if it is possible to put it on a line.
//! \param chaine : pointer on the formatted string to be checked 
//! \param police : Not available for following polices _SMALL_, _MEDIUM_, _LARGE_,
//! \param type : _NORMALE_ or _PROPORTIONNEL_
//! \return 
//! The pixels number used by the given string.
//! \par exit (EXIT_DLL_LIBGR_NOT_INITIALIZED + 42) if function does not exist
//! \note 
//! 'chaine' is a formatted text ( see printf ).
// \if SIMULATION
//  @GSIM_F:_SizeofChaine:KSFAM_VISU:0x7C
// \endif
 *
 * @link KSFAM_VISU Back to top @endlink
*/
extern int  _SizeofChaine(char *chaine,int police,int type);

#endif

/*! @} **/
