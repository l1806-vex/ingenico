package com.ingenico.payment;

import java.util.Calendar;
import java.util.TimeZone;

import junit.framework.TestCase;

/**
 * This class represents unit testing
 *
 * @author Eugene Pestov
 */
public class CardDateTest extends TestCase {

    public static void main(String[] args) {
        junit.textui.TestRunner.run(CardDateTest.class);
    }

    public void testHashCode() {

        CardDate cd1 = new CardDate(6, 2005);
        CardDate cd2 = new CardDate("06/05");
        
        assertEquals(cd1.hashCode(), cd2.hashCode());
    }

    /*
     * Class under test for void CardDate(String, String)
     */
    public void testCardDateStringString() {

        CardDate etalon = new CardDate(6, 2005);
        CardDate cd = new CardDate("06/05");
        
        assertEquals(etalon.getMonth(), cd.getMonth());
        assertEquals(etalon.getYear(), cd.getYear());

        cd = new CardDate("0605", CardDate.FORMAT_MMYY);
        
        assertEquals(etalon.getMonth(), cd.getMonth());
        assertEquals(etalon.getYear(), cd.getYear());

        cd = new CardDate("0506", CardDate.FORMAT_YYMM);
        
        assertEquals(etalon.getMonth(), cd.getMonth());
        assertEquals(etalon.getYear(), cd.getYear());
    }

    /*
     * Class under test for void CardDate(Date)
     */
    public void testCardDateDate() {

        CardDate etalon = new CardDate(6, 2005);
        
        Calendar cal = Calendar.getInstance(TimeZone.getTimeZone("GMT"));
        cal.set(Calendar.DAY_OF_MONTH, 1);
        cal.set(Calendar.MONTH, 5);
        cal.set(Calendar.YEAR, 2005);
        
        CardDate cd = new CardDate(cal.getTime());
        
        assertEquals(etalon.getMonth(), cd.getMonth());
        assertEquals(etalon.getYear(), cd.getYear());
    }

    /*
     * Class under test for String toString(String)
     */
    public void testToStringString() {
        
        CardDate cd = new CardDate(6, 2005);
        
        assertEquals("06/05", cd.toString());
        assertEquals("0605", cd.toString(CardDate.FORMAT_MMYY));
        assertEquals("0506", cd.toString(CardDate.FORMAT_YYMM));
    }

    public void testAfter() {
        
        CardDate before1 = new CardDate(6, 2003);
        CardDate before2 = new CardDate(4, 2004);
        CardDate after1 = new CardDate(6, 2005);
        CardDate after2 = new CardDate(7, 2004);
        
        CardDate cd = new CardDate(6, 2004);
        
        assertTrue(after1.after(cd));
        assertTrue(after2.after(cd));
        
        assertFalse(cd.after(cd));
        assertFalse(before1.after(cd));
        assertFalse(before2.after(cd));
    }

    public void testBefore() {

        CardDate before1 = new CardDate(6, 2003);
        CardDate before2 = new CardDate(4, 2004);
        CardDate after1 = new CardDate(6, 2005);
        CardDate after2 = new CardDate(7, 2004);
        
        CardDate cd = new CardDate(6, 2004);
        
        assertTrue(before1.before(cd));
        assertTrue(before2.before(cd));
        
        assertFalse(cd.before(cd));
        assertFalse(after1.before(cd));
        assertFalse(after2.before(cd));
    }

    /*
     * Class under test for boolean equals(Object)
     */
    public void testEqualsObject() {
        
        CardDate cd1 = new CardDate(6, 2003);
        CardDate cd2 = new CardDate(8, 2004);
        CardDate cd3 = new CardDate(6, 2003);
        
        assertTrue(cd1.equals(cd1));
        assertTrue(cd1.equals(cd3));
        assertFalse(cd1.equals(cd2));
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
