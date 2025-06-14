#ifndef PBNLIB_PBN_H
#define PBNLIB_PBN_H

/**
 * (1) the identification section
 * (2) the auction section
 * (3) the play section
 * (4) supplemental section
 */

#include <vector>

#include "game.h"

namespace nobridge::pbn {

    class Pbn {
       public:
       private:
        std::vector<Game> m_games;
    };

}  // namespace nobridge::pbn

#endif
