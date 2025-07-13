/*
   IDLE support for SMC peripheral.

   Unicapt32 - Idle Application
   Ingenico Latin America
*/

#ifndef SMC_SUPPORT_H
#define SMC_SUPPORT_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * smcSupRequest() may return this to inform that
 * SMC is already inserted.
 */
#define RET_SMC_INSERTED   (RET_EVENT_DETECTED)

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// Fallback steps, used to define where the error happens
/**
 * Error in the powerOn sequency, the status field will be the
 * status returned by the function smcResultGet called
 * to get the return status from the power on
 */
#define GMA_SMC_FALLBACK_POWER_ON (1)
/**
 * Error in the function amgInitPayment that starts the EMV selection process
 */
#define GMA_SMC_FALLBACK_EMV_INIT_SELECTION (2)
/**
 * No applications in the terminal to treat the EMV inserted card
 */
#define GMA_SMC_FALLBACK_EMV_NO_APPS (3)

/**
 * Error in the function amgAskSelection
 */
#define GMA_SMC_FALLBACK_ASK_SELECTION (4)

/**
 * Error in the function amgEmvFinalSelect
 */
#define GMA_SMC_FALLBACK_FINAL_SELECTION (5)


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

// smcResultGet struct B.K
// =======================
typedef struct gmaSmcAtrResult_st
{
   int16 status;             // Execution status
   uint16 length;            // Length of returned data
   uint8 data[50];           // Atr
} gmaSmcAtrResult_t;

/*
 * Enable/Disable SMC events.
 */
int16 smcSupSetEnable(uint8 enabled);

/*
 * Return mask to use in call to psyPeripheralResultWait()
 * in main Idle loop.
 */
uint32 smcSupWaitMask(void);

/*
 * Begin the SMC support.
 */
int16 smcSupBegin(void);

/*
 * End SMC support.
 * Cancel events and close handle.
 */
int16 smcSupEnd(void);

/*
 * Return the SMC handle currently open.
 */
uint32 smcSupGetHandle(void);

/*
 * Make SMC request for card insertion.
 * If the card is already inserted, will ask user to
 * remove it.
 */
int16 smcSupRequest(void);

/*
 * Process the SMC result.
 */
int16 smcSupResult(void);

/*
 * Cancel any pending requests
 */
int16 smcSupCancel(void);

/*
 * Tell the user to remove the smart card.
 */
int16 smcSupRemoveCard(void);

/*
 * Return 1 if there is a pending fallback condition.
 * 0 or a negative number if not.
 */
int16 smcSupIsFallbackPending(void);

/*
 * Clear the fallback condition flag.
 */
int16 smcSupClearFallback(void);

/*
 * Return the number of seconds elapsed since the last SMC transaction
 * that generated a fallback.
 * Return zero
 */
uint32 smcSupFallbackTimer(void);

/**
 * 
 */
int16 smcSupAddFallBackMsg(void);

/**
 * 
 */
int16 smcSupSetFallBack(uint16 step, int16 status);

int16 gmaNoneEmvSelectApplication (gmaSmcAtrResult_t* smcAtr);

#ifdef __cplusplus
}
#endif


#endif

