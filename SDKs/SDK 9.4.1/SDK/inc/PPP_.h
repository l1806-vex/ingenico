#ifndef __PPP__H__
#define __PPP__H__

#ifdef __cplusplus
extern "C"
{
#endif

//
//
//! \file        PPP_.h
//! \brief This module contains all the PPP definitions.
//
//
// Copyright (c) 2005 Ingenico France, rue claude Chappe,
// 07503 Guilherand-Granges, France, All Rights Reserved.
//
// Ingenico France has intellectual property rights relating
// to the technology embodied in this software. In particular,
// and without limitation, these intellectual property rights
// may include one or more patents.
//
// This software is distributed under licenses restricting
// its use, copying, distribution, and decompilation.
// No part of this software may be reproduced in any form
// by any means without prior written authorization of
// Ingenico France.
//


//! \addtogroup TCPIP_PPP 
//! @{

#define PPP_TRUE                     ((void*) ~0L)  //!< True value for boolean.
#define PPP_FALSE                    ((void*) 0L)   //!< False value for boolean.
#define PPP_INT( a)                  ((void*) (a))  //!< Macro for integer cast.
#define PPP_PTR( a)                  ((void*) (a))  //!< Macro for pointer cast.

// Connection states.

//! \defgroup PPP_STATES PPP connection states.
//! \brief Connection state returned by the function "PPP_GetState".
//! @{
#define PPP_STATE_DEAD                1             //!< Physical Link is not ready.
#define PPP_STATE_ESTABLISH           2             //!< Physical connection in progress.
#define PPP_STATE_NETWORK             3             //!< Network connection in progress.
#define PPP_STATE_AUTH                4             //!< Authentication in progress.
#define PPP_STATE_TERMINATE           5             //!< Disconnected connection.
#define PPP_STATE_IFUP                6             //!< Successful connection.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Setup profiles.
//! \defgroup PPP_STEUP PPP profiles.
//! \brief Profiles for connection.
//! @{
#define PPP_PERSONAL_PROFILE		    -1            //!< Minimal configuration (Login and Password).
#define PPP_PSTN_PROFILE			    0             //!< Configuration dedicated to PSTN communications.
#define PPP_GPRS_PROFILE			    1             //!< Configuration dedicated to GPRS communications.
#define PPP_PSTN_PROFILE_OBSOLETE	    2             //!< Deprecated.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}



// PPP interface options.
//! \defgroup PPP_OPTIONS PPP options.
//! \brief Options of the PPP interface.
//! @{

//! \cond __EXCLUDE__
#define PPP_INFO_NAME				          0x100
#define PPP_INFO_DRIVER				        0x101
#define PPP_INFO_OUTQ_MAX			        0x102
//! \endcond

#define PPP_INFO_ADDR				        0x103		//!< Local address.
#define PPP_INFO_NETMASK			        0x104		//!< Network mask.
#define PPP_INFO_BRDADDR			        0x105		//!< Broadcast address.
#define PPP_INFO_DSTADDR			        0x106		//!< Destination address.

//! \cond __EXCLUDE__
#define PPP_INFO_FLAGS				        0x107
#define PPP_INFO_ADDMULTI			        0x108
#define PPP_INFO_DELMULTI			        0x109
#define PPP_INFO_MTU				        0x10a
#define PPP_INFO_BPS				        0x10b
#define PPP_INFO_DEV1				        0x10c
#define PPP_INFO_DEV2				        0x10d
#define PPP_INFO_DEVPTR1			        0x10e
#define PPP_INFO_DEVPTR2			        0x10f
#define PPP_INFO_PROMISC			        0x110
#define PPP_INFO_ALLMULTI			        0x111
//! \endcond

#define PPP_INFO_DEFAULT_ROUTE		    0x301         //!< Default route after connection.
#define PPP_INFO_PASSIVE			        0x302         //!< Wait peer answer.
#define PPP_INFO_SILENT				        0x303         //!< Wait peer initiative.
#define PPP_INFO_RESTART			        0x304         //!< Interface cannot be halted.
#define PPP_INFO_TERM_MAX			        0x307         //!< Maximum number of terminate request.
#define PPP_INFO_CONFIG_MAX			      0x308         //!< Maximum number of config request.
#define PPP_INFO_FAIL_MAX			        0x309         //!< Maximum number of config Nack.
#define PPP_INFO_RESTART_MAX		      0x310         //!< Retrans. timeout.
#define PPP_INFO_RESOLVER			        0x311         //!< Setup resolver (DNS1 and DNS2).
#define PPP_INFO_LCP_ACOMP			      0x320         //!< Address and control fields compression.
#define PPP_INFO_LCP_PCOMP			      0x321         //!< Protocol fields compression.
#define PPP_INFO_LCP_MAGIC			      0x322         //!< Magic number negotiation.
#define PPP_INFO_LCP_MRU			        0x323         //!< Set maximum receive unit.
#define PPP_INFO_LCP_ASYNC			      0x324         //!< Negotiate async map table.
#define PPP_INFO_LCP_AUTH			        0x326         //!< Set when peer auth. requested.
#define PPP_INFO_LCP_PAP			        0x327         //!< PAP may be activated.
#define PPP_INFO_LCP_CHAP			        0x328         //!< CHAP may be activated (idem).
#define PPP_INFO_CHAP_PERIOD		      0x329         //!< CHAP challenge period (in sec).
#define PPP_INFO_LCP_MSCHAP1		      0x32a         //!< MS-CHAPv1 may be activated (idem).
#define PPP_INFO_LCP_MSCHAP2		      0x32b         //!< MS-CHAPv2 may be activated (idem).
#define PPP_INFO_MSCHAP_STYPE		      0x32c         //!< MS-CHAP peer secret type.
#define PPP_INFO_IPCP_ADDR			     0x330         //!< IP addresses negotiation.
#define PPP_INFO_IPCP_ACCEPT_LOCAL	  0x331         //!< Accept peer's address.
#define PPP_INFO_IPCP_ACCEPT_REMOTE	  0x332         //!< Accept peer's dst. address.
#define PPP_INFO_IPCP_VJCOMP		      0x333         //!< Negotiate VJ IP header compression.
#define PPP_INFO_IPCP_VJTABLE		      0x334         //!< NGpppvjent table for compression.
#define PPP_INFO_IPCP_VJMAX			      0x335         //!< Number of element in previous table.
#define PPP_INFO_IPCP_DNS1			      0x336         //!< Negotiate Primary DNS.
#define PPP_INFO_IPCP_DNS2			      0x337         //!< Negotiate Secondary DNS.
#define PPP_INFO_IPCP_DNS1_ADDR		    0x344         //!< Set/get Primary DNS address.
#define PPP_INFO_IPCP_DNS2_ADDR		    0x345         //!< Set/get Secondary DNS address.
#define PPP_INFO_AUTH_USER			      0x338         //!< User and password.
#define PPP_INFO_AUTH_SECRET		      0x339         //!< CHAP/PAP Authentication.
#define PPP_INFO_AUTH_HOST			      0x340         //!< CHAP/PAP Authentication.
#define PPP_INFO_CB_AUTH			        0x341         //!< Authentication callback.
#define PPP_INFO_CB_CONNECT			      0x342         //!< Connection Callback.
#define PPP_INFO_CB_DISCONNECT		    0x343         //!< Disconnection Callback.
#define PPP_INFO_CB_LINK			        0x346         //!< Link transitions callback.
#define PPP_INFO_CB_DATA			        0x347         //!< User data.
#define PPP_INFO_ECHO				          0x348         //!< Enable/disable echo requets.
#define PPP_INFO_ECHO_PERIOD		      0x349         //!< Period between request (sec).
#define PPP_INFO_ECHO_MAX			        0x34a         //!< Maximum number of reply before closing link.

#define PPP_INFO_USE_ROUTE            0x1000        //!< PPP interface selection.
#define PPP_INFO_GATEWAY		          0x1001        //!< Gateway address.
#define PPP_INFO_DNS1				          0x1002        //!< DNS1 address.
#define PPP_INFO_DNS2				          0x1003        //!< DNS2 address.

//! @}

//
//! \brief Definition of PPP_HANDLE
typedef void *PPP_HANDLE;


//! \brief This function opens a connection through a communication port 
//! (physical link). The communication port must be previously opened. 
//! The function returns only an handle on the connection.
//! \param szComPort : Communication port name (for example : 'COM1'...).
//! \return
//! - NULL in case of error.
//! - The connection handle otherwise.
PPP_HANDLE PPP_Open( const char *szComPort );

//! \brief This function closes a connection. It releases all its allocated resources.
//! \param handle : PPP connection handle.
//! \return 
//! - 0 if OK.
//! - A negative error code otherwise.
int PPP_Close( PPP_HANDLE handle );

//! \brief This function configures the parameters of a connection..
//! \param handle : PPP connection handle.
//! \param szLogin : PPP user name.
//! \param szPassword : PPP password.
//! \param profile : Connection profile.
//! \return 
//! - 0 if OK
//! - A negative error code otherwise.
//! \note
//! Several common connection modes are possible. They are defined by a specific profile :
//! - \ref PPP_PERSONAL_PROFILE
//! - \ref PPP_PSTN_PROFILE
//! - \ref PPP_GPRS_PROFILE

int PPP_Setup( PPP_HANDLE handle, 
			   const char *szLogin,
			   const char *szPassword, int profile );

//! \brief This function starts the connection (e.g. : . the PPP negotiation).
//! \param handle : PPP connection handle.
//! \return 
//! - 0 if OK.
//! - A negative error code otherwise.
int PPP_Start( PPP_HANDLE handle );

//! \brief This function stops the connection (e.g. : it disconnect it), but it do not close the connection.
//! \param handle : PPP connection handle.
//! \return 
//! - 0 if OK.
//! - A negative error code otherwise.
int PPP_Stop( PPP_HANDLE handle );

//! \brief This function waits until the connection has reached the given state. 
//! It exits also, with an error, when the 'nStateExit' has been reached or when the waiting timeout expires.
//! \param handle : PPP connection handle.
//! \param nWaitState : Waited state.
//! \param nStateExit : Exit State.
//! \param nTimeout : Maximum timeout for waiting.
//! \return 
//! - 0 if OK.
//! - A negative error code otherwise.
// \endif
int PPP_WaitState( PPP_HANDLE handle, int nWaitState, int nStateExit, 
				   unsigned long nTimeout );
//! @}

//! \brief This function returns the state of the connection.
//! \param handle : PPP connection handle.
//! \return PPP connection state : 
//! - \ref PPP_STATE_DEAD
//! - \ref PPP_STATE_ESTABLISH
//! - \ref PPP_STATE_NETWORK
//! - \ref PPP_STATE_AUTH
//! - \ref PPP_STATE_TERMINATE
//! - \ref PPP_STATE_IFUP
int PPP_GetState( PPP_HANDLE handle );
//! @}


//! \brief This function gets the current value of an option parameter of a connection.
//! \param handle : PPP connection handle.
//! \param opt : Option to get.
//! \param arg : Value.
//! \return 
//! - 0 if OK.
//! - A negative error code otherwise.
int PPP_GetOption( PPP_HANDLE handle, int opt, void *arg );

//! \brief This function sets an option parameter of a connection..
//! \param handle : PPP connection handle.
//! \param opt : Option to set.
//! \param arg : Value.
//! \return 
//! - 0 if OK.
//! - A negative error code otherwise.
int PPP_SetOption( PPP_HANDLE handle, int opt, void *arg );

//! \brief This function restore all the options of the connection to their default values.
//! \param handle : PPP connection handle.
//! \return 
//! - 0 if OK.
//! - A negative error code otherwise.
int PPP_SetDefaultOptions( PPP_HANDLE handle );

//


//! \brief This function establishes a PPP connection through a communication 
//! port. It performs all the process of the connection.
//! \param szComPort : Communication port name (for example : 'COM1', 'COM6'...).
//! \param szLogin : PPP user name.
//! \param szPassword : PPP password.
//! \param nProfile : Connection profile.
//! \param nDelay : Polling delay (in 10 ms).
//! \param nTimeout : Maximum waiting delay (in 10 ms).
//! \return 
//! - The connection handle (>=0).
//! - A negative error code otherwise.
//! \note
//! Several common connection modes are possible. Please refer to the 
//! function 'PPP_Setup' to know the different profiles. The polling delay must be lower than the timeout delay. It indicates the delay to verify periodically the state of the connection.
PPP_HANDLE PPP_Connect( const char *szComPort,
						const char *szLogin, const char *szPassword,
						int nProfile,
						unsigned int nDelay,  /* in 10 ms */
						unsigned int nTimeout /* in 10 ms */ );
//! @}


//! \defgroup PPP_SAMPLE	PPP samples
//! \ingroup TCPIP_SAMPLES
//! @{
//! \defgroup PPP_SAMPLE_CONNECTION		PPP connection over GSM.
//! \ingroup PPP_SAMPLE
//! \brief  The following code shows how to perform a PPP connection through the GSM link. 
//! Just call the following function after connecting the PSTN in GSM.
//! \include PPP__Sample_01.c
//! \example PPP__Sample_01.c
//! @{
//! @}
//! \defgroup PPP_SAMPLE_CONF Get information about a PPP link.
//! \ingroup PPP_SAMPLE
//! \brief The following code shows how the user can accurately set PPP configuration.
//! \include PPP__Sample_02.c
//! \example PPP__Sample_02.c
//! @{
//! @}
//! @}

#ifdef __cplusplus
}
#endif


#endif // __PPP__H__

