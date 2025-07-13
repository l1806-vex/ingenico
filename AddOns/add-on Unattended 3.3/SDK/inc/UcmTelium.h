#ifndef _INC_UCMTELIUM		// For Multiple Include ...
#define _INC_UCMTELIUM

/******************************************************/
/*               Constant declarations                */
/******************************************************/
#define UCM_FILE_PARAM       "UCM.PAR"
#define UCM_FILE_ERR         "UCM_ERR.DIA"
#define UCM_FILE_ICC         "UCM_ICC.DIA"
#define UCM_FILE_PARAMS      "UCM.PAS"

////////////////////////////////////////////////////////////
// Exit Code 
////////////////////////////////////////////////////////////
#define UCM_TELIUM_ERROR		1	// No error / normal 

/************* UCM ERROR CONSTANT DECLARATIONS ********/
#define UCM_ERR_DISK_EXIST      (-1)	// Disk Not existe
#define UCM_ERR_FILE_EXIST      (-2)	// File Not existe
#define UCM_ERR_DISK_CREATION   (-3)	// Disk Not existe
#define UCM_ERR_FILE_CREATION   (-4)	// File Not existe
#define UCM_ERR_DISK_FORMAT     (-5)	// Pb Disk foramt
#define UCM_ERR_DISK_NAME       (-6)	// Disk Name too long
#define UCM_ERR_FILE_NAME       (-7)	// File Name too long
#define UCM_ERR_NOT_INITIALISED (-8)	// Service not initialized
#define UCM_ERR_FILE_OPEN       (-9)	// File open
#define UCM_ERR_FILE_COPY       (-10)	// File Copy
#define UCM_ERR_FILE_WRITE      (-11)	// File write
#define UCM_ERR_FILE_DELETE     (-12)	// File delete
#define UCM_ERR_OPEN_DIR        (-13)	// FS_opendir cmd ko
#define UCM_ERR_FILE_READ      (-14)	// File write
#define UCM_ERR_POINTER_NULL   (-15)	// Pointer null
#define UCM_ERR_SIZE_BUFFER    (-16)	// 
#define UCM_ERR_FILE_FULL      (-17)	// 
#define UCM_ERR_FILE_MALLOC    (-18)	// 
#define UCM_ERR_FILE_START     (-19)	// 
#define UCM_ERR_FILE_END       (-20)	// 

#define UCMERR_WARNING	         0
#define UCMERR_ERROR	            1
#define UCMERR_INFO	            2
#define UCMERR_FATAL_ERROR		   0xFE
#define UCMERR_FATAL_ERROR_RESET	0xFF

/*#define UCM_DEVICE_NOT_USE  0x00
#define UCM_DEVICE_IS_USED  0x01
#define UCM_DEVICE_IS_HOST  0x03
See TE_UCM_PARAM_TYPED and TE_UCM_PARAM_TYPEP
*/
#define UCM_COPY_DISPLAY  0x01
#define UCM_COPY_PRINTER  0x02
#define UCM_COPY_COM0     0x04
#define UCM_COPY_BUF      0x08
#define UCM_COPY_HOST     0x10
#define UCM_COPY_USB      0x20
#define UCM_COPY_COM4     0x40
#define UCM_COPY_MMC      0x80


/********** END UCM ERROR CONSTANT DECLARATIONS ********/


/* List of functions number */
#define UCM_ENTRY_FCT      0x1201
#define UCM_ERR_FCT        0x1202
#define UCM_PARAM_FCT      0x1203
#define UCM_DISPLAY_FCT    0x1204
#define UCM_PRINT_FCT      0x1205
#define UCM_FILE_FCT    	0x1206
#define UCM_HOST_FCT		   0x1207
#define UCM_PAY_FCT			0x1208
#define UCM_DLLSTART_FCT	0x1209
#define UCM_DLLHOST_FCT		0x120A
#define UCM_MODEM_FCT		0x120B
#define UCM_ICC_FCT			0x120C
#define UCM_PINPAD_FCT  	0x120D
#define UCM_BUZZER_FCT  	0x120E
#define UCM_LED_FCT  	   0x120F
#define UCM_DEVICE_FCT     0x1210
#define UCM_HOST2_FCT      0x1211
#define UCM_DLLHOST2_FCT   0x1212
#define UCM_MON_FCT        0x1213

/* List of exit 0x9470 to 0x9663 */
#define UCMEXIT_NEWPARAM   0x9470
#define UCMEXIT_PARAMFTC   0x9471
#define UCMEXIT_HOST_RESTART 0x9472
#define UCMEXIT_NEWPARAM_DRIVER 0x9473
#define UCMEXIT_DETECT_CADTOOL 0x9474
#define UCMEXIT_LOSS_CADTOOL 0x9475
#define UCMEXIT_DEVICE_RECONNECTION 0x9476
#define UCMEXIT_UCMCENTRY   0x9480
#define UCMEXIT_ERR_FTC     0x9490
#define UCMEXIT_DISPLAYFCT  0x94A0
#define UCMEXIT_PRINT_FCT   0x94B0
#define UCMEXIT_FILE_FCT    0x94C0
#define UCMEXIT_HOST_FCT	   0x94D0
#define UCMEXIT_PAY_FCT			0x94E0
#define UCMEXIT_DLLSTART_FCT	0x94F0
#define UCMEXIT_DLLHOST_FCT	 0x9500
#define UCMEXIT_DLLHOST_INIT	 0x9501
#define UCMEXIT_MODEM_FCT		 0x9510
#define UCMEXIT_ICC_FCT		    0x9520
#define UCMEXIT_NO_TIME_FCT    0x9521
#define UCMEXIT_DLLHOST2_FCT	 0x9550
#define UCMEXIT_DLLHOST2_INIT	 0x95F1

#define UCMEXIT_PINPAD_FCT		 0x9610

///////////////////////////////////////////////////////
// VENDING APPLICATIONS
///////////////////////////////////////////////////////
#define VENDING_APPLICATION_NAME    "APP_VENDING"
/******************************************************/
/*               End Constant declarations            */
/******************************************************/



/******************************************************/ 
/*          ENF D OF STRUCTURES DECLARATIONS          */
/******************************************************/
typedef enum
{
	UCM_DEVICE_FUNC = 0,
	UCM_DEVICE_FUNC_HOST,
	UCM_DEVICE_FUNC_BUZLEDIDL,
	UCM_DEVICE_FUNC_READER,
	UCM_DEVICE_FUNC_SAM,
	UCM_DEVICE_FUNC_DISPLAY,   /* 5 */
	UCM_DEVICE_FUNC_PINPAD,
	UCM_DEVICE_FUNC_PRINTER,
	UCM_DEVICE_FUNC_MODEM,
	UCM_DEVICE_FUNC_LED,
 	UCM_DEVICE_FUNC_BUZZER,   /* 10 */
	UCM_DEVICE_FUNC_MAX
} TE_UCM_FUNC_DEVICE;

typedef enum
{
	UCM_DEVICE_HOST = 0,
	UCM_DEVICE_HOST2,
	UCM_DEVICE_BUZLEDIDL, /* old  UCM_DEVICE_CASHFLOW*/
	UCM_DEVICE_ICC0,
	UCM_DEVICE_ICC1,
	UCM_DEVICE_SAM0,     /* 5 */
	UCM_DEVICE_SAM1,
	UCM_DEVICE_SAM2,
	UCM_DEVICE_DISPLAY0,
	UCM_DEVICE_DISPLAY1,
	UCM_DEVICE_PINPAD0,   /* 10 */
	UCM_DEVICE_PINPAD1,
	UCM_DEVICE_PRINTER0,
	UCM_DEVICE_PRINTER1,
	UCM_DEVICE_MODEM,
	UCM_DEVICE_LED,
 	UCM_DEVICE_BUZZER,
	UCM_DEVICE_MAX_DEVICE
} TE_UCM_DEVICE;

#define UCM_DEVICE_UCMSTART 0xFD
#define UCM_DEVICE_UCMC     0xFE

#define UCM_MAX_SIZE_DATA_DEVICE 128

typedef struct {
   unsigned char  ucState;       /* 0=OK 1=Errro detected in UCMSTART 2=Error detected in UCMC */
   unsigned char  ucRuf;
   int            iUCMError;
   int            iError;        /* From device */
   unsigned char  ucRUF[ 50 ] ; /* Place pour recuperer d'autres infos ex:numero serie */
} T_UCM_STATUS_DEVICE ;

typedef struct {
   unsigned char  ucMode;				/* Vending or  MPA */
   unsigned char  ucState;          /* 0=OK 1=init 2=degrade*/
   unsigned char  ucMtncMode;       /* 0=exploitation 1=maintenance*/
   unsigned char  ucICLNumber;
   unsigned char  ucICCNumber;
   unsigned char  ucSAMNumber;
   unsigned char  ucSwipeNumber;
   unsigned char  ucDisplayNumber;
   unsigned char  ucPinpadNumber;
   unsigned char  ucPrinterNumber;

   T_UCM_STATUS_DEVICE sDevice[ UCM_DEVICE_MAX_DEVICE ];
} T_UCM_STATUS ;

/* MAX size of struct is UCM_MAX_SIZE_DATA_DEVICE */
typedef struct {
   unsigned char ucICC_Mixte ;  	 /* 0= Smart only else track used */
   unsigned char ucVersionHard[ 4 ];
   unsigned char ucVersionSoft[ 4 ];
   unsigned char ucITP[ 3 ];        /* v0300 */
} T_UCM_ICC_DATA2 ;

/* Define for ucICC_Mixte + add value UCMC_ICC_SWIPE_ISO1 or/and UCMC_ICC_SWIPE_ISO2 or/and UCMC_ICC_SWIPE_ISO3*/
#define UCMC_ICC_NO_SWIPE           0
#define UCMC_ICC_RETRY_SWIPE        0x10 /* swipe reader card insersion */
#define UCMC_ICC_INSER_SWIPE        0x20 /* swipe reader card retry */
#define UCMC_ICC_SWIPE_EXT          0x40 /* swipe reader external not managed by UCMC */
#define UCMC_ICC_SWIPE_ISO1         0x01
#define UCMC_ICC_SWIPE_ISO2         0x02
#define UCMC_ICC_SWIPE_ISO3         0x04

/* MAX size of struct is UCM_MAX_SIZE_DATA_DEVICE */
typedef struct {
   unsigned char ucRuf ;
   unsigned char ucVersionHard[ 8 ];
   unsigned char ucVersionSoft[ 8 ];
} T_UCM_PPAD_DATA ;

/* MAX size of struct is UCM_MAX_SIZE_DATA_DEVICE */
typedef struct {
   unsigned short usInter_Carac_TO ;    /* inter caracters Time Out (MDB) */
   unsigned short usSlave_response_TO ; /* slave Time Out response (MDB) */
} T_UCM_DA_DATA ;

/* MAX size of struct is UCM_MAX_SIZE_DATA_DEVICE */
typedef struct {
   unsigned char ucType ; 
   unsigned char ucMode ; 
   unsigned char ucHeader ; 
   unsigned char ucDisplayOption ;
   unsigned char ucMsg[ 101 ] ;  /* end by null */
} T_UCM_IDLE_MSG2 ;

/* MAX size of struct is UCM_MAX_SIZE_DATA_DEVICE */
typedef struct {
   int iNbP;
   int iP[ 20 ];  /* Parameter */
} T_UCM_COM_DATA ;

/* MAX size of struct is UCM_MAX_SIZE_DATA_DEVICE */
typedef struct {
   unsigned short usAdrGateway;
   unsigned short usAdrCashless;
   int iRuf[ 20 ];  /* Other Parameter */
} T_UCM_HOST_DATA ;

/******************************************************/ 
/*             STRUCTURES DECLARATIONS                */
/******************************************************/
#define UCM_NAME_DLL_DRIVER_LG 16
typedef struct {
   unsigned char ucType ;				/* See TE_UCM_PARAM_TYPED or TE_UCM_PARAM_TYPEP */
   unsigned char ucMode ;
   unsigned char ucPilote ;	      /* Type pilote 0 = driver standard, 1 = driver spécifique, 2 = DLL */
   unsigned char uctNomDriver[ UCM_NAME_DLL_DRIVER_LG ] ;   /* driver name */
   unsigned char uctNomDll   [ UCM_NAME_DLL_DRIVER_LG ] ;   /* Dll name */
   unsigned char ucCom ;			  /* Port com number	*/
   union
   {
	   unsigned char        uctData [ UCM_MAX_SIZE_DATA_DEVICE ];
	   T_UCM_ICC_DATA2       sIcc;
	   T_UCM_DA_DATA   		sDa ;
      T_UCM_PPAD_DATA      sPpad;
	   T_UCM_IDLE_MSG2      sIdleMsg2 ;
      T_UCM_COM_DATA       sComP;
      T_UCM_HOST_DATA      sHost;
  	} u;
   
} T_UCM_DEVICE ;

/* STATUS */
typedef struct {
	unsigned char ucDLL;      /* Status DLL */ 
	unsigned char ucVM;       /* Status vending machine */
	unsigned char ucCoiner;   /* Status Coiner */
}T_UCMHOST_VM_STATUS;

typedef struct {
	unsigned char ucDLL;         /* Status DLL = Init finished ... */ 
	unsigned char ucCom;         /* Status communication = No com ...*/
	int           iNbErrSend;    /* Collision */
	int           iNbErrRece;    /* Collision */
	int           iNbMsgNotSent; /* Msg not sent */
	int           iNbMsgSent;    /*  */
	int           iNbMsgRece;    /*  */
   char          cRuf[ 40 ];
}T_UCMHOST_MPA_STATUS;


typedef struct {
   unsigned char ucType ;	   /* 1=MPA or 2=Vending 3=CBS_vending 4=CBS contactless */
   unsigned char ucMode ;     /* see param */
   union
   {
	   unsigned char        uctData [ UCM_MAX_SIZE_DATA_DEVICE ];
	   T_UCMHOST_VM_STATUS  sHostVM;
      T_UCMHOST_MPA_STATUS sHostMPA;
  	} u;
   
} T_UCM_DEVICE_STATUS ;

typedef enum
{
   PARAM_TYPE_NOT_USED = 0,
   PARAM_TYPE_STANDARD, 
   PARAM_TYPE_HOST,
   PARAM_TYPE_PPR30,
   PARAM_TYPE_PPS10,
   PARAM_TYPE_CAD30VR,      /* 5 */
   PARAM_TYPE_TPASS,          /* 6 */
   PARAM_TYPE_P30,              /* 7 */
   PARAM_TYPE_UPP,			/* 8 OLD PARAM_TYPE_P40 */
   PARAM_TYPE_UCR,			/* 9 OLD PARAM_TYPE_MR40 */
   PARAM_TYPE_USR,			/* 10 OLD PARAM_TYPE_MR40 */
   PARAM_TYPE_IUC180,		/* 11 */
   PARAM_TYPE_IUR250,		/* 12 */
   PARAM_TYPE_IUP250,		/* 13 */
   PARAM_TYPE_IUC150,		/* 14 */
   PARAM_TYPE_GEN,             /* 15 DEBUG SPECIAL */
   PARAM_TYPE_IUC180B,  	/* 11 */
   UCM_MAX_PARAM_TYPED
} TE_UCM_PARAM_TYPED;

typedef enum
{
	PARAM_TYPE_NO_HOST = 0,
	PARAM_TYPE_HOSTDLL,
	PARAM_TYPE_HOSTDLL_INIT_MSG,   /* initialisation by message */
	UCM_MAX_PARAM_TYPEP
} TE_UCM_PARAM_TYPEP;

typedef struct {
   unsigned char ucMMC_type ;  		   /* Type : 0 = n'existe pas */
   unsigned char ucMMC_mode ; 		   /* RUF */
} T_UCM_MMC ;

typedef struct {
   unsigned char ucMsgRepos ; 		   /* 0=Pas d'affichage, 1 = afficher msg repos */
   unsigned char uctMessRest[200 /* UCMC_IAC_BUFFER_DISPLAY_SIZE*/ ] ;	/* Idle Message */
} T_UCM_MSG_REPOS ;
	
#define UCMC_NOIMPLENTRY 10

typedef struct {
	/* [GENERAL] */
   unsigned char uctVersion[ 9 ] ;	   /* Parameters files version */
   unsigned char ucHeader ;			   /* Header non authorized = 0 */
   unsigned char ucUcmType ;
   unsigned char ucUcmMode ;

   /* [DEVICE */
   T_UCM_DEVICE  sDevice[ UCM_DEVICE_MAX_DEVICE ] ;
   
   /* [MMC] */
   T_UCM_MMC     sMmc ;

   /* [DISPLAY_MESS]	 */
   T_UCM_MSG_REPOS sMessRest ;	   /* Idle Message */

   unsigned char ucNoImplEntry[ 2*UCMC_NOIMPLENTRY ] ;  /* List of entry point not to implemented */

   unsigned short usWaitStart ;                         /* -2 RUF for tick waitstart */
   unsigned char  ucWaitStartMode ;                     /* -3 RUF for start */
   unsigned char  ucAutUSBKey ;                         /* -4 RUF for start */

   unsigned char ucRUF[ 100 - 2*UCMC_NOIMPLENTRY - 4] ; /* RUF */

} T_UCM_PARAM ;

#endif


