DROP USER btmlpa CASCADE
/

CREATE USER btmlpa IDENTIFIED BY ingenico
    DEFAULT TABLESPACE USERS
    TEMPORARY TABLESPACE TEMP
    PROFILE DEFAULT
    ACCOUNT UNLOCK
/
GRANT "CONNECT" TO btmlpa
/
GRANT "RESOURCE" TO btmlpa
/
GRANT DBA TO btmlpa
/
ALTER USER btmlpa DEFAULT ROLE "CONNECT",
                           "RESOURCE",
                           DBA
/
GRANT UNLIMITED TABLESPACE TO btmlpa
/

CONNECT btmlpa/ingenico;

CREATE TABLE BTMLPA_TERMINAL
(
    ID                 NUMBER(19,0)     	NOT NULL ENABLE,
    OE_ITID            VARCHAR2(20)     	NOT NULL ENABLE,
    APACS_TID          VARCHAR2(20)     	NOT NULL ENABLE,
    TRACED	       CHAR(1)	     		DEFAULT 'N',
      CONSTRAINT "BTMLPA_TERMINAL_PK" PRIMARY KEY ("ID") ENABLE
);

CREATE TABLE BTMLPA_TXN
(
    ID                 NUMBER(19,0)              NOT NULL ENABLE,
    TERMINAL_POST_ID   NUMBER(19,0)		 NOT NULL ENABLE,
    TERMINAL_TXN_ID    NUMBER(19,0)              ,
    TYPE               NUMBER(4,0)               ,
    TERMINAL_ID        NUMBER(19,0)              NOT NULL ENABLE,
    TERM_TXN_DATE      TIMESTAMP                 ,
    POST_TXN_DATE      TIMESTAMP                 NOT NULL ENABLE,
    TXN_STARTED        TIMESTAMP                 ,
    TXN_DURATION       NUMBER(19,0)              ,
    ACQR_STARTED       TIMESTAMP                 ,
    ACQR_DURATION      NUMBER(19,0)              ,
    STATE              NUMBER(4,0)               ,
    PAN                VARCHAR2(20)              ,
    STARTDATE          CHAR(5)                   ,
    EXPIRYDATE         CHAR(5)                   ,
    INPUTMETHOD        VARCHAR2(20)              ,
    CARDHOLDERNAME     VARCHAR2(50)              ,
    ISSUENUMBER        NUMBER(8,0)               ,
    ISO2TRACK          VARCHAR2(40)              ,
    ICC_APP            VARCHAR2(32)              ,
    ICC_AIP            NUMBER(8,0)               ,
    ICC_ATC            NUMBER(8,0)               ,
    ICC_ARQC           RAW(8)              ,
    ICC_IAD            RAW(32)             ,
    ICC_TVR            RAW(5)              ,
    ICC_UNUMBER        NUMBER(8,0)               ,
    ICC_ARPC           RAW(8)              ,
    ICC_ISSUER_AUTH    RAW(16)             ,
    ICC_ISSUER_SCRIPT  RAW(128)            ,
    FAIL_REASON        VARCHAR2(50)              ,
    MESSAGE            VARCHAR2(80)              ,
    AUTH_CODE          VARCHAR2(20)              ,
    AMOUNT             NUMBER(19,0)              ,
    AMOUNT_OTHER       NUMBER(19,0)              ,
    CURRENCY_CODE      CHAR(3)                   ,       
    TXNMODE            VARCHAR2(10)              ,
      CONSTRAINT "BTMLPA_TXN_PK" PRIMARY KEY ("ID") ENABLE,    
      CONSTRAINT "BTMLPA_TXN_FK" FOREIGN KEY ("TERMINAL_ID")
	  REFERENCES  "BTMLPA_TERMINAL" ("ID") ENABLE
);

--DROP SEQUENCE btmlpaterm_seq;

CREATE SEQUENCE btmlpaterm_seq
Start with 1
increment by 1
nomaxvalue; 

--DROP SEQUENCE btmlpaterm_seq;

CREATE SEQUENCE btmlpatxn_seq
Start with 1
increment by 1
nomaxvalue; 

create trigger btmlpaterm_trig
before insert
on BTMLPA_TERMINAL
for each row
begin 
select btmlpaterm_seq.nextval into:new.id
from dual;
end;
/

create trigger btmlpatxn_trig
before insert
on BTMLPA_TXN
for each row
begin 
select btmlpatxn_seq.nextval into:new.id
from dual;
end;
/

--DROP TABLE "WEB_SRV" cascade constraints;

CREATE TABLE  "WEB_SRV" 
   (	"ID" NUMBER NOT NULL ENABLE, 
	"SRV_NAME" VARCHAR2(20) NOT NULL ENABLE, 
	"SRV_DESCR" VARCHAR2(255) NOT NULL ENABLE, 
	"PAGE" NUMBER DEFAULT 10 NOT NULL ENABLE, 
	 CONSTRAINT "WEB_SRV_PK" PRIMARY KEY ("ID") ENABLE
   );

--DROP TABLE "WEB_SRVFIELD" cascade constraints;

CREATE TABLE  "WEB_SRVFIELD" 
   (	"SRV_ID" NUMBER NOT NULL ENABLE, 
	"FIELD_ID" NUMBER NOT NULL ENABLE, 
	"FIELD_NAME" VARCHAR2(255) NOT NULL ENABLE, 
	"FIELD_DESCR" VARCHAR2(255) NOT NULL ENABLE, 
	"CHECKED" VARCHAR2(1) DEFAULT 'N' NOT NULL ENABLE, 
	 CONSTRAINT "WEB_SRVFIELD_FK" FOREIGN KEY ("SRV_ID")
	  REFERENCES  "WEB_SRV" ("ID") ENABLE
   );

--DROP TABLE "WEB_USERS" cascade constraints;

CREATE TABLE  "WEB_USERS" 
   (	"ID" NUMBER NOT NULL ENABLE, 
	"NAME" VARCHAR2(255) NOT NULL ENABLE, 
	"LOGIN" VARCHAR2(10) NOT NULL ENABLE, 
	"PASSWD" VARCHAR2(10) NOT NULL ENABLE, 
	 CONSTRAINT "WEB_USERS_PK" PRIMARY KEY ("ID") ENABLE
   );

--DROP TABLE "WEB_GROUPS" cascade constraints;
 
CREATE TABLE  "WEB_GROUPS" 
   (	"ID" NUMBER NOT NULL ENABLE, 
	"NAME" VARCHAR2(20) NOT NULL ENABLE, 
	"DESCR" VARCHAR2(255) NOT NULL ENABLE, 
	 CONSTRAINT "WEB_GROUPS_PK" PRIMARY KEY ("ID") ENABLE
   );

--DROP TABLE "WEB_USER_GROUP" cascade constraints;

CREATE TABLE  "WEB_USER_GROUP" 
   (	"ID" NUMBER NOT NULL ENABLE, 
	"USER_ID" NUMBER NOT NULL ENABLE, 
	"GROUP_ID" NUMBER NOT NULL ENABLE, 
	 CONSTRAINT "WEB_USER_GROUP_PK" PRIMARY KEY ("ID") ENABLE, 
	 CONSTRAINT "WEB_USER_GROUP_FK" FOREIGN KEY ("USER_ID")
	  REFERENCES  "WEB_USERS" ("ID") ENABLE, 
	 CONSTRAINT "WEB_USER_GROUP_FK2" FOREIGN KEY ("GROUP_ID")
	  REFERENCES  "WEB_GROUPS" ("ID") ENABLE
   );

--DROP TABLE "WEB_SRV_USER" cascade constraints;

CREATE TABLE  "WEB_SRV_USER" 
   (	"ID" NUMBER NOT NULL ENABLE, 
	"SRV_ID" NUMBER NOT NULL ENABLE, 
	"TYPE" NUMBER DEFAULT 1 NOT NULL ENABLE, 
	"USER_ID" NUMBER NOT NULL ENABLE, 
	 CONSTRAINT "WEB_SRV_USER_PK" PRIMARY KEY ("ID") ENABLE, 
	 CONSTRAINT "WEB_SRV_USER_FK" FOREIGN KEY ("SRV_ID")
	  REFERENCES  "WEB_SRV" ("ID") ENABLE
   );


CREATE UNIQUE INDEX web_srvfield_idx
on web_srvfield  (srv_id, field_id);

commit;


/*****************************************************************************
*
* COPYRIGHT (C) 2004-2007 Ingenico
* ALL RIGHTS RESERVED
*
* Copyright in the whole and every part of this software program belongs to
* Ingenico.  It may not be used, sold, licensed, transferred, copied
* or reproduced in whole or in part in any manner or form other than in
* accordance with and subject to the terms of a licence from Ingenico
* or with the prior written consent of Ingenico or as permitted by applicable law.
* This software program contains confidential and proprietary information and
* must not be disclosed, in whole or in part, to any person or organisation
* without the prior written consent of Ingenico.
* Any copies or reproductions of this software program (in whole or in part)
* made by any method must also include a copy of this legend.

*****************************************************************************/