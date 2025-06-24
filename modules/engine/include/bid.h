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
        BidType m_type;
        UIntVal m_level = 0;
        Suit m_suit;
        PlayerPtr m_bidder;
    };

}  // namespace nobridge::engine

#endif
