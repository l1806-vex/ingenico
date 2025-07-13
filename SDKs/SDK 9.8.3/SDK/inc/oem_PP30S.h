/*! @addtogroup KSFAM_PPS
 * @{
 */ 
 
#ifndef ___PP30S_OEM_H
#define ___PP30S_OEM_H


/*! @brief Initialise system to use PP30S and its peripherals
 * @param lien : "COM0", "COM1", "COM2", "USB"
 * @return 
 * - TRUE if successful
 * - otherwise FALSE.
 *
 * @link KSFAM_PPS Back to top @endlink
 */
// \if SIMULATION
//  @GSIM_F:PP30S_Mount:KSFAM_PPS:
// \endif
int PP30S_Mount(char* lien);


#endif

/*! @}  */ 
