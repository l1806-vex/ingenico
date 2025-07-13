//! \file        SSL_.h
//! \brief This module contains all the SSL definitions.
//!
/*! @addtogroup KSFAM_SSL
	@{
	@par Introduction
	The package SSL is a static library which implements an API to use the dynamic SSL library. 
	It must be linked with the application. It is composed of two API header files ( <SSL_.h>,
	<X509_.h>) and a library "SSL _.lib" compiled with the three compilers (GCC, RVD and SDT)
	supported by the Telium SDK.
	The package provides all the services to monitor the SSL client facility :
	- SSL connection (simple or double authentication).
	- SSL configuration profile monitoring
	- X509 certificate management
	- //...

	<TABLE border="3" cellspacing="0" bordercolor="black">
	<TR><TD></TD></TR>
	<TR><TD><b>Developers shall read the <a href="ICO-PE-046-GU-EN_PackSSL_SecurityGuidance_UserGuide.html">[SSL Security Guidance]</a> which describes
	best practises for implementing SSL/TLS enabled applications, according to the requirements of
	the POS Terminal Security Program (PTS) and of the PCI PTS v3 "Open Protocols" module.</b></TD></TR>
	<TR><TD></TD></TR>
	</TABLE>

	Be careful, do not forget to load the dynamic SSL library (3620xxxx.LDF/SGN) in your terminal.
	Each function makes a reset with EXIT_DLL_SSL_NOT_INITIALIZED value if the dynamic SSL library is not loaded in the terminal. 

	@par Certificates
  *
  * A certificate is a digitally signed statement from an entity certifying that information about an
    other entity are true. A certificate is an information set, signed by an issuer entity.
  *
  * The signature algorithms are based on asymmetric key cryptography (generally RSA). The
    issuer entity signs by enciphering the information set with its private key (known only by itself).
    The other entities can verified the signature by deciphering the information set with the public key of the issuer.
  *
  * SSL uses the certificate principle to operate the authentication of the entities (client and server).
  *
  * These certificates are coded according to the X509 standard. This standard defines what
    information can contain a certificate, and describes the data format how to write it down.
  *
  * All X.509 certificates contain the following data, in addition to the signature:
  *
  *   - @b Version: This identifies which version of the X509 standard is used to code the certificate.
    It affects mainly what information can be stored in the certificate.
 
  *  -   @b Serial @b Number: This identifies the certificate. It is given by the issuer entity. It serves to distinguish the
    certificate from the other ones issued by the same issuer entity. This information is used
    for example when the certificate is revoked ; in this case, its serial number is placed in a Certificate Revocation List (CRL).
  *
  *   - @b Signature @b Algorithm @b Identifier: This identifies the algorithm used by the issuer entity to sign the certificate.
  *
  *   - @b Issuer @b Name:  The name of the issuer entity. Normally, it corresponds to a Certification Authority (CA).
    Using this certificate implies trusting the entity that issued the certificate.
  *
  *   - @b Validity @b Period: A certificate is valid only for a limited period of time. This period is described by a start
    date and an end date. The validity period is the expected period that the entities can rely
    on the information of the certificate. This period is chosen by the issuer. It depends on the
    strength of the signature algorithm, or mainly the willing of issuer to sell its certificates.
  *
  *   - @b Subject @b Name: The name of the entity whose the certificate identifies.
  *
  *   - @b Subject @b Public @b Key @b Information:  This is the public key of the subject entity. This information identifies also the
    cryptographic algorithm associated to the key.
  *
  * The names of the issuer entity and of the subject entity are coded according to the X500
    standard. They are intended to be unique across the Internet. A X500 name is composed of
    fields, for example : "CN=EFT30, OU=DSEC, O=Ingenico France, C=FR" refer respectively to
    the subject's Common Name, Organisational Unit, Company and Country).
  *
  * There are two ways to generate a certificate:
  *
  * - 1. You can create one yourself using special tools (for example those provided with OpenSSL)
  * - 2. You can ask a Certification Authority (CA) to get one directly or generate a request
   (named CSR for Certification Signature Request) and ask the CA for its signature.
  *
    @par SSL
  *
  * @b SSL stands for @b Secure @b Socket @b Layer. The protocol's name is now officially TLS but SSL is still the better known name. 
        *
    SSL was designed to permit applications and servers to exchange sensitive information and
    prevent programs that could access the network traffic from reading the sensitive data.
  *
  * SSL uses the notion of client and server. Its operational scheme does not require the client and
    the server to share a secrete key. SSL uses asymmetric encryption algorithms to secure the
    transaction. These algorithms uses pair of keys (public and private). The public key is freely
    available and known for anybody. The private key is only known by the entity (the client or the server). 
    These keys have to main properties :
  *
  * - 1. Data encrypted by the public key can only decrypted by the private key. As the public is
    freely known, anybody can transfer secured data to the entity owner of the private key.
  *
  * - 2. Data encrypted by the private key can be only decrypted by using the public key. This
   property is used for authentication. Only the entity owner of the private key is able to
   generate a message which can be decrypted with the public key.
  *
  * In the SSL scheme, the client contacts the server and sends the first SSL message. This
    message starts the SSL negotiation : an encryption algorithm is chosen and a secured key is
    generated to the current connection. After the success of this negotiation, the two entities can
    exchange secured data at will.
  *
  * The @b SSL @b negotiation (named SSL Handshake) involves an authentication process. At least , the
    server is authenticated by the client (case of simple authentication). The server can also request
    the client to be authenticated (case of mutual authentication). The SSL authentication scheme is
    based on the use of certificates.
  *
  * Below is the description of the message sequence to operate the SSL handshake. 
        *
  * @image html SSL.jpg "SSL Message Sequence Diagram"
        *
  * @image html SSL1.jpg " "
        *
	@image html SSL2.jpg " "
	*
	@par Profiles Management
	*
	The SSL library defines the notion of profile. A profile is a data set which contains all the
    configuration useful to perform a connection SSL. The library allows to have several profiles. All
    the profiles are stored in a file in flash.

  * @image html SSL3.jpg "Profiles Management Illustration"
  *
  * A profile is identified by a name. This name must be unique for all the profiles in the terminal. A
    profile contains the list of the enciphering algorithms supported, and the export mode mask. It
    contains also a list of CA certificates file names. And optionally, a key file name and a client
    certificate file name (case of mutual authentication). It contains also extra information about the last connection (result, IP address...).
  
  * @par Capabilities
    *
	The SSL library supports the following cipher suites :
	*
		<TABLE border="3" cellspacing="0" bordercolor="black">
			<TR align="center"><TD><b>Cipher Suite</b></TD><TD><b>Key Exchange</b></TD><TD><b>Cipher</b></TD><TD><b>Hash</b></TD></TR>
			<TR><TD>NULL_WITH_NULL_NULL</TD><TD>NULL</TD><TD>NULL</TD><TD>NULL</TD></TR>
			<TR><TD>RSA_WITH_NULL_MD5</TD><TD>RSA</TD><TD>NULL</TD><TD>MD5</TD></TR>
			<TR><TD>RSA_WITH_NULL_SHA</TD><TD>RSA</TD><TD>NULL</TD><TD>SHA</TD></TR>
			<TR><TD>RSA_EXPORT_WITH_RC4_40_MD5</TD><TD>RSA_EXPORT</TD><TD>RC4_40</TD><TD>MD5</TD></TR>
			<TR><TD>RSA_WITH_RC4_128_MD5</TD><TD>RSA</TD><TD>RC4_128</TD><TD>MD5</TD></TR>
			<TR><TD>RSA_WITH_RC4_128_SHA</TD><TD>RSA</TD><TD>RC4_128</TD><TD>SHA</TD></TR>
			<TR><TD>RSA_EXPORT_WITH_RC2_CBC_40_MD5    </TD><TD>RSA_EXPORT</TD><TD>RC2_CBC_40</TD><TD>MD5</TD></TR>
			<TR><TD>RSA_WITH_IDEA_CBC_SHA             </TD><TD>RSA</TD><TD>IDEA_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>RSA_EXPORT_WITH_DES40_CBC_SHA     </TD><TD>RSA_EXPORT</TD><TD>DES40_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>RSA_WITH_DES_CBC_SHA              </TD><TD>RSA</TD><TD>DES_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>RSA_WITH_3DES_EDE_CBC_SHA         </TD><TD>RSA</TD><TD>3DES_EDE_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DH_DSS_EXPORT_WITH_DES40_CBC_SHA  </TD><TD>DH_DSS_EXPORT</TD><TD>DES40_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DH_DSS_WITH_DES_CBC_SHA           </TD><TD>DH_DSS</TD><TD>DES_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DH_DSS_WITH_3DES_EDE_CBC_SHA      </TD><TD>DH_DSS</TD><TD>3DES_EDE_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DH_RSA_EXPORT_WITH_DES40_CBC_SHA  </TD><TD>DH_RSA_EXPORT</TD><TD>DES40_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DHE_DSS_EXPORT_WITH_DES40_CBC_SHA </TD><TD>DHE_DSS_EXPORT</TD><TD>DES40_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DHE_DSS_WITH_DES_CBC_SHA          </TD><TD>DHE_DSS</TD><TD>DES_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DHE_DSS_WITH_3DES_EDE_CBC_SHA     </TD><TD>DHE_DSS</TD><TD>3DES_EDE_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DHE_RSA_EXPORT_WITH_DES40_CBC_SHA </TD><TD>DHE_RSA_EXPORT</TD><TD>DES40_CBC   </TD><TD>SHA</TD></TR>
			<TR><TD>DHE_RSA_WITH_DES_CBC_SHA          </TD><TD>DHE_RSA</TD><TD>DES_CBC     </TD><TD>SHA</TD></TR>
			<TR><TD>DHE_RSA_WITH_3DES_EDE_CBC_SHA     </TD><TD>DHE_RSA</TD><TD>3DES_EDE_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DH_anon_EXPORT_WITH_RC4_40_MD5    </TD><TD>DH_anon_EXPORT </TD><TD>RC4_40</TD><TD>MD5</TD></TR>
			<TR><TD>DH_anon_WITH_RC4_128_MD5          </TD><TD>DH_anon</TD><TD>RC4_128</TD><TD>MD5</TD></TR>
			<TR><TD>DH_anon_EXPORT_WITH_DES40_CBC_SHA </TD><TD>DH_anon</TD><TD>DES40_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DH_anon_WITH_DES_CBC_SHA          </TD><TD>DH_anon</TD><TD>DES_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DH_anon_WITH_3DES_EDE_CBC_SHA     </TD><TD>DH_anon</TD><TD>3DES_EDE_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>RSA_WITH_AES_128_CBC_SHA      </TD><TD>RSA</TD><TD>AES_128_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DH_DSS_WITH_AES_128_CBC_SHA   </TD><TD>DH_DSS</TD><TD>AES_128_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DH_RSA_WITH_AES_128_CBC_SHA   </TD><TD>DH_RSA</TD><TD>AES_128_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DHE_DSS_WITH_AES_128_CBC_SHA  </TD><TD>DHE_DSS</TD><TD>AES_128_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DHE_RSA_WITH_AES_128_CBC_SHA  </TD><TD>DHE_RSA</TD><TD>AES_128_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DH_anon_WITH_AES_128_CBC_SHA  </TD><TD>DH_anon</TD><TD>AES_128_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>RSA_WITH_AES_256_CBC_SHA      </TD><TD>RSA</TD><TD>AES_256_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DH_DSS_WITH_AES_256_CBC_SHA   </TD><TD>DH_DSS</TD><TD>AES_256_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DH_RSA_WITH_AES_256_CBC_SHA   </TD><TD>DH_RSA</TD><TD>AES_256_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DHE_DSS_WITH_AES_256_CBC_SHA  </TD><TD>DHE_DSS</TD><TD>AES_256_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DHE_RSA_WITH_AES_256_CBC_SHA  </TD><TD>DHE_RSA</TD><TD>AES_256_CBC</TD><TD>SHA</TD></TR>
			<TR><TD>DH_anon_WITH_AES_256_CBC_SHA  </TD><TD>DH_anon</TD><TD>AES_256_CBC</TD><TD>SHA</TD></TR>
		</TABLE>
		<BR><BR>

		The maximum size of RSA keys for a certificate verification is 4096 bits (public key).
		The maximum size for the RSA private keys is 2048 bits.

		The SHA-2 hash algorithm is supported but only for certificate verification. The SSL library does not
		support this algorithm in cipher suites.
		
		This product includes cryptographic software written by Eric Young (eay (at) cryptsoft.com)
  *
  *
  **/

#ifndef SSL_INC
#define SSL_INC

#ifndef __FRAMEWORK_TELIUM_PLUS__
#include "SSL_deprecated.h"
#endif
#include "ssl_profile.h"

/*
======================================================================
                                        List of Defines		 
======================================================================
*/

// SSL function error code

//! \defgroup SSL_ERROR_CODES Error codes
//! \brief Error codes returned by SSL API functions.
//! @{
#define SSL_EOK                                 0               /*!< No error*/ 
#define SSL_EAGAIN                              -6              /*!< Resource temporarily unavailable*/
#define SSL_EINVAL                              -26             /*!< Invalid Argument*/
#define SSL_ENOBUFS                             -39             /*!< Out of Resources*/
#define SSL_ENOENT                              -41             /*!< No such file or directory*/
#define SSL_ENOMEM                              -44 			/*!< Cannot allocate memory*/
#define SSL_ENOTCONN                            -50             /*!< socket not connected*/
#define SSL_ESSL                                -500            /*!< SSL error*/
#define SSL_EBADFORMAT                          -501            /*!< bad certificate file or ca file format*/
#define SSL_SYSCALL_EOF                         -505            /*!< connection closed*/
//! @}

// RSA function error code
#define SSL_RSA_EOK                             0               /*!< No error*/ 
#define SSL_RSA_ENOK                            -1              /*!< RSA error*/ 
#define SSL_RSA_ENOKEY                          -2              /*!< Internal Rsa key not yet generated*/ 
#define SSL_RSA_EEXIST                          -3              /*!< File exist*/ 

// Profile function error code
#define SSL_PROFILE_EOK                         0               /*!< No error*/ 
#define SSL_PROFILE_EEXIST                      -1              /*!< Profile already exist*/ 
#define SSL_PROFILE_ENEXIST                     -2              /*!< Profile does not exist*/ 
#define SSL_PROFILE_ETOOMANY                    -3              /*!< Too many profile are loaded*/ 
#define SSL_PROFILE_ENOMEM                      -4              /*!< Allocation error*/ 
#define SSL_PROFILE_ELOADED                     -5              /*!< Profile already loaded*/ 
#define SSL_PROFILE_ENLOADED                    -6              /*!< Profile not loaded*/ 
#define SSL_PROFILE_ECAEXIST                    -7              /*!< ca already exist*/ 
#define SSL_PROFILE_ECANEXIST                   -8              /*!< ca does not exist in the profile*/ 
#define SSL_PROFILE_ECATOOMANY                  -9              /*!< Too many ca in the profile*/ 
#define SSL_PROFILE_EPARAM                      -10             /*!< A parameter is wrong*/ 
#define SSL_PROFILE_ENOCERT                     -11             /*!< There is no certificate*/ 

// SSL version

//! \defgroup SSL_VERSION SSL versions
//! \brief SSL protocol version.
//! @{
#define SSLv2                                   1               /*!< SSL version 2*/
#define SSLv3                                   2               /*!< SSL version 3*/ 
#define TLSv1                                   3               /*!< TLS version 1.0*/
#define SSLv23                                  4               /*!< SSL version 2 or 3*/
#define TLSv1_1                                 5               /*!< TLS version 1.1*/
#define TLSv1_2                                 6               /*!< TLS version 1.2*/
//! @}

// Cipher information
//! \defgroup SSL_CIPHER Cipher information
//! \brief SSL cipher algorithms.
//! \deprecated Some define are deprecated. Please do the necessary to clean your code
//! @{

#define SSL_kRSA                                0x00000001L     /*!< RSA key exchange*/
#define SSL_kEDH                                0x00000010L     /*!< tmp DH key no DH cert*/ 

#define SSL_aRSA                                0x00000020L     /*!< Authenticate with RSA*/
#define SSL_aDSS                                0x00000040L     /*!< Authenticate with DSS*/

#define SSL_DES									0x00000400L     /*!< DES*/
#define SSL_3DES								0x00000800L     /*!< 3DES*/
#define SSL_RC4									0x00001000L     /*!< RC4*/
#define SSL_RC2									0x00002000L     /*!< RC2*/
#define SSL_AES									0x00200000L     /*!< AES*/

#define SSL_MD5									0x00020000L     /*!< MD5*/
#define SSL_SHA1								0x00040000L     /*!< SHA1*/
#define SSL_SHA256								0x00400000L     /*!< SHA256*/
#define SSL_SHA384								0x00800000L     /*!< SHA384*/

#define SSL_RSA                                 (SSL_kRSA|SSL_aRSA)                     /*!< RSA*/
#define SSL_DSS                                 (SSL_aDSS)        						/*!< Authenticate with DSS*/

//! @}

// export information
#define SSL_NOT_EXP                             0x00000001L     /*!< No export*/ 
#define SSL_EXPORT                              0x00000002L     /*!< Export*/ 

// cipher strength information
#define SSL_STRONG_NONE                         0x00000004L     /*!< None*/ 
#define SSL_EXP40                               0x00000008L     /*!< Micro strength*/ 
#define SSL_MICRO                               (SSL_EXP40)     /*!< Micro strength*/ 
#define SSL_EXP56                               0x00000010L     /*!< Mini strength*/ 
#define SSL_MINI                                (SSL_EXP56)     /*!< Mini strength*/ 
#define SSL_LOW                                 0x00000020L     /*!< Low strength*/ 
#define SSL_MEDIUM                              0x00000040L     /*!< Medium strength*/ 
#define SSL_HIGH                                0x00000080L     /*!< High strength*/ 

// ssl server
#define SSL_SERVER_NO_PEER_VERIFICATION         0               /*!< Configure SSL server without peer verification*/ 
#define SSL_SERVER_VERIFY_PEER                  1		/*!< Configure SSL server with peer verification*/ 
#define SSL_SERVER_NO_CACHE                     0		/*!< Configure SSL server without session cache*/ 
#define SSL_SERVER_USE_CACHE                    1		/*!< Configure SSL server with session cache*/ 

// SSL connection state returned by SSL_GetConnectionState
#define SSL_STATE_DISCONNECT		0x00		/*!< Disconnected*/ 
#define SSL_STATE_TCP_CONNECTION	0x01		/*!< TCP connection in progress*/ 
#define SSL_STATE_TCP_CONNECT		0x02		/*!< TCP connection is done*/ 
#define SSL_STATE_SSL_CONNECTION	0x03		/*!< SSL connection in progress*/ 
#define SSL_STATE_SSL_CONNECT		0x04		/*!< SSL connection is done*/ 
#define SSL_STATE_CONNECT			0x05		/*!< Connection is done */ 

// Error code return by SSL_ProfileGetLastError function
// SSL connection error code
#define	SSL_PROFILE_OK                                                  0               /*!< SSL connection OK */ 
#define SSL_PROFILE_TCP_CONNECT_FAILED                                  -1		/*!< TCP connection failed */ 
#define	SSL_PROFILE_TCP_CONNECT_TIMEOUT                                 -2		/*!< TCP connection timeout */ 
#define	SSL_PROFILE_TCP_ADDR_NOT_AVAILABLE                              -3		/*!< TCP address is not reachable */ 
#define	SSL_PROFILE_SSL_HANDSHAKE_FAILURE                               -4		/*!< SSL handshake failure */ 
#define	SSL_PROFILE_DNS_FAILURE                                         -5		/*!< DNS tranlation failure */ 
#define	SSL_PROFILE_DOMAIN_NAME_FAILURE                                 -6		/*!< Domain name check failure */ 

// Certificate verification error code
#define	SSL_PROFILE_UNABLE_TO_GET_ISSUER_CERT                           2               /*!< Unable to get issuer */ 
#define	SSL_PROFILE_UNABLE_TO_GET_CRL                                   3               /*!< Unable to get certificate revocation list */ 
#define	SSL_PROFILE_UNABLE_TO_DECRYPT_CERT_SIGNATURE                    4               /*!< Unable to decrypt certificate signature */ 
#define	SSL_PROFILE_UNABLE_TO_DECRYPT_CRL_SIGNATURE                     5               /*!< Unable to decrypt certificate revocation list signature */ 
#define	SSL_PROFILE_UNABLE_TO_DECODE_ISSUER_PUBLIC_KEY                  6               /*!< Unable to decode issuer public key */ 
#define	SSL_PROFILE_CERT_SIGNATURE_FAILURE                              7               /*!< Certificate signature verification failure */ 
#define	SSL_PROFILE_CRL_SIGNATURE_FAILURE                               8               /*!< Certificate revocation list signature verification failure */ 
#define	SSL_PROFILE_CERT_NOT_YET_VALID                                  9               /*!< Certificate is not yet valid */ 
#define	SSL_PROFILE_CERT_HAS_EXPIRED                                    10		/*!< Certificate has expired */ 
#define	SSL_PROFILE_CRL_NOT_YET_VALID                                   11		/*!< Certificate revocation list is not yet valid*/ 
#define	SSL_PROFILE_CRL_HAS_EXPIRED                                     12		/*!< Certificate revocation list has expired */ 
#define	SSL_PROFILE_ERROR_IN_CERT_NOT_BEFORE_FIELD                      13		/*!< Error in a validity date of certificate */ 
#define	SSL_PROFILE_ERROR_IN_CERT_NOT_AFTER_FIELD                       14		/*!< Error in a validity date of certificate*/ 
#define	SSL_PROFILE_ERROR_IN_CRL_LAST_UPDATE_FIELD                      15		/*!< Error in a update date of certificate revocation list */ 
#define	SSL_PROFILE_ERROR_IN_CRL_NEXT_UPDATE_FIELD                      16		/*!< Error in a update date of certificate revocation list */ 
#define	SSL_PROFILE_OUT_OF_MEM                                          17		/*!< Out of memory */ 
#define	SSL_PROFILE_DEPTH_ZERO_SELF_SIGNED_CERT                         18		/*!< Certificate is self signed */ 		
#define	SSL_PROFILE_SELF_SIGNED_CERT_IN_CHAIN                           19		/*!< Certificate is self signed */ 
#define	SSL_PROFILE_UNABLE_TO_GET_ISSUER_CERT_LOCALLY                   20		/*!< Unable to get issuer */ 
#define	SSL_PROFILE_UNABLE_TO_VERIFY_LEAF_SIGNATURE                     21		/*!< Unable to verify leaf signature */ 
#define	SSL_PROFILE_CERT_CHAIN_TOO_LONG                                 22		/*!< Certificate chain is too long */ 
#define	SSL_PROFILE_CERT_REVOKED                                        23		/*!< Certificate is revoked */ 
#define	SSL_PROFILE_INVALID_CA                                          24		/*!< Invalid CA */ 
#define	SSL_PROFILE_PATH_LENGTH_EXCEEDED                                25		/*!< Path length too long */ 
#define	SSL_PROFILE_INVALID_PURPOSE                                     26		/*!< Invalid purpose of certificate */ 
#define	SSL_PROFILE_CERT_UNTRUSTED                                      27		/*!< Untrusted certificate */ 
#define	SSL_PROFILE_CERT_REJECTED                                       28		/*!< Rejected certificate */ 
#define	SSL_PROFILE_SUBJECT_ISSUER_MISMATCH                             29		/*!< Certificate subject mismatch */ 
#define	SSL_PROFILE_AKID_SKID_MISMATCH                                  30		/*!< AKID SKID mismatch */ 
#define	SSL_PROFILE_AKID_ISSUER_SERIAL_MISMATCH                         31		/*!< AKID issuer serial mismatch*/ 
#define	SSL_PROFILE_KEYUSAGE_NO_CERTSIGN                                32		/*!< Invalid purpose of certificate */ 
#define	SSL_PROFILE_UNABLE_TO_GET_CRL_ISSUER		                    33		/*!< Unable to get certificate revocation list issuer */ 
#define	SSL_PROFILE_UNHANDLED_CRITICAL_EXTENSION		                34		/*!< Unhandled critical extension */ 
#define	SSL_PROFILE_KEYUSAGE_NO_CRL_SIGN			                    35		/*!< Issuer can't sign a certificate revocation list */ 
#define	SSL_PROFILE_UNHANDLED_CRITICAL_CRL_EXTENSION	                36		/*!< Unhandled critical extension in certificate revocation list */ 

/**
\cond
avoid dox documentation */
// SSL Handshake error code
#define SSL_PROFILE_E_APP_DATA_IN_HANDSHAKE                                     100		 
#define SSL_PROFILE_E_BAD_ALERT_RECORD                                          101		 
#define SSL_PROFILE_E_BAD_AUTHENTICATION_TYPE                                   102		 
#define SSL_PROFILE_E_BAD_CHANGE_CIPHER_SPEC                                    103		 
#define SSL_PROFILE_E_BAD_CHECKSUM                                              104		 
#define SSL_PROFILE_E_BAD_HELLO_REQUEST                                         105		 
#define SSL_PROFILE_E_BAD_DATA_RETURNED_BY_CALLBACK                             106		 
#define SSL_PROFILE_E_BAD_DECOMPRESSION                                         107		 
#define SSL_PROFILE_E_BAD_DH_G_LENGTH                                           108		 
#define SSL_PROFILE_E_BAD_DH_PUB_KEY_LENGTH                                     109		 
#define SSL_PROFILE_E_BAD_DH_P_LENGTH                                           110		 
#define SSL_PROFILE_E_BAD_DIGEST_LENGTH                                         111		 
#define SSL_PROFILE_E_BAD_DSA_SIGNATURE                                         112		 
#define SSL_PROFILE_E_BAD_MAC_DECODE                                            113		 
#define SSL_PROFILE_E_BAD_MESSAGE_TYPE                                          114		 
#define SSL_PROFILE_E_BAD_PACKET_LENGTH                                         115		 
#define SSL_PROFILE_E_BAD_PROTOCOL_VERSION_NUMBER                               116		 
#define SSL_PROFILE_E_BAD_RESPONSE_ARGUMENT                                     117		 
#define SSL_PROFILE_E_BAD_RSA_DECRYPT                                           118		 
#define SSL_PROFILE_E_BAD_RSA_ENCRYPT                                           119		 
#define SSL_PROFILE_E_BAD_RSA_E_LENGTH                                          120		 
#define SSL_PROFILE_E_BAD_RSA_MODULUS_LENGTH                                    121		 
#define SSL_PROFILE_E_BAD_RSA_SIGNATURE                                         122		 
#define SSL_PROFILE_E_BAD_SIGNATURE                                             123		 
#define SSL_PROFILE_E_BAD_SSL_FILETYPE                                          124		 
#define SSL_PROFILE_E_BAD_SSL_SESSION_ID_LENGTH                                 125		 
#define SSL_PROFILE_E_BAD_STATE                                                 126		 
#define SSL_PROFILE_E_BAD_WRITE_RETRY                                           127		 
#define SSL_PROFILE_E_BIO_NOT_SET                                               128		 
#define SSL_PROFILE_E_BLOCK_CIPHER_PAD_IS_WRONG                                 129		 
#define SSL_PROFILE_E_BN_LIB                                                    130		 
#define SSL_PROFILE_E_CA_DN_LENGTH_MISMATCH                                     131		 
#define SSL_PROFILE_E_CA_DN_TOO_LONG                                            132		 
#define SSL_PROFILE_E_CCS_RECEIVED_EARLY                                        133		 
#define SSL_PROFILE_E_CERTIFICATE_VERIFY_FAILED                                 134		 
#define SSL_PROFILE_E_CERT_LENGTH_MISMATCH                                      135		 
#define SSL_PROFILE_E_CHALLENGE_IS_DIFFERENT                                    136		 
#define SSL_PROFILE_E_CIPHER_CODE_WRONG_LENGTH                                  137		 
#define SSL_PROFILE_E_CIPHER_OR_HASH_UNAVAILABLE                                138		 
#define SSL_PROFILE_E_CIPHER_TABLE_SRC_ERROR                                    139		 
#define SSL_PROFILE_E_COMPRESSED_LENGTH_TOO_LONG                                140		 
#define SSL_PROFILE_E_COMPRESSION_FAILURE                                       141		 
#define SSL_PROFILE_E_COMPRESSION_LIBRARY_ERROR                                 142		 
#define SSL_PROFILE_E_CONNECTION_ID_IS_DIFFERENT                                143		 
#define SSL_PROFILE_E_CONNECTION_TYPE_NOT_SET                                   144		 
#define SSL_PROFILE_E_DATA_BETWEEN_CCS_AND_FINISHED                             145		 
#define SSL_PROFILE_E_DATA_LENGTH_TOO_LONG                                      146		 
#define SSL_PROFILE_E_DECRYPTION_FAILED                                         147		 
#define SSL_PROFILE_E_DH_PUBLIC_VALUE_LENGTH_IS_WRONG                           148		 
#define SSL_PROFILE_E_DIGEST_CHECK_FAILED                                       149		 
#define SSL_PROFILE_E_ENCRYPTED_LENGTH_TOO_LONG                                 150		 
#define SSL_PROFILE_E_ERROR_IN_RECEIVED_CIPHER_LIST                             151		 
#define SSL_PROFILE_E_EXCESSIVE_MESSAGE_SIZE                                    152		 
#define SSL_PROFILE_E_EXTRA_DATA_IN_MESSAGE                                     153		 
#define SSL_PROFILE_E_GOT_A_FIN_BEFORE_A_CCS                                    154		 
#define SSL_PROFILE_E_HTTPS_PROXY_REQUEST                                       155		 
#define SSL_PROFILE_E_HTTP_REQUEST                                              156		 
#define SSL_PROFILE_E_INTERNAL_ERROR                                            157		 
#define SSL_PROFILE_E_INVALID_CHALLENGE_LENGTH                                  158		 
#define SSL_PROFILE_E_LENGTH_MISMATCH                                           159		 
#define SSL_PROFILE_E_LENGTH_TOO_SHORT                                          160		 
#define SSL_PROFILE_E_LIBRARY_HAS_NO_CIPHERS                                    161		 
#define SSL_PROFILE_E_MISSING_DH_DSA_CERT                                       162		 
#define SSL_PROFILE_E_MISSING_DH_KEY                                            163		 
#define SSL_PROFILE_E_MISSING_DH_RSA_CERT                                       164		 
#define SSL_PROFILE_E_MISSING_DSA_SIGNING_CERT                                  165		 
#define SSL_PROFILE_E_MISSING_EXPORT_TMP_DH_KEY                                 166		 
#define SSL_PROFILE_E_MISSING_EXPORT_TMP_RSA_KEY                                167		 
#define SSL_PROFILE_E_MISSING_RSA_CERTIFICATE                                   168		 
#define SSL_PROFILE_E_MISSING_RSA_ENCRYPTING_CERT                               169		 
#define SSL_PROFILE_E_MISSING_RSA_SIGNING_CERT                                  170		 
#define SSL_PROFILE_E_MISSING_TMP_DH_KEY                                        171		 
#define SSL_PROFILE_E_MISSING_TMP_RSA_KEY                                       172		 
#define SSL_PROFILE_E_MISSING_TMP_RSA_PKEY                                      173		 
#define SSL_PROFILE_E_MISSING_VERIFY_MESSAGE                                    174		 
#define SSL_PROFILE_E_NON_SSLV2_INITIAL_PACKET                                  175		 
#define SSL_PROFILE_E_NO_CERTIFICATES_RETURNED                                  176		 
#define SSL_PROFILE_E_NO_CERTIFICATE_ASSIGNED                                   177		 
#define SSL_PROFILE_E_NO_CERTIFICATE_RETURNED                                   178		 
#define SSL_PROFILE_E_NO_CERTIFICATE_SET                                        179		 
#define SSL_PROFILE_E_NO_CERTIFICATE_SPECIFIED                                  180		 
#define SSL_PROFILE_E_NO_CIPHERS_AVAILABLE                                      181		 
#define SSL_PROFILE_E_NO_CIPHERS_PASSED                                         182		 
#define SSL_PROFILE_E_NO_CIPHERS_SPECIFIED                                      183		 
#define SSL_PROFILE_E_NO_CIPHER_LIST                                            184		 
#define SSL_PROFILE_E_NO_CIPHER_MATCH                                           185		 
#define SSL_PROFILE_E_NO_CLIENT_CERT_RECEIVED                                   186		 
#define SSL_PROFILE_E_NO_COMPRESSION_SPECIFIED                                  187		 
#define SSL_PROFILE_E_NO_METHOD_SPECIFIED                                       188		 
#define SSL_PROFILE_E_NO_PRIVATEKEY                                             189		 		
#define SSL_PROFILE_E_NO_PRIVATE_KEY_ASSIGNED                                   190		 
#define SSL_PROFILE_E_NO_PROTOCOLS_AVAILABLE                                    191		 
#define SSL_PROFILE_E_NO_PUBLICKEY                                              192		 
#define SSL_PROFILE_E_NO_SHARED_CIPHER                                          193		 
#define SSL_PROFILE_E_NO_VERIFY_CALLBACK                                        194		 
#define SSL_PROFILE_E_NULL_SSL_CTX                                              195		 
#define SSL_PROFILE_E_NULL_SSL_METHOD_PASSED                                    196		 
#define SSL_PROFILE_E_OLD_SESSION_CIPHER_NOT_RETURNED                           197		 
#define SSL_PROFILE_E_PACKET_LENGTH_TOO_LONG                                    198		 
#define SSL_PROFILE_E_PEER_DID_NOT_RETURN_A_CERTIFICATE				199		 
#define SSL_PROFILE_E_PEER_ERROR                                                200		 
#define SSL_PROFILE_E_PEER_ERROR_CERTIFICATE                                    201		 
#define SSL_PROFILE_E_PEER_ERROR_NO_CERTIFICATE                                 202		 
#define SSL_PROFILE_E_PEER_ERROR_NO_CIPHER                                      203		 
#define SSL_PROFILE_E_PEER_ERROR_UNSUPPORTED_CERTIFICATE_TYPE                   204		 
#define SSL_PROFILE_E_PRE_MAC_LENGTH_TOO_LONG                                   205		 
#define SSL_PROFILE_E_PROBLEMS_MAPPING_CIPHER_FUNCTIONS                         206		 
#define SSL_PROFILE_E_PROTOCOL_IS_SHUTDOWN                                      207		 
#define SSL_PROFILE_E_PUBLIC_KEY_ENCRYPT_ERROR                                  208		 
#define SSL_PROFILE_E_PUBLIC_KEY_IS_NOT_RSA                                     209		 
#define SSL_PROFILE_E_PUBLIC_KEY_NOT_RSA                                        210		 
#define SSL_PROFILE_E_READ_BIO_NOT_SET                                          211		 
#define SSL_PROFILE_E_READ_WRONG_PACKET_TYPE                                    212		 
#define SSL_PROFILE_E_RECORD_LENGTH_MISMATCH                                    213		 
#define SSL_PROFILE_E_RECORD_TOO_LARGE                                          214		 
#define SSL_PROFILE_E_REQUIRED_CIPHER_MISSING                                   215		 
#define SSL_PROFILE_E_REUSE_CERT_LENGTH_NOT_ZERO                                216		 
#define SSL_PROFILE_E_REUSE_CERT_TYPE_NOT_ZERO                                  217		 
#define SSL_PROFILE_E_REUSE_CIPHER_LIST_NOT_ZERO                                218		 
#define SSL_PROFILE_E_SHORT_READ                                                219		 
#define SSL_PROFILE_E_SIGNATURE_FOR_NON_SIGNING_CERTIFICATE                     220		 
#define SSL_PROFILE_E_SSL23_DOING_SESSION_ID_REUSE                              221		 
#define SSL_PROFILE_E_SSL3_SESSION_ID_TOO_SHORT                                 222		 
#define SSL_PROFILE_E_SSLV3_ALERT_PEER_ERROR_CERTIFICATE                        223		 
#define SSL_PROFILE_E_SSLV3_ALERT_PEER_ERROR_NO_CERTIFICATE                     224		 
#define SSL_PROFILE_E_SSLV3_ALERT_PEER_ERROR_NO_CIPHER                          225		 
#define SSL_PROFILE_E_SSLV3_ALERT_PEER_ERROR_UNSUPPORTED_CERTIFICATE_TYPE	226              
#define SSL_PROFILE_E_SSLV3_ALERT_UNKNOWN_REMOTE_ERROR_TYPE		        227		 
#define SSL_PROFILE_E_SSL_CTX_HAS_NO_DEFAULT_SSL_VERSION 			228		 
#define SSL_PROFILE_E_SSL_HANDSHAKE_FAILURE                                     229		 
#define SSL_PROFILE_E_SSL_LIBRARY_HAS_NO_CIPHERS                                230		 
#define SSL_PROFILE_E_SSL_SESSION_ID_IS_DIFFERENT                               231		 
#define SSL_PROFILE_E_TLS_CLIENT_CERT_REQ_WITH_ANON_CIPHER                      232		 
#define SSL_PROFILE_E_TLS_PEER_DID_NOT_RESPOND_WITH_CERTIFICATE_LIST 		233		 
#define SSL_PROFILE_E_TLS_RSA_ENCRYPTED_VALUE_LENGTH_IS_WRONG	                234		 
#define SSL_PROFILE_E_TRIED_TO_USE_UNSUPPORTED_CIPHER                           235		 
#define SSL_PROFILE_E_UNABLE_TO_DECODE_DH_CERTS                                 236		 
#define SSL_PROFILE_E_UNABLE_TO_EXTRACT_PUBLIC_KEY                              237		 
#define SSL_PROFILE_E_UNABLE_TO_FIND_DH_PARAMETERS                              238		 
#define SSL_PROFILE_E_UNABLE_TO_FIND_PUBLIC_KEY_PARAMETERS                      239		 
#define SSL_PROFILE_E_UNABLE_TO_FIND_SSL_METHOD                                 240		 
#define SSL_PROFILE_E_UNABLE_TO_LOAD_SSL2_MD5_ROUTINES				241		 
#define SSL_PROFILE_E_UNABLE_TO_LOAD_SSL3_MD5_ROUTINES				242		 
#define SSL_PROFILE_E_UNABLE_TO_LOAD_SSL3_SHA1_ROUTINES				243		 
#define SSL_PROFILE_E_UNEXPECTED_MESSAGE                                        244		 
#define SSL_PROFILE_E_UNEXPECTED_RECORD                                         245		 
#define SSL_PROFILE_E_UNKNOWN_ALERT_TYPE                                        246		 
#define SSL_PROFILE_E_UNKNOWN_CERTIFICATE_TYPE                                  247		 
#define SSL_PROFILE_E_UNKNOWN_CIPHER_RETURNED                                   248              
#define SSL_PROFILE_E_UNKNOWN_CIPHER_TYPE                                       249              
#define SSL_PROFILE_E_UNKNOWN_KEY_EXCHANGE_TYPE                                 250              
#define SSL_PROFILE_E_UNKNOWN_PKEY_TYPE                                         251              
#define SSL_PROFILE_E_UNKNOWN_PROTOCOL                                          252              
#define SSL_PROFILE_E_UNKNOWN_REMOTE_ERROR_TYPE                                 253              
#define SSL_PROFILE_E_UNKNOWN_SSL_VERSION                                       254              
#define SSL_PROFILE_E_UNKNOWN_STATE                                             255              
#define SSL_PROFILE_E_UNSUPPORTED_CIPHER                                        256              
#define SSL_PROFILE_E_UNSUPPORTED_COMPRESSION_ALGORITHM				257              
#define SSL_PROFILE_E_UNSUPPORTED_PROTOCOL                                      258              
#define SSL_PROFILE_E_UNSUPPORTED_SSL_VERSION                                   259              
#define SSL_PROFILE_E_WRITE_BIO_NOT_SET                                         260              
#define SSL_PROFILE_E_WRONG_CIPHER_RETURNED                                     261              
#define SSL_PROFILE_E_WRONG_MESSAGE_TYPE                                        262              
#define SSL_PROFILE_E_WRONG_NUMBER_OF_KEY_BITS                                  263              
#define SSL_PROFILE_E_WRONG_SIGNATURE_LENGTH                                    264              
#define SSL_PROFILE_E_WRONG_SIGNATURE_SIZE                                      265              
#define SSL_PROFILE_E_WRONG_SSL_VERSION                                         266              
#define SSL_PROFILE_E_WRONG_VERSION_NUMBER                                      267              
#define SSL_PROFILE_E_X509_LIB                                                  268              
#define SSL_PROFILE_E_X509_VERIFICATION_SETUP_PROBLEMS				269              
#define SSL_PROFILE_E_PATH_TOO_LONG                                             270              
#define SSL_PROFILE_E_BAD_LENGTH                                                271              
#define SSL_PROFILE_E_ATTEMPT_TO_REUSE_SESSION_IN_DIFFERENT_CONTEXT             272		 
#define SSL_PROFILE_E_SSL_SESSION_ID_CONTEXT_TOO_LONG                           273			 
#define SSL_PROFILE_E_LIBRARY_BUG                                               274			 
#define SSL_PROFILE_E_UNINITIALIZED                                             276			 
#define SSL_PROFILE_E_SESSION_ID_CONTEXT_UNINITIALIZED				277			 
#define SSL_PROFILE_E_INVALID_PURPOSE                                           278			 
#define SSL_PROFILE_E_INVALID_TRUST                                             279		   
#define SSL_PROFILE_E_INVALID_COMMAND                                           280		   
#define SSL_PROFILE_E_SSLV3_ALERT_UNEXPECTED_MESSAGE                            1010		 
#define SSL_PROFILE_E_SSLV3_ALERT_BAD_RECORD_MAC                                1020		 
#define SSL_PROFILE_E_TLSV1_ALERT_DECRYPTION_FAILED                             1021		 
#define SSL_PROFILE_E_TLSV1_ALERT_RECORD_OVERFLOW                               1022		 
#define SSL_PROFILE_E_SSLV3_ALERT_DECOMPRESSION_FAILURE				1030		 
#define SSL_PROFILE_E_SSLV3_ALERT_HANDSHAKE_FAILURE                             1040		 
#define SSL_PROFILE_E_SSLV3_ALERT_NO_CERTIFICATE                                1041		 
#define SSL_PROFILE_E_SSLV3_ALERT_BAD_CERTIFICATE                               1042		 
#define SSL_PROFILE_E_SSLV3_ALERT_UNSUPPORTED_CERTIFICATE			1043		 
#define SSL_PROFILE_E_SSLV3_ALERT_CERTIFICATE_REVOKED                           1044		 
#define SSL_PROFILE_E_SSLV3_ALERT_CERTIFICATE_EXPIRED                           1045		 
#define SSL_PROFILE_E_SSLV3_ALERT_CERTIFICATE_UNKNOWN                           1046		 
#define SSL_PROFILE_E_SSLV3_ALERT_ILLEGAL_PARAMETER                             1047		 
#define SSL_PROFILE_E_TLSV1_ALERT_UNKNOWN_CA                                    1048		 
#define SSL_PROFILE_E_TLSV1_ALERT_ACCESS_DENIED                                 1049		 
#define SSL_PROFILE_E_TLSV1_ALERT_DECODE_ERROR                                  1050		 	
#define SSL_PROFILE_E_TLSV1_ALERT_DECRYPT_ERROR                                 1051		 
#define SSL_PROFILE_E_TLSV1_ALERT_EXPORT_RESTRICTION                            1060		 
#define SSL_PROFILE_E_TLSV1_ALERT_PROTOCOL_VERSION                              1070		 
#define SSL_PROFILE_E_TLSV1_ALERT_INSUFFICIENT_SECURITY				1071		 
#define SSL_PROFILE_E_TLSV1_ALERT_INTERNAL_ERROR                                1080		 
#define SSL_PROFILE_E_TLSV1_ALERT_USER_CANCELLED                                1090		 
#define SSL_PROFILE_E_UNSUPPORTED_OPTION                                        1091		 
#define SSL_PROFILE_E_ERROR_GENERATING_TMP_RSA_KEY                              1092		 
#define SSL_PROFILE_E_RECORD_TOO_SMALL                                          1093		 
#define SSL_PROFILE_E_TLSV1_ALERT_NO_RENEGOTIATION                              1100		 
#define SSL_PROFILE_E_DECRYPTION_FAILED_OR_BAD_RECORD_MAC			1109		 
#define SSL_PROFILE_E_ILLEGAL_PADDING                                           1110		 
#define SSL_PROFILE_E_MESSAGE_TOO_LONG                                          1111		 
#define SSL_PROFILE_E_KEY_ARG_TOO_LONG                                          1112		 
#define SSL_PROFILE_E_SSL3_SESSION_ID_TOO_LONG                                  1113		 
#define SSL_PROFILE_E_SSL2_CONNECTION_ID_TOO_LONG                               1114		 
/**
\endcond */

#ifndef __SSL_HANDLES__
typedef void * SSL_HANDLE;              /*!< SSL session handle */
typedef void * SSL_SERVER_HANDLE;       /*!< SSL server handle */ 
typedef void * SSL_PROFILE_HANDLE;      /*!< SSL profile handle */
typedef void * X509_HANDLE;             /*!< X509 certificate handle */
typedef void * X509_CRL_HANDLE;         /*!< X509 CRL handle */
#define __SSL_HANDLES__
#endif

#define SSL_MAX_SESSION_ID_LENGTH 32	 /*!< Session ID length*/

/*
======================================================================
                        Data Structures Definition
======================================================================
*/

typedef struct
{
        int protocol;                                   /*!< Which protocol is used */ 
        unsigned int id_length;                         /*!< Identifier length of the session */ 
        unsigned char id[SSL_MAX_SESSION_ID_LENGTH];    /*!< Session identifier */ 
        unsigned long cipher;                           /*!< What ciphers are used */
#ifdef __SSL_EXPORT_COMPATIBILITY
		unsigned long export;                      		/*!< Strength and export flags */
#else
		unsigned long export_mask;                      /*!< Strength and export flags */
#endif
        int strength_bits;                              /*!< Number of bits really used */
} SSL_SESSION_INFO;

/*
======================================================================
                        Functions Definition
======================================================================
*/

/*! @brief This function initializes the SSL library.  It loads the SSL Library and link it to the caller.
 *
 *	@return
 *	- OK (0) if successful
 *	- Otherwise negative error code
 *
 *	@note This function must be called prior using any other routines of the library.
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int ssllib_open(void);


/*! @brief This function closes the SSL library
 *
 **/
void ssllib_close(void);

/*! @brief This function creates an ssl structure
 *
 * @param		ssl : A SSL structure
 * @param   profile : The profile handle used for the connection.
 *	@return
 *	- OK (0) if successful
 *	- Otherwise negative error code
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_New( SSL_HANDLE * ssl, SSL_PROFILE_HANDLE profile );


/*! @brief This function free an allocated SSL structure
 * @param   ssl : A SSL structure
 * @return
 * - OK (0) if successful
 * - Otherwise negative error code
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_Free( SSL_HANDLE ssl );


/*! @brief This function allows to attach an existing socket to the SSL session
 * @param   ssl : A SSL structure
 * @param   sok : A socket handle
 * @return
 * - SSL_EOK (0) if successful
 * - Otherwise negative error code
 *
 *	@note 
 *
 *	When this function is called, the socket is not managed (connection and disconnection) by the SSL DLL
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_SetSocket(SSL_HANDLE ssl, int sok);


/*! @brief This function is used to connect to the server
 * @param ssl : A SSL structure
 * @param ip_dot_addr : The ssl server IP address like "192.168.1.2" or domain name adress
 * @param port : The ssl server port
 * @param timeout : Timeout 1/100 second
 * @return
 * - OK (0) if successful
 * - Otherwise negative error code
 *
 *	@note 
 *
 *	It is possible to get an accurate error code by requesting the function #SSL_ProfileGetLastError
 *
 *  The connection supports the cache facility, if this one is activated by the
                server. The SSL library allows to keep 4 cache contexts per handle. A
                cache context points at a server address (same address and port). The
                context is automatically reused when this server is connected. It avoids
                from redoing the handshake. The contexts are erased when the SSL
                handle is freed (call to #SSL_Free). The server can also discard the
                context, when the validity period of the connection in its cache has
                expired.
 *
 *	The timeout parameter can be set to 0. In this case, the function is not
                blocking. It returns the error code SSL_EAGAIN while the connection is
                in progress.
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_Connect( SSL_HANDLE ssl, const char *ip_dot_addr, int port,int timeout);


/*! @brief This function is used to read data on a SSL connection
 * @param ssl : A SSL structure
 * @param buf : Buffer where the data are saved
 * @param num : Size of the data buffer
 * @param timeout : Timeout 1/100 second
 * @return
 * - Number of read bytes
 * - Otherwise negative error code
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_Read( SSL_HANDLE ssl, void * buf, int num, int timeout);


/*! @brief This function closes a SSL connection
 * @param ssl : A SSL structure
 * @return
 *	- OK logout (1) 
 *	- partial disconnection (0)  
 *	  (disconnection and sent no request disconnection of remote) 
 *	- Otherwise negative error code
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_Disconnect( SSL_HANDLE ssl);


/*! @brief This function return a SSL connection state
 * @param ssl : A SSL structure
 * @return
 *	- SSL connection state (#SSL_STATE_DISCONNECT, #SSL_STATE_TCP_CONNECTION, #SSL_STATE_TCP_CONNECT, #SSL_STATE_SSL_CONNECTION, #SSL_STATE_SSL_CONNECT, #SSL_STATE_CONNECT)
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_GetConnectionState( SSL_HANDLE ssl);


/*! @brief This function sends data through the SSL connection. 
 *
 *	These data transferred to the server and are automatically ciphered by the SSL
                protocol.
 * @param ssl : A SSL structure
 * @param buf	: Data to send
 * @param num : Size in bytes of the data buffer
 * @param timeout : Timeout 1/100 second
 * @return Number of send bytes, otherwise negative error code
 *	This function returns (-1) in case of timeout.		
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_Write( SSL_HANDLE ssl, const void * buf, int num, int timeout);


/*! @brief This function gets information about a connection.
 *
 *	It is used to know the options negotiated during the SSL handshake (protocol version,
        ciphers, session identifier...). All the information are stored in the structure #SSL_SESSION_INFO
 * @param ssl : A SSL structure handle
 * @param pInfo : Connection Info
 * @return
 *	- #SSL_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_EINVAL, #SSL_ENOENT)
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_GetSessionInfo(SSL_HANDLE ssl, SSL_SESSION_INFO * pInfo);


/*! @brief This function gets alert error about a connection.
 *
 *	It is used to know the reason of peer handshake error.
 * @param ssl : A SSL structure handle
 * @return
 *	- #SSL_EOK (0) if no error
 *	- Otherwise error code value as describe in SSL RFC-2246
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_GetAlertError(SSL_HANDLE ssl);


/*! @brief This function creates a new ssl profile and returns its handle. 
 *
 * This new profile is not automatically saved in flash. To do that, the function
        #SSL_SaveProfile must be called.
 * @param szName	: Name of the new profile. Maximum size of name is #PROFILE_NAME_SIZE including null terminated character.
 * @param pError	: #SSL_PROFILE_EOK (0) if successful, otherwise negative error code
 *				(#SSL_PROFILE_ELOADED, #SSL_PROFILE_ETOOMANY, #SSL_PROFILE_ENOMEM, #SSL_PROFILE_EPARAM, #SSL_PROFILE_EEXIST)
 * @return The profile handle if successful, otherwise NULL
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
SSL_PROFILE_HANDLE SSL_NewProfile( const char *szName, int * pError );


/*! @brief This function loads a profile search by its name.
 * @param szName	: Name of the profile
 * @return The profile handle if successful, otherwise NULL
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
SSL_PROFILE_HANDLE SSL_LoadProfile( const char *szName );


/*! @brief This function unloads an ssl profile
 * @param profile	: A profile handle
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_EPARAM)
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_UnloadProfile( SSL_PROFILE_HANDLE profile );


/*! @brief This function adds a CA or CRL to a profile
 * @param handle	: A profile handle
 * @param caFile	: CA or CRL file
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_ECAEXIST, #SSL_PROFILE_ECATOOMANY, #SSL_PROFILE_EPARAM)
 *
 *	@note This function does not check if the key file exists in Flash. 
                It just adds its reference in the profile.
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_ProfileAddCertificateCA( SSL_PROFILE_HANDLE handle, const char * caFile );


/*! @brief This function removes a CA of a profile
 * @param handle	: A profile handle
 * @param caFile	: CA file
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_ECANEXIST, #SSL_PROFILE_EPARAM)
 *
 *	@note This function does not erase the certificate file in Flash. 
                It just removes its reference in the profile.
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_ProfileRemoveCertificateCA( SSL_PROFILE_HANDLE handle,const char * caFile);


/*! @brief This function saves an ssl profile.  All the modifications 
                made in this profile are stored in flash.
 * @param handle	:A profile handle
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_EPARAM)
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_SaveProfile( SSL_PROFILE_HANDLE handle );


/*! @brief This function deletes an ssl profile in the ssl saved list
 * @param name	: Name of the profile
 * @return 
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code(#SSL_PROFILE_ELOADED, #SSL_PROFILE_EPARAM)
 *
 *	@note This functions deletes the profile but it does not delete the files
                references by this file (key files, certificate files).
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_DeleteProfile(const char * name);


/*! @brief This function returns the error code of the last operation.
 * @param profile	: A profile handle
 * @param error	: The error code
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_EPARAM)
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileGetLastError( SSL_PROFILE_HANDLE profile, int *error );


/*! @brief This function returns the number of CA used by the ssl profile.
 *
 *	It corresponds to the number of CA certificates contained
                in the profile.
 * @param handle	: A profile handle
 * @param nb_ca	: number of CA
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_EPARAM)
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileGetCACount( SSL_PROFILE_HANDLE handle, int * nb_ca);


/*! @brief This function returns the name of the file which contains the client
                X509 certificate.
 * @param handle	: A profile handle
 * @param certificateFile	: The certificate file (size of buffer must at least FS_PATHSIZE)
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_EPARAM, #SSL_PROFILE_ENOCERT)
 *
 * @note The client certificate file is needed only in case of profile configured for mutual authentication.
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileGetCertificateFile( SSL_PROFILE_HANDLE handle, char *certificateFile );


/*! @brief This function returns the name of the CA certificate file.
 *
 * This authority is searched by its index of the CA list of the profile.
 * @param handle	: A profile handle
 * @param num	: The number of CA
 * @param caFile	: The CA file (size of buffer must at least FS_PATHSIZE)
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_EPARAM, #SSL_PROFILE_ECANEXIST)
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileGetCAFile( SSL_PROFILE_HANDLE handle, int num, char * caFile);


/*! @brief This function sets the private key file used by the ssl profile
 *
 *	The file contains the asymmetric keys used in case of a mutual authentication.
                The parameter 'isEncrypted' indicates if the key file is encrypted. It is the
                case when the keys are automatically generated by the terminal
 *
 * @param handle	: A profile handle
 * @param keyFile	: Private key file or NULL for the internal private key
 * @param isEncrypted	: TRUE if the private key is encrypted with internal key, otherwise FALSE
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_EPARAM)
 *
 *	@note This function does not check if the key file exists in Flash. 
                It just adds its reference in the profile.
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileSetKeyFile( SSL_PROFILE_HANDLE handle, const char * keyFile, int isEncrypted);


/*! @brief This function gets the private key file used by the ssl profile
 *
 *	The file contains the asymmetric keys used in case of a mutual authentication.
                The parameter 'isEncrypted' indicates if the key file is encrypted. It is the
                case when the keys are automatically generated by the terminal
 *
 * @param handle	: A profile handle
 * @param keyFile	: Private key file (size of buffer must at least FS_PATHSIZE)
 * @param isEncrypted	: TRUE if the private key is encrypted with internal key, otherwise FALSE
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_EPARAM)
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileGetKeyFile( SSL_PROFILE_HANDLE handle, char * keyFile, int * isEncrypted);


/*! @brief This function sets the certificate file used by the ssl profile.
 *
 *	The profile will operate in mutual authentication.
 * @param handle	: A profile handle or NULL
 * @param certificateFile	: Certificate file
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_EPARAM)
 *
 *	@note This function does not check if the certificate file exists in Flash.
                It just adds its reference in the profile.
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileSetCertificateFile( SSL_PROFILE_HANDLE handle,const char * certificateFile);


/*! @brief This function sets the ssl protocol used by the ssl profile
 * @param handle	: A profile handle
 * @param protocol	: The ssl protocol (SSLv2,SSLv3,TLSv1)
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED)
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileSetProtocol( SSL_PROFILE_HANDLE handle,int protocol);


/*! @brief This function gets the ssl protocol used by the ssl profile
 * @param handle	: A profile handle
 * @param protocol	: The ssl protocol (SSLv2,SSLv3,TLSv1)
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED)
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileGetProtocol( SSL_PROFILE_HANDLE handle, int * protocol);


/*! @brief This function sets the mask of ciphers and export modes supported
                by the profile
 * @param handle	   : A profile handle
 * @param cipher	   : A mask of supported cipher
 * @param export_mask  : A mask between export mode and the cipher strength
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED)
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileSetCipher( SSL_PROFILE_HANDLE handle, long int cipher, long int export_mask );


/*! @brief This function gets the mask of ciphers and export modes supported
                by the profile.
 * @param handle	   : A profile handle
 * @param cipher	   : A mask of supported cipher
 * @param export_mask  : A mask between export mode and the cipher strength
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful 
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED)
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileGetCipher( SSL_PROFILE_HANDLE handle, long int * cipher, long int * export_mask );


/*! @brief This function gets the name of the profile
 * @param handle	: A profile handle
 * @param name	: The name of the profile (size of buffer must at least #PROFILE_NAME_SIZE)
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_EPARAM)
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileGetName( SSL_PROFILE_HANDLE handle, char *name );


/*! @brief This function loads a profile search by its index in the profile list.
 * @param index	: The index of the profile
 * @return The loaded profile handle if successful, otherwise NULL
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
SSL_PROFILE_HANDLE SSL_GetProfile(int index);


/*! @brief This function is used to get the number of profiles
 * @return The number of SSL profiles
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_GetProfileCount(void);


/*! @brief This function gets the ip and port value
 * @param handle	: A profile handle
 * @param address : The ssl server IP address like "192.168.1.2" the size of buffer must be at least 16
 * @param port : The ssl server port
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_EPARAM)
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileGetLastIpServer(SSL_PROFILE_HANDLE handle,char * address,int * port);


#ifdef __SSL_DATE__
/*! @brief This function gets the date of the last connection
 * @param handle	: A profile handle
 * @param date	: The date of the last connection
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_ENLOADED, #SSL_PROFILE_EPARAM)
 *
 * @note This function requires the definition of the structure "DATE"
                (defined in "oem_public.h"). The pre-processor variable "__SSL_DATE__"
                must be also defined in the compilation settings.
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_ProfileGetLastDate(SSL_PROFILE_HANDLE handle,DATE * pDate);
#endif


/*! @brief This function test if all file of the ssl profile exist
 * @param handle	: A profile handle
 * @return
 *	- #SSL_PROFILE_EOK (0) if successful
 *	- Otherwise negative error code (#SSL_PROFILE_EPARAM, #SSL_PROFILE_ENLOADED, #SSL_PROFILE_ENOCERT)
 *
 *	@link KSFAM_SSL Back to top @endlink
 **/
int SSL_ProfileTestFile(SSL_PROFILE_HANDLE handle);


/*! @brief This function starts an SSL server and creates an SSL_SERVER structure
 * @param serv : A SSL_SERVER structure
 * @param profileHandle : The profile handle
 * @param useCache	: If TRUE use SSL cache session reuse
 * @param mustVerify	: if TRUE verify peer certificate
 * @param port	: Listening port
 * @return OK (0) if successful, otherwise negative error code
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_Server_Open( SSL_SERVER_HANDLE * serv, SSL_PROFILE_HANDLE profileHandle, int useCache, int mustVerify, int port);


/*! @brief This function accepts remote connections on the SSL server.
 *
 *	Please note that at the end of the communication, the SSL handle
                corresponding to the client connection (hHandle) must be released
                by the application using SSL_Free() function.
 * @param ssl : A SSL structure (must not be dealocate with SSL_Free function)
 * @param serv : A SSL_SERVER structure
 * @param timeout : Timeout 1/100 second
 * @return OK (0) if successful, otherwise negative error code
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_Server_Accept(SSL_HANDLE * ssl,SSL_SERVER_HANDLE serv,int timeout);


/*! @brief This function closes an SSL server and free an allocated SSL_SERVER structure
 * @param serv : A SSL_SERVER structure
 * @return OK (0) if successful, otherwise negative error code
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_Server_Close( SSL_SERVER_HANDLE serv);


/*! @brief This function flush the SSL server cache.
 * @param serv : A SSL_SERVER structure
 * @return OK (0) if successful, otherwise negative error code
 *
 * @link KSFAM_SSL Back to top @endlink 
**/
int SSL_Server_ClearCache(SSL_SERVER_HANDLE serv);


#endif
/*! @} **/

//! \defgroup SSL_SAMPLE	SSL samples
//! This section explains the SSL sample provided with the package.
//! \ingroup TCPIP_SAMPLES
//! @{
//! \defgroup SSL_SAMPLE_LOAD		Load and initialize the SSL library.
//! The open of the library is requested prior any call of a routine of the library.
//! \include SSL__Sample_01.c
//! \example SSL__Sample_01.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}
//! 
//! \defgroup SSL_SAMPLE_PROFILE		SSL profile management.
//! The following sample code is adapted from the sample.
//! It shows how to create a new profile and how to save it in flash.
//! \include SSL__Sample_02.c
//! \example SSL__Sample_02.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}
//! 
//! \defgroup SSL_SAMPLE_TRANSFER		SSL connection, transfer and disconnection.
//! The following code is adapted from the sample. 
//! It performs a simple connection to an SSL server, sends and receives data 
//! and then disconnects.
//! \include SSL__Sample_03.c
//! \example SSL__Sample_03.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}
//! 
//! \defgroup SSL_SAMPLE_INFO		Printing the connection information
//! The following code shows how to interpret the information get from the function
//! \ref SSL_GetSessionInfo.
//! \include SSL__Sample_04.c
//! \example SSL__Sample_04.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}
//! 
//! \defgroup SSL_SAMPLE_SERVER		SSL server
//! A sample which shows how to create and manage an SSL server.
//! \include SSL__Sample_05.c
//! \example SSL__Sample_05.c
//! @{
// -- DO NOT SUPPRESS THIS LINE -------------------
//! @}

//! @}


