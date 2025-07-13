#include "SDK30.H"
#include "VGE_UIM.h"



/**
 * @function     : CUTERMprintLine                                                       
 * @description   : This service prints the text and wait for the end of the job
 * ======================================================================= 
 * @param        : txt : Text to be printed.                                                                             
 * ======================================================================= 
 */
void printLine(char * txt)
{
	FILE *lp_printer;
	
	lp_printer = fopen("PRINTER", "w-");
	
	fprintf(lp_printer,"%s\n", txt);
	
	/* wait for print end */
	ttestall(PRINTER, 0);
	
	fclose(stdprt());
}

/**
 * @function:    ServiceResultUIM 
 * @description: Print the result of the service
 */
void ServiceResultUIM(char * i_pcService, int i_nResult)
{
	switch(i_nResult)
	{
		case UIM_SUCCESS				:
			printLine("\nResult : UIM_SUCCESS\n");
			break;
		case UIM_INVALID_PARAMETER		:
			printLine("\nResult : UIM_INVALID_PARAMETER\n");
			break;
		case UIM_CANCEL_PRESSED			:
			printLine("\nResult : UIM_CANCEL_PRESSED\n");
			break;
		case UIM_ERROR					:
			printLine("\nResult : UIM_ERROR\n");
			break;
		case UIM_INVALIDE_IP_ADRESS	:
			printLine("\nResult : UIM_INVALIDE_IP_ADRESS\n");
			break;
		case UIM_INVALIDE_SEPARATOR		:
			printLine("\nResult : UIM_INVALIDE_SEPARATOR\n");
			break;
		case UIM_INVALIDE_FORMAT		:
			printLine("\nResult : UIM_INVALIDE_FORMAT\n");
			break;
		case UIM_INVALIDE_TIME			:
			printLine("\nResult : UIM_INVALIDE_TIME\n");
			break;
		case UIM_INVALIDE_DATE			:
			printLine("\nResult : UIM_INVALIDE_DATE\n");
			break;
		case UIM_INPUT_PAN_ERROR		:
			printLine("\nResult : UIM_INPUT_PAN_ERROR\n");
			break;
		case UIM_INPUT_EXPDATE_ERROR	:
			printLine("\nResult : UIM_INPUT_EXPDATE_ERROR\n");
			break;
		case UIM_INPUT_CVV2_ERROR		:
			printLine("\nResult : UIM_INPUT_CVV2_ERROR\n");
			break;
		case UIM_INPUT_NUM_ERROR		:
			printLine("\nResult : UIM_INPUT_NUM_ERROR\n");
			break;
		case UIM_INPUT_ALPHA_NUM_ERROR	:
			printLine("\nResult : UIM_INPUT_ALPHA_NUM_ERROR\n");
			break;
		case UIM_TIME_OUT				:
			printLine("\nResult : UIM_TIME_OUT\n");
			break;
		case UIM_CANCEL_INPUT			:
			printLine("\nResult : UIM_CANCEL_INPUT\n");
			break;
		case UIM_CODE_LUHN_ERROR		:
			printLine("\nResult : UIM_CODE_LUHN_ERROR\n");
			break;
		default:
			printLine("\nResult : UIM_UNKNOWN\n");
			break;
	}
	printLine("************************\n\n");
}
