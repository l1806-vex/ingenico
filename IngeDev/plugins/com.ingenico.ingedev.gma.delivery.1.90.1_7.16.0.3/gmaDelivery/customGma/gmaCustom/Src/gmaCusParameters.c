#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <unicapt.h>

#include "gmaCustomParameters.h"
#include "gmaPropFile.h"

#define GMA_CUS_PARAMETER_FILE_NAME ("GMACUST1.DAT")

static gmaPropHandle propHandle = NULL;



/**
 * will read the file and store the information on the memory
 */
int16 gmaCusParameterInit(void)
{
	int16 ret;
	if(propHandle != NULL)
		return 0;
		
	gmaPropOpInit();
		
	ret = gmaPropOpen(GMA_CUS_PARAMETER_FILE_NAME, &propHandle);
	if(ret != RET_OK)
	{
		propHandle = NULL;
		return ret;
	}
	return RET_OK;
}

//"-1235|-11218|-12323|-123235|-1223"
//"ALL"
/**
 * 
 */
int16 gmaCusGetValueList(char *name, int16 *list, uint16 *size)
{
   uint16 listCounter;
	int16 ret;
	char *value;
	char valueTemp[10];
	if(propHandle == NULL)
		return -1;
		
	ret = gmaPropRead(propHandle, name, &value);
	if(ret != RET_OK)
		return ret;
	
	if(strstr(value, "ALL")!=NULL)
	{
		*size = 0;
		return RET_OK;
	}
	for(listCounter=0;listCounter<*size;)
	{
		uint8 i;
		for(i=0;*value!=' ' && i < 9 && *value!=0;value++)
		{
			if(isdigit(*value) || *value=='-')
         {      
   			valueTemp[i++] = *value;
         }
		}
      
      
      valueTemp[i]=0;

      list[listCounter++] = atoi(valueTemp);
      
      if(*value==0)
      {
         *size=listCounter;
         if(listCounter == 0)
            return -1;
         return RET_OK;
      }
      value++;
	}
	return RET_OK;
}

