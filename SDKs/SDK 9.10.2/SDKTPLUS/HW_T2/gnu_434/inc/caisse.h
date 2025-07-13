/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CAISSE_H
#define CAISSE_H

#define CR_DIALOGUE_OK        0
#define CR_DIALOGUE_KO        1
#define CR_DIALOGUE_IMPR      2
#define CR_DIALOGUE_NONDEBIT  3
#define CR_DIALOGUE_INDIC2    4
#define CR_DIALOGUE_PB_DEVISE 5
#define CR_DIALOGUE_ISO2      6

#define PROTOCOLE_A         0
#define PROTOCOLE_B_ENVOI   1
#define PROTOCOLE_B_NENVOI  2
#define PROTOCOLE_C         3
#define PROTOCOLE_E         5
#define PROTOCOLE_E_PLUS    6
#define PROTOCOLE_F         7
#define PROTOCOLE_F_PLUS    8

#define INDICATEUR_TYPEB  '1'

#define TYPE_DEBIT        '0'
#define TYPE_CREDIT       '1'
#define TYPE_ANNULATION   '2'
#define TYPE_DUPLICATA    '3'
#define TYPE_PRE_AUTO     '4'

#define PAIE_KO           '1'
#define PAIE_OK           '0'
#define PAIE_NON_ABOUTI_E '7'
#define PAIE_EN_COURS     '9'

/* CR lecture ISO 2 */
#define CR_ISO_OK      '0'
#define CR_ISO_TO      '1'
#define CR_ISO_LUHN    '3'
#define CR_ISO_NO_DATA '6'
#define CR_ISO_KO      '4'
#define LG_REP_ISO     46

/* protocole caisse IP*/
#define IP_ETHERNET 20

#ifndef _EXPORT_

/*! @brief This structure describes an input transaction of the cash register.*/
typedef struct
{
	TYPE_SUPPORT       support;						/*!< type of base*/
    TYPE_SAISIE        saisie;					  /*!< type of entry*/
	TYPE_MODE_PAIEMENT paiement;					/*!< mode of payment*/
	TYPE_TRANSAC       transaction;				/*!< type of transaction*/
	MONTANT            montant;						/*!< transaction amount*/
	S_MONEY            monnaie;						/*!< transaction currency (French domain only)*/
	T_NOCAISSE         caisse;						/*!< cash register number (French domain only)*/
	BUFFER_PISTE2      piste2;						/*!< a track 2 buffer*/
	ZONE_PRIV          zone_privee;				/*!< private data from cash register (French domain only) */
	int                auto_force;					/*!< auto-forcing (Y/N) */
} S_TRANSINCAISSE;

/*! @brief This structure describes an output transaction of the cash register.*/
typedef struct
{      
   NO_SEGMENT    noappli;							  /*!< number of the application*/
   unsigned char cr_paiement;						/*!< payment report*/
   NO_PORTEUR    no_porteur;						/*!< number of the holder*/
} S_TRANSOUTCAISSE;

#else

/*! @brief This structure describes an input transaction of the cash register.*/
typedef struct
{      
	SUPPORT_TYPE       support;						/*!< type of base*/
  ENTRY_TYPE         entry;			  			/*!< type of entry*/
	PAYMENT_MODE       payment;						/*!< mode of payment*/
	TRANSACTION_TYPE   transaction;				/*!< type of transaction*/
	MONTANT            amount;						/*!< transaction amount */
	S_MONEY            currency;					/*!< transaction currency ( French domain only ) */
	T_NOCAISSE         cashreg;						/*!< cash register number ( French domain only ) */
	ZONE_PRIV          private_data;			/*!< private data from cash register ( French domain only ) */
	int                forcing;					/*!< auto-forcing (Y/N) */
} S_TRANSINCAISSE;

#define HOLDER_NB NO_PORTEUR
/*! @brief This structure describes an output transaction of the cash register.*/
typedef struct
{      
   NO_SEGMENT    noappli;							/*!< number of the application*/
   unsigned char rc_payment;					/*!< payment report*/
   HOLDER_NB     card_holder_nb;			/*!< number of the holder*/
} S_TRANSOUTCAISSE;

#endif

/*! \brief Define a pointer on a function used to sale the cash register.*/
typedef void  (*PFONCDEBITCAISSE)(S_TRANSINCAISSE *In,S_TRANSOUTCAISSE *Out);



#endif

/*! @} **/
#ifdef __cplusplus
}
#endif
