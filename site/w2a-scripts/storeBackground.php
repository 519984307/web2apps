<?php
/*
This is an upload script for SWFUpload that attempts to properly handle uploaded files
in a secure way.

Notes:
	
	SWFUpload doesn't send a MIME-TYPE. In my opinion this is ok since MIME-TYPE is no better than
	 file extension and is probably worse because it can vary from OS to OS and browser to browser (for the same file).
	 The best thing to do is content sniff the file but this can be resource intensive, is difficult, and can still be fooled or inaccurate.
	 Accepting uploads can never be 100% secure.
	 
	You can't guarantee that SWFUpload is really the source of the upload.  A malicious user
	 will probably be uploading from a tool that sends invalid or false metadata about the file.
	 The script should properly handle this.
	 
	The script should not over-write existing files.
	
	The script should strip away invalid characters from the file name or reject the file.
	
	The script should not allow files to be saved that could then be executed on the webserver (such as .php files).
	 To keep things simple we will use an extension whitelist for allowed file extensions.  Which files should be allowed
	 depends on your server configuration. The extension white-list is _not_ tied your SWFUpload file_types setting
	
	For better security uploaded files should be stored outside the webserver's document root.  Downloaded files
	 should be accessed via a download script that proxies from the file system to the webserver.  This prevents
	 users from executing malicious uploaded files.  It also gives the developer control over the outgoing mime-type,
	 access restrictions, etc.  This, however, is outside the scope of this script.
	
	SWFUpload sends each file as a separate POST rather than several files in a single post. This is a better
	 method in my opinions since it better handles file size limits, e.g., if post_max_size is 100 MB and I post two 60 MB files then
	 the post would fail (2x60MB = 120MB). In SWFupload each 60 MB is posted as separate post and we stay within the limits. This
	 also simplifies the upload script since we only have to handle a single file.
	
	The script should properly handle situations where the post was too large or the posted file is larger than
	 our defined max.  These values are not tied to your SWFUpload file_size_limit setting.
	
*/
	
function imageCreateFromAny($filepath) {
    $type = exif_imagetype($filepath); // [] if you don't have exif you could use getImageSize()
    $allowedTypes = array(
        1,  // [] gif
        2,  // [] jpg
        3,  // [] png
        6   // [] bmp
    );
    if (!in_array($type, $allowedTypes)) {
        return false;
    }
    switch ($type) {
        case 1 :
            $im = imageCreateFromGif($filepath);
        break;
        case 2 :
            $im = imageCreateFromJpeg($filepath);
        break;
        case 3 :
            $im = imageCreateFromPng($filepath);
        break;
        case 6 :
            $im = imageCreateFromBmp($filepath);
        break;
    }   
    return $im; 
} 
	
// Check post_max_size (http://us3.php.net/manual/en/features.file-upload.php#73762)
	$POST_MAX_SIZE = ini_get('post_max_size');
	$unit = strtoupper(substr($POST_MAX_SIZE, -1));
	$multiplier = ($unit == 'M' ? 1048576 : ($unit == 'K' ? 1024 : ($unit == 'G' ? 1073741824 : 1)));

	if ((int)$_SERVER['CONTENT_LENGTH'] > $multiplier*(int)$POST_MAX_SIZE && $POST_MAX_SIZE) {
		header("HTTP/1.1 500 Internal Server Error"); // This will trigger an uploadError event in SWFUpload
		echo "POST exceeded maximum allowed size.";
		exit(0);
	}	
	
// Settings
	$upload_name = "userfile";
	$max_file_size_in_bytes = 2147483647;				// 2GB in bytes
	$extension_whitelist = array("jpg", "gif", "png", "jpeg", "bmp");	// Allowed file extensions

// Other variables	
	$MAX_FILENAME_LENGTH = 260;
	$file_name = "";
	$file_extension = "";
	$uploadErrors = array(
        0=>"There is no error, the file uploaded with success",
        1=>"The uploaded file exceeds the upload_max_filesize directive in php.ini",
        2=>"The uploaded file exceeds the MAX_FILE_SIZE directive that was specified in the HTML form",
        3=>"The uploaded file was only partially uploaded",
        4=>"No file was uploaded",
        6=>"Missing a temporary folder"
	);


// Validate the upload
	if (!isset($_FILES[$upload_name])) {
		HandleError("No upload found in \$_FILES for " . $upload_name);
		exit(0);
	} else if (isset($_FILES[$upload_name]["error"]) && $_FILES[$upload_name]["error"] != 0) {
		HandleError($uploadErrors[$_FILES[$upload_name]["error"]]);
		exit(0);
	} else if (!isset($_FILES[$upload_name]["tmp_name"]) || !@is_uploaded_file($_FILES[$upload_name]["tmp_name"])) {
		HandleError("Upload failed is_uploaded_file test.");
		exit(0);
	} else if (!isset($_FILES[$upload_name]['name'])) {
		HandleError("File has no name.");
		exit(0);
	}
	
// Validate the file size (Warning: the largest files supported by this code is 2GB)
	$file_size = @filesize($_FILES[$upload_name]["tmp_name"]);
	if (!$file_size || $file_size > $max_file_size_in_bytes) {
		HandleError("File exceeds the maximum allowed size");
		exit(0);
	}
	
	if ($file_size <= 0) {
		HandleError("File size outside allowed lower bound");
		exit(0);
	}

	// Validate file extension
	$path_info = pathinfo($_FILES[$upload_name]['name']);
	$file_extension = $path_info["extension"];
	$is_valid_extension = false;
	foreach ($extension_whitelist as $extension) {
		if (strcasecmp($file_extension, $extension) == 0) {
			$is_valid_extension = true;
			break;
		}
	}
	if (!$is_valid_extension) {
		HandleError("Invalid file extension");
		exit(0);
	}

/*
	Activate this is an automatic resizing is wanter
	
	$max_w = 1600;
	$max_h = 1600;
	
	$img = imagecreatefromjpeg($_FILES[$upload_name]["tmp_name"]);
	if (!$img) {
		echo "ERROR:could not create image handle ". $_FILES[$upload_name]["tmp_name"];
		exit(0);
	}

	$width = imageSX($img);
	$height = imageSY($img);

	
	if (!$width || !$height) {
		echo "ERROR:Invalid width or height";
		exit(0);
	}
	if($width>=$height){
		if($width>$max_w){
			// Build the thumbnail
			$target_width = $max_w;
			$target_ratio = $height / $width;
			$target_height = ($max_w * $target_ratio) ;	
		}
		else {
			$target_height = $height ;
			$target_width = $width;
		}
	} else {
		if($height>$max_h){
			// Build the thumbnail
			$target_height = $max_h ;
			$target_ratio = $width / $height ;
			$target_width = ($max_h * $target_ratio) ;
		}
		else {
			$target_height = $height ;
			$target_width = $width;
		}
	}

	$new_img = ImageCreateTrueColor($target_width, $target_height);
	if (!@imagecopyresampled($new_img, $img, 0, 0, 0, 0, $target_width, $target_height, $width, $height)) {
		echo "ERROR:Could not resize image";
		exit(0);
	}

	$file_id = $sql_id."_".md5("secret_".$sql_id);

	
	if (!imagejpeg($new_img, $save_path."/".$file_id.".jpg",60)) {
		HandleError("File could not be saved.");
		exit(0);
	}
	*/
	
	$uploaddir = './';
	$filenametouse = $_FILES['userfile']['name'];
	
	
	if(!preg_match('/^[0-9a-zA-Z]+$/',$path_info["filename"])) {
		echo'Filename '.$path_info["filename"].' is not valid!';
		exit(0);
	}
	
	if(!preg_match('/^[0-9a-zA-Z \-\_]+$/',$_POST['server-name'])) {
		echo'Server name '.$_POST['server-name'].' is not valid!';
		exit(0);
	}
	
	$uploadfile = $uploaddir .'/'. $_POST['server-name'] .'/'. $path_info["filename"] .".". $path_info["extension"];;
	$thumbfile = $uploaddir .'/'. $_POST['server-name'] .'/thumbs/t_'. $path_info["filename"].'.png';

	if(file_exists($uploadfile)) {
		unlink($uploadfile); //remove the file
	}

	if (!move_uploaded_file($_FILES['userfile']['tmp_name'], $uploadfile)) {
		HandleError("File move failed");
		exit(0);
	}
	
	$new_img = imageCreateFromAny($uploadfile);
	
	
	//Create a thumbnail version 
	$width = imageSX($new_img);
	$height = imageSY($new_img);

	if (!$width || !$height) {
		echo "ERROR:Invalid width or height";
		exit(0);
	}

	// Build the thumbnail
	$target_width = 200;
	$target_height = 200;
	$target_ratio = $target_width / $target_height;

	$img_ratio = $width / $height;

	if ($target_ratio > $img_ratio) {
		$new_height = $target_height;
		$new_width = $img_ratio * $target_height;
	} else {
		$new_height = $target_width / $img_ratio;
		$new_width = $target_width;
	}

	if ($new_height > $target_height) {
		$new_height = $target_height;
	}
	if ($new_width > $target_width) {
		$new_height = $target_width;
	}

	$new_thumb = ImageCreateTrueColor($new_width, $new_height);
	imagealphablending( $new_thumb , false );
	imagesavealpha( $new_thumb , true );
	/*
	If you want a square thumbnail, and fill its background in blck
	if (!@imagefilledrectangle($new_thumb, 0, 0, $target_width-1, $target_height-1, 0)) {	// Fill the image black
		echo "ERROR:Could not fill new image";
		exit(0);
	}

	if (!@imagecopyresampled($new_thumb, $new_img, ($target_width-$new_width)/2, ($target_height-$new_height)/2, 0, 0, $new_width, $new_height, $width, $height)) {
		echo "ERROR:Could not resize image";
		exit(0);
	}*/
	if (!@imagecopyresampled($new_thumb, $new_img, 0, 0 ,0, 0, $new_width, $new_height, $width, $height)) {
		echo "ERROR:Could not resize image";
		exit(0);
	}
	$thumbfilename=$file_id;
	
	if (!imagepng($new_thumb, $thumbfile, 9)) {
		HandleError("File could not be saved.");
		exit(0);
	}	
	
	
	exit(0);


/* Handles the error output. This error message will be sent to the uploadSuccess event handler.  The event handler
will have to check for any error messages and react as needed. */
function HandleError($message) {
	echo $message;
}
?>