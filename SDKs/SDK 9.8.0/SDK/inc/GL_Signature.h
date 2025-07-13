// $Id: GL_Signature.h,v 1.1.2.16 2012/08/24 12:42:52 rbertholet Exp $
// Signature management
#ifndef GL_Signature_h_INCLUDED
#define GL_Signature_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_Signature
@{
@addtogroup GL_SignatureDoc Signature capture
@{

This widget is intended to pilot a signature other than those provided as standard.

<H1>This widget should never be placed in a scrolled view</H1>

Below is a list of specific functions to this class :

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
	- @ref GL_Widget_GetForeColor
	- @ref GL_Widget_SetForeColor
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
	- @ref GL_Widget_ReadResource
	- @ref GL_Widget_InstanciateResource

For messages sent by this widget see @ref GL_Widget_CommonMessage

To retrieve all the points contained in the signature file see section @ref GL_SignatureFile.

<h2>Sample</h2>

	Below is an example of how to use the generic widget signature to interact with the native signature video.
	This is just one example, to view a video you must use the media widget.

	@image html signatureTest.png

	@include GL_SampleSignature.c
@}
*/

/*<ALL>
	Extension("SIGNATURE",             "WIDGET",     "This class is used to play movie or sound",
		Integer("penwidth",                    "Pen width in pixels"),
		),
</ALL>*/


/** Creating a signature
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_Signature_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/** Sets the pen width
@param signature handle of the signature capture widget
@param width pen width in pixels */
void GL_Signature_SetPenWidth(T_GL_HWIDGET signature, T_GL_DIM width) GL_EXCEPTION;

/** Gets the pen width
@param signature handle of the signature capture widget
@return pen width in pixels */
T_GL_DIM GL_Signature_GetPenWidth(T_GL_HWIDGET signature) GL_EXCEPTION;

/** Clears the signature area
@param signature handle of the signature capture widget */
void GL_Signature_Clear(T_GL_HWIDGET signature) GL_EXCEPTION;

/** Saves the signature captured into a file
@param signature handle of the signature capture widget
@param source source filename  (See @ref GL_Widget_Url for the url coding)*/
void GL_Signature_Save(T_GL_HWIDGET signature, const char * source) GL_EXCEPTION;

/** Loads the signature captured from a file
@param signature handle of the signature capture widget
@param source source filename (See @ref GL_Widget_Url for the url coding)*/
void GL_Signature_Load(T_GL_HWIDGET signature, const char * source) GL_EXCEPTION;


/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Signature_h_INCLUDED
