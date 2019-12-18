<?php
$timestamp = "The current time is " . date("h:i:sa"). "<br>\r\n";
file_put_contents('dataDisplayer.html', $timestamp, FILE_APPEND);

$s = json_decode( file_get_contents('php://input'), true );

file_put_contents('dataDisplayer.html', var_export( $s, true ). "<br>\r\n", FILE_APPEND);

?>
