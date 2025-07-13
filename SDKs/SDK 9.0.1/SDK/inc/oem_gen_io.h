/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

# ifndef __OEM_GEN_IO_H
# define __OEM_GEN_IO_H

/*
======================================================================
					List of Defines
======================================================================
*/

// define for all product
#define GEN_IO_FIOCTL_READ			0x8001			/*!< Generic command to read an IO port */
#define GEN_IO_FIOCTL_WRITE			0x8002			/*!< Generic command to write on an IO port */

// define for product MR40
#define GEN_IO_FIOCTL_READ_MR40		0x8100			/*!< Specific command to read IO port on the connector of the MR40 which is used for the additionnal card (modem/GPRS) */
#define GEN_IO_FIOCTL_WRITE_MR40	0x8101			/*!< Specific command to write IO port on the connector of the MR40 which is used for the additionnal card (modem/GPRS) */

#define _MR40_EXT_49	49		/*!< value used on MR40 to write IO port 49 of the connector with the specific command above */
#define _MR40_EXT_50	50		/*!< value used on MR40 to write IO port 50 of the connector with the specific command above */
#define _MR40_EXT_51	51		/*!< value used on MR40 to write IO port 51 of the connector with the specific command above */
#define _MR40_EXT_52	52		/*!< value used on MR40 to read IO port 52 of the connector with the specific command above */
#define _MR40_EXT_53	53		/*!< value used on MR40 to read IO port 53 of the connector with the specific command above */
#define _MR40_EXT_54	54		/*!< value used on MR40 to write IO port 54 of the connector with the specific command above */
#define _MR40_EXT_55	55		/*!< value used on MR40 to read IO port 55 of the connector with the specific command above */
#define _MR40_EXT_56	56		/*!< value used on MR40 to read IO port 56 of the connector with the specific command above */

// for all product
#define IO_FIOCTL_SUCCESS					(0)			/*!< Return value if fioctl command is successful */
#define IO_FIOCTL_IOCTL_NOT_IMPLEMENTED		(-1)		/*!< Return value if fioctl command is unknown */
#define IO_FIOCTL_PARAM_NOT_IMPLEMENTED		(-2)		/*!< Return value if fioctl command is sent with a parameter not allowed */
#define IO_FIOCTL_KO						(-3)		/*!< Return value if fioctl command is sent with a bad IO name */
#define IO_FIOCTL_NO_PARAM					(-4)		/*!< Return value if fioctl command is sent without parameters */


/*! @brief structure to access IO port */
typedef struct
{
	unsigned int io_id;			/*!< IO Id to access */
	unsigned int io_value;		/*!< value to write to the IO or value read from the IO */
} st_io_access;

#endif

/*! @}  */ 

