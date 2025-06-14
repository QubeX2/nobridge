#ifndef NOB_DECK_H
#define NOB_DECK_H

#include "card.h"
#include <memory>
#include <vector>

namespace nobridge {

class Deck {
  std::vector<std::shared_ptr<Card>> m_cards;

public:
  void shuffle();
  std::vector<std::vector<std::shared_ptr<Card>>> deal();
};

}

#endif
