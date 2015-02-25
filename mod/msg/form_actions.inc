<?php
/**
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Mifan Careem <mifan@respere.com>
* @copyright  Respere - http://respere.com/
* @package	  SAMBRO
* @subpackage Messaging
* @version 	  $Id: form_actions.inc,v 1.2 2008/04/30 05:56:58 mifanc Exp $
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

/**
 * Action for store message form
 */
function shn_msg_create_store()
{
	
	$_SESSION['msg_head']=$_POST['msg_head'];
	$_SESSION['message']=$_POST['message'];
	$_SESSION['media_type']=$_POST['media_type'];
	
	if( shn_msg_create_store_validate() == true){
		shn_msg_add_store_msg();
	}else{
			
		global $global;
		global $conf;
		
		include_once($global['approot'].'/inc/lib_uuid.inc');
		
		$db = $global['db'];
		
		$m_uid = shn_create_uuid('msg');
		
		$query = "INSERT INTO msg_stored_messages (m_uuid,message_header,message_content,message_creation_user_id) " .
				" VALUES ('{$m_uid}','{$_SESSION['msg_head']}','{$_SESSION['message']}','{$_SESSION['user']}')";
		$db->Execute($query);
		
		//Enter message mapping to medium
		foreach ($_SESSION['media_type'] as $key=>$val){
			$query_map = "INSERT INTO msg_message_to_medium (m_uuid,opt_msg_message_medium) VALUES ('{$m_uid}','{$val}')";
			$db->Execute($query_map);
		}
		
		add_confirmation(_t('Your message has been stored in the system'));
	}
	
}

function shn_msg_create_store_validate()
{
	$error_flag = false;
	if ((trim($_POST['msg_head'])) == null || trim($_POST['msg_head'])== '')
	{
		add_error(_t('Message Heading/Summary is essential. Please complete and submit again'));
		$error_flag = true;
	}
	if(trim($_POST['message']) == null || trim($_POST['message']) == '')
	{
		add_error(_t('Message is essential. Please complete and submit again'));
		$error_flag = true;
	}
	return $error_flag;
}


/**
 * Action for template  message form
 */
function shn_msg_create_tpl()
{
	
	$_SESSION['msg_head']=$_POST['msg_head'];
	$_SESSION['message']=$_POST['message'];
	$_SESSION['media_type']=$_POST['media_type'];
	
	
	global $global;
	global $conf;
	
	include_once($global['approot'].'/inc/lib_uuid.inc');
	
	$db = $global['db'];
	
	$m_uid = shn_create_uuid('msg');
	
	$query = "INSERT INTO msg_tpl_messages (m_uuid,message_header,message_content,message_creation_user_id) " .
			" VALUES ('{$m_uid}','{$_SESSION['msg_head']}','{$_SESSION['message']}','{$_SESSION['user']}')";
	$db->Execute($query);
	
	//Enter message mapping to medium
	foreach ($_SESSION['media_type'] as $key=>$val){
		$query_map = "INSERT INTO msg_message_to_medium (m_uuid,opt_msg_message_medium) VALUES ('{$m_uid}','{$val}')";
		$db->Execute($query_map);
	}
	
	add_confirmation(_t('Your message has been stored in the system'));
}


/**
 * Send message main call
 * @todo add group information to the message strings
 */
function shn_msg_send_message(){
	global $global;
	include_once $global['approot']."/mod/msg/lib_msg.inc";
	include_once $global['approot']."/mod/twitter/twitter/handler_tweet.php";
	
	$db = $global['db'];
	$message="";
	$email_array = array();
	$sms_array = array();
	$group_array = array();
	$message_array=array();

	
	
	
	
	 if(!file_exists("../mod/msg/ivrtext/"))
	{
		mkdir("../mod/msg/ivrtext/");
	}
	$xml_id = $_SESSION['ivr_msg_id'];
	$output = $_SESSION['ivr_msg'];
	$xml_save_to_file = fopen("../mod/msg/ivrtext/".$xml_id.".txt","w");
	fwrite($xml_save_to_file, $output);
	fclose($xml_save_to_file);
	$list=shn_msg_alert_details($_SESSION['ivr_msg_id']);
	$output = $_SESSION['ivr_msg'];
	
	$insert_file_array = array();
	$insert_file_array['ivr_alert_id'] = $xml_id;
	$insert_file_array['ivr_alert_name'] = $list['name'];
	$insert_file_array['ivr_alert_content'] = $output;
	
	global $global;
	$rset = $global['db']->AutoExecute('msg_ivr_alert', $insert_file_array, 'INSERT');
	$var_name = $_SESSION['ivr_var_name'];	
//echo $var_name;	
	if($var_name == 'message_voice_ivr'){
	
		add_confirmation(_t('IVR information saved successfully'));
	
	}
		
	$var_tweet = $_SESSION['message_tweet'];
	$msg_tweet = $_SESSION['tweet_msg'];

	if($var_tweet == 'short_to_tweet'){
		
		shn_mod_tweet($msg_tweet);	
	
	}
	
 	$_SESSION['message_tweet'] = null;
	$_SESSION['tweet_msg'] = null;
	
	/* $sql = "INSERT INTO msg_ivr_alert (ivr_alert_id,ivr_alert_name,ivr_alert_content) VALUES ('".$xml_id."','".$list['name']."','".$output."')";
	$db->Execute($sql);
	 */
	//Handle message
	if($_POST['stmsg']!=""){
		//Stored Message
		$sql = "SELECT message_content FROM msg_stored_messages WHERE m_uuid='{$_POST['stmsg']}'";
		$result = $db->Execute($sql);
		if(!$result->EOF){
			$message = $result->fields['message_content'];
		}
	}
	else{
		//Template or custom message
		$message = $_POST['message'];
		$message_array['short_sms']=($_REQUEST['message_short_sms']!=''?$_REQUEST['message_short_sms']:$_REQUEST['message']);
		$message_array['short_dlabel']=($_REQUEST['message_short_dlabel']!=''?$_REQUEST['message_short_dlabel']:$_REQUEST['message']);
		$message_array['short_email']=($_REQUEST['message_short_email']!=''?$_REQUEST['message_short_email']:$_REQUEST['message']);
		$message_array['long_email']=($_REQUEST['message_long_email']!=''?$_REQUEST['message_long_email']:$_REQUEST['message']);
		$message_array['long_signage']=($_REQUEST['message_long_signage']!=''?$_REQUEST['message_long_signage']:$_REQUEST['message']);
		$message_array['short_tweet']=($_REQUEST['message_short_tweet']!=''?$_REQUEST['message_short_tweet']:$_REQUEST['message']);
		$message_r = ($message_array['short_email']!=''?$message_array['short_email']:$message_array['long_email']);
	}
	
	//Handle contacts
	list($email_array,$sms_array) = shn_msg_get_categories_from_contact(_shn_msg_message_filter($_POST['to']));
	
	
	//Call library methods
	//Send text messages
	$status_sms = shn_msg_send_short_message($sms_array,$message_array['short_sms']);
	
	//Send email messages
	$status_email = shn_msg_send_email($email_array,$message_r);
	if($status_email){
		//print email status
		foreach($status_email as $key=>$value){
			if($value)
				add_confirmation(_t('Sent mail to ').$key);
			else if(!$value)
				add_error(_t('Send mail failure: The mail to ').$key._t(' was not sent'));
		}
	}
	
}

/**
 * Filter message contacts into email/sms
 * @return mixed_array array of contacts
 */
function _shn_msg_message_filter($contacts)
{
	global $global;
	$contacts = trim($contacts);
	$contacts_array = split(',',$contacts);
	return $contacts_array;		
}

/**
 * RESTful filter function to send alerts
 * 
 * @return unknown_type
 */
function shn_msg_send_alert()
{
	global $global;
	include_once($global['approot'].'/mod/msg/lib_cap_alert_type.php');
	
	switch($_REQUEST['seq']){
		case 'select_contact':
			if($_REQUEST['xml_id']==null){
				add_error('XML Document not linked - please try again');
				return false;
			}
			//$xml_id='Actual-1245046951';
			//clear session first time
			$_SESSION['msg']['send']=array();
			
			$array_of_contacts = shn_msg_alert_contact_select();
			//store xml id for later usage
			$_SESSION['msg']['send']['xml_id']=$_REQUEST['xml_id'];
			break;
			
		case 'delivery_type':
			$_SESSION['msg']['send']['to']=$_REQUEST['to'];
			shn_msg_cap_select_delivery_type(trim($_POST['xml_id']));
			break;
			
		case 'transform_message':
			
			//print_r($_REQUEST['select_type']);
			$id = $_POST['id'];
				echo "<h1>"._('Send Message')."</h1>";
				shn_form_fopen('send_message',null,array('req'=>false));
				if ($_REQUEST['select_type'] == '' || $_REQUEST['select_type'] == NULL)
				{
					if(_shn_msg_add_long_web($id, $flag = 0))
					{
						$confirmation = true;
					}
					else
					{
						$confirmation = false;
					}
				}
				foreach($_REQUEST['select_type'] as $delivery){
					//var_dump($delivery);
					//print 'test';
 					if($delivery == 'short_to_tweet'){
						
 						$_SESSION['message_tweet'] = $delivery;
						
 					}
					$res = _shn_msg_check_long_web($id);
					//print $delivery;
					if($delivery == 'long_to_web')
					{
						if(_shn_msg_add_long_web($id, $flag = 1))
						{
							$confirmation = true;
						}
						else
						{
							$confirmation = false;
						}
					}
					else
					{
					
						//print $res->fields['web_enabled'].'mahesh';			
						if($res->fields['web_enabled'] == 1)
						{
							if(_shn_msg_add_long_web($id, $flag = 0))
							{
								$confirmation = true;
							}
							else
							{
								$confirmation = false;
							}
						}
						shn_msg_cap_transform_message($delivery);
					
					}		
					
					
				}
				
				if($confirmation)
				{
					add_confirmation(_t('Web Information saved Successfully'));
				}
				else
				{
					;//add_error(_t('Web Information not saved due to an error'));
				}
				//var_dump($_SESSION['msg']['send']);
				shn_form_hidden(array('to'=>$_SESSION['msg']['send']['to']));
				shn_form_submit('Send Message');
				shn_form_fclose();
			//shn_msg_cap_transform_message($_REQUEST['select_type']);
			break;
			
		case 'send_final':
			echo "TO:".$_REQUEST['to'];
			echo "MSG:".$_REQUEST['message'];
			
			break;
		default:
	}
}
?>
