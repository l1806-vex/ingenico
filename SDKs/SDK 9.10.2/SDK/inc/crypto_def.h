#ifdef __cplusplus
extern "C" {
#endif

#ifndef __CRYPTO_DEF_H_INCLUDED__
#define __CRYPTO_DEF_H_INCLUDED__

/*! @addtogroup KSFAM_OK
	* @{
 */ 

/*
======================================================================
					List of Defines
======================================================================
*/


//RSA key lengths
#define MIN_RSA_MODULUS_BITS  320				/*!< Minimum managed length (in bits) of the RSA  */
#ifndef RSA_1024_ONLY
#define MAX_RSA_MODULUS_BITS  2048			    /*!< Maximun managed length (in bits) of the RSA */
#else
#define MAX_RSA_MODULUS_BITS  1024			    /*!< Maximun managed length (in bits) of the RSA */
#endif
//#define EXT_RSA_MODULUS_BITS  1280
//#define EX2_RSA_MODULUS_BITS  2048

#define MAX_RSA_MODULUS_LEN   ((MAX_RSA_MODULUS_BITS + 7) / 8)		/*!< RSA modulus length in bytes for the 1024 or 2048 RSA, according to the compilation constant */
#define MAX_RSA_PRIME_BITS    ((MAX_RSA_MODULUS_BITS + 1) / 2)		/*!< RSA prime length in bits for the 1024 or 2048 RSA, according to the compilation constant */
#define MAX_RSA_PRIME_LEN     ((MAX_RSA_PRIME_BITS   + 7) / 8)		/*!< RSA prime length in bytes for the 1024 or 2048 RSA, according to the compilation constant */

//#define EXT_RSA_MODULUS_LEN   ((EXT_RSA_MODULUS_BITS + 7) / 8)
//#define EXT_RSA_PRIME_BITS    ((EXT_RSA_MODULUS_BITS + 1) / 2)
//#define EXT_RSA_PRIME_LEN     ((EXT_RSA_PRIME_BITS   + 7) / 8)

//#define EX2_RSA_MODULUS_LEN   ((EX2_RSA_MODULUS_BITS + 7) / 8)
//#define EX2_RSA_PRIME_BITS    ((EX2_RSA_MODULUS_BITS + 1) / 2)
//#define EX2_RSA_PRIME_LEN     ((EX2_RSA_PRIME_BITS   + 7) / 8)


//Maximum lengths of signatures, encrypted keys, encrypted signatures, and message digests.
#define DIGEST_SIZE           16			/*!< size of the MD5 hashing algorithm result */
#define RANDOM_BYTES_NEEDED   96			/*!< Internal Use only, for RSA key generation */
		
#define SHA_BLOCKSIZE         64			/*!< Size (in byte) of the unitary block for SHA-1 */
#define SHA_DIGESTSIZE        20			/*!< Size (in byte) of the result of SHA-1 */

// Definitions for iso9564 PinBloc format
#define CONTROL_FIELD_0       0x00		/*!< FORMAT 0 for ISO 9564 Pin block */
#define CONTROL_FIELD_1       0x10		/*!< FORMAT 1 for ISO 9564 Pin block  */
#define CONTROL_FIELD_2       0x20		/*!< FORMAT 2 for ISO 9564 Pin block  */


// Definitions for MKSK
#define MKSK_KS_SIMPLE       1		/*!< simple length key */
#define MKSK_KS_DOUBLE       2 		/*!< double length key */

// Definitions for AES
#define     AES_DIR_ENCRYPT         0     /* Are we encrpyting?  */
#define     AES_DIR_DECRYPT         1     /* Are we decrpyting?  */
#define     AES_MODE_ECB            1     /* Are we ciphering in ECB mode?   */
#define     AES_MODE_CBC            2     /* Are we ciphering in CBC mode?   */
#define     AES_MODE_CFB1           3     /* Are we ciphering in 1-bit CFB mode? */

#define	    BITSPERBLOCK            128   /*!< Default number of bits in a cipher block */
#define     MAX_KEY_SIZE            64   	/*!< # of ASCII char's needed to represent a key */
#define     MAX_IV_SIZE		 ((BITSPERBLOCK+7)/8)  /*!< # bytes needed to represent an IV */

// Definitions for RINJDAEL
#define MAXBC				(256/32)		/*!< Maximum block counter ?? */
#define MAXKC				(256/32)		/*!< Maximum key counter ?? */
#define MAXROUNDS			14				/*!< Maximum number of rounds to be performed ine AES function */
	

// Error codes
#define CR_RSA_OK             0  			/*!< RSA function performed OK */
#define CR_RSA_MESSAGE_LEN    (-100)		/*!< RSA message length incorrect */
#define CR_RSA_MODULUS_LEN    (-101)		/*!< RSA modulus length incorrect */
#define CR_RSA_RANDOM         (-102)		/*!< Not enough random number generated to perform an RSA key generation */
#define CR_RSA_GENKEY_EXP     (-103)		/*!< even RSA exponent asked for RSA key generation */
#define CR_RSA_KO             (-104) 		/*!< RSA function performed KO */

#define CR_DUKPT_OK           0				/*!< DUKPT function performed OK */
#define CR_DUKPT_END_LIFE     (-110)		/*!< Transaction counter to 0 */

#define CR_FORMAT_OK          0				/*!< iso9564 PinBloc format performed OK*/
#define CR_FORMAT_PIN_LEN     (-120)		/*!< PinBlock length incorrect */

#define CR_SHA_ASCOM_OK       0				/*!< SHA Ascom function performed OK */
#define CR_SHA_ASCOM_K0       (-130)		/*!< SHA Ascom function performed KO */
#define CR_SHA_ASCOM_LEN      (-131)		/*!< Input length too small */

#define CR_ISO9796_OK         0				/*!< ISO 9796 function performed OK */
#define CR_ISO9796_KO         (-140)		/*!< ISO 9796 function performed KO */

#define CR_MKSK_OK            0				/*!< MasterKey/SessionKey function performed OK */
#define CR_MKSK_KO            (-150)		/*!< MasterKey/SessionKey function performed KO */

#define CR_CERT_OK            0				/*!< Certificate controlled OK */
#define CR_CERT_KO_IS         (-160)  /*!< Issuer control ko */
#define CR_CERT_KO_PR         (-161)  /*!< Version Protocole repudiation Ko */
#define CR_CERT_KO_SIGN       (-162)  /*!< bad certificate signature */ 
#define CR_CERT_KO_AG_H       (-163)  /*!< hash algo doesn't exist */
#define CR_CERT_KO_KEY        (-164)  /*!< bad key number */
#define CR_CERT_KO_AG_S       (-165)  /*!< sign algo doesn't exist */
#define CR_CERT_KO_CRC        (-166)  /*!< Repudiation list KO */
#define CR_CERT_KO_DATE       (-167)  /*!< Validity date (month) is expired */ 
#define CR_CERT_KO_PTF        (-168)  /*!< bad hardware platform */ 

#define CR_SIGN_OK            0     	/*!< Signature controled OK */
#define CR_SIGN_KO            (-170)  /*!< bad APP or scheme signature */
#define CR_SIGN_KO_AG_S       (-171)  /*!< sign algo doesn't exist */
#define CR_SIGN_KO_AG_H       (-172)  /*!< hash algo doesn't exist */
#define CR_SIGN_KO_INFO       (-173)  /*!< bad Info value for ControlWithCurrent */ 

#define CR_KEY_OK             0       /*!< the public key to check the certificate is correct*/
#define CR_KEY_KO             (-180)  /*!< the key doesn't exist */
#define CR_KEY_REP            (-181)  /*!< the key is repudiate */

#define AES_OK                  0 		/*!< AES cypher Init performed OK */
#define AES_BAD_KEY_DIR         (-201)  /*!< Key direction is invalid, unknown value */
#define AES_BAD_KEY_MAT         (-202)  /*!< Key material not of correct length */
#define AES_BAD_KEY_INSTANCE    (-203)  /*!< Key passed is not valid  */
#define AES_BAD_CIPHER_MODE     (-204)  /*!< Params struct passed to cipherInit invalid */
#define AES_BAD_CIPHER_STATE    (-205)  /*!< Cipher in wrong state, not initialized */
#define AES_BAD_CIPHER_INSTANCE (-207) 

#define RIJNDAEL_OK             0			/*!< Rijndael function performed OK */
#define RIJNDAEL_BAD_SIZE       (-210)		/*!< Incorrect key size */
#define RIJNDAEL_BAD_BLOCK      (-211)		/*!< Incorrect block size*/
#define RIJNDAEL_BAD_KEY        (-212)		/*!< this cannot happen */
 

/* more return... */

/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Structure used for SHA-1 functions. */
typedef struct {
    unsigned long digest[5];            /*!< result of SHA-1 */
    unsigned long count_lo, count_hi;   /*!< internal data */
    unsigned long data[16];             /*!< internal data (input) */
} SHA_INFO;


/*! @brief Structure used to define the type of RSA key to generate. */
typedef struct {
  unsigned int bits;              /*!<  length in bits of modulus */
  int          publicExponent;    /*!<  impair value              */
} R_RSA_PROTO_KEY;



/*! @brief Structure used for Random Generation */
/*! @brief This structure has to be allocated by caller but is internally used by Random Generation */
typedef struct {
  unsigned int  bytesNeeded;				/*!< internal field */
  unsigned char state[DIGEST_SIZE];			/*!< internal field */
  unsigned int  outputAvailable;			/*!< internal field */
  unsigned char output[DIGEST_SIZE];		/*!< internal field */
} R_RANDOM_STRUCT;



/*! @brief Structure used for a 1024 or 2048 (according to the RSA_1024_ONLY compilation constante) bits RSA public key */
typedef struct {
  unsigned int  bits;                          	 /*!< length in bits of modulus */
  unsigned char modulus[MAX_RSA_MODULUS_LEN];    /*!< modulus */
  unsigned char exponent[MAX_RSA_MODULUS_LEN];   /*!< public exponent */
} R_RSA_PUBLIC_KEY;


/*! @brief Structure used for a 1024 or 2048 (according to the RSA_1024_ONLY compilation constante) bits RSA private key */
typedef struct {
  unsigned int  bits;                          			/*!< length in bits of modulus */
  unsigned char modulus[MAX_RSA_MODULUS_LEN];           /*!< modulus */
  unsigned char publicExponent[MAX_RSA_MODULUS_LEN];    /*!<  public exponent */
  unsigned char prime[2][MAX_RSA_PRIME_LEN];            /*!< prime factors */
  unsigned char primeExponent[2][MAX_RSA_PRIME_LEN];    /*!< exponents for CRT */
  unsigned char coefficient[MAX_RSA_PRIME_LEN];         /*!< CRT coefficient */
} R_RSA_PRIVATE_KEY;



/*! @brief Structure used for the input data of RSA functions. */
typedef struct {
  unsigned int   inputLen;			/*!< length of the data to cypher/decypher */
  unsigned char *input; 			/*!< pointer to the data to cypher/decypher */
} R_RSA_INPUT;


/*! @brief Structure used for the output data of RSA functions. */
typedef struct {
  unsigned int  *outputLen;			/*!< length of the data cyphered/decyphered */
  unsigned char *output; 			/*!< pointer to the result of the cyphering/decyphering */
} R_RSA_OUTPUT;




/*! @brief Structure used to describe an AES key. */
typedef struct {
      unsigned char direction;	                     /*  Key used for encrypting or decrypting? */
      int           keyLen;	                         /*!<  Length of the key  */
      char          keyMaterial[MAX_KEY_SIZE+1];     /*!<  Raw key data in ASCII, user input or KAT values */
      int           blockLen;                        /*!<  block length */
      unsigned char keySched[MAXROUNDS+1][4][MAXBC]; /*!<  key schedule		*/
} T_AES_KEY_INSTANCE; 


/*! @brief Structure used to describe the type of AES to perform */
typedef struct {
      unsigned char mode;                /*!< MODE_ECB, MODE_CBC, or MODE_CFB1 */
      unsigned char IV[MAX_IV_SIZE];     /*!< A possible Initialization Vector for ciphering */
      int           blockLen;    	 	 /*!< Sample: Handles non-128 bit block sizes (if available) */
} T_AES_CIPHER_INSTANCE;     


/*! @brief Structure used for the input data of DES functions. */
typedef struct {
      int           InputLen;		/*!< length of the data to cypher/decypher */
      unsigned char *Input;			/*!< pointer to the data to cypher/decypher */
} T_DES_INPUT;


/*! @brief Structure used for the input of the iso9564 PinBloc format. */
typedef struct {
      unsigned char *PinText;		/*!< pointer to the pincode that will be ISO9564PinBlocked */
      unsigned char PinLen;			/*!< Length of the Pincode */
} T_ISO9564_INPUT;


/*! @brief Structure used to describe a MasterKey SessionKey  key. */
typedef struct {
      unsigned char *Km; 				/*!< pointer to Master key */
      unsigned char *Kk; 				/*!< pointer to key encryption  */
      unsigned char *Ks; 				/*!< pointer to Session key */
      int           TypeKey;		    /*!< MKSK_KS_SIMPLE or MKSK_KS_DOUBLE */
} T_MKSK_KEY;


/*! @brief Structure used to describe a simple DES DUKPT key. */
typedef struct
{
	  unsigned char  Key[8];			/*!< DUKPT key */
	  unsigned short Check;				/*!< key already used or not */
} T_DUKPT_KEY;


/*! @brief Structure used to describe a triple DES DUKPT key. */
typedef struct
{
	  unsigned char  Key[16];			/*!< DUKPT key */
	  unsigned short Check;				/*!< key already used or not */
} T_DUKPT_TDES_KEY;


/*! @brief Structure used to describe the output of the DUKPT function. */
typedef struct {
      unsigned char *TransactionSmid;		/*!< pointer to the Smid (8 bytes), ie the terminal serial number + transaction counter */
      unsigned char *MacKey;				/*!< pointer to the output Mac Key(16 bytes) */
} T_DUKPT_OUTPUT;


/*! @brief Structure used for the input of the AES functions. */
typedef struct {
      int           InputLen;		/*!< length of the data cyphered/decyphered */
      unsigned char *Input;			/*!< pointer to the data to cypher/decypher */
      int           Rounds;			/*!< rounds number */
} T_AES_INPUT;


/*! @brief unsigned integer 16 bits. */    
typedef unsigned short int UINT2;

/*! @brief unsigned integer 32 bits. */
typedef unsigned long  int UINT4;		


typedef struct {
  UINT4 state[4];                /*!< state (ABCD) */
  UINT4 count[2];                /*!< number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];      /*!< input buffer */
} MD5_CTX;

/*! @}  */ 


#endif   // __CRYPTO_DEF_H_INCLUDED__

#ifdef __cplusplus
}
#endif
