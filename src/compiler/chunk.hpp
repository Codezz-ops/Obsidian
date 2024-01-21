// writen by TheDevConnor on 2023-01-20
#pragma once

#include "value/value.hpp"

#include <cstdint>

enum OpCodes {
  OPConstant,
  OPNegate,
  OPReturn,
};

struct Chunk {
  ValueArray constants;
  uint8_t *code;
  int capacity;
  int *lines;
  int count;
};

class ChunkClass {
public:
  static void writeChunk(Chunk *chunk, uint8_t byte, int line);
  static int addConstant(Chunk *chunk, Value value);
  static void initChunk(Chunk *chunk);
  static void freeChunk(Chunk *chunk);

private:
};
