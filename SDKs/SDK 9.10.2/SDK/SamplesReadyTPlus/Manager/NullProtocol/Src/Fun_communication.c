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

 Project : Null Protocol  Sample
 Module  : FUN - Demo Features Unit

 @file      Fun_communication.c
 @brief     Contains definition functions for Null Protocol demo features.
 @date      03/10/2013

 ------------------------------------------------------------------------------
 */

#include "sdk30.h"
#include "fun_communication.h"
#include "LinkLayer.h"
#include "err_process.h"
#include "TlvTree.h"
#include "trc.h"
#include "trace.h"
#include "par.h"
#include "utilities.h"

/* Task number of M2OS */
static unsigned short m2os_task;
/* link layer handle */
static LL_HANDLE pvComSession;

/** Set task manager number
 * \param[in] unsigned short task manager number
 *
 */
void FUN_Set_ManagerTask(unsigned short task)
{
   m2os_task = task;
}
/** Get task manager number
 *\return
 *         unsigned short task manager number
 *
 */
unsigned short FUN_Get_ManagerTask(void)
{
   return m2os_task;
}

/** Dump received data from serial connection  on PRINTER
 * \param[in] unsigned char *Header data header to be printed
 * \param[in] unsigned char *String data to be printed
 * \param[in] unsigned long Number data length to e printed
 */
void _FUN_HexDump(unsigned char *Header, unsigned char *String, unsigned long Number)
{
   unsigned char Line[100];
   unsigned char Buf[10];
   unsigned long i;
   unsigned long j;

   printText("****************************************************\n");
   printText((char *) Header);
   printText("\n**************************************************\n");
   for (i = 0; i < Number; i += 6)
   {
      memset(Line, ' ', 24);
      Line[24] = '\0';
      for (j = i; j < Number && j < (i + 6); j++)
      {
         sprintf((char *) Buf, "%02X ", String[j]);
         memcpy(&Line[(j - i) * 3], Buf, 3);
         if (String[j] <= 125 && String[j] >= 32)
         {
            Line[18 + (j - i)] = String[j];
         }
         else
         {
            Line[18 + (j - i)] = '.';
         }
      }
      printText((char *) Line);
      printText(" \n");
   }
   printText("\n\n");
   printDocument();

}
/** Initialize and connect over the serial communication.The connection
 *  is performed over COM0/COM1/COM2 port defined in PAR file.
 *        LL_Configure() : Create Link Layer configuration
 *        LL_Connect() : Connect Link Layer
 * \param[in] char *pucMsg Data to send
 * \param[in] word usLen Number of byte to send
 * \return int
 *         >=0 : Initialization done
 *         <0 : Initialization failed
 */
static int _FUN_ComSetSerial(void)
{
   // Local variables
   TLV_TREE_NODE hConfig = NULL;
   TLV_TREE_NODE hPhysicalConfig = NULL;
   int iRet = 0;
   int portNum;
   int portSpeed;
   /* trace instance*/
   TRC_Trace_t trc_fun;
   trc_fun = TRC_HandleGet();
   // Needed to call the link layer
   hConfig = TlvTree_New(LL_TAG_LINK_LAYER_CONFIG);

   // Physical layer parameters
   hPhysicalConfig = TlvTree_AddChild(hConfig, LL_TAG_PHYSICAL_LAYER_CONFIG, NULL, 0);

   iRet = PAR_PortNumGet(&portNum);
   if (iRet != PAR_OK)
   {
      /*No Par file found*/
      UI_ErrMsgDisplay(ERR_PAR_FILE_NOT_FOUND);
      return -1;
   }
   //tag physical layer
   TlvTree_AddChildInteger(hPhysicalConfig, LL_PHYSICAL_T_LINK, portNum, LL_PHYSICAL_L_LINK);
   iRet = PAR_PortSpeedGet(&portSpeed);
   if (iRet != PAR_OK)
   {
      /*No Par file found*/
      UI_ErrMsgDisplay(ERR_PAR_FILE_NOT_FOUND);
      return -1;
   }
   //tag Baudrate
   TlvTree_AddChildInteger(hPhysicalConfig, LL_PHYSICAL_T_BAUDRATE, portSpeed, LL_PHYSICAL_L_BAUDRATE);

   //tag nb byte
   TlvTree_AddChildInteger(hPhysicalConfig, LL_PHYSICAL_T_BITS_PER_BYTE, LL_PHYSICAL_V_8_BITS, LL_PHYSICAL_L_BITS_PER_BYTE);

   //tag stop bit
   TlvTree_AddChildInteger(hPhysicalConfig, LL_PHYSICAL_T_STOP_BITS, LL_PHYSICAL_V_1_STOP, LL_PHYSICAL_L_STOP_BITS);

   //tag parity
   TlvTree_AddChildInteger(hPhysicalConfig, LL_PHYSICAL_T_PARITY, LL_PHYSICAL_V_NO_PARITY, LL_PHYSICAL_L_PARITY);

   //tag flow control
   TlvTree_AddChildInteger(hPhysicalConfig, LL_PHYSICAL_T_FLOW_CTRL, LL_PHYSICAL_V_NO_FLOW_CTRL, LL_PHYSICAL_L_FLOW_CTRL);

   // Link Layer configuration
   // ************************
   iRet = LL_Configure(&pvComSession, hConfig);

   // Release the LinkLayer configuration parameters tree
   // ***************************************************
   TlvTree_Release(hConfig);

   // Link Layer connection
   // *********************
   iRet = LL_Connect(pvComSession);
   if ((iRet == LL_ERROR_OK) || (iRet == LL_ERROR_ALREADY_CONNECTED))
   {
      TRC_TRACE_INFO(trc_fun, "COM%i CONNECTED", portNum);
      return iRet;
   }
   else
      return -1;
}
/** Close the RS232 interface.
 *        LL_Configure() : Delete Link Layer configuration
 * \return int
 *        >=0 : RS232 configuration deleted
 *         <0 : Processing failed
 */
static int _FUN_ComStop(void)
{
   // Local variables
   // ***************
   int iRet;

   // Delete the configuration
   // ************************
   iRet = LL_Configure(&pvComSession, NULL);

   return iRet;
}

/** Send data over the serial communication port.
 *        LL_ClearSendBuffer() : Clear sending buffer
 *        LL_Send() : Send data
 *        LL_GetLastError() : Retrieve the last error
 * \param[in] char *pucMsg Data to send
 * \param[in] word usLen Number of byte to send
 * \return int
 *        >=0 : Number of bytes sent
 *         <0 : Transmission failed
 */
static int _FUN_ComSendBuf(char *pucMsg, word usLen)
{
   // Local variables
   // ***************
   int iRet;

   // Clear sending buffer
   // ********************
   iRet = LL_ClearSendBuffer(pvComSession);

   // Send data
   // *********
   iRet = LL_Send(pvComSession, usLen, pucMsg, LL_INFINITE);
   if (iRet != usLen)
   {
      iRet = LL_GetLastError(pvComSession);
   }

   return iRet;
}

/** Receive data over the serial communication port.
 *        LL_ClearReceiveBuffer() : Clear receiving buffer
 *        LL_Receive() : Wait and receive data
 *        LL_GetLastError() : Retrieve the last error
 * \param[out] char *pucMsg Data to receive
 * \param[in] word usLen Maximum number of bytes to receive
 * \param[in] ucDly Timeout reception (in second, 0xFF infinite)
 * \return int
 *        >=0 : Number of bytes received
 *         <0 : Reception failed
 */
static int _FUN_ComReceiveBuf(char *pucMsg, word usLen, byte ucDly)
{
   // Local variables
   // ***************
   int iRet, iLength = 0, iSec, iNbrBytes;

   // Timeout setting
   // ***************
   if (ucDly != 0xFF)
      iSec = ucDly * 100;
   else
      iSec = LL_INFINITE;

   // Clear receiving buffer
   // **********************
   iRet = LL_ClearReceiveBuffer(pvComSession);

   // Receiving first block
   // *********************
   iNbrBytes = LL_Receive(pvComSession, usLen, pucMsg + iLength, iSec);
   iLength += iNbrBytes;
   iRet = LL_GetLastError(pvComSession);
   if (iNbrBytes != 0)
   {
      // Receiving next block until timeout (Inter block 50ms)
      // =====================================================
      while (1)
      {
         iNbrBytes = LL_Receive(pvComSession, usLen - iLength, pucMsg + iLength, 50);
         iLength += iNbrBytes;
         iRet = LL_GetLastError(pvComSession);
         if (iRet == LL_ERROR_TIMEOUT)
            break;
         if (iNbrBytes == 0)
            break;
      }
   }

   iRet = iLength;
   return iRet;
}
/** Perform Serial communication configuration,
 *  receive data from serial COM, sends back "OK"
 *  and print data received.
 *
 */
void FUN_Task_Protocol(void)
{
   char data[1024]; /* To read from serial link                      */
   unsigned int len; /* Length of data received                       */
   int iRet;
   // Task is now operational
   SignalEvent(m2os_task, EVT_SYNCHRO_DIALOG);
   // RS232 configuration
   iRet = _FUN_ComSetSerial();
   if (iRet == -1)
      return;
   while (1)
   {
      len = _FUN_ComReceiveBuf(data, sizeof(data), 30);
      if (len != 0)
      {
         _FUN_HexDump((unsigned char *) "DATA RECEIVED", (unsigned char *) data, len);
      }
      _FUN_ComSendBuf("OK", 2);
   }
   _FUN_ComStop();
}

