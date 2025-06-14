#ifndef NOB_CONTRACT_H
#define NOB_CONTRACT_H

#include "bid.h"
#include "card.h"
#include "player.h"
#include <cstdint>

namespace nobridge {

class Contract {
  uint8_t m_level;
  Suit m_suit;
  // doubled??
  Player m_declarer;

public:
};

}
#endif
