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

static const unsigned char appname[]    = "TEST MSG";
int			i,select;	
unsigned char     	cr,returned;
ENTRY_BUFFER    	buf_entry;
StructList       	Menu1,Menu2;
int              	MAXX;
int               	MAXY; 
TAB_ENTRY_STRING	NumEntry;
extern void TestPrinter(void);
extern void TestDisplay(void);
extern void LanguageSelection(void);
extern void OtherTest(void);

#define __ENTER_KEY		-1
#define __BACK_KEY		-2
#define __EXIT_KEY		-3
#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))
const char *MenuTest[] =
{
	"Display demo",
	"Printer demo",
	"Language selection",
	"OtherTest",
};

/* Static functions */
int Main (unsigned int size, StructPt *data);


// =================================================================

int ManageMenu( const char *szTitle, int bRadioButtons, int nDefaultChoice, 
				int nItems, const char* Items[] )
{
	// Menu.
	StructList Menu;
	int nY;
	int nMaxX;
	int nMaxY;

	ENTRY_BUFFER Entry;

	//
	int i;
	int nInput;
	int nReturn;

	// Get Screen size.
	GetScreenSize( &nMaxY, &nMaxX );

	// For the menu height of the menu,
	nY = 0;

	if ((nDefaultChoice < 0) || (nDefaultChoice >= nItems))
	{
		nDefaultChoice = 0;
	}

	//
	CreateGraphics(_MEDIUM_);

	//
	memset( &Menu, 0, sizeof(Menu) );
	Menu.MyWindow.left   = 0;
	Menu.MyWindow.top    = nY;
	Menu.MyWindow.rigth  = nMaxX - 1;
	Menu.MyWindow.bottom = nMaxY - 1;
	if( nMaxY == 128 )
	{
		Menu.MyWindow.nblines = 10;
	}
	else
	{
		Menu.MyWindow.nblines = 5;
	}

	Menu.MyWindow.fontsize		= _MEDIUM_;
	Menu.MyWindow.type			= _PROPORTIONNEL_;
	Menu.MyWindow.font			= 0;
	Menu.MyWindow.correct		= _ON_;
	Menu.MyWindow.offset		= 0;
	Menu.MyWindow.shortcommand	= _ON_;
	if( bRadioButtons )
	{
		Menu.MyWindow.selected = _ON_;
	}
	else
	{
		Menu.MyWindow.selected = _OFF_;
	}

	Menu.MyWindow.thickness		= 2;
	Menu.MyWindow.border		= _ON_;
	Menu.MyWindow.popup			= _NOPOPUP_;
	Menu.MyWindow.first			= nDefaultChoice;
	Menu.MyWindow.current		= nDefaultChoice;
	Menu.MyWindow.time_out		= 60;
	Menu.MyWindow.title			= (unsigned char*)szTitle;

	for( i = 0; i < nItems; i++ )
	{
		Menu.tab[i] = (unsigned char*)Items[i];
	}

	G_List_Entry((void*)&Menu);
	ttestall(ENTRY, 0);
	nInput = Get_Entry((void*)&Entry);

	switch( nInput )
	{
	case CR_ENTRY_OK:
		nReturn = Entry.d_entry[0];
		break;

	case CR_ENTRY_NOK:
		nReturn = __EXIT_KEY;
		break;

	default:
		nReturn = __BACK_KEY;
		break;
	}

	return nReturn;
}

// =================================================================
int more_function(NO_SEGMENT no,void *p1,void *p2)
{
	int bContinue = 1;
	int HeaderStatus;


	fopen("KEYBOARD","r");	
	fopen("DISPLAY","w");
	HeaderStatus=StateHeader(0); // disable header on EFT930
	do
	{
		switch( ManageMenu( "Tests", 0, 0, NUMBER_OF_ITEMS(MenuTest), MenuTest ))
		{
		case 0:
			TestDisplay();
			break;
		case 1:
			TestPrinter();
			break;
		case 2:
			LanguageSelection();
			break;
		case 3:
			OtherTest();
			break;
		default:
			bContinue = 0;
			break;
		}
	}
	while( bContinue == 1 );
	HeaderStatus=StateHeader(HeaderStatus);
	fclose(stdin());
	fclose(stdout());
	return FCT_OK;
}


// =================================================================
extern void DefaultSettings(void);
int after_reset(NO_SEGMENT no,void *p1,S_TRANSOUT *etatseq)
{	
	DefaultSettings();
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
  int Language,date_format,pinpad_flag,pinpad_type,iso1,iso2,iso3,pstn_flag;
  NO_TERMIN noterm;
  T_STANDARD PABX_prefix;
  S_PARAM_TLCHGT TMS_infos;
  unsigned long ldate;

  info_seg (noappli, &infos);

  Language=PSQ_Give_Language();
  date_format = PSQ_Give_Date_Format();
  PSQ_No_terminal((NO_TERMINAL *) &noterm[0]);
  PSQ_No_standard(PABX_prefix);
  pinpad_flag=PSQ_Is_pinpad();
  pinpad_type=PSQ_Pinpad_Type();
  iso2 = PSQ_Is_ISO2();
  iso1 = PSQ_Is_ISO1();
  iso3 = PSQ_Is_ISO3();
  pstn_flag = PSQ_Is_PSTN();
  PSQ_Idf_telechgt(&TMS_infos);
  
  printer=fopen ("PRINTER","w-*");
  if ( printer != NULL ) {

	  pprintf ("\x1b""E%s\n""\x1b""F",appname);
	  read_date (&date);
          ldate= d_tolong (&date);
	  pprintf ("Vers. : %s\n",infos.libelle);
	  pprintf ("CRC   : %04x\n",infos.crc);
      ttestall (PRINTER,0);	  
	  fclose(printer); 
  }
    
  return (FCT_OK);
}
// =================================================================
int idle_message (NO_SEGMENT no,void *p1,void *p2)
{
FILE *hdisp;

  hdisp=fopen("DISPLAY","w");
  printf("   Test MSG   \n   use F key \n");
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
   MesServices[i].appli_id  = no;
  MesServices[i].serv_id   = IDLE_MESSAGE;
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

