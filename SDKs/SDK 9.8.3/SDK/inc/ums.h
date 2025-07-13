/*! @addtogroup KSFAM_UMS
	* @{
**/

#define TYPE_USB        0
#define TYPE_MMC        1






/*! @brief This function waits for insertion of a UMS device.
 * @param To   : Timeout operates in units seconds 
 * @param Type : TYPE_USB or TYPE_MMC (see ums.h) 
 * @return 
 * - CR_ENTRY_OK if success 
 * - CR_ENTRY_NOK if problem 
 * - CR_ENTRY_CANCEL if cancel (red key) 
 * - CR_ENTRY_TIME_OUT if timeout 
 * @par exit (EXIT_DLL_USM_NOT_INITIALIZED + 0) if function does not exist
 * @note KEYBOARD and DISPLAY must be opened before calling this function. 
// \if SIMULATION
//  @GSIM_F:WaitForUms:KSFAM_UMS:0x01
// \endif
 *
 * @link KSFAM_UMS Back to top @endlink
*/
extern int  WaitForUms(unsigned short To,int Type);


/*! @brief This function selects and activates software from USB device.
 * 
 *	Same function with LoadFromUms but the device is USB (user don't have to choose device). 
 * - If Path is not a NULL pointer, all steps are automatically executed without user action (BATCH mode).
 * - If last directory of Path is "MANAGER", files are copied into MANAGER volume
 * - If last directory of Path is "HOST", files are copied into HOST volume
 * - If last directory of Path is not "HOST" or "MANAGER", files are copied into SYSTEM volume
 *
 * @param noappli : application number.
 * @param *Path : path into device to activate.If pointer NULL, the user has to select items to activate. 
 * @return None (void).
 * @par exit (EXIT_DLL_USM_NOT_INITIALIZED + 1) if function does not exist
// \if SIMULATION
//  @GSIM_F:LoadFromUsb:KSFAM_UMS:0x03
// \endif
 *
 * @link KSFAM_UMS Back to top @endlink
*/
extern void LoadFromUsb(NO_SEGMENT noappli,char *Path);


/*! @brief This function select and activates software from MMC device. 
 * 
 *	Same function with LoadFromUms but the device is MMC (user don't have to choose device). 
 * - If Path is not a NULL pointer, all steps are automatically executed without user action (BATCH mode)
 * - If last directory of Path is "MANAGER", files are copied into MANAGER volume
 * - If last directory of Path is "HOST", files are copied into HOST volume
 * - If last directory of Path is not "HOST" or "MANAGER",files are copied into SYSTEM volume.
 *
 * @param noappli : application number.
 * @param *Path   : path into device to activate. If pointer NULL, the user has to select items to activate. 
 * @return None
 * @par exit (EXIT_DLL_USM_NOT_INITIALIZED + 2) if function does not exist
// \if SIMULATION
//  @GSIM_F:LoadFromMmc:KSFAM_UMS:0x04
// \endif
 *
 * @link KSFAM_UMS Back to top @endlink
*/
extern void LoadFromMmc(NO_SEGMENT noappli,char *Path);


/*! @brief In this function, the user choose type of device (USB or MMC)
 * 
 *	And then the function wait for insertion of the device.
 *  
 *	When device is ready, a menu is displayed with the contents of the device.
 * - Green key is used to change directory, 
 * - Red key is used to cancel, 
 * - UPPER and LOWER key are used to change current selection, 
 * - F4 key is used to select file or directory to activate, 
 * - F1 key is used to start activation of file/directory selected. 
 *
 * (When a directory is selected, all files and sub-directory are selected).
 *
 * When F1 is pressed, press VAL (green key) to accept activation, press CANCEL (red key) to abort. 
 *
 * When VAL is pressed, copy is in progress. When all files transferred strike a key to activate transferred files .
 * @param noappli : application number.
 * @par exit (EXIT_DLL_USM_NOT_INITIALIZED + 3) if function does not exist
 * @note KEYBOARD and DISPLAY must be opened before calling this function. 
// \if SIMULATION
//  @GSIM_F:LoadFromUms:KSFAM_UMS:0x02
// \endif
 *
 * @link KSFAM_UMS Back to top @endlink
*/
extern void LoadFromUms(NO_SEGMENT noappli);

/*! @} **/
