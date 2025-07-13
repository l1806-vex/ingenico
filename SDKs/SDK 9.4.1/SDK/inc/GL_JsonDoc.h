
/**

@addtogroup GL_Json
@{
@addtogroup GL_JsonFormat

@section GL_JsonWidgetsDefinition Widgets definition

@{



	<table border=0 cellspacing=0 cellpadding=0><tr><td><a href="#BARCODE">BARCODE</a></td><td>Widget to display a barcode</td></tr><tr><td><a href="#BUTTON">BUTTON</a></td><td>The button to command the terminal to perform some action, or to answer a question</td></tr><tr><td><a href="#CHECKBUTTON">CHECKBUTTON</a></td><td>A check button is an option button that can be switched on (checked) or off (unchecked)</td></tr><tr><td><a href="#DOCUMENT">DOCUMENT</a></td><td>The document allows the print of a document</td></tr><tr><td><a href="#DRAWING">DRAWING</a></td><td>the drawing widget is a surface on which the user can draw a graph</td></tr><tr><td><a href="#EDIT">EDIT</a></td><td>Widget that is used to edit a single line of text.</td></tr><tr><td><a href="#HSCROLLBAR">HSCROLLBAR</a></td><td>A scroll bar is a control that enables the user to access parts of a document that is larger than the widget used to display it</td></tr><tr><td><a href="#HSLIDER">HSLIDER</a></td><td>The slider is the classic widget for controlling a bounded value. It lets the user move a slider handle along groove and translates the handle's position into an integer value within the legal range</td></tr><tr><td><a href="#ICON">ICON</a></td><td>The class icon is equivalent to a button, it allows the display of an image more</td></tr><tr><td><a href="#ICONBUTTON">ICONBUTTON</a></td><td>The class icon button is equivalent to a button with an icon, it allows the display of an image more</td></tr><tr><td><a href="#LABEL">LABEL</a></td><td>This class is used to display text on a line or a multi-line text</td></tr><tr><td><a href="#LAYOUT">LAYOUT</a></td><td>The layout can be viewed as a table with multiple rows and columns to place widgets</td></tr><tr><td><a href="#LIST">LIST</a></td><td>The list allows the display of all elements of widgets</td></tr><tr><td><a href="#MEDIA">MEDIA</a></td><td>This class is used to play movie or sound</td></tr><tr><td><a href="#PALETTE">PALETTE</a></td><td>A palette is a widget that can display a color palette</td></tr><tr><td><a href="#PICTURE">PICTURE</a></td><td>A picture is a widget that can display a fixed image or animated image</td></tr><tr><td><a href="#PLUGIN">PLUGIN</a></td><td>This class is used to play movie or sound</td></tr><tr><td><a href="#PRINT">PRINT</a></td><td>This class is used to print text on a line or a multi-line text</td></tr><tr><td><a href="#PROGRESSBAR">PROGRESSBAR</a></td><td>A progress bar is used to give the user an indication of the progress of an operation </td></tr><tr><td><a href="#RADIOBUTTON">RADIOBUTTON</a></td><td>A radio button is an option button that can be switched on (checked) or off (unchecked)</td></tr><tr><td><a href="#SCROLLVIEW">SCROLLVIEW</a></td><td>A scroll view is used to display the contents of many children widget within a frame</td></tr><tr><td><a href="#SIGNATURE">SIGNATURE</a></td><td>This class is used to play movie or sound</td></tr><tr><td><a href="#TIMER">TIMER</a></td><td>Repetitive timers</td></tr><tr><td><a href="#VIRTUALKEYBOARD">VIRTUALKEYBOARD</a></td><td>The virtual keyboard allows easy entry of special characters</td></tr><tr><td><a href="#VSCROLLBAR">VSCROLLBAR</a></td><td>A scroll bar is a control that enables the user to access parts of a document that is larger than the widget used to display it</td></tr><tr><td><a href="#WINDOW">WINDOW</a></td><td>This widget allows management of a window on the screen</td></tr></table><br><b><a name="BARCODE_PARAM_INTEGER">BARCODE_PARAM_INTEGER object</a></b>, Define a barcode integer parameter, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"name":</td><td><a href="#STRING">STRING</a>,</td><td>// Name of parameter</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"valueinteger":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Value of parameter</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="BARCODE_PARAM_STRING">BARCODE_PARAM_STRING object</a></b>, Define a barcode string parameter, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"name":</td><td><a href="#STRING">STRING</a>,</td><td>// Name of parameter</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"valuestring":</td><td><a href="#STRING">STRING</a>,</td><td>// Value of parameter</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="BARCODE_PARAMS">BARCODE_PARAMS</a> array</b>, List of barcode parameters, the different elements that can be used in this array are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>[</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#BARCODE_PARAM_INTEGER">BARCODE_PARAM_INTEGER</a>,</td><td>// Define the integer barcode parameter</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#BARCODE_PARAM_STRING">BARCODE_PARAM_STRING</a>,</td><td>// Define the string barcode parameter</td></tr>
<tr><td>]</td></tr></table><br>
<b><a name="BARCODE">BARCODE object</a></b>, Widget to display a barcode, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"mimetype":</td><td><a href="#STRING">STRING</a>,</td><td>// Barcode mimetype</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"parameters":</td><td><a href="#BARCODE_PARAMS">BARCODE_PARAMS</a>,</td><td>// List of specific parameters for the barcode</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="BUTTON">BUTTON object</a></b>, The button to command the terminal to perform some action, or to answer a question, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"text":</td><td><a href="#STRING">STRING</a>,</td><td>// Text displayed on the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"font":</td><td><a href="#FONT">FONT</a>,</td><td>// Font used in display of text</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="CHECKBUTTON">CHECKBUTTON object</a></b>, A check button is an option button that can be switched on (checked) or off (unchecked), the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"text":</td><td><a href="#STRING">STRING</a>,</td><td>// Text displayed on the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"font":</td><td><a href="#FONT">FONT</a>,</td><td>// Font used in display of text</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="DOCUMENT">DOCUMENT object</a></b>, The document allows the print of a document, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"showonscreen":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Displays the document on the screen</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ACTIONPEN">ACTIONPEN object</a></b>, Define the pen, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"color":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Pen color  (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue) coded decimal</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ACTIONBRUSH">ACTIONBRUSH object</a></b>, Define the brush, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"color":</td><td><a href="#COLOR">COLOR</a>,</td><td>// brush color  (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue) coded decimal</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ACTIONFONT">ACTIONFONT object</a></b>, Define the font action, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"font":</td><td><a href="#FONT">FONT</a>,</td><td>// Font definition</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ACTIONTEXT">ACTIONTEXT object</a></b>, Define the text action, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of text</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"text":</td><td><a href="#STRING">STRING</a>,</td><td>// Text to display</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"wrap":</td><td><a href="#BOOL">BOOL</a>,</td><td>// The wrap allows text to automatically return to the line if it does not fit in width in the space allocated to it.</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ACTIONRECT">ACTIONRECT object</a></b>, Define the rectangle action, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of rectangle</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of rectangle</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ACTIONELLIPSE">ACTIONELLIPSE object</a></b>, Define the ellipse action, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of center </td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"radius":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Radius</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ACTIONPIE">ACTIONPIE object</a></b>, Define the pie action, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of center </td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"radius":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Radius</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"angle1":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Start of arc in 64ths of a degree (anticlockwise from the x axis)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"angle2":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// End of arc in 64ths of a degree (anticlockwise from the x axis)</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ACTIONARC">ACTIONARC object</a></b>, Define the arc action, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of center</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"radius":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Radius</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"start":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Starting point of the arc</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"end":</td><td><a href="#POSITION">POSITION</a>,</td><td>// End point of the arc</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ACTIONLINE">ACTIONLINE object</a></b>, Define the line action, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"point1":</td><td><a href="#POSITION">POSITION</a>,</td><td>// First point of line</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"point2":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Second point of line</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ACTIONIMAGE">ACTIONIMAGE object</a></b>, Define the image action, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"source":</td><td><a href="#SOURCEFILE">SOURCEFILE</a>,</td><td>// Filename of the image (file name can contain alphanumeric, underscore, minus, spaces characters)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Destination position of image</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ACTIONSTRETCH">ACTIONSTRETCH object</a></b>, Define the stretch image action, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"source":</td><td><a href="#SOURCEFILE">SOURCEFILE</a>,</td><td>// Filename of the image (file name can contain alphanumeric, underscore, minus, spaces characters)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Destination position of image</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Destination size of image</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="POINTS">POINTS</a> array</b>, List of points, the different elements that can be used in this array are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>[</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#POSITION">POSITION</a>,</td><td>// Define the point</td></tr>
<tr><td>]</td></tr></table><br>
<b><a name="ACTIONPOLYGON">ACTIONPOLYGON object</a></b>, Define the polygon action, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"points":</td><td><a href="#POINTS">POINTS</a>,</td><td>// List of points</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ACTIONS">ACTIONS</a> array</b>, List of drawing actions, the different elements that can be used in this array are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>[</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ACTIONPEN">ACTIONPEN</a>,</td><td>// Define the pen</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ACTIONBRUSH">ACTIONBRUSH</a>,</td><td>// Define the brush</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ACTIONFONT">ACTIONFONT</a>,</td><td>// Define the font action</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ACTIONTEXT">ACTIONTEXT</a>,</td><td>// Define the text action</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ACTIONRECT">ACTIONRECT</a>,</td><td>// Define the rectangle action</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ACTIONELLIPSE">ACTIONELLIPSE</a>,</td><td>// Define the ellipse action</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ACTIONPIE">ACTIONPIE</a>,</td><td>// Define the pie action</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ACTIONLINE">ACTIONLINE</a>,</td><td>// Define the line action</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ACTIONIMAGE">ACTIONIMAGE</a>,</td><td>// Define the image action</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ACTIONSTRETCH">ACTIONSTRETCH</a>,</td><td>// Define the stretch image action</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ACTIONPOLYGON">ACTIONPOLYGON</a>,</td><td>// Define the polygon action</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ACTIONARC">ACTIONARC</a>,</td><td>// Define the arc action</td></tr>
<tr><td>]</td></tr></table><br>
<b><a name="DRAWING">DRAWING object</a></b>, the drawing widget is a surface on which the user can draw a graph, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"actions":</td><td><a href="#ACTIONS">ACTIONS</a>,</td><td>// Drawing actions</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"vectorized":</td><td><a href="#BOOL">BOOL</a>,</td><td>// If the mode is vectorized, all drawing commands are stored. In this case if you change the size of the widget the entire drawing is then scaled.</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="EDIT">EDIT object</a></b>, Widget that is used to edit a single line of text., the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"text":</td><td><a href="#STRING">STRING</a>,</td><td>// Text displayed on the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"font":</td><td><a href="#FONT">FONT</a>,</td><td>// Font used in display of text</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"fillchar1":</td><td><a href="#CHARACTER">CHARACTER</a>,</td><td>// Sets the default fill character 1 (This character appears only in fields with an input mask defined)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"fillchar2":</td><td><a href="#CHARACTER">CHARACTER</a>,</td><td>// Sets the default fill character 2 (This character appears only in fields with an input mask defined)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"passwordchar":</td><td><a href="#CHARACTER">CHARACTER</a>,</td><td>// Sets the default password character (This character appears only in fields with an input mask defined)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"mode":</td><td><a href="#INPUTMODE">INPUTMODE</a>,</td><td>// Configure the input mode</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"mask":</td><td><a href="#STRING">STRING</a>,</td><td>// mask string handle, see 'Mask properties' in the documentation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"userchar":</td><td><a href="#CHARACTER">CHARACTER</a>,</td><td>// String that contains the set of characters accepted by the user character mask (/u or /U)</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="HSCROLLBAR">HSCROLLBAR object</a></b>, A scroll bar is a control that enables the user to access parts of a document that is larger than the widget used to display it, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"range":</td><td><a href="#RANGE">RANGE</a>,</td><td>// Range</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="HSLIDER">HSLIDER object</a></b>, The slider is the classic widget for controlling a bounded value. It lets the user move a slider handle along groove and translates the handle's position into an integer value within the legal range, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"range":</td><td><a href="#RANGE">RANGE</a>,</td><td>// Range</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ICON">ICON object</a></b>, The class icon is equivalent to a button, it allows the display of an image more, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"source":</td><td><a href="#SOURCEFILE">SOURCEFILE</a>,</td><td>// Image source (file name can contain alphanumeric, underscore, minus, spaces characters)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"text":</td><td><a href="#STRING">STRING</a>,</td><td>// Text displayed on the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"font":</td><td><a href="#FONT">FONT</a>,</td><td>// Font used in display of text</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"transformation":</td><td><a href="#TRANSFORMATION">TRANSFORMATION</a>,</td><td>// Image transformation</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ICONBUTTON">ICONBUTTON object</a></b>, The class icon button is equivalent to a button with an icon, it allows the display of an image more, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"source":</td><td><a href="#SOURCEFILE">SOURCEFILE</a>,</td><td>// Image source (file name can contain alphanumeric, underscore, minus, spaces characters)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"text":</td><td><a href="#STRING">STRING</a>,</td><td>// Text displayed on the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"font":</td><td><a href="#FONT">FONT</a>,</td><td>// Font used in display of text</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"transformation":</td><td><a href="#TRANSFORMATION">TRANSFORMATION</a>,</td><td>// Image transformation</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="LABEL">LABEL object</a></b>, This class is used to display text on a line or a multi-line text, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"text":</td><td><a href="#STRING">STRING</a>,</td><td>// Text displayed on the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"font":</td><td><a href="#FONT">FONT</a>,</td><td>// Font used in display of text</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"wrap":</td><td><a href="#BOOL">BOOL</a>,</td><td>// The wrap allows text to automatically return to the line if it does not fit in width in the space allocated to it.</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="LAYOUT">LAYOUT object</a></b>, The layout can be viewed as a table with multiple rows and columns to place widgets, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ITEMS">ITEMS</a> array</b>, List of widgets, the different elements that can be used in this array are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>[</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#BUTTON">BUTTON</a>,</td><td>// The button to command the terminal to perform some action, or to answer a question</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#CHECKBUTTON">CHECKBUTTON</a>,</td><td>// A check button is an option button that can be switched on (checked) or off (unchecked)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#EDIT">EDIT</a>,</td><td>// The edit widget provides a widget that is used to edit a single line of text.</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#HSLIDER">HSLIDER</a>,</td><td>// The slider is the classic widget for controlling a bounded value. It lets the user move a slider handle along groove and translates the handle's position into an integer value within the legal range</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ICON">ICON</a>,</td><td>// The class icon is equivalent to a button, it allows the display of an image more</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ICONBUTTON">ICONBUTTON</a>,</td><td>// This class is an icon followed by a button</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#LABEL">LABEL</a>,</td><td>// This class is used to display text on a line or a multi-line text</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#LAYOUT">LAYOUT</a>,</td><td>// The layout can be viewed as a table with multiple rows and columns to place widgets</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#PALETTE">PALETTE</a>,</td><td>// A palette is a widget that can display a color palette</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#PICTURE">PICTURE</a>,</td><td>// A picture is a widget that can display a fixed image or animated image</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#PROGRESSBAR">PROGRESSBAR</a>,</td><td>// A progress bar is used to give the user an indication of the progress of an operation </td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#RADIOBUTTON">RADIOBUTTON</a>,</td><td>// A radio button is an option button that can be switched on (checked) or off (unchecked)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#VIRTUALKEYBOARD">VIRTUALKEYBOARD</a>,</td><td>// The virtual keyboard allows easy entry of special characters</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#BARCODE">BARCODE</a>,</td><td>// This widget can display a barcode</td></tr>
<tr><td>]</td></tr></table><br>
<b><a name="LIST">LIST object</a></b>, The list allows the display of all elements of widgets, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"items":</td><td><a href="#ITEMS">ITEMS</a>,</td><td>// List of items. IMPORTANT: All elements of the list widget should be placed in this tag.</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="MEDIA">MEDIA object</a></b>, This class is used to play movie or sound, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"loop":</td><td><a href="#BOOL">BOOL</a>,</td><td>// The video has preserved its width height ratio</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"keepratio":</td><td><a href="#BOOL">BOOL</a>,</td><td>// The video has preserved its width height ratio</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"source":</td><td><a href="#SOURCEFILE">SOURCEFILE</a>,</td><td>// Filename of the audio or video file (file name can contain alphanumeric, underscore, minus, spaces characters)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"volume":</td><td><a href="#BYTE">BYTE</a>,</td><td>// Volume level (0..255) 255=loud</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="PALETTE">PALETTE object</a></b>, A palette is a widget that can display a color palette, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"bordercolor":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Border color of the color item</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusbackcolor":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Background color of the focus</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusforecolor":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Foreground color of the focus</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focussize":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Thickness of the color focus selected on the palette</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxcolors":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Maximum number of colors present on the palette (This value is the number of columns)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxlights":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Minimum number of colors present on the palette (This value is the number of rows)</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="PICTURE">PICTURE object</a></b>, A picture is a widget that can display a fixed image or animated image, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"source":</td><td><a href="#SOURCEFILE">SOURCEFILE</a>,</td><td>// Image source (file name can contain alphanumeric, underscore, minus, spaces characters)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"transformation":</td><td><a href="#TRANSFORMATION">TRANSFORMATION</a>,</td><td>// Image transformation</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="PLUGIN">PLUGIN object</a></b>, This class is used to play movie or sound, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"mimetype":</td><td><a href="#STRING">STRING</a>,</td><td>// Mime type used to find the DLL plugin</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="PRINT">PRINT object</a></b>, This class is used to print text on a line or a multi-line text, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"font":</td><td><a href="#FONT">FONT</a>,</td><td>// Font used in print of text</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"text":</td><td><a href="#STRING">STRING</a>,</td><td>// Text printed on the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"wrap":</td><td><a href="#BOOL">BOOL</a>,</td><td>// The wrap allows text to automatically return to the line if it does not fit in width in the space allocated to it.</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="PROGRESSBAR">PROGRESSBAR object</a></b>, A progress bar is used to give the user an indication of the progress of an operation , the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"font":</td><td><a href="#FONT">FONT</a>,</td><td>// Font used in display of text</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"range":</td><td><a href="#RANGE">RANGE</a>,</td><td>// Range</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"text":</td><td><a href="#STRING">STRING</a>,</td><td>// Text displayed on the widget</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="RADIOBUTTON">RADIOBUTTON object</a></b>, A radio button is an option button that can be switched on (checked) or off (unchecked), the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"text":</td><td><a href="#STRING">STRING</a>,</td><td>// Text displayed on the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"font":</td><td><a href="#FONT">FONT</a>,</td><td>// Font used in display of text</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="SCROLLVIEW">SCROLLVIEW object</a></b>, A scroll view is used to display the contents of many children widget within a frame, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="SIGNATURE">SIGNATURE object</a></b>, This class is used to play movie or sound, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"penwidth":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Pen width in pixels</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="TIMER">TIMER object</a></b>, Repetitive timers, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"enabled":</td><td><a href="#BOOL">BOOL</a>,</td><td>// true indicates that the timer is automaticaly started at the creation, false indicates that is not started</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"interval":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Interval of timer in milliseconds</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="UNIT">UNIT enumeration, </a></b> Unit supported by the graphical library., the different values used are : 
<table border=0 cellspacing=0 cellpadding=0>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"pixel"</td><td> : Dimensions or position are expressed in pixels</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"percent"</td><td> : Dimensions or position are expressed in percentage of parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"perthousand"</td><td> : Dimensions or position are expressed in per thousand of parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"px"</td><td> : Dimensions or position are expressed in pixels</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"%"</td><td> : Dimensions or position are expressed in percentage of parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"%%"</td><td> : Dimensions or position are expressed in per thousand of parent</td></tr>
</table><br>
<b><a name="SIZE">SIZE object</a></b>, Defines a size, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"width":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Width coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"height":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Height coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"unit":</td><td><a href="#UNIT">UNIT</a>,</td><td>// Unit used</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="POSITION">POSITION object</a></b>, Defines a position, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"x":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// x coordinates coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"y":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// y coordinates coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"unit":</td><td><a href="#UNIT">UNIT</a>,</td><td>// Unit used</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="MARGINS">MARGINS object</a></b>, Defines all margins, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"left":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Left margin coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"top":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Top margin coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"right":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Right margin coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"bottom":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Bottom margin coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"unit":</td><td><a href="#UNIT">UNIT</a>,</td><td>// Unit used</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="PADDINGS">PADDINGS object</a></b>, Defines a paddings, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"left":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Left padding coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"top":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Top padding coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"right":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Right padding coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"bottom":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Bottom padding coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"unit":</td><td><a href="#UNIT">UNIT</a>,</td><td>// Unit used</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="BORDERS">BORDERS object</a></b>, Defines a borders, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"left":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Left border coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"top":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Top border coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"right":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Right border coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"bottom":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Bottom border coded according to the chosen unit</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"unit":</td><td><a href="#UNIT">UNIT</a>,</td><td>// Unit used</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"color":</td><td><a href="#COLOR">COLOR</a>,</td><td>// border color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="RANGE">RANGE object</a></b>, Range, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"min":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// The minimum limit of the scroll bar</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"max":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// The maximum limit of the scroll bar</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"value":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// The value of the scroll bar</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"page":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// The page size of the scroll bar (scales the size of slider in the scrollbar)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"step":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// The step increment</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="MAPPAGE">MAPPAGE object</a></b>, Page of characters displayed on the virtual keyboard, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"name":</td><td><a href="#STRING">STRING</a>,</td><td>// Page name displayed in the button page selection</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"mapping":</td><td><a href="#STRING">STRING</a>,</td><td>// List of characters in the page content, use \\n to change the line, use \\uXXXX to enter an unicode value</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="PAGES">PAGES</a> array</b>, List of drawing actions, the different elements that can be used in this array are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>[</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#MAPPAGE">MAPPAGE</a>,</td><td>// Mapping definition of the binary virtual keyboard</td></tr>
<tr><td>]</td></tr></table><br>
<b><a name="VIRTUALKEYBOARD">VIRTUALKEYBOARD object</a></b>, The virtual keyboard allows easy entry of special characters, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"font":</td><td><a href="#FONT">FONT</a>,</td><td>// Font used in display of text</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"fillchar1":</td><td><a href="#CHARACTER">CHARACTER</a>,</td><td>// Sets the default fill character 1 (This character appears only in fields with an input mask defined)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"fillchar2":</td><td><a href="#CHARACTER">CHARACTER</a>,</td><td>// Sets the default fill character 2 (This character appears only in fields with an input mask defined)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"mask":</td><td><a href="#STRING">STRING</a>,</td><td>// mask string handle, see 'Mask properties' in the documentation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"mode":</td><td><a href="#INPUTMODE">INPUTMODE</a>,</td><td>// Configure the input mode</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"passwordchar":</td><td><a href="#CHARACTER">CHARACTER</a>,</td><td>// Sets the default password character (This character appears only in fields with an input mask defined)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"text":</td><td><a href="#STRING">STRING</a>,</td><td>// Text displayed on the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"binary":</td><td><a href="#PAGES">PAGES</a>,</td><td>// Mapping definition of the binary virtual keyboard</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"octal":</td><td><a href="#PAGES">PAGES</a>,</td><td>// Mapping definition of the octal virtual keyboard</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"decimal":</td><td><a href="#PAGES">PAGES</a>,</td><td>// Mapping definition of the decimal virtual keyboard</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"hexadecimal":</td><td><a href="#PAGES">PAGES</a>,</td><td>// Mapping definition of the hexadecimal virtual keyboard</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"alphanumeric":</td><td><a href="#PAGES">PAGES</a>,</td><td>// Mapping definition of the alphanumerical virtual keyboard</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"anychar":</td><td><a href="#PAGES">PAGES</a>,</td><td>// Mapping definition of the any character virtual keyboard</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"userchar":</td><td><a href="#CHARACTER">CHARACTER</a>,</td><td>// String that contains the set of characters accepted by the user character mask (/u or /U)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"usermapping":</td><td><a href="#PAGES">PAGES</a>,</td><td>// Mapping definition of the any user character virtual keyboard</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="VSCROLLBAR">VSCROLLBAR object</a></b>, A scroll bar is a control that enables the user to access parts of a document that is larger than the widget used to display it, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"range":</td><td><a href="#RANGE">RANGE</a>,</td><td>// Range</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="TELIUMKEY">TELIUMKEY enumeration, </a></b> Telium keys values, the different values used are : 
<table border=0 cellspacing=0 cellpadding=0>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\u0030"</td><td> : Telium numeric 0 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\u0031"</td><td> : Telium numeric 1 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\u0032"</td><td> : Telium numeric 2 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\u0033"</td><td> : Telium numeric 3 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\u0034"</td><td> : Telium numeric 4 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\u0035"</td><td> : Telium numeric 5 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\u0036"</td><td> : Telium numeric 6 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\u0037"</td><td> : Telium numeric 7 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\u0038"</td><td> : Telium numeric 8 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\u0039"</td><td> : Telium numeric 9 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\u002E"</td><td> : Telium dot key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\uF850"</td><td> : Telium green key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\uF851"</td><td> : Telium red key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\uF852"</td><td> : Telium yellow key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\uF853"</td><td> : Telium paper feed key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\uF854"</td><td> : Telium function key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\uF855"</td><td> : Telium function 1 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\uF856"</td><td> : Telium function 2 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\uF857"</td><td> : Telium function 3 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\uF858"</td><td> : Telium function 4 key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\uF859"</td><td> : Telium up arrow key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\uF85A"</td><td> : Telium down arrow key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\uF86B"</td><td> : Telium ok key</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"\uF86C"</td><td> : Telium clear key</td></tr>
</table><br>
<b><a name="TELIUMKEY">TELIUMKEY</a></b> : <br>
<b><a name="IDNAMEREF">IDNAMEREF</a></b> : <br>
<b><a name="COLOR">COLOR</a></b> : (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)<br>
<b><a name="CHARACTER">CHARACTER</a></b> : Character definition. This is the unicode key keyboard see GL_KEY_ in the documentation<br>
<b><a name="CHILDREN">CHILDREN</a> array</b>, Widget children, the different elements that can be used in this array are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>[</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#BUTTON">BUTTON</a>,</td><td>// The button to command the terminal to perform some action, or to answer a question</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#CHECKBUTTON">CHECKBUTTON</a>,</td><td>// A check button is an option button that can be switched on (checked) or off (unchecked)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#DRAWING">DRAWING</a>,</td><td>// the drawing widget is a surface on which the user can draw a graph</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#EDIT">EDIT</a>,</td><td>// The edit widget provides a widget that is used to edit a single line of text.</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#HSCROLLBAR">HSCROLLBAR</a>,</td><td>// A scroll bar is a control that enables the user to access parts of a document that is larger than the widget used to display it</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#HSLIDER">HSLIDER</a>,</td><td>// The slider is the classic widget for controlling a bounded value. It lets the user move a slider handle along groove and translates the handle's position into an integer value within the legal range</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ICON">ICON</a>,</td><td>// The class icon is equivalent to a button, it allows the display of an image more</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#ICONBUTTON">ICONBUTTON</a>,</td><td>// This class is an icon followed by a button</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#LABEL">LABEL</a>,</td><td>// This class is used to display text on a line or a multi-line text</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#LAYOUT">LAYOUT</a>,</td><td>// The layout can be viewed as a table with multiple rows and columns to place widgets</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#LIST">LIST</a>,</td><td>// The list allows the display of all elements of widgets</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#MEDIA">MEDIA</a>,</td><td>// This class is used to play movie or sound</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#PALETTE">PALETTE</a>,</td><td>// A palette is a widget that can display a color palette</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#PICTURE">PICTURE</a>,</td><td>// A picture is a widget that can display a fixed image or animated image</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#PLUGIN">PLUGIN</a>,</td><td>// The plugin is used to manage a generic DLL plugin</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#PRINT">PRINT</a>,</td><td>// This class is used to print text on a line or a multi-line text on the printer</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#PROGRESSBAR">PROGRESSBAR</a>,</td><td>// A progress bar is used to give the user an indication of the progress of an operation </td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#RADIOBUTTON">RADIOBUTTON</a>,</td><td>// A radio button is an option button that can be switched on (checked) or off (unchecked)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#SCROLLVIEW">SCROLLVIEW</a>,</td><td>// A scroll view is used to display the contents of many children widget within a frame</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#SIGNATURE">SIGNATURE</a>,</td><td>// This class is used to capture a signature</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#TIMER">TIMER</a>,</td><td>// Repetitive timers</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#VIRTUALKEYBOARD">VIRTUALKEYBOARD</a>,</td><td>// The virtual keyboard allows easy entry of special characters</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#VSCROLLBAR">VSCROLLBAR</a>,</td><td>// A scroll bar is a control that enables the user to access parts of a document that is larger than the widget used to display it</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td><a href="#BARCODE">BARCODE</a>,</td><td>// This widget can display a barcode</td></tr>
<tr><td>]</td></tr></table><br>
<b><a name="ITEM">ITEM object</a></b>, Unit used by the coordinates or sizes, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"column":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Column number in the layout (first row = 0) </td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"row":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Row number in the layout (first column = 0)</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="ALIGN">ALIGN enumeration, </a></b> Item alignement, the different values used are : 
<table border=0 cellspacing=0 cellpadding=0>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"center"</td><td> : The item is placed in the center</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"top"</td><td> : The item is placed in vertical on the top</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"bottom"</td><td> : The item is placed in vertical on the bottom</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"left"</td><td> : The item is placed in horizontal on the left</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"right"</td><td> : The item is placed in horizontal on the right</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"top,left"</td><td> : The item is placed in the top left corner</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"top,right"</td><td> : The item is placed in the top right corner</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"bottom,left"</td><td> : The item is placed in the bottom left corner</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"bottom,right"</td><td> : The item is placed in the bottom right corner</td></tr>
</table><br>
<b><a name="TRANSFORMATION">TRANSFORMATION enumeration, </a></b> Image transformation, the different values used are : 
<table border=0 cellspacing=0 cellpadding=0>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"none"</td><td> : No treatment of the image : if the image is too large it will be truncated, if it is too small it will be displayed as it is</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"repeatx"</td><td> : The image is repeated on the x-axis</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"repeaty"</td><td> : The image is repeated on the y-axis</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"repeatall"</td><td> : The image is repeated on all directions</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"stretchx"</td><td> : The image is stretched along the x-axis only</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"stretchy"</td><td> : The image is stretched along the y-axis only</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"stretchall"</td><td> : The image is stretched along the all directions</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"fitx"</td><td> : The image will keep its width height ratio, but will be adapted on the X axis, if the image is too high it will be truncated</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"fity"</td><td> : The image will keep its width height ratio, but will be adapted on the Y axis, if the image is too large it will be truncated</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"fitall"</td><td> : The image size will be adapted to fit exactly to the space without distortion</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"repeatxstretchy"</td><td> : The image is repeated on the x-axis and stretched along the y-axis</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"repeatystretchx"</td><td> : The image is repeated on the y-axis and stretched along the x-axis</td></tr>
</table><br>
<b><a name="DIRECTION">DIRECTION enumeration, </a></b> Direction of the change in size, the different values used are : 
<table border=0 cellspacing=0 cellpadding=0>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"width"</td><td> : Authorizes a change in size in width</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"height"</td><td> : Authorizes a change in size in height</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"all"</td><td> : Authorizes a change in size all direction</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"none"</td><td> : Prohibits any change in size</td></tr>
</table><br>
<b><a name="STATE">STATE enumeration, </a></b> State to consider whether to display the widget, the different values used are : 
<table border=0 cellspacing=0 cellpadding=0>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focused"</td><td> : The widget has focus</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"unfocused"</td><td> : The widget has not focus</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"checked"</td><td> : The widget is checked</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"unchecked"</td><td> : The widget is not checked</td></tr>
</table><br>
<b><a name="SOURCEFILE">SOURCEFILE</a></b> : Source file name  (file name can contain alphanumeric, underscore, minus, spaces characters)<br>
<b><a name="INPUTMODE">INPUTMODE object</a></b>, Configure the input mode, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"blank":</td><td><a href="#BOOL">BOOL</a>,</td><td>// false:hide the blank part of input, true:show the blank part of input</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"password":</td><td><a href="#BOOL">BOOL</a>,</td><td>// false:The characters entered are displayed, true:The characters entered are replaced by the '*' (used to enter password)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"prompt":</td><td><a href="#BOOL">BOOL</a>,</td><td>// false:hide the prompt, true:show the prompt</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"replace":</td><td><a href="#BOOL">BOOL</a>,</td><td>// false:The characters entered are inserted into the input field, true:The characters entered replace existing characters in the input field</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"zeroSignificant":</td><td><a href="#BOOL">BOOL</a>,</td><td>// false:The zeros are not displayed in the early numbers, true:The zeros are displayed in the early numbers (eg 000123)</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="WINDOW">WINDOW object</a></b>, This widget allows management of a window on the screen, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"id":</td><td><a href="#INTEGER">INTEGER</a>,</td><td>// Id to identify single and unique widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"children":</td><td><a href="#CHILDREN">CHILDREN</a>,</td><td>// Children items attached to this widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"item":</td><td><a href="#ITEM">ITEM</a>,</td><td>// Location in the layout</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"grow":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be growed (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shrink":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can be shrunk (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"expand":</td><td><a href="#DIRECTION">DIRECTION</a>,</td><td>// Indicates that the widget can get as much space as possible (only in case if it is placed in a layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the background relative to its parent</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forealign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of the foreground relative to the background</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"textalign":</td><td><a href="#ALIGN">ALIGN</a>,</td><td>// Alignment of text in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"margins":</td><td><a href="#MARGINS">MARGINS</a>,</td><td>// Margins around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"borders":</td><td><a href="#BORDERS">BORDERS</a>,</td><td>// Borders around the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"paddings":</td><td><a href="#PADDINGS">PADDINGS</a>,</td><td>// Text paddings in the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"backcolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Background color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"forecolor":</td><td><a href="#COLOR">COLOR</a>,</td><td>// Foreground or text color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"shortcut":</td><td><a href="#TELIUMKEY">TELIUMKEY</a>,</td><td>// Keyboard shortcut to a widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"visible":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates if the object is visible (true) or not (false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"state":</td><td><a href="#STATE">STATE</a>,</td><td>// State of the widget has its creation</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"statemask":</td><td><a href="#STATE">STATE</a>,</td><td>// Mask on the state, the widget will be visible only when the state is identical to the mask defined</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"focusable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget can receive focus (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clickable":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that the widget sends a click event (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"clicksensitive":</td><td><a href="#BOOL">BOOL</a>,</td><td>// Indicates that this widget is sensitive pen click (true/false)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"position":</td><td><a href="#POSITION">POSITION</a>,</td><td>// Position of widget in its parent (WARNING : if it set the widget will be removed from its parent layout)</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"maxsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Maximal size of the widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"minsize":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Minimal size of the widget</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="FONTSIZE">FONTSIZE object</a></b>, Defines a size, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"height":</td><td><a href="#FONTSIZES">FONTSIZES</a>,</td><td>// Font height</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="FONTSIZES">FONTSIZES enumeration, </a></b> Unit supported by the graphical library., the different values used are : 
<table border=0 cellspacing=0 cellpadding=0>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>0x3FF0</td><td> : Extra extra small font size</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>0x3FF1</td><td> : Extra small font size</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>0x3FF2</td><td> : Small font size</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>0x3FF3</td><td> : Medium font size</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>0x3FF4</td><td> : Large font size</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>0x3FF5</td><td> : Extra large font size</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>0x3FF6</td><td> : Extra extra large font size</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>5</td><td> : font size 5</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>6</td><td> : font size 6</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>7</td><td> : font size 7</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>8</td><td> : font size 8</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>9</td><td> : font size 9</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>10</td><td> : font size 10</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>11</td><td> : font size 11</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>12</td><td> : font size 12</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>13</td><td> : font size 13</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>14</td><td> : font size 14</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>15</td><td> : font size 15</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>16</td><td> : font size 16</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>17</td><td> : font size 17</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>18</td><td> : font size 18</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>19</td><td> : font size 19</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>20</td><td> : font size 20</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>21</td><td> : font size 21</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>22</td><td> : font size 22</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>23</td><td> : font size 23</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>24</td><td> : font size 24</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>25</td><td> : font size 25</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>26</td><td> : font size 26</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>27</td><td> : font size 27</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>28</td><td> : font size 28</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>29</td><td> : font size 29</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>30</td><td> : font size 30</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>31</td><td> : font size 31</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>32</td><td> : font size 32</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>33</td><td> : font size 33</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>34</td><td> : font size 34</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>35</td><td> : font size 35</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>36</td><td> : font size 36</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>37</td><td> : font size 37</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>38</td><td> : font size 38</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>39</td><td> : font size 39</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>40</td><td> : font size 40</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>41</td><td> : font size 41</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>42</td><td> : font size 42</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>43</td><td> : font size 43</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>44</td><td> : font size 44</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>45</td><td> : font size 45</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>46</td><td> : font size 46</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>47</td><td> : font size 47</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>48</td><td> : font size 48</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>49</td><td> : font size 49</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>50</td><td> : font size 50</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>51</td><td> : font size 51</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>52</td><td> : font size 52</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>53</td><td> : font size 53</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>54</td><td> : font size 54</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>55</td><td> : font size 55</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>56</td><td> : font size 56</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>57</td><td> : font size 57</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>58</td><td> : font size 58</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>59</td><td> : font size 59</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>60</td><td> : font size 60</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>61</td><td> : font size 61</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>62</td><td> : font size 62</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>63</td><td> : font size 63</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>64</td><td> : font size 64</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>65</td><td> : font size 65</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>66</td><td> : font size 66</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>67</td><td> : font size 67</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>68</td><td> : font size 68</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>69</td><td> : font size 69</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>70</td><td> : font size 70</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>71</td><td> : font size 71</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>72</td><td> : font size 72</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>73</td><td> : font size 73</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>74</td><td> : font size 74</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>75</td><td> : font size 75</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>76</td><td> : font size 76</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>77</td><td> : font size 77</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>78</td><td> : font size 78</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>79</td><td> : font size 79</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>80</td><td> : font size 80</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>81</td><td> : font size 81</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>82</td><td> : font size 82</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>83</td><td> : font size 83</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>84</td><td> : font size 84</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>85</td><td> : font size 85</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>86</td><td> : font size 86</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>87</td><td> : font size 87</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>88</td><td> : font size 88</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>89</td><td> : font size 89</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>90</td><td> : font size 90</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>91</td><td> : font size 91</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>92</td><td> : font size 92</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>93</td><td> : font size 93</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>94</td><td> : font size 94</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>95</td><td> : font size 95</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>96</td><td> : font size 96</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>97</td><td> : font size 97</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>98</td><td> : font size 98</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>99</td><td> : font size 99</td></tr>
</table><br>
<b><a name="FONT">FONT object</a></b>, Font used in display of text, the different elements that can be used in the object are : 
<table border=0 cellspacing=0 cellpadding=0><tr><td>{</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"name":</td><td><a href="#STRING">STRING</a>,</td><td>// Font name</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"size":</td><td><a href="#SIZE">SIZE</a>,</td><td>// Font size</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"style":</td><td><a href="#FONTSTYLE">FONTSTYLE</a>,</td><td>// Font style (bold, italic, normal, ...)</td></tr>
<tr><td>}</td></tr></table><br>
<b><a name="FONTSTYLE">FONTSTYLE enumeration, </a></b> Possible font style , the different values used are : 
<table border=0 cellspacing=0 cellpadding=0>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"normal"</td><td> : Normal style</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"italic"</td><td> : Italic style</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"bold"</td><td> : Bold style</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>"bold,italic"</td><td> : Bold italic style</td></tr>
</table><br>
<b><a name="BOOL">BOOL enumeration, </a></b> boolean, the different values used are : 
<table border=0 cellspacing=0 cellpadding=0>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>true</td><td> : True value</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;&nbsp;</td><td>false</td><td> : False value</td></tr>
</table><br>

<br><b><a name="INTEGER">INTEGER</a></b> : integer (-2147483647 to 2147483647)<br>
<br><b><a name="BYTE">BYTE</a></b> : byte (-127 to 128 or 0 to 255) <br>
<br><b><a name="SHORT">SHORT</a></b> : byte (-32768 to 32768 or 0 to 65535) <br>
@}
@}
*/