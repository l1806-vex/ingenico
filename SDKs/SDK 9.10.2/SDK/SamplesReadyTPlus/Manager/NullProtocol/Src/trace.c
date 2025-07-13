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
   
 Project : Card Entry Sample
 Module  : TRC - Trace Management Unit

 @file      trace.c
 @brief     Contains trace management.
            
 @date      03/05/2013

 ------------------------------------------------------------------------------
 */

#ifdef __cplusplus
extern "C" {
#endif


#include "sdk30.h"

#include "trc.h"

static TRC_Trace_t trc=NULL;

void TRC_Init(void)
{
    TRC_Create(0, &trc, "NULLPROT");
    TRC_OutputSet(TRC_STREAM_REMOTE_DEBUG, 0, 0, 0, 0);
    TRC_LevelFilterSet(TRC_FILTER_ALL);
}

TRC_Trace_t TRC_HandleGet(void)
{
    return trc;
}

#ifdef __cplusplus
}
#endif


