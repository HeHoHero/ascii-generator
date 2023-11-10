#include <iostream>
#include "lib/include.h"
#include "lib/ImageProcessing.h"
#include "lib/dithering.h"
#include "lib/asciiGeneration.h"

int main() {
    char tokens[] = " .'`^\",:;Il!i><~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

    PullImage();
    std::cout << "Image was saved successfully" << std::endl << std::endl;

    char input;
    std::cout << "Enable contrast (y, n): " << std::endl;
    std::cin >> input;

    if (input == 'y') {
        float contrast;
        int brightness;

        std::cout << "Insert contrast: " << std::endl;
        std::cin >> contrast;
        std::cout << "Insert brightness: " << std::endl;
        std::cin >> brightness;

        UpImageContrast(contrast, brightness);

        std::cout << "Image has been saved with added contrast and brightness" << std::endl << std::endl;

        GrayScaleImage("outputImages/imageOutContrast.png");
    } else {
        GrayScaleImage("outputImages/image.png");
    }

    std::string finalImagePath = "outputImages/imageOutGrayScale.jpg";

    std::cout << "Image has been saved with gray scale" << std::endl << std::endl;

    std::cout << "Add dithering (y, n): " << std::endl;
    std::cin >> input;

    if (input == 'y') {
        int threshold = 128;

        std::cout << "Enter threshold: " << std::endl;
        std::cin >> threshold;

        FSDithering(sizeof(tokens) / sizeof(tokens[0]), threshold);

        finalImagePath = "outputImages/imageOutDithered.jpg";
    }

    WriteImageToTxt(finalImagePath.c_str(), tokens);

    return 0;
}
