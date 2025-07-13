/*! @addtogroup KSFAM_OS
 * @{
 */

#ifndef _CONFIG_H
#define _CONFIG_H

/* ======================================================================
 *                      Data Structures Definition
 * ======================================================================
 */

/*! @brief This structure define the hardware configuration of the terminal. Warning : can't be used by the applications !*/
typedef struct hterm_t {
   unsigned char terminal_number[8];          /*!< number of the terminal */
   unsigned char product_code[3];             /*!< code of the product */
   unsigned char constructor_code[8];         /*!< code of the constructor */
   unsigned char total_ram[4];                /*!< total size of the RAM */
   unsigned char total_flash[4];              /*!< total size of the flash memory */
   unsigned char options[2];                  /*!< \li HTERM_OPT_PORTABLE : bit 0 \li HTERM_OPT_PRINTER : bit 1 \li HTERM_OPT_RADIO : bit 2 \li HTERM_OPT_BUZZER  : bit 3 \li HTERM_OPT_COM0  : bit 4 \li HTERM_OPT_COM1 : bit 5 \li HTERM_OPT_COM2  : bit 6 \li HTERM_OPT_COM3  : bit 7 \li HTERM_OPT_USB_HOST  : bit 8 \li HTERM_OPT_USB_DEVICE : bit 9 \li HTERM_OPT_ETHERNET : bit 10 \li HTERM_OPT_SMART : bit 11 \li HTERM_OPT_SPY_USB : bit 12 (not used any more) \li HTERM_OPT_DUART : bit 12 option UCM \li HTERM_OPT_MDB_C3 : bit 13 option UCM \li HTERM_OPT_IRDA : bit 15*/
   unsigned char readers_options[2];          /*!< \li HTERM_OPT_ISO1 : bit 0 \li HTERM_OPT_ISO2 : bit 1 \li HTERM_OPT_ISO3 : bit 2 \li HTERM_OPT_CAM1 : bit 3 \li HTERM_OPT_CAM2  : bit 4 \li HTERM_OPT_SAM1 : bit 5 \li HTERM_OPT_SAM2 : bit 6 \li HTERM_OPT_SAM3 : bit 7 \li HTERM_OPT_SAM4 : bit 8 \li HTERM_OPT_BOOSTER : bit 9 option UCM \li HTERM_OPT_CLESS : bit 10 option Cless \li HTERM_OPT_CAM3 : bit 11*/
   unsigned char modem_options[1];            /*!<modem options :HTERM_OPT_MODEM */
   unsigned char country_code[2];             /*!< code of the country */
   unsigned char display_options[1];          /*!< display options : \li HTERM_DISPLAY_64 \li HTERM_DISPLAY_128 */
   unsigned char interface_version[4];        /*!< version of the interface */
   unsigned char ext_options[1];              /*!< external options : \li HTERM_EXT_OPT_NO_MMC \li HTERM_EXT_OPT_COMPACT_FLASH \li HTERM_EXT_OPT_RADIO_TYPE \li HTERM_EXT_OPT_RADIO_TYPE_GPRS 0x00 \li HTERM_EXT_OPT_RADIO_TYPE_BLUETOOTH 0x08 \li HTERM_EXT_OPT_RADIO_TYPE_WIFI 0x04 \li HTERM_EXT_OPT_BIO \li HTERM_EXT_OPT_TILT */
   unsigned char extension_type[1];           /*!< type of the extension */
   unsigned char product_reference[12];       /*!< reference of the product */
   unsigned char thunder_version[4];          /*!< version of the thunder */
   unsigned char booster_version[4];          /*!< version of the booster */
   unsigned char manufacturing_date[8];       /*!< manufacturing date */
   unsigned char hardware_personalization[4]; /*!< hardware personalization */
   unsigned char software_personalization[4]; /*!< software personalization */
   unsigned char tid_zone[20];                /*!< zone ID */
} hterm_t;


/* ======================================================================
 *                      List of Defines
 * ======================================================================
 */

// options
#define HTERM_OPT_PORTABLE    (ConfigTerm()->options[0]&0x01)  /*!< bit 0 */
#define HTERM_OPT_PRINTER     (ConfigTerm()->options[0]&0x02)  /*!< bit 1 */
#define HTERM_OPT_RADIO       (ConfigTerm()->options[0]&0x04)  /*!< bit 2 */
#define HTERM_OPT_BUZZER      (ConfigTerm()->options[0]&0x08)  /*!< bit 3 */
#define HTERM_OPT_COM0        (ConfigTerm()->options[0]&0x10)  /*!< bit 4 */
#define HTERM_OPT_COM1        (ConfigTerm()->options[0]&0x20)  /*!< bit 5 */
#define HTERM_OPT_COM2        (ConfigTerm()->options[0]&0x40)  /*!< bit 6 */
#define HTERM_OPT_COM3        (ConfigTerm()->options[0]&0x80)  /*!< bit 7 */
#define HTERM_OPT_USB_HOST    (ConfigTerm()->options[1]&0x01)  /*!< bit 8 */
#define HTERM_OPT_USB_DEVICE  (ConfigTerm()->options[1]&0x02)  /*!< bit 9 */
#define HTERM_OPT_ETHERNET    (ConfigTerm()->options[1]&0x04)  /*!< bit 10 */
#define HTERM_OPT_SMART       (ConfigTerm()->options[1]&0x08)  /*!< bit 11 */
#define HTERM_OPT_SPY_USB     (ConfigTerm()->options[1]&0x00)  /*!< bit 12 not used */
#define HTERM_OPT_DUART       (ConfigTerm()->options[1]&0x10)  /*!< bit 12 option UCM */
#define HTERM_OPT_MDB_C3      (ConfigTerm()->options[1]&0x20)  /*!< bit 13 option UCM */
#define HTERM_OPT_IRDA        (ConfigTerm()->options[1]&0x80)  /*!< bit 15 option UCM */

// reader options
#define HTERM_OPT_ISO1        (ConfigTerm()->readers_options[0]&0x01)   /*!< bit 0 */
#define HTERM_OPT_ISO2        (ConfigTerm()->readers_options[0]&0x02)   /*!< bit 1 */
#define HTERM_OPT_ISO3        (ConfigTerm()->readers_options[0]&0x04)   /*!< bit 2 */
#define HTERM_OPT_CAM1        (ConfigTerm()->readers_options[0]&0x08)   /*!< bit 3 */
#define HTERM_OPT_CAM2        (ConfigTerm()->readers_options[0]&0x10)   /*!< bit 4 */
#define HTERM_OPT_SAM1        (ConfigTerm()->readers_options[0]&0x20)   /*!< bit 5 */
#define HTERM_OPT_SAM2        (ConfigTerm()->readers_options[0]&0x40)   /*!< bit 6 */
#define HTERM_OPT_SAM3        (ConfigTerm()->readers_options[0]&0x80)   /*!< bit 7 */
#define HTERM_OPT_SAM4        (ConfigTerm()->readers_options[1]&0x01)   /*!< bit 8 */
#define HTERM_OPT_BOOSTER     (ConfigTerm()->readers_options[1]&0x02)   /*!< bit 9 option UCM */
#define HTERM_OPT_CLESS       (ConfigTerm()->readers_options[1]&0x04)   /*!< bit 10 option Cless */
#define HTERM_OPT_CAM3        (ConfigTerm()->readers_options[1]&0x08)   /*!< bit 11 */

#define HTERM_OPT_PROD_TYPE   (ConfigTerm()->readers_options[1]&0xF0)   /*!< bits 12-15 */
#define    HTERM_OPT_PROD_TYPE_IPP3XX            0x10
#define    HTERM_OPT_PROD_TYPE_SMART             0x20
#define    HTERM_OPT_PROD_TYPE_EFT30             0x30
#define    HTERM_OPT_PROD_TYPE_EFT30_PLUS        0x40
#define    HTERM_OPT_PROD_TYPE_TWIN30            0x50
#define    HTERM_OPT_PROD_TYPE_930               0x60

// modem options
#define HTERM_OPT_MODEM       (ConfigTerm()->modem_options[0])          /*!< Modem options: all bits */
#define HTERM_OPT_MODEM_V34   (ConfigTerm()->modem_options[0]&0x20)     /*!< !=0 <-> Support V34 connection */

// display options
#define HTERM_DISPLAY_BIT0    (ConfigTerm()->display_options[0]&0x01)   /*!< !=0 <-> Display 2 alphanumeric lines */
#define HTERM_DISPLAY_BIT1    (ConfigTerm()->display_options[0]&0x02)   /*!< !=0 <-> Display 2 graphic lines */
#define HTERM_DISPLAY_BIT2    (ConfigTerm()->display_options[0]&0x04)   /*!< !=0 <-> Display 4 graphic lines */
#define HTERM_DISPLAY_COLOR   (ConfigTerm()->display_options[0]&0x08)   /*!< !=0 <-> Display 8 graphic lines */
#define HTERM_DISPLAY_64      (ConfigTerm()->display_options[0]&0x10)   /*!< !=0 <-> Display 128x64 */
#define HTERM_DISPLAY_128     (ConfigTerm()->display_options[0]&0x20)   /*!< !=0 <-> Display 128x128 */
#define HTERM_DISPLAY_VGA     (ConfigTerm()->display_options[0]&0x02)   /*!< !=0 <-> Display VGA */
#define HTERM_DISPLAY_QVGA    (ConfigTerm()->display_options[0]&0x04)   /*!< !=0 <-> Display QVGA */

// ext_options
#define HTERM_EXT_OPT_NO_MMC        (ConfigTerm()->ext_options[0]&0x01) /*!< !=0 <-> MMC not active */
#define HTERM_EXT_OPT_COMPACT_FLASH (ConfigTerm()->ext_options[0]&0x02) /*!< !=0 <-> Support Compact Flash */
#define HTERM_EXT_OPT_RADIO_TYPE    (ConfigTerm()->ext_options[0]&0x0C) /*!< !=0 <-> Support Radio */
#define    HTERM_EXT_OPT_RADIO_TYPE_GPRS         0x00                   /*!< !=0 <-> GPRS */
#define    HTERM_EXT_OPT_RADIO_TYPE_BLUETOOTH    0x08                   /*!< !=0 <-> Bluetooth */
#define    HTERM_EXT_OPT_RADIO_TYPE_WIFI         0x04                   /*!< !=0 <-> Wifi */
#define    HTERM_EXT_OPT_RADIO_TYPE_CDMA         0x0C                   /*!< !=0 <-> CDMA */
#define HTERM_EXT_OPT_BIO           (ConfigTerm()->ext_options[0]&0x40) /*!< !=0 <-> Support Biometric device */
#define HTERM_EXT_OPT_TILT          (ConfigTerm()->ext_options[0]&0x80) /*!< !=0 <-> Support Tilt detect */

// extension_type (Thunder specific)
#define HTERM_EXT_OPT_AUDIO         (ConfigTerm()->extension_type[0]&0x01) /*!< bit 0 (zero means n/a) */
#define HTERM_EXT_OPT_TOUCH_SCREEN  (ConfigTerm()->extension_type[0]&0x02) /*!< bit 1 (zero means n/a) */
#define HTERM_EXT_OPT_NO_VIDEO      (ConfigTerm()->extension_type[0]&0x04) /*!< bit 2 (1 to disable video support) */
#define HTERM_EXT_OPT_LIGHT_SENSOR  (ConfigTerm()->extension_type[0]&0x08) /*!< bit 3 (zero means n/a) */

// thunder_version (4 bytes)
#define HTERM_THUNDER_VERSION       (ConfigTerm()->thunder_version)     /*!< Current Thunder version */

// booster_version (4 bytes)
#define HTERM_BOOSTER_VERSION       (ConfigTerm()->booster_version)     /*!< Current Booster version */

// software_personalization (4 bytes)
#define HTERM_REQUIRED_PKI_VERSION  (ConfigTerm()->software_personalization)  /*!< Minimum Ingetrust PKI version required */

#endif /* _CONFIG_H */

/*! @} */
