/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

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
// \if SIMULATION
//  @GSIM_F:iso2:KSFAM_AUTRES_MANAGER:0xA0
//  @GSIM_A:1:ONE_ADDRESS 
//  @GSIM_A:2:DATA_SIZE(4)
//  @GSIM_A:3:DATA_SIZE(41)
//  @GSIM_A:4:DATA_SIZE(40)
//  @GSIM_A:5:DATA_SIZE(4)
// \endif
extern int iso2 (FILE *fd, unsigned char *length, unsigned char *swipe_read,unsigned char *Data_bit,int *Len);


#endif
/*! @} **/
