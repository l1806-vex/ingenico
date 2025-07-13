#ifdef __cplusplus
extern "C" {
#endif

#ifndef __FLASHMANAGER_DEF_H_INCLUDED__
#define __FLASHMANAGER_DEF_H_INCLUDED__

/*! @addtogroup KSFAM_FFMS
	* @{
 */ 
 
/*
======================================================================
					List of Defines
======================================================================
*/

/*! @brief Retrun values for RegisterPowerFailure. */
#define FM_PASS                                 1		/*!< File system return successfully  */
#define FM_FAIL                                 2		/*!< file system returned with error  */
#define FM_GARBAGE_COLLECTION                   3		/*!< File system return successfully, but garbage collection was stated  */

// Area ident
/*! @brief Nand area identification. */
#define FM_ID_AREA_APPLICATION   0	  /*!< Application area : SYSTEM disk  */
#define FM_ID_AREA_DATA          1		/*!< Data area : use to store application disks and HOST disk  */
#define FM_ID_AREA_BOOT_RAM      2		/*!< Reserved for SYSTEM use  */
#define FM_NB_AREA_FILE          3		/*!< Reserved for SYSTEM use  */
#define FM_ID_AREA_BLOC_HS       3		/*!< Reserved for SYSTEM use  */
#define FM_ID_AREA_SAVE_FLIP     4		/*!< Reserved for SYSTEM use  */
#define FM_ID_AREA_SAVE_FLOP     5		/*!< Reserved for SYSTEM use  */

// Page ident and address
#define FM_NO_PAGE_ADDRESS               0xFFFFFFFFL	 		/*!< Reserved for SYSTEM use  */

#define FM_NB_AREA_FLASH         6	 		/*!< Reserved for SYSTEM use  */

// Contexte management
#define FM_MAX_SIZE_APPLI_CONTETXE	0x19000  /*!< max size of RegisterPowerFailure : 100 KOctets */
#define FM_SIZE_LABEL_CONTEXTE   16					 /*!< max size of label for RegisterPowerFailure */
#define FM_LABEL_ALL_CONTEXTE_RESTOR   "ALL"  /*!< erase all RegisterPowerFailure data */
#define FM_LABEL_GET_DATA              "FM_DataGet"	 		/*!< Reserved for SYSTEM use  */

/*! @brief Return code for RegisterPowerFailure function. */
#define FM_SAVE_DATA_OK        0		 /*!< New data area created. No data restored  */
#define FM_SAVE_DATA_PRESENT   1		 /*!< Existing area : data was restored successfully.  */
#define FM_SAVE_DATA_KO        2		 /*!< Error : too many data registered  */

/*! @brief Flash Manufacturer definitions. */
#define FLASH_MAKER_AMD     0x01
#define FLASH_MAKER_FUJITSU 0x04
#define FLASH_MAKER_ST      0x20
#define FLASH_MAKER_MICRON  0x2C
#define FLASH_MAKER_TOSHIBA 0x98
#define FLASH_MAKER_HYNIX   0xAD
#define FLASH_MAKER_SAMSUNG 0xEC

/*! @}  */ 


#endif   // __FLASHMANAGER_DEF_H_INCLUDED__

#ifdef __cplusplus
}
#endif
