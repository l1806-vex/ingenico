/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef OEM_UMS_H
#define OEM_UMS_H

/*
======================================================================
					List of Defines
======================================================================
*/

#define UMS_FIOCTL_IOB       0x8000        /*!< param UMS_iob_t */
#define UMS_FIOCTL_IOB2      0x8002        /*!< param UMS_iob2_t */

#define UMS_BLKSIZE  				 512					 /*!< USB mass storage block size */



/*
======================================================================
			Data Structures Definition
======================================================================
*/

// Definition de l'interface utilisee pour les echanges en mode block
// Les echanges se font par l'intermediaire de descripteurs qui transitent
// a travers les cannaux standard du driver.

typedef enum {
	UMS_STATUS,		/*!< Status maps of bus */
	UMS_INFO,		/*!< Characteristics of a map */
	UMS_READ,		/*!< Reading data */
	UMS_WRITE,		/*!< Writing data */
	UMS_ERASE		/*!< Erasing data */
} UMS_cmd_t;

typedef struct {
	UMS_cmd_t			cmd;			/*!< Command */
	unsigned short			req_num;		/*!< request identification number */
	union {
		struct {
			int	  	ready;			/*!< status : not null if ready */
		} arg_stat;
		struct {
			unsigned  int 	nb_blk;			/*!< number of blocks */
			unsigned  int 	blk_size;		/*!< block size */
		} arg_info;
		struct {
			int		offset;			/*!< data address (bytes) must be n*blk_size */
			int		io_len;			/*!< data length (bytes). Must be n*blk_size */
			unsigned char *	io_buff;		/*!< Application buffer address */
		} arg_rdwr;
		struct {
			int		offset;			/*!< data address (bytes) must be n*blk_size */
			int		io_len;			/*!< data length (bytes). Must be n*blk_size */
		} arg_eras;
	} u_arg;
	int				status;			/*!< Status of the application */
} UMS_iob_t;

typedef struct { 
	UMS_cmd_t		    	cmd;	  		/*!< Commande */
	unsigned short			phy_unit;    	 	/*!< Physical ID */
	unsigned short			logical_unit;   	/*!< Logical Unit ID */
	int				status;			/*!< Status of the application  */
	union {
		struct {
			int		ready;			/*!< status : not null if ready */
		} arg_stat;
		struct {
			unsigned  int 	nb_blk;			/*!< number of blocks */
			unsigned  int 	blk_size;		/*!< block size */
		} arg_info;
		struct {
			int		offset;			/*!< data address (bytes) must be n*blk_size 
								     For FAT32 : block number with Bit31 set to 1 */
			int		io_len;			/*!< data length (bytes). Must be n*blk_size */
			unsigned char *	io_buff;		/*!< Tpplication buffer address*/
		} arg_rdwr; 
		struct {
			int		offset;			/*!< Tdata address (bytes) must be n*blk_size */
			int		io_len;			/*!< length of the transfer of multiple blk_size */
		} arg_eras;
	} u_arg;
} UMS_iob2_t;

#define	UMS_OK			 0  					/*!< success */
#define	UMS_CMDERR		-1					/*!< Command unsupported */
#define	UMS_ARGERR		-2					/*!< Argument incorrect */
#define	UMS_ACCERR		-3					/*!< Data access problem */

#define	UMS_HCFLAG		0x80000000		/*!< Flag for FS type FAT32 > 2GB */
#define	UMS_HCMASK		~UMS_HCFLAG		

#endif

/*! @}  */ 

