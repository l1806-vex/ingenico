#ifdef __cplusplus
extern "C" {
#endif

#ifndef HOMESCREEN_H
#define HOMESCREEN_H

//! \addtogroup KSFAM_HOME_SCREEN
//! \{

//! \brief  <a href="ICO-OPE-00471-EN-HomeScreen Specification.html">HowTo Use Home Screen</a> describes the home screen configuration.

#define APPLI_TYPE_HOME_SCREEN 0xAD58

#define MOSAIC_FORMAT 0
#define ICON_LIST_FORMAT 1
#define TEXT_LIST_FORMAT 2

#define HOME_SCREEN_STATE           200  //!< SELECTING mode : allows to know the home screen state. 
#define HOME_SCREEN_READ_PARAM      201  //!< SELECTING mode : allows to read the home screen parameters.  
#define HOME_SCREEN_WRITE_PARAM     202  //!< SELECTING mode : allows to write the home screen parameters. 

typedef struct
{
    int State_HomeScreen;
    int HomeScreenConfiguration;
    int Header_HomeScreen;
    int Time_out_HS;
    int ruf[64];

} HS_PARAMS;

typedef struct{
   int status_home_screen;
   int ruf[64];
}StatusInfosHomeScreen;

//! \section Sample HomeScreen
//! \include Home_Screen_Sample_01.c

//! \link KSFAM_HOME_SCREEN Back to top @endlink


//! @}

#endif
#ifdef __cplusplus
}
#endif
