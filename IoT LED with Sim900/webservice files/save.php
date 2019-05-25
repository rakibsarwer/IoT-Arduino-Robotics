<html>
<body>
<?php
echo $_POST["red"]; 
echo $_POST["green"]; 
echo $_POST["blue"]; 

$red = "OFF";
$green = "OFF";
$blue = "OFF";

$savedDoneR = "0";
$savedDoneG = "0";
$savedDoneB = "0";

$servername = "mysql2.000webhost.com";
$username = "a5178504_sim900";
$password = "sim900";
$dbname = "a5178504_sim900";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "UPDATE ledStatus SET State='" .$_POST["red"]."' WHERE Color= 'red'";
$sql1 = "UPDATE ledStatus SET State='" .$_POST["green"]."' WHERE Color= 'green'";
$sql2 = "UPDATE ledStatus SET State='" .$_POST["blue"]."' WHERE Color= 'blue'";

if($conn->query($sql) === TRUE)
{
 $savedDoneR = "1";
}
else 
{
echo $sql;
    echo "Error updating record: " . $conn->error;
 $savedDoneR = "0";
}
$conn->close();
// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 


if($conn->query($sql1) === TRUE)
{
 $savedDoneG = "1";
}
else
{
 $savedDoneG = "0";
}
$conn->close();
// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

if($conn->query($sql2) === TRUE)
{
 $savedDoneB = "1";
}
else
{
 $savedDoneB = "0";
}
$conn->close();



if ($savedDoneB == "1" && $savedDoneG == "1" && $savedDoneR == "1") 

{
    echo "Record updated successfully";
		 if($_POST["red"] == "1")
		{
		$red = "ON";
		}
		else
		{
		 $red = "OFF";
		}
		if($_POST["green"] == "1")
		{
		$green = "ON";
		}
		else
		{
		$green = "OFF";
		}
		if($_POST["blue"] == "1")
		{
		$blue = "ON";
		}
		else
		{
		$blue = "OFF";
		}

		echo "<h4>New Status</h4>";
		echo "<h5>RED : " .$red . "</h5>" ;
		echo "<h5>GREEN : " .$green . "</h5>" ;
		echo "<h5>BLUE : " .$blue . "</h5>" ;

} 




?>
</body>
</html>