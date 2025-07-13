package com.ingenico.tml.example.toolkit;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.ingenico.util.logging.Logger;

/**
 * This class represents servlet that posts tml reply
 * @author Eugene Pestov
 */
public abstract class TmlPostServlet extends HttpServlet {

    /**
     * logger
     */
    private static final Logger LOG = Logger.getLogger(TmlPostServlet.class
            .getName());

    /**
     * content type
     */
    public static final String TML_CONTENT_TYPE = "text/tml";

    /**
     * tml post data class
     */
    private Class tmlPostDataClass;

    /**
     * Do post
     * @param request HTTP request
     * @param response HTTP response
     * @throws ServletException in case of any errors occur
     * @throws IOException in case of I/O exception occurs
     */
    protected void doPost(HttpServletRequest request,
            HttpServletResponse response) throws ServletException, IOException {
        // set the contextPath attribute
        request.setAttribute("contextPath", request.getContextPath());

        String contentType = request.getContentType();

        // check content type
        // we handle only 'text/tml'
        if (TML_CONTENT_TYPE.equals(contentType)) {

            int contentLength = request.getContentLength();
            // get the request body input stream
            InputStream in = request.getInputStream();

            // read tmlpost data
            byte tmlPostData[] = new byte[contentLength];
            int read = in.read(tmlPostData);
            if (read != contentLength) {
                LOG.warning("Content-Length = " + contentLength + ", read - "
                        + read);
            }
            // get specialized data object
            TmlPostData dataObj = getTmlPostDataInstance();
            // create parser
            TmlPostParser parser = new TmlPostParser();
            try {
                // parse tmlpost
                parser.parse(new ByteArrayInputStream(tmlPostData), dataObj);
                // validate received data
                dataObj.validate();

                // handle the tmlpost request
                doTmlPost(request, response, dataObj);

            } catch (ValidationException e) {
                LOG.severe("Invalid tmlpost request: " + e.getMessage() + "\n"
                        + new String(tmlPostData));
                error(request, response, dataObj, e);
            } catch (TmlParseException e) {
                LOG.severe("Could not parse tmlpost request:" + e.getMessage()
                        + "\n" + new String(tmlPostData));
                error(request, response, dataObj, e);
            } catch (Throwable e) {
                LOG.severe("Fatal error:" + e.getMessage()
                        + "\n" + new String(tmlPostData));
                throw new ServletException("Fatal error: " + e.getMessage());                
            }

        } else {
            throw new ServletException("Wrong content type: " + contentType);
        }
    }

    /**
     * Do tml post
     * @param request HTTP request
     * @param response HTTP response
     * @param dataObj tml post data
     * @throws ServletException in case of any exceptions occur
     * @throws IOException in case of I/O exception occurs
     */
    protected abstract void doTmlPost(HttpServletRequest request,
            HttpServletResponse response, TmlPostData dataObj)
            throws ServletException, IOException;

    /**
     * Wraps error
     * @param request HTTP request
     * @param response HTTP response
     * @param dataObj tml post data
     * @param e exception
     * @throws ServletException new ServletException
     */
    protected void error(HttpServletRequest request,
            HttpServletResponse response, TmlPostData dataObj, Exception e)
            throws ServletException, IOException {
        LOG.throwing("", "", e);
        throw new ServletException(e.getMessage());
    }

    /**
     * Gets instance of tml post data class
     * @return instance of tml post data class
     * @throws ServletException in case of any errors occur
     */
    protected TmlPostData getTmlPostDataInstance() throws ServletException {
        if (tmlPostDataClass == null) {
            String tmlPostDataClassName = getServletConfig().getInitParameter(
                    "tmlPostDataClass");
            if (tmlPostDataClassName == null) {
                throw new ServletException(
                        "Init paramener 'tmlPostDataClass' is not set");
            }

            try {
                tmlPostDataClass = Class.forName(tmlPostDataClassName);
            } catch (ClassNotFoundException e) {
                throw new ServletException("Not found " + tmlPostDataClassName,
                        e);
            }
        }

        try {
            TmlPostData data = (TmlPostData) tmlPostDataClass.newInstance();
            return data;
        } catch (InstantiationException e) {
            throw new ServletException(e);
        } catch (IllegalAccessException e) {
            throw new ServletException(e);
        }
    }

    /**
     * This method converts string to pounds
     *
     * @param str string to convert
     * @return string in pounds
     */
    public static String toPounds(String str) {
        String s = str.trim();
        if (s != null && !s.equals("")) {
            switch (s.length()) {
                case 1:
                    s = "0.0" + s;
                    break;
                case 2:
                    s = "0." + s;
                    break;
                default:
                    s = s.substring(0, s.length() - 2) + "." + s.substring(s.length() - 2, s.length());
                    break;
            }
        }
        return s;
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