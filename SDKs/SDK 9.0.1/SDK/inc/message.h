/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/
#ifndef MESSAGE_H
#define MESSAGE_H

#define FRANCAIS  1
#define ANGLAIS   0

/*! @brief  value for PSQ_Update_language function */
#define FRENCH    '1' /*!<  to select french*/
#define ENGLISH   '0' /*!<  to select english*/

#define _AFF_FRANCE_      0

#define _AFF_AUTOMATIQUE_ 0
#define _AFF_EXPORT_      1
#define _AFF_TRANSPARENT_ 2
#define _AFF_COLOR_       3

#define MESS0     0x1234

#define MESS_LIC MESS308

/*! @brief This structure provides the 2 versions of the same message, in different languages.*/
//GSIM_T:S_TAB_LANGUE:DATA_CODE(strlen(anglais) + strlen(francais) + sizeof(int))
typedef struct
{
  int   numero_mess;								/*!<  number of the message*/
  char *anglais;										/*!<  pointer on the english version of the message*/
  char *francais;										/*!<  pointer on the french version of the message*/
}
S_TAB_LANGUE;



/*! @brief Retunrs a message from the message list.
 * @param num : message number
 * @param langue : language
 * @return Buffer containing the message
 * @par exit (EXIT_DLL_EXTENS_NOT_INITIALIZED + 68) if function does not exist
// \if SIMULATION
//  @GSIM_F:LireMessage:KSFAM_AUTRES_MANAGER:0x05
// \endif
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
extern char *LireMessage(int num,int langue);


#endif
/*! @} **/
