#ifndef GL_GraphicLib_hpp_INCLUDED
#define GL_GraphicLib_hpp_INCLUDED
#include "GL_GraphicLib.h"

/*
from glob import glob
from os.path import split, splitext

content = open ("..\\..\\_Inc_SDK\\Component\\GraphicLib\\GL_GraphicLib.hpp","r").read()
for filename in glob("stub\\source\\*.c"):
	fctname = splitext(split(filename)[1])[0]
	if not fctname in content:
		print fctname
*/

/* Ignored :
GL_Widget_SetTextById
GL_GraphicLib_SetUserArea
GL_Window_CreateOnRoot
GL_Test
GL_link
*/
namespace GL
{
	class Window;


	class SignatureFile
	{
	public:
		inline SignatureFile(const char * filename, unsigned long width, unsigned long height)
		{
			m_signature = GL_SignatureFile_Open(filename, width, height);
		}

		inline virtual ~SignatureFile()
		{
			GL_SignatureFile_Close(m_signature);
		}

		inline bool getPoint(unsigned long *x, unsigned long *y, unsigned long *pressure, unsigned long *time)
		{
			return GL_SignatureFile_GetPoint(m_signature, x, y, pressure, time);
		}

		inline void getTouchSize(unsigned long * width, unsigned long * height)
		{
			GL_SignatureFile_GetTouchSize(m_signature, width, height);
		}

		inline void getScreenSize(unsigned long * width, unsigned long * height)
		{
			GL_SignatureFile_GetScreenSize(m_signature, width, height);
		}

		inline void getBound(unsigned long *xMin, unsigned long *yMin, unsigned long *xMax, unsigned long *yMax)
		{
			GL_SignatureFile_GetBound(m_signature, xMin, yMin, xMax, yMax);
		}

		inline bool isOpen(void)
		{
			if (m_signature)
			{
				return true;
			}
			return false;
		}

	protected:
		T_GL_HSIGNATURE m_signature;
	};

	class StringList
	{
	public:
		inline StringList(T_GL_ENCODING_CHARSET charset)
		{
			m_list = GL_StringList_Create(charset);
		}

		inline virtual ~StringList()
		{
			GL_StringList_Destroy(m_list);
		}

		inline void clear(void)
		{
			GL_StringList_Clear(m_list);
		}

		inline unsigned long getCount(void)
		{
			return GL_StringList_GetCount(m_list);
		}

		inline T_GL_ENCODING_CHARSET getCharset(void)
		{
			return GL_StringList_GetCharset(m_list);
		}
		
		inline const char * getString(unsigned long index)
		{
			return GL_StringList_GetString(m_list, index);
		}

		inline void setString(unsigned long index, const char * value)
		{
			GL_StringList_SetString(m_list, index, value);
		}

		inline void removeString(unsigned long index)
		{
			GL_StringList_RemoveString(m_list, index);
		}

		inline void sddString(const char * value)
		{
			GL_StringList_AddString(m_list, value);
		}

		inline unsigned long search(const char * value)
		{
			GL_StringList_Search(m_list, value);
		}

		inline StringList clone(void)
		{
			StringList result(GL_StringList_Clone(m_list));
			return result;
		}

		inline void copy (StringList & source, StringList & target)
		{
			GL_StringList_Copy(source.m_list, target.m_list);
		}

		inline T_GL_HSTRINGLIST getHandle(void)
		{
			return m_list;
		}
	
	protected:
		T_GL_HSTRINGLIST m_list;

		inline StringList(T_GL_HSTRINGLIST list)
		{
			m_list = list;
		}
	};

	class Widget
	{
	protected:
		T_GL_HWIDGET m_widget;

	public:
		inline Widget(T_GL_HWIDGET widget)
		{
			m_widget = widget;
		}
			
		inline Widget(const Widget & widget)
		{
			m_widget = widget.m_widget;
		}
			
		inline void destroy(void)
		{
			GL_Widget_Destroy(m_widget);
		}

		inline T_GL_TYPE getType(void)
		{
			return GL_Widget_GetType(m_widget);
		}

		inline T_GL_SIZE getSize(void)
		{
			return GL_Widget_GetSize(m_widget);
		}

		inline void setSize(T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit)
		{
			GL_Widget_SetSize(m_widget, width, height, unit);
		}

		inline T_GL_SIZE getMinSize(void)
		{
			return GL_Widget_GetMinSize(m_widget);
		}

		inline void setMinSize(T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit)
		{
			GL_Widget_SetMinSize(m_widget, width, height, unit);
		}

		inline T_GL_SIZE getMaxSize(void)
		{
			return GL_Widget_GetMaxSize(m_widget);
		}

		inline void setMaxSize(T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit)
		{
			GL_Widget_SetMaxSize(m_widget, width, height, unit);
		}

		inline T_GL_POSITION getPosition(void)
		{
			return GL_Widget_GetPosition(m_widget);
		}

		inline void setPosition(T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit)
		{
			GL_Widget_SetPosition(m_widget, x, y, unit);
		}

		inline bool getVisible(void)
		{
			return GL_Widget_GetVisible(m_widget);
		}

		inline void setVisible(bool visible)
		{
			GL_Widget_SetVisible(m_widget, visible);
		}

		inline T_GL_ITEM getItem(void)
		{
			return GL_Widget_GetItem(m_widget);
		}

		inline void setItem(T_GL_DIM column, T_GL_DIM row)
		{
			GL_Widget_SetItem(m_widget, column, row);
		}

		inline T_GL_ALIGN getBackAlign()
		{
			return GL_Widget_GetBackAlign(m_widget);
		}

		inline void setBackAlign(T_GL_ALIGN align)
		{
			GL_Widget_SetBackAlign(m_widget, align);
		}

		inline T_GL_ALIGN getForeAlign(void)
		{
			return GL_Widget_GetForeAlign(m_widget);
		}

		inline void setForeAlign(T_GL_ALIGN align)
		{
			GL_Widget_SetForeAlign(m_widget, align);
		}

		inline void setMargins(T_GL_DIM left, T_GL_DIM top, T_GL_DIM right, T_GL_DIM bottom, T_GL_UNIT unit)
		{
			GL_Widget_SetMargins(m_widget, left, top, right, bottom, unit);
		}

		inline T_GL_MARGINS getMargins(void)
		{
			return GL_Widget_GetMargins(m_widget);
		}

		inline T_GL_COORD getMin(void)
		{
			return GL_Widget_GetMin(m_widget);
		}

		inline void setMin(T_GL_COORD min)
		{
			GL_Widget_SetMin(m_widget, min);
		}

		inline T_GL_COORD getMax(void)
		{
			return GL_Widget_GetMax(m_widget);
		}

		inline void setMax(T_GL_COORD max)
		{
			GL_Widget_SetMax(m_widget, max);
		}

		inline T_GL_COORD getValue(void)
		{
			return GL_Widget_GetValue(m_widget);
		}

		inline void setValue(T_GL_COORD value)
		{
			GL_Widget_SetValue(m_widget, value);
		}

		inline T_GL_COORD getPage(void)
		{
			return GL_Widget_GetPage(m_widget);
		}

		inline void setPage(T_GL_COORD page)
		{
			GL_Widget_SetPage(m_widget, page);
		}

		inline T_GL_COORD getStep(void)
		{
			return GL_Widget_GetStep(m_widget);
		}

		inline void setStep(T_GL_COORD step)
		{
			GL_Widget_SetStep(m_widget, step);
		}

		inline void setGrow(T_GL_DIRECTION grow)
		{
			GL_Widget_SetGrow(m_widget, grow);
		}

		inline T_GL_DIRECTION getGrow(void)
		{
			return GL_Widget_GetGrow(m_widget);
		}

		inline void setShrink(T_GL_DIRECTION shrink)
		{
			GL_Widget_SetShrink(m_widget, shrink);
		}

		inline T_GL_DIRECTION getShrink(void)
		{
			return GL_Widget_GetShrink(m_widget);
		}

		inline void setExpand(T_GL_DIRECTION expand)
		{
			GL_Widget_SetExpand(m_widget, expand);
		}

		inline T_GL_DIRECTION getExpand(void)
		{
			return GL_Widget_GetExpand(m_widget);
		}

		inline T_GL_ID getId(void)
		{
			return GL_Widget_GetId(m_widget);
		}

		inline void setId(T_GL_ID id)
		{
			GL_Widget_SetId(m_widget, id);
		}

		inline Widget searchId(T_GL_ID id)
		{
			Widget result(GL_Widget_SearchId(m_widget, id));
			return result;
		}

		inline T_GL_COLOR getBackColor(void)
		{
			return GL_Widget_GetBackColor(m_widget);
		}

		inline void setBackColor(T_GL_COLOR color)
		{
			GL_Widget_SetBackColor(m_widget, color);
		}

		inline T_GL_COLOR getForeColor(void)
		{
			return GL_Widget_GetForeColor(m_widget);
		}

		inline void setForeColor(T_GL_COLOR color)
		{
			GL_Widget_SetForeColor(m_widget, color);
		}

		inline bool getFocus(void)
		{
			return GL_Widget_GetFocus(m_widget);
		}

		inline void setFocus(void)
		{
			GL_Widget_SetFocus(m_widget);
		}

		inline bool getFocusable(void)
		{
			return GL_Widget_GetFocusable(m_widget);
		}

		inline void setFocusable(bool state)
		{
			GL_Widget_SetFocusable(m_widget, state);
		}

		inline bool getCheck(void)
		{
			return GL_Widget_GetCheck(m_widget);
		}

		inline void setCheck(bool check)
		{
			GL_Widget_SetCheck(m_widget, check);
		}

		inline void setText(const char * text)
		{
			GL_Widget_SetText(m_widget, text);
		}

		inline const char * getText(void)
		{
			return GL_Widget_GetText(m_widget);
		}

		inline void setFontName(const char * name)
		{
			GL_Widget_SetFontName(m_widget, name);
		}

		inline const char *getFontName(void)
		{
			return GL_Widget_GetFontName(m_widget);
		}

		inline void setFontSize(T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit)
		{
			GL_Widget_SetFontSize(m_widget, width, height, unit);
		}

		inline T_GL_SIZE getFontSize(void)
		{
			return GL_Widget_GetFontSize(m_widget);
		}

		inline void setFontStyle(T_GL_FONT_STYLE style)
		{
			GL_Widget_SetFontStyle(m_widget, style);
		}

		inline T_GL_FONT_STYLE getFontStyle(void)
		{
			return GL_Widget_GetFontStyle(m_widget);
		}

		inline void setSource(const char * filename)
		{
			GL_Widget_SetSource(m_widget, filename);
		}

		inline const char *getSource(void)
		{
			return GL_Widget_GetSource(m_widget);
		}

		inline void registerCallback(T_GL_EVENT_TYPE type, T_GL_MESSAGE_CALLBACK callback)
		{
			GL_Widget_RegisterCallback(m_widget, type, callback);
		}

		inline void unregisterCallback(T_GL_EVENT_TYPE type, T_GL_MESSAGE_CALLBACK callback)
		{
			GL_Widget_UnregisterCallback(m_widget, type, callback);
		}

		inline void setTextAlign(T_GL_ALIGN align)
		{
			GL_Widget_SetTextAlign(m_widget, align);
		}

		inline T_GL_ALIGN getTextAlign(void)
		{
			return GL_Widget_GetTextAlign(m_widget);
		}

		inline void setShortcut(wchar key)
		{
			GL_Widget_SetShortcut(m_widget, key);
		}

		inline wchar getShortcut(void)
		{
			return GL_Widget_GetShortcut(m_widget);
		}

		inline T_GL_HWIDGET getHandle(void)
		{
			return m_widget;
		}

		inline void setMask(const char * mask)
		{
			GL_Widget_SetMask(m_widget, mask);
		}

		inline void setFillChar1(wchar character)
		{
			GL_Widget_SetFillChar1(m_widget, character);
		}

		inline wchar getFillChar1(void)
		{
			return GL_Widget_GetFillChar1(m_widget);
		}

		inline void setFillChar2(wchar character)
		{
			GL_Widget_SetFillChar2(m_widget, character);
		}

		inline wchar getFillChar2(void)
		{
			return GL_Widget_GetFillChar2(m_widget);
		}

		inline void setPasswordChar(wchar character)
		{
			GL_Widget_SetPasswordChar(m_widget, character);
		}

		inline wchar getPasswordChar(void)
		{
			return GL_Widget_GetPasswordChar(m_widget);
		}

		inline void setMode(T_GL_MODE mode)
		{
			GL_Widget_SetMode(m_widget, mode);
		}

		inline T_GL_MODE getMode(void)
		{
			return GL_Widget_GetMode(m_widget);
		}

		inline void setInput(const char * text)
		{
			GL_Widget_SetInput(m_widget, text);
		}

		inline const char *getInput(void)
		{
			return GL_Widget_GetInput(m_widget);
		}

		inline void setTextPaddings(T_GL_DIM left, T_GL_DIM top, T_GL_DIM right, T_GL_DIM bottom, T_GL_UNIT unit)
		{
			GL_Widget_SetTextPaddings(m_widget, left, top, right, bottom, unit);
		}

		inline T_GL_PADDINGS getTextPaddings(void)
		{
			return GL_Widget_GetTextPaddings(m_widget);
		}

		inline void selectAll(void)
		{
			GL_Widget_SelectAll(m_widget);
		}

		inline void setUserData(const void * data, unsigned long dataSize)
		{
			GL_Widget_SetUserData(m_widget, data, dataSize);
		}

		inline unsigned long getUserData(void * data, unsigned long dataSize)
		{
			return GL_Widget_GetUserData(m_widget, data, dataSize);
		}

		inline void setTextById(T_GL_ID id, const char * format, ...)
		{
			va_list arg;
			va_start(arg, format);
			GL_Widget_SetVTextById(m_widget, id, format, arg);
			va_end(arg);
		}

		inline const char * getTextById(T_GL_ID id)
		{
			return GL_Widget_GetTextById(m_widget, id);
		}

		inline void setSourceById(T_GL_ID id, const char * source)
		{
			GL_Widget_SetSourceById(m_widget, id, source);
		}

		inline const char * getSourceById(T_GL_ID id)
		{
			return GL_Widget_GetSourceById(m_widget, id);
		}

		inline void setMaskById(T_GL_ID id, const char * mask)
		{
			GL_Widget_SetMaskById(m_widget, id, mask);
		}

		inline void setUserDataById(T_GL_ID id, const void * data, unsigned long dataSize)
		{
			GL_Widget_SetUserDataById(m_widget, id, data, dataSize);
		}

		inline unsigned long getUserDataById(T_GL_ID id, void * data, unsigned long dataSize)
		{
			return GL_Widget_GetUserDataById(m_widget, id, data, dataSize);
		}

		inline bool getCheckById(T_GL_ID id)
		{
			return GL_Widget_GetCheckById(m_widget, id);
		}

		inline void setCheckById(T_GL_ID id, bool check)
		{
			GL_Widget_SetCheckById(m_widget, id, check);
		}

		inline void registerCallbackById(T_GL_ID id, T_GL_EVENT_TYPE type, T_GL_MESSAGE_CALLBACK callback)
		{
			GL_Widget_RegisterCallbackById(m_widget, id, type, callback);
		}

		inline void unregisterCallbackById(T_GL_ID id, T_GL_EVENT_TYPE type, T_GL_MESSAGE_CALLBACK callback)
		{
			GL_Widget_UnregisterCallbackById(m_widget, id, type, callback);
		}

		inline void setBorders(T_GL_DIM left, T_GL_DIM top, T_GL_DIM right, T_GL_DIM bottom, T_GL_UNIT unit, T_GL_COLOR color)
		{
			GL_Widget_SetBorders(m_widget, left, top, right, bottom, unit, color);
		}

		inline T_GL_BORDERS getBorders(void)
		{
			return GL_Widget_GetBorders(m_widget);
		}

		inline T_GL_RECT getRect(void)
		{
			return GL_Widget_GetRect(m_widget);
		}

		inline void toggleCheck(void)
		{
			GL_Widget_ToggleCheck(m_widget);
		}

		inline void setFontScale(T_GL_SCALE scale)
		{
			GL_Widget_SetFontScale(m_widget, scale);
		}

		inline void setSourceFromBuffer(const void * bufferImage, unsigned long bufferSize)
		{
			GL_Widget_SetSourceFromBuffer(m_widget, bufferImage, bufferSize);
		}

		inline bool getClickable(void)
		{
			return GL_Widget_GetClickable(m_widget);
		}

		inline void setClickable(bool state)
		{
			GL_Widget_SetClickable(m_widget, state);
		}

		inline bool getClickSensitive(void)
		{
			return GL_Widget_GetClickSensitive(m_widget);
		}

		inline void setClickSensitive(bool state)
		{
			GL_Widget_SetClickSensitive(m_widget, state);
		}

		inline T_GL_TRANSFORMATION getTransformation(void)
		{
			return GL_Widget_GetTransformation(m_widget);
		}

		inline void setTransformation(T_GL_TRANSFORMATION transformation)
		{
			GL_Widget_SetTransformation(m_widget, transformation);
		}

		inline const char *getUserChar(void)
		{
			return GL_Widget_GetUserChar(m_widget);
		}

		inline void setUserChar(const char * value)
		{
			GL_Widget_SetUserChar(m_widget, value);
		}
		
		inline Widget readResource(Widget & parent, const char * filename)
		{
			return Widget(GL_Widget_ReadResource(parent.m_widget, filename));
		}

		inline Window getWindow(void);
	};

	class Viewer
	{
	public:
		inline Viewer(long hinstance = 0, long hparent = 0)
		{
			m_viewer = GL_Viewer_Create(hinstance, hparent);
		}

		inline virtual ~Viewer()
		{
			GL_Viewer_Destroy(m_viewer);
		}

		inline void setBitsPerPixels(long bitsPerPixel)
		{
			GL_Viewer_SetBitsPerPixels(m_viewer, bitsPerPixel);
		}
		
		inline void show (void)
		{
			GL_Viewer_Show (m_viewer);
		}

		inline void hide (void)
		{
			GL_Viewer_Hide (m_viewer);
		}

		inline void setFocus(void)
		{
			GL_Viewer_SetFocus(m_viewer);
		}

		inline void setCursor(T_GL_CURSOR cursor)
		{
			GL_Viewer_SetCursor(m_viewer, cursor);
		}

		inline void setSize(T_GL_DIM width, T_GL_DIM height)
		{
			GL_Viewer_SetSize(m_viewer, width, height);
		}

		inline void setPosition(T_GL_COORD x, T_GL_COORD y)
		{
			GL_Viewer_SetPosition(m_viewer, x, y);
		}

		inline void setTitle(const char * title)
		{
			GL_Viewer_SetTitle(m_viewer, title);
		}

		inline void setScale(long scale)
		{
			GL_Viewer_SetScale(m_viewer, scale);
		}

		inline void setFileSystemDirectory(const char * directory)
		{
			GL_Viewer_SetFileSystemDirectory(m_viewer, directory);
		}

		inline void setStyle(unsigned long style)
		{
			GL_Viewer_SetStyle(m_viewer, style);
		}

		inline void showConsole(void)
		{
			GL_Viewer_ShowConsole(m_viewer);
		}

		inline T_GL_VERSION getVersion(void)
		{
			return GL_Viewer_GetVersion();
		}

		inline void setTerminalType(const char * type)
		{
			GL_Viewer_SetTerminalType(m_viewer, type);
		}

		inline void setTouch(unsigned long touch)
		{
			GL_Viewer_SetTouch(m_viewer, touch);
		}

		inline T_GL_HVIEWER getHandle(void)
		{
			return m_viewer;
		}

	protected:
		T_GL_HVIEWER m_viewer;
	};

	class GraphicLib
	{
	protected:
		T_GL_HGRAPHIC_LIB m_handle;
	public:
		inline GraphicLib() 
		{
			m_handle = GL_GraphicLib_Create();
		}
			
		inline GraphicLib(Viewer & viewer, const char * skinName = 0)
		{
			m_handle = GL_GraphicLib_CreateWithParam(viewer.getHandle(), skinName);
		}
			
		inline virtual ~GraphicLib()
		{
			GL_GraphicLib_Destroy(m_handle);
		}
			
		inline Widget readRessource(const char * filename)
		{
			Widget result(GL_GraphicLib_ReadResource(m_handle, filename));
			return result;
		}
			
		inline const char * getErrorMessage()
		{
			return GL_GraphicLib_GetErrorMessages(m_handle);
		}
			
		inline void setCharset(T_GL_ENCODING_CHARSET charset)
		{
			GL_GraphicLib_SetCharset(m_handle, charset);
		}

		inline T_GL_ENCODING_CHARSET getCharset(void)
		{
			return GL_GraphicLib_GetCharset(m_handle);
		}

		inline void bindManyKey(wchar teliumKey, const wchar * keys, unsigned long count)
		{
			GL_GraphicLib_BindManyKey(m_handle, teliumKey, keys, count);
		}

		inline void bindOneKey(wchar teliumKey, wchar key)
		{
			GL_GraphicLib_BindSingleKey(m_handle, teliumKey, key);
		}
			
		inline void unbinKey(wchar teliumKey)
		{
			GL_GraphicLib_UnbindKey(m_handle, teliumKey);
		}

		inline T_GL_VERSION getVersion(void)
		{
			return GL_GraphicLib_GetVersion();
		}

		inline T_GL_HGRAPHIC_LIB getHandle(void)
		{
			return m_handle;
		}

		inline void sendKey(wchar key)
		{
			GL_GraphicLib_SendKey(m_handle, key);
		}

		inline void sendClick(T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit)
		{
			GL_GraphicLib_SendClick(m_handle, x, y, unit);
		}

		inline void sendBreak(void)
		{
			GL_GraphicLib_SendBreak	(m_handle);
		}
		
		inline void setWindowSize(T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit)
		{
			GL_GraphicLib_SetWindowSize(m_handle, width, height, unit);
		}

		inline void setWindowPosition(T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit)
		{
			GL_GraphicLib_SetWindowPosition(m_handle, x, y, unit);
		}

		inline const char *getTerminalType(void)
		{
			return GL_GraphicLib_GetTerminalType(m_handle);
		}

		inline T_GL_SIZE getScreenSize(void)
		{
			return GL_GraphicLib_GetScreenSize(m_handle);
		}

		inline ulong dialogMultiFile (const char * title, const char * root, const char * filter, StringList & files, T_GL_DIALOG_FILE_FILTER filterCallback, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_MultiFile (m_handle, title, root, filter, files.getHandle(), filterCallback, duration);
		}

		inline ulong iconButtonMenu (const char * title, const char ** menu, int selectedItem, T_GL_BUTTONS buttons, wchar shortcut, ulong duration)
		{
			return GL_Dialog_IconButtonMenu (m_handle, title, menu, selectedItem, buttons, shortcut, duration);
		}

		inline ulong dialogMessage(const char * title, const char * text, T_GL_DIALOG_ICON icon, T_GL_BUTTONS buttons, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_Message(m_handle, title, text, icon, buttons, duration);
		}

		inline ulong dialogDate (const char * title, const char * text, T_GL_HDATE date, const char * format, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_Date (m_handle, title, text, date, format, duration);
		}

		inline ulong dialogText (const char * title, const char * text, const char * mask, char * value, ulong valueSize, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_Text (m_handle, title, text, mask, value, valueSize, duration);
		}

		inline ulong dialogIp (const char * title, const char * text, T_GL_HIP ipAddr, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_Ip (m_handle, title, text, ipAddr, duration);
		}

		inline ulong dialogAmount (const char * title, const char * text, const char * mask, char * amount, ulong amountSize, const char * unit, T_GL_ALIGN unitAlign, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_Amount (m_handle, title, text, mask, amount, amountSize, unit, unitAlign, duration);
		}

		inline ulong dialogChoice (const char * title, const char ** menu, int selectedItem, T_GL_BUTTONS buttons = GL_BUTTON_DEFAULT, wchar shortcut = GL_KEY_1, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_Choice (m_handle, title, menu, selectedItem, buttons, shortcut, duration);
		}

		inline ulong dialogIconMenu (const char * title, const char ** menu, int selectedItem, T_GL_BUTTONS buttons = GL_BUTTON_DEFAULT, wchar shortcut = GL_KEY_1, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_IconMenu (m_handle, title, menu, selectedItem, buttons, shortcut, duration);
		}

		inline ulong dialogMenu (const char * title, const char ** menu, int selectedItem, T_GL_BUTTONS buttons = GL_BUTTON_DEFAULT, wchar shortcut = GL_KEY_1, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_Menu (m_handle, title, menu, selectedItem, buttons, shortcut, duration);
		}

		inline ulong dialogColor (const char * title, const char * text, T_GL_HCOLOR color, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_Color (m_handle, title, text, color, duration);
		}

		inline ulong dialogMedia (const char * title, const char * text, const char * source, byte volum, T_GL_BUTTONS buttons = GL_BUTTON_DEFAULT, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_Media (m_handle, title, text, source, volum, buttons, duration);
		}

		inline ulong dialogPicture (const char * title, const char * text, const char * source, T_GL_BUTTONS buttons = GL_BUTTON_DEFAULT, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_Picture (m_handle, title, text, source, buttons, duration);
		}

		inline ulong dialogSlider(const char * title, const char * text, const char * source, T_GL_COORD * value, T_GL_COORD min, T_GL_COORD max, T_GL_DIM step, T_GL_DIALOG_SLIDER_UPDATE update = 0, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_Slider(m_handle, title, text, source, value, min, max, step, update, duration);
		}

		inline ulong dialogProgress(const char * title, const char * text, const char * source, T_GL_COORD * value, T_GL_COORD min, T_GL_COORD max, T_GL_DIALOG_PROGRESS_UPDATE update = 0, T_GL_BUTTONS buttons = GL_BUTTON_DEFAULT, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_Progress(m_handle, title, text, source, value, min, max, update, buttons, duration);
		}

		inline ulong dialogFile(const char * title, const char * root, const char * filter, char * fileSelected, unsigned long fileSelectedSize, T_GL_DIALOG_FILE_FILTER filterCallback, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_File (m_handle, title, root, filter, fileSelected, fileSelectedSize, filterCallback, duration);
		}

		inline ulong virtualKeyboard (const char * title, const char * text, const char * mask, char * value, ulong valueSize, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_VirtualKeyboard (m_handle, title, text, mask, value, valueSize, duration);
		}

		inline ulong multiChoice (const char * title, const char ** menu, int selectedItem, bool * checkedItems, T_GL_BUTTONS buttons = GL_BUTTON_DEFAULT, wchar shortcut = GL_KEY_1, ulong duration= GL_TIME_INFINITE)
		{
			return GL_Dialog_MultiChoice (m_handle, title, menu, selectedItem, checkedItems, buttons, shortcut, duration);
		}

		inline ulong password (const char * title, const char * text, const char * mask, char * value, ulong valueSize, ulong duration = GL_TIME_INFINITE)
		{
			return GL_Dialog_Password (m_handle, title, text, mask, value, valueSize, duration);
		}

		inline ulong scheme (const char * title, const char * text, const char * help, T_GL_HSCHEME_INTERFACE interfac)
		{
			return GL_Dialog_Scheme (m_handle, title, text, help, interfac);
		}

		inline ulong signature (const char * title, const char * text, const char * filename, ulong duration)
		{
			return GL_Dialog_Signature(m_handle, title, text, filename, duration);
		}

		inline T_GL_ERROR_CODE getErrorCode(void)
		{
			return GL_GraphicLib_GetErrorCode(m_handle);
		}

		inline bool isTouch(void)
		{
			return GL_GraphicLib_IsTouchPresent(m_handle);
		}

		inline void setFontName(const char * name)
		{
			GL_GraphicLib_SetFontName(m_handle, name);
		}

		inline const char * getFontName(void)
		{
			return GL_GraphicLib_GetFontName(m_handle);
		}

		inline Widget getWidgetAtPosition(T_GL_COORD x, T_GL_COORD y)
		{
			Widget result(GL_GraphicLib_GetWidgetAtPosition(m_handle, x, y));
			return result;
		}

		inline const char * getDefaultPath(void)
		{
			return GL_GraphicLib_GetDefaultPath(m_handle);
		}

		inline void saveImage(const char * filename, const char * mimeType)
		{
			GL_GraphicLib_SaveImage(m_handle, filename, mimeType);
		}

		inline void setDefaultPath(const char * path)
		{
			GL_GraphicLib_SetDefaultPath(m_handle, path);
		}

		inline T_GL_RECT getUserArea(void)
		{
			return GL_GraphicLib_GetUserArea(m_handle);
		}
	};

	class Window;

	class Timer : public Widget
	{
	public:
		inline Timer(Window & window);

		inline Timer(T_GL_HWIDGET timer) : Widget(0)
		{
			m_widget = timer;
		}

		inline void start(void)
		{
			GL_Timer_Start(m_widget);
		}

		inline void stop(void)
		{
			GL_Timer_Stop(m_widget);
		}

		inline void setInterval(ulong interval)
		{
			GL_Timer_SetInterval(m_widget, interval);
		}

		inline ulong getInterval(void)
		{
			return GL_Timer_GetInterval(m_widget);
		}
	};

	class Message
	{
	protected:
		T_GL_HMESSAGE m_message;
	
	public:
		inline Message(T_GL_HMESSAGE message)
		{
			m_message = message;
		}

		inline T_GL_EVENT_TYPE getType(void)
		{
			return GL_Message_GetType(m_message);
		}

		inline T_GL_POSITION getPosition(void)
		{
			return GL_Message_GetPosition(m_message);
		}

		inline T_GL_MOVE getMove(void)
		{
			return GL_Message_GetMove(m_message);
		}

		inline wchar getKey(void)
		{
			return GL_Message_GetKey(m_message);
		}

		inline T_GL_SIZE getSize(void)
		{
			return GL_Message_GetSize(m_message);
		}

		inline Widget getWidget(void)
		{
			Widget result (GL_Message_GetWidget(m_message));
			return result;
		}

		inline Timer getTimer(void)
		{
			Timer result(GL_Message_GetTimer(m_message));
			return result;
		}

		inline T_GL_RANGE getRange(void)
		{
			return GL_Message_GetRange(m_message);
		}

		inline T_GL_HMESSAGE getHandle(void)
		{
			return m_message;
		}

		inline T_GL_HGRAPHIC_LIB getGraphicLib(void)
		{
			return GL_Message_GetGraphicLib(m_message);
		}

		inline void setResult(ulong result)
		{
			GL_Message_SetResult(m_message, result);
		}
		
		inline ulong getResult(void)
		{
			return GL_Message_GetResult(m_message);
		}

		inline void setUserData(const void * data, unsigned long dataSize)
		{
			GL_Message_SetUserData(m_message, data, dataSize);
		}

		inline unsigned long getUserData(void * data, unsigned long dataSize)
		{
			return GL_Message_GetUserData(m_message, data, dataSize);
		}

		inline Widget getWidgetById(T_GL_ID id)
		{
			return Widget(GL_Message_GetWidgetById(m_message, id));
		}

		inline ulong getTimerCount(void)
		{
			return GL_Message_GetTimerCount(m_message);
		}

		inline Window getWindow(void);
	};

	class Window : public Widget
	{
	public:
		inline Window(GraphicLib & graphicLib) : Widget(0)
		{
			m_widget = GL_Window_Create(graphicLib.getHandle());
		}

		inline Window(T_GL_HWIDGET window) : Widget(0)
		{
			m_widget = window;
		}

		inline Window(const Window & window) : Widget(0)
		{
			m_widget = window.m_widget;
		}

		inline void show(void)
		{
			GL_Window_Show (m_widget);
		}

		inline void hide(void)
		{
			GL_Window_Hide (m_widget);
		}

		inline void nextFocus(void)
		{
			GL_Window_NextFocus(m_widget);
		}

		inline void previousFocus(void)
		{
			GL_Window_PreviousFocus(m_widget);
		}

		inline void setCursor(T_GL_CURSOR cursor)
		{
			GL_Window_SetCursor(m_widget, cursor);
		}

		inline ulong dispatch(unsigned long duration)
		{
			return GL_Window_Dispatch(m_widget, duration);
		}

		inline void sendKey(wchar key)
		{
			GL_Window_SendKey(m_widget, key);
		}

		inline void sendClick(T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit)
		{
			GL_Window_SendClick(m_widget, x, y, unit);
		}

		inline void setResult(ulong result)
		{
			GL_Window_SetResult(m_widget, result);
		}

		inline ulong getResult(void)
		{
			return GL_Window_GetResult(m_widget);
		}

		inline ulong mainLoop(void)
		{
			return GL_Window_MainLoop(m_widget);
		}

		inline void setInactivityDuration(ulong duration)
		{
			GL_Window_SetInactivityDuration(m_widget, duration);
		}

		inline ulong getInactivityDuration(void)
		{
			return GL_Window_GetInactivityDuration(m_widget);
		}

		inline Widget getFocus(void)
		{
			Widget result(GL_Window_GetFocus(m_widget));
			return result;
		}

		inline Widget getWidgetAtPosition(T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit)
		{
			Widget result(GL_Window_GetWidgetAtPosition(m_widget, x, y, unit));
			return result;
		}

		inline void saveImage(const char * filename, const char * mimeType)
		{
			GL_Window_SaveImage(m_widget, filename, mimeType);
		}
	};


	class Button : public Widget
	{
	public:
		inline Button(Widget & parent) : Widget(0)
		{
			m_widget = GL_Button_Create(parent.getHandle());
		}
	};


	class CheckButton : public Widget
	{
	public:
		inline CheckButton(Widget & parent) : Widget(0)
		{
			m_widget = GL_CheckButton_Create(parent.getHandle());
		}
	};


	class Edit : public Widget
	{
	public:
		inline Edit(Widget & parent) : Widget(0)
		{
			m_widget = GL_Edit_Create(parent.getHandle());
		}
	};


	class VirtualKeyboard : public Widget
	{
	public:
		inline VirtualKeyboard(Widget & parent) : Widget(0)
		{
			m_widget = GL_VirtualKeyboard_Create(parent.getHandle());
		}

		inline void addPage(const char * pageName, const char * mapping)
		{
			GL_VirtualKeyboard_AddPage(m_widget, pageName, mapping);
		}

		inline void clearPages(void)
		{
			GL_VirtualKeyboard_ClearPages(m_widget);
		}
	};


	class HScrollBar : public Widget
	{
	public:
		HScrollBar(Widget & parent) : Widget(0)
		{
			m_widget = GL_HScrollBar_Create(parent.getHandle());
		}
	};


	class VScrollBar : public Widget
	{
	public:
		inline VScrollBar(Widget & parent) : Widget(0)
		{
			m_widget = GL_VScrollBar_Create(parent.getHandle());
		}
	};


	class Icon : public Widget
	{
	public:
		inline Icon (Widget & parent) : Widget(0)
		{
			m_widget = GL_Icon_Create(parent.getHandle());
		}
	};


	class IconButton : public Widget
	{
	public:
		inline IconButton (Widget & parent) : Widget(0)
		{
			m_widget = GL_IconButton_Create(parent.getHandle());
		}
	};


	class Label : public Widget
	{
	public:
		inline Label (Widget & parent) : Widget(0)
		{
			m_widget = GL_Label_Create(parent.getHandle());
		}
	};


	class Layout : public Widget
	{
	public:
		inline Layout(Widget & parent) : Widget(0)
		{
			m_widget = GL_Layout_Create(parent.getHandle());
		}
	};


	class List : public Widget
	{
	public:
		inline List(Widget & parent) : Widget(0)
		{
			m_widget = GL_List_Create(parent.getHandle());
		}

		inline ulong getCount(void)
		{
			return GL_List_GetCount(m_widget);
		}

		inline Widget getElement(ulong index)
		{
			Widget result(GL_List_GetElement(m_widget, index));
			return result;
		}

		inline void clear(void)
		{
			GL_List_Clear(m_widget);
		}
	};


	class Drawing : public Widget
	{
	public:
		inline Drawing(Widget & parent) : Widget(0)
		{
			m_widget = GL_Drawing_Create(parent.getHandle());
		}

		inline void setFont(const char * name, T_GL_FONT_STYLE style, T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit)
		{
			GL_Drawing_SetFont(m_widget, name, style, width, height, unit);
		}

		inline void setPen(T_GL_COLOR color, T_GL_DIM width, T_GL_UNIT unit)
		{
			GL_Drawing_SetPen(m_widget, color, width, unit);
		}

		inline void setBrush(T_GL_COLOR color)
		{
			GL_Drawing_SetBrush(m_widget, color);
		}

		inline void drawLine(T_GL_COORD x1, T_GL_COORD y1, T_GL_COORD x2, T_GL_COORD y2, T_GL_UNIT unit)
		{
			GL_Drawing_DrawLine(m_widget, x1, y1, x2, y2, unit);
		}

		inline void drawRect(T_GL_COORD x, T_GL_COORD y, T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit)
		{
			GL_Drawing_DrawRect(m_widget, x, y, width, height, unit);
		}

		inline void drawEllipse(T_GL_COORD x, T_GL_COORD y, T_GL_DIM radiusX, T_GL_DIM radiusY, T_GL_UNIT unit)
		{
			GL_Drawing_DrawEllipse(m_widget, x, y, radiusX, radiusY, unit);
		}

		inline void drawPie(T_GL_COORD x, T_GL_COORD y, T_GL_DIM radiusX, T_GL_DIM radiusY, long angle1, long angle2, T_GL_UNIT unit)
		{
			GL_Drawing_DrawPie (m_widget, x, y, radiusX, radiusY, angle1, angle2, unit);
		}

		inline void drawText(T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit, const char * text)
		{
			GL_Drawing_DrawText(m_widget, x, y, unit, text);
		}

		inline void drawImage(T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit, const char * filename)
		{
			GL_Drawing_DrawImage(m_widget, x, y, unit, filename);
		}

	#ifdef GL_TODO
		inline void drawStretchImage(T_GL_COORD x, T_GL_COORD y, T_GL_DIM width, T_GL_DIM height, T_GL_UNIT unit, const char * filename)
		{
			GL_Drawing_DrawStretchImage(m_widget, x, y, width, height, unit, filename);
		}
	#endif

		inline void addPoint(T_GL_COORD x, T_GL_COORD y, T_GL_UNIT unit)
		{
			GL_Drawing_AddPoint(m_widget, x, y, unit);
		}

		inline void drawPolygon(void)
		{
			GL_Drawing_DrawPolygon(m_widget);
		}

		inline void clear(void)
		{
			GL_Drawing_Clear(m_widget);
		}

		inline void setVectorized(bool vectorized)
		{
			GL_Drawing_SetVectorized(m_widget, vectorized);
		}

		inline bool getVectorized(void)
		{
			return GL_Drawing_GetVectorized(m_widget);
		}

		inline void drawArea (
								T_GL_COORD xDest, T_GL_COORD yDest, T_GL_DIM widthDest, T_GL_DIM heightDest, 
								void* source, 
								T_GL_COORD xSrc, T_GL_COORD ySrc, T_GL_DIM widthSrc, T_GL_DIM heightSrc)
		{
			GL_Drawing_DrawArea (m_widget, xDest, yDest, widthDest, heightDest, source, xSrc, ySrc, widthSrc, heightSrc);
		}

		inline T_GL_PIXEL_TYPE getPixelType(void)
		{
			return GL_Drawing_GetPixelType(m_widget);
		}
	};


	class Picture : public Widget
	{
	public:
		inline Picture(Widget & parent) : Widget(0)
		{
			m_widget = GL_Picture_Create(parent.getHandle());
		}
	};


	class ProgressBar : public Widget
	{
	public:
		inline ProgressBar(Widget & parent) : Widget(0) 
		{ 
			m_widget = GL_ProgressBar_Create(parent.getHandle());
		}
	};

	class Palette : public Widget
	{
	public:
		inline Palette(Widget & parent) : Widget(parent)
		{
			m_widget = GL_Palette_Create(parent.getHandle());
		}

		inline void configure(T_GL_DIM colors, T_GL_DIM lights)
		{
			GL_Palette_Configure(m_widget, colors, lights);
		}

		inline void setColor(T_GL_COLOR color)
		{
			GL_Palette_SetColor(m_widget, color);
		}

		inline T_GL_COLOR getColor(void)
		{
			return GL_Palette_GetColor(m_widget);
		}
	};



	class RadioButton : public Widget
	{
	public:
		inline RadioButton(Widget & parent) : Widget(0) 
		{
			m_widget = GL_RadioButton_Create(parent.getHandle());
		}
	};


	class ScrollView : public Widget
	{
	public:
		inline ScrollView(Widget & parent) : Widget(0)
		{
			m_widget = GL_ScrollView_Create(parent.getHandle());
		}

		inline void attachScrollbar(Widget & hscrollbar, Widget & vscrollbar)
		{
			GL_ScrollView_AttachScrollbar(m_widget, hscrollbar.getHandle(), vscrollbar.getHandle());
		}
	};

	class HSlider : public Widget
	{
	public:
		inline HSlider(Widget & parent) : Widget(0) 
		{
			m_widget = GL_HSlider_Create(parent.getHandle()); 
		}
	};

	class Media : public Widget
	{
	public:
		inline Media(Widget & parent) : Widget(0) 
		{
			m_widget = GL_Media_Create(parent.getHandle()); 
		}

		inline void start(void)
		{
			GL_Media_Start(m_widget);
		}

		inline void stop(void)
		{
			GL_Media_Stop(m_widget);
		}

		inline void pause(void)
		{
			GL_Media_Pause(m_widget);
		}

		inline void keepRatio(bool state)
		{
			GL_Media_KeepRatio(m_widget, state);
		}

		inline void setVolum(byte volum)
		{
			GL_Media_SetVolume(m_widget, volum);
		}

		inline void setLoop(bool loop)
		{
			GL_Media_SetLoop(m_widget, loop);
		}

		inline ulong getDuration(void)
		{
			return GL_Media_GetDuration(m_widget);
		}

		inline void setTime(ulong time)
		{
			GL_Media_SetTime(m_widget, time);
		}

		inline ulong getTime(void)
		{
			return GL_Media_GetTime(m_widget);
		}
	};

	class Document : public Widget
	{
	public:

		inline Document(GraphicLib & graphicLib) : Widget(0)
		{
			m_widget = GL_Document_Create(graphicLib.getHandle());
		}

		inline T_GL_ERROR_CODE print(unsigned int timeout)
		{
			return GL_Document_Print(m_widget, timeout);
		}

		inline void setShowOnScreen(void)
		{
			GL_Document_SetShowOnScreen(m_widget);
		}
	};


	class Plugin : public Widget
	{
	public:
		inline Plugin(Widget & parent) : Widget(0)
		{
			m_widget = GL_Plugin_Create(parent.getHandle());
		}

		inline long setParam(const char * name, const void * value, ulong valueLength)
		{
			return GL_Plugin_SetParam(m_widget, name, value, valueLength);
		}

		inline long getParam(const char * name, void * value, ulong valueLength)
		{
			return GL_Plugin_GetParam(m_widget, name, value, valueLength);
		}

		inline void setMimeType(const char * mimeType)
		{
			GL_Plugin_SetMimeType(m_widget, mimeType);
		}

		inline const char *getMimeType(void)
		{
			return GL_Plugin_GetMimeType(m_widget);
		}
	};

	class Signature : public Widget
	{
	public:
		inline Signature(Widget & parent) : Widget(0)
		{
			m_widget = GL_Signature_Create(parent.getHandle());
		}

		inline void load(const char * name)
		{
			GL_Signature_Load(m_widget, name);
		}

		inline void save(const char * name)
		{
			GL_Signature_Save(m_widget, name);
		}

		inline void clear(void)
		{
			GL_Signature_Clear(m_widget);
		}

		inline void setPenWidth(T_GL_DIM width)
		{
			GL_Signature_SetPenWidth(m_widget, width);
		}

		inline T_GL_DIM getPenWidth(void)
		{
			return GL_Signature_GetPenWidth(m_widget);
		}
	};

	class Print : public Widget
	{
	public:
		inline Print (Widget & parent) : Widget(0)
		{
			m_widget = GL_Print_Create(parent.getHandle());
		}
	};

	class Dir
	{
	public:
		inline Dir(const char * directory)
		{
			m_dir = GL_Dir_Open(directory);
		}

		inline T_GL_ERROR_CODE next(void)
		{
			return GL_Dir_Next(m_dir);
		}

		inline const char * getName(void)
		{
			return GL_Dir_GetName(m_dir);
		}

		inline const char * getPath(void)
		{
			return GL_Dir_GetPath(m_dir);
		}

		inline bool isDirectory(void)
		{
			return GL_Dir_IsDirectory(m_dir);
		}

		inline bool isFile(void)
		{
			return GL_Dir_IsFile(m_dir);
		}

		inline virtual ~Dir()
		{
			GL_Dir_Close(m_dir);
		}

		inline bool isOpen(void)
		{
			if (m_dir)
			{
				return true;
			}
			return false;
		}

	protected:
		T_GL_HDIR m_dir;
		
	};

	class File
	{
	public:
		inline File(const char* name, T_GL_FILE_OPEN_MODE mode, T_GL_FILE_ACCESS access)
		{
			m_file = GL_File_Open(name, mode, access);
		}
		
		inline virtual ~File()
		{
			GL_File_Close(m_file);
		}

		inline unsigned long read(void * buffer, unsigned long count)
		{
			return GL_File_Read(m_file, buffer, count);
		}

		inline unsigned long write(const void * buffer, unsigned long count)
		{
			return GL_File_Write(m_file, buffer, count);
		}

		inline T_GL_ERROR_CODE seek(long offset, T_GL_FILE_POS origin)
		{
			return GL_File_Seek(m_file, offset, origin);
		}

		inline long tell(void)
		{
			return GL_File_Tell(m_file);
		}

		static inline T_GL_ERROR_CODE delet(const char* name)
		{
			return GL_File_Delete(name);
		}

		static inline long getSizeFilename(const char* name)
		{
			return GL_File_GetSizeFilename(name);
		}

		inline long getSize(void)
		{
			return GL_File_GetSize(m_file);
		}

		static inline T_GL_ERROR_CODE getTimeFilename(const char* name, T_GL_FILE_TIME* time)
		{
			return GL_File_GetTimeFilename(name, time);
		}

		inline T_GL_ERROR_CODE getTime(T_GL_FILE_TIME* time)
		{
			return GL_File_GetTime(m_file, time);
		}

		inline bool isOpen(void)
		{
			if (m_file)
			{
				return true;
			}
			return false;
		}

		static bool matchPath (const char * path, const char * pattern)
		{
			return GL_File_MatchPath (path, pattern);
		}


	protected:
		T_GL_HFILE m_file;
	};






	// __NEWTYPE__


	inline Window Message::getWindow(void)
	{
		Window result(GL_Message_GetWindow(m_message));
		return result;
	}

	inline Timer::Timer(Window & window) : Widget(0)
	{
		m_widget = GL_Timer_Create(window.getHandle());
	}

	inline Window Widget::getWindow(void)
	{
		Window result(GL_Widget_GetWindow(m_widget));
		return result;
	}

	// __NEWTYPE__
};
#endif // GL_GraphicLib_hpp_INCLUDED
