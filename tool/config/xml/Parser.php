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
    		case 'array':
    			$data = "";
    			$arr1 = explode("|",$val);
    			foreach ($arr1 as $value1) {
    				$data .= "<value>";
    				$arr2 = explode(",", $value1);
    				foreach ($arr2 as $value2) {
    					$arr3 = explode("=",$value2);
    					$data .="<".$arr3[0].">".$arr3[1]."</".$arr3[0].">";
    				}
    				$data .= "</value>";
    			}
    			return $data;	
    		default:
    			return $val;
    	}
    }

    function Parse()
    {
        $tableName = "Config".$this->sheetName;

		if (isset($this->config["header"])) {
            $header = "<header>\r\n";
			foreach ($this->name2Type as $key => $value){ 
				$header .= "\t<".$key.">".$value."</".$key.">\r\n";
			}
			$header .= "</header>\r\n";
            file_put_contents($this->config["header"].$tableName.".xml", $header);
        }
		
        $data = "<config>\r\n";
        foreach ($this->rows as $value) {
            $data .= $this->ParseXML($value);
        }
		$data .= "</config>";

        
        file_put_contents($this->config["saveDir"].$tableName.".xml", $data);
    }

    function ParseXML($value)
    {
    	$data = "\t<row>\r\n";
    	foreach ($value as $name => $subVal) {
			$data .= "\t\t<".$name.">".$this->RealVal($name, $subVal)."</".$name.">\r\n";
		}
		$data .= "\t</row>\r\n";
		return $data;
    }
}
?>
