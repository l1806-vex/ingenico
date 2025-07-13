/*! @addtogroup KSFAM_DEPRECATED
	* @{
**/
#ifndef DEPREC_H
#define DEPREC_H

#ifdef _DEPRECATED_SDK71_

/*! @brief This function is obsolete. 
 *
 *	This routine performs a loading of DLL crypto into RAM memory.
 *  @deprecated Since the SDK 5.6.1 this loading is done when calling the first crypto Api by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern int InitDLLSaisiePpad (void);


/*! @brief This function is obsolete. 
 *
 *	use int   InitSysSaisiePpad        (void);
 *
 *  @deprecated Since the SDK 5.6.1 it is is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern int InitSysPpad (int);

/*! @brief emvsqlib_open opens library emvsqlib.
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void emvsqlib_open(void);


/*! @brief Opens the extenslib librairy
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void extenslib_open(void);



/*! @brief Opens the libgrlib library.
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void libgrlib_open(void);



/*! @brief saisielib_open Opens the library saisielib
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void saisielib_open(void);



/*! @brief paramlib_open Opens the library paramlib.
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void paramlib_open(void);



/*! @brief svlib_open opens the library svlib
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void svlib_open(void);




/*! @brief dllpsclib_open Opens the library dllpsclib
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void dllpsclib_open(void);



/*! @brief pinpadlib_open Opens the library pinpadlib
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void pinpadlib_open(void);


/*! @brief Opens the languelib librairy
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void languelib_open(void);




/*! @brief protocolelib_open  Opens thelibrary protocolelib
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void protocolelib_open(void);



/*! @brief cb2alib_open Opens the library cb2alib.
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void cb2alib_open(void);



/*! @brief iamlib_open Opens the library iamlib.
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void iamlib_open(void);




/*! @brief partagelib_open Opens the library partagelib.
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void partagelib_open(void);

/*! @brief Crypto_Dll_Open Opens the library crypto.
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern int Crypto_Dll_Open(void);

/*! @brief sdklib_open Opens the SDK libraries.
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void sdklib_open(void);

/*! @brief hwcnflib_open opens the library hardware configuration.
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void hwcnflib_open(void);


/*! @brief umslib_open opens the library umslib.
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void umslib_open(void);


/*! @brief colorlib_open opens the colorlib library.
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void colorlib_open(void);


/*! @brief This function opens the library gprslib.
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void gprslib_open(void);

/*! @brief This function is used to link application to DLL crypto
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 *	This routine load DLL into RAM if necessary and initialize all functions pointers. 
 * @return Returns : 
 * - DLL_OK if successfull
 * - result of ObjectLoad function if not successfull (see loaderapi.h) 
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
int  Crypto_Dll_Open    (void);

/*! @brief This function is used to unlink application to DLL crypto
 *  @deprecated Since the SDK 5.6.1 this loading is done with the first call to this library by the application, so it is not necessary to call this function.  
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 *	DLL was previously loaded with Crypto_Dll_Open
 *	This routine remove DLL from RAM if necessary
 * @return None
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
void Crypto_Dll_Close   (void);

/*! @brief Display the amount.
*	@param montant : amount.
*	@param devise : currency.
*	@return None (void).
*
 *  @deprecated This function is obsolete, to continue to use it, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void USQ_Aff_montant (unsigned long * montant ,S_MONEY * devise);


extern int           PSQ_Est_double90 (void);
extern unsigned char PSQ_Double90_cle ( void );

/*! @brief Returns the m2OS version
*	
*	@deprecated This function is replaced by:
*   - ObjectGetNumber(object_type_t type);
*   - ObjectGetInfo(object_type_t	object_type, unsigned int	num_obj, object_info_t*	info);
*
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern void ET_Idf_seq (T_VERSION  version,NO_SEGMENT *noseg,CHECKSUM   *nochecksum);


/*! @brief Returns if the flag loaded_flag is equal to 1
*	
*	@deprecated This function is replaced by:
*   - ObjectGetInfo(object_type_t	object_type, unsigned int	num_obj, object_info_t*	info);
*	- and test info.loaded_flag
*
 *  However, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
 * @link KSFAM_DEPRECATED Back to top @endlink
*/
extern int is_loaded(NO_SEGMENT    i);


/*! @brief This function must not be used by application
*
 *  @deprecated For compatibility purpose only, if you want to continue to use this function, you have to add the compilation directive _DEPRECATED_SDK71_
 *
*/
extern int InitModeGraphique(int Periph);

#endif



#endif
/*! @} **/

