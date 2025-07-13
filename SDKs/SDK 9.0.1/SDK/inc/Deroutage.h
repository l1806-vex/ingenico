/*! @addtogroup KSFAM_OK
	* @{
 */

#ifndef DEROUTAGE_H
#define DEROUTAGE_H


/*
======================================================================
			Data Structures Definition
======================================================================
*/
typedef  struct
{
	unsigned char FlagOn; 				/*PMD is active*/
	unsigned char FirstAff;				/*First screen */
	unsigned char BothDisp;				/*POS display is not blocked */
	unsigned char FlagModeUSB;		/*USB connected */
	unsigned char BothPrint;			/*POS printer is not blocked */
	unsigned char FlagActivite;		/*to manage the time out*/
	unsigned char RgCaptureFlux;	/*dump com */
	unsigned char ucOldVisu;			/*save the last screen updated*/
	char cDescVisu[5];						/*Display to send*/
	unsigned char GestTO;					/*Time out is active*/
}DEROUTE_T;



typedef struct 
{
	unsigned int version;		        //structure version
	unsigned int type_produit; 		  //TERM_ICT220.... (comes from SYS_FIOCTL_GET_TERMINAL_TYPE)
	unsigned int type_pinpad; 		  //Pinpad kind
	unsigned int type_cible; 		    //Cible kind
	
	unsigned int display_type;			//Display kind (comes from SYS_FIOCTL_GET_DISPLAY_TYPE)
	unsigned int display_width;		  //Horizontal pixel
	unsigned int display_height;	  //Vertical pixel
	
	unsigned char portable;		//TRUE - FALSE
	unsigned char printer;		//TRUE - FALSE

	unsigned char cam0;				//TRUE - FALSE
	unsigned char cam1;				//TRUE - FALSE
	unsigned char cam2;				//TRUE - FALSE
	unsigned char sam1;				//TRUE - FALSE
	unsigned char sam2;				//TRUE - FALSE
	unsigned char sam3;				//TRUE - FALSE
	unsigned char sam4;				//TRUE - FALSE

	unsigned char cless;			//TRUE - FALSE
	unsigned char swipe1;			//TRUE - FALSE
	unsigned char swipe2;			//TRUE - FALSE
	unsigned char swipe3;			//TRUE - FALSE

	unsigned char keyboard;		//TRUE - FALSE
	unsigned char buzzer;			//TRUE - FALSE
	unsigned char backlight;	//TRUE - FALSE
	unsigned char tscreen;		//TRUE - FALSE
	unsigned char audio;			//TRUE - FALSE
	unsigned char accelero;		//TRUE - FALSE
	unsigned char light_sensor;//TRUE - FALSE
	unsigned char video;			//TRUE - FALSE
	unsigned char mmc;				//TRUE - FALSE
	unsigned char morpho;			//TRUE - FALSE
	
	unsigned char com0;				//TRUE - FALSE
	unsigned char com1;				//TRUE - FALSE
	unsigned char com2;				//TRUE - FALSE
	unsigned char com3;				//TRUE - FALSE
	unsigned char usb_host;		//TRUE - FALSE
	unsigned char usb_slave;	//TRUE - FALSE
	unsigned char ethernet;		//TRUE - FALSE
	unsigned char modem;			//TRUE - FALSE
	unsigned char ruf;				//ruf
	unsigned int radio_mask;	//Radio mask (comes from SYS_FIOCTL_GET_RADIO_MASK)

}DEROUTE_INFO_TERM_T;


/*
======================================================================
					List of Defines
======================================================================
*/

#define  FORMAT1		1 					/*!< image direct*/
#define  FORMAT2		2 					/*!< image difference*/
#define  FORMAT3		3 					/*!< image deleted */
#define  FORMAT4		4 					/*!< FORMAT 1 for tst*/
#define  FORMAT5		5 					/*!< BMP color */
#define  FORMAT6		6 					/*!< BMP color difference*/
#define  FORMAT7		7 					/*!< BMP color */

#define MAX_PAGE_64			64/8
#define MAX_PAGE_128		128/8

//system command
#define START_PMD 				0			/*to start pmd*/
#define FIN_PMD 					1			/*to end pmd*/
#define KEY_PMD						2			/*to send a key */
#define ISO_PMD						3			/*to send iso data*/
#define VISU_PMD					4			/*to send screen data  */
#define PRINTER_PMD				5			/*to send printer data */
#define EST_DEROUTE				6			/*pmd is on */
#define ACTIVITE					7			/*to manage the time out */
#define TXT_FIN_PMD				8			/*to send message at the end*/
#define EVT_PRINTER 			9			/*to simulate printer event */
#define STATE_CAM					10		/*indicates cam state */
#define START_PMD_USB			11		/*to start usb pmd */
#define DEROUTE_FLUX_E		12		/*dump com input */
#define DEROUTE_FLUX_R		13		/*dump com output */
#define DEROUTE_VIA_TMS		14		/*pmd is on  */
#define VISU_PMD_COLOR		15		/*to send screen data color */



//mmi command
#define T_CMD_IHM_LANCEE				4		/*connected */
#define T_CMD_MSG_FIN_PRINTER		5		/*end message */
#define T_CMD_CAM								6		/*cam */
#define T_CMD_BOTH_DISP					7		/*actives pos display */
#define T_CMD_BOTH_PRINT				8		/*actives pos printer*/
#define T_CMD_DISP_PMD					9		/*display data  */
#define T_CMD_IHM_POOL					10	/*ask pos connected to TMS */
#define T_CMD_COM_DEROUTE				11	/*dump com */
#define T_CMD_AFF_PERIPH				12	/*actives display periph (pin pad)*/
#define T_CMD_KEY_PERIPH				13	/* periph key*/
#define T_CMD_GESTION_TO				14	/*time out*/
#define T_CMD_GET_INFO					15	/*get info*/
#define T_CMD_TSCREEN						16  /*tscreen command*/
#define T_CMD_RESET_YELLOW_DOT			17  /*Yellow dot reset command*/
#define T_CMD_ECHO						18  /*Echo command*/


//Tscreen command
#define PMD_TSCREEN_DISP_COORD				0		//Set tscreen event with display coord


#define	LG_TYPE			1					/*frame header */
#define	LG_LG				2					/*frame header*/
#define	LG_CMD			4					/*frame header*/


#define	MSG_CON				0x10		/*type message */
#define	MSG_CMD_DATA	0x12		/*type message */

#define REQ_CONNECTION_OFF		1		/*tms cmd */
#define REQ_STATE_ALL_LINE		2		/*tms cmd */
#define REQ_STATE_ONE_LINE		3		/*tms cmd*/
#define REQ_PARAM_CONNECTION	4		/*tms cmd*/
#define SEND_KEY							5		/*tms cmd */
#define SEND_SWIPE						6		/*tms cmd */
#define REC_DISP							7		/*tms cmd */
#define REC_PRINTER						8		/*tms cmd */
#define REQ_END_OF_COM				9		/*tms cmd*/
#define ACK_END_OF_COM				10	/*tms cmd*/
#define DATA_DEROUTE_COM			11	/*tms cmd */


#define MASK_DEROUTE_COM0			0x1		/*dump com */
#define MASK_DEROUTE_COM1			0x2		/*!dump com*/
#define MASK_DEROUTE_COM2			0x3		/*dump com*/
#define MASK_DEROUTE_MODEM		0x4		/*!dump com */
#define EMISSION_FLUX					1			/*dump com */
#define RECEPTION_FLUX				2			/*dump com */




/*display frame */
typedef struct
{
	unsigned char TypDisp;			/*display id */
	unsigned char *BufIm;				/*data */
}DEROUTE_DATA_T;

#ifndef DEROUTE_SOURCE

/*! @brief Deroute is used to test if  the PMD  is running . 
 *
 * @param iNumFct : DEROUTE_VIA_TMS 
 * @param pvP1: NULL
 * @param pvP2: NULL
 * @param pvP3: NULL 
 * @return None
 *   True  :  PMD is ON
 *   False : PMD is OFF
 */ 
extern void *Deroute(int iNumFct,void *pvP1,void *pvP2,void *pvP3);

#endif

#endif

/*! @}  */
