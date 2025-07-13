#include "GL_GraphicLib.h"
#include "GL_Samples.h"
#include "GL_TutorialSteps.h"


/** Samples menu */
static void GL_Samples_MenuWidgetLabel(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Label",
		"Font scale",
		"Font style",
		"Label UTF8",
		"Escape sequence",
		"Big5",
	0};
	T_GL_WCHAR choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_CANCEL, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SampleLabel              (graphicLib); break;
		case 1 : GL_SampleFont               (graphicLib); break;
		case 2 : GL_SampleFontStyle          (graphicLib); break;
		case 3 : GL_SampleLabelUtf8          (graphicLib); break;
		case 4 : GL_SampleLabelEscapeSequence(graphicLib); break;
		case 5 : GL_SampleLabelBig5          (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL);
}


/** Samples menu */
static void GL_Samples_MenuWidgetEdit(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Edit",
		"Edit mask",
		"Edit mode",
		"Edit multiline",
	0};
	T_GL_WCHAR choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_CANCEL, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SampleEdit          (graphicLib); break;
		case 1 : GL_SampleEditMask      (graphicLib); break;
		case 2 : GL_SampleEditMode      (graphicLib); break;
		case 3 : GL_SampleEditMultiline (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL);
}


/** Samples menu */
static void GL_Samples_MenuWidgetButton(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Button",
		"Icon",
		"Icon button",
		"CheckButton",
		"Radio button",
		"Button stretch",
		"Button skinned",
		"Arrow button",
	0};
	T_GL_WCHAR choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_CANCEL, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0: GL_SampleButton        (graphicLib); break;
		case 1: GL_SampleIcon          (graphicLib); break;
		case 2: GL_SampleIconButton    (graphicLib); break;
		case 3: GL_SampleCheckButton   (graphicLib); break;
		case 4: GL_SampleRadioButton   (graphicLib); break;
		case 5: GL_SampleButtonStretch (graphicLib); break;
		case 6: GL_SampleButtonWithSkinedIcon(graphicLib); break;
		case 7: GL_SampleArrowButton    (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL);
}


/** Samples menu */
static void GL_Samples_MenuWidgetList(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Layout",
		"List",
		"ListIcon",
		"Scroll view",
		"Scroll text",
		"Window",
		"Dynamic list",
		"User list",
	0};
	T_GL_WCHAR choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_CANCEL, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SampleLayout     (graphicLib); break;
		case 1 : GL_SampleList       (graphicLib); break;
		case 2 : GL_SampleListIcon   (graphicLib); break;
		case 3 : GL_SampleScrollView (graphicLib); break;
		case 4 : GL_SampleScrollText (graphicLib); break;
		case 5 : GL_SampleWindow     (graphicLib); break;
		case 6 : GL_SampleListDynamic(graphicLib); break;
		case 7 : GL_SampleUserList   (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL);
}


/** Samples menu */
static void GL_Samples_MenuWidgetBar(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Horizontal scroll bar",
		"Vertical scroll bar",
		"Horizontal slider",
		"Progress bar",
	0};
	T_GL_WCHAR choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_CANCEL, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SampleHScrollBar  (graphicLib); break;
		case 1 : GL_SampleVScrollBar  (graphicLib); break;
		case 2 : GL_SampleHSlider     (graphicLib); break;
		case 3 : GL_SampleProgressBar (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL);
}


/** Samples menu */
static void GL_Samples_MenuWidgetGraphical(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Picture",
		"Drawing vectorized",
		"Drawing not vectorized",
		"Palette",
		"Media",
		"Signature",
		"Plugin",
		"Player",
		"Picture stretch",
	0};
	T_GL_WCHAR choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_CANCEL, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SamplePicture             (graphicLib); break;
		case 1 : GL_SampleDrawingVectorized   (graphicLib); break;
		case 2 : GL_SampleDrawingNotVectorized(graphicLib); break;
		case 3 : GL_SamplePalette             (graphicLib); break;
		case 4 : GL_SampleMedia               (graphicLib); break;
		case 5 : GL_SampleSignature           (graphicLib); break;
		case 6 : GL_SamplePlugin              (graphicLib); break;
		case 7 : GL_SamplePlayer              (graphicLib); break;
		case 8 : GL_SamplePictureStretch      (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL);
}


/** Samples menu */
static void GL_Samples_MenuWidgetBarcode(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Barcode Qr",
		"Barcode Pdf417",
		"Barcode EAN 8",
		"Barcode EAN 13",
		"Barcode CODE 25",
		"Barcode CODE 39",
		"Barcode CODE 128",
	0};
	T_GL_WCHAR choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_CANCEL, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SampleBarcodeQr          (graphicLib); break;
		case 1 : GL_SampleBarcodePdf417      (graphicLib); break;
		case 2 : GL_SampleBarcodeEAN8        (graphicLib); break;
		case 3 : GL_SampleBarcodeEAN13       (graphicLib); break;
		case 4 : GL_SampleBarcodeCODE25      (graphicLib); break;
		case 5 : GL_SampleBarcodeCODE39      (graphicLib); break;
		case 6 : GL_SampleBarcodeCODE128     (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL);
}


/** Samples menu */
static void GL_Samples_MenuWidgetOther(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Print document",
		"Print font",
		"Print window",
		"Timer",
		"Virtual keyboard",
		"Custom Virtual keyboard",
		"User mask virtual keyboard",
		"Send key",
		"Send click",
		"Instantiate resource",
		"User control",
		"Screen orientation",
	0};
	T_GL_WCHAR choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_CANCEL, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0 : GL_SampleDocument               (graphicLib); break;
		case 1 : GL_SampleDocumentFontSize       (graphicLib); break;
		case 2 : GL_SampleDocumentWindow         (graphicLib); break;
		case 3 : GL_SampleTimer                  (graphicLib); break;
		case 4 : GL_SampleVirtualKeyboard        (graphicLib); break;
		case 5 : GL_SampleCustomVirtualKeyboard  (graphicLib); break;
		case 6 : GL_SampleUserMaskVirtualKeyboard(graphicLib); break;
		case 7 : GL_SampleSendKey                (graphicLib); break;
		case 8 : GL_SampleSendClick              (graphicLib); break;
		case 9 : GL_SampleInstanciateResource    (graphicLib); break;
		case 10: GL_SampleUserControl            (graphicLib); break;
		case 11: GL_SampleOrientation            (graphicLib); break;

		}
	}
	while(choice != GL_KEY_CANCEL);
}


/** Samples menu */
static void GL_Samples_MenuDialogList(T_GL_HGRAPHIC_LIB  graphicLib)
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
	T_GL_WCHAR choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_CANCEL, GL_KEY_0, GL_TIME_INFINITE);
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
	while(choice != GL_KEY_CANCEL);
}


/** Samples menu */
static void GL_Samples_MenuDialogGraphical(T_GL_HGRAPHIC_LIB  graphicLib)
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
	T_GL_WCHAR choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_CANCEL, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0  : GL_SampleDialogSlider    (graphicLib); break;
		case 1  : GL_SampleDialogProgress  (graphicLib); break;
		case 2  : GL_SampleDialogPicture   (graphicLib); break;
		case 3  : GL_SampleDialogMedia     (graphicLib); break;
		case 4  : GL_SampleDialogColor     (graphicLib); break;
		case 5  : GL_SampleDialogSignature (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL);
}


/** Samples menu */
static void GL_Samples_MenuDialogText(T_GL_HGRAPHIC_LIB  graphicLib)
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
	T_GL_WCHAR choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_CANCEL, GL_KEY_0, GL_TIME_INFINITE);
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
	while(choice != GL_KEY_CANCEL);
}


/** Samples menu */
void  GL_Samples_Menu(T_GL_HGRAPHIC_LIB  graphicLib)
{
	const char * menu [] =
	{
		"Dialog   TEXT->",
		"Dialog   GRAPHIC->",
		"Dialog   LIST->",
		"Widget   LABEL->",
		"Widget   BUTTON->",
		"Widget   EDIT->",
		"Widget   GRAPHIC->",
		"Widget   BARCODE->",
		"Widget   LIST->",
		"Widget   BAR->",
		"Widget   OTHER->",
		"All widgets",
		"Tutorial->",
	0};
	T_GL_WCHAR choice  = 0;

	do
	{
		choice = GL_Dialog_Menu   (graphicLib, 0, menu, choice, GL_BUTTON_CANCEL, GL_KEY_0, GL_TIME_INFINITE);
		switch(choice)
		{
		case 0  : GL_Samples_MenuDialogText       (graphicLib); break;
		case 1  : GL_Samples_MenuDialogGraphical  (graphicLib); break;
		case 2  : GL_Samples_MenuDialogList       (graphicLib); break;
		case 3  : GL_Samples_MenuWidgetLabel      (graphicLib); break;
		case 4  : GL_Samples_MenuWidgetButton     (graphicLib); break;
		case 5  : GL_Samples_MenuWidgetEdit       (graphicLib); break;
		case 6  : GL_Samples_MenuWidgetGraphical  (graphicLib); break;
		case 7  : GL_Samples_MenuWidgetBarcode    (graphicLib); break;
		case 8  : GL_Samples_MenuWidgetList       (graphicLib); break;
		case 9  : GL_Samples_MenuWidgetBar        (graphicLib); break;
		case 10 : GL_Samples_MenuWidgetOther      (graphicLib); break;
		case 11 : GL_SampleAllWidgets             (graphicLib); break;
		case 12 : GL_TutorialSteps_Menu           (graphicLib); break;
		}
	}
	while(choice != GL_KEY_CANCEL);
}


// Load graphic library and display menu with all samples
void GL_Samples(void)
{
	T_GL_HGRAPHIC_LIB graphicLib;
	
	// Create an instance of the graphics library. 
	// This creation takes some time, it is imperative to do once for the entire application life
#if defined(__TELIUM3__)
	graphicLib = GL_GraphicLib_CreateWithParam(0,"GOAL");
#else
	graphicLib = GL_GraphicLib_Create();
#endif
	
	// Display menu with all samples
	GL_Samples_Menu(graphicLib);

	// Release resources from the graphics library.
	// This call is crucial to the end of life of the application, this call frees resources and release memory allocated
	GL_GraphicLib_Destroy(graphicLib);
}
