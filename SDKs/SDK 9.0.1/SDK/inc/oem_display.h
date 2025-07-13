/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef __DISPLAY_H_INCLUDED__
#define __DISPLAY_H_INCLUDED__

/*
======================================================================
					List of Defines
======================================================================
*/

//DON'T USE THESE DEFINES ANYMORE - USE INFORMATIONS GIVEN IN DISPLAY_SCREEN_INFO_FIOCTL
#define  NB_LIGNE_DISPLAY_COLOR             240				/*!< Number of line for the display (DO NOT USE ANYMORE) */
#define  NB_COLONNE_DISPLAY_COLOR           320				/*!< Number of columns for the display (DO NOT USE ANYMORE) */


//List of fioctl 
#define  FIOCTL_SET_FULL_COLOR              0x8000      /*!<  Command to enable or disable Full color mode (pointeur to an unsigned char parameter : TRUE / FALSE) */
#define  FIOCTL_SET_COLOR_DISPLAY           0x8001      /*!<  Command to pass a DISPLAY_COLOR_FIOCTL structure : set the text and background color in compatible mode */
#define  FIOCTL_BITMAP_COLOR                0x8002      /*!<  Command to pass a DISPLAY_BITMAP_COLOR_FIOCTL structure : write in the display screen buffer and set a refresh in the periodcal task */
#define  FIOCTL_BITMAP_COLOR_FILM           0x8003      /*!<  Command to pass a DISPLAY_BITMAP_COLOR_FILM_FIOCTL structure : send directly to the Booster the bitmap in the current task */
#define  FIOCTL_RECTANGLE_COLOR             0x8004      /*!<  Command to pass a DISPLAY_RECTANGLE_COLOR_FIOCTL structure : write in the display screen buffer and set a refresh in the periodcal task  */
#define  FIOCTL_COLOR_REFRESH               0x8005      /*!<  Command to pass a DISPLAY_BITMAP_COLOR_FIOCTL structure : refresh coordinated area in the current task */      
#define  FIOCTL_WRITE_COLOR_BMP             0x8006      /*!<  Command to pass a DISPLAY_BITMAP_COLOR_FIOCTL structure : write in the display screen buffer */
#define  FIOCTL_GET_FULL_COLOR              0x8007      /*!<  Command to get the display mode (full color or not : pointeur to an unsigned char parameter) */
#define  FIOCTL_GET_COLOR_DISPLAY           0x8008      /*!<  Command to get the current DISPLAY_COLOR_FIOCTL structure */
#define  FIOCTL_GET_SCREEN_INFO             0x8009      /*!<  Command to get the screen informations (DISPLAY_SCREEN_INFO_FIOCTL structure) */
#define  FIOCTL_READ_COLOR_BMP              0x800A      /*!<  Command to pass a DISPLAY_BITMAP_COLOR_FIOCTL structure : return the encoding kind and saved coordinated bitmap (with a dll_malloc) */
#define  FIOCTL_CMD_EXTERNAL_DISPLAY        0x800B      /*!< TO_BE_DOCUMENTED */
#define  FIOCTL_FLUSH_DISPLAY               0x800C      /*!<  Command to flush display buffer to screen (NULL parameter) */


//Encoding kind
#define ENCODED_RGB12_16BITS            0  /*!<  12 bits / pixels coded on 16 bits */
#define ENCODED_256COUL                 1  /*!<  256 color + color conversion table (only for film mode) */
#define ENCODED_RGB24_32BITS            2  /*!<  24 bits / pixels coded on 32 bits */
#define ENCODED_RGB24_24BITS            3  /*!<  24 bits / pixels coded on 24 bits */
#define ENCODED_RGB16_16BITS            4  /*!<  16 bits / pixels coded on 16 bits */

//Bitmap kind
#define TYPE_PARTIAL_BITMAP     	0		/*!< The pointed bitmap passed comes from the passed coordinated bitmap  */
#define TYPE_FULL_BITMAP	    	1		/*!< The pointed  passed comes from a full bitmap (full height * full width)  */


//Type command
#define TYPE_CMD_OFF      0		/*!< TO_BE_DOCUMENTED */
#define TYPE_CMD_ON       1		/*!< TO_BE_DOCUMENTED */


//Fioctl returns
#define COLOR_SUCCESS      	         0		/*!< Return if the fioctl command is successful */
#define COLOR_NOT_IMPLEMENTED	    -1      /*!< Return if the fioctl command is unknown */
#define COLOR_ERROR_COORD 	        -2      /*!<  Return if there is an error in the DISPLAY_COORD_BMP_COLOR structure */
#define COLOR_ERROR_NO_FULL_COLOR   -3      /*!<  Return if you have passed an refresh command while the display is not in Full Color mode (the refresh is not done) */
#define COLOR_ERROR_IUC      	    -4      /*!<  Return if there was an transmit error to the Booster */
#define COLOR_ERROR_UNKNOWN_ENCODED -5      /*!<  Return if the "type_encoded" field is unknown */
#define COLOR_ERROR_UNKNOWN_TYPE    -6      /*!<  Return if the "type_bmp" field is unknown */
#define COLOR_ERROR_DLL_MALLOC      -7      /*!<  Return if the buffer malloc in FIOCTL_READ_COLOR_BMP command lead to an error */


/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief  Bitmap coordinates structure */
typedef struct
{
   unsigned short int      	begin_x;		/*!< Bitmap start on x axe */
   unsigned short int      	last_x;			/*!< Bitmap End  on x axe (included) */
   unsigned short int 		begin_y;		/*!< Bitmap start on y axe */
   unsigned short int 		last_y;			/*!< Bitmap End  on y axe (included) */
   unsigned int				size;			/*!< Bitmap size in pixel number */
}DISPLAY_COORD_BMP_COLOR;


/*! @brief Colors for bicolor compatible mode (when Full color mode is disable) */ 
typedef struct
{
   unsigned int         type_encoded;			/*!< Encoding kind for text and background colors */
   unsigned int         text_color;				/*!< Text color */
   unsigned int         background_color;		/*!< Background color */
   unsigned short int	ruf[6];					/*!< ruf */
}DISPLAY_COLOR_FIOCTL;


/*! @brief Bitmap structure for normal display mode */
typedef struct
{
   DISPLAY_COORD_BMP_COLOR	coord_bitmap;		/*!< Bitmap coordinates */
   void		                *bitmap;			/*!< Pointeur to bitmap pixel data */
   unsigned int      	    type_bmp;			/*!< Bitmap kind */
   unsigned int         	type_encoded;		/*!< Encoding kind */
   unsigned int             ruf[2];				/*!< ruf */
}DISPLAY_BITMAP_COLOR_FIOCTL;


/*! @brief Bitmap structure for film  mode */
typedef struct
{
   DISPLAY_COORD_BMP_COLOR	coord_bitmap;			/*!< Bitmap coordinates */
   unsigned int           	type_encoded;			/*!< Encoding kind */
   unsigned int            	*palette_couleur;		/*!< Pointeur to color conversion table */
   void		                *bitmap;				/*!< Pointeur to bitmap pixel data */
   unsigned int      	    ruf[2];					/*!< ruf */
}DISPLAY_BITMAP_COLOR_FILM_FIOCTL;



/*! @brief Fioctl rectangle */
typedef struct
{
   DISPLAY_COORD_BMP_COLOR	coord_bitmap;			/*!< Bitmap coordinates */
   unsigned int      	    couleur;				/*!< Rectangle color */
   unsigned int             type_encoded;			/*!< Encoding kind */
   unsigned int      	    ruf[2];					/*!< ruf */
}DISPLAY_RECTANGLE_COLOR_FIOCTL;



/*! @brief Screen informations */
typedef struct
{
   unsigned short int	phys_width;             /*!< Physical width */
   unsigned short int   phys_height;            /*!< Physical height */
   unsigned short int   bits_per_pixel;         /*!<  1Number of bits per pixel : 2 - 18 - 24 */ 
   unsigned short int   rotate;                 /*!<  0 - 90 - 180 - 270 */
   unsigned short int   width;                  /*!<  Width according to the screen rotation(defined by "rotate") */
   unsigned short int   height;                 /*!<  Heigh according to the screen rotation(defined by "rotate") */
   unsigned int         screen_bmp_encoded;     /*!<  Kind of encoding for the saved screen bitmap */
   unsigned int         encoded_supported;      /*!<  Mask of supported encoding kind (1<<type_encoded) */
   unsigned int         ruf[5];                 /*!<  ruf */
}DISPLAY_SCREEN_INFO_FIOCTL;



/*! @brief Fioctl external display */
typedef struct
{
   unsigned int     command;		/*!< Command */
   unsigned int     config; 	  	/*!< Not use yet */
   unsigned int     ruf[2];			/*!< ruf */
}DISPLAY_COMMAND_FIOCTL;


#endif

/*! @}  */ 


