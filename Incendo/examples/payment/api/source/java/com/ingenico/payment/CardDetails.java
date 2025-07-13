package com.ingenico.payment;

/*-- CLASS DESCRIPTION ------------------------------------------------*/

/**
 * This class represents all the information which designates a credit card.
 * 
 * @author Eugene Pestov
 */
public class CardDetails {

    /**
     * Cardholder name
     */
    private String cardholder;

    /**
     * How card details are entered
     */
    private CardInputType cardInputType;

    /**
     * Card expiration date
     */
    private CardDate expiryDate;

    /**
     * Card issue number
     */
    private int issueNumber;

    /**
     * Primary Account Number (PAN)
     */
    private String pan;

    /**
     * Card effective date
     */
    private CardDate effectiveDate;

    /**
     * ISO Track 1 data
     */
    private String track1Data;

    /**
     * ISO Track 2 data
     */
    private String track2Data;

    /**
     * ISO Track 3 data
     */
    private String track3Data;

    /**
     * Gets cardholder name
     *
     * @return cardholder name
     */
    public String getCardholder() {
        return cardholder;
    }

    /**
     * Gets method of how card details were entered
     *
     * @return method of how card details were entered
     */
    public CardInputType getCardInputType() {
        return cardInputType;
    }

    /**
     * Gets card expiration date
     *
     * @return card expiration date
     */
    public CardDate getExpiryDate() {
        return expiryDate;
    }

    /**
     * Gets card issue number
     *
     * @return card issue number
     */
    public int getIssueNumber() {
        return issueNumber;
    }

    /**
     * Gets Primary Account Number (PAN)
     *
     * @return Primary Account Number (PAN)
     */
    public String getPan() {
        return pan;
    }

    /**
     * Gets card effective date
     *
     * @return card effective date
     */
    public CardDate getEffectiveDate() {
        return effectiveDate;
    }

    /**
     * Gets ISO track 1 data
     *
     * @return ISO track 1 data
     */
    public String getTrack1Data() {
        return track1Data;
    }

    /**
     * Gets ISO track 2 data
     *
     * @return ISO track 2 data
     */
    public String getTrack2Data() {
        return track2Data;
    }

    /**
     * Gets ISO track 3 data
     *
     * @return ISO track 3 data
     */
    public String getTrack3Data() {
        return track3Data;
    }

    /**
     * Sets cardholder name
     *
     * @param string cardholder name
     */
    public void setCardholder(String string) {
        cardholder = string;
    }

    /**
     * Sets method of how card details were entered
     *
     * @param type method of how card details were entered
     */
    public void setCardInputType(CardInputType type) {
        cardInputType = type;
    }

    /**
     * Sets card expiration date
     *
     * @param date card expiration date
     */
    public void setExpiryDate(CardDate date) {
        expiryDate = date;
    }

    /**
     * Sets card issue number
     *
     * @param i card issue number
     */
    public void setIssueNumber(int i) {
        issueNumber = i;
    }

    /**
     * Sets Primary Account Number (PAN)
     *
     * @param string Primary Account Number (PAN)
     */
    public void setPan(String string) {
        pan = string;
    }

    /**
     * Sets card effective date
     *
     * @param date card effective date
     */
    public void setEffectiveDate(CardDate date) {
        effectiveDate = date;
    }

    /**
     * Sets ISO track 1 data
     *
     * @param bs ISO track 1 data
     */
    public void setTrack1Data(String bs) {
        track1Data = bs;
    }

    /**
     * Sets ISO track 2 data
     *
     * @param bs ISO track 2 data
     */
    public void setTrack2Data(String bs) {
        track2Data = bs;
    }

    /**
     * Sets ISO track 3 data
     *
     * @param bs ISO track 3 data
     */
    public void setTrack3Data(String bs) {
        track3Data = bs;
    }

}
/*
 * Incendo Online Payment API
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
