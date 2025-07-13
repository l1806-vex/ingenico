// $Id: GL_Palette.h,v 1.1.2.15 2012/03/05 11:10:03 rbertholet Exp $
// Palette management
#ifndef GL_Palette_h_INCLUDED
#define GL_Palette_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_Palette
@{
@addtogroup GL_PaletteDoc Color palette
@{

A palette is a widget that can display a palette

Below is a list of specific functions to this class :
	- @ref GL_Palette_Create : Creating a palette
	- @ref GL_Palette_Configure : Configures the number of pieces of color in the palette
	- @ref GL_Palette_SetColor : Change the color selected in the palette displayed
	- @ref GL_Palette_GetColor : Returns the selected color in the palette

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_ImagesProperties
	- @ref GL_Widget_CallbackProperties

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

For messages sent by this widget see @ref GL_Widget_CommonMessage

<h2>Sample</h2>

	Below is an example of creating a window with a palette. 

	@image html paletteTest.png

	@include GL_SamplePalette.c
@}
*/

/*<ALL>
	Extension("PALETTE",           "WIDGET",     "A palette is a widget that can display a color palette",
		Integer("bordercolor",                   "Border color of the color item"),
		Integer("focusbackcolor",                "Background color of the focus"),
		Integer("focusforecolor",                "Foreground color of the focus"),
		Integer("focussize",                     "Thickness of the color focus selected on the palette"),
		Integer("maxcolors",                     "Maximum number of colors present on the palette (This value is the number of columns)"),
		Integer("maxlights",                     "Minimum number of colors present on the palette (This value is the number of rows)"),
		),
</ALL>*/

/** Creating a palette
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_Palette_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/** Configures the number of pieces of color in the palette
@param palette palette handle
@param colors sets the number of colors, the minimum allowed is @ref GL_PALETTE_MIN_COLOR, the maximum allowed is @ref GL_PALETTE_MAX_COLOR
@param lights sets the number of light level, the minimum allowed is @ref GL_PALETTE_MIN_LIGHT, the maximum allowed is @ref GL_PALETTE_MAX_LIGHT */
void GL_Palette_Configure(T_GL_HWIDGET palette, T_GL_DIM colors, T_GL_DIM lights) GL_EXCEPTION;

/** Change the color selected in the palette displayed, the color value must exactly match with a color in the palette else it is ignored
@param palette palette handle
@param color color to set */
void GL_Palette_SetColor(T_GL_HWIDGET palette, T_GL_COLOR color) GL_EXCEPTION;

/** Returns the selected color in the palette
@param palette palette handle
@return selected color */
T_GL_COLOR GL_Palette_GetColor(T_GL_HWIDGET palette) GL_EXCEPTION;

/** Minimum number of color palette */
#define GL_PALETTE_MIN_COLOR 2

/** Maximum number of color palette */
#define GL_PALETTE_MAX_COLOR 12

/** Minimum number of light palette */
#define GL_PALETTE_MIN_LIGHT 1

/** Maximum number of light palette */
#define GL_PALETTE_MAX_LIGHT 9

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Palette_h_INCLUDED
