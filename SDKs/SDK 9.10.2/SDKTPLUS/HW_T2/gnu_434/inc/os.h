/*! @addtogroup KSFAM_SANTE
	* @{
**/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OS_H
#define OS_H

/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Defines the Secure type. */
typedef struct
{
  NO_SEGMENT     no_appli;								/*!< number of the application*/
#ifndef __FRAMEWORK_TELIUM_PLUS__
  FILE          *stream;									/*!< stream.*/
#else
  Telium_File_t *stream;									/*!< stream.*/
#endif
  HISTORIC       historic;								/*!< historical*/
  int            cr;											/*!< report*/
} T_Secur;

/*! @brief This type define a Date.*/
typedef struct
{
  char  Jour;													/*!< day, from 1 to 31 */
  char  Mois;													/*!< month, from 1 to 12 */
  char  JourSemaine;									/*!< day of the week, from 0 to 6 (0 for sunday to 6 for saturday).*/
  short Annee;												/*!< year, from 1800 to 2200.*/
} T_Date;

/*! @brief Define a Time.*/
typedef struct
{
  char  Heure;										/*!< hour, from 0 to 23*/
  char  Minute;										/*!< minutes, from 0 to 59*/
  char  Seconde;									/*!< seconds, from 0 to 59*/
  short Centieme;									/*!< hundredth of second, from 0 to 99*/
} T_Timesv;

/*! @brief Define a Time.*/
typedef struct 
 {
 unsigned char Heure;									/*!< hour, from 0 to 23*/
 unsigned char Minute;								/*!< minutes, from 0 to 59*/
 unsigned char Seconde;								/*!< seconds, from 0 to 59*/
 unsigned char Centieme;							/*!< hundredth of second, from 0 to 99*/
 } T_Time;

/*! @brief Define the OS parameters structure.*/
typedef struct
{
char OS_Marque[15];										/*!< brand of the OS*/
char OS_Type[30];											/*!< type of the OS*/
char OS_CodeProduit[15];							/*!< product code of the OS*/
char OS_CRCAppli[20];									/*!< CRC of the applications*/
char OS_Version[5];										/*!< current version of the OS*/
char OS_DateVersion[8];								/*!< date version*/
} PARAM;

/*! @brief This type define an information structure about the OS.*/
typedef struct {
  char              OS_Version[8];						/*!< version of the OS*/
  char              OS_DateVersion[8];				/*!< date version*/
  char              OS_HeureVersion[4];				/*!< hour version*/
  unsigned short    OS_CRCAppli;							/*!< CRC of the applications*/
  char              OS_Libelle[30];						/*!< name of the OS*/
} CONFIGLOG;

/*! @brief This type define an extended information structure about the OS, based on CONFIGLOG.*/
typedef struct {
  char      OS_Marque[15];								/*!< brand of the OS*/
  char      OS_Type[30];									/*!< type of the OS*/
  char      OS_Serie[20];									/*!< series of the OS*/
  char      OS_CodeProduit[15];						/*!< product code of the OS*/
  CONFIGLOG conf_appli[7];								/*!< basic information structure about the OS*/
} CONFIGTPE;

/*! @brief Define the different bits (start, stop, parity...).*/
typedef struct
{
  short BaudRate;									/*!< 1*/
  char  StartBit;									/*!< 1 */
  char  DataBit;									/*!< 7 or 8 */
  char  ParityBit;								/*!< NO, EVEN, or ODD */
  char  StopBit;									/*!< 0 or 2*/
} T_ParamSerie;


#define max_trame_pss 0x8000			/*!< format of the table in return for the pss */ 
/*! @brief Define the return table of the PSS.*/
typedef struct
{
  unsigned short int    nombre;								/*!< length of the data.*/
  unsigned char donnees [max_trame_pss];			/*!< data.*/
} BUFFER_PSS ;

#define CONDENSE 0x0F
#define SIMPLE   0x12
#define DOUBLE   0x0E

#define OS_OK      0
#define OS_KO      1
#define OS_ERREUR  2
#define OS_TIMEOUT 3

#define OS_PARAM_INCORRECT  4
#define OS_COM_PAS_INIT     12
#define OS_COM_TO         11

#define OS_CAM_OK     0
#define OS_NO_CAM     1 
#define OS_MUTE_CAM   2
#define OS_ERROR      3
#define OS_PARAM      4
#define OS_CAM_OFF    5
#define OS_NO_PRES    6
#define OS_MUETTE     7
#define OS_HORS_TENS  8

#define OS_DONNEES_PAS_RENSEIGNES 2
#define OS_CRC_KO 13
#define OS_NON_INTEGRE 15
#define OS_IDENT_INCOR 16
#define OS_PB_ADRESSE  17
#define OS_TROP_GRAND  18

#define OS_CAM_PRESENT     0x0001
#define OS_CAM_ARRACHEE    0x0002
#define OS_CAM_CONNECTEE   0x0004
#define OS_DET_OK  5

#define OS_OUT_ORDER  0
#define OS_IN_ORDER   1

#define OS_CORR   0x3A
#define OS_F      0x3B
#define OS_ANN    0x3D
#define OS_VAL    0x3E
#define OS_ESC    0x1B

#define OS_COM1           1
#define OS_COM2           2
#define OS_9600           1
#define OS_19200          2
#define OS_38400          4
#define OS_57600          6
#define OS_115200         12
#define OS_START          1
#define OS_8BIT           8
#define OS_7BIT           7
#define OS_NO_PARITY      0
#define OS_ODD_PARITY     1
#define OS_EVEN_PARITY    2
#define OS_1STOP          0
#define OS_2STOP          2

#define BUFFER_VIDE       0
#define BUFFER_NON_VIDE   1
#define BUFFER_SATURE     2

#define OS_MAXDELAY       3

#define DESACTIVE         0
#define ACTIVE            1
#define TERMINE           2
#define TERMINE_ACTIF     3

#define OS_CAM2           3
#define OS_CAM0           2
#define OS_CAM1           1
#define OS_SAM            0

#define JANVIER        1
#define FEVRIER        2
#define MARS           3
#define AVRIL          4
#define MAI            5
#define JUIN           6
#define JUILLET        7
#define AOUT           8
#define SEPTEMBRE      9
#define OCTOBRE        10
#define NOVEMBRE       11
#define DECEMBRE       12

#define DIMANCHE       0
#define LUNDI          1
#define MARDI          2
#define MERCREDI       3
#define JEUDI          4
#define VENDREDI       5
#define SAMEDI         6

#define INTERNE        0
#define TERM           1

//! \brief Define a pointer to a function.
typedef void (*PTRFUNCTION)(void);


/*! @brief [French Healthcare] OS_ClkDate Read Date
@param Date: date
@return 0 OK or 1 CRC error
@par exit (EXIT_DLL_SV_NOT_INITIALIZED + 1) if function does not exist
*
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_ClkDate(T_Date *Date);


/*! @brief [French Healthcare] OS_ClkGetMilliseconds return milliseconds elapsed since terminal reboot
@return milliseconds elapsed
@par exit (EXIT_DLL_SV_NOT_INITIALIZED + 46) if function does not exist
*
 * @link KSFAM_SANTE Back to top @endlink
*/
int OS_ClkGetMilliseconds(void);



/*! @brief [French Healthcare] OS_ClkTime Read Time
@param Time: time
@return 0 OK or 1 CRC error
@par exit (EXIT_DLL_SV_NOT_INITIALIZED + 2) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_ClkTime(T_Time *Time);




/*! @brief [French Healthcare] OS_ClkInit initialize Date and Time
@param Date
@param Time
@return 0 OK
@return 1 parameters erroneous
@return 2 hardware error
@par exit (EXIT_DLL_SV_NOT_INITIALIZED + 3) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_ClkInit(T_Date *Date,T_Time *Time);




/*! @brief [French Healthcare] [French Healthcare] OS_ScrInit clears the screen.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 4) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
void  OS_ScrInit(void);


/*! @brief [French Healthcare] This function displays a message on the screen.
 * @param Message : input parameter. Message to display (32 max.)
 * @param Position : input parameter. location on the screen between 1 and 32.
 * @return None.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 5) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
void  OS_ScrMessage(char *Message,short Position);


/*! @brief [French Healthcare] This function empties the keyboard buffer.
 * @return None.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 6) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
void  OS_KbdFlush(void);


/*! @brief [French Healthcare] This function reads a keyboard key.
 * @return
 * - Key pressed.
 * - 0 if no key to read.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 7) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_KbdKey(void);


/*! @brief [French Healthcare] This function generates a BIP.
 * @param usDelay : input parameter. beep duration in period of 100 ms
 * @return None
 * -  OS_OK
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 8) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_SndBip(unsigned short usDelay);


/*! @brief [French Healthcare] This function closes the smart card reader
 * @param NumCoupleur : smart card reader number. 
 * -  OS_CAM0 = extern smart card reader.
 * -  OS_CAM1 = inner smart card reader.
 *
 * @return
 * -  OS_OK
 * -  OS_ERROR invalid smart card reader.
 * -  OS_PARAM invalid smart card reader number.
 * -  OS_NO_PRES card absent.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 9) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_CamOff(unsigned char NumCoupleur);


/*! @brief [French Healthcare] This routine returns the card state.
 * @param NumCoupleur : smart card reader number. 
 * -  OS_CAM0 = extern smart card reader.
 * -  OS_CAM1 = inner smart card reader.
 *
 * @param Etat : output parameter. Status of the card. bit field.
 * -  OS_CAM_CONNECTEE
 * -  OS_CAM_PRESENT
 * -  OS_CAM_ARRACHEE
 *
 * @param Cptetat : output parameter. Status meter. The status meter is incremented : 
 * -   to each power on (OS_CamReset).
 * -   to each power off(OS_CamOff).
 * -   at first card removal after a power off.
 * -   at card removal if it is powered on.
 *
 * @return
 * -   OS_OK
 * -   OS_PARAM invalid smart card reader number.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 13) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_CamEtat(unsigned char NumCoupleur,short *Etat,short *Cptetat);


/*! @brief [French Healthcare] This function initialises the CAM number associated to the smart card reader.
 * @param NumCoupleur : smart card reader number. 
 * -   OS_CAM0 = extern smart card reader.
 * -   OS_CAM1 = inner smart card reader.
 *
 * @param val : index of physical smart card reader.
 * -  0 ==> "CAM0"
 * -  1 ==> "CAM1"
 * -  and so on.
 *
 * @return OS_OK
 * @par exit none
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_CamInit(unsigned char NumCoupleur,int val);


/*! @brief [French Healthcare] This function resets card removal indicator.
 * @param NumCoupleur : smart card reader number. 
 * -  OS_CAM0 = extern smart card reader.
 * -  OS_CAM1 = inner smart card reader.
 *
 * @return
 * -  OS_OK
 * -  OS_PARAM invalid smart card reader number.
 * -  OS_DET_OK removal indicator set to 0.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 14) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_CamInitEtat(unsigned char NumCoupleur);


/*! @brief [French Healthcare] This function sends an order to the reader.
 * @param NumCoupleur : smart card reader number. 
 * -  OS_CAM0 = extern smart card reader.
 * -  OS_CAM1 = inner smart card reader.
 *
 * @param TypeOrder : order type.
 * -  OS_IN_ORDER input order.
 * -  OS_OUT_ORDER output order.
 *
 * @param Order : 
 * -  as input parameter : order to be sent to the card.
 * -  as output parameter : answer of the card.
 *
 * @return
 * -  OS_OK
 * -  OS_ERROR invalid reader
 * -  OS_PARAM invalid reader number.
 * -  OS_MUETTE mute card.
 * -  OS_NO_PRES card absent.
 * -  OS_HORS_TENS card powered off.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 10) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_CamOrder(unsigned char NumCoupleur,
                  unsigned char TypeOrder,char *Order);


/*! @brief [French Healthcare] This function sends an order to the reader.
 * @param NumCoupleur : smart card reader number. 
 * -  OS_CAM0 = extern smart card reader.
 * -  OS_CAM1 = inner smart card reader.
 *
 * @param TypeOrder : order type.
 * -  OS_IN_ORDER input order.
 * -  OS_OUT_ORDER output order.
 *
 * @param Order :
 * -  as input parameter : order to be sent to the card.
 * -  as output parameter : answer of the card.
 *
 * @param LgOrder : size of the data received from the card.
 *
 * @return
 * -  OS_OK
 * -  OS_ERROR invalid reader
 * -  OS_PARAM invalid reader number.
 * -  OS_MUETTE mute card.
 * -  OS_NO_PRES card absent.
 * -  OS_HORS_TENS card powered off.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 45) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_CamOrderLg(unsigned char NumCoupleur,
                  unsigned char TypeOrder,char *Order,
                  unsigned short *LgOrder);


/*! @brief [French Healthcare] This function tests if the card is present.
 * @param NumCoupleur : smart card reader number. 
 * -  OS_CAM0 = extern smart card reader.
 * -  OS_CAM1 = inner smart card reader.
 *
 * @return
 * -  OS_OK card present.
 * -  OS_NO_PRES card absent
 * -  OS_PARAM invalid smart card reader number.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 11) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_CamPres(unsigned char NumCoupleur);


/*! @brief [French Healthcare] This function performs a reset on card reader.
 * @param NumCoupleur : smart card reader number. 
 * -  OS_CAM0 = extern smart card reader.
 * -  OS_CAM1 = inner smart card reader.
 *
 * @param Reponse : output parameter. Answer to reset (ATR).
 * @param LgReponse : output parameter. Length of answer to reset.
 * @return
 * -  OS_CAM_OK
 * -  OS_ERROR invalid smart card reader.
 * -  OS_MUETTE mute card.
 * -  OS_NO_PRES card absent.
 * -  OS_PARAM invalid smart card reader number.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 12) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_CamReset(unsigned char NumCoupleur,unsigned char *Reponse,unsigned short *LgReponse);


/*! @brief [French Healthcare] This function is used to get system identification.
 * @param Param : pointer to structure PARAM.
 * @return OS_OK
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 16) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_SysGetParam(PARAM *Param);


/*! @brief [French Healthcare] This function checks system integrity
 * @return OS_OK
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 15) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_SysVerif(void);


/*! @brief [French Healthcare] This function is used to get the identification of reader.
 * @param Config : pointer to structure CONFIGTPE.
 * @return none
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 0) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
void  OS_GetIdLecteur(CONFIGTPE *Config);


/*! @brief [French Healthcare] This function is used to get the application identification.
 * @param stParam : pointer to stucture PARAM.
 * @param noappli : application identifier.
 * @return OS_OK
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 17) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
short OS_SysGetParamAppli(PARAM *stParam,int noappli);

/*! @brief [French Healthcare] OS_SysGetFreeSpace returns the available memory size.
* @return Memory size in Kb.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 18) if function does not exist
 *
 * @link KSFAM_SANTE Back to top @endlink
*/
unsigned int OS_SysGetFreeSpace(void);




/*! @brief [French Healthcare] This function returns the difference between 2 Dates.
 * @param Date1 : pointer to structure T_Date 1
 * @param Date2 : pointer to structure T_Date 2
 * @param type : type of the date, 0 or 1
 * @return Difference (days).
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 25) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
int  SLSQ_EcartDate        (T_Date *Date1,T_Date *Date2,unsigned char type);


/*! @brief [French Healthcare] This function returns the number of hour between two times.
 * @param Time1 : pointer to structure T_Time 1.
 * @param Time2 : pointer to structure T_Time 2.
 * @return Number of hour.
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 26) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
int  SLSQ_EcartHeure       (T_Time *Time1,T_Time *Time2);



/*! @brief [French Healthcare] This function returns the day of the week.
 * @param Date : pointer to structure T_Date.
 * @return Day (sunday = 0).
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 27) if function does not exist
 *
 * @link KSFAM_USQ Back to top @endlink
*/
char SLSQ_CalculJourSemaine(T_Date *Date);


#endif
/*! @} **/
#ifdef __cplusplus
}
#endif
