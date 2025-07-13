
#ifndef __GMA_MAG_CUSTOM_H_INCLUDED
#define __GMA_MAG_CUSTOM_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This function is called from main custom call back module and will
 * trigger a Magnetic Card Reader request
 *
 */
int16 gmaMagCrdReq (void);


/*
 * This function is called from main custom call back module and will
 * trigger a Magnetic Card Reader request
 *
 */
int16 gmaMagCrdResultGet (void);


/*
 * Cancel any pending requests
 */
int16 gmaMagSupCancel(void);


/*
 * This function is called from anywhere and will
 * open the Magnetic Card Reader handle
 *
 */
int16 gmaMagOpen (void);


/*
 * This function is called from anywhere and will
 * close the Magnetic Card Reader handle
 *
 */
int16 gmaMagClose (void);

int16 gmaMagCrdProcess (magTripleResult_t* magStripe);

#ifdef __cplusplus
}
#endif


#endif

