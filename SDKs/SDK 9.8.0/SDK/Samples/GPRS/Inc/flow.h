/*!
 ------------------------------------------------------------------------------
                  INGENICO Technical Software Department 
 ------------------------------------------------------------------------------
 Copyright (c) 2012, Ingenico.
 28-32 boulevard de Grenelle 75015 Paris, France.
 All rights reserved.

  This source program is the property of INGENICO Company and may not be copied
  in any form or by any means, whether in part or in whole, except under license
  expressly granted by INGENICO company 
  
  All copies of this program, whether in part or in whole, and
  whether modified or not, must display this and all other	
  embedded copyright and ownership notices in full.
 ------------------------------------------------------------------------------
   
 Project : GPRS Sample
 Module  : FLOW - Process Handling Unit

 @file      flow.h
 @brief     Contains all functions prototypes for FLOW that executes processes 
            specific to the sample application. These processes may include but
            not limited to configuration of parameters, demo process, and so
            on.
            
 @date      16/10/2012

 ------------------------------------------------------------------------------
 */

#ifndef __FLOW_H__
#define __FLOW_H__


#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup phugroup FLOW Process Handling Unit
 *
 * Contains all functions related to the handling of parameters of the sample application. 
 * This interfaces the functions that treats data in the file system of the terminal.
 * It maintains variables that holds the values the application parameters in RAM. 
 * It saves and retrieves contents of the parameter file whenever there are changes.
 *
 * @{
 */

/** Executes the parameter configuration process which will obtain the APN
 * to connect to when executing the GPRS functionality of the sample
 * application.
 */
void FLOW_ParamConfigGprsProcess( void );

/** Executes the parameter configuration process which will obtain the login
 * and password to initiate a PPP connection using the GPRS network
 */
void FLOW_ParamConfigPppProcess( void );

/** Executes the parameter configuration process which will obtain the host name and
 * port number to initiate a TCP connection using the GPRS network
 */
void FLOW_ParamConfigTcpProcess( void );

/** Executes the parameter configuration process which will obtain the phone number,
 * baud rate and to activate or deactivate the RLP mode to perform a GSM communication
 */
void FLOW_ParamConfigGsmProcess( void );

/** Activates the GPRS communication mode. After the activation
 * the network is not immediately available, the function will wait and
 * check the availability of the network.
 */
void FLOW_GprsActivationProcess( void );

/** Deactivates the GPRS communication mode. The current connection 
 * to the GPRS network is disconnected.
 */
void FLOW_GprsDeactivationProcess( void );

/** Performs the connection to the GPRS network and initate a PPP connection
 */
void FLOW_PppConnectionProcess( void );
 
/** Performs the disconnection from the current GPRS network.
 * The PPP link will be disconected but the GPRS communication mode will still
 * be activated
 */
void FLOW_PppDisconnectionProcess( void );

/** Executes the TCP tests using the GPRS Network.
 * First it will perform a connection to a TCP server.
 * If sucessful, it will perform sending of a sample data and
 * wait for a response from the server.
 * Lastly, the it will terminate the TCP connection
 */
void FLOW_TcpTransceive( void );

/** Executes the GSM tests.
 * First it will perform a GSM communication by dialing the phone number
 * and negotiate the modulation.
 * If sucessful, it will perform sending of a sample data and
 * wait for a response.
 * Lastly, the it will disconnect the current connection to the network
 */
void FLOW_GsmConnectionProcess( void );

/** @} */

#ifdef __cplusplus
}
#endif

#endif // __PARAM_H__

