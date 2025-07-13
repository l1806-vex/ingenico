/**
 * \author	Ingenico
 * \author	Copyright (c) 2012 Ingenico, rue claude Chappe,\n
 *			07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * \author	Ingenico has intellectual property rights relating to the technology embodied \n
 *			in this software. In particular, and without limitation, these intellectual property rights may\n
 *			include one or more patents.\n
 *			This software is distributed under licenses restricting its use, copying, distribution, and\n
 *			and decompilation. No part of this software may be reproduced in any form by any means\n
 *			without prior written authorization of Ingenico.
 */

/////////////////////////////////////////////////////////////////
//// Includes ///////////////////////////////////////////////////

#include "ClessSample_Implementation.h"


/////////////////////////////////////////////////////////////////
//// Macros & preprocessor definitions //////////////////////////

// Task states
#define TASK_OPEN			0				// Task state: OPEN
#define TASK_RECEPT			1				// Task state: RECEPTION
#define TASK_READING		2				// Task state: READING
#define TASK_CLOSE			3				// Task state: CLOSE


/////////////////////////////////////////////////////////////////
//// Types //////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
//// Global variables ///////////////////////////////////////////

// Parameters of COM_EVENT entry point
static S_COMIN             param_comin;		// Input structure
static S_COMOUT            param_comout;	// Output structure

// My application number
static NO_SEGMENT          appli_number;

// Protocole task handle : see OEM.H for description
static t_topstack         *pttask;

// Task number of M2OS
static unsigned short      m2os_task;

// Serial link order
static unsigned int uns_SerialRequest = 0;


/////////////////////////////////////////////////////////////////
//// Static function definitions ////////////////////////////////

static void _ClessSample_Comevent_DisplayData(char *data,unsigned int len);
static void _ClessSample_Comevent_TaskProtocole(void);


/////////////////////////////////////////////////////////////////
//// Functions //////////////////////////////////////////////////

//! \brief Memorised that orded is asked by serial link
void ClessSample_ComEventSetSerialRequest(void)
{
	uns_SerialRequest = TRUE;
}



//! \brief Deleted information that orded is asked by serial link
void ClessSample_ComEventUnSetSerialRequest(void)
{
	uns_SerialRequest = FALSE;
}



//! \brief Give information that orded is asked by serial link
unsigned char ClessSample_ComEvent_IsSerialRequest(void)
{
	return(uns_SerialRequest);
}



//! \brief Dump data on PRINTER.
//! \param[in] Header line to print on begining of ticket.
//! \param[in] String hexa buffer to print.
//! \param[in] Number hexa buffer length.
void ClessSample_Comevent_HexDump(unsigned char *Header,unsigned char *String,unsigned long Number)
{
	FILE          *hprt;
	unsigned char  Line[100];
	unsigned char  Buf[10];
	unsigned long  i;
	unsigned long  j;

	hprt = fopen("PRINTER","w");

	if (hprt == NULL)
		return;

	pprintf("************************\n%s\n************************\n",Header);
	ttestall(PRINTER,0);
	for (i=0;i<Number;i+=6)
	{
		memset(Line,' ',24);Line[24]='\0';
		for (j=i;j<Number && j<(i+6);j++)
		{
			sprintf((char *)Buf,"%02X ",String[j]);
			memcpy(&Line[(j-i)*3],Buf,3);
			if (String[j]<=125 && String[j]>=32)
			{
				Line[18+(j-i)] = String[j];
			}
			else
			{
				Line[18+(j-i)] = '.';
			}
		}
		pprintf("%s\n",Line);ttestall(PRINTER,0);
	}
	pprintf("\n\n\n\n\n");ttestall(PRINTER,0);
  
	fclose(hprt);
}



//! \brief 
//! \param[in] data 
//! \param[in] len 
static void _ClessSample_Comevent_DisplayData(char *data,unsigned int len)
{
	unsigned int i;

	printf("%c",0x1B);
	for (i=0;i<len;i++)
	{
		if (data[i]==0x0D)
		{
			printf("\n");
		}
		else
		{
			printf("%c",data[i]);
		}
	}
}



//! \brief 
//! \param[in] Msg 
//! \param[in] ucEventType 
void ClessSample_Comevent_SendMsg (char * Msg, unsigned short ucEventType)
{
	unsigned short sender;
	unsigned short receiver;
	unsigned short type;
	static   S_MESSAGE_IAM message;
	object_info_t info;

	// Prepare message to appli
	// Take care that application type may use two bytes, LSB of sender need to be 0x00
	
	GTL_Traces_TraceDebug("SendMsg %x", ucEventType);

	if (ObjectGetInfo  (OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &info) == 0)
	{
		receiver = TaskApplication*256 + ((info.application_type) & 0x00FF);
		sender   = ((info.application_type) & 0xFF00) + 0x00;

		type = ucEventType; // type == 1 for rs232 messages
		// Send Message
		message.receiver = receiver;
		message.sender   = sender;
		message.type     = type;
		message.length   = strlen(Msg);
		strcpy((char*)message.value, Msg);
		Send_Message( &message );
	}
	else
	{
		GTL_Traces_TraceDebug("ClessSample_Comevent_SendMsg: An error occurred when retrieving the information of current application (ObjectGetInfo)");
	}
}




//! \brief Protocol task
static void _ClessSample_Comevent_TaskProtocole(void)
{
	unsigned int   cr;          // Result of ttestall
	unsigned int   mask;        // Mask of event to wait depending of task state
	FILE          *handle=NULL; // Decriptor of serial link
	char           buf[128];    // To read from serial link
	char           data[1024];  // To read from serial link
	unsigned int   nb;          // Result of fread
	unsigned int   len;         // Length of data received
	int            first;       // First execution flag
	FILE * hDisplay;			// Descriptor for display

	// Task state
	static unsigned char task_state;

	// Remember it was the first execution
	first = 1;

	// Task is waiting for DO_OPEN
	task_state = TASK_OPEN;

	// Only synchronisation to wait
	mask       = DIALOG;

	// Task is now operationnal
	SignalEvent(m2os_task,EVT_DIALOG);

	while (1)
	{
		cr = ttestall(mask,0);

		switch (task_state)
		{
		//////////////////////////////////////////////////////////////////////////////////////
		case TASK_OPEN:
			// Only DO_OPEN is accepted in this state */
			if (cr == DIALOG)
			{
				if (param_comin.action==DO_OPEN)
				{
					GTL_Traces_TraceDebug("TASK_OPEN : DO_OPEN");
					GTL_Traces_TraceDebug("OpenCOM0");
             
					// Initialize returned structure
					// Appli number
					param_comout.no_appli = appli_number;
				  
					// Handle of peripheral , not used
					param_comout.handle   = NULL;

					// function return
					param_comout.cr       = CR_DIALOGUE_OK;

					// Open all protocole peripheral (for exemple COM0)
					handle = fopen("COM0","rw");

					// initialize peripheral
					// 9600 bauds,8 bits, 1 stop bit,no parity
					format("COM0",9600,8,1,NO_PARITY,EVEN,0);

					// We are now waiting for serial link and synchronization
					mask = COM0 | DIALOG;

					// New state
					task_state = TASK_RECEPT;
					GTL_Traces_TraceDebug("comevent OPEN->RECEPT");
				}
			}

			// Traitment is over
			SignalEvent(m2os_task,EVT_DIALOG);
			break; // End case TASK_OPEN
		
		//////////////////////////////////////////////////////////////////////////////////////
		case TASK_RECEPT :
			switch (cr)
			{
			/////////////////////////////////////
			case DIALOG :
				GTL_Traces_TraceDebug("TASK_RECEPT : DIALOG");
            
				// Only DO_CLOSE is accepted in this state
				if (param_comin.action == DO_CLOSE)
				{
					GTL_Traces_TraceDebug("TASK_RECEPT : DO_CLOSE");
		    		GTL_Traces_TraceDebug("CloseCOM0");

					// Initialize returned structure
					// Appli number
					param_comout.no_appli = appli_number;
					
					// Handle of peripheral , not used
					param_comout.handle = NULL;
				
					// function return
   					param_comout.cr = CR_DIALOGUE_OK;
					
					// New state
					task_state = TASK_OPEN;
					GTL_Traces_TraceDebug("comevent RECEPT->OPEN");
              
					// Close all protocole peripheral (for exemple COM0)
					if (handle)
						fclose(handle);
					handle = NULL;
              
					// Only synchronisation to wait
					mask = DIALOG;
				}
            
				// Traitment is over
				SignalEvent(m2os_task,EVT_DIALOG);
				break;

			/////////////////////////////////////
			case COM0 :
				GTL_Traces_TraceDebug("TASK_RECEPT : COM0");
				// Task want to manage something from serial link
 				// New state
				task_state = TASK_READING;
				GTL_Traces_TraceDebug("comevent RECEPT->READING");
  				
				// Initialize returned structure
				// Appli number
				param_comout.no_appli = appli_number;
		    
				// Handle of peripheral , not used
				param_comout.handle = NULL;
		    
				// function return
   				param_comout.cr = CR_DIALOGUE_OK;
            
				// Only synchronisation to wait
				mask = DIALOG;
            
				// Traitment is over
				SignalEvent(m2os_task,EVT_DIALOG);
				break;
			/////////////////////////////////////
			case COM5 :
				GTL_Traces_TraceDebug("TASK_RECEPT : USB");
				
				// Task want to manage something from serial link
 				// New state
				task_state = TASK_READING;

				GTL_Traces_TraceDebug("comevent RECEPT->READING");
  				
				// Initialize returned structure
				// Appli number
				param_comout.no_appli = appli_number;
		    
				// Handle of peripheral , not used
				param_comout.handle = NULL;
		    
				// function return
   				param_comout.cr = CR_DIALOGUE_OK;
            
				// Only synchronisation to wait
				mask = DIALOG;
            
				// Traitment is over
				SignalEvent(m2os_task,EVT_DIALOG);
				break;
			}
			break; // End case TASK_RECEPT

		//////////////////////////////////////////////////////////////////////////////////////
		case TASK_READING :
			// Only DO_RECEPT is accepted in this state
			if (cr == DIALOG)
			{
				if (param_comin.action==DO_RECEPT)
				{
					GTL_Traces_TraceDebug("TASK_READING : DO_RECEPT");

					//-------------------------------------------
					// Put protocole managment here              
					//          for exemple                      
					// Read from COM0 and print data received    
					//-------------------------------------------

					// nothing
					len = 0;
					hDisplay = fopen("DISPLAY","w");

					startupcv20(4,6);
					do
					{
						nb=fread(buf,1,128,handle);
						if (nb)
						{
							if (len<sizeof(data))
							{
								memcpy(&data[len],buf,nb);
								len+=nb;data[len]='\0';
								_ClessSample_Comevent_DisplayData(data,len);
								///GTL_Traces_TraceDebugBuffer ((const int)len, (const void*)data, "DisplayData : ");
							}
						}
					}
					while(ttestall(COM0,200)==COM0);
    		  
					if (hDisplay)
						fclose(hDisplay);
					hDisplay = NULL;

					ClessSample_Comevent_SendMsg(data, COM_EVT_COMMUNICATION_ORDER); // Send datas to application
    			
					// Initialize returned structure
					// Appli number
					param_comout.no_appli = appli_number;
					
					// Handle of peripheral , not used
					param_comout.handle   = NULL;
					
					// function return
   					param_comout.cr       = CR_DIALOGUE_OK;
					
					// We are now waiting for serial link and synchronization
					// New state
					task_state = TASK_RECEPT;
					
					// We are now waiting for serial link and synchronization
					mask = COM0 | DIALOG;
				}
			}
      
			// Traitment is over
			SignalEvent(m2os_task,EVT_DIALOG);
			break; // End case TASK_ALONE
		} // End switch
	} // End while (1)
}



//! \brief Start task for COM0 management.
//! \param[in] no : application number.
void ClessSample_Comevent_Start(NO_SEGMENT no)
{
	object_info_t info;

	// Force Cash Connection
	// PSQ_Update_Cash_Connection(cash_connection_off);
	PSQ_Update_Cash_Connection(cash_connection_on);
  
	// Remember my application number
	appli_number = no;
  
	// Remember task number of M2OS
	m2os_task = CurrentTask();
  
	// Start Protocole Task
	pttask = (t_topstack *) fork((PFONCFORK)_ClessSample_Comevent_TaskProtocole,NULL,0);
	GTL_Traces_TraceDebug("StartComEvent %x", GiveNoTask(pttask));

	// Waiting for task to be started
	ttestall(DIALOG,0);

	if (ObjectGetInfo  (OBJECT_TYPE_APPLI, ApplicationGetCurrent(), &info) == 0)
		GTL_Traces_TraceDebug("started !! %x", info.application_type);
	else
		GTL_Traces_TraceDebug("started !! (unable to determine application type)");

}



//! \brief Manage events to manage serial link.
//! \param[in] noappli application number.
//! \param[in] param_in input parameters buffer.
//! \param[in] param_out output parameters buffer.
//! \return allways FCT_OK.
int ClessSample_Comevent_Event (NO_SEGMENT noappli, S_COMIN *param_in, S_COMOUT *param_out)
{
	(void)noappli;
    
	GTL_Traces_TraceDebug("Comevent_Event : %x", param_in->action);

	memcpy((char *)&param_comin, (char *)param_in, sizeof(S_COMIN));
	
	switch(param_in->action)
	{
	case DO_OPEN :
	case DO_RECEPT :
	case DO_CLOSE :
		// because of MMU, GiveNoTack is use to read an element of pttask
		// Signal to protocole task that something is to do
		// The action is available into param_comin variable
		SignalEvent(GiveNoTask(pttask),EVT_DIALOG);
	
		// Wait the end of traitment
		ttestall(DIALOG,0);
		
		// Copy result of traitment
		memcpy((char *)param_out,(char *)&param_comout,sizeof(S_COMOUT));
		break;
	}
	
	return(FCT_OK);
}



//! \brief Manage events.
//! \param[in] action.
//! \return allways FCT_OK 
int ClessSample_Comevent_Manage (unsigned char action)
{
	//S_COMOUT param_out;
	
	param_comin.action = action;

	// because of MMU, GiveNoTack is use to read an element of pttask
	// Signal to protocole task that something is to do
	// The action is available into param_comin variable
	SignalEvent(GiveNoTask(pttask),EVT_DIALOG);
	
	// Wait the end of traitment
	ttestall(DIALOG,0);

	// Copy result of traitment
	//memcpy((char *)param_out,(char *)&param_comout,sizeof(S_COMOUT));

	return(FCT_OK);
}
