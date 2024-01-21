// written by TheDevConnor 2024-01-21
#include "vm.hpp"
#include "../chunk.hpp"
#include "../../common.hpp"

#include <iostream>
#include <unordered_map>

ExitValue ClassVM::OPConstant() {
  Value constant = ReadConst();
  push(constant);
  return OK;
}

ExitValue ClassVM::OPNegate() {
  push(-pop());
  return OK;
}

ExitValue ClassVM::OPReturn() {
    ClassValue::printValue(pop());
    std::cout << std::endl;
    return VM_RETURN;
}

const std::unordered_map<OpCodes, ExitValue (*)(void)> ClassVM::instructions = {
    {OpCodes::OPConstant, OPConstant},
    {OpCodes::OPNegate,   OPNegate},
    {OpCodes::OPReturn,   OPReturn}
}; 