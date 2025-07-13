BEGIN;

/*==============================================================*/

-- btmlpa_terminal_seq for id:
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES ('87183710',  '1');
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES ('87183711',  '2');
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES ('87183712',  '3');
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES ('87183713',  '4');
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES ('87183714',  '5');
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES ('87183715',  '6');
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES ('12345678',  '7');
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES (     '100',  '8');
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES (     '101',  '9');
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES (     '102', '10');
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES (     '103', '11');
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES (     '104', '12');
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES (     '105', '13');
INSERT INTO btmlpa_terminal (oe_itid, apacs_tid) VALUES (     '106', '14');

/*==============================================================*/
-- web_users_seq for id:
INSERT INTO web_users
        (name, login, passwd)
        VALUES ('Administrator','admin','admin');

INSERT INTO web_users
        (name, login, passwd)
        VALUES ('Dmitry Ivanov','di','di');

INSERT INTO web_users 
        (name, login, passwd)
        VALUES ('Sergei Lukashin','sl','sl');

/*==============================================================*/

-- web_groups_seq for id:
INSERT INTO web_groups
        (name, descr)
        VALUES ('admin','Administration group');

INSERT INTO web_groups
        (name, descr)
        VALUES ('helpdesk','Helpdesk people');

INSERT INTO web_groups
        (name, descr)
        VALUES ('manager','Sale managers');

/*==============================================================*/

-- oegwwebusergroup_seq for id:
INSERT INTO web_user_group
        (user_id, group_id)
        -- user 'admin' in 'admin' and 'manager' group(s):
        SELECT u.id, g.id
        FROM web_users u, web_groups g
        WHERE u.login = 'admin'
        AND (g.name = 'admin' OR g.name = 'manager')
        UNION
        -- user 'di' in 'admin' group(s):
        SELECT u.id, g.id
        FROM web_users u, web_groups g
        WHERE u.login = 'di'
        AND g.name = 'admin';

/*==============================================================*/

INSERT INTO web_srv VALUES ( 1,'admin','Actions Page (admin). Page contains list of available application resources',10);
INSERT INTO web_srv VALUES ( 2,'error','Error Page (error), Page contains error message. Shown in case of application error occurs.',10);
INSERT INTO web_srv VALUES ( 3,'gridConfig','Grid Configuration Page (gridConfig). Valid only for resources with datagrid. Sets what fields to display and number of rows in datagrid.',10);
INSERT INTO web_srv VALUES ( 4,'userList','User List Page (userList). Page contains list of available users',10);
INSERT INTO web_srv VALUES ( 5,'groupList','Group List Page (groupList). Page contains list of available user groups',10);
INSERT INTO web_srv VALUES ( 6,'userEdit','User Edit Page (userEdit). You can change login, password and privileges of defined user.',10);
INSERT INTO web_srv VALUES ( 7,'groupEdit','Group Edit Page (groupEdit). You can change name, description and privileges of defined group.',10);
INSERT INTO web_srv VALUES ( 8,'addUser','Add User Page (addUser). Page that allows you to add a new user and specify privileges.',10);
INSERT INTO web_srv VALUES ( 9,'addGroup','Add Group Page (addGroup). Page that allows you to add a new group and specify privileges.',10);
INSERT INTO web_srv VALUES (10,'dropUser','dropUser, The service that removes user from application.',10);
INSERT INTO web_srv VALUES (11,'dropGroup','dropGroup, The service that removes group from application.',10);
INSERT INTO web_srv VALUES (12,'terminalView','Terminal View Page (terminalView). Terminal edit page.',10);
INSERT INTO web_srv VALUES (13,'terminalQueryResult','Terminals Page (terminalQueryResult). Page contains list of available terminals.',10);
-- No 14
INSERT INTO web_srv VALUES (15,'deleteTerminal','deleteTerminal, The service that deletes defined terminal from the database.',10);
INSERT INTO web_srv VALUES (16,'addTerminal','Add Terminal Page (addTerminal). The service that adds a new terminal to database.',10);
INSERT INTO web_srv VALUES (17,'addTerminals','Add Terminals Page (addTerminals). The service that provides bulk terminal management.',10);
-- No 18
INSERT INTO web_srv VALUES (19,'sessionQueryResult','Sessions Page (sessionQueryResult). Contains list of sessions.',10);
INSERT INTO web_srv VALUES (20,'deleteSession','deleteSession, The service that deletes defined terminal session from the database.',10);
-- No 21
INSERT INTO web_srv VALUES (22,'detailsView','detailsView, Transaction Details',10);
INSERT INTO web_srv VALUES (23,'logout','logout, Logout defined user',10);
INSERT INTO web_srv VALUES (24,'about','About Page (about). About page.',10);

/*==============================================================*/

INSERT INTO web_srv_user
(id, srv_id, type, user_id)
SELECT s.id, s.id, 2, u.id --Note, web_srv.id value is used for web_srv_user.id
FROM web_srv s, web_users u
WHERE u.login = 'admin';

/*==============================================================*/

INSERT INTO web_srvfield VALUES ( 4, 1,'NAME','User name','Y');
INSERT INTO web_srvfield VALUES ( 4, 2,'LOGIN','User login','Y');
INSERT INTO web_srvfield VALUES ( 4, 3,'EDITACTION','Edit action','Y');
INSERT INTO web_srvfield VALUES ( 4, 4,'DELACTION','Delete action','Y');

INSERT INTO web_srvfield VALUES ( 5, 1,'NAME','Group name','Y');
INSERT INTO web_srvfield VALUES ( 5, 2,'DESCR','Group description','Y');
INSERT INTO web_srvfield VALUES ( 5, 3,'USERACTION','Show users of this group','Y');
INSERT INTO web_srvfield VALUES ( 5, 4,'EDITACTION','Edit action','Y');
INSERT INTO web_srvfield VALUES ( 5, 5,'DELACTION','Delete action','Y');

INSERT INTO web_srvfield VALUES (13, 1,'ID','Terminal ID','Y');
INSERT INTO web_srvfield VALUES (13, 2,'OE_ITID','OpenEstate Terminal ID','Y');
INSERT INTO web_srvfield VALUES (13, 3,'APACS_TID','APACS Terminal ID','Y');
INSERT INTO web_srvfield VALUES (13, 4,'SHOWSESSIONS','Show session list','Y');
INSERT INTO web_srvfield VALUES (13, 5,'DELETETERMINAL','Delete terminal','Y');

INSERT INTO web_srvfield VALUES (19, 1,'ID','Transaction ID','Y');
INSERT INTO web_srvfield VALUES (19, 2,'TXN_STARTED','Transaction start date','Y');
INSERT INTO web_srvfield VALUES (19, 3,'OE_ITID','OpenEstate Terminal ID','Y');
INSERT INTO web_srvfield VALUES (19, 4,'PAN','Card PAN','Y');
INSERT INTO web_srvfield VALUES (19, 5,'TYPE','Transaction type','Y');
INSERT INTO web_srvfield VALUES (19, 6,'STATE','Transaction state','Y');
INSERT INTO web_srvfield VALUES (19, 7,'AMOUNT','Transaction Amount','Y');
INSERT INTO web_srvfield VALUES (19, 8,'AUTH_CODE','Authorisation code','Y');
INSERT INTO web_srvfield VALUES (19, 9,'TXN_DURATION','Transaction duration','Y');
INSERT INTO web_srvfield VALUES (19,10,'DETAILS','Transactoin details','Y');

COMMIT;

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