package com.ingenico.btmlpa;

/**
 * This calss represents an Ingenico terminal.
 * 
 * @author Eugene Pestov
 */
public class Terminal {

    /**
     * internal BTMLPA id
     */
    private long id = -1;

    /**
     * Ingenico Identifier
     */
    private String itid;

    /**
     * APACS TID
     */
    private String tid;

    /**
     * Default constructor
     */
    public Terminal() {
    }

    /**
     * Creates a <code>Terminal</code> with the given <code>id, ITID</code>
     * and <code>TID</code>.
     *
     * @param id   - internal BTMLPA id
     * @param itid - Ingenico Identifier
     * @param tid  - APACS TID
     */
    public Terminal(long id, String itid, String tid) {
        this.id = id;
        this.itid = itid;
        this.tid = tid;
    }

    /**
     * Gets terminal id
     *
     * @return terminal id
     */
    public long getId() {
        return id;
    }

    /**
     * Gets terminal itid
     *
     * @return terminal itid
     */
    public String getItid() {
        return itid;
    }

    /**
     * Gets APACS terminal id
     *
     * @return APACS terminal id
     */
    public String getTid() {
        return tid;
    }

    /**
     * Sets terminal id in BTMLPA
     *
     * @param id terminal id in BTMLPA
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     * Sets Ingenico terminal id
     *
     * @param itid Ingenico terminal id
     */
    public void setItid(String itid) {
        this.itid = itid;
    }

    /**
     * Sets APACS terminal id
     *
     * @param tid APACS terminal id
     */
    public void setTid(String tid) {
        this.tid = tid;
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