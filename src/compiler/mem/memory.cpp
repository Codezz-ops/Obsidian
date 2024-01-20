// writen by TheDevConnor on 2021-03-28
#include "../../helper/errors.hpp"
#include "memory.hpp"

//!Note: Need to switch the ptrs to be std::unique_ptr instead raw ptrs

int Memory::GrowCapacity(int cap) {
  return ((cap) < 8 ? 8 : (cap) * 2);
}

void *Memory::realloc(void *ptr, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    free(ptr);
    return nullptr;
  }

  void *result = std::realloc(ptr, newSize);
  if (result == nullptr) 
    Error::memError("Memory allocation failure");

  return result;
}

