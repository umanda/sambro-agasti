<?php
/**
 *
 * This is the library will manage media files used in the system
 *
 *
 * PHP version  5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @author     H J P Fonseka <jo@respere.com>
 * @copyright  Respere http://respere.com
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function shn_files_store($name , $dir= 'common'){
    global $global;
    global $conf;
    
    if($_FILES[$name]['name']=='')
        return false;

    include_once ($global['approot']."/inc/lib_uuid.inc");
    $file_id = shn_create_uuid('file');
    $file_name = basename($_FILES[$name]['name']);	
    $file_size = $_FILES[$name]['size'];
    $file_type = $_FILES[$name]['type'];
    $dir = $dir;
    $uploaddir = $conf['media_dir'];
    
    _shn_files_create_dir($uploaddir . $dir , $conf['media_mode']);

    $file_path = $uploaddir .$dir.'/'. $file_id."_". $file_name;
    
    if (move_uploaded_file($_FILES[$name]['tmp_name'], $file_path)) {
        $sql = "INSERT INTO files(file_id , file_name , file_type , file_path , file_size , dir) VALUES ( '$file_id' , '$file_name' , '$file_type' , '$file_path' , '$file_size' , '$dir')";
        $global['db']->Execute($sql);
        return $file_id;
    } else {
        add_error("Possible file upload attack! Files were not saved.");
        // implement the error checking
        return false;
    }
}


function shn_files_return_link($alert_uuid){
    global $global;
    if(!isset($alert_uuid))return "";
    $sql = "SELECT name  FROM msg_alert_files WHERE alert_uuid = '$alert_uuid'";
    //print $sql;
    $file_name = $global['db']->GetOne($sql);
	$file_name = $alert_uuid. '_'.$file_name;
	
    return "<a href='index.php?stream=text&amp;mod=msg&amp;act=file&amp;file=$alert_uuid'>".$file_name."</a>";
}

function shn_files_link($file_id,$return=false){
    global $global;
    $sql = "SELECT name  FROM msg_alert_files WHERE alert_uuid = '$file_id'";
    //print $sql;
    $file_name = $global['db']->GetAll($sql);
    //var_dump($file_name);
    echo "<label>Uploaded files</label>";
    for($i=0; $i<count($file_name); $i++)
    {
		//$filename = $file_id. '_'.$file_name;
		$filename = /*$file_id. '_'.*/$file_name[$i]['name'];
    
	
	shn_files_return_link($file_id);
	$upload_file = '/media/'.$file_id.'/'.$file_name[$i]['name'];

	?>
	
    <!-- <a href='index.php?mod=msg&act=download_file&alert_uuid=<?php echo $file_id?> &file_name=<?php echo $file_name?>'> <?php print $filename. ' /'?> </a>-->
      <!-- <a href="index.php?mod=xst&act=download_file&stream=text&alert_uuid=<?php echo $file_id;?>&file_name=<?php echo $filename;?> " target="_blank"><?php print $filename.' / ';?></a>-->
	<a href="<?php echo $upload_file?>" ><?php print $filename.' / ';?></a>
	<?php 
    }
	echo "<br/>";	
}

function _shn_msg_download_file()
{
	global $global;
	$alert_uuid = $_REQUEST['alert_uuid'];
	$file_name = $_REQUEST['file_name'];
	$upload_file = $global['approot'].'media/'.$alert_uuid.'/'.$file_name;
	//return "index.php?mod=msg&act=download_file&stream=text&alert_=".$report_id;
	$db = $global['db'];
	
	$sql = "SELECT * FROM msg_alert_files WHERE alert_uuid = '$alert_uuid' AND name = '$file_name'";
	//print $sql;
	$records = $db->Execute($sql);
	$type = $records->fileds['type'];
	$size = $records->fields['size'];
	//$content = $records->fields['content'];
	ob_end_flush();
	header("Content-Type: $type");
	header("Content-Length: $size");
	header("Content-Disposition: attachment; filename=$file_name");
	header("Content-Description: PHP Generated Data");
	
	$fh = fopen($upload_file, "rb");
	fpassthru($fh);
	//fseek($fh, 0);
	//print fread($fh, filesize($upload_file));
	//while (!feof($fh)) {
      //print (fread($fh, 500));
      //ob_flush();
//}
fclose($fh);
exit(0);

	
//echo 'media/'.$alert_uuid.'/'.$file_name;
}

function shn_files_img_src($file_id){
    global $global;
    $sql = "SELECT file_name  FROM files WHERE file_id = '$file_id'";
    $file_name = $global['db']->GetOne($sql);
	$filename = $file_id. '_'.$file_name;
    echo "media/pop/$filename";
}


function _shn_files_create_dir($pathname,$mode){
    is_dir(dirname($pathname)) || mkdir_recursive(dirname($pathname), $mode);
    return is_dir($pathname) || @mkdir($pathname, $mode);
}

 /*function shn_files_link2($file_id){
    global $global;
    $sql = "SELECT name   FROM msg_alert_files WHERE alert_uuid = '$file_id'";
    $file_name = $global['db']->GetOne($sql);
    echo "<a href='index.php?mod=xst&amp;act=download&amp;stream=text&amp;id=$file_id'>".$file_name."</a>";
}*/
?>
