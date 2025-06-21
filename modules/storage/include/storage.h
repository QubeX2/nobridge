#ifndef STORAGE_STORAGE_H
#define STORAGE_STORAGE_H

#include <cstddef>

#include "vect.h"
namespace nobridge::storage {
    std::size_t write(std::string filename, const char* data, std::size_t size);
    std::size_t read(std::string filename, char* data, std::size_t size);
}  // namespace nobridge::storage

#endif
