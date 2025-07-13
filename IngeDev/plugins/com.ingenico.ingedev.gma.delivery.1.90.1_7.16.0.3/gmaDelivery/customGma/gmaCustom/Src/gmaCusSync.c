#include "string.h"

#include "unicapt.h"

#include "gmaCusSync.h"
#include "gmaCustomSemaphores.h"
#include "gmaDefines.h"
#include "gmaQueueTask.h"

static uint32 _currentTaskId, _mainTaskId;
static void *_param1;
static uint32 _param2;
static gmaCtSynCBFun _func;

/**
 * Initialize the module (to get the main task id)
 */
void gmaCtSynInitialize(void)
{
   psyTaskIdentThis(&_mainTaskId);
}

/**
 * Execute the following function in the main task
 */
int16 gmaCtSynSendMainTask(gmaCtSynCBFun func, void *param1, uint32 paramSize)
{
   int16 ret;

   uint32 recEvt;

   gmaCustomSemaphoreAcquire(GMA_CUSTOM_SEMAPHORE_TASK_MESSAGE);
   
   psyTaskIdentThis(&_currentTaskId);
   _param1 = param1;
   _param2 = paramSize;
   _func = func;
   
   psyEventSend(_mainTaskId, EVENT_4);

   ret = psyEventReceive(EVENT_4, PSY_EV_ANY | PSY_EV_WAIT, PSY_INFINITE_TIMEOUT, &recEvt);
   
   gmaCustomSemaphoreRelease(GMA_CUSTOM_SEMAPHORE_TASK_MESSAGE);
   
   return RET_OK;
}

/**
 *
 */
int16 gmaCtSynTreatmainTaskEvent(int32 ret)
{

   uint32 data[512/4];
   uint32 dataSize;
   if(ret & EVENT_4)
   {
      dataSize = _param2;
      memcpy(data, _param1, dataSize);
      psyEventSend(_currentTaskId, EVENT_4);
      if(_func)
         _func(data, dataSize);
      
      
   }
   return RET_OK;
}
