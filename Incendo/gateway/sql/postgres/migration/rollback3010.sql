\connect oegw oe

ALTER TABLE OEGW_CLIENT DROP COLUMN EFFECT_DATE;

ALTER TABLE OEGW_SESSION DROP COLUMN SENT;
ALTER TABLE OEGW_SESSION DROP COLUMN GETS;
ALTER TABLE OEGW_SESSION DROP COLUMN POSTS;
ALTER TABLE OEGW_SESSION DROP COLUMN GETS_RECEIVED;
ALTER TABLE OEGW_SESSION DROP COLUMN GETS_SENT;
ALTER TABLE OEGW_SESSION DROP COLUMN POSTS_RECEIVED;
ALTER TABLE OEGW_SESSION DROP COLUMN POSTS_SENT;
ALTER TABLE OEGW_SESSION DROP COLUMN FRMW_RECEIVED;
ALTER TABLE OEGW_SESSION DROP COLUMN FRMW_SENT;

ALTER TABLE OEGW_SRV DROP COLUMN HASH_CHECK;
ALTER TABLE OEGW_SRVSUBSCR DROP COLUMN INHERITED;
ALTER TABLE OEGW_SRVSUBSCR DROP COLUMN PREVIOUS_ITID;

DROP TABLE OEGW_SRVSUBSCR_HISTORY CASCADE;

DROP INDEX OEGW_TXN_TXNID;

ALTER TABLE OEGW_TXN_MSG
        DROP CONSTRAINT OEGW_TXN_MSG_OEGW_TXN_FK;

ALTER TABLE OEGW_TXN_MSG RENAME COLUMN TXN_DB_ID TO TXN_ID;

ALTER TABLE OEGW_TXN_MSG
        ADD CONSTRAINT OEGW_TXN_MSG_OEGW_TXN_FK
                FOREIGN KEY (TXN_ID) REFERENCES OEGW_TXN (ID);

DROP INDEX OEGW_TXN_TXN_ID;
CREATE INDEX OEGW_TXN_TXN_ID ON OEGW_TXN_MSG(TXN_ID);


DROP TABLE OEGW_TERMRESERVE;

DROP TABLE OEGW_HASH CASCADE;

DELETE FROM OEGW_DB_VERSION WHERE MAIN=3 AND MAJOR=0 AND MINOR=1;

INSERT INTO OEGW_DB_VERSION
        (MAIN, MAJOR, MINOR, BUILD)
        VALUES (3,0,0,'0');