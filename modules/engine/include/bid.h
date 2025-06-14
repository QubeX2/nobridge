#ifndef ENGINE_BID_H
#define ENGINE_BID_H

#include "card.h"
#include "player.h"
#include <cstdint>

namespace nobridge::engine {

enum BidType { PASS = 1, DOUBLE, REDOUBLE, ALERT, NORMAL, CONVENTIONAL };

class Bid {
  BidType m_type;
  uint8_t m_level;
  Suit m_suit;
  std::shared_ptr<Player> m_bidder;

public:
};

}

#endif
