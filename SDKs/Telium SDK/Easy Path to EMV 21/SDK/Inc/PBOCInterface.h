/////////////////////////////////////////////////////////////////

//! \file
//! This file describes the interface of the EmvDcInterface.lib library.

//// Macros & preprocessor definitions //////////////////////////

#ifndef _SECDEL_
#error _SECDEL_ must be defined !
#endif

//// Types //////////////////////////////////////////////////////
/** APDU response */
typedef struct {
 unsigned int Lr;       /**< Length of response data field */
 unsigned char *Data;	/**< String of data bytes received in response (=Lr)*/
 unsigned char SW1;		/**< Command processing status */
 unsigned char SW2;		/**< Command processing qualifier */
}APDUResponse;

//// Functions //////////////////////////////////////////////////


int CAM_Get_EC_Balance (APDUResponse *response);
int CAM_Get_EC_ResetThreshold (APDUResponse *response);
void EC_Request_Cid (unsigned char forced_cid_value);
