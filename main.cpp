#include <iostream>
#include "lib/ImageProcessing.h"

int main() {
    PullImage();
    std::cout << "Image was saved successfully" << std::endl << std::endl;

    char input;
    std::cout << "Enable contrast (y, n): " << std::endl;
    std::cin >> input;

    if (input == 'y') {
        float contrast;
        int brightness;

        std::cout << "Insert contrast (0, 1): " << std::endl;
        std::cin >> contrast;
        std::cout << "Insert brightness (>=0, <=255): " << std::endl;
        std::cin >> brightness;

        UpImageContrast(contrast, brightness);

        std::cout << "Image has been saved with added contrast and brightness" << std::endl;
    } else {
        std::cout << "oki" << std::endl;
    }

    return 0;
}
