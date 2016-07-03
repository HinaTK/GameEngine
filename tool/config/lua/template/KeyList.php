<?php
$temp = array();
foreach ($this->rows as $value) {
	$val = $value[$this->index2Name[0]];
	if (!isset($temp[$val])) $temp[$val] = array();
	
	$temp[$val][] = $value;
}

foreach ($temp as $key => $value) {
	$data .= "[".$this->RealKey(0, $value[$this->index2Name[0]])."] = {\r\n";
	foreach ($value as $subKey => $subVal) {
		$data .= "[".$subKey."] = {\r\n";
		$data .= $this->ParseLua($value);
		$data .= "},\r\n";
	}
	$data .= "},\r\n";
}
?>