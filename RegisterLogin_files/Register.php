<?php
    $con = mysqli_connect("localhost", "id5595788_mydatabase", "Ugysemaz99", "id5595788_mydatabase");
    
    $name = $_POST["name"];
    $age = $_POST["age"];
    $username = $_POST["username"];
    $password = $_POST["password"];
	$height = $_POST["height"];
	$address = $_POST["address"];
	
    $statement = mysqli_prepare($con, "INSERT INTO user(name, username, age, password, height, address) VALUES (?, ?, ?, ?, 0, 0)");
    mysqli_stmt_bind_param($statement, "ssis", $name, $username, $age, $password);
    mysqli_stmt_execute($statement);
    
    $response = array();
    $response["success"] = true;  
    
    echo json_encode($response);
?>
