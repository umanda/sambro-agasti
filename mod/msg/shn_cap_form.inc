<?php
	global $global;
	require_once $global['approot']."/inc/lib_locale/lib_locale.inc";
	require_once('class_cap_alert.inc');
	require_once('class_cap_info.inc');
	require_once('class_cap_resource.inc');
	require_once('class_cap_area.inc');
	require_once('lib_cap_form_js.inc');

	
	function shn_msg_cap_alert()
	{
		$alert  = new Msg_CapAlert();
    
	    $alert->setIdentifier($_POST['identifier']);
	    $alert->setSender($_POST['sender']);
	    $alert->setSent($_POST['sent']);
	    $alert->setStatus($_POST['status']);
	    $alert->setMsgType($_POST['msgType']);
	    $alert->setSource($_POST['source']);
	    $alert->setScope($_POST['scope']);
	    /*print $_POST['restriction1'];
	    print '<br>';
	    print $_POST['restriction'];
	    print '<br>';
	    print $_POST['addresses'];
	    print '<br>';
	    print $_POST['addresses2'];
	    print 'test';*/
		
	    if($_POST['restriction'] != '' && $_POST['restriction1'] != '')
	    {
	    	$_POST['restriction1'] = '';
	    	$alert->setRestriction($_POST['restriction']);
	    }
	    else if($_POST['restriction1'] != '' && $_POST['restriction'] == '')
	    {
	    	$alert->setRestriction($_POST['restriction1']);
	    }
	    else if($_POST['restriction'] != '' && $_POST['restriction1'] == '')
	    {
	    	$alert->setRestriction($_POST['restriction']);
	    }
	    
	    else
	    {
	    	$alert->setRestriction($_POST['restriction']);
	    }
	    //$alert->setRestriction($_POST['restriction']);
		if($_POST['addresses'] != '' && $_POST['addresses2'] != '')
	    {
	    	$_POST['addresses2'] = '';
	    	$alert->setAddress($_POST['addresses']);
	    }
	    else if($_POST['addresses2'] != '' && $_POST['addresses'] == '')
	    {
	    	$alert->setAddress($_POST['addresses2']);
	    }
	    else  if($_POST['addresses'] != '' && $_POST['addresses2'] == '')
	    {
	    	$alert->setAddress($_POST['addresses']);
	    }
		
	    else
	    {
	    	$alert->setAddress($_POST['addresses']);
	    }
	    //$alert->setCode($_POST['code']);
	    
	    $codes = split(' ', $_POST['code']);
	    
	    $alert->setCode($codes);
	    //var_dump($codes);
	    
	    /*foreach($codes as $code)
	    {
	        if(trim($code) != ''){	        	
	            $alert->addCode($code);
	        }
	        print $code;
	        print '<br>';
	    }*/
	    
	    $alert->setNote($_POST['note']);
	    $alert->setReferences($_POST['references']);
	    $alert->setIncidents($_POST['incidents']);
	    //var_dump($alert);
	    return $alert;
	}
	
	function shn_msg_cap_info($alert)
	{
	    
	    $info   = new Msg_CapInfo();
	    
	    $info->setLanguage($_POST['info_language']);
	    //print($_POST['info_category']);
	    $category = split(',', $_POST['info_category']);
	    //var_dump($category);
	    /*foreach($category as $cat)
	    {
	        if(trim($cat) != '')
	            $info->addCategory($cat);
	    }*/
	    $info->setCategory($category);
	    //var_dump($info);
	    
	    $info->setEvent($_POST['info_event']);
	    
	    $responseType = split(' ', $_POST['info_responseType']);
	    foreach($responseType as $res)
	    {
	        if(trim($res) != '')
	            $info->addResponseType($res);
	    }
	    $info->setPriority($_POST['opt_msg_priority']);
	    if($_POST['opt_msg_priority']=='unknown')
	    {
	    	$info->setUrgency($_POST['opt_msg_urgency']);
	    	$info->setSeverity($_POST['opt_msg_severity']);
	    	$info->setCertainty($_POST['opt_msg_certainty']);
	    }
	    if($_POST['opt_msg_priority']=='high')
	    {
	    	$info->setUrgency($_POST['info_urgency_high']);
	    	$info->setSeverity($_POST['info_severity_high']);
	    	$info->setCertainty($_POST['info_certainty_high']);
	    }
		if($_POST['opt_msg_priority']=='low')
	    {
	    	$info->setUrgency($_POST['info_urgency_low']);
	    	$info->setSeverity($_POST['info_severity_low']);
	    	$info->setCertainty($_POST['info_certainty_low']);
	    }
		if($_POST['opt_msg_priority']=='urgent')
	    {
	    	$info->setUrgency($_POST['info_urgency']);
	    	$info->setSeverity($_POST['info_severity']);
	    	$info->setCertainty($_POST['info_certainty']);
	    }
	    $info->setAudience($_POST['info_audience']);
	    
	    $eventCodes = split(' ', $_POST['info_eventCode']);
	    foreach($eventCodes as $eventCode)
	    {
	        $eventCode = split(':', $eventCode);
	        if(trim($eventCode[0]) != '' && trim($eventCode[1]) != '' )
	            $info->addEventCode($eventCode[0],$eventCode[1]);
	    }
	    
	    $info->setEffective($_POST['info_effective']);
	    $info->setOnset($_POST['info_onset']);
	    $info->setExpires($_POST['info_expires']);
	    $info->setSendername($_POST['info_senderName']);
	    $info->setHeadline($_POST['info_headline']);
	    $info->setDescription($_POST['info_description']);
	    $info->setInstruction($_POST['info_instruction']);
	    $info->setWeb($_POST['info_web']);
	    $info->setContact($_POST['info_contact']);
	    
	    $parameters = split(' ', $_POST['info_parameter']);
	    foreach($parameters as $parameter)
	    {
	        $parameter = split(':', $parameter);
	        if(trim($parameter[0]) != '' && trim($parameter[1]) != '' )
	            $info->addParameter($parameter[0],$parameter[1]);
	    }
	    
	    $alert->addInfo($info);	 
//var_dump($alert);
	    return $alert;
	}
	
	function shn_msg_cap_res($alert)
	{	    
		//
	    $info   = $alert->getInfo();
	    //var_dump($_FILES);
	    $template_id = $_POST['template_id'];
	    //print($_POST['info_derefUri']);
	    $res = new Msg_CapResource();
	    global $global;
	    //$media_dir = $global['approot'].'media';
	   // print $media_dir;
	    //var_dump(mkdir($media_dir, 0777));
	    if($template_id != NULL)
	    {
	    	$f_id = $template_id;
	    }
	    else
	    {
	    	$f_id = $_POST['identifier'];
	    }
	    $upload_dir = $global['approot'].'media/'.$f_id;
	    //print $upload_dir;
	    mkdir($upload_dir, 0777, true);
	    //print $upload_dir;
	    //if(mkdir($upload_dir, 0777) == true)
	    //{
	    	
	    $fileName = $_FILES['info_derefUri']['name'];
	   // $fileName = "asd";
	    //var_dump($file_name);
		$tmpName  = $_FILES['info_derefUri']['tmp_name'];
		//var_dump($tmpName);
		$fileSize = $_FILES['info_derefUri']['size'];
		$fileType = $_FILES['info_derefUri']['type'];
		//echo $tmpName;
		move_uploaded_file($tmpName, $upload_dir.'/'.$fileName);

		$fp      = fopen($tmpName, 'r');
		$content = fread($fp, filesize($tmpName));
		$content = addslashes($content);
		//var_dump($content);
		fclose($fp);
		$insert_file_array = array();
		//$insert_file_array['file_id'] = shn_create_uuid('file');
		$insert_file_array['alert_uuid'] = $f_id;//trim($_POST['identifier']);
		$insert_file_array['name'] = $fileName;
		$insert_file_array['type'] = $fileType;
		$insert_file_array['size'] = $fileSize;
		$insert_file_array['content'] = "";
		//echo $fileName;
		global $global;
		$rset = $global['db']->AutoExecute('msg_alert_files', $insert_file_array, 'INSERT');
	    //}
	    //else
	    //{
	    	//add_error(_t('Directory Creation failed due to some permission issues. Please set write permission to media direct$tmpNameory and upload the file again'));
	    //}
		//var_dump($insert_file_array);
	    /*$input_name = $_POST['userfile'];
	    print $input_name;
	    $fileName = $_FILES['userfile']['name'];
	    var_dump($file_name);
	    global $HTTP_POST_FILES;

         if(isset($HTTP_POST_FILES) && is_uploaded_file($HTTP_POST_FILES[$input_name]["tmp_name"]))
           {
           $file_handle = fopen($HTTP_POST_FILES[$input_name]["tmp_name"], "rb");
           $file_name = $HTTP_POST_FILES[$input_name]["name"];
           print $file_name;
           $file_bytes = addslashes(fread($file_handle, filesize($HTTP_POST_FILES[$input_name]["tmp_name"])));
           unlink($HTTP_POST_FILES[$input_name]["tmp_name"]);
           }*/
	    $res->setResourceDesc($_POST['info_resDesc']);
	    $res->setMimeType($_POST['info_mimeType']);
	    $res->setSize($_POST['info_size']);
	    $res->setUri($_POST['info_uri']);
	    $res->setDerefUri($_POST['info_derefUri']);
	    $res->setDigest($_POST['info_digest']);
	    
	    $info->addResource($res);
	    $alert->setInfo($info,0);    
	    
	    return $alert;
		
	}
	
	function shn_msg_cap_area($alert)
	{
	 
	    $info   = $alert->getInfo();
	    
	    $ar = new Msg_CapArea();
	        
	    $ar->setAreaDesc($_POST['area_areaDesc']);
	    $ar->setLocationCategory($_POST['loc_cate_area']);
	    $ar->setLocationType($_POST['loc_type_area']);
	    //var_dump($ar);
	    $polys = split('-', $_POST['area_poly_list']);
	    foreach($polys as $poly){
	    	$poly = split(',' , $poly);
	    	$ar->addPolygon($poly);
	    }	

	    if(trim($_POST['area_crl_list']!='')){
	    $circles = split('-', $_POST['area_crl_list']);
	    foreach ($circles as $circle)
	    {
	        $circle = split(',', $circle);
	        $ar->addCircle($circle[0],$circle[1],$circle[2]);
	    }
	    }
	    
	    if(trim($_POST['gc_list']!='')){
	    $geoCodes = split('-', $_POST['gc_list']);
	    foreach ($geoCodes as $geoCode)
	    {
	        $geoCode = split(',', $geoCode);
	        $ar->addGeocode($geoCode[0],$geoCode[1]);
	    }
	    }
	    
	    $ar->setAltitude($_POST['area_altitude']);
	    $ar->setCeiling($_POST['area_ceiling']);
	    
	    $info->addArea($ar);
	    
	    $alert->setInfo($info,0);
	    
	    return $alert;
	}
	
	function shn_msg_cap_getxml(){
		$alert = shn_msg_cap_alert();
		$alert = shn_msg_cap_info($alert);
		//var_dump($alert);
		$alert = shn_msg_cap_res($alert);
		$alert = shn_msg_cap_area($alert);
		return $alert;
	}
	
	function _shn_msg_cap_form($file = null,$id=null)
	{
		global $global;	
		//var_dump($_SESSION);	
		//var_dump($_SESSION["user_agent"]);	
		
		if($_SESSION['is_template']){
			$is_template = $_SESSION['is_template'];
		}
		
		$error_flag = false;
		if ($_FILES["info_derefUri"]["error"] == UPLOAD_ERR_INI_SIZE // exceeds upload_max_filesize
 || $_FILES["info_derefUri"]["error"] == UPLOAD_ERR_FORM_SIZE ) { // exceeds MAX_FILE_SIZE
    // file was too large - not uploaded 
		add_error(_t('File could not upload because file size exceeds the Maximum upload limit'));
		//exit(0);
		$error_flag = true;
		
 }
		if($id != null){
			$_SESSION['update']['alert_uuid']=$id;
		}
		

		$insert_array = array();
		
		if(isset($_POST['save'])){
			

			$alert = shn_msg_cap_getxml();
			//var_dump($alert);
			
			if($_SESSION['update']['alert_uuid'] != null){
				$insert_array['alert_uuid'] = $_SESSION['update']['alert_uuid'];
				unset($_SESSION['update']['alert_uuid']);
			}
			else
			{
				$insert_array['alert_uuid'] = $_SESSION['tmp_alert_id'];
			}			
					
			if(is_array($_SESSION['msg']['new']['alert']) && count($_SESSION['msg']['new']['alert']) != 0){
				$insert_array = $_SESSION['msg']['new']['alert'];
				unset($_SESSION['msg']['new']['alert']);

			}
			$insert_array['file'] = $alert->getCapXML();
			$file =	$insert_array['file'];	


			
			$db = $global['db'];


			if(!is_errors()){
				//var_dump($insert_array);
				//print '<br>';
				//print $_POST['identifier'];
				//$insert_array['alert_uuid'] = trim($_POST['identifier']);
				$insert_array['file'] = $alert->getCapXML();

	    		$res = $db->AutoExecute('msg_alerts', $insert_array, 'UPDATE',"alert_uuid='{$insert_array['alert_uuid']}'");	
				if($res){
					if($_SESSION['is_template'])
					{
						$confirmation_string = "Alert was updated!";
					}
					else
					{
						$destination = "index.php?mod=msg&act=send_alert&seq=select_contact&xml_id=".$_POST['identifier'];
						$confirmation_string = "Alert was updated!".'<br>'.'<a href="'.$destination.'" >'."Click Here".'</a>'." to send the updated alert";
					}
						add_confirmation($confirmation_string);
						//$_SESSION["user_agent"];
						//["user_name"]=>  string(11) "Admin User " ["msg"]=>  array(2) { ["alert"]=>  array(1) { ["name"]=>  string(4) "ghgh" } ["new"]=>  array(0) { } } ["cap_msg"]=>  NULL ["tmp_alert_id"]=>  string(17) "Actual-1268037706" ["update"]=>  array(1) { ["alert_uuid"]=>  string(17) "Actual-1268037575" } } string(32) "6b8b53bd46578b87b656dfdc2d64b337" 
						unset($_SESSION["user_name"]);
						unset($_SESSION["msg"]);
						unset($_SESSION["alert"]);
						unset($_SESSION["name"]);
						unset($_SESSION["new"]);
						unset($_SESSION["cap_msg"]);
						unset($_SESSION["tmp_alert_id"]);
						unset($_SESSION["update"]);
						unset($_SESSION["alert_uuid"]);
						//session_unset();
						//unset($_SESSION[]);
				} else {
					add_error("Alert can not be updated!");
				}				
			}
			else{

				add_error("Alert can not be updated!");
			}
		}
		else if(isset($_POST['save_location'])){
			unset($_POST['loc_cate_area']);
			unset($_POST['loc_type_area']);
			unset($_POST['textarea_areaDesc']);
			
			if(shn_bsm_add_validate()){
							    		    
			    $insert_array['loc_uuid'] = shn_create_uuid('loc');
	        	$insert_array['loc_prnt_uuid'] = $_POST['parent_id'];
	        	$insert_array['loc_name'] = $_POST['name'];
	    		$insert_array['loc_type'] = $_POST['loc_type'];    
	        	$insert_array['loc_prnt_id'] = $_POST['parent_uuid'];    
	        	$insert_array['loc_desc'] = $_POST['description'];
	    		$insert_array['loc_shape'] = $_POST['shape'];    
	        	$insert_array['loc_x_vect'] = $_POST['x_vector'];    
	        	$insert_array['loc_y_vect'] = $_POST['y_vector'];    
	        	$insert_array['loc_z_vect'] = $_POST['add']['z_vector'];    
	        	$insert_array['loc_iso_code'] = $_POST['iso_code'];	
	        	global $global;
	    		$db = $global['db'];	
				$res = $db->AutoExecute('msg_location', $insert_array, 'INSERT');
				unset($insert_array);
				add_confirmation(_t('Location successfully saved'));
			}
			else{
				add_error(_t('Error in saving location'));
			}
			    
    		
        				
		}
		
		$alert = new Msg_CapAlert($file);
		//var_dump($alert);
		
		if($alert != null){
			//var_dump('alert',$alert);
			$id = $alert->getIdentifier();
		    $date = $alert->getSent();
		    $sender = $alert->getSender();
		    $status_sel= $alert->getStatus();
		    $messageType_sel = $alert->getMsgType();
		    $note= $alert->getNote();
		    $source = $alert->getSource();
		    $scope_pre = $alert->getScope();
		    $restriction = $alert->getRestriction();
		    $address = $alert->getAddress();
		    $code = $alert->getCode();
		    $references = $alert->getReferences();
		    $incidents = $alert->getIncidents();
		}
		else if($_SESSION['msg']['new']['alert']['alert_uuid'] != null) {
			$id = $_SESSION['msg']['new']['alert']['alert_uuid'];			
			$sender = $_SESSION['msg']['new']['alert']['author'];			
		}
		//var_dump($alert);
		//print $alert->getSender();
		//print $sender;
		require_once('lib_cap_help.inc');
    
	    //$id = time();
	    $today = date("Y-m-d h:m:s");
	    
	    $status = array('Actual'=>'Actual', 'Exercise'=>'Exercise', 
	                     'System'=>'System', 'Test'=>'Test', 'Draft'=>'Draft');
	    $msgType = array('Alert'=>'Alert', 'Update'=>'Update', 
	                      'Cancel'=>'Cancel', 'Ack'=>'Ack', 'Error'=>'Error');
	    $scope = array('Public'=>'Public', 'Restricted'=>'Restricted', 
	                   'Private'=>'Private');
	    $status_sel = ($status_sel)?$status_sel:'Draft';
	    
	    print "<h2>" . _t("Creating CAP") . "</h2>";
	    
	    shn_form_fopen("cap_form",null,array('req_message'=>false,'tab'=>'float','name'=>'cap_form', 'enctype'=>"enctype='multipart/form-data'"));	    
	    //print $_SESSION['update']['alert_uuid'];
	    //print 'test';
	    //$alert_id=$_GET['for'];
	    //print $alert_id;
	    if($_SESSION['update']['alert_uuid']!= null && $_SESSION['update']['alert_uuid'] == $_GET['for'])
	    {
	    	$id = $_SESSION['update']['alert_uuid'];
	    }
		$sender1 = $_GET['sender'];
		if($sender1 != '' && $sender == '')
		{
			$sender = $sender1;
		}
		if($sender != '' && $sender1 == '')
		{
			$sender = $sender;
		}
		
	    shn_form_fsopen(_t("Alert"));	    	    
		    //shn_form_hidden(array('time'=>$id,'stat'=>$status[_t("Actual")]));
		    if(!$_SESSION['is_template']){
		    	shn_form_text(_t("Message Identifier"),'identifier',null,array('value'=>$id,'help'=>$help_identifire, 'req'=>true));
		    	shn_form_text(_t("Sender"),'sender','class=""',array('value'=>$sender, 'help'=>$help_sender, 'req'=>true));
		    	shn_form_select($msgType, _t("Message Type"), 'msgType', 'onChange="showHideNote(this);"',array('value'=>$messageType_sel,'help'=>$help_msgType, 'req'=>true));
		    }
		    //shn_form_text(_t("Date"),'sent',null,array('value'=>$today));	
		    shn_form_hidden(array('sent'=>$today));	
		    if($status_sel == '' || $status_sel == NULL)
		    {
		    	$status_sel = $status['Draft'];
		    }	
		    //var_dump($status_sel);    
		    shn_form_select($status, _t("Status"), 'status', 'onChange="changeId(this);"', array('value'=>$status_sel,'help'=>$help_status, 'req'=>true));		    
		    print '<div id="cap_note">';
		    shn_form_textarea(_t("Note"),'note');
		    print '</div>';
		    shn_form_text(_t("Source"),'source',null, array('value'=>$source, 'help'=>$help_source, 'req'=>true));
		    
		    shn_form_select($scope, _t("Scope"), 'scope','onChange="changeScope(this);"',array('help'=>$help_scope, 'value'=>$scope_pre, 'req'=>true));
		    switch($scope_pre){
		    	case 'Restricted':
		    		//shn_form_label('Current Restriction Value', _t($restriction), array('br'=>true));
		    		print '<div id="scope_rest1">';
		    		shn_form_text(_t("Restriction [Restricted]"),'restriction1','size="25"',array('value'=>$restriction, 'req'=>true));
		    		print '</div>';
		    		print '<div class="hide" id="scope_addr1">';
		    		shn_form_textarea(_t("Addresses [private]"),'addresses1',null,array('value'=>$address, 'req'=>true));
		    		print '</div>';
		    		//changeScope("Restricted");
		    		break;
		    	case 'Private':
		    		//changeScope("Private");
		    		//shn_form_label('Current Address Value', _t($address), array('br'=>true));
		    		print '<div id="scope_addr1">';
		    		shn_form_textarea(_t("Addresses [private]"),'addresses2',null,array('value'=>$address, 'req'=>true));
		    		print '</div>';
		    		print '<div class="hide" id="scope_rest1">';
		    		shn_form_text(_t("Restriction [Restricted]"),'restriction2','size="25"',array('value'=>$restriction, 'req'=>true));
		    		print '</div>';
		    		break;
		    	
		    }
		    
		    //if($scope_pre == '')
		    //{
		    print '<div id="scope_rest">';
		    shn_form_text(_t("Restriction [Restricted]"),'restriction','size="25"',array(/*'value'=>$restriction,*/ 'req'=>true));
		    print '</div><div id="scope_addr">';
		    shn_form_textarea(_t("Addresses [private]"),'addresses',null,array(/*'value'=>$address,*/ 'req'=>true));
		    print '</div>';
		    print '<div class="hide" id="scope_rest1">';
		    shn_form_text(_t("Restriction [Restricted]"),'restriction_dummy','size="25"',array('value'=>$restriction, 'req'=>true));
		    print '</div>';
		    print '<div class="hide" id="scope_addr1">';
		    shn_form_textarea(_t("Addresses [private]"),'addresses_dummy',null,array('value'=>$address, 'req'=>true));
		    print '</div>';
		    //}
		
		    shn_form_fsopen(_t("Optional"));
		    for($i=0; $i<count($code); $i++)
		    {
		    	$code_display = trim($code_display.' '.$code[$i]);
		    }
		    	    
		    shn_form_text(_t("Code"),'code',null, array('value'=>$code_display,'br'=>false));
		    print "<strong>Enter space separated set of codes</strong> <br />";	    
		    shn_form_text(_t("References"),'references','',array('value'=>$references));
		    shn_form_text(_t("incidents"),'incidents','',array('value'=>$incidents));
		    shn_form_fsclose(); 	    
	    shn_form_fsclose();
	    
	    if($alert != null){
			$info = $alert->getInfo();
	    }
	    
		if($info!=null){
		    $info_language = $info->getLanguage();
		    $category = $info->getCategory();
		    //var_dump($category);
		    $event = $info->getEvent();
		    $responseType = $info->getResponseType();
		    $response = $responseType[0];
		    //var_dump($responseType);
		    $priority = $info->getPriority();
		    //print $priority;
		    $urgency = $info->getUrgency();
		    $severity = $info->getSeverity();
		    $certainty = $info->getCertainty();
		    $audience = $info->getAudience();
		    $eventCode = $info->getEventCode();
		    $effective = $info->getEffective();
		    $onset = $info->getOnset();
		    $expires = $info->getExpires();
		    $sendername = $info->getSendername();
		    $headline = $info->getHeadline();
		    $description = $info->getDescription();
		    $instruction = $info->getInstruction();
		    $web = $info->getWeb();
		    $contact = $info->getContact();
		    $parameter = $info->getParameter();
		    
		    for($i=0; $i<count($parameter); $i++)
		    {
		    	$parameter_display = trim($parameter_display.' '.$parameter[$i]['valueName'].':'.$parameter[$i]['value']);		    
		    }
		    
		    for($i=0; $i<count($eventCode); $i++)
		    {
		    	$eventcode_display = trim($eventcode_display.' '.$eventCode[$i]['valueName'].':'.$eventCode[$i]['value']);
		    }
		    
	    }
	    for($i=0; $i<count($category); $i++)
		    {
		    	if($i==0)
		    	{
		    		$category_display = $category[$i];
		    	}
		    	else
		    	{
		    		$category_display = $category_display.','.$category[$i];
		    	}
		    }
		    
		   // print $category_display;
	    //var_dump($info);
	    //print()
	   	shn_form_fsopen(_t("Information"));
	    	$category = array('Geo'=>'Geo', 'Met'=>'Met', 'Safety'=>'Safety', 
                      'Security'=>'Security', 'Rescue'=>'Rescue', 
                      'Fire'=>'Fire', 'Health'=>'Health', 'Env'=>'Env', 
                      'Transport'=>'Transport', 'Infra'=>'Infra', 
                      'CBRNE'=>'CBRNE', 'Other'=>'Other');
    
		    $session_lang = $_SESSION["locale"];
		    switch ($session_lang)
		    {
		        case 'de_DE':
		                $c_land = 'si_LK';
		                break;
		        default:
		                $c_land = $session_lang;
		    }
		    
		    
		    $language = array('si_LK'=>_t("Sinhala"),'tm_LK'=>_t("Tamil"),'en_US'=>_t("English")); 
		    //$language = array('sinhala'=>_t("Sinhala"),'tamil'=>_t("Tamil"),'english'=>_t("English")); 
		    
		    shn_form_select($language, _t("Language"), 'info_language', null, array('value'=>$info_language,'help'=>$help_language));		    

		    /******************************************************************
		     * This Line comments available caegory drop down and adds a different
		     * Category Drop Down *********************************************
		     */ 
		    shn_form_select($category, _t("Category"),'info_category_list',null,array('br'=>false,'value'=>$category));		    
		    shn_form_button("Add", 'onClick="addCategory(info_category_list.value);"',array('br'=>false));
		    shn_form_text('','info_category','size="25"',array('no_label'=>true,'br'=>false, 'value'=>$category_display));
		    shn_form_button("Clear", 'onClick="clearValue(info_category)"');
		    echo "<br />";		     
			
		   // var_dump($category);
		   //print $category_display;
		   // shn_form_checkbox_multiple($category, _t("Category"), 'info_category', null, array('br'=>true, 'value'=>$category_display));
		    //********************** Event data populate *************
		    
		    shn_form_text(_t("Event"),'info_event',null,array('help'=>$help_event,'value'=>$event,"req"=>true));
		    //$extra_opts['br'] = false;
		    //$extra_opts['value'] = $_POST['destination'];
    		//$destination_array=array('yes'=>'Priority is not known','no'=>'Priority is Known');
    		//shn_form_radio($destination_array,_t(''),'destination','onClick="change_action_des(this.value)"',$extra_opts);
		    if(!$_SESSION['is_template']){
	  			shn_form_opt_select('opt_msg_priority', _t('Priority'), 'onChange="change_action_priority(this.value)"', array('value'=>$priority));
	    		//print $priority;
	  			/*if($priority != '==' && $priority != '')
	    		{
	  				shn_form_label('Current Priority ' . ucfirst($priority),_t('Urgency : '.$urgency), array('br'=>true));
	  				shn_form_label('', _t('Severity : '.$severity), array('br'=>true));
	    			shn_form_label('', _t('Certainty : '.$certainty), array('br'=>true));    			
	    		}*/
		    }
  			$opt = _shn_admin_set_option_javascript();
  			//var_dump($opt);
    		
    		echo "<br />";
    		echo "<br />";
    		if($priority == 'unknown')
    		{
		    	echo "<div id='des_yes'>";
		    	//shn_form_opt_select('opt_msg_priority', _t('Priority'), 'onChange="change_action_priority(this.value)"', null);
				shn_form_opt_select('opt_msg_urgency', _t('Urgency'), null, array('help'=>$help_event, 'value'=>$urgency, 'req'=>true));
				shn_form_opt_select('opt_msg_severity', _t('Severity'), null, array('value'=>$severity, 'req'=>true));
				shn_form_opt_select('opt_msg_certainty', _t('Certainty'), null, array('value'=>$certainty, 'req'=>true));
				//print($_POST['opt_msg_urgency']);
				$urgency = '';
		    	$severity = '';
		    	$certainty = '';
				echo "</div>";
    		}
    		else
    		{
    			echo "<div class='hide' id='des_yes'>";
		    	//shn_form_opt_select('opt_msg_priority', _t('Priority'), 'onChange="change_action_priority(this.value)"', null);
				shn_form_opt_select('opt_msg_urgency', _t('Urgency'), null, array('help'=>$help_event, 'value'=>$urgency, 'req'=>true));
				shn_form_opt_select('opt_msg_severity', _t('Severity'), null, array('value'=>$severity, 'req'=>true));
				shn_form_opt_select('opt_msg_certainty', _t('Certainty'), null, array('value'=>$certainty, 'req'=>true));
				//print($_POST['opt_msg_urgency']);
				$urgency = '';
		    	$severity = '';
		    	$certainty = '';
				echo "</div>";
    		}
    		if($priority == 'urgent')
    		{
    			echo "<div id='des_no_urgent'>";   
				//shn_form_text(_t("Event"),'info_event',null,array('help'=>$help_event,'value'=>$event,"req"=>true));
		    	//shn_form_opt_select('opt_msg_priority', _t('Priority'), null, null);
		    	if($urgency==null || $urgency=='')
		    	{
		    		$urgency = _t('Immediate');
		    	}
		    	if($severity==null || $severity=='')
		    	{
		    		$severity = _t('Extreme');
		    	}
		    	if($certainty == null || $certainty == '')
		    	{
		    		$certainty = _t('Observed');
		    	}
		    	shn_form_text(_t("Urgency"),'info_urgency','readOnly=true',array('help'=>$help_urgency,'value'=>$urgency,"req"=>true));
		    	shn_form_text(_t("Severity"),'info_severity','readOnly=true',array('value'=>$severity,"req"=>true));
		    	shn_form_text(_t("Certainty"),'info_certainty','readOnly=true',array('value'=>$certainty,"req"=>true));
		    	//print($_POST['info_urgency']);
		    	$urgency = '';
		    	$severity = '';
		    	$certainty = '';
		    	echo "</div>";
    		}
    		else
    		{
		    	echo "<div class='hide' id='des_no_urgent'>";   
				//shn_form_text(_t("Event"),'info_event',null,array('help'=>$help_event,'value'=>$event,"req"=>true));
		    	//shn_form_opt_select('opt_msg_priority', _t('Priority'), null, null);
		    	if($urgency==null || $urgency=='')
		    	{
		    		$urgency = _t('Immediate');
		    	}
		    	if($severity==null || $severity=='')
		    	{
		    		$severity = _t('Extreme');
		    	}
		    	if($certainty == null || $certainty == '')
		    	{
		    		$certainty = _t('Observed');
		    	}
		    	shn_form_text(_t("Urgency"),'info_urgency','readOnly=true',array('help'=>$help_urgency,'value'=>$urgency,"req"=>true));
		    	shn_form_text(_t("Severity"),'info_severity','readOnly=true',array('value'=>$severity,"req"=>true));
		    	shn_form_text(_t("Certainty"),'info_certainty','readOnly=true',array('value'=>$certainty,"req"=>true));
		    	//print($_POST['info_urgency']);
		    	$urgency = '';
		    	$severity = '';
		    	$certainty = '';
		    	echo "</div>";
    		}
		    if($priority == 'high')
		    {
		    	echo "<div id='des_no_high'>";  
				if($urgency==null || $urgency=='')
		    	{
		    		$urgency = _t('Expected');
		    	}
		    	if($severity==null || $severity=='')
		    	{
		    		$severity = _t('Severe');
		    	}
		    	if($certainty == null || $certainty == '')
		    	{
		    		$certainty = _t('Observed');
		    	} 
				//shn_form_text(_t("Event"),'info_event',null,array('help'=>$help_event,'value'=>$event,"req"=>true));
		    	//shn_form_opt_select('opt_msg_priority', _t('Priority'), null, null);
		    	shn_form_text(_t("Urgency"),'info_urgency_high','readOnly=true',array('help'=>$help_urgency,'value'=>$urgency,"req"=>true));
		    	shn_form_text(_t("Severity"),'info_severity_high','readOnly=true',array('value'=>$severity,"req"=>true));
		    	shn_form_text(_t("Certainty"),'info_certainty_high','readOnly=true',array('value'=>$certainty,"req"=>true));
		    	//print($_POST['info_urgency']);
		    	$urgency = '';
		    	$severity = '';
		    		$certainty = '';
		    	echo "</div>";
		    }
		    else
		    {
		    	echo "<div class='hide' id='des_no_high'>";  
				if($urgency==null || $urgency=='')
		    	{
		    		$urgency = _t('Expected');
		    	}
		    	if($severity==null || $severity=='')
		    	{
		    		$severity = _t('Severe');
		    	}
		    	if($certainty == null || $certainty == '')
		    	{
		    		$certainty = _t('Observed');
		    	} 
				//shn_form_text(_t("Event"),'info_event',null,array('help'=>$help_event,'value'=>$event,"req"=>true));
		    	//shn_form_opt_select('opt_msg_priority', _t('Priority'), null, null);
		    	shn_form_text(_t("Urgency"),'info_urgency_high','readOnly=true',array('help'=>$help_urgency,'value'=>$urgency,"req"=>true));
		    	shn_form_text(_t("Severity"),'info_severity_high','readOnly=true',array('value'=>$severity,"req"=>true));
		    	shn_form_text(_t("Certainty"),'info_certainty_high','readOnly=true',array('value'=>$certainty,"req"=>true));
		    	//print($_POST['info_urgency']);
		    	$urgency = '';
		    	$severity = '';
		    		$certainty = '';
		    	echo "</div>";
		    }
		    if($priority == 'low')
		    {
		    	echo "<div id='des_no_low'>";
		    	if($urgency==null || $urgency=='')
		    	{
		    		$urgency = _t('Expected');
		    	}
		    	if($severity==null || $severity=='')
		    	{
		    		$severity = _t('Moderate');
		    	}
		    	if($certainty == null || $certainty == '')
		    	{
		    		$certainty = _t('Observed');
		    	}    
				//shn_form_text(_t("Event"),'info_event',null,array('help'=>$help_event,'value'=>$event,"req"=>true));
		    	//shn_form_opt_select('opt_msg_priority', _t('Priority'), null, null);
		    	shn_form_text(_t("Urgency"),'info_urgency_low','readOnly=true',array('help'=>$help_urgency,'value'=>$urgency,"req"=>true));
		    	shn_form_text(_t("Severity"),'info_severity_low','readOnly=true',array('value'=>$severity,"req"=>true));
		    	shn_form_text(_t("Certainty"),'info_certainty_low','readOnly=true',array('value'=>$certainty,"req"=>true));
		    	//print($_POST['info_urgency']);
		    	$urgency = '';
		    	$severity = '';
		    	$certainty = '';
		    	echo "</div>";
		    }
		    else
		    {
		    	echo "<div class='hide' id='des_no_low'>";
		    	if($urgency==null || $urgency=='')
		    	{
		    		$urgency = _t('Expected');
		    	}
		    	if($severity==null || $severity=='')
		    	{
		    		$severity = _t('Moderate');
		    	}
		    	if($certainty == null || $certainty == '')
		    	{
		    		$certainty = _t('Observed');
		    	}    
				//shn_form_text(_t("Event"),'info_event',null,array('help'=>$help_event,'value'=>$event,"req"=>true));
		    	//shn_form_opt_select('opt_msg_priority', _t('Priority'), null, null);
		    	shn_form_text(_t("Urgency"),'info_urgency_low','readOnly=true',array('help'=>$help_urgency,'value'=>$urgency,"req"=>true));
		    	shn_form_text(_t("Severity"),'info_severity_low','readOnly=true',array('value'=>$severity,"req"=>true));
		    	shn_form_text(_t("Certainty"),'info_certainty_low','readOnly=true',array('value'=>$certainty,"req"=>true));
		    	//print($_POST['info_urgency']);
		    	$urgency = '';
		    	$severity = '';
		    	$certainty = '';
		    	echo "</div>";
		    }
		    
		    
		    //*********************** Event data populate end ********
		    		    
		    
		    shn_form_fsopen(_t("Optional"));
		    if(!$_SESSION['is_template']){
		    	shn_form_text(_t("Sender Name"),'info_senderName',null,array('value'=>$sendername));
		    }
		    
		    shn_form_text(_t("Headline"),'info_headline',null,array('value'=>$headline));
		    //shn_form_text(_t("Description"),'info_description',null,array('value'=>$description));		    
		    shn_form_textarea(_t("Description"), 'info_description', null, array('value'=>$description));
		    shn_form_text(_t("Audience"),'info_audience',null,array('value'=>$audience));
			shn_form_fsclose(); 
			if(!$_SESSION['is_template']){
				$responseType = array(''=>'', 'Shelter'=>'Shelter', 'Evacuate'=>'Evacuate', 
			                          'Prepare'=>'Prepare', 'Execute'=>'Execute', 
			                          'Monitor'=>'Monitor', 'Assess'=>'Assess', 
			                          'None'=>'None');
			    /**
			     * This is to comment available response type text field but can be used in feauture 
			     * development
			     * 
		    	shn_form_select($responseType, _t("Response Type"),'info_responseType_list',null,array('br'=>false,'value'=>$responseType));
			
		    	shn_form_button("Add", 'onClick="addResponseType(info_responseType_list.value);"',array('br'=>false));
		    	shn_form_text('','info_responseType',null,array('no_label'=>true, 'br'=>false, 'value'=>$response));
		    	shn_form_button("Clear", 'onClick="clearValue(info_responseType)"');
			
		    	print '<br />';  
		    	*/  
				shn_form_select($responseType, _t("Response Type"),'info_responseType',null,array('br'=>true,'value'=>$response));
				
				/*if($id != NULL || $id != '')
		    	{
		    		//echo '<strong>';
		    		//print $id;
		    		shn_form_label(_t("Current Values"), null, null);
		    		shn_form_label(_t("Effective"), $effective, array('br'=>true));
		    		shn_form_label(_t("Onset"), $onset, array('br'=>true));
		    		shn_form_label(_t("Expires"), $expires, array('br'=>true));
		    		//echo '</strong>';
		    	}
		    	print '<br />';  */  
		    //print $effective;
		    	
		    	shn_form_datetime(_t("Effective"),'info_effective',array('value'=>$effective));
//		    	print "<small color=''>(e. g., 2002-05-24T16:49:00-07:00 for 24 May 2002 at 16: 49 PDT)</small><br />";
		    	shn_form_datetime(_t("Onset"),'info_onset',array('value'=>$onset));
//		    	print "<small>(e. g., 2002-05-24T16:49:00-07:00 for 24 May 2002 at 16: 49 PDT)</small><br />";
		    	shn_form_datetime(_t("Expires"),'info_expires',array('value'=>$expires));
//		    	print "<small>(e. g., 2002-05-24T16:49:00-07:00 for 24 May 2002 at 16: 49 PDT)</small><br />";		    
		    }
		    
		    shn_form_textarea(_t("Instruction"),'info_instruction',null,array('value'=>$instruction));
		    shn_form_text(_t("Web"),'info_web',null,array('value'=>$web));
		    shn_form_text(_t("Contact"),'info_contact',null,array('value'=>$contact));
		    
		    shn_form_fsopen(_t("Cap Message Info - Event Code"));
		    shn_form_text(_t("ValueName"),'valueName');
		    shn_form_text(_t("Value"),'value_val',null, array('br'=>false));
		    shn_form_button("Add", 'onClick="addEventCode(valueName.value,value_val.value);"');
		    shn_form_text('','info_eventCode',null,array('br'=>false, 'value'=>$eventcode_display));
		    shn_form_button("Clear", 'onClick="clearValue(info_eventCode)"');
		    shn_form_fsclose();
		    
		    shn_form_fsopen(_t("Cap Message Info - Parameter"));
		    shn_form_text(_t("ValueName"),'param_valueName');
		    shn_form_text(_t("Value"),'param_value',null, array('br'=>false));
		    shn_form_button("Add", 'onClick="addParameter(param_valueName.value,param_value.value);"');
		    shn_form_text('','info_parameter',null,array('br'=>false, 'value'=>$parameter_display));
		    shn_form_button("Clear", 'onClick="clearValue(info_parameter)"');
		    shn_form_fsclose();
		    
	    shn_form_fsclose();
	    
	    if($info!=null){		    
		    foreach($info->getResource() as $resource){		    
				$resourceDesc = $resource->getResourceDesc();
		    	$mimeType = $resource->getMimeType();
		    	$size = $resource->getSize();
			   	$uri = $resource->getUri();
		    	$derefUri = $resource->getDerefUri();
		    	$digest = $resource->getDigest();
			$id = $alert->getIdentifier();		
          	}
	
	    }
	    
	    shn_form_fsopen(_t("Resouce"));
	    	//shn_form_text(_t("Resource Description"),'info_resDesc',null,array('value'=>$resourceDesc,"req"=>true));
		    shn_form_textarea(_t("Resource Description"), 'info_resDesc', null, array('value'=>$resourceDesc));
	    	shn_form_text(_t("mime Type"),'info_mimeType',null,array('value'=>$mimeType));
		    shn_form_text(_t("Size"),'info_size',null,array('value'=>$size));
		    shn_form_text(_t("URI"),'info_uri','class=""',array('value'=>$uri));
		    //print 'mahesh';
		   // print $template_id;	    
		    shn_form_upload(_t('Attachment'),'info_derefUri');
		   //print $_REQUEST['id']."ll";
		    // print $derefUri.$size;
			//print $id."id";
		 /*   if($_REQUEST['id'] != NULL)
		    {
		    	$file_id = trim($_REQUEST['id']);
		    	//print $file_id;
		    	shn_files_link($file_id,$return=false);	
		    	//shn_files_return_link($file_id);
		    	echo '<br>';
		    	 //shn_files_link2($file_id);
		    }*/
		    if($id != NULL)
                    {
                        $file_id = trim($id);
                        //print $file_id;
                        shn_files_link($file_id,$return=false);
                        //shn_files_return_link($file_id);
                        echo '<br>';
                         //shn_files_link2($file_id);
                    }
		  
		   // shn_files_link2($file_id);
		    //shn_form_text(_t("Uploaded Files"),'info_derefUri', array('value'=>$derefUri));
		    shn_form_text(_t("Digest"),'info_digest',null,array('value'=>$digest));
		    //shn_form_submit(_t("Add Resource"));
    	shn_form_fsclose();
    	
    	if($info!=null){	    	
	    	foreach($info->getArea() as $area){	    	
		    	$areaDesc = $area->getAreaDesc();
		    	$locationCategory = $area->getLocationCategory();
		    	$locationType = $area->getLocationType();
		 		$polygon = $area->getPolygon();
		 		$poly_list = null;		 		
	    		for($i=0; $i<count($polygon); $i++)
		 		{
		 			if($i==0){
		 				$poly_list = $polygon[$i];
		 			}
		 			else{
		 				$poly_list = $poly_list.'-'.$polygon[$i];
		 			}
		 		}
		 		
		 		$circle = $area->getCircle();
		 		for($i=0; $i<count($circle); $i++)
		 		{
		 			if($i==0)
		 			{
		 				$circle_list = $circle[$i];
		 			}
		 			else
		 			{
		 				$circle_list = $circle_list.'-'.$circle[$i];
		 			}
		 		}
		 		
		 		
		 		$geocode = $area->getGeocode();
		 		//var_dump($geocode);
				for($i=0; $i<count($geocode); $i++)
				{
					if($i==0)
					{
						$geocode_list = $geocode[$i]['valueName'].','.$geocode[$i]['value'];
					}
					else
					{
						$geocode_list = $geocode_list.'-'.$geocode[$i]['valueName'].','.$geocode[$i]['value'];
					}
				}
		 		
		 		$altitude = $area->getAltitude();
		 		$ceiling = $area->getCeiling();
	    	}
    	}
 				
    	if(!$_SESSION['is_template']){
    		shn_form_fsopen(_t("Area"));   
				
    		$array_values = array();
    		if(isset($_POST['save_location'])){ 
    			$array_values['name'] = $_POST['name'];
    			$array_values['id'] = $insert_array['loc_uuid'];
    		}
    		else if($areaDesc != null)
    		{
    			
    			global $global;
    			$db=$global['db'];
    			//$q = "SELECT loc_uuid, loc_name FROM msg_location WHERE loc_uuid='$areaDesc'";
    			//alert xml should contain human readable location. This query has been modified to view the human readable location in the UI
    			$q = "SELECT loc_uuid, loc_name FROM msg_location WHERE loc_name='$areaDesc'";
    			$res = $db->Execute($q);
    			$location_name[$res->fields['loc_uuid']] = $res->fields['loc_name'];   
    			//array('area_areaDesc') = $res->fields['loc_uuid'];
    			//print $location_name;			
    			//$location_name = $areaDesc;
    			$array_values['name'] = $res->fields['loc_name'];
    			$array_values['id'] = $areaDesc;
    			
    		}
    		
    		include_once 'loc_type.inc';			  		

    		shn_alert_area_location_type($locationCategory, $locationType);	
    		//var_dump('area_areaDesc');
    		shn_ajax_text_look_up(array('Area Description'),array('area_areaDesc'),array('locationHint'),'index.php?mod=msg&act=get_location&stream=text',$array_values,true,array('br'=>false));    		
			?>
			<input type="button" value="Add" onclick="popup_show('popup', 'popup_drag', 'popup_exit', 'screen-center', 0, 0); return false;" />
			<div class="popup_window"     id="popup" style="display: none;">
			<div class="form_header" id="popup_drag">
			<img class="form_exit"   id="popup_exit" src="theme/default/img/cross2.png" alt="" /><center><strong>Add new location</strong></center></div>
			
			<div class="form_body">
			<br/>
			<?php
			 
			shn_form_text(_('Name'),'name','size="30"',array('help' => _('Enter full or part of the location name.'), 'req'=>true));
			 global $global;
    
		    $sql = "SELECT loc_cate FROM msg_loc_type WHERE deactivate_dt IS NULL AND loc_type = '$loc_type' ORDER BY loc_type ASC";
		    $loc_cate = $global['db']->GetOne($sql);
		
		    shn_xajax_registerFunction('bsm_change_loc_types');
		    $sql = "SELECT * FROM msg_loc_cate WHERE deactivate_dt IS NULL ORDER BY loc_cate ASC";
		    $rsql = $global['db']->GetAll($sql);
		    $arropt = array(''=>'');
		    foreach ($rsql AS $r => $rv)
		    {
		        $arropt[$rv['loc_cate']]=$rv['loc_cate'];
		    }
		
		    shn_form_select($arropt,_('Category'), 'loc_cate',' onchange="bsm_change_loc_types(this.value, \'loc_type\')"',array('value'=>$loc_cate, 'help' => _('Select a location category.'), 'req'=>true));
		
		    if($_POST['loc_cate']!='' || $_POST['loc_cate']!=null)
		    {
		    	$loc_cate = $_POST['loc_cate'];
		    }
		    
		    $sql = "SELECT loc_type FROM msg_loc_type WHERE deactivate_dt IS NULL AND loc_cate = '$loc_cate' ORDER BY loc_type ASC";
		
		    $rsql = $global['db']->Execute($sql);
		
		    $arropt = array(''=>'');
		    foreach ($rsql AS $r => $rv)
		    {
		        $arropt[$rv['loc_type']]=$rv['loc_type'];
		    }
		
		    if($_POST['loc_type']!='' || $_POST['loc_type']!=null)
		    {
		    	$loc_type= $_POST['loc_type'];
		    }
		
		    shn_form_select($arropt,_('Type'), 'loc_type',null,array('value'=>$loc_type, 'help' => _('Select a location type.'), 'req'=>true));

			shn_form_text(_('Description'),'description','size="30"',array('help' => _('Type in the location ISO code.'), 'req'=>false));
			shn_form_opt_select('opt_shape', _('Shape'), null, $extra_opts = null);    
		    shn_form_text(_('X Vector'),'x_vector','size="30"',array('help' => _('Type in the vector seperate each element by a comma e.g. 100.6, 101.2, 102.5.'), 'req'=>false));
		    shn_form_text(_('Y Vector'),'y_vector','size="30"',array('help' => _('Type in the vector seperate each element by a comma e.g. 0.6, 1.2, 2.5.'), 'req'=>false));
		    shn_form_text(_('Z Vector'),'z_vector','size="30"',array('help' => _('Type in the vector seperate each element by a comma e.g. 10.6, 11.2, 12.5.'), 'req'=>false));
		    shn_form_text(_('ISO Code'),'iso_code','size="30"',array('help' => _('Type in the location ISO code.'), 'req'=>false));
			echo "<center>";
			shn_form_submit(_t('Save Location'),'name="save_location"');
			echo "</center><br />"; 
			?>
			</div>
			</div>
			<?php    		

    		//shn_form_text(_t("Area Description"),'area_areaDesc',null,array('value'=>$areaDesc,"req"=>true));        
		    shn_form_fsopen(_t("Polygon"));
		    shn_form_text(_t("X "),'area_pX');
		    shn_form_text(_t("Y "),'area_pY',null,array('br'=>false));
		    shn_form_button("Add Point", 'onClick="addCoordinates(area_pX.value, area_pY.value);"',array('br'=>false));
		    shn_form_text('','area_poly_list',null,array('no_label'=>true, 'value'=>$poly_list));
		    shn_form_fsclose();
		  	
		    shn_form_fsopen(_t("Circle"));
		    shn_form_text(_t("X "),'area_cX');
		    shn_form_text(_t("Y "),'area_cY');
		    shn_form_text(_t("Radius "),'area_r',null,array('br'=>false));
		    shn_form_button("Add Circle", 'onClick="addCircle(area_cX.value, area_cY.value, area_r.value);"',array('br'=>false));
		    shn_form_text('','area_crl_list',null,array('no_label'=>true,'value'=>$circle_list));
		    shn_form_fsclose();
		    
		    shn_form_fsopen(_t("Geocode"));
		    shn_form_text(_t("Value Name"),'gc_vn');
		    shn_form_text(_t("Value"),'gc_v',null,array('br'=>false));
		    shn_form_button("Add Geocode", 'onClick="addGeocode(gc_vn.value, gc_v.value);"',array('br'=>false));
		    shn_form_text('','gc_list',null,array('no_label'=>true, 'value'=>$geocode_list));
		    shn_form_fsclose();
		    
		    shn_form_fsopen(_t("Other"));
		    shn_form_text(_t("Altitude"),'area_altitude',null,array('value'=>$altitude));
		    shn_form_text(_t("Ceiling"),'area_ceiling',null,array('value'=>$ceiling));
		    shn_form_fsclose();
		    
		    print "<br />";
		    //shn_form_submit(_t("Add Area"));
    	
    		shn_form_fsclose();
    	}
	    
    	shn_form_drawtab();
    	if($template_id != NULL)
    	{
    		shn_form_hidden(array('template_id' => $template_id));	
    	}
    	shn_form_submit(_t('Update'),'name="save"');
    	shn_form_reset(_t('Clear'));
	    shn_form_fclose();
	    
	    shn_msg_add_cap_form_js();
	}

	function shn_ajax_send_data($loc_type){
		$id=null;
		$name=null;
		$data=_shn_ajax_get_data($loc_type);
		
		//var_dump($data);
		
	    for($j=0;$j<count($data);$j++){
	    	list($id,$name)=split(';',$data[$j]);
	    	$id_array[$j]=$id;
	    	$name_array[$j]=$name;
	    }
	     
	    //var_dump($_GET);
	    $input=$_GET["input"];
	    $print=$_GET["print"];
	    $event=$_GET["eve"];
	    $input_ele=$_GET["input_ele"];
	    
		if (strlen($input) > 0){
			$hint="";
		  	for($i=0; $i<count($data); $i++){
		  		if (strtolower($input)==strtolower(substr($name_array[$i],0,strlen($input)))){
		    		if ($hint==""){
		      			$hint = ':'.$data[$i];
		      		}
		    		else{
		      			$hint = $hint.':'.$data[$i];
		      		}
		    	}
		  	}
		}
				
	   	$hint=$print.':'.$event.':'.$input_ele.':'.substr($hint,strpos($hint,':')+1,strlen($hint));
		//$hint = "Colombo";
	    if ($hint == ""){
	     	$response="no suggestion";
	    }
	    else{
	        $response=$hint;
	    }	
	
	    echo $response;
		//echo "locationHint:13:group_id:0myigr-1;Selladurai Kethees , Sella , ks , ";
	    return $response;
	}
	
	function _shn_ajax_get_data($loc_type)
	{
		global $global, $conf;
		
		$db = $global['db'];
		$location= array ();
		$count=0;
	
		$sql="SELECT loc_uuid, loc_name FROM msg_location WHERE loc_type = '$loc_type'";
		
		$res = $db->Execute($sql);
		
		//var_dump($res);
		
		while(!$res->EOF){		
			$location[$count]=$res->fields['loc_name'].';'.$res->fields['loc_name'];
			$count++;
		
			$res->MoveNext();
		}
		
		return $location;		
	}
		
	
function _shn_admin_set_option_javascript()
{
?>
<script type="text/javascript">
    
	
	var url = "index.php?"; 
    var start = 1;
 	var http;
    function getHTTPObject() 
    {
        var xmlhttp;
        
        

        if (!xmlhttp && typeof XMLHttpRequest != 'undefined') {
            try {
                xmlhttp = new XMLHttpRequest();

            } catch (e) {
            xmlhttp = false;
            }
        }

    return xmlhttp;
    }



function handleHttpResponse(){
        if (http.readyState == 4) 
    { // Split the comma delimited response into an array  
                results = http.responseText.split(",");
		
                if (results[0]!="null")
            	{ 
                var x=document.getElementsByName('victim_to');
		
                    for (i=0; i<=x[0].options.length+1; i++)
                    {
                            x[0].options[0]=null;
				
                            }
 		

                j=0;
                for (i=1; i<results.length-1; i=i+2, j++)
                    {
                    
                         opt = document.createElement("option") ;
                          opt.value = results[i] ;
                          opt.text = results[i+1].replace(/[^A-Za-z]$/,"");
                          x[0].options[j] = opt;
                            }
                    }
        } 
    }


function change_action_priority(value){
    alert
//alert(value);
     if(value=='unknown'){         	
     	document.getElementById("des_yes").style.display='block';
	//document.getElementById("des_inventory").style.display='none';
	document.getElementById("des_no_urgent").style.display='none';
	document.getElementById("des_no_high").style.display='none';
	document.getElementById("des_no_low").style.display='none';     	
     }
 else if(value=='urgent'){         	
     	document.getElementById("des_no_urgent").style.display='block';  
	document.getElementById("des_yes").style.display='none';
	document.getElementById("des_no_high").style.display='none';
	document.getElementById("des_no_low").style.display='none';  
	//document.getElementById("des_shelter").style.display='none';
	//document.getElementById("des_organization").style.display='none';
	//document.getElementById("des_victim").style.display='none';   	
     }
 else if(value=='high'){         	
  	document.getElementById("des_no_high").style.display='block';  
	document.getElementById("des_yes").style.display='none';
	document.getElementById("des_no_urgent").style.display='none';
	document.getElementById("des_no_low").style.display='none';  
	//document.getElementById("des_shelter").style.display='none';
	//document.getElementById("des_organization").style.display='none';
	//document.getElementById("des_victim").style.display='none';   	
  }
 else if(value=='low'){         	
  	document.getElementById("des_no_low").style.display='block';  
	document.getElementById("des_yes").style.display='none';
	document.getElementById("des_no_urgent").style.display='none';
	document.getElementById("des_no_high").style.display='none';  
	//document.getElementById("des_shelter").style.display='none';
	//document.getElementById("des_organization").style.display='none';
	//document.getElementById("des_victim").style.display='none';   	
  }
 
     else
{
         document.getElementById("des_yes").style.display='none';
	document.getElementById("des_no_urgent").style.display='none';
	document.getElementById("des_no_high").style.display='none';
	document.getElementById("des_no_low").style.display='none';  
	//document.getElementById("des_organization").style.display='none';
	//document.getElementById("des_victim").style.display='none';
}	
     }


    function change_action_des(value){
        alert
	
         if(value=='yes'){         	
         	document.getElementById("des_yes").style.display='block';
		//document.getElementById("des_inventory").style.display='none';
		document.getElementById("des_no").style.display='none';
		//document.getElementById("des_organization").style.display='none';
		//document.getElementById("des_victim").style.display='none';     	
         }
	 else if(value=='no'){         	
         	document.getElementById("des_no").style.display='block';  
		document.getElementById("des_yes").style.display='none';
		//document.getElementById("des_shelter").style.display='none';
		//document.getElementById("des_organization").style.display='none';
		//document.getElementById("des_victim").style.display='none';   	
         }
	 
         else
	{
             document.getElementById("des_yes").style.display='none';
		document.getElementById("des_no").style.display='none';
		//document.getElementById("des_organization").style.display='none';
		//document.getElementById("des_victim").style.display='none';
	}	
         }

	function add_evacuees(){
		
        	var y=document.getElementsByName("head_name");
		
       		http = getHTTPObject();
        	var url2=url + "act=victims&mod=xst&stream=text&head_name="+y[0].value;
        	//var url2=url + "act=sub_cat&cat=" + selection+"&flag="+item_flag;
        	http.open("GET", url2, true); 
//        	http.onreadystatechange = null; 
        	http.onreadystatechange = function(){}; 
        	http.onreadystatechange = handleHttpResponse; 
        	http.send(null);
        }

	function form_clear_location_fields()
    {
    	var oforms = document.forms['cap_form'];
    	oforms['name'].value = "";
    	oforms['loc_cate'].value = "";
    	oforms['loc_type'].value = "";
    	oforms['description'].value = "";
    	oforms['opt_shape'].value = "";
    	oforms['x_vector'].value = "";
    	oforms['y_vector'].value = "";
    	oforms['z_vector'].value = "";
    	oforms['iso_code'].value = "";
    	oforms['textarea_areaDesc'].value = "";	
    }
    
</script>

		
<?php
}
?>
