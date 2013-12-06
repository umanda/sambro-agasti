ALTER TABLE `msg_alerts` ADD `visible` INT( 1 ) NOT NULL DEFAULT '1';
ALTER TABLE `msg_alerts` ADD `deactivate_dt` TIMESTAMP NULL;
ALTER TABLE `msg_alerts` ADD `web_enabled` INT( 1 ) NOT NULL DEFAULT '0';

/**
*
* File Upload
*/
DROP TABLE IF EXISTS msg_alert_files;
CREATE TABLE msg_alert_files (
alert_uuid VARCHAR(60) NOT NULL,
name VARCHAR(30) NOT NULL,
type VARCHAR(30) NOT NULL,
size INT NOT NULL,
content MEDIUMBLOB NOT NULL,
PRIMARY KEY(alert_uuid, name, type, size)
);

/**
This Sample data is available in dbcreate.sql.
* Messaging contact group categories
* Modules: msg 
* Last Edited: mifan@respere.com
*/
INSERT INTO field_options VALUES('opt_msg_group_category','non','None');
INSERT INTO field_options VALUES('opt_msg_group_category','team','Team');
INSERT INTO field_options VALUES('opt_msg_group_category','pers','Personal');
INSERT INTO field_options VALUES('opt_msg_group_category','dept','Department');
INSERT INTO field_options VALUES('opt_msg_group_category','org','Organization');
INSERT INTO field_options VALUES('opt_msg_group_category','communi','Community');
INSERT INTO field_options VALUES('opt_msg_group_category','cust','Customer');

/**
* Add sample data to the msg_people_group
*/
UPDATE `msg_people_group` SET `grp_type` = 'team', `grp_type_desc` = 'Team' WHERE `m_uuid` = 'r7l2msg-3';
UPDATE `msg_people_group` SET `grp_type` = 'team', `grp_type_desc` = 'Team' WHERE `m_uuid` = 'r7l2msg-20';
UPDATE `msg_people_group` SET `grp_type` = 'team', `grp_type_desc` = 'Team' WHERE `m_uuid` = 'r7l2msg-21';
UPDATE `msg_people_group` SET `grp_type` = 'team', `grp_type_desc` = 'Team' WHERE `m_uuid` = 'r7l2msg-22';
UPDATE `msg_people_group` SET `grp_type` = 'team', `grp_type_desc` = 'Team' WHERE `m_uuid` = 'r7l2msg-23';
UPDATE `msg_people_group` SET `grp_type` = 'team', `grp_type_desc` = 'Team' WHERE `m_uuid` = 'r7l2msg-24';
UPDATE `msg_people_group` SET `grp_type` = 'team', `grp_type_desc` = 'Team' WHERE `m_uuid` = 'r7l2msg-25';
UPDATE `msg_people_group` SET `grp_type` = 'team', `grp_type_desc` = 'Team' WHERE `m_uuid` = 'r7l2msg-26';
UPDATE `msg_people_group` SET `grp_type` = 'team', `grp_type_desc` = 'Team' WHERE `m_uuid` = 'r7l2msg-31';
UPDATE `msg_people_group` SET `grp_type` = 'team', `grp_type_desc` = 'Team' WHERE `m_uuid` = 'r7l2msg-32';

