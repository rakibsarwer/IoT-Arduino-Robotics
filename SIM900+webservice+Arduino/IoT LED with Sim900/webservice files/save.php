<html>
<body>
<?php
echo $_POST["red"]; 
echo $_POST["green"]; 

$red = "OFF";
$green = "OFF";

$savedDoneR = "0";
$savedDoneG = "0";

$servername = "localhost";
$username = "id7001629_iottest";
$password = "mgsr25657860";
$dbname = "id7001629_iottest";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "UPDATE ledStatus SET State='" .$_POST["red"]."' WHERE Color= 'red'";
$sql1 = "UPDATE ledStatus SET State='" .$_POST["green"]."' WHERE Color= 'green'";

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



if ($savedDoneG == "1" && $savedDoneR == "1") 

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
		

		echo "<h4>New Status</h4>";
		echo "<h5>RED : " .$red . "</h5>" ;
		echo "<h5>GREEN : " .$green . "</h5>" ;
		

} 




?>
</body>
</html>