
#ifndef _OEM_ISPM_H_
#define _OEM_ISPM_H_


#define APPLE_FIOCTL_EXTERNAL		    		(0x8000)
#define APPLE_FIOCTL_CDE_IPxxx_CHARGING	        (APPLE_FIOCTL_EXTERNAL + 0)
#define APPLE_FIOCTL_START_SSL_GATEWAY 			(APPLE_FIOCTL_EXTERNAL + 1)
#define APPLE_FIOCTL_GET_CNX_STATE 		    	(APPLE_FIOCTL_EXTERNAL + 2)
#define APPLE_FIOCTL_GET_IPxxx_BATTERY_LEVEL    (APPLE_FIOCTL_EXTERNAL + 3)
#define APPLE_FIOCTL_GET_IPxxx_CHARGING_INFO    (APPLE_FIOCTL_EXTERNAL + 4)
#define APPLE_FIOCTL_BARCODE_INIT               (APPLE_FIOCTL_EXTERNAL + 5)
#define APPLE_FIOCTL_BARCODE_UNLOCKED           (APPLE_FIOCTL_EXTERNAL + 6) /*!<must be used only in factory forbidden in the field*/ 

/* see APPLE_FIOCTL_GET_CNX_STATE */
#define STEP_APPLE_OK                    (unsigned char)  0
#define STEP_APPLE_NOT_INITIALIZED       (unsigned char) -1  /* 0xFF */
#define STEP_APPLE_INIT_EN_COURS_STEP1   (unsigned char) -2  /* 0xFE */
#define STEP_APPLE_INIT_EN_COURS_STEP2   (unsigned char) -3  /* 0xFD */
#define STEP_APPLE_INIT_EN_COURS_STEP3   (unsigned char) -4  /* 0xFC */
#define STEP_APPLE_INIT_KO               (unsigned char) -5  /* 0xFB */
#define STEP_APPLE_AUTHENT_EN_COURS      (unsigned char) -6  /* 0xFA */ 
#define STEP_APPLE_AUTHENT_KO            (unsigned char) -7  /* 0xF9 */
#define STEP_APPLE_ATTENTE_CANAL_COMM    (unsigned char) -8  /* 0xF8 */
#define APPLE_NOT_CONNECTED              (unsigned char )-9  /* 0xF7 */
#define APPLE_NOT_POWERED                (unsigned char )-10  /* 0xF6 */
#define STEP_APPLE_REINIT_REQUIRED       (unsigned char )-11  /* 0xF5 */
#define STEP_APPLE_SLEEP_STATE           (unsigned char )-12  /* 0xF4 */



#endif /* _OEM_ISPM_H_ */


