
#ifndef GMA_MENU_RESOURCE_H_INCLUDED
#define GMA_MENU_RESOURCE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


/**
 * 
 */

/**
 * This function read the MENU RESOURCE MODULE from the resource file
 * This function should be called prior to other functions
 * 
 */
int16 gmaMRESinitialize(char *appName);

/**
 * Get the menu entries to be shown
 */
int16 gmaMRESGetMenuEntries(char *path, char **entries, uint16 *actions, uint8 *entryNumber, uint8 logicalId);


/**
 * Initialize the List of application that the GMA will show the resource menu
 */
void gmaMRESInitialize(void);

/**
 * Set if the GMA will show the resource menu of a specific application
 */
void gmaMRESSetMnuResAppShowStatus(uint16 appId, uint8 logicalId, uint8 status);

/**
 * Check if the GMA should show a menu of a specific application.
 */
int16 gmaMRESGetMnuResAppShowStatus(uint16 appId, uint8 logicalId);

#ifdef __cplusplus
}
#endif


#endif

