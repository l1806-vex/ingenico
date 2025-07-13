package com.ingenico.trans.data;

/**
 * @author Sergey Lukashin
 */
public class Txn {
    private int id;
    private String date;
    private String type;
    private int amount;
    private int amount2;
    private String currency;
    private String authcode;
    private String errorcode;
    private String errormessage;

    /**
     * @param id
     *            the id to set
     */
    public void setId(int id) {
        this.id = id;
    }

    /**
     * @return the id
     */
    public int getId() {
        return id;
    }

    /**
     * @param date
     *            the date to set
     */
    public void setDate(String date) {
        this.date = date;
    }

    /**
     * @return the date
     */
    public String getDate() {
        return date;
    }

    /**
     * @param type
     *            the type to set
     */
    public void setType(String type) {
        this.type = type;
    }

    /**
     * @return the type
     */
    public String getType() {
        return type;
    }

    /**
     * @param amount
     *            the amount to set
     */
    public void setAmount(int amount) {
        this.amount = amount;
    }

    /**
     * @return the amount
     */
    public int getAmount() {
        return amount;
    }

    /**
     * @param amount2
     *            the amount2 to set
     */
    public void setAmount2(int amount2) {
        this.amount2 = amount2;
    }

    /**
     * @return the amount2
     */
    public int getAmount2() {
        return amount2;
    }

    /**
     * @param currency
     *            the currency to set
     */
    public void setCurrency(String currency) {
        this.currency = currency;
    }

    /**
     * @return the currency
     */
    public String getCurrency() {
        return currency;
    }

    /**
     * @param authCode
     *            the authCode to set
     */
    public void setAuthcode(String authCode) {
        this.authcode = authCode;
    }

    /**
     * @return the authCode
     */
    public String getAuthcode() {
        return authcode;
    }

    /**
     * @param errorCode
     *            the errorCode to set
     */
    public void setErrorcode(String errorCode) {
        this.errorcode = errorCode;
    }

    /**
     * @return the errorCode
     */
    public String getErrorcode() {
        return errorcode;
    }

    /**
     * @param errorMessage
     *            the errorMessage to set
     */
    public void setErrormessage(String errorMessage) {
        this.errormessage = errorMessage;
    }

    /**
     * @return the errorMessage
     */
    public String getErrormessage() {
        return errormessage;
    }
}
/*
 * Incendo Online TML Examples
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