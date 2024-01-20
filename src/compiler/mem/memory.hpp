// written by TheDevConnor
#pragma once

#include "../../common.hpp"

#include <cstdlib>
#include <memory>

class Memory {
public:
  Memory() = delete;
  ~Memory() = delete;

  static int GrowCapacity(int cap);

  template <typename T>
  static std::unique_ptr<T[]> freeArray(T *ptr, int oldCount) {
    return std::unique_ptr<T[]>(static_cast<T*>(realloc(ptr, sizeof(T) * oldCount, 0)));
  }

    template <typename T>
    static std::unique_ptr<T[]> GrowArray(std::unique_ptr<T[]>& ptr, int oldCount, int newCount) {
        if (newCount == 0) {
            return nullptr;
        }

        T* rawPtr = static_cast<T*>(realloc(ptr.get(), sizeof(T) * oldCount, sizeof(T) * newCount));
        return std::unique_ptr<T[]>(rawPtr, std::default_delete<T[]>());
    }

private:
    static void* realloc(void *ptr, size_t oldSize, size_t newSize) {
        if (newSize == 0) {
            free(ptr);
            return nullptr;
        }

        void *result = std::realloc(ptr, newSize);
        if (result == nullptr)
            Exit(ExitValue::MEMORY_ALLOCATION_FAILURE);
        return result;
    }
};
