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
    			$data = "\r\n";
    			$arr1 = explode("|",$val);
    			foreach ($arr1 as $value1) {
    				$data .= $tab."<row>\r\n";
    				$arr2 = explode(",", $value1);
    				foreach ($arr2 as $value2) {
    					$arr3 = explode("=",$value2);
    					$data .= $tab."\t<".$arr3[0].">".$arr3[1]."</".$arr3[0].">\r\n";
    				}
    				$data .= $tab."</row>\r\n";
    			}
    			return $data."\t\t";
            case 'embed':
                $data = "\r\n";
                if (isset($this->embed->embedData[$val])) {
                    foreach ($this->embed->embedData[$val] as $value) {
                        $data .= $value;
                    }
                }
                return $data."\t\t";
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
            $this->embedData[$val][] = $this->ParseXML($value, "\t\t\t");
        }
    }

    function Parse()
    {
        $tableName = "Config".$this->sheetName;

        // todo 宏定义这一段代码
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
            $data .= $this->ParseXML($value, "\t");
        }
		$data .= "</config>";

        
        file_put_contents($this->config["saveDir"].$tableName.".xml", $data);
    }

    function ParseXML($value, $tab)
    {
    	$data = $tab."<row>\r\n";
    	foreach ($value as $name => $subVal) {
			$data .= $tab."\t<".$name.">".$this->RealVal($name, $subVal, $tab."\t\t")."</".$name.">\r\n";
		}
		$data .= $tab."</row>\r\n";
		return $data;
    }
}
?>
