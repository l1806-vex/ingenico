/*
 * OEM C  C30 interfaces 
 */ 
 
#ifndef ___C30_OEM_H
#define ___C30_OEM_H
 
#include "oem_buzzerC30.h"
#include "oem_ledsC30.h"
#include "oem_retroeclairageC30.h"
#include "oem_cless.h"

/*! @brief Initialise system to use C30 and its peripherals
 * @param lien : "USB" if C30 is connected to terminal by USB, otherwise we use Serial link
 * @return
 * - TRUE if successful
 * - otherwise FALSE.
 *
 */
int C30_Mount(char* lien);

#endif

