
// written by TheDevConnor 2024-01-21
#include "../../common.hpp" // Include necessary headers
#include "../chunk.hpp"
#include "vm.hpp"

#include <iostream>
#include <unordered_map>

// Implementation of binary operations on the virtual machine
ExitValue ClassVM::BinaryOP(double (*operation)(double, double)) {
  double b = pop();      // Pop the second operand from the stack
  double a = pop();      // Pop the first operand from the stack
  push(operation(a, b)); // Perform the binary operation and push the result
                         // back onto the stack
  return OK;             // Return the exit value indicating success
}

// Implementation of the constant operation on the virtual machine
ExitValue ClassVM::OPConstant() {
  Value constant =
      ReadConst(); // Read a constant value from the instruction stream
  push(constant);  // Push the constant value onto the stack
  return OK;       // Return the exit value indicating success
}

// Implementation of the addition operation on the virtual machine
ExitValue ClassVM::OPAdd() {
  return BinaryOP([](double a, double b) {
    return a + b;
  }); // Use the BinaryOP function with a lambda for addition
}

// Implementation of the subtraction operation on the virtual machine
ExitValue ClassVM::OPSub() {
  return BinaryOP([](double a, double b) {
    return a - b;
  }); // Use the BinaryOP function with a lambda for subtraction
}

// Implementation of the multiplication operation on the virtual machine
ExitValue ClassVM::OPMult() {
  return BinaryOP([](double a, double b) {
    return a * b;
  }); // Use the BinaryOP function with a lambda for multiplication
}

// Implementation of the division operation on the virtual machine
ExitValue ClassVM::OPDiv() {
  return BinaryOP([](double a, double b) {
    return a / b;
  }); // Use the BinaryOP function with a lambda for division
}

// Implementation of the negation operation on the virtual machine
ExitValue ClassVM::OPNegate() {
  push(-pop()); // Negate the top value on the stack and push it back onto the
                // stack
  return OK;    // Return the exit value indicating success
}

// Implementation of the return operation on the virtual machine
ExitValue ClassVM::OPReturn() {
  ClassValue::printValue(pop()); // Print the top value on the stack
  std::cout << std::endl;        // Output a newline
  return VM_RETURN; // Return the exit value indicating a return from the
                    // virtual machine
}

// Map of opcode to corresponding function pointers for the virtual machine
// instructions
const std::unordered_map<OpCodes, ExitValue (*)(void)> ClassVM::instructions = {
    {OpCodes::OPConstant, OPConstant}, {OpCodes::OPAdd, OPAdd},
    {OpCodes::OPSub, OPSub},           {OpCodes::OPMult, OPMult},
    {OpCodes::OPDiv, OPDiv},           {OpCodes::OPNegate, OPNegate},
    {OpCodes::OPReturn, OPReturn}};
