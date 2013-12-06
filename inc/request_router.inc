<?php

//if www is not exists take the whole string
list($url,$stream) = explode(".",$_SERVER['REQUEST_URI']);
list($stream,$tmp) = explode("?",$stream);
list($script,$args) = explode("nurls/",$url);
// remove if there is an index.php
// explode by / and modifiy the get list
$args = explode('/',$args);
for($i=0;$i < count($args);$i++){
    $_GET[$args[$i]] = $args[$i+1];
    $_REQUEST[$args[$i]] = $args[++$i];
}
if(isset($stream) && $stream != 'php'){
    $_REQUEST['stream']=$stream;
    $_GET['stream']=$stream;
}

