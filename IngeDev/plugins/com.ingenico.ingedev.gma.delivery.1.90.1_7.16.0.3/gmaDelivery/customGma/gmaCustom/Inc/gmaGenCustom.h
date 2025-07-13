
#ifndef __GMA_GEN_CUSTOM_H_INCLUDED
#define __GMA_GEN_CUSTOM_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @file gmaGenCustom.h
 */

/**
 * Number of columns used in the menu
 */
#define GMA_DISPLAY_NUM_COL           (16)

/**
 * Maximum number of plugins menu itens
 */
#define GMA_MAX_PG_MENU_ITEMS         (50)

/**
 * Maximum number of edit resource items
 */
#define GMA_MAX_PG_EDIT_RES_ITENS     (30)


#define BACKLIGHT_TIMEOUT (1000)
#define BACKLIGHT_NONE    (0xFFFFFFFF)

/**
 * Structure to hold the menu items
 */
typedef struct
{
	uint16 appId; //!< appId of the plugin that adds this item
	uint8  logicalId; //!< logicalId of the plugin that adds this item
	char   itemString[GMA_DISPLAY_NUM_COL+1]; //!< the menu item string
	uint8  itemId; //!< the menu item identifier
	uint8  action; //!< action to be executed when this menu item is selected
   uint32 parameter; //!< the parameter of the action when needed
}sPlugInMenuItem_t;

/**
 * Structure to hold the plugins that have added menu itens to the technical menu
 */
typedef struct
{
	uint16 appId; //!< application Id of the plugin
	uint8  logicalId; //!< logical Id of the plugin
	uint8  numOfItems; //!< number of menu items added by this plugin
	//char   PGName[GMA_DISPLAY_NUM_COL+1]; //!< plugin Name
}sPlugInMenuList_t;

/**
 * Structure to hold the edit string resource
 */
typedef struct 
{
   uint16 appId; //!< appId of the plugin that adds this item
   uint8 logicalId; //!< logicalId of the plugin that adds this item
   uint8 itemId; //!< edit string resource identifier
   uint8 minLength; //!< minimum length of the string
   char caption[16+1]; //!< text to be shown above the edition field
   char mask[30+1]; //!< edition mask
}sPlugInEditResource_t;

int16 gmaTecFunMenuAddItem (uint16 appId, gmaStructHeader_t *msg);

int16 gmaTecFunDisplayPGMenu (void);

int16 gmaTecFunAddEditResource(uint16 appId, gmaStructPGEditResource_t *msg);

int16 gmaCustomSelectApp(uint8* acceptLevel, uint16* appID, uint8* logicalID);

int16 gmaCustomAppMenu(uint16* indexList, uint16 length);

int16 gmaCustomMsgFromPlugIn(uint16 appId, gmaStructHeader_t *msg);

// Add here as this function is called from the gmaAppMsgCustom.c
int16 gmaPGTreatBroadcastMessageMain(void *msgRec, uint32 param2);

// Add here as this function is called from the gmaAppMsgCustom.c
int16 gmaPGtreatTransactionReqMsgmain(void *msg, uint32 param2);

int16 gmaCustomMsgFromApp (uint16 appId, gmaStructHeader_t *msg);

uint8 gmaCustomGetAppType (uint16 appId);

void gmaCustomGenSettMnOneItemBeh(uint8 behaviour);

void gmaCustomUtilBLDisable (void);
void gmaCustomUtilBLEnable (uint32 timeout);
void gmaCustomUtilConfigBLE(uint8 status, uint32 timeout);

#ifdef __cplusplus
}
#endif


#endif

