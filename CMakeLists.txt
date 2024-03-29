cmake_minimum_required(VERSION 3.15)

project(obsidain)

set (CMAKE_CXX_STANDARD 20)

set(OBSIDIAN_HEADER_FILES
    inc/colorize.h
    src/helper/errors.hpp
    src/helper/flags.hpp
    src/lexer/lexer.hpp
    src/common.hpp
    
    src/compiler/value/value.hpp
    src/compiler/debug/debug.hpp
    src/compiler/mem/memory.hpp
    src/compiler/vm/vm.hpp
    src/compiler/chunk.hpp
)

set(OBSIDIAN_SOURCE_FILES
    src/main.cpp
    src/lexer/lexer.cpp
    
    src/compiler/value/value.cpp
    src/compiler/debug/debug.cpp
    src/compiler/mem/memory.cpp
    src/compiler/vm/runVm.cpp
    src/compiler/vm/vm.cpp
    src/compiler/chunk.cpp
)

add_executable(obsidian ${OBSIDIAN_HEADER_FILES} ${OBSIDIAN_SOURCE_FILES})
