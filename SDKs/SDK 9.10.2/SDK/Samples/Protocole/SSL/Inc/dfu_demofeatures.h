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
   
 Project : SSL Sample
 Module  : DFU - Demo Features Unit

 @file      dfu_demofeatures.h
 @brief     Contains all exported prototypes of DFU.
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifndef __DFU_H__
#define __DFU_H__

#ifdef __cplusplus
extern "C" {
#endif


/** \addtogroup dfugroup DFU Demo Functions Unit
 *
 * Contains all functions that demonstrates the use of certain features specific
 * to the sample application, the main attraction on the source code of the application.
 *
 * @{
 */

/** Add SSL profile. The name of the profile is automatically generated sequentially.
 * The profiles created are name PROFILE_00...PROFILE_nn where nn is the maximum number 
 * of profiles that can be created inside the terminal.
 */
void DFU_SslProfileAdd(void);

/** Deletes a previously created profile.
 *
 * \param[in] profileName Pointer to the string containing the name of the profile.
 *
 * \return
 *      - \ref EPU_ERR_DFU_SSL_PROFILE_NOT_FOUND = Specified profile is missing.
 *      - \ref EPU_RET_OK = The profile has been successfully deleted.
 */
int DFU_SslProfileDelete(char *profileName);

/** Prints all the SSL profiles residing in the terminal
 */
void DFU_SslProfileListPrint(void);

/** Initiates a connection test to a desired SSL server
 *
 * \param szHostName    The DNS name or IP address of the SSL server to connect to.
 * \param nPort         The port number where the SSL server is listening.
 * \param szProfile     The name of the SSL profile to use.
 *
 * \return
 *      - \ref EPU_RET_OK = Connection test successful
 *      - \ref EPU_ERR_DFU_SSL_CONNECTION_FAILED = Connection to the server was not successful.
 */
int DFU_SslConnectionTest( const char *szHostName, unsigned int nPort, const char *szProfile );

/** Generates the list of SSL profiles residing in the terminal.
 *
 * \param[out] pnNbItems Pointer to an integer variable which will contain the number of SSL 
 *                      profiles found in the terminal.
 * 
 * \return
 *      - NULL when there is no existing profiles in the terminal.
 *      - Array of strings terminated by a NULL pointer. This array contains the names of all
 *        the SSL profiles found.
 *
 * \note
 *      - The array of strings must be freed after using.
 */
char **DFU_SslProfileListConstruct( int *pnNbItems );

/** @} */

#ifdef __cplusplus
}
#endif

#endif // __DFU_H__



