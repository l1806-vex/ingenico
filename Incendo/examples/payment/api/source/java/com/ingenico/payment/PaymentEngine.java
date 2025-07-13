package com.ingenico.payment;

/**
 * The PaymentEngine interface defines the methods that allow an application
 * to send payment requests to some payment facility (which may be an APACS
 * 30/40 acquirer, or something else).
 *
 * @author Eugene Pestov
 */
public interface PaymentEngine {

    /**
     * Sends the request for the specified payment operation.
     * 
     * @param payment payment request
     * @return payment response data
     * @throws PaymentException in case of any errors occur
     */
    public PaymentResponse makePayment(PaymentRequest payment)
            throws PaymentException;

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
