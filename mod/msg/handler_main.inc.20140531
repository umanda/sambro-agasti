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
* @author	Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package	sahana
* @subpackage	rms
* @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

global $global;
print $global['msg_jabber']->$connected;
?>

<h1 align="center"><?= _t("Messaging Home")?> </h1>
<div id="home">
    <div>
    <p><?= (_t("Messaging module is the main communicative root of the Sahana system. It is used to send SMS, e-mail alerts and/or messages to various groups and individuals before, after and during a disaster. It also provides a convenient way of grouping mobile phone numbers and e-mail addresses.")) ?></p></div>
    <br></br>
    <div><h3><b><em><?= (_t("Features Include:")) ?></em></b></h3></div>
      
    <ul>
        <li><a href="index.php?mod=msg&act=send_console"><b><?= (_t("Messages:"))?></b></a><br><?= (_t("SMS and e-mail alerts/messages could be sent to any groups or individuals. This feature currently works only on Linux platform."))?></li>
        <li><a href="index.php?mod=msg&act=add_contact_group"><b><?= (_t("Manage Groups:"))?></b></a><br><?= (_t("Each end user is provided the facility to create, customize and maintain various groups of SMS and e-mail contacts"))?></li>
        <li><a href="index.php?mod=msg&act=new_alert"><b><?= (_t("CAP:"))?></b></a>
<br><a href="index.php?mod=msg&act=new_alert"><?= (_t("New Alert"))?></a><?= (_t(" option enables end-user to create a new CAP alert. This will create an XML file containing the CAP message and store it in database."))?>
<br><a href="index.php?mod=msg&act=voice_alert"><?= (_t("Voice Alert"))?></a><?= (_t(" option enables end-user to view voice a new CAP alert.And also user can hear the audio file."))?>
<br><a href="index.php?mod=msg&act=view_alert"><?=(_t("View Alert"))?></a><?= (_t(" option enables end-user to view stored CAP messages. Using the send option on the view page you can transmit the alert via SMS."))?></li>
    </ul>

<?php 
/** added by Nuwan Waidyanatha, 2010-05-02 to enable downloading of manuals and guidelines */
?>
    <br></br>
    <div><h3><b><em><?= (_t("Read Me:")) ?></em></b></h3></div>
    <a href="res/docs/Exercise_1_Sahana_CAP_Broker.pdf"> <img title="CAP Broker Guide" src="res/img/CAPGuide.jpg" alt="res/img/CAPGuide.jpg" width="180" height="60" border="0" /> </a>    

<?php




?>
</div>


<!--<div id="home">
<h2><?//php print _t("Messaging")?></h2>

<br/>
<h3>Use the New Message Option to create a New CAP message</h3>
<p>This will create an xml file containing the CAP message and store it in a 
temporary directory. You can view this file using 'View Messages' option</p>

<br />
<h3>Use the View Messages Option to view stored CAP messages</h3>
<p>Two sample messages are already added to the list. You can view them by selecting
one of them and pressing the 'view' button </p>

<br />
<h3>XMPP Messaging</h3>
<p>Comming soon to a Sahana near you ;-)</p>
</div>-->
