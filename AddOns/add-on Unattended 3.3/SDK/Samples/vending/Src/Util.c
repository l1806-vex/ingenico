/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "SDK30.h"
#include "UCMTELIUM.h"

#include "UCMHOSTDLL.h"
#include "UCMCLIB.h"
#include "UCMSTARTDLL.H"


/*
*----------------------------------------------------------------------------
* UTIL_InitStruct_ParamVmcMsg
*----------------------------------------------------------------------------
* Description  : Initialise T_UCMHOST_DA_PARAM_MSGV3 structure
*                
*              :
* Parameter    : 
*                psParamDa_p : pointer to T_UCMHOST_DA_PARAM_MSGV3 structure
*               
*              :
* Return       :
*----------------------------------------------------------------------------
*/
void UTIL_InitStruct_ParamVmcMsg ( T_UCMHOST_DA_PARAM_MSGV3 * pParamDaMsg_p )
{
   strcpy ( (char *)pParamDaMsg_p->tucIdleMsg ,  "   * SAMPLE *  "
									             "\n     INSERT	"   
									             "\n   YOUR CARD  ");
   strcat((char *)pParamDaMsg_p->tucIdleMsg,"\n\\dd/\\mm/\\yyyy \\hh:\\ii");		// to display date (format is free..)


   strcpy ((char *)pParamDaMsg_p->tucMsgDaNonInit ,"\n    SYSTEM     \nNOT INITIALISED");
   strcpy ((char *)pParamDaMsg_p->tucMsgCommunicationVmcKo ,"\n COMMUNICATION \n     ERROR ") ;
   strcpy ((char *)pParamDaMsg_p->tucMsgProductSelected ,"") ; // selection first disabled
   strcpy ((char *)pParamDaMsg_p->tucMsgProductPriceNotDefined ,"\n INVALID CHOICE \n  REMOVE CARD") ;
}


/*
*----------------------------------------------------------------------------
* UTIL_InitStruct_ParamVmc
*----------------------------------------------------------------------------
* Description  : Initialise T_UCMHOST_DA_PARAM structure
*                
*              :
* Parametre    : 
*                psParamDa_p : pointer to T_UCMHOST_DA_PARAM structure
*              : 
*              :
* Retour       : 
*----------------------------------------------------------------------------
*/
void UTIL_InitStruct_ParamVmc ( T_UCMHOST_DA_PARAMV5 * pParamDa_p )
{
int                    iIndx1 ;

	memset(pParamDa_p,0,sizeof(T_UCMHOST_DA_PARAMV5));

	
   pParamDa_p->ucValidity  = 1 ;	// 1 DLL is active                                        
	// 0 DLL is not active                                                                  
	strcpy ( ( char * )pParamDa_p->tucTerminalNumber, "0123456789" ) ;                      
	pParamDa_p->ucVmcType [  0 ] = 0x30 ; /* electronic VMC */                              
	pParamDa_p->ucVmcType [  1 ] = 0x31 ;                                                   
                                                                                           
	pParamDa_p->usiTimeOutIfNoSelection = 30 ; //seconds                                    
	pParamDa_p->usiTimeOutBuzzer        = 5 ;  //seconds                                    
	pParamDa_p->usiBuzzerDuration       = 1 ;  //seconds                                    
	pParamDa_p->ucMultivendPossible     = 1 ; // 1 multi vend                               
	   									      // 0 single vend                                    
                                                                                           
	pParamDa_p->ucPriceHolding          = 1 ; //1 Prices defined by UCM                     
										      //0 Prices defined by VMC                              
                                                                                           
	pParamDa_p->ucDigitNumber           = 2 ;  //999.99                                     
	pParamDa_p->uiScaleFactor          = 1 ;                                               
                                                                                           
	strcpy ( (char *)pParamDa_p->tucCurrencyLabel, "EUR" ) ;
	strcpy ( (char *)pParamDa_p->tucCurrencyCode, "978" ) ;
                                                                                           
                                                                                           
	pParamDa_p->ucNbSelection = 0;                                                           
                                                                                           

	if (pParamDa_p->ucPriceHolding==1)
	{
		for ( iIndx1 = 0 ; 	iIndx1 < 100; iIndx1++ )
		{

			pParamDa_p->tPriceTable [pParamDa_p->ucNbSelection ].ucNumSelection = iIndx1 ;
			pParamDa_p->tPriceTable [pParamDa_p->ucNbSelection ].ucValiditePrixEspece	= 1 ;    // 0 if not defined
			pParamDa_p->tPriceTable [pParamDa_p->ucNbSelection ].uiPrixEspece			= 40 ;      // cts  price for coin vend
			pParamDa_p->tPriceTable [pParamDa_p->ucNbSelection ].ucValiditePrixCarte	= 1 ;	   // 0 if not defined
			pParamDa_p->tPriceTable [pParamDa_p->ucNbSelection ].uiPrixCarte			= 30 ;	   // cts  price for cashless paiement

			pParamDa_p->ucNbSelection++ ;
		}
	}

   pParamDa_p->usTimeOutIfSelected  = 0 ;    	                                             /* second */            
   pParamDa_p->ucVendingMode        = UCMHOST_VENDING_MODE_BALANCE_FIRST ;                   /* Card insertion is the first operation*/                 
   pParamDa_p->ucDisplayPrice       = UCMHOST_DISPLAY_PRICE_NONE ;
	pParamDa_p->usiTimeOutVM         = 90 ;      /* see doc SMO-SPE-0152 § T_UCMC_DA_PARAMV5 structure */
	pParamDa_p->uiDllParameters      = 0x00 ;    /* see doc SMO-SPE-0152 § T_UCMC_DA_PARAMV5 structure */	
	pParamDa_p->usiCashLessAdress    = 0x10 ;    /* see doc SMO-SPE-0152 § T_UCMC_DA_PARAMV5 structure */
	pParamDa_p->ucDisplayDa          = 0x00 ;    /* see doc SMO-SPE-0152 § T_UCMC_DA_PARAMV5 structure */
}  
   
