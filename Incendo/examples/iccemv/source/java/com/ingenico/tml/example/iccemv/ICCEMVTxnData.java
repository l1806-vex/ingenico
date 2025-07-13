package com.ingenico.tml.example.iccemv;

import com.ingenico.tml.example.toolkit.TmlPostData;
import com.ingenico.tml.example.toolkit.ValidationException;

import java.util.Collections;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

/**
 * @author Eugene Pestov
 */
public class ICCEMVTxnData extends TmlPostData {

    /**
     * field mappings
     */
    private static final Map fieldMapping;

    /**
     * card number
     */
    private String card_number;

    /**
     * card start date
     */
    private Date card_start;

    /**
     * card expiration date
     */
    private Date card_expiry;

    /**
     * application PAN sequence number
     */
    private String icc_app_pan_seq;

    /**
     * application interchange profile
     */
    private int icc_aip;

    /**
     * application usage control
     */
    private int icc_auc;

    /**
     * application transaction counter
     */
    private int icc_atc;

    /**
     * icc application authentication cryptogram
     */
    private byte icc_aac[];

    /**
     * transaction certificate
     */
    private byte icc_tc[];

    /**
     * authorisation request cryptogram
     */
    private byte icc_arqc[];

    /**
     * cid
     */
    private byte icc_cid[];

    /**
     * issuer application data
     */
    private byte icc_iad[];

    /**
     * terminal verification results
     */
    private byte icc_tvr[];

    /**
     * unpredictable number
     */
    private int icc_unumber;

    /**
     * transaction id
     */
    private int transid;

    /**
     * transaction amount
     */
    private int amount;

    /**
     * tml post submit mode
     */
    private String submit_mode;

    /**
     * specifies field mappings
     */
    static {

        HashMap hashMap = new HashMap();

        hashMap.put("card.pan", "card_number");
        hashMap.put("card.effective_date", "card_start");
        hashMap.put("card.expiry_date", "card_expiry");
        hashMap.put("card.emv.app_pan_seq", "icc_app_pan_seq");
        hashMap.put("card.emv.aip", "icc_aip");
        hashMap.put("card.emv.auc", "icc_auc");
        hashMap.put("card.emv.atc", "icc_atc");
        hashMap.put("card.emv.aac", "icc_aac");
        hashMap.put("card.emv.tc", "icc_tc");
        hashMap.put("card.emv.arqc", "icc_arqc");
        hashMap.put("card.emv.cid", "icc_cid");
        hashMap.put("card.emv.iad", "icc_iad");
        hashMap.put("card.emv.tvr", "icc_tvr");
        hashMap.put("card.emv.unumber", "icc_unumber");
        hashMap.put("transid", "transid");
        hashMap.put("payment.amount", "amount");
        hashMap.put("oebr.submit_mode", "submit_mode");

        fieldMapping = Collections.unmodifiableMap(hashMap);

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
     * Gets card expiration date
     *
     * @return card expiration date
     */
    public Date getCard_expiry() {
        return card_expiry;
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
     * Gets card start date
     *
     * @return card start date
     */
    public Date getCard_start() {
        return card_start;
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
     * Gets application PAN sequence number
     *
     * @return application PAN sequence number
     */
    public String getIcc_app_pan_seq() {
        return icc_app_pan_seq;
    }

    /**
     * Gets authorisation request cryptogram
     *
     * @return authorisation request cryptogram
     */
    public byte[] getIcc_arqc() {
        return icc_arqc;
    }

    /**
     * Gets application transaction counter
     *
     * @return application transaction counter
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
     * Gets cid
     *
     * @return cid
     */
    public byte[] getIcc_cid() {
        return icc_cid;
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
     * Gets terminal verification results
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
     * Gets issuer application data
     *
     * @return issuer application data
     */
    public byte[] getIcc_iad() {
        return icc_iad;
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
     * @param i transaction amount
     */
    public void setAmount(int i) {
        amount = i;
    }

    /**
     * Sets card expiration date
     *
     * @param date card expiration date
     */
    public void setCard_expiry(Date date) {
        card_expiry = date;
    }

    /**
     * Sets card number
     *
     * @param string card number
     */
    public void setCard_number(String string) {
        card_number = string;
    }

    /**
     * Sets card start date
     *
     * @param date card start date
     */
    public void setCard_start(Date date) {
        card_start = date;
    }

    /**
     * Sets icc application authentication cryptogram
     *
     * @param bs icc application authentication cryptogram
     */
    public void setIcc_aac(byte[] bs) {
        icc_aac = bs;
    }

    /**
     * Sets application interchange profile
     *
     * @param i application interchange profile
     */
    public void setIcc_aip(int i) {
        icc_aip = i;
    }

    /**
     * Sets application PAN sequence number
     *
     * @param i application PAN sequence number
     */
    public void setIcc_app_pan_seq(String s) {
        icc_app_pan_seq = s;
    }

    /**
     * Sets authorisation request cryptogram
     *
     * @param bs authorisation request cryptogram
     */
    public void setIcc_arqc(byte[] bs) {
        icc_arqc = bs;
    }

    /**
     * Sets application transaction counter
     *
     * @param i application transaction counter
     */
    public void setIcc_atc(int i) {
        icc_atc = i;
    }

    /**
     * Sets application usage control
     *
     * @param i application usage control
     */
    public void setIcc_auc(int i) {
        icc_auc = i;
    }

    /**
     * Sets cid
     *
     * @param bs cid
     */
    public void setIcc_cid(byte[] bs) {
        icc_cid = bs;
    }

    /**
     * Sets transaction certificate
     *
     * @param bs transaction certificate
     */
    public void setIcc_tc(byte[] bs) {
        icc_tc = bs;
    }

    /**
     * Sets terminal verification results
     *
     * @param bs terminal verification results
     */
    public void setIcc_tvr(byte[] bs) {
        icc_tvr = bs;
    }

    /**
     * Sets unpredictable number
     *
     * @param i unpredictable number
     */
    public void setIcc_unumber(int i) {
        icc_unumber = i;
    }

    /**
     * Sets issuer application data
     *
     * @param bs issuer application data
     */
    public void setIcc_iad(byte[] bs) {
        icc_iad = bs;
    }

    /**
     * Sets transaction id
     *
     * @param i transaction id
     */
    public void setTransid(int i) {
        transid = i;
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
     * Sets tml post submit mode
     *
     * @param string tml post submit mode
     */
    public void setSubmit_mode(String string) {
        submit_mode = string;
    }

    /**
     * Validates transaction data
     *
     * @throws ValidationException in case of validation failed
     */
    public void validate() throws ValidationException {
        super.validate();
    }

    /**
     * Gets field mappings
     *
     * @return field mappings
     */
    public Map getFieldMappings() {
        return fieldMapping;
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