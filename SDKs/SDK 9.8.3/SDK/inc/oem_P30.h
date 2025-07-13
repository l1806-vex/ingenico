/*! @addtogroup KSFAM_PPS
 * @{
 */ 
 
#ifndef ___P30_OEM_H
#define ___P30_OEM_H
 

/*! @brief Initialise system to use P30 and its peripherals
 * @param lien : "COM0", "COM1", "COM2", "USB"
 * @return 
 * - TRUE if successful
 * - otherwise FALSE.
 *
 * @link KSFAM_PPS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:P30_Mount:KSFAM_PPS:0x56
// \endif
int P30_Mount(char* lien);


#endif

/*! @}  */ 
