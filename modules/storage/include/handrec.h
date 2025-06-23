#ifndef STORAGE_HANDREC_H
#define STORAGE_HANDREC_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace nobridge::storage {

    struct HandRec {
        uint64_t id;
        uint64_t gameid;  // GameRec
        std::array<float, 14> vect;
        float length;
        float angle;
        std::array<char, 100> str;
    };

}  // namespace nobridge::storage

#endif
