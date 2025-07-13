// $Id: GL_Picture.h,v 1.1.2.40 2012/08/24 12:42:52 rbertholet Exp $
// Picture management
#ifndef GL_Picture_h_INCLUDED
#define GL_Picture_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_Picture
@{
@addtogroup GL_PictureDoc Picture
@{

A picture is a widget that can display a fixed image or animated image

Below is a list of specific functions to this class :
	- @ref GL_Picture_Create : Creating a picture

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_ImagesProperties
	- @ref GL_Widget_ImagesTransformationProperties
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
	- @ref GL_Widget_SetSource
	- @ref GL_Widget_GetSource
	- @ref GL_Widget_SetUserData
	- @ref GL_Widget_GetUserData
	- @ref GL_Widget_SetClickable
	- @ref GL_Widget_GetClickable
	- @ref GL_Widget_SetClickSensitive
	- @ref GL_Widget_GetClickSensitive
	- @ref GL_Widget_SetTransformation
	- @ref GL_Widget_GetTransformation
	- @ref GL_Widget_SetSourceFromBuffer

For messages sent by this widget see @ref GL_Widget_CommonMessage

<h2>Sample</h2>

	Below is an example of creating a window with a picture. 

	@image html pictureTest.png

	@include GL_SamplePicture.c

	The following example shows the creation of a frame that adapts automatically to the window.

	The frame consists of the following images :

	@image html pictureTest3.png

	The result will be :

	@image html pictureTest2.png

	@include GL_SamplePictureStretch.c
	
@}
*/

/*<ALL>
	Extension("PICTURE",           "WIDGET",     "A picture is a widget that can display a fixed image or animated image",
		RefOne("source",           "SOURCEFILE","Image source (file name can contain alphanumeric, underscore, minus, spaces characters)"),
		RefOne("transformation",   "TRANSFORMATION", "Image transformation"),
		),
</ALL>*/

/** Creating a picture
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_Picture_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Picture_h_INCLUDED
