
//! \file        IP_.h
//! \brief This module contains all the standard TCP/IP definitions.
//!
// Copyright (c) 2005 Ingenico France, rue claude Chappe,
// 07503 Guilherand-Granges, France, All Rights Reserved.
//
// Ingenico France has intellectual property rights relating
// to the technology embodied in this software.  In particular,
// and without limitation, these intellectual property rights
// may include one or more patents.
//
// This software is distributed under licenses restricting
// its use, copying, distribution, and decompilation.
// No part of this software may be reproduced in any form
// by any means without prior written authorization of
// Ingenico France.
//
//
//! \addtogroup TCPIP
//! @{
//! \par Introduction
//! The package IP is a static library (named "IP_.lib") which makes easier the development of
//! Internet programs for EFT POS terminals. This library is static (it must be linked with the
//! application). It is compiled with the three compilers (GCC, RVD and SDT) supported by the
//! Telium SDK. Its interface is composed of several API header files : <IP_.h >, <SMTP_.h>,
//! <PPP_.h>, <POP3_.h>.and <HTTP_.h>.
//! The package provides all the services to perform Internet communications. Its main facilities
//! are :
//! - IP communications. BSD interface. Client and server. TCP/IP. UDP.
//! - PPP Management.
//! - Ethernet Management.
//! - DNS Resolver.
//! - SMTP and POP3 email services.
//! - HTTP server facility
//! - ...
//!
//! <TABLE border="3" cellspacing="0" bordercolor="black">
//! <TR><TD></TD></TR>
//! <TR><TD><b>Developers shall read the document <a href="ICO-PE-045-GU-EN_PackIP_SecurityGuidance_UserGuide.html">[Pack IP Security Guidance]</a>
//! which describes best practises for implementing IP enabled applications, according to
//! the requirements of the POS Terminal Security Program (PTS) and of the PCI PTS v3 "Open Protocols" module.</b></TD></TR>
//! <TR><TD></TD></TR>
//! </TABLE>
//!
//! The header file <IP_.h> regroups mainly the standard BSD definitions. This document does not
//! explain these functions. It describes the specific functions, particularly the ones of the interface
//! of the integrated protocols PPP, HTTP, POP3 and SMTP.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

#ifndef __IP__H__
#define __IP__H__

#ifdef __cplusplus
extern "C"
{
#endif


//! \defgroup IP_ERROR_CODES BSD Error codes
//! \brief Error codes returned by BSD API functions  (errno).
//! \ingroup IP_BSD
//! @{

#define __EOK               0   //!< No error
#define __E2BIG            -1   //!< Argument list too long
#define __EACCES           -2   //!< Permission denied
#define __EADDRINUSE       -3   //!< Address already in use
#define __EADDRNOTAVAIL    -4   //!< Address not available from this host
#define __EAFNOSUPPORT     -5   //!< Address family not supported
#define __EAGAIN           -6   //!< Resource temporarily unavailable
#define __EALREADY         -7   //!< Operation already in progress
#define __EAUTH            -8   //!< Authentication error
#define __EBADF            -9   //!< Bad descriptor
#define __EBUSY            -10  //!< Resource busy
#define __ECHILD           -11  //!< No child process
#define __ECONNABORTED     -12  //!< Connection aborted by user
#define __ECONNREFUSED     -13  //!< Connection refused
#define __ECONNRESET       -14  //!< Connection reseted by peer
#define __EDEADLK          -15  //!< Resource deadlock avoided
#define __EDESTADDRREQ     -16  //!< Destination address required
#define __EDOM             -17  //!< Value out of range
#define __EEXIST           -18  //!< File exists
#define __EFAULT           -19  //!< Bad address
#define __EFBIG            -20  //!< File too big
#define __EHOSTDOWN        -21  //!< Host down
#define __EHOSTUNREACH     -22  //!< Host unreachable
#define __EIDRM            -23  //!< Identifier removed
#define __EINPROGRESS      -24  //!< Operation now in progress
#define __EINTR            -25  //!< Interrupted function call
#define __EINVAL           -26  //!< Invalid argument
#define __EIO              -27  //!< Input/output error
#define __EISCONN          -28  //!< Already connected
#define __EISDIR           -29  //!< Is a directory
#define __ELOOP            -30  //!< Too many levels of symbolic links
#define __EMFILE           -31  //!< Out of descriptors
#define __EMLINK           -32  //!< Too many links
#define __EMSGSIZE         -33  //!< Message too big
#define __ENEEDAUTH        -34  //!< Need authenticator
#define __ENETDOWN         -35  //!< Network down
#define __ENETRESET        -36  //!< Network dropped connection on reset
#define __ENETUNREACH      -37  //!< Network unreachable
#define __ENFILE           -38  //!< Too many open files in system
#define __ENOBUFS          -39  //!< Out of resources
#define __ENODEV           -40  //!< Device not found
#define __ENOENT           -41  //!< No such file or directory
#define __ENOEXEC          -42  //!< Exec format error
#define __ENOLCK           -43  //!< No locks available
#define __ENOMEM           -44  //!< Cannot allocate memory
#define __ENOMSG           -45  //!< No message of desired type
#define __ENOPROTOOPT      -46  //!< Not a valid protocol option
#define __ENOSPC           -47  //!< Not enough space to create object
#define __ENOSYS           -48  //!< Function not implemented
#define __ENOTBLK          -49  //!< Block device required
#define __ENOTCONN         -50  //!< Socket not connected
#define __ENOTDIR          -51  //!< Not a directory
#define __ENOTEMPTY        -52  //!< Directory not empty
#define __ENOTSOCK         -53  //!< Not a socket descriptor
#define __ENOTTY           -54  //!< Not a tty
#define __ENXIO            -55  //!< Device not configured
#define __EOPNOTSUPP       -56  //!< Operation not supported
#define __EPERM            -57  //!< Operation not permitted
#define __EPFNOSUPPORT     -58  //!< Protocol family not supported
#define __EPIPE            -59  //!< Pipe broken
#define __EPROTONOSUPPORT  -60  //!< Protocol not supported
#define __EPROTOTYPE       -61  //!< Wrong protocol type
#define __ERANGE           -62  //!< Result too large
#define __EROFS            -63  //!< Read-only file system
#define __ESHUTDOWN        -64  //!< Can't send after shutdown
#define __ESOCKTNOSUPPORT  -65  //!< Socket type not supported
#define __ESPIPE           -66  //!< Illegal seek
#define __ESRCH            -67  //!< No such process
#define __ETIMEDOUT        -68  //!< Connection timed out
#define __ETOOMANYREFS     -69  //!< Too many references
#define __EWOULDBLOCK      __EAGAIN  //!< Operation would block
#define __EXDEV            -70  //!< Cross-device link
#define __ENAMETOOLONG     -71  //!< Component of the path name too long
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \ingroup IP_BSD
//! @{

#ifdef __FRAMEWORK_TELIUM_PLUS__

#include "IP_TPlus.h"

#else

	#include "IP_Deprecated.h"

#endif // __FRAMEWORK_TELIUM_PLUS__

//! @}

#ifdef __FRAMEWORK_TELIUM_PLUS__

//! \defgroup DNS_OPTIONS DNS resolver options.
//! \brief DNS resolver options.
//! \ingroup IP_DNS
//! @{

#define RSLVO_SERV1_IPADDR  0x0501  //!< Primary DNS server IP Address.
#define RSLVO_SERV2_IPADDR  0x0503  //!< Secondary DNS server IP Address.
#define RSLVO_DOMAIN        0x0505  //!< Resolver domain name (max length = 32). ex: ResolverSetOption(RSLVO_DOMAIN, &string);
#define RSLVO_SERV1_PORT    ERROR_Deprecation_For_Module_PACKIP_SeeDocumentation_In_CHM_File
#define RSLVO_SERV2_PORT    ERROR_Deprecation_For_Module_PACKIP_SeeDocumentation_In_CHM_File
#define RSLVO_QUERY_MAX     ERROR_Deprecation_For_Module_PACKIP_SeeDocumentation_In_CHM_File
#define RSLVO_QUERY         ERROR_Deprecation_For_Module_PACKIP_SeeDocumentation_In_CHM_File
#define RSLVO_SEM           ERROR_Deprecation_For_Module_PACKIP_SeeDocumentation_In_CHM_File
#define RSLVO_CACHE_MAX     ERROR_Deprecation_For_Module_PACKIP_SeeDocumentation_In_CHM_File
#define RSLVO_CACHE_ENT     ERROR_Deprecation_For_Module_PACKIP_SeeDocumentation_In_CHM_File
#define RSLVO_HOST_MAX      ERROR_Deprecation_For_Module_PACKIP_SeeDocumentation_In_CHM_File
#define RSLVO_HOST_ENT      ERROR_Deprecation_For_Module_PACKIP_SeeDocumentation_In_CHM_File
#define RSLVO_TO            ERROR_Deprecation_For_Module_PACKIP_SeeDocumentation_In_CHM_File
#define RSLVO_RMITMAX       ERROR_Deprecation_For_Module_PACKIP_SeeDocumentation_In_CHM_File
#define RSLVO_SWITCHMAX     ERROR_Deprecation_For_Module_PACKIP_SeeDocumentation_In_CHM_File

//! @}

#else

//! \defgroup DNS_OPTIONS DNS resolver options.
//! \brief DNS resolver options.
//! \ingroup IP_DNS
//! @{

#define RSLVO_SERV1_IPADDR  0x0501  //!< Primary DNS server IP Address.
#define RSLVO_SERV1_PORT    0x0502  //!< Primary DNS server UDP port number.
#define RSLVO_SERV2_IPADDR  0x0503  //!< Secondary DNS server IP Address.
#define RSLVO_SERV2_PORT    0x0504  //!< Secondary DNS server UDP port number.
#define RSLVO_DOMAIN        0x0505  //!< Resolver domain name (max length = 32). ex: ResolverSetOption(RSLVO_DOMAIN, &string);
#define RSLVO_QUERY_MAX     0x0510  //!< Size of next 2 tables.
#define RSLVO_QUERY         0x0511  //!< Table for pending DNS queries.
#define RSLVO_SEM           0x0512  //!< Semaphore tables for sync API calls in RTOS mode.
#define RSLVO_CACHE_MAX     0x0513  //!< Size of next table. 
#define RSLVO_CACHE_ENT     0x0514  //!< Table for cached DNS entries.
#define RSLVO_HOST_MAX      0x0515  //!< Size of next table.
#define RSLVO_HOST_ENT      0x0516  //!< Table for static host entries.
#define RSLVO_TO            0x0517  //!< Timeout for queries (in milli seconds).
#define RSLVO_RMITMAX       0x0518  //!< Number of retries before switching server.
#define RSLVO_SWITCHMAX     0x0519  //!< Number of switch before aborting queries.

//! @}

#endif // __FRAMEWORK_TELIUM_PLUS__

// Common returned codes (not error codes...)
//! \defgroup DNS_ERROR_CODES Resolver error codes.
//! \ingroup IP_DNS
//! \brief Error codes returned by DNS resolving functions.
//! Please refer RFC 2553 sect 6.2.
//! @{

#define __EDNS_OK              __EOK    //!< No error.
#define __EDNS_WOULDBLOCK      -1000

// Error code from RFC 2553 sect 6.2.
#define __EDNS_HOST_NOT_FOUND  -1001	//!< The host name was not found during the DNS lookup.
#define __EDNS_NO_ADDRESS      -1002    //!< No address is available.
#define __EDNS_NO_RECOVERY     -1003	//!< Unrecoverable error.
#define __EDNS_TRY_AGAIN       -1004	//!< Try again.
#define __EDNS_PROTO_SHUTDOWN  -1006
#define __EDNS_TIMEDOUT        -1007	//!< Error because the request timed out during the DNS lookup.

//! @}

//! \defgroup DNS_ERROR DNS error codes.
//! \ingroup IP_DNS
//! \brief Error codes returned by \ref DNS_GetIpAddress and \ref DNS_GetDomainName functions.
//! @{

#define DNS_OK                         ( 0) //!< No error.
#define DNS_BAD_PARAMETER              (-1) //!< At least one input parameter is invalid.
#define DNS_OUTPUT_BUFFER_TOO_SHORT    (-2) //!< Buffer is too short.
#define DNS_HOST_NOT_FOUND             (-3) //!< DNS request failed.

//! @}

//! \ingroup IP_DNS
//! @{

//! \brief This function gets an option parameter of the DNS resolver.
//! \param opt : option to set (\ref DNS_OPTIONS).
//! \param optval : Value
//! \return
//! - 0 if OK.
//! - a negative error code otherwise.
int ResolverGetOption( int opt, void * optval );

//! \brief This function sets an option parameter of the DNS resolver.
//! \param opt : option to set (\ref DNS_OPTIONS).
//! \param optval : Value.
//! \return 
//! - 0 if OK.
//! - a negative error code otherwise.
int ResolverSetOption( int opt, void * optval );

//! \brief      Retrieve an IP address from a domain name.
//! \param[in]  szDomainName NULL terminated string containing the domain name, such as "www.ingenico.com".
//! \param[out] pcIpAddress Buffer that will contain a NULL terminated string with the corresponding IP address, such as "87.118.80.53".
//! \param[in]  nSize Size of the pcIpAddress buffer.
//! \return     DNS_OK or a negative error code (see \ref DNS_ERROR).
int DNS_GetIpAddress( const char* szDomainName, char* pcIpAddress, unsigned int nSize );

//! \brief      Retrieve a domain name from an IP address. Warning ! Some DNS servers do not answer to reverse DNS requests !
//! \param[in]  szIpAddress NULL terminated string containing the IP address, such as "87.118.80.53".
//! \param[out] pcDomainName Buffer that will contain a NULL terminated string with the corresponding domain name, such as "www.ingenico.com".
//! \param[in]  nSize Size of the pcDomainName buffer.
//! \return     DNS_OK or a negative error code (see \ref DNS_ERROR).
int DNS_GetDomainName( const char* szIpAddress, char* pcDomainName, unsigned int nSize );

//! @}

// Ethernet interface options.
//! \defgroup IP_ETH_OPTIONS Ethernet options
//! \ingroup TCPIP
//! \brief Options of the Ethernet interface.
//! @{
#define ETH_IFO_ADDR           0x0103		//!< Local Address.
#define ETH_IFO_NETMASK        0x0104		//!< Network Mask.
#define ETH_IFO_BRDADDR        0x0105		//!< Broadcast Address.

#define ETH_IFO_USE_ROUTE      0x1000     //!< Ethernet route selection.
#define ETH_IFO_GATEWAY        0x1001	  //!< Gateway Address (read-only).
#define ETH_IFO_DNS1           0x1002	  //!< DNS1 Address (read-only).
#define ETH_IFO_DNS2           0x1003	  //!< DNS2 Address (read-only).
#define ETH_IFO_DEFAULT_ROUTE  0x1004     //!< Ethernet default route (read-only).
// -- DO NOT SUPPRESS THIS LINE -------------------

//! \brief This function gets an option parameter of the Ethernet link.
//! On products that have an Ethernet interface through a Bluetooth base (EFT930, iWL2XX) it returns the local Ethernet interface's parameters,
//! not the ones from the base's interface.
//! For such products one should use USQ_EthernetConfig() which will get the relevant Ethernet parameters.
//! \param nOption : Option to get.
//! \param pValue : Value.
//! \return
//! - 0 if OK.
//! - a negative error code otherwise.
int EthernetGetOption( int nOption, void *pValue );


//! \brief This function sets an option parameter of the Ethernet link.
//! \param nOption : Option to set.
//! \param pValue : Value.
//! \return
//! - 0 if OK.
//! - a negative error code otherwise.
int EthernetSetOption( int nOption, void *pValue );
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \addtogroup IP_CONFIGURATION 
//!
//! The different options are listed in the table below. They can be read, written and saved persistently (to
//! become the default configuration).
//!
//!
//! <TABLE border="1" cellspacing="0" bordercolor="black" valign="middle" >
//! <TR><TD><b>Option</b></TD><TD><b>Value</b></TD><TD><b>Access</b></TD><TD><b>Comments</b></TD></TR>
//! <TR>
//! <TD>\ref __DFL_ETH_MAC_ADDRESS</TD>
//! <TD>6 bytes </TD>
//! <TD>Read </TD>
//! <TD>Ethernet MAC Address</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_ETH_LINK_SPEED</TD>
//! <TD>Integer (10 or 100)</TD>
//! <TD>Read/Write </TD>
//! <TD>Ethernet link speed<br>\ref __DFL_ETH_LINK_SPEED_10MB<br>\ref __DFL_ETH_LINK_SPEED_100MB</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_ETH_BOOT_PROTOCOL</TD>
//! <TD>DHCP or static</TD>
//! <TD>Read/Write</TD>
//! <TD>Ethernet boot protocol<br>\ref __DFL_ETH_BOOT_PROTOCOL_NONE<br>\ref __DFL_ETH_BOOT_PROTOCOL_DHCP</TD>
//! </TR>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_ETH_ADDR</TD>
//! <TD>4 bytes</TD>
//! <TD>Read/Write</TD>
//! <TD>Ethernet local address</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_ETH_GATEWAY</TD>
//! <TD>4 bytes</TD>
//! <TD>Read/Write</TD>
//! <TD>Ethernet gateway address</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_ETH_NETMASK</TD>
//! <TD>4 bytes</TD>
//! <TD>Read/Write</TD>
//! <TD>Ethernet network mask</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_ETH_DNS1</TD>
//! <TD>4 bytes</TD>
//! <TD>Read/Write</TD>
//! <TD>Ethernet DNS1 address</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_ETH_DNS2</TD>
//! <TD>4 bytes</TD>
//! <TD>Read/Write</TD>
//! <TD>Ethernet DNS2 address</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_WIFI_MAC_ADDRESS</TD>
//! <TD>6 bytes </TD>
//! <TD>Read </TD>
//! <TD>WiFi MAC Address</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_WIFI_BOOT_PROTOCOL</TD>
//! <TD>DHCP or static</TD>
//! <TD>Read/Write</TD>
//! <TD>WiFi boot protocol<br>\ref __DFL_WIFI_BOOT_PROTOCOL_NONE<br>\ref __DFL_WIFI_BOOT_PROTOCOL_DHCP</TD>
//! </TR>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_WIFI_ADDR</TD>
//! <TD>4 bytes</TD>
//! <TD>Read/Write</TD>
//! <TD>WiFi local address</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_WIFI_GATEWAY</TD>
//! <TD>4 bytes</TD>
//! <TD>Read/Write</TD>
//! <TD>WiFi gateway address</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_WIFI_NETMASK</TD>
//! <TD>4 bytes</TD>
//! <TD>Read/Write</TD>
//! <TD>WiFi network mask</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_WIFI_DNS1</TD>
//! <TD>4 bytes</TD>
//! <TD>Read/Write</TD>
//! <TD>WiFi DNS1 address</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_WIFI_DNS2</TD>
//! <TD>4 bytes</TD>
//! <TD>Read/Write</TD>
//! <TD>WiFi DNS2 address</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_ICMP_REDIRECT</TD>
//! <TD>Boolean (ON or OFF)</TD>
//! <TD>Read/Write</TD>
//! <TD>Activate ICMP redirection<br>\ref __DFL_ON<br> \ref __DFL_OFF</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_ICMP_ECHO_REPLY</TD>
//! <TD>Boolean (ON or OFF)</TD>
//! <TD>Read/Write</TD>
//! <TD>Activate ICMP reply<br>\ref __DFL_ON<br> \ref __DFL_OFF</TD>
//! </TR>
//! <TR>
//! <TD>\ref __DFL_ETH_DHCP_HOSTNAME</TD>
//! <TD>Zero-terminated ASCII string.</TD>
//! <TD>Set hostname (DHCP only)</TD>
//! </TR>
//! </TABLE>
//!
//! A sample is given in \ref SET_DEFAULT_OPTION_SAMPLE.
//!
//! \note The IP configuration management functions require the use of the WiFi dynamic library.
//! The compilation process must include the link with the library "dll_wifi.lib".
//! @{

// Ethernet persistent options


//! \defgroup IP_DEFAULT_OPTION  Configuration options
//! \brief Options to set the default configuration of the TCP/IP facility.
//! @{
#define __DFL_MAC_ADDRESS			0x2000	//!< Deprecated. Use \ref __DFL_ETH_MAC_ADDRESS or \ref __DFL_WIFI_MAC_ADDRESS.
#define __DFL_ETH_LINK_SPEED		0x2001	//!< Ethernet link speed (read/write).
#define __DFL_ETH_BOOT_PROTOCOL		0x2003	//!< Ethernet boot protocol : static or DHCP (read-write).

#define __DFL_ETH_MAC_ADDRESS	__DFL_MAC_ADDRESS	//!< Ethernet MAC address (read-only).
#define __DFL_ETH_ADDR			ETH_IFO_ADDR		//!< Ethernet local address (read-write).
#define __DFL_ETH_NETMASK		ETH_IFO_NETMASK		//!< Ethernet network mask (read-write).
#define __DFL_ETH_GATEWAY		ETH_IFO_GATEWAY		//!< Ethernet gateway address (read-write).
#define __DFL_ETH_DNS1			ETH_IFO_DNS1		//!< Ethernet DNS1 address (read-write).
#define __DFL_ETH_DNS2			ETH_IFO_DNS2		//!< Ethernet DNS2 address (read-write).

#define __DFL_ICMP_ECHO_REPLY	0x2010				//!< Activate ICMP replay (read-write).
#define __DFL_ICMP_REDIRECT		0x2011				//!< Activate ICMP redirection (read-write).

#define __DFL_WIFI_MAC_ADDRESS		0x2100			//!< WiFi MAC address (read-only).
#define __DFL_WIFI_ADDR				0x2101			//!< WiFi local address (read-write).
#define __DFL_WIFI_NETMASK			0x2102			//!< WiFi network mask (read-write).
#define __DFL_WIFI_GATEWAY			0x2103			//!< WiFi gateway address (read-write).
#define __DFL_WIFI_DNS1				0x2104			//!< WiFi DNS1 address (read-write).
#define __DFL_WIFI_DNS2				0x2105			//!< WiFi DNS2 address (read-write).
#define __DFL_WIFI_BOOT_PROTOCOL	0x2106			//!< WiFi boot protocol : static or DHCP (read-write).

#define __DFL_ETH_DHCP_HOSTNAME		0x400A			//!< Set hostname (DHCP only) (read-write).


//! @}

// Enumerated values for ethernet persistent options

//-- general values
#define __DFL_OFF		0	//!< To disable an option.
#define __DFL_ON		1	//!< To enable an option.

//-- option ETH_DFL_LINK_SPEED

#define __DFL_ETH_LINK_SPEED_10MB		10		//!< Ethernet link speed set to 10MB.
#define	__DFL_ETH_LINK_SPEED_100MB		100		//!< Ethernet link speed set to 100MB.

//-- option ETH_DFL_BOOT_PROTOCOL
#define __DFL_ETH_BOOT_PROTOCOL_NONE	1	//!< Ethernet boot protocol : static mode.
#define __DFL_ETH_BOOT_PROTOCOL_DHCP	2	//!< Ethernet boot protocol : activate DHCP mode.

//-- option ETH_WIFI_BOOT_PROTOCOL
#define __DFL_WIFI_BOOT_PROTOCOL_NONE	__DFL_ETH_BOOT_PROTOCOL_NONE	//!< WiFi boot protocol : static mode.
#define __DFL_WIFI_BOOT_PROTOCOL_DHCP	__DFL_ETH_BOOT_PROTOCOL_DHCP	//!< WiFi protocol : activate DHCP mode.

#define __DFL_BT_NO_REBOOT				0x6000

//--
//
//! \defgroup IP_DEFAULT_OPTION_ERROR Error codes
//! @{

#define __DFL_OK							0	//!< OK. The operation is successful.
#define __DFL_ERROR_INVALID_HANDLE			-1	//!< Invalid handle parameter
#define __DFL_ERROR_LOADING					-2	//!< Error when reading the default parameter file.
#define __DFL_ERROR_OPEN_FAILED				-3	//!< The default parameter file can not be opened.
#define __DFL_ERROR_HW_ADDRESS_NOT_FOUND	-4	//!< The hardware address (MAC) is missing. It is a mandatory parameter.
#define __DFL_ERROR_INVALID_OPTION			-5	//!< Invalid option parameter
#define __DFL_ERROR_FIXED_OPTION			-6	//!< The option is fixed. It can not be modified.
#define __DFL_ERROR_INVALID_VALUE			-7	//!< The option value is invalid

#define __DFL_ERROR_BT_NO_ASSOCIATION		-8	//!< No base is associated to the terminal or terminal has no Bluetooth
#define __DFL_ERROR_BT_NO_PERIPHERAL		-9	//!< Peripheral not reachable (no base associated with this peripheral, Bluetooth base without Ethernet interface)
#define __DFL_ERROR_BT_BASE_NOT_AVAILABLE	-10	//!< Base not reachable (Bluetooth base is not available)
#define __DFL_ERROR_BT_NO_BLUETOOTH			-11	//!< The terminal has no Bluetooth

#define __DFL_ERROR_STATIC_HANDLE			-12 //!< The handle cannot be modified
//! @}

typedef void * ETHCONF_HANDLE;					//!< Deprecated (use \ref DFLCONF_HANDLE instead)
//! \brief Definition of DLFCONF_HANDLE.
typedef void * DFLCONF_HANDLE;

//! \brief This function return the status of the Bluetooth base providing an Ethernet interface. 
//! \return 
//! - \ref __DFL_OK
//! - A negative error code otherwise.
//! - \ref __DFL_ERROR_BT_NO_ASSOCIATION
//! - \ref __DFL_ERROR_BT_NO_PERIPHERAL
//! - \ref __DFL_ERROR_BT_BASE_NOT_AVAILABLE
//! \note On a Bluetooth base the function takes at least one second to execute.
int EthernetGetBluetoothBaseStatus(void);

//! \brief This function loads the default parameters of the IP Ethernet link.
//! \param pnError : Output parameter which returns the error code of the loading operation :
//! - \ref __DFL_OK
//! - A negative error code otherwise.
//! - \ref __DFL_ERROR_HW_ADDRESS_NOT_FOUND
//! - \ref __DFL_ERROR_OPEN_FAILED
//! - \ref __DFL_ERROR_LOADING
//! - \ref __DFL_ERROR_BT_NO_ASSOCIATION
//! - \ref __DFL_ERROR_BT_NO_PERIPHERAL
//! - \ref __DFL_ERROR_BT_BASE_NOT_AVAILABLE
//! \return 
//! - An handle on the IP configuration. 
//! - If the device does not have a native IP peripheral (no ETH.CFG configuration file) it returns the default configuratioon hard coded in the IP stack implementation.
//!       To detect this case pnError must be tested.
//!       ! Such a handle can neither be modified with __SetDefaultOption nor saved with __SaveDefaultOptions ! It will result in a __DFL_ERROR_STATIC_HANDLE error.
//! \note On a Bluetooth base the function takes at least one second to execute.
DFLCONF_HANDLE __LoadDefaultOptions ( int *pnError );

//! \brief This function unloads a configuration previously loaded using the 
//! function "__LoadDefaultOptions". The configuration is lost (e.g it is not saved). The configuration handle is released. It must not be used anymore.
//! \param handle : Handle on the configuration to unload.
//! \return 
//! - \ref __DFL_OK
//! - A negative error code otherwise.
//! - \ref __DFL_ERROR_INVALID_HANDLE
int __UnloadDefaultOptions ( DFLCONF_HANDLE handle );

//! \brief This function sets an option parameter in the IP configuration. To make 
//! this change persistent, the configuration must be saved using the function '__SaveDefaultOptions' (described below).
//! \param hConf : Handle on the configuration
//! \param nOption : Option to set. The list of options is given in table above.
//! \param pValue : Value.
//! \return 
//! - \ref __DFL_OK
//! - A negative error code otherwise.
//! - \ref __DFL_ERROR_FIXED_OPTION
//! - \ref __DFL_ERROR_INVALID_VALUE
//! - \ref __DFL_ERROR_INVALID_HANDLE
//! - \ref __DFL_ERROR_INVALID_OPTION
//! - \ref __DFL_ERROR_STATIC_HANDLE
//! \note The option \ref __DFL_BT_NO_REBOOT can be set to a non zero value to avoid a reboot on a Bluetooth product not connected to its base.
int __SetDefaultOption ( DFLCONF_HANDLE hConf, int nOption, void *pValue );

//! \brief This function gets an option parameter of IP configuration.
//! \param hConf : Handle on the configuration .
//! \param nOption : Option to get. The list of options is given in table above.
//! \param pValue : Value.
//! \return 
//! - \ref __DFL_OK
//! - A negative error code otherwise.
//! - \ref __DFL_ERROR_INVALID_HANDLE
//! - \ref __DFL_ERROR_INVALID_OPTION
int __GetDefaultOption ( DFLCONF_HANDLE hConf, int nOption, void *pValue );

//! \brief This function saves the configuration as the default one. The terminal is
//! automatically rebooted and the new saved configuration is used.
//! \param hConf : Handle on the configuration to save.
//! \return 
//! - The negative error code 
//! - \ref __DFL_ERROR_INVALID_HANDLE
//! - \ref __DFL_ERROR_BT_NO_ASSOCIATION
//! - \ref __DFL_ERROR_BT_NO_PERIPHERAL
//! - \ref __DFL_ERROR_BT_BASE_NOT_AVAILABLE
//! - \ref __DFL_ERROR_STATIC_HANDLE
//! - or never returns.
//! \note The option \ref __DFL_BT_NO_REBOOT can be set to a non zero value to avoid a reboot on a Bluetooth product not connected to its base.
int __SaveDefaultOptions ( DFLCONF_HANDLE hConf );

//! \brief This function tests if a remote address is reachable., by sending an ICMP request (Ping).
//! \param addr : Remote address to reach
//! \param nTimeout : Waiting delay (in 10 ms) for the answer.
//! \return
//! - 0 if OK.
//! - a negative error code otherwise.
int __Ping( unsigned int addr, unsigned int nTimeout );

// Route settings management.

//! \brief This function gets the gateway address of the default route.
//! \return None.
void __GetDefaultRoute( unsigned int *gateway_addr );

//! \brief This function sets the gateway address of the default route.
//! \param gateway_addr : Gateway address to set.
//! \return None.
void __SetDefaultRoute( unsigned int gateway_addr );


//! \brief This function add a new static entry in the routing table of the embedded TCP/IP stack.
//! \param dest_addr : destination address
//! \param subnet_mask : mask for the subnetwork.
//! \param gateway_addr : Gateway address to subnetwork.
//! \return 0 or a negative error code.
int __AddRoute( unsigned int dest_addr, unsigned int subnet_mask, unsigned int gateway_addr);

//! \brief This function deletes a static entry in the routing table of the embedded TCP/IP stack.
//! \param dest_addr : destination address
//! \return 0 or a negative error code.
int __DeleteRoute( unsigned int dest_addr );

//! @}




//! \defgroup ETH_INFO_SAMPLE	Get the Ethernet options
//! \ingroup TCPIP_SAMPLES
//! The following code shows how to get the information of the Ethernet link (local IP address and the network mask).
//! \include IP__Sample_01.c
//! \example IP__Sample_01.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//! \defgroup SET_DEFAULT_OPTION_SAMPLE		Enable or disable the ICMP reply
//! \ingroup TCPIP_SAMPLES
//! This sample code shows how to enable or disable the ICMP reply facility. It demonstrates how to modify the default parameters..
//! \include IP__Sample_02.c
//! \example IP__Sample_02.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

#ifdef __cplusplus
}
#endif



#endif // __IP__H__	
