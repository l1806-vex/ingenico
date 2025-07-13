/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/


#ifndef _EMV_SQ_H
#define _EMV_SQ_H
/*
======================================================================
					List of Defines
======================================================================
*/

#define EMV_CARTE_EMV       	0
#define EMV_CARTE_NON_EMV   	1
#define EMV_CARTE_INCIDENT  	2
#define EMV_CARTE_ABSENTE   	3
#define EMV_LISTE_VIDE      	4
#define EMV_MODULE_EMV_ABSENT 	5
#define EMV_CARTE_REESSAI	  	6

#define DEBIT_AUTRE_AID  0
#define DEBIT_OK         1

#define REP_OK               0
#define REP_PROCESSING_ERROR 1
#define REP_CARD_REMOVED     2

#define APPLI_EMV 0
#define APPLI_B0  1

#define VAL_CONFIRM 0x80 /* bit8 de l'API = 1 */

/* pour le telediagnostic texte : VALEUR INTERDITE 0  */
#define T_CARTEREJETEE   1
#define T_NONISO2        2
#define T_PBMPISTE       3

#define NB_MAX_LABEL	20

typedef struct
{
  T_AFFNOM      libelle;
  NO_SEGMENT    no_appli;
  char          AID_VALUE [LEN_AID];
  int           lg_aid;
  unsigned char priority;
  unsigned char codeTableIndex;
  unsigned int  lengthPreferredName;
  unsigned char preferredName[Taille_LABEL];
  unsigned int  lengthApplicationLabel;
  unsigned char applicationLabel[Taille_LABEL];
  unsigned char	lengthLanguagePreference;
  unsigned char languagePreference[8];
} T_EMV_APPLI;

#endif
/*! @} **/
