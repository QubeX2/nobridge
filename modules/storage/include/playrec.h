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
        UIntID gameid;      // GameRec
        UIntVal direction;  // NORTH = 1
        UIntTrickArray tricks;
    };

}  // namespace nobridge::storage

#endif
