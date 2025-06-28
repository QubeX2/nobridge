#ifndef STORAGE_GAMEREC_H
#define STORAGE_GAMEREC_H

#include <array>
#include <cstddef>
#include <cstdint>

namespace nobridge::storage {

    struct GameRec {
        uint64_t id;
        uint8_t dealer;
        uint8_t vulnerable;
    };

}  // namespace nobridge::storage

#endif
