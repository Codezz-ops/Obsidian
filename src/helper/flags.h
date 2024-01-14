#include "../common.h"
#include "version.h"

#include <cstring>
#include <fstream>
#include <iostream>

bool isVaildFileExtension(const char *path) {
    const char *fileExtension = ".ob";
    size_t extensionLength = std::strlen(fileExtension);
    size_t pathLength = std::strlen(path);

    if (pathLength >= extensionLength && std::strcmp(path + pathLength - extensionLength, fileExtension) == 0) {
        return true;
    }

    return false;
}

char *readfile(const char *path) {
    if (!isVaildFileExtension(path)) {
        std::cerr << "Error: Invalid file extension for file '" << path << "'" << std::endl;
        ObsidianExit(INVAILD_FILE_EXTENSION);
    }

    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file '" << path << "'" << std::endl;
        ObsidianExit(INVAILD_FILE);
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    char *buffer = new char[size + 1];
    file.read(buffer, size);
    file.close();

    buffer[size] = 0;
    return buffer;
}

void flags(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << " --help\t\t\tPrints this help message" << std::endl;
        std::cout << " --version\t\tPrints the version of the interpreter." << std::endl;
        ObsidianExit(OK);
    }

    if (argc == 2 && strcmp(argv[1], "--version") == 0) {
        std::cout << "Obsidian " << get_Obsidian_version_string() << std::endl;
        ObsidianExit(OK);
    }
}