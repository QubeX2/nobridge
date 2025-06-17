#ifndef PBN_PBN_H
#define PBN_PBN_H

/**
 * (1) the identification section
 * (2) the auction section
 * (3) the play section
 * (4) supplemental section
 */

#include <memory>
#include <vector>

#include "game.h"
#include "parser.h"

namespace nobridge::pbn {

    class Pbn {
       public:
       private:
        std::vector<Game> m_games;
    };

    using PbnPtr = std::shared_ptr<Pbn>;

    PbnPtr process(GameList& glist);
}  // namespace nobridge::pbn

#endif
