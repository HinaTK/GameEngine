<?php

include("BaseParser.php");

class Parser extends BaseParser
{
	function __construct($config, $sheet){
		parent::__construct($config, $sheet);
    }

    function RealKey($index, $val)
    {
    	if ($this->name2Type[$this->index2Name[$index]] == "string") {
			return "\"".$val."\"";
		}
		return $val;
    }

    function RealVal($name, $val)
    {
    	switch ($this->name2Type[$name]) {
    		case 'array':
    			$arr = explode("|",$val);
    			return "{{".implode("},{",$arr)."}}";
    		case 'string':
    			return "\"".$val."\"";
    		// case 'weight':
    		// 	return $val;	
    		default:
    			return $val;
    	}
    }

    function Parse()
    {
		$tableName = "Config".$this->sheetName;

	    //echo $sheetName." ....\r\n";
	    $data = "local ".$tableName." {\r\n";
	    if (isset($this->config["template"][$this->sheetName])){
	    	include TEMPLATE_DIR.$this->config["template"][$this->sheetName].".php";
	    }
	    else
	    {
	    	include TEMPLATE_DIR."Key.php";
	    }
		$data .= "}\r\nreturn ".$tableName;

		file_put_contents($this->config["saveDir"].$tableName.".lua", $data);
    }

    function ParseLua($value)
    {
    	$data = "";
    	foreach ($value as $name => $subVal) {
			$data .= $name."=".$this->RealVal($name, $subVal).",";
		}
		return $data;
    }
}
?>
