<?php
/**
 * @comment make changes
**/

global $global;
//print $_GET['seq'];
switch($_GET['seq'])
{
	case '':
		_shn_alert_view();
		break;
	case 'filter':
		$data_array = array();
		if($_GET['rpp'] != '' && $_GET['rpp'] != NULL)
		{
			$data_array['sort'] = $_SESSION['msg']['view_alert']['sort'];
			$data_array['title'] = $_SESSION['msg']['view_alert']['title'];
			$data_array['msg_type'] = $_SESSION['msg']['view_alert']['msg_type'];
			$data_array['date_sent'] = $_SESSION['msg']['view_alert']['date_sent'];
			$data_array['sender'] = $_SESSION['msg']['view_alert']['sender'];
			$data_array['priority'] = $_SESSION['msg']['view_alert']['priority'];
			$data_array['date_sent_to'] = $_SESSION['msg']['view_alert']['date_sent_to'];
			$data_array['status'] = $_SESSION['msg']['view_alert']['status'];
			$data_array['scope'] = $_SESSION['msg']['view_alert']['scope'];
			$data_array['category'] = $_SESSION['msg']['view_alert']['category'];
			$data_array['responseType'] = $_SESSION['msg']['view_alert']['responseType'];
			//$sql = _shn_alert_view_filter($_SESSION['msg']['view_alert']['title'] , $_SESSION['msg']['view_alert']['priority'] , $_SESSION['msg']['view_alert']['msg_type'] , $_SESSION['msg']['view_alert']['sender'] , $_SESSION['msg']['view_alert']['date_sent'] , $_SESSION['msg']['view_alert']['sort'], $_SESSION['msg']['view_alert']['date_sent_to'] );
			$sql = _shn_alert_view_filter($data_array);
			//print $sql;
			_shn_alert_view($sql);
			
		}
		else
		{
			$data_array['title'] = trim($_POST['title']);
			$_SESSION['msg']['view_alert']['title'] = $title;
			$data_array['priority'] = $_POST['opt_msg_priority'];
			if($priority == '==')
			{
				$priority = '';
			}
			$_SESSION['msg']['view_alert']['priority'] = $priority;
			$data_array['msg_type'] = $_POST['msg_type'];
			$_SESSION['msg']['view_alert']['msg_type'] = $msg_type;
			$data_array['sender'] = trim($_POST['sender']);
			$_SESSION['msg']['view_alert']['sender'] = $sender;
			$data_array['date_sent'] = trim($_POST['date_sent']);
			$_SESSION['msg']['view_alert']['date_sent'] = $date_sent;
			$data_array['sort'] = $_POST['sort'];
			$_SESSION['msg']['view_alert']['sort'] = $sort;
			$data_array['date_sent_to'] = $_POST['date_sent_to'];
			$_SESSION['msg']['view_alert']['date_sent_to'] = $date_sent_to;
			$data_array['status'] = $_POST['status'];
			$_SESSION['msg']['view_alert']['status'] = $status;
			$data_array['scope'] = $_POST['scope'];
			$_SESSION['msg']['view_alert']['scope'] = $scope;
			$data_array['category'] = $_POST['category'];
			$_SESSION['msg']['view_alert']['category'] = $category;
			$data_array['responseType'] = $_POST['responseType'];
			$_SESSION['msg']['view_alert']['responseType'] = $responseType;
			
			$sql = _shn_alert_view_filter($data_array);
			
			
			//$sql = _shn_alert_view_filter($title , $priority, $msg_type, $sender, $date_sent, $sort, $date_sent_to);
			_shn_alert_view($sql);
		}
		break;
	case 'indv_alert':
		_shn_alert_indv_view();
		break;
	case 'alert_more':
		_shn_alert_indv_view_more();
		break;
	case 'recent_alert':
		_shn_alert_recent_alerts();
		break;
	
}




function _shn_alert_view($sql = NULL)
{
	global $global;
	global $conf;
	$db = $global['db'];
	include_once $global['approot'].'/mod/msg/xsl_convert.inc';
	include_once $global['approot'].'/mod/msg/lib_cap_alert_type.php';
	require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_add_feed('rss_alerts_list',_('Click to subscribe to RSS feed'));
	echo "<h2 align='center'>"._t('List of Alerts')."</h2>";
	include_once 'lib_alert_db.inc';
	shn_form_fopen('view_list_alert', null, null);
	shn_form_fsopen(_t('Scroll down to view the SEARCH results'));
	shn_form_text(_('Title'), 'title', 'size="25"', array('value'=>$title));
	shn_form_opt_select('opt_msg_priority', _t('Priority'), 'priority', array('value'=>$priority));
	$msgType = array(''=>'', 'Alert'=>'Alert', 'Update'=>'Update', 
	                      'Cancel'=>'Cancel', 'Ack'=>'Ack', 'Error'=>'Error');
	$status = array(''=>'', 'Actual'=>'Actual', 'Exercise'=>'Exercise', 
	                     'System'=>'System', 'Test'=>'Test', 'Draft'=>'Draft');  
	$scope = array(''=>'', 'Public'=>'Public', 'Restricted'=>'Restricted', 
	                   'Private'=>'Private');
	$category = array(''=>'', 'Geo'=>'Geo', 'Met'=>'Met', 'Safety'=>'Safety', 
                      'Security'=>'Security', 'Rescue'=>'Rescue', 
                      'Fire'=>'Fire', 'Health'=>'Health', 'Env'=>'Env', 
                      'Transport'=>'Transport', 'Infra'=>'Infra', 
                      'CBRNE'=>'CBRNE', 'Other'=>'Other');
	$responseType = array(''=>'', 'Shelter'=>'Shelter', 'Evacuate'=>'Evacuate', 
			                          'Prepare'=>'Prepare', 'Execute'=>'Execute', 
			                          'Monitor'=>'Monitor', 'Assess'=>'Assess', 
			                          'None'=>'None');
	
	shn_form_select($msgType, _t("Message Type"), 'msg_type', null,array('value'=>$msg_type));
	shn_form_select($status, _t("Status"), 'status', null,array('value'=>$status));
	shn_form_select($scope, _t("Scope"), 'scope', null,array('value'=>$scope));
	shn_form_select($category, _t("Category"), 'category', null,array('value'=>$category));
	shn_form_select($responseType, _t("Response Type"), 'responseType', null,array('value'=>$responseType));
	shn_form_text(_t('Sender'), 'sender', 'size="25"', array('value'=>$sender));
	
	
	//shn_form_datetime(_t("Date Sent"),'date_sent',array('value'=>trim($_POST['date_sent'])));
	shn_form_date(_t("Date Sent From"), 'date_sent', array('value'=>$date_sent));
	shn_form_date(_t("To"), 'date_sent_to', array('value'=>$date_sent_to));
	shn_form_hidden(array('seq'=>'filter'));
	shn_form_submit(_('Search'));
	shn_form_fsclose();
	shn_form_fsopen(_t('Sort'));
	$sort = array('' => '', 'title'=>'Title', 'priority'=>'Priority', 'msg_type'=>'Message Type', 'sender'=>'Sender', 'sent'=>'Date of Sent');
	shn_form_select($sort, _t('Sort By'), 'sort', 'onChange="submit(this)"', array('value'=>$_SESSION['msg']['view_alert']['sort']));
	shn_form_submit(_t('Sort'));
	shn_form_fsclose();
	shn_form_fclose();
	//var_dump($res);
	//print $sql;
	if($_POST['seq'] == '' && $_GET['seq'] != 'filter')
	{
		//$res = shn_msg_get_all_alert_uuid();
		$q = "SELECT alert_uuid FROM msg_alerts WHERE visible=1 AND file != '' AND alert_uuid = extractValue(file, '/alert/identifier') AND web_enabled = 1";
		//print $q;

		$res = shn_paging_get_report($q, $conf['records_per_page'], null, null);
	}
	else
	{
		$res = shn_paging_get_report($sql, $conf['records_per_page'], null, null);
	}
    echo "<table class='alertList'>\n<tbody>";
	while($res != NULL && !$res->EOF)
	{
		$xml_id = $res->fields['alert_uuid'];
		$_SESSION['msg']['send']['xml_id'] = $xml_id;
		$delivery = 'view_data';
		shn_msg_cap_transform_message($delivery);
		$res->MoveNext();
	}
    echo "<tbody></table>";
    
}

function _shn_alert_indv_view()
{
	global $global;
	include_once $global['approot'].'/mod/msg/xsl_convert.inc';
	include_once $global['approot'].'/mod/msg/lib_cap_alert_type.php';
	$identifier = $_GET['identifier'];
	//print $identifier;
	$_SESSION['msg']['send']['xml_id'] = $identifier;
	$delivery = 'view_data_indv';
	shn_msg_cap_transform_message($delivery);
	
}

function _shn_alert_indv_view_more()
{
	global $global;
	include_once $global['approot'].'/mod/msg/xsl_convert.inc';
	include_once $global['approot'].'/mod/msg/lib_cap_alert_type.php';
	$xml_id = trim($_POST['xml_id']);
	$_SESSION['msg']['send']['xml_id'] = $xml_id;
	$delivery = 'view_data_indv_more';
	shn_msg_cap_transform_message($delivery);
	
}

function _shn_alert_recent_alerts()
{
	global $global;
	include_once $global['approot'].'/mod/msg/xsl_convert.inc';
	include_once $global['approot'].'/mod/msg/lib_cap_alert_type.php';
	include_once 'lib_alert_db.inc';
	require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_add_feed('rss_recent_alerts_list',_('Click to Subscribe to RSS feed'));
	echo '<h1 align="center">'.' Recently modified Alerts'.' </h1>';
	$res = _shn_msg_recent_alerts();
	//if($res->RecordCount())
	echo "<table class='alertList'>\n<tbody>";
	while($res != NULL && !$res->EOF)
	{
		$xml_id = $res->fields['alert_uuid'];
		$_SESSION['msg']['send']['xml_id'] = $xml_id;
		$delivery = 'view_data';
		shn_msg_cap_transform_message($delivery);
		$res->MoveNext();
	}
    echo "<tbody></table>";
	
}



?>
