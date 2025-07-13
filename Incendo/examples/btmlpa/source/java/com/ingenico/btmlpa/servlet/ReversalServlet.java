package com.ingenico.btmlpa.servlet;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.ingenico.btmlpa.Application;
import com.ingenico.btmlpa.BTMLPAException;
import com.ingenico.btmlpa.IncorrectValueException;
import com.ingenico.btmlpa.PaymentTransaction;
import com.ingenico.btmlpa.Terminal;
import com.ingenico.btmlpa.TransactionConstants;
import com.ingenico.tml.example.toolkit.TmlPostData;
import com.ingenico.util.logging.Logger;

/**
 * This class extends BaseServlet in part of reversal transaction
 * processing functionality
 *
 * @author Eugene Pestov
 */
public class ReversalServlet extends BaseServlet {

    private static Logger LOG = Logger
            .getLogger(ReversalServlet.class.getName());

    /**
     * Processes reversal btmlpa request
     *
     * @param terminal terminal
     * @param request  HTTP request
     * @param response HTTP response
     * @param data     tml post data
     * @return dtml page that represents container for tml reply
     * @throws BTMLPAException in case of any errors occur
     */
    protected String processBTMLPARequest(Terminal terminal,
                                          HttpServletRequest request, HttpServletResponse response,
                                          TmlPostData data) throws BTMLPAException {

        ReversalData reversalData = (ReversalData) data;

        int reversalTxnId = reversalData.getReversalTxnId();

        PaymentTransaction txn = Application.getInstance()
                .findPaymentTransaction(terminal, reversalTxnId);

        String screen = getResourceName(request, "reversed.tml");

        if (txn == null) {
            // no transaction with such txn id - do nothing
            screen = getResourceName(request, "error.dtml");
            request.setAttribute("errorMessage",
                    "Reversal failed. \nWrong transaction ID");
            request.setAttribute("nextScreen", "init_prompt");
        } else {
            switch (txn.getState()) {
                case TransactionConstants.STATE.APPROVED:
                    // the transaction has been approved by acquirer
                    // so an explicit reversal shuold be sent
                    try {
                        int curtype = txn.getType();
                        txn.setType(4);
                        Application.getInstance().reverseTransaction(txn);
                        // store the transaction
                        txn.setType(curtype);
                        Application.getInstance().savePaymentTransaction(txn);
                    } catch (IncorrectValueException e) {
                        request.setAttribute("errorMessage",
                                "Reversal failed.");
                        request.setAttribute("nextScreen", "init_prompt");
                    }
                    break;
                case TransactionConstants.STATE.NEW:
                    LOG.info("Cancelling transaction for a card: Card PAN: " + null2Empty(txn.getCardNumber() + "\n" +
                    "Card Expiry Date: " + null2Empty(txn.getCardExpiry()) + "\n" +
                    "Card Effective Date: " + null2Empty(txn.getCardStart()) + "\n" +
                    "Issue Number: " + txn.getCardIssue() + "\n" +
                    "Amount: " + toPounds(String.valueOf(txn.getAmount())) + "\n" +
                    "Cashback Amount: " + toPounds(String.valueOf(txn.getAmountOther())) + "\n" +
                    "Currency: " + null2Empty(txn.getCurrencyCode())));
                    // just set state to CANCELED
                    txn.setState(TransactionConstants.STATE.CANCELED);
                    // store the transaction
                    Application.getInstance().savePaymentTransaction(txn);
                    break;
                default:
                    screen = getResourceName(request, "error.dtml");
                    request.setAttribute("errorMessage",
                            "Reversal failed. \nWrong transaction state");
                    request.setAttribute("nextScreen", "init_prompt");
                    break;
            }

        }

        return screen;
    }

    /**
     * This method gets submit mode
     * @param tmlPostData tml post data
     * @return true if online false otherwise
     */
    protected boolean getSubmitMode(TmlPostData tmlPostData) {
        boolean offline = false;
        ReversalData reversalData = (ReversalData) tmlPostData;
        if (reversalData.getSubmitMode().equalsIgnoreCase("offline")) {
            offline = true;
        }
        return offline;
    }

    private static String null2Empty(Object obj) {
        return obj == null ? "" : obj.toString();
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