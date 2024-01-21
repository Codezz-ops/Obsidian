// writen by TheDevConnor on 2023-01-20
#include "value.hpp"
#include "../mem/memory.hpp"

#include <iostream>

void ClassValue::printValue(Value value) { std::cout << value; }

void ClassValue::initValueArray(ValueArray *array) {
  array->values = nullptr;
  array->capacity = 0;
  array->count = 0;
}

void ClassValue::writeValueArray(ValueArray *array, Value value) {
  if (array->capacity < array->count + 1) {
    int oldCap = array->capacity;
    array->capacity = Memory::GrowCapacity(oldCap);
    array->values =
        Memory::GrowArray<Value>(array->values, oldCap, array->capacity);
  }

  array->values[array->count] = value;
  array->count++;
}

void ClassValue::freeValueArray(ValueArray *array) {
  Memory::freeArray<Value>(array->values, array->capacity);
  initValueArray(array);
}
