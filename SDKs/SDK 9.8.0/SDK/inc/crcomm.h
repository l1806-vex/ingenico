/*! @addtogroup KSFAM_CB2A
	* @{
**/
/* codage des phases */
#define PHASE_NUMER 0x0000
#define PHASE_CONNEX 0x1000
#define PHASE_CENTRE 0x2000

#define E_HORS_LIGNE    0x0001       /*!< offline modem    */
#define E_ABANDON       0x000d       /*!< off-line operator */

//return code pb numbering
#define E_ERRNUM       0x0001       /*!< pb numbering  */
#define E_MODEM_INC    0x0002       /*!< pb numbering  */
#define E_ETHERNET_KO  0x0003       /*!< no physical link */
#define E_MODEM_KO     0x0004       /*!< no MODEM */
#define E_PROFIL_KO    0x0005
#define E_PORT_KO      0x0006

//return code of the CSA liaison function
#define E_ERROR					0x0080       		/*!< reception error on frame pad      */
#define E_LIB						0x0081       		/*!< lib reception on pad 				 */
#define E_RESET					0x0082      	  /*!< reception reset pad				 */
#define E_CONNEX				0x0083      		/*!< pb connection pad : Switching to V42a    */
#define E_REC_TRANSPAC	0x0084      		/*!< pb connection pad : Reception TRANSPAC */
#define E_EMI_SET1			0x0085       		/*!< pb connection pad : Settings       */
#define E_EMI_NO_PAD		0x0086       	  /*!< pb connection pad : emission no PAD    */
#define E_REC_COM				0x0087       		/*!< pb connection pad : reception COM      */
#define E_IPDU_LONGUE   0x0088      		/*!< Emission/reception IPDU long           */
#define E_EMI_PASSWD    0x0089      		/*!< Emission/reception PASSWORD              */
#define E_EMI_SET2			0x008A      	  /*!< Settings                             */

//return code level liaison functions
#define E_TINVAL        0x0101       /*!< bad flags debut */
#define E_ETAB          0x0102       /*!< read error. CRLF to establish. row */
#define E_TROPLONG      0x0103       /*!< frame too long before pennon End */
#define E_BADCRC        0x0104       /*!< bad CRC in reading frame*/
#define E_REPEAT        0x0105       /*!< reemission application of the grid */
#define E_NOTLA         0x0106       /*!< frame did not received the expected */
#define E_NOTLT         0x0107       /*!< frame did not received expected LT */
#define E_BADLT         0x0108       /*!< LT frame reception step sequence */

#define E_TIME_OUT_R    0x0109       /*!< timeout waiting on the frame or LT */
#define E_TIME_OUT_W    0x010a       /*!< timeout on ll_write */

#define E_POLLR         0x010b       /*!< error polling reception */
#define E_POLLE         0x010c       /*!< error polling emission */

#define E_BUGANA        0x010d       /*!< appel de ll_anatrame with
                                        incorrect parameter */
#define E_BUGTRLO       0x010e       /*!< appel de ll_lt_out, ll_la_out,
                                        ll_ld_out avec mes_out_adres trop
                                        petit */
//return code level IPDU
#define E_IPDU		0x0200      			 /*!< base error code returned by ipdu 01
					                             the center, ie the code will be X2xx */
#define E_BPROT  0x02FF   					/*!<bad protocol level IPDU */

/* Added NF */  
#define E_FORMAT_PI     0x02FE       /*!< bad IP format (lg bad) */
#define E_SEQ_PI        0x02FD       /*!< wrong order of PI */
#define E_PI_MANQ       0x02FC       /*!< Missing PI */
#define E_LGI_INV       0x02FB       /*!< LGI invalid */
#define E_VAL_PI        0x02fA       /*!< value PI07 = 00 */ /* Added / nath */


//APDU level return codes
#define E_NOT0110   0x0301    /*!< It is not an answer for authorization */
#define E_INCOHER   0x0302    /*!< bit_map parameters and incoherent */
#define E_PARINC    0x0303    /*!< unknown parameter in the data */
#define E_DIFFER    0x0304    /*!< parameter difference between issued and received*/
#define E_PARMANQ   0x0305    /*!< Missing required parameter */

//PI01 values returned in the ipdu AB (disconnect)
#define PI01_PGI_INVALIDE        0x02
#define PI01_APDU_INCONNUE       0x11
#define PI01_APDU_INCORRECTE     0x12
#define PI01_LG_APDU_INCORRECTE  0x13
#define PI01_ERR_PROTOCOLE       0x18
#define PI01_EXPIR_TSI           0x19
#define PI01_EXPIR_TNR           0x1B
#define PI01_SEQ_PI              0x1D
#define PI01_FORMAT_PI           0x26 /* valeur de nath 0x23 */
#define PI01_PI_MANQ             0x25
#define PI01_LGI_INV             0x05 /* valeur de nath 0x26 */
#define PI01_TERMINAISON_NORMALE 0x80
#define PI01_VAL_ZERO_PI07       0x27 /* ajouter / a nath */
#define PI01_NON_RENSEIGNE       0xFF

/*! @} **/




