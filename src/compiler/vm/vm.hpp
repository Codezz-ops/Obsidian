// written by TheDevConnor 2024-01-21
#pragma once

#include "../../common.hpp"
#include "../chunk.hpp"

#include <cstdint>
#include <unordered_map>

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

  // Opcode functions
  static ExitValue OPConstant();
  static ExitValue OPAdd();
  static ExitValue OPSub();
  static ExitValue OPMult();
  static ExitValue OPDiv();
  static ExitValue OPNegate();
  static ExitValue OPReturn();
  
  static ExitValue BinaryOP(double (*operation)(double, double));
  static const std::unordered_map<OpCodes, ExitValue (*)(void)> instructions;
};
