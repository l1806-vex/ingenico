package com.ingenico.payment.impl.dummy;

import com.ingenico.payment.CardDate;
import com.ingenico.payment.CardDetails;

/**
 * Test data for unit testing
 *
 * @author Eugene Pestov
 */
public final class TestData {

    /**
     * card details
     */
    public static final CardDetails CARD_DETAILS;

    /**
     * inits card details
     */
    static {
        CARD_DETAILS = new CardDetails();
        CARD_DETAILS.setPan("40400000001234");
        CARD_DETAILS.setExpiryDate(new CardDate(6, 2005));
        CARD_DETAILS.setIssueNumber(1);
    }

    /**
     * expired card details
     */
    public static final CardDetails EXPIRED_CARD_DETAILS;

    /**
     * cashback amount
     */
    public static final int CASHBACK_AMOUNT = 2500;

    /**
     * transaction amount
     */
    public static final int AMOUNT = 10000;

    /**
     * inits expired card details
     */
    static {
        EXPIRED_CARD_DETAILS = new CardDetails();
        EXPIRED_CARD_DETAILS.setPan("40400000001235");
        EXPIRED_CARD_DETAILS.setExpiryDate(new CardDate(6, 2004));
        EXPIRED_CARD_DETAILS.setIssueNumber(1);
    }
}
/*
 * Incendo Online Payment API
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
