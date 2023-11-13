#include <iostream>
#include <algorithm>

#include "../lib/CheckFolder.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

int GrayScaleImage(const char* imagePath) {
    int width, height, channels;
    unsigned char *image_data = stbi_load(imagePath, &width, &height, &channels, 0);

    if (!image_data) {
        std::cerr << "Failed to open image for gray scale" << std::endl;
        return 1;
    }

    // Original image has 3 to 4 channels
    // While gray scale only has one
    int grayscale_channels = 1;

    auto *grayscale_data = new unsigned char[width * height * grayscale_channels];

    for (int i = 0; i < width * height; ++i) {
        // Convert to grayscale
        grayscale_data[i] = static_cast<unsigned char>(
                0.2126 * image_data[i * channels] +
                0.7152 * image_data[i * channels + 1] +
                0.0722 * image_data[i * channels + 2]
        );
    }

    // Save image data to png
    stbi_write_jpg("outputImages/imageOutGrayScale.jpg", width, height, grayscale_channels, grayscale_data, 100);

    // Clean up memory
    stbi_image_free(image_data);
    delete[] grayscale_data;

    return 0;
}

int main() {
    if (FolderExists() == 1) {
        std::cerr << "Could not find image dump folder" << std::endl;
        return 1;
    }

    std::string path;
    std::cout << "Trying to find previous image..." << std::endl;
    std::cin >> path;

    // Gray scale image
    GrayScaleImage(path.c_str());

    return 0;
}