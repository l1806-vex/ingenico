/*!
 ------------------------------------------------------------------------------
                  INGENICO Technical Software Department 
 ------------------------------------------------------------------------------
 Copyright (c) 2013, Ingenico.
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
 Module  : PAR - Parameter Module

 @file      parTest.h
 @brief     This file provides the API for Parameter Module Unit Tests.
 @date      09/1/2013

 ------------------------------------------------------------------------------
 */
#ifndef __PAR_TEST_H__
#define __PAR_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup PAR
 *
 * @{
 */

/** \weakgroup PAR_UnitTest PAR Unit Test
 * 
 * List of PAR Unit Tests. The last 4 digits represents the test number to be
 * specified in function \ref PAR_TestRun().
 *
 * @{
 */


/** \weakgroup PAR_UnitTestList PAR Unit Test List
 * 
 * List of PAR Unit Tests. The last 4 digits represents the test number to be
 * specified in function \ref PAR_TestRun().
 *
 * @{
 */

/**  \brief  Test Import functionality
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      Import function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0000(void);

/**  \brief  Test READONLY Access of a parameter data
 *
 *  \par Test Prerequisites:
 *     The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      GET function will be allowed and successfully performed
 *
 *      SET function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0001(void);

/**  \brief  Test READWRITE Access of an alphanumeric parameter data
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      GET function will be allowed and successfully performed
 *
 *      SET function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0002(void);

/**  \brief  Test READWRITE Access of a numeric parameter data
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      GET function will be allowed and successfully performed
 *
 *      SET function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0003(void);

/**  \brief  Test choiceField SET and GET functionality
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      GET function will be allowed and successfully performed
 *
 *      SET function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0004(void);


/**  \brief  Test structureField SET and GET functionality
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      GET function will be allowed and successfully performed
 *
 *      SET function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0005(void);

/**  \brief  Export data structure to parameter file
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      GET function will be allowed and successfully performed
 *
 *      SET function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0006(void);

/**  \brief  Invalid data Test
 *
 *  \par Test Prerequisites:
 *     The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      Import function will be allowed and successfully performed
 *
 *      SET function will return PAR_INVALID_DATA
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0007(void);

/**  \brief  Invalid data lenght Test
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      Import function will return PAR_INVALID_DATA_LEN
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0008(void);

/**  \brief  Import test using an invalid filename
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      Import function will return PAR_ERROR_FILE_ACCESS
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0009(void);

/**  \brief  Export test
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      Export function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0010(void);

/**  \brief 1st test for power failure, initialize default data
 *
 *  \par Test Prerequisites:
 *      Import function will be allowed and successfully performed
 *
 *  \par Expected Result:
 *      Import function will return PAR_ERROR_FILE_ACCESS
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0011(void);

/**  \brief 2nd test for power failure, set new data before restart
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      SET function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0012(void);

/**  \brief 3nd test for power failure, check validity of saved data
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      GET function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0013(void);

/**  \brief 4th test for power failure, set new data before 2nd restart
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      SET function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0014(void);

/**  \brief 5th test for power failure, check validity of saved data
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      GET function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0015(void);

/**  \brief Pre-requisite test for \ref PAR_Test0017.
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      GET function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0016(void);

/**  \brief Test export without the internal parameter file stored.
 *
 *  \par Test Prerequisites:
 *      The application can be run either in a remote debugging session or standalone 
 *
 *  \par Expected Result:
 *      GET function will be allowed and successfully performed
 *
 *  \return
 *      - \ref TEST_OK        = Test OK.
 *      - \ref TEST_FAILED    = Test FAILED.
 */
int PAR_Test0017(void);

/** @} */

/** \weakgroup PAR_UnitTestAPI Unit Test API
 * 
 * List of functions that serves as an interface to run the tests using the Test Library.
 *
 * @{
 */

/** The callback function to specify when running its tests using the TEST library.
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
int PAR_TestRun(int testNum, int(*testStatusCb)(int testNum, int testResult, const char *moduleName, unsigned char status));

/** \brief The callback function to configure the parameter tests.
 * The test copies the PAR file from after_reset and creates a copy of the parameter file
 * for Test case Imports to restore the database to its original data
 *
 *  \param[in]  buf  data to be written
 *  \param[in]  len  size of the data to be written
 *
 *  \return
 *      - TEST_OK = Test executed correctly.
 *      - TEST_FAILED = Test failed.
 */
int PAR_TestCfg(char * buf, int len);

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif
