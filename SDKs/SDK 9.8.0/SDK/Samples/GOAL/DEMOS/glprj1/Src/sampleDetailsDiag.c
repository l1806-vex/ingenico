#include "SDK30.H"
#include "GL_GraphicLib.h"
#include "SampDetailsDef.h"
#include "SampDetailsDiag.h"

//****Declare Extern Variable****/
extern T_GL_HGRAPHIC_LIB global_graphicLib;

//****Locale Function Prototype****/
bool USRprintDetailsDiag(void);


//****Declare Globale Variable****/
int	 gMaritalChoice = 0;
int	 gSexChoice = 0;
char gName[100];
char gCity[100];
char gZip[10];
T_GL_DATE gDate;

const char *gDetailsMenu[]=
{
	"NAME",
	"Marital Situation",
		"Birthday",
		"CITY",
		"ZIP code",
		"What about you",
		0 //<- DO NOT FORGET THIS TO STOP THE LIST
};
const char * gMaritalMenu [] =
{
    "Single",
    "Married",
    "PACS",
    0 //<- DO NOT FORGET THIS TO STOP THE LIST
};


void USRinputDetailsDiag(void)
{
	//**********Declare Local variables*********/
    const char * SexMenu [] =
    {
        "Male",
        "Female",
        0 //<- DO NOT FORGET THIS TO STOP THE LIST
    };
    int step=0;
    bool bStop=false;
    bool bPrint=false;

    ulong result=0;
    //************Initialize FIELD VALUE**********/
    //Names
    strcpy(gName,"JOHN DOE");
    //Birthday
    gDate.day    = 25;
    gDate.month  = 9;
    gDate.year   = 1976;
    //city
    strcpy(gCity,"GUILHERAND");
    //ZIP Code
    strcpy(gZip,"07300");


    // GET details using Dialog Box
    do
    {
		switch(step)
		{
		case 0://Get Name
			result = GL_Dialog_VirtualKeyboard (global_graphicLib, gDetailsMenu[step], "Your name?",NULL, gName, sizeof(gName), GL_TIME_INFINITE);
			break;
		case 1://Get Marital situation
			result = GL_Dialog_Choice(global_graphicLib,gDetailsMenu[step],gMaritalMenu,gMaritalChoice,GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
			if(result!=GL_KEY_CANCEL)
				gMaritalChoice = result;
			break;
		case 2:// Birthday
			result = GL_Dialog_Date (global_graphicLib, gDetailsMenu[step], "Your Birthday", &gDate, "y/m/d", GL_TIME_INFINITE);
			break;
		case 3:// City
			result = GL_Dialog_VirtualKeyboard (global_graphicLib, gDetailsMenu[step], "Your city","/c/c/c/c/c/c/c/c/c/c/c/c", gCity, sizeof(gCity), GL_TIME_INFINITE);
			break;
		case 4:// ZIP code
			result = GL_Dialog_Text (global_graphicLib, gDetailsMenu[step], "Your ZIPCode","/d/d/d/d/d", gZip, sizeof(gZip), GL_TIME_INFINITE);
			break;
		case 5:// male or female
			result = GL_Dialog_Choice(global_graphicLib,gDetailsMenu[step],SexMenu,gSexChoice,GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
			if(result!=GL_KEY_CANCEL)
				gSexChoice = result;
			break;
		case 6://Print
			bPrint = USRprintDetailsDiag();

			if (bPrint==false)
			{
				result =GL_Dialog_Message  ( global_graphicLib,"Exit","You want to quit",GL_ICON_NONE,GL_BUTTON_VALID,GL_TIME_INFINITE);
			}
			bStop=true;
			break;
		}
		if (result==GL_KEY_CANCEL)
		{
			if(step==0)
			{
				result =GL_Dialog_Message  ( global_graphicLib,"Exit","You want to quit",GL_ICON_NONE,GL_BUTTON_VALID_CANCEL,GL_TIME_INFINITE);
				if(result==GL_KEY_VALID)
					bStop=true;
			}
			else
			{
				// previous
				step--;
			}
		}
		else
			step++;
    }while(bStop==false);

}

bool USRprintDetailsDiag(void)
{
    T_GL_HWIDGET document;
    T_GL_HWIDGET layout;
    T_GL_HWIDGET label;
    T_GL_DIM line = 0;
    int i=0;
    char Text[100];

    // Creating a document intended for print
    document = GL_Document_Create(global_graphicLib);

    // Creating a layout in document is required to use the alignments to the right and left of the text
    layout = GL_Layout_Create(document);

    // Add all items
    label = GL_Label_Create(layout);
    GL_Widget_SetText         (label, "DETAILS");
    GL_Widget_SetItem         (label, 0, line);
    GL_Widget_SetMargins      (label, 10, 10, 0, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize     (label, 30, 30, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign    (label, GL_ALIGN_CENTER);
    GL_Widget_SetForeColor    (label, GL_COLOR_BLACK);

    // NAME
    line++;

    label = GL_Label_Create(layout);
	GL_Widget_SetText     (label, gDetailsMenu[i++]);
	GL_Widget_SetItem     (label, 0, line);
	GL_Widget_SetMargins  (label, 10, 0, 0, 0, GL_UNIT_PIXEL);
	GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
	GL_Widget_SetBackAlign(label, GL_ALIGN_LEFT);
	GL_Widget_SetForeColor    (label, GL_COLOR_BLACK);

	label = GL_Label_Create(layout);
	if(gSexChoice==0)
		strcpy(Text,"Mister ");
	else
		strcpy(Text,"Miss ");
	strcat(Text,gName);

	GL_Widget_SetText     (label, Text);
	GL_Widget_SetItem     (label, 0, line);
	GL_Widget_SetMargins  (label, 0, 0, 10, 0, GL_UNIT_PIXEL);
	GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
	GL_Widget_SetBackAlign(label, GL_ALIGN_RIGHT);
	GL_Widget_SetForeColor    (label, GL_COLOR_BLACK);

	// MARITAL SITUATION
	line++;
    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, gDetailsMenu[i++]);
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 10, 0, 0, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_LEFT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, gMaritalMenu[gMaritalChoice]);
    GL_Widget_SetItem     (label, 0, line );
    GL_Widget_SetMargins  (label, 0, 0, 10, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_RIGHT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

	// BIRTHDAY
	line++;
    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, gDetailsMenu[i++]);
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 10, 0, 0, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_LEFT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

    label = GL_Label_Create(layout);
    sprintf(Text,"%d /%d/%d",gDate.year,gDate.month,gDate.day);
    GL_Widget_SetText     (label, Text);
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 0, 0, 10, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_RIGHT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

	// CITY
	line++;
    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, gDetailsMenu[i++]);
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 10, 0, 0, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_LEFT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, gCity);
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 0, 0, 10, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_RIGHT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

	// ZIP
	line++;
    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, gDetailsMenu[i++]);
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 10, 0, 0, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_LEFT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, gZip);
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 0, 0, 10, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_RIGHT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

    line++;
    label = GL_Label_Create(layout);
    GL_Widget_SetText         (label, "\n\n\n\n\n");
    GL_Widget_SetItem         (label, 0, line++);

    GL_Document_Print(document, 0);

    GL_Widget_Destroy(document) ;

    return(true);

}




