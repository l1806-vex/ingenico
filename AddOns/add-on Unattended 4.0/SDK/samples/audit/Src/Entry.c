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
#include "UCMTELIUM.h"
#include "UCMHOSTDLL.h"
#include "UCMCLIB.h"
#include "Audit_interface.h"
#include "DEXUCS_interface.h"
#include "DDCMP_interface.h"
#include "GATEWAY_interface.h"



static const char szDate[] = "Date:%.2s/%.2s/%.2s  %.2s:%.2s\n";
static const unsigned char appname[]    = "AUDIT SAMPLE";

#define __1_SECONDS__	100
#define __ENTER_KEY		-1
#define __BACK_KEY		-2
#define __EXIT_KEY		-3

int			i,select;	
unsigned char     	cr,returned;
ENTRY_BUFFER    	buf_entry;
//int              	MAXX;
//int               	MAXY; 

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

int AUDIT_DexUcs ( void ) 
{
unsigned long    ulBlock ;

int	           iReturn ;
int		        iSize ;
int              iBlockSize ;

DEXUCS_HANDLE    hHandle ;

T_DEXUCS_SESSION sHandshake1 ;
T_DEXUCS_SESSION sHandshake2 ;

NO_SERIE		     tucSN ;

unsigned char	  ucResponseCode ;

unsigned char    ucBuf [100] ;
unsigned char    ucBlockDta [DEXUCS_MAX_BLOCK_SIZE+1] ;



   iReturn = DEXUCSlib_open ( ) ;

  	if ( iReturn != 0 )
	{
      sprintf ( (char*)ucBuf, "*DEXUCSlib_open return %d", iReturn ) ;
		iLIBUCM_Display_Message ( UCMC_DISPLAY, (char *)ucBuf, __1_SECONDS__*2 );
      return ( STOP ) ;
	}


   iReturn = DEXUCS_Connect ( &hHandle, (unsigned char*)"COM0", 0 ) ; /* EVA-DTS audit is done via COM0 port */
   if ( iReturn != 0 )
   {
      sprintf ( (char*)ucBuf, "*DEXUCS_Connect return %d", iReturn ) ;
      iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)ucBuf, __1_SECONDS__*2 );

     	DEXUCS_Disconnect(hHandle);
      return ( STOP ) ;
   }

	memset ( &sHandshake1, 0, sizeof ( sHandshake1 ) ) ;
	memset ( &sHandshake2, 0, sizeof ( sHandshake2 ) ) ;

	iReturn = STOP ;

	memset ( tucSN, 0, sizeof ( tucSN ) ) ;
	
	PSQ_Donner_noserie ( (char*) tucSN ) ;	// ID = INGxxxxxxx ING+serial nb
	memcpy ( &sHandshake1.ucCommID [ 0 ], "ING", 3 ) ;
	memcpy ( &sHandshake1.ucCommID [ 3 ], &tucSN[1], 7 ) ;
	
	sHandshake1.ucRevision = 1 ;
	sHandshake1.ucLevel    = 1 ;
	iReturn = DEXUCS_StartAudit ( hHandle, &sHandshake1, &sHandshake2, &ucResponseCode ) ;

   if ( iReturn == _DEXUCS_OK )
	{
		ulBlock         = 0 ;
		iSize           = 0 ;
		do
		{
			ucResponseCode = 0 ;
			iBlockSize     = DEXUCS_MAX_BLOCK_SIZE ;
			
			iReturn = DEXUCS_ReadAudit ( hHandle, DEXUCS_BLOCK_NEXT, &iBlockSize, ucBlockDta ) ;	//-> read one block
			
			if ( iReturn == _DEXUCS_OK ) 
			{
				ulBlock++ ;
				iSize += iBlockSize ;

            /*** Write data (ucBlockDta)into local file ***/
				/* if there is enough place in the local file
                  write data
               else
                  error management
               end if
            */
			}
		} while ( iReturn == _DEXUCS_OK ) ;

      if ( iReturn == _DEXUCS_EOT )
      {
         iReturn = FCT_OK ;
      }
      else
      {
         iReturn = STOP ;	
      }
   }
   else
   {
      iReturn = STOP ;
   }


  	DEXUCS_Disconnect(hHandle);
 	DEXUCSlib_close();

   return ( iReturn ) ;
}

int AUDIT_Ddcmp ( void )
{
int	           iReturn ;

DDCMP_HANDLE     hHandle ;

unsigned char    ucBuf [ 100 ] ;

unsigned char  * pucData ;
unsigned short   usDataLength ;


	iReturn = DDCMPlib_open ( ) ;

	if ( iReturn != FCT_OK )
	{
      sprintf ( (char*)ucBuf, "*DDCMPlib_open return %d", iReturn ) ;
		iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)ucBuf, __1_SECONDS__*2 );
      return STOP;			
	}

	iReturn = DDCMP_Connect ( &hHandle, (unsigned char*)"COM0", 38400 ) ;       /* EVA-DTS audit is done via COM0 port */
	if ( iReturn != FCT_OK )
	{
      sprintf ( (char*)ucBuf, "*DDCMP_Connect return %d", iReturn ) ;
		iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)ucBuf, __1_SECONDS__*2 );
      DDCMPlib_close ( ) ;
      return STOP;			
	}

	iReturn = DDCMP_LinkInitialisation ( hHandle, _DDCMP_ALL_DEVICE ) ;
	if ( iReturn != _DDCMP_END )
	{
		sprintf ( (char*)ucBuf, "*DDCMP_LinkInitialisation return %d", iReturn ) ;
      iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)ucBuf, __1_SECONDS__*2 );
      DDCMP_Disconnect( hHandle ) ;
      DDCMPlib_close ( ) ;
		return STOP;			
	}

	pucData         = NULL ;
	usDataLength    = 0 ;
	
	do
	{
      iReturn = DDCMP_ReadData( hHandle, _DDCMP_AUDIT_COLLECTION_LIST, (void *) &pucData, &usDataLength ) ;

		if ( ( ( iReturn == _DDCMP_CONTINUE ) || ( iReturn == _DDCMP_END ) ) && ( usDataLength > 0 ) )
		{
            /*** Write data (pucData)into local file ***/
				/* if there is enough place in the local file
                  write data
               else
                  error management
               end if
            */
		}
   }
   while ( iReturn == _DDCMP_CONTINUE ) ; 


   if ( iReturn == _DDCMP_END )
   {
      iReturn = FCT_OK ;
   }
   else
   {
      iReturn = STOP ;	
   }

   DDCMP_FinishCommunications( hHandle );
   DDCMP_Disconnect( hHandle );
	DDCMPlib_close ( ) ;
	return ( iReturn ) ;
}

int AUDIT_Gateway ( void )
{
int	           iReturn ;
int 				  iWatchDog ;
int				  iLoop ;

unsigned char    ucBuf [ 100 ] ;

unsigned char  * pucData ;
unsigned short   usDataLength ;


	iReturn = GATEWAYlib_open ( ) ;

   if ( iReturn != FCT_OK )
	{
      sprintf ( (char*)ucBuf, "*GATEWAYlib_open return %d", iReturn ) ;
		iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)ucBuf, __1_SECONDS__*2 );
      return STOP;			
	}

	iReturn = Gateway_LaunchAudit ( 0x01 ) ;

	if ( iReturn != _GATEWAY_OK )
	{
		sprintf ( (char*)ucBuf, "*Gateway_LaunchAudit return %d", iReturn ) ;
  		iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)ucBuf, __1_SECONDS__*2 );
		Gateway_EndAudit ( ) ;
		GATEWAYlib_close ( ) ;
		return STOP;			
	}

	iWatchDog    = 0 ;
	iLoop        = 0 ;
	pucData      = NULL ;
	usDataLength = 0 ;
	do
   {
   	iReturn = Gateway_ReadData( (void *) &pucData, &usDataLength );
      
      if ( iReturn == _GATEWAY_CONTINUE )
      {
      	iLoop++ ;
      }

      if ( iLoop >= 120 )
      {
      	iWatchDog = 1 ;
      }

      ttestall( 0, 50 );
      
   } while ( ( iReturn == _GATEWAY_CONTINUE ) && ( !iWatchDog ) ) ;
     
   Gateway_EndAudit ( ) ;

	if ( iWatchDog || ( iReturn != _GATEWAY_END ) )
	{
		sprintf ( (char*)ucBuf, "*Gateway_ReadData return %d; WatchDog %d", iReturn, iWatchDog ) ;
      iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)ucBuf, __1_SECONDS__*2 );
		Gateway_EndAudit ( ) ;
		GATEWAYlib_close ( ) ;
		return STOP;			
	}

   
   /*** Write data (pucData) into local file ***/
   /* if there is enough place in the local file
         write data
      else
         error management
      end if
   */

   Gateway_EndAudit ( ) ;
	GATEWAYlib_close ( ) ;
	return ( iReturn ) ;
}

int more_function( NO_SEGMENT no, void *p1, void *p2 )
{
int                prec;
ENTRY_BUFFER       buf;
StructList         Menu;
unsigned char      Cr;
	
	prec = StateHeader(0);
	
	do
	{
		default_menu(&Menu) ;
		Menu.MyWindow.shortcommand  = _ON_ ;                 
		Menu.MyWindow.title         = (unsigned char *)"SAMPLE MENU" ;
		Menu.tab[0]  = (unsigned char *)"Audit DEX-UCS" ;
		Menu.tab[1]  = (unsigned char *)"Audit DDCMP" ;
		Menu.tab[2]  = (unsigned char *)"Audit GATEWAY" ;
		Menu.tab[3]  = NULL;

		G_List_Entry((void*)&Menu) ;
		ttestall(ENTRY,0) ;
		Cr = Get_Entry(&buf) ;

		if ( Cr == CR_ENTRY_OK )
		{
			switch (buf.d_entry[0])
			{
			case 0:
            iLIBUCM_Display_Message ( UCMC_DISPLAY, " DEX-UCS audit\n in progress...", __1_SECONDS__*2 );
				if ( AUDIT_DexUcs ( ) == FCT_OK )
				{
               iLIBUCM_Display_Message ( UCMC_DISPLAY, " DEX-UCS audit\n    succeded", __1_SECONDS__*2 );
				}
            else 
            {
               iLIBUCM_Display_Message ( UCMC_DISPLAY, " DEX-UCS audit\n    failure", __1_SECONDS__*2 );
            }
				break;

			case 1:
            iLIBUCM_Display_Message ( UCMC_DISPLAY, "  DDCMP audit\n in progress...", __1_SECONDS__*2 );
				if ( AUDIT_Ddcmp ( ) == FCT_OK )
				{
               iLIBUCM_Display_Message ( UCMC_DISPLAY, "  DDCMP audit\n    succeded", __1_SECONDS__*2 );
				}
            else 
            {
               iLIBUCM_Display_Message ( UCMC_DISPLAY, "  DDCMP audit\n    failure", __1_SECONDS__*2 );
            }
				break;

			case 2:
            iLIBUCM_Display_Message ( UCMC_DISPLAY, " GATEWAY audit\n in progress...", __1_SECONDS__*2 );
				if ( AUDIT_Gateway ( ) == FCT_OK )
				{
               iLIBUCM_Display_Message ( UCMC_DISPLAY, " GATEWAY audit\n    succeded", __1_SECONDS__*2 );
				}
            else 
            {
               iLIBUCM_Display_Message ( UCMC_DISPLAY, " GATEWAY audit\n    failure", __1_SECONDS__*2 );
            }

				break;
			}
		}
		else
		{
			prec  =IsHeader();
			if (Cr==CR_ENTRY_CANCEL)   return(FCT_OK);
			if (Cr==CR_ENTRY_TIME_OUT) return(FCT_OK);
		}
	}
	while (1);
	
	return (FCT_OK);
}


void _Format_Error (int iRet, unsigned char * szMsg)
{
	switch (iRet)
	{
		case _AUDIT_NOT_EXIST: strcpy ((char*)szMsg,"Not Exist");break;
		case _AUDIT_EOF: strcpy ((char*)szMsg,"End of File");break;
		case _AUDIT_OUT_OF_MEMORY: strcpy ((char*)szMsg,"Out Of Mem");break;
		case _AUDIT_OVERFLOW: strcpy ((char*)szMsg,"OverFlow");break;
		case _AUDIT_INVALID_PARAMETERS: strcpy ((char*)szMsg,"Invalid Prm");break;
		case _AUDIT_UNAVAILABLE: strcpy ((char*)szMsg,"Unavailable");break;
		case _AUDIT_UNDEFINED: strcpy ((char*)szMsg,"Undefined");break;
		case _AUDIT_ERROR: strcpy ((char*)szMsg,"Error");break;
		case _AUDIT_OK: strcpy ((char*)szMsg,"OK");break;
		default:strcpy ((char*)szMsg,"Unknown ?");break;
	}	
		
}

int after_reset( NO_SEGMENT no, void *p1, S_TRANSOUT *etatseq )
{
	//
	unsigned char chgt;
	TYPE_CHGT  type;
	unsigned char szMessage[132+1];
	unsigned char szReturn[132+1];
	int iRet;

	// Test if it is the first execution of the application.
	first_init( no, &chgt, (unsigned char*)&type);
	if ( chgt == 0xFF )
	{ 
		AUDIT_Start_Services();
		sprintf((char*)szMessage,"%s\nStart_Services",appname);
	}
	else 
	{
		// Not the fist execution.

		sprintf((char*)szMessage,"%s\nNothing to Do",appname);
	}

	iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)szMessage, __1_SECONDS__ );

	
	iRet=AUDIT_Is_Available();

	if (iRet==_AUDIT_OK)
	{

		sprintf((char*)szMessage,"Audit OK\nVersion : %d",AUDIT_Get_Version());

	}
	else
	{
		_Format_Error(iRet,szReturn);
		sprintf((char*)szMessage,"Audit KO\n->%s",szReturn);
	}

	iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)szMessage, __1_SECONDS__*2 );

	return FCT_OK;
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

int is_delete(NO_SEGMENT no,void *paramin,S_DELETE *paramout)
{

	unsigned char szMessage[132+1];

	paramout->deleting=DEL_YES;
	
	AUDIT_Stop_Services();
	sprintf((char*)szMessage,"%s\nAUDIT_Stop_Services",appname); // --> to kill Audit services

	iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)szMessage, __1_SECONDS__ );

	return (FCT_OK);
}

int state (NO_SEGMENT noappli,void *p1,void *p2)
{
	return FCT_OK;
}


int mcall (NO_SEGMENT noappli,void *p1,void *p2)
{
	return FCT_OK;
}

int consult (NO_SEGMENT noappli,void *p1,void *p2)
{
	return FCT_OK;
}

int time_function (NO_SEGMENT noappli,void *p1,void *p2)
{	
	unsigned char szMessage[132+1];
	unsigned char szReturn[132+1];
	unsigned char szData[1024];
	unsigned short usType,usRecordNum;
	int iSize,iDataSize,iReadCnt,iReturn;
	T_AUDIT_STAT sAuditStat;

	iSize=AUDIT_Get_Size(); // to get size of the current audit file... size != useful size of records
							// this size includes headers, management data...

	if (iSize==0)
	{
		if (AUDIT_File_Exist()!=FCT_OK)
		{
			return FCT_OK;
		}
		else
		{
			// backup file already existed
			// --> audit file read but not deleted
			iSize=1; // to continue processing
			iLIBUCM_Display_Message ( UCMC_DISPLAY, "Backup File\nalready existed", __1_SECONDS__ );
		}
	}

	if (iSize>0)
	{
		
		/* AUDIT_Read_File */
		if (1)
		{
			iReadCnt=0;
			do
			{
				iDataSize=1024;
				iReturn=AUDIT_Read_File( OPTION_NONE,   &iDataSize,	(char*)szData);
				if (iReturn==FCT_OK)
				{
					iReadCnt++;
					sprintf((char*)szMessage,"Block %d\nSize %d",iReadCnt,iDataSize);
					iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)szMessage, __1_SECONDS__ );
				}
				
			}while(iReturn==FCT_OK);


			_Format_Error(iReturn,szReturn);
			sprintf((char*)szMessage,"AUDIT_Read_File\n->%s",szReturn);
			iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)szMessage, __1_SECONDS__ );
		}


		/* AUDIT_Read_Record */
		if (0)
		{
			iReadCnt=0;
			do
			{
				iDataSize=1024;
				//usType=RECORD_TYPE_? if OPTION_FILTER_TYPE
				iReturn=AUDIT_Read_Record( OPTION_NONE, &usType,&usRecordNum, &iDataSize,	(char*)szData);
				if (iReturn==FCT_OK)
				{
					iReadCnt++;
					sprintf((char*)szMessage,"Record no%d\nType %x Sz %d",usRecordNum,usType, iDataSize);
					iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)szMessage, __1_SECONDS__*2 );
					iDataSize=1024;
				}
				
			}while(iReturn==FCT_OK);


			_Format_Error(iReturn,szReturn);
			sprintf((char*)szMessage,"AUDIT_Read_Record\n->%s",szReturn);
			iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)szMessage, __1_SECONDS__*2 );
		}


		/* AUDIT_Get_Stats */
		{
			usType=RECORD_TYPE_ALL; 
			iReturn=AUDIT_Get_Stats( usType, sizeof(sAuditStat),	&sAuditStat);
			if (iReturn==FCT_OK)
			{
				sprintf((char*)szMessage,"%ld Record(s)\nstored (%ld)",sAuditStat.ulStored, sAuditStat.ulStoredSize);
				iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)szMessage, __1_SECONDS__ *2);

				sprintf((char*)szMessage,"%ld Record(s)\nlost (%ld)",sAuditStat.ulFailed,sAuditStat.ulFailedSize);
				iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)szMessage, __1_SECONDS__ *2);

			}
			else
			{//error
				_Format_Error(iSize,szReturn);
				sprintf((char*)szMessage,"Get Stats KO\n->%s",szReturn);
				iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)szMessage, __1_SECONDS__ *2);
			}
		}

		iReturn=AUDIT_Delete_File();
		sprintf((char*)szMessage,"Delete File\n->%s",szReturn);
		iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)szMessage, __1_SECONDS__ );

	}
	else
	{ // error
		_Format_Error(iSize,szReturn);
		sprintf((char*)szMessage,"Get Size KO\n->%s",szReturn);
		iLIBUCM_Display_Message ( UCMC_DISPLAY, (char*)szMessage, __1_SECONDS__ );
	}
	return (FCT_OK);
}


int is_evol_pg(NO_SEGMENT noappli, void *p1, S_ETATOUT *param_out)
{
	S_ETATOUT etatout;
	int       retour;
	memcpy(&etatout, param_out, sizeof(etatout));
	etatout.returned_state[etatout.response_number].state.response=REP_OK;
	memcpy(param_out,&etatout,sizeof(etatout));
	retour = is_name (noappli, PT_NULL, param_out);
	return(FCT_OK);		 
}

int is_time_function(NO_SEGMENT noappli, void *p1, S_ETATOUT *param_out)
{
	S_ETATOUT etatout;
	int       retour;

	memcpy(&etatout, param_out, sizeof(etatout));
	
	if (	(AUDIT_Get_Size()!=0)			// current audit not empty
		||	(AUDIT_File_Exist()==FCT_OK)	// backup file already existed
		)
	{
		etatout.returned_state[etatout.response_number].state.response=REP_OK;
	}
	else
	{
		etatout.returned_state[etatout.response_number].state.response=REP_KO;
	}
	
	memcpy(param_out,&etatout,sizeof(etatout));

	retour = is_name (noappli, PT_NULL, param_out);

	return(FCT_OK);		 
}


int is_change_init(NO_SEGMENT noappli, void *p1, S_ETATOUT *param_out)
{
	S_ETATOUT etatout;
	int       retour;
	memcpy(&etatout, param_out, sizeof(etatout));
	// accept all 
	etatout.returned_state[etatout.response_number].state.mask=0;
	memcpy(param_out,&etatout,sizeof(etatout));
	retour = is_name (noappli, PT_NULL, param_out);
	return(FCT_OK);		 
}

int modif_param(NO_SEGMENT noappli, S_MODIF_P *param_in, void *p2)
{
	return(FCT_OK);
}


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
	MesServices[i].serv_id   = IS_DELETE;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = STATE;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = MCALL;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = CONSULT;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_EVOL_PG;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_TIME_FUNCTION;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = TIME_FUNCTION;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = IS_CHANGE_INIT;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;
	MesServices[i].appli_id  = no;
	MesServices[i].serv_id   = MODIF_PARAM;
	MesServices[i].sap       = (T_SERVICE_FUNCTION)Main;
	MesServices[i].priority  = 10;
	i++;

	ServiceRegister(i,MesServices);

	return FCT_OK;
}

void entry(void)
{
	object_info_t info;
	
	ObjectGetInfo(OBJECT_TYPE_APPLI, ApplicationGetCurrent(),&info);
	give_interface(info.application_type, NULL, NULL);
}

