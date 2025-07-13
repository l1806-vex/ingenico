/*! @addtogroup KSFAM_OS
	* @{
 */ 
 
#ifndef __CALLHOST_H
#define __CALLHOST_H


//! \defgroup CALLHOST CallHost
//! @{

//! \defgroup CALLHOST_CALL_TYPES_VALUE Call Types values

//! \defgroup CALLHOST_ACTIVITY_TYPES List of Activities

//! \defgroup CALLHOST_ACTIVITY_IDX Index of Activities

//! \defgroup CALLHOST_CALL_REASON Call Reasons

//! \defgroup CALLHOST_ERR_CODES Return values of CallHost

//! \defgroup CALLHOST_CALLBACK_ID Callbacks identifiers

//! \defgroup CALLHOST_SAMPLE Sample

//! @}

//! @defgroup NTP_FUNCTIONS NTP_Functions

/*! @}  */ 



//! \addtogroup CALLHOST
//! @{

/*! @brief Define the constructor's code.*/
typedef char  T_CONSTRUCTOR_ID [8]; 

/*! @brief Define the product code.*/
typedef char  T_PRODUCT_ID [3];  	

/*! @brief Version number of the boot in the terminal.*/
typedef char  T_BOOT_VERSION [4];  	

/*! @brief Serial number of the terminal*/
typedef char  T_TERMINAL_NUMBER [8];  

/*! @brief Define the basic information about the terminal.*/
typedef struct
{
T_CONSTRUCTOR_ID 		ConstructorCode;			/*!< Code of the constructor.*/
T_PRODUCT_ID 				ProductCode;					/*!< Code of the product.*/
T_BOOT_VERSION 			BootVersion;					/*!< Version of the boot.*/
T_TERMINAL_NUMBER 	TerminalNumber;				/*!< serial number of the terminal.*/
} S_IDENT_TERMINAL;


/*! @brief Call number. Must be right filled with '0'.*/
typedef char 	T_CALL_NUMBER[35];

/*! @brief Contract name.*/
typedef char 	T_CONTRACT  [10];     

/*! @brief Application name. Must be right filled with space ( 0x20 )*/
typedef char 	T_APPLI_NAME[11];

/*! @brief File name, /0 terminated (0x00)*/
typedef char  	T_FILE_NAME[FS_FILENAMESIZE];

/*! @brief Disk name. /0 terminated (0x00)*/
typedef char  	T_DISK_NAME[FS_DISKNAMESIZE];

/*! @brief Path name. /0 terminated (0x00)*/
typedef char  	T_PATH_NAME[FS_PATHSIZE];

/*! @brief Define the reading and writing name of a disk.*/
typedef struct
{
T_DISK_NAME 	ReadDisk;									/*!< disk name for reading.*/
T_DISK_NAME 	WriteDisk;								/*!< disk name for writing.*/
} S_DISK;

/*
======================================================================
					List of Defines
======================================================================
*/

/*! @brief Max number of defined activities. */
#define  MAX_ACTIVITY   					32

//! @}

//! \addtogroup CALLHOST_ACTIVITY_TYPES
//! @brief  List of activities authorized or performed (bit field). 
//! \li Authorized activities set in \ref S_PARAM_SYSTEM_CALL.AuthorizedActivity
//! \li Performed activities returned in PerformedActivity (output parameter of Callhost)
//! @{

/*! @brief No activity is authorised. */
#define  NONE_ACTIVITY   			0x00L		
/*! @brief Download activity is authorised or performed. */
#define  DOWNLOADING_ACTIVITY   	0x01L	
/*! @brief Diagnostic activity is authorised  or performed. */
#define  DIAGNOSTIC_ACTIVITY   		0x02L		
/*! @brief Maintenance activity is authorised  or performed. */
#define  MAINTENANCE_ACTIVITY   	0x04L			
/*! @brief Licence activity is authorised  or performed. */
#define  LICENCE_ACTIVITY   		0x08L
/*! @brief Remote control activity is authorised  or performed. */
#define  REMOTE_CONTROL_ACTIVITY	0x10L			
/*! @brief Custom1 activity is authorised  or performed. */
#define  CUSTOM1_ACTIVITY       	0x20L	
/*! @brief Custom2 activity is authorised  or performed. */
#define  CUSTOM2_ACTIVITY       	0x40L	

/* @} */


/*! @addtogroup CALLHOST_ACTIVITY_IDX
*! @brief to index \ref S_PARAM_SYSTEM_CALL.DiskActivity
*! @{
*/

/*! @brief Download activity corresponding index. */
#define  IDX_DOWNLOADING_ACTIVITY     0x00		
/*! @brief Diagnostic activity corresponding index. */
#define  IDX_DIAGNOSTIC_ACTIVITY      0x01		
/*! @brief Maintenance activity corresponding index. */
#define  IDX_MAINTENANCE_ACTIVITY     0x02		
/*! @brief Licence activity corresponding index. */
#define  IDX_LICENCE_ACTIVITY         0x03		
/*! @brief Remote control activity corresponding index. */
#define  IDX_REMOTE_CONTROL_ACTIVITY  0x04		
/*! @brief Custom 1 activity corresponding index. */
#define  IDX_CUSTOM1_ACTIVITY         0x05		
/*! @brief Custom 2 activity corresponding index. */
#define  IDX_CUSTOM2_ACTIVITY         0x06		

/*! @} */


/*! @addtogroup CALLHOST_CALL_TYPES_VALUE
* @brief parameter CallType of Callhost
* @{
*/

/*! @brief Local Loading Tool connection. */
#define  LOCAL_CALL   				0x01
/*! @brief Remote call using modem (PSTN). Set the phone number in \ref S_PARAM_SYSTEM_CALL.CallNumber */
#define  REMOTE_CALL   				0x02
/*! @brief Remote call using internet connexion. Set the host ip address in \ref S_PARAM_SYSTEM_CALL.CallNumber.\n If SSL needed, the port and the SSL profile are set in the \ref S_PARAM_SYSTEM_CALL.CallNumber */
#define  REMOTE_IP     				0x03
/*! @brief Remote call with using a PPP channel established by application ( \ref CALLHOST_SAMPLE)*/
#define  REMOTE_X   				0x04
/*! @brief Remote call using internet connexion. Use \ref S_EXTENDED_PARAM_SYSTEM_CALL instead of \ref S_PARAM_SYSTEM_CALL. */
#define  REMOTE_IP_EXTENDED			0x05

/*! @} */



/*! @addtogroup CALLHOST_CALL_REASON
* @brief reason of call -> \ref S_PARAM_SYSTEM_CALL.CallReason
* @{
*/
/*! @brief Call started by user */
#define  MANUAL_CALL                'M'
/*! @brief Call started by software */
#define  CYCLIC_CALL                'C'
/*! @brief Retry */
#define  N_PARAMETER_CALL           'N'

/* @} */

/*! @addtogroup CALLHOST_CALLBACK_ID
* @brief set in \ref U_CALLBACK.id to identify the session step and the struct of union filled.<br>
* The processing is done in the function set in \ref S_PARAM_SYSTEM_CALL.CallBack.
* @{
*/

/*! @brief Called when connecting. -> \ref U_CALLBACK.connect */
#define CALLBACK_CONNECT               0
/*! @brief Called when openning file. -> \ref U_CALLBACK.connect */
#define CALLBACK_OPEN                  1
/*! @brief Called when closing file. ->  \ref U_CALLBACK.connect */
#define CALLBACK_CLOSE                 2
/*! @brief Called when reading file. -> \ref U_CALLBACK.read */
#define CALLBACK_READ                  3
/*! @brief Called when writting file. -> \ref U_CALLBACK.write */
#define CALLBACK_WRITE                 4
/*! @brief Called when disconnecting. ->  \ref U_CALLBACK.disconnect  */
#define CALLBACK_DISCONNECT            5
/*! @brief Called when retry to connect. ->  \ref U_CALLBACK.retry  */
#define CALLBACK_RETRY                 6
/*! @brief Called when enter LLT (local software loading tool) sim. ->  \ref U_CALLBACK.enterlltsim */
#define CALLBACK_ENTER_LLTSIM          7
/*! @brief Called when exit LLT (local software loading tool) sim. ->  \ref U_CALLBACK.exitlltsim */
#define CALLBACK_EXIT_LLTSIM           8

/*! @} */

/*
======================================================================
			Data Struct Definition
======================================================================
*/

//! \addtogroup CALLHOST
//! @{

/*! @brief Struct used for connect callback.*/
typedef struct {
  int          id;             /*!< \ref U_CALLBACK.id = CALLBACK_CONNECT */
  FILE         *handler;
} S_CALLBACK_CONNECT;

/*! @brief Struct used for open file callback.*/
typedef struct {
  int          id;             /*!< \ref U_CALLBACK.id = CALLBACK_OPEN*/
  T_FILE_NAME  file;           /*!< file name opened*/
} S_CALLBACK_OPEN;

/*! @brief Struct used for close file callback.*/
typedef struct {
  int          id;             /*!< \ref U_CALLBACK.id = CALLBACK_CLOSE*/
} S_CALLBACK_CLOSE;

/*! @brief Struct used for read file callback.*/
typedef struct {
  int          id;             /*!< \ref U_CALLBACK.id = CALLBACK_READ*/
  unsigned int len;            /*!< read length*/
} S_CALLBACK_READ;

/*! @brief Struct used for write file callback.*/
typedef struct {
  int          id;             /*!< \ref U_CALLBACK.id = CALLBACK_WRITE*/
  unsigned int len;            /*!< written length*/
} S_CALLBACK_WRITE;

/*! @brief Struct used for disconnect callback.*/
typedef struct {
  int          id;             /*!< \ref U_CALLBACK.id = CALLBACK_DISCONNECT*/
} S_CALLBACK_DISCONNECT;

/*! @brief Struct used for retry callback.*/
typedef struct {
  int          id;             /*!< \ref U_CALLBACK.id = CALLBACK_RETRY*/
} S_CALLBACK_RETRY;

/*! @brief Struct used for "enter LLT (local software loading tool) sim." callback.*/
typedef struct {
  int          id;             /*!< \ref U_CALLBACK.id = S_CALLBACK_ENTER_LLTSIM*/
} S_CALLBACK_ENTER_LLTSIM;

/*! @brief Struct used for "exit LLT (local software loading tool) sim." callback.*/
typedef struct {
  int          id;             /*!< \ref U_CALLBACK.id = S_CALLBACK_EXIT_LLTSIM*/
} S_CALLBACK_EXIT_LLTSIM;

/*! @brief This union contain all the callback informations.*/
typedef union {
  int           			id;									/*!< CALLBACK id.*/
  S_CALLBACK_CONNECT      	connect;							/*!< callback connection informations.*/
  S_CALLBACK_DISCONNECT   	disconnect;							/*!< callback disconnection informations.*/
  S_CALLBACK_OPEN         	open;								/*!< callback opening informations.*/
  S_CALLBACK_READ         	read;								/*!< callback reading informations.*/
  S_CALLBACK_WRITE        	write;								/*!< callback writing informations.*/
  S_CALLBACK_CLOSE        	close;								/*!< callback closing informations.*/
  S_CALLBACK_RETRY        	retry;								/*!< callback retry informations.*/
  S_CALLBACK_ENTER_LLTSIM   enterlltsim;						/*!< callback informations to enter LLT (local software loading tool) sim.*/
  S_CALLBACK_EXIT_LLTSIM    exitlltsim;							/*!< callback informations to exit LLT (local software loading tool) sim.*/
} U_CALLBACK;

/*! @brief Define the system call parameters. The members are right filled with space. Before setting, the struct should be set with 0x20 */
typedef struct
{
T_CALL_NUMBER  CallNumber;										/*!< number to call Host:
																	 
																 	\li PSTN (\ref REMOTE_CALL): call number with \\0.<br>
																 		if X25 link, the X25 connection is realised by the application (send X25 frames from \ref CALLBACK_CONNECT )
																 											 	
																 	\li IP (\ref REMOTE_IP): IP address with \\0.<br>
																 		if SSL required, the port and the SSL profile are set in this member : \em xx.\em xx.\em xx.\em xx: \em port_number/\em SSL_profile_name (for ex 12.34.56.78:6000/INGESTRUST).

																*/
T_CONTRACT     Contract;										/*!< contract number */
T_APPLI_NAME   AppliName;										/*!< application name that calls the host right filled with space */
long           AuthorizedActivity;								/*!< \ref CALLHOST_ACTIVITY_TYPES authorised.*/
T_DISK_NAME    DiskActivity[MAX_ACTIVITY];						/*!< table containing list of destination disks. use \ref CALLHOST_ACTIVITY_IDX to index the disk */
T_PATH_NAME    UpdateComponentList;								/*!< update component list, path name.*/
T_PATH_NAME    MailFile;										/*!< file of the mail.*/
char           CallReason;										/*!< \ref CALLHOST_CALL_REASON*/
unsigned int   Nb1;												/*!< retries number */
unsigned int   T1;												/*!< time between 2 retries in seconds */
int            (*CallBack)(unsigned int lg, U_CALLBACK *adr);	/*!< callback function. User function to manage the display processing or to realize some protocol commands (X25 for ex) */
} S_PARAM_SYSTEM_CALL;   

/*! @brief Define the system call extended parameters (used with \ref REMOTE_IP_EXT). The members are right filled with space. Before setting, the struct should be set with 0x20 */
typedef struct
{
T_CALL_NUMBER  CallNumber;										/*!< number to call Host:
																	 
																 	\li PSTN (\ref REMOTE_CALL): call number with \\0.<br>
																 		if X25 link, the X25 connection is realised by the application (send X25 frames from \ref CALLBACK_CONNECT )
																 											 	
																 	\li IP (\ref REMOTE_IP): IP address with \\0.<br>
																 		if SSL required, the port and the SSL profile are set in this member : \em xx.\em xx.\em xx.\em xx: \em port_number/\em SSL_profile_name (for ex 12.34.56.78:6000/INGESTRUST).

																*/
T_CONTRACT     Contract;										/*!< contract number */
T_APPLI_NAME   AppliName;										/*!< application name that calls the host right filled with space */
long           AuthorizedActivity;								/*!< \ref CALLHOST_ACTIVITY_TYPES authorised.*/
T_DISK_NAME    DiskActivity[MAX_ACTIVITY];						/*!< table containing list of destination disks. use \ref CALLHOST_ACTIVITY_IDX to index the disk */
T_PATH_NAME    UpdateComponentList;								/*!< update component list, path name.*/
T_PATH_NAME    MailFile;										/*!< file of the mail.*/
char           CallReason;										/*!< \ref CALLHOST_CALL_REASON*/
unsigned int   Nb1;												/*!< retries number */
unsigned int   T1;												/*!< time between 2 retries in seconds */
int            (*CallBack)(unsigned int lg, U_CALLBACK *adr);	/*!< callback function. User function to manage the display processing or to realize some protocol commands (X25 for ex) */
unsigned char  SslProfileName[11];                              /*!< SSL profile with \\0. Must be fill with \\0 if SSL must not be used */
unsigned int   Port;											/*!< Port of the server */
unsigned char  Adress[256];										/*!< IP adress or domain name with \\0 */
} S_EXTENDED_PARAM_SYSTEM_CALL;

//! @}

/*! @addtogroup CALLHOST_ERR_CODES Return values of CallHost
* @{
*/

/*! @brief Call host was successful */
#define CALL_HOST_OK                (0)
/*! @brief Argument missing */
#define CALL_HOST_ARG_MISSING      (-1)
/*! @brief Invalid argument */
#define CALL_HOST_ARG_INVALID      (-2)
/*! @brief PPP configuration fail */
#define CALL_HOST_PPP_CONFIG_FAIL  (-3)
/*! @brief Host configuration fail */
#define CALL_HOST_CONNECTION_FAIL  (-4)
/*! @brief Host configuration lost */
#define CALL_HOST_CONNECTION_LOST  (-5)

/* @} */


/*
======================================================================
			Functions Definition
======================================================================
*/

//! \addtogroup CALLHOST
//! @{

/*! @brief This function initiates the downloader with parameters provided by the application. 
 *
 * It handles the complete FTP session with the host. 
 *
 * A call back function is called at the different steps of downloading : Connect, Open, Close, Read, Write, Disconnect.
 * Please contact us for details. 
 * @param CallType : (in) type of call : \ref CALLHOST_CALL_TYPES_VALUE (for ex \ref LOCAL_CALL).
 * @param pt_ParamCall : (in) pointer on \ref S_PARAM_SYSTEM_CALL or \ref S_EXTENDED_PARAM_SYSTEM_CALL struct.
 * @param PerformedActivity : (out)  bit field. \ref CALLHOST_ACTIVITY_TYPES performed (for ex \ref DOWNLOADING_ACTIVITY|\ref DIAGNOSTIC_ACTIVITY)
 * @return
 * - \ref CALL_HOST_OK , in such case PerformedActivity returns Host activity (Nothing, Downloading, Maintenance) 
 * - otherwise, non zero value if download has not been executed:
 *  - \ref CALL_HOST_ARG_MISSING
 *  - \ref CALL_HOST_ARG_INVALID 
 *  - \ref CALL_HOST_PPP_CONFIG_FAIL
 *  - \ref CALL_HOST_CONNECTION_FAIL 
 *  - \ref CALLHOST_ERR_CODES ..
 *
 * @note 
 * - --> \ref CALLHOST_SAMPLE .
 * - This function returns control to the application. The application must process the return code of the function and then, must perform a reset. 
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:CallHost:KSFAM_AUTRES:
//  @GSIM_S:CallHost:E_CallHost
// \endif
int CallHost(char CallType, S_PARAM_SYSTEM_CALL *pt_ParamCall,long *PerformedActivity);

//! @}

/*! @addtogroup CALLHOST_SAMPLE
 *! @code

   int CallHostHandler(unsigned lg, U_CALLBACK *pData) // -> callback to get info from Callhost session 
   {
      switch(pDate->id)
 	   {
 
        case CALLBACK_DISCONNECT:
        {
         
        }break;
        ...
 	   }
   }
	
  int ExecuteCallHost( void )
  {
    S_PARAM_SYSTEM_CALL ParamCall;
    char nCallType;
    PPP_HANDLE   nHandle;
    FILE* hCom5;
    unsigned char bContinue;
    long nPerformedActivity;
    bContinue=FALSE;
    hCom5=0;
    nHandle=0;
    nCallType=REMOTE_IP
 
     // Struct init --> this initialization is mandatory
    memset( &ParamCall, 0x20, sizeof( S_PARAM_SYSTEM_CALL ));
 
    switch(nCallType)
    {
      case REMOTE_CALL:
      {
         strcpy( ParamCall.CallNumber, "0474000000" );  // call number because the Call Type is REMOTE_CALL (PSTN)
         bContinue=TRUE;
      }break;
      
      case REMOTE_IP:
      {
         strcpy( ParamCall.CallNumber, "192.168.1.1" );  // IP address because the Call Type is REMOTE_IP
      }break;
 		
      case REMOTE_X:
      {
         PPP_HANDLE nHandle = 0;
         hCom5 = fopen("COM5", "rw*");
         if (hCom5)
         {
            int arg;
        	// the appli establishs the connection point to point to the TMS
            nHandle = PPP_Open( "COM5"); // -->  the easiest configuration: The terminal is connected to the TMS station via USB
            if (nHandle)
            {
               PPP_SetOption(ppp, PPP_INFO_AUTH_USER, "user");
               PPP_SetOption(ppp, PPP_INFO_AUTH_SECRET, "password");
               arg=PPP_FALSE;  PPP_SetOption(ppp, PPP_INFO_LCP_AUTH, &arg);
            
               arg=PPP_TRUE;   PPP_SetOption(ppp, PPP_INFO_IPCP_ACCEPT_LOCAL, &arg);
               arg=PPP_TRUE;   PPP_SetOption(ppp, PPP_INFO_IPCP_ACCEPT_REMOTE, &arg);
               arg=PPP_FALSE;  PPP_SetOption(ppp, PPP_INFO_IPCP_DNS1, &arg);
               arg=PPP_FALSE;  PPP_SetOption(ppp, PPP_INFO_IPCP_DNS2, &arg);
               reset_buf(hCom5,_receive_id);
               PPP_Start(nHandle);
               if (PPP_GetState(nHandle)==PPP_STATE_IFUP)
               {
                 bContinue=TRUE;
                 // PPP link ON
               }
 
             }
         }
      }break;
 
      default:		
      //case LOCAL_CALL:
      {
      }break;
    }
    
   if (bContinue)
   {
     // ParamCall.Contract : 1st byte must be set to '1' to indicate that contract exist
     //			Other bytes are contract number.
      //			Length must be 10 digits (if needed, this field must be padded with blank)
      strcpy( ParamCall.Contract, "1" );		//'1' to indicate that contract exist.
 
      strcpy(szContractNumber,"1234");		// contrat number "1234" for ex
 
      memcpy( &ParamCall.Contract[1], szContractNumber, strlen( szContractNumber ));
 
 	  // Application number that requests the download.
      strcpy( ParamCall.AppliName,  "MyAppli" ); 
 
      // All TMS activities except 'Licence'
      ParamCall.AuthorizedActivity = DOWNLOADING_ACTIVITY | DIAGNOSTIC_ACTIVITY | MAINTENANCE_ACTIVITY ;
      strcpy( ParamCall.DiskActivity[IDX_DOWNLOADING_ACTIVITY], VOLUME_SYSTEM ); //VOLUME_SYSTEM defined in etat.h
      strcpy( ParamCall.DiskActivity[IDX_DIAGNOSTIC_ACTIVITY],  VOLUME_SYSTEM ); //VOLUME_SYSTEM defined in etat.h
      strcpy( ParamCall.DiskActivity[IDX_MAINTENANCE_ACTIVITY], VOLUME_HOST );   //VOLUME_HOST defined in etat.h
 
 	    //
      sprintf( ParamCall.UpdateComponentList, "/%s/%s", VOLUME_MANAGER_RECEPT, "COMPOFILE" ); //VOLUME_MANAGER_RECEPT defined in etat.h
   
 	    //
      ParamCall.CallReason = MANUAL_CALL;
      ParamCall.Nb1 = 5;	 // Maximum retries
      ParamCall.T1  = 30;  // 30s between 2 retries
      ParamCall.CallBack = CallHostHandler; 
 
      // Fork the task to display in charge of the display. 
      if (CallHost( nCallType, &ParamCall, &nPerformedActivity )==CALL_HOST_OK)
      {
      	exit(0);
      }
    }
 
    if (nHandle)
    {
      PPP_Close(nHandle);
    }
    
    if (hCom5)
    {
      fclose(hCom5);
    }
    return 0;
   }
 
 @endcode
*/
//! @{
//! @}



//! @defgroup NTP_FUNCTIONS NTP_Functions
//! @{


/*! @brief This function updates SYSTEM disk from a specified disk. 
 *
 * Signature and syntax are checked before activation. 
 * @param disk : disk name where new software in stored (name without "/") 
 * @return
 * - non zero value if activation has not been executed. In this case see TRACEFILE.LST in input disk
 * - 0 otherwise.
 *
 * @note Warning : SoftwareActivate is case sensitive. Telium software file names with extension must be UPPER case(Otherwise the file is ignored)
 *
 * @link  KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:SoftwareActivate:KSFAM_AUTRES:
//  @GSIM_A:1:IN_ONLY
// \endif
int SoftwareActivate(const char *disk);

/*! @brief This function updates SYSTEM disk from a specified disk. 
 *  @note See \ref SoftwareActivate for more details
 */
#define NTP_SoftwareActivate SoftwareActivate

/*! @brief This function checks a disk without updating SYSTEM disk. 
 *
 * Signature and syntax are checked. 
 * @param disk : disk name where new software is stored (name without "/") 
 * @return
 * - non zero value if activation has not been executed. In this case see TRACEFILE.LST in input disk
 * - 0 otherwise.
 *
 * @note This function is similar to NTP_SoftwareActivate but without SYSTEM update. 
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:NTP_SoftwareCheck:KSFAM_AUTRES:
// \endif
int NTP_SoftwareCheck(const char *disk);

/*! @brief NTP_SoftwareActivateRam allows to update SYSTEM disk from another disk.
 * @param path : Name of the disk, where are stored softwares to be activated.
 * @return
 * - 0 : No errors.
 * - Number of errors otherwise.
 *
 * @note On the disk given in parameter, a file named TRACEFILE.LST is created.
    This file contains the list of errors that occured.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:SoftwareActivateRam:KSFAM_AUTRES:
//  @GSIM_A:1:IN_ONLY
// \endif
int NTP_SoftwareActivateRam(const char *path);

//! @}


#endif
