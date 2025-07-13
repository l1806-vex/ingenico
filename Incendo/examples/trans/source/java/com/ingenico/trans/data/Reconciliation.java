package com.ingenico.trans.data;

import java.util.ArrayList;

/**
 * @author Sergey Lukashin
 */
public class Reconciliation implements Transaction {
    private int startId;
    private int endId;
    private int txnCount;
    private String status;

    private ArrayList<Row> rows = new ArrayList<Row>();

    /**
     * @param f
     *            the field to add
     */
    public void addRow(Row f) {
        rows.add(f);
    }

    /**
     * @return fields
     */
    public ArrayList<Row> getRows() {
        return rows;
    }

    public Row getRow(int id) {
        for (Row i : rows) {
            if (id == i.getId())
                return i;
        }
        return null;
    }

    /**
     * @param startId
     *            the startId to set
     */
    public void setStartId(int startId) {
        this.startId = startId;
    }

    /**
     * @return the startId
     */
    public int getStartId() {
        return startId;
    }

    /**
     * @param endId
     *            the endId to set
     */
    public void setEndId(int endId) {
        this.endId = endId;
    }

    /**
     * @return the endId
     */
    public int getEndId() {
        return endId;
    }

    /**
     * @param txnCount
     *            the txnCount to set
     */
    public void setTxnCount(int txnCount) {
        this.txnCount = txnCount;
    }

    /**
     * @return the txnCount
     */
    public int getTxnCount() {
        return txnCount;
    }

    /**
     * @param status
     *            the status to set
     */
    public void setStatus(String status) {
        this.status = status;
    }

    /**
     * @return the status
     */
    public String getStatus() {
        return status;
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