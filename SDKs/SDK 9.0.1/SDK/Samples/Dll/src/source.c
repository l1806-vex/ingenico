/***
 * Copyright (c) 2004-2006 Sagem Monetel SA, rue claude Chappe,
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
 * @Description:  
 * @Reference:    
 * @Comment:      
 *
 * @author        
 * @version       
 * @Comment:      
 * @date:         2002/12/02 
 */
 
#include "sdk30.h"

//================================================================================
//
void DisplayHello()
{
	fopen("DISPLAY","w");
	printf("HELLO\n");ttestall(0,300);
    fclose(stdout());
}

void DisplayGoodBye()
{
	fopen("DISPLAY","w");
	printf("GOODBYE\n");ttestall(0,300);
    fclose(stdout());
}
