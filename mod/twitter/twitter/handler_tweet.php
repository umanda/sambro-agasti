<?php

function shn_mod_tweet($messageTweet){
// Insert your keys/tokens
$consumerKey = '0G5lCtMXHk7Angvvf6LIQQ';
$consumerSecret = 'uIJwS4ZZIatAeLxWuC1WK6E8jyUBEEpq4DHhEB2vad8';
$oAuthToken = '392050169-Eh47o1d7Rm128JlJOW7reAs6PGnSZfpePcv8Ak';
$oAuthSecret = 'iPZV5BklLDo77rvkEgbu5SXiOweYHXJeHjPwW6F5gVk';

// Full path to twitteroauth.php (change oauth to your own path)



require_once('include/twitteroauth.php');

// create new instance
$tweet = new TwitterOAuth($consumerKey, $consumerSecret, $oAuthToken, $oAuthSecret);

// Your Message
$message = $messageTweet;

// Send tweet 
$response = $tweet->post('statuses/update', array('status' => "$message"));
if($response){
    echo '';
}else{
    echo 'Something went wrong!';
}

}
?>
