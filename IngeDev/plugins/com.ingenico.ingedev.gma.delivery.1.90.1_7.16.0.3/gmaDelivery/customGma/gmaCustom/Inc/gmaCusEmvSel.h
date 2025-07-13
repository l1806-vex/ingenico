
#ifndef GMA_CUSTOM_EMV_SELECTION_H_INCLUDED
#define GMA_CUSTOM_EMV_SELECTION_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the library
 */
void gmaEmvSelInitialize(void);

/**
 * Add a new AID for the application appId, logicalId
 */
int16 gmaEmvSelAddAid(uint16 appId, uint8 logicalId, amgAid_t *aid);

/**
 * Delete the AID list for the appId
 */
int16 gmaEmvSelDelAids(uint16 appId, uint8 logicalId);

/**
 * Call the function amgSelectionCriteriaAdd to add the AIDs to the AMG,
 * to prepare the selection process
 */
int16 gmaEmvSelAddNow(void);


#ifdef __cplusplus
}
#endif

#endif

