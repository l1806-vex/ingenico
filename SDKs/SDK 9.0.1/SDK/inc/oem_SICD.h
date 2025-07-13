/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef OEM_SICD_H
#define OEM_SICD_H

/*
======================================================================
					List of Defines
======================================================================
*/

#define SICD_FIOCTL_GET_CNX_STATE            0x8000        /*!< Get device connection state */
#define SICD_FIOCTL_TRANSACTION              0x8001        /*!< Get device connection state */
#define SICD_FIOCTL_CANCEL                   0x8002        /*!< Cancel request */
#define SICD_FIOCTL_GET_EVENT                0x8003        /*!< Get extended event */
#define SICD_FIOCTL_RESET                    0x8004        /*!< Device reset request */
#define SICD_FIOCTL_GET_STATUS               0x8005        /*!< Get device status */
#define SICD_FIOCTL_WAIT_INTERRUPT           0x8006        /*!< Wait for an interrupt block */
#define SICD_FIOCTL_SWITCH_USB_ON            0x8007        /*!< Switch on USB power */
#define SICD_FIOCTL_SWITCH_USB_OFF           0x8008        /*!< Switch off USB power */

//SICD_FIOCTL_GET_STATUS
#define SICD_STATUS_NOT_CNX            0		/*!< None device present */
#define SICD_STATUS_CNX                1		/*!< Device is connected */

/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Interface structure between the libPTP library and the SICD driver */
typedef struct {
	enum {
		PTP_DP_NODATA,						/*!< No data to be transferred */
		PTP_DP_SENDDATA,					/*!< Data to send */
		PTP_DP_GETDATA						/*!< Data to receive */
	}		data_phase;
	int		status;							/*!< Status of the request */
	int		transfer_pending;				/*!< Transfer not complete, data follow */
	void	*command;						/*!< PTP command as PTPUSBBulkContainer address */
	unsigned int command_length;			/*!< Command structure length */
	void	*response;						/*!< PTP response as PTPUSBBulkContainer address */
	unsigned int response_length;			/*!< Response structure length */
	void	*data;							/*!< Data address */
	unsigned long data_length;				/*!< Data length */
} SICD_PTP_Params;


/*! @brief SICD transfert abort request */
typedef union {
  struct {
    unsigned short	Cancellation_Code;		/*!< Cancellation code */
    unsigned long	TransactionID;			/*!< Transaction to be cancelled */
  } str;
  unsigned char raw[6];						/*!< For raw acces to structure */
}SICD_CANCEL_REQ;


/*! @brief SICD event definition */
typedef union {
  struct {
    unsigned short	Event_Code;				/*!< Event code */
    unsigned long	TransactionID;			/*!< Transaction sending event */
    unsigned short	Number_of_Parameters;	/*!< Number of parameters */
    } str;
  unsigned char	raw[64];					/*!< For raw acces to structure */
}SICD_EVENT;


/*! @brief SICD status request */
typedef union {
  struct {
    unsigned short	wLength;				/*!< Length of status */
    unsigned short	Code;					/*!< Status code */
    } str;
  unsigned char	raw[64];					/*!< For raw acces to structure */
}SICD_STATUS;

#endif

/*! @}  */ 


