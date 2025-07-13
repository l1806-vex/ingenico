//-------------------------------------------------------------------
//
// Copyright (c) 2001 Sagem Monetel SA, rue claude Chappe,
// 07503 Guilherand-Granges, France, All Rights Reserved.
//
// Sagem Monetel SA has intellectual property rights relating
// to the technology embodied in this software.  In particular, 
// and without limitation, these intellectual property rights 
// may include one or more patents.
//
// This software is distributed under licenses restricting 
// its use, copying, distribution, and decompilation.  
// No part of this software may be reproduced in any form 
// by any means without prior written authorization of 
// Sagem Monetel.
//
// Description: User Interface function set. Miscellaneous.
//      
// Author:      V.GOMES
// Version:     1.0
// Date:        2005/07/22 
//
//-------------------------------------------------------------------

// Includes.
//-------------------------------------------------------------------

#include <SDK30.H>
#include <GL_GraphicLib.h>

#include "string.h"

#include "Utilities.h"

static T_GL_HWIDGET document;
static T_GL_HWIDGET layout;
static T_GL_HWIDGET print;
static T_GL_DIM line;

static int printStart(T_GL_HGRAPHIC_LIB hGoal)
{
    //check if document is already created
    if (document != NULL)
    {
        return 1;
    }

    line = 0;
    document = GL_Document_Create(hGoal);
    if (document == NULL)
    {
        return -1;
    }
    
    // Creating a layout in document is required to use the alignments to the right and left of the text
    layout = GL_Layout_Create(document);
    if (layout == NULL)
    {
        return -1;
    }

    return 1;
}

static void printStop(void)
{
    if (document != NULL)
    {
        // Destroy the document
        GL_Widget_Destroy(document);
        document = NULL;
    }
}

int printText(const char *str)
{
    int ret;
    T_GL_HGRAPHIC_LIB hGoal = NULL;

    trcS("printText\n");
    hGoal = guiStart();
    ret = printStart(hGoal);     // Creating a document intended for print
    if (ret != 1)
    {
        printStop();    
        return -1;
    }

    print = GL_Print_Create(layout);
    if (print == NULL)
    {
        return -1;
    }

    trcS("str = ");
    trcS(str);
    trcS("\n");
    GL_Widget_SetText(print, str);
    GL_Widget_SetItem(print, 0, line);
    GL_Widget_SetFontScale(print, GL_SCALE_MEDIUM);
    GL_Widget_SetBackAlign (print, GL_ALIGN_LEFT);
    line++;

    return 1;
}

void printDocument(void)
{

    trcS("printDocument\n");
    if (document != NULL)
    {
        GL_Document_Print(document, 0);
        printStop();	
    }
}

