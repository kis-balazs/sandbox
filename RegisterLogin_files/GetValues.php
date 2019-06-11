<?php
    $con = mysqli_connect("localhost", "id5595788_mydatabase", "Ugysemaz99", "id5595788_mydatabase");
    
    $username = $_POST["username"];
    
    $statement = mysqli_prepare($con, "SELECT * FROM user WHERE username = ?");
    mysqli_stmt_bind_param($statement, "s", $username);
    mysqli_stmt_execute($statement);
    
    mysqli_stmt_store_result($statement);
    mysqli_stmt_bind_result($statement, $userID, $name, $username, $age, $password, $height, $address);
    
    $response = array();
    $response["success"] = false;  
    
    while(mysqli_stmt_fetch($statement)){
        $response["success"] = true;
        $response["username"] = $username;
        $response["height"] = $height;
		$response["address"] = $address;
    }
    
    echo json_encode($response);
	mysql_close;
?>
