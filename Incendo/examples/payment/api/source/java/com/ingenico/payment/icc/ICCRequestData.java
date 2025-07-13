package com.ingenico.payment.icc;

/**
 * This class represents bean for ICC EMV transaction request
 *
 * @author Eugene Pestov
 */
public class ICCRequestData {

    /**
     * Application identifier
     */
    private String applicationId;

    /**
     * Application Interchange Profile
     */
    private int applicationInterchangeProfile;

    /**
     * Application Transaction Counter
     */
    private int applTxnCounter;

    /**
     * Authorisation Request Cryptogram
     */
    private byte[] authRequestCryptogram;

    /**
     * Cardholder Verification Result
     */
    private String chVerificationResult;

    /**
     * Issuer Application Data
     */
    private byte[] issuerApplData;

    /**
     * Terminal Verification Results
     */
    private byte[] termVerificationResult;

    /**
     * Unpredictable Number
     */
    private int uNumber;


    /**
     * Gets application identifier
     *
     * @return application identifier
     */
    public String getApplicationId() {
        return applicationId;
    }

    /**
     * Gets application interchange profile
     *
     * @return application interchange profile
     */
    public int getApplicationInterchangeProfile() {
        return applicationInterchangeProfile;
    }

    /**
     * Gets application transaction counter
     *
     * @return application transaction counter
     */
    public int getApplTxnCounter() {
        return applTxnCounter;
    }

    /**
     * Gets authorisation request cryptogram
     *
     * @return authorisation request cryptogram
     */
    public byte[] getAuthRequestCryptogram() {
        return authRequestCryptogram;
    }

    /**
     * Gets cardholder verification result
     *
     * @return cardholder verification result
     */
    public String getChVerificationResult() {
        return chVerificationResult;
    }

    /**
     * Gets issuer application data
     *
     * @return issuer application data
     */
    public byte[] getIssuerApplData() {
        return issuerApplData;
    }

    /**
     * Gets terminal verification results
     *
     * @return terminal verification results
     */
    public byte[] getTermVerificationResult() {
        return termVerificationResult;
    }

    /**
     * Gets unpredictable number
     *
     * @return unpredictable number
     */
    public int getUNumber() {
        return uNumber;
    }

    /**
     * Sets application identifier
     *
     * @param string application identifier
     */
    public void setApplicationId(String string) {
        applicationId = string;
    }

    /**
     * Sets application interchange profile
     *
     * @param i application interchange profile
     */
    public void setApplicationInterchangeProfile(int i) {
        applicationInterchangeProfile = i;
    }

    /**
     * Sets application transaction counter
     *
     * @param i application transaction counter
     */
    public void setApplTxnCounter(int i) {
        applTxnCounter = i;
    }

    /**
     * Sets authorisation request cryptogram
     *
     * @param bs authorisation request cryptogram
     */
    public void setAuthRequestCryptogram(byte[] bs) {
        authRequestCryptogram = bs;
    }

    /**
     * Sets cardholder verification result
     *
     * @param string cardholder verification result
     */
    public void setChVerificationResult(String string) {
        chVerificationResult = string;
    }

    /**
     * Sets issuer application data
     *
     * @param bs issuer application data
     */
    public void setIssuerApplData(byte[] bs) {
        issuerApplData = bs;
    }

    /**
     * Sets terminal verification results
     *
     * @param bs terminal verification results
     */
    public void setTermVerificationResult(byte[] bs) {
        termVerificationResult = bs;
    }

    /**
     * Sets unpredictable number
     *
     * @param l unpredictable number
     */
    public void setUNumber(int l) {
        uNumber = l;
    }
}
/*
 * Incendo Online Gateway
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
