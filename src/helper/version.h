#pragma once

#include <string>

#define OBSIDIAN_VERSION {OBSIDIAN_MAJOR_VERSION, OBSIDIAN_MINOR_VERSION, OBSIDIAN_PATCH_LEVEL}

const int OBSIDIAN_MAJOR_VERSION = 0;
const int OBSIDIAN_MINOR_VERSION = 0;
const int OBSIDIAN_PATCH_LEVEL = 1;


struct Obsidian_version {
    int major;
    int minor;
    int patch;
};

std::string get_Obsidian_version_string() {
    Obsidian_version v = OBSIDIAN_VERSION;
    return std::to_string(v.major) + '.' + std::to_string(v.minor) + '.' + std::to_string(v.patch);
}