#include "storage.h"

#include <sys/types.h>

#include <array>
#include <cstdint>
#include <fstream>
#include <ios>
#include <random>

#include "gamerec.h"

namespace nobridge::storage {

    /**
     *
     */
    GameRec createGameRec(uint64_t id, std::array<uint64_t, 4> hands) {
        return GameRec{id, hands};
    }

    /**
     *
     */
    uint64_t uniqueId() {
        uint64_t time_since_epoch = std::chrono::high_resolution_clock::now()
                                        .time_since_epoch()
                                        .count();
        static std::mt19937_64 generator(std::random_device{}());
        return time_since_epoch ^ generator();
    }

    /**
     *
     */
    std::size_t write(std::string filename, const char* data,
                      std::size_t size) {
        std::ofstream output(filename, std::ios::binary);
        if (!output) return -1;
        output.write(data, size);
        output.close();
        if (!output.good()) return -1;
        return size;
    }  // namespace nobridge::storage

    /**
     *
     */
    std::size_t read(std::string filename, char* data, std::size_t size) {
        std::ifstream input(filename);
        if (!input) return -1;
        input.read(data, size);
        input.close();
        if (!input.good()) return -1;
        return size;
    }

}  // namespace nobridge::storage
