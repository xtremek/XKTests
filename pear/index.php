<?php

require_once 'MDB2.php';

$dsn = 'pgsql://xtremek:xtremek0753@172.27.12.132/xtremek';

$options = array(
    'debug' => 2,
    'result_buffering' => false,
);

$mdb2 =& MDB2::factory($dsn, $options);

if (PEAR::isError($mdb2)) {
    die($mdb2->getMessage());
} else {
    print 'Opened ' . $dsn . ' sucessfully!';
}

$res =& $mdb2->query('select * from tblUser');

if (PEAR::isError($res)) {
    die($res->getMessage());
}

while (($row = $res->fetchRow(MDB2_FETCHMODE_ASSOC))) {
    // Assuming MDB2's default fetchmode is MDB2_FETCHMODE_ORDERED
    echo 'User ID: ' . $row['uid'] . "\n";
    echo 'Company ID:  ' . $row['comid'] . "\n";
    echo 'Username:  ' . $row['login'] . "\n";
    echo 'Password:  ' . $row['password'] . "\n";
}

$mdb2->disconnect();

?>