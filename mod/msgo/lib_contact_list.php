<?php

function shn_msg_display_contact_list($to_box_name='to')
{
	global $global;
	_shn_msg_contact_dropdown($to_box_name); 
}

function shn_msg_display_contact_list_with_phone($to_box_name='to')
{
	global $global;
	include_once ('lib_receive_console.inc');
	_shn_msg_contact_dropdown($to_box_name);
?>
<br/>
<?php
	$global['xajax']->printJavascript("res/js"); 
}
?>