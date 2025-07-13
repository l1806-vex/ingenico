package com.ingenico.tml.example.magcard;

import java.io.IOException;
import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.ingenico.tml.example.toolkit.TmlPostData;
import com.ingenico.tml.example.toolkit.TmlPostServlet;
import com.ingenico.util.logging.Logger;

/**
 * This servlet processes the terminal transaction submit
 *
 * @author Eugene Pestov
 */
public class MagCardTxnProcessingServlet extends TmlPostServlet {

    /**
     * tml page in case transaction authorisation failed
     */
    private static final String PAGE_AUTH_FAILED = "failed.tml";

    /**
     * tml page in case of transaction authorisation passed
     */
    private static final String PAGE_AUTH_OK = "auth_ok.tml";

    /**
     * tml page in case of transaction amount exceeds transactoin amount limit
     */
    private static final String PAGE_AMOUNT_TOO_BIG = "amnt_big.tml";

    /**
     * logger
     */
    private static final Logger LOG = Logger
            .getLogger(MagCardTxnProcessingServlet.class.getName());

    /**
     * transaction top limit amount
     */
    private int topLimit = 1000;

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
            HttpServletResponse response, TmlPostData dataObj)
            throws ServletException, IOException {

        MagCardTxnData simpleTxnData = (MagCardTxnData) dataObj;

        String amountStr = toPounds(String.valueOf(simpleTxnData.getAmount()));

        if (LOG.isDebugEnabled()) {
            String logMsg = "Got authorization request:"
                    + "\n terminal.itid - " + simpleTxnData.getItid()
                    + "\n date - " + simpleTxnData.getDate()
                    + "\n----------------------------------------------"
                    + "\n transid\t\t- " + simpleTxnData.getTransid()
                    + "\n payment.amount\t\t- "
                    + amountStr
                    + "\n card.parser.type\t- "
                    + simpleTxnData.getCard_parser()
                    + "\n card.cardholder_name\t- "
                    + simpleTxnData.getCard_holder() + "\n card.pan\t- "
                    + simpleTxnData.getCard_number()
                    + "\n card.issuer_name\t- "
                    + simpleTxnData.getCard_issuer()
                    + "\n card.issue_number\t- "
                    + simpleTxnData.getCard_issue() + "\n card.scheme\t- "
                    + simpleTxnData.getCard_scheme()
                    + "\n card.effective_date\t- "
                    + simpleTxnData.getCard_start() + "\n card.expiry_date\t- "
                    + simpleTxnData.getCard_expiry()
                    + "\n card.mag.iso2_track\t- "
                    + simpleTxnData.getIso2_track();

            LOG.fine(logMsg);
        }

        Date today = new Date();
        String responsePage;
        // check the card expiry date against today
        if (today.before(simpleTxnData.getCard_expiry())) {
            // check amount against top limit
            if (simpleTxnData.getAmount() > topLimit) {
                if (LOG.isDebugEnabled()) {
                    LOG.fine("Transaction [id=" + simpleTxnData.getTransid()
                            + "]: failed; " + "amount ("
                            + amountStr
                            + ") exceeds the top limit (" + toPounds(String.valueOf(topLimit)) + ").");
                }
                responsePage = getResourceName(request, PAGE_AMOUNT_TOO_BIG);
            } else {
                // alles gut
                if (LOG.isDebugEnabled()) {
                    LOG.fine("Transaction [id=" + simpleTxnData.getTransid()
                            + "]: authorized.");
                }
                responsePage = getResourceName(request, PAGE_AUTH_OK);
            }
        } else {
            if (LOG.isDebugEnabled()) {
                LOG.fine("Transaction [id=" + simpleTxnData.getTransid()
                        + "]: failed; card expired");
            }
            responsePage = getResourceName(request, PAGE_AUTH_FAILED);
        }

        // return the selected page
        getServletContext().getRequestDispatcher(responsePage).forward(request,
                response);
    }

    /**
     * This method translates resource name to resource name special for
     * requestor type
     * @param req http request
     * @param resource resource name
     * @return new resource name special for requestor type
     */
    public String getResourceName(HttpServletRequest req, String resource) {
        String userAgent = req.getHeader("User-Agent");
        String term = "other";

        if ((userAgent != null) && (userAgent.length() >= 4)) {
            term = userAgent.substring(userAgent.length() - 4, userAgent.length());
        }
        String resourceValue = "";
        String mapping;
        if (term.equalsIgnoreCase(RequestFilter.TERMINAL_8550)) {
            mapping = (String)RequestFilter.resourceMapping.get(RequestFilter.TERMINAL_8550);
            resourceValue = mapping + "/" + resource;
        }
        else if (term.equalsIgnoreCase(RequestFilter.TERMINAL_5100)) {
            mapping = (String)RequestFilter.resourceMapping.get(RequestFilter.TERMINAL_5100);
            resourceValue = mapping + "/" + resource;
        }
        else {
            mapping = (String)RequestFilter.resourceMapping.get(RequestFilter.TERMINAL_OTHER);
            resourceValue = mapping + "/" + resource;
        }
        return resourceValue;
    }

    /**
     * Initialises servlet
     * @throws ServletException in case of any errors occur
     */
    public void init() throws ServletException {
        topLimit = Integer.parseInt(getServletConfig().getInitParameter(
                "topLimit"));
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