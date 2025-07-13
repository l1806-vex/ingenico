DROP TABLE IF EXISTS CFGSRV_TERMINAL_CONFIG;
CREATE TABLE CFGSRV_TERMINAL_CONFIG
(
    ID                 BIGINT                NOT NULL  IDENTITY PRIMARY KEY, 
    TYPE               VARCHAR(1)            NOT NULL DEFAULT '',
    SEQUENCE_ID        BIGINT                NOT NULL DEFAULT 0,
    VERSION            BIGINT                NULL,
    NAME               VARCHAR(100)          NULL,
    DESCRIPTION        VARCHAR(100)          NULL,
    LASTMODIFIED       BIGINT                NOT NULL,
    TMSTAMP            TIMESTAMP             NOT NULL,
    IS_DEFAULT         CHAR(1)               NOT NULL DEFAULT '0'
);
GRANT ALL ON CFGSRV_TERMINAL_CONFIG TO oe;
CREATE UNIQUE INDEX cfgsrv_config_idx ON CFGSRV_TERMINAL_CONFIG(TYPE, SEQUENCE_ID, VERSION);

DROP TABLE IF EXISTS CFGSRV_KEY_VALUE_PAIRS;
CREATE TABLE CFGSRV_KEY_VALUE_PAIRS
(
    ID                 BIGINT                NOT NULL  IDENTITY PRIMARY KEY, 
    TERMINAL_CONFIG_ID BIGINT                NOT NULL,
    KEY_               VARCHAR(80)           NOT NULL,
    VALUE              VARCHAR(80)           NOT NULL,
    ARRAY_INDEX        INT                   NOT NULL,
    foreign key  (TERMINAL_CONFIG_ID)
       references CFGSRV_TERMINAL_CONFIG (ID)
);
GRANT ALL ON CFGSRV_KEY_VALUE_PAIRS TO oe;

CREATE UNIQUE INDEX cfgsrv_kvp_idx ON CFGSRV_KEY_VALUE_PAIRS(TERMINAL_CONFIG_ID, KEY_);

DROP TABLE IF EXISTS CFGSRV_IINS;
CREATE TABLE CFGSRV_IINS
(
    ID                 BIGINT                NOT NULL  IDENTITY PRIMARY KEY, 
    TERMINAL_CONFIG_ID BIGINT                NOT NULL,
    KEY_               SMALLINT              NOT NULL,
    RANGE_MIN          VARCHAR(19)           NOT NULL,
    RANGE_MAX          VARCHAR(19)           NULL,
    RANGE_EXPIRY       VARCHAR(7)            NULL,
    ACTIVE             CHAR(1)               NOT NULL,
    TTL_PTR            SMALLINT              NOT NULL,
    CS_PTR             SMALLINT              NOT NULL,
    ARRAY_INDEX        INT                   NOT NULL,
    foreign key (TERMINAL_CONFIG_ID)
       references CFGSRV_TERMINAL_CONFIG (ID)
);
GRANT ALL ON CFGSRV_IINS TO oe;
CREATE UNIQUE INDEX cfgsrv_iin_idx ON CFGSRV_IINS(TERMINAL_CONFIG_ID, KEY_);

DROP TABLE IF EXISTS CFGSRV_TTLS;
CREATE TABLE CFGSRV_TTLS
(
    ID                 BIGINT                NOT NULL  IDENTITY PRIMARY KEY,
    TERMINAL_CONFIG_ID BIGINT                NOT NULL,
    KEY_               SMALLINT              NOT NULL,
    NAME               VARCHAR(30)           NOT NULL DEFAULT '',  -- Name of card e.g. Amex, not card holder
    PAN                VARCHAR(38)           NOT NULL,  -- PAN Range e.g. 011519 means PAN can be 1, 15 or 19 chars
    INL                TINYINT               NOT NULL,  -- Issue number length 0, 1 or 2
    INP                TINYINT               NOT NULL,  -- Issue number position - 0 if absent
    SCP                TINYINT               NOT NULL,  -- Service Code Position 0 if not specified, 99 reserved for amex
    SDP                TINYINT               NOT NULL,  -- Start Date Position
    SDF                CHAR(1)               NOT NULL,  -- Start date format 'N' or 'C'
    EDP                TINYINT               NOT NULL,  -- Expiry Date Position
    LCR                TINYINT               NOT NULL,  -- Luhn Check required '0', '1' or '2'
    EDF                CHAR(1)               NOT NULL,  -- Expiry date format 'N' or 'R'
    LCP                TINYINT               NOT NULL,  -- Language Code Position
    CTP                TINYINT               NOT NULL,  -- Card Type Position
    CSNP               TINYINT               NOT NULL,  -- Card Sequence Number Position
    AAP                TINYINT               NOT NULL,  -- Auth Amount Position
    PWIDP              TINYINT               NOT NULL,  -- Pin Verification Value Id
    PWP                TINYINT               NOT NULL,  -- Pin Verification Value 0, 4 or 5
    PWL                TINYINT               NOT NULL,  -- Pin Verification Value Length
    CWP                TINYINT               NOT NULL,  -- Card Verification Value Position
    CAVP               TINYINT               NOT NULL,  -- Card Authentication Value Position
    T2CDP              TINYINT               NOT NULL,  -- Track 2 CCD position
    DDP                TINYINT               NOT NULL,  -- Discretionary Data position
    DDL                TINYINT               NOT NULL,  -- Discretionary Data length
    ARRAY_INDEX        INT                   NOT NULL,
    foreign key  (TERMINAL_CONFIG_ID)
       references CFGSRV_TERMINAL_CONFIG (ID)
);
GRANT ALL ON CFGSRV_TTLS TO oe;

CREATE UNIQUE INDEX cfgsrv_ttls_idx ON CFGSRV_TTLS(TERMINAL_CONFIG_ID, KEY_);


DROP TABLE IF EXISTS CFGSRV_CARD_SCHEMES;
CREATE TABLE CFGSRV_CARD_SCHEMES
(
    ID                 BIGINT                NOT NULL  IDENTITY PRIMARY KEY, 
    TERMINAL_CONFIG_ID BIGINT                NOT NULL,
    KEY_               SMALLINT              NOT NULL,
    ACTIVE             CHAR(1)               NOT NULL,
    NAME               VARCHAR(16)           NOT NULL,
    FLOOR_LIMIT        INT                   NOT NULL,
    KEY_ALLOWED        CHAR(1)               NOT NULL,
    ARRAY_INDEX        SMALLINT              NOT NULL,
    foreign key  (TERMINAL_CONFIG_ID)
       references CFGSRV_TERMINAL_CONFIG (ID)
);
GRANT ALL ON CFGSRV_CARD_SCHEMES TO oe;
CREATE UNIQUE INDEX cfgsrv_card_sch_idx ON CFGSRV_CARD_SCHEMES(TERMINAL_CONFIG_ID, KEY_);

DROP TABLE IF EXISTS CFGSRV_CARD_PROVIDERS;
CREATE TABLE CFGSRV_CARD_PROVIDERS
(
    ID                 BIGINT                NOT NULL  IDENTITY PRIMARY KEY, 
    TERMINAL_CONFIG_ID BIGINT                NOT NULL,
    KEY_               SMALLINT              NOT NULL,
    NAME               VARCHAR(30)           NOT NULL ,
    FLOOR_LIMIT        INT                   NOT NULL,
    THRESHOLD          INT                   NOT NULL,
    TAC_DENIAL         VARCHAR(10)           NULL,
    TAC_ONLINE         VARCHAR(10)           NULL,
    TAC_DEFAULT        VARCHAR(10)           NULL,
    DEFAULT_TDOL       VARCHAR(504)          NULL,
    DEFAULT_DDOL       VARCHAR(504)          NOT NULL,
    TARGET_PERCENTAGE  TINYINT               NOT NULL,
    MAXIMUM_TARGET_PERCENTAGE
                       TINYINT               NOT NULL,
    TERMINAL_COUNTRY_CODE
                       SMALLINT              NOT NULL,
    TXN_CURRENCY_CODE  SMALLINT              NOT NULL,
    ACQUIRER_ID			VARCHAR(12)	NOT NULL,
    MERCHANT_CATEGORY_CODE	VARCHAR(4)	NOT NULL,
    TRANS_CUR_EXP			VARCHAR(4)	NOT NULL,
    TRANS_REF_CUR			VARCHAR(4)	NOT NULL,
    TRANS_REF_CUR_EXP		VARCHAR(2)	NOT NULL,
    MERCHANT_ID			VARCHAR(15)	NOT NULL,
    ARRAY_INDEX        INT                   NOT NULL,
    foreign key  (TERMINAL_CONFIG_ID)
       references CFGSRV_TERMINAL_CONFIG (ID)
);
GRANT ALL ON CFGSRV_CARD_PROVIDERS TO oe;
CREATE UNIQUE INDEX cfgsrv_acrd_prov_idx ON CFGSRV_CARD_PROVIDERS(TERMINAL_CONFIG_ID, KEY_);

DROP TABLE IF EXISTS CFGSRV_EMV_CARD_APPLICATIONS;
CREATE TABLE CFGSRV_EMV_CARD_APPLICATIONS
(
    ID                 BIGINT                NOT NULL  IDENTITY PRIMARY KEY, 
    TERMINAL_CONFIG_ID BIGINT                NOT NULL,
    KEY_               SMALLINT              NOT NULL,
    CARD_APP_LIVE_FLAG CHAR(1)               NOT NULL,
    CARD_PROVIDER_KEY  SMALLINT              NOT NULL,
    AID                VARCHAR(32)           NOT NULL,
    TRMD               VARCHAR(16)           NOT NULL,
    PRIORITY_INDEX     TINYINT               NOT NULL,
    SELECTION_APPLI_FLAG
                       CHAR(1)               NOT NULL,
    APPLICATION_VERSION    
                       SMALLINT              NOT NULL DEFAULT 0,
    TERMINAL_CAPABILITIES		VARCHAR(8)	NOT NULL,
    ADD_TERMINAL_CAPABILITIES	VARCHAR(8)	NOT NULL,
    TERMINAL_TYPE			VARCHAR(2)	NOT NULL,
    ARRAY_INDEX        INT                   NOT NULL,
    foreign key  (TERMINAL_CONFIG_ID)
       references CFGSRV_TERMINAL_CONFIG (ID)
);
GRANT ALL ON CFGSRV_EMV_CARD_APPLICATIONS TO oe;
CREATE UNIQUE INDEX cfgsrv_emv_card_app_idx ON CFGSRV_EMV_CARD_APPLICATIONS(TERMINAL_CONFIG_ID, KEY_);

DROP TABLE IF EXISTS CFGSRV_RSA_KEYS;
CREATE TABLE CFGSRV_RSA_KEYS
(
    ID                 BIGINT                NOT NULL  IDENTITY PRIMARY KEY, 
    TERMINAL_CONFIG_ID BIGINT                NOT NULL,
    KEY_               SMALLINT              NOT NULL,
    KEY_INDICATOR      TINYINT               NOT NULL,
    RID                VARCHAR(10)        NOT NULL,
    KEY_DATA           TEXT   NOT NULL,
    EXPONENT           VARCHAR(64)    NOT NULL,
    ARRAY_INDEX        INT                   NOT NULL,
    HASH               VARCHAR(28)           NOT NULL,
    foreign key  (TERMINAL_CONFIG_ID)
       references CFGSRV_TERMINAL_CONFIG (ID)
);
GRANT ALL ON CFGSRV_RSA_KEYS TO oe;
CREATE UNIQUE INDEX cfgsrv_rsa_key_idx ON CFGSRV_RSA_KEYS(TERMINAL_CONFIG_ID, KEY_);
 
DROP TABLE IF EXISTS CFGSRV_RISK_MAN_VERDICT;
CREATE TABLE CFGSRV_RISK_MAN_VERDICT
(
    ID                 BIGINT                NOT NULL  IDENTITY PRIMARY KEY, 
    TERMINAL_CONFIG_ID BIGINT                NOT NULL,
    KEY_               SMALLINT              NOT NULL,
    CHECK_RISK         VARCHAR(20)           NOT NULL,
    VERDICT            VARCHAR(10)           NOT NULL,
    ARRAY_INDEX        INT                   NOT NULL,
    foreign key  (TERMINAL_CONFIG_ID)
       references CFGSRV_TERMINAL_CONFIG (ID)
);
GRANT ALL ON CFGSRV_RISK_MAN_VERDICT TO oe;
CREATE UNIQUE INDEX cfgsrv_ridk_man_idx ON CFGSRV_RISK_MAN_VERDICT(TERMINAL_CONFIG_ID, KEY_);
 
DROP TABLE IF EXISTS CFGSRV_HOT_CARD;
CREATE TABLE CFGSRV_HOT_CARD
(
    ID                 BIGINT                NOT NULL  IDENTITY PRIMARY KEY, 
    TERMINAL_CONFIG_ID BIGINT                NOT NULL,
    KEY_               SMALLINT              NOT NULL,
    OPERATION          VARCHAR(10)           NOT NULL,
    PAN                VARCHAR(19)           NOT NULL,
    ARRAY_INDEX        INT                   NOT NULL,
    foreign key  (TERMINAL_CONFIG_ID)
       references CFGSRV_TERMINAL_CONFIG (ID)
);
GRANT ALL ON CFGSRV_HOT_CARD TO oe;
CREATE UNIQUE INDEX cfgsrv_hot_card_idx ON CFGSRV_HOT_CARD(TERMINAL_CONFIG_ID, KEY_);
 
DROP TABLE IF EXISTS CFGSRV_HOT_CARD_CONFIG;
CREATE TABLE CFGSRV_HOT_CARD_CONFIG
(
    ID                 BIGINT                NOT NULL  IDENTITY PRIMARY KEY, 
    TERMINAL_CONFIG_ID BIGINT                NOT NULL,
    CLEAR              CHAR(1)               NOT NULL,
    foreign key  (TERMINAL_CONFIG_ID)
       references CFGSRV_TERMINAL_CONFIG (ID)
);
GRANT ALL ON CFGSRV_HOT_CARD_CONFIG TO oe;
CREATE UNIQUE INDEX cfgsrv_hot_card_cfg_idx ON CFGSRV_HOT_CARD_CONFIG(TERMINAL_CONFIG_ID);

 
DROP TABLE IF EXISTS CFGSRV_VARDCL;
CREATE TABLE CFGSRV_VARDCL
(
    ID                 BIGINT                NOT NULL  IDENTITY PRIMARY KEY, 
    TERMINAL_CONFIG_ID BIGINT                NOT NULL,
    KEY_               SMALLINT              NOT NULL,
    NAME               VARCHAR(50)           NOT NULL,
    TYPE               VARCHAR(10)           NULL,
    VOLATILE           CHAR(1)               NULL,
    VALUE              TEXT		     NOT NULL,
    PERMS              VARCHAR(20)           NULL,
    FORMAT             VARCHAR(20)           NULL,
    ARRAY_INDEX        INT                   NOT NULL,
    foreign key  (TERMINAL_CONFIG_ID)
       references CFGSRV_TERMINAL_CONFIG (ID)
);
GRANT ALL ON CFGSRV_VARDCL TO oe;
CREATE UNIQUE INDEX cfgsrv_vardcl_idx ON CFGSRV_VARDCL(TERMINAL_CONFIG_ID, KEY_);

DROP TABLE IF EXISTS CFGSRV_SETVAR;
CREATE TABLE CFGSRV_SETVAR
(
    ID                 BIGINT                NOT NULL  IDENTITY PRIMARY KEY, 
    TERMINAL_CONFIG_ID BIGINT                NOT NULL,
    KEY_               SMALLINT              NOT NULL,
    NAME               VARCHAR(50)           NOT NULL,
    VALUE              TEXT      	     NOT NULL,
    FORMAT             VARCHAR(20)           NULL,
    ARRAY_INDEX        INT                   NOT NULL,
    foreign key  (TERMINAL_CONFIG_ID)
       references CFGSRV_TERMINAL_CONFIG (ID)
);
GRANT ALL ON CFGSRV_SETVAR TO oe;
CREATE UNIQUE INDEX cfgsrv_setvar_idx ON CFGSRV_SETVAR(TERMINAL_CONFIG_ID, KEY_);

DROP TABLE IF EXISTS CFGSRV_CFG_ASSIGN;
CREATE TABLE CFGSRV_CFG_ASSIGN
(
   ID              BIGINT NOT NULL IDENTITY PRIMARY KEY,
   REFERENCE       CHAR(20) NOT NULL,   -- THIS WILL BE THE TERMINAL ITID FOR TERMINALS AND 
                                        -- GROUP SYMBOLIC ID FOR OTHER TYPES
   ASSIGN_TYPE     CHAR(1) NOT NULL,    -- 'T' TERMINAL, 'B' BANK ETC ( ONLY TYPE 'T' WILL BE 
                                        -- USED FOR DETERMINING 
   ASSIGN_LEVEL    CHAR(1) NOT NULL,    -- 'T' TERMINAL, 'B' BANK ETC - DEFINES 'HOW' THE ASSIGNMENT
                                        -- WAS MADE 
   CONFIG_TYPE     CHAR(1) NOT NULL,    -- 'M' MAGCARD ETC - WILL BE 4 ENTRIES FOR EACH 
                                        -- TERMINAL    
   CONFIG_ID       BIGINT NOT NULL,     -- THE KEY TO CFGSRV_TERMINAL_CONFIG  
   STATUS          CHAR(1),             -- 'U' UNDELIVERED,   'D' DELIVERED    
   ASSIGNMENT_DATE DATETIME NOT NULL   -- DATE THE ASSIGNMENT WAS CREATED
) ;
GRANT ALL ON CFGSRV_CFG_ASSIGN TO oe;

DROP TABLE IF EXISTS CFGSRV_CFG_ASSIGN_ARCHIVE;
CREATE TABLE CFGSRV_CFG_ASSIGN_ARCHIVE 
(
   ID              BIGINT NOT NULL  IDENTITY PRIMARY KEY, 
   REFERENCE       CHAR(20) NOT NULL,   -- THIS WILL BE THE TERMINAL ITID FOR TERMINALS AND 
                                        -- GROUP SYMBOLIC ID FOR OTHER TYPES
   CONFIG_TYPE     CHAR(1) NOT NULL,    -- 'M' MAGCARD ETC - WILL BE 4 ENTRIES FOR EACH 
                                        -- TERMINAL    
   ASSIGN_TYPE     CHAR(1) NOT NULL,    -- 'T' TERMINAL, 'B' BANK ETC ( ONLY TYPE 'T' WILL BE 
                                        -- USED FOR DETERMINING TERMINAL CONFIG)
   ASSIGN_LEVEL    CHAR(1) NOT NULL,    -- 'T' TERMINAL, 'B' BANK ETC - DEFINES 'HOW' THE ASSIGNMENT
                                        -- WAS MADE 
   CONFIG_ID       BIGINT NOT NULL,     -- THE KEY TO CFGSRV_TERMINAL_CONFIG  
   STATUS          CHAR(1),             -- 'U' UNDELIVERED,   'D' DELIVERED    
   START_DATE      DATETIME NOT NULL,   -- DATE THE ASSIGNMENT WAS CREATED
   END_DATE        DATETIME NOT NULL   -- DATE THE ASSIGNMENT WAS REMOVED
) ;
GRANT ALL ON CFGSRV_CFG_ASSIGN_ARCHIVE TO oe;

DROP TABLE IF EXISTS CFGSRV_SERVICE_PROFILE_ASSIGN;
CREATE TABLE CFGSRV_SERVICE_PROFILE_ASSIGN (
  ID BIGINT NOT NULL IDENTITY PRIMARY KEY,
  PROFILE VARCHAR(255) NOT NULL COMMENT 'key to CFG_PROFILE.',
  SERVICE VARCHAR(255) NOT NULL,
  ASSIGNMENT_DATE DATE NOT NULL,
  IS_DEFAULT BOOLEAN NOT NULL DEFAULT FALSE,
);

GRANT ALL ON CFGSRV_SERVICE_PROFILE_ASSIGN TO oe;

/*****************************************************************************
*
* COPYRIGHT (C) 2004-2008 Ingenico SA
* ALL RIGHTS RESERVED
*
* Copyright in the whole and every part of this software program belongs to
* Ingenico SA.  It may not be used, sold, licensed, transferred, copied
* or reproduced in whole or in part in any manner or form other than in
* accordance with and subject to the terms of a licence from Ingenico SA
* or with the prior written consent of Ingenico SA or as
* permitted by applicable law.
* This software program contains confidential and proprietary information and
* must not be disclosed, in whole or in part, to any person or organisation
* without the prior written consent of Ingenico SA.
* Any copies or reproductions of this software program (in whole or in part)
* made by any method must also include a copy of this legend.

*****************************************************************************/
