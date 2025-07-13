#ifndef __FTP__H__
#define __FTP__H__

#ifdef __cplusplus
extern "C"
{
#endif

//! \file        FTP_.h
//! \brief This module contains all the FTP definitions.
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
 
//! \addtogroup TCPIP_FTP 
//! \brief This module contains all the FTP definitions.
//!
//! \par Introduction
//! The package FTP is a static library which implements a simple API to use the dynamic FTP
//! library. It must be linked with the application. It is composed of the API header file "FTP_.h " and
//! a library "FTP_.lib" compiled with the three compilers (GCC, RVD and SDT) supported by the
//! Telium SDK.
//!
//! The package provides all the services to monitor the FTP client facility :
//! 	- File downloading and uploading.
//! 	- Remote file system monitoring
//! 	- Downloaded software activation
//!
//! <TABLE border="3" cellspacing="0" bordercolor="black">
//! <TR><TD></TD></TR>
//! <TR><TD><b>Developers shall read the document <a href="ICO-PE-045-GU-EN_PackIP_SecurityGuidance_UserGuide.html">[Pack IP Security Guidance]</a>
//! which describes best practises for implementing FTP enabled applications, according to
//! the requirements of the POS Terminal Security Program (PTS) and of the PCI PTS v3 "Open Protocols" module.</b></TD></TR>
//! <TR><TD></TD></TR>
//! </TABLE>
//!
//! The FTP protocol is described in the RFC 959.
//!
//! Please refer \ref FTP_SAMPLE. 
//!
//! <b>Be careful</b>, do not forget to load the dynamic FTP library (3614xxxx.LDF/SGN) in your terminal.
//!
//
//! @{

//! \brief FTP handle.
typedef void * FTP_HANDLE;

//! \cond __EXCLUDE__
#define __FTP_RELEASE1			1
//! \endcond 

#define __TYPE_ASCII			'a'		//!< ASCII file format.
#define __TYPE_BINARY			'i'		//!< Binary file format.
#define __TYPE_IMAGE			'i'		//!< Image file format (same as binary).



//! \cond __EXCLUDE__

#ifndef __SSL_HANDLES__
//! \brief Definition of SSL_HANDLE.
typedef void * SSL_HANDLE;	
//! \brief Definition of SSL_SERVER_HANDLE.
typedef void * SSL_SERVER_HANDLE;
//! \brief Definition of SSL_PROFILE_HANDLE.
typedef void * SSL_PROFILE_HANDLE;
//! \brief Definition of X509_HANDLE.
typedef void * X509_HANDLE;
#define __SSL_HANDLES__
#endif
//! \endcond


// Connection management

// PPP interface options.
//! \defgroup FTP_OPTIONS PPP options.
//! \brief Options of the FTP interface.
//! @{
#define FTP_OPTION_TIMEOUT		0
//! @}

//! \brief This function sets an option on a FTP handle.
//! \param handle : Must be NULL.
//! \param nOption : Option number. \ref FTP_OPTIONS
//! \param pOptionData : Pointer on the option data.
//! \return
//! - 0 if successful.
//! - -1 otherwise.
int FTP_SetOption( FTP_HANDLE handle, int nOption, void* pOptionData );

//! \brief This function performs a connection to a FTP server.
//! The passive mode determines the connection mode of the data channel. In passive mode, this connection is initiated by the client (e.g. by the terminal).
//! \param szLogin : FTP user name.
//! \param szPassword : FTP password.
//! \param szAddress : FTP server address. This address must be a resolved
//! address ( ex : '217.12.3.11' ).
//! \param nPort : FTP server port. Generally set to 21 (standard FTP port number).
//! \param bPassive : Passive mode activation.
//! \return
//! - The connection handle if successful.
//! - NULL otherwise.
//! \note 
//! This functions performs automatically the loading of the dynamic FTP 
//! library.
// \if SIMULATION
//  @GSIM_F:FTP_Connect:KSFAM_FTP:0x01
//  @GSIM_A:0:ONE_ADDRESS
// \endif
FTP_HANDLE FTP_Connect( const char *szLogin, const char *szPassword,
                        const char *szAddress, unsigned short nPort, int bPassive );



//! \brief This function requests a FTP disconnection. It must be called to terminate all the FTP connections (even if the disconnection is initiated by the remote part). This function releases the allocated handle and all the TCP/IP resources used for the connection.
//! \param handle : FTP connection handle.
//! \return None.
// \if SIMULATION
//  @GSIM_F:FTP_Disconnect:KSFAM_FTP:0x02
//  @GSIM_A:1: ONE_ADDRESS
// \endif
void FTP_Disconnect( FTP_HANDLE handle );

//! \brief This function returns the full path of the current folder in the remote file system.
//! \param handle : FTP connection handle.
//! \param szBuffer : Output buffer set to the current directory path.
//! \param nBufferLen : Maximum size of the output buffer.
//! \return 
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_GetCurrentDir:KSFAM_FTP:0x03
//  @GSIM_A:1:ONE_ADDRESS 
//  @GSIM_A:2:DATA_SIZE(nBufferLen)
// \endif
int FTP_GetCurrentDir( FTP_HANDLE handle, char *szBuffer, int nBufferLen );

//! \brief This function creates a new directory into the current folder of the 
//! remote file system. The execution of this operation must be allowed by the remote server.
//! \param handle : FTP connection handle.
//! \param szRemoteDirName : Name of the directory to create in the current folder of the remote file system.
//! \return 
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_MakeDir:KSFAM_FTP:0x04
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_MakeDir( FTP_HANDLE handle, const char *szRemoteDirName );

//! \brief This function deletes a directory into the current folder of the remote 
//! file system.The execution of this operation must be allowed by the remote server.
//! \param handle : FTP connection handle.
//! \param szRemoteDirName : Name of the directory to remove in the current folder of the remote file system.
//! \return 
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_RemoveDir:KSFAM_FTP:0x05
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int FTP_RemoveDir( FTP_HANDLE handle, const char *szRemoteDirName );

//! \brief This function gets the current item of the list. The internal cursor is 
//! moved on the next item.
//! \param handle : FTP connection handle.
//! \return 
//! - A pointer on the current item of the list, a constant character string.
//! - NULL when the end of the list is reached.
//! \note 
//! It is not possible to reset the internal cursor on the list items.
// \if SIMULATION
//  @GSIM_F:FTP_GetListItem:KSFAM_FTP:0x06
//  @GSIM_A:1: ONE_ADDRESS
// \endif
const char *FTP_GetListItem( FTP_HANDLE handle );

//! \brief This function lists the content of a directory. The execution of this 
//! operation must be allowed by the remote server. The items of the returned list can be read by using the function 'FTP_GetListItem'. The function 'FTP_GetList' returns items which contain only the name of a contained file.
//! \param handle : FTP connection handle.
//! \param szPath : Path of the directory to list.
//! \return 
//! - 0 in case of success.
//! - A negative error code otherwise
//! \note 
//! The execution of this function opens a data channel (according to the 
//! passive mode). This channel must be closed at the end (call to function 'FTP_CloseData'), after processing all the items of the list.
// \if SIMULATION
//  @GSIM_F:FTP_GetList:KSFAM_FTP:0x07
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_GetList( FTP_HANDLE handle, const char *szPath );

//! \brief This function lists the content of a directory. The execution of this operation must be allowed by the remote server. The items of the returned list can be read by using the function 'FTP_GetListItem'. The function 'FTP_GetFullList' returns items which contain the full description of a contained file.
//! \param handle : FTP connection handle.
//! \param szPath : Path of the directory to list.
//! \return 
//! - 0 in case of success.
//! - A negative error code otherwise.
//! \note
//! The execution of this function opens a data channel (according to the passive mode). This channel must be closed at the end (call to function 'FTP_CloseData'), after processing all the items of the list.
// \if SIMULATION
//  @GSIM_F:FTP_GetFullList:KSFAM_FTP:0x08
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_GetFullList( FTP_HANDLE handle, const char *szPath );

//! \brief This function goes into a new directory. The execution of this 
//! operation must be allowed by the remote server.This new directory becomes the current one.
//! \param handle : FTP connection handle.
//! \param szPath : Name of the new current directory.
//! \return 
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_ChangeDir:KSFAM_FTP:0x09
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int FTP_ChangeDir( FTP_HANDLE handle, const char *szPath );

//! \brief This function deletes a file into the current folder of the remote file 
//! system. The execution of this operation must be allowed by the remote server.
//! \param handle : FTP connection handle.
//! \param szDstFile : Name of the file to remove in the current folder of the remote file system.
//! \return 
//! - 0 in case of success
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_RemoveFile:KSFAM_FTP:0x0A
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_RemoveFile( FTP_HANDLE handle, const char *szDstFile  );

//! \brief This function renames a file into the current folder of the remote file 
//! system. The execution of this operation must be allowed by the remote server.
//! \param handle : FTP connection handle.
//! \param szRemoteOldName : Name of the file to rename in the current folder of the remote file system.
//! \param szRemoteNewName : New Name of the file.
//! \return 
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_RenameFile:KSFAM_FTP:0x0B
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_RenameFile( FTP_HANDLE handle, 
					const char *szRemoteOldName,
					const char *szRemoteNewName );


//! \brief This function returns the error code of the last operation.
//! \param handle : FTP connection handle.
//! \return
//! The last error code.
//! \note
//! The error codes are listed in the FTP specifications (RFC 959).
// \if SIMULATION
//  @GSIM_F:FTP_GetError:KSFAM_FTP:0x0C
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_GetError( FTP_HANDLE handle );

//! \brief This function modifies the representation of the transferred data during the connection.
//! \param handle : FTP connection handle.
//! \param type : Data type : ASCII mode (__TYPE_ASCII ) or Binary mode (__TYPE_BINARY ).
//! \return
//! - 0 in case of success.
//! - A negative error code otherwise.
//! \note
//! The type 'Image' (__TYPE_IMAGE) is equivalent to the binary 
//! mode.
// \if SIMULATION
//  @GSIM_F:FTP_SetType:KSFAM_FTP:0x0D
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_SetType( FTP_HANDLE handle, char type );

//! \brief This function maintains the connection with the server. It prevents the server from closing the connection due to inactivity timers.
//! \param handle : FTP connection handle.
//! \return
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_Alive:KSFAM_FTP:0x0E
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_Alive( FTP_HANDLE handle );

//! \brief This function downloads a remote file. It transfers this file into a local 
//! file. The disk used for the local file is automatically mounted (if not previously done by the user), and is not unmounted after the download is finished.
//! \param handle : FTP connection handle.
//! \param szDstFile : Name of the remote file to download.
//! \param szLocalFile : Name of the local file (including directory, '/TEMP/MYFILE.BIN' ).
//! \return 
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_GetFile:KSFAM_FTP:0x0F
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_GetFile( FTP_HANDLE handle, const char *szDstFile, const char *szLocalFile  );

//! \brief This function uploads a local file. It transfers this file to the server.
//! \param handle : FTP connection handle.
//! \param szDstFile : Name of the remote file.
//! \param szLocalFile : Name of the local file to upload (including directory,
//! '/TEMP/MYFILE.BIN' ).
//! \return 
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_PutFile:KSFAM_FTP:0x10
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_PutFile( FTP_HANDLE handle, const char *szDstFile, const char *szLocalFile  );

//! \brief This function uploads a local file. It transfers this file into a remote
//! file. The transferred data are added at the end of the remote file.
//! \param handle : FTP connection handle.
//! \param szDstFile : Name of the remote file.
//! \param szLocalFile : Name of the local file to upload (including directory,
//! '/TEMP/MYFILE.BIN' ).
//! \return 
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_AppendFile:KSFAM_FTP:0x17
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_AppendFile( FTP_HANDLE handle, const char *szDstFile, const char *szLocalFile  );

//! \brief This function read data from the data channel. These data are sent 
//! by the server.
//! \param handle : FTP connection handle.
//! \param pBuffer : Data buffer
//! \param nBufferLen : Number of bytes to read.
//! \return 
//! The number of bytes successfully read or a negative error code.
// \if SIMULATION
//  @GSIM_F:FTP_GetData:KSFAM_FTP:0x11
//  @GSIM_A:1: ONE_ADDRESS
//  @GSIM_A:2:DATA_SIZE(nBufferLen)
// \endif
int FTP_GetData( FTP_HANDLE handle, char *pBuffer, int nBufferLen );

//! \brief This function writes data in the data channel. These data are transferred to the server.
//! \param handle : FTP connection handle.
//! \param pBuffer : Data buffer.
//! \param nBufferLen : Number of bytes to write.
//! \return 
//! The number of bytes successfully written or a negative error code.
// \if SIMULATION
//  @GSIM_F:FTP_PutData:KSFAM_FTP:0x12
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_PutData( FTP_HANDLE handle, const char *pBuffer, int nBufferLen );

//! \brief This function closes the data channel.
//! \param handle : FTP connection handle.
//! \return
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_CloseData:KSFAM_FTP:0x13
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_CloseData( FTP_HANDLE handle );

//! \param handle : FTP connection handle.
//! \param szDstFile : Name of the remote file to download.
//! \return
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_Get:KSFAM_FTP:0x14
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int FTP_Get( FTP_HANDLE handle, const char *szDstFile );

//! \brief This function opens the remote file to upload (from the client to the 
//! server) It creates a channel dedicated to the transfer of the data. These data can be written by the function 'FTP_PutData'. A the end of the transfer the data channel must be closed (call to function 'FTP_CloseData').
//! \param handle : FTP connection handle.
//! \param szDstFile : Name of the file to upload.
//! \return 
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_Put:KSFAM_FTP:0x15
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_Put( FTP_HANDLE handle, const char *szDstFile );

//! \brief This function opens the remote file to upload (from the client to the 
//! server). The remote file is opened in append mode. It creates a channel dedicated to the transfer of the data. These data can be written by the function 'FTP_PutData'. A the end of the transfer the data channel must be closed (call to function 'FTP_CloseData'). The transferred data are added at the end of the file.
//! \param handle : FTP connection handle.
//! \param szDstFile : Name of the file to upload.
//! \return
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTP_Append:KSFAM_FTP:0x16
//  @GSIM_A:1: ONE_ADDRESS
// \endif
int FTP_Append( FTP_HANDLE handle, const char *szDstFile );

// FTPS specific functions

//! \brief This function performs a connection to a secured FTP server.
//! The passive mode determines the connection mode of the data 
//! channel. In passive mode, this connection is initiated by the client (e.g. by the terminal).
//! \param szLogin : FTP user name.
//! \param szPassword : FTP password.
//! \param szAddress : FTP server address. This address must be a resolved address ( ex : '217.12.3.11' ).
//! \param nPort : FTP server port. Generally set to 990 (standard FTPS port 
//! number).
//! \param bPassive : Passive mode activation.
//! \param szSslProfile : Name of the SSL profile. If set to NULL, this function performs a 
//! standard FTP connection (using FTP_Connect).
//! \return 
//! - The connection handle (>=0).
//! - A negative error code otherwise.
//! \note This function performs automatically the loading of the dynamic SSL 
//! and FTP libraries.
// \if SIMULATION
//  @GSIM_F:FTPS_Connect:KSFAM_FTP:0x18
//  @GSIM_A:0: ONE_ADDRESS
// \endif
FTP_HANDLE FTPS_Connect( const char *szLogin, const char *szPassword,
                         const char *szAddress, unsigned short nPort, int bPassive, const char *szSslProfile );


//! \brief This function performs a connection to a secured FTP server in explicit mode (using AUTH command).
//! The passive mode determines the connection mode of the data  channel.
//! In passive mode, this connection is initiated by the client (e.g. by the terminal).
//! The data connection is automatically set to protected mode.
//! \param szLogin : FTP user name.
//! \param szPassword : FTP password.
//! \param szAddress : FTP server address. This address must be a resolved address ( ex : '217.12.3.11' ).
//! \param nPort : FTP server port. Generally set to 21 (standard FTP port number).
//! \param bPassive : Passive mode activation.
//! \param szProfile : Name of the SSL profile. If set to NULL, this function performs a 
//! standard FTP connection (using FTP_Connect).
//! \return 
//! - The connection handle (>=0).
//! - A negative error code otherwise.
//! \note This function performs automatically the loading of the dynamic SSL 
//! and FTP libraries.
FTP_HANDLE FTPES_Connect( const char *szLogin, const char *szPassword, const char *szAddress, unsigned short nPort, int bPassive, const char *szProfile );

//! \brief This function switches the command channel to clear mode.
//! This function can be disabled by the server (no handling of CCC command).
//! \param hHandle : FTP connection handle.
//! \return
//! - 0 in case of success.
//! - A negative error code otherwise.
int FTPES_UnsecureCommand( FTP_HANDLE hHandle);

//! \brief This function switches the command channel to secure mode.
//! \param hHandle : FTP connection handle.
//! \param szLogin : FTP user name.
//! \param szPassword : FTP password.
//! \param szProfile : Name of the SSL profile.
//! \return
//! - 0 in case of success.
//! - A negative error code otherwise.
int FTPES_SecureCommand( FTP_HANDLE hHandle, const char *szLogin, const char *szPassword, const char *szProfile );

//! \brief This function switches the data channel to clear mode.
//! \param hHandle : FTP connection handle.
//! \return
//! - 0 in case of success.
//! - A negative error code otherwise.
int FTPES_UnsecureData( FTP_HANDLE hHandle);

//! \brief This function switches the data channel to secure mode.
//! The command channel must be in secure mode to use this function.
//! \param hHandle : FTP connection handle.
//! \return
//! - 0 in case of success.
//! - A negative error code otherwise.
int FTPES_SecureData( FTP_HANDLE hHandle);

//! \brief This function retrieves the handles on the SSL session and on the SSL 
//! profile used for connection. These handles can then be used to get information about both SSL session and SSL profile.
//! \param hHandle : Current FTP handle.
//! \param hSession : Handle on the SSL session.
//! \param hProfile : Handle on the SSL profile.
//! \return 
//! - 0 in case of success.
//! - A negative error code otherwise.
// \if SIMULATION
//  @GSIM_F:FTPS_GetHandles:KSFAM_FTP:0x19
//  @GSIM_A:1: ONE_ADDRESS
//  @GSIM_A:2: ONE_ADDRESS
//  @GSIM_A:3: ONE_ADDRESS
// \endif
int FTPS_GetHandles( FTP_HANDLE hHandle, SSL_HANDLE *hSession, SSL_PROFILE_HANDLE *hProfile );

//! @}

//! \defgroup FTP_SAMPLE	FTP samples
//! \ingroup TCPIP_SAMPLES
//! \brief  These are examples extracted from the FTP sample project located in the "SDK\Samples\FTP" directory.
//! They are not meant to be compiled as is.
//! @{
//! \defgroup FTP_SAMPLE_RAMDISK	RAM disk monitoring.
//! \ingroup FTP_SAMPLE
//! \brief  The files transferred by FTP are stored in a RAM disk. And, then they can be activated (e.g.
//! copied from the RAMDISK to the permanent Flash memory). This sample shows how to
//! manipulate a RAM disk and how to activate its content.
//! \include FTP__Sample_01.c
//! \example FTP__Sample_01.c
//! @{
//! @}

//! \defgroup FTP_SAMPLE_DONWLOAD	File dowloading.
//! \ingroup FTP_SAMPLE
//! \brief  The following code is adapted from the sample. It performs a simple connection to a FTP
//! server, download a file (logs/foo.txt) and then activate this file.
//!
//! \include FTP__Sample_02.c
//! \example FTP__Sample_02.c
//! @{
//! @}
//! \defgroup FTP_SAMPLE_FILE_LIST	List the files contained in a remote directory.
//! \ingroup FTP_SAMPLE
//! \brief  This sample shows how to list the content of the current remote directory.
//! The names of the files are stored in the array "aFilenames". 
//! The functions returns the number of contained files.
//!
//! \include FTP__Sample_03.c
//! \example FTP__Sample_03.c
//! @{
//! @}

//! @}
//! @}

#ifdef __cplusplus
}
#endif


#endif // __FTP__H__
