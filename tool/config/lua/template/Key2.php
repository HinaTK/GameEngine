<?php
$temp = array();
foreach ($this->rows as $value) {
	$val1 = $value[$this->index2Name[0]];
	$val2 = $value[$this->index2Name[1]];

	if (!isset($temp[$val])) $temp[$val1] = array();

	$temp[$val1][$val2] = $value;
}

foreach ($temp as $key => $value) {
	$data .= "[".$this->RealKey(0, $key)."] = {\r\n";
	foreach ($value as $subKey => $subVal) {
		$data .= "[".$this->RealKey(1, $subKey)."] =";
		$data .= "{";
		$data .= $this->ParseLua($subVal);
		$data .= "},\r\n";
	}
	$data .= "},\r\n";
}
?>