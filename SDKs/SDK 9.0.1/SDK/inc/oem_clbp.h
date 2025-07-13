/*
 * OEM C cless interface 
 */ 
 
#ifndef __OEM_CLBP_H
#define __OEM_CLBP_H
 

/*Type de la carte*/
#define CL_TYPE_A          1
#define CL_TYPE_B          2
#define CL_TYPE_BP         4
#define CL_TYPE_STM        8
#define CL_TYPE_MF         0x10
#define CL_TYPE_AB         (CL_TYPE_A|CL_TYPE_B)

/*genre de la carte*/

/*l'apdu*/
typedef struct{
 byte* data;
 word  length;
}T_CLBP_APDU;

/*specific BP*/
#define SIZE_ATR_BP 27

/*returns ISO 14443*/
#define CLBP_OK            0
#define CLBP_KO            1
#define CLBP_NOCARD        2
#define CLBP_TOOMANYCARDS  3

/*returns oem*/
#define CLBP_SUCCESS           0
#define CLBP_NOT_IMPLEMENTED   -1

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
#define GET_ATRBP          18  
  /*20->29 : TRC*/
#define TRC_START      21
#define TRC_STOP       22
#define TRC_INFOSCARD  23
#define TRC_EXTERNAL   24
#define TRC_GETBUF     25



/*data structure of ioctl function's parameters*/
typedef struct
{
    unsigned int   timeout;
}T_CLBP_FIOCTLPARAM_DETECTCARDS;

typedef struct
{
    unsigned int  waitremove;
}T_CLBP_FIOCTLPARAM_DISCONNECT;

typedef struct
{
    unsigned char*    pucLgAtr;
    unsigned char*    pucATR;
}T_CLBP_FIOCTLPARAM_ATR;

typedef struct
{
    T_CLBP_APDU*    C_apdu;
    T_CLBP_APDU*    R_apdu;
}T_CLBP_FIOCTLPARAM_APDU;

typedef struct
{
    unsigned char  choose;
    unsigned int   data1;
    unsigned int   data2;
    unsigned int   data3;
    unsigned int   data4;
}T_CLBP_FIOCTLPARAM_XX_FORMAT;

/*FIOCTL defines functions*/
#define CLBP_FIOCTL_EXTERNAL      0x8000

#define CLBP_FIOCTL_DETECT        CLBP_FIOCTL_EXTERNAL
#define CLBP_FIOCTL_DISCONNECT    CLBP_FIOCTL_EXTERNAL+1
#define CLBP_FIOCTL_APDU          CLBP_FIOCTL_EXTERNAL+2
#define CLBP_FIOCTL_ATR           CLBP_FIOCTL_EXTERNAL+3


#define CLBP_FIOCTL_XX_FORMAT              CLBP_FIOCTL_EXTERNAL+10
#endif

