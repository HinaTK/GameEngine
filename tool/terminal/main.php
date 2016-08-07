<?php
$post = "jiaming";
$length = strlen($post);
$fp = fsockopen("127.0.0.1",12345,$errno,$errstr,10) or exit($errstr."--->".$errno);
$header  = "GET / HTTP/1.1\r\n";
$header .= "Content-Length: ".$length."\r\n\r\n";
$header .= $post."\r\n";
fputs($fp,$header);
$inheader = 1;
while (!feof($fp)) {
    $line = fgets($fp,1024); //去除请求包的头只显示页面的返回数据
    if ($inheader && ($line == "\n" || $line == "\r\n")) {
         $inheader = 0;
    }
    if ($inheader == 0) {
      echo $line;
    }
}

fclose($fp);
?>