// writen by TheDevConnor on 2023-01-20
#pragma once

typedef double Value;

struct ValueArray {
  Value *values;
  int capacity;
  int count;
};

class ClassValue {
public:
  static void initValueArray(ValueArray *array);
  static void writeValueArray(ValueArray *array, Value value);
  static void freeValueArray(ValueArray *array);

  static void printValue(Value value);

private:
};
