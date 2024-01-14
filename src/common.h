#pragma once

typedef enum {
    OK = 0,

    INVAILD_FILE_EXTENSION = 10,
    INVAILD_FILE = 11,
} Obsidian_Exit_Value;

void ObsidianExit(Obsidian_Exit_Value exit_value);