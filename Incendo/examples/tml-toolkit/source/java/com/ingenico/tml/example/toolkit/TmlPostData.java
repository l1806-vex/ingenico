package com.ingenico.tml.example.toolkit;

import java.util.Date;
import java.util.HashMap;
import java.util.Map;

/**
 * The base class for tmlpost data classes
 * 
 * @author Eugene Pestov
 */
public abstract class TmlPostData {

    /**
     * ingenico terminal id
     */
    private String itid;

    /**
     * post date
     */
    private Date date;

    /**
     * post id
     */
    private String postId;
    
    /**
     * Gets post date
     * @return post date
     */
    public Date getDate() {
        return date;
    }

    /**
     * Gets ingenico terminal id
     * @return ingenico terminal id
     */
    public String getItid() {
        return itid;
    }

    /**
     * Sets post date
     * @param date post date
     */
    public void setDate(Date date) {
        this.date = date;
    }

    /**
     * Sets ingenico terminal id
     * @param string ingenico terminal id
     */
    public void setItid(String string) {
        itid = string;
    }

    /**
     * Gets post id
     * @return post id
     */
    public String getPostId() {
        return postId;
    }

    /**
     * Sets post id
     * @param string post id
     */
    public void setPostId(String string) {
        postId = string;
    }

    /**
     * Validates tml post data
     * @throws ValidationException in case of validation failed
     */
    public void validate() throws ValidationException {
    }

    /**
     * Gets field mapping
     * @return field mapping
     */
    public abstract Map<String, String> getFieldMappings();
    
    private HashMap<String, Object> fields;
    public Map<String, Object> getFields() {
        return fields;
    };

    public void setField(String name, String value) {
        intSetField(name, value);
    }
    public void setField(String name, int value) {
        intSetField(name, value);
    }
    public void setField(String name, boolean value) {
        intSetField(name, value);
    }    
    private void intSetField(String name, Object value) {
        if (fields == null)
            fields = new HashMap<String, Object>();
        fields.put(name, value);
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