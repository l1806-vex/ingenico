
/** @file gmaCustomSemaphores.c
 * 
 * This file has a wrapper for the semaphores used in the custom part.
 *
 * This semaphores are used to don't permit more than one task to access
 * some variables at the same time.
 */

#include "string.h"

#include "unicapt.h"

#include "gmaCustomSemaphores.h"

static uint8 initialize = 0;
static uint32 semaphoreIds[GMA_CUSTOM_SEMAPHORE_MAX_NUMB];

/**
 * Initialize the library variables and
 * create the semaphores
 */
int16 gmaCustomSemaphoreInit(void)
{
   int16 ret;
   uint16 i;
   char name[2];

   if(initialize != 0)
      return -1;
   initialize = 1;

   memset(semaphoreIds, 0, sizeof(semaphoreIds));
   name[0] = 110;
   for(i=0; i<GMA_CUSTOM_SEMAPHORE_MAX_NUMB; i++)
   {
      name[1] = 'a' + i;
      ret = psySemaphoreCreate(name, 1, PSY_SM_FIFO, &semaphoreIds[i]);
      if(ret != RET_OK)
         return ret;
         
   }
   return RET_OK;
}

/**
 * Acquire a semaphore.
 *
 * @param semaphoreId the id of the semaphore to be acquire. A number
 * between 0 and (GMA_CUSTOM_SEMAPHORE_MAX_NUMB - 1)
 */
int16 gmaCustomSemaphoreAcquire(uint8 semaphoreId)
{
   if(semaphoreId >= GMA_CUSTOM_SEMAPHORE_MAX_NUMB)
      return -1;
   return psySemaphoreAcquire(semaphoreIds[semaphoreId], PSY_INFINITE_TIMEOUT);
}

/**
 * Release the semaphore with semaphoreId Id.
 */
int16 gmaCustomSemaphoreRelease(uint8 semaphoreId)
{
   if(semaphoreId >= GMA_CUSTOM_SEMAPHORE_MAX_NUMB)
      return -1;
   return psySemaphoreRelease(semaphoreIds[semaphoreId]);
}

