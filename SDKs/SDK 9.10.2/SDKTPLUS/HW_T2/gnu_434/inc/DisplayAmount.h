#ifdef __cplusplus
extern "C" {
#endif

#ifndef DISPLAYAMOUNT
#define DISPLAYAMOUNT

/*! @addtogroup KSFAM_DISPLAY_AMOUNT
	* @{
**/

/*! @brief See SAMPLE CARD ENTRY IN SDK SAMPLES CARD ENTRY */

/*! @brief Define a pointer on a function to display a message.
* @param mess    : The message number that be displayed
* @param flag cless: A flag that indicates that cless target shall be displayed
* @param refresh    : Force refresh display  
*/
typedef int (*Fct_Mess) (int mess,int flag_cless,int refresh);

/*! @brief Define a pointer on a function to display the current amount.
* @param amount       : A pointer to the transaction amount
* @param currency_infos :  A pointer to currency data
* @param mess         : The message number that be displayed
* @param periph        : The display peripheral location (terminal display, pinpad display, target display)
* @param flag cless     : A flag that indicates that cless target shall be displayed
* @param refresh       : Force refresh display  
*/
typedef int (*Fct_Amount) (unsigned char *amount, S_MONEY_EXTENDED *currency_infos,int mess,int periph,int flag_cless,int refresh);

/*! @brief Define a pointer on a function to display the target.
*/
typedef int (*Fct_Cless)(void);

/*! @brief Define a pointer on a function to display the check bitmap*/
typedef int (*Fct_Check)(void);

/*! @brief Define a pointer on a function to display the Tpass bitmap*/
typedef int (*Fct_Tpass)(void);

/*! @brief Define a pointer on a function to displaythe message and amount on the pinpad 2 lines
* @param amount       : A pointer to the transaction amount
* @param currency_infos :  A pointer to currency data
* @param mess         : The message number that be displayed
*/
typedef int (*Fct_Pinpad2lines)( unsigned char *amount ,S_MONEY * currency_infos,int mess);

/*! @brief Define a pointer on a function to display the header on a black and white peripheral (Graphic pinpad, C30 target).
* @param header    : set this parameter to 0 on a graphic pinpad B&W or a C30 target B&W  
* @param flag cless  : A flag that indicates that cless target shall be displayed
* @param refresh    : Force refresh display  
*/
typedef int (*Fct_Header)(int header,int periph,int flag_cless,int refresh);

/*! @brief Define the input wait card service. */
typedef struct
{
  int periph;                                 /*!<The display peripheral location (terminal display, pinpad display, target display) */
  int MessWaitCard;                          /*!< The message number that be displayed */
  Fct_Mess  fct_mess;                        /*!< A pointer to a function that can be called by the application if it does no wich to display the current message */
  unsigned char amount[14];                  /*!< The transaction amount*/
  S_MONEY_EXTENDED currency_infos;         /*!<The transaction currency data*/
  Fct_Amount fct_amount;                    /*!< A pointer to a function that can be called by the application if it does no wich to display the current amount*/
  int flag_cless;                             /*!<A flag that indicates that cless target shall be displayed*/
  int x_target_cless_position;                /*!<coordinates x to display the target*/ 
  int y_target_cless_position;                /*!<coordinates y to display the target*/
  Fct_Cless fct_cless;                        /*!<A pointer to a function that can be called by the application if it does no wich to display the target */
  int flag_check;                            /*!<A flag that indicates that the check bitmap shall be displayed*/
  Fct_Check fct_check;                      /*!< A pointer to a function that can be called by the application if it does no wich to display the check bitmap */
  int flag_tpass;                            /*!<A flag that indicates that the Tpass bitmap shall be displayed*/
  Fct_Tpass fct_tpass;                       /*!<A pointer to a function that can be called by the application if it does no wich to display the Tpass bitmap*/
  Fct_Pinpad2lines fct_pinpad2lines;           /*!<A pointer to a function that can be called by the application if it does no wich to display the message and amount on the pinpad 2 lines*/
  Fct_Header fct_header;                    /*!<A pointer to a function that can be called by the application to display the header on a black and white screen (terminal display, pinpad display, target display) */
  void *ruf;                                /*!<ruf*/
}S_CUST_CARD_Entry;

/*! @} **/


/*! @brief This function checks the parameters of customization to display the string amount.\n
 *  This function verifies if the currency has to be displayed before or after the amount: test the parameter currency_position of struct S_MONEY\n
 *  This function checks if the name of the currency has to be replaced by the Euro bitmap contained in the policy of the manager test the
 *  parameter DisplayEuroSymbol of struct S_STATE_PARAM.
 * @param amount   : amount of the transaction
 * @param currency  : currency of transaction
 * @param symbol   : hexadecimal code of Euro bitmap SYMBOL_EURO or SYMBOL_EURO_DAX(only if the font DAX is loaded)
 * @param buf_final      : return the result
 * @param bufamount    : return the buffer amount
 * @param buf_currency  : return the buffer currency
 *
 * 
 * @link KSFAM_DISPLAY_AMOUNT Back to top @endlink
*/
extern void Amount_Format(unsigned char *amount,S_MONEY * currency,unsigned char symbol,unsigned char *buf_final,unsigned char *bufamount,unsigned char *buf_currency);

/*! @} **/
#endif

#ifdef __cplusplus
}
#endif
