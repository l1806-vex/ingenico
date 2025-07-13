/*
   Custom Definitions and Types for GMA

   Unicapt32 - GMA Application
*/

/**
 * @file gmaCustomDefines.h
 *
 * General custom definitions
 */

#ifndef CUSTOM_DEFINES_H
#define CUSTOM_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Plugin menu title
 */
#define GMA_PG_MENU_TITLE              (IDS_PLUGIN_MENU_TITLE)

/**
 * Plugin menu timeout
 */
#define GMA_PG_MENU_TIMEOUT           (6000)

/* app selection menu defines */

/**
 * menu application timeout
 */
#define GMA_APP_MENU_TIMEOUT           (6000)

/**
 * Menu font type
 */
#define GMA_APP_MENU_FONT              (HMI_INTERNAL_FONT_1)
#define GMA_APP_MENU_TITLE_FONT        (HMI_INTERNAL_FONT_2)

#define GMA_APP_MENU_ERROR             (-1)

/**
 * Application menu title
 */
#define GMA_APP_MENU_TITLE             (IDS_SEL_APPLICATION)

#define GMA_NO_FUNC_AVAILABLE          (-1)
#define GMA_NO_FUNC_SELECTED           (GMA_NO_FUNC_AVAILABLE-1)

/**
 * Define the number of screen updates before change the application logo
 */
#define GMA_IDLE_SCREEN_PERIOD         (20)

/**
 * Used to identify that a media data is from a plugin
 */
#define GMA_MEDIA_CUSTOM_PGIN          (10)
/**
 * Used to identify that a media data is from an application
 */
#define GMA_MEDIA_CUSTOM_APPL          (11)
/**
 * Used to identify that a media data is hidden.
 */
#define GMA_MEDIA_CUSTOM_HIDE          (12)

#define GMA_MEDIA_LOGO_EMPTY           (1)
#define GMA_MEDIA_LOGO_CHANGE          (2)
#define GMA_MEDIA_LOGO_DISPLAY         (3)



#ifdef __cplusplus
}
#endif

#endif

