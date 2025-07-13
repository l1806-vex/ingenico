package com.ingenico.btmlpa.servlet;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import com.ingenico.tml.example.toolkit.TmlPostData;

/**
 * This class represents a bean for icc offline submit
 * 
 * @author Eugene Pestov
 */
public class ICC2OfflineSubmitData extends TmlPostData {

    /**
     * field mappings
     */
    private static final Map fieldMappings;

    /**
     * transaction id
     */
    private int transid;

    /**
     * icc transaction certificate
     */
    private byte[] icc_tc;

    /**
     * icc application authentication cryptogram
     */
    private byte[] icc_aac;

    /**
     * Initialise field mappings
     */
    static {

        HashMap hashMap = new HashMap();

        hashMap.put("card.emv.aac", "icc_aac");
        hashMap.put("card.emv.tc", "icc_tc");
        hashMap.put("transid", "icc_transid");

        fieldMappings = Collections.unmodifiableMap(hashMap);

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
     * Sets icc application authentication cryptogram
     * 
     * @param icc_aac
     *            icc application authentication cryptogram
     */
    public void setIcc_aac(byte[] icc_aac) {
        this.icc_aac = icc_aac;
    }

    /**
     * Gets icc transaction certificate
     * 
     * @return icc transaction certificate
     */
    public byte[] getIcc_tc() {
        return icc_tc;
    }

    /**
     * Sets icc transaction certificate
     * 
     * @param icc_tc
     *            icc transaction certificate
     */
    public void setIcc_tc(byte[] icc_tc) {
        this.icc_tc = icc_tc;
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
     * Sets transaction id
     * 
     * @param transid
     *            transaction id
     */
    public void setTransid(int transid) {
        this.transid = transid;
    }

    /**
     * Gets field mapping
     * 
     * @return field mapping
     */
    public Map getFieldMappings() {
        return fieldMappings;
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