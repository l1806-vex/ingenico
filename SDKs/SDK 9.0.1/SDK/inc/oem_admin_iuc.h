/***
 * Copyright (c) 2001 Ascom Monetel SA, rue claude Chappe,
 * 07503 Guilherand-Granges, France, All Rights Reserved.
 *
 * Ascom Monetel SA has intellectual property rights relating
 * to the technology embodied in this software.  In particular,
 * and without limitation, these intellectual property rights
 * may include one or more patents.
 *
 * This software is distributed under licenses restricting
 * its use, copying, distribution, and decompilation.
 * No part of this software may be reproduced in any form
 * by any means without prior written authorization of
 * Ascom Monetel.
 *
 * Title:        oem_admin_iuc.h
 * Description:  DRIVER ADMIN INTER UC interface
 * Reference:    ANSI X9.30
 * Comment:
 *
 * @author:      Nicolas BARITEAU
 * @version:     1.0
 * @date:        02/04/2010
 * @since:
 * @tools:       Arm Developer Suite 1.1 (if need)
 * @processor:   ARM 9 (only for ASM)
 * @evolution:   
 */


#ifndef ADMIN_INTER_UC_OEM_H
#define	ADMIN_INTER_UC_OEM_H

//ADMIN_IUC_FIOCTL_GET_STATE
#define ADMIN_IUC_STATE_ACTIVE		1
#define ADMIN_IUC_STATE_IDLE		2
#define ADMIN_IUC_STATE_MAINTENANCE	3
#define ADMIN_IUC_STATE_LLT			4

#define ADMIN_IUC_STATE_NEW_MODE_INTELLIGENT      0x101		/*!< The peripheral has to go to the intelligent mode*/



// Returns oem */
#define ADMIN_IUC_FIOCTL_SUCCESS				(0)			/*!< Return value if fioctl command is successful */
#define ADMIN_IUC_FIOCTL_IOCTL_NOT_IMPLEMENTED	(-1)		/*!< Return value if fioctl command is unknown */
#define ADMIN_IUC_FIOCTL_INTERNAL_ERR			(-2)			/*!< Return value if fioctl command is successful */
#define ADMIN_IUC_INVALID_PARAMETER				(-4)

// FIOCTL defines functions *
#define ADMIN_IUC_FIOCTL_EXTERNAL    0x8100		/*!< External led ioctl base address */


#define ADMIN_IUC_FIOCTL_REGISTER_IDLE				( ADMIN_IUC_FIOCTL_EXTERNAL + 1 )		/*!< command to inform that the application uses ressources in idle state */
#define ADMIN_IUC_FIOCTL_UNREGISTER_IDLE			( ADMIN_IUC_FIOCTL_EXTERNAL + 2 )		/*!< command to inform that the application doesn't use ressources in idle state (default) */

#define ADMIN_IUC_FIOCTL_GET_STATE					( ADMIN_IUC_FIOCTL_EXTERNAL + 3 )		/*!< command to get the admin iuc state*/

#endif


