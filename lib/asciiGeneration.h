#ifndef ASCII_GENERATOR_ASCIIGENERATION_H
#define ASCII_GENERATOR_ASCIIGENERATION_H

void WriteImageToTxt(const char* path, const char* tokens) {
    int width, height, channels;
    unsigned char* image = stbi_load(path, &width, &height, &channels, 0);

    if (!image) {
        std::cerr << "Failed to open image for ascii generation";
        return;
    }

    // Open txt file
    std::ofstream outputText("outputImages/ascii.txt");
    if (!outputText) {
        std::cerr << "Failed to open text file for ascii output";
        return;
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
}

#endif //ASCII_GENERATOR_ASCIIGENERATION_H
