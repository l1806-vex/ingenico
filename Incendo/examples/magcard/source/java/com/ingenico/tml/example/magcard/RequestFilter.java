package com.ingenico.tml.example.magcard;

import javax.servlet.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Map;
import java.util.Hashtable;

/**
 * This class represents filter that forward clients to resources
 * according to client type
 *
 * @author Dmitry Ivanov
 */
public class RequestFilter implements Filter {

    /**
     * terminal 8550
     */
    public final static String TERMINAL_8550 = "8550";
    
    /**
     * terminal 6770
     */
    public final static String TERMINAL_6770 = "6770";
    
    /**
     * terminal 6780
     */
    public final static String TERMINAL_6780 = "6780";
    
    /**
     * terminal 6580
     */
    public final static String TERMINAL_6580 = "6580";

    /**
     * terminal 5100
     */
    public final static String TERMINAL_5100 = "5100";

    /**
     * terminal ICT250
     */
    public final static String TERMINAL_ICT250 = "ICT250";

    /**
     * terminal EFT930G Color
     */
    public final static String TERMINAL_EFT930G = "EFT930G";

    /**
     * ISC350 True Color
     */
    public final static String TERMINAL_ISC350 = "ISC350";

    /**
     * other terminals
     */
    public final static String TERMINAL_OTHER = "other";

    /**
     * resource mapping
     */
    public static Map resourceMapping;

    /**
     * Filter initialisation
     * @param config filter configuration
     * @throws javax.servlet.ServletException in case any error occur
     */
    public void init(FilterConfig config) throws ServletException {
        resourceMapping = new Hashtable();
        resourceMapping.put(TERMINAL_5100, "/5100");
        resourceMapping.put(TERMINAL_8550, "/8550");
        resourceMapping.put(TERMINAL_6770, "/8550");
        resourceMapping.put(TERMINAL_6780, "/8550");
        resourceMapping.put(TERMINAL_6580, "/8550");
        resourceMapping.put(TERMINAL_ICT250, "/8550");
        resourceMapping.put(TERMINAL_EFT930G, "/8550");
        resourceMapping.put(TERMINAL_ISC350, "/8550");
        resourceMapping.put(TERMINAL_OTHER, "/5100");
    }

    /**
     * Do filtering
     * @param request request
     * @param response response
     * @param chain filter chain
     * @throws java.io.IOException I/O exception
     * @throws ServletException in case any other than I/O exception occurs
     */
    public void doFilter(ServletRequest request, ServletResponse response,
                   FilterChain chain) throws IOException, ServletException {

        HttpServletRequest req = (HttpServletRequest)request;
        HttpServletResponse res = (HttpServletResponse)response;

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

            String resourceName = req.getRequestURI().replaceFirst("/magcard/","");

            String redirectTo = "";
            String redirectValue = "";                        

            if (term.equalsIgnoreCase(TERMINAL_8550) || 
                term.equalsIgnoreCase(TERMINAL_6770) || 
                term.equalsIgnoreCase(TERMINAL_6780) || 
                term.equalsIgnoreCase(TERMINAL_6580) ||
                term.equalsIgnoreCase(TERMINAL_ICT250) ||
                term.equalsIgnoreCase(TERMINAL_EFT930G)) {                
                redirectValue = (String)resourceMapping.get(TERMINAL_8550);
                redirectTo = res.encodeURL("/magcard" + redirectValue + "/" + resourceName + "?redirected=1");
                res.sendRedirect(redirectTo);
            }
            else if (term.equalsIgnoreCase(TERMINAL_5100)) {            	
                redirectValue = (String)resourceMapping.get(TERMINAL_5100);
                redirectTo = res.encodeURL("/magcard" + redirectValue + "/" + resourceName + "?redirected=1");
                res.sendRedirect(redirectTo);
            }
            else {            	
                redirectValue = (String)resourceMapping.get(TERMINAL_OTHER);
                redirectTo = res.encodeURL("/magcard" + redirectValue + "/" + resourceName + "?redirected=1");
                res.sendRedirect(redirectTo);
            }
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