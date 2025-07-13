// $Id: GL_Samples.h,v 1.1.2.22 2013/01/18 16:06:05 rbertholet Exp $
#ifndef GL_Samples_h_INCLUDED
#define GL_Samples_h_INCLUDED

#include "GL_GraphicLib.h"
#ifdef WIN32
#include <stdio.h>
#endif
#if defined(__TELIUM2__)
#include "sdk30.h"
#endif
#include <string.h>

#if __cplusplus
extern "C"
{
#endif

// Load graphic library and display menu with all samples
void GL_Samples(void);

// Sample menu
void GL_Samples_Menu(T_GL_HGRAPHIC_LIB  graphicLib);

// Sample of button
void GL_SampleButton(T_GL_HGRAPHIC_LIB  graphicLib);

// Sample of arrow button
void GL_SampleArrowButton(T_GL_HGRAPHIC_LIB  graphicLib);

// Sample of button with a skin icon on top
void GL_SampleButtonWithSkinedIcon(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of stretching buttons
void GL_SampleButtonStretch(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of check button
void GL_SampleCheckButton(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog text
void GL_SampleDialogText(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog text
void GL_SampleDialogText1(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog text
void GL_SampleDialogText2(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog slider
void GL_SampleDialogSlider(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog slider
void GL_SampleDialogSlider1(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog slider
void GL_SampleDialogSlider2(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog progress
void GL_SampleDialogProgress(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog progress
void GL_SampleDialogProgress1(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog progress
void GL_SampleDialogProgress2(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog picture
void GL_SampleDialogPicture(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog picture
void GL_SampleDialogPicture1(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog picture
void GL_SampleDialogPicture2(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog picture
void GL_SampleDialogPicture3(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog picture
void GL_SampleDialogPicture4(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog picture
void GL_SampleDialogPicture5(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog picture
void GL_SampleDialogPicture6(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog picture
void GL_SampleDialogPicture7(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog picture
void GL_SampleDialogPicture8(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog message
void GL_SampleDialogMessage(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog message
void GL_SampleDialogMessage1(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog message
void GL_SampleDialogMessage2(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog message
void GL_SampleDialogMessage3(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog message
void GL_SampleDialogMessage4(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog message
void GL_SampleDialogMessage5(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog message
void GL_SampleDialogMessage6(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog menu
void GL_SampleDialogMenu(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog media
void GL_SampleDialogMedia(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog signature
void GL_SampleDialogSignature(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog ip
void GL_SampleDialogIp(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog icon menu
void GL_SampleDialogIconMenu(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog icon button menu
void GL_SampleDialogIconButtonMenu(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog file
void GL_SampleDialogFile(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog date
void GL_SampleDialogDate(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog date
void GL_SampleDialogDate1(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog date
void GL_SampleDialogDate2(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog color
void GL_SampleDialogColor(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog choice
void GL_SampleDialogChoice(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog multi choice
void GL_SampleDialogMultiChoice(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog amount
void GL_SampleDialogAmount(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog password
void GL_SampleDialogPassword(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of print document
void GL_SampleDocument(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of print document
void GL_SampleDocumentFontSize(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of drawing with vectorized mode
void GL_SampleDrawingVectorized(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of drawing with not vectorized mode
void GL_SampleDrawingNotVectorized(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of edit
void GL_SampleEdit(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of horizontal scroll bar
void GL_SampleHScrollBar(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of horizontal slider
void GL_SampleHSlider(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of icon
void GL_SampleIcon(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of icon button
void GL_SampleIconButton(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of label
void GL_SampleLabel(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of layout
void GL_SampleLayout(T_GL_HGRAPHIC_LIB graphicLib);

// Sample list icons completely user-defined
void GL_SampleUserList(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of list
void GL_SampleList(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of list icon
void GL_SampleListIcon(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of media
void GL_SampleMedia(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of palette
void GL_SamplePalette(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of picture
void GL_SamplePicture(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of picture
void GL_SamplePictureStretch(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of generic plugin
void GL_SamplePlugin(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of progress bar
void GL_SampleProgressBar(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of radio button
void GL_SampleRadioButton(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of scroll view
void GL_SampleScrollView(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of scroll text
void GL_SampleScrollText(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of timer
void GL_SampleTimer(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of virtual keyboard
void GL_SampleVirtualKeyboard(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of virtual keyboard with user mask
void GL_SampleUserMaskVirtualKeyboard(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of customized virtual keyboard
void GL_SampleCustomVirtualKeyboard(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of vertical scroll bar
void GL_SampleVScrollBar(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of window
void GL_SampleWindow(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of edit mask
void GL_SampleEditMask(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of edit mode
void GL_SampleEditMode(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of edit multiline
void GL_SampleEditMultiline(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of font
void GL_SampleFont(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of font style
void GL_SampleFontStyle(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog virtual keyboard
void GL_SampleDialogVirtualKeyboard(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog virtual keyboard
void GL_SampleDialogVirtualKeyboard1(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog virtual keyboard
void GL_SampleDialogVirtualKeyboard2(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog virtual keyboard
void GL_SampleDialogVirtualKeyboard3(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog scheme
void GL_SampleDialogScheme(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of signature capture
void GL_SampleSignature(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog multi files selection
void GL_SampleDialogMultiFile(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog multi files selection
void GL_SampleDialogMultiFile1(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog multi files selection
void GL_SampleDialogMultiFile2(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog multi files selection
void GL_SampleDialogMultiFile3(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog multi files selection
void GL_SampleDialogMultiFile4(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of player
void GL_SamplePlayer(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of all widgets
void GL_SampleAllWidgets(T_GL_HGRAPHIC_LIB graphicLib);

// Example of printing the displayed window
void GL_SampleDocumentWindow(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of barcode QR
void GL_SampleBarcodeQr(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of barcode PDF 417
void GL_SampleBarcodePdf417(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of barcode EAN 8
void GL_SampleBarcodeEAN8(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of barcode EAN 13
void GL_SampleBarcodeEAN13(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of barcode CODE 25
void GL_SampleBarcodeCODE25(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of barcode CODE 39
void GL_SampleBarcodeCODE39(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of barcode CODE 128
void GL_SampleBarcodeCODE128(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of label utf8
void GL_SampleLabelUtf8(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of label big5
void GL_SampleLabelBig5(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of label escape sequences
void GL_SampleLabelEscapeSequence(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of send key 
void GL_SampleSendKey(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of send key and send click
void GL_SampleSendClick(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of list of dynamic items
void GL_SampleListDynamic(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of instanciation of a resource
void GL_SampleInstanciateResource(T_GL_HGRAPHIC_LIB graphicLib);

// Example of creating a user control for a simple arithmetic operation
void GL_SampleUserControl(T_GL_HGRAPHIC_LIB graphicLib);

// Initialization function of the user control, this function will register all the callback processing calculator 
void GL_SampleCalculatorInit(T_GL_HWIDGET userControl);

// Sample of screen orientation
void GL_SampleOrientation(T_GL_HGRAPHIC_LIB graphicLib);

#if __cplusplus
}
#endif

#endif // GL_Samples_h_INCLUDED
