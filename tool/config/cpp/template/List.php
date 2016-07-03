<?php

function Declaration($types, $name){
	$data = "std::vector<";
	$header = "struct ".$name."\r\n{\r\n";
	$i = 0;
	foreach ($types as $key => $subVal) {
		$header .= MakeStruct($key, $subVal);
	}
	$header .= "};\r\n";
	
	return $header.$data.$name."> m_".$name."_vector;";
}
?>