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
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

global $global;
require_once $global['approot']."/inc/lib_locale/lib_locale.inc";
require_once('class_cap_alert.inc');
require_once('class_cap_info.inc');
require_once('class_cap_resource.inc');
require_once('class_cap_area.inc');
require_once('lib_cap_js.inc');
//print $_REQUEST['seq'];

switch ($_REQUEST['seq'])
{
    case '' :
            $_SESSION['cap_msg'] = null;
            unset($_SESSION['is_template']);
            _shn_msg_cap_newalertmain();
            break;
    case 'new_cap_main':  
    		
    			_shn_msg_new_alert_db();
    		
                   // _shn_msg_cap_addmain();
                   // _shn_msg_cap_infonew();
                    break;
   /* case 'new_cap_info':
                    _shn_msg_cap_addinfo();
                    _shn_msg_cap_resourcenew();
                    break;
    case 'new_cap_res':
                    _shn_msg_cap_add_res();
                    _shn_msg_cap_resourcenew();
                    break;
    case 'del_cap_res':
                    _shn_msg_cap_del_res();
                    _shn_msg_cap_resourcenew();
                    break;
    case 'new_cap_area':
                    _shn_msg_cap_new_area();
                    break;
    case 'add_cap_area':
                    _shn_msg_cap_add_area();
                    _shn_msg_cap_new_area();
                    break;
    case 'del_cap_area':
                    _shn_msg_cap_del_area();
                    _shn_msg_cap_new_area();
                    break;
    case 'new_cap_finish':
                    _shn_msg_cap_finish();
                    break;
    case 'new_cap_save':
                    _shn_msg_cap_save();
                    break;*/
}

function _shn_msg_cap_newalertmain()
{
	global $global;
	global $conf;
    require_once('lib_cap_help.inc');
    $name = trim($_POST['name']);
    $mode = trim('cap');
    $id = time();
    $today = date("Y-m-d");
    $message_id = $conf['alert_identifier'].$id;
    //print $today;
    
    $status = array('Actual'=>'Actual', 'Exercise'=>'Exercise', 
                     'System'=>'System', 'Test'=>'Test', 'Draft'=>'Draft');
    $msgType = array('Alert'=>'Alert', 'Update'=>'Update', 
                      'Cancel'=>'Cancel', 'Ack'=>'Ack', 'Error'=>'Error');
    $scope = array('Public'=>'Public', 'Restricted'=>'Restricted', 
                   'Private'=>'Private');
    
    print "<h2>" . _t("Creating New Cap Alert") . "</h2>";
    
    shn_form_fopen("alert_new",null,array('req_message'=>false,'name'=>'cap_new'));
    shn_form_hidden(array('seq'=>'new_cap_main'));
    shn_form_fsopen(_t("New Cap Alert"));
    shn_form_hidden(array('time'=>$id,'stat'=>$status[_t("Actual")], 'name'=> $name, 'mode'=>$mode));
    shn_form_text(_t("Message Identifier"),'identifier',null,array('value'=>$message_id,'help'=>$help_identifire, 'req'=>true));
    shn_form_date(_t("Date Created"),'date_created',array('value'=>$today, 'req' => true));
    shn_form_text(_t("Sender"),'sender','class=""',array('help'=>$help_sender, 'req' => true));
    shn_form_text(_t("File Type"),'file_type',null, array('value'=>$mode, 'req' => true));
    shn_form_text(_t("File Version"),'file_version',null, array('req' => true, 'value'=> $conf['mod_msg_cap_version'], 'help'=>_t('Indicate the CAP/EDXL Version: e.g 1.01')));
    //shn_form_upload(_('Upload file'), 'upload', null);
      
    
    shn_form_fsclose();
    //shn_form_hidden(array('name'=> $name));
    //shn_form_hidden(array('mode'=> $mode));
    shn_form_submit(_t("Next"), 'style="float: left"');
    
    shn_form_fsclose(); //Close capmessage form
    
    
    shn_form_fclose();
    
   // _shn_msg_add_capjs();
}

function _shn_msg_alert_validate()
{
	$error_flag = false;
	if ((trim($_POST['sender'])) == null || trim($_POST['sender'])== '')
	{
		add_error(_t('Sender is essential. Please complete and submit again'));
		$error_flag = true;
	}
	if(trim($_POST['identifier']) == null || trim($_POST['identifier'])== '')
	{
		add_error(_t('Message Identifier is essential. Please complete and submit again'));
		$error_flag = true;
	}
	if(trim($_POST['date_created']) == null || trim($_POST['date_created'])== '')
	{
		add_error(_t('Date Created is essential. Please complete and submit again'));
		$error_flag = true;
	}
	if(trim($_POST['file_type']) == null || trim($_POST['file_type'])== '')
	{
		add_error(_t('File Type is essential. Please complete and submit again'));
		$error_flag = true;
	}
	if(trim($_POST['file_version']) == null || trim($_POST['file_version'])== '')
	{
		add_error(_t('File Version is essential. Please complete and submit again'));
		$error_flag = true;
	}
	/*if($_SESSION['msg']['alert']['name'] == null || $_SESSION['msg']['alert']['name']== '')
	{
		add_error(_t('Name is essential. Please complete and submit again'));
		$error_flag = true;
	}*/
	return $error_flag;
}

function _shn_msg_new_alert_db($type=null)
{
	if((_shn_msg_alert_validate() == true && $_SESSION['alert_temp'] == 1) || (_shn_msg_alert_validate() == true && $_SESSION['alert_temp'] != 1))
	{
		add_error(_t('Please Submit the required values'));
		shn_msg_new_alert();
	}
	else
	{
	global $global;
	$insert_array = array();
	$insert_array['alert_uuid'] = trim($_POST['identifier']);
	$insert_array['alert_name'] = trim($_POST['name']);
	$insert_array['file_type'] = ($_POST['file_type'])? trim($_POST['file_type']) : "cap";
	$insert_array['file_version'] = ($_POST['file_version'])? trim($_POST['file_version']) : "1.1";
	$insert_array['author'] = trim($_POST['sender']);
	$insert_array['date_created'] = trim($_POST['date_created']);
	$insert_array['type'] = trim($_POST['mode']);
	
	$_SESSION['msg']['new']['alert'] = $insert_array;
	
	//var_dump($insert_array);
	
	$db = $global['db'];
    $res = $db->AutoExecute('msg_alerts', $insert_array, 'INSERT');
    if($res == true )
    {
    	add_confirmation(_t('Data Saved Successfully'));
    	unset($_REQUEST['seq']);
    	unset($_SESSION['is_template']);
    	//include_once 'handler_cap_new.inc'; //Use Previous UIs
    	
    	if(isset($_SESSION['alert_temp'])){
    	
    	} else {
    		//To Use New UIs
    		include_once 'shn_cap_form.inc';
			_shn_msg_cap_form();
			
    	}
    	unset($_SESSION['alert_temp']); // distroy
    	$_SESSION['tmp_alert_id']=$insert_array['alert_uuid'];
    	
    }
    else
    {
    	add_error(_('Error while saving data'));
    	_shn_msg_cap_newalertmain();
    }
 	
    //echo $res->get;
    //var_dump($res);
	}
	
}

?>
