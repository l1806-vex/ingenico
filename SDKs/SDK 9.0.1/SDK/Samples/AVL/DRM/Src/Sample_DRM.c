/* ========================================================================	*/
/* Include																	*/
/* ========================================================================	*/
#include "SDK30.H"
#include "VGE_DRM.h"
#include "VGE_UIM.h"


/* ========================================================================	*/
/* Macros & preprocessor definitions										*/						
/* ========================================================================	*/

#define LABEL_DISK_SAMPLE	"DRMPATH"
#define LABEL_FILE_SAMPLE	"DRMFILE"
#define DISK_SAMPLE_SIZE	0x19000

#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))


/* ========================================================================	*/
/* Local function declaration												*/
/* ========================================================================	*/

void DrmStatus(void);
void SaveData(void);
void RestoreData(void);
void DeleteData(void);


/* ========================================================================	*/
/* External function definitions											*/
/* ========================================================================	*/

extern void DRM_PrintResult(int i_iRet);
extern void CUTERMprintLine(char *xs_text);
extern int EntCreateOrMountDisk (char * i_pcFilePath, unsigned int i_uiDiskSize);



/* ========================================================================	*/
/* Functions																*/
/* ========================================================================	*/

/**
 * @function:		InitDRM 
 * @description:	Call DRM_Init and prints results 
 */
void InitDRM(void)
{
	char pcText[50];
	int  iRet=0;

    CUTERMprintLine("** INIT DRM **");
	
    sprintf(pcText,"PathName= %s ",LABEL_DISK_SAMPLE);
	CUTERMprintLine(pcText);
    sprintf(pcText,"FileName= %s ",LABEL_FILE_SAMPLE);
	CUTERMprintLine(pcText);
	sprintf(pcText,"DiskSize= %d ",DISK_SAMPLE_SIZE);
	CUTERMprintLine(pcText);

	iRet=DRM_Init (LABEL_DISK_SAMPLE, LABEL_FILE_SAMPLE, DISK_SAMPLE_SIZE);
	
	DRM_PrintResult(iRet);
	CUTERMprintLine("\n\n");
}

/**
 * @function:		DrmStatus 
 * @description:	Call DRM_GetStatus and prints results
 */
void DrmStatus(void)
{
	char pcFilePath_L[MAX_DRM_FILE_PATH+MAX_DRM_FILE_NAME+3];
	unsigned int uiReturnValue=DRM_DELETE_ERROR,uiLabelBufValue=0,uiLengthBufValue=0;
	long lFileLength;
	S_FS_FILE *file;
	char * buff_tmp=NULL;
	int i=0,iRet,nPosition,iSize=0;
	Boolean bFound = FALSE;	
	DRM_t_drm_status sDrmStatus;
	int iNbElement;
	char pcText[50];
	char uiBufValue[40];

	memset(pcText,0,50);
	memset(&sDrmStatus,0,sizeof(DRM_t_drm_status));
	
	if(DRM_GetStatus (&sDrmStatus)==DRM_SUCCESS)
	{
		CUTERMprintLine("**   DRM STATUS    **");
		
		iNbElement=sDrmStatus.uiNbDataSaved;
		
		sprintf(pcText,"Path Name : %s",sDrmStatus.pcPathName);
		CUTERMprintLine(pcText);
		
		sprintf(pcText,"File Name : %s",sDrmStatus.pcFileName);
		CUTERMprintLine(pcText);
		
		sprintf(pcText,"Disk Size = %d",sDrmStatus.uiDiskSize);
		CUTERMprintLine(pcText);
		
		sprintf(pcText,"File Size = %d",sDrmStatus.uiFileSize);
		CUTERMprintLine(pcText);
		
		sprintf(pcText,"Data Number = %d",sDrmStatus.uiNbDataSaved);
		CUTERMprintLine(pcText);
		
		CUTERMprintLine("***********************");
		
		EntCreateOrMountDisk (sDrmStatus.pcPathName,sDrmStatus.uiDiskSize);
		sprintf(pcFilePath_L, "/%s/%s",sDrmStatus.pcPathName,sDrmStatus.pcFileName);
		
		/* Open the file */
		file= FS_open (pcFilePath_L, "r");
		if (file == NULL)
		{
			uiReturnValue = DRM_DELETE_ERROR;
		}
		else
		{
			lFileLength =FS_length(file);
			buff_tmp = PageAlloc(lFileLength); // allocate the buffer
			if (buff_tmp != NULL )
			{
				iRet = FS_seek(file,0,FS_SEEKSET);
				if (iRet==FS_OK)
				{
					iSize = FS_read(buff_tmp,lFileLength,1,file);
					if((iSize==1)||((iSize ==0)&&(lFileLength==0)))
					{
						nPosition=0;
						
						while ((nPosition<lFileLength)&&(nPosition>=0))
						{
							memset(uiBufValue,0,40);
							memcpy(&uiLabelBufValue,buff_tmp+nPosition,sizeof(unsigned int));
							i=0;
							bFound=FALSE;
							while((i<iNbElement)&&(bFound!=TRUE))
							{
								if(uiLabelBufValue==sDrmStatus.piIdDataList[i])
									bFound=TRUE;
								i++;
							}
							
							CUTERMprintLine(" ");
							
							if(bFound!=TRUE)
								CUTERMprintLine("\n ! Element not Found !");
							
							
							nPosition+=sizeof(unsigned int); // Tag
							memcpy(&uiLengthBufValue,buff_tmp+nPosition,sizeof(unsigned int));
							
							if (((int)uiLengthBufValue >= 0)&&((int)uiLengthBufValue<=(lFileLength-nPosition)))
							{
								nPosition+=sizeof(unsigned int); // Length
								memcpy(uiBufValue,buff_tmp+nPosition,uiLengthBufValue);
								nPosition+=uiLengthBufValue;	 // Value	
								
								sprintf(pcText,"Tag = %d",uiLabelBufValue);
								CUTERMprintLine(pcText);
								
								sprintf(pcText,"Length = %d",uiLengthBufValue);
								CUTERMprintLine(pcText);
								
								sprintf(pcText,"Value = %s",uiBufValue);
								CUTERMprintLine(pcText);
							}
							else
							{
								sprintf(pcText,"Parse error at tag : %d",sDrmStatus.piIdDataList[i-1]);
								CUTERMprintLine(pcText);
								nPosition=lFileLength;
							}
						}
					}
				}
			}
			PageFree(buff_tmp);		
			FS_close(file);
		}
	}
	
	CUTERMprintLine("\n\n\n");
}


/**
 * @function:		SaveData 
 * @description:	Call DRM_SaveData and prints results
 */
void SaveData(void)
{
	int iRet,iDataLabel,iLength=0;
	char pcBuffer[33];
	char pcText[50];
    
	CUTERMprintLine("** DRM SAVE DATA **");
	
	iDataLabel = 1234;
	sprintf(pcText,"DataLabel= %d",iDataLabel);
    CUTERMprintLine(pcText); 
	strcpy(pcBuffer,"SAMPLE DRM Data");
    sprintf(pcText,"DataValue= %s",pcBuffer);
    CUTERMprintLine(pcText); 
	iLength=strlen(pcBuffer);

	iRet = DRM_SaveData (iDataLabel, pcBuffer, iLength);

	DRM_PrintResult(iRet);
	CUTERMprintLine("\n\n");
}

/**
 * @function:		RestoreData 
 * @description:	Call DRM_RestoreData and prints results
 */
void RestoreData(void)
{

	int iRet,iDataLabel, iDataLen=0;
	char pcBuffer[40];
	char pcText[50];

	CUTERMprintLine("** DRM RESTORE DATA **");
	
	memset(pcBuffer,0,40);
	
	iDataLabel = 1234;
	sprintf(pcText,"DataLabel= %d",iDataLabel);
    CUTERMprintLine(pcText); 

	iRet = DRM_RestoreData (iDataLabel,pcBuffer,&iDataLen);

	DRM_PrintResult(iRet);

	if (iRet == DRM_SUCCESS)
		CUTERMprintLine(pcBuffer);
	else
		CUTERMprintLine("RESTORE DATA FAILED");
    CUTERMprintLine("\n\n\n");
}

/**
 * @function:		DeleteData 
 * @description:	Call DRM_DeleteData and prints results
 */
void DeleteData(void)
{

	int iRet,iDataLabel;
	char pcText[50];

	CUTERMprintLine("** DRM DELETE DATA **");

	iDataLabel = 1234; 
	sprintf(pcText,"DataLabel= %d",iDataLabel);
    CUTERMprintLine(pcText); 

	iRet = DRM_DeleteData (iDataLabel);

	DRM_PrintResult(iRet);
	CUTERMprintLine("\n\n\n");
}

/**
 * @function:		DRM_Test 
 * @description:	Manage menu that contains DRM functions
 */
int DRM_Test(void)
{
	int l_nRet;

	UIM_t_navigate_menu l_x_NavigateMenu[] =
	{
		{"DRM SAMPLE",	"0",		0,	PT_NULL},
		{"DRM Status",	"1",		1,	(PFONCNAVI)DrmStatus},
		{"Save data",	"2",		1,	(PFONCNAVI)SaveData},
		{"Restore data","3",		1,	(PFONCNAVI)RestoreData},
		{"Delete data",	"4",		1,	(PFONCNAVI)DeleteData},
		{"Init DRM",	"5",		1,	(PFONCNAVI)InitDRM},
	};
	
	UIM_t_navigate_option l_x_NavigateOption = {
		30,						/*time out in second*/
		1,						/*offset*/
		0,						/*radio button*/
		UIM_DISPLAY_MESSAGE,	/*action to do after time out*/
		0,						/*default choice*/
		"Time Out",				/*message to display after time out*/
		UIM_CONTINUE_AFTER_FCT	/*Action to do after the execution of the function*/
	};

	l_nRet = UIM_NavigateService(l_x_NavigateMenu,NUMBER_OF_ITEMS(l_x_NavigateMenu),&l_x_NavigateOption);

	return FCT_OK;
}
