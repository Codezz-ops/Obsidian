// written by TheDevConnor 2024-01-21
#include "vm.hpp"
#include "../../common.hpp"
#include "../debug/debug.hpp"
#include "../value/value.hpp"

#include <cstdint>
#include <iostream>

uint8_t ClassVM::ReadByte() { return *vm.ip++; }
Value ClassVM::ReadConst() { return vm.chunk->constants.values[ReadByte()]; }

void ClassVM::resetStack() { vm.stackTop = vm.stack; }

void ClassVM::push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

Value ClassVM::pop() {
  vm.stackTop--;
  return *vm.stackTop;
}

void ClassVM::initVm() { ClassVM::resetStack(); }

void ClassVM::freeVm() {}

ExitValue ClassVM::run() {
  while (1) {
#ifdef TRACE_EXECUTION
    std::cout << "          ";
    for (Value *slot = vm.stack; slot < vm.stackTop; slot++) {
      std::cout << "[ ";
      ClassValue::printValue(*slot);
      std::cout << " ]";
    }
    std::cout << std::endl;
    Debug::dissassembleInstruction(vm.chunk,
                                   static_cast<int>(vm.ip - vm.chunk->code));
#endif

    uint8_t instruction;
    switch (instruction = ReadByte()) {
    case OPConstant: {
      Value constant = ReadConst();
      push(constant);
      break;
    }
    case OPNegate:
      push(-pop());
      break;
    case OPReturn: {
      ClassValue::printValue(pop());
      std::cout << std::endl;
      return OK;
    }
    }
  }
}

ExitValue ClassVM::interpret(Chunk *chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}
