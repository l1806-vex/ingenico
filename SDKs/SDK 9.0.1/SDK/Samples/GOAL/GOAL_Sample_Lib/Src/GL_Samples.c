#include "GL_GraphicLib.h"
#include "GL_Samples.h"
#include "GL_TutorialSteps.h"


/** Samples menu */
static wchar GL_Samples_MenuWidgetText(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Label",
		"Font",
		"Button",
		"Icon",
		"Icon button",
		"CheckButton",
		"Radio button",
		"Edit",
		"Edit mask",
		"Edit mode",
		"Edit multiline",
	0};
	wchar choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SampleLabel                 (graphicLib); break;
		case 1 : GL_SampleFont                  (graphicLib); break;
		case 2 : GL_SampleButton                (graphicLib); break;
		case 3 : GL_SampleIcon                  (graphicLib); break;
		case 4 : GL_SampleIconButton            (graphicLib); break;
		case 5 : GL_SampleCheckButton           (graphicLib); break;
		case 6 : GL_SampleRadioButton           (graphicLib); break;
		case 7 : GL_SampleEdit                  (graphicLib); break;
		case 8 : GL_SampleEditMask              (graphicLib); break;
		case 9 : GL_SampleEditMode              (graphicLib); break;
		case 10: GL_SampleEditMultiline         (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL && choice != GL_KEY_CORRECTION);
	if (choice == GL_KEY_CORRECTION) choice = GL_KEY_NONE;
	return choice;
}


/** Samples menu */
static wchar GL_Samples_MenuWidgetList(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Layout",
		"List",
		"ListIcon",
		"Scroll view",
		"Window",
	0};
	wchar choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SampleLayout                (graphicLib); break;
		case 1 : GL_SampleList                  (graphicLib); break;
		case 2 : GL_SampleListIcon              (graphicLib); break;
		case 3 : GL_SampleScrollView            (graphicLib); break;
		case 4 : GL_SampleWindow                (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL && choice != GL_KEY_CORRECTION);
	if (choice == GL_KEY_CORRECTION) choice = GL_KEY_NONE;
	return choice;
}


/** Samples menu */
static wchar GL_Samples_MenuWidgetBar(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Horizontal scroll bar",
		"Vertical scroll bar",
		"Horizontal slider",
		"Progress bar",
	0};
	wchar choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SampleHScrollBar            (graphicLib); break;
		case 1 : GL_SampleVScrollBar            (graphicLib); break;
		case 2 : GL_SampleHSlider               (graphicLib); break;
		case 3 : GL_SampleProgressBar           (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL && choice != GL_KEY_CORRECTION);
	if (choice == GL_KEY_CORRECTION) choice = GL_KEY_NONE;
	return choice;
}


/** Samples menu */
static wchar GL_Samples_MenuWidgetGraphical(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Picture",
		"Drawing",
		"Palette",
		"Media",
		"Signature",
		"Plugin",
		"Player",
	0};
	wchar choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SamplePicture               (graphicLib); break;
		case 1 : GL_SampleDrawing               (graphicLib); break;
		case 2 : GL_SamplePalette               (graphicLib); break;
		case 3 : GL_SampleMedia                 (graphicLib); break;
		case 4 : GL_SampleSignature             (graphicLib); break;
		case 5 : GL_SamplePlugin                (graphicLib); break;
		case 6 : GL_SamplePlayer                (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL && choice != GL_KEY_CORRECTION);
	if (choice == GL_KEY_CORRECTION) choice = GL_KEY_NONE;
	return choice;
}


/** Samples menu */
static wchar GL_Samples_MenuWidgetOther(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Print document",
		"Print font",
		"Print window",
		"Timer",
		"Virtual keyboard",
		"Custom Virtual keyboard",
	0};
	wchar choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SampleDocument              (graphicLib); break;
		case 1 : GL_SampleDocumentFontSize      (graphicLib); break;
		case 2 : GL_SampleDocumentWindow        (graphicLib); break;
		case 3 : GL_SampleTimer                 (graphicLib); break;
		case 4 : GL_SampleVirtualKeyboard       (graphicLib); break;
		case 5 : GL_SampleCustomVirtualKeyboard (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL && choice != GL_KEY_CORRECTION);
	if (choice == GL_KEY_CORRECTION) choice = GL_KEY_NONE;
	return choice;
}


/** Samples menu */
static wchar GL_Samples_MenuDialogList(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Dialog menu",
		"Dialog icon menu",
		"Dialog icon button menu",
		"Dialog file",
		"Dialog choice",
		"Dialog multi choice",
		"Dialog multi file",
	0};
	wchar choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SampleDialogMenu            (graphicLib); break;
		case 1 : GL_SampleDialogIconMenu        (graphicLib); break;
		case 2 : GL_SampleDialogIconButtonMenu  (graphicLib); break;
		case 3 : GL_SampleDialogFile            (graphicLib); break;
		case 4 : GL_SampleDialogChoice          (graphicLib); break;
		case 5 : GL_SampleDialogMultiChoice     (graphicLib); break;
		case 6 : GL_SampleDialogMultiFile       (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL && choice != GL_KEY_CORRECTION);
	if (choice == GL_KEY_CORRECTION) choice = GL_KEY_NONE;
	return choice;
}


/** Samples menu */
static wchar GL_Samples_MenuDialogGraphical(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Dialog slider",
		"Dialog progress",
		"Dialog picture",
		"Dialog media",
		"Dialog color",
		"Dialog signature",
	0};
	wchar choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0  : GL_SampleDialogSlider          (graphicLib); break;
		case 1  : GL_SampleDialogProgress        (graphicLib); break;
		case 2  : GL_SampleDialogPicture         (graphicLib); break;
		case 3  : GL_SampleDialogMedia           (graphicLib); break;
		case 4  : GL_SampleDialogColor           (graphicLib); break;
		case 5  : GL_SampleDialogSignature       (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL && choice != GL_KEY_CORRECTION);
	if (choice == GL_KEY_CORRECTION) choice = GL_KEY_NONE;
	return choice;
}


/** Samples menu */
static wchar GL_Samples_MenuDialogText(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Dialog text",
		"Dialog message",
		"Dialog ip",
		"Dialog date",
		"Dialog amount",
		"Dialog virtual keyboard",
		"Dialog password",
		"Dialog scheme",
	0};
	wchar choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SampleDialogText            (graphicLib); break;
		case 1 : GL_SampleDialogMessage         (graphicLib); break;
		case 2 : GL_SampleDialogIp              (graphicLib); break;
		case 3 : GL_SampleDialogDate            (graphicLib); break;
		case 4 : GL_SampleDialogAmount          (graphicLib); break;
		case 5 : GL_SampleDialogVirtualKeyboard (graphicLib); break;
		case 6 : GL_SampleDialogPassword        (graphicLib); break;
		case 7 : GL_SampleDialogScheme          (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL && choice != GL_KEY_CORRECTION);
	if (choice == GL_KEY_CORRECTION) choice = GL_KEY_NONE;
	return choice;
}


/** Samples menu */
wchar  GL_Samples_Menu(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Dialog   TEXT",
		"Dialog   GRAPHIC",
		"Dialog   LIST",
		"Widget   TEXT",
		"Widget   GRAPHIC",
		"Widget   LIST",
		"Widget   BAR",
		"Widget   OTHER",
		"Tutorial",
	0};

	wchar choice  = 0;
	wchar result = 0;
	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_DEFAULT, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0  : result = GL_Samples_MenuDialogText       (graphicLib); break;
		case 1  : result = GL_Samples_MenuDialogGraphical  (graphicLib); break;
		case 2  : result = GL_Samples_MenuDialogList       (graphicLib); break;
		case 3  : result = GL_Samples_MenuWidgetText       (graphicLib); break;
		case 4  : result = GL_Samples_MenuWidgetGraphical  (graphicLib); break;
		case 5  : result = GL_Samples_MenuWidgetList       (graphicLib); break;
		case 6  : result = GL_Samples_MenuWidgetBar        (graphicLib); break;
		case 7  : result = GL_Samples_MenuWidgetOther      (graphicLib); break;
		case 8  : result = GL_TutorialSteps_Menu           (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL && choice != GL_KEY_CORRECTION && result != GL_KEY_CANCEL && result != GL_KEY_CORRECTION);
	if (choice == GL_KEY_CORRECTION) choice = GL_KEY_NONE;
	return choice;
}


// Load graphic library and display menu with all samples
wchar GL_Samples(void)
{
	T_GL_HGRAPHIC_LIB graphicLib;
	wchar choice;
	
	// Create an instance of the graphics library. 
	// This creation takes some time, it is imperative to do once for the entire application life
	graphicLib = GL_GraphicLib_Create();
	
	// Display menu with all samples
	choice = GL_Samples_Menu(graphicLib);

	// Release resources from the graphics library.
	// This call is crucial to the end of life of the application, this call frees resources and release memory allocated
	GL_GraphicLib_Destroy(graphicLib);
	return choice;
}
