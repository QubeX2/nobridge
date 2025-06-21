#include "storage.h"

#include <fstream>
#include <ios>

namespace nobridge::storage {
    std::size_t write(std::string filename, const char* data,
                      std::size_t size) {
        std::ofstream output(filename, std::ios::binary);
        if (!output) return -1;
        output.write(data, size);
        output.close();
        if (!output.good()) return -1;
        return size;
    }  // namespace nobridge::storage

    std::size_t read(std::string filename, char* data, std::size_t size) {
        std::ifstream input(filename);
        if (!input) return -1;
        input.read(data, size);
        input.close();
        if (!input.good()) return -1;
        return size;
    }

}  // namespace nobridge::storage
