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

 Project : Fun_DualSim  Sample
 Module  : FUN - Demo Features Unit

 @file      Fun_DualSim.c
 @brief     Contains all definitions of functions utilized for Dual Sim.
 @date      04/16/2013

 ------------------------------------------------------------------------------
 */

#include "sdk30.h"
#include <GL_GraphicLib.h>
#include "TlvTree.h"
#include "LinkLayer.h"
#include "GTL_Traces.h"
#include "Fun_DualSim.h"
#include "trace.h"
#include "par.h"
#include "Utilities.h"
#include "err_process.h"

typedef struct
{
   char* m_szTest;
   unsigned long m_nSlotId;
   char* m_szPinCode;
   char* m_szAPN;
   char* m_szHostName;
   unsigned long m_nPort;
} T_GPRS_TEST_SETTINGS;

/** Configure a TCP communication.
 *
 *\param[in] const char* szIp.
 *\param[in] unsigned int nPort.
 *
 *\return TLV_TREE_NODE
 *
 */
static TLV_TREE_NODE _FUN_GetGprsConfiguration(const char* szIp, unsigned int nPort)
{
   TLV_TREE_NODE hConfig;
   TLV_TREE_NODE hPhysicalLayer;
   TLV_TREE_NODE hTransportLayer;

   hConfig = TlvTree_New(LL_TAG_LINK_LAYER_CONFIG);

   if (hConfig != NULL)
   {
      hPhysicalLayer = TlvTree_AddChild(hConfig, LL_TAG_PHYSICAL_LAYER_CONFIG, NULL, 0);
      TlvTree_AddChildInteger(hPhysicalLayer, LL_PHYSICAL_T_LINK, LL_PHYSICAL_V_GPRS, LL_PHYSICAL_L_LINK);
      hTransportLayer = TlvTree_AddChild(hConfig, LL_TAG_TRANSPORT_LAYER_CONFIG, NULL, 0);
      TlvTree_AddChildInteger(hTransportLayer, LL_TRANSPORT_T_PROTOCOL, LL_TRANSPORT_V_TCPIP, LL_TRANSPORT_T_PROTOCOL);
      TlvTree_AddChildString(hTransportLayer, LL_TCPIP_T_HOST_NAME, szIp);
      TlvTree_AddChildInteger(hTransportLayer, LL_TCPIP_T_PORT, nPort, LL_TCPIP_L_PORT);
      TlvTree_AddChildInteger(hTransportLayer, LL_TCPIP_T_CONNECT_TIMEOUT, 60 * 100, LL_TCPIP_L_CONNECT_TIMEOUT);
   }

   return hConfig;
}
/** Send and receive TCP request over GPRS/3G connexion.
 *
 *\param[in] const char* szIp.
 *\param[in] unsigned int nPort.
 *
 *
 */
static void _FUN_TestTcp(const char* szIp, unsigned int nPort)
{
   TLV_TREE_NODE hConfig;
   LL_HANDLE hSession = NULL;
   int nError;
   unsigned char pucBuffer[256];
   const char* HTTP_REQUEST = "GET / HTTP/1.0\r\n\r\n";
   int nBytes;
   TRC_Trace_t trc_fun; /* trace instance*/
   char message[100];
   hConfig = _FUN_GetGprsConfiguration(szIp, nPort);
   trc_fun = TRC_HandleGet();
   if (hConfig != NULL)
   {
      if (LL_Configure(&hSession, hConfig) == LL_ERROR_OK)
      {
         nError = LL_Connect(hSession);
         if ((nError == LL_ERROR_OK) || (nError == LL_ERROR_ALREADY_CONNECTED))
         {
            TRC_TRACE_INFO(trc_fun, "TCP Connected");
            sprintf(message, "connected to host: %s ", szIp);
            guiScreen("Dual Sim", message, GL_ICON_NONE, 3000);
            LL_Send(hSession, strlen(HTTP_REQUEST), HTTP_REQUEST, 100);

            do
            {

               nBytes = LL_Receive(hSession, sizeof(pucBuffer), pucBuffer, 1000);
            } while (nBytes > 0);

            LL_Disconnect(hSession);
         }
         else
         {
            sprintf(message, "Failed to connect to host: %s ", szIp);
            guiScreen("Dual Sim", message, GL_ICON_NONE, 3000);
         }

         LL_Configure(&hSession, NULL);
      }

      TlvTree_Release(hConfig);
   }
}

/** Establish GPRS connexion.
 *
 *\param[in] const char* szPinCode.
 *\param[in] unsigned int szApn.
 *\param[in] unsigned int nWaitTimeout.
 *\param[in] unsigned int nWaitMaxTimeout
 *\return int connexion state
 */
int _FUN_ConnectNetworkGPRS(const char* szPinCode, const char* szApn, unsigned int nWaitTimeout, unsigned int nWaitMaxTimeout)
{
   unsigned int nWaitTotal = 0;
   int nError = 0;
   int nStatus;
   int bExit = FALSE;
   TRC_Trace_t trc_fun; /* trace instance*/

   trc_fun = TRC_HandleGet();

   // Start the GPRS/3G network.
   LL_GPRS_Start(szPinCode, szApn);

   do
   {
      if (nWaitTotal < nWaitMaxTimeout)
      {
         nError = LL_Network_GetStatus(LL_PHYSICAL_V_GPRS, &nStatus);

         if (nError == LL_ERROR_NETWORK_NOT_READY)
         {
            // Normal case.
            if (nStatus == LL_STATUS_GPRS_AVAILABLE)
            {
               // The GPRS/3G network is available. Perform the connection.
               LL_GPRS_Connect(szApn, "", "", nWaitMaxTimeout - nWaitTotal);
            }
            else
            {
               ttestall(0, nWaitTimeout);
               nWaitTotal += nWaitTimeout;
            }
         }
         else
         {
            // Due to SIM switch, we might be in this case.
            if ((nError == LL_ERROR_NETWORK_ERROR) && (nStatus == LL_STATUS_GPRS_ERROR_NO_SIGNAL))
            {
               ttestall(0, nWaitTimeout);
               nWaitTotal += nWaitTimeout;
            }
            else
            {
               bExit = TRUE;
            }
         }
      }
      else
      {
         // Timeout.
         bExit = TRUE;
      }

   } while (bExit == FALSE);

   // Display the status.
   switch (nError)
   {
      case LL_ERROR_OK:
         TRC_TRACE_INFO(trc_fun, "GPRS Connected !");
         break;

      case LL_ERROR_NETWORK_NOT_SUPPORTED:
         TRC_TRACE_INFO(trc_fun, "GPRS Network Not supported !");
         break;

      default:
      {
         switch (nStatus)
         {
            case LL_STATUS_GPRS_DISCONNECTED:
               TRC_TRACE_INFO(trc_fun, "GPRS Disconnected !");
               break;
            case LL_STATUS_GPRS_ERROR_NO_SIM:
               TRC_TRACE_INFO(trc_fun, "NO SIM !");
               break;
            case LL_STATUS_GPRS_ERROR_SIM_LOCK:
               TRC_TRACE_INFO(trc_fun, "SIM Lock!");
               break;
            case LL_STATUS_GPRS_ERROR_BAD_PIN:
               TRC_TRACE_INFO(trc_fun, "Bad PIN!");
               break;
            case LL_STATUS_GPRS_ERROR_NO_PIN:
               TRC_TRACE_INFO(trc_fun, "NO PIN!");
               break;
            case LL_STATUS_GPRS_ERROR_PPP:
               TRC_TRACE_INFO(trc_fun, "PPP Error!");
               break;
            case LL_STATUS_GPRS_ERROR_UNKNOWN:
               TRC_TRACE_INFO(trc_fun, "Unknown Error!");
               break;
            case LL_STATUS_GPRS_CONNECTING:
               TRC_TRACE_INFO(trc_fun, "Connecting...!");
               break;
            case LL_STATUS_GPRS_AVAILABLE:
               TRC_TRACE_INFO(trc_fun, "GPRS available...!");
               break;
            case LL_STATUS_GPRS_CONNECTING_PPP:
               TRC_TRACE_INFO(trc_fun, "Connecting PPP...!");
               break;
            case LL_STATUS_GPRS_CONNECTED:
               TRC_TRACE_INFO(trc_fun, "Connected!");
               break;
            default:
               TRC_TRACE_INFO(trc_fun, "Unknown network status !");
               break;
         }
      }
         break;
   }

   return nError;
}

/**Dual SIM management:
 * Switch between SIM 1 and SIM2,GPRS configuration and TCP communication.
 *
 */
void FUN_DualSim(void)
{
   T_GPRS_TEST_SETTINGS* pTest;
   T_GPRS_TEST_SETTINGS GPRS_SETTINGS[2];
   unsigned int nIndex;
   TRC_Trace_t trc_fun; /* trace instance*/
   int ret = 0;
   trc_fun = TRC_HandleGet();
   unsigned long ulStart;
   char message[50];
   int nStatus;

   for (nIndex = 0; nIndex < 2; nIndex++)
   {
      ulStart = get_tick_counter();

      ret = PAR_T_GPRS_TEST_SETTINGS_NameStrGet(nIndex, &GPRS_SETTINGS[nIndex].m_szTest);
      ret = ret + PAR_T_GPRS_TEST_SETTINGS_NSlotIdGet(nIndex, &GPRS_SETTINGS[nIndex].m_nSlotId);
      ret = ret + PAR_T_GPRS_TEST_SETTINGS_SzPinCodeGet(nIndex, &GPRS_SETTINGS[nIndex].m_szPinCode);
      ret = ret + PAR_T_GPRS_TEST_SETTINGS_SzAPnGet(nIndex, &GPRS_SETTINGS[nIndex].m_szAPN);
      ret = ret + PAR_T_GPRS_TEST_SETTINGS_NPortGet(nIndex, &GPRS_SETTINGS[nIndex].m_nPort);
      ret = ret + PAR_T_GPRS_TEST_SETTINGS_SzHostNameGet(nIndex, &GPRS_SETTINGS[nIndex].m_szHostName);
      if (ret == PAR_OK)
      {
         pTest = &GPRS_SETTINGS[nIndex];
         TRC_TRACE_INFO(trc_fun, "Starting test %s ", pTest->m_szTest);

         nStatus = gprs_select_sim_slot(pTest->m_nSlotId);

         TRC_TRACE_INFO(trc_fun, "gprs_select_sim_slot %s %d %d", pTest->m_szTest, pTest->m_nSlotId, nStatus);

         if (nStatus == CR_ENTRY_OK)
         {

            TRC_TRACE_INFO(trc_fun, "ConnectNetworkGPRS %s %s %s", pTest->m_szTest, pTest->m_szPinCode, pTest->m_szAPN);
            nStatus = _FUN_ConnectNetworkGPRS(pTest->m_szPinCode, pTest->m_szAPN, 100, 9000);
            TRC_TRACE_INFO(trc_fun, "ConnectNetworkGPRS %s %d %ld0ms", pTest->m_szTest, nStatus, get_tick_counter() - ulStart);

            if (nStatus == LL_ERROR_OK)
            {
               sprintf(message, "%s Gprs connected", pTest->m_szTest);
               guiScreen("Dual Sim", message, GL_ICON_NONE, 3000);
               _FUN_TestTcp(pTest->m_szHostName, pTest->m_nPort);
            }
            else
            {

               sprintf(message, "%s Gprs not connected", pTest->m_szTest);
               guiScreen("Dual Sim", message, GL_ICON_NONE, 3000);

            }
            LL_GPRS_Stop();
         }
      }
      else
      {
         UI_ErrMsgDisplay(ERR_PAR_FILE_NOT_FOUND);
      }
   }
}
