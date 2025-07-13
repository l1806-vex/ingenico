package com.ingenico.tml.example.iccemv;

import com.ingenico.tml.example.toolkit.TmlPostData;
import com.ingenico.tml.example.toolkit.TmlPostServlet;
import com.ingenico.util.http.HTTPResponse;
import com.ingenico.util.logging.Logger;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

/**
 * This class extends TmlPostServlet with functionality specific for
 * ICC EMV application
 *
 * @author Eugene Pestov
 */
public class ICCEMVTxn2ProcessingServlet extends TmlPostServlet {

    /**
     * logger
     */
    private static final Logger LOG =
            Logger.getLogger(ICCEMVTxn2ProcessingServlet.class.getName());

    /**
     * Do tml post
     *
     * @param request  HTTP request
     * @param response HTTP response
     * @param dataObj  data to post
     * @throws ServletException in case of servlet error occcurs
     * @throws IOException      in case of I/O error occurs
     */
    protected void doTmlPost(HttpServletRequest request,
                             HttpServletResponse response,
                             TmlPostData dataObj)
            throws ServletException, IOException {

        ICCEMVTxn2Data simpleTxn2Data = (ICCEMVTxn2Data) dataObj;

        if (LOG.isDebugEnabled()) {
            String logMsg =
                    "Got offline authorization result request:"
                    + "\n itid - "
                    + simpleTxn2Data.getItid()
                    + "\n date - "
                    + simpleTxn2Data.getDate()
                    + "\n----------------------------------------------"
                    + "\n transid\t- "
                    + simpleTxn2Data.getTransid();

            LOG.fine(logMsg);
        }

        // the request always goes offline 
        // send an empty 200 response
        response.setStatus(HTTPResponse.HTTP_OK);
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