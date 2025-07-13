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
   
 Project : GPRS Sample
 Module  : FUN - Functional Demo Unit

 @file      fun_tcp.c
 @brief     Contains all definitions of functions utilized for TCP/IP.
 @date      03/10/2012

 ------------------------------------------------------------------------------
 */

#include "sdk30.h"

#include "utilities.h"
#include "client_ip.h"
#include "err.h"

#ifdef __cplusplus
extern "C" {
#endif

int FUN_TcpIpTransceive( char *host, int port )
{
    int ret;
    int tcpHandle;

    unsigned char* dataToSend = "Test Send";
    char rcvBuf[1024];
    
    trcS("TCP Connecting to Server...\n");
    UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_TCP_CONNECTING);

    tcpHandle = tcp_connect_to_server(host, port, 6000);
    if(tcpHandle >= 0)
    {
        int msgSize = strlen(dataToSend);
        trcS("TCP Connected\n");
        UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_TCP_CONNECTED);

        trcS("TCP Sending...\n");
        UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_TCP_SENDING);

        ret = tcp_send_to_server(tcpHandle, dataToSend, msgSize, 0);
        if( ret == msgSize)
        {
            trcS("TCP Sending OK\n");
            memset(rcvBuf, 0, sizeof(rcvBuf));
            trcS("TCP Receiving...\n");
            UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_TCP_RECEIVING);
            ret = tcp_recv_from_server(tcpHandle, rcvBuf, sizeof(rcvBuf), 1000);
            if(ret >= 0)
            {
                trcS("TCP Receiving OK\n");
            }
            else
            {
                trcS("TCP Receiving KO!\n");
               UI_ErrMsgDisplay(ERR_FUN_TCP_RECEIVE_FAILED);
                ret = ERR_FUN_TCP_RECEIVE_FAILED;
            }
        }
        else
        {
            trcS("TCP Sending KO!\n");
            UI_ErrMsgDisplay(ERR_FUN_TCP_SEND_FAILED);
            ret = ERR_FUN_TCP_SEND_FAILED;
        }

        trcS("TCP Disconnecting...\n");
        UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_TCP_DISCONNECTING);

        tcp_disconnect_from_server(tcpHandle);
        trcS("TCP Disconnected\n");
        UI_PromptMsgDisplay(UI_PROMPT_MSG_STAT_TCP_DISCONNECTED);

    }
    else
    {
        trcS("TCP Connection KO!\n");
        UI_ErrMsgDisplay(ERR_FUN_TCP_CONNECTION_FAILED);
        ret = ERR_FUN_TCP_CONNECTION_FAILED;
    }

    return ret;
}

#ifdef __cplusplus
}
#endif


