package com.ingenico.payment;

/**
 * This class represent exception that is thrown in case of factory cannot be
 * created
 *
 * @author Eugene Pestov
 */
public class FactoryInstantiationException extends Exception {

    /**
     * Empty constructor
     */
    public FactoryInstantiationException() {
        super();
    }

    /**
     * Constructor with error message
     *
     * @param message error message
     */
    public FactoryInstantiationException(String message) {
        super(message);
    }

    /**
     * Constructor with error stack trace as throwable
     *
     * @param cause error stack trace as throwable
     */
    public FactoryInstantiationException(Throwable cause) {
        super(cause);
    }

    /**
     * Constructor with error message and the cause
     *
     * @param message error message
     * @param cause   the cause
     */
    public FactoryInstantiationException(String message, Throwable cause) {
        super(message, cause);
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
