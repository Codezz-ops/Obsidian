// written by TheDevConnor 2024-01-21
#include "vm.hpp"
#include "../../common.hpp"
#include "../debug/debug.hpp"
#include "../value/value.hpp"

#include <cstdint>
#include <iostream>
#include <unordered_map>

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

    uint8_t instruction = ReadByte();
    std::unordered_map<OpCodes, ExitValue (*)(void)>::const_iterator it;
    it = instructions.find(static_cast<OpCodes>(instruction));
    if (it != instructions.end()) {
      // check if the instruction is in the map
      ExitValue result = it->second();
      // if we are equal to an OPReturn then we return
      if (result == VM_RETURN) {
        return VM_RETURN;
      }
    } else {
      std::cout << "Unknown opcode " << instruction << std::endl;
      return VM_ERROR;
    }
  }
}

ExitValue ClassVM::interpret(Chunk *chunk) {
  vm.chunk = chunk;
  vm.ip = vm.chunk->code;
  return run();
}
