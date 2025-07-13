package com.ingenico.payment.impl.dummy;

import java.util.Properties;

import com.ingenico.payment.PaymentEngine;
import com.ingenico.payment.PaymentEngineFactory;

/**
 * This class represents dummy payment engine factory
 *
 * @author Eugene Pestov
 */
public class DummyPaymentEngineFactory implements PaymentEngineFactory {

    /**
     * prefix
     */
    public static final String PROPERTIES_PREFIX =
            "com.ingenico.payment.impl.dummy.";

    /**
     * top limit
     */
    private long topLimit;

    /**
     * authorisation delay
     */
    private int delay;

    /**
     * dummy payment engine instance
     */
    private DummyPaymentEngine dummyEngineInstance;

    /**
     * Configures factory
     *
     * @param props configuration properties
     */
    public void configure(Properties props) {
        delay =
                Integer.parseInt(props.getProperty(PROPERTIES_PREFIX + "delay"));
        topLimit =
                Long.parseLong(props.getProperty(PROPERTIES_PREFIX + "topLimit"));
    }

    /**
     * Gets instance of payment engine
     *
     * @return instance of payment engine
     */
    public synchronized PaymentEngine getPaymentEngine() {
        if (dummyEngineInstance == null) {
            dummyEngineInstance = new DummyPaymentEngine(delay, topLimit);
        }
        return dummyEngineInstance;
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
