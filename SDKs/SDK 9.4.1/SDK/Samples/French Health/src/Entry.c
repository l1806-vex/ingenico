/***
 * Copyright (c) 2004 Sagem Monetel SA, rue claude Chappe,
 * 07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * Sagem Monetel SA has intellectual property rights relating
 * to the technology embodied in this software.  In particular, 
 * and without limitation, these intellectual property rights 
 * may include one or more patents.
 *
 * This software is distributed under licenses restricting 
 * its use, copying, distribution, and decompilation.  
 * No part of this software may be reproduced in any form 
 * by any means without prior written authorization of 
 * Sagem Monetel.
 *
 * @Title:        
 * @Description:  SDK30 sample application
 * @Reference:    
 * @Comment:      
 *
 * @author        
 * @version       
 * @Comment:      
 * @date:         
 */
#include "SDK30.H"

void   menusv(void);			// call test Sesam Vital 

static const char t_date    [] = "LE %.2s/%.2s/%.2s  %.2s:%.2s\n";
static const unsigned char appname[]    = "TEST SV";

int			i,select;	
unsigned char     	cr,returned;
ENTRY_BUFFER    	buf_entry;
StructList       	Menu1,Menu2;
int              	MAXX;
int               	MAXY; 
TAB_ENTRY_STRING	NumEntry;

/* Static functions */
int Main (unsigned int size, StructPt *data);

// =================================================================
int more_function(NO_SEGMENT no,void *p1,void *p2)
{
  menusv();			// call test Sesam Vital 
  return (FCT_OK);
}

// =================================================================
int after_reset(NO_SEGMENT no,void *p1,S_TRANSOUT *etatseq)
{
  return (FCT_OK);
}
// =================================================================
int is_state(NO_SEGMENT no,void *p1,S_ETATOUT *etatseq)
{
  S_ETATOUT etatout;
  int retour; 

   memcpy (&etatout, etatseq, sizeof(etatout));
   etatout.returned_state[etatout.response_number].state.response = REP_OK;
   memcpy (etatseq, &etatout, sizeof(etatout));
   retour = is_name (no, PT_NULL, etatseq);
   return (retour);
 }
// =================================================================

int is_name(NO_SEGMENT no,void *p1,S_ETATOUT *etatseq)
{
  S_ETATOUT etatout;
  
  memcpy ((char *)&etatout, (char *)etatseq, sizeof(etatout));
  strcpy((char *)etatout.returned_state[etatout.response_number].appname,(char *)appname);
  etatout.returned_state[etatout.response_number].no_appli = no;
  etatout.response_number++;
  memcpy (etatseq, &etatout, sizeof(etatout));
  return (FCT_OK);
}
// =================================================================

int give_your_domain(NO_SEGMENT no,void *p1,S_INITPARAMOUT *param_out)
{
  S_INITPARAMOUT etatout;

  memcpy (&etatout, param_out, sizeof(etatout));
  etatout.returned_state[etatout.response_number].mask     = MSK_MDP|MSK_SWIPE|MSK_TYPE_PPAD|MSK_PINPAD|MSK_STANDARD|MSK_LANGUE|MSK_FRMT_DATE|MSK_DATE;
  etatout.returned_state[etatout.response_number].application_type = TYP_EXPORT;
  etatout.response_number++;
  memcpy (param_out, &etatout, sizeof(etatout));
  return (FCT_OK);
}
// =================================================================

int state (NO_SEGMENT noappli,void *p1,void *p2)
{
  SEGMENT infos;
  DATE    date;
  FILE     *printer;
  int Language,date_format;
  unsigned long ldate;

  info_seg (noappli, &infos);

  Language=PSQ_Give_Language();
  date_format = PSQ_Give_Date_Format();
  printer=fopen ("PRINTER","w-*");
  if ( printer != NULL ) 
  {
	  
	  pprintf ("\x1b""E%s\n""\x1b""F",appname);
	  read_date (&date);
	  ldate= d_tolong (&date);
	  pprintf (t_date, date.day, date.month, date.year, date.hour, date.minute);
	  
	  pprintf ("Vers. : %s\n",infos.libelle);
	  pprintf ("CRC   : %04x\n",infos.crc);
	  fclose(printer); 
  }
    
  return (FCT_OK);
}

// =================================================================
int idle_message (NO_SEGMENT no,void *p1,void *p2)
{
FILE *hdisp;

  hdisp=fopen("DISPLAY","w");
  printf("  Test SV   \n   use F key");
  fclose(hdisp);
  return (FCT_OK);
}
// =================================================================


typedef int (*T_SERVICE_FUNCTION)(unsigned int nSize, void*Data);

int give_interface(unsigned short no,void *p1,void *p2)
{
  service_desc_t MesServices[40];
  int i ; 
  i = 0 ;
  MesServices[i].appli_id  = no;
  MesServices[i].serv_id   = IS_NAME;
  MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
  MesServices[i].priority  = 10;
  i++;
  MesServices[i].appli_id  = no;
  MesServices[i].serv_id   = GIVE_YOUR_DOMAIN;
  MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
  MesServices[i].priority  = 10;
  i++;
  MesServices[i].appli_id  = no;
  MesServices[i].serv_id   = MORE_FUNCTION;
  MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
  MesServices[i].priority  = 10;
  i++;
  MesServices[i].appli_id  = no;
  MesServices[i].serv_id   = IDLE_MESSAGE;
  MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
  MesServices[i].priority  = 20;
  i++;
  MesServices[i].appli_id  = no;
  MesServices[i].serv_id   = AFTER_RESET;
  MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
  MesServices[i].priority  = 10;
  i++;
  MesServices[i].appli_id  = no;
  MesServices[i].serv_id   = IS_STATE;
  MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
  MesServices[i].priority  = 10;
  i++;
  MesServices[i].appli_id  = no;
  MesServices[i].serv_id   = STATE;
  MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
  MesServices[i].priority  = 10;
  i++;
  ServiceRegister(i,MesServices);
  return (FCT_OK);
}

#ifdef _EFT30_
void entry(void)
{
  object_info_t info;
  
  ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&info);
  give_interface((NO_SEGMENT)info.application_type, NULL, NULL);
}
#endif

