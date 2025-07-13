package com.ingenico.btmlpa;

import java.util.Date;

import com.ingenico.payment.CardDate;

/**
 * This class represents a BTMLPA payment transaction bean.
 * 
 * @author Eugene Pestov
 */
public class PaymentTransaction {

    /**
     * time in milliseconds that took acquirer authorisation
     */
    private long acqrDuration;

    /**
     * datetime when transactoin is sent to acquirer
     */
    private Date acqrStarted;

    /**
     * transactoin amount
     */
    private long amount;

    /**
     * cash back amount
     */
    private long amountOther;

    /**
     * authorisation code
     */
    private String authorisationCode;

    /**
     * How card details were entered
     */
    private int cardInputType;

    /**
     * card expiration date
     */
    private CardDate cardExpiry;

    /**
     * Card issue number
     */
    private int cardIssue;

    /**
     * primary account number (PAN)
     */
    private String cardNumber;

    /**
     * card start date
     */
    private CardDate cardStart;

    /**
     * Cardholder name
     */
    private String cardHolderName;

    /**
     * currency code
     */
    private String currencyCode;

    /**
     * transactoin duration
     */
    private long duration;

    /**
     * transaction id
     */
    private long id = -1;

    /**
     * post id
     */
    private String postID = "-1";

    /**
     * message received from acquirer
     */
    private String messageFromAcquirer;

    /**
     * submit mode
     */
    private String submitMode;

    /**
     * datetime when transaction started
     */
    private Date started;

    /**
     * terminal bean
     */
    private Terminal terminal;

    /**
     * transaction id specified by terminal (post id)
     */
    private long terminalTransactionId;

    /**
     * datetime of transaction specified by terminal
     */
    private Date terminalTransactionDate;

    /**
     * datetime of transaction post specified by terminal
     */
    private Date postTransactionDate;

    /**
     * transaction type
     */
    private int type;

    /**
     * transaction state
     */
    private int state;

    /**
     * iso2 track
     */
    private String iso2Track;

    // ICC request data

    /**
     * application PAN sequence number
     */
    private String icc_app;

    /**
     * application interchange profile
     */
    private int icc_aip;

    /**
     * application usage control
     */
    private int icc_auc;

    /**
     * application transaction counter
     */
    private int icc_atc;

    /**
     * application authentication cryptogram
     */
    private byte[] icc_aac;

    /**
     * transaction certificate
     */
    private byte[] icc_tc;

    /**
     * authorisation request cryptogram
     */
    private byte[] icc_arqc;

    /**
     * issuer application data
     */
    private byte[] icc_iad;

    /**
     * terminal verification results
     */
    private byte[] icc_tvr;

    /**
     * unpredictable number
     */
    private int icc_unumber;

    // ICC response data

    /**
     * authorisation response cryptogram
     */
    private byte[] icc_arpc;

    /**
     * issuer script
     */
    private byte[] issuer_script;

    /**
     * issuer authorisation data
     */
    private byte[] issuer_auth;

    /**
     * Empty constructor
     */
    public PaymentTransaction() {
    }


    /**
     * Gets time in milliseconds that took acquirer authorisation
     *
     * @return time in milliseconds that took acquirer authorisation
     */
    public long getAcqrDuration() {
        return acqrDuration;
    }

    /**
     * Sets time in milliseconds that took acquirer authorisation
     *
     * @param acqrDuration time in milliseconds that took acquirer authorisation
     */
    public void setAcqrDuration(long acqrDuration) {
        this.acqrDuration = acqrDuration;
    }

    /**
     * Gets datetime when transactoin is sent to acquirer
     *
     * @return datetime when transactoin is sent to acquirer
     */
    public Date getAcqrStarted() {
        return acqrStarted;
    }

    /**
     * Sets datetime when transactoin is sent to acquirer
     *
     * @param acqrStarted datetime when transactoin is sent to acquirer
     */
    public void setAcqrStarted(Date acqrStarted) {
        this.acqrStarted = acqrStarted;
    }

    /**
     * Gets transactoin amount
     *
     * @return transactoin amount
     */
    public long getAmount() {
        return amount;
    }

    /**
     * Sets transactoin amount
     *
     * @param amount transactoin amount
     */
    public void setAmount(long amount) {
        this.amount = amount;
    }

    /**
     * Gets cash back amount
     *
     * @return cash back amount
     */
    public long getAmountOther() {
        return amountOther;
    }

    /**
     * Sets cash back amount
     *
     * @param amountOther cash back amount
     */
    public void setAmountOther(long amountOther) {
        this.amountOther = amountOther;
    }

    /**
     * Gets authorisation code
     *
     * @return authorisation code
     */
    public String getAuthorisationCode() {
        return authorisationCode;
    }

    /**
     * Sets authorisation code
     *
     * @param authorisationCode authorisation code
     */
    public void setAuthorisationCode(String authorisationCode) {
        this.authorisationCode = authorisationCode;
    }

    /**
     * Gets card expiration date
     *
     * @return card expiration date
     */
    public CardDate getCardExpiry() {
        return cardExpiry;
    }

    /**
     * Sets card expiration date
     *
     * @param cardExpiry card expiration date
     */
    public void setCardExpiry(CardDate cardExpiry) {
        this.cardExpiry = cardExpiry;
    }

    /**
     * Gets card input type
     *
     * @return card input type
     */
    public int getCardInputType() {
        return cardInputType;
    }

    /**
     * Sets card input type
     *
     * @param cardInputType card input type
     */
    public void setCardInputType(int cardInputType) {
        this.cardInputType = cardInputType;
    }

    /**
     * Gets card issue number
     *
     * @return card issue number
     */
    public int getCardIssue() {
        return cardIssue;
    }

    /**
     * Sets card issue number
     *
     * @param cardIssue card issue number
     */
    public void setCardIssue(int cardIssue) {
        this.cardIssue = cardIssue;
    }

    /**
     * Gets primary account number
     *
     * @return primary account number
     */
    public String getCardNumber() {
        return cardNumber;
    }

    /**
     * Sets primary account number
     *
     * @param cardNumber primary account number
     */
    public void setCardNumber(String cardNumber) {
        this.cardNumber = cardNumber;
    }

    /**
     * Gets card start date
     *
     * @return card start date
     */
    public CardDate getCardStart() {
        return cardStart;
    }

    /**
     * Sets card start date
     *
     * @param cardStart card start date
     */
    public void setCardStart(CardDate cardStart) {
        this.cardStart = cardStart;
    }

    /**
     * Gets cardholder name
     *
     * @return cardholder name
     */
    public String getCardHolderName() {
        return cardHolderName;
    }

    /**
     * Sets cardholder name
     *
     * @param cardHolderName cardholder name
     */
    public void setCardHolderName(String cardHolderName) {
        this.cardHolderName = cardHolderName;
    }

    /**
     * Gets currency code
     *
     * @return currency code
     */
    public String getCurrencyCode() {
        return currencyCode;
    }

    /**
     * Sets currency code
     *
     * @param currencyCode currency code
     */
    public void setCurrencyCode(String currencyCode) {
        this.currencyCode = currencyCode;
    }

    /**
     * Gets transactoin duration
     *
     * @return transactoin duration
     */
    public long getDuration() {
        return duration;
    }

    /**
     * Sets transactoin duration
     *
     * @param duration transactoin duration
     */
    public void setDuration(long duration) {
        this.duration = duration;
    }

    /**
     * Gets transaction id
     *
     * @return transaction id
     */
    public long getId() {
        return id;
    }

    /**
     * Sets transaction id
     *
     * @param id transaction id
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     * Gets post id
     *
     * @return post id
     */
    public String getPostID() {
        return postID;
    }

    /**
     * Sets post id
     *
     * @param postID post id
     */
    public void setPostID(String postID) {
        this.postID = postID;
    }

    /**
     * Gets message received from acquirer
     *
     * @return message received from acquirer
     */
    public String getMessageFromAcquirer() {
        return messageFromAcquirer;
    }

    /**
     * Sets message received from acquirer
     *
     * @param messageFromAcquirer message received from acquirer
     */
    public void setMessageFromAcquirer(String messageFromAcquirer) {
        this.messageFromAcquirer = messageFromAcquirer;
    }

    /**
     * Gets datetime when transaction started
     *
     * @return datetime when transaction started
     */
    public Date getStarted() {
        return started;
    }

    /**
     * Sets datetime when transaction started
     *
     * @param started datetime when transaction started
     */
    public void setStarted(Date started) {
        this.started = started;
    }

    /**
     * Gets transaction state
     *
     * @return transaction state
     */
    public int getState() {
        return state;
    }

    /**
     * Sets transaction state
     *
     * @param state transaction state
     */
    public void setState(int state) {
        this.state = state;
    }

    /**
     * Gets submit mode
     *
     * @return submit mode
     */
    public String getSubmitMode() {
        return submitMode;
    }

    /**
     * Sets submit mode
     *
     * @param submitMode submit mode
     */
    public void setSubmitMode(String submitMode) {
        this.submitMode = submitMode;
    }

    /**
     * Gets terminal bean
     *
     * @return terminal bean
     */
    public Terminal getTerminal() {
        return terminal;
    }

    /**
     * Sets terminal bean
     *
     * @param terminal terminal bean
     */
    public void setTerminal(Terminal terminal) {
        this.terminal = terminal;
    }

    /**
     * transaction id specified by terminal
     *
     * @return transaction id specified by terminal
     */
    public long getTerminalTransactionId() {
        return terminalTransactionId;
    }

    /**
     * Sets transaction id specified by terminal
     *
     * @param terminalTransactionId transaction id specified by terminal
     */
    public void setTerminalTransactionId(long terminalTransactionId) {
        this.terminalTransactionId = terminalTransactionId;
    }

    /**
     * Sets datetime of transaction specified by terminal
     *
     * @param terninalTransactionDate datetime of transaction specified by terminal
     */
    public void setTerminalTransactionDate(Date terninalTransactionDate) {
        this.terminalTransactionDate = terninalTransactionDate;
    }

  public Date getTerminalTransactionDate() {
      return this.terminalTransactionDate;
  }

    /**
     * Gets post transaction date specified by terminal
     *
     * @return post transaction date specified by terminal
     */
    public Date getPostTransactionDate() {
        return postTransactionDate;
    }

    /**
     * Sets post transaction date specified by terminal
     * 
     * @param postTransactionDate post transaction date specified by terminal
     */
    public void setPostTransactionDate(Date postTransactionDate) {
        this.postTransactionDate = postTransactionDate;
    }

    /**
     * Gets transaction type
     *
     * @return transaction type
     */
    public int getType() {
        return type;
    }

    /**
     * Sets transaction type
     *
     * @param type transaction type
     */
    public void setType(int type) {
        this.type = type;
    }

    /**
     * Gets application authentication cryptogram
     *
     * @return application authentication cryptogram
     */
    public byte[] getIcc_aac() {
        return icc_aac;
    }

    /**
     * Sets application authentication cryptogram
     *
     * @param icc_aac application authentication cryptogram
     */
    public void setIcc_aac(byte[] icc_aac) {
        this.icc_aac = icc_aac;
    }

    /**
     * Gets application interchange profile
     *
     * @return application interchange profile
     */
    public int getIcc_aip() {
        return icc_aip;
    }

    /**
     * Sets application interchange profile
     *
     * @param icc_aip application interchange profile
     */
    public void setIcc_aip(int icc_aip) {
        this.icc_aip = icc_aip;
    }

    /**
     * Gets application PAN sequence number
     *
     * @return application PAN sequence number
     */
    public String getIcc_app() {
        return icc_app;
    }

    /**
     * Sets application PAN sequence number
     *
     * @param icc_app application PAN sequence number
     */
    public void setIcc_app(String icc_app) {
        this.icc_app = icc_app;
    }

    /**
     * Gets application transaction counter
     *
     * @return application transaction counter
     */
    public int getIcc_atc() {
        return icc_atc;
    }

    /**
     * Sets application transaction counter
     *
     * @param icc_atc application transaction counter
     */
    public void setIcc_atc(int icc_atc) {
        this.icc_atc = icc_atc;
    }

    /**
     * Gets application usage control
     *
     * @return application usage control
     */
    public int getIcc_auc() {
        return icc_auc;
    }

    /**
     * Sets application usage control
     *
     * @param icc_auc application usage control
     */
    public void setIcc_auc(int icc_auc) {
        this.icc_auc = icc_auc;
    }

    /**
     * Gets issuer application data
     *
     * @return issuer application data
     */
    public byte[] getIcc_iad() {
        return icc_iad;
    }

    /**
     * Sets issuer application data
     *
     * @param icc_iad issuer application data
     */
    public void setIcc_iad(byte[] icc_iad) {
        this.icc_iad = icc_iad;
    }

    /**
     * Gets authorisation request cryptogram
     *
     * @return authorisation request cryptogram
     */
    public byte[] getIcc_arqc() {
        return icc_arqc;
    }

    /**
     * Sets authorisation request cryptogram
     *
     * @param icc_irqc authorisation request cryptogram
     */
    public void setIcc_arqc(byte[] icc_irqc) {
        this.icc_arqc = icc_irqc;
    }

    /**
     * Gets transaction certificate
     *
     * @return transaction certificate
     */
    public byte[] getIcc_tc() {
        return icc_tc;
    }

    /**
     * Sets transaction certificate
     *
     * @param icc_tc transaction certificate
     */
    public void setIcc_tc(byte[] icc_tc) {
        this.icc_tc = icc_tc;
    }

    /**
     * Gets terminal verification results
     *
     * @return terminal verification results
     */
    public byte[] getIcc_tvr() {
        return icc_tvr;
    }

    /**
     * Sets terminal verification results
     *
     * @param icc_tvr terminal verification results
     */
    public void setIcc_tvr(byte[] icc_tvr) {
        this.icc_tvr = icc_tvr;
    }

    /**
     * Gets unpredictable number
     *
     * @return unpredictable number
     */
    public int getIcc_unumber() {
        return icc_unumber;
    }

    /**
     * Sets unpredictable number
     *
     * @param icc_unumber unpredictable number
     */
    public void setIcc_unumber(int icc_unumber) {
        this.icc_unumber = icc_unumber;
    }

    /**
     * Gets authorisation response cryptogram
     *
     * @return authorisation response cryptogram
     */
    public byte[] getIcc_arpc() {
        return icc_arpc;
    }

    /**
     * Sets authorisation response cryptogram
     *
     * @param icc_arpc authorisation response cryptogram
     */
    public void setIcc_arpc(byte[] icc_arpc) {
        this.icc_arpc = icc_arpc;
    }

    /**
     * Gets issuer authorisation data
     *
     * @return issuer authorisation data
     */
    public byte[] getIssuer_auth() {
        return issuer_auth;
    }

    /**
     * Sets issuer authorisation data
     *
     * @param issuer_auth issuer authorisation data
     */
    public void setIssuer_auth(byte[] issuer_auth) {
        this.issuer_auth = issuer_auth;
    }

    /**
     * Gets issuer script
     *
     * @return issuer script
     */
    public byte[] getIssuer_script() {
        return issuer_script;
    }

    /**
     * Sets issuer script
     *
     * @param issuer_script issuer script
     */
    public void setIssuer_script(byte[] issuer_script) {
        this.issuer_script = issuer_script;
    }

    /**
     * Gets iso2 track
     *
     * @return iso2 track
     */
    public String getIso2Track() {
        return iso2Track;
    }

    /**
     * Sets iso2 track
     *
     * @param iso2_track iso2 track
     */
    public void setIso2Track(String iso2_track) {
        this.iso2Track = iso2_track;
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