<?php
/**Class that front ends the PHP Mailer
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sri Ganeshan <sri@opensource.lk>
* @author     Ravindra De Silva <ravindra@opensource.lk><ravi@computer.org>
* @edit		  Mifan Careem <mifan@opensource.lk> [Converting to use global $conf variables]
* @edit		tharaka wilfred tharakawilfred85@gmail.com
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* $license	  $Id: lib_mail.inc,v 1.8 2008/04/30 06:01:36 mifanc Exp $
* @subpackage msg
*/


global $global;
require_once($global['approot']."3rd/phpmailer/class.phpmailer.php");

/**
 * PHPMailer extension class
 */
class InheritPhpMailer extends PHPMailer
{
    // Mifan: Converting previously used $sit global variable to $conf global array
    
    var $priority = 3;

    function InheritPhpMailer()
    {
      global $conf;
      
      
      if($conf['mod_msg_smtp_mode'] == "enabled"){
		    $this->Host = $conf['mod_msg_smtp_host'];
		    $this->Port = $conf['mod_msg_smtp_port'];
		    if($conf['mod_msg_smtp_username'] != ""){
		         $this->SMTPAuth  = true;
		         $this->Username  = $conf['mod_msg_smtp_username'];
		         $this->Password  = $conf['mod_msg_smtp_password'];
        	}
        $this->Mailer = $conf['mod_msg_phpmail_conf'];
        
      }
      if(!$this->From){
        	$this->From = $conf['mod_msg_smtp_sender_email'];
      }
      if(!$this->FromName){
        	$this->FromName = $conf['mod_msg_smtp_sender_name'];
      }
      	
      if(!$this->Sender){
        	//
      }
      
      if(isset($_SESSION['msg']['email']['sender']))
      		$this->Sender = $_SESSION['msg']['email']['sender'];
      else
      		$this->Sender = $conf['mod_msg_smtp_sender_email'];
      		
      $this->Priority = $this->priority;
    }
}

/**
 * Email sending main function
 * Group sending
 */
function _shn_msg_send_group_mail($msg,$receipients,$subject_line=false)
{
	//config settings
	//require_once('mail_settings.inc');
	//shn_update_mail_configuration();
	global $conf;
	
	// instantiate the class
	$mailer = new InheritPhpMailer();
	$status=0;
	$trimd_msg=trim($msg);
	if(!$subject){
		$subject=substr($trimd_msg,0,15);
		$mailer->Subject = $conf['mod_msg_mail_subject_prefix'].$subject;
	}
		
	if(isset($_SESSION['msg']['email']['subject']))
		$mailer->Subject = $_SESSION['msg']['email']['subject'];
	else
		$mailer->Subject = $subject_line;

	if(isset($_SESSION['msg']['email']['attachment']))
		$mailer->AddAttachment($_SESSION['msg']['email']['attachment'],'cap_alert.xml');
		

	$mailer->Body = $msg;
	$status_mail=array();
	   foreach($receipients as $receipient){
			$mailer->AddAddress($receipient, '');
			
	        $status=$mailer->Send();
	
	        if($status){ 
	        	$status_mail[$receipient]=1;
	        }else{
		  		$status_mail[$receipient]=0;
	        }
	        $status=0;
	        $mailer->ClearAddresses();
	   }
	return $status_mail;
}

function _shn_msg_send_mail()
{
// Grab our config settings
require_once('mail_settings.inc');

// Grab the InheritPhpMailer class
//require_once('MailClass.inc');

// instantiate the class
$mailer = new InheritPhpMailer();

$receipient = $_POST['receipient'];

$subject = $_POST["subject"];

$ccreceipient = $_POST['ccreceipients'];

$bccreceipient = $_POST['bccreceipients'];

$attachment = $_POST['attachments'];

$body = $_POST['contents'];

$mailer->Subject = $subject;

$mailer->Body = $body;

$mailer->AddAddress($receipient, 'hari');

//$mailer->AddAddress('hari1222@yahoo.com', 'hari');

$mailer->AddAttachment($attachment, ''); 

$mailer->AddCC($ccreceipient, ''); 

$mailer->AddBCC($bccreceipient,''); 

//$mailer->AddReplyTo('kushi223344@yahoo.com', 'sri'); 

if(!$mailer->Send())
{
  echo 'There was a problem sending this mail!';
}
else
{
  echo 'Mail sent!';
}
$mailer->ClearAddresses();
$mailer->ClearAttachments();
}

function _shn_msg_send_mail_confirm_user($fullname, $email) {

// Grab our config settings
require_once('mail_settings.inc');

// Grab the InheritPhpMailer class
//require_once('MailClass.inc');

// instantiate the class
$mailer = new InheritPhpMailer();

//$receipient = $_POST['receipient'];

$subject = $_POST["subject"];

//$ccreceipient = $_POST['ccreceipients'];

//$bccreceipient = $_POST['bccreceipients'];

//$attachment = $_POST['attachments'];

//$body = $_POST['contents'];

$subject = "Confirmation - your account is active now";

$mailer->Subject = $subject;

$body_data = file_get_contents($global['approot']."mod/msg/confirm_body.txt");

$mailer->Body = "Dear ".$fullname.",".$body_data."Admin User.";

$mailer->AddAddress($email, 'hari');

//$mailer->AddAddress('hari1222@yahoo.com', 'hari');

//$mailer->AddAttachment($attachment, '');

//$mailer->AddCC($ccreceipient, '');

//$mailer->AddBCC($bccreceipient,'');

//$mailer->AddReplyTo('kushi223344@yahoo.com', 'sri'); 

if(!$mailer->Send())
{
  echo 'There was a problem sending this mail!';
}
else
{
  add_confirmation(_t('Mail sent successfully to '.$email));
}
$mailer->ClearAddresses();
$mailer->ClearAttachments(); 
}


function _shn_msg_send_mail_admin($new_user,$user_email)
{
// Grab our config settings
require_once('mail_settings.inc');

// Grab the InheritPhpMailer class
//require_once('MailClass.inc');

// instantiate the class
$mailer = new InheritPhpMailer();

//$receipient = $_POST['receipient'];

$subject = "Account registration request received";

$ccreceipient = $_POST['ccreceipients'];

$bccreceipient = $_POST['bccreceipients'];

$attachment = $_POST['attachments'];

//$body_data = file_get_contents($global['approot']."mod/msg/body.txt");

$mailer->Subject = $subject;

//$mailer->Body = $body_data;
global $global;
$db=$global['db'];

$query = "select u.user_name from users as u inner join sys_user_to_group as p on u.p_uuid = p.p_uuid where p.group_id='1'";

$res = $db->Execute($query);

$receipients = array();
$receipient_list = $res->fields['user_name'];
		
$receipients = split(',',$receipient_list);
array_push($receipients, $user_email);

$body_data = file_get_contents($global['approot']."mod/msg/body.txt");

//$mailer->Body = $body_data;

foreach($receipients as $receipient) {

	$qry = "select p.full_name from person_uuid as p inner join users as u on p.p_uuid = u.p_uuid where u.user_name = '{$receipient}'";
	
	$rs = $db->Execute($qry);
	$fullname = $rs->fields['full_name'];

	$mailer->Body = "Dear ".$new_user.",".$body_data;

	$mailer->AddAddress($receipient, 'hari');

	$status = $mailer->Send();
	
		if($status) {
			add_confirmation(_t('Mail sent successfully to '.$receipient));
//echo $res;
			$status_mail[$receipient] = 1;
		} else {
			$status_mail[$receipient] = 0;	
		}
		$status=0;
		$mailer->ClearAddresses();
	

}
//$mailer->AddAddress('hari1222@yahoo.com', 'hari');

//$mailer->AddAttachment($attachment, '');

//$mailer->AddCC($ccreceipient, '');

//$mailer->AddBCC($bccreceipient,'');

//$mailer->AddReplyTo('kushi223344@yahoo.com', 'sri'); 

$mailer->ClearAttachments();
}

?> 
