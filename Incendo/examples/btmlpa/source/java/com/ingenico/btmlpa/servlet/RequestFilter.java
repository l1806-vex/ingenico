package com.ingenico.btmlpa.servlet;

import java.io.IOException;
import java.io.InputStream;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.ingenico.btmlpa.Constants;
import com.ingenico.util.configuration.Configuration;
import com.ingenico.util.configuration.PropertiesConfiguration;

/**
 * This class represents filter that forward clients to resources
 * according to client type
 *
 * @author Dmitry Ivanov
 */
public class RequestFilter implements Filter {

    /**
     * filter configuration
     */
    protected FilterConfig filterConfig;

    /**
     * application properties
     */
    private Configuration applConfig;

    /**
     * Filter initialisation
     * @param config filter configuration
     * @throws ServletException in case any error occur
     */
    public void init(FilterConfig config) throws ServletException {
        this.filterConfig = config;
    }

    /**
     * Do filtering
     * @param request request
     * @param response response
     * @param chain filter chain
     * @throws IOException I/O exception
     * @throws ServletException in case any other than I/O exception occurs
     */
    public void doFilter(ServletRequest request, ServletResponse response,
                   FilterChain chain) throws IOException, ServletException {

        HttpServletRequest req = (HttpServletRequest)request;
        HttpServletResponse res = (HttpServletResponse)response;

        if (applConfig == null) {
            try {
                String configFile = filterConfig.getServletContext().getInitParameter("configuration-file");
                if (configFile == null) {
                    configFile = "btmlpa.properties";
                }
                InputStream configFileIn = RequestFilter.class.getClassLoader().getResourceAsStream(configFile);
                if (configFileIn == null)
                    throw new ServletException("btmlpa.properties not found");
                applConfig = new PropertiesConfiguration(configFileIn);
            } catch (Exception se) {
                throw new ServletException(se);
            }
        }

        boolean redirected = false;

        if ((req.getParameter("redirected") != null) && req.getParameter("redirected").equals("1")) {
            redirected = true;
        }

        if (req.getMethod().equals("GET") && !redirected) {

            String userAgent = req.getHeader("User-Agent");
            String term = "other";

            if ((userAgent != null) && (userAgent.contains("/"))) {
                term = userAgent.substring(userAgent.lastIndexOf("/") + 1, userAgent.length());
            }
            else if ((userAgent != null) && (userAgent.length() >= 4)) {
                term = userAgent.substring(userAgent.length() - 4, userAgent.length());
            }

            String resourceName = req.getRequestURI().replaceFirst("/btmlpa/","");

            String defaultRedirectValue = applConfig.getString(Constants.TERMINAL_OTHER, "/5100");
            String redirectValue = applConfig.getString(Constants.TERMINAL_TYPE + term, defaultRedirectValue);
            String redirectTo = res.encodeURL("/btmlpa" + redirectValue + "/" + resourceName + "?redirected=1");
            res.sendRedirect(redirectTo);
        }

        // pass the request on
        try {
            chain.doFilter(req, res);
        }
        catch (Exception e) {
            // we do nothing
        }


    }

    /**
     * Destroys the filter
     */
    public void destroy() {
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