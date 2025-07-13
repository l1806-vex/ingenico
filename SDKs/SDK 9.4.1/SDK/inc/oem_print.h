/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

# ifndef __OEM_PRINT_H
# define __OEM_PRINT_H

/*
======================================================================
					List of Defines
======================================================================
*/

#define    PARAM_MOTOR_DISABLE_ENABLE_OFF		0			/*!< INTERNAL USE ONLY :disable stepper motor, to be used with fioclt command code: PRINTER_MOTOR_DISABLE_ENABLE */
#define    PARAM_MOTOR_DISABLE_ENABLE_FORWARD	1			/*!< THIS IS THE DEFAULT: set motor in forward mode, to be used with fioclt command code: PRINTER_MOTOR_DISABLE_ENABLE */
#define    PARAM_MOTOR_DISABLE_ENABLE_BACKWARD 	(-1)		/*!< DON'T USE :set motor in backward mode, to be used with fioclt command code: PRINTER_MOTOR_DISABLE_ENABLE */

#define    PRINTER_TYPE_HARWARE_UNKNOWN			0				/*!< OS old releases only */
#define    PRINTER_TYPE_HARWARE_EFT30			1000			/*!< root for this terminal printer mechanism, see below */
#define    PRINTER_TYPE_HARWARE_EFT930			2000			/*!< root for this terminal printer mechanism, see below */
#define    PRINTER_TYPE_HARWARE_ICT2xx			3000			/*!< root for this terminal printer mechanism, see below */
#define    PRINTER_TYPE_HARWARE_IWL2xx			4000			/*!< root for this terminal printer mechanism, see below */
#define    PRINTER_TYPE_HARWARE_E530			5000			/*!< root for this terminal printer mechanism, see below */
#define    PRINTER_TYPE_HARWARE_RUF_MAX			6000			/*!< reserve for future root , Warning this value must be > all PRINTER_TYPE_HARWARE_xxx */
#define    PRINTER_TYPE_DEFAULT					(PRINTER_TYPE_HARWARE_UNKNOWN+0)	/*!< EFT30=SII, EFT930=APS, ICT220=ALPS */
#define    PRINTER_TYPE_SII_LTPA245				(PRINTER_TYPE_HARWARE_EFT30+0)		/*!< This terminal has this printer mechanism inside, return code of fioclt with PRINTER_GET_PRINTER_TYPE command code */
#define    PRINTER_TYPE_APS_SS205				(PRINTER_TYPE_HARWARE_EFT930+0)		/*!< This terminal has this printer mechanism inside, return code of fioclt with PRINTER_GET_PRINTER_TYPE command code */
#define    PRINTER_TYPE_SII_LTPJ245				(PRINTER_TYPE_HARWARE_EFT930+1)		/*!< This terminal has this printer mechanism inside, return code of fioclt with PRINTER_GET_PRINTER_TYPE command code */
#define    PRINTER_TYPE_ALPS_PTMBL1AXX			(PRINTER_TYPE_HARWARE_ICT2xx+0)		/*!< This terminal has this printer mechanism inside, return code of fioclt with PRINTER_GET_PRINTER_TYPE command code */
#define    PRINTER_TYPE_SII_LTPB245				(PRINTER_TYPE_HARWARE_ICT2xx+1)		/*!< This terminal has this printer mechanism inside, return code of fioclt with PRINTER_GET_PRINTER_TYPE command code */
#define    PRINTER_TYPE_ALPS_PTMBL1AXX_PCIV3	(PRINTER_TYPE_HARWARE_ICT2xx+2)		/*!< This terminal has this printer mechanism inside, return code of fioclt with PRINTER_GET_PRINTER_TYPE command code */
#define    PRINTER_TYPE_SII_LTPB245_PCIV3		(PRINTER_TYPE_HARWARE_ICT2xx+3)		/*!< This terminal has this printer mechanism inside, return code of fioclt with PRINTER_GET_PRINTER_TYPE command code */
#define    PRINTER_TYPE_ALPS_IWL2xx				(PRINTER_TYPE_HARWARE_IWL2xx+0)		/*!< This terminal has this printer mechanism inside, return code of fioclt with PRINTER_GET_PRINTER_TYPE command code */
#define    PRINTER_TYPE_APS_CM215_IWL2xx		(PRINTER_TYPE_HARWARE_IWL2xx+1)		/*!< This terminal has this printer mechanism inside, return code of fioclt with PRINTER_GET_PRINTER_TYPE command code */
#define    PRINTER_TYPE_APS_SS205_E530 			(PRINTER_TYPE_HARWARE_E530+0)		/*!< This terminal has this printer mechanism inside, return code of fioclt with PRINTER_GET_PRINTER_TYPE command code */

//fioclt command codes
#define    PRINTER_INTENSITY      				0x8000		/*!< Modify printer contrast */
#define    PRINTER_COIL_CURRENT_ADJUST     		0x8001		/*!< DON'T USE :for test only / modify stepper motor current */
#define    PRINTER_GET_HEAD_ENERGY_TANK    		0x8002		/*!< DON'T USE :for test only / get updated virtual energy container level */
#define    PRINTER_GET_HEAD_ENERGY_TRESHOLD    	0x8003		/*!< DON'T USE :for test only / get virtual energy container treshold */ 
#define    PRINTER_GET_HEAD_ENERGY_MAXTANK    	0x8004		/*!< DON'T USE :for test only / get virtual energy container max value */
#define    PRINTER_GET_HEAD_ENERGY_TIME_ELAPSED	0x8005		/*!< DON'T USE :for test only / get printer elapsed time */
#define    PRINTER_MOTOR_DISABLE_ENABLE			0x8006		/*!< DON'T USE :used internally by battery discharging process */
#define    PRINTER_GET_RELEASE_NUMBER      		0x8007		/*!< read printer driver release number : (DRIVER_PRINTER<<24) + (VERSION_MAJOR<<16) + (VERSION_MINOR<<8) + (VERSION_PATCH) */
#define    PRINTER_PRINT_ULIGNE      			0x8008		/*!< print X*uligne,if success {returns(1+ <'queue available slots'>)} else {returns(0)}  */
#define    PRINTER_IP_SET_ADDR	                0x8009		/*!< configure address for PRINTER_IP */
#define    PRINTER_IP_SET_PORT	                0x8010		/*!< configure port for PRINTER_IP */
#define    PRINTER_GET_DOTS_ENERGY_TOTAL      	0x8011		/*!< read cumulated energy tranfered to dots (unit=uJ) */
#define    PRINTER_GET_PRINTER_TYPE    			0x8012		/*!< read printer type (this can be used if terminal can received differents printers )  */
#define    PRINTER_SET_PRINTER_SPEED   			0x8013		/*!< DON'T USE :for test only / modify printer step max duration (reduce only) */
#define    PRINTER_GET_PRINTER_SPEED   			0x8014		/*!< DON'T USE :for test only / modify printer step max duration (reduce only) */
#define    PRINTER_COIL_CURRENT_READ   			0x8015		/*!< DON'T USE :for test only / read coil current PWN cyclic ratio */
#define    PRINTER_REFRESH_MAX_DOT   			0x8016		/*!< DON'T USE :for test only / force next printing starting at max dot, give back this value */
#define    PRINTER_GOT_MAX_CONCURRENT_MAX_DOT   0x8017		/*!< DON'T USE :for test only / printer reaches max concurrent max dot, reset this information when called */
#define    PRINTER_SET_POLYSWITCH_MANAGEMENT	0x8018		/*!< DON'T USE :for test only / set/clear polyswitch management */
#define    PRINTER_FIOCTL_DEFPRINTERPATTERN		0x8019	    /*!< Command to link a pattern to a char * @note EXT_PRINTER only @param st_ext_printer_defpattern * : Printer Pattern definition */
#define    PRINTER_FIOCTL_SET_COM				0x8020	    /*!< Command to set the COM port used for the external printer @note EXT_PRINTER only. @param st_ext_printer_defpattern * */
#define    PRINTER_FIOCTL_SET_BT_ADDRESS		0x8021	    /*!< Command to set the Bluetooth address of the external printer @note EXT_PRINTER only @param st_ext_printer_bt_device_addr * : Printer Bluetooth Address  */
#define    PRINTER_INTENSITY_L2      			0x8022		/*!< Modify printer contrast: saturates at PRINTER.CFG/PRINTER_INTENSITY_L2_MAX if exist  */
#define    PRINTER_GET_INTENSITY	      		0x8023		/*!< Get printer contrast value */
#define    PRINTER_GET_INTENSITY_L2	      		0x8024		/*!< Get printer contrast_l2 value */
#define    PRINTER_IS_KEEPALIVE_SUPPORTED		0x8025	/*!< Is keep alive supported (ext printer, bluetooth only) */
#define    PRINTER_SET_KEEPALIVE				0x8026	/*!< Set keep alive state @param unsigned int *  \ref PRINTER_KEEPALIVE_ENABLE or \ref PRINTER_KEEPALIVE_DISABLE @note external printer, bluetooth only */
#define    PRINTER_GET_KEEPALIVE				0x8027	/*!< Get keep alive @param unsigned int *  \ref PRINTER_KEEPALIVE_ENABLE or \ref PRINTER_KEEPALIVE_DISABLE @note external printer, bluetooth only */


#define    PRINTER_INTENSITY_NORMAL		      0 			/*!< (70%) to be used with PRINTER_INTENSITY fioctl command (this is the default)*/
#define    PRINTER_INTENSITY_HIGH		  	  1 			/*!< (85%) to be used with PRINTER_INTENSITY fioctl command */
#define    PRINTER_INTENSITY_EXTRAHIGH		  2				/*!< (100%) to be used with PRINTER_INTENSITY fioctl command */
#define    PRINTER_INTENSITY_ADJUST(e)  	  (2+e)			/*!< (100%+(e*3)%) to be used with PRINTER_INTENSITY fioctl command (be carefull:very dark printing)*/
#define    PRINTER_INTENSITY_MAX_VALUE	      36 			/*!< max allowed value= higher request will be upper-limited to this value*/

#define		PRINTER_KEEPALIVE_ENABLE			1			/*!< keep alive enabled */
#define		PRINTER_KEEPALIVE_DISABLE			0			/*!< keep alive disabled */



/*! @brief structure to define a printer pattern (EXT_PRINTER only) @ref PRINTER_FIOCTL_DEFPRINTERPATTERN */
typedef struct
{
	unsigned char key;			/*!< Key to redefine */
	unsigned char *pattern;		/*!< pattern of the bitmap */
} st_ext_printer_defpattern;

/*! @brief  Define the address of the bluetooth device. (total size 2 * 4) (EXT_PRINTER only)  @ref PRINTER_FIOCTL_SET_BT_ADDRESS*/
typedef struct
{
	unsigned int nap:16,		/*!< Non significant Address Part 32..47 */
				 uap:8;			/*!< Upper Address Part 24..31 */
	unsigned int lap;			/*!< Lower Address part 00..23 */
} st_ext_printer_bt_device_addr;



/*! @brief This structure is used by PRINTER_PRINT_ULIGNE fioctl() */
typedef struct {
 unsigned int 	count; 			/*!< print count time given *ptr uligne */
 unsigned char 	*bitmap;		/*!< uligne to print ,dots are printed from left to right in big endian model ( msbit first and msbyte first ) */
 unsigned int  	lng;			/*!< uligne byte size */
 int 			      suspend;	/*!< if set,wait until completion  */
}t_uligne;

#define    	PRINTER_COIL_CURRENT_ADJUST_MAX_VALUE   99	/*!< border for PRINTER_COIL_CURRENT_ADJUST */
#define    	PRINTER_COIL_CURRENT_ADJUST_MIN_VALUE   51	/*!< border for PRINTER_COIL_CURRENT_ADJUST */

#define PRINTER_MOTOR_DISABLE_ENABLE_SUPPORTED(e) ((e<<8)>=0x2000000)		/*!< To see if OS supports PRINTER_MOTOR_DISABLE_ENABLE command: apply this filter on return code of fioclt with PRINTER_GET_RELEASE_NUMBER command code  */

#define PRINTER_BIT_WITDH 384						/*!< dots number */
#define PRINTER_BYTE_WITDH (PRINTER_BIT_WITDH/8)	/*!< dots number */

// fioctl return
#define PRINTER_SUCCESS           			(0)		/*!< Return value if fioctl command is successful */
#define PRINTER_ERR_NOT_IMPLEMENTED   		(-1)	/*!< Return value if fioctl command is unknown */
#define PRINTER_ERR_NO_PARAM			 	(-2)	/*!< Return value if fioctl command is sent without parameters */
#define PRINTER_ERR_NOT_AVAILABLE	 		(-3)	/*!< Return value if fioctl command is not available with the printer used */
#define PRINTER_ERR_ALREADY_DEFINED_IN_FILE	(-4)	/*!< Return value if fioctl command has no effect due to a parameter already defined in EXTPRN.CFG file @note EXT_PRINTER only*/
#define PRINTER_ERR_NOT_SUPPORTED	 		(-5)	/*!< Return value if fioctl command or parameter is not available */
#define PRINTER_ERR_BAD_PARAM		 		(-6)	/*!< Return value if one or severals parameters provided are wrong @note EXT_PRINTER only*/
#define PRINTER_ERR_OVERRUN			 		(-7)	/*!< Return value if one or severals parameters provided are wrong @note EXT_PRINTER only*/
#endif

/*! @}  */ 
