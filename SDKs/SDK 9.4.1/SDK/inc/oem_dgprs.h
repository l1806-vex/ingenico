/*! @addtogroup KSFAM_IOSF
 * @{
 */ 


#ifndef __DGPRS_H_INCLUDED__
#define __DGPRS_H_INCLUDED__


#define DGPRS_NETWORK_NAME_LGR                  20      /*!< Maximum size of network name */
#define DGPRS_VERSION_SOFTWARE_LGR              24      /*!< Maximum size of version software */
#define DGPRS_IMEI_NUMBER_LGR                   20      /*!< Maximum size of IMEI */
#define DGPRS_SIM_ICC_ID_LGR                    20      /*!< Maximum size of ICC */
#define DGPRS_SIM_PIN_CODE_LGR_MIN              4       /*!< Minimum size of SIM PIN code */
#define DGPRS_SIM_PIN_CODE_LGR                  8       /*!< Maximum size of SIM PIN code */
#define DGPRS_APN_LGR                           63      /*!< Maximum size of APN */
#define DGPRS_EXTENDED_APN_LGR                  100     /*!< Maximum size for extended APN */
#define DGPRS_IMSI_LGR                          16      /*!< Maximum size of IMSI */
#define DGPRS_SIM_PROVIDER_LGR                  16      /*!< Maximum size of SIM provider */
#define DGPRS_LOCAL_AREA_IDENTIFICATION_LGR     6       /*!< Maximum size of network id */
#define DGPRS_DATA_NUMBER_LGR                   20      /*!< Maximum size of phone number */
#define DGPRS_UNSOLICITED_MESSAGE_LGR           512     /*!< Maximum size of unsolicited message */
#define SPECIFIC_CME_ERROR_SIZE                 (31)    /*!< Maximum size of specific error messages (AT+CGATT=1, AT+CGDCONT=1,..., AT+CGACT=1,1), not counting the trailing '\0' */

#define DGPRS_REPORT_NOT_RECEIVED_YET           -1      /*!< Wait status of module */
#define DGPRS_REPORT_READY                      0       /*!< The GPRS module is ready */
#define DGPRS_REPORT_WAITING_CODE               1       /*!< A PIN code is required */
#define DGPRS_REPORT_SIM_NOT_PRESENT            2       /*!< The SIM card is not present */
#define DGPRS_REPORT_SIMLOCK_STATE              3       /*!< The module is in "SIMlock" state */
#define DGPRS_REPORT_FATAL_ERROR                4       /*!< Unrecoverable error */
#define DGPRS_REPORT_UNKNOWN_ERROR              5       /*!< Unknown state */

#define DGPRS_SIM_NOT_RECEIVED_YET              -1      /*!< SIM status not yet received */
#define DGPRS_SIM_OK                            1       /*!< SIM is ready */
#define DGPRS_SIM_KO                            2       /*!< SIM error */
#define DGPRS_SIM_PIN_REQUIRED                  3       /*!< The SIM PIN code is required */
#define DGPRS_SIM_PIN2_REQUIRED                 4       /*!< The SIM PIN2 code is required */
#define DGPRS_SIM_PIN_ERRONEOUS                 5       /*!< Wrong SIM code */
#define DGPRS_SIM_NOT_INSERTED                  6       /*!< The SIM is not detected */
#define DGPRS_SIM_PUK_REQUIRED                  7       /*!< The SIM PUK code is required */
#define DGPRS_SIM_PUK2_REQUIRED                 8       /*!< The SIM PUK2 code is required */
#define DGPRS_SIM_PIN_PRESENTED                 9       /*!< Wait status of SIM code */

#define DGPRS_MASK_FUNC_NONE                    0       /*!< Disable GPRS and GSM */
#define DGPRS_MASK_FUNC_GSM                     1       /*!< Enable GSM only */
#define DGPRS_MASK_FUNC_GPRS                    2       /*!< Enable GPRS only */
#define DGPRS_MASK_FUNC_GLOBAL                  3       /*!< Enable both GPRS and GSM */

#define DGPRS_GPRS_DISCONNECTED                 0       /*!< GPRS is disconnected */
#define DGPRS_GPRS_PDP_READY                    1       /*!< Ready to connect to GPRS */
#define DGPRS_GPRS_PDP_CONNECTED                2       /*!< Connected to GPRS */
#define DGPRS_GPRS_PPP_NEGOCIATED               3       /*!< PPP link is established */
#define GPRS_ATTACHEMENT_FAILED                 4       /*!< GPRS attachement failed */

#define DGPRS_GSM_NETWORK_DISCONNECT            1       /*!< Not ready to do GSM call */
#define DGPRS_GSM_NETWORK_URGENCY_CONNECT       2       /*!< Only emergency GSM call is accepted */
#define DGPRS_GSM_NETWORK_NORMAL_CONNECT        3       /*!< Ready to do a GSM call */
#define DGPRS_GSM_NETWORK_COM_IN_PROGRESS       4       /*!< GSM call in progress */

#define DGPRS_GSM_NETWORK_COM_DATA_IN_PROGRESS 	0       /*!< Data GSM connection in progress */
#define DGPRS_GSM_NETWORK_COM_VOICE_IN_PROGRESS 1       /*!< Voice GSM connection in progress */

#define DGPRS_GSM_CONNECTION                    0       /*!< GSM connection */
#define DGPRS_GPRS_CONNECTION                   1       /*!< GPRS connection */

#define DGPRS_GSM_2400_V22BIS                   4       /*!< V22 bis at 2400 bauds */
#define DGPRS_GSM_4800_V32                      6       /*!< V32 at 4800 bauds */
#define DGPRS_GSM_9600_V32                      7       /*!< V32 at 9600 bauds */
#define DGPRS_GSM_2400_V110                     68      /*!< V110 at 2400 bauds */
#define DGPRS_GSM_4800_V110                     70      /*!< V110 at 4800 bauds */
#define DGPRS_GSM_9600_V110                     71      /*!< V110 at 9600 bauds */

#define DGPRS_GSM_DATA_MODE_TRANSPARENT         0       /*!< Transparent mode */
#define DGPRS_GSM_DATA_MODE_RLP                 1       /*!< RLP mode */

#define DGPRS_FIOCTL_ALIM_OFF                   0       /*!< Turn off GPRS module */
#define DGPRS_FIOCTL_ALIM_ON                    1       /*!< Turn on GRPS module */

#define ACCESS_TECHNOLOGY_GSM                   0       /*!< Access technology is GSM (aka 2G) */
#define ACCESS_TECHNOLOGY_UTRAN                 2       /*!< Access technology is UTRAN (aka 3G) */

#define RADIO_ACCESS_TECHNOLOGY_AUTO              0     /*!< Automatic selection of RAT */
#define RADIO_ACCESS_TECHNOLOGY_2G_ONLY           1     /*!< Use 2G network only */
#define RADIO_ACCESS_TECHNOLOGY_3G_ONLY           2     /*!< Use 3G network only */
#define RADIO_ACCESS_TECHNOLOGY_2G_WHEN_AVAILABLE 3     /*!< Use 2G when available, else 3G */
#define RADIO_ACCESS_TECHNOLOGY_3G_WHEN_AVAILABLE 4     /*!< Use 3G when available, else 2G */

/*! @brief Boolean type define */
typedef unsigned int binaire;



/*! @brief PIN code verification parameters */
typedef struct
{
        binaire ctl_activ;                              /*!< Active PIN code verification */
        char    code[DGPRS_SIM_PIN_CODE_LGR+1];         /*!< PIN code */
        int     reserved[8];                            /*!< Reserved for future use */
}T_DGPRS_PIN_CTL;



/*! @brief Connection parameters */
typedef struct
{
        int     connection_type;                        /*!< DGPRS_GSM_CONNECTION / DGPRS_GPRS_CONNECTION */
        int     timeout;                                /*!< Connection timeout in seconds */
        int     data_baudrate;                          /*!< Baudrate (DGPRS_GSM_2400_V22BIS, DGPRS_GSM_4800_V32, ...) */
        int     data_mode;                              /*!< DGPRS_GSM_DATA_MODE_TRANSPARENT / DGPRS_GSM_DATA_MODE_RLP */
        char    data_number[DGPRS_DATA_NUMBER_LGR+1];   /*!< Phone number */
        int     reserved[8];                            /*!< Reserved for future use */
}T_DGPRS_CONNECT;



/*! @brief State of GPRS driver */
typedef struct
{	
        int     start_report;   /*!< GPRS module status
                                        - DGPRS_REPORT_NOT_RECEIVED_YET
                                        - DGPRS_REPORT_READY
                                        - DGPRS_REPORT_WAITING_CODE
                                        - DGPRS_REPORT_SIM_NOT_PRESENT
                                        - DGPRS_REPORT_SIMLOCK_STATE
                                        - DGPRS_REPORT_FATAL_ERROR
                                        - DGPRS_REPORT_UNKNOWN_ERROR */

        int     sim_status;     /*!< SIM status
                                        - DGPRS_SIM_NOT_RECEIVED_YET
                                        - DGPRS_SIM_OK				
                                        - DGPRS_SIM_KO		
                                        - DGPRS_SIM_PIN_REQUIRED		
                                        - DGPRS_SIM_PIN2_REQUIRED
                                        - DGPRS_SIM_PIN_ERRONEOUS		
                                        - DGPRS_SIM_SIM_NOT_INSERTED			
                                        - DGPRS_SIM_PUK_REQUIRED (3 PIN KO)
                                        - DGPRS_SIM_PUK2_REQUIRED */

        int     radio_level;    /*!< Radio level: 0 to 5 */
        
        int     battery_level;  /*!< Battery level: 0 to 5 */
        
        int     network_connection;     /*!< Network connection status
                                                - DGPRS_GSM_NETWORK_DISCONNECT		
                                                - DGPRS_GSM_NETWORK_URGENCY_CONNECT : emergency call only  
                                                - DGPRS_GSM_NETWORK_NORMAL_CONNECT : ready to connect
                                                - DGPRS_GSM_NETWORK_COM_IN_PROGRESS  */

        binaire incoming_data_call;     /*!< Incomming GSM data call */

        char    network_name[DGPRS_NETWORK_NAME_LGR+1]; /*!< Network name (string) */

        char    module_software_version[DGPRS_VERSION_SOFTWARE_LGR+1];  /*!< GPRS module version (string) */

        char    module_imei_number[DGPRS_IMEI_NUMBER_LGR+1];    /*!< IMEI (string) */

        binaire gprs_attachment;        /*!< GPRS attachment */	

        int     status_gprs;    /*!< GPRS status
                                        - GPRS_DISCONNECTED
                                        - GPRS_PDP_ACTIV
                                        - GPRS_PDP_CONNECTED
                                        - GPRS_PPP_NEGOCIATED
                                        - GPRS_ATTACHEMENT_FAILED */

        binaire	pin_control_activ;	  /*!< PIN verification state */

        binaire pin_mode_free;          /*!< Automatic PIN presentation state */

        binaire shut_down_mode_off;     /*!< GPRS module shutdown mode */

        int     func_enable;    /*!< Enable GSM / GPRS
                                        - DGPRS_MASK_FUNC_NONE
                                        - DGPRS_MASK_FUNC_GSM
                                        - DGPRS_MASK_FUNC_GPRS
                                        - DGPRS_MASK_FUNC_GLOBAL */

        char    gprs_apn[DGPRS_APN_LGR+1];      /*!< APN */
        
        FILE    *com2_status;   /*!< COM file handle */

        binaire incoming_sms;   /*!< Incomming SMS status */

        char    simIccId[DGPRS_SIM_ICC_ID_LGR+1];       /*!< SIM ICC */

        char    module_identification[32];      /*!< GPRS module name */

        binaire use_sim_provider;       /*!< Indicates if there is a SIM provider */
        char    sim_provider[DGPRS_SIM_PROVIDER_LGR+1];	/*!< SIM provider */

        int     reserved[37];   /*!< Reserved for future use */
        
        int     location_area_code;   /*!< Location Area Code of the Serving Cell */
        int     cell_id;              /*!< ID of the Serving Cell*/
        
        int     network_typ;        /*!< GSM status
                                                - GSM_NETWORK_COM_VOICE_IN_PROGRESS
                                                - GSM_NETWORK_COM_DATA_IN_PROGRESS */
        binaire plmn;   /*!<GSM Public Land Mobile Network Identifier in GSM format (padded with f, nibbles swapped inside byte)
                            plmn = (Mobile Country Code << 16) + Mobile Network Code
                            Examples :
                                MOVISTAR is 716 06     => GSM <MCC,MNC> <0x17f6,0x60>   => plmn = 0x17f60060
                                Is.Com TCI is 376 350> => GSM <MCC,MNC> <0x73f6,0x53f0> => plmn = 0x73f653f0
                                 */
} T_DGPRS_GET_INFORMATION;


#define DGPRS_NB_NETWORK_MAX                    20      /*!< Maximum number of network */
#define DGPRS_NETWORK_STATUS_UNKNOWN            0       /*!< Network status unknown */
#define DGPRS_NETWORK_STATUS_AVAILABLE          1       /*!< Authorized network */
#define DGPRS_NETWORK_STATUS_CURRENT            2       /*!< Current network */
#define DGPRS_NETWORK_STATUS_FORBIDDEN          3       /*!< Forbidden network */

/*! @brief List of network found */
typedef struct
{
        char    network_name[DGPRS_NETWORK_NAME_LGR+1][DGPRS_NB_NETWORK_MAX];                   /*!< Network name */
        char    network_id[DGPRS_LOCAL_AREA_IDENTIFICATION_LGR+1][DGPRS_NB_NETWORK_MAX];        /*!< Network identifier */
        int     network_status[DGPRS_NB_NETWORK_MAX];                                           /*!< Network status */
        int     nb_network;                                                                     /*!< Number of network found */
} T_DGPRS_SEARCH_NETWORK;


/*! @brief AT command descriptor */
typedef struct
{
        char    cmd[512];               /*!< AT command to send */
        char *  result_buffer;          /*!< Buffer where response is stored */
        int     buffer_size;            /*!< Size of the buffer */
        int     result_length;          /*!< Length of th response */
}T_DGPRS_CMD_AT;


/*! @brief Description of unsolicited message */
typedef struct
{
        char *  result_buffer;          /*!< Buffer where unsolicited message is stored */
        int     buffer_size;            /*!< Size of the buffer */
        int     result_length;          /*!< Length of the unsolicited message */
}T_DGPRS_UNSOLICITED_MESSAGE;


/*! @brief Description of network name replacement or addition (NOT permanent) */
#if 0
/*!<@deprecated */
typedef struct
{
        char    real_network_name[DGPRS_NETWORK_NAME_LGR+1];    /*!< Network name to change */
        char    new_network_name[DGPRS_NETWORK_NAME_LGR+1];     /*!< New network name to use */
}T_DGPRS_NETWORK_NAME;
#else
typedef struct {
    binaire mcc;                                /*!< Mobile Country Code */
    binaire mnc;                                /*!< Mobile Network Code */
    char long_alpha_id[DGPRS_NETWORK_NAME_LGR]; /*!< Long alphanumeric name */
} T_DGPRS_NETWORK_MCC_MNC_AND_NAME;
#endif


#ifdef GESTION_SMS
#define DGPRS_NB_SMS_MAX                        16      /*!< Maximum number of SMS */

/*! @brief Get the list of SMS */
typedef struct
{
        int     nb_sms;                                 /*!< Number of SMS */
        int     sms_index_list[DGPRS_NB_SMS_MAX];       /*!< List of SMS index */
}T_DGPRS_GET_SMS_LIST;


/*! @brief Read a SMS */
typedef struct
{
        uchar   pdu[256];       /*!< SMS PDU */
}T_DGPRS_GET_SMS;


/*! @brief Send a SMS */
typedef struct
{
        int     stat;           /*!< SMS status */
        int     length;         /*!< SMS length */
        uchar   pdu[256];       /*!< SMS PDU */
}T_DGPRS_SEND_SMS;

#endif


#define DGPRS_FIOCTL_EXTERNAL                           0x8000                          /*!< Base of GPRS fioctl number. */

#define DGPRS_FIOCTL_SET_PIN_MODE_FREE                  DGPRS_FIOCTL_EXTERNAL           /*!< Enable or disable the automatic PIN presentation by the driver
                                                                                                param: binaire mode_free (TRUE or FALSE) */

#define DGPRS_FIOCTL_SET_PIN_CONTROL_ACTIV              DGPRS_FIOCTL_EXTERNAL+1         /*!< Enable or disable PIN verification of the SIM
                                                                                                param: T_DGPRS_PIN_CTL *control */

#define DGPRS_FIOCTL_SET_PIN_CODE                       DGPRS_FIOCTL_EXTERNAL+2         /*!< Present the SIM PIN code.
                                                                                                param: char code[DGPRS_SIM_PIN_CODE_LGR_MIN+1 -> DGPRS_SIM_PIN_CODE_LGR+1] */

#define DGPRS_FIOCTL_SET_FUNC_ENABLE                    DGPRS_FIOCTL_EXTERNAL+3         /*!< Enable/Disable GSM and GPRS.
                                                                                                param: int (DGPRS_MASK_FUNC_NONE, DGPRS_MASK_FUNC_GSM, ...) */

#define DGPRS_FIOCTL_SET_SHUTDOWN_MODE                  DGPRS_FIOCTL_EXTERNAL+4         /*!< NOT USED 
                                                                                                param binaire module_mode_off (TRUE, FALSE) */

#define DGPRS_FIOCTL_SET_APN                            DGPRS_FIOCTL_EXTERNAL+5         /*!< Set the APN.
                                                                                                param: char APN[DGPRS_EXTENDED_APN_LGR+1] */

#define DGPRS_FIOCTL_CONNECT                            DGPRS_FIOCTL_EXTERNAL+6         /*!< Connect GPRS or GSM
                                                                                                param: T_DGPRS_CONNECT * msg_cnx*/

#define DGPRS_FIOCTL_DISCONNECT                         DGPRS_FIOCTL_EXTERNAL+7         /*!< Disconnection.
                                                                                                param: none */

#define DGPRS_FIOCTL_CALL_ACCEPTED                      DGPRS_FIOCTL_EXTERNAL+8         /*!< NOT IMPLEMENTED */

#define DGPRS_FIOCTL_GET_INFORMATION                    DGPRS_FIOCTL_EXTERNAL+9         /*!< Get driver informations.
                                                                                                param: T_DGPRS_GET_INFORMATION * gprs_info */

#ifdef GESTION_SMS
#define DGPRS_FIOCTL_SMS_LIST                           DGPRS_FIOCTL_EXTERNAL+10        /*!< Get the list of SMS.
                                                                                                param: T_DGPRS_GET_SMS_LIST * sms_list */

#define DGPRS_FIOCTL_SMS_GET                            DGPRS_FIOCTL_EXTERNAL+11        /*!< Read a SMS
                                                                                                param(in):  int index
                                                                                                param(out): T_DGPRS_GET_SMS * sms*/

#define DGPRS_FIOCTL_SMS_SEND                           DGPRS_FIOCTL_EXTERNAL+12        /*!< Sens a SMS.
                                                                                                param: T_DGPRS_SEND_SMS * sms */
#endif

#define DGPRS_FIOCTL_RETROFIT_MOD                       DGPRS_FIOCTL_EXTERNAL+13        /*!< Put GPRS module in retrofit mode.
                                                                                                param: int timeout (second) */

#define DGPRS_FIOCTL_ALIM                               DGPRS_FIOCTL_EXTERNAL+14        /*!< Turn on/of GPRS module
                                                                                                param: int  on_off */

#define DGPRS_FIOCTL_GET_RSSI                           DGPRS_FIOCTL_EXTERNAL+15        /*!< Get RSSI.
                                                                                                param: int  value_rssi 
                                                                                                        - 0		-113 dBm or less
                                                                                                        - 1		-111 dBm
                                                                                                        - 2...30	-109... -53 dBm
                                                                                                        - 31		-51 dBm or greater
                                                                                                        - 99		not known or not detectable */

#define DGPRS_FIOCTL_SET_PIN2_CODE                      DGPRS_FIOCTL_EXTERNAL+16        /*!< Present the SIM PIN2 code.
                                                                                                param: char code[DGPRS_SIM_PIN_CODE_LGR_MIN+1 -> DGPRS_SIM_PIN_CODE_LGR+1] */

#define DGPRS_FIOCTL_SET_PUK_CODE                       DGPRS_FIOCTL_EXTERNAL+17        /*!< Present the SIM PUK code.
                                                                                                param: char code[DGPRS_SIM_PIN_CODE_LGR_MIN+1 -> DGPRS_SIM_PIN_CODE_LGR+1] */

#define DGPRS_FIOCTL_SET_PUK2_CODE                      DGPRS_FIOCTL_EXTERNAL+18        /*!< Present the SIM PUK2 code.
                                                                                                param: char code[DGPRS_SIM_PIN_CODE_LGR_MIN+1 -> DGPRS_SIM_PIN_CODE_LGR+1] */

#define DGPRS_FIOCTL_MODIFY_PIN_CODE                    DGPRS_FIOCTL_EXTERNAL+19        /*!< Modify the SIM PIN code.
                                                                                                param: char code[2*DGPRS_SIM_PIN_CODE_LGR_MIN+2 -> 2*DGPRS_SIM_PIN_CODE_LGR+2] ("old_pin,new_pin") */

#define DGPRS_FIOCTL_MODIFY_PIN2_CODE                   DGPRS_FIOCTL_EXTERNAL+20        /*!< Modify the SIM PIN2 code.
                                                                                                param: char code[2*DGPRS_SIM_PIN_CODE_LGR_MIN+2 -> 2*DGPRS_SIM_PIN_CODE_LGR+2] ("old_pin,new_pin") */

#define DGPRS_FIOCTL_SET_NETWORK                        DGPRS_FIOCTL_EXTERNAL+21        /*!< Change the current network.
                                                                                                param: char network_id[DGPRS_NETWORK_ID_LGR+1] */

#define DGPRS_FIOCTL_SEARCH_NETWORK                     DGPRS_FIOCTL_EXTERNAL+22        /*!< Scan all network.
                                                                                                param: T_DGPRS_SEARCH_NETWORK */

#define DGPRS_FIOCTL_SEND_CMD_AT                        DGPRS_FIOCTL_EXTERNAL+23        /*!< Send AT command.
                                                                                                param: T_DGPRS_CMD_AT */

#define DGPRS_FIOCTL_SELECT_COM                         DGPRS_FIOCTL_EXTERNAL+24        /*!< Select COM to use for external GPRS modem.
                                                                                                param: char * com ("COM0","COM1","COM2","USB") */

#define DGPRS_FIOCTL_SIM_PRESENT                        DGPRS_FIOCTL_EXTERNAL+25        /*!< Test if SIM is present.
                                                                                                param: none */

#define DGPRS_FIOCTL_GET_IMSI                           DGPRS_FIOCTL_EXTERNAL+26        /*!< Get IMSI.
                                                                                                param: char imsi[DGPRS_IMSI_LGR+1] */

#define DGPRS_FIOCTL_REGISTER_UNSOLICITED_MESSAGE       DGPRS_FIOCTL_EXTERNAL+27        /*!< Register unsolicited message pattern.
                                                                                                param: char pattern[DGPRS_UNSOLICITED_MESSAGE_LGR] */

#define DGPRS_FIOCTL_POLL_UNSOLICITED_MESSAGE           DGPRS_FIOCTL_EXTERNAL+28        /*!< Poll if unsolicited message is arrived.
                                                                                                param: T_DGPRS_UNSOLICITED_MESSAGE */

#define DGPRS_FIOCTL_GET_APN                            DGPRS_FIOCTL_EXTERNAL+29        /*!< Get the current APN.
                                                                                                param: char apn[DGPRS_EXTENDED_APN_LGR+1] */

#define DGPRS_FIOCTL_DEFINE_NETWORK_NAME                DGPRS_FIOCTL_EXTERNAL+30        /*!< Change a network name.
                                                                                                param: T_DGPRS_NETWORK_NAME * network_name */

#define DGPRS_FIOCTL_CDMA_TEST                			DGPRS_FIOCTL_EXTERNAL+31        /*!< For cdma prod test */

#define DGPRS_FIOCTL_FORBIDDEN_1                        DGPRS_FIOCTL_EXTERNAL+32        /*!< DO NOT USE */

#define DGPRS_FIOCTL_GET_ACCESS_TECHNOLOGY              DGPRS_FIOCTL_EXTERNAL+33        /*!< Obtain Current Access Technology (ACCESS_TECHNOLOGY_GSM, ACCESS_TECHNOLOGY_UTRAN)
                                                                                                param: pointer to an int holding the result on return */

#define DGPRS_FIOCTL_GET_CGATT_LAST_ERROR               DGPRS_FIOCTL_EXTERNAL+34        /*!< Obtain the last CME ERROR obtained for the +CGATT=1 command
                                                                                                param: pointer to a string holding the result on return
                                                                                                The error string is automatically cleared after the call */
#define DGPRS_FIOCTL_GET_CGDCONT_LAST_ERROR             DGPRS_FIOCTL_EXTERNAL+35        /*!< Obtain the last CME ERROR obtained for the +CGDCONT=1,"IP","APN",,0,0 command
                                                                                                param: pointer to a string holding the result on return
                                                                                                The error string is automatically cleared after the call */
#define DGPRS_FIOCTL_GET_CGACT_LAST_ERROR               DGPRS_FIOCTL_EXTERNAL+36        /*!< Obtain the last CME ERROR obtained for the +CGACT command
                                                                                                param: pointer to a string holding the result on return
                                                                                                The error string is automatically cleared after the call */

#define DGPRS_FIOCTL_SET_CGATT_TIMEOUT                  DGPRS_FIOCTL_EXTERNAL+37        /*!< Set the timeout for the +CGATT=1 command in 10ms unit (100 means 1 second). If this timeout is set to zero, default timeout applies.
                                                                                                param: pointer to a unsigned int containing the required timeout in seconds. */
#define DGPRS_FIOCTL_SET_CGDCONT_TIMEOUT                DGPRS_FIOCTL_EXTERNAL+38        /*!< Set the timeout for the +CGDCONT=1,"IP","APN",,0,0 command in 10ms unit (100 means 1 second). If this timeout is set to zero, default timeout applies.
                                                                                                param: pointer to a unsigned int containing the required timeout in seconds. */
#define DGPRS_FIOCTL_SET_CGACT_TIMEOUT                  DGPRS_FIOCTL_EXTERNAL+39        /*!< Set the timeout for the +CGACT=1,1 command in 10ms unit (100 means 1 second). If this timeout is set to zero, default timeout applies (connection timeout given in connect fioctl).
                                                                                                param: pointer to a unsigned int containing the required timeout in seconds. */


#define DGPRS_FIOCTL_GET_RADIO_ACCESS_TECHNOLOGY        DGPRS_FIOCTL_EXTERNAL+40        /*!< Get the desired Radio Access Technology in :
                                                                                                    RADIO_ACCESS_TECHNOLOGY_AUTO
                                                                                                    RADIO_ACCESS_TECHNOLOGY_2G_ONLY
                                                                                                    RADIO_ACCESS_TECHNOLOGY_3G_ONLY
                                                                                                    RADIO_ACCESS_TECHNOLOGY_2G_WHEN_AVAILABLE
                                                                                                    RADIO_ACCESS_TECHNOLOGY_3G_WHEN_AVAILABLE
                                                                                                param: pointer to a unsigned int containing the required RAT. */

#define DGPRS_FIOCTL_SET_RADIO_ACCESS_TECHNOLOGY        DGPRS_FIOCTL_EXTERNAL+41        /*!< Set the desired Radio Access Technology in :
                                                                                                    RADIO_ACCESS_TECHNOLOGY_AUTO
                                                                                                    RADIO_ACCESS_TECHNOLOGY_2G_ONLY
                                                                                                    RADIO_ACCESS_TECHNOLOGY_3G_ONLY
                                                                                                    RADIO_ACCESS_TECHNOLOGY_2G_WHEN_AVAILABLE
                                                                                                    RADIO_ACCESS_TECHNOLOGY_3G_WHEN_AVAILABLE
                                                                                                param: pointer to a unsigned int containing the required RAT. */

// Fioctl return value
#define DGPRS_SUCCES                            0       /*!< No error */
#define DGPRS_NO_MORE_CONNECTED                 1       /*!< Not connected to GPRS or GSM */
#define DGPRS_ALREADY_CONNECTED                 2       /*!< Already connected */
#define DGPRS_WRITE_DENIED                      3       /*!< Write denied */
#define DGPRS_NOT_IMPLEMENTED                   4       /*!< Not implemented */
#define DGPRS_BAD_PARAMETER                     5       /*!< Bad parameter */
#define DGPRS_BUSY                              6       /*!< Driver is busy */

 
/*! @brief Mount the GPRS driver for an external equipment.
 * @param serial : serial device to use "USB" "COM0", "COM1", "COM2".
 * @return 0 if no error.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:GPRS_Mount:KSFAM_IOSF:
// \endif
int GPRS_Mount(char* serial);

#endif

/*! @}  */ 

