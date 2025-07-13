
#ifndef __GMA_HMI_KEY_PROCESS_H_INCLUDED
#define __GMA_HMI_KEY_PROCESS_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file gmaHmiProcess.h
 */

/**
 * Structure to hold key action information
 */
typedef struct
{
    uint8    keyVal; //!< key code
    uint8    action; //!< action to be executed when this key is pressed
    uint8    parameter; //!< Stores "function" if action = ACTION_FUNCTION  or  "logical app" if action = ACTION_NOTIFY
    uint8    flags;
    uint16   appID;     //!<   Used only if action = ACTION_NOTIFY to store the application to be identifier
} s_keyAssignTable;

#define SZ_KEY_ASSIGN_TABLE (sizeof(keyAssignTable)/sizeof(s_keyAssignTable))



/**
 * Change the specific keys for this terminal
 */
void gmaHmiUtilSetSpecKeys(void);

/**
 * Change the keys set
 */
int16 gmaHmiKeyChangeTable(uint8 keyVal, uint8 action, uint8 parameter, uint16 appID);

/**
 * Process the key pressed
 */
int16 gmaHmiKeyProcess(char keyPress);

/**
 * Process the touch screen action
 */
void gmaHmiTouchProcess(uint8 pluginId, uint16 appId,uint16 action, uint16 parameter);

#ifdef __cplusplus
}
#endif


#endif

