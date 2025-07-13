#ifndef OEM_SYSTEM_DEPRECATED_H
#define OEM_SYSTEM_DEPRECATED_H


#ifdef _DEPRECATED_SYSTEMFIOCTL_SDK091000_


//! \addtogroup SYSFIOTCL_FEATURES
//! @{

#define SYS_FIOCTL_GET_RAM_SIZE                         0x800B		/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK091000_ in your application. 
																				           @brief Get the Total ram size. @param Unsigned int* : 0x800000 = 8MBytes */

//! @}

//! \addtogroup SYSTEMFIOCTL_MISCELLANEOUS
//! @{

#define SYS_FIOCTL_GET_SYS_TIMER_UNIT             							0x806F 	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK091000_ in your application. 
																				                       @brief param : unsigned int, Get system clock counter unit ns */

//! @}

//! \addtogroup SYSFIOCTL_USB
//! @{

#define SYS_FIOCTL_GET_USB_DEV_STRINGS                   0x8114 	//!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK091000_ in your application. 
                                                                  //!< @brief to get the strings (manufacturer, product, serial) of an USB device                                                                            
                                                                  //!< @param SYS_FIOCTL_GET_USB_DEV_STRINGS_S* 
                                                                  //!< @return
                                                                  //!< @li 0 OK
                                                                  //!< @li -1 not implemented
                                                                  //!< @li -2 bad parameter (NULL for ex).
                                                                  //!< @note

// @include oem_sysfioctl_Sample_15.c

                                                                     

//! @}

#endif // _DEPRECATED_SYSTEMFIOCTL_SDK091000_


#ifdef _DEPRECATED_SYSTEMFIOCTL_SDK96_

//! \addtogroup SYSFIOCTL_MISCELLANEOUS
//! @{

#define SYS_FIOCTL_ENABLE_PERIODIC_DATA_SAVING          0x8000         /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief Enable periodic data saving for current application @param NULL*/
#define SYS_FIOCTL_DISABLE_PERIODIC_DATA_SAVING         0x8001         /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief Disable periodic data saving for current application @param NULL */

//! @}


//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

#define SYS_FIOCTL_CLEAR_TERMINAL                       0x8003        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief  Remove all files except SYSTEM, BOOT_RAM and config files 
																		 	@param NULL
																		 	@return 0 OK */
#define SYS_FIOCTL_RENAME_DESCRIPTOR                    0x8004        /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. @brief 2 param. first one Descriptor to be replaced ; second new Descriptor taking place of the first one */

//! @}

//! \addtogroup SYSFIOTCL_IDENT
//! @{

#define SYS_FIOCTL_GET_TERMINAL_TYPE                    0x8005		/*!< @deprecated This fioctl should not be called directly, use IsXXX API instead where XXX is the terminal type, e.g. IsICT220, IsICT250, IsIST150 .... To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																		 @brief Get the terminal typ ID 
																		 @param int * : \ref TERMTYPE_VALUE 
																		 @return 0 : OK */

//! @}

//! \addtogroup SYSFIOTCL_IDENT
//! @{

#define SYS_FIOCTL_GET_PRODUCT_SERIAL_NUMBER            0x8007		/*!< @deprecated This fioctl should not be called directly, use PSQ_Give_Serial_Number API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																		 @brief Short Terminal serial number : 8 last digits
																		 @param Unsigned char[4] :  BCD serial numb 
																		 @return 0 */
//! @}


//! \addtogroup SYSFIOCTL_IS
//! @brief To inform that a feature is available
//! @param NULL
//! @return 
//! \li 0 available
//! \li -1 not available or not implemented.
//!
//! @include oem_sysfioctl_Sample_03.c
//! @{

#define SYS_FIOCTL_IS_BATTERY                           0x800D		/*!< @deprecated This fioctl should not be called directly, use isbattery API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if terminal is battery powered 
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable  */
#define SYS_FIOCTL_IS_MAIN_POWERED                      0x800E		/*!< @deprecated This fioctl should not be called directly, use powered API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if terminal is main powered  
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable  */
#define SYS_FIOCTL_IS_PRINTER                           0x800F		/*!< @deprecated This fioctl should not be called directly, use IsPrinter API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if printer available   
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable  */
#define SYS_FIOCTL_IS_PORTABLE                          0x8010		/*!< @deprecated This fioctl should not be called directly, use IsPortable API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if terminal is portable  
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable  */
#define SYS_FIOCTL_IS_WIRELESS                          0x8011		/*!< @deprecated This fioctl should not be called directly, use IsRadio API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if radio option is available   
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable  */

//! @}

//! \addtogroup SYSFIOTCL_FEATURES
//! @{


#define SYS_FIOCTL_GET_RADIO_TYPE                       0x8012		/*!< @deprecated This fioctl should not be called directly, use IsRadio, IsRadioGPRS IsRadio3G or IsRadioCDMA API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Get the Radio Type @param unsigned int * : \ref TERM_MAIN_RADIO_TYPE */

//! @}


//! \addtogroup SYSFIOCTL_IS
//! @{

#define SYS_FIOCTL_IS_MODEM                             0x8014			/*!< @deprecated This fioctl should not be called directly, use IsMODEM API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief  no parameter : Test if modem is available  */

//! @}

//! \addtogroup SYSFIOCTL_IS
//! @{

#define SYS_FIOCTL_IS_BUZZER                            0x8016			/*!< @deprecated This fioctl should not be called directly, use IsBUZZER API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief  Test if buzzer is available
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable  */
#define SYS_FIOCTL_IS_COM0                              0x8017			/*!< @deprecated This fioctl should not be called directly, use IsCOM0 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if COM0 is available 
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable   */
#define SYS_FIOCTL_IS_COM1                              0x8018			/*!< @deprecated This fioctl should not be called directly, use IsCOM1 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if COM1 is available 
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable   */
#define SYS_FIOCTL_IS_COM2                              0x8019			/*!< @deprecated This fioctl should not be called directly, use IsCOM2 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if COM2 is available 
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable   */
#define SYS_FIOCTL_IS_COM3                              0x801A			/*!< @deprecated This fioctl should not be called directly, use IsCOM3 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if COM3 is available 
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable   */
#define SYS_FIOCTL_IS_USB_DEV                           0x801B			/*!< @deprecated This fioctl should not be called directly, use IsUsbSlave API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if USB Device available
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable */
#define SYS_FIOCTL_IS_USB_HOST                          0x801C			/*!< @deprecated This fioctl should not be called directly, use IsUsbHost API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if USB Host available
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable   */
#define SYS_FIOCTL_IS_ETHERNET                          0x801D			/*!< @deprecated This fioctl should not be called directly, use IsEthernet API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if Ethernet available
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable   */
#define SYS_FIOCTL_IS_MORPHO                            0x801E			/*!< @deprecated This fioctl should not be called directly, use IsBio API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if Morpho device available
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable */
#define SYS_FIOCTL_IS_ISO1                              0x801F			/*!< @deprecated This fioctl should not be called directly, use IsISO1 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if ISO1 reader available
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable */
#define SYS_FIOCTL_IS_ISO2                              0x8020			/*!< @deprecated This fioctl should not be called directly, use IsISO2 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if ISO2 reader available
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable */
#define SYS_FIOCTL_IS_ISO3                              0x8021			/*!< @deprecated This fioctl should not be called directly, use IsISO3 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if ISO3 reader available
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable */
#define SYS_FIOCTL_IS_CAM1                              0x8022			/*!< @deprecated This fioctl should not be called directly, use IsCAM1 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if smart card reader CAM1 available 
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable*/
#define SYS_FIOCTL_IS_CAM2                              0x8023			/*!< @deprecated This fioctl should not be called directly, use IsCAM2 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if smart card reader CAM2 available
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable */
#define SYS_FIOCTL_IS_SAM1                              0x8024			/*!< @deprecated This fioctl should not be called directly, use IsSAM1 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if SAM1 reader available 
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable */
#define SYS_FIOCTL_IS_SAM2                              0x8025			/*!< @deprecated This fioctl should not be called directly, use IsSAM2 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if SAM2 reader available
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable */
#define SYS_FIOCTL_IS_SAM3                              0x8026			/*!< @deprecated This fioctl should not be called directly, use IsSAM3 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if SAM3 reader available 
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable*/
#define SYS_FIOCTL_IS_SAM4                              0x8027			/*!< @deprecated This fioctl should not be called directly, use IsSAM4 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if SAM4 reader available
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable */
#define SYS_FIOCTL_IS_MMC                               0x8028			/*!< @deprecated This fioctl should not be called directly, use IsMMC API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if MMC is available 
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable*/
#define SYS_FIOCTL_IS_TILT                              0x8029			/*!< @deprecated This fioctl should not be called directly, use IsTILTO API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Test if Acceleration sensor is available 
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable*/

//! @}

//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

#define SYS_FIOCTL_CHANGE_EVENT_DESCRIPTOR              0x802C      /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																		@brief parameter type is SYS_FIOCTL_CHANGE_EVENT_DESCRIPTOR_S : Used to associate an event with a descriptor */

//! @}



//! \addtogroup SYSFIOTCL_IDENT
//! @{

#define SYS_FIOCTL_GET_PRODUCT_CODE                     0x802E 			/*!<@deprecated  param type is Unsigned char[3] : product code M3X */

//! @}


//! \addtogroup SYSFIOCTL_IS
//! @{

#define SYS_FIOCTL_IS_CLESS                             0x8033				/*!< @deprecated This fioctl should not be called directly, use IsCless API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief no parameter : Test if cless is available */

//! @}

//! \addtogroup SYSFIOCTL_MISCELLANEOUS
//! @{

#define	SYS_FIOCTL_GET_PIO_BL2							0x8035			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																		@brief parameter type is SYS_FIOCTL_GET_PIO_BL2_ : gets IO port state for Booster Light II */

//! @}

//! \addtogroup SYSFIOCTL_IS
//! @{

#define SYS_FIOCTL_IS_CAM3                  			0x8036			/*!< @deprecated This fioctl should not be called directly, use IsCAM3 API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																		@brief   no parameter : Test if smart card reader CAM3 available  */

//! @}

//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

#define SYS_FIOCTL_DECOMPRESS_FLASH_FILES				0x8037 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief  decompress one file or files in the directory 
																			@param char * : \li "*" All files
																							\li filename  
																			@return 
																			\li 0 : OK
																			\li -1 not supported
																			\li other values : Please contact Telium support
																			@note supported by the product CAD30UCR only
																			*/
																							
#define SYS_FIOCTL_SET_SYSTEM_SAV						0x8038 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief  Internal use only. Set the sav sytem status  (Thunder 2)
																			@param unsigned int * : 0-disabled  1-enabled 
																			@return 
																			\li 0 : OK
																			\li -1 not supported
																			*/																							

#define SYS_FIOCTL_GET_SYSTEM_SAV						0x8039 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief Internal use only. Get the sav sytem status (Thunder 2)
																			@param char * : 0-disabled  1-enabled  
																			@return 
																			\li 0 : OK
																			\li -1 not supported
																			*/

//! @}

//! \addtogroup SYSFIOCTL_IS
//! @{

#define SYS_FIOCTL_IS_IMP_COMPANION                		0x803A			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief no parameter : Test if IMP3xx is in companion mode  */

//! @}

//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

#define SYS_FIOCTL_PER_EXIST                            0x8042 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief param : char*, Tests if an OEMC device is present in Telium system */

//! @}


//! \addtogroup SYSTEMFIOCTL_CMD
//! @{
	                                                                        
#define SYS_FIOCTL_REMOVE_DRIVER                        0x8045 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			 @brief Remove one component
																			 @param unsigned int : application type 
																			 @return 
																			 \li 0 Component deleted
																			 \li -1 Failed */
																			 
//! @}

//! \addtogroup SYSTEMFIOCTL_MISCELLANEOUS
//! @{

#define SYS_FIOCTL_GET_LAST_FM_BLOCK_REFRESH            0x8047 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief param : unsigned int,Gets address of the last block that had been refreshed */

//! @}

//! \addtogroup SYSFIOTCL_IDENT
//! @{

#define SYS_FIOCTL_GET_PROD_IDENT_AREA                  0x8048 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			 @brief Gets product identification area in NAND flash (page 0)
																			 @param unsigned char[512] */

//! @}

//! \addtogroup SYSFIOCTL_SNMP
//! @{

// SNMP fioctl see mib_snmp.h
#define SYS_FIOCTL_SNMP_START                      		0x8050 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			 @brief param : none, Start SNMP Agent */
#define SYS_FIOCTL_SNMP_STOP                      		0x8051 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			 @brief param : none, Stop SNMP Agent */
#define SYS_FIOCTL_SNMP_GET_STATUS                 		0x8052 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			 @brief param : unsigned int *, Get the SNMP Agent state */
#define SYS_FIOCTL_SNMP_SET_PORT                      	0x8054 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			 @brief param : unsigned int, Set SNMP Agent port */
#define SYS_FIOCTL_SNMP_GET_RCOM_NAME              		0x8055 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			 @brief param : char[32+1], Get the read commnuity name */
#define SYS_FIOCTL_SNMP_SET_RCOM_NAME                 	0x8056 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			 @brief param : char[32+1], Set the read commnuity name */
#define SYS_FIOCTL_SNMP_GET_WCOM_NAME              		0x8057 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			 @brief param : char[32+1], Get the write commnuity name */
#define SYS_FIOCTL_SNMP_SET_WCOM_NAME                 	0x8058 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			 @brief param : char[32+1], Set the write commnuity name */
	
//! @}

//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

#define SYS_FIOCTL_SWAP_FROM_CADTOOL_TO_P40				0x8060			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			 @brief Swap OEMC FILE "P40"<-->"CADTOOL" @param NULL @note supported by CAD30 products only*/
#define SYS_FIOCTL_SWAP_FROM_P40_TO_CADTOOL				0x8061			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			 @brief Swap OEMC FILE "P40"<-->"CADTOOL" @param NULL @note supported by CAD30 products only*/

//! @}

//! \addtogroup SYSTEMFIOCTL_MISCELLANEOUS
//! @{

#define SYS_FIOCTL_GET_RESET_STATUS_REGISTER      		0x8062 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			 @brief Param : unsigned int : read Thunder II Reset Register */

//! @}


///! \addtogroup SYSFIOCL_SECURITY
//! @{

#define SYS_FIOCTL_BOOSTER_GET_SECURITY_LEVEL  	 				0x8065 			/*!< @deprecated You should not call this fioctl directly, use IsTerminalPeds API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																					@brief Get booster level
																					@param unsigned char*  booster level \ref SECURITY_LEVEL 
																					@return 0 OK
																					*/

//! @}


//! \addtogroup SYSFIOCTL_IS
//! @{

#define SYS_FIOCTL_IS_SLOW_PRINTER               				0x8066 			/*!< @deprecated You should not call this fioctl directly, use IsSlowPrinter API instead. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																					@brief Test if slow printer configuration 
																					@param NULL
																					@return 
																					\li 0 Slow printer enabled
																					\li -1 Slow printer disabled 
																				*/
#define SYS_FIOCTL_IS_PAPER_OUT_DETECTION        				0x8066 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																					@brief Check the paper out detection presence
																					@param NULL
																					@return 
																					\li 0 paper out detection
																					\li -1 No paper out detection
																				*/

//! @}


//! \addtogroup SYSFIOTCL_FEATURES
//! @{

#define SYS_FIOCTL_GET_MANUFACTURING_CONFIG             		0x806B 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																					@brief param Unsigned char[32] name of the configuration in Logprod.dia */

//! @}

//! \addtogroup SYSTEMFIOCTL_MISCELLANEOUS
//! @{

#define SYS_FIOCTL_STORE_THUNDER_KEY	                		0x806C 			/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																					@brief param Unsigned char[16]	Store key in Thunder flash */

//! @}

//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

#define SYS_FIOCTL_START_WATCHDOG												0x8070 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																							@brief Start hardware Watchdog
																							@param NULL 
																							@return 
																							\li 0 OK
																							\li -1 not supported
																							
																							@note Telium I only  */
																							

#define SYS_FIOCTL_STOP_WATCHDOG												0x8071 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																							@brief Stop hardware Watchdog
																							@param NULL 
																							@return 
																							\li 0 OK
																							\li -1 not supported
																							
																							@note Telium I only  */
																							
#define SYS_FIOCTL_RELOAD_WATCHDOG											    0x8072 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																							@brief Reload hardware Watchdog 
																							@param NULL 
																							@return 
																							\li 0 OK
																							\li -1 not supported
																							
																							@note Telium I only  */

//! @}

//! \addtogroup SYSTEMFIOCTL_MISCELLANEOUS
//! @{

#define SYS_FIOCTL_GET_FIQ_COUNTER            					0x8073 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																			@brief param type is unsigned int : gets Fast IRQ counter */

//! @}

//! \addtogroup SYSFIOCTL_DEBUG
//! @{

#define SYS_FIOCTL_FFMS_DEBUG_ON                        0x8074 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																	@brief no parameter : enable FFMS debug for current applicatio */
#define SYS_FIOCTL_FFMS_DEBUG_OFF                       0x8075 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																	@brief  no parameter : disable FFMS debug for current application */

//! @}

//! \addtogroup SYSTEMFIOCTL_MISCELLANEOUS
//! @{

#define SYS_FIOCTL_RST_DEBUG_ON                         0x8076 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
																	@brief parameter type is unsigned int : enable/disable LLT mode after 200 resets */
//! @}


//! \addtogroup SYSFIOCTL_IS
//! @{

#define SYS_FIOCTL_IS_INGETRUST       	                0x8079 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief  Test if terminal is Ingetrusted.
                                                                    @param NULL
                                                                    @return 
                                                                    \li Ingetrusted mode check result
                                                                    \li 0 terminal is not Ingetrusted
                                                                    \li 1 terminal is Ingetrusted
                                                                    \li -1 not implemented
                                                                */
//! @}

//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

#define SYS_FIOCTL_M2OS_IDLE_STATE_START                0x807A /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief Enter idle state (for M2OS only)
																	@param NULL  */
#define SYS_FIOCTL_M2OS_IDLE_STATE_END                  0x807B /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief Exit idle state (for M2OS only)
																	@param NULL  */

//! @}

//! \addtogroup SYSFIOCL_SECURITY
//! @{

#define SYS_FIOCTL_GET_INGETRUST_TYPE  	                0x807C /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief  Get Ingetrust certificate type.
                                                                    @param NULL
                                                                    @return 
                                                                    \li gets Ingetrust certificate type (\ref INGETRUST_TYPES)
                                                                    \li -1 not implemented

																	*/
#define SYS_FIOCTL_GET_HTERM_REQUIRED_INGETRUST_TYPE    0x807D /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief Get hterminal information of Ingetrust required version.
                                                                    @param NULL
                                                                    @return 
                                                                    \li Ingestrust type ( \ref INGETRUST_TYPES
                                                                    \li -1 not implemented
                                                                */
                                                                
//! \addtogroup PCI_PTS_VERSION
//! @{

#define SYS_FIOCTL_GET_PCI_PTS_VERSION 	                0x807E /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief Get PCI PTS version (Implemented only on TELIUM II).
                                                                    @param NULL.
                                                                    @return \li \ref PCI_PTS_VERSION (\ref PCI_PTS_V2, \ref PCI_PTS_V3)
                                                                            \li -1 not implemented
                                                                */
//! @}

//! \addtogroup SECURITYLOCKS
//! @{

// Security locks 0x8080 to 0x80FF
#define SYS_FIOCTL_SET_SECURITY_MODE                    0x8080 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief  Set security mode @param NULL*/
#define SYS_FIOCTL_SECURITY_SET_ZKA SYS_FIOCTL_SET_SECURITY_MODE /*!< @deprecated replaced by \ref SYS_FIOCTL_SET_SECURITY_MODE */
#define SYS_FIOCTL_GET_SECURITY_MODE                    0x8081 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief Get the security mode
                                                                    @param NULL
                                                                    @return
                                                                        \li 0 security mode is not activated
                                                                        \li 1 security mode  is activated
                                                                        \li -1 not implemented
                                                                */
#define SYS_FIOCTL_SECURITY_GET_ZKA SYS_FIOCTL_GET_SECURITY_MODE

#define SYS_FIOCTL_SECURITY_SET_FALLBACK_DISABLED       0x8082 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief   Disable software version fall back 
																	@param NULL
																	@return 
																	\li 0 OK
																	\li -1 not implemented */
																	
#define SYS_FIOCTL_SECURITY_GET_FALLBACK_DISABLED       0x8083 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief   Test software version fall back mode
																	@param NULL
																	@return
                                                                    \li 0 Fall back is not disabled
                                                                    \li 1 Fall back is disabled
                                                                    \li -1 not implemented
                                                               */
                                                               
#define SYS_FIOCTL_SECURITY_SET_VARID_CHECKING          0x8084 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief   no parameter : Disable software update if varID is not the same
																																		return value : 0=success other=failure
                                                                */
#define SYS_FIOCTL_SECURITY_GET_VARID_CHECKING          0x8085 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief no parameter : Test software varID checking mode using return value :
                                                                    0 varID checking is disabled
                                                                    1 varID checking is enabled
                                                                    -1 not implemented
                                                               */
#define SYS_FIOCTL_SECURITY_SET_SCHEME_VARID_CHECKING   0x8086 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief no parameter : Disable scheme if varID is not the same that appi vardIR */
#define SYS_FIOCTL_SECURITY_GET_SCHEME_VARID_CHECKING   0x8087 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief no parameter : Test scheme varID checking mode using return value :
                                                                    0 varID checking is disabled
                                                                    1 varID checking is enabled
                                                                    -1 not implemented
                                                               */
#define SYS_FIOCTL_SECURITY_SET_DATE_PROTECT            0x8088 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief  no parameter : Protect Booster date */
#define SYS_FIOCTL_SECURITY_GET_DATE_PROTECT            0x8089 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief  no parameter : Test Booster date protection.
                                                                    0 pate protect is disabled
                                                                    1 date protect is enabled
                                                                    -1 not implemented
                                                                */
#define SYS_FIOCTL_SECURITY_LOCK_KEYBOARD               0x808A /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief  parameter type is unsigned int : magic number */
#define SYS_FIOCTL_SECURITY_GET_SECURITY_APPLICATION_APLLI_TYPE 0x808B /*!< param type is unsigned short * security_application_type : Get the application type of security application.
                                                                            Return value :
                                                                            0 there is security application
                                                                            1 no security application
                                                                            -1 not implemented
                                                                       */
#define SYS_FIOCTL_SECURITY_SET_INGETRUST_LOCK    		0x808C /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief Enable Ingetrust lock 
																	@param NULL
																	@return 0.*/

#define SYS_FIOCTL_SECURITY_GET_INGETRUST_LOCK    		0x808D /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief Get Ingetrust lock status 
																	@param NULL
																	@return 
																	\li \ref INGETRUSTLOCKED
                                                                    \li  -1 not implemented
																   */
//! @}

//! \addtogroup SECURITYLOCKS
//! @{

#define SYS_FIOCTL_SECURITY_SET_PIN_ENTRY_PROTECT      			0x808E /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief parameter type is unsigned int varID: PIN entry can be done only by scheme signed with the correct varid */
#define SYS_FIOCTL_SECURITY_GET_PIN_ENTRY_PROTECT       		0x808F /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief parameter type is unsigned int varID: PIN entry can be done only by scheme signed with the correct varid */


#define SYS_FIOCTL_SECURITY_SET_SWIPE_CALLBACK                  0x8090 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief param type is (void (*) (unsigned char * iso1, unsigned char * iso2, unsigned char * iso3)) : Set a callback called when a swipe track is read
                                                                            Return value :
                                                                            0 OK
                                                                            -1 not implemented
                                                                            -5 application is not a security application */
#define SYS_FIOCTL_SECURITY_SET_SOFTWARE_ACTIVATE_CALLBACK      0x8091 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief param type is (int (*) (const char *disk)) : Set a callback called when a SowftwareActivate is called
                                                                            Return value :
                                                                            0 OK
                                                                            -1 not implemented
                                                                            -5 application is not a security application*/
                                                                           
//! @}

//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

#define SYS_FIOCTL_SECURITY_SET_SECURITY_APPLICATION_PROTECT    0x8092 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief  Protect security application against deletion and unload 
																			@param NULL
																			@return 0*/
#define SYS_FIOCTL_SECURITY_GET_SECURITY_APPLICATION_PROTECT    0x8093 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Get security application protection status
																			@param NULL
																			@return 
                                                                            \li 0 security application protect is disabled
                                                                            \li 1 security application protect is enabled
                                                                            \li -1 not implemented*/
#define SYS_FIOCTL_SECURITY_SET_SYSTEM_LOADING_DISABLE          0x8094 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Disable the system loading mode at startup (LLT with up key pressed, USB key with F4 key pressed) 
																			@param NULL
																			@return 0*/
#define SYS_FIOCTL_SECURITY_GET_SYSTEM_LOADING_DISABLE          0x8095 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Get the system loading mode status :
																			@param NULL
																			@return 
                                                                            \li 0 System loading mode at startup are enabled
                                                                            \li 1 System loading mode at startup are disabled
                                                                            \li -1 not implemented*/
//! @}
                                                                            
//! \addtogroup SYSFIOCTL_CLESS
//! @{

#define  SYS_FIOCTL_WHERE_IS_CLESS                              0x8096 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @param NULL
																			@return
                                                                            \li 0: Booster manages the CLESS
                                                                            \li 1: Thunder manages the CLESS
                                                                            \li 2: Thunder manages the CLESS on external sensor
                                                                            \li -1 not implemented*/
                                                                            //! 
//! @}

//! \addtogroup SYSTEMFIOCTL_MISCELLANEOUS
//! @{
                                                                          
#define  SYS_FIOCTL_SET_CARD_INSERT_REMOVE_EVENT                0x8097 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Fioctl used to send an event when a card is inserted or removed.
                                                                            Telium OS signal the event specified in parameter to the current task when card is inserted or removed.
                                                                            param type is unsigned int : event number form 0 to 31  or 0xFFFFFFFF to disable this function.
                                                                            @param NULL
                                                                            @return
                                                                            \li 0 OK
                                                                            \li -1 not implemented*/
//! @}

//! \addtogroup SECURITYLOCKS
//! @{

#define SYS_FIOCTL_SECURITY_SET_EMV_KEY_PROTECT                 0x8098 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Fioctl used to enable EMV public keys to be stored Booster.
                                                                            @return
                                                                            \li 0 OK
                                                                            \li -1 not implemented
                                                                            \li other : error*/
#define SYS_FIOCTL_SECURITY_GET_EMV_KEY_PROTECT                 0x8099 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Fioctl used to check if EMV public keys are stored Booster.
                                                                            @return
                                                                            \li 0 : EMV key protection mode not activated
                                                                            \li 1 : EMV key protection mode activated
                                                                            \li -1 : EMV key protection mode not implemented in this system*/
                                                                            
//! @}

//! \addtogroup SYSFIOCTL_PCI_FIRMWARE
//! @{

#define SYS_FIOCTL_GET_PCI_CORE_REQUIREMENTS_FIRMWARE			0x809A  /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Get PCI Core Requirements firmware version  -> ex:"820305v01.01".
																			@param char[16]
																			@return 
																			\li 0 : OK
																			\li -1 : not supported
																			\note Telium II only*/
																			
#define SYS_FIOCTL_GET_PCI_OPEN_PROTOCOLS_FIRMWARE				0x809B  /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Get PCI Open Protocols firmware version -> ex:"820656v01.01".
																			@param char[16]
																			@return 
																			\li 0 : OK
																			\li -1 : not supported
																			\note Telium II only*/

//! @}

//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

#define SYS_FIOCTL_BOOSTER_DISABLE_YELLOW_DOT                   0x809C /*!< @deprecated You should not call directly this fioctl, call DisableYellowDot API from the Manager instead. To continue to use the fioctl, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Disable yellow dot sequence (Reset) 
																			@param unsigned int * : Magic number --> contact Telium support
																			@return 0: OK*/

#define SYS_FIOCTL_GET_UNATTENDED_MAINTENANCE_MODE              0x809D /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Get Unattended Maintenance Mode 
																			@param unsigned char * : Maintenance State
																			@return 0: OK*/

#define SYS_FIOCTL_GET_UNATTENDED_BUTTON_STATE	              	0x809E /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Get Unattended Button State 
																			@param unsigned char * : Button State
																			@return 0: OK*/

#define SYS_FIOCTL_SET_PINSHIELD_LIGHT			              	0x809F /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Set the pinshield light  
																			@param unsigned char * : Light On/Off
																			@return 0: OK*/

#define SYS_FIOCTL_SET_BACK_SCREEN								0x80A0 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief  Set On/Off the back screen of the iUC180 */


#define SYS_FIOCTL_GET_READER_INFORMATION						0x80A1 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Give information about External Reader
																			@param SYS_FIOCTL_PINPAD_DEF * *  pointer to struct of reader features
																			@return 0: OK*/

#define SYS_FIOCTL_GET_HORS_SERVICE_BUTTON_STATE				0x80A2 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Give information about the "Out of Order" switch (iUP250/iUR250)
																			@param unsigned char * : 0=Released 1=Pressed 255=Not Available
																			@return 0: OK*/

#define	SYS_FIOCTL_MOUNT_NIL_DEVICE								0x80A3 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Mount Nil Device  */	

#define SYS_FIOCTL_GET_KEY_JAMMED_INFO							0x80A4 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Look if a key is jammed on the keyboard
																			@param unsigned char * : 0=OK 1=Jammed 255=Not Available
																			@return 0: OK*/
			
//! @}

//! \addtogroup SYSFIOCTL_PCI_FIRMWARE
//! @{
#define SYS_FIOCTL_GET_READER_PCI_CORE_REQUIREMENTS_FIRMWARE			0x80A5  /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Get External Reader PCI Core Requirements firmware version  -> ex:"820514v01.01".
																			@param char[16]
																			@return 
																			\li 0 : OK
																			\li -1 : not supported
																			\note Telium II only*/
//! @}

//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

#define	SYS_FIOCTL_SET_MODE_LEVER_LOCK									0x80A6 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Activate/Desactivate Lever Lock on iUR250
																			@param unsigned char * : 0=OFF 1=ON */
   #define _MODE_LEVER_LOCK_OFF				 0x00
   #define _MODE_LEVER_LOCK_ON				 0x01

//! @}

																			
#define SYS_FIOCTL_GET_CPU_CHARGE						0x80A7 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Give information about External Reader
																			@param NULL
																			@return unsigned int: CPU charge in %*/
//! @}

//! \addtogroup SYSFIOCTL_ETHERNET
//! @{
																			
/*! @brief structure used with \ref SYS_FIOCTL_CONFIGURE_PROXY fioctl. */
typedef struct
{
	unsigned int proxy_type;				/*!< 0: Don't use proxy, 4: SOCKS4, 5: SOCKS5 */
	unsigned int proxy_address;   			/*!< IP address of proxy */
	unsigned short proxy_port;              /*!< Port of proxy */
	char proxy_login[64];                   /*!< Login for proxy identification */
	char proxy_password[64];                /*!< Password for proxy identification */
}SYS_FIOCTL_CONFIGURE_PROXY_S;
#define SYS_FIOCTL_CONFIGURE_PROXY  							0x80A8 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Configure system to automaticaly use a SOCKS proxy in TCP connection
                                                                            @param SYS_FIOCTL_CONFIGURE_PROXY_S *
																			@return 0: OK */
			
//! @}


//! \addtogroup SYSFIOCTL_USB
//! @{

/* 0x8100 to 0x82FF are reserved for USB fioctl */
#define SYS_FIOCTL_USB_CONNECT_PUP                      0x8100 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. Internal use only */
#define SYS_FIOCTL_USB_DISCONNECT_PUP                   0x8101 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. Internal use only */
#define SYS_FIOCTL_USBHOST_CLEAR_GLOBAL_POWER           0x8102 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. Internal use only */
#define SYS_FIOCTL_USBHOST_SET_GLOBAL_POWER             0x8103 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. Internal use only */
#define SYS_FIOCTL_GET_DEVICE_RELEASE_NUMBER            0x8104 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. Get the device release number 
																	@param  SYS_FIOCTL_GET_DEVICE_RELEASE_NUMBER_S * 
																	@return 
																	\li 0 :OK
																	\li -1 : not applicable; usb device not connected*/
																	
#define SYS_FIOCTL_USB_DEVICE_POWER_ON                  0x8105 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. no parameter : Power on usb device */
#define SYS_FIOCTL_USB_DEVICE_POWER_OFF                 0x8106 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. no parameter : Power off usb device */

#define SYS_FIOCTL_USB_DEVICE_SERIAL_NUMBER_ENABLE      0x8107 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief param type is unsigned int  Default value : 0=Disable / 1=Enable
                                                                    Enable Serial Number string.
                                                                            Return value :
                                                                            0 : OK
                                                                            -1 :function ot implemented in this system*/
                                                                            
#define SYS_FIOCTL_USB_DEVICE_SERIAL_NUMBER_GET         0x8108 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief Gets USB Serial Number status.
																	@param NULL
                                                                    @return 
                                                                    \li 0 : disabled
                                                                    \li 1 : enabled
                                                                    \li -1 : not implemented*/

//! @}

//! \addtogroup SYSTEMFIOCTL_CMD
//! @{
                                                                
#define SYS_FIOCTL_SECURITY_MODE_LOCK_MOZART_BY_HANDS  0x8109 	/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief Fioctl used for the Mozart by hands
																	@param SYS_FIOCTL_SECURITY_MODE_LOCK_MOZART_BY_HANDS_S * 
																	@return 
																	\li 0 :OK
																	\li 1 :KO (not supported or bad magic number) (please contact Telium support)
																	\li -1 :bad parameter (NULL for ex)
																	\note supported by BOOSTER 2 and 3 only.
																	*/
#define MLMBH_SET  							               0x55 /*!<@deprecated  cmd used to set   the mode lock of the Mozart by hands (\ref SYS_FIOCTL_SECURITY_MODE_LOCK_MOZART_BY_HANDS_S.mlmbh_cmd)*/
#define MLMBH_CLEAR 						               0xAA /*!<@deprecated  cmd used to clear the mode lock of the Mozart by hands (\ref SYS_FIOCTL_SECURITY_MODE_LOCK_MOZART_BY_HANDS_S.mlmbh_cmd)*/
#define MLMBH_STATUS                                       0xA5 /*!<@deprecated  cmd used to get status of mode lock of Mozart by hands (\ref SYS_FIOCTL_SECURITY_MODE_LOCK_MOZART_BY_HANDS_S.mlmbh_cmd)*/

//! @}


//! \addtogroup SYSFIOCTL_USB
//! @{

#define SYS_FIOCTL_USB_DEVICE_SESAM_VITALE_ENABLE      0x810A /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                   @brief use USBDEV_FIOCTL_SET_MODE (COM5) with mode USB_DEVICE_MODE_CDC_SV */
#define SYS_FIOCTL_USB_DEVICE_SESAM_VITALE_GET         0x810B /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                   @brief  use USBDEV_FIOCTL_GET_MODE (COM5) and check the mode USB_DEVICE_MODE_CDC_SV */

//! @}

//! \addtogroup SYSTEMFIOCTL_MISCELLANEOUS
//! @{

#define  SYS_FIOCTL_SET_WAKEUP_EVENT                   0x810C /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                   @brief Fioctl used to send an event when the terminal wakes up using SetNextWakeUp.
                                                                            The Telium OS signals the event specified in parameter to the current task when the terminal waked up.
                                                                            @param unsigned int * : event mask  or 0 to disable this function.
		                                                                    @return
      		                                                               \li 0 OK
                                                                            \li -1 not implemented*/
 //! @}

//! \addtogroup SYSTEMFIOCTL_LIFE_COUNTER
//! @{

#define  SYS_FIOCTL_RESET_LIFE_COUNTER                 0x810D /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                   @brief Fioctl used to reset a life counter in LIFECOUNTER.DIA
                                                                            @param unsigned int * : use LIFE counters identifier defined in defdiag_TSys.h.
                                                                            @return
                                                                            \li 0 OK
																			\li 1 counter not found
                                                                            \li -1 not implemented*/
//! @}
                                                                 
//! \addtogroup SYSFIOTCL_IDENT
//! @{
#define  SYS_FIOCTL_GET_PRODUCT_FULL_REFERENCE          0x810E /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                   @brief Fioctl used to read product ref (Level 3) string (for ex ICT220-01T1076C )
                                                                            @param char * : 64 bytes string required.
                                                                            @return
                                                                            \li 0 OK
                                                                            \li -1 not implemented
                                                                            \li -2 bad parameter (NULL for ex)
                                                                            \li -3 not available
                                                                            @note Telium II only*/
                                                                 
//! @}


//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

#define  SYS_FIOCTL_GET_OEMC_MAX_TASK_NUMBER            0x8110 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                    @brief to read the max number of Tasks that can be used by all applications  
                                                                            @param unsigned int * : max number of Tasks.
                                                                            @return
                                                                            \li 0 OK
                                                                            \li -1 not implemented
                                                                            \li -2 bad parameter (NULL for ex)
                                                                */

#define  SYS_FIOCTL_GET_OEMC_MAX_MAILBOX_NUMBER         0x8111 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief to read the max number of Mailboxes that can be used by all applications  
                                                                            @param unsigned int * : max number of Mailboxes.
                                                                            @return
                                                                            \li 0 OK
                                                                            \li -1 not implemented
                                                                            \li -2 bad parameter (NULL for ex)
                                                                */

#define  SYS_FIOCTL_GET_OEMC_MAX_SEMAPHORE_NUMBER         0x8112 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief  to read the max number of Semaphores that can be used by all applications  
                                                                            @param unsigned int * : max number of Semaphores.
                                                                            @return
                                                                            \li 0 OK
                                                                            \li -1 not implemented
                                                                            \li -2 bad parameter (NULL for ex)
                                                                */

#define  SYS_FIOCTL_GET_OEMC_MAX_DELAY_NUMBER             0x8113 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief to read the max number of Delays that can be used by all applications  
                                                                            @param unsigned int * : max number of Delays.
                                                                            @return
                                                                            \li 0 OK
                                                                            \li -1 not implemented
                                                                            \li -2 bad parameter (NULL for ex)
                                                                */

//! @}


//! \addtogroup SYSTEMFIOCTL_MISCELLANEOUS
//! @{

#define  SYS_FIOCTL_SET_LOWPOWER_EXIT_EVENT            0x8116 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Fioctl used to send an event when the terminal exits from low power mode.
                                                                            The Telium OS signals the event specified in parameter to the current task when the terminal exits from low power mode.
                                                                            @param unsigned int * : event mask  or 0 to disable this function.
		                                                                    @return
      		                                                               \li 0 OK
                                                                            \li -1 not implemented*/
 //! @}


//! \addtogroup SYSFIOCTL_USB
//! @{

#define SYS_FIOCTL_USB_HOST_BSD                        0x82F0 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief   make a usb BSD host ioctl */

typedef struct {
    char           dev_name[16];
    unsigned long  dev_ioctl;
    void *         dev_data;
} UsbHostIoctl_data;

#define SYS_FIOCTL_USB_HOST_BSD_GET_LAST_HUB_SPEED      0x82F1 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief   make a usb BSD host ioctl to get the last plugged hub speed (used by PROD tests) iSC250/350 */

typedef enum {
    hubSpeed_nohub     = 0,
    hubSpeed_LowSpeed  = 1,
    hubSpeed_FullSpeed = 2,
    hubSpeed_HighSpeed = 3
} UsbHostIoctl_hubSpeed;

#define SYS_FIOCTL_USB_HOST_BSD_GET_LAST_HUB_DCNX       0x82F2 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief   make a usb BSD host ioctl to get the last plugged hub number of deconncetions (used by PROD tests) iSC250/350 */

#define SYS_FIOCTL_USB_HOST_BSD_DLLWIFI                 0x82F3 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief make a usb BSD host DLL WIFI ioctl */

typedef struct {
    char           dev_name[16];
    unsigned long  dev_ioctl;
    void *         dev_data;
} UsbHostIoctlDllWifi_data;



//! @}

//! \addtogroup SYSFIOTCL_PINPAD_EMULATION
//! @{

/* 0x8300 to ... are reserved for others fioctl */
#define SYS_FIOCTL_START_INTERUC_THUNDER	               	 	0x8300 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief  to start the thunder interuc (host) - Internal use only */
#define SYS_FIOCTL_STOP_INTERUC_THUNDER                   		0x8301 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief  to stop the thunder interuc (host) - Internal use only */

#define SYS_FIOCTL_CMD_MAINTENANCE_PINPAD     			 		0x8302 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief to send to the thunder pinpad the maintenance request */

//! @}

//! \addtogroup SYSFIOCTL_TOUCH
//! @{
#define SYS_FIOCTL_CALIBRATION_MATRIX_ERASE                    	0x8303 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief  to delete the touch screen calibration matrix. The touch screen peripheral must be closed.
                                                                           @param NULL.
                                                                           @return 
                                                                           \li 0 : file with calibration matrix has been deleted, or it is absent, or touch screen is not supported.
                                                                           \li -1 : touch screen peripheral is not closed.
                                                                       */

//! @}

//! \addtogroup SYSFIOTCL_PINPAD_EMULATION
//! @{

#define SYS_FIOCTL_CMD_MAINTENANCE_CLESS          				0x8304 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief to send to the thunder cless target the maintenance request */

//! @}

//! \addtogroup SYSFIOCTL_IS
//! @{

#define SYS_FIOCTL_IS_TOUCH_SCREEN                           	0x8305 /*!< @deprecated You should not call directly this fioctl, call IsTouchScreen API from the Manager instead. To continue to use the fioctl, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Test if touch screen available    
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable */
#define SYS_FIOCTL_IS_AUDIO                           			0x8306 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Test if audio available   
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable*/


#define SYS_FIOCTL_GET_VIDEO_CAPABILITY                         0x8307 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Test if video available 
																			@param NULL
																			@return 
																					\li 0 Video available
																					\li -1 Video unavailable   */

//! @}

//! \addtogroup SYSFIOTCL_PINPAD_EMULATION
//! @{

#define SYS_FIOCTL_SET_DEVICE_MODE 	               			 	0x8308 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief to set the device mode - Internal use only */
#define SYS_FIOCTL_GET_DEVICE_MODE                    			0x8309 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief to get the device mode */

//! @}

//! \addtogroup SYSFIOCTL_CLESS
//! @{

#define SYS_FIOCTL_CLESS_SIGNAL_BEFORE_FIELD_ON                 0x830A /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Signal for touch screen driver: contactless is going to switch OFF the field */
#define SYS_FIOCTL_CLESS_SIGNAL_BEFORE_FIELD_OFF                0x830B /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Signal for touch screen driver: contactless is going to switch ON the field */

//! @}

//! \addtogroup SYSFIOCTL_IS
//! @{

#define SYS_FIOCTL_IS_LIGHT_SENSOR                    			0x830C /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Test if a light sensor is available 
																			@param NULL
																			@return 
																			\li 0 : available
																			\li -1: unavailable  */

//! @}

//! \addtogroup SYSFIOTCL_PINPAD_EMULATION
//! @{

#define SYS_FIOCTL_IS_DEVICE_MODE_SUPPORTED            			0x8310 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief does the terminal manage the device mode - Internal use only */

//! @}

//! \addtogroup SYSFIOTCL_FEATURES
//! @{

#define SYS_FIOCTL_GET_RADIO_MASK                               0x8311 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Get the Radio Mask 
																			@param unsigned int * : Bit mask containing all radio types available (\ref TERM_RADIO_MASK)
																			@return 
																			\li 0 :OK 
																			\li -1 : bad parameter (NULL for ex) or not implemented*/

//! @}

//! \addtogroup TERM_RADIO_MASK
//! @brief Get the radio features (bit field). Set by \ref SYS_FIOCTL_GET_RADIO_MASK
//! @note Some products can support several radio types (ex : BT + GPRS)
//!
//! @include oem_sysfioctl_Sample_16.c
//!
//! @{

#define TERM_RADIO_MASK_GPRS   1			/*!< value for \ref SYS_FIOCTL_GET_RADIO_MASK : GPRS */
#define TERM_RADIO_MASK_BT     2			/*!< value for \ref SYS_FIOCTL_GET_RADIO_MASK : BlueTooth */
#define TERM_RADIO_MASK_WIFI   4			/*!< value for \ref SYS_FIOCTL_GET_RADIO_MASK : Wifi */
#define TERM_RADIO_MASK_CDMA   8			/*!< value for \ref SYS_FIOCTL_GET_RADIO_MASK : CDMA */
#define TERM_RADIO_MASK_3G_850 (1 << 4)		/*!< value for \ref SYS_FIOCTL_GET_RADIO_MASK : 3G 850 MHz */
#define TERM_RADIO_MASK_3G_900 (1 << 5)		/*!< value for \ref SYS_FIOCTL_GET_RADIO_MASK : 3G 900 MHz */
#define TERM_RADIO_MASK_3G (TERM_RADIO_MASK_3G_850|TERM_RADIO_MASK_3G_900)	/*!< value for SYS_FIOCTL_GET_RADIO_MASK : 3G (any frequency band) */

//! @}

//! \addtogroup SYSFIOCTL_ETHERNET
//! @{

#define SYS_FIOCTL_ENTER_ETH_POWERDOWN			                0x8312 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief enter ethernet power down mode  -> powerdown mode*/
#define SYS_FIOCTL_LEAVE_ETH_POWERDOWN			                0x8313 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief leave ethernet power down mode  -> normal operation*/

//! @}

//! \addtogroup SYSFIOCTL_IS
//! @{

#define SYS_FIOCTL_GET_BT_NO_DIAL_TO_BASE                       0x8314 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Test if bluetooth doesn't work with a Telium Base (standalone)
																		 @param NULL
																		 @return 
																		 \li 0 This bluetooth terminal can't be connected to a Telium base.
																		 \li -1 Not supported or not applicable
																		 */

//! @}

//! \addtogroup SYSTEMFIOCTL_CMD
//! @{
#define SYS_FIOCTL_SND_SWITCH									0x8315 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief switch between primary and secondary sound output */

//! @}


//! \addtogroup SYSFIOTCL_IDENT
//! @{


#define SYS_FIOCTL_GET_PRODUCT_FULL_SERIAL_NUMBER             	0x8320 /*!< @deprecated You should not call directly this fioctl, call PSQ_Give_Full_Serial_Number API from the Manager instead. To continue to use the fioctl, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief get the long serial number (for ex 10176CT60000286) 
                                                                           @param unsigned char [64] serial numb (ASCII with \\0)
                                                                           @return 
                                                                           \li 0 OK
                                                                           \li -1 not implemented
                                                                           \li -2 bad parameter (NULL for ex)
                                                                           \li -3 serial number not available 
                                                                           @note Telium II only*/
                                                                           
#define SYS_FIOCTL_GET_PRODUCT_TOUCH_RELEASE                   	0x8321 /*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief get the touch release	
                                                                           @param unsigned char [64] : ASCII with \\0
                                                                           @return 
                                                                           \li 0 OK
                                                                           \li -1 not implemented
                                                                           \li -2 bad parameter (NULL for ex)
                                                                           \li -3 not available */

#define SYS_FIOCTL_GET_PRODUCT_STRING   	    		         0x8322		/*!< @deprecated This fioctl has been parsed as unused and may not be supported in future releases of the SDK. To use it, you may define define _DEPRECATED_SYSTEMFIOCTL_SDK96_ in your application. 
                                                                            @brief Get the terminal string (for ex "iCT250" )
																		 @param unsigned char [64] : string with \\0
																		  @return 
                                                                           \li 0 OK
                                                                           \li -1 not implemented
                                                                           \li -2 bad parameter (NULL for ex)
                                                                           \li -3 unknown string
                                                                           */


//#define SYS_FIOCTL_GET_PRODUCT_RFU_XXXX	                   	0x8323 /*!< RFU*/
//#define SYS_FIOCTL_GET_PRODUCT_RFU_XXXX	                   	0x8324 /*!< RFU*/
//#define SYS_FIOCTL_GET_PRODUCT_RFU_XXXX	                   	0x8325 /*!< RFU*/
//#define SYS_FIOCTL_GET_PRODUCT_RFU_XXXX	                   	0x8326 /*!< RFU*/
//#define SYS_FIOCTL_GET_PRODUCT_RFU_XXXX	                   	0x8327 /*!< RFU*/
//#define SYS_FIOCTL_GET_PRODUCT_RFU_XXXX	                   	0x8328 /*!< RFU*/
//#define SYS_FIOCTL_GET_PRODUCT_RFU_XXXX	                   	0x8329 /*!< RFU*/
//#define SYS_FIOCTL_GET_PRODUCT_RFU_XXXX	                   	0x832A /*!< RFU*/
//#define SYS_FIOCTL_GET_PRODUCT_RFU_XXXX	                   	0x832B /*!< RFU*/
//#define SYS_FIOCTL_GET_PRODUCT_RFU_XXXX	                   	0x832C /*!< RFU*/
//#define SYS_FIOCTL_GET_PRODUCT_RFU_XXXX	                   	0x832D /*!< RFU*/
//#define SYS_FIOCTL_GET_PRODUCT_RFU_XXXX	                   	0x832F /*!< RFU*/

//! @}

//! \addtogroup SYSTEMFIOCTL_AUDIO
//! @{

/* 0x8410 to 842F are reserved for audio fioctl*/    

#define SYS_FIOCTL_IS_AUDIO_AVAILABLE			               	0x8410 /*!< @deprecated  */
#define SYS_FIOCTL_AUDIO_SET_VOLUME			               		0x8411 /*!< @deprecated  */
#define SYS_FIOCTL_AUDIO_SET_ATTENUATION						0x8412 /*!< @deprecated  */
#define SYS_FIOCTL_AUDIO_PLAY_OGG			               		0x8420 /*!< @deprecated  */
#define SYS_FIOCTL_AUDIO_PLAY_OGG_WITH_VOL	             		0x8421 /*!< @deprecated  */
#define SYS_FIOCTL_AUDIO_PLAY_TONE			               		0x8422 /*!< @deprecated  */
#define SYS_FIOCTL_AUDIO_PLAY_TONE_WITH_VOL	               		0x8423 /*!< @deprecated  */
#define SYS_FIOCTL_AUDIO_PLAY_WAV			               		0x8424 /*!< @deprecated  */
#define SYS_FIOCTL_AUDIO_PLAY_WAV_WITH_VOL	             		0x8425 /*!< @deprecated  */
// #define SYS_FIOCTL_AUDIO_XXX	             					0x842F

//! @}

//! \addtogroup SYSFIOTCL_PINPAD_EMULATION
//! @{

/*! @brief structure used with \ref SYS_FIOCTL_START_INTERUC_THUNDER and \ref SYS_FIOCTL_STOP_INTERUC_THUNDER fioctl : set parameters for INTER UC THUNDER (optional). */

#define INTERUC_THUNDER_CMD_START		1
#define INTERUC_THUNDER_CMD_STOP		2

//! @}

//! \addtogroup SECURITYLOCKS
//! @{

/*! @brief structure used with \ref SYS_FIOCTL_SECURITY_SET_PIN_ENTRY_PROTECT fioctl : give the information of VarId locked. */
typedef struct
{
	unsigned short var_id;				/*!< VarId value */
	int	           cr;					/*!< cmd state   */
}
SYS_FIOCTL_SECURITY_SET_PIN_ENTRY_PROTECT_S;

//! @}

//! \addtogroup SYSTEMFIOCTL_CMD
//! @{

/*! @brief structure used with \ref SYS_FIOCTL_SECURITY_MODE_LOCK_MOZART_BY_HANDS fioctl : give the status of the Mozart : Disabled or not */
typedef struct
{
	unsigned char  mlmbh_cmd;	   	 	/*!< Mode Lock Mozart By Hands Status Commande : \ref MLMBH_SET / \ref MLMBH_CLEAR / \ref MLMBH_STATUS */
	unsigned char  mlmbh_status;		/*!< Mode Lock Mozart By Hands Status */
	char           ruf[2];              /* ruf to align  */
	int	           cr;					/*!< cmd state   */
}SYS_FIOCTL_SECURITY_MODE_LOCK_MOZART_BY_HANDS_S;

/*! @brief structure used with \ref SYS_FIOCTL_SET_MODE_LEVER_LOCK fioctl : Set the Lever Lock state : On or Off */
                                    
typedef struct
{
	unsigned char  mll_cmd;	   	 		/*!< Mode Lever Lock Commande */
	unsigned char  ruf[3];              /* ruf to align  */
	int	           cr;					/*!< cmd state   */
}SYS_FIOCTL_MODE_LEVER_LOCK_S;

//! @}
#endif


#endif // OEM_SYSTEM_DEPRECATED_H
