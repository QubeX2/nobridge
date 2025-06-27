#ifndef CONTRACT_H
#define CONTRACT_H

#include <cstdint>
#include <memory>

#include "bid.h"
#include "card.h"
#include "player.h"
#include "types.h"

namespace nobridge::engine {

    class Contract {
        UIntV m_level;
        Suit m_suit;
        // doubled??
        Direction m_direction;

       public:
    };

}  // namespace nobridge::engine
#endif
