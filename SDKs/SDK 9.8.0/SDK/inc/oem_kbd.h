/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

# ifndef __OEM_KEYBOARD_H
# define __OEM_KEYBOARD_H

/*
======================================================================
			Data Structures Definition
======================================================================
*/

typedef struct { 
 unsigned int      Xconf;		            /*!< used by FIOCTL_READ_KEYBOARD_STATES fioctl() : filtered keyboard state */
 unsigned int 	   Xacq;		            /*!< used by FIOCTL_READ_KEYBOARD_STATES fioctl() : unfiltered keyboard state*/
}t_kbd_states;  


/*
======================================================================
					List of Defines
======================================================================
*/

#define    FIOCTL_AVAPAP_KEY      				0x8000	/*!< parameter type is unsigned char : read key value returned when paper-feed key is pressed */
#define    FIOCTL_READ_KEYBOARD   				0x8001	/*!< parameter type is unsigned char : read current key pressed : 0=no key pressed */
#define    FIOCTL_READ_KEYBOARD_STATES   		0x8002	/*!< parameter type is t_kbd_states  : read keyboard bitmap */
#define    FIOCTL_READ_KEYBOARD_KEY_VALUE 		0x8003	/*!< parameter type is unsigned int  : read key value returned for specified key index (0 if not used) */
#define	   FIOCTL_LOCK_MAINTENANCE_KEYBOARD		0x8004	/*!< lock maintenance keyboard on iUC180 */

#endif

/*! @}  */ 


