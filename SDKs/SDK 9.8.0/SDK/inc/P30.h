/*! @addtogroup KSFAM_PPS_MANAGER
	* @{
**/

#ifndef __P30_H_
#define __P30_H_


/*
======================================================================
					List of Defines
======================================================================
*/

#define ERR_P30_OK												(0)				/*!< No P30 error.*/
#define ERR_P30_KO												(1)				/*!< P30 unknown error.*/
#define ERR_P30_DISCONNECT								(-1)			/*!< The P30 device is not connected.*/
#define ERR_P30_COMPONENT_NOT_FOUND				(-2)			/*!< The P30 software component is not found.*/
#define ERR_P30_NOT_CONFIGURED						(-3)			/*!< The P30 is not configured in the manager.*/

#define P30_PRODUCT_ID_LENGTH							(8)				/*!< Length of a P30 product identifier.*/
#define P30_SERIAL_NUMBER_LENGTH					(8)				/*!< Length of a P30 serial number.*/
#define P30_PRODUCT_CODE_LENGTH						(3)				/*!< Length of a P30 product code.*/
#define P30_CONSTRUCTOR_CODE_LENGTH				(8)				/*!< Length of a P30 constructor code.*/
#define P30_MANUFACTURING_DATE_LENGTH			(8)				/*!< Length of a P30 manufacturing date.*/
#define P30_BOOSTER_VERSION_LENGTH				(4)				/*!< Length of a P30 booster version.*/

#define P30_HARDWARE_OPTION_BUZZER			(0x00000001)	/*!< The P30 has a buzzer.*/
#define P30_HARDWARE_OPTION_USB_SLAVE		(0x00000002)	/*!< The P30 has a slave USB port.*/
#define P30_HARDWARE_OPTION_COM0				(0x00000010)	/*!< The P30 has a COM0 port.*/
#define P30_HARDWARE_OPTION_COM1				(0x00000020)	/*!< The P30 has a COM1 port.*/

#define P30_HARDWARE_OPTION_CAM_1				(0x00000100)	/*!< The P30 has a SAM1 connector.*/
#define P30_HARDWARE_OPTION_CAM_2				(0x00000200)	/*!< The P30 has a SAM2 connector.*/

#define P30_HARDWARE_OPTION_SAM_1				(0x00000400)	/*!< The P30 has a SAM1 connector.*/
#define P30_HARDWARE_OPTION_SAM_2				(0x00000800)	/*!< The P30 has a SAM2 connector.*/
#define P30_HARDWARE_OPTION_SAM_3				(0x00001000)	/*!< The P30 has a SAM3 connector.*/
#define P30_HARDWARE_OPTION_SAM_4				(0x00002000)	/*!< The P30 has a SAM4 connector.*/

#define P30_HARDWARE_OPTION_ISO_1				(0x00004000)	/*!< The P30 has a SAM1 connector.*/
#define P30_HARDWARE_OPTION_ISO_2				(0x00008000)	/*!< The P30 has a SAM2 connector.*/
#define P30_HARDWARE_OPTION_ISO_3				(0x00010000)	/*!< The P30 has a SAM3 connector.*/

#define P30_HARDWARE_OPTION_DISPLAY_NONE		(0x00020000)	/*!< The P30 has no display.*/
#define P30_HARDWARE_OPTION_DISPLAY_128_64	(0x00040000)	/*!< The P30 has a 128x64 graphic display.*/
#define P30_HARDWARE_OPTION_DISPLAY_2_16		(0x00080000)	/*!< The P30 has a 2x16 alphanumerical display.*/

#define P30_HARDWARE_OPTION_CLESS						(0x00100000)	/*!< The P30 is CLESS.*/

#define P30_HARDWARE_OPTION_INTER_UC_ON_COM0		(0x80000000)	/*!< The inter-uc communication is mapped on COM0 (valid only when both COM0 and USB are available).*/
#define P30_HARDWARE_OPTION_COM0_COM1_SEPARATED	(0x40000000)	/*!< The COM0 an COM1 are separated.*/

/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Define a structure describing the P30 hardware capabilities.*/
typedef struct
{
	char szProductIdentification[P30_PRODUCT_ID_LENGTH + 1];			/*!< Product identification of the P30 device.*/
	char szSerialNumber[P30_SERIAL_NUMBER_LENGTH + 1];						/*!< Serial number of the P30 device.*/
	char szProductCode[P30_PRODUCT_CODE_LENGTH + 1];							//!< Product code of the P30 device.*/
	char szConstructorCode[P30_CONSTRUCTOR_CODE_LENGTH + 1];			/*!< Constructor code of the P30 device.*/
	char szManufacturingDate[P30_MANUFACTURING_DATE_LENGTH + 1];	/*!< Manufacturing date of the P30 device.*/
	char szBoosterVersion[P30_BOOSTER_VERSION_LENGTH + 1];				/*!< Booster version of the P30 device.*/
	unsigned int Options;																					/*!< Hardware options of the P30 device. See P30_HARDWARE_OPTION_xxx.*/
} T_P30_HARDWARE_CAPABILITIES;

/*
======================================================================
			Functions Definition
======================================================================
*/


/*! @brief Get pinpad hardware description
 * @param pHardCapabilities : the pinpad description structure.
 * @return ERR_PP_OK (0) if successful.
 * @par exit None
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:P30_GetHardwareCapabilities:KSFAM_PPS_MANAGER:0x52
//  @GSIM_A:1:ONE_POINTER
// \endif
int P30_GetHardwareCapabilities(T_P30_HARDWARE_CAPABILITIES* pHardCapabilities);


/*! @brief Configure swipe reader of P30
 * @param terminalSwipe : TRUE or FALSE activate the terminal swipe reader.
 * @param p30Swipe : TRUE or FALSE activate the pinpad swipe reader.
 * @return OK if successful.
 *  @par exit none
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:P30_ConfigSwipe:KSFAM_PPS_MANAGER:0x53
// \endif
int P30_ConfigSwipe(int terminalSwipe, int p30Swipe);


/*! @brief Print a ticket with pinpad hardware description
 * @return None
 * @par exit None
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:P30_PrintHardwareCapabilities:KSFAM_PPS_MANAGER:0x54
// \endif
void P30_PrintHardwareCapabilities(void);


/*! @brief Print a ticket with software component information of a pinpad
 * @return Note
 * @par exit None
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:P30_PrintComponents:KSFAM_PPS_MANAGER:0x55
// \endif
void P30_PrintComponents(void);


#endif
/*! @} **/
