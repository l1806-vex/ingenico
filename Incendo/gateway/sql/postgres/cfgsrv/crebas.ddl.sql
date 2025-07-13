/*==============================================================*/
/* Table: CFGSRV_TERMINAL_CONFIG                                */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_TERMINAL_CONFIG CASCADE;
CREATE TABLE CFGSRV_TERMINAL_CONFIG (
  ID            BIGINT          NOT NULL,--SERIAL with explicit SEQUENCE
  TYPE          VARCHAR(1)      NOT NULL DEFAULT '',
  SEQUENCE_ID   BIGINT          NOT NULL DEFAULT 0,
  VERSION       BIGINT,
  NAME          VARCHAR(100),
  DESCRIPTION   VARCHAR(100),
  LASTMODIFIED  BIGINT          NOT NULL,
  TMSTAMP       TIMESTAMP       NOT NULL,
  IS_DEFAULT    BOOLEAN         NOT NULL DEFAULT FALSE
);

DROP SEQUENCE IF EXISTS CFGSRV_CONFIG_SEQ;
CREATE SEQUENCE CFGSRV_CONFIG_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_TERMINAL_CONFIG.ID;
ALTER TABLE CFGSRV_TERMINAL_CONFIG
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_CONFIG_SEQ');

ALTER TABLE CFGSRV_TERMINAL_CONFIG
        ADD CONSTRAINT CFGSRV_TERMINAL_CONFIG_PK
                PRIMARY KEY (ID);

CREATE UNIQUE INDEX CFGSRV_TERMINAL_CONFIG_IDX ON 
        CFGSRV_TERMINAL_CONFIG(TYPE, SEQUENCE_ID, VERSION);
        
COMMENT ON COLUMN CFGSRV_TERMINAL_CONFIG.TYPE IS 'Configuration type - Varlib "V", MagCard "M", IccEmv "E", Hot List "H", Terminal appl "A".';
COMMENT ON COLUMN CFGSRV_TERMINAL_CONFIG.SEQUENCE_ID IS 'Configuration id.';
COMMENT ON COLUMN CFGSRV_TERMINAL_CONFIG.VERSION IS 'Configuration version.';
COMMENT ON COLUMN CFGSRV_TERMINAL_CONFIG.NAME IS 'Configuration name.';
COMMENT ON COLUMN CFGSRV_TERMINAL_CONFIG.DESCRIPTION IS 'Description of configuration.';
COMMENT ON COLUMN CFGSRV_TERMINAL_CONFIG.LASTMODIFIED IS 'Last time configuration was modified - number of milliseconds since January, 1, 1970, 00:00:00 GMT.';
COMMENT ON COLUMN CFGSRV_TERMINAL_CONFIG.TMSTAMP IS 'Date of configuration.';
COMMENT ON COLUMN CFGSRV_TERMINAL_CONFIG.IS_DEFAULT IS 'Indicates wether or not the configuration is default.';

/*==============================================================*/
/* Table: CFGSRV_KEY_VALUE_PAIRS                                */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_KEY_VALUE_PAIRS CASCADE;
CREATE TABLE CFGSRV_KEY_VALUE_PAIRS (
  ID                    BIGINT          NOT NULL,--SERIAL with explicit SEQUENCE
  TERMINAL_CONFIG_ID    BIGINT          NOT NULL,
  KEY_                  VARCHAR(80)     NOT NULL,
  VALUE                 VARCHAR(80)     NOT NULL,
  ARRAY_INDEX           INT             NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_KVP_SEQ;
CREATE SEQUENCE CFGSRV_KVP_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_KEY_VALUE_PAIRS.ID;
ALTER TABLE CFGSRV_KEY_VALUE_PAIRS
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_KVP_SEQ');

ALTER TABLE CFGSRV_KEY_VALUE_PAIRS
        ADD CONSTRAINT CFGSRV_KEY_VALUE_PAIRS_PK
                PRIMARY KEY (ID);
ALTER TABLE CFGSRV_KEY_VALUE_PAIRS
        ADD CONSTRAINT CFGSRV_KEY_VALUE_PAIRS_TERMINAL_CONFIG_FK
                FOREIGN KEY (TERMINAL_CONFIG_ID)
                REFERENCES CFGSRV_TERMINAL_CONFIG (ID);

CREATE UNIQUE INDEX CFGSRV_KEY_VALUE_PAIRS_IDX ON
        CFGSRV_KEY_VALUE_PAIRS(TERMINAL_CONFIG_ID, KEY_);
        
COMMENT ON COLUMN CFGSRV_KEY_VALUE_PAIRS.KEY_ IS 'Id.';
COMMENT ON COLUMN CFGSRV_KEY_VALUE_PAIRS.VALUE IS 'Value.';
COMMENT ON COLUMN CFGSRV_KEY_VALUE_PAIRS.ARRAY_INDEX IS 'Index in the list.';

/*==============================================================*/
/* Table: CFGSRV_IINS                                           */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_IINS CASCADE;
CREATE TABLE CFGSRV_IINS (
  ID                    BIGINT          NOT NULL,--SERIAL with explicit SEQUENCE
  TERMINAL_CONFIG_ID    BIGINT          NOT NULL,
  KEY_                  SMALLINT        NOT NULL,
  RANGE_MIN             VARCHAR(19)     NOT NULL,
  RANGE_MAX             VARCHAR(19),
  RANGE_EXPIRY          VARCHAR(7),
  ACTIVE                CHAR(1)         NOT NULL,
  TTL_PTR               SMALLINT        NOT NULL,
  CS_PTR                SMALLINT        NOT NULL,
  ARRAY_INDEX           INT             NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_IIN_SEQ;
CREATE SEQUENCE CFGSRV_IIN_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_IINS.ID;
ALTER TABLE CFGSRV_IINS
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_IIN_SEQ');

ALTER TABLE CFGSRV_IINS
        ADD CONSTRAINT CFGSRV_IINS_PK
                PRIMARY KEY (ID);
ALTER TABLE CFGSRV_IINS
        ADD CONSTRAINT CFGSRV_IINS_TERMINAL_CONFIG_FK
                FOREIGN KEY (TERMINAL_CONFIG_ID)
                REFERENCES CFGSRV_TERMINAL_CONFIG (ID);

CREATE UNIQUE INDEX
        CFGSRV_IINS_IDX ON 
        CFGSRV_IINS(TERMINAL_CONFIG_ID, KEY_);
        
COMMENT ON COLUMN CFGSRV_IINS.KEY_ IS 'Numeric ID off iin.';
COMMENT ON COLUMN CFGSRV_IINS.RANGE_MIN IS 'Defines the minimum in the range of PANs.';
COMMENT ON COLUMN CFGSRV_IINS.RANGE_MAX IS 'Defines the maximum in the range of PANs.';
COMMENT ON COLUMN CFGSRV_IINS.RANGE_EXPIRY IS 'Validity period for exception ranges (optional).';
COMMENT ON COLUMN CFGSRV_IINS.ACTIVE IS 'Specifies whether or not the cards whith the PANs in the range are active.';
COMMENT ON COLUMN CFGSRV_IINS.TTL_PTR IS 'Corresponds to the key attribute of the linked ttl.';
COMMENT ON COLUMN CFGSRV_IINS.CS_PTR IS 'Corresponds to the key attribute of the linked card-scheme.';

/*==============================================================*/
/* Table: CFGSRV_TTLS                                           */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_TTLS CASCADE;
CREATE TABLE CFGSRV_TTLS (
  ID                    BIGINT          NOT NULL,--SERIAL with explicit SEQUENCE
  TERMINAL_CONFIG_ID    BIGINT          NOT NULL,
  KEY_                  SMALLINT        NOT NULL,
  -- Name of card e.g. Amex, not card holder:
  NAME                  VARCHAR(30)     NOT NULL DEFAULT '',
  -- PAN Range e.g. 011519 means PAN can be 1, 15 or 19 chars:
  PAN                   VARCHAR(38)     NOT NULL,
  -- Issue number length 0, 1 or 2:  
  INL                   SMALLINT        NOT NULL,
  -- Issue number position - 0 if absent:  
  INP                   SMALLINT        NOT NULL,
  -- Service Code Position 0 if not specified, 99 reserved for amex:
  SCP                   SMALLINT        NOT NULL,
  -- Start Date Position:  
  SDP                   SMALLINT        NOT NULL,
  -- Start date format 'N' or 'C':
  SDF                   CHAR(1)         NOT NULL,
  -- Expiry Date Position:
  EDP                   SMALLINT        NOT NULL,
  -- Luhn Check required '0', '1' or '2':
  LCR                   SMALLINT        NOT NULL,
  -- Expiry date format 'N' or 'R':
  EDF                   CHAR(1)         NOT NULL,
  -- Language Code Position:
  LCP                   SMALLINT        NOT NULL,
  -- Card Type Position:
  CTP                   SMALLINT        NOT NULL,
  -- Card Sequence Number Position:
  CSNP                  SMALLINT        NOT NULL,
  -- Auth Amount Position:
  AAP                   SMALLINT        NOT NULL,
  -- Pin Verification Value Id
  PWIDP                 SMALLINT        NOT NULL,
  -- Pin Verification Value 0, 4 or 5
  PWP                   SMALLINT        NOT NULL,
  -- Pin Verification Value Length
  PWL                   SMALLINT        NOT NULL,
  -- Card Verification Value Position
  CWP                   SMALLINT        NOT NULL,
  -- Card Authentication Value Position
  CAVP                  SMALLINT        NOT NULL,
  -- Track 2 CCD position
  T2CDP                 SMALLINT        NOT NULL,
  -- Discretionary Data position:
  DDP                   SMALLINT        NOT NULL,
  -- Discretionary Data length:
  DDL                   SMALLINT        NOT NULL,
  ARRAY_INDEX           INT             NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_TTLS_SEQ;
CREATE SEQUENCE CFGSRV_TTLS_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_TTLS.ID;
ALTER TABLE CFGSRV_TTLS
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_TTLS_SEQ');

ALTER TABLE CFGSRV_TTLS
        ADD CONSTRAINT CFGSRV_TTLS_PK
                PRIMARY KEY (ID);
ALTER TABLE CFGSRV_TTLS
        ADD CONSTRAINT CFGSRV_TTLS_TERMINAL_CONFIG_FK
                FOREIGN KEY (TERMINAL_CONFIG_ID)
                REFERENCES CFGSRV_TERMINAL_CONFIG (ID);

CREATE UNIQUE INDEX
        CFGSRV_TTLS_IDX ON
        CFGSRV_TTLS(TERMINAL_CONFIG_ID, KEY_);
        
COMMENT ON COLUMN CFGSRV_TTLS.KEY_ IS 'Ttl unique id.';
COMMENT ON COLUMN CFGSRV_TTLS.NAME IS 'Name of card e.g. Amex, not card holder.';
COMMENT ON COLUMN CFGSRV_TTLS.PAN IS 'PAN Range e.g. 011519 means PAN can be 1, 15 or 19 digits.';
COMMENT ON COLUMN CFGSRV_TTLS.INL IS 'Issue number length 0, 1 or 2.';
COMMENT ON COLUMN CFGSRV_TTLS.INP IS 'Issue number position - 0 if absent.';
COMMENT ON COLUMN CFGSRV_TTLS.SCP IS 'Service Code Position - 0 if not specified, 99 reserved for amex.';
COMMENT ON COLUMN CFGSRV_TTLS.SDP IS 'Start Date Position.';
COMMENT ON COLUMN CFGSRV_TTLS.SDF IS 'Start date format "N" or "C".';
COMMENT ON COLUMN CFGSRV_TTLS.EDP IS 'Expiry Date Position.';
COMMENT ON COLUMN CFGSRV_TTLS.LCR IS 'Luhn Check required - "0", "1" or "2".';
COMMENT ON COLUMN CFGSRV_TTLS.EDF IS 'Expiry date format "N" or "R".';
COMMENT ON COLUMN CFGSRV_TTLS.LCP IS 'Language Code Position.';
COMMENT ON COLUMN CFGSRV_TTLS.CTP IS 'Card Type Position.';
COMMENT ON COLUMN CFGSRV_TTLS.CSNP IS 'Card Sequence Number Position.';
COMMENT ON COLUMN CFGSRV_TTLS.AAP IS 'Auth Amount Position.';
COMMENT ON COLUMN CFGSRV_TTLS.PWIDP IS 'Pin Verification Value Id.';
COMMENT ON COLUMN CFGSRV_TTLS.PWP IS 'Pin Verification Value - 0, 4 or 5.';
COMMENT ON COLUMN CFGSRV_TTLS.PWL IS 'Pin Verification Value Length.';
COMMENT ON COLUMN CFGSRV_TTLS.CWP IS 'Card Verification Value Position.';
COMMENT ON COLUMN CFGSRV_TTLS.CAVP IS 'Card Authentication Value Position.';
COMMENT ON COLUMN CFGSRV_TTLS.T2CDP IS 'Track 2 CCD position.';
COMMENT ON COLUMN CFGSRV_TTLS.DDP IS 'Discretionary Data position.';
COMMENT ON COLUMN CFGSRV_TTLS.DDL IS 'Discretionary Data length.';

/*==============================================================*/
/* Table: CFGSRV_CARD_SCHEMES                                   */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_CARD_SCHEMES CASCADE;
CREATE TABLE CFGSRV_CARD_SCHEMES (
  ID                 BIGINT           NOT NULL,--SERIAL with explicit SEQUENCE
  TERMINAL_CONFIG_ID BIGINT           NOT NULL,
  KEY_               SMALLINT         NOT NULL,
  ACTIVE             CHAR(1)          NOT NULL,
  NAME               VARCHAR(16)      NOT NULL,
  FLOOR_LIMIT        INT              NOT NULL,
  KEY_ALLOWED        CHAR(1)          NOT NULL,
  ARRAY_INDEX        SMALLINT         NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_CARD_SCH_SEQ;
CREATE SEQUENCE CFGSRV_CARD_SCH_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_CARD_SCHEMES.ID;
ALTER TABLE CFGSRV_CARD_SCHEMES
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_CARD_SCH_SEQ');

ALTER TABLE CFGSRV_CARD_SCHEMES
        ADD CONSTRAINT CFGSRV_CARD_SCHEMES_PK
                PRIMARY KEY (ID);
ALTER TABLE CFGSRV_CARD_SCHEMES
        ADD CONSTRAINT CFGSRV_CARD_SCHEMES_TERMINAL_CONFIG_FK
                FOREIGN KEY (TERMINAL_CONFIG_ID)
                REFERENCES CFGSRV_TERMINAL_CONFIG (ID);

CREATE UNIQUE INDEX
        CFGSRV_CARD_SCHEMES_IDX ON
        CFGSRV_CARD_SCHEMES(TERMINAL_CONFIG_ID, KEY_);
        
COMMENT ON COLUMN CFGSRV_CARD_SCHEMES.KEY_ IS 'Card Scheme unique id.';
COMMENT ON COLUMN CFGSRV_CARD_SCHEMES.NAME IS 'Card scheme name.';
COMMENT ON COLUMN CFGSRV_CARD_SCHEMES.FLOOR_LIMIT IS 'Floor limit (in the minimum country-specific monetary units) set by the card scheme.';
COMMENT ON COLUMN CFGSRV_CARD_SCHEMES.KEY_ALLOWED IS 'Specifies whether or not the card scheme allows manual keying of the card details.';
COMMENT ON COLUMN CFGSRV_CARD_SCHEMES.ACTIVE IS 'Specifies whether or not the card scheme is active.';

/*==============================================================*/
/* Table: CFGSRV_CARD_PROVIDERS                                 */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_CARD_PROVIDERS CASCADE;
CREATE TABLE CFGSRV_CARD_PROVIDERS (
  ID                            BIGINT          NOT NULL,--SERIAL with explicit SEQUENCE
  TERMINAL_CONFIG_ID            BIGINT          NOT NULL,
  KEY_                          SMALLINT        NOT NULL,
  NAME                          VARCHAR(30)     NOT NULL,
  FLOOR_LIMIT                   INT             NOT NULL,
  THRESHOLD                     INT             NOT NULL,
  TAC_DENIAL                    VARCHAR(10),
  TAC_ONLINE                    VARCHAR(10),
  TAC_DEFAULT                   VARCHAR(10),
  DEFAULT_TDOL                  VARCHAR(504),
  DEFAULT_DDOL                  VARCHAR(504)    NOT NULL,
  TARGET_PERCENTAGE             SMALLINT        NOT NULL,
  MAXIMUM_TARGET_PERCENTAGE     SMALLINT        NOT NULL,
  TERMINAL_COUNTRY_CODE         SMALLINT        NOT NULL,
  TXN_CURRENCY_CODE             SMALLINT        NOT NULL,
  ACQUIRER_ID			VARCHAR(12)	NOT NULL,
  MERCHANT_CATEGORY_CODE	VARCHAR(4)	NOT NULL,
  TRANS_CUR_EXP			VARCHAR(4)	NOT NULL,
  TRANS_REF_CUR			VARCHAR(4)	NOT NULL,
  TRANS_REF_CUR_EXP		VARCHAR(2)	NOT NULL,
  MERCHANT_ID			VARCHAR(15)	NOT NULL,
  ARRAY_INDEX                   INT             NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_CARD_PROV_SEQ;
CREATE SEQUENCE CFGSRV_CARD_PROV_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_CARD_PROVIDERS.ID;
ALTER TABLE CFGSRV_CARD_PROVIDERS
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_CARD_PROV_SEQ');

ALTER TABLE CFGSRV_CARD_PROVIDERS
        ADD CONSTRAINT CFGSRV_CARD_PROVIDERS_PK
                PRIMARY KEY (ID);
ALTER TABLE CFGSRV_CARD_PROVIDERS
        ADD CONSTRAINT CFGSRV_CARD_PROVIDERS_TERMINAL_CONFIG_FK
                FOREIGN KEY (TERMINAL_CONFIG_ID)
                REFERENCES CFGSRV_TERMINAL_CONFIG (ID);

CREATE UNIQUE INDEX CFGSRV_CARD_PROVIDERS_IDX ON
        CFGSRV_CARD_PROVIDERS(TERMINAL_CONFIG_ID, KEY_);
        
COMMENT ON COLUMN CFGSRV_CARD_PROVIDERS.KEY_ IS 'Corresponds to the key of the EMV card application linked.';
COMMENT ON COLUMN CFGSRV_CARD_PROVIDERS.NAME IS 'Card provider name.';
COMMENT ON COLUMN CFGSRV_CARD_PROVIDERS.FLOOR_LIMIT IS 'Floor limit (in the minimum country-specific monetary units) set by the card provider.';
COMMENT ON COLUMN CFGSRV_CARD_PROVIDERS.THRESHOLD IS 'Threshold (in the minimum country-specific monetary units) set by the card provider.';
COMMENT ON COLUMN CFGSRV_CARD_PROVIDERS.TAC_DENIAL IS 'Termminal Action Code Denial - hexadecimal string encoded in base64 format.';
COMMENT ON COLUMN CFGSRV_CARD_PROVIDERS.TAC_ONLINE IS 'Termminal Action Code Online - hexadecimal string encoded in base64 format.';
COMMENT ON COLUMN CFGSRV_CARD_PROVIDERS.TAC_DEFAULT IS 'Termminal Action Code Default - hexadecimal string encoded in base64 format.';
COMMENT ON COLUMN CFGSRV_CARD_PROVIDERS.DEFAULT_TDOL IS 'Default Transaction Certificate Data Object List - hexadecimal string encoded in base64 format.';
COMMENT ON COLUMN CFGSRV_CARD_PROVIDERS.DEFAULT_DDOL IS 'Default Dynamic Data Authentication Data Object List - hexadecimal string encoded in base64 format.';
COMMENT ON COLUMN CFGSRV_CARD_PROVIDERS.TARGET_PERCENTAGE IS 'Target percentage set by the card provider.';
COMMENT ON COLUMN CFGSRV_CARD_PROVIDERS.MAXIMUM_TARGET_PERCENTAGE IS 'Maximum target percentage set by the card provider.';
COMMENT ON COLUMN CFGSRV_CARD_PROVIDERS.TERMINAL_COUNTRY_CODE IS 'A numeric identifier (code) of the country to wich the terminal is assigned.';
COMMENT ON COLUMN CFGSRV_CARD_PROVIDERS.TXN_CURRENCY_CODE IS 'Transaction currency code.';

/*==============================================================*/
/* Table: CFGSRV_EMV_CARD_APPLICATIONS                          */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_EMV_CARD_APPLICATIONS CASCADE;
CREATE TABLE CFGSRV_EMV_CARD_APPLICATIONS (
  ID                    BIGINT          NOT NULL,--SERIAL with explicit SEQUENCE
  TERMINAL_CONFIG_ID    BIGINT          NOT NULL,
  KEY_                  SMALLINT        NOT NULL,
  CARD_APP_LIVE_FLAG    CHAR(1)         NOT NULL,
  CARD_PROVIDER_KEY     SMALLINT        NOT NULL,
  -- Application IDentifier - hex string encoded in base64 - max length 32.
  AID                   VARCHAR(32)     NOT NULL,
  -- Termminal Risk Management Data - hex string encoded in base64 - max length 16.
  TRMD                  VARCHAR(16)     NOT NULL,
  PRIORITY_INDEX        SMALLINT        NOT NULL,
  SELECTION_APPLI_FLAG  CHAR(1)         NOT NULL,
  APPLICATION_VERSION   SMALLINT        NOT NULL DEFAULT 0,
  TERMINAL_CAPABILITIES		VARCHAR(8)	NOT NULL,
  ADD_TERMINAL_CAPABILITIES	VARCHAR(8)	NOT NULL,
  TERMINAL_TYPE			VARCHAR(2)	NOT NULL,
  ARRAY_INDEX           INT             NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_EMV_CARD_APP_SEQ;
CREATE SEQUENCE CFGSRV_EMV_CARD_APP_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_EMV_CARD_APPLICATIONS.ID;
ALTER TABLE CFGSRV_EMV_CARD_APPLICATIONS
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_EMV_CARD_APP_SEQ');

ALTER TABLE CFGSRV_EMV_CARD_APPLICATIONS
        ADD CONSTRAINT CFGSRV_EMV_CARD_APPLICATIONS_PK
                PRIMARY KEY (ID);
ALTER TABLE CFGSRV_EMV_CARD_APPLICATIONS
        ADD CONSTRAINT CFGSRV_EMV_CARD_APPLICATIONS_TERMINAL_CONFIG_FK
                FOREIGN KEY (TERMINAL_CONFIG_ID)
                REFERENCES CFGSRV_TERMINAL_CONFIG (ID);

CREATE UNIQUE INDEX
        CFGSRV_EMV_CARD_APPLICATIONS_IDX ON
        CFGSRV_EMV_CARD_APPLICATIONS(TERMINAL_CONFIG_ID, KEY_);
        
COMMENT ON COLUMN CFGSRV_EMV_CARD_APPLICATIONS.KEY_ IS 'Number of EMV card application element.';
COMMENT ON COLUMN CFGSRV_EMV_CARD_APPLICATIONS.CARD_APP_LIVE_FLAG IS 'Specifies whether or not the application is active, that is, can be selected and used when processing a transaction.';
COMMENT ON COLUMN CFGSRV_EMV_CARD_APPLICATIONS.CARD_PROVIDER_KEY IS 'Key attribute of the card provider.';
COMMENT ON COLUMN CFGSRV_EMV_CARD_APPLICATIONS.AID IS 'EMV unique Application IDentifier - hexadecimal string encoded in base64 format.';
COMMENT ON COLUMN CFGSRV_EMV_CARD_APPLICATIONS.TRMD IS 'Termminal Risk Management Data - hexadecimal string encoded in base64 format.';
COMMENT ON COLUMN CFGSRV_EMV_CARD_APPLICATIONS.PRIORITY_INDEX IS 'Priority affecting the selection of an application in cases when more than one application is present in the smart card.';
COMMENT ON COLUMN CFGSRV_EMV_CARD_APPLICATIONS.SELECTION_APPLI_FLAG IS 'Specifies whether or not an application can be selected if its AID in the terminal and in the smart card match partially.';
COMMENT ON COLUMN CFGSRV_EMV_CARD_APPLICATIONS.APPLICATION_VERSION IS 'EMV application version number, assigned by the payment system.';


/*==============================================================*/
/* Table: CFGSRV_RSA_KEYS                                       */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_RSA_KEYS CASCADE;
CREATE TABLE CFGSRV_RSA_KEYS (
  ID                 BIGINT             NOT NULL,--SERIAL with explicit SEQUENCE
  TERMINAL_CONFIG_ID BIGINT             NOT NULL,
  KEY_               SMALLINT           NOT NULL,
  KEY_INDICATOR      SMALLINT           NOT NULL,
  RID                VARCHAR(10)        NOT NULL,
  KEY_DATA           TEXT               NOT NULL,
  EXPONENT           VARCHAR(64)        NOT NULL,
  ARRAY_INDEX        INT                NOT NULL,
  HASH               VARCHAR(28)        NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_RSA_KEY_SEQ;
CREATE SEQUENCE CFGSRV_RSA_KEY_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_RSA_KEYS.ID;
ALTER TABLE CFGSRV_RSA_KEYS
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_RSA_KEY_SEQ');

ALTER TABLE CFGSRV_RSA_KEYS
        ADD CONSTRAINT CFGSRV_RSA_KEYS_PK
                PRIMARY KEY (ID);
ALTER TABLE CFGSRV_RSA_KEYS
        ADD CONSTRAINT CFGSRV_RSA_KEYS_TERMINAL_CONFIG_FK
                FOREIGN KEY (TERMINAL_CONFIG_ID)
                REFERENCES CFGSRV_TERMINAL_CONFIG (ID);

CREATE UNIQUE INDEX
        CFGSRV_RSA_KEYS_IDX ON
        CFGSRV_RSA_KEYS(TERMINAL_CONFIG_ID, KEY_);
        
COMMENT ON COLUMN CFGSRV_RSA_KEYS.KEY_INDICATOR IS 'The certification Authority Public Key Index.';
COMMENT ON COLUMN CFGSRV_RSA_KEYS.RID IS 'Registered Application Provider Identifier - hexadecimal string encoded in base64 format.';
COMMENT ON COLUMN CFGSRV_RSA_KEYS.KEY_DATA IS 'Modulus of the RSA key - hexadecimal string encoded in base64 format.';
COMMENT ON COLUMN CFGSRV_RSA_KEYS.EXPONENT IS 'Exponent of the RSA key - hexadecimal string encoded in base64 format.';
COMMENT ON COLUMN CFGSRV_RSA_KEYS.HASH IS 'RSA key hash - hexadecimal string encoded in base64 format.';
 
/*==============================================================*/
/* Table: CFGSRV_RISK_MAN_VERDICT                               */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_RISK_MAN_VERDICT CASCADE;
CREATE TABLE CFGSRV_RISK_MAN_VERDICT (
  ID                 BIGINT             NOT NULL,--SERIAL with explicit SEQUENCE
  TERMINAL_CONFIG_ID BIGINT             NOT NULL,
  KEY_               SMALLINT           NOT NULL,
  CHECK_RISK         VARCHAR(20)        NOT NULL,
  VERDICT            VARCHAR(10)        NOT NULL,
  ARRAY_INDEX        INT                NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_RISK_MAN_SEQ;
CREATE SEQUENCE CFGSRV_RISK_MAN_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_RISK_MAN_VERDICT.ID;
ALTER TABLE CFGSRV_RISK_MAN_VERDICT
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_RISK_MAN_SEQ');

ALTER TABLE CFGSRV_RISK_MAN_VERDICT
        ADD CONSTRAINT CFGSRV_RISK_MAN_VERDICT_PK
                PRIMARY KEY (ID);
ALTER TABLE CFGSRV_RISK_MAN_VERDICT
        ADD CONSTRAINT CFGSRV_RISK_MAN_VERDICT_TERMINAL_CONFIG_FK
                FOREIGN KEY (TERMINAL_CONFIG_ID)
                REFERENCES CFGSRV_TERMINAL_CONFIG (ID);
            
CREATE UNIQUE INDEX
        CFGSRV_RISK_MAN_VERDICT_IDX ON
        CFGSRV_RISK_MAN_VERDICT(TERMINAL_CONFIG_ID, KEY_);
        
COMMENT ON COLUMN CFGSRV_RISK_MAN_VERDICT.KEY_ IS 'Risk management id.';
COMMENT ON COLUMN CFGSRV_RISK_MAN_VERDICT.CHECK_RISK IS 'Type of check performed on the card data ("PanLength", "LuhnCheckDigit", "HotCardList", "ExpiryDate", "StartDate".';
COMMENT ON COLUMN CFGSRV_RISK_MAN_VERDICT.VERDICT IS 'Verdict when the corresponding check gives unsatisfactory result ("online", reject", "ignore".';

/*==============================================================*/
/* Table: CFGSRV_HOT_CARD                                       */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_HOT_CARD CASCADE;
CREATE TABLE CFGSRV_HOT_CARD (
  ID                 BIGINT             NOT NULL,--SERIAL with explicit SEQUENCE
  TERMINAL_CONFIG_ID BIGINT             NOT NULL,
  KEY_               SMALLINT           NOT NULL,
  OPERATION          VARCHAR(10)        NOT NULL,
  PAN                VARCHAR(19)        NOT NULL,
  ARRAY_INDEX        INT                NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_HOT_CARD_SEQ;
CREATE SEQUENCE CFGSRV_HOT_CARD_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_HOT_CARD.ID;
ALTER TABLE CFGSRV_HOT_CARD
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_HOT_CARD_SEQ');

ALTER TABLE CFGSRV_HOT_CARD
        ADD CONSTRAINT CFGSRV_HOT_CARD_PK
                PRIMARY KEY (ID);
ALTER TABLE CFGSRV_HOT_CARD
        ADD CONSTRAINT CFGSRV_HOT_CARD_TERMINAL_CONFIG_FK
                FOREIGN KEY (TERMINAL_CONFIG_ID)
                REFERENCES CFGSRV_TERMINAL_CONFIG (ID);

CREATE UNIQUE INDEX
        CFGSRV_HOT_CARD_IDX ON
        CFGSRV_HOT_CARD(TERMINAL_CONFIG_ID, KEY_);
        
COMMENT ON COLUMN CFGSRV_HOT_CARD.KEY_ IS 'Unique hot card id.';
COMMENT ON COLUMN CFGSRV_HOT_CARD.OPERATION IS 'Specifies what should be done whith the corresponding card information - "insert", "remove".';
COMMENT ON COLUMN CFGSRV_HOT_CARD.PAN IS 'Primary Account Number which identifies the card.';

/*==============================================================*/
/* Table: CFGSRV_HOT_CARD_CONFIG                                */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_HOT_CARD_CONFIG CASCADE;
CREATE TABLE CFGSRV_HOT_CARD_CONFIG (
  ID                 BIGINT     NOT NULL,--SERIAL with explicit SEQUENCE
  TERMINAL_CONFIG_ID BIGINT     NOT NULL,
  CLEAR              CHAR(1)    NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_HOT_CARD_CFG_SEQ;
CREATE SEQUENCE CFGSRV_HOT_CARD_CFG_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_HOT_CARD_CONFIG.ID;
ALTER TABLE CFGSRV_HOT_CARD_CONFIG
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_HOT_CARD_CFG_SEQ');

ALTER TABLE CFGSRV_HOT_CARD_CONFIG
        ADD CONSTRAINT CFGSRV_HOT_CARD_CONFIG_PK
                PRIMARY KEY (ID);
ALTER TABLE CFGSRV_HOT_CARD_CONFIG
        ADD CONSTRAINT CFGSRV_HOT_CARD_CONFIG_TERMINAL_CONFIG_FK
                FOREIGN KEY (TERMINAL_CONFIG_ID)
                REFERENCES CFGSRV_TERMINAL_CONFIG (ID);

CREATE UNIQUE INDEX
        CFGSRV_HOT_CARD_CONFIG_IDX ON
        CFGSRV_HOT_CARD_CONFIG(TERMINAL_CONFIG_ID);
        
COMMENT ON COLUMN CFGSRV_HOT_CARD_CONFIG.CLEAR IS 'Specifies whether or not the hot card list used by the terminal should be cleared.';

/*==============================================================*/
/* Table: CFGSRV_VARDCL                                         */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_VARDCL CASCADE;
CREATE TABLE CFGSRV_VARDCL (
  ID                 BIGINT             NOT NULL,--SERIAL with explicit SEQUENCE 
  TERMINAL_CONFIG_ID BIGINT             NOT NULL,
  KEY_               SMALLINT           NOT NULL,
  NAME               VARCHAR(50)        NOT NULL,
  TYPE               VARCHAR(10),
  VOLATILE           CHAR(1),
  VALUE              TEXT               NOT NULL,
  PERMS              VARCHAR(20),
  FORMAT             VARCHAR(20),
  ARRAY_INDEX        INT                NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_VARDCL_SEQ;
CREATE SEQUENCE CFGSRV_VARDCL_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_VARDCL.ID;
ALTER TABLE CFGSRV_VARDCL
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_VARDCL_SEQ');

ALTER TABLE CFGSRV_VARDCL
        ADD CONSTRAINT CFGSRV_VARDCL_PK
                PRIMARY KEY (ID);
ALTER TABLE CFGSRV_VARDCL
        ADD CONSTRAINT CFGSRV_VARDCL_TERMINAL_CONFIG_FK
                FOREIGN KEY (TERMINAL_CONFIG_ID)
                REFERENCES CFGSRV_TERMINAL_CONFIG (ID);

CREATE UNIQUE INDEX
        CFGSRV_VARDCL_IDX ON
        CFGSRV_VARDCL(TERMINAL_CONFIG_ID, KEY_);
        
COMMENT ON COLUMN CFGSRV_VARDCL.KEY_ IS 'ID of the variable.';
COMMENT ON COLUMN CFGSRV_VARDCL.NAME IS 'Defines the name of the variable.';
COMMENT ON COLUMN CFGSRV_VARDCL.TYPE IS 'The variable type - "string", "integer", "date", "opaque".';
COMMENT ON COLUMN CFGSRV_VARDCL.VOLATILE IS 'Specifies if the variable is physically stored in the RAM ("1") or in the terminal flash memory ("0").';
COMMENT ON COLUMN CFGSRV_VARDCL.VALUE IS 'Value assigned to the variable.';
COMMENT ON COLUMN CFGSRV_VARDCL.PERMS IS 'Defines access permissions for the variable - e.g "rw-rw".';
COMMENT ON COLUMN CFGSRV_VARDCL.FORMAT IS 'Defines a formatting pattern for the variable value.';

/*==============================================================*/
/* Table: CFGSRV_SETVAR                                         */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_SETVAR CASCADE;
CREATE TABLE CFGSRV_SETVAR (
    ID                 BIGINT           NOT NULL,--SERIAL with explicit SEQUENCE
    TERMINAL_CONFIG_ID BIGINT           NOT NULL,
    KEY_               SMALLINT         NOT NULL,
    NAME               VARCHAR(50)      NOT NULL,
    VALUE              TEXT             NOT NULL,
    FORMAT             VARCHAR(20),
    ARRAY_INDEX        INT              NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_SETVAR_SEQ;
CREATE SEQUENCE CFGSRV_SETVAR_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_SETVAR.ID;
ALTER TABLE CFGSRV_SETVAR
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_SETVAR_SEQ');

ALTER TABLE CFGSRV_SETVAR
        ADD CONSTRAINT CFGSRV_SETVAR_PK
                PRIMARY KEY (ID);
ALTER TABLE CFGSRV_SETVAR
        ADD CONSTRAINT CFGSRV_SETVAR_TERMINAL_CONFIG_FK
                FOREIGN KEY (TERMINAL_CONFIG_ID)
                REFERENCES CFGSRV_TERMINAL_CONFIG (ID);

CREATE UNIQUE INDEX
        CFGSRV_SETVAR_IDX ON
        CFGSRV_VARDCL(TERMINAL_CONFIG_ID, KEY_);
        
COMMENT ON COLUMN CFGSRV_VARDCL.NAME IS 'Defines the name of the variable.';
COMMENT ON COLUMN CFGSRV_VARDCL.VALUE IS 'Value assigned to the variable.';
COMMENT ON COLUMN CFGSRV_VARDCL.FORMAT IS 'Defines a formatting pattern for the variable value.';


/*==============================================================*/
/* Table: CFGSRV_CFG_ASSIGN                                     */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_CFG_ASSIGN CASCADE;
CREATE TABLE CFGSRV_CFG_ASSIGN (
  ID                    BIGINT          NOT NULL,--SERIAL with explicit SEQUENCE
  -- THIS WILL BE THE TERMINAL ITID FOR TERMINALS AND
  -- GROUP SYMBOLIC ID FOR OTHER TYPES:
  REFERENCE             CHAR(20)        NOT NULL,
  -- GROUP SYMBOLIC ID FOR OTHER TYPES
  -- 'T' TERMINAL, 'B' BANK ETC ( ONLY TYPE 'T' WILL BE USED FOR DETERMINING):
  ASSIGN_TYPE           CHAR(1)         NOT NULL,
  -- 'T' TERMINAL, 'B' BANK ETC - DEFINES 'HOW' THE ASSIGNMENT WAS MADE:
  ASSIGN_LEVEL          CHAR(1)         NOT NULL,
  -- 'M' MAGCARD ETC - WILL BE 4 ENTRIES FOR EACH TERMINAL:
  CONFIG_TYPE           CHAR(1)         NOT NULL,
  -- THE KEY TO CFGSRV_TERMINAL_CONFIG:
  CONFIG_ID             BIGINT          NOT NULL,--TODO FK?
  -- 'U' UNDELIVERED,   'D' DELIVERED:
  STATUS                CHAR(1),
  -- DATE THE ASSIGNMENT WAS CREATED:
  ASSIGNMENT_DATE       TIMESTAMP       NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_ASSIGN_SEQ;
CREATE SEQUENCE CFGSRV_ASSIGN_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_CFG_ASSIGN.ID;
ALTER TABLE CFGSRV_CFG_ASSIGN
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_ASSIGN_SEQ');

ALTER TABLE CFGSRV_CFG_ASSIGN
        ADD CONSTRAINT CFGSRV_CFG_ASSIGN_PK
                PRIMARY KEY (ID);
                
COMMENT ON COLUMN CFGSRV_CFG_ASSIGN.REFERENCE IS 'Terminal ITID for terminals and Group Symbolic ID for other types.';
COMMENT ON COLUMN CFGSRV_CFG_ASSIGN.ASSIGN_TYPE IS '"T" terminal, "B" bank etc.';
COMMENT ON COLUMN CFGSRV_CFG_ASSIGN.ASSIGN_LEVEL IS '"T" terminal, "B" bank etc.';
COMMENT ON COLUMN CFGSRV_CFG_ASSIGN.CONFIG_TYPE IS '"M" for margard etc - 4 entries for each terminal.';
COMMENT ON COLUMN CFGSRV_CFG_ASSIGN.CONFIG_ID IS 'key to CFGSRV_TERMINAL_CONFIG.';
COMMENT ON COLUMN CFGSRV_CFG_ASSIGN.STATUS IS '"U" undelivered, "D" delivered.';
COMMENT ON COLUMN CFGSRV_CFG_ASSIGN.ASSIGNMENT_DATE IS 'Assignment creation date.';

/*==============================================================*/
/* Table: CFGSRV_CFG_ASSIGN_ARCHIVE                             */
/*==============================================================*/
DROP TABLE IF EXISTS CFGSRV_CFG_ASSIGN_ARCHIVE CASCADE;
CREATE TABLE CFGSRV_CFG_ASSIGN_ARCHIVE (
  ID              BIGINT        NOT NULL,--SERIAL with explicit SEQUENCE
  -- THIS WILL BE THE TERMINAL ITID FOR TERMINALS AND
  -- GROUP SYMBOLIC ID FOR OTHER TYPES:
  REFERENCE       CHAR(20)      NOT NULL,
  -- 'M' MAGCARD ETC - WILL BE 4 ENTRIES FOR EACH TERMINAL:
  CONFIG_TYPE     CHAR(1)       NOT NULL,
  -- 'T' TERMINAL, 'B' BANK ETC ( ONLY TYPE 'T' WILL BE 
  -- USED FOR DETERMINING TERMINAL CONFIG):
  ASSIGN_TYPE     CHAR(1)       NOT NULL,
  -- 'T' TERMINAL, 'B' BANK ETC - DEFINES 'HOW' THE ASSIGNMENT WAS MADE:
  ASSIGN_LEVEL    CHAR(1)       NOT NULL,
  -- THE KEY TO CFGSRV_TERMINAL_CONFIG:
  CONFIG_ID       BIGINT        NOT NULL,--TODO FK?
  -- 'U' UNDELIVERED,   'D' DELIVERED:
  STATUS          CHAR(1),
  -- DATE THE ASSIGNMENT WAS CREATED:
  START_DATE      TIMESTAMP     NOT NULL,
  -- DATE THE ASSIGNMENT WAS CREATED:
  END_DATE        TIMESTAMP     NOT NULL
);

DROP SEQUENCE IF EXISTS CFGSRV_ASSIGN_ARCH_SEQ;
CREATE SEQUENCE CFGSRV_ASSIGN_ARCH_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_CFG_ASSIGN_ARCHIVE.ID;
ALTER TABLE CFGSRV_CFG_ASSIGN_ARCHIVE
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_ASSIGN_ARCH_SEQ');

ALTER TABLE CFGSRV_CFG_ASSIGN_ARCHIVE
        ADD CONSTRAINT CFGSRV_CFG_ASSIGN_ARCHIVE_PK
                PRIMARY KEY (ID);

DROP TABLE IF EXISTS CFGSRV_SERVICE_PROFILE_ASSIGN;
CREATE TABLE CFGSRV_SERVICE_PROFILE_ASSIGN (
  ID BIGINT NOT NULL,
  PROFILE VARCHAR(255) NOT NULL,
  SERVICE VARCHAR(255) NOT NULL,
  ASSIGNMENT_DATE DATE NOT NULL,
  IS_DEFAULT BOOLEAN NOT NULL DEFAULT FALSE
);

DROP SEQUENCE IF EXISTS srv_profile_assign_seq;
CREATE SEQUENCE srv_profile_assign_seq
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_SERVICE_PROFILE_ASSIGN.ID;
ALTER TABLE CFGSRV_SERVICE_PROFILE_ASSIGN
        ALTER COLUMN ID SET DEFAULT NEXTVAL('srv_profile_assign_seq');

ALTER TABLE CFGSRV_SERVICE_PROFILE_ASSIGN
        ADD CONSTRAINT CFGSRV_SERVICE_PROFILE_ASSIGN_PK
                PRIMARY KEY (ID);