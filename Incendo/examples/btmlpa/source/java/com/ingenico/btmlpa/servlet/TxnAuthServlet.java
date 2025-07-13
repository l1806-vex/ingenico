package com.ingenico.btmlpa.servlet;

import java.util.Date;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.ingenico.btmlpa.Application;
import com.ingenico.btmlpa.BTMLPAException;
import com.ingenico.btmlpa.Constants;
import com.ingenico.btmlpa.IncorrectValueException;
import com.ingenico.btmlpa.PaymentTransaction;
import com.ingenico.btmlpa.Terminal;
import com.ingenico.btmlpa.TransactionConstants;
import com.ingenico.payment.CardDate;
import com.ingenico.tml.example.toolkit.TmlPostData;
import com.ingenico.tml.example.toolkit.Utils;
import com.ingenico.util.OegwDateUtils;
import com.ingenico.util.logging.Logger;

/**
 * This class extends BaseServlet with functionality specific for magcard and
 * icc transaction processing (first post)
 *
 * @author Eugene Pestov
 */
public class TxnAuthServlet extends BaseServlet {

    /**
     * logger
     */
    private static Logger LOG = Logger
            .getLogger(TxnAuthServlet.class.getName());

    // Constants used internally; unit is milliseconds

    /**
     * Process btmlpa request
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

        long durStarted = System.currentTimeMillis();

        TxnAuthData magCardAuthData = (TxnAuthData) data;

        PaymentTransaction txn = Application.getInstance()
                .findPaymentTransaction(terminal, magCardAuthData.getTransid());

        if (txn == null) {

            txn = new PaymentTransaction();

            txn.setState(TransactionConstants.STATE.NEW);
            txn.setStarted(OegwDateUtils.getCurrentTimeGMT());

            txn.setTerminal(terminal);
            txn.setTerminalTransactionId(magCardAuthData.getTransid());
            txn.setPostID(magCardAuthData.getPostId());
            txn.setSubmitMode(magCardAuthData.getSubmit_mode());
            txn.setType(convertPaymentType(magCardAuthData.getTrans_type()));

            Date txn_date = magCardAuthData.getTxn_date();
            if (txn_date != null) {
                long millis = txn_date.getTime();
                txn.setTerminalTransactionDate(OegwDateUtils.getTimeGMT(millis));
            } else {
                txn.setTerminalTransactionDate(OegwDateUtils.getCurrentTimeGMT());
            }

            Date post_date = magCardAuthData.getDate();
            if (post_date != null) {
                long millis = post_date.getTime();
                txn.setPostTransactionDate(OegwDateUtils.getTimeGMT(millis));
            }

            txn.setAmount(magCardAuthData.getAmount());                        
            
            if (txn.getType() == TransactionConstants.TYPE.SALECASHBACK) {
                if (magCardAuthData.getAmount_other() == Constants.NOT_SPECIFIED) {
                    throw new BTMLPAException("Cashback amount should be specified.");
                }
                txn.setAmountOther(magCardAuthData.getAmount_other());
            }
            txn.setCurrencyCode(magCardAuthData.getCurrency_code());

            txn.setCardNumber(magCardAuthData.getCard_number());
            txn.setCardHolderName(magCardAuthData.getCard_holdername());
            txn.setCardIssue(magCardAuthData.getCard_issue());
            txn.setCardInputType(magCardAuthData.getCard_input_mode());
            txn.setIso2Track(magCardAuthData.getIso2_track());

            try {
                Date expiry_date = magCardAuthData.getCard_expiry();
                if (expiry_date != null) {
                    txn.setCardExpiry(new CardDate(expiry_date));
                }

                Date start_date = magCardAuthData.getCard_start();
                if (start_date != null) {
                    txn.setCardStart(new CardDate(start_date));
                }
            }
            catch (IllegalArgumentException e) {
                if (txn != null) {
                    txn.setState(TransactionConstants.STATE.DECLINED);
                    Application.getInstance().savePaymentTransaction(txn);
                }
                LOG.severe("Incorrect transaction data: " + e.getMessage());
                throw new BTMLPAException("Incorrect Data.");
            }

            if (txn.getCardInputType() == TransactionConstants.INPUT_METHOD.ICC) {

                txn.setIcc_app(magCardAuthData.getIcc_aid());
                txn.setIcc_aip(magCardAuthData.getIcc_aip());
                txn.setIcc_auc(magCardAuthData.getIcc_auc());
                txn.setIcc_atc(magCardAuthData.getIcc_atc());
                txn.setIcc_aac(magCardAuthData.getIcc_aac());
                txn.setIcc_tc(magCardAuthData.getIcc_tc());
                txn.setIcc_arqc(magCardAuthData.getIcc_arqc());
                txn.setIcc_iad(magCardAuthData.getIcc_iad());
                txn.setIcc_tvr(magCardAuthData.getIcc_tvr());
                txn.setIcc_unumber(magCardAuthData.getIcc_unumber());
            }

            // save info that request received
            Application.getInstance().savePaymentTransaction(txn);

        } else {
            // check that we get the same postponed request
            if (!txn.getPostID().equals(magCardAuthData.getPostId())) {
                // if not than signalise an error
                LOG.warning("Transaction processing failed. "
                        + "Duplicate transaction id: "
                        + magCardAuthData.getTransid());

                throw new BTMLPAException("Transaction has a duplicate id.");
            }

            // set submit mode to offline
            txn.setSubmitMode("offline");
            // and save this
            Application.getInstance().savePaymentTransaction(txn);
        }

        if (txn.getState() == TransactionConstants.STATE.NEW) {
            try {
                // authorise the transaction
                Application.getInstance().authoriseTransaction(txn);
            } catch (IncorrectValueException e) {
                if (txn != null) {
                    txn.setState(TransactionConstants.STATE.DECLINED);
                    Application.getInstance().savePaymentTransaction(txn);
                }
                LOG.severe("Incorrect transaction data: " + e.getMessage());
                throw new BTMLPAException("Incorrect data.");
            }

            // set duration
            txn.setDuration(System.currentTimeMillis() - durStarted);

            // save response into the database
            Application.getInstance().savePaymentTransaction(txn);
        }

        String page = null;

        if ("online".equals(magCardAuthData.getSubmit_mode())) {

            AuthResultData authResult = new AuthResultData();
            authResult.setAuthorisationCode(txn.getAuthorisationCode());
            authResult.setMessage(txn.getMessageFromAcquirer());
            authResult.setIcc_arpc(Utils.encodeBase64(txn.getIcc_arpc()));
            authResult.setIssuer_script(Utils.encodeBase64(txn
                    .getIssuer_script()));
            authResult.setIssuer_auth(Utils.encodeBase64(txn.getIssuer_auth()));

            request.setAttribute("authResult", authResult);

            if (txn.getCardInputType() == TransactionConstants.INPUT_METHOD.ICC) {
                page = getResourceName(request, "icc_auth_rslt.dtml");
            } else {
                page = getResourceName(request, "mag_auth_rslt.dtml");
            }

        } else {
            // send nothing
        }

        return page;
    }
    
    private static int convertPaymentType(String paymentType) throws BTMLPAException {
    	if (paymentType.equalsIgnoreCase("debit")) {
    		return 1;
    	}
    	else if (paymentType.equalsIgnoreCase("cashback")) {
    		return 2;
    	}
    	else if (paymentType.equalsIgnoreCase("credit")) {
    		return 3;
    	}
    	else if (paymentType.equalsIgnoreCase("reversal")) {
    		return 1;
    	}
    	else {
    		throw new BTMLPAException("Unsupported payment type: '" + paymentType + "'");
    	}
    }

    /**
     * This method gets submit mode
     * @param tmlPostData tml post data
     * @return true if online false otherwise
     */
    protected boolean getSubmitMode(TmlPostData tmlPostData) {
        boolean offline = false;
        TxnAuthData CardAuthData = (TxnAuthData) tmlPostData;
        if (CardAuthData.getSubmit_mode().equalsIgnoreCase("offline")) {
            offline = true;
        }
        return offline;
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