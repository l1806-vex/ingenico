\connect oegw oe
ALTER TABLE OEGW_SESSION ADD COLUMN SERVICE_NAME VARCHAR(32);
ALTER TABLE OEGW_REQUEST ADD COLUMN SERVICE_NAME VARCHAR(32);

ALTER TABLE OEGW_SRV ADD COLUMN POST_CONV BOOLEAN DEFAULT false;

ALTER TABLE OEGW_SRVSUBSCR ADD COLUMN STARTUP BOOLEAN DEFAULT false;
ALTER TABLE OEGW_SRVSUBSCR ADD COLUMN PROFILE BIGINT default NULL;

ALTER TABLE CFGSRV_CARD_PROVIDERS ADD COLUMN ACQUIRER_ID 		VARCHAR(12)	NOT NULL DEFAULT '7361470000';
ALTER TABLE CFGSRV_CARD_PROVIDERS ADD COLUMN MERCHANT_CATEGORY_CODE	VARCHAR(4)	NOT NULL DEFAULT '12';
ALTER TABLE CFGSRV_CARD_PROVIDERS ADD COLUMN TRANS_CUR_EXP		VARCHAR(4)	NOT NULL DEFAULT 'Ag==';
ALTER TABLE CFGSRV_CARD_PROVIDERS ADD COLUMN TRANS_REF_CUR		VARCHAR(4)	NOT NULL DEFAULT '5600';
ALTER TABLE CFGSRV_CARD_PROVIDERS ADD COLUMN TRANS_REF_CUR_EXP		VARCHAR(2)	NOT NULL DEFAULT '02';
ALTER TABLE CFGSRV_CARD_PROVIDERS ADD COLUMN MERCHANT_ID		VARCHAR(15)	NOT NULL DEFAULT '';

ALTER TABLE CFGSRV_EMV_CARD_APPLICATIONS ADD COLUMN TERMINAL_CAPABILITIES VARCHAR(8) NOT NULL DEFAULT '4PDI';
ALTER TABLE CFGSRV_EMV_CARD_APPLICATIONS ADD COLUMN ADD_TERMINAL_CAPABILITIES VARCHAR(8) NOT NULL DEFAULT '/4DwoAE=';
ALTER TABLE CFGSRV_EMV_CARD_APPLICATIONS ADD COLUMN TERMINAL_TYPE VARCHAR(2) NOT NULL DEFAULT '22';

DROP TABLE IF EXISTS CFGSRV_PROFILE CASCADE;
CREATE TABLE CFGSRV_PROFILE (
  ID                 BIGINT             NOT NULL,--SERIAL with explicit SEQUENCE 
  MAGCARD_ID BIGINT             NOT NULL,
  ICCEMV_ID BIGINT             NOT NULL,
  VARLIB_ID BIGINT             NOT NULL,
  HCL_ID BIGINT			NOT NULL,
  NAME VARCHAR(255)
);
DROP SEQUENCE IF EXISTS CFGSRV_PROFILE_SEQ;
CREATE SEQUENCE CFGSRV_PROFILE_SEQ
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_PROFILE.ID;
ALTER TABLE CFGSRV_PROFILE
        ALTER COLUMN ID SET DEFAULT NEXTVAL('CFGSRV_PROFILE_SEQ');

ALTER TABLE CFGSRV_PROFILE
        ADD CONSTRAINT CFGSRV_PROFILE_PK
                PRIMARY KEY (ID);
CREATE UNIQUE INDEX CFGSRV_PROFILE_NAME ON CFGSRV_PROFILE(NAME);
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

ALTER TABLE CFGSRV_PROFILE OWNER TO oe;
ALTER TABLE CFGSRV_PROFILE_SEQ OWNER TO oe;
ALTER TABLE CFGSRV_SERVICE_PROFILE_ASSIGN OWNER TO oe;
ALTER TABLE srv_profile_assign_seq OWNER TO oe;


insert into cfgsrv_service_cfg_assign (config_id,config_type,service,assignment_date) 
select distinct -1,'M',a.service,a.assignment_date from cfgsrv_service_cfg_assign a
where not exists (select * from cfgsrv_service_cfg_assign where service=a.service and config_type='M');

insert into cfgsrv_service_cfg_assign (config_id,config_type,service,assignment_date) 
select distinct -1,'E',a.service,a.assignment_date from cfgsrv_service_cfg_assign a
where not exists (select * from cfgsrv_service_cfg_assign where service=a.service and config_type='E');

insert into cfgsrv_service_cfg_assign (config_id,config_type,service,assignment_date) 
select distinct -1,'H',a.service,a.assignment_date from cfgsrv_service_cfg_assign a
where not exists (select * from cfgsrv_service_cfg_assign where service=a.service and config_type='H');

insert into cfgsrv_service_cfg_assign (config_id,config_type,service,assignment_date) 
select distinct -1,'S',a.service,a.assignment_date from cfgsrv_service_cfg_assign a
where not exists (select * from cfgsrv_service_cfg_assign where service=a.service and config_type='S');

insert into cfgsrv_profile(name,magcard_id,iccemv_id,varlib_id,hcl_id)
select distinct service.srvid,assign1.config_id,assign2.config_id,assign3.config_id,assign4.config_id
from oegw_srv service, cfgsrv_service_cfg_assign assign1, cfgsrv_service_cfg_assign assign2, cfgsrv_service_cfg_assign assign3, cfgsrv_service_cfg_assign assign4
where service.srvid=assign1.service and assign1.config_type='M' 
and service.srvid=assign2.service and assign2.config_type='E' 
and service.srvid=assign3.service and assign3.config_type='S' 
and service.srvid=assign4.service and assign4.config_type='H';

insert into CFGSRV_SERVICE_PROFILE_ASSIGN(profile, service, assignment_date, is_default)
select profile.name,service.srvid,now(),true from cfgsrv_profile profile, oegw_srv service where profile.name=service.srvid; 

DROP TABLE IF EXISTS CFGSRV_SERVICE_CFG_ASSIGN;

DELETE FROM OEGW_DB_VERSION;

INSERT INTO OEGW_DB_VERSION
        (MAIN, MAJOR, MINOR, BUILD)
        VALUES (3,0,2,'0');