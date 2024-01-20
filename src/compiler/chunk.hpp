// Written by the DevConnor
#pragma once

#include <cstdint>
#include <memory>

enum OpCodes {
  OPReturn,
};

struct Chunk {
  std::unique_ptr<uint8_t[]> code;
  int capacity;
  int count;
};

class ChunkClass {
public:
  static void initChunk(std::unique_ptr<Chunk> chunk);
  static void freeChunk(std::unique_ptr<Chunk> chunk);
  static void writeChunk(std::unique_ptr<Chunk>& chunk, uint8_t byte);

  ~ChunkClass() = delete;
private:
};