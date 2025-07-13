
#ifndef __DEXUCS_INTERF_H__
#define __DEXUCS_INTERF_H__


//! \defgroup DEXUCS_DLL DEX-UCS DLL
//! \brief Provides the application some functions to use the DEX-UCS protocol. This protocol is used with vending solutions and is defined by <a href="http://www.vending-europe.eu/eva/home.html"> EVA </a>(European Vending Association). The protocol is described in the EVA Data Transfert Standard (EVA DTS).
//! @{
//! \defgroup DEXUCS_COMMUN_FUNCTIONS  General Functions
//! \defgroup DEXUCS_MASTER  The terminal is master
//! \defgroup DEXUCS_SLAVE  The terminal is slave
//! \defgroup DEXUCS_SPECIF  Specific functions

//! \brief DEXUCS communication handle. 
//! This handle is created by calling DEXUCS_Connect and released by calling DEXUCS_Disconnect.
typedef void* DEXUCS_HANDLE;
//!@}

//! \defgroup DEXUCS_ERRORS   Error list
//! @{
//! \brief OK. The operation has been successfully processed.
#define _DEXUCS_OK                 (0)
//! \brief Wrong parameters.
#define _DEXUCS_ERR_WRONG_PRM      (-1)
//! \brief The request is unexpected in the current state.
#define _DEXUCS_ERR_WRONG_STATE    (-2)
//! \brief The devise is mute. No bytes received. Check cable or device.
#define _DEXUCS_ERR_MUTE           (-3)
//! \brief Communication stopped (the cable has been removed for example).
#define _DEXUCS_ERR_TMO            (-4)
//! \brief Unkown bytes received from the device.
#define _DEXUCS_ERR_KO             (-5)
//! \brief Unexpected request.
#define _DEXUCS_ERR_DENIED         (-6)
//! \brief The request is cancelled by the specified Telium event.
#define _DEXUCS_ERR_CANCEL         (-7)
//! \brief The file can't be read.
#define _DEXUCS_ERR_PB_FILE        (-8)
//! \brief The operation has been successfully processed and terminated.
#define _DEXUCS_EOT                (-9)
//! @}

//! \defgroup DEXUCS_READING_OPERATION Reading Operation
//! @{
  #define  DEXUCS_BLOCK_NEXT        0   /*!< Ask the first or next block*/
  #define  DEXUCS_BLOCK_REPEAT      1   /*!< Ask the previous block repetition*/
//! @}

//! \brief Max block size (in bytes)
#define DEXUCS_MAX_BLOCK_SIZE    300

//! \defgroup DEXUCS_DEF_REQUEST Request values of the master. 
//! \brief These requests are defined by EVA.
//! @{
  #define  DEXUCS_REQUEST_CONFIGURATION    'S'  /*!< Request to send configuration data to VMD */
  #define  DEXUCS_REQUEST_AUDIT            'R'  /*!< Request to read audit data from VMD */
  #define  DEXUCS_REQUEST_MANUFACTURER     'M'  /*!< Request to read audit data from VMD */
  #define DEXUCS_REQUEST_TRANSPARENT       'T' /*!< INGENICO's private Request. not EVA. --> don't use it */
  #define DEXUCS_REQUEST_SETPARAM          'P' /*!< INGENICO's private Request. not EVA. --> don't use it*/
//!@}

//! \defgroup DEXUCS_DEF_RESP_CODE Response code value of the slave
//! \brief These response codes are defined by EVA (EVA V6.0 cf.4.5.7)
//! @{
  #define DEXUCS_REPCODE_OK                   0 /*!< Request accepted. ref. (EVA V6.0 4.5.7)*/
  #define DEXUCS_REPCODE_UNRECOGN_ID          1 /*!< Request denied. ref. (EVA V6.0 4.5.7)*/
  #define DEXUCS_REPCODE_UNSUPPORT_LEVEL      2 /*!< Request denied. ref. (EVA V6.0 4.5.7)*/
  #define DEXUCS_REPCODE_OP_CONFLICT          3 /*!< Request denied. ref. (EVA V6.0 4.5.7)*/
  #define DEXUCS_REPCODE_NODATA_TO_TRANSFERT  4 /*!< Request denied. ref. (EVA V6.0 4.5.7)*/
  #define DEXUCS_REPCODE_UNDEF_ERR            5 /*!< Request denied. ref. (EVA V6.0 4.5.7)*/
  #define DEXUCS_REPCODE_MANUFACTURER        90 /*!<Request denied. ref. (EVA V6.0 4.5.7)*/
  #define DEXUCS_REPCODE_UNSUPPORTED         80 /*!< INGENICO's private reply. don't use it*/
  #define DEXUCS_REPCODE_DEVICE_OFF          81 /*!< INGENICO's private reply. don't use it */
//!@}

//! \addtogroup DEXUCS_SLAVE
//! \brief The terminal is the slave (VMD). It waits for the master request. The terminal provides the audit data (EVA-DTS format).
//! @{
//! \addtogroup DEXUCS_ERRORS
//! \addtogroup DEXUCS_DEF_REQUEST
//! \addtogroup DEXUCS_DEF_RESP_CODE
//! \addtogroup DEXUCS_SLAVE_EXAMPLE

//! \defgroup DEXUCS_DEF_TRN_MODE Device requested.
//! \brief used in transparent mode.
//! @{
#define DEXUCS_DEVICE_NONE        0  /*!< not used */
#define DEXUCS_DEVICE_SELECTOR    1  /*!< to enable transparent mode with coin selector */
#define DEXUCS_DEVICE_CASHLESS    2  /*!< to enable transparent mode with cashless */
//!@}

//! \brief provides terminal features or gets the master features.
//! \note Thoses parameters are defined by EVA.
typedef struct
{
  unsigned char ucCommID[10];  /*!<  Slave or Master ID. Format defined by EVA ("SAGxxxxxxx" for ex.)*/
  unsigned char ucRevision;  /*!<  Protocol revision . 00 = EVA DTS v6.0  or 01 EVA DTS v1.1   */
  unsigned char ucLevel;    /*!<  Protocol Level. 06 = EVA DTS v6.0  or 01 EVA DTS v1.1   */
}T_DEXUCS_SESSION;

//! \brief transparent mode settings
typedef struct
{
  unsigned long  ulDevice;   /*!< \ref DEXUCS_DEF_TRN_MODE */
  unsigned short usBaudRate; /*!< dialogue baud rate (9600,1200) */
}T_DEXUCS_TRANSPARENT_MODE;

//! \brief update date of the slave
#define DEXUCS_PARAM_TIME  1

//! \brief Member of T_DEXUCS_REQUEST_SETTINGS
typedef struct
{
  unsigned long ulParam;    /*!< Param value. Only \ref DEXUCS_PARAM_TIME is available */
  union
  {
    DATE  sDate;      /*!< Master Date */ 
  }uParam;
}T_DEXUCS_SET_PARAM;

//! \brief Extra request parameters 
//! \brief INGENICO's private requests \ref DEXUCS_REQUEST_TRANSPARENT or \ref DEXUCS_REQUEST_SETPARAM)
typedef struct
{
  unsigned char ucRequest;  /*!< \ref  DEXUCS_REQUEST_TRANSPARENT or \ref DEXUCS_REQUEST_SETPARAM */
  union  
  {
    T_DEXUCS_TRANSPARENT_MODE  sTransparent;  /*!< get the transparent channel features (\ref  DEXUCS_REQUEST_TRANSPARENT) */
    T_DEXUCS_SET_PARAM      sSet;      /*!< Get the parameters  (\ref DEXUCS_REQUEST_SETPARAM) */
  }u;
}T_DEXUCS_REQUEST_SETTINGS;

//! \brief Wait for the master request. 
//! \param[in] pCtx_p session handle
//! \param[out] pDC_p Master features (\ref T_DEXUCS_SESSION)
//! \param[out] pucRequest_p Master Request (\ref DEXUCS_DEF_REQUEST)
//! \param[in,out] puiEvent_p Telium events which cancel the waiting (KEYBOARD ..). 
//! \param[in] iTimeOut_p Timeout (in 10ms)
//! \return
//!    - \ref _DEXUCS_OK  The master sends a request
//!    - errors.. (see \ref DEXUCS_ERRORS)  
int DEXUCS_WaitHandshake (DEXUCS_HANDLE pCtx_p,T_DEXUCS_SESSION* pDC_p,unsigned char * pucRequest_p,unsigned int* puiEvent_p,unsigned int iTimeOut_p);

//! \brief Reply to the master request. 
//! \param[in] pCtx_p session handle  (\ref T_DEXUCS_SESSION)
//! \param[in] pVMD_p Slave features (\ref T_DEXUCS_SESSION)
//! \param[out] ucResponseCode_p \ref DEXUCS_DEF_RESP_CODE
//! \return
//!    - \ref _DEXUCS_OK  The reply was correctly sent.
//!    - errors.. (see \ref DEXUCS_ERRORS)  
int DEXUCS_AnswerHandshake(DEXUCS_HANDLE pCtx_p,T_DEXUCS_SESSION* pVMD_p,unsigned char ucResponseCode_p);

//! \brief Send an audit file to the master. 
//! \param[in] pCtx_p session handle.
//! \param[in] szLocalFile_p full path of the audit file application.
//! \return
//!    - \ref _DEXUCS_OK  The file was correctly sent.
//!    - errors.. (see \ref DEXUCS_ERRORS)  
//! \note The audit file format is EVA-DTS (ASCII)
//! \warning The Disk must be mounted by the application.
int DEXUCS_PutFile(DEXUCS_HANDLE pCtx_p, const char *szLocalFile_p);  

//! \brief Get the INGENICO's private request settings.
//! \param[in] pCtx_p session handle
//! \param[in] i_Size_p size of the pSettings_p
//! \param[out] pSettings_p Extra request settings
//! \return
//!    - \ref _DEXUCS_OK  The file was correctly sent.
//!    - errors.. (see \ref DEXUCS_ERRORS)  
//! \note Only the private requests \ref DEXUCS_REQUEST_TRANSPARENT and \ref DEXUCS_REQUEST_SETPARAM are supported.
int DEXUCS_GetRequestSettings (DEXUCS_HANDLE pCtx_p,int i_Size_p,T_DEXUCS_REQUEST_SETTINGS* pSettings_p);

//!@}

//! \addtogroup DEXUCS_COMMUN_FUNCTIONS
//! @{

//! \addtogroup DEXUCS_ERRORS

//! \brief Load the DLL DEXUCS.
//! \return The return value of the ObjectLoad function. 0 if successfull.
int DEXUCSlib_open(void);
//! \brief Unload the DLL DEXUCS.
void DEXUCSlib_close(void);
//! \brief Version of the API lib interface with DEXUCS DLL.
//! \return Version as integer.
int DEXUCS_Version (void);
//! \brief Open the DEXUCS session (MASTER or SLAVE)
//! \param[in,out] pCtx_p pointer on handle. The memory is allocated .
//! \param[in] pucCom_p Port name ("COM0" for ex)
//! \param[in] ucMode_p Connection mode -> set to 0. No specif mode is available.
//! \return
//!    - \ref _DEXUCS_OK  The file was correctly sent.
//!    - errors.. (see \ref DEXUCS_ERRORS)  
int DEXUCS_Connect (DEXUCS_HANDLE* pCtx_p, unsigned char * pucCom_p,unsigned char ucMode_p);
//! \brief Close the DEXUCS session (MASTER or SLAVE)
//! \param[in] pCtx_p handle of the session. The function releases the handle.
void DEXUCS_Disconnect (DEXUCS_HANDLE pCtx_p);
//!@}


//! \addtogroup DEXUCS_MASTER
//! \brief The terminal is the master (DC). It collects the audit from an another device (VMD) : coin selector, vending machine for example.
//! @{
//! \addtogroup DEXUCS_ERRORS
//! \addtogroup DEXUCS_DEF_REQUEST
//! \addtogroup DEXUCS_DEF_RESP_CODE
//! \addtogroup DEXUCS_READING_OPERATION
//! \addtogroup DEXUCS_MASTER_EXAMPLE

//! \brief Start audit dialog (Handshake) 
//! \param[in] pCtx_p session handle
//! \param[in] pDC_p Master features (\ref T_DEXUCS_SESSION)
//! \param[out] pVMD_p Slave features (\ref T_DEXUCS_SESSION)
//! \param[out] pucResponseCode_p \ref DEXUCS_DEF_RESP_CODE
//! \return
//!    - \ref _DEXUCS_OK  The slave device has accepted the audit request.
//!    - errors.. (see \ref DEXUCS_ERRORS)  
//! \note The request \ref DEXUCS_REQUEST_AUDIT is sent to the slave device (VMD)
int DEXUCS_StartAudit (DEXUCS_HANDLE pCtx_p, T_DEXUCS_SESSION* pDC_p, T_DEXUCS_SESSION* pVMD_p,unsigned char * pucResponseCode_p);
//! \brief Read the audit file
//! \param[in] pCtx_p session handle
//! \param[in] ucOperation_p \ref DEXUCS_READING_OPERATION
//! \param[in,out] pi_Size_p pointer on buffer size. 
//!    in input, size of the output buffer. *pi_Size_p=DEXUCS_MAX_BLOCK_SIZE.
//!    in output, size of the read data.
//! \param[out] puc_Data_p Read Buffer
//! \return
//!    - \ref _DEXUCS_OK  The block is correctly read. The application has to read the next block.
//!    - \ref _DEXUCS_EOT  Reading is terminated.
//!    - errors.. (see \ref DEXUCS_ERRORS)  
//! \note DEXUCS_ReadAudit has to be called while the function returns _DEXUCS_OK. The application concatenates the block read.
int DEXUCS_ReadAudit (DEXUCS_HANDLE pCtx_p, unsigned char ucOperation_p, int* pi_Size_p, unsigned char* puc_Data_p);
//! \brief Start configuration dialog (Handshake)
//! \param[in] pCtx_p session handle
//! \param[in] pDC_p Master features (\ref T_DEXUCS_SESSION)
//! \param[out] pVMD_p Slave features (\ref T_DEXUCS_SESSION)
//! \param[out] pucResponseCode_p \ref DEXUCS_DEF_RESP_CODE
//! \return
//!    - \ref _DEXUCS_OK  The slave device has accepted the configuration request.
//!    - errors.. (see \ref DEXUCS_ERRORS)  
//! \note The request \ref DEXUCS_REQUEST_CONFIGURATION is sent to the slave device (VMD)
int DEXUCS_StartConfiguration(DEXUCS_HANDLE pCtx_p, T_DEXUCS_SESSION* pDC_p , T_DEXUCS_SESSION* pVMD_p, unsigned char * pucResponseCode_p);
//! \brief Write configuration data
//! \param[in] pCtx_p session handle.
//! \param[in] i_Size_p Size of the data to write.
//! \param[out] puc_Data_p Data to write.
//! \return
//!    - \ref _DEXUCS_OK  The configuration data have been correctly sent to the slave device (VMD).
//!    - errors.. (see \ref DEXUCS_ERRORS)  
int DEXUCS_WriteConfiguration(DEXUCS_HANDLE pCtx_p, int i_Size_p, unsigned char* puc_Data_p);
//! @}

//! \addtogroup DEXUCS_SPECIF
//! \brief INGENICO's private functions.
//! \brief The application can use them to send and receive bytes without procotol commands.
//! @{
//! \addtogroup DEXUCS_ERRORS

//! \brief Write bytes to DEXUCS's com port.
//! \param[in] pCtx_p Session handle.
//! \param[in] i_Size_p Size of byte to write.
//! \param[out] pucBuf_p Buffer to write.
//! \return
//!    - \ref _DEXUCS_OK  The bytes were correctly sent.
//!    - errors.. (see \ref DEXUCS_ERRORS)  
int DEXUCS_Write(DEXUCS_HANDLE pCtx_p, int i_Size_p, unsigned char *pucBuf_p);
//! \brief Read bytes from DEXUCS's com port
//! \param[in] pCtx_p Session handle
//! \param[in,out] pi_Size_p pointer of buffer size.
//!    in input, *pi_Size_p Size of bytes to read.
//!    in output, *pi_Size_p Size of read bytes.
//! \param[out] pucBuf_p Buffer to write.
//! \param[in] iTimeOut_p Timeout (in 10ms).
//! \return
//!    - \ref _DEXUCS_OK Some bytes were received.
//!    - errors.. (see \ref DEXUCS_ERRORS)  
int DEXUCS_Read(DEXUCS_HANDLE pCtx_p, int* pi_Size_p, unsigned char *pucBuf_p,unsigned int iTimeOut_p);
//! @}

//! \defgroup DEXUCS_SLAVE_EXAMPLE Example
//! @{
//! \include DEXUCS_interface_Sample_01.c
//! @}

//! \defgroup DEXUCS_MASTER_EXAMPLE Example
//! @{
//! \include DEXUCS_interface_Sample_02.c
//! @}

#endif /* __DEXUCS_INTERF_H__ */

