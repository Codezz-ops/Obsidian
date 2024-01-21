// writen by TheDevConnor on 2021-03-28
#include "debug.hpp"

#include <functional>
#include <iostream>

void Debug::dissassembleChunk(Chunk *chunk, const char *name) {
    std::cout << "== " << name << " ==" << std::endl;

    for (int offset = 0; offset < chunk->count;) {
        offset = dissassembleInstruction(chunk, offset);
    }
}

int Debug::simpleInstruction(const char *name, int offset) {
    std::cout << name << std::endl;
    return offset + 1;
}

int Debug::dissassembleInstruction(Chunk *chunk, int offset) {
    std::cout << offset << " ";

    uint8_t instruction = chunk->code[offset];
    std::function<uint8_t(const uint8_t)> opcodeFunctions[] = {
        [](const uint8_t offset) -> uint8_t {return simpleInstruction("OPReturn", offset);},
    };

    auto opcodeFunction = opcodeFunctions[static_cast<OpCodes>(instruction)];

    if (opcodeFunction == nullptr) {
        std::cout << "Unknown opcode " << instruction << std::endl;
        return offset + 1;
    }

    return opcodeFunction(offset);
}