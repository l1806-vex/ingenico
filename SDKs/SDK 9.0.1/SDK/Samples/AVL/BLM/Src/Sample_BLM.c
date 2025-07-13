/* ========================================================================	*/
/* Include																	*/
/* ========================================================================	*/
#include "SDK30.H"
#include "VGE_BLM.h"
#include "VGE_UIM.h"


/* ========================================================================	*/
/* Local function declaration												*/
/* ========================================================================	*/

int bubble_sort(BLM_t_black_list * io_psBlackList);
void permut(BLM_t_elt_black_list *p1,BLM_t_elt_black_list *p2);
int FindElement ( BLM_t_black_list* io_psBlackList, BLM_t_pan *i_psPan,int * o_pnPostion);
void ServiceResultBLM(int ret,char * code);
void l_ConvertToDate(char * i_pcDate,DATE * o_sDate );


/* ========================================================================	*/
/* External function definitions											*/
/* ========================================================================	*/

extern void BLM_PrintResult(int i_iRet);
extern void char2double(char * src,int lengthSrc,double * dest);
extern void CUTERMprintLine(char *xs_text);


#define NUMBER_OF_ITEMS(a)			(sizeof(a)/sizeof((a)[0]))


/* ========================================================================	*/
/* Local function definition												*/
/* ========================================================================	*/

/**
 * @function:    l_ConvertToDate
 * @description: Convert date from text (ex:"01/01/08") to DATE structure
 */
void l_ConvertToDate(char * i_pcDate,DATE * o_sDate )
{
	memcpy(o_sDate->day,i_pcDate,2 );
    memcpy(o_sDate->month,i_pcDate+3,2 );
    memcpy(o_sDate->year,i_pcDate+6,2 );
}

/**
 * @function:    permut
 * @description: Permut two elements of a Black List
 */
void permut(BLM_t_elt_black_list *p1,BLM_t_elt_black_list *p2)
{
	BLM_t_elt_black_list temp;

	memcpy(&temp,p1,sizeof(BLM_t_elt_black_list));
	memcpy(p1,	p2,	sizeof(BLM_t_elt_black_list));
	memcpy(p2,&temp,sizeof(BLM_t_elt_black_list));
}

/**
 * @function:    bubble_sort
 * @description: Sorting function used to sort Black List elements
 */
int bubble_sort(BLM_t_black_list * io_psBlackList)
{
	int counter=(io_psBlackList->ulNbElements);
    double dBlackListPan,dBlackListPan1,dBlackListRangeMin,dBlackListRangeMin1;

	while(counter>0)
	 {	
		 int index=0;

		 while(index<counter)
		 {
			 dBlackListPan=0;
			 dBlackListPan1=0;
			 dBlackListRangeMin=0;
			 dBlackListRangeMin1=0;

			 if (io_psBlackList->sBLTable[index].ucRecordType == BLM_PAN_TYPE && 
				 io_psBlackList->sBLTable[index+1].ucRecordType == BLM_PAN_TYPE)
			 { 				 
				 char2double((char*)io_psBlackList->sBLTable[index].BLM_u_elt_bl.sPan.ucPan,strlen((char*)io_psBlackList->sBLTable[index].BLM_u_elt_bl.sPan.ucPan),&dBlackListPan);
				 char2double((char*)io_psBlackList->sBLTable[index+1].BLM_u_elt_bl.sPan.ucPan,strlen((char*)io_psBlackList->sBLTable[index+1].BLM_u_elt_bl.sPan.ucPan),&dBlackListPan1);
	
				 if(dBlackListPan>dBlackListPan1)
				 {				 
					 permut(&(io_psBlackList->sBLTable[index]),
						 &(io_psBlackList->sBLTable[index+1]));
				 }
			 }
			 else if (io_psBlackList->sBLTable[index].ucRecordType == BLM_RANGE_TYPE && 
				 io_psBlackList->sBLTable[index+1].ucRecordType == BLM_RANGE_TYPE)
			 {				 
				 char2double((char*)io_psBlackList->sBLTable[index].BLM_u_elt_bl.sRange.ucRangeMin,strlen((char*)io_psBlackList->sBLTable[index].BLM_u_elt_bl.sRange.ucRangeMin),&dBlackListRangeMin);
		         char2double((char*)io_psBlackList->sBLTable[index+1].BLM_u_elt_bl.sRange.ucRangeMin,strlen((char*)io_psBlackList->sBLTable[index+1].BLM_u_elt_bl.sRange.ucRangeMin),&dBlackListRangeMin1);
				 
				 if(dBlackListRangeMin>dBlackListRangeMin1)
				 {
					permut(&(io_psBlackList->sBLTable[index]),
							&(io_psBlackList->sBLTable[index+1]));
				 }
			 }
			 else if (io_psBlackList->sBLTable[index].ucRecordType == BLM_PAN_TYPE && 
				 io_psBlackList->sBLTable[index+1].ucRecordType == BLM_RANGE_TYPE)
			 {	 
				 char2double((char*)io_psBlackList->sBLTable[index].BLM_u_elt_bl.sPan.ucPan,strlen((char*)io_psBlackList->sBLTable[index].BLM_u_elt_bl.sPan.ucPan),&dBlackListPan);
		         char2double((char*)io_psBlackList->sBLTable[index+1].BLM_u_elt_bl.sRange.ucRangeMin,strlen((char*)io_psBlackList->sBLTable[index+1].BLM_u_elt_bl.sRange.ucRangeMin),&dBlackListRangeMin1);
				 
				 if(dBlackListPan>dBlackListRangeMin1)
				 {
					permut(&(io_psBlackList->sBLTable[index]),
							&(io_psBlackList->sBLTable[index+1]));
				 }
			 }
			else if (io_psBlackList->sBLTable[index].ucRecordType == BLM_RANGE_TYPE && 
				 io_psBlackList->sBLTable[index+1].ucRecordType == BLM_PAN_TYPE)
			 {
				 
				char2double((char*)io_psBlackList->sBLTable[index].BLM_u_elt_bl.sRange.ucRangeMin,strlen((char*)io_psBlackList->sBLTable[index].BLM_u_elt_bl.sRange.ucRangeMin),&dBlackListRangeMin);

				char2double((char*)io_psBlackList->sBLTable[index+1].BLM_u_elt_bl.sPan.ucPan,strlen((char*)io_psBlackList->sBLTable[index+1].BLM_u_elt_bl.sPan.ucPan),&dBlackListPan1);
		        
				
				if(dBlackListRangeMin>dBlackListPan1)
				 {
					permut(&(io_psBlackList->sBLTable[index]),
							&(io_psBlackList->sBLTable[index+1]));
				 }
			 }
			index++;
		}
		counter--;
	}
	return 1; 
 }

/**
 * @function:    FindElement
 * @description: Function used to search for an element in the black list.
 */
int FindElement ( BLM_t_black_list* io_psBlackList, BLM_t_pan *i_psPan,int * o_pnPostion)
{
	int iReturn=0;
	unsigned int iCounter;
	double dEltPan, dBlackListPan,dBlackListRangeMin,dBlackListRangeMax;
	
	iCounter=0;

	char2double((char*)i_psPan->ucPan,strlen((char*)i_psPan->ucPan),&dEltPan);

	while(iCounter<io_psBlackList->ulNbElements)
	{	
		if (io_psBlackList->sBLTable[iCounter].ucRecordType == BLM_PAN_TYPE)
		{
            char2double((char*)io_psBlackList->sBLTable[iCounter].BLM_u_elt_bl.sPan.ucPan,strlen((char*)io_psBlackList->sBLTable[iCounter].BLM_u_elt_bl.sPan.ucPan),&dBlackListPan);

			if(dEltPan==dBlackListPan)
			{
				*o_pnPostion=iCounter;
				iReturn=1;
				break;
			}
			else
				if(dEltPan< dBlackListPan)
				{  /* Growing sort : search is stopped*/
					*o_pnPostion=iCounter;
					iReturn=0;
					break;
				}
		}
		else
		{
			char2double((char*)io_psBlackList->sBLTable[iCounter].BLM_u_elt_bl.sRange.ucRangeMin,strlen((char*)io_psBlackList->sBLTable[iCounter].BLM_u_elt_bl.sRange.ucRangeMin),&dBlackListRangeMin);
            char2double((char*)io_psBlackList->sBLTable[iCounter].BLM_u_elt_bl.sRange.ucRangeMax,strlen((char*)io_psBlackList->sBLTable[iCounter].BLM_u_elt_bl.sRange.ucRangeMax),&dBlackListRangeMax);
		   
			if ((dEltPan>= dBlackListRangeMin)&&(dEltPan<= dBlackListRangeMax))
			{
				*o_pnPostion=iCounter;
				iReturn=1;
				break;
			}
			else
				if(dEltPan < dBlackListRangeMin)
				{
					/* Growing sort : search is stopped*/
					*o_pnPostion=iCounter;
					iReturn=0;
					break;
				}
		}
	iCounter++;	
	}
	return (iReturn);
}

/* ========================================================================	*/
/*  BLM Functions 																*/
/* ========================================================================	*/

/**
 * @function:    BLM_CreateBlackList_test 
 * @description: Call BLM_CreateBlackList and prints results 
 */
void BLM_CreateBlackList_test(void)
{	
	int iCreate;

	CUTERMprintLine("************************");
	CUTERMprintLine("* BLM CREATE BLACKLIST *\n");

	iCreate = BLM_CreateBlackList(bubble_sort,FindElement);

	BLM_PrintResult(iCreate);
}

/**
 * @function:    BLM_deleteBlackList_test 
 * @description: Call BLM_DeleteBlackList and prints results 
 */
void BLM_deleteBlackList_test(void)
{
	int iDelete;

    CUTERMprintLine("************************");
	CUTERMprintLine("* BLM DELETE BLACKLIST *\n");
	
	iDelete=BLM_DeleteBlackList();

	BLM_PrintResult(iDelete);
}
	
/**
 * @function:    BLM_InitBlackList_test 
 * @description: Call BLM_InitBlackList and prints results 
 */
void BLM_InitBlackList_test(void)
{
	int iInit;
	DATE sActivationDate,sExpirationDate;
	char acText[50];
	char acDate[20];

    CUTERMprintLine("************************");
	CUTERMprintLine("* BLM INIT BLACKLIST *\n");
	
	memset(&sActivationDate,0,sizeof(DATE));
    memset(&sExpirationDate,0,sizeof(DATE)); 

	strcpy(acDate,"01/01/08");
	sprintf(acText,"Activation Date=%s",acDate);
    CUTERMprintLine(acText);
    l_ConvertToDate(acDate,&sActivationDate);
	
    strcpy(acDate,"01/01/09");
	sprintf(acText,"Expiration Date=%s",acDate);
    CUTERMprintLine(acText);
    l_ConvertToDate(acDate,&sExpirationDate);

	iInit=BLM_InitBlackList(sActivationDate,sExpirationDate,5);
	
	BLM_PrintResult(iInit);
}

/**
 * @function:    BLM_AddElementInBL_test 
 * @description: Call BLM_AddElementInBL and prints results
 */
void BLM_AddElementInBL_test(void)
{
	int iAdd;
	BLM_t_elt_black_list psEltBlackList;
	
	CUTERMprintLine("************************");
	CUTERMprintLine("*** BLM ADD ELEMENT  ***\n");

	memset(&psEltBlackList,0,sizeof(BLM_t_elt_black_list));
	
    psEltBlackList.ucRecordType=BLM_PAN_TYPE;
	strcpy((char*)psEltBlackList.BLM_u_elt_bl.sPan.ucPan,"12345678");
	
	iAdd=BLM_AddElementInBL(&psEltBlackList);
	
	BLM_PrintResult(iAdd);
}

/**
 * @function:    BLM_PrintDiagOfBL_test 
 * @description: Call BLM_PrintDiagOfBL
 */
void BLM_PrintDiagOfBL_test(void)
{
	BLM_PrintDiagOfBL();
}

/**
 * @function:    BLM_DeleteElementFromBL_test
 * @description: Call BLM_DeleteElementFromBL and prints results 
 */
void BLM_DeleteElementFromBL_test(void)
{
	int iDelete;
	BLM_t_elt_black_list psEltBlackList;
    
	CUTERMprintLine("************************");
	CUTERMprintLine("** BLM DELETE ELEMENT **\n");

	memset(&psEltBlackList,0,sizeof(BLM_t_elt_black_list));
	
	psEltBlackList.ucRecordType=BLM_PAN_TYPE;
	strcpy((char*)psEltBlackList.BLM_u_elt_bl.sPan.ucPan,"12345678");
	
	iDelete=BLM_DeleteElementFromBL(&psEltBlackList);
    	
	BLM_PrintResult(iDelete);
}

/**
 * @function:    BLM_CheckExistenceInBL_test
 * @description: Call BLM_CheckExistenceInBL and prints results 
 */
void BLM_CheckExistenceInBL_test(void)
{
	int iCheck;
	BLM_t_pan psPan;

    CUTERMprintLine("************************");
	CUTERMprintLine("*** CHECK EXISTENCE  ***\n");

    strcpy((char*)psPan.ucPan,"12345678");
	
	iCheck=	BLM_CheckExistenceInBL(&psPan);

    BLM_PrintResult(iCheck);
}

/**
 * @function:    BLM_ModifyValidityOfBL_test
 * @description: Call BLM_ModifyValidityOfBL and prints results 
 */
void BLM_ModifyValidityOfBL_test(void)
{
	int iModify;
	DATE sActivationDate,sExpirationDate;
	char acText[50];
	char acDate[20];

	CUTERMprintLine("************************");
	CUTERMprintLine("* MODIFY VALIDITY OF BL*\n");

    memset(&sActivationDate,0,sizeof(DATE));
    memset(&sExpirationDate,0,sizeof(DATE)); 

	strcpy(acDate,"01/01/08");
	sprintf(acText,"Activation Date=%s",acDate);
    CUTERMprintLine(acText);
    l_ConvertToDate(acDate,&sActivationDate);
	
	strcpy(acDate,"01/01/10");
	sprintf(acText,"Expiration Date=%s",acDate);
    CUTERMprintLine(acText);
    l_ConvertToDate(acDate,&sExpirationDate);
	
	iModify=BLM_ModifyValidityOfBL(sActivationDate,sExpirationDate);
     
	BLM_PrintResult(iModify);
}

/**
 * @function:    BLM_VerifyValidityOfBL_test
 * @description: Call BLM_VerifyValidityOfBL and prints results 
 */
void BLM_VerifyValidityOfBL_test(void)
{
	int iVerify;
	DATE sDate;
	char acText[50];
	char acDate[20];

    CUTERMprintLine("************************");
	CUTERMprintLine("* VERIFY VALIDITY OF BL*\n");

    memset(&sDate,0,sizeof(DATE));
	strcpy(acDate,"09/01/08");
	
	sprintf(acText,"Current Date=%s",acDate);
    CUTERMprintLine(acText);
    l_ConvertToDate(acDate,&sDate);
	
	iVerify=BLM_VerifyValidityOfBL(sDate);
	
	BLM_PrintResult(iVerify);
}

/**
 * @function:    Test_BLM
 * @description: Manage menu that contains BLM functions
 */
int Test_BLM(void)
{
	UIM_t_navigate_menu l_x_NavigateMenu[] =
	{
		{"BLM SAMPLE",			"0",		0,	PT_NULL},
		{"Create BL",			"1",		1,	(PFONCNAVI)BLM_CreateBlackList_test},
		{"Init BL",				"2",		1,	(PFONCNAVI)BLM_InitBlackList_test},
		{"Add Element In BL",	"3",		1,	(PFONCNAVI)BLM_AddElementInBL_test},
		{"Print Diag Of BL",	"4",		1,	(PFONCNAVI)BLM_PrintDiagOfBL_test},
		{"Delete Element",		"5",		1,	(PFONCNAVI)BLM_DeleteElementFromBL_test},
		{"Check Existence",		"6",		1,	(PFONCNAVI)BLM_CheckExistenceInBL_test},
		{"Modify BL Validity",	"7",		1,	(PFONCNAVI)BLM_ModifyValidityOfBL_test},
		{"Verify BL Validity",	"8",		1,	(PFONCNAVI)BLM_VerifyValidityOfBL_test},
		{"Delete BL",			"9",		1,	(PFONCNAVI)BLM_deleteBlackList_test},
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

	UIM_NavigateService(l_x_NavigateMenu,NUMBER_OF_ITEMS(l_x_NavigateMenu),&l_x_NavigateOption);

	return FCT_OK;
}

