#include <iostream>
#include <string>
#include <curl/curl.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "../lib/CheckFolder.h"

size_t WriteCallBack(void* contents, size_t size, size_t nmemb, FILE* file) {
    return fwrite(contents, size, nmemb, file);
}
int PullImage(const std::string& userUrl) {
    // init cURL
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize cURL" << std::endl;
        return 1;
    }

    // Convert string to char*
    const char* url = userUrl.c_str();

    // Set up file
    const char* filename = "outputImages/image.png";
    FILE* imageFile = fopen(filename, "wb");
    if (!imageFile) {
        std::cerr << "Failed to open file for writing" << std::endl;
        curl_easy_cleanup(curl);
        return 1;
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
        return 1;
    }

    return 0;
}

int main() {
    if (FolderExists() == 1) {
        std::cerr << "Could not find image dump folder" << std::endl;
        return 1;
    }

    // Get user URL
    std::string userUrl;
    std::cout << "Please enter a valid URL: <br>" << std::endl;
    std::cin >> userUrl;

    // Pull the image
    PullImage(userUrl);

    return 0;
}