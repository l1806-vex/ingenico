package com.ingenico.btmlpa;

import java.sql.Timestamp;
import java.util.Locale;
import java.util.Properties;

import com.ingenico.btmlpa.db.BTMLPA;
import com.ingenico.payment.CardDetails;
import com.ingenico.payment.CardInputType;
import com.ingenico.payment.FactoryInstantiationException;
import com.ingenico.payment.PaymentEngine;
import com.ingenico.payment.PaymentEngineFactory;
import com.ingenico.payment.PaymentException;
import com.ingenico.payment.PaymentHelper;
import com.ingenico.payment.PaymentRequest;
import com.ingenico.payment.PaymentResponse;
import com.ingenico.payment.PaymentType;
import com.ingenico.payment.icc.ICCRequestData;
import com.ingenico.payment.icc.ICCResponseData;
import com.ingenico.util.OegwDateUtils;
import com.ingenico.util.configuration.Configuration;
import com.ingenico.util.exception.SystemException;
import com.ingenico.webappl.db.ConnectionPool;
import com.ingenico.webappl.db.DBClient;
import com.ingenico.webappl.db.DBException;
import com.ingenico.webappl.db.DBManager;

/**
 * This calss contains businness logic of the BTMLPA application.
 * 
 * @author Eugene Pestov
 */
public class Application {

    /**
     * instance of the class
     */
    private static Application instance = new Application();

    /**
     * application configuration
     */
    private Configuration configuration;

    /**
     * flag shows whether the instance was initialised
     */
    private boolean initialized;

    /**
     * instance of PaymentEngine factory
     */
    private PaymentEngineFactory paymentEngineFactory;

    /**
     * Gets the single instance of the class.
     *
     * @return Application instance
     */
    public static Application getInstance() {
        return instance;
    }

    /**
     * Default constructor
     */
    private Application() {
    }

    /**
     * Gets configuration
     *
     * @return configuration
     */
    public Configuration getConfiguration() {
        return configuration;
    }

    /**
     * Gets payment engine factory
     *
     * @return payment engine factory
     */
    public PaymentEngineFactory getPaymentEngineFactory() {
        return paymentEngineFactory;
    }

    /**
     * Finds terminal in database according to specified itid and returns
     * terminal as bean
     *
     * @param itid itid
     * @return terminal bean
     * @throws SystemException in case of any errors occur
     */
    public Terminal findTerminal(String itid) throws SystemException {

        Terminal term = null;
        try {
            term = BTMLPA.getTerminal(itid, "");
            return term;
        }
        catch (DBException e) {
            throw new SystemException(e);
        }

    }

    /**
     * Gets payment transaction in database according to terminal and
     * transaction id data
     *
     * @param terminal      terminal bean
     * @param terminalTxnID transaction id
     * @return payment transaction bean
     */
    public PaymentTransaction findPaymentTransaction(final Terminal terminal,
                                                     long terminalTxnID) {

        PaymentTransaction txn = null;
        try {
            txn = BTMLPA.getTxn(terminal, terminalTxnID, "");
            return txn;
        }
        catch (DBException e) {
            throw new SystemException(e);
        }

    }

    /**
     * Initialises application class including payment engine, hibernate
     *
     * @param config configuration
     */
    public synchronized void initialize(Configuration config) {

        if (initialized) {
            return;
        }

        Locale.setDefault(Locale.ENGLISH);

        this.configuration = config;

        Properties props = new Properties();

        //
        // set up PaymentEngineFactory
        //
        props.setProperty(PaymentHelper.FACTORY_CLASS, configuration
                .getString(Constants.ENGINE_FACTORY));

        // set provider specific properties
        int dummy_delay = configuration.getInt(Constants.DUMMY_DELAY, 1);
        props.setProperty("com.ingenico.payment.impl.dummy.delay",
                String.valueOf(dummy_delay));
        int top_limit = configuration.getInt(Constants.TOP_LIMIT, 10000);
        props.setProperty("com.ingenico.payment.impl.dummy.topLimit",
                String.valueOf(top_limit));

        try {
            // get a configured PaymentEngineFactory instance
            paymentEngineFactory = PaymentHelper.getPaymentEngineFactory(props);
        } catch (FactoryInstantiationException e) {
            // TODO more graceful exception handling
            throw new SystemException(e);
        }

        // database stuff initialisation
        try {
            java.util.Properties prTmpDriverUrl = new java.util.Properties();
            prTmpDriverUrl.put("driver", configuration.getString(
                    Constants.JDBC_DRIVER));
            prTmpDriverUrl.put("url", configuration.getString(
                    Constants.URL_TO_DATABASE));

            String sUser = configuration.getString(Constants.DB_USER, "");
            String sPassword = configuration.getString(Constants.DB_PASSWORD, "");

            java.util.Properties prTmpUserPasswd = new java.util.Properties();
            prTmpUserPasswd.put("user", sUser);
            prTmpUserPasswd.put("password", sPassword);

            DBManager.init(prTmpDriverUrl);
            DBManager.registerNewDBManager((DBManager)
                    (Class.forName("com.ingenico.webappl.db.DBManager" +
                    configuration.getString(Constants.DBMS_NAME)).newInstance()));

            int iMax = configuration.getInt(Constants.CONNECTION_POOL_MAX, 50);
            int iMin = configuration.getInt(Constants.CONNECTION_POOL_MIN, 10);

            ConnectionPool cp = new ConnectionPool(iMax, iMin, prTmpUserPasswd);

            ConnectionPool.registerNewConnectionPool(cp);

            if (!DBClient.isInit()) {
                DBClient.init();
            }
        }
        catch (Exception e) {
            // TODO more graceful exception handling
            throw new SystemException(e);
        }

        // mark as initializes
        initialized = true;
    }

    /**
     * Checks if application class is initialised
     *
     * @return true if application class is initialised false otherwise
     */
    public synchronized boolean isInitialized() {
        return initialized;
    }

    /**
     * Saves payment transaction into the database
     *
     * @param pmntTxn payment transaction
     * @throws SystemException in case of any errors occur
     */
    public void savePaymentTransaction(PaymentTransaction pmntTxn)
            throws SystemException {

        try {
            BTMLPA.saveTxn(pmntTxn, "");
        }
        catch (DBException e) {
            throw new SystemException(e);
        }

    }

    /**
     * Authorise transaction
     *
     * @param txn payment transaction
     * @throws IncorrectValueException in case of incorrect value passed
     */
    public void authoriseTransaction(PaymentTransaction txn)
            throws IncorrectValueException {

        PaymentRequest paymentRequest = new PaymentRequest();

        paymentRequest.setTid(txn.getTerminal().getTid());

        CardDetails cardDetails = new CardDetails();
        cardDetails.setTrack2Data(txn.getIso2Track());
        cardDetails.setPan(txn.getCardNumber());
        cardDetails.setIssueNumber(txn.getCardIssue());
        cardDetails.setCardInputType(getCardInputType(txn.getCardInputType()));

        cardDetails.setExpiryDate(txn.getCardExpiry());
        cardDetails.setEffectiveDate(txn.getCardStart());

        paymentRequest.setCardDetails(cardDetails);

        paymentRequest.setAmount(txn.getAmount());
        paymentRequest.setAmountOther(txn.getAmountOther());
        paymentRequest.setCurrencyCode(txn.getCurrencyCode());
        paymentRequest.setType(getPaymentType(txn.getType()));

        if (txn.getCardInputType() == TransactionConstants.INPUT_METHOD.ICC) {
            ICCRequestData iccRequestData = new ICCRequestData();
            iccRequestData.setApplicationId(txn.getIcc_app());
            iccRequestData.setApplicationInterchangeProfile(txn.getIcc_aip());
            iccRequestData.setApplTxnCounter(txn.getIcc_atc());
            iccRequestData.setAuthRequestCryptogram(txn.getIcc_arqc());
            iccRequestData.setIssuerApplData(txn.getIcc_iad());
            iccRequestData.setTermVerificationResult(txn.getIcc_tvr());
            iccRequestData.setUNumber(txn.getIcc_unumber());
            paymentRequest.setIccRequestData(iccRequestData);
        }

        // get a payment engine instance
        PaymentEngine paymentEngine = getPaymentEngineFactory()
                .getPaymentEngine();

        PaymentResponse authresp = null;

        try {

            long acStart = System.currentTimeMillis();
            // say that we started pending acquirer
            txn.setAcqrStarted(new Timestamp(OegwDateUtils.getCurrentTimeGMT().getTime()));

            authresp = paymentEngine.makePayment(paymentRequest);

            // calculate duration
            txn.setAcqrDuration(System.currentTimeMillis() - acStart);

            // check the authorisation code
            String authCode = authresp.getAuthorisationCode();
            if (authCode != null) {
                // if it is present, the txn is approved
                txn.setState(TransactionConstants.STATE.APPROVED);
                txn.setAuthorisationCode(authresp.getAuthorisationCode());
            } else {
                // no auth code - declined
                txn.setState(TransactionConstants.STATE.DECLINED);
            }

            // set the message from acquirer
            txn.setMessageFromAcquirer(authresp.getMessage());
            // and ICC data
            if (txn.getCardInputType() == TransactionConstants.INPUT_METHOD.ICC) {
                ICCResponseData iccResponseData = authresp.getIccResponseData();
                if (iccResponseData != null) {
                    txn.setIcc_arpc(iccResponseData.getAuthResponseCryptogram());
                    txn.setIssuer_auth(iccResponseData
                            .getIssuerAuthenticationData());
                    txn.setIssuer_script(iccResponseData.getIssuerScript());
                }
            }

        } catch (PaymentException e) {
            txn.setState(TransactionConstants.STATE.FAILED);
        }
    }

    /**
     * Gets paym,ent type bean
     *
     * @param type type as int
     * @return payment type as bean
     * @throws IncorrectValueException in case of incorrect value passed
     */
    public static PaymentType getPaymentType(int type)
            throws IncorrectValueException {
        PaymentType paymentType;
        switch (type) {
            case 1:
                paymentType = PaymentType.SALE;
                break;
            case 2:
                paymentType = PaymentType.SALE_WITH_CASHBACK;
                break;
            case 3:
                paymentType = PaymentType.REFUND;
                break;
            case 4:
                paymentType = PaymentType.REVERSAL;
                break;
            default:
                throw new IncorrectValueException("Incorrect payment type: '"
                        + type + "'.");
        }
        return paymentType;
    }

    /**
     * Gets card input type as bean
     *
     * @param mode card input mode
     * @return card input type as bean
     * @throws IncorrectValueException in case of incorrect value passed
     */
    public static CardInputType getCardInputType(int mode)
            throws IncorrectValueException {

        CardInputType inputType;
        switch (mode) {
            case 1:
                inputType = CardInputType.MAGNETIC;
                break;
            case 2:
                inputType = CardInputType.ICC;
                break;
            case 3:
                inputType = CardInputType.KEYED;
                break;
            default:
                throw new IncorrectValueException("Incorrect card input mode '"
                        + mode + "'.");
        }
        return inputType;
    }

    /**
     * Reverse transaction
     *
     * @param txn payment transaction
     */
    public void reverseTransaction(PaymentTransaction txn) throws IncorrectValueException {
        // just set state to REVERSED
        // FIXME
        authoriseTransaction(txn);
        txn.setState(TransactionConstants.STATE.REVERSED);
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