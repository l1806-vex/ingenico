package com.ingenico.payment;

import com.ingenico.payment.icc.ICCRequestData;

/**
 * This class represents bean for payment request
 *
 * @author Eugene Pestov
 */
public class PaymentRequest {

    /**
     * transaction amount
     */
    private long amount;

    /**
     * transaction cashback amount
     */
    private long amountOther;

    /**
     * card details
     */
    private CardDetails cardDetails;

    /**
     * transaction currency code
     */
    private String currencyCode;

    /**
     * icc emv specific data
     */
    private ICCRequestData iccRequestData;

    /**
     * terminal id in APACS
     */
    private String tid;

    /**
     * payment type
     */
    private PaymentType type;

    /**
     * Gets transaction amount
     *
     * @return transaction amount
     */
    public long getAmount() {
        return amount;
    }

    /**
     * Gets transaction cashback amount
     *
     * @return transaction cashback amount
     */
    public long getAmountOther() {
        return amountOther;
    }

    /**
     * Gets card details
     *
     * @return card details
     */
    public CardDetails getCardDetails() {
        return cardDetails;
    }

    /**
     * Gets transaction currency code
     *
     * @return transaction currency code
     */
    public String getCurrencyCode() {
        return currencyCode;
    }

    /**
     * Gets icc emv specific data
     *
     * @return icc emv specific data
     */
    public ICCRequestData getIccRequestData() {
        return iccRequestData;
    }

    /**
     * Gets terminal id in APACS
     *
     * @return terminal id in APACS
     */
    public String getTid() {
        return tid;
    }

    /**
     * Gets payment type
     *
     * @return payment type
     */
    public PaymentType getType() {
        return type;
    }

    /**
     * Sets transaction amount
     *
     * @param i transaction amount
     */
    public void setAmount(long i) {
        amount = i;
    }

    /**
     * Sets transaction cashback amount
     *
     * @param i transaction cashback amount
     */
    public void setAmountOther(long i) {
        amountOther = i;
    }

    /**
     * Sets card details
     *
     * @param details card details
     */
    public void setCardDetails(CardDetails details) {
        cardDetails = details;
    }

    /**
     * Sets transaction currency code
     *
     * @param string transaction currency code
     */
    public void setCurrencyCode(String string) {
        currencyCode = string;
    }

    /**
     * Sets icc emv specific data
     *
     * @param data icc emv specific data
     */
    public void setIccRequestData(ICCRequestData data) {
        iccRequestData = data;
    }

    /**
     * Sets terminal id in APACS
     *
     * @param string terminal id in APACS
     */
    public void setTid(String string) {
        tid = string;
    }

    /**
     * Sets payment type
     *
     * @param type payment type
     */
    public void setType(PaymentType type) {
        this.type = type;
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
