#include "GL_GraphicLib.h"
#include "GL_Samples.h"

// Build the receipt
T_GL_HWIDGET GL_SampleBuildReceipt(T_GL_HGRAPHIC_LIB gl)
{
	T_GL_HWIDGET document;
	T_GL_HWIDGET layout;
	T_GL_HWIDGET print;
	T_GL_HWIDGET picture;
	T_GL_DIM line = 0;
	int i;
	int total = 0;

	// Items names
	const char * items[]=
	{
		"Orange",
		"Apple",
		"Potatoe",
		"Carrot",
		"Turnip",
		"Squash",
		"Mandarin",
		"Eggplant",
		"Pear",
		"Kiwi",
		"Artichoke",
		"Bread",
		0
	};

	// Items prices
	const int prices[]=
	{
		123,
		234,
		156,
		102,
		301,
		234,
		396,
		102,
		302,
		500,
		212,
		221,
		0
	};

	// Creating a document intended for print
	document = GL_Document_Create(gl);

		// Creating a layout in document is required to use the alignments to the right and left of the text
		layout = GL_Layout_Create(document);

			// Adds an image on the receipt in the layout
			picture = GL_Picture_Create (layout);
				GL_Widget_SetSource     (picture, "file://flash/HOST/TU.TAR/icones/8.png");
				GL_Widget_SetItem       (picture, 0, line++);

			// Adds the address of the company
			print = GL_Print_Create    (layout);
				GL_Widget_SetId        (print, 1);
				GL_Widget_SetText      (print, "Ingenico SA");
				GL_Widget_SetItem      (print, 0, line++);
				GL_Widget_SetFontScale (print, GL_SCALE_XSMALL);

			print = GL_Print_Create    (layout);
				GL_Widget_SetText      (print, "1, rue Claude Chappe\nB.P. 346\n07503 Guilherand-Granges\n");
				GL_Widget_SetItem      (print, 0, line++);
				GL_Widget_SetFontScale (print, GL_SCALE_XSMALL);

			// Adds the date of receipt
			print = GL_Print_Create    (layout);
				GL_Widget_SetText      (print, "\nDate 01/06/11\n\n");
				GL_Widget_SetItem      (print, 0, line++);
				GL_Widget_SetFontScale (print, GL_SCALE_MEDIUM);
				GL_Widget_SetBackAlign (print, GL_ALIGN_LEFT);

			// Adds an item listing header
			print = GL_Print_Create    (layout);
				GL_Widget_SetText      (print, "Item");
				GL_Widget_SetItem      (print, 0, line);
				GL_Widget_SetMargins   (print, 10, 0, 0, 0, GL_UNIT_PIXEL);
				GL_Widget_SetFontScale (print, GL_SCALE_MEDIUM);
				GL_Widget_SetBackAlign (print, GL_ALIGN_LEFT);

			print = GL_Print_Create    (layout);
				GL_Widget_SetText      (print, "Price");
				GL_Widget_SetItem      (print, 0, line++);
				GL_Widget_SetMargins   (print, 0, 0, 10, 0, GL_UNIT_PIXEL);
				GL_Widget_SetFontScale (print, GL_SCALE_MEDIUM);
				GL_Widget_SetBackAlign (print, GL_ALIGN_RIGHT);

			// Add all items
			for (i = 0; items[i] != 0; i++)
			{
				print = GL_Print_Create    (layout);
					GL_Widget_SetText      (print, items[i]);
					GL_Widget_SetItem      (print, 0, line);
					GL_Widget_SetMargins   (print, 10, 0, 0, 0, GL_UNIT_PIXEL);
					GL_Widget_SetFontScale (print, GL_SCALE_MEDIUM);
					GL_Widget_SetBackAlign (print, GL_ALIGN_LEFT);

				print = GL_Print_Create    (layout);
					GL_Widget_SetText      (print, "%d.%02d", prices[i] / 100, prices[i] % 100);
					GL_Widget_SetItem      (print, 0, line++);
					GL_Widget_SetMargins   (print, 0, 0, 10, 0, GL_UNIT_PIXEL);
					GL_Widget_SetFontScale (print, GL_SCALE_MEDIUM);
					GL_Widget_SetBackAlign (print, GL_ALIGN_RIGHT);

				// Computes the total amount
				total += prices[i];
			}

			// Adds the total of all items
			print = GL_Print_Create    (layout);
				GL_Widget_SetText      (print, "TOTAL");
				GL_Widget_SetItem      (print, 0, line);
				GL_Widget_SetMargins   (print, 10, 10, 0, 0, GL_UNIT_PIXEL);
				GL_Widget_SetFontScale (print, GL_SCALE_LARGE);
				GL_Widget_SetBackAlign (print, GL_ALIGN_LEFT);

			print = GL_Print_Create    (layout);
				GL_Widget_SetText      (print, "%d.%02d EUR", total / 100, total % 100);
				GL_Widget_SetItem      (print, 0, line++);
				GL_Widget_SetMargins   (print, 0, 10, 10, 0, GL_UNIT_PIXEL);
				GL_Widget_SetFontScale (print, GL_SCALE_LARGE);
				GL_Widget_SetBackAlign (print, GL_ALIGN_RIGHT);

			print = GL_Print_Create    (layout);
				GL_Widget_SetText      (print, "\n\n\n\n\n\n\n");
				GL_Widget_SetItem      (print, 0, line++);

	return document;
}


// Sample of document
void GL_SampleDocument(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET    document;

	// Creating receipt
	document = GL_SampleBuildReceipt(graphicLib);

	// Receipt print
	GL_Document_Print(document, 0);

	// Destroy the document
	GL_Widget_Destroy(document);
}


// Build the receipt
T_GL_HWIDGET GL_SampleFontSizeReceipt(T_GL_HGRAPHIC_LIB gl)
{
	T_GL_HWIDGET document;
	T_GL_HWIDGET layout;
	T_GL_HWIDGET print;
	T_GL_DIM line = 0;

	// Creating a document intended for print
	document = GL_Document_Create(gl);

		// Creating a layout in document is required to use the alignments to the right and left of the text
		layout = GL_Layout_Create(document);

			print = GL_Print_Create   (layout);
				GL_Widget_SetText     (print, "GL_SkkCALE_XXSMALL");
				GL_Widget_SetItem     (print, 0, line++);
				GL_Widget_SetFontScale(print, GL_SCALE_XXSMALL);

			print = GL_Print_Create   (layout);
				GL_Widget_SetText     (print, "GL_SCALE_XSMALL");
				GL_Widget_SetItem     (print, 0, line++);
				GL_Widget_SetFontScale(print, GL_SCALE_XSMALL);

			print = GL_Print_Create   (layout);
				GL_Widget_SetText     (print, "GL_SCALE_SMALL");
				GL_Widget_SetItem     (print, 0, line++);
				GL_Widget_SetFontScale(print, GL_SCALE_SMALL);

			print = GL_Print_Create   (layout);
				GL_Widget_SetText     (print, "GL_SCALE_MEDIUM");
				GL_Widget_SetItem     (print, 0, line++);
				GL_Widget_SetFontScale(print, GL_SCALE_MEDIUM);

			print = GL_Print_Create   (layout);
				GL_Widget_SetText     (print, "GL_SCALE_LARGE");
				GL_Widget_SetItem     (print, 0, line++);
				GL_Widget_SetFontScale(print, GL_SCALE_LARGE);

			print = GL_Print_Create   (layout);
				GL_Widget_SetText     (print, "GL_SCALE_XLARGE");
				GL_Widget_SetItem     (print, 0, line++);
				GL_Widget_SetFontScale(print, GL_SCALE_XLARGE);

			print = GL_Print_Create   (layout);
				GL_Widget_SetText     (print, "GL_SCALE_XXLARGE");
				GL_Widget_SetItem     (print, 0, line++);
				GL_Widget_SetFontScale(print, GL_SCALE_XXLARGE);

			print = GL_Print_Create   (layout);
				GL_Widget_SetText     (print, "\n\n\n\n\n\n\n");
				GL_Widget_SetItem     (print, 0, line++);

			print = GL_Print_Create   (layout);
				GL_Widget_SetItem     (print, 0, line++);
				GL_Widget_SetText     (print, "UTF8 chars : éàùçè");
				GL_Widget_SetFontScale(print,GL_SCALE_LARGE);

	return document;
}


// Sample of document with font size
void GL_SampleDocumentFontSize(T_GL_HGRAPHIC_LIB graphicLib)
{
	T_GL_HWIDGET    document;

	// Creating receipt
	document = GL_SampleFontSizeReceipt(graphicLib);

	// Receipt print
	GL_Document_Print(document, 0);

	// Destroy the document
	GL_Widget_Destroy(document);
}


// Example of printing the displayed window
void GL_SampleDocumentWindow(T_GL_HGRAPHIC_LIB graphicLib)
{
	// Taking a picture of the image of the window
	{
		T_GL_HWIDGET window;
		T_GL_HWIDGET list;
		T_GL_HWIDGET widget;

		// Creating a blank window
		window = GL_Window_Create(graphicLib);

			// Creating a list
			list = GL_List_Create(window);

				// Adds a label and an edit to enter the name
				widget = GL_Label_Create(list);
				GL_Widget_SetText(widget,"Name");

				widget = GL_Edit_Create(list);
				GL_Widget_SetMask(widget,"/a/a/a/a/a/a/a/a/a/a");

				// Adds check button to select the marital status
				widget = GL_CheckButton_Create(list);
				GL_Widget_SetText(widget,"married");
				GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);

				// Adds quit button
				widget = GL_Button_Create(list);
				GL_Widget_SetText(widget,"quit");
				GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);

		// Display the window
		GL_Window_Dispatch(window, 0);

		// Create the file with the image
		GL_Window_SaveImage(window, "file://flash/HOST/window.bmp", GL_MIME_IMAGE_BMP);

		// Destroy the window
		GL_Widget_Destroy(window);
	}

	// printing the image of the window
	{
		T_GL_HWIDGET document;
		T_GL_HWIDGET picture;

		// Creating receipt
		document = GL_Document_Create(graphicLib);

			// Adds an image on the receipt in the layout
			picture = GL_Picture_Create (document);
			GL_Widget_SetSource     (picture, "file://flash/HOST/window.bmp");

		// Receipt print
		GL_Document_Print(document, 0);

		// Destroy the document
		GL_Widget_Destroy(document);
	}
}
