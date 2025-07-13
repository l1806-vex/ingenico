#include "SDK30.H"
#include "VGE_BLM.h"

#define __ENTER_KEY		-1
#define __BACK_KEY		-2
#define __EXIT_KEY		-3

/**
 * @function     : CUTERMprintLine                                                       
 * @description   : This service prints the text and wait for the end of the job
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
 * @function:    Pw
 * @description: return val to the power 10
 */
double Pw(int val)
{
	double ret,i;

	ret = 1;

	for(i=0;i<val;i++)
		ret *= 10;

	return ret;
}

/**
 * @function:    char2double
 */
void char2double(char * src,int lengthSrc,double * dest)
{
	int length,i,j;
	double intermed;

	length = lengthSrc;
	intermed = 0;
	j = length-1;

	for(i=0;i<length;i++)
	{
		intermed += (src[j]-0x30)*Pw(i);
		j--;
	}

	*dest = intermed ;
}

/**
 * @function:    ServiceResultBLM
 * @description: Convert return code
 */
void ServiceResultBLM(int ret,char * code)
{
	switch( ret )
	{
	case	0:
		strcpy(code," ");
		break;
	case	BLM_SUCCESS:
		strcpy(code,"BLM_SUCCESS");
		break;

	case	BLM_NOT_EXPIRED:
		strcpy(code,"BLM_NOT_EXPIRED");
		break;
	case	BLM_EXPIRED:
		strcpy(code,"BLM_EXPIRED");
		break;
	case	BLM_BLACK_LIST_DOES_NOT_EXIST:
		strcpy(code,"BLM_BLACK_LIST_DOES_NOT_EXIST");
		break;
	case	BLM_INVALID_RANGE:
		strcpy(code,"BLM_INVALID_RANGE");
		break;
	case	BLM_DELETE_ERROR:
		strcpy(code,"BLM_DELETE_ERROR");
		break;
	case	BLM_ADD_ERROR:
		strcpy(code,"BLM_ADD_ERROR");
		break;
	case	BLM_ELT_FOUND:
		strcpy(code,"BLM_ELT_FOUND");
		break;
	case	BLM_ELT_NOT_FOUND:
		strcpy(code,"BLM_ELT_NOT_FOUND");
		break;
	case	BLM_INVALID_PARAM:
		strcpy(code,"BLM_INVALID_PARAM");
		break;
	case	BLM_CREATE_ERROR:
		strcpy(code,"BLM_CREATE_ERROR");
		break;
	case	BLM_ELT_DOES_NOT_EXIST:
		strcpy(code,"BLM_ELT_DOES_NOT_EXIST");
		break;
	case	BLM_ELT_EXIST:
		strcpy(code,"BLM_ELT_EXIST");
		break;
	case	BLM_SORT_ERROR:
		strcpy(code,"BLM_SORT_ERROR");				
		break;
	case	BLM_UPDATE_ERROR:
		strcpy(code,"BLM_UPDATE_ERROR");
		break;
	case	BLM_INVALID_DATE:
		strcpy(code,"BLM_INVALID_DATE");
		break;

	case BLM_DELETE_BL_ERROR:
		strcpy(code,"BLM_DELETE_BL_ERROR");
        break;

	default:
		strcpy(code,"BLM_UNKNOWN");
		break;
	}	
}

void BLM_PrintResult(int i_iRet)
{
	char acReturnMessage[50];
	char acText[50];

	ServiceResultBLM(i_iRet, acReturnMessage);

	sprintf(acText,"Result= %s",acReturnMessage);
	CUTERMprintLine(acText);
	CUTERMprintLine("************************");
	CUTERMprintLine("\n\n");
}
