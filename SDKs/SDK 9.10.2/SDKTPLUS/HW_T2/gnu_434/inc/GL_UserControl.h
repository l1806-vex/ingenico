// $Id: GL_UserControl.h,v 1.1.2.5 2012/10/08 09:42:05 rbertholet Exp $
// UserControl management
#ifndef GL_UserControl_h_INCLUDED
#define GL_UserControl_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_UserControl
@{
@addtogroup GL_UserControlDoc UserControl
@{

User controls are re usable components that may have a graphical user interface. 
User controls include pre-defined components for all the fundamental components of a 
GOAL graphical user interface, such as buttons, sliders, check boxes, radio buttons, etc. 
Non-interactive components such as a simple timer interface are also included.

Below is a list of specific functions to this class :
	- @ref GL_UserControl_Create : Creating a user control
	- @ref GL_UserControl_SearchId : Search an id inside a user control
	- @ref GL_UserControl_Register : Register a new user control in the graphics library
	- @ref GL_UserControl_Unregister : Unregister an user control 

Functions used in messages :
	- @ref GL_Message_GetUserControl 

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_CallbackProperties
	- @ref GL_Widget_UserDataProperties

For messages sent by this widget see :
	- @ref GL_Widget_CommonMessage

Methods inherited from class widget :
	- @ref GL_Widget_GetSize
	- @ref GL_Widget_SetSize
	- @ref GL_Widget_GetMinSize
	- @ref GL_Widget_SetMinSize
	- @ref GL_Widget_GetMaxSize
	- @ref GL_Widget_SetMaxSize
	- @ref GL_Widget_GetPosition
	- @ref GL_Widget_SetPosition
	- @ref GL_Widget_GetVisible
	- @ref GL_Widget_SetVisible
	- @ref GL_Widget_GetItem
	- @ref GL_Widget_SetItem
	- @ref GL_Widget_GetBackAlign
	- @ref GL_Widget_SetBackAlign
	- @ref GL_Widget_GetForeAlign
	- @ref GL_Widget_SetForeAlign
	- @ref GL_Widget_Destroy
	- @ref GL_Widget_GetWindow
	- @ref GL_Widget_SetMargins
	- @ref GL_Widget_GetMargins
	- @ref GL_Widget_SetBorders
	- @ref GL_Widget_GetBorders
	- @ref GL_Widget_GetId
	- @ref GL_Widget_SetId
	- @ref GL_Widget_SearchId
	- @ref GL_Widget_GetBackColor
	- @ref GL_Widget_SetBackColor
	- @ref GL_Widget_SetShrink
	- @ref GL_Widget_GetShrink
	- @ref GL_Widget_SetGrow
	- @ref GL_Widget_GetGrow
	- @ref GL_Widget_SetExpand
	- @ref GL_Widget_GetExpand
	- @ref GL_Widget_SetUserData
	- @ref GL_Widget_GetUserData
	- @ref GL_Widget_SetClickable
	- @ref GL_Widget_GetClickable
	- @ref GL_Widget_SetClickSensitive
	- @ref GL_Widget_GetClickSensitive

Methods 

For messages sent by this widget see @ref GL_Widget_CommonMessage

<h2>Sample</h2>

	Below is an example of creating a reusable component.
	Here we want to create an user control for performing a simple mathematical operation.

	@image html userControlTest2.png

	Below is the code management user control :

	@include GL_SampleCalculator.c

	Below the gml describing the user control :

	@include Calculator.wml

	Now that the user control is defined we will use it twice in a window to get the following result :

	@image html userControlTest1.png
	
	Below is the code to use the user control :

	@include GL_SampleUserControl.c

	Below the gml describing the window :

	@include UseCalculator.gml

@}
*/


/*<ALL>
	Extension("INCLUDE",             "WIDGET",     "This class is used include another resource file or use user control (WARNING this API is not final and may change in future)",
		RefOne("filename",           "SOURCEFILE", 'User Control filename property must respect the following naming convention: ${WmlRelativePath)#${GoalName} where ${WmlRelativePath) is the relative path to the wml file in the project containing the usercontrol definition, and ${GoalName} is the value of the "name" attribute in the goal tag of the wml file. Example: "calculator.wml#calculator" for a usercontrol stored in the "calculator.wml" file, with a goal tag whose name attribute is set to "calculator"')),
	Extension("USERCONTROL",             "WIDGET",     "This class is used create a user control (WARNING this API is not final and may change in future)",
		RefOne("children",         "CHILDREN",   "Children items attached to this widget"),
		),
</ALL>*/

/** Creating a userControl. A user control must have been previously loaded with @ref GL_UserControl_Register.
@param parent handle on the parent widget
@param filename filename of the resource file
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_UserControl_Create(T_GL_HWIDGET parent, const char * filename) GL_EXCEPTION;

/** This callback function is to initialize the user control
@param userControl user control handle */
typedef void (*T_GL_USERCONTROL_CALLBACK)(T_GL_HWIDGET userControl);

/** Register a new user control in the graphics library
@param graphicLib Graphic library context handle 
@param filename filename of the graphic resources of user control
@param init This callback function is used to initialize the user control */
void GL_UserControl_Register(T_GL_HGRAPHIC_LIB graphicLib, const char * filename, T_GL_USERCONTROL_CALLBACK init) GL_EXCEPTION;

/** Unregister an user control 
@param graphicLib Graphic library context handle 
@param filename resource filename of the user control */
void GL_UserControl_Unregister(T_GL_HGRAPHIC_LIB graphicLib, const char * filename) GL_EXCEPTION;

/** Search an id inside a user control
It does not search the id inside a user control, in this case you need to use this function @ref GL_UserControl_SearchId.
@param widget widget handle (window handle for example)
@param userControlId the identifier id of the user control
@param internalId the identifier inside the user control
@return the widget handle found or null if it is not found */
T_GL_HWIDGET GL_UserControl_SearchId(T_GL_HWIDGET widget, T_GL_ID userControlId, T_GL_ID internalId) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_UserControl_h_INCLUDED
