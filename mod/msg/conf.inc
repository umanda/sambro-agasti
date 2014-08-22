<?php
/**
* The Sahana Messaging Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author	Sudheera R. Fernando <sudheera@opensource.lk>
* @author	Mifan Careem <mifan@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package	sahana
* @subpackage	msg
* @tutorial
* @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

/*$conf['mod_msg_name'] = _("Messaging/Alerting Module");*/
$conf['mod_msg_name'] = _("Alerting Module");
$conf['mod_msg_menuorder'] = 2;

$conf['input_file']="../mod/msg/kannel.conf";
$conf['output_file']="/tmp/kannel.conf";

/**
 * Internal Configuration for Messaging
 * Not required to be handled via the generic $conf handler in Sahana, 
 * so doesn't adhere to generic $conf namespace
 */
 
 //$conf['mod_msg_plugin']='sms';
$conf['mod_msg_plugin']='kannel';
 
 //Counter for messaging module Media
 $conf['msg_supported_media']=2;
 
 //Medium: SMS
 $conf['msg_name'][0]='Short Messaging';
 $conf['msg_code'][0]='sms';
 
 //Medium: EMail
 $conf['msg_name'][1]='EMail';
 $conf['msg_code'][1]='email';
 
 /**
  * Email configuration
  * Use to configure SMTP server for email sending
  * Requires availability of local/remote SMTP server
  */
 $conf['mod_msg_smtp_host'] = 'localhost';
 $conf['mod_msg_smtp_user'] = '';
 $conf['mod_msg_smtp_pass'] = '';
 $conf['mod_msg_smtp_sender_name'] = 'CAP ITU PROJECTS';
 $conf['mod_msg_smtp_sender_email'] = 'kosol@itupo.org';
 $conf['mod_msg_smtp_port'] = 25;
 $conf['mod_msg_smtp_mode'] = 'enabled';
 $conf['mod_msg_mail_subject_prefix'] = '[CAPITUS]';
 
 
 // Dynamics for PHPmailer: sendmail|mail|smtp
 $conf['mod_msg_phpmail_conf'] = 'sendmail';

 // SMS receive console refresh rates in miliseconds
 $conf['msg_rc_refresh_rate']= 10000;
 
 // XSLT files for CAP conversion
 $conf['mod_msg_cap_short_to_sms']='xsl_cap_short_sms.xsl';
 $conf['mod_msg_cap_short_to_email']='xsl_cap_short_email.xsl';
 $conf['mod_msg_cap_long_to_email']='xsl_cap_long_email.xsl';
 $conf['mod_msg_cap_long_to_web']='xsl_cap_short_sms.xsl';
 $conf['mod_msg_cap_view_data']='xsl_cap_view_data.xsl';
 $conf['mod_msg_cap_view_data_indv']='xsl_cap_view_data_indv.xsl';
 $conf['mod_msg_cap_view_data_indv_more']='xsl_cap_view_data_indv_more.xsl';
 $conf['mod_msg_cap_voice_to_ivr']='xsl_cap_voice_ivr.xsl'; 
 $conf['mod_msg_cap_short_to_tweet']='xsl_cap_short_tweet.xsl';
 $conf['mod_msg_cap_voice_to_satellite']='xsl_cap_voice_satellite.xsl';
 $conf['mod_msg_cap_long_to_signage']='xsl_cap_long_signage.xsl';
  
#####################################
#      CAP Alert Options            #
#####################################

$conf['mod_msg_cap_version'] = '1.2';

 # Default Message identifier - Prefix

$conf['alert_identifier'] = '2.49.0.1.xxx.1-ITUPROJECTS-';

# Default Time (change for the specific country)

$conf['timezone'] = '+07.00';

# To off using tiny url feature while sending a sms and send the sms with orginal url, set this variable as false 
$conf['tinyurl'] = false;

# This line will add the number of viewing recently modified of alerts
$conf['number_of_recent_alerts_view'] = 10;

#This will add the number of records per page in View alerts page
$conf['records_per_page'] = 10;

#This will add a default title name if the actual title name is empty
$conf['default_title'] = 'CAPITUS-ALERT';
?>
