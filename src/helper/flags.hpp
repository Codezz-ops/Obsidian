#include "../common.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>

constexpr size_t FILE_EXTENSION_LENGTH = 3;

bool isValidFileExtension(const char* path) {
    if (!path || path[0] == '\0') {
        return false;
    }

    const std::string fileExtension = ".ob";
    const size_t extensionLength = fileExtension.length();
    const size_t pathLength = std::strlen(path);

    if (pathLength >= extensionLength &&
        std::strcmp(path + pathLength - extensionLength, fileExtension.c_str()) == 0) {
        return true;
    }

    return false;
}

std::unique_ptr<char[]> readfile(const char *path) {
    if (!isValidFileExtension(path)) {
        std::cerr << "Error: Invalid file extension for file '" << path << "'" << std::endl;
        Exit(ExitValue::INVALID_FILE_EXTENSION);
    }

    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << path << "'" << std::endl;
        Exit(ExitValue::INVALID_FILE);
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::unique_ptr<char[]> buffer(new (std::nothrow) char[size + 1]);
    if (!buffer) {
        std::cerr << "Error: Memory allocation failed" << std::endl;
        Exit(ExitValue::MEMORY_ALLOCATION_FAILURE);
    }
    file.read(buffer.get(), size);
    buffer[size] = '\0';

    return buffer;
}


void printHelpMessage(const std::string& programName) {
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