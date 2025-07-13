/*! @addtogroup KSFAM_SMS
	* @{
			
 	* @section ex_GPRS1 SMS Example/s
 	*
 	* @subsection sub01_SMS SMS Management
 	*
 	* The sample of code below shows how to read SMS from the SIM card and how to send a textual SMS.
 	*

 * @include sms_Sample_01.c
 	* 
 	* @link KSFAM_SMS Back to top @endlink
 		
		
 */ 

#ifndef SMS_H
#define SMS_H

/*
======================================================================
					List of Defines
======================================================================
*/
// Error codes
#define SMS_OK						0
#define SMS_ERR_ALREADY_OPENED		-1
#define SMS_ERR_NO_SMS				-2
#define SMS_ERR_LAST_SMS			-3
#define SMS_ERR_BAD_PARAMETER		-4
#define SMS_ERR_INCOMPLETE			-5
#define SMS_ERR_TIMEOUT				-6
#define SMS_ERR_DELETED				-7
#define SMS_ERR_TOO_LONG_MSG		-9
#define SMS_ERR_UNKNOWN				-8

#define SMS_ERR_SIM_UNAVAILABLE		-100
#define SMS_ERR_NETWORK_UNAVAILABLE -101
#define SMS_ERR_GPRS_UNAVAILABLE    -102

// Encoding flags
#define SMS_NO_ENCODING 0
#define SMS_GSM_7_BIT 1

#ifdef _GSIM_

/* redefinition du type pour analyse GSIM */
typedef void SMS;

#else

struct sms;
typedef struct sms SMS;

#endif

/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Define the basic informations about a SMS. */
typedef struct
{
	int length;										//!< length in bytes.
	char sender[30];								//!< sender phone number.
	char timestamp[30];								//!< service center timstamp.
	int slots;										//!< number of slots used by this message.
	int slots_tot;									//!< number of slots used by this message when complete.
} SMS_INFO;



/*
======================================================================
			Functions Definition
======================================================================
*/


/*! @brief This function sets the SMS center address.
 * @param sca : pointer to SMS Center Address.
 * @return 
 * - GPRS_OK if OK.
 * - A negative error code otherwise.      
 * - #SMS_OK                    
 * - #SMS_ERR_GPRS_UNAVAILABLE  
 * - #SMS_ERR_SIM_UNAVAILABLE   
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_set_sim_sca:KSFAM_GPRS:0x0D
// \endif
int sms_set_sim_sca(const char *sca);


/*! @brief This function is used to get the address of the SMS center.
 * @param sca : The SMS center address. It is a output parameter. It must be allocated by the calling function with a size of 20 characters.
 * @return
 * - #SMS_OK 
 * - #SMS_ERR_SIM_UNAVAILABLE 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 41) if function does not exist
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_get_sim_sca:KSFAM_GPRS:0x0F
// \endif
int sms_get_sim_sca(char *sca);


/*! @brief This function sends a message (binary or text encoded).
 * @param dest_addr : Destination address (phone number).
 * @param msg : 
 * @param msg_lg : Message length. 
 * @param encoding : Message encoding format. : 
 * - SMS_NO_ENCODING Binary message.
 * - SMS_GSM_7_BIT Text message. Encoded 7 bits.
 *
 * @param msg : Message content. 
 * @return 
 * - #SMS_OK 
 * - #SMS_ERR_GPRS_UNAVAILABLE 
 * - #SMS_ERR_NETWORK_UNAVAILABLE 
 * - #SMS_ERR_TOO_LONG_MSG 
 * - #SMS_ERR_UNKNOWN
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 43) if function does not exist
 *
 * @note 
 * - The maximum size of a short message is basically 140 bytes. 
 * - Message can be encoded using a 7 bits character fonts. It increases the size of text 
 * - message to 160 characters ( 160 * 7 bits = 140 * 8 bits).
 * - Messages with a size > 160 bytes can be sent. 
 * - The function automatically fragments and chains the message in short messages (SM PDU).
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_send:KSFAM_GPRS:0x04
// \endif
int sms_send(const char *dest_addr, const char *msg, int msg_lg, int encoding);


/*! @brief This function reads all the received messages and stores them in a chained list. 
 *
 *	It automatically concatenates chained messages (PDUs) to rebuild the complete message.
 * @param err : Return an accurate error code :
 * - #SMS_ERR_GPRS_UNAVAILABLE 
 * - #SMS_ERR_NO_SMS 
 * - #SMS_ERR_NETWORK_UNAVAILABLE 
 * - #SMS_ERR_SIM_UNAVAILABLE 
 *
 * @param err : Return an accurate error code :
 * @return 
 * - The handle on the first message in the list if OK.
 * - NULL otherwise.
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 44) if function does not exist
 *
 * @note 
 * - Incomplete messages are stored in a separate list. 
 * - They can be accessed with dedicated functions suffixed with "_incomplete".
 *
 * An example is available at @ref sub01_SMS  
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_open:KSFAM_GPRS:0x01
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:1:ONE_POINTER
// \endif
SMS * sms_open(int * err);


/*! @brief This function moves the position cursor at the first position of the message list. 
 *
 *	It returns the handle on the first message or NULL when the list is empty. 
 * @param err : accurate error code. Ouput parameter.
 * - #SMS_ERR_GPRS_UNAVAILABLE  
 * - #SMS_ERR_NO_SMS            
 * - #SMS_OK 
 *
 * @return
 * - The handle on the first message in the list.
 * - NULL.
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 45) if function does not exist
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_first:KSFAM_GPRS:0x06
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:1:ONE_POINTER
// \endif
SMS * sms_first(int * err);


/*! @brief This function moves the position cursor at the first position of the incomplete message list. 
 *	It returns the handle on the first message or NULL when the list is empty. 
 * @param err : accurate error code.
 * - #SMS_ERR_ALREADY_OPENED 
 * - #SMS_ERR_GPRS_UNAVAILABLE   
 * - #SMS_ERR_NO_SMS            
 * - #SMS_OK  
 *
 * @return 
 * - The handle on the first incomplete message in the list if OK.
 * - NULL otherwise. 
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_first_incomplete:KSFAM_GPRS:0x07
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:1:ONE_POINTER
// \endif
SMS * sms_first_incomplete(int * err);


/*! @brief This function moves the position cursor at the next position in the message list. 
 *
 * It returns the handle on the next message or NULL when the end of list is reached. 
 * @param sms_h : pointer to the current SMS of the list.
 * @param err : accurate error code.
 * - #SMS_ERR_GPRS_UNAVAILABLE    
 * - #SMS_ERR_NO_SMS              
 * - #SMS_OK                   
 * - #SMS_ERR_BAD_PARAMETER       
 * - #SMS_ERR_LAST_SMS            
 *
 * @return The handle on the next message in the list or NULL when the position cursor has reached the end of the list. 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 46) if function does not exist
 *
 * An example is available at @ref sub01_SMS  
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_next:KSFAM_GPRS:0x0A
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
// \endif
SMS * sms_next(SMS * sms_h, int * err);


/*! @brief This function moves the position cursor at the next position in the incomplete message list.
 *
 *	It returns the handle on the next incomplete message or NULL when the end of list is reached. 
 * @param sms_h_ : pointer to the current incomplete SMS of the list.
 * @param err : accurate error code.
 * - #SMS_ERR_GPRS_UNAVAILABLE  
 * - #SMS_ERR_NO_SMS          
 * - #SMS_OK                
 * - #SMS_ERR_BAD_PARAMETER     
 * - #SMS_ERR_LAST_SMS         
 *
 * @return The handle on the next message in the incomplete message list or NULL when the position cursor has reached the end of the list. 
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_next_incomplete:KSFAM_GPRS:0x0B
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
// \endif
SMS * sms_next_incomplete(SMS * sms_h_, int * err);


/*! @brief This function waits for the reception of a new message.
 * @param timeout : Waiting time (in 10 ms units)
 * @param err : accurate error code
 * - #SMS_ERR_GPRS_UNAVAILABLE     
 * - #SMS_OK                  
 * - #SMS_ERR_UNKNOWN 
 * - #SMS_ERR_NETWORK_UNAVAILABLE 
 * - #SMS_ERR_TIMEOUT              
 * - #SMS_ERR_INCOMPLETE           
 *
 * @return
 * - A handle on the new received message. 
 * - Or NULL when no message has been received. 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 47) if function does not exist
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_wait:KSFAM_GPRS:0x0E
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
// \endif
SMS * sms_wait(int timeout, int * err);


/*! @brief This function returns the content of the message (text message).
 * @param sms_h : Handle on the message to read.
 * @param buffer : Storage buffer for the text content of the message.
 * @param buf_lg : Size of the buffer.
 * @return 
 * - SMS_OK 
 * - SMS_ERR_GPRS_UNAVAILABLE 
 * - SMS_ERR_BAD_PARAMETER 
 * - SMS_ERR_DELETED 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 48) if function does not exist
 *
 * An example is available at @ref sub01_SMS  
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_read:KSFAM_GPRS:0x03
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int sms_read(SMS * sms_h, char * buffer, int buf_lg);


/*! @brief This function returns the information about a message.
 * @param sms_h : handle on the message to get information.
 * @param info : Storage structure for the message information.
 * @return 
 * - #SMS_OK or an negative error code.           
 * - #SMS_ERR_GPRS_UNAVAILABLE 
 * - #SMS_ERR_BAD_PARAMETER     
 * - #SMS_ERR_DELETED          
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 49) if function does not exist
 *
 * An example is available at @ref sub01_SMS  
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_get_info:KSFAM_GPRS:0x08
//  @GSIM_A:1:ONE_ADDRESS
//  @GSIM_A:2:ONE_POINTER
// \endif
int sms_get_info(SMS * sms_h, SMS_INFO * info);


/*! @brief This function deletes a message in the SIM card.
 * @param sms_h : handle on the message to delete.
 * @return 
 * - #SMS_OK or a negative error code :
 * - #SMS_ERR_GPRS_UNAVAILABLE  
 * - #SMS_ERR_BAD_PARAMETER    
 * - #SMS_ERR_UNKNOWN                 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 50) if function does not exist
 *
 * @note The message is deleted in the SIM card and it is not removed from the message list. Only its status is changed (marked as deleted). 
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_delete:KSFAM_GPRS:0x05
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int sms_delete(SMS * sms_h);


/*! @brief This function frees the message lists. 
 *
 * 	This function must be called to release all the resources allocated by the call to the function "sms_open".
 * @return 
 * - #SMS_ERR_GPRS_UNAVAILABLE 
 * - #SMS_OK 
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 52) if function does not exist
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_close:KSFAM_GPRS:0x02
// \endif
int sms_close(void);


/*! @brief This function returns information about the memory allocated for the messages. 
 *
 *	It returns the number of messages (complete and incomplete), the number of memory slots used to store the messages and the total number of memory slots of the SIM card. 
 * @param msg_nb : number of complete messages.
 * @param inc_msg_nb : number of incomplete messages.
 * @param slots_used : number of slots used to store the messages.
 * @param slots_total : number of slots the SIM card contains.
 * @return 
 * - #SMS_OK if OK.
 * - A negative error code (-1) otherwise.
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 53) if function does not exist
 * @note The pointer parameters can be NULL. In this case, the function does not affect its value. 
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_mem_info:KSFAM_GPRS:0x09
//  @GSIM_A:1:ONE_POINTER 
//  @GSIM_A:2:ONE_POINTER
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:4:ONE_POINTER
// \endif
int sms_mem_info(int * msg_nb, int * inc_msg_nb, int * slots_used, int * slots_total);


/*! @brief This function deletes all the incomplete messages contained in the SIM card and frees all the content of the incomplete list message. 
 * @return
 * - SMS_OK
 * - a negative error code.
 * @par exit (EXIT_DLL_GPRS_NOT_INITIALIZED + 51) if function does not exist
 *
 * @link KSFAM_SMS Back to top @endlink
*/
// \if SIMULATION
//  @GSIM_F:sms_purge_incomplete:KSFAM_GPRS:0x0C
// \endif
int sms_purge_incomplete(void);


#endif
/*! @} **/
