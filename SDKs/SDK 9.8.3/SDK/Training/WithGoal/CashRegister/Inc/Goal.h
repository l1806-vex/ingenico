#include "GL_GraphicLib.h"


// Goal keys
// =========
#define K_VALID        0
#define KEY_VALID	   (1 << K_VALID)  // Mask Telium green key
#define K_CANCEL       1
#define KEY_CANCEL	   (1 << K_CANCEL) // Mask Telium red key
#define K_UP           2
#define KEY_UP	       (1 << K_UP)     // Telium up arrow key
#define K_DOWN         3
#define KEY_DOWN	   (1 << K_DOWN)   // Telium down arrow key

// Goal properties
// ===============
typedef struct stPadding
{
	T_GL_DIM usLeft;
	T_GL_DIM usTop;
	T_GL_DIM usRight;
	T_GL_DIM usBottom;
}ST_PADDING;

typedef struct stBorder
{
	T_GL_DIM usLeft;
	T_GL_DIM usTop;
	T_GL_DIM usRight;
	T_GL_DIM usBottom;
	T_GL_COLOR ulColor;
}ST_BORDER;

typedef struct stMargin
{
	T_GL_DIM usLeft;
	T_GL_DIM usTop;
	T_GL_DIM usRight;
	T_GL_DIM usBottom;
}ST_MARGIN;

typedef struct stFont
{
	const char *pcName;        // Font name (GOAL by default if null)
	T_GL_FONT_STYLE eStyle;    // Font style (Normal, Italic, Bold, BoldItalic)
	T_GL_SCALE eScale;         // Font scale (xxsmall, xsmall, medium, large, xlarge, xxlarge)
}ST_FONT;

typedef struct stDspColor
{
	T_GL_ALIGN eTextAlign;     // Widget text alignment
	T_GL_ALIGN eBackAlign;     // Widget background alignment
	T_GL_COLOR ulPen;          // Pen color
	T_GL_COLOR ulBrush;        // Brush color
	T_GL_DIM usSizeWidth;      // Background (width) size of the Widget
	bool bGrowWidth;           // Background (width) will fill the complete cell
	ST_PADDING xPadding;       // Widget text paddings properties
	ST_BORDER xBorder;         // Widget border properties
	ST_MARGIN xMargin;         // Widget margin properties
	ST_FONT xFont;             // Widget font properties
}ST_DSP_COLOR;

typedef struct stDspBW
{
	T_GL_ALIGN eTextAlign;     // Widget text alignment
	T_GL_ALIGN eBackAlign;     // Widget background alignment
	bool bReverse;             // Reverse mode (Black&White to White&Black)
	T_GL_DIM usSizeWidth;      // Background (width) size of the Widget
	bool bGrowWidth;           // Background (width) will fill the complete cell
	ST_PADDING xPadding;       // Widget padding properties
	ST_BORDER xBorder;         // Widget border properties
	ST_MARGIN xMargin;         // Widget margin properties
	ST_FONT xFont;             // Widget font properties
}ST_DSP_BW;

typedef struct stDspLine
{
	ST_DSP_COLOR xColor;       // Properties for color screen
	ST_DSP_BW xBW;             // Properties for B&W screen
}ST_DSP_LINE;

typedef struct stDrawFont
{
	const char *pcName;        // Font name
	T_GL_FONT_STYLE eStyle;    // Font style (Normal, Italic, Bold, BoldItalic)
	T_GL_DIM usWidth;          // Font width
	T_GL_DIM usHeight;         // Font height
}ST_DRAW_FONT;

typedef struct stPrnLine
{
	T_GL_ALIGN eTextAlign;     // Widget text alignment
	T_GL_ALIGN eBackAlign;     // Widget background alignment
	bool bReverse;             // Reverse mode (Black&White to White&Black)
	T_GL_DIM usSizeWidth;      // Background (width) size of the Widget
	ST_PADDING xPadding;       // Widget padding properties
	ST_BORDER xBorder;         // Widget border properties
	ST_MARGIN xMargin;         // Widget margin properties
	ST_FONT xFont;             // Widget font properties
}ST_PRN_LINE;

typedef struct stImgColor
{
	T_GL_COLOR ulPen;          // Pen color
	bool bGrowWidth;           // Background (width) will fill the complete cell
	ST_FONT xFont;             // Widget font properties
	T_GL_DIRECTION eExpand;    // Widget to expand
	ST_BORDER xBorder;         // Widget border properties
	ST_MARGIN xMargin;         // Widget margin properties
}ST_IMG_COLOR;

typedef struct stImgBW
{
	bool bGrowWidth;           // Background (width) will fill the complete cell
	ST_FONT xFont;             // Widget font properties
	T_GL_DIRECTION eExpand;    // Widget to expand
	ST_BORDER xBorder;         // Widget border properties
	ST_MARGIN xMargin;         // Widget margin properties
}ST_IMG_BW;

typedef struct stImage
{
	ST_IMG_COLOR xColor;       // Properties for color screen
	ST_IMG_BW xBW;             // Properties for B&W screen
}ST_IMAGE;

// Goal prototypes
// ===============
// *** Screen ***
T_GL_HWIDGET GoalCreateScreen (T_GL_HGRAPHIC_LIB xGraphicLib, const ST_DSP_LINE txLine[], ushort usMaxLine, T_GL_ENCODING_CHARSET eCharSet);
void GoalDestroyScreen(T_GL_HWIDGET *pxWindow);
int GoalClrScreen(T_GL_HWIDGET xWindow, T_GL_COLOR ulBackColor, unsigned int uiKeys, bool bRefresh);
void GoalRefreshScreen(T_GL_HWIDGET xWindow);
int GoalDspLine(T_GL_HWIDGET xWindow, ushort usLine, char *pcText, const ST_DSP_LINE* pxLine, ulong ulTimeOut, bool bRefresh);
int GoalDspMultiLine(T_GL_HWIDGET xWindow, ushort usLine, char *pcData , int iLen, const ST_DSP_LINE txLine[], ushort usMaxLine, ulong ulTimeOut, bool bRefresh);
int GoalGetKey(T_GL_HWIDGET xWindow, T_GL_HGRAPHIC_LIB xGraphicLib, bool bShortcut, ulong ulTimeOut, bool bClear);
// *** Drawing ***
T_GL_HWIDGET GoalCreateDrawing (T_GL_HGRAPHIC_LIB xGraphicLib, T_GL_ENCODING_CHARSET eCharSet);
void GoalDestroyDrawing(T_GL_HWIDGET *pxWindow);
int GoalClrDrawing(T_GL_HWIDGET xWindow, T_GL_COLOR ulBackColor, unsigned int uiKeys, bool bRefresh);
int GoalDrawLine(T_GL_HWIDGET xWindow, T_GL_COLOR ulPen, T_GL_COORD sX1, T_GL_COORD sY1, T_GL_COORD sX2, T_GL_COORD sY2, ulong ulTimeOut, bool bRefresh);
int GoalDrawRect(T_GL_HWIDGET xWindow, T_GL_COLOR ulPen, T_GL_COLOR ulBrush, T_GL_COORD sX, T_GL_COORD sY, T_GL_COORD sWidth, T_GL_COORD sHeight, ulong ulTimeOut, bool bRefresh);
int GoalDrawEllipse(T_GL_HWIDGET xWindow, T_GL_COLOR ulPen, T_GL_COLOR ulBrush, T_GL_COORD sX, T_GL_COORD sY, T_GL_DIM usRadiusX, T_GL_DIM usRadiusY, ulong ulTimeOut, bool bRefresh);
int GoalDrawText(T_GL_HWIDGET xWindow, const char* pcText, const ST_DRAW_FONT* pxFont, T_GL_COLOR ulPen, T_GL_COORD sX, T_GL_COORD sY, ulong ulTimeOut, bool bRefresh);
// *** Picture ***
T_GL_HWIDGET GoalCreatePicture (T_GL_HGRAPHIC_LIB xGraphicLib);
void GoalDestroyPicture(T_GL_HWIDGET *pxWindow);
int GoalClrPicture(T_GL_HWIDGET xWindow, T_GL_COLOR ulBackColor, unsigned int uiKeys, bool bRefresh);
int GoalDspPicture(T_GL_HWIDGET xWindow, char *pcTitle, const char* pcPicture, const ST_IMAGE* pxImage, ulong ulTimeOut, bool bRefresh);
// *** Document ***
T_GL_HWIDGET GoalCreateDocument (T_GL_HGRAPHIC_LIB xGraphicLib, T_GL_ENCODING_CHARSET eCharSet);
void GoalDestroyDocument(T_GL_HWIDGET *pxDocument);
int GoalPrnLine(T_GL_HWIDGET xDocument, ushort usLine, char *pcText, const ST_PRN_LINE* pxLine);
int GoalPrnMultiLine(T_GL_HWIDGET xDocument, ushort usLine, ushort usSize, char *pcData , ushort usLen, const ST_PRN_LINE* pxLine);
int GoalPrnPicture(T_GL_HWIDGET xDocument, ushort usLine, const char* pcPicture, const ST_BORDER* pxBorder);
int GoalPrnDocument(T_GL_HWIDGET xDocument);








