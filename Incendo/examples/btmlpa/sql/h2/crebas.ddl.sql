/*==============================================================*/
/* Table: BTMLPA_TERMINAL                                       */
/*==============================================================*/
--DROP TABLE IF EXISTS BTMLPA_TERMINAL CASCADE;
CREATE TABLE BTMLPA_TERMINAL (
  ID            BIGINT          NOT NULL IDENTITY PRIMARY KEY,--SERIAL with explicit SEQUENCE
  OE_ITID       VARCHAR(20)     NOT NULL,
  APACS_TID     VARCHAR(20)     NOT NULL,
  TRACED        VARCHAR(1)      NOT NULL DEFAULT 'N'
);
GRANT ALL ON BTMLPA_TERMINAL TO btmlpa;

/*==============================================================*/
/* Table: BTMLPA_TERMINAL                                       */
/*==============================================================*/
--DROP TABLE IF EXISTS BTMLPA_TXN CASCADE;
CREATE TABLE BTMLPA_TXN (
  ID                    BIGINT          NOT NULL IDENTITY PRIMARY KEY,--SERIAL with explicit SEQUENCE
  TERMINAL_POST_ID      BIGINT          NOT NULL,
  TERMINAL_TXN_ID       BIGINT,
  TYPE                  INT,
  TERMINAL_ID           BIGINT          NOT NULL,
  TERM_TXN_DATE         TIMESTAMP,
  POST_TXN_DATE         TIMESTAMP       NOT NULL,
  TXN_STARTED           TIMESTAMP,
  TXN_DURATION          BIGINT,
  ACQR_STARTED          TIMESTAMP,
  ACQR_DURATION         BIGINT,
  STATE                 INT,
  PAN                   VARCHAR(20),
  STARTDATE             CHAR(5),
  EXPIRYDATE            CHAR(5),
  INPUTMETHOD           VARCHAR(20),
  CARDHOLDERNAME        VARCHAR(50),
  ISSUENUMBER           INT,
  ISO2TRACK             VARCHAR(40),
  ICC_APP               VARCHAR(32),
  ICC_AIP               INT,
  ICC_ATC               INT,
  ICC_ARQC              BYTEA,--8
  ICC_IAD               BYTEA,--32
  ICC_TVR               BYTEA,--5
  ICC_UNUMBER           INT,
  ICC_ARPC              BYTEA,--8
  ICC_ISSUER_AUTH       BYTEA,--16
  ICC_ISSUER_SCRIPT     BYTEA,--128
  FAIL_REASON           VARCHAR(50),
  MESSAGE               VARCHAR(80),
  AUTH_CODE             VARCHAR(20),
  AMOUNT                BIGINT,
  AMOUNT_OTHER          BIGINT,
  CURRENCY_CODE         CHAR(3),       
  TXNMODE               VARCHAR(10),
   FOREIGN KEY  (TERMINAL_ID)
       REFERENCES BTMLPA_TERMINAL(id)

);
GRANT ALL ON BTMLPA_TXN TO btmlpa;

/*==============================================================*/
/* Table: WEB_SRV                                               */
/*==============================================================*/
--DROP TABLE IF EXISTS WEB_SRV CASCADE;
CREATE TABLE WEB_SRV (
  ID            INT             NOT NULL IDENTITY PRIMARY KEY,
  SRV_NAME      VARCHAR(20)     NOT NULL,
  SRV_DESCR     VARCHAR(255)    NOT NULL,
  PAGE          INT             NOT NULL DEFAULT 10
);
GRANT ALL ON WEB_SRV TO btmlpa;

/*==============================================================*/
/* Table: WEB_SRVFIELD                                          */
/*==============================================================*/
--DROP TABLE IF EXISTS WEB_SRVFIELD CASCADE;
CREATE TABLE WEB_SRVFIELD (
  SRV_ID        INT             NOT NULL,
  FIELD_ID      INT             NOT NULL,
  FIELD_NAME    VARCHAR(255)    NOT NULL,
  FIELD_DESCR   VARCHAR(255)    NOT NULL,
  CHECKED       CHAR(1)         NOT NULL DEFAULT 'N',
   FOREIGN KEY  (SRV_ID)
       REFERENCES WEB_SRV(ID)
);
GRANT ALL ON WEB_SRVFIELD TO btmlpa;

CREATE UNIQUE INDEX WEB_SRVFIELD_IDX ON WEB_SRVFIELD(SRV_ID, FIELD_ID);

/*==============================================================*/
/* Table: WEB_USERS                                             */
/*==============================================================*/
--DROP TABLE IF EXISTS WEB_USERS CASCADE;
CREATE TABLE WEB_USERS (
  ID            INT             NOT NULL IDENTITY PRIMARY KEY,--SERIAL with explicit SEQUENCE
  NAME          VARCHAR(255)    NOT NULL,
  LOGIN         VARCHAR(10)     NOT NULL,
  PASSWD        VARCHAR(10)     NOT NULL
);

GRANT ALL ON WEB_USERS TO btmlpa;

/*==============================================================*/
/* Table: WEB_GROUPS                                            */
/*==============================================================*/
--DROP TABLE IF EXISTS WEB_GROUPS CASCADE;
CREATE TABLE WEB_GROUPS (
  ID    INT             NOT NULL IDENTITY PRIMARY KEY,--SERIAL with explicit SEQUENCE
  NAME  VARCHAR(20)        NOT NULL,
  DESCR VARCHAR(255)       NOT NULL
);
GRANT ALL ON WEB_GROUPS TO btmlpa;

/*==============================================================*/
/* Table: WEB_USER_GROUP                                        */
/*==============================================================*/
--DROP TABLE IF EXISTS WEB_USER_GROUP CASCADE;
CREATE TABLE WEB_USER_GROUP (
  ID            INT     NOT NULL IDENTITY PRIMARY KEY,--SERIAL with explicit SEQUENCE
  USER_ID       INT     NOT NULL,
  GROUP_ID      INT     NOT NULL,
   FOREIGN KEY  (USER_ID)
       REFERENCES WEB_USERS(ID),
   FOREIGN KEY  (GROUP_ID)
       REFERENCES WEB_GROUPS(ID)
);

GRANT ALL ON WEB_USER_GROUP TO btmlpa;

/*==============================================================*/
/* Table: WEB_SRV_USER                                          */
/*==============================================================*/
--DROP TABLE IF EXISTS WEB_SRV_USER CASCADE;
CREATE TABLE WEB_SRV_USER (
  ID            INT     NOT NULL IDENTITY PRIMARY KEY,
  SRV_ID        INT     NOT NULL,
  TYPE          INT     NOT NULL DEFAULT 1,
  USER_ID       INT     NOT NULL,

   FOREIGN KEY  (USER_ID)
       REFERENCES WEB_USERS(ID),
   FOREIGN KEY  (SRV_ID)
       REFERENCES WEB_SRV(ID)

);
GRANT ALL ON WEB_SRV_USER TO btmlpa;

--DROP SEQUENCE IF EXISTS WEB_SRV_USER_SEQ;
--CREATE SEQUENCE WEB_SRV_USER_SEQ
--        INCREMENT BY 1 START WITH 1 NO MAXVALUE
--        OWNED BY WEB_SRV_USER.ID;
--ALTER TABLE WEB_SRV_USER
--        ALTER COLUMN ID SET DEFAULT NEXTVAL('WEB_SRV_USER_SEQ');

/***************************************************************************** 
*
* COPYRIGHT (C) 2010 Ingenico
* ALL RIGHTS RESERVED
*
* Copyright in the whole and every part of this software program belongs to
* Ingenico.  It may not be used, sold, licensed, transferred, copied
* or reproduced in whole or in part in any manner or form other than in
* accordance with and subject to the terms of a licence from Ingenico
* or with the prior written consent of Ingenico or as
* permitted by applicable law.
* This software program contains confidential and proprietary information and
* must not be disclosed, in whole or in part, to any person or organisation
* without the prior written consent of Ingenico.
* Any copies or reproductions of this software program (in whole or in part)
* made by any method must also include a copy of this legend.

*****************************************************************************/