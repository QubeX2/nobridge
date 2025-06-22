#ifndef STORAGE_HANDREC_H
#define STORAGE_HANDREC_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace nobridge::storage {

    template <typename T, std::size_t N>
    struct HandRec {
        uint64_t id;
        uint64_t gameid;  // GameRec
        std::string str;
        std::array<T, N> vect;
        float length;
        float angle;
    };

}  // namespace nobridge::storage

#endif
