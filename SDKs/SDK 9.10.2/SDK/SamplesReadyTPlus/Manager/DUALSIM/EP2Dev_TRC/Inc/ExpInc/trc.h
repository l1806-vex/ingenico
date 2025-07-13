/*!
 ------------------------------------------------------------------------------
                  INGENICO Technical Software Department 
 ------------------------------------------------------------------------------
 Copyright (c) 2012, Ingenico.
 28-32 boulevard de Grenelle 75015 Paris, France.
 All rights reserved.

  This source program is the property of INGENICO Company and may not be copied
  in any form or by any means, whether in part or in whole, except under license
  expressly granted by INGENICO company 
  
  All copies of this program, whether in part or in whole, and
  whether modified or not, must display this and all other	
  embedded copyright and ownership notices in full.
 ------------------------------------------------------------------------------
   
 Project : Easy Path to Dev
 Module  : TRC - Trace Module

 @file      trc.h
 @brief     This file provides the API for Trace Module.
 @date      06/12/2012

 ------------------------------------------------------------------------------
 */

#ifndef __TRC_H__
#define __TRC_H__

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup TRC Trace Management Module
 *
 * @{
 */

#define Major_Release 01
#define Minor_Release 00

/** \weakgroup TRC_API TRC APIs
 *
 * @{
 */

/** \weakgroup TRC_API_ErrorCodes Trace Error Codes
 * These are the error codes returned by the TRC Management Module.
 * @{
 */

#define TRC_OK                               00 /**< No error encountered */
#define TRC_ERR_UNKNOWN                     -01 /**< Unknown error */
#define TRC_ERR_INSUFFICIENT_MEM            -02 /**< Insufficient memory */
#define TRC_ERR_DUPLICATE_CAT               -03 /**< A category with the same name already exist. */
#define TRC_ERR_INVALID_TRACE_ID            -04 /**< Invalid trace ID*/
#define TRC_ERR_INVALID_PARAM_CAT_NAME      -05 /**< Category name is passed is NULL or exceeds the limit. */
#define TRC_ERR_INVALID_PARAM_TRC_ID        -06 /**< Trace ID parameter is NULL. */
#define TRC_ERR_TRCID_TURNED_OFF            -07 /**< Trace is turned off for the specific trace ID. */
#define TRC_ERR_TRCLEVEL_TURNED_OFF         -8 /**< Trace is turned off for the specific level. */

#define TRC_ERR_FILESYSTEM_OPEN             -20 /**< The trace file cannot be openned */
#define TRC_ERR_FILESYSTEM_MOUNT            -21 /**< The volume cannot be mounted */
#define TRC_ERR_FILESYSTEM_FULL             -22 /**< The filesystem is full */
#define TRC_ERR_FILESYSTEM_WRITE            -23 /**< There was an error writing to the file */
#define TRC_ERR_FILESYSTEM_SENTINEL         -24 /**< There was an error in the trace sentinel of the file. */
#define TRC_ERR_FILESYSTEM_EOF              -25 /**< Unexpected end of function or end of file. */

#define TRC_ERR_PRINTER_UNKNOWN             -40 /**< Unknown error in the printer API */
#define TRC_ERR_PRINTER_NOMOREPAPER	        -41 /**< No more paper in the Printer */
#define TRC_ERR_PRINTER_NOTAVAILABLE        -42 /**< Printer not available */
#define TRC_ERR_PRINTER_RESOURCE_CONFLICT   -43 /**< Printer is currently in used by another process.*/

#define TRC_ERR_UDP_CONNECT                 -60 /**< Could not connect to the UDP host*/
#define TRC_ERR_UDP_SEND                    -61 /**< Unable to send to the UDP host*/

#define TRC_ERR_REMOTE_SEND                 -80 /**< Could not send traces to the remote debug console */


/** @} */

/** \weakgroup TRC_API_TraceLevel Trace Levels
 *
 * Constants that SHALL be used to set the level filter of the trace module.
 * @{
 */
#define TRC_LEVEL_ERR                   1<<0 /**< Traces are seen in the output stream with a label ERR. */
#define TRC_LEVEL_WARNING               1<<1 /**< Traces are seen in the output stream with a label WARNING. */
#define TRC_LEVEL_INFO                  1<<2 /**< Traces are seen in the output stream with a label INFO. */
#define TRC_LEVEL_DEBUG                 1<<3 /**< Traces are seen in the output stream with a label DEBUG. */

/** @} */

/** \weakgroup TRC_API_TraceCategoryConstants Trace Category Constants
 * These are constants that defines the limits of buffers that are passed to the Trace module.
 * @{
 */
#define TRC_CATEGORY_NAME_MAX_LEN   10 /**< Maximum length of trace category name.*/

/** @} */

/** \weakgroup TRC_API_TraceFilterConstants Trace Filter Constants
 * Constants based on \ref TRC_API_TraceLevel that may be used to set the level filter of the trace module.
 * These constants are used when calling \ref TRC_LevelFilterSet().
 * @{
 */

#define TRC_FILTER_NONE             (0x00)
#define TRC_FILTER_ERR              (TRC_LEVEL_ERR)
#define TRC_FILTER_WARNING          (TRC_LEVEL_ERR|TRC_LEVEL_WARNING)
#define TRC_FILTER_INFO             (TRC_LEVEL_ERR|TRC_LEVEL_WARNING|TRC_LEVEL_INFO)
#define TRC_FILTER_DEBUG            (TRC_LEVEL_ERR|TRC_LEVEL_WARNING|TRC_LEVEL_INFO|TRC_LEVEL_DEBUG)
#define TRC_FILTER_ALL              (0xFF)

/** @} */

/** \weakgroup TRC_API_TraceMacros Trace Macros
 *
 * @{
 */

#define TRC_TRACE_ERR(category, string, ...) { (void)TRC_Trace(category, TRC_LEVEL_ERR, __FILE__, __LINE__, string, ##__VA_ARGS__);}
#define TRC_TRACE_WARN(category, string, ...) { (void)TRC_Trace(category, TRC_LEVEL_WARNING, __FILE__, __LINE__, string, ##__VA_ARGS__);}
#define TRC_TRACE_INFO(category, string, ...) { (void)TRC_Trace(category, TRC_LEVEL_INFO, __FILE__, __LINE__, string, ##__VA_ARGS__);}
#define TRC_TRACE_DEBUG(category, string, ...) { (void)TRC_Trace(category, TRC_LEVEL_DEBUG, __FILE__, __LINE__, string, ##__VA_ARGS__);}

/** @} */

/** \weakgroup TRC_API_STREAMS Trace Output Streams
 * These are the supported output streams of the TRC Module.
 * @{
 */

typedef enum
{
    TRC_STREAM_TELIUM_TRACE     = 0x0001, /**< Trace is directed to the native Telium Trace tool */
    TRC_STREAM_REMOTE_DEBUG     = 0x0002, /**< Trace is directed to the remote debug trace tool */
    TRC_STREAM_INT_FILE         = 0x0004, /**< Trace is directed to a file and is stored in the Telium File System */
    TRC_STREAM_EXT_FILE_USB1    = 0x0008, /**< Trace is directed to a file and is stored in an external storage such as SD, MMC, etc.*/
    TRC_STREAM_EXT_FILE_MMC     = 0x0010, /**< Trace is directed to a file and is stored in an external storage such as SD, MMC, etc.*/
    TRC_STREAM_PRINTER          = 0x0020, /**< Trace is directed to the printer */
    TRC_STREAM_UDP_IP           = 0x0040  /**< Trace is directed to a specifc IP:PORT using UDP */
}TRC_OutputStream_t;

/** @} */


/** \weakgroup TRC_API_TraceIDType Trace Identifier
 *
 * @{
 */

typedef unsigned long TRC_Trace_t; /**< Type definition of trace objects created. */

/** @} */

/** \weakgroup TRC_API_TraceFunctions Trace Functions
 *
 * @{
 */

/** \brief Creates a handle for a trace category.
 *
 * \param[in]   appType   The application type of the caller.
 * \param[out]  trcID     The address where to store the traceID.
 * \param[in]   name      The name of the trace category to be instantiated.
 *
 * \return
 *      - \ref TRC_OK = Trace category has been successfully instantiated.
 *      - \ref TRC_ERR_DUPLICATE_CAT = A Trace category with the same name already exists.
 *      - \ref TRC_ERR_INSUFFICIENT_MEM = Memory is not sufficient to allocate a new trace category.
 *      - \ref TRC_ERR_INVALID_PARAM_CAT_NAME = Category name is passed is NULL or exceeds the limit.
 *      - \ref TRC_ERR_INVALID_PARAM_TRC_ID = Trace ID parameter is NULL.
 *
 * \note
 *      - The default output stream is \ref TRC_STREAM_TELIUM_TRACE.
 *      - See the snippet of \ref TRC_Test0000() below:
 * \include trcTest0000.c
 */
int TRC_Create(const unsigned int appType, TRC_Trace_t *trcID, char* name);

/** \brief Removes a trace category.
 *
 * \param[in] trcID     The trace ID obtained using TRC_Create().
 *
 * \return
 *      - \ref TRC_OK = The trace ID has been removed from the list of valid trace IDs.
 *      - \ref TRC_ERR_INVALID_TRACE_ID = The trace ID provided does not exist in the list.
 * \note
 *      - See the snippet of \ref TRC_Test0000() below:
 * \include trcTest0000.c
*/
int TRC_Destroy(const TRC_Trace_t trcID);

/** \brief Appends a trace log into the output stream.
 *
 * \param[in] trcID     The trace ID obtained using TRC_Create().
 * \param[in] level     The trace level. See \ref TRC_API_TraceLevel.
 * \param[in] file      The name of the file where this function is called. The __FILE__
 *                      macro is used here to obtain the name of the file automatically.
 * \param[in] line      The line number in the file where this function is called. The
 *                      __LINE__ macro is used to obtain the line number automatically.
 * \param[in] fmt       The variable formatted character string which contains what
 *                      is to be traced. The format is similar to the call of the
 *                      sprintf() function.
 *
 * \return
 *      - \ref TRC_OK = The trace has been successfully sent to the output stream.
 *      - \ref TRC_ERR_INVALID_TRACE_ID = The trace ID provided does not exist in the list.
 *      - \ref TRC_ERR_INSUFFICIENT_MEM = Memory is not enough to format the data to be traced.
 *      - \ref TRC_ERR_PRINTER_NOMOREPAPER = The printer is out of paper.
 *      - \ref TRC_ERR_PRINTER_NOTAVAILABLE = The printer is not available.
 *      - \ref TRC_ERR_PRINTER_RESOURCE_CONFLICT = The printer is being used by another process.
 *      - \ref TRC_ERR_TRCID_TURNED_OFF = The switch for the specific trace ID is turned OFF.
 *      - \ref TRC_ERR_TRCLEVEL_TURNED_OFF = The switch for the specific level is turned OFF.
 *      - \ref TRC_ERR_UNKNOWN = There was an unknown error encountered during the sending of traces
 *        to the specified output streams.
 *
 * \note
 *      - Any length of data can be passed to this function subject to the terminal's
 *        memory limit.
 *      - See the snippet of \ref TRC_Test0000() below:
 * \include trcTest0000.c
 */
int TRC_Trace( const TRC_Trace_t trcID, const unsigned int level, const char* file, const int line, const char* fmt, ... );

/** \brief Turns ON/OFF tracing of specific trace levels.
 * 
 * \param[in] level    Bitwise OR of the trace levels. See \ref TRC_API_TraceLevel for the possible values
 *                      of trace levels. Or, see \ref TRC_API_TraceFilterConstants to use a predefined filter
 *                      masks.
 * \return
 *      - \ref TRC_OK = The trace level has been successfully set.
 * \note
 *      - The default filter is set to all levels. This means that all levels are traced or
 *        accepted by the Trace module.
 *      - See the snippet of \ref TRC_Test0000() below:
 * \include trcTest0000.c
 */
int TRC_LevelFilterSet(const unsigned int level);

/** \brief Turns ON/OFF tracing depending on the category.
 *
 * \param[in] trcID     The trace ID obtained using TRC_Create().
 * \param[in] state     The value to be set. FALSE to turn OFF. TRUE to turn ON.
 *
 * \return
 *      - \ref TRC_OK = The trace has been successfully sent to the output stream.
 *      - \ref TRC_ERR_INVALID_TRACE_ID = The trace ID provided does not exist in the list.
 * \note
 *      - See the snippet of \ref TRC_Test0001() below:
 * \include trcTest0001.c
 */
int TRC_CategoryFilterSet(const TRC_Trace_t trcID, const unsigned char state);


/** \brief Change the output stream of traces. This function is also used to clear the parameters
 * of the output streams.
 * Default is TELIUM trace system.
 * Depend on the outputStream, the parameters shall be used filepath, addr and port
 *
 * \param[in]   outputStream    Bitwise OR of \ref TRC_Outputstream_t enum values. If the value is
 *                              zero, the output streams' parameters will be cleared and closed.
 * \param[in]   dst             The absolute path of the file where the traces will be
 *                              stored. This parameter is used only when the output
 *                              stream is \ref TRC_STREAM_INT_FILE or \ref TRC_STREAM_EXT_FILE.
 * \param[in]   addr            The IP address of the PC where UDP host is running.
 *                              This parameter is used only when the output stream is
 *                              \ref TRC_STREAM_UDP_IP.
 * \param[in]   port            The port number where the UDP host is listening.
 *                              This parameter is only used when the output stream is
 *                              \ref TRC_STREAM_UDP_IP.
 * \param[in]   tlmTrcID        The assigned telium trace ID when using the Native Telium
 *                              trace tool. This paramter is only used when the output
 *                              stream is set to \ref TRC_STREAM_TELIUM_TRACE.
 * \return
 *      - \ref TRC_OK = The trace output stream has been successfully set.
 *      - \ref TRC_ERR_FILESYSTEM_OPEN = The trace file cannot be openned for writing.
 *      - \ref TRC_ERR_FILESYSTEM_MOUNT = The volume cannot be mounted.
 *      - \ref TRC_ERR_UDP_CONNECT = The trace module could not connect to the UDP host.
 *
 * \note
 *      - The parameters for file output streams cannot be set at the same time. That is, the
 *        the parameters for TRC_STREAM_INT_FILE, TRC_STREAM_EXT_FILE_USB1, and TRC_STREAM_EXT_FILE_MMC
 *        should be set separately. This requires calling \ref TRC_OutputSet() separately.
 *      - See the snippet of \ref TRC_Test0000() below:
 * \include trcTest0000.c
 */
int TRC_OutputSet(
                        const unsigned int outputStream,
                        const char * dst, 
                        const char *addr, 
                        unsigned short port, 
                        unsigned int tlmTrcID
                      );

/** \brief Sets the maximum size of the trace file. 
 *
 * When the size of the file reach this limit, the writing of traces will restart at the beginning of the file.
 *
 * \param[in] maxSize  The maximum size of trace file desired.
 * \param[in] stm      The stream to set applicable to file streams only.
 *
 * \return
 *      The size that has been set. For outputs stream using terminal's flash, when the desired maximum size is greater than the
 *      available size of the free area, then the size of the free area is returned
 *      and that this size will be set instead of the requested size. For other output stream using external storage, there is no
 *      special return value due to limited Telium SDK API. The Telium SDK does not have an API to determine the remaining free
 *      area of the external storage.
 *
 * \note
 *      The default value of the maximum limit when this function is not called
 *      is 32KB.
 * \note
 *      - See the snippet of \ref TRC_Test0002() below:
 * \include trcTest0002.c
 */
int TRC_MaxFileSizeSet( unsigned int  maxSize, TRC_OutputStream_t stm);

/** @} */
/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif
