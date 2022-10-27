<?php
	$myfile = fopen("configs/content2.js", "w") ;
	fwrite($myfile, $_POST["json"]);
	fclose($myfile);
	exit(0);
?>