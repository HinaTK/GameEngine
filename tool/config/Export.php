<?php

$configFile = isset($argv[1]) ? $argv[1] : "Config.php";
$config = include($configFile);

define('TOOL_DIR',     	str_replace('\\', '/', dirname(__FILE__))."/");
define('PROJECT_DIR',	TOOL_DIR.$config["project"]);
define('EXPORT_DIR',    TOOL_DIR.$config["exportDir"]);
define('TEMPLATE_DIR', 	PROJECT_DIR.$config["templateDir"]);
define('RECORD_FILE', 	"Record.php");
define('FILTER_SHEET', 	"@");

include(PROJECT_DIR."Parser.php");

error_reporting(E_ALL);

function InitRecord($dir)
{
	$record = include(RECORD_FILE);
	return $record ? $record : array();
}

function WriteRecord($record)
{
	file_put_contents(RECORD_FILE, "<?php \r\nreturn ".var_export($record, TRUE)."\r\n?>");
}

$res = array();
function GetSheetByName($name){
	global $res;
	foreach ($res->Worksheet as $sheet) {
		if ($sheet->attributes('ss', true)->Name == $name) {
			return $sheet;
		}	
	}
	return false;
}

function Export($dir, $record){
	global $config;
	global $res;
	foreach ($dir as $val) {
		$path = $val["path"];
		$file = $val["file"];
		$oldTime = isset($record[$file]) ? $record[$file] : 0;
		$newTime = filemtime($path);
		if ($oldTime != $newTime) {
			$record[$file] = $newTime;
			$res = simplexml_load_file($path);
			foreach ($res->Worksheet as $sheet) {
				if (substr($sheet->attributes('ss', true)->Name, 0, 1) != FILTER_SHEET) {
					//Parse($sheet);
					$parser = new Parser($config, $sheet);
					$parser->Parse();
				}
			}
		}
	}
	return $record;
}

$dir = array();
$dirHandle = opendir(EXPORT_DIR);
while($file = readdir($dirHandle))
{
	$path = EXPORT_DIR.$file;
	if (is_file($path)) {
		$dir[] = array("file" => basename($file,".xml"), "path" => $path);
	}
}

$record = array();
if (!isset($config["all"]) or !$config["all"]) {
	$record = InitRecord($dir);
}
$record = Export($dir, $record);
WriteRecord($record);

echo "Export OK!\r\n";
?>