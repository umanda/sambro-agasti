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

function _shn_msg_alert_form_using_template()
{
global $global;
global $conf;
require_once $global['approot']."/inc/lib_locale/lib_locale.inc";
require_once('class_cap_alert.inc');
require_once('class_cap_info.inc');
require_once('class_cap_resource.inc');
require_once('class_cap_area.inc');
require_once('lib_cap_js.inc');

	$_SESSION['cap_msg'] = null;
	require_once('lib_cap_help.inc');
    $name = trim($_POST['name']);
	$mode = trim($_POST['mode']);
    $id = time();
    $message_id = $conf['alert_identifier'].$id;
    $today = date("Y-m-d");
    //print $today;
    
    $status = array('Actual'=>'Actual', 'Exercise'=>'Exercise', 
                     'System'=>'System', 'Test'=>'Test', 'Draft'=>'Draft');
    $msgType = array('Alert'=>'Alert', 'Update'=>'Update', 
                      'Cancel'=>'Cancel', 'Ack'=>'Ack', 'Error'=>'Error');
    $scope = array('Public'=>'Public', 'Restricted'=>'Restricted', 
                   'Private'=>'Private');
    
    print "<h2>" . _t("Template based CAP Alert") . "</h2>";
    
    shn_form_fopen("alert_submit",null,array('req_message'=>false,'name'=>'cap_new'));
    shn_form_hidden(array('seq'=>'new_cap_main'));
    shn_form_hidden(array('target'=>'new_alert_temp_base'));
    shn_form_fsopen(_t("New Cap Alert"));
    shn_form_hidden(array('time'=>$id,'stat'=>$status[_t("Actual")], 'name'=> $name, 'mode'=>$mode));
    shn_form_text(_t("Message Identifier"),'identifier',null,array('value'=>$message_id,'help'=>$help_identifire, 'req'=>true));
    shn_form_date(_t("Date Created"),'date_created',array('value'=>$today, 'req'=> true));
    shn_form_text(_t("Sender"),'sender','class=""',array('help'=>$help_sender, 'req'=>true));
    shn_form_text(_t("File Type"),'file_type',null, array('value'=>'cap', 'req' => true));
    shn_form_text(_t("File Version"),'file_version',null, array('value'=>'1.2', 'req' => true));
    //shn_form_upload(_('Upload file'), 'upload', null);
    
    
    
    shn_form_fsclose();
    //shn_form_hidden(array('name'=> $name));
    //shn_form_hidden(array('mode'=> $mode));
    shn_form_submit(_t("Next"), 'style="float: left"');
    
    shn_form_fsclose(); //Close capmessage form
    
    
    shn_form_fclose();
}

/**
 * Alert and Alert Template create form
 */
function shn_msg_alert_form($target, $values=null)
{
	shn_form_fopen("alert_submit", null,array('req_message'=>true));
    	shn_form_fsopen("Basic Information");
    	shn_form_text("Name","name","size='20'",array("req"=>true, 'value'=>$name));
    	shn_form_hidden(array("target"=>"$target"));
    	shn_form_submit("Save", $submit_opts = null);	
    shn_form_fclose();	
}

/**
 * Template list to Choose from
 */
function shn_msg_select_template($alert_id=null, $sender=null)
{
	$temp_list=shn_msg_alerts_list_generator("template");
	//print_r($temp_list);
	$num=count($temp_list);
	
	shn_form_fopen("",null,array('req_message'=>false));	
		shn_form_fsopen("Template List");
		print "Please select an alert template.";	
	?>
		<table width=50%>
		<thead>
			<tr>
				<td>Template Name</td>
				<td>Category</td>
				<td>Event</td>
				<td>Author</td>
			</tr>
		</thead>	
	<?php
	
	for($x=0; $x<$num; $x++)
	{
		?>
	
			<tr>
				<td><a href="index.php?mod=msg&act=pick_template&sender=<?php echo $sender?>&id=<?php echo $temp_list[$x]['id']?>&for=<?php echo $alert_id?>"><?php echo $temp_list[$x]['name'];?></a></td>
				<td><?php echo $temp_list[$x]['category'];?></td>
				<td><?php echo $temp_list[$x]['event'];?></td>
				<td><?php echo $temp_list[$x]['author'];?></td>
			</tr>
    			
		<?php 
	}
	?></table><?php
		shn_form_fsclose();
	shn_form_fsclose();
}

/**
 * Alerts and Templates List
 */
function shn_msg_alerts_list_form($type, $list)
{
	if($type=="alert"){
		$lable="Alerts";
		$link="view_alert";
	} else {
		$lable="Templates";
		$link="view_alert_temp";
	}
	echo '<h2>'._t($lable.' List').'</h2>';
	
	shn_form_fopen("alert_submit", null,array('req_message'=>false));
    	shn_form_fsopen("List");
    	//print_r($list);
    	
    	// display someway
    	?>
    	<table width=100%>
    		<thead>
    			<tr>
    				<td>Name</td>
    				<td>Category</td>
<!--    				<td>Type</td>
    				<td>Version</td>
-->
    				<td>Author</td>
    				
    			</tr>
    		</thead>	
    	<?php 	
    	$value = count($list);
    	for($x=0; $x <= ($value-1); $x++){
    		//print "<br>".$list[$x]['name']." ";
    		?>
    			<tr>
	    			<td><strong><a href="index.php?mod=msg&act=<?php echo $link ?>&id=<?php print $list[$x]['id']?>"><?php 
	    			if (($list[$x]['name'])==""){
	    				print "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
	    			} else {	
	    				print $list[$x]['name'];
	    			}
	    			?></a></strong></td>
	    			<td><?php print $list[$x]['category']?></td>
<!--	    			<td><?php print $list[$x]['alert_type']?></td>
	    			<td><?php print $list[$x]['alert_version']?></td>
-->
	    			<td><?php print $list[$x]['author']?></td>
    			</tr>
    		<?php 	
    	}
    	?>
    	</table>
    	<?php
    	
    shn_form_fclose();
}



function shn_msg_alerts_ivr_form($type, $list)
{
	if($type=="alert"){
		$lable="Alerts";
		$link="view_alert";
	} else {
		$lable="Templates";
		$link="view_alert_temp";
	}
	echo '<h2>'._t($lable.' List').'</h2>';

	shn_form_fopen("alert_submit", null,array('req_message'=>false));
	shn_form_fsopen("List");
	//print_r($list);
	 
	// display someway
	?>
    	<table width=100%>
    		<thead>
    			<tr>
    				<td>Name</td>
    				<td>Type</td>
    				<td>Version</td>
    				<td>Author</td>
    				
    			</tr>
    		</thead>	
    	<?php 	
    	$value = count($list);
    	for($x=0; $x <= ($value-1); $x++){
    		//print "<br>".$list[$x]['name']." ";
    		?>
    			<tr>
	    			<td><strong><a href="index.php?mod=msg&act=<?php echo $link ?>&id=<?php print $list[$x]['id']?>"><?php 
	    			if (($list[$x]['name'])==""){
	    				print "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
	    			} else {	
	    				print $list[$x]['name'];
	    			}
	    			?></a></strong></td>
	    			<td><?php print $list[$x]['alert_type']?></td>
	    			<td><?php print $list[$x]['alert_version']?></td>
	    			<td><?php print $list[$x]['author']?></td>
    			</tr>
    		<?php 	
    	}
    	?>
    	</table>
    	<?php
    	
    shn_form_fclose();
}
/**
 * 
 */
function shn_msg_alert_template_gen($type)
{
	shn_form_fopen('new_alert');
	shn_form_fsopen(_t('New Alert'));
	$options = array();
	$options['cap'] = _t('CAP');
	$options['edxl'] = _t('EDXL');
	shn_form_radio($options, _t('Select Mode'), 'mode', 'onClick="submit(this);"', array('value'=>$_POST['mode']));
	switch ($_POST['mode'])
	{
		case 'cap':
			shn_form_text(_t('Name'), 'name', 'size="25"', array('value'=> $_POST['name']));
			$templates = array();
			$templates['new'] = _t('New Alert');
			$templates['existing'] = _t('Existing Alert Template');
			shn_form_radio($templates, _t(''), 'template', 'onClick="submit(this);"', array('value'=>$_POST['template']));
			shn_form_fsclose();
			shn_form_fclose();
			if($_POST['template'] == 'new')
			{
				//include_once 'handler_cap_new.inc';
				include_once 'handler_new_alert.inc';
			}
			if($_POST['template'] == 'existing')
			{
				shn_msg_view_alert_temp();
			}
			break;
		
		case 'edxl':
			add_error ("EDXL is still under development! Please use CAP.");
			break;
			
		default:
			;
	}
	
		//shn_form_submit(_t('Send'));
	
}


/**
 * CAP viewer
 */
function shn_msg_view_alert_form($id,$type)
{
	$msg=shn_msg_get_xml_by_id($id);// get the xml
	$list=shn_msg_alert_details($id);// get the message details
	
	//print "<br>id is $id and type is $type";
	
	if($type=="template"){
		$label="Template";
		$panel ="<a href='index.php?mod=msg&act=update_alert&id=$id'>Update</a>&nbsp;&nbsp;&nbsp;<a href='index.php?mod=msg&act=delete_template&id=$id'>Delete</a>";
	} elseif($type=="alert") {
		$label="Alert";
		$panel ="<a href='index.php?mod=msg&act=send_alert&seq=select_contact&xml_id=$id'>Send</a>&nbsp;&nbsp;&nbsp;<a href='index.php?mod=msg&act=update_alert&id=$id'>Update</a>&nbsp;&nbsp;&nbsp;<a href='index.php?mod=msg&act=delete_alert&id=$id'>Delete</a>";
		//&nbsp;&nbsp;&nbsp;<a href='index.php?mod=msg&act=download_alert&id=$id'>Download</a>
	}
	
	print "<h2>$label View</h2>";
	shn_form_fopen("alert_submit", null,array('req_message'=>false));
		shn_form_fsopen("$label Information");
		shn_form_hidden(array("target"=>"send"));
			print "<strong>Message ID </strong>: ".$id;
			print "<strong><br>Message Name </strong>: ".$list['name'];
			print "<strong><br>Mime Type </strong>: ".$list['alert_type'];
			print "<strong><br>Alert Version </strong>: ".$list['alert_version'];
			print "<strong><br>Author </strong>: ".$list['author'];
			print "<strong><br>Message Type </strong>: ".$list['type']."<br>";
		
		
		print "<br><strong>$panel</strong>";
		shn_form_fsclose();
	shn_form_fclose();
}



