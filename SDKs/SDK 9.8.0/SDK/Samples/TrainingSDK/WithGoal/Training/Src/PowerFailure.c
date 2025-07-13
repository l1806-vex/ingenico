//****************************************************************************
//       INGENICO                                INGEDEV 7                   
//============================================================================
//       FILE  POWERFAILURE.C                      (Copyright INGENICO 2012)
//============================================================================
//  Created :       13-July-2012     Kassovic
//  Last modified : 13-July-2012     Kassovic
//  Module : TRAINING                                                          
//                                                                          
//  Purpose :                                                               
//                    *** RegisterPowerFailure management ***
//  On EFT30/SMART, there is a capacitor which is able to back up the RAM
//  for 50ms (Backup is limited to 80kb for all applications and system =>
//  5kb max per app).
//  So the RAM area declared by the RegisterPowerFailure function is copied
//  from RAM to FLASH only when a power failure (i.e. main power cut)
//  is detected.
//  On all other terminals, because of design, there is no such capacitor.
//  Consequence is that copy from RAM to FLASH can't be done when a power failure
//  (i.e. battery removal) is detected. So there is a special mechanism where
//  the hardware detection is replaced by a 100ms timer. To prevent useless
//  writing in FLASH, data are saved only if they changed since last timer tick.
//  This means that developer must handle power failure the same way on all
//  Telium terminals. In all cases, its task is just to register the RAM area
//  which has to be saved/restored. Telium system will do all the job! The only
//  goal of the explanations are maybe to prevent the developer to register data
//  which change very often. In that case, the life time of the Flash could be
//  affected and garbage collection will occur frequently.
//                                                                            
//  List of routines in file :  
//      WriteInRam : Write in RAM protected by RegisterPowerFailure().
//      ReadFromRam : Read from RAM protected by RegisterPowerFailure().
//                            
//  File history :
//  071312-BK : File created
//                                                                           
//****************************************************************************

//****************************************************************************
//      INCLUDES                                                            
//****************************************************************************
#include "SDK30.H"
#include "Training.h"

//****************************************************************************
//      EXTERN                                                              
//****************************************************************************
extern T_GL_HGRAPHIC_LIB xGoal; // New instance of the graphics object library

// Buffer saved automatically from RAM to FLASH in case of power failure
extern char tcPowerFailure[5*1024];

//****************************************************************************
//      PRIVATE CONSTANTS                                                   
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE TYPES                                                       
//****************************************************************************
    /* */

//****************************************************************************
//      PRIVATE DATA                                                        
//****************************************************************************
// Properties of the Power screen (Goal)
// =====================================
static const ST_DSP_LINE txPower[] =
{
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_YELLOW, GL_COLOR_BLACK,   0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line0
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, TRUE,    0, FALSE, {2, 0, 2, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE,  GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line1
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE,  GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line2
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, GL_COLOR_WHITE,  GL_COLOR_BLACK, 100, FALSE, {1, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line3
	  {GL_ALIGN_LEFT,   GL_ALIGN_CENTER, FALSE, 100, FALSE, {2, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} },
	{ {GL_ALIGN_CENTER, GL_ALIGN_CENTER, GL_COLOR_RED,    GL_COLOR_BLACK,   0, FALSE, {0, 0, 0, 0}, {0, 0, 0, 0, GL_COLOR_WHITE}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}}, // Line4
	  {GL_ALIGN_CENTER, GL_ALIGN_CENTER, TRUE,    0, FALSE, {2, 0, 2, 0}, {0, 0, 0, 0, GL_COLOR_BLACK}, {0, 0, 0, 0}, {NULL, GL_FONT_STYLE_NORMAL, GL_SCALE_MEDIUM}} }
};

//****************************************************************************
//                       void WriteInRam (char *pcMsg)
//  This function writes a message inside a buffer in RAM protected by the
//  function RegisterPowerFailure() (See entry.c).
//   - RegisterPowerFailure() : save a RAM data area into FLASH
//                              in case of power failure.
//  This function has parameters.
//		ucMsgNbr (I-) : Message number to write (Msg1 or Msg2).
//  This function has no return value.                                      
//****************************************************************************

void WriteInRam (byte ucMsgNbr)
{
	// Local variables 
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	int iRet;

    // Buzzer management
	// *****************
	xScreen = GoalCreateScreen(xGoal, txPower, NUMBER_OF_LINES(txPower), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                           // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, 0, false);
	CHECK(iRet>=0, lblKO);

    memset (tcPowerFailure, 0, sizeof(tcPowerFailure));
    if (ucMsgNbr == 1)
    	strcpy(tcPowerFailure, "Hello, do you hear me?\n"  // Write message1 in RAM
							   "Hello, do you hear me?\n"
							   "Hello, do you hear me?");
    else
    	strcpy(tcPowerFailure, "Hi, how are you doing?\n"  // Write message2 in RAM
							   "Hi, how are you doing?\n"
							   "Hi, how are you doing?");

	iRet = GoalDspLine(xScreen, 0, "Msg in RAM :", &txPower[0], 0, false);
	CHECK(iRet>=0, lblKO);
	iRet = GoalDspMultiLine(xScreen, 1, tcPowerFailure, strlen(tcPowerFailure), txPower, NUMBER_OF_LINES(txPower), 0, false);
	CHECK(iRet>=0, lblKO);                                 // Show message written
	iRet = GoalDspLine(xScreen, 4, "Reboot terminal !", &txPower[4], 60*1000, true);
	CHECK(iRet>=0, lblKO);                                 // Unplug terminal then read RAM to see that
	                                                       // the message has been restored properly
	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                     // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);                       // Destroy screen
}

//****************************************************************************
//                       void ReadFromRam(void)
//  This function reads a message from a buffer in RAM protected by the
//  function RegisterPowerFailure() (See entry.c).
//   - RegisterPowerFailure() : Restore a RAM data area from FLASH
//                              in case of power failure.
//  This function has no parameters.
//  This function has no return value.
//****************************************************************************

void ReadFromRam(void)
{
	// Local variables
    // ***************
	T_GL_HWIDGET xScreen=NULL;
	int iRet;

    // Buzzer management
	// *****************
	xScreen = GoalCreateScreen(xGoal, txPower, NUMBER_OF_LINES(txPower), GL_ENCODING_UTF8);
	CHECK(xScreen!=NULL, lblKO);                              // Create screen and clear it
	iRet = GoalClrScreen(xScreen, GL_COLOR_BLACK, KEY_CANCEL | KEY_VALID, false);
	CHECK(iRet>=0, lblKO);

	iRet = GoalDspLine(xScreen, 0, "Msg in RAM :", &txPower[0], 0, false);
	CHECK(iRet>=0, lblKO);                                    // Show message written
	iRet = GoalDspMultiLine(xScreen, 1, tcPowerFailure, strlen(tcPowerFailure), txPower, NUMBER_OF_LINES(txPower), 30*1000, true);
	CHECK(iRet>=0, lblKO);

	goto lblEnd;

	// Errors treatment
    // ****************
lblKO:                                                        // None-classified low level error
	GL_Dialog_Message(xGoal, NULL, "Processing Error", GL_ICON_ERROR, GL_BUTTON_VALID, 5*1000);
lblEnd:
	if (xScreen)
		GoalDestroyScreen(&xScreen);                          // Destroy screen
}
