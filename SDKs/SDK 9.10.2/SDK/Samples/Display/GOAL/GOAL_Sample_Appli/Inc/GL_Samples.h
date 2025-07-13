// $Id: GL_Samples.h,v 1.1.2.4 2013/01/18 16:06:05 rbertholet Exp $
#ifndef GL_Samples_h_INCLUDED
#define GL_Samples_h_INCLUDED

#include "GL_GraphicLib.h"
#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS
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
T_GL_WCHAR GL_Samples(void);

// Sample menu
T_GL_WCHAR GL_Samples_Menu(T_GL_HGRAPHIC_LIB  graphicLib);

// Sample of button
void GL_SampleButton(T_GL_HGRAPHIC_LIB  graphicLib);

// Sample of check button
void GL_SampleCheckButton(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog text
void GL_SampleDialogText(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog slider
void GL_SampleDialogSlider(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog progress
void GL_SampleDialogProgress(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog picture
void GL_SampleDialogPicture(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog message
void GL_SampleDialogMessage(T_GL_HGRAPHIC_LIB graphicLib);

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

// Sample of drawing
void GL_SampleDrawing(T_GL_HGRAPHIC_LIB graphicLib);

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

// Sample of generic plugin
void GL_SamplePlugin(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of progress bar
void GL_SampleProgressBar(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of radio button
void GL_SampleRadioButton(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of scroll view
void GL_SampleScrollView(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of timer
void GL_SampleTimer(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of virtual keyboard
void GL_SampleVirtualKeyboard(T_GL_HGRAPHIC_LIB graphicLib);

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

// Sample of dialog virtual keyboard
void GL_SampleDialogVirtualKeyboard(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog scheme
void GL_SampleDialogScheme(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of signature capture
void GL_SampleSignature(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of dialog multi files selection
void GL_SampleDialogMultiFile(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of player
void GL_SamplePlayer(T_GL_HGRAPHIC_LIB graphicLib);

// Sample of all widgets
void GL_SampleAllWidgets(T_GL_HGRAPHIC_LIB graphicLib);

// Example of printing the displayed window
void GL_SampleDocumentWindow(T_GL_HGRAPHIC_LIB graphicLib);

#if __cplusplus
}
#endif

#endif // GL_Samples_h_INCLUDED
