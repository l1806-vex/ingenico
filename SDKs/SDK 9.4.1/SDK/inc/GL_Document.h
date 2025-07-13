// $Id: GL_Document.h,v 1.1.2.11 2012/03/05 11:10:03 rbertholet Exp $
// This class allows the creation of a document to be printed
#ifndef GL_Document_h_INCLUDED
#define GL_Document_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_Document
@{
@addtogroup GL_DocumentDoc Printing document
@{

This class allows the creation of a document to be printed.

Below is a document of specific functions to this class :
	- @ref GL_Document_Create : Creating a document
	- @ref GL_Document_Print : Prints a document on the printer connected to the graphical client

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_AppearanceProperties

Methods inherited from class widget :
	- @ref GL_Widget_GetSize
	- @ref GL_Widget_GetBackAlign
	- @ref GL_Widget_SetBackAlign
	- @ref GL_Widget_Destroy
	- @ref GL_Widget_SearchId
	- @ref GL_Widget_GetBackColor
	- @ref GL_Widget_SetBackColor
	- @ref GL_Widget_SetExpand
	- @ref GL_Widget_GetExpand
	- @ref GL_Widget_SetUserData
	- @ref GL_Widget_GetUserData

For messages sent by this widget see @ref GL_Widget_CommonMessage

<b>IMPORTANT</b> : For printing you must replace the widgets label by the widgets print.
If you use the label widget for printing, you must force its font size and color of text in black.

<h2>Sample</h2>

	Below is an example of printing receipt

	@image html documentTest.png
	@include GL_SampleDocument.c
@}*/


/*<ALL>
	Extension("DOCUMENT",          "WIDGET",     "The document allows the print of a document",
		Bool("showonscreen",                     "Displays the document on the screen"),
		),
	</ALL>*/

/** Creating a document intended for print
@param graphicLib handle on the graphical client
@return returns the window handle created or null if creation failed */
T_GL_HWIDGET GL_Document_Create(T_GL_HGRAPHIC_LIB graphicLib) GL_EXCEPTION;

/** Prints a document on the printer connected to the graphical client
@param document document to print handle
@param timeout waiting (in ms) for printer availability. if the printer is not busy, printing starts instantly
@return printing status */
T_GL_ERROR_CODE GL_Document_Print(T_GL_HWIDGET document, unsigned int timeout) GL_EXCEPTION;

/** Sets the display of document on the screen, this behavior is only available before the first printing
@param document document to print handle */
void GL_Document_SetShowOnScreen(T_GL_HWIDGET document) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Document_h_INCLUDED
