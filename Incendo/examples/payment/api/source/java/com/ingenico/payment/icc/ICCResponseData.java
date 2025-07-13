package com.ingenico.payment.icc;

/**
 * This class represents bean that contains response data for ICC EMV
 * transaction
 *
 * @author Eugene Pestov
 */
public class ICCResponseData {

    /**
     * Optional Additional Data
     */
    private byte[] additionalData;

    /**
     * Authorisation Response Cryptogram
     */
    private byte[] authResponseCryptogram;

    /**
     * Issuer Application Data
     */
    private byte[] issuerAuthenticationData;

    /**
     * Issuer Script Data
     */
    private byte[] issuerScript;

    /**
     * Gets optional additional data
     *
     * @return optional additional data
     */
    public byte[] getAdditionalData() {
        return additionalData;
    }

    /**
     * Gets authorisation response cryptogram
     *
     * @return authorisation response cryptogram
     */
    public byte[] getAuthResponseCryptogram() {
        return authResponseCryptogram;
    }

    /**
     * Gets issuer application data
     *
     * @return issuer application data
     */
    public byte[] getIssuerAuthenticationData() {
        return issuerAuthenticationData;
    }

    /**
     * Gets issuer script data
     *
     * @return issuer script data
     */
    public byte[] getIssuerScript() {
        return issuerScript;
    }

    /**
     * Sets optional additional data
     *
     * @param bs optional additional data
     */
    public void setAdditionalData(byte[] bs) {
        additionalData = bs;
    }

    /**
     * Sets authorisation response cryptogram
     *
     * @param bs authorisation response cryptogram
     */
    public void setAuthResponseCryptogram(byte[] bs) {
        authResponseCryptogram = bs;
    }

    /**
     * Sets issuer application data
     *
     * @param bs issuer application data
     */
    public void setIssuerAuthenticationData(byte[] bs) {
        issuerAuthenticationData = bs;
    }

    /**
     * Sets issuer script data
     *
     * @param bs issuer script data
     */
    public void setIssuerScript(byte[] bs) {
        issuerScript = bs;
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
