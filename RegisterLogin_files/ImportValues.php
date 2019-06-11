<?php
    $con = mysqli_connect("localhost", "id5595788_mydatabase", "Ugysemaz99", "id5595788_mydatabase");
    
    $username = $_POST["username"];
    $password = $_POST["password"];
	$height = $_POST["height"];
	$address = $_POST["address"];
	
    $statement =  "UPDATE user SET height = $height, address = $address WHERE username = '$username'";

	$response = array();	
	if (mysqli_query($con, $statement)) {
		$response["success"] = true; 
	} else {
		$response["success"] = false; 
	}
    echo json_encode($response);
?>
