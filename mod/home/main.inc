<?PHP
include_once($global['approot']."inc/user_feedback.inc");
include_once ($global['approot']."/inc/lib_menu.inc");

function shn_home_default()
{

    global $conf;
    
    ?>

<div id="home">
<img width="100%" src="res/img/cap-banner.png" style="padding-bottom:5px; margin-top:-10px">
<h2>Welcome to Common Alerting Protocol-enabled International Telecommunication Union Software (CAPITUS)</h2>
<table border="0">
  <tr>
    <td valign="top" width="350"><p>
	<strong>What is CAP?</strong></p>      
	<iframe width="300" height="180" src="//www.youtube.com/embed/n0iKp60jjtY?list=PL23CB283949653EDC" frameborder="0" allowfullscreen></iframe></p>
	<strong>CAPITUS?</strong>
        <p>The <a href="http://docs.oasis-open.org/emergency/cap/v1.2/CAP-v1.2-os.html">Common Alerting Protocol</a>, CAP-enabled, ITU Software (CAPITUS) is part of a multi phase project. The self-training aids and demo tools for advocating the uptake of CAP to foster an interoperable platform for exchanging national and cross-boarder alerts and warnings for Multi-agency Situational-awareness. This project is sponsored by the ITU Development Sector Emergency Communication program.

The CAPITUS Project has three primary intentions: 
        <ul>
          <li>Offer a training module for member states to learn and experminet with CAP-enabled early warning software and procedures</li><br>
          <li>Assist member states with developing and implementing their Country CAP Profiles</li><br>
          <li>Suport the initiative for worldwide CAP Adaptation and proliferation</li>
        </ul>
</p>
<p><strong>Other CAP Videos to come</strong></p>
<ul>
  <li>How to register a user</li>
  <li>How to manage subscribets</li>
  <li>How to create templates</li>
  <li>How to issue an alert</li>
</ul>
</td>
    <td valign="top" width="400">
      <p><strong>How to use this CAP-enabled Module</strong></p>
       <ol>
          <li>Learn <strong>about the CAP standard</strong> and the software through a <a href="http://www.youtube.com/watch?v=G7WOq5giddI">case study</a> with the use of <I>CAP messages in Public Health Alerting</I>.</li><br>
          <li>Ask for an account from the CAPITUS administrators: <strong>Request Account</strong></li><br>
	  <li>Experiment with <strong>issuing CAP messages</strong> over technologies like SMS, Email, RSS/Atom, Twitter using CAPITUS. [<a href="#">Video</a> | <a href="#">PDF</a>]</li><br>
	  <li>Formulate your <strong>Country CAP Profile</strong> for all-hazards all-media warnings through a stakeholder participatory approach.</li><br>
	  <li>Request for your <strong>own localized instance of CAPITUS</strong></a>. Then use it with stakeholders to experiment and demonstrate the pros and cons of adopting CAP standard and CAP-enabled software for a National Eaerly waring and Situational-Awareness.</li><br>
	  <li>Software developers can <a href="https://github.com/waidyanatha/sambro-agasti">download</a> the <strong>H-FOSS code</strong>. Under the GNU License, it is free to use, change, and redistribute</li><br>
	  <li>Advance users would <strong>foster a Multi-Agency Situational-Awareness</strong> platform in their jurisdictions. [<a href="#">Video</a> | <a href="#">PDF</a>]</li>
       </ol>
    </td>

    <td valign="top" width="400">
      <p><strong>Resources</strong></p>
       <ul>
          <li><a href="https://github.com/waidyanatha/sambro-agasti/wiki">WIKI</a> with all that is documented about the software:</li>
          <ul>
            <li>How to <a href="https://github.com/waidyanatha/sambro-agasti/wiki/Installation">install</a> the software</li>
            <li>how to administer <a href"https://github.com/waidyanatha/sambro-agasti/wiki/User-Access-Control">users</a></li>
            <li>how to configure and operationalize your own<a href"#"> country instance</a></li>
          </ul>
          <li><a href="https://www.incident.com/CAP/">CAP Cookbook</a> - all you need to know about CAP. This site will have links to all the CAP relevant resources:</li><br>
          <li><a href="http://www.wmo.int/pages/prog/amp/pwsp/CAPWorkshopDocs2014.html">2014 CAP Implementation Workshop</a> - was held in Negombo, Sri Lanka (17-8th June 2014). The resourece provides access to all CAP presentations and CAP related literature archived since 2006.</li><br>
	    <li><a href="#">OASIS</a> - the Organization for the Advancement of Structured Information Standards. especially the OASIS Emergency Management Technical Committee (OASIS EM-TC) - is the organization that systematically manages the Emergency Data Exchange Language (EDXL) approved CAP technical standard is currently at <a href="http://docs.oasis-open.org/emergency/cap/v1.2/CAP-v1.2-os.html">version 1.2.</a>.</li><br>
	    <li><a href="#">Sahana Alerting and Messaging Broker</a> (SAMBRO) - is a Free and Open Source Software designed for CAP-enabled messaging and implementing a multi-agency sitiational-awareness platform</li><br>
	    <li><a href="">MASAS - Canadian Multi Agency Situational Awareness System</a> - is developed using ESRI products such as ArcGIS as a platform to add layers.</li><br>
	    <li><a href="https://alert-hub.appspot.com/">Google Alerthub</a> - offers a tool to <a href="https://cap-validator.appspot.com/">validate CAP messages</a>, with the option of validating against an available CAP Profile. Valid messages, can be easily integrated with Google's Alerthub for disseminating public alerts.</li><br>
	    <li><a href="http://www.internetalerts.org">Federation for Internet Alerts</a> - is a consortium that is developing guidelines for, specifically, on-line advertising systems to publish CAP messages.</li>
       </ul>
    </td>
  </tr>
</table>

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
function _shn_home_module_info($module, $description) 
{
    global $conf;

    if ($conf['mod_'.$module.'_enabled']) {
        echo "<li><a href=\"index.php?mod=$module\" ><strong>".$conf['mod_'.$module.'_name'].'</strong></a> - ';
        echo _t($description)."</li>\n";
    }

}

/**
 * Show a welcome page for first time users.
 *
 */
function shn_home_welcome(){
	global $global;
	echo _t("<h2>Welcome to the RTBP</h2>")
	?>
<h4><?php echo _t("Congratulations !. You have successfully installed Sahana.")?></h4>
<p><?php echo _t("You may need to customize sahana according to your requirements.") ?></p>
	<?php
	if(shn_acl_is_enabled()){
		
		if($_SESSION['logged_in']===true && $_SESSION['user']=="admin" && $_SESSION['user_id']=="1"){
			shn_admin_default();
			// unset it the first time flag so that this never appears again
			$_SESSION['first_time_run']=false;
		}else{
		
			$_SESSION['last_module']="admin";
			$_SESSION['last_action']="default";
		?>
<div class="message information"><strong> <?php
echo _t("Please login by entering the administrator username and password in the respective text boxes on the left side
		panel to proceed customizing sahana.")
?> </strong></div>
<?php
		}
	}else{
		shn_admin_default();
		// unset it the first time flag so that this never appears again
		$_SESSION['first_time_run']=false;
	}
}

function shn_home_bug_report(){
	echo "<h2>"._t("Sahana bug reporting")."</h2>";
	
	shn_form_fopen("bug_report_cr");
	shn_form_fsopen(_t("Report a bug"));	
	shn_form_text(_t("Your name"),"reporter_name",null,array("req"=>true));
	shn_form_text(_t("Contact email"),"reporter_email");
	shn_form_text(_t("Bug Title"),"title",null,array("req"=>true));
	shn_form_text(_t("Module(s)"),"target_module");
	shn_form_textarea("What you did before you caught the bug","steps",null,array("req"=>true));
	shn_form_textarea(_t("Bug Description / Additional Notes"),"notes");
	shn_form_fsclose();
	shn_form_submit(_t("Cancel"),"name='cancel'");
	shn_form_submit(_t("Create Bug Report"),"name='download_rep'");
	shn_form_fclose();
}

function shn_home_bug_report_cr(){
	global $global,$conf;
	if(isset($_POST['cancel'])){
		shn_home_default();
	}else if(isset($_POST['download_rep'])){
		$reporter_name = $_POST['reporter_name'];
		$error = false;
		if(isset($reporter_name)==false || strlen($reporter_name)==0){
			add_error(_t("Please enter your name"));
			$error = true;
		}
		$reporter_email = $_POST['reporter_email'];
		$bug_title = $_POST['title'];
		if(isset($bug_title)==false || strlen($bug_title)==0){
			add_error(_t("Please enter a title for the bug"));
			$error = true;
		}
		$bug_module = $_POST['target_module'];
		$steps = $_POST['steps'];
		if(isset($steps)==false || strlen($steps)==0){
			add_error(_t("Please enter what you did before this bug appeared."));
			$error = true;
		}
		$notes = $_POST['notes'];
		
		if($error==false){
		$comment = "<!--Please email this file to bugs@sahana.lk-->";
		$timestamp = date("Ymdhis");
		$tname = "shn-bug-report".$timestamp;//tempnam("/tmp","shn-bug-report");
		if(is_writable($global['approot']."www/tmp/")){
			$fp = fopen($global['approot']."www/tmp/".$tname,"w+");		
		
			fwrite($fp,"<?xml version=\"1.0\"?>");
			fwrite($fp,$comment);
			fwrite($fp,"<bug-report id=\"$timestamp\">");
			fwrite($fp,"<reporter-name>$reporter_name</reporter-name>");
			fwrite($fp,"<reporter-email>$reporter_email</reporter-email>");
			fwrite($fp,"<title>$bug_title</title>");
			fwrite($fp,"<module>$bug_module</module>");
			fwrite($fp,"<steps>$steps</steps>");
			fwrite($fp,"<notes>$notes</notes>");
			fwrite($fp,"<environment>".$_SERVER['HTTP_USER_AGENT']."</environment>");
			fwrite($fp,"</bug-report>");
			fclose($fp);
		
			echo "<h2>"._t("Thank you for your effort towards making sahana better.")."</h2>";
			echo "<div class='message information'>";
			echo "<p>"._t("Please download the bug report from the link below and email it to ")."<a href=\"mailto:bugs@sahana.lk\">bugs@sahana.lk</a></p>";
			echo "<br/>";
			echo "<a href=\"?mod=home&act=download_bug_report&stream=text&brpt_id=$tname\">"._t("Download the bug report here")."</a>";
			echo "</div>";
		}else{
			add_error(sprintf(_t("The path \"%s\" is not writable"),$global['approot']."www/tmp/"));
			add_error(_t("Failed to create bug report due to the lack of file write permissions to the above folder."));							
		}
		}else{
			shn_home_bug_report();
		}
	}
	
	
}

function shn_home_faq(){
	_shn_home_faq();
}

/*
 * Enable disable user feedback user interface.
 */
function shn_home_userfb(){

if($_SESSION['user'] != "Anonymous")
	{


    echo "<h2>"._t("Help / User feedback preferences")."</h2>";
	shn_form_fopen("userfb_cr","home",array("req"=>false));
	shn_form_fsopen(_t("Enable or disable help and user feeback"));
	$value = shn_get_user_pref_value("home","shn_user_pref_feedback_enabled");
	$valstr = ($value==true?'enabled':'disabled');
	shn_form_radio(array("enabled"=>_t("Enabled"),"disabled"=>_t("Disabled")),_t("Help / User feedback"),"userfb_status","",array('value'=>$valstr));
	shn_form_fsclose();
	shn_form_submit(_t("Cancel"),"name='cancel'");
	shn_form_submit(_t("Save"));
	shn_form_fclose();

}
	else
	{
		add_error(_('Sorry you do not have permission to access this'));
	}

}
	
function shn_home_userfb_cr(){
	if(!$_POST['cancel']){
		$valstr = $_POST['userfb_status'];
		if($valstr=='enabled'){
			$ret = shn_user_pref_update('home','shn_user_pref_feedback_enabled',true);
			if($ret == true){
				add_confirmation(_t("Your preference was successfully saved."));
			}else{
				add_error(_t("An error occured while saving your preference."));
			}
		}else{
			$ret = shn_user_pref_update('home','shn_user_pref_feedback_enabled',false);
			if($ret == false){
				add_confirmation(_t("Your preference was successfully saved."));
			}else{
				add_error(_t("An error occured while saving your preference."));
			}
		}
		shn_home_userfb();
	}else{
		shn_home_default();
	}
}

function shn_text_home_download_bug_report(){
	global $global;
	$bug_report_id = $_REQUEST['brpt_id'];
	header("Content-type: text/xml");
	header("Content-Disposition: attachment; filename=\"$bug_report_id\"");
	$content = file_get_contents($global['approot']."www/tmp/"."/".$bug_report_id);
	print $content;	
	//unlink($global['approot']."www/tmp/"."/".$bug_report_id);
}

// Default stream welcome function 
function shn_XST_home_default() {

    // Currently the stream only redirect to home if there is an error
    echo _t('Welcome to Sahana on the '.$_REQUEST['stream'].' stream.');
    

}
function shn_home_contact(){
	echo _t('<br><br><h2>Contact us</h2>');
	echo _t("<br><br>");
	echo _t("<b>For more details contact,</b><br><br> ");
	echo _t("ITU/BDT Office<br>");
	echo _t("Bangkok, Thailand<br>");
	echo _t("Email : admin@capitus.th<br>");
	echo _t("<br><br> <br>");
    
		 }
		 
		 
function shn_home_manual(){
	echo _t('<br><br><h2>User Manual</h2>');
	echo _t("<br><br>");
	echo _t("<a href='#'>Click here to download user manual </a><br><br> ");
	echo _t("<br><br> <br>");
    
		 }
function shn_home_about(){
	echo _t('<br><br><h2>About the CAP ITU Sofotware</h2>');

echo _t("<p>The software is intended for member states intending to trial the Common Alerting Protocol warning standard. ITU will also use this package in their Emergency Comm training.<br>");
}

function shn_home_mainmenu(){
	global $global,$conf;

/*** DEPRECATED BY waidyanatha [at] gmail [dot] com 2014-06-02
** Move these details to the Messaging Module Menu

	shn_mod_menuopen(_t($conf['mod_home_name']));
	shn_mod_menuitem('about',_t('About us'),'home');
	shn_mod_menuitem('contact',_t('Contact us'),'home');
	shn_mod_menuitem('manual',_t('User Manual'),'home');

	shn_mod_menuclose();
*/
	include $global['approot']."/inc/handler_mainmenu.inc";

}

?>
