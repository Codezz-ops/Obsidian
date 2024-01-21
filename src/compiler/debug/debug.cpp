// writen by TheDevConnor on 2023-01-20
#include "debug.hpp"
#include "../value/value.hpp"

#include <cstdint>
#include <functional>
#include <iostream>
#include <unordered_map>

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

int Debug::constantInstruction(const char *name, Chunk *chunk, int offset) {
  uint8_t constant = chunk->code[offset + 1];
  std::cout << name << " " << constant << " '";
  ClassValue::printValue(chunk->constants.values[constant]);
  std::cout << "'" << std::endl;
  return offset + 2;
}

int Debug::dissassembleInstruction(Chunk *chunk, int offset) {
  std::cout << std::hex << offset << " ";

  if (offset > 0 && chunk->lines[offset] == chunk->lines[offset - 1]) {
    std::cout << "   | ";
  } else {
    std::cout << std::dec << chunk->lines[offset] << " ";
  }

  uint8_t instruction = chunk->code[offset];

  std::unordered_map<uint8_t, std::function<int()>> opcodes = {
      {OpCodes::OPConstant,
       [&]() { return constantInstruction("OPConstant", chunk, offset); }},
      {OpCodes::OPNegate,
       [&]() { return simpleInstruction("OPNegate", offset); }},
      {OpCodes::OPReturn,
       [&]() { return simpleInstruction("OPReturn", offset); }},
  };

  if (opcodes.find(instruction) != opcodes.end()) {
    return opcodes[instruction]();
  }

  std::cout << "Unknown opcode " << instruction << std::endl;
  return offset + 1;
}
