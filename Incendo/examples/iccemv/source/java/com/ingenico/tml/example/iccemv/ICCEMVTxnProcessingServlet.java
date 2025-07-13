package com.ingenico.tml.example.iccemv;

import com.ingenico.tml.example.toolkit.TmlPostData;
import com.ingenico.tml.example.toolkit.TmlPostServlet;
import com.ingenico.util.http.HTTPResponse;
import com.ingenico.util.logging.Logger;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Date;

/**
 * This class processes icc emv transactions
 *
 * @author Eugene Pestov
 */
public class ICCEMVTxnProcessingServlet extends TmlPostServlet {

    /**
     * tml page in case of transaction processing failed
     */
    private static final String PAGE_AUTH_FAILED = "failed.tml";

    /**
     * tml page in case of transaction authorised
     */
    private static final String PAGE_AUTH_OK = "auth_ok.tml";

    /**
     * tml page in case of too big transaction amount
     */
    private static final String PAGE_AMOUNT_TOO_BIG = "amnt_big.tml";

    /**
     * logger
     */
    private static final Logger LOG =
            Logger.getLogger(ICCEMVTxnProcessingServlet.class.getName());

    /**
     * top limit
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
                             HttpServletResponse response,
                             TmlPostData dataObj)
            throws ServletException, IOException {

        ICCEMVTxnData simpleTxnData = (ICCEMVTxnData) dataObj;

        String amountStr = toPounds(String.valueOf(simpleTxnData.getAmount()));

        if (LOG.isDebugEnabled()) {
            String logMsg =
                    "Got authorization request:"
                    + "\n itid - "
                    + simpleTxnData.getItid()
                    + "\n date - "
                    + simpleTxnData.getDate()
                    + "\n----------------------------------------------"
                    + "\n transid\t- "
                    + simpleTxnData.getTransid()
                    + "\n payment.amount\t\t- "
                    + amountStr
                    + "\n card.pan\t- "
                    + simpleTxnData.getCard_number()
                    + "\n card.effective_date\t- "
                    + simpleTxnData.getCard_start()
                    + "\n card.expiry_date\t- "
                    + simpleTxnData.getCard_expiry();

            LOG.fine(logMsg);
        }

        Date today = new Date();
        String responsePage;
        // check the card expiry date against today
        if (today.before(simpleTxnData.getCard_expiry())) {
            // check amount against top limit
            if (simpleTxnData.getAmount() > topLimit) {
                if (LOG.isDebugEnabled()) {
                    LOG.fine("Transaction [id="
                            + simpleTxnData.getTransid()
                            + "]: failed; "
                            + "amount ("
                            + amountStr
                            + ") exceeds the top limit ("
                            + toPounds(String.valueOf(topLimit))
                            + ").");
                }
                responsePage = getResourceName(request, PAGE_AMOUNT_TOO_BIG);
            } else {
                // alles gut
                if (LOG.isDebugEnabled()) {
                    LOG.fine("Transaction [id="
                            + simpleTxnData.getTransid()
                            + "]: authorized.");
                }
                responsePage = getResourceName(request, PAGE_AUTH_OK);
            }
        } else {
            if (LOG.isDebugEnabled()) {
                LOG.fine("Transaction [id="
                        + simpleTxnData.getTransid()
                        + "]: failed; card expired");
            }
            responsePage = getResourceName(request, PAGE_AUTH_FAILED);
        }

        if ("online".equals(simpleTxnData.getSubmit_mode())) {
            // the request goes online
            // return the selected page
            getServletContext().getRequestDispatcher(responsePage).forward(request,
                    response);
        } else {
            // the request goes offline 
            // send an empty 200 response
            response.setStatus(HTTPResponse.HTTP_OK);
        }
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
     *
     * @throws ServletException in case of any exception occurs
     */
    public void init() throws ServletException {
        topLimit =
                Integer.parseInt(getServletConfig().getInitParameter("topLimit"));
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