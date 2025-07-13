// $Id: OSL_MessageQueue.h,v 1.1.2.6 2013/03/19 13:49:42 nthibert Exp $
// This module lets you create an expandable memory space

#ifndef OSL_MessageQueue_h_INCLUDED
#define OSL_MessageQueue_h_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

// ****************************************************************************
/// @addtogroup OSLayer
/// @{
/// @addtogroup MessageQueue MessageQueue
/// @{

// ****************************************************************************

/** @addtogroup MessageQueueDoc Documentation
	@{
	This module lets you create a MessageQueue for IPC.
	
	@}
	*/

/** MessageQueue handle */
typedef struct T_OSL_MESSAGE_QUEUE * T_OSL_HMESSAGE_QUEUE;

/** Create or open an already created binary message queue 
@param name name of the message queue , can be NULL
@param mode used while openning the message queue 
@param sec security attributes, optional
@return returns an handle of the binary message queue created */
T_OSL_HMESSAGE_QUEUE OSL_MessageQueue_Create(const char *name, T_OSL_OPEN_MODE mode, T_OSL_HSECURITY sec);

/** Release reference on the message queue object or destroy it if it is the last reference
@param msgqueue pointer to the binary message queue handle */
void OSL_MessageQueue_Destroy(T_OSL_HMESSAGE_QUEUE msgqueue);

/** Read data into the message queue
@param msgqueue binary message queue handle
@param data pointer to fill with message read from the queue message
@param size maximum size of read data buffer
@param timeout to wait in ms (OSL_TIMEOUT_INFINITE to wait indefinitely)
@return Error code */
T_OSL_ERROR OSL_MessageQueue_Receive(T_OSL_HMESSAGE_QUEUE msgqueue, void * data, unsigned long size, unsigned long timeout);

/** Writes data in the binary message queue
@param msgqueue binary message queue handle
@param data pointer to write to the message queue
@param size of the data buffer to write to the message queue
@param timeout to wait in ms (OSL_TIMEOUT_INFINITE to wait indefinitely)
@return Error code*/
T_OSL_ERROR OSL_MessageQueue_Send(T_OSL_HMESSAGE_QUEUE msgqueue, const void * data, unsigned long size, unsigned long timeout);

#ifdef __cplusplus
}
#endif

/// @}
/// @}

#endif // OSL_MessageQueue_h_INCLUDED
