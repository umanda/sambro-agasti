<?php

function shn_mod_tweet($messageTweet){
// Insert your keys/tokens
$consumerKey = 'Jz5p9ooGU9PDnH72VqWvfo1OY';
$consumerSecret = '31HbcCUZjrUQzr2w07ThnYNBsEVIEGHJkuuYiij0r2TXtPZ7VY';
$oAuthToken = '392050169-RI4Ubihvkej1dytVcyvbnYUIsvKocUkgiWLWu3E2';
$oAuthSecret = 'fHF7ckrZWWrNU4Y9pcqONFnkewGeafXeBSDZUweFXsFb6';

// Full path to twitteroauth.php (change oauth to your own path)



require_once('include/twitteroauth.php');

// create new instance
$tweet = new TwitterOAuth($consumerKey, $consumerSecret, $oAuthToken, $oAuthSecret);

// Your Message
$message = $messageTweet;

// Send tweet 
$response = $tweet->post('statuses/update', array('status' => "$message"));
echo $response;
if($response){
echo "tweet = ";
echo $tweet;
echo ", message = ";
echo $message;
echo ", response = ";
echo $response;
add_confirmation(_t('TWEET information posted successfully'));
    echo ', yes';
}else{
	add_error(_t('TWEET information not posted successfully'));
    echo 'Something went wrong!';
}

}
?>
