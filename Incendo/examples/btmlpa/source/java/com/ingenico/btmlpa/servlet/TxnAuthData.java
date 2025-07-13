package com.ingenico.btmlpa.servlet;

import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import com.ingenico.btmlpa.Constants;
import com.ingenico.tml.example.toolkit.TmlPostData;
import com.ingenico.tml.example.toolkit.ValidationException;

/**
 * This class represents bean for transaction authorisation data
 *
 * @author Eugene Pestov
 */
public class TxnAuthData extends TmlPostData {

    /**
     * field mappings
     */
    private static final Map fieldMappings;

    /**
     * txn amount
     */
    private int amount;

    /**
     * cashback amount
     */
    private int amount_other = Constants.NOT_SPECIFIED;

    /**
     * card expiry date
     */
    private Date card_expiry;

    /**
     * card input mode (swipe/manual)
     */
    private int card_input_mode;

    /**
     * card issue
     */
    private int card_issue;

    /**
     * card number
     */
    private String card_number;

    /**
     * cardholder name
     */
    private String card_holdername;


    /**
     * card start date
     */
    private Date card_start;

    /**
     * currency code
     */
    private String currency_code;
    
    // ICC Data

    /**
     * icc application authentication cryptogram
     */
    private byte[] icc_aac;

    /**
     * application interchange profile
     */
    private int icc_aip;

    /**
     * application identifier
     */
    private String icc_aid;

    /**
     * authorisation request cryptogram
     */
    private byte[] icc_arqc;

    /**
     * application transaction counter
     */
    private int icc_atc;

    /**
     * application usage control
     */
    private int icc_auc;

    /**
     * issuer application data
     */
    private byte[] icc_iad;

    /**
     * transaction certificate
     */
    private byte[] icc_tc;

    /**
     * terminal verification results
     */
    private byte[] icc_tvr;

    /**
     * unpredictable number
     */
    private int icc_unumber;

    /**
     * iso2 track
     */
    private String iso2_track;

    /**
     * txn submit mode (online/offline)
     */
    private String submit_mode;

    /**
     * transaction type
     */
    private String trans_type;

    /**
     * transactoin id
     */
    private int transid;

    /**
     * transaction date
     */
    private Date txn_date;

    /**
     * time zone
     */
    private int time_zone;

    /**
     * specifies fields mapping
     */
    static {

        HashMap hashMap = new HashMap();

        hashMap.put("payment.amount", "amount");
        hashMap.put("payment.amount_other", "amount_other");
        hashMap.put("card.expiry_date", "card_expiry");
        hashMap.put("card.input_type", "card_input_mode");
        hashMap.put("card.issue_number", "card_issue");
        hashMap.put("card.pan", "card_number");
        hashMap.put("card.cardholder_name", "card_holdername");
        hashMap.put("card.effective_date", "card_start");
        hashMap.put("currency_code", "currency_code");
        hashMap.put("card.emv.aac", "icc_aac");
        hashMap.put("card.emv.aip", "icc_aip");
        hashMap.put("card.emv.aid", "icc_aid");
        hashMap.put("card.emv.arqc", "icc_arqc");
        hashMap.put("card.emv.atc", "icc_atc");
        hashMap.put("card.emv.auc", "icc_auc");
        hashMap.put("card.emv.iad", "icc_iad");
        hashMap.put("card.emv.tc", "icc_tc");
        hashMap.put("card.emv.tvr", "icc_tvr");
        hashMap.put("card.emv.unumber", "icc_unumber");
        hashMap.put("card.mag.iso2_track", "iso2_track");
        hashMap.put("oebr.submit_mode", "submit_mode");
        hashMap.put("payment.trans_type", "trans_type");
        hashMap.put("transid", "transid");
        hashMap.put("payment.txn_date", "txn_date");
        hashMap.put("oebr.time_zone", "time_zone");

        fieldMappings = Collections.unmodifiableMap(hashMap);

    }

    /**
     * Gets transaction amount
     *
     * @return transaction amount
     */
    public int getAmount() {
        return amount;
    }

    /**
     * Gets cashback amount
     *
     * @return cashback amount
     */
    public int getAmount_other() {
        return amount_other;
    }

    /**
     * Gets card expiration date
     *
     * @return card expiration date
     */
    public Date getCard_expiry() {
        return card_expiry;
    }

    /**
     * Gets card input mode
     *
     * @return card input mode
     */
    public int getCard_input_mode() {
        return card_input_mode;
    }

    /**
     * Gets card issue
     *
     * @return card issue
     */
    public int getCard_issue() {
        return card_issue;
    }

    /**
     * Gets card number
     *
     * @return card number
     */
    public String getCard_number() {
        return card_number;
    }

    /**
     * Gets cardholder name
     *
     * @return cardholder name
     */
    public String getCard_holdername() {
        return card_holdername;
    }

    /**
     * Gets card start date
     *
     * @return card start date
     */
    public Date getCard_start() {
        return card_start;
    }

    /**
     * Gets currency code
     *
     * @return currency code
     */
    public String getCurrency_code() {
        return currency_code;
    }

    /**
     * Gets field mapping
     *
     * @return field mapping
     */
    public Map getFieldMappings() {
        return fieldMappings;
    }

    /**
     * Gets icc application authentication cryptogram
     *
     * @return icc application authentication cryptogram
     */
    public byte[] getIcc_aac() {
        return icc_aac;
    }

    /**
     * Gets application interchange profile
     *
     * @return application interchange profile
     */
    public int getIcc_aip() {
        return icc_aip;
    }

    /**
     * Gets application identifier
     *
     * @return application identifier
     */
    public String getIcc_aid() {
        return icc_aid;
    }

    public byte[] getIcc_arqc() {
        return icc_arqc;
    }

    /**
     * Gets authorisation request cryptogram
     *
     * @return authorisation request cryptogram
     */
    public int getIcc_atc() {
        return icc_atc;
    }

    /**
     * Gets application usage control
     *
     * @return application usage control
     */
    public int getIcc_auc() {
        return icc_auc;
    }

    /**
     * Gets issuer application data
     *
     * @return issuer application data
     */
    public byte[] getIcc_iad() {
        return icc_iad;
    }

    /**
     * Gets transaction certificate
     *
     * @return transaction certificate
     */
    public byte[] getIcc_tc() {
        return icc_tc;
    }

    /**
     * terminal verification results
     *
     * @return terminal verification results
     */
    public byte[] getIcc_tvr() {
        return icc_tvr;
    }

    /**
     * Gets unpredictable number
     *
     * @return unpredictable number
     */
    public int getIcc_unumber() {
        return icc_unumber;
    }

    /**
     * Gets iso2 track
     *
     * @return iso2 track
     */
    public String getIso2_track() {
        return iso2_track;
    }

    /**
     * Gets tml post submit mode
     *
     * @return tml post submit mode
     */
    public String getSubmit_mode() {
        return submit_mode;
    }

    /**
     * Gets transactoin type
     *
     * @return transactoin type
     */
    public String getTrans_type() {
        return trans_type;
    }

    /**
     * Gets transaction id
     *
     * @return transaction id
     */
    public int getTransid() {
        return transid;
    }

    /**
     * Sets transaction amount
     *
     * @param amount transaction amount
     */
    public void setAmount(int amount) {
        this.amount = amount;
    }

    /**
     * Sets cashback amount
     *
     * @param amount_other cashback amount
     */
    public void setAmount_other(int amount_other) {
        this.amount_other = amount_other;
    }

    /**
     * Sets card expiration date
     *
     * @param card_expiry card expiration date
     */
    public void setCard_expiry(Date card_expiry) {
        this.card_expiry = card_expiry;
    }

    /**
     * Sets card input mode (swipe/manual)
     *
     * @param card_input_mode card input mode (swipe/manual)
     */
    public void setCard_input_mode(int card_input_mode) {
        this.card_input_mode = card_input_mode;
    }

    /**
     * Sets card issue
     *
     * @param card_issue card issue
     */
    public void setCard_issue(int card_issue) {
        this.card_issue = card_issue;
    }

    /**
     * Sets card number
     *
     * @param card_number card number
     */
    public void setCard_number(String card_number) {
        this.card_number = card_number;
    }

    /**
     * Sets cardholder name
     *
     * @param card_holdername cardholder name
     */
    public void setCard_holdername(String card_holdername) {
        this.card_holdername = card_holdername;
    }

    /**
     * Sets card start date
     *
     * @param card_start card start date
     */
    public void setCard_start(Date card_start) {
        if (card_start.getTime() > 0) {
            this.card_start = card_start;
        } else {
            this.card_start = null;
        }
    }

    /**
     * Sets currency code
     *
     * @param currency_code currency code
     */
    public void setCurrency_code(String currency_code) {
        this.currency_code = currency_code;
    }

    /**
     * Sets icc application authentication cryptogram
     *
     * @param icc_aac icc application authentication cryptogram
     */
    public void setIcc_aac(byte[] icc_aac) {
        this.icc_aac = icc_aac;
    }

    /**
     * Sets application interchange profile
     *
     * @param icc_aip application interchange profile
     */
    public void setIcc_aip(int icc_aip) {
        this.icc_aip = icc_aip;
    }

    /**
     * Sets application identifier
     *
     * @param icc_app application identifier
     */
    public void setIcc_aid(String icc_app) {
        this.icc_aid = icc_app;
    }

    /**
     * Sets authorisation request cryptogram
     *
     * @param icc_irqc authorisation request cryptogram
     */
    public void setIcc_arqc(byte[] icc_irqc) {
        this.icc_arqc = icc_irqc;
    }

    /**
     * Sets application transaction counter
     *
     * @param icc_atc application transaction counter
     */
    public void setIcc_atc(int icc_atc) {
        this.icc_atc = icc_atc;
    }

    /**
     * Sets application usage control
     *
     * @param icc_auc application usage control
     */
    public void setIcc_auc(int icc_auc) {
        this.icc_auc = icc_auc;
    }

    /**
     * Sets issuer application data
     *
     * @param icc_iad issuer application data
     */
    public void setIcc_iad(byte[] icc_iad) {
        this.icc_iad = icc_iad;
    }

    /**
     * Sets transaction certificate
     *
     * @param icc_tc transaction certificate
     */
    public void setIcc_tc(byte[] icc_tc) {
        this.icc_tc = icc_tc;
    }

    /**
     * Sets terminal verification results
     *
     * @param icc_tvr terminal verification results
     */
    public void setIcc_tvr(byte[] icc_tvr) {
        this.icc_tvr = icc_tvr;
    }

    /**
     * Sets unpredictable number
     *
     * @param icc_unumber unpredictable number
     */
    public void setIcc_unumber(int icc_unumber) {
        this.icc_unumber = icc_unumber;
    }

    /**
     * Sets iso2 track
     *
     * @param iso2_track iso2 track
     */
    public void setIso2_track(String iso2_track) {
        this.iso2_track = iso2_track;
    }

    /**
     * Sets tml post submit mode
     *
     * @param submit_mode tml post submit mode
     */
    public void setSubmit_mode(String submit_mode) {
        this.submit_mode = submit_mode;
    }

    /**
     * Sets transaction type
     *
     * @param trans_type transaction type
     */
    public void setTrans_type(String trans_type) {
        this.trans_type = trans_type;
    }

    /**
     * Sets transaction id
     *
     * @param transid transaction id
     */
    public void setTransid(int transid) {
        this.transid = transid;
    }

    /**
     * Validates txn parameters
     *
     * @throws ValidationException in case validation fails
     */
    public void validate() throws ValidationException {
        super.validate();

    }

    /**
     * Gets transaction date
     *
     * @return transaction date
     */
    public Date getTxn_date() {
        return txn_date;
    }

    /**
     * Sets transaction date
     *
     * @param txn_date transaction date
     */
    public void setTxn_date(Date txn_date) {
        this.txn_date = txn_date;
    }

    /**
     * Gets time zone
     *
     * @return time zone
     */
    public int getTime_zone() {
        return time_zone;
    }

    /**
     * Sets time zone
     *
     * @param time_zone time zone
     */
    public void setTime_zone(int time_zone) {
        this.time_zone = time_zone;
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