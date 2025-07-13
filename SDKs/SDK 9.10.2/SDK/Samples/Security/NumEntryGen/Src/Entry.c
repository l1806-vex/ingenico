/***
 * Copyright (c) 2001 Sagem Monetel SA, rue claude Chappe,
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
 * @Title:        ENTRY.C
 * @Description:  Entry points for interface with M2OS
 * @Company:      Sagem Monetel
 * @Reference:    
 * @Comment:
 *       
 * @author        JLM
 * @version       1.0
 * @date          2006/12
 */ 

#include "sdk30.h"
//#include "schVar_def.h"
#include "SEC_interface.h"


/*
 Glabal variables
 */
DEL         TheInputDEL;
_DEL_       TheOutputDEL;

extern unsigned char G_ptResult [8];
extern int G_iLenResult;


/*
 external declarations
 */
int Sample_SECExtNumEntry     (void);
 
/*
 Local/static definitions
 */
#define ITEMS_M1  1
const unsigned char   title1 [20] = {"Action ?"};
const unsigned char   item0  [20] = {"\nSample NumEntryGen"};
const unsigned char   result [20] = {"Result ?"};


const NavigationItems mylist1 [ITEMS_M1] =
{ 
  {(char *)item0, NULL, 0, (PFONCNAVI) Sample_SECExtNumEntry},
};

/* Static functions */
int Main (unsigned int size, StructPt *data);


/**
 * @function    AfterReset 
 * @description This module performs the initialisation of the component
 * @param       noappli  : Number of application, param_in : not used        
 * @param out   See doc M²OS Multi Application Manager      
 * @return      Always FCT_OK    
 */
int AfterReset (NO_SEGMENT noappli, void *param_in, S_TRANSOUT *param_out)
{

unsigned char chgt;

unsigned char type;

DATE       date;
S_TRANSOUT paramseq;

    
	read_date(&date);
	memcpy (&paramseq, param_out, sizeof (paramseq));


	//* check for first run : cold or warm reset ? 
	if (first_init (noappli,&chgt,&type) != FSE_FAILED)
	{
		if (chgt == 0xFF)
		{   
		    //* cold reset                                                  
			raz_init(noappli);
        }
    }
	
	paramseq.noappli = noappli;
    memcpy (param_out, &paramseq, sizeof (paramseq));

	return (OK);
}



/**
 * @function    State 
 * @description prints the application info and status 
 * @param       noappli  : Number of application, param_in : not used        
 * @param out   See doc M²OS Multi Application Manager      
 * @return      Always FCT_OK    
 */
int State (NO_SEGMENT noappli,void *param_in,void *param_out)
{
DATE  date;
object_info_t xInfos;
FILE  *hdPrinter;

	ObjectGetInfo(OBJECT_TYPE_APPLI, noappli, &xInfos);      // Retrieve application info
	hdPrinter = fopen ("PRINTER","w-");

	if (hdPrinter != NULL)
	{
	   pprintf  ("\x1b""ESECURITYTEST\n""\x1b""F");
	   read_date(&date);
	   pprintf  ("%.2s/%.2s/%.2s  %.2s:%.2s\n", date.day, date.month, date.year, date.hour, date.minute);
	   pprintf  ("Vers. : %s\n",       xInfos.file_name);
       pprintf  ("Type  : %X (hex)\n", xInfos.application_type);
	   pprintf  ("Crc   : %04X\n",     xInfos.crc);
	   pprintf  ("Size(Code/Data) : %08X\n",     xInfos.memory_size);

	   ttestall (PRINTER,0);
	   fclose   (stdprt());
	}
	   
	return (OK);
}




/**
 * @function     IsName 
 * @description  This service returns the name of the application.
 * @param        application number 
 * @param out    See doc M2OS User's Guide ref[D]. 
 * @return       Always FCT_OK   
 */
int IsName (NO_SEGMENT NoAppli, void *param_in, S_ETATOUT *param_out)
{
S_ETATOUT etatout;

   memcpy (&etatout, param_out, sizeof(etatout));

   strcpy (etatout.returned_state[etatout.response_number].appname, "SECURITY TEST");
   etatout.returned_state[etatout.response_number].no_appli = NoAppli;
   etatout.response_number++;

   memcpy (param_out, &etatout, sizeof (etatout));

   return(OK);
}





/**
 * @function    IsState 
 * @description gives application state
 * @param       noappli  : Number of application, param_in : not used        
 * @param out   See doc M²OS Multi Application Manager      
 * @return      REP_OK or REP_KO  
 */
int IsState (NO_SEGMENT noappli,void *param_in,S_ETATOUT *param_out)
{
S_ETATOUT etatout;
int retour ;

	memcpy (&etatout, param_out, sizeof(etatout));

    etatout.returned_state[etatout.response_number].state.response = REP_OK ;
    memcpy (param_out, &etatout, sizeof (etatout));
	
	retour = IsName (noappli, PT_NULL, param_out);
	
	return (retour);
}




/**
 * @function     IsDelete 
 * @description  This service 
 * @param        application number 
 * @param out    See doc M2OS User's Guide ref[D]. 
 * @return       Always FCT_OK   
 */
int IsDelete (unsigned short no,void *paramin,S_DELETE *paramout)
{
  paramout->deleting=DEL_YES;
  return (OK);
}




/**
 * @function     MoreFunction 
 * @description 
 * @param        application number 
 * @param out    See doc M2OS User's Guide ref[D]. 
 * @return       Always FCT_OK   
 */
int MoreFunction (unsigned short no, void *p1, void *p2)
{
int            ret;
ENTRY_BUFFER   buf;
StructList     Menu;
int            i,c,maxx,maxy; 
FILE           *hdDisplay, *hdKeyboard;
unsigned char  entry, szTemp[3];
char           buffer[30];

  
    hdDisplay  = fopen ("DISPLAY" ,"w");
    hdKeyboard = fopen ("KEYBOARD","r");
   
	GetScreenSize (&maxy,&maxx);
	Menu.MyWindow.left         = 0;                     
	Menu.MyWindow.top          = 0;                     
	Menu.MyWindow.rigth        = (maxx-1);               
	Menu.MyWindow.bottom       = (maxy-1);               
	Menu.MyWindow.fontsize     = _MEDIUM_;               
    Menu.MyWindow.type         = _NORMALE_;        
	Menu.MyWindow.font         = 0;                      
	Menu.MyWindow.shortcommand = _OFF_;                 
	Menu.MyWindow.thickness    = 2;                      
	Menu.MyWindow.border       = _ON_;                   
	Menu.MyWindow.popup        = _NOPOPUP_;              
	Menu.MyWindow.first        = 0;                     
	Menu.MyWindow.time_out     = 60;                    
    Menu.MyWindow.current      = 0;
    Menu.MyWindow.correct      = _ON_;
    Menu.MyWindow.offset       = 0;
    Menu.MyWindow.selected     = _OFF_;                               
    Menu.MyWindow.nblines      = 10;                      
    Menu.MyWindow.type         = _PROPORTIONNEL_; 
    for (i=0;i<ITEMS_LIST_NUMBER;i++) Menu.tab[i] = (unsigned char *)PT_NULL;
    Menu.MyWindow.shortcommand  = _ON_;                 
    Menu.MyWindow.title         = (unsigned char *)title1;
    Menu.tab[0] = (unsigned char *)item0;

    do
    {
      G_List_Entry ((void*)&Menu);    
      ttestall (ENTRY,0);
    
      entry = Get_Entry (&buf);
      if ((entry == CR_ENTRY_OK) && (buf.d_entry[0] < ITEMS_M1))
      {
         c = buf.d_entry[0];
		 G_iLenResult = 0;
         ret = mylist1[c].function ();
         
         sprintf (buffer,"--> %d",ret);
         if ((G_iLenResult > 0) && (ret == 0))
		 {

			if ((G_iLenResult*2) >= (sizeof(buffer)- 5))
				G_iLenResult = (sizeof(buffer) - 5) / 2;
			strcpy (buffer,"> ");
			for (i=0; i< G_iLenResult; i++)
			{
				sprintf ((char*)szTemp, (const char*)"%02X", G_ptResult[i]);
				strcat (buffer, (const char*)szTemp);
			}
		}
         _DrawWindow (10,20,120,60,2,(unsigned char *)"RESULT:");
         _DrawString (buffer,13,35,_OFF_);
         PaintGraphics ();         
         ttestall (0,300);
      }   
    }
    while (entry == CR_ENTRY_OK); 

   fclose (hdDisplay);
   fclose (hdKeyboard);
      
   return (OK);
}



#define FALL_BACK   47



/**
 * @function     FallBack 
 * @description  
 * @param        application number 
 * @param out    See doc M2OS User's Guide ref[D]. 
 * @return       Always FCT_OK   
 */
int FallBack (unsigned short no, S_TRANSIN *p1, void *p2)
{
FILE           *hdDisplay, *hdKeyboard;


   hdDisplay  = fopen ("DISPLAY" ,"w");
   hdKeyboard = fopen ("KEYBOARD","r");
   //startupcv20 (7,7);
      printf ("\x1B");
      printf ("Coucou FALL BACK");
      ttestall (0,500);
   
   fclose (hdDisplay);
   fclose (hdKeyboard);
      
      
   return (OK);
}




/**
 * @function     give_interface 
 * @description 
 * @param        application number 
 * @param out    See doc M2OS User's Guide ref[D]. 
 * @return       Always FCT_OK   
 */
int GiveInterface (unsigned short NoApplication,void *p1,void *p2)
{
service_desc_t MyServices[10];
int iret;


  /* 
   Open DLL (required) 
   */
  iret = SEClib_Open();    /* SEC_ open */


  /*
   Init services data struct 
   */
  MyServices[0].appli_id   = NoApplication;
  MyServices[0].serv_id    = AFTER_RESET;
  MyServices[0].sap        = (int (*)(unsigned int, void *)) Main;
  MyServices[0].priority   = 30; 

  MyServices[1].appli_id   = NoApplication;
  MyServices[1].serv_id    = STATE;
  MyServices[1].sap        = (int (*)(unsigned int, void *)) Main;
  MyServices[1].priority   = 30;

  MyServices[2].appli_id   = NoApplication;
  MyServices[2].serv_id    = IS_STATE;
  MyServices[2].sap        = (int (*)(unsigned int, void *)) Main;
  MyServices[2].priority   = 30;

  MyServices[3].appli_id   = NoApplication;
  MyServices[3].serv_id    = IS_NAME;
  MyServices[3].sap        = (int (*)(unsigned int, void *)) Main;
  MyServices[3].priority   = 30; 

  MyServices[4].appli_id   = NoApplication;
  MyServices[4].serv_id    = MORE_FUNCTION;
  MyServices[4].sap        = (int (*)(unsigned int, void *)) Main;
  MyServices[4].priority   = 30;

  MyServices[5].appli_id   = NoApplication;
  MyServices[5].serv_id    = FALL_BACK;
  MyServices[5].sap        = (int (*)(unsigned int, void *)) Main;
  MyServices[5].priority   = 30;


  /*
   And register...
   */
  ServiceRegister(6, MyServices);
		
		
  return (OK);
}



/**
 * @function     Main 
 * @description 
 * @param              
 * @param        
 * @return       Always FCT_OK   
 */
int Main (unsigned int size, StructPt *data)
{
NO_SEGMENT No;


	No=ApplicationGetCurrent();

	switch(data->service)
	{
      case AFTER_RESET :
	    AfterReset (No, NULL, &data->Param.AfterReset.param_out);
      break;

	  case STATE :
		State (No, NULL, NULL);
      break;

	  case IS_STATE :
	    IsState (No, NULL, &data->Param.IsState.param_out);
      break;

      case IS_NAME :
	    IsName (No, NULL, &data->Param.IsName.param_out);
      break;
    
      case MORE_FUNCTION :
        MoreFunction (No, NULL, NULL);
      break;
    
      case FALL_BACK :
        FallBack (No, NULL, NULL);
      break;
	
	  default : break;
	}
	
	
	return (OK);
}




/**
 * @function    sdklib_open 
 * @description  
 * @see 
 */
void sdklib_open(void)
{

}




/**
 * @function    entry 
 * @description 
 * @see 
 */
void entry (void)
{
   object_info_t info;
  
  
   sdklib_open ();
   
   ObjectGetInfo (OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&info);
   GiveInterface (info.application_type, NULL, NULL);
}



