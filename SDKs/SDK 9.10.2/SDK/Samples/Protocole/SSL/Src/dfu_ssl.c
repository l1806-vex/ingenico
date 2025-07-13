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

 @file      dfu_ssl.c
 @brief     Contains all definitions of functions utilized for SSL.
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "sdk30.h"
#include "SSL_.h"
#include "X509_.h"
#include "ssl_profile.h"

#include "utilities.h"
#include "dfu_demofeatures.h"
#include "uiu_userinterface.h"
#include "epu_errprocess.h"

#define _DFU_SSL_TIMEOUT_20_SECONDS             2000 /**< Time out used to connect to SSL server*/

/** Structure used to declare an SSL communication handle.
 */
typedef struct
{
    SSL_HANDLE hdl;/**< SSL handle to be initialized using SSL_New()*/
    SSL_PROFILE_HANDLE profile; /**< SSL profile to be initialized using SSL_LoadProfile()*/
}_DFU_Ssl_ComsChannel_t;

static void _DFU_SslProfilePrint( SSL_PROFILE_HANDLE hProfile );
static int _DFU_SslStart(const char *profile);
static void _DFU_SslStop(void);
static int _DFU_SslConnect(const char *host, unsigned int port);
static void _DFU_SslDisconnect(void);


_DFU_Ssl_ComsChannel_t _DFU_Ssl_comsChannel; /**< SSL Connection test handle */

/** Prints the profile details including the last SSL server to connect. The very last error
 * encountered using the specified profile is also printed.
 *
 * \param[in] hProfile  The SSL profile handle initialized using SSL_LoadProfile() or obtained
 *                      using SSL_GetProfile().
 */
static void _DFU_SslProfilePrint( SSL_PROFILE_HANDLE hProfile )
{
    int iError;
    int iPort;
    int i;
    X509_HANDLE hX509;

    char szTmp[80];
    int szTmpSize = 80;
    char szBuffer[100];

    prtStart();
    if( hProfile == NULL )
    {
        return;
    }

    UIU_PromptMsgDisplay(UIU_PROMPT_MSG_STAT_PRINTING_PROFILE);

    /* Retrieve the name of the specified profile and place it on the trace console.*/
    if( SSL_ProfileGetName( hProfile, szTmp ) == 0 )
    {
        trcS(szTmp);
        trcS("\n");
        printText(szTmp);
    }

    /* Retrieves the last error encountered during an SSL connection.*/
    if( SSL_ProfileGetLastIpServer( hProfile, szTmp, &iPort ) == 0 )
    {
        if(strcmp(szTmp,"")!=0)
        {
            sprintf( szBuffer, "Last connection :\n%s:%d\n", szTmp, iPort );
            trcS( szBuffer);
            printText(szBuffer);
            
            if( SSL_ProfileGetLastError( hProfile, &iError ) == 0 )
            {
                switch( iError )
                {
                    case SSL_PROFILE_OK:
                        sprintf( szBuffer, "Connection OK\n" );
                        break;
                    case SSL_PROFILE_TCP_CONNECT_TIMEOUT:
                        sprintf( szBuffer, "TCP connection timeout\n" );
                        break;
                    case SSL_PROFILE_TCP_CONNECT_FAILED:
                        sprintf( szBuffer, "TCP connection failed\n"  );
                        break;
                    case SSL_PROFILE_TCP_ADDR_NOT_AVAILABLE:
                        sprintf( szBuffer, "Address Not available\n" );
                        break;
                    case SSL_PROFILE_SSL_HANDSHAKE_FAILURE:
                        sprintf( szBuffer, "Not SSL server\n" );
                        break;
                    case SSL_PROFILE_UNABLE_TO_GET_ISSUER_CERT_LOCALLY:
                        sprintf( szBuffer, "Unknown server certificate\n" );
                        break;
                    case SSL_PROFILE_ERROR_IN_CERT_NOT_BEFORE_FIELD:
                        sprintf( szBuffer, "Server certificate not yet valid\n" );
                        break;
                    case SSL_PROFILE_ERROR_IN_CERT_NOT_AFTER_FIELD:
                        sprintf( szBuffer, "Server certificate has expired\n" );
                        break;
                    case SSL_PROFILE_E_SSLV3_ALERT_HANDSHAKE_FAILURE:
                        sprintf( szBuffer, "Server refused connection\n" );
                        break;
                    default:
                        sprintf( szBuffer, "Error: %d\n", iError );
                }
                trcS( szBuffer);
                printText(szBuffer);
                trcS( "\n");
            }
        }
    }

    /* Retrieves the details of the client certificate associated with the profile.*/
    if( SSL_ProfileGetCertificateFile( hProfile, szTmp ) == 0 )
    {
        sprintf( szBuffer, "Client Certificate :\n");
        trcS( szBuffer);
        printText(szBuffer);

        /* Open the certificate file */
        if(( hX509 = X509_Load( szTmp )) != NULL )
        {
            /* Get beginning validity date of certificate */
            if(X509_GetInfo(hX509,X509_NOTBEFORE,0,szTmp,szTmpSize)>0)
            {
                sprintf( szBuffer, "Not Before :\n%s\n",szTmp);
                trcS( szBuffer);
                printText(szBuffer);
            }
            /* Get end validity date of certificate */
            if(X509_GetInfo(hX509,X509_NOTAFTER,0,szTmp,szTmpSize)>0)
            {
                sprintf( szBuffer, "Not After :\n%s\n",szTmp);
                trcS( szBuffer);
                printText(szBuffer);
            }
            /* Unload the certificate file*/
            X509_Unload( hX509 );
        }
        trcS( "\n");
    }

    /* Retrieves the details of all the CA certificate/s associated with the profile.*/
    i = 0;
    while(SSL_ProfileGetCAFile( hProfile, i, szTmp ) == 0)
    {
        sprintf( szBuffer, "Certificate Authority :\n");
        trcS( szBuffer);
        printText(szBuffer);

        if(( hX509 = X509_Load( szTmp )) != NULL )
        {
            /* Get beginning validity date of certificate */
            if(X509_GetInfo(hX509,X509_NOTBEFORE,0,szTmp,szTmpSize)>0)
            {
                sprintf( szBuffer, "Not Before :\n%s\n",szTmp);
                trcS( szBuffer);
                printText(szBuffer);
            }
            /* Get end validity date of certificate */
            if(X509_GetInfo(hX509,X509_NOTAFTER,0,szTmp,szTmpSize)>0)
            {
                sprintf( szBuffer, "Not After :\n%s\n",szTmp);
                trcS( szBuffer);
                printText(szBuffer);
            }
            /* Get issuer information of certificate by NID */
            if(X509_GetInfo(hX509,X509_ISSUER,NID_commonName,szTmp,szTmpSize)>0)
            {
                sprintf( szBuffer, "Issuer %s :\n%s\n",SN_commonName,szTmp);
                trcS( szBuffer);
                printText(szBuffer);
            }
            /* Unload the certificate file*/
            X509_Unload( hX509 );
        }
        trcS("\n");
        i++;
    }
    
    trcS("\n");
    printDocument();
    prtStop();
}

/** Initializes the SSL communication handles.
 *
 * \param[in] profile Pointer to the name of the SSL profile to be used.
 * 
 * \return
 *      -   \ref EPU_RET_OK = Profile has been successfully loaded.
 *      -   \ref EPU_ERR_DFU_SSL_PROFILE_NOT_LOADED = Profile has not been loaded. 
 *          Check the existence of the profile specified.
 */
static int _DFU_SslStart(const char *profile)
{
    int ret = EPU_RET_OK;

    memset(&_DFU_Ssl_comsChannel, 0, sizeof(_DFU_Ssl_comsChannel));
    /* Search for the profile in the terminal and load it*/
    _DFU_Ssl_comsChannel.profile = SSL_LoadProfile(profile);

    if (_DFU_Ssl_comsChannel.profile==NULL)
    {
        ret = EPU_ERR_DFU_SSL_PROFILE_NOT_LOADED;
    }

    return ret;
}

/** Connects to the SSL server identified by \ref host and \ref port.
 *
 * \param[in] host  Pointer to the name of the host to connect to. This can be the
 *                  DNS name or the IP address(e.g. 192.168.2.1).
 * \param[in] port  The port number where the SSL is listening.
 *
 * \return
 *      - \ref EPU_ERR_DFU_SSL_HANDLE_INIT_FAILED = No SSL handle has been initialized.
 *      - \ref EPU_ERR_DFU_SSL_HANDLE_CONNECT_FAILED = Connection to SSL server failed.
 */
static int _DFU_SslConnect(const char *host, unsigned int port)
{
    int ret;

    /* Create an SSL Structure */
    ret = SSL_New(&_DFU_Ssl_comsChannel.hdl, _DFU_Ssl_comsChannel.profile);
    if (ret!=0)
    {
        return EPU_ERR_DFU_SSL_HANDLE_INIT_FAILED;
    }

    /* Connect to the server */
    ret = SSL_Connect(_DFU_Ssl_comsChannel.hdl, host, port, _DFU_SSL_TIMEOUT_20_SECONDS );
    if (ret!=0)
    {
        return EPU_ERR_DFU_SSL_HANDLE_CONNECT_FAILED;
    }

    return ret;
}

/** Disconnects to a previously connected SSL server.
 */
static void _DFU_SslDisconnect(void)
{
    SSL_Disconnect(_DFU_Ssl_comsChannel.hdl);
}

/** Unloads an SSL profile used to connect to a given SSL server and frees
 * the memory used by SSL.
 */
static void _DFU_SslStop(void)
{
    /* Unload the profile and free the ssl handler */
    SSL_UnloadProfile(_DFU_Ssl_comsChannel.profile);
    SSL_Free(_DFU_Ssl_comsChannel.hdl);
}

/** Print and trace  the error from the last connection attempt */
static void _DFU_Ssl_Error(void)
{
    int err;
    
    SSL_ProfileGetLastError(_DFU_Ssl_comsChannel.profile, &err);
    switch (err)
    {
        case SSL_PROFILE_EEXIST:
            trcS("Profile already exist\n");
            printText("Profile already exist\n");
            break;
        case SSL_PROFILE_ENEXIST:
            trcS("Profile does not exist\n");
            printText("Profile does not exist\n");
            break;
        case SSL_PROFILE_ETOOMANY:
            trcS("Too many profile are loaded\n");
            printText("Too many profile are loaded\n");
            break;
        case SSL_PROFILE_ENOMEM:
            trcS("Allocation error\n");
            printText("Allocation error\n");
            break;
        case SSL_PROFILE_ELOADED:
            trcS("Profile already loaded\n");
            printText("Profile already loaded\n");
            break;
        case SSL_PROFILE_ENLOADED:
            trcS("Profile not loaded\n");
            printText("Profile not loaded\n");
            break;
        case SSL_PROFILE_ECAEXIST:
            trcS("ca already exist\n");
            printText("ca already exist\n");
            break;
        case SSL_PROFILE_ECANEXIST:
            trcS("ca does not exist in the profile\n");
            printText("ca does not exist in the profile\n");
            break;
        case SSL_PROFILE_ECATOOMANY:
            trcS("Too many ca in the profile\n");
            printText("Too many ca in the profile\n");
            break;
        case SSL_PROFILE_EPARAM:
            trcS("A parameter is wrong\n");
            printText("A parameter is wrong\n");
            break;
        case SSL_PROFILE_ENOCERT:
            trcS("There is no certificate\n");
            printText("There is no certificate\n");
            break;
        default:
            trcS("Unknown Error\n");
            printText("Unknown Error\n");
            break;
    }

    if (err!=SSL_PROFILE_EOK)
    {
        printDocument();
    }
}

void DFU_SslProfileListPrint(void)
{
    SSL_PROFILE_HANDLE hProfile;
    int i = 0;
    int count;

    /* Obtain the number of profiles loaded in the terminal */
    count = SSL_GetProfileCount();
    if(count == 0)
    {
        UIU_ErrMsgDisplay(EPU_ERR_DFU_SSL_NO_PROFILE_FOUND);
        return;
    }

   /* For each profile, print the certificate details */
    while(( hProfile = SSL_GetProfile( i++ )) != NULL )
    {
        _DFU_SslProfilePrint( hProfile );

        SSL_UnloadProfile( hProfile );
    }
}

char **DFU_SslProfileListConstruct( int *pnNbItems )
{
    int nNbProfiles = 0;
    char **pItems = NULL;
    char *szName = NULL;

    SSL_PROFILE_HANDLE hProfile;
    int i = 0;

    /* Obtain the number of profiles loaded in the terminal */
    nNbProfiles = SSL_GetProfileCount();
    if( nNbProfiles != 0 )
    {
        /* Allocate a memory space big enough for to create a menu containing all of the profiles as menu item*/
        pItems = (char **) umalloc( sizeof(const char*) * (nNbProfiles +1));

        /* Fr each profile in the terminal, add it to the menu char buffer*/
        while(( hProfile = SSL_GetProfile( i )) != NULL )
        {
            szName = (char *) umalloc( PROFILE_NAME_SIZE );

            SSL_ProfileGetName( hProfile, szName );
            pItems[i] = szName;

            SSL_UnloadProfile( hProfile );
            i++;
        }
        pItems[i]=0;
    }
    *pnNbItems = nNbProfiles;
    /* Return the created menu parameter to be displayed for profile selection*/
    return pItems;
}


void DFU_SslProfileAdd(void)
{
    int idx=0;
    int err;
    char szName[80];
    char szBuffer[100];

    SSL_PROFILE_HANDLE hProfile;

    UIU_PromptMsgDisplay(UIU_PROMPT_MSG_STAT_CREATING_PROFILE);
    sprintf( szBuffer, "Creating Profile: %s\n", szName );
    trcS( szBuffer);

    err = SSL_PROFILE_EEXIST;
    /* Search for the profile in the terminal if it already exists,
     * If it already exist increment the profile id and try to create it again */
    while (err==SSL_PROFILE_EEXIST)
    {
        sprintf( szName, "PROFILE_%02d", idx++ );
        hProfile = SSL_NewProfile( szName, &err );
    }

    if( hProfile != NULL )
    {
        SSL_ProfileSetProtocol( hProfile, SSLv3 );
        SSL_ProfileSetCipher( hProfile,
                              SSL_RSA | SSL_DES | SSL_3DES | SSL_RC4 | SSL_RC2 |
                              SSL_MD5 | SSL_SHA1 , SSL_HIGH | SSL_NOT_EXP);

        /* The created profile will use the following certificates in the terminal */
        SSL_ProfileSetKeyFile( hProfile, "/HOST/CLIENT_KEY.PEM", FALSE );
        SSL_ProfileSetCertificateFile( hProfile, "/HOST/CLIENT.CRT" );
        SSL_ProfileAddCertificateCA( hProfile, "/HOST/CA.CRT" );

        /* Save the profile.*/
        SSL_SaveProfile( hProfile );

        /* Tests whether the files linked to the profile are loaded into the terminal.*/
        {
            SSL_HANDLE sslHdl;
            err = SSL_New(&sslHdl, hProfile);
            if(err != 0)
            {
                UIU_ErrMsgDisplay(EPU_ERR_DFU_SSL_CERTS_KEYS_NOT_LOADED);
                UIU_ErrMsgDisplay(EPU_ERR_DFU_SSL_PROFILE_CREATION_FAILED);
                SSL_UnloadProfile( hProfile );
                SSL_DeleteProfile(szName);
                return;
            }
            SSL_Free(sslHdl);
        }
        
        SSL_UnloadProfile( hProfile );

        UIU_PromptMsgDisplay(UIU_PROMPT_MSG_STAT_PROFILE_CREATION_OK);
        trcS( "SUCCESS !!\n");
    }
    else
    {
        UIU_ErrMsgDisplay(EPU_ERR_DFU_SSL_PROFILE_CREATION_FAILED);
        trcS( "ERROR !!\n");
    }
}


int DFU_SslProfileDelete(char *profileName)
{
    int ret;

    /* Search for the profile in the terminal and delete it*/
    ret = SSL_DeleteProfile(profileName);
    if(ret != 0)
    {
        ret = EPU_RET_OK;
    }
    else
    {
        ret = EPU_ERR_DFU_SSL_PROFILE_NOT_FOUND;
    }

    return ret;
}

int DFU_SslConnectionTest( const char *szHostName, unsigned int nPort, const char *szProfile )
{
    int ret = EPU_RET_OK;

    UIU_PromptMsgDisplay(UIU_PROMPT_MSG_STAT_LOADING_SSL_PROFILE);
    ret = _DFU_SslStart(szProfile);
    if(ret>=0)
    {
        UIU_PromptMsgDisplay(UIU_PROMPT_MSG_STAT_CONNECTING_TO_SERVER);
        ret = _DFU_SslConnect(szHostName, nPort);
        if (ret==0)
        {
            UIU_PromptMsgDisplay(UIU_PROMPT_MSG_STAT_CONNECTION_OK);
            
            UIU_PromptMsgDisplay(UIU_PROMPT_MSG_STAT_DISCONNECTING_FROM_SERVER);
            _DFU_SslDisconnect();
        }
        else
        {
            _DFU_Ssl_Error();

            // TODO: Set the proper SSL error code as a result of a connection attempt.
            UIU_ErrMsgDisplay(EPU_ERR_DFU_SSL_CONNECTION_FAILED);
            ret = EPU_ERR_DFU_SSL_CONNECTION_FAILED;
        }

        _DFU_SslStop();
    }
    else
    {
        UIU_ErrMsgDisplay(EPU_ERR_DFU_SSL_PROFILE_NOT_FOUND);
    }

    return ret;
}


#ifdef __cplusplus
}
#endif


