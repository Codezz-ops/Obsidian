// writen by TheDevConnor on 2021-03-28
#include "chunk.hpp"
#include "mem/memory.hpp"

#include <cstdint>
#include <memory>

void ChunkClass::initChunk(Chunk* chunk) {
  chunk->code = nullptr;
  chunk->capacity = 0;
  chunk->count = 0;
}

void ChunkClass::freeChunk(Chunk* chunk) {
  Memory::freeArray<uint8_t>(chunk->code, chunk->capacity);
  initChunk(chunk);
}

void ChunkClass::writeChunk(Chunk* chunk, uint8_t byte) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = Memory::GrowCapacity(oldCapacity);
    chunk->code = Memory::GrowArray<uint8_t>(chunk->code, oldCapacity, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;
  chunk->count++;
}
