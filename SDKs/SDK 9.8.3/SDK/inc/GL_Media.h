// $Id: GL_Media.h,v 1.1.2.26 2012/08/24 12:42:52 rbertholet Exp $
// Media management
#ifndef GL_Media_h_INCLUDED
#define GL_Media_h_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/**
@addtogroup GL_Media
@{
@addtogroup GL_MediaDoc Multimedia
@{

This class is used to play movie or sound.

Below is a list of specific functions to this class :
	- @ref GL_Media_Create : Creating a media
	- @ref GL_Media_Start : Start playback of a media
	- @ref GL_Media_Stop : Stop playback of a media
	- @ref GL_Media_Pause : Pause playback of a media
	- @ref GL_Media_KeepRatio : Keep ratio of a media
	- @ref GL_Media_SetVolume : Sets the volume

For more details of the functions shared with the class widget see :
	- @ref GL_Widget_UnitProperties
	- @ref GL_Widget_GeometryProperties
	- @ref GL_Widget_LayoutProperties
	- @ref GL_Widget_IdProperties
	- @ref GL_Widget_AppearanceProperties
	- @ref GL_Widget_CallbackProperties
	- @ref GL_Widget_ShortcutProperties
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
	- @ref GL_Widget_SetShrink
	- @ref GL_Widget_GetShrink
	- @ref GL_Widget_SetGrow
	- @ref GL_Widget_GetGrow
	- @ref GL_Widget_SetExpand
	- @ref GL_Widget_GetExpand
	- @ref GL_Widget_SetSource
	- @ref GL_Widget_GetSource
	- @ref GL_Widget_SetShortcut
	- @ref GL_Widget_GetShortcut
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

	Below is an example of creating a blank window with a video.

	@image html mediaTest.png

	@include GL_SampleMedia.c

	Below is an example of player video.

	@image html mediaTest2.png

	@include GL_SamplePlayer.c
@}
*/

/*<ALL>
	Extension("MEDIA",             "WIDGET",     "This class is used to play movie or sound",
		Bool("loop",                             "The video has preserved its width height ratio"),
		Bool("keepratio",                        "The video has preserved its width height ratio"),
		RefOne("source",           "SOURCEFILE","Filename of the audio or video file (file name can contain alphanumeric, underscore, minus, spaces characters)"),
		Byte("volume",                           "Volume level (0..255) 255=loud"),
		),
</ALL>*/

/** Creating a media
@param parent handle on the parent widget
@return returns the widget handle created or null if creation failed */
T_GL_HWIDGET GL_Media_Create(T_GL_HWIDGET parent) GL_EXCEPTION;

/** Starts playback of a media
@param media media handle */
void GL_Media_Start(T_GL_HWIDGET media) GL_EXCEPTION;

/** Stops playback of a media
@param media media handle */
void GL_Media_Stop(T_GL_HWIDGET media) GL_EXCEPTION;

/** Pauses playback of a media
@param media media handle */
void GL_Media_Pause(T_GL_HWIDGET media) GL_EXCEPTION;

/** Keeps ratio of a media
@param media media handle
@param state true indicates that the ratio is kept, false indicates that the ratio is lost */
void GL_Media_KeepRatio(T_GL_HWIDGET media, bool state) GL_EXCEPTION;

/** Sets the volume
@param media media handle 
@param volume volume level (0..255, 255=loud) */
void GL_Media_SetVolume(T_GL_HWIDGET media, byte volume) GL_EXCEPTION;

/** Play video loop
@param media media handle 
@param loop true=loop, false=once */
void GL_Media_SetLoop(T_GL_HWIDGET media, bool loop) GL_EXCEPTION;

/** Gets the total time duration of the video
@param media media handle 
@return the duration in milliseconds */
ulong GL_Media_GetDuration(T_GL_HWIDGET media) GL_EXCEPTION;

/** Set the viewing of video at a given time
@param media media handle 
@param time time in milliseconds */
void GL_Media_SetTime(T_GL_HWIDGET media, ulong time) GL_EXCEPTION;

/** Gets the current time of the video 
@param media media handle 
@return time in milliseconds */
ulong GL_Media_GetTime(T_GL_HWIDGET media) GL_EXCEPTION;

/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif // GL_Media_h_INCLUDED
