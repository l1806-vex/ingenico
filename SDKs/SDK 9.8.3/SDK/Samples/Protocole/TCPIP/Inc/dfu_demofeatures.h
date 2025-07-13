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
   
 Project : TCP/IP Sample
 Module  : DFU - Demo Features Unit

 @file      dfu_demofeatures.h
 @brief     Contains all exported prototypes of DFU.
 @date      17/09/2012

 ------------------------------------------------------------------------------
 */

#ifndef __DFU_H__
#define __DFU_H__

/** \addtogroup dfugroup DFU Demo Functions Unit
 *
 * Contains all functions that demonstrates the use of certain features specific
 * to the sample application, the main attraction on the source code of the application.
 *
 * @{
 */

/** Display network information
 * It displays the Ethernet parameters of the terminal.
 * The Local Address will be displayed followed by the Netmask
 *
 */
void DFU_ComNetInfoDisplay(void);

/** Launch a HTTP Server
 *
 * It will perform the following tasks:
 * - Create a listening socket (comStart())
 * - Bind/assigning a name to a socket (comSetServer())
 * - Wait for incoming connections
 * - Accept Incoming connection
 * - Receive messages from the socket (from the client socket)
 * - Transmit messages to another socket (to the client socket)
 * - Close the socket connection
 *
 * \return
 *    - 0 if OK. 
 *    - negative if failure.
 */
int DFU_ComServerStart(void);

/** Connect to a HTTP Server
 *
 It will perform the following tasks:
 * - Create a listening socket (comStart())
 * - Set the address and port of the server to connect to (comSetClient())
 * - Connect to a socket server (comConnect())
 * - Transmit messages to the server
 * - Receive messages from the server
 * - Close the socket connection
 *
 * \param host (I) host address.
 * \param hostPort (I) port to use.
 * \param trm (I) host address terminator. 
 * \return
 *    - number of bytes received from server. 
 *    - negative if failure.
 */
int DFU_ComClientConnect(const char *host, unsigned int port, const char *trm);

/** @} */
#endif // __DFU_H__



