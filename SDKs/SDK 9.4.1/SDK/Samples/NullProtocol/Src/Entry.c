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
 * @Description:
 * @Reference:
 * @Comment:
 *
 * @author
 * @version
 * @Comment:
 * @date:         2002/12/02
 */


/**
 * @function:
 * @description:
 * @see:
 * @author:
 *-----------------------------------------------------------------------------
 * @param:
 * @param:
 * @return:
 * @execption:
 *-----------------------------------------------------------------------------
 */

#include "sdk30.h"

#define VERSION "1.02"
int idleStage = TRUE;
/* My Name */
static const unsigned char appname[] = "NULL_PROT";


/* Parameters of COM_EVENT entry point */
static S_COMIN             param_comin;
static S_COMOUT            param_comout;
/* My application number */
static NO_SEGMENT          appli_number;
/* Protocole task handle : see OEM.H for description */
static t_topstack         *pttask;
/* Task number of M2OS */
static unsigned short      m2os_task;


/* Dump data on PRINTER */
void HexDump(unsigned char *Header,unsigned char *String,unsigned long Number)
{
  FILE          *hprt;
  unsigned char  Line[100];
  unsigned char  Buf[10];
  unsigned long  i;
  unsigned long  j;

  hprt = fopen("PRINTER","w-");
  pprintf("************************\n%s\n************************\n",Header);
  ttestall(PRINTER,0);
  for (i=0;i<Number;i+=6)
  {
    memset(Line,' ',24);Line[24]='\0';
    for (j=i;j<Number && j<(i+6);j++)
    {
      sprintf((char *)Buf,"%02X ",String[j]);
      memcpy(&Line[(j-i)*3],Buf,3);
      if (String[j]<=125 && String[j]>=32)
      {
        Line[18+(j-i)] = String[j];
      }
      else
      {
        Line[18+(j-i)] = '.';
      }
    }
    pprintf("%s\n",Line);ttestall(PRINTER,0);
  }
  pprintf("\n\n\n\n\n");ttestall(PRINTER,0);
  fclose(hprt);
}


/* Protocol task 

Com port configuration (COM0): 9600, 8 bits, 1 stop bit, no parity.

*/
void Task_Protocol(void)
{
    unsigned int   cr;          /* Result of ttestall                            */
    unsigned int   mask;        /* Mask of event to wait depending of task state */
    FILE          *handle=NULL; /* Decriptor of serial link                      */
    char           buf[128];    /* To read from serial link                      */
    char           data[1024];  /* To read from serial link                      */
    unsigned int   nb;          /* Result of fread                               */
    unsigned int   len;         /* Length of data received                       */

    /* Only synchronisation to wait */
    mask       = SYNCHRO_DIALOG;
    /* Task is now operationnal */
    SignalEvent(m2os_task,EVT_SYNCHRO_DIALOG);
    while (1)
    {
        cr = ttestall(mask,0);
        if( cr == COM0 )
        {
            /* Only synchronisation to wait */
            mask = SYNCHRO_DIALOG;
            if (idleStage == TRUE){
            	/* Request manager focus */
            	SignalEvent(m2os_task,EVT_DIALOG);
            }
            else {
                len = 0;
                do
                {
                    nb=fread(buf,1,128,handle);
                    if(nb)
                    {
                        if ((len + nb) <= sizeof(data))
                        {
                            memcpy(&data[len],buf,nb);
                            len+=nb;
                        }
                        else
                        {
                            memcpy(&data[len],buf,sizeof(data)-len);
                            len = sizeof(data);
                        }
                    }
                }
                while(((len != sizeof(data)) && (ttestall(COM0,10) == COM0)) || (nb != 0));
			}
        }
        else // SYNCHRO_DIALOG event
        {
            /* Initialize returned structure */
            /* Appli number */
            param_comout.no_appli = appli_number;
            /* Handle of peripheral , not used */
            param_comout.handle   = NULL;
            /* function return */
            param_comout.cr       = CR_DIALOGUE_OK;

            switch (param_comin.action)
            {
                case DO_OPEN:
                    /* Open all protocole peripheral (for exemple COM0) */
                    handle = fopen("COM0","rw");
                    /* initialize peripheral */
                    /* 9600 bauds,8 bits, 1 stop bit,no parity */
                    format("COM0",CBR_9600,8,1,NO_PARITY,NO_PARITY,0);
                    /* We are now waiting for serial link and synchronization */
                    mask = COM0 | SYNCHRO_DIALOG;
                    break;
                case DO_RECEPT:
                    /*-------------------------------------------*/
                    /* Put protocole managment here              */
                    /*          for exemple                      */
                    /* Read from COM0 and print data received    */
                    /*-------------------------------------------*/
                    /* nothing */
                    len = 0;
                    do
                    {
                        nb=fread(buf,1,128,handle);
                        if(nb)
                        {
                            if ((len + nb) <= sizeof(data))
                            {
                                memcpy(&data[len],buf,nb);
                                len+=nb;
                            }
                            else
                            {
                                memcpy(&data[len],buf,sizeof(data)-len);
                                len = sizeof(data);
                            }
                        }
                    }
                    while(((len != sizeof(data)) && (ttestall(COM0,10) == COM0)) || (nb != 0));
                    if (len!=0)
                    {
                        HexDump("DATA RECEIVED FROM C0M0",data,len);
                    }
                    /* We are now waiting for serial link and synchronization */
                    mask = COM0 | SYNCHRO_DIALOG;
                    break;
                case DO_CLOSE:
                    /* Close all protocole peripheral (for exemple COM0) */
                    fclose(handle);
                    /* Only synchronisation to wait */
                    mask = SYNCHRO_DIALOG;
                    break;
            }
            /* Traitment is over */
            SignalEvent(m2os_task,EVT_SYNCHRO_DIALOG);
        }
    }
}

/* Function executed with AFTER_RESET entry point */
int after_reset(NO_SEGMENT no,void *p1,S_TRANSOUT *param_out)
{
    /* Link wtih Librairies */
    /* Remember my application number */
    appli_number = no;
    /* Remember task number of M2OS */
    m2os_task = CurrentTask();
    /* Force Cash Connection */
    PSQ_Update_Cash_Connection(cash_connection_on);
    /* Start Protocole Task */
    pttask = (t_topstack *) fork((PFONCFORK)Task_Protocol,NULL,NULL);
    /* Waiting for task to be started */
    ttestall(SYNCHRO_DIALOG,0);
    /* End */
    return (FCT_OK);
}

int com_event (NO_SEGMENT noappli, S_COMIN *param_in, S_COMOUT *param_out)
{
    memcpy((char *)&param_comin, (char *)param_in, sizeof(S_COMIN));
    switch(param_in->action)
    {
        case DO_OPEN :
        case DO_RECEPT :
        case DO_CLOSE :
            /* because of MMU, GiveNoTack is use to read an element of pttask */
            /* Signal to protocole task that something is to do               */
            /* The action is available into param_comin variable              */
            SignalEvent(GiveNoTask(pttask),EVT_SYNCHRO_DIALOG);
            /* Wait the end of traitment */
            ttestall(SYNCHRO_DIALOG,0);
            /* Copy result of traitment */
            memcpy((char *)param_out,(char *)&param_comout,sizeof(S_COMOUT));
            break;
    }
    return(FCT_OK);
}

int idle_message (NO_SEGMENT no,void *p1,void *p2)
{
    fopen("DISPLAY","w");
    printf("CASH CONNECTION\nNULL SAMPLE");
    fclose(stdout());
    return (FCT_OK);
}

int give_your_domain(NO_SEGMENT no,void *p1,S_INITPARAMOUT *param_out)
{
    S_INITPARAMOUT etatout;

    memcpy (&etatout, param_out, sizeof(etatout));
    etatout.returned_state[etatout.response_number].mask             = MSK_ALL_PARAM;
    etatout.returned_state[etatout.response_number].application_type = TYP_EXPORT;
    etatout.response_number++;
    memcpy (param_out, &etatout, sizeof(etatout));
    return (FCT_OK);
}

int more_function(NO_SEGMENT no,void *p1,void *p2)
{
	idleStage = FALSE;
    fopen("DISPLAY","w");fopen("KEYBOARD","r");
    printf("CASH CONNECTION\nSAMPLE %s",VERSION);getchar();
    fclose(stdout());fclose(stdin());
	idleStage = TRUE;
    return (FCT_OK);
    return (FCT_OK);
}

int is_name(NO_SEGMENT no,void *p1,S_ETATOUT *etatseq)
{
    S_ETATOUT        etatout;

    memcpy ((char *)&etatout, (char *)etatseq, sizeof(etatout));
    strcpy((char *)etatout.returned_state[etatout.response_number].appname,(char *)appname);
    etatout.returned_state[etatout.response_number].no_appli = no;
    etatout.response_number++;
    memcpy (etatseq, &etatout, sizeof(etatout));
    return (FCT_OK);
}

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

int keyboard_event(NO_SEGMENT noappli,S_KEY *key_in,S_KEY *key_out)
{
	// Local variables *
    // *****************
	   // Empty

	// Keyboard management
	// *******************
	switch (key_in->keycode)
	{
	case N0:
		more_function(noappli, NULL, NULL);
		key_out->keycode = 0;               // Inhibit these keys to Manager for International domain
		break;
	case N1: case N2: case N3: case N4:
	case N5: case N6: case N7: case N8: case N9:
	case T_VAL:
		more_function(noappli, NULL, NULL);
		key_out->keycode = 0;               // Inhibit these keys to Manager for International domain
		break;
		case T_POINT: case F2: case F3:
		key_out->keycode = 0;               // Inhibit these keys to Manager for International domain
		break;
	case F1: case F4:
	case T_CORR: case T_ANN: case NAVI_CLEAR: case NAVI_OK:
	case UP: case DOWN:
		key_out->keycode=key_in->keycode;
		break;
	case T_F:                               // do not filter F key and return the same key !
		key_out->keycode=key_in->keycode;   // Return the same key value for keys above !
		break;
	default:
		key_out->keycode=key_in->keycode;
		break;
	}

	return FCT_OK;
}

int give_interface(unsigned short no,void *p1,void *p2)
{
    service_desc_t MesServices[40];
    int            i;

    i=0;

    MesServices[i].appli_id  = no;
    MesServices[i].serv_id   = GIVE_YOUR_DOMAIN;
    MesServices[i].sap       = (SAP)Main;
    MesServices[i].priority  = 10;
    i++;

    MesServices[i].appli_id  = no;
    MesServices[i].serv_id   = AFTER_RESET;
    MesServices[i].sap       = (SAP)Main;
    MesServices[i].priority  = 10;
    i++;

    MesServices[i].appli_id  = no;
    MesServices[i].serv_id   = IDLE_MESSAGE;
    MesServices[i].sap       = (SAP)Main;
    MesServices[i].priority  = 10;
    i++;

    MesServices[i].appli_id  = no;
    MesServices[i].serv_id   = COM_EVENT;
    MesServices[i].sap       = (SAP)Main;
    MesServices[i].priority  = 10;
    i++;

    MesServices[i].appli_id  = no;
    MesServices[i].serv_id   = MORE_FUNCTION;
    MesServices[i].sap       = (SAP)Main;
    MesServices[i].priority  = 10;
    i++;

    MesServices[i].appli_id  = no;
    MesServices[i].serv_id   = IS_NAME;
    MesServices[i].sap       = (SAP)Main;
    MesServices[i].priority  = 10;
    i++;

    MesServices[i].appli_id  = no;
    MesServices[i].serv_id   = IS_STATE;
    MesServices[i].sap       = (SAP)Main;
    MesServices[i].priority  = 10;
    i++;
    MesServices[i].appli_id  = no;
    MesServices[i].serv_id   = KEYBOARD_EVENT;              // Service => Return the key pressed
    MesServices[i].sap       = (SAP)Main;
    MesServices[i].priority  = 0;
	i++;

    ServiceRegister(i,MesServices);

    return (FCT_OK);
}

void entry(void)
{
    object_info_t info;

    ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&info);
    give_interface(info.application_type, NULL, NULL);
}

