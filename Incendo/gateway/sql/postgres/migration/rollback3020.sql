\connect oegw oe

ALTER TABLE OEGW_SESSION DROP COLUMN SERVICE_NAME;
ALTER TABLE OEGW_REQUEST DROP COLUMN SERVICE_NAME;

ALTER TABLE OEGW_SRV DROP COLUMN POST_CONV;

ALTER TABLE OEGW_SRVSUBSCR DROP COLUMN PROFILE;
ALTER TABLE OEGW_SRVSUBSCR DROP COLUMN STARTUP;

DROP TABLE IF EXISTS CFGSRV_SERVICE_CFG_ASSIGN;
CREATE TABLE CFGSRV_SERVICE_CFG_ASSIGN (
  ID BIGINT NOT NULL,
  CONFIG_ID BIGINT NOT NULL,
  CONFIG_TYPE CHAR(1) NOT NULL,
  SERVICE VARCHAR(255) NOT NULL,
  ASSIGNMENT_DATE DATE NOT NULL
);

COMMENT ON COLUMN CFGSRV_SERVICE_CFG_ASSIGN.CONFIG_ID IS 'key to CFGSRV_SERVICE_CONFIG.';
COMMENT ON COLUMN CFGSRV_SERVICE_CFG_ASSIGN.CONFIG_TYPE IS '"M" for margard etc - 3 entries max for each service.';
COMMENT ON COLUMN CFGSRV_SERVICE_CFG_ASSIGN.SERVICE IS 'Service name.';
COMMENT ON COLUMN CFGSRV_SERVICE_CFG_ASSIGN.ASSIGNMENT_DATE IS 'Assignment creation date.';

DROP SEQUENCE IF EXISTS srv_cfg_assign_seq;
CREATE SEQUENCE srv_cfg_assign_seq
        INCREMENT BY 1 START WITH 1 NO MAXVALUE
        OWNED BY CFGSRV_SERVICE_CFG_ASSIGN.ID;
ALTER TABLE CFGSRV_SERVICE_CFG_ASSIGN
        ALTER COLUMN ID SET DEFAULT NEXTVAL('srv_cfg_assign_seq');

ALTER TABLE CFGSRV_SERVICE_CFG_ASSIGN
        ADD CONSTRAINT CFGSRV_SERVICE_CFG_ASSIGN_PK
                PRIMARY KEY (ID);

ALTER TABLE CFGSRV_SERVICE_CFG_ASSIGN OWNER TO oe;
ALTER TABLE srv_cfg_assign_seq OWNER TO oe;

insert into cfgsrv_service_cfg_assign (config_id,config_type,service,assignment_date)
select profile.magcard_id, 'M', service.srvid,a.assignment_date from oegw_srv service,cfgsrv_profile profile,cfgsrv_service_profile_assign a 
where profile.name=a.profile and service.srvid=a.service and profile.magcard_id != -1;

insert into cfgsrv_service_cfg_assign (config_id,config_type,service,assignment_date)
select profile.iccemv_id, 'E', service.srvid,a.assignment_date from oegw_srv service,cfgsrv_profile profile,cfgsrv_service_profile_assign a 
where profile.name=a.profile and service.srvid=a.service and profile.iccemv_id != -1;

insert into cfgsrv_service_cfg_assign (config_id,config_type,service,assignment_date)
select profile.hcl_id, 'H', service.srvid,a.assignment_date from oegw_srv service,cfgsrv_profile profile,cfgsrv_service_profile_assign a 
where profile.name=a.profile and service.srvid=a.service and profile.hcl_id != -1;

insert into cfgsrv_service_cfg_assign (config_id,config_type,service,assignment_date)
select profile.varlib_id, 'S', service.srvid,a.assignment_date from oegw_srv service,cfgsrv_profile profile,cfgsrv_service_profile_assign a 
where profile.name=a.profile and service.srvid=a.service and profile.varlib_id != -1;

DROP TABLE IF EXISTS CFGSRV_SERVICE_PROFILE_ASSIGN;
DROP TABLE IF EXISTS CFGSRV_PROFILE CASCADE;
DROP SEQUENCE IF EXISTS CFGSRV_PROFILE_SEQ;

ALTER TABLE CFGSRV_CARD_PROVIDERS DROP COLUMN ACQUIRER_ID;
ALTER TABLE CFGSRV_CARD_PROVIDERS DROP COLUMN MERCHANT_CATEGORY_CODE;
ALTER TABLE CFGSRV_CARD_PROVIDERS DROP COLUMN TRANS_CUR_EXP;
ALTER TABLE CFGSRV_CARD_PROVIDERS DROP COLUMN TRANS_REF_CUR;
ALTER TABLE CFGSRV_CARD_PROVIDERS DROP COLUMN TRANS_REF_CUR_EXP;
ALTER TABLE CFGSRV_CARD_PROVIDERS DROP COLUMN MERCHANT_ID;

ALTER TABLE CFGSRV_EMV_CARD_APPLICATIONS DROP COLUMN TERMINAL_CAPABILITIES;
ALTER TABLE CFGSRV_EMV_CARD_APPLICATIONS DROP COLUMN ADD_TERMINAL_CAPABILITIES;
ALTER TABLE CFGSRV_EMV_CARD_APPLICATIONS DROP COLUMN TERMINAL_TYPE;

DELETE FROM OEGW_DB_VERSION WHERE MAIN=3 AND MAJOR=0 AND MINOR=2;

INSERT INTO OEGW_DB_VERSION
        (MAIN, MAJOR, MINOR, BUILD)
        VALUES (3,0,1,'0');