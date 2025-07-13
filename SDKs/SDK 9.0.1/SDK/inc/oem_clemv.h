/*
 * OEM C EMV cless interface 
 */ 
 
#ifndef __OEM_CLEMV_H
#define __OEM_CLEMV_H
 

/*Type de la carte*/
#define CL_TYPE_A          1
#define CL_TYPE_B          2
#define CL_TYPE_BP         4
#define CL_TYPE_STM        8
#define CL_TYPE_MF         0x10
#define CL_TYPE_BMONEO     0x20 
#define CL_TYPE_AB         (CL_TYPE_A|CL_TYPE_B)

/*genre de la carte*/
#define CL_ISO14443_4   0x80
#define CL_MF_CLASSIC   0x40
#define CL_B_UNDEFINED  0x20
#define CL_MF_ULTRALIGHT 0x10
#define CL_ALLKINDS     0xFF
#ifndef __OEM_CLESS_H

/*l'apdu*/
#define CL_APDU_LGMAXDATA 256
//! \brief Define a APDU data buffer.
typedef struct{
 byte data[CL_APDU_LGMAXDATA];						//!< data of the APDU.
 word length;										//!< length of the data.
}T_CL_APDU;

//! \brief Define a APDU data buffer.
typedef struct{
 byte* data;										//!< data of the APDU.
 word  length;										//!< length of the data.
}T_CL_APDU_L;
#endif
#define SIZE_ATR  12

/*returns ISO 14443*/
#define CL_OK            0
#define CL_KO            1
#define CL_NOCARD        2
#define CL_TOOMANYCARDS  3
#define CL_INVALIDCARD   4
#define CL_NOT_ISO       5
#define CL_KO_UNSECURED_IUC 6

/*returns oem*/
#define CLESS_SUCCESS           0
#define CLESS_NOT_IMPLEMENTED   -1

/*ERROR TYPE : pour remontee vers appli EPI*/
#define NO_ERROR                   0
#define COLLISION_DETECTION_ERROR  1
#define PROTOCOL_ERROR             2
#define TRANSMISSION_ERROR         3
#define TIME_OUT_ERROR             4

/*acces fonctions via format()*/
  /*00->09*/
#define GET_ERROR          1
#define FCTWAIT            2
#define CUSTOMDRIVER       3
#define SETFIELD           4
#define FCTREQ             5
#define FCTHLT             6
#define RESETPICC          7
#define SETCNFREG_STR      8
#define SETCNFREG_ANY      9
#define READ_REG_ANY       10
#define GET_INFOCARD       11
#define GET_FULLINFOCARD   12
#define CANCEL_NOISE_TRT   13
#define SND_RATS_ATTRIB    14
#define LITTLE_DETECT      15 //Detect without RATS or ATTRIB (just for Testing purpose)
#define DECREASE_POLLING_F 16 //Decrease polling frequency
#define GET_UIDISO         17 
#define GET_ATR            18  
#define FRAMING            19

  /*20->29 : TRC*/
#define TRC_START      21
#define TRC_STOP       22
#define TRC_INFOSCARD  23
#define TRC_EXTERNAL   24
#define TRC_GETBUF     25
#define TRC_RESTART    26

#define FORCE_QUOTA          30
#define SET_NBOFTRANSMISSION 31
#define SET_FAST_REPLY       32
#define SET_MONEO_POLLING    33
// ISO 1.1 #define PROTOCOLTYPE_CHECK   34
// ISO 1.1 #define DISABLE_PUPI_CHECK   35
#define ABORT_APDU           36
//MF #define MF_GETEXTENDEDINFO  37 
//MF #define MF_STOREKEY         38
#define REQB_SPECIFIC_TO    39 
#define TRNSP_EXCH			40 //process a transparent Cmd/Resp exchange
#define LOWLEVEL_FORMAT 	41 //ask for a driver reconfiguration
#define 	LL_FORMAT_INIT_RX_THRESHOLD 	1 //reset Rx Threshold value
#define 	LL_FORMAT_WRITE_RC				2 //write directly a PN512 Register
#define 	LL_FORMAT_SET_CONFIG 			3 //ask for a driver reconfiguration
//#define	MF_RESETCRYPTO1		42
#define ISO_ENABLE_FIELD_OPTIM 43

/*data structure of ioctl function's parameters*/
//! \brief Data structure of ioctl function&apos;s parameters. \n
//! Contactless card detection in the reader area. \n
//! (EMVCO 2.0 driver)
typedef struct
{
    unsigned char  typeofcard;						//!< type of card A, B, ou AB.
    unsigned int   timeout;							//!< deselection time out detection 
}T_CLEMV_FIOCTLPARAM_DETECT;

/*data structure of ioctl function's parameters*/
//! \brief Data structure of ioctl function&apos;s parameters. \n
//! Contactless card detection in the reader area. \n
//! (EMVCO 2.0 driver)
typedef struct
{
    unsigned int  typeofcard;						//!< type of card A, B, ou AB.
    unsigned int   timeout;							//!< deselection time out detection 
    unsigned int card_kind;
    unsigned int card_type;
    byte card_uid[12];
    unsigned int card_uidsize;
    
}T_CLEMV_FIOCTLPARAM_MULTIDETECT;

//! \brief Data structure of ioctl function's parameters. \n
//! APDU exchange between the reader and the contactless card. \n
//! (reader driver EMVCO spec 2.0).
/* @GSIM_T:T_CLEMV_FIOCTLPARAM_APDU:DATA_CODE(C_apdu.length + R_apdu.length + sizeof(int) * 2 ) */
typedef struct
{
    T_CL_APDU_L*    C_apdu;							//!< buffer of the command
    T_CL_APDU_L*    R_apdu;							//!< buffer of the answer
}T_CLEMV_FIOCTLPARAM_APDU;

//! \brief Data structure of ioctl function&apos;s parameters. \n
//! Generical function for driver formatting (expert users only).
typedef struct
{
    unsigned char  choose;							//!< choice of the command
    unsigned int   data1;							//!< parameter 1 of the command
    unsigned int   data2;							//!< parameter 2 of the command
    unsigned int   data3;							//!< parameter 3 of the command
    unsigned int   data4;							//!< parameter 4 of the command
}T_CLEMV_FIOCTLPARAM_XX_FORMAT;

/*FIOCTL defines functions*/
#define CLEMV_FIOCTL_EXTERNAL      0x8000
/* 1.1
#define CLESS_FIOCTL_DETECTCARDS   CLESS_FIOCTL_EXTERNAL
#define CLESS_FIOCTL_ACTIVECARD    CLESS_FIOCTL_EXTERNAL+1
#define CLESS_FIOCTL_DESELECTCARD  CLESS_FIOCTL_EXTERNAL+2
#define CLESS_FIOCTL_APDU          CLESS_FIOCTL_EXTERNAL+3

#define CLESS_FIOCTL_DETECTCARDS_START  CLESS_FIOCTL_EXTERNAL+4
#define CLESS_FIOCTL_DESELECTCARD_START CLESS_FIOCTL_EXTERNAL+5
#define CLESS_FIOCTL_DETECTCARDS_STOP   CLESS_FIOCTL_EXTERNAL+6
#define CLESS_FIOCTL_APDU_L        CLESS_FIOCTL_EXTERNAL+7
*/

#define CLEMV_FIOCTL_XX_FORMAT     CLEMV_FIOCTL_EXTERNAL+10

#define CLEMV_FIOCTL_USE_STANDARD_CLESS		CLEMV_FIOCTL_EXTERNAL+11
#define CLEMV_FIOCTL_USE_EMBEDDED_CLESS		CLEMV_FIOCTL_EXTERNAL+12
#define CLEMV_FIOCTL_USE_PINPAD_CLESS		CLEMV_FIOCTL_EXTERNAL+13
#define CLEMV_FIOCTL_IS_CLESS               CLEMV_FIOCTL_EXTERNAL+14


#define CLEMV_FIOCTL_DETECT    CLEMV_FIOCTL_EXTERNAL+20
#define CLEMV_FIOCTL_REMOVAL   CLEMV_FIOCTL_EXTERNAL+21
#define CLEMV_FIOCTL_APDU      CLEMV_FIOCTL_EXTERNAL+22
#define CLEMV_FIOCTL_MULTIDETECT CLEMV_FIOCTL_EXTERNAL+23

#define CLEMV_FIOCTL_DETECTCARDS_START  CLEMV_FIOCTL_EXTERNAL+24
#define CLEMV_FIOCTL_DESELECTCARD_START CLEMV_FIOCTL_EXTERNAL+25
#define CLEMV_FIOCTL_REMOVAL_START CLEMV_FIOCTL_DESELECTCARD_START
#define CLEMV_FIOCTL_DETECTCARDS_STOP   CLEMV_FIOCTL_EXTERNAL+26




#endif

