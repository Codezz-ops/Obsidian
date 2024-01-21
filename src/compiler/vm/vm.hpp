// written by TheDevConnor 2024-01-21
#pragma once

#include "../../common.hpp"
#include "../chunk.hpp"
#include <cstdint>

constexpr int STACK_MAX = 256;

struct VM {
  Value stack[STACK_MAX];
  Value *stackTop;
  Chunk *chunk;
  uint8_t *ip;
};

inline VM vm;

class ClassVM {
public:
  static void initVm();
  static void freeVm();

  static ExitValue interpret(Chunk *chunk);

private:
  static uint8_t ReadByte();
  static Value ReadConst();

  static void resetStack();

  static void push(Value value);
  static Value pop();

  static ExitValue run();
};
