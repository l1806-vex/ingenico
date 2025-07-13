
#ifndef GMA_HMI_TRANSFER_H_INCLUDED
#define GMA_HMI_TRANSFER_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


/**
 * This function must be called instead of call directly the function \ref gmaAppMsgWakeApp to have support
 * for HMI transfer when the application support it.
 */
int16 gmaHmiTrAppMsgWakeApp(uint16 appId, uint8 logicalId, amgMsg_t *msg);

/**
 * Initialize
 */
void gmaHmiTrInit(void);


/**
 * Treat the structure \ref gmaStructTransferHmiSup_t.
 * 
 * This structure can be received from plug-ins or from applications
 * 
 * \ref appId the application Id that send the structure
 * 
 * \ref msg a pointer to the structure
 */
void gmaHmiTrTreatTransferHmiSup(uint16 appId, gmaStructHeader_t *msg);

/**
 * Treat the structure \ref gmaStructTransferHmi_t.
 * 
 * This structure can be received from plug-ins or from applications when 
 * the application/plug-in close and open a transfer hmi handle.
 * 
 * \ref appId the application Id that send the structure
 * 
 * \ref msg a pointer to the structure
 */
void gmaHmiTrTreatTransferHmiBack(uint16 appId, gmaStructHeader_t *msg);

/**
 * 
 */
void gmaHmiTrHmiOpen(void);
/**
 * 
 */
void gmaHmiTrHmiClose(void);

#ifdef __cplusplus
}
#endif


#endif

