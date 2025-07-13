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

 @file      trcTest.h
 @brief     This file provides the API for Trace Module Unit Tests.
 @date      06/12/2012

 ------------------------------------------------------------------------------
 */
#ifndef __TRC_TEST_H__
#define __TRC_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup TRC
 *
 * @{
 */

/** \weakgroup TRC_UnitTest TRC Unit Test
 * 
 * List of TRC Unit Tests. The last 4 digits represents the test number to be
 * specified in function \ref TRC_TestRun().
 *
 * @{
 */


/** \weakgroup TRC_UnitTestList TRC Unit Test List
 * 
 * List of TRC Unit Tests. The last 4 digits represents the test number to be
 * specified in function \ref TRC_TestRun().
 *
 * @{
 */

/** \brief Create a TRC category and use the Remote Debug output stream.
 *
 *  \par Test Prerequisites:
 *      The application should be debugged in GNU_ARM_DEBUG configuration.
 *
 *  \par Expected Result:
 *      Traces should appear on the outstream console which
 *      is the remote debugging console of Ingedev. Below are sample traces:
 *  \code  
15:25:48.78 ERR     0x0 TEST0000 Src/trcTest.c:48	String: This is my String 100
15:25:48.79 WARNING 0x0 TEST0000 Src/trcTest.c:49	String: This is my String 200
15:25:48.80 INFO    0x0 TEST0000 Src/trcTest.c:50	String: This is my String 300
15:25:48.81 DEBUG   0x0 TEST0000 Src/trcTest.c:51	String: This is my String 400
 *  \endcode 
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0000(void);

/** \brief Tracing for a specific category is TURNED OFF.
 *
 *      Remote Debug output stream is used in this scenario.
 *
 *  \par Test Prerequisites:
 *      The application should be debugged in GNU_ARM_DEBUG configuration.
 *
 *  \par Expected Result:
 *      Traces should appear on the outstream console which
 *      is the remote debugging console of Ingedev. Below are sample traces:
 *  \code 
15:15:32.17 ERR     0x0 TEST0001B Src/trcTest.c:89	String: This is my String 100
15:15:32.18 WARNING 0x0 TEST0001B Src/trcTest.c:90	String: This is my String 200
15:15:32.19 INFO    0x0 TEST0001B Src/trcTest.c:91	String: This is my String 300
15:15:32.20 DEBUG   0x0 TEST0001B Src/trcTest.c:92	String: This is my String 400
 *  \endcode 
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0001(void);

/** \brief Tracing on a file stored on a USB key.
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session
 *      or standalone with a USB key inserted on its USB port. Any USB key
 *      can be used.
 *
 *  \par Expected Result:
 *      Traces should be sent and stored on the USB key. File name is to look for in the usb is: \b TEST0002TRC. Below are sample traces:
 *  \code 
17:26:33.35 ERR     0x0 TEST0002 Src/trcTest.c:119	String: This is my String 100
17:26:33.36 WARNING 0x0 TEST0002 Src/trcTest.c:120	String: This is my String 200
17:26:33.37 INFO    0x0 TEST0002 Src/trcTest.c:121	String: This is my String 300
17:26:33.38 DEBUG   0x0 TEST0002 Src/trcTest.c:122	String: This is my String 400
 *  \endcode 
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0002(void);

/** \brief Tracing on the printer.
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session
 *      or standalone.
 *
 *  \par Expected Result:
 *      Traces should be printed on the terminal. Below are sample traces:
 *  \code 
17:26:33.35 ERR     0x0 TEST0003 Src/trcTest.c:119	String: This is my String 100
17:26:33.36 WARNING 0x0 TEST0003 Src/trcTest.c:120	String: This is my String 200
17:26:33.37 INFO    0x0 TEST0003 Src/trcTest.c:121	String: This is my String 300
17:26:33.38 DEBUG   0x0 TEST0003 Src/trcTest.c:122	String: This is my String 400
 *  \endcode 
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0003(void);

/** \brief Test the maximum low level buffer of the printer is exceeded by the
 *      traces sent to the printer. 
 *
 *      The SDK API allows only 128 bytes.
 *      However, the TRC module manages this limitation to allow more
 *      than 128 bytes to be passed to TRC module.
 *
 *  \par Test Prerequisites:
 *      The application can be run either in remote debugging session or
 *      stand alone. Make sure a paper has been properly set.
 *
 *  \par Expected Result:
 *      Traces should be printed on the terminal. Below are sample traces:
 *  \code  
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
 *  \endcode 
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0004(void);

/** \brief Makes sure that new line characters are properly handled internally
 *      by the TRC printer output stream processor.
 *
 *  \par Test Prerequisites:
 *      The application can be run either in remote debugging session or
 *      stand alone. Make sure a paper has been properly set.
 *
 *  \par Expected Result:
 *      Traces should be printed on the terminal. Below are sample traces:
 *  \code  
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
0123456789012345678901
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
012345678901234567890123456789012345678901234567
 *  \endcode 
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0005(void);

/** \brief Tracing on a file stored on the terminal.
 *
 *  \par Test Prerequisites:
 *      The application can be run either in remote debugging session or
 *      stand alone.
 *
 *  \par Expected Result:
 *      Traces should be sent and stored on the Internal file system of the terminal. It can be found at: /HOST/TEST0006TRC.txt on LLT. 
 *      Below are sample traces:
 *  \code 
17:26:33.35 ERR     0x0 TEST0006 Src/trcTest.c:119	String: This is my String 100
17:26:33.36 WARNING 0x0 TEST0006 Src/trcTest.c:120	String: This is my String 200
17:26:33.37 INFO    0x0 TEST0006 Src/trcTest.c:121	String: This is my String 300
17:26:33.38 DEBUG   0x0 TEST0006 Src/trcTest.c:122	String: This is my String 400
 *  \endcode 
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0006(void);

/** \brief Tracing on a UDP channel running somewhre in the LAN.
 *
 *  \par Test Prerequisites:
 *      The application can be run either in remote debugging session or
 *      stand alone. Make sure that the UDP port 6000 was properly openned.
 *
 *  \par Expected Result:
 *      Traces should be appear on the UDP server. Below are sample traces:
 *  \code 
17:26:33.35 ERR     0x0 TEST0007 Src/trcTest.c:119	String: This is my String 100
17:26:33.36 WARNING 0x0 TEST0007 Src/trcTest.c:120	String: This is my String 200
17:26:33.37 INFO    0x0 TEST0007 Src/trcTest.c:121	String: This is my String 300
17:26:33.38 DEBUG   0x0 TEST0007 Src/trcTest.c:122	String: This is my String 400
 *  \endcode 
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0007(void);

/** \brief Invalid usage of tracing. 
 *
 * An invalid pointer has been passed to TRC_Trace().
 *
 *  \par Test Prerequisites:
 *      The application can be run in remote debugging session or stand alone.
 *
 *  \par Expected Result:
 *      There will be no traces sent to the output stream. 
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0008(void);

/** \brief Tracing on Telium trace tool.
 *
 *  \par Test Prerequisites:
 *      The application can be run either in remote debugging session or
 *      stand alone. 
 *
 *  \par Expected Result:
 *      Traces should appear on the Telium Trace tool. Below are sample traces:
 *
 *  \code 
17:26:33.35 ERR     0x0 TEST0009 Src/trcTest.c:119	String: This is my String 100
17:26:33.36 WARNING 0x0 TEST0009 Src/trcTest.c:120	String: This is my String 200
17:26:33.37 INFO    0x0 TEST0009 Src/trcTest.c:121	String: This is my String 300
17:26:33.38 DEBUG   0x0 TEST0009 Src/trcTest.c:122	String: This is my String 400
 *  \endcode
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0009(void);


/** \brief Tracing on ALL output streams.
 *
 *  \par Test Prerequisites:
 *      The application should be in remote debugging session.  ALL Output streams should be available and ready.
 *
 *  \par Expected Result:
 *      Traces should be sent to ALL output streams. The following output streams should receive traces:
 *
 * - Remote debugging console of INGEDEV
 * - Telium Trace Tool
 * - UDP Server
 * - Internal File System of the Terminal
 * - USB
 * - MMC
 * - Terminal printer
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0010(void);


/** \brief Test OUT OF PAPER scenario when output stream is PRINTER.
 *
 *  \par Test Prerequisites:
 *      Remove the paper in the terminal's printer.
 *  \par Expected Result:
 *      The TRC module should return an OUT OF PAPER error code.
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0011(void);

/** \brief Tracing on ALL output streams except on Telium Trace tool
 *
 *  \par Test Prerequisites:
 *      The application should be in remote debugging session.  ALL Output streams should be available and ready.
 *
 *  \par Expected Result:
 *      Traces should be sent to ALL output streams except on Telium Trace tool. The following output streams should receive traces:
 *
 * - Remote debugging console of INGEDEV
 * - UDP Server
 * - Internal File System of the Terminal
 * - USB
 * - MMC
 * - Terminal printer
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0012(void);


/** \brief Tracing on ALL output streams except on Internal File
 *
 *  \par Test Prerequisites:
 *      The application should be in remote debugging session.  ALL Output streams should be available and ready.
 *
 *  \par Expected Result:
 *      Traces should be sent to ALL output streams except on Internal File. The following output streams should receive traces:
 *
 * - Remote debugging console of INGEDEV
 * - UDP Server
 * - Telium Trace Tool
 * - USB
 * - MMC
 * - Terminal printer
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0013(void);


/** \brief Tracing on ALL output streams except on USB
 *
 *  \par Test Prerequisites:
 *      The application should be in remote debugging session.  ALL Output streams should be available and ready.
 *
 *  \par Expected Result:
 *      Traces should be sent to ALL output streams except on USB. The following output streams should receive traces:
 *
 * - Remote debugging console of INGEDEV
 * - UDP Server
 * - Internal File System of the Terminal
 * - Telium Trace Tool
 * - MMC
 * - Terminal printer
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0014(void);


/** \brief Tracing on ALL output streams except on UDP channel
 *
 *  \par Test Prerequisites:
 *      The application should be in remote debugging session.  ALL Output streams should be available and ready.
 *
 *  \par Expected Result:
 *      Traces should be sent to ALL output streams except on UDP Channel. The following output streams should receive traces:
 *
 * - Remote debugging console of INGEDEV
 * - Telium Trace Tool
 * - Internal File System of the Terminal
 * - USB
 * - MMC
 * - Terminal printer
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0015(void);


/** \brief Tracing on ALL output streams except on the terminal's printer.
 *
 *  \par Test Prerequisites:
 *      The application should be in remote debugging session.  ALL Output streams should be available and ready.
 *
 *  \par Expected Result:
 *      Traces should be sent to ALL output streams except on Terminal's Printer. The following output streams should receive traces:
 *
 * - Remote debugging console of INGEDEV
 * - UDP Server
 * - Internal File System of the Terminal
 * - USB
 * - MMC
 * - Telium Trace Tool
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0016(void);

/** \brief Tracing on the PRINTER with a very large buffer.
 *
 *  \par Test Prerequisites:
 *      The application can be run either in remote debugging session or
 *      stand alone. 
 *
 *  \par Expected Result:
 *      There should be traces printed on the receipt containing 81 lines
 *      of the string "012345678901234567890123456789012345678901234567".
 *      There should be no errors encountered.
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0017(void);

/** \brief Test OUT OF PAPER while printing a very large trace.
 *
 *  \par Test Prerequisites:
 *      Put a paper small enough not to contain 81 lines.
 *  \par Expected Result:
 *      When the printer is out of paper
 *      terminal should display test is OK.
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0018(void);

/** \brief Test that makes sure a NULL trace is handled properly by the \ref TRC_Trace()
 * function.
 *
 *  \par Test Prerequisites:
 *      None.
 *  \par Expected Result:
 *      Trace should only contain the trace header.
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0019(void);

/** \brief Test that makes sure that trace levels turned OFF should not
 * be traced.
 *
 *  \par Test Prerequisites:
 *      None.
 *  \par Expected Result:
 *      Trace levels that are turned ON should only be the traces seen.
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0020(void);

/** \brief Test that tests the cyclic mechanism of internal file.
 *
 *  \par Test Prerequisites:
 *      None.
 *  \par Expected Result:
 *      Trace file size should not exceed the maximum size set.
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0021(void);

/** \brief Test that tests the cyclic mechanism of external file - USB1.
 *
 *  \par Test Prerequisites:
 *      None.
 *  \par Expected Result:
 *      Trace file size should not exceed the maximum size set.
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0022(void);

/** \brief Test that tests the cyclic mechanism of external file - MMC.
 *
 *  \par Test Prerequisites:
 *      None.
 *  \par Expected Result:
 *      Trace file size should not exceed the maximum size set.
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0023(void);

/** \brief Performance test for the telium internal file output stream
 *
 * Iteration is 20,000 
 *
 *  \par Test Prerequisites:
 *      None.
 *  \par Expected Result:
 *      The averaged time should not exceed:
 *      - 2.28ms on ICTXXX terminals
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0024(void);

/** \brief Performance test for the USB output stream.
 *
 * Iteration is 500
 *
 *  \par Test Prerequisites:
 *      None.
 *  \par Expected Result:
 *      The averaged time should not exceed:
 *      - 2.28ms on ICTXXX terminals
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0025(void);

/** \brief Performance test for the external file microSD output stream.
 *
 * Iteration is 500
 *
 *  \par Test Prerequisites:
 *      None.
 *  \par Expected Result:
 *      The averaged time should not exceed:
 *      - 2.28ms on ICTXXX terminals
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0026(void);

/** \brief Performance test for the remote debug output stream.
 *
 * Iteration is 20,000 
 *
 *  \par Test Prerequisites:
 *      This test must be performed in a remote debugging session.
 *  \par Expected Result:
 *      The averaged time should not exceed:
 *      - 2.28ms on ICTXXX terminals
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0027(void);

/** \brief Performance test for the printer output stream.
 *
 * Iteration is 40
 *
 *  \par Test Prerequisites:
 *      None.
 *  \par Expected Result:
 *      The averaged time should not exceed:
 *      - 2.28ms on ICTXXX terminals
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0028(void);

/** \brief Performance test for the UDP/IP output stream.
 *
 * Iteration is 20,000 
 *
 *  \par Test Prerequisites:
 *      UDP/IP host should be listening.
 *  \par Expected Result:
 *      The averaged time should not exceed:
 *      - 2.28ms on ICTXXX terminals
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0029(void);

/** \brief Performance test for the native telium trace output stream.
 *
 * Iteration is 20,000 
 *
 *  \par Test Prerequisites:
 *      Native Telium Trace Tool should be running and listening.
 *  \par Expected Result:
 *      The averaged time should not exceed:
 *      - 2.28ms on ICTXXX terminals
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int TRC_Test0030(void);



/** @} */

/** \weakgroup TRC_UnitTestAPI Unit Test API
 * 
 * List of functions that serves as an interface to run the tests using the Test Library.
 *
 * @{
 */

/** \brief The callback function to specify when running its tests using the TEST library.
 *
 *  The test numbers implemented are from test 0 to test 8. See \ref
 *
 *  \param[in]  testNum     The test number to be executed.
 *  \param[in]  testStatus  0: Executing, 1:Finished
 *
 *  \return
 *      - TEST_OK = Test executed correctly.
 *      - TEST_FAILED = Test failed.
 *      - TEST_ERR_TEST_NUM_NOT_IMPLEMENTED = The test number specified was not implemented.
 */
int TRC_TestRun(int testNum, int(*testStatusCb)(int testNum, int testResult, const char *moduleName, unsigned char status));

/** \brief The callback function to configure the module tests.
 *
 *  The test numbers implemented are from test 0 to test 8. See \ref
 *
 *  \param[in]  testNum     Unused.
 *  \param[in]  testStatus  0: Executing, 1:Finished
 *
 *  \return
 *      - TEST_OK = Test executed correctly.
 *      - TEST_FAILED = Test failed.
 *      - TEST_ERR_TEST_NUM_NOT_IMPLEMENTED = The test number specified was not implemented.
 */
int TRC_TestCfg(int testNum, int(*testStatusCb)(int testNum, int testResult, const char *moduleName, unsigned char status));


/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif
