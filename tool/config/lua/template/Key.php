<?php
foreach ($this->rows as $value) {
	$data .= "[".$this->RealKey(0, $value[$this->index2Name[0]])."] = {";
	$data .= $this->ParseLua($value);
	$data .= "},\r\n";
}
?>