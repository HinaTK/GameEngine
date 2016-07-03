<?php

function Declaration($types, $name){
	$data = "std::map<";
	$header = "struct ".$name."\r\n{\r\n";
	$i = 0;
	foreach ($types as $key => $subVal) {
		if (0 == $i++) {
			$data .= $subVal.", ";
		}
		else{
			$header .= MakeStruct($key, $subVal);	
		}
	}
	$header .= "};\r\n";
	
	return $header.$data.$name."> m_".$name."_map;";
}
?>