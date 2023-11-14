<?php
$path = __DIR__ . "/../exe/ImagePull.exe";

$process = proc_open($path, [
    0 => ['pipe', 'r'], // stdin
    1 => ['pipe', 'w'], // stdout
    2 => ['pipe', 'w']  // stderr
], $pipes);

if (is_resource($process)) {
    $link = $_GET['link'];

    // Input link
    fwrite($pipes[0], $link);
    fclose($pipes[0]);

    // Read output
    $output = stream_get_contents($pipes[1]);
    fclose($pipes[1]);

    // Read errors
    $error = stream_get_contents($pipes[2]);
    fclose($pipes[2]);

    $returnValue = proc_close($process);

    echo "Error: " . $error . "<br>";
    echo "Return value: " . $returnValue;
} else {
    echo "Failed to open process";
}

header('Location: ' . $_SERVER['HTTP_REFERER']);