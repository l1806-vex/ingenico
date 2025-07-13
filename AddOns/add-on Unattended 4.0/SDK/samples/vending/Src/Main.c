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
	case GIVE_AID :
        break;
	case IS_FOR_YOU_AFTER :
		ret = is_for_you_after(No,&data->Param.IsForYouAfter.param_in,&data->Param.IsForYouAfter.param_out );
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

 int iAPP_Event( T_UCMC_IAC_SERVICE *pdata_p )
{
int iRet ;
T_UCMC_IAC_EVENT       *pEvent;
char cTemp[ 200 ];

 iRet = FCT_OK;
 
 pEvent = (void*)&pdata_p->Par.ucBuffer[0];

    switch( pEvent->usType )
   {
    
      case UCMC_EVENT_TYPE_USB:
         sprintf( cTemp, "Sample Event\nUsb") ;
      break;

      default:
         sprintf( cTemp, "Sample Event\n?? 0x%x", pEvent->usType ) ;
      break;
   }

 

   trace( 0x0E01, strlen( cTemp), cTemp );
   iLIBUCM_Display_Message( UCMC_DISPLAY, cTemp, 10 ) ;

 

   return( iRet );
}

 

int iAPPLIUCM_IAC( unsigned short usAppli_p , T_UCMC_IAC_SERVICE *pdata_p )
{
int iRet;

   iRet = FCT_OK;

   switch( pdata_p->usFct )
   {
      case UCMHOST_FCTAPP_EVENT:
         iRet = iAPP_Event( pdata_p  ) ;
         break;
      
      default:
         break;
   }
   return( iRet ) ;
}

 

int MainAppliUCMC_IAC(unsigned int iSize_p, T_UCMC_IAC_SERVICE *pdata_p)
{
 int          iRet;
 object_info_t info;
 
 ObjectGetInfo( OBJECT_TYPE_APPLI, pdata_p->usType_code, &info ) ;

 iRet = FCT_OK;
 
 switch( pdata_p->usService )
 {
  case SERVICE_APPLI_UCMC: 


   switch( pdata_p->usModule )
   {
    case UCMAPPLIMODULE_FCTAPP:
         iRet = iAPPLIUCM_IAC( pdata_p->usType_code, pdata_p ) ;
    break;

    
    default:
    break;
   }

  break;
  
  default:
   break;
 }

 

 return( iRet );
}
