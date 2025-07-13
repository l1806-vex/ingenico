package com.ingenico.trans;

import java.io.IOException;
import java.io.StringWriter;

import com.ingenico.trans.data.Field;
import com.ingenico.trans.data.Message;
import com.ingenico.trans.data.Reconciliation;
import com.ingenico.trans.data.Row;
import com.ingenico.trans.data.Transaction;
import com.ingenico.trans.data.Txn;
import com.ingenico.trans.data.TxnUpload;

/**
 * Serialization of all types of transactions
 * 
 * @author Sergey Lukashin
 */
public class TransactionSerializer {
    public static String serialize(Transaction data) throws IOException {
        if (data instanceof Message) {
            Message tr = (Message) data;
            StringWriter wr = new StringWriter();
            wr.write("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n");
            wr.write("<transaction xmlns=\"http://www.ingenico.com/terminal-config\">\n");
            wr.write("<transaction-id>" + tr.getTransactionId()
                    + "</transaction-id>\n");
            if (tr.getMessageRequest() != null) {
                wr.write("<message-request>\n");
                for (Field field : tr.getMessageRequest().getFields())
                    wr.write("<field name=\"" + field.getName() + "\" value=\""
                            + field.getValue() + "\"/>\n");
                wr.write("</message-request>\n");
            } else {
                wr.write("<message-response>\n");
                for (Field field : tr.getMessageResponse().getFields())
                    wr.write("<field name=\"" + field.getName() + "\" value=\""
                            + field.getValue() + "\"/>\n");
                wr.write("</message-response>\n");
            }

            wr.write("</transaction>");
            return wr.toString();
        } else if (data instanceof Reconciliation) {
            Reconciliation tr = (Reconciliation) data;
            StringWriter wr = new StringWriter();
            wr.write("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n");
            if (tr.getStatus() != null) { // i.e. response
                wr
                        .write("<reconciliation xmlns=\"http://www.ingenico.com/terminal-config\" startid=\""
                                + tr.getStartId()
                                + "\" endid=\""
                                + tr.getEndId()
                                + "\" status=\""
                                + tr.getStatus() + "\">");
                wr.write("</reconciliation>");
            } else {
                wr
                        .write("<reconciliation xmlns=\"http://www.ingenico.com/terminal-config\" startid=\""
                                + tr.getStartId()
                                + "\" endid=\""
                                + tr.getEndId()
                                + "\" txncount=\""
                                + tr.getTxnCount()
                                + "\" rows=\""
                                + tr.getRows().size() + "\">");
                for (Row r : tr.getRows())
                    wr.write("<row id=\"" + r.getId()
                            + "\" transaction-type=\"" + r.getTransactionType()
                            + "\" currency=\"" + r.getCurrency()
                            + "\" amount=\"" + r.getAmount() + "\" number=\""
                            + r.getNumber() + "\"/>\n");

                wr.write("</reconciliation>");
            }
            return wr.toString();
        } else if (data instanceof TxnUpload) {
            TxnUpload tr = (TxnUpload) data;
            StringWriter wr = new StringWriter();
            wr.write("<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n");
            wr
                    .write("<txnupload xmlns=\"http://www.ingenico.com/terminal-config\">");
            for (Txn r : tr.getTxns())
                wr.write("<txn id=\"" + r.getId() + "\" date=\"" + r.getDate()
                        + "\" type=\"" + r.getType() + "\" amount=\""
                        + r.getAmount() + "\" amount2=\"" + r.getAmount2()
                        + "\" currency=\"" + r.getCurrency() + "\" authcode=\""
                        + r.getAuthcode() + "\" errorcode=\""
                        + r.getErrorcode() + "\" errormessage=\""
                        + r.getErrormessage() + "\"/>");
            wr.write("</txnupload>");
            return wr.toString();
        } else
            throw new IllegalArgumentException("Unsupported class");
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