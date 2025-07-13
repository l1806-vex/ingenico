#ifndef __OEM_UCM_DEPRECATED_H_INCLUDED__
#define __OEM_UCM_DEPRECATED_H_INCLUDED__


#ifdef _DEPRECATED_OEM_UCM_SDK091000_

#define COM_FIOCTL_GET_DSR              	0x800a	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	     @brief read DSR com signal if signal supported*/
#define COM_FIOCTL_GET_RI	          		0x800b	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																		  @brief read DSR com signal if signal supported*/
#define COM_FIOCTL_GET_DCD             	0x800c	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
															     		  @brief read DCD com signal if signal supported */
#define MDB_FIOCTL_SEND_NEXT_BYTE_9BIT  	0x800d	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																		  @brief Indicate to the system that next byte need to be transmit as MDB Address */
#define MDB_FIOCTL_SET_SLAVE_1          	0x800e	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																		  @brief configuration command of the first MDB Address in slave Mode */
#define MDB_FIOCTL_SET_SLAVE_2          	0x800f	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																		  @brief configuration command of the secondt MDB Address in slave Mode */
#define IRDA_FIOCTL_SET_FILTER      		0x8012	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																		  @brief Configure filter Level in IRDA mode */
#define MDB_FIOCTL_SET_RESP_DELAY     	   0x8013	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																		  @brief configuration command of Time-out MDB protocol  */
#define MDB_FIOCTL_GET_RESP_DELAY     	   0x8014	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																		  @brief return Time-out programmed for MDB protocol */

/*
======================================================================
					List of Defines (IO)
======================================================================
*/
// FIOCTL
// LEDs (from UCM board)
#define IO_FIOCTL_SET_LED0              0x8000	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief switch led0 on */
#define IO_FIOCTL_CLEAR_LED0            0x8001	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief switch led0 off */
#define IO_FIOCTL_SET_LED1              0x8002	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief switch led1 on */
#define IO_FIOCTL_CLEAR_LED1            0x8003	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief switch led1 off */
#define IO_FIOCTL_SET_LED2              0x8004	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief switch led2 on */
#define IO_FIOCTL_CLEAR_LED2            0x8005	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief switch led2 off */

// IO inputs/outputs
#define IO_FIOCTL_SET_IO0               0x8008	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief set output IO0 to 1 */
#define IO_FIOCTL_CLEAR_IO0             0x8009	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief set output IO0 to 0 */
#define IO_FIOCTL_SET_IO1               0x800a	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief set output IO1 to 1 */
#define IO_FIOCTL_CLEAR_IO1             0x800b	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief set output IO1 to 0 */
#define IO_FIOCTL_GET_STATE_IO0         0x800c	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief read input IO0	 */
#define IO_FIOCTL_GET_STATE_IO1         0x800d	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief read input IO1 */
#define IO_FIOCTL_GET_STATE_PUSH0	    0x8010	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief read input push */
 
// Battery state
#define IO_FIOCTL_GET_STATE_BATTERY     0x8006 	/*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	  @brief give battery state: 	0 -> battery low /	1 -> battery ok */

// cmd external com power (COM1,2,COM10,COM11,COM3_MDB,USB_HOST) 
#define IO_FIOCTL_EXTERNAL_POWER_ON    	 0x800e 	 /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	      @brief turn on 5VDC power on connectors:COM1,COM2,COM10,COM11,COM3_MDB,USB_HOST */
#define IO_FIOCTL_EXTERNAL_POWER_OFF     0x800f 	 /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_UCM_SDK091000_ in your application. 
																	      @brief turn off 5VDC power on connectors:COM1,COM2,COM10,COM11,COM3_MDB,USB_HOST */


#endif // _DEPRECATED_OEM_UCM_SDK091000_

#endif // __OEM_UCM_DEPRECATED_H_INCLUDED__
