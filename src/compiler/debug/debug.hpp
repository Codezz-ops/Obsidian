// writen by TheDevConnor on 2023-01-20
#pragma once

#include "../chunk.hpp"

class Debug {
public:
  static void dissassembleChunk(Chunk *chunk, const char *name);
  static int dissassembleInstruction(Chunk *chunk, int offset);

private:
  static int constantInstruction(const char *name, Chunk *chunk, int offset);
  static int simpleInstruction(const char *name, int offset);
};
