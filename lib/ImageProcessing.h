#ifndef ASCII_GENERATOR_IMAGEPROCESSING_H
#define ASCII_GENERATOR_IMAGEPROCESSING_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

#include <curl/curl.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

size_t WriteCallBack(void* contents, size_t size, size_t nmemb, FILE* file) {
    return fwrite(contents, size, nmemb, file);
}

void PullImage() {
    // init cURL
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize cURL" << std::endl;
        return;
    }

    // Get user URL
    std::string userUrl;
    std::cout << "Please enter a valid URL: " << std::endl;
    std::cin >> userUrl;

    // Convert string to char*
    const char* url = userUrl.c_str();

    // Set up file
    const char* filename = "image.png";
    FILE* imageFile = fopen(filename, "wb");
    if (!imageFile) {
        std::cerr << "Failed to open file for writing" << std::endl;
        curl_easy_cleanup(curl);
        return;
    }

    // Set cURL options
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, imageFile);

    // Perform HTTP request
    CURLcode res = curl_easy_perform(curl);

    // Clean up
    fclose(imageFile);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "cURL request failed: " << curl_easy_strerror(res) << std::endl;
        remove(filename);
        return;
    }
}

void UpImageContrast(const float contrast, const int brightness) {
    // Load the source image
    const char* sourcePath = "image.png";
    int width, height, channels;
    unsigned char* sourceData = stbi_load(sourcePath, &width, &height, &channels, 0);

    if (!sourceData) {
        std::cerr << "Error loading source image." << std::endl;
        return;
    }

    // Convert image to 3D array [y][x][r, g, b, a]
    unsigned char*** imageArray = new unsigned char**[height];
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
    unsigned char* destinationData = new unsigned char[width * height * channels];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            for (int c = 0; c < channels; c++) {
                destinationData[y * width * channels + x * channels + c] = imageArray[y][x][c];
            }
        }
    }

    // Save image data to png
    const char* destPath = "imageOut.png";
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
}

#endif //ASCII_GENERATOR_IMAGEPROCESSING_H
