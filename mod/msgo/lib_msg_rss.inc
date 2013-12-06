<?php
/**
* Sahana Messaging module Feeds
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author        J P Fonseka <jo@respere.lk>
* @copyright     Respere http://respere.com
* @package       Sahana
* @subpackage    msg
* @license       http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/
require_once('class_cap_alert.inc');
// require_once('class_cap_info.inc');
// require_once('class_cap_resource.inc');
// require_once('class_cap_area.inc');

function shn_xml_msg_rss_alert(){
    global $global;
    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_open();
    shn_rss_channel_open(_t('CAP Alerts'),_t('Cap messages issued by the sahana system.'));
    
    $url="http://".$_SERVER[HTTP_HOST].$_SERVER['PHP_SELF']."?mod=msg&amp;act=cap_download&amp;stream=text&amp;type=messages";

    $MSG_DIR = '../res/msg';
    $files = scandir($MSG_DIR.'/cap/messages');
    
    $messages=array();
    $time=array();
    foreach ($files as $file)
    {
        $message=array();
        if(strstr($file,'.xml') || strstr($file,'.XML')){
            $msg = new Msg_CapAlert($MSG_DIR.'/cap/messages/' . $file);
            $info = $msg->getInfo();
            $message['title']= $info->getHeadline()." : ".$msg->getSent();
            $message['desc'] = $info->getDescription();
            $message['url']= $url. '&amp;file='.$file;
            array_push($time,$msg->getSent());
            array_push($messages , $message);
        }
    }
    
    arsort($time);
    
    $i=20; //max links 
    foreach ($time as $key=>$t){
        if($i<1)break;
        --$i;
        $message=$messages[$key];
        shn_rss_item($message['title'],$message['url'],$message['desc']);
    }

    shn_rss_channel_close();
    shn_rss_close();
}

function shn_xml_msg_rss_recent_alerts_list(){
    global $global;
    global $conf;
    //_shn_ims_expire_date_check();
    require_once($global['approot']."/inc/lib_rss.inc");
    include_once 'lib_alert_db.inc';
    shn_rss_open();
    shn_rss_channel_open(_('Recently modified Alerts List'),_('Following are the list of Recently modified CAP Alerts'));

    //get a list of expired item list limit it to 30 
    //$sql="SELECT item_id,inv_id,item_name,amount,ct_unit.name as unit,manufactured_date,expire_date FROM ims_item_records as i INNER JOIN ct_unit ON ct_unit.unit_uuid = i.unit WHERE state='expired' ORDER BY expire_date LIMIT 0, 30;";
    define('ADODB_FETCH_ASSOC',2);
    $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
    $res = _shn_msg_recent_alerts();//$global['db']->Execute($sql);
    //var_dump($res);
    if (!$res){add_error($global['db']->ErrorMsg());}
    $url1="http://".$_SERVER[HTTP_HOST].$_SERVER['PHP_SELF']."?mod=msg&amp;act=view_list_alert&amp;seq=indv_alert&amp;identifier=";
    foreach($res as $record){
    if($record['priority'] != '' || $record['priority'] != NULL)
        {
        	$pri_text = _(' Priority of ').$record['priority'];
        }
        if($record['msg_type'] != '' || $record['msg_type'] != NULL)
        {
        	$msg_type_text = _t(' Message Type of ').$record['msg_type'];
        }
        if($record['category'] != '' || $record['category'] != NULL)
        {
        	$category_text = _(' Category of ').$record['category'];
        }
        //$desc=_("This item is manufactured on ").$record['manufactured_date']._(" and expired on ").$record['expire_date']."."._(" And Currently there are ").$record['amount']." ".$record['unit']._(" left in the inventory.");
        $desc = $pri_text.' '.$msg_type_text.' '.$category_text.' '._t(' issued by ').$record['sender']._t(' on ').$record['sent_date'];
    	$url = $url1.$record['alert_uuid'];
    	if($record['head_line'] == '' || $record['head_line'] == NULL)
    	{
    		$record['head_line'] = $conf['default_title'];
    	}
    	$title = $record['head_line'];
    	if($record['area'] != '' && $record['head_line'] != '')
    	{
    		$title = $title.', '.$record['area'];
    	}
    	shn_rss_item($title,$url,$desc);
    }

    shn_rss_channel_close();
    shn_rss_close();
}

function shn_xml_msg_rss_alerts_list()
{
	global $global;
	global $conf;
    //_shn_ims_expire_date_check();
    require_once($global['approot']."/inc/lib_rss.inc");
    include_once 'lib_alert_db.inc';
    shn_rss_open();
    shn_rss_channel_open(_('CAP Alerts List'),_('Following are the list of CAP Alerts'));

    //get a list of expired item list limit it to 30 
    //$sql="SELECT item_id,inv_id,item_name,amount,ct_unit.name as unit,manufactured_date,expire_date FROM ims_item_records as i INNER JOIN ct_unit ON ct_unit.unit_uuid = i.unit WHERE state='expired' ORDER BY expire_date LIMIT 0, 30;";
    define('ADODB_FETCH_ASSOC',2);
    $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
    //$sql = $_SESSION['msg']['alert']['view_alert_sql'];
    $sql = "SELECT alert_uuid, ExtractValue(file, '/alert/info/headline') AS head_line, ExtractValue(file, '/alert/sent') AS sent_date, ExtractValue(file, '/alert/info/senderName') AS sender, ExtractValue(file, '/alert/info/priority') AS priority, ExtractValue(file, '/alert/info/area/areaDesc') AS area, ExtractValue(file, '/alert/info/category') AS category, ExtractValue(file, '/alert/msgType') AS msg_type FROM msg_alerts WHERE visible=1 AND file != '' AND alert_uuid = ExtractValue(file, '/alert/identifier') AND web_enabled = 1 ";
    //print $sql;
    $res = $global['db']->Execute($sql);/*_shn_alert_view_all_alerts();*///$global['db']->Execute($sql);
    //var_dump($res);
    if (!$res){add_error($global['db']->ErrorMsg());}
    $url1="http://".$_SERVER[HTTP_HOST].$_SERVER['PHP_SELF']."?mod=msg&amp;act=view_list_alert&amp;seq=indv_alert&amp;identifier=";
    foreach($res as $record){
        //$desc=_("This item is manufactured on ").$record['manufactured_date']._(" and expired on ").$record['expire_date']."."._(" And Currently there are ").$record['amount']." ".$record['unit']._(" left in the inventory.");
        if($record['priority'] != '' || $record['priority'] != NULL)
        {
        	$pri_text = _(' Priority of ').$record['priority'];
        }
        if($record['msg_type'] != '' || $record['msg_type'] != NULL)
        {
        	$msg_type_text = _t(' Message Type of ').$record['msg_type'];
        }
        if($record['category'] != '' || $record['category'] != NULL)
        {
        	$category_text = _(' Category of ').$record['category'];
        }
    	
    	
    	//$desc = _(' of priority ').$record['priority']._t(' issued by ').$record['sender']._t(' on ').$record['sent_date'];
    	$desc = $pri_text.' '.$msg_type_text.' '.$category_text._t(' issued by ').$record['sender']._t(' on ').$record['sent_date'];
        $url = $url1.$record['alert_uuid'];
    	if($record['head_line'] == '' || $record['head_line'] == NULL)
    	{
    		$record['head_line'] = $conf['default_title'];
    	}
    	$title = $record['head_line'];
    	if($record['area'] != '' && $record['head_line'] != '')
    	{
    		$title = $title.', '.$record['area'];
    	}
    	shn_rss_item($title,$url,$desc);
    }

    shn_rss_channel_close();
    shn_rss_close();
	
}

?>