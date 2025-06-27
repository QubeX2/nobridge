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
        UIntID gameid;    // GameRec
        UIntV direction;  // NORTH = 1
        FloatA<vmath::POS_SIZE> vect{};
        float length;
        float angle;
        UIntA<HAND_LENGTH> cards{};
    };

}  // namespace nobridge::storage

#endif
