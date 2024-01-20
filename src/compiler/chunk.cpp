// written by TheDevConnor
#include "chunk.hpp"
#include "mem/memory.hpp"

#include <cstdint>
#include <memory>

void ChunkClass::initChunk(std::unique_ptr<Chunk> chunk) {
  chunk->code = nullptr;
  chunk->capacity = 0;
  chunk->count = 0;
}

void ChunkClass::freeChunk(std::unique_ptr<Chunk> chunk) {
  Memory::freeArray(chunk->code.get(), chunk->capacity);
  initChunk(std::move(chunk));
}

void ChunkClass::writeChunk(std::unique_ptr<Chunk>& chunk, uint8_t byte) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    auto newCode = Memory::GrowArray<uint8_t>(chunk->code, oldCapacity, chunk->capacity);
    chunk->code = std::move(newCode);
  }

  chunk->code.get()[chunk->count] = byte;
  chunk->count++;
}
