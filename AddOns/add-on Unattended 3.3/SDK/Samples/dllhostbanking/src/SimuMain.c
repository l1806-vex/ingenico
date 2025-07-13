/***
 * Copyright (c) 2004 Sagem Monetel SA, rue claude Chappe,
 * 07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * Sagem Monetel SA has intellectual property rights relating
 * to the technology embodied in this software.  In particular, 
 * and without limitation, these intellectual property rights 
 * may include one or more patents.
 *
 * This software is distributed under licenses restricting 
 * its use, copying, distribution, and decompilation.  
 * No part of this software may be reproduced in any form 
 * by any means without prior written authorization of 
 * Sagem Monetel.
 *
 * @Title:        
 * @Description:  Entry points of EFT30 simulator
 * @Reference:    
 * @Comment:      
 *
 * @author        C.Ardin 
 * @version       
 * @Comment:      
 * @date:          
 */
#include "SDK30.h"						// Constante OK/KO 
#include "SimuMain.h"

void entry(void);						// Main application function 

appliPC tabAppliPC[]=
{
	{0x0006E,entry},				// Entry of application ...

	{0x0000,NULL}						// End of table !!!
};


void main(short argc,char *argv[])
{
// ***********************************    NEW    ********************************* 
//  To log in file all exchanges between PC and TPE, suppress comments from the 
//  two following lines. You can put the name of your application instead of xxx. 
// 
	SimuLogHN = 1;
	strcpy (SimuLogAppliFileName, "SimuEFT30_xxx.log");
// *******************************************************************************

	// PC init ...
	SimuInit("\\\\.\\COM10",1);					// USB / COM5 port ...
										// 1=  USB = Not V24 ...
//	SimuInit("COM2",0);					// V24 CommunicationInit ....
										// 0 = V24 = Not USB ...


	SimuWaitTPE();						// Wait TPE and execute application code

	SimExit(KPB_NO_ERROR);
}
