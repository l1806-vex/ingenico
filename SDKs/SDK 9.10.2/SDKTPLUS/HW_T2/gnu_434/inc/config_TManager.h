/*! @addtogroup KSFAM_AUTRES_MANAGER
	* @{
**/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _MANAGER_CONFIG_H
#define _MANAGER_CONFIG_H

/*
======================================================================
			Data Structures Definition
======================================================================
*/
/*! @brief This structure describes the hardware data.*/
typedef struct activ_t{
	unsigned char NumeroSerie[16];							/*!< serial number*/
	unsigned char Sep1;													/*!< separation mark*/
	unsigned char DatePremiereActivation[12];		/*!< date of the first activation*/
	unsigned char Sep2;													/*!< separation mark*/
	unsigned char NiveauSecurite[2];						/*!< security level*/
	unsigned char Sep3;													/*!< separation mark*/
	unsigned char IdentificationPays[36];				/*!< country ID*/
	unsigned char Sep4;													/*!< separation mark*/
	unsigned char DateDerniereActivation[12];		/*!< date of the last activation*/
	unsigned char Sep5;													/*!< separation mark*/
	unsigned char MotifTensionBasse;						/*!< low voltage motif*/
	unsigned char Sep6;													/*!< separation mark*/
	unsigned char MotifTensionHaute;						/*!< high voltage motif*/
	unsigned char Sep7;													/*!< separation mark*/
	unsigned char MotifTreillis;								/*!< lattice motif*/
	unsigned char Sep8;													/*!< separation mark*/
	unsigned char MotifTemperatureHaute;				/*!< high temperature motif*/
	unsigned char Sep9;													/*!< separation mark*/
	unsigned char MotifTemperatureBasse;				/*!< low temperature motif*/
	unsigned char Sep10;												/*!< separation mark*/
	unsigned char MotifMembraneClavier;					/*!< keyboard motif*/
	unsigned char Sep11;												/*!< separation mark*/
	unsigned char CapotInferieur;								/*!< inferior cover */
	unsigned char Sep12;												/*!< separation mark*/
	unsigned char CapotSuperieur;								/*!< superior cover*/
	unsigned char Sep13;												/*!< separation mark*/
	unsigned char ExtensionSXX[3];							/*!< SXX Extension*/
	unsigned char Sep14;												/*!< separation mark*/
}activ_t;

/*! @brief Define the ethernet configuration structure.*/
typedef struct ethernet_t{
  unsigned char HWADDR[21];										/*!< hardware address (MAC)*/
  unsigned char IPADDR[21];										/*!< IP address*/
  unsigned char NETMASK[21];									/*!< network mask*/
}ethernet_t;


#endif
/*! @} **/
#ifdef __cplusplus
}
#endif
