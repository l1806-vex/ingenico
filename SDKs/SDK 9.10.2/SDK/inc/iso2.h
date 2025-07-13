/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef ISO2_H
#define ISO2_H

#define	ISO2_LEN	40
#define	ISO2_WDL	5



/*! @brief Returns an iso2 track
 * @param fd : pointer to FILE structure.
 * @param length : length of the iso2 data
 * @param swipe_read : iso2 data
 * @param Data_bit : data of the track
 * @param Len : length of the track
 * @return
 * - ISO_OK 0
 * - DEF_SEP 1
 * - DEF_PAR 2 
 * - DEF_LRC 3 
 * - DEF_LUH 4 
 * - DEF_NUM 5 
 * - NO_DATA 6 
 * @par exit (EXIT_DLL_SV_NOT_INITIALIZED + 42) if function does not exist
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
#ifndef __FRAMEWORK_TELIUM_PLUS__
extern int iso2 (FILE *fd, unsigned char *length, unsigned char *swipe_read,unsigned char *Data_bit,int *Len);
#else
extern int iso2 (Telium_File_t *fd, unsigned char *length, unsigned char *swipe_read,unsigned char *Data_bit,int *Len);
#endif


#endif
/*! @} **/
#ifdef __cplusplus
}
#endif
