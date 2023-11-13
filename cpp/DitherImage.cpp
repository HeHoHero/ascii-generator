#include <iostream>
#include <algorithm>

#include "../lib/CheckFolder.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "../lib/dithering.h"

int main() {
    if (FolderExists() == 1) {
        std::cerr << "Could not find image dump folder" << std::endl;
        return 1;
    }

    // Get user input
    std::string path;
    std::cout << "Trying to find previous image..." << std::endl;
    std::cin >> path;

    int dithering;
    std::cout << "Please select dithering method: " << std::endl;
    std::cin >> dithering;

    // Dithering
    switch (dithering) {
        case 0:
        default:
            char answer;
            std::cout << "Do you want to enable a custom char set?: (y/n)" << std::endl;
            std::cin >> answer;

            std::string tokens = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
            if (answer == 'y') {
                std::cout << "Enter tokens from least to most dense: " << std::endl;
                std::cin >> tokens;
            }

            int threshold;
            std::cout << "Enter dithering threshold: " << std::endl;
            std::cin >> threshold;

            FSDithering(path.c_str(), (int)tokens.length(), threshold);

            break;
        // Add more as needed
    }

    return 0;
}
