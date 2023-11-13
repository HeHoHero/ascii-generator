#ifndef ASCII_GENERATOR_CHECKFOLDER_H
#define ASCII_GENERATOR_CHECKFOLDER_H

#include <filesystem>
#include <iostream>

// Check if dump folder exists
int FolderExists() {
    namespace fs = std::filesystem;
    std::string path = "outputImages";
    for (int i = 0; i < 3; i++) {
        if (fs::exists(path) && fs::is_directory(path)) {
            std::cout << "Found image dump folder <br>" << std::endl;
            return 0;
        } else {
            std::cout << "Could not find image dump folder. <br>Attempt " << i + 1 << " to create folder... <br>" << std::endl;
            try {
                fs::create_directory(path);
            } catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "Failed to create image dump: " << e.what() << "<br>" << std::endl;
                return 1;
            }
        }
    }

    return 0;
}

#endif //ASCII_GENERATOR_CHECKFOLDER_H
