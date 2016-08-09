<?php

include("BaseParser.php");

class Parser extends BaseParser
{
	function __construct($config, $sheet){
        parent::__construct($config, $sheet);
    }

    function RealVal($name, $val)
    {

    	switch ($this->name2Type[$name]) {
    		case 'vector':
    			$data = "[";
    			$arr1 = explode("|",$val);
    			foreach ($arr1 as $value1) {
    				$data .= "{";
    				$arr2 = explode(",", $value1);
    				foreach ($arr2 as $value2) {
    					$arr3 = explode("=",$value2);
    					$data .= "\"".$arr3[0]."\":".$arr3[1].",";
    				}
                    $data = substr_replace($data, "},", -1);
    			}
    			return substr_replace($data, "]", -1);
            case 'embed':
               $data = "[";
                if (isset($this->embed->embedData[$val])) {
                    foreach ($this->embed->embedData[$val] as $value) {
                        $data .= $value;
                    }
                }
                return substr_replace($data, "]", -1);
            //case 'mixture':

            case 'string':
                return '"'.$val.'"';
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
            $this->embedData[$val][] = $this->ParseJSON($value);
        }
    }

    function Parse()
    {
        $tableName = "Config".$this->sheetName;
		
        $data = "[\r\n";
        foreach ($this->rows as $value) {
            $data .= "\t{";
            foreach ($value as $name => $subVal) {
                $data .= "\"".$name."\":".$this->RealVal($name, $subVal).",";
            }
            $data = substr_replace($data, "},\r\n", -1);
        }
        $data = substr_replace($data, "\r\n]", -3);
        
        file_put_contents($this->config["saveDir"].$tableName.".json", $data);
    }

    function ParseJSON($value)
    {
        $data = "{";
    	foreach ($value as $name => $subVal) {
			$data .= "\"".$name."\":".$this->RealVal($name, $subVal).",";
		}
        return substr_replace($data, "},", -1);
    }
}
?>
