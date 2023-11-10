#ifndef ASCII_GENERATOR_IMAGEPROCESSING_H
#define ASCII_GENERATOR_IMAGEPROCESSING_H

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
    const char* filename = "outputImages/image.png";
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
    const char* sourcePath = "outputImages/image.png";
    int width, height, channels;
    unsigned char* sourceData = stbi_load(sourcePath, &width, &height, &channels, 0);

    if (!sourceData) {
        std::cerr << "Failed to open image for contrast/brightness editing" << std::endl;
        return;
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
}

void GrayScaleImage(const char* imagePath) {
    int width, height, channels;
    unsigned char *image_data = stbi_load(imagePath, &width, &height, &channels, 0);

    if (!image_data) {
        std::cout << "Failed to open image for gray scale" << std::endl;
        return;
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
}

#endif //ASCII_GENERATOR_IMAGEPROCESSING_H
