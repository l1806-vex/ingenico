package com.ingenico.trans;

import java.io.IOException;
import java.net.URL;

import org.apache.commons.digester.Digester;
import org.xml.sax.ErrorHandler;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException;

import com.ingenico.trans.data.Field;
import com.ingenico.trans.data.Message;
import com.ingenico.trans.data.MessageRequest;
import com.ingenico.trans.data.MessageResponse;
import com.ingenico.trans.data.Reconciliation;
import com.ingenico.trans.data.Row;
import com.ingenico.trans.data.Transaction;
import com.ingenico.trans.data.Txn;
import com.ingenico.trans.data.TxnUpload;

/**
 * Transaction parser
 * 
 * @author Sergey Lukashin
 */
public class TransactionParser {

    public static final String FIELD_CLASS = Field.class.getName();
    public static final String TRANS_CLASS = Message.class.getName();
    public static final String MESSAGE_REQUEST_CLASS = MessageRequest.class
            .getName();
    private static final String MESSAGE_RESPONSE_CLASS = MessageResponse.class
            .getName();
    public static final String RECONS_REQUEST_CLASS = Reconciliation.class
            .getName();
    private static final String TXN_UPLOAD_CLASS = TxnUpload.class.getName();
    private static final String TXN_CLASS = Txn.class.getName();
    private static final String ROW_CLASS = Row.class.getName();

    /**
     * Have we been configured yet?
     */
    protected boolean configured = false;

    /**
     * digester
     */
    private Digester digester;
    private ErrorHandler errorHandler;

    public TransactionParser() {
        this.errorHandler = new ErrorHandler() {
            public void warning(SAXParseException exception)
            throws SAXException {
        exception.printStackTrace();
    }

    public void error(SAXParseException exception)
            throws SAXException {
        exception.printStackTrace();
    }

    public void fatalError(SAXParseException exception)
            throws SAXException {
        exception.printStackTrace();
    }
  };
}
    /**
     * Configure the parsing rules that will be used.
     */
    protected void configure() {

        if (configured) {
            return;
        }

        digester = new Digester();
        digester.setClassLoader(this.getClass().getClassLoader());
        if (getRegistrations().length >= 2) {
            digester.setNamespaceAware(true);
            digester.setValidating(true);
            digester.setErrorHandler(errorHandler);
            try {
                digester.setFeature(
                        "http://apache.org/xml/features/validation/schema",
                        true);
            } catch (Exception e) {
                throw new RuntimeException(e);
            }

        }

        String[] registrations = getRegistrations();
        // Register local copies of the DTDs we understand
        for (int i = 0; i < registrations.length; i += 2) {
            String scheme;
            ClassLoader loader = this.getClass().getClassLoader();
            
            URL url = loader.getResource(registrations[i + 1]);
            if (url != null) {
                digester.register(registrations[i], url.toString());
                scheme = url.getPath();
                if (scheme.contains("jar!"))
                    scheme = "jar:" + scheme;

                try {
                    digester
                            .setProperty(
                                    "http://java.sun.com/xml/jaxp/properties/schemaLanguage",
                                    "http://www.w3.org/2001/XMLSchema");
                    digester
                            .setProperty(
                                    "http://java.sun.com/xml/jaxp/properties/schemaSource",
                                    scheme);
                } catch (SAXException e) {
                    throw new RuntimeException(e);
                }
            }
        }

        // Add the rules for the Transaction object
        setDigestRules();

        // Mark this digester as having been configured
        configured = true;
    }

    protected String[] getRegistrations() {
        return new String[] { "-// trans xsd", "trans.xsd" };
    }

    protected void setDigestRules() {
        digester.addObjectCreate("transaction", TRANS_CLASS);
        digester.addBeanPropertySetter("transaction/transaction-id",
                "transactionId");

        digester.addObjectCreate("transaction/message-request",
                MESSAGE_REQUEST_CLASS);
        digester.addSetProperties("transaction/message-request");
        digester.addSetNext("transaction/message-request", "setMessageRequest");

        digester.addObjectCreate("transaction/message-request/field",
                FIELD_CLASS);
        digester.addSetProperties("transaction/message-request/field");
        digester.addSetNext("transaction/message-request/field", "addField");

        digester.addObjectCreate("transaction/message-response",
                MESSAGE_RESPONSE_CLASS);
        digester.addSetProperties("transaction/message-response");
        digester.addSetNext("transaction/message-response",
                "setMessageResponse");

        digester.addObjectCreate("transaction/message-response/field",
                FIELD_CLASS);
        digester.addSetProperties("transaction/message-response/field");
        digester.addSetNext("transaction/message-response/field", "addField");

        digester.addObjectCreate("reconciliation", RECONS_REQUEST_CLASS);
        digester.addSetProperties("reconciliation");

        digester.addObjectCreate("reconciliation/row", ROW_CLASS);
        digester.addSetProperties("reconciliation/row", "transaction-type",
                "transactionType");
        digester.addSetProperties("reconciliation/row");
        digester.addSetNext("reconciliation/row", "addRow");

        digester.addObjectCreate("txnupload", TXN_UPLOAD_CLASS);
        digester.addSetProperties("txnupload");

        digester.addObjectCreate("txnupload/txn", TXN_CLASS);
        digester.addSetProperties("txnupload/txn");
        digester.addSetNext("txnupload/txn", "addTxn");
    }

    /**
     * Parse the content of the specified input source using this Digester.
     * Returns the root element from the object stack.
     * 
     * @param input
     *            Input source containing the XML data to be parsed
     */
    public synchronized Transaction parse(InputSource input)
            throws IOException, SAXException {

        if (!configured)
            configure();
        return (Transaction) digester.parse(input);

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