
#ifndef GMA_CUSTOM_SYNC_H_INCLUDED
#define GMA_CUSTOM_SYNC_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


typedef int16 (*gmaCtSynCBFun)(void *param1, uint32 param2);

/**
 * Execute the following function in the main task
 */
int16 gmaCtSynSendMainTask(gmaCtSynCBFun func, void *param1, uint32 param2);

/**
 * Must be called by the main task when an event is received
 */
int16 gmaCtSynTreatmainTaskEvent(int32 ret);

/**
 * Initialize the module (to get the main task id)
 */
void gmaCtSynInitialize(void);

#ifdef __cplusplus
}
#endif


#endif

