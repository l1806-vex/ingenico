/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef _HID_INCLUDE_
#define _HID_INCLUDE_

#define GET_MOUSE	 0x8001  // for get the informations of the mouse button and dxdy,Wheel

#define GET_KEYS	 0x8001 // to read all the keys ==>  special and normal geographic keys

/*
======================================================================
					List of Defines
======================================================================
*/

#define GET_MOUSE	 0x8001 //!< for get the informations of the mouse button and dxdy,Wheel
#define GET_KEYS	 0x8001 //!< to read all the keys ==>  special and normal geographic keys
#define SET_KEYS	 0x8002 //!< set the new keyboard map

// value of special keys of the keyboard
#define CTRL_G  	1				//!< Key pressed on USB keyboard : Control + Left 
#define CTRL_D 	 	16			//!< Key pressed on USB keyboard : Control + Right 
#define SHIFT_G	 	2				//!< Key pressed on USB keyboard : Shift + Left 
#define SHIFT_D 	32			//!< Key pressed on USB keyboard : Control + Right 
#define ALT_G 		4				//!< Key pressed on USB keyboard : Alt + Left 
#define ALT_D 		64			//!< Key pressed on USB keyboard : Alt + Right 
#define WIN_G			8				//!< Key pressed on USB keyboard : Windows + Left 
#define WIN_D			128			//!< Key pressed on USB keyboard : Windows + Rigth 

#define SPECIAL_KEY  1		//!< Use with mask_event : If you choose the event each strike on the special key send an event to the application 

// definition de la table de redirection
// the first index is the geographic keys ( 102 keys)
// The second index is the state of the keys ( NORMAL/SHIFT/ALT/CTRL)
typedef char KEY[102][4];		/*!< Keyboard mapping definition :
        													- the first index is the geographic keys ( 102 keys)
        													- The second index is the state of the keys ( NORMAL/SHIFT/ALT/CTRL)
                            */
#define KEY_NORMAL 0				//!< Normal key 
#define KEY_SHIFT  1				//!< Shift + key 
#define KEY_CTRL   2				//!< Ctrl + key 
#define KEY_ALT    3				//!< Alt + key 

#define LEFT_BUTTON 	1			//!< define for mouse : left button pressed 
#define RIGHT_BUTTON 	2			//!< define for mouse : right button pressed
#define CENTER_BUTTON 4			//!< define for mouse : central button pressed


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This protoype is here only for compatibility. See #ttestall in oem_public.h for function description
*/
extern unsigned int ttestall(unsigned int events,unsigned int TimeOut);


#endif

/*! @}  */ 
