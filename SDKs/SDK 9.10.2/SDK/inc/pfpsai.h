/*! @addtogroup KSFAM_M2OS
	* @{
**/
/*   definition des types de touches */
#ifdef __cplusplus
extern "C" {
#endif

#define T_FONCTION	      0x80   
#define T_CORRECTION	  0x81   
#define T_VALIDATION	  0x82   
#define T_NUMERIQUE	      0x83   
#define T_ALPHANUMERIQUE  0x84 

#define NUMBER 0xA0
#define LETTER 0xB0
  
#define CLEAR         0
#define NO_CLEAR      1
#define ERROR_SAISIE 9999 

#define SAISIE_ALPHA        0
#define SAISIE_NUM          1
#define SAISIE_FCT          2
#define SAISIE_MT           3
#define SAISIE_SEUIL        4
#define SAISIE_DATE         5
#define SAISIE_HEURE        6
#define SAISIE_OPERATION    7
#define G_SAISIE_LISTE      8
#define G_SAISIE_NUM        9
#define G_SAISIE_DATE       10
#define G_SAISIE_HEURE      11
#define G_SAISIE_ALPHA      12 
#define SAISIE_CODE         13 
#define G_SAISIE_CODE       14 
#define G_AFF_LISTE_PPR     15
#define G_SAISIE_FCT        16
#define G_SAISIE_ETENDUE    17
#define G_AFF_LISTE         18

#define wSAISIE_ALPHA        20
#define wSAISIE_NUM          21
#define wSAISIE_FCT          22
#define wSAISIE_MT           23
#define wSAISIE_SEUIL        24
#define wSAISIE_DATE         25
#define wSAISIE_HEURE        26
#define wSAISIE_OPERATION    27
#define wG_SAISIE_LISTE      28
#define wG_SAISIE_NUM        29
#define wG_SAISIE_DATE       30
#define wG_SAISIE_HEURE      31
#define wG_SAISIE_ALPHA      32 
#define wSAISIE_CODE         33 
#define wG_SAISIE_CODE       34 
#define wG_AFF_LISTE_PPR     35
#define wG_SAISIE_FCT        36
#define wG_SAISIE_ETENDUE    37
#define wG_AFF_LISTE         38
#define wGUI_ENTRY_LIST    39
#define wGUI_AFF_LISTE       40
#define wGUI_SAISIE_NUM     41 
#define wGUI_ICON_LISTE      42
#define wGUI_SAISIE_ETENDUE 43
#define wGUI_SAISIE_DATE_FR 44
#define wGUI_SAISIE_DATE_US 45
#define wGUI_SAISIE_DATE_DE 46
#define wGUI_SAISIE_DATE_CN 47
#define wGUI_SAISIE_IP        48
#define wGUI_SAISIE_ALPHA_NUM 49
#define wGUI_SAISIE_CODE     50
#define wGUI_SAISIE_HEURE 51
#define wGUI_SAISIE_ALPHA 52
#define wGUI_SAISIE_BINAIRE 53
#define wGUI_MULTI_ENTRY_LIST 54
#define wGUI_LARGE_ENTRY_LIST    55
#define wGUI_LARGE_ICON_LIST   56
#define wGUI_ENTRY_FCT 57

#define LGMONTANT 8
/*! @} **/
#ifdef __cplusplus
}
#endif
