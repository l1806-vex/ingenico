/*
 * OEM C CTS cless interface 
 */ 
 
#ifndef __OEM_CLCTS_H
#define __OEM_CLCTS_H
 

/*Type de la carte*/
#define CL_TYPE_A          1
#define CL_TYPE_B          2
#define CL_TYPE_BP         4
#define CL_TYPE_STM        8
#define CL_TYPE_MF         0x10
#define CL_TYPE_BMONEO     0x20 
#define CL_TYPE_CTS        0x0100 
#define CL_TYPE_AB         (CL_TYPE_A|CL_TYPE_B)

/*genre de la carte*/
#define CL_ALLKINDS     0xFF
#define CL_CTS_256      0x1
#define CL_CTS_512      0x2
#define CL_CTS_NO_CARD  0x0

/*returns */
#define CLCTS_OK            0
#define CLCTS_KO            1
#define CLCTS_NOCARD        2
#define CLCTS_TOOMANYCARDS  3
#define CLCTS_INVALIDCARD   4

/*returns oem*/
#define CLCTS_SUCCESS           0
#define CLCTS_NOT_IMPLEMENTED   -1

/*ERROR TYPE : pour remontee vers appli EPI*/
#define NO_ERROR                   0
#define COLLISION_DETECTION_ERROR  1
#define PROTOCOL_ERROR             2
#define TRANSMISSION_ERROR         3
#define TIME_OUT_ERROR             4


/* deselection flags */
#define CL_CTS_DESELECT_DEFAULT			0  //< default behaviour is no REMOVAL mechanism and lowpower
#define CL_CTS_DESELECT_REMOVAL			1
#define CL_CTS_DESELECT_NO_LOWPOWER		2

/* write flags */
#define CL_CTS_W_DEFAULT			0  //< default behaviour is no Write without ERASE and data integrity check
#define CL_CTS_W_ERASE				1
#define CL_CTS_W_NOCHECK			2

/*acces fonctions via format()*/
  /*00->09*/
// ISO #define GET_ERROR          1
#define FCTWAIT            2
// ISO #define CUSTOMDRIVER       3
#define SETFIELD           4
// ISO #define FCTREQ             5
// ISO #define FCTHLT             6
#define RESETPICC          7
#define SETCNFREG_STR      8
#define SETCNFREG_ANY      9
#define READ_REG_ANY       10
// ISO #define GET_INFOCARD       11
// ISO #define GET_FULLINFOCARD   12
#define CANCEL_NOISE_TRT   13
// ISO #define SND_RATS_ATTRIB    14
// ISO #define LITTLE_DETECT      15 //Detect without RATS or ATTRIB (just for Testing purpose)
// ISO #define DECREASE_POLLING_F 16 //Decrease polling frequency
// ISO #define GET_UIDISO         17 
// ISO #define GET_ATRBP          18  
// ISO #define FRAMING            19

  /*20->29 : TRC*/
#define CTS_TRC_START      21
#define CTS_TRC_STOP       22
// #define TRC_INFOSCARD  23
#define CTS_TRC_EXTERNAL   24
#define CTS_TRC_GETBUF     25

#define FORCE_QUOTA          30
// ISO #define SET_NBOFTRANSMISSION 31
// ISO #define SET_FAST_REPLY       32
// ISO #define SET_MONEO_POLLING    33
// ISO 1.1 #define PROTOCOLTYPE_CHECK   34
// ISO 1.1 #define DISABLE_PUPI_CHECK   35
#define ABORT_APDU           36
//MF #define MF_GETEXTENDEDINFO  37 
//MF #define MF_STOREKEY         38
//ISO #define REQB_SPECIFIC_TO    39 //on IRC531 ISO
#define TRNSP_EXCH			40 //process a transparent Cmd/Resp exchange
//ISO #define SET_CONFIG 			41 //ask for a driver reconfiguration

/*data structure of ioctl function's parameters*/
//! \brief Data structure of ioctl function&apos;s parameters. \n
//! Contactless card detection in the reader area. \n
typedef struct T_CLCTS_FIOCTLPARAM_DETECT_s
{
    int * cardtype;						//!< type of card CTS 256, 512.
    int   timeout;						//!< deselection time out detection 
}T_CLCTS_FIOCTLPARAM_DETECT;

//! \brief Data structure of ioctl function&apos;s parameters. \n
//! Contactless card detection in the reader area. \n
typedef struct T_CLCTS_FIOCTLPARAM_DESELECT_s
{
    int  flag;						//!< change deselect behaviour.
}T_CLCTS_FIOCTLPARAM_DESELECT;

//! \brief Data structure of ioctl function&apos;s parameters. \n
//! Contactless card detection in the reader area. \n
typedef struct T_CLCTS_FIOCTLPARAM_READ_s
{
    int    addr;					//!< block to read.
    short* data;					//!< address used to store data ( data size is 2 bytes for read and 8 bytes for Multiread.
}T_CLCTS_FIOCTLPARAM_READ;

//! \brief Data structure of ioctl function&apos;s parameters. \n
//! Contactless card detection in the reader area. \n
typedef struct T_CLCTS_FIOCTLPARAM_WRITE_s
{
    int    addr;					//!< block to write.
    short  data;					//!< data to write.
    int  flag;						//!< change Write behaviour.
}T_CLCTS_FIOCTLPARAM_WRITE;

//! \brief Data structure of ioctl function&apos;s parameters. \n
//! Generical function for driver formatting (expert users only).
typedef struct T_CLCTS_FIOCTLPARAM_XX_FORMAT_s
{
    unsigned char  choose;							//!< choice of the command
    unsigned int   data1;							//!< parameter 1 of the command
    unsigned int   data2;							//!< parameter 2 of the command
    unsigned int   data3;							//!< parameter 3 of the command
    unsigned int   data4;							//!< parameter 4 of the command
}T_CLCTS_FIOCTLPARAM_XX_FORMAT;

/*FIOCTL defines functions*/
#define CLCTS_FIOCTL_EXTERNAL      0x8000
#define CLCTS_FIOCTL_DETECT       CLCTS_FIOCTL_EXTERNAL 
#define CLCTS_FIOCTL_HALT          CLCTS_FIOCTL_EXTERNAL+1
#define CLCTS_FIOCTL_DESELECT      CLCTS_FIOCTL_EXTERNAL+2
#define CLCTS_FIOCTL_WRITE         CLCTS_FIOCTL_EXTERNAL+3
#define CLCTS_FIOCTL_READ          CLCTS_FIOCTL_EXTERNAL+4
#define CLCTS_FIOCTL_MULTIREAD     CLCTS_FIOCTL_EXTERNAL+5

#define CLCTS_FIOCTL_XX_FORMAT     CLCTS_FIOCTL_EXTERNAL+10

#endif

