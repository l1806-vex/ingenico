/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

#ifndef _LOADER_API_H_
#define _LOADER_API_H_


/*
======================================================================
					List of Defines
======================================================================
*/

/*! @brief Max number of object allowed. */
#define NUMBER_OF_DLL        64  /*!< max number of DLL */
#define NUMBER_OF_DRV        64  /*!< max number of Drivers */
#define NUMBER_OF_PARAM_FILE 64  /*!< max number of Parameter files */
#define NUMBER_OF_APPLI      38  /*!< max number of Applications */
#define NUMBER_OF_KEY_FILE   16  /*!< max number of Key files */


/*
======================================================================
			Data Structures Definition
======================================================================
*/

#define SERVICE_CALL_INTERFACE_VERSION  0x00000001  /*!< Current version of SERVICE_CALL_PARAM structure */

/*! @brief Defines System parameters for Service Call. */
typedef struct {
  unsigned int version;										/*!< version of this structure */
  unsigned int caller_application_type; 	/*!< Application type (identifier) of calling application.
                                               This field is present for version>=1 */  
  /*!< WARNING : field may be added in this structure in future releases of Telium System. */
} SERVICE_CALL_PARAM;


/*! @brief Defines a service access point.*/
typedef int (*SAP) (unsigned int data_size, 		 			    /*!< Mandatory : Data size to be exchanged between application ( this is because there is no way to read from the caller due to firewalls )  */
                    void *data);                     	    /*!< Mandatory : Data address to be exchanged */
                    
typedef int (*SAP4)(unsigned int data_size, 		 			    /*!< Mandatory : Data size to be exchanged between application ( this is because there is no way to read from the caller due to firewalls )  */
                    void *data,                      	    /*!< Mandatory : Data address to be exchanged */
                    unsigned int sys_param_size, 		   	  /*!< Optional  : Size of system parameters. Zero if service parameters are not provided by Telium System */
                    SERVICE_CALL_PARAM *serv_call_param); /*!< Optional  : System parameters. NULL if service parameters are not provided by Telium System */
																															
/*! @brief In the service descriptor type is specified the number of services to be recorded and for each service : 
*
* - the routine address with a data  transfert area as parameter
* - the priority of the service
* - the application number that provides the service*/
typedef struct {
   unsigned short appli_id;						/*!< application type */
   unsigned short serv_id;						/*!< service number */
   SAP            sap;	              /*!< service entry point */
   unsigned char priority;						/*!< service priority  */
}service_desc_t;



/*! @brief Define the object (application, DLL, driver, param, key) type. 
* object are executable or data signed files.
* Corresponding file extension are :
* - Application : SGN+ADF for Telium I / AGN for Telium II 
* - DLL         : SGN+LDF for Telium I / LGN for Telium II 
* - Driver      : SGN+DDF for Telium I / DGN for Telium II 
* - Parameter   : SGN+PDF for Telium I / DGN for Telium II 
* - Key file    :                      / KGN for Telium II 
*/
typedef enum {
	OBJECT_TYPE_APPLI	 = 1,		/*!< Application object */
	OBJECT_TYPE_DLL	   = 2,		/*!< Dynamicaly Linked Library object */
	OBJECT_TYPE_DRIVER = 3,		/*!< System driver object */
	OBJECT_TYPE_PARAM  = 4,		/*!< Parameter file */
	OBJECT_TYPE_KEY    = 5		/*!< Key file */
} object_type_t;


#define OBJECT_NAME_LEN        20		/*!< Max length of obect name (application family) */
#define OBJECT_FILE_NAME_LEN   20		/*!< Max length of file name */


/*! @brief This type contains the information about the object. */
typedef struct {
	char	name[OBJECT_NAME_LEN];								/*!< Object name (application family given at generation time ) */
	char	file_name[OBJECT_FILE_NAME_LEN];			/*!< Binary file */

#ifdef _SIMULPC_
	unsigned short	object_type;								/*!< object type (application, DLL, driver, param) */
#else
	object_type_t	object_type;									/*!< object type (application, DLL, driver, param) */
#endif
	unsigned short	application_type;						/*!< Application type given at generation time */
	unsigned short	crc;												/*!< CRC */
	unsigned int	memory_size;									/*!< Memory needed to download (code + data) in bytes */
	unsigned char	loaded_flag;									/*!< 1 if the object is already loaded in RAM 0 otherwise */
	unsigned char	loader_type;									/*!< Local downloading or remote downloading */
	unsigned char	first_exec;										/*!< 1 if first execution, 0 otherwise */
} object_info_t;


#define FILE_NAME_LEN        15								/*!< Max length of file name */
#define APPLI_FAMILY_LEN     16								/*!< Max length of obect name (application family) */


/*! @brief  This type contains detailled informations about object. */
typedef struct object_descriptor_t { 
   unsigned int   zip_file_size;					/*!< size of the ZIP file */
   unsigned int   code_size;							/*!< size of the code */
   unsigned int   data_size;							/*!< size of the data */
   unsigned int   code_adr;								/*!< address of the code */
   unsigned int   data_adr;								/*!< address of the data */
   int            loader_status;					/*!< status of the loader */
   unsigned short appli_type;							/*!< type of the application */
   unsigned short crc;										/*!< CRC */
   unsigned char  file_type ;							/*!< type of the file */
   unsigned char  file_name[FILE_NAME_LEN+1];					/*!< name of the file */
   unsigned char  appli_family[APPLI_FAMILY_LEN+1];		/*!< family of the application  */
   unsigned char  compressing;												/*!< compressing or not. */ 
   unsigned char  crc_ctrl;														/*!< control CRC */
   unsigned char  loader_type;												/*!< local downloading or remote downloading */
   unsigned char  first_exec;													/*!< 1 if first execution, 0 otherwise */
   unsigned char  loaded;															/*!< loaded or not. (1/0) */
}object_descriptor_t ;



/*! @brief This type contains informations about object RAM and flash usage.*/
typedef struct {
   unsigned int code_size;              /*!< object code size (bytes) */
   unsigned int data_size;              /*!< object data size (bytes) */
   unsigned int page_alloc_size;        /*!< object PageAlloc size (bytes) */
   unsigned int umalloc_size;           /*!< object umalloc size (bytes) */  
   unsigned int dllmalloc_size;         /*!< object dllmalloc size (bytes)  */
   unsigned int usr_stacks_nbr;         /*!< number of user stacks */
   unsigned int usr_stacks_size;        /*!< size of user stacks */
   unsigned int svc_stacks_nbr;         /*!< number of supervisor stacks */
   unsigned int svc_stacks_size;        /*!< size of supervisor stacks */
   unsigned int total_ram;   		        /*!< total RAM used */
   unsigned int flash_prog;             /*!< flash used space for code (SYSTEM disk) */
   unsigned int flash_data;             /*!< flash used space for data (created disks)    */
} object_size_t;



/*! @brief This type enumerates all the possible access levels for PageProtect(). */
typedef enum {
  PAGE_NO_ACCESS  = 0,			/*!< No access allowed */
  PAGE_READ_ONLY  = 1,			/*!< Read only allowed */
  PAGE_READ_WRITE = 2				/*!< Read and write access allowed */
}access_t;



/*! @brief This type enumerates all the possible values for ObjectSeek orgin parameter. */
typedef enum {
  OBJ_SEEK_SET  = 0,			/*!< Seek into object data from beginning */
  OBJ_SEEK_CUR  = 1,			/*!< Seek into object data from current position  */
  OBJ_SEEK_END  = 2				/*!< Seek into object data from end */
}object_seek_t;


//ObjectUnload return codes 
#define OL_OBJECT_NOT_FIND     1		/*!< Specified object had not been found */
#define OL_NOT_LOADED          2		/*!< Specified object is not loaded into dynamic memory */
#define OL_UNLOAD_ERROR        3		/*!< ObjectUnload has not succeed to unload specified object */

// Object Handling 


/*
======================================================================
			Functions Definition
======================================================================
*/

/*! @brief This function returns the object number available for a given object type. 
 * 
 * It should replace the num_seg routine that has been only kept for compatibility purpose. 
 * @param type : object type (application or DLL) .
 * @return Objects number available
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectGetNumber:KSFAM_IOSF:
// \endif
int ObjectGetNumber(object_type_t type) ;



/*! @brief This function allows to get information about the object ( i.e an application ).
 *
 * It should replace the info_seg routine that has been only kept for compatibility purpose.
 * @param object_type : object type (application or DLL).
 * @param num_obj : object number for a given object type between 0 and objects number -1 
 * @param info : object_info_t structure.
 * @return 
 * - code 0 if successfull.
 * - non zero value otherwise.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectGetInfo:KSFAM_IOSF:
//  @GSIM_A:1:IN_ONLY
//  @GSIM_A:3:ONE_POINTER
//  @GSIM_A:3:OUT_ONLY
// \endif
int ObjectGetInfo(object_type_t	object_type, unsigned int	num_obj, object_info_t*	info);



/*! @brief This function loads an object in RAM (application or DLL)
 * @param object_type : Type of object (application or DLL).
 * @param name : Name of the object (application family).
 * @return 
 * - 0 if no error. Else :
 * - 1 : object not found
 * - 2 : no more Domain available
 * - 3 : no enough memory
 * - 4 : Data address if wrong
 * - 5 : Code address is wrong
 * - 6 : already loaded
 * - 7 : Out of allowed area (DLL)
 * - 8 : address conflict
 * - 9 : bad CRC
 * - 10 : bad code length
 * - 11 : Corresponding file of specified object has not been found 
 * - 12 : Type of the specified object is unknown 
 * - 13 : Authentication of the specified object had fail 
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectLoad:KSFAM_IOSF:
// \endif
int ObjectLoad(object_type_t	object_type,char	*name	) ;



/*! @brief This function unloads an object from RAM (application or DLL)
 * @param object_type : Type of object (application or DLL).
 * @param name : Name of the object (application family).
 * @return 
 * - 0 if no error. Else :
 * - 1: object not found
 * - 2: object is not loaded
 * - 3: internal unloader error
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectUnLoad:KSFAM_IOSF:
// \endif
int ObjectUnLoad(object_type_t object_type,char *name );

/*! @brief This function is used to reset the "First Exececution" flag (first_exec)
 * @param type : Type of object (application or DLL...).
 * @param num_obj : object identifer.
 * @param value : half byte to write (Telium I only).
 * @return 
 * - 0 if no error. Else :
 * - 1: object not found
 * - 2: object is not loaded
 * - 3: internal unloader error
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectWriteInfo:KSFAM_IOSF:
// \endif
int ObjectWriteInfo(object_type_t type,unsigned int num_obj, char value) ;


/*! @brief This function retrieves description of an object present in active directory ('SYSTEM').
 * @param object_type : object Type : 
 * - OBJECT_TYPE_APPLI	 : Application object 
 * - OBJECT_TYPE_DLL	   : Dynamicaly Linked Library object 
 * - OBJECT_TYPE_DRIVER : System driver object 
 * - OBJECT_TYPE_PARAM  : Parameter file 
 * - OBJECT_TYPE_KEY    : Key file 
 * @param application_type : application type.
 * @param desc : pointer to object_descriptor_t structure.
 * @return
 * - 0 if no error. Else :
 * - -1 if object has not been found.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectGetDescriptor:KSFAM_IOSF:
//  @GSIM_A:3:ONE_POINTER
// \endif
int ObjectGetDescriptor(object_type_t	object_type, unsigned short application_type, object_descriptor_t*	desc);




/*! @brief This function retrieves memory information of an object present in active directory ('SYSTEM').
 * @param object_type : object Type (application or DLL).
 * @param application_type : application type.
 * @param desc_size : size of structure object_size_t (for future structure use).
 * @param desc : pointer to object_size_t structure.
 * @return 0 if no error.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectGetSize:KSFAM_IOSF:
//  @GSIM_A:4:ONE_POINTER
// \endif
int ObjectGetSize(object_type_t	object_type, unsigned short application_type, unsigned int desc_size, object_size_t*	desc);



/*! @brief This function removes all objects of a specified family name : APPLI+DLL+PARAM
 * @param name : DLL family name
 * @return 0 if no error.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectRemoveByFamily:KSFAM_IOSF:
// \endif
int ObjectRemoveByFamily(const char* name);



/*! @brief This function reads data from object.
 * @param buffer : pointer to area to store data.
 * @param size : size of element to read.
 * @param element_nbr : Number of elements to read.
 * @param fd : pointer to File handle returned by ObjectOpen. 
 * @return Number of read elements
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectRead:KSFAM_IOSF:
//  @GSIM_A:1:DATA_CODE(size*element_nbr)
//  @GSIM_A:4:ONE_ADDRESS
// \endif
int ObjectRead(void *buffer, int size, int element_nbr, void *fd);



/*! @brief This routine closes object.
 * @param fd : pointer to File handle returned by ObjectOpen.
 * @return None.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectClose:KSFAM_IOSF:
//  @GSIM_A:1:ONE_ADDRESS
// \endif
void ObjectClose(void *fd);



/*! @brief This function opens object for read.
 * @param obj : pointer to Object descriptor.
 * @return 
 * - File handle.
 * - NULL if error.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectOpen:KSFAM_IOSF:
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:1:ONE_POINTER
// \endif
void* ObjectOpen(object_descriptor_t *obj);


/*! @brief This function is used to remove an object form SYSTEM disk
 * @param object_type : Type of object (application or DLL...).
 * @param application_type : application type.
 * @return 
 * - 0 if no error. Else :
 * - 1: object not found
 * - 2: object is not loaded
 * - 3: internal unloader error
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectRemove:KSFAM_IOSF:
// \endif
int ObjectRemove(object_type_t object_type, unsigned short application_type);

//	Applications Handling 


/*! @brief This function retrieves your application number at the boot time.
 *
 * The returned value corresponds to the obj_num parameter of ObjectGetInfo routine and may change after a reset.
 * @return application number as an integer.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ApplicationGetCurrent:KSFAM_IOSF:
// \endif
int ApplicationGetCurrent(void) ;


/*! @brief This function retrieves your application type.
 *
 * The returned value corresponds to the application type of the current application.
 * @return application type.
 *
 * @note ApplicationGetCurrentAppliType is suppoted by Telium System only if info_seg_SE returns a value > SWI_ApplicationGetCurrentAppliType.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
unsigned short ApplicationGetCurrentAppliType(void);
#define SWI_ApplicationGetCurrentAppliType     373		/*!< ApplicationGetCurrentAppliType SWI number */

/*! @}  */ 


/*! @addtogroup KSFAM_OS
	* @{
 */ 


// Utilities 


/*! @brief This function returns the available RAM usable for all the applications. 
 * @return Available memory (in bytes).
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:FreeSpace:KSFAM_OS:
// \endif
unsigned long FreeSpace(void) ;


/*! @brief This function returns RAM size in bytes. 
 * @return RAM memory size (in bytes).
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:RamGetSize:KSFAM_OS:
// \endif
unsigned int RamGetSize( void );

/*! @}  */ 


/*! @addtogroup KSFAM_M2OS
	* @{
 */ 


// Services Handling 


/*! @brief This function can call a service.
 * @param serv_id : service identifier
 * @param data_size : Data size to be exchanged between application ( this is because there is no way to read from the caller due to firewalls ) .
 * @param data : Data address to be exchanged 
 * @param ret_code : Returned value from the called service 
 * @return
 * - 0 : successful 
 * - 5 : task context error 
 * - 1 : no more resources to allocate a stack 
 * @note
 * - Data area to be exchanged between applications must be contiguous and does not contain any  pointer. 
 * - This area is used as an input or output from the service : the service provider may read or write into this data area. 
 *
 * @link KSFAM_M2OS Back to top @endlink
 */ 
// \if SIMULATION
//  :ServiceCall:KSFAM_M2OS:
//  :3:DATA_SIZE(data_size)
//  :4:ONE_POINTER
// \endif
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
// \if SIMULATION
//  @GSIM_F:ServiceRegister:KSFAM_IOSF:
//  @GSIM_S:ServiceRegister:E_ServiceRegister
// \endif
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
// \if SIMULATION
//  @GSIM_F:ServiceGet:KSFAM_M2OS:
//  @GSIM_A:3:ONE_POINTER
// \endif
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
// \if SIMULATION
//  @GSIM_F:ServiceRemove:KSFAM_M2OS:
//  @GSIM_S:ServiceRemove:E_ServiceRemove
// \endif
int ServiceRemove(unsigned short appli_id, unsigned short serv_id,
                  int (*sap)(unsigned int data_size, void*data),unsigned char priority);

/*! @}  */ 


/*! @addtogroup KSFAM_IOSF
	* @{
 */ 


// DLL Management 


/*! @brief This function returns a pointer to the 'GetProcAddress' function of the specified DLL name. 
 *
 * This routine allows to make a link between a string representing the function name to the function itself (i.e a function pointer ).
 * @param name : Name of descriptor file of the DLL .
 * @return 
 * - Pointer of the 'GetProcAddress' DLL routine if DllLink has been executed successfully .
 * - Null pointer otherwise. 
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:DllLink:KSFAM_IOSF:
//  @GSIM_A:0:ONE_ADDRESS
// \endif
void *DllLink(char *name);



/*! @brief This function returns a pointer to the 'GetProcAddress' function of the specified DLL. 
 *
 * This routine allows to make a link between a string representing the function name to the function itself (i.e a function pointer ).
 * @param application_type : application type.
 * @return 
 * - Pointer of the 'GetProcAddress' DLL routine if DllLink has been executed successfully .
 * - Null pointer otherwise. 
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:DllLinkByType:KSFAM_IOSF:
// \endif
void *DllLinkByType(unsigned short application_type);


/*! @brief This function returns the identifier of the entity that builds ( generates ) the DLL.
 * @param name : Name of descriptor file of the DLL.
 * @param id   : DLL Identifier Id.
 * @return 
 * - 0 if successful 
 * - Non zero value otherwise 
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:DllGetId:KSFAM_IOSF:
//  @GSIM_A:2:ONE_POINTER
// \endif
int DllGetId(char *name,int *id);


/*! @brief This function releases the link with the DLL specified. 
 * 
 * Memory space allocated to the DLL can only be physically released if there is no more link open with an application. 
 * @param name : Name of descriptor file of the DLL .
 * @return 
 * - 0  if the count has reached zero, DLL is unloaded, 
 * - >0 link count number after operation (just decremented but DLL still in memory )
 * - -1 if bad desc or Dll not loaded
 *
 * @note 
 * - Each DLL has a link counter by application. 
 * - It is increased when DllLink is called, and decreased when Dllunlink is called. 
 * - When all counters reach zero, the DLL is unload
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:DllUnlink:KSFAM_IOSF:
// \endif
int DllUnlink(char *name);


/*! @brief This function releases the link with the DLL specified. 
 *
 * Memory space allocated to the DLL can only be physically released if there is no more link open with an application. 
 * @param application_type : application type.
 * @return 
 * - 0  if the count has reached zero, DLL is unloaded, 
 * - >0 link count number after operation (just decremented but DLL still in memory )
 * - -1 if bad desc or Dll not loaded
 *
 * @note 
 * - Each DLL has a link counter by application. 
 * - It is increased when DllLink is called, and decreased when Dllunlink is called. 
 * - When all counters reach zero, the DLL is unload
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:DllUnlinkByType:KSFAM_IOSF:
// \endif
int DllUnlinkByType(unsigned short application_type);

/*! @}  */ 





/*! @addtogroup KSFAM_OS
	* @{
 */ 


// Page management


/*! @brief This function is used to allocate a secured memory space. 32 allocations maximum can be done within an application.
 * @param size : Number of bytes , 4 Kb as a minimum , 128Kb as a maximum 
 * @return Pointer to the allocated page if successfull. Null pointer otherwise.
 * @note The allocated memory area is not accessible for other applications. 
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:PageAlloc:KSFAM_OS:
//  @GSIM_S:PageAlloc:E_PageAlloc
// \endif
void* PageAlloc (unsigned int	size) ;



/*! @brief This function releases a previously allocated page.
 * @param page : Page Address .
 * @return 
 * - 0 if successfull.
 * - 4 if bad pointer.
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:PageFree:KSFAM_OS:
//  @GSIM_S:PageFree:E_PageFree
// \endif
int PageFree (void *page) ;



/*! @brief This function modifies the access rights of a secured memory allocated page.
 * @param page : Page address allocated by PageAlloc
 * @param access : access rights : 
 * - PAGE_READ_ONLY 
 * - PAGE_READ_WRITE 
 * - PAGE_NO_ACCESS 
 *
 * @return
 * - 0 if successfull. 
 * - Non zero value otherwise. 4 : bad pointer .
 *
 * @note An application can modify the access rights of a page only if this one belongs to the same secured context. 
 *
 * @link KSFAM_OS Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:PageProtect:KSFAM_OS:
//  @GSIM_S:PageProtect:E_PageProtect
// \endif
int PageProtect (void*	page, access_t	access) ;


// ObjectLoad return codes 
//#define OL_OBJECT_NOT_FIND     1		/*!< Specified object had not been found */
#define OL_NO_DOMAIN_FREE      2		/*!< There is no free domain to load specified object */
#define OL_OUT_OF_MEM          3		/*!< There is no free memory to load specified object */
#define OL_BAD_DATA_ADR        4		/*!< Data address range of specified object is not correct */
#define OL_BAD_CODE_ADR        5		/*!< Code address range of specified object is not correct */
#define OL_ALREADY_LOADED      6		/*!< Specified object is already loaded */
#define OL_OUT_OF_ALLOWED_AREA 7		/*!< Code or data of specified object is out of range */
#define OL_ADDRESS_CONFICT     8		/*!< There is a conflict with an other object loaded in memory */
#define OL_BAD_CRC             9		/*!< Crc of specified object is not correct */
#define OL_BAD_CODE_LEN        10		/*!< Code langth of specified object is not correct */
#define OL_FILE_NOT_FOUND      11		/*!< Corresponding file of specified object has not been found */
#define OL_BAD_OBJECT_TYPE     12		/*!< Type of the specified object is unknown */
#define OL_FILE_BAD_SIG        13 	/*!< Authentication of the specified object has failled */
#define OL_FILE_BAD_WORLD      14 	/*!< Specified object cannot be loaded using current key file */
#define OL_BAD_PARAM           15 	/*!< Specified parameter is not correct */


/*! @}  */ 


/*! @addtogroup KSFAM_IOSF
	* @{
 */ 

/*! @brief This function opens object for read.
 * @param obj : pointer to Object descriptor.
 * @return 
 * - File handle.
 * - NULL if error.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectOpen:KSFAM_IOSF:
//  @GSIM_A:0:ONE_ADDRESS
//  @GSIM_A:1:ONE_POINTER
// \endif
void* ObjectOpen(object_descriptor_t *obj);


/*! @brief This routine closes object.
 * @param fd : pointer to File handle returned by ObjectOpen.
 * @return None.
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectClose:KSFAM_IOSF:
//  @GSIM_A:1:ONE_ADDRESS
// \endif
void ObjectClose(void *fd);


/*! @brief This function reads data from object. Header and signature could not be read using this function.
 * @param buffer : pointer to area to store data.
 * @param size : size of element to read.
 * @param element_nbr : Number of elements to read.
 * @param fd : pointer to handle returned by ObjectOpen. 
 * @return 
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectRead:KSFAM_IOSF:
//  @GSIM_A:1:DATA_CODE(size*element_nbr)
//  @GSIM_A:4:ONE_ADDRESS
// \endif
int ObjectRead(void *buffer, int size, int element_nbr, void *fd);


/*! @brief  This function changes current offset when reading an object.
 * @param fd     : file object descriptor
 * @param offset : new file object position
 * @param whence : offset origin
 * @return 0 if OK
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectSeek:KSFAM_IOSF:
//  @GSIM_A:1:ONE_ADDRESS
// \endif
int ObjectSeek(void *fd, long offset, object_seek_t whence);


/*! @brief  This function is used to get object position
 * @param fd : file object descriptor
 * @return offset in fil
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectTell:KSFAM_IOSF:
//  @GSIM_A:1:ONE_ADDRESS
// \endif
unsigned long ObjectTell(void *fd) ;


/*! @brief This function loads an object in RAM (application or DLL)
 * @param object_type : Type of object (application or DLL).
 * @param application_type : application type.
 * @return 
 * - 0 if no error. Else :
 * - 1 : object not found
 * - 2 : no more Domain available
 * - 3 : no enough memory
 * - 4 : Data address if wrong
 * - 5 : Code address is wrong
 * - 6 : already loaded
 * - 7 : Out of allowed area (DLL)
 * - 8 : address conflict
 * - 9 : bad CRC
 * - 10 : bad code length
 * - 11 : Corresponding file of specified object has not been found 
 * - 12 : Type of the specified object is unknown 
 * - 13 : Authentication of the specified object had fail 
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
// \if SIMULATION
//  @GSIM_F:ObjectLoadType:KSFAM_IOSF:
// \endif
int ObjectLoadType(object_type_t object_type, unsigned short application_type );

/*! @brief This function loads an object in RAM (uncompressing it)
 * @param buffer : pointer to area to store data.
 * @param size : buffer size in bytes. Must be large enough to receive full uncompressed object.
 * @param fd : pointer to handle returned by ObjectOpen.
 * @return 
 * - 0 if no error. Else :
 * - 1 : object not found
 * - 3 : no enough memory
 * - 9 : bad CRC
 * - 10 : bad code length
 * - 11 : Corresponding file of specified object has not been found 
 * - 15 : bad parameter 
 *
 * @link KSFAM_IOSF Back to top @endlink
 */ 
int ObjectUnzip(void *buffer, int size, void *obj_fd);


#endif

/*! @}  */ 
