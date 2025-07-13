/*==============================================================*/
-- oegwwebuser_seq for id:
INSERT INTO web_users
        (name, login, passwd, passwd_encrypt, passwd_changed, status)
        VALUES ('Administrator','admin','Adm1nist', NULL, CURRENT_DATE, 'E');

/*==============================================================*/

-- oegwwebusergroup_seq for id:
INSERT INTO web_user_group
        (user_id, group_id)
        SELECT u.id, g.id
        FROM web_users u, web_groups g
        WHERE u.login = 'admin'
        AND g.name = 'admin';

/*==============================================================*/

INSERT INTO web_user_pass_hist (user_id, passwd_encrypt) VALUES (1, 'kF8iwqf6EFmHniI96IQSBA==');

INSERT INTO web_srv VALUES (1,'admin','Actions Page (admin). Page contains list of available application resources',10);
INSERT INTO web_srv VALUES (2,'error','Error Page (error), Page contains error message. Shown in case of application error occurs.',10);
INSERT INTO web_srv VALUES (3,'gridConfig','Grid Configuration Page (gridConfig). Valid only for resources with datagrid. Sets what fields to display and number of rows in datagrid.',10);
INSERT INTO web_srv VALUES (4,'userList','User List Page (userList). Page contains list of available users',10);
INSERT INTO web_srv VALUES (5,'groupList','Group List Page (groupList). Page contains list of available user groups',10);
INSERT INTO web_srv VALUES (6,'userEdit','User Edit Page (userEdit). You can change login, password and privileges of defined user.',10);
INSERT INTO web_srv VALUES (7,'groupEdit','Group Edit Page (groupEdit). You can change name, description and privileges of defined group.',10);
INSERT INTO web_srv VALUES (8,'addUser','Add User Page (addUser). Page that allows you to add a new user and specify privileges.',10);
INSERT INTO web_srv VALUES (9,'addGroup','Add Group Page (addGroup). Page that allows you to add a new group and specify privileges.',10);
INSERT INTO web_srv VALUES (10,'dropUser','dropUser, The service that removes user from application.',10);
INSERT INTO web_srv VALUES (11,'dropGroup','dropGroup, The service that removes group from application.',10);
INSERT INTO web_srv VALUES (13,'terminalView','Terminal View Page (terminalView). Terminal edit page.',10);
INSERT INTO web_srv VALUES (14,'terminalQueryResult','Terminals Page (terminalQueryResult). Page contains list of available terminals specified by search criteria.',10);
INSERT INTO web_srv VALUES (15,'terminalQuery','Terminal Query Page (terminalQuery). Terminal search page.',10);
INSERT INTO web_srv VALUES (16,'deleteTerminal','deleteTerminal, The service that deletes defined terminal from the database.',10);
INSERT INTO web_srv VALUES (17,'modifyTerminals','Modify Terminals Page (modifyTerminals). The service that modifies bulk of terminals according to choosen criteria.',10);
INSERT INTO web_srv VALUES (18,'addTerminal','Add Terminal Page (addTerminal). The service that adds a new terminal to database.',10);
INSERT INTO web_srv VALUES (19,'addTerminals','Add Terminals Page (addTerminals). The service that provides bulk terminal management.',10);
INSERT INTO web_srv VALUES (20,'sessionQuery','Session Query Page (sessionQuery). Session search page. Contains query criteria.',10);
INSERT INTO web_srv VALUES (21,'sessionQueryResult','Sessions Page (sessionQueryResult). Session query result page. Contains results of session query.',10);
INSERT INTO web_srv VALUES (23,'sessionRequestView','Session Request Page (sessionRequestView). List of session requests/replays of specified session.',10);
INSERT INTO web_srv VALUES (24,'requestView','requestView, Request details view page.',10);
INSERT INTO web_srv VALUES (25,'replyView','replyView, Replay details view page.',10);
INSERT INTO web_srv VALUES (26,'configuration','Gateway Configuration Page (configuration). Configuration page. OEGW server can be stopped or restarted on another port from here.',10);
INSERT INTO web_srv VALUES (27,'configProp','Gateway Configuration Details Page (configProp). Configuration details Page. Contains OEGW configuration properties.',10);
INSERT INTO web_srv VALUES (28,'statsView','Gateway Statistics Page (statsView). The service presents OEGW runtime statistics.',10);
INSERT INTO web_srv VALUES (29,'deleteSession','deleteSession, The service that deletes defined terminal session from the database.',10);
INSERT INTO web_srv VALUES (30,'deleteTerminals','Delete Terminals Page (deleteTerminals). Bulk terminal deletion.',10);
INSERT INTO web_srv VALUES (31,'schemeView','Scheme View Page (schemeView). Terminal configuration page. List of card schemes.',1000);
INSERT INTO web_srv VALUES (32,'iinsView','IINs View Page (iinsView). Terminal configuration page. List of IINS.',1000);
INSERT INTO web_srv VALUES (34,'ttlsView','TTLs View Page (ttlsView). Terminal configuration page. List of TTLS.',1000);
INSERT INTO web_srv VALUES (35,'addConfig','Add Config Page (addConfig). Load new terminal configuration from a file.',10);
INSERT INTO web_srv VALUES (36,'cpView','Card Providers View Page (cpView). Terminal configuration page. List of card providers.',1000);
INSERT INTO web_srv VALUES (37,'emvView','EMV Card Applications View Page (emvView). Terminal configuration page. List of EMV card applications.',1000);
INSERT INTO web_srv VALUES (38,'rsaView','RSA Keys View Page (rsaView). Terminal configuration page. List of RSA keys.',1000);
INSERT INTO web_srv VALUES (39,'baseView','baseView, Common page that is used by various actions for displaying information.',10);
INSERT INTO web_srv VALUES (40,'logout','logout, Logout defined user',10);
INSERT INTO web_srv VALUES (41,'eventView','Events View Page (eventView). OEGW events. List of application events.',100);
INSERT INTO web_srv VALUES (42,'about','About Page (about). About page.',100);
INSERT INTO web_srv VALUES (43,'httpResponseView','httpResponseView, HTTP response details view page.',100);
INSERT INTO web_srv VALUES (44,'configDump','configDump, Page containing list of terminal configuration dumps.',100);
INSERT INTO web_srv VALUES (45,'messageView','messageView, Page displaying message.',100);

/*==============================================================*/

INSERT INTO web_srv_user
(id, srv_id, type, user_id)
SELECT s.id, s.id, 2, u.id --Note, web_srv.id value is used for web_srv_user.id
FROM web_srv s, web_users u
WHERE u.login = 'admin'
AND s.id NOT IN (12, 22, 33);

/*==============================================================*/

INSERT INTO web_srvfield VALUES ( 4,  2, 'LOGIN', 'User login', 'Y');
INSERT INTO web_srvfield VALUES ( 4,  3, 'EDITACTION', 'Edit action', 'Y');
INSERT INTO web_srvfield VALUES ( 4,  4, 'DELACTION', 'Delete action', 'Y');
INSERT INTO web_srvfield VALUES ( 4,  1, 'NAME', 'User name', 'Y');

INSERT INTO web_srvfield VALUES ( 5,  4, 'EDITACTION', 'Edit action', 'Y');
INSERT INTO web_srvfield VALUES ( 5,  1, 'NAME', 'Group name', 'Y');
INSERT INTO web_srvfield VALUES ( 5,  2, 'DESCR', 'Group description', 'Y');
INSERT INTO web_srvfield VALUES ( 5,  3, 'USERSACTION', 'Show users of this group', 'Y');
INSERT INTO web_srvfield VALUES ( 5,  5, 'DELACTION', 'Delete action', 'Y');

INSERT INTO web_srvfield VALUES (14,  1, 'ID', 'Terminal ID', 'Y');
INSERT INTO web_srvfield VALUES (14,  2, 'ITID', 'Ingenico terminal ID', 'Y');
INSERT INTO web_srvfield VALUES (14,  3, 'STATUS', 'Status', 'Y');
INSERT INTO web_srvfield VALUES (14,  4, 'TRACED', 'Traced mode', 'Y');
INSERT INTO web_srvfield VALUES (14,  5, 'SHOWSESSIONS', 'Shows sessions of this terminal', 'Y');
INSERT INTO web_srvfield VALUES (14,  6, 'DELETETERMINAL', 'Deletes terminal', 'Y');
INSERT INTO web_srvfield VALUES (14,  7, 'SERIAL_NMB', 'Terminal serial number', 'Y');
INSERT INTO web_srvfield VALUES (14,  8, 'PIN', 'Security Key', 'Y');
INSERT INTO web_srvfield VALUES (14,  9, 'VALID_DATE', 'Expiry date', 'Y');
INSERT INTO web_srvfield VALUES (14, 11, 'PART_NMB', 'Terminal part number', 'Y');

INSERT INTO web_srvfield VALUES (21,  1, 'SID', 'Session id', 'Y');
INSERT INTO web_srvfield VALUES (21,  2, 'ITID', 'Ingenico terminal ID', 'Y');
INSERT INTO web_srvfield VALUES (21,  3, 'STARTDATE', 'Session start time', 'Y');
INSERT INTO web_srvfield VALUES (21,  4, 'STATUS', 'Session status', 'Y');
INSERT INTO web_srvfield VALUES (21,  5, 'DURATION', 'Session duration', 'Y');
INSERT INTO web_srvfield VALUES (21,  6, 'SPEED', 'Data transfer speed', 'Y');
INSERT INTO web_srvfield VALUES (21,  7, 'TRACED', 'Traced mode,  link to session details', 'Y');
INSERT INTO web_srvfield VALUES (21,  8, 'CLIENT_IP', 'Client host ip address', 'Y');

INSERT INTO web_srvfield VALUES (23,  1, 'STARTDATE', 'Session request start time', 'Y');
INSERT INTO web_srvfield VALUES (23,  2, 'DURATION', 'Session request duration', 'Y');
INSERT INTO web_srvfield VALUES (23,  3, 'URI', 'Session request URI', 'Y');
INSERT INTO web_srvfield VALUES (23,  4, 'STATUS', 'Session request status', 'Y');
INSERT INTO web_srvfield VALUES (23,  5, 'REQUEST', 'Link to request details', 'Y');
INSERT INTO web_srvfield VALUES (23,  6, 'REPLY', 'Link to reply details', 'Y');
INSERT INTO web_srvfield VALUES (23,  7, 'HTTP_RESPONSE', 'Link to http response', 'Y');

INSERT INTO web_srvfield VALUES (31,  1, 'ARRAY_INDEX', 'Index in array', 'Y');
INSERT INTO web_srvfield VALUES (31,  2, 'NAME', 'Sheme name', 'Y');
INSERT INTO web_srvfield VALUES (31,  3, 'KEY_', 'Sheme key', 'Y');
INSERT INTO web_srvfield VALUES (31,  4, 'ACTIVE', 'Defines if the scheme is active', 'Y');
INSERT INTO web_srvfield VALUES (31,  5, 'FLOOR_LIMIT', 'Floor limit', 'Y');
INSERT INTO web_srvfield VALUES (31,  6, 'VALIDITY', 'Validity', 'Y');
INSERT INTO web_srvfield VALUES (31,  7, 'SWIPE_ALLOWED', 'Card swipe allowed', 'Y');
INSERT INTO web_srvfield VALUES (31,  8, 'KEY_ALLOWED', 'Key entry transactions allowed', 'Y');

INSERT INTO web_srvfield VALUES (32,  1, 'ARRAY_INDEX', 'Index in array', 'Y');
INSERT INTO web_srvfield VALUES (32,  2, 'KEY_', 'IIN key', 'Y');
INSERT INTO web_srvfield VALUES (32,  3, 'ACTIVE', 'Bank active flag', 'Y');
INSERT INTO web_srvfield VALUES (32,  4, 'RANGE_MIN', 'Low order IIN', 'Y');
INSERT INTO web_srvfield VALUES (32,  5, 'RANGE_MAX', 'High order IIN', 'Y');
INSERT INTO web_srvfield VALUES (32,  6, 'TTL_PTR', 'Pointer to track 2 layout', 'Y');
INSERT INTO web_srvfield VALUES (32,  7, 'CS_PTR', 'Pointer to card scheme table entry', 'Y');

INSERT INTO web_srvfield VALUES (34,  1, 'ARRAY_INDEX', 'Index in array', 'Y');
INSERT INTO web_srvfield VALUES (34,  2, 'KEY_', 'TTL key', 'Y');
INSERT INTO web_srvfield VALUES (34,  3, 'PAN', 'Pan length', 'Y');
INSERT INTO web_srvfield VALUES (34,  4, 'INL', 'Issue number length', 'Y');
INSERT INTO web_srvfield VALUES (34,  5, 'INP', 'Issue number position', 'Y');
INSERT INTO web_srvfield VALUES (34,  6, 'SCP', 'Service code position', 'Y');
INSERT INTO web_srvfield VALUES (34,  7, 'SDF', 'Start date format', 'Y');
INSERT INTO web_srvfield VALUES (34,  8, 'EDP', 'Expiry date offset from FS', 'Y');
INSERT INTO web_srvfield VALUES (34,  9, 'LCR', 'Luhn check required', 'Y');
INSERT INTO web_srvfield VALUES (34, 10, 'EDF', 'Expiry date format', 'Y');

INSERT INTO web_srvfield VALUES (36,  1, 'ARRAY_INDEX', 'Index in array', 'Y');
INSERT INTO web_srvfield VALUES (36,  2, 'KEY_', 'Card provider key', 'Y');
INSERT INTO web_srvfield VALUES (36,  3, 'FLOOR_LIMIT', 'Transaction floor limit', 'Y');
INSERT INTO web_srvfield VALUES (36,  4, 'THRESHOLD', 'Threshold', 'Y');
INSERT INTO web_srvfield VALUES (36,  5, 'TAC_DENIAL', 'TAC denial', 'Y');
INSERT INTO web_srvfield VALUES (36,  6, 'TAC_ONLINE', 'TAC online', 'Y');
INSERT INTO web_srvfield VALUES (36,  7, 'TAC_DEFAULT', 'TAC default', 'Y');
INSERT INTO web_srvfield VALUES (36,  8, 'DEFAULT_TDOL', 'default TDOL', 'Y');
INSERT INTO web_srvfield VALUES (36,  9, 'DEFAULT_DDOL', 'default DDOL', 'Y');
INSERT INTO web_srvfield VALUES (36, 10, 'TARGET_PERCENTAGE', 'Target percentage', 'Y');
INSERT INTO web_srvfield VALUES (36, 11, 'MAXIMUM_TARGET_PERCENTAGE', 'Maximum target percentage', 'Y');
INSERT INTO web_srvfield VALUES (36, 12, 'TERMINAL_COUNTRY_CODE', 'Terminal country code', 'Y');
INSERT INTO web_srvfield VALUES (36, 13, 'TXN_CURRENCY_CODE', 'Transaction currency code', 'Y');

INSERT INTO web_srvfield VALUES (37,  1, 'ARRAY_INDEX', 'Index in array', 'Y');
INSERT INTO web_srvfield VALUES (37,  2, 'KEY_', 'EMV key', 'Y');
INSERT INTO web_srvfield VALUES (37,  3, 'CARD_APP_LIVE_FLAG', 'Indicates that emv application is active', 'Y');
INSERT INTO web_srvfield VALUES (37,  4, 'CARD_PROVIDER_KEY', 'Key in card providers table', 'Y');
INSERT INTO web_srvfield VALUES (37,  5, 'AID', 'Application identifier', 'Y');
INSERT INTO web_srvfield VALUES (37,  6, 'TRMD', 'Terminal risk management data', 'Y');
INSERT INTO web_srvfield VALUES (37,  7, 'PRIORITY_INDEX', 'application priority', 'Y');
INSERT INTO web_srvfield VALUES (37,  8, 'SELECTION_APPLI_FLAG', 'Selection application flag', 'Y');

INSERT INTO web_srvfield VALUES (38,  1, 'ARRAY_INDEX', 'Index in array', 'Y');
INSERT INTO web_srvfield VALUES (38,  2, 'KEY_', 'RSA key', 'Y');
INSERT INTO web_srvfield VALUES (38,  3, 'KEY_INDICATOR', 'Number of RSA key in the card and in authority certificate', 'Y');
INSERT INTO web_srvfield VALUES (38,  4, 'RID', 'Row ID', 'Y');
INSERT INTO web_srvfield VALUES (38,  5, 'KEY_DATA', 'RSA key', 'Y');
INSERT INTO web_srvfield VALUES (38,  6, 'EXPONENT', 'Exponent of RSA key', 'Y');

INSERT INTO web_srvfield VALUES (41,  1, 'STARTDATE', 'Event start date', 'Y');
INSERT INTO web_srvfield VALUES (41,  2, 'EVENT', 'Event name', 'Y');
INSERT INTO web_srvfield VALUES (41,  3, 'DESCR', 'Event description', 'Y');
INSERT INTO web_srvfield VALUES (41,  4, 'STATUS', 'Event status', 'Y');

INSERT INTO oegw_db_version
        (main, major, minor, build)
        VALUES (3,1,5,'0');

INSERT INTO oegw_activity_log
	(event_time,event_severity,event_status,activity,event_originator,event_originator_ip,source_component,log_message)
	VALUES(NOW() AT TIME ZONE 'UTC','INFO','Completed','Init','','','','Postgres DB recreated successfully');

/***************************************************************************** 
*
* COPYRIGHT (C) 2004-2006 Ingenico UK
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
