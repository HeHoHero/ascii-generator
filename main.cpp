#include <iostream>
#include "lib/include.h"
#include "lib/ImageProcessing.h"
#include "lib/dithering.h"

int main() {
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

        std::cout << "Image has been saved with added contrast and brightness" << std::endl;

        GrayScaleImage("outputImages/imageContrastOut.png");
    } else {
        GrayScaleImage("outputImages/image.png");
    }

    std::cout << "Image has been saved with gray scale" << std::endl;

    std::cout << "Stating dithering" << std::endl;
    FSDithering(16);
    std::cout << "Finished dithering" << std::endl;

    return 0;
}
