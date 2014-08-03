<?php  
/**
* Displays the login box 
* Sahana - http://sahana.sourceforge.net
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    framework
* @subpackage handler 
* @author     http://www.linux.lk/~chamindra
* @author     ravindra@opensource.lk
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $conf;

if ($_SESSION['logged_in'] != true ) {
?>
    <div id="loginform">
	<form method="post" action="index.php?act=login">
        <!-- <fieldset> <legend><?=_t('Login')?></legend> -->
        <label><?=_t('User Name')?></label><input type="text" name="user_name" id="userName" />
        <label><?=_t('Password')?></label><input type="password" name="password" id="pswd" />
		<input type="submit" value="Sign In" />

        <!-- <a href="#">Forgot your password?</a> -->
        
        <?php
         	$acl=shn_acl_is_signup_enabled();
 			if(true){
 				?>

      
        <?php echo _t("  "); ?> <a href="index.php?act=signup"><?php echo _t("Request Account");?></a>

        <?php }?>
<!-- </fieldset> -->
</form>   
 
   </div><!-- /loginform -->
    
    <div id="openid_loginform">
    	<form action="" method="get">
    		<fieldset><legend><?=_t('OpenId Login')?></legend>
    			<label><?=_t('OpenID')?></label><input type="text" name="identity_url" id="openid_login" />
				<input type="submit" value="Sign In" />
				<br />
				<i><?php echo _t("For example: "); ?> <tt>you.someblog.com</tt></i>
			</fieldset>
		</form>
	<center><a href="#" onclick="switchLogin('openid_loginform','loginform');"><?php echo _t("go back to the Normal Login"); ?></a></center>
    </div>
    <script type="text/javascript">
    	switchLogin('openid_loginform','loginform');
    </script>
<?php
} else {
?>
    <div id="loginform">
        <fieldset><?=_t('Logged In')?>
        <?=_t('User: ')?><?php echo $_SESSION['user'];?>
      
<a href="index.php?act=logout"><?=_t('Logout')?></a>
    </div>

<?php
}

?>
