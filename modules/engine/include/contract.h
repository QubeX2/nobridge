#ifndef CONTRACT_H
#define CONTRACT_H

#include <cstdint>

#include "bid.h"
#include "card.h"
#include "player.h"

namespace nobridge::engine {

    class Contract {
        uint8_t m_level;
        Suit m_suit;
        // doubled??
        Player m_declarer;

       public:
    };

}  // namespace nobridge::engine
#endif
