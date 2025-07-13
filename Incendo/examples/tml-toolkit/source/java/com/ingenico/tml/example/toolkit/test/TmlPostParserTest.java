package com.ingenico.tml.example.toolkit.test;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

import junit.framework.TestCase;

import org.apache.commons.codec.binary.Base64;

import com.ingenico.tml.example.toolkit.TmlParseException;
import com.ingenico.tml.example.toolkit.TmlPostData;
import com.ingenico.tml.example.toolkit.TmlPostParser;

/**
 * JUnit test class
 * @author Eugene Pestov
 */
public class TmlPostParserTest extends TestCase {

    /**
     * opaque
     */
    private static byte OPAQUE[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };

    /**
     * base64 encoder
     */
    private static String BASE64 = new String(Base64.encodeBase64(OPAQUE));

    /**
     * tml post
     */
    private static String TMLPOST =
    "<tmlpost xmlns=\"http://www.ingenico.com/tml\"" +
    " itid=\"1234:5678\" date=\"1093042545\" post_id=\"1\">\n" +
    "  <postvar name=\"intVar\" type=\"integer\" value=\"123\"/>\n" +
    "  <postvar name=\"strVar\" type=\"string\" value=\"123\"/>\n" +
    "  <postvar name=\"opVar\" type=\"opaque\" value=\"" + BASE64 + "\"/>\n" +
    "  <postvar name=\"dateVar\" type=\"date\" value=\"1093042545\"/>\n" +
    "</tmlpost>";

    /**
     * Simple TML post data
     */
    public static class SimpleTmpPostData extends TmlPostData {

        /**
         * Sets int variable
         * @param i int
         */
        public void setIntVar(int i) {
            System.out.println("setIntVar(" + i + ")");
        }

        /**
         * Sets string variable
         * @param s string
         */
        public void setStrVar(String s) {
            System.out.println("setStrVar(" + s + ")");
        }

        /**
         * Sets opaque variable
         * @param bs opaque
         */
        public void setOpVar(byte bs[]) {
            System.out.println("setOpVar(" + bs.toString() + ")");
        }

        /**
         * Sets date variable
         * @param d
         */
        public void setDateVar(Date d) {
            System.out.println("setDateVar(" + d.toGMTString() + ")");
        }

        /**
         * Gets field mappings
         * @return field mappings
         */
        public Map<String, String> getFieldMappings() {
            HashMap<String, String> map = new HashMap<String, String>();
            map.put("intVar", "intVar");
            map.put("strVar", "strVar");
            map.put("opVar", "opVar");
            map.put("dateVar", "dateVar");
            return map;
        }
    }
    
    /**
     * Constructor for TmlPostParserTest.
     * @param arg0 ÙÍÔ„¸ÛÚÂ
     */
    public TmlPostParserTest(String arg0) {
        super(arg0);
    }

    /**
     * Main
     * @param args arguments
     */
    public static void main(String[] args) {
        junit.textui.TestRunner.run(TmlPostParserTest.class);
    }

    /**
     * Parses tml post
     * @throws TmlParseException in case of error during tml parsing
     * @throws IOException in case of any I/O error occurs
     */
    public void testParse() throws TmlParseException, IOException {
        System.out.println(TMLPOST);
        TmlPostParser parser = new TmlPostParser();
        TmlPostData data = new SimpleTmpPostData();
        parser.parse(new ByteArrayInputStream(TMLPOST.getBytes()), data);
    }
}
/*
 * Incendo Online TML Toolkit
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