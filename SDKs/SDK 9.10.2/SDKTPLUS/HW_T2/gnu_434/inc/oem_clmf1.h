/*
 * OEM C cless MF1 interface 
 */ 
 
#ifndef __OEM_CLESSMF1_H
#define __OEM_CLESSMF1_H
 
/*returns oem*/
#define CLESS_SUCCESS           0
#define CLESS_NOT_IMPLEMENTED   -1

/*MF1*/
#define KEY_A 0x60
#define KEY_B 0x61
#define MF_EEPROMKEY 0x80
#define VALUE 1
#define DATA  2

/*operations*/
#define MF_READ      0x30
#define MF_WRITE     0xA0
#define MF_INCREMENT 0xC1
#define MF_DECREMENT 0xC0
#define MF_RESTORE   0xC2
#define MF_TRANSFER  0xB0

/*error returns*/
#define MF_OK 0

#define MF_KO                      1
#define MF_UID_SIZE_ERR           10
#define MF_BIT_FRAME_ANTICOLL_ERR 11
#define MF_NOT_MF1                12
#define MF_NOT_MFUL               22
#define MF_UID_NOT_COMPLETE_ERR   13
#define MF_LOAD_KEY_ERR           0x40	
#define MF_AUTH_ERR               14
#define MF_WRITE_ERR              15
#define MF_VALUE_ERR              16
#define MF_ACCESS_ERR             17
#define MF_NO_CARD          	  18
#define MF_TIME_OUT_ERR           19 
#define MF_RESPONSE_SIZE_ERR      20
#define MF_BCC_ERR                21
#define MF_TOOMANYCARDS           23
#define MF_INVALIDCARD            24

/*ERROR TYPE : pour remontee vers appli EPI*/
#define NO_ERROR                   0
#define COLLISION_DETECTION_ERROR  1
#define PROTOCOL_ERROR             2
#define TRANSMISSION_ERROR         3
#define TIME_OUT_ERROR             4

/*Type de la carte*/
#define CL_TYPE_A          1
#define CL_TYPE_B          2
#define CL_TYPE_BP         4
#define CL_TYPE_STM        8
#define CL_TYPE_MF         0x10
#define CL_TYPE_AB         (CL_TYPE_A|CL_TYPE_B)

#define CL_ISO14443_4    0x80
#define CL_MF_CLASSIC    0x40
#define CL_MF_ULTRALIGHT 0x10
#define CL_MF_4K         0x08
#define CL_MF_MINI       0x04
#define CL_MF_PLUS_L2    0x02
#define CL_B_UNDEFINED   0x20
#define CL_ALLKINDS      0xFF
/*acces fonctions via format()*/
  /*00->09*/
#define MF_FCTWAIT        2
#define MF_SETFIELD       4
#define MF_GETUID         5 //!< Get uid of a mifare card, accept large UID, format include card type stored in 1st byte and uid size stored in 2nd byte so buffer must be 12 bytes long
#define RESETPICC          7
#define SETCNFREG_ANY      9
#define READ_REG_ANY       10

  /*20->29 : TRC*/
#define MF_TRC_START      21
#define MF_TRC_STOP       22
#define MF_TRC_INFOSCARD  23
#define MF_TRC_EXTERNAL   24
#define MF_TRC_GETBUF     25

/*etat de la carte*/
#define PICCSTATE_HLT 1 /*halt*/
#define PICCSTATE_ACT 2 /*active == entered iso/iec 14443-4 for exchange transparent data*/
#define PICCSTATE_IGN 3 /*ignored picc == command deselect failed*/
#define PICCSTATE_RST 4 /*reseted picc == PiccsReset generated by the PCD or before detection*/

//ISO #define FORCE_QUOTA          30
//ISO #define SET_NBOFTRANSMISSION 31
//ISO #define SET_FAST_REPLY       32
//ISO #define SET_MONEO_POLLING    33
// ISO 1.1 #define PROTOCOLTYPE_CHECK   34
// ISO 1.1 #define DISABLE_PUPI_CHECK   35
#define MF_GETEXTENDEDINFO  37 
#define MF_STOREKEY         38

#define TRNSP_EXCH			40 //process a transparent Cmd/Resp exchange
#define LOWLEVEL_FORMAT 	41 //ask for a driver reconfiguration
#define 	LL_FORMAT_TXRXCRC				7 // TXCRC is enabled if data2 is true, RXCRC is enabled if data3 is true
#define	MF_RESETCRYPTO1		42
//ISO #define ISO_ENABLE_FIELD_OPTIM 43
#define QUOTA_NON_PERSISTENT	44
#define 	QNP_SET_QUOTA	 	1 //set ratio TON TOFF
#define 	QNP_SET_MIN_BREAK	2 //try to set minimal duration of TOFF
#define 	QNP_SET_MAX_PERIOD	3 //try to set maximum for TON + TOFF
//ISO #define QUOTA_EXTREMUM_DEFINITION	45
//ISO #define GET_SPEC_VERSION		46

#define FULL_TRNSP_EXCH			49 //process a transparent Cmd/Resp exchange



/*data structure of ioctl function's parameters*/
//! \brief Data structure of ioctl function's parameters. \n
//! Detection of a MIFARE card.
/* @GSIM_T:T_CLMF1_FIOCTLPARAM_DETECTCARDS:DATA_CODE( 1 + sizeof(dword) )  */
typedef struct
{
    byte*  cards_number;							//!< number of cards detected.
    dword  time_out_sec;							//!< time out (in seconds)
}T_CLMF1_FIOCTLPARAM_DETECTCARDS;

//! \brief Data structure of ioctl function's parameters. \n
//! Detection of a MIFARE card.
typedef struct
{
    byte   cards_type;			  				    //!< type of cards we are looking for
    byte*  cards_number;							//!< number of card detected.
    dword  time_out_sec;							//!< time out (in seconds)
}T_CLMF1_FIOCTLPARAM_DETECTCARDS_EX;

//! \brief Data structure of ioctl function's parameters. \n
//! Activate a detected MIFARE card.
typedef struct
{
    dword  card_index;								//!< index of the card to activate.
}T_CLMF1_FIOCTLPARAM_ACTIVECARD;

//! \brief Data structure of ioctl function's parameters. \n
//! Used to test if a sector of the activated card is authentic.
/* @GSIM_T:T_CLMF1_FIOCTLPARAM_AUTHENTICATION:DATA_CODE( 6 + sizeof(byte)*2 )  */
typedef struct
{
    byte  key_type;									//!< type of the key (A or B)
    byte* uncoded_key;								//!< key to use
    byte  sector;									//!< sector to test
}T_CLMF1_FIOCTLPARAM_AUTHENTICATION;

//! \brief Data structure of ioctl function's parameters. \n
//! Read ablock.
/*  @GSIM_T:T_CLMF1_FIOCTLPARAM_READBLOCK:DATA_CODE( 16 + sizeof(byte) *3 )  */
typedef struct
{
    byte  data_type;								//!< type of the data
    byte  sector;									//!< sector number
    byte  block;									//!< block number (in the sector).
    byte* received_data;							//!< pointer on the buffer to fill with data
}T_CLMF1_FIOCTLPARAM_READBLOCK;

//! \brief Data structure of ioctl function's parameters. \n
//! Used to wwrite a block.
/* @GSIM_T:T_CLMF1_FIOCTLPARAM_WRITEBLOCK:DATA_CODE(16 + sizeof(byte) * 3 )  */
typedef struct
{
    byte  data_type;								//!< type of the data
    byte  sector;									//!< sector number
    byte  block;									//!< block number (in the sector)
    byte* data_to_write;							//!< data to write
}T_CLMF1_FIOCTLPARAM_WRITEBLOCK;

//! \brief Data structure of ioctl function&apos;s parameters. \n
//! Used to do a « Value » operation on a block.
/* @GSIM_T:T_CLMF1_FIOCTLPARAM_VALUEOPERATION:DATA_CODE( 4 + sizeof(byte) * 4 )  */
typedef struct
{
    byte  operation_type;							//!< type of operation
    byte  sector;									//!< sector number
    byte  source_block;								//!< source block 
    byte  dest_block;								//!< destination block
    byte* value;									//!< value (depends of the operation)
}T_CLMF1_FIOCTLPARAM_VALUEOPERATION;

//! \brief Data structure of ioctl function&apos;s parameters. \n
//! Generical function for driver formatting (expert users only).
typedef struct
{
    byte  choose;									//!< choice of the command
    unsigned int data1;								//!< parameter 1 of the command
    unsigned int data2;								//!< parameter 2 of the command
    unsigned int data3;								//!< parameter 3 of the command
    unsigned int data4;								//!< parameter 4 of the command
}T_CLMF1_FIOCTLPARAM_XX_FORMAT;

//! \brief Data structure used in ioctl format function&apos;s parameters. \n
typedef struct
{
    byte  cardtype; //!< type of car Mifareclassic, ultralight...
    byte  uidsize;  //!< size of uid in bytes
    byte  uid[10];  //!< card uid
}T_CLMF1_FIOCTLPARAM_FORMAT_GETUID;

/*FIOCTL defines functions*/
#define CLESS_FIOCTL_EXTERNAL      0x8000

#define CLMF1_FIOCTL_DETECTCARDS    CLESS_FIOCTL_EXTERNAL
#define CLMF1_FIOCTL_ACTIVECARD     CLESS_FIOCTL_EXTERNAL+1
#define CLMF1_FIOCTL_AUTHENTICATION CLESS_FIOCTL_EXTERNAL+2
#define CLMF1_FIOCTL_READBLOCK      CLESS_FIOCTL_EXTERNAL+3
#define CLMF1_FIOCTL_WRITEBLOCK     CLESS_FIOCTL_EXTERNAL+4
#define CLMF1_FIOCTL_VALUEOPERATION CLESS_FIOCTL_EXTERNAL+5
#define CLMF1_FIOCTL_DETECTCARDS_EX CLESS_FIOCTL_EXTERNAL+6
#define CLMF1_FIOCTL_REMOVAL        CLESS_FIOCTL_EXTERNAL+7

#define CLMF1_FIOCTL_XX_FORMAT     CLESS_FIOCTL_EXTERNAL+10
#endif

