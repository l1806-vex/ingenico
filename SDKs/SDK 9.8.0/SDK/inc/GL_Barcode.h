// $Id: GL_Barcode.h,v 1.1.2.9 2012/08/24 12:42:52 rbertholet Exp $
// Barcode management
#ifndef GL_Barcode_h_INCLUDED
#define GL_Barcode_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_Barcode
@{
@addtogroup GL_BarcodeDoc Barcode
@{

This widget can display or print a barcode

Below is a list of specific functions to this class :
	- @ref GL_Barcode_Create : Creating a barcode

Information on barcodes :
	- Barcode QR : @ref GL_ParamBarcodeQr, @ref GL_TypesMimesBarcode

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
	- @ref GL_Widget_SetUserData
	- @ref GL_Widget_GetUserData
	- @ref GL_Widget_SetClickable
	- @ref GL_Widget_GetClickable
	- @ref GL_Widget_SetClickSensitive
	- @ref GL_Widget_GetClickSensitive


For messages sent by this widget see @ref GL_Widget_CommonMessage


<h2>Sample</h2>

	Below is an example of creating a window with a QR barcode. 

	@image html barcodeQrTest.png

	@include GL_SampleBarcodeQr.c

	Below is an example of creating a window with a PDF417 barcode. 

	@image html barcodePdf417Test.png

	@include GL_SampleBarcodePdf417.c

	Below is an example of creating a window with a EAN8 barcode. 

	@image html barcodeEAN8.png

	@include GL_SampleBarcodeEAN8.c

	Below is an example of creating a window with a EAN13 barcode. 

	@image html barcodeEAN13.png

	@include GL_SampleBarcodeEAN13.c

	Below is an example of creating a window with a CODE25 barcode. 

	@image html barcodeCODE25.png

	@include GL_SampleBarcodeCODE25.c

	Below is an example of creating a window with a CODE39 barcode. 

	@image html barcodeCODE39.png

	@include GL_SampleBarcodeCODE39.c

	Below is an example of creating a window with a CODE128 barcode. 

	@image html barcodeCODE128.png

	@include GL_SampleBarcodeCODE128.c
@}
*/

/*<ALL>
	Extension("BARCODE_PARAM_INTEGER",    "BARCODE_PARAM","Define a barcode integer parameter",
		String("name",                                    "Name of parameter"),
		Integer("valueinteger",                           "Value of parameter"),
		),

	Extension("BARCODE_PARAM_STRING",     "BARCODE_PARAM","Define a barcode string parameter",
		String("name",                                    "Name of parameter"),
		String("valuestring",                             "Value of parameter"),
		),

	List("BARCODE_PARAMS",                                "List of barcode parameters",
		Item("paraminteger",     "BARCODE_PARAM_INTEGER", "Define the integer barcode parameter"),
		Item("paramstring",      "BARCODE_PARAM_STRING",  "Define the string barcode parameter"),
		),

	BaseType("BARCODE_PARAM",                             "Bare code parameter"),
		
	Extension("BARCODE",           "WIDGET",          "Widget to display a barcode",
		String("mimetype",                                "Barcode mimetype"),
		RefOne("parameters",          "BARCODE_PARAMS",  "List of specific parameters for the barcode"),
	),
</ALL>*/

/** Creating a barcode
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_Barcode_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/** Sets the value of the barcode 
@param barcode widget barcode handle
@param value buffer which content the value 
@param size size of value buffer */
void GL_Barcode_SetValue(T_GL_HWIDGET barcode, const void * value, ulong size) GL_EXCEPTION;

/** Sets the mime type of the barcode
@param barcode widget barcode handle
@param mimeType mime type name @ref GL_TypesMimesBarcode */
void GL_Barcode_SetMimeType(T_GL_HWIDGET barcode, const char * mimeType) GL_EXCEPTION;

/** Sets a parameter width a chain terminated by a null character (@ref GL_ParamBarcodeQr)
@param barcode widget barcode handle
@param name parameter name
@param value parameter value (C string with null terminator) */
void GL_Barcode_SetParamString(T_GL_HWIDGET barcode, const char * name, const char * value) GL_EXCEPTION;

/** Sets a parameter width an integer (@ref GL_ParamBarcodeQr)
@param barcode widget barcode handle
@param name parameter name
@param value parameter value */
void GL_Barcode_SetParamInteger(T_GL_HWIDGET barcode, const char * name, long value) GL_EXCEPTION;

/** Sets a parameter width a binary buffer (@ref GL_ParamBarcodeQr)
@param barcode widget barcode handle
@param name parameter name
@param value pointer on the binary buffer
@param length length of value buffer */
void GL_Barcode_SetParamBuffer(T_GL_HWIDGET barcode, const char * name, const void * value, ulong length) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Barcode_h_INCLUDED
