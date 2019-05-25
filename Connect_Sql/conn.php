
<?php
class rfid{
 public $link='';
 function __construct($id){
  $this->connect();
  $this->storeInDB($id);
 }
 
 function connect(){
  $this->link = mysql_connect('localhost','root','') or die('Cannot connect to the DB');
  mysql_select_db('rfid') or die('Cannot select the DB');
 }
 
 function storeInDB($id){
  $query = "insert into tb_rfid set rfid='".$id."'";
  $result = mysql_query($query) or die('Errant query:  '.$query);
 }
 
}


?>
