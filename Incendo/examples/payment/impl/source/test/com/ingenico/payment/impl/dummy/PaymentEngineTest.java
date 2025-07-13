package com.ingenico.payment.impl.dummy;

import com.ingenico.payment.*;
import junit.framework.TestCase;

import java.util.Properties;

/**
 * This class represents unit testing
 *
 * @author Eugene Pestov
 */
public class PaymentEngineTest extends TestCase {

    /**
     * payment engine
     */
    private PaymentEngine paymentEngine;

    /**
     * Constructor for PaymentManagerTest.
     *
     * @param arg0 argument
     */
    public PaymentEngineTest(String arg0) {
        super(arg0);
    }

    /**
     * Start test
     *
     * @param args arguments
     */
    public static void main(String[] args) {
        junit.textui.TestRunner.run(PaymentEngineTest.class);
    }

    /**
     * Inits test
     *
     * @throws Exception in case of any errors occur
     */
    protected void setUp() throws Exception {
        super.setUp();

        Properties props = new Properties();
        props.setProperty(PaymentHelper.FACTORY_CLASS,
                "com.ingenico.payment.impl.dummy.DummyPaymentEngineFactory");
        props.setProperty("com.ingenico.payment.impl.dummy.delay", "1");
        props.setProperty("com.ingenico.payment.impl.dummy.topLimit",
                Long.toString(TestData.AMOUNT));

        PaymentEngineFactory paymentEngineFactory =
                PaymentHelper.getPaymentEngineFactory(props);

        paymentEngine = paymentEngineFactory.getPaymentEngine();
    }

    /**
     * Process sale transaction
     */
    public void testMakePayment_SALE() {

        PaymentRequest paymentRequest = new PaymentRequest();

        paymentRequest.setType(PaymentType.SALE);
        paymentRequest.setCardDetails(TestData.CARD_DETAILS);
        paymentRequest.setAmount(TestData.AMOUNT);

        try {
            PaymentResponse paymentResponse =
                    paymentEngine.makePayment(paymentRequest);
        } catch (PaymentException e) {
            fail(e.getMessage());
        }
    }

    /**
     * Process sale transaction with expired card
     */
    public void testMakePayment_SALE_EXPIRED_CARD() {

        PaymentRequest paymentRequest = new PaymentRequest();

        paymentRequest.setType(PaymentType.SALE);
        paymentRequest.setCardDetails(TestData.EXPIRED_CARD_DETAILS);
        paymentRequest.setAmount(TestData.AMOUNT);

        try {
            PaymentResponse paymentResponse =
                    paymentEngine.makePayment(paymentRequest);
            fail("Expiration check was not done");
        } catch (PaymentException e) {
            // ok
        }
    }

    /**
     * Process sale transaction with amount that exceed top limit
     */
    public void testMakePayment_SALE_BIG_AMOUNT() {

        PaymentRequest paymentRequest = new PaymentRequest();

        paymentRequest.setType(PaymentType.SALE);
        paymentRequest.setCardDetails(TestData.CARD_DETAILS);
        paymentRequest.setAmount(TestData.AMOUNT + 1);

        try {
            PaymentResponse paymentResponse =
                    paymentEngine.makePayment(paymentRequest);
            fail("Top limit check was not done");
        } catch (PaymentException e) {
            // ok
        }
    }

    /**
     * Process sale with cashback transaction
     */
    public void testMakePayment_SALE_WITH_CASHBACK() {

        PaymentRequest paymentRequest = new PaymentRequest();

        paymentRequest.setType(PaymentType.SALE_WITH_CASHBACK);
        paymentRequest.setCardDetails(TestData.CARD_DETAILS);
        paymentRequest.setAmount(TestData.AMOUNT);
        paymentRequest.setAmountOther(TestData.CASHBACK_AMOUNT);

        try {
            PaymentResponse paymentResponse =
                    paymentEngine.makePayment(paymentRequest);
        } catch (PaymentException e) {
            fail(e.getMessage());
        }
    }

    /**
     * Process refund transaction
     */
    public void testMakePayment_REFUND() {

        PaymentRequest paymentRequest = new PaymentRequest();

        paymentRequest.setType(PaymentType.REFUND);
        paymentRequest.setCardDetails(TestData.CARD_DETAILS);
        paymentRequest.setAmount(TestData.AMOUNT);

        try {
            PaymentResponse paymentResponse =
                    paymentEngine.makePayment(paymentRequest);
        } catch (PaymentException e) {
            fail(e.getMessage());
        }
    }

    /**
     * Process reversal transaction
     */
    public void testMakePayment_REVERSAL() {

        PaymentRequest paymentRequest = new PaymentRequest();

        paymentRequest.setType(PaymentType.REVERSAL);
        paymentRequest.setCardDetails(TestData.CARD_DETAILS);
        paymentRequest.setAmount(TestData.AMOUNT);

        try {
            PaymentResponse paymentResponse =
                    paymentEngine.makePayment(paymentRequest);
        } catch (PaymentException e) {
            fail(e.getMessage());
        }
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
