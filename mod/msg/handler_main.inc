<?php
/**
* The SAMBRO Messaging Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author	Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package	SAMBRO
* @subpackage	rms
* @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

    global $conf;
    
    ?>

<div id="home">
<img width="100%" src="res/img/cap-banner.png" style="padding-bottom:5px; margin-top:-10px">
<h2>Welcome to Common Alerting Protocol-enabled International Telecommunication Union Software (CAPITUS)</h2>

<div style="box-shadow: 0 0.5px 0 0 #ffffff inset, 0 1px 2px 0 #B3B3B3;">
<table border="0">
  <tr>
    <td valign="top" width="350">
      <p><strong>Video on Issuing Alerts with the Software</strong></p>
	<iframe src="//player.vimeo.com/video/47523528" width="300" height="220" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe> <p><a href="http://vimeo.com/47523528">CAP Broker on a Tablet PC</a>.</p>
    </td>
    <td valign="top" width="400">
      <p><strong>What can the software do</strong></p>
      <ul>
        <li>Manage subscriber and subsriber groups</li><br>
        <li>Store CAP message templates as a "draft"</li><br>
        <li>Issue CAP messages over:
          <ul> 
            <li>Email</li>
            <li>SMS</li>
            <li>RSS/Atom</li>
            <li>Twitter</li>
            <li>HTTP</li>
          </ul></li>
       </ul>
    </td>
    <td valign="top" width="400"><p>
	<strong>Resources</strong></p>
        <ul> 
          <li><a href="https://www.incident.com/CAP/">CAP Cookbook</a> - all you need to know about CAP. This site will have links to all the CAP relevant resources:</li><br>
          <li><strong>Videos:</strong>
          <ul> 
            <li>Managing subscribers</li>
            <li>Creating CAP message templates</li>
            <li>Issuing CAP messages</li>
          </ul></li><br>
          <li><strong>Quick reference guides:</strong>
          <ul> 
            <li>Managing subscribers</li>
            <li>Creating CAP message templates</li>
            <li>Issuing CAP messages</li>
          </ul></li>
        </ul>
    </td>
  </tr>
</table>
</div>

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
