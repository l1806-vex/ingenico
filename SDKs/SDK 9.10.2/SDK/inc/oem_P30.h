#ifdef __cplusplus
extern "C" {
#endif
 
#ifndef __OEM_P30_H_INCLUDED__
#define __OEM_P30_H_INCLUDED__
 
/*! @addtogroup KSFAM_PPS
 * @{
 */ 

/*! @brief Initialise system to use P30 and its peripherals
 * @param lien : "COM0", "COM1", "COM2", "USB"
 * @return 
 * - TRUE if successful
 * - otherwise FALSE.
 *
 * @link KSFAM_PPS Back to top @endlink
 */ 
int P30_Mount(char* lien);

/*! @}  */ 


#endif   // __OEM_P30_H_INCLUDED__

#ifdef __cplusplus
}
#endif
