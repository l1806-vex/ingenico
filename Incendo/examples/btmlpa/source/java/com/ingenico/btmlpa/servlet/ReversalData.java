package com.ingenico.btmlpa.servlet;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import com.ingenico.tml.example.toolkit.TmlPostData;

/**
 * This class represents bean for reversal transaction data
 *
 * @author Eugene Pestov
 */
public class ReversalData extends TmlPostData {

    /**
     * fields mapping
     */
    private static final Map fieldMappings;

    /**
     * reversal transaction id
     */
    private int reversalTxnId;

    /**
     * submit mode
     */
    private String submitMode;

    /**
     * specifies fields mapping
     */
    static {

        HashMap hashMap = new HashMap();

        hashMap.put("transid", "reversalTxnId");
        hashMap.put("oebr.submit_mode", "submitMode");

        fieldMappings = Collections.unmodifiableMap(hashMap);

    }

    /**
     * Gets field mapping
     *
     * @return
     */
    public Map getFieldMappings() {
        return fieldMappings;
    }

    /**
     * Gets reversal transaction id
     *
     * @return reversal transaction id
     */
    public int getReversalTxnId() {
        return reversalTxnId;
    }

    /**
     * Sets reversal transaction id
     *
     * @param reversalTxnId reversal transaction id
     */
    public void setReversalTxnId(int reversalTxnId) {
        this.reversalTxnId = reversalTxnId;
    }

    /**
     * Gets submit mode
     *
     * @return submit mode
     */
    public String getSubmitMode() {
        return submitMode;
    }

    /**
     * Sets submit mode
     *
     * @param submitMode submit mode
     */
    public void setSubmitMode(String submitMode) {
        this.submitMode = submitMode;
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