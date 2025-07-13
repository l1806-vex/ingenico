/*! @addtogroup KSFAM_CB2A
	* @{
**/
#ifndef FT_CB2A_H
#define FT_CB2A_H

/*
======================================================================
					List of Defines
======================================================================
*/

/*=================== MPE V5 ====================*/
/********************************************
  definition pour l'interface entre objet
*********************************************/
#define IX_ABOUTIE     0x00
#define IX_NON_ABOUTIE 0x57
#define IX_DEBIT       0x00
#define IX_CREDIT      0x20
#define IX_ANNULATION  0x56
#define IX_DIFF_RECOUVREMENT 0x33 /* MPEV5.2 */
/*-- pour le marquage d'une transaction 
** ATTENTION seul le quartet de poids fort est disponible 
** on utilise celui du no_porteur[0] */
#define MK_EFFACEMENT     0x08 	 	/*!< 00001000 */
#define MK_ANNULATION     0x04  	/*!< 00000100 */
#define MK_REFUSEE        0x02  	/*!< 00000010 */
#define MK_INTERDIT       0x01  	/*!< 00000001 */
/*-- pour le type de carte */
#define  IX_PISTE         0x01
#define  IX_PUCE          0x02
#define  IX_PISTE_PUCE    0x03

#endif

/*! @} **/
