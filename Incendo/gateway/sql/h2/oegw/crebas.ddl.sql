/*==============================================================*/
/* Table: oegw_client                                           */
/*==============================================================*/
CREATE TABLE oegw_client
(
   id			bigint		NOT NULL IDENTITY PRIMARY KEY,
   itid			varchar(32)	NOT NULL,
   initial_itid		varchar(32)	NOT NULL,
   merchant		varchar(50),
   serial_nmb           varchar(50),
   part_nmb             varchar(20),
   passwd               varchar(32),
   passwd_admin_reset   varchar(32),
   status               char(1)         NOT NULL,
   status_date          datetime,
   effect_date          datetime,
   prev_status          char(1),
   last_conn		bigint		DEFAULT 0,
   pin                  varchar(255)     NOT NULL,
   valid_date           datetime        NOT NULL,
   predecessor_itid     varchar(32),
   successor_itid       varchar(32),
   init_attempt		int             NOT NULL DEFAULT 0,
   synch		char(1)		NOT NULL DEFAULT 'Y',
   model                varchar(32)  NOT NULL DEFAULT 'other',
   browser              varchar(32)  NOT NULL DEFAULT 'v31',
   screentype           VARCHAR(32)  NOT NULL DEFAULT 'uc32color',
   resolution           VARCHAR(32),
   magcard              boolean  NOT NULL DEFAULT true,
   iccemv               boolean  NOT NULL DEFAULT true,
   cless                boolean  NOT NULL DEFAULT false,
   pinpad               boolean  NOT NULL DEFAULT false,
   touch                boolean  NOT NULL DEFAULT false,
   printer              boolean  NOT NULL DEFAULT true,
   idle			VARCHAR(255),
   clientid_ext		int
);

GRANT ALL ON oegw_client TO oe;
CREATE UNIQUE INDEX oegw_client_idx ON oegw_client(itid);
CREATE INDEX oegw_client_idx2 ON oegw_client(initial_itid);

/*==============================================================*/
/* Table: oegw_termcfg                                          */
/*==============================================================*/
CREATE TABLE oegw_termcfg
(
   id			bigint		NOT NULL IDENTITY PRIMARY KEY,
   cid			bigint		NOT NULL,
   post_date            datetime        NOT NULL,
   termcfg              text        	NOT NULL,
   foreign key  (cid)
       references oegw_client(id)
);
GRANT ALL ON oegw_termcfg TO oe;

/*==============================================================*/
/* Table: oegw_session                                          */
/*==============================================================*/
CREATE TABLE oegw_session
(
   id			bigint		NOT NULL IDENTITY PRIMARY KEY,
   cid                  bigint		NOT NULL,
   itid			varchar(32)	NOT NULL,
   client_ip            varchar(255)	NOT NULL,
   speed                float(24),
   compression 		float(24),
   istp			int, 
   auth			int, 
   web			int, 
   parser		int, 
   converter 		int, 
   db			int,
   oegw			int,
   sent          	int,
   gets			int,
   posts		int,
   gets_received	int,
   gets_sent		int,
   posts_received 	int,
   posts_sent		int,
   frmw_received	int,
   frmw_sent		int,
   received 	        int, 
   requests             int,
   startdate            datetime,
   enddate              datetime,
   duration             int,
   status               varchar(9)         NOT NULL,
   service_name		varchar(32),
   foreign key  (cid)
       references oegw_client(id)
);
GRANT ALL ON oegw_session TO oe;

CREATE INDEX oegw_session_cid ON oegw_session(cid);
CREATE INDEX oegw_session_itid ON oegw_session(itid);
CREATE INDEX oegw_session_startdate ON oegw_session(startdate);
CREATE INDEX oegw_session_status ON oegw_session(status);

/*==============================================================*/
/* Table: oegw_request                                          */
/*==============================================================*/
CREATE TABLE oegw_request
(
   sid            	bigint		NOT NULL,
   rid            	int             NOT NULL,
   startdate          	datetime,
   duration       	int,
   uri            	varchar(255),
   request		text,
   reqheader      	nvarchar(1024),
   error_response 	text,
   reply          	text,
   http_response	text,
   repheader         	nvarchar(1024),
   http_repheader       nvarchar(1024),
   status               varchar(9)         NOT NULL,
   resultcode           varchar(10)        NOT NULL,
   errortext            nvarchar(1024),
   service_name		varchar(32),
   foreign key  (sid)
       references oegw_session(id)
);
GRANT ALL ON oegw_request TO oe;

CREATE INDEX oegw_request_sid ON oegw_request(sid);
CREATE INDEX oegw_request_rid ON oegw_request(rid);

/*==============================================================*/
/* Table: oegw_termlog                                          */
/*==============================================================*/
CREATE TABLE oegw_termlog
(
   id			bigint		NOT NULL IDENTITY PRIMARY KEY,
   itid			varchar(32)	NOT NULL,
   name			varchar(255)	NOT NULL,
   uri            	varchar(255)
);
GRANT ALL ON oegw_termlog TO oe;

CREATE INDEX oegw_termlog_itid ON oegw_termlog(itid);

/*==============================================================*/
/* Table: oegw_termlogrecord                                    */
/*==============================================================*/
CREATE TABLE oegw_termlogrecord
(
   id			bigint		NOT NULL IDENTITY PRIMARY KEY,
   lid			bigint		NOT NULL,
   term_date            datetime        NOT NULL,
   module		varchar(255)	NOT NULL,
   severity            	varchar(20)		,
   descr            	varchar(255)		,
   foreign key  (lid)
       references oegw_termlog(id)
);
GRANT ALL ON oegw_termlogrecord TO oe;
CREATE INDEX oegw_termlogrecord_lid ON oegw_termlogrecord(lid);

CREATE TABLE web_srv
(
    id		int		NOT NULL IDENTITY PRIMARY KEY,
    srv_name 	varchar(20) 	NOT NULL,
    srv_descr 	varchar(255) 	NOT NULL,
    page	int		NOT NULL DEFAULT 10
);
GRANT ALL ON web_srv TO oe;

CREATE TABLE web_srvfield
(
    srv_id	int		NOT NULL,
    field_id	int		NOT NULL,
    field_name 	varchar(255) 	NOT NULL,
    field_descr varchar(255) 	NOT NULL,
    checked	char(1)		NOT NULL DEFAULT 'N',
    foreign key(srv_id)
    references web_srv(id)
);
GRANT ALL ON web_srvfield TO oe;
CREATE UNIQUE INDEX web_srvfield_idx ON web_srvfield(srv_id, field_id);

CREATE TABLE web_users
(
    id              int          NOT NULL IDENTITY PRIMARY KEY,
    name            varchar(255) NOT NULL,
    login           varchar(10)  NOT NULL,
    passwd          varchar(10)  NOT NULL,
    passwd_encrypt  varchar(100) ,
    passwd_changed  datetime     ,
    status          char 
);
GRANT ALL ON web_users TO oe;

CREATE TABLE web_user_pass_hist
(
    id              int          NOT NULL IDENTITY PRIMARY KEY,
    user_id         int          NOT NULL,
    passwd_encrypt  varchar(100) NOT NULL
);
GRANT ALL ON web_user_pass_hist TO oe;


CREATE TABLE web_groups
(
	id            int          NOT NULL IDENTITY PRIMARY KEY,
	name          varchar(20)  NOT NULL,
	descr         varchar(255) NOT NULL,
        access_admin  char(1)      ,
        access_cfg    char(1)      ,
        access_emm    char(1)      ,
        access_oegwmm char(1)       
);
GRANT ALL ON web_groups TO oe;


CREATE TABLE web_user_group
(
        id		int		NOT NULL IDENTITY PRIMARY KEY,
        user_id		int		NOT NULL,
        group_id	int		NOT NULL,
        foreign key(user_id)
               references web_users(id),
        foreign key(group_id)
               references web_groups(id)
);
GRANT ALL ON web_user_group TO oe;

CREATE TABLE web_srv_user
(
id		int		NOT NULL PRIMARY KEY,
srv_id		int		NOT NULL,
type		int		NOT NULL DEFAULT 1,
user_id		int		NOT NULL,
foreign key(srv_id)
       references web_srv(id)
);
GRANT ALL ON web_srv_user TO oe;

CREATE TABLE oegw_activity_log
(
   id                  bigint       NOT NULL IDENTITY PRIMARY KEY,
   event_time          datetime     NOT NULL,
   session_id          bigint       ,
   activity            varchar(50)  NOT NULL,
   event_severity      varchar(10)  NOT NULL,
   event_status        varchar(10)  NOT NULL,
   event_originator    varchar(100) NOT NULL,
   event_originator_ip varchar(255) NOT NULL,
   source_component    varchar(50)  NOT NULL,
   log_message         varchar(2048)NOT NULL  
);
CREATE TABLE oegw_db_version 
(
  main  int          NOT NULL,
  major int          NOT NULL,
  minor int          NOT NULL,
  build varchar(255) NOT NULL,
PRIMARY KEY (main,major,minor,build)
);
GRANT ALL ON oegw_activity_log TO oe;
CREATE INDEX oegw_activity_log_time ON oegw_activity_log(event_time);
CREATE INDEX oegw_activity_log_sid ON oegw_activity_log(session_id);
CREATE INDEX oegw_activity_log_severity ON oegw_activity_log(event_severity);
CREATE INDEX oegw_activity_log_status ON oegw_activity_log(event_status);

CREATE TABLE oegw_srvprovider
(
   id                   bigint          NOT NULL IDENTITY PRIMARY KEY,
   srvpid               varchar(32)     NOT NULL,
   name                 varchar(32)     NOT NULL,
   descr                varchar(255),
   email                varchar(255),
   phone                varchar(32),
   address              varchar(255),
   status               char(1)         NOT NULL
);
GRANT ALL ON oegw_srvprovider TO oe;

CREATE UNIQUE INDEX oegw_srvprovider_idx ON oegw_srvprovider(srvpid);

CREATE TABLE oegw_srv
(
   id                   bigint          NOT NULL IDENTITY PRIMARY KEY,
   srvid                varchar(32)     NOT NULL,
   srvpid               bigint          NOT NULL,
   name                 varchar(32)     NOT NULL,
   descr                varchar(255),
   status               char(1)         NOT NULL,
   hash_check           boolean DEFAULT FALSE,
   post_conv            boolean DEFAULT FALSE,
   base_uri             varchar(255)    ,
   start_page           varchar(255)    ,
   icon           	bigint    ,
   priority           	int DEFAULT 50,
foreign key(srvpid)
       references oegw_srvprovider(id)
);
GRANT ALL ON oegw_srv TO oe;

CREATE UNIQUE INDEX oegw_srv_idx ON oegw_srv(srvid);
CREATE INDEX oegw_srv_srvpid ON oegw_srv(srvpid);

CREATE TABLE cfgsrv_profile (
  id                 bigint             NOT NULL AUTO_INCREMENT PRIMARY KEY,
  magcard_id bigint             NOT NULL,
  iccemv_id bigint             NOT NULL,
  varlib_id bigint             NOT NULL,
  hcl_id bigint			NOT NULL,
  name varchar(255)
);
GRANT ALL ON cfgsrv_profile TO oe;

CREATE UNIQUE INDEX cfgsrv_profile_name ON cfgsrv_profile(name);

CREATE TABLE oegw_srvsubscr
(
   id                   bigint          NOT NULL IDENTITY PRIMARY KEY,--SERIAL WITH EXPLICIT SEQUENCE
   contract             varchar(255)    NOT NULL,
   cid			bigint          NOT NULL,
   srvid                bigint          NOT NULL,
   status               char(1)         NOT NULL,
   itid               	varchar(32)     NOT NULL,
   startup              boolean      DEFAULT false,
   inherited            boolean      DEFAULT false,
   previous_itid        varchar(32) default NULL,
   profile bigint default NULL,

   foreign key (cid)
       references oegw_client(id),
   foreign key (srvid)
       references oegw_srv(id),
   foreign key (profile)
       references cfgsrv_profile(id)
);
GRANT ALL ON oegw_srvsubscr TO oe;

CREATE INDEX oegw_srvsubscr_cid ON oegw_srvsubscr(cid);
CREATE INDEX oegw_srvsubscr_itid ON oegw_srvsubscr(itid);

CREATE TABLE oegw_srvsubscr_history
(
   id bigint NOT NULL IDENTITY PRIMARY KEY,
   srvid varchar(255) NOT NULL,
   status char(1) NOT NULL,
   term_itid varchar(32) NOT NULL,
   contract varchar(255) NOT NULL,
   status_date timestamp NOT NULL
);
GRANT ALL ON oegw_srvsubscr_history TO oe;

CREATE TABLE oegw_txn
(
   id                   bigint          NOT NULL IDENTITY PRIMARY KEY,--SERIAL WITH EXPLICIT SEQUENCE
   txn_id               bigint          NOT NULL,
   type                 int    NOT NULL,
   date                 bigint          NOT NULL,
   usr_txn_type         varchar(255)            ,
   itid                 varchar(255)    NOT NULL,
   srvid                varchar(255)    NOT NULL,
   status               varchar(255)    NOT NULL,
   amount               bigint         NOT NULL,
   cashback             bigint                 ,
   currency             varchar(3)      NOT NULL,
   currency_minor       int             NOT NULL,
   auth_code            varchar(255)            ,
   action_code          varchar(4)      
   
);
GRANT ALL ON oegw_txn TO oe;

CREATE INDEX oegw_txn_srvid ON oegw_txn(srvid);
CREATE INDEX oegw_txn_itid ON oegw_txn(itid);
CREATE INDEX oegw_txn_txnid ON oegw_txn(txn_id);

CREATE TABLE oegw_txn_msg
(
   id                   bigint          NOT NULL IDENTITY PRIMARY KEY,
   msg_id               bigint          NOT NULL,
   txn_db_id            bigint          NOT NULL,
   type                 int    NOT NULL,
   date                 bigint          NOT NULL,
   resend               int             NOT NULL,

   foreign key (txn_db_id)
       references oegw_txn(id)
);
GRANT ALL ON oegw_txn_msg TO oe;

CREATE INDEX oegw_txn_msg_id ON oegw_txn_msg(msg_id);
CREATE INDEX oegw_txn_txn_id ON oegw_txn_msg(txn_db_id);

CREATE TABLE oegw_txn_auth
(
   msg_id               bigint          NOT NULL,
   auth_code            varchar(255)            ,
   action_code          varchar(4),

   foreign key (msg_id)
       references oegw_txn_auth(msg_id)
);
GRANT ALL ON oegw_txn_auth TO oe;

CREATE INDEX oegw_txn_auth_msg_id ON oegw_txn_auth(msg_id);

CREATE TABLE oegw_txn_req
(
   msg_id               bigint          NOT NULL,
   amount               bigint         NOT NULL,
   cashback             bigint                 ,
   currency             varchar(3)      NOT NULL,
   currency_minor       int             NOT NULL,
   expiry               varchar(255)    NOT NULL,
   pan                  varchar(255)    NOT NULL,
   ext_fields           oid,

   foreign key (msg_id)
       references oegw_txn_msg(id)
);
GRANT ALL ON oegw_txn_req TO oe;

CREATE INDEX oegw_txn_req_msg_id ON oegw_txn_req(msg_id);

CREATE TABLE oegw_reconciliation_txn
(
   id                   bigint          NOT NULL IDENTITY PRIMARY KEY,
   txn_id               bigint          NOT NULL,
   type                 int             NOT NULL,
   date                 bigint          NOT NULL,
   itid                 varchar(255)    NOT NULL,
   srvid                varchar(255)    NOT NULL,
   merchant             varchar(255)    ,
   amount               bigint         NOT NULL,
   cashback             bigint                 ,
   currency             varchar(3)      NOT NULL,
   currency_minor       int             NOT NULL,
   auth_code            varchar(255)            ,
   error_code           varchar(255)            ,
   error_msg            varchar(255)
   
);
GRANT ALL ON oegw_reconciliation_txn TO oe;

CREATE INDEX oegw_reconciliation_txn_id ON oegw_reconciliation_txn(txn_id);
CREATE INDEX oegw_reconciliation_txn_itid ON oegw_reconciliation_txn(itid);
CREATE INDEX oegw_reconciliation_txn_srvid ON oegw_reconciliation_txn(srvid);

CREATE TABLE oegw_termreserve (
   id                   bigint        NOT NULL IDENTITY PRIMARY KEY,
   itid                 varchar(255)  NOT NULL ,
   locked               boolean       NOT NULL
);
GRANT ALL ON oegw_termreserve TO oe;

CREATE TABLE oegw_hash (
   id                   bigint        NOT NULL IDENTITY PRIMARY KEY,
   srvid                varchar(255)  NOT NULL ,
   resource             varchar(255)  NOT NULL ,
   hash                 varchar(255)  NOT NULL
);
GRANT ALL ON oegw_hash TO oe;

CREATE INDEX oegw_hash_srvid ON oegw_hash(srvid);
CREATE INDEX oegw_hash_resource ON oegw_hash(resource);
CREATE INDEX oegw_hash_hash ON oegw_hash(hash);






CREATE TABLE oegw_resource (
  id bigint NOT NULL IDENTITY PRIMARY KEY,
  data text NOT NULL,
  hash varchar(32) NOT NULL,
  name varchar(255) NOT NULL
);
GRANT ALL ON oegw_resource TO oe;

CREATE INDEX oegw_resource_hash ON oegw_resource(hash);


CREATE TABLE oegw_srvicon
(
   id                   bigint          NOT NULL IDENTITY PRIMARY KEY,--SERIAL WITH EXPLICIT SEQUENCE
   srvid                bigint	        NOT NULL,  
   data1                text            NOT NULL,
   data1_version        bigint          NOT NULL,
   
   foreign key (srvid)
       references oegw_srv(id)
);

GRANT ALL ON oegw_srvicon TO oe;

CREATE TABLE oegw_client_history (
  id                    bigint          NOT NULL IDENTITY PRIMARY KEY,
  itid                  varchar(32)     NOT NULL,
  clientid_ext          int,
  status                varchar(1)      NOT NULL,
  status_date           timestamp
);

GRANT ALL ON oegw_client_history TO oe;

CREATE INDEX oegw_client_history_itid on oegw_client_history(itid);
CREATE INDEX oegw_client_history_external_id on oegw_client_history(clientid_ext);


/*****************************************************************************
*
* COPYRIGHT (C) 2004-2012 Ingenico SA
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
