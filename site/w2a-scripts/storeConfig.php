<?php
	$myfile = fopen("configs/config2.js", "w") ;
	fwrite($myfile, $_POST["json"]);
	fclose($myfile);
	exit(0);
?>