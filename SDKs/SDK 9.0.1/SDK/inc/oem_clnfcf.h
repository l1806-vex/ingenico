/*
 * OEM C cless interface 
 */ 
 
#ifndef __OEM_CLNFCF_H
#define __OEM_CLNFCF_H
 
/*Type de la carte*/
#define CL_TYPE_A          1
#define CL_TYPE_B          2
#define CL_TYPE_BP         4
#define CL_TYPE_STM        8
#define CL_TYPE_MF         0x10
#define CL_TYPE_BMONEO     0x20
#define CL_TYPE_ASK        0x40
#define CL_TYPE_NFCF       0x80
 
#define CL_TYPE_AB         (CL_TYPE_A|CL_TYPE_B)


/*genre de la carte*/

/*l'apdu*/
typedef struct{
 byte* data;
 word  length;
}T_CLNFCF_APDU;

/*specific NFCF*/
#define SIZE_SENSF_RES_MAX 20 //2 bytes RD not mandatory
#define SIZE_NFCID2 8
#define SIZE_ATR_RES_MIN  17
#define SIZE_ATR_RES_MAX  256

/*returns ISO 18092*/
#define CLNFCF_OK            0
#define CLNFCF_KO            1
#define CLNFCF_NOCARD        2
#define CLNFCF_TOOMANYCARDS  3
#define CLNFCF_ALLOCDATAFAILED  4


/*returns oem*/
#define CLNFCF_SUCCESS           0
#define CLNFCF_NOT_IMPLEMENTED   -1

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
#define SETCNFREG_ANY      9
#define READ_REG_ANY       10
#define GET_UID            17 
#define GET_ATRBP          18  
  /*20->29 : TRC*/
#define TRC_START      21
#define TRC_STOP       22
#define TRC_INFOSCARD  23
#define TRC_EXTERNAL   24
#define TRC_GETBUF     25


#define SET_TO_MIN_NEXTAPDU  34

/*detection configuration = mask*/
#define NFC_DETECTCNF_DEFAULT  0
#define NFC_DETECTCNF_212      0x01
#define NFC_DETECTCNF_424      0x02

/*data structure of ioctl function's parameters*/
typedef struct
{
    unsigned int   timeout;
    unsigned int   config;
}T_CLNFCF_FIOCTLPARAM_DETECTCARDS;

typedef struct
{
  byte* generalbytes;             //in&out optional : NULL if not used
  unsigned int  *gblength;        //in&out optional : NULL if not used
}T_CLNFCF_FIOCTLPARAM_ACTIVATE;

typedef struct
{
    unsigned int  waitremove;
}T_CLNFCF_FIOCTLPARAM_RELEASE;

typedef struct
{
    T_CLNFCF_APDU*    C_apdu;
    T_CLNFCF_APDU*    R_apdu;
    unsigned int      timeoutms; //application timeout (ms) , 0 if not needed
}T_CLNFCF_FIOCTLPARAM_APDU;

typedef struct
{
    unsigned char  choose;
    unsigned int   data1;
    unsigned int   data2;
    unsigned int   data3;
    unsigned int   data4;
}T_CLNFCF_FIOCTLPARAM_XX_FORMAT;

/*FIOCTL defines functions*/
#define CLNFCF_FIOCTL_EXTERNAL      0x8000

#define CLNFCF_FIOCTL_DETECT        CLNFCF_FIOCTL_EXTERNAL
#define CLNFCF_FIOCTL_ACTIVE        CLNFCF_FIOCTL_EXTERNAL+1
#define CLNFCF_FIOCTL_APDU          CLNFCF_FIOCTL_EXTERNAL+2
#define CLNFCF_FIOCTL_DESELECT      CLNFCF_FIOCTL_EXTERNAL+3
#define CLNFCF_FIOCTL_RELEASE       CLNFCF_FIOCTL_EXTERNAL+4


#define CLNFCF_FIOCTL_XX_FORMAT              CLNFCF_FIOCTL_EXTERNAL+10
#endif

