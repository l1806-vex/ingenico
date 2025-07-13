/***
 * Copyright (c) 2001 Ascom Monetel SA, rue claude Chappe,
 * 07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * Ascom Monetel SA has intellectual property rights relating
 * to the technology embodied in this software.  In particular, 
 * and without limitation, these intellectual property rights 
 * may include one or more patents.
 *
 * This software is distributed under licenses restricting 
 * its use, copying, distribution, and decompilation.  
 * No part of this software may be reproduced in any form 
 * by any means without prior written authorization of 
 * Ascom Monetel.
 *
 * Title:        getprocadr.c
 * Description:  API for standard C DLL
 * Reference:    ANSI X9.30
 * Comment:
 *       
 * @author:      D. TESTU
 * @version:     1.0
 * @date:        02/2001 
 * @since:
 * @tools:       Arm Developer Suite 1.1 (if need)
 * @processor:   ARM920 (only for ASM)
 * @evolution:
 *
 */

#include "SDK30.h"
#include "UCMTELIUM.h"
#include "UCMHOSTDLL.h"
#include "code.h"

static const fct_desc_t tab_fct[]={
  {"UcmHostDll_GetVersion", (void*)UcmHostDll_GetVersion},
  {"UcmHostDll_Cmd",    (void*)UcmHostDll_Cmd}
};

#define NB_FCT    sizeof(tab_fct)/sizeof(fct_desc_t)

void *GetProcAddress(char *name){
  unsigned int i;
  
   for(i=0;i<NB_FCT;i++){
    if(strcmp(name,tab_fct[i].fct_name)==0)
      return(tab_fct[i].fct);
  }
   return((void*)0);
}
