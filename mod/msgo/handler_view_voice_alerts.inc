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
* ----------
* HISTORY	
* 	@desc		The original version of this file was created by:	
* 	@author		Sudheera R. Fernando <sudheera@opensource.lk>
* 	@author		Sriganeshan<sri@opensource.lk>
* ----------
* @author		Mifan Careem <mifan@respere.com>
* @author		Pradeeper <pradeeper@respere.com>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage   msg
* @tutorial
* @version		$Id: main.inc,v 1.32 2008/08/02 15:29:45 priyanga Exp $
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function shn_msg_view_ivr_form($list)
{
	$id = $list[0]['ivr_alert_id'];
	//$panel ="<a href='index.php?mod=msg&act=add_ivr_alert&id= $id'>Add</a>&nbsp;&nbsp;&nbsp;<a href='index.php?mod=msg&act=update_ivr_alert&id=$list[0]['ivr_alert_id']'>Update</a>&nbsp;&nbsp;&nbsp;<a href='index.php?mod=msg&act=delete_ivr_alert&id=$list[0]['ivr_alert_id']'>Delete</a>";
	print "<h2>$label View</h2>";
	shn_form_fopen("ivr_submit", null,array('req_message'=>false));
	shn_form_fsopen("IVR Information");
	shn_form_hidden(array("target"=>"send"));
	print "<strong>IVR ID </strong>: ".$list[0]['ivr_alert_id'];
	print"<br/>";
	print "<strong><br>IVR Name </strong>: ".$list[0]['ivr_alert_name'];
	print"<br/>";
	print "<strong><br>IVR Content </strong>: ".$list[0]['ivr_alert_content'];
	print"<br/>";
	print"<br/>";
	print"<br/>";
//	shn_form_upload(_t('Attachment'),'info_derefUri');
	
	if($_REQUEST['id'] != NULL)
	{
		$file_id = trim($_REQUEST['id']);
		//print $file_id;
		shn_files_link($file_id,$return=false);
		//shn_files_return_link($file_id);
		echo '<br>';
		//shn_files_link2($file_id);
	}
	
	//print "<br><strong>$panel</strong>";
	shn_form_fsclose();
	shn_form_fclose();
}
function shn_msg_ivr_list_form($list)
{
	$lable = "IVR Alerts";
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
	    				<td>ID</td>
	    				
	    				
	    			</tr>
	    		</thead>	
	    	<?php 	
	    	$value = count($list);
	    	for($x=0; $x <= ($value-1); $x++){
	    		//print "<br>".$list[$x]['name']." ";
	    		?>
	    			<tr>
		    			<td><strong><a href="index.php?mod=msg&act=view_ivr&id=<?php print $list[$x]['ivr_alert_id']?>"><?php 
		    			if (($list[$x]['ivr_alert_name'])==""){
		    				print "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
		    			} else {	
		    				print $list[$x]['ivr_alert_name'];
		    			}
		    			?></a></strong></td>
		    			<td><?php print $list[$x]['ivr_alert_id']?></td>
		    		</tr>
	    		<?php 	
	    	}
	    	?>
	    	</table>
	    	<?php
	    	
	    shn_form_fclose();
		
}
/*
function shn_msg_add_ivr($list)
{
	$id = $list[0]['ivr_alert_id'];
	$ivr_id = $list['ivr_alert_id'];
	$ivr_id = $list['ivr_alert_name'];
	// $fileName = "asd";
	//var_dump($file_name);
	//$tmpName  = $_FILES['info_derefUri']['tmp_name'];
	//var_dump($tmpName);
	//$fileSize = $_FILES['info_derefUri']['size'];
	//$fileType = $_FILES['info_derefUri']['type'];
	//echo $tmpName;
	move_uploaded_file($tmpName, $upload_dir.'/'.$fileName);
	
	$fp      = fopen($tmpName, 'r');
	$content = fread($fp, filesize($tmpName));
	$content = addslashes($content);
	//var_dump($content);
	fclose($fp);
	$insert_file_array = array();
	//$insert_file_array['file_id'] = shn_create_uuid('file');
	$insert_file_array['ivr_alert_id'] = $f_id;//trim($_POST['identifier']);
	$insert_file_array['name'] = $fileName;
	$insert_file_array['type'] = $fileType;
	$insert_file_array['size'] = $fileSize;
	$insert_file_array['content'] = "";
	//echo $fileName;
	global $global;
	$rset = $global['db']->AutoExecute('msg_alert_files', $insert_file_array, 'INSERT');
	
}*/
