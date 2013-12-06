<?php

/**
 * shn_home_default 
 * 
 * @access public
 * @return string
 */
function shn_home_default()
{
$message = _t("
        Real-Time Biosurveillance Program (RTBP) will be developed around the Information Communication and Technology (ICT) based surveillance and notification system. Pilot implementation in the two nations will be a research project aimed at evaluating the RTBP for a wider scale deployment in India and Sri Lanka with the possibility of extending the RTBP to the region.");
    switch ($_GET['stream_type']){
        case 'soap' :
            return $message;
        break;

        case 'xml' :
            return '<description>'.$message.'</description>';
        break;

        default:
            return $message;
        break;

    }
        
}

/**
 * This is a test function
 * 
 * @param string $var1 
 * @param string $var2 
 * @access public
 * @return void
 */
function shn_home_test($var1, $var2)
{

}
?>
