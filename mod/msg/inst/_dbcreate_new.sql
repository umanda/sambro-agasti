-- SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
-- SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
-- SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

-- CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci ;
-- USE `mydb`;

-- -----------------------------------------------------
-- Table `msg_alerts`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `msg_alerts` (
  `alert_uuid` INT NOT NULL ,
  `alert_name` VARCHAR(45) NOT NULL ,
  `file_type` VARCHAR(45) NULL , -- CAP/EDXL?
  `file_version` VARCHAR(45) NULL ,
  `author` VARCHAR(45) NULL ,
  `date_created` TIMESTAMP NULL ,
  `date_modified` TIMESTAMP NULL ,
  `type` VARCHAR(45) NULL ,
  `file` TEXT NULL ,
  PRIMARY KEY (`alert_uuid`) )
ENGINE = InnoDB
COMMENT = 'template records\n';


-- -----------------------------------------------------
-- Table `mydb`.`contact`
-- -----------------------------------------------------
--CREATE  TABLE IF NOT EXISTS `mydb`.`contact` (
  --`con_uuid` INT NOT NULL ,
  --`cont_mode` VARCHAR(45) NULL ,
  --`cont_value` VARCHAR(45) NULL ,
  --`deactivate_date` TIMESTAMP NULL ,
  --PRIMARY KEY (`con_uuid`) )
--ENGINE = MRG_MyISAM
--COMMENT = 'Contact Details\n	';


-- -----------------------------------------------------
-- Table `mydb`.`msg_grp_membership`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_grp_membership` (
  `person_id` INT NOT NULL ,
  `group_id` VARCHAR(45) NULL ,
  `grp_updated_date` TIMESTAMP NULL ,
  PRIMARY KEY (`person_id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`msg_sms_tools_log`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_sms_tools_log` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `type` VARCHAR(45) NULL ,
  `sent` TIMESTAMP NOT NULL ,
  `received` TIMESTAMP NULL ,
  `sender` VARCHAR(45) NULL ,
  `receiver` VARCHAR(45) NULL ,
  `status` VARCHAR(45) NULL ,
  `msgid` VARCHAR(45) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`messaging_group`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`messaging_group` (
  `group_uuid` VARCHAR(20) NULL DEFAULT NULL ,
  `group_name` VARCHAR(100) NULL DEFAULT NULL ,
  `address` VARCHAR(500) NULL DEFAULT NULL ,
  `mobile` VARCHAR(500) NULL DEFAULT NULL ,
  PRIMARY KEY (`group_uuid`) );


-- -----------------------------------------------------
-- Table `mydb`.`msg_people_contact`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_people_contact` (
  `m_uuid` VARCHAR(60) NOT NULL ,
  `name` VARCHAR(100) NOT NULL ,
  `full_name` VARCHAR(150) NULL DEFAULT NULL ,
  `address` VARCHAR(200) NULL DEFAULT NULL ,
  `primary_method` VARCHAR(6) NULL DEFAULT NULL ,
  `primary_mobile` INT(10) NULL DEFAULT NULL ,
  `secondary_mobile` INT(10) NULL DEFAULT NULL ,
  `primary_email` VARCHAR(25) NULL DEFAULT NULL ,
  `secondary_email` VARCHAR(25) NULL DEFAULT NULL ,
  `added_date` TIMESTAMP NOT NULL );


-- -----------------------------------------------------
-- Table `mydb`.`msg_people_group`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_people_group` (
  `m_uuid` VARCHAR(60) NOT NULL ,
  `grp_name` VARCHAR(15) NOT NULL ,
  `grp_des` VARCHAR(25) NULL DEFAULT NULL ,
  `grp_type` VARCHAR(50) NOT NULL ,
  `grp_type_desc` VARCHAR(100) NOT NULL ,
  `grp_created_date` TIMESTAMP NOT NULL );


-- -----------------------------------------------------
-- Table `mydb`.`msg_group_membership`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_group_membership` (
  `person_id` VARCHAR(60) NOT NULL ,
  `group_id` VARCHAR(60) NOT NULL ,
  `grp_updated_date` TIME NULL DEFAULT NULL );


-- -----------------------------------------------------
-- Table `mydb`.`msg_survey`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_survey` (
  `msg_id` VARCHAR(60) NOT NULL ,
  `survey_name` VARCHAR(100) NOT NULL ,
  `survey_key` VARCHAR(70) NOT NULL ,
  `recipient` VARCHAR(150) NOT NULL ,
  `message` VARCHAR(200) NULL DEFAULT NULL ,
  `send_time` TIME NULL DEFAULT NULL );


-- -----------------------------------------------------
-- Table `mydb`.`msg_survey_opt`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_survey_opt` (
  `msg_id` VARCHAR(60) NOT NULL ,
  `opt_num` VARCHAR(3) NOT NULL ,
  `opt_val` VARCHAR(30) NOT NULL );


-- -----------------------------------------------------
-- Table `mydb`.`msg_smstools_log`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_smstools_log` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `type` CHAR(16) NULL DEFAULT NULL ,
  `sent` DATETIME NULL DEFAULT NULL ,
  `received` DATETIME NULL DEFAULT NULL ,
  `sender` CHAR(32) NULL DEFAULT NULL ,
  `receiver` CHAR(32) NULL DEFAULT NULL ,
  `status` CHAR(3) NULL DEFAULT NULL ,
  `msgid` CHAR(3) NULL DEFAULT NULL ,
  PRIMARY KEY (`id`) );


-- -----------------------------------------------------
-- Table `mydb`.`msg_received_messages`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_received_messages` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `received` DATETIME NULL DEFAULT NULL ,
  `sender` CHAR(32) NULL DEFAULT NULL ,
  `status` CHAR(1) NULL DEFAULT NULL ,
  `message` VARCHAR(160) NULL DEFAULT NULL ,
  PRIMARY KEY (`id`) );


-- -----------------------------------------------------
-- Table `mydb`.`msg_stored_messages`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_stored_messages` (
  `m_uuid` VARCHAR(60) NOT NULL ,
  `message_header` VARCHAR(100) NOT NULL ,
  `message_content` VARCHAR(500) NULL DEFAULT NULL ,
  `message_creation_date` TIMESTAMP NOT NULL DEFAULT now() ,
  `message_creation_user_id` VARCHAR(60) NULL DEFAULT NULL ,
  PRIMARY KEY (`m_uuid`) );


-- -----------------------------------------------------
-- Table `mydb`.`msg_tpl_messages`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_tpl_messages` (
  `m_uuid` VARCHAR(60) NOT NULL ,
  `message_header` VARCHAR(100) NOT NULL ,
  `message_content` VARCHAR(500) NULL DEFAULT NULL ,
  `message_creation_date` TIMESTAMP NOT NULL DEFAULT now() ,
  `message_creation_user_id` VARCHAR(60) NULL DEFAULT NULL ,
  PRIMARY KEY (`m_uuid`) );


-- -----------------------------------------------------
-- Table `mydb`.`person_uuid`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`person_uuid` (
  `p_uuid`  NULL );


-- -----------------------------------------------------
-- Table `mydb`.`msg_message_to_medium`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_message_to_medium` (
  `m_uuid` VARCHAR(60) NOT NULL ,
  `opt_msg_message_medium` VARCHAR(10) NOT NULL ,
  PRIMARY KEY (`m_uuid`, `opt_msg_message_medium`) ,
  CONSTRAINT `fk_91187df6-4b82-11de-82cc-000ae4fedff3`
    FOREIGN KEY (`m_uuid` )
    REFERENCES `mydb`.`person_uuid` ());


-- -----------------------------------------------------
-- Table `mydb`.`msg_message`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_message` (
  `msg_uuid` VARCHAR(60) NOT NULL ,
  `message_content` VARCHAR(500) NULL DEFAULT NULL ,
  PRIMARY KEY (`msg_uuid`) );


-- -----------------------------------------------------
-- Table `mydb`.`msg_sent_messages`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_sent_messages` (
  `m_uuid` VARCHAR(60) NOT NULL ,
  `sender_id` VARCHAR(60) NOT NULL ,
  `recipient_number` VARCHAR(20) NOT NULL ,
  `msg_uuid` VARCHAR(60) NOT NULL ,
  `status`  NULL DEFAULT NULL ,
  `message_sent_time` TIMESTAMP NOT NULL DEFAULT now() ,
  PRIMARY KEY (`m_uuid`) ,
  INDEX `fk_91187e0d-4b82-11de-82cc-000ae4fedff3` (`msg_uuid` ASC) ,
  CONSTRAINT `fk_91187e0d-4b82-11de-82cc-000ae4fedff3`
    FOREIGN KEY (`msg_uuid` )
    REFERENCES `mydb`.`msg_message` (`msg_uuid` ));


-- -----------------------------------------------------
-- Table `mydb`.`msg_alert`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`msg_alert` (
  `tpl_uuid` VARCHAR(60) NOT NULL ,
  `tpl_name` VARCHAR(45) NULL ,
  `file_location` VARCHAR(45) NULL ,
  `file_type` VARCHAR(45) NULL ,
  `file_version` VARCHAR(45) NULL ,
  `author` VARCHAR(45) NULL ,
  `date_created` TIMESTAMP NULL ,
  `date_modified` TIMESTAMP NULL ,
  `template` VARCHAR(45) NULL ,
  `file` TEXT NULL ,
  PRIMARY KEY (`tpl_uuid`) )
ENGINE = InnoDB
COMMENT = 'template records\n';



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
