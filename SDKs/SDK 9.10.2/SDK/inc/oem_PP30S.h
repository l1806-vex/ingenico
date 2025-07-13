#ifdef __cplusplus
extern "C" {
#endif
 
#ifndef __OEM_PP30S_H_INCLUDED__
#define __OEM_PP30S_H_INCLUDED__

/*! @addtogroup KSFAM_PPS
 * @{
 */ 

/*! @brief Initialise system to use PP30S and its peripherals
 * @param lien : "COM0", "COM1", "COM2", "USB"
 * @return 
 * - TRUE if successful
 * - otherwise FALSE.
 *
 * @link KSFAM_PPS Back to top @endlink
 */
int PP30S_Mount(char* lien);

/*! @}  */


#endif   // __OEM_PP30S_H_INCLUDED__

 #ifdef __cplusplus
}
#endif
