/*! @addtogroup KSFAM_PPS_MANAGER
	* @{
**/

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _PINPAD_DEF_H
#define _PINPAD_DEF_H

/*
======================================================================
					List of Defines
======================================================================
*/
#define SYSTEM_STACK_SIZE         800 
#define STACK_TASK_SIZE           (2048/4)
#define MAX_MESSAGE_LEN           64
#define MAX_ANSWER_LEN            64
#define MAX_REPET_NUMBER          4
#define MAX_TIMEOUT               100 
#define RESET_TIMEOUT             50   // * 10 ms 
#define BREAK_TIMEOUT             400  // ms
#define MAX_TIMEOUT_SYNCHRO       600  

#define PIN_BLOC_SIZE             8
#define TDES_KEY_SIZE             16
#define MAX_PIN_LEN               12

//Display sizes
#define MAX_DISPLAY_WIDTH         16
#define MAX_DISPLAY_HEIGHT        2


// Char definitions
#define STX_CAR                   0x02
#define ETX_CAR                   0x03
#define ENQ_CAR                   0x05
#define ACK_CAR                   0x06
#define LF_CAR                    0x0A 
#define CR_CAR                    0x0D
#define DC1_CAR                   0x11  
#define DC2_CAR                   0x12  
#define DC3_CAR                   0x13  
#define DC4_CAR                   0x14  
#define NACK_CAR                  0x15
#define ESC_CAR                   0x1B
#define HOME_CAR                  0x1E
#define SPACE_CAR                 0x20
 

#define FUNCTION_LEN              2   
#define DOMAIN_LEN                2
#define ENVELOPE_LEN              3

#define STATUS_ANSWER_LEN         2
#define IDENT_ANSWER_LEN          16
#define PRODUCT_TYPE_ANSWER_LEN   16
#define REFERENCE_ANSWER_LEN      IDENT_ANSWER_LEN + PRODUCT_TYPE_ANSWER_LEN
#define NUMERICAL_ANSWER_LEN      4
#define TDES_PIN_ANSWER_LEN       16 
#define KEY_TEST_ANSWER_LEN       22
#define SOFT_NUMBER_ANSWER_LEN    16
#define SOFT_VERSION_ANSWER_lEN   12
#define SOFT_REF_ANSWER_LEN       SOFT_NUMBER_ANSWER_LEN + SOFT_VERSION_ANSWER_lEN               
#define CANCEL_ANSWER_LEN         2
#define CLEAR_KEYS_ANSWER_LEN     2

#define SOFT_REF_DLL_LEN          8
#define SOFT_VERSION_DLL_LEN      6
#define PP30_ID_NUMBER_DLL_LEN    8
#define PP30_PRODUCT_TYPE_DLL_LEN 8
#define KEY_TEST_DLL_LEN          11

#define  PHASE_0_FIXE             1
#define  PHASE_1_DERIVED          2 

#define  MIN_NUM_DIGIT            1
#define  MAX_NUM_DIGIT            2

#define  TDES_NUMERICAL_ANSWER_LEN   16

/*
 Application error codes
 */
#define RET_PP_OK                    (0)
#define RET_PP_KO                    (1)
#define RET_PP_BUSY                  (99) 
#define RET_PP_SYNTAX                (11) 
#define RET_PP_EEPROM                (12)
#define RET_PP_CANCEL                (13) 
#define RET_PP_INVALID_LEN           (14) 
#define RET_PP_NO_MASTER_KEY         (15)  
#define RET_PP_DELAYED               (18)
#define RET_PP_TIMEOUT_PIN           (19)

#define RET_PP_NEW_PP_DETECTED       (20) 

#define RET_PP_ALREADY_OPEN          (-16)  // equivalent 0xFFFFFFEF
#define RET_PP_BAD_WRITE             (-17)  
#define RET_PP_BAD_ACKNOWLEDGE       (-18)
#define RET_PP_BAD_ANSWER_LEN        (-19)
#define RET_PP_BAD_LRC               (-20)
#define RET_PP_BAD_ANSWER            (-21)
#define RET_PP_COMMAND_KO            (-22)
#define RET_PP_TIMEOUT               (-23)
#define RET_PP_DISCONNECT            (-24) 
#define RET_PP_BAD_SOFT_VERSION      (-25)
#define RET_PP_BAD_REFERENCE         (-26)
#define RET_PP_BAD_DOMAIN            (-27)
#define RET_PP_BAD_KEY               (-28)   

#define RET_PP_NOT_COMPATIBLE        (-100)


/*! @brief Define the configuration of the COM port.*/
typedef struct {
   int           Speed;								/*!< baudrate.*/
   unsigned char Len;									/*!< length of the data (7-8 bits)*/
   unsigned char Stop;								/*!< number of stop bit (1-2 bits)*/
   unsigned char Parity;							/*!< parity or not*/
   unsigned char Type;								/*!< type of the parity*/
   unsigned char RtsCts;							/*!< activate flow control or not*/
   unsigned char Rfu;									/*!< reserved for future use.*/
   unsigned char Name[10];						/*!< name of the COM port (COM0, 1,2 ...)*/
} T_FORMAT_COM;

/*! @brief Define a pointer on a function to fork.*/
typedef unsigned short (*T_PFONC_FORK) (void);


//Definition des Exits 
#define EXIT_DEFAULT_TASK_PP30    0x1201


#endif
/*! @} **/
#ifdef __cplusplus
}
#endif
