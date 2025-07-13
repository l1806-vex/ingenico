package com.ingenico.btmlpa;

/**
 * BTMLPA constants
 */
public class Constants {

    /*
     * Payment engine configuration properties
     */

    /**
     * payment top limit
     */
    public static final String TOP_LIMIT = "btmlpa.payment.topLimit";

    /**
     * payment engine factory class
     */
    public static final String ENGINE_FACTORY = "btmlpa.payment.EngineFactory";

    /**
     * dummy delay of transactoin authorisation that emulates delay caused by
     * real transaction authorisation
     */
    public static final String DUMMY_DELAY = "btmlpa.payment.dummydelay";

    /**
     * indicates that mandatory parameter not specified
     */
    public static final int NOT_SPECIFIED = -100000;

    /**
     * Database constants
     */
    public static final String DB_USER = "btmlpa.db.user";
    public static final String DB_PASSWORD = "btmlpa.db.password";
    public static final String CONNECTION_POOL_MIN = "btmlpa.db.connpool.min";
    public static final String CONNECTION_POOL_MAX = "btmlpa.db.connpool.max";
    public static final String JDBC_DRIVER = "btmlpa.db.jdbc";
    public static final String URL_TO_DATABASE = "btmlpa.db.url";
    public static final String DBMS_NAME = "btmlpa.db.name";

    
    /**
     * terminal type
     */
    public final static String TERMINAL_TYPE = "terminal.type.";        

    /**
     * other terminals
     */
    public final static String TERMINAL_OTHER = "terminal.type.other";

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