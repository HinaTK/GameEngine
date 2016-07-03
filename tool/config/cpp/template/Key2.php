<?php
class Handle
{
	private $types;
	private $name;
	private $keys;
	function __construct($types, $name){
        $this->types = $types;
        $this->name = $name;
        $keys = array();
    }

    function Header()
    {
    	$keyName = $this->name."Key";
		$structKey = "struct ".$keyName."\r\n{\r\n";
		$op = "";

		$header = "struct ".$this->name."\r\n{\r\n";
		$i = 0;
		foreach ($this->types as $key => $subVal) {
			if (0 == $i) {
				$op = "\t\tif (".$key." < key.".$key." ) return true;\r\n";
				$op .= "\t\tif (".$key." == key.".$key." ) return ";
			}
			elseif (1 == $i) {
				$structKey .= "\t".$subVal." ".$key.";\r\n";
				$op .= $key." < key.".$key.";\r\n";
				$op .= "\t\treturn false;\r\n";
			}
			else{
				$header .= MakeStruct($key, $subVal);
				continue;	
			}
			$structKey .= "\t".$subVal." ".$key.";\r\n";
			$keys[$key] = $subVal;
			$i++;
		}

		$structKey .= "\tbool operator < (const ".$keyName." &key) const\r\n\t{\r\n".$op."\t};\r\n";
		$structKey .= "};\r\n";
		$header .= "};\r\n";
		
		return $structKey.$header."std::map<".$keyName.", ".$this->name."> m_".$this->name."_map;";
    }

    function Body($key)
    {
    	$field = "info.".$key;
    	if (isset($this->keys[$key])) {
    		$field = "key.".$key;
    	}
    	return "!GetSubNodeValue(curElement, \"".$key."\", ".$field.", err) ||\r\n\t\t\t\t";
    }
}
function Declaration($types, $name){
	$keyName = $name."Key";
	$structKey = "struct ".$keyName."\r\n{\r\n";
	$op = "";

	$header = "struct ".$name."\r\n{\r\n";
	$i = 0;
	foreach ($types as $key => $subVal) {
		if (0 == $i) {
			$structKey .= "\t".$subVal." ".$key.";\r\n";
			$op = "\t\tif (".$key." < key.".$key." ) return true;\r\n";
			$op .= "\t\tif (".$key." == key.".$key." ) return ";
			$i++;
		}
		elseif (1 == $i) {
			$structKey .= "\t".$subVal." ".$key.";\r\n";
			$op .= $key." < key.".$key.";\r\n";
			$op .= "\t\treturn false;\r\n";
			$i++;
		}
		else{
			$header .= MakeStruct($key, $subVal);	
		}
	}

	$structKey .= "\tbool operator < (const ".$keyName." &key) const\r\n\t{\r\n".$op."\t};\r\n";
	$structKey .= "};\r\n";
	$header .= "};\r\n";
	
	return $structKey.$header."std::map<".$keyName.", ".$name."> m_".$name."_map;";
}
?>