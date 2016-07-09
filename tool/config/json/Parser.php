<?php

include("BaseParser.php");

class Parser extends BaseParser
{
	function __construct($config, $sheet){
        parent::__construct($config, $sheet);
    }

    function RealVal($name, $val, $tab)
    {
    	switch ($this->name2Type[$name]) {
    		case 'vector':
    			$data = "{\"ROW\":[\r\n";
    			$arr1 = explode("|",$val);
    			foreach ($arr1 as $value1) {
    				$data .= $tab."{\r\n";
    				$arr2 = explode(",", $value1);
    				foreach ($arr2 as $value2) {
    					$arr3 = explode("=",$value2);
    					$data .= $tab."\t\"".$arr3[0]."\":".$arr3[1].",\r\n";
    				}
                    $data = substr_replace($data, "\r\n".$tab."},\r\n", -3);
    			}
    			return substr_replace($data, "\r\n\t\t]}", -3);
            case 'embed':
               $data = "{\"ROW\":[\r\n";
                if (isset($this->embed->embedData[$val])) {
                    foreach ($this->embed->embedData[$val] as $value) {
                        $data .= $value;
                    }
                }
                return substr_replace($data, "\r\n\t\t]}", -3);
                //return $data."\t\t]}";
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
            $this->embedData[$val][] = $this->ParseJSON($value, "\t\t\t");
        }
    }

    function Parse()
    {
        $tableName = "Config".$this->sheetName;
		
        $data = "{\"ROW\":[\r\n";
        foreach ($this->rows as $value) {
            $data .= $this->ParseJSON($value, "\t");
        }
        $data = substr_replace($data, "\r\n]}", -3);
        
        file_put_contents($this->config["saveDir"].$tableName.".xml", $data);
    }

    function ParseJSON($value, $tab)
    {
        $data = $tab."{\r\n";
    	foreach ($value as $name => $subVal) {
			$data .= $tab."\t\"".$name."\":".$this->RealVal($name, $subVal, $tab."\t\t").",\r\n";
		}
        return substr_replace($data, "\r\n".$tab."},\r\n", -3);
    }
}
?>
