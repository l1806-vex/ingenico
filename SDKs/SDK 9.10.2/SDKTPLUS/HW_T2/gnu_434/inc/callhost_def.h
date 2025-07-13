#ifdef __cplusplus
extern "C" {
#endif

#ifndef __CALLHOST_DEF_H_INCLUDED__
#define __CALLHOST_DEF_H_INCLUDED__

//! @defgroup NTP_FUNCTIONS NTP_Functions
//! @{


/*! @brief This function updates SYSTEM disk from a specified disk. 
 *
 * Signature and syntax are checked before activation. 
 * @param disk : disk name where new software in stored (name without "/") 
 * @return
 * - non zero value if activation has not been executed. In this case see TRACEFILE.LST in input disk
 * - 0 otherwise.
 *
 * @note Warning : SoftwareActivate is case sensitive. Telium software file names with extension must be UPPER case(Otherwise the file is ignored)
 *
 * @link  KSFAM_OS Back to top @endlink
 */ 
int SoftwareActivate(const char *disk);

/*! @brief This function updates SYSTEM disk from a specified disk. 
 *  @note See \ref SoftwareActivate for more details
 */
#define NTP_SoftwareActivate SoftwareActivate

/*! @brief This function checks a disk without updating SYSTEM disk. 
 *
 * Signature and syntax are checked. 
 * @param disk : disk name where new software is stored (name without "/") 
 * @return
 * - non zero value if activation has not been executed. In this case see TRACEFILE.LST in input disk
 * - 0 otherwise.
 *
 * @note This function is similar to NTP_SoftwareActivate but without SYSTEM update. 
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
int NTP_SoftwareCheck(const char *disk);

/*! @brief NTP_SoftwareActivateRam allows to update SYSTEM disk from another disk.
 * @param path : Name of the disk, where are stored softwares to be activated.
 * @return
 * - 0 : No errors.
 * - Number of errors otherwise.
 *
 * @note On the disk given in parameter, a file named TRACEFILE.LST is created.
    This file contains the list of errors that occured.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
int NTP_SoftwareActivateRam(const char *path);

//! @}


#endif   // __CALLHOST_DEF_H_INCLUDED__

#ifdef __cplusplus
}
#endif
