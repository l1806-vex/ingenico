/*! @addtogroup KSFAM_OS
	* @{
 */ 
                                                                         
#ifndef _UIRAM_H
#define _UIRAM_H

/*
======================================================================
					List of Defines
======================================================================
*/

#define TRAP_RESET_DATA_LEN 256       /*!< MAX value */
#define TRAP_RESET_EX_LEN   5         /*!< MAX value */
#define EXCEPTION_INFO_LEN  22				

/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief This structure contains the processor status during the last exception.  */
typedef struct spy_data_t { 
  unsigned int  hard_reset_nbr ;		/*!< Warning : It is used in assembly language #00 */
  unsigned int  soft_reset_nbr ;		/*!< Warning : It is used in assembly language #04 */
  unsigned int  exceptions_nbr ;		/*!< Warning : It is used in assembly language #08 */
  unsigned int  exception_type ;		/*!< Warning : It is used in assembly language #0C */
  unsigned int  exception_r0   ;		/*!< Warning : It is used in assembly language #10 */
  unsigned int  exception_r1   ;		/*!< Warning : It is used in assembly language #14 */
  unsigned int  exception_r2   ;		/*!< Warning : It is used in assembly language #18 */
  unsigned int  exception_r3   ;		/*!< Warning : It is used in assembly language #1C */
  unsigned int  exception_r4   ;		/*!< Warning : It is used in assembly language #20 */
  unsigned int  exception_r5   ;		/*!< Warning : It is used in assembly language #24 */
  unsigned int  exception_r6   ;		/*!< Warning : It is used in assembly language #28 */
  unsigned int  exception_r7   ;		/*!< Warning : It is used in assembly language #2C */
  unsigned int  exception_r14  ;		/*!< Warning : It is used in assembly language #30 */
  unsigned int  exception_info			/*!< Warning : It is used in assembly language #34 */
               [EXCEPTION_INFO_LEN];
  unsigned char trap_reset_ptr ;												/*!< Used by C program */
  unsigned char trap_reset_data[TRAP_RESET_DATA_LEN];		/*!< Used by C program */
} spy_data_t ;

/*! @brief This structure is not used in the thunder, it was defined for micro-security. */
typedef struct call_back_t {
  unsigned int call_back1_rdy;					/*!< separator */ 
  unsigned int call_back1;							/*!< INT_Statup */
  unsigned int call_back2_rdy;					/*!< separator */
  unsigned int call_back2;							/*!< INT_Power_Ready */
  unsigned int call_back3_rdy;					/*!< separator */
  unsigned int call_back3;							/*!< INT_Branch_To_INC_Initialize */ 
  unsigned int call_back4_rdy;					/*!< separator */
  unsigned int call_back4;							/*!< TCT_Schedule */
  unsigned int call_back5_rdy;					/*!< separator */
  unsigned int call_back5;							/*!< INT_Test_Abort  */
  unsigned int call_back6_rdy;					/*!< separator */
  unsigned int call_back6;							/*!< INT_Soft_Reset  */
  unsigned int call_back7_rdy;					/*!< separator */
  unsigned int call_back7;							/*!< INT_ */
} call_back_t ; 


#define UI_SPY_INC_RESET_NBR       spy_data.reset_nbr++		

                                                                              
#endif /*_SPY_H*/ 

/*! @}  */ 


