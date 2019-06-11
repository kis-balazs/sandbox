<?php
    $con = mysqli_connect("localhost", "id5595788_mydatabase", "Ugysemaz99", "id5595788_mydatabase");
 
    $username = $_POST["username"];
	
    $statement = mysqli_prepare($con, "DELETE FROM user WHERE username = '$username'");
    
    $response = array();
    $response["success"] = true;  
    
    echo json_encode($response);
?>