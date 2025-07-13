// $Id: GL_Tutorial.h,v 1.1.2.27 2012/12/17 09:51:23 rbertholet Exp $
// Tutorial
#ifndef GL_Tutorial_h_INCLUDED
#define GL_Tutorial_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_Tutorial
@{

	We will present step by step the creation of the next window with the C API Goal. 
	The same principle can be used by the graphic designer's : C API will be replaced by XML.
	This input field is an example to enter data about a user.

	@image html tutorial0.png




<br>
<hr><h1>Graphic library creation </h1>

	Above all we must create an instance of the graphics library. This instance can then create a window, dialog, etc. ...

	Creating an instance of the graphics library can be done in two ways, either using 
	@ref GL_GraphicLib_Create or using @ref GL_GraphicLib_CreateWithParam. 
	@ref GL_GraphicLib_CreateWithParam function should be used only if the rendering is done 
	on a remote screen or if you wish to select a particular skin.
	The easiest way is to use @ref GL_GraphicLib_Create.

	<b>IMPORTANT : The creation of the graphics library takes an important time, it is recommended to do creation once at application startup and use it for all windows created after.</b>

	Note : When you no longer need the graphics library you can recover the memory space with the function @ref GL_GraphicLib_Destroy.
	This function will destroy all windows created. If you constantly need to use graphics library, 
	it is better to destroy the windows you no longer need with the function @ref GL_Widget_Destroy.

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
// Creates the graphic lib instance
T_GL_HGRAPHIC_LIB gl = GL_GraphicLib_Create();

// Destroy the graphic lib instance
GL_GraphicLib_Destroy(gl);
	@endcode
	</td><td>
Note : the form is named "Form"
	@code
<?xml version="1.0" encoding="UTF-8"?>
<DAL xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://www.ingenico.com/schemas/dal">
	<version DAL_version="01.00" this_version="01.00" />
	<goal name="Form">
	</goal>
</DAL>
	@endcode
	</td></tr></table>

	See the full source of this step here @ref GL_TutorialStepGraphicLib.c





<br>
<hr><h1>Window creation </h1>

	To display the dialog box previously described, you must first create a window. 
	This window will receive all widgets (button and textbox). The window creation is done by the function
	@ref GL_Window_Create. By default the window fills the screen and is positioned in the upper left corner.
	The creation of a window is necessarily linked to an instance of graphic library.

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
// Creates window
T_GL_HWIDGET window = GL_Window_Create(gl);

// Shows the window 1 seconds
GL_Window_Dispatch(window, 1000);
	@endcode
	</td><td>
	@code
// Load window ressource file
T_GL_HWIDGET window = GL_GraphicLib_ReadResource(gl, "dal://Tutorial");
	@endcode
	@code
<window>
	<children>
	</children>
</window>
	@endcode
	</td></tr></table>

	See the full source of this step here 
		<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
			@ref GL_TutorialStepWindow.c
		</td><td>
			@ref GL_TutorialStepWindowGml.c
		</td></tr></table>





<br>
<hr><h1>Layout creation</h1>

	At this point the window is created but not yet visible on the screen.
	The window display is done by the function @ref GL_Window_Dispatch.
	However, it is necessary to add all objects to the window before his first display.

	Now we will begin placing items on the window. Optimal way to place widgets and that for any screen resolution, 
	it is strongly recommended the use of layouts. For this it is necessary to analyze the distribution of widgets in the layout.
	WARNING : A layout is an array where each cell in a column have the same width, and each cell in a line are the same height.

	In the dialog that we want to build we can detect three nested layout.

	@image html tutorial1.png
		
	The layout 1 is a main layout of the dialog, it is composed of 3 lines (header, body and footer).

	The layout 2 contains all the input fields, they are distributed several lines of two columns.

	The layout 3 allows to distribute the buttons in the footer.

	@image html tutorial2.png

	The main layout is attached to the window 

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
T_GL_HWIDGET mainLayout = GL_Layout_Create(window);
	@endcode
	</td><td>
	@code
<window>
	<children>
		<layout>
			<children>
			</children>
		</layout>
	</children>
</window>
	@endcode
	</td></tr></table>

	The main layout is composed of 3 lines:

	@image html tutorial3.png

	We will place the title in the main layout. To do this we will create the title using a widget label.
	Important: The widget title should be attached at its creation in the main layout.

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
T_GL_HWIDGET title = GL_Label_Create(mainLayout);
	@endcode
	</td><td>
	@code
<layout>
	<children>
		<label>
		</label>
	</children>
</layout>
	@endcode
	</td></tr></table>

	To place the title in the right cell on the layout you need :
	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetItem(title, 0, 0); 
	@endcode
	</td><td>
	@code
<label>
	...
	<item>
		<column>0</column>
		<row>0</row>
	</item>
</label>
	@endcode
	</td></tr></table>


	Then we put the text with:

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetText(title, "Information");
	@endcode
	</td><td>
	@code
<label>
	...
	<text>Information</text>
</label>
	@endcode
	</td></tr></table>

	Then the colors of text and background are set with :

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetBackColor(title, GL_COLOR_PURPLE);
GL_Widget_SetForeColor(title, GL_COLOR_WHITE);
	@endcode
	</td><td>
	@code
<label>
	...
	<backcolor>0xFF800080</backcolor>
	<forecolor>0xFFFFFFFF</forecolor>
</label>
	@endcode
	</td></tr></table>


	To expand the title over the entire width, you must set :

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetExpand(title, GL_DIRECTION_WIDTH);
	@endcode
	</td><td>
	@code
<label>
	...
	<expand>width</expand>
</label>
	@endcode
	</td></tr></table>


	The representation obtained is as follows:

	@image html Tutorial6.png

	At this point the title is centered on the window, this may should be strange, 
	but like other cells were not yet used, then it is placed optimally on the screen.

	See the full source of this step here 
		<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
			@ref GL_TutorialStepLayout.c
		</td><td>
			@ref GL_TutorialStepWindowGml.c <br>
			@ref GL_TutorialStepLayout.gml	
		</td></tr></table>





<br>
<hr><h1>Footer creation</h1>

	Now we will place the footer with the buttons, we'll use a second layout with two columns.

	@image html Tutorial5.png

	The creation of the layout is as follows:

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
T_GL_HWIDGET footerLayout = GL_Layout_Create(mainLayout);
	@endcode
	</td><td>
	@code
...
<layout>
	<children>
		<layout>
		</layout>
	</children>
</layout>
	@endcode
	</td></tr></table>


	You may notice that this layout is attached to the main layout.
	It must then be placed in the right line on the main layout.
	You must set :

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetItem(footerLayout, 0, 2);
	@endcode
	</td><td>
	@code
...
<layout>
	<item>
		<column>0</column>
		<row>2</row>
	</item>
</layout>
	@endcode
	</td></tr></table>

	We will now create the two buttons.

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
T_GL_HWIDGET buttonOk;
T_GL_HWIDGET buttonCancel;
buttonOk = GL_Button_Create(footerLayout);
GL_Widget_SetText(buttonOk, "OK");
buttonCancel = GL_Button_Create(footerLayout);
GL_Widget_SetText(buttonCancel, "Cancel");
	@endcode
	</td><td>
	@code
...
<layout>
	...
	<children>
		<button>
			<text>OK</text>
		</button>
		<button>
			<text>Cancel</text>
		</button>
	</children>
</layout>
	@endcode
	</td></tr></table>

	The buttons should be tied to the layout of the footer at the creation.
	You must then place the buttons in each cell of the layout.

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetItem(buttonOk, 0, 0);
GL_Widget_SetItem(buttonCancel, 1, 0);
	@endcode
	</td><td>
	@code
...
<button>
	...
	<item>
		<column>0</column>
		<row>0</row>
	</item>
</button>
<button>
	...
	<item>
		<column>1</column>
		<row>0</row>
	</item>
</button>
	@endcode
	</td></tr></table>


	The representation obtained is as follows:

		@image html Tutorial7.png

	See the full source of this step here 
		<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
			@ref GL_TutorialStepFooter.c
		</td><td>
			@ref GL_TutorialStepWindowGml.c <br>
			@ref GL_TutorialStepFooter.gml	
		</td></tr></table>





<br>
<hr><h1>Inputs fields creation </h1>

	Now we will put all the input fields on the dialog box, we'll use a third layout with two columns

	@image html Tutorial4.png

	The creation of the layout is as follows:

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
T_GL_HWIDGET inputLayout = GL_Layout_Create(mainLayout);
	@endcode
	</td><td>
	@code
...
<window>
	<children>
		<layout>
			<children>
				...
				<layout>
					<children>
					</children>
				</layout>
			</children>
		</layout>
	</children>
</window>
	@endcode
	</td></tr></table>


	You may notice that this layout is attached to the main layout.
	It must then be placed in the right line on the main layout.

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetItem(inputLayout, 0, 1);
	@endcode
	</td><td>
	@code
...
<layout>
	<item>
		<column>0</column>
		<row>1</row>
	</item>
	<children>
	</children>
</layout>
	@endcode
	</td></tr></table>

	We will now create the first line of the input layout, for this we add two radio widget.
	The radio buttons are placed in the right cell of the input layout.

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
widget = GL_RadioButton_Create(inputLayout);
GL_Widget_SetText(widget, "Mr");
GL_Widget_SetItem(widget, 0, 0);
GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);

widget = GL_RadioButton_Create(inputLayout);
GL_Widget_SetText(widget, "Mrs");
GL_Widget_SetItem(widget, 1, 0);
GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);
	@endcode
	</td><td>
	@code
...
<layout>
	...
	<children>
		<radiobutton>
			<text>Mr</text>
			<item>
				<column>0</column>
				<row>0</row>
			</item>
			<expand>width</expand>
		</radiobutton>
		<radiobutton>
			<text>Mrs</text>
			<item>
				<column>1</column>
				<row>0</row>
			</item>
			<expand>width</expand>
		</radiobutton>
	</children>
</layout>
	@endcode
	</td></tr></table>

	It is imperative to initialize the radio buttons or you may have an uncertain state.
	To do this we sets the radio button to the gentleman.

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetCheck(widget, true);
	@endcode
	</td><td>
	@code
...
<layout>
	...
	<children>
		<radiobutton>
			...
			<state>checked</state>
		</radiobutton>
		...
	</children>
</layout>
	@endcode
	</td></tr></table>


	Now we will add the creation of the input line of the first name.
	For these input fields we force the expension (with @ref GL_Widget_SetExpand) 
	they occupy the full width of the column of the input layout.


	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
widget = GL_Label_Create(inputLayout);
GL_Widget_SetText(widget, "First name");
GL_Widget_SetItem(widget, 0, 1);

widget = GL_Edit_Create(inputLayout);
GL_Widget_SetItem(widget, 1, 1);
GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);
	@endcode
	</td><td>
	@code
...
<layout>
	...
	<children>
		...
		<label>
			<text>First name</text>
			<item>
				<column>0</column>
				<row>1</row>
			</item>
		</label>
		<edit>
			<item>
				<column>1</column>
				<row>1</row>
			</item>
			<expand>width</expand>
		</edit>
	</children>
</layout>
	@endcode
	</td></tr></table>


	Now we will add the creation of the input line of the last name.
	
	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
widget = GL_Label_Create(inputLayout);
GL_Widget_SetText(widget, "Last name");
GL_Widget_SetItem(widget, 0, 2);
	
widget = GL_Edit_Create(inputLayout);
GL_Widget_SetItem(widget, 1, 2);
GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);
	@endcode
	</td><td>
	@code
...
<layout>
	...
	<children>
		...
		<label>
			<text>Last name</text>
			<item>
				<column>0</column>
				<row>2</row>
			</item>
		</label>
		<edit>
			<item>
				<column>1</column>
				<row>2</row>
			</item>
			<expand>width</expand>
		</edit>
	</children>
</layout>
	@endcode
	</td></tr></table>	
	

	Now we will add the creation of the input line of the birth day.
	
	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
widget = GL_Label_Create(inputLayout);
GL_Widget_SetText(widget, "Birth day");
GL_Widget_SetItem(widget, 0, 3);

widget = GL_Edit_Create(inputLayout);
GL_Widget_SetItem(widget, 1, 3);
GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);
	@endcode
	</td><td>
	@code
...
<layout>
	...
	<children>
		...
		<label>
			<text>Birth day</text>
			<item>
				<column>0</column>
				<row>3</row>
			</item>
		</label>
		<edit>
			<expand>width</expand>
			<item>
				<column>1</column>
				<row>3</row>
			</item>
		</edit>
	</children>
</layout>
	@endcode
	</td></tr></table>	
	
	
	Now we add the checkbox :
	
	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
widget = GL_CheckButton_Create(inputLayout);
GL_Widget_SetText(widget, "Married");
GL_Widget_SetItem(widget, 1, 4);
GL_Widget_SetExpand(widget, GL_DIRECTION_WIDTH);
	@endcode
	</td><td>
	@code
...
<layout>
	...
	<children>
		...
		<checkbutton>
			<text>Married</text>
			<item>
				<column>1</column>
				<row>4</row>
			</item>
			<expand>width</expand>
		</checkbutton>
	</children>
</layout>
	@endcode
	</td></tr></table>	
		
	
	The representation obtained is as follows:
		@image html Tutorial8.png

	See the full source of this step here 
		<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
			@ref GL_TutorialStepInput.c
		</td><td>
			@ref GL_TutorialStepWindowGml.c<br>
			@ref GL_TutorialStepInput.gml
		</td></tr></table>





<br>
<hr><h1>Customisation</h1>

	As you can see the title is not positioned to the top of the window, and the buttons are not positioned at the bottom of the window
	The main layout in the absence of constraint design cell, tries to equitable distribution of each cell to its grid.
	As we want that the title must be placed is at the top of the screen, 
	we must force the cell of the title does expand in width only, why we use the next call :
	
	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetGrow(title, GL_DIRECTION_WIDTH);
	@endcode
	</td><td>
	@code
...
<label>
	<text>Information</text>
	...
	<grow>width</grow>
</label>
	@endcode
	</td></tr></table>	
	

	We must also place the same constraint on the layout of the buttons
	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetGrow(footerLayout, GL_DIRECTION_WIDTH);
	@endcode
	</td><td>
	@code
...
<layout>
	...
	<grow>width</grow>
</layout>
	@endcode
	</td></tr></table>	
	
	And we must also place the same constraint for buttons
	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetGrow(buttonOk,     GL_DIRECTION_WIDTH);
GL_Widget_SetGrow(buttonCancel, GL_DIRECTION_WIDTH);
	@endcode
	</td><td>
	@code
...
<layout>
	...
	<children>
		<button>
			<text>OK</text>
			<grow>width</grow>
			...
		</button>
		<button>
			<text>Cancel</text>
			<grow>width</grow>
			...
		</button>
	</children>
	<grow>width</grow>
</layout>
	@endcode
	</td></tr></table>	

	It is necessary in this case to put the constraint on each of the nested objects,
	otherwise it will not produce the desired result

	The representation obtained is as follows:

	@image html Tutorial9.png




<br>
<hr><h1>Assignment ID</h1>

	To simplify data retrieval and especially to separate the creation of the window of data extraction, 
	each field will receive a unique identifier.
	To do this we add identifiers after each field creation.

	@code
#define GL_ID_MR         1
#define GL_ID_MRS        2
#define GL_ID_FIRST_NAME 3
#define GL_ID_LAST_NAME  4
#define GL_ID_BIRTH_DAY  5
#define GL_ID_MARRIED    6
#define GL_ID_OK         7
#define GL_ID_CANCEL     8
	@endcode

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetId(buttonOk,     GL_ID_OK);
GL_Widget_SetId(buttonCancel, GL_ID_CANCEL);
...
GL_Widget_SetId(widget, GL_ID_MR);
...
GL_Widget_SetId(widget, GL_ID_MRS);
...
GL_Widget_SetId(widget, GL_ID_FIRST_NAME);
...
GL_Widget_SetId(widget, GL_ID_LAST_NAME);
...
GL_Widget_SetId(widget, GL_ID_BIRTH_DAY);
...
GL_Widget_SetId(widget, GL_ID_MARRIED);
	@endcode
	</td><td>
	@code
...
<button>
	<text>OK</text>
	...
	<id>7</id>
</button>
<button>
	<text>Cancel</text>
	...
	<id>8</id>
</button>
...
<radiobutton>
	<text>Mr</text>
	...
	<id>1</id>
</radiobutton>
<radiobutton>
	<text>Mrs</text>
	...
	<id>2</id>
</radiobutton>
<label>
	<text>First name</text>
	...
</label>
<edit>
	...
	<id>3</id>
</edit>
<label>
	<text>Last name</text>
	...
</label>
<edit>
	...
	<id>4</id>
</edit>
<label>
	<text>Birth day</text>
	...
</label>
<edit>
	...
	<id>5</id>
</edit>
<checkbutton>
	<text>Married</text>
	...
	<id>6</id>
</checkbutton>
	@endcode
	</td></tr></table>

	To extract the string data you can use the function @ref GL_Widget_GetTextById.
	WARNING : this function returns a pointer to internal GOAL data, you must copy the contents into another variable.

See the full source of this step here 
	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
		@ref GL_TutorialStepId.c
	</td><td>
		@ref GL_TutorialStepWindowGml.c<br>
		@ref GL_TutorialStepId.gml
	</td></tr></table>




<br>
<hr><h1>Event handling</h1>

	Now that we have created the graph, we'll add the event management button.
	Currently the dialog only to appear and to disappear, now we'll stay inside until a click of a button.

	We'll create two callback functions. These functions change the result of the window.

	@code
static bool GL_Tutorial_OnOkClick(T_GL_HMESSAGE message)
{
	GL_Message_SetResult(message, GL_KEY_VALID);
	return true;
}

static bool GL_Tutorial_OnCancelClick(T_GL_HMESSAGE message)
{
	GL_Message_SetResult(message, GL_KEY_CANCEL);
	return true;
}
	@endcode

	Now register the events callback buttons.
	@code
GL_Widget_RegisterCallbackById(window, GL_ID_OK,     GL_EVENT_STYLUS_CLICK, GL_Tutorial_OnOkClick);
GL_Widget_RegisterCallbackById(window, GL_ID_CANCEL, GL_EVENT_STYLUS_CLICK, GL_Tutorial_OnCancelClick);
	@endcode
	
	

	We replaces the function @ref GL_Window_Dispatch by the blocking the function @ref GL_Window_MainLoop. 
	This function remains on the dialog box until the result not set (the result is set with @ref GL_Message_SetResult function).

	@code
if (GL_Window_MainLoop(window) == GL_KEY_VALID)
{
	// Treatment
}
	@endcode

	If you click on "OK" button you obtained as a result @ref GL_KEY_VALID of the function @ref GL_Window_MainLoop,
	if you click on "Cancel" button you obtained as a result @ref GL_KEY_CANCEL.

	To simplify use of dialog, we will place shortcuts on keyboard buttons.

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetShortcut(buttonOk,     GL_KEY_VALID);
GL_Widget_SetShortcut(buttonCancel, GL_KEY_CANCEL);
	@endcode
	</td><td>
	@code
...
<children>
	<button>
		<text>OK</text>
		...
		<shortcut>\uF850</shortcut>
	</button>
	<button>
		<text>Cancel</text>
		...
		<shortcut>\uF851</shortcut>
	</button>
</children>	
	@endcode
	</td></tr></table>

	When you press the green key on the keyboard that will call to callback GL_Tutorial_OnOkClick,
	and when you press the red key on the keyboard that will call to callback GL_Tutorial_OnCancelClick.

	When the focus is set on a widget button, pressing the green button on the keyboard is equivalent to a stylus tap on the button.
	If this is done on the cancel button, this can cause confusion for the user.
	This then produces a result @ref GL_KEY_CANCEL when the user pressed the green button on the keyboard.
	To avoid this it is best to prohibit the focus on the two buttons with this next lines :
	
	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
GL_Widget_SetFocusable(buttonOk, false);
GL_Widget_SetFocusable(buttonCancel, false);
	@endcode
	</td><td>
	@code
...
<children>
	<button>
		<text>OK</text>
		...
		<focusable>false</focusable>
	</button>
	<button>
		<text>Cancel</text>
		...
		<focusable>false</focusable>
	</button>
</children>
	@endcode
	</td></tr></table>
	

	Thus both buttons will never receive more focus.

	See the full source of this step here 
		<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
			@ref GL_TutorialStepEvent.c
		</td><td>
			@ref GL_TutorialStepEventGml.c<br>
			@ref GL_TutorialStepEvent.gml
		</td></tr></table>





<br>
<hr><h1>Sets and gets datas </h1>

	Now we will retrieve the data entered in the dialog. 

	@code
char firstName[256];
char lastName[256];
char birthDay[256];
strncpy(firstName, GL_Widget_GetTextById(window, GL_ID_FIRST_NAME), sizeof(firstName));
strncpy(lastName,  GL_Widget_GetTextById(window, GL_ID_LAST_NAME),  sizeof(lastName));
strncpy(birthDay,  GL_Widget_GetTextById(window, GL_ID_BIRTH_DAY),  sizeof(birthDay));
	@endcode

	To extract the contents of the checkbox and radio button, 
	we must first search the widget based on its identifier with the function @ref GL_Widget_SearchId, and then extract the widget state.

	@code
int mister, married;
if (GL_Widget_GetCheckById(window, GL_ID_MR))
{
	mister= 1;
}
else
{
	mister = 0;
}

if (GL_Widget_GetCheckById(window, GL_ID_MARRIED))
{
	married = 1;
}
else
{
	married = 0;
}
	@endcode


	The data may have been previously entered in the application life. 
	In this case the fields must have the data already entered before opening the dialog box.

	@code
// Sets the default data
GL_Widget_SetTextById(window, GL_ID_FIRST_NAME, "Set first name");
GL_Widget_SetTextById(window, GL_ID_LAST_NAME,  "Set last name");
GL_Widget_SetTextById(window, GL_ID_BIRTH_DAY,  "Set birth day");
GL_Widget_SetCheckById(window, GL_ID_MARRIED, 0);
	@endcode

	And now the finish: adding text colors and background of the window.

	@image html Tutorial10.png


	See the full source of this step here 
		<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
			@ref GL_TutorialStepData.c
		</td><td>
			@ref GL_TutorialStepDataGml.c<br>
			@ref GL_TutorialStepDataGml.gml
		</td></tr></table>

<br>
<hr><h1>Fine tuning</h1>

	We note that on some terminals the input fields does not fit in the screen.
	The easiest solution is to add a scroll view the entire window.
	For this we modify the creation of the main layout

	<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
	@code
// Create scroll view
T_GL_HWIDGET scrollview = GL_ScrollView_Create(window);

// Creates main layout
T_GL_HWIDGET mainLayout = GL_Layout_Create(scrollview);
	@endcode
	</td><td>
	@code
...
<window>
	<children>
		<scrollview>
			<children>
				<layout>
				...
				</layout>
			</children>
		</scrollview>
	</children>
</window>
...
	@endcode
	</td></tr></table>

When entering data you must first erase the contents of each input field.
This is not very ergonomic. We wish that when the first character is input, the field
is automatically erased. For this we force a selection of all the characters each time the focus is positioned on an input field.

	@code
// On focus select all characters (first character pressed erase all other)
static bool GL_Tutorial_OnEditFocus(T_GL_HMESSAGE message)
{
	GL_Widget_SelectAll(GL_Message_GetWidget(message));
	return true;
}
	@endcode

	@code
GL_Widget_RegisterCallbackById(window, GL_ID_FIRST_NAME, GL_EVENT_FOCUS,        GL_Tutorial_OnEditFocus);
GL_Widget_RegisterCallbackById(window, GL_ID_LAST_NAME,  GL_EVENT_FOCUS,        GL_Tutorial_OnEditFocus);
GL_Widget_RegisterCallbackById(window, GL_ID_BIRTH_DAY,  GL_EVENT_FOCUS,        GL_Tutorial_OnEditFocus);
	@endcode

	See the full source of this step here 
		<table><tr><td>With C api</td><td>With GML ressource</td></tr><tr><td>
			@ref GL_TutorialStepScrollView.c
		</td><td>
			@ref GL_TutorialStepScrollViewGml.c<br>
			@ref GL_TutorialStepScrollViewGml.gml
		</td></tr></table>
	
@} 

@addtogroup GL_TutorialDesign
@{
	In this chapter only presents the design, C code is not mentioned it has already been seen in the previous tutorial.
	In this tutorial we want to create the following screen:
	@image html TutoDesign1.png

	Each icon should be clickable by the stylus, and you can set the focus (purple square) of an icon to another by the arrow key.

	We will cut into several layout positioned on the screen (See colored rectangle) :
	@image html TutoDesign2.png

	Each layout is divided into two cells, one containing the icon in the other text : 
	@image html TutoDesign3.png

	First step creating a window :
@code
<?xml version="1.0" encoding="UTF-8"?>
<DAL xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="http://www.ingenico.com/schemas/dal/1_0">
	<version DAL_version="01.00" this_version="01.00" />
	<goal name="/006E/Design">
	<window>
		<children>
			...
		</children>
	</window>
</goal>
</DAL>
@endcode

Create a layout containing the first icon, the focus and the text

@code
...
<layout>
	<children>
		<picture>
			<source>FOCUS.PNG</source>
			<item>
				<column>0</column>
				<row>0</row>
			</item>
		</picture>
		<picture>
			<source>0.PNG</source>
			<item>
				<column>0</column>
				<row>0</row>
			</item>
		</picture>
		<label>
			<text>find</text>
			<item>
				<column>1</column>
				<row>0</row>
			</item>
		</label>
	</children>
</layout>
...
@endcode

Here we place two images in the same cell layout, first focus as it appears under the icon, and the second icon. 
Important : reading order of GML is identical to the order of display, if you want an image on in another, it is imperative to place it before.
Then in the second cell is placed the text.

Must then place the layout on the screen.
@code
<layout>
	<position>
		<y>20</y>
		<x>30</x>
	</position>
	...
</layout>
@endcode

In the absence of positioning the layout will occupy the entire screen. 
Once the position set it automatically sizes the minimum size of the widgets it contains. We then get :

@image html TutoDesign4.png

To tell the widget that can receive the focus you need to place the property "focusable" to true.

@code
<layout>
	<focusable>true</focusable>
	...
</layout>
@endcode

The focus here is evidenced by the show or hide of the image focus.png.
Focus state is redistributed to widget children but focus is always assigned to only one widget at a time, 
then it is imperative to put the "focusable" at the top of the hierarchy.

To make visible the image of the focus.png only when the focus is on the layout, you must added the property "statemask"
on the picture.
The property "statemask" take the next value :
	- focused : The widget will be displayed only if it has focus
	- unfocused : The widget will be displayed only if it has not focus
	- checked : The widget will be displayed only if it is checked
	- unchecked : The widget will be displayed only if it is not checked
Here we want the image focus.png appears only when the focus is present, then set :

@code
<picture>
	<source>FOCUS.PNG</source>
	<statemask>focused</statemask>
	...
</picture>
@endcode

To generate the @ref GL_EVENT_STYLUS_CLICK event when you click with the stylus on the layout, 
you must set the property "clickable":

@code
<layout>
	<clickable>true</clickable>
	...
</layout>
@endcode

This property is not sufficient, we must now define which areas are sensitive to clicks. 
And all children of the layout must set the property "clicksensitive":

@code
<layout>
	<clickable>true</clickable>
	..
	<children>
		<picture>
			<source>FOCUS.PNG</source>
			<clicksensitive>true</clicksensitive>
			...
		</picture>
		<picture>
			<source>0.PNG</source>
			<clicksensitive>true</clicksensitive>
			...
		</picture>
		<label>
			<text>find</text>
			<clicksensitive>true</clicksensitive>
			...
		</label>
	</children>
</layout>
@endcode

Now the first is finished, the others are identical in principle.

@ref GL_TutorialDesign.gml

@}

@addtogroup KSFAM_GOAL_Documentation
@{

@example GL_SampleArrowButton.c
@example GL_SampleButton.c
@example GL_SampleButtonStretch.c
@example GL_SampleCheckButton.c
@example GL_SampleDialogAmount.c
@example GL_SampleDialogChoice.c
@example GL_SampleDialogColor.c
@example GL_SampleDialogDate.c
@example GL_SampleDialogFile.c
@example GL_SampleDialogIconMenu.c
@example GL_SampleDialogIp.c
@example GL_SampleDialogMedia.c
@example GL_SampleDialogMenu.c
@example GL_SampleDialogMessage.c
@example GL_SampleDialogMultiChoice.c
@example GL_SampleDialogPassword.c
@example GL_SampleDialogPicture.c
@example GL_SampleDialogProgress.c
@example GL_SampleDialogScheme.c
@example GL_SampleDialogSlider.c
@example GL_SampleDialogText.c
@example GL_SampleDialogVirtualKeyboard.c
@example GL_SampleDocument.c
@example GL_SampleDrawing.c
@example GL_SampleDrawingNotVectorized.c
@example GL_SampleEdit.c
@example GL_SampleEditMask.c
@example GL_SampleEditMode.c
@example GL_SampleEditMultiline.c
@example GL_SampleFont.c
@example GL_SampleFontStyle.c
@example GL_SampleHScrollBar.c
@example GL_SampleHSlider.c
@example GL_SampleIcon.c
@example GL_SampleLabel.c
@example GL_SampleLayout.c
@example GL_SampleList.c
@example GL_SampleUserList.c
@example GL_SampleListDynamic.c
@example GL_SampleListIcon.c
@example GL_SampleMedia.c
@example GL_SampleOrientation.c
@example GL_SamplePalette.c
@example GL_SamplePicture.c
@example GL_SamplePictureStretch.c
@example GL_SamplePlugin.c
@example GL_SampleProgressBar.c
@example GL_SampleRadioButton.c
@example GL_Samples.c
@example GL_SampleScrollView.c
@example GL_SampleTimer.c
@example GL_SampleVirtualKeyboard.c
@example GL_SampleVScrollBar.c
@example GL_SampleWindow.c
@example GL_SampleSendClick.c
@example GL_SampleSendKey.c
@example GL_SampleScrollText.c
@example GL_SampleCalculator.c
@example GL_SampleUserControl.c
@example GL_SampleBarcodeQR.c
@example GL_SampleBarcodeEAN8.c
@example GL_SampleBarcodeEAN13.c
@example GL_SampleBarcodeCODE25.c
@example GL_SampleBarcodeCODE39.c
@example GL_SampleBarcodeCODE128.c

@example GL_TutorialStepGraphicLib.c
@example GL_TutorialStepWindowGml.c
@example GL_TutorialStepWindow.c
@example GL_TutorialStepLayout.c
@example GL_TutorialStepLayout.gml
@example GL_TutorialStepFooter.c
@example GL_TutorialStepFooter.gml
@example GL_TutorialStepInput.c
@example GL_TutorialStepInput.gml
@example GL_TutorialStepId.c
@example GL_TutorialStepId.gml
@example GL_TutorialStepEvent.c
@example GL_TutorialStepEvent.gml
@example GL_TutorialStepEventGml.c
@example GL_TutorialStepData.c
@example GL_TutorialStepDataGml.c
@example GL_TutorialStepDataGml.gml
@example GL_TutorialStepScrollView.c
@example GL_TutorialStepScrollViewGml.c
@example GL_TutorialStepScrollViewGml.gml
@example GL_TutorialDesign.gml

@}

*/

#ifdef __cplusplus
}
#endif
#endif // GL_Tutorial_h_INCLUDED
