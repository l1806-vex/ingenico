/**

@addtogroup GL_Json
@{
@addtogroup GL_JsonDoc
@{
@section GL_JsonIntroduction Introduction
This section describes the syntax used to create JSON files resource.
This format is natively supported by GOAL, it is interpreted and therefore requires no compilation.
All skins used in GOAL are in Json format.

<hr>@section GL_JsonFormat Json format

In JSON, they data stored in a file take on these forms :

An object is an unordered set of name/value pairs. An object begins with { (left brace) and ends with } (right brace). Each name is followed by : (colon) and the name/value pairs are separated by , (comma).

@image html JsonObject.png

An array is an ordered collection of values. An array begins with [ (left bracket) and ends with ] (right bracket). Values are separated by , (comma).

@image html JsonArray.png

A value can be a string in double quotes, or a number, or true or false or null, or an object or an array. These structures can be nested.

@image html JsonValue.png

A string is a sequence of zero or more utf8 characters, wrapped in double quotes, using backslash escapes. A character is represented as a single character string. A string is very much like a C or Java string.

@image html JsonString.png

A number is very much like a C or Java number, the octal, binary and hexadecimal formats can be used.

@image html JsonNumber.png

Whitespace can be inserted between any pair of tokens. Excepting a few encoding details, that completely describes the language.

A comment line is like a C comment :

@image html JsonLineComment.png

A comment block of lines is like a C comment :

@image html JsonBlockComment.png

@section GL_JsonGoal Json in GOAL

A widget must be typed with the following json object : 

@code
{
    "type":"widget", 
    // add here other attributes of your widget
}
@endcode

Replace "widget" by the name of widget. The names of the types of widgets must be lowercase.

@section GL_JsonSample A example of resource file in JSON format

@code
// This resource file defines a window with a label and a button.
{                                      // The braces allows the description of an object 
  "type"        : "window",            // Defines an object of type window
  "backcolor"   : 0xFFFF0000,          // Defines the backcolor in red
  "children"    :                      // Adds children into the window
  [                                    // The brackets define a array of objects
    {
      "type"    : "layout",            // Defines an object of type layout
      "children":                      // Adds children into the layout
      [
        {                        
          "type"     : "label",        // Defines an object of type label
          "backcolor": 0xFF0000FF,     // Defines the backcolor in blue
          "text"     : "Hello world",  // Sets the text "Hello world" into the label
          "item"     :                 // Place the button in the layout 
          {
            "row"    : 0,
            "column" : 0
          }
        },
        {
          "type"     : "button",       // Defines an object of type button
          "text"     : "Ok",           // Sets the text "Ok" into the button
          "item"     :                 // Place the button in the layout
          {
            "row"    : 1,
            "column" : 0
          }
        }
      ]
    }
  ]
}
@endcode

<b>Remember to put commas between objects, otherwise it produces a syntax error.

To find syntax errors you can use @ref GL_GraphicLib_GetErrorMessages.</b>


You must write the content in a file. To create the GOAL resource, you can use: 
	- @ref GL_GraphicLib_ReadResource : the first object in the file must be either a window or document 
	- @ref GL_Widget_ReadResource : the first object in the file must be different of a window or document 

If you write the file to the host, to read it you should do: 
@code
	window = GL_GraphicLib_ReadResource(graphicLib, "file://flash/HOST/FILE.JS");
@endcode

You can also sign your file and pack into a tar file, to read it you should do: 
@code
	window = GL_GraphicLib_ReadResource(graphicLib, "file://param/TARFILE.TAR/FILE.JS");
@endcode




@}
@}
****************************************************************************************
****************************************************************************************
****************************************************************************************
@addtogroup GL_Skin
@{

@addtogroup GL_SkinArchiveFile
@{

@section GL_SkinIntroduction Introduction

This section describes the contents of a skin archive file used for GOAL.
A skin is used to describe the look of all widgets and that for every screen resolution.


@section GL_SkinContent Skin content

All the files used in a skin are gathered in a TAR, the files contained in this archive are : 
	<table border=0 cellspacing=0 cellpadding=0>

<tr><td><b>Main files</b></td><td>These files are mandatory and must have the same name and location in the archive of the skin</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; skins.js               </td><td> This is the index file of all the skins of various widgets. See @ref GL_SkinSkinsJs</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; graphiclib.js          </td><td> This file contains all the scales fonts depending on screen resolution. See @ref GL_SkinGraphicLibJs </td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; colors.js              </td><td> This file defines the overload color values to all of the skin (@ref GL_SkinColors). See @ref GL_SkinColorsJs</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp;</td><td>&nbsp;&nbsp;&nbsp;</td></tr>
		<tr><td><b>Text widgets skins</b></td><td>See @ref GL_SkinTextWidgets</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; label.js               </td><td> Defines the skin for the @ref GL_Label widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; print.js               </td><td> Defines the skin for the print @ref GL_Print widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; button.js              </td><td> Defines the skin for the @ref GL_Button widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; checkbutton.js         </td><td> Defines the skin for the @ref GL_CheckButton widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; radiobutton.js         </td><td> Defines the skin for the @ref GL_RadioButton widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; iconbutton.js          </td><td> Defines the skin for the @ref GL_IconButton widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; icon.js                </td><td> Defines the skin for the @ref GL_Icon widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; edit.js                </td><td> Defines the skin for the @ref GL_Edit widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; virtualkeyboard.js     </td><td> Defines the skin for the @ref GL_VirtualKeyboard widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; key.js                 </td><td> Defines the skin for the key widget used in the @ref GL_VirtualKeyboard</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;</td><td>&nbsp;&nbsp;&nbsp;</td></tr>
<tr><td><b>Bar and slider widgets skins</b></td><td>See @ref GL_SkinBarSliderWidgets</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; vscrollbar.js          </td><td> Defines the skin for the @ref GL_VScrollBar widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; hscrollbar.js          </td><td> Defines the skin for the @ref GL_HScrollBar widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; progressbar.js         </td><td> Defines the skin for the @ref GL_ProgressBar widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; hslider.js             </td><td> Defines the skin for the @ref GL_HSlider widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;</td><td>&nbsp;&nbsp;&nbsp;</td></tr>
<tr><td><b>Graphical widgets skins</b></td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; palette.js             </td><td> Defines the skin for the @ref GL_Palette widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; signature.js           </td><td> Defines the skin for the @ref GL_Signature widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;</td><td>&nbsp;&nbsp;&nbsp;</td></tr>
<tr><td><b>Container widgets skins</b></td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; list.js                </td><td> Defines the skin for the @ref GL_List widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; window.js              </td><td> Defines the skin for the @ref GL_Window widget</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;</td><td>&nbsp;&nbsp;&nbsp;</td></tr>
<tr><td><b>Dialogs skins</b></td><td>See @ref GL_SkinDialog</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialog.js              </td><td> Defines the skin for the @ref GL_Dialog widget</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/title.js       </td><td> Defines the part containing the title of all dialog @ref GL_Dialog</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/buttons.js     </td><td> Defines the part containing the buttons of all dialog @ref GL_Dialog</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;</td><td>&nbsp;&nbsp;&nbsp;</td></tr>
<tr><td><b>List dialogs skins</b></td><td>See @ref GL_DialogListDoc</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/list.js        </td><td> Defines the content of dialog @ref GL_Dialog_Menu, @ref GL_Dialog_IconMenu, @ref GL_Dialog_IconButtonMenu, @ref GL_Dialog_Choice, @ref GL_Dialog_MultiChoice</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;</td><td>&nbsp;&nbsp;&nbsp;</td></tr>
<tr><td><b>File dialogs skins</b></td><td>See @ref GL_DialogFileDoc</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/file.js        </td><td> Defines the content of dialog @ref GL_Dialog_File, @ref GL_Dialog_MultiFile</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;</td><td>&nbsp;&nbsp;&nbsp;</td></tr>
<tr><td><b>Message dialogs skins</b></td><td>See @ref GL_DialogMessageDoc</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/message.js     </td><td> Defines the content of dialog @ref GL_Dialog_Message</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/media.js       </td><td> Defines the content of dialog @ref GL_Dialog_Media</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/picture.js     </td><td> Defines the content of dialog @ref GL_Dialog_Picture</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;</td><td>&nbsp;&nbsp;&nbsp;</td></tr>
<tr><td><b>Input dialogs skins</b></td><td>See @ref GL_DialogInputDoc</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/input.js       </td><td> Defines the content of dialog @ref GL_Dialog_Password, @ref GL_Dialog_Text, @ref GL_Dialog_Date, @ref GL_Dialog_Ip, @ref GL_Dialog_Amount</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/keyboard.js    </td><td> Defines the content of dialog @ref GL_Dialog_VirtualKeyboard</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/color.js       </td><td> Defines the content of dialog @ref GL_Dialog_Color</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/progress.js    </td><td> Defines the content of dialog @ref GL_Dialog_Progress</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/scheme.js      </td><td> Defines the content of dialog @ref GL_Dialog_Scheme</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/signature.js   </td><td> Defines the content of dialog @ref GL_Dialog_Signature</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; dialogs/slider.js      </td><td> Defines the content of dialog @ref GL_Dialog_Slider</td></tr>
<tr><td>&nbsp;&nbsp;&nbsp;</td><td>&nbsp;&nbsp;&nbsp;</td></tr>
<tr><td><b>Images used in skins</b></td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; images/question.wgu    </td><td> Image question displayed on the dialog box message @ref GL_Dialog_Message</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; images/information.wgu </td><td> Image information displayed on the dialog box message @ref GL_Dialog_Message</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; images/error.wgu       </td><td> Image error displayed on the dialog box message @ref GL_Dialog_Message</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; images/warning.wgu     </td><td> Image warning displayed on the dialog box message @ref GL_Dialog_Message</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; images/correction.wgu  </td><td> Image displayed on the correction button of dialog box @ref GL_Dialog</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; images/cancel.wgu      </td><td> Image displayed on the cancel button of dialog box @ref GL_Dialog</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; images/validation.wgu  </td><td> Image displayed on the validation button of dialog box @ref GL_Dialog</td></tr>
		<tr><td>&nbsp;&nbsp;&nbsp; images/*.wgu           </td><td> Other images used in all widgets must be placed in this folder</td></tr>
	</table>


@section GL_SkinName Skin name

The name of a skin is composed of the following pattern "[<b>Name</b>]_SK[<b>Width</b>]_[<b>Height</b>]" 
   - <b>Name</b> : name of skin (Default name "GOAL")
   - <b>Width</b> : screen width in pixels
   - <b>Height</b> : screen height in pixels

The total length of the name is limited to 16 characters. This name must be placed by the signing tool, it is the family name of the component.

To find the skin file relating to the resolution of a screen see @ref GL_BinaryComponent and search the family string "GOAL_SK".

Then search the filename found in the SDK directory "C:\Program Files\SDK30\SDK x.x\tools\Ingedev\GOAL\skins\fileSystem\flash\SYSTEM".
This skin format is a true TAR format that can be unpacked with any executable decompression.

@}

****************************************************************************************
****************************************************************************************
****************************************************************************************

@addtogroup GL_SkinTextWidgets 
@{

The button, check button, radio button, icon, icon button, and edit  widgets share the same operating principle.
We will explain the creation of a skin through the example of the check button.

A button has the ability to expand, it is composed of several images :
	- an image with the right side, 
	- an image repeated several times in the center, 
	- an image containing the left edge,

To differentiate the state of a button with and without the focus you have to repeat this pattern twice : 
	- one with a focus light blue, 
	- and an unfocused dark blue

Since this is a check button you must have two images of the check box : 
	- checked image 
	- and unchecked image

Not forgetting to add text label.

Each image is placed in a given cell of the layout

We obtain three-dimensional:

@image html Skin.png

The description of the skin file check button starts with :

@code
{
	// Defines the type of widget you want to describe the skin (here is check button)
	"type":"checkbutton",
	
	// The following property is use to generate the @ref GL_EVENT_STYLUS_CLICK event when you click 
	// with the stylus on the layout, you must set the property at true
	"clickable":true,      
	
	// The following property indicates that the widget can receive focus.
	"focusable":true,
	
	// Enables the cell of layout to grows in width direction only
	"grow":"all",
	
	// Disables the cell of layout to shrink in all the directions
	"shrink":"none",
	
	// This property defines children of check button
	"children":
	[
@endcode

The following paragraph describes the part that shows the focus of check button :

@code
		// Defines the left image of the focus
		{
			// Define the type of widget here it is a picture
			"type"          :"picture",
			
			// Positions the image in the second column of the layout (the first column is occupied by the box)
			"item"          :{"column":1, "row":0},
			
			// The following property indicates that the image is displayed only when the widget have the focus
			"statemask"     :"focused",
			
			// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
			"source"        :"/images/ButFocus(Left).wgu",
			
			// Strength of the cell layout to have a fixed width.
			// If we do not specify the height it has the capacity to expand in height.
			"size"          :{"width":7},
			
			// Force a margin at the top and bottom of the image
			"margins"       :{"left":3, "top":2, "right":0, "bottom":2},
			
			// Aligns the image to see the left edge of the image
			"forealign"     :"left",
			
			// Allows the image to stretch in y
			"transformation":"stretchy",
			
			// Allows the cell's layout to stretch in height
			"expand"        :"height",
			
			// Allows the cell's layout to shrink in height
			"shrink"        :"height",

			// The following property defines that the areas are sensitive to clicks. 
			"clicksensitive":true,
		},
		
		// Defines the center image of the focus
		{
			// Define the type of widget here it is a picture
			"type":"picture",
			
			// Positions the image in the third column of the layout (the first column is occupied by the box)
			"item":{"column":2, "row":0},
			
			// The following property indicates that the image is displayed only when the widget have the focus
			"statemask":"focused",
			
			// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
			"source":"/images/ButFocus(center).wgu",
			
			// Force a margin at the top and bottom of the image
			"margins":{"left":0, "top":2, "right":0, "bottom":2},
			
			// Allows the image to stretch in y and repeated in x
			"transformation":"repeatxstretchy",
			
			// Allows the widget to expand its background in all directions
			"expand":"all",
			
			// Allows the cell of layout to shrink in all the directions
			"shrink":"all",

			// The following property defines that the areas are sensitive to clicks. 
			"clicksensitive":true,
		},

		// Defines the right image of the focus
		{
			// Define the type of widget here it is a picture
			"type":"picture",

			// Positions the image in the fourth column of the layout (the first column is occupied by the box)
			"item":{"column":3, "row":0},

			// The following property indicates that the image is displayed only when the widget have the focus
			"statemask":"focused",

			// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
			"source":"/images/ButFocus(right).wgu",

			// Strength of the cell layout to have a fixed width.
			// If we do not specify the height it has the capacity to expand in height.
			"size":{"width":7},

			// Force a margin at the top and bottom of the image
			"margins":{"left":0, "top":2, "right":3, "bottom":2},

			// Aligns the image to see the right edge of the image
			"forealign":"right",

			// Allows the image to stretch in y
			"transformation":"stretchy",

			// Allows the cell's layout to stretch in height
			"expand":"height",

			// Allows the cell's layout to shrink in height
			"shrink":"height",

			// The following property defines that the areas are sensitive to clicks. 
			"clicksensitive":true,
		},
@endcode

The following paragraph describes the part that shows the unfocus of check button.
It is similar with the previous paragraph except the statemask and the source image :

@code
		// Defines the left image of the unfocus
		{
			// Define the type of widget here it is a picture
			"type":"picture",
			
			// Positions the image in the second column of the layout (the first column is occupied by the box)
			"item":{"column":1, "row":0},
			
			// The following property indicates that the image is displayed only when the widget have not the focus
			"statemask":"unfocused",
			
			// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
			"source":"/images/Button(left).wgu", 
			
			// Strength of the cell layout to have a fixed width.
			// If we do not specify the height it has the capacity to expand in height.
			"size":{"width":7},
			
			// Force a margin at the top and bottom of the image
			"margins":{"left":3, "top":2, "right":0, "bottom":2},
			
			// Aligns the image to see the left edge of the image
			"forealign":"left",
			
			// Allows the image to stretch in y
			"transformation":"stretchy",
			
			// Allows the cell's layout to stretch in height
			"expand":"height",
			
			// Allows the cell's layout to shrink in height
			"shrink":"height",

			// The following property defines that the areas are sensitive to clicks. 
			"clicksensitive":true,
		},
		
		// Defines the center image of the unfocus
		{
			// Define the type of widget here it is a picture
			"type":"picture",
			
			// Positions the image in the third column of the layout (the first column is occupied by the box)
			"item":{"column":2, "row":0},
			
			// The following property indicates that the image is displayed only when the widget have not the focus
			"statemask":"unfocused",
			
			// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
			"source":"/images/Button(center).wgu",
			
			// Force a margin at the top and bottom of the image
			"margins":{"left":0, "top":2, "right":0, "bottom":2},
			
			// Allows the image to stretch in y and repeated in x
			"transformation":"repeatxstretchy",
			
			// Allows the widget to expand its background in all directions
			"expand":"all",
			
			// Allows the cell of layout to shrink in all the directions
			"shrink":"all",

			// The following property defines that the areas are sensitive to clicks. 
			"clicksensitive":true,
		},
		
		// Defines the right image of the unfocus
		{
			// Define the type of widget here it is a picture
			"type":"picture",
			
			// Positions the image in the fourth column of the layout (the first column is occupied by the box)
			"item":{"column":3, "row":0},
			
			// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
			"source":"/images/Button(right).wgu",
			
			// The following property indicates that the image is displayed only when the widget have not the focus
			"statemask":"unfocused",
			
			// Strength of the cell layout to have a fixed width.
			// If we do not specify the height it has the capacity to expand in height.
			"size":{"width":7},
			
			// Force a margin at the top and bottom of the image
			"margins":{"left":0, "top":2, "right":3, "bottom":2},
			
			// Aligns the image to see the right edge of the image
			"forealign":"right",
			
			// Allows the image to stretch in y
			"transformation":"stretchy",
			
			// Allows the cell's layout to stretch in height
			"expand":"height",
			
			// Allows the cell of layout to shrink in height the directions
			"shrink":"height",

			// The following property defines that the areas are sensitive to clicks. 
			"clicksensitive":true,
		},
@endcode

The following paragraph describes the part that shows the uncheck.
For the :
	- color see @ref GL_SkinColors.
	- specific id see @ref GL_SkinWidgetId
	- font scale see @ref T_GL_SCALE

@code
		// Defines the uncheck image 
		{
			// Define the type of widget here it is a picture
			"type":"picture",
			
			// Positions the image in the first column of the layout 
			"item":{"column":0, "row":0},
			
			// IMPORTANT : This id allows to find the check image in the tree widget (GL_SkinWidgetId)
			"id":0xFF000003, // See GL_ID_SKIN_CHECK
			
			// The state mask specifies that the image will be displayed only if the wigdet is not checked
			"statemask":"unchecked",
			
			// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
			"source":"/images/CheckOff.wgu",
			
			// Strength of the cell layout to have a fixed width.
			// If we do not specify the height it has the capacity to expand in height.
			"size":{"width":54},

			// The following property is use to generate the @ref GL_EVENT_STYLUS_CLICK event when you click 
			// with the stylus on this image, this allows to check or uncheck the box
			"clickable":true,
	
			// The following property defines that the areas are sensitive to clicks. 
			"clicksensitive":true,
		},
@endcode

The following paragraph describes the part that shows the check.
For the :
	- color see @ref GL_SkinColors.
	- specific id see @ref GL_SkinWidgetId
	- font scale see @ref T_GL_SCALE

@code
		// Defines the check image 
		{
			// Define the type of widget here it is a picture
			"type":"picture",
			
			// Positions the image in the first column of the layout 
			"item":{"column":0, "row":0},
			
			// IMPORTANT : This id allows to find the check image in the tree widget (GL_SkinWidgetId)
			"id":0xFF000003, // See GL_ID_SKIN_CHECK
			
			// The state mask specifies that the image will be displayed only if the wigdet is checked
			"statemask":"checked",
			
			// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
			"source":"/images/CheckOn.wgu",
			
			// Strength of the cell layout to have a fixed width.
			// If we do not specify the height it has the capacity to expand in height.
			"size":{"width":54},

			// The following property is use to generate the @ref GL_EVENT_STYLUS_CLICK event when you click 
			// with the stylus on this image, this allows to check or uncheck the box
			"clickable":true,
	
			// The following property defines that the areas are sensitive to clicks. 
			"clicksensitive":true,
		},
@endcode

The following paragraph describes the text label displayed on the button.

For the :
	- color see @ref GL_SkinColors.
	- specific id see @ref GL_SkinWidgetId
	- font scale see @ref T_GL_SCALE

@code
		// Define the label of the check box
		{
			// Define the type of widget here it is a picture
			"type":"label",
			
			// Positions the text in the middle of button
			"item":{"column":2, "row":0},
			
			// IMPORTANT : This id allows to find the text label in the tree widget
			"id":0xFF000001, // See GL_ID_SKIN_LABEL
			
			// Sets the size of the button text 
			"font":{"size":{"height":0x3FF3}}, // See GL_SCALE_MEDIUM
			
			// Sets the text color, the color here is defined in the file of the skin color.js.
			"forecolor":0x0000000D, // See GL_COLOR_BUTTON_TEXT
			
			// Force a margin at the top and bottom of the label
			"margins":{"top":2, "bottom":2},

			// The following property defines that the areas are sensitive to clicks. 
			"clicksensitive":true,
		},
	]
}
@endcode

@}

****************************************************************************************
****************************************************************************************
****************************************************************************************

@addtogroup GL_SkinBarSliderWidgets
@{

The progress bar, vertical scroll bar, horizontal scroll bar, horizontal slider, and progress bar widgets share the same operating principle.
We will explain the creation of a skin through the example of the horizontal scroll bar.


An horizontal scrollbar is composed of several part :
	- The bar : This is the part of the bottom
	- The slider : This is the part that slides into the bar

A horizontal scrollbar has the ability to expand, it is composed of several images :
	- an image with the right side, 
	- an image repeated several times in the center, 
	- an image containing the left edge,

Each image is placed in a given cell of the layout

We obtain three-dimensional:

@image html SkinBar.png

The description of the skin file horizontal scroll bar starts with :

@code
{
	// Defines the type of widget you want to describe the skin (here is horizontal scroll bar)
	"type":"hscrollbar",

	// The following property allows to expand widget in width
	"expand":"width",

	// Disables the cell of layout to shrink in all the directions
	"shrink":"none",

	// The following property is use to generate the @ref GL_EVENT_STYLUS_CLICK event when you click 
	// with the stylus on the layout, you must set the property at true
	"clickable":true,

	// This property defines children of horizontal scroll bar
	"children":
	[
@endcode

The following paragraph describes the part that shows the bar of horizontal scroll bar :

@code
		{
			// Define the type of widget here it is a layout
			"type":"layout",

			// Enables the cell of layout to grows in width direction only
			"grow":"width",

			// Disables the cell of layout to shrink in all the directions
			"shrink":"none",

			// Align the background to the left side
			"backalign":"left",

			// IMPORTANT : This id allows to find the bar in the tree widget (GL_SkinWidgetId)
			"id":0xFF000005, // GL_ID_SKIN_BAR

			// The following property defines that the areas are sensitive to clicks. 
			"clicksensitive":true,

			// This property defines children of the bar
			"children":
			[
				// Defines the left image of the bar
				{
					// Define the type of widget here it is a picture
					"type":"picture",

					// Positions the image in the first column of the layout
					"item":{"column":0, "row":0},

					// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
					"source":"/images/HScrollBar(left).wgu",

					// Strength of the cell layout to have a fixed size.
					"size":{"width":6, "height":12},

					// Align the foreground to the left side
					"forealign":"left",
				},

				// Defines the center image of the bar
				{
					// Define the type of widget here it is a picture
					"type":"picture",

					// Positions the image in the second column of the layout
					"item":{"column":1, "row":0},

					// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
					"source":"/images/HScrollBar(center).wgu",

					// Allows the cell's layout to shrink in width
					"shrink":"width",

					// Allows the image to repeated in x
					"transformation":"repeatx",

					// Allows the widget to expand its background in all directions
					"expand":"all",
				},

				// Defines the right image of the bar
				{
					"type":"picture",

					// Positions the image in the third column of the layout
					"item":{"column":2, "row":0},

					// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
					"source":"/images/HScrollBar(right).wgu",

					// Strength of the cell layout to have a fixed size.
					"size":{"width":6, "height":12},

					// Align the foreground to the right side
					"forealign":"right",
				},
			]
		},

@endcode

The following paragraph describes the part that shows the slider of horizontal scroll bar :

@code
		{
			// Define the type of widget here it is a layout
			"type":"layout",

			// Enables the cell of layout to grows in width direction only
			"grow":"width",

			// Disables the cell of layout to shrink in all the directions
			"shrink":"none",

			// Align the background to the left side
			"backalign":"left",

			// IMPORTANT : This id allows to find the slider in the tree widget (GL_SkinWidgetId)
			"id":0xFF000004, // GL_ID_SKIN_SLIDER

			// The following property defines that the areas are sensitive to clicks. 
			"clicksensitive":true,

			// This property defines children of the slider
			"children":
			[
				// Defines the left image of the slider
				{
					// Define the type of widget here it is a picture
					"type":"picture",

					// Positions the image in the first column of the layout
					"item":{"column":0, "row":0},

					// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
					"source":"/images/HSlider(left).wgu", 

					// Strength of the cell layout to have a fixed size.
					"size":{"width":4, "height":8},

					// Force a margin at the top and bottom of the slider
					"margins":{"left":2, "top":2, "right":0, "bottom":2},

					// Align the foreground to the left side
					"forealign":"left",
				},

				// Defines the center image of the slider
				{
					// Define the type of widget here it is a picture
					"type":"picture",

					// Positions the image in the second column of the layout
					"item":{"column":1, "row":0},

					// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
					"source":"/images/HSlider(center).wgu",

					// Force a margin at the top and bottom of the slider
					"margins":{"left":0, "top":2, "right":0, "bottom":2},

					// Allows the cell's layout to shrink in width
					"shrink":"width",

					// Allows the image to repeated in x
					"transformation":"repeatx",

					// Allows the widget to expand its background in all directions
					"expand":"all",
				},

				// Defines the right image of the slider
				{
					// Define the type of widget here it is a picture
					"type":"picture",

					// Positions the image in the third column of the layout
					"item":{"column":2, "row":0},

					// Indicates the filename of images (The path is relative to easily find the file in the skin tar)
					"source":"/images/HSlider(right).wgu",

					// Strength of the cell layout to have a fixed size.
					"size":{"width":4, "height":8},

					// Force a margin at the top and bottom of the slider
					"margins":{"left":0, "top":2, "right":2, "bottom":2},

					// Align the foreground to the right side
					"forealign":"right",
				},
			]
		},
	]
}
@endcode


@}

****************************************************************************************
****************************************************************************************
****************************************************************************************

@addtogroup GL_SkinDialog 
@{

Dialogs are composed of several skin files nested in the other one. 
The dialog box is first a dialog widget that contains a 3-piece layout :
- The title (dialog/title.js)
- The contents 
- The button (dialog/buttons.js)

Each part of the layout contains a skin file.

@image html SkinDialog.png

The content, however, can receive a file from several skin, this according to the dialog box displayed.

The skins files for @ref GL_DialogListDoc are :
	- dialogs/list.js      (@ref GL_Dialog_Menu, @ref GL_Dialog_IconMenu, @ref GL_Dialog_IconButtonMenu, @ref GL_Dialog_Choice, @ref GL_Dialog_MultiChoice)
	
The skins files for @ref GL_DialogFileDoc are :
	- dialogs/file.js      (@ref GL_Dialog_File, @ref GL_Dialog_MultiFile)
	
The skins files for @ref GL_DialogMessageDoc are :
	- dialogs/media.js     (@ref GL_Dialog_Media)
	- dialogs/message.js   (@ref GL_Dialog_Message)
	- dialogs/picture.js   (@ref GL_Dialog_Picture)
	
Skins files for @ref GL_DialogInputDoc :
	- dialogs/input.js     (@ref GL_Dialog_Password, @ref GL_Dialog_Text, @ref GL_Dialog_Date, @ref GL_Dialog_Ip, @ref GL_Dialog_Amount )
	- dialogs/keyboard.js  (@ref GL_Dialog_VirtualKeyboard)
	- dialogs/color.js     (@ref GL_Dialog_Color)
	- dialogs/progress.js  (@ref GL_Dialog_Progress)
	- dialogs/scheme.js    (@ref GL_Dialog_Scheme)
	- dialogs/signature.js (@ref GL_Dialog_Signature)
	- dialogs/slider.js    (@ref GL_Dialog_Slider)

@}
****************************************************************************************
****************************************************************************************
****************************************************************************************
@addtogroup GL_SkinSkinsJs Skin skins.js file
@{

This file is an index to find the skin files in the archive, one side was the name of another widget file defining the widget.
If this file is missing the skin is not loaded. It should never be changed unless you moved or renamed files in the tree.

@code
{
	// Object type skin
	"type":"skin",

	"skins":
	{
		// Widgets name       : Widget skin filename
		"label"               : "label.js",
		"button"              : "button.js",
		"checkbutton"         : "checkbutton.js",
		"radiobutton"         : "radiobutton.js",
		"edit"                : "edit.js",
		"vscrollbar"          : "vscrollbar.js",
		"hscrollbar"          : "hscrollbar.js",
		"progressbar"         : "progressbar.js",
		"icon"                : "icon.js",
		"iconbutton"          : "iconbutton.js",
		"list"                : "list.js",
		"dialog"              : "dialog.js",
		"palette"             : "palette.js",
		"virtualkeyboard"     : "virtualkeyboard.js",
		"key"                 : "key.js",
		"hslider"             : "hslider.js",
		"window"              : "window.js",
		"print"               : "print.js",
		"signature"           : "signature.js",

		// Dialogs
		"dialogs/message"     : "dialogs/message.js",
		"dialogs/title"       : "dialogs/title.js",
		"dialogs/buttons"     : "dialogs/buttons.js",
		"dialogs/input"       : "dialogs/input.js",
		"dialogs/list"        : "dialogs/list.js",
		"dialogs/color"       : "dialogs/color.js",
		"dialogs/media"       : "dialogs/media.js",
		"dialogs/picture"     : "dialogs/picture.js",
		"dialogs/keyboard"    : "dialogs/keyboard.js",
		"dialogs/slider"      : "dialogs/slider.js",
		"dialogs/progress"    : "dialogs/progress.js",
		"dialogs/file"        : "dialogs/file.js",
		"dialogs/scheme"      : "dialogs/scheme.js",
		"dialogs/signature"   : "dialogs/signature.js",

		// Images
		"images/question"     : "images/question.wgu",
		"images/information"  : "images/information.wgu",
		"images/error"        : "images/error.wgu",
		"images/warning"      : "images/warning.wgu",
		"images/correction"   : "images/correction.wgu",
		"images/cancel"       : "images/cancel.wgu",
		"images/validation"   : "images/validation.wgu",
		"images/mistake"      : "images/mistake.wgu",
	}
}
@endcode

@}
****************************************************************************************
****************************************************************************************
****************************************************************************************
@addtogroup GL_SkinColorsJs Skin colors.js file
@{

This file allows for the association between skin color (@ref GL_SkinColors) of the generic and a specific color :

@code
[
	// Skin color,   Color displayed
	[0x00000001,     0xFFFFFFFF], // GL_COLOR_LABEL_TEXT
	[0x00000002,     0xFF4EB2DD], // GL_COLOR_KEY_FOCUS
	[0x00000003,     0xFFFFFFFF], // GL_COLOR_KEY_TEXT
	[0x00000004,     0xFF000000], // GL_COLOR_WINDOW_BACKGROUND
	[0x00000005,     0xFF445577], // GL_COLOR_WINDOW_BORDER
	[0x00000006,     0xFFFFFFFF], // GL_COLOR_WINDOW_TEXT
	[0x00000007,     0xFF1F344E], // GL_COLOR_SIGNATURE_INK
	[0x00000008,     0xFF198DC1], // GL_COLOR_SIGNATURE_BORDER
	[0x00000009,     0xFFEBF1F7], // GL_COLOR_SIGNATURE_BACKGROUND
	[0x0000000A,     0xFFB6DBD2], // GL_COLOR_PALETTE_FOCUS
	[0x0000000B,     0xFF0A246A], // GL_COLOR_PALETTE_FOCUS_BORDER
	[0x0000000C,     0xFF000000], // GL_COLOR_EDIT_TEXT
	[0x0000000D,     0xFFFFFFFF], // GL_COLOR_BUTTON_TEXT
	[0x0000000E,     0xFFFFFFFF], // GL_COLOR_DIALOG_TEXT
	[0x0000000F,     0x9F000000], // GL_COLOR_DIALOG_TEXT_BACKGROUND
	[0x00000010,     0xFF000000], // GL_COLOR_PROGRESS_TEXT
	[0x00000011,     0x7FFFFFFF], // GL_COLOR_PROGRESS_TEXT_BACKGROUND 
	[0x00000012,     0xFF000000], // GL_COLOR_DIALOG_HELP_TEXT
	[0x00000013,     0xFFFFFFFF], // GL_COLOR_DIALOG_HELP_TEXT_BACKGROUND
	[0x00000014,     0xFF000000], // GL_COLOR_PRINT_TEXT
]
@endcode


@}
****************************************************************************************
****************************************************************************************
****************************************************************************************
@addtogroup GL_SkinGraphicLibJs Skin graphiclib.js file
@{

Configuration file of the graphic library, the format is :

@code
{
	// Object type are font graphic library
	"type":"graphiclib",

	// Font name to select the default
	"fontname":"GOAL",

	// Default character encoding
	"charset":"utf8",

	// Definitions of the fonts scale according to the screen and printer resolutions 
	"fonts":
	[
		// Definition of the scales of fonts if the screen size is unknown
		{
			// Object type are font scale
			"type"   :"fontscale",

			//The device is a screen
			"device" :"screen", 

			// Default size of screen
			"size"   :"default",

			///< Extra extra small font size (Optimized to display an average of 24 characters on the screen width)
			"xxsmall": 5,

			///< Extra small font size  (Optimized to display an average of 24 characters on the screen width)
			"xsmall" : 5,

			///< Small font size (Optimized to display an average of 22 characters on the screen width)
			"small"  : 7,

			// Medium font size (Optimized to display an average of 20 characters on the screen width)
			"medium" :10,

			// Large font size (Optimized to display an average of 16 characters on the screen width)
			"large"  :16,

			// Extra large font size (Optimized to display an average of 12 characters on the screen width)
			"xlarge" :20,

			// Extra extra large font size (Optimized to display an average of 10 characters on the screen width)
			"xxlarge":25,
		},

		// Definition of the scales of fonts to the screen 128 x 64
		{
			// Object type are font scale
			"type"   :"fontscale", 

			// The device is a screen
			"device" :"screen", 

			// Size of screen here 128x64 other possible are "240x320", "320x240",320x480","480x272","640x480"
			"size"   :"128x64", 

			// Extra extra small font size (Optimized to display an average of 24 characters on the screen width)
			"xxsmall": 5,

			// Extra small font size  (Optimized to display an average of 24 characters on the screen width)
			"xsmall" : 5,

			// Small font size (Optimized to display an average of 22 characters on the screen width)
			"small"  : 7,

			// Medium font size (Optimized to display an average of 20 characters on the screen width)
			"medium" :10,

			// Large font size (Optimized to display an average of 16 characters on the screen width)
			"large"  :16,

			// Extra large font size (Optimized to display an average of 12 characters on the screen width)
			"xlarge" :20,

			// Extra extra large font size (Optimized to display an average of 10 characters on the screen width)
			"xxlarge":25,
		},
		
		... here other screen resolution ...

		// Definition of the scales of the sizes of fonts to the printer
		{
			// Object type are font scale
			"type"   :"fontscale",

			// The device is a printer
			"device" :"printer", 

			// Default size of printer
			"size"   :"default",

			// Extra extra small font size (Optimized to display an average of 24 characters on the screen width)
			"xxsmall":10,

			// Extra small font size  (Optimized to display an average of 24 characters on the screen width)
			"xsmall" :16,

			// Small font size (Optimized to display an average of 22 characters on the screen width)
			"small"  :20,

			// Medium font size (Optimized to display an average of 20 characters on the screen width)
			"medium" :25,

			// Large font size (Optimized to display an average of 16 characters on the screen width)
			"large"  :32,

			// Extra large font size (Optimized to display an average of 12 characters on the screen width)
			"xlarge" :39,

			// Extra extra large font size (Optimized to display an average of 10 characters on the screen width)
			"xxlarge":49,
		}
	],
}
@endcode



@}
@}
@}

*/