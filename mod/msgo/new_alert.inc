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
* @author		Mahesh Kaluarachchi<mahesh@respere.com>
* @copyright    Respere http://www/respere.com
* @package		sahana
* @subpackage   msg
* @tutorial
* @version		$Id: main.inc,v 1.32 2008/08/02 15:29:45 priyanga Exp $
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

function _shn_new_alert()
{
	shn_form_fopen('new_alert');
	shn_form_fsopen(_t('New Alert'));
	$options = array();
	$options['cap'] = _t('CAP');
	//$options['edxl'] = _t('EDXL');
	//shn_form_radio($options, _t('Select Mode'), 'mode', 'onClick="submit(this);"', array('value'=>$_POST['mode']));
	$_POST['mode'] = 'cap';
	switch ($_POST['mode'])
	{
		case 'cap':
			//shn_form_label(null, 'CAP', null);
			shn_form_text(_t('Name'), 'name', 'size="25"', array("req"=>true,'value'=>$_POST['name']));
			$templates = array();
			$templates['existing'] = _t('Existing Alert Template');
			$templates['new'] = _t('New Alert');
			if(trim($_POST['name']  == '') || trim($_POST['name'] == NULL))
			{
				shn_form_radio($templates, _t(''), 'template', 'onClick="submit(this);"', null);
			}
			else
			{
				shn_form_radio($templates, _t(''), 'template', 'onClick="submit(this);"', array('value'=>$_POST['template']));
			}
			shn_form_fsclose();
			shn_form_fclose();
			$_SESSION['msg']['alert']['name'] = trim($_POST['name']);
			if(trim($_POST['name']) == '' && trim($_POST['template']) != null)
			{
				add_error(_t('Name is essential. Please complete and submit again'));
			}
			else
			{
				if($_POST['template'] == 'new')
				{
					//include_once 'handler_cap_new.inc';
					include_once 'handler_new_alert.inc';
				}
				if($_POST['template'] == 'existing')
				{
					//shn_msg_view_alert_temp();
					_shn_msg_alert_form_using_template();
					//shn_msg_select_template();
				}
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

function _shn_blank_template()
{
	
}

?>
