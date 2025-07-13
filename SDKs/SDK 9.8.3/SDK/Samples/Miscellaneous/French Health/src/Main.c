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
 * @Description: SDK30 sample application 
 * @Reference:    
 * @Comment:      
 *
 * @author        
 * @version       
 * @Comment:      
 * @date:         
 */
#include "SDK30.H"
#include "etat.h"

extern int after_reset         (NO_SEGMENT, void *,        S_TRANSOUT *);

#ifdef _EFT20_
int Main               (unsigned short typ_appli,unsigned short service,StructPt *data,unsigned int size);
#else
int Main(unsigned int size, StructPt *data)
#endif
{
	NO_SEGMENT No;
	int            ret;
	No = ApplicationGetCurrent();
	switch(data->service)
	{
	case IS_NAME :
		ret = is_name(No,NULL,&data->Param.IsName.param_out);
        break;
	case MORE_FUNCTION :
		ret = more_function(No,NULL,NULL);
        break;
	case IDLE_MESSAGE :
        idle_message(No,NULL,NULL);
        break;
	case AFTER_RESET :
		ret = after_reset(No,NULL,&data->Param.AfterReset.param_out);
        break;
	case IS_STATE :
		ret = is_state(No,NULL,&data->Param.IsState.param_out);
        break;
	case STATE :
		ret = state(No,NULL,NULL);
        break;
	case GIVE_YOUR_DOMAIN :
		ret = give_your_domain(No,NULL,&data->Param.GiveYourType.param_out);
        break;
	}
	return(0);
}

