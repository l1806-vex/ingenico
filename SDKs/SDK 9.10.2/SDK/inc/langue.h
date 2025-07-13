/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/
#ifdef __cplusplus
extern "C" {
#endif

#ifndef LANGUE_H
#define LANGUE_H

/************************************************************************
  DLL LANGUAGE SERVICES 
*************************************************************************/




/*! @brief  Return a list of language .
* @param TableLangue: table of language
* @param Nb: number of language defined in the dll language 
* @return 0
* @par exit None
 *
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
extern int            GetExtendedLangage         (unsigned char TableLangue[MAX_LANGUE][T_LANGUE],unsigned int *Nb);



/*! @brief  Return a message contained in a table of messages
* @param num of message
* @param langue: pointer on a language defined in the table language 
* @return pointer on message
* @par exit (EXIT_DLL_LANGUE_NOT_INITIALIZED + 0) if function does not exist
*
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
extern char          *GetExtendedMessage         (int num,unsigned char *langue);




/*! @brief Return the name of current language .
* @param langue: number of language defined in the dll language 
* @return pointer on name language
* @par exit (EXIT_DLL_LANGUE_NOT_INITIALIZED + 2) if function does not exist
*
 * @link KSFAM_AUTRES_MANAGER Back to top @endlink
*/
extern char          *GetCurrentExtendedLangage  (int langue);


/*****************************************************************************/
/* Contain message structure                                                 */
/* To Add a language, add an element to the struture (language2 for example) */
/* and complete the langage_list_message with the new langage                */
/*****************************************************************************/
typedef struct
{
  int   number;
  char *language1;
}
S_LANGUAGE;

#endif 

/*! @} **/
#ifdef __cplusplus
}
#endif
