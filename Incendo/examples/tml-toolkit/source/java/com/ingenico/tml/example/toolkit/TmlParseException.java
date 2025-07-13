package com.ingenico.tml.example.toolkit;

import com.ingenico.util.exception.IngenicoException;

/**
 * Exception that should be thrown in case of tml parsing error
 * @author Eugene Pestov
 */
public class TmlParseException extends IngenicoException {

    /**
     * Empty constructor
     */
    public TmlParseException() {
        super();
    }

    /**
     * Constructor that specifies error message
     * @param msg error message
     */
    public TmlParseException(String msg) {
        super(msg);
    }
}
/*
 * Incendo Online TML Toolkit
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