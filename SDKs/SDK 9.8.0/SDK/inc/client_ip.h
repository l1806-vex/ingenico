/*! @addtogroup KSFAM_TCP
	* @{

  * @section sub03_TCP TCP Communication
  *
  * The following example performs a TCP connection to an HTTP server. 
  *
  * It requests the WEB page and waits for the disconnection from the server.
  *

 * @include client_ip_Sample_01.c
*/



/*
======================================================================
					List of Defines
======================================================================
*/

#ifndef _CLIENT_IP_H_INCLUDED_
#define _CLIENT_IP_H_INCLUDED_

#define NO_ERROR         0	/*!< no error*/
#define ERROR_SOCKET    -1	/*!< error when creating the socket*/
#define ERROR_CONNECT   -2	/*!< Error connecting to server*/
#define ERROR_TIMEOUT   -3 	/*!< timeout during a transmission or reception*/


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function performs a connection to a TCP server. 
 *	
 *	The GPRS network must be enabled and connected. 
 * @param *address : TCP server address. This address must be a resolved address (ex : 217.12.3.11). 
 * @param tcp_port : TCP server port. 
 * @param timeout : Timeout connection in 10 milliseconds. This value must not be set to 0. 
 * @return
 * - The connection handle (>=0).
 * - Negative error code :
 * - Error Code     Description 
 * - ERROR_SOCKET   Error in creation of the internal TCP descriptor(socket). 
 * - ERROR_CONNECT  Connection error. The server can not be reached (its address or its port may be invalid). 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 10) if function does not exist
 *
 * An example is available at @ref sub03_TCP  
 *
 * @link KSFAM_TCP Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:tcp_connect_to_server:KSFAM_TCP:0x01
// \endif
int tcp_connect_to_server(char *address, int tcp_port, int timeout);



/*! @brief This function sends length bytes from the data buffer. 
 *
 *	It returns the total number of sent bytes. This returned size may be less than the requested size if the timeout expires or if the TCP connection ends. 
 * @param connect_result : TCP connection handle. 
 * @param *data : Data buffer to be written. 
 * @param length : Number of bytes to write. 
 * @param timeout : Maximum blocking period (in 10 milliseconds). This function is blocking if the internal sending 
   buffer is full. The timeout value must not be set to 0. 
 * @return
 * - The number of bytes sent if OK.
 * - A negative error code otherwise : 
 * - Error Code      Description 
 * - ERROR_TIMEOUT   Timeout expired. 
 * - 0               The TCP connection is ended. 
 * - >0           The total of bytes sent. 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 12) if function does not exist
 *
 * @link KSFAM_TCP Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:tcp_send_to_server:KSFAM_TCP:0x02
//  @GSIM_A:2:DATA_SIZE(length)
// \endif
int tcp_send_to_server(int connect_result, unsigned char *data, int length, int timeout);



/*! @brief This function reads nMaxLength bytes from the TCP connection and stores them in the buffer data.
 *	
 *	The function returns the number of bytes received. The returned size may be less than the requested size nMaxLength if the timeout expires or if the TCP connection ends. 
 * @param connect_result : TCP connection handle. 
 * @param *data : Storage buffer. Must be allocated by the caller. 
 * @param max_length : Maximum number of bytes to read. 
 * @param timeout : Maximum blocking period (in 10 milliseconds). If this value is set to 0, the function is not blocking, it returns immediately the data already received and stored in the internal buffers. 
 * @return
 * - The number of bytes received if OK.
 * - A negative error code otherwise :
 * - Error Code      Description 
 * - ERROR_TIMEOUT   Timeout expired. 
 * - 0               The TCP connection is ended. 
 * - >0           The number of received data and stored in the data buffer. 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 14) if function does not exist
 *
 * @link KSFAM_TCP Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:tcp_recv_from_server:KSFAM_TCP:0x03
//  @GSIM_A:2:DATA_SIZE(max_length)
// \endif
int tcp_recv_from_server(int connect_result, unsigned char *data, int max_length, int timeout);



/*! @brief This function requests a TCP disconnection. 
 *
 *	It must be called to terminate all the TCP/IP connections (even if the disconnection is initiated by the remote part). 
    Indeed, this function releases the internal TCP/IP resources used for the connection. 
 *
 *	The GPRS network is still connected and the PPP connection is maintained. 
 * @param connect_result : TCP connection handle.
 * @return Always 0. The TCP connection is disconnected..
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 16) if function does not exist
 *
 * @link KSFAM_TCP Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:tcp_disconnect_from_server:KSFAM_TCP:0x04
// \endif
int tcp_disconnect_from_server(int connect_result);


#endif
/*! @} **/

