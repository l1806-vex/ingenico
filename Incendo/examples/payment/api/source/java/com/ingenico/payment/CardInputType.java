package com.ingenico.payment;

/**
 * This class represents bean for card input type (method that card data was
 * entered: magnetic, icc emv or keyed)
 *
 * @author Eugene Pestov
 */
public final class CardInputType {

    /**
     * magnetic input type
     */
    public static final CardInputType MAGNETIC = new CardInputType("Magnetic swipe");

    /**
     * ICC EMV input type
     */
    public static final CardInputType ICC = new CardInputType("ICC");

    /**
     * card data is keyed
     */
    public static final CardInputType KEYED = new CardInputType("Keyed");

    /**
     * card input type
     */
    private String name;

    /**
     * Default constructor
     *
     * @param name card input type
     */
    private CardInputType(String name) {
        this.name = name;
    }

    /**
     * Gets card input type
     *
     * @return card input type
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
