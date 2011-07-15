<?php

$a[] = "Jesse";
$a[] = "Demi";

$q = $_GET["q"];

$qsize = strlen($q);

if ($qsize > 0) {
    $hint = "";

    for ($i = 0; $i < count($a); $i++) {
        if (strtolower($q) == strtolower(substr($a[$i], 0, $qsize))) {
            if ($hint == "") {
                $hint = $a[$i];
            } else {
                $hint = $hint . " , " . $a[$i];
            }
        }
    }
}

if ($hint == "") {
    $response = "no names found...";
} else {
    $response = $hint;
}   

echo $response;

?>