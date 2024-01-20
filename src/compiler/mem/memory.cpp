// written by TheDevConnor
#include "../../common.hpp"
#include "memory.hpp"

#include <cstdlib>

//!Note: Need to switch the ptrs to be std::unique_ptr instead raw ptrs

int Memory::GrowCapacity(int cap) {
  return ((cap) < 8 ? 8 : (cap) * 2);
}