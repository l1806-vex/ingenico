#ifdef __cplusplus
extern "C" {
#endif

#ifndef __OEM_DGPRS_DEF_H_INCLUDED__
#define __OEM_DGPRS_DEF_H_INCLUDED__

/*! @addtogroup KSFAM_IOSF
 * @{
 */ 
 
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

/*! @brief Boolean type define */
typedef unsigned int binaire;

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
        
        void *com2_status;   /*!< COM file handle */

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

/*! @brief GPRS registration information */
typedef struct {
    int creg;   // Last answer to AT+CREG?
    int cgreg;  // Last answer to AT+CGREG?
} registration_info_s;

/*! @}  */ 


#endif   // __OEM_DGPRS_DEF_H_INCLUDED__

#ifdef __cplusplus
}
#endif
