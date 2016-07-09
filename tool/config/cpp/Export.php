<?php

$config = include("Config.php");

define('TOOL_DIR',     	str_replace('\\', '/', dirname(__FILE__))."/");
define('EXPORT_DIR',    TOOL_DIR.$config["exportDir"]);

/*
todo:
	处理array
	处理key(目前是列表，1键，2键)
*/
error_reporting(E_ALL);
fwrite(STDOUT, "Input export file name: ");
$arr = explode(" ", trim(fgets(STDIN)));
$name = $arr[0];
$file = $name.".xml";

//$res = simplexml_load_file("data/".$file);
$header = simplexml_load_file("header/".$file);

function MakeStruct($key, $val){
	switch ($val) {
		case 'vector':
			$val = "std::vector<".ucfirst($key).">";
			break;
		case 'struct':
			$val = "<".ucfirst($key).">";
			break;
		default:
			break;		
	}
	return "\t".$val." ".$key.";\r\n";
}

$template = isset($arr[1]) ? $arr[1].".php" : "Key.php";
include("template/".$template);

file_put_contents($name.".h", Declaration($header->children(), $name));

$init = "bool Init()\r\n{\r\n";
$init .= "\tstd::string file =\"".$file."\";\r\n";
$init .= "\tstd::string err;\r\n";
$init .= "\tTiXmlDocument doc;\r\n";
$init .= "\tif (doc.LoadFile(file.c_str()))\r\n\t{\r\n";
$init .= "\t\tTiXmlElement* rootElement = doc.RootElement();\r\n";
$init .= "\t\tif (rootElement == NULL) return false;\r\n";
$struct = "";
$element = "";

$source = "\t\tTiXmlElement* curElement = rootElement->FirstChildElement(\"row\");\r\n";
$source .= "\t\twhile (curElement != NULL)\r\n\t\t{\r\n";
$normal = "\t\t\tif (";
$array = "";
foreach ($header->children() as $key => $value) {
	switch ($value) {
		case 'vector':
			$nameElement = $key."Element";
			$element .= "\t\tTiXmlElement* ".$nameElement." = NULL;\r\n";
			$struct .= "\t\tstruct ".ucfirst($key)." _".$key.";\r\n";

			$array .= "\r\n";
			$array .= "\t\t\t".$nameElement."= curElement->FirstChildElement(\"".$key."\");\r\n";
			$array .= "\t\t\tif (".$nameElement." == NULL){ShowError(file.c_str(), \"".$key."\"); return false;}\r\n";
			$array .= "\t\t\t".$nameElement." = ".$nameElement."->FirstChildElement(\"value\");\r\n";
			$array .= "\t\t\twhile (".$nameElement." != NULL)\r\n\t\t\t{\r\n";
			$array .= "\t\t\t\tinfo.".$key.".push_back(_".$key.");\r\n";
			$array .= "\t\t\t\t".$nameElement." = ".$nameElement."->NextSiblingElement(\"value\");\r\n\t\t\t}\r\n";
			break;
				
		default:
			$normal .= "!GetSubNodeValue(curElement, \"".$key."\", info.".$key.", err) ||\r\n\t\t\t\t";
			break;
	}
}

$source .= substr($normal, 0, -9).")\r\n";
$source .= "\t\t\t{\r\n";
$source .= "\t\t\t\tShowError(file.c_str(), err.c_str());\r\n";
$source .= "\t\t\t\treturn false;\r\n";
$source .= "\t\t\t}\r\n";

$source .= $array;
$source .= "\t\t\tcurElement = curElement->NextSiblingElement(\"row\");\r\n\t\t}\r\n";
$source .= "\t}\r\n\telse\r\n\t{\r\n";
$source .= "\t\tShowError(file.c_str(), \"can not load the file\");\r\n";
$source .= "\t\treturn false;\r\n";
$source .= "\t}\r\n";
$source .= "\treturn true;\r\n}";

file_put_contents($name.".cpp", $init.$struct.$element.$source);

echo "export ok!\r\n";


?>