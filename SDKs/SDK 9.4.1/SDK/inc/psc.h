/*! @addtogroup KSFAM_PSC
	* @{
**/


#ifndef _PSC_INCLUDE_
#define _PSC_INCLUDE_
/*
======================================================================
					List of Defines
======================================================================
*/
//records of psc

#define CR_FCT_OK			0
#define CR_FCT_ETB_REC		1
#define CR_FCT_IN_PROGRESS	2	
#define CR_FCT_ABORT		3
#define CR_FCT_ERROR 		4
#define CR_FCT_TO 	  		5
#define CR_FCT_TIMER 		6


//definitions of current values of parameters

#define _ETB_          10
#define _ETX_          20
#define _ETB_BEGIN_    30
#define _ETX_END_      40

#define _DLE_    10
#define _NO_DLE_  0

#define NO_WAIT   0

#define NUL_TRAME 00000000
#define max_trame 300

/*
======================================================================
			Data Structures Definition
======================================================================
*/
//format de la table en retour de la psc */ 
/*! @brief Define the return table of the PSC.*/
typedef struct {
		unsigned short int nombre;								/*!<  size of data */
		unsigned char donnees [max_trame];				/*!<  data */
} BUFFER_PSC ;



/*! @brief Define a pointer on a PSC function to open.*/
typedef FILE          *(*PFONCPSC_OPEN)(void);

/*! @brief Define a pointer on a PSC function to close.*/
typedef void           (*PFONCPSC_CLOSE)(FILE *);

/*! @brief Define a PSC function to overbalance.*/
typedef unsigned char  (*PFONCPSC_BASCUL)(BUFFER_PSC *);

//format de la table en entree pour la psc
/*! @brief Define the entry table for the psc.*/
typedef struct {
              	PFONCPSC_OPEN      fonction_open;				/*!< pointer on a PSC function to open.*/
                PFONCPSC_CLOSE     fonction_close;			/*!< pointer on a PSC function to close.*/
                PFONCPSC_BASCUL    fonction_basculement;/*!< pointer on a PSC function to overbalance.*/
                unsigned int       evt_periph ;					/*!< peripherical event on wich the reception is waited*/
								unsigned char	   dle;										/*!< management of the DLE Y/N*/
                unsigned short int lg_emi_trame;				/*!< length of the emission framework.*/
                unsigned short int lg_rec_trame;				/*!< length of the reception framework*/
	  						unsigned char      nb_rep_trame;				/*!< number of framework repetition*/
								unsigned char      nb_rep_enq;					/*!< number of ENQ repetition*/
                unsigned short int to_retournement ;		/*!< time out*/
                unsigned short int to_rec_enq ;					/*!< ENQ reception time out*/
                unsigned short int to_rec_stx ;					/*!< STX reception time out*/
                unsigned short int to_rec_trame ;				/*!< framework reception time out*/
                unsigned short int to_rec_eot ;					/*!< EOT reception time out*/
                unsigned short int to_rec_inter_car ;		/*!< inter-character reception time out*/
                unsigned short int to_emi_enq ;					/*!< ENQ emission time out*/
                unsigned short int to_rec_ack1 ;				/*!< ACK1 time out*/
                unsigned short int to_rec_ack2 ;				/*!< ACK2 time out*/
                unsigned short int to_deconnex ;				/*!< disconnection time out*/
		 } TAB_ENTRY_PSC;

//format de la table en entree pour la psc
/*! @brief Define the entry table for the psc.*/
typedef struct {
                TAB_ENTRY_PSC       in;								/*!< PSC entry table*/
                unsigned char      *buf_send;					/*!< sent buffer*/
                unsigned short int  lg_send;					/*!< length of the buffer*/
                unsigned char       car_send;					/*!< sent character*/
                unsigned short int  tache;						/*!< task id*/
		 } TAB_ENTRY_COMMANDE;




/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief Initialises the PSC protocol.
 * @return None
 * @par exit (EXIT_DLL_PSC_NOT_INITIALIZED + 7) if function does not exist
 *
 * @link KSFAM_PSC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Init_Psc:KSFAM_PSC:0x02
// \endif
extern void          Init_Psc (void);


/*! @brief Opens the PSC protocol.
 * @param *TAB_ENTRY_PSC: PSC's initialization parameter structure.
 * @return None
 * @par exit (EXIT_DLL_PSC_NOT_INITIALIZED + 0) if function does not exist
 *
 * @link KSFAM_PSC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Open_Psc:KSFAM_PSC:0x01
//  @GSIM_S:Open_Psc:E_Open_Psc
// \endif
extern void          Open_Psc ( TAB_ENTRY_PSC * TAB_ENTRY_PSC);


/*! @brief Sends an emission PSC buffer.
 * @param buffer : buffer to send.
 * @param len : length of this buffer.
 * @param type:  type of emission
 * @return None 
 * @par exit (EXIT_DLL_PSC_NOT_INITIALIZED + 1) if function does not exist
 *
 * @link KSFAM_PSC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Send_Psc:KSFAM_PSC:0x03
//  @GSIM_A:1:DATA_SIZE(len)
// \endif
extern void          Send_Psc ( unsigned char * buffer, unsigned short int len , unsigned char type);


/*! @brief Receives a PSC buffer
 * @return None 
 * @par exit (EXIT_DLL_PSC_NOT_INITIALIZED + 6) if function does not exist
 *
 * @link KSFAM_PSC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Receive_Psc:KSFAM_PSC:0x04
// \endif
extern void          Receive_Psc ( void);


/*! @brief Reads the reception data.
 * @param data : buffer structure (number of data and data.
 * @return Execution report 
 * - CR_FCT_OK
 * - CR_FCT_ETB_REC
 * @par exit (EXIT_DLL_PSC_NOT_INITIALIZED + 4) if function does not exist
 *
 * @link KSFAM_PSC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Read_Psc:KSFAM_PSC:0x06
//  @GSIM_A:1:ONE_POINTER
// \endif
extern unsigned char Read_Psc ( BUFFER_PSC * data);


/*! @brief Closes the PSC protocol.
 * @return None
 * @par exit (EXIT_DLL_PSC_NOT_INITIALIZED + 3) if function does not exist
 *
 * @link KSFAM_PSC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Close_Psc:KSFAM_PSC:0x05
// \endif
extern void          Close_Psc (void);


/*! @brief Suspension of the PSC protocole.
 * @return None
 * @par exit (EXIT_DLL_PSC_NOT_INITIALIZED + 2) if function does not exist
 *
 * @link KSFAM_PSC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Suspend_Psc:KSFAM_PSC:0x07
// \endif
extern void          Suspend_Psc (void);


/*! @brief Returns an event for the PSC task to establish a contact with the computer.
 * @return None 
 * @par exit (EXIT_DLL_PSC_NOT_INITIALIZED + 5) if function does not exist
 *
 * @link KSFAM_PSC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Prise_Contact:KSFAM_PSC:0x08
// \endif
extern void          Prise_Contact(void);


/*! @brief Returns the PSC version.
 * @return PSC version
 * @par exit None
 *
 * @link KSFAM_PSC Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:Version_Psc:KSFAM_PSC:0x09
// \endif
extern int           Version_Psc ( void);

/* definition table de reponse */
/*! @brief Define the report table.*/
typedef struct {
                unsigned char      cr_message;								/*!< report message*/
								unsigned short int lgalire;										/*!< length of the data to read.*/
                unsigned char      donneesalire [max_trame] ;	/*!< data to read.*/
								unsigned short int lgrec;											/*!< length of the record data*/
                unsigned char      donneesrec [max_trame];		/*!< record data*/
} TAB_CR ;

#endif
/*! @} **/
