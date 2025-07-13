/*! @addtogroup KSFAM_USQ
	* @{
**/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _UTIL_SQ_INCLUDE_
#define _UTIL_SQ_INCLUDE_

#define  TIME_OUT_POINT 12100  /*2*MINUTE + 100 */

/*
======================================================================
					List of Defines
======================================================================
*/
#define S_ETHERNET_PUT_DEFAULT   0				/*!< Put default parameters : like after reset		*/
#define S_ETHERNET_PUT_CURRENT   1				/*!< Put own parameters : like in parameter    */
#define S_ETHERNET_GET_DEFAULT   2				/*!<Get Default parameters : like after reset */
#define S_ETHERNET_GET_CURRENT   3				/*!< Get current parameters                    */
#define S_ETHERNET_GET_INTERNAL  4				/*!< Get internal Value */
#define S_ETHERNET_PUT_INTERNAL  5				/*!<Put internal Value */
/*! @brief Define structure for USQ_EthernetConfig. */
typedef struct 
{
  unsigned int addr;									/*!<(IP) Address*/
  unsigned int netmask;								/*!< net mask*/
  unsigned int gateway;								/*!< gateway*/
  unsigned int dns1_addr;							/*!< address of the first DNS*/
  unsigned int dns2_addr;							/*!< address of the second DNS*/
} S_ETHERNET_CONFIG;


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function changes or returns the ethernet configuration.
 *	@param function : Define functions for USQ_EthernetConfig
 * -	Put default parameters : like after reset S_ETHERNET_PUT_DEFAULT 0
 * -	Put own parameters : like in parameter S_ETHERNET_PUT_CURRENT 1
 * -	Get Default parameters : like after reset S_ETHERNET_GET_DEFAULT 2
 * -	Get current parameters S_ETHERNET_GET_CURRENT 3
 * -	Get internal Value S_ETHERNET_GET_INTERNAL 4
 * -	Put internal Value S_ETHERNET_PUT_INTERNAL 5
 *
 *	@param val : pointer to structure S_ETHERNET_CONFIG.
 *	@return None.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 131) if function does not exist
 *	@note 
 *
 * @link KSFAM_USQ Back to top @endlink
*/
extern void USQ_EthernetConfig  ( int function , S_ETHERNET_CONFIG *val);


/*! @brief This function calculate a crc16 using the iso3309 system.
 *	@param Fcs : result
 *	@param Cp : incoming buffer 
 *	@param len : length of the buffer
 *  @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 17) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
extern unsigned short USQ_Calcrc_iso3309 ( unsigned short Fcs,
                                           unsigned char *Cp,
                                           short len          );



/*! @brief This function add N days to DATE.
 *	@param nb : number of days
 *	@param Date : date to increment
 *	@return None (void).
 *  @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 19) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
#ifndef __FRAMEWORK_TELIUM_PLUS__
extern void  USQ_AddDays    ( unsigned int nb , DATE *Date);
#else
extern void  USQ_AddDays    ( unsigned int nb , Telium_Date_t *Date);
#endif

/*! @brief This function set the date N days before.
 *	@param nb : number of days
 *	@param Date : date to set.
 *	@return None (void).
 *  @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 20) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
#ifndef __FRAMEWORK_TELIUM_PLUS__
extern void  USQ_RemoveDays    ( unsigned int nb  , DATE *Date );
#else
extern void  USQ_RemoveDays    ( unsigned int nb  , Telium_Date_t *Date );
#endif


/*! @brief This function set the date N minutes before.
 *	@param min : number of minutes 
 *	@param date : pointer to structure DATE.
 *	@return None (void).
 *  @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 21) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
#ifndef __FRAMEWORK_TELIUM_PLUS__
extern void  USQ_RemoveMinutes      ( unsigned int min , DATE *date );
#else
extern void  USQ_RemoveMinutes      ( unsigned int min , Telium_Date_t *date );
#endif


/*! @brief This function set the date the day before.
 *	@param Date : date to set.
 *	@return None (void).
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 22) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
#ifndef __FRAMEWORK_TELIUM_PLUS__
extern void  USQ_PreviousDay  ( DATE *Date );
#else
extern void  USQ_PreviousDay  ( Telium_Date_t *Date );
#endif


/*! @brief This function add increment seconds to date.
 *	@param increment : number of seconds to add.
 *	@param date : pointer to structure DATE.
 *	@return None (void).
 *  @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 23) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
#ifndef __FRAMEWORK_TELIUM_PLUS__
extern void  USQ_AddSeconds   (unsigned int  increment, DATE *date);
#else
extern void  USQ_AddSeconds   (unsigned int  increment, Telium_Date_t *date);
#endif


/*! @brief This function add increment minutes to date.
 *	@param increment : Number of minutes to increment.
 *	@param date : date to set.
 *	@return None (void).
 *  @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 24) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
#ifndef __FRAMEWORK_TELIUM_PLUS__
extern void  USQ_AddMinutes (unsigned int  increment, DATE *date);
#else
extern void  USQ_AddMinutes (unsigned int  increment, Telium_Date_t *date);
#endif

/*! @brief This function set a date increment seconds before.
 *	@param increment : number of seconds.
 *	@param date : date to set.
 *	@return None (void).
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 27) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
#ifndef __FRAMEWORK_TELIUM_PLUS__
extern void USQ_RemoveSeconds   ( unsigned int increment , DATE * date );
#else
extern void USQ_RemoveSeconds   ( unsigned int increment , Telium_Date_t * date );
#endif


/*! @brief Returns the difference between to date (date2 and date1), in seconds.
 *	@param date1: the first date
 *	@param date2 : the second date.
 *	@return Returns the number of seconds between the two dates.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 28) if function does not exist
 *
 * @note 
 * The DATE Fields (day, month, year) have no effect on the result.
 * For example, when date1 = 20/05/2011-23:55:00 and date2 = 21/05/2011-00:05:00, this function returns -85800 seconds 
 *
 * @link KSFAM_USQ Back to top @endlink
*/
#ifndef __FRAMEWORK_TELIUM_PLUS__
extern int  SLSQ_TimeGapInSeconds (DATE *date1, DATE *date2);
#else
extern int  SLSQ_TimeGapInSeconds (Telium_Date_t *date1, Telium_Date_t *date2);
#endif


/*! @brief Define for param Action of function Beep. */
#define BEEP_ON         0x0001
#define BEEP_WAIT       0x0002
#define BEEP_OFF        0x0004
#define BEEP_ON_PINPAD  0x0008
#define BEEP_ON_PINCODE 0x0010

/*! @brief This function is used to dynamically change the application name that is displayed in the header
 *	@param isname : Structure containing the name to display .
 *	@return
 * -	0 if OK
 *
 *	@note 
 *  only the first element of the structure is used
 *    S_ETATOUT_EXTENDED   bannername;
 *    bannername.response_number = 1;
 *    strcpy(bannername.returned_state[0].appname,"MYNAME");
 *    bannername.returned_state[0].no_appli = ApplicationGetCurrent();
 *    SetSpecificIsName(&is_name);
 *  Call function with NULL restore normal case
 *
 * @link KSFAM_USQ Back to top @endlink
*/
extern int SetSpecificIsName(S_ETATOUT_EXTENDED *isname);

/*! @brief This function is used to manage buzzer functionnality.
*	@param note : note
*	@param octave : octave
*	@param duration : duration (1/100 s)
*	@param Action BEEP_ON,BEEP_WAIT,BEEP_OFF
*
*	@note 
*   Action is a mask
*		BEEP_ON to start buzzer with note and octave
*		BEEP_WAIT to wait for duration
*       BEEP_OFF to stop buzzer
*       BEEP_ON_PINPAD start buzzer on PINPAD with note and octave,
*       wait for duration and after duration stop the buzzer on PINPAD
*
*   Warning: this function has not to be used before SDK6.5
*
*	@section beep1

 * @include util_sq_Sample_01.c
*
 * @link KSFAM_USQ Back to top @endlink
*/
extern int Beep(int note,int octave,unsigned short duration,int Action);

/*! @brief This function is used to wait for card removal with buzzer activation.
*	@param handle : handle of CHIP card peripheral
 *	@return
 * -	0 if OK
 * -	-1 if not implemented
*
*	@note 
*   Buzzer is activated on proper device (on PINPAD if PINPAD reader is activated or on terminal).
*   This function use TimeOutRemoveCard and CardBeep parameters
*
 * @link KSFAM_USQ Back to top @endlink
*/
#ifndef __FRAMEWORK_TELIUM_PLUS__
extern int RemoveCardWithBeep(FILE *handle);
#else
extern int RemoveCardWithBeep(Telium_File_t *handle);
#endif

/*! @} **/

/*! @addtogroup KSFAM_M2OS
	* @{
**/


/*! @brief Allows to enter an amount, with gestion of the graphic context.
 *	@param *devise : Currency name and decimal point position.
 *	@param *saisie : Amount entry (output).
 *	@param *reponse : entry's response.
 *	@param *chaine1: string to display on the first line.
 *	@param *table : mask of the keys and time out.
 *	@param *tab_devise : address of the available currency table.
 *	@param nb_money : number of money in the table.
 *	@param maskevent : testall events mask.
 *	@param mode : France or export.
 *  @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 79) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
extern unsigned int  G_Amount_Entry (S_MONEY      *devise     ,  					/* name of the currency and decimal point position (e / s)  */
                              ENTRY_BUFFER         *saisie     ,  					/* Amount entry (output)     */
                              unsigned char         *reponse    ,  					/* response to entry             */
                              char                  *chaine1    ,  					/* String to display on the first line           */
                              TAB_ENTRY_AMOUNT      *table      ,  					/* Mask of keys and time out   */
                              S_MONEY               *tab_devise ,  					/* address of available currency table*/
                              unsigned char         nb_money    ,  					/* number of money contained in the table */
                              unsigned int          maskevent   ,  					/* mask of events ttestall*/
                              unsigned short int    mode           					/* France Mode or Export */
				           	 );


// French prototypes
#ifndef __FRAMEWORK_TELIUM_PLUS__
extern void  USQ_Ajouterjour    ( unsigned int nb  , DATE *Date );
extern void  USQ_Enleverjour    ( unsigned int nb  , DATE *Date );
extern void  USQ_Enlevermn      ( unsigned int min , DATE *date );
extern void  USQ_Jourprecedent  ( DATE *date );
extern void  USQ_Ajoutermnsec   (unsigned int  increment, DATE *date);
extern void  USQ_Ajoutermn (unsigned int  increment, DATE *date);
extern void  USQ_Enlevermnsec   ( unsigned int increment , DATE * date );
extern int   SLSQ_Ecart_heure_minute_seconde (DATE *date1, DATE *date2);
extern void USQ_Enlevermnsec   ( unsigned int increment , DATE * date );
extern int  SLSQ_Ecart_heure_minute_seconde (DATE *date1, DATE *date2);
#else
extern void  USQ_Ajouterjour    ( unsigned int nb  , Telium_Date_t *Date );
extern void  USQ_Enleverjour    ( unsigned int nb  , Telium_Date_t *Date );
extern void  USQ_Enlevermn      ( unsigned int min , Telium_Date_t *date );
extern void  USQ_Jourprecedent  ( Telium_Date_t *date );
extern void  USQ_Ajoutermnsec   (unsigned int  increment, Telium_Date_t *date);
extern void  USQ_Ajoutermn (unsigned int  increment, Telium_Date_t *date);
extern void  USQ_Enlevermnsec   ( unsigned int increment , Telium_Date_t * date );
extern int   SLSQ_Ecart_heure_minute_seconde (Telium_Date_t *date1, Telium_Date_t *date2);
extern void USQ_Enlevermnsec   ( unsigned int increment , Telium_Date_t * date );
extern int  SLSQ_Ecart_heure_minute_seconde (Telium_Date_t *date1, Telium_Date_t *date2);
#endif

extern unsigned int  G_Saisie_montant (S_MONEY      *devise     ,  					/* name of the currency and decimal point position (e / s)  */
                              ENTRY_BUFFER         *saisie     ,  					/* Amount entry (output)     */
                              unsigned char         *reponse    ,  					/* response to entry             */
                              char                  *chaine1    ,  					/* String to display on the first line           */
                              TAB_ENTRY_AMOUNT      *table      ,  					/* Mask of keys and time out   */
                              S_MONEY               *tab_devise ,  					/* address of available currency table*/
                              unsigned char         nb_money    ,  					/* number of money contained in the table */
                              unsigned int          maskevent   ,  					/* mask of events ttestall*/
                              unsigned short int    mode           					/* France Mode or Export */
				           	 );


#define USQ_AddDays           USQ_Ajouterjour
#define USQ_RemoveDays        USQ_Enleverjour
#define USQ_RemoveMinutes     USQ_Enlevermn
#define USQ_PreviousDay       USQ_Jourprecedent
#define USQ_AddSeconds        USQ_Ajoutermnsec
#define USQ_AddMinutes        USQ_Ajoutermn
#define USQ_RemoveSeconds     USQ_Enlevermnsec
#define SLSQ_TimeGapInSeconds SLSQ_Ecart_heure_minute_seconde
#define G_Amount_Entry        G_Saisie_montant

/*! @} **/

/*! @addtogroup KSFAM_DLL
	* @{
**/

/*! @brief DLLExist returns TRUE or FALSE depending if the specified DLL is loaded or not.
 *	@param name : This is the name of the DLL : CB2A, EXTENS, LANGUE, LIBGR, PARAM, SAISIE, SV, DLLPSC, PROTOCOLE, SSL, EMVSQ, PINPAD, PPS30, PPR30, IAM, GPRS, UMS, FTP,.... 
 *	@return
 * -	TRUE if the dll is loaded.
 * -	false otherwise
 * -	false otherwise.
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 102) if function does not exist
 *	@note 
 *
 * @link KSFAM_DLL Back to top @endlink
*/
extern int  DLLExist(char * name);
/*! @} **/

#endif

#ifdef __cplusplus
}
#endif
