package com.ingenico.payment;

import java.util.Properties;

/**
 * This class is used to acquire a PaymentEngineFactory via a standard
 * Properties construction.
 *
 * @author Eugene Pestov
 */
public final class PaymentHelper {

    /**
     * payment factory class property
     */
    public static final String FACTORY_CLASS =
            "com.ingenico.payment.factoryClass";

    /**
     * Get a PaymentEngineFactory based on a Properties instance, using the
     * current thread's context class loader to locate the PaymentEngineFactory
     * class.
     * <p/>
     * The following are standard key values:</br>
     * "com.ingenico.payment.factoryClass"
     * <p/>
     * Payment implementations are permitted to define key values of their
     * own. Any key values not recognized by the implementation must be
     * ignored. Key values that are recognized but not supported by an
     * implementation must result in a FactoryInstantiationException thrown
     * by the method.
     *
     * @param props - a Properties instance with properties of the
     *              PaymentEngineFactory.
     * @return the PaymentEngineFactory.
     * @throws FactoryInstantiationException if something goes wrong
     */
    public static PaymentEngineFactory getPaymentEngineFactory(Properties props)
            throws FactoryInstantiationException {
        if (props == null) {
            throw new IllegalArgumentException("props==null");
        }

        String factoryClass = props.getProperty(FACTORY_CLASS);
        if (factoryClass == null) {
            throw new FactoryInstantiationException("Property '" + FACTORY_CLASS + "' is not specified");
        }

        PaymentEngineFactory factory;
        try {

            factory =
                    (PaymentEngineFactory) Class.forName(factoryClass).newInstance();

            factory.configure(props);

        } catch (ClassNotFoundException e) {
            throw new FactoryInstantiationException("Factory class '" + factoryClass + "' not found", e);
        } catch (InstantiationException e) {
            throw new FactoryInstantiationException(e);
        } catch (IllegalAccessException e) {
            throw new FactoryInstantiationException(e);
        }

        return factory;
    }

    /**
     * Empty constructor
     */
    private PaymentHelper() {
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
