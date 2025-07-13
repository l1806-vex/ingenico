//-------------------------------------------------------------------
//
// Copyright (c) 2005 Sagem Monetel SA, rue claude Chappe,
// 07503 Guilherand-Granges, France, All Rights Reserved.
//
// Sagem Monetel SA has intellectual property rights relating
// to the technology embodied in this software.  In particular, 
// and without limitation, these intellectual property rights 
// may include one or more patents.
//
// This software is distributed under licenses restricting 
// its use, copying, distribution, and decompilation.  
// No part of this software may be reproduced in any form 
// by any means without prior written authorization of 
// Sagem Monetel.
//
// Description: Communication utilities module.
//      
// Author:      V.GOMES
// Version:     1.0
// Date:        2005/07/22 
//
//-------------------------------------------------------------------


// Includes
//-------------------------------------------------------------------
#include <SDK30.H>

#include "Communication.h"
#include "UserInterfaceHelpers.h"

#include <IP_.h>
#include <PPP_.h>

// Macros & preprocessor definitions.
//-------------------------------------------------------------------

// Delays.
#define __500_MSECONDS__		50
#define __5_SECONDS__			500
#define __20_SECONDS__			2000
#define __60_SECONDS__			6000

//
#define DATA_MESSAGE_SIZE		1024
#define DEFAULT_HTTP_PORT		80
#define BUFFER_SIZE				1024

#define HTTP_ROOT	"/HOST"
#define PAGE_404 "HTTP/1.0 404" " KO" "\r\n" "\r\n" "The requested URL could not be retreived !\r\n"
#define HTTP_200_HEADER "HTTP/1.0 200" " OK" "\r\n" "\r\n"
#define MAX_PATH (256)
#define MALFORMED_REQUEST "HTTP/1.0 404" " KO" "\r\n" "\r\n" "Malformed HTTP Request\r\n"



// Types.
//-------------------------------------------------------------------
typedef struct
{
	int	received_byte;
	int cr_1;
	int lf_1;
	int cr_2;
	int lf_2;
	char path[MAX_PATH + 1];
	int path_index;
	int path_received;
} automate_s;


// Global variables
//-------------------------------------------------------------------
unsigned int page_counter;
unsigned int byte_counter;
char *last_page_name;


static char *method;
static char last_page_name_buffer[128];

static void init_automate_analyse( automate_s *ptr )
{
	memset( ptr, 0, sizeof( automate_s ));
}


static int automate_analyse( automate_s *ptr, int l, unsigned char *buf )
{
	int end_http_header = 0;
	int i;

	for(i = 0 ; i < l ; i++)
	{
		ptr->received_byte++;
		if(buf[i] == '\r')
		{
			ptr->path_received = 1;
			if(ptr->cr_1)
			{
				ptr->cr_2 = 1;
			}
			else
			{
				ptr->cr_1 = 1;
			}
		}
		else
		{
			if(buf[i] == '\n')
			{
				if(ptr->cr_2)
				{
					ptr->lf_2 = 1;
					end_http_header = 1;
				}
				else
				{
					if(ptr->cr_1)
					{
						ptr->lf_1 = 1;
					}
				}
			}
			else
			{
				ptr->cr_1 = 0;
				ptr->cr_2 = 0;
				ptr->lf_1 = 0;
				ptr->lf_2 = 0;
			}
		}

		if(ptr->path_received == 0)
		{
			ptr->path[ptr->path_index] = buf[i];
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



// Global functions.
//-------------------------------------------------------------------
void PrintNetworkInfos(void)
{
	char szTemp[BUFFER_SIZE];

	char *p;

	unsigned int local_addr = 0;
	unsigned int netmask_addr = 0;

	//
	EthernetGetOption( ETH_IFO_ADDR,    &local_addr	  );	
	EthernetGetOption( ETH_IFO_NETMASK, &netmask_addr );

	//
	p = (char *) &local_addr;
	sprintf( szTemp, "Local Addr: %d.%d.%d.%d\n", (unsigned char)p[0], (unsigned char)p[1], (unsigned char)p[2], (unsigned char)p[3] );
	PrintText( szTemp, 1 );

	p = (char *) &netmask_addr;
	sprintf( szTemp, "Netmask: %d.%d.%d.%d\n", (unsigned char)p[0], (unsigned char)p[1], (unsigned char)p[2], (unsigned char)p[3] );
	PrintText( szTemp, 1 );
}


int LaunchServerHTTP(void)
{
	int	listen_port;
	int	s;
	struct sockaddr_in sock_addr;

	char szTemp[BUFFER_SIZE];			// Printing buffer.

	page_counter = 0;
	byte_counter = 0;

	DisplayScreen( "Launching HTTP Server...", "" );

	listen_port = DEFAULT_HTTP_PORT;

	// Listening socket creation.
	DisplayScreen( "Launching Server...", "Creating listening socket..." );

	s = socket( AF_INET, SOCK_STREAM, 0 );
	if( s == -1 )
	{
		DisplayScreen( "Launching Server...",  "Socket failed." );
		ttestall( 0, __5_SECONDS__ );

		sprintf( szTemp, "Socket failed : %d\n", GetErrno());
		PrintText( szTemp, 1 );

		return -1;
	}

	memset(&sock_addr, 0, sizeof(sock_addr));
	sock_addr.sin_port = htons((unsigned short)listen_port);
	sock_addr.sin_addr.s_addr = INADDR_ANY;
	if( bind( s, (struct sockaddr*)&sock_addr, sizeof( sock_addr )) == -1 )
	{
		sprintf( szTemp, "Bind failed : %d\n", GetErrno());

		closesocket(s);

		DisplayScreen( "Launching Server...",  "Bind failed." );
		ttestall( 0, __5_SECONDS__ );

		PrintText( szTemp, 1 );

		return -2;
	}

	if( listen( s, 8 ) == -1 ) // Accept 8 simultaneous connections.
	{
		sprintf( szTemp, "Listen failed : %d\n", GetErrno());

		closesocket(s);

		DisplayScreen( "Launching Server...",  "Listen failed." );
		ttestall( 0, __5_SECONDS__ );

		PrintText( szTemp, 1 );

		return -3;
	}

	for(;;)
	{
		struct sockaddr_in peer_addr;
		int peer_addr_len = sizeof(peer_addr);
		int transmit_socket;

		DisplayScreen( "Server Ready.",  "Wait for connection..." );

		memset(&peer_addr, 0, peer_addr_len);
		transmit_socket = accept(s, (struct sockaddr*)&peer_addr, &peer_addr_len);
		if( transmit_socket == -1 )
		{
			sprintf( szTemp, "Accept failed : %d\n", GetErrno());

			closesocket(s);

			DisplayScreen( "Server Ready.",  "Accept failed." );
			ttestall( 0, __5_SECONDS__ );

			PrintText( szTemp, 1 );

			return -4;
		}
		else
		{
			unsigned char data_message[DATA_MESSAGE_SIZE];
			automate_s automate;
			init_automate_analyse(&automate);
			page_counter++;

			DisplayScreen( "Server Ready.",  "Accepted connection !" );

			for(;;)
			{
				int l = recv(transmit_socket, data_message, DATA_MESSAGE_SIZE, 0);
				if(l > 0)
				{
					if(automate_analyse(&automate, l, data_message) != 0)
					{
						break;
					}
				}else
				{
					break;
				}
			}
			if( automate.path_received )
			{
				int error = 0;
				char *link = strchr(automate.path, '/');
				char *protocol = strrchr(automate.path, 'H');
				method = automate.path;
				if(link != NULL)
				{
					link[-1] = '\0';
				}
				else
				{
					error = 1;
				}

				if(protocol != NULL)
				{
					protocol[-1] = '\0';
				}
				else
				{
					error = 1;
				}
				if(error == 0)
				{
					char full_path[1024];
					S_FS_FILE *f;
					unsigned int mode;

					FS_mount(HTTP_ROOT, &mode);

					if(link[strlen(link) - 1] == '/')
					{
						sprintf(full_path, "%s%s%s", HTTP_ROOT, link, "INDEX.HTML");
						last_page_name = "/INDEX.HTML";
					}
					else
					{
						sprintf(full_path, "%s%s", HTTP_ROOT, link);
						if(strstr(link, ".HTML") != NULL)
						{
							memset(last_page_name_buffer, 0, sizeof(last_page_name_buffer));
							strcpy(last_page_name_buffer, link);
							last_page_name = last_page_name_buffer;
						}
					}
					f = FS_open(full_path, "r");
					if(f != NULL)
					{
						unsigned char buffer[1024];
						int l;
						send(transmit_socket, HTTP_200_HEADER, strlen(HTTP_200_HEADER), 0);
						for(;;)
						{
							l = FS_read(buffer, 1, sizeof(buffer), f);
							if(l > 0)
							{
								send(transmit_socket, buffer, l, 0);
								byte_counter += (unsigned int)l;
							}
							else
							{
								break;
							}
						}
						FS_close(f);
					}
					else
					{
						send(transmit_socket, PAGE_404, strlen(PAGE_404), 0);
					}
					FS_unmount(HTTP_ROOT);
				}
				else
				{
					send(transmit_socket, MALFORMED_REQUEST, strlen(MALFORMED_REQUEST), 0);
				}
			}

			DisplayScreen( "Server Ready.",  "Close connection." );

			shutdownsocket( transmit_socket, SHUT_RDWR );
			closesocket(transmit_socket);
		}
	}

	return 0;
}


int PerformConnectionHTTP( const char *szHostName, unsigned int nPort, const char *szWebPage ) 
{
    int s;								// Connected socket descriptor.
    struct hostent *hp;					// Pointer to host info for remote host.
    struct sockaddr_in peeraddr_in;     // For peer socket address.
    int i, j;
    fd_set fdMask;						// For call to selectsocket().
    int selected;						// Value returned by selectsocket().
    struct timeval timeout;				// For call to selectsocket().
    int err;

    char buf[BUFFER_SIZE];

	char szTemp[BUFFER_SIZE];			// Printing buffer.

	unsigned int start_time, stop_time;
	unsigned int old_time, new_time;
	unsigned int old_total, new_total;
	struct hostent hostent;

	DisplayScreen( "Connecting HTTP...", "" );

	sprintf( szTemp, "WGET http://%s%s" "\n", szHostName, szWebPage );
	PrintText( szTemp, 1 );

    // Clear out address structure.
    memset ((char *) &peeraddr_in, 0, sizeof (struct sockaddr_in));
    
	// Set up the peer address to which we will connect.
    peeraddr_in.sin_family = AF_INET;

    // Get the host information for the hostname that the
    // user passed in.
    peeraddr_in.sin_addr.s_addr = __inet_addr( szHostName );
    if( peeraddr_in.sin_addr.s_addr == INADDR_NONE )
	{
		DisplayScreen( "Connecting HTTP...", "DNS Resolution" );

		PrintText( "DNS Resolution\n", 1 );

        hp = gethostbyname_r( szHostName, &hostent, buf, sizeof(buf), &err);
        if (hp == NULL)
		{
			sprintf( szTemp, "Unknown host %s\n", szHostName );
			PrintText( szTemp, 1 );
            return ERROR_UNKNOWN_HOST;
        }
		else
		{
            peeraddr_in.sin_addr.s_addr = ((struct in_addr *)(void*) (hp->h_addr))->s_addr;
        }
    }
    peeraddr_in.sin_port = htons(nPort);

	//
	sprintf( szTemp, "Address: %s\n", __inet_ntoa( peeraddr_in.sin_addr ));
	PrintText( szTemp, 1 );

    // Create the socket.

	DisplayScreen( "Connecting HTTP...", "Creating socket." );

    s = socket( AF_INET, SOCK_STREAM, 0 );
    if (s == -1)
	{
		// Error socket creation.
		DisplayScreen( "Connecting HTTP...",  "Socket failed." );
		ttestall( 0, __5_SECONDS__ );

		PrintText( "Error : socket failed\n", 1 );

        return ERROR_SOCKET_FAILED;
    }

	//
	sprintf( szTemp, "Socket: %d\n", s );
	PrintText( szTemp, 1 );

    // Try to connect to the remote server at the address
    // which was just built into peeraddr.
	DisplayScreen( "Connecting HTTP...",  "Connecting server..." );

    if( connect( s, (const struct sockaddr *)&peeraddr_in, sizeof ( struct sockaddr_in )) == -1 )
	{
		// Connection error.
        closesocket (s);

		//
		DisplayScreen( "Connecting HTTP...",  "Connection failed." );
		ttestall( 0, __5_SECONDS__ );

		PrintText( "Error : connect failed\n", 1 );

        return ERROR_CONNECT_FAILED;
    }

	PrintText( "Connected\n", 1 );

	DisplayScreen( "HTTP Connected.",  "Send GET Request." );

    sprintf (buf, "GET %s HTTP/1.0" "\r\n" "HOST: %s" "\r\n\r\n", szWebPage, szHostName);
    if( send ( s, buf, strlen (buf), TCP_NODELAY ) != (int)strlen (buf))
	{
		// Error sending request.

		closesocket (s);

		DisplayScreen( "HTTP Connected.",  "Error Send Request." );
		ttestall( 0, __5_SECONDS__ );
		PrintText( "Error : send failed\n", 1 );

        return ERROR_SEND_FAILED;
    }


    shutdownsocket( s, SHUT_WR );

    start_time = get_tick_counter();
	old_time = start_time;
	old_total = 0;
	i = 0;

    //Wait for a response.
    timeout.tv_sec = 60;
    timeout.tv_usec = 0;
    FD_ZERO (&fdMask);
    FD_SET (s, &fdMask);
    selected = selectsocket( __SELECT_FD_MAX + 1, (fd_set *) & fdMask, (fd_set *) 0, (fd_set *) 0, &timeout );
    if( selected == 0 )
	{
        // Timeout.
		PrintText( "recv() : timeout\n", 1 );
        ttestall (0, 50);
        j = 0;
    }
	else
	{
        j = recv (s, buf, BUFFER_SIZE, 0);
    }

    while (j > 0)
	{
        i += j;

		new_time = get_tick_counter();
		if( new_time - old_time > 100 )
		{
			// More than one second
			new_total = i;

			sprintf( szTemp, "\xF""%d ms : %d B (%d B/S)""\x12""\n",
					10 * (new_time - start_time),
					new_total,
					(100 * (new_total - old_total)) / (new_time - old_time)); // Bytes per Second.
			PrintText( szTemp, 1 );

			old_time = new_time;
			old_total = new_total;
		}

        // Wait for a response.
        timeout.tv_sec = 60;
        timeout.tv_usec = 0;
        FD_ZERO (&fdMask);
        FD_SET (s, &fdMask);
        selected = selectsocket( __SELECT_FD_MAX + 1, (fd_set *) & fdMask, (fd_set *) 0, (fd_set *) 0, &timeout);
        if( selected == 0 )
		{
            // Timeout.
			PrintText( "recv() : timeout\n", 1 );
            ttestall (0, 50);
            j = 0;
        }
		else
		{
            j = recv (s, buf, BUFFER_SIZE, 0);
        }
    }

	stop_time = get_tick_counter();

	DisplayScreen( "HTTP Connected.",  "Close connection..." );
    shutdownsocket( s, SHUT_RD );
    closesocket (s);

	//
	sprintf( szTemp, "Total :" "\n" "\xF" "%d B/ %d S" "\x12" "\n", i, ( stop_time - start_time ) / 100 );
	PrintText( szTemp, 1 );
	ttestall(0, 50);

    return i;
}


