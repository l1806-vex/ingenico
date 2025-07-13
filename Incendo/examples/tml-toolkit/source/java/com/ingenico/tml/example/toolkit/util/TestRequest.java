package com.ingenico.tml.example.toolkit.util;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

import com.ingenico.util.configuration.Version;
import com.ingenico.util.exception.ExitCodes;

/**
 * This class represents TML request
 * @author Eugene Pestov
 */
public class TestRequest {

    private static final String COPYRIGHT_MESSAGE = "Copyright (C) 2003-2012 " +
            "Ingenico.";
    private static final String UNDERSCORE = "--------------------------" +
            "---------------------------";

    /**
     * tool version
     */
    private static final String VERSION = Version.FULL_VERSION;

    /**
     * Title
     */
    public static final String APPLICATION_NAME = "Incendo Online TML Toolkit.";

    /**
     * Main
     * @param argv arguments
     */
    public static void main(String[] argv) {

        // print start message
        System.out.println(getStartMessage());

        
        if (argv.length != 2) {
        	displayUsage();
        	System.exit(0);
        }
        	
        String fileName = argv[0];
        String urlStr = "http://localhost:8090/";
        String exampleName = argv[1];
        
        if (exampleName.equals("btmlpa")) {
        	urlStr += "btmlpa/auth";
        } else if (exampleName.equals("iccemv")) {
        	urlStr += "iccemv/authtnx";
        } else if (exampleName.equals("magcard")) {
        	urlStr += "magcard/authtnx";
        } else {
        	urlStr = exampleName;
        }
        
        System.out.println("Sending the request to " + urlStr);
        
        try {

            // Construct data
            FileInputStream isRequest = new FileInputStream(fileName);
            byte[] request = new byte[isRequest.available()];
            isRequest.read(request);

            URL url = new URL(urlStr);
            HttpURLConnection httpConnection = (HttpURLConnection) url
                    .openConnection();
            httpConnection.setRequestMethod("POST");
            httpConnection.setRequestProperty("Content-Type", "text/tml");
            httpConnection.setDoOutput(true);
            OutputStream os = httpConnection.getOutputStream();
            os.write(request);
            os.flush();

            // Get the response
            BufferedReader rd;
            try {
                rd = new BufferedReader(new InputStreamReader(httpConnection
                        .getInputStream()));
            } catch (IOException e) {
                System.out.println(e.toString());
                rd = new BufferedReader(new InputStreamReader(httpConnection
                        .getErrorStream()));
            }

            String line;
            while ((line = rd.readLine()) != null) {
                // Process line...
                System.out.println(line);
            }
            os.close();
            rd.close();

        } catch (IOException e) {
            System.out.println(e.toString());
            System.exit(ExitCodes.ERROR);
        }

    }

    /**
     * Prints usage
     */
    private static void displayUsage() {
    	System.out.println("Usage: TestRequest filename btmlpa |iccemv |magcard | url");
    	System.out.println("Description:");
    	System.out.println("\tSends request from 'filename' to corresponding example application");
    	System.out.println("\turl by alias (btmlpa, iccemv, magcard) or to defined application url ");
    	System.out.println("\t(url parameter is valid URL).");
    }

    /**
     * Gets copyright notice
     * @return copyright notice
     */
    public static String getStartMessage() {
        String sVersion = "v." + VERSION;
        String sStartMsg = APPLICATION_NAME + " " + sVersion + "\n" +
                COPYRIGHT_MESSAGE + "\n" + UNDERSCORE;
        return sStartMsg;
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