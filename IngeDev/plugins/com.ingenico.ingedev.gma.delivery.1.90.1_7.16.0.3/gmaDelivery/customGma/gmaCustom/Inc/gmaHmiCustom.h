
#ifndef __GMA_HMI_CUSTOM_H_INCLUDED
#define __GMA_HMI_CUSTOM_H_INCLUDED

#include "gmaDefines.h"

#ifdef __cplusplus
extern "C" {
#endif


int16 gmaHmiOpen (void);

int16 gmaHmiClose (void);

/**
 * return the HMI handle
 */
uint32 gmaHmiGetHandle(void);

/**
 * Set the hmiHandle
 */
void gmaHmiSetHandle(uint32 hmiHandle);


/**
 * Set the beep status
 */
void gmaHmiSetBeepStatus(uint8 status);

/**
 * Get the beep status
 */
uint8 gmaHmiGetBeepStatus(void);



int16 gmaHmiKeyReq (void);

int16 gmaHmiKeyResultGet (void);

int16 gmaHmiMenu (const char* title, const char** itemList, uint8 length, uint8* choice, uint32 timeout);

int16 gmaHmiKeyTableUpdate (uint16 appId, gmaStructHeader_t *msg);

int16 gmaDisplayCustom (void);

int16 gmaDispInitConf (uint32 hmiHandle);

int16 gmaHmiGraphUpdate(void);

int16 gmaHmiDisplayText(uint32 line, uint32 column, char * text);

int16 gmaHmiAutoCentre(uint8 status);

int16 gmaHmiSetBackLightDef(uint8 value, uint8 setPerm);

int16 gmaHmiSetFont(void *font);

bool gmaHmiConfirm(const char *name, int len);

int16 gmaHmiSupCancel(void);

int16 gmaHmiClearLine(uint16 line);

/**
 * 
 */
int16 gmaHmiEditMask(char *mask, char *editItem, uint16 minLen, char *caption);

/**
 * Set the backlight
 *
 */
int16 gmaHmiBackLight(uint8 value);



int16 gmaDispGetDispSize(uint16 *height, uint16 *width);

#ifdef __cplusplus
}
#endif


#endif

