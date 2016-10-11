<?php
namespace Home\Controller;

use Think\Controller;
use Home\Model\UserModel;

class NiumingController extends Controller {
	// 初始化方法
	public function _initialize() {
		echo 'hello NiumingController init <br/>';
		print_r ( $_REQUEST );
	}
	// 前置操作方法
	public function _before_getdata() {
		echo 'before<br/>';
	}
	// 后置操作方法
	public function _after_getdata() {
		echo 'after<br/>';
	}

	public function sayhello() {
		echo 'hello,niuming!';
	}
	
	public function getdata() {
		$conn = mysql_connect ( 'localhost', 'root', 'root' );
		if (! $conn) {
			die ( 'Could not connect: ' . mysql_error () );
		}
		mysql_select_db ( 'test', $conn );
		
		print_r ( $_REQUEST );
		
		print_r ( "  " );
		
		$pageindex = isset ( $_POST ['pageindex'] ) ? intval ( $_POST ['pageindex'] ) : 1;
		$pagesize = 20; // 写死每页20条
		
		print_r ( "pageindex_post=" . $_POST ['pageindex'] . "  " );
		print_r ( "pageindex_get=" . $_GET ['pageindex'] . "  " );
		
		$offset = ($pageindex - 1) * $pagesize;
		
		print_r ( "select * from test1 limit " . $offset . "," . $pagesize );
		
		$result = array (
				"code" => 1,
				"msg" => "牛鸣niuming",
				"extra" => "31" 
		);
		
		// include 'conn.php';
		
		$rs = mysql_query ( "select count(*) from test1" );
		$row = mysql_fetch_row ( $rs );
		
		$rs = mysql_query ( "select * from test1 limit " . $offset . "," . $pagesize );
		
		$items = array ();
		while ( $row = mysql_fetch_object ( $rs ) ) {
			array_push ( $items, $row );
		}
		$result ["data"] = $items;
		
		echo json_encode ( $result );
	}
	
	public function insert() {
		$User = D ( 'User' );//等价于$User = new UserModel();
		$User->name = $_POST ['name'];
		$User->sex = $_POST ['sex'];
		$User->age = isset ( $_POST ['age'] ) ? intval ( $_POST ['age'] ) : NULL;
		$result = $User->add (); // 写入数据数据库
		echo "uid=" . $result;
	}
	public function delete() {
		$User = D ( 'User' );
		$User->where ( 'uid=22' )->delete ();
		echo "uid=" . $result;
	}
	public function update() {
		$User = D ( 'User' );
		$User->name = 'rrr';
		$User->sex = 'ggg';
		$User->where ( 'uid=20' )->save ();
	}
	public function query() {
		$User = D ( 'User' );
// 		$data = $User->where ( 'age>10' )->select ();
		//过滤字段，只显示name，sex
		$data = $User->where ( 'age>10' )->field( 'name,sex' )->find();
		echo json_encode ( $data );
	}
}