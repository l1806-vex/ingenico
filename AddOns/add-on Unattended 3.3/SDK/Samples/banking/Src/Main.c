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
 * @Description: SDK30 sample application 
 * @Reference:    
 * @Comment:      
 *
 * @author        
 * @version       
 * @Comment:      
 * @date:         
 */
#include "SDK30.H"
#include "UCMTELIUM.H"

#include "UCMHOSTDLL.H"
#include "UCMCLIB.H"

#include "etat.h"

extern int after_reset         (NO_SEGMENT, void *,        S_TRANSOUT *);

#ifdef _EFT20_
int Main               (unsigned short typ_appli,unsigned short service,StructPt *data,unsigned int size);
#else
int Main(unsigned int size, StructPt *data)
#endif
{
	NO_SEGMENT No;
	int            ret;
	
	No = ApplicationGetCurrent();
	switch(data->service)
	{
	case AFTER_RESET :
		ret = after_reset(No,NULL,&data->Param.AfterReset.param_out);
        break;
	case DEBIT_OVER :
		break;
	case MORE_FUNCTION :
		ret = more_function(No,NULL,NULL);
        break;
	case IS_TIME_FUNCTION :
		ret = is_time_function(No,NULL,&data->Param.IsTimeFunction.param_out); 
		break;
	case TIME_FUNCTION :
        ret = time_function(No,NULL,NULL); 
		break;
	case TIME_FUNCTION_CHAINE : // French Bank Domain 
        break;
	case CONSULT :
		ret = consult(No,NULL,NULL);
        break;
	case MCALL :
		ret = mcall(No,NULL,NULL);
        break;
	case STATE :
		ret = state(No,NULL,NULL);
        break;
	case AUTO_OVER :
        break;
	case IS_NAME :
		ret = is_name(No,NULL,&data->Param.IsName.param_out);
        break;
	case IS_STATE :
		ret = is_state(No,NULL,&data->Param.IsState.param_out);
        break;
	case IS_EVOL_PG :
		ret = is_evol_pg(No,NULL,&data->Param.IsEvolPg.param_out);
        break;
	case IS_CHANGE_INIT :
        ret = is_change_init(No,NULL,&data->Param.IsChangeInit.param_out);
        break;
	case MODIF_PARAM :
        ret = modif_param(No, &data->Param.ModifParam.param_in, NULL);
		break;
	case IS_ORDER : // French Health Care Domain 
        break;
	case ORDER : // French Health Care Domain 
        break;
	case IS_SUPPR_PG : // French Health Care Domain 
        break;
	case IS_INSTALL_PG : // French Health Care Domain 
        break;
	case GET_ORDER : // French Health Care Domain 
        break;
	case IS_LIBELLE : // French Health Care Domain 
        break;
	case IS_DELETE :
        ret = is_delete(No,NULL,&data->Param.IsDelete.param_out);
        break;
	case EVOL_CONFIG : // French Bank Domain 
        break;
	case GIVE_MONEY : // French Bank Domain 
		break;
	case IDLE_MESSAGE :
        break;
	case COM_EVENT :
        break;
	case MODEM_EVENT :
        break;
	case KEYBOARD_EVENT :
        ret = keyboard_event(No,&data->Param.KeyboardEvent.param_in,&data->Param.KeyboardEvent.param_out);
		break;
	case GIVE_INFOS_CX : // French Bank Domain 
        break;
	case FILE_RECEIVED :
        ret = file_received(No,&data->Param.FileReceived.param_in,NULL);
        break;
	case MESSAGE_RECEIVED :
        break;
	case CARD_INSIDE : // French Health Care Domain
        break;
	case GIVE_INTERFACE : 
        break;
	case IS_BIN_CB : // French Bank Domain
        break;
	case IS_CARD_SPECIFIC : // French Health Care Domain
        break;
	case IS_FOR_YOU_BEFORE : 
	/*	ret = is_for_you_before(No,&data->Param.IsForYouBefore.param_in,&data->Param.IsForYouBefore.param_out);*/
        break;
	case GIVE_AID :
        break;
	case IS_FOR_YOU_AFTER :
		ret = is_for_you_after(No,&data->Param.IsForYouAfter.param_in,&data->Param.IsForYouAfter.param_out );
        break;
	case IS_CARD_EMV_FOR_YOU :
//		ret = is_card_emv_for_you(No,&data->Param.IsCardEmvForYou.param_in,&data->Param.IsCardEmvForYou.param_out );
        break;
	case DEBIT_EMV :
//		ret = debit_emv(No,&data->Param.DebitNonEmv.param_in,&data->Param.DebitNonEmv.param_out);
		break;
	case DEBIT_NON_EMV :
		ret = debit_non_emv(No,&data->Param.DebitNonEmv.param_in,&data->Param.DebitNonEmv.param_out);
        break;
	case SELECT_FUNCTION : // French Bank Domain
        break;
	case SELECT_FUNCTION_EMV : // French Bank Domain
        break;
	case GIVE_YOUR_DOMAIN :
		ret = give_your_domain(No,NULL,&data->Param.GiveYourType.param_out);
        break;
	case FALL_BACK : 
		ret = fall_back(No,&data->Param.FallBack.param_in,NULL);			
		break;
   case DEBIT_TPASS:
        break;
	}
	
	return(0);
}


extern int iAPPLIUCM_IAC( unsigned short usAppli_p , T_UCMC_IAC_SERVICE *pdata_p );

int iAPP_Protocol_Init( T_UCMC_IAC_SERVICE *pdata_p  )
{
int iRet;

   iRet = FCT_OK;

/* RUF */

   return( iRet );
}

 

/* application received message from Host */
int iAPP_Protocol_Sending( T_UCMC_IAC_SERVICE *pdata_p  )
{
int iRet;
char cTemp[ 1000 ];

   iRet = FCT_OK;

   pdata_p->usFct = 0;
   pdata_p->uiSize = 0;

   sprintf( cTemp, "Sample Received: %s", &pdata_p->Par.ucBuffer[0]);
   trace( 0x0E01, strlen( cTemp), cTemp ) ;

   switch( pdata_p->Par.ucBuffer[1] ) /* SES1042 */
   {
      case 'a':   /* reponse etat */
         
      break;

      case 'k': /* reponse solvabilite */
         if( pdata_p->Par.ucBuffer[11] != ' ' ) /* Si appli selectionnee Libelle non blanc */
         {
            if( pdata_p->Par.ucBuffer[5] == '0' )  /* CR OK */
            {
				sprintf( cTemp, "Dem enreg OK. Cr solv= %s", &pdata_p->Par.ucBuffer[0]);
				trace( 0x0E01, strlen( cTemp), cTemp ) ;
                /* demande enreg */ 

            }
            else
            {
               /* demande enreg montant nul */

               sprintf( cTemp, "Dem enreg 0. Cr solv: %s", &pdata_p->Par.ucBuffer[0]);
               trace( 0x0E01, strlen( cTemp), cTemp ) ;
            }
         }

      break;
   }

   return( iRet );
}

 

/* Host read message in application */
int iAPP_Protocol_Reading( T_UCMC_IAC_SERVICE *pdata_p  )
{
int iRet;
int iDem;

   iRet = FCT_OK;

   /* Add status message */
   pdata_p->usFct = UCMHOST_PROTOCOL_SEND;

   iDem = 1; /* exemple */

   switch( iDem )
   {
      case 1: /* dem etat */
         /* 1042: message state request */
         sprintf( (char *)&pdata_p->Par.ucBuffer[0],"%s","AA000" );
         pdata_p->uiSize = strlen( (char *)&pdata_p->Par.ucBuffer[0] ) ;
      break;

      case 2: /* dem solv */
         sprintf( (char *)&pdata_p->Par.ucBuffer[0],"%s","AK016100000200509781D" );
         pdata_p->uiSize = strlen( (char *)&pdata_p->Par.ucBuffer[0] ) ;
      break;

      case 3: /* dem enreg Ok */
         sprintf( (char *)&pdata_p->Par.ucBuffer[0],"%s","AL01100000200978" );
         pdata_p->uiSize = strlen( (char *)&pdata_p->Par.ucBuffer[0] ) ;
      break; 

      case 4: /* dem enreg KO montant null */
         sprintf( (char *)&pdata_p->Par.ucBuffer[0],"%s","AL01100000000978" );
         pdata_p->uiSize = strlen( (char *)&pdata_p->Par.ucBuffer[0] ) ;
      break;
   }

   return( iRet );
}


int iAPPLIUCM_IAC_PROTOCOL( unsigned short usAppli_p , T_UCMC_IAC_SERVICE *pdata_p )
{
int iRet;
unsigned char ucTemp[ 50 ];

 iRet = FCT_OK;

 switch( pdata_p->usFct )
 {
  case UCMHOST_PROTOCOL_INIT:
   iRet = iAPP_Protocol_Init( pdata_p );
  break;
  
  case UCMHOST_PROTOCOL_SEND:
   iRet = iAPP_Protocol_Sending( pdata_p ) ;
    break;
  
  case UCMHOST_PROTOCOL_READ:
   iRet = iAPP_Protocol_Reading( pdata_p ) ;
  break;

  default:
   iRet = UCMERR_IAC_NO_FCT;
   
   sprintf( (char *)ucTemp, "Sample6E UCMC IACPROTOCOL Fct %04X %d\n", pdata_p->usFct, iRet );
         trace( 0x0E01, strlen( (char *)ucTemp), ucTemp ) ;

 

   upload_diagnostic_txt( ucTemp ) ;
   iLIBUCM_Print_Message( UCMC_PRINT, (char *)ucTemp ) ;
  break;
  
 }

 return( iRet ) ;
}


	
int MainAppliUCMC_IAC(unsigned int iSize_p, T_UCMC_IAC_SERVICE *pdata_p)
{
	int          iRet;
	object_info_t info;
	unsigned char ucTemp[ 100];
	
	ObjectGetInfo( OBJECT_TYPE_APPLI, pdata_p->usType_code, &info ) ;

	iRet = FCT_OK;
	
	switch( pdata_p->usService )
	{
		case SERVICE_APPLI_UCMC:	
			switch( pdata_p->usModule )
			{
				case UCMAPPLIMODULE_FCTAPP:
					iRet = iAPPLIUCM_IAC( pdata_p->usType_code, pdata_p ) ;
					
					if( iRet < 0 )
					{
						sprintf( (char *)ucTemp, "APPLIUCMC IAC TLP FCT %04X %d\n", pdata_p->usFct, iRet );
						upload_diagnostic_txt( ucTemp ) ;
					}
										
				break;
				
				case UCMAPPLIMODULE_PROTOCOL:
					iRet = iAPPLIUCM_IAC_PROTOCOL( pdata_p->usType_code, pdata_p ) ;

				break;    
				
				default:
					iRet = UCMERR_IAC_NO_MODULE;
					sprintf( (char *)ucTemp, "APPLIUCMC IAC Module %04X not exist %d\n",
						pdata_p->usModule, iRet );
					upload_diagnostic_txt( ucTemp ) ;

				break;
			}

		break;
		
		default:
			iRet = UCMERR_IAC_NO_SERVICE;
			sprintf( (char *)ucTemp, "APPLIUCMC IAC Service %04X not exist %d\n",
						pdata_p->usModule, iRet );
			upload_diagnostic_txt( ucTemp ) ;

			break;
	}

	return( iRet );
}
