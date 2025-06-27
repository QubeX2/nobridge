#ifndef ENGINE_BID_H
#define ENGINE_BID_H

#include <cstdint>
#include <memory>

#include "card.h"
#include "player.h"
#include "types.h"

namespace nobridge::engine {

    class Bid {
       public:
       private:
        Direction m_direction;
        UIntV m_level = 0;
        Suit m_suit;
        BidType m_type;
    };

}  // namespace nobridge::engine

#endif
