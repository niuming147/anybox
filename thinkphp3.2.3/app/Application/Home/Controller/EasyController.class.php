<?php

namespace Home\Controller;

use Think\Controller;
use Home\Model\UserModel;

class EasyController extends Controller {
	public function sayhello() {
		echo 'hello,EasyController!';
	}
	
// 	public function getdata() {
// 		$conn = mysql_connect ( 'localhost', 'root', 'root' );
// 		if (! $conn) {
// 			die ( 'Could not connect: ' . mysql_error () );
// 		}
// 		mysql_select_db ( 'test', $conn );
		
// 		$page = isset($_POST['page']) ? intval($_POST['page']) : 1;
// 		$rows = isset($_POST['rows']) ? intval($_POST['rows']) : 10;
// 		$offset = ($page-1)*$rows;
		
// 		//$result = array();
// 		$result=array("code"=>1,"msg"=>"牛鸣","extra"=>"31");
// 		$rs = mysql_query ( "select count(*) from test1" );
// 		$row = mysql_fetch_row ( $rs );
// 		$result ["total"] = $row [0];
		
// 		$rs = mysql_query ( "select * from test1 limit $offset,$rows" );
		
// 		$items = array ();
// 		while ( $row = mysql_fetch_object ( $rs ) ) {
// 			array_push ( $items, $row );
// 		}
// 		$result ["rows"] = $items;
		
// 		echo json_encode ( $result );
// 	}
	
	public function getdata2() {
		
		//先收cookie
		$coo = cookie('myname');
// 		print_r("getcookie=".$coo);
// 		\Think\Log::write("getcookie=".$coo);
		\Think\Log::record("getcookie=".$coo);
		//再设置cookie		
		cookie('myname',"zxccccc");  //设置cookie
		
		
		$User = M ('test1');
		$data = $User->select ();
// 		$data = $User->where ( 'age>10' )->find ();

		$result = array();
		$result ["total"] = 58;
		$result ["rows"] = $data;
		
		echo json_encode ( $result );
	}
}