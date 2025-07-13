#include "SDK30.H"
#include "GL_GraphicLib.h"
#include "SampDetailsDef.h"
#include "SampDetailsWdg.h"
#include "widgetMappings.h"

/*+************* DATA DECLARATIONS ***************************************---*/
extern T_GL_HGRAPHIC_LIB global_graphicLib;

/*+************* FUNCTION PROTOTYPES ***************************************+*/
bool USRDetails_wdgOKBUTTON_pressed(T_GL_HMESSAGE message);
bool USRDetails_wdgCANCELBUTTON_pressed(T_GL_HMESSAGE message);
bool USRprintDetailsWdg(T_GL_HMESSAGE message);


void USRinputDetailsWdg(void)
{
	// Declaration of my widget
	T_GL_HWIDGET widgetLabel_Name;
	T_GL_HWIDGET widgetEdit_Name;
	T_GL_HWIDGET widgetLabel_Age;
	T_GL_HWIDGET widgetEdit_Age;
	T_GL_HWIDGET widgetRadio_Male;
	T_GL_HWIDGET widgetRadio_Female;
	T_GL_HWIDGET widgetCheck_Marital;
	T_GL_HWIDGET widgetLabel_ZIP;
	T_GL_HWIDGET widgetEdit_ZIP;
    T_GL_HWIDGET widgetLabel_City;
    T_GL_HWIDGET widgetEdit_City;
    T_GL_HWIDGET widgetButton_OK;
    T_GL_HWIDGET widgetButton_CANCEL;

    T_GL_HWIDGET      window;
    T_GL_HWIDGET      layout;
    T_GL_HWIDGET      list;


    // Creating a blank window
    window = GL_Window_Create(global_graphicLib);

    // Reduces maximize the size of window to full screen
    GL_Widget_SetSize (window, 100, 100, GL_UNIT_PERCENT);


    // Creating a layout with 3 rows and one column
    layout = GL_Layout_Create(window);

    // Creating a list
    list = GL_List_Create(window);

        // Adds a label and an edit to enter the name
		widgetLabel_Name = GL_Label_Create(list); GL_Widget_SetText (widgetLabel_Name,"Name");
		widgetEdit_Name = GL_Edit_Create(list);  GL_Widget_SetMask(widgetEdit_Name,"/a/a/a/a/a/a/a/a/a/a/a/a/a/a/a");
		GL_Widget_SetId(widgetLabel_Name,ID_LABEL_NAME);
		GL_Widget_SetId(widgetEdit_Name,ID_EDIT_NAME);

        // Adds a label and an edit to enter the age
        widgetLabel_Age = GL_Label_Create(list); GL_Widget_SetText (widgetLabel_Age,"Birthday");
        widgetEdit_Age = GL_Edit_Create(list);  GL_Widget_SetMask(widgetEdit_Age,"/d/d./d/d./d/d/d/d");
        GL_Widget_SetId(widgetLabel_Age,ID_LABEL_AGE);
        GL_Widget_SetId(widgetEdit_Age,ID_EDIT_AGE);

        // Adds two radio buttons to select the sex
        widgetRadio_Male	= GL_RadioButton_Create(list);  GL_Widget_SetText(widgetRadio_Male,"male");
        widgetRadio_Female	= GL_RadioButton_Create(list);  GL_Widget_SetText(widgetRadio_Female,"female");
        GL_Widget_SetId(widgetRadio_Male,ID_RADIO_MALE);
        GL_Widget_SetId(widgetRadio_Female,ID_RADIO_FEMALE);


        // Adds check button to select the marital status
        widgetCheck_Marital = GL_CheckButton_Create(list);  GL_Widget_SetText(widgetCheck_Marital,"married");
		GL_Widget_SetId(widgetCheck_Marital,ID_CHECK_MARITAL);

        // Adds a label and an edit to enter ZIP Code
        widgetLabel_ZIP = GL_Label_Create(list); GL_Widget_SetText (widgetLabel_ZIP,"ZIP Code");
		widgetEdit_ZIP = GL_Edit_Create(list);  GL_Widget_SetMask(widgetEdit_ZIP,"/d/d/d/d/d");
		GL_Widget_SetId(widgetLabel_ZIP,ID_LABEL_ZIP);
		GL_Widget_SetId(widgetEdit_ZIP,ID_EDIT_ZIP);

        // Adds a label and an edit to enter City
        widgetLabel_City = GL_Label_Create(list); GL_Widget_SetText (widgetLabel_City,"City");
        widgetEdit_City = GL_Edit_Create(list);  GL_Widget_SetMask(widgetEdit_City,"/a/a/a/a/a/a/a/a/a/a/a/a");
		GL_Widget_SetId(widgetLabel_City,ID_LABEL_CITY);
		GL_Widget_SetId(widgetEdit_City,ID_EDIT_CITY);

        // Creating a button with text "OK"
        widgetButton_OK = GL_Button_Create(list);  GL_Widget_SetText(widgetButton_OK,"OK");
		GL_Widget_SetId(widgetButton_OK,ID_BUTTON_OK);
        // Creating a button with text "OK"
        widgetButton_CANCEL = GL_Button_Create(list);  GL_Widget_SetText(widgetButton_CANCEL,"CANCEL");
		GL_Widget_SetId(widgetButton_CANCEL,ID_BUTTON_CANCEL);



    // Registering a callback. This callback will be called every click on the button
    GL_Widget_RegisterCallback(GL_Widget_SearchId(window, ID_BUTTON_OK),GL_EVENT_STYLUS_CLICK, USRDetails_wdgOKBUTTON_pressed);

      // Here we loop indefinitely. To break this loop you must set the result of window to 0 (GL_Message_SetResult or GL_Window_SetResult),
    // which was made earlier in the call back OnClick
    GL_Window_MainLoop(window);

    // Destruction of the window. Destruction frees all allocated memory,
    // all the widgets attached to the window and suppress the window on the screen.
    // This call is crucial, if it forgotten you get a memory leak.
    GL_Widget_Destroy(window);
}

bool USRDetails_wdgCANCELBUTTON_pressed(T_GL_HMESSAGE message)
{
	GL_Message_SetResult(message, 0);
	return false;
}
bool USRDetails_wdgOKBUTTON_pressed(T_GL_HMESSAGE message)
{
	bool bPrint;

	bPrint=USRprintDetailsWdg(message);
	GL_Message_SetResult(message, 0);
	return true;
}

bool USRprintDetailsWdg(T_GL_HMESSAGE message)
{
	 T_GL_HWIDGET document;
	 T_GL_HWIDGET layout;
	 T_GL_HWIDGET lcl_window;
	 T_GL_HWIDGET label;

	 T_GL_HWIDGET widget;


	 bool bChecked = false;
	 char Text[256];
	 int line=0;

	// Creating a document intended for print
	document = GL_Document_Create(global_graphicLib);

	// Creating a layout in document is required to use the alignments to the right and left of the text
	layout = GL_Layout_Create(document);

	lcl_window =  GL_Message_GetWindow(message);

	line=0;

    label = GL_Label_Create(layout);
    GL_Widget_SetText         (label, "DETAILS");
    GL_Widget_SetItem         (label, 0, line);
    GL_Widget_SetMargins      (label, 10, 10, 0, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize     (label, 30, 30, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign    (label, GL_ALIGN_CENTER);
    GL_Widget_SetForeColor    (label, GL_COLOR_BLACK);


	line++;
	label = GL_Label_Create(layout);
	GL_Widget_SetText     (label, GL_Widget_GetTextById(lcl_window,ID_LABEL_NAME));
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 10, 0, 0, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_LEFT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

    label = GL_Label_Create(layout);
	widget = GL_Widget_SearchId(lcl_window,ID_RADIO_MALE);
	bChecked= GL_Widget_GetCheck(widget);
	if(bChecked==TRUE)
		strcpy(Text,"Mister ");
	else
		strcpy(Text,"Miss ");
	strcat(Text,GL_Widget_GetTextById(lcl_window,ID_EDIT_NAME));
    GL_Widget_SetText     (label,Text );
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 0, 0, 10, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_RIGHT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

	line++;
	widget = GL_Widget_SearchId(lcl_window,ID_CHECK_MARITAL);
	bChecked= GL_Widget_GetCheck  ( widget   );

    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, "Situation");
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 10, 0, 0, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_LEFT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

    label = GL_Label_Create(layout);
    if(bChecked==true)
    	GL_Widget_SetText     (label, "SINGLE");
    else
    	GL_Widget_SetText     (label, "MARRIED");
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 0, 0, 10, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_RIGHT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

	line++;
    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, GL_Widget_GetTextById(lcl_window,ID_LABEL_AGE));
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 10, 0, 0, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_LEFT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, GL_Widget_GetTextById(lcl_window,ID_EDIT_AGE));
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 0, 0, 10, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_RIGHT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

	line++;
    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, GL_Widget_GetTextById(lcl_window,ID_LABEL_CITY));
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 10, 0, 0, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_LEFT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, GL_Widget_GetTextById(lcl_window,ID_EDIT_CITY));
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 0, 0, 10, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_RIGHT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

	line++;
    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, GL_Widget_GetTextById(lcl_window,ID_LABEL_ZIP));
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 10, 0, 0, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_LEFT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

    label = GL_Label_Create(layout);
    GL_Widget_SetText     (label, GL_Widget_GetTextById(lcl_window,ID_EDIT_ZIP));
    GL_Widget_SetItem     (label, 0, line);
    GL_Widget_SetMargins  (label, 0, 0, 10, 0, GL_UNIT_PIXEL);
    GL_Widget_SetFontSize (label, 20, 20, GL_UNIT_PIXEL);
    GL_Widget_SetBackAlign(label, GL_ALIGN_RIGHT);
    GL_Widget_SetForeColor(label, GL_COLOR_BLACK);

    GL_Document_Print(document, 0);

	return true;
}
