#ifndef STORAGE_HANDREC_H
#define STORAGE_HANDREC_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

#include "types.h"

namespace nobridge::storage {

    struct HandRec {
        UIntID id;
        UIntID gameid;      // GameRec
        UIntVal direction;  // NORTH = 1
        FloatArray<14> vect{};
        float length;
        float angle;
        UIntArray<13> cards{};
    };

}  // namespace nobridge::storage

#endif
