<?php

$actual_link = 'http://'.$_SERVER['HTTP_HOST'].$_SERVER['REQUEST_URI'].'www/index.php';

header("Location:".$actual_link);

?>