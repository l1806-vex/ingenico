package com.ingenico.btmlpa.db;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Timestamp;
import java.sql.Types;

import com.ingenico.btmlpa.PaymentTransaction;
import com.ingenico.btmlpa.Terminal;
import com.ingenico.payment.CardDate;
import com.ingenico.util.logging.Logger;
import com.ingenico.webappl.common.Constants;
import com.ingenico.webappl.db.ConnectionFailedException;
import com.ingenico.webappl.db.ConnectionPool;
import com.ingenico.webappl.db.DBClient;
import com.ingenico.webappl.db.DBDataObject;
import com.ingenico.webappl.db.DBException;

/**
 * This class contains business logic
 * for BTMLPA application
 * <p/>
 */
public class BTMLPA {

    /**
     * logger
     */
    private static Logger logger = Logger.getLogger(BTMLPA.class.getName());

    /**
     * This method gets terminal properties
     *
     * @param itid terminal id
     * @return container that contains terminal info
     * @throws DBException if any errors occurs
     */
    public static Terminal getTerminal(String itid, String sessionID)
            throws DBException {

        DBDataObject dbdo = null;

        StringBuffer strSQL = new StringBuffer();

        strSQL.append("SELECT *");
        strSQL.append(" FROM ");
        strSQL.append(" BTMLPA_TERMINAL ");
        strSQL.append(" WHERE ");
        strSQL.append(" OE_ITID = '" + itid + "'");

        logger.fine("BTMLPA.getTerminal query: " + strSQL.toString());

        Terminal term = null;

        try {
            dbdo = DBClient.getInstance().doSelect(sessionID, strSQL.toString(),
                    Constants.SELECT_ROWS_UNLIMITED);
            if (dbdo.getRecordsCount() > 0) {
                int id = Integer.parseInt(dbdo.getField(0, "ID"));
                String tid = dbdo.getField(0, "APACS_TID");
                term = new Terminal(id, itid, tid);
            }
        } catch (Exception e) {
            logger.severe("BTMLPA.getTerminal:\n" + e.toString());
            throw new DBException("BTMLPA.getTerminal: " + e.toString());
        }

        return term;

    }

    /**
     * This method gets terminal properties
     *
     * @param termID terminal id
     * @return container that contains terminal info
     * @throws DBException if any errors occurs
     */
    public static Terminal getTerminal(long termID, String sessionID)
            throws DBException {

        DBDataObject dbdo = null;

        StringBuffer strSQL = new StringBuffer();

        strSQL.append("SELECT *");
        strSQL.append(" FROM ");
        strSQL.append(" BTMLPA_TERMINAL ");
        strSQL.append(" WHERE ");
        strSQL.append(" ID = " + termID);

        logger.fine("BTMLPA.getTerminal query: " + strSQL.toString());

        Terminal term = null;

        try {
            dbdo = DBClient.getInstance().doSelect(sessionID, strSQL.toString(),
                    Constants.SELECT_ROWS_UNLIMITED);
            if (dbdo.getRecordsCount() > 0) {
                String itid = dbdo.getField(0, "OE_ITID");
                String tid = dbdo.getField(0, "APACS_TID");
                term = new Terminal(termID, itid, tid);
            }
        } catch (Exception e) {
            logger.severe("BTMLPA.getTerminal:\n" + e.toString());
            throw new DBException("BTMLPA.getTerminal: " + e.toString());
        }

        return term;

    }

    /**
     * This method gets terminal properties
     *
     * @param terminal terminal
     * @return container that contains terminal info
     * @throws DBException if any errors occurs
     */
    public static PaymentTransaction getTxn(Terminal terminal, long txnID, String sessionID)
            throws DBException {

        StringBuffer strSQL = new StringBuffer();

        strSQL.append("SELECT ID, TERMINAL_POST_ID, TERMINAL_TXN_ID, TYPE, TERMINAL_ID, " +
                "TERM_TXN_DATE, POST_TXN_DATE, TXN_STARTED, TXN_DURATION, ACQR_STARTED, " +
                "ACQR_DURATION, STATE, PAN, STARTDATE, EXPIRYDATE, CARDHOLDERNAME, INPUTMETHOD, " +
                "ISSUENUMBER, ISO2TRACK, ICC_APP, ICC_AIP, ICC_ATC, " +
                "ICC_ARQC, ICC_IAD, ICC_TVR, ICC_UNUMBER, ICC_ARPC, ICC_ISSUER_AUTH, " +
                "ICC_ISSUER_SCRIPT, MESSAGE, AUTH_CODE, AMOUNT, " +
                "AMOUNT_OTHER, CURRENCY_CODE, TXNMODE");
        strSQL.append(" FROM ");
        strSQL.append(" BTMLPA_TXN ");
        strSQL.append(" WHERE ");
        strSQL.append(" TERMINAL_ID = " + terminal.getId());
        strSQL.append(" AND TERMINAL_TXN_ID = " + txnID);

        logger.fine("BTMLPA.getTxn query: " + strSQL.toString());

        PaymentTransaction pmntTxn = null;

        try {
            Connection ctn = getConnection();
            PreparedStatement prepStmt = ctn.prepareStatement(strSQL.toString());

            ResultSet rslt = prepStmt.executeQuery();

            if (rslt.next()) {
                pmntTxn = new PaymentTransaction();

                pmntTxn.setTerminalTransactionId(txnID);
                pmntTxn.setPostID(rslt.getString("TERMINAL_POST_ID"));
                pmntTxn.setType(rslt.getInt("TYPE"));

                pmntTxn.setTerminal(terminal);

                pmntTxn.setId(rslt.getLong("ID"));
                pmntTxn.setTerminalTransactionDate(rslt.getTimestamp("TERM_TXN_DATE"));
                pmntTxn.setPostTransactionDate(rslt.getTimestamp("POST_TXN_DATE"));
                pmntTxn.setStarted(rslt.getTimestamp("TXN_STARTED"));
                pmntTxn.setDuration(rslt.getLong("TXN_DURATION"));
                pmntTxn.setAcqrStarted(rslt.getTimestamp("ACQR_STARTED"));
                pmntTxn.setAcqrDuration(rslt.getLong("ACQR_DURATION"));
                pmntTxn.setState(rslt.getInt("STATE"));
                pmntTxn.setCardNumber(rslt.getString("PAN"));
                if (rslt.getString("STARTDATE") != null) {
                    pmntTxn.setCardStart(new CardDate(rslt.getString("STARTDATE")));
                }
                if (rslt.getString("EXPIRYDATE") != null) {
                    pmntTxn.setCardExpiry(new CardDate(rslt.getString("EXPIRYDATE")));
                }
                if (rslt.getString("CARDHOLDERNAME") != null) {
                    pmntTxn.setCardHolderName(rslt.getString("CARDHOLDERNAME"));
                }
                pmntTxn.setCardInputType(rslt.getInt("INPUTMETHOD"));
                pmntTxn.setCardIssue(rslt.getInt("ISSUENUMBER"));
                pmntTxn.setIso2Track(rslt.getString("ISO2TRACK"));
                pmntTxn.setIcc_app(rslt.getString("ICC_APP"));
                pmntTxn.setIcc_aip(rslt.getInt("ICC_AIP"));
                pmntTxn.setIcc_atc(rslt.getInt("ICC_ATC"));
                pmntTxn.setIcc_arqc(rslt.getBytes("ICC_ARQC"));
                pmntTxn.setIcc_iad(rslt.getBytes("ICC_IAD"));
                pmntTxn.setIcc_tvr(rslt.getBytes("ICC_TVR"));
                pmntTxn.setIcc_unumber(rslt.getInt("ICC_UNUMBER"));
                pmntTxn.setIcc_arpc(rslt.getBytes("ICC_ARPC"));
                pmntTxn.setIssuer_auth(rslt.getBytes("ICC_ISSUER_AUTH"));
                pmntTxn.setIssuer_script(rslt.getBytes("ICC_ISSUER_SCRIPT"));
                pmntTxn.setMessageFromAcquirer(rslt.getString("MESSAGE"));
                pmntTxn.setAuthorisationCode(rslt.getString("AUTH_CODE"));
                pmntTxn.setAmount(rslt.getLong("AMOUNT"));
                pmntTxn.setAmountOther(rslt.getLong("AMOUNT_OTHER"));
                pmntTxn.setCurrencyCode(rslt.getString("CURRENCY_CODE"));
                pmntTxn.setSubmitMode(rslt.getString("TXNMODE"));

            }

            // let's free up resources
            rslt.close();
            prepStmt.close();
            prepStmt = null;

            ctn.commit();

            releaseConnection(ctn, true);

            return pmntTxn;

        } catch (Exception e) {
            logger.severe("BTMLPA.getTxn:\n" + e.toString());
            throw new DBException("BTMLPA.getTxn: " + e.toString());
        }

    }

    /**
     * This method gets terminal properties
     *
     * @param terminal terminal
     * @return container that contains terminal info
     * @throws DBException if any errors occurs
     */
    public static long getTxnID(Terminal terminal, long termTxnID, String sessionID)
            throws DBException {

        DBDataObject dbdo = null;

        StringBuffer strSQL = new StringBuffer();

        strSQL.append("SELECT ID");
        strSQL.append(" FROM ");
        strSQL.append(" BTMLPA_TXN ");
        strSQL.append(" WHERE ");
        strSQL.append(" TERMINAL_ID = " + terminal.getId());
        strSQL.append(" AND TERMINAL_TXN_ID = " + termTxnID);

        logger.fine("BTMLPA.getTxnID query: " + strSQL.toString());

        long txnID = -1;

        try {
            dbdo = DBClient.getInstance().doSelect(sessionID, strSQL.toString(),
                    Constants.SELECT_ROWS_UNLIMITED);
            if (dbdo.getRecordsCount() > 0) {
                txnID = Long.parseLong(dbdo.getField(0, "ID"));
            }
        } catch (Exception e) {
            logger.severe("BTMLPA.getTxnID:\n" + e.toString());
            throw new DBException("BTMLPA.getTxnID: " + e.toString());
        }

        return txnID;

    }

    /**
     * This method updates terminals
     *
     * @param pmntTxn   payment txn
     * @throws DBException if any errors occurs
     */
    public static void saveTxn(PaymentTransaction pmntTxn, String sessionID)
            throws DBException {

        StringBuffer strSQL = new StringBuffer();

        if (pmntTxn.getId() == -1) {
            // new txn
            strSQL.append("INSERT INTO BTMLPA_TXN(TERMINAL_POST_ID, TERMINAL_TXN_ID, TYPE, TERMINAL_ID, " +
                    "TERM_TXN_DATE, POST_TXN_DATE, TXN_STARTED, TXN_DURATION, ACQR_STARTED, " +
                    "ACQR_DURATION, STATE, PAN, STARTDATE, CARDHOLDERNAME, EXPIRYDATE, INPUTMETHOD, " +
                    "ISSUENUMBER, ISO2TRACK, ICC_APP, ICC_AIP, ICC_ATC, " +
                    "ICC_ARQC, ICC_IAD, ICC_TVR, ICC_UNUMBER, ICC_ARPC, ICC_ISSUER_AUTH, " +
                    "ICC_ISSUER_SCRIPT, MESSAGE, AUTH_CODE, AMOUNT, " +
                    "AMOUNT_OTHER, CURRENCY_CODE, TXNMODE) ");
            strSQL.append("VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
        }
        else {
            // txn already exists
            strSQL.append("UPDATE BTMLPA_TXN SET TERMINAL_POST_ID = ?, TERMINAL_TXN_ID = ?, TYPE = ?, TERMINAL_ID = ?, " +
                    "TERM_TXN_DATE = ?, POST_TXN_DATE = ?, TXN_STARTED = ?, TXN_DURATION = ?, ACQR_STARTED = ?, " +
                    "ACQR_DURATION = ?, STATE = ?, PAN = ?, STARTDATE = ?, CARDHOLDERNAME = ?, EXPIRYDATE = ?, INPUTMETHOD = ?, " +
                    "ISSUENUMBER = ?, ISO2TRACK = ?, ICC_APP = ?, ICC_AIP = ?, ICC_ATC = ?, " +
                    "ICC_ARQC = ?, ICC_IAD = ?, ICC_TVR = ?, ICC_UNUMBER = ?, ICC_ARPC = ?, ICC_ISSUER_AUTH = ?, " +
                    "ICC_ISSUER_SCRIPT = ?, MESSAGE = ?, AUTH_CODE = ?, AMOUNT = ?, " +
                    "AMOUNT_OTHER = ?, CURRENCY_CODE = ?, TXNMODE = ? WHERE ID = ?");
        }

            Connection ctn = getConnection();
            try {
                PreparedStatement prepStmt = ctn.prepareStatement(strSQL.toString());
                prepStmt.setLong(1, Long.valueOf(pmntTxn.getPostID()));
                prepStmt.setLong(2, pmntTxn.getTerminalTransactionId());
                prepStmt.setLong(3, pmntTxn.getType());
                prepStmt.setLong(4, pmntTxn.getTerminal().getId());
                if (pmntTxn.getTerminalTransactionDate() != null) {
                    prepStmt.setTimestamp(5, new Timestamp(pmntTxn.getTerminalTransactionDate().getTime()));
                }
                else {
                    prepStmt.setNull(5, Types.TIMESTAMP);
                }
                if (pmntTxn.getPostTransactionDate() != null) {
                    prepStmt.setTimestamp(6, new Timestamp(pmntTxn.getPostTransactionDate().getTime()));
                }
                else {
                    prepStmt.setNull(6, Types.TIMESTAMP);
                }
                if (pmntTxn.getStarted() != null) {
                    prepStmt.setTimestamp(7, new Timestamp(pmntTxn.getStarted().getTime()));
                }
                else {
                    prepStmt.setNull(7, Types.TIMESTAMP);
                }
                prepStmt.setLong(8, pmntTxn.getDuration());
                if (pmntTxn.getAcqrStarted() != null) {
                    prepStmt.setTimestamp(9, new Timestamp(pmntTxn.getAcqrStarted().getTime()));
                }
                else {
                    prepStmt.setNull(9, Types.TIMESTAMP);
                }
                prepStmt.setLong(10, pmntTxn.getAcqrDuration());
                prepStmt.setLong(11, pmntTxn.getState());
                prepStmt.setString(12, pmntTxn.getCardNumber());
                if (pmntTxn.getCardStart() != null) {
                    prepStmt.setString(13, pmntTxn.getCardStart().toString());
                }
                else {
                    prepStmt.setNull(13, Types.CHAR);
                }
                if (pmntTxn.getCardHolderName() != null) {
                    prepStmt.setString(14, pmntTxn.getCardHolderName());
                }
                else {
                    prepStmt.setNull(14, Types.CHAR);
                }
                if (pmntTxn.getCardExpiry() != null) {
                    prepStmt.setString(15, pmntTxn.getCardExpiry().toString());
                }
                else {
                    prepStmt.setNull(15, Types.CHAR);
                }
                prepStmt.setInt(16, pmntTxn.getCardInputType());
                prepStmt.setInt(17, pmntTxn.getCardIssue());
                prepStmt.setString(18, pmntTxn.getIso2Track());
                prepStmt.setString(19, pmntTxn.getIcc_app());
                prepStmt.setInt(20, pmntTxn.getIcc_aip());
                prepStmt.setInt(21, pmntTxn.getIcc_atc());
                if (pmntTxn.getIcc_arqc() != null) {
                    prepStmt.setBytes(22, pmntTxn.getIcc_arqc());
                }
                else {
                    prepStmt.setNull(22, Types.BINARY);
                }
                if (pmntTxn.getIcc_iad() != null) {
                    prepStmt.setBytes(23, pmntTxn.getIcc_iad());
                }
                else {
                    prepStmt.setNull(23, Types.BINARY);
                }
                if (pmntTxn.getIcc_tvr() != null) {
                    prepStmt.setBytes(24, pmntTxn.getIcc_tvr());
                }
                else {
                    prepStmt.setNull(24, Types.BINARY);
                }
                prepStmt.setInt(25, pmntTxn.getIcc_unumber());
                if (pmntTxn.getIcc_arpc() != null) {
                    prepStmt.setBytes(26, pmntTxn.getIcc_arpc());
                }
                else {
                    prepStmt.setNull(26, Types.BINARY);
                }
                if (pmntTxn.getIssuer_auth() != null) {
                    prepStmt.setBytes(27, pmntTxn.getIssuer_auth());
                }
                else {
                    prepStmt.setNull(27, Types.BINARY);
                }
                if (pmntTxn.getIssuer_script() != null) {
                    prepStmt.setBytes(28, pmntTxn.getIssuer_script());
                }
                else {
                    prepStmt.setNull(28, Types.BINARY);
                }
                if (pmntTxn.getMessageFromAcquirer() != null) {
                    prepStmt.setString(29, pmntTxn.getMessageFromAcquirer());
                }
                else {
                    prepStmt.setNull(29, Types.CHAR);
                }
                if (pmntTxn.getAuthorisationCode() != null) {
                    prepStmt.setString(30, pmntTxn.getAuthorisationCode());
                }
                else {
                    prepStmt.setNull(30, Types.CHAR);
                }
                prepStmt.setLong(31, pmntTxn.getAmount());
                prepStmt.setLong(32, pmntTxn.getAmountOther());
                if (pmntTxn.getCurrencyCode() != null) {
                    prepStmt.setString(33, pmntTxn.getCurrencyCode());
                }
                else {
                    prepStmt.setNull(33, Types.CHAR);
                }
                if (pmntTxn.getSubmitMode() != null) {
                    prepStmt.setString(34, pmntTxn.getSubmitMode());
                }
                else {
                    prepStmt.setNull(34, Types.CHAR);
                }

                if (pmntTxn.getId() != -1) {
                    prepStmt.setLong(35, pmntTxn.getId());
                }

                prepStmt.executeUpdate();

                // let's free up resources
                prepStmt.close();
                prepStmt = null;

                ctn.commit();

                releaseConnection(ctn, true);

                if (pmntTxn.getId() == -1) {
                    long txnID = getTxnID(pmntTxn.getTerminal(), pmntTxn.getTerminalTransactionId(), sessionID);
                    pmntTxn.setId(txnID);
                }
            }
            catch (SQLException e) {
                try {
                    ctn.rollback();
                    releaseConnection(ctn, true);
                } catch (Exception ex) {
                    releaseConnection(ctn, false);
                }
                processErrorCode(e);
            }

    }

    /**
     * Obtains database connection from the connection pool
     *
     * @return database connection
     * @throws com.ingenico.webappl.db.DBException if any errors occur
     */
    private static Connection getConnection() throws DBException {
        Connection ctn = null;
        try {
            ctn = ConnectionPool.getInstance().getConnection("", null);
        } catch (com.ingenico.webappl.common.NotYetInitializedException e) {
            // we do nothing
        }
        return ctn;
    }

    /**
     * Releases connection to the pool
     *
     * @param ctn    connection
     * @param status connection status
     */
    private static void releaseConnection(Connection ctn, boolean status) {
        try {
            ConnectionPool.getInstance().releaseConnection(ctn, status);
        } catch (com.ingenico.webappl.common.NotYetInitializedException exc) {
            // we do nothing
        }
    }

    /**
     * This method processes sql errors
     * @param e sql exception
     * @throws DBException exception after processing
     */
    public static void processErrorCode(SQLException e) throws DBException {
        if (e.getMessage().indexOf("Communication link failure") != -1) {
            throw new ConnectionFailedException("Communication to database is broken. " +
                    "Please, check that there is a SQL server running on the machine/port " +
                    "you are trying to connect to.");
        }
        else {
            throw new DBException(e.getMessage());
        }
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