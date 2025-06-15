#ifndef ENGINE_BID_H
#define ENGINE_BID_H

#include <cstdint>
#include <memory>

#include "card.h"
#include "player.h"

namespace nobridge::engine {

    enum BidType : uint8_t {
        PASS = 1,
        DOUBLE,
        REDOUBLE,
        ALERT,
        NORMAL,
        CONVENTIONAL
    };

    class Bid {
       public:
       private:
        BidType m_type;
        uint8_t m_level;
        Suit m_suit;
        std::shared_ptr<Player> m_bidder;
    };

}  // namespace nobridge::engine

#endif
