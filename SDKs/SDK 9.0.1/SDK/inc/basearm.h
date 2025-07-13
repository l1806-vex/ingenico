/*! @addtogroup KSFAM_OS
	* @{
 */ 


#ifndef _BASEARM_H
#define _BASEARM_H


/*
======================================================================
					RealTime Craft products common constants and types 
======================================================================
*/

#define  		cOK             0  /*!< The use of this definition is not restricted to XEC and may have to be put apart */
#ifndef			TRUE
#define    	TRUE            1
#endif
#ifndef			FALSE
#define    	FALSE           0
#endif

/*
======================================================================
	 The 3 following type definitions must be tuned to conform
   to the integer representation of the given compiler !!!
   Their use is not restricted to XEC and they may have
   to be put apart
======================================================================
*/

/*! @brief Define a byte on 8 bits.  This type definitions must be tuned to conform to the integer representation of the given compiler !*/
typedef unsigned char 		Byte;					/*!< Byte : 8 bits*/

/*! @brief Define a byte on 8 bits. This type definitions must be tuned to conform to the integer representation of the given compiler !*/
typedef unsigned char 		byte;					/*!< byte : 8 bits*/

/*! @brief Define a boolean type.  This type definitions must be tuned to conform to the integer representation of the given compiler !*/
typedef Byte 		Boolean;								/*!< Boolean : 0 = false, 1 = true.*/

/*! @brief Define a word on 16 bits.  This type definitions must be tuned to conform to the integer representation of the given compiler !*/
typedef unsigned short int  	Word;			/*!< signed or unsigned integer on 16 bits.*/

/*! @brief Define a word on 16 bits. This type definitions must be tuned to conform to the integer representation of the given compiler !*/
typedef unsigned short int  	word;			/*!< signed or unsigned integer on 16 bits.*/

/*! @brief Define a doubleword on 32 bits. This type definitions must be tuned to conform to the integer representation of the given compiler !*/
typedef unsigned int 		DoubleWord;			/*!< signed or unsigned integer on 32 bits*/

/*! @brief Define a doubleword on 32 bits. This type definitions must be tuned to conform to the integer representation of the given compiler! */
typedef unsigned int 		doubleword;			/*!< signed or unsigned integer on 32 bits*/

/*! @brief Define an address.*/
typedef DoubleWord 	Address;			



#endif

/*! @}  */ 
