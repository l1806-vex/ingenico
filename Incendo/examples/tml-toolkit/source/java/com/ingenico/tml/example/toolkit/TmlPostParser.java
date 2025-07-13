package com.ingenico.tml.example.toolkit;

import java.io.IOException;
import java.io.InputStream;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParserFactory;

import org.xml.sax.Attributes;
import org.xml.sax.InputSource;
import org.xml.sax.SAXException;
import org.xml.sax.XMLReader;
import org.xml.sax.helpers.DefaultHandler;

import com.ingenico.util.exception.UnexpectedException;
import com.ingenico.util.logging.Logger;

/**
 * This class represents TML post parser
 * @author Eugene Pestov
 */
public class TmlPostParser extends DefaultHandler {

    /**
     * elements handlers
     */
    private static HashMap elementHandlersMap = new HashMap();

    /**
     * logger
     */
    private static final Logger LOG = Logger.getLogger(TmlPostParser.class
            .getName());

    /**
     * sax parser factory
     */
    private static SAXParserFactory parserFactory = SAXParserFactory
            .newInstance();

    /**
     * tml post namespace
     */
    public static final String TMLPOST_NAMESPACE = "";

    //        "http://www.ingenico.com/tml";

    /**
     * XMLReader instance associated with this parser
     */
    private XMLReader reader;

    /**
     * initialises element handlers
     */
    static {
        // <tmlpost> element handler
        elementHandlersMap.put("tmlpost", new ElementHandler() {
            public void handleStart(TmlPostData dataObj, Attributes attributes)
                    throws SAXException {

                dataObj.setItid(attributes.getValue(TMLPOST_NAMESPACE, "itid"));
                String dateStr = attributes.getValue(TMLPOST_NAMESPACE, "date");
                try {
                    DateFormat df = new SimpleDateFormat("dd MM yyyy HH:mm:ss zzz");
                    Date date = df.parse(dateStr);
                    dataObj.setDate(date);
                } catch (ParseException e) {
                    LOG.warning("Could not parse value of attribute date:"
                            + dateStr);
                }
                dataObj.setPostId(attributes.getValue(TMLPOST_NAMESPACE,
                        "post_id"));
            }
        });

        // <postvar> element handler
        elementHandlersMap.put("postvar", new ElementHandler() {
            public void handleStart(TmlPostData dataObj, Attributes attributes)
                    throws SAXException {

                String name = attributes.getValue(TMLPOST_NAMESPACE, "name");
                String type = attributes.getValue(TMLPOST_NAMESPACE, "type");
                String value = attributes.getValue(TMLPOST_NAMESPACE, "value");

                try {
                    try {
                        Utils.setProperty(dataObj, name, type, value);
                    } catch (Exception e) {
                        Utils.setProperty(dataObj, name, "string", value);
                      }
                }
                catch (RuntimeException e) {
                    throw e;
                } catch (TmlParseException e) {
                    throw new SAXException(e);
                } catch (Exception e) {
                    // just warn now
                    LOG.severe(e);
                    throw new UnexpectedException(e);
                }
            }
        });
    }

    /**
     * simple interface for element handling
     */
    private interface ElementHandler {

        /**
         * Starts handling
         * @param dataObj tml post data
         * @param attributes attributes
         * @throws SAXException in case of any errors occurs
         */
        void handleStart(TmlPostData dataObj, Attributes attributes)
                throws SAXException;
    }

    /**
     * TML post handler
     */
    private class TmlPostHandler extends DefaultHandler {

        /**
         * tml post data
         */
        private TmlPostData dataObj;

        /**
         * Default constructor
         * @param dataObj tml post data
         */
        public TmlPostHandler(TmlPostData dataObj) {
            this.dataObj = dataObj;
        }

        /**
         * Receive notification of the beginning of the document.
         * @throws SAXException in case of any errors occur
         */
        public void startDocument() throws SAXException {
            // reset
        }

        /**
         * Receive notification of the start of an element.
         * Parses tml element
         * @param uri uri
         * @param localName local name
         * @param qName qname
         * @param attributes attributes
         * @throws SAXException in case of any errors occur
         */
        public void startElement(String uri, String localName, String qName,
                Attributes attributes) throws SAXException {

            ElementHandler elementHandler = (ElementHandler) elementHandlersMap
                    .get(localName);

            if (elementHandler != null) {
                elementHandler.handleStart(dataObj, attributes);
            } else {
                throw new SAXException("Unknown element in tmlpost:"
                        + localName);
            }
        }
    }

    /**
     * Default constructor
     */
    public TmlPostParser() {
        try {
            //initialize XML reader
            reader = parserFactory.newSAXParser().getXMLReader();

            // TODO: include tmlpost validation
            reader.setFeature("http://xml.org/sax/features/validation", false);
            reader.setFeature("http://xml.org/sax/features/namespaces", true);
            reader.setFeature("http://xml.org/sax/features/namespace-prefixes",
                    false);

        } catch (SAXException e) {
            LOG.severe("Error initializing XMLReader", e);
            throw new UnexpectedException("Error initializing XMLReader", e);
        } catch (ParserConfigurationException e) {
            LOG.severe("Error initializing XMLReader", e);
            throw new UnexpectedException("Error initializing XMLReader", e);
        }
    }

    /**
     * This method reads the tmlpost xml document from the input stream and
     * fills properties of the dataObj according to &lt;postvar&gt; elements.
     * 
     * @param in input stream
     * @param dataObj tml post
     * @throws IOException in case of any errors occur
     */
    public void parse(InputStream in, TmlPostData dataObj)
            throws TmlParseException, IOException {

        // set new handler
        TmlPostHandler handler = new TmlPostHandler(dataObj);
        reader.setContentHandler(handler);

        try {
            reader.parse(new InputSource(in));
        } catch (SAXException e) {
            throw new TmlParseException(e.getMessage());
        }
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