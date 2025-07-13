/*! @addtogroup KSFAM_GPRS
	* @{
	
 	* @section ex_GPRS Sample Programs
 	*
 	* @subsection sub01_GPRS Network Availability
 	*
 	* All the functions of the DLL do not generate immediately an effective result. 
 	*
 	* For example, the function @c gprs_enable is called to activate the GPRS communication mode, it returns immediately its result. However, in case of success, the GPRS network is not immediately available. The following function waits for the network availability.
 	*

 * @include gprs_lib_Sample_01.c
 	* 
 	* @link KSFAM_GPRS Back to top @endlink
 
  * @n @subsection sub02_GPRS GPRS Network Connection
  *
  * The following sample performs a GPRS connection. 
  *
  * The GPRS facility is previously activated and the GPRS network connection is requested. The connection timeout is set to 30 seconds.
  *

 * @include gprs_lib_Sample_02.c
  * 
  * @link KSFAM_GPRS Back to top @endlink		




  * @n @subsection sub04_GPRS GSM Communication
  *
  * The next example performs a GSM connection, waits 3 seconds then initiates the disconnection.
  *

 * @include gprs_lib_Sample_03.c
  * 
  * @link KSFAM_GPRS Back to top @endlink  		

**/
#ifndef GPRSLIB_INC
#define GPRSLIB_INC

/*
======================================================================
					List of Defines
======================================================================
*/
#define GPRS_LOGIN_LGR				30
#define GPRS_PASSWORD_LGR			30
#define GPRS_NETWORK_NAME_LGR		20
#define GPRS_SIM_PIN_CODE_LGR_MIN	4
#define GPRS_SIM_PIN_CODE_LGR		8
#define GPRS_APN_LGR				100


// Return values
#define GPRS_OK				        0
#define GPRS_ERR_BAD_PARAM		   -1
#define GPRS_ERR_NO_SIM 		  	 		-2			/*!< There is no SIM card in the device */
#define GPRS_ERR_NO_PIN			  	 		-3			/*!< The PIN code of the SIM card is required */
#define GPRS_ERR_BAD_PIN		  	 		-4			/*!< The entered PIN code is invalid.  */
#define GPRS_ERR_SIM_LOCK		  		  -5			/*!< The SIM card is locked. */
#define GPRS_ERR_FATAL			   -6
#define GPRS_ERR_UNKNOWN		  	 		-7			/*!< The SIM card is not ready.  */
#define GPRS_ERR_CONNECT_TIMEOUT 		-8			/*!< The connection failed - the timeout expired. */
#define GPRS_ERR_PPP			   				-9			/*!< The PPP connection failed. */
#define GPRS_ERR_ALREADY_CONNECTED -10
#define GPRS_ERR_NO_GPRS		   		 -11			/*!< The library facilities are not available*/
#define GPRS_ERR_BAD_PUK_CODE  	 		-12			/*!< The entered PUK code is invalid.  */


#define GPRS_ERRNO_DRIVER_NOT_OPEN        0x0041
#define GPRS_ERRNO_START_REPORT           0x0042
#define GPRS_ERRNO_BAD_PIN                0x0043
#define GPRS_ERRNO_NO_SIM                 0x0044
#define GPRS_ERRNO_SIM_LOCK               0x0045
#define GPRS_ERRNO_FATAL_ERROR            0x0046
#define GPRS_ERRNO_UNKNOWN_ERROR          0x0047
#define GPRS_ERRNO_ENABLE_TIMEOUT         0x0048
#define GPRS_ERRNO_CONNECT_KO             0x0049
#define GPRS_ERRNO_CONNECT_TIMEOUT        0x004A
#define GPRS_ERRNO_PPP                    0x004B
#define GPRS_ERRNO_DISCONNECT_KO          0x004C
#define GPRS_ERRNO_GSM_CONNECT_KO         0x004D
#define GPRS_ERRNO_GSM_CONNECT_TIMEOUT    0x004E
#define GPRS_ERRNO_GSM_CONNECT_VOICE      0x004F
#define GPRS_ERRNO_BAD_PARAM              0x0050
#define GPRS_ERRNO_GPRS_DISCONNECTED      0x0051
#define GPRS_ERRNO_GSM_DISCONNECTED       0x0052
#define GPRS_ERRNO_GSM_ALREADY_CONNECTED  0x0053
#define GPRS_ERRNO_GSM_CONNECT_ABORTED    0x000D
#define GPRS_ERRNO_PPP_NOT_CLOSED         0x0055
#define GPRS_ERRNO_CONNECT_ABORTED        0x000D
#define GPRS_ERRNO_NO_PIN                 0x0057
#define GPRS_ERRNO_GSM_SEND_KO            0x0058
#define GPRS_ERRNO_GSM_SEND_ABORTED       0x000D
#define GPRS_ERRNO_GSM_RECEIVE_KO         0x005A
#define GPRS_ERRNO_GSM_RECEIVE_ABORTED    0x000D
#define GPRS_ERRNO_GSM_RECEIVE_OVERFLOW   0x005B
#define GPRS_ERRNO_GSM_RECEIVE_TIMEOUT    0x005C
#define GPRS_ERRNO_SIM_PIN_REQUIRED       0x005D
#define GPRS_ERRNO_NO_PIN_REQUIRED        0x005E
#define GPRS_ERRNO_NOT_IMPLEMENTED        0x005F
#define GPRS_ERRNO_SMS_ABORTED            0x000D

#define GATEWAY_CONNECT_SSL_KO            0x0060
#define GATEWAY_CONNECT_TCP_KO            0x0061
#define GATEWAY_CONNECT_RECEIVE_KO        0x0062
#define GATEWAY_CONNECT_SEND_KO           0x0063
#define GATEWAY_INVALID_DATA              0x0064
#define GATEWAY_CONNECT_REJECTED          0x0065
#define GATEWAY_X25_ADRESS_TOO_LONG       0x0066
#define GATEWAY_INVALID_GATEWAY           0x0067
#define GATEWAY_SOCKET_KO                 0x0068
#define GATEWAY_IDENTIF_KO                0x0069

// option argument of gprs_getParam function
#define GPRS_PARAM_LOGIN		1
#define GPRS_PARAM_PASSWORD		2
#define GPRS_PARAM_APN			3
#define GPRS_PARAM_PIN			4
#define GPRS_PARAM_NETWORK		5
#define GPRS_PARAM_PUK			6

// Value of parameter for gprs_gettechnology
#define GPRS_GSM_TECHNOLOGY     0
#define GPRS_3G_TECHNOLOGY      2

#define GPRS_FREE_PIN_MODE		1
#define GPRS_SUSPICIOUS_PIN_MODE	2

#define gsm_disconnect gprs_stop
#define gprs_disconnect gprs_stop

/*
======================================================================
			Functions Definition
======================================================================
*/


/*! @brief This function disconnects the current connection to the GPRS network.
 *
 *	The PPP link is disconnected. The GPRS is still enabled. 
 * @return 
 * - GPRS_OK or A negative error code otherwise : 
 * - GPRS_ERR_NO_GPRS
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 18) if function does not exist
// \if SIMULATION
//  @GSIM_F:gprs_stop:KSFAM_GPRS:
// \endif
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
int            gprs_stop(void);


/*! @brief This function is used to get the last error
 * @return 
 * - last error of GPRS driver.
 * - GPRS_OK if none.
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 20) if function does not exist
// \if SIMULATION
//  @GSIM_F:gprs_errno:KSFAM_GPRS:0x10
// \endif
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
unsigned short gprs_errno(void);



/*! @} **/



/*! @addtogroup KSFAM_DLL
	* @{
**/


/*! @brief This function closes library gprslib.
 * @return None
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 30) if function does not exist
// \if SIMULATION
//  @GSIM_F:gprslib_close:KSFAM_DLL:0x10
// \endif
 *
 * @link KSFAM_DLL Back to top @endlink
*/
void           gprslib_close(void);

/*! @} **/

/*! @addtogroup KSFAM_GPRS
	* @{
**/

/*! @brief This function performs the connection to the GPRS network, then initiates a PPP connection. 
 * @param abort_key : Key code to press in order to request the disconnection : 
 * - 0x00 : No key. 
 * - 0x17 : T_ANN : i.e the cancellation key (red key). 
 * - Any other key codes are allowed. 
 *
 * @param *apn : APN 
 * @param *login: PPP login. 
 * @param *password: PPP password. 
 * @param to : Connection timeout (in seconds) 
 *
 * @return
 * - GPRS_OK or a negative error code otherwise :
 * - GPRS_ERR_NO_SIM           
 * - GPRS_ERR_NO_PIN            
 * - GPRS_ERR_SIM_LOCK          
 * - GPRS_ERR_FATAL
 * - GPRS_ERR_UNKNOWN    
 * - GPRS_ERR_CONNECT_TIMEOUT  
 * - GPRS_ERR_PPP      
 * - GPRS_ERR_NO_GPRS   
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 0) if function does not exist
 *
 * An example is available at @ref sub02_GPRS  
 *
 * @note To use the cancellation key facility, the keyboard driver must have been previously opened by the task which performs the call to this function. 
// \if SIMULATION
//  @GSIM_F:gprs_connect:KSFAM_GPRS:
// \endif
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
int            gprs_connect(unsigned char abort_key,char *apn,char *login,char *password,int to);


/*! @brief This function performs a GSM communication. The phone number szPhoneNumber is dialled, and the modulation nModulation is negotiated. 
 * @param *num : Phone number to dial. 
 * @param abort_key : Key code to press in order to request the disconnection :
 * - 0x00 : No key. 
 * - 0x17 : T_ANN : i.e the cancellation key (red key). 
 * - Any other key codes are allowed. 
 *
 * @param data_baudrate : Baudrate modulation. The possible values are : 
 * - DGPRS_GSM_2400_V22BIS     V22Bis (2400 bauds) 
 * - DGPRS_GSM_4800_V32        V32 (4800 bauds) 
 * - DGPRS_GSM_9600_V32        V32 (9600 bauds) 
 * - DGPRS_GSM_2400_V110       V110 - ISDN (2400 bauds) 
 * - DGPRS_GSM_4800_V110       V110 - ISDN (4800 bauds) 
 * - DGPRS_GSM_9600_V110       V110 - ISDN (9600 bauds) 
 *
 * @param data_mode : Activate or deactivate the RLP mode. RLP mode is the native GSM protocol for error detection and correction. In RLP mode, the remote part must support V42 connections .
 * @param to : Connection timeout (in seconds). 
 * @return
 * - GPRS_OK or a negative error code otherwise :
 * - GPRS_ERR_NO_SIM     
 * - GPRS_ERR_NO_PIN       
 * - GPRS_ERR_SIM_LOCK  
 * - GPRS_ERR_FATAL 
 * - GPRS_ERR_UNKNOWN     
 * - GPRS_ERR_NO_GPRS      
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 19) if function does not exist
 *
 * An example is available at @ref sub04_GPRS  
 *
 * @note
 * - To use the cancellation key facility, the keyboard driver must have been previously opened by the task which performs the call to this function. 
 * - The GSM modem does not perform modulation fallbacks. For example, if a V32 (9600 bauds) connection is initiated to a remote modem which only supports V32 (4800 bauds), it fails. 
// \if SIMULATION
//  @GSIM_F:gsm_connect:KSFAM_GPRS:
// \endif
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
int            gsm_connect(char *num,unsigned char abort_key,int data_baudrate,int data_mode,int to);


/*! @brief This functions sends Ln bytes from the Data buffer.
 * @param *Data : Data buffer to be written. 
 * @param Ln : Number of bytes to write. 
 * @return
 * - GPRS_OK or a negative error code otherwise : 
 * - GPRS_ERR_NO_GPRS 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 25) if function does not exist
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:gsm_write:KSFAM_GPRS:0x16
//  @GSIM_A:1:DATA_SIZE(Ln)
// \endif
int            gsm_write(unsigned char *Data,int Ln);


/*! @brief This function reads pnMaxLength bytes from the GSM connection and stores them in the buffer pucData. 
 *
 *	The function returns the number of bytes received through the parameter pnMaxLength. 
 *
 *	This returned size may be less than the requested size pnMaxLength if the timeout expires or if the GSM connection ends. 
 *	The timeout values must be set according to the modulation of the GSM connection. 
 * @param *Data : Storage buffer. Must be allocated by the caller. 
 * @param *Ln : Maximum number of bytes to read. This parameter is set by the number of bytes received. 
 * @param FirstTimeout : Period (in 10 ms) to wait for reception of the first byte. 
 * @param InterTimeout : Maximum period (in 10 milliseconds) to wait between reception of two characters. 
 * @return 
 * - GPRS_OK or a negative error code otherwise : 
 * - GPRS_ERR_NO_GPRS 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 26) if function does not exist
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:gsm_read:KSFAM_GPRS:0x17
//  @GSIM_A:1:DATA_CODE(*Ln) 
//  @GSIM_A:2:ONE_POINTER
// \endif
int            gsm_read(unsigned char *Data,int *Ln,unsigned short FirstTimeout,unsigned short InterTimeout);


/*! @brief This function activates the GPRS communication mode.
 * @param *apn : APN
 * @return
 * - GPRS_OK or a negative error code otherwise :
 * - GPRS_ERR_NO_SIM  
 * - GPRS_ERR_NO_PIN   
 * - GPRS_ERR_BAD_PIN 
 * - GPRS_ERR_SIM_LOCK 
 * - GPRS_ERR_FATAL 
 * - GPRS_ERR_UNKNOWN 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 28) if function does not exist
 *
 * @note 
 * - The GPRS network is not immediately available after calling this function. 
 * - The caller has to wait for its availability before performing any communication. 
// \if SIMULATION
//  @GSIM_F:gprs_enable:KSFAM_GPRS:0x11
// \endif
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
int            gprs_enable(char *apn);


/*! @brief This function activates the GSM communication mode.
 * @param *apn : APN
 * @return GPRS_OK.
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 27) if function does not exist
 * @note
 * - The GSM network is not immediately available after calling this function. 
 * - The caller has to wait for its availability before initiating a communication. 
// \if SIMULATION
//  @GSIM_F:gsm_enable:KSFAM_GPRS:0x12
// \endif
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
int            gsm_enable(char *apn);



/*! @brief This function send an sms to a phone.
* @param *xpTel: phone number of receiver
* @param *xucSMS: sms data
* @return 
*- 0 if OK
* @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 23) if function does not exist
* @note
* - The GSM network is not immediately available after calling this function. The caller has 
* - to wait for its availability before initiating a communication. 
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:gprs_EmissionSMS:KSFAM_GPRS:
// \endif
int            gprs_EmissionSMS( char *xpTel, char *xucSMS);

/*! @brief This function displays a popup window which monitors the input of SIM PIN code.
 *	
 *	This popup window can not be customised, but all its displayed messages can be translated by using the language library. 
 * @return
 * - GPRS_OK.
 * - GPRS_ERR_NO_PIN when the input timeout (20 seconds) expires. 
 * @note
 * - The GPRS network is not immediately available after calling this function.
 * - The caller has to wait for its availability before performing any communication. 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 29) if function does not exist
// \if SIMULATION
//  @GSIM_F:gprs_setpincode:KSFAM_GPRS:0x18
// \endif
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
int            gprs_setpincode(void);

/*! @brief This function displays a popup window which monitors the input of SIM PUK code.
 *	
 *	This popup window can not be customised, but all its displayed messages can be translated by using the language library. 
 * @return
 * - GPRS_OK.
 * - GPRS_ERR_NO_PIN when the input timeout (20 seconds) expires. 
 * - GPRS_ERR_BAD_PUK_CODE when the PUK code is invalid.
 * @note
 * - The GPRS network is not immediately available after calling this function.
 * - The caller has to wait for its availability before performing any communication. 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 29) if function does not exist
// \if SIMULATION
//  @GSIM_F:gprs_setpukcode:KSFAM_GPRS:0x18
// \endif
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
int            gprs_setpukcode(void);


/*! @brief This function sets the PIN code. 
 *	
 *	The given value is taken in account only if the SIM card requests a PIN code entry. 
 *
 *	If this PIN code is correctly presented, it is saved  and automatically presented the next time the SIM card will request a PIN code entry. 
 *	Invalid PIN codes are never stored. 
 * @param val : SIM card PIN code to set. The size of this parameter must be at least 4 digits. 
 * @return
 * - GPRS_OK
 * - a negative error code.
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 54) if function does not exist
// \if SIMULATION
//  @GSIM_F:gprs_submitpincode:KSFAM_GPRS:0x1E
//  @GSIM_A:1:DATA_SIZE(12)
// \endif
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
int            gprs_submitpincode(char *val);



/*! @brief following the param option return the value. 
 *	
 *	The given value is taken in account only if the SIM card requests a PIN code entry. 
 *
 *	If this PIN code is correctly presented, it is saved  and automatically presented the next time the SIM card will request a PIN code entry. 
 *	Invalid PIN codes are never stored. 
 * @param option : SIM card PIN code to set. The size of this parameter must be at least 4 digits. 
 * - GPRS_PARAM_LOGIN
 * - GPRS_PARAM_PASSWORD
 * - GPRS_PARAM_APN
 * - GPRS_PARAM_PIN
 * - GPRS_PARAM_NETWORK
 * @param val : data result
 * @return
 *- GPRS_OK
 *- a negative error code.
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 55) if function does not exist
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:gprs_getParam:KSFAM_GPRS:
//  @GSIM_A:1:DATA_SIZE(12)
// \endif
int            gprs_getParam(int option, char * val);

/*! @brief This function disconnects the current connection to the GPRS network. 
 *
 *	The PPP link is disconnected. The GPRS is still enabled. 
 * @return
 * - GPRS_OK if OK or a negative error code otherwise.
 * - GPRS_ERR_NO_GPRS  
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 31) if function does not exist
// \if SIMULATION
//  @GSIM_F:gprs_ppp_disconnect:KSFAM_GPRS:0x1D
// \endif
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
int            gprs_ppp_disconnect(void);


/*! @brief This function returns the handle of PPP connection.
 * @return handle of PPP connection
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 32) if function does not exist
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:gprs_handle_ppp:KSFAM_GPRS:0x1C
//  @GSIM_A:0:ONE_ADDRESS
// \endif
void *         gprs_handle_ppp(void);


/*! @brief This function is used to check the availability of the network GPRS.
 * @param bGPRS : 
 * @param pbResult : the output parameter 'int *pbResult' receives the network availability status. 
 * @param pError : the output parameter 'int *pError' is set when the network is not operational. It receives the error code. 
 * @param pbLinkPPP : the output parameter 'int *pbLinkPPP' is set to __TRUE__ when the network is operational and the PPP link established. 
 * @return : this function returns __TRUE__ when the network availability is not yet known. 
 *
 * An example is available at @ref sub01_GPRS  
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:gprs_IsNetworkAvailable:KSFAM_GPRS:0x1B
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
// \endif
int            gprs_IsNetworkAvailable( int bGPRS, int *pbResult, int *pError, int *pbLinkPPP );

/*! @brief This function get current GPRS technology (GSM or 3G).
 *	
 * @param pbResult : the output parameter receives the actual technology (GPRS_GSM_TECHNOLOGY , GPRS_3G_TECHNOLOGY).

 * @return
 * - GPRS_OK.
 * - GPRS_ERRNO_DRIVER_NOT_OPEN DGPRS driver not open. 
 * @note
 * - Default value is GPRS_GSM_TECHNOLOGY.
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 56) if function does not exist
 *
 * @link KSFAM_GPRS Back to top @endlink
*/
int            gprs_gettechnology(int *pbResult);


#endif
/*! @} **/
