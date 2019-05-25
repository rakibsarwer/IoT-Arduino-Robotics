
1. create a DB and create the table (use the dbscript to create the table)

2. add three lines of data as 
   INSERT INTO `ledStatus` VALUES(1, 'blue', '1');
INSERT INTO `ledStatus` VALUES(2, 'red', '1');
INSERT INTO `ledStatus` VALUES(3, 'green', '0');

3.open save.php and getstate.php files and change the connections information as you need
  $servername = "----";
$username = "-----";
$password = "-----";
$dbname = "-----";

4. copy save.php, index.html and getstate.php files to the root location of the serve 
then check the application is working fine by changing values.




This is only if you need to create the webservice only.