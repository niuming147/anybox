<?php
namespace Home\Model;
use Think\Model;

class UserModel extends Model {
	protected $trueTableName = 't_user';
// 	protected $dbName = 'top';
	protected $fields = array('name', 'sex');
	

}