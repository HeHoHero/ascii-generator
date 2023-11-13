#include <iostream>
#include <fstream>

#include "../lib/CheckFolder.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

int WriteImageToTxt(const char* path, const char* tokens) {
    int width, height, channels;
    unsigned char* image = stbi_load(path, &width, &height, &channels, 0);

    if (!image) {
        std::cerr << "Failed to open image for ascii generation";
        return 1;
    }

    // Open txt file
    std::ofstream outputText("outputImages/ascii.txt");
    if (!outputText) {
        std::cerr << "Failed to open text file for ascii output";
        return 1;
    }

    int tokenAmount = strlen(tokens) - 1;
    for (int y = 0; y < height; y++) {
        for (int x= 0; x < width; x++) {
            int pixelValue = static_cast<int>(image[(y * width + x) * channels]);

            int index = static_cast<int>((static_cast<double>(pixelValue) / 255.0) * (tokenAmount - 1));
            outputText << tokens[index];
        }
        outputText << std::endl;
    }

    // Clean up
    outputText.close();
    stbi_image_free(image);

    return 0;
}

int main() {
    if (FolderExists() == 1) {
        std::cerr << "Could not find image dump folder" << std::endl;
        return 1;
    }

    // Get user input
    std::string path;
    std::cout << "Trying to find previous image..." << std::endl;
    std::cin >> path;

    // Ascii generation
    char* tokens = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
    WriteImageToTxt(path.c_str(), tokens);

    return 0;
}