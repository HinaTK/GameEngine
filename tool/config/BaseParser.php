<?php
class BaseParser
{
	protected $rows;
	protected $sheetName;
	protected $index2Name;
	protected $name2Type;
	protected $config;
	function __construct($config, $sheet){
        $rows = $sheet->Table->Row;
        $this->sheetName = $sheet->attributes('ss', true)->Name."";
        $this->index2Name = array();
	    $this->name2Type = array();

	    $i = 0;
		foreach($rows[$config["nameRow"]] as $cell){
		    $val = trim((string)$cell->Data);
		    if($val) {
		        $this->index2Name[$i] = $val;
		    }
		    $i++;
		}

		$i = 0;
		foreach($rows[$config["typeRow"]] as $cell){
		    $val = trim((string)$cell->Data);
		    if ($val && isset($this->index2Name[$i])) {
		    	$this->name2Type[$this->index2Name[$i]] = $val;
		    	if ($val == "embed") {
		    		$embedSheet = GetSheetByName(FILTER_SHEET.$this->index2Name[$i]);
                    if ($embedSheet) {
                        $this->embed = new Parser($config, $embedSheet);
                        $this->embed->ParseEmbed();
                    }
                    else{
                    	exit("can not find the sheet name: ".FILTER_SHEET.$this->index2Name[$i]."\r\n");
                    }
		    	}
		    }
		    $i++;
		}

		$i = 0;
	    foreach($rows as $row){
	        if(($i++) < $config["beginRow"]) continue;
	        $rowData = array();
	        $index = 0;
	        foreach($row->Cell as $cell){
	        	if (isset($this->index2Name[$index])) {
	    			$rowData[$this->index2Name[$index]] = (string)$cell->Data;
	    		}
	    		$index++;	
	        }
	        
	        $this->rows[] = $rowData;
	    }
	    $this->config = $config;
    }
}
?>
