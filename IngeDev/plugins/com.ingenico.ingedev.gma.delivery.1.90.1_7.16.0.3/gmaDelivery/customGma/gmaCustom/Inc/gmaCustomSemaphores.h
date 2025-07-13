
/**
 * @file gmaCustomSemaphores.h
 */

#ifndef GMA_CUSTOM_SEMAPHORE_H_INCLUDED
#define GMA_CUSTOM_SEMAPHORE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Id of the key table semaphore
 */
#define GMA_CUSTOM_SEMAPHORE_KEY_TABLE (0)

/**
 * Id of the menu table semaphore
 */
#define GMA_CUSTOM_SEMAPHORE_MENU_TABLE (1)

/**
 * Id of the main task message
 */
#define GMA_CUSTOM_SEMAPHORE_TASK_MESSAGE (2)

#define GMA_CUSTOM_SEMAPHORE_OTHER (3)

/*
 * Number of semaphores
 */
#define GMA_CUSTOM_SEMAPHORE_MAX_NUMB (3)

/*
 * Initialize the library variables and
 * create the semaphores
 */
int16 gmaCustomSemaphoreInit(void);

/*
 * Acquire a semaphore.
 */
int16 gmaCustomSemaphoreAcquire(uint8 semaphoreId);

/*
 * Release the semaphore
 */
int16 gmaCustomSemaphoreRelease(uint8 semaphoreId);

#ifdef __cplusplus
}
#endif


#endif

