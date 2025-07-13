#include "GL_GraphicLib.h"
#include "string.h"

#define GL_ID_MR         1
#define GL_ID_MRS        2
#define GL_ID_FIRST_NAME 3
#define GL_ID_LAST_NAME  4
#define GL_ID_BIRTH_DAY  5
#define GL_ID_MARRIED    6
#define GL_ID_OK         7
#define GL_ID_CANCEL     8

// On click ok button event
static bool GL_Tutorial_OnOkClick(T_GL_HMESSAGE message)
{
	GL_Message_SetResult(message, GL_KEY_VALID);
	return true;
}

// On click cancel button event
static bool GL_Tutorial_OnCancelClick(T_GL_HMESSAGE message)
{
	GL_Message_SetResult(message, GL_KEY_CANCEL);
	return true;
}

// On focus select all characters (first character pressed erase all other)
static bool GL_Tutorial_OnEditFocus(T_GL_HMESSAGE message)
{
	GL_Widget_SelectAll(GL_Message_GetWidget(message));
	return true;
}

void GL_TutorialStepScrollView(void)
{
	// Creates the graphic lib instance. The creation of the graphics library takes an important time, it is recommended to do creation once at application startup and use it for all windows created after.
	T_GL_HGRAPHIC_LIB gl = GL_GraphicLib_Create();

	// Creates window
	T_GL_HWIDGET window = GL_Window_Create(gl);

	// Create scroll view
	T_GL_HWIDGET scrollview = GL_ScrollView_Create(window);

	// Creates main layout
	T_GL_HWIDGET mainLayout = GL_Layout_Create(scrollview);

	GL_Widget_SetBackColor(window, 0xFFFFBBFE);
	GL_Widget_SetBorders(window, 2, 2, 2, 2, GL_UNIT_PIXEL, 0xFF5B005B);

	// Creates the title
	{
		T_GL_HWIDGET title = GL_Label_Create(mainLayout);
		GL_Widget_SetItem(title, 0, 0); 
		GL_Widget_SetText(title, "Information");
		GL_Widget_SetBackColor(title, GL_COLOR_PURPLE);
		GL_Widget_SetForeColor(title, GL_COLOR_WHITE);
		GL_Widget_SetExpand(title, GL_DIRECTION_WIDTH);
		GL_Widget_SetGrow(title, GL_DIRECTION_WIDTH);
		GL_Widget_SetGrow(title, GL_DIRECTION_WIDTH);
	}

	// Create the footer layout
	{
		T_GL_HWIDGET footerLayout;
		T_GL_HWIDGET buttonOk;
		T_GL_HWIDGET buttonCancel;

		footerLayout = GL_Layout_Create(mainLayout);
		GL_Widget_SetItem(footerLayout, 0, 2);
		
		buttonOk = GL_Button_Create(footerLayout);
		GL_Widget_SetText(buttonOk, "OK");
		buttonCancel = GL_Button_Create(footerLayout);
		GL_Widget_SetText(buttonCancel, "Cancel");
		GL_Widget_SetItem(buttonOk, 0, 0);
		GL_Widget_SetItem(buttonCancel, 1, 0);
		GL_Widget_SetId(buttonOk,     GL_ID_OK);
		GL_Widget_SetId(buttonCancel, GL_ID_CANCEL);

		GL_Widget_SetGrow(footerLayout, GL_DIRECTION_WIDTH);
		GL_Widget_SetGrow(buttonOk,     GL_DIRECTION_WIDTH);
		GL_Widget_SetGrow(buttonCancel, GL_DIRECTION_WIDTH);
		GL_Widget_SetShortcut(buttonOk,     GL_KEY_VALID);
		GL_Widget_SetShortcut(buttonCancel, GL_KEY_CANCEL);
		GL_Widget_SetFocusable(buttonOk,     false);
		GL_Widget_SetFocusable(buttonCancel, false);
		GL_Widget_SetForeColor(buttonOk,0xFFFFBBFE);
		GL_Widget_SetForeColor(buttonCancel,0xFFFFBBFE);
	}

	// Create the input layout
	{
		T_GL_HWIDGET inputLayout;
		T_GL_HWIDGET widget;
		inputLayout = GL_Layout_Create(mainLayout);
		GL_Widget_SetItem(inputLayout, 0, 1);

		widget = GL_RadioButton_Create(inputLayout);
		GL_Widget_SetText(widget, "Mr");
		GL_Widget_SetItem(widget, 0, 0);
		GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);
		GL_Widget_SetId(widget, GL_ID_MR);
		GL_Widget_SetCheck(widget, true);
		GL_Widget_SetForeColor(widget,0xFFFFBBFE);

		widget = GL_RadioButton_Create(inputLayout);
		GL_Widget_SetText(widget, "Mrs");
		GL_Widget_SetItem(widget, 1, 0);
		GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);
		GL_Widget_SetId(widget, GL_ID_MRS);
		GL_Widget_SetForeColor(widget,0xFFFFBBFE);

		widget = GL_Label_Create(inputLayout);
		GL_Widget_SetText(widget, "First name");
		GL_Widget_SetItem(widget, 0, 1);
		GL_Widget_SetForeColor(widget,0xFF5B005B);

		widget = GL_Edit_Create(inputLayout);
		GL_Widget_SetItem(widget, 1, 1);
		GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);
		GL_Widget_SetId(widget, GL_ID_FIRST_NAME);
		GL_Widget_SetForeColor(widget,0xFF5B005B);

		widget = GL_Label_Create(inputLayout);
		GL_Widget_SetText(widget, "Last name");
		GL_Widget_SetItem(widget, 0, 2);
		GL_Widget_SetForeColor(widget,0xFF5B005B);

		widget = GL_Edit_Create(inputLayout);
		GL_Widget_SetItem(widget, 1, 2);
		GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);
		GL_Widget_SetId(widget, GL_ID_LAST_NAME);
		GL_Widget_SetForeColor(widget,0xFF5B005B);

		widget = GL_Label_Create(inputLayout);
		GL_Widget_SetText(widget, "Birth day");
		GL_Widget_SetItem(widget, 0, 3);
		GL_Widget_SetForeColor(widget,0xFF5B005B);

		widget = GL_Edit_Create(inputLayout);
		GL_Widget_SetItem(widget, 1, 3);
		GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);
		GL_Widget_SetId(widget, GL_ID_BIRTH_DAY);
		GL_Widget_SetForeColor(widget,0xFF5B005B);

		widget = GL_CheckButton_Create(inputLayout);
		GL_Widget_SetText(widget, "Married");
		GL_Widget_SetItem(widget, 1, 4);
		GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);
		GL_Widget_SetId(widget, GL_ID_MARRIED);
		GL_Widget_SetForeColor(widget,0xFFFFBBFE);
	}

	{
		char firstName[256];
		char lastName[256];
		char birthDay[256];
		int mister, married;

		// Register event callback
		GL_Widget_RegisterCallbackById(window, GL_ID_OK,         GL_EVENT_STYLUS_CLICK, GL_Tutorial_OnOkClick);
		GL_Widget_RegisterCallbackById(window, GL_ID_CANCEL,     GL_EVENT_STYLUS_CLICK, GL_Tutorial_OnCancelClick);
		GL_Widget_RegisterCallbackById(window, GL_ID_FIRST_NAME, GL_EVENT_FOCUS,        GL_Tutorial_OnEditFocus);
		GL_Widget_RegisterCallbackById(window, GL_ID_LAST_NAME,  GL_EVENT_FOCUS,        GL_Tutorial_OnEditFocus);
		GL_Widget_RegisterCallbackById(window, GL_ID_BIRTH_DAY,  GL_EVENT_FOCUS,        GL_Tutorial_OnEditFocus);

		// Sets the default data
		GL_Widget_SetTextById(window, GL_ID_FIRST_NAME, "Set first name");
		GL_Widget_SetTextById(window, GL_ID_LAST_NAME,  "Set last name");
		GL_Widget_SetTextById(window, GL_ID_BIRTH_DAY,  "Set birth day");
		GL_Widget_SetCheck(GL_Widget_SearchId(window, GL_ID_MARRIED), 0);

		// Wait the validation by the user
		if (GL_Window_MainLoop(window) == GL_KEY_VALID)
		{
			// Gets the data entered
			strncpy(firstName, GL_Widget_GetTextById(window, GL_ID_FIRST_NAME), sizeof(firstName));
			strncpy(lastName,  GL_Widget_GetTextById(window, GL_ID_LAST_NAME),  sizeof(lastName));
			strncpy(birthDay,  GL_Widget_GetTextById(window, GL_ID_BIRTH_DAY),  sizeof(birthDay));

			if (GL_Widget_GetCheck(GL_Widget_SearchId(window, GL_ID_MR)))
			{
				mister= 1;
			}
			else
			{
				mister = 0;
			}

			if (GL_Widget_GetCheck(GL_Widget_SearchId(window, GL_ID_MARRIED)))
			{
				married = 1;
			}
			else
			{
				married = 0;
			}
		}
	}

	// Destroy the window
	GL_Widget_Destroy(window);

	// Destroy the graphic lib instance
	GL_GraphicLib_Destroy(gl);
}
