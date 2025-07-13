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
 Module  : FUN - Functional Demo Unit

 @file      fun.h
 @brief     Contains all exported prototypes of FUN.
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#ifndef __FUN_H__
#define __FUN_H__

/** \addtogroup dfugroup FUN Functional Demo Unit
 * \brief
 * Contains all functions that demonstrates the use of certain features specific
 * to the sample application, the main attraction on the source code of the application.
 * \brief
 * @{
 */

/** \weakgroup dfugroupgprs FUN GPRS
 *
 * @{
 */

/** Activates the GPRS communications module.
 *
 * \param[in] apn   Null terminated pointer to the GPRS network's APN.
 * \return
 *      - \ref ERR_RET_OK = GPRS network successfully activated.
 *      - \ref ERR_FUN_GPRS_NO_SIM = SIM card is missing or cannot be detected.
 *      - \ref ERR_FUN_GPRS_NO_PIN = PIN Code of the card is required.
 *      - \ref ERR_FUN_GPRS_BAD_PIN = Invalid PIN provided when PIN was asked.
 *      - \ref ERR_FUN_GPRS_SIM_LOCK = SIM card is locked.
 *      - \ref ERR_FUN_GPRS_FATAL = The GPRS module encountered a FATAL error.
 *      - \ref ERR_FUN_GPRS_NETWORK_UNAVAILABLE = There is no GPRS facility available.
 *      - \ref ERR_FUN_GPRS_UNKNOWN = The SIM card is not ready.
 */
int FUN_GprsActivate( char *apn );

/** Deactives the GPRS network currently in used including any active
 * PPP connection.
 * 
 * \return
 *      - \ref ERR_RET_OK = Deactivation was successful.
 *      - \ref ERR_FUN_GPRS_NETWORK_UNAVAILABLE = There is no GPRS facility available.
 */
int FUN_GprsDeactivate( void );

/** @} */

/** \weakgroup dfugroupppp FUN PPP
 *
 * @{
 */

/** Establishes a PPP connection via an activated GPRS network.
 *
 * \param[in] login     The pointer to the login name. It can be NULL if the
 *                      GPRS network provides none.
 * \param[in] password  The pointer to the password associated with the login
 *                      name. It can be NULL if the GPRS network provides none.
 *
 * \return
 *      - \ref ERR_RET_OK = GPRS network successfully activated.
 *      - \ref ERR_FUN_GPRS_NO_SIM = SIM card is missing or cannot be detected.
 *      - \ref ERR_FUN_GPRS_NO_PIN = PIN Code of the card is required.
 *      - \ref ERR_FUN_GPRS_BAD_PIN = Invalid PIN provided when PIN was asked.
 *      - \ref ERR_FUN_GPRS_SIM_LOCK = SIM card is locked.
 *      - \ref ERR_FUN_GPRS_FATAL = The GPRS module encountered a FATAL error.
 *      - \ref ERR_FUN_GPRS_NETWORK_UNAVAILABLE = There is no GPRS facility available.
 *      - \ref ERR_FUN_GPRS_UNKNOWN = The SIM card is not ready.
 *      - \ref ERR_FUN_PPP_CONNECT_FAILED = PPP Connection failed.
 *      - \ref ERR_FUN_PPP_AUTH_TIMEOUT = Authentication timed out.
 *      - \ref ERR_FUN_PPP_AUTH_FAILED = Authentication failed. It could be invalid
 *             login details.
 *
 * \note
 *      - The \ref FUN_GprsActivate() function should be called first before
 *        calling this function.
 */
int FUN_PppConnect( char *login, char *password );

/** Disccnnects the current PPP connection.
 * 
 * \return
 *      - \ref ERR_RET_OK = Deactivation was successful.
 *      - \ref ERR_FUN_GPRS_NETWORK_UNAVAILABLE = There is no GPRS facility available.
 */
int FUN_PppDisconnect( void );

/** @} */


/** \weakgroup dfugroupgsm FUN GSM
 *
 * @{
 */

/** Performs the GSM connectivity tests.
 *
 * \return
 *      - \ref ERR_RET_OK = Connectivity tests OK
 */
int FUN_GsmConnectionTest( char *szPhoneNumber, int baud, int bRLP );

/** @} */

/** \weakgroup dfugrouptcpip FUN TCP/IP
 *
 * @{
 */

/** Performs the TCP/IP connectivity tests over an established PPP connection
 * via the GPRS network.
 *
 * \return
 *      - \ref ERR_RET_OK = Connectivity tests OK.
 */
int FUN_TcpIpTransceive( char *host, int port );

/** @} */


/** @} */
#endif // __FUN_H__



