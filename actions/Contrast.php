<?php
$path = __DIR__ . "/../exe/EditContrast.exe";

$process = proc_open($path, [
    0 => ['pipe', 'r'], // stdin
    1 => ['pipe', 'w'], // stdout
    2 => ['pipe', 'w']  // stderr
], $pipes);

if (is_resource($process)) {
    $contrast = $_GET['contrast'];
    $brightness = $_GET['brightness'];

    // Input link
    fwrite($pipes[0], $contrast . "\n");
    fwrite($pipes[0], $brightness . "\n");
    fclose($pipes[0]);

    // Read output
    $output = stream_get_contents($pipes[1]);
    fclose($pipes[1]);

    // Read errors
    $error = stream_get_contents($pipes[2]);
    fclose($pipes[2]);

    $returnValue = proc_close($process);

    echo "Output: " . $output . "<br>";
    echo "Error: " . $error . "<br>";
    echo "Return value: " . $returnValue;
} else {
    echo "Failed to open process";
}

header('Location: ' . $_SERVER['HTTP_REFERER']);