/*
 * OEM C cless interface 
 */ 
 
#ifndef __OEM_CLSTM_H
#define __OEM_CLSTM_H

/*Type de la carte*/
#define CL_TYPE_A          1
#define CL_TYPE_B          2
#define CL_TYPE_BP          4
#define CL_TYPE_STM         8
#define CL_TYPE_AB         (CL_TYPE_A|CL_TYPE_B)
 

/*returns ISO 14443*/
#define CLSTM_OK            0
#define CLSTM_KO            1
#define CLSTM_NOCARD        2
#define CLSTM_TOOMANYCARDS  3
#define CLSTM_INVALIDCARD   4

/*returns oem*/
#define CLSTM_SUCCESS           0
#define CLSTM_NOT_IMPLEMENTED   -1
#define CLSTM_NOT_SUPPORTED     -2

/*acces fonctions via format()*/
  /*00->09*/
#define FCTWAIT        2
#define SETFIELD       4
#define RESETPICC      7
#define SETCNFREG_ANY  9
#define READ_REG_ANY   10
  /*20->29 : TRC*/
#define TRC_START      21
#define TRC_STOP       22
#define TRC_INFOSCARD  23
#define TRC_EXTERNAL   24
#define TRC_GETBUF     25

//ISO #define FORCE_QUOTA          30
//ISO #define SET_NBOFTRANSMISSION 31
//ISO #define SET_FAST_REPLY       32
//ISO #define SET_MONEO_POLLING    33
//ISO 1.1 #define PROTOCOLTYPE_CHECK   34
//ISO 1.1 #define DISABLE_PUPI_CHECK   35
//MF #define MF_GETEXTENDEDINFO  37 
//MF #define MF_STOREKEY         38

//MF ISO #define TRNSP_EXCH			40 //process a transparent Cmd/Resp exchange
//ISO #define LOWLEVEL_FORMAT 	41 //ask for a driver reconfiguration
//MF  #define	MF_RESETCRYPTO1		42
//ISO #define ISO_ENABLE_FIELD_OPTIM 43
#define QUOTA_NON_PERSISTENT		44
#define 	QNP_SET_QUOTA	 	1 //set ratio TON TOFF
#define 	QNP_SET_MIN_BREAK	2 //try to set minimal duration of TOFF
#define 	QNP_SET_MAX_PERIOD	3 //try to set maximum for TON + TOFF
//ISO #define QUOTA_EXTREMUM_DEFINITION	45
//ISO #define GET_SPEC_VERSION		46


//STM card type
#define STM_SR176      1
#define STM_SRIX4K     (1<<1)
#define STM_SRIX512    (1<<2)
#define STM_SRI512     (1<<3)
#define STM_SRI4K      (1<<4)
#define STM_SRT512     (1<<5)

//! \brief Data structure of ioctl function's parameters   \n
//! Card detection in the reader area.
typedef struct
{
    unsigned char   timeout;		//!<  detection time out		
}T_CLSTM_FIOCTLPARAM_DETECT;

//! \brief Data structure of ioctl function's parameters. Read a 16-bit memory block.
/* @GSIM_T:T_CLSTM_FIOCTLPARAM_READBLOCK:DATA_SIZE(12) */
typedef struct
{
    unsigned char   addr;		//!<  address of the block
    unsigned char*  pdataL;		//!<  SR176 :byte address to store the least significant byte of the read 16-bit(or 32-bit if other STM) value.
    unsigned char*  pdataH;		//!<  SR176 :byte address to store the most significant byte of the read 16-bit value.others STM:byte address to store the next byte of the read 32-bit value.
//keep same interface for old applications using SR176
//for other STM products add two extra bytes 
    unsigned char*   pdataL2;     //!<  others STM:byte address to store the next byte of the read 32-bit value.
    unsigned char*   pdataH2;     //!<  others STM:byte address to store the most significant byte of the read 32-bit value.

}T_CLSTM_FIOCTLPARAM_READBLOCK;

//! \brief Data structure of ioctl function's parameters. Write a 16-bit memory block.
typedef struct
{
    unsigned char   addr;		//!<  address of the block
    unsigned char   dataL;		//!<  SR176 :least significant byte of the 16-bit(or 32-bit if other STM) value to write.
    unsigned char   dataH;		//!<  SR176 :most significant byte of the 16-bit value to write.others STM:next byte of the 32-bit value to write.
//keep same interface for old applications using SR176
//for other STM products add two extra bytes 
    unsigned char   dataL2;     //!<  next byte of the 32-bit value to write.
    unsigned char   dataH2;     //!<  most  significant byte of the 32-bit value to write.
}T_CLSTM_FIOCTLPARAM_WRITEBLOCK;

//! \brief Data structure of ioctl function's parameters. Protect a 16-bit memory block.
typedef struct
{
    unsigned char   lockreg;		//!<  Block protection status (See the SR176 specification for the lockreg meaning).
}T_CLSTM_FIOCTLPARAM_PROTECTBLOCK;

//! \brief Data structure of ioctl function's parameters. Get a protection.
/* @GSIM_T:T_CLSTM_FIOCTLPARAM_GETPROTECTION:DATA_SIZE(4) */
typedef struct
{
    unsigned char*  plockreg;		//!<  pointer on the block protection status (See the SR176 specification for the lockreg meaning).
}T_CLSTM_FIOCTLPARAM_GETPROTECTION;

//! \brief Data structure of ioctl function's parameters \n
//! Generical function for driver formatting (expert users only).
typedef struct
{
    unsigned char  choose;		//!<  choice of the command
    unsigned int   data1;		//!<  parameter 1 of the command
    unsigned int   data2;		//!<  parameter 2 of the command
    unsigned int   data3;		//!<  parameter 3 of the command
    unsigned int   data4;		//!<  parameter 4 of the command
}T_CLSTM_FIOCTLPARAM_XX_FORMAT;

typedef struct
{
    int              cardtype; //!<  STM card type, SR176 SRI512 ...
    unsigned char*   uid; //!<  address to store the 64-bit UID 
}T_CLSTM_FIOCTLPARAM_GETUID;

/*FIOCTL defines functions*/
#define CLSTM_FIOCTL_EXTERNAL      0x8000

#define CLSTM_FIOCTL_DETECT        CLSTM_FIOCTL_EXTERNAL
#define CLSTM_FIOCTL_DEACTIVATE    CLSTM_FIOCTL_EXTERNAL+1
#define CLSTM_FIOCTL_READBLOCK     CLSTM_FIOCTL_EXTERNAL+2
#define CLSTM_FIOCTL_WRITEBLOCK    CLSTM_FIOCTL_EXTERNAL+3
#define CLSTM_FIOCTL_PROTECTBLOCK  CLSTM_FIOCTL_EXTERNAL+4
#define CLSTM_FIOCTL_GETPROTECTION CLSTM_FIOCTL_EXTERNAL+5
#define CLSTM_FIOCTL_GETUID        CLSTM_FIOCTL_EXTERNAL+6
#define CLSTM_FIOCTL_REMOVAL       CLSTM_FIOCTL_EXTERNAL+7

#define CLSTM_FIOCTL_XX_FORMAT  CLSTM_FIOCTL_EXTERNAL+10
#endif

