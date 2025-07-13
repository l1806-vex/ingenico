#ifdef __cplusplus
extern "C" {
#endif

#ifndef __OEM_DGPRS_H_INCLUDED__
#define __OEM_DGPRS_H_INCLUDED__

#include "oem_dgprs_def.h"
#ifdef __FRAMEWORK_TELIUM_2__
#include "oem_dgprs_deprecated.h"
#endif

/*! @addtogroup KSFAM_IOSF
 * @{
 */ 

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
typedef struct {
    binaire mcc;                                /*!< Mobile Country Code */
    binaire mnc;                                /*!< Mobile Network Code */
    char long_alpha_id[DGPRS_NETWORK_NAME_LGR]; /*!< Long alphanumeric name */
} T_DGPRS_NETWORK_MCC_MNC_AND_NAME;

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

#define DGPRS_FIOCTL_SET_FUNC_ENABLE                    DGPRS_FIOCTL_EXTERNAL+3         /*!< Enable/Disable GSM and GPRS.
                                                                                        param: int (DGPRS_MASK_FUNC_NONE, DGPRS_MASK_FUNC_GSM, ...) */
#define DGPRS_FIOCTL_GET_INFORMATION                    DGPRS_FIOCTL_EXTERNAL+9         /*!< Get driver informations. Data available only if the driver is ON.
                                                                                                param: T_DGPRS_GET_INFORMATION * gprs_info */

#define DGPRS_FIOCTL_GET_RSSI                           DGPRS_FIOCTL_EXTERNAL+15        /*!< Get RSSI.
                                                                                                param: int  value_rssi
                                                                                                        - 1		-111 dBm
                                                                                                        - 2...30	-109... -53 dBm
                                                                                                        - 31		-51 dBm or greater
                                                                                                        - 99		not known or not detectable */


#define DGPRS_FIOCTL_SET_NETWORK                        DGPRS_FIOCTL_EXTERNAL+21        /*!< Change the current network.
                                                                                                param: char network_id[DGPRS_NETWORK_NAME_LGR+1] */



#define DGPRS_FIOCTL_SEARCH_NETWORK                     DGPRS_FIOCTL_EXTERNAL+22        /*!< Scan all network.
                                                                                                param: T_DGPRS_SEARCH_NETWORK */

#define DGPRS_FIOCTL_GET_IMSI                           DGPRS_FIOCTL_EXTERNAL+26        /*!< Get IMSI.
                                                                                                param: char imsi[DGPRS_IMSI_LGR+1] */

// Fioctl return value
#define DGPRS_SUCCES                            0       /*!< No error */
#define DGPRS_NO_MORE_CONNECTED                 1       /*!< Not connected to GPRS or GSM */
#define DGPRS_ALREADY_CONNECTED                 2       /*!< Already connected */
#define DGPRS_WRITE_DENIED                      3       /*!< Write denied */
#define DGPRS_NOT_IMPLEMENTED                   4       /*!< Not implemented */
#define DGPRS_BAD_PARAMETER                     5       /*!< Bad parameter */
#define DGPRS_BUSY                              6       /*!< Driver is busy */

/*! @}  */


#endif     // __OEM_DGPRS_H_INCLUDED__

#ifdef __cplusplus
}
#endif
