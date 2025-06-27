#ifndef STORAGE_PLAYREC_H
#define STORAGE_PLAYREC_H

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

#include "types.h"
#include "vmath.h"

namespace nobridge::storage {

    struct PlayRec {
        UIntID id;
        UIntID gameid;    // GameRec
        UIntV direction;  // NORTH = 1
        UInt2dA<4, 13> tricks;
    };

}  // namespace nobridge::storage

#endif
