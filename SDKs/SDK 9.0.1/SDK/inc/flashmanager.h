/*! @addtogroup KSFAM_FFMS
	* @{
 */ 

#ifndef _FLASH_MANAGER_H
#define _FLASH_MANAGER_H

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
#define FLASH_MAKER_SAMSUNG 0xEC
#define FLASH_MAKER_TOSHIBA 0x98
#define FLASH_MAKER_AMD     0x01
#define FLASH_MAKER_FUJITSU 0x04
#define FLASH_MAKER_HYNIX   0xAD


/*! @brief RegisterPowerFailure is used to save an application RAM data area ( global data ) in FLASH. 
 * 
 * Data are saved to Nand flash memory when power down occures.
 * Data will be recovered in RAM when application restarts at boot time.
 * @param Label : area identifier must start with the prefix 'E_' followed by the application
    name ( example E_AMEX for American Express application ) .
 * @param ptr : area address
 * @param size_p : area size in bytes
 * @return
 * - FM_SAVE_DATA_OK        0 : New data area created. No data restored
 * - FM_SAVE_DATA_PRESENT   1 : Existing area : data was restored successfully.
 * - FM_SAVE_DATA_KO        2 : Error : too many data registered
 * @note The size is limited to 80Kb for all applications.
 * @note The size is limited to 5Kb for each application.
 * @note This function is deprecated. Please use file system instead.
 * 
 * @code 
 *  typedef struct {
 *    unsigned int data1;    
 *  } MY_DATA;
 *  MY_DATA MyData;     
 *  memset(&MyData, 0, sizeof(MyData)); // data must be initialized BEFORE calling RegisterPowerFailure 
 *  RegisterPowerFailure("E_AMEX", (unsigned char *)&MyData, sizeof(MyData));
 *  
 *  //RegisterPowerFailure return 0 when it is called for the first time : address and size of MyData is recoded by system
 *  //RegisterPowerFailure return 1 when it is called at next startup time : data previously saved in flash is restored into MyData
 *  //RegisterPowerFailure return 2 when there is an error (too many calls or to much data)
 * @endcode 
 
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:RegisterPowerFailure:KSFAM_FFMS:
//  @GSIM_S:RegisterPowerFailure:E_RegisterPowerFailure
//  2:DATA_CODE(size_p)
//  1:ONE_ADDRESS
// \endif
unsigned int RegisterPowerFailure(char * Label,unsigned char * ptr,unsigned short size_p);


/*! @brief UnregisterPowerFailure is used to remove an area defined by RegisterPowerFailure. 
 *
 * @param Label : area identifier must start with the prefix 'E_' followed by the application
    name ( example E_AMEX for American Express application ) .
 * @return
 * - FM_SAVE_DATA_OK        0 : data has been removed
 * - FM_SAVE_DATA_KO        2 : data has not been found
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:UnregisterPowerFailure:KSFAM_FFMS:
//  @GSIM_S:UnregisterPowerFailure:E_UnregisterPowerFailure
//  1:ONE_ADDRESS
// \endif
unsigned int UnregisterPowerFailure(char *Label);

/*! @brief PersistentDataUpdate save persistent data to file.
 *
 * Save data regstred using RegisterPowerFailure
 *
 * @param adr : data area to save.
 * @return None.
 *
 * @link KSFAM_FFMS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:PersistentDataUpdate:KSFAM_FFMS:
//  @GSIM_S:PersistentDataUpdate:E_PersistentDataUpdatee
//  1:ONE_ADDRESS
// \endif
void PersistentDataUpdate(void *adr);


#endif

/*! @}  */ 


