/*! @addtogroup KSFAM_DIAG
	* @{
 */ 


#define EXIT_ALREADY_OPEN 				1		/*!< When calling fopen : file is already opened */
#define EXIT_INVALID_MODE_OPEN		2		/*!< When calling fopen : trying to open a read only device in write mode or a write only device in read mode */
#define EXIT_INVALID_MOD 					3		/*!< When calling fopen : invalid open mode or neither read or write mode specified */
#define EXIT_FOPEN_SEM 						4		/*!< When calling fopen : file is already opened and specified device has no semaphore */
#define EXIT_NOT_DESCRIPTOR 			5		/*!< FILE* is not valid (argument has not been returned by fopen) */
#define EXIT_NOT_PROPER_TASK 			6		/*!< File has not been opened by the current task */
#define EXIT_SCRIT 								7		/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_NAME_USED 						8		/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_CANT_READ 						10	/*!< File is not in read mode */
#define DATE_OUT_OF_RANGE 				11	/*!< Only for compatibility with existing projects. It has not to be used. */	
#define BUG_ACCES_CALEND 					12	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_BUG_CALEND 					13	/*!< Only for compatibility with existing projects. It has not to be used. */
#define DATE_NOT_FORMAT 					14	/*!< Only for compatibility with existing projects. It has not to be used. */
#define SPEED_PRINTER 						15	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_CANT_WRITE 					20	/*!< File is not in write mode */
#define EXIT_BUSY_KO 							30	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_PRINT 								40	/*!< When fprintf : can't print on this file */
#define EXIT_SYSTEM_ERROR 				0x10		/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_ABORT_TELECHARGEMENT 0x100		/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_CHARG_APPLI 					50			/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_TELE_APPLI  					51			/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_DIAG_APPLI  					52			/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_NUM_TELE  						53			/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_MODEM_EN_COURS  			54			/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_MODEM_PAS_RACCROCHE  55			/*!< When calling MODEM fclose function : modem is connected */
#define EXIT_NOT_PROPER_TASK_MODEM  56		/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_IO_NOT_OPEN  					57		/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_BAD_TASK_NUMBER 				0x81	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_BAD_SEM_NUMBER 				0x82	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_BAD_MAILBOX_NUMBER 		0x83	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_BAD_DELAI_NUMBER 			0x84	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_BAD_PRIORITY 					0x85	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_BAD_CLOCK_PRIORITY 		0x86	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_DATA_SEG_OVERFLOW 			0x87	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_NEG_MAX_VALUE 					0x89	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_NEG_CAPACITY 					0x8A	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_BAD_CURR_TASK 					0x8B	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_DELAI_ALREADY_USE 			0x8C	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_TASK_NOT_INIT 					0x8D	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_TASK_ALREADY_STARTED 	0x8E	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_TASK_NOT_OPERATION 		0x8F	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_NESTING_OVERFLOW 			0x90	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_NESTING_UNDERFLOW 			0x91	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_WAIT_BACKGROUND 				0x93	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_MES_OVERFLOW 					0x94	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_NB_OBJECT_OVERFLOW 		0x96	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_INVALID_OPCODE 				0x97	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_INSUFFICIENT_PRIVILEGE 0x98	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_TERMINATE_BACKGROUND 	0x99	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_PB_MALLOC 							0x9A	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_TIME_OUT_PRINTER 			0x9B	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_PRINTER_MODF 					0x9B	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_NOT_IMPLEMENTED 				0x9C	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_TELICAPT 							0x9D	/*!< Telicapt driver has returned an error */
#define EXIT_STACK_CHK_FAIL               0x9E		    /*!< Stack overflow */

/* Anomalies carte extension */
#define EXIT_NO_EXTENSION_CARD 			0xA0	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_PB_DP_RAM 							0xA1	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_PB_EXTENSION_RAM 			0xA2	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_PB_CARD_LOADING 				0xA3	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_PB_COM_EXTENSION_CARD 	0xA4	/*!< Only for compatibility with existing projects. It has not to be used. */

/*CAM*/
#define EXIT_PB_VCC 								0xB0	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_PB_T0 									0xB1	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_PB_CAM_I2C 						0xB2	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_PB_CAM_RECEPT_INTER_UC 0xC0	/*!< Booster<-->Thunder link error : CAM acces timeout waiting for answer */
#define EXIT_PB_CAM_SYNCHRO         0xC1	/*!< TO_BE_DOCUMENTED */
#define EXIT_PB_CAM_SEND_INTER_UC   0xC2	/*!< Booster<-->Thunder link error : CAM acces failure trying to send command */
#define EXIT_CAM_OPEN_FORBIDDEN     0xC3	/*!< Error trying to open a CAM not driven by Booster */

 /* PPS */
#define EXIT_NO_PRINTER 						0xA8	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_NO_SWIPE2 							0xA9	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_NO_MODEM 							0xAA	/*!< Only for compatibility with existing projects. It has not to be used. */

#define EXIT_LEVEL_KO 							0x111	/*!< Only for compatibility with existing projects. It has not to be used. */

/* concentre */
#define EXIT_CHANGEMENT_CONCENTRATEUR 0x123	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_CHANGEMENT_CONCENTRE 		0x124	/*!< Only for compatibility with existing projects. It has not to be used. */

/* lrs */
#define EXIT_FORK_RESERVED 						0x12C	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_LINKED_TO_PERIPHERAL 		0x12D	/*!< When callink kill : the specified task has one or more OEMC files opened */
#define EXIT_UNKNOWN_TASK_NUMBER 			0x12E	/*!< When callink kill : the specified task is unknown */
#define EXIT_MAX_TASK_NUMBER 					0x12F	/*!< Too many task has been forked */

/* ajout : tp97 */
#define EXIT_TOO_MANY_VEC_EXEC 				0x130	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_ILLEGAL_MSQ_EXEC  				0x131	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_UNKNOWN_FILE      				0x132	/*!< When calling fopen : file is unknown */
#define EXIT_ABSENT_FILE       				0x133	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_TOO_MANY_FILE     				0x134	/*!< There is too many OEMC files */
#define EXIT_INVALID_FILE_PROC 				0x135	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_TOO_MANY_HTR_EXEC   		 	0x136	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_ILLEGAL_MSQ_HTR_EXEC		 	0x137	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_BAD_WRITABLE_BYTE 				0x138	/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_ILLEGAL_PERIPH 					0x139	/*!< Not called by owner task. */

/* ajout : modem V32bis */
#define EXIT_MODEM_PLANTE 								0x140		/*!< Only for compatibility with existing projects. It has not to be used. */

#define EXIT_TOO_SLOW 										0x141		/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_MODEM_NETBRICKS_ALREADY_OPEN 0x142		/*!< Trying to open V34 modem when standard modem is already opened */
#define EXIT_MODEM_V34_ALREADY_OPEN       0x143		/*!< Trying to open standard modem when V34 modem is already opened */

/* ajout : ksu */
#define EXIT_PB_KSU 										0x13F			/*!< Link to Booster is broken */
#define EXIT_EFFRACTION_KSU 						0x13E			/*!< Only for compatibility with existing projects. It has not to be used. */


/* ajout : PCE311 */
#define EXIT_BAD_FORMAT         				0x150			/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_TOO_MANY_ITDUART_EXEC  		0x151			/*!< Only for compatibility with existing projects. It has not to be used. */
#define ILLEGAL_UNLINK_ITDUART      		0x152			/*!< Only for compatibility with existing projects. It has not to be used. */
#define BAD_ITDUART_EXEC       					0x153			/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_TOO_MANY_LINK_ITDUARTS     0x154			/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_ILLEGAL_UNLINK_ITDUARTS    0x155			/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_ILLEGAL_LINK_ITDUARTS      0x156			/*!< Only for compatibility with existing projects. It has not to be used. */

#define EXIT_PB_ACTIVATE                0x160			/*!< Only for compatibility with existing projects. It has not to be used. */
#define EXIT_DIV0                       0x194			/*!< Only for compatibility with existing projects. It has not to be used. */

#define EXIT_VFS_NOT_IMPLEMENTED        0x200   /*!< Reset in VFS driver. This function is not implemented. */
#define EXIT_VFS_RESERVED_1             0x201	/*!< VFS driver : error number 1 */
#define EXIT_VFS_RESERVED_2             0x202	/*!< VFS driver : error number 2 */
#define EXIT_VFS_RESERVED_3             0x203	/*!< VFS driver : error number 3 */
#define EXIT_VFS_RESERVED_4             0x204	/*!< VFS driver : error number 4 */
#define EXIT_VFS_RESERVED_5             0x205	/*!< VFS driver : error number 5 */
#define EXIT_VFS_RESERVED_6             0x206	/*!< VFS driver : error number 6 */
#define EXIT_VFS_RESERVED_7             0x207	/*!< VFS driver : error number 7 */
#define EXIT_VFS_RESERVED_8             0x208	/*!< VFS driver : error number 8 */
#define EXIT_VFS_RESERVED_9             0x209	/*!< VFS driver : error number 9 */
#define EXIT_VFS_RESERVED_10            0x20A	/*!< VFS driver : error number 10 */

/* ajout hf */
#define CPT_CRC_TRM_HF   0x300			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_CRC_TRM_C4   0x301			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_LG_TRM_HF    0x302			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_LG_TRM_C4    0x303			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_REPRISE_HF   0x304			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_REPRISE_C4   0x305			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_ETAB_HF      0x306			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_ETAB_C4      0x307			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_LIB_HF       0x308			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_LIB_C4       0x309			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_TRM_BIS_HF   0x30A			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_TRM_BIS_C4   0x30B			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_SMP_INVALID  0x30C			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_GLITCH       0x30D			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_TRM_INCOMP   0x30E			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_BITIGNORE    0x30F			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_PB_RSSI      0x310			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_BETABLI_OK   0x311			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_BETABLI_KO   0x312			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_ETABLI_OK    0x313			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_PBDIAGSOC    0x314			/*!< Only for compatibility with existing projects. It has not to be used. */
#define CPT_PBDIAGTER    0x315			/*!< Only for compatibility with existing projects. It has not to be used. */


/* ajout eft30 */

#define	BAD_HISR_PRIORITY					0x400		/*!< Only for compatibility with existing projects. It has not to be used. */
#define	T_BAD_SWI_MODE						0x401		/*!< SWI called in not correct mode */
#define	T_BAD_SWI_NB_IN_USER_MODE 0x402 	/*!< SWI called in not correct mode */
#define	BAD_PIO_CONFIG						0x403		/*!< Bad PIO number */
#define	NOT_ENOUGH_SEM						0x404		/*!< Fail to create semaphore */

#define EXIT_TRAP_MODEM         					0x405		/*!< Modem internal error */
/* suite eft30 */
#define EXIT_DIV_ZERO           					0x406		/*!< Try to devide by zero */
#define EXIT_PB_LOAD_BOOSTER							0x407		/*!< Fail to load file into booster */
#define EXIT_PB_OPEN_SYSTEM_BOOSTER				0x408		/*!< Error reading booster file in Thunder file system */
#define EXIT_PB_ALLOC_SYSTEM_BOOSTER			0x409		/*!< Fail to alloc memory for booster system */
#define EXIT_SYSTEM_BOOSTER_TOO_BIG				0x40A		/*!< Booster Operating System is too big */
#define EXIT_PB_DRV_SYNC_NOT_FOUND				0x40B		/*!< Synchronous card driver not found */		
#define EXIT_PB_OPEN_DRV_SYNC							0x40C		/*!< Synchronous card driver open error */
#define EXIT_PB_DRV_SYNC_ALLOC_BOOSTER		0x40D		/*!< Synchronous card driver memory allocation error */
#define EXIT_PRINTER_FAILURE          		0x40E		/*!< Printer Driver internal error */
#define EXIT_TRAP_RESET          					0x40F		/*!< Telium System internal error */
#define EXIT_MMU_ABORT          					0x410		/*!< Telium System memory violation */
#define EXIT_YELLOW_DOT          					0x411		/*!< Key "yellow" + key "." has been pressed for reset */
#define EXIT_ECC_ERROR	         					0x412		/*!< ECC error found in nand flash */
#define EXIT_INTER_UC_USB	         				0x413		/*!< USB pinpad communication error */
#define EXIT_BOOSTER_RESET         				0x414		/*!< Booster has restarted ==> Thunder restart too */
#define EXIT_GARBAGE             	  			0x415		/*!< Garbage collection (this is not a reset) */
#define EXIT_PRINTER_LOCKED        				0x416		/*!< Printer internal error : semaphore dead lock */
#define EXIT_BAD_SWI_NUMBER        				0x417		/*!< Unknown SWI nuumber has been used */
#define EXIT_CODE_VIOLATION       				0x418		/*!< Application of driver code has been corrupted */
#define EXIT_BOOSTER_AUTO_CONTROLE_KO           0x419		/*!< Only for compatibility with existing projects. It has not to be used. */


#define EXIT_BLUETOOTH_BASE_NO_REQ_FOR_TOO_LONG (0x0420)		/*!< Bluetooth message form base timeout */
#define EXIT_BLUETOOTH_BASE_RESTART_REQUESTED   (0x0421)		/*!< Bluetooth base restart request */
#define EXIT_BLUETOOTH_BASE_SOFTWARE_ACTIVATE   (0x0422)		/*!< Bluetooth base software activate */
#define EXIT_BLUETOOTH_SCHED_MEMORY_POOL        (0x0423)		/*!< Bluetooth : fail to create memory pool */
#define EXIT_BLUETOOTH_SCHED_ALLOCATE_MEMORY    (0x0424)		/*!< Bluetooth : fail to allocate memory */
#define EXIT_BLUETOOTH_SCHED_QUEUE              (0x0425)		/*!< Bluetooth : fail to create queue */
#define EXIT_BLUETOOTH_APPLICATION_QUEUE        (0x0426)		/*!< Bluetooth : bad queue */
#define EXIT_BLUETOOTH_RESERVED_7               (0x0427)		/*!< Bluetooth : error number 7 */
#define EXIT_BLUETOOTH_RESERVED_8               (0x0428)		/*!< Bluetooth : error number 8 */
#define EXIT_BLUETOOTH_RESERVED_9               (0x0429)		/*!< Bluetooth : error number 9 */
#define EXIT_BLUETOOTH_RESERVED_A               (0x042A)		/*!< Bluetooth : error number A */
#define EXIT_BLUETOOTH_RESERVED_B               (0x042B)		/*!< Bluetooth : error number B */
#define EXIT_BLUETOOTH_RESERVED_C               (0x042C)		/*!< Bluetooth : error number C */
#define EXIT_BLUETOOTH_RESERVED_D               (0x042D)		/*!< Bluetooth : error number D */
#define EXIT_BLUETOOTH_RESERVED_E               (0x042E)		/*!< Bluetooth : error number E */
#define EXIT_BLUETOOTH_RESERVED_F               (0x042F)		/*!< Bluetooth : error number F */
#define EXIT_BLUETOOTH_SPP_CHANNEL_LOCKED       (0x0430)		/*!< Transparent SPP channel blocked. Authorization file not present */

#define EXIT_CALLHOST_TMO1				        (0x0440)		/*!< Callhost time out 1*/
#define EXIT_CALLHOST_TMO2				        (0x0441)		/*!< Callhost time out 2*/

#define EXIT_TERM_INIT	         		0x500			/*!< End of activation process */


/* LIFE counters */
// Value 0 is reserved for free counter
#define LIFE_RESET_THUNDER					0x0001		/*!< Accumulated number of Main processor (Thunder) Operating System start */
#define LIFE_SPURIOUS_INTERRUPT			0x0002		/*!< Accumulated number of spurious interrupts (internal use) */
#define LIFE_GARBAGE								0x0003		/*!< Accumulated number of nand flash garbage collection (physically erasing nand flash) */
#define LIFE_BAD_BLOCK							0x0004		/*!< Accumulated number of nand bad block found (some nand flash blocks may be bads without problem) */
#define LIFE_BAD_PRINTER_SENSOR			0x0005		/*!< Accumulated number of printer optical sensor errors */
#define LIFE_PRINTER_STEP_NUMBER		0x0006		/*!< Accumulated number of printer motor steps */
#define LIFE_PRINTING_TIME					0x0007		/*!< Accumulated printing time */
#define LIFE_PRINTER_DOTS_NUMBER		0x0008		/*!< Accumulated number of dots printed */
#define LIFE_POWER_SHUTDOWN					0x0009		/*!< Accumulated number of power shutdown */
#define LIFE_SWIPE_1_NUMBER					0x000A		/*!< Accumulated number of ISO1 magnetic cards swiped */
#define LIFE_SWIPE_2_NUMBER					0x000B		/*!< Accumulated number of ISO2 magnetic cards swiped */
#define LIFE_SWIPE_3_NUMBER					0x000C		/*!< Accumulated number of ISO3 magnetic cards swiped */
#define LIFE_VAL_KEY_PRESSED				0x000D		/*!< Accumulated number of green key pressed */
#define LIFE_0_KEY_PRESSED					0x000E		/*!< Accumulated number of '0' key pressed */
#define LIFE_F1_KEY_PRESSED					0x000F		/*!< Accumulated number of F1 key pressed */
#define LIFE_F2_KEY_PRESSED					0x0010		/*!< Accumulated number of F2 key pressed */
#define LIFE_CAM_1_NUMBER						0x0011		/*!< Accumulated number of smart card inserted is slot 1 */
#define LIFE_CAM_2_NUMBER						0x0012		/*!< Accumulated number of smart card inserted is slot 2 */
#define LIFE_PUT_ON_BASE						0x0013		/*!< Accumulated number of craddle landing (only for mobile terminals) */
#define LIFE_TIME_RUNNING						0x0014		/*!< Accumulated running time in seconds */
#define LIFE_MODEM_ACCESS						0x0015		/*!< Accumulated number of modem connection (successeful+failed) */
#define LIFE_GPRS_ACCESS						0x0016		/*!< Accumulated number of GPRS netwok connection */
#define LIFE_FLASH_BLOCK_REFRESH		0x0017		/*!< Accumulated number of nand flash bock refresh (1bit ECC error had been found in NAND flash. Data had been corrected) */
#define LIFE_RESET_NRST_PIN       	0x0018		/*!< Accumulated number of thunder reset by NRST pin (internal use, value read at startup in thunder reset controler) - Telium 2 only */
#define LIFE_RESET_SOFT           	0x0019		/*!< Accumulated number of Soft reset:Processor reset required by the software (internal use, value read at startup in thunder reset controler) - Telium 2 only */
#define LIFE_FILTERED_FIQ         	0x001A		/*!< Accumulated number of filtred power failure FIQ low for a too short time, and ignored */
#define LIFE_SLEEP_NUMBER				0x001B		/*!< Accumulated number of switch to sleep mode (only for mobile terminals) */
#define LIFE_TOUCHSCR_UPDOWN  	   0x001C      /*!< Accumulated number of "clicks" on touchscreen */
#define LIFE_TOUCHSCR_DISTANCE	   0x001D      /*!< Accumulated distance of drawing on the touchscreen (abrasive wear of the pen) */
#define LIFE_SWIPE_2_IS_ISO2_OK					0x001E		/*!< Accumulated number of is_iso2() request with correct decoding result (including LUHN errors)  */
#define LIFE_BACKLIGHT_ON_TIME					0x001F		/*!<  Accumulated main backlight time (seconds) */
 



/*! @}  */ 


