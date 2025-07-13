// $Id: GL_Drawing.h,v 1.1.2.41 2012/05/23 07:03:48 rbertholet Exp $
// Graphic Object drawing
#ifndef GL_Drawing_h_INCLUDED
#define GL_Drawing_h_INCLUDED
#ifdef __cplusplus
extern "C"
{
#endif
/**
@addtogroup GL_Drawing
@{
@addtogroup GL_DrawingDoc  Drawing
@{

the drawing widget is a surface on which the user can draw a graph.
For this you must stack all the actions of drawing, for get the render you must call the function @ref GL_Window_Dispatch.
It is important to set all units in percentage or perthousand to get a draw that automatically adapts to screen size.

Below is a list of specific functions to this class :
	- @ref GL_Drawing_Create : Creating a drawing
	- @ref GL_Drawing_SetFont : Sets the font will be used to write text 
	- @ref GL_Drawing_SetPen : Sets the pen will be used to draw
	- @ref GL_Drawing_SetBrush : Sets the pen will be used to draw
	- @ref GL_Drawing_DrawLine : Draw a line with the pen
	- @ref GL_Drawing_DrawRect : Draw a rectangle with the pen and brush
	- @ref GL_Drawing_DrawEllipse : Draw an ellipse with the pen and brush
	- @ref GL_Drawing_DrawPie : Draw a pie with the pen and brush
	- @ref GL_Drawing_DrawText : Draw a text with the pen and brush
	- @ref GL_Drawing_DrawImage : Draw an image 
	- @ref GL_Drawing_AddPoint : Add point in the polygon, to display the polygon you must use @ref GL_Drawing_DrawPolygon
	- @ref GL_Drawing_DrawPolygon : Draws the polygon previously created with @ref GL_Drawing_AddPoint
	- @ref GL_Drawing_Clear : Clear the drawing 

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties

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

<h2>Sample</h2>

	Below is an example of creating a window with a drawing surface. 

	@image html drawingTest.png
	@include GL_SampleDrawing.c
@}
*/


/*<ALL>
	Extension("ACTIONPEN",         "ACTION",     "Define the pen",
		RefOne("color",            "COLOR",      "Pen color  (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue) coded decimal"),
		),
	Extension("ACTIONBRUSH",       "ACTION",     "Define the brush",
		RefOne("color",            "COLOR",      "brush color  (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue) coded decimal"),
		),
	Extension("ACTIONFONT",        "ACTION",     "Define the font action",
		RefOne("font",             "FONT",       "Font definition")
		),
	Extension("ACTIONTEXT",        "ACTION",     "Define the text action",
		RefOne("position",         "POSITION",   "Position of text"),
		String("text",                           "Text to display"),
		Bool("wrap",                             "The wrap allows text to automatically return to the line if it does not fit in width in the space allocated to it."),
		),
	Extension("ACTIONRECT",        "ACTION",     "Define the rectangle action",
		RefOne("position",         "POSITION",   "Position of rectangle"),
		RefOne("size",             "SIZE",       "Size of rectangle"),
		),
	Extension("ACTIONELLIPSE",     "ACTION",     "Define the ellipse action",
		RefOne("position",         "POSITION",   "Position of center "),
		RefOne("radius",           "SIZE",       "Radius"),
		),
	Extension("ACTIONPIE",         "ACTION",     "Define the pie action",
		RefOne("position",         "POSITION",   "Position of center "),
		RefOne("radius",           "SIZE",       "Radius"),
		Integer("angle1",                        "Start of arc in 64ths of a degree (anticlockwise from the x axis)"),
		Integer("angle2",                        "End of arc in 64ths of a degree (anticlockwise from the x axis)"),
		),
	Extension("ACTIONARC",         "ACTION",     "Define the arc action",
		RefOne("position",         "POSITION",   "Position of center"),
		RefOne("radius",           "SIZE",       "Radius"),
		RefOne("start",            "POSITION",   "Starting point of the arc"),
		RefOne("end",              "POSITION",   "End point of the arc"),
		),
	Extension("ACTIONLINE",        "ACTION",     "Define the line action",
		RefOne("point1",           "POSITION",   "First point of line"),
		RefOne("point2",           "POSITION",   "Second point of line"),
		),
	Extension("ACTIONIMAGE",       "ACTION",     "Define the image action",
		RefOne("source",           "SOURCEFILE", "Filename of the image (file name can contain alphanumeric, underscore, minus, spaces characters)"),
		RefOne("position",         "POSITION",   "Destination position of image"),
		),
	Extension("ACTIONSTRETCH",     "ACTION",     "Define the stretch image action",
		RefOne("source",           "SOURCEFILE", "Filename of the image (file name can contain alphanumeric, underscore, minus, spaces characters)"),
		RefOne("position",         "POSITION",   "Destination position of image"),
		RefOne("size",             "SIZE",       "Destination size of image"),
		),
	List("POINTS",                               "List of points",
		Item("position",          "POSITION",    "Define the point"),
		),
	ExtensionMany("ACTIONPOLYGON", "ACTION",     "Define the polygon action",
		RefMany("points",          "POINTS",     "List of points"),
		),
	List("ACTIONS",                               "List of drawing actions",
		Item("actionpen",         "ACTIONPEN",    "Define the pen"),  
		Item("actionbrush",       "ACTIONBRUSH",  "Define the brush"),  
		Item("actionfont",        "ACTIONFONT",   "Define the font action"),  
		Item("actiontext",        "ACTIONTEXT",   "Define the text action"),  
		Item("actionrect",        "ACTIONRECT",   "Define the rectangle action"),  
		Item("actionellipse",     "ACTIONELLIPSE","Define the ellipse action"),
		Item("actionpie",         "ACTIONPIE",    "Define the pie action"),
		Item("actionline",        "ACTIONLINE",   "Define the line action"),
		Item("actionimage",       "ACTIONIMAGE",  "Define the image action"),
		Item("actionstretch",     "ACTIONSTRETCH","Define the stretch image action"),
		Item("actionpolygon",     "ACTIONPOLYGON","Define the polygon action"),
		Item("actionarc",         "ACTIONARC",    "Define the arc action"),
		),
	BaseType("ACTION",                             "Generique drawing action"),
		
	ExtensionMany("DRAWING",           "WIDGET",     "the drawing widget is a surface on which the user can draw a graph",
		RefMany("actions",             "ACTIONS",    "Drawing actions"),
		Bool("vectorized",                          "If the mode is vectorized, all drawing commands are stored. In this case if you change the size of the widget the entire drawing is then scaled."),
	),
</ALL>*/


/** Creating a drawing
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_Drawing_Create(T_GL_HWIDGET parent) GL_EXCEPTION;


/** Sets the font will be used to write text 
@param drawing drawing handle
@param name font name 
@param style style of font
@param width font width coded according to the chosen unit 
@param height font width coded according to the chosen unit
@param unit unit of size */
void GL_Drawing_SetFont(T_GL_HWIDGET drawing, const char * name, T_GL_FONT_STYLE style, T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit) GL_EXCEPTION;

/** Sets the pen will be used to draw
@param drawing drawing handle
@param color to put on the pen
@param width stroke width 
@param unit unit of coordinates */
void GL_Drawing_SetPen(T_GL_HWIDGET drawing, T_GL_COLOR color, T_GL_DIM width, T_GL_UNIT unit) GL_EXCEPTION;

/** Sets the brush will be used to draw
@param drawing drawing handle
@param color to put on the brush */
void GL_Drawing_SetBrush(T_GL_HWIDGET drawing, T_GL_COLOR color) GL_EXCEPTION;

/** Draw a line with the pen
@param drawing drawing handle
@param x1 X coordinate of first point coded according to the chosen unit
@param y1 Y coordinate of first point coded according to the chosen unit
@param x2 X coordinate of second point coded according to the chosen unit
@param y2 Y coordinate of second point coded according to the chosen unit
@param unit unit of coordinates */
void GL_Drawing_DrawLine(T_GL_HWIDGET drawing, T_GL_COORD x1, T_GL_COORD y1, T_GL_COORD x2, T_GL_COORD y2, T_GL_UNIT unit) GL_EXCEPTION;

/** Draw a rectangle with the pen and brush
@param drawing drawing handle 
@param x X coordinate coded according to the chosen unit 
@param y Y coordinate coded according to the chosen unit 
@param width width coded according to the chosen unit
@param height height coded according to the chosen unit 
@param unit unit of coordinates */
void GL_Drawing_DrawRect(T_GL_HWIDGET drawing, T_GL_COORD x, T_GL_COORD y, T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit) GL_EXCEPTION;

/** Draw an ellipse with the pen and brush
@param drawing drawing handle 
@param x X center coordinates coded according to the chosen unit 
@param y Y center coordinates coded according to the chosen unit 
@param radiusX X radius coded according to the chosen unit
@param radiusY Y radius coded according to the chosen unit 
@param unit unit of coordinates */
void GL_Drawing_DrawEllipse(T_GL_HWIDGET drawing, T_GL_COORD x, T_GL_COORD y, T_GL_DIM radiusX, T_GL_DIM radiusY, T_GL_UNIT unit) GL_EXCEPTION;

/** Draw a pie with the pen and brush
@param drawing drawing handle 
@param x X center coordinates coded according to the chosen unit 
@param y Y center coordinates coded according to the chosen unit 
@param radiusX X radius coded according to the chosen unit
@param radiusY Y radius coded according to the chosen unit 
@param angle1 start of arc in 64ths of a degree (anticlockwise from the x axis)
@param angle2 end of arc in 64ths of a degree (anticlockwise from the x axis)
@param unit unit of coordinates */
void GL_Drawing_DrawPie (T_GL_HWIDGET drawing, T_GL_COORD x, T_GL_COORD y, T_GL_DIM radiusX, T_GL_DIM radiusY, long angle1, long angle2, T_GL_UNIT unit) GL_EXCEPTION;

/** Draw a text with the pen and brush
@param drawing drawing handle 
@param x X coordinate coded according to the chosen unit 
@param y Y coordinate coded according to the chosen unit 
@param unit unit of coordinates 
@param text text to draw (the default charset is UTF8, to change the charset use the function @ref GL_GraphicLib_SetCharset), WARNING: If the default charset is UTF8 and if you pass a non-UTF8 string all non-utf8 characters are replaced by '?' */
void GL_Drawing_DrawText(T_GL_HWIDGET drawing, T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit, const char * text) GL_EXCEPTION;

/** Draw an image 
@param drawing drawing handle 
@param x X coordinate coded according to the chosen unit 
@param y Y coordinate coded according to the chosen unit 
@param unit unit of coordinates
@param filename image filename (See @ref GL_Widget_Url for the url coding)*/
void GL_Drawing_DrawImage(T_GL_HWIDGET drawing, T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit, const char * filename) GL_EXCEPTION;


/** Stretch and draw an image 
@param drawing drawing handle 
@param x X coordinate coded according to the chosen unit 
@param y Y coordinate coded according to the chosen unit 
@param width destination width coded according to the chosen unit
@param height destination height coded according to the chosen unit 
@param unit unit of coordinates
@param filename image filename (See @ref GL_Widget_Url for the url coding)*/
void GL_Drawing_DrawStretchImage(T_GL_HWIDGET drawing, T_GL_COORD x, T_GL_COORD y, T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit, const char * filename) GL_EXCEPTION;


/** Add point in the polygon, to display the polygon you must use @ref GL_Drawing_DrawPolygon
@param drawing drawing handle 
@param x X coordinate coded according to the chosen unit 
@param y Y coordinate coded according to the chosen unit
@param unit unit of coordinates */
void GL_Drawing_AddPoint(T_GL_HWIDGET drawing, T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit) GL_EXCEPTION;


/** Draws the polygon previously created with @ref GL_Drawing_AddPoint
@param drawing drawing handle */
void GL_Drawing_DrawPolygon(T_GL_HWIDGET drawing) GL_EXCEPTION;


/** Clear the drawing 
@param drawing drawing handle */
void GL_Drawing_Clear(T_GL_HWIDGET drawing) GL_EXCEPTION;


/** Change the mode of vectorization. If the mode is vectorized, all drawing commands are stored. 
In this case if you change the size of the widget the entire drawing is then scaled.
If the mode is not vectorized, resizing the widget causes the loss of the drawing.
@param vectorized true indicates that the drawing is vectorized
@param drawing drawing handle */
void GL_Drawing_SetVectorized(T_GL_HWIDGET drawing, bool vectorized) GL_EXCEPTION;


/** Indicates the vectorized mode @ref GL_Drawing_SetVectorized
@param drawing drawing handle
@return indicates if the drawing is vectorized or not */
bool GL_Drawing_GetVectorized(T_GL_HWIDGET drawing) GL_EXCEPTION;


/** Draw raw data into a drawing. The image data source must be ordered according to the definition of the drawing memory returned by @ref GL_Drawing_GetPixelType.
The data drawed will be displayed at the next call of @ref GL_Window_Dispatch or @ref GL_Window_MainLoop.

IMPORTANT : The GL_Drawing_DrawArea writes data directly in the drawing, 
the drawing widget is completly created after an initial call to @ref GL_Window_Dispatch or @ref GL_Window_MainLoop.
All data written before the first call to @ref GL_Window_Dispatch will be lost.

IMPORTANT : The data drawed are lost if you resize the drawing.

In you use vectorized mode with this command that can produce strange results. 
In vectorized mode, drawing commands are executed only when calling the @ref GL_Window_Dispatch or @ref GL_Window_MainLoop, 
but for @ref GL_Drawing_DrawArea the result is immediately applied to the drawing.

@param drawing drawing handle
@param xDest x coordinate in pixels of the upper-left corner of the destination rectangle
@param yDest y coordinate in pixels of the upper-left corner of the destination rectangle
@param widthDest width in pixels of the source and destination rectangles
@param heightDest height in pixels of the source and the destination rectangles
@param source pointer to the source raw data buffer
@param xSrc x coordinate in pixels of the upper-left corner of the source rectangle
@param ySrc y coordinate in pixels of the upper-left corner of the source rectangle
@param widthSrc Width in pixels of the source image
@param heightSrc height in pixels of the source image */
void GL_Drawing_DrawArea (T_GL_HWIDGET drawing, 
                            T_GL_COORD xDest, T_GL_COORD yDest, T_GL_DIM widthDest, T_GL_DIM heightDest, 
                            void* source, 
                            T_GL_COORD xSrc, T_GL_COORD ySrc, T_GL_DIM widthSrc, T_GL_DIM heightSrc) GL_EXCEPTION;


/** Gets information about the encoding of the pixels
@param drawing drawing handle 
@return pixel type */
T_GL_PIXEL_TYPE GL_Drawing_GetPixelType(T_GL_HWIDGET drawing) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Drawing_h_INCLUDED
