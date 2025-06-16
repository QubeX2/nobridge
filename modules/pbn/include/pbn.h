#ifndef PBN_PBN_H
#define PBN_PBN_H

/**
 * (1) the identification section
 * (2) the auction section
 * (3) the play section
 * (4) supplemental section
 */

#include <vector>

#include "game.h"

namespace nobridge::pbn {

    struct Pbn {
        std::vector<Game> games;
    };

}  // namespace nobridge::pbn

#endif
