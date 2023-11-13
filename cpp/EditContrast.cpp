#include <iostream>
#include <algorithm>

#include "../lib/CheckFolder.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

int UpImageContrast(const float contrast, const float brightness) {
    // Load the source image
    const char* sourcePath = "outputImages/image.png";
    int width, height, channels;
    unsigned char* sourceData = stbi_load(sourcePath, &width, &height, &channels, 0);

    if (!sourceData) {
        std::cerr << "Failed to open image for contrast/brightness editing" << std::endl;
        return 1;
    }

    // Convert image to 3D array [y][x][r, g, b, a]
    auto*** imageArray = new unsigned char**[height];
    for (int y = 0; y < height; y++) {
        imageArray[y] = new unsigned char*[width];
        for (int x = 0; x < width; x++) {
            imageArray[y][x] = new unsigned char[channels];
            for (int c = 0; c < channels; c++) {
                // Update contrast
                auto currentValue = static_cast<float>(sourceData[y * width * channels + x * channels + c]);
                int updatedValue = (int)(contrast * (currentValue - 128) + 128 + (float)brightness);

                // Since std::clamp won't work for some reason, do it manually
                if (updatedValue > 255) {
                    updatedValue = 255;
                } else if (updatedValue < 0) {
                    updatedValue = 0;
                }

                imageArray[y][x][c] = updatedValue;
            }
        }
    }

    // Convert 3D array back into image
    auto* destinationData = new unsigned char[width * height * channels];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channels; c++) {
                destinationData[y * width * channels + x * channels + c] = imageArray[y][x][c];
            }
        }
    }

    // Save image data to png
    const char* destPath = "outputImages/imageOutContrast.png";
    stbi_write_png(destPath, width, height, channels, destinationData, width * channels);

    // Clean up
    stbi_image_free(sourceData);
    delete[] destinationData;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            delete[] imageArray[y][x];
        }
        delete[] imageArray[y];
    }
    delete[] imageArray;

    return 0;
}

int main() {
    if (FolderExists() == 1) {
        std::cerr << "Could not find image dump folder" << std::endl;
        return 1;
    }

    // Get user input
    float contrast, brightness;
    std::cout << "contrast: <br>" << std::endl;
    std::cin >> contrast;
    std::cout << "brightness: <br>" << std::endl;
    std::cin >> brightness;

    // Up contrast / brightness
    UpImageContrast(contrast, brightness);

    return 0;
}