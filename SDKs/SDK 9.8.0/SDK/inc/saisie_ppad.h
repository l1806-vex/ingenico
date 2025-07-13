/*! @addtogroup KSFAM_PPS_MANAGER
	* @{
**/
 
#ifndef _SAISIE_PPAD_P
#define _SAISIE_PPAD_P



/* 
 Definition of application codes keys PP30
 */
#define TC_FONCTION_PPAD               0x24   
#define TC_ANNULATION_PPAD             0x25 
#define TC_CORRECTION_PPAD             0x26   
#define TC_VALIDATION_PPAD             0x27   
#define TC_VIRGULE_PPAD                0x28
#define TC_ETOILE_PPAD                 0x20
#define TC_ZERO_PPAD                   0x30 
#define TC_SK1_PPAD                    0x19
#define TC_SK2_PPAD                    0x21
#define TC_SK3_PPAD                    0x22
#define TC_SK4_PPAD                    0x23


/*
 Before Reports 
 */
/*!< Report for PPS_Read_Entry function */
#define CR_ENTRY_PINPAD_OK            0  /*!< Successful entry. d_entry[0] contains the index of the selected item in the list for G_List_Entry d_len contains the entry length d_entry [50] contains the entry for G_Numerical_Entry . */
#define CR_ENTRY_PINPAD_NOK           1  /*!< Entry not correct */
#define CR_ENTRY_PINPAD_CANCEL        2	 /*!< Entry Cancelled */
#define CR_ENTRY_PINPAD_TIME_OUT      3  /*!< Timeout elapsed  */
#define CR_ETRYE_PINPAD_FCT           4  /*!< F key pushed (if authorised )  */
#define CR_ENTRY_PINPAD_IN_PROGRESS   5  /*!< Entry in progress*/
#define CR_ENTRY_PINPAD_VALIDATED     6  /*!< Entry validated*/
#define CR_ENTRY_PINPAD_BREAK         7  /*!<  Entry break*/
#define CR_ENTRY_PINPAD_SK1           8  /*!< SK1 ('1' on EFT930M or ML30) key pushed (if authorised ) */
#define CR_ENTRY_PINPAD_SK2           9  /*!< SK2 ('2' on EFT930M or ML30) key pushed (if authorised ) */
#define CR_ENTRY_PINPAD_SK3           10 /*!< SK3 ('3' on EFT930M or ML30) key pushed (if authorised ) */
#define CR_ENTRY_PINPAD_SK4           11 /*!< SK4 ('4' on EFT930M or ML30) key pushed (if authorised )  */
#define CR_ENTRY_PINPAD_BAD_PIN_LEN   12 /*!< Incorrect Pin length  */
/*
 Before Reports 
 */
#define CR_SAISIE_PINPAD_OK            0
#define CR_SAISIE_PINPAD_NOK           1
#define CR_SAISIE_PINPAD_ANNUL         2	
#define CR_SAISIE_PINPAD_TIME_OUT      3
#define CR_SAISIE_PINPAD_FCT           4
#define CR_SAISIE_PINPAD_EN_COURS      5
#define CR_SAISIE_PINPAD_VAL           6
#define CR_SAISIE_PINPAD_ARRET         7
#define CR_SAISIE_PINPAD_SK1           8
#define CR_SAISIE_PINPAD_SK2           9
#define CR_SAISIE_PINPAD_SK3           10
#define CR_SAISIE_PINPAD_SK4           11
#define CR_SAISIE_PINPAD_BAD_PIN_LEN   12


/*
 Definitions of current values of parameters
 */
#define NO_TIME_OUT_PPAD               0
    
#define NO_ECHO_PPAD                   0
#define ECHO_NORMAL_PPAD               1    
#define ECHO_SPECIAL_PPAD              2    

#define TAB_STANDARD_PPAD              0

#define CAR_SECRET_PPAD                '*'

#define REQUEST_PHASE_1                1
#define REQUEST_PHASE_2                2

#define AFFICHER_SAISIR_A_L_ABRI      0x01

/* 
 Definition of common table 
 */
/*! @brief Define a common table for all the entry. */
typedef struct {
  unsigned short mask;								/*!< entry mask*/
  unsigned short tache ;							/*!< entry task*/
  unsigned char  time_out ;						/*!< entry time out*/
  unsigned char  line ;								/*!< line where the entry will be displayed*/
  unsigned char  column ;							/*!< column where the entry will be displayed*/
  unsigned char  echo;								/*!< character to display in echo on each entry characters*/
  unsigned char  nb_max;							/*!< maximum count of entry characters*/
  unsigned char  nb_min;							/*!< minimum count of entry characters*/
  unsigned char  type_saisie;					/*!< type of entry*/
  unsigned char  efface ;							/*!< clear (Y/N).*/
  unsigned char  *tab_car;						/*!< pointer on the data buffer*/
} TAB_ENTRY_STANDARD_PPAD ;


/* 
 Definition table de reponse 
 */
/*! @brief Define a response table.*/
typedef struct {
  unsigned char  cr_message;									/*!< report of the message.*/
  unsigned char  lg_message;									/*!< length of the message*/
  unsigned char  donnees_message [50];				/*!< data of the message.*/
} TAB_EXIT_PPAD ;


/* 
 Size of table input for digital capture PPAD 
 */ 
/*! @brief Format of the entry table for a PPAD entry.*/
typedef struct {
  unsigned short mask;								/*!< entry mask*/
  unsigned char  time_out ;						/*!< entry time out*/
  unsigned char  line;								/*!< line where the entry will be displayed*/
  unsigned char  column;							/*!< column where the entry will be displayed*/
  unsigned char  echo;								/*!< character to display in echo on each entry characters*/
  unsigned char  nb_max;							/*!< maximum count of entry characters*/
  unsigned char  nb_min;							/*!< minimum count of entry characters*/
  unsigned char  timeout_inter;				/*!< inter-character entry time out.*/
  unsigned char  phase;								/*!< value of the phase : \li REQUEST_PHASE_1 1  \li REQUEST_PHASE_2 2*/
  unsigned char  ruf[2];							/*!< reserved for future use.*/
} TAB_ENTRY_STRING_PPAD ;

#endif
/*! @} **/
