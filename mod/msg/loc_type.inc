<?php
	
	function shn_alert_area_location_type($locationCategory = null, $locationType = null)
	{
	    global $global;	    
	    
	    //$sql = "SELECT loc_cate FROM bsm_loc_type WHERE deactivate_dt IS NULL AND loc_type = '$loc_type' ORDER BY loc_type ASC";
	    //$loc_cate = $global['db']->GetOne($sql);
	
	    $loc_cate = (isset($_POST['loc_cate']) && $_POST['loc_cate'] != null) ? $_POST['loc_cate'] : $locationCategory;
	    $loc_type = (isset($_POST['loc_type']) && $_POST['loc_type'] != null) ? $_POST['loc_type'] : $locationType;
	     
	    shn_xajax_registerFunction('bsm_change_loc_types');
	    $sql = "SELECT * FROM msg_loc_cate WHERE deactivate_dt IS NULL ORDER BY loc_cate ASC";
	    $rsql = $global['db']->GetAll($sql);
	    $arropt = array(''=>'');
	    foreach ($rsql AS $r => $rv)
	    {
	        $arropt[$rv['loc_cate']]=$rv['loc_cate'];
	    }	    
	    
	    //var_dump($_POST);
	    
	    
	    shn_form_select($arropt,_('Location Category'), 'loc_cate_area',' onchange="bsm_change_loc_types(this.value, \'loc_type_area\')"',array('value'=>$loc_cate));	
	    
	    
	    $sql = "SELECT loc_type FROM msg_loc_type WHERE deactivate_dt IS NULL AND loc_cate = '$loc_cate' ORDER BY loc_type ASC";
	
	    $rsql = $global['db']->Execute($sql);
	
	    $arropt = array(''=>'');
	    foreach ($rsql AS $r => $rv)
	    {
	        $arropt[$rv['loc_type']]=$rv['loc_type'];
	    }	   
	
	    shn_form_select($arropt,_('Location Type'), 'loc_type_area',null,array('value'=>$loc_type));		
	}
