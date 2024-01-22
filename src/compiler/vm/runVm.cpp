// written by TheDevConnor 2024-01-21
#include "../../common.hpp"
#include "../chunk.hpp"
#include "vm.hpp"

#include <iostream>
#include <unordered_map>

ExitValue ClassVM::BinaryOP(double (*operation)(double, double)) {
  double b = pop();
  double a = pop();
  push(operation(a, b));
  return OK;
}

ExitValue ClassVM::OPConstant() {
  Value constant = ReadConst();
  push(constant);
  return OK;
}

ExitValue ClassVM::OPAdd() {
  return BinaryOP([](double a, double b) { return a + b; });
}

ExitValue ClassVM::OPSub() {
  return BinaryOP([](double a, double b) { return a - b; });
}

ExitValue ClassVM::OPMult() {
  return BinaryOP([](double a, double b) { return a * b; });
}

ExitValue ClassVM::OPDiv() {
  return BinaryOP([](double a, double b) { return a / b; });
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
    {OpCodes::OPConstant, OPConstant}, {OpCodes::OPAdd, OPAdd},
    {OpCodes::OPSub, OPSub},           {OpCodes::OPMult, OPMult},
    {OpCodes::OPDiv, OPDiv},           {OpCodes::OPNegate, OPNegate},
    {OpCodes::OPReturn, OPReturn}};
