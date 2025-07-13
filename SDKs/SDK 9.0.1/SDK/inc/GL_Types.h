// $Id: GL_Types.h,v 1.1.2.52 2012/01/16 08:12:56 rbertholet Exp $
// Common types shared between the graphics server and the graphic library
#ifndef GL_Types_h_INCLUDED
#define GL_Types_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

#include "GL_CommonTypes.h"

/**
@addtogroup GL_Types
@{
@addtogroup GL_TypesStruct Structures
@{
*/

/*<ALL>
	Enum("UNIT",                                 "Unit supported by the graphical library.",
		Define("pixel",            "0",          "Dimensions or position are expressed in pixels"),
		Define("percent",          "1",          "Dimensions or position are expressed in percentage of parent"),
		Define("perthousand",      "2",          "Dimensions or position are expressed in per thousand of parent"),
		Define("px",               "0",          "Dimensions or position are expressed in pixels"),
		Define("%",               "1",          "Dimensions or position are expressed in percentage of parent"),
		Define("%%",             "2",          "Dimensions or position are expressed in per thousand of parent"),
		),    
</ALL>*/
/** Unit supported by the graphical library.
When you select the unit GL_UNIT_PERCENT, the position and dimension on the screen are expressed in 
ten thousandth of the width or height of the screen. */
typedef enum T_GL_UNIT 
{
	GL_UNIT_PIXEL,      ///< all dimensions and position are expressed in pixels
	GL_UNIT_PERCENT,    ///< all dimensions and position are expressed in percentage of parent
	GL_UNIT_PERTHOUSAND ///< all dimensions and position are expressed in per thousand of parent
} T_GL_UNIT;

#define GL_VALUE_PERCENT 100      ///< Percent value
#define GL_VALUE_PERTHOUSAND 1000 ///< Perthousand value


/** Defines a coordinates type. (See special values @ref GL_DIM_UNDEFINED, @ref GL_DIM_MIN, @ref GL_DIM_MAX) */
typedef short T_GL_COORD;

/** Defines a dimension type (See special values @ref GL_DIM_UNDEFINED, @ref GL_DIM_MIN, @ref GL_DIM_MAX) */
typedef unsigned short T_GL_DIM;

/*<ALL>
	Struct("SIZE",                               "Defines a size",
		Integer("width",                         "Width coded according to the chosen unit"),
		Integer("height",                        "Height coded according to the chosen unit"),
		RefOne("unit",             "UNIT",       "Unit used"),
		),
</ALL>*/
/** Defining a Dimension */
typedef struct T_GL_SIZE
{
#ifdef WIN32
	/** Width coded according to the chosen unit */
	T_GL_DIM width;
	
	/** Height coded according to the chosen unit */
	T_GL_DIM height;

	/** Unit of size */
	T_GL_UNIT unit;
#else
	/** Width coded according to the chosen unit */
	unsigned int width:15;
	
	/** Height coded according to the chosen unit */
	unsigned int height:15;

	/** Unit of size */
	unsigned int unit:2;
#endif 
} T_GL_SIZE;

/** Handle on size */
typedef T_GL_SIZE * T_GL_HSIZE;

/*<ALL>
	Struct("POSITION",                           "Defines a position",
		Integer("x",                             "x coordinates coded according to the chosen unit"),
		Integer("y",                             "y coordinates coded according to the chosen unit"),
		RefOne("unit",             "UNIT",       "Unit used"),
		),
</ALL>*/
/** Defines a position */
typedef struct T_GL_POSITION
{
#ifdef WIN32
	/** X coded according to the chosen unit */
	T_GL_COORD x;
	
	/** Y coded according to the chosen unit */
	T_GL_COORD y;

	/** Unit of position */
	T_GL_UNIT unit;
#else
	/** X coded according to the chosen unit */
	int x:15;
	
	/** Y coded according to the chosen unit */
	int y:15;

	/** Unit of position */
	unsigned int unit:2;
#endif
} T_GL_POSITION;

/** Handle on position */
typedef T_GL_POSITION * T_GL_HPOSITION;


/** Move */
typedef T_GL_POSITION T_GL_MOVE;

/** Handle on move */
typedef T_GL_MOVE * T_GL_HMOVE;

/*<ALL>
	Struct("MARGINS",                            "Defines all margins",
		Integer("left",                          "Left margin coded according to the chosen unit"),
		Integer("top",                           "Top margin coded according to the chosen unit"),
		Integer("right",                         "Right margin coded according to the chosen unit"),
		Integer("bottom",                        "Bottom margin coded according to the chosen unit"),
		RefOne("unit",             "UNIT",       "Unit used"),
		),
</ALL>*/
/** Defines a margins */
typedef struct T_GL_MARGINS
{
#ifdef WIN32
	/** Left margin coded according to the chosen unit */
	T_GL_DIM left;

	/** Top margin coded according to the chosen unit */
	T_GL_DIM top;

	/** Right margin coded according to the chosen unit */
	T_GL_DIM right;

	/** Bottom margin coded according to the chosen unit */
	T_GL_DIM bottom;

	/** Unit of margin */
	T_GL_UNIT unit;
#else
	/** Left margin coded according to the chosen unit */
	unsigned int left:15;

	/** Top margin coded according to the chosen unit */
	unsigned int top:15;

	/** Right margin coded according to the chosen unit */
	unsigned int right:15;

	/** Bottom margin coded according to the chosen unit */
	unsigned int bottom:15;

	/** Unit of margin */
	unsigned int unit:2;
#endif
} T_GL_MARGINS;

/** Margins handle */
typedef T_GL_MARGINS * T_GL_HMARGINS;

/*<ALL>
	Struct("PADDINGS",                           "Defines a paddings",
		Integer("left",                          "Left padding coded according to the chosen unit"),
		Integer("top",                           "Top padding coded according to the chosen unit"),
		Integer("right",                         "Right padding coded according to the chosen unit"),
		Integer("bottom",                        "Bottom padding coded according to the chosen unit"),
		RefOne("unit",             "UNIT",       "Unit used"),
		),
</ALL>*/
/** Defines paddings */
typedef T_GL_MARGINS T_GL_PADDINGS;

/** Paddings handle */
typedef T_GL_PADDINGS * T_GL_HPADDINGS;


/*<ALL>
	Struct("BORDERS",                            "Defines a borders",
		Integer("left",                          "Left border coded according to the chosen unit"),
		Integer("top",                           "Top border coded according to the chosen unit"),
		Integer("right",                         "Right border coded according to the chosen unit"),
		Integer("bottom",                        "Bottom border coded according to the chosen unit"),
		RefOne("unit",             "UNIT",       "Unit used"),
		RefOne("color",            "COLOR",      "border color (0xAARRGGBB, AA=alpha, RR=red, GG=green, BB=blue)"),
		),
</ALL>*/

/** Defines a borders */
typedef struct T_GL_BORDERS
{
	/** Border size */
	T_GL_MARGINS size;

	/** Border colors */
	T_GL_COLOR color;
} T_GL_BORDERS;

/** Borders handle */
typedef T_GL_BORDERS * T_GL_HBORDERS;


/** Rectangle */
typedef struct T_GL_RECT
{
	/** Defines a position */
	T_GL_POSITION position;

	/** Defining a Dimension */
	T_GL_SIZE     size;
} T_GL_RECT;

/** Handle on rectangle */
typedef T_GL_RECT * T_GL_HRECT;

/*<ALL>
	Struct("RANGE","Range",
		Integer("min",                           "The minimum limit of the scroll bar"),
		Integer("max",                           "The maximum limit of the scroll bar"),
		Integer("value",                         "The value of the scroll bar"),
		Integer("page",                          "The page size of the scroll bar (scales the size of slider in the scrollbar)"),
		Integer("step",                          "The step increment"),
		),  
</ALL>*/
/** Range */
typedef struct T_GL_RANGE
{
	/** lower bound */
	T_GL_COORD min;

	/** upper bound */
	T_GL_COORD max;

	/** current value */
	T_GL_COORD value;

	/** page */
	T_GL_DIM page;

	/** step */
	T_GL_DIM step;
} T_GL_RANGE;

/** Handle on range */
typedef T_GL_RANGE * T_GL_HRANGE;


/** Date */
typedef struct T_GL_DATE
{
	/** Year (1900..2100) */
	ushort year;

	/** Month (1..12) */
	byte month;

	/** Day (1..31) */
	byte day;

	/** Hour (0..23) */
	byte hour;

	/** Minute (0..59) */
	byte minute;

	/** Second (0..59) */
	byte second;
}T_GL_DATE;

/** Date handle */
typedef T_GL_DATE * T_GL_HDATE;


/** Ip V4 address string */
typedef struct T_GL_IP_STR
{
#define GL_IP_MAX 16 ///< Maximal size of ip address string

	/** Ip address string */
	char address[GL_IP_MAX];
} T_GL_IP_STR;

/** Ip V4 address handle */
typedef T_GL_IP_STR * T_GL_HIP_STR;

/** Ip V4 address integer value  (0x01020304 -> 001.002.003.004) */
typedef unsigned long T_GL_IP;

/** Ip V4 address integer handle */
typedef T_GL_IP * T_GL_HIP;

/**
@}
@}
*/


#ifdef __cplusplus
}
#endif

#endif // GL_Types_h_INCLUDED
