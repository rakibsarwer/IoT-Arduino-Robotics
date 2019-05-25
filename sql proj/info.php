<?php
   
    $dbusername = "rfid";  
    $dbpassword = "rfid";  
    $server = "localhost"; 
  
    $dbconnect = mysqli_connect($server, $dbusername, $dbpassword);
    $dbselect = mysqli_select_db($dbconnect, "rfid");
    
  $request= $_GET['rfid'];

    $sql = "INSERT INTO rfidtable1.rfid (rfid) VALUES ('$request')";
 
    mysqli_query($dbconnect,$sql);

?>

<html>
<head>
    <
</head>
</html>