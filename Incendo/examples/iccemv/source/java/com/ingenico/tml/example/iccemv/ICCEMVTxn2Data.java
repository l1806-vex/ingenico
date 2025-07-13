package com.ingenico.tml.example.iccemv;

import com.ingenico.tml.example.toolkit.TmlPostData;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

/**
 * This class represen5ts bean for icc emv transaction processing
 *
 * @author Eugene Pestov
 */
public class ICCEMVTxn2Data extends TmlPostData {

    /**
     * field mappings
     */
    private static final Map fieldMappings;

    /**
     * icc application authentication cryptogram
     */
    private byte icc_aac[];

    /**
     * transaction certificate
     */
    private byte icc_tc[];

    /**
     * transaction id
     */
    private int transid;

    /**
     * specifies field mappings
     */
    static {

        HashMap hashMap = new HashMap();

        hashMap.put("card.emv.aac", "icc_aac");
        hashMap.put("card.emv.tc", "icc_tc");
        hashMap.put("transid", "transid");

        fieldMappings = Collections.unmodifiableMap(hashMap);

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
     * Sets transaction certificate
     *
     * @param bs transaction certificate
     */
    public void setIcc_tc(byte[] bs) {
        icc_tc = bs;
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
     * Gets transaction certificate
     *
     * @return transaction certificate
     */
    public byte[] getIcc_tc() {
        return icc_tc;
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
     * @param i transaction id
     */
    public void setTransid(int i) {
        transid = i;
    }

    /**
     * Gets field mappings
     *
     * @return field mappings
     */
    public Map getFieldMappings() {
        return fieldMappings;
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