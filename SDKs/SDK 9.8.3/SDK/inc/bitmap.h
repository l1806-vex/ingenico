/*! @addtogroup KSFAM_HEADER
	* @{
**/
#ifndef _BITMAP_H
#define _BITMAP_H

#define HEADER_DEFAULT_HEIGHT_LOW         56
#define HEADER_DEFAULT_WIDTH_LOW         320
#define HEADER_DEFAULT_HEIGHT_HIGH        78
#define HEADER_DEFAULT_WIDTH_HIGH        240

#define LEDS_DEFAULT_HEIGHT               10
#define LEDS_DEFAULT_WIDTH               320

#define FOOTER_DEFAULT_HEIGHT             14
#define FOOTER_DEFAULT_WIDTH             320

#define AFF_DECAL_BAS		         11
#define TAILLE_BAND_BAS_X			 127
#define TAILLE_BAND_BAS_Y			 			 7					/* Set the height of the banner at the bottom and display bmp */
#define TAILLE_BAND_HAUT_Y			  	 12					/* Set the height of the banner high                        */
#define AFF_HAUT_Y					 1
#define AFF_LIGNE2_Y                 (AFF_HAUT_Y+6)
#define TAILLE_BMP_BATT_X			 14
#define TAILLE_BMP_SECTEUR_X		 9
#define TAILLE_BMP_RACCRO_X			 20
#define TAILLE_BMP_DECRO_X			 20
#define TAILLE_BMP_NIV_RECEP_X		 17
#define TAILLE_BMP_NIV_RECEP_BT  	 21
#define TAILLE_INTER_BMP_X			 5
#define TAILLE_INTER_HEURE_X		 5
#define TAILLE_INTER_BMP_BATT_X		 2
#define TAILLE_INTER_BMP_SECTEUR_X   2
#define TAILLE_INTER_BMP_RESEAU_X    13
#define TAILLE_BMP_VIDE_X			 32
#define TAILLE_BMP_ONGLET			 6
#define TAILLE_HEURE_X	  		 	 28
#define TAILLE_PEDS_X				 17
#define AFF_BMP_BATT_X				 0
#define AFF_BMP_SECTEUR_X			 (TAILLE_BMP_BATT_X+TAILLE_INTER_BMP_BATT_X)
#define AFF_BMP_RACCRO_X			 (AFF_BMP_SECTEUR_X+TAILLE_BMP_SECTEUR_X+TAILLE_INTER_BMP_SECTEUR_X)
#define AFF_BMP_DECRO_X				 AFF_BMP_RACCRO_X
#define AFF_TXT_NOM_RESEAU_X		 (AFF_BMP_RACCRO_X+TAILLE_BMP_DECRO_X+TAILLE_INTER_BMP_RESEAU_X)
#define AFF_TXT_NOM_RESEAU_X_GPRS	 (AFF_TXT_NOM_RESEAU_X+10)
#define AFF_TXT_NOM_RESEAU_X_BT		 (AFF_TXT_NOM_RESEAU_X+2)
#define AFF_RESEAU_X                 (AFF_BMP_DECRO_X+7)
#define AFF_ETHERNET_DECRO_X         (AFF_BMP_DECRO_X+13)
#define AFF_ETHERNET_RACCRO_X        (AFF_BMP_DECRO_X+3)
#define AFF_BMP_RECEP_X				 (MAX_VISU_X-TAILLE_BMP_NIV_RECEP_X+1)
#define AFF_BMP_ONGLET_Y			 (TAILLE_BAND_HAUT_Y+1)
#define AFF_PEDS_X					 (TAILLE_BAND_BAS_X - TAILLE_PEDS_X)
#define AFF_DATE  					 (TAILLE_BAND_HAUT_Y+2)
#define AFF_DATE_X					 10
#define AFF_HEURE_X_AVEC_PEDS		 (AFF_PEDS_X - TAILLE_HEURE_X - TAILLE_INTER_HEURE_X)
#define AFF_HEURE_X_SANS_PEDS		 (TAILLE_BAND_BAS_X - TAILLE_HEURE_X - AFF_DATE_X)
#define AFF_NOM_APPLI				 (TAILLE_BAND_HAUT_Y+2)
#define AFF_ECRAN_UTILISATEUR		 (AFF_BMP_ONGLET_Y+TAILLE_BMP_ONGLET+1)
#define AFF_ECRAN_UTILISATEUR_LIGNE1 (AFF_ECRAN_UTILISATEUR+2)
#define AFF_ECRAN_UTILISATEUR_LIGNE2 (AFF_ECRAN_UTILISATEUR_LIGNE1 + 19)

#define AFF_DATE_EFT30				 5
#define AFF_DATE_X_EFT30			 7
#define AFF_HEURE_X_AVEC_PEDS_EFT30	 85
#define AFF_HEURE_X_SANS_PEDS_EFT30	 102
#define AFF_PEDS_X_EFT30			 115

#define AFF_CLESS_X_X07             65
#define AFF_CLESS_Y_X07             98

#define AFF_CLESS_X_IWL250         80 
#define AFF_CLESS_Y_IWL250         96

#define AFF_CLESS_X_930             79
#define AFF_CLESS_Y_930            134

#define AFF_CLESS_X_ISC350          240
#define AFF_CLESS_Y_ISC350          130

#define AFF_CLESS_X_ISC250          160
#define AFF_CLESS_Y_ISC250          92

#define AFF_CLESS_X_IPP480          60
#define AFF_CLESS_Y_IPP480         127

#define AFF_CLESS_X_IWL280          60
#define AFF_CLESS_Y_IWL280         108

#define AFF_CLESS_X_IWL350          80
#define AFF_CLESS_Y_IWL350         110

#define HEADER_GPRS_AREA    0
#define HEADER_BT_AREA      1
#define HEADER_WIFI_AREA    2
#define HEADER_NETWORK_AREA 3

#define FOOTER_KEY1         0
#define FOOTER_KEY2         1
#define FOOTER_KEY3         2
#define FOOTER_KEY4         3
#define FOOTER_CANCEL       4
#define FOOTER_VALID        5

#define FOOTER_KEYNUM0           10
#define FOOTER_KEYNUM1           11
#define FOOTER_KEYNUM2           12
#define FOOTER_KEYNUM3           13
#define FOOTER_KEYNUM4           14
#define FOOTER_KEYNUM5           15
#define FOOTER_KEYNUM6           16
#define FOOTER_KEYNUM7           17
#define FOOTER_KEYNUM8           18
#define FOOTER_KEYNUM9           19
#define FOOTER_KEYSTAR           20
#define FOOTER_KEYPOINT          21
#define FOOTER_KEYF              22
#define FOOTER_KEYVAL            23
#define FOOTER_KEYCORR           24
#define FOOTER_KEYANN            25
#define FOOTER_PINCODE_KEYBOARD  26

#define _SOCLE_STATE_            0x0001
#define _BATT_STATE_             0x0002
#define _NIV_RECEP_              0x0004
#define _GPRS_STATE_             0x0008
#define _APPLI_STATE_            0x0010
#define _RTC_STATE_              0x0020
#define _INTER_STATE_            0x0040
#define _BITMAP_STATE_           0x0080
#define _UP_STATE_               0x0100
#define _ETH_STATE_              0x0200
#define _DATE_STATE_             0x0400
#define _GPRS_NETWORK_STATE_     0x1000
#define _BT_NETWORK_STATE_       0x2000
#define _GPRS_BT_NETWORK_STATE_  0x4000
#define _BT_GPRS_NETWORK_STATE_  0x8000

#define _ALL_STATE_              (_DATE_STATE_ | _ETH_STATE_ | _UP_STATE_ | _APPLI_STATE_ | _SOCLE_STATE_ | _BATT_STATE_ | _NIV_RECEP_ | _GPRS_STATE_ | _RTC_STATE_ | _BITMAP_STATE_)
#define _OLD_ALL_STATE_          (_APPLI_STATE_ | _SOCLE_STATE_ | _BATT_STATE_ | _NIV_RECEP_ | _GPRS_STATE_ | _RTC_STATE_ | _BITMAP_STATE_)

// Network State
#define HANG_UP  0
#define HANG_ON  1

/*
======================================================================
			Data Structures Definition
======================================================================
*/

typedef struct
{
  int Number;
  int State; 
  int Blink;
  int TimeOn;
  int TimeOff;
  int Color;
  int TimeElapsed;
}
StructLeds;

typedef struct
{
  unsigned int  adresse;                                                    //!< adress base
  int           indice;                                                     //!< index of base that manage the periph
  int           isconnected;                                               //!< state base: connected or not
  int           base_name[DBLUETOOTH_SPP_INFO_MAX_BASE_NAME_SIZE + 1]; //!< base name
  int           level;                                                     //!< level recept 
} BtState;


/*
======================================================================
			Functions Definition
======================================================================
*/


/*! @brief This function returns the handle BT.
 * @return Pointer to handle
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 203) if function does not exist
// \if SIMULATION
//  @GSIM_F:GetBtHandle:KSFAM_HEADER:0x1
//  @GSIM_A:0:ONE_ADDRESS
// \endif
 *
 * @link KSFAM_HEADER Back to top @endlink
*/
extern FILE *GetBtHandle(void);


/*! @brief This function returns the state of handle BT.
 * @param dbt : Handle BT.
 * @param fct :  periph name fct.
 * - DBLUETOOTH_FIOCTL_GET_MODEM_ADDRESS
 * - DBLUETOOTH_FIOCTL_GET_COM0_ADDRESS
 * - DBLUETOOTH_FIOCTL_GET_COMN_ADDRESS
 * - DBLUETOOTH_FIOCTL_GET_COMU_ADDRESS
 *
 * @param periph : see struct Btstate
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 204) if function does not exist
// \if SIMULATION
//  @GSIM_F:GetPeriphState:KSFAM_HEADER:0x2
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
// \endif
 *
 * @link KSFAM_HEADER Back to top @endlink
*/
extern void  GetPeriphState(FILE *dbt,int fct,BtState *periph);


/*! @brief This function returns TRUE if one base is associated.
 * @param dbt : Handle BT.
 * @return TRUE or FALSE
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 205) if function does not exist
// \if SIMULATION
//  @GSIM_F:IsBaseKnown:KSFAM_HEADER:0x3
//  @GSIM_A:0:ONE_ADDRESS
// \endif
 *
 * @link KSFAM_HEADER Back to top @endlink
*/
extern int   IsBaseKnown(FILE *dbt);


/*! @brief This function returns TRUE if one base is connected.
 * @param dbt : Handle BT.
 * @param indice : num of base given by the BT driver
 * @return TRUE or FALSE
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 206) if function does not exist
// \if SIMULATION
//  @GSIM_F:IsBaseConnected:KSFAM_HEADER:0x4
//  @GSIM_A:0:ONE_ADDRESS
// \endif
 *
 * @link KSFAM_HEADER Back to top @endlink
*/
extern int   IsBaseConnected(FILE *dbt,int indice);


/*! @brief This function returns the name of base connected.
 * @param dbt : Handle BT.
 * @param indice : num of base given by the BT driver
 * @param base_name : return the base name
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 207) if function does not exist
// \if SIMULATION
//  @GSIM_F:GetBaseName:KSFAM_HEADER:0x5
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:2:ONE_ADDRESS
// \endif
 *
 * @link KSFAM_HEADER Back to top @endlink
*/
extern void  GetBaseName(FILE *dbt,int indice,char *base_name);


/*! @brief This function returns the level BT.
 * @param dbt : Handle BT.
 * @param indice : num of base given by the BT driver
 * @return
 * - 0 = not connected
 * - 1 = Bluetooth level > 100
 * - 2 = Bluetooth level > 75
 * - 3 = Bluetooth level > 50
 * - 4 = Bluetooth level > 25
 * - 5 = Bluetooth level > 0
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 208) if function does not exist
// \if SIMULATION
//  @GSIM_F:Get_BtLevel:KSFAM_HEADER:0x6
//  @GSIM_A:0:ONE_ADDRESS
// \endif
 *
 * @link KSFAM_HEADER Back to top @endlink
*/
extern int   Get_BtLevel(FILE *dbt,int indice);


/*! @brief This function returns the level Battery.
 * @param iLevBatt   : return level bat
 * - iLevBatt < 5 = very low level bat
 * - iLevBatt >=80 = high level bat
 *
 * @param iBatLoading: return if bat is loading
 * - 0 = PWR_FIOCTL_CHARGER_STATE_OFF
 * - 1 = PWR_FIOCTL_CHARGER_STATE_ON
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 209) if function does not exist
// \if SIMULATION
//  @GSIM_F:Get_battery_level:KSFAM_HEADER:0x7
//  @GSIM_A:0:ONE_POINTER
//  @GSIM_A:1:ONE_POINTER
// \endif
 *
 * @link KSFAM_HEADER Back to top @endlink
*/
extern void  Get_battery_level(int *iLevBatt,int *iBatLoading);



/*! @brief This function returns the charger state.
 * @param iLevBatt    : return level bat
 * - iLevBatt < 5 = very low level bat
 * - iLevBatt >=80 = high level bat
 * @param iBatLoading : return if bat is loading
 * - 0 = PWR_FIOCTL_CHARGER_STATE_OFF
 * - 1 = PWR_FIOCTL_CHARGER_STATE_ON
 * @param iPresUSB    : return connected to USB
 * - 0 = disconnected
 * - 1 = connected to USB
 * @param iPresBase   : return terminal on BASE
 * - 0 = terminal not on base
 * - 1 = terminal on BASE
 * @return
 * - 0                      : OK
 * - EXTENS_NOT_IMPLEMENTED : function does'nt exist
 *
 * @par exit none if function does not exist
// \if SIMULATION
//  @GSIM_F:Get_battery_level:KSFAM_HEADER:0x7
//  @GSIM_A:0:ONE_POINTER
//  @GSIM_A:1:ONE_POINTER
// \endif
 *
 * @link KSFAM_HEADER Back to top @endlink
*/
extern int ConnectedToPower(int *iLevBatt,int *iBatLoading,int *iPresUSB,int *iPresBase);


/*! @brief This function returns the Network state.
 * @param ptrInfos : return the name of network
 * @param ConnectState : return TRUE if the com is etablish or FALSE
 * @return connect state 
 * - HANG_UP
 * - HANG_ON
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 210) if function does not exist
// \if SIMULATION
//  @GSIM_F:Get_Network_State:KSFAM_HEADER:0x8
//  @GSIM_A:0:ONE_POINTER
//  @GSIM_A:1:ONE_POINTER
// \endif
 *
 * @link KSFAM_HEADER Back to top @endlink
*/
extern int   Get_Network_State(MSGinfos *ptrInfos,int *ConnectState);


/*! @brief This function returns the Sim state.
 * @param dgprs   : handle gprs
 * @return sim state 
 * - DGPRS_SIM_NOT_RECEIVED_YET
 * - DGPRS_SIM_OK				
 * - DGPRS_SIM_KO		
 * - DGPRS_SIM_PIN_REQUIRED		
 * - DGPRS_SIM_PIN2_REQUIRED
 * - DGPRS_SIM_PIN_ERRONEOUS		
 * - DGPRS_SIM_SIM_NOT_INSERTED			
 * - DGPRS_SIM_PUK_REQUIRED (blocked after three wrong pin code)
 * - DGPRS_SIM_PUK2_REQUIRED
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 211) if function does not exist
// \if SIMULATION
//  @GSIM_F:Get_SIM_State:KSFAM_HEADER:0x9
//  @GSIM_A:0:ONE_ADDRESS
// \endif
 *
 * @link KSFAM_HEADER Back to top @endlink
*/
extern int   Get_SIM_State(FILE *dgprs);


/*! @brief This function returns the Gprs state.
 * @param dgprs        : handle gprs
 * @param Attachment   : TRUE if Attached to the gprs network else FALSE
 * @param ConnectState : HANG_UP,HANG_ON
 * @param network_name: operator name
 * @return sim state 
 * - TRUE = network_name is ok
 * - FALSE = network_name is ko
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 212) if function does not exist
// \if SIMULATION
//  @GSIM_F:Get_SIM_State:KSFAM_HEADER:0xA
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:1:ONE_POINTER
//  @GSIM_A:2:ONE_ADDRESS
// \endif
 *
 * @link KSFAM_HEADER Back to top @endlink
*/
extern int   Get_GPRS_State(FILE *dgprs,unsigned int *Attachment,int *ConnectState,char *network_name);


/*! @brief This function returns the Gprs radio level.
 * @param dgprs      : handle gprs
 * @return level
 * - 0 (not connected)
 * - to 5 (high level)
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 213) if function does not exist
// \if SIMULATION
//  @GSIM_F:Get_GPRS_Radio_Level:KSFAM_HEADER:0xB
//  @GSIM_A:0:ONE_ADDRESS
// \endif
 *
 * @link KSFAM_HEADER Back to top @endlink
*/
extern int   Get_GPRS_Radio_Level(FILE *dgprs);


#endif
/*! @} **/
