
#ifndef GMA_CUS_TOUCH_SCREEN_H_INCLUDED
#define GMA_CUS_TOUCH_SCREEN_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


#define GMA_CT_MAX_REGIONS_TS (50)

typedef void (*gmaCTHandler)(uint8 pluginId, uint16 appId,uint16 action, uint16 parameter);

typedef struct gmaCTtouchArea_st gmaCTtouchArea_t;
struct gmaCTtouchArea_st
{
	uint16 yUp;
	uint16 xLeft;
	uint16 yBottom;
	uint16 xRight;
};

typedef struct gmaCTtouchData_st gmaCTtouchData_t;

struct gmaCTtouchData_st
{
	uint16 action;
	uint16 parameter;
};


/**
 * Reset the library
 */
void gmaCTReset(void);

/**
 * Set the function that will be called when an touch screen event happens
 */
void gmaCTSetHandlerFunction(gmaCTHandler handler);


/**
 * Make the request to get a touch screen entry
 */
void gmaCTSreq(void);

/**
 * Analise the result.
 * 
 * @param ret return value from the psyPeripheralResultWait
 */
void gmaCTSresult(int32 ret);

/**
 * enable or disable the touch screen support
 * 
 * @param status if 1 activate the library, if 0 deactivate
 */
void gmaCTSEnableTouchScreen(uint8 status);

/**
 * Open the touch screen handle
 */
void gmaCTOpenHandle(void);

/**
 * Get the touchHandle
 */
uint32 gmaCTGetTouchHandle(void);


/**
 * Close the touch Screen handle
 */
void gmaCTCloseHandle(void);

#ifdef __cplusplus
}
#endif


#endif
