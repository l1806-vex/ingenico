USE [master]
GO

IF  EXISTS (SELECT name FROM sys.databases WHERE name = N'btmlpa')
DROP DATABASE [btmlpa]
GO

IF  NOT EXISTS (SELECT * FROM sys.server_principals WHERE name = N'btmlpa')
CREATE LOGIN [btmlpa] WITH PASSWORD=N'ingenico', DEFAULT_DATABASE=[btmlpa], DEFAULT_LANGUAGE=[us_english], CHECK_EXPIRATION=ON, CHECK_POLICY=ON
GO

CREATE DATABASE [btmlpa] 
GO

USE btmlpa;
GO

CREATE USER [btmlpa] FOR LOGIN [btmlpa] WITH DEFAULT_SCHEMA=[dbo]
GO

EXEC sp_addrolemember N'db_owner', N'btmlpa'
GO

create table dbo.BTMLPA_TERMINAL
(
    ID                 BIGINT                NOT NULL IDENTITY,
    OE_ITID            VARCHAR(20)           NOT NULL,
    APACS_TID          VARCHAR(20)           NOT NULL,
    TRACED	       VARCHAR(1)	     NOT NULL DEFAULT 'N',
    primary key (ID)
);
GO

create table dbo.BTMLPA_TXN
(
    ID                 BIGINT                not null IDENTITY,
    TERMINAL_POST_ID   BIGINT		     not null,
    TERMINAL_TXN_ID    BIGINT                        ,
    TYPE               INT                           ,
    TERMINAL_ID        BIGINT                not null,
    TERM_TXN_DATE      datetime                      ,
    POST_TXN_DATE      datetime              not null,
    TXN_STARTED        datetime                      ,
    TXN_DURATION       BIGINT                        ,
    ACQR_STARTED       datetime                      ,
    ACQR_DURATION      BIGINT                        ,
    STATE              INT                           ,
    PAN                VARCHAR(20)                   ,
    STARTDATE          CHAR(5)                       ,
    EXPIRYDATE         CHAR(5)                       ,
    INPUTMETHOD        VARCHAR(20)                   ,
    CARDHOLDERNAME     VARCHAR(50)                   ,
    ISSUENUMBER        INT                           ,
    ISO2TRACK          VARCHAR(40)                   ,
    ICC_APP            VARCHAR(32)                   ,
    ICC_AIP            INT                           ,
    ICC_ATC            INT                           ,
    ICC_ARQC           VARBINARY(8)                  ,
    ICC_IAD            VARBINARY(32)                 ,
    ICC_TVR            VARBINARY(5)                  ,
    ICC_UNUMBER        INT                           ,
    ICC_ARPC           VARBINARY(8)                  ,
    ICC_ISSUER_AUTH    VARBINARY(16)                 ,
    ICC_ISSUER_SCRIPT  VARBINARY(128)                ,
    FAIL_REASON        VARCHAR(50)                   ,
    MESSAGE            VARCHAR(80)                   ,
    AUTH_CODE          VARCHAR(20)                   ,
    AMOUNT             BIGINT                        ,
    AMOUNT_OTHER       BIGINT                        ,
    CURRENCY_CODE      CHAR(3)                       ,       
    TXNMODE            VARCHAR(10)                   ,
    primary key (ID),
    foreign key  (TERMINAL_ID)
       references BTMLPA_TERMINAL (ID)
);
GO

create table dbo.web_srv
	(
	id		int		NOT NULL PRIMARY KEY,
	srv_name 	varchar(20) 	NOT NULL,
	srv_descr 	varchar(255) 	NOT NULL,
	page		int		NOT NULL DEFAULT 10
	);
GO

create table dbo.web_srvfield
	(
	srv_id		int		NOT NULL,
	field_id	int		NOT NULL,
	field_name 	varchar(255) 	NOT NULL,
	field_descr 	varchar(255) 	NOT NULL,
	checked		char(1)		NOT NULL DEFAULT 'N',
	foreign key(srv_id)
	       references web_srv(id)
	);
GO
create unique index web_srvfield_idx on web_srvfield(srv_id, field_id);
GO

create table dbo.web_users
	(
	id		int		NOT NULL PRIMARY KEY,
	name		varchar(255)	NOT NULL,
	login		varchar(10)	NOT NULL,
	passwd		varchar(10)	NOT NULL
	);
GO

create table dbo.web_groups
	(
	id		int		NOT NULL PRIMARY KEY,
	name		varchar(20)	NOT NULL,
	descr		varchar(255)	NOT NULL
	);
GO


create table dbo.web_user_group
	(
	id		int		NOT NULL PRIMARY KEY,
	user_id		int		NOT NULL,
	group_id	int		NOT NULL,
	foreign key(user_id)
	       references web_users(id),
	foreign key(group_id)
	       references web_groups(id)
	);
GO

create table dbo.web_srv_user
	(
	id		int		NOT NULL PRIMARY KEY,
	srv_id		int		NOT NULL,
	type		int		NOT NULL DEFAULT 1,
	user_id		int		NOT NULL,
	foreign key(srv_id)
	       references web_srv(id)
	);
GO


/***************************************************************************** 
*
* COPYRIGHT (C) 2004 Ingenico UK
* ALL RIGHTS RESERVED
*
* Copyright in the whole and every part of this software program belongs to
* Ingenico UK.  It may not be used, sold, licensed, transferred, copied
* or reproduced in whole or in part in any manner or form other than in
* accordance with and subject to the terms of a licence from Ingenico UK
* or with the prior written consent of Ingenico UK or as
* permitted by applicable law.
* This software program contains confidential and proprietary information and
* must not be disclosed, in whole or in part, to any person or organisation
* without the prior written consent of Ingenico UK.
* Any copies or reproductions of this software program (in whole or in part)
* made by any method must also include a copy of this legend.

*****************************************************************************/