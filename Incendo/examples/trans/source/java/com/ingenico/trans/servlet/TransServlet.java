package com.ingenico.trans.servlet;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.Enumeration;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;

import com.ingenico.trans.TransactionParser;
import com.ingenico.trans.TransactionSerializer;
import com.ingenico.trans.data.Field;
import com.ingenico.trans.data.Message;
import com.ingenico.trans.data.MessageRequest;
import com.ingenico.trans.data.MessageResponse;
import com.ingenico.trans.data.Transaction;

public class TransServlet extends HttpServlet {
    private static final String RESPONSE_TYPE_INIT_PARAM = "content-type";
    private static final String TEST_SAVE_REQUEST_INIT_PARAM = "save-request";
    private static final String AUTH_CODE_INIT_PARAM = "authcode";
    private static final String ACTION_CODE_INIT_PARAM = "actioncode";
    Logger logger = Logger.getLogger(TransServlet.class);

    /**
     * Implements authorisation functionality for clients using GET method to
     * call servlet
     * 
     * @param req
     *            request object
     * @param resp
     *            response object
     */
    public void doGet(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        // logger.info("Request reveived");
        doPost(req, resp);
    }

    /**
     * Initializes the servlet.
     * 
     * @param config
     *            Instance of ServletConfig.
     * @throws ServletException
     *             thrown if there is an error in intialization.
     */
    public void init(ServletConfig config) throws ServletException {
        super.init(config);
    }

    String readResource(String name) throws IOException {
        InputStream f = TransServlet.class.getClassLoader()
                .getResourceAsStream(name);

        BufferedReader br = new BufferedReader(new InputStreamReader(f));

        String string;
        String result = br.readLine();
        while ((string = br.readLine()) != null) {
            result += string;
            logger.info(string);
        }
        return result;
    }

    /**
     * Implements authorisation functionality for clients using POST method to
     * call servlet
     * 
     * @param req
     *            request object
     * @param resp
     *            response object
     */
    public void doPost(HttpServletRequest req, HttpServletResponse resp)
            throws ServletException, IOException {
        try {
            Object tRequest = readRequest(req);

            if (tRequest instanceof Message) {
                MessageRequest request = ((Message) tRequest)
                        .getMessageRequest();
                Message tResponse = new Message();

                MessageResponse mResponse = new MessageResponse();
                tResponse.setMessageResponse(mResponse);
                tResponse.setTransactionId(((Message) tRequest)
                        .getTransactionId());
                if (request != null) {
                    mResponse.addField(new Field("transaction.message.id", request
                            .getField("transaction.message.id")));
                    mResponse.addField(new Field("transaction.message.type", request.getField("transaction.message.type")));
                    mResponse.addField(new Field("transaction.message.resend",
                            request.getField("transaction.message.resend")));
                    mResponse.addField(new Field("transaction.message.date",
                            request.getField("transaction.message.date")));
                    mResponse.addField(new Field("transaction.message.transaction-date",
                                    request.getField("transaction.message.transaction-date")));
                    mResponse.addField(new Field("transaction.message.transaction-type",
                            request.getField("transaction.message.transaction-type")));
                }
                try {
                    double amount = Double.parseDouble(request.getField("transaction.message.transaction-amount"));
                    
                    if (amount < 10000)
                      mResponse.addField(new Field("transaction.message.authcode", getServletContext().getInitParameter(AUTH_CODE_INIT_PARAM)));
                    else {
                        mResponse.addField(new Field("transaction.message.authcode", "ERROR"));
                        mResponse.addField(new Field("transaction.message.errormessage", "Transaction amount limit exceeded"));
                    }
                }
                catch (NumberFormatException e) {
                    mResponse.addField(new Field("transaction.message.authcode", getServletContext().getInitParameter(AUTH_CODE_INIT_PARAM)));
                }
                mResponse.addField(new Field("transaction.message.actioncode",
                        getServletContext().getInitParameter(
                                ACTION_CODE_INIT_PARAM)));

                writeResponse(resp, tResponse);
            }

        } catch (Throwable e) {
            try {
                ByteArrayOutputStream baos = new ByteArrayOutputStream();
                e.printStackTrace();
                e.printStackTrace(new PrintStream(baos));
                OutputStream os = resp.getOutputStream();
                os.write(baos.toByteArray());
                os.flush();
                os.close();
            } catch (Exception ex) {
                // we do nothing
            }
        }
    }

    private void writeResponse(HttpServletResponse resp, Message tResponse)
            throws IOException {
        String contentType = getServletContext().getInitParameter(
                RESPONSE_TYPE_INIT_PARAM);
        resp.setContentType(contentType);
        logger.info("Content-type header set to: " + contentType);

        OutputStream os = resp.getOutputStream();
        logger.info("Response:");
        String res = TransactionSerializer.serialize(tResponse);

        logger.info(res);
        os.write(res.getBytes());
        os.flush();
        os.close();
    }

    private Message readRequest(HttpServletRequest req) throws IOException,
            SAXException {
        Message result = null;
        String doSaveRequest = this.getServletContext().getInitParameter(
                TEST_SAVE_REQUEST_INIT_PARAM).trim();
        if (!(doSaveRequest == null || doSaveRequest.equalsIgnoreCase("none") || doSaveRequest.equalsIgnoreCase("log") || doSaveRequest
                .equalsIgnoreCase(""))) {
            Enumeration headers = req.getHeaderNames();
            InputStream is = req.getInputStream();

            int b;
            PrintStream os = null;
            if (doSaveRequest.equalsIgnoreCase("screen")) // print on screen
                os = System.out;
            else if (doSaveRequest.equalsIgnoreCase("file")){ // print in file
                File f = new File(doSaveRequest);
                os = new PrintStream(new FileOutputStream(f, true));
            }

            while (headers.hasMoreElements()) {
                String s = (String) headers.nextElement();
                if (os != null)
                    os.println(s + "=" + req.getHeader(s));
                else
                    logger.info(s + "=" + req.getHeader(s));
            }
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            while ((b = is.read()) != -1) {
                baos.write(b);
                if (os != null)
                    os.write(b);
            }

            if (os == null)
                logger.info(baos.toString());
            
            ByteArrayInputStream bais = new ByteArrayInputStream(baos
                    .toByteArray());
            result = (Message) new TransactionParser().parse(
                    new InputSource(bais));

            bais.close();
            baos.close();
            if (!doSaveRequest.equalsIgnoreCase("screen") && os != null)
                os.close();
        }
        if (result == null)
            throw new IllegalArgumentException("Failed to parse transaction");
        
        return result;
    }

    public static void main(String[] args) throws Exception {
        InputSource is = new InputSource(new FileInputStream(args[0]));
        TransactionParser p = new TransactionParser();
        Transaction data = p.parse(is);
        if (data != null) {
            String s = TransactionSerializer.serialize(data);
            s = TransactionSerializer.serialize(data);
            s = TransactionSerializer.serialize(data);
            System.out.println(s);
            p.parse(new InputSource(new ByteArrayInputStream(s.getBytes())));
        } else
            System.out
                    .println("Can't perform serialization, input data is null");
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