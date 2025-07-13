/**
* \file Gpinpad.c
* \brief This module contains functions used for pinpad management.
*
* \author Ingenico France
* \author Copyright (c) 2009 Ingenico France, 1 rue claude Chappe,\n
* 07503 Guilherand-Granges, France, All Rights Reserved.
*
* \author Ingenico France has intellectual property rights relating to the technology embodied\n
* in this software. In particular, and without limitation, these intellectual property rights may\n
* include one or more patents.\n
* This software is distributed under licenses restricting its use, copying, distribution, and\n
* and decompilation. No part of this software may be reproduced in any form by any means\n
* without prior written authorization of Ingenico France.
**/

/* ======================================================================== */
/* Include Files                                                            */
/* ======================================================================== */

#include "sdk30.h"
#include "pp30_def.h"
#include "basppr.h"
#include "cu_mess.h"
#include "MessagesDefinitions.h"
#include "def_tag.h"
#include "cu_term.h"

//! \addtogroup Group_Gpinpad
//! @{

/* ======================================================================== */
/* Macros & preprocessor definitions                                        */
/* ======================================================================== */

/* =========================================================================*/
/* Types declarations                                                       */
/* =========================================================================*/

/* ======================================================================== */
/* Constant declarations                                                    */
/* ======================================================================== */

static const TAB_ENTRY_FCT    tab_test_ppr = {0x2920, 4*MINUTE};
static const TAB_ENTRY_FCT    t_annulcd    = {0x2000, 2*MINUTE};
static const TAB_ENTRY_FCT    tab_test     = {0x6800, 4*MINUTE};

/* ========================================================================	*/
/* Global variables                                                         */
/* ========================================================================	*/

/* ========================================================================	*/
/* Static function definitions                                              */
/* ========================================================================	*/

//===========================================================================
//! \brief This function displays an application identifier list on pinpad reader. 
//! Then it waits for a key entry.
//! \param[in] Tab : list of applications to be displayed on pinpad.
//! \param[in] number : number of applications to be displayed.
//! \param[in] selected : number of application to display on the first line.
//! \return The returned value of entry function.
//===========================================================================
static unsigned char Display_ppr_list (T_LABEL *Tab,unsigned char number,unsigned char selected)
{
	int           MAXX,MAXY;
	int           i;
	StructList    Menu;
	unsigned char cr;
	ENTRY_BUFFER  buf;

	InitContexteGraphique(PERIPH_PPR);
	GetScreenSize(&MAXY,&MAXX);
	Menu.MyWindow.left         = 0;
	Menu.MyWindow.top          = 0;
	Menu.MyWindow.rigth        = (MAXX-1);
	Menu.MyWindow.bottom       = (MAXY-1-12);
	Menu.MyWindow.fontsize     = _NORMALE_;
	Menu.MyWindow.type         = _PROPORTIONNEL_;
	Menu.MyWindow.font         = 0;
	Menu.MyWindow.shortcommand = _OFF_;
	Menu.MyWindow.thickness    = 2;
	Menu.MyWindow.border       = _ON_;
	Menu.MyWindow.popup            = _NOPOPUP_;
	Menu.MyWindow.first        = selected;
	Menu.MyWindow.time_out     = 60;
	Menu.MyWindow.current      = selected;
	Menu.MyWindow.correct      = _ON_;
	Menu.MyWindow.offset       = 0;
	Menu.MyWindow.nblines      = 3;
	Menu.MyWindow.selected     = _OFF_;
	Menu.MyWindow.title        = (unsigned char *)"LIST";
	for (i=0;i<number;i++)
	{
		Menu.tab[i]             = (unsigned char *)Tab[i];
	}
	Menu.tab[i] = PT_NULL;
	InitContexteGraphique(PERIPH_DISPLAY);
	G_Aff_Liste_Ppr((StructListe *)(void*)&Menu);ttestall(ENTRY,0);
	cr=Get_Entry((ENTRY_BUFFER*)&buf);
	InitContexteGraphique(PERIPH_PPR);
	DisplayBitmap(0,(MAXY-1-10),(unsigned char*)basppr,8,_OFF_);
	InitContexteGraphique(PERIPH_DISPLAY);
	return(cr);
}

/* ======================================================================== */
/* Functions                                                                */
/* ======================================================================== */

//===========================================================================
unsigned char Select_on_PPR_pinpad ( T_LABEL *Tab , unsigned char number )
{
	unsigned char	selected ;
	ENTRY_BUFFER	buffer ;
	T_LABEL			Tab_Appli_Name[20+1]; // Tab_nom_appli[ 20 + 1] ;
	unsigned char	Cr ;
	unsigned short	Ret ;
	unsigned char	Continue ;
	int				lg_code;
	unsigned char	msg[100];
	unsigned char	*pc_line1, *pc_line2;


	selected = 0 ;Continue = 0;
	memcpy(Tab_Appli_Name,Tab, number *sizeof(T_LABEL));

	// Get the manager language
	lg_code = PSQ_Give_Language();

	pc_line1 = (unsigned char *)CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_SELECT, lg_code);
	pc_line2 = (unsigned char *)CUMESS_Read_Message(DEFAULT_TABLE, DFT_MESS_NB_ON_PINPAD, lg_code);
	memset(msg, 0, sizeof(msg));
	sprintf((char*)msg, "%s\n%s", pc_line1, pc_line2);
	CUTERMdisplayLine(0, (char*)msg , CENTER, (char *)"w");


	do
	{

		Display_ppr_list ((T_LABEL *)&Tab_Appli_Name,number,selected);
		Fct_Entry ( (TAB_ENTRY_FCT *)&t_annulcd );
		PPS_Fct_Entry  ( (TAB_ENTRY_FCT *)&tab_test_ppr );
		Ret = ttestall ( ENTRY | ENTRY_PPAD , 0);
		if (Ret & ENTRY)
		{
			// The merchant canceled, or inactivity timeout occured.
			PPS_Stop_Entry ();
			Cr = Get_Entry (&buffer);
			// End of loop. selected is set to max application index + 1.
			selected = number + 1; 
			Continue = 1;
		}
		else
		{
			if (Ret & ENTRY_PPAD)
			{
				memclr( &buffer , sizeof(buffer) );
				Cr =  PPS_Read_Entry ((BUFFER_SAISIE*)&buffer);
				Stop_Entry ();
				PPS_Stop_Entry  ();
				switch(Cr)
				{
				case CR_ENTRY_CANCEL :
					selected = number + 1 ;
					Continue = 1;
					break;
				case CR_ENTRY_VALIDATED   :
					Continue = 1;
					break;
				case CR_ENTRY_OK    :
					switch (buffer.d_entry[0])
					{
					case TC_FONCTION_PPAD :
					case TC_SK4_PPAD :
						selected++;
						if (selected==number)
						{
							selected=0;
						}
						break;
					case TC_SK1_PPAD :
						if (selected==0)
						{
							selected=(number-1);
						}
						else
						{
							selected--;
						}
						break;
					}
					break;
				}
			}
			else
			{
				PPS_Stop_Entry  ();
				Stop_Entry ();
			}
		}
	}
	while(Continue==0);
	PPS_clear_display();
	return(selected);
}

//===========================================================================
unsigned char Select_on_pinpad (T_LABEL *Tab_param_appli_name , unsigned char nb_appli)
{
	unsigned char    appli_index;
	ENTRY_BUFFER    buffer;
	T_LABEL          Tab_Appli_Name[16+1];
	unsigned char    Tab_first_line_name[17];
	unsigned char    Tab_second_line_name[17];
	unsigned char    returned_char;
	unsigned short   fct_return;
	unsigned char    no_end;

	appli_index = 0;
	no_end = 0;
	memcpy(Tab_Appli_Name,Tab_param_appli_name, nb_appli *sizeof(T_LABEL));


	CUMESS_Display_Message (0, STD_MESS_SELECT_PROG_1, DISPLAY_MERCHANT_CARDHOLDER);
	CUMESS_Display_Message (1, STD_MESS_SELECT_PROG_2, DISPLAY_MERCHANT_CARDHOLDER);

	do
	{
		//if (PSQ_type_pinpad()==pinpad_simple)
		{
			char * pc_l_DisplayTxt;

			// On the first line is displayed the current AID
			PPS_firstline();
			memclr( &Tab_first_line_name , sizeof( Tab_first_line_name ) );
			memcpy( &Tab_first_line_name , &Tab_Appli_Name[appli_index],Taille_LABEL );
			send_message_pinpad ((char *)Tab_first_line_name );

			// On the second line is displayed "OK(V)   OTHER(F)"
			PPS_newline();
			memclr( Tab_second_line_name , sizeof( Tab_second_line_name ) );

			pc_l_DisplayTxt = CUMESS_Read_Message(DEFAULT_TABLE, STD_MESS_OK_AUTRE, PSQ_Give_Language());
			sprintf((char *)Tab_second_line_name, pc_l_DisplayTxt);
			send_message_pinpad ( (char *)Tab_second_line_name );
		}

		Fct_Entry ( (TAB_ENTRY_FCT *)&t_annulcd );
		//if (PSQ_type_pinpad()==pinpad_simple)
		{
			PPS_Fct_Entry ( (TAB_ENTRY_FCT *)&tab_test );
		}
		fct_return = ttestall ( ENTRY | ENTRY_PPAD , TO_EXIT);
		if (fct_return & ENTRY)
		{
			// The merchant canceled, or inactivity timeout occured.
			PPS_Stop_Entry ();
			returned_char = Get_Entry (&buffer);
			// End of loop. appli_index is set to max application index + 1.
			appli_index = nb_appli + 1 ;
			no_end = 1;
		}
		else
		{
			if (fct_return & ENTRY_PPAD)
			{
				memclr( &buffer , sizeof(buffer) );
				returned_char =  PPS_Read_Entry ((BUFFER_SAISIE*)&buffer);
				Stop_Entry ();
				PPS_Stop_Entry  ();
				switch(returned_char)
				{
				case CR_SAISIE_PINPAD_VAL   :
					no_end = 1;
					break;
				case CR_SAISIE_PINPAD_OK    :
					switch (buffer.d_entry[0])
					{
					case TC_FONCTION_PPAD :
					case TC_SK4_PPAD :
						appli_index++;
						if (appli_index==nb_appli)
						{
							appli_index=0;
						}
						break;
					case TC_SK1_PPAD :
						if (appli_index==0)
						{
							appli_index=(nb_appli-1);
						}
						else
						{
							appli_index--;
						}
						break;
					}
					break;
				default :
				case CR_SAISIE_PINPAD_ANNUL :
					appli_index = nb_appli + 1 ;
					no_end = 1;
					break;
				}
			}
			else
			{
				PPS_Stop_Entry  ();
				Stop_Entry ();
			}
		}
	}
	while(no_end==0);
	PPS_clearline ();
	PPS_firstline ();
	PPS_clearline ();
	return(appli_index);
}


//===========================================================================
unsigned char Confirm_on_pinpad( unsigned char *aid  )
{
	unsigned char Is_Confirmed;
	TAB_ENTRY_FCT t_confirm_PP = {0x2800, MINUTE};
	TAB_ENTRY_FCT t_confirm_Com = {0x2000, MINUTE};
	unsigned char line1[17], line2[17];
	ENTRY_BUFFER buffer;
	unsigned short fct_return;
	unsigned char  returned_char;

	Is_Confirmed = FALSE;
	PPS10_firstline();

	if ( !PSQ_Est_pinpad_2_lignes() )
	{
		PPS10_clearline();
	}

	if ( PSQ_Est_pinpad_2_lignes() )
	{
		sprintf((char *)line1, "%.16s", aid);
		fct_return = send_message_pinpad ( (char*)line1 );
		PPS10_newline();
		sprintf((char *)line2,"CONFIRMATION ?" );
	}
	else
	{
		sprintf((char *)line2, "%.15s?", aid);
	}

	fct_return = send_message_pinpad ( (char*)line2 );

	Fct_Entry ( &t_confirm_Com );
	PPS_Fct_Entry ( &t_confirm_PP );

	fct_return = ttestall ( ENTRY | ENTRY_PPAD , TO_EXIT);

	if (fct_return & ENTRY)
	{
		// The merchant canceled, or inactivity timeout occured.
		PPS_Stop_Entry ();
		Is_Confirmed = FALSE;
	}
	else
	{
		if (fct_return & ENTRY_PPAD)
		{
			Stop_Entry ();
			memclr( &buffer , sizeof(buffer) );
			returned_char =  PP10_Read_Entry ((BUFFER_SAISIE*)&buffer);
			PPS_Stop_Entry  ();
			if (returned_char == CR_SAISIE_PINPAD_VAL)
				Is_Confirmed = TRUE;
			else if (returned_char == CR_SAISIE_PINPAD_ANNUL)
				Is_Confirmed = FALSE;
		}
		else
		{
			PPS_Stop_Entry  ();
			Stop_Entry ();
			Is_Confirmed = FALSE;
		}
	}

	PPS10_clearline ();
	PPS10_firstline ();
	PPS10_clearline ();

	return (Is_Confirmed);
}

//! @}

