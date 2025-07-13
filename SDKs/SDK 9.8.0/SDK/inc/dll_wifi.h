/*! @addtogroup KSFAM_WIFI
	* @{
*/

#ifndef __DLL_WIFI_H_INCLUDED__
#define __DLL_WIFI_H_INCLUDED__

/*
======================================================================
					List of Defines
======================================================================
*/

#define DLL_WIFI_ALGO_NONE    (0)			/*!< No cyphering algorythm used */
#define DLL_WIFI_ALGO_WEP64   (1)			/*!< Cyphering algorithm is WEP with 64 bit key */
#define DLL_WIFI_ALGO_WEP128  (2)			/*!< Cyphering algorithm is WEP with 128 bit key */
#define DLL_WIFI_ALGO_WPA_PSK (3)			/*!< Cyphering algorithm is WPA */

#define DLL_WIFI_AUTH_MODE_OPEN   (0)	/*!< Authentication mode is Open */
#define DLL_WIFI_AUTH_MODE_SHARED (1)	/*!< Authentication mode is Shared */

// @see Wifi_GetBootproto
// @see Wifi_SetBootproto
 
#define DLL_WIFI_BOOT_PROTO_DHCP   (0)	/*!< Wifi interface is using DHCP for its IP parameter configuration */
#define DLL_WIFI_BOOT_PROTO_STATIC (1)	/*!< Wifi interface is using static IP parameter configuration */

#define DLL_WIFI_CAP_PRIVACY (0x10)			/*!< Access Point privacy flag */

#define DLL_WIFI_CAP_ESS     (0x0001)		/*!< This is a Access Point (Infrastructure BSS and not AdHoc) */

/*! @} */


/*
======================================================================
			Data Structures Definition
======================================================================
*/


/*! @addtogroup WIFI_AP
	* @{
	*/	
	
/*! @brief Description of an Access Point */
typedef struct {
	unsigned char  bssid[6];        /*!< MAC Address of Access Point */
	unsigned short cap;             /*!< Capabilities flag */
  unsigned char  channel;         /*!< Channel */
  unsigned char  signalStrength;  /*!< Receive Signal Strength */
  unsigned char  signalQuality;   /*!< Receive Signal Quality */
  unsigned char  apMode;          /*!< Working mode of Access Point (b/g) */
	unsigned char  essid[36];       /*!< Name of wireless Network (SSID or ESSID) */
} dll_wifi_access_point_t;


#ifndef DLL_WIFI_MAX_ACCESS_POINT
#define DLL_WIFI_MAX_ACCESS_POINT (64)	/*!< Maximum number of simultaneous Access Points handled by the DLL */
#endif


/*! @brief Scan result */
typedef struct {
	dll_wifi_access_point_t access_point_info[DLL_WIFI_MAX_ACCESS_POINT];		/*!< Informations for each Access Point */
	unsigned int            access_point_count;									/*!< Number of Access points found */
} dll_wifi_access_point_list_t;


/*! @} */


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @addtogroup WIFI_DM
	* @{
	*/	
	
/*! @brief This function must be called once by application before attempting to use any other functionality of the Wifi DLL
 * @return WIFI_OK or a negative error code
 *
 * @link WIFI_DM Back to top @endlink
*/
extern int  wifilib_open(void);



/*! @brief This function is to be called when the application doesn't need to use the Wifi DLL anymore
 * @return WIFI_OK or a negative error code
 *
 * @link WIFI_DM Back to top @endlink
 */ 
extern void wifilib_close(void);


/*! @}  */ 


/*! @addtogroup WIFI_Config
	* @{
	 */ 	

/*! @brief Check is a Wifi device is up and running (either the internal of the external equivalent)
 * @return 0 if no Wifi device has been detected, != 0 else.
 * @note On EFT930W, a few seconds latency can be observed when leaving standby mode (as well as when powering the EFT up),
 * so, on these specific platform, this should be called for a few second before considering no Wifi device is present.
 * 
 * On power up, the time between before control is given to the application should be long enough to hide this issue.
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern int  Wifi_IsDevicePresent(void);


/*! @brief Check is the device is connected to an Access Point
 * @return != 0 when we are connected to the configured Access Point, 0 else.
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern int  Wifi_IsConnected(void);


/*! @brief This function copies the configured ESSID (Wireless Network IDentifier) in the given array.
 * @param essid  : a string representing the name of the wireless network we want to connect to
 * @note The essid array shall be at least 36 byte long.
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_Essid(char *essid);


/*! @brief This function copies the MAC address of the configured Access Point into bssid
 * @param bssid  : an array containing the MAC address of the Access Point we want to connect to
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_Bssid(unsigned char bssid[6]);


/*! @brief This function provides the RSSI for the Access Point the EFT is connected to.
 * @note only relevant when Wifi_IsConnected() returns TRUE.
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern int  Wifi_RSSI(void);


/*! @brief Get coarse grain receive signal indication
 * @return A receive signal indication, from 0 to 5, 0 indicating no reception and 5 perfect reception.
 * @note 
 * - Only relevant when Wifi_IsConnected() returns TRUE.
 * - Used to update the Wifi header.
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern int  Wifi_SignalIndication(void);


/*! @brief Get the MAC address of the Wifi device.
 * @param mac  : pointer to a 6-byte array that will hold the Big Endian Mac Address on return
 * @note In case of a EFT930W configuration, the Mac Address is managed by the configuration file Wlan0.cfg
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_GetMacAddress(unsigned char mac[6]);


/*! @brief Get the IP address of the Wifi network interface.
 * @param ip  : pointer to a 4-byte array that will hold the IP Address on return
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_GetIpAddress(unsigned char ip[4]);


/*! @brief Set the IP address of the Wifi network interface.
 * @param ip  : pointer to a 4-byte array holding the IP Address
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_SetIpAddress(unsigned char ip[4]);


/*! @brief This function copies the netmask of the Wifi network interface.
 * @param netmask  : pointer to a 4-byte array that will hold the subnetwork mask on return
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_GetNetmask(unsigned char netmask[4]);


/*! @brief This function is used to set the netmask of the Wifi network interface.
 * @param netmask  : pointer to a 4-byte array holding the subnetwork mask
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_SetNetmask(unsigned char netmask[4]);


/*! @brief This function copies the gateway of the Wifi network interface.
 * @param gateway  : pointer to a 4-byte array that will hold the gateway IP Address on return
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_GetGateway(unsigned char gateway[4]);


/*! @brief This function is used to set the gateway of the Wifi network interface.
 * @param gateway  : pointer to a 4-byte array holding the gatway IP Address
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_SetGateway(unsigned char gateway[4]);


/*! @brief This function copies the DNS1 address for the Wifi network interface.
 * @param dns1  : pointer to a 4-byte array that will hold the DNS1 IP Address on return
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_GetDNS1(unsigned char dns1[4]);


/*! @brief This function is used to set the DNS1 address for the Wifi network interface.
 * @param dns1  : pointer to a 4-byte array holding the DNS1 IP Address
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_SetDNS1(unsigned char dns1[4]);


/*! @brief This function copies the DNS2 address for the Wifi network interface.
 * @param dns2  : pointer to a 4-byte array that will hold the DNS2 IP Address on return
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_GetDNS2(unsigned char dns2[4]);


/*! @brief This function is used to set the DNS2 address for the Wifi network interface.
 * @param dns2  : pointer to a 4-byte array holding the DNS2 IP Address
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_SetDNS2(unsigned char dns2[4]);


/*! @brief Returns the configuration for the Boot Proto option.
 * @sa DLL_WIFI_BOOT_PROTO_DHCP, DLL_WIFI_BOOT_PROTO_STATIC
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern int  Wifi_GetBootproto(void);


/*! @brief This function is used to set the configuration for the Boot Proto option.
 * @sa DLL_WIFI_BOOT_PROTO_DHCP, DLL_WIFI_BOOT_PROTO_STATIC
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_SetBootproto(int);


/*! @brief Get value for DHCP Gateway negociation option
 * @return TRUE if the DHCP Request includes GATEWAY information (default).
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern int  Wifi_GetDHCPGateway(void);


/*! @brief If set to TRUE the DHCP Negociation will include GATEWAY information (default).
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern int  Wifi_SetDHCPGateway(int);


/*! @brief Get value for the DHCP DNS negociation value
 * @return TRUE if the DHCP Request includes DNS informations (default).
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern int  Wifi_GetDHCPDNS(void);


/*! @brief If set to TRUE the DHCP Negociation will include DNS information (default).
 *
 * @link WIFI_Config Back to top @endlink
 */ 
extern void Wifi_SetDHCPDNS(int);


/*! @}  */ 



/*! @addtogroup WIFI_PM
	* @{
	 */ 	



/*! @brief This function creates a new profile
 * @param profile_name : a const string representing the profile name
 * @param essid   : a const string representing the name of the wireless network we want to connect to
 * @param bssid   : an array containing the MAC address of the Access Point we want to connect to
 * @param algo    : the alogrithm to use with the Access Point (value in DLL_WIFI_ALGO_NONE, DLL_WIFI_ALGO_WEP64, DLL_WIFI_ALGO_WEP128 and DLL_WIFI_ALGO_WPA_PSK)
 * @param auth    : the authentication method to use with the Access Point (value in DLL_WIFI_AUTH_MODE_OPEN, DLL_WIFI_AUTH_MODE_SHARED)
 * @param channel : the Wifi channel to use with the Access Point
 * @param key     : a hexadecimal string representation of the ciphering key (when relevant).
 *          For WPA_PSK this should be a null-terminated passphrase containing [8..63] characters
 *          essid, bssid and channel are obtained from the result of a scan 
 *
 * @sa Wifi_AccessPointScan, Wifi_AccessPointList, Wifi_GetScanResults
 * 
 * @b code @b sample: \ref Code_Add
 *
 * @link WIFI_PM Back to top @endlink
 */ 
extern void Wifi_ProfileAdd(const char *profile_name, const char *essid, const unsigned char bssid[6], const int algo, const int auth, const int channel, const char *key);


/*! @brief This function modifies an existing profile
 * @param profile_name : a const string representing the profile name
 * @param essid        : a const string representing the name of the wireless network we want to connect to
 * @param bssid        : an array containing the MAC address of the Access Point we want to connect to
 * @param algo         : the alogrithm to use with the Access Point (value in DLL_WIFI_ALGO_NONE, DLL_WIFI_ALGO_WEP64, DLL_WIFI_ALGO_WEP128 and DLL_WIFI_ALGO_WPA_PSK)
 * @param auth         : the authentication method to use with the Access Point (value in DLL_WIFI_AUTH_MODE_OPEN, DLL_WIFI_AUTH_MODE_SHARED)
 * @param channel      : the Wifi channel to use with the Access Point
 * @param key          : a hexadecimal string representation of the ciphering key (when relevant).
 *          For WPA_PSK this should be a null-terminated passphrase containing [8..63] characters
 *          essid, bssid and channel are obtained from the result of a scan 
 *
 * @sa Wifi_AccessPointScan, Wifi_AccessPointList, Wifi_GetScanResults
 * 
 * @b code @b sample: \ref Code_Modify
 *
 * @link WIFI_PM Back to top @endlink
 */ 
extern void Wifi_ProfileModify(const char *profile_name, const char *essid, const unsigned char bssid[6], const int algo, const int auth, const int channel, const char *key);


/*! @brief This function select a profile to be the current one.
 *
 * bssid for a profile can be retrieved using Wifi_ProfileGetList().
 * 
 * @b code @b sample: \ref Code_Activate
 *
 * @link WIFI_PM Back to top @endlink
 */ 
extern void Wifi_ProfileSetActive(const unsigned char bssid[6]);


/*! @brief This function removes a profile from the managed profiles.
 *
 * bssid for a profile can be retrieved using Wifi_ProfileGetList().
 *
 * @b NOTICE : even when no more profile exist, the driver can still connect to the last one because it has a copy of the required parameters.
 * 
 * @b code @b sample: \ref Code_Remove
 *
 * @link WIFI_PM Back to top @endlink
 */ 
extern void Wifi_ProfileRemove(const unsigned char bssid[6]);


/*! @brief This function is used to get the list of all currently managed profiles.
 *
 * On return list->access_point_count will contain the number of profiles actually managed.
 *
 * @link WIFI_PM Back to top @endlink
 */ 
extern void Wifi_ProfileGetList(dll_wifi_access_point_list_t *list);


/*! @}  */ 



/*! @addtogroup WIFI_AP
	* @{
	 */ 	
	
	
/*! @brief This function requests a wireless network scan.
 * @return WIFI_OK or a negative error code. 
 * @note Scan results can be obtained with Wifi_AccessPointList() or Wifi_GetScanResults().
 *
 * @link WIFI_AP Back to top @endlink
 */ 
extern int  Wifi_AccessPointScan(void);


/*! @brief This function obtains scan result
 * @param list   : a pointer to a dll_wifi_access_point_list_t object.
 * On return list->access_point_count will contain the number of network actually discovered.
 * @return WIFI_OK
 * @note For consistency, <*list> must be cleared prior to call.
 * @par Example:
 * @code
 * dll_wifi_access_point_list_t list;
 * memset(&list, 0, sizeof(list));
 * Wifi_AccessPointList(&list);
 * @endcode
 *
 * @link WIFI_AP Back to top @endlink
 */ 
extern void Wifi_AccessPointList(dll_wifi_access_point_list_t *list);



#ifndef ETH_ALEN
#   define ETH_ALEN 6		/*!< Ethernet address byte-length */
#endif

#ifndef SSID_MAX_WPA_IE_LEN
#   define SSID_MAX_WPA_IE_LEN 40		/*!< WPA IE max length */
#endif


/*! @brief Informations for an Access Point retrieved by a scan. */
typedef struct {
        unsigned char bssid[ETH_ALEN];             /*!< MAC Address of Access Point */
        unsigned char ssid[34];                    /*!< Access Point ESSID (NULL-terminated string) */
        unsigned int  ssid_len;                    /*!< Length of above string */
        unsigned char wpa_ie[SSID_MAX_WPA_IE_LEN]; /*!< WPA IE broadcasted by this Access Point. Only relevant if wpa_ie_len > 0. */
        unsigned int  wpa_ie_len;                  /*!< Length of above information. If > 0, then this Access Point can do WPA */
        unsigned char rsn_ie[SSID_MAX_WPA_IE_LEN]; /*!< RSN IE broadcasted by this Access Point. Only relevant if rsn_ie_len > 0. */
        unsigned int  rsn_ie_len;                  /*!< Length of above information. If > 0, then this Access Point can do WPA2 (RSN) */
        int freq;                                  /*!< Channel */
        int qual;                                  /*!< Receive Signal Quality */
        int noise;                                 /*!< Receive Signal Noise */ 
        int level;                                 /*!< Receive Signal Level */ 
        int maxrate;                               /*!< Maximum Rate supported by this Access Point (in bit/s, for example 54Mbit/s => 54000000) */
        int mdie_present;													 /*!< Internal use only */
        unsigned char mdie[6];										 /*!< Internal use only */
        unsigned short caps;                       /*!< Capability flags @see DLL_WIFI_CAP_PRIVACY, DLL_WIFI_CAP_ESS */

#ifdef _MSC_VER
        unsigned __int64 tsf;											 /*!< Internal use only */
#else
        unsigned long long tsf;										 /*!< Internal use only */
#endif
} dll_wifi_scan_result_t;



/*! @brief This function obtains scan results with complete information
 * @param list        : a dll_wifi_scan_result array.
 * @param max_results : the number of element in the above array
 * @return 
 * - The actual number of Access Points as found by the last scan.
 * - APs not seen for more than 5 seconds are not returned.
 *
 * @link WIFI_AP Back to top @endlink
 */ 
extern int  Wifi_GetScanResults(dll_wifi_scan_result_t *list, int max_results);



/*
======================================================================
Roaming policies.
We define 4 policies :
- ROAMING_POLICY_STICK_TO_PREFERRED (=> NO_ROAMING) : only connect to preferred Access Point (same ESSID and BSSID)
- ROAMING_POLICY_PREFERRED_ESSID (=> BASIC_ROAMING) : connect to any Access Point having the same ESSID as preferred Access Point
- ROAMING_POLICY_ALL_ALLOWED_BSSID                  : connect to any Access Point having a known BSSID (NOT implemented yet)
- ROAMING_POLICY_ALL_ALLOWED_ESSID                  : connect to any Access Point having a known ESSID (NOT implemented yet)
======================================================================
*/

#define ROAMING_POLICY_STICK_TO_PREFERRED (0)		/*!< only connect to preferred Access Point (same ESSID and BSSID) */
#define ROAMING_POLICY_NO_ROAMING ROAMING_POLICY_STICK_TO_PREFERRED		/*!< only connect to preferred Access Point (same ESSID and BSSID) */

#define ROAMING_POLICY_PREFERRED_ESSID   (1)			/*!< connect to any Access Point having the same ESSID as preferred Access Point */
#define ROAMING_POLICY_BASIC_ROAMING ROAMING_POLICY_PREFERRED_ESSID		/*!< connect to any Access Point having the same ESSID as preferred Access Point */

#define ROAMING_POLICY_ALL_ALLOWED_BSSID (2)		/*!< connect to any Access Point having a known BSSID (NOT implemented yet) */

#define ROAMING_POLICY_ALL_ALLOWED_ESSID (3)		/*!< connect to any Access Point having a known ESSID (NOT implemented yet) */

/*! @}  */ 

#endif // __DLL_WIFI_H_INCLUDED__



/*! @addtogroup Code_Menu
	* @{
	 	
 * @code
 * static void configure_wifi_profiles(void){
 *   int s = 0;
 *   char *choices[8];
 *   int fini = 0;
 *   choices[0] = GetString(WIFI_NEW_PROFILE_MESSAGE);
 *   choices[1] = GetString(WIFI_SET_ACTIVE_PROFILE_MESSAGE);
 *   choices[2] = GetString(WIFI_MODIFY_PROFILE_MESSAGE);
 *   choices[3] = GetString(WIFI_REMOVE_PROFILE_MESSAGE);
 *   choices[4] = NULL;
 *   do {
 *     s = op_selection(GetString(WIFI_PROFILE_MESSAGE), choices, s, 0);
 *     switch (s) {
 *     case 0:
 *      configure_wifi_profile_new();
 *      break;
 *     case 1:
 *      configure_wifi_profile_set_active();
 *      break;
 *     case 2:
 *      configure_wifi_profile_modify();
 *      break;
 *     case 3:
 *      configure_wifi_profile_remove();
 *      break;
 *     default:
 *      fini = 1;
 *      break;
 *     }
 *    } while (!fini);
 * }
 *
 * static void configure_wifi_infos(void){
 *   dll_wifi_access_point_list_t list;
 *   unsigned char tmp[36];
 *   int i;
 *
 *   Wifi_GetMacAddress(tmp);
 *   pprintf("\x1B""E"" Terminal " "\n\x1B""F""" "\n");
 *   pprintf("\xF" "MAC @ : " MAC_STR "\x12" "\n", MAC_2_STR(tmp));
 *   Wifi_Essid((char *)tmp);
 *   pprintf("\xF" "ESSID : %s" "\x12" "\n", tmp);
 *   Wifi_Bssid(tmp);
 *   pprintf("\xF" "BSSID : " MAC_STR "\x12" "\n", MAC_2_STR(tmp));
 *   if(Wifi_IsConnected()){
 *     pprintf("\xF" "Connected" "\x12" "\n");
 *     pprintf("\xF" "Level : %d" "\x12" "\n", Wifi_SignalIndication());
 *     pprintf("\xF" "RSSI : %d" "\x12" "\n", Wifi_RSSI());
 *   }
 *   pprintf("\n");
 *
 *   pprintf("\x1B""E"" Access Point" "\n\x1B""F""" "\n");
 *
 *   Wifi_ProfileGetList(&list);
 *   i = list.access_point_count;
 *   while(i-- > 0){
 *     dll_wifi_access_point_t *info = list.access_point_info + i;
 *     int algo, auth;
 *     pprintf("ESSID: [\xF%s\x12]" "\n", info->essid);
 *     pprintf("BSSID: " MAC_STR "\n", MAC_2_STR(info->bssid));
 *     pprintf("Channel: %2d" "\n", info->channel);
 *     algo = auth = info->cap;
 *     auth >>= 4;
 *     algo &= 0xF;
 *     print_auth(auth);
 *     print_algo(algo);
 *     pprintf("\n");
 *     ttestall(PRINTER, 0);
 *   }
 *   if(0 == list.access_point_count){
 *   pprintf("No Profile");
 *   }
 *   pprintf("\n""\n""\n""\n""\n");
 *   ttestall(PRINTER, 0);
 * }
 *
 * void configure_wifi(void){
 *   int s = 0;
 *   char *choices[4];
 *   int fini = 0;
 *   choices[0] = GetString(WIFI_PROFILE_MESSAGE);
 *   choices[1] = GetString(WIFI_INFO_MESSAGE);
 *   choices[2] = NULL;
 *   do {
 *     s = op_selection(GetString(WIFI_SETUP_MESSAGE), choices, s, 0);
 *     switch (s) {
 *     case 0:
 *      configure_wifi_profiles();
 *      break;
 *     case 1:
 *      configure_wifi_infos();
 *      break;
 *     case OP_SELECTION_COR:
 *      configure_wifi_hidden();
 *      break;
 *     default:
 *      fini = 1;
 *      break;
 *     }
 *   } while (!fini);
 * }
 *
 * static void print_auth(int auth_mode){
 *   const char *message;
 *   if(DLL_WIFI_AUTH_MODE_OPEN == auth_mode){
 *     message = GetString(WIFI_AUTH_MODE_OPEN_MESSAGE);
 *   }else{
 *     message = GetString(WIFI_AUTH_MODE_SHARED_MESSAGE);
 *   }
 *   if(message != NULL){
 *     pprintf("Auth : %s" "\n", my_str_to_upper(message));
 *   }
 * }
 *
 * static void print_algo(int algo){
 *   const char *message = NULL;
 *   if(DLL_WIFI_ALGO_WPA_PSK == algo){
 *     message = "WPA-PSK";
 *   }else if(DLL_WIFI_ALGO_WEP64 == algo){
 *     message = "WEP64";
 *   }else if(DLL_WIFI_ALGO_WEP128 == algo){
 *     message = "WEP128";
 *   }
 *   if(message != NULL){
 *     pprintf("Algo : %s" "\n", message);
 *   }
 * }
 * @endcode
 *
 * @note op_selection() is a function from the HWcnf Dll. 
 *
 * @link WIFI_Code Back to top @endlink


 @}  */ 



/*! @addtogroup Code_Add
	* @{ 	 
	 
 * @code
 * static void configure_wifi_profile_new(void){
 *   _draw_window(GetString(WIFI_AVAILABLE_NETWORKS_MESSAGE));
 *   _draw_centered_string(GetString(WIFI_SCANNING_MESSAGE), 30, _OFF_);
 *   PaintGraphics();
 *   if(0 == Wifi_AccessPointScan()){
 *     dll_wifi_access_point_list_t list;
 *     const char *choices[65];
 *     char bssid_str[64][18];
 *     int i, s = 0;
 *
 *     memset(&list, 0, sizeof(list));
 *     Wifi_AccessPointList(&list);
 *     i = list.access_point_count;
 *     choices[i] = NULL;
 *     while(i-- > 0){
 *       dll_wifi_access_point_t *info = list.access_point_info + i;
 *       if(0 == info->essid[0]){ // non-string => hidden ESSID, display BSSID instead
 *         sprintf(bssid_str[i], MAC_STR, MAC_2_STR(info->bssid));
 *         choices[i] = bssid_str[i];
 *       }else{
 *         choices[i] = info->essid;
 *       }
 *     }
 *     s = op_selection(GetString(WIFI_SELECT_NETWORK_MESSAGE), choices, s, 1);
 *     if(0 <= s){
 *     
 *       dll_wifi_access_point_t *info = list.access_point_info + s;
 *       if(info->cap & DLL_WIFI_CAP_PRIVACY){
 *       int auth = DLL_WIFI_AUTH_MODE_SHARED;
 *       int algo = DLL_WIFI_ALGO_WEP128;
 *         auth = configure_wifi_get_auth_mode(auth);
 *         algo = configure_wifi_get_algo(algo);
 *         if(DLL_WIFI_ALGO_NONE != algo){
 *           unsigned char key[16];
 *           if(configure_wifi_get_key(algo, key) > 0){
 *              Wifi_ProfileAdd(info->essid, info->essid, info-
 *              >bssid, algo, auth, info->channel, key);
 *
 *    draw_message_window(GetString(WIFI_NEW_PROFILE_MESSAGE), OK_STRING, 1, 150);
 *              }
 *          }
 *       }else{
 *            Wifi_ProfileAdd(info->essid, info->essid, info->bssid,
 *            DLL_WIFI_ALGO_NONE, DLL_WIFI_AUTH_MODE_OPEN, info->channel, NULL);
 *            draw_message_window(GetString(WIFI_NEW_PROFILE_MESSAGE), OK_STRING, 1, 150);
 *       }
 *     }
 *   }
 * }
 * @endcode
 *
 * @link WIFI_Code Back to top @endlink
 
 
 @}  */ 
 
 

/*! @addtogroup Code_Activate
	* @{

 * @code
 * static void configure_wifi_profile_set_active(void){
 *    dll_wifi_access_point_list_t list;
 *    const char *choices[65];
 *    char bssid_str[64][18];
 *    int i, s = 0;
 *
 *    Wifi_ProfileGetList(&list);
 *    i = list.access_point_count;
 *    if( i <= 0){
 *      return;
 *    }
 *    choices[i] = NULL;
 *    while(i-- > 0){
 *      dll_wifi_access_point_t *info = list.access_point_info + i;
 *      if(0 == info->essid[0]){ // non-string => hidden ESSID, display BSSID instead
 *        sprintf(bssid_str[i], MAC_STR, MAC_2_STR(info->bssid));
 *        choices[i] = bssid_str[i];
 *      }else{
 *        choices[i] = info->essid;
 *      }
 *    }
 *    s = op_selection(GetString(WIFI_SELECT_NETWORK_MESSAGE), choices, s, 1);
 *    if(0 <= s){
 *      dll_wifi_access_point_t *info = list.access_point_info + s;
 *      Wifi_ProfileSetActive(info->bssid);
 *      draw_message_window(GetString(WIFI_SET_ACTIVE_PROFILE_MESSAGE), OK_STRING, 1, 150);
 *    }
 * }
 * @endcode
 *
 * @link WIFI_Code Back to top @endlink


 @}  */ 




/*! @addtogroup Code_Modify
	* @{

 * @code
 * static void configure_wifi_profile_modify(void){
 *    dll_wifi_access_point_list_t list;
 *    const char *choices[65];
 *    char bssid_str[64][18];
 *    int i, s = 0;
 *
 *    Wifi_ProfileGetList(&list);
 *    i = list.access_point_count;
 *    if( i <= 0){
 *      return;
 *    }
 *    choices[i] = NULL;
 *    while(i-- > 0){
 *      dll_wifi_access_point_t *info = list.access_point_info + i;
 *      if(0 == info->essid[0]){ // non-string => hidden ESSID, display BSSID instead
 *      sprintf(bssid_str[i], MAC_STR, MAC_2_STR(info->bssid));
 *      choices[i] = bssid_str[i];
 *    }else{
 *      choices[i] = info->essid;
 *    }
 * }
 * s = op_selection(GetString(WIFI_SELECT_NETWORK_MESSAGE), choices, s, 1);
 * if(0 <= s){
 *    unsigned char key[16];
 *    dll_wifi_access_point_t *info = list.access_point_info + s;
 *    int auth, algo;
 *    auth = configure_wifi_get_auth_mode(info->cap >> 4);
 *    if(auth < 0){
 *      return;
 *    }
 *    algo = configure_wifi_get_algo(info->cap & 0xF);
 *    if(algo < 0){
 *      return;
 *    }
 *    if(DLL_WIFI_ALGO_NONE != algo){
 *      if(configure_wifi_get_key(algo, key) <= 0){
 *        return;
 *     }
 *   }
 *   Wifi_ProfileModify(info->essid, info->essid, info->bssid, algo, auth, info->channel, key);
 *   draw_message_window(GetString(WIFI_MODIFY_PROFILE_MESSAGE), OK_STRING, 1,150);
 *  }
 * }
 * @endcode
 *
 * @link WIFI_Code Back to top @endlink


 @}  */ 




/*! @addtogroup Code_Remove
	* @{
	 
 * @code
 * static void configure_wifi_profile_remove(void){
 *    dll_wifi_access_point_list_t list;
 *    const char *choices[65];
 *    char bssid_str[64][18];
 *    int i, s = 0;
 *
 *    Wifi_ProfileGetList(&list);
 *    i = list.access_point_count;
 *    if( i <= 0){
 *      return;
 *    }
 *    choices[i] = NULL;
 *    while(i-- > 0){
 *      dll_wifi_access_point_t *info = list.access_point_info + i;
 *      if(0 == info->essid[0]){ // non-string => hidden ESSID, display BSSID instead
 *        sprintf(bssid_str[i], MAC_STR, MAC_2_STR(info->bssid));
 *        choices[i] = bssid_str[i];
 *      }else{
 *        choices[i] = info->essid;
 *      }
 *   }
 *   s = op_selection(GetString(WIFI_SELECT_NETWORK_MESSAGE), choices, s, 1);
 *   if(0 <= s){
 *     dll_wifi_access_point_t *info = list.access_point_info + s;
 *     Wifi_ProfileRemove(info->bssid);
 *    draw_message_window(GetString(WIFI_REMOVE_PROFILE_MESSAGE), OK_STRING, 1, 150);
 *   }
 * }
 * @endcode
 *
 * @link WIFI_Code Back to top @endlink


 @}  */
 


/*! @addtogroup Code_Util
	* @{

 * @code
 * #ifndef MAC_STR
 * # define MAC_STR "%02X:%02X:%02X:%02X:%02X:%02X"
 * #endif
 * #ifndef MAC_2_STR
 * # define MAC_2_STR(A) (A)[0],(A)[1],(A)[2],(A)[3],(A)[4],(A)[5]
 * #endif
 *
 * static void configure_wifi_hidden(void){
 *   if (password_entry("Fonction", "Impossible", "7581") == PASSWORD_ENTRY_OK) {
 *   }
 * }
 * static int configure_wifi_get_algo(int current_algo){
 *   const char *choices[5];
 *
 *   // ATTENTION : do not change the order, correct behaviour depends upon it !!!
 *   choices[DLL_WIFI_ALGO_NONE]    = "NONE";    // #define DLL_WIFI_ALGO_NONE    (0)
 *   choices[DLL_WIFI_ALGO_WEP64]   = "WEP64";   // #define DLL_WIFI_ALGO_WEP64   (1)
 *   choices[DLL_WIFI_ALGO_WEP128]  = "WEP128";  // #define DLL_WIFI_ALGO_WEP128  (2)
 *   choices[DLL_WIFI_ALGO_WPA_PSK] = "WPA_PSK"; // #define DLL_WIFI_ALGO_WPA_PSK (3)
 *   choices[4] = NULL;
 *   return(op_selection(GetString(WIFI_CYPHER_MODE_MESSAGE), choices, current_algo, 1));
 * }
 * static int configure_wifi_get_auth_mode(int current_mode){
 *    const char *choices[3];
 *
 *    // ATTENTION : do not change the order, correct behaviour depends upon it !!!
 *    choices[DLL_WIFI_AUTH_MODE_OPEN] = GetString(WIFI_AUTH_MODE_OPEN_MESSAGE);
 *    // #define DLL_WIFI_AUTH_MODE_OPEN (0)
 *    choices[DLL_WIFI_AUTH_MODE_SHARED] = GetString(WIFI_AUTH_MODE_SHARED_MESSAGE);
 *    // #define DLL_WIFI_AUTH_MODE_SHARED (1)
 *    choices[2] = NULL;
 *
 *    return(op_selection(GetString(WIFI_AUTH_MODE_MESSAGE), choices, current_mode, 1));
 *  }
 * #if 0
 * 
 * // remove a char at position (<*index> - 1) in the <*len> char string <str>, updating *index and *len if needed.
 * // Note : terminating '\0' is also moved to ensure proper ending; If *len <= 0, p <= 0 or *index > *len, do nothing.
 * 
 * static void remove_car(char *str, int *len, int *index){
 *    int l = *len;
 *    int p = *index;
 *    if((l > 0) && (p <= l) && (p > 0)){
 *      char *dst;
 *      char *src;
 *      int r = (l - p) + 1;
 *      p--;
 *      *index = p;
 *      dst = str + p;
 *      src = dst + 1;
 *      while(r-- > 0){
 *        *dst++ = *src++;
 *      }
 *      l--;
 *      *len = l;
 *     }
 * }
 * 
 * // Insert a char at position <*index> in the <*len> char string <str>, updating *index and *len if needed.
 * // Note : terminating '\0' is also moved to ensure proper ending; If *index > *len or if *len >= max_len, do nothing.
 * 
 * static void insert_car(char *str, int c, int *len, int *index, int max_len){
 *    int l = *len;
 *    int p = *index;
 *    if((p <= l) && (l < max_len)){
 *    char *dst = str + l;
 *    char *src = dst - 1;
 *    int r = (l - p);
 *    while(r-- > 0){
 *      *dst-- = *src--;
 *    }
 *    *dst = c;
 *    *index = p + 1;
 *    *len = l + 1;
 *   }
 * }
 * #endif
 *
 * 
 * // Enter exactly <str_len> hexa digits (up to 32 chars)
 *   
 *   //====================
 *   //	 WEP 128 Key
 *   //   Enter 26 digits 
 *   //     FFFFFFFFFF01
 *   //       12 / 26  
 *   //====================
 *
 * // @return number of char entered, or a negative error code
 * // -1 : empty entry (emptied (yellow))
 * // -2 : cancel (red)
 * 
 * static int configure_wifi_enter_hexa_key(const char *title, const char *first_line,
 * char *key_str, int str_len){
 *    int a_renvoyer = 0;
 *    int len;
 *    int letter = 'A';
 *    int in_letter = 0;
 *    key_str[str_len] = '\0'; // just in case ...
 *    len = strlen(key_str);
 *    for(;;){
 *      char tmp_str[32];
 *      int c;
 *      _draw_window(title);
 *      _draw_centered_string(first_line, 10, _OFF_);
 *      if(len > 16){
 *        char sauv = key_str[16];
 *        key_str[16] = '\0';
 *        _DrawString(key_str, 10, 25, _OFF_);      // _draw_centered_string(key_str, 25, _OFF_);
 *        key_str[16] = sauv;
 *        _DrawString(key_str + 16, 10, 35, _OFF_); // _draw_centered_string(key_str + 16, 35, _OFF_);
 *      }else{
 *        _DrawString(key_str, 10, 25, _OFF_);      // _draw_centered_string(key_str, 25, _OFF_);
 *      }
 *      sprintf(tmp_str, "%2d / %2d", len, str_len);
 *      _draw_centered_string(tmp_str, 50, _OFF_);
 *      PaintGraphics();
 *      if(ttestall(KEYBOARD, 50)){
 *        int stay_in_letter = 0;
 *        c = getchar();
 *        if(('0' <= c) && (c <= '9')){
 *          if(len < str_len){
 *            key_str[len] = c;
 *            len++;
 *            key_str[len] = '\0';
 *           }
 *        }else if(T_CORR == c){
 *          if(len > 0){
 *          len--;
 *          key_str[len] = '\0';
 *          }
 *        }else if((T_SKBAS == c) || (T_SKHAUT == c)){
 *          stay_in_letter = 1;
 *          if(in_letter){
 *            if(T_SKHAUT == c){
 *             if(letter < 'F'){
 *               letter++;
 *          }else{
 *               letter = 'A';
 *          }
 *     }else{
 *      if(letter > 'A'){
 *        letter--;
 *     }else{
 *        letter = 'F';
 *     }
 *   }
 * }
 * in_letter = 1;
 * key_str[len] = letter;
 * key_str[len + 1] = '\0';
 * }else if(T_ANN == c){
 * a_renvoyer = -2;
 * break;
 * }else if(T_VAL){
 * if(in_letter){
 * in_letter = 0;
 * len++;
 * }else{
 * if(len == str_len){
 * return(len);
 * }
 * }
 * }
 * if(!stay_in_letter){
 * in_letter = 0;
 * }
 * }
 * }
 * return(a_renvoyer);
 * }
 * static int configure_wifi_hex_string_to_key(const char *key_str, int str_len,
 * unsigned char *key){
 *    int i = str_len >> 1;
 *    const char *src = key_str;
 *    unsigned char *dst = key;
 *    while(i-- > 0){
 *      int tmp = hex_digit_value(*src++);
 *      int val;
 *      if(tmp < 0){
 *      break;
 *     }
 *     val = tmp << 4;
 *     tmp = hex_digit_value(*src++);
 *     if(tmp < 0){
 *       break;
 *    }
 *    val += tmp;
 *    *dst++ = val;
 *   }
 *  return((str_len >> 1) - i);
 * }
 *
 *
 * static int configure_wifi_get_key(int algo, unsigned char *key){
 *    int a_renvoyer = 0;
 *    char key_str[32];
 *    key_str[0] = '\0';
 *    switch(algo){
 *    case DLL_WIFI_ALGO_WEP64:
 *      a_renvoyer =
 *    configure_wifi_enter_hexa_key(GetString(WIFI_WEP_64_KEY_MESSAGE),
 *    GetString(WIFI_ENTER_10_DIGITS_MESSAGE), key_str, 10);
 *    if(a_renvoyer > 0){
 *     a_renvoyer = configure_wifi_hex_string_to_key(key_str, 10, key);
 *    }
 *    break;
 *    case DLL_WIFI_ALGO_WEP128:
 *    a_renvoyer =
 *    configure_wifi_enter_hexa_key(GetString(WIFI_WEP_128_KEY_MESSAGE),
 *    GetString(WIFI_ENTER_26_DIGITS_MESSAGE), key_str, 26);
 *    if(a_renvoyer > 0){
 *    a_renvoyer = configure_wifi_hex_string_to_key(key_str, 26, key);
 *    }
 *    break;
 *    case DLL_WIFI_ALGO_WPA_PSK:
 *    break;
 *    }
 *    return(a_renvoyer);
 *  }	
 * @endcode
 *
 * @link WIFI_Code Back to top @endlink


 @}  */ 


