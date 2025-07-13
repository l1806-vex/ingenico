/**
@addtogroup KSFAM_GOAL_Documentation
@{
@addtogroup GL_History
@{

Release 3.06 : CMP_GOAL_0306
	- 11632 G_Extended_Entry : on ICT250, not possible to exit via Cancel (red button). Idem on IWL280 (OK by touchscreen but not by keyboard)
	- 11631 : cGUI Performance - Delayed Response from scrollbar when large amount of text displayed on TextArea Control
	- 11493 : The progressbar text property is not correctly managed
	- Adds picture image cache
	- Adding vectorized mode in drawing widgets (@ref GL_Drawing_SetVectorized, @ref GL_Drawing_GetVectorized)
	- Adding draw area in drawing widgets (@ref GL_Drawing_DrawArea, @ref GL_Drawing_GetPixelType)
	- Changing the internal behavior of scrollbars (the min and max now shows the movement of the slider)
	- Added ability to scroll the view by the code C (@ref GL_ScrollView_GetVerticalRange, @ref GL_ScrollView_GetHorizontalRange, @ref GL_ScrollView_Move)
	- Added ability to define a mask user in an input field (@ref GL_Widget_GetUserChar, @ref GL_Widget_SetUserChar)
	- The cancel button will exit the dialog keyboard
	- Reducing the size of text on dialog boxes
	- Remove the image of the virtual keyboard on the function @ref GL_Dialog_Scheme
	- Improved ergonomics on @ref GL_Dialog_File
	- Fixed state change visibility widget
	- Correction of the jolt problem on scrolling widget
	- GML renaming of the tag page into mappage. This tag is used in the virtual keyboard

Release 3.05 : CMP_GOAL_0305
	- 11297 : @ref GL_Widget_SearchId returns always NULL for a WINDOW
	- 11338 : Fuite de mémoire / handles / threads
	- 11377 : Fuite de handle et thread
	- 10853 : Dal doesn't support ressource file from subdirectory
	- Improved management of URL to support directories
	- In the @ref GL_Dialog_Scheme removes the display of the help area if it is empty
	- Predefined colors can be used by the C API
	- Fixed scrolling problem with multiple ScrollView
	- Fixes the signature speed problem with CGUI
	- Fixes the signature problem for IPP480
	- Fixes the print problem (Jira PE0001-40)
	- Improves the scrolling performance
	- Improved the performance :
		- reduce the number of system calls
		- adds archive index for fast file access (increase load performances)
	- Add functions :
		- @ref GL_File_MatchPath
		- @ref GL_Widget_GetClickable
		- @ref GL_Widget_SetClickable
		- @ref GL_Widget_GetClickSensitive
		- @ref GL_Widget_SetClickSensitive

Release 3.04 : CMP_GOAL_0304
	- 11074 : @ref GL_GraphicLib_ReadResource ignores appli_type=006F in the dal URL
	- Fix user area problem
	- Scrolling optimisation
	- Renumbering of binary files
	- Fix the problem of missing text on the list of icons
	- Adds BMP encoding
	- Using GetTerminalName (this requires a minimum system version 11.00)
	- The "\n" are supported in gml text strings
	- The space alone are supported in gml text strings
	- Adding an input cursor on the black and white screen
	- Fixed overflow text input in the "numero centre" screen with black and white terminal
	- Fixed deadlock in the call for @ref GL_Window_Hide
	- Added function to extract image from window

Release 3.03 : CMP_GOAL_0303
	- Dal optimisation.
	- Enumeration renammed :
		- Old values                        New values
		- GL_BOTTOM_ALIGN                -> GL_ALIGN_BOTTOM
		- GL_BOTTOM_LEFT_ALIGN           -> GL_ALIGN_BOTTOM_LEFT
		- GL_BOTTOM_RIGHT_ALIGN          -> GL_ALIGN_BOTTOM_RIGHT
		- GL_CENTER_ALIGN                -> GL_ALIGN_CENTER
		- GL_HORIZONTAL_ALIGN            -> GL_ALIGN_HORIZONTAL
		- GL_LEFT_ALIGN                  -> GL_ALIGN_LEFT
		- GL_RIGHT_ALIGN                 -> GL_ALIGN_RIGHT
		- GL_TOP_ALIGN                   -> GL_ALIGN_TOP
		- GL_TOP_LEFT_ALIGN              -> GL_ALIGN_TOP_LEFT
		- GL_TOP_RIGHT_ALIGN             -> GL_ALIGN_TOP_RIGHT
		- GL_VERTICAL_ALIGN              -> GL_ALIGN_VERTICAL
		- GL_ALL_DIRECTION               -> GL_DIRECTION_ALL
		- GL_HEIGHT_DIRECTION            -> GL_DIRECTION_HEIGHT
		- GL_NONE_DIRECTION              -> GL_DIRECTION_NONE
		- GL_WIDTH_DIRECTION             -> GL_DIRECTION_WIDTH
		- GL_WIDGET_0_NOT_SIGNIFICANT    -> GL_MODE_0_NOT_SIGNIFICANT
		- GL_WIDGET_0_SIGNIFICANT        -> GL_MODE_0_SIGNIFICANT
		- GL_WIDGET_HIDE_BLANK           -> GL_MODE_HIDE_BLANK
		- GL_WIDGET_HIDE_PROMPT          -> GL_MODE_HIDE_PROMPT
		- GL_WIDGET_INSERT               -> GL_MODE_INSERT
		- GL_WIDGET_LEFT_TO_RIGHT        -> GL_MODE_LEFT_TO_RIGHT
		- GL_WIDGET_NORMAL               -> GL_MODE_NORMAL
		- GL_WIDGET_PASSWORD             -> GL_MODE_PASSWORD
		- GL_WIDGET_REPLACE              -> GL_MODE_REPLACE
		- GL_WIDGET_RIGHT_TO_LEFT        -> GL_MODE_RIGHT_TO_LEFT
		- GL_WIDGET_SHOW_BLANK           -> GL_MODE_SHOW_BLANK
		- GL_WIDGET_SHOW_PROMPT          -> GL_MODE_SHOW_PROMPT
		- GL_FFMS_FLASH_ROOT             -> GL_ROOT_FFMS_FLASH
		- GL_FFMS_RAM_ROOT               -> GL_ROOT_FFMS_RAM
		- GL_PARAM_ROOT                  -> GL_ROOT_PARAM
		- GL_VFS_FLASH_ROOT              -> GL_ROOT_VFS_FLASH
		- GL_VFS_MMC_ROOT                -> GL_ROOT_VFS_MMC
		- GL_VFS_RAM_ROOT                -> GL_ROOT_VFS_RAM
		- GL_VFS_USB_ROOT                -> GL_ROOT_VFS_USB
		- GL_LARGE                       -> GL_SCALE_LARGE
		- GL_MEDIUM                      -> GL_SCALE_MEDIUM
		- GL_SMALL                       -> GL_SCALE_SMALL
		- GL_XLARGE                      -> GL_SCALE_XLARGE
		- GL_XSMALL                      -> GL_SCALE_XSMALL
		- GL_XXLARGE                     -> GL_SCALE_XXLARGE
		- GL_XXSMALL                     -> GL_SCALE_XXSMALL
		- GL_ALL_STATE                   -> GL_STATE_ALL
		- GL_CHECKED_STATE               -> GL_STATE_CHECKED
		- GL_EMPTY_STATE                 -> GL_STATE_EMPTY
		- GL_FOCUSED_STATE               -> GL_STATE_FOCUSED
		- GL_BUTTON_TYPE                 -> GL_TYPE_BUTTON
		- GL_CHECKBUTTON_TYPE            -> GL_TYPE_CHECKBUTTON
		- GL_DIALOG_TYPE                 -> GL_TYPE_DIALOG
		- GL_DOCUMENT_TYPE               -> GL_TYPE_DOCUMENT
		- GL_DRAWING_TYPE                -> GL_TYPE_DRAWING
		- GL_EDIT_TYPE                   -> GL_TYPE_EDIT
		- GL_FIRST_RFU                   -> GL_TYPE_FIRST_RFU
		- GL_GRAPHIC_LIB_TYPE            -> GL_TYPE_GRAPHIC_LIB
		- GL_HSCROLLBAR_TYPE             -> GL_TYPE_HSCROLLBAR
		- GL_HSLIDER_TYPE                -> GL_TYPE_HSLIDER
		- GL_ICON_TYPE                   -> GL_TYPE_ICON
		- GL_ICONBUTTON_TYPE             -> GL_TYPE_ICONBUTTON
		- GL_ITEM_TYPE_START             -> GL_TYPE_ITEM_START
		- GL_ITEM_TYPE_STOP              -> GL_TYPE_ITEM_STOP
		- GL_KEY_TYPE                    -> GL_TYPE_KEY
		- GL_LABEL_TYPE                  -> GL_TYPE_LABEL
		- GL_LAYOUT_TYPE                 -> GL_TYPE_LAYOUT
		- GL_LIST_TYPE                   -> GL_TYPE_LIST
		- GL_MEDIA_TYPE                  -> GL_TYPE_MEDIA
		- GL_PALETTE_TYPE                -> GL_TYPE_PALETTE
		- GL_PICTURE_TYPE                -> GL_TYPE_PICTURE
		- GL_PLUGIN_TYPE                 -> GL_TYPE_PLUGIN
		- GL_PRINT_TYPE                  -> GL_TYPE_PRINT
		- GL_PROGRESSBAR_TYPE            -> GL_TYPE_PROGRESSBAR
		- GL_RADIOBUTTON_TYPE            -> GL_TYPE_RADIOBUTTON
		- GL_SCROLLVIEW_TYPE             -> GL_TYPE_SCROLLVIEW
		- GL_SIGNATURE_TYPE              -> GL_TYPE_SIGNATURE
		- GL_SKIN_TYPE                   -> GL_TYPE_SKIN
		- GL_TIMER_TYPE                  -> GL_TYPE_TIMER
		- GL_WIDGET_UNDEFINED            -> GL_TYPE_UNDEFINED
		- GL_VIRTUALKEYBOARD_TYPE        -> GL_TYPE_VIRTUALKEYBOARD
		- GL_VSCROLLBAR_TYPE             -> GL_TYPE_VSCROLLBAR
		- GL_WIDGET_TYPE_END             -> GL_TYPE_WIDGET_END
		- GL_WIDGET_TYPE_START           -> GL_TYPE_WIDGET_START
		- GL_WINDOW_TYPE                 -> GL_TYPE_WINDOW
		- GL_PERCENT_UNIT                -> GL_UNIT_PERCENT
		- GL_PERTHOUSAND_UNIT            -> GL_UNIT_PERTHOUSAND
		- GL_PIXEL_UNIT                  -> GL_UNIT_PIXEL
		- GL_DAL_URL                     -> GL_URL_DAL
		- GL_DIR_URL                     -> GL_URL_DIR
		- GL_FILE_URL                    -> GL_URL_FILE
		- GL_INFINITE                    -> GL_TIME_INFINITE   
		- GL_SECOND                      -> GL_TIME_SECOND   
		- GL_MINUTE                      -> GL_TIME_MINUTE   
		- GL_PERCENT_VALUE               -> GL_VALUE_PERCENT 
		- GL_PERTHOUSAND_VALUE           -> GL_VALUE_PERTHOUSAND 


Release 3.02 : CMP_GOAL_0302
	- Removal of the optimization of image read by DAL
	- Fixed problem with scrolling of some widgets
	- Fixed problem displaying bmp image

Release 3.01 : CMP_GOAL_0301
	- Adding image stretching
	- Adding signature capture with 300 samples per seconds
	- Fix the edit field problem
	- Adding the cgui component in the package delivered

Release 2.02 : CMP_GOAL_0202
	- Fixed FT : 10266, 10495, 10750, 10861
	- Adding the notion of scale in the fonts
	- loading a skin can be done by using a name
	- The binaries have now an official number
	- The user area is now managed in GOAL
	- The skin official is now present
	- The default font has accented characters in the ISO8859-1
	- The icon button widget was added, and the various dialogs using this widget
	- Scrolling with your finger is now dynamic
	- The player can play audio files
	- Improved performance of reading image files

Release 2.01 : CMP_GOAL_0201
	- Adding Jpeg decoder, Bmp decoder, Gif animated

Release 2.00 : CMP_GOAL_0200
	- Add signature capture, modification API, customisation virtual keyboard, nanox multi instance, documentation updated and examples added, treatment duration of video.

@}
@}
*/