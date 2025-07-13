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
   
 Project : Mifare Sample
 Module  : TRC - Trace Management Unit

 @file      trace.c
 @brief     Contains trace management.
            
 @date      21/03/2013

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "sdk30.h"

#include "par.h"
#include "trc.h"
#include "trace.h"

static void _TRC_OutputStreamSet(enum etrcOutput val);

static TRC_Trace_t trc=NULL;
static TRC_OutputStream_t output=TRC_STREAM_REMOTE_DEBUG;

static void _TRC_OutputStreamSet(enum etrcOutput val)
{
    switch (val)
    {
        case trcOutput_telium:
            output =  TRC_STREAM_TELIUM_TRACE;
            break;

        case trcOutput_internalFile:
            output =  TRC_STREAM_INT_FILE;
            break;

        case trcOutput_externalFileUsb:
            output = TRC_STREAM_EXT_FILE_USB1;
            break;

        case trcOutput_externalFileMmc:
            output =  TRC_STREAM_EXT_FILE_MMC;
            break;

        case trcOutput_printer:
            output = TRC_STREAM_PRINTER;
            break;

        case trcOutput_udpIp:
            output = TRC_STREAM_UDP_IP;
            break;

        case trcOutput_remoteDbg:
        default:
            output = TRC_STREAM_REMOTE_DEBUG;
            break;
    }
}

void TRC_Init(void)
{
    int ret;
    enum etrcOutput  data;

    ret = PAR_TrcOutputGet(&data);
    if (ret!=PAR_OK)
    {
        data = trcOutput_remoteDbg;
    }
    _TRC_OutputStreamSet(data);

    if (trc!=NULL)
    {
        TRC_Destroy(trc);
        trc = NULL;
    }

    TRC_Create(0, &trc, "MIFARE");
    TRC_OutputSet(0, 0, 0, 0, 0);

    switch (output)
    {
        case TRC_STREAM_TELIUM_TRACE:
            TRC_OutputSet(output, 0, 0, 0, 0x2001);
            break;

        case TRC_STREAM_INT_FILE:
            TRC_OutputSet(output, "/HOST/MIFARE.TXT", 0, 0, 0);
            break;

        case TRC_STREAM_EXT_FILE_USB1:
            TRC_OutputSet(output, "/USB1/MIFARE.TXT", 0, 0, 0);
            break;

        case TRC_STREAM_EXT_FILE_MMC:
            TRC_OutputSet(output, "/MMC/MIFARE.TXT", 0, 0, 0);
            break;

        case TRC_STREAM_UDP_IP:
            TRC_OutputSet(output, 0, "10.17.32.10", 5000, 0);
            break;

        case TRC_STREAM_PRINTER:
        case TRC_STREAM_REMOTE_DEBUG:
        default:
            TRC_OutputSet(output, 0, 0, 0, 0);
            break;
    }

    TRC_LevelFilterSet(TRC_FILTER_ALL);
}

TRC_Trace_t TRC_HandleGet(void)
{
    return trc;
}

#ifdef __cplusplus
}
#endif


