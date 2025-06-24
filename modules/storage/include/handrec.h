#ifndef STORAGE_HANDREC_H
#define STORAGE_HANDREC_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

#include "types.h"
#include "vmath.h"

namespace nobridge::storage {

    struct HandRec {
        UIntID id;
        UIntID gameid;      // GameRec
        UIntVal direction;  // NORTH = 1
        FloatArray<vmath::POS_SIZE> vect{};
        float length;
        float angle;
        UIntArray<HAND_LENGTH> cards{};
    };

}  // namespace nobridge::storage

#endif
