/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

#ifndef OEM_MANAGER_H
#define OEM_MANAGER_H

// --------------------------------
// ON N'UTILISE PAS LE SEMI-HOSTING
// --------------------------------
//#pragma import(__use_no_semihosting_swi)
#ifndef _GSIM_

// includes supprimes pour l'analyse GSIM
#include <string.h>
#include <stdarg.h> 

#endif
// suppression des majuscules pour l'analyse GSIM
#include "basearm.h"
//#include "noy_cfg.h" // pour OS_k_TICK
#include "xecarm.h"

//#include "api.h"

#include "oem_public.h"
#include "gprs_lib.h"

//! \brief Define a status.
typedef int  STATUS;

// recuperes dans std_c.h
//! \brief Re-define an unsigned char.
typedef   unsigned char       Uchar;
//! \brief Re-define an unsigned short.
typedef   unsigned short      U16bit;


// Trace
// pour eviter de tirer trace_sap_id_t
// void trace(unsigned int id,unsigned int data_size,void *data);

#ifndef _SIMULPC_
#if defined(__cplusplus) || defined(_INTERNAL_REDEF_)
	#define eft_fputc(a,b) eft_putc(a,b)
#else
	#define fputc(a,b) putc(a,b)
#endif
#endif
#if defined(__cplusplus) || defined(_INTERNAL_REDEF_)
#define eft_fgetc(a)   eft_getc(a)
#else
#define fgetc(a)   getc(a)
#endif

/*! @} **/
//! \addtogroup KSFAM_SV
//! @{

//! \brief This function manage DTR signal
//! \param val : ON or OFF.
//! \return None.
//! \par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 96) if function does not exist
// \if SIMULATION
//  @GSIM_F:cde_com0:KSFAM_SV:
// \endif
void cde_com0(unsigned char val);
//! @}

/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/
#define CBR_1200       1200
#define CBR_2400       2400
#define CBR_4800       4800
#define CBR_9600       9600
#define CBR_19200      19200
#define CBR_38400      38400
#define CBR_57600      57600
#define CBR_115200     115200

/************************************************/
// visu.c
// int nb_lig_max(void); Pas connu ?
// int nb_col_max(void);

/************************************************/
// clavier.c
#define NAVI_OK  	T_SKVAL
#define NAVI_CLEAR 	T_SKCLEAR
#define UP  		T_SKHAUT
#define DOWN  		T_SKBAS

/************************************************/
// fonctions Cam
#undef PB_COMM
#define PB_COMM 0x29  /* PB_DIALOGUE ou PB_PARITE */

/*! @brief define a PIN code.*/
typedef struct
       {
        unsigned char length ;						/*!< length of the PIN code.*/
        unsigned char value[8];						/*!< value of the PIN code.*/
       } PIN_CODE ;

/*! @brief Response of the card power on.*/
typedef struct
{
   unsigned char statusword1;						/*!< first response byte SW1*/
   unsigned char statusword2;						/*!< second response byte SW2*/
   unsigned char length;								/*!< length*/
   unsigned short int ad_zone;					/*!< address of the card*/
   unsigned char ins;										/*!< ins*/
   unsigned char cr_couche_basse;				/*!< cr_couche_basse : low layer report.*/
} DIAGNOSTIC_CAM;


/*! @brief Define a transpac address.*/
typedef char T_TRANSPAC [15]; /* pour Param.h */

/*! @brief Define a contract.*/
typedef char T_CONTRAT  [10]; /* pour Param.h */

/*! @brief Define a call number.*/
typedef char T_NOAPPEL [35];

/*! @brief Define the type of the network.*/
typedef char TYPE_RES;

/*! @brief Define a software number.*/
typedef char T_NOLOGICIEL [8];

/* utilisation du telechargeur */

#define VAL_NONPRESENT 0

#define V22 '0'
#define VIP '1'
#define VIP_EXT '2'

#define BELL212 '2'
#define BELL103 '3'
#define TYPE_MODEM V22
#define INTERACTIF '1'
#define PASSIF '0'

#define RTC      0
#define TMSIPEXT 0xF8
#define TMSEXT   0xF9
#define TMSIPRTC 0xFA
#define TMSGPRS  0xFB
#define TMSGSM   0xFC
#define TMSRNIS  0xFD
#define TMSIP    0xFE
#define X25      0xFF

#define CLE_DLE    1
#define CLE_DLE_90 2

//#define EVOL -1   ????
//#define MAJ 0

/*! @brief Define the old download structure.*/
typedef struct
{
   char type_modem;											/*!< modem type*/
   T_NOAPPEL     t_noappel;							/*!< number to call*/
   TYPE_RES      reseau;								/*!< network type*/
   T_TRANSPAC    t_transpac;						/*!< transpac address*/
   char 					appel;								/*!< call ? Y/N*/
   T_CONTRAT     t_nocontrat;						/*!< contract number*/
   T_NOLOGICIEL  t_nologiciel;					/*!< software number*/
   char *message;												/*!< message.*/
} S_OLD_PARAM_TLCHGT;   

/*! @brief Define the new download structure.*/
typedef struct
{
  S_OLD_PARAM_TLCHGT param;									/*!< old download parameters*/
  char           t_nologiciel[15+1];				/*!< software number.*/
  char           messagemdp[100+1];					/*!< message to send to MDP*/
} S_NEW_PARAM_TLCHGT;   

/*! @brief Define the download parameters.*/
typedef struct
{
  //V22 pour compatibilite             
  //VIP pour nouvelle interface         
  char           type_modem;						/*!< modem type : \li V22 for compatibility, \li VIP for new interface.*/
  T_NOAPPEL      t_noappel;							/*!< call number*/
  TYPE_RES       reseau;								/*!< network type*/
  T_TRANSPAC     t_transpac;						/*!< transpac address*/
  char           appel;									/*!< call ? Y/N*/
  T_CONTRAT      t_nocontrat;						/*!< contract number*/
  T_NOLOGICIEL   t_nologiciel;					/*!< software number.*/
  char          *message;								/*!< message*/


  // Ce champs est a prendre en compte                   
  // si param.t_nologiciel commence par {0x01,0x02,0x03} 
  char           nologiciel[15+1];					/*!< software number. To take in account only if param.t_nologiciel begins with {0x01,0x02,0x03}.*/
  
  //A prendre en compte quoiqu'il arrive 
  char           messagemdp[100+1];					/*!< message to send to MDP*/
  
  // Ces parametres sont a prendre en compte 
  // si reseau = RNIS                        
  unsigned int   liaison_serie;						/*!< To take in account only if reseau=RNIS.*/
  
  //Ces parametres sont a prendre en compte 
  //si type_modem = VIP                     
  unsigned int   ip;											/*!< IP address. To take in account only if type_modem=VIP or VIP_EXT.*/
  unsigned int   port;										/*!< port (xxxx) To take in account only if type_modem=VIP.*/
  unsigned char  login[22+1];							/*!< login. To take in account only if type_modem=VIP.*/
  unsigned char  password[22+1];					/*!< password. To take in account only if type_modem=VIP.*/
  unsigned char  apn[GPRS_APN_LGR+1];			/*!< To take in account only if type_modem=VIP.*/
  unsigned char  SslProfileName[11];              /*!< SSL profile with \\0. Must be fill with \\0 if SSL must not be used */
  unsigned char  Adress[256];  				   /*!< IP adress or domain name with \\0 */
} S_PARAM_TLCHGT;   

			
#define CRC  CRC16												/*!< This type define a CRC.*/

 /* valeur du code ASCII des touches */     
 #define F1  T_SK1
 #define SK1 T_SK1
 #define F2  T_SK2
 #define SK2 T_SK2
 #define F3  T_SK3
 #define SK3 T_SK3
 #define F4  T_SK4
 #define SK4 T_SK4

 #define N0 T_NUM0 
 #define N1 T_NUM1
 #define N2 T_NUM2
 #define N3 T_NUM3
 #define N4 T_NUM4
 #define N5 T_NUM5
 #define N6 T_NUM6
 #define N7 T_NUM7
 #define N8 T_NUM8
 #define N9 T_NUM9
 
 #define POINT T_POINT
 #define T_F   T_SK10
 #define APAP  T_APAP

//utilisation du lecteur piste ISO2  
#define ISO_OK    0  // recopie de iso2def.h sous clearcase le 13 mai 2002 
#define DEF_SEP   1  // recopie de iso2def.h sous clearcase le 13 mai 2002 
#define DEF_PAR   2  // recopie de iso2def.h sous clearcase le 13 mai 2002 
#define DEF_LRC   3  // recopie de iso2def.h sous clearcase le 13 mai 2002 
#define DEF_LUH   4  // recopie de iso2def.h sous clearcase le 13 mai 2002 
#define DEF_NUM   5  // recopie de iso2def.h sous clearcase le 13 mai 2002 
#define NO_DATA   6  // recopie de iso2def.h sous clearcase le 13 mai 2002 

#define Defaut_Separateur (unsigned char)1   // recopie de iso2def.h sous clearcase le 13 mai 2002 
#define Defaut_Parite     (unsigned char)2   // recopie de iso2def.h sous clearcase le 13 mai 2002 
#define Defaut_LRC        (unsigned char)3   // recopie de iso2def.h sous clearcase le 13 mai 2002 
#define Defaut_Luhn       (unsigned char)4   // recopie de iso2def.h sous clearcase le 13 mai 2002 
#define Defaut_Numericite (unsigned char)5   // recopie de iso2def.h sous clearcase le 13 mai 2002 

#define Data_Available 1   // recopie de iso2def.h sous clearcase le 13 mai 2002 
#define Reading        2   // recopie de iso2def.h sous clearcase le 13 mai 2002 
#define Closed         3   // recopie de iso2def.h sous clearcase le 13 mai 2002 
#define No_Data        6   // recopie de iso2def.h sous clearcase le 13 mai 2002 




/*! @brief This routine returns the luhn key of a string. 
 *
 *	The length of the string is given as a parameter. 
 * @param pt_str : string.
 * @param str_length : string length.
 * @return luhn key
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:cle_luhn:KSFAM_AUTRES_MANAGER:0x11
//  @GSIM_A:1:DATA_SIZE(str_length)
// \endif
extern unsigned char   cle_luhn(unsigned char *pt_str,unsigned char str_length);
/*! @} **/

/*! @addtogroup KSFAM_SV
	* @{
**/
/* valeurs possibles du champ application_type dans le type object_info_t */
#define OEM                0
#define COM                1
#define SEQ                2
#define USER               3
/* Definitions des logiciels */
#define TYPE_LOG_ACTIVATION     1
#define TYPE_LOG_CB             3
#define TYPE_LOG_CHEQUE         4
#define TYPE_LOG_AMEX           5
#define TYPE_LOG_CETDIS         6
#define TYPE_LOG_DINERS         7
#define TYPE_LOG_COFINOGA       8
#define TYPE_LOG_CETNCB         9
#define TYPE_LOG_JCB            10
#define TYPE_LOG_ACCORDFINANCE  12
#define TYPE_LOG_CBEMV          16
#define TYPE_LOG_VAD            26
#define TYPE_LOG_MONEO          40
#define TYPE_LOG_FINTRAX        182
#define TYPE_LOG_CUP            183
#define TYPE_LOG_PLBS           188
#define TYPE_LOG_CUP_BPOP       125
#define TYPE_LOG_FRANFINANCE    202
#define MSG_FILE_TYPE         0xAC36
#define MSG_FILE_TYPE1        0x5962
#define TYPE_LOG_IPA280       0xB3BA
#define TYPE_LOG_PACK           2
#define TYPE_LOG_SDK           0xACBF

#define PARAM_FILE_TYPE '0'
#define APPLI_TYPE      '1'
#define DLL_TYPE        '2' 
#define DRIVER_TYPE     '3'

#define TYPE_DRV_GPRS     131

#define PARAM_FILE_CGUI 0xB3B7
#define PARAM_FILE_GRAPHIC_MANAGER 0xB3B7


// C'est dans Diag_Def.h du Systeme
//#define EFT30P            0x30
//#define TWIN30            0x38
//#define X930              0x34

/* valeurs possibles du type FLAG_CHGT (cf fct first_init */

//#define CHGT_OUI 0xFF    ???
//#define CHGT_NON 0

#ifndef GESTIONNAIRE
#define read_date      SV_read_date
#define write_date     SV_write_date
#define power_down     SV_power_down
#define input_command  SV_input_command
#define output_command SV_output_command
#define power_on       SV_power_on
#endif


/*! @brief This function is used to shutdown the card per standard ISO 7816-3.
 * @param handle : Card flow address.
  * @return Returns 0 if function has been correctly executed, or 1 if card has already been removed .
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 19) if function does not exist
 *
 * @link KSFAM_SV Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:SV_power_down:KSFAM_SV:0x02
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
// \endif
int  SV_power_down(FILE *handle);



/*! @brief This function is used to execute an input command per standard ISO 7816-3. 
//! The function returns control following execution. 
 * @param handle : Card flow address.
 * @param inputcommand : Address of structure of input command.
 * @return Returns : 
 * - 0 if function has been correctly executed 
 * - 1 if card is absent ( returned only on CAM0, CAM1 ) 
 * - 3 if card is silent 
 * - 4 if VDC voltage fault detected 
 * - 5 if VPP problem detected 
 * - 6 if card communication fault detected 
 * - 7 if card has been removed 
 * - 29Hex if card communication fault detected 
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 20) if function does not exist
 *
 * @note The header comprises 5 bytes : 
 * - application class 
 * - instruction code 
 * - P1 card parameter 
 * - P2 card parameter 
 * - length of data to write into the card from 0 to 248. 
 * - The status words can only be accessed provided the function returns 0. 
 * - These are updated by the operating system in the input structure. 
 *
 * @link KSFAM_SV Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:SV_input_command:KSFAM_SV:0x03
//  @GSIM_S:SV_input_command:E_SV_input_command
// \endif
int  SV_input_command(FILE *handle,COMMAND_CAM *inputcommand);


/*! @brief This function is used to execute an output command per standard ISO 7816-3. 
 * @param handle : Card flow address.
 * @param outputcommand : Address of structure of output command.
 * @return Returns : 
 * - 0 if function has been correctly executed 
 * - 1 if card is absent ( returned only on CAM0, CAM1 ) 
 * - 3 if card is silent 
 * - 4 if VDC voltage fault detected 
 * - 5 if VPP problem detected 
 * - 6 if card communication fault detected 
 * - 7 if card has been removed 
 * - 29Hex if card communication fault detected 
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 21) if function does not exist
 *
 * @note The header comprises 5 bytes : 
 * - application class 
 * - instruction code 
 * - P1 card parameter 
 * - P2 card parameter 
 * - length of data to read from the card from 0 to 248. 
 * The status words are only significant provided the function returns to 0. 
 * These are updated by the operating system in the input structure. 
 *
 * @link KSFAM_SV Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:SV_output_command:KSFAM_SV:0x04
//  @GSIM_S:SV_output_command:E_SV_output_command
// \endif
int  SV_output_command(FILE *handle,COMMAND_CAM *outputcommand);


/*! @brief This function is used to switch the card on per standard ISO 7816-3.
 * @param handle : card flow address.
 * @param historical : read address for card history data generated by the reset historical.
 * @return Returns : 
 * - 0 if function has been executed correctly 
 * - 1 if card is absent ( returned only on CAM0, CAM1 ) 
 * - 2 if card has not been processed 
 * - 3 if card does not reply to reset 
 * - 4 if VDC voltage fault detected 
 * - 5 if VPP problem detected 
 * - 6 if card communication fault detected 
 * - 7 if card has been removed 
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 22) if function does not exist
 *
 * @note the card historical data may be : 
 * - Manufacturer's identifier 
 * - Mask number 
 * - Lock word 
 * - Status word 1 
 * - Status word 2 
 * - The history data are only recovered provided the function returns 0. 
 * - The HISTORIC structure contains the length (up to 15 characters) and the history data. 
 *
 * @link KSFAM_SV Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:SV_power_on:KSFAM_SV:0x01
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
// \endif
int  SV_power_on(FILE *handle,HISTORIC *historical);


/*! @brief This function is used to read the date in the terminal's calendar.
 * @param date : Structure return address.
 * @return Returns 0 if function has been correctly executed or -1 if date is incoherent.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 23) if function does not exist
 *
 * @link KSFAM_SV Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:SV_read_date:KSFAM_SV:0x05
//  @GSIM_A:1:ONE_POINTER
// \endif
int  SV_read_date(DATE *date);


/*! @brief This function is used to program the terminal calendar.
 * @param date : Structure return address.
 * @return 
 * - 0 if function has been correctly executed
 * - -1 if date is incoherent.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 24) if function does not exist
 *
 * @link KSFAM_SV Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:SV_write_date:KSFAM_SV:0x06
//  @GSIM_A:1:ONE_POINTER
// \endif
int  SV_write_date(DATE *date);
/*! @} **/



/*! @addtogroup KSFAM_M2OS
	* @{
**/

/*! @brief This function can call a service.
 * @param num_appli : Application number 
 * @param service : Service number 
 * @param data_size : Data size to be exchanged between application ( this is because there is no way to read from the caller due to firewalls).
 * @param data : Data address to be exchanged 
 * @param ret_code : Returned value from the called service 
 * @return 
 * - 0 : successful 
 * - 5 : task context error 
 * - 1 : no more resources to allocate a stack 
 * @note Data area to be exchanged between applications must be contiguous and does not contain any 
 * pointer. This area is used as an input or output from the service : the service provider 
 * may read or write into this data area. 
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 86) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:USR_ServiceCall:KSFAM_M2OS:0x73
//  @GSIM_A:4:DATA_SIZE(data_size)
//  @GSIM_A:5:ONE_POINTER
// \endif
extern int USR_ServiceCall(unsigned short num_appli, unsigned short service, unsigned int data_size, void* data, int *ret_code);

#define ServiceCall    USR_ServiceCall

//! \brief Define a pointer on a function to fork.
typedef unsigned short (*PFONCFORK) (void);

#define crckey(a, b)   (unsigned short)((calcrc((a), (b)) ^ (unsigned short)0x1234) & 0x00FF)
#define memclr(a, b)   memset((a), 0, (b))
/*! @} **/

/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

/*! @brief This routine return absolute value
*- brief 
*- param car : character to convert
*- return absolute value
 *
 * @link KSFAM_AUTRES Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:abs:KSFAM_AUTRES_MANAGER:
// \endif
extern int  abs( int car);
/*! @} **/


/*! @addtogroup KSFAM_M2OS
	* @{
**/

/*! @brief Remote activity completed */
#define STATUS_MDP_OK	    0	
/*! @brief No activity completed */
#define STATUS_MDP_PAS_MAJ  1 
/*! @brief Unknown activity */
#define STATUS_MDP_INCID    2

/*! @brief This function is used to Start a download activity.
 * @param Download  Structure.
 * @return Download report.\n For CallHost Error (see callhost.h for detail):\n
 * - CALL_HOST_ARG_MISSING
 * - CALL_HOST_ARG_INVALID
 * - CALL_HOST_PPP_CONFIG_FAIL
 * - CALL_HOST_CONNECTION_FAIL
 * - CALL_HOST_CONNECTION_LOST2\n
 * Internal to function\n
 * - STATUS_MDP_OK
 * - STATUS_MDP_PAS_MAJ
 * - STATUS_MDP_INCID
 *
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 114) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:remote_download:KSFAM_M2OS:0x92
//  @GSIM_S:remote_download:E_remote_download
// \endif
int remote_download (S_PARAM_TLCHGT * Download);


/*! @brief This function calls the TMS for remote software downloading.
 * @param p_telecht : The list of required/optional parameters depends on the network 
 * @return Exit at the end of the download.
 *
 * type acceded ( [] : optional parameter). :
 *
 * <table cellpading="0" cellspacing="0" border="1" width="100%">
 * <tr><th> 'reseau' </th><th> t_noappel </th><th> t_transpac </th><th> apn </th><th> t_login </th><th> t_password</th></tr>
 * <tr><td> RTC (0x00) </td><td> Phone number preceded by PABX informations </td><td>.</td><td>.</td><td>.</td><td>.</td></tr>
 * <tr><td> X25 (0xFF) </td><td> Phone number preceded by PABX informations </td><td> X25 address </td><td>.</td><td>.</td><td>.</td></tr>
 * <tr><td> IP (0xFE)  </td><td> Address IP + port : xxx.xxx.xxx.xxx :yyyy </td><td>.</td><td> [apn]</td><td> [login]</td><td> [password]</td></tr>
 * <tr><td> IP/RTC (0xFD) </td><td> Address IP + port : xxx.xxx.xxx.xxx :yyyy </td><td> FAI phone number (preceded by PABX informations)</td><td>.</td><td> login</td><td> password</td></tr>
 * </table>
 *
 * @note Three formats may be used for calling application and IP address :
 * - 1.	xxx.xxx.xxx.xxx :yyyy : IP address + port. No indications about SSL. Remote download 
 * will use Telium Manager TMS parameters ( with/without SSL and SSL Profile)
 * - 2.	xxx.xxx.xxx.xxx :yyyy/ : Without SSL whatever Telium manager TMS parameter.
 * - 3.	xxx.xxx.xxx.xxx :yyyy/PROFIL SSL : With SSL and with SSL profile specified by calling application.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 112) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:remote_downloading:KSFAM_M2OS:0x91
//  @GSIM_S:remote_downloading:E_remote_downloading
// \endif
int remote_downloading (S_PARAM_TLCHGT *p_telecht);




/*! @brief This function starts a download activity.
 * @param p_telecht : pointer to structure S_PARAM_TLCHGT
 * @return Exit at the end of the download.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 124) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:remote_downloading_from_manager:KSFAM_M2OS:0xCC
//  @GSIM_S:remote_downloading_from_manager:E_remote_downloading_from_manager
// \endif
int remote_downloading_from_manager (S_PARAM_TLCHGT * p_telecht);

/*! @brief Calls the TMS for remote software diagnostic.
* @param p_telecht : The list of required/optional parameters depends on the network 
*   type acceded ( [] : optional parameter). :
*   <table cellpading="0" cellspacing="0" border="1" width="100%">
*   <tr><th> 'reseau' </th><th> t_noappel </th><th> t_transpac </th><th> apn </th><th> t_login </th><th> t_password</th></tr>
*    <tr><td> RTC (0x00) </td><td> Phone number preceded by PABX informations </td><td>.</td><td>.</td><td>.</td><td>.</td></tr>
*    <tr><td> X25 (0xFF) </td><td> Phone number preceded by PABX informations </td><td> X25 address </td><td>.</td><td>.</td><td>.</td></tr>
*    <tr><td> IP (0xFE)  </td><td> Address IP + port : xxx.xxx.xxx.xxx :yyyy </td><td>.</td><td> [apn]</td><td> [login]</td><td> [password]</td></tr>
*    <tr><td> IP/RTC (0xFD) </td><td> Address IP + port : xxx.xxx.xxx.xxx :yyyy </td><td> FAI phone number (preceded by PABX informations)</td><td>.</td><td> login</td><td> password</td></tr>
*    </table>
*    Three formats may be used for calling application and IP address :
*    - 1.	xxx.xxx.xxx.xxx :yyyy : IP address + port. No indications about SSL. Remote download 
*    will use Telium Manager TMS parameters ( with/without SSL and SSL Profile)
*    - 2.	xxx.xxx.xxx.xxx :yyyy/ : Without SSL whatever Telium manager TMS parameter.
*    - 3.	xxx.xxx.xxx.xxx :yyyy/PROFIL SSL : With SSL and with SSL profile specified by calling application.
 * @return Diagnostic report.\n
 * For CallHost Error (see callhost.h for detail):\n
 *  - CALL_HOST_ARG_MISSING
 *  - CALL_HOST_ARG_INVALID
 *  - CALL_HOST_PPP_CONFIG_FAIL
 *  - CALL_HOST_CONNECTION_FAIL
 *  - CALL_HOST_CONNECTION_LOST\n
 * Internal to function\n
 *  - STATUS_MDP_OK
 *  - STATUS_MDP_PAS_MAJ
 *  - STATUS_MDP_INCID
 *
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 113) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:remote_diagnostic:KSFAM_M2OS:
//  @GSIM_S:remote_diagnostic:E_remote_diagnostic
// \endif
int remote_diagnostic (S_PARAM_TLCHGT *p_telecht);


/*! @brief Calls the TMS for remote software licensing
* @param p_telecht : The list of required/optional parameters depends on the network 
*  type acceded ( [] : optional parameter). :
*  <table cellpading="0" cellspacing="0" border="1" width="100%">
*  <tr><th> 'reseau' </th><th> t_noappel </th><th> t_transpac </th><th> apn </th><th> t_login </th><th> t_password</th></tr>
*  <tr><td> RTC (0x00) </td><td> Phone number preceded by PABX informations </td><td>.</td><td>.</td><td>.</td><td>.</td></tr>
*  <tr><td> X25 (0xFF) </td><td> Phone number preceded by PABX informations </td><td> X25 address </td><td>.</td><td>.</td><td>.</td></tr>
*  <tr><td> IP (0xFE)  </td><td> Address IP + port : xxx.xxx.xxx.xxx :yyyy </td><td>.</td><td> [apn]</td><td> [login]</td><td> [password]</td></tr>
*  <tr><td> IP/RTC (0xFD) </td><td> Address IP + port : xxx.xxx.xxx.xxx :yyyy </td><td> FAI phone number (preceded by PABX informations)</td><td>.</td><td> login</td><td> password</td></tr>
*  </table>
*  Three formats may be used for calling application and IP address :
*   - 1.	xxx.xxx.xxx.xxx :yyyy : IP address + port. No indications about SSL. Remote download 
*   will use Telium Manager TMS parameters ( with/without SSL and SSL Profile)
*   - 2.	xxx.xxx.xxx.xxx :yyyy/ : Without SSL whatever Telium manager TMS parameter.
*   - 3.	xxx.xxx.xxx.xxx :yyyy/PROFIL SSL : With SSL and with SSL profile specified by calling application.
* @return Diagnostic report.\n
 * For CallHost Error (see callhost.h for detail):\n
 *  - CALL_HOST_ARG_MISSING
 *  - CALL_HOST_ARG_INVALID
 *  - CALL_HOST_PPP_CONFIG_FAIL
 *  - CALL_HOST_CONNECTION_FAIL
 *  - CALL_HOST_CONNECTION_LOST\n
 * Internal to function\n
 *  -SDI_STATUS_OK							
 *  -SDI_STATUS_KO							
 *  -SDI_STATUS_BUSY							
 *  -SDI_STATUS_DISCONNECTED					
 *  -SDI_STATUS_NOT_ALLOWED					
 *  -SDI_STATUS_APPROVED					
 *  -SDI_STATUS_DECLINED					
 *  -SDI_STATUS_ONLINE_REQUEST				
 *  -SDI_STATUS_TERMINATED					
 *  -SDI_STATUS_USE_OTHER_INTERFACE			
 *  -SDI_STATUS_INVALID_DATA					
 *  -SDI_STATUS_CANCELLED					
 *  -SDI_STATUS_IN_PROGRESS					
 *  -SDI_STATUS_NO_PARAMETER					
 *  -SDI_STATUS_NO_OPERATION_IN_PROGRESS		
 *  -SDI_STATUS_UNKNOWN_SERVICE				
 *  -SDI_STATUS_MISSING_DATA					
 *  -SDI_STATUS_NOT_ENOUGH_MEMORY			
 *  -SDI_STATUS_OUTPUT_BUFFER_TOO_SMALL		
 *  -SDI_STATUS_NO_CARD						
 *  -SDI_STATUS_CARD_BLOCKED					
 *  -SDI_STATUS_APPLICATION_BLOCKED			
 *  -SDI_STATUS_NOT_SUPPORTED				
 *  -SDI_STATUS_ANSWER_NOT_YET_RECEIVED		
 *  -SDI_STATUS_CARD_NOT_SUPPORTED			
 *  -SDI_STATUS_CONTACTLESS_NOT_ALLOWED		
 *  -SDI_STATUS_INVALID_PARAMETER          
 *  -SDI_STATUS_DLL_NOT_LOADED				
 *  -SDI_STATUS_UNKNOWN						
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 277) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink 
 */
// \if SIMULATION
//  @GSIM_F:remote_licencing:KSFAM_M2OS:
//  @GSIM_S:remote_licencing:E_remote_licencing
// \endif
int remote_licencing (S_PARAM_TLCHGT *p_telecht);

/*! @brief Calls the TMS for remote software iST target if the intelligent mode is enable
* @param param_telechgt : The list of required/optional parameters depends on the network 
*  type acceded ( [] : optional parameter). :
*  <table cellpading="0" cellspacing="0" border="1" width="100%">
*  <tr><th> 'reseau' </th><th> t_noappel </th><th> t_transpac </th><th> apn </th><th> t_login </th><th> t_password</th></tr>
*  <tr><td> RTC (0x00) </td><td> Phone number preceded by PABX informations </td><td>.</td><td>.</td><td>.</td><td>.</td></tr>
*  <tr><td> X25 (0xFF) </td><td> Phone number preceded by PABX informations </td><td> X25 address </td><td>.</td><td>.</td><td>.</td></tr>
*  <tr><td> IP (0xFE)  </td><td> Address IP + port : xxx.xxx.xxx.xxx :yyyy </td><td>.</td><td> [apn]</td><td> [login]</td><td> [password]</td></tr>
*  <tr><td> GPRS (0xFB) </td><td> Address IP + port : xxx.xxx.xxx.xxx :yyyy </td><td>.</td><td> [apn]</td><td> [login]</td><td> [password]</td></tr>
*  </table>
*  Three formats may be used for calling application and IP address :
*   - 1.	xxx.xxx.xxx.xxx :yyyy : IP address + port. No indications about SSL. Remote download 
*   will use Telium Manager TMS parameters ( with/without SSL and SSL Profile)
*   - 2.	xxx.xxx.xxx.xxx :yyyy/ : Without SSL whatever Telium manager TMS parameter.
*   - 3.	xxx.xxx.xxx.xxx :yyyy/PROFIL SSL : With SSL and with SSL profile specified by calling application.
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 123) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:remote_licencing:KSFAM_M2OS:
//  @GSIM_S:remote_licencing:E_remote_licencing
// \endif
int remote_IST (S_PARAM_TLCHGT *param_telechgt);

/*! @} **/
/*! @addtogroup KSFAM_PPS_MANAGER
	* @{
**/

/* Fin PBE : Serveur Licence 04-979 */
#define get_terminal_infos(p) lire_infos_terminal(FCT_INFOS_TERMINAL,p)
#define font_size startupcv20




#define C_CONF_PPR		0
#define C_CONF_PPC		1
#define C_CONF_P30		2
#define C_CONF_PP30S	3
#define C_CONF_IPP220	4
#define C_CONF_IPP250	5
#define C_CONF_IPP280	6
#define C_CONF_IPP320	7
#define C_CONF_IPP350	8

/*! @brief This function returns the type of connected pinpad 
 * @return 
 * - C_CONF_PPR
 * - C_CONF_PPC
 * - C_CONF_P30
 * - C_CONF_PP30S
 * - C_CONF_IPP220
 * - C_CONF_IPP250
 * - C_CONF_IPP280
 * - C_CONF_IPP320
 * - C_CONF_IPP350 
 *  @par exit (EXIT_DLL_PINPAD_NOT_INITIALIZED + 34) if function does not exist
 *
 * @link KSFAM_PPS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:PPR_Type:KSFAM_PPS_MANAGER:0x50
// \endif
int PPR_Type(void);
/*! @} **/



/*! @addtogroup KSFAM_OS_MANAGER
	* @{
**/

/*! @brief This function will return a semaphore number to be used.
 * @return GetSemaphoreUser returns a semaphore number to be used. When GetSemaphoreUser returns a value 0xFFFF. There is no more semaphore slot available.
 *
 * @link KSFAM_OS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:GetSemaphoreUser:KSFAM_OS_MANAGER:0x10
// \endif
Word GetSemaphoreUser(void);


/*! @brief This function will release a semaphore number for another application .
 * @param sem : semaphore number to release.
 * @return None.
 *
 * @link KSFAM_OS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:FreeSemaphoreUser:KSFAM_OS_MANAGER:0x11
// \endif
void FreeSemaphoreUser(Word sem);


/*! @brief This function will return a delay number to be used.
 * @return 
 * - a delay slot number. 
 * - when GetDelayUser returns a value 0xFF, there is no more delay slot available.
 * @note This routine is handled by M2OS via its DLL named extens in order to handle the multi application. DLL extens must be open and linked to the application using the Manager routine extenslib_open. 
 *
 * @link KSFAM_OS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:GetDelayUser:KSFAM_OS_MANAGER:0x22
// \endif
Word GetDelayUser(void);


/*! @brief This function will release a delay slot number for another application. 
 * @param Delay slot number to release.
 * @return None.
 * @note This routine is handled by M2OS via its DLL named extens in order to handle the multi application. DLL extens must be open and linked to the application using the Manager routine extenslib_open. 
 *
 * @link KSFAM_OS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:FreeDelayUser:KSFAM_OS_MANAGER:0x23
// \endif
void FreeDelayUser(Word Delay);


/*! @brief This function allow management of the mailbox ressource.
 * @return Resource number or 0xFFFF if no resource available.
 *
 * @link KSFAM_OS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:GetMailboxUser:KSFAM_OS_MANAGER:0x1C
// \endif
Word GetMailboxUser(void);


/*! @brief This function allow management of the mailbox ressource.
 * @param bal : Resource number.
 * @return None
 *
 * @link KSFAM_OS_MANAGER Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:FreeMailboxUser:KSFAM_OS_MANAGER:0x1D
// \endif
void FreeMailboxUser(Word bal);

/*! @} **/


/*! @addtogroup KSFAM_M2OS
	* @{
**/

/*! @brief Powered checks if the terminal is really powered.
 * @return TRUE if the terminal is really powered.
 * @par exit (EXIT_DLL_PARAM_NOT_INITIALIZED + 50) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink 
*/
// \if SIMULATION
//  @GSIM_F:Powered:KSFAM_M2OS:0xC3
// \endif
int Powered(void);
/*! @} **/


/*! @addtogroup KSFAM_PPS_MANAGER
	* @{
**/
#define TAILLE_MAXBUF_CHEQUE 150
/*! @brief Define the buffer for the cheque.*/
typedef unsigned char BUFFER_CHEQUE[TAILLE_MAXBUF_CHEQUE+1];

#ifdef _SIMULPC_
#include "simu.h"	// Type des fonctions simulees sur TPE 
#endif				// _SIMULPC_
/* niveau de securite */
#define NIV_STD     "80"
#define NIV_PEDS    "81"
#define NIV_ZKA     "82"

#endif
/*! @} **/
