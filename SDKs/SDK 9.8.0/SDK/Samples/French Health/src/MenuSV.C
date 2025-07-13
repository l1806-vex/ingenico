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

//Prototype added : _vfprintf is not part of the Telium release but in C lib
int _vfprintf(FILE *, const char *, va_list );

static const unsigned char MESS_DIALOGUE[]  = "APPLI_DIALOGUE";
static const unsigned char MESS_SYNC[]      = "APPLI_SYNC";
static const unsigned char MESS_ETAT[]      = "ETAT";
static const unsigned char MESS_ETAT_SV[]   = "ETAT SV";
static const unsigned char MESS_LECT_PS[]   = "LECTURE PS";
static const unsigned char MESS_LECT_SV[]   = "LECTURE SV";
static const unsigned char MESS_M_ON[]      = "M_ON";
static const unsigned char MESS_M_OFF[]     = "M_OFF";
//=============================================================================
int My_pprintf(const char *frmt,...)
{
	va_list arglist;
	int     cr=0;
	FILE   *handle;
	char    gamme;
	char    buf[501];
	
	gamme = PSQ_lire_type_materiel();
	if (gamme==TYPE_TERMINAL_TWIN30)
	{
		/* Information sur le pack */
		handle = fopen("COM0","rw");
		mask_event(handle,COM_FIN_EMI);
		va_start(arglist, frmt);
#ifdef __GNUC__
		vsprintf(buf, frmt, &arglist);
#else
		vsprintf(buf, frmt, arglist);
#endif

		fprintf(handle,buf);
		ttestall(COM0,0);
		fclose(handle);				 		 
		SignalEvent(CurrentTask(),E_PRINTER);
	}
	else
	{
		do
		{
			va_start(arglist, frmt);
#ifdef __GNUC__
			cr = _vfprintf(__stdprt(), frmt, &arglist);
#else
			cr = _vfprintf(__stdprt(), frmt, arglist);
#endif
			if(cr ==EOF)   ttestall(0,5);
		}
		while(cr ==EOF);				 		 
	} 
	return(cr);
} 
//=============================================================================
// Dump data on PRINTER 
void HexDump(unsigned char *Header,unsigned char *String,unsigned long Number)
{
  FILE          *hprt;
  unsigned char  Line[100];
  unsigned char  Buf[10];
  unsigned long  i;
  unsigned long  j;

  hprt = fopen("PRINTER","w-");
  My_pprintf("************************\n%s\n************************\n",Header);
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
    My_pprintf("%s\n",Line);ttestall(PRINTER,0);
  }
  My_pprintf("\n\n\n\n\n");ttestall(PRINTER,0);
  fclose(hprt);
}
//=============================================================================
void default_menu ( StructList *Menu )
{
    int              MAXX,MAXY;

	GetScreenSize(&MAXY,&MAXX);
	Menu->MyWindow.left         = 0;                     
	Menu->MyWindow.top          = 0;                     
	Menu->MyWindow.rigth        = (MAXX-1);               
	Menu->MyWindow.bottom       = (MAXY-1);               
	Menu->MyWindow.fontsize     = _SMALL_;               
    Menu->MyWindow.type         = _NORMALE_;        
	Menu->MyWindow.font         = 0;                      
	Menu->MyWindow.shortcommand = _OFF_;                 
	Menu->MyWindow.thickness    = 1;                      
	Menu->MyWindow.border       = _ON_;                   
	Menu->MyWindow.popup        = _NOPOPUP_;              
	Menu->MyWindow.first        = 0;                     
	Menu->MyWindow.time_out     = 60;                    
    Menu->MyWindow.current      = 0;
    Menu->MyWindow.correct      = _ON_;
    Menu->MyWindow.offset       = 1;
    Menu->MyWindow.selected     = _OFF_;                               
    Menu->MyWindow.nblines      = 15;                      
    Menu->MyWindow.type         = _PROPORTIONNEL_; 
    Menu->tab[0]                = (unsigned char *)PT_NULL;
    Menu->tab[1]                = (unsigned char *)PT_NULL;      
	Menu->tab[2]                = (unsigned char *)PT_NULL;

}
//=============================================================================
void menusv(NO_SEGMENT noappli)
{
  FILE           *fd=NULL;
  FILE           *fd1=NULL;
  unsigned char   cr;
  ENTRY_BUFFER    buf;
  unsigned char   EmissMessage[128];
  unsigned short  usLgEmissMessage;
  unsigned char   RecepMessage[2048];
  unsigned short  usLgRecepMessage;
  StructList      Menu;
  unsigned char   CartePresente;

  fopen("DISPLAY","w");
  default_menu(&Menu);
  /* table init from const */
  Menu.MyWindow.title          = (unsigned char *)MESS_DIALOGUE;
  Menu.tab[0] = (unsigned char *) MESS_ETAT;
  Menu.tab[1] = (unsigned char *) MESS_ETAT_SV;
  Menu.tab[2] = (unsigned char *) MESS_LECT_PS;
  Menu.tab[3] = (unsigned char *) MESS_LECT_SV;
  Menu.tab[4] = (unsigned char *) MESS_M_ON;
  Menu.tab[5] = (unsigned char *) MESS_M_OFF;
  Menu.tab[6] = NULL;
  G_List_Entry((void*)&Menu);ttestall(ENTRY,0);
  cr=Get_Entry(&buf);
  switch(cr)
  {  
    case CR_ENTRY_OK :
	  if (buf.d_entry[0]==0)  // ETAT
	  {
        EmissMessage[0]  = 0xFF;
        EmissMessage[1]  = 0x01;
        EmissMessage[2]  = 0x06;
        EmissMessage[3]  = 0x01;
        usLgEmissMessage = 0x04;
        APPLI_Dialogue(noappli,EmissMessage,usLgEmissMessage,RecepMessage,&usLgRecepMessage);
        HexDump((unsigned char *)MESS_ETAT,RecepMessage,usLgRecepMessage);
	  }
	  if (buf.d_entry[0]==1)  // ETAT SV
	  {
        EmissMessage[0]  = 0x01;
        EmissMessage[1]  = 0x00;
        EmissMessage[2]  = 0x00;
        EmissMessage[3]  = 0x94;
        usLgEmissMessage = 0x04;
        APPLI_Dialogue(noappli,EmissMessage,usLgEmissMessage,RecepMessage,&usLgRecepMessage);
        HexDump((unsigned char *)MESS_ETAT_SV,RecepMessage,usLgRecepMessage);
	  }
	  if (buf.d_entry[0]==2)    // LECT_PS
	  {
		printf("\x1b LECT_PS\n");

		 /* Ouverture du peripherique CAM0 si necessaire */
		if ((fd=stdcam0())==NULL) fd1 = fopen("CAM0","rw");
		// test si carte presente
		do
		{
			if(fd==NULL)
				status(fd1,&CartePresente);
			else
				status(fd,&CartePresente);
			if((CartePresente& CAM_PRESENT)!=CAM_PRESENT)
			{
				printf("Introduire carte");
			}
		}while((CartePresente& CAM_PRESENT)!=CAM_PRESENT);
		// fabrique le buffer
		EmissMessage[0]   = 0x01;
		EmissMessage[1]   = 0x00;
		EmissMessage[2]   = 0x00;
		EmissMessage[3]   = 0x91;
		EmissMessage[4]   = 0x02;
		EmissMessage[5]   = 0x01;
		EmissMessage[6]   = 0x00;
		EmissMessage[7]   = 0xAF;
		EmissMessage[8]   = 0x30;
		EmissMessage[9]   = 0x00;
		EmissMessage[10]  = 0x00;
		EmissMessage[11]  = 0x00;
		EmissMessage[12]  = 0x00;
		EmissMessage[13]  = 0x00;
		EmissMessage[14]  = 0x00;
		EmissMessage[15]  = 0x00;
		EmissMessage[16]  = 0x00;
		EmissMessage[17]  = 0x00;
		EmissMessage[18]  = 0x00;
		EmissMessage[19]  = 0x00;
		EmissMessage[20]  = 0x00;
		EmissMessage[21]  = 0x00;
		EmissMessage[22]  = 0x00;
		EmissMessage[23]  = 0x00;
		EmissMessage[24]  = 0x00;
		EmissMessage[25]  = 0x00;
		EmissMessage[26]  = 0x00;
		EmissMessage[27]  = 0x00;
		EmissMessage[28]  = 0x00;
		EmissMessage[29]  = 0x00;
		EmissMessage[30]  = 0x00;
		EmissMessage[31]  = 0x00;
		EmissMessage[32]  = 0x00;
		EmissMessage[33]  = 0x00;
		EmissMessage[34]  = 0x00;
		EmissMessage[35]  = 0x00;
		EmissMessage[36]  = 0x00;
		EmissMessage[37]  = 0x00;
		EmissMessage[38]  = 0x00;
		EmissMessage[39]  = 0x00;
		EmissMessage[40]  = 0x00;
		EmissMessage[41]  = 0x00;
		EmissMessage[42]  = 0x00;
		EmissMessage[43]  = 0x00;
		EmissMessage[44]  = 0x00;
		EmissMessage[45]  = 0x00;
		EmissMessage[46]  = 0x00;
		EmissMessage[47]  = 0x00;
		EmissMessage[48]  = 0x00;
		EmissMessage[49]  = 0x20;
		EmissMessage[50]  = 0x20;
		EmissMessage[51]  = 0x20;
		EmissMessage[52]  = 0x20;
		EmissMessage[53]  = 0x20;
		EmissMessage[54]  = 0x20;
		EmissMessage[55]  = 0x20;
		EmissMessage[56]  = 0x20;
		EmissMessage[57]  = 0x20;
		EmissMessage[58]  = 0x20;
		EmissMessage[59]  = 0x20;
		EmissMessage[60]  = 0x20;
        usLgEmissMessage = 61;
        APPLI_Dialogue(noappli,EmissMessage,usLgEmissMessage,RecepMessage,&usLgRecepMessage);
        HexDump((unsigned char *)MESS_LECT_PS,RecepMessage,usLgRecepMessage);
		/* fermeture si ferme avant de rentrer dans l'appli */
		if (fd==NULL) fclose(fd1);
	  }


	  if (buf.d_entry[0]==3)  // LECT_SV
	  {
		printf("\x1b LECT_SV\n");
		/* Ouverture du peripherique CAM0 si necessaire */
		if ((fd=stdcam0())==NULL) fd1 = fopen("CAM0","rw");
		// test si carte presente
		do
		{
			if(fd==NULL)
				status(fd1,&CartePresente);
			else
				status(fd,&CartePresente);
			if((CartePresente& CAM_PRESENT)!=CAM_PRESENT)
			{
				printf("Introduire carte");
			}
		}while((CartePresente& CAM_PRESENT)!=CAM_PRESENT);
		// fabrique le buffer
        EmissMessage[0]   = 0x01;
		EmissMessage[1]   = 0x00;
		EmissMessage[2]   = 0x00;
		EmissMessage[3]   = 0x95;
		EmissMessage[4]   = 0x00;
		EmissMessage[5]   = 0x00;
		EmissMessage[6]   = 0x00;
		EmissMessage[7]   = 0xAF;
		EmissMessage[8]   = 0x30;
		EmissMessage[9]   = 0x00;
		EmissMessage[10]  = 0x00;
		EmissMessage[11]  = 0x00;
		EmissMessage[12]  = 0x00;
		EmissMessage[13]  = 0x00;
		EmissMessage[14]  = 0x00;
		EmissMessage[15]  = 0x00;
		EmissMessage[16]  = 0x00;
		EmissMessage[17]  = 0x00;
		EmissMessage[18]  = 0x00;
		EmissMessage[19]  = 0x00;
		EmissMessage[20]  = 0x00;
		EmissMessage[21]  = 0x00;
		EmissMessage[22]  = 0x00;
		EmissMessage[23]  = 0x00;
		EmissMessage[24]  = 0x00;
		EmissMessage[25]  = 0x00;
		EmissMessage[26]  = 0x00;
		EmissMessage[27]  = 0x00;
		EmissMessage[28]  = 0x00;
		EmissMessage[29]  = 0x00;
		EmissMessage[30]  = 0x00;
		EmissMessage[31]  = 0x00;
		EmissMessage[32]  = 0x00;
		EmissMessage[33]  = 0x00;
		EmissMessage[34]  = 0x00;
		EmissMessage[35]  = 0x00;
		EmissMessage[36]  = 0x00;
		EmissMessage[37]  = 0x00;
		EmissMessage[38]  = 0x00;
		EmissMessage[39]  = 0x00;
		EmissMessage[40]  = 0x00;
		EmissMessage[41]  = 0x00;
		EmissMessage[42]  = 0x00;
		EmissMessage[43]  = 0x00;
		EmissMessage[44]  = 0x00;
		EmissMessage[45]  = 0x00;
		EmissMessage[46]  = 0x00;
		EmissMessage[47]  = 0x00;
		EmissMessage[48]  = 0x00;
		EmissMessage[49]  = 0x20;
		EmissMessage[50]  = 0x20;
		EmissMessage[51]  = 0x20;
		EmissMessage[52]  = 0x20;
		EmissMessage[53]  = 0x20;
		EmissMessage[54]  = 0x20;
		EmissMessage[55]  = 0x20;
		EmissMessage[56]  = 0x20;
		EmissMessage[57]  = 0x20;
		EmissMessage[58]  = 0x20;
		EmissMessage[59]  = 0x20;
		EmissMessage[60]  = 0x20;
		EmissMessage[61]  = 0x31;
		EmissMessage[62]  = 0x39;
		EmissMessage[63]  = 0x39;
		EmissMessage[64]  = 0x39;
		EmissMessage[65]  = 0x30;
		EmissMessage[66]  = 0x31;
		EmissMessage[67]  = 0x30;
		EmissMessage[68]  = 0x31;
        usLgEmissMessage = 69;
        APPLI_Dialogue(noappli,EmissMessage,usLgEmissMessage,RecepMessage,&usLgRecepMessage);
        HexDump((unsigned char *)MESS_LECT_SV,RecepMessage,usLgRecepMessage);
		/* fermeture si ferme avant de rentrer dans l'appli */
		if (fd==NULL) fclose(fd1);
	  }


	  if (buf.d_entry[0]==4)  // M_ON
	  {
		printf("\x1b M_ON\n");
		/* Ouverture du peripherique CAM0 si necessaire */
		if ((fd=stdcam0())==NULL) fd1 = fopen("CAM0","rw");
				// test si carte presente
		do
		{
			if(fd==NULL)
				status(fd1,&CartePresente);
			else
				status(fd,&CartePresente);
			if((CartePresente& CAM_PRESENT)!=CAM_PRESENT)
			{
				
				printf("Introduire carte");
			}
		}while((CartePresente& CAM_PRESENT)!=CAM_PRESENT);

		OS_CamReset(OS_CAM0,RecepMessage,&usLgRecepMessage);

        HexDump((unsigned char *)MESS_M_ON,RecepMessage,usLgRecepMessage);
		if (fd==NULL) fclose(fd1);
	  }
	  if (buf.d_entry[0]==5)  // M_OFF
	  {
		/* Ouverture du peripherique CAM0 si necessaire */
		if ((fd=stdcam0())==NULL) fd1 = fopen("CAM0","rw");
		OS_CamOff(OS_CAM0);
		if (fd==NULL) fclose(fd1);
	  }
      break;
  }
  fclose(stdout());
}

