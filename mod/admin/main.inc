<?php
/**
 *
 * Sahana Admin & ACL section
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available throughacl_user_roles the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana - http://sahana.sourceforge.net
 * @author     Ravindra <ravindra@opensource.lk>
 * @author     Chamindra <chamindra@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 *
 */

global $global;

include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once "menu.inc";
include_once "acl.inc";
include_once "location.inc";
include_once $global['approot']."inc/lib_security/auth_form.inc";
include_once $global['approot']."inc/lib_security/lib_auth.inc";
// Incident Management Module
include_once $global['approot']."mod/admin/ims_main.inc";
include_once $global['approot']."mod/admin/conf_admin.inc";

// Module Management Console
include_once $global['approot']."mod/admin/mmc_main.inc";
include_once $global['approot'] . '/inc/lib_xajax.inc';



function shn_admin_mainmenu()
{
	_shn_admin_mainmenu();
}

function shn_admin_view()
{
	global $global;
	?>

<p><b><?=_t("You called the admin view")?> </b></p>
<p><?=_t(" on module") ?></p>
	<?php

}

function shn_admin_field_option_config(){
	include_once 'lib_fo_config.inc';
	_shn_admin_field_option_config();
}

function shn_admin_default()
{

    global $conf;
    
    ?>

<div id="home">
<img width="100%" src="res/img/cap-banner.png" style="padding-bottom:5px; margin-top:-10px">
<h2>ADMINISTRATOR RESOURCE CENTER</h2>

<table border="0">
  <tr>
    <td valign="top" width="300"><p>
	<strong>What is CAPITUS Administration?</strong></p>
<p>The main function for an Administrator is granting and revoking user permissions. When a user requests for permission to use CAPITUS: 
<ul>
  <li>Grant permissions to that use through <strong>User Management</strong> sub menu within the <strong>System Security</strong> options</li>
  <li>Click on User Management submenu, then access the <strong>Edit Roles of a User</strong></li>
  <li>Select the user to grant permission and submit, that's it!</li>
</ul>
</p></td>
    <td valign="top">
      <p><strong>Reference material</strong></p>
       <ul>
          <li><a href="https://github.com/waidyanatha/sambro-agasti/wiki/users#edit-roles">Quick Guide: Editing Roles of a User</a></li><br>
          <li><a href="https://github.com/waidyanatha/sambro-agasti/wiki/users">Wiki on the System's Users</a></li><br>
	  <li><a href="http://docs.oasis-open.org/emergency/cap/v1.2/CAP-v1.2-os.html">What is CAP Version 1.2?</a></li>
       </ul>
    </td>

    <td valign="top">
      <p><strong>Video on setting user permissions</strong></p>
	<iframe width="300" height="180" src="//www.youtube.com/embed/n0iKp60jjtY?list=PL23CB283949653EDC" frameborder="0" allowfullscreen></iframe>
    </td>
  </tr>
</table>

<div style="box-shadow: 0 0.5px 0 0 #ffffff inset, 0 1px 2px 0 #B3B3B3;">
<h3 style="padding:5px">FAQ</h3>
</div>

<?php
 class rss {
     var $feed;

  function rss($feed) 
    {   $this->feed = $feed;  }
 
  function parse() 
    {
    $rss = simplexml_load_file($this->feed);
    

    $rss_split = array();
    foreach ($rss->channel->item as $item) {

    $title = (string) $item->title; // Title
    $link   = (string) $item->link; // Url Link
    $description = (string) $item->description; //Description
    $rss_split[] = '<div>
        <a href="'.$link.'" target="_blank" title="" >
            '.$title.' 
        </a>
   <hr>
          </div>
';
    }
    return $rss_split;
  }
  function display($numrows,$head) 
  {
    $rss_split = $this->parse();

    $i = 0;
    $rss_data = '<div class="vas">
           <div class="title-head">
         '.$head.'
           </div>
         <div class="feeds-links">';
    while ( $i < $numrows ) 
   {
      $rss_data .= $rss_split[$i];
      $i++;
    }
    $trim = str_replace('', '',$this->feed);
    $user = str_replace('&lang=en-us&format=rss_200','',$trim);
    $rss_data.='</div></div>';
    return $rss_data;
  }
}
?>
<style>
.vas{
    float:left;
    width:30%;
    padding:10px;
}
.title-head {
    font-size:18px;
    font-weight:bold;
    text-align:left;
    background-color:#006699;
    color:#FFFFFF;
    padding:5px;}
.feeds-links {
    text-align:left;
    padding:5px;
    border:1px solid #dedede;
 }
</style>

<div>
  <?php
  include('rssclass.php');
  $feedlist = new rss('http://www.gdacs.org/xml/rss.xml');
  echo $feedlist->display(3,"Latest disaster alerts ");
  /*
  $feedlist = new rss('http://www.wmo.int/rss/index.php');
  echo $feedlist->display(3,"WMO");
  */
 
  $feedlist = new rss('http://feeds.sciencedaily.com/sciencedaily/earth_climate/storms?format=xml');
  echo $feedlist->display(3,"Storms News");

  $feedlist = new rss('http://feeds.sciencedaily.com/sciencedaily/earth_climate/natural_disasters?format=xml');
  echo $feedlist->display(3,"Natural Disasters News");


  ?> 
  </div>


</div>

<?php
}

function shn_admin_modadmin()
{
	global $global;

	// include original module admin section
	include $global['approot']."/mod/".$global['module']."/admin.inc";

	// compose and call the relevant module function
	$module_function = "shn_".$global['module']."_".$global['action'];

	if(!function_exists($module_function)) {
		$module_function="shn_".$global['module']."_adm_default";
	}

	// @TODO remove. call the admin menu shn_<mod>_adminmenu if it exists
	/*$admin_menu = "shn_".$global['module']."_adminmenu";

	if(function_exists($admin_menu))
	$admin_menu();
	*/

	$module_function();
}

function shn_admin_check_sec_policies()
{
	shn_acl_check_valid_policy();
}

function shn_admin_acl_change_user_status($error=false)
{
	_shn_admin_acl_user_menu($module);
	shn_acl_form_change_user_status();
}

function shn_admin_acl_change_user_status_cr($error=false)
{
	_shn_admin_acl_change_user_status_cr();
	_shn_admin_acl_enable_locking_on_lock_user();
	shn_admin_acl_change_user_status();
}

function shn_admin_acl_unlock_user($error=false)
{
	_shn_admin_acl_user_menu($module);
	shn_acl_form_unlock_user();
}
function shn_admin_acl_unlock_user_cr($error=false)
{
	_shn_admin_acl_unlock_user_cr();
	_shn_admin_acl_enable_locking_on_lock_user();
	shn_admin_acl_unlock_user();
}

function shn_admin_acl_event_log($error=false)
{
	shn_acl_form_event_log();
}

function shn_admin_add_user($error=false)
{
	_shn_admin_acl_user_menu($module);
	shn_auth_form_user_add($error);
}

function shn_admin_add_user_cr()
{
	include_once "errors.inc";
	if(shn_auth_add_user_cr()==true) {
		shn_admin_add_user();
		return;
	}

	_shn_admin_acl_user_menu();
	shn_auth_form_user_add($error);
}

function shn_admin_del_user($error=false)
{
	_shn_admin_acl_user_menu($module);
	shn_auth_form_user_del();
}

function shn_admin_del_user_cr()
{
	_shn_auth_del_user_cr();
	_shn_admin_acl_user_menu();
}

function shn_admin_reset_pwd($error=false)
{
	_shn_admin_acl_user_menu();
	shn_auth_form_reset_pwd($error);
}

function shn_admin_reset_pwd_cr()
{
	include_once "errors.inc";
	$done=_shn_admin_reset_pwd_cr();


	_shn_admin_acl_user_menu();

}

function shn_admin_ch_pwd($error=false)
{
	_shn_admin_acl_user_menu($module);
	shn_auth_form_ch_pwd($error);
}

function shn_admin_ch_pwd_cr()
{
	include_once "errors.inc";
	$error=_shn_admin_ch_pwd_cr();
	?>
<div id="result_msg"><?php
if($error){
	$msg="An error ocurred";
}else{
	$msg="The Password was succesfully updated ";
}

if($error)
display_errors();
?></div>
<?php
_shn_admin_acl_system_menu();
}




function shn_admin_acl_user_roles()
{

	_shn_admin_acl_user_roles();
}


function shn_admin_acl_privacy()
{

	_shn_admin_acl_privacy_menu(true);
}

function shn_admin_acl_enable_mods()
{

	_shn_admin_acl_enable_mods();
}
function shn_admin_acl_enable_mods_cr()
{

	_shn_admin_acl_enable_mods_cr();
}
function shn_admin_acl_enable_acl()
{

	_shn_admin_acl_enable_acl();
}

function shn_admin_acl_enable_acl_cr()
{

	_shn_admin_acl_enable_acl_cr();
}
function shn_admin_acl_enable_signup()
{

	_shn_admin_acl_enable_signup();
}

function shn_admin_acl_enable_signup_cr()
{

	_shn_admin_acl_enable_signup_cr();
}


function shn_admin_acl_enable_locking()
{

	_shn_admin_acl_enable_locking();
}
function shn_admin_acl_enable_locking_cr()
{
	// changed by Ravith.
	// enable the locking
	$act = $_POST['action'];
	if($act == 'enable'){
		_shn_admin_acl_enable_locking_cr(true);
		add_confirmation(_("User Locking is enabled now."));
	}else if($act=='disable'){
		_shn_admin_acl_enable_locking_cr(false);
		add_confirmation(_("User Locking is disabled now."));
	}
	// show the ui
	shn_acl_form_enable_locking();
}

function shn_admin_acl_state()
{
	_shn_admin_acl_state();
}




function shn_admin_add_loc()
{
	_shn_admin_location_form();
}

function shn_admin_add_loc_cr()
{
	shn_location_add();
	_shn_admin_location_form();
}

function shn_admin_view_loc()
{
	_shn_admin_location_view_form();
}

function shn_admin_view_loc_cr()
{
	if(isset($_POST{"chk_start"})) {
		$loc=0;
	}else {
		$level="loc_select_".$_POST{"opt_location_type"};
		$loc=$_POST{$level};
	}
	if($loc=="0"){
		add_error("Select the \"Location\" first and then select the \"Location Level\"");
		_shn_admin_location_view_form();
	}
	else{
		_shn_admin_location_edit_form($loc);
	}
}

function shn_admin_edit_loc_cr()
{
	$act=$_POST{"action"};
	$loc=$_POST{"loc_id"};
	switch($act) {
		case "edit":
			$loc=array();
			$loc["loc"]=$_POST{"loc_id"};
			$loc["name"]=$_POST{"loc_name"};
			$loc["desc"]=$_POST{"desc"};
			$loc["iso"]=$_POST{"iso"};

			shn_location_edit($loc);
			_shn_admin_location_view_form();
			break;
		case "del":
			shn_location_del($loc);
			_shn_admin_location_view_form();
			break;
		default:
			_shn_admin_location_view_form();
			break;
	}

}

function shn_admin_loc_range()
{
	_shn_admin_location_range_form();
}

function shn_admin_loc_range_cr()
{
	_shn_admin_loc_range_cr();
}


function shn_admin_loc_start()
{
	_shn_admin_location_start_form();
}

function shn_admin_loc_start_cr()
{
	_shn_admin_loc_start_cr();
}

function shn_admin_loc_lvl()
{
	_shn_admin_levels_form();
}
function shn_admin_loc_lvl_cr()
{
	_shn_adm_loc_lvl_cr();
}
function shn_admin_start_loc()
{
	_shn_admin_location_view_form();
}


/************************************/
function shn_admin_acl_user()
{
	_shn_admin_acl_user();
}
function shn_admin_acl_user_edit_roles($error=false)
{
	_shn_admin_acl_user_edit_roles();
}
function shn_admin_acl_user_edit_roles_cr($error=false)
{
	_shn_admin_acl_user_edit_roles_cr();
}

function shn_admin_acl_data_privacy()
{
	_shn_admin_acl_privacy_menu();
	_shn_admin_acl_data_privacy();
}
function shn_admin_acl_role_edit_perms()
{
	_shn_admin_acl_role_edit_perms();
}

function  shn_admin_acl_role_edit_perms_cr()
{
	_shn_admin_acl_role_edit_perms_cr();
}

function shn_admin_acl_data_classifications_tables()
{
	_shn_admin_acl_privacy_menu();
	_shn_admin_acl_data_classifications_tables();
}

function shn_admin_acl_data_classifications_tables_cr()
{
	_shn_admin_acl_data_classifications_tables_cr();
}
/*
 function shn_admin_acl_existing_perms_tab()
 {
 _shn_admin_acl_existing_perms_tab();
 }

 function shn_admin_acl_user_cr()
 {
 _shn_admin_acl_user_cr();
 }



 function shn_admin_acl_user_perms()
 {
 _shn_admin_acl_user_perms();
 }

 function shn_admin_acl_user_add_roles($module=NULL,$error=false)
 {
 _shn_admin_acl_user_add_roles();
 }

 function shn_admin_acl_user_add_roles_cr($module=NULL,$error=false)
 {
 _shn_admin_acl_user_add_roles_cr();
 }

 function shn_admin_acl_user_edit_roles($error=false)
 {
 _shn_admin_acl_user_edit_roles();
 }

 function shn_admin_acl_user_edit_roles_cr($error=false)
 {
 _shn_admin_acl_user_edit_roles_cr();
 }
 */

/**************************************/
/*
 function shn_admin_acl_role_perms()
 {
 _shn_admin_acl_role_perms();
 }

 function shn_admin_acl_role_edit_perms()
 {
 _shn_admin_acl_role_edit_perms();
 }

 function shn_admin_acl_role_edit_perms_cr()
 {
 $module=$_GET{"sel"};
 _shn_admin_acl_role_edit_perms_cr($module);
 }

 function shn_admin_acl_role()
 {
 _shn_admin_acl_role();
 }

 function shn_admin_acl_role_cr()
 {
 _shn_admin_acl_role_cr();
 }
 */

/***
 * Localization interface for language translation
 */
function shn_admin_lc_trns()
{
	print ("<h1><center>"._t("Language Translation")."</center></h1>");
	require_once('lc_translate.inc');
}

function shn_admin_lc_set()
{
	print ("<h1><center>"._t("Set Locale")."</center></h1>");
	require_once('lc_setlocale.inc');
}

function shn_admin_lc_db()
{
	print ("<h1><center>"._t("Database Translation")."</center></h1>");
	require_once('lc_db.inc');
}

//User interface language translation

function shn_admin_lc_ui_trns()
{
	global $global;
	require_once $global['approot']."/inc/lib_locale/lib_locale.inc";
	require_once('lc_ui_translate.inc');

	print ("<h1><center>"._t("User Interface Language Translation")."</center></h1>");
	if($_POST['locale']==null){
		_shn_admin_set_locale();
	}else {
		_shn_admin_lc_set_ui_translate();
		$locale = $_POST['locale'];
		_shn_lc_setcookielc($locale);
		_shn_lc_setsessionlc($locale);
	}

}

function shn_admin_lc_ui_trns_enable()
{
	require_once('lc_ui_translate.inc');
	if(isset($_POST['lc'])) {
		if (!is_writable('../res')){
			add_error(_('sahana/res folder is not writable!'));
			_shn_admin_lc_set_ui_translate();
		}
		else
		_shn_admin_lc_ui_trns_enable();
	}
	if(isset($_POST['lc_dis'])) {
		_shn_admin_lc_ui_trns_disable();
	}
	if(isset($_POST['lc_update'])) {
		_shn_admin_lc_ui_trns_update();
	}

}

function shn_admin_lc_ui_trns_update()
{
	require_once('lc_ui_translate_update.inc');
	print ("<h1><center>"._t("Update Translation")."</center></h1>");

	if($_GET['update']=="Update") {
		_shn_admin_lc_translate_compile();

	}else {
		_shn_admin_lc_translate_update();
	}

}

function shn_admin_lc_add_new_lang()
{
	require_once('lc_add_new_language.inc');
	print ("<h1><center>"._t("Add/Remove language")."</center></h1>");
	_shn_admin_lc_add_new_language_form();
}

function shn_admin_lc_add_new_language_post()
{
	require_once('lc_add_new_language.inc');
	if(isset($_POST['add'])) {
		if($_POST['lang_name']!=null && $_POST['lang_folder_name']!=null)
		_shn_admin_lc_add_new_language();
		else {
			add_error(_t('Language Name and Folder Name cannot be blank'));
			print ("<h1><center>"._t("Add/Remove language")."</center></h1>");
			_shn_admin_lc_add_new_language_form();
		}
	}
	else if(isset($_POST['remove'])) {
		_shn_admin_lc_remove_language();
	}
}

function shn_admin_lc_add_new_module()
{
	require_once('lc_add_new_module.inc');
	print ("<h1><center>"._t("Add New Module")."</center></h1>");
	_shn_admin_lc_add_new_module();
}

function shn_admin_lc_add_new_module_post()
{
	require_once('lc_add_new_module.inc');

	if(isset($_POST['merge']))
	_shn_admin_lc_add_new_module_update();
}


function shn_admin_lc_file_browser()
{
	global $global;
	$locale = $_POST['locale'];
	//$file_type=$_POST['file_type'];
	$uploaddir = "../res/locale/$locale/LC_MESSAGES/";
	//"../res/locale/$locale/LC_MESSAGES/";
	//echo $uploaddir;
	$uploadfile = $uploaddir . basename($_FILES['userfile']['name']);

	if(move_uploaded_file($_FILES['userfile']['tmp_name'], $uploadfile)) {
		add_confirmation('File uploaded sucessfully');
	}else {
		add_error('File uploaded failed');
	}

}

function shn_admin_lc_javascript()
{
	global $global;
	global $conf;
	$approot = $global['approot'];
	$request  = $_REQUEST['request'];
	if($request=='first') {
		require_once $approot."/mod/admin/lc_first_process_request.inc";
		_find_translated_str();
	}
	else if($request=='second') {
		require_once $approot."/mod/admin/lc_second_process_request.inc";
		_find_str();
	}
	else if($request=='third') {
		require_once $approot."/mod/admin/lc_third_process_request.inc";
		_find_str();
	}
	else if($request=='select') {
		require_once $approot."/mod/admin/lc_select_process_request.inc";
		shn_admin_lc_select_tag();
	}shn_sub_mod_menuopen(_t("Location Hierarchy"));

}

/**
 * Module manager funciton
 */
function shn_admin_module_mgr(){
	global $global,$conf;
	$db = $global['db'];
	echo "<h2>"._t("Module Manager")."</h2>";
	echo "<table><tr>";
	echo "<th>"._('Module')."</th>";
	echo "<th>"._('Status')."</th>";
	echo "<th>"._('Actions')."</th>";
	echo "</tr>";
	$mod_dir = $global['approot']."mod";
	$mod_query = "SELECT module,status FROM modules";
	$res = $db->Execute($mod_query);
	$result_array = $res->GetAssoc();
	
	include_once $global['approot'].'inst/setup_utils.inc';
	$essencial_modules = _shn_setup_get_essencial_modules();
	
	if($dh = opendir($mod_dir)) {

		while (($file = readdir($dh)) !== false) {
			echo "<tr>";
			if(is_dir($mod_dir.'/'.$file)){
				//echo "<td>$file</td>";
				if($file!='..' && $file!='.' && $file!='CVS' && preg_match('/^\.w+$/i',$file)==false){
					echo "<td>".$conf['mod_'.$file.'_name']."</td>";
					echo "<td>".((trim($result_array[$file])=='installed')?_t('Installed'):_t('Not Installed'))."</td>";
					echo "<td>".((trim($result_array[$file])=='installed')?((array_search($file,$essencial_modules)==false)?_t('Uninstall Now'):''):_t('Install Now'))."</td>";
				}
			}
				
			//echo "filename: $file : filetype: " . filetype($dir . $file) . "\n";
			echo "</tr>";
		}
		closedir($dh);

	}
	echo "</table>";
}

/**
 * Inclusion of GIS admin menu functionality/actions
 */
include_once $global['approot'].'/inc/lib_gis/admin_acts.inc';

/**
 * Inclusion of Messaging admin menu
 * @edit: Mifan Careem <mifan@respere.com>
 * @todo check availability of messaing module
 */
include_once $global['approot']."/mod/msg/adm_menu_actions.inc";
?>
