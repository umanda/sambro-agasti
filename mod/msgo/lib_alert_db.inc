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
* @author		Pradeeper <pradeeper@respere.com>
* @copyright    Respere - http://respere.com/
* @package		sahana
* @subpackage   msg
* @tutorial
* @version		
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*  
*/
include_once $global['approot'].'/inc/lib_form.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_errors.inc';

/**
 * Alerts and Templates submitter
 */
function shn_msg_alert_store($alert_id, $alert_name)
{
	global $global;
    $db=$global["db"];
    
    // get the logged in user
	$author=$_SESSION['user'];
    
    $q="INSERT INTO msg_alerts (alert_uuid, alert_name, file_type, file_version, author, date_created, type) VALUES ('$alert_id','$alert_name','cap','1.1','$author','','temp');";
    
    $res = $db->Execute($q);
    
    if($res){
    	add_confirmation("<strong>$alert_name</strong> template was saved! Please <a href='index.php?mod=msg&act=new_alert_temp'>click</a> to create a new template.");
    } else {
    	add_error("Can not save the template in the database!");
    }
}

/**
 * Get a list of names of the alerts or templates
 */
function shn_msg_alert_list($type)
{
	global $global;
    $db=$global["db"];
    
    
    if($type=="template"){
    	$tmp="temp";
    } else {
    	$tmp="cap";
    }
    
    $q="SELECT * FROM msg_alerts WHERE type='$tmp' AND visible=1 ";
    
    $res = $db->Execute($q);
    
    $x=0;
	while (!$res==NULL && !$res->EOF)
	{
    	$list[$x]['id']="{$res->fields['alert_uuid']}";
    	$list[$x]['name']="{$res->fields['alert_name']}";
    	$list[$x]['alert_type']="{$res->fields['file_type']}";
    	$list[$x]['alert_version']="{$res->fields['file_version']}";
    	$list[$x]['author']="{$res->fields['author']}";
    	$list[$x]['type']="{$res->fields['type']}";
    	$x=$x+1;
		$res->MoveNext();
	}
	return $list;
}
function shn_ivr_alert_list()
{
	global $global;
	$db=$global["db"];
	
	
	
	$q="SELECT * FROM msg_ivr_alert INNER JOIN msg_alerts ON msg_ivr_alert.ivr_alert_id=msg_alerts.alert_uuid WHERE msg_alerts.deactivate_dt is NULL";
	
	$res = $db->Execute($q);
	
	$x=0;
	while (!$res==NULL && !$res->EOF)
	{
		$list[$x]['ivr_alert_id']="{$res->fields['ivr_alert_id']}";
		$list[$x]['ivr_alert_name']="{$res->fields['ivr_alert_name']}";
		$list[$x]['ivr_alert_content']="{$res->fields['ivr_alert_content']}";
		$x=$x+1;
		$res->MoveNext();
	}
	return $list;
}
function shn_get_ivr_alert($id)
{
	global $global;
	$db=$global["db"];
	
	
	
	$q="SELECT * FROM msg_ivr_alert WHERE ivr_alert_id = '".$id."'";
	
	$res = $db->Execute($q);
	
	$x=0;
	while (!$res==NULL && !$res->EOF)
	{
		$list[$x]['ivr_alert_id']="{$res->fields['ivr_alert_id']}";
		$list[$x]['ivr_alert_name']="{$res->fields['ivr_alert_name']}";
		$list[$x]['ivr_alert_content']="{$res->fields['ivr_alert_content']}";
		$x=$x+1;
		$res->MoveNext();
	}
	return $list;
}
/**
 * Get Message Details When ID is Given
 */
function shn_msg_alert_details($id)
{
	global $global;
    $db=$global["db"];
    
    $q="SELECT * FROM `msg_alerts` WHERE alert_uuid='$id';";
    
    $res = $db->Execute($q);
    
    $list['id']="{$res->fields['alert_uuid']}";
    $list['name']="{$res->fields['alert_name']}";
    $list['alert_type']="{$res->fields['file_type']}";
    $list['alert_version']="{$res->fields['file_version']}";
    $list['author']="{$res->fields['author']}";
    $list['type']="{$res->fields['type']}";
    
    return $list;
}


/**
 * Get the xml file when id is given
 */
function shn_msg_xml_grabber($id)
{
	global $global;
    $db=$global["db"];
    
    $q="SELECT file FROM `msg_alerts` WHERE alert_uuid='$id'";
    $res = $db->Execute($q);
    
    $xml_file="{$res->fields['file']}";
    
    return $xml_file;
}
function shn_msg_hide_template($id)
{
	global $global;
    $db=$global["db"];
    
    $q = "UPDATE msg_alerts SET visible=0, deactivate_dt=NOW() WHERE alert_uuid='$id'";
    return $res = $db->Execute($q);
    
}
function shn_msg_hide_alert($id)
{
	global $global;
    $db=$global["db"];
    
    $q = "UPDATE msg_alerts SET visible=0, deactivate_dt=NOW() WHERE alert_uuid='$id'";
    //print $q;
    return $res = $db->Execute($q);
    
}

function shn_msg_get_all_alert_uuid()
{
	global $global;
	$db=$global["db"];
	
	$q = "SELECT alert_uuid FROM msg_alerts WHERE visible=1";
	//print $q;
	return $res = $db->Execute($q);
	
}

function shn_msg_get_xml($xml_id)
{
	global $global;
	$db = $global["db"];
	
	$q = "SELECT file FROM msg_alerts WHERE alert_uuid='$xml_id'";
	//print $q;
	return $res_xml = $db->Execute($q);
}

//function _shn_alert_view_filter($title = NULL, $priority = NULL, $msg_type = NULL, $sender = NULL, $date_sent = NULL, $sort = NULL, $date_sent_to = NULL)
function _shn_alert_view_filter($data_array)
{
	
	$sort = trim($data_array['sort']); 
	$title = $data_array['title'];
	$msg_type = trim($data_array['msg_type']);
	$date_sent = $data_array['date_sent'];
	$sender = $data_array['sender'];
	$priority = $data_array['priority'];
	$date_sent_to = $data_array['date_sent_to'];
	$status = $data_array['status'];
	$scope = $data_array['scope'] ;
	$category = $data_array['category'];
	$responseType = $data_array['responseType'];
	
	if($priority == '==')
	{
		$priority =  '';
	}
	
	
	//print $title;
	global $global;
	$db = $global["db"];
	if(!isset($title) && !isset($priority) && !isset($msg_type) && !isset($sender) && !isset($date_sent))
	{
		$sql = "SELECT alert_uuid, ExtractValue(file, '/alert/info/headline') AS head_line, ExtractValue(file, '/alert/sent') AS sent_date, ExtractValue(file, '/alert/info/senderName') AS sender, ExtractValue(file, '/alert/info/priority') AS priority FROM msg_alerts WHERE visible=1 AND file != '' AND alert_uuid = ExtractValue(file, '/alert/identifier') AND web_enabled = 1 AND";
		//$sql = "SELECT alert_uuid, ExtractValue(file, '/alert/info/headline') AS headline, ExtractValue(file, '/alert/info/priority') AS priority FROM msg_alerts WHERE visibl=1;";
	}
	else
	{
		$sql = "SELECT alert_uuid, ExtractValue(file, '/alert/info/headline') AS head_line, ExtractValue(file, '/alert/sent') AS sent_date, ExtractValue(file, '/alert/info/senderName') AS sender, ExtractValue(file, '/alert/info/priority') AS priority FROM msg_alerts WHERE visible=1 AND file != '' AND alert_uuid = ExtractValue(file, '/alert/identifier') AND web_enabled = 1"; 
	}
	if(!isset($title) || $title != '')
	{
		//print 'test';
		//$title = "<title>".$title;
		$sql = $sql." AND ExtractValue(file, '/alert/info/headline') LIKE '%$title%'";
	}
	if(!isset($priority) || $priority != '')
	{
		//$priority = "&lt;priority&gt;".$priority;
		//print $priority;
		$sql = $sql." AND ExtractValue(file, '/alert/info/priority') LIKE '%$priority%'";
	}
	if(!isset($msg_type) || $msg_type != '')
	{
		$sql = $sql." AND ExtractValue(file, '/alert/msgType') LIKE '%$msg_type%'";
	}
	if(!isset($sender) || $sender != '')
	{
		$sql = $sql." AND ExtractValue(file, '/alert/info/senderName') LIKE '%$sender%'";
	}
	if(!isset($status) || $status != '')
	{
		$sql = $sql." AND ExtractValue(file, '/alert/status') LIKE '%$status%'";
	}
	if(!isset($scope) || $scope != '')
	{
		$sql = $sql." AND ExtractValue(file, '/alert/scope') LIKE '%$scope%'";
	}
	if(!isset($category) || $category != '')
	{
		$sql = $sql." AND ExtractValue(file, '/alert/info/category') LIKE '%$category%'";
	}
	if(!isset($responseType) || $responseType != '')
	{
		$sql = $sql." AND ExtractValue(file, '/alert/info/responseType') LIKE '%$responseType%'";
	}
	if($date_sent != '' && $date_sent_to != '')
	{
		//$sql = $sql." AND ExtractValue(file, '/alert/sent') LIKE '%$date_sent%'";
		$date_sent = $date_sent.' 00:00:00';
		$date_sent_to = $date_sent_to.' 00:00:00';
		$sql = $sql." AND DATEDIFF(ExtractValue(file, '/alert/sent'), '$date_sent')>0 AND DATEDIFF('$date_sent_to', ExtractValue(file, '/alert/sent'))>0 ";
	}
	if($date_sent != '' && $date_sent_to == '')
	{
		//$sql = $sql." AND ExtractValue(file, '/alert/sent') LIKE '%$date_sent%'";
		$date_sent = $date_sent.' 00:00:00';
		//$date_sent_to = $date_sent_to.' 00:00:00';
		$sql = $sql." AND DATEDIFF(ExtractValue(file, '/alert/sent'), '$date_sent')>0 ";
	}
	if($date_sent == '' && $date_sent_to != '')
	{
		//$sql = $sql." AND ExtractValue(file, '/alert/sent') LIKE '%$date_sent%'";
		//$date_sent = $date_sent.' 00:00:00';
		$date_sent_to = $date_sent_to.' 00:00:00';
		$sql = $sql." AND DATEDIFF('$date_sent_to', ExtractValue(file, '/alert/sent'))>0 ";
	}
	switch($sort)
	{
		case 'title':
			$sql = $sql." ORDER BY ExtractValue(file, '/alert/info/headline')";
			break;
			
		case 'priority':
			$sql = $sql." ORDER BY ExtractValue(file, '/alert/info/priority')";
			break;
			
		case 'msg_type':
			$sql = $sql." ORDER BY ExtractValue(file, '/alert/msgType')";
			break;
			
		case 'sender':
			$sql = $sql." ORDER BY ExtractValue(file, '/alert/sender')";
			break;
			
		case 'sent':
			$sql = $sql." ORDER BY ExtractValue(file, '/alert/sent')";
			break;
			
	}
	
	//print $sql;
	return $sql;
	//$res_view = $db->Execute($sql);
	//return $res_view;
	
}

function _shn_msg_recent_alerts()
{
	global $global;
	global $conf;
	//$conf['number_of_recent_alerts_view'] = 10;
	//$no_recent_alerts = $conf['number_of_recent_alerts_view'];
	$db =$global['db'];
	$sql = "SELECT alert_uuid, ExtractValue(file, '/alert/info/headline') AS head_line, ExtractValue(file, '/alert/sent') AS sent_date, ExtractValue(file, '/alert/info/senderName') AS sender, ExtractValue(file, '/alert/info/priority') AS priority, ExtractValue(file, '/alert/info/area/areaDesc') AS area, ExtractValue(file, '/alert/info/category') AS category, ExtractValue(file, '/alert/msgType') AS msg_type FROM msg_alerts WHERE visible=1 AND file != '' AND alert_uuid = ExtractValue(file, '/alert/identifier') AND web_enabled = 1 ORDER BY date_modified DESC LIMIT ".$conf['number_of_recent_alerts_view']."";

	//print $sql;
	return $res=$db->Execute($sql);
}

function _shn_alert_view_all_alerts()
{
	global $global;
	$db = $global['db'];
	$sql = $_SESSION['msg']['alert']['view_alert_sql'];
	return $db->Execute($sql);
}

function _shn_msg_add_long_web($id, $flag)
{
	global $global;
	$sql = "UPDATE msg_alerts SET web_enabled=$flag WHERE alert_uuid = '$id'";
	//print $sql;
	return $global['db']->Execute($sql);
}

function _shn_msg_check_long_web($id)
{
	global $global;
	$sql = "SELECT alert_uuid, web_enabled FROM msg_alerts WHERE alert_uuid = '$id' ";
	//print $sql;
	return $global['db']->Execute($sql);
}
?>
