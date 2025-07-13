package com.ingenico.tml.example.magcard;

import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import com.ingenico.tml.example.toolkit.TmlPostData;
import com.ingenico.tml.example.toolkit.ValidationException;

/**
 * This class represents magnetic card transaction bean
 * @author Eugene Pestov
 */
public class MagCardTxnData extends TmlPostData {

    /**
     * field mappings
     */
    private static final Map fieldMappings;

    /**
     * transaction amount
     */
    private int amount;

    /**
     * card expiration date
     */
    private Date card_expiry;

    /**
     * card holder name
     */
    private String card_holder;

    /**
     * card issue
     */
    private int card_issue;

    /**
     * card issuer
     */
    private String card_issuer;

    /**
     * card number
     */
    private String card_number;

    /**
     * card parser
     */
    private String card_parser;

    /**
     * card scheme
     */
    private String card_scheme;

    /**
     * card start date
     */
    private Date card_start;

    /**
     * iso2 track
     */
    private String iso2_track;

    /**
     * transaction id
     */
    private int transid;

    /**
     * specifies field mappings
     */
    static {
        
        HashMap hashMap = new HashMap();
        
        hashMap.put("card.parser.type", "card_parser");
        hashMap.put("card.cardholder_name", "card_holder");
        hashMap.put("card.pan", "card_number");
        hashMap.put("card.issuer_name", "card_issuer");
        hashMap.put("card.issue_number", "card_issue");
        hashMap.put("card.scheme", "card_scheme");
        hashMap.put("card.effective_date", "card_start");
        hashMap.put("card.expiry_date", "card_expiry");
        hashMap.put("card.mag.iso2_track", "iso2_track");
        hashMap.put("transid", "transid");
        hashMap.put("payment.amount", "amount");
        
        fieldMappings = Collections.unmodifiableMap(hashMap);
    
    }
    
    /**
     * Gets transaction amount
     * @return transaction amount
     */
    public int getAmount() {
        return amount;
    }

    /**
     * Gets card expiration date
     * @return card expiration date
     */
    public Date getCard_expiry() {
        return card_expiry;
    }

    /**
     * Gets card holder name
     * @return card holder name
     */
    public String getCard_holder() {
        return card_holder;
    }

    /**
     * Gets card issue
     * @return card issue
     */
    public int getCard_issue() {
        return card_issue;
    }

    /**
     * Gets card issuer
     * @return card issuer
     */
    public String getCard_issuer() {
        return card_issuer;
    }

    /**
     * Sets card issuer
     * @return card issuer
     */
    public String getCard_number() {
        return card_number;
    }

    /**
     * Gets card parser
     * @return card parser
     */
    public String getCard_parser() {
        return card_parser;
    }

    /**
     * Gets card scheme
     * @return card scheme
     */
    public String getCard_scheme() {
        return card_scheme;
    }

    /**
     * Gets card start date
     * @return card start date
     */
    public Date getCard_start() {
        return card_start;
    }

    /* (non-Javadoc)
     * @see com.ingenico.tml.example.toolkit.TmlPostData#getFieldMapping()
     */
    public Map getFieldMappings() {
        return fieldMappings;
    }

    /**
     * Gets iso2 track
     * @return iso2 track
     */
    public String getIso2_track() {
        return iso2_track;
    }

    /**
     * Gets transaction id
     * @return transaction id
     */
    public int getTransid() {
        return transid;
    }

    /**
     * Sets transaction amount
     * @param i transaction amount
     */
    public void setAmount(int i) {
        amount = i;
    }

    /**
     * Sets card expiration date
     * @param string card expiration date
     */
    public void setCard_expiry(Date string) {
        card_expiry = string;
    }

    /**
     * Sets card holder name
     * @param string card holder name
     */
    public void setCard_holder(String string) {
        card_holder = string;
    }

    /**
     * Sets card issue
     * @param i card issue
     */
    public void setCard_issue(int i) {
        card_issue = i;
    }

    /**
     * @param string
     */
    public void setCard_issuer(String string) {
        card_issuer = string;
    }

    /**
     * @param string
     */
    public void setCard_number(String string) {
        card_number = string;
    }

    /**
     * Sets card parser
     * @param string card parser
     */
    public void setCard_parser(String string) {
        card_parser = string;
    }

    /**
     * Sets card scheme
     * @param string card scheme
     */
    public void setCard_scheme(String string) {
        card_scheme = string;
    }

    /**
     * Sets card start date
     * @param string card start date
     */
    public void setCard_start(Date string) {
        card_start = string;
    }

    /**
     * Sets iso2 track
     * @param bs iso2 track
     */
    public void setIso2_track(String bs) {
        iso2_track = bs;
    }

    /**
     * Sets transaction id
     * @param i transaction id
     */
    public void setTransid(int i) {
        transid = i;
    }

    /**
     * Validates transaction data
     * @throws ValidationException in case of validation failed
     */
    public void validate() throws ValidationException {
        // TODO Auto-generated method stub
        super.validate();
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