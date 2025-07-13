#ifndef GL_Viewer_h_INCLUDED
#define GL_Viewer_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif
/* 
*/
/**
@addtogroup GL_Viewer
@{
@addtogroup GL_ViewerDoc Viewer
@{
	This class is only used to initialize the viewer. 
@}
*/

/** Creating a viewer in the win32 environnement
@return returns the viewer handle created or null if creation failed 
@param hinstance WIN32 handle to application instance
@param hparent WIN32 handle to parent window */
T_GL_HVIEWER GL_Viewer_Create(long hinstance, long hparent) GL_EXCEPTION;

/** Destroy the viewer
@param viewer the viewer handle */
void GL_Viewer_Destroy(T_GL_HVIEWER viewer) GL_EXCEPTION;

#define GL_VIEWER_BLACK_WHITE  1           ///< used with black and white display
#define GL_VIEWER_12BPP_COLORS 12          ///< used with 12 bits per color pixel display
#define GL_VIEWER_18BPP_COLORS 18          ///< used with 18 bits per color pixel display

/** Sets the number of bits per pixels of the viewer
@param viewer the viewer handle 
@param bitsPerPixel number of bits per pixels*/
void GL_Viewer_SetBitsPerPixels(T_GL_HVIEWER viewer, long bitsPerPixel) GL_EXCEPTION;

/** Makes the viewer visible
@param viewer the viewer handle */
void GL_Viewer_Show (T_GL_HVIEWER viewer) GL_EXCEPTION;

/** Makes invisible viewer
@param viewer the viewer handle */
void GL_Viewer_Hide (T_GL_HVIEWER viewer) GL_EXCEPTION;

/** Sets the focus to the window
@param viewer viewer handle */
void GL_Viewer_SetFocus(T_GL_HVIEWER viewer) GL_EXCEPTION;

/** Sets the stylus cursor displayed on viewer
@param viewer viewer handle
@param cursor cursor type */
void GL_Viewer_SetCursor(T_GL_HVIEWER viewer, T_GL_CURSOR cursor) GL_EXCEPTION;

/** Sets the viewer size
@param viewer viewer handle
@param width new width coded according to the chosen unit
@param height new height coded according to the chosen unit */
void GL_Viewer_SetSize(T_GL_HVIEWER viewer, T_GL_DIM width, T_GL_DIM height) GL_EXCEPTION;

/** Gets the viewer size
@param viewer viewer handle
@return width and height */
T_GL_SIZE GL_Viewer_GetSize(T_GL_HVIEWER viewer);

/** Sets the position of the viewer
@param viewer viewer handle
@param x new X coordinates coded according to the chosen unit 
@param y new Y coordinates coded according to the chosen unit  */
void GL_Viewer_SetPosition(T_GL_HVIEWER viewer, T_GL_COORD x, T_GL_COORD y) GL_EXCEPTION;

/** Sets the title of viewer
@param viewer viewer handle
@param title title string  */
void GL_Viewer_SetTitle(T_GL_HVIEWER viewer, const char * title) GL_EXCEPTION;

/** Sets the scale display on the viewer
@param viewer viewer handle
@param scale rendering scale value */
void GL_Viewer_SetScale(T_GL_HVIEWER viewer, long scale) GL_EXCEPTION;

/** Sets the default file system directory
@param viewer viewer handle
@param directory default file system directory */
void GL_Viewer_SetFileSystemDirectory(T_GL_HVIEWER viewer, const char * directory) GL_EXCEPTION;

/** Sets the class style of the win32 window 
@param viewer viewer handle
@param style class style(see WNDCLASS style constant) */
void GL_Viewer_SetStyle(T_GL_HVIEWER viewer, unsigned long style) GL_EXCEPTION;

/** Shows the console window
@param viewer viewer handle */
void GL_Viewer_ShowConsole(T_GL_HVIEWER viewer) GL_EXCEPTION;

/** Gets the viewer version 
@return version */
T_GL_VERSION GL_Viewer_GetVersion(void) GL_EXCEPTION;

/** Gets the viewer package 
@return the Java package name */
const char * GL_Viewer_GetPackage(void) GL_EXCEPTION;

/** Sets the terminal type 
@param viewer viewer handle
@param type type name*/
void GL_Viewer_SetTerminalType(T_GL_HVIEWER viewer, const char * type) GL_EXCEPTION;

/** Sets the touch screen
@param viewer viewer handle
@param touch true the terminal is touch */
void GL_Viewer_SetTouch(T_GL_HVIEWER viewer, unsigned long touch) GL_EXCEPTION;

/** Garbage viewer cache
@param viewer viewer handle*/
void GL_Viewer_Garbage(T_GL_HVIEWER viewer) GL_EXCEPTION;
/**
@}
*/

#ifdef __cplusplus
}
#endif

#endif // GL_Viewer_h_INCLUDED
