<?php
$path = __DIR__ . "/../exe/GrayScale.exe";

$process = proc_open($path, [
    0 => ['pipe', 'r'], // stdin
    1 => ['pipe', 'w'], // stdout
    2 => ['pipe', 'w']  // stderr
], $pipes);

if (is_resource($process)) {
    $link = 'outputImages/image.png';
    if (file_exists('outputImages/imageOutContrast.png') && isset($_GET['contrast'])) {
        $link = $_GET['contrast'] === 'on' ? 'outputImages/imageOutContrast.png' : 'outputImages/image.png';
    }

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

echo $link;

header('Location: ../?contrast=' . $_GET['contrast']);