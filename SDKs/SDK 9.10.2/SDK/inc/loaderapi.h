#ifdef __cplusplus
extern "C" {
#endif

#ifndef __LOADER_API_H_INCLUDED__
#define __LOADER_API_H_INCLUDED__

#include "loaderapi_def.h"
#ifdef __FRAMEWORK_TELIUM_2__
#include "loaderapi_deprecated.h"
#endif

/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

// Services Handling 


/*! @brief This function can call a service.
 * @param serv_id : service identifier
 * @param data_size : Data size to be exchanged between application ( this is because there is no way to read from the caller due to firewalls ) .
 * @param data : Data address to be exchanged 
 * @param ret_code : Returned value from the called service 
 * @return
 * -1 --> Service does not exist
 * -2 --> Application does not exist
 * -3 --> Application is not loaded
 *  0 --> successful 
 *  1 --> no more resources to allocate a stack 
 *  4 --> MMU error
 *  5 --> task context error (not called by a task)
 * @note
 * - Data area to be exchanged between applications must be contiguous and does not contain any  pointer. 
 * - This area is used as an input or output from the service : the service provider may read or write into this data area. 
 *
 * @link KSFAM_M2OS Back to top @endlink
 */ 
int ServiceCall(unsigned int serv_id, unsigned int data_size, void* data, int *ret_code);

/*! @}  */ 


/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

/*! @brief This function records new services via a service descriptor in which is specified the number of services to be recorded and for each service : 
 *
 * - the routine address with a data transfert area as parameter.
 * - the priority of the service .
 * - the application number that provides the service .
 *
 * There is 2 prototypes allowed for servicies with 2 or 4 parameters. 
 *
 * @param num_of_serv : number of services in the service descriptor .
 * @param services : service descriptor .
 *
 * @return 
 * - 0 sucessfull .
 * - Non zero value otherwise.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int ServiceRegister(unsigned int num_of_serv, service_desc_t services[]);

/*! @}  */ 


/*! @addtogroup KSFAM_M2OS
	* @{
 */ 

/*! @brief This function checks the availability of a service and allow to read the service priority if it exists.
 * @param appli_id : application number 
 * @param serv_id : service number 
 * @param *priority : Service priority 
 * @return
 * - 0 sucessfull .
 * - Non zero value otherwise ( service does not exist ) .
 *
 * @link KSFAM_M2OS Back to top @endlink
 */ 
int ServiceGet(unsigned short appli_id, unsigned short serv_id,unsigned char *priority);


/*! @brief This function is used to remove a service.
 * @param appli_id : Application number.
 * @param serv_id : Service number to remove.
 * @param sap : Service entry point.
 * @param priority : Service priority.
 * @return
 * - 0 sucessfull .
 * - Non zero value otherwise ( service does not exist or bad parameters passing).
 *
 * @note The service is removed only if parameters num_appli, service, sap, priority correspond to the recorded service. 
 *
 * @link KSFAM_M2OS Back to top @endlink
 */ 
int ServiceRemove(unsigned short appli_id, unsigned short serv_id,
                  int (*sap)(unsigned int data_size, void*data),unsigned char priority);

/*! @}  */ 


#endif   // __LOADER_API_H_INCLUDED__

#ifdef __cplusplus
}
#endif
