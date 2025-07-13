package com.ingenico.tml.example.magcard.test;

import java.io.IOException;
import java.util.Date;

import com.ingenico.tml.example.toolkit.TmlPostServlet;
import com.ingenico.util.http.HTTPRequest;
import com.ingenico.util.http.HTTPResponse;
import com.ingenico.util.http.HTTPUtils;
import com.ingenico.util.logging.Logger;

/**
 * This class tests mag card application
 * @author Eugene Pestov
 */
public class MagCardAppTest {

    /**
     * logger
     */
    private static final Logger LOG =
        Logger.getLogger(MagCardAppTest.class.getName());

    /**
     * Main
     * @param args arguments
     * @throws IOException in case of any errors occur
     */
    public static void main(String[] args) throws IOException {

        if (args.length < 1) {
            System.exit(10);
        }

        int amount = Integer.parseInt(args[0]);

        HTTPRequest request = new HTTPRequest();
        request.setMethod(HTTPRequest.HTTP_POST);
        request.setURI("http://localhost:8090/magcard/authtxn");
        request.setHeader("Content-Type", TmlPostServlet.TML_CONTENT_TYPE);
        request.setContentBytes(getTmlPost(amount).getBytes());

        LOG.info("Sending request:\n" + request.toString());

        HTTPResponse response = HTTPUtils.sendRequest(request);

        LOG.info("Got response:\n" + response.toString());
    }

    /**
     * Creates tml post
     * @param amount transaction amount
     * @return tml post
     */
    private static String getTmlPost(int amount) {
        String tmlPost =
            "<tmlpost xmlns=\"http://www.ingenico.com/tml\""
            + " itid=\"1234:5678\" post_id=\"1\" date=\""
            + new Date().getTime() / 1000 // current time
            +"\">\n"
            + "  <postvar name=\"card.parser.type\" type=\"string\" value=\"mag\"/>\n"
            + "  <postvar name=\"card.cardholder_name\" type=\"string\" value=\"Eugene Pestov\"/>\n"
            + "  <postvar name=\"card.pan\" type=\"string\" value=\"4040123456784321\"/>\n"
            + "  <postvar name=\"card.issuer_name\" type=\"string\" value=\"Guta Bank\"/>\n"
            + "  <postvar name=\"card.issue_number\" type=\"integer\" value=\"10\"/>\n"
            + "  <postvar name=\"card.scheme\" type=\"string\" value=\"VISA\"/>\n"
            + "  <postvar name=\"card.effective_date\" type=\"date\" value=\""
            + new Date(103, 2, 1).getTime() / 1000 // 01.03.2003
            + "\"/>\n"
            + "  <postvar name=\"card.expiry_date\" type=\"date\" value=\""
            + new Date(105, 4, 31).getTime() / 1000 // 31.05.2005
            + "\"/>\n"
            + "  <postvar name=\"card.mag.iso2_track\" type=\"string\" value=\"5678\"/>\n"
            + "  <postvar name=\"transid\" type=\"integer\" value=\"123\"/>\n"
            + "  <postvar name=\"payment.amount\" type=\"integer\" value=\""
            + amount
            + "\"/>\n"
            + "</tmlpost>";
            
        return tmlPost;
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