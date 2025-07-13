#ifndef _INC_UCMCLIB		// For Multiple Include ...
#define _INC_UCMCLIB

#ifndef __RSA_H__ 
#ifndef SHA_H 
#include "CRYPTO_DEF.h"
#endif
#endif

#define UCMERR_IAC_NO_SERVICE (-1)
#define UCMERR_IAC_NO_MODULE (-2)
#define UCMERR_IAC_NO_FCT (-3)
#define UCMERR_IAC_FCT_RETURN (-4)

#define UCMC_IAC_BUFFER_SIZE 2048   /* MAX buffer size for IAC */

/***************************************/
/************** DISPLAY ****************/
/***************************************/
#define UCMC_IAC_BUFFER_DISPLAY_SIZE 200

typedef struct
{
	unsigned char  ucChannel ;
	char 			 ctOpen[ 5 ] ;
	unsigned short usOption;
	unsigned short usTimeout;
	char          cBuf [ UCMC_IAC_BUFFER_DISPLAY_SIZE ] ;
} T_UCMC_IAC_DISPLAY ;

typedef struct
{
	unsigned char  ucChannel ;
	char 		  ctOpen[ 5 ] ;
	unsigned short usOption;
	unsigned short usContinus;
	unsigned short usTimeout1;
	char          cBuf1 [ UCMC_IAC_BUFFER_DISPLAY_SIZE ] ;
	unsigned short usTimeout2;
	char          cBuf2 [ UCMC_IAC_BUFFER_DISPLAY_SIZE ] ;
} T_UCMC_IAC_DISPLAY2 ;

#define UCMCDISPLAY_BKL_COLOR_NO_DEFINED     0x00
#define UCMCDISPLAY_BKL_COLOR_RED            0x01
#define UCMCDISPLAY_BKL_COLOR_GREEN          0x02
#define UCMCDISPLAY_BKL_COLOR_BLUE           0x03
#define UCMCDISPLAY_BKL_COLOR_CYAN           0x04
#define UCMCDISPLAY_BKL_COLOR_MAGENTA        0x05
#define UCMCDISPLAY_BKL_COLOR_YELLOW         0x06
#define UCMCDISPLAY_BKL_COLOR_BLACK          0x07
#define UCMCDISPLAY_BKL_COLOR_WHITE          0x08
#define UCMCDISPLAY_BKL_COLOR_RETRO_OFF      0xFF
#define UCMCDISPLAY_BKL_COLOR_RETRO_ON       0xFE



typedef struct {
   unsigned char       ucColorDefined ;  /* use UCMCDISPLAY_BKL_COLOR_NO_DEFINED , UCMCDISPLAY_BKL_COLOR_RED ...*/
   unsigned char       ucOption ;        /* not used must be set 0 */
   unsigned short int  usBlue;
   unsigned short int  usGreen;
   unsigned short int  usRed;
 } T_UCMC_DISPLAY_BACKLIGHT_COLOR;

/***************************************/
/************** PRINTER ****************/
/***************************************/

#define UCMC_IAC_BUFFER_PRINT_SIZE 400

typedef struct
{
	unsigned char  ucChannel ;
	char 			 ctOpen[ 5 ] ;
	unsigned short usOption;
	char          cBuf [ UCMC_IAC_BUFFER_PRINT_SIZE ] ;
} T_UCMC_IAC_PRINT ;

typedef struct
{
	unsigned char  ucChannel ;
	char 			 cKey;
	char 			 cWeight;
	char 			 cDensity;
	unsigned char  ucOption[4];
	unsigned short usSize;

	char          cPattern [ UCMC_IAC_BUFFER_PRINT_SIZE ] ; /* size must be over */
} T_UCMC_IAC_PRINTPATTERN ;

/***************************************/
/************** DEVICE  ***************/
/**************************************/

typedef struct
{
	unsigned char           ucChannel ;
	T_UCM_DEVICE          sDevice;
} T_UCMC_CHANNEL_DEVICE ;

/***************************************/
/************** ICC  *******************/
/***************************************/
#define UCMC_IAC_BUFFER_ICC_SIZE 255
typedef struct
{
	unsigned char ucChannel ;
	char 			 ctOpen[ 5 ] ;
	unsigned short usOption ;
	unsigned short usHeaderLg ;
	unsigned char  ucHeaderBuf [ UCMC_IAC_BUFFER_ICC_SIZE ] ;
	unsigned short usDataLg ;
	unsigned char ucDataBuf [ UCMC_IAC_BUFFER_ICC_SIZE ] ;
	unsigned char ucStatusWord1;
	unsigned char ucStatusWord2;
} T_UCMC_IAC_ICC ;

typedef struct
{
	unsigned char  ucP1 ;
	unsigned char  ucP2 ;
	unsigned char  ucP3 ;
	unsigned char  ucP4 ;
	unsigned char  ucP5 ;
} T_UCMC_IAC_ICC_CMD_INITGK ;

typedef struct
{
	int            ucP1 ;   /* oulala c'est un int */
	unsigned char  ucP2 ;
} T_UCMC_IAC_ICC_CMD_FORMAT ;

typedef struct
{
	int            iCmd ;         /* 0 = descative ICL */
	int            iCmdDeselect ; 
	int            iCmdWaitCard ; 
	unsigned short usCmdWaitTO ; /* en secondes */
} T_UCMC_IAC_ICC_CMD_ICL ;

#define UCMCICC_CMD_INITGK 1
#define UCMCICC_CMD_FORMAT 2
#define UCMCICC_CMD_ICL    3
#define UCMCICC_CMD_LOCK   4
#define UCMCICC_CMD_GET_HANDLE   5

typedef struct
{
    unsigned char ucChannel ;
    char 			 ctOpen[ 5 ] ;
    unsigned short usOption ;
    unsigned short usCmd ;
    union 
    {
        unsigned char               ucData [ UCMC_IAC_BUFFER_ICC_SIZE * 4 ] ;
        T_UCMC_IAC_ICC_CMD_INITGK   sInitGK ;
        T_UCMC_IAC_ICC_CMD_FORMAT   sFormatIcc ;
        T_UCMC_IAC_ICC_CMD_ICL      sCmdIcl;
        FILE          *pFHandle;
        unsigned char ucLock;  /* 0=OFF 1=ON */
    } u;

} T_UCMC_IAC_ICC_CMD ;

typedef struct
{
	unsigned char ucChannel ;
	char 			 ctOpen[ 5 ] ;
	unsigned short usOption ;
	/* emission */
	unsigned short usCmdLg ;
	unsigned char  ucCmdBuf [ UCMC_IAC_BUFFER_ICC_SIZE ] ;
	/* result */
	unsigned short usRCmdLg ;
	unsigned char ucRCmdBuf [ UCMC_IAC_BUFFER_ICC_SIZE ] ;
} T_UCMC_IAC_ICC_EMV ;

typedef struct
{
	unsigned char  ucChannel ;
	unsigned short usOption ;
	unsigned char  ucFunction ;
	unsigned char  ucParam ;
} T_UCMC_IAC_ICC_SYNC ;

typedef struct
{
	unsigned short usTypeCard ;	/* EMV BO, EMV */
	unsigned char  ucSubmitFormat; /* exemple PMC10S_SUBMIT_EMV_ENCIPHERED  see PPS10_Interface.h */
	unsigned char  ucLgPinCode ;
	
	R_RSA_PUBLIC_KEY sRSAPublicKey;
		
	/* RUF for generic schema */
	unsigned char  ucPositionStart ;	/* Start or paddage and finish at end */
	unsigned char  ucPositionEnd ;	/* End or paddage*/
	unsigned char  ucPaddageValue ;  /* 0x20 0xFF ... */
	unsigned char  ucFormat1 ;			/* ASCII BCD ... */
	unsigned char  ucFormat2 ;			/* */
	unsigned char  ucFormat3 ;			/* */
	unsigned char  ucConcatenation ;	/*  */

} T_UCMC_ICC_CODE ;	


typedef struct
{
	unsigned char ucChannel ;
	char 			 ctOpen[ 5 ] ;
	unsigned short usOption ;

	union
	{
		unsigned char uctData[ 1000 ] ;
		T_UCMC_ICC_CODE tCode;
	} u;
	
	/* Card command */
	unsigned short usCmdLg ;
	unsigned char  ucCmdBuf [ UCMC_IAC_BUFFER_ICC_SIZE ] ;
	
	/* result */
	unsigned short usRCmdLg ;
	unsigned char ucRCmdBuf [ UCMC_IAC_BUFFER_ICC_SIZE ] ;
} T_UCMC_IAC_ICC_PCODE ;

typedef struct
{
	unsigned char  ucTypeTrack ;	/* 1 or 2 or 3 */
	LG_REF_CLI     ucResultLg_ref;
	unsigned short usTimeout;		/* seconde */
	int  				iResultStatus;
	
	unsigned char  ucRuf1;
	unsigned char  ucRuf2;

	union
	{
	#ifdef _EXPORT_	
		TRACK1_BUFFER sTrack1;
		TRACK2_BUFFER sTrack2;
		TRACK3_BUFFER sTrack3;
   #else
	   BUFFER_PISTE1  sTrack1;  	// track 1 contents
   	BUFFER_PISTE2	sTrack2;  	// track 2 contents
	   BUFFER_PISTE3	sTrack3;  	// track 3 contents
   #endif
	} u;
} T_UCMC_ICC_TRACK ;	

typedef struct
{
	unsigned char  ucTypeTrack ;	/* 1=Track1 and/or 2=Track2  and/or 4=Track3 */
	LG_REF_CLI     ucResultLg_ref1;
	LG_REF_CLI     ucResultLg_ref2;
	LG_REF_CLI     ucResultLg_ref3;
	unsigned char  ucRuf;
	unsigned short usTimeout;		/* seconde */
	int  				iResultStatus1;
	int  				iResultStatus2;
	int  				iResultStatus3;
	
	#ifdef _EXPORT_	
	TRACK1_BUFFER sTrack1;
	TRACK2_BUFFER sTrack2;
	TRACK3_BUFFER sTrack3;
   #else
   BUFFER_PISTE1 sTrack1;  	// track 1 contents
	BUFFER_PISTE2 sTrack2;  	// track 2 contents
   BUFFER_PISTE3 sTrack3;  	// track 3 contents
   #endif
} T_UCMC_ICC_TRACKMULTI ;	

typedef struct
{
	unsigned char ucChannel ;
	char 			 ctOpen[ 5 ] ;
	unsigned short usOption ;

	union
	{
		unsigned char uctData[ 1000 ] ;
		T_UCMC_ICC_TRACK tTrack;
		T_UCMC_ICC_TRACKMULTI tTrackMulti;
	} u;
	
} T_UCMC_IAC_ICC_TRACK ;

/***************************************/
/************KEYPAD PINPAD*************/
/***************************************/
#define UCMC_IAC_BUFFER_PPAD_MES_SIZE 100
#define UCMC_IAC_BUFFER_PPAD_RES_SIZE 50

typedef struct {
	unsigned short usMask ;
	unsigned short usTask ;
	unsigned char  ucTimeout ;
	unsigned char  ucTimeout_inter ;
	unsigned char  ucLine ;          /* 1=Seconde ligne */
	unsigned char  ucColumn ;        /* 1=first column 0=bad value */
	unsigned char  ucEcho ;
	unsigned char  ucNb_max ;
	unsigned char  ucNb_min ;
	unsigned char  ucType ;
	unsigned char  ucClear ;
	unsigned char  ucPhase ;
	unsigned char  ucRuf[4] ;

	unsigned char  ucLgDisplay;
	unsigned char  uctDisplay[ UCMC_IAC_BUFFER_PPAD_MES_SIZE ];

	unsigned char  ucResultCr;
	unsigned char  ucResultLg;
	unsigned char  uctResultBuf[ UCMC_IAC_BUFFER_PPAD_RES_SIZE ];

} T_UCM_ENTRY_PPAD;

/* ucType */
#define UCM_PPAD_NUMERIQUE 1
#define UCM_PPAD_FUNCTION  2
#define UCM_PPAD_CODE  		3
#define UCM_PPAD_ALPHANUM  4

/* ucResultCr same value as "_emvdctag_.h" */
#define UCM_PPAD_RESULTCR_PIN_ENTRY_OK 0 /**< PIN Entry OK */
#define UCM_PPAD_RESULTCR_PIN_TRY_LEFT 52 /**< PIN Try limit Exceeded */
#define UCM_PPAD_RESULTCR_PIN_OK       55  /**< PIN entry entry performed */
#define UCM_PPAD_RESULTCR_NO_INPUT     56 /**< CVM End */
#define UCM_PPAD_RESULTCR_PPAD_HS      60 /**< Pinpad Out of Services */
#define UCM_PPAD_RESULTCR_CANCEL       61		/**< Pin entry cancelled */
#define UCM_PPAD_RESULTCR_TIME_OUT      62		/**< Time Out during PIN Entry */
#define UCM_PPAD_RESULTCR_CARD_REMOVED 63		/**< Card Removed */
#define UCM_PPAD_RESULTCR_CARD_ERROR 64		/**< Card Error */
#define UCM_PPAD_RESULTCR_MORE		65 /**< Internal use only */
#define UCM_PPAD_RESULTCR_ERROR_ENC_DATA		66 /**< Error during PIN Encpherment */

#define UCM_PPAD_CMD_KEY_CTRL		1      /* keyboard check key */
#define UCMC_IAC_PINPAD_CMD_BUFFER_SIZE (UCMC_IAC_BUFFER_SIZE - 48)
typedef struct
{
    int iCmd ;
    int iLg ;
    int iRet ;

    union
    {
        unsigned char ucKey;
        unsigned char ucBuf[ UCMC_IAC_PINPAD_CMD_BUFFER_SIZE ] ;
    } u;

}T_UCM_IAC_PINPAD_CMD;

typedef struct {
    unsigned char  ucChannel ;
    char 			  ctOpen[ 5 ] ;
    unsigned short usOption ;

    union
    {
        T_UCM_ENTRY_PPAD tEntry;
        T_UCM_IAC_PINPAD_CMD tCmd;
    } u;
	
} T_UCMC_IAC_PPAD ;

/***************************************/
/************** LED  *******************/
/***************************************/
typedef struct
{
	unsigned char ucLedNumber ;
	unsigned char ucCmd ;
	unsigned short usDelay ;
} T_UCMC_IAC_LED ;

typedef struct
{
   unsigned char  ucChannel ;
   T_UCMC_IAC_LED sLed ;
} T_UCMC_IAC_LEDCH ;

#define  UCMC_LED_1     0x01
#define  UCMC_LED_2     0x02
#define  UCMC_LED_3     0x04
#define  UCMC_LED_4     0x08

#define  UCMC_LED_OFF   0x00
#define  UCMC_LED_ON    0x01
#define  UCMC_LED_BLINK 0x02

#define  UCMC_LEDINTERNAL_OFF   0x10
#define  UCMC_LEDINTERNAL_ON    0x11
#define  UCMC_LEDINTERNAL_BLINK 0x12
#define  UCMC_LEDINTERNAL_1     0x01 /* Red */
#define  UCMC_LEDINTERNAL_2     0x02 /* yellow */
#define  UCMC_LEDINTERNAL_3     0x04 /* Green */

typedef struct
{
   unsigned long  ulCmd ;        /* led pack command */
   unsigned short usDelay ;      /* same delay for all leds */
} T_UCMC_IAC_ALL_LEDS ;

typedef struct
{
   unsigned char  ucChannel ;
   T_UCMC_IAC_ALL_LEDS sLed ;
} T_UCMC_IAC_ALL_LEDSCH ;

#define  UCMC_LED_GREEN_PACK       0x00000003
#define  UCMC_LED_GREEN_OFF        0x00000000
#define  UCMC_LED_GREEN_ON         0x00000001
#define  UCMC_LED_GREEN_BLINK      0x00000002
#define  UCMC_LED_GREEN_NO_CHANGE  0x00000003

#define  UCMC_LED_YELLOW_PACK      0x0000000C
#define  UCMC_LED_YELLOW_OFF       0x00000000
#define  UCMC_LED_YELLOW_ON        0x00000004
#define  UCMC_LED_YELLOW_BLINK     0x00000008
#define  UCMC_LED_YELLOW_NO_CHANGE 0x0000000C

#define  UCMC_LED_RED_PACK         0x00000030
#define  UCMC_LED_RED_OFF          0x00000000
#define  UCMC_LED_RED_ON           0x00000010
#define  UCMC_LED_RED_BLINK        0x00000020
#define  UCMC_LED_RED_NO_CHANGE    0x00000030

#define  UCMC_LED1_PACK           0x000000C0
#define  UCMC_LED1_OFF            0x00000000
#define  UCMC_LED1_ON             0x00000040
#define  UCMC_LED1_BLINK          0x00000080
#define  UCMC_LED1_NO_CHANGE      0x000000C0

#define  UCMC_LED2_PACK           0x00000300
#define  UCMC_LED2_OFF            0x00000000
#define  UCMC_LED2_ON             0x00000100
#define  UCMC_LED2_BLINK          0x00000200
#define  UCMC_LED2_NO_CHANGE      0x00000300

#define  UCMC_LED3_PACK           0x00000C00
#define  UCMC_LED3_OFF            0x00000000
#define  UCMC_LED3_ON             0x00000400
#define  UCMC_LED3_BLINK          0x00000800
#define  UCMC_LED3_NO_CHANGE      0x00000C00

#define  UCMC_LED4_PACK           0x00003000
#define  UCMC_LED4_OFF            0x00000000
#define  UCMC_LED4_ON             0x00001000
#define  UCMC_LED4_BLINK          0x00002000
#define  UCMC_LED4_NO_CHANGE      0x00003000

/***************************************/
/************** BUZZER*****************/
/***************************************/
#define  UCMC_BUZ_OFF        0x00
#define  UCMC_BUZ_NORMAL 0x01
#define  UCMC_BUZ_HIGH      0x02
#define  UCMC_BUZ_BASS      0x03

typedef struct
{
	unsigned char ucCmd ;      /* UCMC_BUZ_OFF,  UCMC_BUZ_NORMAL,  UCMC_BUZ_HIGH or UCMC_BUZ_BASS */
	unsigned short usDelay ;   /* second */
} T_UCMC_IAC_BUZ ;

typedef struct
{
   unsigned char  ucChannel ;
   T_UCMC_IAC_BUZ sBuz ;
} T_UCMC_IAC_BUZCH ;

/***************************************/
/************** MODEM *****************/
/***************************************/
#define UCMC_Taille_ADR_RACCORD  20
#define UCMC_Taille_ADR_APPEL    40
#define UCMC_Taille_COMPLX25	   40
typedef unsigned char UCMC_ADR_RACCORD [UCMC_Taille_ADR_RACCORD];
typedef unsigned char UCMC_ADR_APPEL   [UCMC_Taille_ADR_APPEL];
typedef unsigned char UCMC_ADR_COMPLX25 [UCMC_Taille_COMPLX25];


/* Depuis UCMC version 0113 */
typedef struct
{
   unsigned char         ucTypeProt;   /* equivalent STR_ETABL_CONNEX type_protocole;  CBCOM V5 / V42A */
   unsigned char         ucTypePad;    /* equivalent STR_ETABL_CONNEX type_PAD EBA / EMA */
	unsigned char         ucTypeCentre; /* Correspond à la raison d'appel Utiliser par exemple UCMHOST_HOST_CAB */ 

   unsigned char         ucLgComplX25; /* equivalent STR_ETABL_CONNEX unsigned char   lgr_data_compl;	longueur de la chaine */
   UCMC_ADR_COMPLX25     uctComplX25; 	/* equivalent STR_ETABL_CONNEX  STR_COMP_X25    data_compl_X25 buffer ipdu_identif_out */

	UCMC_ADR_RACCORD      uctRaccord;   /* equivalent STR_ETABL_CONNEX  adr_raccord; 	numero_PAD */
	unsigned char         ucLgRaccord;  /* equivalent STR_ETABL_CONNEX lgr_adr_raccord */

	unsigned char         ucLgAppel;    /* equivalent STR_ETABL_CONNEX lgr_adr_appel */
	UCMC_ADR_APPEL        uctAppel;     /* equivalent STR_ETABL_CONNEX adr_appel; numero_X25 */

   unsigned char         ucTimer;      /* equivalent STR_ETABL_CONNEX timer_TNR valeur de l'init timer 		*/

   unsigned char         ucRuf[ 40 ] ;
} T_UCMC_IAC_MODEM_CNX ;


#define UCMC_MODEM_READ_BUFFER_SIZE (UCMC_IAC_BUFFER_SIZE - sizeof( unsigned long ) - 2*sizeof( unsigned short ) )
typedef struct
{
   unsigned short        usTimeOut ;
   unsigned long         ulLength ;
   unsigned short        usRuf ;

   unsigned char         ucBuf[ UCMC_MODEM_READ_BUFFER_SIZE ] ;
} T_UCMC_IAC_MODEM_RW ;

typedef struct
{
	unsigned short usType_code;	/* Appli number */
   unsigned short usService;		/* UCMC */
	unsigned short usModule;		/* PAYEMENT, PRINTER, DISPLAY ... */		
   unsigned short usFct;			/* */
   
   unsigned int   uiSize;
   
	union
	{
      char ucBuffer[UCMC_IAC_BUFFER_SIZE ];
		T_UCMC_IAC_MODEM_RW sModRead;
	} Par;
	
} T_UCMC_IAC_SERVICE_MODEM_READ_WRITE ;

#define UCMC_EVENT_BUFFER_SIZE (UCMC_IAC_BUFFER_SIZE - 4*sizeof( unsigned short ) )

typedef struct
{
	unsigned short usType;
   unsigned short usRuf1;
	unsigned short usRuf2;
	unsigned short usRuf3;   

	union
	{
      char ucBuffer[ UCMC_EVENT_BUFFER_SIZE ];
      char ucKey;
	} Par;
	
} T_UCMC_IAC_EVENT ;

#define UCMC_HOSTDATA_BUFFER_SIZE (UCMC_IAC_BUFFER_SIZE - 4*sizeof( unsigned short ) )
/* usType of event */
#define UCMC_EVENT_TYPE_LLT_BT 0x0001
#define UCMC_EVENT_TYPE_KEY    0x0002
#define UCMC_EVENT_TYPE_USB    0x0004


typedef struct
{
	unsigned short usType;
   unsigned short usRuf1;
	unsigned short usRuf2;
	unsigned short usLg;   

	union
	{
      char ucBuffer[ UCMC_HOSTDATA_BUFFER_SIZE ];
	} Par;
	
} T_UCMC_IAC_HOSTDATA ;

/***************************************/
/*************** VENDING ***************/
/***************************************/


/***************************************/
/************** HOST CMD **************/
/***************************************/

#define UCMC_IAC_HOST2_BUFFER_SIZE 2032
typedef struct
{
	unsigned short       usHostCmd;

	unsigned char        ucCr;

	unsigned char        ucRuf;
	
	unsigned short       usHostWaitTimeout; /* seconde */

	unsigned short       usSize; 				/* of data in union */
	
	union
	{
		unsigned char ucBuf[ UCMC_IAC_HOST2_BUFFER_SIZE ] ;

      /* List of structs used by vending application                                  */
      /* the used struct is function of         usHostCmd                             */
      /* T_UCMHOST_DA_EPURSE_BALANCE         -> UCMHOSTLIB_CMD_EPURSE_BALANCE         */
      /* T_UCMHOST_DA_PARAM                  -> UCMHOSTLIB_CMD_PARAM_DA               */
      /* T_UCMHOST_DA_PARAM_MSG              -> UCMHOSTLIB_CMD_PARAM_DA_MSG           */
      /* T_UCMHOST_DA_CR_EPURSE_REVALUE      -> UCMHOSTLIB_CMD_ANS_EPURSE_REVALUE     */
      /* T_UCMHOST_DA_CR_REC_EPURSE_REVALUE  -> UCMHOSTLIB_CMD_ANS_REC_EPURSE_REVALUE */
      /* T_UCMHOST_DEVICE_CMD */
      /* END                                                                          */
	} u;
	
} T_UCMC_IAC_HOST2 ;

/* usHostCmd */
/* Use  0 for init all cmd */
/* #define UCMHOSTLIB_MSG_DEM_CONSO			   0x0015 */
/* #define UCMHOSTLIB_MSG_REP_CONSO			   0x0016 */

/* ucCr */
#define UCMC_IAC_HOST_CR_OK               0
#define UCMC_IAC_HOST_CR_TIMEOUT         1
#define UCMC_IAC_HOST_CR_CMD_UNKNOWN   2
#define UCMC_IAC_HOST_CR_BUSY             3

/***************************************/
/************** SYSTEMFIOCTL ***********/
/***************************************/
typedef struct
{
	int iCmd ;
	int iLg ;
	int iRet ;

   union
   {
      unsigned int uiRes;
      unsigned char ucBuf[ 200 ] ;
   } u;

}T_UCM_IAC_SYSTEMFIOCTL;

/***************************************/
/************** SYSTEMFIOCTL ***********/
/***************************************/
typedef struct
{
   int     iSecureType;
   char	 cBoosterType;
   char   ctszBoosterPeripheral[ 20 ];
   char   cbGestResid;
}T_UCM_DEVICE_CMD_CONF_DLL_SECU;

typedef struct
{
	int iNb ;

   T_UCM_DEVICE_CMD_CONF_DLL_SECU tConf[10] ;

}T_UCM_IAC_DEVICE_CMD_DLL_SECU;

typedef struct
{
	int iStandByType ;  /* 0=none 1=light 2=deep */
	int iDelay ;         /* seconde */
   int iWakeup;        /* seconde only for light */
   int iRuf;             /*  */
} T_UCM_IAC_DEVICE_CMD_POWER_MNG;

#define UCMC_IAC_DEVICE_CMD_BUFFER_SIZE (UCMC_IAC_BUFFER_SIZE - 48)
typedef struct
{
	int iCmd ;
	int iLg ;
	int iRet ;

   union
   {
      unsigned int uiRes;
      T_UCM_IAC_DEVICE_CMD_DLL_SECU tSecu;
      T_UCM_IAC_DEVICE_CMD_POWER_MNG tPowerMng;
      unsigned char ucBuf[ UCMC_IAC_DEVICE_CMD_BUFFER_SIZE ] ;
   } u;

}T_UCM_IAC_DEVICE_CMD;

#define UCMDEVICE_CMD_SETDLLSECU    0xF001
#define UCMDEVICE_CMD_GET_POWER_MNG 0xF002
#define UCMDEVICE_CMD_SET_POWER_MNG 0xF003
#define UCMDEVICE_CMD_ICC_ITP 0xF005 
#define UCMDEVICE_CMD_ICL_ITP 0xF004

/***************************************/
/*************    ALL     **************/
/***************************************/
typedef struct
{
    unsigned short usType_code;	/* Appli number */
    unsigned short usService;		/* UCMC */
    unsigned short usModule;		/* PAYEMENT, PRINTER, DISPLAY ... */		
    unsigned short usFct;			/* */

    unsigned int   uiSize;			/* */

    union
    {
        unsigned char          ucBuffer [ UCMC_IAC_BUFFER_SIZE ] ;

        unsigned short         usData;

        T_UCM_IAC_DEVICE_CMD sDeviceCmd;

        T_UCM_DEVICE           sDevice;

        T_UCMC_CHANNEL_DEVICE  sChannelDevice;

        /* DISPLAY */
        T_UCMC_IAC_DISPLAY    sDisplay;
        T_UCMC_IAC_DISPLAY2   sDisplay2;

        /* PRINT */
        T_UCMC_IAC_PRINT      sPrint;
        T_UCMC_IAC_PRINTPATTERN sPrintPattern;

        /* ICC */
        T_UCMC_IAC_ICC        sIcc;
        T_UCMC_IAC_ICC_EMV    sIccEmv;
        T_UCMC_IAC_ICC_SYNC   sIccSync;
        T_UCMC_IAC_ICC_PCODE  sIccPCode;
        T_UCMC_IAC_ICC_TRACK  sIccTrack;
        T_UCMC_IAC_ICC_CMD    sIccCmd;

        /* MODEM */
        T_UCMC_IAC_MODEM_CNX  sModCnx;
        T_UCMC_IAC_MODEM_RW   sModRead;

        /* DEBIT_EMV               */
        StructDebitEmv       sDebitEmv;

        /* DEBIT_NON_EMV           */
        StructDebitNonEmv    sDebitNonEmv;

        /* PINPAD */
        T_UCMC_IAC_PPAD       sPpad;

        /* LED */
        T_UCMC_IAC_LED        sLed;

        /* LED with channel */
        T_UCMC_IAC_LEDCH      sLedCh;

        /* BUZZER */
        T_UCMC_IAC_BUZ        sBuz;

        /* BUZZER with channel */
        T_UCMC_IAC_BUZCH      sBuzCh;

        /* HOST CMD */
        T_UCMC_IAC_HOST2       sHost2;

        T_UCM_IAC_SYSTEMFIOCTL sSystemFioctl;

        T_UCMHOST_DEBIT      sDebit ;

        object_info_t       sInfos_p ;

        T_UCMHOST_APP_LIST_RECORD_LOC sFctAppListRecordLoc;

        /* EVENT */
        T_UCMC_IAC_EVENT       sEvent;

        /* DATA HOST->APP */
        T_UCMC_IAC_HOSTDATA     sHostData;
    } Par;
	
} T_UCMC_IAC_SERVICE ;


/*******************************************************/
/* PAYMENT FUNCTIONS                                  */
/*******************************************************/
extern int iLIBUCM_Pay_Init( int iSize_p, unsigned char * ) ;
extern int iLIBUCM_Pay_Ready_For_Debit( int iSize_p, void * ) ;
extern int iLIBUCM_Pay_Result_Debit( int iSize_p, void * ) ;
extern int iLIBUCM_Pay_End( int iSize_p, void * ) ;
extern int iLIBUCM_Pay_Host_Cmd( int iSize_p, void *ps_p, void *psResult_p ) ;
extern int iLIBUCM_Pay_Host_Get_Last_Cmd( int iSize_p, void *ps_p, void *psResult_p ) ;
extern int iLIBUCM_Host_Send( int iSize_p, void *pData, void *psResult_p ) ;
extern int iLIBUCM_Host_Read( int iSize_p, void *pData, int *piSizeData ) ;
extern int iLIBUCM_Host_Init( T_UCM_DEVICE *psDevice_p ) ;
extern int iLIBUCM_Pay_Host_Get_Last_Cmd_Data( unsigned char ucTypeHOST_p /* UCM_DEVICE_HOST */, T_UCMC_IAC_HOST2 *psHost_p ) ;

#define UCMCPAY_SOLV                    0x23
#define UCMCPAY_RECORD                  0x25
#define UCMCPAY_SOLV_LOC                0x26
#define UCMCPAY_RECORD_LOC              0x27
#define UCMCPAY_CARD_INFO               0x29

#define UCMCPAY_ASK_EPURSE_BALANCE      0x30   /* modif DA */
#define UCMCPAY_REVALUE_EPURSE          0x31   /* modif DA */
#define UCMCPAY_RECORD_REVALUE_EPURSE   0x32   /* modif DA */
#define UCMCPAY_HOST_NOT_AVAILABLE      0x33   /* modif DA */
#define UCMCPAY_HOST_REMOVE_CARD        0x34   /* modif DA */
#define UCMCPAY_ASK_DEFAULT_BALANCE     0x35   /* v0123 modif DA contacless */
#define UCMCPAY_ASK_STOP                0x36   /* v0123 modif DA contacless */

/*******************************************************/
/* DISPLAY FUNCTIONS                                  */
/*******************************************************/

/*******  DISPLAY Option *******/
#define UCMDISPLAY_NO_OPTION     		0x0000
#define UCMDISPLAY_OPEN_ALWAYS			0x0001
#define UCMDISPLAY_CLOSE_AT_END			0x0002
#define UCMDISPLAY_WAIT_END				0x0004
#define UCMDISPLAY_CLEAR					0x0008
#define UCMDISPLAY_APPEND					0x0010
#define UCMDISPLAY_OPEN_IF_NOT			0x0020
#define UCMDISPLAY_CLOSE_IF_OPEN 		0x0040
#define UCMDISPLAY_NEW_LINE				0x0080
#define UCMDISPLAY_NO_WAITING_TO			0x0100
#define UCMDISPLAY_CENTER			      0x0200
#define UCMDISPLAY_CENTER_LINEONLY     0x0201

typedef enum
{
	UCMC_DISPLAY0 = 0,
	UCMC_DISPLAY1,
	UCMC_DISPLAYMAX
} TE_UCM_DISPLAY_CANAL;

#define UCMC_DISPLAY       0xF0	/* DEFAULT DISPLAY */
#define UCMC_DISPLAY_ICC   0xF1	/* ICC DISPLAY */
#define UCMC_DISPLAY_ICL   0xF2	/* ICL DISPLAY */
#define UCMC_DISPLAY_PPAD  0xF3	/* PINPAD DISPLAY */
#define UCMC_DISPLAY_HOST  0xF4  /* HOST DISPLAY */

/*******  DISPLAY Interface *******/
extern int iLIBUCM_Display_Init( unsigned char ucChannel_p, T_UCM_DEVICE *psDevice_p ) ;
extern int iLIBUCM_Display_Is_Open(unsigned char ucChannel_p) ;
extern int iLIBUCM_Display_Is_Connect(unsigned char ucChannel_p) ;
extern int iLIBUCM_Display_Close( unsigned char ucChannel_p ) ;
extern int iLIBUCM_Display_Open( unsigned char ucChannel_p, char *cOption_p ) ;
extern int iLIBUCM_Display_Message( unsigned char ucChannel_p, char *cMessage_p , unsigned short usTimeout_p ) ;
extern int iLIBUCM_Display_Option( unsigned char ucChannel_p, char *cMessage_p , unsigned short usOption, unsigned short usTimeout_p ) ;
extern int iLIBUCM_Display_Clear( unsigned char ucChannel_p ) ;
extern int iLIBUCM_Display_NewLine( unsigned char ucChannel_p ) ;
extern int iLIBUCM_Display_Cmd( unsigned char ucChannel_p, T_UCMC_IAC_SERVICE * ) ;
extern int iLIBUCM_Display_Exist( unsigned char ucChannel_p ) ;
extern int iLIBUCM_Display_No_Wait( unsigned char ucChannel_p, char *cMessage_p , unsigned short usTimeout_p ) ;
extern int iLIBUCM_Display_No_Wait2Msg( unsigned char ucChannel_p, unsigned short usContinus_p, 
									 char *cMessage1_p, unsigned short usTimeout1_p,
									 char *cMessage2_p, unsigned short usTimeout2_p) ;

extern int iLIBUCM_Display_New_Idle_Msg( unsigned char ucChannel_p, char *cMessage_p ) ;
extern int iLIBUCM_Display_Get_Msg( unsigned char ucChannel_p, unsigned short usMsgNumber_p, char *cMessage_p );
extern int iLIBUCM_Display_Graphic_Start( unsigned char ucChannel_p );
extern int iLIBUCM_Display_Graphic_Stop( unsigned char ucChannel_p );
extern int iLIBUCM_Display_ClearLine( unsigned char ucChannel_p ) ;
extern int iLIBUCM_Display_Backlight_Color( unsigned char ucChannel_p, T_UCMC_DISPLAY_BACKLIGHT_COLOR *pBck_color_p );
extern int iLIBUCM_Display_Idle_Event( unsigned char ucChannel_p, unsigned char ucOnOff_p );
extern int iLIBUCM_Display_Backlight_Color_Exist( unsigned char ucChannel_p );

/*******************************************************/
/* PRINTER FUNCTIONS                                  */
/*******************************************************/

/*******  PRINT Option *******/
#define UCMPRINT_NO_OPTION     0x0000
#define UCMPRINT_OPEN_ALWAYS   0x0001
#define UCMPRINT_CLOSE_AT_END  0x0002
#define UCMPRINT_WAIT_END      0x0004
#define UCMPRINT_NEWLINE        0x0008
#define UCMPRINT_APPEND         0x0010
#define UCMPRINT_OPEN_IF_NOT    0x0020
#define UCMPRINT_CLOSE_IF_OPEN  0x0040
#define UCMPRINT_CUTPAPER       0x0080
#define UCMPRINT_NO_END         0x0100

/*******  PRINT Interface *******/
extern int iLIBUCM_Print_Init( unsigned char ucChannel_p, T_UCM_DEVICE *psDevice_p ) ;
extern int iLIBUCM_Print_Is_Open( unsigned char ucChannel_p ) ;
extern int iLIBUCM_Print_Open( unsigned char ucChannel_p, char *cOption_p ) ;
extern int iLIBUCM_Print_Close( unsigned char ucChannel_p ) ;
extern int iLIBUCM_Print_Message( unsigned char ucChannel_p, char *cMessage_p ) ;
extern int iLIBUCM_Print_Option( unsigned char ucChannel_p, char *cMessage_p , unsigned short usOption_p) ;
extern int iLIBUCM_Print_NewLine( unsigned char ucChannel_p, unsigned char ucNbLine ) ;
extern int iLIBUCM_Print_CutPaper( unsigned char ucChannel_p ) ;
extern int iLIBUCM_Print_Cmd( unsigned char ucChannel_p, T_UCMC_IAC_SERVICE * ) ;
extern int iLIBUCM_Print_Exist( unsigned char ucChannel_p ) ;
extern int iLIBUCM_Print_Status( unsigned char ucChannel_p, unsigned char *pucStatus_p ) ;
extern int iLIBUCM_Print_Ttestall( unsigned char ucChannel_p, unsigned short usDelay_p ) ;
extern int iLIBUCM_Print_Defprinterpattern (unsigned char ucChannel_p, char cKey_p, char *pcPattern_p );

typedef enum
{
	UCMC_PRINT0 = 0,
	UCMC_PRINT1,
	UCMC_PRINTMAX
} TE_UCM_PRINT_CANAL;

#define UCMC_PRINT  0xF0	/* DEFAULT PRINTER */

/*******************************************************/
/* MODEM FUNCTIONS                                  */
/*******************************************************/

/*******  MODEM Option  *******/
#define UCMMODEM_NO_OPTION      0x0000
#define UCMMODEM_OPEN_ALWAYS    0x0001
#define UCMMODEM_CLOSE_AT_END   0x0002
#define UCMMODEM_WAIT_END       0x0004
#define UCMMODEM_RESET			  0x0008
#define UCMMODEM_OPEN_IF_NOT    0x0020
#define UCMMODEM_CLOSE_IF_OPEN  0x0040

/*******  MODEM Interface  *******/
extern int iLIBUCM_Modem_Init( T_UCM_DEVICE *psDevice_p ) ;
extern int iLIBUCM_Modem_Config( T_UCM_DEVICE *psDevice_p ) ;
extern int iLIBUCM_Modem_Cnx( T_UCMC_IAC_MODEM_CNX *) ;
extern int iLIBUCM_Modem_Dcnx( unsigned char ucOption_p ) ;
extern int iLIBUCM_Modem_Write( unsigned char *, unsigned long ) ;
extern int iLIBUCM_Modem_Read( unsigned char *, unsigned long *pulNb_p , unsigned short usTimeOut ) ;
extern int iLIBUCM_Modem_Exist( void ) ;

#define UCMMODEM_NO 0
#define UCMMODEM_INTERNAL 1
#define UCMMODEM_HOST 2       /* 2 au lieu de 3 Comme parametrage */
#define UCMMODEM_KO	 	0xFF	/* Exist but ko */

/*******************************************************/
/* ICCS SAMS FUNCTIONS                               */
/*******************************************************/

/*******  ICC Option *******/
#define UCMICC_NO_OPTION      0x0000
#define UCMICC_OPEN_ALWAYS    0x0001
#define UCMICC_CLOSE_AT_END   0x0002
#define UCMICC_WAIT_END       0x0004
#define UCMICC_OPEN_IF_NOT    0x0020
#define UCMICC_CLOSE_IF_OPEN  0x0040

/*******  ICC Poweron option for usPowerOnType_p *******/
#define UCMCICC_POWER_ON            0x0027
#define UCMCICC_POWER_DOWN 	      0x0028
#define UCMCICC_EMV_POWER_ON        0x0030
#define UCMCICC_POWER_ON_SYNC       0x0031
#define UCMCICC_POWER_DOWN_SYNC     0x0032
#define UCMCICC_POWER_ATR                0x0040

#define UCMCMAX_ATR 64
typedef struct {
	unsigned char length;
   unsigned char atr[UCMCMAX_ATR];
} UCMC_ATR;

typedef enum
{
	UCMC_ICC0 = 0,
	UCMC_ICC1,
   UCMC_SAM0,		/* Internal UCMC */
   UCMC_SAM1,	
	UCMC_SAM2,
	UCMC_SAM3,   /* External UCMC */
	UCMC_SAM4,
	UCMC_ICCSAMMAX
} TE_UCM_ICC_CANAL;

#define UCMC_ICC    0xF0		/* Default ICC */
#define UCMC_SAM    0x0F		/* Deault SAM */
#define UCMC_ISO1   0xEC		/* Default SWIPE ISO1 if ICC mixte */
#define UCMC_ISO3   0xED		/* Default SWIPE ISO3 if ICC mixte */
#define UCMC_ISO2   0xEE		/* Default SWIPE ISO2 if ICC mixte */
#define UCMC_ICL    0xE0		/* Default Contactless */

#define UCMC_STATUS_CARD_OUTSIDE 0
#define UCMC_STATUS_CARD_INSIDE  1


/*******  ICC Interface *******/
extern int iLIBUCM_Icc_Init( unsigned char ucChannel, T_UCM_DEVICE *psDevice_p ) ;
extern int iLIBUCM_Icc_Ttestall( unsigned char ucChannel , unsigned short usDelay_p );
extern int iLIBUCM_Icc_Is_Open( unsigned char ucChannel );
extern int iLIBUCM_Icc_Is_Connect( unsigned char ucChannel );
extern int iLIBUCM_Icc_Close( unsigned char ucChannel ) ;
extern int iLIBUCM_Icc_Exist( unsigned char ucChannel ) ;
extern int iLIBUCM_Icc_Open( unsigned char ucChannel, char *cOption_p ) ;
extern int iLIBUCM_Icc_PowerOn( unsigned char ucChannel, unsigned short usPowerOnType_p, HISTORIC *pHisto ) ;
extern int iLIBUCM_Icc_PowerDown( unsigned char ucChannel, unsigned short usPowerOnType_p ) ;
extern int iLIBUCM_Icc_Input( unsigned char ucChannel, unsigned short usOption_p, COMMAND_CAM *pCmd_p ) ;
extern int iLIBUCM_Icc_Output( unsigned char ucChannel, unsigned short usOption_p, COMMAND_CAM *pCmd_p ) ;
extern int iLIBUCM_Icc_Status( unsigned char ucChannel, unsigned char *puc_Card_p ) ;
extern int iLIBUCM_Icc_Cmd( /*unsigned char ucChannel_p,*/ T_UCMC_IAC_ICC_CMD *pdata_p ) ;
extern int iLIBUCM_Icc_EmvApdu( unsigned char ucChannel_p, unsigned short usOption_p, T_APDU *pC_apdu_p, T_APDU *pR_apdu_p ) ;
extern int iLIBUCM_Icc_F_Sync_Fct ( unsigned char ucChannel_p, unsigned short usOption_p, unsigned char ucFunction_p, unsigned char ucParam_p ) ;
extern int iLIBUCM_Icc_PCode( unsigned char ucChannel_p, unsigned short usOption_p, 
                              T_APDU *pC_apdu_p, T_APDU *pR_apdu_p, T_UCMC_ICC_CODE *pCode ) ;
extern int iLIBUCM_Icc_Read_Swipe( unsigned char ucChannel_p, unsigned short usOption_p, 
		                        T_UCMC_ICC_TRACK *pCode ) ;
extern int iLIBUCM_Icc_Read_SwipeMulti( unsigned char ucChannel_p, unsigned short usOption_p, 
		T_UCMC_ICC_TRACKMULTI *psTrack_p );

extern int iLIBUCM_Icc_Backlight_Color( unsigned char ucChannel_p, T_UCMC_DISPLAY_BACKLIGHT_COLOR *ptBlkColor_p );
extern int iLIBUCM_Icc_Backlight_Color_Exist( unsigned char ucChannel_p );

/*******************************************************/
/* PINPAD FUNCTIONS                                   */
/*******************************************************/

/*******  PINPAD Option *******/
#define UCMPPAD_NO_OPTION  0x0000
#define UCMPPAD_OPEN_ALWAYS   0x0001
#define UCMPPAD_CLOSE_AT_END  0x0002
#define UCMPPAD_WAIT_END      0x0004
#define UCMPPAD_OPEN_IF_NOT    0x0020
#define UCMPPAD_CLOSE_IF_OPEN  0x0040

typedef enum
{
	UCMC_PINPAD0 = 0,
	UCMC_PINPAD1,
	UCMC_PINPADMAX
} TE_UCM_PPAD_CANAL;

#define UCMC_PPAD           0xF0	/* DEFAULT PPAD */
#define UCMC_PPAD_INTERNAL  0xF1	/* Internal push button */

/*******  PINPAD Interface *******/
extern int iLIBUCM_Pinpad_Init( unsigned char ucChannel, T_UCM_DEVICE *psDevice_p ) ;
extern int iLIBUCM_Pinpad_Ttestall( unsigned char ucChannel , unsigned short usDelay_p );
extern int iLIBUCM_Pinpad_Is_Open( unsigned char ucChannel );
extern int iLIBUCM_Pinpad_Close( unsigned char ucChannel ) ;
extern int iLIBUCM_Pinpad_Exist( unsigned char ucChannel ) ;
extern int iLIBUCM_Pinpad_Open( unsigned char ucChannel, char *cOption_p ) ;
extern int iLIBUCM_Pinpad_Input( unsigned char ucChannel, unsigned short usOption_p, T_UCM_ENTRY_PPAD *pCmd_p ) ;
extern int iLIBUCM_Pinpad_Option( unsigned char ucChannel, unsigned short usOption_p) ;
extern int iLIBUCM_Pinpad_Status( unsigned char ucChannel, unsigned char *puc_Card_p ) ;
extern int iLIBUCM_Pinpad_Cmd( unsigned char ucChannel_p, T_UCM_IAC_PINPAD_CMD *sCmd_p  ) ;
extern int iLIBUCM_Pinpad_GetChar( unsigned char ucChannel_p );
extern int iLIBUCM_Pinpad_Is_Connect( unsigned char ucChannel_p ) ;

/*******************************************************/
/* LED FUNCTIONS                                   */
/*******************************************************/
typedef enum
{
	UCMC_LED0 = 0,
	UCMC_LED1,
	UCMC_LEDMAX
} TE_UCM_LED_CHANNEL;

#define UCMC_LED      0xF0 /* DEFAULT LED */
#define UCMC_LED_ICC  0xE0	/* LED CONTACT READER */
#define UCMC_LED_ICL  0xD0	/* LED CONTACTLESS READER */

/*******  LED Interface *******/
extern int iLIBUCM_LED_Init( T_UCM_DEVICE *psDevice_p ) ;
extern int iLIBUCM_LED_Exist( void ) ;
extern int iLIBUCM_LED_Status( unsigned char *pucLed_p ) ;
extern int iLIBUCM_LED_Cmd( T_UCMC_IAC_LED *pdata_p ) ;

extern int iLIBUCM_LED_InitCh( unsigned char ucChannel_p, T_UCM_DEVICE *psDevice_p ) ;
extern int iLIBUCM_LED_ExistCh( unsigned char ucChannel_p ) ;
extern int iLIBUCM_LED_StatusCh( unsigned char ucChannel_p, unsigned char *pucLed_p ) ;
extern int iLIBUCM_LED_CmdCh(  unsigned char ucChannel_p, T_UCMC_IAC_LED *pdata_p ) ;

/*******************************************************/
/* BUZZER FUNCTIONS                                   */
/*******************************************************/
typedef enum
{
	UCMC_BUZZER0 = 0,
	UCMC_BUZZER1,
	UCMC_BUZZERMAX
} TE_UCM_BUZZER_CHANNEL;

#define UCMC_BUZZER      0xF0	   /* DEFAULT BUZZER */
#define UCMC_BUZZER_ICC  0xE0	/* BUZZER CONTACT READER */
#define UCMC_BUZZER_ICL  0xD0	/* BUZZER CONTACTLESS READER */


/*******  BUZZER Interface *******/
extern int iLIBUCM_BUZZER_Init( T_UCM_DEVICE *psDevice_p ) ;
extern int iLIBUCM_BUZZER_Exist( void ) ;
extern int iLIBUCM_BUZZER_Status( unsigned char *pucLed_p ) ;
extern int iLIBUCM_BUZZER_Cmd( T_UCMC_IAC_BUZ *pdata_p ) ;

extern int iLIBUCM_BUZZER_InitCh( unsigned char ucChannel_p, T_UCM_DEVICE *psDevice_p ) ;
extern int iLIBUCM_BUZZER_ExistCh( unsigned char ucChanel_p ) ;
extern int iLIBUCM_BUZZER_StatusCh(  unsigned char ucChannel_p, unsigned char *pucLed_p ) ;
extern int iLIBUCM_BUZZER_CmdCh( unsigned char ucChannel_p, T_UCMC_IAC_BUZ *pdata_p ) ;

/*******************************************************/
/* MULTIPLE DEVICE TTESTALL                            */
/*******************************************************/
typedef enum
{
	UCMMULTI_TTESTALL_PAY     = 0x0001,
	UCMMULTI_TTESTALL_DISPLAY = 0x0002,
	UCMMULTI_TTESTALL_PRINT   = 0x0004,
	UCMMULTI_TTESTALL_MODEM  = 0x0008,
	UCMMULTI_TTESTALL_ICC     = 0x0010,
	UCMMULTI_TTESTALL_SAM    = 0x0020,
	UCMMULTI_TTESTALL_PINPAD = 0x0040,
	UCMMULTI_TTESTALL_HOST   = 0x0080,
	UCMMULTI_TTESTALL_HOST2  = 0x0100,
	UCMMULTI_TTESTALL_ISO2   = 0x0200,
	UCMMULTI_TTESTALL_ISO1   = 0x0400,
	UCMMULTI_TTESTALL_ISO3   = 0x0800
} TE_UCM_MULTI_TTESTALL;

#define UCMTTESTALL_ALL_EVENT     0x03FF

#define UCMTTESTALL_CR_OK_EVENT     FCT_OK
#define UCMTTESTALL_CR_NO_DEVICE    ( 1 )		/* Device not exist */
#define UCMTTESTALL_CR_NO_DECLARED  ( 2 )	  /* Device not declared */
#define UCMTTESTALL_CR_NO_EVENT     ( 3 )		/* No Event possible */
#define UCMTTESTALL_CR_TIME_OUT     ( 4 )		/* Time out */
#define UCMTTESTALL_CR_ABORD_MSG     ( 5 )		/* Abord MSG */
#define UCMTTESTALL_CR_ABORD_KEY     ( 6 )		/* Abord key */

/*******************************************************/
/* DEVICE STATUS                                      */
/*******************************************************/
typedef struct
{
	unsigned char ucUCM;       /* 0=Ok 1=Occuped 3=Maintenance .... */
	unsigned char ucICC;			/* 0=ok 1=no icc 2=icc ko */
	unsigned char ucICCMode;	/* 0 = smart only, 2=sarmt + track */
	unsigned char ucSAM;			/* OK = 0 */
	unsigned char ucNetwork;	/* OK = 0*/
	unsigned char ucPrinter;	/* OK = 0 HS or no paper */
	unsigned char ucPinpad;	   /* OK = 0 */
	unsigned char ucDisplay;	/* OK = 0 */
	unsigned char ucDevice;	   /* Other device 0=Ok else pb */
} T_LIBUCM_DEVICE_STATUS;

extern int iLIBUCM_Device_Ttestall( unsigned short *pusWhat, unsigned short usDelay_p ) ;
extern int iLIBUCM_Device_Config( unsigned char ucDevice, T_UCM_DEVICE *psDevice_p ) ;
extern int iLIBUCM_Device_Config_OPE( unsigned char ucDevice, T_UCM_DEVICE *psDevice_p ) ;
extern int iLIBUCM_Device_ConfigAll( T_UCM_PARAM *pParam ) ;
extern int iLIBUCM_Device_ConfigAll_OPE( T_UCM_PARAM *pParam ) ;
extern int iLIBUCM_Device_Ucm_Status( T_LIBUCM_DEVICE_STATUS *pDeviceStatus_p ) ;
extern int iLIBUCM_SystemFioctl( int iFioCmd_p , void *vpData_p, int iLgData_p ) ;
/* ucDevice = TE_UCM_DEVICE */
/* ucDevice = UCM_DEVICE_UCMC for info on UCMC */
/* ucDevice = UCM_DEVICE_UCMSTART for info on UCMSTART */
extern int iLIBUCM_Device_GetInfo( unsigned char ucDevice, object_info_t *pinfos_p ) ;
extern int iLIBUCM_Device_GetStatus( unsigned char ucDevice, T_UCM_DEVICE_STATUS *psDevice_p );
extern int iLIBUCM_Device_Event_Service_Set( T_UCMC_IAC_EVENT *psEvent_p ) ;
extern int iLIBUCM_Device_Cmd( unsigned short usCmd_p, void *pData_p, int *piLgData_p, int *piRet_p ) ;

/*******************************************************/
/* Service from application called by UCM                  */
/*******************************************************/
#define SERVICE_APPLI_UCMC 0x1202

#define UCMAPPLIMODULE_FCTAPP   0x0001
#define UCMAPPLIMODULE_PROTOCOL 0x0002

/*******************************************************/
/* FILE                                      */
/*******************************************************/
extern int iLIBUCM_File_Add_Record( char *pcFileName_p, int iDataSize_p, char *pcData_p );
extern int iLIBUCM_File_Edit( unsigned char ucWhere_p, unsigned char ucOption_p,
                     char *pcFileName_p, int *piDataSize_p, char *pcData_p );
extern int iLIBUCM_File_Delete( char *pcFileName_p );
extern int iLIBUCM_File_Get_Size( char *pcFileName_p );
/* See ucmhostdll.h to see each app function */
#endif
