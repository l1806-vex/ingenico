package com.ingenico.trans.data;

/**
 * @author Sergey Lukashin
 */
public class Message implements Transaction {
    private int transactionId;
    private MessageRequest messageRequest;
    private MessageResponse messageResponse;

    /**
     * @param transactionId
     *            the transactionId to set
     */
    public void setTransactionId(int transactionId) {
        this.transactionId = transactionId;
    }

    /**
     * @return the transactionId
     */
    public int getTransactionId() {
        return transactionId;
    }

    /**
     * @param messageRequest
     *            the messageRequest to set
     */
    public void setMessageRequest(MessageRequest messageRequest) {
        this.messageRequest = messageRequest;
    }

    /**
     * @return the messageRequest
     */
    public MessageRequest getMessageRequest() {
        return messageRequest;
    }

    /**
     * @param messageResponse
     *            the messageResponse to set
     */
    public void setMessageResponse(MessageResponse messageResponse) {
        this.messageResponse = messageResponse;
    }

    /**
     * @return the messageResponse
     */
    public MessageResponse getMessageResponse() {
        return messageResponse;
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