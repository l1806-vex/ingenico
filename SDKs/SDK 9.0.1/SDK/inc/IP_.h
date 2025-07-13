
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
//! <TR><TD><b>Developers shall read the document [ICO-PE-045-GU-EN_PackIP_SecurityGuidance_UserGuide.pdf]
//! which describes best practises for implementing IP enabled applications, according to
//! the requirements of the POS Terminal Security Program (PTS) and of the PCI PTS v3 "Open Protocols" module.</b></TD></TR>
//! <TR><TD></TD></TR>
//! </TABLE>
//!
//! The header file <IP_.h> regroups mainly the standard BSD definitions. This document does not
//! explain these functions. It describes the specific functions, particularly the ones of the interface
//! of the integrated protocols PPP, HTTP, POP3 and SMTP.
//!

#ifndef __IP__H__
#define __IP__H__

#ifdef __cplusplus
extern "C"
{
#endif

//! \addtogroup IP_BSD 
//! @{
//! The package TCP/IP is compatible with BSD interface. 
//! However, it exists some main differences, listed below.
//! - The "shutdown()" function is renamed \ref shutdownsocket().
//! - The "select()" function is renamed \ref selectsocket()'.
//! - The functions "gethostbyname()" and "gethostbyaddr()" are replaced respectively by the functions : \ref gethostbyname_r() and \ref gethostbyaddr_r().
//! - The functions "inet_addr()", "inet_aton()" and "inet_ntoa()" are replaced respectively by the functions :
//! \ref __inet_addr(), \ref __inet_aton() and \ref __inet_ntoa().

//! \defgroup IP_ERROR_CODES BSD Error codes
//! \brief Error codes returned by BSD API functions  (errno).
//! \ingroup IP_BSD
//! @{

#define __EOK               0  //!< No error
#define __E2BIG            -1  //!< Argument list too long
#define __EACCES           -2  //!< Permission denied
#define __EADDRINUSE       -3  //!< Address already in use
#define __EADDRNOTAVAIL    -4  //!< Address not available from this host
#define __EAFNOSUPPORT     -5  //!< Address family not supported
#define __EAGAIN           -6  //!< Resource temporarily unavailable
#define __EALREADY         -7  //!< Operation already in progress
#define __EAUTH            -8  //!< Authentication error
#define __EBADF            -9  //!< Bad descriptor
#define __EBUSY            -10 // Resource busy
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

// Settings 
#define __TIMERHZ      2   //!< 500ms stack timer
#define __FD_MAX      32   //!< Maximum number of 'file' descriptors

// Address family.

//! \defgroup ADDRESS_FAMILY Address family
//! \brief Address family.
//! @{
#define AF_UNSPEC        0       //!< Unspecified.
#define AF_INET          2       //!< Internetwork: UDP, TCP, etc.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Protocol family (== address family).

//! \defgroup PROTOCOL_FAMILY Protocol family
//! \brief Protocol family.
//! @{
#define PF_UNSPEC          0         //!< Unspecified.
#define PF_INET            2         //!< Internet IP Protocol.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Type of socket.
//! \defgroup SOCKET_TYPE Socket type
//! \brief Socket type.
//! @{
#define SOCK_STREAM        1         //!< Type of socket: stream (connection) type socket (TCP).
#define SOCK_DGRAM         2         //!< Type of socket: datagram (connection less) socket (UDP).
#define SOCK_RAW           3         //!< Type of socket: raw socket.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Protocols.
//! \defgroup  IP_PROTOCOLS IP protocols
//! \brief IP protocols.
//! @{
#define IPPROTO_IP         0         //!< Dummy protocol for TCP.
#define IPPROTO_HOPOPTS    0         //!< IPv6 Hop-by-Hop options.
#define IPPROTO_ICMP       1         //!< Internet Control Message Protocol.
#define IPPROTO_IGMP       2         //!< Internet Group Management Protocol.
#define IPPROTO_GGP        3         //!< Gateway2 (deprecated).
#define IPPROTO_IPV4       4         //!< IPv4 header.
#define IPPROTO_IPIP       4         //!< IPIP tunnels (older KA9Q tunnels use 94).
#define IPPROTO_TCP        6         //!< Transmission Control Protocol.
#define IPPROTO_EGP        8         //!< Exterior Gateway Protocol.
#define IPPROTO_PUP        12        //!< PUP protocol.
#define IPPROTO_UDP        17        //!< User Datagram Protocol.
#define IPPROTO_IDP        22        //!< XNS IDP protocol.
#define IPPROTO_TP         29        //!< SO Transport Protocol Class 4.
#define IPPROTO_IPV6       41        //!< IPv6 header.
#define IPPROTO_ROUTING    43        //!< IPv6 routing header.
#define IPPROTO_FRAGMENT   44        //!< IPv6 fragmentation header.
#define IPPROTO_RSVP       46        //!< Reservation Protocol.
#define IPPROTO_GRE        47        //!< General Routing Encapsulation.
#define IPPROTO_ESP        50        //!< Encapsulating security payload.
#define IPPROTO_AH         51        //!< Authentication header.
#define IPPROTO_EON        80        //!< ISO CNLP.
#define IPPROTO_MOBILE     55        //!< IP Mobility.
#define IPPROTO_IPV6_ICMP  58        //!< ICMPv6.
#define IPPROTO_ICMPV6     58        //!< ICMPv6.
#define IPPROTO_NONE       59        //!< IPv6 no next header.
#define IPPROTO_DSTOPTS    60        //!< IPv6 destination options.
#define IPPROTO_ENCAP      98        //!< Encapsulation Header.
#define IPPROTO_PIM        103       //!< Protocol Independent Multicast.
#define IPPROTO_IPCOMP     108       //!< Compression Header Protocol.
#define IPPROTO_VRRP       112       //!< VRRP (RFC 2338).
#define IPPROTO_RAW        255       //!< Raw IP packets.
#define IPPROTO_MAX        256       //!< Maximum value for IPPROTO options.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Recv/Send flags.
//! \defgroup  IP_SEND_RECV_FLAGS Send and receive flags
//! \brief Send and receive flags.
//! @{
#define MSG_DONTWAIT       0x0001    //!< Non-blocking operation request.
#define MSG_WAITALL        0x0002    //!< Wait till operation completed.
#define MSG_OOB            0x0004    //!< Receive out-of-band data.
#define MSG_PEEK           0x0008    //!< Peek at data, don't remove from buffer.
#define MSG_DONTROUTE      0x0010    //!< Don't use gateway.
#define MSG_EOR            0x0020    //!< End of record.
#define MSG_TRUNC          0x0040    //!< Packet data was discarded (buffer too small).
#define MSG_CTRUNC         0x0080    //!< Control data was discarded (buffer too small).
#define MSG_BCAST          0x0100    //!< Broadcast message.
#define MSG_MCAST          0x0200    //!< Multicast message.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


// Level of option.
#define SOL_SOCKET		0xffffU		 //!< Options for socket level.
#define SO_ERROR        0x1007		 //!< Get error status and clear (ro).

// Socket options
//! \defgroup  SOCKET_OPTIONS Socket options
//! \brief Socket options (used by \ref setsockopt()/ \ref getsockopt()).
//! @{
#define SO_REUSEADDR       0x0004    //!< Reuse address.
#define SO_KEEPALIVE       0x0008    //!< Keep alive.
#define SO_BROADCAST       0x0020    //!< Broadcast.
#define SO_LINGER          0x0080    //!< Linger-on-close timeout.
#define SO_SNDTIMEO        0x1005    //!< Send timeout.
#define SO_RCVTIMEO        0x1006    //!< Receive timeout.
#define SO_NREAD           0x1f02    //!< Number of bytes in the receive buffer (ReadOnly option).


// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


//
#define INADDR_ANY         (unsigned int)0x00000000   //!< Unspecified IP address (all zeroes).
#define INADDR_LOOPBACK    0x0100007f                 //!< Loopback address.
#define INADDR_BROADCAST   (unsigned int)0xffffffff   //!< Broadcast address 
#define INADDR_NONE        0xffffffff                 //!< Address none (same as broadcast)

// TCP options used by setsockopt/getsockopt.

//! \defgroup  TCP_OPTIONS TCP options
//! \brief TCP options (used by \ref setsockopt()/ \ref getsockopt()).
//! @{
#define TCP_NODELAY      0x0001  //!< Don't delay send to coalesce packets.
#define TCP_MAXSEG       0x0002  //!< Set maximum segment size.
#define TCP_USE_SCALE    0x0003  //!< Deprecated.
#define TCP_SEND_TSTMP   0x0004  //!< Deprecated.
#define TCP_SACK_DISABLE 0x0005  //!< Disable SACKs (per-connection).
#define TCP_NOTIMEWAIT   0x0006  //!< Disable time-wait state.
#define TCP_CONNRST      0x0007  //!< Send a RST before active connection.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Shutdown "how" parameter.
//! \defgroup  IP_SHUTDOWN_METHOD Shutdown method
//! \brief Shutdown "how" parameter.
//! @{
#define SHUT_RD			       0         //!< Shutdown read part of full duplex socket.
#define SHUT_WR			       1         //!< Shutdown write part of full duplex socket.
#define SHUT_RDWR		       2         //!< Shutdown read and write part of full duplex socket.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \brief Generic socket address.
struct sockaddr
{
    unsigned char     sa_len;						//!< Total length.
    unsigned char     sa_family;					//!< Address family.
    unsigned char     sa_data[14];					//!< Address value.
};

//! \brief Socket address in internet domain.
struct in_addr
{
    unsigned int      s_addr;						//!< 32 bits IP address, net byte order.
};

//! \brief Generic socket_in address.
struct sockaddr_in
{
    unsigned char     sin_len;						//!< Total length (16).
    unsigned char     sin_family;					//!< AF_INET.
    unsigned short    sin_port;						//!< 16 bits port number, net byte order.
    struct in_addr sin_addr;						//!< 32 bits IP address.
    unsigned char     sin_zero[8];					//!< Unused.
};

//! \brief Structure used by readv/writev/recvmsg/writemsg.
struct iovec
{
    void   *iov_base;
    int     iov_len;
};


//! \brief Used by SO_LINGER socket option.
struct linger 
{
    int     l_onoff;
    int     l_linger;
};

//! \brief Message structure for sendmsg/recvmsg.
struct msghdr
{
    caddr_t			msg_name;						//!< Optional address.
    unsigned int	msg_namelen;					//!< Address size.
    struct iovec*	msg_iov;						//!< Scatter/gather array.
    unsigned int	msg_iovlen;						//!< Number of elements in msg_iov.
    caddr_t			msg_control;					//!< Ancillary data.
    unsigned int	msg_controllen;					//!< Ancillary data buffer length.
    int				msg_flags;						//!< flags on received message.
};

//! \brief 
struct cmsghdr 
{
	unsigned int	cmsg_len;						//!< Data byte count, including hdr.
	int				cmsg_level;						//!< Originating protocol.
	int				cmsg_type;						//!< Protocol-specific type.
									// Followed by unsigned char  cmsg_data[];.
};

// Commands for fcntlsocket().
#define F_GETFL         3 	//!< Read the socket status flags. 
#define F_SETFL         4	//!< Set the socket status flags. 

#define O_NONBLOCK      0x0004	//!< Non-blocking socket mode


// Commands for ioctlsocket().
#define IOC_OUT         0x40000000L   //!< Copy out parameters.
#define IOC_IN          0x80000000L   //!< Copy in parameters.
#define IOCPARM_MASK    0x1fff        //!< Parameter length, at most 13 bits.
#define _IOC(inout,group,num,len) \
        (inout | (((long)len & IOCPARM_MASK) << 16) | ((group) << 8) | (num))
#define _IOR(g,n,t)     _IOC(IOC_OUT,   (g), (n), sizeof(t))
#define _IOW(g,n,t)     _IOC(IOC_IN,    (g), (n), sizeof(t))

#define FIONBIO         _IOW('f', 126, int)   //!< Set/clear nonblocking io.
#define FIONREAD        _IOR('f', 127, int)   //!< Get # bytes to read.
#define SIOCATMARK      _IOR('s',  7, int)    //!< At oob mark ?

// Definitions for selectsocket()
//! \defgroup  IP_FD_SET Descriptor set management.
//! \brief Socket descriptor set management (used for \ref selectsocket().
//! @{

typedef struct 
{
    unsigned long fds[(__FD_MAX+31)/32];
} fd_set;

//! \brief FD_ZERO() initializes a descriptor set 'fdset' to the null set.
#define FD_ZERO( fdset) { int i; for( i=0; i<((__FD_MAX+31)/32); i++) (fdset)->fds[i] = 0; }

//! \brief FD_SET() includes a particular descriptor 'fd' in 'fdset'.
#define FD_SET( fd, fdset)      ((fdset)->fds[(fd)>>5] |= 1UL<<((fd) & 0x1f))

//! \brief FD_CLR() removes 'fd' from 'fdset'.
#define FD_CLR( fd, fdset)      ((fdset)->fds[(fd)>>5] &= ~(1UL<<((fd) & 0x1f)))

//! \brief FD_ISSET() call returns non zero if 'fd' is a member of 'fdset'
//! Otherwise, it returns zero.
#define FD_ISSET( fd, fdset)    ((fdset)->fds[(fd)>>5] & (1UL<<((fd) & 0x1f)))

//! \brief Max number of fds in one select()
#define __SELECT_FD_MAX    (__FD_MAX/2)
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}


// Prototypes.
//! \brief accept() extracts the first connection request on the queue of pending connections,
//! creates a new socket with the same properties of socket, and allocates a new file descriptor for the socket.
//! The argument socket is a socket that has been created with \ref socket(), bound to an address with \ref bind(), 
//! and is listening for connections after a \ref listen().
//! \param s : socket descriptor.
//! \param addr : pointer to structure sockaddr. Output parameter that is filled in with the address of the connecting entity,
//! as known to the communications layer. The exact format of the address parameter is determined by the domain 
//! in which the communication is occurring.
//! \param addrlen : this parameter is a value-result parameter; it should initially contain the amount of space pointed to by address; on return it will contain the actual length (in bytes) of the address returned.
//! \return
//! - On success, the descriptor for the accepted socket is returned.
//! - On error, -1 is returned, and errno is set appropriately. 
// \if SIMULATION
//  @GSIM_F:accept:KSFAM_PPP_OLD:0x43
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
// \endif
int	accept( int s, struct sockaddr *addr, int *addrlen);

//! \brief bind gives the socket 's' the local address 'my_addr'. Traditionally, this is called 'assigning a name to a 
//! socket.' .When a socket is created with socket, it exists in a name space (address family) but has no name assigned.
//! \param s : socket descriptor
//! \param my_addr : pointer to structure sockaddr.
//! \param addrlen : length of returned data.
//! \return
//! - On success, zero is returned.
//! - On error, -1 is returned, and errno is set appropriately. 
// \if SIMULATION
//  @GSIM_F:bind:KSFAM_PPP_OLD:0x41
//  @GSIM_A:2:ONE_POINTER
// \endif
int	bind( int s, const struct sockaddr *my_addr, int addrlen);

//! \brief This function closes an existing socket.
//! \param s : descriptor identifying the socket to close.
//! \return
//! - On success, zero is returned.
//! - On error, -1 is returned, and errno is set appropriately. 
// \if SIMULATION
//  @GSIM_F:closesocket:KSFAM_PPP_OLD:0x14
// \endif
int closesocket( int s);


//! \brief  The connect() function call connects the socket referred to by the file descriptor 's' 
//! to the address specified by 'serv_addr'. 
//! The addrlen argument specifies the size of serv_addr. The format of the address in serv_addr is determined by the address space of the socket sockfd; 
//! see \ref socket() for further details. 
//! If the socket 's' is of type \ref SOCK_DGRAM then 'serv_addr' is the address to which datagrams are sent 
//! by default, and the only address from which datagrams are received. 
//! If the socket is of type \ref SOCK_STREAM, this call attempts to make a connection to the socket 
//! that is bound to the address specified 'by serv_addr'.
//! \note Generally, connection-based protocol sockets may successfully \ref connect() only once. 
//! Connectionless protocol sockets may use \ref connect() multiple times to change their association. 
//! Connectionless sockets may dissolve the association by connecting to an address with the 
//! sa_family member of sockaddr set to \ref AF_UNSPEC. 

//! \param s : socket descriptor
//! \param serv_addr : remote server address.
//! \param addrlen : length (in bytes) of the address returned.
//! \return
//! - On success (the connection or binding succeeds), zero is returned. 
//! - On error, -1 is returned, and errno is set appropriately. 
// \if SIMULATION
//  @GSIM_F:connect:KSFAM_PPP_OLD:0x40
//  @GSIM_A:2:ONE_POINTER
// \endif
int	connect( int s, const struct sockaddr *serv_addr, int addrlen);


//! \brief The fcntlsocket() performs one of the operations described below on the socket descriptor 's'.
//! The operation is determined by 'cmd'. 
//! \param s : socket descriptor.
//! \param cmd :
//! - \ref F_GETFL 
//! - \ref F_SETFL 
//! \return
//! For a successful call, the return value depends on the executed operation :
//! - Otherwise, -1 is returned and errno set to indicate the error.
// \if SIMULATION
//  @GSIM_F:fcntlsocket:KSFAM_PPP_OLD:0x16
// \endif
int fcntlsocket( int s, int cmd, ...);

//! \brief getpeername() returns the name of the peer connected to socket s. The namelen parameter should be initialized to indicate the amount of space pointed to by name. 
//! On return it contains the actual size of the name returned (in bytes). 
//! The name is truncated if the buffer provided is too small.
//! \param s : socket.
//! \param name : pointer to structure sockaddr.
//! \param namelen : amount of space pointed to by name.
//! \return
//! - On success, zero is returned.
//! - On error, -1 is returned, and errno is set appropriately.
// \if SIMULATION
//  @GSIM_F:getpeername:KSFAM_PPP:0x10
//  @GSIM_A:2:ONE_POINTER 
//  @GSIM_A:3:ONE_POINTER 
// \endif
int	getpeername( int s, struct sockaddr *name, int *namelen);

//! \brief getsockname() returns the current name for the specified socket. 
//! The 'namelen' parameter should be initialized to indicate the amount of space pointed to by 'name'. 
//! On return it contains the actual size of the name returned (in bytes).
//! \param s : socket descriptor.
//! \param name : pointer to structure sockaddr.
//! \param namelen : amount of space pointed to by 'name'.
//! \return
//! - On success, zero is returned.
//! - On error, -1 is returned, and errno is set appropriately.
// \if SIMULATION
//  @GSIM_F:getsockname:KSFAM_PPP_OLD:0x19
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
// \endif
int	getsockname( int s, struct sockaddr *name, int *namelen);


//! \brief ioctlsocket() manipulates the I/O mode of a socket.
//! \param s : socket descriptor.
//! \param cmd : command to execute.
//! \param arg : command parameter.
//! \return
//! - On success, zero is returned. 
//! - On error, -1 is returned, and errno is set appropriately. 
// \if SIMULATION
//  @GSIM_F:ioctlsocket:KSFAM_PPP:0x11
//  @GSIM_A:3:ONE_POINTER 
// \endif
int ioctlsocket( int s, long cmd, int *arg);

//! \brief listen() specifies the acceptance and the queue of incoming connections.
//! To accept connections, a socket is first created with \ref socket(),
//! a willingness to accept incoming connections and a queue limit for incoming connections 
//! are specified with \ref listen(), and then the connections are accepted with \ref accept(). 
//! \param s : socket identifier.
//! \param backlog : the maximum length for the queue of pending connections.
//! \return
//! - On success, zero is returned.
//! - On error, -1 is returned, and errno is set appropriately. 
//! \note The listen() call applies only to sockets of type \ref SOCK_STREAM. 
// \if SIMULATION
//  @GSIM_F:listen:KSFAM_PPP_OLD:0x42
// \endif
int	listen( int s, int backlog);


//! \brief The recvfrom() call is used to receive messages from a socket, 
//! and may be used to receive data on a socket whether or not it is connection-oriented. 
//! \param s : socket.
//! \param buf : source address.
//! \param len : buffer length.
//! \param flags : the flags argument is formed by OR'ing one or more of the following values (\ref IP_SEND_RECV_FLAGS) :
//! - \ref MSG_DONTWAIT 
//! - \ref MSG_OOB 
//! - \ref MSG_PEEK 
//! - \ref MSG_TRUNC 
//! - \ref MSG_WAITALL
//! \param from : pointer to structure sockaddr. If 'from' is not NULL, and the underlying protocol provides the source address, this source address is filled in.
//! \param fromlen : a value-result parameter, initialized to the size of the buffer associated with from, and modified on return to indicate the actual size of the address stored there.
//! \return
//! - The number of bytes received if successful.
//! - The return value will be 0 when the peer has performed an orderly shutdown.
//! - Otherwise, -1 is returned and errno set to indicate the error. 
// \if SIMULATION
//  @GSIM_F:recvfrom:KSFAM_PPP_OLD:0x13
//  @GSIM_A:2:DATA_SIZE(ARG=3) 
//  @GSIM_A:5:ONE_POINTER
//  @GSIM_A:6:ONE_POINTER
// \endif
int	recvfrom( int s, void *buf, int len, int flags, struct sockaddr *from, int *fromlen);

//! \brief The recvmsg() function call is used to receive a message from a connection-mode or connectionless-mode socket. It is normally used with connectionless-mode sockets
//! because it permits the application to retrieve the source address of received data. 
//! \param s : socket descriptor.
//! \param msg :  parameter containing both the buffer to store the source address 
//! and the buffers for the incoming message. The length and format of the address depend on the address family of the socket. 
//! The "msg_flags" member is ignored on input, but may contain meaningful values on output. 

//! \param flags : Specifies the type of message reception. Values of this argument are formed by logically OR'ing zero or more of the following values (\ref IP_SEND_RECV_FLAGS):: 
//! - \ref MSG_DONTWAIT
//! - \ref MSG_OOB 
//! - \ref MSG_PEEK 
//! - \ref MSG_TRUNC.
//! \return
//! - The length of the message in bytes on successful completion.
//! - If no messages are available to be received and the peer has performed an orderly shutdown, it returns 0. 
//! - Otherwise, -1 is returned and errno set to indicate the error. 
//! \note If a message is too long to fit in the supplied buffer, excess bytes may be discarded depending 
//! on the type of socket the message is received from.
// \if SIMULATION
//  @GSIM_F:recvmsg:KSFAM_PPP:0x12
//  @GSIM_A:2: ONE_POINTER
// \endif
int	recvmsg( int s, struct msghdr *msg, int flags);

//! \brief selectsocket() waits for a number of sockets to change status.
//! It allows to monitor multiple descriptors, waiting until one or more of the descriptors 
//! become "ready" for some class of I/O operation (e.g., input possible). 
//! A descriptor is considered ready if it is possible to perform the corresponding I/O operation (e.g., \ref recv()) 
//! without blocking (refer \ref IP_FD_SET). 

//! \param fdmax : is the highest-numbered descriptor in any of the three sets, plus 1.
//! \param readfds : pointer to structure fd_set. Set of descriptors readfds will be watched to see if characters become available for reading.
//! \param writefds : pointer to structure fd_set. Set of descriptors writefds will be watched to see if it is ok to immediately write on it.
//! \param exceptfds : pointer to structure fd_set. Set of descriptors exceptfds will be watched for exceptions.
//! \param timeout : pointer to structure timeval.
//! \return
//! - On success, select returns the number of descriptors contained in the descriptor sets, which may be zero if the timeout expires before anything interesting happens. 
//! - On error, -1 is returned, and errno is set appropriately; the sets and timeout become undefined, so do not rely on their contents after an error.
//! \note
//! Four macros are provided to manipulate the sets. FD_ZERO() clears a set. FD_SET() and FD_CLR() respectively add and remove a given descriptor from a set. 
//! FD_ISSET() tests to see if a descriptor is part of the set; this is useful after selectsocket() returns. 
// \if SIMULATION
//  @GSIM_F:selectsocket:KSFAM_PPP_OLD:0x12
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
//  @GSIM_A:5:ONE_POINTER
// \endif
int selectsocket( int fdmax, fd_set *readfds, fd_set *writefds,
                  fd_set *exceptfds, struct timeval *timeout);


//! \brief The sendto(), function is used to transmit a message to another transport 
//! end-point. The sendto() function can be used at any time. The 's' socket is created with \ref socket() .
//! \param s : socket descriptor.
//! \param buf : buffer containing the message to send.
//! \param len : length of the message.
//! \param flags : bitwise OR of zero or more of the following (\ref IP_SEND_RECV_FLAGS): 
//! - \ref MSG_OOB
//! - \ref MSG_DONTROUTE 
//! \param to : address of the target.
//! \param tolen : size of the parameter 'to'.
//! \return
//! - On success, these calls return the number of characters sent. 
//! - On error, -1 is returned, and errno is set appropriately. 
// \if SIMULATION
//  @GSIM_F:sendto:KSFAM_PPP_OLD:0x11
//  @GSIM_A:2:DATA_SIZE(ARG=3) 
//  @GSIM_A:5:ONE_POINTER
// \endif
int	sendto( int s, const void *buf, int len, int flags, const struct sockaddr *to, int tolen);

//! \brief sendmsg() is used to transmit a message to another socket.
//! The address of the target is given by "msg.msg_name", with 
//! "msg.msg_namelen" specifying its size. The message to send is pointed to by the elements of the array 
//! "msg.msg_iov". 
//! The sendmsg() call also allows sending ancillary data (also known as control information).
//! \param s : the descriptor of the sending socket.
//! \param msg : pointer to structure msghdr
//! \param flags : the bitwise OR of zero or more of the following flags  (\ref IP_SEND_RECV_FLAGS) : 
//! - \ref MSG_EOR 
//! - \ref MSG_OOB
//! \return
//! - On success, these calls return the number of characters sent.
//! - On error, -1 is returned, and errno is set appropriately.
// \if SIMULATION
//  @GSIM_F:sendmsg:KSFAM_PPP:0x13
//  @GSIM_A:2: ONE_POINTER
// \endif
int	sendmsg( int s, const struct msghdr *msg, int flags);


//! \brief getsockopt() gets the options associated with a socket. Options may exist at multiple protocol levels; 
//! they are always present at the uppermost  "socket" level. When manipulating socket options the level 
//! at which the option resides and the name of the option must be specified. 
//! To manipulate options at the socket level, level is specified as \ref SOL_SOCKET. 
//! To manipulate options at any other level the protocol number of the appropriate protocol controlling the option is supplied. 
//! For example, to indicate that an option is to be interpreted by the TCP protocol, level should be set to the protocol number of TCP.
//! \param s : socket descriptor.
//! \param level : socket level options.
//! \param optname : option name (refer \ref SOCKET_OPTIONS, \ref TCP_OPTIONS). 
//! \param optval : buffer in which the value for the requested option(s) is to be returned.
//! \param optlen : 'optval' buffer length.
//! \note 'optname' parameter and any specified options are passed uninterpreted to the appropriate protocol module 
//! for interpretation. 
//! \return
//! - On success, zero is returned. 
//! - On error, -1 is returned, and errno is set appropriately. 
// \if SIMULATION
//  @GSIM_F:getsockopt:KSFAM_PPP_OLD:0x17
//  @GSIM_A:4:DATA_SIZE(ARG=5)
//  @GSIM_A:5:ONE_POINTER
// \endif
int	getsockopt( int s, int level, int optname, void *optval, int *optlen);



//! \brief setsockopt() sets the options associated with a socket. Options may exist at multiple protocol levels; they are always present at the uppermost "socket" level.
//! When manipulating socket options the level at which the option resides and the name of the option must be specified. 
//! To manipulate options at the socket level, level is specified as \ref SOL_SOCKET. 
//! To manipulate options at any other level the protocol number of the appropriate protocol controlling the option is supplied. 
//! For example, to indicate that an option is to be interpreted by the TCP protocol, level should be set to the protocol number of TCP.
//! \param s : socket descriptor.
//! \param level : socket level options.
//! \param optname : option name (refer \ref SOCKET_OPTIONS, \ref TCP_OPTIONS).
//! \param optval : value to set.
//! \param optlen : length of 'optval'.
//! \return
//! - Upon successful completion, the value 0 is returned.
//! - otherwise the value -1 is returned and the global variable errno is set to indicate the error.
//! \note 'optname' and any specified options are passed uninterpreted to the appropriate protocol module for interpretation. 
// \if SIMULATION
//  @GSIM_F:setsockopt:KSFAM_PPP_OLD:0x18
//  @GSIM_A:4:DATA_SIZE(ARG=5) 
// \endif
int	setsockopt( int s, int level, int optname, const void *optval, int optlen);

//! \brief The shutdownsocket() function call causes all or part of a full-duplex connection 
//! on the socket associated with 's' to be shut down. 
//! \param s : specifies the file descriptor of the socket. 
//! \param how : specifies the type of shutdown. The values are as follows (\ref IP_SHUTDOWN_METHOD) :
//! - \ref SHUT_RD : further receptions will be disallowed. 
//! - \ref SHUT_WR : further transmissions will be disallowed.
//! - \ref SHUT_RDWR : further receptions and transmissions will be disallowed. 
//! \return
//! - On success, zero is returned.
//! - On error, -1 is returned, and errno is set appropriately. 
// \if SIMULATION
//  @GSIM_F:shutdownsocket:KSFAM_PPP_OLD:0x15
// \endif
int	shutdownsocket( int s, int how);

//! \brief socket creates an endpoint for communication and returns its descriptor.
//! \param domain : domain parameter specifies a communication domain ; this selects the protocol family which will be used for communication.
//! \param type : specifies the communication semantics.
//! Currently defined types are :
//! - \ref SOCK_STREAM 
//! - \ref SOCK_DGRAM 
//! - \ref SOCK_RAW 
//! \param protocol : protocol used (\ref IP_PROTOCOLS).
//! \return 
//! - On success, a file descriptor for the new socket is returned. 
//! - On error, -1 is returned, and errno is set appropriately. 
// \if SIMULATION
//  @GSIM_F:socket:KSFAM_PPP_OLD:0x10
// \endif
int	socket( int domain, int type, int protocol);


#define recv( s, buf, len, flags)   recvfrom( s, buf, len, flags, NULL, NULL)
#define readsocket( s, buf, len)    recvfrom( s, buf, len, 0, NULL, NULL)


//! \brief The send() call may be used only when the socket is in a connected state 
//! (so that the intended recipient is known). The only difference between send() and writesocket() 
//! is the presence of flags. With zero flags parameter, send() is equivalent to writesocket(). 
//! Also, send(s,buf,len,flags) is equivalent to sendto(s,buf,len,flags,NULL,0). 
#define send( s, buf, len, flags)   sendto( s, buf, len, flags, NULL, 0)

#define writesocket( s, buf, len)   sendto( s, buf, len, 0, NULL, 0)

//! @}





// Internet address manipulation routines.
// !! Please use the following functions instead of the standard ones.
// !! Problem of MMU.

//! \addtogroup  IP_ADDRESS_Management 
//! @{

//! \brief This function converts an ASCII TCP/IP address to its 4 bytes format (struct in_addr).
//! \param addr : TCP/IP address - ASCII format ('www.xxx.yyy.zzz').
//! \return
//! - the converted address (4 bytes format).
//! - -1 when the ASCII address is not rightly formatted. 
// \if SIMULATION
//  @GSIM_F:__inet_addr:KSFAM_PPP:0x1A
// \endif
unsigned long  __inet_addr( const char *addr);

//! \brief This function converts an ASCII TCP/IP address to its 4 bytes format (struct in_addr).
//! \param name : TCP/IP address - ASCII format ('www.xxx.yyy.zzz').
//! \param addr : Converted address - 4 bytes format.
//! \return 
//! - 1 if the address has been rightly converted.
//! - 0 otherwise.
// \if SIMULATION
//  @GSIM_F:__inet_aton:KSFAM_PPP:0x1B
//  @GSIM_A:2:ONE_POINTER
// \endif
int __inet_aton(const char *name, struct in_addr *addr );

//! \brief This function is the inverse of the function \ref __inet_addr(). 
//! It converts a 4 bytes address in its ASCII format.
//! \param addr : TCP/IP address - 4 bytes format.
//! \return
//! - Converted address - ASCII format ('www.xxx.yyy.zzz').
//! \note 
//! The returned character string is NULL terminated. It is allocated by the function \ref __inet_ntoa()
//! and belongs to this one. It must copied by the calling function and must not be freed.
// \if SIMULATION
//  @GSIM_F:__inet_ntoa:KSFAM_PPP:0x1C
// \endif
char   *__inet_ntoa( struct in_addr addr);

// Network/host byte order conversions.
#define ConstBSwap16(a)   (((((unsigned short) (a)) << 8)&0xff00U) |		\
                           ((((unsigned short) (a)) >> 8)&0x00ffU) )
#define ConstBSwap32(a)   (((((unsigned int) (a)) << 24)&0xff000000UL) |	\
                           ((((unsigned int) (a)) <<  8)&0x00ff0000UL) |	\
                           ((((unsigned int) (a)) >>  8)&0x0000ff00UL) |	\
                           ((((unsigned int) (a)) >> 24)&0x000000ffUL) )

#define ntohs( a)   ConstBSwap16( a)  //!< Macro reversing a 16 bit value.
#define ntohl( a)   ConstBSwap32( a)  //!< Macro reversing a 32 bit value.
#define htons( a)   ConstBSwap16( a)  //!< Macro reversing a 16 bit value.
#define htonl( a)   ConstBSwap32( a)  //!< Macro reversing a 32 bit value.

//! @}
//! @}

//! \defgroup IP_DNS 

//! @{

// Resolver
// Protocol configuration options

//! \defgroup DNS_OPTIONS DNS resolver options.
//! \brief DNS resolver options.
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

//! \brief This function gets an option parameter of the DNS resolver.
//! \param opt : option to set (\ref DNS_OPTIONS).
//! \param optval : Value
//! \return
//! - 0 if OK.
//! - a negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:ResolverGetOption:KSFAM_PPP:0x14
// \endif
int ResolverGetOption( int opt, void * optval );

//! \brief This function sets an option parameter of the DNS resolver.
//! \param opt : option to set (\ref DNS_OPTIONS).
//! \param optval : Value.
//! \return 
//! - 0 if OK.
//! - a negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:ResolverSetOption:KSFAM_PPP:0x15
// \endif
int ResolverSetOption( int opt, void * optval );

// Common returned codes (not error codes...)
//! \defgroup DNS_ERROR_CODES Resolver error codes.
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
//! \brief Error codes returned by \ref DNS_GetIpAddress and \ref DNS_GetDomainName functions.
//! @{

#define DNS_OK                         ( 0) //!< No error.
#define DNS_BAD_PARAMETER              (-1) //!< At least one input parameter is invalid.
#define DNS_OUTPUT_BUFFER_TOO_SHORT    (-2) //!< Buffer is too short.
#define DNS_HOST_NOT_FOUND             (-3) //!< DNS request failed.

//! @}

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


// Host information.
//! \brief Host information structure.
struct hostent 
{
    char   *h_name;         //!< Host name.
    char  **h_aliases;      //!< List of aliases.
    int     h_addrtype;     //!< Type of address (always AF_INET).
    int     h_length;       //!< Length of address.
    char  **h_addr_list;    //!< List of addresses.
};

#define h_addr h_addr_list[0]

// Error codes.
#define HOST_NOT_FOUND  1
#define TRY_AGAIN       2
#define NO_RECOVERY     3
#define NO_DATA_ERR     4
#define NO_ADDRESS      4


// Threads-safe routines.
// !! To use instead of the functions :
// struct hostent * gethostbyname( char *name);
// struct hostent * gethostbyaddr( char *addr, int len, int type);
// 

//! \brief The gethostbyname_r() function returns a structure of type hostent for the given host name. 
//! It searches for information for a host with the hostname specified by the character-string parameter 'name'. 
//! It provides a reentrant interface for the function gethostbyname(). 
//! The reentrant interface performs the same operation as the non-reentrant counterpart "gethostbyname()".
//! It uses a buffer supplied by the caller to store returned results, and it is safe for use 
//! in both single-threaded and multi-threaded applications. 
//! \param name : name is either a host name, or an Ipv4 address in standard dot notation.
//! \param result : pointer to struct hostent.
//! \param buf : buffer.
//! \param buflen : length of the buffer.
//! \param err : error.
//! \return
//! - pointer to a struct hostent if the function successfully located the requested entry.
//! - otherwise it will return NULL.
// \if SIMULATION
//  @GSIM_F:gethostbyname_r:KSFAM_PPP_OLD:0x31
//  @GSIM_A:0:ONE_POINTER
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:DATA_SIZE(buflen)
//  @GSIM_A:5:ONE_POINTER
// \endif
struct hostent * gethostbyname_r( const char *name, struct hostent *result,
                                  void *buf, int buflen, int *err );


//! \brief The gethostbyaddr_r() function returns a structure of type hostent for the given host address 'addr' 
//! of length 'len' and address type 'type'. The valid address type \ref AF_INET. 
//! The host address argument is a pointer to a struct of a type depending on the address type, 
//! for example a struct in_addr * (probably obtained via a call to __inet_addr()) for address type \ref AF_INET. 
//! It provides a reentrant interface for the function gethostbynaddr(). 
//! The reentrant interface performs the same operation as the non-reentrant counterpart "gethostbyaddr()".
//! It uses a buffer supplied by the caller to store returned results, and it is safe for use 
//! in both single-threaded and multi-threaded applications. 
//! \param addr : host address.
//! \param len : host address length.
//! \param type : address type.
//! \param result : pointer to struct hostent.
//! \param buf : buffer.
//! \param buflen : length of the buffer.
//! \param err : error.
//! \return
//! - pointer to a struct hostent if the function successfully resolved the requested a.
//! - otherwise it will return NULL.
struct hostent * gethostbyaddr_r( const char *addr, int len, int type,
								  struct hostent *result, void *buf, int buflen, int *err );

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
//! @}


//! \brief This function gets an option parameter of the Ethernet link.
//! On products that have an Ethernet interface through a Bluetooth base (EFT930, iWL2XX) it returns the local Ethernet interface's parameters,
//! not the ones from the base's interface.
//! For such products one should use USQ_EthernetConfig() which will get the relevant Ethernet parameters.
//! \param nOption : Option to get.
//! \param pValue : Value.
//! \return
//! - 0 if OK.
//! - a negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:EthernetGetOption:KSFAM_PPP:0x16
// \endif
int EthernetGetOption( int nOption, void *pValue );


//! \brief This function sets an option parameter of the Ethernet link.
//! \param nOption : Option to set.
//! \param pValue : Value.
//! \return
//! - 0 if OK.
//! - a negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:EthernetSetOption:KSFAM_PPP:0x17
// \endif
int EthernetSetOption( int nOption, void *pValue );


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

#define __DFL_ERROR_BT_NO_ASSOCIATION		-8	//!< No base is associated to the terminal
#define __DFL_ERROR_BT_NO_PERIPHERAL		-9	//!< Peripheral not reachable (no base associated with this peripheral)
#define __DFL_ERROR_BT_BASE_NOT_AVAILABLE	-10	//!< Base not reachable
#define __DFL_ERROR_BT_NO_BLUETOOTH			-11	//!< The terminal has no Bluetooth
//! @}

typedef void * ETHCONF_HANDLE;					//!< Deprecated (use \ref DFLCONF_HANDLE instead)
//! \brief Definition of DLFCONF_HANDLE.
typedef void * DFLCONF_HANDLE;

//! \brief This function return the status of the Bluetooth base providing an Ethernet interface. 
//! \return 
//! - __DFL_OK if the base is available.
//! - __DFL_ERROR_BT_NO_ASSOCIATION if no Bluetooth base is associated with the terminal or if the terminal has no Bluetooth.
//! - __DFL_ERROR_BT_NO_PERIPHERAL if no Bluetooth base is providing an Ethernet interface.
//! - __DFL_ERROR_BT_BASE_NOT_AVAILABLE if the Bluetooth base is not available.
//! \note On a Bluetooth base the function takes at least one second to execute.
int EthernetGetBluetoothBaseStatus(void);

//! \brief This function loads the default parameters of the IP Ethernet link.
//! \param pnError : Output parameter which returns the error code of the loading operation :
//! - \ref __DFL_OK
//! - \ref __DFL_ERROR_HW_ADDRESS_NOT_FOUND
//! - \ref __DFL_ERROR_OPEN_FAILED
//! - \ref __DFL_ERROR_LOADING
//! \return 
//! - An handle on the IP configuration (>=0) if OK.
//! - __DFL_ERROR_BT_NO_ASSOCIATION if no Bluetooth base is associated with the terminal or if the terminal has no Bluetooth.
//! - __DFL_ERROR_BT_NO_PERIPHERAL if no Bluetooth base is providing an Ethernet interface.
//! - __DFL_ERROR_BT_BASE_NOT_AVAILABLE if the Bluetooth base is not available.
//! \note On a Bluetooth base the function takes at least one second to execute.
// \if SIMULATION
//  @GSIM_F:__LoadDefaultOptions:KSFAM_ETHCONF:0x01
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:1:ONE_POINTER 
// \endif
DFLCONF_HANDLE __LoadDefaultOptions ( int *pnError );

//! \brief This function unloads a configuration previously loaded using the 
//! function "__LoadDefaultOptions". The configuration is lost (e.g it is not saved). The configuration handle is released. It must not be used anymore.
//! \param handle : Handle on the configuration to unload.
//! \return 
//! - \ref __DFL_OK
//! - A negative error code otherwise.
//! - \ref __DFL_ERROR_INVALID_HANDLE
// \if SIMULATION
//  @GSIM_F:__UnloadDefaultOptions:KSFAM_ETHCONF:0x02
//  @GSIM_A:1:ONE_ADDRESS
// \endif
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
// \if SIMULATION
//  @GSIM_F:__SetDefaultOption:KSFAM_ETHCONF:0x05
//  @GSIM_A:1:ONE_ADDRESS
// \endif
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
// \if SIMULATION
//  @GSIM_F:__GetDefaultOption:KSFAM_ETHCONF:0x04
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:3:USE_CODE
// \endif
int __GetDefaultOption ( DFLCONF_HANDLE hConf, int nOption, void *pValue );

//! \brief This function saves the configuration as the default one. The terminal is
//! automatically rebooted and the new saved configuration is used.
//! \param hConf : Handle on the configuration to save.
//! \return 
//! - The negative error code 
//! - \ref __DFL_ERROR_INVALID_HANDLE
//! - or never returns.
//! \note The option \ref __DFL_BT_NO_REBOOT can be set to a non zero value to avoid a reboot on a Bluetooth product not connected to its base.
// \if SIMULATION
//  @GSIM_F:__SaveDefaultOptions:KSFAM_ETHCONF:0x03
//  @GSIM_A:1:ONE_ADDRESS 
// \endif
int __SaveDefaultOptions ( DFLCONF_HANDLE hConf );




// Global error number.
//! \brief Global error number (ERRNO).
extern int h_errno;

//! \brief This function returns the current value of the internal error code (ERRNO).
//! \return
//! The internal error code value (ERRNO).
// \if SIMULATION
//  @GSIM_F:GetErrno:KSFAM_PPP:0x18
// \endif
int  GetErrno( void);


//! \brief This function sets the value of the internal error code (ERRNO).
//! \param err : Error code.
//! \return None.
// \if SIMULATION
//  @GSIM_F:SetErrno:KSFAM_PPP:0x19
// \endif
void SetErrno( int err);

//


// Ping function.


//! \brief This function tests if a remote address is reachable., by sending an ICMP request (Ping).
//! \param addr : Remote address to reach
//! \param nTimeout : Waiting delay (in 10 ms) for the answer.
//! \return
//! - 0 if OK.
//! - a negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:__Ping:KSFAM_PPP:0x1F
// \endif
int __Ping( unsigned int addr, unsigned int nTimeout );

// Route settings management.

//! \brief This function gets the gateway address of the default route.
//! \return None.
// \if SIMULATION
//  @GSIM_F:__GetDefaultRoute:KSFAM_PPP:0x1D
//  @GSIM_A:2:ONE_POINTER
// \endif
void __GetDefaultRoute( unsigned int *gateway_addr );

//! \brief This function sets the gateway address of the default route.
//! \param gateway_addr : Gateway address to set.
//! \return None.
// \if SIMULATION
//  @GSIM_F:__SetDefaultRoute:KSFAM_PPP:0x1E
// \endif
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
