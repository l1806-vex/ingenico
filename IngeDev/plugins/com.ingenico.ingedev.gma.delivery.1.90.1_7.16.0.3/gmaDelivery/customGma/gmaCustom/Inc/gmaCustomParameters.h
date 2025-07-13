
#ifndef GMA_CUSTOM_PARAMETERS_H_INCLUDED
#define GMA_CUSTOM_PARAMETERS_H_INCLUDED

/**
 * will read the file and store the information on the memory
 */
int16 gmaCusParameterInit(void);

//"-1235|-11218|-12323|-123235|-1223"
//"ALL"
/**
 * 
 */
int16 gmaCusGetValueList(char *name, int16 *list, uint16 *size);



#endif
