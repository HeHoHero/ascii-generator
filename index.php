<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>Ascii++</title>
</head>

<body>
    <!-- Image regular -->
    <?php
    if (is_dir('actions/outputImages')) {
        echo "<img src='actions/outputImages/image.png' alt='your image' class='image'>";
    }
    ?>

    <form action="actions/ImagePull.php" method="get">
        <label>
            <input type="text" name="link">
        </label>

        <input type="submit">
    </form>

    <!-- Image contrast -->
    <?php
    if (is_dir('actions/outputImages')) {
        echo "<img src='actions/outputImages/imageOutContrast.png' alt='your image' class='image'>";
    }
    ?>

    <form action="actions/Contrast.php" method="get">
        <label>
            <input type="text" name="contrast">
        </label>
        <label>
            <input type="text" name="brightness">
        </label>

        <input type="submit">
    </form>

    <!-- Image gray scale -->
    <?php
    if (is_dir('actions/outputImages')) {
        echo "<img src='actions/outputImages/imageOutGrayScale.jpg' alt='your image' class='image'>";
    }
    ?>

    <form action="actions/GrayScale.php" method="get">
        <label>
            Enable contrast: <input type="checkbox" name="contrast">
        </label>

        <input type="submit">
    </form>

    <!-- Image dithering -->
    <?php
    if (is_dir('actions/outputImages')) {
        echo "<img src='actions/outputImages/imageOutGrayScale.jpg' alt='your image' class='image'>";
    }
    ?>

    <form action="actions/GrayScale.php" method="get">
        <label>
            Enable contrast: <input type="checkbox" name="contrast">
        </label>

        <input type="submit">
    </form>

    <button onclick="RefreshImage()">Refresh Images</button>

    <script>
        const img = document.querySelectorAll('.image');

        function RefreshImage() {
            const timestamp = new Date().getTime();

            for (let i = 0; i < img.length; i++) {
                img[i].src = `${img[i].src}?t=${timestamp}`;
            }
        }

        RefreshImage();
    </script>
</body>
</html>