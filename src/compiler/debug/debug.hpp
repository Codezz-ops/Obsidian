// writen by TheDevConnor on 2021-03-28
#pragma once

#include <unordered_map>

#include "../chunk.hpp"

class Debug {
public:
    static void dissassembleChunk(Chunk *chunk, const char *name);

private:
    static int dissassembleInstruction(Chunk *chunk, int offset);
    static int simpleInstruction(const char *name, int offset);
};