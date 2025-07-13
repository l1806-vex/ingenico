/*+
 *  PROJECT         :   TCP/IP Sample
 *  MODULE          :   Utilities
 *  FILEMANE        :   Utilities.h
 *  PURPOSE         :   Types for UIU
 *
 *  DESCRIPTION     :   Collection of utility functions for SDK samples
 *
 *  Copyright (c) 2012 Ingenico. All Rights Reserved.
 *
 *  Ingenico has intellectual property rights relating to the technology 
 *  embodied in this software.  In particular, and without limitation, 
 *  these intellectual property rights may include one or more patents.
 *
 *  This software is distributed under licenses restricting its use, 
 *  copying, distribution, and decompilation. No part of this software may be 
 *  reproduced in any form by any means without prior written authorization of 
 *  Ingenico.
 *
 * 
 *  HISTORY         :
 *
 *  Author:          Ingenico R&D Philippines Team
 *  Modification:    Creation
 *  Date:            2012/09/17
-*/
#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include <GL_GraphicLib.h>

/** \addtogroup utlgroup Utilities
 *
 * Contains the functions that are used for Telium Utilites
 *
 * @{
*/

/** \addtogroup prfgroup Peripheral handling
 *
 * Contains the functions that are used for handling Peripherals
 *
 * @{
*/

/** \weakgroup MAG Magnetic stripe processing
 * @{
 */

/** Open the associated channel.
 * Start waiting the magnetic stripe card.
 * Normally this function should be called just before magnetic card acquisition.
 * \return non-negative value if OK; negative otherwise
 * \header Utilities.h
 * \source Peripherals.c
 */
int magStart(void);             ///<start the magstripe perypheral

/** Stop waiting the magnetic stripe card.
 * Close the associated channel.
 * Normally this function should be called just after magnetic card acquisition.
 * \return non-negative value if OK; negative otherwise
 * \header Utilities.h
 * \source Peripherals.c
 */
int magStop(void);              ///<stop the magstripe perypheral

/** Verify whether a card is swiped; if so, copy its tracks into trk1, trk2, trk3 buffers.
 * If a pointer trk1, trk2, or trk3 is zero, the related track data will be ignored.
 * The size of buffers pointed by trk1, trk2, trk3 should be 128.
 * Please use getCard function instead as it is much more stable for Telium.
 * \param trk1 (O) Buffer to capture track1, this size of the buffer should be 128
 * \param trk2 (O) buffer to capture track2, this size of the buffer should be 128
 * \param trk3 (O) Buffer to capture track3, this size of the buffer should be 128
 * \return
 *    - negative if failure.
 *    - number of tracks read.
 *    - zero means that the card is not swiped.
 * \header Utilities.h
 * \source Peripherals.c
 */
int magGet(char *trk1, char *trk2, char *trk3); ///<get magstripe tracks

/** Process card input. The application waits for an external event: chip card inserted
 * or magnetic stripe card swiped or a key pressed or 30 sec timeout 
 *
 * The control string contains characters 'c', 'm' or 'k' to indicate what type of input is accepted.
 *
 * If a chip card is inserted the ATR is saved into buf and the value ‘c?is returned.
 *
 * If a magnetic stripe card is swiped the track1 is saved into buf+0,
 * the track2 into buf+128 and the track3 into buf+256 and the value 'm' is returned.
 * 
 * If a key is pressed it is saved into buf and the value 'k' is returned
 * Timeout of 30 seconds is set.
 *
 * Please use this function for Telium instead of magGet function for mag reader
 * interfacing as this is much stable.
 *
 * \param buf (I) Buffer to capture the input (character or ATR or 3 tracks)
 * \param ctl (I) control string containing 'c','k','m' to indicate what type of input is accepted
 *
 * \pre 
 *    - buf!=0; the size of the buffer should be not less that 128*3
 *    - ctl!=0
 *
 * \return  
 *    - 'k' if a key is pressed.
 *    - 'm' if a card is swiped.
 *    - 'c' if a card is inserted.
 *    -  0 in case of timeout.
 *    - negative in case of error.
 *
 * \header Utilities.h
 * \source Peripherals.c
*/
int getCard(unsigned char * buf, const char *ctl);   ///<process event card input

/** Wait until the chip card is removed
 * \return N/A
 * \header Utilities.h
 * \source Peripherals.c
*/
void detectCard(void); ///<detect if chip card is inserted

/** @} */

/** \weakgroup SMC Smart card processing
 * @{
 */
enum eIcc {                     ///<Smart card error processing codes
    iccBeg,                     ///< start sentinel
    iccCardRemoved,             ///< card removed
    iccCardMute,                ///< card mute
    iccCardPb,                  ///< other card problem
    iccDriverPb,                ///< driver problem
    iccReadFailure,             ///< Read error
    iccKO                       ///< unknown error
};

/** Open the associated channel for the default card reader.
 * \param rdr (I) 
 *  - right nibble: Reader number, 0..4
 *  - left nibble: 0 for EMV cards, 1 for ICC7816
 * \return non-negative value if OK; negative otherwise
 * \header Utilities.h
 * \source Peripherals.c
 */
int iccStart(unsigned char rdr);         ///<Open Integrated Circuit Card perypheral

/** Close the associated channel.
 * \param rdr (I) Reader number, 0..4
 * \return non-negative value if OK; negative otherwise
 * \header Utilities.h
 * \source Peripherals.c
 */
int iccStop(unsigned char rdr);          ///<Close Integrated Circuit Card perypheral

/** Check if ICC is present/inserted.
 * \param rdr (I) Reader number, 0..4
 * \return 1 if ICC is present, 0 otherwise.
 * \header Utilities.h
 * \source Peripherals.c
 */
int iccDetect(unsigned char rdr);        ///<Detect card

/** Send a command cmd followed by data dat to the card; capture the result into rsp.
 *
 * The command cmd consists of  5 bytes:
 *  - 0) TYP is the command type, can take values in the range 0..4:
 *    - 0: without any protocol
 *    - 1:  no input, no output
 *    - 2: no input, some output
 *    - 3: some input, no ouput
 *    - 4: some input, some output
 *  - 1) CLA: class byte
 *  - 2) INS: instruction byte
 *  - 3) P1: parameter 1 byte
 *  - 4) P1: parameter 2 byte
 * The data dat consists of the length of data and the data itself.
 *
 * So:
 * - the length of input data, if any, is given in the first byte of dat array
 * - the length of output data, if any, is given in the cmdLC byte of command
 *
 * The pointers can take NULL values:
 *  - If cmd is zero, it means POWER ON command
 *  - If dat is zero, it means that there is no data (the type byte should take proper value in this case)
 *  - If rsp is zero, it means that no output is expected
 *
 * Response length can be given as the first byte of rsp; zero means: get all data
 * \param rdr (I) Reader number, 0..4
 * \param cmd (I) Command to send, consists of 6 bytes: TYP,CLA,INS,P1,P2,LC; for POWER ON command the pointer cmd should be zero
 * \param dat (I) Data to send; zero pointer if there is no data. The first byte is the length of the data; after that the data array follows
 * \param rsp (O) Buffer to capture card response, this size of the buffer should be 260
 * \return
 *    - (-eIcc code) if failure.
 *    - length of response if OK.
 *    - Zero return value means that there is not card inserted (no response).
 * \header Utilities.h
 * \source Peripherals.c
 */
int iccCommand(unsigned char rdr, const unsigned char * cmd, const unsigned char * dat, unsigned char * rsp);   ///<Send a command and data to a smart card and retrieve the response

/** @} */

/** \weakgroup PRT Printer processing
 * @{
 */

/** Open the associated channel.
 * Should be called before calling any printing, normally before an event treatment.
 * \return
 *    - negative if failure.
 *    - non negative if OK.
 * \header Utilities.h
 * \source Peripherals.c
 */
int prtStart(void);             ///<Start printer perypheral

/** Close the associated channel.
 * Should be called before returning to the idle prompt or before giving the control to another application.
 * \return
 *    - negative if failure.
 *    - non negative if OK.
 * \header Utilities.h
 * \source Peripherals.c
 */
int prtStop(void);              ///<Stop printer perypheral

/** Control paper presence for associated channel.
 * Should be called before printing
 * \return
 *    - negative if failure.
 * 	  - zero if paper is absent
 *    - positive if paper is present or if no information available.
 * \header Utilities.h
 * \source Peripherals.c
 */
int prtCtrl(void);              ///<Control paper presence

/** @} */

/** \weakgroup DSP Display processing
 * @{
 */

/** Open the associated channel.
 * Should be called before calling any display processing,
 * normally before an event treatment.
 * \return non-negative value if OK; negative otherwise
 * \header Utilities.h
 * \source Peripherals.c
 */
int dspStart(void);             ///<Start display perypheral

/** Close the associated channel.
 * Should be called before returning to the idle prompt or before giving the control to another application.
 * \return non-negative value if OK; negative otherwise
 * \header Utilities.h
 * \source Peripherals.c
 */
int dspStop(void);              ///<Stop display perypheral

/** @} */

/** \weakgroup KBD Keyboard processing
 * @{
 */

/** Start waiting for a key.
 * This function should be called when an application is ready to accept a user input.
 * The keys waiting in the buffer are flushed if fls is not zero.
 * \param fls (I) Indicates whether key flush is to be done
 * \return non-negative value if OK; negative otherwise
 * \header Utilities.h
 * \source Peripherals.c
 */
int kbdStart(unsigned char fls);         ///<start waiting for a key

/** Stop waiting for a key. All the keys pressed after calling this function will be ignored.
 * \return 0
 * \header Utilities.h
 * \source Peripherals.c
*/
int kbdStop(void);              ///<stop waiting for a key

/** Retrieve a key pressed if any. Return its key code.
 * \return
 *    - Key code according to eKbd enum.
 *    - If no key pressed zero value is returned.
 *    - In case of error it returns 0xFF.
 * \header Utilities.h
 * \source Peripherals.c
 */
char kbdKey(void);              ///<get a key pressed

/** @} */

/** \weakgroup TFT Touch Screen processing
 * @{
 */

/** Start waiting for a touch.
 * This function should be called when an application is ready to accept a user input.
 * \return non-negative value if OK; negative otherwise
 * \header Utilities.h
 * \source Peripherals.c
 */
int tftStart(void);

/** Stop waiting for a touch.
 * \return non-negative value if OK; negative otherwise
 * \header Utilities.h
 * \source Peripherals.c
 */
int tftStop(void);

/** @} */

/** \weakgroup TMR Timer processing
 * There can be up to tmrN timers
 *
 * The first parameter tmr of the functions below is the timer number (0..tmrN-1)
 *
 * The parameter dly (delay) is the number of centiseconds to wait
 * @{
 */

/** Start a timer number tmr for dly/100 seconds.
 *
 * There are 4 timers numbered from 0 to 3.
 *
 * After starting a timer a function tmrGet() should be called to know whether it is over or not.
 *
 * The timer should be over after dly/100 seconds.
 *
 * \param tmr (I)  Timer number 0..tmrN-1
 * \param dly (I)  Initial timer value in hundredth of second
 * \return non-negative value if OK; negative otherwise
 * \header Utilities.h
 * \source Peripherals.c
 */
int tmrStart(unsigned char tmr, int dly);    ///<start the timer tmr for dly centiseconds

/** Return the state of the timer tmr.
 * \param tmr (I) Timer number 0..tmrN-1
 * \return
 *    - negative if failure.
 *    - otherwise the number of centiseconds rest.
 * \header Utilities.h
 * \source Peripherals.c
 */
int tmrGet(unsigned char tmr);           ///<get the number of centiseconds waitng for timer tmr

/** Stop a timer number tmr.
 *
 * Should be called when the timer is no more needed.
 * \param tmr (I) Timer number 0..tmrN-1
 * \return no
 * \header Utilities.h
 * \source Peripherals.c
 */
void tmrStop(unsigned char tmr);         ///<stop the timer tmr

/** @} */
/** @} */

/** \addtogroup prtgroup Printing Functions
 *
 * Printer.c/h contains the functions that are used Goal Printing
 *
 * @{
*/

/** Adds the string str to the document which can be printed by calling the function printDocument()
 * \param str (I) String to be added to the document.
 * \return
 *    - negative if failure.
 *    - non negative if OK.
 * \header Utilities.h
 * \source Printer.c
 */
int printText(const char *str);

/** Print a document containing data prepared through calling the function printText().
 * \header Utilities.h
 * \source Printer.c
 */
void printDocument(void);

/** @} */

/** \addtogroup stagroup State
 *
 * Contains the functions that are used for states processing
 *
 * @{
*/

// Input automaton state
enum {
    STATE_OK, 
    STATE_NEXT,
    STATE_BACK,
    STATE_SET,
    STATE_ABORT,    
    STATE_FAILED = -1
};

/** Get the next state.
 * \header Utilities.h
 * \source State.c
 */
void stateNext(void);

/** Get the previous state.
 * \header Utilities.h
 * \source State.c
 */
void statePrev(void);

/** Set the next state.
 * \param nextState (I) State to be set
 * \header Utilities.h
 * \source State.c
*/
void stateSet(int nextState);

/** Get the current state.
 * \return
 *  - current state
 * \header Utilities.h
 * \source State.c
*/
int stateGet(void);

/** @} */

/** \addtogroup trcgroup Trace
 *
 * Contains the functions that are used for tracing
 *
 * @{
*/

/** Trace where an error occured
 * It is a shortcut to call traceFS  and traceFL.
 * \param cond (I) Conditional statement to be checked
 * \param file (I) Source file name, usually srcFile pointing to __FILE__ macro
 * \param line (I) Source line, usually __LINE__ macro
 * \return none
 * \header Utilities.h
 * \source Trace.c
 */
extern void errChk(const char *cond, const char *file, word line); ///<trace error and continue

/** Trace where a fatal error occured
 * It is a shortcut to call traceFS  and traceFL.
 * \param cond (I) Conditional statement to be checked
 * \param file (I) Source file name, usually srcFile pointing to __FILE__ macro
 * \param line (I) Source line, usually __LINE__ macro
 * \return none
 * \header Utilities.h
 * \source Trace.c
 */
extern void errVrf(const char *cond, const char *file, word line); ///<trace error and stop

// Macros & preprocessor definitions.
//-------------------------------------------------------------------
#define CHECK(CND,LBL) {if(!(CND)){errChk(#CND,__FILE__,(word)__LINE__); goto LBL;}}
#define VERIFY(CND) {if(!(CND)){errVrf(#CND,__FILE__,(word)__LINE__);}}
#define CHK(CND,LBL) {if(!(CND)) goto LBL;}

#define BIT(B) (0x01<<(B-1))

#ifdef __TRACE__

/** Put string str into the trace file.
 *
 * It is defined as an empty macro in non-testing mode.
 * \param str (I) String to trace
 * \return none
 * \header Utilities.h
 * \source Trace.c
 */
extern void _trcS(const char *str);  ///<Trace a string

/** Put string source file name and line into the trace file.
 * It is defined as an empty macro in non-testing mode.
 * \param file (I) Source file name, usually srcFile pointing to __FILE__ macro
 * \param line (I) Source line, usually __LINE__ macro
 * \return none
 * \header Utilities.h
 * \source Trace.c
 */
extern void _trcFL(const char *file, int line);  ///<Trace source file name and line

/** Put string str formatted by sprintf function using fmt string into the trace file.
 * It is defined as an empty macro in non-testing mode.
 * \param  fmt (I) Format string for sprintf function.
 * \param  str (I) String to trace.
 * \return none
 * \header Utilities.h
 * \source Trace.c
 */
extern void _trcFS(const char *fmt, const char *str);    ///<Trace formatted string

/** Put a numeric value num formatted by sprintf function using fmt string into the trace file.
 *
 * It is defined as an empty macro in non-testing mode.
 * \param opt (I) Trace option; if zero tracing will not be done
 * \param fmt (I) Format string for sprintf function.
 * \param num (I) Number to trace.
 * \return none
 * \header Utilities.h
 * \source Trace.c
 */
extern void _trcFN(const char *fmt, long num);   ///<Trace formatted number

/** Trace a binary buffer of length len. Each byte is traced as is.
 *
 * It is defined as an empty macro in non-testing mode.
 * \param buf (I) Pointer to the buffer to trace.
 * \param len (I) Number of bytes to be traced.
 * \return none
 * \header Utilities.h
 * \source Trace.c
 * \remark End of line is not traced. It should be added separately if needed.
 */
extern void _trcBuf(const byte * buf, int len);  ///<Trace binary data of a given length as is

/** Trace a binary buffer of length len. Each byte is traced as a hex value.
 * The bytes are separated by spaces.
 *
 * It is defined as an empty macro in non-testing mode.
 * \param buf (I) Pointer to the buffer to trace.
 * \param len (I) Number of bytes to be traced.
 * \return none
 * \header Utilities.h
 * \source Trace.c
 * \remark End of line is not traced. It should be added separately if needed.
 */
extern void _trcBN(const byte * buf, int len);   ///<Trace binary data in HEX of a given length

/** Trace a binary buffer of length len. Each byte is traced as an ascii value.
 * The values less than 0x20 and greater than 0x7F are replaced by question marks ‘?’.
 *
 * It is defined as an empty macro in non-testing mode.
 * \param buf (I) Pointer to the buffer to trace.
 * \param len (I) Number of bytes to be traced.
 * \return none
 * \header Utilities.h
 * \source Trace.c
 */
extern void _trcAN(const byte * buf, int len);   ///<Trace ASCII data of a given length

/** Trace a binary buffer of length len in binary and ascii format.
 * It is a shortcut to call traceBN  and traceAN.
 * \param buf (I) Pointer to the buffer to trace.
 * \param len (I) Number of bytes to be traced.
 * \return none
 * \header Utilities.h
 * \source Trace.c
 */
extern void _trcBAN(const byte * buf, int len);  ///<Trace data in HEX and ASCII format

/** Trace an error code.
 * It is defined as an empty macro in non- testing mode.
 * A simple call of traceFN() is performed here.
 * \param err (I) Number to trace.
 * \return none
 * \header Utilities.h
 * \source Trace.c
 */
extern void _trcErr(long err);   ///<Trace en error value

#define trcS(s) _trcS(s)
#define trcFL(f,l) {} _trcFL(f,l)
#define trcFS(f,s) {} _trcFS(f,s)
#define trcFN(f,n) {} _trcFN(f,n)
#define trcBuf(b,n) {} _trcBuf(b,n)
#define trcBN(b,n) {} _trcBN(b,n)
#define trcAN(b,n) {} _trcAN(b,n)
#define trcBAN(b,n) {} _trcBAN(b,n)
#define trcErr(n) {} _trcErr(n)
#else
#define trcS(s) {}
#define trcFL(f,l) {}
#define trcFS(f,s) {}
#define trcFN(f,n) {}
#define trcBuf(b,n) {}
#define trcBN(b,n) {}
#define trcAN(b,n) {}
#define trcBAN(b,n) {}
#define trcErr(n) {}
#endif

/** @} */

/** \addtogroup hmigroup User Interface Helpers
 *
 * UserInterface.c/h contains the functions that are used for communication testing
 *
 * @{
*/

// Macros & preprocessor definitions.
//-------------------------------------------------------------------

///Combine two bytes into a word
#define WORDHL(H,L) ((unsigned short)((((unsigned short)H)<<8)|((unsigned short)L)))
///Extract highest byte from a word
#define HBYTE(W) (unsigned char)(((unsigned short)W&0xFF00)>>8)
///Extract lowest byte from a word
#define LBYTE(W) (unsigned char)((unsigned short)W&0x00FF)
///Combine two words into a card
#define CARDHL(H,L) ((unsigned long)((((unsigned long)H)<<16)|((unsigned long)L)))
///Extract highest word from a card
#define HWORD(C) (unsigned short)(((unsigned long)C&0xFFFF0000UL)>>16)
///Extract lowest word from a card
#define LWORD(C) (unsigned short)((unsigned long)C&0x0000FFFFUL)

enum eMnuType {
    mnuTypeBeg,
    mnuTypeDialog,
    mnuTypeIcon,
    mnuTypeButton,
    mnuTypeEnd
}; ///<Menu Type

// Functions.
//-------------------------------------------------------------------

/** Open the associated channel.
 * Should be called before calling any GUI/GOAL Functions.
 *
 *
 * \return
 *  - GOAL Graphic Library handler
 *   
 * \header Utilities.h
 * \source UserInterface.c
*/
T_GL_HGRAPHIC_LIB guiStart(void);

/** Close the associated channel.
 * Cose the GOAL handler.
 *
 * \return 1 if OK
 *   
 * \header Utilities.h
 * \source UserInterface.c
*/
void guiStop(void);

/** Dialog to display Info screen
 *
 * \param title (I) title ofthe screen
 * \param text (I) text to be displayed on the screen
 * \param icon (I) Icon to be displayed with the message
 * \param dly (I) Timeout delay
 *
 * \return
 *  - key returned
 *   
 * \header Utilities.h
 * \source UserInterface.c
*/
int guiScreen(char *title, char *text, int icon, int delay);

/** Display GOAL Menu Dialog
 * There are 3 kinds of GOAL Menu displays
 * - ICON MENU 
 * - ICON BUTTON MENU and
 * - DIALOG MENU
 *
 * \param type (I) menu type
 * \param hdr (I) The menu header
 * \param mnu (I) menu items 
 * \param sta (I) current menu item selected 
 *
 * \return
 *  - key returned
 *   
 * \header Utilities.h
 * \source UserInterface.c
*/
int guiMenu(int type, int sta, const char *hdr, const char **mnu);

/** Dialog for string input
 * If during waiting a key is pressed the function returns the code of the key pressed.
 * \param title (I) title ofthe screen
 * \param text (I) text to be displayed on the screen
 * \param buf (I) input buffer
 * \param len (I) size of the input buffer
 * \return
 *  - the key or button pressed
 * \header Utilities.h
 * \source UserInterface.c
*/
unsigned long enterStr(char *title, char *text, char *buf, int len);

/** Dialog for numeric password input
 * If during waiting a key is pressed the function returns the code of the key pressed.
 * \param title (I) title ofthe screen
 * \param text (I) text to be displayed on the screen
 * \param buf (I) input buffer
 * \param len (I) size of the input buffer
 * \return
 *  - the key or button pressed 
 * \header Utilities.h
 * \source UserInterface.c
*/
unsigned long enterPwd(char *title, char *text, char *buf, int len);

/** Dialog for alphanumeric password input
 * If during waiting a key is pressed the function returns the code of the key pressed.
 * \param title (I) title ofthe screen
 * \param text (I) text to be displayed on the screen
 * \param buf (I) input buffer
 * \param len (I) size of the input buffer
 * \return
 *  - the key or button pressed 
 * \header Utilities.h
 * \source UserInterface.c
*/
unsigned long enterPwdTxt(char *title, char *text, char *buf, int len);

/** Dialog for amount input
 * If during waiting a key is pressed the function returns the code of the key pressed.
 * \param title (I) title ofthe screen
 * \param text (I) text to be displayed on the screen
 * \param buf (I) input buffer
 * \param len (I) size of the input buffer
 * \param exp (I) number of decimal places
 * \return
 *  - the key or button pressed 
 * \header Utilities.h
 * \source UserInterface.c
*/
unsigned long enterAmt(char *title, char *text, char *buf, int len, int exp);

/** Dialog for IP adddress input
 * If during waiting a key is pressed the function returns the code of the key pressed.
 * \param title (I) title ofthe screen
 * \param text (I) text to be displayed on the screen
 * \param buf (I) input buffer
 * \param len (I) size of the input buffer
 * \return
 *  - the key or button pressed 
 * \header Utilities.h
 * \source UserInterface.c
*/
unsigned long enterTcp(char *title, char *text, char *buf, int len);

/** Dialog for text input
 * If during waiting a key is pressed the function returns the code of the key pressed.
 * \param title (I) title ofthe screen
 * \param text (I) text to be displayed on the screen
 * \param buf (I) input buffer
 * \param len (I) size of the input buffer
 * \return
 *  - the key or button pressed 
 * \header Utilities.h
 * \source UserInterface.c
*/
unsigned long enterTxt(char *title, char *text, char *buf, int len);

/** Date Input
 * If during waiting a key is pressed the function returns the code of the key pressed.
 * \param title (I) title ofthe screen
 * \param text (I) text to be displayed on the screen
 * \param buf (I) input buffer
 * \param len (I) size of the input buffer
 * \return
 *  - the key or button pressed 
 * \header Utilities.h
 * \source UserInterface.c
*/
unsigned long enterDate(char *title, char *text, char *buf, int len);

/** Time Input
 * If during waiting a key is pressed the function returns the code of the key pressed.
 * \param title (I) title ofthe screen
 * \param text (I) text to be displayed on the screen
 * \param buf (I) input buffer
 * \param len (I) size of the input buffer
 * \return
 *  - the key or button pressed 
 * \header Utilities.h
 * \source UserInterface.c
*/
unsigned long enterTime(char *title, char *text, char *buf, int len);

/** @} */

/** \addtogroup stmgroup File/Ram Stream Processing
 *
 * Contains the functions that are used for streams processing
 *
 * @{
*/

typedef struct sStream tStream;

typedef struct sStmVmt
{
    int (*get)(tStream *stm); ///<virtual method table for stream get
    int (*put)(tStream *stm, unsigned char buf); ///<virtual method table for stream put
    void (*close)(tStream *stm); ///<virtual method table for stream close
} tStmVmt;

struct sStream
{
    const tStmVmt *vmt; ///<virtual method table for get, put and close
    char mode; ///<'r' read or 'w' write mode
};

/** Initialize Ram stream processing and the virtual method table
 * \param buf (I) stream buffer 
 * \param len (I) size of the stream buffer  
 * \param mod (I) access mode: 'r'= read, 'w'= write
 * \return pointer to the stream descriptor; NULL in case of error
 * \header Utilities.h
 * \source RamManagement.c
 */
tStream *stmRamInit(unsigned char *buf, unsigned int len, char mod);  ///<initialize a ram stream

/** Initialize file stream processing and the virtual method table
 * \param file (I) file handle for file stream
 * \param mod (I) access mode: 'r'= read, 'w'= write, 'a'=append
 * \return pointer to the stream descriptor; NULL in case of error
 * \header Utilities.h
 * \source FileManagement.c
 */
tStream *stmFileInit(const char *file, char *mod);  ///<initialize a file stream

/** Get 1 byte from the stream:
 * \param stm (I) pointer to the stream descriptor
 * \param b (O) pointer to the destination buffer 
 * \return number of bytes retrieved; negative in case of error
 * \header Utilities.h
 * \source Stream.c
 */
int stmGet(tStream *stm);

/** Get "len" bytes from the stream:
 * \param stm (I) pointer to the stream descriptor
 * \param b (O) pointer to the destination buffer 
 * \param len (I) length of data reserved in the destination buffer 
 * \return number of bytes retrieved; 0 in case of error
 * \header Utilities.h
 * \source Stream.c
 */
int stmGetBuf(tStream *stm, unsigned char *buf, unsigned int len); ///<get len bytes from the stream

/** Put 1 byte to the stream:
 * \param stm (I) pointer to the stream descriptor
 * \param b (O) pointer to the destination buffer 
 * \return number of bytes added to the stream; 0 in case of error
 * \header Utilities.h
 * \source Stream.c
 */
int stmPut(tStream *stm, unsigned char buf);

/** Put "len" bytes to the stream:
 * \param stm (I) pointer to the stream descriptor
 * \param b (I) pointer to the destination buffer 
 * \param len (I) length of data reserved in the destination buffer 
 * \return number of bytes added to the stream; negative in case of error
 * \header Utilities.h
 * \source Stream.c
 */
int stmPutBuf(tStream *stm, const unsigned char *buf, unsigned int len); ///<put len bytes from the stream

/** Put 1 byte to the stream:
 * \param stm (I) pointer to the stream descriptor
 * \return none
 * \header Utilities.h
 * \source Stream.c
 */
void stmClose(tStream *stm); ///<close the stream
/** @} */

/** \addtogroup dpmgroup Data Processing Module
 *
 * Contains the functions that are used for Data Processing Module
 *
 * @{
*/

/** Initialise Data Procesing
 * Initial data is obtain from PARAM.XML then the parsed data is saved later to the data storage file (DBS.TXT)
 * \return number of characters saved into the database
 * \header Utilities.h
 * \source ParamManagement.c
 */
int dpmInit(const char*filename);

/** Obtain the data from the database
 * \param id (I) database identifier based from the parameter index in the XML file
 * \param buf (O) pointer to the destination buffer 
 * \param len (I) length to the destination buffer 
 * \return number of bytes obtained from the database
 * \header Utilities.h
 * \source ParamManagement.c
 */
int dpmGet(int id, char *buf, int len);

/** Save the data to the database
 * \param id (I) database identifier based from the parameter index in the XML file
 * \param buf (I) pointer to the source buffer 
 * \param len (I) length of the source buffer 
 * \return number of bytes saved to the database
 * \header Utilities.h
 * \source ParamManagement.c
 */
int dpmPut(int id, char *buf, int len);
/** @} */

/** @} */

//-------------------------------------------------------------------
//-------------------------------------------------------------------
#endif // __UTILITIES_H__

