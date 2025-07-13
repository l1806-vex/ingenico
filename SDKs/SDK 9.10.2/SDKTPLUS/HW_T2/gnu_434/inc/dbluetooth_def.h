#ifdef __cplusplus
extern "C" {
#endif

#ifndef __DBLUETOOTH_DEF_H_INCLUDED__
#define __DBLUETOOTH_DEF_H_INCLUDED__

/*! @addtogroup KSFAM_BLUE_TOOTH
 * @{
 * @section Description_BT1 Documentation
 *
 * Introduction to Bluetooth handheld and cradle interoperability.
 *
 * First, let's see the different cradles available.
 *
 * EFT930 family:
 * - 930P : multiplexed MODEM and COM0 going through one single Infra Red link (so simultaneous access is NOT possible)
 * - 930PEM : with a Thunder embedded, can to simultaneous MODEM, COM0 and even Ethernet through the single IR link
 * - 930BEM : with a Thunder embedded, plus Bluetooth, can do simultaneous MODEM, COM0 and Ethernet through both IR and Bluetooth link
 * - other cradles exist, with different options (MODEM / COM1 / Ethernet) but they work the same way
 *
 * iWL family:
 * - MODEM cradle : two serial links, a MODEM and a USB Host, all accessible simultaneously ; this will be called P cradle to be consistent with 930 family
 * - Ethernet cradle (with a Thunder 2 embedded), either Bluetooth or not, with two serial links, MODEM, USB Device, USB Host limited to CDC and Ethernet ; they will be called BEM and PEM to be consistent with 930 family.
 * As far as COM0, COM1 and MODEM are concerned, the connectors and functionnalities are the same for P and B cradle.
 * With the power supply jack connector at the top, the lowest connector is COM0, the one just above is COM1 and the one above COM1 is MODEM.
 * For the USB Host connector, while it's physically the same, only CDC class is supported on B cradle (and seen as "COMH" from the handheld).
 *
 * As far as handhelds are concerned, they are Bluetooth-enabled ones (further referenced as 'B') and the others (further referenced as 'P').
 *
 * P handheld can work on either P, PEM or BEM cradle, but only through physical link (either IR (on EFT930) or USB (on iWL)).
 * B handheld can work on either P, PEM or BEM cradle, only through physical link for P and PEM, and through Bluetooth for BEM.
 *
 * So every handheld can work on every cradle, with the limitation that Bluetooth can, of course, only be used between a B handheld and a B cradle.
 * Nonetheless, this requires proper configuration of advanced options on the handheld side.
 *
 * On EFT930 those options were IS_IR and FORCE_IR, respectively meaning run on P cradle and run on either PEM or BEM but through IR only.
 * On iWL these options are now IS_CDC and FORCE_USB but keep the same semantic(except IR physical link has been replaced with USB).
 * For peripherals available both on B and P cradle, both IS_IR / IS_CDC and FORCE_IR / FORCE_USB options are available.
 * For peripherals only available on PEM / BEM cradle, only FORCE_IR / FORCE_USB option is available.
 *
 * Let's take a look at which peripherals are seen from the handheld:
 *
 * - COM0  : the lowest RJ11 connector of the cradle
 * - COM1  : the RJ11 connector just above COM0
 * - MODEM : the RJ11 connecter just above COM1
 * - COMU  : the USB Device connector of the cradle, equivalent to the COM5, but on the cradle
 * - COMH  : the USB Host connector of the cradle, limited to CDC class, so equivalent to COM6, but on the cradle
 * - COMN  : hidden to the application, but related to Ethernet connector
 *
 * So on EFT930, the following options exist:
 * - COM0.IS_IR, COM0.FORCE_IR
 * - COM1.FORCE_IR
 * - MODEM.IS_IR, MODEM.FORCE_IR
 * - COMU.FORCE_IR
 * - COMH.FORCE_IR
 * - COMN.FORCE_IR
 *
 * And, on iWL, the following options are available:
 * - COM0.IS_CDC, COM0.FORCE_USB
 * - COM1.IS_CDC, COM1.FORCE_USB
 * - MODEM.IS_CDC, MODEM.FORCE_USB
 * - COMU.FORCE_USB
 * - COMH.FORCE_USB
 * - COMN.FORCE_USB
 *
 * The following table shows, for EFT930 as well as for iWL, how to set the options for the different possible configurations. XXX is meant to be replaced by the desired peripheral (COM0, COM1 and so on).
 * The option mnemonic are simply linked to the name of the fioctl to call : for example, to set the COM0.IS_IR option, use the DBLUETOOTH_FIOCTL_SET_COM0_IS_IR fioctl().
 *
 * @image html HH_CRADLE_INTEROPERABILITY.JPG "Handheld / Cradle interoperability options"
 *
 * Important notices :
 *
 * - IS_CDC / IS_IR options require a terminal restart to be taken into account
 * - FORCE_IR / FORCE_CDC are taken into account at the next fopen() of the device (COM0 / COM1 / ...)
 * - no automatic switch from IR/USB to Bluetooth are made on docking / undocking of handheld
 * - on B handheld, IS_CDC / IS_IR options are OFF by default (we want to talk to a BEM/PEM cradle)
 * - on P handheld, IS_CDC / IS_IR options are ON by default (we want to work on a P cradle)
 * - when associating a P handheld with a BEM/PEM cradle, IS_CDC / IS_IR are switched to OFF, which requires a restart (before association on EFT930, after association on iWL).
 * - you CANNOT use a cradle both through IR/USB and Bluetooth at the same time : information obtained through IR/USB about peripheral availability is not correct.
 *   For example, you cannot know through IR/USB if the MODEM is already in use by a handheld connected through Bluetooth.
 *   It is working this way because you cannot dock more than one handheld onto a cradle, so having the information through IR/USB is pointless.
 *
 *
 * Important information on the impact of using Bluetooth-provided device on standby policy :
 *
 * If a device is provided through the Bluetooth driver (that is none of the IS_IR / IS_CDC option is ON for this device), as soon as fopen() returns, the driver declares a permanent activity to prevent the handheld from going to sleep mode.
 * This remains so until the fclose() for the previously fopen()'d device is called. Whereafter the standard standby policy applies, and the device goes to sleep mode after the usual standby timeout.
 * This is also true is going through IR ou USB (FORCE_IR or FORCE_USB option is ON), but as the handheld is supposed to be docked at that time, it doesn't make any difference.
 * This no-sleep-mode policy applies for the following Telium devices :
 *   - COM0
 *   - COM1
 *   - MODEM
 *   - COMU
 *   - COMH
 *
 * As COMN is internally used and managed by the driver, it has no impact on the standby policy.
 *
 *
 *
 * @section Description_BT2  Samples
 * The sample of code below shows how to use API OPEN_BT (new peripheral on recent Bluetooth devices)
 * @include dbluetooth_Sample_01.c
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
#define DBLUETOOTH_FIOCTL_GET_COM0_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0x12)		/*!< Is COM0 configured to work on a plain P base (not a smart one) ? */
#define DBLUETOOTH_FIOCTL_SET_COM0_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0x13)		/*!< Set COM0 to work on plain P base, or not (restart required to be taken into account) */
#define DBLUETOOTH_FIOCTL_GET_COM0_FORCE_USB (DBLUETOOTH_FIOCTL_EXTERNAL + 0x14)		/*!< Is COM0 configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_COM0_FORCE_USB (DBLUETOOTH_FIOCTL_EXTERNAL + 0x15)		/*!< Set COM0 to work on InfraRed only or not */
#define DBLUETOOTH_FIOCTL_GET_COM0_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x16)		/*!< Get the serial number (ie address) of the base providing COM0 */
#define DBLUETOOTH_FIOCTL_SET_COM0_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x17)		/*!< Set the serial number (ie address) of the base providing COM0 */
#define DBLUETOOTH_FIOCTL_DOES_COM0_NEED_BASE (DBLUETOOTH_FIOCTL_EXTERNAL + 0x18)		/*!< Deprecated */

// Values for the above fioctl()
#define DBLUETOOTH_FIOCTL_COM0_DONT_NEED_BASE (1)		/*!< Deprecated */
#define DBLUETOOTH_FIOCTL_COM0_NEED_BASE      (0)		/*!< Deprecated */

// COM1
#define DBLUETOOTH_FIOCTL_SET_COM1_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x23)		/*!< Set COM1 to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_GET_COM1_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x24)		/*!< Get the serial number (ie address) of the base providing COM1 */

// COMN
#define DBLUETOOTH_FIOCTL_GET_COMN_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x30)		/*!< Is COMN configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_COMN_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x31)		/*!< Set COMN to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_GET_COMN_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x32)		/*!< Get the serial number (ie address) of the base providing Ethernet (COMN) */

#define DBLUETOOTH_FIOCTL_ETHERNET_CONNECTION_PROGRESS \
                                             (DBLUETOOTH_FIOCTL_EXTERNAL + 0x34)		/*!< Get progress for the PPP connection between portable and base (Ethernet base only) */
#define DBLUETOOTH_FIOCTL_ETHERNET_GET_INTERNET_INFO \
                                             (DBLUETOOTH_FIOCTL_EXTERNAL + 0x35)		/*!< Equivalent to SYS_FIOCTL_GET_ETHERNET_INFO but for the base */
#define DBLUETOOTH_FIOCTL_ETHERNET_GET_PPP_HANDLE \
                                             (DBLUETOOTH_FIOCTL_EXTERNAL + 0x36)		/*!< Internal use only */

// MODEM
#define DBLUETOOTH_FIOCTL_GET_MODEM_IS_IR    (DBLUETOOTH_FIOCTL_EXTERNAL + 0x42)		/*!< Is MODEM configured to work on a plain P base (not a smart one) ? */
#define DBLUETOOTH_FIOCTL_SET_MODEM_IS_IR    (DBLUETOOTH_FIOCTL_EXTERNAL + 0x43)		/*!< Set MODEM to work on plain P base, or not (restart required to be taken into account) */
#define DBLUETOOTH_FIOCTL_SET_MODEM_FORCE_IR (DBLUETOOTH_FIOCTL_EXTERNAL + 0x45)		/*!< Set MODEM to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_GET_MODEM_ADDRESS  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x46)		/*!< Get the serial number (ie address) of the base providing MODEM */

#define DBLUETOOTH_FIOCTL_SET_PRE_AMP_LEVEL      (DBLUETOOTH_FIOCTL_EXTERNAL + 0x50)		/*!< Internal use only */
#define DBLUETOOTH_FIOCTL_GET_BASE_PRE_AMP_LEVEL (DBLUETOOTH_FIOCTL_EXTERNAL + 0x51)		/*!< Internal use only */
#define DBLUETOOTH_FIOCTL_SET_BASE_PRE_AMP_LEVEL (DBLUETOOTH_FIOCTL_EXTERNAL + 0x52)		/*!< Internal use only */

#ifndef SYS_FIOCTL_GET_ETHERNET_INFO
#define SYS_FIOCTL_GET_ETHERNET_INFO  0x802D		/*!< Internal use only */
#endif

#define DBLUETOOTH_FIOCTL_GET_BASE_USERS (DBLUETOOTH_FIOCTL_EXTERNAL + 0x70)		/*!< Obtain the list of peripherals that are available / used in a base we're connected to*/
                                     
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
#define DBLUETOOTH_FIOCTL_SET_COMU_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x93)		/*!< Set COMU to work on InfraRed only or not */

// COMH (930 BC06) / COMUSB1 (iWL)
#define DBLUETOOTH_FIOCTL_SET_COMH_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0xA3)		/*!< Set COMH (930) / COMUSB1 (iWL)  to work on InfraRed(930)/USB(iWL) only or not */

#define OPEN_BT_VISIBILITY_VISIBLE   (1)		/*!< OpenBT : portable device becomes visible to Bluetooth scan request */
#define OPEN_BT_VISIBILITY_INVISIBLE (0)		/*!< OpenBT : portable device becomes invisible to Bluetooth scan request (default behaviour) */

#define DBLUETOOTH_FIOCTL_OPEN_BT_SET_VISIBILITY \
											 (DBLUETOOTH_FIOCTL_EXTERNAL + 0x101)		/*!< Set visibility state regarding Bluetooth scan */
#define DBLUETOOTH_FIOCTL_OPEN_BT_SET_NAME   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x103)		/*!< Set the name for the OpenBT Bluetooth link */

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

/*! @brief  Define the address of the bluetooth device. (total size 2 * 4)  */
typedef struct {
    unsigned int  nap:16,							/*!< Non significant Address Part 32..47 */
                  uap:8;							/*!< uap:8 : Upper Address Part 24..31 */
    unsigned int  lap;								/*!< lap : Lower Address part 00..23 */
} dbluetooth_device_addr_s; // total size 2 * 4

typedef void (*generic_callback_t)(void * /* param */, unsigned int /* type */, const unsigned char * /* data */, unsigned int /* data_len */); //!< Internal use only 
typedef int (*pass_key_callback_t)(dbluetooth_device_addr_s * /* Remote Address */, char *pass_key /* Result : PIN */); /* @return 0 if PIN found, < 0 else */ //!< Internal use only 
typedef unsigned char uuid128_t[16];

/*! @brief Define the parameters of connection for the bluetooth.  */
typedef struct {
    int                      mux_id;					/*!< which SPP to use. */
    dbluetooth_device_addr_s addr;						/*!< address of remote host to connect to. (used by connect() only). */
    generic_callback_t       callback;				/*!< function to call to inform user. */
    void                    *callback_param;	/*!< user parameter passed back as first parameter to the callback function. */
    const char              *name;						/*!< name of SPP (used in listen only). */
    uuid128_t				uuid;						/*!< UUID of remote RFCOMM server to connect to. (used by connect() only). */
	char					useuuid;					/*!< Choose SPP connect or specific RFCOMM Connect */
} dbluetooth_connection_param_s;

/*! @brief Define the sent parameters of the bluetooth.  */
typedef struct {
    int                  mux_id;					/*!< which SPP  */
    const unsigned char *data;						/*!< pointer to start of data  */
    unsigned int         data_len;				/*!< data length  */
} dbluetooth_send_param_s;

#define DBLUETOOTH_SPP_INFO_MAX_NAME_SIZE (7)					/*!< Max size for the name of an SPP instance */
#define DBLUETOOTH_SPP_INFO_MAX_BASE_NAME_SIZE (15)		/*!< Max size for the clear name of a base */

/*! @brief Define the SPP information. */
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
typedef struct {
    dbluetooth_device_addr_s local_address;						       /*!< BlueTooth address of the embedded device  */
    void                    *com2_file;							         /*!< pointer on a file */
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
    void                    *com2_file;							        /*!< pointer on a file */
    int                      status;							        	/*!< current status of the instance, see DBLUETOOTH_STATE_ xxx */
    int                      dut_status;						        /*!< status of the last Device Under Test Confirm */
    int                      dut_step;							        /*!< step number of the last Device Under Test Confirm */ 
    dbluetooth_spp_info_s    spp_info[DBLUETOOTH_SPP_NUMBER_HCI];       /*!< informations on each SPP instance */
    unsigned int             round_trip_lst[DBLUETOOTH_SPP_NUMBER_HCI]; /*!< time, in ticks (10 ms) of the round trip of the last service package between the portable and the base for the selected channel. */
    unsigned int             round_trip_avg[DBLUETOOTH_SPP_NUMBER_HCI]; /*!< average of the 10 last round trip. */
    unsigned int             time_since_req[DBLUETOOTH_SPP_NUMBER_HCI]; /*!< time, in seconds, since the transmission of the last service framework (usually 0). */
    int                      unused[DBLUETOOTH_SPP_NUMBER_HCI];           /*!< unused */
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
// Added for SPP1
#define DBLUETOOTH_SPP_INFO_INDEX_SPP1     (DBLUETOOTH_SPP_SOCLE_4)		/*!< Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */
// Added for SPP2
#define DBLUETOOTH_SPP_INFO_INDEX_SPP2     (DBLUETOOTH_SPP_SOCLE_3)		/*!< Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */
// Added for SPP3
#define DBLUETOOTH_SPP_INFO_INDEX_SPP3     (DBLUETOOTH_SPP_SOCLE_2)		/*!< Index in spp_info and for the DBLUETOOTH_FIOCTL_GET_BASE_USERS fioctl() */
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

typedef struct {
    unsigned int flag:8, timestamp:24;
} key_event_s;

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

#define DBLUETOOTH_FIOCTL_SPP1_GET_BT_ADDRESS            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x143) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_SPP1_SET_BT_ADDRESS            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x144) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_SPP1_SET_PINCODE               (DBLUETOOTH_FIOCTL_EXTERNAL + 0x145) /*!< Internal use only */

#define DBLUETOOTH_FIOCTL_SPP2_GET_BT_ADDRESS            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x146) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_SPP2_SET_BT_ADDRESS            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x147) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_SPP2_SET_PINCODE               (DBLUETOOTH_FIOCTL_EXTERNAL + 0x148) /*!< Internal use only */

#define DBLUETOOTH_FIOCTL_SPP3_GET_BT_ADDRESS            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x149) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_SPP3_SET_BT_ADDRESS            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x14A) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_SPP3_SET_PINCODE               (DBLUETOOTH_FIOCTL_EXTERNAL + 0x14B) /*!< Internal use only */
typedef struct {
	int currentRole;
	int nextRole;
	int ioctl_get_bt_address;
	int ioctl_set_bt_address;
	int ioctl_set_pincode;
	int spp_info_index;
	char name[8];
} dbluetooth_get_spp_s;

typedef enum {
SPP_ROLE_FREE=0,
SPP_ROLE_GENERIC,
SPP_ROLE_PRINTER_EXT,
SPP_ROLE_BARCODE,
SPP_ROLE_APPLE_SPP,
SPP_ROLE_APPLE_IAP_BT,
SPP_ROLE_BASE = 1024,
SPP_ROLE_OPEN_BT
}spp_role_t;

typedef struct {
	int spp_info_index; /*!< which SPP to use. info retrieved by DBLUETOOTH_FIOCTL_GET_SPP */
	char useuuid;		/*!< perform SPP connection or private RFCOMM connection */
	uuid128_t uuid;		/*!< if we perform private RFCOMM connection describe RFCOMM server to use*/
} dbluetooth_set_spp_uuid_s;

#define DBLUETOOTH_FIOCTL_SPP_SET_UUID					 (DBLUETOOTH_FIOCTL_EXTERNAL + 0x170) /*!<  If remote device is not using SPP but a private UUID, we can ask to coonect to remote device anyway*/

#define DBLUETOOTH_FIOCTL_GET_SPP			            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x14F) /*!< Internal use only */

#define DBLUETOOTH_FIOCTL_SYS_FIOCTL_USB_DEVICE_SERIAL_NUMBER_ENABLE (DBLUETOOTH_FIOCTL_EXTERNAL + 0x150) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_USBDEV_FIOCTL_SET_MODE                     (DBLUETOOTH_FIOCTL_EXTERNAL + 0x151) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_OEMC_DEVICES_RENAME                        (DBLUETOOTH_FIOCTL_EXTERNAL + 0x152) /*!< Internal use only */

typedef struct {
	short public_port;  // Ethernet side of base
	short private_port; // Handheld side
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
#define DBLUETOOTH_FIOCTL_INCOMING_TCP_FORWARD_TOO_MANY_REDIRECTION                     (-6) /*!< Internal use only */

#define DBLUETOOTH_FIOCTL_AV0_GET_BT_ADDRESS              (DBLUETOOTH_FIOCTL_EXTERNAL + 0x160) /*!< get BT address of streaming device */
#define DBLUETOOTH_FIOCTL_AV0_SET_BT_ADDRESS              (DBLUETOOTH_FIOCTL_EXTERNAL + 0x161) /*!< set BT address of streaming device */
#define DBLUETOOTH_FIOCTL_AV0_SET_PINCODE                 (DBLUETOOTH_FIOCTL_EXTERNAL + 0x162) /*!< change pincode of streaming connection */
#define DBLUETOOTH_FIOCTL_AV0_CONFIGURE                   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x163) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_AV0_START                       (DBLUETOOTH_FIOCTL_EXTERNAL + 0x164) /*!< Start streaming service (either in server mode or client mode) */
#define DBLUETOOTH_FIOCTL_AV0_STOP                        (DBLUETOOTH_FIOCTL_EXTERNAL + 0x165) /*!< Stop streaming service */
#define DBLUETOOTH_FIOCTL_AV0_GET_PT_SEND_DATA            (DBLUETOOTH_FIOCTL_EXTERNAL + 0x166) /*!< Internal use only */
#define DBLUETOOTH_FIOCTL_AV0_GET_STATE                   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x167) /*!< get State of streaming service */
typedef struct {
    unsigned int  flag; /*!< Change streaming service behaviour : LISTEN / CONNECT*/
    unsigned int  evtMask; /*!< specify wich event are notified to application*/
    unsigned int  evt;     /*!< change event generated by driver*/
} dbluetooth_av_start_s;

typedef struct {
    unsigned int  action; /**/
    int*  param;
} dbluetooth_av_configure_s;
#define DaAvStateAvDisconnected			0x00 /*!< State of streaming service : Not connected*/
#define DaAvStateAvConnecting			0x01 /*!< State of streaming service : lowlevel connection in progress */
#define DaAvStateAvConnected			0x02 /*!< State of streaming service : lowlevel connection established */
#define DaAvStateAvConnectedOpen		0x03 /*!< State of streaming service : datalevel connection established but not streaming */
#define DaAvStateAvConnectedStreaming	0x04 /*!< State of streaming service : Streaming */
#define DaAvStateAvDisconnecting		0x05 /*!< State of streaming service : disconnectin in progress */

#define BT_AV0_DISABLED                     0 /*!< streaming service behaviour :  REJECT ALL remote device*/
#define BT_AV0_LISTEN                       1 /*!< streaming service behaviour :  wait for incoming connection*/
#define BT_AV0_CONNECT                      2 /*!< streaming service behaviour :  CONNECT to remote device*/
#define BT_AV0_FIRST_CONNECT                4 /*!< streaming service behaviour :  one CONNECT to remote device*/

#define BT_AV0_EVTMASK_CONNECTION           1 /*!< streaming event :  connection of new device*/
#define BT_AV0_EVTMASK_DISCONNECTION        2 /*!< streaming event :  disconnection of remote device*/
#define BT_AV0_EVTMASK_SUSPEND				4 /*!< streaming event :  stream suspended but device still connected */

#define OBTAV_CONFIGURE_CODEC_CONFIG 1 /*!< Internal use only */
#define OBTAV_CONFIGURE_GET_BUFFERISED 2 /*!< Internal use only */
#define OBTAV_CONFIGURE_SET_BUFFERISED 3 /*!< Internal use only */
#define OBTAV_CONFIGURE_CLEAN        4 /*!< Internal use only */
#define OBTAV_CONFIGURE_SUSPEND      5 /*!< Internal use only */

//Pairing state
#define PAIRING_NO_BONDING_IN_PROGRESS        0
#define PAIRING_BONDING_IN_PROGRESS           1
#define PAIRING_BONDING_REQUESTED             2
#define PAIRING_BONDING_WAIT_RESULT           3
#define PAIRING_BONDING_SUCCESSED             4
#define PAIRING_BONDING_FAILLED               5

//Bonding type
#define PAIRING_TYPE_PASSKEY                  0x8000   // == SC_PASSKEY_IND  
#define PAIRING_TYPE_COMPARE                  0x800D   // == SC_SSP_COMPARE_IND

/*! @} **/


#endif   //__DBLUETOOTH_DEF_H_INCLUDED__

#ifdef __cplusplus
}
#endif
