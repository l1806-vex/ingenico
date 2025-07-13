/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef OEM_ACCELERO_H
#define OEM_ACCELERO_H

/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Structure use with ACCELERO_FIOCTL_GET_STATE */
typedef struct accelero_state_t{
  unsigned char   back_front;             /*!< Tell if the product is lying on its front or its back (ACCELERO_BF_FRONT - ...) */
  unsigned char   polarity;               /*!< Polarity of the product (POLARITY_LEFT_PORTRAIT - ...) */
  unsigned char   tap;                    /*!< TRUE if the product has detected a tap (reserved for futur use) */
  unsigned char   shake;                  /*!< TRUE if the product has been shaked */
  unsigned int    tilt_cpt;               /*!< Tilt counter (incremented at each accelerometer event) */
  unsigned int    ruf[2];                 /*!< RUF */
}accelero_state_t;


/*! @brief Structure use with ACCELERO_FIOCTL_CONFIG_POWER */
typedef struct accelero_cfg_pwr_t{
  unsigned int pmc_activity;           /*!< Disable or enable pmc activity at each accelerometer event (ACCELERO_PWR_PMC_ACT_OFF - ACCELERO_PWR_PMC_ACT_ON) */
  unsigned int wake_up;                /*!< Disable or enable wake up on accelerometer event when product in sleep (ACCELERO_PWR_WAKE_UP_OFF - ACCELERO_PWR_WAKE_UP_ON)*/
  unsigned int ruf[2];                 /*!< RUF */
}accelero_cfg_pwr_t;



/*
======================================================================
					List of Defines
======================================================================
*/

// List of all fioctl 
#define ACCELERO_FIOCTL_START             0x8000   /*!< param NULL : Start accelerometer */
#define ACCELERO_FIOCTL_STOP              0x8001   /*!< param NULL : Stop accelerometer */
#define ACCELERO_FIOCTL_GET_DRV_STATE     0x8002   /*!< param unsigned int* : Get driver state */
#define ACCELERO_FIOCTL_CONFIG_POWER      0x8003   /*!< param accelero_cfg_pwr_t* : Set accelerometer power configuration */
#define ACCELERO_FIOCTL_GET_POWER_CONFIG  0x8004   /*!< param accelero_cfg_pwr_t* : Get accelerometer power configuration */
#define ACCELERO_FIOCTL_SET_EVENT         0x8005   /*!< param unsigned int* : Set user event to report when accelerometer event  */
#define ACCELERO_FIOCTL_CLEAR_EVENT       0x8006   /*!< param NULL : Clear user event management */
#define ACCELERO_FIOCTL_GET_STATE         0x8007   /*!< param accelero_state_t* : Get accelerometer state */


// fioctl error codes
#define ACCELERO_RET_OK                0        /*!< Ok  */
#define ACCELERO_RET_FIOCTL_UNKNOWN    -1       /*!< Unknown fioctl */
#define ACCELERO_RET_BAD_PARAM         -2       /*!< Fioctl parameters are wrong */


// parameters values :

// List of return value of ACCELERO_FIOCTL_GET_DRV_STATE fioctl
#define ACCELERO_DRV_STOPED      0           /*!< value for ACCELERO_FIOCTL_GET_DRV_STATE : accelerometer is stoped */
#define ACCELERO_DRV_STARTING    1           /*!< value for ACCELERO_FIOCTL_GET_DRV_STATE : accelerometer is starting : accelero state is not correct yet, wait for first event */
#define ACCELERO_DRV_STARTED     2           /*!< value for ACCELERO_FIOCTL_GET_DRV_STATE : accelerometer is started  */



// List of value of the accelerometer's polarity in accelero_state_t struct
#define POLARITY_UNKNOWN               0     /*!< The product is in an unknown polarity */
#define POLARITY_LEFT_PORTRAIT         1     /*!< The product is standing in left vertical position (Default for portrait product) */
#define POLARITY_RIGHT_PORTRAIT        2     /*!< The product is standing in inversed vertical position */
#define POLARITY_LEFT_LANDSCAPE        3     /*!< The product is in landscape mode to the left (Default for landscape product) */
#define POLARITY_RIGHT_LANDSCAPE       4     /*!< The product is in landscape mode to the right */


// List of value of the accelerometer's back_front in accelero_state_t struct
#define ACCELERO_BF_UNKNOWN    0         /*!< Unknown condition of front or back */
#define ACCELERO_BF_FRONT     1          /*!< The product is lying on its front */
#define ACCELERO_BF_BACK      2          /*!< The product is lying on its back */


// List of value of the pmc_activity field in accelero_cfg_pwr_t struct
#define ACCELERO_PWR_PMC_ACT_OFF  0          /*!< Disable pmc activity on accelerometer event */
#define ACCELERO_PWR_PMC_ACT_ON   1          /*!< Enable pmc activity on accelerometer event (restart backlight and sleep counter)  */

// List of value of the wake_up field in accelero_cfg_pwr_t struct
#define ACCELERO_PWR_WAKE_UP_OFF  0          /*!< Disable wake up on accelerometer event when product is asleep */
#define ACCELERO_PWR_WAKE_UP_ON   1          /*!< Enable wake up on accelerometer event when product is asleep */






#endif

/*! @}  */ 



