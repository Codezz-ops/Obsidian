// writen by TheDevConnor on 2023-01-20
#pragma once

#include <cstdlib>

//! Note: Need to switch the ptrs to be std::unique_ptr instead raw ptrs

class Memory {
public:
  static int GrowCapacity(int cap);

  template <typename T> static T *freeArray(T *ptr, int oldCount) {
    return (T *)realloc(ptr, sizeof(T) * oldCount, 0);
  }

  template <typename T>
  static T *GrowArray(T *ptr, int oldCount, int newCount) {
    if (newCount == 0) {
      free(ptr);
      return nullptr;
    }

    return (T *)realloc(ptr, sizeof(T) * oldCount, sizeof(T) * newCount);
  }

private:
  static void *realloc(void *ptr, size_t oldSize, size_t newSize);
};
