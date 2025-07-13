package com.ingenico.trans.data;

import java.util.ArrayList;

/**
 * @author Sergey Lukashin
 */
public class MessageResponse {
    private ArrayList<Field> fields = new ArrayList<Field>();

    /**
     * @param f
     *            the field to add
     */
    public void addField(Field f) {
        fields.add(f);
    }

    /**
     * @return fields
     */
    public ArrayList<Field> getFields() {
        return fields;
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