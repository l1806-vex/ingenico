/*! @addtogroup KSFAM_IOSF
 * @{
 */ 


#ifndef __DGPRS_DEPRECATED_H_INCLUDED__
#define __DGPRS_DEPRECATED_H_INCLUDED__

#ifdef _DEPRECATED_DGPRS_SDK96_

#define DGPRS_FIOCTL_SET_PIN_MODE_FREE                  DGPRS_FIOCTL_EXTERNAL           /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                Enable or disable the automatic PIN presentation by the driver
                                                                                                param: binaire mode_free (TRUE or FALSE) */

#define DGPRS_FIOCTL_SET_PIN_CONTROL_ACTIV              DGPRS_FIOCTL_EXTERNAL+1         /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Enable or disable PIN verification of the SIM
                                                                                                param: T_DGPRS_PIN_CTL *control */

#define DGPRS_FIOCTL_SET_PIN_CODE                       DGPRS_FIOCTL_EXTERNAL+2         /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                  Present the SIM PIN code.
                                                                                                param: char code[DGPRS_SIM_PIN_CODE_LGR_MIN+1 -> DGPRS_SIM_PIN_CODE_LGR+1] */


#define DGPRS_FIOCTL_SET_SHUTDOWN_MODE                  DGPRS_FIOCTL_EXTERNAL+4         /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 NOT USED 
                                                                                                param binaire module_mode_off (TRUE, FALSE) */

#define DGPRS_FIOCTL_SET_APN                            DGPRS_FIOCTL_EXTERNAL+5         /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Set the APN.
                                                                                                param: char APN[DGPRS_EXTENDED_APN_LGR+1] */

#define DGPRS_FIOCTL_CONNECT                            DGPRS_FIOCTL_EXTERNAL+6         /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Connect GPRS or GSM
                                                                                                param: T_DGPRS_CONNECT * msg_cnx*/

#define DGPRS_FIOCTL_DISCONNECT                         DGPRS_FIOCTL_EXTERNAL+7         /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Disconnection.
                                                                                                param: none */

#define DGPRS_FIOCTL_CALL_ACCEPTED                      DGPRS_FIOCTL_EXTERNAL+8         /*!< @deprecated NOT IMPLEMENTED */

#ifdef GESTION_SMS
#define DGPRS_FIOCTL_SMS_LIST                           DGPRS_FIOCTL_EXTERNAL+10        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Get the list of SMS.
                                                                                                param: T_DGPRS_GET_SMS_LIST * sms_list */

#define DGPRS_FIOCTL_SMS_GET                            DGPRS_FIOCTL_EXTERNAL+11        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Read a SMS
                                                                                                param(in):  int index
                                                                                                param(out): T_DGPRS_GET_SMS * sms*/

#define DGPRS_FIOCTL_SMS_SEND                           DGPRS_FIOCTL_EXTERNAL+12        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Sens a SMS.
                                                                                                param: T_DGPRS_SEND_SMS * sms */
#endif

#define DGPRS_FIOCTL_RETROFIT_MOD                       DGPRS_FIOCTL_EXTERNAL+13        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Put GPRS module in retrofit mode.
                                                                                                param: int timeout (second) */

#define DGPRS_FIOCTL_ALIM                               DGPRS_FIOCTL_EXTERNAL+14        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Turn on/of GPRS module
                                                                                                param: int  on_off */


#define DGPRS_FIOCTL_SET_PIN2_CODE                      DGPRS_FIOCTL_EXTERNAL+16        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Present the SIM PIN2 code.
                                                                                                param: char code[DGPRS_SIM_PIN_CODE_LGR_MIN+1 -> DGPRS_SIM_PIN_CODE_LGR+1] */

#define DGPRS_FIOCTL_SET_PUK_CODE                       DGPRS_FIOCTL_EXTERNAL+17        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Present the SIM PUK code.
                                                                                                param: char code[DGPRS_SIM_PIN_CODE_LGR_MIN+1 -> DGPRS_SIM_PIN_CODE_LGR+1] */

#define DGPRS_FIOCTL_SET_PUK2_CODE                      DGPRS_FIOCTL_EXTERNAL+18        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Present the SIM PUK2 code.
                                                                                                param: char code[DGPRS_SIM_PIN_CODE_LGR_MIN+1 -> DGPRS_SIM_PIN_CODE_LGR+1] */

#define DGPRS_FIOCTL_MODIFY_PIN_CODE                    DGPRS_FIOCTL_EXTERNAL+19        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Modify the SIM PIN code.
                                                                                                param: char code[2*DGPRS_SIM_PIN_CODE_LGR_MIN+2 -> 2*DGPRS_SIM_PIN_CODE_LGR+2] ("old_pin,new_pin") */

#define DGPRS_FIOCTL_MODIFY_PIN2_CODE                   DGPRS_FIOCTL_EXTERNAL+20        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Modify the SIM PIN2 code.
                                                                                                param: char code[2*DGPRS_SIM_PIN_CODE_LGR_MIN+2 -> 2*DGPRS_SIM_PIN_CODE_LGR+2] ("old_pin,new_pin") */

#define DGPRS_FIOCTL_SEND_CMD_AT                        DGPRS_FIOCTL_EXTERNAL+23        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Send AT command.
                                                                                                param: T_DGPRS_CMD_AT */

#define DGPRS_FIOCTL_SELECT_COM                         DGPRS_FIOCTL_EXTERNAL+24        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Select COM to use for external GPRS modem.
                                                                                                param: char * com ("COM0","COM1","COM2","USB") */

#define DGPRS_FIOCTL_SIM_PRESENT                        DGPRS_FIOCTL_EXTERNAL+25        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Test if SIM is present.
                                                                                                param: none */

#define DGPRS_FIOCTL_REGISTER_UNSOLICITED_MESSAGE       DGPRS_FIOCTL_EXTERNAL+27        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Register unsolicited message pattern.
                                                                                                param: char pattern[DGPRS_UNSOLICITED_MESSAGE_LGR] */

#define DGPRS_FIOCTL_POLL_UNSOLICITED_MESSAGE           DGPRS_FIOCTL_EXTERNAL+28        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Poll if unsolicited message is arrived.
                                                                                                param: T_DGPRS_UNSOLICITED_MESSAGE */

#define DGPRS_FIOCTL_GET_APN                            DGPRS_FIOCTL_EXTERNAL+29        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Get the current APN.
                                                                                                param: char apn[DGPRS_EXTENDED_APN_LGR+1] */

#define DGPRS_FIOCTL_DEFINE_NETWORK_NAME                DGPRS_FIOCTL_EXTERNAL+30        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Change a network name.
                                                                                                param: T_DGPRS_NETWORK_NAME * network_name */

#define DGPRS_FIOCTL_CDMA_TEST                			DGPRS_FIOCTL_EXTERNAL+31        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 For cdma prod test */

#define DGPRS_FIOCTL_FORBIDDEN_1                        DGPRS_FIOCTL_EXTERNAL+32        /*!< @deprecated DO NOT USE */

#define DGPRS_FIOCTL_GET_ACCESS_TECHNOLOGY              DGPRS_FIOCTL_EXTERNAL+33        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Obtain Current Access Technology (ACCESS_TECHNOLOGY_GSM, ACCESS_TECHNOLOGY_UTRAN)
                                                                                                param: pointer to an int holding the result on return */

#define DGPRS_FIOCTL_GET_CGATT_LAST_ERROR               DGPRS_FIOCTL_EXTERNAL+34        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Obtain the last CME ERROR obtained for the +CGATT=1 command
                                                                                                param: pointer to a string holding the result on return
                                                                                                The error string is automatically cleared after the call */
#define DGPRS_FIOCTL_GET_CGDCONT_LAST_ERROR             DGPRS_FIOCTL_EXTERNAL+35        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Obtain the last CME ERROR obtained for the +CGDCONT=1,"IP","APN",,0,0 command
                                                                                                param: pointer to a string holding the result on return
                                                                                                The error string is automatically cleared after the call */
#define DGPRS_FIOCTL_GET_CGACT_LAST_ERROR               DGPRS_FIOCTL_EXTERNAL+36        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Obtain the last CME ERROR obtained for the +CGACT command
                                                                                                param: pointer to a string holding the result on return
                                                                                                The error string is automatically cleared after the call */

#define DGPRS_FIOCTL_SET_CGATT_TIMEOUT                  DGPRS_FIOCTL_EXTERNAL+37        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Set the timeout for the +CGATT=1 command in 10ms unit (100 means 1 second). If this timeout is set to zero, default timeout applies.
                                                                                                param: pointer to a unsigned int containing the required timeout in seconds. */
#define DGPRS_FIOCTL_SET_CGDCONT_TIMEOUT                DGPRS_FIOCTL_EXTERNAL+38        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Set the timeout for the +CGDCONT=1,"IP","APN",,0,0 command in 10ms unit (100 means 1 second). If this timeout is set to zero, default timeout applies.
                                                                                                param: pointer to a unsigned int containing the required timeout in seconds. */
#define DGPRS_FIOCTL_SET_CGACT_TIMEOUT                  DGPRS_FIOCTL_EXTERNAL+39        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Set the timeout for the +CGACT=1,1 command in 10ms unit (100 means 1 second). If this timeout is set to zero, default timeout applies (connection timeout given in connect fioctl).
                                                                                                param: pointer to a unsigned int containing the required timeout in seconds. */


#define DGPRS_FIOCTL_GET_RADIO_ACCESS_TECHNOLOGY        DGPRS_FIOCTL_EXTERNAL+40        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Get the desired Radio Access Technology in :
                                                                                                    RADIO_ACCESS_TECHNOLOGY_AUTO
                                                                                                    RADIO_ACCESS_TECHNOLOGY_2G_ONLY
                                                                                                    RADIO_ACCESS_TECHNOLOGY_3G_ONLY
                                                                                                    RADIO_ACCESS_TECHNOLOGY_2G_WHEN_AVAILABLE
                                                                                                    RADIO_ACCESS_TECHNOLOGY_3G_WHEN_AVAILABLE
                                                                                                param: pointer to a unsigned int containing the required RAT. */

#define DGPRS_FIOCTL_SET_RADIO_ACCESS_TECHNOLOGY        DGPRS_FIOCTL_EXTERNAL+41        /*!< @deprecated This fioctl has been parsed as unused by our survey. It will no longer be supported in future releases of the SDK. If you need to use it anyway, you may define _DEPRECATED_DGPRS_SDK96_ in your application.
                                                                                                 Set the desired Radio Access Technology in :
                                                                                                    RADIO_ACCESS_TECHNOLOGY_AUTO
                                                                                                    RADIO_ACCESS_TECHNOLOGY_2G_ONLY
                                                                                                    RADIO_ACCESS_TECHNOLOGY_3G_ONLY
                                                                                                    RADIO_ACCESS_TECHNOLOGY_2G_WHEN_AVAILABLE
                                                                                                    RADIO_ACCESS_TECHNOLOGY_3G_WHEN_AVAILABLE
                                                                                                param: pointer to a unsigned int containing the required RAT. */

/*! @deprecated Mount the GPRS driver for an external equipment.
 * @param serial : serial device to use "USB" "COM0", "COM1", "COM2".
 * @return 0 if no error.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
#ifndef _DEPRECATED_SYSTEMFIOCTL_SDK96_
#define GPRS_Mount(a) ERROR_Deprecation_For_Function_GPRS_Mount_For_Module_DPRGS_SeeDocumentation_In_CHM_File;
/* This error is generated to warn you about the deprecation for DGPRS.
You can remove this error by adding _DEPRECATED_DGPRS_SDK96_. Please do the necessary to clean your
code and use TELIUM GPRS library.*/
#else
int GPRS_Mount(char* serial) MACRO_DEPRECATED;
#endif

#endif

#endif // __DGPRS_DEPRECATED_H_INCLUDED__
/*! @}  */ 

