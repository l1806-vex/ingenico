#include "SDK30.H"
#include "VGE_DRM.h"


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
 * @function:    EntCreateOrMountDisk
 * @description: 
 */
int EntCreateOrMountDisk (char * i_pcFilePath, unsigned int i_uiDiskSize)
{
	int               Ret;
	unsigned long     TailleDisk;
	S_FS_PARAM_CREATE ParamCreat;
	
	
	ParamCreat.Mode         = FS_WRITEONCE;
	ParamCreat.IdentZone    = FS_WO_ZONE_DATA;
	
	strcpy(ParamCreat.Label, i_pcFilePath);
	ParamCreat.AccessMode   = FS_WRTMOD;
	ParamCreat.NbFichierMax = 30;		
	TailleDisk              = i_uiDiskSize;

	Ret = FS_mount (i_pcFilePath,&ParamCreat.Mode);
	ParamCreat.Mode         = FS_WRITEONCE;
	
	if (Ret != FS_OK)
	{
		Ret=FS_dskcreate(&ParamCreat,&TailleDisk);
	}
	
    return (Ret);
}

/**
 * @function:    ServiceResultDRM
 * @description: Convert return code
 */
void ServiceResultDRM(char * o_pcResult, int i_nResult)
{
	char l_acResult [40];

	switch(i_nResult)
	{
		case DRM_SUCCESS:
			sprintf(l_acResult,"DRM_SUCCESS");
			break;

		case DRM_INIT_OK:
			sprintf(l_acResult,"DRM_INIT_OK");
			break;

		case DRM_INIT_KO:
			sprintf(l_acResult,"DRM_INIT_KO");
			break;

		case DRM_STATUS_ERROR:
			sprintf(l_acResult,"DRM_STATUS_ERROR");
			break;

		case DRM_SAVE_ERROR:
			sprintf(l_acResult,"DRM_SAVE_ERROR");
			break;

		case DRM_DELETE_ERROR:
			sprintf(l_acResult,"DRM_DELETE_ERROR");
			break;

		case DRM_RESTORE_ERROR:
			sprintf(l_acResult,"DRM_RESTORE_ERROR");
			break;

		case DRM_LABEL_ERROR:
			sprintf(l_acResult,"DRM_LABEL_ERROR");
			break;

		default:
			sprintf(l_acResult,"DRM_UNKNOWN");
			break;
	}
	strcpy(o_pcResult, l_acResult);
}

void DRM_PrintResult(int i_iRet)
{
	char acReturnMessage[50];
	char acText[50];

	ServiceResultDRM(acReturnMessage,i_iRet);
	
	sprintf(acText,"Result= %s",acReturnMessage);
	CUTERMprintLine(acText);
}
