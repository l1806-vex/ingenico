package com.ingenico.btmlpa.servlet;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.ingenico.btmlpa.BTMLPAException;
import com.ingenico.btmlpa.Terminal;
import com.ingenico.tml.example.toolkit.TmlPostData;
import com.ingenico.util.logging.Logger;

/**
 * This class extends BaseServlet with functionality specific for
 * ICC Ofline submit
 *
 * @author Eugene Pestov
 */
public class ICC2OfflineSubmitServlet extends BaseServlet {

    /**
     * logger
     */
    private static Logger LOG = Logger.getLogger(ICC2OfflineSubmitServlet.class.getName());

    /**
     * Processes btmlpa request
     * For now it is not yet implemented
     *
     * @param terminal terminal
     * @param request  HTTP request
     * @param response HTTP response
     * @param data     tml post data
     * @return dtml page that represents container for tml reply
     * @throws BTMLPAException in case of any error occur
     */
    protected String processBTMLPARequest(Terminal terminal,
                                          HttpServletRequest request, HttpServletResponse response,
                                          TmlPostData data) throws BTMLPAException {

        LOG.info("Second offline submit is not implemented yet");

        return null;
    }

    /**
     * This method gets submit mode
     * @param tmlPostData tml post data
     * @return true if online false otherwise
     */
    protected boolean getSubmitMode(TmlPostData tmlPostData) {
        return false;
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