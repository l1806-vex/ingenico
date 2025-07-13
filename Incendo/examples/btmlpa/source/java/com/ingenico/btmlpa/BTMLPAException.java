package com.ingenico.btmlpa;

/**
 * The base BTMLPA exception class.
 * 
 * @author Eugene Pestov
 */
public class BTMLPAException extends Exception {

    /**
     * Constructs a <code>BTMLPAException</code> with no detail message.
     */
    public BTMLPAException() {
        super();
    }

    /**
     * Constructs a <code>BTMLPAException</code> with the
     * specified detail message.
     *
     * @param message the detail message.
     */
    public BTMLPAException(String message) {
        super(message);
    }

    /**
     * Constructs a <code>BTMLPAException</code> with no detail message
     * and optional exception that was caused the problem.
     *
     * @param cause the exception that was caused the problem
     */
    public BTMLPAException(Throwable cause) {
        super(cause);
    }

    /**
     * Constructs a <code>BTMLPAException</code> with the
     * specified detail message and optional exception that was
     * caused the problem.
     *
     * @param message the detail message
     * @param cause   the exception that was caused the problem
     */
    public BTMLPAException(String message, Throwable cause) {
        super(message, cause);
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