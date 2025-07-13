
#ifndef GMA_CUSTOM_CB_H_INCLUDED
#define GMA_CUSTOM_CB_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Begin the peripheral support
 */
int16 gmaCBBeginPerSup(void);

/**
 * Stop the peripheral support
 */
int16 gmaCBStopPerSup(void);

/**
 * Cancel all pending events
 */
int16 gmaCBCancelEvents(void);


/**
 * An activity is finished. Only send a message to the plugins
 * if a previous \ref gmaCBActivityStart was called
 */
int16 gmaCBActivityEnd(void);

/**
 * An activity is begun. Call the function \ref gmaAppMsgSendActivityMsg
 * to warn the plugins about it
 */
int16 gmaCBActivityStart(void);

/**
 * Enable/disable peripheral start
 */
void gmaCBEnablePerStart(uint8 status);



/**
 * Set the custom call backs
 *
 * 
 */
int16 gmaInitCustomCallBacks(void);

#ifdef __cplusplus
}
#endif


#endif

