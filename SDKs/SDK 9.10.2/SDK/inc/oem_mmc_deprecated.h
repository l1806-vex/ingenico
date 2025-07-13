/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef __OEM_MMC_H
#define __OEM_MMC_H

#ifdef _DEPRECATED_OEM_MMC_SDK96_
/*
======================================================================
			Data Structures Definition
======================================================================
*/

// Definition de l'interface utilisee pour les echanges en mode block
// Les echanges se font par l'intermediaire de descripteurs qui transitent
// a travers les cannaux standard du driver.

/*! @brief Define the interface used for echanges in block mode. The exchanges get past by descriptors which pass trought the strandard channels of the driver. */
typedef enum {
	MMC_STATUS,						/*!< Status of the bus card		*/
	MMC_INFO,						/*!< Constructor characteristics of a card */		
	MMC_READ,						/*!< data reading */
	MMC_WRITE,						/*!< data writing */
	MMC_ERASE						/*!< data erasing	*/
} MMC_cmd_t;

/*! @brief Define the interface used for echanges in block mode. The exchanges get past by descriptors which pass trought the strandard channels of the driver. */
typedef struct {
	MMC_cmd_t		cmd;						/*!< Command. */
	unsigned short	req_num;					/*!< rank of the request. */
	int				card_num;					/*!< rank of the card. */
	union {
		struct {
			int				nb_card;			/*!< card count. */
		} arg_stat;
		struct {
			void *			pt_cid;				/*!< CID buffer address. */
			void *			pt_csd;				/*!< CSD buffer address. */
		} arg_info;
		struct {
			int				offset;				/*!< Address of the data in the card. */
			int				io_len;				/*!< transfer length. */
			unsigned char *	io_buff;			/*!< address of the application buffer.  */
		} arg_rdwr;
		struct {
			int				offset;				/*!< Adress of the data in the card. */
			int				io_len;				/*!< transfer length. */
		} arg_eras;
	} u_arg;
	int				status;						/*!< Status of the request.  */
} MMC_io_descr;


/*
======================================================================
					List of Defines
======================================================================
*/

#define	MMC_OK			 0		/*!< Command successful */
#define	MMC_CMDERR		-1		/*!< Command unsupported */
#define	MMC_ARGERR		-2		/*!< Argument incorrect */ 
#define	MMC_ACCERR		-3		/*!< Data access problem */

// fiotcl
#define MMC_FIOCTL_IOB	0x8000	/*!< @deprecated This fioctl has been parsed as unused. It will no longer be supported in future releases of the SDK. To use this fioctl, you can define _DEPRECATED_LEDSPERI_SDK96_ in your application. @brief For all I/O in block mode */

#endif
#endif

/*! @}  */ 

