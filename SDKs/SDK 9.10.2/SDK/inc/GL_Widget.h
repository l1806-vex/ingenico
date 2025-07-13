// $Id: GL_Widget.h,v 1.1.2.133 2013/01/21 07:51:30 rbertholet Exp $
// Class manager characteristics common to all graphical objects
#ifndef GL_Widget_h_INCLUDED
#define GL_Widget_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_WidgetDoc
@{
@section GL_Widget_Properties Common properties
This section presents the propeties shared by all widgets :

Properties that affect the rendering :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_RangeProperties
	- @ref GL_Widget_AppearanceProperties

Properties to change the behavior of a widget :
	- @ref GL_Widget_ClickProperties
	- @ref GL_Widget_FocusProperties
	- @ref GL_Widget_CheckProperties
	- @ref GL_Widget_StateMaskProperties
	- @ref GL_Widget_ShortcutProperties

Properties for widgets with text :
	- @ref GL_Widget_TextEscapeSequence
	- @ref GL_Widget_TextProperties
	- @ref GL_Widget_InputProperties
	- @ref GL_Widget_MaskProperties
	- @ref GL_Widget_Font
	- @ref GL_Widget_FormatProperties

Properties for widgets with images :
	- @ref GL_Widget_ImagesProperties
	- @ref GL_Widget_Image
	- @ref GL_Widget_ImagesTransformationProperties
	- @ref GL_WguImage

Properties for messages : 
	- @ref GL_Widget_CommonMessage
	- @ref GL_Widget_CallbackProperties

Properties for files and directories :
	- @ref GL_Widget_Url

Properties for the user : 
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_ByIdProperties
	- @ref GL_Widget_UserDataProperties

For messages sent by this widget see :
	- @ref GL_Widget_CommonMessage


<hr>@section GL_Widget_UnitProperties Unit

	The sizes, positions, margins can be expressed in different units @ref T_GL_UNIT :
		- @ref GL_UNIT_PERCENT : All sizes and positions are expressed in percentage of its parent, this unit is highly <b>RECOMMENDED</b>
		- @ref GL_UNIT_PERTHOUSAND : All sizes and positions are expressed in per thousand of its parent, this unit is highly <b>RECOMMENDED</b>
		- @ref GL_UNIT_PIXEL : All sizes and positions are expressed in pixels, this unit is <b>NOT RECOMMENDED</b> especially if your application needs to operate on varied size screens


<hr>@section GL_Widget_GeometryProperties Geometry

	The functions GL_Widget_Set* allow you to configure the geometry of a widget. 
	The functions GL_Widget_Get* get the configuration value previously set. 
	If you would like to get the size of the actual position in pixels on the screen must use the @ref GL_Widget_GetRect.
	Default values positioned are @ref GL_DIM_UNDEFINED.
	The size and position can be controlled by the following functions:
		- @ref GL_Widget_GetSize : Gets the widget size 
		- @ref GL_Widget_SetSize : Sets the widget size 
		- @ref GL_Widget_GetPosition : Gets the widget position
		- @ref GL_Widget_SetPosition : Sets the widget position


	<h2>Minimal size</h2>

		The functions GL_Widget_Set* allow you to configure the geometry of a widget. 
		The functions GL_Widget_Get* get the configuration value previously set. 
		If you would like to get the size of the actual position in pixels on the screen must use the @ref GL_Widget_GetRect.
		Default values positioned are @ref GL_DIM_MIN.
		When you specify a minimum size of a widget, the widget will not have a size smaller than this size.
		To change the minimum size see : 
			- @ref GL_Widget_SetMinSize : Sets the minimum widget size
			- @ref GL_Widget_GetMinSize : Gets the minimum widget size

		Example for three label placed in a layout:

			@image html normalSize.png

		If you specifie a minimum size for the label "2" larger than the cell size, 
		cells with labels "1" and "3" will have their size reduced, you get :
	
			@image html minSize.png


	<h2>Maximal size</h2>

		The functions GL_Widget_Set* allow you to configure the geometry of a widget. 
		The functions GL_Widget_Get* get the configuration value previously set. 
		If you would like to get the size of the actual position in pixels on the screen must use the @ref GL_Widget_GetRect.
		Default values positioned are @ref GL_DIM_MAX.
		When you specify a maximum size of a widget, the widget will not have a size greater than this size.
		To change the maximum size see :
			- @ref GL_Widget_SetMaxSize : Sets the maximum widget size
			- @ref GL_Widget_GetMaxSize : Gets the maximum widget size

		Example if you specifie a maximum size for the label "2" smaller than the cell size, you get :

			@image html maxSize.png


<hr>@section GL_Widget_LayoutProperties Layout

	All of the following properties are mainly used with widgets embedded in a layout. For more details on the layout see @ref GL_LayoutDoc


	<h2>Item placement</h2>

		Each widget is placed in a cell layout thanks to the function :
			- @ref GL_Widget_SetItem : Sets a widget location in the layout
			- @ref GL_Widget_GetItem : Gets a widget location in the layout

		A layout cell can contain multiple widgets, the size of a cell depends on all the properties of the widgets it contains.


	<h2>Layout cell growth</h2>

		The growth of a cell layout can be controlled by the following functions :
			- @ref GL_Widget_SetGrow : Sets the widget grow flag
			- @ref GL_Widget_GetGrow : Gets the widget grow flag

		It is thus possible to enable or disable the growth of a cell in width, height or both.
		A cell that is not allowed to grow take as the maximum size its contents.

		In the example below it disables the growth of the label "2 " in both directions (@ref GL_DIRECTION_NONE) :

			@image html growNone.png

		In the example below allows the growth of the label "2" in width (@ref GL_DIRECTION_WIDTH) :

			@image html growWidth.png

		In the example below allows the growth of the label "2" in height (@ref GL_DIRECTION_HEIGHT) :

			@image html growHeight.png

		In the example below allows the growth of the label "2" in all directions (@ref GL_DIRECTION_ALL) :

			@image html growAll.png


	<h2>Layout cell shrink</h2>
		The shrink of a cell layout can be controlled by the following functions :
			- @ref GL_Widget_SetShrink : Sets the widget shrink flag
			- @ref GL_Widget_GetShrink : Gets the widget shrink flag

		A cell that allows the shrinkage may be smaller than its contents.

		In the following example the central cell contains a long text, which forces the cell shrinkage around (@ref GL_DIRECTION_NONE) :

			@image html shrinkNone.png

		In the following example forces the shrink in all directions, in this case the text is truncated (@ref GL_DIRECTION_ALL) :

			@image html shrinkAll.png


	<h2>Background expansion</h2>
		
		The background of a widget can be expanded or disagree with the following functions :
			- @ref GL_Widget_SetExpand : Sets the widget expand flag
			- @ref GL_Widget_GetExpand : Gets the widget expand flag

		In the following example the label disables the expansion of its background (@ref GL_DIRECTION_NONE) :
	
			@image html expandNone.png
		
		In the following example the label enables the expansion in width of its background (@ref GL_DIRECTION_WIDTH) :
	
			@image html expandWidth.png
		
		In the following example the label enables the expansion in height of its background (@ref GL_DIRECTION_HEIGHT) :
	
			@image html expandHeight.png
		
		In the following example the label enables the expansion in all direction of its background (@ref GL_DIRECTION_ALL) :
	
			@image html expandAll.png
		

	<h2>Difference between the grow and expand</h2>

		below is a layout with 3 rows and 3 columns. 
		If no constraint is placed on the widgets contained in the layout they are evenly distributed in the center 
		of each layout cells.
		<b>The layout cells are highlighted with orange line.</b>

		@image html layout1.png

		Now we place a constraint on central label allowing the grow only in width (@ref GL_Widget_SetGrow with @ref GL_DIRECTION_WIDTH).
		In this case the cell layout does not grow in height :
		
		@image html layout3.png

		Now we place a constraint on central label allowing the grow only in height (@ref GL_Widget_SetGrow with @ref GL_DIRECTION_HEIGHT).
		In this case the cell layout does not grow in width :
		
		@image html layout4.png

		Now we place a constraint on central label disabling the grow in all direction (@ref GL_Widget_SetGrow with @ref GL_DIRECTION_NONE).
		In this case the cell layout does not grow in all direction :
		
		@image html layout2.png

		In the previous example we have modify only the grow property.

		Now we allow the expand the background of the central widget in the width only (@ref GL_Widget_SetExpand with @ref GL_DIRECTION_WIDTH).
		The layout cell size is absolutely not modified :

		@image html layout13.png

		Now we allow the expand of the background of the central widget in the height only (@ref GL_Widget_SetExpand with @ref GL_DIRECTION_HEIGHT).
		The layout cell size is absolutely not modified :

		@image html layout12.png

		Now we allow the expand of the background of the central widget in the all direction (@ref GL_Widget_SetExpand with @ref GL_DIRECTION_ALL).
		The layout cell size is absolutely not modified :

		@image html layout11.png

	<h2>Background alignement</h2>

		The alignment of a widget in the cell can be controlled with the following functions:
			- @ref GL_Widget_SetBackAlign : Sets the widget background alignement
			- @ref GL_Widget_GetBackAlign : Gets the widget background alignement

		In the following example no alignment is set, by default the widget is placed in the middle of the cell (@ref GL_ALIGN_CENTER) :

			@image html backAlignCenter.png

		In the following example background left alignment is set (@ref GL_ALIGN_LEFT) :

			@image html backAlignLeft.png

		In the following example background right alignment is set (@ref GL_ALIGN_RIGHT) :

			@image html backAlignRight.png

		In the following example background top alignment is set (@ref GL_ALIGN_TOP) :

			@image html backAlignTop.png

		In the following example background bottom alignment is set (@ref GL_ALIGN_BOTTOM) :

			@image html backAlignBottom.png


	<h2>Foregound alignement</h2>

		The alignment of the contents of a widget can be controlled by the following functions :
			- @ref GL_Widget_SetForeAlign : Sets the widget foreground alignement
			- @ref GL_Widget_GetForeAlign : Gets the widget foreground alignement

		In the example below the widget has been expanded to the whole cell, default content is placed in the middle (@ref GL_ALIGN_CENTER) :

			@image html foreAlignCenter.png

		In the following example foreground left alignment is set (@ref GL_ALIGN_LEFT) :

			@image html foreAlignLeft.png

		In the following example foreground right alignment is set (@ref GL_ALIGN_RIGHT) :

			@image html foreAlignRight.png

		In the following example foreground top alignment is set (@ref GL_ALIGN_TOP) :

			@image html foreAlignTop.png

		In the following example foreground bottom alignment is set (@ref GL_ALIGN_BOTTOM) :

			@image html foreAlignBottom.png


	<h2>Margins</h2>

		The margin clears an area around an element (outside the border). The margin does not have a background color, and is completely transparent.

		The margin of a widget can be controlled by the following functions :
			- @ref GL_Widget_SetMargins : Sets the widget margins
			- @ref GL_Widget_GetMargins : Gets the widget margins

		In the following example margin left is defined :

			@image html marginLeft.png

		In the following example margin right is defined :

			@image html marginRight.png

		In the following example margin top is defined :

			@image html marginTop.png

		In the following example margin bottom is defined :

			@image html marginBottom.png


<hr>@section GL_Widget_RangeProperties Range

		The range is used by the widgets scrollbar, progressbar. 
		It defines the minimum and maximum limits of the widget, the current value and size of the current page

		The range of a widget can be controlled by the following functions :
			- @ref GL_Widget_SetMin : Sets the minimum limit 
			- @ref GL_Widget_GetMin : Gets the minimum limit 
			- @ref GL_Widget_SetMax : Sets the maximum limit 
			- @ref GL_Widget_GetMax : Gets the maximum limit 
			- @ref GL_Widget_SetValue : Sets the value 
			- @ref GL_Widget_GetValue : Gets the value 
			- @ref GL_Widget_SetPage : Sets the page size
			- @ref GL_Widget_GetPage : Gets the page size
			- @ref GL_Widget_SetStep : Sets the step increment
			- @ref GL_Widget_GetStep : Gets the step increment

		The relationship between a document length, the range of values used in a scroll bar, 
		and the page is simple in many common situations. 
		The scroll bar's range of values is determined by subtracting a chosen page from some value 
		representing the length of the document. In such cases, the following equation is useful:
			document length = maximum() - minimum() + pageStep().


<hr>@section GL_Widget_IdProperties Identifier

	The identifier as a unique identifier to an widget. It allows to find a particular widget in a window.

	WARNING: some identifier are reserved because they are used in skins, 
	therefore you must avoid to define identifier between @ref GL_ID_SKIN_START and @ref GL_ID_SKIN_STOP

	The identifier of a widget can be controlled by the following functions :
		- @ref GL_Widget_SetId : Sets the widget identifier
		- @ref GL_Widget_GetId : Gets the widget identifier
		- @ref GL_Widget_SearchId : Search a widget based on its id


<hr>@section GL_Widget_ByIdProperties By Id

	The identifier is looked up in the children of the current widget, and when he found the treatment is then performed.
	
	This section presents the functions allows access to a widget based on its identifier :
		- @ref GL_Widget_SetTextById : Changes the text of the widget @ref GL_Widget_FormatProperties
		- @ref GL_Widget_GetTextById : Return the text of the widget
		- @ref GL_Widget_SetSourceById : Changes the image source of the widget @ref GL_Widget_Url
		- @ref GL_Widget_GetSourceById : Return the image source of the widget @ref GL_Widget_Url
		- @ref GL_Widget_SetMaskById : Sets the input mask 
		- @ref GL_Widget_SetUserDataById : Sets the contents of the user data attached to a widget
		- @ref GL_Widget_GetUserDataById : Sets the contents of the user data attached to a widget
		- @ref GL_Message_GetWidgetById : Gets a widget in a window associated to the message according to an id 

<hr>@section GL_Widget_FormatProperties Format

	The string can optionally contain embedded format tags that are substituted by the values specified in subsequent argument(s) 
	and formatted as requested.
	The number of arguments following the format parameters should at least be as much as the number of format tags.
	The format tags follow this prototype:

	<b>%[flags][width][.precision][length]specifier</b>

	Where specifier is the most significant one and defines the type and the interpretation of the value of the coresponding argument:

	<b>specifier</b>

		- <b>c</b> Character
		- <b>d</b> or <b>i</b> Signed decimal integer
		- <b>o</b> Unsigned octal
		- <b>s</b> String of characters
		- <b>u</b> Unsigned decimal integer
		- <b>x</b> Unsigned hexadecimal integer
		- <b>X</b> Unsigned hexadecimal integer (capital letters)
		- <b>b</b> Unsigned binary integer
		- <b>B</b> Unsigned binary integer
		- <b>p</b> Pointer address
		- <b>%</b> A % followed by another % character will write % to text.

	The tag can also contain flags, width, .precision and modifiers sub-specifiers, which are optional and follow these specifications:

	<b>flags</b>

		- <b>-</b> Left-justify within the given field width; Right justification is the default (see width sub-specifier).
		- <b>+</b> Forces to precede the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a - sign.
		- <b>(space)</b> If no sign is going to be written, a blank space is inserted before the value.
		- <b>0</b> Left-pads the number with zeroes (0) instead of spaces, where padding is specified (see width sub-specifier).

	<b>width</b>
		- <b>(number)</b> Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger.
		- <b>*</b> The width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.

	<b>.precision</b>
		- <b>.number</b> : For integer specifiers (d, i, o, u, b, B, x, X): precision specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A precision of 0 means that no character is written for the value 0.
		- For s this is the maximum number of characters to be printed. By default all characters are printed until the ending null character is encountered.
		- For c type: it has no effect.
		- When no precision is specified, the default is 1. If the period is specified without an explicit value for precision, 0 is assumed.
		- <b>.*</b>	The precision is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.

	<b>length</b>
		- <b>h</b> The argument is interpreted as a short int or unsigned short int (only applies to integer specifiers: i, d, o, u, b, B, x and X).
		- <b>l</b> The argument is interpreted as a long int or unsigned long int for integer specifiers (i, d, o, u, b, B, x and X), and as a wide character or wide character string for specifiers c and s.

<hr>@section GL_Widget_AppearanceProperties Appearance

	The appearance of a widget can be controlled by the following functions :
		- @ref GL_Widget_SetBackColor : Sets the widget background color
		- @ref GL_Widget_GetBackColor : Gets the widget background color
		- @ref GL_Widget_SetForeColor : Sets the widget foreground color
		- @ref GL_Widget_GetForeColor : Gets the widget foreground color
		- @ref GL_Widget_SetVisible : Sets the visible state
		- @ref GL_Widget_GetVisible : Gets the visible state


<hr>@section GL_Widget_ClickProperties Click

	The "click sensitive" can make a widget sensitive to click.
	The "clickable" allowing a widget to generate a click event (@ref GL_EVENT_STYLUS_CLICK).

	If you want to get click event on a single widget should position both to true.

	If a widget is composed of several children, place the property click sensitive on each child, 
	and set the property clickable on the top widget.

	the click configuration can be controlled by the following functions :
		- @ref GL_Widget_GetClickable : Indicates that the widget sends a click event
		- @ref GL_Widget_SetClickable : Sets the clickable state (the widget sends a click event)
		- @ref GL_Widget_GetClickSensitive : Sets the click sensitive state (this widget is sensitive pen click)
		- @ref GL_Widget_SetClickSensitive : Indicates that this widget is sensitive pen click

<hr>@section GL_Widget_FocusProperties Focus

	When a widget has focus it indicates that it is usable for editing or validation by the keyboard, 
	generally when a widget has focus its color changes, one widget can have the focus to a window, 
	if you force the focus on a widget, it removes automatically the focus of the widget that had.
	When the focus is positioned on an element it can receive keyboard messages, the focus
	can be controlled by the following functions :
		- @ref GL_Widget_GetFocus : Find the widget with the focus you need to use the function :
		- @ref GL_Widget_SetFocus : Sets the focus state on the widget if the widget is focusable (only a single widget on a window can receive focus) :
		- @ref GL_Widget_GetFocusable : Lets know if the widget can receive focus or not
		- @ref GL_Widget_SetFocusable : Indicates that the widget can receive focus or not


<hr>@section GL_Widget_CheckProperties Check

	This state represents the state of the check for @ref GL_RadioButton or @ref GL_CheckButton.

	The check state can be controlled by the following functions :
		- @ref GL_Widget_SetCheck : Sets the check state 
		- @ref GL_Widget_GetCheck : Gets the check state 
		- @ref GL_Widget_ToggleCheck : Toggle the check state (only used by check button)

<hr>@section GL_Widget_StateMaskProperties State mask

	The following functions are used to define the display behavior of the widget according to these states
	(@ref GL_Widget_FocusProperties, @ref GL_Widget_CheckProperties).


<hr>@section GL_Widget_TextProperties Text

	These properties are used to manage the embedded text into a widget, they include widgets 
	@ref GL_Button, @ref GL_CheckButton, @ref GL_RadioButton, @ref GL_ProgressBar, @ref GL_Icon, @ref GL_Label, @ref GL_Edit ...

	The text properties can be controlled by the following functions :
		- @ref GL_Widget_SetText : Sets the text of the widget @ref GL_Widget_FormatProperties
		- @ref GL_Widget_GetText : Gets the text of the widget
		- @ref GL_Widget_SetFontName : Sets the font name of the widget
		- @ref GL_Widget_GetFontName : Gets the font name of the widget
		- @ref GL_Widget_SetFontSize : Sets the font size of the widget
		- @ref GL_Widget_GetFontSize : Gets the font size of the widget
		- @ref GL_Widget_SetFontStyle : Sets the font style of the widget
		- @ref GL_Widget_GetFontStyle : Gets the font style of the widget
		- @ref GL_Widget_SetTextAlign : Sets the widget text alignement
		- @ref GL_Widget_GetTextAlign : Gets the widget text alignement
		- @ref GL_Widget_SetTextPaddings : Sets the widget text paddings
		- @ref GL_Widget_GetTextPaddings : Gets the widget text paddings

	For information on fonts see @ref GL_Widget_Font


<hr>@section GL_Widget_TextEscapeSequence Escapes sequences
	It offers the abality to add directly in the message text the format of the text.
	This escape can be integrated only in a @ref GL_Label or @ref GL_Print widgets.

	To use an escape sequence must prefix the format character with the escape character.

	Below the list of format :

	- <b>"\x1B*"</b> : toggle the text in bold
	- <b>"\x1B/"</b> : toggle the text in italic
	- <b>"\x1B0"</b> : set the text in xxsmall size
	- <b>"\x1B1"</b> : set the text in xsmall size
	- <b>"\x1B2"</b> : set the text in small size
	- <b>"\x1B3"</b> : set the text in medium size
	- <b>"\x1B4"</b> : set the text in large size
	- <b>"\x1B5"</b> : set the text in xlarge size
	- <b>"\x1B6"</b> : set the text in xxlarge size
	- <b>"\x1B#"</b> : reverse the color of text
	- <b>"\x1B-"</b> : underline the text
	- <b>"\x1B."</b> : restore the default format
	- <b>"\x1B\x??"</b> : set the fore or back color of text, see below the value of colors 

	Back colors table :
	@image html PaletteEscapeSequenceBackColor.png

	Fore colors table :
	@image html PaletteEscapeSequenceForeColor.png

<hr>@section GL_Widget_InputProperties Input

	These properties are used to manage the input into a widget, they include widgets 
	@ref GL_Edit, @ref GL_VirtualKeyboard

	The input properties can be controlled by the following functions :
		- @ref GL_Widget_SetMask : Sets the input mask (@ref GL_Widget_MaskProperties)
		- @ref GL_Widget_GetUserChar : Gets the character user mask (@ref GL_Widget_MaskProperties)
		- @ref GL_Widget_SetUserChar : Sets the character user mask (@ref GL_Widget_MaskProperties)
		- @ref GL_Widget_SetFillChar1 : Sets the default fill character 1
		- @ref GL_Widget_GetFillChar1 : Gets the default fill character 1
		- @ref GL_Widget_SetFillChar2 : Sets the default fill character 2
		- @ref GL_Widget_GetFillChar2 : Gets the default fill character 2
		- @ref GL_Widget_SetPasswordChar : Sets the default password character 
		- @ref GL_Widget_GetPasswordChar : Gets the default password character 
		- @ref GL_Widget_SetMode : Sets the input mode
		- @ref GL_Widget_GetMode : Gets the input mode
		- @ref GL_Widget_SetInput : Sets the input text of the widget 
		- @ref GL_Widget_GetInput : Gets the input text of the widget  
		- @ref GL_Widget_SelectAll : Selects all characters in the widget, the first entry of a character deletes the entire contents of the field


<hr>@section GL_Widget_MaskProperties Mask

	The mask is a string normal, the format characters are always preceded by '/'.
	(the default charset is UTF8, to change the charset use the function @ref GL_GraphicLib_SetCharset), 
	
	<b> WARNING: If the default charset is UTF8 and if you pass a non-UTF8 string all non-utf8 characters are replaced by '?'</b>

	For all the masks follow the fill character is 1 (by default <b>'_'</b>) @ref GL_Widget_SetFillChar1 :
		- <b>/b</b> : accepts a character in binary
		- <b>/o</b> : accepts a character in octal
		- <b>/d</b> : accepts a character in decimal
		- <b>/x</b> : accepts a hexadecimal character
		- <b>/a</b> : accepts an alphanumeric character
		- <b>/c</b> : accepts any character
		- <b>/u</b> : accepts all characters in the range of allowed characters defined by the user (@ref GL_Widget_SetUserChar)

	For all the masks follow the fill character is 2 (by default <b>'0'</b>) @ref GL_Widget_SetFillChar2 :
		- <b>/B</b> : accepts a character in binary
		- <b>/O</b> : accepts a character in octal
		- <b>/D</b> : accepts a character in decimal
		- <b>/X</b> : accepts a hexadecimal character
		- <b>/A</b> : accepts an alphanumeric character
		- <b>/C</b> : accepts any character
		- <b>/U</b> : accepts all characters in the range of allowed characters defined by the user (@ref GL_Widget_SetUserChar)
		- <b>//</b> : accepts the character '/'
	
	The character '|' is the beginning of the user char definition (You can also use the @ref GL_Widget_SetUserChar to define the user character)

	Example of mask :
		- The mask "0x/x/x/x/x" accept strings containing a decimal number coded on 4 digits hex preceded by "0x"
		- The mask "/u/u/u/u|1234" accept strings containing all characters from 1 to 4 (Please note: the character '|' is the beginning of defining the user character, is strictly equivalent to a call of @ref GL_Widget_SetUserChar )
		
	<b>WARNING : 
		If a @ref GL_Widget_SetText was done before it is not taken into account. 
		Always specify the input mask before loading the default content of the field</b>

	The mask properties can be controlled by the following functions :
		- @ref GL_Widget_SetMask : Sets the input mask
		- @ref GL_Widget_SetMaskById : Sets the input mask 


<hr>@section GL_Widget_CallbackProperties Message callback

	Each message received by the widget can be intercepted by registering a callback (type @ref GL_Widget_RegisterCallback)
		using the function @ref T_GL_MESSAGE_CALLBACK.

	The callback propertie can be controlled by the following functions :
		- @ref GL_Widget_RegisterCallback : Adds a callback to a widget of treatment for a given message type
		- @ref GL_Widget_UnregisterCallback : Removes a callback to a widget of treatment for a given message type

	Example of callback processing :
	@code
bool OnOkButtonClicked(T_GL_HMESSAGE message)
{
	GL_Message_SetResult(message, GL_KEY_VALID); // <- Forces the output of the function @ref GL_Window_MainLoop
	return true;
}
	@endcode

	A message processing callback should always return true, if you want to ignore the message processing then you can return false, but only in this case.

	Example of registering callback on a widget message:
@code 
GL_Widget_RegisterCallback(widget, GL_EVENT_STYLUS_CLICK, OnOkButtonClicked);
@endcode

	To manage the execution result of the current window  :
	- @ref GL_Window_SetResult or @ref GL_Message_SetResult : Sets the execution result of the current window. 
	- @ref GL_Window_GetResult or @ref GL_Message_GetResult : Gets the execution result of the current window

	For predefined result value see @ref GL_TypesResults or @ref GL_TypesKeys, the initial default value is set to GL_KEY_NONE.

<hr>@section GL_Widget_CommonMessage Messages

	
	Below is the list of messages sent by the widgets :
	
	All widgets :
		- @ref GL_EVENT_STYLUS_LEAVE : The stylus enters the bounding area of a widget
		- @ref GL_EVENT_STYLUS_ENTER : The stylus leaves the bounding area of a widget
		- @ref GL_EVENT_STYLUS_CLICK : The widget clicked (@ref GL_Message_GetPosition)
		- @ref GL_EVENT_STYLUS_SCROLL : The scrolling request was done by the stylus (stylus down, long stylus move, stylus up) (@ref GL_Message_GetMove, @ref GL_Message_GetPosition)
		- @ref GL_EVENT_STYLUS_MOVE : The stylus moved on the screen (@ref GL_Message_GetPosition)
		- @ref GL_EVENT_STYLUS_DOWN : The stylus pressed on the screen (@ref GL_Message_GetPosition)
		- @ref GL_EVENT_STYLUS_UP : The stylus removed from the screen (@ref GL_Message_GetPosition)
		- @ref GL_EVENT_KEY_DOWN : The key pressed on keyboard (@ref GL_Message_GetKey)
		- @ref GL_EVENT_KEY_UP : The key released on keyboard (@ref GL_Message_GetKey)

	All widgets focusable :
		- @ref GL_EVENT_FOCUS : The widget received focus
		- @ref GL_EVENT_UNFOCUS : The widget lost focus
		- @ref GL_EVENT_FOCUS_KEY : The change in focus is due to key pressed (used to move the scrolled view to the widget focused)

	@ref GL_WindowDoc :
		- @ref GL_EVENT_WINDOW_LEAVE : The stylus enters the bounding area of a window
		- @ref GL_EVENT_WINDOW_ENTER : The stylus leaves the bounding area of a window
		- @ref GL_EVENT_INACTIVITY : No user action detected for the specified time,
			configured by the function @ref GL_Window_SetInactivityDuration (for dialog box see the result @ref GL_RESULT_INACTIVITY)
		- @ref GL_EVENT_PAINT : The window must be repaint (@ref GL_Message_GetSize, @ref GL_Message_GetPosition)
		- @ref GL_EVENT_ORIENTATION_CHANGE : The screen orientation has changed (@ref GL_Message_GetScreenOrientation)

	@ref GL_TimerDoc :
		- @ref GL_EVENT_TIMER_OUT : The timer is out (@ref GL_Message_GetTimer)

	@ref GL_RadioButtonDoc and @ref GL_CheckButtonDoc
		- @ref GL_EVENT_CHECKED : The widget is checked
		- @ref GL_EVENT_UNCHECKED : The widget is unchecked

	@ref GL_ScrollViewDoc :
		- @ref GL_EVENT_VERTICAL_SCROLL : The view or scrollbar moved vertically (@ref GL_Message_GetRange)
		- @ref GL_EVENT_HORIZONTAL_SCROLL : The view or scrollbar moved horizontally (@ref GL_Message_GetRange)

	@ref GL_VScrollBarDoc :
		- @ref GL_EVENT_VERTICAL_SCROLL : The view or scrollbar moved vertically (@ref GL_Message_GetRange)
	
	@ref GL_HScrollBarDoc and @ref GL_HSliderDoc :
		- @ref GL_EVENT_HORIZONTAL_SCROLL : The view or scrollbar moved horizontally (@ref GL_Message_GetRange)

	@ref GL_VirtualKeyboardDoc :
		- @ref GL_EVENT_VALID : The button valid (green) clicked on virtual keyboard (@ref GL_Message_GetPosition)
		- @ref GL_EVENT_CANCEL : The button cancel (red) clicked on virtual keyboard (@ref GL_Message_GetPosition)

	@ref GL_EditDoc :
		- @ref GL_EVENT_TEXT_CHANGED : The text in the input field has changed

	@ref GL_UserControlDoc
		- @ref GL_EVENT_DATA : The message contains data attached (@ref GL_Message_GetData, @ref GL_Message_SetData)

	@ref GL_MediaDoc and @ref GL_PictureDoc
		- @ref GL_EVENT_MEDIA_ENDED : The video, audio or animated image ended (no data attached to this message)

	The following functions allows the application to create its own message, they are mainly used by the @ref GL_UserControlDoc :
		- @ref GL_Message_Create : Create the message
		- @ref GL_Message_Destroy : Releases a message and free its associated memory (should never be used)
		- @ref GL_Message_SetPosition : Sets the position of stylus in case of STYLUS message
		- @ref GL_Message_SetMove : Sets the move of stylus in case of STYLUS message
		- @ref GL_Message_SetKey : Sets the key code in case of KEY message
		- @ref GL_Message_SetRange : Sets the range 
		- @ref GL_Message_SetData : Sets the data attached to this message
		- @ref GL_Message_GetData : Gets the data attached to this message

	For more details on the operation on messages see @ref GL_MessageDoc

<hr>@section GL_Widget_ShortcutProperties Shortcut

	This property allows you to add a keyboard shortcut. 
	When the hotkey is registered, if you press the key that causes a click event on the widget.

	The shortcut propertie can be controlled by the following functions :
		- @ref GL_Widget_SetShortcut : Adds a keyboard shortcut to a widget
		- @ref GL_Widget_GetShortcut : Gets the keyboard shortcut attached to widget


<hr>@section GL_Widget_ImagesProperties Image

	This propertie is used to manage the embedded image into a widget, they include widgets 
	@ref GL_Icon, @ref GL_IconButton, @ref GL_Picture.

	The text properties can be controlled by the following functions :
		- @ref GL_Widget_SetSource : Sets the image source of the widget @ref GL_Widget_Url
		- @ref GL_Widget_GetSource : Gets the image source of the widget @ref GL_Widget_Url

	For supported image formats see @ref GL_Widget_Image

<hr>@section GL_Widget_ImagesTransformationProperties Image transformation

	This propertie is used to resize the embedded image into a widget, they include widgets 
	@ref GL_Icon, @ref GL_IconButton, @ref GL_Picture.
		- @ref GL_Widget_SetTransformation : Sets the image transformation
		- @ref GL_Widget_GetTransformation : Gets the image transformation

	Image transformations @ref T_GL_TRANSFORMATION :

	@ref GL_TRANSFORMATION_NONE : No treatment of the image, if the image is too large it will be truncated, if it is too small it will be displayed as it is :
	@image html transformnone.png

	@ref GL_TRANSFORMATION_REPEAT_X : The image is repeated on the x-axis
	@image html repeatx.png

	@ref GL_TRANSFORMATION_REPEAT_Y : The image is repeated on the y-axis
	@image html repeaty.png

	@ref GL_TRANSFORMATION_REPEAT_ALL : The image is repeated on all directions
	@image html repeatall.png

	@ref GL_TRANSFORMATION_STRETCH_X : The image is stretched along the x-axis only
	@image html stretchx.png

	@ref GL_TRANSFORMATION_STRETCH_Y : The image is stretched along the y-axis only
	@image html stretchy.png

	@ref GL_TRANSFORMATION_STRETCH_ALL : The image is stretched along the all directions
	@image html stretchall.png

	@ref GL_TRANSFORMATION_FIT_X : The image will keep its width height ratio, but will be adapted on the X axis, if the image is too high it will be truncated
	@image html fitx1.png
	@image html fitx2.png

	@ref GL_TRANSFORMATION_FIT_Y : The image will keep its width height ratio, but will be adapted on the Y axis, if the image is too large it will be truncated
	@image html fity1.png
	@image html fity2.png

	@ref GL_TRANSFORMATION_FIT_ALL : The image size will be adapted to fit exactly to the space without distortion
	@image html fitall1.png
	@image html fitall2.png
	@image html fitall3.png
	
<hr>@section GL_Widget_Url Url

	This part describes how the URL must be coded in the source.

	The URL is composed with : 
		<b>protocol://drive/path</b>
			- <b>protocol</b>  : set at this position the protocol name 
			- <b>drive</b>     : set at this position the drive
			- <b>path</b>      : set at this position the path with disk

		The <b>protocol</b> can be the following:
			-	<b>file ://</b>: this protocol can read file stored in the terminal file system.
			-	<b>dir ://</b>: this protocol can parse directory stored in the terminal file system.
			-	<b>dal ://</b>: this protocol can parse the data layer content

		The <b>drive</b> can be the following: 
			-	<b>flash/</b>: to get file stored in the flash disk (ie : file://flash/HOST/file.wgu to access file.wgu in host disk)
			-	<b>ram/</b>: to get file stored in the ram disk (ie : file://ram/MYDISK/file.wgu to access file.wgu in ram disk)
			-	<b>param</b> : to get signed file parameter, the '-' character ignore any other characters (ie : file://param/sample----.sgn/file.wgu to load file named samplexxxx, xxxx are untested characters)
			if the VFS file system is included the following path can be specified as : 
			-	<b>rdd</b>: to get file stored in the Vfs RAM disk (ie : file://rdd0a/file.wgu : access file.wgu on the first partition of the first ramdrive)
			-	<b>infd</b>: to get file stored in the Vfs FLASH disk (ie : file://infd0a/file.wgu : access file.wgu on the first partition of the first internal flash drive)
			-	<b>mmcd</b>: to get a file stored on a mmc card (ie : file://mmcd0a/file.wgu : access file.wgu on the first partition of the MMC)
			-	<b>umsd</b>: to get files stored on USB mass storage (ie : file://umsd0a/file.wgu : access file.wgu on the first partition of the first USB) 	Umsd0 and Umsd1 can ben accessed)

		Particular case for the <b>dal ://</b> protocol :
			The url to access the data must be composed as follows : 
				dal://[win32Path]dalName[?appli_type=XXXXX]

				- win32Path : only available with the win32 component, it is composed with the path and file name of TAR or TBR. This part is optional.
				- dalName : name of the identifier of the data dal. This part is mandatory
				- ?appli_type=XXXX : Type application, XXXX must be replaced by the hexadecimal value. This part is optional.

		With the the archive file TAR or Gziped file, you must specified in the path the archive filename and the 
		filename contained in the archive file. 
		
		For example to read "FileInTar.txt" in an "MYARCHIVE.TAR" TAR archive  (use 
		@ref GL_File to read TAR file), you must sets the url :
			- file://flash/HOST/MYARCHIVE.TAR/DirectoryInTar/FileInTar.txt

		You can compress and decompress GZip file, for this you must use the same principle (use 
		@ref GL_File to read or write GZip file), you must sets the url :
			- file://flash/HOST/MYARCHIVE.GZ/FileInGz.txt

		The possible extensions of the archive filename is ".TAR" or ".GZ".
		IMPORTANT : The extension of the archive must be in the url even if the file is signed and takes another extension.

		Only reading a tarball is possible.
		Reading and writing is possible with GZip format, only one file by archive can be compressed in this format.
		With Gzip file the compression is done when the file is closed, 
		the decompression is done when opening the file. 
		So be careful not to compress huge data : it will be temporarily in memory twice.

		Samples url :
			- <b>file://flash/HOST/DEMO.tar/index.wgu</b> : load index.wgu from demo.tar 
				located in HOST disk of the terminal
			- <b>file://param/DEMO.tar/index.wgu</b> : load index.wgu from demo.sgn or pgn stored as signed parameter file
				located in HOST disk of the terminal


<hr>@section GL_Widget_UserDataProperties User data

	It is used to attach data to a widget, such data are absolutely not used by the graphic library, they are just for the user application.
	Its format is free, you can put a string, a buffer given or a handle to object, simply specify its size.

	The text properties can be controlled by the following functions :
		- @ref GL_Widget_SetUserData : Sets the contents of the user data attached to a widget
		- @ref GL_Widget_GetUserData : Gets the contents of the user data attached to a widget
		- @ref GL_Widget_SetUserDataById : Sets the contents of the user data attached to a widget
		- @ref GL_Widget_GetUserDataById : Sets the contents of the user data attached to a widget
		- @ref GL_Message_SetUserData : Sets the contents of the user data attached to a window (to be used in a callback message processing)
		- @ref GL_Message_GetUserData : Gets the contents of the user data attached to a window (to be used in a callback message processing)

	To attach data (In this case the contents of the structure is copied into the widget) :
@code
	struct MyData data;
	GL_Widget_SetUserData(window, &data, sizeof(data));
@endcode

	To get attached data in a callback treatement message :
@code
	struct MyData data;
	GL_Message_GetUserData(message, &data, sizeof(data));
@endcode

	To get the attached data in your widget :
@code
	struct MyData data;
	GL_Widget_GetUserData(window, &data, sizeof(data));
@endcode

	If you change the contents you must replace the data modified in the widget with @ref GL_Widget_GetUserData.


	To attach pointer to data :
@code
	struct MyData data;
	struct MyData * ptrData = &data; // <- It is important to go through an intermediate variable, else it does not work

	GL_Widget_SetUserData(window, &ptrData, sizeof(ptrData));
@endcode

	To get pointer attached in a callback treatement message :
@code
	struct MyData * ptrData;
	GL_Message_GetUserData(message, &ptrData, sizeof(ptrData));
@endcode

	To get pointer attached in your widget :
@code
	struct MyData * ptrData;
	GL_Widget_GetUserData(window, &ptrData, sizeof(ptrData));
@endcode

<hr>@section GL_Widget_Font Fonts

	All fonts files are dynamically loaded at the startup of the GOAL Engine.
	
	<h3>Font file</h3>

		A font file contains many font size and font weight for only one family. The family name defined are :
		-	"sans-serif" : sans serif font
		-	"serif" : serif font
		-	"monospace" : monospace font
		-	"cursive" : cursive font
		-	"fantasy" : fantasy font

		The only font comes standard is "GOAL" with only one family "sans-serif" in normal weight.

	<h3>Font name selection</h3>
		Font selection can be done by pass the name of the font or the name of the family.
		
		@code
		GL_Widget_SetFontName(handle, "GOAL");
		@endcode
		
		The font with name "GOAL" will be selected.
		
		It is also possible to send several information to select the font. Each of these information must be separated by a comma.

		@code
		GL_Widget_SetFontName(handle, "GOAL,ARIAL,sans-serif");
		@endcode
		
		The font with name "GOAL" will be selected primarily, 
		if this font not exists the font with name "ARIAL" will be selected,
		if this font not exists the first sans-serif font will be selected.

	<h3>Font size selection</h3>
		To select a font size, you have two options available :
			- Select by size using @ref GL_Widget_SetFontSize
			- Size selection depending on the size of the screen @ref GL_Widget_SetFontScale

		With @ref GL_Widget_SetFontSize you must place in the height the size existing in the font file.
		If the size not available the closest size will be selected.

		With @ref GL_Widget_SetFontScale you must specify a size between 5 values ​​(extra large, large, medium, small, extra small),
		the best size is chosen according to the screen resolution. 
		- A medium size displays 20 characters in screen width.
		- A large size displays 16 characters in screen width.
		This solution is preferred if your application must run on different screen size.

	<h3>Font style selection</h3>
		To select the style of the font you would use: @ref GL_Widget_SetFontStyle.

		The style existing are :
			- Normal
			- Italic
			- Bold
			- Bold italic

		The fonts delivered are in the normal style.

	<h3>Font file creation</h3>

		To create new font files, please read the "TELIUM FON tool user guide rev D.pdf".

		The GOAL Engine automatically retrieves all font files loaded in the terminal. The font file name must respect the next pattern :

		@image html fontDescriptor.png
		
		The family name must be in next list (respect the case and _):
			- <b>SansSerif</b>  : sans-serif family
			- <b>Serif____</b>  : serif family
			- <b>Monospace</b> : monospace family
			- <b>Fantasy__</b> : fantasy family
			- <b>Cursive__</b> : cursive family
			
		The weight must be in next list (respect the case):
			- <b>No</b> : Normal
			- <b>Bo</b> : Bold
			- <b>It</b> : Italic
			- <b>BI</b> : Bold Italic

		The size is in point and must be a number between 0 to 99, all size smaller than 10 must be prefixed with "0".
		
	<h3>Font file generation sample</h3>
		The next lines presents a sample to generate the font = "ARIAL", family = "Serif____", in 4 sizes (8, 10, 13, 17 points) in normal weight : 
		
		@code
		rem Convert true type file into BDF file 
		rem The 72 dpi resolution (-r 72) is 1 point = 1 pixel
		ttf2bdf -p 8  -r 72 -l '0_255' arial.ttf> Serif____No08.bdf
		ttf2bdf -p 10 -r 72 -l '0_255' arial.ttf> Serif____No10.bdf
		ttf2bdf -p 13 -r 72 -l '0_255' arial.ttf> Serif____No13.bdf
		ttf2bdf -p 17 -r 72 -l '0_255' arial.ttf> Serif____No17.bdf

		rem Convert BDF to font telium file
		bdf2fon -c -d0 -fSerif____No08.bdf -sSerif____No08 ARIAL.FON
		bdf2fon    -d0 -fSerif____No10.bdf -sSerif____No10 ARIAL.FON
		bdf2fon    -d0 -fSerif____No13.bdf -sSerif____No13 ARIAL.FON
		bdf2fon    -d0 -fSerif____No17.bdf -sSerif____No17 ARIAL.FON

		rem Convert BDF to bitmap
		bdf2bmp Serif____No08.bdf Serif____No08.bmp
		bdf2bmp Serif____No10.bdf Serif____No10.bmp
		bdf2bmp Serif____No13.bdf Serif____No13.bmp
		bdf2bmp Serif____No17.bdf Serif____No17.bmp
		@endcode

	To function on every device the font files must be generated in several heights. 
	
	Please note the sizes below 9 gives a bad result with true type fonts, you will then use the raster fonts.
	
	<h3>Font generator</h3>
		Goal comes with the tool "FontGenerator.exe", it simplifies the creation of font by hiding many MSDOS commands should be run.
		This tool is located in your SDK in the directory "C:\Program Files\SDK30\SDK X.X.X\Tools\GOAL\FontGenerator".
		
		Run the FontGenerator.exe :
		@image html FonGenerator1.png

		In the "Binary target path" enter the destination directory of the file generated FON.

		In the "Binary name" enter the name of binary FON file, only numbers are allowed to be downloaded by TMS, The last 4 digits are the version and revision of the FON file

		In the "Font name" enter the name, this name will be used with the function @ref GL_Widget_SetFontName to select this font.
		The name "GOAL" is reserved and you do not use.

		To add a font click on add button.

		@image html FonGenerator2.png

		In the "Font filename" select the True Type filename of the font. Bdf font file and Otf are accepted.

		Selects the family, the weight.

		Selects the charset, only characters contained in the charset given will be added.

		Selects the writing direction with direction field.

		If your file contains a font TTF bitmap (not vector), you must check the box "Bitmap font", and specify the pixel size of the font.

		Min size, max size, step size allows you to create multiple font sizes, the size commonly used by GOAL are (10, 12, 16, 19, 24, 30, 39, 50, 64).
		Please note sizes below 12 with TTF files produce ugly results. 
		You must edit with ingedev the BDF files generated and then re-add into the BDF format.

		The ratio allows the characters to be larger (> 1.0) or higher (<1.0).

		When you have added all the fonts you want, save the project (avoid directory names and file with spaces).
		To start font generation press F5 key.

		The generated files are placed in a subdirectory where are located the project file.

		- MYFONT.log file contains the result of commands executed.
		- MYFONT.bat file contains all commands executed, you can run another time this command if you want.
		- MYFONT directory contains all BDF file generated from TTF file and the bitmap of all characters.

		"MYFONT" is the font name you chose for your font.

		Watch the bitmaps and check that all the characters are legible.
		If some characters are not legible, you must edit the BDF file with ingedev, 
		recreate a directory containing these BDF files, modify your font project to take into account the bdf files modified.
		
		Check the FON file size generated. If it is size is too big, you can :
		 - limit the number of characters (with charset).
		 - limit the step of sizes.
		 - reduce the maximal size.
		 - suppress some style.

	<h3>BDF editor</h3>

		If the result of font obtained by FON Generator is not beautiful, it is necessary in this case to 
		copy the BDF files generated by the FON Generator in a different directory, 
		edit the BDF with ingedev or fontForge, modify the project FonPrj to use these new files BDF, and retry
		font generation.

		In some cases ingedev refuses to open a file BDF, in this case you must use fontforge :

		- Fontforge WIN32 : http://www.geocities.jp/meir000/fontforge/   (file : fontforge-cygwin_2011_06_06.zip)
		- Fontforge Linux : http://fontforge.sourceforge.net/

		For use fonteforge in WIN32 you must in this case change the default Japanese language 
		by editing fontforge.bat, change the line "set LANG=".
		
		If you use multiple monitors on your PC, change also the option -nomultimonitors by -multimonitors.

		IMPORTANT : Be careful you do not "Save..." or "Save as..." with fontforge in this case you will lose the entire font file. 
		We must instead use "Generate Fonts ..." and save into BDF format.

		Fontforge is more complex and more powerful than ingedev it is to be used only if necessary.

<hr>@section GL_Widget_Image Images formats
This part describes all images formats supported, and defines the optimized WGU format (@ref GL_WguImage).

<h2>Images formats supported</h2>
	
		- PNG images with alpha chanel
		- GIF images
		- JPEG images 
		- BMP images 
		- WGU images 
			
	<table border=1>
		<tr><th>Format</th><th>Usage</th><th>Bytes per pixel in RAM</th><th>compression</th><th>Animated</th><th>Transparency</th></tr>
		<tr><td>JPEG</td><td>Picture only</td><td>4</td><td>Yes</td><td>No</td><td>No</td></tr>
		<tr><td>PNG</td><td>Picture and drawing</td><td>4</td><td>Yes</td><td>No</td><td>Yes</td></tr>
		<tr><td>BMP</td><td>Picture and drawing</td><td>4</td><td>No</td><td>No</td><td>Yes</td></tr>
		<tr><td>GIF</td><td>Picture and drawing</td><td>4</td><td>Yes</td><td>Yes</td><td>Only one color</td></tr>
		<tr><td>WGU</td><td>Picture and drawing</td><td>1,2,3 or 4</td><td>No</td><td>Yes</td><td>Yes</td></tr>
	</table>
	
	The BMP format supported are :
		- BMP monochrome
		- BMP 8 bits with paletized
		- BMP 24 bits
		- BMP 32 bits with alpha.
	
	BMP format 565, BMP with RLE compression are not supported


<h2>Owner WGU format</h2>
	Why an owner WGU picture format ? 
	
	PNG, JPEG or GIF require a long time to inflate the image, also it reserves for each pixel 4 bytes in RAM. <br>
	GIF animated image is limited to 256 colors and only one color can be used to set the transparency. 
	WGU can be encoded in 1,2,3,4 bytes per pixels with full transparency, no inflate is required the image is directly
	coded in the format usable by GOAL. 
	The animated WGU image is only a concatenation of several WGU images in a single file.
	The WGU images are more faster and smaller in RAM than other images format.


<h2>Dithering tools</h2>
	The tools can be used to generate WGU image, these tools are delivered in SDK :
	- PictureOptimizer.exe : image converter 
	- ImageEnhance.exe : console image converter
	
	These tools can also dithered image. Dithering is a technique used in computer graphics to create the illusion of color depth in images with a limited color palette (color quantization)
	
	Normal image :
	@image html normal.png
	
	The ICT 250 and EFT930 have a color palette limited to 4096 colors, the image display on terminal will be :
	@image html undithered.png
	
	But you can dither image with these tools, and the result on terminal be :
	@image html dithered.png
	
	A detail zoomed of dithered image :
	@image html zoomDithered.png
	
	To convert image into a dithered image use <b>PictureOptimizer.exe</b> application 
	(This tool is located in your SDK directory : "C:\Program Files\SDK30\SDK X.X.X\tools\CGUI\ImageTools").


<h2>Animated image creation</h2>

	This tutorial presents the mean to create an animated image. 
	To create this animation we need the inkscape software to create the image,
	Inkscape is an open source vector graphics editor using the W3C standard Scalable Vector Graphics (SVG) file format. 

	Download the version 0.48 from the http://sourceforge.net/projects/inkscape/files/.

	Now we go to create a sample "hello world" animation, the first slide contents the 
	"Hello" text and the second slide contents "World" text.

	Install inkscape and start it. Open the document properties :
	@image html Tuto1.png

	Change the size of the document (320x240 pixels in this case) :
	@image html Tuto2.png

	Now you have changed the size of the document, you get the small image displayed :
	@image html Tuto3.png

	You can zoom it with the zoom menu, or use the Ctrl+Mouse Wheel to zoom the document :
	@image html Tuto4.png

	Now to create a text in your document, you must clic on text tools :
	@image html Tuto5.png

	Draw the text rectangle :
	@image html Tuto6.png

	Enter the text "Hello" :
	@image html Tuto8.png

	The color is not correct, to change the color select the Fill and Stroke menu :
	@image html Tuto9.png

	In the Fill and Stroke dialog box, set fill color :
	@image html Tuto10.png

	Set the stroke paint to "no paint" :
	@image html Tuto11.png

	Click on text and press the arrow in the corner to resize the text :
	@image html Tuto12.png

	Change the color text to gradiant, clic on the gradiant button :
	@image html Tuto14.png

	Click on edit button to change the gradiant, select the stop with transparency :
	@image html Tuto15.png

	Set the stop to yellow color, suppress the transparency :
	@image html Tuto16.png

	Click on gradiant in tools to change its direction :
	@image html Tuto18.png

	Press the small red circle and move it, the gradiant direction changes :
	@image html Tuto19.png

	We have now the first slide of the animation, to create the next slide we use the layer,
	add new layer in your document :
	@image html Tuto21.png

	Set the layer name, add in brackets the duration in seconds (s) or milliseconds (ms),
	add in brackets the type of undraw method :  
	 - <b>(replace)</b> : replaces the image displayed by the background before displaying the next image (see @ref T_GL_WGU_HEADER)
	 - <b>(combine)</b> : leaves the image displayed before displaying the next image (see @ref T_GL_WGU_HEADER)
	 - <b>(previous)</b> : replaces the previously displayed image before displaying the next image  (see @ref T_GL_WGU_HEADER)

	@image html Tuto22.png

	To view all slides, open the layers dialog box :
	@image html Tuto23.png

	Edit and change the name of the first layer :
	@image html Tuto24.png

	Select all objects displayed in document with Ctrl A. Copy the object selected :
	@image html Tuto25.png

	Change the layer activated :
	@image html Tuto26.png

	Paste the object copied in the selected layer :
	@image html Tuto27.png

	Change the content of text with "World" :
	@image html Tuto28.png

	Select all objects with Ctrl A :
	@image html Tuto29.png

	Open the align and distribute dialog box :
	@image html Tuto30.png

	Set the relative value to "Page", all alignements will be relative to the page :
	@image html Tuto31.png

	Press the "center horizontally" button :
	@image html Tuto32.png

	And press the "center on horizontal axis" button :
	@image html Tuto33.png

	To terminate save this document into the HelloWorld.svg file :
	@image html Tuto34.png


<h2>Image conversion</h2>

	Once you have created the document with all slides, you must now convert this document
	into an animated image. The first thing you must done, is to add the directory of inkscape
	executable into your PATH environment variables.
	
	On your desktop right-click on "My Computer" and choose "Properties". 
	In the box that opens, click the "Advanced" tab to obtain the dialog box shown below. 
	Next, click the button "Environment Variables". 
	@image html Tuto36.png

	Search the variable named "PATH", and double click on it :
	@image html Tuto37.png

	Add the inkscape executable directory in the PATH and click OK :
	@image html Tuto38.png

	Now you can convert the document into an animated image, start the <b>PictureOptimizer.exe</b> application 
	(This tool is located in your SDK directory : "C:\Program Files\SDK30\SDK X.X.X\tools\CGUI\ImageTools").

	@image html Tuto39.png

		- Set the input picture filename to optimize (wildcard mask accepted) into <b>Input picture filename</b>,
			the input image extensions supported are <b>jpg</b> or <b>jpeg</b>, <b>png</b>, <b>bmp</b>, <b>gif</b>, <b>svg</b>(only with inkscape).
		- Set the directory where the optimized pictures will be saved into <b>Output directory</b>
		- Select the output format into <b>Format</b> :
			- <b>wgu</b> : this format is fully optimized for POS, it reduces the memory footprint in ram, improve the display speed, this format is the best format for all pictures types :photo, drawing, logo, animated picture, pictures with transparency.
			- <b>png</b> : Portable Network Graphic format, this format can be used for picture with transparency, photo, drawing and logo.
			- <b>gif</b> : Graphics Interchange Format, this format must be reserved for animated pictures only.
			- <b>bmp</b> : Microsoft Bitmap, this format can be used for photo, drawing. Transparency and animated picture are not supported.
			- <b>jpg</b> : Joint Photographic Experts Group format, this format can be used for photo only. Transparency and the animated picture are not supported.
		- Select the dithering optimizer (for Isc 350 set <b>24 bits per pixel</b>, for Ict 250, Eft930 set <b>16 bits per pixel</b>) :
		   - <b>Black and white</b> : convert into black and white image
		   - <b>Gray</b> : convert into gray scale image
		   - <b>8 bits per pixel</b> : convert in a dithered image with a color palette coded on 8 bits per pixel (poor quality, low memory)
		   - <b>16 bits per pixel</b> : convert in a dithered image with a color palette coded on 16 bits per pixel (this is the best quality with a screen limited to 4096 colors)
		   - <b>24 bits per pixel</b> : convert in a dithered image with a color palette coded on 24 bits per pixel (this is the best quality with a screen limited to 262144 colors)
		   - <b>32 bits per pixel</b> : convert in a dithered image with a color palette coded on 32 bits per pixel (this is the best quality with a screen which support full colors)	
		- Not change the scale, the defaut size has been set in document properties of inkscape document.
		- Press start button

	The image obtained :
	@image html HelloWorld.gif

<h2>Inkscape links</h2>

	Documentation :
		- http://tavmjong.free.fr/INKSCAPE/MANUAL/html
		
	Tutorials :
		- http://screencasters.heathenx.org
		- http://chrisdesign.wordpress.com
		- http://inkscapetutorials.wordpress.com

@}

@addtogroup GL_Widget
@{
*/

/*<DEFINE>
	EnumXml("TELIUMKEY",                     "Telium keys values",
		DefineXml("KEY_0"           ,"\u0030"         ,"Telium numeric 0 key"),
		DefineXml("KEY_1"           ,"\u0031"         ,"Telium numeric 1 key"),
		DefineXml("KEY_2"           ,"\u0032"         ,"Telium numeric 2 key"),
		DefineXml("KEY_3"           ,"\u0033"         ,"Telium numeric 3 key"),
		DefineXml("KEY_4"           ,"\u0034"         ,"Telium numeric 4 key"),
		DefineXml("KEY_5"           ,"\u0035"         ,"Telium numeric 5 key"),
		DefineXml("KEY_6"           ,"\u0036"         ,"Telium numeric 6 key"),
		DefineXml("KEY_7"           ,"\u0037"         ,"Telium numeric 7 key"),
		DefineXml("KEY_8"           ,"\u0038"         ,"Telium numeric 8 key"),
		DefineXml("KEY_9"           ,"\u0039"         ,"Telium numeric 9 key"),
		DefineXml("KEY_DOT"         ,"\u002E"         ,"Telium dot key"),
		DefineXml("KEY_VALID"       ,"\uF850"         ,"Telium green key"),
		DefineXml("KEY_CANCEL"      ,"\uF851"         ,"Telium red key"),
		DefineXml("KEY_CORRECTION"  ,"\uF852"         ,"Telium yellow key"),
		DefineXml("KEY_PAPER"       ,"\uF853"         ,"Telium paper feed key"),
		DefineXml("KEY_F"           ,"\uF854"         ,"Telium function key"),
		DefineXml("KEY_F1"          ,"\uF855"         ,"Telium function 1 key"),
		DefineXml("KEY_F2"          ,"\uF856"         ,"Telium function 2 key"),
		DefineXml("KEY_F3"          ,"\uF857"         ,"Telium function 3 key"),
		DefineXml("KEY_F4"          ,"\uF858"         ,"Telium function 4 key"),
		DefineXml("KEY_UP"          ,"\uF859"         ,"Telium up arrow key"),
		DefineXml("KEY_DOWN"        ,"\uF85A"         ,"Telium down arrow key"),
		DefineXml("KEY_OK"          ,"\uF86B"         ,"Telium ok key"),
		DefineXml("KEY_CLEAR"       ,"\uF86C"         ,"Telium clear key"),
		),
</DEFINE>
<JSON>
	RegExpString("TELIUMKEY", "", ""),
	RegExpString("IDNAMEREF",   "", ""),
</JSON>
<ALL>
	RegExpInt("COLOR", "0x[A-Fa-f0-9]{8}", "(0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)"),
	RegExpString("CHARACTER", "[0-9]+|(\\\\u[A-Fa-f0-9]{4})", "Character definition. This is the unicode key keyboard see GL_KEY_ in the documentation"),
	BaseType("WIDGET","",
</ALL>
<JSON>
		Range("id",                0,0xEFFFFFFF, "Id to identify single and unique widget"),
</JSON>
<XSD>
		RefOne("idname",           "IDNAMEREF",   '''idname must respect the following naming convention: ${widgetMappingsImlRelativePath)#${IdName} where ${widgetMappingsImlRelativePath) is the relative path to the widgetMappings.iml file in the project, and ${IdName} is the widget identifier. The value of ${IdName} must be one of the "idname" attributes declared in the "widgetMappings.iml" file {IdName} must start with alpha character, and then any alphanumeric and '_' are allowed. The string must be unique in a GML file. Example: "../widgetMappings.iml#BUTTON_OK"'''),
</XSD>
<ALL>
		RefOne("item",             "ITEM",       "Location in the layout"),
		RefOne("grow",             "DIRECTION",  "Indicates that the widget can be growed (only in case if it is placed in a layout)"),
		RefOne("shrink",           "DIRECTION",  "Indicates that the widget can be shrunk (only in case if it is placed in a layout)"),
		RefOne("expand",           "DIRECTION",  "Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)"),
		
		RefOne("backalign",        "ALIGN",      "Alignment of the background relative to its parent"),
		RefOne("forealign",        "ALIGN",      "Alignment of the foreground relative to the background"),
		RefOne("textalign",        "ALIGN",      "Alignment of text in the widget"),

		RefOne("margins",          "MARGINS",    "Margins around the widget"),
		RefOne("borders",          "BORDERS",    "Borders around the widget"),
		RefOne("paddings",         "PADDINGS",   "Text paddings in the widget"),
		
		RefOne("backcolor",        "COLOR",      "Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)"),
		RefOne("forecolor",        "COLOR",      "Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)"),

		RefOne("shortcut",         "TELIUMKEY",  "Keyboard shortcut to a widget"),
		
		Bool("visible",                          "Indicates if the object is visible (true) or not (false)"),
		RefOne("state",            "STATE",      "State of the widget has its creation"),
		RefOne("statemask",        "STATE",      "Mask on the state, the widget will be visible only when the state is identical to the mask defined"),
		
		Bool("focusable",                        "Indicates that the widget can receive focus (true/false)"),
		Bool("clickable",                        "Indicates that the widget sends a click event (true/false)"),
		Bool("clicksensitive",                   "Indicates that this widget is sensitive pen click (true/false)"),

		RefOne("position",         "POSITION",   "Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)"),
		RefOne("size",             "SIZE",       "Size of the widget"),
		RefOne("maxsize",          "SIZE",       "Maximal size of the widget"),
		RefOne("minsize",          "SIZE",       "Minimal size of the widget"),
		),

	List("CHILDREN",                                 "Widget children",
		Item("arrowbutton",       "ARROWBUTTON",     "This widget is a button with an arrow"),
		Item("barcode",           "BARCODE",         "This widget is a barcode"),
		Item("button",            "BUTTON",          "The button to command the terminal to perform some action, or to answer a question"),
		Item("checkbutton",       "CHECKBUTTON",     "A check button is an option button that can be switched on (checked) or off (unchecked)"),
		Item("drawing",           "DRAWING",         "the drawing widget is a surface on which the user can draw a graph"),
		Item("edit",              "EDIT",            "The edit widget provides a widget that is used to edit a single line of text."),
		Item("hscrollbar",        "HSCROLLBAR",      "A scroll bar is a control that enables the user to access parts of a document that is larger than the widget used to display it"),
		Item("hslider",           "HSLIDER",         "The slider is the classic widget for controlling a bounded value. It lets the user move a slider handle along groove and translates the handle's position into an integer value within the legal range"),
		Item("include",           "INCLUDE",         'This widget is used include another resource file or use user control.'),
		Item("icon",              "ICON",            "The class icon is equivalent to a button, it allows the display of an image more"),
		Item("iconbutton",        "ICONBUTTON",      "This class is an icon followed by a button"),
		Item("label",             "LABEL",           "This class is used to display text on a line or a multi-line text"),
		Item("layout",            "LAYOUT",          "The layout can be viewed as a table with multiple rows and columns to place widgets"),
		Item("list",              "LIST",            "The list allows the display of all elements of widgets"),
		Item("media",             "MEDIA",           "This class is used to play movie or sound"),
		Item("palette",           "PALETTE",         "A palette is a widget that can display a color palette"),
		Item("picture",           "PICTURE",         "A picture is a widget that can display a fixed image or animated image"),
		Item("plugin",            "PLUGIN",          "The plugin is used to manage a generic DLL plugin"),
		Item("print",             "PRINT",           "This class is used to print text on a line or a multi-line text on the printer"),
		Item("progressbar",       "PROGRESSBAR",     "A progress bar is used to give the user an indication of the progress of an operation "),
		Item("radiobutton",       "RADIOBUTTON",     "A radio button is an option button that can be switched on (checked) or off (unchecked)"),
		Item("scrollview",        "SCROLLVIEW",      "A scroll view is used to display the contents of many children widget within a frame"),
		Item("signature",         "SIGNATURE",       "This class is used to capture a signature"),
		Item("timer",             "TIMER",           "Repetitive timers"),
		Item("virtualkeyboard",   "VIRTUALKEYBOARD", "The virtual keyboard allows easy entry of special characters"),
		Item("vscrollbar",        "VSCROLLBAR",      "A scroll bar is a control that enables the user to access parts of a document that is larger than the widget used to display it"),
		),
</ALL>*/

/** Destroys widget in the graphical client
@param widget the widget handle */
void GL_Widget_Destroy(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Gets the window handle attached to the widget
@param widget widget handle 
@return window handle or null */
T_GL_HWIDGET GL_Widget_GetWindow(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                 WIDGET TYPE                                                    */
/* ************************************************************************************************************** */

/** Type of widget */
typedef enum T_GL_TYPE
{
	GL_TYPE_UNDEFINED = 0,
	GL_TYPE_WIDGET_START = 0x123,
	GL_TYPE_GRAPHIC_LIB,           ///< @see GL_GraphicLib
	GL_TYPE_WINDOW,                ///< @see GL_Window
	GL_TYPE_DIALOG,                ///< @see GL_Dialog
	GL_TYPE_LIST,                  ///< @see GL_List
	GL_TYPE_SKIN,                  ///< @see GL_Skin
	GL_TYPE_TIMER,                 ///< @see GL_Timer
	GL_TYPE_DRAWING,               ///< @see GL_Drawing
	GL_TYPE_VSCROLLBAR,            ///< @see GL_VScrollBar
	GL_TYPE_HSCROLLBAR,            ///< @see GL_HScrollBar
	GL_TYPE_SCROLLVIEW,            ///< @see GL_ScrollView
	GL_TYPE_KEY,                   ///< @see GL_Button
	GL_TYPE_MEDIA,                 ///< @see GL_Media
	GL_TYPE_HSLIDER,               ///< @see GL_HSlider
	GL_TYPE_PLUGIN,                ///< @see GL_Plugin
	GL_TYPE_DOCUMENT,              ///< @see GL_Document
	GL_TYPE_PRINT,                 ///< @see GL_Print
	GL_TYPE_SIGNATURE,             ///< @see GL_Sign
	GL_TYPE_USERCONTROL,           ///< @see GL_UserControl
	/* __NEWTYPE__ */

	// Widget types that can be inserted into a list
	GL_TYPE_ITEM_START = 0x234,

		GL_TYPE_BUTTON,            ///< @see GL_Button
		GL_TYPE_CHECKBUTTON,       ///< @see GL_CheckButton
		GL_TYPE_RADIOBUTTON,       ///< @see GL_RadioButton
		GL_TYPE_LABEL,             ///< @see GL_Label
		GL_TYPE_EDIT,              ///< @see GL_Edit
		GL_TYPE_PROGRESSBAR,       ///< @see GL_ProgressBar
		GL_TYPE_ICON,              ///< @see GL_Icon
		GL_TYPE_LAYOUT,            ///< @see GL_Layout
		GL_TYPE_PALETTE,           ///< @see GL_Palette
		GL_TYPE_PICTURE,           ///< @see GL_Picture
		GL_TYPE_VIRTUALKEYBOARD,   ///< @see GL_VirtualKeyboard
		GL_TYPE_ICONBUTTON,        ///< @see GL_IconButton
		GL_TYPE_BARCODE,           ///< @see GL_Barcode
		GL_TYPE_ARROWBUTTON,       ///< @see GL_Button

	GL_TYPE_ITEM_STOP,


	// INSERT NEW TYPE BEFORE
	GL_TYPE_FIRST_RFU       = GL_TYPE_WIDGET_START + 0x800, 
	GL_TYPE_WIDGET_END = 0xFFF

} T_GL_TYPE;

/** Gets the type of widget
@param widget widget handle 
@return widget type */
T_GL_TYPE GL_Widget_GetType(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                 SIZE                                                           */
/* ************************************************************************************************************** */

/** Undefined dimension. A dimension defined disables the automatic placement in a layout. 
This value set in size or position enables the automatic placement. 
All sizes and position are initialized by default with this value */
#define GL_DIM_UNDEFINED ((T_GL_DIM)(0x3FFF))

/** Minimal dimension */
#define GL_DIM_MIN ((T_GL_DIM)(0))

/** Maximal dimension */
#define GL_DIM_MAX ((T_GL_DIM)(0x3FFE))

/** Gets the widget size.   @ref GL_Widget_GeometryProperties
@param widget widget handle 
@return size */
T_GL_SIZE GL_Widget_GetSize(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the widget size in the window. If the widget is in a layout, these values are ignored. @ref GL_Widget_GeometryProperties
@param widget widget handle 
@param width new width coded according to the chosen unit
@param height new height coded according to the chosen unit 
@param unit unit of size */
void GL_Widget_SetSize(T_GL_HWIDGET widget, T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit) GL_EXCEPTION;

/** Gets the widget minimum size.  @ref GL_Widget_LayoutProperties.
The value is ignored if a size has been defined. It is useful to control the stretching of the widgets in the layout.
@param widget widget handle 
@return size */
T_GL_SIZE GL_Widget_GetMinSize(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the minimum widget size in the window.  @ref GL_Widget_LayoutProperties
The value is ignored if a size has been defined. It is useful to control the stretching of the widgets in the layout.
@param widget widget handle 
@param width new width coded according to the chosen unit
@param height new height coded according to the chosen unit 
@param unit unit size */
void GL_Widget_SetMinSize(T_GL_HWIDGET widget, T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit) GL_EXCEPTION;

/** Gets the widget maximum size.  @ref GL_Widget_LayoutProperties
The value is ignored if a size has been defined. It is useful to control the stretching of the widgets in the layout.
@param widget widget handle 
@return size */
T_GL_SIZE GL_Widget_GetMaxSize(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the maximum widget size in the window.  @ref GL_Widget_LayoutProperties
The value is ignored if a size has been defined. It is useful to control the stretching of the widgets in the layout.
@param widget widget handle 
@param width new width coded according to the chosen unit
@param height new height coded according to the chosen unit
@param unit unit size */
void GL_Widget_SetMaxSize(T_GL_HWIDGET widget, T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                 POSITION                                                       */
/* ************************************************************************************************************** */

/** Defines a widget position. This value allows for absolute positioning on the window. @ref GL_Widget_GeometryProperties
When the position is set on a widget contained in a layout, the automatique placement is suspended
@param widget widget handle 
@return position datas */
T_GL_POSITION GL_Widget_GetPosition(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Defines a widget position in the window. If the widget is in a layout, these values are ignored. @ref GL_Widget_GeometryProperties
This value allows for absolute positioning on the window.
When the position is set on a widget contained in a layout, the automatique placement is suspended.
@param widget widget handle 
@param x new X coordinates coded according to the chosen unit 
@param y new Y coordinates coded according to the chosen unit 
@param unit unit position*/
void GL_Widget_SetPosition(T_GL_HWIDGET widget, T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                 VISIBLE                                                        */
/* ************************************************************************************************************** */

/** Indicates if the widget is visible @ref GL_Widget_AppearanceProperties
@param widget widget handle 
@return the visible state*/
bool GL_Widget_GetVisible(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Indicates if the widget is visible @ref GL_Widget_AppearanceProperties
@param widget widget handle 
@param visible the visible state */
void GL_Widget_SetVisible(T_GL_HWIDGET widget, bool visible) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                 LAYOUT ITEM                                                    */
/* ************************************************************************************************************** */

/*<ALL>
	Struct("ITEM",                               "Unit used by the coordinates or sizes",
		Integer("column",                        "Column number in the layout (first row = 0) "),
		Integer("row",                           "Row number in the layout (first column = 0)"),
		),
</ALL>*/
/** Item in layout */
typedef struct T_GL_ITEM
{
	/** Row number in layout (first row = 0) */
	T_GL_DIM row;

	/** Column number in layout (first column = 0) */
	T_GL_DIM column;
}T_GL_ITEM;

/** Undefined position in layout */
#define GL_ITEM_UNDEFINED ((T_GL_DIM)(-1))

/** Item handle in layout (see special values @ref GL_ITEM_UNDEFINED) */
typedef T_GL_ITEM * T_GL_HITEM;

/** Gets the widget item location in the layout.  @ref GL_Widget_LayoutProperties
@param widget widget handle 
@return the item */
T_GL_ITEM GL_Widget_GetItem(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets a widget location in the layout. If the widget is not in a layout, these values are ignored.  @ref GL_Widget_LayoutProperties
@param widget widget handle 
@param column the column id (the first column id is 0)
@param row the row id (the first row id is 0)*/
void GL_Widget_SetItem(T_GL_HWIDGET widget, T_GL_DIM column, T_GL_DIM row) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                 ALIGN                                                          */
/* ************************************************************************************************************** */

/*<ALL>
	Enum("ALIGN",                                "Item alignement",
		Define("center",           "0",          "The item is placed in the center"),
		Define("top",              "4",          "The item is placed in vertical on the top"),
		Define("bottom",           "8",          "The item is placed in vertical on the bottom"),
		Define("left",             "1",          "The item is placed in horizontal on the left"),
		Define("right",            "2",          "The item is placed in horizontal on the right"),
		Define("top,left",         "5",          "The item is placed in the top left corner"),
		Define("top,right",        "6",          "The item is placed in the top right corner"),
		Define("bottom,left",      "9",          "The item is placed in the bottom left corner"),
		Define("bottom,right",     "10",         "The item is placed in the bottom right corner"),
		),
</ALL>*/

/** Alignement */
typedef enum T_GL_ALIGN
{
	GL_ALIGN_CENTER        = 0x00, ///< the item is placed in the center
	GL_ALIGN_LEFT          = 0x01, ///< the item is placed in horizontal on the left
	GL_ALIGN_RIGHT         = 0x02, ///< the item is placed in horizontal on the right
	GL_ALIGN_TOP           = 0x04, ///< the item is placed in vertical on the top
	GL_ALIGN_BOTTOM        = 0x08, ///< the item is placed in vertical on the bottom

	GL_ALIGN_TOP_LEFT      = GL_ALIGN_TOP    | GL_ALIGN_LEFT,   ///< the item is placed on the top left corner
	GL_ALIGN_TOP_RIGHT     = GL_ALIGN_TOP    | GL_ALIGN_RIGHT,  ///< the item is placed on the top right corner

	GL_ALIGN_BOTTOM_LEFT   = GL_ALIGN_BOTTOM | GL_ALIGN_LEFT,   ///< the item is placed on the bottom left corner
	GL_ALIGN_BOTTOM_RIGHT  = GL_ALIGN_BOTTOM | GL_ALIGN_RIGHT,  ///< the item is placed on the bottom right corner

	GL_ALIGN_HORIZONTAL    = GL_ALIGN_LEFT   | GL_ALIGN_RIGHT,  ///< Horizontal alignement mask
	GL_ALIGN_VERTICAL      = GL_ALIGN_TOP    | GL_ALIGN_BOTTOM  ///< Vertical alignement mask
} T_GL_ALIGN;

/** Gets the widget background alignement @ref GL_Widget_LayoutProperties
@param widget widget handle 
@return the alignement */
T_GL_ALIGN GL_Widget_GetBackAlign(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the widget background alignement @ref GL_Widget_LayoutProperties
@param widget widget handle 
@param align the alignement */
void GL_Widget_SetBackAlign(T_GL_HWIDGET widget, T_GL_ALIGN align) GL_EXCEPTION;

/** Gets the widget foreground alignement @ref GL_Widget_LayoutProperties
@param widget widget handle 
@return the alignement */
T_GL_ALIGN GL_Widget_GetForeAlign(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the widget foreground alignement @ref GL_Widget_LayoutProperties
@param widget widget handle 
@param align the alignement */
void GL_Widget_SetForeAlign(T_GL_HWIDGET widget, T_GL_ALIGN align) GL_EXCEPTION;



/* ************************************************************************************************************** */
/*                                                 MARGIN                                                         */
/* ************************************************************************************************************** */

/** Sets the widget margins  @ref GL_Widget_LayoutProperties
@param widget widget handle 
@param left left margin coded according to the chosen unit
@param top top margin coded according to the chosen unit
@param right right margin coded according to the chosen unit
@param bottom bottom margin coded according to the chosen unit
@param unit unit margins*/
void GL_Widget_SetMargins(T_GL_HWIDGET widget, T_GL_DIM left, T_GL_DIM top, T_GL_DIM right, T_GL_DIM bottom, T_GL_UNIT unit) GL_EXCEPTION;

/** Gets the widget margins @ref GL_Widget_LayoutProperties
@param widget widget handle 
@return margins */
T_GL_MARGINS GL_Widget_GetMargins(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** 
                                                    TRANSFORMATION
   ************************************************************************************************************** */

/*<ALL>
	Enum("TRANSFORMATION",             "Image transformation",
		Define("none",                "0",  "No treatment of the image : if the image is too large it will be truncated, if it is too small it will be displayed as it is"),
		Define("repeatx",             "1",  "The image is repeated on the x-axis"),
		Define("repeaty",             "2",  "The image is repeated on the y-axis"),
		Define("repeatall",           "3",  "The image is repeated on all directions"),
		Define("stretchx",            "4",  "The image is stretched along the x-axis only"),
		Define("stretchy",            "5",  "The image is stretched along the y-axis only"),
		Define("stretchall",          "6",  "The image is stretched along the all directions"),
		Define("fitx",                "7",  "The image will keep its width height ratio, but will be adapted on the X axis, if the image is too high it will be truncated"),
		Define("fity",                "8",  "The image will keep its width height ratio, but will be adapted on the Y axis, if the image is too large it will be truncated"),
		Define("fitall",              "9",  "The image size will be adapted to fit exactly to the space without distortion"),
		Define("repeatxstretchy",     "10", "The image is repeated on the x-axis and stretched along the y-axis"),
		Define("repeatystretchx",     "11", "The image is repeated on the y-axis and stretched along the x-axis"),
		),    
</ALL>*/

/** Image transformation */
typedef enum T_GL_TRANSFORMATION
{
	GL_TRANSFORMATION_NONE,               ///< No treatment of the image : if the image is too large it will be truncated, if it is too small it will be displayed as it is
	GL_TRANSFORMATION_REPEAT_X,           ///< The image is repeated on the x-axis
	GL_TRANSFORMATION_REPEAT_Y,           ///< The image is repeated on the y-axis
	GL_TRANSFORMATION_REPEAT_ALL,         ///< The image is repeated on all directions
	GL_TRANSFORMATION_STRETCH_X,          ///< The image is stretched along the x-axis only
	GL_TRANSFORMATION_STRETCH_Y,          ///< The image is stretched along the y-axis only
	GL_TRANSFORMATION_STRETCH_ALL,        ///< The image is stretched along the all directions
	GL_TRANSFORMATION_FIT_X,              ///< The image will keep its width height ratio, but will be adapted on the X axis, if the image is too high it will be truncated
	GL_TRANSFORMATION_FIT_Y,              ///< The image will keep its width height ratio, but will be adapted on the Y axis, if the image is too large it will be truncated
	GL_TRANSFORMATION_FIT_ALL,            ///< The image size will be adapted to fit exactly to the space without distortion
	GL_TRANSFORMATION_REPEAT_X_STRETCH_Y, ///< The image is repeated on the x-axis and stretched along the y-axis
	GL_TRANSFORMATION_REPEAT_Y_STRETCH_X, ///< The image is repeated on the y-axis and stretched along the x-axis

	GL_TRANSFORMATION_LAST
} T_GL_TRANSFORMATION;

/** Gets the image transformation @ref GL_Widget_ImagesTransformationProperties
@param widget widget handle 
@return the image transformation */
T_GL_TRANSFORMATION GL_Widget_GetTransformation(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the image transformation @ref GL_Widget_ImagesTransformationProperties
@param widget widget handle 
@param transformation the image transformation */
void GL_Widget_SetTransformation(T_GL_HWIDGET widget, T_GL_TRANSFORMATION transformation) GL_EXCEPTION;



/* ************************************************************************************************************** 
                                                    RANGE
   ************************************************************************************************************** */

/** Gets the minimum limit of the bar (scrollbar, progressbar) @ref GL_Widget_RangeProperties
@param widget widget handle
@return minimum limit */
T_GL_COORD GL_Widget_GetMin(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the minimum limit of the bar (scrollbar, progressbar) @ref GL_Widget_RangeProperties
@param widget widget handle
@param min minimum limit */
void GL_Widget_SetMin(T_GL_HWIDGET widget, T_GL_COORD min) GL_EXCEPTION;

/** Gets the maximum limit of the bar (scrollbar, progressbar) @ref GL_Widget_RangeProperties
@param widget widget handle
@return maximum limit */
T_GL_COORD GL_Widget_GetMax(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the maximum limit of the bar (scrollbar, progressbar) @ref GL_Widget_RangeProperties
@param widget widget handle
@param max maximum limit */
void GL_Widget_SetMax(T_GL_HWIDGET widget, T_GL_COORD max) GL_EXCEPTION;

/** Gets the value of the bar (scrollbar, progressbar) @ref GL_Widget_RangeProperties
@param widget widget handle
@return the current value */
T_GL_COORD GL_Widget_GetValue(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the value of the bar (scrollbar, progressbar) @ref GL_Widget_RangeProperties
@param widget widget handle
@param value value to set (this value must always be within min and max otherwise this value will be ignored) */
void GL_Widget_SetValue(T_GL_HWIDGET widget, T_GL_COORD value) GL_EXCEPTION;

/** Gets the page size of the bar (scrollbar, progressbar) @ref GL_Widget_RangeProperties
@param widget widget handle
@return the current page */
T_GL_DIM GL_Widget_GetPage(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the page size of the bar (scrollbar, progressbar) @ref GL_Widget_RangeProperties
@param widget widget handle
@param page page size to set (this page must be greater than 0) */
void GL_Widget_SetPage(T_GL_HWIDGET widget, T_GL_DIM page) GL_EXCEPTION;

/** Gets the step value of the bar (scrollbar, progressbar, slider) @ref GL_Widget_RangeProperties
@param widget widget handle
@return the current step */
T_GL_DIM GL_Widget_GetStep(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the step size of the bar (scrollbar, progressbar, slider) @ref GL_Widget_RangeProperties
@param widget widget handle
@param step step size to set (this step must be greater than 0) */
void GL_Widget_SetStep(T_GL_HWIDGET widget, T_GL_DIM step) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                    GROW                                                        */
/* ************************************************************************************************************** */

/*<ALL>
	Enum("DIRECTION",                            "Direction of the change in size",
		Define("width",            "1",          "Authorizes a change in size in width"),
		Define("height",           "2",          "Authorizes a change in size in height"),
		Define("all",              "3",          "Authorizes a change in size all direction"),
		Define("none",             "0",          "Prohibits any change in size"),
		),             
</ALL>*/
/** Direction of grow or crop */
typedef enum T_GL_DIRECTION
{
	GL_DIRECTION_NONE   = 0, ///< No modification
	GL_DIRECTION_WIDTH  = 1, ///< Width adaptation direction
	GL_DIRECTION_HEIGHT = 2, ///< Height adaptation direction
	GL_DIRECTION_ALL    = (GL_DIRECTION_WIDTH | GL_DIRECTION_HEIGHT) ///< All adaptation direction 
} T_GL_DIRECTION;

/** Sets the widget grow flag (Grow flag : The widget cell can grow beyond its size hint if necessary) @ref GL_Widget_LayoutProperties
@param widget widget handle 
@param grow grow value */
void GL_Widget_SetGrow(T_GL_HWIDGET widget, T_GL_DIRECTION grow) GL_EXCEPTION;

/** Gets the widget grow flag (Grow flag : The widget cell can grow beyond its size hint if necessary) @ref GL_Widget_LayoutProperties
@param widget widget handle 
@return grow */
T_GL_DIRECTION GL_Widget_GetGrow(T_GL_HWIDGET widget) GL_EXCEPTION;



/* ************************************************************************************************************** */
/*                                                    SHRINK                                                      */
/* ************************************************************************************************************** */

/** Sets the widget shrink flag (Shrink flag : The widget cell can shrink below its size hint if necessary) @ref GL_Widget_LayoutProperties
@param widget widget handle
@param shrink shrink value */
void GL_Widget_SetShrink(T_GL_HWIDGET widget, T_GL_DIRECTION shrink) GL_EXCEPTION;

/** Gets the widget shrink flag (Shrink flag : The widget cell can shrink below its size hint if necessary) @ref GL_Widget_LayoutProperties
@param widget widget handle 
@return shrink */
T_GL_DIRECTION GL_Widget_GetShrink(T_GL_HWIDGET widget) GL_EXCEPTION;



/* ************************************************************************************************************** */
/*                                                    EXPAND                                                      */
/* ************************************************************************************************************** */

/** Sets the widget expand flag (Expand flag : The widget should get as much space as possible) @ref GL_Widget_LayoutProperties
@param widget widget handle 
@param expand expand value */
void GL_Widget_SetExpand(T_GL_HWIDGET widget, T_GL_DIRECTION expand) GL_EXCEPTION;

/** Gets the widget expand flag (Expand flag : The widget should get as much space as possible) @ref GL_Widget_LayoutProperties
@param widget widget handle 
@return expand */
T_GL_DIRECTION GL_Widget_GetExpand(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Gets the widget identifier @ref GL_Widget_IdProperties
@param widget widget handle 
@return the identifier */
T_GL_ID GL_Widget_GetId(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the widget identifier @ref GL_Widget_IdProperties
@param widget widget handle 
@param id the identifier */
void GL_Widget_SetId(T_GL_HWIDGET widget, T_GL_ID id) GL_EXCEPTION;

/** Search a widget based on its id @ref GL_Widget_IdProperties.
It does not search the id inside a user control, in this case you need to use this function @ref GL_UserControl_SearchId.
@param widget widget handle 
@param id the identifier 
@return the widget handle found or null if it is not found */
T_GL_HWIDGET GL_Widget_SearchId(T_GL_HWIDGET widget, T_GL_ID id) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                 COLOR                                                          */
/* ************************************************************************************************************** */

/** Gets the widget background color (@ref GL_SkinColors, @ref GL_TypesColors)
@param widget widget handle 
@return the background color */
T_GL_COLOR GL_Widget_GetBackColor(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the widget background color (@ref GL_SkinColors, @ref GL_TypesColors)
@param widget widget handle 
@param color new color */
void GL_Widget_SetBackColor(T_GL_HWIDGET widget, T_GL_COLOR color) GL_EXCEPTION;

/** Gets the widget foreground color (@ref GL_SkinColors, @ref GL_TypesColors)
@param widget widget handle 
@return the background color */
T_GL_COLOR GL_Widget_GetForeColor(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the widget foreground color (@ref GL_SkinColors, @ref GL_TypesColors)
@param widget widget handle 
@param color new color */
void GL_Widget_SetForeColor(T_GL_HWIDGET widget, T_GL_COLOR color) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                 FOCUS                                                          */
/* ************************************************************************************************************** */
/** Gets the focus state @ref GL_Widget_FocusProperties
@param widget widget handle
@return the focus state */
bool GL_Widget_GetFocus(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the focus state on the widget if the widget is focusable (only a single widget on a window can receive focus) @ref GL_Widget_FocusProperties
@param widget widget handle */
void GL_Widget_SetFocus(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Lets know if the widget can receive focus or not @ref GL_Widget_FocusProperties
@param widget widget handle
@return the focus state */
bool GL_Widget_GetFocusable(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Indicates that the widget can receive focus or not @ref GL_Widget_FocusProperties
@param widget widget handle 
@param state focusable state */
void GL_Widget_SetFocusable(T_GL_HWIDGET widget, bool state) GL_EXCEPTION;



/* ************************************************************************************************************** */
/*                                                 STATE                                                          */
/* ************************************************************************************************************** */
/*<ALL>
	Enum("STATE",                                "State to consider whether to display the widget",
		Define("focused",          "1",          "The widget has focus"),
		Define("unfocused",        "2",          "The widget has not focus"),
		Define("checked",          "4",          "The widget is checked"),
		Define("unchecked",        "8",          "The widget is not checked"),
		),
</ALL>*/

/** State to consider whether to display the widget @ref GL_Widget_StateMaskProperties */
typedef enum T_GL_STATE
{
	GL_STATE_FOCUSED = 0x01, ///< The widget has focus
	GL_STATE_CHECKED = 0x02, ///< The widget is checked

	GL_STATE_ALL = (GL_STATE_FOCUSED | GL_STATE_CHECKED),

	GL_STATE_EMPTY = 0
} T_GL_STATE;

/** Sets the state mask @ref GL_Widget_StateMaskProperties, by default the widget is always displayed.
@param widget widget handle
@param onMask Display mask when the state value is on (example if you place @ref GL_STATE_FOCUSED the widget will appear when it has focus)
@param offMask Display mask when the state value is off  (example if you place @ref GL_STATE_FOCUSED the widget will appear when it has not focus) */
void GL_Widget_SetStateMask(T_GL_HWIDGET widget, T_GL_STATE onMask, T_GL_STATE offMask);


/* ************************************************************************************************************** */
/*                                                CONFIG CLICK                                                    */
/* ************************************************************************************************************** */

/** Indicates that the widget sends a click event @ref GL_Widget_ClickProperties
@param widget widget handle
@return the focus state */
bool GL_Widget_GetClickable(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the clickable state (the widget sends a click event) @ref GL_Widget_ClickProperties
@param widget widget handle 
@param state clickable state */
void GL_Widget_SetClickable(T_GL_HWIDGET widget, bool state) GL_EXCEPTION;

/** Sets the click sensitive state (this widget is sensitive pen click) @ref GL_Widget_ClickProperties
@param widget widget handle
@return the focus state */
bool GL_Widget_GetClickSensitive(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Indicates that this widget is sensitive pen click @ref GL_Widget_ClickProperties
@param widget widget handle 
@param state clickable state */
void GL_Widget_SetClickSensitive(T_GL_HWIDGET widget, bool state) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                 CHECK                                                          */
/* ************************************************************************************************************** */

/** Gets the check state (only used by check button and radio button) @ref GL_Widget_CheckProperties
@param widget widget handle
@return the check state */
bool GL_Widget_GetCheck(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the check state (only used by check button and radio button) @ref GL_Widget_CheckProperties
@param widget widget handle
@param check the check state */
void GL_Widget_SetCheck(T_GL_HWIDGET widget, bool check) GL_EXCEPTION;

/** Toggle the check state (only used by check button) @ref GL_Widget_CheckProperties
@param widget widget handle */
void GL_Widget_ToggleCheck(T_GL_HWIDGET widget) GL_EXCEPTION;



/* ************************************************************************************************************** 
                                                    TEXT
   ************************************************************************************************************** */

/** Changes the text of the widget @ref GL_Widget_TextProperties
@param widget widget handle  (the default charset is UTF8, to change the charset use the function @ref GL_GraphicLib_SetCharset), WARNING: If the default charset is UTF8 and if you pass a non-UTF8 string all non-utf8 characters are replaced by '?'
@param format format diplayed on the widget (printf format) @ref GL_Widget_FormatProperties */
void GL_Widget_SetText(T_GL_HWIDGET widget, const char * format, ...)
#if (defined(__GNUC__) && !defined(_SIMULPC_))
      __attribute__((format(printf, 2, 3)));
#else
       GL_EXCEPTION;
#endif

/** Change the text of the widget (vprintf format) @ref GL_Widget_TextProperties
@param widget widget handle  (the default charset is UTF8, to change the charset use the function @ref GL_GraphicLib_SetCharset), WARNING: If the default charset is UTF8 and if you pass a non-UTF8 string all non-utf8 characters are replaced by '?'
@param format format diplayed on the widget @ref GL_Widget_FormatProperties 
@param arg arguments */
void GL_Widget_SetVText(T_GL_HWIDGET widget, const char * format, va_list arg)
#if (defined(__GNUC__) && !defined(_SIMULPC_))
      __attribute__((format(printf, 2, 0)));
#else
       GL_EXCEPTION;
#endif

/** Return the text of the widget @ref GL_Widget_TextProperties
@param widget widget handle
@return text of widget */
const char *GL_Widget_GetText(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                 TEXT WRAP                                                      */
/* ************************************************************************************************************** */

/** Sets the wrap of text. The wrap allows text to automatically return to the line if it does not fit in width in the space allocated to it.
@param widget widget handle
@param wrap wrap state (true activated, false disabled) */
void GL_Widget_SetWrap(T_GL_HWIDGET widget, bool wrap) GL_EXCEPTION;

/** Gets the wrap of text. The wrap allows text to automatically return to the line if it does not fit in width in the space allocated to it.
@param widget widget handle
@return wrap wrap state (true activated, false disabled) */
bool GL_Widget_GetWrap(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** 
                                                    FONT NAME
   ************************************************************************************************************** */

/** Change the font of the widget @ref GL_Widget_TextProperties
@param widget widget handle
@param name font name */
void GL_Widget_SetFontName(T_GL_HWIDGET widget, const char * name) GL_EXCEPTION;

/** Return the font name of the widget @ref GL_Widget_TextProperties
@param widget widget handle
@return font name */
const char *GL_Widget_GetFontName(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** 
                                                    FONT SIZE
   ************************************************************************************************************** */

/** Change the font size of the widget (Only the height is managed, width is reserved for future use) @ref GL_Widget_TextProperties
@param widget widget handle
@param width font width coded according to the chosen unit (width is reserved for future use)
@param height font width coded according to the chosen unit
@param unit unit of size */
void GL_Widget_SetFontSize(T_GL_HWIDGET widget, T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit) GL_EXCEPTION;

/** Return the font size of the widget (Only the height is managed, width is reserved for future use) @ref GL_Widget_TextProperties
@param widget widget handle
@return font size */
T_GL_SIZE GL_Widget_GetFontSize(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Relative size to the size of the screen */
typedef enum T_GL_SCALE
{
	GL_SCALE_XXSMALL = 0x3FF0, ///< Extra extra small font size (Optimized to display an average of 24 characters on the screen width)
	GL_SCALE_XSMALL  = 0x3FF1, ///< Extra small font size  (Optimized to display an average of 24 characters on the screen width)
	GL_SCALE_SMALL   = 0x3FF2, ///< Small font size (Optimized to display an average of 22 characters on the screen width)
	GL_SCALE_MEDIUM  = 0x3FF3, ///< Medium font size (Optimized to display an average of 20 characters on the screen width)
	GL_SCALE_LARGE   = 0x3FF4, ///< Large font size (Optimized to display an average of 16 characters on the screen width)
	GL_SCALE_XLARGE  = 0x3FF5, ///< Extra large font size (Optimized to display an average of 12 characters on the screen width)
	GL_SCALE_XXLARGE = 0x3FF6  ///< Extra extra large font size (Optimized to display an average of 10 characters on the screen width)
} T_GL_SCALE;

/** Change the font size relative to the size of the screen (This size depends of the skin loaded) @ref GL_Widget_TextProperties
@param widget widget handle
@param scale scale to set */
void GL_Widget_SetFontScale(T_GL_HWIDGET widget, T_GL_SCALE scale) GL_EXCEPTION;

/* ************************************************************************************************************** 
                                                    FONT STYLE
   ************************************************************************************************************** */

/** Change the font style of the widget @ref GL_Widget_TextProperties
@param widget widget handle
@param style style of font */
void GL_Widget_SetFontStyle(T_GL_HWIDGET widget, T_GL_FONT_STYLE style) GL_EXCEPTION;

/** Return the font style of the widget @ref GL_Widget_TextProperties
@param widget widget handle
@return font style */
T_GL_FONT_STYLE GL_Widget_GetFontStyle(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** 
                                                    IMAGE FILENAME
   ************************************************************************************************************** */
/*<ALL>
	RegExpString("SOURCEFILE", ".*",                          "Source file name  (file name can contain alphanumeric, underscore, minus, spaces characters)"),
</ALL>*/
/** Changes the image source of the widget @ref GL_Widget_Url, @ref GL_Widget_ImagesProperties
@param widget widget handle
@param source source of the image (See @ref GL_Widget_Url for the url coding)*/
void GL_Widget_SetSource(T_GL_HWIDGET widget, const char * source) GL_EXCEPTION;

/** Return the image source of the widget @ref GL_Widget_Url, @ref GL_Widget_ImagesProperties
@param widget widget handle
@return source of image */
const char *GL_Widget_GetSource(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Changes the source image from buffer @ref GL_Widget_ImagesProperties
@param widget widget handle
@param bufferImage image buffer
@param bufferSize size of image buffer */
void GL_Widget_SetSourceFromBuffer(T_GL_HWIDGET widget, const void * bufferImage, unsigned long bufferSize) GL_EXCEPTION;


/* ************************************************************************************************************** 
                                                    CALLBACK
   ************************************************************************************************************** */

/** Message handle definition (Stylus button, key, timer, ...) */
typedef struct T_GL_MESSAGE * T_GL_HMESSAGE ;

/** Definition pointer callback message processing 
@param message message handle
@return Returns false to skip the processing of this message. Returns true to consider the message*/
typedef bool (*T_GL_MESSAGE_CALLBACK)(T_GL_HMESSAGE message);

/** Adds a callback to a widget of treatment for a given message type @ref GL_Widget_CallbackProperties 
@param widget widget handle
@param type event type of message on which the callback will be called
@param callback pointer message processing (null pointer unregister the callback) */
void GL_Widget_RegisterCallback(T_GL_HWIDGET widget, T_GL_EVENT_TYPE type, T_GL_MESSAGE_CALLBACK callback) GL_EXCEPTION;

/** Removes a callback to a widget of treatment for a given message type @ref GL_Widget_CallbackProperties 
@param widget widget handle
@param type event type of message on which the callback will be called
@param callback pointer message processing (null pointer unregister the callback) */
void GL_Widget_UnregisterCallback(T_GL_HWIDGET widget, T_GL_EVENT_TYPE type, T_GL_MESSAGE_CALLBACK callback) GL_EXCEPTION;

/** Sends a message, is used to transmit a message, the message must always be created with the functions @ref GL_Message_Create.
A message received in a callback should never be send by this function.
@param widget widget handle
@param message message handle */
void GL_Widget_SendMessage(T_GL_HWIDGET widget, T_GL_HMESSAGE message) GL_EXCEPTION;



/* ************************************************************************************************************** 
                                                    TEXT ALIGN
   ************************************************************************************************************** */

/** Sets the widget text alignement @ref GL_Widget_TextProperties
@param widget widget handle
@param align the text alignement */
void GL_Widget_SetTextAlign(T_GL_HWIDGET widget, T_GL_ALIGN align) GL_EXCEPTION;


/** Gets the widget text alignement @ref GL_Widget_TextProperties
@param widget widget handle
@return the text alignement */
T_GL_ALIGN GL_Widget_GetTextAlign(T_GL_HWIDGET widget) GL_EXCEPTION;



/* ************************************************************************************************************** 
                                                    TEXT PADDINGS
   ************************************************************************************************************** */

/** Sets the widget text paddings @ref GL_Widget_TextProperties
@param widget widget handle
@param left left padding coded according to the chosen unit
@param top top padding coded according to the chosen unit
@param right right padding coded according to the chosen unit
@param bottom bottom padding coded according to the chosen unit
@param unit unit size*/
void GL_Widget_SetTextPaddings(T_GL_HWIDGET widget, T_GL_DIM left, T_GL_DIM top, T_GL_DIM right, T_GL_DIM bottom, T_GL_UNIT unit) GL_EXCEPTION;

/** Gets the widget text paddings @ref GL_Widget_TextProperties
@param widget widget handle
@return the text paddings */
T_GL_PADDINGS GL_Widget_GetTextPaddings(T_GL_HWIDGET widget) GL_EXCEPTION;



/* ************************************************************************************************************** 
                                                    SHORTCUT
   ************************************************************************************************************** */

/** Adds a keyboard shortcut to a widget @ref GL_Widget_ShortcutProperties
@param widget widget handle (Only the widget clickable supports shortcuts)
@param key keystroke (If the value is @ref GL_KEY_NONE the shortcut will be removed, @ref GL_VIRTUAL_KEY_NEXT and @ref GL_VIRTUAL_KEY_PREVIOUS key can not be used as shortcu) */
void GL_Widget_SetShortcut(T_GL_HWIDGET widget, T_GL_WCHAR key) GL_EXCEPTION;

/** Gets the keyboard shortcut attached to widget @ref GL_Widget_ShortcutProperties
@param widget widget handle
@return keystroke */
T_GL_WCHAR GL_Widget_GetShortcut(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** 
                                                    INPUT MASK
   ************************************************************************************************************** */

/** Sets the input mask @ref GL_Widget_InputProperties
@param widget widget handle
@param mask mask string handle (@ref GL_Widget_MaskProperties) */
void GL_Widget_SetMask(T_GL_HWIDGET widget, const char * mask) GL_EXCEPTION;

/** Gets the character user mask (@ref GL_Widget_MaskProperties) @ref GL_Widget_InputProperties
@param widget widget handle
@return character user mask */
const char *GL_Widget_GetUserChar(T_GL_HWIDGET widget);

/** Sets the character user mask (@ref GL_Widget_MaskProperties) @ref GL_Widget_InputProperties
@param widget widget handle
@param value String that contains the set of characters accepted by the user mask */
void GL_Widget_SetUserChar(T_GL_HWIDGET widget, const char * value);


/* ************************************************************************************************************** 
                                                    FILL CHAR
   ************************************************************************************************************** */

/** Sets the default fill character (This character appears only in fields with an input mask defined) @ref GL_Widget_MaskProperties
@param widget widget handle 
@param character fill character */
void GL_Widget_SetFillChar1(T_GL_HWIDGET widget, T_GL_WCHAR character) GL_EXCEPTION;

/** Gets the default fill character (This character appears only in fields with an input mask defined) @ref GL_Widget_MaskProperties
@param widget widget handle
@return character fill character */
T_GL_WCHAR GL_Widget_GetFillChar1(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Sets the default fill character (This character appears only in fields with an input mask defined) @ref GL_Widget_MaskProperties
@param widget widget handle
@param character fill character */
void GL_Widget_SetFillChar2(T_GL_HWIDGET widget, T_GL_WCHAR character) GL_EXCEPTION;

/** Gets the default fill character (This character appears only in fields with an input mask defined) @ref GL_Widget_MaskProperties
@param widget widget handle
@return character fill character */
T_GL_WCHAR GL_Widget_GetFillChar2(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** 
                                                    PASSWORD CHAR
   ************************************************************************************************************** */

/** Sets the default password character @ref GL_Widget_MaskProperties
@param widget widget handle
@param character password character */
void GL_Widget_SetPasswordChar(T_GL_HWIDGET widget, T_GL_WCHAR character) GL_EXCEPTION;

/** Gets the default password character @ref GL_Widget_MaskProperties
@param widget widget handle
@return character password character */
T_GL_WCHAR GL_Widget_GetPasswordChar(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** 
                                                    INPUT MODE
   ************************************************************************************************************** */
/*<ALL>
	Struct("INPUTMODE",                           "Configure the input mode",
		Bool("blank",                             "false:hide the blank part of input, true:show the blank part of input"),
		Bool("password",                          "false:The characters entered are displayed, true:The characters entered are replaced by the '*' (used to enter password)"),
		Bool("prompt",                            "false:hide the prompt, true:show the prompt"),
		Bool("replace",                           "false:The characters entered are inserted into the input field, true:The characters entered replace existing characters in the input field"),
		Bool("zeroSignificant",                   "false:The zeros are not displayed in the early numbers, true:The zeros are displayed in the early numbers (eg 000123)"),
	),
</ALL>*/
/** Input mode mask */
typedef enum T_GL_MODE
{
	// Input behavior
	GL_MODE_INSERT            = 0x00, ///< The characters entered are inserted into the input field
	GL_MODE_REPLACE           = 0x01, ///< The characters entered replace existing characters in the input field

	// Password
	GL_MODE_NORMAL            = 0x00, ///< The characters entered are displayed
	GL_MODE_PASSWORD          = 0x02, ///< The characters entered are replaced by the '*' (used to enter password)

	// 0 not significant
	GL_MODE_0_SIGNIFICANT     = 0x00, ///< The zeros are displayed in the early numbers (eg 000123)
	GL_MODE_0_NOT_SIGNIFICANT = 0x08, ///< The zeros are not displayed in the early numbers 

	// Hide or show prompt
	GL_MODE_SHOW_PROMPT       = 0x00, ///< Show the prompt
	GL_MODE_HIDE_PROMPT       = 0x10, ///< Hide the prompt

	// Hide or show blank part 
	GL_MODE_SHOW_BLANK        = 0x00, ///< Show the blank part of input (example : with the following pattern "/d/d,/d/d/D./D/D" it shows the comma unnecessary : "  ,  0.00")
	GL_MODE_HIDE_BLANK        = 0x20  ///< Hide the blank part of input (example : with the following pattern "/d/d,/d/d/D./D/D" it hides the comma unnecessary : "0.00")
} T_GL_MODE;

/** Sets the input mode @ref GL_Widget_MaskProperties
@param widget widget handle 
@param mode input mode */
void GL_Widget_SetMode(T_GL_HWIDGET widget, T_GL_MODE mode) GL_EXCEPTION;

/** Gets the input mode @ref GL_Widget_MaskProperties
@param widget widget handle 
@return mode input mode */
T_GL_MODE GL_Widget_GetMode(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** 
                                                    INPUT
   ************************************************************************************************************** */

/** Sets the input text of the widget (The input text is the raw text entered by the user without the mask characters) @ref GL_Widget_MaskProperties
@param widget widget handle
@param text text diplayed on the widget */
void GL_Widget_SetInput(T_GL_HWIDGET widget, const char * text) GL_EXCEPTION;

/** Gets the input text of the widget  (The input text is the raw text entered by the user without the mask characters) @ref GL_Widget_MaskProperties
@param widget widget handle
@return widget text */
const char *GL_Widget_GetInput(T_GL_HWIDGET widget) GL_EXCEPTION;

/** Selects all characters in the widget, the first entry of a character deletes the entire contents of the field @ref GL_Widget_MaskProperties
@param widget widget handle */
void GL_Widget_SelectAll(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** 
                                                    User data
   ************************************************************************************************************** */

/** Sets the contents of the user data attached to a widget.
The contents of the data passed as parameter is copied internally in the widget. (@ref GL_Widget_UserDataProperties)
@param widget widget handle
@param data data buffer handle
@param dataSize maximal size of data buffer */
void GL_Widget_SetUserData(T_GL_HWIDGET widget, const void * data, unsigned long dataSize) GL_EXCEPTION;

/** Gets the contents of the user data attached to a widget (@ref GL_Widget_UserDataProperties for explanation)
@param widget widget handle
@param data data buffer handle
@param dataSize maximal size of data buffer
@return size of data gets */
unsigned long GL_Widget_GetUserData(T_GL_HWIDGET widget, void * data, unsigned long dataSize) GL_EXCEPTION;


/* ************************************************************************************************************** 
                                                    By ID
   ************************************************************************************************************** */

/** Changes the text of the widget
@param widget widget handle  (the default charset is UTF8, to change the charset use the function @ref GL_GraphicLib_SetCharset), WARNING: If the default charset is UTF8 and if you pass a non-UTF8 string all non-utf8 characters are replaced by '?'
@param id the identifier 
@param format format diplayed on the widget 
@param arg arguments */
void GL_Widget_SetVTextById(T_GL_HWIDGET widget, T_GL_ID id, const char * format, va_list arg)
#if (defined(__GNUC__) && !defined(_SIMULPC_))
      __attribute__((format(printf, 3, 0)));
#else
       GL_EXCEPTION;
#endif

/** Changes the text of the widget
@param widget widget handle  (the default charset is UTF8, to change the charset use the function @ref GL_GraphicLib_SetCharset), WARNING: If the default charset is UTF8 and if you pass a non-UTF8 string all non-utf8 characters are replaced by '?'
@param id the identifier 
@param format format diplayed on the widget @ref GL_Widget_FormatProperties */
void GL_Widget_SetTextById(T_GL_HWIDGET widget, T_GL_ID id, const char * format, ...)
#if (defined(__GNUC__) && !defined(_SIMULPC_))
      __attribute__((format(printf, 3, 4)));
#else
       GL_EXCEPTION;
#endif

/** Return the text of the widget
@param widget widget handle
@param id the identifier 
@return error code */
const char * GL_Widget_GetTextById(T_GL_HWIDGET widget, T_GL_ID id) GL_EXCEPTION;

/** Changes the image source of the widget @ref GL_Widget_Url
@param widget widget handle
@param id the identifier 
@param source source of the image (See @ref GL_Widget_Url for the url coding)*/
void GL_Widget_SetSourceById(T_GL_HWIDGET widget, T_GL_ID id, const char * source) GL_EXCEPTION;

/** Return the image source of the widget @ref GL_Widget_Url
@param widget widget handle
@param id the identifier 
@return source of image */
const char * GL_Widget_GetSourceById(T_GL_HWIDGET widget, T_GL_ID id) GL_EXCEPTION;

/** Sets the input mask 
@param widget widget handle
@param id the identifier 
@param mask mask string handle (@ref GL_Widget_MaskProperties) */
void GL_Widget_SetMaskById(T_GL_HWIDGET widget, T_GL_ID id, const char * mask) GL_EXCEPTION;

/** Sets the contents of the user data attached to a widget (@ref GL_Widget_UserDataProperties)
@param widget widget handle
@param id the identifier 
@param data data buffer handle
@param dataSize maximal size of data buffer */
void GL_Widget_SetUserDataById(T_GL_HWIDGET widget, T_GL_ID id, const void * data, unsigned long dataSize) GL_EXCEPTION;

/** Gets the contents of the user data attached to a widget (@ref GL_Widget_UserDataProperties)
@param widget widget handle
@param id the identifier 
@param data data buffer handle
@param dataSize maximal size of data buffer
@return size of data gets */
unsigned long GL_Widget_GetUserDataById(T_GL_HWIDGET widget, T_GL_ID id, void * data, unsigned long dataSize) GL_EXCEPTION;

/** Gets the check state 
@param widget widget handle
@param id the identifier 
@return the checked state */
bool GL_Widget_GetCheckById(T_GL_HWIDGET widget, T_GL_ID id) GL_EXCEPTION;

/** Sets the check state 
@param widget widget handle
@param id the identifier 
@param check the checked state */
void GL_Widget_SetCheckById(T_GL_HWIDGET widget, T_GL_ID id, bool check) GL_EXCEPTION;

/** Adds a callback to a widget of treatment for a given message type
@param widget widget handle
@param id the identifier 
@param type event type of message on which the callback will be called
@param callback pointer message processing (null pointer unregister the callback) */
void GL_Widget_RegisterCallbackById(T_GL_HWIDGET widget, T_GL_ID id, T_GL_EVENT_TYPE type, T_GL_MESSAGE_CALLBACK callback) GL_EXCEPTION;

/** Removes a callback to a widget of treatment for a given message type
@param widget widget handle
@param id the identifier 
@param type event type of message on which the callback will be called
@param callback pointer message processing (null pointer unregister the callback) */
void GL_Widget_UnregisterCallbackById(T_GL_HWIDGET widget, T_GL_ID id, T_GL_EVENT_TYPE type, T_GL_MESSAGE_CALLBACK callback) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                 BORDER                                                         */
/* ************************************************************************************************************** */

/** Sets the widget borders  
@param widget widget handle 
@param left left border coded according to the chosen unit
@param top top border coded according to the chosen unit
@param right right border coded according to the chosen unit
@param bottom bottom border coded according to the chosen unit
@param unit unit borders
@param color new color */
void GL_Widget_SetBorders(T_GL_HWIDGET widget, T_GL_DIM left, T_GL_DIM top, T_GL_DIM right, T_GL_DIM bottom, T_GL_UNIT unit, T_GL_COLOR color) GL_EXCEPTION;

/** Gets the widget margins
@param widget widget handle 
@return margins */
T_GL_BORDERS GL_Widget_GetBorders(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                 DESIGNER                                                       */
/* ************************************************************************************************************** */

/** Gets the rectangle of the widget on the window. The position is relative to the window.
WARNING : This function returns the correct values only after a call of function @ref GL_Window_Dispatch.
WARNING : it does not take into account the thickness of the border of the window.
@param widget widget handle
@return Rectangle occupied by the widget on the window. The coordinates and sizes are expressed in pixels. */
T_GL_RECT     GL_Widget_GetRect(T_GL_HWIDGET widget) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                 RESOURCE                                                       */
/* ************************************************************************************************************** */

/** Reads a resource file and instantiates all objects in the read file.
This function is intended to assemble multiple resources to create the contents of a window. 
Ingedev currently does not allow the creation of such a resource, but later it will.
WARNING resource file must absolutely not contain window or document widget.
@param parent parent object which will hold the resource read
@param filename name and file path configuration
@return returns the instantiated resource or null if an error is detected */
T_GL_HWIDGET GL_Widget_ReadResource(T_GL_HWIDGET parent, const char * filename) GL_EXCEPTION;

/** Instanciates a resource from a string 
This function is intended to assemble multiple resources to create the contents of a window. 
Ingedev currently does not allow the creation of such a resource, but later it will.
WARNING resource file must absolutely not contain window or document widget.
You can also create a resource from a Json file.
@param parent parent object which will hold the resource read
@param content JSON string content the resource 
(The JSON string can be encoded in UTF-8, UTF-16 or UTF-32. If the string is encoded in UTF-32 or UTF-16 it is 
imperative to add a BOM at the begin of the string, to know the BOM supported see @ref T_GL_ENCODING_BOM)
@param size total size in bytes of the JSON string
@return returns the instantiated resource or null if an error is detected */
T_GL_HWIDGET GL_Widget_InstanciateResource(T_GL_HWIDGET parent, const char * content, unsigned long size) GL_EXCEPTION;


/* ************************************************************************************************************** */
/*                                                    ID                                                          */
/* ************************************************************************************************************** */

/**
@}
@addtogroup GL_SkinWidgetId
@{
*/
#define GL_ID_SKIN_START               0xFF000000 //!< First reserved id used by the skin
#define GL_ID_SKIN_LABEL               0xFF000001 //!< Identifies the text label in a widget (@ref GL_Button, @ref GL_CheckButton, @ref GL_Edit, @ref GL_Icon, @ref GL_IconButton, @ref GL_ProgressBar, @ref GL_RadioButton, ...)
#define GL_ID_SKIN_CHECK               0xFF000003 //!< Identifies the check or radio picture in a widget (@ref GL_CheckButton, @ref GL_RadioButton)
#define GL_ID_SKIN_SLIDER              0xFF000004 //!< Identifies the slider in a bar (@ref GL_HScrollBar, @ref GL_VScrollBar, @ref GL_HSlider, @ref GL_ProgressBar)
#define GL_ID_SKIN_BAR                 0xFF000005 //!< Identifies the bar (@ref GL_HScrollBar, @ref GL_VScrollBar, @ref GL_HSlider, @ref GL_ProgressBar)
#define GL_ID_SKIN_ICON                0xFF000006 //!< Identifies the icon image (@ref GL_Button, @ref GL_Icon, @ref GL_IconButton)
#define GL_ID_SKIN_HSCROLLBAR          0xFF000007 //!< Identifies the horizontal scroll bar 
#define GL_ID_SKIN_VSCROLLBAR          0xFF000008 //!< Identifies the vertical scroll bar in a list (@ref GL_List)
#define GL_ID_SKIN_LIST                0xFF000009 //!< Identifies the content layout in a list (@ref GL_List)
#define GL_ID_SKIN_SCROLLVIEW          0xFF00000A //!< Identifies the scroll view in a list (@ref GL_List)
#define GL_ID_SKIN_DIALOG              0xFF00000B //!< Identifies the dialog (@ref GL_Dialog)
#define GL_ID_SKIN_DIALOG_CONTENT      0xFF00000C //!< Identifies the content layout in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_DIALOG_TITLE        0xFF00000D //!< Identifies the title in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_DIALOG_ICON         0xFF00000E //!< Identifies the icon in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_DIALOG_BUTTONS      0xFF00000F //!< Identifies the buttons layout in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_DIALOG_TEXT         0xFF000010 //!< Identifies the text in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_DIALOG_VALID        0xFF000011 //!< Identifies the valid button in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_DIALOG_CORRECTION   0xFF000012 //!< Identifies the correction button in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_DIALOG_CANCEL       0xFF000013 //!< Identifies the cancel button in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_DIALOG_LAYOUT       0xFF000014 //!< Identifies the layout in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_DIALOG_VALUE        0xFF000015 //!< Identifies the edit in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_DIALOG_UNIT         0xFF000016 //!< Identifies the unit in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_EDIT_FIELD          0xFF000017 //!< Identifies the edit field in the virtual keyboard (@ref GL_VirtualKeyboard)
#define GL_ID_SKIN_DIALOG_LIST         0xFF000018 //!< Identifies the list in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_DIALOG_HELP         0xFF000019 //!< Identifies the help in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_DIALOG_KEYBOARD     0xFF00001A //!< Identifies the virtual keyboard table (@ref GL_Dialog)
#define GL_ID_SKIN_KEY_ICON            0xFF00001B //!< Identifies the key icon (@ref GL_VirtualKeyboard)
#define GL_ID_SKIN_DIALOG_SHORTCUT     0xFF00001C //!< Identifies the shortcut button in dialog (@ref GL_Dialog)
#define GL_ID_SKIN_LEFT_ARROW          0xFF00001D //!< Identifies the icon image of the left arrow (@ref GL_Button)
#define GL_ID_SKIN_RIGHT_ARROW         0xFF00001E //!< Identifies the icon image of the right arrow (@ref GL_Button)

/* ------------------------------------------------------------------------------------------------------ */
#define GL_ID_SKIN_STOP                0xFFFFFFFE //!< Last id used by the skin 
#define GL_ID_UNDEFINED                0xFFFFFFFF //!< Undefined id 

/**
@}
*/
#ifdef __cplusplus
}
#endif

#endif //GL_Widget_h_INCLUDED
