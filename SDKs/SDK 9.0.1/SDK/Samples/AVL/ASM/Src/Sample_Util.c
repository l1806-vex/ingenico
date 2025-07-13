#include "SDK30.H"
#include "VGE_ASM.h"


/**
 * @function     : CUTERMprintLine                                                       
 * @description  : This service prints the text and wait for the end of the job
 * ======================================================================= 
 * @param        : *xs_text : Text to be printed.                                                                             
 * ======================================================================= 
 */
void CUTERMprintLine(char *xs_text)
{
	FILE *lp_printer;
	
	lp_printer = fopen("PRINTER", "w-");
	
	fprintf(lp_printer,"%s\n", xs_text);
	
	/* wait for print end */
	ttestall(PRINTER, 0);
	
	fclose(stdprt());
}

/**
 * @function:    ServiceResult 
 * @description: Convert service Result to string
 *-----------------------------------------------------------------------------
 * @param:       - i_nResult : result in integer format
 * @param out:   - o_pcResult : result in string format 
 *-----------------------------------------------------------------------------
 */
static void ServiceResult(char * o_pcResult, int i_nResult)
{
	char l_acResult [40];

	memclr(l_acResult, sizeof(l_acResult));
	
	switch(i_nResult)
	{
		case ASM_SUCCESS				:
			sprintf(l_acResult,"ASM_SUCCESS");
			break;

		case ASM_CALENDAR_DOES_NOT_EXIST	:
			sprintf(l_acResult,"ASM_CALENDAR_DOES_NOT_EXIST");
			break;

		case ASM_TASK_DOES_NOT_EXIST		:
			sprintf(l_acResult,"ASM_TASK_DOES_NOT_EXIST");
			break;

		case ASM_CALENDAR_EXIST			:
			sprintf(l_acResult,"ASM_CALENDAR_EXIST");
			break;

		case ASM_INVALID_DATE			:
			sprintf(l_acResult,"ASM_INVALID_DATE");
			break;

		case ASM_INVALID_PARAM			:
			sprintf(l_acResult,"ASM_INVALID_PARAM");
			break;

		case ASM_CALL_FAILURE			:
			sprintf(l_acResult,"ASM_CALL_FAILURE");
			break;

		case ASM_NO_TASK_TO_EXECUTE		:
			sprintf(l_acResult,"ASM_NO_TASK_TO_EXECUTE");
			break;

		case ASM_MAX_CALENDAR_ERROR		:
			sprintf(l_acResult,"ASM_MAX_CALENDAR_ERROR");
			break;

		case ASM_MAX_TASK_ERROR			:
			sprintf(l_acResult,"ASM_MAX_TASK_ERROR");
			break;

		case ASM_TASK_ALREADY_EXIST		:
			sprintf(l_acResult,"ASM_TASK_ALREADY_EXIST");
			break;

		case ASM_UPDATE_ERROR			:
			sprintf(l_acResult,"ASM_UPDATE_ERROR");
			break;

		case ASM_TASK_IN_PROGRESS		:
			sprintf(l_acResult,"ASM_TASK_IN_PROGRESS");
			break;

		default							:
			sprintf(l_acResult,"ASM_UNKNOWN");
			break;
	}

	strcpy(o_pcResult, l_acResult);
}


/**
 * @function:    ASM_PrintResult 
 * @description: Print the result of a function 
 */
void ASM_PrintResult(char * i_acCommand, int i_iRet, char *i_acOptional1, char * i_acOptional2)
{
	char acText[50];
	char acReturn[50];
	
	CUTERMprintLine("***********************");
	CUTERMprintLine(i_acCommand);
	CUTERMprintLine("***********************\n");
	
	if (strlen(i_acOptional1) != 0)
		CUTERMprintLine(i_acOptional1);

	ServiceResult(acReturn, i_iRet);
	sprintf(acText,"\nResult= %s\n",acReturn);
	
	CUTERMprintLine(acText);

	if (strlen(i_acOptional2) != 0)
		CUTERMprintLine(i_acOptional2);

	CUTERMprintLine("\n***********************");
	CUTERMprintLine("\n\n");
}

/**
 * @function:    L_PrintTaskInfoInString
 * @description: Prints external task infos
 *-----------------------------------------------------------------------------
 * @param:       i_pxTask : task infos
 * @param out:   i_acPrintOutput : external buffer
 *-----------------------------------------------------------------------------
 */
void L_PrintTaskInfoInString(ASM_t_task * i_pxTask, char * i_acPrintOutput)
{
	char acText[50];
	char acDate[50];

	memclr(acDate,50);

	sprintf(acText,"\nApplication Id = %04X",i_pxTask->usApplicationId);
	sprintf(i_acPrintOutput, "\n%s", acText);

	sprintf(acText,"\nTask Id = %d",i_pxTask->usTaskId);
	strcat(i_acPrintOutput, acText);
	
	sprintf(acText,"\nTask name = %s",i_pxTask->acTaskName);
	strcat(i_acPrintOutput, acText);

	memcpy(acDate,i_pxTask->sExexutionTimeBase.day,2);
	memcpy(acDate+2,"/",1);
	memcpy(acDate+3,i_pxTask->sExexutionTimeBase.month,2);
	memcpy(acDate+5,"/",1);
	memcpy(acDate+6,i_pxTask->sExexutionTimeBase.year,2);
	sprintf(acText,"\nDate = %s",acDate);
	strcat(i_acPrintOutput, acText);
	
	memcpy(acDate+8,"\n",1);
	memcpy(acDate+9,i_pxTask->sExexutionTimeBase.hour,2);
	memcpy(acDate+11,":",1);
	memcpy(acDate+12,i_pxTask->sExexutionTimeBase.minute,2);
	memcpy(acDate+14,":",1);
	memcpy(acDate+15,i_pxTask->sExexutionTimeBase.second,2);
	sprintf(acText,"\nTime = %s",acDate+9);
	strcat(i_acPrintOutput, acText);

	sprintf(acText,"\nTask priority = %d",i_pxTask->iPriority);
	strcat(i_acPrintOutput, acText);

	sprintf(acText,"\nTask periodicity = %d",i_pxTask->iPeriodicity);
	strcat(i_acPrintOutput, acText);

	sprintf(acText,"\nTask duration = %d",i_pxTask->iDuration);
	strcat(i_acPrintOutput, acText);

	sprintf(acText,"\nNB max try = %d",i_pxTask->iNbMaxTry);
	strcat(i_acPrintOutput, acText);

	sprintf(acText,"\nTime retry = %d",i_pxTask->iTimeRetry);
	strcat(i_acPrintOutput, acText);

	sprintf(acText,"\nLast call status = %d\n",i_pxTask->iStatusLastCall);
	strcat(i_acPrintOutput, acText);
}


