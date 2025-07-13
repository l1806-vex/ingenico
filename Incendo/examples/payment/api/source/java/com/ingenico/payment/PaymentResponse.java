package com.ingenico.payment;

import com.ingenico.payment.icc.ICCResponseData;

/**
 * This class represents bean for payment response
 *
 * @author Eugene Pestov
 */
public class PaymentResponse {

    /**
     * Payment authorisation code
     */
    private String authorisationCode;

    /**
     * ICC EMV specific response data
     */
    private ICCResponseData iccResponseData;

    /**
     * authorisation message
     */
    private String message;

    /**
     * Default constructor
     *
     * @param authorisationCode authorisation code
     * @param message           authorisation message
     */
    public PaymentResponse(String authorisationCode, String message) {
        this.authorisationCode = authorisationCode;
        this.message = message;
    }

    /**
     * Gets authorisation code
     *
     * @return authorisation code
     */
    public String getAuthorisationCode() {
        return authorisationCode;
    }

    /**
     * Gets ICC EMV specific response data
     *
     * @return ICC EMV specific response data
     */
    public ICCResponseData getIccResponseData() {
        return iccResponseData;
    }

    /**
     * @return
     */
    public String getMessage() {
        return message;
    }

    /**
     * Sets ICC EMV specific response data
     *
     * @param data ICC EMV specific response data
     */
    public void setIccResponseData(ICCResponseData data) {
        iccResponseData = data;
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
