#ifndef __DBLUETOOTH_DEPRECATED_H_INCLUDED__
#define __DBLUETOOTH_DEPRECATED_H_INCLUDED__


#ifdef _DEPRECATED_DBLUETOOTH_SDK091000_

// Power control
#define DBLUETOOTH_FIOCTL_POWER           (DBLUETOOTH_FIOCTL_EXTERNAL + 0x0E)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						 @brief Request change in the power state of the Bluetooth device */

#define DBLUETOOTH_POWER_OFF (0)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
											 @brief parameter value for DBLUETOOTH_FIOCTL_POWER fioctl to shut Bluetooth device power down */
#define DBLUETOOTH_POWER_ON  (1)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
											 @brief paramater value for DBLUETOOTH_FIOCTL_POWER fioctl to power Bluetooth device up */

#define DBLUETOOTH_FIOCTL_LEARN_ISMP_CRADLE (DBLUETOOTH_FIOCTL_EXTERNAL + 0x0F)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						 @brief Request association with an iSMP base, only its BT_address is known */

// COM1
#define DBLUETOOTH_FIOCTL_GET_COM1_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0x20)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is COM1 configured to work through USB CDC ? */
#define DBLUETOOTH_FIOCTL_SET_COM1_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0x21)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set COM1 to work through USB CDC, or not (restart required to be taken into account) */
#define DBLUETOOTH_FIOCTL_GET_COM1_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x22)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is COM1 configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_GET_COM1_FORCE_USB (DBLUETOOTH_FIOCTL_EXTERNAL + 0x22)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is COM1 configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_COM1_FORCE_USB (DBLUETOOTH_FIOCTL_EXTERNAL + 0x23)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set COM1 to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_SET_COM1_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x25)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set the serial number (ie address) of the base providing COM1 */

// COMN
#define DBLUETOOTH_FIOCTL_GET_COMN_FORCE_USB (DBLUETOOTH_FIOCTL_EXTERNAL + 0x30)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is COMN configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_COMN_FORCE_USB (DBLUETOOTH_FIOCTL_EXTERNAL + 0x31)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set COMN to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_SET_COMN_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x33)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set the serial number (ie address) of the base providing Ethernet (COMN) */

// MODEM
#define DBLUETOOTH_FIOCTL_GET_MODEM_FORCE_IR (DBLUETOOTH_FIOCTL_EXTERNAL + 0x44)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is MODEM configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_GET_MODEM_IS_CDC   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x42)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is MODEM configured to work on a plain P base (not a smart one) ? */
#define DBLUETOOTH_FIOCTL_SET_MODEM_IS_CDC   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x43)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set MODEM to work on plain P base, or not (restart required to be taken into account) */
#define DBLUETOOTH_FIOCTL_GET_MODEM_FORCE_USB (DBLUETOOTH_FIOCTL_EXTERNAL + 0x44)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is MODEM configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_MODEM_FORCE_USB (DBLUETOOTH_FIOCTL_EXTERNAL + 0x45)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set MODEM to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_SET_MODEM_ADDRESS  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x47)		/*!< Set the serial number (ie address) of the base providing MODEM */

// BASE
#define DBLUETOOTH_FIOCTL_RESET_BASE (DBLUETOOTH_FIOCTL_EXTERNAL + 0x60)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																					 @brief Request a base restart */
#define DBLUETOOTH_FIOCTL_RESET_BASE_SECRET      (DBLUETOOTH_FIOCTL_EXTERNAL + 0x53)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						         @brief Request the base to erase its secrets (Bluetooth PIN Code and 3DES key) ; re-association of all portables is required */
#define DBLUETOOTH_FIOCTL_SET_BASE_NAME          (DBLUETOOTH_FIOCTL_EXTERNAL + 0x54)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						         @brief Request to set a clear name for a base different from its initial value (string representing serial number) */
#define DBLUETOOTH_FIOCTL_GET_BASE_NAME          (DBLUETOOTH_FIOCTL_EXTERNAL + 0x55)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						         @brief Request to get the clear name of the base we're sitting on */
#define DBLUETOOTH_FIOCTL_GET_BASE_INFOS         (DBLUETOOTH_FIOCTL_EXTERNAL + 0x56)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						         @brief Request to get infos about the cradle we are docked on ; parameter is pointeur to inter_uc_sp_options_public_base_s */
#define DBLUETOOTH_FIOCTL_GET_BASE_LIST_FOR_PERIPHERAL_MASK \
                                         (DBLUETOOTH_FIOCTL_EXTERNAL + 0x71)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						 @brief Get a list of base serial number having the required peripheral(s) @see definition of dbluetooth_base_list_for_peripheral_s struct */
#define DBLUETOOTH_FIOCTL_GET_BASE_PERIPHERAL_MASK_FROM_TYPE \
                                         (DBLUETOOTH_FIOCTL_EXTERNAL + 0x72)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						 @brief Get the mask of available peripheral(s) from the base kind */
#define DBLUETOOTH_FIOCTL_GET_BASE_USERS_EX (DBLUETOOTH_FIOCTL_EXTERNAL + 0x73)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						 @brief Obtain the list of peripherals that are available / used in a base we're connected to, plus the user of each PPP connection between portable and base */

// COMU
#define DBLUETOOTH_FIOCTL_GET_COMU_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0x92)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is COMU configured to use only InfraRed link ? */
#define DBLUETOOTH_FIOCTL_GET_COMU_FORCE_USB (DBLUETOOTH_FIOCTL_EXTERNAL + 0x92)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is COMU configured to use only USB link ? */
#define DBLUETOOTH_FIOCTL_SET_COMU_FORCE_USB (DBLUETOOTH_FIOCTL_EXTERNAL + 0x93)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set COMU to work on USB only or not */
#define DBLUETOOTH_FIOCTL_GET_COMU_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x94)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Get the serial number (ie address) of the base providing COMU */
#define DBLUETOOTH_FIOCTL_SET_COMU_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x95)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set the serial number (ie address) of the base providing COMU */

// COMH (930 BC06)
#define DBLUETOOTH_FIOCTL_GET_COMH_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0xA0)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is COMH (930) / COMUSB1 (iWL)  configured to work through USB CDC ? */
#define DBLUETOOTH_FIOCTL_SET_COMH_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0xA1)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set COMH (930) / COMUSB1 (iWL)  to work through USB CDC, or not (restart required to be taken into account) */
#define DBLUETOOTH_FIOCTL_GET_COMH_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0xA2)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is COMH (930) / COMUSB1 (iWL)  configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_GET_COMH_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0xA4)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Get the serial number (ie address) of the base providing COMH (930) / COMUSB1 (iWL) */
#define DBLUETOOTH_FIOCTL_SET_COMH_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0xA5)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set the serial number (ie address) of the base providing COMH (930) / COMUSB1 (iWL)  */

// COMUSB1 (iWL)
#define DBLUETOOTH_FIOCTL_GET_COMUSB1_IS_CDC   	DBLUETOOTH_FIOCTL_GET_COMH_IS_CDC   	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is COMH (930) / COMUSB1 (iWL)  configured to work through USB CDC ? */
#define DBLUETOOTH_FIOCTL_SET_COMUSB1_IS_CDC   	DBLUETOOTH_FIOCTL_SET_COMH_IS_CDC   	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set COMH (930) / COMUSB1 (iWL)  to work through USB CDC, or not (restart required to be taken into account) */
#define DBLUETOOTH_FIOCTL_GET_COMUSB1_FORCE_IR 	DBLUETOOTH_FIOCTL_GET_COMH_FORCE_IR 	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is COMH (930) / COMUSB1 (iWL)  configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_COMUSB1_FORCE_IR 	DBLUETOOTH_FIOCTL_SET_COMH_FORCE_IR 	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set COMH (930) / COMUSB1 (iWL)  to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_GET_COMUSB1_ADDRESS  	DBLUETOOTH_FIOCTL_GET_COMH_ADDRESS  	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Get the serial number (ie address) of the base providing COMH (930) / COMUSB1 (iWL) */
#define DBLUETOOTH_FIOCTL_SET_COMUSB1_ADDRESS  	DBLUETOOTH_FIOCTL_SET_COMH_ADDRESS  	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set the serial number (ie address) of the base providing COMH (930) / COMUSB1 (iWL)  */

// COMUSB2 (iWL only)
#define DBLUETOOTH_FIOCTL_GET_COMUSB2_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0xB0)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is COMUSB2 configured to work through USB CDC ? */
#define DBLUETOOTH_FIOCTL_SET_COMUSB2_IS_CDC    (DBLUETOOTH_FIOCTL_EXTERNAL + 0xB1)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set COMUSB2 to work through USB CDC, or not (restart required to be taken into account) */
#define DBLUETOOTH_FIOCTL_GET_COMUSB2_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0xB2)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Is COMUSB2 configured to use only InfraRed(930)/USB(iWL) link ? */
#define DBLUETOOTH_FIOCTL_SET_COMUSB2_FORCE_IR  (DBLUETOOTH_FIOCTL_EXTERNAL + 0xB3)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set COMUSB2 to work on InfraRed(930)/USB(iWL) only or not */
#define DBLUETOOTH_FIOCTL_GET_COMUSB2_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0xB4)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Get the serial number (ie address) of the base providing COMUSB2 */
#define DBLUETOOTH_FIOCTL_SET_COMUSB2_ADDRESS   (DBLUETOOTH_FIOCTL_EXTERNAL + 0xB5)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set the serial number (ie address) of the base providing COMUSB2 */

#define DBLUETOOTH_FIOCTL_GET_INFO_BC06      (DBLUETOOTH_FIOCTL_EXTERNAL + 0x100)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Obtain informations for BC06 devices */

// Open BT
#define DBLUETOOTH_FIOCTL_OPEN_BT_SET_PINCODE \
											 (DBLUETOOTH_FIOCTL_EXTERNAL + 0x102)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Set the PIN code for the OpenBT Bluetooth link */
#define DBLUETOOTH_FIOCTL_OPEN_BT_GET_NAME   (DBLUETOOTH_FIOCTL_EXTERNAL + 0x104)		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_DBLUETOOTH_SDK091000_ in your application. 
																						     @brief Get the name for the OpenBT Bluetooth link */


#endif	// _DEPRECATED_DBLUETOOTH_SDK091000_

											 
#endif	// __DBLUETOOTH_DEPRECATED_H_INCLUDED__
