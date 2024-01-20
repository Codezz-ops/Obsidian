// writen by TheDevConnor on 2021-03-28
#pragma once

#include <cstdint>
#include <memory>

enum OpCodes {
  OPReturn,
};

struct Chunk {
  uint8_t *code;
  int capacity;
  int count;
};

class ChunkClass {
public:
  static void writeChunk(Chunk *chunk, uint8_t byte);
  static void initChunk(Chunk* chunk);
  static void freeChunk(Chunk* chunk);

  ~ChunkClass() = delete;
private:
};
