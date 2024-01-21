// writen by TheDevConnor on 2023-01-20
#include "memory.hpp"
#include "../../helper/errors.hpp"

//! Note: Need to switch the ptrs to be std::unique_ptr instead raw ptrs

int Memory::GrowCapacity(int cap) { return ((cap) < 8 ? 8 : (cap) * 2); }

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
