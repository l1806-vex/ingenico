package com.ingenico.btmlpa.servlet;

import java.io.IOException;
import java.io.InputStream;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.ingenico.btmlpa.Application;
import com.ingenico.btmlpa.BTMLPAException;
import com.ingenico.btmlpa.Constants;
import com.ingenico.btmlpa.Terminal;
import com.ingenico.tml.example.toolkit.TmlPostData;
import com.ingenico.tml.example.toolkit.TmlPostServlet;
import com.ingenico.util.configuration.Configuration;
import com.ingenico.util.configuration.PropertiesConfiguration;
import com.ingenico.util.exception.SystemException;
import com.ingenico.util.logging.Logger;

/**
 * This is base servlet that process requests and forms replies
 * for Basic TML Payment Application
 * This servlet is overwritten in set of classes
 *
 * @author Eugene Pestov
 */
public abstract class BaseServlet extends TmlPostServlet {

    private static Logger LOG = Logger
            .getLogger(BaseServlet.class.getName());

    /**
     * Initializes the servlet.
     *
     * @param config Instance of ServletConfig.
     * @throws ServletException thrown if there is an error in intialization.
     */
    public void init(ServletConfig config) throws ServletException {

        super.init(config);

        if (!Application.getInstance().isInitialized()) {
            try {
                // do init

                String configFile = getServletContext().getInitParameter("configuration-file");
                if (configFile == null) {
                    configFile = "btmlpa.properties";
                }

                InputStream configFileIn = BaseServlet.class.getClassLoader().getResourceAsStream(configFile);

                if (configFileIn == null)
                    throw new ServletException("btmlpa.properties not found");
                
                Configuration configuration = new PropertiesConfiguration(configFileIn);

                Application.getInstance().initialize(configuration);

            } catch (IOException se) {
                throw new ServletException(se);
            }
        }
    }

    /**
     * Do tml post
     *
     * @param request     HTTP request
     * @param response    HTTP response
     * @param tmlPostData data to post
     * @throws ServletException in case of servlet error occcurs
     * @throws IOException      in case of I/O error occurs
     */
    protected void doTmlPost(HttpServletRequest request,
                             HttpServletResponse response, TmlPostData tmlPostData)
            throws ServletException, IOException {

        String screen = null;

        Terminal terminal = null;

        boolean offline = false;

        try {

            offline = getSubmitMode(tmlPostData);

            // look up the requesting terminal
            terminal = Application.getInstance().findTerminal(tmlPostData.getItid());

            if (terminal == null) {
                LOG.severe("Transaction processing failed: Unknown ITID: '" + tmlPostData.getItid() + "'. Error " +
                        "response will be sent to the client.");
                if (!offline) {
                    request.setAttribute("errorMessage",
                            "Transaction processing failed. \nUnknown ITID: "
                            + tmlPostData.getItid()
                            + ". \nPlease, call the helpdesk.");

                    request.setAttribute("nextScreen", "trans_abrt");

                    String resource = getResourceName(request, "error.dtml");

                    getServletContext().getRequestDispatcher(resource).forward(request, response);
                }
                else {
                    response.sendError(HttpServletResponse.SC_BAD_REQUEST,
                            "Transaction processing failed. Unknown ITID: '" +
                            tmlPostData.getItid() + "'. Please, call the helpdesk.");
                }

                return;
            }
        }
        catch (SystemException e) {

            LOG.severe("Transaction processing failed. Error response will be sent to the client.");
            if (!offline) {
                request.setAttribute("errorMessage",
                        "Transaction processing failed.\nPlease, call the helpdesk.");

                request.setAttribute("nextScreen", "trans_abrt");

                String resource = getResourceName(request, "error.dtml");

                getServletContext().getRequestDispatcher(resource).forward(request, response);
            }
            else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND,
                        "Transaction processing failed. Please, call the helpdesk.");
            }

            return;
        }

        try {
            screen = processBTMLPARequest(terminal, request, response,
                    tmlPostData);
        } catch (Exception e) {
            LOG.severe("Transaction processing failed:\n'" + e.getMessage() + "'. Error " +
                    "response will be sent to the client.");
            if (!offline) {
                request.setAttribute("errorMessage",
                        "Transaction processing failed.\n" + e.getMessage()
                        + "\nPlease, call the helpdesk.");
                request.setAttribute("nextScreen", "trans_abrt");

                screen = getResourceName(request, "error.dtml");
            }
            else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND,
                        "Transaction processing failed. Please, call the helpdesk.");
            }
        }

        if (screen != null && !offline) {
            getServletContext().getRequestDispatcher(screen).forward(request,
                    response);
        }
    }

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

        LOG.severe("Transaction processing failed:\n'" + e.getMessage() + "'. Error " +
            "response will be sent to the client.");
        request.setAttribute("errorMessage",
                "Transaction processing failed. \nPlease, call the helpdesk.");
        request.setAttribute("nextScreen", "trans_abrt");

        String screen = getResourceName(request, "error.dtml");
        getServletContext().getRequestDispatcher(screen).forward(request, response);

    }

    /**
     * This method translates resource name to resource name special for
     * requestor type
     * @param req http request
     * @param resource resource name
     * @return new resource name special for requestor type
     */
    public String getResourceName(HttpServletRequest req, String resource) {
        String userAgent = req.getHeader("User-Agent");
        String term = "other";

        if ((userAgent != null) && (userAgent.length() >= 4)) {
            term = userAgent.substring(userAgent.length() - 4, userAgent.length());
        }
        String resourceValue = "";
        
        String defaultRedirectValue = Application.getInstance().getConfiguration().getString(Constants.TERMINAL_OTHER, "/5100");                
        
        String mapping = Application.getInstance().getConfiguration().getString(Constants.TERMINAL_TYPE + term, defaultRedirectValue);
                
        resourceValue = mapping + "/" + resource;        
                        
        return resourceValue;
    }

    /**
     * Process btmlpa request
     *
     * @param terminal    terminal
     * @param request     HTTP request
     * @param response    HTTP response
     * @param tmlPostData tml post data
     * @return dtml page that represents container for tml reply
     * @throws BTMLPAException in case of any errors occur
     */
    protected abstract String processBTMLPARequest(Terminal terminal,
                                                   HttpServletRequest request, HttpServletResponse response,
                                                   TmlPostData tmlPostData) throws BTMLPAException;

    /**
     * This method gets submit mode
     * @param tmlPostData tml post data
     * @return true if online false otherwise
     */
    protected abstract boolean getSubmitMode(TmlPostData tmlPostData);

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