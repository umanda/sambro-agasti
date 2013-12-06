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
include_once $global['approot'].'/inc/lib_uuid.inc';
include_once 'lib_alert_db.inc';
include_once 'lib_alert_form.inc';

/**
 * Templates processor
 */
function shn_msg_alert_temp_process()
{
	$template_name = $_POST['name'];
	$alert_id = shn_create_uuid('msg');
	
	if($template_name!=""){	
		// store temp in the db
		shn_msg_alert_store($alert_id, $template_name);	
		/* Alert Update Code Should go here
		 */
		shn_msg_update_alert($alert_id);
	} else {
		add_error("Please provide a Template name!");
		shn_msg_new_alert_temp(); // calling template form again
	}	
}





/**
 * Generate a alert/template list
 */
function shn_msg_alerts_list_generator($type)
{
	if($type=="template"){ // for templates
		// fetch the template list
		$result = shn_msg_alert_list("$type"); // grab the list
		return $result;
	} elseif ($type=="cap") {// for alerts
		// fetch the alert list
		$result = shn_msg_alert_list("$type");
		return $result;
	} else {
		add_error("Unknown Message type!");
	}
}


/**
 * Grabe the Alert for update
 */
function shn_msg_alert_grabber($id)
{
	//include 'shn_cap_form.inc';
	//print "you're here";
	$xml=shn_msg_get_xml_by_id($id);
	if($xml!=null){		
		_shn_msg_cap_form($xml,$id);
	} else {
		add_warning("This alert is empty! Please update it.");
		_shn_msg_cap_form('',$id);
	}		
}

/**
 * Get XML Document when its ID is passed
 * @param $xml_id
 * @return text XML Document
 */
function shn_msg_get_xml_by_id($xml_id)
{
	$xml=shn_msg_xml_grabber($xml_id);// grab the XML from DB
	
	if($xml!==""){
		$doc = new DOMDocument();
		$doc->loadXML("$xml");
		return $xml;	
	} else {
		
	}
	//echo $xml;
	
	//print ".<hr>".$xx."<hr>";
  		
}

function create_tmp_xml_file($file, $tmp_content)
{
	$content=rtrim($tmp_content,"&quot;");
	
	$f=fopen($file,'w');
	if(!$f){
		add_error("Can not create the temp file under $file, please check the permission!");
	} else {
		fwrite($f,$content);
		//print "<br>File name is $file and the content is - $content";
	}
	fclose($f);	
		
}

/**
 * Get Type of XML - EDXL or CAP, and versions
 * @param $xml_doc Full XML Document
 * @return array('type'=>edxl/cap, 'version'=><version_number>)
 */
function shn_msg_get_xml_type($xml_doc)
{
	$type=null;
	$version=null;
	return array('type'=>$type,'version'=>$version);
}

?>