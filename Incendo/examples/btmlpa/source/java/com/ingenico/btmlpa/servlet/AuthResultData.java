package com.ingenico.btmlpa.servlet;

/**
 * This class represent a bean for Authorisation Result Data
 *
 * @author Eugene Pestov
 */
public class AuthResultData {

    /**
     * authorisation code
     */
    private String authorisationCode;

    /**
     * authorisation message
     */
    private String message;

    /**
     * icc arpc
     */
    private String icc_arpc;

    /**
     * issuer script
     */
    private String issuer_script;

    /**
     * issuer authorisation
     */
    private String issuer_auth;

    /**
     * Checks if transaction approved
     *
     * @return true if transaction approved false otherwise
     */
    public boolean isApproved() {
        return authorisationCode != null;
    }

    /**
     * Gets the authorization code
     *
     * @return authorisationCode
     */
    public String getAuthorisationCode() {
        return authorisationCode;
    }

    /**
     * Sets authorisation code
     *
     * @param authorisationCode authorisation code
     */
    public void setAuthorisationCode(String authorisationCode) {
        this.authorisationCode = authorisationCode;
    }

    /**
     * Gets icc_arpc
     *
     * @return icc_arpc
     */
    public String getIcc_arpc() {
        return icc_arpc;
    }

    /**
     * Sets icc_arpc
     *
     * @param icc_arpc icc_arpc
     */
    public void setIcc_arpc(String icc_arpc) {
        this.icc_arpc = icc_arpc;
    }

    /**
     * Gets issuer authorisation
     *
     * @return issuer authorisation
     */
    public String getIssuer_auth() {
        return issuer_auth;
    }

    /**
     * Sets issuer authorisation
     *
     * @param issuer_auth issuer authorisation
     */
    public void setIssuer_auth(String issuer_auth) {
        this.issuer_auth = issuer_auth;
    }

    /**
     * Gets issuer script
     *
     * @return issuer script
     */
    public String getIssuer_script() {
        return issuer_script;
    }

    /**
     * Sets issuer script
     *
     * @param issuer_script issuer script
     */
    public void setIssuer_script(String issuer_script) {
        this.issuer_script = issuer_script;
    }

    /**
     * Gets authorisation message
     *
     * @return authorisation message
     */
    public String getMessage() {
        return message;
    }

    /**
     * Sets authorisation message
     *
     * @param message authorisation message
     */
    public void setMessage(String message) {
        this.message = message;
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