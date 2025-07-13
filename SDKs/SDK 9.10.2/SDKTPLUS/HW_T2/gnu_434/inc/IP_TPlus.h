
#ifndef __IP_TPLUS_H__
#define __IP_TPLUS_H__

// Definitions for Telium_Socket_selectsocket()
//! \defgroup  IP_FD_SET Descriptor set management.
//! \ingroup IP_BSD
//! \brief Socket descriptor set management (used for \ref Telium_Socket_select().
//! @{

#define TELIUM_FD_MAX    (1024)

typedef struct
{
	unsigned long fds[TELIUM_FD_MAX/(8*sizeof(unsigned long))];
}Telium_fd_set;

void Telium_FD_ZERO( Telium_fd_set* pFdSet );
void Telium_FD_SET( int nSocket, Telium_fd_set* pFdSet );
void Telium_FD_CLR( int nSocket, Telium_fd_set* pFdSet );
int  Telium_FD_ISSET( int nSocket, Telium_fd_set* pFdSet );

//! \brief FD_ZERO() initializes a descriptor set 'fdset' to the null set.
#define TELIUM_FD_ZERO(pFdSet)             Telium_FD_ZERO(pFdSet)

//! \brief FD_SET() includes a particular descriptor 'fd' in 'fdset'.
#define TELIUM_FD_SET(nSocket,pFdSet)      Telium_FD_SET(nSocket,pFdSet)

//! \brief FD_CLR() removes 'fd' from 'fdset'.
#define TELIUM_FD_CLR(nSocket,pFdSet)      Telium_FD_CLR(nSocket,pFdSet)

//! \brief FD_ISSET() call returns non zero if 'fd' is a member of 'fdset'
//! Otherwise, it returns zero.
#define TELIUM_FD_ISSET(nSocket,pFdSet)    Telium_FD_ISSET(nSocket,pFdSet)

struct Telium_timeval
{
	long	tv_sec;							/*!< seconds */
	long	tv_usec;						/*!< microseconds */
};
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \ingroup IP_BSD
//! @{

// Level of option.
#define TELIUM_SOL_SOCKET		0xffffU		 //!< Options for socket level.
#define TELIUM_SO_ERROR        0x1007		 //!< Get error status and clear (ro).

//
#define TELIUM_INADDR_ANY         (unsigned int)0x00000000   //!< Unspecified IP address (all zeroes).
#define TELIUM_INADDR_LOOPBACK    0x0100007f                 //!< Loopback address.
#define TELIUM_INADDR_BROADCAST   (unsigned int)0xffffffff   //!< Broadcast address 
#define TELIUM_INADDR_NONE        0xffffffff                 //!< Address none (same as broadcast)

// Commands for Telium_Socket_fnctl().
#define TELIUM_F_GETFL         3 	//!< Read the socket status flags. 
#define TELIUM_F_SETFL         4	//!< Set the socket status flags. 

#define TELIUM_O_NONBLOCK      0x0004	//!< Non-blocking socket mode


// Commands for Telium_Socket_ioctlsocket().
#define TELIUM_IOC_OUT         0x40000000L   //!< Copy out parameters.
#define TELIUM_IOC_IN          0x80000000L   //!< Copy in parameters.
#define TELIUM_IOCPARM_MASK    0x1fff        //!< Parameter length, at most 13 bits.
#define TELIUM__IOC(inout,group,num,len) \
        (inout | (((long)len & TELIUM_IOCPARM_MASK) << 16) | ((group) << 8) | (num))
#define TELIUM__IOR(g,n,t)     TELIUM__IOC(TELIUM_IOC_OUT,   (g), (n), sizeof(t))
#define TELIUM__IOW(g,n,t)     TELIUM__IOC(TELIUM_IOC_IN,    (g), (n), sizeof(t))

#define TELIUM_FIONBIO         TELIUM__IOW('f', 126, int)   //!< Set/clear nonblocking io.
#define TELIUM_FIONREAD        TELIUM__IOR('f', 127, int)   //!< Get # bytes to read.
#define TELIUM_SIOCATMARK      TELIUM__IOR('s',  7, int)    //!< At oob mark ?

//! \brief Generic socket address.
struct Telium_sockaddr
{
    unsigned char     sa_len;						//!< Total length.
    unsigned char     sa_family;					//!< Address family.
    unsigned char     sa_data[14];					//!< Address value.
};

//! \brief Socket address in internet domain.
struct Telium_in_addr
{
    unsigned int      s_addr;						//!< 32 bits IP address, net byte order.
};

//! \brief Generic socket_in address.
struct Telium_sockaddr_in
{
    unsigned char         sin_len;						//!< Total length (16).
    unsigned char         sin_family;					//!< TELIUM_AF_INET.
    unsigned short        sin_port;						//!< 16 bits port number, net byte order.
    struct Telium_in_addr sin_addr;						//!< 32 bits IP address.
    unsigned char         sin_zero[8];					//!< Unused.
};

//! \brief Structure used by readv/writev/Telium_Socket_recvmsg/Telium_Socket_writemsg.
struct Telium_iovec
{
    void   *iov_base;
    int     iov_len;
};

//! \brief Used by SO_LINGER socket option.
struct Telium_linger 
{
    int     l_onoff;
    int     l_linger;
};

//! \brief Message structure for Telium_Socket_sendmsg/Telium_Socket_recvmsg.
struct Telium_msghdr
{
    char*					msg_name;						//!< Optional address.
    unsigned int			msg_namelen;					//!< Address size.
    struct Telium_iovec*	msg_iov;						//!< Scatter/gather array.
    unsigned int			msg_iovlen;						//!< Number of elements in msg_iov.
    char*					msg_control;					//!< Ancillary data.
    unsigned int			msg_controllen;					//!< Ancillary data buffer length.
    int						msg_flags;						//!< flags on received message.
};

//! \brief 
struct Telium_cmsghdr 
{
	unsigned int	cmsg_len;						//!< Data byte count, including hdr.
	int				cmsg_level;						//!< Originating protocol.
	int				cmsg_type;						//!< Protocol-specific type.
									// Followed by unsigned char  cmsg_data[];.
};

// Prototypes.
//! \brief Telium_Socket_accept() extracts the first connection request on the queue of pending connections,
//! creates a new socket with the same properties of socket, and allocates a new file descriptor for the socket.
//! The argument socket is a socket that has been created with \ref Telium_Socket_socket(), bound to an address with \ref Telium_Socket_bind(),
//! and is listening for connections after a \ref Telium_Socket_listen().
//! \param s : socket descriptor.
//! \param addr : pointer to structure sockaddr. Output parameter that is filled in with the address of the connecting entity,
//! as known to the communications layer. The exact format of the address parameter is determined by the domain 
//! in which the communication is occurring.
//! \param addrlen : this parameter is a value-result parameter; it should initially contain the amount of space pointed to by address; on return it will contain the actual length (in bytes) of the address returned.
//! \return
//! - On success, the descriptor for the accepted socket is returned.
//! - On error, -1 is returned, and errno is set appropriately. 
int	Telium_Socket_accept( int s, struct Telium_sockaddr *addr, int *addrlen);

//! \brief Telium_Socket_bind gives the socket 's' the local address 'my_addr'. Traditionally, this is called 'assigning a name to a 
//! socket.' .When a socket is created with Telium_Socket_socket(), it exists in a name space (address family) but has no name assigned.
//! \param s : socket descriptor
//! \param my_addr : pointer to structure sockaddr.
//! \param addrlen : length of returned data.
//! \return
//! - On success, zero is returned.
//! - On error, -1 is returned, and errno is set appropriately. 
int	Telium_Socket_bind( int s, const struct Telium_sockaddr *my_addr, int addrlen);

//! \brief This function closes an existing socket.
//! \param s : descriptor identifying the socket to close.
//! \return
//! - On success, zero is returned.
//! - On error, -1 is returned, and errno is set appropriately. 
int Telium_Socket_close( int s);

//! \brief  The Telium_Socket_connect() function call connects the socket referred to by the file descriptor 's'
//! to the address specified by 'serv_addr'. 
//! The addrlen argument specifies the size of serv_addr. The format of the address in serv_addr is determined by the address space of the socket sockfd; 
//! see \ref Telium_Socket_socket() for further details.
//! If the socket 's' is of type \ref TELIUM_SOCK_DGRAM then 'serv_addr' is the address to which datagrams are sent
//! by default, and the only address from which datagrams are received. 
//! If the socket is of type \ref TELIUM_SOCK_STREAM, this call attempts to make a connection to the socket
//! that is bound to the address specified 'by serv_addr'.
//! \note Generally, connection-based protocol sockets may successfully \ref Telium_Socket_connect() only once.
//! Connectionless protocol sockets may use \ref Telium_Socket_connect() multiple times to change their association.
//! Connectionless sockets may dissolve the association by connecting to an address with the 
//! sa_family member of sockaddr set to \ref TELIUM_AF_UNSPEC. 

//! \param s : socket descriptor
//! \param serv_addr : remote server address.
//! \param addrlen : length (in bytes) of the address returned.
//! \return
//! - On success (the connection or binding succeeds), zero is returned. 
//! - On error, -1 is returned, and errno is set appropriately. 
int	Telium_Socket_connect( int s, const struct Telium_sockaddr *serv_addr, int addrlen);

//! \brief Telium_Socket_getpeername() returns the name of the peer connected to socket s. The namelen parameter should be initialized to indicate the amount of space pointed to by name. 
//! On return it contains the actual size of the name returned (in bytes). 
//! The name is truncated if the buffer provided is too small.
//! \param s : socket.
//! \param name : pointer to structure sockaddr.
//! \param namelen : amount of space pointed to by name.
//! \return
//! - On success, zero is returned.
//! - On error, -1 is returned, and errno is set appropriately.
int	Telium_Socket_getpeername( int s, struct Telium_sockaddr *name, int *namelen);

//! \brief Telium_Socket_getsockname() returns the current name for the specified socket. 
//! The 'namelen' parameter should be initialized to indicate the amount of space pointed to by 'name'. 
//! On return it contains the actual size of the name returned (in bytes).
//! \param s : socket descriptor.
//! \param name : pointer to structure sockaddr.
//! \param namelen : amount of space pointed to by 'name'.
//! \return
//! - On success, zero is returned.
//! - On error, -1 is returned, and errno is set appropriately.
int	Telium_Socket_getsockname( int s, struct Telium_sockaddr *name, int *namelen);


//! \brief Telium_Socket_ioctl() manipulates the I/O mode of a socket.
//! \param s : socket descriptor.
//! \param cmd : command to execute.
//! \param arg : command parameter.
//! \return
//! - On success, zero is returned. 
//! - On error, -1 is returned, and errno is set appropriately. 
int Telium_Socket_ioctl( int s, long cmd, int *arg);

//! \brief Telium_Socket_listen() specifies the acceptance and the queue of incoming connections.
//! To accept connections, a socket is first created with \ref Telium_Socket_socket(),
//! a willingness to accept incoming connections and a queue limit for incoming connections 
//! are specified with \ref Telium_Socket_listen(), and then the connections are accepted with \ref Telium_Socket_accept(). 
//! \param s : socket identifier.
//! \param backlog : the maximum length for the queue of pending connections.
//! \return
//! - On success, zero is returned.
//! - On error, -1 is returned, and errno is set appropriately. 
//! \note The Telium_Socket_listen() call applies only to sockets of type \ref TELIUM_SOCK_STREAM. 
int	Telium_Socket_listen( int s, int backlog);

//! \brief The Telium_Socket_recvfrom() call is used to receive messages from a socket, 
//! and may be used to receive data on a socket whether or not it is connection-oriented. 
//! \param s : socket.
//! \param buf : source address.
//! \param len : buffer length.
//! \param flags : the flags argument is formed by OR'ing one or more of the following values (\ref IP_SEND_RECV_FLAGS) :
//! - \ref TELIUM_MSG_DONTWAIT 
//! - \ref TELIUM_MSG_OOB 
//! - \ref TELIUM_MSG_PEEK 
//! - \ref TELIUM_MSG_TRUNC 
//! - \ref TELIUM_MSG_WAITALL
//! \param from : pointer to structure sockaddr. If 'from' is not NULL, and the underlying protocol provides the source address, this source address is filled in.
//! \param fromlen : a value-result parameter, initialized to the size of the buffer associated with from, and modified on return to indicate the actual size of the address stored there.
//! \return
//! - The number of bytes received if successful.
//! - The return value will be 0 when the peer has performed an orderly shutdown.
//! - Otherwise, -1 is returned and errno set to indicate the error. 
int	Telium_Socket_recvfrom( int s, void *buf, int len, int flags, struct Telium_sockaddr *from, int *fromlen);

//! \brief The Telium_Socket_recv() call is used to receive messages from a socket, 
//! and may be used to receive data on a socket whether or not it is connection-oriented. 
//! \param s : socket.
//! \param buf : source address.
//! \param len : buffer length.
//! \param flags : the flags argument is formed by OR'ing one or more of the following values (\ref IP_SEND_RECV_FLAGS) :
//! - \ref TELIUM_MSG_DONTWAIT 
//! - \ref TELIUM_MSG_OOB 
//! - \ref TELIUM_MSG_PEEK 
//! - \ref TELIUM_MSG_TRUNC 
//! - \ref TELIUM_MSG_WAITALL
//! \return
//! - The number of bytes received if successful.
//! - The return value will be 0 when the peer has performed an orderly shutdown.
//! - Otherwise, -1 is returned and errno set to indicate the error. 
int Telium_Socket_recv( int s, void *buf, int len, int flags );

//! \brief The Telium_Socket_read() call is used to receive messages from a socket, 
//! and may be used to receive data on a socket whether or not it is connection-oriented. 
//! \param s : socket.
//! \param buf : source address.
//! \param len : buffer length.
//! \return
//! - The number of bytes received if successful.
//! - The return value will be 0 when the peer has performed an orderly shutdown.
//! - Otherwise, -1 is returned and errno set to indicate the error. 
int Telium_Socket_read( int s, void* buf, int len );

//! \brief The Telium_Socket_recvmsg() function call is used to receive a message from a connection-mode or connectionless-mode socket. It is normally used with connectionless-mode sockets
//! because it permits the application to retrieve the source address of received data. 
//! \param s : socket descriptor.
//! \param msg :  parameter containing both the buffer to store the source address 
//! and the buffers for the incoming message. The length and format of the address depend on the address family of the socket. 
//! The "msg_flags" member is ignored on input, but may contain meaningful values on output. 
//! \param flags : Specifies the type of message reception. Values of this argument are formed by logically OR'ing zero or more of the following values (\ref IP_SEND_RECV_FLAGS):: 
//! - \ref TELIUM_MSG_DONTWAIT
//! - \ref TELIUM_MSG_OOB 
//! - \ref TELIUM_MSG_PEEK 
//! - \ref TELIUM_MSG_TRUNC.
//! \return
//! - The length of the message in bytes on successful completion.
//! - If no messages are available to be received and the peer has performed an orderly shutdown, it returns 0. 
//! - Otherwise, -1 is returned and errno set to indicate the error. 
//! \note If a message is too long to fit in the supplied buffer, excess bytes may be discarded depending 
//! on the type of socket the message is received from.
int	Telium_Socket_recvmsg( int s, struct Telium_msghdr *msg, int flags);

//! \brief Telium_Socket_selectsocket() waits for a number of sockets to change status.
//! It allows to monitor multiple descriptors, waiting until one or more of the descriptors 
//! become "ready" for some class of I/O operation (e.g., input possible). 
//! A descriptor is considered ready if it is possible to perform the corresponding I/O operation (e.g., \ref Telium_Socket_recv()) 
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
//! Four macros are provided to manipulate the sets. TELIUM_FD_ZERO() clears a set. TELIUM_FD_SET() and TELIUM_FD_CLR() respectively add and remove a given descriptor from a set. 
//! TELIUM_FD_ISSET() tests to see if a descriptor is part of the set; this is useful after Telium_Socket_selectsocket() returns. 
int Telium_Socket_select( int fdmax, Telium_fd_set *readfds, Telium_fd_set *writefds,
                  Telium_fd_set *exceptfds, struct Telium_timeval *timeout);

//! \brief The Telium_Socket_send(), function is used to transmit a message to another transport 
//! end-point. The Telium_Socket_send() function can be used at any time. The 's' socket is created with \ref Telium_Socket_socket() .
//! \param s : socket descriptor.
//! \param buf : buffer containing the message to send.
//! \param len : length of the message.
//! \param flags : bitwise OR of zero or more of the following (\ref IP_SEND_RECV_FLAGS): 
//! - \ref TELIUM_MSG_OOB
//! - \ref TELIUM_MSG_DONTROUTE 
//! \return
//! - On success, these calls return the number of characters sent. 
//! - On error, -1 is returned, and errno is set appropriately. 
int Telium_Socket_send( int s, const void *buf, int len, int flags );

//! \brief The Telium_Socket_write(), function is used to transmit a message to another transport 
//! end-point. The Telium_Socket_write() function can be used at any time. The 's' socket is created with \ref Telium_Socket_socket() .
//! \param s : socket descriptor.
//! \param buf : buffer containing the message to send.
//! \param len : length of the message.
//! \return
//! - On success, these calls return the number of characters sent. 
//! - On error, -1 is returned, and errno is set appropriately. 
int Telium_Socket_write( int s, const void *buf, int len );

//! \brief The Telium_Socket_sendto(), function is used to transmit a message to another transport 
//! end-point. The Telium_Socket_sendto() function can be used at any time. The 's' socket is created with \ref Telium_Socket_socket() .
//! \param s : socket descriptor.
//! \param buf : buffer containing the message to send.
//! \param len : length of the message.
//! \param flags : bitwise OR of zero or more of the following (\ref IP_SEND_RECV_FLAGS): 
//! - \ref TELIUM_MSG_OOB
//! - \ref TELIUM_MSG_DONTROUTE 
//! \param to : address of the target.
//! \param tolen : size of the parameter 'to'.
//! \return
//! - On success, these calls return the number of characters sent. 
//! - On error, -1 is returned, and errno is set appropriately. 
int	Telium_Socket_sendto( int s, const void *buf, int len, int flags, const struct Telium_sockaddr *to, int tolen);

//! \brief Telium_Socket_sendmsg() is used to transmit a message to another socket.
//! The address of the target is given by "msg.msg_name", with 
//! "msg.msg_namelen" specifying its size. The message to send is pointed to by the elements of the array 
//! "msg.msg_iov". 
//! The Telium_Socket_sendmsg() call also allows sending ancillary data (also known as control information).
//! \param s : the descriptor of the sending socket.
//! \param msg : pointer to structure msghdr
//! \param flags : the bitwise OR of zero or more of the following flags  (\ref IP_SEND_RECV_FLAGS) : 
//! - \ref TELIUM_MSG_EOR 
//! - \ref TELIUM_MSG_OOB
//! \return
//! - On success, these calls return the number of characters sent.
//! - On error, -1 is returned, and errno is set appropriately.
int	Telium_Socket_sendmsg( int s, const struct Telium_msghdr *msg, int flags);

//! \brief Telium_Socket_getsockopt() gets the options associated with a socket. Options may exist at multiple protocol levels; 
//! they are always present at the uppermost  "socket" level. When manipulating socket options the level 
//! at which the option resides and the name of the option must be specified. 
//! To manipulate options at the socket level, level is specified as \ref TELIUM_SOL_SOCKET. 
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
int	Telium_Socket_getsockopt( int s, int level, int optname, void *optval, int *optlen);

//! \brief Telium_Socket_setsockopt() sets the options associated with a socket. Options may exist at multiple protocol levels; they are always present at the uppermost "socket" level.
//! When manipulating socket options the level at which the option resides and the name of the option must be specified. 
//! To manipulate options at the socket level, level is specified as \ref TELIUM_SOL_SOCKET. 
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
int	Telium_Socket_setsockopt( int s, int level, int optname, const void *optval, int optlen);

//! \brief The Telium_Socket_shutdown() function call causes all or part of a full-duplex connection 
//! on the socket associated with 's' to be shut down. 
//! \param s : specifies the file descriptor of the socket. 
//! \param how : specifies the type of shutdown. The values are as follows (\ref IP_SHUTDOWN_METHOD) :
//! - \ref TELIUM_SHUT_RD : further receptions will be disallowed. 
//! - \ref TELIUM_SHUT_WR : further transmissions will be disallowed.
//! - \ref TELIUM_SHUT_RDWR : further receptions and transmissions will be disallowed. 
//! \return
//! - On success, zero is returned.
//! - On error, -1 is returned, and errno is set appropriately. 
int	Telium_Socket_shutdown( int s, int how);

//! \brief socket creates an endpoint for communication and returns its descriptor.
//! \param domain : domain parameter specifies a communication domain ; this selects the protocol family which will be used for communication.
//! \param type : specifies the communication semantics.
//! Currently defined types are :
//! - \ref TELIUM_SOCK_STREAM 
//! - \ref TELIUM_SOCK_DGRAM 
//! - \ref TELIUM_SOCK_RAW 
//! \param protocol : protocol used (\ref IP_PROTOCOLS).
//! \return 
//! - On success, a file descriptor for the new socket is returned. 
//! - On error, -1 is returned, and errno is set appropriately. 
int	Telium_Socket_socket( int domain, int type, int protocol);
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup ADDRESS_FAMILY Address family
//! \ingroup IP_BSD
//! \brief Address family.
//! @{
#define TELIUM_AF_UNSPEC        0       //!< Unspecified.
#define TELIUM_AF_INET          2       //!< Internetwork: UDP, TCP, etc.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Protocol family (== address family).

//! \defgroup PROTOCOL_FAMILY Protocol family
//! \ingroup IP_BSD
//! \brief Protocol family.
//! @{
#define TELIUM_PF_UNSPEC          0         //!< Unspecified.
#define TELIUM_PF_INET            2         //!< Internet IP Protocol.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Type of socket.
//! \defgroup SOCKET_TYPE Socket type
//! \ingroup IP_BSD
//! \brief Socket type.
//! @{
#define TELIUM_SOCK_STREAM        1         //!< Type of socket: stream (connection) type socket (TCP).
#define TELIUM_SOCK_DGRAM         2         //!< Type of socket: datagram (connection less) socket (UDP).
#define TELIUM_SOCK_RAW           3         //!< Type of socket: raw socket.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Protocols.
//! \defgroup  IP_PROTOCOLS IP protocols
//! \ingroup IP_BSD
//! \brief IP protocols.
//! @{
#define TELIUM_IPPROTO_IP         0         //!< Dummy protocol for TCP.
#define TELIUM_IPPROTO_HOPOPTS    0         //!< IPv6 Hop-by-Hop options.
#define TELIUM_IPPROTO_ICMP       1         //!< Internet Control Message Protocol.
#define TELIUM_IPPROTO_IGMP       2         //!< Internet Group Management Protocol.
#define TELIUM_IPPROTO_IPIP       4         //!< IPIP tunnels (older KA9Q tunnels use 94).
#define TELIUM_IPPROTO_TCP        6         //!< Transmission Control Protocol.
#define TELIUM_IPPROTO_EGP        8         //!< Exterior Gateway Protocol.
#define TELIUM_IPPROTO_PUP        12        //!< PUP protocol.
#define TELIUM_IPPROTO_UDP        17        //!< User Datagram Protocol.
#define TELIUM_IPPROTO_IDP        22        //!< XNS IDP protocol.
#define TELIUM_IPPROTO_TP         29        //!< SO Transport Protocol Class 4.
#define TELIUM_IPPROTO_IPV6       41        //!< IPv6 header.
#define TELIUM_IPPROTO_ROUTING    43        //!< IPv6 routing header.
#define TELIUM_IPPROTO_FRAGMENT   44        //!< IPv6 fragmentation header.
#define TELIUM_IPPROTO_RSVP       46        //!< Reservation Protocol.
#define TELIUM_IPPROTO_GRE        47        //!< General Routing Encapsulation.
#define TELIUM_IPPROTO_ESP        50        //!< Encapsulating security payload.
#define TELIUM_IPPROTO_AH         51        //!< Authentication header.
#define TELIUM_IPPROTO_ICMPV6     58        //!< ICMPv6.
#define TELIUM_IPPROTO_NONE       59        //!< IPv6 no next header.
#define TELIUM_IPPROTO_DSTOPTS    60        //!< IPv6 destination options.
#define TELIUM_IPPROTO_ENCAP      98        //!< Encapsulation Header.
#define TELIUM_IPPROTO_PIM        103       //!< Protocol Independent Multicast.
#define TELIUM_IPPROTO_IPCOMP     108       //!< Compression Header Protocol.
#define TELIUM_IPPROTO_RAW        255       //!< Raw IP packets.
#define TELIUM_IPPROTO_MAX        256       //!< Maximum value for IPPROTO options.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Recv/Send flags.
//! \defgroup  IP_SEND_RECV_FLAGS Send and receive flags
//! \ingroup IP_BSD
//! \brief Send and receive flags.
//! @{
#define TELIUM_MSG_DONTWAIT       0x0001    //!< Non-blocking operation request.
#define TELIUM_MSG_WAITALL        0x0002    //!< Wait till operation completed.
#define TELIUM_MSG_OOB            0x0004    //!< Receive out-of-band data.
#define TELIUM_MSG_PEEK           0x0008    //!< Peek at data, don't remove from buffer.
#define TELIUM_MSG_DONTROUTE      0x0010    //!< Don't use gateway.
#define TELIUM_MSG_EOR            0x0020    //!< End of record.
#define TELIUM_MSG_TRUNC          0x0040    //!< Packet data was discarded (buffer too small).
#define TELIUM_MSG_CTRUNC         0x0080    //!< Control data was discarded (buffer too small).
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}



// Socket options
//! \defgroup  SOCKET_OPTIONS Socket options
//! \ingroup IP_BSD
//! \brief Socket options (used by \ref Telium_Socket_setsockopt()/ \ref Telium_Socket_getsockopt()).
//! @{
#define TELIUM_SO_REUSEADDR       0x0004    //!< Reuse address.
#define TELIUM_SO_KEEPALIVE       0x0008    //!< Keep alive.
#define TELIUM_SO_BROADCAST       0x0020    //!< Broadcast.
#define TELIUM_SO_LINGER          0x0080    //!< Linger-on-close timeout.
#define TELIUM_SO_SNDTIMEO        0x1005    //!< Send timeout.
#define TELIUM_SO_RCVTIMEO        0x1006    //!< Receive timeout.
#define TELIUM_SO_NREAD           0x1f02    //!< Number of bytes in the receive buffer (ReadOnly option).


// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \defgroup  TCP_OPTIONS TCP options
//! \ingroup IP_BSD
//! \brief TCP options (used by \ref Telium_Socket_setsockopt()/ \ref Telium_Socket_getsockopt()).
//! @{
#define TELIUM_TCP_NODELAY      0x0001  //!< Don't delay send to coalesce packets.
#define TELIUM_TCP_MAXSEG       0x0002  //!< Set maximum segment size.
#define TELIUM_TCP_NOTIMEWAIT   0x0006  //!< Disable time-wait state.
#define TELIUM_TCP_CONNRST      0x0007  //!< Send a RST before active connection.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

// Shutdown "how" parameter.
//! \defgroup  IP_SHUTDOWN_METHOD Shutdown method
//! \ingroup IP_BSD
//! \brief Shutdown "how" parameter.
//! @{
#define TELIUM_SHUT_RD			       0         //!< Shutdown read part of full duplex socket.
#define TELIUM_SHUT_WR			       1         //!< Shutdown write part of full duplex socket.
#define TELIUM_SHUT_RDWR		       2         //!< Shutdown read and write part of full duplex socket.
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! \addtogroup  IP_CONFIGURATION 
//! @{

//! \brief This function returns the current value of the internal error code (ERRNO).
//! \return
//! The internal error code value (ERRNO).
int Telium_GetErrno( void);

//! \brief This function sets the value of the internal error code (ERRNO).
//! \param err : Error code.
//! \return None.
void Telium_SetErrno( int err);

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
unsigned long  Telium_inet_addr( const char *addr);

//! \brief This function converts an ASCII TCP/IP address to its 4 bytes format (struct in_addr).
//! \param name : TCP/IP address - ASCII format ('www.xxx.yyy.zzz').
//! \param addr : Converted address - 4 bytes format.
//! \return 
//! - 1 if the address has been rightly converted.
//! - 0 otherwise.
int Telium_inet_aton(const char *name, struct Telium_in_addr *addr );

//! \brief This function is the inverse of the function \ref Telium_inet_addr(). 
//! It converts a 4 bytes address in its ASCII format.
//! \param addr : TCP/IP address - 4 bytes format.
//! \return
//! - Converted address - ASCII format ('www.xxx.yyy.zzz').
//! \note 
//! The returned character string is NULL terminated. It is allocated by the function \ref Telium_inet_ntoa()
//! and belongs to this one. It must copied by the calling function and must not be freed.
char *Telium_inet_ntoa( struct Telium_in_addr addr);

//! \brief Converts the unsigned short value from network byte order to host byte order.
//! \param usNetworkShort : network byte order value to convert.
//! \return The input value converted in host byte order.
unsigned short Telium_ntohs( unsigned short usNetworkShort );

//! \brief Converts the unsigned short value from host byte order to network byte order.
//! \param usHostShort : host byte order value to convert.
//! \return The input value converted in network byte order.
unsigned short Telium_htons( unsigned short usHostShort );

//! \brief Converts the unsigned int value from network byte order to host byte order.
//! \param nNetworkInt : network byte order value to convert.
//! \return The input value converted in host byte order.
unsigned int Telium_ntohl( unsigned int nNetworkInt );

//! \brief Converts the unsigned int value from host byte order to network byte order.
//! \param nHostInt : host byte order value to convert.
//! \return The input value converted in network byte order.
unsigned int Telium_htonl( unsigned int nHostInt );

//! @}

//! \ingroup  IP_BSD 
//! @{
// Host information.
//! \brief Host information structure.
struct Telium_hostent 
{
    char   *h_name;         //!< Host name.
    char  **h_aliases;      //!< List of aliases.
    int     h_addrtype;     //!< Type of address (always TELIUM_AF_INET).
    int     h_length;       //!< Length of address.
    char  **h_addr_list;    //!< List of addresses.
};

#define h_addr h_addr_list[0]

// Error codes.
#define TELIUM_HOST_NOT_FOUND  1
#define TELIUM_TRY_AGAIN       2
#define TELIUM_NO_RECOVERY     3
#define TELIUM_NO_DATA_ERR     4
#define TELIUM_NO_ADDRESS      4


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
struct Telium_hostent * Telium_gethostbyname_r( const char *name, struct Telium_hostent *result, void *buf, int buflen, int *err );

//! \brief The gethostbyaddr_r() function returns a structure of type hostent for the given host address 'addr' 
//! of length 'len' and address type 'type'. The valid address type \ref TELIUM_AF_INET. 
//! The host address argument is a pointer to a struct of a type depending on the address type, 
//! for example a struct in_addr * (probably obtained via a call to Telium_inet_addr()) for address type \ref TELIUM_AF_INET. 
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
struct Telium_hostent * Telium_gethostbyaddr_r( const char *addr, int len, int type, struct Telium_hostent *result, void *buf, int buflen, int *err );

//! @}

#endif // __IP_TPLUS_H__
