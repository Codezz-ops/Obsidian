// writen by TheDevConnor on 2023-01-20
#include "chunk.hpp"
#include "mem/memory.hpp"
#include "value/value.hpp"

#include <cstdint>

void ChunkClass::initChunk(Chunk *chunk) {
  ClassValue::initValueArray(&chunk->constants);
  chunk->code = nullptr;
  chunk->lines = nullptr;
  chunk->capacity = 0;
  chunk->count = 0;
}

void ChunkClass::freeChunk(Chunk *chunk) {
  Memory::freeArray<uint8_t>(chunk->code, chunk->capacity);
  Memory::freeArray<int>(chunk->lines, chunk->capacity);
  ClassValue::freeValueArray(&chunk->constants);
  initChunk(chunk);
}

void ChunkClass::writeChunk(Chunk *chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = Memory::GrowCapacity(oldCapacity);
    chunk->code =
        Memory::GrowArray<uint8_t>(chunk->code, oldCapacity, chunk->capacity);
    chunk->lines =
        Memory::GrowArray<int>(chunk->lines, oldCapacity, chunk->capacity);
  }

  chunk->code[chunk->count] = byte;
  chunk->lines[chunk->count] = line;
  chunk->count++;
}

int ChunkClass::addConstant(Chunk *chunk, Value value) {
  ClassValue::writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}
