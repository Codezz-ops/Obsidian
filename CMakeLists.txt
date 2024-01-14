cmake_minimum_required(VERSION 3.15)

project(obsidain)

set (CMAKE_CXX_STANDARD 20)

set(OBSIDIAN_HEADER_FILES
    inc/colorize.h
    src/helper/errors.h
    src/helper/flags.h
    src/helper/version.h
    src/lexer/tokens.h
    src/common.h
)

set(OBSIDIAN_SOURCE_FILES
    src/main.cc
    src/common.cc
    src/lexer/lexer.cc
)

add_executable(obsidian ${OBSIDIAN_HEADER_FILES} ${OBSIDIAN_SOURCE_FILES})

# For Linux
# cmake -S . -B build 
# cmake --build build
# ./build/obsidian

# For Windows
# cmake -S . -B build -G "MinGW Makefiles"
# cmake --build build
# build\obsidian.exe