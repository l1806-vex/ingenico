package com.ingenico.btmlpa;

/**
 * This calss contains constants used in BTMLPA.
 *
 * @author Eugene Pestov
 */

public interface TransactionConstants {

    /**
     * Possible values of transaction states
     */
    interface STATE {

        static int NEW = 0;
        static int APPROVED = 1;
        static int DECLINED = 2;
        static int FAILED = 3;
        static int REVERSED = 4;
        static int CANCELED = 5;
    }

    /**
     * TYPE interface defines possible values of transaction types
     */
    interface TYPE {
        static int SALE = 1;
        static int SALECASHBACK = 2;
        static int REFUND = 3;
        static int REVERSAL = 4;
    }


    /**
     * RESULT_CODE interface defines possible values of reply code values submitted to terminal
     */
    interface RESULT_CODE {
        static int ACCEPTED = 0;
        static int REFUSED = 1;
    }


    /**
     * AUTH_REPLY interface defines possible values of reply code values of Acquirer host
     */
    interface AUTH_REPLY {
        static int AUTHORISED = 0;
        static int DECLINED = 1;
    }


    /**
     * AUTH_CODE interface defines possible values of auth code values submitted
     * to terminal host
     */
    interface AUTH_CODE {
        static String NONE = "NONE";
        static String OK = "OK";
    }

    /**
     * Possible values of card input method
     */
    interface INPUT_METHOD {
        static int MAGNETIC = 1;
        static int ICC = 2;
        static int KEYED = 3;
    }

}
/*
 * Basic TML Payment Application
 *
 * COPYRIGHT (C) 2003-2012 INGENICO ALL RIGHTS RESERVED
 *
 * Copyright in the whole and every part of this software program belongs to
 * Ingenico. It may not be used, sold, licensed, transferred, copied
 * or reproduced in whole or in part in any manner or form other than in
 * accordance with and subject to the terms of a licence from Ingenico
 * or with the prior written consent of Ingenico or as permitted by
 * applicable law.
 * This software program contains confidential and proprietary information and
 * must not be disclosed, in whole or in part, to any person or organisation
 * without the prior written consent of Ingenico.
 * Any copies or reproductions of this software program (in whole or in part)
 * made by any method must also include a copy of this legend.
 */