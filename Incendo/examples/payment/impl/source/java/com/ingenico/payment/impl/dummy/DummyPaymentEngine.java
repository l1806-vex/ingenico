package com.ingenico.payment.impl.dummy;

import java.text.NumberFormat;
import java.util.Calendar;
import java.util.TimeZone;

import com.ingenico.payment.CardDate;
import com.ingenico.payment.CardDetails;
import com.ingenico.payment.PaymentEngine;
import com.ingenico.payment.PaymentException;
import com.ingenico.payment.PaymentRequest;
import com.ingenico.payment.PaymentResponse;
import com.ingenico.payment.PaymentType;
import com.ingenico.util.logging.Logger;

/**
 * This class represents dummy payment engine implementation
 *
 * @author Eugene Pestov
 */
public class DummyPaymentEngine implements PaymentEngine {

    /**
     * authorisation code sequence
     */
    private static int authCodeSequence = 1;

    /**
     * logger
     */
    private static Logger LOG = Logger.getLogger(DummyPaymentEngine.class.getName());

    /**
     * formatter for auth code
     */
    private static final NumberFormat nf;

    /**
     * delay in seconds
     */
    private int delay;

    /**
     * the transaction's top limit
     */
    private long topLimit;

    /**
     * init number formatter
     */
    static {
        nf = NumberFormat.getNumberInstance();
        nf.setGroupingUsed(false);
        nf.setMinimumIntegerDigits(6);
    }

    /**
     * Default constructor
     * no delay, top limit 100.00
     */
    public DummyPaymentEngine() {
        this(0, 10000);
    }

    /**
     * Constructor
     *
     * @param delay      delay
     * @param topLimit top limit
     */
    public DummyPaymentEngine(int delay, long topLimit) {
        this.delay = delay;
        this.topLimit = topLimit;

        LOG.info("DummyPaymentEngine is created and configured with delay "
                + delay
                + " sec, top limit "
                + (double) topLimit / 100);

    }

    /**
     * This method only checks the expiry date.
     *
     * @param details card details
     */
    private void checkCard(CardDetails details) throws PaymentException {

        LOG.info("Checking card " + details.getPan());

        // Imitating delay for APACS processing.
        // This is meaningful just for testing.
        // In real implementation this delay will be natural.
        delayProcessing();

        // get the current values
        Calendar calendar = Calendar.getInstance(TimeZone.getTimeZone("GMT"));
        int month = calendar.get(Calendar.MONTH) + 1; // card month is 1-12
        int year = calendar.get(Calendar.YEAR);
        CardDate cd = new CardDate(month, year);

        if (cd.after(details.getExpiryDate())) {
            throw new PaymentException("Card expired");
        }

        LOG.info("Card " + details.getPan() + " is good");

    }

    /**
     * Delay
     */
    private void delayProcessing() {
        if (delay > 0) {
            LOG.info("Delaying for " + delay + " sec");
            long ts = System.currentTimeMillis();
            long delayMs = delay * 1000;
            while (System.currentTimeMillis() - ts < delayMs) {
                // do nothing
            }
        }
    }

    /**
     * Processes payment
     *
     * @param payment payment data
     * @return payment response
     * @throws PaymentException in case of any errors occur
     */
    public PaymentResponse makePayment(PaymentRequest payment)
            throws PaymentException {

        int authorisationCode;
        String message = "OK";

        String logmsg;

        if (payment.getType() == PaymentType.REVERSAL) {
            logmsg = "Reversing transaction for a card:\n";
        }
        else {
            logmsg = "Handling a " + null2Empty(payment.getType()) + " transaction for a card:\n";
            // log all the card information
        }
        LOG.info(logmsg +
                "Card PAN: " + null2Empty(payment.getCardDetails().getPan()) + "\n" +
                "Card Expiry Date: " + null2Empty(payment.getCardDetails().getExpiryDate()) + "\n" +
                "Card Effective Date: " + null2Empty(payment.getCardDetails().getEffectiveDate()) + "\n" +
                "Issue Number: " + payment.getCardDetails().getIssueNumber() + "\n" +
                "Amount: " + toPounds(String.valueOf(payment.getAmount())) + "\n" +
                "Cashback Amount: " + toPounds(String.valueOf(payment.getAmountOther())) + "\n" +
                "Currency: " + null2Empty(payment.getCurrencyCode()));

        try {
            checkCard(payment.getCardDetails());

            // check amount
            if (payment.getAmount() <= 0 ) {
                throw new PaymentException("Incorrect amount. Amount should be > 0");
            }

            // check for top limit
            if (payment.getAmount() > topLimit) {
                throw new PaymentException("Top limit exceeded");
            }

            if ((payment.getType() == PaymentType.SALE_WITH_CASHBACK)
                    && (payment.getAmountOther() > payment.getAmount())) {

                throw new PaymentException("Cachback amount exceeds the amount paid");
            }

            authorisationCode = 0;

            if (payment.getType() == PaymentType.REVERSAL) {
                LOG.info("Transaction reversed.");
            }
            else {
                authorisationCode = authCodeSequence++;
                LOG.info("Transaction approved. Auth Code: "
                    + nf.format(authorisationCode));
            }

            return new PaymentResponse(nf.format(authorisationCode), message);

        } catch (PaymentException e) {
            LOG.info("Transaction is declined. " + e.getMessage());
            return new PaymentResponse(null, e.getMessage());
        }
    }

    /**
     * This method converts string to pounds
     *
     * @param str string to convert
     * @return string in pounds
     */
    private static String toPounds(String str) {
        String s = str.trim();
        if (s != null && !s.equals("")) {
            switch (s.length()) {
                case 1:
                    s = "0.0" + s;
                    break;
                case 2:
                    s = "0." + s;
                    break;
                default:
                    s = s.substring(0, s.length() - 2) + "." + s.substring(s.length() - 2, s.length());
                    break;
            }
        }
        return s;
    }

    /**
     * Converts null to empty
     *
     * @param obj object
     * @return empty string if object equals null and string representation of
     *         object otherwise
     */
    private static String null2Empty(Object obj) {
        return obj == null ? "" : obj.toString();
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
