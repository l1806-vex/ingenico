#ifndef __DBLUETOOTH_H_INCLUDED__
#define __DBLUETOOTH_H_INCLUDED__

/*! @addtogroup KSFAM_BLUE_TOOTH
	* @{
			
 	* @section Description  Samples

 	* The sample of code below shows how to use API OPEN_BT (new peripheral on recent Bluetooth devices)
	@code
 * static int bluetooth_fioctl(int function, void *param) {
 *     int   a_renvoyer    = 0;
 *     FILE *bluetooth          = NULL;
 *     FILE *bluetooth_stdperif = NULL;
 *     FILE *bluetooth_fopen    = NULL;
 * 
 *     bluetooth_fopen = fopen("INTER_UC_BT", "rw*");
 *     if(bluetooth_fopen == NULL) {
 *         bluetooth_stdperif = stdperif("INTER_UC_BT", NULL);
 *         if(bluetooth_stdperif != NULL) {
 *             bluetooth = bluetooth_stdperif;
 *         }
 *     } else {
 *         bluetooth = bluetooth_fopen;
 *     }
 *     if(bluetooth != NULL) {
 *         a_renvoyer = fioctl(function, param, bluetooth);
 * 	}
 *     if(bluetooth_fopen != NULL) {
 *         fclose(bluetooth_fopen);
 *     }
 *     return(a_renvoyer);
 * }
 * 
 * static void util_bt_open_bt(void){
 * 	FILE *open_bt = fopen("OPEN_BT", "rw*");
 * 	if(open_bt){
 * 		const char *choices[9];
 * 
 * 		choices[0] = "Set Visible";
 * 		choices[1] = "Set Invisible";
 * 		choices[2] = "Set Pin Code";
 * 		choices[3] = "Send data";
 * 		choices[4] = "Receive data";
 * 		choices[5] = "Name=titi";
 * 		choices[6] = "Name=titi2";
 * 		choices[7] = "GetName";
 * 		choices[8] = NULL;
 * 
 * 		const char pin_code[17] = "123456";
 * 
 * 		int s = 0;
 * 		do{
 * 			int visibility;
 * 			s = op_selection("OPEN_BT", choices, s, 0); // Display a list of items to select from
 * 			switch(s){
 * 				case 0:
 * 					visibility = OPEN_BT_VISIBILITY_VISIBLE;
 * 					bluetooth_fioctl(DBLUETOOTH_FIOCTL_OPEN_BT_SET_VISIBILITY, &visibility);
 * 				break;
 * 				case 1:
 * 					visibility = OPEN_BT_VISIBILITY_INVISIBLE;
 * 					bluetooth_fioctl(DBLUETOOTH_FIOCTL_OPEN_BT_SET_VISIBILITY, &visibility);
 * 				break;
 * 				case 2:
 * 					bluetooth_fioctl(DBLUETOOTH_FIOCTL_OPEN_BT_SET_PINCODE, (void*)pin_code);
 * 				break;
 * 				case 3:
 * 					fwrite("Hello World !", 1, 13, open_bt);
 * 				break;
 * 				case 4:
 * 				{
 * 					unsigned char buffer[64];
 * 					mask_event(open_bt, COM_REC_NOT_EMPTY);
 * 					reset_buf(open_bt, _receive_id);
 * 					printf("\x1B" "Waiting event ...");
 * 					for(;;){
 * 						unsigned int event_occurred = ttestall(COM_EXT | KEYBOARD, 1000);
 * 						if(event_occurred){
 * 							if(event_occurred & KEYBOARD){
 * 								break;
 * 							}
 * 							int n = fread(buffer, 1, sizeof(buffer), open_bt);
 * 							printf("\x1B" "Received %d" "\n", n);
 * 						}else{
 * 							printf("\x1B" "!!! TIMEOUT !!!");
 * 						}
 * 					}
 * 				}
 * 				break;
 * 				case 5:
 * 				    bluetooth_fioctl(DBLUETOOTH_FIOCTL_OPEN_BT_SET_NAME, "titi");
 * 				break;
 * 				case 6:
 * 				    bluetooth_fioctl(DBLUETOOTH_FIOCTL_OPEN_BT_SET_NAME, "titi2");
 * 				break;
 * 				case 7:
 * 				{
 * 					char name[DBLUETOOTH_SPP_INFO_MAX_BASE_NAME_SIZE + 1];
 * 					name[0] = '\0';
 * 				    bluetooth_fioctl(DBLUETOOTH_FIOCTL_OPEN_BT_GET_NAME, name);
 * 					pprintf("Name = [%s]" "\n", name);
 * 				}
 * 				break;
 * 			}
 * 		}while(0 <= s);
 * 		fclose(open_bt);
 * 	}
 * }
 * 
 *
 * @endcode
 * @link KSFAM_BLUE_TOOTH Back to top @endlink
 */ 


/*
======================================================================
					List of Defines
======================================================================
*/

// API for driver "INTER_UC_BT"
#define    DBLUETOOTH_STATE_INIT                     (0)		/*!< Initial value for status field in dbluetooth_info_xxx structure */
#define    DBLUETOOTH_STATE_BLUETOOTH_ADDRESS_KNOWN  (1)		/*!< Value for status field in dbluetooth_info_xxx structure when Bluetooth device has started and given its Bluetooth address */
#define    DBLUETOOTH_STATE_DEVICE_UNDER_TEST_REQ    (2)    /*!< Value for status field in dbluetooth_info_xxx structure when DUT mode has been requested (for internal testing only) */ 		
#define    DBLUETOOTH_STATE_DEVICE_UNDER_TEST_CFM    (3)    /*!< Value for status field in dbluetooth_info_xxx structure when device is in DUT mode (for internal testing only) */ 

// FIOCTL : return values
#define DBLUETOOTH_FIOCTL_SUCCESS           (0)			/*!< The last fioctl has successfully completed */
#define DBLUETOOTH_FIOCTL_NOT_IMPLEMENTED   (-1)		/*!< The last fioctl is not implemened in the device driver */
#define DBLUETOOTH_FIOCTL_WRONG_PARAMETER   (-2)		/*!< An improper parameter has been given too the last fioctl (for example, NULL pointeur when a parameter was expected) */
#define DBLUETOOTH_FIOCTL_ALREADY_CONNECTED (-3)		/*!< Connection request when already connected (deprecated) */
#define DBLUETOOTH_FIOCTL_NOT_CONNECTED     (-4)		/*!< Disconnection request when not connected (deprecated) */

// FIOCTL : implemented functions
#define DBLUETOOTH_FIOCTL_EXTERNAL      (0x8000)		/*!< Not an actual fioctl, just the starting number for all public fioctl of this device driver */
#define DBLUETOOTH_FIOCTL_CLOSE_COM     (DBLUETOOTH_FIOCTL_EXTERNAL + 0x00)		/*!< Request the driver to release (fclose()) the COM2 (deprecated) */
#define DBLUETOOTH_FIOCTL_OPEN_COM      (DBLUETOOTH_FIOCTL_EXTERNAL + 0x01)		/*!< Allow the driver to access (fopen()) the COM2(deprecated)  */
#define DBLUETOOTH_FIOCTL_GET_INFO      (DBLUETOOTH_FIOCTL_EXTERNAL + 0x02)		/*!< Obtain informations from the device driver in a dbluetooth_info_s structure*/
#define DBLUETOOTH_FIOCTL_DUT_MODE      (DBLUETOOTH_FIOCTL_EXTERNAL + 0x05)		/*!< Request Device Under Test mode (for internal testing only) */
#define DBLUETOOTH_FIOCTL_RETROFIT      (DBLUETOOTH_FIOCTL_EXTERNAL + 0x06)		/*!< Request SPI retrofit mode (for internal use only) */

// Association
#define DBLUETOOTH_FIOCTL_ASSOCIATION     (DBLUETOOTH_FIOCTL_EXTERNAL + 0x08)		/*!< Request association to the base the device is on */
#define DBLUETOOTH_FIOCTL_REMOVE_BASE     (DBLUETOOTH_FIOCTL_EXTERNAL + 0x09)		/*!< Request to remove a base from the base database */
#define DBLUETOOTH_FIOCTL_BASES_INFOS     (DBLUETOOTH_FIOCTL_EXTERNAL + 0x0A)		/*!< Obtain informations about all known bases in the base database */
#define DBLUETOOTH_FIOCTL_SELECT_BASE     (DBLUETOOTH_FIOCTL_EXTERNAL + 0x0B)		/*!< Request that a base be used for all possible device */
#define DBLUETOOTH_FIOCTL_GET_ADDRESSES   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x0C)		/*!< Request the descending order base serial number array of base(s) to connect to */
#define DBLUETOOTH_FIOCTL_BASES_INFOS_EXT (DBLUETOOTH_FIOCTL_EXTERNAL + 0x0D)		/*!< Obtain more informations about known bases */

// Number of element for the unsigned int array passed to _GET_ADDRESSES
// @see definition in inter_uc_sp_options_const.h
#ifndef MAX_ADDRESS
#   define MAX_ADDRESS (8)		/*!< Max number of element in the array for DBLUETOOTH_FIOCTL_GET_ADDRESSES fioctl */
#endif

// Power control
#define DBLUETOOTH_FIOCTL_POWER           (DBLUETOOTH_FIOCTL_EXTERNAL + 0x0E)		/*!< Request change in the power state of the Bluetooth device */

#define DBLUETOOTH_POWER_OFF (0)		/*!< parameter value for DBLUETOOTH_FIOCTL_POWER fioctl to shut Bluetooth device power down */
#define DBLUETOOTH_POWER_ON  (1)		/*!< paramater value for DBLUETOOTH_FIOCTL_POWER fioctl to power Bluetooth device up */

// association error code 
#define DBLUETOOTH_FIOCTL_ASSOCIATION_SUCCESS               (0)			/*!< Association request successfull */
#define DBLUETOOTH_FIOCTL_ASSOCIATION_CANNOT_CONNECT        (-1)		/*!< Association failure because InfraRed link not available (trace on COM0, MODEM.IS_IR or COM0.IS_IR selected) */
#define DBLUETOOTH_FIOCTL_ASSOCIATION_CONNECT_TIMEOUT       (-2)		/*!< Association failure because base couldn't be connected to (not a smart base ?) */
#define DBLUETOOTH_FIOCTL_ASSOCIATION_CANNOT_SEND           (-3)		/*!< Association failure because request couldn't be transmited */
#define DBLUETOOTH_FIOCTL_ASSOCIATION_RECEIVE_TIMEOUT       (-4)		/*!< Association failure because association request was successfully received by base, but no answer was received */
#define DBLUETOOTH_FIOCTL_ASSOCIATION_BT_ADDRESS_NULL       (-5)		/*!< Association failure because of a NULL address for the base Bluetooth device (either not started yet or Out Of Order) */
#define DBLUETOOTH_FIOCTL_ASSOCIATION_OUT_OF_BASE           (-6)		/*!< Associtaion failure because portable was not on cradle */
#define DBLUETOOTH_FIOCTL_ASSOCIATION_WRONG_DRIVER          (-7)		/*!< Association failure because Device driver is too old (either portable or base) */
#define DBLUETOOTH_FIOCTL_ASSOCIATION_UNKNOWN_BASE_FW       (-8)		/*!< Association failure because firmware version for the base Bluetooth device not known (yet, or Out Of Order) */
#define DBLUETOOTH_FIOCTL_ASSOCIATION_UNKNOWN_PORTABLE_FW   (-9)		/*!< Association failure because firmware version for the portable Bluetooth device is not known (yet, or Out Of Order) */
#define DBLUETOOTH_FIOCTL_ASSOCIATION_BASE_FW_IS_16_4_4     (-10)		/*!< Association failure because of improper base Bluetooth device firmware version */
#define DBLUETOOTH_FIOCTL_ASSOCIATION_PORTABLE_FW_IS_16_4_4 (-11)		/*!< Association failure because of improper portable Bluetooth device firmware version */
#define DBLUETOOTH_FIOCTL_ASSOCIATION_BOTH_FW_ARE_16_4_4    (-12)		/*!< Association failure because both portable and base have improper Bluetooth device firmware version */

// COM0
#define DBLUETOOTH_FIOCTL_GET_COM0_IS_IR     (DBLUETOOTH_FIOCTL_EXTERNAL + 0x12)		/*!< Is COM0 configured to work on a plain P base (not a smart one) ? */
#define DBLUETOOTH_FIOCTL_SET_COM0_IS_IR     (DBLUETOOTH_FIOCTL_EXTERNAL + 0x13)		/*!< Set COM0 to work on plain P base, or not (restart required to be taken into account) */
#define DBLUETOOTH_FIOCTL_GET_COM0_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x14)		/*!< Is COM0 configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_COM0_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x15)		/*!< Set COM0 to work on InfraRed only or not */
#define DBLUETOOTH_FIOCTL_GET_COM0_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x16)		/*!< Get the serial number (ie address) of the base providing COM0 */
#define DBLUETOOTH_FIOCTL_SET_COM0_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x17)		/*!< Set the serial number (ie address) of the base providing COM0 */
#define DBLUETOOTH_FIOCTL_DOES_COM0_NEED_BASE (DBLUETOOTH_FIOCTL_EXTERNAL + 0x18)		/*!< Deprecated */

// Values for the above fioctl()
#define DBLUETOOTH_FIOCTL_COM0_DONT_NEED_BASE (1)		/*!< Deprecated */
#define DBLUETOOTH_FIOCTL_COM0_NEED_BASE      (0)		/*!< Deprecated */

// COM1
#define DBLUETOOTH_FIOCTL_GET_COM1_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0x20)		/*!< Is COM1 configured to work through USB CDC ? */
#define DBLUETOOTH_FIOCTL_SET_COM1_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0x21)		/*!< Set COM1 to work through USB CDC, or not (restart required to be taken into account) */
#define DBLUETOOTH_FIOCTL_GET_COM1_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x22)		/*!< Is COM1 configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_COM1_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x23)		/*!< Set COM1 to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_GET_COM1_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x24)		/*!< Get the serial number (ie address) of the base providing COM1 */
#define DBLUETOOTH_FIOCTL_SET_COM1_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x25)		/*!< Set the serial number (ie address) of the base providing COM1 */

// COMN
#define DBLUETOOTH_FIOCTL_GET_COMN_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x30)		/*!< Is COMN configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_COMN_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x31)		/*!< Set COMN to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_GET_COMN_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x32)		/*!< Get the serial number (ie address) of the base providing Ethernet (COMN) */
#define DBLUETOOTH_FIOCTL_SET_COMN_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x33)		/*!< Set the serial number (ie address) of the base providing Ethernet (COMN) */
#define DBLUETOOTH_FIOCTL_ETHERNET_CONNECTION_PROGRESS \
                                             (DBLUETOOTH_FIOCTL_EXTERNAL + 0x34)		/*!< Get progress for the PPP connection between portable and base (Ethernet base only) */
#define DBLUETOOTH_FIOCTL_ETHERNET_GET_INTERNET_INFO \
                                             (DBLUETOOTH_FIOCTL_EXTERNAL + 0x35)		/*!< Equivalent to SYS_FIOCTL_GET_ETHERNET_INFO but for the base */
#define DBLUETOOTH_FIOCTL_ETHERNET_GET_PPP_HANDLE \
                                             (DBLUETOOTH_FIOCTL_EXTERNAL + 0x36)		/*!< Internal use only */

// MODEM
#define DBLUETOOTH_FIOCTL_GET_MODEM_IS_IR    (DBLUETOOTH_FIOCTL_EXTERNAL + 0x42)		/*!< Is MODEM configured to work on a plain P base (not a smart one) ? */
#define DBLUETOOTH_FIOCTL_SET_MODEM_IS_IR    (DBLUETOOTH_FIOCTL_EXTERNAL + 0x43)		/*!< Set MODEM to work on plain P base, or not (restart required to be taken into account) */
#define DBLUETOOTH_FIOCTL_GET_MODEM_FORCE_IR (DBLUETOOTH_FIOCTL_EXTERNAL + 0x44)		/*!< Is MODEM configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_MODEM_FORCE_IR (DBLUETOOTH_FIOCTL_EXTERNAL + 0x45)		/*!< Set MODEM to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_GET_MODEM_ADDRESS  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x46)		/*!< Get the serial number (ie address) of the base providing MODEM */
#define DBLUETOOTH_FIOCTL_SET_MODEM_ADDRESS  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x47)		/*!< Set the serial number (ie address) of the base providing MODEM */

#define DBLUETOOTH_FIOCTL_SET_PRE_AMP_LEVEL      (DBLUETOOTH_FIOCTL_EXTERNAL + 0x50)		/*!< Internal use only */
#define DBLUETOOTH_FIOCTL_GET_BASE_PRE_AMP_LEVEL (DBLUETOOTH_FIOCTL_EXTERNAL + 0x51)		/*!< Internal use only */
#define DBLUETOOTH_FIOCTL_SET_BASE_PRE_AMP_LEVEL (DBLUETOOTH_FIOCTL_EXTERNAL + 0x52)		/*!< Internal use only */
#define DBLUETOOTH_FIOCTL_RESET_BASE_SECRET      (DBLUETOOTH_FIOCTL_EXTERNAL + 0x53)		/*!< Request the base to erase its secrets (Bluetooth PIN Code and 3DES key) ; re-association of all portables is required */
#define DBLUETOOTH_FIOCTL_SET_BASE_NAME          (DBLUETOOTH_FIOCTL_EXTERNAL + 0x54)		/*!< Request to set a clear name for a base different from its initial value (string representing serial number) */
#define DBLUETOOTH_FIOCTL_GET_BASE_NAME          (DBLUETOOTH_FIOCTL_EXTERNAL + 0x55)		/*!< Request to get the clear name of the base we're sitting on */

#define DBLUETOOTH_FIOCTL_RESET_BASE (DBLUETOOTH_FIOCTL_EXTERNAL + 0x60)		/*!< Request a base restart */

#ifndef SYS_FIOCTL_GET_ETHERNET_INFO
#define SYS_FIOCTL_GET_ETHERNET_INFO  0x802D		/*!< Internal use only */
#endif

#define DBLUETOOTH_FIOCTL_GET_BASE_USERS (DBLUETOOTH_FIOCTL_EXTERNAL + 0x70)		/*!< Obtain the list of peripherals that are available / used in a base we're connected to*/

#define DBLUETOOTH_FIOCTL_GET_BASE_LIST_FOR_PERIPHERAL_MASK \
                                         (DBLUETOOTH_FIOCTL_EXTERNAL + 0x71)		/*!< Get a list of base serial number having the required peripheral(s) @see definition of dbluetooth_base_list_for_peripheral_s struct */

#define DBLUETOOTH_FIOCTL_GET_BASE_PERIPHERAL_MASK_FROM_TYPE \
                                         (DBLUETOOTH_FIOCTL_EXTERNAL + 0x72)		/*!< Get the mask of available peripheral(s) from the base kind */
                                         
#define DBLUETOOTH_FIOCTL_GET_BASE_USERS_EX (DBLUETOOTH_FIOCTL_EXTERNAL + 0x73)		/*!< Obtain the list of peripherals that are available / used in a base we're connected to, plus the user of each PPP connection between portable and base */

#define DBLUETOOTH_CONNECTION_PROGRESS_IDLE          (-1)		/*!< Bluetooth link idle */
#define DBLUETOOTH_CONNECTION_PROGRESS_NOT_CONNECTED (0)		/*!< Bluetooth link not connected */
#define DBLUETOOTH_CONNECTION_PROGRESS_CONNECTING    (1)		/*!< Bluetooth link connecting */
#define DBLUETOOTH_CONNECTION_PROGRESS_CONNECTED     (2)		/*!< Bluetooth link connected */
#define DBLUETOOTH_CONNECTION_PROGRESS_DISCONNECTING (3)		/*!< Bluetooth link disconnecting */
#define DBLUETOOTH_CONNECTION_PROGRESS_WAITING       (4)		/*!< Bluetooth link waiting for incoming connection (OpenBT) */

// DOWNLOAD / UPLOAD between portable and base
#define DBLUETOOTH_FIOCTL_EXCHANGE_SESSION_PARAM  (0x80)		/*!< Configure file exchange session */
#define DBLUETOOTH_FIOCTL_EXCHANGE_SESSION_ABORT  (0x81)		/*!< Abort file exchange session */
#define DBLUETOOTH_FIOCTL_EXCHANGE_SESSION_INFO   (0x82)		/*!< Obtain file exchange session progress information*/

// Status and Errors
#define DBLUETOOTH_FIOCTL_EXCHANGE_SUCCESS               (0)		/*!< Exchange successfull */
#define DBLUETOOTH_FIOCTL_EXCHANGE_CANNOT_CONNECT        (-1)		/*!< Failure : cannot connect to base (no link available) */
#define DBLUETOOTH_FIOCTL_EXCHANGE_CONNECT_TIMEOUT       (-2)		/*!< Failure : cannot connect to base (no response from base) */
#define DBLUETOOTH_FIOCTL_EXCHANGE_CANNOT_SEND           (-3)		/*!< Failure : cannot send to base */
#define DBLUETOOTH_FIOCTL_EXCHANGE_RECEIVE_TIMEOUT       (-4)		/*!< Failure : receive timeout */
#define DBLUETOOTH_FIOCTL_EXCHANGE_RUF                   (-5)		/*!< Reserved for Future Use */
#define DBLUETOOTH_FIOCTL_EXCHANGE_OUT_OF_BASE           (-6)		/*!< Failure : not on cradle and transfer through InfraRed required */
#define DBLUETOOTH_FIOCTL_EXCHANGE_FILE_DOES_NOT_EXIST   (-7)		/*!< Failure : this file doesn't exist */
#define DBLUETOOTH_FIOCTL_EXCHANGE_DISK_DOES_NOT_EXIST   (-8)		/*!< Failure : this disk doesn't exist */
#define DBLUETOOTH_FIOCTL_EXCHANGE_SRC_FILE_READ_ERROR   (-9)		/*!< Failure : cannot read source file */
#define DBLUETOOTH_FIOCTL_EXCHANGE_TRANSMIT_TIMEOUT      (-10)	/*!< Failure : transmit timeout */
#define DBLUETOOTH_FIOCTL_EXCHANGE_UNKNOWN_REQUEST_TYPE  (-11)	/*!< Failure : unknown request type */
#define DBLUETOOTH_FIOCTL_EXCHANGE_RECEIVE_ERROR         (-12)	/*!< Failure : receive error */
#define DBLUETOOTH_FIOCTL_EXCHANGE_ABORT                 (-13)	/*!< Failure : user abort */
#define DBLUETOOTH_FIOCTL_EXCHANGE_DISK_NOT_ALLOWED      (-14)	/*!< Failure : use of this disk not allowed */
#define DBLUETOOTH_FIOCTL_EXCHANGE_CONNECT_ERROR         (-15)	/*!< Failure : cannot connect to base */

#define DBLUETOOTH_FIOCTL_HTTP_CLIENT_REQUEST_TYPE_ERROR    (-2)	/*!< Invalid request */
#define DBLUETOOTH_FIOCTL_HTTP_CLIENT_REQUEST_TYPE_LAST     (-1)	/*!< Last value in array of parameters */
#define DBLUETOOTH_FIOCTL_HTTP_CLIENT_REQUEST_TYPE_CONNECT  (0)		/*!< Connect information to contact the base for further tranfers */
#define DBLUETOOTH_FIOCTL_HTTP_CLIENT_REQUEST_TYPE_GET      (1)		/*!< GET parameters for retrieving a file from the base */
#define DBLUETOOTH_FIOCTL_HTTP_CLIENT_REQUEST_TYPE_PUT      (2)		/*!< PUT parameters for sending a file to the base */
#define DBLUETOOTH_FIOCTL_HTTP_CLIENT_REQUEST_TYPE_ACTIVATE (3)		/*!< Activate (disk name for SoftwareActivate() in the base) */

#define DBLUETOOTH_FIOCTL_HTTP_CLIENT_STATUS_IDLE          (0)		/*!< No activity in progress */
#define DBLUETOOTH_FIOCTL_HTTP_CLIENT_STATUS_CONNECTING    (1)		/*!< HTTP Client connecting */
#define DBLUETOOTH_FIOCTL_HTTP_CLIENT_STATUS_CONNECTED     (2)		/*!< HTTP Client connected */
#define DBLUETOOTH_FIOCTL_HTTP_CLIENT_STATUS_DISCONNECTING (3)		/*!< HTTP Client disconnecting */
#define DBLUETOOTH_FIOCTL_HTTP_CLIENT_STATUS_SENDING       (4)		/*!< HTTP Client sending */
#define DBLUETOOTH_FIOCTL_HTTP_CLIENT_STATUS_RECEIVING     (5)		/*!< HTTP Client receiving */
#define DBLUETOOTH_FIOCTL_HTTP_CLIENT_STATUS_ACTIVATING    (6)		/*!< HTTP Client sending activation request */

// COMU
#define DBLUETOOTH_FIOCTL_GET_COMU_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x92)		/*!< Is COMU configured to use only InfraRed link ? */
#define DBLUETOOTH_FIOCTL_SET_COMU_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x93)		/*!< Set COMU to work on InfraRed only or not */
#define DBLUETOOTH_FIOCTL_GET_COMU_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x94)		/*!< Get the serial number (ie address) of the base providing COMU */
#define DBLUETOOTH_FIOCTL_SET_COMU_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x95)		/*!< Set the serial number (ie address) of the base providing COMU */

// COMH (930 BC06) / COMUSB1 (iWL)
#define DBLUETOOTH_FIOCTL_GET_COMH_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0xA0)		/*!< Is COMH (930) / COMUSB1 (iWL)  configured to work through USB CDC ? */
#define DBLUETOOTH_FIOCTL_SET_COMH_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0xA1)		/*!< Set COMH (930) / COMUSB1 (iWL)  to work through USB CDC, or not (restart required to be taken into account) */
#define DBLUETOOTH_FIOCTL_GET_COMH_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0xA2)		/*!< Is COMH (930) / COMUSB1 (iWL)  configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_COMH_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0xA3)		/*!< Set COMH (930) / COMUSB1 (iWL)  to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_GET_COMH_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0xA4)		/*!< Get the serial number (ie address) of the base providing COMH (930) / COMUSB1 (iWL) */
#define DBLUETOOTH_FIOCTL_SET_COMH_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0xA5)		/*!< Set the serial number (ie address) of the base providing COMH (930) / COMUSB1 (iWL)  */

#define DBLUETOOTH_FIOCTL_GET_COMUSB1_IS_CDC   	DBLUETOOTH_FIOCTL_GET_COMH_IS_CDC   	/*!< Is COMH (930) / COMUSB1 (iWL)  configured to work through USB CDC ? */
#define DBLUETOOTH_FIOCTL_SET_COMUSB1_IS_CDC   	DBLUETOOTH_FIOCTL_SET_COMH_IS_CDC   	/*!< Set COMH (930) / COMUSB1 (iWL)  to work through USB CDC, or not (restart required to be taken into account) */
#define DBLUETOOTH_FIOCTL_GET_COMUSB1_FORCE_IR 	DBLUETOOTH_FIOCTL_GET_COMH_FORCE_IR 	/*!< Is COMH (930) / COMUSB1 (iWL)  configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_COMUSB1_FORCE_IR 	DBLUETOOTH_FIOCTL_SET_COMH_FORCE_IR 	/*!< Set COMH (930) / COMUSB1 (iWL)  to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_GET_COMUSB1_ADDRESS  	DBLUETOOTH_FIOCTL_GET_COMH_ADDRESS  	/*!< Get the serial number (ie address) of the base providing COMH (930) / COMUSB1 (iWL) */
#define DBLUETOOTH_FIOCTL_SET_COMUSB1_ADDRESS  	DBLUETOOTH_FIOCTL_SET_COMH_ADDRESS  	/*!< Set the serial number (ie address) of the base providing COMH (930) / COMUSB1 (iWL)  */

// COMUSB2 (iWL only)
#define DBLUETOOTH_FIOCTL_GET_COMUSB2_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0xB0)		/*!< Is COMUSB2 configured to work through USB CDC ? */
#define DBLUETOOTH_FIOCTL_SET_COMUSB2_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0xB1)		/*!< Set COMUSB2 to work through USB CDC, or not (restart required to be taken into account) */
#define DBLUETOOTH_FIOCTL_GET_COMUSB2_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0xB2)		/*!< Is COMUSB2 configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_COMUSB2_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0xB3)		/*!< Set COMUSB2 to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_GET_COMUSB2_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0xB4)		/*!< Get the serial number (ie address) of the base providing COMUSB2 */
#define DBLUETOOTH_FIOCTL_SET_COMUSB2_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0xB5)		/*!< Set the serial number (ie address) of the base providing COMUSB2 */

#define DBLUETOOTH_FIOCTL_GET_INFO_BC06      (DBLUETOOTH_FIOCTL_EXTERNAL + 0x100)		/*!< Obtain informations for BC06 devices */

#define OPEN_BT_VISIBILITY_VISIBLE   (1)		/*!< OpenBT : portable device becomes visible to Bluetooth scan request */
#define OPEN_BT_VISIBILITY_INVISIBLE (0)		/*!< OpenBT : portable device becomes invisible to Bluetooth scan request (default behaviour) */

#define DBLUETOOTH_FIOCTL_OPEN_BT_SET_VISIBILITY \
											 (DBLUETOOTH_FIOCTL_EXTERNAL + 0x101)		/*!< Set visibility state regarding Bluetooth scan */
#define DBLUETOOTH_FIOCTL_OPEN_BT_SET_PINCODE \
											 (DBLUETOOTH_FIOCTL_EXTERNAL + 0x102)		/*!< Set the PIN code for the OpenBT Bluetooth link */
#define DBLUETOOTH_FIOCTL_OPEN_BT_SET_NAME   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x103)		/*!< Set the name for the OpenBT Bluetooth link */
#define DBLUETOOTH_FIOCTL_OPEN_BT_GET_NAME   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x104)		/*!< Get the name for the OpenBT Bluetooth link */

#define DBLUETOOTH_FIOCTL_GET_PRESENCE_PORTABLE    (DBLUETOOTH_FIOCTL_EXTERNAL + 0x110) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_GET_PRESENCE_SOCLE       (DBLUETOOTH_FIOCTL_EXTERNAL + 0x110) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_ALIM_EXAR                (DBLUETOOTH_FIOCTL_EXTERNAL + 0x111) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_GET_FLOW_CONTROL         (DBLUETOOTH_FIOCTL_EXTERNAL + 0x112) /*!< Internal use only */

// This event was choosen to be GPRS one, because GPRS + BLUETOOTH didn't exist
#define E_DBLUETOOTH_FIOCTL_EXCHANGE_STATUS_CHANGED (23)			/*!< Event fired to signal a change in file exchange status */
#define DBLUETOOTH_FIOCTL_EXCHANGE_STATUS_CHANGED   (1 << E_DBLUETOOTH_FIOCTL_EXCHANGE_STATUS_CHANGED)		/*!< Eventmask to wait for a change in file exchange status */

#define DBLUETOOTH_SEND_DATA_UNKNOWN_MUX_ID_OR_NOT_CONNECTED (-1)		/*!< deprecated */

#define DBLUETOOTH_CALLBACK_TYPE_CONNECT_OK_INDICATION   (1)		/*!< Internal use only */
#define DBLUETOOTH_CALLBACK_TYPE_CONNECT_KO_INDICATION   (2)		/*!< Internal use only */
#define DBLUETOOTH_CALLBACK_TYPE_DATA_INDICATION         (3)		/*!< Internal use only */
#define DBLUETOOTH_CALLBACK_TYPE_DATA_CONFIRM            (4)		/*!< Internal use only */
#define DBLUETOOTH_CALLBACK_TYPE_DISCONNECT_INDICATION   (5)		/*!< Internal use only */
#define DBLUETOOTH_CALLBACK_TYPE_SERVICE_NAME_INDICATION (6)		/*!< Internal use only */
#define DBLUETOOTH_CALLBACK_TYPE_LOW_POWER_REQ           (7)		/*!< Internal use only */
#define DBLUETOOTH_CALLBACK_TYPE_LOW_POWER_END           (8)		/*!< Internal use only */

#ifdef _GSIM_
typedef struct {
    unsigned int  nap_uap;	/*!< Non significant Address Part + Upper Address Part */
    unsigned int  lap;		  /*!< Lower Address Part */							
} dbluetooth_device_addr_s; // total size 2 * 4
#else
/*! @brief  Define the address of the bluetooth device. (total size 2 * 4)  */
typedef struct {
    unsigned int  nap:16,							/*!< Non significant Address Part 32..47 */
                  uap:8;							/*!< uap:8 : Upper Address Part 24..31 */
    unsigned int  lap;								/*!< lap : Lower Address part 00..23 */
} dbluetooth_device_addr_s; // total size 2 * 4
#endif

typedef void (*generic_callback_t)(void * /* param */, unsigned int /* type */, const unsigned char * /* data */, unsigned int /* data_len */); //!< Internal use only 
typedef int (*pass_key_callback_t)(dbluetooth_device_addr_s * /* Remote Address */, char *pass_key /* Result : PIN */); /* @return 0 if PIN found, < 0 else */ //!< Internal use only 

/*! @brief Define the parameters of connection for the bluetooth.  */
// GSIM_T:dbluetooth_connection_param_s:DATA_CODE(4 + strlen(name) + sizeof(int) + 8 ) 
typedef struct {
    int                      mux_id;					/*!< which SPP to use. */
    dbluetooth_device_addr_s addr;						/*!< address of remote host to connect to. (used by connect() only). */
    generic_callback_t       callback;				/*!< function to call to inform user. */
    void                    *callback_param;	/*!< user parameter passed back as first parameter to the callback function. */
    const char              *name;						/*!< name of SPP (used in listen only). */
} dbluetooth_connection_param_s;

/*! @brief Define the sent parameters of the bluetooth.  */
//GSIM_T:dbluetooth_send_param_s:DATA_CODE(sizeof(int) * 2 + data_len) 
typedef struct {
    int                  mux_id;					/*!< which SPP  */
    const unsigned char *data;						/*!< pointer to start of data  */
    unsigned int         data_len;				/*!< data length  */
} dbluetooth_send_param_s;

#define DBLUETOOTH_SPP_INFO_MAX_NAME_SIZE (7)					/*!< Max size for the name of an SPP instance */
#define DBLUETOOTH_SPP_INFO_MAX_BASE_NAME_SIZE (15)		/*!< Max size for the clear name of a base */

/*! @brief Define the SPP information. */
// GSIM_T:dbluetooth_spp_info_s:DATA_CODE((2+5+2+4+1+1) * 4) 
typedef struct {
    dbluetooth_device_addr_s remote_address;				/*!< BlueTooth address of the remote device this SPP instance is connected to. */
    int                      connection_progress;		/*!< see DBLUETOOTH_CONNECTION_PROGRESS_xxx  */
    int                      last_result;						/*!< Last SPP_xxx_IND message result */
    int                      max_frame_size;				/*!< Maximum Size of a frame for this SPP instance */
    int                      mux_id;								/*!< Multiplexer ID : for internal use only */
    int                      server_channel;				/*!< Server Channel : for internal use only */
    char                     name[DBLUETOOTH_SPP_INFO_MAX_NAME_SIZE + 1];					/*!< Name of this SPP instance */
	char                     base_name[DBLUETOOTH_SPP_INFO_MAX_BASE_NAME_SIZE + 1];	/*!< Name of the base this instance is connected to */
    generic_callback_t      callback;								/*!< User (but supervisor) callback  */
    void                   *callback_param;					/*!< User parameter passed back to the callback as first argument. */
} dbluetooth_spp_info_s; // total size (2 + 5 + 2 + 4 + 1 + 1) * 4 = 15 * 4

#define DBLUETOOTH_SPP_NUMBER_RFCOMM (3) /*!< Number of SPP link for RFCOMM build (bc02 device) */

/*! @brief Define the bluetooth information. (total size : 256 )  */
// GSIM_T:dbluetooth_info_s:DATA_CODE(4 +  9 * sizeof(int) + 60 + sizeof(int) * (64 - (2 + 4 + (15 * 3) + 3 + 3 + 3 + 1 + 1 + 1)) + 8 ) 
typedef struct {
    dbluetooth_device_addr_s local_address;						       /*!< BlueTooth address of the embedded device  */
    void                    *com2_file;							         /*!< pointer on a file (FILE *com2)  */
    int                      status;							           /*!< current status of the instance, see DBLUETOOTH_STATE_xxx  */
    int                      dut_status;						         /*!< status of the last Device Under Test Confirm  */
    int                      dut_step;							         /*!< step number of the last Device Under Test Confirm  */
    dbluetooth_spp_info_s    spp_info[DBLUETOOTH_SPP_NUMBER_RFCOMM];       /*!< informations on each SPP instance  */
    unsigned int             round_trip_lst[DBLUETOOTH_SPP_NUMBER_RFCOMM]; /*!< time, in ticks (10 ms) of the round trip of the last service package between the portable and the base for the selected channel.  */
    unsigned int             round_trip_avg[DBLUETOOTH_SPP_NUMBER_RFCOMM]; /*!< average of the 10 last round trip.  */
    unsigned int             time_since_req[DBLUETOOTH_SPP_NUMBER_RFCOMM]; /*!< time, in seconds, since the transmission of the last service framework (usually 0).  */ 
    int                      pre_amplifier_level;				      /*!< pre-amplifier level  */
    unsigned int             firmware_version;					      /*!< version of the firmware  */
    unsigned int             loader_version;					        /*!< version of the loader  */
    unsigned int             rfu[64 - (2 + 4 + (15 * 3) + 3 + 3 + 3 + 1 + 1 + 1)];			/*!< Reserved for Future Use  */
} dbluetooth_info_s; // total size = 256

#define DBLUETOOTH_SPP_NUMBER_HCI (7)		/*!< number of SPP link for HCI build (bc06) */

/*! @brief Define the bluetooth information for new (BC06) devices */
typedef struct {
    dbluetooth_device_addr_s local_address;						      /*!< BlueTooth address of the embedded device */
    void                    *com2_file;							        /*!< pointer on a file (FILE *com2) */
    int                      status;							        	/*!< current status of the instance, see DBLUETOOTH_STATE_ xxx */
    int                      dut_status;						        /*!< status of the last Device Under Test Confirm */
    int                      dut_step;							        /*!< step number of the last Device Under Test Confirm */ 
    dbluetooth_spp_info_s    spp_info[DBLUETOOTH_SPP_NUMBER_HCI];       /*!< informations on each SPP instance */
    unsigned int             round_trip_lst[DBLUETOOTH_SPP_NUMBER_HCI]; /*!< time, in ticks (10 ms) of the round trip of the last service package between the portable and the base for the selected channel. */
    unsigned int             round_trip_avg[DBLUETOOTH_SPP_NUMBER_HCI]; /*!< average of the 10 last round trip. */
    unsigned int             time_since_req[DBLUETOOTH_SPP_NUMBER_HCI]; /*!< time, in seconds, since the transmission of the last service framework (usually 0). */
    int                      rssi[DBLUETOOTH_SPP_NUMBER_HCI];           /*!< Receive Signal Strength Indication */
    int                      pre_amplifier_level;				      /*!< pre-amplifier level  */
    unsigned int             firmware_version;					      /*!< version of the firmware */
    unsigned int             loader_version;					        /*!< version of the loader */
    unsigned int             rfu[8];                          /*!< Reserved for Future Use */
} dbluetooth_info_bc06_s;


/*! @brief Define the information about a public base. */
typedef struct _inter_uc_sp_options_public_base_s {
	unsigned int             serial_number;								/*!< serial number. */
	char                     type[4];											/*!< type of device : "MDM", "ETH", "TSL", "MD2", "UNK", "BME", ... */
	dbluetooth_device_addr_s bt_addr;											/*!< address of the device. */
	char                     name[DBLUETOOTH_SPP_INFO_MAX_BASE_NAME_SIZE + 1];	//!< name of the device. */
} inter_uc_sp_options_public_base_s;

/*! @brief Define the information about a public base. */
typedef struct _inter_uc_sp_options_public_base_ext_s {
	unsigned int             serial_number;								/*!< serial number. */
	char                     type[4];											/*!< type of device : "MDM", "ETH", "TSL", "MD2", "UNK", "BME", ... */
	dbluetooth_device_addr_s bt_addr;											/*!< address of the device. */
	char                     name[DBLUETOOTH_SPP_INFO_MAX_BASE_NAME_SIZE + 1];	//!< name of the device. */
	unsigned int             firmware_version;						/*!< version of the firmware */
	unsigned int             loader_version;							/*!< version of the loader. */
} inter_uc_sp_options_public_base_ext_s;

#define MAXIMUM_NUMBER_OF_BASES (32)		/*!< Maximum number of cradle in portable database */

/*! @brief Define the information about all the public bases. */
typedef struct {
	inter_uc_sp_options_public_base_s	bases[MAXIMUM_NUMBER_OF_BASES];		/*!< information about the bases. */
	unsigned int                        actual_number_of_bases;					/*!< actual number of bases. */
} dbluetooth_bases_infos_s;

/*! @brief Define the information about all the public bases. */
typedef struct {
	inter_uc_sp_options_public_base_ext_s	bases[MAXIMUM_NUMBER_OF_BASES];		/*!< information about the bases */
	unsigned int                        	actual_number_of_bases;						/*!< actual number of bases */
} dbluetooth_bases_infos_ext_s;

// Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl().
#define DBLUETOOTH_SPP_PORTABLE (0)		/*!< Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */
#define DBLUETOOTH_SPP_SOCLE_0  (0)		/*!< Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */
#define DBLUETOOTH_SPP_SOCLE_1  (1)		/*!< Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */
#define DBLUETOOTH_SPP_SOCLE_2  (2)		/*!< Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */

// Added for BC06
#define DBLUETOOTH_SPP_SOCLE_3  (3)		/*!< Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */
#define DBLUETOOTH_SPP_SOCLE_4  (4)		/*!< Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */
#define DBLUETOOTH_SPP_SOCLE_5  (5)		/*!< Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */
#define DBLUETOOTH_SPP_SOCLE_6  (6)		/*!< Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */

// Modified for DBLUETOOTH_FIOCTL_GET_BASE_USERS in case of BC06
// However the IR link does not update any informations about base users (yet)
#define DBLUETOOTH_SPP_SOCLE_IR (7)		/*!< For the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */

// Added for SPP0
#define DBLUETOOTH_SPP_INFO_INDEX_SPP0     (DBLUETOOTH_SPP_SOCLE_5)		/*!< Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */
// Added for OPEN_BT
#define DBLUETOOTH_SPP_INFO_INDEX_OPEN_BT  (DBLUETOOTH_SPP_SOCLE_6)		/*!< Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */

/*! @brief Define the information about the users of a base. */
typedef struct {
	unsigned int base_serial_number;					/*!< Input : chanel number (see above) ; Ouput : serial number of the base */
	unsigned int base_peripheral_users[16];		/*!< (serial_number << 4) + interface_number */
} dbluetooth_base_users_s;

/*! @brief Define the information about the users of a base peripherals and PPPs. */
typedef struct {
	unsigned int base_serial_number;					/*!< Input : chanel number (see above) ; Ouput : serial number of the base */
	unsigned int base_peripheral_users[16];		/*!< (serial_number << 4) + interface_number */
	unsigned int base_ethernet_users[8];		/*!< (serial_number << 4) + interface_number */
} dbluetooth_base_users_ex_s;


/*! @brief Define the exchange request between base and portable . */
typedef struct {
	int request_type;							/*!< type of the request */
	union {
		struct {
			unsigned int address;			/*!< address to connect */
		} connect; 
		struct {
			char remote_disk[20];			/*!< remote disk to activate */
		} activate;
		struct {
			char local_disk[20];			/*!< local disk for the transfer */
			char local_file[20];			/*!< local file to transfer */
			char remote_disk[20];			/*!< remote disk fot the transfer */
			char remote_file[20];			/*!< remote file to transfer. */
		} transfer;
	} request;
} http_client_request_s;


/*! @brief Define the status of an exchange between base and portable. */
typedef struct {
	int  status;						/*!< status of the exchange */
	int  last_error;					/*!< last error during this exchange */
	int  total_size;					/*!< total size of the transfer */
	int  total_completed;				/*!< total size already transfered */
	int  current_size;					/*!< current size of the transfer */
	int  current_completed;				/*!< current size already transfered */
	char local_disk[20];				/*!< local disk for the transfer */
	char local_file[20];				/*!< local file for the transfer */
	char remote_disk[20];				/*!< remote disk for the transfer */
	char remote_file[20];				/*!< remote file for the transfer */
} http_client_status_s;


/*! @brief Define the bluetooth descriptor structure (see COMPONENT.LST ). */
typedef struct {
	char loader_type[1];					/*!< type of loader */
	char coma_0;									/*!< coma (for separation) */
	char file_name[20];						/*!< file name */
	char coma_1;									/*!< coma (for separation) */
	char type[4];									/*!< type informations */
	char coma_2;									/*!< coma (for separation) */
	char family_name[20];					/*!< family name */
	char coma_3;									/*!< coma (for separation) */
	char compressed;							/*!< compressed Y/N */
	char coma_4;									/*!< coma (for separation) */
	char crc_ctrl;								/*!< control CRC */
	char coma_5;									/*!< coma (for separation) */
	char crc[4];									/*!< CRC */
	char coma_6;									/*!< coma (for separation) */
	char code_size[8];						/*!< code size */
	char coma_7;									/*!< coma (for separation) */
	char zip_code_size[8];				/*!< size of the zip code */
	char coma_8;									/*!< coma (for separation) */
	char data_size[8];						/*!< data size */
	char ruf[2];									/*!< Reserved for future use. */
	char cr;											/*!< Carriage Return */
	char lf;											/*!< Line Feed */
} dbluetooth_descriptor_s;

/*! @brief Define the bluetooth ethernet tag descriptor structure.  */
typedef struct {
	union {
		char         octet[4] ;			/*!< tag. ex : {'A', 'D', 'D', 'R'}  */
		unsigned int dword;					/*!< tag  */
	} tag;
	union {
		char         octet[4] ;		  /*!< value. ex : {10, 138, 20, 30}  */
		unsigned int dword;				  /*!< value  */
	} val;
} dbluetooth_ethernet_tag_s ;

#define DBLUETOOTH_TAG_ETHERNET_IP_ADDR 		(0x41444452)		/*!< TAG for Ethernet interface IP address */
#define DBLUETOOTH_TAG_ETHERNET_NETMASK 		(0x4D41534B)		/*!< TAG for Ethernet interface IP netmask */
#define DBLUETOOTH_TAG_ETHERNET_GATEWAY 		(0x47415445)		/*!< TAG for Ethernet gateway IP address */
#define DBLUETOOTH_TAG_ETHERNET_DNS_1_ADDR  (0x444E5331)		/*!< TAG for Ethernet DNS1 address */
#define DBLUETOOTH_TAG_ETHERNET_DNS_2_ADDR  (0x444E5332)		/*!< TAG for Ethernet DNS2 address */


// Define the constants for peripheral_mask in the base list request (DBLUETOOTH_FIOCTL_GET_BASE_LIST_FOR_PERIPHERAL_MASK fioctl) 
#define PERIPHERAL_MASK_RADIO    (1 << 0)			/*!< Mask for radio availability */
#define PERIPHERAL_MASK_MODEM    (1 << 1)			/*!< Mask for MODEM availability */
#define PERIPHERAL_MASK_ETHERNET (1 << 2)			/*!< Mask for Ethernet availability */
#define PERIPHERAL_MASK_COM1     (1 << 3)			/*!< Mask for COM1 availability */
#define PERIPHERAL_MASK_COMH     (1 << 4)			/*!< Mask for COMH availability */
#define PERIPHERAL_MASK_COM0     (1 << 5)			/*!< Mask for COM0 availability */
#define PERIPHERAL_MASK_COMU     (1 << 6)			/*!< Mask for COMU availability */
#define PERIPHERAL_MASK_COMH2    (1 << 7)           /*!< Mask for COMUSB2 availability */
#define PERIPHERAL_MASK_COMH1    PERIPHERAL_MASK_COMH
#define PERIPHERAL_MASK_COMUSB1  PERIPHERAL_MASK_COMH1
#define PERIPHERAL_MASK_COMUSB2  PERIPHERAL_MASK_COMH2

/*! @brief Define the base list request / response structure (DBLUETOOTH_FIOCTL_GET_BASE_LIST_FOR_PERIPHERAL_MASK fioctl) */
typedef struct {
    union {
        unsigned int peripheral_mask;  	/*!< request : peripheral_mask */
        unsigned int number_of_base; 		/*!< response : number of bases matching such a peripheral_mask */
    } cmd;
    unsigned int base_list[MAXIMUM_NUMBER_OF_BASES];//!< serial number of bases matching such a peripheral_mask
} dbluetooth_base_list_for_peripheral_s;


/*
 * Service Discovery Protocol
 */

#define DBLUETOOTH_FIOCTL_SEARCH_START                (DBLUETOOTH_FIOCTL_EXTERNAL + 0x120) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_SEARCH_CANCEL               (DBLUETOOTH_FIOCTL_EXTERNAL + 0x121) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_SEARCH_RESULT               (DBLUETOOTH_FIOCTL_EXTERNAL + 0x122) /*!< Internal use only */

typedef struct {
	unsigned int classOfDevice;
	unsigned int classOfDeviceMask;
	unsigned short signalNumber;
	unsigned short taskNumber;
} dbluetooth_search_request_s;

#define MAX_RESULT_NAME_LENGTH (30)

typedef struct {
    dbluetooth_device_addr_s address; // BT @
    unsigned int             cod;     // Class Of Device
    unsigned char            rssi;    //
    char                     name[MAX_RESULT_NAME_LENGTH + 1];
} dbluetooth_search_result_s;

#define MAX_SEARCH_RESULT (32)

typedef struct {
	int number_of_result;
	dbluetooth_search_result_s results[MAX_SEARCH_RESULT];
} dbluetooth_search_results_s;


/*
 * Wiimote interface
 */

#define DBLUETOOTH_WIIMOTE_CLASS_OF_DEVICE            (0x00002504)

#define DBLUETOOTH_FIOCTL_WIIMOTE_CONNECT             (DBLUETOOTH_FIOCTL_EXTERNAL + 0x130) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_WIIMOTE_DISCONNECT          (DBLUETOOTH_FIOCTL_EXTERNAL + 0x131) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_WIIMOTE_CALIBRATION         (DBLUETOOTH_FIOCTL_EXTERNAL + 0x132) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_WIIMOTE_SET_LEDS            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x133) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_WIIMOTE_START_REPORT        (DBLUETOOTH_FIOCTL_EXTERNAL + 0x134) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_WIIMOTE_STOP_REPORT         (DBLUETOOTH_FIOCTL_EXTERNAL + 0x135) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_WIIMOTE_START_LOG           (DBLUETOOTH_FIOCTL_EXTERNAL + 0x136) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_WIIMOTE_STOP_LOG            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x137) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_WIIMOTE_GET_INFO            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x138) /*!< Internal use only */

typedef struct {
    dbluetooth_device_addr_s wiimote_address;
    unsigned short task_number;
    unsigned short event_number;
} wiimote_connect_req_s;

typedef struct {
    char filename[20];
    unsigned int log_mask;
} wiimote_log_req_s;

#define DBLUETOOTH_WIIMOTE_INFO_FLAG_CONNECTED  (0x01)
#define DBLUETOOTH_WIIMOTE_INFO_FLAG_ACCEL_ON   (0x02)
#define DBLUETOOTH_WIIMOTE_INFO_FLAG_ACCEL_CAL  (0x04)
#define DBLUETOOTH_WIIMOTE_INFO_FLAG_CONTINUOUS (0x08)
#define DBLUETOOTH_WIIMOTE_INFO_FLAG_RECORDING  (0x10)



#define WIIMOTE_BUTTON_TWO   (0)
#define WIIMOTE_BUTTON_ONE   (1)
#define WIIMOTE_BUTTON_B     (2)
#define WIIMOTE_BUTTON_A     (3)
#define WIIMOTE_BUTTON_MINUS (4)
#define WIIMOTE_BUTTON_HOME  (7)

#define WIIMOTE_BUTTON_LEFT  (8)
#define WIIMOTE_BUTTON_RIGHT (9)
#define WIIMOTE_BUTTON_DOWN  (10)
#define WIIMOTE_BUTTON_UP    (11)
#define WIIMOTE_BUTTON_PLUS  (12)
#define WIIMOTE_BUTTON_MAX   (12)

#define WIIMOTE_BUTTON_MASK_TWO   (0x0001)
#define WIIMOTE_BUTTON_MASK_ONE   (0x0002)
#define WIIMOTE_BUTTON_MASK_B     (0x0004)
#define WIIMOTE_BUTTON_MASK_A     (0x0008)
#define WIIMOTE_BUTTON_MASK_MINUS (0x0010)
#define WIIMOTE_BUTTON_MASK_HOME  (0x0080)

#define WIIMOTE_BUTTON_MASK_LEFT  (0x0100)
#define WIIMOTE_BUTTON_MASK_RIGHT (0x0200)
#define WIIMOTE_BUTTON_MASK_DOWN  (0x0400)
#define WIIMOTE_BUTTON_MASK_UP    (0x0800)
#define WIIMOTE_BUTTON_MASK_PLUS  (0x1000)
#define WIIMOTE_BUTTON_MASK_MAX   (0x1000)

#ifdef _GSIM_
typedef struct {
    unsigned int flag_timestamp;
} key_event_s;
#else
typedef struct {
    unsigned int flag:8, timestamp:24;
} key_event_s;
#endif

typedef struct {
    dbluetooth_device_addr_s addr;
    unsigned char  flags;               // @see DBLUETOOTH_WIIMOTE_INFO_FLAG_XXX
    unsigned char  deviceId;            // as returned by CONNECT_IND (used to Disconnect())
    // Button related infos
    unsigned short button_mask;         // @see WIIMOTE_BUTTON_MASK_XXX
    key_event_s    last_pressed[16];    // stored by their number, cleared on wiimote_get_info() @see WIIMOTE_BUTTON_XXX
    key_event_s    last_released[16];   // stored by their number, cleared on wiimote_get_info() @see WIIMOTE_BUTTON_XXX
    // Accelerometer related infos
    unsigned short acc_x, acc_x_zero, acc_x_gain;
    unsigned short acc_y, acc_y_zero, acc_y_gain;
    unsigned short acc_z, acc_z_zero, acc_z_gain;
    
    unsigned short pad;
} dbluetooth_wiimote_info_s;

#define DBLUETOOTH_FIOCTL_SPP0_GET_BT_ADDRESS            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x140) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_SPP0_SET_BT_ADDRESS            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x141) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_SPP0_SET_PINCODE               (DBLUETOOTH_FIOCTL_EXTERNAL + 0x142) /*!< Internal use only */

#define DBLUETOOTH_FIOCTL_SYS_FIOCTL_USB_DEVICE_SERIAL_NUMBER_ENABLE (DBLUETOOTH_FIOCTL_EXTERNAL + 0x150) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_USBDEV_FIOCTL_SET_MODE                     (DBLUETOOTH_FIOCTL_EXTERNAL + 0x151) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_OEMC_DEVICES_RENAME                        (DBLUETOOTH_FIOCTL_EXTERNAL + 0x152) /*!< Internal use only */

typedef struct {
	unsigned short public_port; // Ethernet side of base
	unsigned short private_port; // Handheld side
} dbluetooth_tcp_port_redirect_s;

#define DBLUETOOTH_TCP_PORT_REDIRECT_MAX (4)

#define DBLUETOOTH_FIOCTL_INCOMING_TCP_START_FORWARD           (DBLUETOOTH_FIOCTL_EXTERNAL + 0x153) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_INCOMING_TCP_STOP_FORWARD            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x154) /*!< Internal use only */

#define DBLUETOOTH_FIOCTL_INCOMING_TCP_FORWARD_OK (0)  /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_INCOMING_TCP_FORWARD_KO (-1) /*!< Internal use only */

#define DBLUETOOTH_FIOCTL_INCOMING_TCP_FORWARD_ALREADY_REGISTERED_BY_SAME_APPLICATION   (-2) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_INCOMING_TCP_FORWARD_ALREADY_REGISTERED_BY_OTHER_APPLICATION  (-3) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_INCOMING_TCP_FORWARD_NOT_REGISTERED                           (-4) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_INCOMING_TCP_FORWARD_REGISTERED_BY_OTHER_APPLICATION          (-5) /*!< Internal use only */

/*! @} **/
#endif   //__DBLUETOOTH_H_INCLUDED__

