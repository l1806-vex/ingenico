/*! @addtogroup KSFAM_M2OS
	* @{
*/


#ifndef _INC_MODEM_
#define _INC_MODEM_

/*
======================================================================
					List of Defines
======================================================================
*/
#define CR_FCT_EN_COURS    0xFF
#define NO_HORS_LIGNE 0

/* comptes rendus d'emission et reception */

#define CR_MODEM_OK		0
#define CR_MODEM_NOK		1
#define CR_MODEM_STOP           2
#define CR_MODEM_PORTEUSE_NOK   3
#define CR_MODEM_TO		4

/*
======================================================================
			Data Structures Definition
======================================================================
*/

typedef struct{
 byte   masque_sauv;
 word   tache_courrante;
 byte   cr_fct;
 byte   saisie_hl;
 byte   touche_hl;
 dword  cr_ttestall;
 word   index ;
 size_t nb_car;
 byte   trouve_ca;
 size_t lg_read;
 byte   valid_DCD;
 byte   x_fonction;
 byte  *x_ad_buffer;
 word   x_to_global;
 word   x_to_car        ;
 word   x_to_inter;
 word   x_butee;
 byte   x_arret1;
 byte   x_arret2;
 byte   x_lg_arret;
 word   x_lg_buffer;
 word   lg_write;
 byte   nb_restants;
 dword  evt_modem;
 byte   cr_fin;
 FILE  *modem;
 FILE  *clavier;
}t_apm;
//format de la table en entree pour reception sur code arret 

/*! @brief This structure describes the entry table for reception on a stop code. */
//GSIM_T:TAB_REC_CA:DATA_CODE( 4 * 2 + sizeof(word) + sizeof(byte) * 4 )  
// @GSIM_T:TAB_REC_CA:SUPPLIED(BUF_SER_TAB_REC_CA;BUF_DES_TAB_REC_CA) 
typedef struct {
                byte * ad_buffer_attendu ;			/*!< expected buffer*/
                word * ad_longueur_recue ;			/*!< received data length	*/
                word butee;											/*!< stubborn*/
                byte time_out ;									/*!< reception time out*/
                byte nb_car_code_arret;					/*!< number of characters of stop code.*/
                byte code_arret_1 ;							/*!< stop code 1*/
                byte code_arret_2 ;							/*!< stop code 2*/
				 } TAB_REC_CA ;

/*! @brief This structure describes the entry table for reception on a stop code.*/
//GSIM_T:TAB_REC_TO:DATA_CODE( 4 * 2 + sizeof(word) * 2 + sizeof(byte) * 2 )
//GSIM_T:TAB_REC_TO:SUPPLIED(BUF_SER_TAB_REC_TO;BUF_DES_TAB_REC_TO) 
typedef struct {
                byte * ad_buffer_attendu ;			/*!< expected buffer*/
                word * ad_longueur_recue ;			/*!< received data length*/
                word butee;											/*!< stubborn*/
                byte time_out_global ;					/*!< global time out*/
                byte time_out_1er_car ;					/*!< first case time out*/
                word time_out_inter ;						/*!< intermediary time out */
				 } TAB_REC_TO ;
	

/* declaration externe des fonctions */
extern unsigned char Hors_Ligne (void );

// \if SIMULATION
//  @GSIM_F:Validation_Hors_Ligne:KSFAM_M2OS:0x53
//  @GSIM_A:2:ONE_ADDRESS
// \endif
extern void          Validation_Hors_Ligne ( unsigned char  , FILE * , word );

// \if SIMULATION
//  @GSIM_F:Devalidation_Hors_Ligne:KSFAM_M2OS:0x52
// \endif
extern void          Devalidation_Hors_Ligne ( void);


/*! @brief This function sends a data modem buffer.
 * @param * : buffer
 * @param buf_size : size of the buffer
 * @return 
 * - CR_MODEM_OK 0
 * - CR_MODEM_NOK 1
 * - CR_MODEM_STOP 2
 * - CR_MODEM_PORTEUSE_NOK 3
 * - CR_MODEM_TO 4
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 9) if function does not exist
 *
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Emission_Modem:KSFAM_M2OS:0x54
//  @GSIM_A:1:DATA_SIZE(buf_size)
// \endif
extern unsigned char Emission_Modem ( unsigned char * , unsigned short int buf_size);



/*! @brief receive a data modem buffer on counter of bytes.
* @param * : buffer
* @param buf_size : size of the buffer
* @param to : time out
* @return 
* - CR_MODEM_OK
* - CR_MODEM_NOK
* - CR_MODEM_TO
* - CR_MODEM_STOP
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 10) if function does not exist
*
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Reception_Co_Modem:KSFAM_M2OS:0x56
//  @GSIM_A:1:DATA_SIZE(buf_size)
// \endif
extern unsigned char Reception_Co_Modem ( unsigned char * , unsigned short int buf_size, unsigned char to );

/*! @brief receive a data modem buffer on stop code.
* @param pt_infos : pointer to TAB_REC_CA structure ( see modem .h ).
* @return 
* - CR_MODEM_OK
* - CR_MODEM_NOK
* - CR_MODEM_TO
* - CR_MODEM_STOP
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 11) if function does not exist
*
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Reception_Ca_Modem:KSFAM_M2OS:0x55
//  @GSIM_A:1:ONE_POINTER
// \endif
extern unsigned char Reception_Ca_Modem ( TAB_REC_CA * pt_infos);


/*! @brief receive a data modem buffer on stop code.
* @param pt_infos : pointer to TAB_REC_TO structure ( see modem .h ).
* @return 
* - CR_MODEM_OK
* - CR_MODEM_NOK
* - CR_MODEM_TO
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 12) if function does not exist
*
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Reception_To_Modem:KSFAM_M2OS:0x57
//  @GSIM_A:1:ONE_POINTER
// \endif
extern unsigned char Reception_To_Modem ( TAB_REC_TO * pt_infos);


/*! @brief receive a data modem buffer .
* @param pt_infos : pointer to TAB_REC_CA structure ( see modem .h ).
* @return 
* - CR_MODEM_OK
* - CR_MODEM_NOK
* - CR_MODEM_TO
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 13) if function does not exist
*
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Reception_To_Modem:KSFAM_M2OS:0x57
//  @GSIM_A:1:ONE_POINTER
// \endif
extern unsigned char Reception_Buf_Modem ( TAB_REC_CA * pt_infos);


/*! @brief enable carrier detect .
* @return
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 14) if function does not exist
*
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Validation_DCD:KSFAM_M2OS:0x51
// \endif
extern void          Validation_DCD(void);

/*! @brief disable carrier detect .
* @return
* @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 15) if function does not exist
*
 * @link KSFAM_M2OS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Devalidation_DCD:KSFAM_M2OS:0x50
// \endif
extern void          Devalidation_DCD(void);

#endif
/*! @} **/
