#include "stdlib.h"
#include "string.h"

#include "unicapt.h"

#include "appList.h"
#include "gmaAppMsg.h"
#include "gmaHmiCustom.h"

#include "gmaHmiTransfer.h"
#include "gmaStructures.h"


static int16 gmaHmitrCheckHmiTransfer(uint16 appId, uint8 logicalId);


static uint8 statusHmiTransfer = 0;
static uint8 realHmiTransfer = 0;
static uint8 ctrlHmiTransfer = 0;

/**
 * This function must be called instead of call directly the function \ref gmaAppMsgWakeApp to have support
 * for HMI transfer when the application support it.
 */
int16 gmaHmiTrAppMsgWakeApp(uint16 appId, uint8 logicalId, amgMsg_t *msg)
{
	gmaStructTransferHmi_t *ptr = (gmaStructTransferHmi_t *) &(msg->msg[msg->msgLength]);
	
	if(gmaHmitrCheckHmiTransfer(appId, logicalId) == RET_OK)
	{
		uint32 hmiHandle = gmaHmiGetHandle();
		
		ptr->header.id = GMA_STRUCT_TRANSFER_HMI;
		ptr->header.length = sizeof(gmaStructTransferHmi_t) - sizeof(gmaStructHeader_t);
		ptr->header.logicalApp = logicalId;
		
		ptr->hmiHandle = hmiHandle;
		
		msg->msgLength += sizeof(gmaStructTransferHmi_t);
		
		statusHmiTransfer = 1;
	}
	
	return RET_OK;
}

static uint8 appLogicalHmiTransfer[GMA_APP_LIST_LOGICAL_APP_NUMBER];

/**
 * Initialize
 */
void gmaHmiTrInit(void)
{
	memset(appLogicalHmiTransfer, 0, sizeof(appLogicalHmiTransfer));
}

/**
 * Treat the structure \ref gmaStructTransferHmiSup_t.
 * 
 * This structure can be received from plug-ins or from applications
 * 
 * \ref appId the application Id that send the structure
 * 
 * \ref msg a pointer to the structure
 */
void gmaHmiTrTreatTransferHmiSup(uint16 appId, gmaStructHeader_t *msg)
{
	uint8 i;
	gmaAppListLogicalData_t *entry;
	
	gmaStructTransferHmiSup_t *str = (gmaStructTransferHmiSup_t *) msg;
	
	for(i=0; gmaAppListGetLogicalEntryFromInd(i, &entry) == RET_OK; i++)
	{
		if((entry->logicalId == str->logicalId || str->logicalId == GMA_APP_LIST_LOGICAL_ID_DEFAULT) &&
		   entry->appId     == appId)
		{
			appLogicalHmiTransfer[i] = str->status;
		}
		   	
	}
	return;
}

/**
 * Treat the structure \ref gmaStructTransferHmi_t.
 * 
 * This structure can be received from plug-ins or from applications when 
 * the application/plug-in close and open a transfer hmi handle.
 * 
 * \ref appId the application Id that send the structure
 * 
 * \ref msg a pointer to the structure
 */
void gmaHmiTrTreatTransferHmiBack(uint16 appId, gmaStructHeader_t *msg)
{
	gmaStructTransferHmi_t *str = (gmaStructTransferHmi_t *) msg;
	
	gmaHmiSetHandle(str->hmiHandle);
}

/**
 * Check if the application support HMI transfer and call the OS
 * function to transfer the handle if the application supports it.
 */
static int16 gmaHmitrCheckHmiTransfer(uint16 appId, uint8 logicalId)
{
	uint8 i;
	gmaAppListLogicalData_t *entry;
	gmaAppListPhysicalData_t *phyEntry;
	psyPid_t pid;
	
	hmiChangeOwnerInfo_t tempData;
	

	
	for(i=0; gmaAppListGetLogicalEntryFromInd(i, &entry) == RET_OK; i++)
	{
		if(entry->logicalId == logicalId &&
		   entry->appId     == appId)
		{
			if(appLogicalHmiTransfer[i] != 0)
			{
				uint32 hmiHandle = gmaHmiGetHandle();
				// support HMI transfer
				
				gmaAppListGetAppEntryFromId(appId, &phyEntry);
				
				psyPidGet(&pid);
				
				if(pid != phyEntry->pid)
				{
					tempData.pid = phyEntry->pid;
#if !defined(_ING_SIMUL_ING5)
					hmiChangeOwner(hmiHandle, HMI_CO_TYPE_PID, &tempData);
#endif
					realHmiTransfer = 1;
				}
				ctrlHmiTransfer = 1;
				return RET_OK;
			}
			else
				return -1;
		}
	}
	return -1;
}

/**
 * 
 */
void gmaHmiTrHmiOpen(void)
{
	gmaHmiOpen();
	statusHmiTransfer = 0;
	realHmiTransfer = 0;
}

/**
 * 
 */
void gmaHmiTrHmiClose(void)
{
	if ((!ctrlHmiTransfer) && ((!statusHmiTransfer) || (!realHmiTransfer)) )
	{
		gmaHmiClose();
	}
	else
	{
		gmaHmiSupCancel();
	}
	ctrlHmiTransfer = 0;
}


