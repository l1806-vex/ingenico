/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/
#ifndef NTTYPES_H
#define NTTYPES_H

/*
======================================================================
					List of Defines
======================================================================
*/

#define PT_NULL          (void *)(0)
#define NB_MAX_APPLI 15  /*v5rr -- 6 -> 15 -- */
#define NB_MAX_DLL   NUMBER_OF_DLL

#define LG_APN       (22+1)
#define LG_PIN       (8+1)
#define LG_PASSWORD  (22+1)
#define LG_LOGIN     (22+1)
#define LG_DOMAINE   (256+1)
#define MAX_RACCORD  20

/* time-out */
#define TO_EXIT            255000/XecTimeUnit  /* 255s : attente exception sur un ttestall */
#define TO_RETRAIT         10000/XecTimeUnit   /* 10s  : attente retrait de la carte puce  */
#define TO_FCT_PERIODCXE   58000/XecTimeUnit   /* 58s  : attente fonctions periodiques     */
#define TO_FINIMP          600000/XecTimeUnit  /* 10mn : attente fin impression ticket     */
#define TO_MESS            1500/XecTimeUnit    /* 1,5s : attente message visu              */
#define TO_ATTENTE_PISTE   120000/XecTimeUnit  /* 2mn  : attente piste ou puce en milli    */
#define TO_PARAM           120                 /* 2mn  : saisie des parametres en seconde  */
#define TMO_INTERCARACTERE 5000/XecTimeUnit    /* 5s   : intercaractere saisie montant     */

/* oem c return code for first_init */
#define FSE_FAILED EOF

/* function prototyping for entry routines */
/*! @brief Define a pointer on a function.*/
typedef void (*PFONC) (void *);

/*! @brief Define the number of the cash register.*/
typedef char               T_NOCAISSE [2];
/*! @brief This type define the name of anobject (application...). EFT30 like.*/
// @GSIM_T:T_AFFNOM:DATA_CODE(sizeof(T_AFFNOM)) 
typedef char               T_AFFNOM   [12+1]; /* EFT30 like */
// @GSIM_T:T_AFFNOM_EXTENDED:DATA_CODE(sizeof(T_AFFNOM_EXTENDED)) 
typedef char               T_AFFNOM_EXTENDED   [32+1]; 
/*! @brief Define a mask (EFT30 like).*/
typedef unsigned long      MASQUE;            /* EFT30 like */
/*! @brief Define the number of a holder.*/
typedef unsigned char      NO_PORTEUR [19];
/*! @brief Define a buffer for entry routines.*/
typedef char               BUFFER_MAN [33];
/*! @brief Define a type identity.*/
typedef unsigned short int TYPE;
/*! @brief Define a pointer to a character.*/
typedef char *    PT_CHAR ;

/*! @brief Define the priority table of an application.*/
typedef struct
{
 int            niv_priorite ;						/*!< priority level */
 T_AFFNOM       libelle_log  ;						/*!< name of the software.*/
 T_AFFNOM       libelle_appli  ;					/*!< name of the application*/
 unsigned char  num_applicrt ;						/*!< number of the 1 to 4 card holder application */
 NO_SEGMENT     no_appli ;								/*!< number of the application*/
} TAB_PRIORITE ;

/*! @brief Define a choice table for an application.*/
typedef struct
{
 NO_SEGMENT     no_appli ;								/*!< number of the application*/
 unsigned char  num_applicrt ;						/*!< number of the 1 to 4 holder card application*/
} TABLE_CHOIX ;

/*! @brief Define the network parameters.*/
typedef struct
{
  unsigned int  type_reseau ;										/*!< define the network type.*/
  unsigned char apn[GPRS_APN_LGR+1];		        /*!< APN, size 100+1*/
  unsigned int  liaison_serie;									/*!< com number (size 4)*/
  unsigned char login[LG_LOGIN];								/*!< login.*/
  unsigned char password[LG_PASSWORD];					/*!< password*/
  unsigned int  passerelle;											/*!< gateway*/
  unsigned int  ip;															/*!< IP address*/
  unsigned int  port;														/*!< port xxxx*/
  unsigned int  type_pad;												/*!< type of PAD*/
  int           presence_ssl;										/*!< SSL presence, Y/N*/
  unsigned char profil_ssl[PROFILE_NAME_SIZE];	/*!< SSL profile*/
  unsigned char modem_sur_socle;								/*!< is the modem on its base ?*/
  unsigned char dtr;														/*!< \li 0 if no DTR, \li 1 if DTR*/
  unsigned int  forcage_v32;										/*!< V32 forced ? Y/N*/
  unsigned char pad_forcage_v32[MAX_RACCORD];		/*!< V32 PAD forcing informations*/
  unsigned int  forcage_prefixe;								/*!< prefix forced ? (Y/N)*/
  unsigned char prefixe [10];										/*!< prefix*/
} S_PARAM_RESEAU;

/*v5rr*/
/*! @brief Serial link informations.*/
typedef union
{
  unsigned int  liaison_serie ;									/*!< serial link number*/
  unsigned int  type_pad;												/*!< type of PAD*/
} U_INFOS_LIAISON_RES ;

/*! @brief Informations about GPRS network.*/
typedef struct
{
 U_INFOS_LIAISON_RES  infos_sup_reseau ;							/*!< network informations*/
 unsigned char        apn[LG_APN];										/*!< APN*/
 unsigned char        pincode[LG_PIN];								/*!< PIN code*/
 unsigned char        login[LG_LOGIN];								/*!< login*/
 unsigned char        password[LG_PASSWORD];					/*!< password.*/
 unsigned int         passerelle;											/*!< gateway*/
 unsigned int         ip;															/*!< IP address*/
 unsigned int         port;														/*!< port xxxx*/
 unsigned int         ssl;														/*!< SSL presence, Y/N*/
 unsigned char        profil_ssl[PROFILE_NAME_SIZE];	/*!< SSL profile*/
} U_INFOS_SUP_RES_SUP ;

/*! @brief Network informations*/
typedef struct
{
  unsigned int         type_reseau ;				/*!< network type.*/
  U_INFOS_SUP_RES_SUP  infos_sup ;					/*!< GPRS network informations.*/
} S_INFOS_RESEAU_SUP ;

//! \brief Network informations for the withdrawal.*/
typedef struct
{
  S_INFOS_RESEAU_SUP   infos_sup ;					  /*!< manager network parameter for the withdrawal.*/
  int			             repli;									/*!< withdrawal.*/
  S_PARAM_RESEAU       infos_sup_repli;				/*!< manager network parameter for the withdrawal.*/
} S_INFOS_RESEAU_SUP_REPLI ;

//! \brief Define the network parameters.*/
typedef struct
{
  unsigned char apn[GPRS_APN_LGR+1];						/*!< network informations*/
  unsigned char apn_repli[GPRS_APN_LGR+1];			/*!< manager network parameter for the withdrawal*/
  unsigned char apn_tms[GPRS_APN_LGR+1];			  /*!< TMS APN (size : 100+1)*/
} S_INFOS_APN_PARAM;

//! \brief Network informations for the withdrawal.*/
typedef struct
{
  S_INFOS_RESEAU_SUP_REPLI  infos_sup ;						/*!< Network informations for the withdrawal.*/
  S_INFOS_APN_PARAM         infos_apn;						/*!< the network parameters.*/
} S_INFOS_RESEAU_SUP_APN_REPLI ;

//! \brief Network informations*/
typedef union
{
 unsigned int  cle ;								/*!< network key*/
} U_INFOS_SUP_RES ;

//! \brief Network informations*/
typedef struct
{
 unsigned int type_reseau ;							/*!< define the type of network : \li RES_RTC \li RES_RNIS \li RES_GSM_EXT \li RES_GMS_INT \li GPRS \li RES_CLE \li ...*/
 U_INFOS_SUP_RES  infos_sup ;						/*!< informations about the network*/
} S_INFOS_RESEAU ;

#endif
/*! @} **/
