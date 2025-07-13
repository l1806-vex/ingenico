#include "GL_GraphicLib.h"
#include "GL_Samples.h"


// Print the content of files selected
void GL_SamplePrintFileList(T_GL_HGRAPHIC_LIB gl, T_GL_HSTRINGLIST files)
{
	T_GL_HWIDGET document;
	T_GL_HWIDGET layout;
	T_GL_HWIDGET print;
	T_GL_DIM line = 0;
	unsigned long i;

	// Creating a document intended for print
	document = GL_Document_Create(gl);

	// Creating a layout in document is required to use the alignments to the right and left of the text
	layout = GL_Layout_Create(document);

	for (i = 0; i < GL_StringList_GetCount(files); i++)
	{
		// Adds the address of the company
		print = GL_Print_Create(layout);
		GL_Widget_SetText         (print, GL_StringList_GetString(files, i));
		GL_Widget_SetItem         (print, 0, line++);
		GL_Widget_SetTextAlign    (print, GL_ALIGN_LEFT);
		GL_Widget_SetBackAlign    (print, GL_ALIGN_LEFT);
		GL_Widget_SetShrink       (print, GL_DIRECTION_WIDTH);
	}

	// Adds empty lines to exit the ticket
	print = GL_Print_Create(layout);
	GL_Widget_SetText         (print, "\n\n\n\n\n\n");
	GL_Widget_SetItem         (print, 0, line++);

	// Print the receipt
	GL_Document_Print(document, 0);

	// Destroy the document
	GL_Widget_Destroy(document);
}


// Sample of dialog multi files selection
void GL_SampleDialogMultiFile(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HSTRINGLIST files;

	// IMPORTANT : Create an empty list of files 
	// NOTA : If you are not sure of the charset encoding of the drive used an ISO encoding (Most USB drives are not UTF8 encoded).
	files = GL_StringList_Create(GL_ENCODING_ISO_8859_1);

	// Example of choose of file in HOST
	if (GL_Dialog_MultiFile(graphicLib, "Select files HOST", "dir://flash/HOST", "*.*", files, 0, GL_TIME_INFINITE) == GL_KEY_VALID)
	{
		// Here print list of files selected
		GL_SamplePrintFileList(graphicLib, files);
	}

	// Clear the content of list
	GL_StringList_Clear(files);

	// Example of choose of file in usb key
	if (GL_Dialog_MultiFile(graphicLib, "Select files USB key", "dir://umsd0a", "*.*", files, 0, GL_TIME_INFINITE) == GL_KEY_VALID)
	{
		// Here print list of files selected
		GL_SamplePrintFileList(graphicLib, files);
	}

	// Clear the content of list
	GL_StringList_Clear(files);

	// Example of choose of file in MMC
	if (GL_Dialog_MultiFile(graphicLib, "Select files MMC", "dir://mmcd0a", "*.*", files, 0, GL_TIME_INFINITE) == GL_KEY_VALID)
	{
		// Here print list of files selected
		GL_SamplePrintFileList(graphicLib, files);
	}

	// Clear the content of list
	GL_StringList_Clear(files);

	// Example of choose of file in TAR
	if (GL_Dialog_MultiFile(graphicLib, "Select files TAR", "file://flash/HOST/TU.TAR", "*.*", files, 0, GL_TIME_INFINITE) == GL_KEY_VALID)
	{
		// Here print list of files selected
		GL_SamplePrintFileList(graphicLib, files);
	}

	// IMPORTANT : Destroy the list of files
	GL_StringList_Destroy(files);
}
