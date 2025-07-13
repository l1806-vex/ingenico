//! \file Desfire.h
//! \brief This module implements DESFire commands

/** \addtogroup Contactless 
 * @{
    * \defgroup MIFARELib MIFARE Library
    * @{
       * \details This library implements commands to manage: 
       * - DESFire EV0 and EV1 cards,
       * - MIFARE Plus cards.
       *
       * To use this libary, you should have:
       * - the Mifare system library added in the Telium project settings, 
       * - the component CLess\Mifare.Mxx loaded into the terminal.
       *
       * \defgroup Desfire DESFire card management
       * @{
       *    \details This library implements DESFire commands compliant with both DESFire
       *    EV0 and EV1 generations. The APDU exhanged between the PCD and the PICC can be
       *    either in DESFire format (command byte followed by the payload [CMD][Payload]) or in 7816-3
       *    format (also called Wrapped, [CLA][CMD][P1][P2][LC][Payload][LE]). The cryptographic
       *    operations can be done either on the Thunder, either on a MIFARE SAM.
       * 
       *    \par How to use this library :
       *    -# <b>The PICC has to be detected and activated. The SAM has to be detected
       *    and powered if it needs to be used (\ref mifareSAM_AutoDetectSAM).</b>
       *    -# Create a new DESFire context (\ref desfire_NewContext, \ref desfire_NewContextWithSAM).
       *    <b>This is at this step that the communication mode (DESFire Native or Wrapped)
       *    and the cryptographic mode (use a SAM or not) is determined.</b>
       *    -# Use DESFire commands to interact with the PICC using commands provided by
       *    this library. For example : authentication, creation of a new application, selection
       *    of the created application, creation of a file into the selected application,
       *    write into the file, read the file, format the PICC (See \ref DesfireCommands).
       *    -# Free the DESFire context (\ref desfire_FreeContext). If any, free created keys
       *    (\ref mifare_FreeKey).
       *    -# Power off the SAM if it has been powered.
       *    -# Power of the Cless field.
       * 
       *    \par Details about DESFire
       *    - up to 28 applications can be created per card
       *    - up to 16 files can be created under each application
       *    - 5 types of files (standard data file, backup data file, value file,
       *    linear record file and cyclic record file)
       *    - up to 14 key can be set under each application
       *    - 3 communication modes to exchange data with the PICC :
       *       - Plain : data not protected
       *       - MACed : a MAC is computed with a key and appended on data exchanged with the PICC.
       *       - ENCIPHERED : data exchanged between PCD and PICC are ciphered.
       *     
       *    \note When a file is deleted, the PICC memory is not released. The file is only
       *    disabled. The PICC memory can only be freed with a PICC formating (\ref desfire_FormatPicc)
       *
       *    \defgroup DesfireErrors DESFire Errors
       *
       *    \defgroup ContextManagement Context management functions
       *    @{
       *       \brief Functions used to create or free a DESFire context.
       *    @}
       *
       *    \defgroup DesfireCommands DESFire commands
       *    @{
       *      \brief Commands for the PICC.
       *      \defgroup DesfireSecurityLevel Security level commands
       *      @{
       *         \brief Commands related to DESFire PICC security (Authentication, Key management...)
       *      @}
       *      \defgroup DesfirePICCLevel PICC level commands
       *      @{
       *         \brief Commands managing the PICC (Application managment, Memory management, PICC settings...)
       *      @}
       *      \defgroup DesfireApplicationLevel Application level commands
       *      @{
       *         \brief Commands used to manage files of applications (Files settings, file creation and deletion...)
       *      @}
       *      \defgroup DesfireDataLevel Data level commands
       *      @{
       *         \brief Commands allowing to Write or Read data in a file.
       *      @}
       *    @}
	   *
       *    \defgroup KeyManagement Key management functions
       *    @{
       *       \brief Functions to create or free keys to be used for cryptographic operations
       *       without a SAM.
       *    @}
       * @}
       *       
       * \defgroup MifareSAM MIFARE SAM management
       * @{
       *    \defgroup SAMContextManagement SAM context management functions
       *    @{
       *       \brief Functions used to create or free a SAM context. This functions usually don't need
       *       to be used because \ref desfire_NewContextWithSAM or \ref ClessMFP_NewContextWithSAM create  
       *       a SAM context and \ref desfire_FreeContext or \ref ClessMFP_FreeContext also free the SAM context.
       *    @}
       *    \defgroup SAMCommands SAM commands
       *    @{
       *       \brief Commands for the SAM.
       *    @}
       * @}
    * @}
 * @}
 * \example DesfireSample.c
*/

#ifndef __DESFIRE_H__
#define __DESFIRE_H__

// Mifare SAM defines
#define MIFARE_SAM_CAPDU_HEADER_SIZE      5     //!< SAM command APDU header size [CLA][INS][P1][P2][Lc]
#define MIFARE_SAM_CAPDU_PAYLOAD_SIZE     255   //!< Maximum SAM command APDU payload size
#define MIFARE_SAM_MAX_CAPDU_SIZE         (MIFARE_SAM_CAPDU_HEADER_SIZE + MIFARE_SAM_CAPDU_PAYLOAD_SIZE) //!< Maximum SAM command APDU size [CLA][INS][P1][P2][Lc][0..255][Le]
#define MIFARE_SAM_RAPDU_TAIL_SIZE        2     //!< Maximum SAM response APDU tail size [SW1][SW2]
#define MIFARE_SAM_RAPDU_PAYLOAD_SIZE     256   //!< Maximum SAM response APDU payload size
#define MIFARE_SAM_MAX_RAPDU_SIZE         (MIFARE_SAM_RAPDU_PAYLOAD_SIZE + MIFARE_SAM_RAPDU_TAIL_SIZE) //!< Maximum SAM response APDU size [0..256][SW1][SW2]
extern const unsigned char MIFARE_SAM_HISTORICAL[15]; //!< MIFARE SAM Historical
extern const unsigned char MIFARE_SAM_AV1_HISTORICAL[15]; //!< MIFARE SAM AV1 Historical
extern const unsigned char MIFARE_SAM_AV2_HISTORICAL[15]; //!< MIFARE SAM AV2 Historical


// DESFire defines

#define MAX_APPLICATION_COUNT    28 //!< Maximum number of application on a DESFire Card
#define MAX_FILE_COUNT           32 //!< Maximum number of file which can be created in an application
/* Desfire Commands */
#define AUTHENTICATE_LEGACY 0x0A //!< Instruction for authentication for DES and 2K3DES keys. Compliant with DESFire EV0 and EV1 using DESFire chaining for crypto operations
#define AUTHENTICATE_ISO 0x1A    //!< Instruction for authentication for DES, 2K3DES and 3K3DES keys. Compliant with DESFire EV1 using CBC chaining for crypto operations
#define AUTHENTICATE_AES 0xAA    //!< Instruction for authentication for AES keys. Compliant with DESFire EV1
/* Desfire errors */
//! \addtogroup DesfireErrors
//! @{
#define  DESFIRE_OPERATION_OK          0x00 //!< Successful operation
#define  DESFIRE_NO_CHANGES            0x0C //!< No changes done to backup files, \ref desfire_CommitTransaction or \ref desfire_AbortTransaction not necessary
#define  DESFIRE_OUT_OF_EEPROM_ERROR   0x0E //!< Insufficient NV-Memory to complete command
#define  DESFIRE_ILLEGAL_COMMAND       0x1C //!< Command not supported
#define  DESFIRE_INTEGRITY_ERROR       0x1E //!< CRC or MAC does not match data. Padding bytes not valid.
#define  DESFIRE_NO_SUCH_KEY           0x40 //!< Invalid key number specified
#define  DESFIRE_LENGTH_ERROR          0x7E //!< Length of command string invalid
#define  DESFIRE_PERMISSION_DENIED     0x9D //!< Current configuration / status does not allow the requested command
#define  DESFIRE_PARAMETER_ERROR       0x9E //!< Value of the parameter(s) invalid
#define  DESFIRE_APPLICATION_NOT_FOUND 0xA0 //!< Requested AID not present on PICC
#define  DESFIRE_APPL_INTEGRITY_ERROR  0xA1 //!< Unrecoverable error within application, application will be disabled.
#define  DESFIRE_AUTHENTICATION_ERROR  0xAE //!< Current authentication status does not allow the requested command.
#define  DESFIRE_ADDITIONAL_FRAME      0xAF //!< Additional data frame is expected to be sent.
#define  DESFIRE_BOUNDARY_ERROR        0xBE //!< Attempt to read/write data from/to beyond the file's/record's limits. Attempt to exceed the limits of a value file.
#define  DESFIRE_PICC_INTEGRITY_ERROR  0xC1 //!< Unrecoverable error within PICC. PICC will be disabled.
#define  DESFIRE_COMMAND_ABORTED       0xCA //!< Previous command was not fully completed. Not all frames were requested or provided by the PCD.
#define  DESFIRE_PICC_DISABLED         0xCD //!< PICC was disabled by an unrecoverable error.
#define  DESFIRE_COUNT_ERROR           0xCE //!< Number of applications limited to 28, not additional \ref desfire_CreateApplication possible.
#define  DESFIRE_DUPLICATE_ERROR       0xDE //!< Creation of file/application failed because file/application with same number already exists.
#define  DESFIRE_EEPROM_ERROR          0xEE //!< Could not complete NV-write operation due to loss of powedn internal backup/rollback mechanism activated.
#define  DESFIRE_FILE_NOT_FOUND        0xF0 //!< Specified file number does not exist.
#define  DESFIRE_FILE_INTEGRITY_ERROR  0xF1 //!< Unrecoverable error within file. File will be disabled.
#define  DESFIRE_DLL_INIT_OK           0x0000 //!< Initialization of DLL OK
#define  DESFIRE_DLL_NOT_LOADED        0x0100 //!< DLL not loaded
//! @}

/* File types */
//! \addtogroup DesfireApplicationLevel
//! @{

//! \brief DESFire File Types
//! \details File type is returned by te command \ref desfire_GetFileSettings.
//! \sa \ref desfire_GetFileSettings, \ref desfire_CreateValueFile, \ref desfire_CreateStdDataFile,
//! \ref desfire_CreateBackupDataFile, \ref desfire_CreateLinearRecordFile, \ref desfire_CreateCyclicRecordFile
enum T_DESFIRE_FILE_TYPES
{
   DFT_STANDARD_DATA_FILE = 0x00, //!< Standard data file
   DFT_BACKUP_DATA_FILE = 0x01, //!< Data file with a backup mechanism
   DFT_VALUE_FILE_WITH_BACKUP = 0x02, //!< Value file with a bacup mechanism
   DFT_LINEAR_RECORD_FILE_WITH_BACKUP = 0x03, //!< Linear record file with a backup mechanism
   DFT_CYCLIC_RECORD_FILE_WITH_BACKUP = 0x04
//!< Cyclic record file with a backup mechanism
};
//! @}

/* Desfire Communication mode */
#define DCM_PLAIN      0x00 //!< Communication mode PLAIN, data transmitted without protection
#define DCM_MACED      0x01 //!< Communication mode MACED, data protected with a MAC or CMAC
#define DCM_ENCIPHERED 0x03 //!< Communication mode ENCIPHERED, data transmitted is ciphered
/* Masks to get Desfire access rights */
#define DAR_READ(ar)       (((ar) >> 12) & 0x0f) //!< Macro allowing to retreive the access rights of Read operations
#define DAR_WRITE(ar)      (((ar) >>  8) & 0x0f) //!< Macro allowing to retreive the access rights of Write operations
#define DAR_READ_WRITE(ar) (((ar) >>  4) & 0x0f) //!< Macro allowing to retreive the access rights of Read and Write operations
#define DAR_CHANGE_AR(ar)  ((ar)         & 0x0f) //!< Macro allowing to retreive the access rights of Change operations
/* Desfire Access Rights */
#define DAR_KEY0  0x0 //!< Key 0 identifier for Access Rights
#define DAR_KEY1  0x1 //!< Key 1 identifier for Access Rights
#define DAR_KEY2  0x2 //!< Key 2 identifier for Access Rights
#define DAR_KEY3  0x3 //!< Key 3 identifier for Access Rights
#define DAR_KEY4  0x4 //!< Key 4 identifier for Access Rights
#define DAR_KEY5  0x5 //!< Key 5 identifier for Access Rights
#define DAR_KEY6  0x6 //!< Key 6 identifier for Access Rights
#define DAR_KEY7  0x7 //!< Key 7 identifier for Access Rights
#define DAR_KEY8  0x8 //!< Key 8 identifier for Access Rights
#define DAR_KEY9  0x9 //!< Key 9 identifier for Access Rights
#define DAR_KEY10 0xA //!< Key 10 identifier for Access Rights
#define DAR_KEY11 0xB //!< Key 11 identifier for Access Rights
#define DAR_KEY12 0xC //!< Key 12 identifier for Access Rights
#define DAR_KEY13 0xD //!< Key 13 identifier for Access Rights
#define DAR_FREE  0xE //!< Free access right
#define DAR_DENY  0xF //!< Access right value to deny all accesses.
//! \brief Structure filled with command \ref desfire_GetVersion
//! \details This structure contains PICC hardware informations, software
//! informations, date of production and UID
struct S_DESFIRE_VERSION_INFO
{
   struct
   {
      unsigned char ucVendorId; //!< Vendor ID (0x04 for NXP)
      unsigned char ucType; //!< Type
      unsigned char ucSubtype; //!< Subtype
      unsigned char ucVersionMajor; //!< Major version number
      unsigned char ucVersionMinor; //!< Minor version number
      unsigned char ucStorageSize; //!< Storage size. The 7 most significant bits ( =n ) code the storage size itself (2^n). The parity bit is set to 0 if the size is exactly 2^n, 1 if the size is between 2^n and 2^(n+1)
      unsigned char ucProtocol; //!< Communication protocol type
   } hwInfo; //!< Hardware related information
   struct
   {
      unsigned char ucVendorId; //!< Vendor ID (0x04 for NXP)
      unsigned char ucType; //!< Type
      unsigned char ucSubtype; //!< Subtype
      unsigned char ucVersionMajor; //!< Major version number
      unsigned char ucVersionMinor; //!< Minor verson number
      unsigned char ucStorageSize; //!< Storage size. The 7 most significant bits ( =n ) code the storage size itself (2^n). The parity bit is set to 0 if the size is exactly 2^n, 1 if the size is between 2^n and 2^(n+1)
      unsigned char ucProtocol; //!< Communication protocol type
   } swInfo; //!< Software related information
   unsigned char tucUid[7]; //!< Unique Serial Number
   unsigned char tucBatchNumber[5]; //!< Production batch number
   unsigned char ucProductionWeek; //!< Calendar week of production
   unsigned char ucProductionYear; //!< Year of production
};

//! \brief Type allowing to identify APDU mode.
//! \details See \ref ContextManagement.
typedef enum
{
   APDU_NATIVE, //!< Command are sent in desfire native format : [INS][DATA]
   APDU_WRAPPED
//!< Command are wrapped to be sent in desfire ISO/IEC 7816-3 format
} T_DESFIRE_APDU_STYLE;

//! \brief Type to identify authentication scheme.
typedef enum
{
   AS_LEGACY, //!< DESFire native communication. Compliant with EV0 and EV1 (\ref AUTHENTICATE_LEGACY).
   AS_NEW
//!< DESFire standard communication or 3K3DES or AES. Compliant with EV1 only (\ref AUTHENTICATE_ISO, \ref AUTHENTICATE_AES).
} T_DESFIRE_AUTH_SCHEME;

//! \brief File settings
//! \details This structure is especially used for command \ref desfire_GetFileSettings
//! to retrieve the settings of a file.
//! \sa \ref desfire_GetFileSettings, \ref desfire_CreateValueFile,
//! \ref desfire_CreateStdDataFile , \ref desfire_CreateLinearRecordFile ,
//! \ref desfire_CreateCyclicRecordFile , \ref desfire_CreateBackupDataFile
struct S_DESFIRE_FILE_SETTINGS
{
   unsigned char ucFileType; //!< File type. See \ref T_DESFIRE_FILE_TYPES
   unsigned char ucComSettings; //!< File communication settings. See \ref DCM_PLAIN, DCM_MACED, DCM_ENCIPHERED
   unsigned short int usiAccessRights; //!< Access Rigths on 16 bits [Read][Write][Read & Write][Change]. See \ref DAR_READ, \ref DAR_WRITE, \ref DAR_READ_WRITE, \ref DAR_CHANGE_AR
   union
   {
      struct
      {
         unsigned int uiFileSize; //!< Data file size
      } stdFile; //!< Data file (\ref DFT_STANDARD_DATA_FILE and \ref DFT_BACKUP_DATA_FILE)
      struct
      {
         int iLowerLimit; //!< Value file lowed limit
         int iUpperLimit; //!< Value file upper limit
         int iLimitedCreditValue; //!< Value file limited credit value
         bool ucLimitedCreditEnabled; //!< Boolean to indicate whether limited credit is enabled or not.
      } valueFile; //!< Value file (\ref DFT_VALUE_FILE_WITH_BACKUP)
      struct
      {
         unsigned int uiRecordSize; //!< Maximum size of a record
         unsigned int uiMaxNumOfRecords; //!< Maximum number of records in a file
         unsigned int uiCurrentNbOfRecords; //!< Current number of records in a file
      } recordFile; //!< Records (\ref DFT_LINEAR_RECORD_FILE_WITH_BACKUP, \ref DFT_CYCLIC_RECORD_FILE_WITH_BACKUP)
   } settings; //!< File specific settings
};
typedef struct S_DESFIRE_FILE_SETTINGS T_DESFIRE_FILE_SETTINGS; //!< Type associated to \ref S_DESFIRE_FILE_SETTINGS

typedef unsigned char T_DESFIRE_AID[3]; //!< DESFire Application Identifier on 3 bytes.
typedef unsigned char T_DESFIRE_FID; //!< DESFire File Identifier on 1 byte
typedef unsigned char T_DESFIRE_ISO_FID[2]; //!< DESFire ISO File Identifier on 2 bytes

//! \brief Structure used for \ref desfire_GetDfNames result
struct S_DESFIRE_DFNAME
{
   T_DESFIRE_AID aid; //!< Application ID
   T_DESFIRE_ISO_FID isoFid; //!< ISO File identifier
   unsigned char tucDFName[16]; //!< DF Name (not mandatory)
};
typedef struct S_DESFIRE_DFNAME T_DESFIRE_DFNAME; //!< Type associated to \ref S_DESFIRE_DFNAME

//! \brief Type allowing to identify SAM mode
typedef enum
{
   MF_SAM_AV1, //!< SAM mode AV1
   MF_SAM_AV2
//!< SAM mode AV2
} T_MIFARE_SAM_MODE;

//! \brief Structure containing various information related to the key, needed for cryptographic operations.
//! \details For example : key type; key value, des, aes or cmac contexts; generated subkeys etc.
struct S_MIFARE_KEY;

//! \brief Type associated to private structure S_DESFIRE_KEY.
//! \details See \ref KeyManagement.
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion,
//! \ref desfire_NewContext, \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
typedef struct S_MIFARE_KEY T_MIFARE_KEY;

//! \brief Context needed for SAM operations
struct S_MIFARE_SAM_CONTEXT;
typedef struct S_MIFARE_SAM_CONTEXT T_MIFARE_SAM_CONTEXT; //!< Type associated to S_MIFARE_SAM_CONTEXT


//! \brief Context needed for DESFire commands processing.
//! \details See \ref ContextManagement.
//! \sa \ref desfire_NewContext, \ref desfire_NewContextWithSAM, \ref desfire_FreeContext
struct S_DESFIRE_CONTEXT
{
   T_DESFIRE_APDU_STYLE apduStyle; //!< Determines which APDU formatting will be applied for communications between PICC and PCD
   T_DESFIRE_AUTH_SCHEME authenticationScheme; //!< Save the last authentication scheme used.
   T_MIFARE_KEY* pSessionKey; //!< Pointer to the Session key (only when SAM is not used)
   T_DESFIRE_AID currentAID; //!< AID of last selected application
   T_MIFARE_SAM_CONTEXT* pSAMCtx; //!< SAM context. NULL if SAM not used
   unsigned char ucNoKey; //!< Key number used in last authentication
   unsigned char bNoCard; //!< Card number (in case of multiple card detection)
   unsigned char *pucCryptoBuffer; //!< Internal buffer used for cryptographic operations
   int iCryptoBufferSize; //!< pucCryptoBuffer size
};
//! \brief Type associated to \ref S_DESFIRE_CONTEXT
typedef struct S_DESFIRE_CONTEXT T_DESFIRE_CONTEXT;


//! \brief Key Entry for MIFARE SAM key management
typedef struct S_MIFARE_KEY_ENTRY
{
   unsigned char tKeyA[16];
   unsigned char tKeyB[16];
   unsigned char tKeyC[16];
   T_DESFIRE_AID dfAid;
   unsigned char dfKeyNr;
   unsigned char CEK_No;
   unsigned char CEK_V;
   unsigned char KUC;
   unsigned char SET[2];
   unsigned char VerA;
   unsigned char VerB;
   unsigned char VerC;
} T_MIFARE_KEY_ENTRY;

//! \brief Encrypt/Decrypt block chaining mode
typedef enum
{
   MF_CHAINING_ECB, //!< ECB chaining mode.
   MF_CHAINING_CBC, //!< CBC chaining mode.
   MF_CHAINING_DESFIRE_NATIVE //!< MIFARE DESFire Native chaining mode
} T_MIFARE_CHAINING_MODE;

// DESFire Functions

//! \addtogroup ContextManagement
//! @{

//! \brief Initialize a context.
//! \details This context is required to send command to the PICC as it
//! contains essential information about communication settings, the session key
//! the current application, the number of the current key etc.
//! (See \ref T_DESFIRE_CONTEXT).
//! \param[in] apduStyle Defines if the frames used for the communication between
//! the PCD and the PICC will be in DESfire Native mode or in ISO/IEC 7816-3 mode.
//! (See \ref T_DESFIRE_APDU_STYLE).
//! - APDU_NATIVE : Frames in DESfire Native style.
//! - APDU_WRAPPED : Frames in in ISO/IEC 7816-3 style.
//! \return Return a pointer to the initialised context. NULL if an error occured.
//! \sa \ref desfire_FreeContext, \ref desfire_NewContextWithSAM
extern T_DESFIRE_CONTEXT* desfire_NewContext(T_DESFIRE_APDU_STYLE apduStyle);

//! \brief Initialize a context allowing to use SAM for cryptographic operations.
//! \details This context is required to send command to the PICC as it
//! contains essential information about the current application, the number of
//! the current key, and the SAM context which allows to choose the SAM mode etc.
//! (See \ref T_DESFIRE_CONTEXT, \ref T_MIFARE_SAM_CONTEXT).
//! \param[in] hSAM File descriptor of the SAM.
//! \param[in] samMode Use the SAM in AV1 or AV2 mode (see \ref T_MIFARE_SAM_MODE).
//! - MF_SAM_AV1
//! - MF_SAM_AV2
//! \param[in] apduStyle Defines if the frames used for the communication between
//! the PCD and the PICC will be in DESfire Native mode or in ISO/IEC 7816-3 mode.
//! (See \ref T_DESFIRE_APDU_STYLE).
//! - APDU_NATIVE : Frames in DESfire Native style.
//! - APDU_WRAPPED : Frames in in ISO/IEC 7816-3 style.
//! \return Return a pointer to the initialised context. NULL if an error occured.
//! \sa \ref desfire_FreeContext
extern T_DESFIRE_CONTEXT* desfire_NewContextWithSAM(FILE* hSAM,
      T_MIFARE_SAM_MODE samMode, T_DESFIRE_APDU_STYLE apduStyle);

//! \brief Free a context.
//! \details The context and all data it contains will be deleted.
//! \param[in] pContext Pointer to the context to delete.
//! \remarks If the value of pointer is NULL, no operations will be performed.
//! \remarks After having deleted a context, it can be advised to set the pointer
//! value to NULL.
//! \sa \ref desfire_NewContext
extern void desfire_FreeContext(T_DESFIRE_CONTEXT *pContext);

//! @}

//! \addtogroup DesfireCommands
//! @{

//security level commands
//! \addtogroup DesfireSecurityLevel
//! @{

//! \brief Authentication between PCD en PICC using SAM
//! \details
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] ucCommand Authentication mode to use :
//! - AUTHENTICATE_LEGACY : For DES or 2K3DES with DESFire chaining mode (compliant EV0 and EV1)
//! - AUTHENTICATE_ISO : For DES, 2K3DES, 3K3DES with CBC chaining mode (compliant EV1)
//! - AUTHENTICATE_AES : For AES (compliant EV1)
//! \param[in] ucAuthMode Byte to set various options for SAM authentication
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 5</td><td>RFU</td></tr>
//! <tr><td>Bit 4</td><td>
//! - 0 : use AV1 compatibility mode key diversification methods
//! - 1 : use AV2 compatibility mode key diversification methods (make bit 3 ignored)</td></tr>
//! <tr><td>Bit 3</td><td>DES or 2K3DES key
//! - 0 : diversify using 2 encryption rounds
//! - 1 : diversify using 1 encryption rounds
//! .
//! 2K3DES and AES key
//! - RFU : Has to be set to 0</td></tr>
//! <tr><td>Bit 2</td><td> RFU : Has to be set to 0</td></tr>
//! <tr><td>Bit 1</td><td>
//! - 0 : key selection by SAM key entry number
//! - 1 : key selection by DESFire PICC key number</td></tr>
//! <tr><td>Bit 0</td><td>
//! - 0 : no key diversification
//! - 1 : key diversification with 8 or 16 bytes diversification input
//! </table>
//! \param[in] ucKeyNo Key entry. Can be either a SAM key number (0x00 to 0x7F)
//! or a DESFire key number (0x00 to 0x0D) according parameter ucAuthMode.
//! \param[in] ucKeyVersion Key version (0x00 to 0xFF).
//! \param[in] iDivInpLen Diversification input length
//! \param[in] pDivInp Diversification input.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_NewContextWithSAM, \ref desfire_NewContext, \ref desfire_Authenticate, \ref mifare_New3desKey, mifare_New3desKeyWithVersion,
//! \ref mifare_New3k3desKey, \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey,
//! \ref mifare_NewAesKeyWithVersion, \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion
extern int desfire_AuthenticateWithSAM(T_DESFIRE_CONTEXT *pContext,
      unsigned char ucCommand, unsigned char ucAuthMode, unsigned char ucKeyNo,
      unsigned char ucKeyVersion, int iDivInpLen, unsigned char *pDivInp);

//! \brief Authentication between PCD en PICC
//! \details This command detect the key type and chose the authentication
//! method (Native or Standard)\n
//! MIFARE DESFire EV1 and the reader device show in an encrypted way
//! that they have the same secret which especially means the same key.
//! This not only confirms that both entities are permitted to perform
//! operations on each other but also creates a session key which can be
//! used to keep the further communication path secure. As the name
//! session key implicitly indicates, each time a new authentication
//! procedure is successfully completed a new key for further cryptographic
//! operations is generated. <b>Compliant with MIFARE DESFire "EV0" for key types
//! DES or 3DES generated in native mode </b><br>
//! If the current context has been created in order to use SAM (\ref desfire_NewContextWithSAM),
//! This command will have the same effect than :
//! \code
//! desfire_AuthenticateWithSAM(pContext,AUTHENTICATE_LEGACY, 0x02, ucKeyNo, 0, 0, NULL );
//! \endcode
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] ucKeyNo Identify the key that the PICC shall use to encipher/deciper.
//! \param[in] pKey Pointer to the key that will be used to encipher/decipher
//! messages and to generate the session key. Key types standard DES, 3KDES or AES
//! will automatically call functions \ref desfire_AuthenticateIso or
//! \ref desfire_AuthenticateAes.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_NewContext, \ref mifare_New3desKey, mifare_New3desKeyWithVersion,
//! \ref mifare_New3k3desKey, \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey,
//! \ref mifare_NewAesKeyWithVersion, \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion
//! , \ref desfire_AuthenticateWithSAM, \ref desfire_NewContextWithSAM
extern int desfire_Authenticate(T_DESFIRE_CONTEXT *pContext,
      unsigned char ucKeyNo, T_MIFARE_KEY *pKey);

//! \brief Authentication between PCD en PICC using standard DES keys
//! \details Same purpose that \ref desfire_Authenticate but using CBC chaining and
//! enhanced features (i.e CMAC calculation, IV update even in Plain mode).
//! <b>Not compliant with DESFire "EV0"</b>.\n
//! If the current context has been created in order to use SAM (\ref desfire_NewContextWithSAM),
//! This command will have the same effect than :
//! \code
//! desfire_AuthenticateWithSAM(pContext,AUTHENTICATE_ISO, 0x02, ucKeyNo, 0, 0, NULL );
//! \endcode
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] ucKeyNo Identify the key that the PICC shall use to encipher/deciper.
//! \param[in] pKey Pointer to the key that will be used to encipher/decipher
//! messages and to generate the session key. The key shall be 3K3DES or DES generated
//! in standard mode (not native)
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_NewContext, \ref mifare_New3desKey, mifare_New3desKeyWithVersion,
//! \ref mifare_New3k3desKey, \ref mifare_New3k3desKeyWithVersion,
//! \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion
//! , \ref desfire_AuthenticateWithSAM, \ref desfire_NewContextWithSAM
extern int desfire_AuthenticateIso(T_DESFIRE_CONTEXT *pContext,
      unsigned char ucKeyNo, T_MIFARE_KEY *pKey);

//! \brief Authentication between PCD en PICC using standard AES keys
//! \details Same purpose that \ref desfire_Authenticate but with enhanced features
//! (i.e CMAC calculation, IV update even in Plain mode). <b>Not compliant with DESFire
//! "EV0".</b>\n
//! If the current context has been created in order to use SAM (\ref desfire_NewContextWithSAM),
//! This command will have the same effect than :
//! \code
//! desfire_AuthenticateWithSAM(pContext,AUTHENTICATE_AES, 0x02, ucKeyNo, 0, 0, NULL );
//! \endcode
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] ucKeyNo Identify the key that the PICC shall use to encipher/deciper.
//! \param[in] pKey Pointer to an AES key that will be used to encipher/decipher
//! messages and to generate the session key.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_NewContext, \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion
//! , \ref desfire_AuthenticateWithSAM, \ref desfire_NewContextWithSAM
extern int desfire_AuthenticateAes(T_DESFIRE_CONTEXT *pContext,
      unsigned char ucKeyNo, T_MIFARE_KEY *pKey);

//! \brief Changes the master key (MK) settings on PICC and application level
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] ucSettings
//! At PICC level :
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 4</td><td>Not Used</td></tr>
//! <tr><td>Bit 3</td><td>Codes whether a change of PICC master key settings is allowed
//! - 0 : configuration not changeable anymore (frozen)
//! - 1 : this configuration is changeable if authenticated with PICC Master Key (default setting)</td></tr>
//! <tr><td>Bit 2</td><td>Codes whether PICC master key authentication is needed before create/delete application
//! - 0 : Create or delete application is allowed only with PICC master key authentication
//! - 1 : Create application is permitted without PICC MK authentication (default setting). Delete application requires an authentication with PICC MK or application MK</td></tr>
//! <tr><td>Bit 1</td><td>Codes whether PICC master key authentication is needed for application directory access
//! - 0 : PICC MK Authentication required for \ref desfire_GetApplicationIds and \ref desfire_GetKeySettings
//! - 1 : \ref desfire_GetApplicationIds and \ref desfire_GetKeySettings commands succeed independently of processing a PICC MK authentication (default setting)</td></tr>
//! <tr><td>Bit 0</td><td>Codes whether PICC master key is changeable
//! - 0 : PICC Master Key not changeable anymore (frozen)
//! - 1 : PICC Master Key changeable(Authentication with current PICC MK necessary,default setting)</td></tr>
//! </table>
//! At Application level (selected AID is not 0x00):
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 4</td><td>Access rights for changing application keys (\ref desfire_ChangeKey command)
//! - 0x0 : Application master key (MK) authentication is necessary to change any key (default)
//! - 0x1 .. 0xD : Authentication with the specified key is necessary to change any key(default)
//! - 0xE : Authentication with the key to be changed (same Key N°) is necessary to change a key
//! - 0xF : All keys (except application MK, see bit 0) within the application are frozen</td></tr>
//! <tr><td>Bit 3</td><td>Codes whether a change of application master key settings is allowed
//! - 0 : configuration not changeable anymore (frozen)
//! - 1 : this configuration is changeable if authenticated with application MK (default setting)</td></tr>
//! <tr><td>Bit 2</td><td>Codes whether application master key authentication is needed before create/delete file
//! - 0 : Create or delete a file is allowed only with application MK authentication
//! - 1 : Create or delete a file is also allowed without application MK authentication</td></tr>
//! <tr><td>Bit 1</td><td>Codes whether application MK authentication is needed for file directory access
//! - 0 : Application MK Authentication required for \ref desfire_GetFileIds \ref desfire_GetKeySettings \ref desfire_GetFileSettings
//! - 1 : \ref desfire_GetFileIds \ref desfire_GetKeySettings \ref desfire_GetFileSettings commands succeed independently of processing a PICC MK authentication (default setting)</td></tr>
//! <tr><td>Bit 0</td><td>Codes whether application MK is changeable
//! - 0 : Application MK not changeable anymore (frozen)
//! - 1 : Application MK changeable(Authentication with current Application MK necessary,default setting)</td></tr>
//! </table>
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_GetKeySettings
extern int desfire_ChangeKeySettings(T_DESFIRE_CONTEXT *pContext,
      unsigned char ucSettings);

//! \brief Changes any key stored on the PICC using SAM
//! \details Generate the payload of the DESFire ChangeKey command with the SAM
//! and send the DESFire command with the generated payload to the PICC.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] ucKeyCompMeth Key compilation method (defines the method of key generation)
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 6</td><td>RFU</td></tr>
//! <tr><td>Bit 5</td><td>choice between AV1 and AV2 key diversification methods.
//! - 0 : diversify using AV1 compatibility mode key diversification methods.
//! - 1 : diversify using MIFARE SAM AV2 mode key diversification methods.</td></tr>
//! <tr><td>Bit 4</td><td>key diversification method for current key.
//! RFU if key entry is of type 3K3DES or AES or bit 5 is set to 1.
//! - 0 : diversify using 2 encryption method rounds.
//! - 1 : diversify using 1 encryption method rounds.</td></tr>
//! <tr><td>Bit 3</td><td>key diversification method for new key.
//! RFU if key entry is of type 3K3DES or AES or bit 5 is set to 1.
//! - 0 : diversify using 2 encryption method rounds.
//! - 1 : diversify using 1 encryption method rounds.</td></tr>
//! <tr><td>Bit 2</td><td>use of key diversification for current key.
//! - 0 : current key is not diversified.
//! - 1 : current key is already diversified.</td></tr>
//! <tr><td>Bit 1</td><td>use of key diversification for new key.
//! - 0 : current key is should not be diversified.
//! - 1 : current key is should be diversified.</td></tr>
//! <tr><td>Bit 0</td><td>role or involvement of ChangeKey key.
//! - 0 : If the ChangeKey key of the targeted application is 0x00 to 0x0D.
//! In this case both the old and the new key are involved in the calculation
//! of the deciphered key data.
//! - 1 : if the ChangeKey key of the targeted application is 0x0E or the master
//! (key 0x00) itself changed. In this case only the new key is involved ins the
//! calculation of the deciphered key data. The parameter ucOldSAMKeyNo is ignored
//! in this case.</td></tr>
//! </table>
//! \param[in] ucConfig Configuration
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 5</td><td>RFU</td></tr>
//! <tr><td>Bit 4</td><td>
//! - 0 : Any other key but not the DESFire card master key shall be changed</td></tr>
//! - 1 : the DESFire card master key shall be changed (the key type information
//! has to be included in the cryptogram)</td></tr>
//! <tr><td>Bit 3 - 0</td><td> number of the DESFire key to be changed</td></tr>
//! </table>
//! \param[in] ucKeyNo number of the DESFire key to be changed
//! \todo the ucConfig parameter may be deleted and generated automatically from ucKeyNo
//! \param[in] ucOldSAMKeyNo 1 byte unsigned SAM key entry holding the current key
//! (0x00 to 0x7F).
//! \param[in] ucOldSAMKeyVersion 1 byte unsigned key version of the current key
//! (0x00 to 0xFF)
//! \param[in] ucNewSAMKeyNo 1 byte unsigned SAM key entry holding the new key
//! (0x00 to 0x7F).
//! \param[in] ucNewSAMKeyVersion 1 byte unsigned key version of the new key
//! (0x00 to 0xFF)
//! \param[in] iDivInpLen Length of the diversification input parameter
//! \param[in] pDivInp Diversification input
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \remarks After a successful change of the key used on the current authentication,
//! the authentication will be invalidated. A new authentication with the new key will
//! be required for subsequent operations.
//! \warning Will not work if SAM is not used. The function \ref desfire_ChangeKey
//! shall be used instead.
//! \sa \ref mifare_New3desKey, mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey,
//! \ref mifare_NewAesKeyWithVersion, \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion
//! , \ref desfire_ChangeKeyWithSAM
extern int desfire_ChangeKeyWithSAM(T_DESFIRE_CONTEXT *pContext,
      unsigned char ucKeyCompMeth, unsigned char ucConfig,
      unsigned char ucKeyNo, unsigned char ucOldSAMKeyNo,
      unsigned char ucOldSAMKeyVersion, unsigned char ucNewSAMKeyNo,
      unsigned char ucNewSAMKeyVersion, int iDivInpLen, unsigned char *pDivInp);

//! \brief Changes any key stored on the PICC
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] ucKeyNo Identify the key to change.
//! \param[in] pNewKey New key to use.
//! \param[in] pOldKey Old key to change.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \remarks After a successful change of the key used on the current authentication,
//! the authentication will be invalidated. A new authentication with the new key will
//! be required for subsequent operations.
//! \warning Will not work if SAM is used. The function \ref desfire_ChangeKeyWithSAM
//! shall be used instead.
//! \sa \ref mifare_New3desKey, mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey,
//! \ref mifare_NewAesKeyWithVersion, \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion
//! , \ref desfire_ChangeKeyWithSAM
extern int desfire_ChangeKey(T_DESFIRE_CONTEXT *pContext,
      unsigned char ucKeyNo, T_MIFARE_KEY *pNewKey, T_MIFARE_KEY *pOldKey);

//! \brief Reads out the current key version of any key stored on the PICC
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] ucKeyNo Key number.
//! \param[out] pucVersion Version of the key.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref mifare_KeyGetVersion, \ref mifare_KeySetVersion
extern int desfire_GetKeyVersion(T_DESFIRE_CONTEXT *pContext,
      unsigned char ucKeyNo, unsigned char *pucVersion);

//! \brief Configures the card and pre-personalizes the card with a key, defines if
//! the UID or the random ID is sent back during communication setup and
//! configures the ATS string
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] ucOptions
//! - 0x00 : data is the configuration byte
//! - 0x01 : data is default key version and default key to use during application creation instead of key 0x00
//! - 0x02 : data is the user defined ATS
//! - others : Not used
//! \param[in] pucData Data part.\n
//! - If Option = 0x00 : Data shall be 1 byte long.
//!   - bit 0 = 0 : Format card enabled.
//!   - bit 0 = 1 : Format card disabled; cannot be reset.
//!   - bit 1 = 0 : Random ID disabled.
//!   - bit 1 = 1 : Random ID enabled; cannot be reset.
//!   .
//! - If Option = 0x01 : data is [key(24bytes)][key version(1byte)]. If the key is
//! shorter than 24 bytes, only left bytes will be used
//! - If Option = 0x02 : User defined ATS. Format is :
//! [TL(length on 1byte)][T0(1byte)][TA(1byte)][TB(1byte)][TC(1byte)][string (<16 bytes)]
//! padded with iso/iec 9797-1 method (0x80 then 0x00) + 2bytes CRC
//! \param[in] iDataLen Data field length.
//! \remarks Option 0x02 should only be carried out by experts. For this option, padding
//! is carried out with ISO/IEC 9797-1 padding method. For all other options, padding
//! is carried out with 0x00. For ATS longer than 16 bytes, please check the frame
//! size of all used readers, as a reader with frame size of 16 bytes could have
//! problems in the receipt of ATS.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_GetCardUID
extern int desfire_SetConfiguration(T_DESFIRE_CONTEXT *pContext,
      unsigned char ucOptions, unsigned char *pucData, int iDataLen);
//! @}

//card level commands
//! \addtogroup DesfirePICCLevel
//! @{

//! \brief Returns the UID
//! \details An authentication with any key needs to be performed before this command.
//! This command return the UID and gives the opportunity to retreive the UID even if
//! the random ID is used.
//! \param[in,out] pContext Pointer to the application context.
//! \param[out] pucUID Returned UID.
//! \param[out] piUidLength Size of the return UID. 0 if the command failed.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \remarks The UID can be 4, 7 or 10 bytes long.
//! \ref desfire_SetConfiguration
extern int desfire_GetCardUID(T_DESFIRE_CONTEXT *pContext,
      unsigned char *pucUID, int * piUidLength);

//! \brief Creates new applications on the PICC using \ref T_DESFIRE_AID for application identifier
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] pAid Pointer to the Application Identifier to use.
//! \param[in] ucSettings1 Application master key settings
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 4</td><td>Access rights for changing application keys (\ref desfire_ChangeKey command)
//! - 0x0 : Application master key (MK) authentication is necessary to change any key (default)
//! - 0x1 .. 0xD : Authentication with the specified key is necessary to change any key(default)
//! - 0xE : Authentication with the key to be changed (same Key N°) is necessary to change a key
//! - 0xF : All keys (except application MK, see bit 0) within the application are frozen</td></tr>
//! <tr><td>Bit 3</td><td>Codes whether a change of application master key settings is allowed
//! - 0 : configuration not changeable anymore (frozen)
//! - 1 : this configuration is changeable if authenticated with application MK (default setting)</td></tr>
//! <tr><td>Bit 2</td><td>Codes whether application master key authentication is needed before create/delete file
//! - 0 : Create or delete a file is allowed only with application MK authentication
//! - 1 : Create or delete a file is also allowed without application MK authentication</td></tr>
//! <tr><td>Bit 1</td><td>Codes whether application MK authentication is needed for file directory access
//! - 0 : Application MK Authentication required for \ref desfire_GetFileIds \ref desfire_GetKeySettings \ref desfire_GetFileSettings
//! - 1 : \ref desfire_GetFileIds \ref desfire_GetKeySettings \ref desfire_GetFileSettings commands succeed independently of processing a PICC MK authentication (default setting)</td></tr>
//! <tr><td>Bit 0</td><td>Codes whether application MK is changeable
//! - 0 : Application MK not changeable anymore (frozen)
//! - 1 : Application MK changeable(Authentication with current Application MK necessary,default setting)</td></tr>
//! </table>
//! \param[in] ucSettings2 Other settings
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 6</td><td>Indicates the crypto method of the application :
//! - '00' : specifies DES and 2K3DES operation for the whole application
//! - '01' : specifies 3K3DES operation for the whole application
//! - '10' : specifies AES operation for the whole application</td></tr>
//! <tr><td>Bit 5</td><td>Indicates use of 2 bytes ISO/IEC 7816-4 file identifier
//! for files within the application :
//! - 0 : 2 bytes iso file identifier for files within the application not supported
//! - 1 : 2 bytes iso file identifier for files within the application supported</td></tr>
//! <tr><td>Bit 4</td><td>RFU, has to be set to 0.
//! <tr><td>Bit 3 - 0</td><td>Number of keys that can be stored within the application
//! for cryptographic purposes. A maximum if 14 keys can be stored within the application.
//! It is possible to create an application with no key</td></tr>
//! </table>
//! \param[in] isoFileId (optional)ISO File ID. Used for ISO/IEC 7816-4 file systems.
//! The ISO FID will be used to select the application with the ISO SELECT command.\n
//! <b>bit 5 of ucSettings2 has to be set to 1</b>
//! \param[in] pcIsoFileName (optional)DF-Name used in 7816-4 mode in combination with
//! the ISO SELECT command. The length of this parameter can be from 1 to 16 bytes. This
//! parameter can be null even if an ISO FID is used\n
//! <b>bit 5 of ucSettings2 has to be set to 1</b>
//! \param[in] iIsoFileNameLen (optional)Length if the DF-Name\n
//! <b>bit 5 of ucSettings2 has to be set to 1</b>
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_SelectApplication, \ref desfire_DeleteApplication,
//! \ref desfire_GetApplicationIds
extern int desfire_CreateApplicationWithAid(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_AID *pAid, unsigned char ucSettings1,
      unsigned char ucSettings2, T_DESFIRE_ISO_FID isoFileId,
      char *pcIsoFileName, int iIsoFileNameLen);

//! \brief Creates new applications on the PICC using and interger as application identifier
//! \details Convert the interger AID into a \ref T_DESFIRE_AID and calls \ref desfire_CreateApplicationWithAid
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] iAid Application Identifier to use.
//! \param[in] ucSettings1 Application master key settings
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 4</td><td>Access rights for changing application keys (\ref desfire_ChangeKey command)
//! - 0x0 : Application master key (MK) authentication is necessary to change any key (default)
//! - 0x1 .. 0xD : Authentication with the specified key is necessary to change any key(default)
//! - 0xE : Authentication with the key to be changed (same Key N°) is necessary to change a key
//! - 0xF : All keys (except application MK, see bit 0) within the application are frozen</td></tr>
//! <tr><td>Bit 3</td><td>Codes whether a change of application master key settings is allowed
//! - 0 : configuration not changeable anymore (frozen)
//! - 1 : this configuration is changeable if authenticated with application MK (default setting)</td></tr>
//! <tr><td>Bit 2</td><td>Codes whether application master key authentication is needed before create/delete file
//! - 0 : Create or delete a file is allowed only with application MK authentication
//! - 1 : Create or delete a file is also allowed without application MK authentication</td></tr>
//! <tr><td>Bit 1</td><td>Codes whether application MK authentication is needed for file directory access
//! - 0 : Application MK Authentication required for \ref desfire_GetFileIds \ref desfire_GetKeySettings \ref desfire_GetFileSettings
//! - 1 : \ref desfire_GetFileIds \ref desfire_GetKeySettings \ref desfire_GetFileSettings commands succeed independently of processing a PICC MK authentication (default setting)</td></tr>
//! <tr><td>Bit 0</td><td>Codes whether application MK is changeable
//! - 0 : Application MK not changeable anymore (frozen)
//! - 1 : Application MK changeable(Authentication with current Application MK necessary,default setting)</td></tr>
//! </table>
//! \param[in] ucSettings2 Other settings
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 6</td><td>Indicates the crypto method of the application :
//! - '00' : specifies DES and 2K3DES operation for the whole application
//! - '01' : specifies 3K3DES operation for the whole application
//! - '10' : specifies AES operation for the whole application</td></tr>
//! <tr><td>Bit 5</td><td>Indicates use of 2 bytes ISO/IEC 7816-4 file identifier
//! for files within the application :
//! - 0 : 2 bytes iso file identifier for files within the application not supported
//! - 1 : 2 bytes iso file identifier for files within the application supported</td></tr>
//! <tr><td>Bit 4</td><td>RFU, has to be set to 0.
//! <tr><td>Bit 3 - 0</td><td>Number of keys that can be stored within the application
//! for cryptographic purposes. A maximum if 14 keys can be stored within the application.
//! It is possible to create an application with no key</td></tr>
//! </table>
//! \param[in] isoFileId (optional)ISO File ID. Used for ISO/IEC 7816-4 file systems.
//! The ISO FID will be used to select the application with the ISO SELECT command.\n
//! <b>bit 5 of ucSettings2 has to be set to 1</b>
//! \param[in] pcIsoFileName (optional)DF-Name used in 7816-4 mode in combination with
//! the ISO SELECT command. The length of this parameter can be from 1 to 16 bytes. This
//! parameter can be null even if an ISO FID is used\n
//! <b>bit 5 of ucSettings2 has to be set to 1</b>
//! \param[in] iIsoFileNameLen (optional)Length if the DF-Name\n
//! <b>bit 5 of ucSettings2 has to be set to 1</b>
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_SelectApplication, \ref desfire_DeleteApplication,
//! \ref desfire_GetApplicationIds
extern int desfire_CreateApplication(T_DESFIRE_CONTEXT *pContext, int iAid,
      unsigned char ucSettings1, unsigned char ucSettings2,
      T_DESFIRE_ISO_FID isoFileId, char *pcIsoFileName, int iIsoFileNameLen);

//! \brief Permanently deactivates an application from the PICC
//! \details The application ID is removed, therefore it is possible to create a
//! new application with the deleted application ID. All keys are overwritten with
//! random values. However, the deleted memory blocks can only be recovered by using
//! the \ref desfire_FormatPicc command which erases the whole user memory of the PICC.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] pAid Pointer to the Application Identifier to use.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \remarks Depending on the application master key settings, a preceding authentication
//! with the picc master key or  the application master key might be required.
//! \remarks Even if the PICC master key contains the default value 0 and the bit
//! \"free create/delete without the PICC master key" is set, it is necessary to be
//! either authenticated with the zero PICC master key or the respective application
//! master key.
//! \warning If the deleted application is the current application, the current
//! application becomes Picc level (AID 00 00 00) and the session key is destoyed.
//! In this case, a new authentication is necessary.
//! \sa \ref desfire_SelectApplication, \ref desfire_CreateApplication,
//! \ref desfire_GetApplicationIds
extern int desfire_DeleteApplication(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_AID *pAid);

//! \brief Return a list of application ID existing on the PICC
//! \param[in,out] pContext Pointer to the application context.
//! \param[out] tAids Array of application IDs.
//! \param[out] piCount Number of application on the PICC.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_SelectApplication, \ref desfire_CreateApplication,
//! \ref desfire_DeleteApplication
extern int desfire_GetApplicationIds(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_AID tAids[], int *piCount);

//! \brief Return the available free memory on the PICC
//! \details Depending on the PICC master key settings, a successful authentication
//! with the PICC master key might be required to execute this command.\n
//! This command require that the currently selected application AID is 0x000000
//! which references the card level.
//! \param[in,out] pContext Pointer to the application context.
//! \param[out] piSize Number bytes available on the PICC.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_FormatPicc
extern int desfire_FreeMem(T_DESFIRE_CONTEXT *pContext, unsigned int *piSize);

//! \brief Returns the ISO/IEC 7816-4 DF-Names of all active application on the PICC
//! \details Depending on the PICC master key settings, a successful authentication
//! with the PICC master key might be required to execute this command.\n
//! This command require that the currently selected application AID is 0x000000
//! which references the card level.
//! \param[in,out] pContext Pointer to the application context.
//! \param[out] tDfname Array of DF NAMES (See \ref T_DESFIRE_DFNAME).
//! \param[out] piCount Number of application on the PICC.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_CreateApplication
extern int desfire_GetDfNames(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_DFNAME tDfname[], int * piCount);

//! \brief Get the configuration information on the PICC and application
//! master key configuration settings. Also returns the maximum number of
//! keys which can be stored in the selected application
//! \param[in,out] pContext Pointer to the application context.
//! \param[out] pucSettings According the level (PICC and Application), contains
//! the key settings. See \ref desfire_ChangeKeySettings for setting details
//! \param[out] pucMaxKeys Maximum number of key. At application level, the 2
//! most significant bits specify if the key is DES/2K3DES, 3K3DES or AES
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa desfire_ChangeKeySettings
extern int desfire_GetKeySettings(T_DESFIRE_CONTEXT *pContext,
      unsigned char *pucSettings, unsigned char * pucMaxKeys);

//! \brief Select an application for further access.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] pAid Pointer to the Application Identifier to select.
//! \remarks The application 00 00 00 is the PICC level.
//! \warning After a selection invalidates the current authentication status. A
//! new authentication will be necessary for further operations.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_GetApplicationIds \ref desfire_CreateApplication
//! \ref desfire_DeleteApplication, \ref desfire_SelectApplication
extern int desfire_SelectApplicationWithAid(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_AID *pAid);

//! \brief Select an application for further access.
//! \details The function will convert the iAid interger parameter to an actual
//! AID (\ref T_DESFIRE_AID ) and call \ref desfire_SelectApplicationWithAid.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] iAid Application Identifier to select.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_GetApplicationIds \ref desfire_CreateApplication
//! \ref desfire_DeleteApplication, \ref desfire_SelectApplicationWithAid
extern int desfire_SelectApplication(T_DESFIRE_CONTEXT *pContext, int iAid);

//! \brief Releases the PICC user memory.
//! \details This command releases all allocated user memory on the PICC. All
//! applications are deleted and all files within those applications are deleted.
//! The memory is deleted.
//! \param[in,out] pContext Pointer to the application context.
//! \remarks The PICC master key and the PICC master key settings keep their currently
//! set values. they are not impacted by this command. The command can be disabled
//! using \ref desfire_SetConfiguration . <b>This command always requires a preceding
//! authentication with the PICC master key</b>
//! \warning This command cannot be rolled back.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_SetConfiguration, \ref desfire_FreeMem
extern int desfire_FormatPicc(T_DESFIRE_CONTEXT *pContext);

//! \brief Return manufactoring data related to the PICC
//! \param[in,out] pContext Pointer to the application context.
//! \param[out] pVersionInfo Manufactoring data. See \ref S_DESFIRE_VERSION_INFO.
//! \return Command status code or CLESS status code (0x00 if no error occured)
extern int desfire_GetVersion(T_DESFIRE_CONTEXT *pContext,
      struct S_DESFIRE_VERSION_INFO *pVersionInfo);

//! @}

//application level commands
//! \addtogroup DesfireApplicationLevel
//! @{

//! \brief Get the properties of a specific file.
//! The information provided by this command depends on the type of file which is
//! queried.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId Identifier of the file.
//! \param[out] pFileSettings Structure containing the file settings.
//! See \ref T_DESFIRE_FILE_SETTINGS
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_ChangeFileSettings, \ref T_DESFIRE_FILE_SETTINGS
extern int desfire_GetFileSettings(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, T_DESFIRE_FILE_SETTINGS *pFileSettings);

//! \brief Return a list of all file identifiers of all active files existing in
//! the currently selected application.
//! \param[in,out] pContext Pointer to the application context.
//! \param[out] tucFiles Array of file identifiers
//! \param[out] piCount Number of files in the selected application
//! \remarks Depending on the application master key settings, a preceding authentication
//! with the application master key might be required.
//! Each file id is coded on one byte and is in the range from 0x00 to 0x1F
//! Duplicated values are not possible as each file must have an unambiguous identifier.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_CreateValueFile, \ref desfire_CreateStdDataFile,
//! \ref desfire_CreateLinearRecordFile, \ref desfire_CreateCyclicRecordFile,
//! \ref desfire_CreateBackupDataFile, \ref desfire_DeleteFile, \ref desfire_GetIsoFileIds
extern int desfire_GetFileIds(T_DESFIRE_CONTEXT *pContext,
      unsigned char tucFiles[], int *piCount);

//! \brief Return a list of 2 bytes ISO/IEC 7816-4 File identifiers of
//! all active files within the currently selected application.
//! \param[in,out] pContext Pointer to the application context.
//! \param[out] tucFiles Array of ISO file identifiers
//! \param[out] piCount Number of ISO files in the selected application
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_CreateStdDataFile, \ref desfire_CreateBackupDataFile,
//! \ref desfire_CreateLinearRecordFile, \ref desfire_CreateCyclicRecordFile
extern int desfire_GetIsoFileIds(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_ISO_FID tucFiles[], int *piCount);

//! \brief Permanently deactivates a file within the currently selected application.
//! \details The operation of this command invalidates the file directory entry of the
//! specified file which means that the file can not be accessed anymode.
//! Allocated memory blocks associated with the deleted file are not set free.
//! The file identifier of the deleted file can be re-used to create a new file within
//! this application.
//! To release memory blocks for re-use, the whole PICC user NV-memory needs to
//! be erased using \ref desfire_FormatPicc command.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the file to deactivate in the current application.
//! \remarks Depending on the application master key settings, a preceding authentication
//! with the application master key might be required.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_CreateValueFile, \ref desfire_CreateStdDataFile,
//! \ref desfire_CreateLinearRecordFile, \ref desfire_CreateCyclicRecordFile,
//! \ref desfire_CreateBackupDataFile, \ref desfire_GetFileIds, \ref desfire_GetIsoFileIds
extern int
desfire_DeleteFile(T_DESFIRE_CONTEXT *pContext, T_DESFIRE_FID fileId);

//! \brief Create a file for the storage and manipulation of 32bits signed integer values
//! within an existing application on the PICC.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the file to create in the current application.
//! \param[in] ucComSettings Communication settings on one byte.
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 2</td><td>RFU.</td></tr>
//! <tr><td>Bit 1 - 0</td><td>Communication mode :
//! - 'X0' : Plain communication (\ref DCM_PLAIN)
//! - '01' : Plain communication secured by MACing (\ref DCM_MACED)
//! - '11' : Fully enciphered communication (\ref DCM_ENCIPHERED)</td></tr>
//! </table>
//! \param[in] uiAccessRights Specify the access rights for the new file on 2 bytes:
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 15 - 12</td><td>Read Access rights</td></tr>
//! <tr><td>Bit 11 - 8</td><td>Write Access rights</td></tr>
//! <tr><td>Bit 7 - 4</td><td>Read & Write Access rights</td></tr>
//! <tr><td>Bit 3 - 0</td><td>Change Access rights</td></tr>
//! </table>
//! For each of this mode, value from 0x0 to 0xD is the number of the key required
//! to access the file in the mode. 0xE means free access, 0xF means deny access.
//! \remarks Read is possible with a Read & Write access.
//! \remarks Write is possible with a Read & Write access.
//! \remarks If a file is accessed without a valid authentication but free access
//! is possible, the communication mode is forced to plain.
//! \param[in] iLowerLimit Lower limit which is valid for this file.
//! The lower limit marks the boundary which must not be passed by a debit calculation
//! on the current value. It can be a negative value.
//! \param[in] iUpperLimit Upped limit which is valid for this file.
//! The upper limit has to be higher than or equal to the lower limit, otherwise
//! an error message would be returned by the PICC and the file would not be created.
//! \param[in] iValue Specify the initial value of the value file. The upper and lower
//! limits are checked by the PICC. In case of inconsistency, the file is not
//! created and an error message is returned by the PICC.
//! \param[in] ucLimitedCreditEnabled Several options :
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 2</td><td>RFU.</td></tr>
//! <tr><td>Bit 1</td><td>Limited credit feature (see \ref desfire_LimitedCredit):
//! - 0 : Limited credit feature is disabled.
//! - 1 : Limited credit feature is enabled.
//! <tr><td>Bit 0</td><td>Free get value feature (see \ref desfire_GetValue):
//! - 0 : Free get value feature is disabled.
//! - 1 : Free get value feature is enabled.
//! </table>
//! \remarks Value files feature always the integrated backup mechanism. Therefore,
//! every access changing the value needs to be validated using \ref desfire_CommitTransaction
//! or invalidated using \ref desfire_AbortTransaction.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_DeleteFile, \ref desfire_CreateStdDataFile,
//! \ref desfire_CreateLinearRecordFile, \ref desfire_CreateCyclicRecordFile,
//! \ref desfire_CreateBackupDataFile, \ref desfire_GetFileIds, \ref desfire_GetIsoFileIds,
//! \ref desfire_CommitTransaction, \ref desfire_AbortTransaction
extern int desfire_CreateValueFile(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, unsigned char ucComSettings,
      unsigned int uiAccessRights, int iLowerLimit, int iUpperLimit,
      int iValue, unsigned char ucLimitedCreditEnabled);

//! \brief Create a file for the storage of plain unformatted user data within
//! an existing application on the PICC.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the file to create in the current application.
//! \param[in] iSOFileId (optional)ISO File identifier. The application has to be created with
//! the option enabling the use of ISO FID. Otherwise, the PICC will return an error
//! as it will not expect an ISO FID. <b>NULL means that the ISO FID will not be
//! used</b>
//! \param[in] ucComSettings Communication settings on one byte.
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 2</td><td>RFU.</td></tr>
//! <tr><td>Bit 1 - 0</td><td>Communication mode :
//! - 'X0' : Plain communication (\ref DCM_PLAIN)
//! - '01' : Plain communication secured by MACing (\ref DCM_MACED)
//! - '11' : Fully enciphered communication (\ref DCM_ENCIPHERED)</td></tr>
//! </table>
//! \param[in] uiAccessRights Specify the access rights for the new file on 2 bytes:
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 15 - 12</td><td>Read Access rights</td></tr>
//! <tr><td>Bit 11 - 8</td><td>Write Access rights</td></tr>
//! <tr><td>Bit 7 - 4</td><td>Read & Write Access rights</td></tr>
//! <tr><td>Bit 3 - 0</td><td>Change Access rights</td></tr>
//! </table>
//! For each of this mode, value from 0x0 to 0xD is the number of the key required
//! to access the file in the mode. 0xE means free access, 0xF means deny access.
//! \remarks Read is possible with a Read & Write access.
//! \remarks Write is possible with a Read & Write access.
//! \remarks If a file is accessed without a valid authentication but free access
//! is possible, the communication mode is forced to plain.
//! \param[in] uiFileSize specify the size of the file.
//! \remarks The PICC internally allocates NV-memory in  multiple of 32 bytes.
//! Therefore a file creation command with a file size parameter equal to 1 will
//! internally consume the same amount of NV-memory as the same command with a file
//! size parameter equal to 32, namely 32 bytes.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_DeleteFile, \ref desfire_CreateValueFile,
//! \ref desfire_CreateLinearRecordFile, \ref desfire_CreateCyclicRecordFile,
//! \ref desfire_CreateBackupDataFile, \ref desfire_GetFileIds, \ref desfire_GetIsoFileIds
extern int desfire_CreateStdDataFile(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, T_DESFIRE_ISO_FID iSOFileId,
      unsigned char ucComSettings, unsigned int uiAccessRights,
      unsigned int uiFileSize);

//! \brief Create a file for multiple storage of structural data, for example for
//! loyatly programs, within an existing application on the PICC. Once the file is
//! filled completely with data records, further writing to the file is not possible
//! unless it is cleared.
//! \details Linear Record Files feature always the integrated backup mechanism.
//! Therefore every access appending a record needs to be validated using the
//! \ref desfire_CommitTransaction or aborted using \ref desfire_AbortTransaction.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the file to create in the current application.
//! \param[in] iSOFileId (optional)ISO File identifier. The application has to be created with
//! the option enabling the use of ISO FID. Otherwise, the PICC will return an error
//! as it will not expect an ISO FID. <b>NULL means that the ISO FID will not be
//! used</b>
//! \param[in] ucComSettings Communication settings on one byte.
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 2</td><td>RFU.</td></tr>
//! <tr><td>Bit 1 - 0</td><td>Communication mode :
//! - 'X0' : Plain communication (\ref DCM_PLAIN)
//! - '01' : Plain communication secured by MACing (\ref DCM_MACED)
//! - '11' : Fully enciphered communication (\ref DCM_ENCIPHERED)</td></tr>
//! </table>
//! \param[in] uiAccessRights Specify the access rights for the new file on 2 bytes:
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 15 - 12</td><td>Read Access rights</td></tr>
//! <tr><td>Bit 11 - 8</td><td>Write Access rights</td></tr>
//! <tr><td>Bit 7 - 4</td><td>Read & Write Access rights</td></tr>
//! <tr><td>Bit 3 - 0</td><td>Change Access rights</td></tr>
//! </table>
//! For each of this mode, value from 0x0 to 0xD is the number of the key required
//! to access the file in the mode. 0xE means free access, 0xF means deny access.
//! \remarks Read is possible with a Read & Write access.
//! \remarks Write is possible with a Read & Write access.
//! \remarks If a file is accessed without a valid authentication but free access
//! is possible, the communication mode is forced to plain.
//! \param[in] uiRecordSize Size of a single record in bytes. This parameter has
//! to be in the range 0x000001 to 0xFFFFFF.
//! \param[in] uiMaxNumberOfRecords Number of records. This parameter has
//! to be in the range 0x000001 to 0xFFFFFF.
//! \remarks The entire file size in the PICC NV-memory is given by uiRecordSize * uiMaxNumberOfRecords
//! rounded to next multiple of 32.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_ClearRecordFile, \ref desfire_DeleteFile, \ref desfire_CreateValueFile,
//! \ref desfire_CreateStdDataFile, \ref desfire_CreateCyclicRecordFile,
//! \ref desfire_CreateBackupDataFile, \ref desfire_GetFileIds, \ref desfire_GetIsoFileIds,
//! \ref desfire_CommitTransaction, \ref desfire_AbortTransaction
extern int desfire_CreateLinearRecordFile(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, T_DESFIRE_ISO_FID iSOFileId,
      unsigned char ucComSettings, unsigned int uiAccessRights,
      unsigned int uiRecordSize, unsigned int uiMaxNumberOfRecords);

//! \brief Create a file for multiple storage of structural data, for example for
//! logging transactions, within an existing application on the PICC. Once the file is
//! filled completely with data records, the PICC automatically overwrites the oldest
//! record with the latest written one. This wrap is fully transparent for the PCD.
//! \details Linear Record Files feature always the integrated backup mechanism.
//! Therefore every access appending a record needs to be validated using the
//! \ref desfire_CommitTransaction or aborted using \ref desfire_AbortTransaction.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the file to create in the current application.
//! \param[in] iSOFileId (optional)ISO File identifier. The application has to be created with
//! the option enabling the use of ISO FID. Otherwise, the PICC will return an error
//! as it will not expect an ISO FID. <b>NULL means that the ISO FID will not be
//! used</b>
//! \param[in] ucComSettings Communication settings on one byte.
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 2</td><td>RFU.</td></tr>
//! <tr><td>Bit 1 - 0</td><td>Communication mode :
//! - 'X0' : Plain communication (\ref DCM_PLAIN)
//! - '01' : Plain communication secured by MACing (\ref DCM_MACED)
//! - '11' : Fully enciphered communication (\ref DCM_ENCIPHERED)</td></tr>
//! </table>
//! \param[in] uiAccessRights Specify the access rights for the new file on 2 bytes:
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 15 - 12</td><td>Read Access rights</td></tr>
//! <tr><td>Bit 11 - 8</td><td>Write Access rights</td></tr>
//! <tr><td>Bit 7 - 4</td><td>Read & Write Access rights</td></tr>
//! <tr><td>Bit 3 - 0</td><td>Change Access rights</td></tr>
//! </table>
//! For each of this mode, value from 0x0 to 0xD is the number of the key required
//! to access the file in the mode. 0xE means free access, 0xF means deny access.
//! \remarks Read is possible with a Read & Write access.
//! \remarks Write is possible with a Read & Write access.
//! \remarks If a file is accessed without a valid authentication but free access
//! is possible, the communication mode is forced to plain.
//! \param[in] uiRecordSize Size of a single record in bytes. This parameter has
//! to be in the range 0x000001 to 0xFFFFFF.
//! \param[in] uiMaxNumberOfRecords Number of records. This parameter has
//! to be in the range 0x000002 to 0xFFFFFF.
//! \remarks As the backup feature consumes one recored, the uiMaxNumberOfRecords
//! needs to be one larger than the application requires.
//! \remarks The entire file size in the PICC NV-memory is given by uiRecordSize * uiMaxNumberOfRecords
//! rounded to next multiple of 32.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_ClearRecordFile, \ref desfire_DeleteFile, \ref desfire_CreateValueFile,
//! \ref desfire_CreateStdDataFile, \ref desfire_CreateLinearRecordFile,
//! \ref desfire_CreateBackupDataFile, \ref desfire_GetFileIds, \ref desfire_GetIsoFileIds,
//! \ref desfire_CommitTransaction, \ref desfire_AbortTransaction
extern int desfire_CreateCyclicRecordFile(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, T_DESFIRE_ISO_FID iSOFileId,
      unsigned char ucComSettings, unsigned int uiAccessRights,
      unsigned int uiRecordSize, unsigned int uiMaxNumberOfRecords);

//! \brief Create a file for the storage of plain unformatted user data within
//! an existing application on the PICC, and additionally supporting the feature
//! of an integrated backup mechanism.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the file to create in the current application.
//! \param[in] iSOFileId (optional)ISO File identifier. The application has to be created with
//! the option enabling the use of ISO FID. Otherwise, the PICC will return an error
//! as it will not expect an ISO FID. <b>NULL means that the ISO FID will not be
//! used</b>
//! \param[in] ucComSettings Communication settings on one byte.
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 2</td><td>RFU.</td></tr>
//! <tr><td>Bit 1 - 0</td><td>Communication mode :
//! - 'X0' : Plain communication (\ref DCM_PLAIN)
//! - '01' : Plain communication secured by MACing (\ref DCM_MACED)
//! - '11' : Fully enciphered communication (\ref DCM_ENCIPHERED)</td></tr>
//! </table>
//! \param[in] uiAccessRights Specify the access rights for the new file on 2 bytes:
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 15 - 12</td><td>Read Access rights</td></tr>
//! <tr><td>Bit 11 - 8</td><td>Write Access rights</td></tr>
//! <tr><td>Bit 7 - 4</td><td>Read & Write Access rights</td></tr>
//! <tr><td>Bit 3 - 0</td><td>Change Access rights</td></tr>
//! </table>
//! For each of this mode, value from 0x0 to 0xD is the number of the key required
//! to access the file in the mode. 0xE means free access, 0xF means deny access.
//! \remarks Read is possible with a Read & Write access.
//! \remarks Write is possible with a Read & Write access.
//! \remarks If a file is accessed without a valid authentication but free access
//! is possible, the communication mode is forced to plain.
//! \param[in] uiFileSize specify the size of the file.
//! \remarks The PICC internally allocates NV-memory in  multiple of 32 bytes.
//! Therefore a file creation command with a file size parameter equal to 1 will
//! internally consume the same amount of NV-memory as the same command with a file
//! size parameter equal to 32, namely 32 bytes.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_DeleteFile, \ref desfire_CreateValueFile,
//! \ref desfire_CreateLinearRecordFile, \ref desfire_CreateCyclicRecordFile,
//! \ref desfire_CreateStdDataFile, \ref desfire_GetFileIds, \ref desfire_GetIsoFileIds,
//! \ref desfire_CommitTransaction, \ref desfire_AbortTransaction
extern int desfire_CreateBackupDataFile(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, T_DESFIRE_ISO_FID iSOFileId,
      unsigned char ucComSettings, unsigned int uiAccessRights,
      unsigned int uiFileSize);

//! \brief Change the access parameters of an existing file.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the file to manage.
//! \param[in] ucComSettings New communication settings :
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 7 - 2</td><td>RFU.</td></tr>
//! <tr><td>Bit 1 - 0</td><td>Communication mode :
//! - 'X0' : Plain communication (\ref DCM_PLAIN)
//! - '01' : Plain communication secured by MACing (\ref DCM_MACED)
//! - '11' : Fully enciphered communication (\ref DCM_ENCIPHERED)</td></tr>
//! </table>
//! \param[in] uiAccessRights New access rights :
//! <table><tr><th>Bits Value</th><th>Description</th></tr>
//! <tr><td>Bit 15 - 12</td><td>Read Access rights</td></tr>
//! <tr><td>Bit 11 - 8</td><td>Write Access rights</td></tr>
//! <tr><td>Bit 7 - 4</td><td>Read & Write Access rights</td></tr>
//! <tr><td>Bit 3 - 0</td><td>Change Access rights</td></tr>
//! </table>
//! For each of this mode, value from 0x0 to 0xD is the number of the key required
//! to access the file in the mode. 0xE means free access, 0xF means deny access.
//! \remarks Read is possible with a Read & Write access.
//! \remarks Write is possible with a Read & Write access.
//! \remarks If a file is accessed without a valid authentication but free access
//! is possible, the communication mode is forced to plain.
//! \remarks This change only succeeds if the current access rights for \"change
//! access rights\" is different from \"never\".
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_GetFileSettings
extern int desfire_ChangeFileSettings(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, unsigned char ucComSettings,
      unsigned int uiAccessRights);
//! @}

//Data level commands
//! \addtogroup DesfireDataLevel
//! @{

//! \brief Read data from a Standard data file or a Backup data file.
//! \details The read command requires a preceding authentication either
//! with the key specified for \"Read\" or \"Read & Write\" access. \n
//! This function send a first command to the PICC to get the communication
//! settings of the file (see \ref desfire_GetFileSettings), then the read command.
//! Depending on the communication settings of the file, data will be sent
//! by the PICC either in plain, MACed or enciphered.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the file to read.
//! \param[in] ulOffset Position where the read operation has to start.
//! This parameter has to be in the range 0x000000 to file size -1.
//! \param[in] ulDataToReadLen Number of bytes to be read.
//! This parameter has to be in the range 0x000000 to 0xFFFFFF. If this
//! parameter is set to 0x000000, the entire data file is read starting to
//! the position specified in the offset value.
//! \param[out] pulDataReadLen Pointer to an unsigned long which will receive the
//! number of bytes read. Useful when ulDataToReadLen parameter has been set to 0.
//! \param[out] pData Pointer to a buffer which will receive the data read.
//! \remarks If a Backup data file is read after writing to it, but before
//! the \"commit transaction\" has been performed, the data read will be the
//! old unchanged data stored in the PICC. All data written to a backup data file
//! is validated and readable only after a \"commit transaction\" command.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \warning The buffer pData shall be big enough to receive the data read. In most case,
//! the size of pData shall be at least equal to uLength but if uLength is equal to 0,
//! the whole file will be read so pData shall have at least the same size than the
//! file which is read.
//! \sa \ref desfire_ReadDataCS, \ref desfire_WriteData, \ref desfire_WriteDataCS, \ref
//! desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_Credit, \ref desfire_CreditCS, \ref
//! desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCredit, \ref desfire_LimitedCreditCS
//! desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS,
//! \ref desfire_ClearRecordFile, \ref desfire_CommitTransaction, \ref desfire_AbortTransaction
extern int desfire_ReadData(T_DESFIRE_CONTEXT *pContext, T_DESFIRE_FID fileId,
      unsigned long ulOffset, unsigned long ulDataToReadLen,
      unsigned long* pulDataReadLen, void *pData);

//! \brief Read data from a Standard data file or a Backup data file.
//! \details The read command requires a preceding authentication either
//! with the key specified for \"Read\" or \"Read & Write\" access. \n
//! Depending on the communication settings defined in parameter, data will be sent
//! by the PICC either in plain, MACed or enciphered only if the defined communication
//! settings is compliant with the communication settings of the file.
//! \remarks This command can be use instead of \ref desfire_ReadData to avoid
//! the \"get file settings\" command send by the \ref desfire_ReadData command.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the file to read.
//! \param[in] ulOffset Position where the read operation has to start.
//! This parameter has to be in the range 0x000000 to file size -1.
//! \param[in] ulDataToReadLen Number of bytes to be read.
//! This parameter has to be in the range 0x000000 to 0xFFFFFF. If this
//! parameter is set to 0x000000, the entire data file is read starting to
//! the position specified in the offset value.
//! \param[out] pulDataReadLen Pointer to an unsigned long which will receive the
//! number of bytes read. Useful when ulDataToReadLen parameter has been set to 0.
//! \param[out] pData Pointer to a buffer which will receive the data read.
//! \remarks If a Backup data file is read after writing to it, but before
//! the \"commit transaction\" has been performed, the data read will be the
//! old unchanged data stored in the PICC. All data written to a backup data file
//! is validated and readable only after a \"commit transaction\" command.
//! \param[in] iCommSettings Communication settings to use :
//! - \ref DCM_PLAIN
//! - \ref DCM_MACED
//! - \ref DCM_ENCIPHERED
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \warning The buffer pData shall be big enough to receive the data read. In most case,
//! the size of pData shall be at least equal to uLength but if uLength is equal to 0,
//! the whole file will be read so pData shall have at least the same size than the
//! file which is read.
//! \sa \ref desfire_ReadData, \ref desfire_WriteData, \ref desfire_WriteDataCS, \ref
//! desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_Credit, \ref desfire_CreditCS, \ref
//! desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCredit, \ref desfire_LimitedCreditCS
//! desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS,
//! \ref desfire_ClearRecordFile, \ref desfire_CommitTransaction, \ref desfire_AbortTransaction
extern int desfire_ReadDataCS(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, unsigned long ulOffset,
      unsigned long ulDataToReadLen, unsigned long* pulDataReadLen,
      void *pData, int iCommSettings);

//! \brief Write data in a Standard data file or a Backup data file.
//! \details The write command requires a preceding authentication either
//! with the key specified for \"Write\" or \"Read & Write\" access. \n
//! This function send a first command to the PICC to get the communication
//! settings of the file (see \ref desfire_GetFileSettings), then the write command.
//! Depending on the communication settings of the file, data will be sent
//! by the PICC either in plain, MACed or enciphered.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the file where the data will be written.
//! \param[in] ulOffset Position where the write operation has to start.
//! This parameter has to be in the range 0x000000 to file size -1.
//! \param[in] ulLength Number of bytes to be written.
//! This parameter has to be in the range 0x000001 to 0xFFFFFF.
//! \param[in] pData Pointer to a buffer containing the data to write.
//! \remarks If the data is written in a Backup data file, it is necessary to
//! validate the written data with a \"commit transaction\" command. An
//! \"abort transaction\" command will invalidates the changes.\n
//! If data is written to a standard data file (without integrated backup mechanism),
//! data is directly programmed into the visible NV-memory of the file. The new data
//! is immediately available to any following \"read data\" command performed on
//! that file.
//! \remarks In case of MACed or enciphered communication, the validity of data
//! is verified by the PICC by checking the MAC or the CRC (including necessary
//! padding bytes) which is transmitted at the end of the data frame. if the
//! verification fails (MAC or CRC does not fit data, padding bytes invali), the
//! PICC stops further NV-programming and returns an integrity error (\ref DESFIRE_INTEGRITY_ERROR)
//! to the PCD. As a consequence of the integrity error, any transaction which might
//! have begun is automatically aborted.
//! \remarks In case of MACing, the padding data bytes are only used for cryptographic
//! purpose but not exchanged between PCD and PICC.
//! \remarks If the communication mode is enciphered but the file is configured for
//! free access, then the communication is either in plain (authenticate with a DES
//! or 2K3DES key in native mode) or CMACed (authentication with a DES or 2K3DES key in
//! standard mode or 3K3DES or AES key).
//! \warning Getting an integrity error when writting to a standard data file
//! can corrupt the content of the file.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteDataCS, \ref
//! desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_Credit, \ref desfire_CreditCS, \ref
//! desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCredit, \ref desfire_LimitedCreditCS
//! desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS,
//! \ref desfire_ClearRecordFile, \ref desfire_CommitTransaction, \ref desfire_AbortTransaction
extern int desfire_WriteData(T_DESFIRE_CONTEXT *pContext, T_DESFIRE_FID fileId,
      unsigned long ulOffset, unsigned long ulLength, void *pData);

//! \brief Write data in a Standard data file or a Backup data file.
//! \details The write command requires a preceding authentication either
//! with the key specified for \"Write\" or \"Read & Write\" access. \n
//! Depending on the communication settings defined in parameter, data will be sent
//! by the PCD either in plain, MACed or enciphered. The defined communication
//! settings has to be compliant with the communication settings of the file, otherwise,
//! the PICC will return an error.
//! \remarks This command can be use instead of \ref desfire_WriteData to avoid
//! the \"get file settings\" command send by the \ref desfire_WriteData command.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the file where the data will be written.
//! \param[in] ulOffset Position where the write operation has to start.
//! This parameter has to be in the range 0x000000 to file size -1.
//! \param[in] ulLength Number of bytes to be written.
//! This parameter has to be in the range 0x000001 to 0xFFFFFF.
//! \param[in] pData Pointer to a buffer containing the data to write.
//! \param[in] iCommSettings Communication settings to use :
//! - \ref DCM_PLAIN
//! - \ref DCM_MACED
//! - \ref DCM_ENCIPHERED
//! \remarks If the data is written in a Backup data file, it is necessary to
//! validate the written data with a \"commit transaction\" command. An
//! \"abort transaction\" command will invalidates the changes.\n
//! If data is written to a standard data file (without integrated backup mechanism),
//! data is directly programmed into the visible NV-memory of the file. The new data
//! is immediately available to any following \"read data\" command performed on
//! that file.
//! \remarks In case of MACed or enciphered communication, the validity of data
//! is verified by the PICC by checking the MAC or the CRC (including necessary
//! padding bytes) which is transmitted at the end of the data frame. if the
//! verification fails (MAC or CRC does not fit data, padding bytes invali), the
//! PICC stops further NV-programming and returns an integrity error (\ref DESFIRE_INTEGRITY_ERROR)
//! to the PCD. As a consequence of the integrity error, any transaction which might
//! have begun is automatically aborted.
//! \remarks In case of MACing, the padding data bytes are only used for cryptographic
//! purpose but not exchanged between PCD and PICC.
//! \remarks If the communication mode is enciphered but the file is configured for
//! free access, then the communication is either in plain (authenticate with a DES
//! or 2K3DES key in native mode) or CMACed (authentication with a DES or 2K3DES key in
//! standard mode or 3K3DES or AES key).
//! \warning Getting an integrity error when writting to a standard data file
//! can corrupt the content of the file.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteDataCS, \ref
//! desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_Credit, \ref desfire_CreditCS, \ref
//! desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCredit, \ref desfire_LimitedCreditCS
//! desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS,
//! \ref desfire_ClearRecordFile, \ref desfire_CommitTransaction, \ref desfire_AbortTransaction
extern int desfire_WriteDataCS(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, unsigned long ulOffset, unsigned long ulLength,
      void *pData, int iCommSettings);

//! \brief Read the current stored value from a value file.
//! \details The \"get value\" command requires a preceding authentication either
//! with the key specified for \"Read\" or \"Read & Write\" access. \n
//! This function send a first command to the PICC to get the communication
//! settings of the file (see \ref desfire_GetFileSettings), then the get value command.
//! Depending on the communication settings of the file, data will be sent
//! by the PICC either in plain, MACed or enciphered.\n
//! After updating a value file's value but before issuing the \"commit transaction\"
//! command, the \"get value\" command will always retreive the old unchanged value
//! which is still the valid one.\n
//! If \"get free value\" option is enabled at the file creation, then the communication
//! mode is plain (authenticate with a DES or 2K3DES key in native mode) or CMACed
//! (authentication with a DES or 2K3DES key in standard mode or 3K3DES or AES key).
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the value file.
//! \param[out] piValue Value read in the value file.
//! \remarks Depending on the option parameter in the \ref desfire_CreateValueFile
//! command, the command \"get value\" can access freely to the value file.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteData, \ref
//! desfire_WriteDataCS, \ref desfire_GetValueCS, \ref desfire_Credit, \ref desfire_CreditCS, \ref
//! desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCredit, \ref desfire_LimitedCreditCS
//! desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS,
//! \ref desfire_ClearRecordFile, \ref desfire_CommitTransaction, \ref desfire_AbortTransaction
extern int desfire_GetValue(T_DESFIRE_CONTEXT *pContext, T_DESFIRE_FID fileId,
      int *piValue);

//! \brief Read the current stored value from a value file.
//! \details The \"get value\" command requires a preceding authentication either
//! with the key specified for \"Read\" or \"Read & Write\" access. \n
//! Depending on the communication settings defined in parameter, data will be sent
//! by the PICC either in plain, MACed or enciphered only if the defined communication
//! settings is compliant with the communication settings of the file.\n
//! After updating a value file's value but before issuing the \"commit transaction\"
//! command, the \"get value\" command will always retreive the old unchanged value
//! which is still the valid one.\n
//! If \"get free value\" option is enabled at the file creation, then the communication
//! mode is plain (authenticate with a DES or 2K3DES key in native mode) or CMACed
//! (authentication with a DES or 2K3DES key in standard mode or 3K3DES or AES key).
//! \remarks This command can be use instead of \ref desfire_GetValue to avoid
//! the \"get file settings\" command send by the \ref desfire_GetValue command.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the value file.
//! \param[out] piValue Value read in the value file.
//! \param[in] iComSettings Communication settings to use :
//! - \ref DCM_PLAIN
//! - \ref DCM_MACED
//! - \ref DCM_ENCIPHERED
//! \remarks Depending on the option parameter in the \ref desfire_CreateValueFile
//! command, the command \"get value\" can access freely to the value file.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteData, \ref
//! desfire_WriteDataCS, \ref desfire_GetValue, \ref desfire_Credit, \ref desfire_CreditCS, \ref
//! desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCredit, \ref desfire_LimitedCreditCS
//! desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS,
//! \ref desfire_ClearRecordFile, \ref desfire_CommitTransaction, \ref desfire_AbortTransaction
extern int desfire_GetValueCS(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, int *piValue, int iComSettings);

//! \brief Increase a value stored in a value file.
//! \details The \"credit\" command requires a preceding authentication either
//! with the key specified for \"Read & Write\" access. \n
//! This function send a first command to the PICC to get the communication
//! settings of the file (see \ref desfire_GetFileSettings), then the credit command.
//! Depending on the communication settings of the file, data will be sent
//! by the PICC either in plain, MACed or enciphered.\n
//! It is necessary to validate the written data with a \"commit transaction\"
//! command. An \"abort transaction\" command will invalidates the changes. \n
//! The value modifications of credit, debit or limited credit commands are cumulated
//! until a \"commit transaction\" command is performed. Credit command NEVER
//! modify the limited credit value of a value file. However, if the limited credit
//! value needs to be set to 0, a limited credit with value 0 can be used.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the value file.
//! \param[in] iAmount Amount to be credited in the current stored value.\n
//! Although the parameter is a signed integer, only positive value are allowed
//! for the credit command.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteData, \ref
//! desfire_WriteDataCS, \ref desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_CreditCS, \ref
//! desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCredit, \ref desfire_LimitedCreditCS,
//! \ref desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS
extern int desfire_Credit(T_DESFIRE_CONTEXT *pContext, T_DESFIRE_FID fileId,
      int iAmount);

//! \brief Increase a value stored in a value file.
//! \details The \"credit\" command requires a preceding authentication either
//! with the key specified for \"Read & Write\" access. \n
//! Depending on the communication settings defined in parameter, data will be sent
//! by the PICC either in plain, MACed or enciphered only if the defined communication
//! settings is compliant with the communication settings of the file.\n
//! It is necessary to validate the written data with a \"commit transaction\"
//! command. An \"abort transaction\" command will invalidates the changes. \n
//! The value modifications of credit, debit or limited credit commands are cumulated
//! until a \"commit transaction\" command is performed. Credit command NEVER
//! modify the limited credit value of a value file. However, if the limited credit
//! value needs to be set to 0, a limited credit with value 0 can be used.
//! \remarks This command can be use instead of \ref desfire_Credit to avoid
//! the \"get file settings\" command send by the \ref desfire_Credit command.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the value file.
//! \param[in] iAmount Amount to be credited in the current stored value.\n
//! Although the parameter is a signed integer, only positive value are allowed
//! for the credit command.
//! \param[in] iComSettings Communication settings to use :
//! - \ref DCM_PLAIN
//! - \ref DCM_MACED
//! - \ref DCM_ENCIPHERED
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \remarks This command can be use instead of \ref desfire_Credit to avoid
//! the \"get file settings\" command send by the \ref desfire_Credit command.
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteData, \ref
//! desfire_WriteDataCS, \ref desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_Credit, \ref
//! desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCredit, \ref desfire_LimitedCreditCS,
//! \ref desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS
extern int desfire_CreditCS(T_DESFIRE_CONTEXT *pContext, T_DESFIRE_FID fileId,
      int iAmount, int iComSettings);

//! \brief Decrease a value stored in a value file.
//! \details The \"debit\" command requires a preceding authentication either
//! with the key specified for \"Read & Write\" access. \n
//! This function send a first command to the PICC to get the communication
//! settings of the file (see \ref desfire_GetFileSettings), then the debit command.
//! Depending on the communication settings of the file, data will be sent
//! by the PICC either in plain, MACed or enciphered.\n
//! It is necessary to validate the written data with a \"commit transaction\"
//! command. An \"abort transaction\" command will invalidates the changes. \n
//! The value modifications of credit, debit or limited credit commands are cumulated
//! until a \"commit transaction\" command is performed.\n
//! If the usage of \"limited credit\" feature is enabled, the new limit for subsequent
//! \"limited credit\" command is set to the sum of \"debit\" commands within one
//! transaction before issuing a \"commit transaction\" command. This assures that a
//! \"limited credit\" command can not re-book more values than a debiting transaction
//! deduced before.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the value file.
//! \param[in] iAmount Amount to be debited in the current stored value.\n
//! Although the parameter is a signed integer, only positive value are allowed
//! for the debit command.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteData, \ref
//! desfire_WriteDataCS, \ref desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_Credit, \ref
//! desfire_CreditCS, \ref desfire_DebitCS, \ref desfire_LimitedCredit, \ref desfire_LimitedCreditCS,
//! \ref desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS
extern int desfire_Debit(T_DESFIRE_CONTEXT *pContext, T_DESFIRE_FID fileId,
      int iAmount);

//! \brief Decrease a value stored in a value file.
//! \details The \"debit\" command requires a preceding authentication either
//! with the key specified for \"Read & Write\" access. \n
//! Depending on the communication settings defined in parameter, data will be sent
//! by the PICC either in plain, MACed or enciphered only if the defined communication
//! settings is compliant with the communication settings of the file.\n
//! It is necessary to validate the written data with a \"commit transaction\"
//! command. An \"abort transaction\" command will invalidates the changes. \n
//! The value modifications of credit, debit or limited credit commands are cumulated
//! until a \"commit transaction\" command is performed.\n
//! If the usage of \"limited credit\" feature is enabled, the new limit for subsequent
//! \"limited credit\" command is set to the sum of \"debit\" commands within one
//! transaction before issuing a \"commit transaction\" command. This assures that a
//! \"limited credit\" command can not re-book more values than a debiting transaction
//! deduced before.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the value file.
//! \param[in] iAmount Amount to be debited in the current stored value.\n
//! Although the parameter is a signed integer, only positive value are allowed
//! for the debit command.
//! \param[in] iComSettings Communication settings to use :
//! - \ref DCM_PLAIN
//! - \ref DCM_MACED
//! - \ref DCM_ENCIPHERED
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \remarks This command can be use instead of \ref desfire_Credit to avoid
//! the \"get file settings\" command send by the \ref desfire_Credit command.
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteData, \ref
//! desfire_WriteDataCS, \ref desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_Credit, \ref
//! desfire_CreditCS, \ref desfire_Debit, \ref desfire_LimitedCredit, \ref desfire_LimitedCreditCS,
//! \ref desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS
extern int desfire_DebitCS(T_DESFIRE_CONTEXT *pContext, T_DESFIRE_FID fileId,
      int iAmount, int iComSettings);

//! \brief Increase a value stored in a value file without having full
//! Read & Write permissions to the file.
//! \details This feature is enabled or disabled during value file creation. \n
//! This function send a first command to the PICC to get the communication
//! settings of the file (see \ref desfire_GetFileSettings), then the limited credit command.
//! Depending on the communication settings of the file, data will be sent
//! by the PICC either in plain, MACed or enciphered.\n
//! It is necessary to validate the written data with a \"commit transaction\"
//! command. An \"abort transaction\" command will invalidates the changes. \n
//! The value modifications of credit, debit or limited credit commands are cumulated
//! until a \"commit transaction\" command is performed.\n
//! The value of \"limited credit\" is limited to the sum of the \"debit\" commands
//! on this value file within the most recent transaction containing at least on debit.
//! After executing the \"limited credit\" command, the new limit is set to 0 regardless
//! of the amout which has been re-booked. Therefore the \"limited credit\" command
//! can be used once after a debit transaction.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the value file.
//! \param[in] iAmount Amount to be credited in the current stored value.\n
//! Although the parameter is a signed integer, only positive value are allowed
//! for the limited credit command.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteData, \ref
//! desfire_WriteDataCS, \ref desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_Credit, \ref
//! desfire_CreditCS, \ref desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCreditCS,
//! \ref desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS
extern int desfire_LimitedCredit(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, int iAmount);

//! \brief Increase a value stored in a value file without having full
//! Read & Write permissions to the file.
//! \details This feature is enabled or disabled during value file creation. \n
//! Depending on the communication settings defined in parameter, data will be sent
//! by the PICC either in plain, MACed or enciphered only if the defined communication
//! settings is compliant with the communication settings of the file.\n
//! It is necessary to validate the written data with a \"commit transaction\"
//! command. An \"abort transaction\" command will invalidates the changes. \n
//! The value modifications of credit, debit or limited credit commands are cumulated
//! until a \"commit transaction\" command is performed.\n
//! The value of \"limited credit\" is limited to the sum of the \"debit\" commands
//! on this value file within the most recent transaction containing at least on debit.
//! After executing the \"limited credit\" command, the new limit is set to 0 regardless
//! of the amout which has been re-booked. Therefore the \"limited credit\" command
//! can be used once after a debit transaction.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the value file.
//! \param[in] iAmount Amount to be credited in the current stored value.\n
//! Although the parameter is a signed integer, only positive value are allowed
//! for the limited credit command.
//! \param[in] iComSettings Communication settings to use :
//! - \ref DCM_PLAIN
//! - \ref DCM_MACED
//! - \ref DCM_ENCIPHERED
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteData, \ref
//! desfire_WriteDataCS, \ref desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_Credit, \ref
//! desfire_CreditCS, \ref desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCredit,
//! \ref desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS
extern int desfire_LimitedCreditCS(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, int iAmount, int iComSettings);

//! \brief Write a data to a record in a cyclic or linear record file.
//! \details This function send a first command to the PICC to get the communication
//! settings of the file (see \ref desfire_GetFileSettings), then the write record command.
//! Depending on the communication settings of the file, data will be sent
//! by the PICC either in plain, MACed or enciphered.\n
//! The wite record command appends one record at the end of a linear record file.
//! it erases and overwrites the oldest record in case of a cyclic record file if
//! it is already full. The entire new record is clear before data is written to it.\n
//! If no \"commit transaction\" command is sent after a \"write record\" command, the
//! next \"write record\" command to the same file writes to the already created record.
//! After sending a \"commit transaction\" command, a new \"write record\" command
//! will create a new record in the record file. An \"abort transaction\"
//! command will invalidates the changes.\n
//! After issuing a \"clear record\" command, but before a \"commit/abort transaction\"
//! command, a \"write record\" command to the same file will fail.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the value file.
//! \param[in] ulOffset Position where the write operation has to start.
//! This parameter has to be in the range 0x000000 to file size -1.
//! \param[in] ulLength Number of bytes to be written.
//! This parameter has to be in the range 0x000001 to 0xFFFFFF.
//! \param[in] pData Pointer to a buffer containing the data to write.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteData, \ref
//! desfire_WriteDataCS, \ref desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_Credit, \ref
//! desfire_CreditCS, \ref desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCredit,
//! \ref desfire_LimitedCreditCS, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS
extern int desfire_WriteRecord(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, unsigned long ulOffset, unsigned long ulLength,
      void *pData);

//! \brief Write a data to a record in a cyclic or linear record file.
//! \details Depending on the communication settings defined in parameter, data will be sent
//! by the PICC either in plain, MACed or enciphered only if the defined communication
//! settings is compliant with the communication settings of the file.\n
//! The wite record command appends one record at the end of a linear record file.
//! it erases and overwrites the oldest record in case of a cyclic record file if
//! it is already full. The entire new record is clear before data is written to it.\n
//! If no \"commit transaction\" command is sent after a \"write record\" command, the
//! next \"write record\" command to the same file writes to the already created record.
//! After sending a \"commit transaction\" command, a new \"write record\" command
//! will create a new record in the record file. An \"abort transaction\"
//! command will invalidates the changes.\n
//! After issuing a \"clear record\" command, but before a \"commit/abort transaction\"
//! command, a \"write record\" command to the same file will fail.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the value file.
//! \param[in] ulOffset Position where the write operation has to start.
//! This parameter has to be in the range 0x000000 to file size -1.
//! \param[in] ulLength Number of bytes to be written.
//! This parameter has to be in the range 0x000001 to 0xFFFFFF.
//! \param[in] pData Pointer to a buffer containing the data to write.
//! \param[in] iComSettings Communication settings to use :
//! - \ref DCM_PLAIN
//! - \ref DCM_MACED
//! - \ref DCM_ENCIPHERED
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteData, \ref
//! desfire_WriteDataCS, \ref desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_Credit, \ref
//! desfire_CreditCS, \ref desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCredit,
//! \ref desfire_LimitedCreditCS, \ref desfire_WriteRecord, \ref desfire_ReadRecords, \ref desfire_ReadRecordsCS
extern int desfire_WriteRecordCS(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, unsigned long ulOffset, unsigned long ulLength,
      void *pData, int iComSettings);

//! \brief Read out a set of complete records from a cyclic or linear record file.
//! \details The \"read records\" command requires a preceding authentication either
//! with the key specified for \"Read\" or \"Read & Write\" access. \n
//! This function send a first command to the PICC to get the communication
//! settings of the file (see \ref desfire_GetFileSettings), then the read record command.
//! Depending on the communication settings of the file, data will be sent
//! by the PICC either in plain, MACed or enciphered.\n
//! A \"read records\" command on an empty record file (directly after creation
//! or after a commited clearance) will return in an error.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the value file.
//! \param[in] ulOffset Offset of the newest record which is read out. In case
//! of 0x000000 the latest record is read out. The offset value must be in range
//! from 0x000000 to number of existing records -1.
//! \param[in] ulDataToReadLen Number of records to be read from the PICC. Records are
//! are always transmitted by the PICC in chronological order (=starting with the oldest,
//! which is number of records -1 before the one adressed by the given offset).
//! If this parameter is set to 0x000000 then all records, from the oldest record
//! up to and including the newest record (given by the offset parameter) are read.\n
//! The allowed range for the number of records parameter is from 0x000000 to
//! number of existing records - offset.
//! \param[out] pulDataReadLen Pointer to an unsigned long which will receive the
//! number of bytes read. Useful when ulDataToReadLen parameter has been set to 0.
//! \param[out] pData Pointer to a buffer which will receive the data read.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \remarks In cyclic record files the maximum number of stored valid records is
//! one less than the number of records specified in the \"create cyclic record file\"
//! command.
//! \warning The buffer pData shall be big enough to receive the data read. In most case,
//! the size of pData shall be at least equal to uLength but if uLength is equal to 0,
//! the whole file will be read so pData shall have at least the same size than the
//! file which is read.
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteData, \ref
//! desfire_WriteDataCS, \ref desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_Credit, \ref
//! desfire_CreditCS, \ref desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCredit,
//! \ref desfire_LimitedCreditCS, \ref desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecordsCS
extern int
desfire_ReadRecords(T_DESFIRE_CONTEXT *pContext, T_DESFIRE_FID fileId,
      unsigned long ulOffset, unsigned long ulDataToReadLen,
      unsigned long* pulDataReadLen, void *pData);

//! \brief Read out a set of complete records from a cyclic or linear record file.
//! \details The \"read records\" command requires a preceding authentication either
//! with the key specified for \"Read\" or \"Read & Write\" access. \n
//! Depending on the communication settings defined in parameter, data will be sent
//! by the PICC either in plain, MACed or enciphered only if the defined communication
//! settings is compliant with the communication settings of the file.\n
//! A \"read records\" command on an empty record file (directly after creation
//! or after a commited clearance) will return in an error.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the value file.
//! \param[in] ulOffset Offset of the newest record which is read out. In case
//! of 0x000000 the latest record is read out. The offset value must be in range
//! from 0x000000 to number of existing records -1.
//! \param[in] ulDataToReadLen Number of records to be read from the PICC. Records are
//! are always transmitted by the PICC in chronological order (=starting with the oldest,
//! which is number of records -1 before the one adressed by the given offset).
//! If this parameter is set to 0x000000 then all records, from the oldest record
//! up to and including the newest record (given by the offset parameter) are read.\n
//! The allowed range for the number of records parameter is from 0x000000 to
//! number of existing records - offset.
//! \param[out] pulDataReadLen Pointer to an unsigned long which will receive the
//! number of bytes read. Useful when ulDataToReadLen parameter has been set to 0.
//! \param[out] pData Pointer to a buffer which will receive the data read.
//! \param[in] iComSettings Communication settings to use :
//! - \ref DCM_PLAIN
//! - \ref DCM_MACED
//! - \ref DCM_ENCIPHERED
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \warning The buffer pData shall be big enough to receive the data read. In most case,
//! the size of pData shall be at least equal to uLength but if uLength is equal to 0,
//! the whole file will be read so pData shall have at least the same size than the
//! file which is read.
//! \remarks In cyclic record files the maximum number of stored valid records is
//! one less than the number of records specified in the \"create cyclic record file\"
//! command.
//! \sa \ref desfire_ReadData, \ref desfire_ReadDataCS, \ref desfire_WriteData, \ref
//! desfire_WriteDataCS, \ref desfire_GetValue, \ref desfire_GetValueCS, \ref desfire_Credit, \ref
//! desfire_CreditCS, \ref desfire_Debit, \ref desfire_DebitCS, \ref desfire_LimitedCredit,
//! \ref desfire_LimitedCreditCS, \ref desfire_WriteRecord, \ref desfire_WriteRecordCS, \ref desfire_ReadRecords
extern int desfire_ReadRecordsCS(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId, unsigned long ulOffset,
      unsigned long ulDataToReadLen, unsigned long* pulDataReadLen,
      void *pData, int iComSettings);

//! \brief Reset a cyclic or linear record file to the empty state.
//! \details After a \"clear record\" command but before a \"commit transaction\",
//! all subsequent \"write record\" commands will fail. The \"read records\"
//! command will return the old still valid records.\n
//! After the \"commit transaction\" command has been performed, a \"read records\"
//! command will fail, \"write record\" commands will be successful.\n
//! An \"abort transaction\" command (instead of \"commit transaction\") will
//! invalidate the clearance.\n
//! The full \"Read & Write\" permission on the file is necessary for executing
//! this command.
//! \param[in,out] pContext Pointer to the application context.
//! \param[in] fileId File identifier of the value file.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_CommitTransaction, \ref desfire_AbortTransaction
extern int desfire_ClearRecordFile(T_DESFIRE_CONTEXT *pContext,
      T_DESFIRE_FID fileId);

//! \brief Validate all previous write access on backup data files, value files and
//! record files within one application.
//! \details The \"commit transaction\" command validates all write access to files
//! with integrated backup mechanisms :
//! - Backup Data Files
//! - Value Files
//! - Linear Record Files
//! - Cyclic Record Files
//! The \"commit transaction\" is typically the last command of a transaction before
//! the ISO/IEC 14443-4 \"deselect\" command or before proceeding with another application
//! (see \ref desfire_SelectApplication).
//! \param[in,out] pContext Pointer to the application context.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_AbortTransaction
extern int desfire_CommitTransaction(T_DESFIRE_CONTEXT *pContext);

//! \brief Invalidates all previous write access on backup data files, value
//! files and record files within one application.
//! \details This command is useful to cancel a transaction without loosing
//! the current authenticated status hence reducing the need for re-selection
//! and re-authentication of the application. \n
//! The \"abort transaction\" command invalidates all write access to files
//! with integrated backup mechanisms without changing the authentication status :
//! - Backup Data Files
//! - Value Files
//! - Linear Record Files
//! - Cyclic Record Files
//! \param[in,out] pContext Pointer to the application context.
//! \return Command status code or CLESS status code (0x00 if no error occured)
//! \sa \ref desfire_CommitTransaction
extern int desfire_AbortTransaction(T_DESFIRE_CONTEXT *pContext);
//! @}
//! @}

//Key management fonctions

//! \addtogroup KeyManagement
//! @{

//! \brief Generate a DES key either for DESFire Native authentication or standard
//! authentication.
//! \details The less significant bits of the 8 first bytes (used to set a key version)
//! are set to 0.
//! \param[in] tucValue Value of the key (array of 8 bytes).
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Return a pointer to the new key.
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion,
//! \ref desfire_NewContext, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_NewDesKey(unsigned char tucValue[8],
      T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Generate a DES key either for DESFire Native authentication or standard
//! authentication.
//! \details The less significant bits of the 8 first bytes (used to set a key version)
//! are kept unchanged.
//! \param[in] tucValue Value of the key (array of 8 bytes).
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Return a pointer to the new key.
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion,
//! \ref desfire_NewContext, \ref mifare_NewDesKey, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_NewDesKeyWithVersion(unsigned char tucValue[8],
      T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Generate a 2K3DES key either for DESFire Native authentication or standard
//! authentication.
//! \details The less significant bits of the 8 first bytes (used to set a key version)
//! are set to 0.
//! \param[in] tucValue Value of the key (array of 16 bytes).
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Return a pointer to the new key.
//! \sa \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey, \ref mifare_New3k3desKeyWithVersion,
//! \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion, \ref desfire_NewContext,
//! \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_New3desKey(unsigned char tucValue[16],
      T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Generate a 2K3DES key either for DESFire Native authentication or standard
//! authentication.
//! \details The less significant bits of the 8 first bytes (used to set a key version)
//! are kept unchanged.
//! \param[in] tucValue Value of the key (array of 16 bytes).
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Return a pointer to the new key.
//! \sa \ref mifare_New3desKey, \ref mifare_New3k3desKey, \ref mifare_New3k3desKeyWithVersion,
//! \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion, \ref desfire_NewContext,
//! \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_New3desKeyWithVersion(unsigned char tucValue[16],
      T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Generate a 3K3DES key for DESFire standard authentication
//! (see \ref desfire_Authenticate, or \ref desfire_AuthenticateIso).
//! \details The less significant bits of the 8 first bytes (used to set a key version)
//! are set to 0. \n
//! <b>This key is not compliant with DESFire EV0)</b>.
//! \param[in] tucValue Value of the key (array of 24 bytes).
//! or desfire_AuthenticateIso).
//! \return Return a pointer to the new key.
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKeyWithVersion,
//! \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion, \ref desfire_NewContext,
//! \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_New3k3desKey(unsigned char tucValue[24]);

//! \brief Generate a 3K3DES key for DESFire standard authentication
//! (see \ref desfire_Authenticate, or \ref desfire_AuthenticateIso).
//! \details The less significant bits of the 8 first bytes (used to set a key version)
//! are kept unchanged. \n
//! <b>This key is not compliant with DESFire EV0)</b>.
//! \param[in] tucValue Value of the key (array of 24 bytes).
//! or desfire_AuthenticateIso).
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion, \ref desfire_NewContext,
//! \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_New3k3desKeyWithVersion(unsigned char tucValue[24]);

//! \brief Generate a AES key either for DESFire standard authentication
//! (see \ref desfire_Authenticate, or \ref desfire_AuthenticateAes).
//! \details The less significant bits of the 8 first bytes (used to set a key version)
//! are set to 0.\n
//! <b>This key is not compliant with DESFire EV0)</b>.
//! \param[in] tucValue Value of the key (array of 16 bytes).
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKeyWithVersion, \ref desfire_NewContext,
//! \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_NewAesKey(unsigned char tucValue[16]);

//! \brief Generate a AES key either for DESFire standard authentication
//! (see \ref desfire_Authenticate, or \ref desfire_AuthenticateAes).
//! \details The less significant bits of the 8 first bytes (used to set a key version)
//! are kept unchanged. \n
//! <b>This key is not compliant with DESFire EV0)</b>.
//! \param[in] tucValue Value of the key (array of 16 bytes).
//! \param[in] ucVersion Version of the key to create (1 byte).
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey, \ref desfire_NewContext,
//! \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion, \ref mifare_FreeKey
extern T_MIFARE_KEY* mifare_NewAesKeyWithVersion(const unsigned char tucValue[16],
      unsigned char ucVersion);

//! \brief Free a key.
//! \details The key and all data it contains will be deleted.
//! \param[in] pKey Pointer to the key to delete.
//! \remarks If the value of pointer is NULL, no operations will be performed.
//! \remarks After having deleted a key, it can be advised to set the pointer
//! value to NULL.
//! \sa \ref mifare_New3desKey, \ref mifare_New3desKeyWithVersion, \ref mifare_New3k3desKey,
//! \ref mifare_New3k3desKeyWithVersion, \ref mifare_NewAesKey, \ref mifare_NewAesKeyWithVersion,
//! \ref desfire_NewContext, \ref mifare_NewDesKey, \ref mifare_NewDesKeyWithVersion
extern void mifare_FreeKey(T_MIFARE_KEY *pKey);

//! \brief Create a diversified DES key. Compliant with MIFARE SAM AV1
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] tucDivInp Diversification input
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
extern T_MIFARE_KEY * mifare_DiversifyKeyDES(unsigned char tucKeyValue[8],
      unsigned char tucDivInp[8], T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Create a diversified 2k3DES key. Compliant with MIFARE SAM AV1
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] tucDivInp Diversification input
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
//! \sa \ref mifare_DiversifyKey2K3DES_AV2
extern T_MIFARE_KEY * mifare_DiversifyKey2K3DES(unsigned char tucKeyValue[16],
      unsigned char tucDivInp[8], T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Create a diversified 2k3DES key. Compliant with MIFARE SAM AV2
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] tucDivInp Diversification input (1 to 15 bytes)
//! \param[in] iDivInpLen Diversification input length
//! \param[in] chainingMode The block chaining mode: \ref MF_CHAINING_ECB, \ref MF_CHAINING_CBC or \ref MF_CHAINING_DESFIRE_NATIVE.
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
//! \sa \ref mifare_DiversifyKey2K3DES
extern T_MIFARE_KEY * mifare_DiversifyKey2K3DES_AV2(
      unsigned char tucKeyValue[16], unsigned char tucDivInp[15],
      int iDivInpLen, T_MIFARE_CHAINING_MODE chainingMode);

//! \brief Create a diversified 3k3DES key. Compliant with MIFARE SAM AV1
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] tucDivInp Diversification input
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
//! \sa \ref mifare_DiversifyKey3K3DES_AV2
extern T_MIFARE_KEY * mifare_DiversifyKey3K3DES(unsigned char tucKeyValue[24],
      unsigned char tucDivInp[8]);

//! \brief Create a diversified 3k3DES key. Compliant with MIFARE SAM AV2
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] tucDivInp Diversification input (1 to 15 bytes)
//! \param[in] iDivInpLen Diversification input length
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
//! \sa \ref mifare_DiversifyKey3K3DES
extern T_MIFARE_KEY * mifare_DiversifyKey3K3DES_AV2(
      unsigned char tucKeyValue[24], unsigned char tucDivInp[15],
      int iDivInpLen);

//! \brief Create a diversified AES key. Compliant with MIFARE SAM AV1
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] ucVersion Version of the key to diversify.
//! \param[in] tucDivInp Diversification input
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
//! \sa \ref mifare_DiversifyKeyAES128
extern T_MIFARE_KEY * mifare_DiversifyKeyAES128(unsigned char tucKeyValue[16],
      unsigned char ucVersion, unsigned char tucDivInp[16]);

//! \brief Create a diversified AES key. Compliant with MIFARE SAM AV2
//! \param[in] tucKeyValue Value of the key to diversify.
//! \param[in] ucVersion Version of the key to diversify.
//! \param[in] tucDivInp Diversification input (1 to 31 bytes)
//! \param[in] iDivInpLen Diversification input length
//! \return Pointer to the diversified key (\ref T_MIFARE_KEY)
//! \sa \ref mifare_DiversifyKeyAES128_AV2
extern T_MIFARE_KEY * mifare_DiversifyKeyAES128_AV2(
      unsigned char tucKeyValue[16], unsigned char ucVersion,
      unsigned char tucDivInp[31], int iDivInpLen);

//! \brief Compute a key version from a key without sending a command to the PICC
//! \param[in] pKey Pointer to a key
//! \return Version of the key on 1 byte
//! \sa \ref mifare_KeySetVersion, desfire_GetKeyVersion
extern unsigned char mifare_KeyGetVersion(T_MIFARE_KEY *pKey);

//! \brief Add a version to a key.
//! \details Only the version of the key passed in parameter is changed.
//! <b> No changes are done on the PICC</b>
//! \param[in] pKey Pointer to a key
//! \param[in] ucVersion Version to add on the less significant bit of the 8
//! first bytes of the key.
//! \sa \ref mifare_KeyGetVersion, desfire_GetKeyVersion
extern void mifare_KeySetVersion(T_MIFARE_KEY *pKey, unsigned char ucVersion);
//! @}

// Mifare SAM functions

//! \addtogroup SAMContextManagement
//! @{

//! \brief Detect SAM presence and power it on.
//! \details This function detect and return the descriptor to the first SAM
//! detected. If several SAM are present, the first one will be used and others
//! will be ignored. If a specific SAM has to be used, it will be necessary to
//! power it on without the mifareSAM_AutoDetectSAM function.
//! \remarks Think about powering off the SAM when it is not used anymore.
//! \return
//! - Pointer to descriptor of powered SAM
//! - NULL if SAM not found or if power on failed
extern FILE* mifareSAM_AutoDetectSAM(void);

//! \brief Create a SAM context
//! \param[in] hSAM File descriptor of the SAM to use
//! \param[in] samMode SAM mode (see \ref T_MIFARE_SAM_MODE)
//! - MF_SAM_AV1
//! - MF_SAM_AV2
//! \return Pointer to the new SAM context. NULL if an error occured.
//! \sa \ref mifareSAM_FreeContext
extern T_MIFARE_SAM_CONTEXT* mifareSAM_NewContext(FILE* hSAM,
      T_MIFARE_SAM_MODE samMode);

//! \brief Clear a SAM context
//! \param[in,out] pSAMCtx Pointer to the SAM context to be cleared
//! \sa \ref mifareSAM_NewContext
extern void mifareSAM_FreeContext(T_MIFARE_SAM_CONTEXT* pSAMCtx);
//! @}

//! \addtogroup SAMCommands
//! @{

// SAM Security and configuration commands

//! \brief Put the SAM in sleep mode to lower power consumption.
//! \details The SAM will be woken-up automaticaly on the reception of the next command.
//! \param[in] pSAMCtx Pointer to the SAM context
//! \return
//! - 0 if OK
//! - EMV_apdu error return code in case of EMV_apdu error
//! - Byte SW2 or the SAM response APDU if SW1 SW2 is not equal to 0x90 0x00
extern int mifareSAM_Sleep(T_MIFARE_SAM_CONTEXT* pSAMCtx);


// Mifare DESFire and ULC in non-X-mode commands

//! \todo
extern int mifareSAM_AuthenticateHost(T_MIFARE_SAM_CONTEXT* pSAMCtx,
      T_MIFARE_KEY* pKey, unsigned char ucAuthMode, unsigned char ucKeyNo,
      unsigned char ucKeyVersion, unsigned char *pDivInp, int iDivInpLen);

//! \todo
extern int mifareSAM_ChangeKeyEntry(T_MIFARE_SAM_CONTEXT* pSAMCtx,
      unsigned char ucKeyNo, unsigned char ucProgMask,
      T_MIFARE_KEY_ENTRY* pKeyEntry);


//! @}

// Include the deprecated declarations
#include "Desfire_deprecated.h"

#endif /* !__DESFIRE_H__ */
