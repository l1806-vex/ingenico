package com.ingenico.payment;

import java.io.Serializable;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.TimeZone;

/**
 * This type represents a card date, eg month and year - 05/04. This type is
 * immutable.
 * 
 * @author Eugene Pestov
 */
public class CardDate implements Serializable, Cloneable {

    /**
     * Date formats
     */

    /**
     * MMYY date format
     */
    public static final String FORMAT_MMYY = "MMyy";

    /**
     * YYMM date format
     */
    public static final String FORMAT_YYMM = "yyMM";

    /**
     * MM/YY date format
     */
    public static final String FORMAT_MM_SLASH_YY = "MM/yy";

    /**
     * month - number within 1-12
     */
    private int month;

    /**
     * year - minimum 1979
     */
    private int year;

    /**
     * Construct the CardDate object with the given month and year values.
     *
     * @param month -
     *              the month in 1-12
     * @param year  -
     *              the year (eg 2004), but not less than 1970
     */
    public CardDate(int month, int year) {
        setMonth(month);
        setYear(year);
    }

    /**
     * Construct the CardDate object from a 'MM/YY' string.
     *
     * @param dateStr -
     *                the string in 'MM/YY' format.
     */
    public CardDate(String dateStr) {
        this(dateStr, FORMAT_MM_SLASH_YY);
    }

    /**
     * Construct the CardDate object from a string of known format.
     *
     * @param dateStr -
     *                the string representing the card date.
     * @param format  -
     *                the format of the string
     */
    public CardDate(String dateStr, String format) {

        DateFormat df = new SimpleDateFormat(format);

        try {
            df.parse(dateStr);
            Calendar cal = df.getCalendar();
            month = cal.get(Calendar.MONTH) + 1;
            if (format.equals(FORMAT_MM_SLASH_YY)) {
                year = cal.get(Calendar.YEAR) + 100;
            }
            else {
                year = cal.get(Calendar.YEAR);
            }
        } catch (ParseException e) {
            throw new RuntimeException("Cannot parse date: '" + dateStr + "' to format '" + format + "'.");
        }
    }

    /**
     * Construct the CardDate object from a date defined as parameter.
     *
     * @param date card date
     */
    public CardDate(Date date) {
        Calendar cal = Calendar.getInstance(TimeZone.getTimeZone("GMT"));
        cal.setTime(date);
        setMonth(cal.get(Calendar.MONTH) + 1);
        setYear(cal.get(Calendar.YEAR));
    }

    /**
     * Provides string representation of object
     *
     * @return string representation of object
     */
    public String toString() {
        return toString(FORMAT_MM_SLASH_YY);
    }

    /**
     * Provides string representation of object in specified format
     *
     * @param format the format of the date
     * @return string representation of object in specified format
     */
    public String toString(String format) {

        DateFormat df = new SimpleDateFormat(format);

        Calendar cal = df.getCalendar();
        cal.set(Calendar.DAY_OF_MONTH, 1);
        cal.set(Calendar.MONTH, month - 1);
        cal.set(Calendar.YEAR, year);

        return df.format(cal.getTime());
    }

    /**
     * Gets month of card date
     *
     * @return Returns the month.
     */
    public int getMonth() {
        return month;
    }

    /**
     * Sets month of card date
     *
     * @param month The month to set.
     */
    private void setMonth(int month) {
        if (month < 1 || month > 12) {
            throw new IllegalArgumentException("Month should be in 1-12, but it is " + month);
        }
        this.month = month;
    }

    /**
     * Gets year of card date
     *
     * @return Returns the year.
     */
    public int getYear() {
        return year;
    }

    /**
     * Sets year of card date
     *
     * @param year The year to set.
     */
    private void setYear(int year) {
        if (year < 1970) {
            throw new IllegalArgumentException("Year should be not less than 1970, got " + year);
        }
        this.year = year;
    }

    /**
     * Checks if card date of the object is greater then specified in parameter
     * card date
     *
     * @param cd card date
     * @return true if card date of the object is greater then specified in
     *         parameter card date and false otherwise
     */
    public boolean after(CardDate cd) {
        return (year > cd.year) || ((year == cd.year) && (month > cd.month));
    }

    /**
     * Checks if card date of the object is less then specified in parameter
     * card date
     *
     * @param cd card date
     * @return true if card date of the object is less then specified in
     *         parameter card date and false otherwise
     */
    public boolean before(CardDate cd) {
        return (year < cd.year) || ((year == cd.year) && (month < cd.month));
    }

    /**
     * Equals card date object with specified as the parameter
     *
     * @param o object to check with
     * @return true if specified object is equal to card date object and false
     *         otherwise
     */
    public boolean equals(Object o) {
        if (this == o)
            return true;

        if (o instanceof CardDate) {
            CardDate cd = (CardDate) o;
            return (this.year == cd.year) && (this.month == cd.month);
        }

        return false;
    }

    /**
     * Returns hash code of the object
     *
     * @return hash code of the object
     */
    public int hashCode() {
        return (year << 3) | month;
    }

    /**
     * Clones the object
     *
     * @return cloned object
     */
    public Object clone() {
        try {
            return super.clone();
        } catch (CloneNotSupportedException e) {
            // could never happen
            return null;
        }
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
