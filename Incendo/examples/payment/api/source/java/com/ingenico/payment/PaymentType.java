package com.ingenico.payment;

/**
 * This class represents bean for payment types
 *
 * @author Eugene Pestov
 */
public final class PaymentType {

    /**
     * sequence
     */
    private static int idSeq = 0;

    /**
     * refund transaction
     */
    public static final PaymentType REFUND = new PaymentType("REFUND");

    /**
     * reversal transaction
     */
    public static final PaymentType REVERSAL = new PaymentType("REVERSAL");

    /**
     * sale transaction
     */
    public static final PaymentType SALE = new PaymentType("SALE");

    /**
     * sale with cashback transaction
     */
    public static final PaymentType SALE_WITH_CASHBACK =
            new PaymentType("SALE WITH CASHBACK");

    /**
     * sequense id
     */
    private int id;

    /**
     * payment name
     */
    private String name;

    /**
     * Default constructor
     *
     * @param name payment name
     */
    private PaymentType(String name) {
        this.id = idSeq++;
        this.name = name;
    }

    /**
     * Equals payment type
     *
     * @param obj payment type
     * @return true if specified payment type is equal to this false otherwise
     */
    public boolean equals(Object obj) {
        return (obj instanceof PaymentType)
                && (((PaymentType) obj).id == this.id);
    }

    /**
     * Gets hash code
     *
     * @return hash code
     */
    public int hashCode() {
        return id;
    }

    /**
     * Gets string representation of the object
     *
     * @return string representation of the object
     */
    public String toString() {
        return name;
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
