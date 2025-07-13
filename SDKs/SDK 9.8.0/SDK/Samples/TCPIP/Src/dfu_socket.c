/**+
 *  PROJECT         :   TCP/IP Sample
 *  MODULE          :   Demo Features Unit
 *  FILEMANE        :   dfu.c
 *  PURPOSE         :   Definitions of DFU functions
 *
 *  DESCRIPTION     :   Contains all definitions of functions that demonstrates
 *                      the use of certain features specific to the sample 
 *                      application.
 *
 *  Copyright (c) 2012 Ingenico. All Rights Reserved.
 *
 *  Ingenico has intellectual property rights relating to the technology 
 *  embodied in this software.  In particular, and without limitation, 
 *  these intellectual property rights may include one or more patents.
 *
 *  This software is distributed under licenses restricting its use, 
 *  copying, distribution, and decompilation. No part of this software may be 
 *  reproduced in any form by any means without prior written authorization of 
 *  Ingenico.
 *
 * 
 *  HISTORY         :
 *
 *  Author:          V.GOMES
 *  Modification:    Creation
 *  Date:            2005/07/22
 *
 *  Author:          Ingenico R&D Philippines Team
 *  Modification:    Refurbishments
 *  Date:            2012/09/17
-*/

#include <SDK30.H>
#include <IP_.h>
#include <GL_GraphicLib.h>

#include "Utilities.h"
#include "dfu_demofeatures.h"
#include "uiu_userinterface.h"
#include "epu_errprocess.h"

#define DATA_MESSAGE_SIZE		1024
#define DEFAULT_HTTP_PORT		80
#define BUFFER_SIZE				1024

#define HTTP_ROOT	"/HOST"
#define PAGE_404 "HTTP/1.0 404" " KO" "\r\n" "\r\n" "The requested URL could not be retreived !\r\n"
#define HTTP_200_HEADER "HTTP/1.0 200" " OK" "\r\n" "\r\n"
#define MAX_PATH (256)
#define MALFORMED_REQUEST "HTTP/1.0 404" " KO" "\r\n" "\r\n" "Malformed HTTP Request\r\n"

typedef struct
{
    int received_byte;
    int cr_1;
    int lf_1;
    int cr_2;
    int lf_2;
    char path[MAX_PATH + 1];
    int path_index;
    int path_received;
} automate_s;

typedef struct sComsChannel {
    int hdlSck;	//socket
    int transmit_sck; //transmit socket
    int max_sck; //upper limit socket descriptor
    struct sockaddr_in sck_addr; // socket address.	
    struct sockaddr_in peer_addr; // peer socket address.
} DFU_ComsChannel_t;

static DFU_ComsChannel_t com;

unsigned int page_counter;
unsigned int byte_counter;
char *last_page_name;

static char *method;
static char last_page_name_buffer[128];

static int _DFU_ComHttpReqMsgHeaderCheck(automate_s *ptr, int len, unsigned char *buf);
static int _DFU_ComStart(void) ;
static int _DFU_ComSetServer(unsigned int addr, unsigned short port, unsigned char family);
static int _DFU_ComSetClient(unsigned int addr, unsigned short port, unsigned char family);
static int _DFU_ComConnect(void);
static int _DFU_ComWait(void);
static int _DFU_ComSocketSelect(fd_set *read, struct timeval *delay);
static int _DFU_ComSend(int sck, unsigned char *buf, int len);
static int _DFU_ComReceive(int sck, unsigned char *buf, int len);
static void _DFU_ComStop(int sck, int type);
static int _DFU_ComHttpMsgSend(automate_s *ptr, int sck);


/** Checks the received message whether it contains the required header carriage returns
 *  and line feeds. The header should contain the character sequences "\r\n\r\n"
 */
static int _DFU_ComHttpReqMsgHeaderCheck(automate_s *ptr, int len, unsigned char *buf)
{
    int end_http_header = 0;
    int ctr;
    
    for(ctr = 0 ; ctr < len ; ctr++)
    {
        ptr->received_byte++;
        if(buf[ctr] == '\r')
        {
            ptr->path_received = 1;
            if(ptr->cr_1)
            {
                ptr->cr_2 = 1; //Second carriage return '\r' character has been detected. The line feed character should follow.
            }
            else
            {
                ptr->cr_1 = 1; //First carriage return '\r' character has been detected. The line feed '\n' should follow.
            }
        }
        else
        {
            if(buf[ctr] == '\n') // Linefeed '\n' character has been detected after a '\r' character.
            {
                 if(ptr->cr_2) // Checks if it is the line feed after a second carriage return character.
                 {
                     ptr->lf_2 = 1;
                     end_http_header = 1;
                 }
                 else // Line feed detected after the first carriage return character.
                 {
                     if(ptr->cr_1)
                     {
                         ptr->lf_1 = 1;
                     }
                 }
            }
            else // Otherwise, no valid header terminating characters has been detected.
            {
                ptr->cr_1 = 0;
                ptr->cr_2 = 0;
                ptr->lf_1 = 0;
                ptr->lf_2 = 0;
            }
        }
        
        if(ptr->path_received == 0)
        {
             ptr->path[ptr->path_index] = buf[ctr];
             if(ptr->path_index == MAX_PATH)
             {
                 ptr->path_received = 1;
             }
             else
             {
                 ptr->path_index++;
             }
        }
    }
    
    return end_http_header;
}


/** Instantiate a socket.
 */
static int _DFU_ComStart(void) 
{
    int ret=1;

    trcS("DFU_ComStart\n");
    memset(&com, 0, sizeof(com));
    com.hdlSck = socket(AF_INET, SOCK_STREAM, 0);
    if (com.hdlSck < 0)
    {
        ret = -1;
    }
    return ret;
}

/** Initialize the socket descriptor parameters of the server. This descriptor will be 
 *  used for the function call bind().
 *
 * \param (I) addr      IP address of the server.
 * \param (I) port      Port number to listen to.
 * \param (I) family    AF_INET
 *
 */
static int _DFU_ComSetServer(unsigned int addr, unsigned short port, unsigned char family)
{
    int ret=1;
    char buf[BUFFER_SIZE];

    trcS("DFU_ComSetServer\n");

    com.sck_addr.sin_addr.s_addr = addr;
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "Address: %s\n", __inet_ntoa(com.sck_addr.sin_addr));
    trcS( buf );

    memset(&com.sck_addr, 0, sizeof(com.sck_addr));
    if (port != 0)
    {
        trcFN("Port: %d\n", port);
        com.sck_addr.sin_port = htons(port);
    }

    if (family !=0)
    {
        com.sck_addr.sin_family = family;
    }

    return ret;
}

/** Initialize the socket descriptor parameters of the client. This descriptor will be 
 *  used for the function call connect().
 *
 * \param (I) addr      IP address of the server.
 * \param (I) port      Port number to listen to.
 * \param (I) family    AF_INET
 *
 */
static int _DFU_ComSetClient(unsigned int addr, unsigned short port, unsigned char family)
{
    int ret=1;
    char buf[BUFFER_SIZE];

    trcS("DFU_ComSetClient\n");
    memset(&com.peer_addr, 0, sizeof(com.peer_addr));
    if (port != 0)
    {
        trcFN("Port: %d\n", port);
        com.peer_addr.sin_port = htons(port);
    }
    if (addr !=0)
    {
        com.peer_addr.sin_addr.s_addr = addr;
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "Address: %s\n", __inet_ntoa(com.peer_addr.sin_addr));
        trcS( buf );
    }
    if (family !=0)
    {
        com.peer_addr.sin_family = family;
    }

    return ret;
}

/** Connects to a server. Note that before calling this function, _DFU_ComSetClient() has been
 * called.
 */
static int _DFU_ComConnect(void)
{
    int ret;

    trcS("DFU_ComConnect\n");
    ret = connect(com.hdlSck, (const struct sockaddr *)&com.peer_addr, sizeof(struct sockaddr_in));
    if (ret == -1)// If connection to the server failed, socket handle will be closed.
    {
        closesocket(com.hdlSck);
    }

    return ret;	
}

/** Awaits incoming connections. This function can only be called when socket binding has been
 * successful and the listening parameters has been successfully set.
 */
static int _DFU_ComWait(void)
{
    int ret;
    int len;

    trcS("DFU_ComWait\n");
    len = sizeof(com.peer_addr);
    memset(&com.peer_addr, 0, len);

    //com.transmit_sck = accept(com.hdlSck, (struct sockaddr*)&com.peer_addr, &len);
    com.transmit_sck = accept(com.hdlSck, (struct sockaddr*)&com.peer_addr, &len);
    ret = com.transmit_sck;
    return ret;
}

/** Waits for the change in status of a given socket designated to read data from.
 * It waits until the given delay. It returns when waiting has timeout or data is available to
 * be read from the socket.
 */
static int _DFU_ComSocketSelect(fd_set *read, struct timeval *delay)
{
    int ret;

    trcS("DFU_ComSelectSocket\n");
    //ret = selectsocket( __SELECT_FD_MAX + 1, read, 0, 0, delay);
    ret = selectsocket( com.max_sck + 1, read, 0, 0, delay);
    if(ret == 0)
    {
        // Timeout.
        trcS( "recv() : timeout\n" );
    }

    return ret;
}

/** Sends data via a given socket.
 */
static int _DFU_ComSend(int sck, unsigned char *buf, int len)
{
    int ret;

    ret = send(sck, buf, len, 0);
    trcS("Sent: ");
    trcBAN(buf, len);
    trcS("\n");
    trcAN(buf, ret);
    trcS("\n");

    return ret;
}

/** Receives messages in a given socket.
 */
static int _DFU_ComReceive(int sck, unsigned char *buf, int len)
{
    int ret;

    ret = recv(sck, buf, len, 0);
    trcS("Received: ");
    trcBN(buf, ret);
    trcS("\n");
    trcAN(buf, ret);
    trcS("\n");

    return ret;
}

/** Shuts down and closes a given socket.
 */
static void _DFU_ComStop(int sck, int type)
{
    trcS("DFU_ComStop\n");
    
    shutdownsocket(sck, type);
    closesocket(sck);
}

/** Sends an http response message via the socket. Based on the HTTP
 * request message, it will extract the path of the HTML page to be sent.
 * It performs a look-up of the HTML page located in the HOST directory of the 
 * terminal and sends the content to the client. If the HTML page is not
 * found, it sends an HTTP error response message to the client specifying that
 * the requested page was not found. If the HTTP request message sent by the 
 * client is an invalid request, it will send an HTTP error response message that
 * the request messsage received is invalid or malformed.
 *
 * \param (I) ptr   Pointer to the request message analyzed earlier. It is where
 *                  the URL path is obtained and then the path is looked up in the
 *                  file system of the terminal.
 * \param[in] sck   Socket handle of the client request.
 * \return
 *      - Status of sending.
 */
static int _DFU_ComHttpMsgSend(automate_s *ptr, int sck)
{
    int ret;
    int error = 0;
    char *link = strchr(ptr->path, '/');
    char *protocol = strrchr(ptr->path, 'H');
    
    method = ptr->path;
    if (link != NULL)
    {
        link[-1] = '\0';
    }
    else
    {
        error = 1;
    }
    
    if (protocol != NULL)
    {
        protocol[-1] = '\0';
    }
    else
    {
        error = 1;
    }
    
    if (error == 0)
    {
        char full_path[1024];
        S_FS_FILE *fname;
        unsigned int mode;
        
        FS_mount(HTTP_ROOT, &mode);
        
        if (link[strlen(link) - 1] == '/')
        {
            sprintf(full_path, "%s%s%s", HTTP_ROOT, link, "INDEX.HTML");
            last_page_name = "/INDEX.HTML";
        }
        else
        {
            sprintf(full_path, "%s%s", HTTP_ROOT, link);
            if (strstr(link, ".HTML") != NULL)
            {
                memset(last_page_name_buffer, 0, sizeof(last_page_name_buffer));
                strcpy(last_page_name_buffer, link);
                last_page_name = last_page_name_buffer;
            }
        }

        fname = FS_open(full_path, "r");
        if (fname != NULL)
        {
            unsigned char buffer[1024];
            int len;
            
            ret = _DFU_ComSend(sck, HTTP_200_HEADER, strlen(HTTP_200_HEADER));
            while (1)
            {
                len = FS_read(buffer, 1, sizeof(buffer), fname);
                if (len > 0)
                {
                    ret = _DFU_ComSend(sck, buffer, len);
                    byte_counter += (unsigned int)len;
                }
                else
                {
                    break;
                }
            }
            FS_close(fname);
        }
        else
        {
            ret = _DFU_ComSend(sck, PAGE_404, strlen(PAGE_404));
        }
        FS_unmount(HTTP_ROOT);
    }
    else
    {
        ret = _DFU_ComSend(sck, MALFORMED_REQUEST, strlen(MALFORMED_REQUEST));
    }
    return ret;
}

/** Retrieves and displays the terminal IP parameters of the terminal.
 */
void DFU_ComNetInfoDisplay(void)
{
    char szTemp[BUFFER_SIZE];
    char *p;
    unsigned int local_addr = 0;
    unsigned int netmask_addr = 0;
    
    // Retrieves the network parameters of the terminal
    EthernetGetOption( ETH_IFO_ADDR,    &local_addr	  );
    EthernetGetOption( ETH_IFO_NETMASK, &netmask_addr );
    
    // Converts the IP address for display
    p = (char *) &local_addr;
    sprintf( szTemp, "Local Addr: %d.%d.%d.%d\n", (unsigned char)p[0], (unsigned char)p[1], (unsigned char)p[2], (unsigned char)p[3] );
    trcS( szTemp );
    guiScreen("Local Address", szTemp, GL_ICON_INFORMATION, UIU_TIMEOUT_3_SECONDS);

    // Converts the subnet mask for display
    p = (char *) &netmask_addr;
    sprintf( szTemp, "Netmask: %d.%d.%d.%d\n", (unsigned char)p[0], (unsigned char)p[1], (unsigned char)p[2], (unsigned char)p[3] );
    trcS( szTemp );
    guiScreen("Netmask", szTemp, GL_ICON_INFORMATION, UIU_TIMEOUT_3_SECONDS);
}

/** Instantiate a server to accept incoming connections.
 */
int DFU_ComServerStart(void)
{
    int ret;
    unsigned int addr;
    unsigned short port;
    unsigned char buf[DATA_MESSAGE_SIZE];
    automate_s automate;
    int    i, len, on = 1;
    int    max_sd;
    int    desc_ready, end_server = FALSE;
    int    close_conn;

    fd_set masterSet;
    fd_set workingSet;
    struct timeval timeout;

    page_counter = 0;
    byte_counter = 0;
    
    UIU_PromptDisplay(UIU_PROMPT_MSG_SERVER_TEST_LAUNCH);
    UIU_PromptDisplay(UIU_PROMPT_MSG_SERVER_TEST_CREATING_SOCKET);

    ret = _DFU_ComStart();
    if (ret == -1)
    {
        UIU_ErrMsgDisplay(EPU_ERR_SERVER_TEST_SOCKET_FAILED);
        return EPU_ERR_SERVER_TEST_SOCKET_FAILED;
    }

   /*************************************************************/
   /* Allow socket descriptor to be reuseable                   */
   /*************************************************************/
   ret = setsockopt(com.hdlSck, SOL_SOCKET,  SO_REUSEADDR,
                   (char *)&on, sizeof(on));
   if (ret < 0)
   {
      closesocket(com.hdlSck);
      UIU_ErrMsgDisplay(EPU_ERR_SERVER_TEST_SOCKET_FAILED);
      return EPU_ERR_SERVER_TEST_SOCKET_FAILED;
   }

   /*************************************************************/
   /* Set socket to be non-blocking.  All of the sockets for    */
   /* the incoming connections will also be non-blocking since  */
   /* they will inherit that state from the listening socket.   */
   /*************************************************************/
   ret = ioctlsocket(com.hdlSck, FIONBIO, &on);
   if (ret < 0)
   {
      closesocket(com.hdlSck);
      UIU_ErrMsgDisplay(EPU_ERR_SERVER_TEST_SOCKET_FAILED);
      return EPU_ERR_SERVER_TEST_SOCKET_FAILED;
   }

   /*************************************************************/
   /* Bind the socket                                           */
   /*************************************************************/
   memset(&addr, 0, sizeof(addr));
   addr =INADDR_ANY;
    port = DEFAULT_HTTP_PORT;
   _DFU_ComSetServer(addr, port, 0);
   ret = bind(com.hdlSck,
             (struct sockaddr *)&com.sck_addr, sizeof(com.sck_addr));
   if (ret < 0)
   {
        closesocket(com.hdlSck);
        UIU_ErrMsgDisplay(EPU_ERR_SERVER_TEST_BINDING_FAILED);
        return EPU_ERR_SERVER_TEST_BINDING_FAILED;
   }

    /*************************************************************/
    /* Set the listen back log                                   */
    /*************************************************************/
    ret = listen(com.hdlSck, 8);// Accept 8 simultaneous requests.
    if (ret < 0)
    {
        closesocket(com.hdlSck);
        UIU_ErrMsgDisplay(EPU_ERR_SERVER_TEST_LISTEN_FAILED);
        return EPU_ERR_SERVER_TEST_LISTEN_FAILED;
    }

    /*************************************************************/
    /* Initialize the master fd_set                              */
    /*************************************************************/
    FD_ZERO(&masterSet);
    com.max_sck = com.hdlSck;
    FD_SET(com.hdlSck, &masterSet);

    /*************************************************************/
    /* Initialize the timeval struct to 60 seconds.  If no        */
    /* activity after 60 seconds this function will end.           */
    /*************************************************************/
    timeout.tv_sec  = 60;
    timeout.tv_usec = 0;

    /*************************************************************/
    /* Loop waiting for incoming connects or for incoming data   */
    /* on any of the connected sockets.                          */
    /*************************************************************/
    do
    {
        /**********************************************************/
        /* Copy the master fd_set over to the working fd_set.     */
        /**********************************************************/
        memcpy(&workingSet, &masterSet, sizeof(masterSet));

        UIU_PromptDisplay(UIU_PROMPT_MSG_SERVER_TEST_LISTENING);

        /**********************************************************/
        /* Call select() and wait 5 minutes for it to complete.   */
        /**********************************************************/
        ret = _DFU_ComSocketSelect((fd_set *) &workingSet, &timeout);

        /**********************************************************/
        /* Check to see if the select call failed.                */
        /**********************************************************/
        if (ret < 0)
        {
            break;
        }

        /**********************************************************/
        /* Check to see if the 5 minute time out expired.         */
        /**********************************************************/
        if (ret == 0)
        {
            break;
        }

        /**********************************************************/
        /* One or more descriptors are readable.  Need to         */
        /* determine which ones they are.                         */
        /**********************************************************/
        desc_ready = ret;
        for (i=0; i <= com.max_sck  &&  desc_ready > 0; ++i)
        {
            /*******************************************************/
            /* Check to see if this descriptor is ready            */
            /*******************************************************/
            if (FD_ISSET(i, &workingSet))
            {
                /****************************************************/
                /* A descriptor was found that was readable - one   */
                /* less has to be looked for.  This is being done   */
                /* so that we can stop looking at the working set   */
                /* once we have found all of the descriptors that   */
                /* were ready.                                      */
                /****************************************************/
                desc_ready -= 1;

                /****************************************************/
                /* Check to see if this is the listening socket     */
                /****************************************************/
                if (i == com.hdlSck)
                {
                    /*************************************************/
                    /* Accept all incoming connections that are      */
                    /* queued up on the listening socket before we   */
                    /* loop back and call select again.              */
                    /*************************************************/
                    do
                    {
                        /**********************************************/
                        /* Accept each incoming connection.  If       */
                        /* accept fails with EWOULDBLOCK, then we     */
                        /* have accepted all of them.  Any other      */
                        /* failure on accept will cause us to end the */
                        /* server.                                    */
                        /**********************************************/
                        ret = _DFU_ComWait();
                        if (ret < 0)
                        {
                            if (GetErrno()!= __EWOULDBLOCK)
                            {
                                UIU_ErrMsgDisplay(EPU_ERR_SERVER_TEST_ACCEPT_FAILED);
                                end_server = TRUE;
                            }
                            break;
                        }
                        UIU_PromptDisplay(UIU_PROMPT_MSG_SERVER_TEST_CONNECTION_ACCEPTED);
                        /**********************************************/
                        /* Add the new incoming connection to the     */
                        /* master read set                            */
                        /**********************************************/
                        FD_SET(com.transmit_sck, &masterSet);
                        if (com.transmit_sck > com.max_sck)
                            com.max_sck= com.transmit_sck;

                        /**********************************************/
                        /* Loop back up and accept another incoming   */
                        /* connection                                 */
                        /**********************************************/
                    } while (com.transmit_sck != -1);
                }

                /****************************************************/
                /* This is not the listening socket, therefore an   */
                /* existing connection must be readable             */
                /****************************************************/
                else
                {
                    close_conn = FALSE;
                    /*************************************************/
                    /* Receive all incoming data on this socket      */
                    /* before we loop back and call select again.    */
                    /*************************************************/
                    UIU_PromptDisplay(UIU_PROMPT_MSG_SERVER_TEST_RECEIVING);
                    memset(buf, 0, sizeof(buf));
                    memset(&automate, 0, sizeof(automate));
                    page_counter++;
                    do
                    {
                        /**********************************************/
                        /* Receive data on this connection until the  */
                        /* recv fails with EWOULDBLOCK.  If any other */
                        /* failure occurs, we will close the          */
                        /* connection.                                */
                        /**********************************************/
                        ret = _DFU_ComReceive(i, buf, sizeof(buf));
                        if (ret < 0)
                        {
                            if (GetErrno() != __EWOULDBLOCK)
                            {
                                close_conn = TRUE;
                            }
                            break;
                        }

                        /**********************************************/
                        /* Check to see if the connection has been    */
                        /* closed by the client                       */
                        /**********************************************/
                        if (ret == 0)
                        {
                            close_conn = TRUE;
                            break;
                        }

                        /**********************************************/
                        /* Data was recevied                          */
                        /**********************************************/
                        len = ret;

                        UIU_PromptDisplay(UIU_PROMPT_MSG_SERVER_TEST_SENDING);

                        /**********************************************/
                        /* Check Request!                             */
                        /**********************************************/
                        _DFU_ComHttpReqMsgHeaderCheck(&automate, ret, buf);
                        ret = _DFU_ComHttpMsgSend(&automate, i); // Close connection when sending fails.
                        if (ret < 0)
                        {
                            close_conn = TRUE;
                            break;
                        }
                    } while (TRUE);

                    /*************************************************/
                    /* If the close_conn flag was turned on, we need */
                    /* to clean up this active connection.  This     */
                    /* clean up process includes removing the        */
                    /* descriptor from the master set and            */
                    /* determining the new maximum descriptor value  */
                    /* based on the bits that are still turned on in */
                    /* the master set.                               */
                    /*************************************************/
                    if (close_conn)
                    {
                        closesocket(i);
                        FD_CLR(i, &masterSet);
                        if (i == com.max_sck)
                        {
                            while (FD_ISSET(com.max_sck, &masterSet) == FALSE)
                                com.max_sck -= 1;
                        }
                    }
                } /* End of existing connection is readable */
            } /* End of if (FD_ISSET(i, &working_set)) */
        } /* End of loop through selectable descriptors */
    } while (end_server == FALSE);

    UIU_PromptDisplay(UIU_PROMPT_MSG_SHUTTING_CONNECTION);
    /*************************************************************/
    /* Cleanup all of the sockets that are open                  */
    /*************************************************************/
    for (i=0; i <= max_sd; ++i)
    {
        if (FD_ISSET(i, &masterSet))
        closesocket(i);
    }

    UIU_PromptDisplay(UIU_PROMPT_MSG_TEST_OK);
    return 0;
}

/** Instantiates a communication channel to connect to a given server.
 * Sends a simple HTTP request message and waits for a response from the
 * server.
 */
int DFU_ComClientConnect(const char *host, unsigned int port, const char *trm) 
{
    int ret;
    int ctr;
    int dataLen;
    int err;
    unsigned int addr;
    unsigned char family;
    unsigned int start_time, stop_time;
    unsigned int old_time, new_time;
    unsigned int old_total, new_total;	
    char buf[BUFFER_SIZE];
    
    fd_set fdMask;// For call to selectsocket().
    struct hostent *hp;// Pointer to host info for remote host.
    struct timeval timeout;// For call to selectsocket().
    struct hostent hostent;

    UIU_PromptDisplay(UIU_PROMPT_MSG_CLIENT_TEST_LAUNCH);

    sprintf(buf, "WGET http://%s%s" "\n", host, trm);
    trcS(buf);
    
    // Create the socket.
    UIU_PromptDisplay(UIU_PROMPT_MSG_CLIENT_TEST_CREATING_SOCKET);
    ret = _DFU_ComStart();
    if (ret == -1)
    {
        UIU_ErrMsgDisplay(EPU_ERR_CLIENT_TEST_SOCKET_FAILED);
        return EPU_ERR_CLIENT_TEST_SOCKET_FAILED;
    }
    
    sprintf(buf, "Socket: %d\n", com.hdlSck);
    trcS(buf);

    /** Initialize the socket setting the host address to connect to and
     * the address family(TCP, UDP, etc...)
     */ 
    addr = __inet_addr(host);
    family = AF_INET;
    
    _DFU_ComSetClient(addr, port, family);
    if (com.peer_addr.sin_addr.s_addr == INADDR_NONE)
    {
        UIU_PromptDisplay(UIU_PROMPT_MSG_CON_STATUS_RESOLVING_DNS);
        trcS( "DNS Resolution\n" );
        
        hp = gethostbyname_r(host, &hostent, buf, sizeof(buf), &err);
        if (hp == NULL)
        {
            // TODO: Create an error message prompt for Unknown host error.
            sprintf(buf, "Unknown host %s\n", host);
            trcS(buf);
            return EPU_ERR_CLIENT_TEST_UNKNOWN_HOST;
        }
        else
        {
            com.peer_addr.sin_addr.s_addr = ((struct in_addr *)(void*) (hp->h_addr))->s_addr;
        }
    }

    // Connect to the server.
    UIU_PromptDisplay(UIU_PROMPT_MSG_CON_STATUS_CONNECTING);
    ret = _DFU_ComConnect();
    if( ret == -1 )
    {
        // Connection to server failed.
        UIU_ErrMsgDisplay(EPU_ERR_CLIENT_TEST_CONNECTION_FAILED);
        return EPU_ERR_CLIENT_TEST_CONNECTION_FAILED;
    }

    // Sends HTTP Get Request
    trcS( "Connected\n" );
    UIU_PromptDisplay(UIU_PROMPT_MSG_CLIENT_TEST_SENDING);
    
    sprintf (buf, "GET %s HTTP/1.0" "\r\n" "HOST: %s" "\r\n\r\n", trm, host);// Prepares the HTTP Request Message
    ret = _DFU_ComSend(com.hdlSck, buf, strlen(buf));
    if(ret != (int)strlen(buf))
    {
        // Error sending request.
        closesocket (com.hdlSck);
        UIU_PromptDisplay(UIU_PROMPT_MSG_CLIENT_TEST_SEND_FAILED);
        return EPU_ERR_CLIENT_TEST_SEND_FAILED;
    }

    start_time = get_tick_counter();
    old_time = start_time;
    old_total = 0;
    ctr = 0;
    
    //Wait for a response.
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;
    FD_ZERO(&fdMask);
    FD_SET(com.hdlSck, &fdMask);

    UIU_PromptDisplay(UIU_PROMPT_MSG_CLIENT_TEST_RECEIVING);
    ret = _DFU_ComSocketSelect((fd_set *) &fdMask, &timeout);
    if (ret == 0)// There was no activity on the scoket. No response from the host
    {
        dataLen = 0;
    }
    else
    {
        dataLen = _DFU_ComReceive(com.hdlSck, buf, sizeof(buf));
    }

    // Continue receiving the response message until all data has been obtained from the socket
    while (dataLen > 0)
    {
        ctr+=dataLen;
        
        new_time = get_tick_counter();
        if( new_time - old_time > 100 )
        {
            // More than one second
            new_total = ctr;
            
            sprintf(buf, "\xF""%d ms : %d B (%d B/S)""\x12""\n",
                10 * (new_time - start_time),
                 new_total,
                (100 * (new_total - old_total)) / (new_time - old_time)); // Bytes per Second.
            trcS(buf);
            
            old_time = new_time;
            old_total = new_total;
        }
        
        // Wait for a response.
        timeout.tv_sec = 60;
        timeout.tv_usec = 0;
        FD_ZERO (&fdMask);
        FD_SET (com.hdlSck, &fdMask);

        UIU_PromptDisplay(UIU_PROMPT_MSG_CLIENT_TEST_RECEIVING);
        ret = _DFU_ComSocketSelect((fd_set *) &fdMask, &timeout);
        if (ret == 0)
        {
            // Timeout.
            dataLen = 0;
        }
        else
        {
            dataLen = _DFU_ComReceive(com.hdlSck, buf, sizeof(buf));
        }
    }
    
    stop_time = get_tick_counter();
    
    UIU_PromptDisplay(UIU_PROMPT_MSG_SHUTTING_CONNECTION);
    _DFU_ComStop(com.hdlSck, SHUT_RD);
    
    sprintf(buf, "Total :" "\n" "\xF" "%d B/ %d S" "\x12" "\n", ctr, ((stop_time - start_time )/100));
    trcS(buf);

    UIU_PromptDisplay(UIU_PROMPT_MSG_TEST_OK);
    return ctr;
}

