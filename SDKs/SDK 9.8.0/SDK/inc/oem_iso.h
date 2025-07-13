/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef __OEM_ISO_H
#define __OEM_ISO_H

/*
======================================================================
					List of Defines
======================================================================
*/

#define	SWP_F2F_DECODING_LEVEL_0 0	/*!< low level basic */
#define	SWP_F2F_DECODING_LEVEL_1 1	/*!< medium level */
#define	SWP_F2F_DECODING_LEVEL_2 2	/*!< high level */
#define	SWP_F2F_DECODING_LEVEL_3 3	/*!< high level with ISO syntax controlling  */
#define	SWP_F2F_DECODING_LEVEL_4 4	/*!< very high level ISO2/3 tracks only (5bits/char) with ISO syntax controlling */
#define	SWP_F2F_DECODING_LEVEL_5 5	/*!< very high level ISO1 tracks only (7bits/char)with ISO syntax controlling */

#define SWP_FIOCTL_GET_MIN_CLOCK 			0x8000   	/*!<  param unsigned int: get clock minimum value ( noted during F2F decoding ) */
#define SWP_FIOCTL_GET_MOY_CLOCK 			0x8001   	/*!<  param unsigned int: get clock average value ( noted during F2F decoding ) */
#define SWP_FIOCTL_GET_MAX_CLOCK 			0x8002   	/*!<  param unsigned int: get clock maximum value ( noted during F2F decoding ) */
#define SWP_FIOCTL_GET_MAX_JITTER 			0x8004   	/*!<  param int ( low level basic decoding only ) */
#define SWP_FIOCTL_SET_MAX_JITTER 			0x8005   	/*!<  param int ( low level basic decoding only ) */
#define SWP_FIOCTL_GET_COEF_ACCEL 			0x8006   	/*!<  param int ( low level basic decoding only ) */
#define SWP_FIOCTL_SET_COEF_ACCEL 			0x8007   	/*!<  param int ( low level basic decoding only ) */
#define SWP_FIOCTL_GET_SAMPLE 				0x8008		/*!<  param unsigned int: get queue item indexed value ( index must be defined by caller ) */
#define SWP_FIOCTL_GET_SAMPLE_COUNT 		0x8009		/*!<  For test & terminal with BOOSTER1/2 only: param unsigned int: get queue available items count */
#define SWP_FIOCTL_SET_REFILL 				0x800a		/*!<  For test & terminal with BOOSTER1/2 only: param void 		  : refill last read file buffer, the goal is to re-run decoding algorithm with new parameters */
#define SWP_FIOCTL_SET_DECODING_LEVEL		0x800b		/*!<  For test & terminal with BOOSTER1/2 only: param unsigned int: modify F2F decoding level (uses: SWP_F2F_DECODING_LEVEL_X parameter ) */
#define SWP_FIOCTL_LNK_DUMP_ANALOGIQUE		0x8100		/*!<  For test & terminal with BOOSTER3 only: subscribe an analog buffer to receive ISO analog samples */
#define SWP_FIOCTL_UPDATE_DUMP_ANALOGIQUE	0x8101		/*!<  For test & terminal with BOOSTER3 only: to be used after reading :updates analog buffer last got samples */
#define SWP_FIOCTL_PARAM_MODIFY				0x8102		/*!<  For test & terminal with BOOSTER3 only: modify swipe parameters */
#define SWP_FIOCTL_PARAM_GET				0x8103		/*!<  For test & terminal with BOOSTER3 only: read swipe parameters  */
#define SWP_FIOCTL_PIC_GET					0x8104		/*!<  For test & terminal with BOOSTER3 only: get PICs informations according to last reading  */


/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief exchange data structure: to be used with fioctl(SWP_FIOCTL_LNK_DUMP_ANALOGIQUE | SWP_FIOCTL_UPDATE_DUMP_ANALOGIQUE,...) */
typedef struct 
 {
  unsigned char*b; 	/*!< address of analog turnaround buffer to subscribe (default=NULL : analog dump inhibited) */
  int size;			/*!< size of this analog buffer */
  int i; 			/*!< next sample to write index, turnaround buffer can be reorganized using this value */
} BANA;
 

/*! @brief exchange data structure: to be used with fioctl(SWP_FIOCTL_PARAM_MODIFY | SWP_FIOCTL_PARAM_GET,...) */
#define MAX_CHANNEL_COUNT 					3			/*!< ISO1,2,3 = 3 channels count */
typedef struct
 { 
  unsigned int freq;						/*!< sampling frequency (unit=Hz) */
  unsigned char gain;						/*!< amplification requiered, domain:{0=12,1=15,2=16,3=18} */
  unsigned char i_noise[MAX_CHANNEL_COUNT];	/*!< read only: noise detected level on channel, index value:{0=ISO1,1=ISO2,2=ISO3}*/
  unsigned char ch[MAX_CHANNEL_COUNT];		/*!< 3 booleans to activate channels ( TRUE if active ), index value:{0=ISO1,1=ISO2,2=ISO3} */
  unsigned char dump_bana_iuc_on;			/*!< if TRUE, then activates analog dump process allowing BANA downloading (!this increases dramatically traffic on inter-cpu link) */
 } t_parametre;

typedef struct
 { 
  t_parametre  p;							/*!< read/write parameters */
  unsigned char is_two_side_pics;			/*!< read only:if TRUE, then driver manages up and low signal pics allowing reading of more than 15% bit to bit variation cards */
  unsigned char switches_state;				/*!< read only:gives back switches state (hybrid readers only) */
  unsigned char ruf[2];                     /*!< read only:reserved for future */
 } t_parametre_ro;


/*! @brief exchange data structure: to be used with fioctl(SWP_FIOCTL_PIC_GET,...)  */
typedef struct
 { 
  int     			track_number;	/*!< track to copy ,domain:{0=ISO1,1=ISO2,2=ISO3} */
  unsigned int 		b_count;		/*!< valid PICs count, set by fioctl() */
  unsigned int		b_max;			/*!< buffer recipient size (unit =  unsigned short ), fioctl() copy border */
  unsigned short*	b;				/*!< buffer recipient address, fioctl() will copy recorded PICs to this buffer */
 } t_dpics; 


#endif
/*! @}  */ 
