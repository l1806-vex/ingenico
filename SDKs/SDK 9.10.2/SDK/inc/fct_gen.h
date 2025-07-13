/*! @addtogroup KSFAM_CB2A
	* @{
**/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FCT_GEN_H
#define FCT_GEN_H

/*
======================================================================
					List of Defines
======================================================================
*/
#define PAD_NOSIG '0' /* MPEV5.2 */
#define PAD_EMA   '1'
#define PAD_EBA   '2'
#define PAD_IP    'A'

/*********************************************************************/
/* Le fait que le buffer en emission soit double de celui de         */
/* la reception est important                                        */
/* en fait , le buffer de reception sert a la preparation du buffer  */
/* final en emission avec doublement des DLE soit une taille         */
/* theorique finale double (si le message ne contient que des DLE)   */
/*********************************************************************/
#define SIZE_BUF_OUT  1024  		    		/* emission buffer size  */
#define SIZE_BUF_IN   5120              /* reception buffer size */

// #define INTERNE		    0x01
// #define EXTERNE		    0x00

#define Taille_CMD_MODEM		40
#define Taille_CMD_STAND		20
#define Taille_COMPL_X25		40
#define Taille_ADR_RACCORD      20
#define Taille_ADR_APPEL        40

/*
======================================================================
			Type Definitions
======================================================================
*/
/*! @brief Define a standard command string. */
typedef unsigned char STR_CMD_STAND    [Taille_CMD_STAND];

/*! @brief String for complementary informations about the X25. */
typedef unsigned char STR_COMP_X25     [Taille_COMPL_X25];

/*! @brief Define a link address string. */
typedef unsigned char STR_ADR_RACCORD  [Taille_ADR_RACCORD+1];

/*! @brief Define a call address string. */
typedef unsigned char STR_ADR_APPEL    [Taille_ADR_APPEL+1];

#endif
/*! @} **/
#ifdef __cplusplus
}
#endif
