<?php

$i = 1;
foreach ($this->rows as $value) {
	$data .= "[".$i++."] = {";
	$data .= $this->ParseLua($value);
	$data .= "},\r\n";
}
?>