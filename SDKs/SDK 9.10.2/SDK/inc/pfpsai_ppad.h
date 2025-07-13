/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/


#ifdef __cplusplus
extern "C" {
#endif

#ifndef _PFPSAI_PPAD_H
#define _PFPSAI_PPAD_H

/*
======================================================================
					List of Defines
======================================================================
*/

#define T_FONCTION_PPAD      0x80   
#define T_CORRECTION_PPAD    0x81   
#define T_VALIDATION_PPAD    0x82   
#define T_NUMERIQUE_PPAD     0x83   

        
#define T_ANN_PPAD           0x41 /* CANCEL  */
#define T_CORR_PPAD          0x43 /* CORRECT */
#define T_VAL_PPAD           0x56 /* VALID   */

#define ETOILE               0x2A /* STAR     */
#define VIRGULE              0x2C /* COMMA    */
#define T_F_PPAD             0x46 /* FUNCTION */

#define NUMBER_PPAD          0xA0

#define T_F1_PPAD            0x21
#define T_F2_PPAD            0x22
#define T_F3_PPAD            0x23
#define T_F4_PPAD            0x24
 
#define MASK_NUM_PPAD        0x8000 
#define MASK_F_PPAD          0x4000
#define MASK_ANN_PPAD        0x2000 
#define MASK_CORR_PPAD       0x1000 
#define MASK_VAL_PPAD        0x0800 
#define MASK_VIRGULE_PPAD    0x0400
#define MASK_ETOILE_PPAD     0x0200

#define MASK_SK1_PPAD        0x0100
#define MASK_SK2_PPAD        0x0080
#define MASK_SK3_PPAD        0x0040
#define MASK_SK4_PPAD        0x0020

 
#define CLEAR_PPAD           0
#define NO_CLEAR_PPAD        1
#define ERROR_SAISIE_PPAD    9999 


#define SAISIE_NUM_PPAD      1
#define SAISIE_FCT_PPAD      2
#define SAISIE_PIN_PPAD      3

#define QB_CONV_OK_PPAD      0
#define QB_CONV_NOK_PPAD     1

#define FIN_SAISIE_PPAD      0
#define NOT_FIN_SAISIE_PPAD  1
#define QB_MASK_OK_PPAD      0
#define QB_MASK_NOK_PPAD     1
#define QB_PREMIER_PPAD      1

typedef struct {
 TAB_ENTRY_STANDARD_PPAD BufferCommandePpad ;
 TAB_EXIT_PPAD BufferReponsePpad ;
 unsigned char ColonnePpad;
 unsigned char LignePpad;
 unsigned char Carac_Recu;
 char          buf[17];
}t_pfpsaippd;

typedef struct {
		unsigned char code_touche;
		unsigned char type_touche;
		unsigned char code_appli;
		unsigned short int masque; 
} T_ELT_CORRESPONDANCE_PPAD ;

/* 
 Interface from entry function return and real key
 */
#define TAILLE_TAB_PPAD      12

#ifdef DLL_PPR_C

static const T_ELT_CORRESPONDANCE_PPAD TabTouchePpad[TAILLE_TAB_PPAD] = { 
	{T_SK10      , T_FONCTION_PPAD   , TC_FONCTION_PPAD   , MASK_F_PPAD} ,
	{T_ANN       , T_FONCTION_PPAD   , TC_ANNULATION_PPAD , MASK_ANN_PPAD} ,
	{T_CORR      , T_FONCTION_PPAD   , TC_CORRECTION_PPAD , MASK_CORR_PPAD} ,
	{T_VAL       , T_FONCTION_PPAD   , TC_VALIDATION_PPAD , MASK_VAL_PPAD} ,
	{T_POINT     , T_FONCTION_PPAD   , TC_VIRGULE_PPAD    , MASK_VIRGULE_PPAD} ,
	{VIRGULE     , T_FONCTION_PPAD   , TC_VIRGULE_PPAD    , MASK_VIRGULE_PPAD} ,
	{ETOILE      , T_FONCTION_PPAD   , TC_ETOILE_PPAD     , MASK_ETOILE_PPAD} ,
	{NUMBER_PPAD , T_NUMERIQUE_PPAD  , TC_ZERO_PPAD       , MASK_NUM_PPAD} ,
	{T_SK1       , T_FONCTION_PPAD   , TC_SK1_PPAD        , MASK_SK1_PPAD},
	{T_SK2       , T_FONCTION_PPAD   , TC_SK2_PPAD        , MASK_SK2_PPAD},
	{T_SK3       , T_FONCTION_PPAD   , TC_SK3_PPAD        , MASK_SK3_PPAD},
	{T_SK4       , T_FONCTION_PPAD   , TC_SK4_PPAD        , MASK_SK4_PPAD}
}; 

#else

static const T_ELT_CORRESPONDANCE_PPAD TabTouchePpad[TAILLE_TAB_PPAD] = { 
	{T_F_PPAD    , T_FONCTION_PPAD   , TC_FONCTION_PPAD   , MASK_F_PPAD} ,
	{T_ANN_PPAD  , T_FONCTION_PPAD   , TC_ANNULATION_PPAD , MASK_ANN_PPAD} ,
#if defined(DLL_PMPC10S) || defined(__DLL_P40)
	{T_CORR_PPAD , T_FONCTION_PPAD , TC_CORRECTION_PPAD , MASK_CORR_PPAD} , // Prise en compte CORR pour Fct_Entry
#else
	{T_CORR_PPAD , T_CORRECTION_PPAD , TC_CORRECTION_PPAD , MASK_CORR_PPAD} ,
#endif
	{T_VAL_PPAD  , T_FONCTION_PPAD   , TC_VALIDATION_PPAD , MASK_VAL_PPAD} ,
	{T_POINT     , T_FONCTION_PPAD   , TC_VIRGULE_PPAD    , MASK_VIRGULE_PPAD} ,
	{VIRGULE     , T_FONCTION_PPAD   , TC_VIRGULE_PPAD    , MASK_VIRGULE_PPAD} ,
	{ETOILE      , T_FONCTION_PPAD   , TC_ETOILE_PPAD     , MASK_ETOILE_PPAD} ,
	{NUMBER_PPAD , T_NUMERIQUE_PPAD  , TC_ZERO_PPAD       , MASK_NUM_PPAD} ,
	{T_F1_PPAD   , T_FONCTION_PPAD   , TC_SK1_PPAD        , MASK_SK1_PPAD},
	{T_F2_PPAD   , T_FONCTION_PPAD   , TC_SK2_PPAD        , MASK_SK2_PPAD},
	{T_F3_PPAD   , T_FONCTION_PPAD   , TC_SK3_PPAD        , MASK_SK3_PPAD},
	{T_F4_PPAD   , T_FONCTION_PPAD   , TC_SK4_PPAD        , MASK_SK4_PPAD}
}; 
#endif

#endif
/*! @} **/
#ifdef __cplusplus
}
#endif
