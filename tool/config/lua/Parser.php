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
    		case 'vector':
    			$arr = explode("|",$val);
    			return "{{".implode("},{",$arr)."}}";
            case 'embed':
                $data = "";
                if (isset($this->embed->embedData[$val])) {
                    foreach ($this->embed->embedData[$val] as $value) {
                        $data .= "{".$value."},";
                    }
                }
                return "{".$data."}";    
    		case 'string':
    			return "\"".$val."\"";	
    		default:
    			return $val;
    	}
    }

    function ParseEmbed()
    {
        foreach ($this->rows as $value) {
            $val = $value[$this->index2Name[0]];
            if (!isset($this->embedData)) {
                $this->embedData = array();
            }
            if (!isset($this->embedData[$val])) {
                $this->embedData[$val] = array();
            }
            $this->embedData[$val][] = $this->ParseLua($value);
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
