/*! @addtogroup KSFAM_OS_NET
 * @{
 */ 

#ifndef MIB_SNMP_H
#define MIB_SNMP_H

/*
======================================================================
			List of Defines
======================================================================
*/

#define SNMP_EOK                0               /*!< No error */
#define SNMP_EINVAL             -26             /*!< Invalid argument */
#define SNMP_ENOENT             -41             /*!< No such file or directory */
#define SNMP_EPERM              -57             /*!< Operation not permitted */

#define SNMP_GET                0XA0            /*!< Manager get request */
#define SNMP_GETNEXT            0XA1            /*!< Manager get next request */
#define SNMP_SET                0XA3            /*!< Manager set request */
#define SNMP_CHECK              0XAE            /*!< For checking types in sequence */

#define ASN_LONG_LEN            (0x80)          /*!< */

#define ASN_BOOLEAN             (0x01)          /*!< ANS id of Boolean */
#define ASN_INTEGER             (0x02)          /*!< ASN id of Integer */
#define ASN_BIT_STR             (0x03)          /*!< ASN id of Bit String */
#define ASN_OCTET_STR           (0x04)          /*!< ASN id of Octet String */
#define ASN_NULL                (0x05)          /*!< ASN id of NULL Object */
#define ASN_OBJECT_ID           (0x06)          /*!< ASN id of OID */
#define ASN_SEQUENCE            (0x10)          /*!< ASN id of Sequence */
#define ASN_SET                 (0x11)          /*!< ASN id of Set */
#define ASN_CONSTRUCTOR         (0X20)          /*!< ASN id of Constructor */
#define ASN_IPADDR              (0X40)          /*!< ASN id of ip address */
#define ASN_COUNTER32           (0X41)          /*!< ASN id of 32 bits counter */
#define ASN_GAUGE32             (0X42)          /*!< ASN id of 32 bits gauge */
#define ASN_TIMETICKS           (0X43)          /*!< ASN id of tick counter */
#define ASN_OPAQUE              (0X44)          /*!< ASN id of an Opaque object */
#define ASN_COUNTER64           (0X46)          /*!< ASN id of 64 bits counter */
#define ASN_UNSIGNED32          (0X42)          /*!< ASN id of 32 bits unsigned integer */


/*
======================================================================
			Data Structures Definition
======================================================================
*/

/*! @brief Structure for columns in mib table (sequence mib entries) */
typedef struct Mibcol_S {
        unsigned char   mc_oid;         /*!< OID of column (column identifier) */
        unsigned char   mc_type[2];     /*!< Type of value */
} Mibcol;

/*! @brief Structure for mib entries in mib modules */
typedef struct Mibent_S 
{
        unsigned char   me_oid;         /*!< Base MIB module object identifier */
        unsigned char   me_type[2];     /*!< [0]:asn or snmp type [1] opaque type */
        /*!< Members for tables (valid if "me_type[0] == ASN_SEQUENCE") */
        Mibcol const *  me_cols;        /*!< List of cols (index ones first) */
        int             me_ncols;       /*!< Number of cols in previous list */
        int             me_nidx;        /*!< Number of index cols in previous list */
} Mibent;

/*! @brief Structure for mib modules */
typedef struct Mibmod_S {
        unsigned char   mm_oid[64];     /*!< Base MIB module object identifier */
        int             mm_oidlen;      /*!< OID length of the MIB module */
        Mibent const *  mm_ent;         /*!< Points to first entity */
        int             mm_nent;        /*!< Number of entries in mib */
        int             (* mm_cb_f)(void * Mibparamcb, unsigned int *val, int *vallen, unsigned int cbdata);            /*!< MIB access function (callback) */
        unsigned int    mm_cbdata;      /*!< Callback data for arg cbdata of mm_cb_f */
} Mibmod;

/*! @brief Parameters of MIB module callbacks */
typedef struct Mibparamcb_S {
        void *                  session;        /*!< Beackpointer to SNMP session */
        unsigned char           cmd;            /*!< Cmd snmp(SNMP_GET, SNMP_GETNEXT, SNMP_SET, SNMP_CHECK) */ 
        Mibmod const *          mib;            /*!< Current mib module */
        unsigned int            mibdata;        /*!< Mib callback data */
        Mibent const *          mibent;         /*!< Current mib entry */
        Mibcol const *          mibcol;         /*!< Current column of mibent (for sequence) */
        unsigned char const *   oid;            /*!< Pointer to read oid */
        unsigned int            oidlen;         /*!< Size of oid_in */
        int                     nidx;           /*!< Number of index */
        unsigned int            idx[8];         /*!< Index values */
        unsigned int            idxlen[8];      /*!< Length of values */
} Mibparamcb;

/*! @brief Parameters of trap function */
typedef struct TrapOid_S {
        const unsigned char *   trapoid;        /*!< MIB object identifier */
        int                     trapoidlen;     /*!< OID length */
} TrapOid;

/*! @brief Data to send with SNMP trap message */
typedef struct TrapVars_S {
        const void *    vars;                   /*!< Trap data */
        int             varslen;                /*!< Trap data length */
} TrapVars;


/*
======================================================================
			Functions Definition
======================================================================
*/


/*! @brief This function adds a new MIB to the SNMP agent
 * @param mib : MIB structure
 * @return 0 if OK,  other value if not OK 
 *
 * @link KSFAM_OS_NET Back to top @endlink
 */ 
int SnmpMibAdd(Mibmod const *mib);


/*! @brief This function sends an SNMP trap message to a SNMP manager
 * @param addr : IP address of the SNMP manager (like "192.168.0.1")
 * @param com  : Community to use (like "public")
 * @param oid  : Oid to send
 * @param vars : ASN1 formatted data
 * @return 0 if OK,  other value if not OK 
 *
 * @link KSFAM_OS_NET Back to top @endlink
 */ 
int SnmpTrapTo(const char *addr, const char *com, TrapOid * oid, TrapVars * vars);


// Result of SNMP fioctl (see oem_sysfioctl.h) 
#define SNMP_OK                 0               /*!< No error */
#define SNMP_NOT_IMPLEMENTED    -1              /*!< Not implemented */
#define SNMP_BAD_PARAM          -2              /*!< Bad parameter */
#define SNMP_AGENT_STARTED      -3              /*!< SNMP agent started */
#define SNMP_AGENT_STOPPED      -4              /*!< SNMP agent stopped */


#endif
/*! @}  */ 


