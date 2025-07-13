/************************************************************/
/* API dans la LIB 														*/
/************************************************************/
extern int  iUcmStartLib_GetInfo( object_info_t *pinfos_p ) ;
extern int  iUcmStartLib_Open(char *);
extern void UcmStartLib_Close(void);
extern int  iUcmStartLib_Cmd(unsigned short, int, void*, int, void* ) ;

/************************************************************/
/* Description des commandes API dans la LIB						*/
/************************************************************/
#define UCMSTART_INIT			      0x0001
#define UCMSTART_PARAM_TREAT_FILE   0x0002
#define UCMSTART_PARAM_GET          0x0003
#define UCMSTART_PARAM_GET_DEVICE   0x0004
#define UCMSTART_PARAM_EDIT_FILE    0x0005
#define UCMSTART_INIT_EXTENS		   0x0006
#define UCMSTART_STATUS_GET         0x0007
#define UCMSTART_SYSTEM_FIOCTL      0x0008
#define UCMSTART_STATUS_SET         0x0009
#define UCMSTART_PARAM_TAG_SET      0x000A
#define UCMSTART_PARAM_SAVE         0x000B
#define UCMSTART_GET_SOFT_BEHAVIOUR 0x000C
#define UCMSTART_GET_ITP            0x000D
#define UCMSTART_PARAM_RESULT_TREAT_FILE   0x000E
#define UCMSTART_UCMC_FILE_UPDATE   0x000F
#define UCMSTART_PARAM_DEFAULT      0x0010
#define UCMSTART_PARAM_GET_OPE      0x0011
#define UCMSTART_PARAM_GET_DEVICE_OPE 0x0012
#define UCMSTART_GET_ITP_ICC0         0x0013
#define UCMSTART_GET_ITP_ICC1         0x0014

#define UCMSTART_ERROR_ADD				0x0020
#define UCMSTART_ERROR_EDIT_FILE    0x0021
#define UCMSTART_ERROR_ERASE_FILE	0x0022
#define UCMSTART_ERROR_TOOLS			0x0023
#define UCMSTART_ERROR_DRIVER			0x0024

#define UCMSTART_CONF_EDIT_FILE     0x0025

#define UCMSTART_ANY_EDIT_FILE      0x0026
#define UCMSTART_ANY_COPY_FILE      0x0027
#define UCMSTART_ANY_DELETE_FILE    0x0028

#define UCMSTART_CONF_FILE_DEVICE_CREATE  0x0029

#define UCMSTART_CONF_HARD_DATA     0x0030

#define UCMSTART_CONF_HARD_ORIGINAL 0x0031

/* Lance la DLL x= pointeur sur NULL pas utilisé */
#define iUcmStartDll_Init( x )             (iUcmStartLib_Cmd( UCMSTART_INIT, 0, x, 0, NULL ) )
#define iUcmStartDll_Init_Extens( x, y)      (iUcmStartLib_Cmd( UCMSTART_INIT_EXTENS, x, y, 0, NULL ) )
/* Traite le fichier de parametrage x=pointeur sur S_FILE utilisé dans file _received() */
#define iUcmStartDll_Param_Treat_File( x ) (iUcmStartLib_Cmd( UCMSTART_PARAM_TREAT_FILE, sizeof( S_FILE ) , x , 0, NULL ) )
/* Result of  parameters file trt */
#define iUcmStartDll_Param_Result_Treat_File( void ) (iUcmStartLib_Cmd( UCMSTART_PARAM_RESULT_TREAT_FILE, 0 , NULL, 0, NULL ) )
/* Result of  parameters file trt */
#define iUcmStartDll_Param_UCM_File_Update( void ) (iUcmStartLib_Cmd( UCMSTART_UCMC_FILE_UPDATE, 0 , NULL, 0, NULL ) )
/* Demande des parametres x=pointeur sur T_UCM_PARAM  */
#define iUcmStartDll_Param_Get_Param( x )  (iUcmStartLib_Cmd( UCMSTART_PARAM_GET, sizeof( T_UCM_PARAM), x, 0, NULL ) )
/* Demande des parametres x=pointeur sur T_UCM_PARAM  */
#define iUcmStartDll_Param_Get_Param_OPE( x )  (iUcmStartLib_Cmd( UCMSTART_PARAM_GET_OPE, sizeof( T_UCM_PARAM), x, 0, NULL ) )
/* Demande des parametres d'un device x=pointeur sur char, type de device demande  y=pointeur sur T_UCM_DEVICE */
#define iUcmStartDll_Param_Get_Param_Device( x, y ) (iUcmStartLib_Cmd( UCMSTART_PARAM_GET_DEVICE, 1, x, sizeof( T_UCM_DEVICE), y ) )
/* Demande des parametres d'un device en mode exploitationx=pointeur sur char, type de device demande  y=pointeur sur T_UCM_DEVICE */
#define iUcmStartDll_Param_Get_Param_Device_OPE( x, y ) (iUcmStartLib_Cmd( UCMSTART_PARAM_GET_DEVICE_OPE, 1, x, sizeof( T_UCM_DEVICE), y ) )
/* Mise a jour un parametre x=pointeur sur TAG, y longueur valeur, z pointeur sur valeur */
#define iUcmStartDll_Param_Set_TAG( x , y, z )  (iUcmStartLib_Cmd( UCMSTART_PARAM_TAG_SET, 7 /* longueur TAG*/, x , y, z ) )
/* Demande des parametres x=pointeur sur parametre sur 1 octet */
#define iUcmStartDll_Param_Set_Default( x ) (iUcmStartLib_Cmd( UCMSTART_PARAM_DEFAULT, 1 , x, 0, NULL  ) )
/* Demande des parametres x=pointeur sur parametre sur 1 octet */
#define iUcmStartDll_Param_Save( x )  (iUcmStartLib_Cmd( UCMSTART_PARAM_SAVE, 1, x, 0, NULL ) )
/* Edition des parametres sur sortie definie par x  x=pointeur sur char exemple sur UCM_COPY_PRINTER */
#define iUcmStartDll_Param_Edit_File( x ) (iUcmStartLib_Cmd( UCMSTART_PARAM_EDIT_FILE, 1 , x, 0, NULL ) )
/* Give software behaviour */
#define iUcmStartDll_Get_Soft_Behaviour( void ) (iUcmStartLib_Cmd( UCMSTART_GET_SOFT_BEHAVIOUR, 0, NULL, 0, NULL ) )
/* Give ITP behaviour */
#define iUcmStartDll_Get_ITP( x )       (iUcmStartLib_Cmd( UCMSTART_GET_ITP, 3, x, 0, NULL ) )
/* Give ITP ICC0 behaviour */
#define iUcmStartDll_Get_ITP_ICC0( x )       (iUcmStartLib_Cmd( UCMSTART_GET_ITP_ICC0, 3, x, 0, NULL ) )
/* Give ITP ICC1 behaviour */
#define iUcmStartDll_Get_ITP_ICC1( x )       (iUcmStartLib_Cmd( UCMSTART_GET_ITP_ICC1, 3, x, 0, NULL ) )
/*  Ajoute une erreur dans le fichier x=pointeur sur T_DLLSTART_ERR_ADD */
#define iUcmStartDll_Error_Add( x ) (iUcmStartLib_Cmd( UCMSTART_ERROR_ADD, sizeof( T_DLLSTART_ERR_ADD ), x, 0, NULL ) )
/*  Edition des erreurs sur sortie definie par x x=pointeur sur T_DLLSTART_ERR_ADD */
#define iUcmStartDll_Error_Edit_File( x ) (iUcmStartLib_Cmd( UCMSTART_ERROR_EDIT_FILE, sizeof( T_DLLSTART_ERR_ADD), x, 0, NULL ) )
/*  Efface le fichier d'erreur  */
#define iUcmStartDll_Error_Erase_File( ) (iUcmStartLib_Cmd( UCMSTART_ERROR_ERASE_FILE, 0, NULL, 0, NULL ) )
/*  Ajoute dans le fichier d'erreur la taille des fichiers UCM x=pointeur sur  */
#define iUcmStartDll_Error_Tools( ) (iUcmStartLib_Cmd( UCMSTART_ERROR_TOOLS, 0, NULL, 0, NULL ) )
/* Demande des etats des peripheriques */
#define iUcmStartDll_Status_Get( x )  (iUcmStartLib_Cmd( UCMSTART_STATUS_GET, sizeof(T_UCM_STATUS), x, 0, NULL ) )
/* Mise ajour des etats  x=pointeur sur T_UCM_STATUS  */
#define iUcmStartDll_Status_Set( x )  (iUcmStartLib_Cmd( UCMSTART_STATUS_SET, sizeof(T_UCM_STATUS), x, 0, NULL ) )

/* Compatible SystemFioctl( x, z) y est la longueur */
#define iUcmStartDll_SystemFioctl( x, y, z )  (iUcmStartLib_Cmd( UCMSTART_SYSTEM_FIOCTL, x, NULL, z, y ) )

/* Edition d'un fichier y sur sortie definie par x  x=pointeur sur char exemple sur UCM_COPY_PRINTER */
#define iUcmStartDll_Conf_Edit_File( x ) (iUcmStartLib_Cmd( UCMSTART_CONF_EDIT_FILE, 1 , x, 0, NULL ) )

/* Edition d'un fichier y sur sortie definie par x  x=pointeur sur char exemple sur UCM_COPY_PRINTER */
#define iUcmStartDll_Conf_Hard_Data( x, y ) (iUcmStartLib_Cmd( UCMSTART_CONF_HARD_DATA, y , x, 0, NULL ) )

/* Edition d'un fichier y sur sortie definie par x  x=pointeur sur char exemple sur UCM_COPY_PRINTER */
#define iUcmStartDll_Conf_Hard_Original( void ) (iUcmStartLib_Cmd( UCMSTART_CONF_HARD_ORIGINAL, 0 , NULL, 0, NULL ) )

/* Edition d'un fichier y sur sortie definie par x  x=pointeur sur char exemple sur UCM_COPY_PRINTER */
#define iUcmStartDll_Any_Edit_File( x, y ) (iUcmStartLib_Cmd( UCMSTART_ANY_EDIT_FILE, 1 , x, 40, y ) )
/* Copy d'un fichier y sur sortie definie par x  x=pointeur sur char exemple sur UCM_COPY_PRINTER */
#define iUcmStartDll_Any_Copy_File( x, y ) (iUcmStartLib_Cmd( UCMSTART_ANY_COPY_FILE, 40 , x, 40, y ) )
/* Copy d'un fichier y sur sortie definie par x  x=pointeur sur char exemple sur UCM_COPY_PRINTER */
#define iUcmStartDll_Any_Delete_File( x, y ) (iUcmStartLib_Cmd( UCMSTART_ANY_DELETE_FILE, 20 , x, 20, y ) )

/* Creation fichier configuration  x=device */
#define iUcmStartDll_Conf_File_Device_Create( x ) (iUcmStartLib_Cmd( UCMSTART_CONF_FILE_DEVICE_CREATE, 4 , x, 0, NULL ) )

/************************************************************/
/* Erreur																	*/
/************************************************************/
#define UCMSTARTLIB_ERR_DLL_NAME               ( -1 )
#define UCMSTARTLIB_ERR_LINK                   ( -2 )
#define UCMSTARTLIB_ERR_OBJECTLOAD             ( -3 )
#define UCMSTARTLIB_ERR_CMD_NOT_AUTHORIZED     ( -4 )

#define UCMSTARTLIB_ERROR_NO_DEVICE_DETECTED		( -5 )
#define UCMSTARTLIB_ERROR_LINK			         ( -6 )
#define UCMSTARTLIB_ERROR_OBJECT_LOAD			   ( -7 )
#define UCMSTARTLIB_ERROR_TRT_PARAM		   	   ( -8 )
#define UCMSTARTLIB_ERROR_DEVICE_UNAUTHORIZED   ( -9 )
#define UCMSTARTLIB_ERROR_DEVICE_OUT_OF_SERVICE ( -10 )
/*************************************************************/
/*  Structures                                               */
/*************************************************************/
#define UCM_CURRENT_FILE "%s/%s"
#define UCM_DISK         "/UCMDDF"

/*************************************************************/
/*  Structures                                               */
/*************************************************************/
typedef struct {
unsigned char 	ucCriticity ;
unsigned short usFunction ;
int  				iNumErr ;
char 				*pcMessage ;
} T_DLLSTART_ERR_ADD ;

