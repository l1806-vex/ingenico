#ifndef __OEM_PRINT_DEPRECATED_H_INCLUDED__
#define __OEM_PRINT_DEPRECATED_H_INCLUDED__

#ifdef _DEPRECATED_OEM_PRINT_SDK091000_

#define    PRINTER_FIOCTL_DEFPRINTERPATTERN		0x8019	    /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_PRINT_SDK091000_ in your application. 
																				      @brief Command to link a pattern to a char * @note EXT_PRINTER only @param st_ext_printer_defpattern * : Printer Pattern definition */
#define    PRINTER_FIOCTL_SET_BT_ADDRESS		0x8021	       /*!< @deprecated This fioctl has been parsed as unused. It may not be supported in future releases of the SDK.  To use it, you may define define _DEPRECATED_OEM_PRINT_SDK091000_ in your application. 
																				      @brief Command to set the Bluetooth address of the external printer @note EXT_PRINTER only @param st_ext_printer_bt_device_addr * : Printer Bluetooth Address  */

/*! @brief  Define the address of the bluetooth device. (total size 2 * 4) (EXT_PRINTER only)  @ref PRINTER_FIOCTL_SET_BT_ADDRESS*/
typedef struct
{
	unsigned int nap:16,		/*!< Non significant Address Part 32..47 */
				 uap:8;			/*!< Upper Address Part 24..31 */
	unsigned int lap;			/*!< Lower Address part 00..23 */
} st_ext_printer_bt_device_addr;

#endif // _DEPRECATED_OEM_PRINT_SDK091000_


#endif // __OEM_PRINT_DEPRECATED_H_INCLUDED__
