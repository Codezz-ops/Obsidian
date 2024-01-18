#include "../common.h"

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
        Exit(ExitValue::INVALID_FILE_EXTENSION);
    }

    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Could not open file '" << path << "'" << std::endl;
        Exit(ExitValue::INVALID_FILE);
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

void printHelpMessage(const char* programName) {
    std::cout << "Usage: " << programName << " [options]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << " --help\t\t\tPrints this help message" << std::endl;
    std::cout << " --version\t\tPrints the version of the interpreter." << std::endl;
}

void flags(int argc, char *argv[]) {
    if (argc == 2) {
        if (strcmp(argv[1], "--help") == 0) {
            printHelpMessage(argv[0]);
            Exit(ExitValue::OK);
        }

        if (strcmp(argv[1], "--version") == 0) {
            std::cout << "Obsidian " << ObsidianVersion << std::endl;
            Exit(ExitValue::OK);
        }
    }
}