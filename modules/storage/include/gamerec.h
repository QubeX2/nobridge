#ifndef STORAGE_GAMEREC_H
#define STORAGE_GAMEREC_H

#include <array>
#include <cstddef>
#include <cstdint>

namespace nobridge::storage {

    struct GameRec {
        uint64_t id;
        std::array<uint64_t, 4> hands;
    };

}  // namespace nobridge::storage

#endif
