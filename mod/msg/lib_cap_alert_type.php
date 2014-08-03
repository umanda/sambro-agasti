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
* @author       	Mifan Careem <mifan@respere.com>
* @copyright  		Respere - http://respere.com/
* @package      	sahana
* @subpackage   	msg
* @tutorial
* @version      	$Id$
* @license       	http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* @contribution    This code was developed and contributed to the project 
* by Respere Lanka (Pvt) Ltd.
*/


/**
 * Form for selecting the delivery type
 * Short - SMS,HF,RDF
 * Long - Email,web
 * Voice - IVR, Phone
 * @return unknown_type
 */
function shn_msg_cap_select_delivery_type($id = null,$full_message_xml=null)
{
	global $global;
	//print $id;
	//include_once $global['approot'].'/mod/msg/lib_contact.php';
	shn_form_fopen('send_alert&seq=transform_message&id='.$id,null,array('req'=>false));
	shn_form_fsopen(_t('Select Delivery Type'));
?>
<table>
	<thead>
		<tr>
			<td><?php echo _('Delivery Category');?></td>
			<td><?php echo _('Delivery Type');?></td>
			<td><?php echo _('Select');?></td>
		</tr>
	</thead>
	<tbody>
		<tr>
			<td rowspan=5><?php echo _('Short Text');?></td>
			<td><?php echo _('SMS');?></td>
			<td><input type="checkbox" name="select_type[]" id="select[]" value="short_to_sms"/></td>
		</tr>
		<tr>
			<td><?php echo _('HF');?></td>
			<td><input type="checkbox" name="select_type[]" id="select[]" disabled/></td>
		</tr>
		<tr>
			<td><?php echo _('RDF');?></td>
			<td><input type="checkbox" name="select_type[]" id="select[]" disabled/></td>
		</tr>
		<tr>
			<td><?php echo _('Email');?></td>
			<td><input type="checkbox" name="select_type[]" id="select[]" value="short_to_email"/></td>
		</tr>
		<tr>
			<td><?php echo _('Tweet');?></td>
			<td><input type="checkbox" name="select_type[]" id="select[]" value="short_to_tweet"/></td>
		</tr>
		
		
		<tr>
			<td rowspan=3><?php echo _('Long Text');?></td>
			<td><?php echo _('Email');?></td>
			<td><input type="checkbox" name="select_type[]" id="select[]" value="long_to_email"/></td>
		</tr>
		<tr>
			<td><?php echo _('Web');?></td>
			<?php 
			if($res = _shn_msg_check_long_web($id))
			{
				
				if($res->fields['web_enabled'] == 1)
				{
					$checked = 'checked';
					//print $checked;	
				}
				else
				{
					//$checked = '';
				}
			}
			else
			{
				add_error(_t('Web is not pre poulated due to an error. Please try again shortely'));
			}
			?>
			<td><input type="checkbox" name="select_type[]" id="select[]" value="long_to_web" <?php echo $checked?> /></td>
		</tr>
		<tr>
                        <td><?php echo _('Signage');?></td>
                        <td><input type="checkbox" name="select_type[]" id="select[]" value="long_to_signage"/></td>
                </tr>
	
		<tr>
			<td rowspan=2><?php echo _('Voice Text');?></td>
			<td><?php echo _('VoiceXML');?></td>
			<td><input type="checkbox" name="select_type[]" id="select[]" disabled/></td>
		</tr>
		<tr>
			<td><?php echo _('IVR');?></td>
			<td><input type="checkbox" name="select_type[]" id="select[]" value="voice_to_ivr"/></td>
		</tr>
		
	</tbody>
</table>
<?php 

	shn_form_fsclose();
	shn_form_hidden(array('id'=>$id));
	shn_form_submit('Next -> Transform Message');
	shn_form_fclose();
}

function shn_msg_cap_transform_message($delivery_type)
{
//	print $delivery_type." =mdelivery Type";
	global $global;
	include_once $global['approot'].'/mod/msg/xsl_convert.inc';
	$output_message = shn_msg_xsl_transform($_SESSION['msg']['send']['xml_id'],$delivery_type);
//print $output_message." = output message";
	shn_msg_alert_show_converted_message_send_form($output_message,$delivery_type);
}

function shn_msg_alert_contact_select()
{
	global $global;
	include_once $global['approot'].'/mod/msg/lib_contact.php';
	shn_form_fopen('send_alert&seq=delivery_type',null,array('req'=>false));
	shn_form_fsopen(_t('Select Contacts'));
	shn_form_textarea('Recipient List','to');
	//shn_msg_display_contact_list('to');
	_shn_msg_contact_dropdown('to');
	echo "<br/>";
	shn_form_fsclose();
	shn_form_hidden(array('xml_id'=>$_REQUEST['xml_id']));
	shn_form_submit('Next -> Alert Type');
	shn_form_fclose();
}



?>
