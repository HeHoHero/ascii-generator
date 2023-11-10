#ifndef ASCII_GENERATOR_DITHERING_H
#define ASCII_GENERATOR_DITHERING_H

// Find closest palette color
int ClosestPaletteColor(int pixelValue, int tokenAmount) {
    int paletteColors[tokenAmount];
    for (int i = 0; i < tokenAmount; i++) {
        paletteColors[i] = static_cast<int>(255 * i / (tokenAmount - 1));
    }

    int closestColor = paletteColors[0];
    int minDiff = std::abs(pixelValue - paletteColors[0]);

    for (int i = 1; i < tokenAmount; i++) {
        int diff = std::abs(pixelValue - paletteColors[i]);
        if (diff < minDiff) {
            minDiff = diff;
            closestColor = paletteColors[i];
        }
    }

    return closestColor;
}

// Floyd-Steinberg dithering
void FSDithering(int tokenAmount, int threshold) {
    // Load the source image
    const char* path = "outputImages/imageOutGrayScale.jpg";
    int width, height, channels;
    unsigned char* image = stbi_load(path, &width, &height, &channels, 0);

    if (!image) {
        std::cerr << "Failed to open image for dithering" << std::endl;
        return;
    }

    // Convert to grayscale
    auto* grayscaleImage = new unsigned char[width * height];

    for (int i = 0; i < width * height; i++) {
        grayscaleImage[i] = static_cast<unsigned char>(
                0.2126 * image[i * channels] +
                0.7152 * image[i * channels + 1] +
                0.0722 * image[i * channels + 2]
        );
    }

    // The actual dithering
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int oldPixel = static_cast<int>(grayscaleImage[y * width + x]);
            int newPixel = ClosestPaletteColor(oldPixel, tokenAmount);
            newPixel = std::clamp(newPixel, 0, 255);
            grayscaleImage[y * width + x] = newPixel;

            int quant_error = oldPixel - newPixel;

            if (quant_error > threshold) {
                if (x + 1 < width) {
                    grayscaleImage[y * width + (x + 1)] += quant_error * 7 / 16;
                    grayscaleImage[y * width + (x + 1)] = std::clamp(static_cast<int>(grayscaleImage[y * width + (x + 1)]), 0, 255);
                }
                if (y + 1 < height) {
                    grayscaleImage[(y + 1) * width + x] += quant_error * 5 / 16;
                    grayscaleImage[(y + 1) * width + x] = std::clamp(static_cast<int>(grayscaleImage[(y + 1) * width + x]), 0, 255);
                    if (x - 1 >= 0) {
                        grayscaleImage[(y + 1) * width + (x - 1)] += quant_error * 3 / 16;
                        grayscaleImage[(y + 1) * width + (x - 1)] = std::clamp(static_cast<int>(grayscaleImage[(y + 1) * width + (x - 1)]), 0, 255);
                    }
                    if (x + 1 < width) {
                        grayscaleImage[(y + 1) * width + (x + 1)] += quant_error * 1 / 16;
                        grayscaleImage[(y + 1) * width + (x + 1)] = std::clamp(static_cast<int>(grayscaleImage[(y + 1) * width + (x + 1)]), 0, 255);
                    }
                }
            }
        }
    }

    // Save dithered image data into jpg
    const char* outputPath = "outputImages/imageOutDithered.jpg";
    stbi_write_jpg(outputPath, width, height, 1, grayscaleImage, 100);

    // Clean up
    stbi_image_free(image);
    delete[] grayscaleImage;
}

#endif //ASCII_GENERATOR_DITHERING_H
